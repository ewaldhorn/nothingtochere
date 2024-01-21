#include <stdio.h>
#include <string.h>

int main() {
    char str1[] = "apple";
    char str2[] = "banana";

    int result = strcmp(str1, str2);

    if (result == 0) {
        printf("The strings are equal.\n");
    } else if (result < 0) {
        printf("String 1 is less than string 2.\n");
    } else {
        printf("String 1 is greater than string 2.\n");
    }

    return 0;
}
