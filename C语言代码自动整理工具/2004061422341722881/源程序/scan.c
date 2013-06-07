/****************************************************************************
*                     U N R E G I S T E R E D   C O P Y
* 
* You are on day 85 of your 30 day trial period.
* 
* This file was produced by an UNREGISTERED COPY of Parser Generator. It is
* for evaluation purposes only. If you continue to use Parser Generator 30
* days after installation then you are required to purchase a license. For
* more information see the online help or go to the Bumble-Bee Software
* homepage at:
* 
* http://www.bumblebeesoftware.com
* 
* This notice must remain present in the file. It cannot be removed.
****************************************************************************/

/****************************************************************************
* scan.c
* C source file generated from scan.l.
* 
* Date: 06/24/03
* Time: 17:07:53
* 
* ALex Version: 2.05
****************************************************************************/

#include <yylex.h>

/* namespaces */
#if defined(__cplusplus) && defined(YYSTDCPPLIB)
using namespace std;
#endif
#if defined(__cplusplus) && defined(YYNAMESPACE)
using namespace yl;
#endif

#define YYFASTLEXER

#line 6 ".\\scan.l"

#include "globals.h"
#include "util.h"
#include "scan.h"
#include "parse.h"

char tokenString[MAXTOKENLEN+1];

#line 49 "scan.c"
/* repeated because of possible precompiled header */
#include <yylex.h>

/* namespaces */
#if defined(__cplusplus) && defined(YYSTDCPPLIB)
using namespace std;
#endif
#if defined(__cplusplus) && defined(YYNAMESPACE)
using namespace yl;
#endif

#define YYFASTLEXER

#include ".\scan.h"

#ifndef YYTEXT_SIZE
#define YYTEXT_SIZE 100
#endif
#ifndef YYUNPUT_SIZE
#define YYUNPUT_SIZE YYTEXT_SIZE
#endif
#ifndef YYTEXT_MAX
#define YYTEXT_MAX 0
#endif
#ifndef YYUNPUT_MAX
#define YYUNPUT_MAX YYTEXT_MAX
#endif

/* yytext */
static char YYNEAR yysatext[(YYTEXT_SIZE) + 1];		/* extra char for \0 */
char YYFAR *YYNEAR YYDCDECL yystext = yysatext;
char YYFAR *YYNEAR YYDCDECL yytext = yysatext;
int YYNEAR YYDCDECL yystext_size = (YYTEXT_SIZE);
int YYNEAR YYDCDECL yytext_size = (YYTEXT_SIZE);
int YYNEAR YYDCDECL yytext_max = (YYTEXT_MAX);

/* yystatebuf */
#if (YYTEXT_SIZE) != 0
static int YYNEAR yysastatebuf[(YYTEXT_SIZE)];
int YYFAR *YYNEAR YYDCDECL yysstatebuf = yysastatebuf;
int YYFAR *YYNEAR YYDCDECL yystatebuf = yysastatebuf;
#else
int YYFAR *YYNEAR YYDCDECL yysstatebuf = NULL;
int YYFAR *YYNEAR YYDCDECL yystatebuf = NULL;
#endif

/* yyunputbuf */
#if (YYUNPUT_SIZE) != 0
static int YYNEAR yysaunputbuf[(YYUNPUT_SIZE)];
int YYFAR *YYNEAR YYDCDECL yysunputbufptr = yysaunputbuf;
int YYFAR *YYNEAR YYDCDECL yyunputbufptr = yysaunputbuf;
#else
int YYFAR *YYNEAR YYDCDECL yysunputbufptr = NULL;
int YYFAR *YYNEAR YYDCDECL yyunputbufptr = NULL;
#endif
int YYNEAR YYDCDECL yysunput_size = (YYUNPUT_SIZE);
int YYNEAR YYDCDECL yyunput_size = (YYUNPUT_SIZE);
int YYNEAR YYDCDECL yyunput_max = (YYUNPUT_MAX);

/* backwards compatability with lex */
#ifdef input
#ifdef YYPROTOTYPE
int YYCDECL yyinput(void)
#else
int YYCDECL yyinput()
#endif
{
	return input();
}
#else
#define input yyinput
#endif

