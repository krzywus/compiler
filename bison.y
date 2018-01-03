
%{
  #include <stdio.h>
  #include <stdlib.h>
  #include <math.h>
  #include <string.h>

  #include "errors.h"


	#define VAR_STATE 11
	#define BEGINZ_STATE 12
	#define END_STATE 13
  int current_state = -1;

  int ids_max = 0;
  int ids_count = 0;
  char** ids;

  int yylex (void);
  void yyerror (char const *);

  void initialize();
  void finalize();
  void printResult();
  void addVarIdentifier(char* id);
  void checkIfIdExists(char* id);
  int getErrorCode(char const *s);
%}

%union{
    long num;
    char* id;
}


%left '-' '+'
%left '*' '/' '%'
%start program
%token VAR BEGINZ END  /* sections */
%token IF THEN ELSE ENDIF /* if commands */
%token WHILE DO ENDWHILE FOR FROM TO DOWNTO ENDFOR /* loops commands */
%token num            /* value */
%token pidentifier    /* identifier */
%token READ WRITE     /* I/O */
%token '[' ']' '>' '<' ';'
%token ASSIGN ":="
%token ISEQ "="
%token LEQ "<="
%token GTEQ ">="
%token UNEQ "<>"
%token EOL /* miscellaneous */

%type <id> pidentifier

%%

program:
     VAR vdeclarations BEGINZ commands END

vdeclarations:
     vdeclarations pidentifier               { addVarIdentifier($2); }
     | vdeclarations pidentifier '[' num ']'
     |

commands:
     commands command
     | command

command:
     identifier ASSIGN expression ';'
     | IF condition THEN commands ELSE commands ENDIF
     | IF condition THEN commands ENDIF
     | WHILE condition DO commands ENDWHILE
     | FOR pidentifier FROM value TO value DO commands ENDFOR
     | FOR pidentifier FROM value DOWNTO value DO commands ENDFOR
     | READ identifier ';'
     | WRITE value ';'

expression:
     value
     | value '+' value
     | value '-' value
     | value '*' value
     | value '/' value
     | value '%' value

condition:
     value ISEQ value
     | value UNEQ value
     | value '<' value
     | value '>' value
     | value LEQ value
     | value GTEQ value

value:
     num
     | identifier

identifier:
     pidentifier
     | pidentifier '[' pidentifier ']'
     | pidentifier '[' num ']'



%%
int main (void) {
  initialize();
  long result = 0;
  /*while(result == 0) {*/
	  result = yyparse();
	/*}*/
  finalize();
  return 0;
}

void initialize(){
  ids_count = 0;
  ids_max = 20;
  ids = malloc(ids_max * sizeof(char*));
}

void finalize(){
  printf("Identifiers:\n");
  for(int i=0; i < ids_count; i++){
    printf("'%s'\n", ids[i]);
    free(ids[i]);
  }
  free(ids);
}

void addVarIdentifier(char* id){
  printf("BISON: pidentifier found '%s'\n", id);
  checkIfIdExists(id);
  ids[ids_count] = id;
  ids_count++;
  if(current_state == BEGINZ_STATE){
    printf("Current State: %d. Fixing identifiers.\n", current_state);
    ids_max = ids_count;
  }else if(ids_count == ids_max-1){
    printf("BISON DEBUG: reallocating identifiers due to overflow.\n");
    ids_max += 10;
    char** newpointer = realloc(ids, ids_max * sizeof(char*));
    if (newpointer == NULL) {
      yyerror("Failed to reallocate memory.");
    } else {
        ids = newpointer;
    }
  }
}

void checkIfIdExists(char* id){
    for(int i=0; i < ids_count; i++){
        if(strcmp(id, ids[i]) == 0){
           yyerror(SECOND_DECLARATION);
        }
    }
}

void printResult(){
  printf("HALT\n");
}

/* Called by yyparse on error.  */
void yyerror (char const *s)
{
  fprintf (stderr, "BISON: %s\n", s);
  finalize();
  exit(getErrorCode(s));
  /*main();*/
}
