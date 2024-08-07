#include <stdlib.h>
#include <stdio.h>

// ----------------------------------------------------------------- Solution 1
float findMaxOf(float a, float b, float c) {
  if (a > b) {
    if (a > c) {
      return a;
    } else {
      return c;
    }
  } else {
    if (b > c) {
      return b;
    } else {
      return c;
    }
  }
}

// ----------------------------------------------------------------- Solution 2
float findMaxOfShorter(float a, float b, float c) {
  float max = a;

  if (b > max) max = b;
  if (c > max) max = c;

  return max;
}

// ======================================================================= main
int main() {
  float a = 2.0, b = 3.0, c = 5.0;

  printf("Solution 1: The biggest of %.1f, %.1f and %.1f is: %.1f\n", a, b, c, findMaxOf(a, b, c));
  printf("Solution 2: The biggest of %.1f, %.1f and %.1f is: %.1f\n", a, b, c, findMaxOfShorter(a, b, c));

  return EXIT_SUCCESS;
}
