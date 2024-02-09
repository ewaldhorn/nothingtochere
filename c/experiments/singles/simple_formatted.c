#include <stdio.h>

int main() {

	int answer = 42;
	float PI = 3.124f;

	puts("This just prints a string.\n");

	printf("This allows us to output variables, like answer == %d.\n", answer);
	printf("We can also print floats PI == %.2f.\n", PI);

	return 0;
}
