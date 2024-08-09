#include <stdio.h>
#include <stdlib.h>

// ------------------------------------------------------------- isAPrimeNumber
int isAPrimeNumber(int number) {

  if (number < 2) { // 0 and 1 are not primes, don't bother
    return EXIT_FAILURE;
  }

  for (int i = 2; i <= number / 2; ++i) {
    // if number is divisible by i, it's not a prime
    if (number % i == 0) {
      return EXIT_FAILURE;
    }
  }

  return EXIT_SUCCESS;
}

// ======================================================================= main
int main() {

  for (int i = 0; i <= 45; i++) {
    printf("%2d is%sa prime number.\n",
           i, (isAPrimeNumber(i) == EXIT_SUCCESS) ? " " : " not ");
  }

  return EXIT_SUCCESS;
}
