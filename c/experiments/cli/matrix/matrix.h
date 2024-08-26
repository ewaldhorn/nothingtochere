#ifndef __MATRIX_H__
#define __MATRIX_H__

#include <stdbool.h>

#define NUM_DRIPS 250
#define PROB_SPAWN 0.45
#define PROB_CHANGE 0.65
#define PROB_DIM 0.50
#define RANDOM_PRINTABLE_CHARACTER (33 + (rand()%80))


typedef struct {
  int x,y;
  bool live;
  bool bright;
} drip;

void matrix_init(void);
void matrix_update(void);

#endif
