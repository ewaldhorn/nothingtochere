#include <stdio.h>
#include <string.h>

typedef struct {
    int id;
    char title[40];
    float hours;
} course;

int main()
{
    course cs1;

    cs1.id = 1001;
    cs1.hours = 5.0;
    strcpy(cs1.title, "Cooking Rice");

    course cs2 = {1001, "Cleaning", 7.0};

    printf("%d\t%s\t%4.2f\n", cs1.id, cs1.title, cs1.hours);
    printf("%d\t%s\t%4.2f\n", cs2.id, cs2.title, cs2.hours);

    return 0;
}