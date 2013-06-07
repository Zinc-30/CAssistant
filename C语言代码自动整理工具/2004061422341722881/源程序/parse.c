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
* parse.c
* C source file generated from parse.y.
* 
* Date: 06/24/03
* Time: 17:07:53
* 
* AYACC Version: 2.05
****************************************************************************/

#include <yypars.h>

/* namespaces */
#if defined(__cplusplus) && defined(YYSTDCPPLIB)
using namespace std;
#endif
#if defined(__cplusplus) && defined(YYNAMESPACE)
using namespace yl;
#endif

#define YYFASTPARSER

#line 1 ".\\parse.y"

#define YYPARSER /* distinguishes Yacc output from other code files */

#include "globals.h"
#include "util.h"
#include "scan.h"
#include "parse.h"


static char * savedFunName; /* for use in assignments */
static char * savedIdName;
static int savedLineNo;  /* ditto */
static TreeNode * savedTree; /* stores syntax tree for later return */


#line 56 "parse.c"
/* repeated because of possible precompiled header */
#include <yypars.h>

/* namespaces */
#if defined(__cplusplus) && defined(YYSTDCPPLIB)
using namespace std;
#endif
#if defined(__cplusplus) && defined(YYNAMESPACE)
using namespace yl;
#endif

#define YYFASTPARSER

#include ".\parse.h"

#ifndef YYSTYPE
#define YYSTYPE int
#endif
#ifndef YYSTACK_SIZE
#define YYSTACK_SIZE 100
#endif
#ifndef YYSTACK_MAX
#define YYSTACK_MAX 0
#endif

/* (state) stack */
#if (YYSTACK_SIZE) != 0
static yystack_t YYNEAR yystack[(YYSTACK_SIZE)];
yystack_t YYFAR *YYNEAR YYDCDECL yysstackptr = yystack;
yystack_t YYFAR *YYNEAR YYDCDECL yystackptr = yystack;
#else
yystack_t YYFAR *YYNEAR YYDCDECL yysstackptr = NULL;
yystack_t YYFAR *YYNEAR YYDCDECL yystackptr = NULL;
#endif

/* attribute stack */
#if (YYSTACK_SIZE) != 0
static YYSTYPE YYNEAR yyattributestack[(YYSTACK_SIZE)];
#ifdef YYPROTOTYPE
void YYFAR *YYNEAR YYDCDECL yysattributestackptr = yyattributestack;
void YYFAR *YYNEAR YYDCDECL yyattributestackptr = yyattributestack;
#else
char YYFAR *YYNEAR YYDCDECL yysattributestackptr = (char YYFAR *) yyattributestack;
char YYFAR *YYNEAR YYDCDECL yyattributestackptr = (char YYFAR *) yyattributestack;
#endif
#else
#ifdef YYPROTOTYPE
void YYFAR *YYNEAR YYDCDECL yysattributestackptr = NULL;
void YYFAR *YYNEAR YYDCDECL yyattributestackptr = NULL;
#else
char YYFAR *YYNEAR YYDCDECL yysattributestackptr = NULL;
char YYFAR *YYNEAR YYDCDECL yyattributestackptr = NULL;
#endif
#endif

int YYNEAR YYDCDECL yysstack_size = (YYSTACK_SIZE);
int YYNEAR YYDCDECL yystack_size = (YYSTACK_SIZE);
int YYNEAR YYDCDECL yystack_max = (YYSTACK_MAX);

/* attributes */
YYSTYPE YYNEAR yyval;
YYSTYPE YYNEAR yylval;
#ifdef YYPROTOTYPE
void YYFAR *YYNEAR YYDCDECL yyvalptr = &yyval;
void YYFAR *YYNEAR YYDCDECL yylvalptr = &yylval;
#else
char YYFAR *YYNEAR YYDCDECL yyvalptr = (char *) &yyval;
char YYFAR *YYNEAR YYDCDECL yylvalptr = (char *) &yylval;
#endif

size_t YYNEAR YYDCDECL yyattribute_size = sizeof(YYSTYPE);

/* yyattribute */
#ifdef YYDEBUG
#ifdef YYPROTOTYPE
static YYSTYPE YYFAR *yyattribute1(int index)
#else
static YYSTYPE YYFAR *yyattribute1(index)
int index;
#endif
{
	YYSTYPE YYFAR *p = &((YYSTYPE YYFAR *) yyattributestackptr)[yytop + index];
	return p;
}
#define yyattribute(index) (*yyattribute1(index))
#else
#define yyattribute(index) (((YYSTYPE YYFAR *) yyattributestackptr)[yytop + (index)])
#endif

#ifdef YYDEBUG
#ifdef YYPROTOTYPE
static void yyinitdebug(YYSTYPE YYFAR **p, int count)
#else
static void yyinitdebug(p, count)
YYSTYPE YYFAR **p;
int count;
#endif
{
	int i;
	yyassert(p != NULL);
	yyassert(count >= 1);

	for (i = 0; i < count; i++) {
		p[i] = &((YYSTYPE YYFAR *) yyattributestackptr)[yytop + i - (count - 1)];
	}
}
#endif

