/*
Using lookup tables in C.
*/

#include <stddef.h>
#include <stdio.h>

// ----------------------------------------------------------------------------
// A serving set comes with a single plate service and enough food etc. for four
// people.
//
// This function is just a raw implementation
void print_catering_requirements_basic(size_t meals) {
  if (meals <= 0) {
    printf("For %2zu: Nothing required for no meals!\n", meals);
  } else if (meals == 1) {
    printf("For %2zu: Just one full set is required.\n", meals);
  } else if (meals == 2) {
    printf("For %2zu: One set and an extra plate service is required.\n",
           meals);
  } else if (meals <= 4) {
    printf("For %2zu: One set and an extra %zu plate services is required.\n",
           meals, (meals - 1));
  } else if (meals <= 8) {
    printf("For %2zu: Two sets and an extra %zu plate services is required.\n",
           meals, (meals - 2));
  } else if (meals <= 12) {
    printf(
        "For %2zu: Three sets and an extra %zu plate services is required.\n",
        meals, (meals - 3));
  } else if (meals <= 16) {
    printf("For %2zu: Four sets and an extra %zu plate services is required.\n",
           meals, (meals - 4));
  } else if (meals <= 20) {
    printf("For %2zu: Five sets and an extra %zu plate services is required.\n",
           meals, (meals - 5));
  } else if (meals <= 24) {
    printf("For %2zu: Six sets and an extra %zu plate services is required.\n",
           meals, (meals - 6));
  } else if (meals <= 28) {
    printf(
        "For %2zu: Seven sets and an extra %zu plate services is required.\n",
        meals, (meals - 7));
  } else if (meals <= 32) {
    printf(
        "For %2zu: Eight sets and an extra %zu plate services is required.\n",
        meals, (meals - 8));
  } else if (meals <= 36) {
    printf("For %2zu: Nine sets and an extra %zu plate services is required.\n",
           meals, (meals - 9));
  } else if (meals <= 40) {
    printf("For %2zu: Ten sets and an extra %zu plate services is required.\n",
           meals, (meals - 10));
  } else if (meals <= 44) {
    printf(
        "For %2zu: Eleven sets and an extra %zu plate services is required.\n",
        meals, (meals - 11));
  } else if (meals <= 48) {
    printf(
        "For %2zu: Twelve sets and an extra %zu plate services is required.\n",
        meals, (meals - 12));
  } else {
    printf("Sorry, we don't cater for parties larger than 48.\n");
  }
}

// ----------------------------------------------------------------------------
// We can make things a bit cleaner and easier to maintain with lookup tables.
const char *countWords[] = {"Zero", "One",    "Two",   "Three", "Four",
                            "Five", "Six",    "Seven", "Eight", "Nine",
                            "Ten",  "Eleven", "Twelve"};

const char *messages[] = {
    "For %2zu: Nothing required for no meals!\n",
    "For %2zu: Just one full set is required.\n",
    "For %2zu: %s set(s) and an extra %zu plate services is required.\n",
    "Sorry, we don't cater for parties larger than 48.\n"};

void print_catering_requirements(size_t meals) {
  if (meals <= 0) {
    printf(messages[0], meals);
  } else if (meals == 1) {
    printf(messages[1], meals);
  } else if (meals <= 48) {
    int sets = meals / 4 + meals % 4;
    int plates = meals - sets;

    printf(messages[2], meals, countWords[sets], plates);
  } else {
    printf("%s", messages[3]);
  }
}

// ----------------------------------------------------------------------------
int main() {

  print_catering_requirements_basic(0);
  print_catering_requirements_basic(1);
  print_catering_requirements_basic(2);
  print_catering_requirements_basic(5);
  print_catering_requirements_basic(8);
  print_catering_requirements_basic(9);
  print_catering_requirements_basic(10);
  print_catering_requirements_basic(12);
  print_catering_requirements_basic(15);
  print_catering_requirements_basic(41);
  print_catering_requirements_basic(48);
  print_catering_requirements_basic(49);

  printf("\n===============================\nUsing lookup tables:\n\n");

  print_catering_requirements(0);
  print_catering_requirements(1);
  print_catering_requirements(2);
  print_catering_requirements(5);
  print_catering_requirements(8);
  print_catering_requirements(9);
  print_catering_requirements(10);
  print_catering_requirements(12);
  print_catering_requirements(15);
  print_catering_requirements(41);
  print_catering_requirements(48);
  print_catering_requirements(49);

  return 0;
}
