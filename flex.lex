
%{
	#include<math.h>
  #include "bison.yy.h"

  int debug = 0;
  void printLex(char* s);
%}

OPERATOR		[+\-*/%^]
DIGIT			[0-9]

%%

VAR				return VAR;
BEGIN			return BEGINZ;
END				return END;
.*				return ';';
\n				return ';';

%%

void printLex(char* s) {
  if(debug){
    printf("FLEX: %s\n", s);
  }
}
