
%{
  #include <stdio.h>
  #include <stdlib.h>
  #include <math.h>
  #include <string.h>
  char output_string[100];

  int yylex (void);
  void yyerror (char const *);

  void printResult();
%}

%union{
    long num;
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
%token '[' ']' '>' '<' '=' ';' ':'
%token EOL /* miscellaneous */

%%

program:
     VAR vdeclarations BEGINZ commands END

vdeclarations:
     vdeclarations pidentifier
     | vdeclarations pidentifier '[' num ']'
     |

commands:
     commands command
     | command

command:
     identifier ':' '=' expression ';'
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
     value '=' value
     | value '<' '>' value
     | value '<' value
     | value '>' value
     | value '<' '=' value
     | value '>' '=' value

value:
     num
     | identifier

identifier:
     pidentifier
     | pidentifier '[' pidentifier ']'
     | pidentifier '[' num ']'



%%
int main (void) {
  long result = 0;
  /*while(result == 0) {*/
    strcpy (output_string,"");
	  result = yyparse();
	/*}*/
  return 0;
}

void printResult(){
  printf("%s", output_string);
  printf("HALT\n");
}

/* Called by yyparse on error.  */
void yyerror (char const *s)
{
  fprintf (stderr, "BISON: %s\n", s);
  exit(1);
  /*main();*/
}
