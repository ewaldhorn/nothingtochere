#include "functions.h"

int addUp(int left, int right) {
    return left + right;
}

int main() {
    printf("Adding up 1 and 2 gives %d.\n", addUp(1,2));
    
    printf("Reverse 123456789 : ");
    printInReverse("123456789");

    return 0;
}

// With the preprocessor we can have functions anywhere, even after main...
void printInReverse(char *msg) {
    int strSize = sizeof(msg);

    for (int i = strSize; i >= 0; i--) {
        printf("%c", msg[i]);
    }
}