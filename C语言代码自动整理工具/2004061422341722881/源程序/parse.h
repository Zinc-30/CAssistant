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
* parse.h
* C header file generated from parse.y.
* 
* Date: 06/24/03
* Time: 17:07:53
* 
* AYACC Version: 2.05
****************************************************************************/

#ifndef _PARSE_H
#define _PARSE_H

#include <yypars.h>

#define ENDFILE 257
#define ERROR 258
#define INT 259
#define CHAR 260
#define FLOAT 261
#define IF 262
#define ELSE 263
#define WHILE 264
#define VOID 265
#define RETURN 266
#define BREAK 267
#define CONTINUE 268
#define ID 269
#define NUM 270
#define FNUM 271
#define SCHAR 272
#define PLUS 273
#define SUB 274
#define MUT 275
#define DIV 276
#define LT 277
#define LE 278
#define GT 279
#define GE 280
#define EQ 281
#define NEQ 282
#define AND 283
#define OR 284
#define NOT 285
#define ASSIGN 286
#define SEMI 287
#define COMMA 288
#define LP 289
#define RP 290
#define LSP 291
#define RSP 292
#define LFP 293
#define RFP 294
#ifndef YYSTYPE
union tagYYSTYPE {
#line 23 ".\\parse.y"
 TreeNode * ptree;
         Type type; 
       
#line 77 "parse.h"
};

#define YYSTYPE union tagYYSTYPE
#endif

extern YYSTYPE YYNEAR yylval;

#line 44 ".\\parse.y"

    void yyerror(const char * message);
	TreeNode * parse(void);

#line 90 "parse.h"
#endif
