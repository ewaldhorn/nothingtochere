#include <stdio.h>

void printData(void *data, char dataType)
{
    if (dataType == 'i')
    {
        printf("Integer: %d\n", *((int *)data));
    }
    else if (dataType == 'f')
    {
        printf("Float: %E\n", *((float *)data));
    }
    else if (dataType == 'c')
    {
        printf("Char: %c\n", *((char *)data));
    }
    else
    {
        printf("I don't know what to do with `%c`!\n", dataType);
    }
}

int main()
{
    int intVal = 42;

    printData(&intVal, 'i');
    printData(&intVal, 'f');
    printData(&intVal, 'c');

    return 0;
}