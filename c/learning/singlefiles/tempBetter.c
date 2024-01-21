#include <stdio.h>

#define LOWER 0
#define UPPER 500
#define STEP  20

int main() {
    float fahr, celsius;

    fahr = LOWER;


    printf("%3s %6s\n", "F", "C");

    while (fahr <= UPPER) {
        celsius = (5.0/9.0) * (fahr - 32);
        printf("%3.0f %6.1f\n", fahr, celsius);
        fahr += STEP;
    }

    return 0;
}
