/****************************************************/
/* File: globals.h                                  */
/* Global types and vars for C_Minus compiler       */
/* must come before other include files             */
/****************************************************/

#ifndef _GLOBALS_H_
#define _GLOBALS_H_

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#ifndef FALSE
#define FALSE 0
#endif

#ifndef TRUE
#define TRUE 1
#endif

#define sizeofint 2
#define sizeofchar 2
#define sizeoffloat sizeof(float)

/* MAXRESERVED = the number of reserved words */
#define MAXRESERVED 10
#define VARIABLE_LENGTH 2
#define EXP_VARIABLE_LENGTH 1
#define LABEL_SIZE 10

typedef int TokenType;

extern FILE* source; /* source code text file */
extern FILE* listing; /* listing output text file */
extern FILE* inter_code; /* code text file for TM simulator */

extern int lineno; /* source line number for listing */

/**************************************************/
/***********   Syntax tree for parsing ************/
/**************************************************/


typedef enum {Dec,Stmt,Exp} NodeKind;
typedef enum {IfK,WhileK,CallK,ReturnK,BreakK,ContinueK,AssignK} StmtKind;
typedef enum {OpK,NumK,FnumK,CharK,IdK,NotK} ExpKind;
typedef enum {FunDecK,FunDefK,VarK,CompK,ParamK} DecKind;

/* Type is used for type checking */
typedef enum {Void,Integer,Float,Boolean,Char} Type;

/* the size of the symble table */
#define SIZE 13

/* the record in the variable table for 
   each variable */
typedef struct valEntry {
	char * name;
	Type type;
	int offset;		//used for activation record
	struct valEntry * next;
} ValEntry;

/* the record in the function table for 
   each function */
typedef struct funEntry {
	char * name;
	Type type;
	int ret_val;
	ValEntry * para;	//parameters of the function
	struct funEntry * next;
} FunEntry;

/* the symble table structure for variables */
typedef struct symtab {
	struct symtab * parent;
	int nestlevel;
	int memloc;		//memory location for variables in the symble table
	ValEntry * valTable[SIZE];
	FunEntry * funEntry;
	char lab1[LABEL_SIZE];
	char lab2[LABEL_SIZE];
} Symtab;


#define MAXCHILDREN 3

typedef struct treeNode
   { struct treeNode * child[MAXCHILDREN];
     struct treeNode * sibling;
     int lineno;
     NodeKind nodekind;
	 union { StmtKind stmt; ExpKind exp; DecKind dec;} kind;
     union { TokenType op;
             union
				{int i;
				 float f;
				} val;
             char * name; 
			 Symtab * table;
           } attr;
	 int call_stmt;
     Type type; 
   } TreeNode;

/**************************************************/
/***********   Flags for tracing       ************/
/**************************************************/

/* TraceScan = TRUE causes token information to be
 * printed to the listing file as each token is
 * recognized by the scanner
 */
extern int TraceScan;

/* TraceParse = TRUE causes the syntax tree to be
 * printed to the listing file in linearized form
 * (using indents for children)
 */
extern int TraceParse;

/* TraceAnalyze = TRUE causes symbol table inserts
 * and lookups to be reported to the listing file
 */
extern int TraceAnalyze;

/* Error = TRUE prevents further passes if an error occurs */
extern int Error; 
#endif
