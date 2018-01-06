
%{
  #include <stdio.h>
  #include <stdlib.h>
  #include <math.h>
  #include <string.h>
  #include <stack>
	#include <vector>
  #include <string>
  #include <iostream>

  #include "commands.h"
  #include "errors.h"
  #include "pidentifierAdding.h"
  #include "IO.h"
  #include "numberCreation.h"
  #include "assignment.h"
  #include "arithmetic.h"

  using namespace std;

  int current_state = -1;

	vector<string> commands;

  int ids_max = 0;
  int ids_count = 0;
  char** ids;
  long program_k;
  long code_k;
  int free_tmp_pointer;

  int yylex (void);
  void yyerror (char const *);

  void initialize();
  void finalize();
  void printResult();
  void checkIfIdExists(char* id);
  void assignToVariable(char* id);
  /* pidentifierAdding.h*/
  void addVarIdentifier(char* id);
  void addArrayIdentifier(char* id, char* amount);
  /* IO.h */
  void readAndStore(char* id);
  void writeVariable(char* var);
  /* errors.h */
  int getErrorCode(char const *s);
  /* arithmetic.h */
  void putValueToTmp(char* num);
  void addition(char* a, char* b);
  void substraction(char* a, char* b);
  void divide(char* a, char* b);
  void multiply(char* a, char* b);
  void mod(char* a, char* b);
%}

%union{
    long num;
    char* id;
    char* value;
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
%type <value> value
%type <value> num
%type <value> expression

%%

program:
     VAR vdeclarations BEGINZ commands END    { printResult(); return 0;}

vdeclarations:
     vdeclarations pidentifier                  { addVarIdentifier($2); }
     | vdeclarations pidentifier '[' num ']'    { addArrayIdentifier($2, $4); }
     |

commands:
     commands command
     | command

command:
     identifier ASSIGN expression ';'                                 { assignToVariable($1); }
     | IF condition THEN commands ELSE commands ENDIF
     | IF condition THEN commands ENDIF
     | WHILE condition DO commands ENDWHILE
     | FOR pidentifier FROM value TO value DO commands ENDFOR
     | FOR pidentifier FROM value DOWNTO value DO commands ENDFOR
     | READ identifier ';'      { readAndStore($2); }
     | WRITE value ';'          { writeVariable($2); }

expression:
     value                    { putValueToTmp($1); }
     | value '+' value        { addition($1, $3); }
     | value '-' value        { substraction($1, $3); }
     | value '*' value        { multiply($1, $3); }
     | value '/' value        { divide($1, $3); }
     | value '%' value        { mod($1, $3); }

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
     | pidentifier '[' pidentifier ']'    { $$ = concat($1, concat("|", $3));}
     | pidentifier '[' num ']'            { $$ = concat($1, $3);}



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
  program_k = 0;
  ids_count = 0;
  ids_max = 20;
  ids = (char**) malloc(ids_max * sizeof(char*));
  if(debug) printf("Allocating stack for creating number.\n");
  /*stack = (char*) malloc(sizeof(STACK)*100);*/
  if(debug) printf("Stack initialized successfully.\n");
}

void finalize(){
  if(debug) printf("Identifiers: ");
  for(int i=0; i < ids_count; i++){
    if(debug) printf("%s ", ids[i]);
    free(ids[i]);
  }
  if(debug) printf("\n");
  free(ids);
}

void printResult(){
  HALT();
}

/* Called by yyparse on error.  */
void yyerror (char const *s)
{
  fprintf (stderr, "BISON: %s\n", s);
  finalize();
  exit(getErrorCode(s));
  /*main();*/
}
