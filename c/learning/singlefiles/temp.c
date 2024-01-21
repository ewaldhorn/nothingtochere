#include <stdio.h>

int main() {
    float fahr, celsius, lower = 0, upper = 500, step = 20;

    fahr = lower;


    printf("%3s %6s\n", "F", "C");

    while (fahr <= upper) {
        celsius = (5.0/9.0) * (fahr - 32);
        printf("%3.0f %6.1f\n", fahr, celsius);
        fahr += step;
    }

    return 0;
}
