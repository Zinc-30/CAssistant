/****************************************************/
/* File: symtab.c                                   */
/* Symbol table implementation						*/
/* for the C_Minus compiler							*/
/****************************************************/

#include <stdio.h>

#include "globals.h"
#include "util.h"
#include "symtab.h"

Symtab * GlobalTable;		//global symble table for variables
Symtab * pTable;	
FunEntry * FunTable[SIZE];	//symble table for functions

/* the hash function */
static int hash(char * key)
{
	int temp = 0;
	int i;
	for (i = 0; key[i] != '\0'; i++)
		temp = ((temp << SHIFT) + key[i]) % SIZE;
	return temp;
}

/* create a new variable table
 * and link it to its parent
 */
Symtab * Createtab(Symtab * pTable, FunEntry *pEntry)
{
	Symtab * newtab = (Symtab *)malloc(sizeof(Symtab));
	if (newtab == NULL)
		return NULL;	//out of memory
 	newtab->parent = pTable;
	newtab->nestlevel = (pTable == NULL)? 0 : pTable->nestlevel+1;
	newtab->memloc = 0;
	memset(newtab->valTable, 0, SIZE * sizeof(ValEntry *));
	newtab->funEntry = pEntry;
	return newtab;
}

/* insert a new entry to the variable table */
ValEntry * Insert_Var(Symtab * pTable, char * name, Type type, int count)
{
	int hashnumber = hash(name), size;
	ValEntry * pnew = (ValEntry *)malloc(sizeof(ValEntry));

	switch(type) {
	case Integer:	size = sizeofint;		break;
	case Float:		size = sizeoffloat;	break;
	case Char:		size = sizeofchar;	break;
	default:		size = sizeofint;
	}
	pTable->memloc += size * count;
	pnew->name = copyString(name);
	pnew->type = type;
	pnew->offset = -pTable->memloc;
	pnew->next = pTable->valTable[hashnumber];
	pTable->valTable[hashnumber] = pnew;
	return pnew;
}

/* lookup a variable in the symbol table */
int Lookup_Var(Symtab * pTable, FunEntry * pFun, char * name, ValEntry * pEntry)
{
	int hashnumber = hash(name);
	ValEntry * ptemp;

	for ( ; pTable != NULL; pTable = pTable->parent) {		
		for (ptemp = pTable->valTable[hashnumber]; ptemp != NULL; ptemp = ptemp->next)
			if (strcmp(ptemp->name, name) == 0) {
				pEntry->name = copyString(ptemp->name);
				pEntry->type = ptemp->type;
				pEntry->offset = ptemp->offset;
				pEntry->next = NULL;
				return pTable->nestlevel;
			}
	}
	if (pFun != NULL) {
		for (ptemp = pFun->para; ptemp != NULL; ptemp = ptemp->next)
			if (strcmp(name, ptemp->name) == 0) {
				pEntry->name = copyString(ptemp->name);
				pEntry->type = ptemp->type;
				pEntry->offset = ptemp->offset;
				pEntry->next = NULL;
				return 1;
			}
	}
	return -1;
}

/* insert a new entry to the function table */
FunEntry * Insert_Fun(char * name, Type type, TreeNode * pTreeNode)
{
	int hashnumber = hash(name), size = 14;
	FunEntry * pnew = (FunEntry *)malloc(sizeof(FunEntry));
	ValEntry * para;
	TreeNode * ptemp;

	pnew->name = copyString(name);
	pnew->type = type;
	pnew->para = NULL;
	if (strcmp(name, "main") == 0)
		size += 4;
	if (pTreeNode != NULL) {
		pnew->para = (ValEntry *)malloc(sizeof(ValEntry));
		pnew->para->name = copyString(pTreeNode->attr.name);
		pnew->para->type = pTreeNode->type;
		pnew->para->offset = size;
		if (pTreeNode->child[0] == NULL)
			switch (pnew->para->type) {
			case Integer:	size += sizeofint;	break;
			case Float:		size += sizeoffloat;	break;
			case Char:		size += sizeofchar;	break;
			default:		size += sizeofint;
			}
		else
			size += sizeofint;
		for (ptemp = pTreeNode->sibling, para = pnew->para;
			ptemp != NULL; ptemp = ptemp->sibling, para = para->next) {
			para->next = (ValEntry *)malloc(sizeof(ValEntry));
			para->next->name = copyString(ptemp->attr.name);
			para->next->type = ptemp->type;
			para->next->offset = size;
			if (ptemp->child[0] == NULL)
				switch (para->next->type) {
				case Integer:	size += sizeofint;	break;
				case Float:		size += sizeoffloat;	break;
				case Char:		size += sizeofchar;	break;
				default:		size += sizeofint;
				}
			else
				size += sizeofint;
		}
		para->next = NULL;
	}
	pnew->ret_val = size;
	pnew->next = FunTable[hashnumber];
	FunTable[hashnumber] = pnew;
	return pnew;
}

