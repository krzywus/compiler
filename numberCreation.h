#ifndef NUMBER_CREATION_H
#define NUMBER_CREATION_H

#include "stringStack.h"

extern void push (STACK *s, char* instruction);
extern char* pop (STACK *s);
extern int isEmpty(STACK *s);

extern long program_k;
extern STACK* stack;

void printCommandsForCreatingNumber(long number) {
  if(debug) printf("Preparing to print commands for creating: '%ld'\n", number);
  if (number == 0L) {
    printf("ZERO\n"); program_k++;
    return;
  }
  while(number > 1) {
      if(debug) printf("number: %lu ", number);
      if (number%2 == 0) {
        number = number / 2;
        push(stack, "SHL\n"); program_k++;
      } else {
        number--;
        push(stack, "INC\n"); program_k++;
      }
  }
  push(stack, "ZERO\nINC\n"); program_k += 2;
  if(debug) printf("\nInstructions ready, printing in progress.\n");
  while(!isEmpty(stack)) {
    char* instruction = pop(stack);
    printf("%s", instruction);
  }
}

#endif
