#include <stdlib.h>
#include <stdio.h>

int main(void) {
    int myArray[4] = {1,2,3,4};
    char myWord[4] = {'f','i', 'v', 'e'};
    char anotherWord[] = {'t','h','i','s',' ','i','s',' ','h','a','n','d','y'};

    FILE *outFile = fopen("output.txt", "w+");
    if (outFile == NULL) {
        perror("Could not open output.txt for writing.");
        return -1;
    }

    fprintf(outFile, "Program output:\n");
    fclose(outFile);

    return EXIT_SUCCESS;
}