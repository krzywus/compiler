#ifndef LOOPS_H
#define LOOPS_H

using namespace std;

extern vector<string> commands;
extern map<string, int> forLoopsVariables;
void convertStringToNumberAndPutInRegister(char* num);
long getIdNumIfExistsOrFreeMemoryAddressOtherwise(char* id);

void endLoop(long loopStart);
long createForIteratorAndReturnHisMemoryAddress(char* id);

void endWhile(){
  if(bisonDebug) cout << "ENDING WHILE, k: " << program_k << " commands_size: " << commands.size() << endl;
  for (long i = commands.size()-1; i > 0; i--) {
      if (commands[i].find("WHILE START") != string::npos) {
        if(bisonDebug) cout << "Loop started at: " << i << endl;
        endLoop(i);
        return;
      }
  }
  yyerror(WHILE_LOOP_ENDING_FAILURE);
}


void forFromTo(char* id, char* from, char* to){
    long idMemAddr = createForIteratorAndReturnHisMemoryAddress(id);

    convertStringToNumberAndPutInRegister(from);
    STORE(idMemAddr);
    convertStringToNumberAndPutInRegister(to);
    long tmpMemAddr = getFreeMemoryAddress();
    STORE(tmpMemAddr);

    stringstream ss;
    ss << "FINCSTART " << id << endl;
    commands.push_back(ss.str());
    LOAD(tmpMemAddr);
    INC();
    SUB(idMemAddr);
    commands.push_back("COND JZERO OVER\n"); program_k++;
    commands.push_back("COND BEGIN\n");

    free(from);
    free(to);
}

void forFromDownTo(char* id, char* from, char* to){
  long idMemAddr = createForIteratorAndReturnHisMemoryAddress(id);

  convertStringToNumberAndPutInRegister(from);
  STORE(idMemAddr);
  convertStringToNumberAndPutInRegister(to);
  long tmpMemAddr = getFreeMemoryAddress();
  STORE(tmpMemAddr);

  stringstream ss;
  ss << "FDECSTART " << id << endl;
  commands.push_back(ss.str());
  LOAD(idMemAddr);
  INC();
  SUB(tmpMemAddr);
  commands.push_back("COND JZERO OVER\n"); program_k++;
  commands.push_back("COND BEGIN\n");

  free(from);
  free(to);
}

long createForIteratorAndReturnHisMemoryAddress(char* id){
  long idMemAddr = getIdNumIfExistsOrFreeMemoryAddressOtherwise(id);
  if (idMemAddr < ids_count) {
    yyerror(SECOND_DECLARATION);
  }
  forLoopsVariables[id] = idMemAddr;
  return idMemAddr;
}

void endFor(){
  if(bisonDebug) cout << "ENDING FOR, k: " << program_k << " commands_size: " << commands.size() << endl;
  long loopStart = -1;
  int wasDownTo = 0;
  for (long i = commands.size()-1; i > 0; i--) {
      if (commands[i].find("FINCSTART") != string::npos) {
        if(bisonDebug) cout << "Loop started at: " << i << endl;
        loopStart = i;
      }else if (commands[i].find("FDECSTART") != string::npos) {
        if(bisonDebug) cout << "Loop started at: " << i << endl;
        loopStart = i;
        wasDownTo = 1;
      }
      if (loopStart != -1) {
        string idString = commands[loopStart].substr(10, commands[loopStart].length()-11);
        LOAD(forLoopsVariables[idString]);
        if (wasDownTo == 0) {
          INC();
        } else {
          JZERO(program_k+4);
          DEC();
        }
        STORE(forLoopsVariables[idString]);
        if(bisonDebug) cout << "removing from for variables: '" << idString << "'" << endl;
        forLoopsVariables.erase(idString);

        endLoop(loopStart);
        return;
      }
  }
  yyerror(FOR_LOOP_ENDING_FAILURE);
}

void endLoop(long loopStart){
  commands.erase(commands.begin()+loopStart);
  int beginFound = 0;
  for (long i = commands.size()-1; i > 0; i--) {
    if (commands[i].find("COND") != string::npos) {
      if (commands[i].find("BEGIN") != string::npos) {
        if (beginFound > 0) {
            if(bisonDebug) cout << "BEGIN found, decreasing loopStart place." << endl;
            loopStart -= 2; // zmniejszamy o 2 za każde 2 instrukcje, które będą usuwane
        } else if (beginFound == 0){
          if(bisonDebug) cout << "turning flag on at: " << i << endl;
          commands.erase(commands.begin()+i);
        }
        beginFound++;
      } else if (beginFound < 2) {
        if (commands[i].find("OVER") != string::npos) {
          if(bisonDebug) cout << "inserting JZERO/JUMP at: " << i << endl;
          stringstream ss;
          if (commands[i].find("JZERO") != string::npos) {
            ss <<  "JZERO " << (program_k+1) << endl;
          } else if (commands[i].find("JUMP") != string::npos) {
            ss <<  "JUMP " << (program_k+1) << endl;
          }
          commands[i] = ss.str();
        }else{
          yyerror(LOOP_ENDING_FAILURE);
        }
      }
    }
  }
  if(bisonDebug) cout << "Inserting JUMP " << loopStart << " at " << program_k << endl;
  JUMP(loopStart);
}


#endif
