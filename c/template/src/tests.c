#include <stdio.h>
#include <stdlib.h>

#include "lib/my_math.h"

#define ENSURE(expr)                                                           \
  if (expr) {                                                                  \
    printf("\033[0;32mPASS: %s\n\033[0m", #expr);                              \
  } else {                                                                     \
    printf("\033[0;31mFAIL: %s\n\033[0m", #expr);                              \
  }

void display_header(void);
void display_footer(void);

void test_biggestOf(void) {
  puts("Testing biggest_Of");

  int left = 10, right = 8;

  int biggest = biggestOf(left, right);
  ENSURE(biggest == 10);

  biggest = biggestOf(right, left);
  ENSURE(biggest == 10);

  left = 7;
  biggest = biggestOf(right, left);
  ENSURE(biggest == 8);

  biggest = biggestOf(left, right);
  ENSURE(biggest == 8);
}

int main() {
  display_header();

  test_biggestOf();

  display_footer();
  return EXIT_SUCCESS;
}

void display_header(void) {
  puts("\nStarting tests.\n------------------------------\n");
}

void display_footer(void) {
  puts("\n______________________________\nCompleted tests.\n");
}
