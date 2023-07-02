#include "difference-of-squares.h"
#include <stdio.h>

int main()
{
    return 0;
}

unsigned int sum_of_squares(unsigned int number)
{
    unsigned int result = 1;

    for (unsigned int i = 2; i <= number; i++) {
        result += i*i;
    }

    return result;
}


unsigned int square_of_sum(unsigned int number)
{
    unsigned int result = 1;

    for (unsigned int i = 2; i <= number; i++) {
        result += i;
    }

    return result*result;
}

unsigned int difference_of_squares(unsigned int number)
{
    unsigned int result = square_of_sum(number) - sum_of_squares(number);
    return result;
}
