#include <stdio.h>

int myStrlen(char s[]);

int main() {
    printf("The string `%s` is %d characters long.\n", "0987654321", myStrlen("0987654321"));

    return 0;
}

int myStrlen(char s[]) {
    int i;

    while (s[i] != '\0') {
        ++i;
    }

    return i;
}