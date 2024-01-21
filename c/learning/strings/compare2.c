#include <stdio.h>
#include <string.h>
#include <ctype.h>

int main() {
    char str1[] = "Apple";
    char str2[] = "apple";

    // Convert both strings to lowercase
    for (int i = 0; str1[i]; i++) {
        str1[i] = tolower(str1[i]);
    }
    for (int i = 0; str2[i]; i++) {
        str2[i] = tolower(str2[i]);
    }

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
