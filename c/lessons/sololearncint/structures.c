#include <stdio.h>

struct course
{
    int id;
    char title[40];
    float hours;
};

struct student
{
    int age;
    int grade;
    char name[40];
};

int main()
{
    // different ways of declaring a struct variable
    struct student s1;

    struct student s2 = {19, 9, "John"};
    struct student s3 = {22, 10, "Batman"};

    struct student s4;
    s4 = (struct student){19, 9, "John"};

    struct student s5 = {.grade = 9, .age = 19, .name = "John"};

    return 0;
}