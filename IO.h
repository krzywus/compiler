#ifndef IO_H
#define IO_H

extern int debug;

extern int current_state;
extern char** ids;
extern int ids_count;
extern int ids_max;

void yyerror(char const *);
int getIdNumIfExists(char* id);

void readAndStore(char* id){
  for(int i=0; i < ids_count; i++){
      if(strcmp(id, ids[i]) == 0){
         printf("GET\nSTORE %d\n", i);
         return;
      }
  }
  yyerror(UNDECLARED_VARIABLE);
}

/**TODO: */
void writeVariable(char* var){
  char *end;
  long lnum = strtol(var, &end, 10);
  if (end == var) {    //if no characters were converted these pointers are equal
    if(debug) printf("BISON DEBUG: got identifier, not value: %s\n", var);
    int i = getIdNumIfExists(var);
    printf("LOAD %d\nPUT\n", i);
  } else {
    /** Trzeba wyliczyć otrzymaną liczbę poprzez instrukcje: "ZERO -> INC -> INC/SHL". */
  }
}

int getIdNumIfExists(char* id){
    for(int i=0; i < ids_count; i++){
        if(strcmp(id, ids[i]) == 0){
           return i;
        }
    }
    yyerror(UNDECLARED_VARIABLE);
}

#endif
