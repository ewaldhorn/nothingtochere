#include <stdio.h>
#include <stdlib.h>

int main() {
  printf("\nCount from 6 to 10 with a for loop: ");

  for (int i = 6; i <= 10; i++) {
    printf("%d ", i);
  }

  printf("\nNow with a while loop             : ");
  int i = 6;

  while (i <= 10) {
    printf("%d ", i);
    i += 1;
  }

  printf("\nAlso a do-while loop              : ");
  i = 6;
  do {
    printf("%d ", i);
    i += 1;
  } while (i < 11);

  printf("\n\nAll done!\n");
  return EXIT_SUCCESS;
}
