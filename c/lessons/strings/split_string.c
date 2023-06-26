#include <stdio.h>
#include <string.h>

int main() {
    char inputString[] = "This string needs to be split into words somehow";
    int stringSize = strlen(inputString);
    char delim[] = " ";

    char *ptr = strtok(inputString, delim);

    while (ptr != NULL)
    {
        printf("'%s'\n", ptr);
        ptr = strtok(NULL, delim);
    }

    /* Ok so now we have a bunch of zeroes between words... */
    for (int i = 0; i < stringSize; i++)
    {
        printf("%d ", inputString[i]); 
    }
    printf("\n");

    printf("\nAs an ASCII code string:\n");

    for (int i=0; i < stringSize; i++)
    {
        if (inputString[i] != '\0') {
            printf("%d ", inputString[i]); 
        } else {
            printf("%d ", ' '); 
        }
    }
    printf("\n");

    return 0;
}