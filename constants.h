#ifndef CONSTANTS_H
#define CONSTANTS_H

#define VAR_STATE 11
#define BEGINZ_STATE 12
#define END_STATE 13

extern int ids_count;
extern char** ids;
extern int free_tmp_pointer;

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

#endif
