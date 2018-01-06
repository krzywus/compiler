#ifndef PID_ADDING_H
#define PID_ADDING_H

#include "constants.h"

extern int debug;
extern int current_state;
extern char** ids;
extern int ids_count;
extern int ids_max;
extern int free_tmp_pointer;

void addVarIdentifier(char* id);
void addArrayIdentifier(char* id, char* amount);
void checkStateAndIdsOverflow();
void checkIdsOveflow();
void checkIfUnique(char* id);
char* concat(char* a, char* b);
void yyerror(char const *);

void addVarIdentifier(char* id){
  if(debug) printf("BISON: pidentifier found '%s'\n", id);
  checkIfUnique(id);
  ids[ids_count] = id;
  ids_count++;
  checkStateAndIdsOverflow();
}

void addArrayIdentifier(char* id, char* amount){
  if(debug) printf("BISON: array pidentifier found '%s', size: %s\n", id, amount);
  checkIfUnique(id);
  int intAmount = atoi(amount);
  if (intAmount == 0) {
    yyerror(ZERO_ARRAY_DECLARATION);
  }
  for (int i = 0; i < intAmount; i++) {
    int ilen = snprintf( NULL, 0, "%d", i );
    char* inum = (char*) malloc( ilen + 1 );
    snprintf( inum, ilen + 1, "%d", i );
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
    if(debug) printf("Current State: %d. Fixing identifiers.\n", current_state);
    ids_max = ids_count;
  }else {
    checkIdsOveflow();
  }
}

void checkIdsOveflow() {
  if(ids_count == ids_max-1){
    if(debug) printf("BISON DEBUG: reallocating identifiers due to overflow.\n");
    ids_max += 10;
    char** newpointer = (char**) realloc(ids, ids_max * sizeof(char*));
    if (newpointer == NULL) {
      yyerror(REALLOCATE_FAILURE);
    } else {
        ids = newpointer;
    }
  }
}

void checkIfUnique(char* id){
    for(int i=0; i < ids_count; i++){
        if(strcmp(id, ids[i]) == 0){
           yyerror(SECOND_DECLARATION);
        }
    }
}


#endif
