// basic_canvas — Synthwave grid + bouncing balls in C, compiled to WASM with Zig.
// All drawing happens in a linear RGBA pixel buffer. JS blits it to a <canvas>.
//
// Truly freestanding: no libc headers, no math library. Only compiler builtins.

// ---------------------------------------------------------------------------
// Freestanding type definitions (no <stdint.h>)
// ---------------------------------------------------------------------------
typedef unsigned char  uint8_t;
typedef unsigned short uint16_t;
typedef unsigned int   uint32_t;
typedef signed int     int32_t;

#define NULL ((void*)0)

// ---------------------------------------------------------------------------
// Minimal freestanding stubs
// ---------------------------------------------------------------------------
static void* fmemset(void* s, int c, uint32_t n) {
    uint8_t* p = (uint8_t*)s;
    for (uint32_t i = 0; i < n; i++) p[i] = (uint8_t)c;
    return s;
}

static int fabs(int x) {
    return x < 0 ? -x : x;
}

// ---------------------------------------------------------------------------
// Canvas dimensions
// ---------------------------------------------------------------------------
#define WIDTH  800
#define HEIGHT 600
#define BUF_SIZE (WIDTH * HEIGHT * 4)

// ---------------------------------------------------------------------------
// Pixel buffer — lives in WASM linear memory, visible to JS via pointer.
// ---------------------------------------------------------------------------
static uint8_t pixels[BUF_SIZE];

// ---------------------------------------------------------------------------
// Ball physics (matching godom's vibe)
// ---------------------------------------------------------------------------
#define MAX_BALLS 24

typedef struct {
    float x, y;
    float vx, vy;
    float radius;
    uint8_t r, g, b;
    uint8_t alive;
} Ball;

static Ball balls[MAX_BALLS];
static int   ball_count = 0;

// ---------------------------------------------------------------------------
// Grid / synthwave state
// ---------------------------------------------------------------------------
static float grid_offset  = 0.0f;
static float grid_speed   = 60.0f;   // pixels per second
static int   grid_spacing = 44;

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
    return (float)(rng_next() & 0xFFFFFF) / (float)(0xFFFFFF + 1);
}

// ---------------------------------------------------------------------------
// Precomputed sine table for ray angles (avoids <math.h>)
// 128 entries covering 0..2π
// ---------------------------------------------------------------------------
#define SIN_TABLE_SIZE 128
static float sin_table[SIN_TABLE_SIZE];

static void build_sin_table(void) {
    // Taylor series for sin: x - x³/6 + x⁵/120
    for (int i = 0; i < SIN_TABLE_SIZE; i++) {
        float t = (float)i * 6.283185307f / (float)SIN_TABLE_SIZE;  // 2π * i/N
        float t2 = t * t;
        float t3 = t2 * t;
        float t5 = t3 * t2;
        sin_table[i] = t - t3 / 6.0f + t5 / 120.0f;
    }
}

static float fsin(float x) {
    // Normalize x to [0, 2π)
    float two_pi = 6.283185307f;
    while (x < 0.0f) x += two_pi;
    while (x >= two_pi) x -= two_pi;
    float idx_f = x * (float)SIN_TABLE_SIZE / two_pi;
    int idx = (int)idx_f;
    if (idx >= SIN_TABLE_SIZE - 1) idx = SIN_TABLE_SIZE - 2;
    float frac = idx_f - (float)idx;
    return sin_table[idx] * (1.0f - frac) + sin_table[idx + 1] * frac;
}

static float fcos(float x) {
    return fsin(x + 1.570796327f);  // cos(x) = sin(x + π/2)
}

