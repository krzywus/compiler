#ifndef ASSIGNMENT_H
#define ASSIGNMENT_H

extern int getIdNumIfExists(char* id);

void assignToVariable(char* id) {
  if(debug) printf("assign to: %s\n", id);
  printf("LOAD %d\n", ids_count);
  int assignId = getIdNumIfExists(id);
  printf("STORE %d\n", assignId);
}

#endif
