#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>

int main() {
  int fd = open("./nope", O_RDONLY);
  if (fd == -1) {
    perror("open");
    return EXIT_FAILURE;
  }

  return EXIT_SUCCESS;
}
