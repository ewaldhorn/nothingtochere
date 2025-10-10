#include <stdio.h>
#include <stdlib.h>

int main() {
  int *ptr = (int *)malloc(sizeof(int));
  if (ptr == NULL) {
    printf("Memory allocation failed\\n");
    return 1;
  }

  *ptr = 42;
  printf("Value: %d, Address: %p\\n", *ptr, (void *)ptr);
  free(ptr);
  ptr = NULL;

  return 0;
}
