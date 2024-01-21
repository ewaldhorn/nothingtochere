#include <stdio.h>
#include <string.h>

int main() {
  char myString[] = "Any string";

  printf("\n");
  printf("The string is `%s`.\n", myString);
  printf("The length of the string is %lu characters.\n", strlen(myString));
  printf("The size of the string is %lu bytes, because of the terminator.\n", sizeof(myString));

  printf("\n");
  return 0;
}
