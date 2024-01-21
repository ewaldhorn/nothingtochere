#include <stdio.h>

int factorial(int num) {
	if (num < 0) {
		return -1;
	}

	if (num <= 1) {
		return 1;
	}

	return (num * factorial(num - 1));
}

int main() {
	printf("The factorial of 3 is %d\n", factorial(3));
	printf("The factorial of 25 is %d\n", factorial(25));

	return 0;
}
