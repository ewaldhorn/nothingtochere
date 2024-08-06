#include <stdio.h>

// ----------------------------------------------------------------- fizzOrBuzz
char* fizzOrBuzz(int n) {
  char *result;

  if (n % 15 == 0) {
    asprintf(&result, "FizzBuzz");
  } else if (n % 3 == 0) {
    asprintf(&result, "Fizz");
  } else if (n % 5 == 0) {
    asprintf(&result, "Buzz");
  } else {
    asprintf(&result, "%d", n);
  }

  return result;
}

// ======================================================================= main
int main() {
  printf("Fizz or Buzz?\n");

  for (int i = 1; i <= 15; i++) {
    printf("%d gives %s\n", i, fizzOrBuzz(i));
  }

  return 0;
}
