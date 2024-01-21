#include <stdio.h>

void boxIt() {
    for (int i = 0; i < 20; i++) {
        printf("=");
    }
    
    printf("\n");
    printf("=");

    for (int i = 0; i < 18; i++) {
        printf(" ");
    }

    printf("=");
    printf("\n");

    for (int i = 0; i < 20; i++) {
        printf("=");
    }

    printf("\n");
}

int main(void)
{
    printf("C Info Display Experiments\n");
    boxIt();
    return 0;
}
