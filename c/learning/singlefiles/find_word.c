#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
  char *src = "The big bird watches the little cat closely.";
  char *tgt = "cat";

  puts("Looking for 'cat' in 'The big bird watches the little cat closely.'");

  char *answer = strstr(src, tgt);

  printf("The answer is '%s'\n", (answer == NULL) ? "<not found>" : answer);

  return EXIT_SUCCESS;
}
