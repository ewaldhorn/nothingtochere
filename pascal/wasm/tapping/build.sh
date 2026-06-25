#!/bin/sh
# Build basic_canvas.pas -> basic_canvas.wasm using Free Pascal wasm32 cross-compiler
# Requires: ppcrosswasm32, wasm-opt (from binaryen), fpc.cfg with wasm32 units
set -e

ppcrosswasm32 \
    -Tembedded \
    -O3 \
    -XX \
    -Xs \
    -CX \
    -k--initial-memory=4194304 \
    -obasic_canvas.wasm \
    basic_canvas.pas

# Post-process with wasm-opt to shrink further
wasm-opt -Oz --strip-debug --strip-producers --enable-bulk-memory \
    -o basic_canvas_opt.wasm basic_canvas.wasm \
    && mv basic_canvas_opt.wasm basic_canvas.wasm

ls -lh basic_canvas.wasm
