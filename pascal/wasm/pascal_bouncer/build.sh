#!/bin/sh
# Build bouncer.pas -> bouncer.wasm using Free Pascal wasm32 cross-compiler
# Requires: ppcrosswasm32, wasm-opt (from binaryen), fpc.cfg with wasm32 units
set -e

ppcrosswasm32 \
    -Tembedded \
    -O3 \
    -XX \
    -Xs \
    -Xg \
    -Xd \
    -Xn \
    -CX \
    -k--initial-memory=4194304 \
    -obouncer.wasm \
    bouncer.pas

# Post-process with wasm-opt to shrink further
wasm-opt -Oz --strip-debug --strip-producers --enable-bulk-memory \
    -o bouncer_opt.wasm bouncer.wasm \
    && mv bouncer_opt.wasm bouncer.wasm

ls -lh bouncer.wasm
