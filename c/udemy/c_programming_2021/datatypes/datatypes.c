#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

int main() {

    int i1 = 0;
    printf("i1=%d\n", i1);

    i1 = 5;
    printf("i1=%d\n", i1);

    i1 = -3;
    printf("i1=%d\n", i1);

    // the following statement generates a compiler warning because of the implicit conversion
    i1 = 3.5;
    printf("i1=%d\n", i1);

    double d1 = 4.5;
    printf("d1=%lf\n", d1);

    d1 = 0;
    printf("d1=%lf\n", d1);

    float f1 = 1.37;
    printf("f1=%f\n", f1);

    f1 = 1;
    printf("f1=%f\n", f1);

    char c1 = 'A';
    printf("c1='%c'\n", c1);

    c1 = '0';
    printf("c1='%c'\n", c1);

    _Bool b1 = 0;
    printf("b1=%d\n",b1);

    b1 = false;
    printf("b1=%d\n", b1);

    char name[] = "The Coder";
    printf("The name is %s\n", name);

    return 0;
}