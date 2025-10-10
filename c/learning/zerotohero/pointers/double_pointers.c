#include <stdio.h>
#include <stdlib.h>

// ---------------------------------------------------- change_incoming_pointer
void change_incoming_pointer(int **ptr) {
  int otherNumber = 11;
  int *other_ptr = &otherNumber;
  **ptr = otherNumber;
}

// ------------------------------------------------------- pointers_to_pointers
void pointers_to_pointers(void) {
  int number = 10;
  int *ptr_to_number = &number;
  int **ptr_to_ptr_to_number = &ptr_to_number;

  printf("The number is             : %d\n", number);
  printf("It's address is           : %p\n", ptr_to_number);
  printf("The ptr_to_ptr points to  : %p\n", ptr_to_ptr_to_number);
  printf("The value at ptr_to_number: %d\n", *ptr_to_number);

  puts("Now we assign a new value");
  change_incoming_pointer(ptr_to_ptr_to_number);

  printf("The number is             : %d\n", number);
  printf("It's address is           : %p\n", ptr_to_number);
  printf("The ptr_to_ptr points to  : %p\n", ptr_to_ptr_to_number);
  printf("The value at ptr_to_number: %d\n", *ptr_to_number);
}

// ======================================================================= main
int main() {
  pointers_to_pointers();
  return EXIT_SUCCESS;
}
