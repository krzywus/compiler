#ifndef IO_H
#define IO_H

extern long current_state;
extern char** ids;
extern long ids_count;
extern long ids_max;
extern long program_k;
extern vector<string> initializedVariables;

void yyerror(char const *);
long getIdNumIfExists(char* id);
void convertStringToNumberAndPutInRegister(char* num);

void readAndStore(char* id){
  if (doesStringContainIdSeparator(id)) { // is id of form a[b]
    char* bId = strrchr(id, '|') + 1;
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

    convertStringToNumberAndPutInRegister(a0IdAddrString); // put a0 adress in register
    STORE(tmpMemAddr);
    LOAD(bAddr);
    ADD(tmpMemAddr);
    STORE(tmpMemAddr);
    free(aId);
    free(a0Id);
    free(a0IdAddrString);
    GET();
    STOREI(tmpMemAddr);
  } else {
    for(long i=0; i < ids_count; i++){
      if(strcmp(id, ids[i]) == 0){
        GET();
        STORE(i);
        initializedVariables.push_back(id);
        return;
      }
    }
    yyerror(UNDECLARED_VARIABLE);
  }
}

void writeVariable(char* var){
  convertStringToNumberAndPutInRegister(var);
  PUT();
  free(var);
}

#endif
