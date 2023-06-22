#include <stdio.h>

#define TO_STR(x) #x
#define CONCAT(x, y) x##y
int main()
{
    printf("%s\n", TO_STR(123\\12));
    int x = 4;

    int y = 5;

    int CONCAT(x, y) = x + y;

    printf("%d", xy);
    return 0;
}