#include <stdio.h>

int main()
{
    FILE *fptr;
    int arr[10];
    int x[10];
    int k;

    /* generate array of numbers */
    for (k = 0; k < 10; k++)
        arr[k] = k;

    /* write array to file */
    fptr = fopen("datafile.bin", "wb");
    fwrite(arr, sizeof(arr[0]),
           sizeof(arr) / sizeof(arr[0]), fptr);
    fclose(fptr);

    /* read array from file */
    fptr = fopen("datafile.bin", "rb");
    fread(x, sizeof(arr[0]), sizeof(arr) / sizeof(arr[0]), fptr);
    fclose(fptr);

    /* print array */
    for (k = 0; k < 10; k++)
    {
        printf("%d", x[k]);
    }

    printf("\n");
    return 0;
}