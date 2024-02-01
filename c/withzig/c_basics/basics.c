#include <stdlib.h>
#include <stdio.h>

int factorial(int n) {
    int retval = 1;

    while (n != 1) {
        retval *= n--;
    }

    return retval;
}

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

    printf("\nThe factorial of 2 is: %d\n", factorial(2));
    printf("The factorial of 3 is: %d\n", factorial(3));
    printf("The factorial of 4 is: %d\n", factorial(4));
    printf("The factorial of 5 is: %d\n", factorial(5));
    printf("The factorial of 6 is: %d\n", factorial(6));

    return EXIT_SUCCESS;
}