#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/*
    Generates a specified number of random numbers between 0 and 100.
*/
int main()
{
    int num, i;
    time_t t1;

    printf("How many random numbers are required? : ");
    scanf("%d", &num);

    /* seed the random number generator */
    srand((unsigned)time(&t1));
    printf("\n");

    for (i = 0; i < num; i++)
    {
        printf("%3d: %4d \n", (1 + i), rand() % 100);
    }

    printf("\n");
    return 0;
}