#include "power.h"

int main() {
    for (int i = 1; i <= 20; i++) {
        printf("%2d to the power of %d is %d.\n", i, 3, power(i, 3));
    }

    return 0;
}