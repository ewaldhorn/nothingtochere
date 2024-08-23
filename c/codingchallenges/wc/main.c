#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include "app_lib.h"

// -------------------------------------------------------------------- Globals
char *filename;

// ----------------------------------------------------------- handle_arguments
int handle_arguments(int count, char *arguments[]) {
  if (count < 2) {
    puts("Usage: ccwc [option] <filename>\n");
    return NOT_ENOUGH_ARGUMENTS;
  }

  if (count == 2) {
    filename = arguments[1];
  } else if (count == 3) {
    // printf("Option is [%s]\n", arguments[1]);
    filename = arguments[2];
  }

  return ALL_GOOD;
}

// ======================================================================= main
int main(int argc, char **argv) {
  if (handle_arguments(argc, argv) != ALL_GOOD) {
    puts("So much of NO!");
  } else {
    int64_t characterCount = getCharacterCount(filename);

    if (characterCount >= 0) {
      printf(
          "We received %lld character%s as the character count for \"%s\".\n",
          characterCount, characterCount != 1 ? "s" : "", filename);
    } else {
      printf("Unable to open \"%s\" for reading.\n", filename);
      return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
  }
}
