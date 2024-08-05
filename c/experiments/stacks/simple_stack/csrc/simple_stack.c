// #include <stdio.h>
#include <limits.h>
#include <stdbool.h>

// -------------------------------------------------------------------- defines
#define MAX_STACK_LENGTH 5
#define EMPTY (-1)
#define STACK_EMPTY INT_MIN

// -------------------------------------------------------------------- globals
int theStack[MAX_STACK_LENGTH];
int top = EMPTY;

// ----------------------------------------------------------------------- push
bool push(int val) {
  if (top >= MAX_STACK_LENGTH-1) return false; // abort if stack is full

  top++;
  theStack[top] = val;
  return true;
}

// ------------------------------------------------------------------------ pop
int pop() {
  if (top == EMPTY) return STACK_EMPTY;

  int result = theStack[top];
  top--;

  return result;
}
