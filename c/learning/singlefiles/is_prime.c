#include <math.h>
#include <stdio.h>
#include <stdlib.h>

void isPrime(int number) {
  if (number <= 2 || number % 2 == 0) {
    printf("%4d is not prime!\n", number);
    return;
  } else {
    int d, s = floor(sqrt(number));
    for (d = 3; d * d <= s; d += 2) {
      if (number % d == 0) {
        printf("%4d is not prime!\n", number);
        return;
      }
    }

    printf("%4d is prime!\n", number);
  }
}

int main() {
  for (int i = 0; i <= 50; i++) {
    isPrime(i);
  }
  return EXIT_SUCCESS;
}