#ifdef YYPROTOTYPE
void YYCDECL yyparseraction(int action)
#else
void YYCDECL yyparseraction(action)
int action;
#endif
{
	switch (action) {
	case 0:
		{
#ifdef YYDEBUG
			YYSTYPE YYFAR *yya[2];
			yyinitdebug(yya, 2);
#endif
			{
#line 52 ".\\parse.y"
 savedTree = yyattribute(1 - 1).ptree;
#line 182 "parse.c"
			}
		}
		break;
	case 1:
		{
#ifdef YYDEBUG
			YYSTYPE YYFAR *yya[3];
			yyinitdebug(yya, 3);
#endif
			{
#line 55 ".\\parse.y"
 TreeNode * t = yyattribute(1 - 2).ptree;
				  if (t != NULL)
				  { while (t->sibling != NULL)
					t = t->sibling;
					t->sibling = yyattribute(2 - 2).ptree;
					yyval.ptree = yyattribute(1 - 2).ptree; }
				  else yyval.ptree = yyattribute(2 - 2).ptree;
				
#line 202 "parse.c"
			}
		}
		break;
	case 2:
		{
#ifdef YYDEBUG
			YYSTYPE YYFAR *yya[2];
			yyinitdebug(yya, 2);
#endif
			{
#line 64 ".\\parse.y"
 yyval.ptree = yyattribute(1 - 1).ptree; 
#line 215 "parse.c"
			}
		}
		break;
	case 3:
		{
#ifdef YYDEBUG
			YYSTYPE YYFAR *yya[2];
			yyinitdebug(yya, 2);
#endif
			{
#line 66 ".\\parse.y"
 yyval.ptree = yyattribute(1 - 1).ptree; 
#line 228 "parse.c"
			}
		}
		break;
	case 4:
		{
#ifdef YYDEBUG
			YYSTYPE YYFAR *yya[2];
			yyinitdebug(yya, 2);
#endif
			{
#line 67 ".\\parse.y"
 yyval.ptree = yyattribute(1 - 1).ptree; 
#line 241 "parse.c"
			}
		}
		break;
	case 5:
		{
#ifdef YYDEBUG
			YYSTYPE YYFAR *yya[2];
			yyinitdebug(yya, 2);
#endif
			{
#line 68 ".\\parse.y"
 yyval.ptree = yyattribute(1 - 1).ptree; 
#line 254 "parse.c"
			}
		}
		break;
	case 6:
		{
#ifdef YYDEBUG
			YYSTYPE YYFAR *yya[2];
			yyinitdebug(yya, 2);
#endif
			{
#line 70 ".\\parse.y"
 savedIdName = copyString(tokenString); 
#line 267 "parse.c"
			}
		}
		break;
	case 7:
		{
#line 72 ".\\parse.y"
 savedFunName = savedIdName; 
#line 275 "parse.c"
		}
		break;
	case 8:
		{
#ifdef YYDEBUG
			YYSTYPE YYFAR *yya[4];
			yyinitdebug(yya, 4);
#endif
			{
#line 75 ".\\parse.y"
 if(yyattribute(1 - 3).type == Void)
					  ;
					  // err
				  else
				    {	
					  yyval.ptree = newDecNode(VarK); 
					  yyval.ptree -> type = yyattribute(1 - 3).type;
					  yyval.ptree -> child[0] = yyattribute(2 - 3).ptree;
					}
				
#line 296 "parse.c"
			}
		}
		break;
	case 9:
		{
#ifdef YYDEBUG
			YYSTYPE YYFAR *yya[4];
			yyinitdebug(yya, 4);
#endif
			{
#line 87 ".\\parse.y"
 
                  TreeNode * t = yyattribute(1 - 3).ptree;
				  if (t != NULL)
				  { while (t->sibling != NULL)
					t = t->sibling;
					t->sibling = yyattribute(3 - 3).ptree;
					yyval.ptree = yyattribute(1 - 3).ptree; }
				  else yyval.ptree = yyattribute(3 - 3).ptree;
                
#line 317 "parse.c"
			}
		}
		break;
	case 10:
		{
#ifdef YYDEBUG
			YYSTYPE YYFAR *yya[2];
			yyinitdebug(yya, 2);
#endif
			{
#line 96 ".\\parse.y"
 yyval.ptree = yyattribute(1 - 1).ptree; 
#line 330 "parse.c"
			}
		}
		break;
	case 11:
		{
#ifdef YYDEBUG
			YYSTYPE YYFAR *yya[6];
			yyinitdebug(yya, 6);
#endif
			{
#line 98 ".\\parse.y"
 
				  TreeNode * new_node = newStmtNode(AssignK);
				  TreeNode * t = yyattribute(1 - 5).ptree;
				  if (t != NULL)
				  { while (t->sibling != NULL)
					t = t->sibling;
					t->sibling = new_node;
					yyval.ptree = yyattribute(1 - 5).ptree; }
				  else yyval.ptree = new_node;
              
#line 352 "parse.c"
			}
		}
		break;
	case 12:
		{
#ifdef YYDEBUG
			YYSTYPE YYFAR *yya[4];
			yyinitdebug(yya, 4);
#endif
			{
#line 109 ".\\parse.y"
 
				 yyval.ptree = newStmtNode(AssignK);
				 yyval.ptree -> child[0] = newExpNode(IdK);
				 yyval.ptree -> child[0] -> attr.name = savedIdName;
				 yyval.ptree -> child[1] = yyattribute(3 - 3).ptree;
              
#line 370 "parse.c"
			}
		}
		break;
	case 13:
		{
#ifdef YYDEBUG
			YYSTYPE YYFAR *yya[2];
			yyinitdebug(yya, 2);
#endif
			{
#line 116 ".\\parse.y"
 yyval.type = Integer; 
#line 383 "parse.c"
			}
		}
		break;
	case 14:
		{
#ifdef YYDEBUG
			YYSTYPE YYFAR *yya[2];
			yyinitdebug(yya, 2);
#endif
			{
#line 117 ".\\parse.y"
 yyval.type = Float; 
#line 396 "parse.c"
			}
		}
		break;
	case 15:
		{
#ifdef YYDEBUG
			YYSTYPE YYFAR *yya[2];
			yyinitdebug(yya, 2);
#endif
			{
#line 118 ".\\parse.y"
 yyval.type = Char; 
#line 409 "parse.c"
			}
		}
		break;
	case 16:
		{
#ifdef YYDEBUG
			YYSTYPE YYFAR *yya[2];
			yyinitdebug(yya, 2);
#endif
			{
#line 119 ".\\parse.y"
 yyval.type = Void; 
#line 422 "parse.c"
			}
		}
		break;
	case 17:
		{
#ifdef YYDEBUG
			YYSTYPE YYFAR *yya[8];
			yyinitdebug(yya, 8);
#endif
			{
#line 122 ".\\parse.y"
 yyval.ptree = newDecNode(FunDefK);
				  yyval.ptree -> attr.name = savedFunName;
				  yyval.ptree -> type = yyattribute(1 - 7).type;
				  yyval.ptree -> child[0] = yyattribute(5 - 7).ptree;
				  yyval.ptree -> child[1] = yyattribute(7 - 7).ptree; 
				
#line 440 "parse.c"
			}
		}
		break;
	case 18:
		{
#ifdef YYDEBUG
			YYSTYPE YYFAR *yya[7];
			yyinitdebug(yya, 7);
#endif
			{
#line 129 ".\\parse.y"
 yyval.ptree = newDecNode(FunDefK);
				  yyval.ptree -> attr.name = savedFunName;
				  yyval.ptree -> type = Void;
				  yyval.ptree -> child[0] = yyattribute(4 - 6).ptree;
				  yyval.ptree -> child[1] = yyattribute(6 - 6).ptree; 
				
#line 458 "parse.c"
			}
		}
		break;
	case 19:
		{
#ifdef YYDEBUG
			YYSTYPE YYFAR *yya[8];
			yyinitdebug(yya, 8);
#endif
			{
#line 137 ".\\parse.y"
 yyval.ptree = newDecNode(FunDecK);
				  yyval.ptree -> attr.name = savedFunName;
				  yyval.ptree -> type = yyattribute(1 - 7).type;
				  yyval.ptree -> child[0] = yyattribute(5 - 7).ptree;
				  yyval.ptree -> child[1] = NULL;
				
#line 476 "parse.c"
			}
		}
		break;
	case 20:
		{
#ifdef YYDEBUG
			YYSTYPE YYFAR *yya[7];
			yyinitdebug(yya, 7);
#endif
			{
#line 144 ".\\parse.y"
 yyval.ptree = newDecNode(FunDecK);
				  yyval.ptree -> attr.name = savedFunName;
				  yyval.ptree -> type = Void;
				  yyval.ptree -> child[0] = yyattribute(4 - 6).ptree;
				  yyval.ptree -> child[1] = NULL;
				
#line 494 "parse.c"
			}
		}
		break;
	case 21:
		{
#ifdef YYDEBUG
			YYSTYPE YYFAR *yya[2];
			yyinitdebug(yya, 2);
#endif
			{
#line 152 ".\\parse.y"
 yyval.ptree = yyattribute(1 - 1).ptree; 
#line 507 "parse.c"
			}
		}
		break;
	case 22:
		{
#line 154 ".\\parse.y"
 yyval.ptree = NULL; 
#line 515 "parse.c"
		}
		break;
	case 23:
		{
#ifdef YYDEBUG
			YYSTYPE YYFAR *yya[4];
			yyinitdebug(yya, 4);
#endif
			{
#line 157 ".\\parse.y"
 TreeNode * t = yyattribute(1 - 3).ptree;
				  if (t != NULL)
				  { while (t->sibling != NULL)
					t = t->sibling;
					t->sibling = yyattribute(3 - 3).ptree;
					yyval.ptree = yyattribute(1 - 3).ptree; }
				  else yyval.ptree = yyattribute(3 - 3).ptree;
				
#line 534 "parse.c"
			}
		}
		break;
	case 24:
		{
#ifdef YYDEBUG
			YYSTYPE YYFAR *yya[2];
			yyinitdebug(yya, 2);
#endif
			{
#line 166 ".\\parse.y"
 yyval.ptree = yyattribute(1 - 1).ptree; 
#line 547 "parse.c"
			}
		}
		break;
	case 25:
		{
#ifdef YYDEBUG
			YYSTYPE YYFAR *yya[2];
			yyinitdebug(yya, 2);
#endif
			{
#line 169 ".\\parse.y"
 yyval.ptree = newDecNode(ParamK);
                  yyval.ptree -> type = yyattribute(1 - 1).type;
                
#line 562 "parse.c"
			}
		}
		break;
	case 26:
		{
#ifdef YYDEBUG
			YYSTYPE YYFAR *yya[3];
			yyinitdebug(yya, 3);
#endif
			{
#line 173 ".\\parse.y"
 yyval.ptree = newDecNode(ParamK);
                  yyval.ptree -> type = yyattribute(1 - 2).type;
                  yyval.ptree -> attr.name = savedIdName;
                
#line 578 "parse.c"
			}
		}
		break;
	case 27:
		{
#ifdef YYDEBUG
			YYSTYPE YYFAR *yya[5];
			yyinitdebug(yya, 5);
#endif
			{
#line 178 ".\\parse.y"
 yyval.ptree = newDecNode(ParamK);
                  yyval.ptree -> type = yyattribute(1 - 4).type;
                  yyval.ptree -> attr.name = savedIdName;
                
#line 594 "parse.c"
			}
		}
		break;
	case 28:
		{
#ifdef YYDEBUG
			YYSTYPE YYFAR *yya[6];
			yyinitdebug(yya, 6);
#endif
			{
#line 183 ".\\parse.y"
 yyval.ptree = newDecNode(ParamK);
                  yyval.ptree -> type = yyattribute(1 - 5).type;
                  yyval.ptree -> attr.name = savedIdName;
                  yyval.ptree -> child[0] = yyattribute(4 - 5).ptree;
                
#line 611 "parse.c"
			}
		}
		break;
	case 29:
		{
#ifdef YYDEBUG
			YYSTYPE YYFAR *yya[5];
			yyinitdebug(yya, 5);
#endif
			{
#line 190 ".\\parse.y"
 yyval.ptree = newDecNode(CompK);
                  yyval.ptree -> child[0] = yyattribute(2 - 4).ptree;
                  yyval.ptree -> child[1] = yyattribute(3 - 4).ptree;
                
#line 627 "parse.c"
			}
		}
		break;
	case 30:
		{
#ifdef YYDEBUG
			YYSTYPE YYFAR *yya[3];
			yyinitdebug(yya, 3);
#endif
			{
#line 196 ".\\parse.y"
 TreeNode * t = yyattribute(1 - 2).ptree;
				  if (t != NULL)
				  { while (t->sibling != NULL)
					t = t->sibling;
					t->sibling = yyattribute(2 - 2).ptree;
					yyval.ptree = yyattribute(1 - 2).ptree; }
				  else yyval.ptree = yyattribute(2 - 2).ptree;
				
#line 647 "parse.c"
			}
		}
		break;
	case 31:
		{
#line 205 ".\\parse.y"
 yyval.ptree = NULL; 
#line 655 "parse.c"
		}
		break;
	case 32:
		{
#ifdef YYDEBUG
			YYSTYPE YYFAR *yya[3];
			yyinitdebug(yya, 3);
#endif
			{
#line 208 ".\\parse.y"
 TreeNode * t = yyattribute(1 - 2).ptree;
				  if (t != NULL)
				  { while (t->sibling != NULL)
					t = t->sibling;
					t->sibling = yyattribute(2 - 2).ptree;
					yyval.ptree = yyattribute(1 - 2).ptree; }
				  else yyval.ptree = yyattribute(2 - 2).ptree;
				
#line 674 "parse.c"
			}
		}
		break;
	case 33:
		{
#line 217 ".\\parse.y"
 yyval.ptree = NULL; 
#line 682 "parse.c"
		}
		break;
	case 34:
		{
#ifdef YYDEBUG
			YYSTYPE YYFAR *yya[2];
			yyinitdebug(yya, 2);
#endif
			{
#line 219 ".\\parse.y"
 yyval.ptree = yyattribute(1 - 1).ptree; 
#line 694 "parse.c"
			}
		}
		break;
	case 35:
		{
#ifdef YYDEBUG
			YYSTYPE YYFAR *yya[2];
			yyinitdebug(yya, 2);
#endif
			{
#line 220 ".\\parse.y"
 yyval.ptree = yyattribute(1 - 1).ptree; 
#line 707 "parse.c"
			}
		}
		break;
	case 36:
		{
#ifdef YYDEBUG
			YYSTYPE YYFAR *yya[2];
			yyinitdebug(yya, 2);
#endif
			{
#line 221 ".\\parse.y"
 yyval.ptree = yyattribute(1 - 1).ptree; 
#line 720 "parse.c"
			}
		}
		break;
	case 37:
		{
#ifdef YYDEBUG
			YYSTYPE YYFAR *yya[2];
			yyinitdebug(yya, 2);
#endif
			{
#line 222 ".\\parse.y"
 yyval.ptree = yyattribute(1 - 1).ptree; 
#line 733 "parse.c"
			}
		}
		break;
	case 38:
		{
#ifdef YYDEBUG
			YYSTYPE YYFAR *yya[2];
			yyinitdebug(yya, 2);
#endif
			{
#line 223 ".\\parse.y"
 yyval.ptree = yyattribute(1 - 1).ptree; 
#line 746 "parse.c"
			}
		}
		break;
	case 39:
		{
#ifdef YYDEBUG
			YYSTYPE YYFAR *yya[3];
			yyinitdebug(yya, 3);
#endif
			{
#line 224 ".\\parse.y"
 yyval.ptree = newStmtNode(ContinueK); 
#line 759 "parse.c"
			}
		}
		break;
	case 40:
		{
#ifdef YYDEBUG
			YYSTYPE YYFAR *yya[3];
			yyinitdebug(yya, 3);
#endif
			{
#line 225 ".\\parse.y"
 yyval.ptree = newStmtNode(BreakK); 
#line 772 "parse.c"
			}
		}
		break;
	case 41:
		{
#ifdef YYDEBUG
			YYSTYPE YYFAR *yya[3];
			yyinitdebug(yya, 3);
#endif
			{
#line 228 ".\\parse.y"
 yyval.ptree = yyattribute(1 - 2).ptree; 
#line 785 "parse.c"
			}
		}
		break;
	case 42:
		{
#ifdef YYDEBUG
			YYSTYPE YYFAR *yya[2];
			yyinitdebug(yya, 2);
#endif
			{
#line 230 ".\\parse.y"
 yyval.ptree = NULL; 
#line 798 "parse.c"
			}
		}
		break;
	case 43:
		{
#ifdef YYDEBUG
			YYSTYPE YYFAR *yya[6];
			yyinitdebug(yya, 6);
#endif
			{
#line 233 ".\\parse.y"
 yyval.ptree = newStmtNode(IfK);
                  yyval.ptree -> child[0] = yyattribute(3 - 5).ptree;
                  yyval.ptree -> child[1] = yyattribute(5 - 5).ptree;
                
#line 814 "parse.c"
			}
		}
		break;
	case 44:
		{
#ifdef YYDEBUG
			YYSTYPE YYFAR *yya[8];
			yyinitdebug(yya, 8);
#endif
			{
#line 238 ".\\parse.y"
 yyval.ptree = newStmtNode(IfK);
                  yyval.ptree -> child[0] = yyattribute(3 - 7).ptree;
                  yyval.ptree -> child[1] = yyattribute(5 - 7).ptree;
				  yyval.ptree -> child[2] = yyattribute(7 - 7).ptree;
                
#line 831 "parse.c"
			}
		}
		break;
	case 45:
		{
#ifdef YYDEBUG
			YYSTYPE YYFAR *yya[6];
			yyinitdebug(yya, 6);
#endif
			{
#line 245 ".\\parse.y"
 yyval.ptree = newStmtNode(WhileK);
                  yyval.ptree -> child[0] = yyattribute(3 - 5).ptree;
                  yyval.ptree -> child[1] = yyattribute(5 - 5).ptree;
                
#line 847 "parse.c"
			}
		}
		break;
	case 46:
		{
#ifdef YYDEBUG
			YYSTYPE YYFAR *yya[3];
			yyinitdebug(yya, 3);
#endif
			{
#line 251 ".\\parse.y"
 yyval.ptree = newStmtNode(ReturnK);
                  yyval.ptree -> child[0] = NULL;
                
#line 862 "parse.c"
			}
		}
		break;
	case 47:
		{
#ifdef YYDEBUG
			YYSTYPE YYFAR *yya[4];
			yyinitdebug(yya, 4);
#endif
			{
#line 255 ".\\parse.y"
 yyval.ptree = newStmtNode(ReturnK);
                  yyval.ptree -> child[0] = yyattribute(2 - 3).ptree;
                
#line 877 "parse.c"
			}
		}
		break;
	case 48:
		{
#ifdef YYDEBUG
			YYSTYPE YYFAR *yya[4];
			yyinitdebug(yya, 4);
#endif
			{
#line 260 ".\\parse.y"
 yyval.ptree = newStmtNode(AssignK);
                  yyval.ptree -> child[0] = yyattribute(1 - 3).ptree;
                  yyval.ptree -> child[1] = yyattribute(3 - 3).ptree;
                
#line 893 "parse.c"
			}
		}
		break;
	case 49:
		{
#ifdef YYDEBUG
			YYSTYPE YYFAR *yya[2];
			yyinitdebug(yya, 2);
#endif
			{
#line 265 ".\\parse.y"
 yyval.ptree = yyattribute(1 - 1).ptree; 
#line 906 "parse.c"
			}
		}
		break;
	case 50:
		{
#ifdef YYDEBUG
			YYSTYPE YYFAR *yya[2];
			yyinitdebug(yya, 2);
#endif
			{
#line 268 ".\\parse.y"
 yyval.ptree = newExpNode(IdK);
                  yyval.ptree -> attr.name = savedIdName;
                
#line 921 "parse.c"
			}
		}
		break;
	case 51:
		{
#ifdef YYDEBUG
			YYSTYPE YYFAR *yya[5];
			yyinitdebug(yya, 5);
#endif
			{
#line 272 ".\\parse.y"
 yyval.ptree = newExpNode(IdK);
				  yyval.ptree -> attr.name = savedIdName;
                  yyval.ptree -> child[0] = yyattribute(3 - 4).ptree;
                
#line 937 "parse.c"
			}
		}
		break;
	case 52:
		{
#ifdef YYDEBUG
			YYSTYPE YYFAR *yya[4];
			yyinitdebug(yya, 4);
#endif
			{
#line 278 ".\\parse.y"
 yyval.ptree = newExpNode(OpK);
				  yyval.ptree -> child[0] = yyattribute(1 - 3).ptree;
				  yyval.ptree -> child[1] = yyattribute(3 - 3).ptree;
				  yyval.ptree -> attr.op = OR;
				
#line 954 "parse.c"
			}
		}
		break;
	case 53:
		{
#ifdef YYDEBUG
			YYSTYPE YYFAR *yya[4];
			yyinitdebug(yya, 4);
#endif
			{
#line 284 ".\\parse.y"
 yyval.ptree = newExpNode(OpK);
				  yyval.ptree -> child[0] = yyattribute(1 - 3).ptree;
				  yyval.ptree -> child[1] = yyattribute(3 - 3).ptree;
				  yyval.ptree -> attr.op = AND;
				
#line 971 "parse.c"
			}
		}
		break;
	case 54:
		{
#ifdef YYDEBUG
			YYSTYPE YYFAR *yya[4];
			yyinitdebug(yya, 4);
#endif
			{
#line 290 ".\\parse.y"
 yyval.ptree = newExpNode(OpK);
				  yyval.ptree -> child[0] = yyattribute(1 - 3).ptree;
				  yyval.ptree -> child[1] = yyattribute(3 - 3).ptree;
				  yyval.ptree -> attr.op = LT;
				  yyval.ptree -> type = Boolean;
				
#line 989 "parse.c"
			}
		}
		break;
	case 55:
		{
#ifdef YYDEBUG
			YYSTYPE YYFAR *yya[4];
			yyinitdebug(yya, 4);
#endif
			{
#line 297 ".\\parse.y"
 yyval.ptree = newExpNode(OpK);
				  yyval.ptree -> child[0] = yyattribute(1 - 3).ptree;
				  yyval.ptree -> child[1] = yyattribute(3 - 3).ptree;
				  yyval.ptree -> attr.op = LE;
				  yyval.ptree -> type = Boolean;
				
#line 1007 "parse.c"
			}
		}
		break;
	case 56:
		{
#ifdef YYDEBUG
			YYSTYPE YYFAR *yya[4];
			yyinitdebug(yya, 4);
#endif
			{
#line 304 ".\\parse.y"
 yyval.ptree = newExpNode(OpK);
				  yyval.ptree -> child[0] = yyattribute(1 - 3).ptree;
				  yyval.ptree -> child[1] = yyattribute(3 - 3).ptree;
				  yyval.ptree -> attr.op = GT;
				  yyval.ptree -> type = Boolean;
				
#line 1025 "parse.c"
			}
		}
		break;
	case 57:
		{
#ifdef YYDEBUG
			YYSTYPE YYFAR *yya[4];
			yyinitdebug(yya, 4);
#endif
			{
#line 311 ".\\parse.y"
 yyval.ptree = newExpNode(OpK);
				  yyval.ptree -> child[0] = yyattribute(1 - 3).ptree;
				  yyval.ptree -> child[1] = yyattribute(3 - 3).ptree;
				  yyval.ptree -> attr.op = GE;
				  yyval.ptree -> type = Boolean;
				
#line 1043 "parse.c"
			}
		}
		break;
	case 58:
		{
#ifdef YYDEBUG
			YYSTYPE YYFAR *yya[4];
			yyinitdebug(yya, 4);
#endif
			{
#line 318 ".\\parse.y"
 yyval.ptree = newExpNode(OpK);
				  yyval.ptree -> child[0] = yyattribute(1 - 3).ptree;
				  yyval.ptree -> child[1] = yyattribute(3 - 3).ptree;
				  yyval.ptree -> attr.op = EQ;
				  yyval.ptree -> type = Boolean;
				
#line 1061 "parse.c"
			}
		}
		break;
	case 59:
		{
#ifdef YYDEBUG
			YYSTYPE YYFAR *yya[4];
			yyinitdebug(yya, 4);
#endif
			{
#line 325 ".\\parse.y"
 yyval.ptree = newExpNode(OpK);
				  yyval.ptree -> child[0] = yyattribute(1 - 3).ptree;
				  yyval.ptree -> child[1] = yyattribute(3 - 3).ptree;
				  yyval.ptree -> attr.op = NEQ;
				  yyval.ptree -> type = Boolean;
				
#line 1079 "parse.c"
			}
		}
		break;
	case 60:
		{
#ifdef YYDEBUG
			YYSTYPE YYFAR *yya[4];
			yyinitdebug(yya, 4);
#endif
			{
#line 332 ".\\parse.y"
 yyval.ptree = newExpNode(OpK);
				  yyval.ptree -> child[0] = yyattribute(1 - 3).ptree;
				  yyval.ptree -> child[1] = yyattribute(3 - 3).ptree;
				  yyval.ptree -> attr.op = PLUS;
				
#line 1096 "parse.c"
			}
		}
		break;
	case 61:
		{
#ifdef YYDEBUG
			YYSTYPE YYFAR *yya[4];
			yyinitdebug(yya, 4);
#endif
			{
#line 338 ".\\parse.y"
 yyval.ptree = newExpNode(OpK);
				  yyval.ptree -> child[0] = yyattribute(1 - 3).ptree;
				  yyval.ptree -> child[1] = yyattribute(3 - 3).ptree;
				  yyval.ptree -> attr.op = SUB;
				
#line 1113 "parse.c"
			}
		}
		break;
	case 62:
		{
#ifdef YYDEBUG
			YYSTYPE YYFAR *yya[4];
			yyinitdebug(yya, 4);
#endif
			{
#line 344 ".\\parse.y"
 yyval.ptree = newExpNode(OpK);
				  yyval.ptree -> child[0] = yyattribute(1 - 3).ptree;
				  yyval.ptree -> child[1] = yyattribute(3 - 3).ptree;
				  yyval.ptree -> attr.op = MUT;
				
#line 1130 "parse.c"
			}
		}
		break;
	case 63:
		{
#ifdef YYDEBUG
			YYSTYPE YYFAR *yya[4];
			yyinitdebug(yya, 4);
#endif
			{
#line 350 ".\\parse.y"
 yyval.ptree = newExpNode(OpK);
				  yyval.ptree -> child[0] = yyattribute(1 - 3).ptree;
				  yyval.ptree -> child[1] = yyattribute(3 - 3).ptree;
				  yyval.ptree -> attr.op = DIV;
				
#line 1147 "parse.c"
			}
		}
		break;
	case 64:
		{
#ifdef YYDEBUG
			YYSTYPE YYFAR *yya[2];
			yyinitdebug(yya, 2);
#endif
			{
#line 356 ".\\parse.y"
 yyval.ptree = yyattribute(1 - 1).ptree; 
#line 1160 "parse.c"
			}
		}
		break;
	case 65:
		{
#ifdef YYDEBUG
			YYSTYPE YYFAR *yya[4];
			yyinitdebug(yya, 4);
#endif
			{
#line 360 ".\\parse.y"
 yyval.ptree = yyattribute(2 - 3).ptree; 
#line 1173 "parse.c"
			}
		}
		break;
	case 66:
		{
#ifdef YYDEBUG
			YYSTYPE YYFAR *yya[2];
			yyinitdebug(yya, 2);
#endif
			{
#line 362 ".\\parse.y"
 yyval.ptree = yyattribute(1 - 1).ptree; 
#line 1186 "parse.c"
			}
		}
		break;
	case 67:
		{
#ifdef YYDEBUG
			YYSTYPE YYFAR *yya[2];
			yyinitdebug(yya, 2);
#endif
			{
#line 364 ".\\parse.y"
 yyval.ptree = yyattribute(1 - 1).ptree; 
#line 1199 "parse.c"
			}
		}
		break;
	case 68:
		{
#ifdef YYDEBUG
			YYSTYPE YYFAR *yya[2];
			yyinitdebug(yya, 2);
#endif
			{
#line 366 ".\\parse.y"
 yyval.ptree = newExpNode(NumK);
			      yyval.ptree -> type = Integer;
			      yyval.ptree -> attr.val.i = atoi(tokenString);
			    
#line 1215 "parse.c"
			}
		}
		break;
	case 69:
		{
#ifdef YYDEBUG
			YYSTYPE YYFAR *yya[2];
			yyinitdebug(yya, 2);
#endif
			{
#line 371 ".\\parse.y"
 yyval.ptree = newExpNode(FnumK);
			      yyval.ptree -> type = Float;
			      yyval.ptree -> attr.val.f = atof(tokenString);
			    
#line 1231 "parse.c"
			}
		}
		break;
	case 70:
		{
#ifdef YYDEBUG
			YYSTYPE YYFAR *yya[2];
			yyinitdebug(yya, 2);
#endif
			{
#line 376 ".\\parse.y"
 yyval.ptree = newExpNode(CharK);
			      yyval.ptree -> type = Char;
			      yyval.ptree -> attr.val.i = *(tokenString + 1);
			    
#line 1247 "parse.c"
			}
		}
		break;
	case 71:
		{
#ifdef YYDEBUG
			YYSTYPE YYFAR *yya[3];
			yyinitdebug(yya, 3);
#endif
			{
#line 381 ".\\parse.y"
 yyval.ptree = yyattribute(2 - 2).ptree;
			      yyval.ptree -> attr.op = NOT;
			    
#line 1262 "parse.c"
			}
		}
		break;
	case 72:
		{
#ifdef YYDEBUG
			YYSTYPE YYFAR *yya[5];
			yyinitdebug(yya, 5);
#endif
			{
#line 386 ".\\parse.y"
 yyval.ptree = newStmtNode(CallK);
				  yyval.ptree -> attr.name = yyattribute(1 - 4).ptree -> attr.name;
                  yyval.ptree -> child[0] = yyattribute(3 - 4).ptree;
                
#line 1278 "parse.c"
			}
		}
		break;
	case 73:
		{
#ifdef YYDEBUG
			YYSTYPE YYFAR *yya[4];
			yyinitdebug(yya, 4);
#endif
			{
#line 392 ".\\parse.y"
 TreeNode * t = yyattribute(1 - 3).ptree;
				  if (t != NULL)
				  { while (t->sibling != NULL)
					t = t->sibling;
					t->sibling = yyattribute(3 - 3).ptree;
					yyval.ptree = yyattribute(1 - 3).ptree; }
				  else yyval.ptree = yyattribute(3 - 3).ptree;
				
#line 1298 "parse.c"
			}
		}
		break;
	case 74:
		{
#ifdef YYDEBUG
			YYSTYPE YYFAR *yya[2];
			yyinitdebug(yya, 2);
#endif
			{
#line 401 ".\\parse.y"
 yyval.ptree = yyattribute(1 - 1).ptree; 
#line 1311 "parse.c"
			}
		}
		break;
	case 75:
		{
#ifdef YYDEBUG
			YYSTYPE YYFAR *yya[2];
			yyinitdebug(yya, 2);
#endif
			{
#line 404 ".\\parse.y"
 yyval.ptree = yyattribute(1 - 1).ptree; 
#line 1324 "parse.c"
			}
		}
		break;
	case 76:
		{
#line 406 ".\\parse.y"
 yyval.ptree = NULL; 
#line 1332 "parse.c"
		}
		break;
	default:
		yyassert(0);
		break;
	}
}
#ifdef YYDEBUG
YYCONST yysymbol_t YYNEARFAR YYBASED_CODE YYDCDECL yysymbol[] = {
	{ "$end", 0 },
	{ "error", 256 },
	{ "INT", 259 },
	{ "CHAR", 260 },
	{ "FLOAT", 261 },
	{ "IF", 262 },
	{ "ELSE", 263 },
	{ "WHILE", 264 },
	{ "VOID", 265 },
	{ "RETURN", 266 },
	{ "BREAK", 267 },
	{ "CONTINUE", 268 },
	{ "ID", 269 },
	{ "NUM", 270 },
	{ "FNUM", 271 },
	{ "SCHAR", 272 },
	{ "PLUS", 273 },
	{ "SUB", 274 },
	{ "MUT", 275 },
	{ "DIV", 276 },
	{ "LT", 277 },
	{ "LE", 278 },
	{ "GT", 279 },
	{ "GE", 280 },
	{ "EQ", 281 },
	{ "NEQ", 282 },
	{ "AND", 283 },
	{ "OR", 284 },
	{ "NOT", 285 },
	{ "ASSIGN", 286 },
	{ "SEMI", 287 },
	{ "COMMA", 288 },
	{ "LP", 289 },
	{ "RP", 290 },
	{ "LSP", 291 },
	{ "RSP", 292 },
	{ "LFP", 293 },
	{ "RFP", 294 },
	{ NULL, 0 }
};

