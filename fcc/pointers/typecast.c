#include <stdio.h>

int main()
{
    int nb = 42, *ptr = &nb;

    printf("%d %5.60f\n", *ptr, *(float *)ptr);

    return 0;
}