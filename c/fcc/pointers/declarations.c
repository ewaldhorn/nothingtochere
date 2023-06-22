#include <stdio.h>

int main()
{
    int n, *pn, **ppn, ***pppn;

    n = 42;        // value
    pn = &n;       // pointer to value
    ppn = &pn;     // pointer to pointer of value
    pppn = &ppn;   // pointer to pointer to pointer of value

    printf("Address %p == %p\n", *pppn, ppn);

    printf("The value of n    is %d.\n", n);
    printf("The value of pn   is %d.\n", *pn);
    printf("The value of ppn  is %d.\n", **ppn);
    printf("The value of pppn is %d.\n", ***pppn);

    return 0;
}