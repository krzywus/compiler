
%{
  #include <stdio.h>
  #include <stdlib.h>
  #include <math.h>
  #include <string.h>
  #include <stack>
	#include <vector>
  #include <string>
  #include <iostream>
  #include <sstream>
  #include <map>

  #include "commands.h"
  #include "errors.h"
  #include "pidentifierAdding.h"
  #include "IO.h"
  #include "numberCreation.h"
  #include "assignment.h"
  #include "arithmetic.h"
  #include "conditions.h"
  #include "loops.h"

  using namespace std;

  int current_state = -1;

	vector<string> commands;
  map<string, int> forLoopsVariables;
  vector<string> initializedVariables;

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
  /* conditions.h */
  void condISEQ(string a, string b);
  void condUNEQ(string a, string b);
  void condLESS(string a, string b);
  void condGREATER(string a, string b);
  void condLEQ(string a, string b);
  void condGTEQ(string a, string b);
  void endIf(int modifier);
  void endElse();
  /* loops.h */
  void endWhile();
  void forFromTo(char* id, char* from, char* to);
  void forFromDownTo(char* id, char* from, char* to);
  void endFor();
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
     | IF condition THEN commands ELSE {  endIf(1);
                                          commands.push_back("COND JUMP OVER\n"); program_k++;
                                          commands.push_back("COND BEGIN\n");
                                        }
                                  commands  {  endElse();
                                  } ENDIF
     | IF condition THEN commands ENDIF                                 { endIf(0); }
     | WHILE                                                      { commands.push_back("WHILE START\n");}
       condition DO commands ENDWHILE                             { endWhile(); }
     | FOR pidentifier FROM value TO value DO                     { forFromTo($2, $4, $6);}
       commands ENDFOR                                            { endFor(); }
     | FOR pidentifier FROM value DOWNTO value DO                 { forFromDownTo($2, $4, $6); }
        commands ENDFOR                                           { endFor(); }
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
     value ISEQ value         { condISEQ($1, $3); }
     | value UNEQ value       { condUNEQ($1, $3); }
     | value '<' value        { condLESS($1, $3); }
     | value '>' value        { condGREATER($1, $3); }
     | value LEQ value        { condLEQ($1, $3); }
     | value GTEQ value       { condGTEQ($1, $3); }

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
}

void finalize(){
  if(bisonDebug) printf("Identifiers: ");
  for(int i=0; i < ids_count; i++){
    if(bisonDebug) printf("%s ", ids[i]);
    free(ids[i]);
  }
  if(bisonDebug) printf("\n");
  free(ids);
}

void printResult(){
  HALT();
  for(int i=0; i < commands.size(); i++){
    if(printK) {
      cout << i << " " << commands[i];
    } else {
      cout << commands[i];
    }
  }
}

/* Called by yyparse on error.  */
void yyerror (char const *s)
{
  fprintf (stderr, "BISON: %s\n", s);
  finalize();
  exit(getErrorCode(s));
  /*main();*/
}
