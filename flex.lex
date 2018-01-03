
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
		lexError("Second VAR section.");
		exit(11);
	}
	current_state = VAR_STATE;
	return VAR;
}

long beginFound(){
	printLex("found begin");
	if(current_state != VAR_STATE){
		lexError("Missing VAR section or second BEGIN section.");
		exit(12);
	}
	current_state = BEGINZ_STATE;
	return BEGINZ;
}

long endFound(){
	printLex("found end");
	if(current_state != BEGINZ_STATE){
		lexError("Program was not started or already finished.");
		exit(13);
	}
	current_state = END_STATE;
	return END;
}

long pidentifierFound(){
	printLex(yytext);
	if(current_state != VAR_STATE){
		lexError("Illegal identifier.");
		exit(14);
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
