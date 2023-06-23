#include <stdio.h>

int main()
{
    char characters[] = "These are my characters";

    printf("Characters: `%s`\n", characters);

    characters[2] = 'i';
    printf("Characters: `%s`\n", characters);

    return 0;
}