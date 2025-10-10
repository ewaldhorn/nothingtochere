#include <stdio.h>
#include <stdlib.h>

// I asked Gemini to split the code into functions.
// --- Function Prototypes ---

/**
 * @brief Allocates memory for an integer and initializes it.
 *
 * @param initial_value The value to store in the allocated memory.
 * @return A pointer to the newly allocated integer, or NULL if allocation
 * fails.
 */
int *create_integer(int initial_value);

/**
 * @brief Prints the value and memory address of an integer pointer.
 *
 * @param ptr A constant pointer to the integer to print. The function will not
 * modify the integer's value.
 */
void print_integer_details(const int *ptr);

/**
 * @brief Frees the memory pointed to by the pointer and sets the original
 * pointer to NULL.
 *
 * @param ptr_address A pointer to the pointer that needs to be freed.
 */
void safe_free_integer(int **ptr_address);

// --- Main Function ---

int main() {
  int *my_int = create_integer(42);
  if (my_int == NULL) {
    return 1; // Exit if creation failed.
  }

  print_integer_details(my_int);
  safe_free_integer(&my_int);

  // You can verify that the pointer is now NULL
  if (my_int == NULL) {
    printf("Pointer has been successfully set to NULL.\n");
  }

  return 0;
}

// --- Function Implementations ---

int *create_integer(int initial_value) {
  int *ptr = (int *)malloc(sizeof(int));
  if (ptr == NULL) {
    printf("Memory allocation failed\n");
    return NULL;
  }
  *ptr = initial_value;
  return ptr;
}

void print_integer_details(const int *ptr) {
  if (ptr == NULL) {
    printf("Provided pointer is NULL.\n");
    return;
  }
  // Note: We cast ptr to (void*) for printing because %p expects a void
  // pointer.
  printf("Value: %d, Address: %p\n", *ptr, (void *)ptr);
}

void safe_free_integer(int **ptr_address) {
  // Check if the pointer-to-pointer is not NULL and the pointer it holds is not
  // NULL
  if (ptr_address != NULL && *ptr_address != NULL) {
    free(*ptr_address);
    *ptr_address = NULL; // Set the original pointer in main() to NULL
  }
}
