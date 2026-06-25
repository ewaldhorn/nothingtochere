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

// Newton's method — fast enough for infrequent collision resolution.
static float fsqrt(float x) {
    if (x <= 0.0f) return 0.0f;
    float guess = x;
    for (int i = 0; i < 10; i++) {
        guess = (guess + x / guess) * 0.5f;
    }
    return guess;
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
// Ball physics
// ---------------------------------------------------------------------------
#define MAX_BALLS 100

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
// Ball management
// ---------------------------------------------------------------------------
static void spawn_ball(float x, float y) {
    if (ball_count >= MAX_BALLS) {
        // Recycle oldest ball
        for (int i = 0; i < MAX_BALLS - 1; i++) {
            balls[i] = balls[i + 1];
        }
        ball_count = MAX_BALLS - 1;
    }

    Ball* b = &balls[ball_count++];
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
    b->alive = 1;
}

static void update_balls(float dt) {
    // ---- Move all balls ----
    for (int i = 0; i < ball_count; i++) {
        Ball* b = &balls[i];
        if (!b->alive) continue;
        b->x += b->vx * dt;
        b->y += b->vy * dt;
    }

    // ---- Wall collisions ----
    for (int i = 0; i < ball_count; i++) {
        Ball* b = &balls[i];
        if (!b->alive) continue;

        if (b->x - b->radius < 0)      { b->x = b->radius;          b->vx = -b->vx; }
        if (b->x + b->radius > WIDTH)  { b->x = WIDTH - b->radius;  b->vx = -b->vx; }
        if (b->y - b->radius < 0)      { b->y = b->radius;          b->vy = -b->vy; }
        if (b->y + b->radius > HEIGHT) { b->y = HEIGHT - b->radius; b->vy = -b->vy; }
    }

    // ---- Ball-ball collisions (equal-mass elastic) ----
    for (int i = 0; i < ball_count; i++) {
        Ball* a = &balls[i];
        if (!a->alive) continue;

        for (int j = i + 1; j < ball_count; j++) {
            Ball* b = &balls[j];
            if (!b->alive) continue;

            float dx = b->x - a->x;
            float dy = b->y - a->y;
            float dist_sq = dx * dx + dy * dy;
            float min_dist = a->radius + b->radius;

            if (dist_sq >= min_dist * min_dist) continue;
            if (dist_sq < 0.0001f) continue;  // avoid division by zero

            float dist = fsqrt(dist_sq);
            float nx = dx / dist;
            float ny = dy / dist;

            // Relative velocity along the collision normal
            float dvx = a->vx - b->vx;
            float dvy = a->vy - b->vy;
            float vn = dvx * nx + dvy * ny;

            // Only resolve if balls are approaching each other
            if (vn > 0.0f) {
                a->vx -= vn * nx;
                a->vy -= vn * ny;
                b->vx += vn * nx;
                b->vy += vn * ny;

                // Separate overlapping balls to avoid sticking
                float overlap = min_dist - dist;
                float push = overlap * 0.5f + 0.5f;  // tiny extra nudge
                a->x -= push * nx;
                a->y -= push * ny;
                b->x += push * nx;
                b->y += push * ny;
            }
        }
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
    fmemset(pixels, 0, BUF_SIZE);
    ball_count = 0;

    // Seed with initial balls spread across the canvas
    for (int i = 0; i < 6; i++) {
        spawn_ball(100.0f + rng_float() * 600.0f,
                   80.0f + rng_float() * 440.0f);
    }
}

__attribute__((export_name("wasm_update")))
void wasm_update(float dt) {
    if (dt > 0.1f) dt = 0.1f;
    if (dt <= 0.0f) dt = 0.016f;

    // Plain dark background
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
