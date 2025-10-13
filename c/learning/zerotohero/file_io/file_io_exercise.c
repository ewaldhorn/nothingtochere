#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void print_the_flag() {
    const char *filepath = "/tmp/flag";
    int fd = open(filepath, O_RDONLY); // Open the file for read-only access.

    if (fd == -1) {
        // open failed, print error and exit
        perror("open");
        exit(EXIT_FAILURE);
    }

    // Define buffer size and buffer
    enum { BUFFER_SIZE = 2000 };
    char readBuffer[BUFFER_SIZE];

    // Read the file content into the buffer
    // The -1 is typically not needed here since we are not null-terminating on read
    // but the original code used it, so we'll use the full buffer size
    ssize_t bytesRead = read(fd, readBuffer, BUFFER_SIZE - 1); // Use read(2)

    if (bytesRead == -1) {
        // read failed, print error, close the file, and exit
        perror("read");
        close(fd);
        exit(EXIT_FAILURE);
    }

    // Null-terminate the string to ensure printf works safely
    readBuffer[bytesRead] = '\0';
    
    // Print the content
    printf("%s\n", readBuffer);

    // Close the file descriptor
    if (close(fd) == -1) {
        // close failed, print error and exit
        perror("close");
        exit(EXIT_FAILURE);
    }
}

// ------------------------------------------------------------------------------------------------
int main() { print_the_flag(); }
