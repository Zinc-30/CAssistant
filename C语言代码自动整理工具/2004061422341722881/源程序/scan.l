/****************************************************************************
scan.l
ParserWizard generated Lex file.

****************************************************************************/
%{
#include "globals.h"
#include "util.h"
#include "scan.h"
#include "parse.h"

char tokenString[MAXTOKENLEN+1];
%}

%include {
    #define MAXTOKENLEN 40

	extern char tokenString[MAXTOKENLEN+1];

	TokenType getToken(void);
}

/////////////////////////////////////////////////////////////////////////////
// declarations section

letter      [_a-zA-Z]
letnum		[_a-zA-Z0-9]
identifier  {letter}{letnum}*
digit       [0-9]
number      {digit}+
fnumber     {number}"."{number}
constchar	'.'
newline		\n
whitespace  [ \t]+

%%

/////////////////////////////////////////////////////////////////////////////
// rules section

"int"           {return INT;}
"float"         {return FLOAT;}
"char"          {return CHAR;}
"void"          {return VOID;}
"if"            {return IF;}
"else"          {return ELSE;}
"while"         {return WHILE;}
"continue"      {return CONTINUE;}
"break"         {return BREAK;}
"return"        {return RETURN;}
"+"             {return PLUS;}
"-"             {return SUB;}
"*"             {return MUT;}
"/"             {return DIV;}
"<"             {return LT;}
"<="            {return LE;}
">"             {return GT;}
">="            {return GE;}
"=="            {return EQ;}
"!="            {return NEQ;}
"&&"            {return AND;}
"||"            {return OR;}
"!"             {return NOT;}
"="             {return ASSIGN;}
";"             {return SEMI;}
","             {return COMMA;}
"("             {return LP;}
")"             {return RP;}
"["             {return LSP;}
"]"             {return RSP;}
"{"             {return LFP;}
"}"             {return RFP;}
{identifier}    {return ID;}
{number}        {return NUM;}
{fnumber}       {return FNUM;}
{constchar}		{return SCHAR;}
{newline}		{lineno++;}
{whitespace}    {}
"//"			{ char c;
				  while ((c = yyinput()) != '\n')
				    if (c == EOF) return ENDFILE;
				  yyunput(c);
				}
"/*"            { char c;
                  int done = FALSE;
                  do {
                    while ((c = yyinput()) != '*')
                      if (c == EOF) return ERROR;
                    while ((c = yyinput()) == '*');
                    if (c == '/') done = TRUE;
                  } while (!done);
                }
.               {return ERROR;}


%%

/////////////////////////////////////////////////////////////////////////////
// programs section

TokenType getToken(void)
{
    static int firstTime = TRUE;
    TokenType currentToken;
    if (firstTime) {
        firstTime = FALSE;
        lineno++;
        yyin = source;
        yyout = listing;
    }
    currentToken = yylex();
    strncpy(tokenString, yytext, MAXTOKENLEN);
    if (TraceScan) {
		lineno = yylineno;
        fprintf(listing,"\t%d: ",lineno);
        printToken(currentToken,tokenString);
    }
    return currentToken;
}
