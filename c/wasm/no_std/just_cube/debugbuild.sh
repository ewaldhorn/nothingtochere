clang \
    --target=wasm32 \
    -nostdlib \
    -Wl,--no-entry \
    -Wl,--export=cube \
    -Wl,--export=square \
    -Wl,--allow-undefined \
    -o ./docs/math.wasm \
    ./src/math.c
