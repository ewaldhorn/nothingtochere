#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/fcntl.h>
#include <unistd.h>

struct item_record {
  int item_number;
  int item_count;
  int item_version;
};

// ----------------------------------------------------- open_and_write_to_file
void open_and_write_to_file(void) {
  int myFileDescriptor = open("./items.db", O_RDWR | O_CREAT, 0644);
  if (myFileDescriptor == -1) {
    perror("open");
    exit(EXIT_FAILURE);
  }

  struct item_record record = {
      .item_count = 2, .item_number = 1, .item_version = 1};

  printf("About to write %lu bytes to the file.\n", sizeof(record));
  ssize_t written = write(myFileDescriptor, &record, sizeof(record));
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
  int myFileDescriptor = open("./items.db", O_RDONLY);
  if (myFileDescriptor == -1) {
    perror("open");
    exit(EXIT_FAILURE);
  }

  struct item_record myStruct;

  ssize_t bytesRead = read(myFileDescriptor, &myStruct, sizeof(myStruct));
  if (bytesRead == -1) {
    perror("read");
    exit(EXIT_FAILURE);
  }
  printf("We read %zd bytes from the file.\n", bytesRead);
  printf("Data read: \n%d count\n%d number\n%d version\n", myStruct.item_count,
         myStruct.item_number, myStruct.item_version);

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
