#include <stdio.h>
#include <stdlib.h>

// ----------------------------------------------------------------- prototypes
void basic_array_operations(void);
int find_array_length(int arr[]);

// ======================================================================= main
int main() {
  basic_array_operations();

  return EXIT_SUCCESS;
}

// ----------------------------------------------------- basic_array_operations
void basic_array_operations() {
  int numbers[] = {1, 2, 3, 4};
  int lengthBySizeOf = sizeof(numbers) / sizeof(numbers[0]);
  int lengthByPointerMath = *(&numbers + 1) - numbers;
  int lengthByLoop = find_array_length(numbers);

  printf("%d: array size via sizeOf.\n", lengthBySizeOf);
  printf("%d: array size via pointer math.\n", lengthByPointerMath);
  printf("%d: array size via loop.\n", lengthByLoop);
}

// ---------------------------------------------------------- find_array_length
// won't work since memory wasn't set to 0
int find_array_length(int arr[]) {
  int size = 0;

  while (arr[size] != '\0') {
    size += 1;
  }

  return size;
}
