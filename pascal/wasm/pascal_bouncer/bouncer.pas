library bouncer;

{$mode fpc}
{$inline on}
{$WARN 5025 off}

// ------------------------------------------------------------------------------------------------
const
  COLS: Integer = 40;
  ROWS: Integer = 25;
  CELL_SIZE: Integer = 30;
  WIDTH: Integer = 1200;
  HEIGHT: Integer = 750;

  // Colours (packed as AABBGGRR — DrawFilledRect writes byte[0]=R, byte[1]=G, byte[2]=B, byte[3]=A)
  COL_BG: Cardinal = $FF501405;      // Navy blue (5, 20, 80, 255)
  COL_LAND: Cardinal = $FF3A600C;    // Green (12, 96, 58, 255)
  COL_TRAIL: Cardinal = $FFFF00FF;   // Magenta (255, 0, 255, 255)
  COL_PLAYER: Cardinal = $FFFFFFFF;  // White (255, 255, 255, 255)
  COL_ENEMY: Cardinal = $FF5500FF;   // Red (255, 0, 85, 255)
  COL_LAND_ENEMY: Cardinal = $FF0078FF; // Orange (255, 120, 0, 255)
  COL_OVERLAY: Cardinal = $80000000; // Semi-transparent black

  MAX_ENEMIES: Integer = 10;

// ------------------------------------------------------------------------------------------------
type
  TCell = (Sea, Land, Trail);

  TStackPos = record
    col, row: Integer;
  end;

  TEnemyData = record
    pixel_x, pixel_y: Single;
    vel_x, vel_y: Single;
    size: Single;
    active: Boolean;
  end;

  TGameStatus = (StartScreen, Playing, GameOver, LevelUpDelay);

// ------------------------------------------------------------------------------------------------
var
  grid: array[0..24, 0..39] of TCell;
  player: record
    col, row: Integer;
    dx, dy: Integer;
    moveTimer: Single;
    moveInterval: Single;
  end;
  enemies: array[0..9] of TEnemyData;
  enemyCount: Integer;
  landEnemy: TEnemyData;
  score, level, lives: Integer;
  gameStatus: TGameStatus;
  levelUpTimer: Double;
  canvasWidth, canvasHeight: Integer;
  canvasPixels: PByte;
  canvasInitialized: Boolean;

// ── Random number generator ────────────────────────────────────────────────
var
  rngState: Cardinal = 1;

// ------------------------------------------------------------------------------------------------
function RngNext: Cardinal;
var
  x: Cardinal;
begin
  x := rngState;
  x := x xor (x shl 13);
  x := x xor (x shr 17);
  x := x xor (x shl 5);
  rngState := x;
  RngNext := x;
end;

// ------------------------------------------------------------------------------------------------
function RngInt(maxVal: Integer): Integer;
begin
  if maxVal <= 0 then RngInt := 0
  else RngInt := RngNext mod maxVal;
end;

// ------------------------------------------------------------------------------------------------
function CellToPixelX(c: Integer): Integer;
begin
  CellToPixelX := c * CELL_SIZE;
end;

// ------------------------------------------------------------------------------------------------
function CellToPixelY(r: Integer): Integer;
begin
  CellToPixelY := r * CELL_SIZE;
end;

// ------------------------------------------------------------------------------------------------
function MinInt(a, b: Integer): Integer;
begin
  if a < b then MinInt := a else MinInt := b;
end;

// ------------------------------------------------------------------------------------------------
function MaxInt(a, b: Integer): Integer;
begin
  if a > b then MaxInt := a else MaxInt := b;
end;

// ------------------------------------------------------------------------------------------------
procedure ResetGrid;
var
  c, r: Integer;
begin
  for r := 0 to ROWS - 1 do
    for c := 0 to COLS - 1 do
      grid[r, c] := Sea;
  for r := 0 to ROWS - 1 do
    for c := 0 to COLS - 1 do
      if (c < 2) or (c >= COLS - 2) or (r < 2) or (r >= ROWS - 2) then
        grid[r, c] := Land;
end;

