#include <stdio.h>
#include <stdlib.h>

#include "app_lib.h"

int main(int argc, char **argv) {
  printf("We received %lld byte(s) as the count.\n", getCharacterCount());
  return EXIT_SUCCESS;
}
