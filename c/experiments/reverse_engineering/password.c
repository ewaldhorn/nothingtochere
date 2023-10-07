#include <stdio.h>

int getPass(char *b) {}

int main(int argc, char **argv) 
{
    char buffer[64];

    printf("Just something to crack!\n");
    printf("Give me your password:");
    scanf("%64s", buffer);

    if (getPass(buffer)) {
        printf("Great job!\n");
    }
}