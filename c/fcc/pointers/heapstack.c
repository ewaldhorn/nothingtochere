#include <stdio.h>
#include <stdlib.h>

void bar()
{
    int nb;
    nb = 1337;
}

int *foo()
{
    int *n;
    n = malloc(sizeof(int));
    *n = 42;

    return n;
}

int main()
{
    int *pn;

    pn = foo();
    printf("%d\n", *pn);

    bar();
    printf("%d\n", *pn);

    return 0;
}