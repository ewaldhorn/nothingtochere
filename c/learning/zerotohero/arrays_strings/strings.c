#include <stdio.h>
#include <stdlib.h>

// --------------------------------------------------------------- basic_string
void basic_string(void) {
  char *aString = "This is a string";
  printf("This prints a basic string: '%s'.\n", aString);
}

// ---------------------------------------------------------- string_from_array
void string_from_array(void) {
  char stringInArray[] = {'t', 'h', 'i', 's', ' ', 'i', 's', ' ', 'a',
                          ' ', 's', 't', 'r', 'i', 'n', 'g', 0};

  printf("The array string is: '%s'.\n", stringInArray);
}

// ------------------------------------------------------------ getStringLength
int getStringLength(char str[]) {
  int len = 0;

  while (str[len] != '\0') {
    len++;
  }

  return len;
}

// ======================================================================= main
int main() {
  basic_string();
  string_from_array();

  char *str = "This is my string with 37 characters.";
  int length = getStringLength(str);
  printf("The source string contains %d characters.\n", length);

  return EXIT_SUCCESS;
}
