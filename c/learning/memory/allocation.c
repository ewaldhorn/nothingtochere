#include <stdio.h>
#include <stdlib.h>

int* generateNumbers(int count) {
    int* numbers = (int*)malloc(sizeof(int) * count);

    for (int i = 0; i < count; i++) {
        numbers[i] = i+1;
    }

    return numbers;
}

int main(){
    // allocate 200 ints on the heap
    int* numbers = generateNumbers(200);
    
    for (int i = 0; i < 200; i++) {
        printf("%d, ", numbers[i]);
    }

    printf("\n");

    // remember to free the memory
    free(numbers);

    return 0;
}