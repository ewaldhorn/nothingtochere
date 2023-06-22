#include <stdio.h>

int main()
{
    int x = 33;
    float y = 12.4;
    char c = 'a';
    void *ptr;

    ptr = &x;
    printf("void pointer points to %d\n", *((int *)ptr));

    ptr = &y;
    printf("void pointer points to %f\n", *((float *)ptr));

    ptr = &c;
    printf("void pointer points to %c\n", *((char *)ptr));

    return 0;
}