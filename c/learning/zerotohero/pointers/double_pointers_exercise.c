#include <stdio.h>
#include <stdlib.h>

/**
Correct this code to update the value in the heap
to 10 before giving the address to main
**/

int resizeArrayTo(int **ptr) {
  int value = 10;
  *ptr = (int *)malloc(sizeof(int));

  if (ptr == NULL) {
    fprintf(stderr, "Memory allocation failed\n");
    return -1;
  }

  **ptr = value;
  return 0;
}

int main() {
  int *ptr = NULL;
  if (0 != resizeArrayTo(&ptr)) {
    return -1;
  }

  if (ptr != NULL) {
    printf("Value: %d\n", *ptr);
    free(ptr);
  }

  return 0;
}
