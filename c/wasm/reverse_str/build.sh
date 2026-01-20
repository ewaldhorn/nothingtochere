clang --target=wasm32 \
  -O3 \
  -nostdlib \
  -fno-builtin \
  -ffreestanding \
  -Wl,--no-entry \
  -Wl,--export-all \
  -Wl,--export-memory \
  -o module.wasm main.c
