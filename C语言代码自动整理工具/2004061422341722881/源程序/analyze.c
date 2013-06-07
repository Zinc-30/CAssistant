/****************************************************/
/* File: analyze.c                                  */
/* Semantic analyzer implementation					*/
/* for the C_Minus compiler							*/
/****************************************************/

#include "globals.h"
#include "util.h"
#include "parse.h"
#include "symtab.h"
#include "analyze.h"

/* counter for variable memory locations */
static int location = 0;

/* current symble table */
static Symtab * pTable;
static FunEntry * pFun;

/* procedure traverse is a generic recursive
 * syntax tree traversal routine:
 * it applies preProc in preorder and postProc 
 * in postorder to tree pointed to by t
 */
static void traverse(TreeNode * t, 
					 void (* preProc) (TreeNode *),
					 void (* postProc) (TreeNode *))
{ 
	if (t != NULL)
	{ 
		int i;
		preProc(t);
		for (i=0; i < MAXCHILDREN; i++)
			traverse(t->child[i], preProc, postProc);
		postProc(t);
		traverse(t->sibling, preProc, postProc);
	}
}

/* nullProc is a do-nothing procedure to 
 * generate preorder-only or postorder-only
 * traversals from traverse
 */
static void nullpreProc(TreeNode * t)
{ 
	if (t == NULL) return;
	else if (t->nodekind == Dec) {
		switch (t->kind.dec)
		{
		case FunDefK:
			pFun = Lookup_Fun(t->attr.name);
			break;
		case CompK:
			pTable = t->attr.table;
			break;
		}
	}
}

static void nullpostProc(TreeNode * t)
{ 
	if (t == NULL || pTable == NULL) return;
	else if (t->nodekind == Dec && t->kind.dec == CompK)
		pTable = pTable->parent;
}

/* procedure insertNode inserts 
 * identifiers stored in t into 
 * the symbol table 
 */
static void insertNode(TreeNode * t)
{ 
	switch (t->nodekind)
	{ 
    case Dec:
		switch (t->kind.dec)
		{ 
		case FunDecK:
			if (Lookup_Fun(t->attr.name) == NULL)
				Insert_Fun(t->attr.name, t->type, t->child[0]);
			break;
		case FunDefK:
			if (Lookup_Fun(t->attr.name) == NULL)
				pFun = Insert_Fun(t->attr.name, t->type, t->child[0]);
			break;
		case VarK:
		{
			ValEntry Entry;
			TreeNode * child;
			for (child = t->child[0]; child != NULL; child = child->sibling) {
				if (child->nodekind == Exp && child->kind.exp == IdK) {
					if (Lookup_Var(pTable, pFun, child->attr.name, &Entry) != pTable->nestlevel)
						if (child->child[0] == NULL)
							Insert_Var(pTable, child->attr.name, t->type, 1);
						else
							Insert_Var(pTable, child->attr.name, t->type, child->child[0]->attr.val.i);
				}
				else if (child->nodekind == Stmt && child->kind.stmt == AssignK) {
					if (Lookup_Var(pTable, pFun, child->child[0]->attr.name, &Entry) != pTable->nestlevel)
						if (child->child[0]->child[0] == NULL)
							Insert_Var(pTable, child->child[0]->attr.name, t->type, 1);
						else
							Insert_Var(pTable, child->child[0]->attr.name, t->type, child->child[0]->child[0]->attr.val.i);
				}
			}
		}
			break;
		case CompK:
			pTable = Createtab(pTable, pFun);
			if (pTable==NULL)
				fprintf(listing, "Out of memory error at line %d\n", t->lineno);
			t->attr.table = pTable;
			break;
        default:
			break;
      }
      break;
	default:
		break;
	}
}

/* function buildSymtab constructs the symbol 
 * table by preorder traversal of the syntax tree
 */
void buildSymtab(TreeNode * tree)
{
	GlobalTable = Createtab(NULL, NULL);
	if (GlobalTable==NULL)
		fprintf(listing, "Out of memory error at line %d\n", tree->lineno);
	pTable = GlobalTable;
	traverse(tree, insertNode, nullpostProc);
	if (TraceAnalyze)
	{ 
		printFunTab();
		printSymTab(tree);
	}
}

static void typeError(TreeNode * t, char * message)
{ 
	fprintf(listing,"Type error at line %d: %s\n", t->lineno, message);
	Error = TRUE;
}

/* procedure checkNode performs
 * type checking at a single tree node
 */