// ------------------------------------------------------------------------------------------------
procedure ClearTrail;
var
  c, r: Integer;
begin
  for r := 0 to ROWS - 1 do
    for c := 0 to COLS - 1 do
      if grid[r, c] = Trail then
        grid[r, c] := Sea;
end;

// ------------------------------------------------------------------------------------------------
function GetPercentCaptured: Integer;
var
  c, r, landCount: Integer;
begin
  landCount := 0;
  for c := 0 to COLS - 1 do
    for r := 0 to ROWS - 1 do
      if grid[r, c] = Land then
        Inc(landCount);
  GetPercentCaptured := (landCount * 100) div (COLS * ROWS);
end;

// ------------------------------------------------------------------------------------------------
function CellAt(x, y: Integer): TCell;
begin
  if (x < 0) or (x >= COLS) or (y < 0) or (y >= ROWS) then
    CellAt := Land
  else
    CellAt := grid[y, x];
end;

// ------------------------------------------------------------------------------------------------
procedure EnemySetGridPos(var e: TEnemyData; gx, gy: Integer);
begin
  e.pixel_x := gx * CELL_SIZE + (CELL_SIZE - e.size) / 2.0;
  e.pixel_y := gy * CELL_SIZE + (CELL_SIZE - e.size) / 2.0;
end;

// ------------------------------------------------------------------------------------------------
function EnemyCheckCollision(e: TEnemyData; testX, testY: Single): Boolean;
var
  cs: Single;
  gx, gy, i: Integer;
  ptsX: array[0..3] of Single;
  ptsY: array[0..3] of Single;
begin
  cs := CELL_SIZE;
  ptsX[0] := testX;        ptsY[0] := testY;
  ptsX[1] := testX + e.size; ptsY[1] := testY;
  ptsX[2] := testX;        ptsY[2] := testY + e.size;
  ptsX[3] := testX + e.size; ptsY[3] := testY + e.size;
  for i := 0 to 3 do
  begin
    gx := Trunc(ptsX[i] / cs);
    gy := Trunc(ptsY[i] / cs);
    if CellAt(gx, gy) = Land then
      Exit(True);
  end;
  EnemyCheckCollision := False;
end;

// ------------------------------------------------------------------------------------------------
function EnemyCheckLandCollision(e: TEnemyData; testX, testY: Single): Boolean;
var
  cs: Single;
  gx, gy, i: Integer;
  ptsX: array[0..3] of Single;
  ptsY: array[0..3] of Single;
begin
  cs := CELL_SIZE;
  ptsX[0] := testX;        ptsY[0] := testY;
  ptsX[1] := testX + e.size; ptsY[1] := testY;
  ptsX[2] := testX;        ptsY[2] := testY + e.size;
  ptsX[3] := testX + e.size; ptsY[3] := testY + e.size;
  for i := 0 to 3 do
  begin
    gx := Trunc(ptsX[i] / cs);
    gy := Trunc(ptsY[i] / cs);
    if (gx < 0) or (gx >= COLS) or (gy < 0) or (gy >= ROWS) then
      Exit(True);
    if CellAt(gx, gy) <> Land then
      Exit(True);
  end;
  EnemyCheckLandCollision := False;
end;

// ------------------------------------------------------------------------------------------------
procedure EnemyEnsureInSea(var e: TEnemyData);
var
  cs: Single;
  gx, gy, nx, ny: Integer;
  head, tail: Integer;
  qx, qy: array[0..999] of Integer;
  visited: array[0..24, 0..39] of Boolean;
  c, r: Integer;
  found: Boolean;
