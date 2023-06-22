#include <stdio.h>
#include <stdlib.h>

int main()
{
    char choice[10];

    while (1)
    {
        printf("Select:\n(a)dd\n(d)elete\n(q)uit\n: ");
        fgets(choice, sizeof(choice), stdin);

        switch (choice[0])
        {
        case 'a':
            printf("Adding...\n");
            break;
        case 'd':
            printf("Deleting...\n");
            break;
        case 'q':
            printf("Quitting...\n");
            exit(0);
        default:
            printf("Wot?!\n");
            break;
        }
    }

    return 0;
}