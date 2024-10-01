#include "tools.h"
#include <stdio.h>
#include <string.h>

// ----------------------------------------------------------------------------
// Ensure inputs are valid
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
void printHelp(char *extraMessage) {
  printf("\n");

  if (extraMessage) {
    printf("Error: %s\n\n", extraMessage);
  }

  printf("\tUsage: solver <puzzle>\n");
  printf("\tWhere <puzzle is a string of 81 numbers, .'s for spaces.\n");
  printf("\n");
}

// ----------------------------------------------------------------------------
int containsInvalidCharacters(char *inputString) {
  int result = 0;

  for (int pos = 0; pos < strlen(inputString); pos++) {
    if ((inputString[pos] < '0' || inputString[pos] > '9') &&
        inputString[pos] != '.') {
      result += 1;
    }
  }

  return result;
}

// ----------------------------------------------------------------------------
void printAsPuzzle(char *inputString) {
  for (int pos = 0; pos <= 81; pos++) {
    if (inputString[pos] != '.') {
      printf("%c ", inputString[pos]);
    } else {
      printf("  ");
    }

    if ((pos + 1) % 9 == 0) {
      printf("\n");
    }
  }

  printf("\n");
}
