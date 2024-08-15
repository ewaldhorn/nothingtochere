#include <stdio.h>

// something is wrong here :(
int swap(int *a, int *b) {
  int temp;
  temp = *a; // get value at address of a
  *a = *b;   // swap value at a for value at b
  *b = temp; // change value at b to what is in temp
}

int main() {
  int x = 10, y = 20;
  printf("%d %d\n", x, y);
  swap(&x, &y);
  printf("%d %d\n", x, y);
  return 0;
}
