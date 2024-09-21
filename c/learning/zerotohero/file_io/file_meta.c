#include <stdio.h>
#include <sys/fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

// ----------------------------------------------------------------------------
struct database_header_t {
  unsigned short version;
  unsigned short employees;
  unsigned int filesize;
};

// ======================================================================= main
int main(int argc, char *argv[]) {
  struct database_header_t head = {0};
  struct stat dbFileStat = {0};

  if (argc != 2) {
    printf("Usage: %s <filename>\n", argv[0]);
    return 0;
  }

  int fd = open(argv[1], O_RDWR | O_CREAT, 0644);
  if (fd == -1) {
    perror("open");
    return -1;
  }

  if (read(fd, &head, sizeof(head)) != sizeof(head)) {
    perror("read");
    close(fd);
    return -1;
  }

  printf("DB Version  : %u\n", head.version);
  printf("DB Employees: %u\n", head.employees);
  printf("DB File size: %u\n", head.filesize);

  if (fstat(fd, &dbFileStat) < 0) {
    perror("fstat");
    close(fd);
    return -1;
  }

  printf("Stat File Size: %llu\n", dbFileStat.st_size);

  close(fd);
  return 0;
}
