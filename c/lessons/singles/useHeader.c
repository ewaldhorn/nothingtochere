#include "myheader.h"

int main()
{
    int a = 5;
    int b = 10;

    printf("The sum of %d and %d is %d.\n", a, b, addUp(a, b));
    return 0;
}

int addUp(int L, int R)
{
    return L + R;
}
