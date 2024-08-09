#include <stdlib.h>
#include <stdio.h>
#include <string.h>

// ----------------------------------------------------- justPrintAStaticString
void justPrintAStaticString() {
  printf("C strings can be confusing!\n");
}

// ---------------------------------------------- printStringWithEscapedNewline
// Decimal 10, Hex 0A, is the newline character in ASCII
void printStringWithEscapedNewline() {
  printf("This newline is unusual...\x0A");
}

// ---------------------------------------------------- getStringLengthManually
int getStringLengthManually(char *str) {
  int charCount = 0;

  while(str[charCount] != 0) {
    charCount += 1;
  }

  return charCount;
}

// ------------------------------------------------------------------- makeCopy
void makeCopy(char *src, char *tgt) {
  int position = 0;

  while (src[position] != 0) {
    tgt[position] = src[position];
    position += 1;
  }

  tgt[position] = 0; // need to make sure our final string is null terminated
}

// -------------------------------------------------------------- reverseString
void reverseString(char *src, char *tgt) {
  int position = 0;
  int len = getStringLengthManually(src);

  while (position < len) {
    tgt[position] = src[len - position - 1];
    position += 1;
  }

  tgt[position] = 0;
}

// ======================================================================= main
int main() {
  justPrintAStaticString();
  printStringWithEscapedNewline();
  printf("The string '%s' contains %d characters. (manual)\n", "Alright", getStringLengthManually("Alright"));
  printf("The string '%s' contains %lu characters. (string.h)\n", "Alright", strlen("Alright"));

  char *src = "This is the source";
  char target[100];
  makeCopy(src, target);

  printf("Length of source is: %lu.\n", strlen(src));
  printf("Length of target is: %lu.\n", strlen(target));

  reverseString(src, target);
  printf("The reverse of '%s' is '%s'.\n", src, target);

  return EXIT_SUCCESS;
}
