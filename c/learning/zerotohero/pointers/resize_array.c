#include <stdio.h>
#include <stdlib.h>

// ------------------------------------------------------------------------------------------------
typedef enum {
  STATUS_GOOD,
  STATUS_BAD,
} status_t;

// ------------------------------------------------------------------------------------------------
status_t resizeArrayTo(int **arr, size_t new_size) {
  int *temp = realloc(*arr, new_size * sizeof(int));
  if (temp == NULL) {
    // Handle realloc failure
    printf("Memory allocation failed\n");
    return STATUS_BAD;
  }

  // Ok, it worked, return the new pointer
  *arr = temp;

  return STATUS_GOOD;
}

// ------------------------------------------------------------------------------------------------
int main() {
  size_t initial_size = 5;
  size_t new_size = 10;

  int *arr = malloc(initial_size * sizeof(int));
  if (arr == NULL) {
    printf("Memory allocation failed\n");
    return 1;
  }

  // Initialize the array
  for (size_t i = 0; i < initial_size; i++) {
    arr[i] = i;
  }

  // Print the initial array
  printf("Initial array:\n");
  for (size_t i = 0; i < initial_size; i++) {
    printf("%d ", arr[i]);
  }
  printf("\n");

  // Call resizeArrayTo to resize the array
  if (STATUS_BAD == resizeArrayTo(&arr, new_size)) {
    printf("uh oh");
    return -1;
  }

  // Initialize the new part of the array
  for (size_t i = initial_size; i < new_size; i++) {
    arr[i] = i;
  }

  // Print the resized array
  printf("Resized array:\n");
  for (size_t i = 0; i < new_size; i++) {
    printf("%d ", arr[i]);
  }
  printf("\n");

  free(arr);
  arr = NULL;

  return EXIT_SUCCESS;
}
