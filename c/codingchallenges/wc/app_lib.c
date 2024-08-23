#include "app_lib.h"
#include <stdint.h>
#include <stdio.h>

int64_t getCharacterCount() {

  int64_t count = 0;
  FILE *filePtr;
  char *fname = "artofwar.txt";
  char ch;

  filePtr = fopen(fname, "r");
  if (filePtr == NULL) {
    puts("Error opening file.");
    return -1;
  }

  while ((ch = fgetc(filePtr)) != EOF) {
    count += 1;
  }

  fclose(filePtr);

  return count;
}
