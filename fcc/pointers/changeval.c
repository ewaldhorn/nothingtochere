#include <stdio.h>

void change_value(int nb);

int main()
{
    int nb = 42;
    change_value(nb);
    printf("The value is %d.\n", nb);
    return 0;
}

void change_value(int nb) {
    nb = 1337;
}