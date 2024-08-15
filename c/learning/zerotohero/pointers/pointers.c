#include <stdio.h>
#include <stdlib.h>
// --------------------------------------------------------------------- struct
struct person_t {
  int id;
  int paygrade;
  char *name;
};

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

// ---------------------------------------------------------- upgrade_pay_grade
void upgrade_pay_grade(struct person_t *person, int increase) {
  person->paygrade += increase;
}

// -------------------------------------------------------------- more_pointers
void more_pointers(void) {
  struct person_t operator;

  operator.id = 10;
  operator.paygrade = 1;
  operator.name = "Kaspaas";

  puts("\nOperater details:");
  printf("ID   : %d\nName : %s\nGrade: %d\n", operator.id, operator.name,
                                                           operator.paygrade);

  upgrade_pay_grade(&operator, 2);

  puts("\nOperater updated details:");
  printf("ID   : %d\nName : %s\nGrade: %d\n", operator.id, operator.name,
                                                           operator.paygrade);
}

// ======================================================================= main
int main() {
  simple_pointer();
  more_pointers();

  return EXIT_SUCCESS;
}
