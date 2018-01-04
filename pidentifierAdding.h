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
void checkIfUnique(char* id);
void yyerror(char const *);

void addVarIdentifier(char* id){
  if(debug) printf("BISON: pidentifier found '%s'\n", id);
  checkIfUnique(id);
  ids[ids_count] = id;
  ids_count++;
  if(current_state == BEGINZ_STATE){
    if(debug) printf("Current State: %d. Fixing identifiers.\n", current_state);
    ids_max = ids_count;
    free_tmp_pointer = ids_count+1;
  }else if(ids_count == ids_max-1){
    if(debug) printf("BISON DEBUG: reallocating identifiers due to overflow.\n");
    ids_max += 10;
    char** newpointer = realloc(ids, ids_max * sizeof(char*));
    if (newpointer == NULL) {
      yyerror("Failed to reallocate memory.");
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
