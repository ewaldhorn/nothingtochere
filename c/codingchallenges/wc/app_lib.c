#include "app_lib.h"
#include <stdint.h>
#include <stdio.h>

// --------------------------------------------------------- openFileForReading
FILE *openFileForReading(char *filename) {
  FILE *filePtr = fopen(filename, "r");

  if (filePtr == NULL) {
    return NULL;
  }

  return filePtr;
}

// ---------------------------------------------------------- getCharacterCount
int64_t getCharacterCount(char *filename) {
  int64_t count = FILE_ERROR;
  FILE *filePtr = openFileForReading(filename);
  char ch;

  if (filePtr != NULL) {
    count = 0;

    while ((ch = fgetc(filePtr)) != EOF) {
      count += 1;
    }

    fclose(filePtr);
  }

  return count;
}
