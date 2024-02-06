#include <stdlib.h>
#include <stdio.h>

int main(void) {

    for (size_t i = 0; i < 10; i++) {
        printf("%2zu. - Hello world!\n", i+1);
    }

    return EXIT_SUCCESS;
}