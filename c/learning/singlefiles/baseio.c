#include <stdio.h>

/* copies input to output one character at a time */

int main()
{
	int c;

	c = getchar();

	while (c != EOF)
	{
		putchar(c);
		c = getchar();
	}
}
