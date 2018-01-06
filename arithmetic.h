#ifndef ARITHMETIC_H
#define ARITHMETIC_H


using namespace std;

extern map<string, int> forLoopsVariables;
extern vector<string> initializedVariables;
extern long program_k;
int getIdNumIfExistsOrFreeMemoryAddressOtherwise(char* id);
int getFreeMemoryAddress();

void convertStringToNumberAndPutInRegister(char* num){
  if(bisonDebug) printf("String to convert: %s\n", num);
  char *end;
  long lnum = strtol(num, &end, 10);
  if (num == end ) { // got identifier
    if(bisonDebug) printf("Got memory adress identifier, loading into register: '%s'\n", num);
    if (doesStringContainIdSeparator(num)) { // does id is of form a[b]
        char* bId = strrchr(num, '|') + 1;
        int index = (int)(bId - num - 1);
        int bAddr = getIdNumIfExists(bId);

        char* aId = (char*) malloc(sizeof(char)*index);
        memset(aId, '\0', index+1);
        strncpy(aId, num, index);
        char* a0Id = concat(aId, "0");
        int a0IdAddr = getIdNumIfExists(a0Id);

        int a0IdAddrLen = snprintf( NULL, 0, "%d", a0IdAddr );
        char* a0IdAddrString = (char*) malloc( a0IdAddrLen + 1 );
        snprintf( a0IdAddrString, a0IdAddrLen + 1, "%d", a0IdAddr );

        int tmpMemAddr = getFreeMemoryAddress();

        convertStringToNumberAndPutInRegister(a0IdAddrString); // put a0 adress in register
        STORE(tmpMemAddr);
        LOAD(bAddr);
        ADD(tmpMemAddr);
        STORE(tmpMemAddr);
        LOADI(tmpMemAddr);
        free(aId);
        free(a0Id);
        free(a0IdAddrString);
    } else {
      if(forLoopsVariables.find(num) != forLoopsVariables.end()) {
         LOAD(forLoopsVariables[num]);
         return;
      }
      if(find(initializedVariables.begin(), initializedVariables.end(), num) == initializedVariables.end()) {
        // arrays could be initialized using other variables, which is hard to detect
        int flag = 0;
        for(int i=0; num[i] != '\0'; i++) {
          if(num[i]=='0'||num[i]=='1'||num[i]=='2'||num[i]=='3'||num[i]=='5'||num[i]=='6'||num[i]=='7'||num[i]=='8'||num[i]=='9') {
            flag++; break;
          }
        }
        if (flag == 0) {
          if(bisonDebug) cout << "UNINITIALIZED_VARIABLE: " << num << endl;
          yyerror(UNINITIALIZED_VARIABLE);
        }
      }
      int i = getIdNumIfExists(num);
      LOAD(i);
    }
  } else {
    /** Trzeba wyliczyć otrzymaną liczbę poprzez instrukcje: "ZERO -> INC -> INC/SHL". */
    if(bisonDebug) printf("Got number, calculating and putting into register.\n");
    printCommandsForCreatingNumber(lnum);
  }
}

void putValueToTmp(char* num){
  if(bisonDebug) printf("putting number to tmp: %s\n", num);
  convertStringToNumberAndPutInRegister(num);
  STORE(ids_count);
  free(num);
}

void addition(char* a, char* b) {
	if(bisonDebug) printf("addition: %s %s\n", a, b);
  convertStringToNumberAndPutInRegister(a);
  STORE(ids_count);
  convertStringToNumberAndPutInRegister(b);
  ADD(ids_count);
  STORE(ids_count);
  free(a);
  free(b);
}

void substraction(char* a, char* b) {
	if(bisonDebug) printf("substraction: %s %s\n", a, b);
  convertStringToNumberAndPutInRegister(b);
  STORE(ids_count);
  convertStringToNumberAndPutInRegister(a);
  SUB(ids_count);
  STORE(ids_count);
  free(a);
  free(b);
}

