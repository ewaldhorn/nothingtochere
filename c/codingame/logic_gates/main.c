#include <stdbool.h>
#include <stdio.h>
#include <string.h>

// --------------------------------------------------------------------- DEFINE
#define TRUE "-"
#define FALSE "_"

// ------------------------------------------------------------------------ AND
char *AND(char *left, char *right) {
  if (strcmp(left, TRUE) && (strcmp(right, TRUE))) {
    return TRUE;
  } else {
    return FALSE;
  }
}

// ------------------------------------------------------------------------- OR
char *OR(char *left, char *right) {
  if (strcmp(left, TRUE) || strcmp(right, TRUE)) {
    return TRUE;
  } else {
    return FALSE;
  }
}

// ------------------------------------------------------------------------ XOR
char *XOR(char *left, char *right) {
  if ((strcmp(left, TRUE) && strcmp(right, FALSE)) ||
      (strcmp(left, FALSE) && strcmp(right, TRUE))) {
    return TRUE;
  } else {
    return FALSE;
  }
}

// ----------------------------------------------------------------------- NAND
char *NAND(char *left, char *right) {
  if (strcmp(AND(left, right), TRUE)) {
    return FALSE;
  } else {
    return TRUE;
  }
}

// ------------------------------------------------------------------------ NOR
char *NOR(char *left, char *right) {
  if (strcmp(OR(left, right), TRUE)) {
    return FALSE;
  } else {
    return TRUE;
  }
}

// ----------------------------------------------------------------------- NXOR
char *NXOR(char *left, char *right) {
  if (strcmp(XOR(left, right), TRUE)) {
    return FALSE;
  } else {
    return TRUE;
  }
}

// ======================================================================= MAIN
int main() {
  int inputSignals, outputSignals;
  scanf("%d", &inputSignals);
  scanf("%d", &outputSignals);

  for (int i = 0; i < inputSignals; i++) {
    char input_name[9];
    char input_signal[65];
    scanf("%s%s", input_name, input_signal);
  }

  for (int i = 0; i < outputSignals; i++) {
    char output_name[9];
    char type[9];
    char input_name_1[9];
    char input_name_2[9];
    scanf("%s%s%s%s", output_name, type, input_name_1, input_name_2);
  }

  for (int i = 0; i < outputSignals; i++) {

    // Write an answer using printf(). DON'T FORGET THE TRAILING \n
    // To debug: fprintf(stderr, "Debug messages...\n");

    printf("output name and signal\n");
  }

  return 0;
}
