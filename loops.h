#ifndef LOOPS_H
#define LOOPS_H

using namespace std;

extern vector<string> commands;
extern map<string, int> forLoopsVariables;
void convertStringToNumberAndPutInRegister(char* num);
long getIdNumIfExistsOrFreeMemoryAddressOtherwise(char* id);

void endWhile(){
  long beginFound = 0;
  if(bisonDebug) cout << "ENDING WHILE, k:" << program_k << endl;
  if(bisonDebug) cout << "commands size " << commands.size() << endl;
  long loopStart = -1;
  long max_k = commands.size();
  for (long i = commands.size()-1; i > 0; i--) {
      if (commands[i].find("WHILE START") != string::npos) {
        if(bisonDebug) cout << "Loop started at: " << i << endl;
        loopStart = i;
        commands.erase(commands.begin()+i);
        break;
      }
  }
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
          if (commands[i].find("JZERO") != string::npos) {
            if(bisonDebug) cout << "inserting JZERO at: " << i << endl;
            stringstream ss;
            ss <<  "JZERO " << min((long)(program_k+1), max_k) << endl;
            commands[i] = ss.str();
          } else if (commands[i].find("JUMP") != string::npos) {
            if(bisonDebug) cout << "inserting JUMP at: " << i << endl;
            stringstream ss;
            ss <<  "JUMP " << min((long)(program_k+1), max_k) << endl;
            commands[i] = ss.str();
          }
        }else{
          cout << "something weird at: " << i << endl;
        }
      }
    }
  }
  if(bisonDebug) cout << "Inserting JUMP " << loopStart << " at " << program_k << endl;
  JUMP(loopStart);
}


void forFromTo(char* id, char* from, char* to){
    long idMemAddr = getIdNumIfExistsOrFreeMemoryAddressOtherwise(id);
    if (idMemAddr < ids_count) {
      yyerror(SECOND_DECLARATION);
    }
    forLoopsVariables[id] = idMemAddr;

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
  long idMemAddr = getIdNumIfExistsOrFreeMemoryAddressOtherwise(id);
  if (idMemAddr < ids_count) {
    yyerror(SECOND_DECLARATION);
  }
  forLoopsVariables[id] = idMemAddr;

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

void endFor(){
  long beginFound = 0;
  if(bisonDebug) cout << "ENDING FOR, k: " << program_k << endl;
  if(bisonDebug) cout << "commands_size: " << commands.size() << endl;
  long loopStart = -1;
  for (long i = commands.size()-1; i > 0; i--) {
      if (commands[i].find("FINCSTART") != string::npos) {
        if(bisonDebug) cout << "Loop started at: " << i << endl;
        loopStart = i;
        string idString = commands[i].substr(10, commands[i].length()-11);

        LOAD(forLoopsVariables[idString]);
        INC();
        STORE(forLoopsVariables[idString]);

        if(bisonDebug) cout << "removing from for variables: '" << idString << "'" << endl;
        forLoopsVariables.erase(idString);
        commands.erase(commands.begin()+i);
        break;
      }
      if (commands[i].find("FDECSTART") != string::npos) {
        if(bisonDebug) cout << "Loop started at: " << i << endl;
        loopStart = i;
        string idString = commands[i].substr(10, commands[i].length()-11);

        LOAD(forLoopsVariables[idString]);
        JZERO(program_k+4);
        DEC();
        STORE(forLoopsVariables[idString]);

        if(bisonDebug) cout << "removing from for variables: '" << idString << "'" << endl;
        forLoopsVariables.erase(idString);
        commands.erase(commands.begin()+i);
        break;
      }
  }
  long max_k = 0;
  for (long i = commands.size()-1; i > 0; i--) {
    max_k++;
  }
  max_k++;
  if(bisonDebug) cout << "max_k: " << max_k << endl;
  for (long i = commands.size()-1; i > 0; i--) {
    if (commands[i].find("COND") != string::npos) {
      if (commands[i].find("BEGIN") != string::npos) {
        if (beginFound != 0) {
            loopStart -= 2; // zmniejszamy o 2 za każde 2 instrukcje, które będą usuwane
            beginFound++;
        } else {
          if(bisonDebug) cout << "turning flag on at: " << i << endl;
          beginFound = 1;
          commands.erase(commands.begin()+i);
        }
      } else if (beginFound < 2) {
        if (commands[i].find("OVER") != string::npos) {
          if (commands[i].find("JZERO") != string::npos) {
            if(bisonDebug) cout << "inserting JZERO at: " << i << endl;
            stringstream ss;
            ss <<  "JZERO " << min((long)(program_k+1), max_k) << endl;
            commands[i] = ss.str();
          } else if (commands[i].find("JUMP") != string::npos) {
            if(bisonDebug) cout << "inserting JUMP at: " << i << endl;
            stringstream ss;
            ss <<  "JUMP " << min((long)(program_k+1), max_k) << endl;
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