// ---------------------------------------------------------------------------
// Pixel helpers
// ---------------------------------------------------------------------------
static inline void set_pixel(int x, int y,
                             uint8_t r, uint8_t g, uint8_t b, uint8_t a) {
    if ((uint32_t)x >= WIDTH || (uint32_t)y >= HEIGHT) return;
    int idx = (y * WIDTH + x) * 4;
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

// ---------------------------------------------------------------------------
// Drawing primitives
// ---------------------------------------------------------------------------

static void clear_screen(uint8_t r, uint8_t g, uint8_t b) {
    for (int y = 0; y < HEIGHT; y++) {
        int row = y * WIDTH * 4;
        for (int x = 0; x < WIDTH; x++) {
            int idx = row + x * 4;
            pixels[idx + 0] = r;
            pixels[idx + 1] = g;
            pixels[idx + 2] = b;
            pixels[idx + 3] = 255;
        }
    }
}

// Bresenham line
static void draw_line(int x1, int y1, int x2, int y2,
                      uint8_t r, uint8_t g, uint8_t b) {
    int dx  = fabs(x2 - x1);
    int dy  = -fabs(y2 - y1);
    int sx  = x1 < x2 ? 1 : -1;
    int sy  = y1 < y2 ? 1 : -1;
    int err = dx + dy;

    for (;;) {
        set_pixel(x1, y1, r, g, b, 255);
        if (x1 == x2 && y1 == y2) break;
        int e2 = 2 * err;
        if (e2 >= dy) { err += dy; x1 += sx; }
        if (e2 <= dx) { err += dx; y1 += sy; }
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
static void draw_filled_circle(int cx, int cy, int radius,
                               uint8_t r, uint8_t g, uint8_t b) {
    int x  = radius;
    int y  = 0;
    int dp = 1 - radius;

    while (x >= y) {
        for (int px = cx - x; px <= cx + x; px++) set_pixel(px, cy + y, r, g, b, 255);
        for (int px = cx - x; px <= cx + x; px++) set_pixel(px, cy - y, r, g, b, 255);
        for (int px = cx - y; px <= cx + y; px++) set_pixel(px, cy + x, r, g, b, 255);
        for (int px = cx - y; px <= cx + y; px++) set_pixel(px, cy - x, r, g, b, 255);
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
// Synthwave grid — perspective lines converging at a vanishing point
// ---------------------------------------------------------------------------
static void draw_grid(float offset) {
    int vx = WIDTH / 2;
    int vy = HEIGHT - 40;

    uint8_t gr = 0, gg = 230, gb = 247;  // cyan base

    // Horizontal lines — closer together near the horizon (quadratic spacing)
    int num_h = 28;
    for (int i = 0; i < num_h; i++) {
        float t    = (float)i / (float)(num_h - 1);
        float yf   = 20.0f + t * t * (float)(vy - 20);
        int   y    = (int)(yf + offset);
        uint8_t alpha = (uint8_t)(40 + (1.0f - t) * 180);
        for (int x = 0; x < WIDTH; x++) {
            set_pixel(x, y, gr, gg, gb, alpha);
        }
    }

    // Vertical rays from vanishing point outward (precomputed angles)
    int num_rays = 38;
    float angle_start = -3.14159f * 0.42f;
    float angle_range = 3.14159f * 0.84f;
    for (int i = 0; i < num_rays; i++) {
        float angle = angle_start + (float)i * angle_range / (float)(num_rays - 1);
        uint8_t alpha = (uint8_t)(30 + (rng_next() % 40));
        int dx = (int)(fcos(angle) * 1200.0f);
        int dy = (int)(-fsin(angle) * 500.0f);
        int ex = vx + dx;
        int ey = vy + dy;
        if (ey < 0) ey = 0;
        draw_line(vx, vy, ex, ey, gr, gg, gb);
    }
}

// Neon sun near the horizon
static void draw_sun(float offset) {
    int sx = WIDTH / 2;
    int sy = HEIGHT - 80 + (int)(offset * 0.3f);
    if (sy < HEIGHT - 160) sy = HEIGHT - 160;

    draw_filled_circle(sx, sy, 70, 255, 80, 0);
    draw_filled_circle(sx, sy, 50, 255, 140, 20);
    draw_filled_circle(sx, sy, 34, 255, 200, 80);

    // Cut off bottom half (sun below horizon)
    int cut_y = sy + 34;
    for (int y = cut_y; y < HEIGHT; y++) {
        for (int x = 0; x < WIDTH; x++) {
            int idx = (y * WIDTH + x) * 4;
            pixels[idx + 0] = 10;
            pixels[idx + 1] = 5;
            pixels[idx + 2] = 20;
            pixels[idx + 3] = 255;
        }
    }

    // Horizon line
    int hy = sy + 34;
    for (int x = 0; x < WIDTH; x++) {
        set_pixel(x, hy, 255, 50, 180, 200);
    }
}

// ---------------------------------------------------------------------------
// Ball management
// ---------------------------------------------------------------------------
static void spawn_ball(float x, float y) {
    if (ball_count >= MAX_BALLS) {
        for (int i = 0; i < MAX_BALLS - 1; i++) {
            balls[i] = balls[i + 1];
        }
        ball_count = MAX_BALLS - 1;
    }

    Ball* b = &balls[ball_count++];
    b->x      = x;
    b->y      = y;
    b->vx     = (rng_float() - 0.5f) * 300.0f;
    b->vy     = (rng_float() - 0.5f) * 300.0f;
    b->radius = 10.0f + rng_float() * 20.0f;

    // Neon colours
    int pick = (int)(rng_next() % 6);
    switch (pick) {
        case 0: b->r = 0;   b->g = 240; b->b = 220; break;
        case 1: b->r = 255; b->g = 0;   b->b = 180; break;
        case 2: b->r = 255; b->g = 230; b->b = 0;   break;
        case 3: b->r = 255; b->g = 100; b->b = 0;   break;
        case 4: b->r = 160; b->g = 0;   b->b = 255; break;
        case 5: b->r = 0;   b->g = 255; b->b = 100; break;
    }
    b->alive = 1;
}

static void update_balls(float dt) {
    for (int i = 0; i < ball_count; i++) {
        Ball* b = &balls[i];
        if (!b->alive) continue;

        b->x += b->vx * dt;
        b->y += b->vy * dt;

        if (b->x - b->radius < 0)      { b->x = b->radius;        b->vx = -b->vx; }
        if (b->x + b->radius > WIDTH)  { b->x = WIDTH - b->radius; b->vx = -b->vx; }
        if (b->y - b->radius < 0)      { b->y = b->radius;         b->vy = -b->vy; }
        if (b->y + b->radius > HEIGHT) { b->y = HEIGHT - b->radius; b->vy = -b->vy; }
    }
}

static void draw_balls(void) {
    for (int i = 0; i < ball_count; i++) {
        Ball* b = &balls[i];
        if (!b->alive) continue;
        int r = (int)b->radius;
        draw_filled_circle((int)b->x, (int)b->y, r, b->r, b->g, b->b);
        draw_circle((int)b->x, (int)b->y, r, 255, 255, 255);
    }
}

// ---------------------------------------------------------------------------
// Exported API — called from JavaScript
// ---------------------------------------------------------------------------

__attribute__((export_name("wasm_init")))
void wasm_init(void) {
    build_sin_table();
    fmemset(pixels, 0, BUF_SIZE);
    ball_count = 0;

    for (int i = 0; i < 6; i++) {
        spawn_ball(100.0f + rng_float() * 600.0f,
                   80.0f + rng_float() * 300.0f);
    }
}

__attribute__((export_name("wasm_update")))
void wasm_update(float dt) {
    if (dt > 0.1f) dt = 0.1f;
    if (dt <= 0.0f) dt = 0.016f;

    grid_offset += grid_speed * dt;
    if (grid_offset > (float)grid_spacing) {
        grid_offset -= (float)grid_spacing;
    }

    clear_screen(10, 5, 20);
    draw_grid(grid_offset);
    draw_sun(grid_offset);
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
