#ifndef CONSTANTS_H
#define CONSTANTS_H

#define VAR_STATE 11
#define BEGINZ_STATE 12
#define END_STATE 13

using namespace std;

extern map<string, int> forLoopsVariables;
extern long ids_count;
extern char** ids;
extern long free_tmp_pointer;
extern long printK;
extern long bisonDebug;

void yyerror (char const *);

long getIdNumIfExists(char* id) {
    for(long i=0; i < ids_count; i++){
        if(strcmp(id, ids[i]) == 0){
           return i;
        }
    }
    if(forLoopsVariables.find(id) != forLoopsVariables.end()) {
      return forLoopsVariables[id];
    }
    yyerror(UNDECLARED_VARIABLE);
}

long getIdNumIfExistsOrFreeMemoryAddressOtherwise(char* id) {
    for(long i=0; i < ids_count; i++){
        if(strcmp(id, ids[i]) == 0){
           return i;
        }
    }
    free_tmp_pointer++;
    return free_tmp_pointer;
}

long getFreeMemoryAddress(){
  free_tmp_pointer++;
  return free_tmp_pointer;
}

char* concat(char* a, char* b) {
  char *result = (char*) malloc(strlen(a)+strlen(b)+1);
  strcpy(result, a);
  strcat(result, b);
  return result;
}

long doesStringContainIdSeparator(char* text) {
  char* position = strchr(text, '|');
  if (position) {
    return 1;
  }
  return 0;
}
#endif
