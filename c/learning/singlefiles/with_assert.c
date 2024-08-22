#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

void isEvenOrOdd(int number) {
  printf("%d is ", number);

  assert(number >= 0 && "number was negative");

  if (number % 2 == 0) {
    puts("Even");
  } else {
    puts("Odd");
  }
}

int main() {
  isEvenOrOdd(15);
  isEvenOrOdd(-10);
  return EXIT_SUCCESS;
}
