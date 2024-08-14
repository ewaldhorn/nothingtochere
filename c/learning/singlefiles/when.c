#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// ======================================================================= main
int main() {
  time_t currentTime = time(NULL);

  printf("Current time in ms %ld.\n", currentTime);

  struct tm currentDate = *localtime(&currentTime);
  printf("Current date is %02d-%02d-%d", currentDate.tm_mday,
         1 + currentDate.tm_mon, 1900 + currentDate.tm_year);

  return EXIT_SUCCESS;
}