begin
  if not e.active then Exit;
  if not EnemyCheckCollision(e, e.pixel_x, e.pixel_y) then Exit;

  cs := CELL_SIZE;
  gx := Trunc((e.pixel_x + e.size / 2.0) / cs);
  gy := Trunc((e.pixel_y + e.size / 2.0) / cs);

  // Check if current cell is Sea — snap to it
  if (gx >= 0) and (gx < COLS) and (gy >= 0) and (gy < ROWS) then
    if CellAt(gx, gy) = Sea then
    begin
      EnemySetGridPos(e, gx, gy);
      Exit;
    end;

  // BFS to find nearest Sea cell
  for r := 0 to ROWS - 1 do
    for c := 0 to COLS - 1 do
      visited[r, c] := False;

  head := 0;
  tail := 0;
  if (gx >= 0) and (gx < COLS) and (gy >= 0) and (gy < ROWS) then
  begin
    visited[gy, gx] := True;
    qx[tail] := gx; qy[tail] := gy; Inc(tail);
  end;

  found := False;
  while (head < tail) and not found do
  begin
    gx := qx[head]; gy := qy[head]; Inc(head);

    // 4 neighbors
    for c := 0 to 3 do
    begin
      case c of
        0: begin nx := gx;     ny := gy + 1; end;
        1: begin nx := gx;     ny := gy - 1; end;
        2: begin nx := gx + 1; ny := gy;     end;
        3: begin nx := gx - 1; ny := gy;     end;
      end;
      if (nx >= 0) and (nx < COLS) and (ny >= 0) and (ny < ROWS) then
        if not visited[ny, nx] then
        begin
          visited[ny, nx] := True;
          if CellAt(nx, ny) = Sea then
          begin
            EnemySetGridPos(e, nx, ny);
            found := True;
            break;
          end;
          if tail < 1000 then
          begin
            qx[tail] := nx; qy[tail] := ny; Inc(tail);
          end;
        end;
    end;
  end;
end;

// ------------------------------------------------------------------------------------------------
procedure EnemyEnsureInLand(var e: TEnemyData);
var
  cs: Single;
  gx, gy, nx, ny: Integer;
  head, tail: Integer;
  qx, qy: array[0..999] of Integer;
  visited: array[0..24, 0..39] of Boolean;
  c, r: Integer;
  found: Boolean;
begin
  if not e.active then Exit;
  if not EnemyCheckLandCollision(e, e.pixel_x, e.pixel_y) then Exit;

  cs := CELL_SIZE;
  gx := Trunc((e.pixel_x + e.size / 2.0) / cs);
  gy := Trunc((e.pixel_y + e.size / 2.0) / cs);

  if (gx >= 0) and (gx < COLS) and (gy >= 0) and (gy < ROWS) then
    if CellAt(gx, gy) = Land then
    begin
      EnemySetGridPos(e, gx, gy);
      Exit;
    end;

  for r := 0 to ROWS - 1 do
    for c := 0 to COLS - 1 do
      visited[r, c] := False;

  head := 0;
  tail := 0;
  if (gx >= 0) and (gx < COLS) and (gy >= 0) and (gy < ROWS) then
  begin
    visited[gy, gx] := True;
    qx[tail] := gx; qy[tail] := gy; Inc(tail);
  end;

  found := False;
  while (head < tail) and not found do
  begin
    gx := qx[head]; gy := qy[head]; Inc(head);
    for c := 0 to 3 do
    begin
      case c of
        0: begin nx := gx;     ny := gy + 1; end;
        1: begin nx := gx;     ny := gy - 1; end;
        2: begin nx := gx + 1; ny := gy;     end;
        3: begin nx := gx - 1; ny := gy;     end;
      end;
      if (nx >= 0) and (nx < COLS) and (ny >= 0) and (ny < ROWS) then
        if not visited[ny, nx] then
        begin
          visited[ny, nx] := True;
          if CellAt(nx, ny) = Land then
          begin
            EnemySetGridPos(e, nx, ny);
            found := True;
            break;
          end;
          if tail < 1000 then
          begin
            qx[tail] := nx; qy[tail] := ny; Inc(tail);
          end;
        end;
    end;
  end;
end;

// ------------------------------------------------------------------------------------------------
function EnemyThreatensPlayer(e: TEnemyData): Boolean;
var
  cs: Single;
  i, gx, gy: Integer;
  ptsX: array[0..3] of Single;
  ptsY: array[0..3] of Single;
