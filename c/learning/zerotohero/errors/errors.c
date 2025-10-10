#include <fcntl.h>
#include <stdio.h>

int main(int argc, char *argv[]) {
  int fd = open("./file-that-doesnt-exist", O_RDONLY);
  if (fd == -1) {
    perror("open");
    return -1;
  }
}
