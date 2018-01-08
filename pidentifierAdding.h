#ifndef PID_ADDING_H
#define PID_ADDING_H

#include "constants.h"

extern vector<string> ids;
extern map<string, long> arrayIdsToSize;
extern map<string, long> arrayIdsToFirstPosition;
extern long current_state;

extern long ids_count;
extern long normal_ids_count;
extern long ids_max;
extern long free_tmp_pointer;

void addVarIdentifier(char* id);
void addArrayIdentifier(char* id, char* amount);
void updateFreeMemoryPointer();
void checkIfUnique(char* id);
char* concat(char* a, char* b);
void yyerror(char const *);

void addVarIdentifier(char* id){
  if(bisonDebug) printf("BISON: pidentifier found '%s'\n", id);
  checkIfUnique(id);

  ids.push_back(id);
  ids_count++;
  normal_ids_count++;
  updateFreeMemoryPointer();
}

void addArrayIdentifier(char* id, char* amount){
  if(bisonDebug) printf("BISON: array pidentifier found '%s', size: %s\n", id, amount);
  checkIfUnique(id);
  long longAmount = atol(amount);
  if (longAmount == 0) {
    yyerror(ZERO_ARRAY_DECLARATION);
  }
  string idString = string(id);
  arrayIdsToSize[idString] = longAmount;
  arrayIdsToFirstPosition[idString] = ids_count;
  ids_count += longAmount;
  updateFreeMemoryPointer();
  free(id);
  free(amount);
}

void updateFreeMemoryPointer() {
  free_tmp_pointer = ids_count;
}

void checkIfUnique(char* id){
    for(long i=0; i < normal_ids_count; i++){
        if(ids[i].compare(id) == 0){
           yyerror(SECOND_DECLARATION);
        }
    }
}


#endif
