#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/fcntl.h>
#include <unistd.h>

struct item_record {
  int item_number;
  int item_count;
  char *item_description;
};

// ----------------------------------------------------- open_and_write_to_file
void open_and_write_to_file(void) {
  int myFileDescriptor = open("./sample.txt", O_RDWR | O_CREAT, 0644);
  if (myFileDescriptor == -1) {
    perror("open");
    exit(EXIT_FAILURE);
  }

  char *data = "This goes into the file.\n";
  printf("About to write %lu bytes to the file.\n", strlen(data));
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

// ---------------------------------------------------- open_and_read_from_file
void open_and_read_from_file(void) {
  int myFileDescriptor = open("./sample.txt", O_RDONLY);
  if (myFileDescriptor == -1) {
    perror("open");
    exit(EXIT_FAILURE);
  }

  // create buffer, zero it out
  char readBuffer[2000];
  for (int i = 0; i < sizeof(readBuffer); i++) {
    readBuffer[i] = 0;
  }

  ssize_t bytesRead = read(myFileDescriptor, readBuffer, sizeof(readBuffer));
  if (bytesRead == -1) {
    perror("read");
    exit(EXIT_FAILURE);
  }
  printf("We read %zd bytes from the file.\n", bytesRead);
  printf("Data read: \n%s\n", readBuffer);

  int didClose = close(myFileDescriptor);
  if (didClose == -1) {
    perror("close");
    exit(EXIT_FAILURE);
  }
}

// ======================================================================= main
int main() {
  open_and_write_to_file();
  open_and_read_from_file();
  return EXIT_SUCCESS;
}
