#include "tools.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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
void printHelp(char *extraMessage) {
  printf("\n");

  if (extraMessage) {
    printf("Error: %s\n\n", extraMessage);
  }

  printf("\tUsage: solver <puzzle>\n");
  printf("\tWhere <puzzle is a string of 81 numbers, .'s for spaces.\n");
  printf("\n");
}

// ----------------------------------------------------------------------------
int containsInvalidCharacters(char *inputString) {
  int result = 0;

  for (int pos = 0; pos < strlen(inputString); pos++) {
    if ((inputString[pos] < '0' || inputString[pos] > '9') &&
        inputString[pos] != '.') {
      result += 1;
    }
  }

  return result;
}

// ----------------------------------------------------------------------------
void printAsPuzzle(char *inputString) {
  for (int pos = 0; pos <= 81; pos++) {
    if (inputString[pos] != '.') {
      printf("%c ", inputString[pos]);
    } else {
      printf("  ");
    }

    if ((pos + 1) % 9 == 0) {
      printf("\n");
    }
  }

  printf("\n");
}

// ----------------------------------------------------------------------------
// Populate board from input, spaces (.) become 0, others numbers
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
int isValid(int board[][9], int row, int col, int num) {
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
char *getBoardAsString(int board[][9]) {
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
void printBoardAsString(int board[][9]) {
  for (int row = 0; row < 9; row++) {
    for (int col = 0; col < 9; col++) {
      printf("%d", board[row][col]);
    }
  }
  printf("\n");
}

// ----------------------------------------------------------------------------
int solveSudoku(int board[][9]) {
  for (int row = 0; row < 9; row++) {
    for (int col = 0; col < 9; col++) {
      if (board[row][col] == 0) {
        for (int num = 1; num <= 9; num++) {
          if (isValid(board, row, col, num) == TRUE) {
            board[row][col] = num;
            if (solveSudoku(board) == TRUE) {
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
