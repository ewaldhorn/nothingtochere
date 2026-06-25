library basic_canvas;

// ---------------------------------------------------------------------------
// Bouncing neon balls with elastic collision — Free Pascal → WASM
// All drawing into a linear RGBA pixel buffer. JS blits to <canvas>.
// No RTL dependencies beyond compiler intrinsics.
// Translation of the freestanding C version at
// https://github.com/ewaldhorn/nothingtochere/tree/main/c/withzig/wasm/basic_canvas
// ---------------------------------------------------------------------------

{$mode fpc}
{$inline on}
{$WARN 5025 off}  // no sysmelon for freestanding; ignore ext declaration warning

// ---------------------------------------------------------------------------
// Canvas dimensions
// ---------------------------------------------------------------------------
const
  WIDTH    = 800;
  HEIGHT   = 600;
  BUF_SIZE = LongInt(WIDTH) * LongInt(HEIGHT) * 4;  // = 1 920 000

// ---------------------------------------------------------------------------
// Ball ring buffer — MAX_BALLS MUST be a power of two for bitwise wraparound
// ---------------------------------------------------------------------------
const
  MAX_BALLS = 256;  // 2^8

{$IF (MAX_BALLS and (MAX_BALLS - 1)) <> 0}
  {$FATAL MAX_BALLS must be a power of two}
{$ENDIF}

type
  TBall = record
    x, y: Single;
    vx, vy: Single;
    radius: Single;
    r, g, b: Byte;
  end;

// ---------------------------------------------------------------------------
// Global state
// ---------------------------------------------------------------------------
var
  balls: array[0..MAX_BALLS - 1] of TBall;
  ballCount: Integer = 0;  // number of active balls (0..MAX_BALLS)
  ballHead:  Integer = 0;  // ring-buffer index of the oldest ball

  // Xorshift32 PRNG
  rngState: Cardinal = $DEADBEEF;

// ---------------------------------------------------------------------------
// Primitives — host-side entry points expected by FPC runtime
// ---------------------------------------------------------------------------
procedure _haltproc(exitCode: Integer); external 'env' name '_haltproc';

// Pixel buffer base address — fixed offset past static data in WASM memory.
// $20000 (128 KB) is safely past all data segments (~104 KB) with margin.
// Must be recomputed if WIDTH, HEIGHT, or MAX_BALLS change significantly.
function PixelBase: PByte; inline;
begin
  PixelBase := PByte($20000);  // 128 KB
end;

// ---------------------------------------------------------------------------
// PRNG — xorshift32 (deterministic, fast, no libc needed)
// ---------------------------------------------------------------------------
function RngNext: Cardinal;
begin
  rngState := rngState xor (rngState shl 13);
  rngState := rngState xor (rngState shr 17);
  rngState := rngState xor (rngState shl 5);
  RngNext := rngState;
end;

function RngFloat: Single;
begin
  // Shift to 24 bits; divide by 2^24 for a uniform [0, 1) float.
  RngFloat := (RngNext shr 8) / 16777216.0;
end;

// ---------------------------------------------------------------------------
// Square root — delegates to FPC's built-in Sqrt, which on wasm32-embedded
// maps to the f32.sqrt WASM instruction (single uop, IEEE 754 exact).
// ---------------------------------------------------------------------------
function FPSqrt(x: Single): Single;
begin
  if x <= 0.0 then
    FPSqrt := 0.0
  else
    FPSqrt := Sqrt(x);
end;

// ---------------------------------------------------------------------------
// Pixel helpers
// ---------------------------------------------------------------------------
procedure SetPixel(x, y: Integer; r, g, b, a: Byte);
var
  idx: Cardinal;
  inv: Byte;
  p: PByte;
