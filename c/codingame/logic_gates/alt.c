#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
// ---------------------------------------------------
typedef struct {
  char *name;
  char *signal;
} input;
input inputs[4];
// ---------------------------------------------------
int AND(int a, int b) { return a & b; }
int OR(int a, int b) { return a | b; }
int XOR(int a, int b) { return a ^ b; }
int NAND(int a, int b) { return !(a & b); }
int NOR(int a, int b) { return !(a | b); }
int NXOR(int a, int b) { return !(a ^ b); }

int boolit(int a) { return a == '-'; }
int unboolit(int a) { return a ? '-' : '_'; }
// ---------------------------------------------------

char result[1000];
void process(char *gate, char *s1, char *s2) {
  int (*g)(int a, int b) = strcmp(gate, "AND") == 0    ? AND
                           : strcmp(gate, "OR") == 0   ? OR
                           : strcmp(gate, "XOR") == 0  ? XOR
                           : strcmp(gate, "NAND") == 0 ? NAND
                           : strcmp(gate, "NOR") == 0  ? NOR
                           : strcmp(gate, "NXOR") == 0 ? NXOR
                                                       : NULL;

  assert(g);

  char *r = result;
  while (*s1)
    *r++ = unboolit(g(boolit(*s1++), boolit(*s2++)));
  *r = 0;
}
// ---------------------------------------------------
char *signal(char *name) {
  for (int i = 0; i < 4; i++)
    if (strcmp(inputs[i].name, name) == 0)
      return inputs[i].signal;
  assert(0);
}
// ---------------------------------------------------
int main() {
  int n; // number of input signals
  int m; // number of output signals
  scanf("%d\n%d\n", &n, &m);

  for (int i = 0; i < n; i++) {
    input *in = inputs + i;
    scanf("%ms%ms", &in->name, &in->signal);
  }
  for (int i = 0; i < m; i++) {
    char output_name[9];
    char type[9];
    char input_name_1[9];
    char input_name_2[9];
    scanf("%s%s%s%s", output_name, type, input_name_1, input_name_2);
    process(type, signal(input_name_1), signal(input_name_2));
    printf("%s %s\n", output_name, result);
  }

  return EXIT_SUCCESS;
}
