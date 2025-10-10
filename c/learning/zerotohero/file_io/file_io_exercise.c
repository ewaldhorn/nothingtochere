#include <stdio.h>
#include <stdlib.h>

void print_the_flag() {
  FILE *file = fopen("/temp/flag", "r");
  if (file == NULL) {
    perror("fopen");
    exit(EXIT_FAILURE);
  }

  // create buffer, zero it out
  char readBuffer[2000];
  for (int i = 0; i < sizeof(readBuffer); i++) {
    readBuffer[i] = 0;
  }

  size_t bytesRead = fread(readBuffer, 1, sizeof(readBuffer) - 1, file);
  if (ferror(file)) {
    perror("fread");
    fclose(file);
    exit(EXIT_FAILURE);
  }

  // Null-terminate the string to be safe
  readBuffer[bytesRead] = '\0';
  printf("%s\n", readBuffer);

  int didClose = fclose(file);
  if (didClose == EOF) {
    perror("fclose");
    exit(EXIT_FAILURE);
  }
}

// ------------------------------------------------------------------------------------------------
int main() { print_the_flag(); }
