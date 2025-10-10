#include <stdio.h>

void count_evens_to_100(void) {
  for (int i = 0; i < 100; i += 2) {
    printf("%d\n", i);
  }
}
