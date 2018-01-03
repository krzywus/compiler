
%{
	#include<math.h>
  #include "bison.yy.h"

  int debug = 1;
  void printLex(char* s);
%}

OPERATOR		[+\-*/%]
DIGIT				[0-9]

%%

VAR			{printLex(yytext); return VAR; }
BEGIN			return BEGINZ;
END				return END;
.*				{printLex(yytext); return ';';}
\n

%%

void printLex(char* s) {
  if(debug){
    printf("FLEX: %s\n", s);
  }
}
