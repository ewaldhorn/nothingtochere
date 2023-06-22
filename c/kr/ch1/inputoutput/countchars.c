#include <stdio.h>

int main() {
    long nc = 0;

    while (getchar() != EOF) {
        ++nc;
        printf("That was character #%ld\n", nc);
    }

    return 0;
}
