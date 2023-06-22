#include <stdio.h>
#include <string.h>

struct course {
    int id;
    char title[40];
    float hours;
};

int main() {
    struct course cs1 = {341279, "Intro to C", 12.5};
    struct course cs2;

    cs2.id = 341280;
    strcpy(cs2.title, "Advanced C");
    cs2.hours = 17.5;

    printf("%d\t%s\t%4.2f\n", cs1.id, cs1.title, cs1.hours);
    printf("%d\t%s\t%4.2f\n", cs2.id, cs2.title, cs2.hours);

    return 0;
}
