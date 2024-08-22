#include <stdio.h>

void printAsEnglish(int num) {
  switch (num) {
  case 1:
    printf("one");
    break;
  case 2:
    printf("two");
    break;
  case 3:
    printf("three");
    break;
  case 4:
    printf("four");
    break;
  case 5:
    printf("five");
    break;
  case 6:
    printf("six");
    break;
  case 7:
    printf("seven");
    break;
  case 8:
    printf("eight");
    break;
  case 9:
    printf("nine");
    break;
  }
  printf("\n");
}

int main() {
  int a, b;
  puts("Enter two numbers, one after the other, between 0 and 10");
  scanf("%d\n%d", &a, &b);
  // Complete the code.
  if (a < 10) {
    printAsEnglish(a);
  } else {
    printf("%s\n", (a % 2 == 0) ? "even" : "odd");
  }

  if (b < 10) {
    printAsEnglish(b);
  } else {
    printf("%s\n", (b % 2 == 0) ? "even" : "odd");
  }

  return 0;
}
