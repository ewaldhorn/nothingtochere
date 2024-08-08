#include <stdlib.h>
#include <stdio.h>

#define DEBUG

int main() {
  #ifdef DEBUG
    printf("In debug mode on line %d in file %s\n", __LINE__, __FILE__);
  #endif
  return EXIT_SUCCESS;
}
