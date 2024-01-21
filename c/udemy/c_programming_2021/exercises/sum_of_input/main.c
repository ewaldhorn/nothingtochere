#include <stdlib.h>
#include <stdio.h>

/**
 * Write a program that reads a sequence of values from the user and stops by displaying "done" 
 * when the sum of the values exceed 100.
*/

int main() {
    int runningTotal = 0;
    int input = 0;

    printf("\n");

    while (runningTotal < 100) {
        printf("Enter a number: ");
        scanf("%d", &input);
        runningTotal += input;
    }

    printf("\nDone.\nThe total reached was %d.\n\n", runningTotal);

    return 0;
}