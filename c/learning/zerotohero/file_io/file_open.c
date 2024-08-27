#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/fcntl.h>
#include <unistd.h>

// ---------------------------------------------------------------- open_a_file
void open_a_file(void) {
  int myFileDescriptor = open("./sample.txt", O_RDWR | O_CREAT, 0644);
  if (myFileDescriptor == -1) {
    perror("open");
    exit(EXIT_FAILURE);
  }

  char *data = "This goes into the file.\n";
  ssize_t written = write(myFileDescriptor, data, strlen(data));
  if (written == -1) {
    perror("write");
    exit(EXIT_FAILURE);
  }

  int didClose = close(myFileDescriptor);
  if (didClose == -1) {
    perror("close");
    exit(EXIT_FAILURE);
  }
}

// ======================================================================= main
int main() {
  open_a_file();
  return EXIT_SUCCESS;
}
