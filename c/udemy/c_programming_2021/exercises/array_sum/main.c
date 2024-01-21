/**
 * Fill an array with integers and calculate the sum and product of the elements.
*/
#include <stdio.h>
#include <stdlib.h>

int main() {
    int numbers[] = {1,3,4,8,3,1,2,6,2,3,4,1,5,5,5,6,3,4,2,1,8,9};
    int numberSize = sizeof numbers / sizeof numbers[0];

    int sum = 0;
    int product = 1;

    for (int i = 0; i < numberSize; i++) {
        sum += numbers[i];
        product *= numbers[i];
    }

    printf("\nThe sum is %d\n", sum);
    printf("The product is %d\n", product);

    return 0;
}