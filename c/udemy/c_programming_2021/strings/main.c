#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int main() {
    printf("C Strings:\n\n");

    char firstName[] = {"Ben"};
    char lastName[] = {"Benjamin"};

    printf("All together now: %s %s\n", firstName, lastName);
    printf("%s is %lu characters long\n", firstName, strlen(firstName));

    printf("\nMore string adventures: (every 2nd character from 1)\n");

    char anyString[] = {"abcdefghijklmnopqrstuvwxyz"};

    for (int i = 1; i <= 20; i += 2) {
        printf("%c", anyString[i]);
    }

    printf("\n");

    printf("\n");
    return 0;
}