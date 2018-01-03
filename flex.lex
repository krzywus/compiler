
%{
	#include<math.h>
  #include "bison.yy.h"

	#define VAR_STATE 11
	#define BEGINZ_STATE 12
	#define END_STATE 13
	int current_state = -1;

  int debug = 1;
  void printLex(char* s);
  void lexError(char* s);
	long varFound();
	long beginFound();
	long endFound();
%}

OPERATOR		[+\-*/%]
DIGIT				[0-9]

%%

VAR				return varFound();
BEGIN			return beginFound();
END				return endFound();
.*				{printLex(yytext); return ';';}
\n

%%


long varFound(){
	printLex(yytext);
	if(current_state != -1){
		lexError("Second VAR section.");
		exit(11);
	}
	current_state = VAR_STATE;
	return VAR;
}

long beginFound(){
	printLex(yytext);
	if(current_state != 11){
		lexError("Second BEGIN section.");
		exit(12);
	}
	current_state = BEGINZ_STATE;
	return BEGINZ;

}

long endFound(){
	printLex(yytext);
	if(current_state != 12){
		lexError("Program already finished.");
		exit(13);
	}
	current_state = END_STATE;
	return END;
}

void lexError(char* s){
	printf("Lexical error: %s\n", s);
}

void printLex(char* s) {
  if(debug){
    printf("FLEX: %s\n", s);
  }
}
