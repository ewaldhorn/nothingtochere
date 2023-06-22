#include <stdio.h>

int main()
{
    FILE *fptr;
    fptr = fopen("myfile.txt", "r");
    
    if (fptr != NULL)
    {
        printf("Could open file!\n");
    } else {
        printf("Error opening file!\n");
        return -1;
    }
    
    fclose(fptr);

    return 0;
}