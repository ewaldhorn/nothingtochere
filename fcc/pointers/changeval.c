#include <stdio.h>

void change_value(int *num);

int main()
{
    int nb = 42;
    
    change_value(&nb);
    printf("The value is %d.\n", nb);

    return 0;
}

void change_value(int *num) {
    *num = 1337;
}