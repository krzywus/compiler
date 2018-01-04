
%{
  #include <stdio.h>
  #include <stdlib.h>
  #include <math.h>
  #include <string.h>

  #include "errors.h"
  #include "pidentifierAdding.h"
  #include "IO.h"

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
  void readAndStore(char* id);
  void writeVariable(char* var);
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
%type <id> identifier
%type <id> value

%%

program:
     VAR vdeclarations BEGINZ commands END    { printResult(); return 0;}

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
     | READ identifier ';'      { readAndStore($2); }
     | WRITE value ';'          { writeVariable($2); }

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
