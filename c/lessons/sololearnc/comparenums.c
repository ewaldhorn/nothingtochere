#include <stdio.h>
#include <stdlib.h>

int compareAscending(const void *, const void *);

int main()
{
    int arr[5] = {52, 23, 56, 19, 4};

    int width = sizeof(arr[0]);
    int num = sizeof(arr) / width;

    qsort((void *)arr, num, width, compareAscending);

    for (int i = 0; i < num; i++)
    {
        printf("%d ", arr[i]);
    }

    printf("\n");

    return 0;
}

int compareAscending(const void *l, const void *r)
{
    if ((*(int *)l) == (*(int *)r))
    {
        return 0;
    }
    else if ((*(int *)l) < (*(int *)r))
    {
        return -1;
    }
    else
    {
        return 1;
    }
}