#ifdef output
#ifdef YYPROTOTYPE
void YYCDECL yyoutput(int ch)
#else
void YYCDECL yyoutput(ch)
int ch;
#endif
{
	output(ch);
}
#else
#define output yyoutput
#endif

#ifdef unput
#ifdef YYPROTOTYPE
void YYCDECL yyunput(int ch)
#else
void YYCDECL yyunput(ch)
int ch;
#endif
{
	unput(ch);
}
#else
#define unput yyunput
#endif

#ifndef YYNBORLANDWARN
#ifdef __BORLANDC__
#pragma warn -rch		/* <warning: unreachable code> off */
#endif
#endif

#ifdef YYPROTOTYPE
int YYCDECL yylexeraction(int action)
#else
int YYCDECL yylexeraction(action)
int action;
#endif
{
	yyreturnflg = YYTRUE;
	switch (action) {
	case 1:
		{
#line 41 ".\\scan.l"
return INT;
#line 170 "scan.c"
		}
		break;
	case 2:
		{
#line 42 ".\\scan.l"
return FLOAT;
#line 177 "scan.c"
		}
		break;
	case 3:
		{
#line 43 ".\\scan.l"
return CHAR;
#line 184 "scan.c"
		}
		break;
	case 4:
		{
#line 44 ".\\scan.l"
return VOID;
#line 191 "scan.c"
		}
		break;
	case 5:
		{
#line 45 ".\\scan.l"
return IF;
#line 198 "scan.c"
		}
		break;
	case 6:
		{
#line 46 ".\\scan.l"
return ELSE;
#line 205 "scan.c"
		}
		break;
	case 7:
		{
#line 47 ".\\scan.l"
return WHILE;
#line 212 "scan.c"
		}
		break;
	case 8:
		{
#line 48 ".\\scan.l"
return CONTINUE;
#line 219 "scan.c"
		}
		break;
	case 9:
		{
#line 49 ".\\scan.l"
return BREAK;
#line 226 "scan.c"
		}
		break;
	case 10:
		{
#line 50 ".\\scan.l"
return RETURN;
#line 233 "scan.c"
		}
		break;
	case 11:
		{
#line 51 ".\\scan.l"
return PLUS;
#line 240 "scan.c"
		}
		break;
	case 12:
		{
#line 52 ".\\scan.l"
return SUB;
#line 247 "scan.c"
		}
		break;
	case 13:
		{
#line 53 ".\\scan.l"
return MUT;
#line 254 "scan.c"
		}
		break;
	case 14:
		{
#line 54 ".\\scan.l"
return DIV;
#line 261 "scan.c"
		}
		break;
	case 15:
		{
#line 55 ".\\scan.l"
return LT;
#line 268 "scan.c"
		}
		break;
	case 16:
		{
#line 56 ".\\scan.l"
return LE;
#line 275 "scan.c"
		}
		break;
	case 17:
		{
#line 57 ".\\scan.l"
return GT;
#line 282 "scan.c"
		}
		break;
	case 18:
		{
#line 58 ".\\scan.l"
return GE;
#line 289 "scan.c"
		}
		break;
	case 19:
		{
#line 59 ".\\scan.l"
return EQ;
#line 296 "scan.c"
		}
		break;
	case 20:
		{
#line 60 ".\\scan.l"
return NEQ;
#line 303 "scan.c"
		}
		break;
	case 21:
		{
#line 61 ".\\scan.l"
return AND;
#line 310 "scan.c"
		}
		break;
	case 22:
		{
#line 62 ".\\scan.l"
return OR;
#line 317 "scan.c"
		}
		break;
	case 23:
		{
#line 63 ".\\scan.l"
return NOT;
#line 324 "scan.c"
		}
		break;
	case 24:
		{
#line 64 ".\\scan.l"
return ASSIGN;
#line 331 "scan.c"
		}
		break;
	case 25:
		{
#line 65 ".\\scan.l"
return SEMI;
#line 338 "scan.c"
		}
		break;
	case 26:
		{
#line 66 ".\\scan.l"
return COMMA;
#line 345 "scan.c"
		}
		break;
	case 27:
		{
#line 67 ".\\scan.l"
return LP;
#line 352 "scan.c"
		}
		break;
	case 28:
		{
#line 68 ".\\scan.l"
return RP;
#line 359 "scan.c"
		}
		break;
	case 29:
		{
#line 69 ".\\scan.l"
return LSP;
#line 366 "scan.c"
		}
		break;
	case 30:
		{
#line 70 ".\\scan.l"
return RSP;
#line 373 "scan.c"
		}
		break;
	case 31:
		{
#line 71 ".\\scan.l"
return LFP;
#line 380 "scan.c"
		}
		break;
	case 32:
		{
#line 72 ".\\scan.l"
return RFP;
#line 387 "scan.c"
		}
		break;
	case 33:
		{
#line 73 ".\\scan.l"
return ID;
#line 394 "scan.c"
		}
		break;
	case 34:
		{
#line 74 ".\\scan.l"
return NUM;
#line 401 "scan.c"
		}
		break;
	case 35:
		{
#line 75 ".\\scan.l"
return FNUM;
#line 408 "scan.c"
		}
		break;
	case 36:
		{
#line 76 ".\\scan.l"
return SCHAR;
#line 415 "scan.c"
		}
		break;
	case 37:
		{
#line 77 ".\\scan.l"
lineno++;
#line 422 "scan.c"
		}
		break;
	case 38:
		{
#line 78 ".\\scan.l"

#line 429 "scan.c"
		}
		break;
	case 39:
		{
#line 79 ".\\scan.l"
 char c;
				  while ((c = yyinput()) != '\n')
				    if (c == EOF) return ENDFILE;
				  yyunput(c);
				
#line 440 "scan.c"
		}
		break;
	case 40:
		{
#line 84 ".\\scan.l"
 char c;
                  int done = FALSE;
                  do {
                    while ((c = yyinput()) != '*')
                      if (c == EOF) return ERROR;
                    while ((c = yyinput()) == '*');
                    if (c == '/') done = TRUE;
                  } while (!done);
                
#line 455 "scan.c"
		}
		break;
	case 41:
		{
#line 93 ".\\scan.l"
return ERROR;
#line 462 "scan.c"
		}
		break;
	default:
		yyassert(0);
		break;
	}
	yyreturnflg = YYFALSE;
	return 0;
}

