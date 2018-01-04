#ifndef IO_H
#define IO_H

extern int debug;

extern int current_state;
extern char** ids;
extern int ids_count;
extern int ids_max;

void yyerror(char const *);
int getIdNumIfExists(char* id);
void printCommandsForCreatingNumber(long number);
void convertStringToNumberAndPutInRegister(char* num);

void readAndStore(char* id){
  for(int i=0; i < ids_count; i++){
      if(strcmp(id, ids[i]) == 0){
         printf("GET\nSTORE %d\n", i);
         return;
      }
  }
  yyerror(UNDECLARED_VARIABLE);
}

void writeVariable(char* var){
  convertStringToNumberAndPutInRegister(var);
  printf("PUT\n");
  free(var);
}

/* TODO: probably should belong to some utils.h file*/
int getIdNumIfExists(char* id) {
    for(int i=0; i < ids_count; i++){
        if(strcmp(id, ids[i]) == 0){
           return i;
        }
    }
    yyerror(UNDECLARED_VARIABLE);
}

#endif
