#include <stdio.h>

int main() {
    int num;
    printf("Enter a number: ");
    scanf("%d", &num);

    printf("You entered %d. It is ", num);

    if (num % 2 != 0) {
        printf("not ");
    }

    printf("divisible by two without a remainder.\n");

    return 0;
}