void multiply(char* a, char* b) {
  if(bisonDebug) printf("multiply: %s %s\n", a, b);
  int aIdNum = getIdNumIfExistsOrFreeMemoryAddressOtherwise(a);
  if (aIdNum > ids_count) {
    convertStringToNumberAndPutInRegister(a);
    STORE(aIdNum);
  } else {
    LOAD(aIdNum);
    aIdNum = getFreeMemoryAddress();
    STORE(aIdNum);
  }
  int bIdNum = getIdNumIfExistsOrFreeMemoryAddressOtherwise(b);
  if (bIdNum > ids_count) {
    convertStringToNumberAndPutInRegister(b);
    STORE(bIdNum);
  } else {
    LOAD(bIdNum);
    bIdNum = getFreeMemoryAddress();
    STORE(bIdNum);
  }
  char* result = strdup("0"); // neccessary, will be freed inside putValueToTmp
  putValueToTmp(result);
  int pointOfReturn = program_k;
  LOAD(aIdNum);
  JZERO(program_k+13);
      DEC();
      JODD(program_k+4);
          LOAD(ids_count);
          ADD(bIdNum);
          STORE(ids_count);
      LOAD(aIdNum);
      SHR();
      STORE(aIdNum);
      LOAD(bIdNum);
      SHL();
      STORE(bIdNum);
  JUMP(pointOfReturn);
  free(a);
  free(b);
}

void divide(char* a, char* b) {
	if(bisonDebug) printf("divide: %s %s\n", a, b);
  if (strcmp(b, "0") == 0) {
    if(bisonDebug) printf("Dividing by zero.\n");
    ZERO();
    STORE(ids_count);
  }

  int remainIdNum = getIdNumIfExistsOrFreeMemoryAddressOtherwise(a);
  if (remainIdNum > ids_count) {
    convertStringToNumberAndPutInRegister(a);
  } else {
    LOAD(remainIdNum);
    remainIdNum = getFreeMemoryAddress();
  }
  STORE(remainIdNum);

  int scaledDivisorIdNum = getIdNumIfExistsOrFreeMemoryAddressOtherwise(b);
  if (scaledDivisorIdNum > ids_count) {
    convertStringToNumberAndPutInRegister(b);
  } else {
    LOAD(scaledDivisorIdNum);
    scaledDivisorIdNum = getFreeMemoryAddress();
  }
  STORE(scaledDivisorIdNum);

  int resultIdNum = getFreeMemoryAddress(); // = 0
  convertStringToNumberAndPutInRegister("0");
  STORE(resultIdNum);
	int multipleIdNum = getFreeMemoryAddress(); // = 1
  convertStringToNumberAndPutInRegister("1");
  STORE(multipleIdNum);


  LOAD(scaledDivisorIdNum);
  JZERO((program_k+52));  // dzielenie przez zero

  int pointOfReturn = program_k;
  LOAD(remainIdNum);
  SUB(scaledDivisorIdNum);
  JZERO(program_k+8);  //while (scaledDivisor < remain=dividend)
      LOAD(scaledDivisorIdNum);
      SHL();
      STORE(scaledDivisorIdNum);
      LOAD(multipleIdNum);
      SHL();
      STORE(multipleIdNum);
      JUMP(pointOfReturn);  // end while

  // powtórz raz pętlę, żeby zrobić do..while
  LOAD(scaledDivisorIdNum);
  INC();
  SUB(remainIdNum);
  JZERO(program_k+4);  // do ifa
  DEC();
  JZERO(program_k+2);  // do ifa
  JUMP(program_k+7);  // omijamy ifa
      // if (remain >= scaled_divisor)
      LOAD(remainIdNum);
      SUB(scaledDivisorIdNum);
      STORE(remainIdNum);
      LOAD(resultIdNum);
      ADD(multipleIdNum);
      STORE(resultIdNum);
  LOAD(scaledDivisorIdNum);
  SHR();
  STORE(scaledDivisorIdNum);
  LOAD(multipleIdNum);
  SHR();
  STORE(multipleIdNum);
  // while (multiple != 0)
  pointOfReturn = program_k;
  LOAD(multipleIdNum);  // unnecessary?
  JZERO(program_k+21);  // while
      LOAD(scaledDivisorIdNum);
      INC();
      SUB(remainIdNum);
      JZERO(program_k+4);  // do ifa
      DEC();
      JZERO(program_k+2);  // do ifa
      JUMP(program_k+7);  // omijamy ifa
          // if (remain >= scaled_divisor)
          LOAD(remainIdNum);
          SUB(scaledDivisorIdNum);
          STORE(remainIdNum);
          LOAD(resultIdNum);
          ADD(multipleIdNum);
          STORE(resultIdNum);
      LOAD(scaledDivisorIdNum);
      SHR();
      STORE(scaledDivisorIdNum);
      LOAD(multipleIdNum);
      SHR();
      STORE(multipleIdNum);
      JUMP(pointOfReturn);

  LOAD(resultIdNum);
  STORE(ids_count);
  free(a);
  free(b);
}

