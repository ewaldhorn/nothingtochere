#include <stdio.h>

#define PI 3.1415

int main()
{
  float radius = 7.82;
  float area = PI * radius * radius;

  printf("A circle with a radius of %.2f will have a an area of %.2f.\n", radius, area);

  return 0;
}