begin
  if not e.active then Exit(False);
  cs := CELL_SIZE;

  // Check if any corner of the enemy is on a Trail cell
  ptsX[0] := e.pixel_x;             ptsY[0] := e.pixel_y;
  ptsX[1] := e.pixel_x + e.size;    ptsY[1] := e.pixel_y;
  ptsX[2] := e.pixel_x;             ptsY[2] := e.pixel_y + e.size;
  ptsX[3] := e.pixel_x + e.size;    ptsY[3] := e.pixel_y + e.size;
  for i := 0 to 3 do
  begin
    gx := Trunc(ptsX[i] / cs);
    gy := Trunc(ptsY[i] / cs);
    if (gx >= 0) and (gx < COLS) and (gy >= 0) and (gy < ROWS) then
      if grid[gy, gx] = Trail then
        Exit(True);
  end;

  // Check circle collision with player
  ptsX[0] := cs * player.col + cs / 2.0;
  ptsY[0] := cs * player.row + cs / 2.0;
  gx := Trunc(e.pixel_x + e.size / 2.0);
  gy := Trunc(e.pixel_y + e.size / 2.0);
  if Sqrt((gx - ptsX[0]) * (gx - ptsX[0]) + (gy - ptsY[0]) * (gy - ptsY[0])) < (e.size / 2.0 + cs / 2.0) then
    Exit(True);

  EnemyThreatensPlayer := False;
end;

// ------------------------------------------------------------------------------------------------
procedure UpdateEnemy(var e: TEnemyData; dtMs: Single);
var
  dt: Single;
  cs: Single;
  nextX, nextY: Single;
  maxX, maxY: Single;
begin
  if not e.active then Exit;
  dt := dtMs / 1000.0;
  cs := CELL_SIZE;

  EnemyEnsureInSea(e);

  // Move X
  nextX := e.pixel_x + e.vel_x * dt;
  if EnemyCheckCollision(e, nextX, e.pixel_y) then
    e.vel_x := -e.vel_x
  else
    e.pixel_x := nextX;

  // Move Y
  nextY := e.pixel_y + e.vel_y * dt;
  if EnemyCheckCollision(e, e.pixel_x, nextY) then
    e.vel_y := -e.vel_y
  else
    e.pixel_y := nextY;

  // Wall clamp
  maxX := WIDTH;
  maxY := HEIGHT;
  if e.pixel_x <= 0 then begin e.pixel_x := 0; e.vel_x := -e.vel_x; end;
  if e.pixel_x + e.size >= maxX then begin e.pixel_x := maxX - e.size; e.vel_x := -e.vel_x; end;
  if e.pixel_y <= 0 then begin e.pixel_y := 0; e.vel_y := -e.vel_y; end;
  if e.pixel_y + e.size >= maxY then begin e.pixel_y := maxY - e.size; e.vel_y := -e.vel_y; end;
end;

// ------------------------------------------------------------------------------------------------
procedure UpdateLandEnemy(var e: TEnemyData; dtMs: Single);
var
  dt: Single;
  cs: Single;
  nextX, nextY: Single;
  maxX, maxY: Single;
  cx, cy, px, py, p_cx, p_cy, self_cx, self_cy: Single;
  dx, dy, dist: Single;
