#include <stdio.h>
#include <stdlib.h>

#define PI 3.14 

int main() {
    const int x = 10;
    double y = 3.0;
    // x=y; // can't do this if x is a constant!

    printf("x=%d\n",x);
    printf("y=%lf\n",y);

    printf("\nThe address of x is %p\n", &x);


    printf("PI * 2 = %f\n", PI*2);

    return 0;
}