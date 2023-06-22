#include <stdio.h>

void* square(const void* num);

int main()
{
    int x = 6, sq_int;
    sq_int = square(&x);
    printf("%d squared is %d.\n", x, sq_int);

    return 0;
}

void* square(const void* num)
{
    int result;
    // (*(int *)num)  cast num to an int*, then dereference pointer to get int value
    result = (*(int *)num) * (*(int *)num);
    return result; 
}