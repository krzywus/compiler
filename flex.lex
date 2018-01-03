
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

/* Environments */
%s IF
%s WHILE
%s FOR
%s condition
%x array_opened


OPERATOR				[+\-*/%]
DIGIT						[0-9]
num							{DIGIT}+
pidentifier 		[_a-z]+
ALL_BUT_BRACES	[^\(\)]
comment_re			\({ALL_BUT_BRACES}*\)

%%

[\ \t]*				;
VAR						return varFound();
BEGIN					return beginFound();
END						return endFound();
<*>{pidentifier} return pidentifierFound();

<*>num									{ return num; }
IF											{ BEGIN(IF); return IF;}
<IF>THEN								{ return THEN; }
<IF>ELSE								{ return ELSE; }
<IF>ENDIF								{ BEGIN(0); return ENDIF; }
WHILE										{ BEGIN(WHILE); return WHILE; }
<WHILE>DO								{ return DO; }
<WHILE>ENDWHILE					{ BEGIN(0); return ENDWHILE; }
FOR											{ BEGIN(FOR); return FOR; }
<FOR>FROM								{ return FROM; }
<FOR>TO									{ return TO; }
<FOR>DOWNTO							{ return DOWNTO; }
<FOR>ENDFOR							{ BEGIN(0); return ENDFOR; }
READ										{ return READ; }
WRITE										{ return WRITE; }
"["											{ return '['; }
<array_opened>"]"				{ return ']'; }
";"											{ return ';'; }
":=" 										{ return ASSIGN; }
<condition>">"					{ return '>'; }
<condition>"<"					{ return '<'; }
<condition>"=" 					{ return ISEQ; }
<condition>"<="					{ return LEQ; }
<condition>">="					{ return GTEQ; }
<condition>"<>"					{ return UNEQ; }

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
