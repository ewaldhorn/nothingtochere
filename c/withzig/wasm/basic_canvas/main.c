// basic_canvas — Bouncing balls with collision in C, compiled to WASM with Zig.
// All drawing happens in a linear RGBA pixel buffer. JS blits it to a <canvas>.
//
// Truly freestanding: no libc headers, no math library. Only compiler builtins.

// ---------------------------------------------------------------------------
// Freestanding type definitions (no <stdint.h>)
// ---------------------------------------------------------------------------
typedef unsigned char  uint8_t;
typedef unsigned short uint16_t;
typedef unsigned int   uint32_t;

// ---------------------------------------------------------------------------
// Minimal freestanding stubs
// ---------------------------------------------------------------------------
static void* fmemset(void* s, int c, uint32_t n) {
    uint8_t* p = (uint8_t*)s;
    for (uint32_t i = 0; i < n; i++) p[i] = (uint8_t)c;
    return s;
}

// Compiler builtin maps to a single f32.sqrt WASM opcode — far faster than Newton's method.
static inline float fsqrt(float x) {
    return __builtin_sqrtf(x);
}

// ---------------------------------------------------------------------------
// Canvas dimensions
// ---------------------------------------------------------------------------
#define WIDTH  800
#define HEIGHT 600
#define BUF_SIZE (WIDTH * HEIGHT * 4)

// ---------------------------------------------------------------------------
// Pixel buffer — allocated at runtime from WASM memory, not embedded in binary.
// This avoids bloating the .wasm file with 1.9MB of zero bytes.
// ---------------------------------------------------------------------------
static uint8_t* pixels;

// ---------------------------------------------------------------------------
// Ball physics
// ---------------------------------------------------------------------------
#define MAX_BALLS 256
// MAX_BALLS must be a power of two — the ring-buffer uses (& MAX_BALLS-1) instead of (% MAX_BALLS).
_Static_assert((MAX_BALLS & (MAX_BALLS - 1)) == 0, "MAX_BALLS must be a power of two");

typedef struct {
    float x, y;
    float vx, vy;
    float radius;
    uint8_t r, g, b;
} Ball;

static Ball balls[MAX_BALLS];
static int   ball_count = 0;  // number of active balls (0..MAX_BALLS)
static int   ball_head  = 0;  // ring-buffer index of the oldest ball

// ---------------------------------------------------------------------------
// PRNG — xorshift32 (deterministic, fast, no libc needed)
// ---------------------------------------------------------------------------
static uint32_t rng_state = 0xDEADBEEF;

static uint32_t rng_next(void) {
    rng_state ^= rng_state << 13;
    rng_state ^= rng_state >> 17;
    rng_state ^= rng_state << 5;
    return rng_state;
}

static float rng_float(void) {
    // Shift to 24 bits; divide by 2^24 for a uniform [0, 1) float.
    return (float)(rng_next() >> 8) / 16777216.0f;
}

// ---------------------------------------------------------------------------
// Pixel helpers
// ---------------------------------------------------------------------------
static inline void set_pixel(int x, int y,
                             uint8_t r, uint8_t g, uint8_t b, uint8_t a) {
    if ((uint32_t)x >= WIDTH || (uint32_t)y >= HEIGHT) return;
    uint32_t idx = ((uint32_t)y * WIDTH + (uint32_t)x) * 4u;
    if (a == 255) {
        pixels[idx + 0] = r;
        pixels[idx + 1] = g;
        pixels[idx + 2] = b;
        pixels[idx + 3] = 255;
    } else {
        uint8_t inv = 255 - a;
        pixels[idx + 0] = (uint8_t)(((uint16_t)r * a + (uint16_t)pixels[idx + 0] * inv) / 255);
        pixels[idx + 1] = (uint8_t)(((uint16_t)g * a + (uint16_t)pixels[idx + 1] * inv) / 255);
        pixels[idx + 2] = (uint8_t)(((uint16_t)b * a + (uint16_t)pixels[idx + 2] * inv) / 255);
        pixels[idx + 3] = 255;
    }
}

// Unchecked write — caller guarantees 0 <= x < WIDTH, 0 <= y < HEIGHT.
static inline void set_pixel_unchecked(int x, int y,
                                        uint8_t r, uint8_t g, uint8_t b) {
    uint32_t idx = ((uint32_t)y * WIDTH + (uint32_t)x) * 4u;
    pixels[idx + 0] = r;
    pixels[idx + 1] = g;
    pixels[idx + 2] = b;
    pixels[idx + 3] = 255;
}

// Fill a horizontal span, clamping x to [0, WIDTH-1] — one bounds check per row, not per pixel.
static inline void fill_scanline(int y, int x0, int x1,
                                  uint8_t r, uint8_t g, uint8_t b) {
    if ((uint32_t)y >= HEIGHT) return;
    if (x0 < 0) x0 = 0;
    if (x1 >= (int)WIDTH) x1 = (int)WIDTH - 1;
    for (int px = x0; px <= x1; px++)
        set_pixel_unchecked(px, y, r, g, b);
}

