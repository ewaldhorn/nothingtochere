#include <stdio.h>
#include <string.h>

int main(int argc, char **argv) {

    // this is a string
    char *str = "hehe";

    // create the same string
    // as a character array 
    char otherstr[] = {'h','e','h','e',0} ;

    if (!strcmp(str, otherstr)) {
        printf("Yay!\n");
    } else {
        printf("Nay!\n");
    }

    return 0;
}
