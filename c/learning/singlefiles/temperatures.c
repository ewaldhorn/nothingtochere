#include <stdio.h>

int main() {
    int fahr, celsius;
    int lower = 0, upper = 500, step = 20;

    fahr = lower;

    printf("F\tC\n");

    while (fahr <= upper) {
        celsius = 5 * (fahr - 32) / 9;
        printf("%d\t%d\n", fahr, celsius);
        fahr += step;
    }

    return 0;
}