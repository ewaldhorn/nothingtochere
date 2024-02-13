#include "reverse-string.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    char *tmp = "loop";
    printf("%s reversed is %s\n", tmp, reverse(tmp));

    return 0;
}

char *reverse(const char *value)
{
	int length = strlen(value);
	char *result;
	result = malloc(sizeof(char) * (length + 1));

	int i = 0;
	while (i < length)
	{
	    result[i] = value[length - 1 - i];
	    i++;
	}

	result[i] = '\0'; // don't forget the string terminator!
	
    return result;
}