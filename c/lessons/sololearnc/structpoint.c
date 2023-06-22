#include <stdio.h>

struct student {
    char name[50];
    int number;
    int age;
};

void showStudentData(struct student *st)
{
    printf("\nStudent:\n");
    printf("Name: %s\n", st->name);
    printf("Number: %d\n", st->number);
    printf("Age: %d\n", st->age);
}

int main()
{
    struct student s1 = {"Rishi", 5, 22};
    showStudentData(&s1);

    return 0;
}