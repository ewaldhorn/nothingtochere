#include <stdio.h>
#include <string.h>

// --------------------------------------------------------- reportStringLength
void reportStringLength(char *str) {
  printf("The string '%s' contains %lu characters.\n", str, strlen(str));
}

// ------------------------------------------------------------ getStringLength
unsigned long getStringLength(char *str) { return strlen(str); }
