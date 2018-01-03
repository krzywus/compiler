
%{
	#include<math.h>
	#include<string.h>
  #include "bison.yy.h"


  int debug = 1;
  void printLex(char* s);
  void lexError(char* s);
	long varFound();
	long beginFound();
	long endFound();
	long pidentifierFound();
%}

OPERATOR				[+\-*/%]
DIGIT						[0-9]
pidentifier 		[_a-z]+
ALL_BUT_BRACES	[^\(\)]
comment_re			\({ALL_BUT_BRACES}*\)

%%

[\ \t]*				;
VAR						return varFound();
BEGIN					return beginFound();
END						return endFound();
{pidentifier} return pidentifierFound();
{comment_re}
\n
[A-Z]*				{ lexError("[WARNING] Unknown word found. Ignoring."); lexError(yytext); }

%%
long varFound(){
	printLex("found var");
	if(current_state != -1){
		lexError(VAR_STATE_ERROR);
		exit(VAR_STATE_ERROR_CODE);
	}
	current_state = VAR_STATE;
	return VAR;
}

long beginFound(){
	printLex("found begin");
	if(current_state != VAR_STATE){
		lexError(BEGINZ_STATE_ERROR);
		exit(BEGINZ_STATE_ERROR_CODE);
	}
	current_state = BEGINZ_STATE;
	return BEGINZ;
}

long endFound(){
	printLex("found end");
	if(current_state != BEGINZ_STATE){
		lexError(END_STATE_ERROR);
		exit(END_STATE_ERROR_CODE);
	}
	current_state = END_STATE;
	return END;
}

long pidentifierFound(){
	printLex(yytext);
	if(current_state != VAR_STATE){
		lexError(ILLEGAL_IDENTIFIER);
		exit(ILLEGAL_IDENTIFIER_ERROR_CODE);
	}
	yylval.id = strdup(yytext);
	return pidentifier;
}

void lexError(char* s){
	printf("Lexical error: %s\n", s);
}

void printLex(char* s) {
  if(debug){
    printf("FLEX: '%s'\n", s);
  }
}
