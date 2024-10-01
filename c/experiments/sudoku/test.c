#include <stdio.h>
#include <stdlib.h>

#define ENSURE(expr)                                                           \
  if (expr) {                                                                  \
    printf("\033[0;32mPASS: %s\n\033[0m", #expr);                              \
  } else {                                                                     \
    printf("\033[0;31mFAIL: %s\n\033[0m", #expr);                              \
  }

void display_header(void);
void display_footer(void);

int main() {
  display_header();

  display_footer();
  return EXIT_SUCCESS;
}

void display_header(void) {
  puts("\nStarting tests.\n------------------------------\n");
}

void display_footer(void) {
  puts("\n______________________________\nCompleted tests.\n");
}