begin
  if not e.active then Exit;
  dt := dtMs / 1000.0;
  cs := CELL_SIZE;

  EnemyEnsureInLand(e);

  // Move X with player-chasing
  nextX := e.pixel_x + e.vel_x * dt;
  if EnemyCheckLandCollision(e, nextX, e.pixel_y) then
  begin
    p_cx := cs * player.col + cs / 2.0;
    self_cx := e.pixel_x + e.size / 2.0;
    if p_cx > self_cx then e.vel_x := Abs(e.vel_x) else e.vel_x := -Abs(e.vel_x);
    nextX := e.pixel_x + e.vel_x * dt;
    if EnemyCheckLandCollision(e, nextX, e.pixel_y) then
      e.vel_x := -e.vel_x
    else
      e.pixel_x := nextX;
  end
  else
    e.pixel_x := nextX;

  // Move Y with player-chasing
  nextY := e.pixel_y + e.vel_y * dt;
  if EnemyCheckLandCollision(e, e.pixel_x, nextY) then
  begin
    p_cy := cs * player.row + cs / 2.0;
    self_cy := e.pixel_y + e.size / 2.0;
    if p_cy > self_cy then e.vel_y := Abs(e.vel_y) else e.vel_y := -Abs(e.vel_y);
    nextY := e.pixel_y + e.vel_y * dt;
    if EnemyCheckLandCollision(e, e.pixel_x, nextY) then
      e.vel_y := -e.vel_y
    else
      e.pixel_y := nextY;
  end
  else
    e.pixel_y := nextY;

  // Wall clamp
  maxX := WIDTH;
  maxY := HEIGHT;
  if e.pixel_x <= 0 then begin e.pixel_x := 0; e.vel_x := -e.vel_x; end;
  if e.pixel_x + e.size >= maxX then begin e.pixel_x := maxX - e.size; e.vel_x := -e.vel_x; end;
  if e.pixel_y <= 0 then begin e.pixel_y := 0; e.vel_y := -e.vel_y; end;
  if e.pixel_y + e.size >= maxY then begin e.pixel_y := maxY - e.size; e.vel_y := -e.vel_y; end;

  // Player collision
  cx := e.pixel_x + e.size / 2.0;
  cy := e.pixel_y + e.size / 2.0;
  px := cs * player.col + cs / 2.0;
  py := cs * player.row + cs / 2.0;
  dx := cx - px;
  dy := cy - py;
  dist := Sqrt(dx * dx + dy * dy);
  if dist < (e.size / 2.0 + cs / 2.0) then
  begin
    // Player died
  end;
end;

// ------------------------------------------------------------------------------------------------
procedure InitLevel;
var
  e, ex, ey: Integer;
  found: Boolean;
  attempts: Integer;
begin
  ResetGrid;
  player.col := COLS div 2;
  player.row := 0;
  player.dx := 0;
  player.dy := 0;
  player.moveTimer := 0;
  player.moveInterval := 80.0;

  // Spawn enemies based on level
  enemyCount := 0;
  for e := 0 to MAX_ENEMIES - 1 do
  begin
    if e >= level then break;
    found := False;
    attempts := 0;
    while (not found) and (attempts < 200) do
    begin
      ex := RngInt(COLS - 4) + 2;
      ey := RngInt(ROWS - 4) + 2;
      if CellAt(ex, ey) = Sea then found := True;
      Inc(attempts);
    end;
    if found then
    begin
      enemies[e].pixel_x := ex * CELL_SIZE;
      enemies[e].pixel_y := ey * CELL_SIZE;
      enemies[e].vel_x := 100.0;
      enemies[e].vel_y := 100.0;
      enemies[e].size := CELL_SIZE - 8;
      enemies[e].active := True;
      Inc(enemyCount);
    end;
  end;

  // From level 3, spawn land enemy
  landEnemy.active := False;
  if level >= 3 then
  begin
    landEnemy.active := True;
    ex := COLS div 2;
    ey := ROWS - 1;
    landEnemy.pixel_x := ex * CELL_SIZE;
    landEnemy.pixel_y := ey * CELL_SIZE;
    landEnemy.vel_x := 125.0;
    landEnemy.vel_y := 125.0;
    landEnemy.size := CELL_SIZE - 8;
  end;
end;

// ------------------------------------------------------------------------------------------------
procedure GameStart;
begin
  score := 0;
  level := 1;
  lives := 3;
  gameStatus := Playing;
  levelUpTimer := 0;
  InitLevel;
end;

// ------------------------------------------------------------------------------------------------
procedure GamePlayerDied;
begin
  if (lives <= 0) or (gameStatus <> Playing) then Exit;
  Dec(lives);
  if lives <= 0 then
    gameStatus := GameOver
  else
  begin
    player.col := COLS div 2;
    player.row := 0;
    player.dx := 0;
    player.dy := 0;
    player.moveTimer := 0;
    ClearTrail;
  end;
end;

