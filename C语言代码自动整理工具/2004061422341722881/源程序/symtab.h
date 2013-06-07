/****************************************************/
/* File: symtab.h                                   */
/* Symbol table interface							*/
/* for the C_Minus compiler							*/
/****************************************************/

#ifndef _SYMTAB_H_
#define _SYMTAB_H_

/* the power of two used as multiplier
   in hash function */
#define SHIFT 4

extern Symtab * GlobalTable;		//global symble table for variables
extern Symtab * pTable;		//global symble table for variables
extern FunEntry * FunTable[SIZE];	//symble table for functions

/* create a new variable table
 * and link it to its parent
 */
Symtab * Createtab(Symtab * pTable, FunEntry *pEntry);
/* insert a new entry to the variable table */
ValEntry * Insert_Var(Symtab * pTable, char * name, Type type, int count);
/* lookup a variable in the symbol table */
int Lookup_Var(Symtab * pTable, FunEntry * pFun, char * name, ValEntry * pEntry);
/* insert a new entry to the function table */
FunEntry * Insert_Fun(char * name, Type type, TreeNode * pTreeNode);
/* lookup a function in the symbol table */
FunEntry * Lookup_Fun(char * name);

/* procedure printFunTab prints a formatted 
 * listing of the function table contents 
 * to the listing file
 */
void printFunTab(void);

/* procedure printSymTab prints a formatted 
 * listing of the symbol table contents 
 * to the listing file
 */
void printSymTab(TreeNode * tree);

#endif

