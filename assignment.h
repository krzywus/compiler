#ifndef ASSIGNMENT_H
#define ASSIGNMENT_H

extern long program_k;
extern long getIdNumIfExists(char* id);
extern vector<string> initializedVariables;
extern map<string, int> forLoopsVariables;

long getIdNumIfExistsForAssignment(char* id){
  for(long i=0; i < normal_ids_count; i++){
      if(ids[i].compare(id) == 0){
        long j =i;
        vector<string> alreadyChecked;
        for (long k = 0; k < arrayIdsToFirstPosition.size(); k++) {
          for (map<string, long>::iterator it = arrayIdsToFirstPosition.begin(); it != arrayIdsToFirstPosition.end(); it++ ) {
            if (j >= it->second && find(alreadyChecked.begin(), alreadyChecked.end(), it->first) == alreadyChecked.end()) {
              if (bisonDebug) { cout << "increasing because of array " << it->first << " by: " << arrayIdsToSize[it->first] << endl; }
              j += arrayIdsToSize[it->first];
              alreadyChecked.push_back(it->first);
            }
          }
        }
        if (bisonDebug) { printf("Matching id with number: %s %ld\n", id, j); }
        return j;
      }
  }
  string idStringWithNumbers = string(id); // check if is an array
  for (long i = 0; i < idStringWithNumbers.length(); i++) {
    if(idStringWithNumbers[i]=='0'||idStringWithNumbers[i]=='1'||idStringWithNumbers[i]=='2'||idStringWithNumbers[i]=='4'
        || idStringWithNumbers[i]=='3' ||idStringWithNumbers[i]=='5'||idStringWithNumbers[i]=='6'
        || idStringWithNumbers[i]=='7' ||idStringWithNumbers[i]=='8'||idStringWithNumbers[i]=='9') {
      string idString = idStringWithNumbers.substr(0, i);
      string idNumbers = idStringWithNumbers.substr(i, idStringWithNumbers.length());
      if(arrayIdsToFirstPosition.find(idString) != arrayIdsToFirstPosition.end()) {
        return (arrayIdsToFirstPosition[idString] + stol(idNumbers));
      }
    }
  }
  if(bisonDebug) cout << "UNDECLARED_VARIABLE: " << id << endl;
  yyerror(UNDECLARED_VARIABLE);
}

void assignToVariable(char* id) {
  if(bisonDebug) printf("assign to: '%s'\n", id);
  LOAD(ids_count);
  long assignId = -1;
  if (doesStringContainIdSeparator(id)) { // does id is of form a[b]
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
      LOAD(ids_count);
      STOREI(tmpMemAddr);
      free(aId);
      free(a0Id);
      free(a0IdAddrString);
  } else {
      if(bisonDebug) cout << "getting number" << endl;
      assignId = getIdNumIfExistsForAssignment(id);
      initializedVariables.push_back(id);
      STORE(assignId);
  }
  free(id);
}

#endif
