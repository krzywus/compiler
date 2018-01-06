#ifndef NUMBER_CREATION_H
#define NUMBER_CREATION_H

using namespace std;

extern long program_k;
stack<string> tmp_stk;

void printCommandsForCreatingNumber(long number) {
  if(debug) cout << "Preparing to print commands for creating: " << number << endl;
  if (number == 0L) {
    cout << "ZERO\n"; program_k++;
    return;
  }
  while(number > 1) {
      if(debug) cout << "number:  " << number;
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
    string instruction = tmp_stk.top();
    tmp_stk.pop();
    cout << instruction;
  }
}

#endif
