#ifndef ASSIGNMENT_H
#define ASSIGNMENT_H

extern long program_k;
extern int getIdNumIfExists(char* id);


void assignToVariable(char* id) {
  if(debug) printf("assign to: '%s'\n", id);
  printf("LOAD %d\n", ids_count); program_k++;
  int assignId = -1;
  if (doesStringContainIdSeparator(id)) { // does id is of form a[b]
      char* bId = strrchr(id, '|') + 1;
      int index = (int)(bId - id - 1);
      int bAddr = getIdNumIfExists(bId);

      char* aId = malloc(sizeof(char)*index);
      memset(aId, '\0', index+1);
      strncpy(aId, id, index);
      char* a0Id = concat(aId, "0");
      int a0IdAddr = getIdNumIfExists(a0Id);

      int a0IdAddrLen = snprintf( NULL, 0, "%d", a0IdAddr );
      char* a0IdAddrString = malloc( a0IdAddrLen + 1 );
      snprintf( a0IdAddrString, a0IdAddrLen + 1, "%d", a0IdAddr );

      int tmpMemAddr = getFreeMemoryAddress();

      convertStringToNumberAndPutInRegister(a0IdAddrString); // put a0 adress in register
      printf("STORE %d\n", tmpMemAddr); program_k++;
      printf("LOAD %d\n", bAddr); program_k++;
      printf("ADD %d\n", tmpMemAddr); program_k++;
      printf("STORE %d\n", tmpMemAddr); program_k++;
      printf("LOAD %d\n", ids_count); program_k++;
      printf("STOREI %d\n", tmpMemAddr); program_k++;
      free(aId);
      free(a0Id);
      free(a0IdAddrString);
  } else {
      assignId = getIdNumIfExists(id);
      printf("STORE %d\n", assignId); program_k++;
  }
  free(id);
}

#endif
