#include "app_lib.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>

// ---------------------------------------------------------------------------
void display_help() { printf("Usage:  catt <filename>\n"); }

// ---------------------------------------------------------------------------
int check_arguments(int argc, char **argv) {
  if (argc < 2) {
    display_help();
    return EXIT_FAILURE;
  }

  if ((strcmp("-h", argv[1]) == 0) || (strcmp("--help", argv[1]) == 0)) {
    display_help();
    return EXIT_FAILURE;
  }

  return EXIT_SUCCESS;
}

// ===========================================================================
int main(int argc, char **argv) {
  print_version();

  if (check_arguments(argc, argv) == EXIT_FAILURE) {
    return EXIT_SUCCESS;
  }

  FILE *f = fopen(argv[1], "r");
  char ch;

  while ((ch = getc(f)) != EOF) {
    printf("%c", ch);
  }
  fclose(f);

  printf("\n");
  return EXIT_SUCCESS;
}
