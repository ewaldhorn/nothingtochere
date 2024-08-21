#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#define ROWS 50000
#define COLUMNS 10000

int array2d[ROWS][COLUMNS];

// ---------------------------------------------------------------- report_size
void report_size(void) {
  printf("%d x %d == %d\n", ROWS, COLUMNS, ROWS * COLUMNS);
}

// ------------------------------------------------------------- populate_array
void populate_array(void) {
  for (int row = 0; row < ROWS; row++) {
    for (int col = 0; col < COLUMNS; col++) {
      array2d[row][col] = rand();
    }
  }
}

// ----------------------------------------------------- sum_and_populate_array
void sum_and_populate_array(void) {
  int64_t sum = 0;
  for (int row = 0; row < ROWS; row++) {
    for (int col = 0; col < COLUMNS; col++) {
      sum += array2d[row][col] = rand();
    }
  }
  printf("Sum is %lld\n", sum);
}

// ======================================================================= main
int main() {
  report_size();
  populate_array();
  sum_and_populate_array();
  return EXIT_SUCCESS;
}
