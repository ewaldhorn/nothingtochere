/**
 * 2D array, calculate rainfall data.
 * 
*/
#include <stdio.h>
#include <stdlib.h>

void printTable(double arr[][12], int rows, int cols) {
    for (int year = 0; year < rows; year++) {
        for (int month = 0; month < cols; month++) {
            printf("%4.1lf", arr[year][month]);
        }
        printf("\n");
    }
}

int main() {
    double rainfall[5][12] = {
        // 5 years, 12 months
        {4.3, 4.0, 4.2, 4.4, 3.9, 3.9, 4.1, 4.2, 2.7, 1.3, 0.6, 0.7},
        {5.5, 5.2, 4.8, 4.7, 4.0, 3.4, 3.1, 4.0, 1.0, 0.9, 0.1, 0.2},
        {9.1, 8.8, 4.6, 4.7, 4.1, 4.0, 2.7, 3.0, 0.5, 1.5, 0.5, 1.1},
        {8.9, 8.7, 4.0, 4.5, 3.9, 3.8, 2.5, 2.1, 0.7, 1.1, 0.7, 1.1},
        {6.5, 5.5, 2.1, 3.1, 3.3, 3.2, 2.0, 1.9, 0.6, 1.7, 2.3, 2.8},
    };

    printf("The rainfall table:\n");
    printTable(rainfall, 5, 12);
    printf("\n");
    
    return 0;
}