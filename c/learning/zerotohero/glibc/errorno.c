#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>

int main() {
  int fileDescriptor = open("./nope", O_RDONLY);
  if (fileDescriptor == -1) {
    perror("open");
    return EXIT_FAILURE;
  }

  return EXIT_SUCCESS;
}
