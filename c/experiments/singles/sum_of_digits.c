#include <stdio.h>

int getSumOfDigits(int src) {
    int total = 0;

    while (src > 0) {
        total += src % 10;
        src /= 10;
    }

    return total;
}

int main() {
    int src = 1;

    while (src < 100000) {
        printf("The sum of the digits of %5d: %d\n", src, getSumOfDigits(src));
        src += 59;
    }

    return 0;
}
