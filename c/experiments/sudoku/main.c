#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "tools.h"

// ----------------------------------------------------------------------------
// Ensure inputs are valid
char *checkInputs(int argc, char *argv[]) {
  if (argc != 2) {
    printHelp(NULL);
    return NULL;
  }

  char *input = argv[1];

  if (strlen(input) != 81) {
    printHelp("Input is the wrong length.");
    return NULL;
  }

  int invalidCharCount = containsInvalidCharacters(input);

  if (invalidCharCount > 0) {
    printHelp("Input contains invalid characters.");
    return NULL;
  }

  return argv[1];
}
// ----------------------------------------------------------------------------
// Populate board from input, spaces become 0, others numbers
void populateBoard(int board[][9], char *inputString) {
  for (int col = 0; col < 9; col++) {
    for (int row = 0; row < 9; row++) {
      char tmp = inputString[col * 9 + row];
      if (tmp > '0' && tmp <= '9') {
        board[col][row] = tmp - '0';
      } else {
        board[col][row] = 0;
      }
    }
  }
}
// ----------------------------------------------------------------------------
// Display the board
void printBoard(int board[][9]) {
  for (int col = 0; col < 9; col++) {
    for (int row = 0; row < 9; row++) {
      printf("%d ", board[col][row]);
    }
    printf("\n");
  }
}
// ----------------------------------------------------------------------------
// ----------------------------------------------------------------------------
// ----------------------------------------------------------------------------
// ----------------------------------------------------------------------------
// ----------------------------------------------------------------------------
int main(int argc, char *argv[]) {

  char *input = checkInputs(argc, argv);

  if (input == NULL) {
    return EXIT_FAILURE;
  }

  printf("The input puzzle:\n");
  printAsPuzzle(input);

  printf("=======================\n");
  printf("Calculation solution...\n");

  // create the board
  int board[9][9];
  populateBoard(board, input);
  printBoard(board);

  return EXIT_SUCCESS;
}
