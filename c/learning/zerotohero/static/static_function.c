#include <stdio.h>
#include <stdlib.h>

// ------------------------------------------------------------------------------------------------
int my_static_test() {
  static int i = 0;
  i++;

  return i;
}

// ------------------------------------------------------------------------------------------------
int main() {
  printf("First call gives  : %d\n", my_static_test());
  printf("Second call gives : %d\n", my_static_test());
  printf("Third call gives  : %d\n", my_static_test());

  return EXIT_SUCCESS;
}
