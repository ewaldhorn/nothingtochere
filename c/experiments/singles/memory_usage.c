#include <stdio.h>

int main() {
  int var1 = 1000;
  int var2 = 1010;
  int arr1[1] = {11};
  int arr2[2] = {22, 33};

  printf("&var1 = %p\n", &var1);
  printf("&var2 = %p\n", &var2);
  printf("&arr1 = %p\n", arr1);
  printf("&arr2 = %p\n", arr2);

  return 0;
}