YYCONST char *YYCONST YYNEARFAR YYBASED_CODE YYDCDECL yyrule[] = {
	"$accept: program",
	"program: dec_list",
	"dec_list: dec_list dec",
	"dec_list: dec",
	"dec: var_dec",
	"dec: fun_dec",
	"dec: fun_def",
	"id: ID",
	"fid:",
	"var_dec: type_spec id_list SEMI",
	"id_list: id_list COMMA var",
	"id_list: var",
	"id_list: id_list COMMA id ASSIGN simple_exp",
	"id_list: id ASSIGN simple_exp",
	"type_spec: INT",
	"type_spec: FLOAT",
	"type_spec: CHAR",
	"type_spec: VOID",
	"fun_def: type_spec id fid LP params RP comp_stmt",
	"fun_def: id fid LP params RP comp_stmt",
	"fun_dec: type_spec id fid LP params RP SEMI",
	"fun_dec: id fid LP params RP SEMI",
	"params: param_list",
	"params:",
	"param_list: param_list COMMA param",
	"param_list: param",
	"param: type_spec",
	"param: type_spec id",
	"param: type_spec id LSP RSP",
	"param: type_spec id LSP simple_exp RSP",
	"comp_stmt: LFP local_dec stmt_list RFP",
	"local_dec: local_dec var_dec",
	"local_dec:",
	"stmt_list: stmt_list stmt",
	"stmt_list:",
	"stmt: exp_stmt",
	"stmt: sele_stmt",
	"stmt: iter_stmt",
	"stmt: return_stmt",
	"stmt: comp_stmt",
	"stmt: CONTINUE SEMI",
	"stmt: BREAK SEMI",
	"exp_stmt: exp SEMI",
	"exp_stmt: SEMI",
	"sele_stmt: IF LP exp RP stmt",
	"sele_stmt: IF LP exp RP stmt ELSE stmt",
	"iter_stmt: WHILE LP exp RP stmt",
	"return_stmt: RETURN SEMI",
	"return_stmt: RETURN exp SEMI",
	"exp: var ASSIGN exp",
	"exp: simple_exp",
	"var: id",
	"var: id LSP simple_exp RSP",
	"simple_exp: simple_exp OR simple_exp",
	"simple_exp: simple_exp AND simple_exp",
	"simple_exp: simple_exp LT simple_exp",
	"simple_exp: simple_exp LE simple_exp",
	"simple_exp: simple_exp GT simple_exp",
	"simple_exp: simple_exp GE simple_exp",
	"simple_exp: simple_exp EQ simple_exp",
	"simple_exp: simple_exp NEQ simple_exp",
	"simple_exp: simple_exp PLUS simple_exp",
	"simple_exp: simple_exp SUB simple_exp",
	"simple_exp: simple_exp MUT simple_exp",
	"simple_exp: simple_exp DIV simple_exp",
	"simple_exp: factor",
	"factor: LP exp RP",
	"factor: var",
	"factor: call",
	"factor: NUM",
	"factor: FNUM",
	"factor: SCHAR",
	"factor: NOT factor",
	"call: var LP args RP",
	"arg_list: arg_list COMMA exp",
	"arg_list: exp",
	"args: arg_list",
	"args:"
};
#endif