// ---------------------------------------------------------------------------
// Drawing primitives
// ---------------------------------------------------------------------------

// Fill the entire pixel buffer with a solid colour.
// Writes 32-bit words (RGBA packed) instead of 4 individual bytes per pixel.
// WASM is little-endian, so the in-memory byte order is R, G, B, A.
static void clear_screen(uint8_t r, uint8_t g, uint8_t b) {
    uint32_t color = (uint32_t)r
                   | ((uint32_t)g << 8)
                   | ((uint32_t)b << 16)
                   | (255u << 24);
    uint32_t* p   = (uint32_t*)pixels;
    uint32_t count = BUF_SIZE / 4;
    for (uint32_t i = 0; i < count; i++) {
        p[i] = color;
    }
}

// Midpoint circle (outline)
static void draw_circle(int cx, int cy, int radius,
                        uint8_t r, uint8_t g, uint8_t b) {
    int x  = radius;
    int y  = 0;
    int dp = 1 - radius;

    while (x >= y) {
        set_pixel(cx + x, cy + y, r, g, b, 255);
        set_pixel(cx - x, cy + y, r, g, b, 255);
        set_pixel(cx + x, cy - y, r, g, b, 255);
        set_pixel(cx - x, cy - y, r, g, b, 255);
        set_pixel(cx + y, cy + x, r, g, b, 255);
        set_pixel(cx - y, cy + x, r, g, b, 255);
        set_pixel(cx + y, cy - x, r, g, b, 255);
        set_pixel(cx - y, cy - x, r, g, b, 255);
        y++;
        if (dp <= 0) {
            dp += 2 * y + 1;
        } else {
            x--;
            dp += 2 * (y - x) + 1;
        }
    }
}

// Filled circle
// Uses fill_scanline (clamped, unchecked inner loop) and skips duplicate rows
// at y==0 (top/bottom mirror) and x==y (diagonal octant boundary).
static void draw_filled_circle(int cx, int cy, int radius,
                               uint8_t r, uint8_t g, uint8_t b) {
    int x  = radius;
    int y  = 0;
    int dp = 1 - radius;

    while (x >= y) {
        fill_scanline(cy + y, cx - x, cx + x, r, g, b);
        if (y != 0)
            fill_scanline(cy - y, cx - x, cx + x, r, g, b);
        fill_scanline(cy + x, cx - y, cx + y, r, g, b);
        if (x != y)
            fill_scanline(cy - x, cx - y, cx + y, r, g, b);
        y++;
        if (dp <= 0) {
            dp += 2 * y + 1;
        } else {
            x--;
            dp += 2 * (y - x) + 1;
        }
    }
}

// ---------------------------------------------------------------------------
// Ball management
// ---------------------------------------------------------------------------
static void spawn_ball(float x, float y) {
    int slot;
    if (ball_count < MAX_BALLS) {
        // Ring not full: append at the next free slot.
        slot = (ball_head + ball_count) & (MAX_BALLS - 1);
        ball_count++;
    } else {
        // Ring full: overwrite the oldest ball and advance the head — O(1).
        slot = ball_head;
        ball_head = (ball_head + 1) & (MAX_BALLS - 1);
    }

    Ball* b = &balls[slot];
    // Jitter spawn position so rapid clicks at the same spot don't
    // create perfectly overlapping balls that the collision code skips.
    b->x      = x + (rng_float() - 0.5f) * 12.0f;
    b->y      = y + (rng_float() - 0.5f) * 12.0f;
    b->vx     = (rng_float() - 0.5f) * 300.0f;
    b->vy     = (rng_float() - 0.5f) * 300.0f;
    b->radius = 10.0f + rng_float() * 20.0f;

    // Neon colours
    int pick = (int)(rng_next() % 6);
    switch (pick) {
        case 0: b->r = 0;   b->g = 240; b->b = 220; break; // cyan
        case 1: b->r = 255; b->g = 0;   b->b = 180; break; // hot pink
        case 2: b->r = 255; b->g = 230; b->b = 0;   break; // yellow
        case 3: b->r = 255; b->g = 100; b->b = 0;   break; // orange
        case 4: b->r = 160; b->g = 0;   b->b = 255; break; // purple
        case 5: b->r = 0;   b->g = 255; b->b = 100; break; // green
    }
}

