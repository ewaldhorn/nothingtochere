#include <stdio.h>

union val
{
    int int_num;
    float fl_num;
    char str[20];
};

int main()
{
    union val info;
    union val *ptr = NULL;
    ptr = &info;
    ptr->int_num = 10;
    printf("info.int_num is %d\n", info.int_num);

    (*ptr).int_num = 11;

    printf("info.int_num is %d\n", info.int_num);
}