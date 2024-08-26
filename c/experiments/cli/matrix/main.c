#include <curses.h>
#include <stdlib.h>
#include <unistd.h>

#include "app_lib.h"
#include "matrix.h"

// ======================================================================= main
int main() {
  print_version();
  init_ui();

  for (int i = 0; i < ITERATIONS; i++) {
    matrix_update();
    show_matrix();

    usleep(REFRESH_DELAY);
  }

  cleanup_ui();
  return EXIT_SUCCESS;
}
