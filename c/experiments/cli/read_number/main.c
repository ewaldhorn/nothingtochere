#include "app_lib.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>

// ---------------------------------------------------------------------------
void display_help() { printf("Usage:  readnum <number>\n"); }

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

  int number = atoi(argv[1]);

  if (number == 0) {
    printf("Yeah, what do I do with %d?", number);
  } else if (number > 0) {
    printf("%d is positive!", number);
  } else {
    printf("%d is negative!", number);
  }

  printf("\n");
  return EXIT_SUCCESS;
}
