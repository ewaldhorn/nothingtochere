#include <stdio.h>

int add(int num1, int num2);
int subtract(int num1, int num2);
int multiply(int num1, int num2);
int divide(int num1, int num2);

int main()
{
    int x, y, choice, result;
    int (*op[4])(int, int);

    op[0] = add;
    op[1] = subtract;
    op[2] = multiply;
    op[3] = divide;

    printf("Enter two integers:");
    scanf("%d%d", &x, &y);

    printf("Enter 0 to add, 1 to subtract, 2 to multiply and 3 to divide:");
    scanf("%d", &choice);

    result = op[choice](x,y);
    printf("%d\n", result);

    return 0;
}

int add(int num1, int num2) { return num1 + num2; }
int subtract(int num1, int num2) { return num1 - num2; }
int multiply(int num1, int num2) { return num1 * num2; }
int divide(int num1, int num2) { return num1 / num2; }
