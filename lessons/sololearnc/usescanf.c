#include <stdio.h>

int main()
{
    char info[]= "Snoqaulmie WA 13910";
    char city[50], state[50];
    int population;

    sscanf(info, "%s %s %d", city, state, &population);
    printf("%d people live in %s, %s.\n", population, city, state);

    return 0;
}