YYCONST yyreduction_t YYNEARFAR YYBASED_CODE YYDCDECL yyreduction[] = {
	{ 0, 1, -1 },
	{ 1, 1, 0 },
	{ 2, 2, 1 },
	{ 2, 1, 2 },
	{ 3, 1, 3 },
	{ 3, 1, 4 },
	{ 3, 1, 5 },
	{ 4, 1, 6 },
	{ 5, 0, 7 },
	{ 6, 3, 8 },
	{ 7, 3, 9 },
	{ 7, 1, 10 },
	{ 7, 5, 11 },
	{ 7, 3, 12 },
	{ 8, 1, 13 },
	{ 8, 1, 14 },
	{ 8, 1, 15 },
	{ 8, 1, 16 },
	{ 9, 7, 17 },
	{ 9, 6, 18 },
	{ 10, 7, 19 },
	{ 10, 6, 20 },
	{ 11, 1, 21 },
	{ 11, 0, 22 },
	{ 12, 3, 23 },
	{ 12, 1, 24 },
	{ 13, 1, 25 },
	{ 13, 2, 26 },
	{ 13, 4, 27 },
	{ 13, 5, 28 },
	{ 14, 4, 29 },
	{ 15, 2, 30 },
	{ 15, 0, 31 },
	{ 16, 2, 32 },
	{ 16, 0, 33 },
	{ 17, 1, 34 },
	{ 17, 1, 35 },
	{ 17, 1, 36 },
	{ 17, 1, 37 },
	{ 17, 1, 38 },
	{ 17, 2, 39 },
	{ 17, 2, 40 },
	{ 18, 2, 41 },
	{ 18, 1, 42 },
	{ 19, 5, 43 },
	{ 19, 7, 44 },
	{ 20, 5, 45 },
	{ 21, 2, 46 },
	{ 21, 3, 47 },
	{ 22, 3, 48 },
	{ 22, 1, 49 },
	{ 23, 1, 50 },
	{ 23, 4, 51 },
	{ 24, 3, 52 },
	{ 24, 3, 53 },
	{ 24, 3, 54 },
	{ 24, 3, 55 },
	{ 24, 3, 56 },
	{ 24, 3, 57 },
	{ 24, 3, 58 },
	{ 24, 3, 59 },
	{ 24, 3, 60 },
	{ 24, 3, 61 },
	{ 24, 3, 62 },
	{ 24, 3, 63 },
	{ 24, 1, 64 },
	{ 25, 3, 65 },
	{ 25, 1, 66 },
	{ 25, 1, 67 },
	{ 25, 1, 68 },
	{ 25, 1, 69 },
	{ 25, 1, 70 },
	{ 25, 2, 71 },
	{ 26, 4, 72 },
	{ 27, 3, 73 },
	{ 27, 1, 74 },
	{ 28, 1, 75 },
	{ 28, 0, 76 }
};

