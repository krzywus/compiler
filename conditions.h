#ifndef CONDITIONS_H
#define CONDITIONS_H

using namespace std;

extern vector<string> commands;
void convertStringToNumberAndPutInRegister(char* num);

void ifEnded(int modifier){
  int beginFound = 0;
  if(bisonDebug) cout << "ENDING IF" << endl;
  if(bisonDebug) cout << commands.size() << endl;
  for (int i = commands.size()-1; i > 0; i--) {
    if (commands[i].find("COND") != string::npos) {
      if (commands[i].find("BEGIN") != string::npos) {
        if (beginFound != 0) {
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
            ss <<  "JZERO " << (program_k+modifier) << endl;
            commands[i] = ss.str();
          } else if (commands[i].find("JUMP") != string::npos) {
            if(bisonDebug) cout << "inserting JUMP at: " << i << endl;
            stringstream ss;
            ss <<  "JUMP " << (program_k+modifier) << endl;
            commands[i] = ss.str();
          }
        }else{
          cout << "something weird at: " << i << endl;
        }
      }
    }
  }
}

void elseEnded(){
  int beginFound = 0;
  if(bisonDebug) cout << "ENDING ELSE, k: " << program_k <<  endl;
  int max_k = 0;
  for (int i = commands.size()-1; i > 0; i--) {
    if (commands[i].find("BEGIN") == string::npos) {
      max_k++;
    }
  }
  max_k++;
  if(bisonDebug) cout << "max_k: " << max_k << "  comLen: " << commands.size() << endl;
  for (int i = commands.size()-1; i > 0; i--) {
    if (commands[i].find("COND") != string::npos) {
      if (commands[i].find("BEGIN") != string::npos) {
        if (beginFound != 0) {
            return;
        }
        if(bisonDebug) cout << "turning flag on at: " << i << endl;
        beginFound = 1;
        commands.erase(commands.begin()+i);
      } else {
          if (commands[i].find("JUMP OVER") != string::npos) {
              if(bisonDebug) cout << "inserting JUMP at: " << i << endl;
              stringstream ss;
              ss <<  "JUMP " << min((int)(program_k+1), max_k) << endl;
              commands[i] = ss.str();
          }else{
            cout << "something weird at: " << i << endl;
          }
        }
      }
    }
}

void condISEQ(string a, string b) {
  char * a_cstr = new char[a.size() + 1];
  std::copy(a.begin(), a.end(), a_cstr);
  a_cstr[a.size()] = '\0';
  char * b_cstr = new char[a.size() + 1];
  std::copy(b.begin(), b.end(), b_cstr);
  b_cstr[b.size()] = '\0';

  convertStringToNumberAndPutInRegister(b_cstr);
  int tmpMemAddr = getFreeMemoryAddress();
  STORE(tmpMemAddr);
  convertStringToNumberAndPutInRegister(a_cstr);
  INC();
  SUB(tmpMemAddr);
  commands.push_back("COND JZERO OVER\n"); program_k++;
  DEC();
  JZERO(program_k+2);
  commands.push_back("COND JUMP OVER\n"); program_k++;
  commands.push_back("COND BEGIN\n");

  delete[] a_cstr;
  delete[] b_cstr;
}

void condUNEQ(string a, string b) {
  char * a_cstr = new char[a.size() + 1];
  std::copy(a.begin(), a.end(), a_cstr);
  a_cstr[a.size()] = '\0';
  char * b_cstr = new char[a.size() + 1];
  std::copy(b.begin(), b.end(), b_cstr);
  b_cstr[b.size()] = '\0';

  convertStringToNumberAndPutInRegister(b_cstr);
  int tmpMemAddr = getFreeMemoryAddress();
  STORE(tmpMemAddr);
  convertStringToNumberAndPutInRegister(a_cstr);
  INC();
  SUB(tmpMemAddr);
  JZERO(program_k+3);
  DEC();
  commands.push_back("COND JZERO OVER\n"); program_k++;
  commands.push_back("COND BEGIN\n");

  delete[] a_cstr;
  delete[] b_cstr;
}

void condLESS(string a, string b) {
    char * a_cstr = new char[a.size() + 1];
    std::copy(a.begin(), a.end(), a_cstr);
    a_cstr[a.size()] = '\0';
    char * b_cstr = new char[a.size() + 1];
    std::copy(b.begin(), b.end(), b_cstr);
    b_cstr[b.size()] = '\0';

    convertStringToNumberAndPutInRegister(a_cstr);
    int tmpMemAddr = getFreeMemoryAddress();
    STORE(tmpMemAddr);
    convertStringToNumberAndPutInRegister(b_cstr);
    SUB(tmpMemAddr);
    commands.push_back("COND JZERO OVER\n"); program_k++;
    commands.push_back("COND BEGIN\n");

    delete[] a_cstr;
    delete[] b_cstr;
}

void condLEQ(string a, string b) {
  char * a_cstr = new char[a.size() + 1];
  std::copy(a.begin(), a.end(), a_cstr);
  a_cstr[a.size()] = '\0';
  char * b_cstr = new char[a.size() + 1];
  std::copy(b.begin(), b.end(), b_cstr);
  b_cstr[b.size()] = '\0';

  convertStringToNumberAndPutInRegister(a_cstr);
  int tmpMemAddr = getFreeMemoryAddress();
  STORE(tmpMemAddr);
  convertStringToNumberAndPutInRegister(b_cstr);
  INC();
  SUB(tmpMemAddr);
  commands.push_back("COND JZERO OVER\n"); program_k++;
  commands.push_back("COND BEGIN\n");

  delete[] a_cstr;
  delete[] b_cstr;
}

void condGREATER(string a, string b) {
      char * a_cstr = new char[a.size() + 1];
      std::copy(a.begin(), a.end(), a_cstr);
      a_cstr[a.size()] = '\0';
      char * b_cstr = new char[a.size() + 1];
      std::copy(b.begin(), b.end(), b_cstr);
      b_cstr[b.size()] = '\0';

      convertStringToNumberAndPutInRegister(b_cstr);
      int tmpMemAddr = getFreeMemoryAddress();
      STORE(tmpMemAddr);
      convertStringToNumberAndPutInRegister(a_cstr);
      SUB(tmpMemAddr);
      commands.push_back("COND JZERO OVER\n"); program_k++;
      commands.push_back("COND BEGIN\n");

      delete[] a_cstr;
      delete[] b_cstr;
}

void condGTEQ(string a, string b) {
    char * a_cstr = new char[a.size() + 1];
    std::copy(a.begin(), a.end(), a_cstr);
    a_cstr[a.size()] = '\0';
    char * b_cstr = new char[a.size() + 1];
    std::copy(b.begin(), b.end(), b_cstr);
    b_cstr[b.size()] = '\0';

    convertStringToNumberAndPutInRegister(b_cstr);
    int tmpMemAddr = getFreeMemoryAddress();
    STORE(tmpMemAddr);
    convertStringToNumberAndPutInRegister(a_cstr);
    INC();
    SUB(tmpMemAddr);
    commands.push_back("COND JZERO OVER\n"); program_k++;
    commands.push_back("COND BEGIN\n");

    delete[] a_cstr;
    delete[] b_cstr;
}


#endif
