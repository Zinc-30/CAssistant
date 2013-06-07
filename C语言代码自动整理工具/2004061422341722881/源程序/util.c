/****************************************************/
/* File: util.c                                     */
/* Utility function implementation                  */
/* for the C_Minus compiler                         */
/****************************************************/

#include "globals.h"
#include "util.h"
#include "parse.h"

void printType(Type type)
{
	switch(type){
	case Void:	fprintf(listing,"Void"); break;
	case Integer:	fprintf(listing,"Integer"); break;
	case Float:	fprintf(listing,"Float"); break;
	case Char:	fprintf(listing,"Char"); break;
	case Boolean:	fprintf(listing,"Boolean"); break;
	default: fprintf(listing,"Unknown Type"); break;
	}
}

/* procedure printToken prints a token 
 * and its lexeme to the listing file
 */
void printToken(TokenType token, const char* tokenString )
{ switch (token)
  { case INT:
	case CHAR:
	case FLOAT:
	case VOID:
	case IF:
    case ELSE:
    case WHILE:
    case RETURN:
      fprintf(listing,"reserved word: %s\n",tokenString);
      break;
    case PLUS: fprintf(listing,"+\n"); break;
    case SUB: fprintf(listing,"-\n"); break;
    case MUT: fprintf(listing,"*\n"); break;
    case DIV: fprintf(listing,"/\n"); break;
    case LT: fprintf(listing,"<\n"); break;
    case LE: fprintf(listing,"<=\n"); break;
    case GT: fprintf(listing,">\n"); break;
    case GE: fprintf(listing,">=\n"); break;
    case EQ: fprintf(listing,"==\n"); break;
    case NEQ: fprintf(listing,"!=\n"); break;
    case AND: fprintf(listing,"&&\n"); break;
    case OR: fprintf(listing,"||\n"); break;
    case NOT: fprintf(listing,"!\n"); break;
    case ASSIGN: fprintf(listing,"=\n"); break;
    case SEMI: fprintf(listing,";\n"); break;
    case COMMA: fprintf(listing,",\n"); break;
    case LP: fprintf(listing,"(\n"); break;
    case RP: fprintf(listing,")\n"); break;
    case LSP: fprintf(listing,"[\n"); break;
    case RSP: fprintf(listing,"]\n"); break;
    case LFP: fprintf(listing,"{\n"); break;
    case RFP: fprintf(listing,"}\n"); break;
	case ENDFILE: fprintf(listing,"EOF\n"); break;
    case NUM: fprintf(listing,"NUM, val= %s\n",tokenString); break;
    case FNUM: fprintf(listing,"FNUM, val= %s\n",tokenString); break;
	case SCHAR: fprintf(listing,"SCHAR, val= %s\n",tokenString); break;
    case ID: fprintf(listing,"ID, name= %s\n",tokenString); break;
    case ERROR:fprintf(listing,"ERROR: %s\n",tokenString); break;
    default: /* should never happen */
      fprintf(listing,"Unknown token: %d\n",token);
  }
}

/* function newNode creates a new treenode
 * for syntax tree construction
 */
TreeNode * newDecNode(DecKind kind)
{ 
  TreeNode * t = (TreeNode *) malloc(sizeof(TreeNode));
  int i;
  if (t==NULL)
    fprintf(listing,"Out of memory error at line %d\n",lineno);
  else {
    for (i=0;i<MAXCHILDREN;i++) t->child[i] = NULL;
    t->sibling = NULL;
    t->nodekind = Dec;
    t->lineno = lineno;
	t->call_stmt = 0;
    t->kind.dec = kind;
  }
  return t;
}

TreeNode * newStmtNode(StmtKind kind)
{ TreeNode * t = (TreeNode *) malloc(sizeof(TreeNode));
  int i;
  if (t==NULL)
    fprintf(listing,"Out of memory error at line %d\n",lineno);
  else {
    for (i=0;i<MAXCHILDREN;i++) t->child[i] = NULL;
    t->sibling = NULL;
    t->nodekind = Stmt;
    t->lineno = lineno;
	t->call_stmt = 0;
	t->kind.stmt = kind;
  }
  return t;
}