/* lookup a function in the symbol table */
FunEntry * Lookup_Fun(char * name)
{
	int hashnumber = hash(name);
	FunEntry * pEntry;

	for (pEntry = FunTable[hashnumber]; pEntry != NULL; pEntry = pEntry->next)
		if (strcmp(pEntry->name, name) == 0)
			return pEntry;
	return NULL;
}

/* procedure printFunTab prints a formatted 
 * listing of the function table contents 
 * to the listing file
 */
void printFunTab(void)
{
	int i;
	fprintf(listing, "\nFunction table:\n");
	fprintf(listing,"\nFunction Name  Type    \n");
	fprintf(listing,"-------------  ----    \n");
	for (i=0; i<SIZE; ++i) {
		FunEntry * pEntry;
		for (pEntry = FunTable[i]; pEntry != NULL; pEntry = pEntry->next) {
			ValEntry * para;
			fprintf(listing, "%-14s ", pEntry->name);
			printType(pEntry->type);
			fprintf(listing, "\nParameter\n");
			fprintf(listing, "---------\n");
			for (para = pEntry->para ; para != NULL; para = para->next) {
				fprintf(listing, "%s ", para->name);
				printType(para->type);
				fprintf(listing, "  %-d\n", para->offset);
			}
		}
	}
}

/* procedure printSymTab prints a formatted 
 * listing of the symbol table contents 
 * to the listing file
 */
void printSymTab(TreeNode * tree)
{ 
	static int Globalprinted = FALSE;
	Symtab * pTable;

	if (!Globalprinted) {
		int i;
		fprintf(listing, "\nSymbol table:\n");
		fprintf(listing, "\nNestlevel: %d\n", GlobalTable->nestlevel); 
		fprintf(listing,"Variable Name  Type && Offset\n");
		fprintf(listing,"-------------  --------------\n");
		for (i=0; i<SIZE; ++i) {
				ValEntry * pEntry;
				for (pEntry = GlobalTable->valTable[i]; pEntry != NULL; pEntry = pEntry->next) {
					fprintf(listing, "%-14s ", pEntry->name);
					printType(pEntry->type);
					fprintf(listing, "  %-d\n", pEntry->offset);
				}
		}
		Globalprinted = TRUE;
	}
	while (tree != NULL) {
		int i;
		if (tree ->nodekind == Dec && tree->kind.dec == CompK) {
			pTable = tree->attr.table;    
			fprintf(listing, "\nNestlevel: %d\n", pTable->nestlevel); 
			fprintf(listing,"Variable Name  Type && Offset\n");
			fprintf(listing,"-------------  --------------\n");
			for (i=0; i<SIZE; ++i) {
				ValEntry * pEntry;
				for (pEntry = pTable->valTable[i]; pEntry != NULL; pEntry = pEntry->next) {
					fprintf(listing, "%-14s ", pEntry->name);
					printType(pEntry->type);
					fprintf(listing, "  %-d\n", pEntry->offset);
				}
			}
		}
		for (i=0; i<MAXCHILDREN; i++)
			printSymTab(tree->child[i]);
		tree = tree->sibling;
	}
}