// ------------------------------------------------------------------------------------------------
function CheckCapture: Integer;
var
  e, c, r: Integer;
  safeSet: array[0..24, 0..39] of Boolean;
  cs: Single;
  ex, ey: Integer;
  captured: Integer;

  procedure FloodFillFrom(sx, sy: Integer);
  var
    stack: array[0..999] of TStackPos;
    stackTop: Integer;
    nx, ny: Integer;
  begin
    if (sx < 0) or (sx >= COLS) or (sy < 0) or (sy >= ROWS) then Exit;
    if grid[sy, sx] <> Sea then Exit;
    if safeSet[sy, sx] then Exit;
    stackTop := 0;
    stack[0].col := sx; stack[0].row := sy;
    safeSet[sy, sx] := True;
    while stackTop >= 0 do
    begin
      nx := stack[stackTop].col; ny := stack[stackTop].row;
      Dec(stackTop);
      if (nx + 1 < COLS) and (grid[ny, nx + 1] = Sea) and not safeSet[ny, nx + 1] then
      begin safeSet[ny, nx + 1] := True; Inc(stackTop); stack[stackTop].col := nx + 1; stack[stackTop].row := ny; end;
      if (nx - 1 >= 0) and (grid[ny, nx - 1] = Sea) and not safeSet[ny, nx - 1] then
      begin safeSet[ny, nx - 1] := True; Inc(stackTop); stack[stackTop].col := nx - 1; stack[stackTop].row := ny; end;
      if (ny + 1 < ROWS) and (grid[ny + 1, nx] = Sea) and not safeSet[ny + 1, nx] then
      begin safeSet[ny + 1, nx] := True; Inc(stackTop); stack[stackTop].col := nx; stack[stackTop].row := ny + 1; end;
      if (ny - 1 >= 0) and (grid[ny - 1, nx] = Sea) and not safeSet[ny - 1, nx] then
      begin safeSet[ny - 1, nx] := True; Inc(stackTop); stack[stackTop].col := nx; stack[stackTop].row := ny - 1; end;
    end;
  end;

begin
  FillChar(safeSet, SizeOf(safeSet), 0);

  // Mark land cells as safe
  for r := 0 to ROWS - 1 do
    for c := 0 to COLS - 1 do
      if grid[r, c] = Land then
        safeSet[r, c] := True;

  // Flood fill from each enemy position
  cs := CELL_SIZE;
  for e := 0 to enemyCount - 1 do
  begin
    if not enemies[e].active then Continue;
    ex := Trunc((enemies[e].pixel_x + enemies[e].size / 2.0) / cs);
    ey := Trunc((enemies[e].pixel_y + enemies[e].size / 2.0) / cs);
    FloodFillFrom(ex, ey);
  end;

  // Convert Trail → Land, capture unreachable Sea → Land
  captured := 0;
  for r := 0 to ROWS - 1 do
    for c := 0 to COLS - 1 do
    begin
      if grid[r, c] = Trail then
        grid[r, c] := Land
      else if (grid[r, c] = Sea) and not safeSet[r, c] then
      begin
        grid[r, c] := Land;
        Inc(captured);
      end;
    end;

  CheckCapture := captured;
end;

// ------------------------------------------------------------------------------------------------
procedure SetPlayerDirection(dx, dy: Integer);
begin
  // Prevent 180-degree reversal (Zig logic)
  if (player.dx = -dx) and (player.dy = -dy) and ((dx <> 0) or (dy <> 0)) then
    Exit;
  player.dx := dx;
  player.dy := dy;
end;

// ------------------------------------------------------------------------------------------------
function UpdatePlayer(dtMs: Single): Boolean;
var
  nextX, nextY: Integer;
  nextCell, prevCell: TCell;
  captured: Integer;