int YYNEAR YYDCDECL yytokenaction_size = 187;
YYCONST yytokenaction_t YYNEARFAR YYBASED_CODE YYDCDECL yytokenaction[] = {
	{ 97, YYAT_SHIFT, 49 },
	{ 97, YYAT_SHIFT, 50 },
	{ 97, YYAT_SHIFT, 51 },
	{ 97, YYAT_SHIFT, 52 },
	{ 97, YYAT_SHIFT, 53 },
	{ 97, YYAT_SHIFT, 54 },
	{ 97, YYAT_SHIFT, 55 },
	{ 97, YYAT_SHIFT, 56 },
	{ 97, YYAT_SHIFT, 57 },
	{ 97, YYAT_SHIFT, 58 },
	{ 97, YYAT_SHIFT, 59 },
	{ 97, YYAT_SHIFT, 60 },
	{ 95, YYAT_SHIFT, 1 },
	{ 95, YYAT_SHIFT, 2 },
	{ 95, YYAT_SHIFT, 3 },
	{ 73, YYAT_SHIFT, 51 },
	{ 73, YYAT_SHIFT, 52 },
	{ 130, YYAT_SHIFT, 132 },
	{ 95, YYAT_SHIFT, 4 },
	{ 97, YYAT_SHIFT, 102 },
	{ 66, YYAT_SHIFT, 49 },
	{ 66, YYAT_SHIFT, 50 },
	{ 66, YYAT_SHIFT, 51 },
	{ 66, YYAT_SHIFT, 52 },
	{ 66, YYAT_SHIFT, 53 },
	{ 66, YYAT_SHIFT, 54 },
	{ 66, YYAT_SHIFT, 55 },
	{ 66, YYAT_SHIFT, 56 },
	{ 66, YYAT_SHIFT, 57 },
	{ 66, YYAT_SHIFT, 58 },
	{ 66, YYAT_SHIFT, 59 },
	{ 66, YYAT_SHIFT, 60 },
	{ 47, YYAT_SHIFT, 49 },
	{ 47, YYAT_SHIFT, 50 },
	{ 47, YYAT_SHIFT, 51 },
	{ 47, YYAT_SHIFT, 52 },
	{ 47, YYAT_SHIFT, 53 },
	{ 47, YYAT_SHIFT, 54 },
	{ 47, YYAT_SHIFT, 55 },
	{ 47, YYAT_SHIFT, 56 },
	{ 47, YYAT_SHIFT, 57 },
	{ 47, YYAT_SHIFT, 58 },
	{ 47, YYAT_SHIFT, 59 },
	{ 47, YYAT_SHIFT, 60 },
	{ 33, YYAT_SHIFT, 49 },
	{ 33, YYAT_SHIFT, 50 },
	{ 33, YYAT_SHIFT, 51 },
	{ 33, YYAT_SHIFT, 52 },
	{ 33, YYAT_SHIFT, 53 },
	{ 33, YYAT_SHIFT, 54 },
	{ 33, YYAT_SHIFT, 55 },
	{ 33, YYAT_SHIFT, 56 },
	{ 33, YYAT_SHIFT, 57 },
	{ 33, YYAT_SHIFT, 58 },
	{ 33, YYAT_SHIFT, 59 },
	{ 33, YYAT_SHIFT, 60 },
	{ 83, YYAT_SHIFT, 49 },
	{ 83, YYAT_SHIFT, 50 },
	{ 83, YYAT_SHIFT, 51 },
	{ 83, YYAT_SHIFT, 52 },
	{ 83, YYAT_SHIFT, 53 },
	{ 83, YYAT_SHIFT, 54 },
	{ 83, YYAT_SHIFT, 55 },
	{ 83, YYAT_SHIFT, 56 },
	{ 83, YYAT_SHIFT, 57 },
	{ 83, YYAT_SHIFT, 58 },
	{ 83, YYAT_SHIFT, 59 },
	{ 82, YYAT_SHIFT, 49 },
	{ 82, YYAT_SHIFT, 50 },
	{ 82, YYAT_SHIFT, 51 },
	{ 82, YYAT_SHIFT, 52 },
	{ 82, YYAT_SHIFT, 53 },
	{ 82, YYAT_SHIFT, 54 },
	{ 82, YYAT_SHIFT, 55 },
	{ 82, YYAT_SHIFT, 56 },
	{ 82, YYAT_SHIFT, 57 },
	{ 82, YYAT_SHIFT, 58 },
	{ 132, YYAT_SHIFT, 103 },
	{ 126, YYAT_SHIFT, 129 },
	{ 132, YYAT_SHIFT, 104 },
	{ 125, YYAT_SHIFT, 128 },
	{ 132, YYAT_SHIFT, 105 },
	{ 132, YYAT_SHIFT, 106 },
	{ 132, YYAT_SHIFT, 107 },
	{ 81, YYAT_SHIFT, 49 },
	{ 81, YYAT_SHIFT, 50 },
	{ 81, YYAT_SHIFT, 51 },
	{ 81, YYAT_SHIFT, 52 },
	{ 81, YYAT_SHIFT, 53 },
	{ 81, YYAT_SHIFT, 54 },
	{ 81, YYAT_SHIFT, 55 },
	{ 81, YYAT_SHIFT, 56 },
	{ 80, YYAT_SHIFT, 49 },
	{ 80, YYAT_SHIFT, 50 },
	{ 80, YYAT_SHIFT, 51 },
	{ 80, YYAT_SHIFT, 52 },
	{ 80, YYAT_SHIFT, 53 },
	{ 80, YYAT_SHIFT, 54 },
	{ 80, YYAT_SHIFT, 55 },
	{ 80, YYAT_SHIFT, 56 },
	{ 121, YYAT_SHIFT, 127 },
	{ 84, YYAT_SHIFT, 93 },
	{ 132, YYAT_SHIFT, 108 },
	{ 48, YYAT_SHIFT, 5 },
	{ 48, YYAT_SHIFT, 27 },
	{ 48, YYAT_SHIFT, 28 },
	{ 48, YYAT_SHIFT, 29 },
	{ 84, YYAT_SHIFT, 86 },
	{ 132, YYAT_SHIFT, 86 },
	{ 119, YYAT_SHIFT, 27 },
	{ 119, YYAT_SHIFT, 28 },
	{ 119, YYAT_SHIFT, 29 },
	{ 7, YYAT_SHIFT, 1 },
	{ 7, YYAT_SHIFT, 2 },
	{ 7, YYAT_SHIFT, 3 },
	{ 64, YYAT_SHIFT, 1 },
	{ 64, YYAT_SHIFT, 2 },
	{ 64, YYAT_SHIFT, 3 },
	{ 7, YYAT_SHIFT, 4 },
	{ 48, YYAT_SHIFT, 30 },
	{ 116, YYAT_SHIFT, 124 },
	{ 64, YYAT_SHIFT, 4 },
	{ 7, YYAT_SHIFT, 5 },
	{ 48, YYAT_SHIFT, 31 },
	{ 119, YYAT_SHIFT, 30 },
	{ 38, YYAT_SHIFT, 1 },
	{ 38, YYAT_SHIFT, 2 },
	{ 38, YYAT_SHIFT, 3 },
	{ 119, YYAT_SHIFT, 31 },
	{ 107, YYAT_SHIFT, 123 },
	{ 117, YYAT_SHIFT, 21 },
	{ 38, YYAT_SHIFT, 4 },
	{ 24, YYAT_SHIFT, 1 },
	{ 24, YYAT_SHIFT, 2 },
	{ 24, YYAT_SHIFT, 3 },
	{ 117, YYAT_SHIFT, 22 },
	{ 72, YYAT_SHIFT, 51 },
	{ 72, YYAT_SHIFT, 52 },
	{ 24, YYAT_SHIFT, 4 },
	{ 79, YYAT_SHIFT, 49 },
	{ 79, YYAT_SHIFT, 50 },
	{ 79, YYAT_SHIFT, 51 },
	{ 79, YYAT_SHIFT, 52 },
	{ 78, YYAT_SHIFT, 49 },
	{ 78, YYAT_SHIFT, 50 },
	{ 78, YYAT_SHIFT, 51 },
	{ 78, YYAT_SHIFT, 52 },
	{ 77, YYAT_SHIFT, 49 },
	{ 77, YYAT_SHIFT, 50 },
	{ 77, YYAT_SHIFT, 51 },
	{ 77, YYAT_SHIFT, 52 },
	{ 76, YYAT_SHIFT, 49 },
	{ 76, YYAT_SHIFT, 50 },
	{ 76, YYAT_SHIFT, 51 },
	{ 76, YYAT_SHIFT, 52 },
	{ 17, YYAT_SHIFT, 21 },
	{ 26, YYAT_SHIFT, 43 },
	{ 106, YYAT_SHIFT, 122 },
	{ 17, YYAT_REDUCE, 8 },
	{ 46, YYAT_SHIFT, 68 },
	{ 17, YYAT_SHIFT, 22 },
	{ 26, YYAT_SHIFT, 22 },
	{ 46, YYAT_SHIFT, 48 },
	{ 16, YYAT_SHIFT, 19 },
	{ 16, YYAT_SHIFT, 20 },
	{ 105, YYAT_SHIFT, 120 },
	{ 104, YYAT_SHIFT, 119 },
	{ 103, YYAT_SHIFT, 118 },
	{ 101, YYAT_SHIFT, 5 },
	{ 100, YYAT_SHIFT, 109 },
	{ 89, YYAT_SHIFT, 96 },
	{ 71, YYAT_SHIFT, 92 },
	{ 70, YYAT_SHIFT, 91 },
	{ 65, YYAT_SHIFT, 89 },
	{ 63, YYAT_SHIFT, 85 },
	{ 62, YYAT_SHIFT, 84 },
	{ 45, YYAT_SHIFT, 67 },
	{ 42, YYAT_SHIFT, 5 },
	{ 40, YYAT_SHIFT, 64 },
	{ 39, YYAT_SHIFT, 63 },
	{ 37, YYAT_SHIFT, 61 },
	{ 36, YYAT_SHIFT, 22 },
	{ 32, YYAT_SHIFT, 48 },
	{ 23, YYAT_SHIFT, 38 },
	{ 18, YYAT_SHIFT, 24 },
	{ 6, YYAT_ACCEPT, 0 },
	{ 0, YYAT_SHIFT, 5 }
};

