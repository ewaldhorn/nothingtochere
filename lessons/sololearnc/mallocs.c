#include <stdio.h>
#include <stdlib.h>

int main()
{

    int *ptr;
    ptr = malloc(10 * sizeof(*ptr));
    if (ptr != NULL)
    {
        *(ptr + 2) = 50; // assign 50 to 3rd element
    }

    free(ptr);

    return 0;
}