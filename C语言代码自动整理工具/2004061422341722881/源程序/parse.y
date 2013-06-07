%{
#define YYPARSER /* distinguishes Yacc output from other code files */

#include "globals.h"
#include "util.h"
#include "scan.h"
#include "parse.h"


static char * savedFunName; /* for use in assignments */
static char * savedIdName;
static int savedLineNo;  /* ditto */
static TreeNode * savedTree; /* stores syntax tree for later return */

%}

%token ENDFILE ERROR 
%token INT CHAR FLOAT IF ELSE WHILE VOID RETURN BREAK CONTINUE
%token ID NUM FNUM SCHAR
%token PLUS SUB MUT DIV LT LE GT GE EQ NEQ AND OR NOT ASSIGN SEMI COMMA LP RP LSP RSP LFP RFP 

	
%union { TreeNode * ptree;
         Type type; 
       }
       
%type <ptree> program dec_list dec var_dec fun_dec fun_def params param_list param comp_stmt local_dec stmt_list stmt 
              exp_stmt sele_stmt iter_stmt return_stmt exp var simple_exp factor call args arg_list
              id_list 
%type <type> type_spec

%left	COMMA
%right	ASSIGN
%left OR    
%left AND
%left EQ NEQ
%left LT LE GT GE
%left PLUS SUB
%left MUT DIV
%left	LP RP LSP RSP LFP RFP

%right ELSE

%include {
    void yyerror(const char * message);
	TreeNode * parse(void);
}

%% /* Grammar for C_minus */

program     : dec_list
                 { savedTree = $1;} 
            ;
dec_list    : dec_list dec	
				{ TreeNode * t = $1;
				  if (t != NULL)
				  { while (t->sibling != NULL)
					t = t->sibling;
					t->sibling = $2;
					$$ = $1; }
				  else $$ = $2;
				}	                 
            | dec  
                { $$ = $1; }
            ;
dec         : var_dec	{ $$ = $1; }
            | fun_dec	{ $$ = $1; }
            | fun_def   { $$ = $1; }
            ;
id          : ID { savedIdName = copyString(tokenString); }
            ;
fid         : { savedFunName = savedIdName; }
            ;
var_dec     : type_spec id_list SEMI	
				{ if($1 == Void)
					  ;
					  // err
				  else
				    {	
					  $$ = newDecNode(VarK); 
					  $$ -> type = $1;
					  $$ -> child[0] = $2;
					}
				} 
            ;
id_list     : id_list COMMA var
                { 
                  TreeNode * t = $1;
				  if (t != NULL)
				  { while (t->sibling != NULL)
					t = t->sibling;
					t->sibling = $3;
					$$ = $1; }
				  else $$ = $3;
                }	//	i,str[5],j
            | var { $$ = $1; }
            | id_list COMMA id ASSIGN simple_exp
              { 
				  TreeNode * new_node = newStmtNode(AssignK);
				  TreeNode * t = $1;
				  if (t != NULL)
				  { while (t->sibling != NULL)
					t = t->sibling;
					t->sibling = new_node;
					$$ = $1; }
				  else $$ = new_node;
              }
            | id ASSIGN simple_exp
              { 
				 $$ = newStmtNode(AssignK);
				 $$ -> child[0] = newExpNode(IdK);
				 $$ -> child[0] -> attr.name = savedIdName;
				 $$ -> child[1] = $3;
              }
            ; 
type_spec   : INT { $$ = Integer; }         
            | FLOAT { $$ = Float; }         
            | CHAR { $$ = Char; }         
            | VOID { $$ = Void; }         
            ;
fun_def     : type_spec id fid LP params RP comp_stmt 
				{ $$ = newDecNode(FunDefK);
				  $$ -> attr.name = savedFunName;
				  $$ -> type = $1;
				  $$ -> child[0] = $5;
				  $$ -> child[1] = $7; 
				}
            | id fid LP params RP comp_stmt
				{ $$ = newDecNode(FunDefK);
				  $$ -> attr.name = savedFunName;
				  $$ -> type = Void;
				  $$ -> child[0] = $4;
				  $$ -> child[1] = $6; 
				}
            ;
