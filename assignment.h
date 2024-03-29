#ifndef ASSIGNMENT_H
#define ASSIGNMENT_H

extern long program_k;
extern long getIdNumIfExists(char* id);
extern vector<string> initializedVariables;
extern map<string, int> forLoopsVariables;
extern long loadedMemory;

long getIdNumIfExistsForAssignment(char* id);
long putReferenceVariableInMemoryAndReturnAdress(char* id);

void assignToVariable(char* id) {
  if(bisonDebug) printf("assign to: '%s'\n", id);
  long assignId = -1;
  if (doesStringContainIdSeparator(id)) { // does id is of form a[b]
      long tmpMemAddr = putReferenceVariableInMemoryAndReturnAdress(id);
      if (loadedMemory != ids_count) {
        LOAD(ids_count);
      }
      STOREI(tmpMemAddr);
  } else {
      if (loadedMemory != ids_count) {
        LOAD(ids_count);
      }
      if(bisonDebug) cout << "getting number" << endl;
      assignId = getIdNumIfExistsForAssignment(id);
      initializedVariables.push_back(id);
      STORE(assignId);
  }
  free(id);
}

long putReferenceVariableInMemoryAndReturnAdress(char* id) {
  char* bId = strrchr(id, '|') + 1;
  if(forLoopsVariables.find(bId) == forLoopsVariables.end()) {
    if(find(initializedVariables.begin(), initializedVariables.end(), bId) == initializedVariables.end()) {
      if(bisonDebug) cout << "UNINITIALIZED_VARIABLE: " << bId << endl;
      yyerror(UNINITIALIZED_VARIABLE);
    }
  }
  long index = (long)(bId - id - 1);
  long bAddr = getIdNumIfExists(bId);

  char* aId = (char*) malloc(sizeof(char)*index);
  memset(aId, '\0', index+1);
  strncpy(aId, id, index);
  char* a0Id = concat(aId, "0");
  long a0IdAddr = getIdNumIfExists(a0Id);

  long a0IdAddrLen = snprintf( NULL, 0, "%ld", a0IdAddr );
  char* a0IdAddrString = (char*) malloc( a0IdAddrLen + 1 );
  snprintf( a0IdAddrString, a0IdAddrLen + 1, "%ld", a0IdAddr );

  long tmpMemAddr = getFreeMemoryAddress();

  if(bisonDebug) printf("Putting in register a0: %s, Adding to memory address: %ld\n", a0IdAddrString, bAddr);
  convertStringToNumberAndPutInRegister(a0IdAddrString); // put a0 adress in register
  STORE(tmpMemAddr);
  LOAD(bAddr);
  ADD(tmpMemAddr);
  STORE(tmpMemAddr);
  free(aId);
  free(a0Id);
  free(a0IdAddrString);

  return tmpMemAddr;
}

#endif
