#include <stdio.h>

int factorial(int num);

int main() {
    int x = 5;

    printf("Factorials of 5: %d.\n", factorial(5));

    return 0;
}

int factorial(int num) {
    if (num == 1) {
        return 1;
    } else {
        return (num * factorial(num - 1));
    }
}