fun_dec     : type_spec id fid LP params RP SEMI
				{ $$ = newDecNode(FunDecK);
				  $$ -> attr.name = savedFunName;
				  $$ -> type = $1;
				  $$ -> child[0] = $5;
				  $$ -> child[1] = NULL;
				}
			| id fid LP params RP SEMI
				{ $$ = newDecNode(FunDecK);
				  $$ -> attr.name = savedFunName;
				  $$ -> type = Void;
				  $$ -> child[0] = $4;
				  $$ -> child[1] = NULL;
				}
            ;             
params      : param_list
                { $$ = $1; }
            | 
				{ $$ = NULL; }
            ;         
param_list  : param_list COMMA param
            	{ TreeNode * t = $1;
				  if (t != NULL)
				  { while (t->sibling != NULL)
					t = t->sibling;
					t->sibling = $3;
					$$ = $1; }
				  else $$ = $3;
				}	                 
            | param
                { $$ = $1; }
            ;
param       : type_spec 
                { $$ = newDecNode(ParamK);
                  $$ -> type = $1;
                }            
			| type_spec id
                { $$ = newDecNode(ParamK);
                  $$ -> type = $1;
                  $$ -> attr.name = savedIdName;
                }            
            | type_spec id LSP RSP
                { $$ = newDecNode(ParamK);
                  $$ -> type = $1;
                  $$ -> attr.name = savedIdName;
                }            
            | type_spec id LSP simple_exp RSP
                { $$ = newDecNode(ParamK);
                  $$ -> type = $1;
                  $$ -> attr.name = savedIdName;
                  $$ -> child[0] = $4;
                }            
            ;
comp_stmt   : LFP local_dec stmt_list RFP
                { $$ = newDecNode(CompK);
                  $$ -> child[0] = $2;
                  $$ -> child[1] = $3;
                }            
            ;
local_dec   : local_dec var_dec            
            	{ TreeNode * t = $1;
				  if (t != NULL)
				  { while (t->sibling != NULL)
					t = t->sibling;
					t->sibling = $2;
					$$ = $1; }
				  else $$ = $2;
				}	                 
            | 
                { $$ = NULL; }
            ;
stmt_list   : stmt_list stmt            
            	{ TreeNode * t = $1;
				  if (t != NULL)
				  { while (t->sibling != NULL)
					t = t->sibling;
					t->sibling = $2;
					$$ = $1; }
				  else $$ = $2;
				}	                 
            | 
                { $$ = NULL; }
            ;
stmt        : exp_stmt	{ $$ = $1; }            
            | sele_stmt	{ $$ = $1; }
            | iter_stmt	{ $$ = $1; }
            | return_stmt	{ $$ = $1; }
            | comp_stmt { $$ = $1; }
            | CONTINUE SEMI { $$ = newStmtNode(ContinueK); }
            | BREAK SEMI    { $$ = newStmtNode(BreakK); }
            ;
exp_stmt    : exp SEMI
                { $$ = $1; }
            | SEMI
                { $$ = NULL; }            
            ;
sele_stmt   : IF LP exp RP stmt %prec ELSE
                { $$ = newStmtNode(IfK);
                  $$ -> child[0] = $3;
                  $$ -> child[1] = $5;
                }            
            | IF LP exp RP stmt ELSE stmt
                { $$ = newStmtNode(IfK);
                  $$ -> child[0] = $3;
                  $$ -> child[1] = $5;
				  $$ -> child[2] = $7;
                }
            ;
iter_stmt   : WHILE LP exp RP stmt
				{ $$ = newStmtNode(WhileK);
                  $$ -> child[0] = $3;
                  $$ -> child[1] = $5;
                }            
            ;    
return_stmt : RETURN SEMI
                { $$ = newStmtNode(ReturnK);
                  $$ -> child[0] = NULL;
                }
            | RETURN exp SEMI
                { $$ = newStmtNode(ReturnK);
                  $$ -> child[0] = $2;
                }
            ;                   
exp         : var ASSIGN exp
                { $$ = newStmtNode(AssignK);
                  $$ -> child[0] = $1;
                  $$ -> child[1] = $3;
                }
            | simple_exp
                { $$ = $1; }
            ;
var         : id
                { $$ = newExpNode(IdK);
                  $$ -> attr.name = savedIdName;
                }            
            | id LSP simple_exp RSP
				{ $$ = newExpNode(IdK);
				  $$ -> attr.name = savedIdName;
                  $$ -> child[0] = $3;
                }           
            ;
