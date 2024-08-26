#include "matrix.h"
#include "app_lib.h"
#include <stdbool.h>
#include <stdlib.h>

cell matrix[MAX_X][MAX_Y];
drip drips[NUM_DRIPS];

// ----------------------------------------------------------------- init_drips
void init_drips(void) {
  for (int i = 0; i < NUM_DRIPS; i++) {
    drips[i].live = false;
  }
}

// --------------------------------------------------------------- update_drips
void update_drips(void) {
  for (int i = 0; i < NUM_DRIPS; i++) {
    if (drips[i].live) {
      if (drips[i].bright) {
        matrix[drips[i].x][drips[i].y].intensity = MAX_INTENSITY;
      } else {
        matrix[drips[i].x][drips[i].y].intensity = MIN_INTENSITY;
      }

      // disable drips when they drop off the bottom
      if (++drips[i].y >= MAX_Y - 1) {
        drips[i].live = false;
      }
    }
  }
}

// ---------------------------------------------------------------- matrix_init
void matrix_init() {
  for (int x = 0; x < MAX_X; x++) {
    for (int y = 0; y < MAX_Y; y++) {
      matrix[x][y].char_value = 0;
      matrix[x][y].intensity = 0;
    }
  }

  init_drips();
}

// ---------------------------------------------------------------- rand_double
double rand_double(void) { return (double)rand() / (double)RAND_MAX; }

// -------------------------------------------------- fade_change_unfade_matrix
void fade_change_unfade_matrix(void) {
  for (int x = 0; x < MAX_X; x++) {
    for (int y = 0; y < MAX_Y; y++) {
      if (rand_double() < PROB_CHANGE || matrix[x][y].char_value == 0) {
        matrix[x][y].char_value = RANDOM_PRINTABLE_CHARACTER;
      }

      if (rand_double() < PROB_DIM) {
        if (matrix[x][y].intensity > 0) {
          matrix[x][y].intensity -= 1;
        }
      }
    }
  }
}

// -------------------------------------------------------------- try_add_drips
void try_add_drips(void) {
  for (int i = 0; i < NUM_DRIPS; i++) {
    if (drips[i].live == false) {
      drips[i].live = true;
      drips[i].x = rand() % MAX_X;
      drips[i].y = 0;
      // drips[i].y = rand() % MAX_Y;
      drips[i].bright = rand() % 2;
      return;
    }
  }
}

// -------------------------------------------------------------- matrix_update
void matrix_update() {
  if (rand_double() < PROB_SPAWN) {
    try_add_drips();
  }

  update_drips();
  fade_change_unfade_matrix();
}
