#include <string.h>
#include <stdio.h>

int main()
{
    char input[10];
    int num;

    printf("Enter a number:");
    gets(input);
    num = atoi(input);
    printf("The number + 1 is %d\n", num + 1);

    return 0;
}