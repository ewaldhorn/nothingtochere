#define WASM_EXPORT __attribute__((used)) __attribute__((visibility("default")))

// Provided by the linker; the start of available memory
extern unsigned char __heap_base;

// Keep track of where the next allocation should start
static unsigned char* bump_ptr = &__heap_base;

WASM_EXPORT
void* malloc(unsigned long size) {
    // 1. Align the pointer to 8 bytes
    // Formula: (ptr + 7) & ~7
    unsigned long ptr_addr = (unsigned long)bump_ptr;
    ptr_addr = (ptr_addr + 7) & ~7;

    void* res = (void*)ptr_addr;

    // 2. "Bump" the pointer forward for the next call
    bump_ptr = (unsigned char*)(ptr_addr + size);

    return res;
}

// In a tiny bump allocator, free usually does nothing.
// You'd need a more complex "Free List" allocator to reuse memory.
WASM_EXPORT
void free(void* ptr) {
    // Left intentionally blank
}
