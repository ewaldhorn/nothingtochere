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

// --------------------------------------------------------------------- STRUCT
struct InputStruct {
  char *name;
  char *signal;
};

struct InstructionsStruct {
  char *name;
  char *gate;
  char *left;
  char *right;
};

// ======================================================================= MAIN
int main() {
  int inputSignals, outputSignals;
  scanf("%d", &inputSignals);
  scanf("%d", &outputSignals);

  struct InputStruct inputs[10];
  struct InstructionsStruct instructions[10];

  // read all the input signals
  for (int i = 0; i < inputSignals; i++) {
    char input_name[2];
    char input_signal[100];
    scanf("%s%s", input_name, input_signal);
    fprintf(stderr, "Read: %s %s\n", input_name, input_signal);
    inputs[i].name = input_name;
    inputs[i].signal = input_signal;
  }

  // now read all the output signals
  for (int i = 0; i < outputSignals; i++) {
    char output_name[9];
    char type[9];
    char input_name_1[9];
    char input_name_2[9];
    scanf("%s%s%s%s", output_name, type, input_name_1, input_name_2);
    fprintf(stderr, "Read %s %s %s %s\n", output_name, type, input_name_1,
            input_name_2);
    instructions[i].name = output_name;
    instructions[i].gate = type;
    instructions[i].left = input_name_1;
    instructions[i].right = input_name_2;
  }

  for (int i = 0; i < outputSignals; i++) {
    fprintf(stderr, "%s %s %s %s\n", instructions[i].name, instructions[i].gate,
            instructions[i].left, instructions[i].right);
  }

  // now process it
  for (int i = 0; i < outputSignals; i++) {
    printf("%s ", instructions[i].name);

    int len = strlen(instructions[i].left);
    for (int pos = 0; pos < len; pos++) {
    }

    printf("\n");
  }

  return 0;
}
