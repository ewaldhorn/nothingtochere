#include <stdio.h>
#include <stdlib.h>

// ======================================================================= main
int main() {
  char *name;

  printf("Who goes there?: ");
  scanf("%20s", name);

  printf("Oh, hello there %s!\n", name);

  return EXIT_SUCCESS;
}
