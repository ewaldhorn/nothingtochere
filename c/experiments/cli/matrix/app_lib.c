#include "app_lib.h"
#include <curses.h>
#include <stdio.h>
#include <stdlib.h>

WINDOW *uiwindow = NULL;
int colour_map[MAX_INTENSITY + 1] = {1, 2, 2, 3, 3, 3, 4, 4, 4, 4, 4, 5, 3, 6};

// -------------------------------------------------------------- print_version
void print_version(void) { printf("Matrix version %d.\n", VERSION); }

// --------------------------------------------------------------- clear_matrix
void clear_matrix(void) {
  for (int x = 0; x < MAX_X; x++) {
    for (int y = 0; y < MAX_Y; y++) {
      matrix[x][y].char_value = 0;
      matrix[x][y].intensity = 0;
    }
  }
}

// -------------------------------------------------------------------- init_ui
void init_ui(void) {
  clear_matrix();

  uiwindow = initscr();
  if (uiwindow == NULL) {
    puts("Error: Unable to init screen.");
    exit(EXIT_FAILURE);
  }

  start_color();
  if (!has_colors() || !can_change_color() || COLOR_PAIRS < 6) {
    puts("Error: Not a writeable colour terminal!");
    exit(EXIT_FAILURE);
  }
  set_colours();
}

// ----------------------------------------------------------------- cleanup_ui
void cleanup_ui(void) {
  delwin(uiwindow);
  endwin();
  refresh();
}

// ---------------------------------------------------------------- show_matrix
void show_matrix(void) {
  for (int x = 0; x < MAX_X; x++) {
    for (int y = 0; y < MAX_Y; y++) {
      color_set(colour_map[matrix[x][y].intensity], NULL);
      mvaddch(y, x, matrix[x][y].char_value);
    }
  }
  refresh();
}

// ---------------------------------------------------------------- set_colours
void set_colours(void) {
  for (int i = 0; i < 8; i++) {
    init_pair(i + 1, i, COLOR_BLACK);
  }

  for (int i = 0; i < 5; i++) {
    init_color(i, 0, i * 200, 0);
  }

  init_color(6, 100, 800, 100);
}
