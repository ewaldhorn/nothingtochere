#include <stdlib.h>
#include <stdio.h>

int main(void) {

    int born, current;

    printf("\nEnter the born and current years, separated by a space: ");
    scanf("%d %d", &born, &current);

    printf("\nSomeone born in %d will be %d years old in %d.\n\n", born, current-born, current);

    return EXIT_SUCCESS;
}