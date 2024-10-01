#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "tools.h"

// ----------------------------------------------------------------------------
char *checkInputs(int argc, char *argv[]) {
  if (argc != 2) {
    printHelp(NULL);
    return NULL;
  }

  char *input = argv[1];

  if (strlen(input) != 81) {
    printHelp("Input is the wrong length.");
    return NULL;
  }

  int invalidCharCount = containsInvalidCharacters(input);

  if (invalidCharCount > 0) {
    printHelp("Input contains invalid characters.");
    return NULL;
  }

  return argv[1];
}
// ----------------------------------------------------------------------------
// ----------------------------------------------------------------------------
// ----------------------------------------------------------------------------
int main(int argc, char *argv[]) {

  char *input = checkInputs(argc, argv);

  if (input == NULL) {
    return EXIT_FAILURE;
  }

  printf("The input puzzle:\n");
  printAsPuzzle(input);

  printf("=======================\n");
  printf("Calculation solution...\n");

  return EXIT_SUCCESS;
}
