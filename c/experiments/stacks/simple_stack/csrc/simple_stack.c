#include "simple_stack.h"

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

// ---------------------------------------------------------------------- clear
void clear() {
  top = EMPTY;
}

// --------------------------------------------------------------------- peek()
int peek() {
  if (top == EMPTY) return STACK_EMPTY;

  return theStack[top];
}
