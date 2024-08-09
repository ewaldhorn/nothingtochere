#include <stdlib.h>
#include <stdio.h>

void processUserInput();

// ======================================================================= main
int main() {
  processUserInput();

  return EXIT_SUCCESS;
}

// ----------------------------------------------------------- processUserInput
void processUserInput() {
  int position = 0, count = 0;
  int maximum = 0, number = 0;

  printf("How many values do you have?: ");
  scanf("%d", &count);

  while (position < count) {
    printf("Number %2d: ", position + 1);
    scanf("%d", &number);

    if (number > maximum) {
      maximum = number;
    }

    position += 1;
  }

  printf("\nThe maximum number is %d.\n", maximum);
}