YYCONST yystateaction_t YYNEARFAR YYBASED_CODE YYDCDECL yystateaction[] = {
	{ -83, 1, YYAT_DEFAULT, 64 },
	{ 0, 0, YYAT_REDUCE, 14 },
	{ 0, 0, YYAT_REDUCE, 16 },
	{ 0, 0, YYAT_REDUCE, 15 },
	{ 0, 0, YYAT_REDUCE, 17 },
	{ 0, 0, YYAT_REDUCE, 7 },
	{ 185, 1, YYAT_ERROR, 0 },
	{ -147, 1, YYAT_REDUCE, 1 },
	{ 0, 0, YYAT_REDUCE, 3 },
	{ 0, 0, YYAT_REDUCE, 4 },
	{ 0, 0, YYAT_REDUCE, 5 },
	{ 0, 0, YYAT_REDUCE, 6 },
	{ 0, 0, YYAT_DEFAULT, 101 },
	{ 0, 0, YYAT_REDUCE, 8 },
	{ 0, 0, YYAT_REDUCE, 2 },
	{ 0, 0, YYAT_REDUCE, 11 },
	{ -124, 1, YYAT_ERROR, 0 },
	{ -131, 1, YYAT_REDUCE, 51 },
	{ -105, 1, YYAT_ERROR, 0 },
	{ 0, 0, YYAT_REDUCE, 9 },
	{ 0, 0, YYAT_DEFAULT, 101 },
	{ 0, 0, YYAT_DEFAULT, 119 },
	{ 0, 0, YYAT_DEFAULT, 119 },
	{ -106, 1, YYAT_ERROR, 0 },
	{ -127, 1, YYAT_REDUCE, 23 },
	{ 0, 0, YYAT_REDUCE, 10 },
	{ -130, 1, YYAT_REDUCE, 51 },
	{ 0, 0, YYAT_REDUCE, 69 },
	{ 0, 0, YYAT_REDUCE, 70 },
	{ 0, 0, YYAT_REDUCE, 71 },
	{ 0, 0, YYAT_DEFAULT, 119 },
	{ 0, 0, YYAT_DEFAULT, 119 },
	{ -107, 1, YYAT_REDUCE, 67 },
	{ -229, 1, YYAT_REDUCE, 13 },
	{ 0, 0, YYAT_REDUCE, 65 },
	{ 0, 0, YYAT_REDUCE, 68 },
	{ -110, 1, YYAT_REDUCE, 51 },
	{ -112, 1, YYAT_DEFAULT, 97 },
	{ -134, 1, YYAT_REDUCE, 23 },
	{ -111, 1, YYAT_ERROR, 0 },
	{ -110, 1, YYAT_REDUCE, 22 },
	{ 0, 0, YYAT_REDUCE, 25 },
	{ -92, 1, YYAT_REDUCE, 26 },
	{ 0, 0, YYAT_DEFAULT, 119 },
	{ 0, 0, YYAT_REDUCE, 72 },
	{ -114, 1, YYAT_ERROR, 0 },
	{ -127, 1, YYAT_REDUCE, 67 },
	{ -241, 1, YYAT_REDUCE, 50 },
	{ -166, 1, YYAT_REDUCE, 77 },
	{ 0, 0, YYAT_DEFAULT, 119 },
	{ 0, 0, YYAT_DEFAULT, 119 },
	{ 0, 0, YYAT_DEFAULT, 119 },
	{ 0, 0, YYAT_DEFAULT, 119 },
	{ 0, 0, YYAT_DEFAULT, 119 },
	{ 0, 0, YYAT_DEFAULT, 119 },
	{ 0, 0, YYAT_DEFAULT, 119 },
	{ 0, 0, YYAT_DEFAULT, 119 },
	{ 0, 0, YYAT_DEFAULT, 119 },
	{ 0, 0, YYAT_DEFAULT, 119 },
	{ 0, 0, YYAT_DEFAULT, 119 },
	{ 0, 0, YYAT_DEFAULT, 119 },
	{ 0, 0, YYAT_REDUCE, 52 },
	{ -115, 1, YYAT_ERROR, 0 },
	{ -113, 1, YYAT_DEFAULT, 84 },
	{ -144, 1, YYAT_ERROR, 0 },
	{ -118, 1, YYAT_REDUCE, 27 },
	{ -253, 1, YYAT_REDUCE, 12 },
	{ 0, 0, YYAT_REDUCE, 66 },
	{ 0, 0, YYAT_DEFAULT, 119 },
	{ 0, 0, YYAT_REDUCE, 75 },
	{ -118, 1, YYAT_ERROR, 0 },
	{ -117, 1, YYAT_REDUCE, 76 },
	{ -139, 1, YYAT_REDUCE, 61 },
	{ -260, 1, YYAT_REDUCE, 62 },
	{ 0, 0, YYAT_REDUCE, 63 },
	{ 0, 0, YYAT_REDUCE, 64 },
	{ -122, 1, YYAT_REDUCE, 55 },
	{ -126, 1, YYAT_REDUCE, 56 },
	{ -130, 1, YYAT_REDUCE, 57 },
	{ -134, 1, YYAT_REDUCE, 58 },
	{ -181, 1, YYAT_REDUCE, 59 },
	{ -189, 1, YYAT_REDUCE, 60 },
	{ -206, 1, YYAT_REDUCE, 54 },
	{ -217, 1, YYAT_REDUCE, 53 },
	{ -186, 1, YYAT_ERROR, 0 },
	{ 0, 0, YYAT_REDUCE, 21 },
	{ 0, 0, YYAT_REDUCE, 32 },
	{ 0, 0, YYAT_REDUCE, 19 },
	{ 0, 0, YYAT_REDUCE, 24 },
	{ -122, 1, YYAT_DEFAULT, 119 },
	{ 0, 0, YYAT_REDUCE, 49 },
	{ 0, 0, YYAT_REDUCE, 73 },
	{ 0, 0, YYAT_DEFAULT, 119 },
	{ 0, 0, YYAT_REDUCE, 20 },
	{ 0, 0, YYAT_REDUCE, 18 },
	{ -247, 1, YYAT_REDUCE, 34 },
	{ 0, 0, YYAT_REDUCE, 28 },
	{ -273, 1, YYAT_ERROR, 0 },
	{ 0, 0, YYAT_REDUCE, 74 },
	{ 0, 0, YYAT_REDUCE, 31 },
	{ -125, 1, YYAT_DEFAULT, 132 },
	{ -101, 1, YYAT_ERROR, 0 },
	{ 0, 0, YYAT_REDUCE, 29 },
	{ -122, 1, YYAT_ERROR, 0 },
	{ -123, 1, YYAT_ERROR, 0 },
	{ -122, 1, YYAT_DEFAULT, 119 },
	{ -130, 1, YYAT_ERROR, 0 },
	{ -158, 1, YYAT_ERROR, 0 },
	{ 0, 0, YYAT_REDUCE, 43 },
	{ 0, 0, YYAT_REDUCE, 30 },
	{ 0, 0, YYAT_REDUCE, 39 },
	{ 0, 0, YYAT_REDUCE, 33 },
	{ 0, 0, YYAT_REDUCE, 35 },
	{ 0, 0, YYAT_REDUCE, 36 },
	{ 0, 0, YYAT_REDUCE, 37 },
	{ 0, 0, YYAT_REDUCE, 38 },
	{ -167, 1, YYAT_ERROR, 0 },
	{ -156, 1, YYAT_REDUCE, 51 },
	{ 0, 0, YYAT_DEFAULT, 119 },
	{ -161, 1, YYAT_DEFAULT, 101 },
	{ 0, 0, YYAT_REDUCE, 47 },
	{ -187, 1, YYAT_ERROR, 0 },
	{ 0, 0, YYAT_REDUCE, 41 },
	{ 0, 0, YYAT_REDUCE, 40 },
	{ 0, 0, YYAT_REDUCE, 42 },
	{ -210, 1, YYAT_ERROR, 0 },
	{ -212, 1, YYAT_ERROR, 0 },
	{ 0, 0, YYAT_REDUCE, 48 },
	{ 0, 0, YYAT_DEFAULT, 132 },
	{ 0, 0, YYAT_DEFAULT, 132 },
	{ -246, 1, YYAT_REDUCE, 44 },
	{ 0, 0, YYAT_REDUCE, 46 },
	{ -185, 1, YYAT_DEFAULT, 119 },
	{ 0, 0, YYAT_REDUCE, 45 }
};

