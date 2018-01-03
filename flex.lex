
%{
	#include<math.h>
	#include<string.h>
  #include "bison.yy.h"
	#include "sectionsKeywords.h"


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
