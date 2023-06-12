#include <stdio.h>
#include <string.h>

union val {
    int int_num;
    float float_num;
    char str[20];
};

union val test;

int main()
{
    test.float_num = 3.33;
    test.int_num =  50;
    strcpy(test.str, "This is a string!");

    printf("%d\n", test.int_num);
    printf("%f\n", test.float_num);
    printf("%s\n", test.str);

    return 0;
}