#include <stdio.h>

int main() {
    printf("Enter some text: ");

    int c, nl = 0;

    while ((c = getchar()) != EOF) {
        if (c == '\n') {
            ++nl;
        }
    }

    printf("\nYou entered %d lines.\n", nl);

    return 0;
}