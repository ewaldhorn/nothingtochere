# basic_canvas

Bouncing neon balls with elastic collision — written in freestanding C, compiled to WebAssembly with Zig. No libc, no math library, no runtime. ~5.6 KB `.wasm` binary.

```
basic_canvas/
├── main.c          C source (freestanding — no #includes)
├── index.html      Browser shell: canvas, WASM loader, animation loop
├── build.sh        zig build-lib → main.wasm
├── run.sh          python3 -m http.server 9000
├── _inspect.py     Dump WASM imports/exports without wasm-objdump
├── _test.js        Node.js smoke test (no browser needed)
└── main.wasm       5.6 KB (1.9 MB before we moved the pixel buffer out)
```

## Quick start

```bash
chmod +x build.sh run.sh
./build.sh          # Zig → main.wasm
./run.sh            # Serves on http://localhost:9000
```

Open the URL. Click anywhere to spawn balls. They bounce off walls and each other.

To verify the build without a browser:

```bash
node _test.js
# bg pixel: 10,5,20,255
# SUCCESS
```

## How it works

### C side (`main.c`)

- **No standard library.** No `<stdint.h>`, `<string.h>`, or `<math.h>`. Types are typedef'd by hand. `memset` and `sqrt` are handwritten (`fmemset`, `fsqrt` via Newton's method).
- **Pixel buffer.** A flat RGBA array at a fixed offset in WASM linear memory (64 KB past static data). Zeroed at init. JS reads it every frame and blits to a `<canvas>` via `putImageData`.
- **Drawing.** Midpoint circle algorithm (outline + filled). No line drawing needed for this demo.
- **Physics.** 100-ball cap. Equal-mass elastic collision with overlap push-apart to prevent sticking. Xorshift32 PRNG for random colours, velocities, and spawn jitter.
- **Exports.** Six functions callable from JavaScript:

| Export | Signature | Purpose |
|---|---|---|
| `wasm_init` | `() → void` | Allocate buffer, seed 6 balls |
| `wasm_update` | `(dt: f32) → void` | Clear, update physics, draw |
| `wasm_click` | `(x: i32, y: i32) → void` | Spawn ball at click point |
| `wasm_get_pixels` | `() → *u8` | Pointer to RGBA buffer |
| `wasm_get_width` | `() → i32` | 800 |
| `wasm_get_height` | `() → i32` | 600 |

### JS side (`index.html`)

- Provides `WebAssembly.Memory` (32 pages / 2 MB), an indirect function table, and two globals (`__memory_base`, `__table_base`) to satisfy Zig's PIC ABI imports.
- Runs `requestAnimationFrame` loop: calls `wasm_update(dt)`, copies the pixel buffer into an `ImageData`, and puts it on the canvas.
- Click handler scales mouse coordinates to canvas pixel space and calls `wasm_click`.

### Build (`build.sh`)

```bash
zig build-lib \
    -O ReleaseSmall \
    -target wasm32-freestanding \
    -dynamic \
    -fPIC \
    main.c \
    -femit-bin=main.wasm
```

- `wasm32-freestanding` — no OS, no libc. Just the raw WASM VM.
- `-dynamic` — produce a shared library with an export section. Side effect: memory is imported from the host rather than exported.
- `-fPIC` — position-independent code (required by `wasm-ld` for dynamic WASM).

### Why the binary is so small

The pixel buffer (`800 × 600 × 4 = 1.92 MB`) used to be a static array, which WASM embeds as a data segment — raw zero bytes in the file. It now lives as a pointer, allocated at a known offset in the JS-provided memory and zeroed at runtime. The binary dropped from 1.9 MB to 5.6 KB.

## Key numbers

| Metric | Value |
|---|---|
| Canvas | 800 × 600 px, 32-bit RGBA |
| Ball cap | 100 |
| Collision pairs/frame (worst) | ~5,000 (O(n²), 100 balls) |
| WASM binary | ~5.6 KB |
| Memory footprint | 2 MB (32 pages) |

## Requirements

- **Zig** 0.13+ (tested with 0.16.0)
- **Python** 3.x (for `run.sh`; any HTTP server works)
- **Node.js** (optional, for `_test.js`)
