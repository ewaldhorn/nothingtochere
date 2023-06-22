#include <stdio.h>
#include <time.h>
#include <stdlib.h>

#define SIZE_ARRAY 50

typedef struct s_fat_boy
{
    char v[SIZE_ARRAY];
} t_fat_boy;

void find_42(t_fat_boy fat_boy)
{
    int i = 0;

    while (1)
    {
        if (fat_boy.v[i] == 42)
        {
            printf("42 is in position %d.\n", i);
            break;
        }
        
        i++;

        if (i > SIZE_ARRAY)
        {
            printf("Nope, 42 could not be found!\n");
            break;
        }
    }
}

int main()
{
    t_fat_boy fat_boy_with42, fat_boy_sans42;

    srand(time(NULL));

    fat_boy_with42.v[rand() % SIZE_ARRAY] = 42;

    printf("\n");
    printf("Looking for 42 in fat_boy_with42: ");
    find_42(fat_boy_with42);
    printf("Looking for 42 in fat_boy_sans42: ");
    find_42(fat_boy_sans42);
    printf("\n");
    
    return 0;
}