int YYNEAR YYDCDECL yynontermgoto_size = 74;

YYCONST yynontermgoto_t YYNEARFAR YYBASED_CODE YYDCDECL yynontermgoto[] = {
	{ 119, 36 },
	{ 132, 110 },
	{ 30, -1 },
	{ 30, 44 },
	{ 132, 133 },
	{ 132, 112 },
	{ 132, 113 },
	{ 132, 114 },
	{ 132, 115 },
	{ 132, 116 },
	{ 7, 14 },
	{ 7, 13 },
	{ 20, 26 },
	{ 7, 9 },
	{ 129, 131 },
	{ 7, 12 },
	{ 7, 11 },
	{ 7, 10 },
	{ 119, 126 },
	{ 119, 46 },
	{ 119, 47 },
	{ 119, 34 },
	{ 119, 35 },
	{ 101, 117 },
	{ 48, 69 },
	{ 95, 99 },
	{ 101, 16 },
	{ 95, 101 },
	{ 64, 42 },
	{ 48, 71 },
	{ 48, 70 },
	{ 20, 25 },
	{ 128, 130 },
	{ 64, 88 },
	{ 118, 125 },
	{ 95, 100 },
	{ 89, -1 },
	{ 89, 32 },
	{ 89, 97 },
	{ 38, 62 },
	{ 38, 40 },
	{ 38, 41 },
	{ 101, 15 },
	{ 0, 6 },
	{ 0, 7 },
	{ 0, 8 },
	{ 105, 121 },
	{ 100, 111 },
	{ 92, 98 },
	{ 86, 95 },
	{ 84, 94 },
	{ 68, 90 },
	{ 63, 87 },
	{ 60, 83 },
	{ 59, 82 },
	{ 58, 81 },
	{ 57, 80 },
	{ 56, 79 },
	{ 55, 78 },
	{ 54, 77 },
	{ 53, 76 },
	{ 52, 75 },
	{ 51, 74 },
	{ 50, 73 },
	{ 49, 72 },
	{ 43, 66 },
	{ 42, 65 },
	{ 31, 45 },
	{ 24, 39 },
	{ 22, 37 },
	{ 21, 33 },
	{ 17, 23 },
	{ 13, 18 },
	{ 12, 17 }
};

