#include <stdio.h>

void swap(int *l, int *r)
{
    int tmp;

    tmp = *l;
    *l = *r;
    *r = tmp;
}

int main()
{
    int l = 1, r = 2;
    
    printf("Left is %d and Right is %d.\nPerforming swap...\n", l, r);

    swap(&l, &r);

    printf("Now Left is %d and Right is %d.\n", l, r);

    return 0;
}