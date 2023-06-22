#include <stdio.h>

int main() {
    double nc;
    for (nc = 0.0; getchar() != EOF; ++nc) {
        printf("That was character #%.0lf\n", nc);
    }

    return 0;
}