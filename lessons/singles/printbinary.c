#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int _putchar(char c);
void _divide(unsigned long int n);

/**
 * print_binary - Prints the binary representation of a number
 * @n: The number to representing in binary
 *
 * Return: Nothing
 */
void print_binary(unsigned long int n)
{
    if (n == 0)
    {
        _putchar('0');
        return;
    }

    _divide(n);
}

/**
 * _divide - ...
 * @n: ...
 *
 * Return: ...
 */
void _divide(unsigned long int n)
{
    if (n < 1)
        return;

    _divide(n >> 1);

    if (n & 1)
        _putchar('1');
    else
        _putchar('0');
}

int main()
{
    print_binary(0);
    printf("\n");
    print_binary(1);
    printf("\n");
    print_binary(2);
    printf("\n");
    print_binary(3);
    printf("\n");
    print_binary(4);
    printf("\n");
    print_binary(5);
    printf("\n");
    print_binary(6);
    printf("\n");
    print_binary(7);
    printf("\n");
    print_binary(8);
    printf("\n");
    print_binary(9);
    printf("\n");
    print_binary(10);
    printf("\n");
    print_binary(11);
    printf("\n");
    print_binary(12);
    printf("\n");
    print_binary(13);
    printf("\n");
    print_binary(14);
    printf("\n");
    print_binary(15);
    printf("\n");
    print_binary(16);
    printf("\n");
    print_binary(98);
    printf("\n");
    print_binary(1024);
    printf("\n");
    print_binary((1 << 10) + 1);
    printf("\n");

    return 0;
}

int _putchar(char c)
{
    return (write(1, &c, 1));
}