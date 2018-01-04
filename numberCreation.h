#ifndef NUMBER_CREATION_H
#define NUMBER_CREATION_H

#include "stringStack.h"

extern void initStack(STACK *s);
extern void finalizeStack(STACK *s);
extern void push (STACK *s, char* instruction);
extern char* pop (STACK *s);
extern int isEmpty(STACK *s);

STACK* stack;

void printCommandsForCreatingNumber(long number) {
  if(debug) printf("Preparing to print commands for creating: '%ld'\n", number);
  if (number == 0L) {
    printf("ZERO\n");
    return;
  }
  if(debug) printf("Allocating stack for creating number.\n");
  STACK *stack = malloc(sizeof(STACK)*100);
  initStack(stack);
  if(debug) printf("Stack initialized successfully.\n");
  while(number > 1) {
      if(debug) printf("number: %lu ", number);
      if (number%2 == 0) {
        number = number / 2;
        push(stack, "SHL\n");
      } else {
        number--;
        push(stack, "INC\n");
      }
  }
  push(stack, "ZERO\nINC\n");
  if(debug) printf("\nInstructions ready, printing in progress.\n");
  while(!isEmpty(stack)) {
    char* instruction = pop(stack);
    printf("%s", instruction);
  }
  finalizeStack(stack);
}

#endif
