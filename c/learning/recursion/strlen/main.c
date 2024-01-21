#include "main.h"
#include <stdio.h>

int main() {
    printf("C string length without using stdlib functions:\n\n");
    char *myString = "This is a string!";
    printf("The string `%s` is %d characters long.\n", myString, mystrlen(myString));

    myString = "0123456789";
    printf("The string `%s` is %d characters long.\n", myString, mystrlen(myString));

    printf("\n");
    return 0;
}

int mystrlen(char *s) {
    // check if it's an empty string
    if (*s == '\0') {
        return 0;
    }

    s++;
    return (mystrlen(s) + 1);
}