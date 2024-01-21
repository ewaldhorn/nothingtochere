#include <stdio.h>

void intro();
void outtro();
void hugWord(char* word);

int main() {
    intro();

    hugWord("blue");
    hugWord("red");
    hugWord("orange");
    hugWord("green");
    hugWord("red");
    hugWord("blue");

    outtro();
    return 0;
}

void intro() {
    printf("Yellow yellow!\n\n");
}

void outtro() {
    printf("\nOk bye bye!\n");
}

void hugWord(char* word) {
    printf("[%s]\n", word);
}