#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

// ----------------------------------------------------------------- prototypes
void reportIntegerSizes(void);

// ======================================================================= main
int main() {
  reportIntegerSizes();

  return EXIT_SUCCESS;
}

// --------------------------------------------------------- reportIntegerSizes
void reportIntegerSizes(void) {
  printf("Integer sizes:\n");

  int basicInt = 0;
  long basicLong = 0;
  int8_t int8Bits = 0;
  int16_t int16Bits = 0;
  int32_t int32Bits = 0;
  int64_t int64Bits = 0;

  printf("The size of an int is    : %lu byte(s).\n", sizeof(basicInt));
  printf("The size of an long is   : %lu byte(s).\n", sizeof(basicLong));
  printf("The size of an int8_t is : %lu byte(s).\n", sizeof(int8Bits));
  printf("The size of an int16_t is: %lu byte(s).\n", sizeof(int16Bits));
  printf("The size of an int32_t is: %lu byte(s).\n", sizeof(int32Bits));
  printf("The size of an int64_t is: %lu byte(s).\n", sizeof(int64Bits));
}

// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------
