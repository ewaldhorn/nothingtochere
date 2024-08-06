#include "fizz_buzzer.h"

// --------------------------------------------------------------------- buzzer
const char* buzzer(const int n) {
  char *result;

  if (n % 15 == 0){
    asprintf(&result, "FizzBuzz");
  } else if (n % 3 == 0) {
    asprintf(&result, "Fizz");
  } else if (n % 5 == 0) {
    asprintf(&result, "Buzz");
  } else {
    asprintf(&result, "%d", n);
  }

  return result;
}

// -------------------------------------------------------------------- version
/// returns the version of the app as a string
const char* version() {
  char *result;
  asprintf(&result, "0.0.1");
  return result;
}
