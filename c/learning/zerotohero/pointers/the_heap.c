#include <malloc/_malloc_type.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
// --------------------------------------------------------------------- struct
struct person_t {
  int id;
  int paygrade;
  char *name;
};

// -------------------------------------------------------------- allocate_free
void allocate_free(void) {
  puts("\nAllocate and Free memory.\n");

  struct person_t *person = NULL;
  printf("Person address is : %p\n", person);

  person = malloc(sizeof(struct person_t));

  if (person == NULL) {
    puts("Unable to allocate memory!");
  }
  printf("Person address is : %p\n", person);
  free(person);
  printf("Person address is : %p\n", person);
  person = NULL;
  printf("Person address is : %p\n\n", person);
}

// ======================================================================= main
int main() {
  allocate_free();
  return EXIT_SUCCESS;
}