#ifndef YYNBORLANDWARN
#ifdef __BORLANDC__
#pragma warn .rch		/* <warning: unreachable code> to the old state */
#endif
#endif
YYCONST yymatch_t YYNEARFAR YYBASED_CODE YYDCDECL yymatch[] = {
	0
};

int YYNEAR YYDCDECL yytransitionmax = 218;
YYCONST yytransition_t YYNEARFAR YYBASED_CODE YYDCDECL yytransition[] = {
	{ 0, 0 },
	{ 4, 1 },
	{ 5, 1 },
	{ 4, 4 },
	{ 40, 16 },
	{ 42, 19 },
	{ 16, 16 },
	{ 16, 16 },
	{ 16, 16 },
	{ 16, 16 },
	{ 16, 16 },
	{ 16, 16 },
	{ 16, 16 },
	{ 16, 16 },
	{ 16, 16 },
	{ 16, 16 },
	{ 45, 25 },
	{ 38, 15 },
	{ 43, 20 },
	{ 49, 28 },
	{ 44, 24 },
	{ 0, 8 },
	{ 39, 15 },
	{ 46, 25 },
	{ 4, 1 },
	{ 6, 1 },
	{ 4, 4 },
	{ 50, 28 },
	{ 47, 26 },
	{ 48, 27 },
	{ 7, 1 },
	{ 8, 1 },
	{ 9, 1 },
	{ 10, 1 },
	{ 11, 1 },
	{ 12, 1 },
	{ 13, 1 },
	{ 14, 1 },
	{ 35, 6 },
	{ 15, 1 },
	{ 16, 1 },
	{ 16, 1 },
	{ 16, 1 },
	{ 16, 1 },
	{ 16, 1 },
	{ 16, 1 },
	{ 16, 1 },
	{ 16, 1 },
	{ 16, 1 },
	{ 16, 1 },
	{ 51, 29 },
	{ 17, 1 },
	{ 18, 1 },
	{ 19, 1 },
	{ 20, 1 },
	{ 52, 30 },
	{ 53, 31 },
	{ 21, 1 },
	{ 21, 1 },
	{ 21, 1 },
	{ 21, 1 },
	{ 21, 1 },
	{ 21, 1 },
	{ 21, 1 },
	{ 21, 1 },
	{ 21, 1 },
	{ 21, 1 },
	{ 21, 1 },
	{ 21, 1 },
	{ 21, 1 },
	{ 21, 1 },
	{ 21, 1 },
	{ 21, 1 },
	{ 21, 1 },
	{ 21, 1 },
	{ 21, 1 },
	{ 21, 1 },
	{ 21, 1 },
	{ 21, 1 },
	{ 21, 1 },
	{ 21, 1 },
	{ 21, 1 },
	{ 21, 1 },
	{ 22, 1 },
	{ 54, 33 },
	{ 23, 1 },
	{ 55, 37 },
	{ 21, 1 },
	{ 57, 44 },
	{ 21, 1 },
	{ 24, 1 },
	{ 25, 1 },
	{ 21, 1 },
	{ 26, 1 },
	{ 27, 1 },
	{ 21, 1 },
	{ 21, 1 },
	{ 28, 1 },
	{ 21, 1 },
	{ 21, 1 },
	{ 21, 1 },
	{ 21, 1 },
	{ 21, 1 },
	{ 21, 1 },
	{ 21, 1 },
	{ 21, 1 },
	{ 29, 1 },
	{ 21, 1 },
	{ 21, 1 },
	{ 21, 1 },
	{ 30, 1 },
	{ 31, 1 },
	{ 21, 1 },
	{ 21, 1 },
	{ 21, 1 },
	{ 32, 1 },
	{ 33, 1 },
	{ 34, 1 },
	{ 21, 82 },
	{ 21, 82 },
	{ 21, 82 },
	{ 21, 82 },
	{ 21, 82 },
	{ 21, 82 },
	{ 21, 82 },
	{ 21, 82 },
	{ 21, 82 },
	{ 21, 82 },
	{ 58, 45 },
	{ 59, 46 },
	{ 60, 47 },
	{ 61, 48 },
	{ 62, 50 },
	{ 63, 51 },
	{ 64, 52 },
	{ 21, 82 },
	{ 21, 82 },
	{ 21, 82 },
	{ 21, 82 },
	{ 21, 82 },
	{ 21, 82 },
	{ 21, 82 },
	{ 21, 82 },
	{ 21, 82 },
	{ 21, 82 },
	{ 21, 82 },
	{ 21, 82 },
	{ 21, 82 },
	{ 21, 82 },
	{ 21, 82 },
	{ 21, 82 },
	{ 21, 82 },
	{ 21, 82 },
	{ 21, 82 },
	{ 21, 82 },
	{ 21, 82 },
	{ 21, 82 },
	{ 21, 82 },
	{ 21, 82 },
	{ 21, 82 },
	{ 21, 82 },
	{ 65, 53 },
	{ 36, 7 },
	{ 66, 57 },
	{ 67, 58 },
	{ 21, 82 },
	{ 68, 59 },
	{ 21, 82 },
	{ 21, 82 },
	{ 21, 82 },
	{ 21, 82 },
	{ 21, 82 },
	{ 21, 82 },
	{ 21, 82 },
	{ 21, 82 },
	{ 21, 82 },
	{ 21, 82 },
	{ 21, 82 },
	{ 21, 82 },
	{ 21, 82 },
	{ 21, 82 },
	{ 21, 82 },
	{ 21, 82 },
	{ 21, 82 },
	{ 21, 82 },
	{ 21, 82 },
	{ 21, 82 },
	{ 21, 82 },
	{ 21, 82 },
	{ 21, 82 },
	{ 21, 82 },
	{ 21, 82 },
	{ 21, 82 },
	{ 56, 56 },
	{ 56, 56 },
	{ 56, 56 },
	{ 56, 56 },
	{ 56, 56 },
	{ 56, 56 },
	{ 56, 56 },
	{ 56, 56 },
	{ 56, 56 },
	{ 56, 56 },
	{ 69, 60 },
	{ 70, 61 },
	{ 71, 63 },
	{ 72, 64 },
	{ 73, 65 },
	{ 74, 66 },
	{ 75, 68 },
	{ 76, 70 },
	{ 77, 71 },
	{ 78, 73 },
	{ 79, 75 },
	{ 80, 77 },
	{ 81, 79 },
	{ 82, 81 },
	{ 41, 18 }
};

