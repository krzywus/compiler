#ifndef NUMBER_CREATION_H
#define NUMBER_CREATION_H

using namespace std;

extern long program_k;
extern vector<string> commands;
stack<string> tmp_stk;

void printCommandsForCreatingNumber(long number) {
  if(bisonDebug) cout << "Preparing to prlong commands for creating: " << number << endl;
  if (number == 0L) {
    tmp_stk.push("ZERO\n"); program_k++;
  } else {
    while(number > 1) {
      if(bisonDebug) cout << "number:  " << number;
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
  }
  if(bisonDebug) printf("\nInstructions ready, printing in progress.\n");
  while(!tmp_stk.empty()) {
    string instruction = tmp_stk.top();
    tmp_stk.pop();
    commands.push_back(instruction);
  }
}

#endif
