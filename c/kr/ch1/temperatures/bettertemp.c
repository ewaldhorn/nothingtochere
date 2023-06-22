#include <stdio.h>

#define LOWER 0
#define UPPER 500
#define STEP  20

int main() {
    for (int fahr = 0; fahr <= UPPER; fahr += STEP) {
        printf("%3d %6.1f\n", fahr, (5.0/9.0)*(fahr-32));
    }

    return 0;
}