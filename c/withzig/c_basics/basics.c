#include <stdlib.h>
#include <stdio.h>

int main(void) {
    double data[5] = {
        [0] = 111.0,
        [3] = 444.0,
        [4] = 555.0,
        [1] = 222.0
    }; 

    for (size_t i = 0; i < 5; i++) {
        printf("Position %zu contains %g\n", i, data[i]);
    }

    return EXIT_SUCCESS;
}