TreeNode * newExpNode(ExpKind kind)
{ TreeNode * t = (TreeNode *) malloc(sizeof(TreeNode));
  int i;
  if (t==NULL)
    fprintf(listing,"Out of memory error at line %d\n",lineno);
  else {
    for (i=0;i<MAXCHILDREN;i++) t->child[i] = NULL;
    t->sibling = NULL;
    t->nodekind = Exp;
    t->lineno = lineno;
	t->call_stmt = 0;
	t->kind.exp = kind;
  }
  return t;
}


/* function copyString allocates and makes a new
 * copy of an existing string
 */
char * copyString(char * s)
{ int n;
  char * t;
  if (s==NULL) return NULL;
  n = strlen(s)+1;
  t = malloc(n);
  if (t==NULL)
    fprintf(listing,"Out of memory error at line %d\n",lineno);
  else strcpy(t,s);
  return t;
}

/* variable indentno is used by printTree to
 * store current number of spaces to indent
 */
static indentno = 0;

/* macros to increase/decrease indentation */
#define INDENT indentno+=2
#define UNINDENT indentno-=2

/* printSpaces indents by printing spaces */
static void printSpaces(void)
{ int i;
  for (i=0;i<indentno;i++)
    fprintf(listing," ");
}

/* procedure printTree prints a syntax tree to the 
 * listing file using indentation to indicate subtrees
 */
void printTree(TreeNode * tree)
{ int i;
  INDENT;
  while (tree != NULL) {
	printSpaces();
    
    switch (tree ->nodekind) {
	 case Dec:
		 switch(tree ->kind.dec){
		 case VarK:
          fprintf(listing,"ID_Dec Var_Type: ");
		  printType(tree ->type);
		  fprintf(listing,"\n");
          break;
		 case FunDecK:
          fprintf(listing,"Fun_Dec name: %s		Return_Type: ",tree->attr.name);
          printType(tree ->type);
		  fprintf(listing,"\n");
		  break;
		 case FunDefK:
          fprintf(listing,"Fun_Def name: %s		Return_Type: ",tree->attr.name);
		  printType(tree ->type);
		  fprintf(listing,"\n");
          break;
         case ParamK:
          fprintf(listing,"Param_Dec Param_Type: ");
		  printType(tree ->type);
		  fprintf(listing,"\n");
          break;
         case CompK:
          fprintf(listing,"Comp_Dec \n");
          break;
		 }
		 break;
	  case Stmt:
		 switch(tree ->kind.stmt){
         case IfK:
          fprintf(listing,"If\n");
          break;
         case WhileK:
          fprintf(listing,"While\n");
          break;
         case AssignK:
          fprintf(listing,"Assign\n");
          break;
         case ReturnK:
          fprintf(listing,"Return\n");
          break;
         case CallK:
          fprintf(listing,"Call to: %s\n",tree ->attr.name);
          break;
		case ContinueK:
          fprintf(listing,"Continue\n");
          break;
		case BreakK:
          fprintf(listing,"break\n");
          break;
		 }
		 break;
	  case Exp:
		 switch(tree->kind.exp){
         case NumK:
			fprintf(listing,"Num_Const: %d\n",tree->attr.val.i);
			break;
		 case FnumK:
		    fprintf(listing,"FNum_Const: %f\n",tree->attr.val.f);
			break;
         case CharK:
		    fprintf(listing,"Char_Const: %c\n",tree->attr.val.i);
			break;
		 case IdK:
			fprintf(listing,"Var: %s\n",tree->attr.name);
			break;
		 case NotK:
			 fprintf(listing,"Not: \n");
			 break;
		 default:
          fprintf(listing,"Op: ");
          printToken(tree->attr.op,"\0");
          break;
		 }
		 break;
       default:
          fprintf(listing,"Unknown treenode kind\n");
          break;
      }
    
    for (i=0;i<MAXCHILDREN;i++)
         printTree(tree->child[i]);
    tree = tree->sibling;
  }
  UNINDENT;
}
       