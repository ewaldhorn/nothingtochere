/opt/wasi-sdk/bin/clang++ \
    --target=wasm32-unknown-wasi \
    --sysroot=/opt/wasi-sdk/share/wasi-sysroot \
    -Oz \
    -fno-exceptions \
    -mexec-model=reactor \
    -Wl,--export=processNumbers \
    -Wl,--export=malloc \
    -Wl,--export=free \
    -Wl,--no-entry \
    -o logic.wasm \
    vector_logic.cpp