begin
  if (Cardinal(x) >= WIDTH) or (Cardinal(y) >= HEIGHT) then Exit;
  p := PixelBase;
  idx := (Cardinal(y) * WIDTH + Cardinal(x)) * 4;
  if a = 255 then
  begin
    p[idx + 0] := r;
    p[idx + 1] := g;
    p[idx + 2] := b;
    p[idx + 3] := 255;
  end
  else
  begin
    inv := 255 - a;
    p[idx + 0] := Byte((Word(r) * a + Word(p[idx + 0]) * inv) div 255);
    p[idx + 1] := Byte((Word(g) * a + Word(p[idx + 1]) * inv) div 255);
    p[idx + 2] := Byte((Word(b) * a + Word(p[idx + 2]) * inv) div 255);
    p[idx + 3] := 255;
  end;
end;

// Unchecked write — caller guarantees 0 <= x < WIDTH, 0 <= y < HEIGHT.
procedure SetPixelUnchecked(x, y: Integer; r, g, b: Byte);
var
  idx: Cardinal;
  p: PByte;
begin
  p := PixelBase;
  idx := (Cardinal(y) * WIDTH + Cardinal(x)) * 4;
  p[idx + 0] := r;
  p[idx + 1] := g;
  p[idx + 2] := b;
  p[idx + 3] := 255;
end;

// Fill a horizontal span, clamping x to [0, WIDTH-1]
procedure FillScanline(y, x0, x1: Integer; r, g, b: Byte);
var
  px: Integer;
  p: PByte;
begin
  if Cardinal(y) >= HEIGHT then Exit;
  if x0 < 0 then x0 := 0;
  if x1 >= WIDTH then x1 := WIDTH - 1;
  p := PixelBase;
  for px := x0 to x1 do
  begin
    SetPixelUnchecked(px, y, r, g, b);
    // Note: SetPixelUnchecked calls PixelBase again — the inline
    // should optimize the redundant load away with -O3.
  end;
end;

// ---------------------------------------------------------------------------
// Drawing primitives
// ---------------------------------------------------------------------------

// Fill the entire pixel buffer with a solid colour.
// Writes 32-bit words (RGBA packed) instead of 4 individual bytes per pixel.
// WASM is little-endian, so the in-memory byte order is R, G, B, A.
procedure ClearScreen(r, g, b: Byte);
var
  color: Cardinal;
  p: ^Cardinal;
  i: LongInt;
begin
  color := r or (Cardinal(g) shl 8) or (Cardinal(b) shl 16) or (255 shl 24);
  p := pointer(PixelBase);
  for i := 0 to BUF_SIZE div 4 - 1 do
    p[i] := color;
end;

// Midpoint circle (outline)
procedure DrawCircle(cx, cy, radius: Integer; r, g, b: Byte);
var
  x, y, dp: Integer;
begin
  x  := radius;
  y  := 0;
  dp := 1 - radius;
  while x >= y do
  begin
    SetPixel(cx + x, cy + y, r, g, b, 255);
    SetPixel(cx - x, cy + y, r, g, b, 255);
    SetPixel(cx + x, cy - y, r, g, b, 255);
    SetPixel(cx - x, cy - y, r, g, b, 255);
    SetPixel(cx + y, cy + x, r, g, b, 255);
    SetPixel(cx - y, cy + x, r, g, b, 255);
    SetPixel(cx + y, cy - x, r, g, b, 255);
    SetPixel(cx - y, cy - x, r, g, b, 255);
    Inc(y);
    if dp <= 0 then
      dp := dp + 2 * y + 1
    else
    begin
      Dec(x);
      dp := dp + 2 * (y - x) + 1;
    end;
  end;
end;

// Filled circle — uses FillScanline to fill horizontal spans.
procedure DrawFilledCircle(cx, cy, radius: Integer; r, g, b: Byte);
var
  x, y, dp: Integer;
