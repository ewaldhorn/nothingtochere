clang \
    --target=wasm32 \
    -nostdlib \
    -Os \
    -Wl,--no-entry \
    -Wl,--export=cube \
    -Wl,--export=square \
    -Wl,--allow-undefined \
    -Wl,--strip-all \
    -Wl,--gc-sections \
    -o ./docs/math.wasm \
    ./src/math.c
