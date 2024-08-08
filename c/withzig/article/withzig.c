#include <stdio.h>
#include <stdlib.h>

int summer(int left, int right) {
  return left + right;
}

int main() {
  int value1 = 12;
  int value2 = 30;

  printf("The sum of %d and %d is %d.\n", value1, value2, summer(value1, value2));

  return EXIT_SUCCESS;
}
