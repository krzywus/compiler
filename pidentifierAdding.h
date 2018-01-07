#ifndef PID_ADDING_H
#define PID_ADDING_H

#include "constants.h"

extern long current_state;
extern char** ids;
extern long ids_count;
extern long ids_max;
extern long free_tmp_pointer;

void addVarIdentifier(char* id);
void addArrayIdentifier(char* id, char* amount);
void checkStateAndIdsOverflow();
void checkIdsOveflow();
void checkIfUnique(char* id);
char* concat(char* a, char* b);
void yyerror(char const *);

void addVarIdentifier(char* id){
  if(bisonDebug) printf("BISON: pidentifier found '%s'\n", id);
  checkIfUnique(id);
  ids[ids_count] = id;
  ids_count++;
  checkStateAndIdsOverflow();
}

void addArrayIdentifier(char* id, char* amount){
  if(bisonDebug) printf("BISON: array pidentifier found '%s', size: %s\n", id, amount);
  checkIfUnique(id);
  long intAmount = atoi(amount);
  if (intAmount == 0) {
    yyerror(ZERO_ARRAY_DECLARATION);
  }
  for (long i = 0; i < intAmount; i++) {
    long ilen = snprintf( NULL, 0, "%ld", i );
    char* inum = (char*) malloc( ilen + 1 );
    snprintf( inum, ilen + 1, "%ld", i );
    ids[ids_count] = concat(id, inum);
    ids_count++;
    checkIdsOveflow();
  }
  checkStateAndIdsOverflow();
  free(id);
  free(amount);
}

void checkStateAndIdsOverflow() {
  free_tmp_pointer = ids_count;
  if(current_state == BEGINZ_STATE){
    if(bisonDebug) printf("Current State: %ld. Fixing identifiers.\n", current_state);
    ids_max = ids_count;
  }else {
    checkIdsOveflow();
  }
}

void checkIdsOveflow() {
  if(ids_count == ids_max-1){
    if(bisonDebug) printf("BISON DEBUG: reallocating identifiers due to overflow.\n");
    ids_max += 10000000;
    char** newpointer = (char**) realloc(ids, ids_max * sizeof(char*));
    if (newpointer == NULL) {
      yyerror(REALLOCATE_FAILURE);
    } else {
        ids = newpointer;
    }
  }
}

void checkIfUnique(char* id){
    for(long i=0; i < ids_count; i++){
        if(strcmp(id, ids[i]) == 0){
           yyerror(SECOND_DECLARATION);
        }
    }
}


#endif