static void checkNode(TreeNode * t)
{ 
	switch (t->nodekind)
	{ 
    case Dec:
		if (t->kind.dec == CompK)
			pTable = pTable->parent;
		break;
	case Exp:
		switch (t->kind.exp)
		{ 
		case OpK:
			switch(t->attr.op) {
			case PLUS: case SUB: case MUT: case DIV:
				if ((t->child[0]->type != Integer && t->child[0]->type != Float) ||
					(t->child[1]->type != Integer && t->child[1]->type != Float))
					typeError(t, "Op applied to non-number");
				else if (t->child[0]->type == Float || t->child[1]->type == Float)
					t->type = Float;
				else
					t->type = Integer;
				break;
			case LT: case LE: case GT: case GE: case EQ: case NEQ:
				if ((t->child[0]->type != Integer && t->child[0]->type != Float) ||
					(t->child[1]->type != Integer && t->child[1]->type != Float))
					typeError(t, "Op applied to non-number");
				else 
					t->type = Boolean;
				break;
			case AND: case OR:
				if ((t->child[0]->type != Integer && t->child[0]->type != Boolean) ||
					(t->child[1]->type != Integer && t->child[1]->type != Boolean))
					typeError(t, "Op applied to non-boolean");
				else
					t->type = Boolean;
				break;
			}
			break;
        case IdK:
		{
			ValEntry Entry;
			if (Lookup_Var(pTable, pFun, t->attr.name, &Entry) != -1)
				t->type = Entry.type;
			else {
				ValEntry * pEntry;
				for (pEntry = pFun->para; pEntry != NULL; pEntry = pEntry->next)
					if (strcmp(t->attr.name, pEntry->name) == 0) {
						t->type = pEntry->type;
						break;
					}
				if (pEntry == NULL)
					typeError(t, "reference to undefined id");
			}
		}
			break;
		}
		break;
    case Stmt:
		switch (t->kind.stmt)
		{ 
		case IfK:
			if (t->child[0]->type != Boolean && t->child[0]->type != Integer)
				typeError(t->child[0], "if test is not Boolean");
			break;
        case WhileK:
			if (t->child[0]->type != Boolean && t->child[0]->type != Integer)
				typeError(t->child[0], "while test is not Boolean");
			break;
		case CallK: 
		{
			FunEntry * pEntry = Lookup_Fun(t->attr.name);
			if (pEntry != NULL) {
				ValEntry * para;
				t->type = pEntry->type;
				for (para = pEntry->para, t = t->child[0]; para != NULL && t != NULL;
					para = para->next, t = t->sibling)
					if (para->type != t->type)
						typeError(t, "call to function with wrong parameter");
				if (para != NULL || t != NULL)
					typeError(t, "call to function with wrong parameter");
			}
			else
				typeError(t, "call to undefined function");
		}
			break;
		case ReturnK:
			t->type = t->child[0]->type;
			if (t->type != pFun->type)
				typeError(t, "return type inconsistent with definition");
			break;
		case AssignK:
			if (t->child[0]->type != t->child[1]->type) {
				if (t->child[0]->type == Float && t->child[1]->type == Integer)
					t->type = t->child[1]->type = Float;
				else if (t->child[0]->type == Integer && t->child[1]->type == Float) 
					t->type = Integer;
				else 
					typeError(t->child[0], "assignment type mismatched");
			}
			t->type = t->child[0]->type;
			break;
		}
		break;
	}
}

/* procedure transNode transforms
 * a tree node type to the appropriate one 
 */
static void transNode(TreeNode * t)
{
	if (t->nodekind == Exp && t->kind.exp == OpK) {
		switch(t->attr.op) {
		case PLUS: case SUB: case MUT: case DIV:
			if ((t->type == Float && t->child[0]->type == Integer)) {
				t->child[0]->type = Float;
				if (t->child[0]->nodekind == Exp && t->child[0]->kind.exp == NumK)
					t->child[0]->attr.val.f = (float)(t->child[0]->attr.val.i);
			}
			if ((t->type == Float && t->child[1]->type == Integer)) {
				t->child[1]->type = Float;
				if (t->child[1]->nodekind == Exp && t->child[1]->kind.exp == NumK)
					t->child[1]->attr.val.f = (float)(t->child[1]->attr.val.i);
			}
			break;
		}
	}
}

/* procedure typeCheck performs type checking 
 * by a postorder syntax tree traversal
 */
void typeCheck(TreeNode * syntaxTree)
{ 
	traverse(syntaxTree, nullpreProc, checkNode);
	traverse(syntaxTree, transNode, nullpostProc);
}
