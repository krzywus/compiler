#ifndef ARITHMETIC_H
#define ARITHMETIC_H


using namespace std;

extern map<string, int> forLoopsVariables;
extern vector<string> initializedVariables;
extern long program_k;
long getIdNumIfExistsOrFreeMemoryAddressOtherwise(char* id);
long getFreeMemoryAddress();
int doesStringContainNumber(string str);
/* assignment.h */
long putReferenceVariableInMemoryAndReturnAdress(char* id);

void convertStringToNumberAndPutInRegister(char* num){
  if(bisonDebug) printf("String to convert: %s\n", num);
  char *end;
  long lnum = strtol(num, &end, 10);
  if (num == end ) { // got identifier
    if(bisonDebug) printf("Got memory adress identifier, loading into register: '%s'\n", num);
    if (doesStringContainIdSeparator(num)) { // does id is of form a[b]
        long tmpMemAddr = putReferenceVariableInMemoryAndReturnAdress(num);
        LOADI(tmpMemAddr);
        return;
    }
    if(forLoopsVariables.find(num) != forLoopsVariables.end()) {
       LOAD(forLoopsVariables[num]);
       return;
    }
    if(find(initializedVariables.begin(), initializedVariables.end(), num) == initializedVariables.end()) {
      // arrays could be initialized using other variables, which is hard to detect
      if (!doesStringContainNumber(num)) {
        if(bisonDebug) cout << "UNINITIALIZED_VARIABLE: " << num << endl;
        yyerror(UNINITIALIZED_VARIABLE);
      }
    }
    long i = getIdNumIfExists(num);
    LOAD(i);
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
  long aIdNum = getIdNumIfExistsOrFreeMemoryAddressOtherwise(a);
  if (aIdNum > ids_count) {
    convertStringToNumberAndPutInRegister(a);
    STORE(aIdNum);
  } else {
    if (aIdNum != loadedMemory) {
      LOAD(aIdNum);
    }
    aIdNum = getFreeMemoryAddress();
    STORE(aIdNum);
  }
  long bIdNum = getIdNumIfExistsOrFreeMemoryAddressOtherwise(b);
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
  long pointOfReturn = program_k;
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

  long remainIdNum = getIdNumIfExistsOrFreeMemoryAddressOtherwise(a);
  if (remainIdNum > ids_count) {
    convertStringToNumberAndPutInRegister(a);
  } else {
    LOAD(remainIdNum);
    remainIdNum = getFreeMemoryAddress();
  }
  STORE(remainIdNum);

  long scaledDivisorIdNum = getIdNumIfExistsOrFreeMemoryAddressOtherwise(b);
  if (scaledDivisorIdNum > ids_count) {
    convertStringToNumberAndPutInRegister(b);
  } else {
    LOAD(scaledDivisorIdNum);
    scaledDivisorIdNum = getFreeMemoryAddress();
  }
  STORE(scaledDivisorIdNum);

  long resultIdNum = getFreeMemoryAddress(); // = 0
  convertStringToNumberAndPutInRegister("0");
  STORE(resultIdNum);
	long multipleIdNum = getFreeMemoryAddress(); // = 1
  convertStringToNumberAndPutInRegister("1");
  STORE(multipleIdNum);


  LOAD(scaledDivisorIdNum);
  JZERO((program_k+52));  // dzielenie przez zero

  long pointOfReturn = program_k;
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

  long remainIdNum = getIdNumIfExistsOrFreeMemoryAddressOtherwise(a);
  if (remainIdNum > ids_count) {
    convertStringToNumberAndPutInRegister(a);
  } else {
    LOAD(remainIdNum);
    remainIdNum = getFreeMemoryAddress();
  }
  STORE(remainIdNum);

  long scaledDivisorIdNum = getIdNumIfExistsOrFreeMemoryAddressOtherwise(b);
  if (scaledDivisorIdNum > ids_count) {
    convertStringToNumberAndPutInRegister(b);
  } else {
    LOAD(scaledDivisorIdNum);
    scaledDivisorIdNum = getFreeMemoryAddress();
  }
  STORE(scaledDivisorIdNum);

  long resultIdNum = getFreeMemoryAddress(); // = 0
  convertStringToNumberAndPutInRegister("0");
  STORE(resultIdNum);
	long multipleIdNum = getFreeMemoryAddress(); // = 1
  convertStringToNumberAndPutInRegister("1");
  STORE(multipleIdNum);

  LOAD(scaledDivisorIdNum);
  JZERO((program_k+52));  // dzielenie przez zero

  long pointOfReturn = program_k;
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