begin
  UpdatePlayer := False;
  if (player.dx = 0) and (player.dy = 0) then Exit;
  if gameStatus <> Playing then Exit;

  player.moveTimer := player.moveTimer + dtMs;
  if player.moveTimer < player.moveInterval then Exit;
  player.moveTimer := 0;

  nextX := player.col + player.dx;
  nextY := player.row + player.dy;

  if (nextX < 0) or (nextX >= COLS) or (nextY < 0) or (nextY >= ROWS) then
  begin
    player.dx := 0;
    player.dy := 0;
    Exit;
  end;

  nextCell := grid[nextY, nextX];
  prevCell := grid[player.row, player.col];

  if nextCell = Trail then
  begin
    UpdatePlayer := True; // Died
    Exit;
  end;

  player.col := nextX;
  player.row := nextY;

  if nextCell = Sea then
  begin
    grid[nextY, nextX] := Trail;
  end
  else if nextCell = Land then
  begin
    if prevCell = Trail then
    begin
      captured := CheckCapture;
      if captured > 0 then
        score := score + captured;
      player.dx := 0;
      player.dy := 0;
      if GetPercentCaptured >= 85 then
      begin
        gameStatus := LevelUpDelay;
        levelUpTimer := 2000.0;
      end;
    end;
  end;
end;

// ------------------------------------------------------------------------------------------------
procedure DrawPixel(col, row: Integer; colour: Cardinal);
var
  px: PByte;
  ch: Integer;
begin
  px := canvasPixels + (row * canvasWidth + col) * 4;
  for ch := 0 to 3 do
    px[ch] := Byte(colour shr (ch * 8));
end;

// ------------------------------------------------------------------------------------------------
procedure DrawFilledRect(c1, r1, c2, r2: Integer; colour: Cardinal);
var
  c, r: Integer;
  px: PByte;
  ch: Integer;
begin
  for r := r1 to r2 do
    for c := c1 to c2 do
    begin
      px := canvasPixels + (r * canvasWidth + c) * 4;
      for ch := 0 to 3 do
        px[ch] := Byte(colour shr (ch * 8));
    end;
end;

// ------------------------------------------------------------------------------------------------
procedure DrawPlayer;
var
  px, py: Integer;
begin
  px := CellToPixelX(player.col);
  py := CellToPixelY(player.row);
  DrawFilledRect(px, py, px + CELL_SIZE - 1, py + CELL_SIZE - 1, COL_PLAYER);
end;

// ------------------------------------------------------------------------------------------------
procedure DrawEnemyCircle(e: TEnemyData; colour: Cardinal);
var
  cx, cy, r: Integer;
  i, j: Integer;
  px: PByte;
  ch: Integer;
begin
  if not e.active then Exit;
  cx := Trunc(e.pixel_x + e.size / 2.0);
  cy := Trunc(e.pixel_y + e.size / 2.0);
  r := Trunc(e.size / 2.0);
  for i := -r to r do
    for j := -r to r do
    begin
      if (i * i + j * j) <= (r * r) then
      begin
        px := canvasPixels + ((cy + j) * canvasWidth + (cx + i)) * 4;
        for ch := 0 to 3 do
          px[ch] := Byte(colour shr (ch * 8));
      end;
    end;
end;

// ------------------------------------------------------------------------------------------------
procedure Render;
var
  c, r: Integer;
  e: Integer;
begin
  if not canvasInitialized then Exit;

  // Clear background
  DrawFilledRect(0, 0, canvasWidth - 1, canvasHeight - 1, COL_BG);

  // Draw grid cells
  for r := 0 to ROWS - 1 do
    for c := 0 to COLS - 1 do
    begin
      case grid[r, c] of
        Land:
          DrawFilledRect(c * CELL_SIZE, r * CELL_SIZE, (c + 1) * CELL_SIZE - 1, (r + 1) * CELL_SIZE - 1, COL_LAND);
        Trail:
          DrawFilledRect(c * CELL_SIZE, r * CELL_SIZE, (c + 1) * CELL_SIZE - 1, (r + 1) * CELL_SIZE - 1, COL_TRAIL);
        else
          ; // Sea is background colour
      end;
    end;

  // Draw player (filled rectangle, like Zig)
  DrawPlayer;

  // Draw enemies (filled circles, pixel-based pos)
  for e := 0 to enemyCount - 1 do
    DrawEnemyCircle(enemies[e], COL_ENEMY);

  // Draw land enemy
  DrawEnemyCircle(landEnemy, COL_LAND_ENEMY);
end;

