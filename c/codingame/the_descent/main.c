#include <stdbool.h>
#include <stdio.h>

int main() {
  int target = 0, highest = 0;
  // game loop
  while (1) {
    for (int i = 0; i < 8; i++) {
      // represents the height of one mountain.
      int mountain_h;
      scanf("%d", &mountain_h);

      if (mountain_h > highest) {
        highest = mountain_h;
        target = i;
      }
    }

    printf("%d\n", target); // The index of the mountain to fire on.
  }

  return 0;
}
