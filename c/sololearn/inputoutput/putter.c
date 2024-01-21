#include <stdio.h>

int main() {
    char spacer = '|';

    printf("Output five characters:\n");
    for (int i = 0; i < 5; i++) {
        putchar(spacer);
    }

    char myString[] = "Yolo";

    printf("\n");
    printf("Output a string three times:\n");
    for (int i = 0; i < 3; i++) {
        puts(myString);
    }

    return 0;
}