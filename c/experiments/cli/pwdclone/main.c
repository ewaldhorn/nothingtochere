#include <stdio.h>
#include <stdlib.h>
#include <sys/syslimits.h>
#include <unistd.h>

// ----------------------------------------------------------------------------
int main(int argc, char **argv) {
  printf("Simple PWD clone in C:\n\n");

  char pwd[PATH_MAX];
  if (getcwd(pwd, sizeof(pwd)) != NULL) {
    printf("We are at:\n%s\n", pwd);
  } else {
    perror("getcwd() error");
    return EXIT_FAILURE;
  }

  return EXIT_SUCCESS;
}
