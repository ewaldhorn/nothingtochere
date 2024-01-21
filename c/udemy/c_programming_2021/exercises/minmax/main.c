/**
 * Write a program that reads 10 positive real numbers.
 * It must show the min, max and average of the numbers.
 **/
#include <stdio.h>
#include <stdlib.h>

int main() {
  int min = 0;
  int max = 0;
  int runningTotal = 0;
  int input = 0;

  for (int i = 0; i < 10; i++) {
    printf("Enter number %d: ", i+1);
    scanf("%d", &input);

    if (i == 0) {
      min = input;
      max = input;
      runningTotal = input;
    } else {
      runningTotal += input;

      if (input < min) { min=input; }
      if (input > max) { max=input; }
    }
  }

  printf("The min is %3d\n", min);
  printf("The max is %3d\n", max);
  printf("The avg is %3d\n", runningTotal/10);

  printf("\n");

  return 0;
}
