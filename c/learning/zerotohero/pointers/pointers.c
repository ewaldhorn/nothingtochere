#include <stdio.h>
#include <stdlib.h>

// ------------------------------------------------------------- simple_pointer
void simple_pointer(void) {
  int number = 10;
  int *pointerToNumber = &number;

  printf("The address of number is: %p\n", &number);
  printf("The pointer points to   : %p\n", pointerToNumber);
  printf("The value of the number is : %d\n", number);
  printf("The value of the pointer is: %d\n", *pointerToNumber);

  printf("\nNow we change number by adding one.\n");
  number += 1;
  printf("The address of number is: %p\n", &number);
  printf("The pointer points to   : %p\n", pointerToNumber);
  printf("The value of the number is : %d\n", number);
  printf("The value of the pointer is: %d\n", *pointerToNumber);

  printf("\nNow we change pointer value by adding one.\n");
  *pointerToNumber += 1;
  printf("The address of number is: %p\n", &number);
  printf("The pointer points to   : %p\n", pointerToNumber);
  printf("The value of the number is : %d\n", number);
  printf("The value of the pointer is: %d\n", *pointerToNumber);
}

// -------------------------------------------------------------- more_pointers
void more_pointers(void) {}

// ======================================================================= main
int main() {
  simple_pointer();

  return EXIT_SUCCESS;
}
