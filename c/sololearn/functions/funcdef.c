#include <stdio.h>

int square(int num);

int main() {
    printf("The square of 4 is %d.\n", square(4));

    return 0;
}

int square(int num) {
    return num * num;
}