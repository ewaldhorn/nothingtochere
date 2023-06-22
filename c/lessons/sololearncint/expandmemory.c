#include <stdio.h>
#include <stdlib.h>

int main()
{
    int *ptr;
    ptr = malloc(10 * sizeof(*ptr));
    if (ptr != NULL)
    {
        *(ptr + 2) = 50; /* assign 50 to third int */
    }
    ptr = realloc(ptr, 100 * sizeof(*ptr));
    *(ptr + 30) = 75;

    free(ptr);
 
    return 0;
}