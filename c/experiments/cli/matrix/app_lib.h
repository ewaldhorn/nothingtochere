#ifndef __APP_LIB__
#define __APP_LIB__

#define VERSION 1

#define ITERATIONS 300
#define REFRESH_DELAY 50000L

#define MAX_X 160
#define MAX_Y 50
#define MIN_INTENSITY 4
#define MAX_INTENSITY 13

typedef struct {
  char char_value;
  int intensity;
} cell;

// extern means it's defined somewhere else
extern cell matrix[MAX_X][MAX_Y];

void print_version(void);
void init_ui(void);
void cleanup_ui();
void show_matrix(void);
void set_colours(void);

#endif
