#include <stdio.h>
#include <stdlib.h>

int main() {
    int x = 3;
    double y = 3.5;

    char c = 0;

    printf("Type a character: ");
    scanf("%c", &c);
    printf("You typed '%c'\n", c);

    char name[50];
    printf("\nEnter a name: ");
    scanf("%s", name);
    printf("Well, hello there %s!\n", name);

    return 0;
}