#include <stdlib.h>
#include <stdio.h>

int main() {

    // 1d arrays
    int nums[10];

    nums[0] = 123; // 1st element
    nums[4] = 456; // 5th element
    nums[9] = 789; // last element

    printf("\n1d Array of numbers:\n");
    for (int i = 0; i < 10; i++) {
        printf("Position %2d contains %d\n", i, nums[i]);
    }

    // more 1d arrays
    int totals[] = {78,65,44,82,81,81,74,70,55};

    printf("\nMore 1d array (first 5 elements):\n");
    for (int i = 0; i < 5; i++) {
        printf("Position %d contains %d\n", i, totals[i]);
    }

    // 2d arrays
    int grid[5][5] = {{0,1,2,3,4},{1,2,3,4,5},{2,3,4,5,6},{3,4,5,6,7},{4,5,6,7,8}};

    printf("\n2d arrays:\n");
    
    for (int y = 0; y < 5; y++) {
        for (int x = 0; x < 5; x++) {
            printf("%d ", grid[y][x]);
        }
        printf("\n");
    }

    printf("\n");

    return 0;
}