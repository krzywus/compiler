#ifndef NUMBER_CREATION_H
#define NUMBER_CREATION_H

#include "stringStack.h"

extern void initStack(STACK *s);
extern void finalizeStack(STACK *s);
extern void push (STACK *s, char* instruction);
extern char* pop (STACK *s);
extern int isEmpty(STACK *s);

void printCommandsForCreatingNumber(long number) {
  if (number == 0) {
    printf("ZERO\n");
    return;
  }
  STACK *stack = malloc(sizeof(STACK));
  initStack(stack);
  while(number > 1) {
      if(debug) printf("number: %ld ", number);
      if (number%2 == 0) {
        number = number / 2;
        push(stack, "SHL\n");
      } else {
        number--;
        push(stack, "INC\n");
      }
  }
  push(stack, "ZERO\nINC\n");
  while(!isEmpty(stack)) {
    char* instruction = pop(stack);
    printf("%s", instruction);
  }
  finalizeStack(stack);
}

#endif
