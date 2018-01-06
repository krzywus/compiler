#ifndef CONSTANTS_H
#define CONSTANTS_H

#define VAR_STATE 11
#define BEGINZ_STATE 12
#define END_STATE 13

using namespace std;

extern int ids_count;
extern char** ids;
extern int free_tmp_pointer;
extern int bisonDebug;
extern int printK;

void yyerror (char const *);

int getIdNumIfExists(char* id) {
    for(int i=0; i < ids_count; i++){
        if(strcmp(id, ids[i]) == 0){
           return i;
        }
    }
    yyerror(UNDECLARED_VARIABLE);
}

int getIdNumIfExistsOrFreeMemoryAddressOtherwise(char* id) {
    for(int i=0; i < ids_count; i++){
        if(strcmp(id, ids[i]) == 0){
           return i;
        }
    }
    free_tmp_pointer++;
    return free_tmp_pointer;
}

int getFreeMemoryAddress(){
  free_tmp_pointer++;
  return free_tmp_pointer;
}

char* concat(char* a, char* b) {
  char *result = (char*) malloc(strlen(a)+strlen(b)+1);
  strcpy(result, a);
  strcat(result, b);
  return result;
}

int doesStringContainIdSeparator(char* text) {
  char* position = strchr(text, '|');
  if (position) {
    return 1;
  }
  return 0;
}
#endif
