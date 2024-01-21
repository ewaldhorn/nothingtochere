#include <stdio.h>

int main() {
    
    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 20; j++) {
            printf("%4d", j+(i*j));
        }
        printf("\n");
    }
    
    return 0;
}