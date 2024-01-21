#include <stdlib.h>
#include <stdio.h>

/**
 * Write a program which reads a positive integer value and show its divisors.
 *
 * Notes:
 * Let n be the number:
 * 	let d be a divisor of n --> n/d gives a remainder of 0
 * 	n is a divisor of n
 * 	The strict divisors of n are <= n/2, excluding n
 **/

int main() {
  
  printf("\nPlease provide a number: ");
  int n = 0;
  scanf("%d", &n);

  printf("The divisors of %d are:\n", n);
  printf("1\n");
  for (int i = 2; i <= n/2; i++) {
    if (n % i == 0) {
      printf("%d\n", i);
    }
  }
  printf("%d\n", n);
	
  printf("\n");
  return 0;
}
