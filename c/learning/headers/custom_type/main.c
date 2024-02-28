#include <stdio.h>
#include "person.h"

int main() {
    person p;

    p.id = 3;
    p.score = 4;

    printf("We have %d for the score.\n", p.score);

    return 0;
}