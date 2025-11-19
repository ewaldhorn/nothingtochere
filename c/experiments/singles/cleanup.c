#include <stdio.h>
#include <stdlib.h>

// A custom cleanup function for a FILE pointer.
// The function must accept a pointer to the variable's type.
void file_closer(FILE** file_ptr) {
    if (*file_ptr != NULL) {
        fclose(*file_ptr);
        printf("File closed automatically.\n");
    }
}

int main(void) {
    // Declare a file pointer with the cleanup attribute.
    // When 'fp' goes out of scope (at the end of main, or via an early return),
    // file_closer will be called automatically.
    [[gnu::cleanup(file_closer)]] FILE* fp = fopen("example.txt", "w");

    if (fp == NULL) {
        perror("Failed to open file");
        // No explicit fclose needed here, the cleanup attribute handles it.
        return EXIT_FAILURE;
    }

    fprintf(fp, "Hello, C23 cleanup!");
    printf("Content written to file.\n");

    // The file is automatically closed when main() returns.
    // The explicit call is not needed.
    // fclose(fp);
    return EXIT_SUCCESS;
}

