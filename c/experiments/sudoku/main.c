#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "tools.h"

// ----------------------------------------------------------------------------
int main(int argc, char *argv[]) {

  char *input = checkInputs(argc, argv);

  if (input == NULL) {
    return EXIT_FAILURE;
  }

  printf("The input puzzle:\n");
  printAsPuzzle(input);

  int board[9][9];

  // create the board
  populateBoard(board, input);
  printf("Becomes a board:\n");
  printBoard(board);
  printf("\n");

  printf("=======================\n");
  printf("Calculation solution...\n");
  solveSudoku(board);
  printBoard(board);
  printBoardAsString(board);

  printf("\n");

  return EXIT_SUCCESS;
}
