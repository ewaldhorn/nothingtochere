#include "lib/my_lib.h"
#include "lib/my_math.h"

#include <stdio.h>
#include <stdlib.h>

int main() {
    say_hello();

    int one = 10, two = 20;
    printf("The larger of %d and %d is clearly %d.\n", one, two, biggestOf(one, two));
    
    return EXIT_SUCCESS;
}