simple_exp : simple_exp OR simple_exp 
				{ $$ = newExpNode(OpK);
				  $$ -> child[0] = $1;
				  $$ -> child[1] = $3;
				  $$ -> attr.op = OR;
				}
			|simple_exp AND simple_exp 
				{ $$ = newExpNode(OpK);
				  $$ -> child[0] = $1;
				  $$ -> child[1] = $3;
				  $$ -> attr.op = AND;
				}
			|simple_exp LT simple_exp 
				{ $$ = newExpNode(OpK);
				  $$ -> child[0] = $1;
				  $$ -> child[1] = $3;
				  $$ -> attr.op = LT;
				  $$ -> type = Boolean;
				}
			|simple_exp LE simple_exp 
				{ $$ = newExpNode(OpK);
				  $$ -> child[0] = $1;
				  $$ -> child[1] = $3;
				  $$ -> attr.op = LE;
				  $$ -> type = Boolean;
				}
			|simple_exp GT simple_exp 
				{ $$ = newExpNode(OpK);
				  $$ -> child[0] = $1;
				  $$ -> child[1] = $3;
				  $$ -> attr.op = GT;
				  $$ -> type = Boolean;
				}
			|simple_exp GE simple_exp 
				{ $$ = newExpNode(OpK);
				  $$ -> child[0] = $1;
				  $$ -> child[1] = $3;
				  $$ -> attr.op = GE;
				  $$ -> type = Boolean;
				}
			|simple_exp EQ simple_exp 
				{ $$ = newExpNode(OpK);
				  $$ -> child[0] = $1;
				  $$ -> child[1] = $3;
				  $$ -> attr.op = EQ;
				  $$ -> type = Boolean;
				}
			|simple_exp NEQ simple_exp 
				{ $$ = newExpNode(OpK);
				  $$ -> child[0] = $1;
				  $$ -> child[1] = $3;
				  $$ -> attr.op = NEQ;
				  $$ -> type = Boolean;
				}
			|simple_exp PLUS simple_exp 
				{ $$ = newExpNode(OpK);
				  $$ -> child[0] = $1;
				  $$ -> child[1] = $3;
				  $$ -> attr.op = PLUS;
				}
			|simple_exp SUB simple_exp 
				{ $$ = newExpNode(OpK);
				  $$ -> child[0] = $1;
				  $$ -> child[1] = $3;
				  $$ -> attr.op = SUB;
				}
			|simple_exp MUT simple_exp 
				{ $$ = newExpNode(OpK);
				  $$ -> child[0] = $1;
				  $$ -> child[1] = $3;
				  $$ -> attr.op = MUT;
				}
			|simple_exp DIV simple_exp 
				{ $$ = newExpNode(OpK);
				  $$ -> child[0] = $1;
				  $$ -> child[1] = $3;
				  $$ -> attr.op = DIV;
				}
			| factor
			    { $$ = $1; }
			;

factor      : LP exp RP
                { $$ = $2; }			
            | var
                { $$ = $1; }			
			| call
			    { $$ = $1; }			
			| NUM
			    { $$ = newExpNode(NumK);
			      $$ -> type = Integer;
			      $$ -> attr.val.i = atoi(tokenString);
			    }
			| FNUM
			    { $$ = newExpNode(FnumK);
			      $$ -> type = Float;
			      $$ -> attr.val.f = atof(tokenString);
			    }
			| SCHAR
			    { $$ = newExpNode(CharK);
			      $$ -> type = Char;
			      $$ -> attr.val.i = *(tokenString + 1);
			    }
			| NOT factor
			    { $$ = $2;
			      $$ -> attr.op = NOT;
			    }
			;
call        : var LP args RP
                { $$ = newStmtNode(CallK);
				  $$ -> attr.name = $1 -> attr.name;
                  $$ -> child[0] = $3;
                }
            ;
arg_list    : arg_list COMMA exp            
				{ TreeNode * t = $1;
				  if (t != NULL)
				  { while (t->sibling != NULL)
					t = t->sibling;
					t->sibling = $3;
					$$ = $1; }
				  else $$ = $3;
				}	                 
            | exp
                { $$ = $1; }
			;
args        : arg_list
                { $$ = $1; }           
            | 
                { $$ = NULL; }
            ;
%%

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
