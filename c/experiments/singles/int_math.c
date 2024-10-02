// ----------------------------------------------------------------------------
#include <stdio.h>
int squareOf(int n) { return n * n; }

// ----------------------------------------------------------------------------
int cubeOf(int n) { return n * squareOf(n); }

// ----------------------------------------------------------------------------
void testNumbers(void) {

  printf("\n");
  for (int i = 1; i <= 50; i++) {
    printf("Testing %3d: Squared:%5d, Cubed:%7d\n", i, squareOf(i), cubeOf(i));
  }
  printf("\n");
}

// ----------------------------------------------------------------------------
int main() {
  testNumbers();
  return 0;
}
