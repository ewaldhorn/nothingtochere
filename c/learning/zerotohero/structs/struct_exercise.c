#include <stdio.h>

struct Employee {
  char name[100];
  int age;
};

int main(int argc, char **argv) {

  struct Employee emp = {"Steve", 42};

  printf("%s, aged %d years\n", emp.name, emp.age);

  return 0;
}
