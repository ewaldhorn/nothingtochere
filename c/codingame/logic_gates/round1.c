#include <stdbool.h>
#include <stdio.h>
#include <string.h>

// --------------------------------------------------------------------- DEFINE
#define TRUE '-'
#define FALSE '_'

// ----------------------------------------------------------------------- ENUM
enum gates { andgate, orgate, xorgate, nandgate, norgate, nxorgate };

// --------------------------------------------------------------------- STRUCT
struct InputStruct {
  char name[100];
  char signal[100];
};

struct InstructionsStruct {
  char name[100];
  char gate[100];
  char left[100];
  char right[100];
};

// ------------------------------------------------------------------------ AND
char AND(char left, char right) {
  if ((left == TRUE) && (right == TRUE)) {
    return TRUE;
  } else {
    return FALSE;
  }
}

// ------------------------------------------------------------------------- OR
char OR(char left, char right) {
  if ((left == TRUE) || (right == TRUE)) {
    return TRUE;
  } else {
    return FALSE;
  }
}

// ------------------------------------------------------------------------ XOR
char XOR(char left, char right) {
  if (((left == TRUE) && (right == FALSE)) ||
      ((left == FALSE) && (right == TRUE))) {
    return TRUE;
  } else {
    return FALSE;
  }
}

// ----------------------------------------------------------------------- NAND
char NAND(char left, char right) {
  if ((AND(left, right) == TRUE)) {
    return FALSE;
  } else {
    return TRUE;
  }
}

// ------------------------------------------------------------------------ NOR
char NOR(char left, char right) {
  if ((OR(left, right) == TRUE)) {
    return FALSE;
  } else {
    return TRUE;
  }
}

// ----------------------------------------------------------------------- NXOR
char NXOR(char left, char right) {
  if ((XOR(left, right) == TRUE)) {
    return FALSE;
  } else {
    return TRUE;
  }
}

// ---------------------------------------------------------------- getGateType
enum gates getGateType(char *gate) {
  enum gates gatetype;

  if (strcmp(gate, "AND") == 0) {
    gatetype = andgate;
  } else if (strcmp(gate, "OR") == 0) {
    gatetype = orgate;
  } else if (strcmp(gate, "XOR") == 0) {
    gatetype = xorgate;
  } else if (strcmp(gate, "NAND") == 0) {
    gatetype = nandgate;
  } else if (strcmp(gate, "NOR") == 0) {
    gatetype = norgate;
  } else if (strcmp(gate, "NXOR") == 0) {
    gatetype = nxorgate;
  }

  return gatetype;
}

// ----------------------------------------------------------- getInputPosition
int getInputPosition(char *inputName, int inputCount,
                     struct InputStruct inputs[]) {
  int result = 0;

  for (int i = 0; i < inputCount; i++) {
    if (strcmp(inputName, inputs[i].name) == 0) {
      result = i;
      break;
    }
  }

  return result;
}

// ======================================================================= MAIN
int main() {
  int inputSignals, outputSignals;
  scanf("%d", &inputSignals);
  scanf("%d", &outputSignals);

  struct InputStruct inputs[20];
  struct InstructionsStruct instructions[20];

  // read all the input signals
  for (int i = 0; i < inputSignals; i++) {
    char input_name[100];
    char input_signal[100];
    scanf("%s%s", input_name, input_signal);

    strcpy(inputs[i].name, input_name);
    strcpy(inputs[i].signal, input_signal);
  }

  // now read all the output signals
  for (int i = 0; i < outputSignals; i++) {
    char output_name[100];
    char type[100];
    char input_name_1[100];
    char input_name_2[100];
    scanf("%s%s%s%s", output_name, type, input_name_1, input_name_2);

    strcpy(instructions[i].name, output_name);
    strcpy(instructions[i].gate, type);
    strcpy(instructions[i].left, input_name_1);
    strcpy(instructions[i].right, input_name_2);
  }

  // now process it
  for (int i = 0; i < outputSignals; i++) {
    printf("%s ", instructions[i].name);
    enum gates gateType = getGateType(instructions[i].gate);

    int leftInput =
        getInputPosition(instructions[i].left, inputSignals, inputs);
    int rightInput =
        getInputPosition(instructions[i].right, inputSignals, inputs);

    int len = strlen(inputs[leftInput].signal);

    // DEBUG CODE
    // fprintf(stderr, "%d Looking at %s of type %s with inputs %s and %s\n", i,
    //         instructions[i].name, instructions[i].gate, instructions[i].left,
    //         instructions[i].right);

    for (int pos = 0; pos < len; pos++) {
      switch (gateType) {
      case andgate:
        printf("%c", AND(inputs[leftInput].signal[pos],
                         inputs[rightInput].signal[pos]));
        break;
      case orgate:
        printf("%c", OR(inputs[leftInput].signal[pos],
                        inputs[rightInput].signal[pos]));
        break;
      case xorgate:
        printf("%c", XOR(inputs[leftInput].signal[pos],
                         inputs[rightInput].signal[pos]));
        break;
      case nandgate:
        printf("%c", NAND(inputs[leftInput].signal[pos],
                          inputs[rightInput].signal[pos]));
        break;
      case norgate:
        printf("%c", NOR(inputs[leftInput].signal[pos],
                         inputs[rightInput].signal[pos]));
        break;
      case nxorgate:
        printf("%c", NXOR(inputs[leftInput].signal[pos],
                          inputs[rightInput].signal[pos]));
        break;
      }
    }

    printf("\n");
  }

  return 0;
}
