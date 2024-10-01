#ifndef __TOOLS_H_
#define __TOOLS_H_

#define TRUE 1
#define FALSE 0

char *checkInputs(int argc, char *argv[]);
void printHelp(char *extraMessage);
int containsInvalidCharacters(char *inputString);
void printAsPuzzle(char *inputString);
void populateBoard(int board[][9], char *inputString);
void printBoard(int board[][9]);
int isValid(int board[][9], int row, int col, int num);
char *getBoardAsString(int board[][9]);
void printBoardAsString(int board[][9]);
int solveSudoku(int board[][9]);

#endif
