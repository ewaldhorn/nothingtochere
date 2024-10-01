#include <malloc/_malloc_type.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/syslimits.h>

#include "tools.h"

int board[9][9];

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
// Populate board from input, spaces (.) become 0, others numbers
void populateBoard(char *inputString) {
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
void printBoard() {
  for (int col = 0; col < 9; col++) {
    for (int row = 0; row < 9; row++) {
      printf("%d ", board[col][row]);
    }
    printf("\n");
  }
}

// ----------------------------------------------------------------------------
int isValid(int row, int col, int num) {
  // check the line
  for (int i = 0; i < 9; i++) {
    if (board[row][i] == num) {
      return FALSE;
    }
  }

  // Check the column
  for (int i = 0; i < 9; i++) {
    if (board[i][col] == num) {
      return FALSE;
    }
  }

  // Check the box
  int startRow = row - row % 3;
  int startCol = col - col % 3;
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      if (board[i + startRow][j + startCol] == num) {
        return FALSE;
      }
    }
  }

  return TRUE;
}

// ----------------------------------------------------------------------------
int solveSudoku() {
  for (int row = 0; row < 9; row++) {
    for (int col = 0; col < 9; col++) {
      if (board[row][col] == 0) {
        for (int num = 1; num <= 9; num++) {
          if (isValid(row, col, num) == TRUE) {
            board[row][col] = num;
            if (solveSudoku() == TRUE) {
              return TRUE;
            } else {
              // that didn't work, reset
              board[row][col] = 0;
            }
          }
        }
        return FALSE;
      }
    }
  }

  return TRUE;
}

// ----------------------------------------------------------------------------
char *getBoardAsString() {
  char *buffer;
  buffer = malloc(82);

  for (int col = 0; col < 9; col++) {
    for (int row = 0; row < 9; row++) {
      buffer[col * 9 + row] = '0' + board[col][row];
    }
  }

  return buffer;
}

// ----------------------------------------------------------------------------
void printBoardAsString() {
  for (int row = 0; row < 9; row++) {
    for (int col = 0; col < 9; col++) {
      printf("%d", board[row][col]);
    }
  }
  printf("\n");
}

// ----------------------------------------------------------------------------
int main(int argc, char *argv[]) {

  char *input = checkInputs(argc, argv);

  if (input == NULL) {
    return EXIT_FAILURE;
  }

  printf("The input puzzle:\n");
  printAsPuzzle(input);

  // create the board
  populateBoard(input);
  printf("Becomes a board:\n");
  printBoard();
  printf("\n");

  printf("=======================\n");
  printf("Calculation solution...\n");
  solveSudoku();
  printBoard();

  printf("\n\n");
  printBoardAsString();
  char *expected = "53467891267219534819834256785976142342685379171392485696153"
                   "7284287419635345286179";
  printf("%s\n", expected);

  char *tmp = getBoardAsString();
  printf("%s\n", tmp);

  int diff = 0;

  for (int i = 0; i < strlen(expected); i++) {
    if (expected[i] != tmp[i]) {
      diff += 1;
    }
  }

  printf("Difference: %d\n", diff);

  return EXIT_SUCCESS;
}