static void update_balls(float dt) {
    // ---- Move all balls ----
    for (int i = 0; i < ball_count; i++) {
        Ball* b = &balls[(ball_head + i) & (MAX_BALLS - 1)];
        b->x += b->vx * dt;
        b->y += b->vy * dt;
    }

    // ---- Wall collisions ----
    for (int i = 0; i < ball_count; i++) {
        Ball* b = &balls[(ball_head + i) & (MAX_BALLS - 1)];

        if (b->x - b->radius < 0)      { b->x = b->radius;          b->vx = -b->vx; }
        if (b->x + b->radius > WIDTH)  { b->x = WIDTH - b->radius;  b->vx = -b->vx; }
        if (b->y - b->radius < 0)      { b->y = b->radius;          b->vy = -b->vy; }
        if (b->y + b->radius > HEIGHT) { b->y = HEIGHT - b->radius; b->vy = -b->vy; }
    }

    // ---- Ball-ball collisions (equal-mass elastic) ----
    for (int i = 0; i < ball_count; i++) {
        Ball* a = &balls[(ball_head + i) & (MAX_BALLS - 1)];

        int idx_b = (ball_head + i + 1) & (MAX_BALLS - 1);

        for (int j = i + 1; j < ball_count; j++) {
            Ball* b = &balls[idx_b];

            float dx = b->x - a->x;
            float dy = b->y - a->y;
            float dist_sq = dx * dx + dy * dy;
            float min_dist = a->radius + b->radius;

            if (dist_sq >= min_dist * min_dist) {
                idx_b = (idx_b + 1) & (MAX_BALLS - 1);
                continue;
            }
            // Safety net: two balls are essentially coincident (dist < 0.01 px).
            // This can't normally be reached after the first frame because min_dist >= 20,
            // but it guards against division-by-zero if balls ever spawn at the same spot.
            if (dist_sq < 0.0001f) {
                a->x -= 0.5f;
                b->x += 0.5f;
                idx_b = (idx_b + 1) & (MAX_BALLS - 1);
                continue;
            }

            float dist = fsqrt(dist_sq);
            float nx = dx / dist;
            float ny = dy / dist;

            // Relative velocity along the collision normal
            float dvx = a->vx - b->vx;
            float dvy = a->vy - b->vy;
            float vn = dvx * nx + dvy * ny;

            // Always separate overlapping balls — fixes balls that spawn already
            // overlapping, which the velocity check alone would never resolve.
            float overlap = min_dist - dist;
            float push = overlap * 0.5f + 0.5f;  // tiny extra nudge
            a->x -= push * nx;
            a->y -= push * ny;
            b->x += push * nx;
            b->y += push * ny;

            // Only swap velocities if balls are approaching each other.
            if (vn > 0.0f) {
                a->vx -= vn * nx;
                a->vy -= vn * ny;
                b->vx += vn * nx;
                b->vy += vn * ny;
            }

            idx_b = (idx_b + 1) & (MAX_BALLS - 1);
        }
    }
}

static void draw_balls(void) {
    for (int i = 0; i < ball_count; i++) {
        Ball* b = &balls[(ball_head + i) & (MAX_BALLS - 1)];
        int r = (int)b->radius;
        if (r > 0) {
            draw_filled_circle((int)b->x, (int)b->y, r, b->r, b->g, b->b);
            draw_circle((int)b->x, (int)b->y, r, 255, 255, 255);
        }
    }
}

// ---------------------------------------------------------------------------
// Exported API — called from JavaScript
// ---------------------------------------------------------------------------

__attribute__((export_name("wasm_init")))
void wasm_init(void) {
    // Place pixel buffer at a fixed offset past static data.
    // 64KB is safely beyond our ~8KB of static data (balls array, etc.).
    // If static data grows significantly, verify the Zig build's --initial-memory
    // and segment layout to ensure no overlap with this fixed offset.
    pixels = (uint8_t*)65536;
    fmemset(pixels, 0, BUF_SIZE);
    ball_count = 0;
    ball_head  = 0;

    // Seed with initial balls spread across the canvas
    for (int i = 0; i < 6; i++) {
        spawn_ball(100.0f + rng_float() * 600.0f,
                   80.0f + rng_float() * 440.0f);
    }
}

__attribute__((export_name("wasm_update")))
void wasm_update(float dt) {
    if (dt > 0.1f)   dt = 0.1f;   // cap: prevents tunnelling on a frozen/slow tab
    if (dt < 0.001f) dt = 0.001f; // floor: also covers zero, negative, and near-zero dt

    // Order matters: clear first so draw_balls() always writes into a fresh frame.
    // If the JS blit is delayed the canvas will briefly show the previous frame —
    // preferable to drawing onto stale pixel data.
    clear_screen(10, 5, 20);

    update_balls(dt);
    draw_balls();
}

__attribute__((export_name("wasm_click")))
void wasm_click(int x, int y) {
    spawn_ball((float)x, (float)y);
}

__attribute__((export_name("wasm_get_pixels")))
uint8_t* wasm_get_pixels(void) {
    return pixels;
}

__attribute__((export_name("wasm_get_width")))
int wasm_get_width(void) {
    return WIDTH;
}

__attribute__((export_name("wasm_get_height")))
int wasm_get_height(void) {
    return HEIGHT;
}
