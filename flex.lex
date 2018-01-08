%option yylineno
%{
	#include<math.h>
	#include<string.h>
  #include "bison.yy.h"

	extern long code_k;

  long flexDebug = 0; // debug
  long bisonDebug = 0; // debug
  long printK = 0; // debug
  void printLex(char* s);
	long pidentifierFound();
	long numFound();
%}

DIGIT						[0-9]
num							{DIGIT}+
pidentifier 		[_a-z]+
ALL_BUT_BRACES	[^\(\)]
comment_re			\({ALL_BUT_BRACES}*\)

%%

[\ \t]*									;
VAR											return VAR;
BEGIN										return BEGINZ;
END											return END;
{pidentifier} 					return pidentifierFound();

{num}										{ return numFound(); }
IF											{ printLex(yytext); return IF;}
THEN										{ printLex(yytext); return THEN; }
ELSE										{ printLex(yytext); return ELSE; }
ENDIF										{ printLex(yytext); return ENDIF; }
WHILE										{ printLex(yytext); return WHILE; }
DO											{ printLex(yytext); return DO; }
ENDWHILE								{ printLex(yytext); return ENDWHILE; }
FOR											{ printLex(yytext); return FOR; }
FROM										{ printLex(yytext); return FROM; }
TO											{ printLex(yytext); return TO; }
DOWNTO									{ printLex(yytext); return DOWNTO; }
ENDFOR									{ printLex(yytext); return ENDFOR; }
READ										{ printLex(yytext); return READ; }
WRITE										{ printLex(yytext); return WRITE; }
"["											{ printLex(yytext); return '['; }
"]"											{ printLex(yytext); return ']'; }
";"											{ printLex(yytext); return ';'; }
":=" 										{ printLex(yytext); return ASSIGN; }
">"											{ printLex(yytext); return '>'; }
"<"											{ printLex(yytext); return '<'; }
"=" 										{ printLex(yytext); return ISEQ; }
"<="										{ printLex(yytext); return LEQ; }
">="										{ printLex(yytext); return GTEQ; }
"<>"										{ printLex(yytext); return UNEQ; }
"+"											{ printLex(yytext); return '+'; }
"-"											{ printLex(yytext); return '-'; }
"*"											{ printLex(yytext); return '*'; }
"/"											{ printLex(yytext); return '/'; }
"%"											{ printLex(yytext); return '%'; }

{comment_re}
\n						{ code_k++; }
[A-Z]*				{ printf("[WARNING] Unknown word found: '%s'. Ignoring.", yytext); }

%%
long pidentifierFound(){
	printLex(yytext);
	yylval.value = strdup(yytext);
	return pidentifier;
}

long numFound() {
	printLex(yytext);
	yylval.value = strdup(yytext);
	return num;
}

void printLex(char* s) {
  if(flexDebug){
    printf("FLEX: '%s'\n", s);
  }
}
