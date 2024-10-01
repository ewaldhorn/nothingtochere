#include "tools.h"
#include <stdio.h>
#include <string.h>

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