begin
  x  := radius;
  y  := 0;
  dp := 1 - radius;
  while x >= y do
  begin
    FillScanline(cy + y, cx - x, cx + x, r, g, b);
    if y <> 0 then
      FillScanline(cy - y, cx - x, cx + x, r, g, b);
    FillScanline(cy + x, cx - y, cx + y, r, g, b);
    if x <> y then
      FillScanline(cy - x, cx - y, cx + y, r, g, b);
    Inc(y);
    if dp <= 0 then
      dp := dp + 2 * y + 1
    else
    begin
      Dec(x);
      dp := dp + 2 * (y - x) + 1;
    end;
  end;
end;

// ---------------------------------------------------------------------------
// Ball management
// ---------------------------------------------------------------------------
procedure SpawnBall(x, y: Single);
var
  slot, pick: Integer;
  b: ^TBall;
begin
  if ballCount < MAX_BALLS then
  begin
    // Ring not full: append at the next free slot.
    slot := (ballHead + ballCount) and (MAX_BALLS - 1);
    Inc(ballCount);
  end
  else
  begin
    // Ring full: overwrite the oldest ball and advance the head — O(1).
    slot := ballHead;
    ballHead := (ballHead + 1) and (MAX_BALLS - 1);
  end;

  b := @balls[slot];
  // Jitter spawn position so rapid clicks at the same spot don't
  // create perfectly overlapping balls that the collision code skips.
  b^.x      := x + (RngFloat - 0.5) * 12.0;
  b^.y      := y + (RngFloat - 0.5) * 12.0;
  b^.vx     := (RngFloat - 0.5) * 300.0;
  b^.vy     := (RngFloat - 0.5) * 300.0;
  b^.radius := 10.0 + RngFloat * 20.0;

  // Neon colours
  pick := Integer(RngNext mod 6);
  case pick of
    0: begin b^.r :=   0; b^.g := 255; b^.b := 255; end;  // cyan
    1: begin b^.r := 255; b^.g := 100; b^.b := 200; end;  // pink
    2: begin b^.r := 100; b^.g := 255; b^.b :=  50; end;  // lime
    3: begin b^.r := 255; b^.g := 200; b^.b :=   0; end;  // amber
    4: begin b^.r := 100; b^.g := 150; b^.b := 255; end;  // periwinkle
  else
    begin b^.r := 255; b^.g :=  60; b^.b :=  60; end;  // red
  end;
end;

// ---------------------------------------------------------------------------
// Physics
// ---------------------------------------------------------------------------
procedure UpdateBalls(dt: Single);
var
  i, j, idx_a, idx_b: Integer;
  a, b: ^TBall;
  dx, dy, dist_sq, dist, min_dist: Single;
  nx, ny, dvx, dvy, vn, overlap, push: Single;
