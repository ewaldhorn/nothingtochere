#include <stdlib.h>
#include <string.h>

#include "tools.h"

int main(int argc, char *argv[]) {
  if (argc != 2) {
    printHelp(NULL);
    return EXIT_SUCCESS;
  }

  char *input = argv[1];

  if (strlen(input) != 81) {
    printHelp("Input is troublesome.");
    return EXIT_FAILURE;
  }

  int invalidCharCount = containsInvalidCharacters(input);

  if (invalidCharCount > 0) {
    printHelp("Input contains invalid characters.");
    return EXIT_FAILURE;
  }

  return EXIT_SUCCESS;
}