YYCONST yystategoto_t YYNEARFAR YYBASED_CODE YYDCDECL yystategoto[] = {
	{ 42, 7 },
	{ 0, -1 },
	{ 0, -1 },
	{ 0, -1 },
	{ 0, -1 },
	{ 0, -1 },
	{ 0, -1 },
	{ 7, -1 },
	{ 0, -1 },
	{ 0, -1 },
	{ 0, -1 },
	{ 0, -1 },
	{ 69, 101 },
	{ 67, -1 },
	{ 0, -1 },
	{ 0, -1 },
	{ 0, -1 },
	{ 66, -1 },
	{ 0, -1 },
	{ 0, -1 },
	{ 8, -1 },
	{ 46, 89 },
	{ 45, 89 },
	{ 0, -1 },
	{ 57, 38 },
	{ 0, -1 },
	{ 0, -1 },
	{ 0, -1 },
	{ 0, -1 },
	{ 0, -1 },
	{ -22, 89 },
	{ 45, 119 },
	{ 0, -1 },
	{ 0, -1 },
	{ 0, -1 },
	{ 0, -1 },
	{ 0, -1 },
	{ 0, -1 },
	{ 28, 64 },
	{ 0, -1 },
	{ 0, -1 },
	{ 0, -1 },
	{ 62, -1 },
	{ 41, 89 },
	{ 0, -1 },
	{ 0, -1 },
	{ 0, -1 },
	{ 0, -1 },
	{ 2, 119 },
	{ 40, 89 },
	{ 39, 89 },
	{ 38, 89 },
	{ 37, 89 },
	{ 36, 89 },
	{ 35, 89 },
	{ 34, 89 },
	{ 33, 89 },
	{ 32, 89 },
	{ 31, 89 },
	{ 30, 89 },
	{ 29, 89 },
	{ 0, -1 },
	{ 0, -1 },
	{ 38, -1 },
	{ 20, -1 },
	{ 0, -1 },
	{ 0, -1 },
	{ 0, -1 },
	{ 29, 119 },
	{ 0, -1 },
	{ 0, -1 },
	{ 0, -1 },
	{ 0, -1 },
	{ 0, -1 },
	{ 0, -1 },
	{ 0, -1 },
	{ 0, -1 },
	{ 0, -1 },
	{ 0, -1 },
	{ 0, -1 },
	{ 0, -1 },
	{ 0, -1 },
	{ 0, -1 },
	{ 0, -1 },
	{ 36, -1 },
	{ 0, -1 },
	{ 34, -1 },
	{ 0, -1 },
	{ 0, -1 },
	{ 14, 119 },
	{ 0, -1 },
	{ 0, -1 },
	{ 26, 119 },
	{ 0, -1 },
	{ 0, -1 },
	{ 19, -1 },
	{ 0, -1 },
	{ 0, -1 },
	{ 0, -1 },
	{ 0, -1 },
	{ 30, 132 },
	{ 19, -1 },
	{ 0, -1 },
	{ 0, -1 },
	{ 0, -1 },
	{ 24, 119 },
	{ 0, -1 },
	{ 0, -1 },
	{ 0, -1 },
	{ 0, -1 },
	{ 0, -1 },
	{ 0, -1 },
	{ 0, -1 },
	{ 0, -1 },
	{ 0, -1 },
	{ 0, -1 },
	{ 0, -1 },
	{ 0, -1 },
	{ 12, 119 },
	{ -4, -1 },
	{ 0, -1 },
	{ 0, -1 },
	{ 0, -1 },
	{ 0, -1 },
	{ 0, -1 },
	{ 0, -1 },
	{ 0, -1 },
	{ 0, -1 },
	{ 15, 132 },
	{ -3, 132 },
	{ 0, -1 },
	{ 0, -1 },
	{ -13, 119 },
	{ 0, -1 }
};

YYCONST yydestructor_t YYNEARFAR *YYNEAR YYDCDECL yydestructorptr = NULL;

YYCONST yytokendest_t YYNEARFAR *YYNEAR YYDCDECL yytokendestptr = NULL;
int YYNEAR YYDCDECL yytokendest_size = 0;

YYCONST yytokendestbase_t YYNEARFAR *YYNEAR YYDCDECL yytokendestbaseptr = NULL;
int YYNEAR YYDCDECL yytokendestbase_size = 0;
#line 408 ".\\parse.y"


void yyerror(const char * message)
{ fprintf(listing,"Syntax error at line %d: %s\n",lineno,message);
  fprintf(listing,"Current token: ");
  printToken(yychar,tokenString);
  Error = TRUE;
}

/* yylex calls getToken to make Yacc/Bison output
 * compatible with ealier versions of the TINY scanner
 */
#ifdef YYPROTOTYPE
int YYCDECL yygettoken(void)
#else
int YYCDECL yygettoken()
#endif
{
	return yylex();
}

static TokenType yylex(void)
{ return getToken(); }

TreeNode * parse(void)
{ yyparse();
  return savedTree;
}