YYCONST yystate_t YYNEARFAR YYBASED_CODE YYDCDECL yystate[] = {
	{ 0, 0, 0 },
	{ -3, -8, 0 },
	{ 1, 0, 0 },
	{ 0, 0, 41 },
	{ 0, -6, 38 },
	{ 0, 0, 37 },
	{ 0, -23, 23 },
	{ 0, 124, 41 },
	{ -37, 11, 41 },
	{ 0, 0, 27 },
	{ 0, 0, 28 },
	{ 0, 0, 13 },
	{ 0, 0, 11 },
	{ 0, 0, 26 },
	{ 0, 0, 12 },
	{ 0, -25, 14 },
	{ 0, -42, 34 },
	{ 0, 0, 25 },
	{ 0, 156, 15 },
	{ 0, -56, 24 },
	{ 0, -43, 17 },
	{ 82, 0, 33 },
	{ 0, 0, 29 },
	{ 0, 0, 30 },
	{ 82, -94, 33 },
	{ 82, -88, 33 },
	{ 82, -80, 33 },
	{ 82, -79, 33 },
	{ 82, -83, 33 },
	{ 82, -51, 33 },
	{ 82, -56, 33 },
	{ 82, -48, 33 },
	{ 0, 0, 31 },
	{ 0, -40, 41 },
	{ 0, 0, 32 },
	{ 0, 0, 20 },
	{ 0, 0, 21 },
	{ 0, 47, 0 },
	{ 0, 0, 40 },
	{ 0, 0, 39 },
	{ 56, 0, 0 },
	{ 0, 0, 16 },
	{ 0, 0, 19 },
	{ 0, 0, 18 },
	{ 82, -13, 33 },
	{ 82, 31, 33 },
	{ 82, 19, 33 },
	{ 82, 15, 33 },
	{ 82, 20, 33 },
	{ 82, 0, 5 },
	{ 82, 16, 33 },
	{ 82, 17, 33 },
	{ 82, 29, 33 },
	{ 82, 56, 33 },
	{ 0, 0, 22 },
	{ 0, 0, 36 },
	{ 0, 145, 35 },
	{ 82, 66, 33 },
	{ 82, 50, 33 },
	{ 82, 50, 33 },
	{ 82, 102, 33 },
	{ 82, 107, 33 },
	{ 82, 0, 1 },
	{ 82, 88, 33 },
	{ 82, 106, 33 },
	{ 82, 99, 33 },
	{ 82, 101, 33 },
	{ 82, 0, 3 },
	{ 82, 104, 33 },
	{ 82, 0, 6 },
	{ 82, 94, 33 },
	{ 82, 97, 33 },
	{ 82, 0, 4 },
	{ 82, 111, 33 },
	{ 82, 0, 9 },
	{ 82, 103, 33 },
	{ 82, 0, 2 },
	{ 82, 104, 33 },
	{ 82, 0, 7 },
	{ 82, 98, 33 },
	{ 82, 0, 10 },
	{ 82, 115, 33 },
	{ 0, 70, 8 }
};

YYCONST yybackup_t YYNEARFAR YYBASED_CODE YYDCDECL yybackup[] = {
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0
};

#line 96 ".\\scan.l"


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

