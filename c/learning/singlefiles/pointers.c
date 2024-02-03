#include <stdio.h>

void pointers() {
    int count = 100, score = 25;
    int *pCount = &count;
    count = *pCount + 1;
}

void update(int *a,int *b) {
    int sum = *a + *b;
    int dif = *a - *b;
    
    *a = sum;
    if (dif < 0) {
        *b = -1 * dif;
    } else {
        *b = dif;
    } 
}

void swap(int *left, int *right) {
    int tmp = *left;
    *left = *right;
    *right = tmp;
}

int alternativeStringLength(char *string) {
    return strlen(string);
}

int main() {
    int a, b;
    int *pa = &a, *pb = &b;
    
    scanf("%d %d", &a, &b);
    update(pa, pb);
    printf("%d\n%d", a, b);

    char* yolo = "YOLO!";
    int (*aFuncPtr)(char *);
    aFuncPtr = alternativeStringLength;

    int length = (*aFuncPtr)(yolo);
    printf("The string length is %d\n", length);

    return 0;
}
