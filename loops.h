#ifndef LOOPS_H
#define LOOPS_H

using namespace std;

extern vector<string> commands;
void convertStringToNumberAndPutInRegister(char* num);

void endWhile(){
  int beginFound = 0;
  if(bisonDebug) cout << "ENDING WHILE" << endl;
  if(bisonDebug) cout << commands.size() << endl;
  int loopStart = -1;
  int max_k = 0;
  for (int i = commands.size()-1; i > 0; i--) {
    // if (commands[i].find("WHILE START") == string::npos) {
      max_k++;
    // }
  }
  max_k++;
  for (int i = commands.size()-1; i > 0; i--) {
      if (commands[i].find("WHILE START") != string::npos) {
        if(bisonDebug) cout << "Loop started at: " << i << endl;
        loopStart = i;
        commands.erase(commands.begin()+i);
        break;
      }
  }
  for (int i = commands.size()-1; i > 0; i--) {
    if (commands[i].find("COND") != string::npos) {
      if (commands[i].find("BEGIN") != string::npos) {
        if (beginFound != 0) {
            loopStart -= 2;
            JUMP(loopStart);
            return;
        }
        if(bisonDebug) cout << "turning flag on at: " << i << endl;
        beginFound = 1;
        commands.erase(commands.begin()+i);
      } else {
        if (commands[i].find("OVER") != string::npos) {
          if (commands[i].find("JZERO") != string::npos) {
            if(bisonDebug) cout << "inserting JZERO at: " << i << endl;
            stringstream ss;
            ss <<  "JZERO " << min((int)(program_k+1), max_k) << endl;
            commands[i] = ss.str();
          } else if (commands[i].find("JUMP") != string::npos) {
            if(bisonDebug) cout << "inserting JUMP at: " << i << endl;
            stringstream ss;
            ss <<  "JUMP " << min((int)(program_k+1), max_k) << endl;
            commands[i] = ss.str();
          }
        }else{
          cout << "something weird at: " << i << endl;
        }
      }
    }
  }
  JUMP(loopStart);
}


#endif