// ------------------------------------------------------------------------------------------------
procedure CanvasInit(w, h: Integer; pixels: PByte; parent_id: PAnsiChar);
begin
  canvasWidth := w;
  canvasHeight := h;
  canvasPixels := pixels;
  canvasInitialized := True;
end;

// ------------------------------------------------------------------------------------------------
procedure GameUpdate(dtMs: Single);
var
  i: Integer;
begin
  // Clamp dt
  if dtMs > 50.0 then dtMs := 50.0;

  // Handle level-up delay
  if gameStatus = LevelUpDelay then
  begin
    levelUpTimer := levelUpTimer - dtMs;
    if levelUpTimer <= 0 then
    begin
      Inc(level);
      if (level mod 5) = 0 then
      begin
        if lives < 5 then Inc(lives);
      end;
      gameStatus := Playing;
      InitLevel;
    end;
    Exit;
  end;

  if gameStatus <> Playing then Exit;

  // Update player (timed movement)
  if UpdatePlayer(dtMs) then
  begin
    GamePlayerDied;
    Exit;
  end;

  // Update enemies
  for i := 0 to enemyCount - 1 do
    UpdateEnemy(enemies[i], dtMs);

  // Update land enemy
  if landEnemy.active then
    UpdateLandEnemy(landEnemy, dtMs);

  // Check enemy threat (trail or player collision)
  for i := 0 to enemyCount - 1 do
  begin
    if EnemyThreatensPlayer(enemies[i]) then
    begin
      GamePlayerDied;
      Exit;
    end;
  end;
  if landEnemy.active then
    if EnemyThreatensPlayer(landEnemy) then
    begin
      GamePlayerDied;
      Exit;
    end;
end;

// ------------------------------------------------------------------------------------------------
procedure init;
begin
  rngState := 1;
  gameStatus := StartScreen;
  level := 1;
  score := 0;
  lives := 3;
  levelUpTimer := 0;
  landEnemy.active := False;
end;

// ------------------------------------------------------------------------------------------------
procedure on_key_down(keyCode: Integer);
begin
  case keyCode of
    37: SetPlayerDirection(-1, 0);  // Left
    38: SetPlayerDirection(0, -1);  // Up
    39: SetPlayerDirection(1, 0);   // Right
    40: SetPlayerDirection(0, 1);   // Down
  end;
end;

// ------------------------------------------------------------------------------------------------
procedure on_start;
begin
  GameStart;
end;

// ------------------------------------------------------------------------------------------------
function step(dt: Single): Integer;
begin
  GameUpdate(dt * 1000.0);  // Convert seconds to ms
  step := 1;  // Keep running
end;

// ------------------------------------------------------------------------------------------------
function get_score: Integer;
begin
  get_score := score;
end;

// ------------------------------------------------------------------------------------------------
function get_lives: Integer;
begin
  get_lives := lives;
end;

// ------------------------------------------------------------------------------------------------
function get_level: Integer;
begin
  get_level := level;
end;

// ------------------------------------------------------------------------------------------------
function get_game_status: Integer;
begin
  get_game_status := Ord(gameStatus);
end;

// ------------------------------------------------------------------------------------------------
function get_percent_captured: Integer;
begin
  get_percent_captured := GetPercentCaptured;
end;

// ------------------------------------------------------------------------------------------------
function get_pixels: PByte;
begin
  get_pixels := canvasPixels;
end;

// ------------------------------------------------------------------------------------------------
function get_width: Integer;
begin
  get_width := WIDTH;
end;

// ------------------------------------------------------------------------------------------------
function get_height: Integer;
begin
  get_height := HEIGHT;
end;

// ------------------------------------------------------------------------------------------------
exports
  init            name 'init',
  on_key_down     name 'on_key_down',
  on_start        name 'on_start',
  step            name 'step',
  get_score       name 'get_score',
  get_lives       name 'get_lives',
  get_level       name 'get_level',
  get_game_status name 'get_game_status',
  get_pixels      name 'get_pixels',
  get_width       name 'get_width',
  get_height      name 'get_height',
  get_percent_captured name 'get_percent_captured',
  CanvasInit      name 'CanvasInit',
  render          name 'render';

// ================================================================================================
begin
end.
