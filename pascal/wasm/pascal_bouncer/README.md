# Bouncer — Pascal WASM Xonix Clone

A browser-based arcade game inspired by the classic DOS game **Xonix**, written entirely in **Free Pascal** and compiled to **WebAssembly (WASM)**. The game logic runs as a native WASM module; the browser handles input, rendering, and the game loop via a thin JavaScript glue layer.

## Gameplay

- Use the **Arrow Keys** to move your player across the grid.
- **Capture territory** by cutting off sections of the sea and converting them to land.
- Avoid the **red bouncing balls** in the sea — they kill you on contact.
- Avoid the **orange tracker ball** on land — it hunts you down while you're away from safe ground.
- **Win** a level by capturing **85% or more** of the grid.
- You start with **3 lives**; enemies increase each level.

## Project Structure

| File | Description |
|------|-------------|
| `bouncer.pas` | Full game logic — written in Free Pascal, compiled to WASM |
| `bouncer.wasm` | Compiled WebAssembly binary (output of `build.sh`) |
| `bouncer.js` | JavaScript glue: loads WASM, drives the game loop, handles input |
| `index.html` | HTML entry point and UI shell |
| `style.css` | Glassmorphism-style CSS for the game dashboard |
| `fpc.cfg` | Free Pascal compiler config — points to the WASM cross-compiler units |
| `build.sh` | Compiles `bouncer.pas` to `bouncer.wasm` |
| `run.sh` | Builds then serves the project locally on port 9000 |

## Prerequisites

### 1. Free Pascal with WASM Cross-Compiler

You need a **Free Pascal** build that includes the `wasm32-embedded` cross-compiler (`ppcrosswasm32`) and its matching standard units.

- **Free Pascal homepage:** https://www.freepascal.org/
- **Download page:** https://www.freepascal.org/download.html
- **Trunk / nightly builds** (required for WASM support): https://gitlab.com/freepascal.org/fpc/source

> **Important:** The WASM cross-compilation target is only available in **FPC 3.3.1 (development trunk)** or later.
> Stable FPC 3.2.x does **not** include `ppcrosswasm32`.

Once installed, the compiler units must be available at the path referenced in `fpc.cfg`:

```
~/fpcwasm/lib/fpc/3.3.1/units/wasm32-embedded/*
```

Adjust `fpc.cfg` if your installation lives elsewhere.

### 2. Binaryen (`wasm-opt`)

`build.sh` post-processes the WASM binary with `wasm-opt` to reduce file size.

- **Binaryen releases:** https://github.com/WebAssembly/binaryen/releases

Install via Homebrew on macOS:

```sh
brew install binaryen
```

### 3. Python 3 (for the dev server)

`run.sh` uses Python's built-in HTTP server. Python 3 ships with macOS and most Linux distros.

## Building

```sh
./build.sh
```

This will:
1. Compile `bouncer.pas` using `ppcrosswasm32` targeting `wasm32-embedded`, with aggressive size optimisations (`-O3 -XX -Xs`).
2. Post-process the output with `wasm-opt -Oz` (Binaryen) to shrink it further.
3. Print the final size of `bouncer.wasm`.

## Running

```sh
./run.sh
```

This will:
1. Run `build.sh` (build failure aborts the run).
2. Start a local HTTP server on **port 9000**.
3. Open your browser at **http://localhost:9000**.

> **Note:** A local HTTP server is required because browsers block WebAssembly loading from `file://` URLs due to CORS restrictions.

## Compiler Flags Reference

| Flag | Meaning |
|------|---------|
| `-Tembedded` | Target: embedded/freestanding (no OS) |
| `-O3` | Optimise for speed |
| `-XX` | Smart linking (dead-code elimination) |
| `-Xs` | Strip debug symbols |
| `-Xg` | Use external linker |
| `-Xd` | Disable default library search paths |
| `-Xn` | No default units |
| `-CX` | Enable position-independent code |
| `-k--initial-memory=4194304` | Set WASM initial memory to 4 MB |