void mod(char* a, char* b) {
	if(bisonDebug) printf("mod: %s %s\n", a, b);
  if (strcmp(b, "0") == 0) {
    if(bisonDebug) printf("Modulo zero.\n");
    ZERO();
    STORE(ids_count);
  }

  int remainIdNum = getIdNumIfExistsOrFreeMemoryAddressOtherwise(a);
  if (remainIdNum > ids_count) {
    convertStringToNumberAndPutInRegister(a);
  } else {
    LOAD(remainIdNum);
    remainIdNum = getFreeMemoryAddress();
  }
  STORE(remainIdNum);

  int scaledDivisorIdNum = getIdNumIfExistsOrFreeMemoryAddressOtherwise(b);
  if (scaledDivisorIdNum > ids_count) {
    convertStringToNumberAndPutInRegister(b);
  } else {
    LOAD(scaledDivisorIdNum);
    scaledDivisorIdNum = getFreeMemoryAddress();
  }
  STORE(scaledDivisorIdNum);

  int resultIdNum = getFreeMemoryAddress(); // = 0
  convertStringToNumberAndPutInRegister("0");
  STORE(resultIdNum);
	int multipleIdNum = getFreeMemoryAddress(); // = 1
  convertStringToNumberAndPutInRegister("1");
  STORE(multipleIdNum);

  LOAD(scaledDivisorIdNum);
  JZERO((program_k+52));  // dzielenie przez zero

  int pointOfReturn = program_k;
  LOAD(remainIdNum);
  SUB(scaledDivisorIdNum);
  JZERO(program_k+8);  //while (scaledDivisor < remain=dividend)
      LOAD(scaledDivisorIdNum);
      SHL();
      STORE(scaledDivisorIdNum);
      LOAD(multipleIdNum);
      SHL();
      STORE(multipleIdNum);
      JUMP(pointOfReturn);  // end while

  // powtórz raz pętlę, żeby zrobić do..while
  LOAD(scaledDivisorIdNum);
  INC();
  SUB(remainIdNum);
  JZERO(program_k+4);  // do ifa
  DEC();
  JZERO(program_k+2);  // do ifa
  JUMP(program_k+4);  // omijamy ifa
      // if (remain >= scaled_divisor)
      LOAD(remainIdNum);
      SUB(scaledDivisorIdNum);
      STORE(remainIdNum);
  LOAD(scaledDivisorIdNum);
  SHR();
  STORE(scaledDivisorIdNum);
  LOAD(multipleIdNum);
  SHR();
  STORE(multipleIdNum);
  // while (multiple != 0)
  pointOfReturn = program_k;
  LOAD(multipleIdNum);  // unnecessary?
  JZERO(program_k+18);  // while
      LOAD(scaledDivisorIdNum);
      INC();
      SUB(remainIdNum);
      JZERO(program_k+4);  // do ifa
      DEC();
      JZERO(program_k+2);  // do ifa
      JUMP(program_k+4);  // omijamy ifa
          // if (remain >= scaled_divisor)
          LOAD(remainIdNum);
          SUB(scaledDivisorIdNum);
          STORE(remainIdNum);
      LOAD(scaledDivisorIdNum);
      SHR();
      STORE(scaledDivisorIdNum);
      LOAD(multipleIdNum);
      SHR();
      STORE(multipleIdNum);
      JUMP(pointOfReturn);

  LOAD(remainIdNum);
  STORE(ids_count);
  free(a);
  free(b);
}

#endif
