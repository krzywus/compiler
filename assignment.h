#ifndef ASSIGNMENT_H
#define ASSIGNMENT_H

extern long program_k;
extern int getIdNumIfExists(char* id);


void assignToVariable(char* id) {
  if(debug) printf("assign to: '%s'\n", id);
  printf("LOAD %d\n", ids_count); program_k++;
  int assignId = getIdNumIfExists(id);
  printf("STORE %d\n", assignId); program_k++;
  free(id);
}

#endif
