#include <stdio.h>

int main() {
    char a[100];

    printf("Enter a string:");

    // UNSAFE
    gets(a);

    printf("You entered '%s'\n", a);

    return 0;
}