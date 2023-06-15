#include "stringer.h"

int main()
{
    char* myString = "This is a string!";
    char* anotherString = myString;

    printf("The string `%s` is %ld characters long.\n", myString, strlen(myString));
    printf("Is `i` in myString? %d.\n", strchr(anotherString, 'i') == NULL);

    return 0;
}