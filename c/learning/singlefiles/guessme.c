#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main() {
    /* Intializes random number generator */
    time_t t;
    srand((unsigned) time(&t));

    int target = 1 + (rand()%100);

    int guesses = 0;
    int guess = -1;

    do {
        printf("Guess a number between 1-100: ");
        scanf("%d", &guess);

        if (guess < target) {
            printf("Too low!\n");
        } else if (guess > target) {
            printf("Too high!\n");
        }
        guesses++;

    } while (guess != target);

    printf("\nYou needed %d guesses!\n", guesses);
    return 0;
}