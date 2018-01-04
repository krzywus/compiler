
%{
	#include<math.h>
	#include<string.h>
  #include "bison.yy.h"
	#include "sectionsKeywords.h"

  int debug = 0;
  void printLex(char* s);
  void lexError(char* s);
	long varFound();
	long beginFound();
	long endFound();
	long pidentifierFound();
%}

DIGIT						[0-9]
num							{DIGIT}+
pidentifier 		[_a-z]+
ALL_BUT_BRACES	[^\(\)]
comment_re			\({ALL_BUT_BRACES}*\)

%%

[\ \t]*									;
VAR											return varFound();
BEGIN										return beginFound();
END											return endFound();
{pidentifier} 					return pidentifierFound();

{num}										{ yylval.id = strdup(yytext); return num; }
IF											{ return IF;}
THEN										{ return THEN; }
ELSE										{ return ELSE; }
ENDIF										{ return ENDIF; }
WHILE										{ return WHILE; }
DO											{ return DO; }
ENDWHILE								{ return ENDWHILE; }
FOR											{ return FOR; }
FROM										{ return FROM; }
TO											{ return TO; }
DOWNTO									{ return DOWNTO; }
ENDFOR									{ return ENDFOR; }
READ										{ return READ; }
WRITE										{ return WRITE; }
"["											{ return '['; }
"]"											{ return ']'; }
";"											{ return ';'; }
":=" 										{ return ASSIGN; }
">"											{ return '>'; }
"<"											{ return '<'; }
"=" 										{ return ISEQ; }
"<="										{ return LEQ; }
">="										{ return GTEQ; }
"<>"										{ return UNEQ; }
"+"											{ return '+'; }
"-"											{ return '-'; }
"*"											{ return '*'; }
"/"											{ return '/'; }
"%"											{ return '%'; }

{comment_re}
\n
[A-Z]*				{ lexError("[WARNING] Unknown word found. Ignoring."); lexError(yytext); }

%%
long pidentifierFound(){
	printLex(yytext);
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
