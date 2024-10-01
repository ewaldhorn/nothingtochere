#include "tools.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ENSURE(expr)                                                           \
  if (expr) {                                                                  \
    printf("\033[0;32mPASS: %s\n\033[0m", #expr);                              \
  } else {                                                                     \
    printf("\033[0;31mFAIL: %s\n\033[0m", #expr);                              \
  }

void display_header(void);
void display_footer(void);

// ----------------------------------------------------------------------------
void test_one(void) {
  char *input = "53..7....6..195....98....6.8...6...34..8.3..17...2...6.6...."
                "28....419..5....8..79";
  char *expected = "53467891267219534819834256785976142342685379171392485696153"
                   "7284287419635345286179";

  int board[9][9];

  // create the board
  populateBoard(board, input);
  solveSudoku(board);
  char *tmp = getBoardAsString(board);

  int diff = 0;

  for (int i = 0; i < strlen(expected); i++) {
    if (expected[i] != tmp[i]) {
      diff += 1;
    }
  }

  ENSURE(diff == 0);
}

// ----------------------------------------------------------------------------
void test_two(void) {
  char *input = "4.....8.5.3..........7......2.....6.....8.4......1.......6.3."
                "7.5..2.....1.4......";
  char *expected = "41736982563215894795872431682543716979158643234691275828964"
                   "3571573291684164875293";

  int board[9][9];

  // create the board
  populateBoard(board, input);
  solveSudoku(board);
  char *tmp = getBoardAsString(board);

  int diff = 0;

  for (int i = 0; i < strlen(expected); i++) {
    if (expected[i] != tmp[i]) {
      diff += 1;
    }
  }

  ENSURE(diff == 0);
}

int main() {
  display_header();

  test_one();
  test_two();

  display_footer();
  return EXIT_SUCCESS;
}

void display_header(void) {
  puts("\nStarting tests.\n------------------------------\n");
}

void display_footer(void) {
  puts("\n______________________________\nCompleted tests.\n");
}
