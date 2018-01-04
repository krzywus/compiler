#ifndef ASSIGNMENT_H
#define ASSIGNMENT_H

extern int getIdNumIfExists(char* id);

void assignToVariable(char* id, char* num) {
  if(debug) printf("assign: %s %s\n", id, num);
  char *end;
  long lnum = strtol(num, &end, 10);
  if (num == end ) { // got identifier
    int i = getIdNumIfExists(end);
    printf("LOAD %d\n", i);
  } else {
    printCommandsForCreatingNumber(lnum);
  }
  int assignId = getIdNumIfExists(id);
  printf("STORE %d\n", assignId);
}

#endif
