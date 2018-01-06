#ifndef NUMBER_CREATION_H
#define NUMBER_CREATION_H

#include <stack>

using namespace std;

extern long program_k;
stack<char*> tmp_stk;

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
        tmp_stk.push("SHL\n"); program_k++;
      } else {
        number--;
        tmp_stk.push("INC\n"); program_k++;
      }
  }
  tmp_stk.push("INC\n"); program_k++;
  tmp_stk.push("ZERO\n"); program_k++;
  if(debug) printf("\nInstructions ready, printing in progress.\n");
  while(!tmp_stk.empty()) {
    char* instruction = tmp_stk.top();
    tmp_stk.pop();
    printf("%s", instruction);
  }
}

#endif
