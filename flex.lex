
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
IF											{ BEGIN(IF); return IF;}
THEN										{ return THEN; }
ELSE										{ return ELSE; }
ENDIF										{ BEGIN(0); return ENDIF; }
WHILE										{ BEGIN(WHILE); return WHILE; }
DO											{ return DO; }
ENDWHILE								{ BEGIN(0); return ENDWHILE; }
FOR											{ BEGIN(FOR); return FOR; }
FROM										{ return FROM; }
TO											{ return TO; }
DOWNTO									{ return DOWNTO; }
ENDFOR									{ BEGIN(0); return ENDFOR; }
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
