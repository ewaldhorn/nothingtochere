#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>

int main() {
	
    // int n;
    // scanf("%d", &n);
    //Complete the code to calculate the sum of the five digits on n.

    int n = 10564;
    int expected = 1 + 0 + 5 + 6 + 4;
    int answer = 0;
    int factor = 10000;

    printf("Input is %d.\n", n);

    while (factor >= 1) {
        int tmp = n % factor;
        int diff = (n-tmp)/factor;
        
        answer += diff;
        n -= factor * diff;

        factor /= 10;
    }


    printf("Expected %d, got %d, so %s.\n", expected, answer, (answer==expected)?"true":"false");

    return 0;
}