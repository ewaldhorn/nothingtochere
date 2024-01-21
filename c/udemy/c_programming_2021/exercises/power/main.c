/**
 * Write a program that calculates an expression n^n where n is an integer value provided
 * by the user.
*/
#include <stdlib.h>
#include <stdio.h>

double power(int base, int exponent) {
    double result = base;

    for (int i = 1; i < exponent; i++) {
        result = result * base;
    }


    return result;
}

int main() {
    // printf("Enter a number: ");
    // int n = 0;
    // scanf("%d", &n);

    printf("\n");    

    printf("%d to the power of %d is %.0lf.\n", 2, 2, power(2, 2));
    printf("%d to the power of %d is %.0lf.\n", 2, 3, power(2, 3));
    printf("%d to the power of %d is %.0lf.\n", 3, 2, power(3, 2));
    printf("%d to the power of %d is %.0lf.\n", 3, 3, power(3, 3));

    printf("\n");    
    
    return 0;
}