# basic_canvas

Bouncing neon balls with elastic collision — written in freestanding C, compiled to WebAssembly. No libc, no math library, no runtime. Two build paths: **Zig** (`build.sh`) and **clang + lld** (`build_clang.sh`).

```
basic_canvas/
├── main.c          C source (freestanding — no #includes)
├── index.html      Browser shell: canvas, WASM loader, animation loop
├── build.sh        zig build-lib → main.wasm
├── build_clang.sh  clang + lld wasm-ld → main.wasm (no zig needed)
├── run.sh          python3 -m http.server 9000
├── _inspect.py     Dump WASM imports/exports without wasm-objdump
├── _test.js        Node.js smoke test (no browser needed)
└── main.wasm       ~3.6–9.4 KB depending on toolchain
```

## Quick start

**With Zig:**
```bash
chmod +x build.sh run.sh
./build.sh          # zig build-lib → main.wasm
./run.sh            # Serves on http://localhost:9000
```

**With clang + lld** (no zig required):
```bash
# macOS: brew install llvm lld
chmod +x build_clang.sh run.sh
./build_clang.sh    # clang + wasm-ld → main.wasm
./run.sh
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

### Build (`build.sh` — Zig)

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

### Build (`build_clang.sh` — clang + lld)

```bash
clang \
    -target wasm32-unknown-unknown \
    -O2 \
    -nostdlib \
    -fPIC \
    -Wl,--no-entry \
    -Wl,--export-dynamic \
    -Wl,--experimental-pic \
    -Wl,--shared \
    -Wl,--allow-undefined \
    -fuse-ld=/path/to/wasm-ld \
    -o main.wasm \
    main.c
```

- `-fPIC` — position-independent code; data accesses go through the imported `__memory_base` global, so the module doesn't define its own memory.
- `--experimental-pic` — enables wasm-ld's PIC relocation support.
- `--shared` — builds a WASM shared library (mirrors zig's `-dynamic`).
- `--allow-undefined` — allows imports from JS (memory, function table, globals).

The resulting module **imports** `env.memory` from the JS host, exactly like the zig build, so `index.html` works unchanged with either binary.

The script auto-detects both `clang` and `wasm-ld` across common Homebrew paths (arm64 and x86_64) and `$PATH`.

## Requirements

| | `build.sh` (Zig) | `build_clang.sh` (clang) |
|---|---|---|
| **Compiler** | `brew install zig` | `brew install llvm` |
| **Linker** | bundled with zig | `brew install lld` |
| **Server** | `python3` (any HTTP server) | same |
| **Smoke test** | `node` (optional) | same |

- Tested with Zig 0.16.0, Homebrew clang 22.1.8, Homebrew lld 22.1.8.
- Apple's bundled clang (Xcode / CLT) does **not** include the WebAssembly backend — Homebrew LLVM is required for `build_clang.sh`.