begin
  // Move balls and bounce off walls
  for i := 0 to ballCount - 1 do
  begin
    a := @balls[(ballHead + i) and (MAX_BALLS - 1)];
    a^.x := a^.x + a^.vx * dt;
    a^.y := a^.y + a^.vy * dt;

    // Wall bounce — right
    if a^.x + a^.radius > WIDTH then
    begin
      a^.x := WIDTH - a^.radius;
      a^.vx := -a^.vx;
    end;
    // Wall bounce — left
    if a^.x - a^.radius < 0 then
    begin
      a^.x := a^.radius;
      a^.vx := -a^.vx;
    end;
    // Wall bounce — bottom
    if a^.y + a^.radius > HEIGHT then
    begin
      a^.y := HEIGHT - a^.radius;
      a^.vy := -a^.vy;
    end;
    // Wall bounce — top
    if a^.y - a^.radius < 0 then
    begin
      a^.y := a^.radius;
      a^.vy := -a^.vy;
    end;
  end;

  // Collision detection — O(n^2) elastic collision between equal-mass circles
  for i := 0 to ballCount - 2 do
  begin
    idx_a := (ballHead + i) and (MAX_BALLS - 1);
    a := @balls[idx_a];
    for j := i + 1 to ballCount - 1 do
    begin
      idx_b := (ballHead + j) and (MAX_BALLS - 1);
      b := @balls[idx_b];

      dx := a^.x - b^.x;
      dy := a^.y - b^.y;
      dist_sq := dx * dx + dy * dy;
      min_dist := a^.radius + b^.radius;

      // No overlap — skip
      if dist_sq >= min_dist * min_dist then
        Continue;

      // Extremely close? nudge apart (guard against division-by-zero)
      if dist_sq < 0.0001 then
      begin
        a^.x := a^.x + 0.5;
        b^.x := b^.x - 0.5;
        Continue;
      end;

      dist := FPSqrt(dist_sq);
      nx := dx / dist;
      ny := dy / dist;

      // Relative velocity along the collision normal
      dvx := a^.vx - b^.vx;
      dvy := a^.vy - b^.vy;
      vn := dvx * nx + dvy * ny;

      // Always separate overlapping balls — fixes balls that spawn already
      // overlapping, which the velocity check alone would never resolve.
      overlap := min_dist - dist;
      push := overlap * 0.5 + 0.1;  // tiny extra nudge to prevent sticking
      a^.x := a^.x + push * nx;
      a^.y := a^.y + push * ny;
      b^.x := b^.x - push * nx;
      b^.y := b^.y - push * ny;

      // Only swap velocities if balls are approaching each other.
      if vn < 0.0 then
      begin
        a^.vx := a^.vx - vn * nx;
        a^.vy := a^.vy - vn * ny;
        b^.vx := b^.vx + vn * nx;
        b^.vy := b^.vy + vn * ny;
      end;
    end;
  end;
end;

procedure DrawBalls;
var
  i, idx, rad: Integer;
  b: ^TBall;
begin
  for i := 0 to ballCount - 1 do
  begin
    idx := (ballHead + i) and (MAX_BALLS - 1);
    b := @balls[idx];
    rad := Trunc(b^.radius);
    if rad > 0 then
    begin
      DrawFilledCircle(Trunc(b^.x), Trunc(b^.y), rad, b^.r, b^.g, b^.b);
      DrawCircle(Trunc(b^.x), Trunc(b^.y), rad, 255, 255, 255);
    end;
  end;
end;

// ---------------------------------------------------------------------------
// Exported API — called from JavaScript
// ---------------------------------------------------------------------------

procedure wasm_init;
var
  i: LongInt;
  p: PByte;
begin
  // Zero the pixel buffer
  p := PixelBase;
  for i := 0 to BUF_SIZE - 1 do
    p[i] := 0;

  ballCount := 0;
  ballHead  := 0;

  // Seed with initial balls spread across the canvas
  for i := 1 to 6 do
    SpawnBall(100.0 + RngFloat * 600.0, 80.0 + RngFloat * 440.0);
end;

procedure wasm_update(dt: Single);
begin
  // Cap: prevents tunnelling on a frozen/slow tab
  if dt > 0.1   then dt := 0.1;
  // Floor: also covers zero, negative, and near-zero dt
  if dt < 0.001 then dt := 0.001;

  // Order matters: clear first so DrawBalls() always writes into a fresh frame.
  ClearScreen(10, 5, 20);

  UpdateBalls(dt);
  DrawBalls;
end;

procedure wasm_click(x, y: Integer);
begin
  SpawnBall(Single(x), Single(y));
end;

function wasm_get_pixels: PByte;
begin
  wasm_get_pixels := PixelBase;
end;

function wasm_get_width: Integer;
begin
  wasm_get_width := WIDTH;
end;

function wasm_get_height: Integer;
begin
  wasm_get_height := HEIGHT;
end;

// ---------------------------------------------------------------------------
// Export table
// ---------------------------------------------------------------------------
exports
  wasm_init       name 'wasm_init',
  wasm_update     name 'wasm_update',
  wasm_click      name 'wasm_click',
  wasm_get_pixels name 'wasm_get_pixels',
  wasm_get_width  name 'wasm_get_width',
  wasm_get_height name 'wasm_get_height';

begin
end.
