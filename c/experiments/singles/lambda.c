#include <stdio.h>

#define λ(return_type, args, body) ({ return_type __func args body __func__; })

int main() {
  int (*add)(int, int) = λ(int, (int a, int b), { return a + b; });
  printf("%d\n", add(2, 3));

  int (*cube)(int) = λ(int, (int x), { return x * x * x; });

  return 0;
}
