#!/bin/bash
# build_clang.sh — Compile main.c to WASM with clang + lld (no zig, no emscripten).
#
# Single-step build: clang drives both compilation and linking via -fuse-ld=wasm-ld.
#
# Requirements (macOS):
#   brew install llvm   — clang with wasm32 backend
#   brew install lld    — wasm-ld linker
#
# Requirements (Linux):
#   sudo apt install clang lld   # Debian/Ubuntu
#   sudo dnf install clang lld   # Fedora/RHEL
set -euo pipefail

SCRIPT_DIR="$(cd "$(dirname "$0")" && pwd)"
cd "$SCRIPT_DIR"

# ---------------------------------------------------------------------------
# Locate clang (must support wasm32 target).
# ---------------------------------------------------------------------------
find_clang() {
    local candidates=(
        /opt/homebrew/opt/llvm/bin/clang   # Homebrew arm64 (Apple Silicon)
        /usr/local/opt/llvm/bin/clang      # Homebrew x86_64
        clang                              # $PATH fallback (Linux etc.)
    )
    for c in "${candidates[@]}"; do
        if [[ -x "$c" ]] || command -v "$c" &>/dev/null; then
            if "$c" -target wasm32-unknown-unknown -nostdlib -c \
                    -x c /dev/null -o /dev/null &>/dev/null; then
                echo "$c"
                return 0
            fi
        fi
    done
    return 1
}

# ---------------------------------------------------------------------------
# Locate wasm-ld (ships with Homebrew lld on macOS; bundled with clang on Linux).
# ---------------------------------------------------------------------------
find_wasmld() {
    local candidates=(
        /usr/local/opt/lld/bin/wasm-ld     # Homebrew lld x86_64
        /opt/homebrew/opt/lld/bin/wasm-ld  # Homebrew lld arm64
        /usr/local/bin/wasm-ld             # Homebrew lld keg-only symlink
        /opt/homebrew/bin/wasm-ld          # Homebrew lld arm64 symlink
        wasm-ld                            # $PATH fallback (Linux etc.)
    )
    for w in "${candidates[@]}"; do
        if [[ -x "$w" ]] || command -v "$w" &>/dev/null; then
            echo "$w"
            return 0
        fi
    done
    return 1
}

CLANG=$(find_clang || true)
if [[ -z "$CLANG" ]]; then
    cat >&2 <<'EOF'
Error: no clang with wasm32 support found.

  macOS  →  brew install llvm
             (Apple's bundled clang does NOT include the WebAssembly backend)

  Linux  →  sudo apt install clang   # Debian/Ubuntu
             sudo dnf install clang   # Fedora/RHEL

EOF
    exit 1
fi

WASMLD=$(find_wasmld || true)
if [[ -z "$WASMLD" ]]; then
    cat >&2 <<'EOF'
Error: wasm-ld not found.

  macOS  →  brew install lld
  Linux  →  sudo apt install lld   # Debian/Ubuntu
             sudo dnf install lld   # Fedora/RHEL

EOF
    exit 1
fi

echo "==> clang  : $CLANG ($("$CLANG" --version | head -1))"
echo "==> wasm-ld: $WASMLD ($("$WASMLD" --version | head -1))"

# ---------------------------------------------------------------------------
# 4. Link — wasm-ld → freestanding .wasm module.
#
# Memory layout (must match what wasm_init() assumes in main.c):
#   The C code places the pixel buffer at the hardcoded address 65536 (64 KB).
#   That is safe only if all static data lives BELOW 65536.
#
#   Homebrew lld defaults to --stack-first, which places the shadow stack in
#   the first 64 KB and static data starting at 65536 — a direct collision
#   with the pixel buffer.  clear_screen() would overwrite the `pixels` global
#   itself (at offset 65552) on every frame, corrupting it silently and
#   crashing on the next frame.
#
#   Fix: --no-stack-first --global-base=1024
#     * Static data starts at 1024 (~1 KB), matching the zig PIC layout.
#     * Shadow stack grows downward from the TOP of linear memory (2 MB).
#     * Pixel buffer at 65536 is safely in heap space above all static data.
#
#   initial-memory: pixel buffer needs 65536 + 800×600×4 = 1,985,536 bytes
#   → 31 WASM pages. We allocate 32 pages (2 MB).  One page = 65536 bytes.
# ---------------------------------------------------------------------------
echo "==> Building main.wasm ..."
"$CLANG" \
    -target wasm32-unknown-unknown \
    -O2 \
    -nostdlib \
    -Wl,--no-entry \
    -Wl,--export-dynamic \
    -Wl,--allow-undefined \
    -Wl,--no-stack-first \
    -Wl,--global-base=1024 \
    -Wl,--initial-memory=2097152 \
    -fuse-ld="$WASMLD" \
    -o main.wasm \
    main.c

SIZE=$(wc -c < main.wasm | tr -d ' ')
echo "==> Done. main.wasm: ${SIZE} bytes"
