#include <stdio.h>
#include <stdlib.h>

#include "app_lib.h"

char *filename;

int handle_arguments(int count, char *arguments[]) {
  if (count < 2) {
    puts("Usage: ccwc [option] <filename>\n");
    return NOT_ENOUGH_PARAMETERS;
  }

  if (count == 2) {
    printf("File is [%s]\n", arguments[1]);
    filename = arguments[1];
  } else if (count == 3) {
    printf("Option is [%s]\n", arguments[1]);
    printf("File is [%s]\n", arguments[2]);
    filename = arguments[2];
  }

  return ALL_GOOD;
}

int main(int argc, char **argv) {
  if (handle_arguments(argc, argv) != ALL_GOOD) {
    puts("Doh!");
  } else {
    printf("We received %lld byte(s) as the count.\n",
           getCharacterCount(filename));
  }
  return EXIT_SUCCESS;
}
