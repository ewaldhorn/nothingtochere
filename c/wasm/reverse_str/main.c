#define WASM_EXPORT __attribute__((visibility("default")))

extern unsigned char __heap_base;
static unsigned char* bump_ptr = &__heap_base;

typedef unsigned long size_t;

int my_strlen(const char* s) {
    int size = 0;
    while (s[size] != '\0') size++;
    return size;
}

WASM_EXPORT
void* my_malloc(int size) {
    unsigned char* ptr = bump_ptr;
    bump_ptr += size;
    return ptr;
}

WASM_EXPORT
void reverse_string(char* str) {
    int len = my_strlen(str);
    for (int i = 0; i < len / 2; i++) {
        char temp = str[i];
        str[i] = str[len - 1 - i];
        str[len - 1 - i] = temp;
    }
}
