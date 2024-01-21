#include <stdio.h>

void counter();

int main() {
    counter();
    counter();
    counter();
    
    return 0;
}

void counter() {
    static int count = 0;
    count += 1;
    printf("Count is now at %d.\n", count);
}