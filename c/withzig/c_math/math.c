#include <stdlib.h>
#include <stdio.h>

int main(void) {
    double initial = 10.0;
    double total = initial;
    double rate = 0.05;
    int term = 24;

    for (size_t i = 1; i <= 24; i++) {
        total = total + (total * rate);
    }

    printf("\n\nInitial investment: R%.2lf.\n", initial);
    printf("Interest at %.0lf%% per year over %d years.\n", (rate*100), term);
    printf("Final amount is: R%.2lf.\n", total);

    return EXIT_SUCCESS;
}