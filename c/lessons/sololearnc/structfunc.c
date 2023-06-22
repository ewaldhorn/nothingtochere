#include <stdio.h>
#include <string.h>

typedef struct
{
    int id;
    char title[40];
    float hours;
} course;

void update_course(course *class);
void display_course(course *class);

int main()
{
    course cs;

    update_course(&cs);
    display_course(&cs);

    return 0;
}

void update_course(course *class)
{
    strcpy(class->title, "C Fundamentals");
    class->id = 1010;
    class->hours = 7.5;
}

void display_course(course *class)
{
    printf("%d\t%s\t%3.1fh\n", class->id, class->title, class->hours);
}