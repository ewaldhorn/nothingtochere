#include <stdio.h>
#include <stdlib.h>

// ===================================================================== define
#define MAX 3

// ===================================================================== struct
struct person {
  char *name;
  char *occupation;
};

// ======================================================================= main
int main() {
  struct person people[MAX];

  for (int i = 0; i < MAX; i++) {
    char name[21];

    printf("Name %d please: ", i + 1);
    scanf("%20s", name);

    people[i].name = name;
  }

  printf("\nPeople on the list:\n");
  for (int i = 0; i < MAX; i++) {
    printf("%d. %s\n", i + 1, people[i].name);
  }

  return EXIT_SUCCESS;
}
