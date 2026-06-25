#!/bin/bash
# build.sh — Compile main.c to WASM with Zig for browser use.
set -euo pipefail

SCRIPT_DIR="$(cd "$(dirname "$0")" && pwd)"
cd "$SCRIPT_DIR"

echo "==> Building main.wasm with Zig (wasm32-freestanding) ..."
zig build-lib \
    -O ReleaseSmall \
    -target wasm32-freestanding \
    -dynamic \
    -fPIC \
    main.c \
    -femit-bin=main.wasm

SIZE=$(wc -c < main.wasm | tr -d ' ')
echo "==> Done. main.wasm: ${SIZE} bytes"
