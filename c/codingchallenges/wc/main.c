#include <stdio.h>
#include <stdlib.h>

#include "app_lib.h"

int main(int argc, char **argv) {
  printf("We received %lld.\n", getCharacterCount());
  return EXIT_SUCCESS;
}
