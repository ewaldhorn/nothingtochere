#include <stdio.h>
#include <stdlib.h>

// ------------------------------------------------------------------ prototype
int checkParameters(int argc, char **argv);
void block(int w, int h);

// ======================================================================= main
int main(int argc, char **argv) {
  if (checkParameters(argc, argv) == EXIT_FAILURE) {
    return EXIT_FAILURE;
  }

  int width = atoi(argv[1]);
  int height = width;

  if (argv[2] != NULL) {
    height = atoi(argv[2]);
  }

  if (width == 0 || height == 0) {
    puts("Neither width nor height can be 0.\n");
    return EXIT_FAILURE;
  }

  printf("Ok, we need to make a block of %d x %d.\n", width, height);
  block(width, height);
  printf("\n");

  return EXIT_SUCCESS;
}

// ------------------------------------------------------------ checkParameters
int checkParameters(int argc, char **argv) {
  if (argc < 2) {
    // not enough parameters
    puts("Usage:");
    puts("block <width> [height]");
    puts("width is mandatory, height optional, will be the same if not "
         "specified.\n");

    return EXIT_FAILURE;
  } else {
    return EXIT_SUCCESS;
  }
}
// ------------------------------------------------------------------------ box
void block(int width, int height) {
  for (int h = 0; h < height; h++) {
    for (int w = 0; w < width; w++) {
      printf("*");
    }
    printf("\n");
  }
}
