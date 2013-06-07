#include <stdlib.h>
#include "globals.h"
#include "parse.h"
#include "symtab.h"

static int label_num = 0;
TreeNode * Fun;

void GenLabel(char lab[LABEL_SIZE])
{
	static int i=1;
	char temp[LABEL_SIZE];
	strcpy(lab,"L");
	_itoa(i,temp,10);
	strcat(lab,temp);
	i++;
}


void StackSegmentBegin(void)
{
	fprintf(inter_code,";*******************************************************\n");
	fprintf(inter_code,"Stack_seg\tsegment\n");
	fprintf(inter_code,"\tdw\t1024 dup(?)\n");
	fprintf(inter_code,"\ttos\tlabel\tword\n");
	fprintf(inter_code,"Stack_seg\tends\n");
	fprintf(inter_code,";*******************************************************\n");
	fprintf(inter_code,"Data_seg\tsegment\n");
}

void StackSegmentEnd(void)
{
	fprintf(inter_code,"Data_seg\tends\n");
	fprintf(inter_code,";*******************************************************\n");
}

void CodeSegmentBegin(void)
{
	fprintf(inter_code,"Code_seg\tsegment\n");
	fprintf(inter_code,"\tassume\tCS:Code_seg, DS:Data_seg, SS:Stack_seg\n");
}

void CodeSegmentEnd(void)
{
	fprintf(inter_code,"Code_seg\tends\n");
	fprintf(inter_code,"\tend\tstart\n");
	fprintf(inter_code,";*******************************************************\n");
}

void VarDec_ini(char *name, int value)//local variable declaration with initial value
{
	int os;
	ValEntry * pEntry = malloc(sizeof(ValEntry));
	
	if(pTable ->nestlevel == 0)
		fprintf(inter_code,"\t%s\tdw\t%d\n",name,value);
	else
	{
	Lookup_Var(pTable, pTable ->funEntry, name, pEntry);
	os = pEntry ->offset;
			
	fprintf(inter_code,"\tPUSH\tAX\n");//为该变量占个位置，迫使sp移动
	fprintf(inter_code,"\tPUSH\tAX\n");//store value
	fprintf(inter_code,"\tMOV\tAX , %d\n",value);
	fprintf(inter_code,"\tPUSH\tBP\n");//calculate variable address
	fprintf(inter_code,"\tADD\tBP , %d\n",os);
	fprintf(inter_code,"\tMOV\tSS:[BP] , AX\n",os);//store value
	fprintf(inter_code,"\tPOP\tBP\n");
	fprintf(inter_code,"\tPOP\tAX\n");
	}
}

void VarDec(char *name)//local variable declaration without initial value
{
	if(pTable ->nestlevel == 0)
		fprintf(inter_code,"\t%s\tdw\t?\n",name);
	else
		fprintf(inter_code,"\tPUSH\tAX\n");//为该变量占个位置，迫使sp移动
}

void ArrDec(char *name, int entitynum)
{
	int i;
	if(pTable ->nestlevel == 0)
		fprintf(inter_code,"\t%s\tdw\t%d dup(?)\n",name,entitynum);//to data file
	else
		for(i = 0; i < entitynum; i ++)
			fprintf(inter_code,"\tPUSH\tAX\n");//为该变量占个位置，迫使sp移动
}

void ent(char *name, int para, int retvalue)
{
	fprintf(inter_code,"\t%s\tproc\tfar\n",name);//to code file
	if(!strcmp("main",name)){//main function
		fprintf(inter_code,"start:\n");
		fprintf(inter_code,"\tMOV\tAX , Stack_seg\n");
		fprintf(inter_code,"\tMOV\tSS , AX\n");
		fprintf(inter_code,"\tMOV\tSP , offset tos\n\n");
		fprintf(inter_code,"\tPUSH\tDS\n");
		fprintf(inter_code,"\tSUB\tAX , AX\n");
		fprintf(inter_code,"\tPUSH\tAX\n\n");
		fprintf(inter_code,"\tMOV\tAX , Data_seg\n");
		fprintf(inter_code,"\tMOV\tDS , AX\n");
	}
	fprintf(inter_code,"\tPUSH\tAX\n");
	fprintf(inter_code,"\tPUSH\tBX\n");
	fprintf(inter_code,"\tPUSH\tCX\n");
	fprintf(inter_code,"\tPUSH\tDX\n");	
	fprintf(inter_code,"\tPUSH\tBP\n");
	fprintf(inter_code,"\tMOV\tBP , SP\n");//begin to accept local variables
}


//--------------------------------------------------
void adi(void)
{
	fprintf(inter_code,"\tPOP\tBX\n");
	fprintf(inter_code,"\tPOP\tAX\n");
	fprintf(inter_code,"\tADD\tAX , BX\n");
	fprintf(inter_code,"\tPUSH\tAX\n");
}

void andi(void)
{
	fprintf(inter_code,"\tPOP\tBX\n");
	fprintf(inter_code,"\tPOP\tAX\n");
	fprintf(inter_code,"\tAND\tAX , BX\n");
	fprintf(inter_code,"\tPUSH\tAX\n");
}

void compound_enter(void)
{
}

void compound_exit(void)
{
pTable = pTable->parent;
}

void cup(char *name, int paranum)	//function call end, 'int' is the number of actual parameters
{
	fprintf(inter_code,"\tCALL\t%s\n",name);
}

void divi(void)
{
	fprintf(inter_code,"\tPOP\tBX\n");
	fprintf(inter_code,"\tPOP\tAX\n");
	fprintf(inter_code,"\tPUSH\tDX\n");
	fprintf(inter_code,"\tIDIV\tBX\n");
	fprintf(inter_code,"\tPOP\tDX\n");
	fprintf(inter_code,"\tPUSH\tAX\n");
}

void equi(void)
{
	fprintf(inter_code,"\tPOP\tBX\n");
	fprintf(inter_code,"\tPOP\tAX\n");
	fprintf(inter_code,"\tCMP\tAX , BX\n");
	fprintf(inter_code,"\tJE\tLabel%d\n",label_num);
	fprintf(inter_code,"\tMOV\tAX , 0\n");
	fprintf(inter_code,"\tPUSH\tAX\n");
	fprintf(inter_code,"\tJMP\tLabel%d\n",label_num + 1);
	fprintf(inter_code,"Label%d:",label_num);
	fprintf(inter_code,"\tMOV\tAX , 1\n");
	fprintf(inter_code,"\tPUSH\tAX\n");
	fprintf(inter_code,"Label%d:",label_num + 1);
	label_num += 2;
}

void leave(char *name)
{
	fprintf(inter_code,"\t%s\tendp\n",name);
}

void fjp(char*label)
{
	fprintf(inter_code,"\tPOP\tAX\n");
	fprintf(inter_code,"\tCMP\tAX , 0\n");
	fprintf(inter_code,"\tJE\t%s\n",label);
}

void gorei(void)
{
	fprintf(inter_code,"\tPOP\tBX\n");
	fprintf(inter_code,"\tPOP\tAX\n");
	fprintf(inter_code,"\tCMP\tAX , BX\n");
	fprintf(inter_code,"\tJGE\tLabel%d\n",label_num);
	fprintf(inter_code,"\tMOV\tAX , 0\n");
	fprintf(inter_code,"\tPUSH\tAX\n");
	fprintf(inter_code,"\tJMP\tLabel%d\n",label_num+1);
	fprintf(inter_code,"Label%d:",label_num);
	fprintf(inter_code,"\tMOV\tAX , 1\n");
	fprintf(inter_code,"\tPUSH\tAX\n");
	fprintf(inter_code,"Label%d:",label_num+1);
	label_num += 2;
}

void greater(void)
{
	fprintf(inter_code,"\tPOP\tBX\n");
	fprintf(inter_code,"\tPOP\tAX\n");
	fprintf(inter_code,"\tCMP\tAX , BX\n");
	fprintf(inter_code,"\tJG\tLabel%d\n",label_num);
	fprintf(inter_code,"\tMOV\tAX , 0\n");
	fprintf(inter_code,"\tPUSH\tAX\n");
	fprintf(inter_code,"\tJMP\tLabel%d\n",label_num+1);
	fprintf(inter_code,"Label%d:",label_num);
	fprintf(inter_code,"\tMOV\tAX , 1\n");
	fprintf(inter_code,"\tPUSH\tAX\n");
	fprintf(inter_code,"Label%d:",label_num+1);
	label_num += 2;
}

void ind(char *name)
{
	if(pTable ->nestlevel == 0){
		fprintf(inter_code,"\tPOP\tBX\n");
		fprintf(inter_code,"\tPUSH\tDS:[BX]\n");
	}
	else{
		fprintf(inter_code,"\tPOP\tBX\n");
		fprintf(inter_code,"\tPUSH\tBP\n");
		fprintf(inter_code,"\tMOV\tBP , BX\n");
		fprintf(inter_code,"\tPUSH\tSS:[BP]\n");
		fprintf(inter_code,"\tPOP\tBP\n");
	}
}

void ixa_elem_size(void)
{
	fprintf(inter_code,"\tPOP\tAX\n");
	fprintf(inter_code,"\tPOP\tBX\n");
	fprintf(inter_code,"\tSHL\tAX , %d\n",EXP_VARIABLE_LENGTH);//AX * VARIABLE_LENGTH
	fprintf(inter_code,"\tADD\tAX , BX\n");
	fprintf(inter_code,"\tPUSH\tAX\n");
}

void lab(char *label)
{
	fprintf(inter_code,"%s :\n",label);
}

void ldl(char value)
{
	fprintf(inter_code,"\tMOV\tAX , %d\n",(int)value);
	fprintf(inter_code,"\tPUSH\tAX\n");
}

void lda(char *name)//load address
{
	int addr = 0;
	ValEntry * pEntry = malloc(sizeof(ValEntry));
	if(pTable ->nestlevel == 0){
		fprintf(inter_code,"\tLEA\tAX , %s\n",name);
		fprintf(inter_code,"\tPUSH\tAX\n");
	}
	else{
		Lookup_Var(pTable, pTable ->funEntry, name, pEntry);
		addr = pEntry->offset;
		fprintf(inter_code,"\tMOV\tAX , BP\n");
		fprintf(inter_code,"\tADD\tAX , %d\n",addr);
		fprintf(inter_code,"\tPUSH\tAX\n");
	}
}

void ldc(int value)//load constant
{
	fprintf(inter_code,"\tMOV\tAX , %d\n",value);
	fprintf(inter_code,"\tPUSH\tAX\n");
}

void less(void)
{
	fprintf(inter_code,"\tPOP\tBX\n");
	fprintf(inter_code,"\tPOP\tAX\n");
	fprintf(inter_code,"\tCMP\tAX , BX\n");
	fprintf(inter_code,"\tJL\tLabel%d\n",label_num);
	fprintf(inter_code,"\tMOV\tAX , 0\n");
	fprintf(inter_code,"\tPUSH\tAX\n");
	fprintf(inter_code,"\tJMP\tLabel%d\n",label_num+1);
	fprintf(inter_code,"Label%d:",label_num);
	fprintf(inter_code,"\tMOV\tAX , 1\n");
	fprintf(inter_code,"\tPUSH\tAX\n");
	fprintf(inter_code,"Label%d:",label_num+1);
	label_num += 2;
}

void lod(char *name)
{
	int addr = 0;
	ValEntry * pEntry = malloc(sizeof(ValEntry));
	Lookup_Var(pTable, pTable ->funEntry, name, pEntry);
	if(pTable ->nestlevel == 0){
		fprintf(inter_code,"\tMOV\tAX , %s\n",name);
		fprintf(inter_code,"\tPUSH\tAX\n");
	}
	else{
		Lookup_Var(pTable,pTable ->funEntry, name,pEntry);
		addr = pEntry ->offset;
		fprintf(inter_code,"\tPUSH\tBP\n");
		fprintf(inter_code,"\tADD\tBP , %d\n",addr);
		fprintf(inter_code,"\tMOV\tAX , SS:[BP]\n");
		fprintf(inter_code,"\tPOP\tBP\n");
		fprintf(inter_code,"\tPUSH\tAX\n");
	}
}

void lorei(void)
{
	fprintf(inter_code,"\tPOP\tBX\n");
	fprintf(inter_code,"\tPOP\tAX\n");
	fprintf(inter_code,"\tCMP\tAX , BX\n");
	fprintf(inter_code,"\tJLE\tLabel%d\n",label_num);
	fprintf(inter_code,"\tMOV\tAX , 0\n");
	fprintf(inter_code,"\tPUSH\tAX\n");
	fprintf(inter_code,"\tJMP\tLabel%d\n",label_num+1);
	fprintf(inter_code,"Label%d:",label_num);
	fprintf(inter_code,"\tMOV\tAX , 1\n");
	fprintf(inter_code,"\tPUSH\tAX\n");
	fprintf(inter_code,"Label%d:",label_num+1);
	label_num += 2;
}

void mst(char *name)
{
}

void multi(void)
{
	fprintf(inter_code,"\tPOP\tBX\n");
	fprintf(inter_code,"\tPOP\tAX\n");
	fprintf(inter_code,"\tPUSH\tDX\n");
	fprintf(inter_code,"\tIMUL\tBX\n");
	fprintf(inter_code,"\tPOP\tDX\n");
	fprintf(inter_code,"\tPUSH\tAX\n");
}

void neqi(void)
{
	fprintf(inter_code,"\tPOP\tBX\n");
	fprintf(inter_code,"\tPOP\tAX\n");
	fprintf(inter_code,"\tCMP\tAX , BX\n");
	fprintf(inter_code,"\tJNE\tLabel%d\n",label_num);
	fprintf(inter_code,"\tMOV\tAX , 0\n");
	fprintf(inter_code,"\tPUSH\tAX\n");
	fprintf(inter_code,"\tJMP\tLabel%d\n",label_num+1);
	fprintf(inter_code,"Label%d:",label_num);
	fprintf(inter_code,"\tMOV\tAX , 1\n");
	fprintf(inter_code,"\tPUSH\tAX\n");
	fprintf(inter_code,"Label%d:",label_num+1);
	label_num += 2;
}

void ori(void)
{
	fprintf(inter_code,"\tPOP\tBX\n");
	fprintf(inter_code,"\tPOP\tAX\n");
	fprintf(inter_code,"\tOR\tAX , BX\n");
	fprintf(inter_code,"\tPUSH\tAX\n");
}

void pop(void)
{
	fprintf(inter_code,"\tPOP\tAX\n");
}

void ret(int r,char * name)
{
	int addr = 0;
	FunEntry * pEntry = malloc(sizeof(FunEntry));
	if(r){//if the function has a return value
		fprintf(inter_code,"\tPOP\tAX\n");//get the return value from the top of the stack
		pEntry = Lookup_Fun(name);
		addr = pEntry ->ret_val;
		fprintf(inter_code,"\tPUSH\tBP\n");
		fprintf(inter_code,"\tADD\tBP , %d\n",addr);
		fprintf(inter_code,"\tMOV\tSS:[BP] , AX\n");
		fprintf(inter_code,"\tPOP\tBP\n");
	}
	fprintf(inter_code,"\tMOV\tSP , BP\n");//release local parameters
	fprintf(inter_code,"\tPOP\tBP\n");//pop bp
	fprintf(inter_code,"\tPOP\tDX\n");
	fprintf(inter_code,"\tPOP\tCX\n");
	fprintf(inter_code,"\tPOP\tBX\n");
	fprintf(inter_code,"\tPOP\tAX\n");

	fprintf(inter_code,"\tRET\n");		
}

void stn(char *name)
{
	if(pTable ->nestlevel == 0){
		fprintf(inter_code,"\tPOP\tBX\n");//get the value from the top of the stack
		fprintf(inter_code,"\tPOP\tAX\n");//get the actual address at STACK segment
		fprintf(inter_code,"\tMOV\tDS:[AX] , BX\n");//load value
		fprintf(inter_code,"\tPUSH\tBX\n");
	}
	else{
		fprintf(inter_code,"\tPOP\tBX\n");//get the value from the top of the stack
		fprintf(inter_code,"\tPOP\tAX\n");//get the actual address at STACK segment
		fprintf(inter_code,"\tPUSH\tBP\n");
		fprintf(inter_code,"\tMOV\tBP , AX\n");
		fprintf(inter_code,"\tMOV\tSS:[BP] , BX\n");//load value
		fprintf(inter_code,"\tPOP\tBP\n");
		fprintf(inter_code,"\tPUSH\tBX\n");
	}
}

void subi(void)
{
	fprintf(inter_code,"\tPOP\tDX\n");
	fprintf(inter_code,"\tPOP\tCX\n");
	fprintf(inter_code,"\tSUB\tCX , DX\n");
	fprintf(inter_code,"\tPUSH\tCX\n");
}

void ujp(char *label)
{
	fprintf(inter_code,"\tJMP\t%s\n",label);
}

void write(void)
{
	fprintf(inter_code,"\tWRITE\tproc\tfar\n");//to code file
	fprintf(inter_code,"\tPUSH\tAX\n");
	fprintf(inter_code,"\tPUSH\tBX\n");
	fprintf(inter_code,"\tPUSH\tCX\n");
	fprintf(inter_code,"\tPUSH\tDX\n");	
	fprintf(inter_code,"\tPUSH\tBP\n");
	fprintf(inter_code,"\tMOV\tBP , SP\n");//begin to accept local variables
	fprintf(inter_code,"\tMOV\tBX , [BP + 14]\n");
	fprintf(inter_code,"\tMOV\tCX , 10000\n");
	fprintf(inter_code,"\tCMP\tBX , CX\n");
	fprintf(inter_code,"\tJL\tw_label1\n");
	fprintf(inter_code,"\tCALL\tWRITE_SUB\n");
	fprintf(inter_code,"w_label1:\n");
	fprintf(inter_code,"\tMOV\tCX , 1000\n");
	fprintf(inter_code,"\tCMP\tBX , CX\n");
	fprintf(inter_code,"\tJL\tw_label2\n");
	fprintf(inter_code,"\tCALL\tWRITE_SUB\n");
	fprintf(inter_code,"w_label2:\n");
	fprintf(inter_code,"\tMOV\tCX , 100\n");
	fprintf(inter_code,"\tCMP\tBX , CX\n");
	fprintf(inter_code,"\tJL\tw_label3\n");
	fprintf(inter_code,"\tCALL\tWRITE_SUB\n");
	fprintf(inter_code,"w_label3:\n");
	fprintf(inter_code,"\tMOV\tCX , 10\n");
	fprintf(inter_code,"\tCMP\tBX , CX\n");
	fprintf(inter_code,"\tJL\tw_label4\n");
	fprintf(inter_code,"\tCALL\tWRITE_SUB\n");
	fprintf(inter_code,"w_label4:\n");
	fprintf(inter_code,"\tMOV\tCX , 1\n");
	fprintf(inter_code,"\tCALL\tWRITE_SUB\n");
	fprintf(inter_code,"\tMOV\tSP , BP\n");//release local parameters
	fprintf(inter_code,"\tPOP\tBP\n");//pop bp
	fprintf(inter_code,"\tPOP\tDX\n");
	fprintf(inter_code,"\tPOP\tCX\n");
	fprintf(inter_code,"\tPOP\tBX\n");
	fprintf(inter_code,"\tPOP\tAX\n");
	fprintf(inter_code,"\tRET\n");		
	fprintf(inter_code,"\tWRITE\tendp\n\n");

	fprintf(inter_code,"\tWRITE_SUB\tproc\tnear\n");
	fprintf(inter_code,"\tMOV\tAX , BX\n");
	fprintf(inter_code,"\tMOV\tDX , 0\n");
	fprintf(inter_code,"\tDIV\tCX\n");
	fprintf(inter_code,"\tMOV\tBX , DX\n");
	fprintf(inter_code,"\tMOV\tDL , AL\n");
	fprintf(inter_code,"\tADD\tDL , '0'\n");
	fprintf(inter_code,"\tMOV\tAH , 02h\n");
	fprintf(inter_code,"\tINT\t21h\n");
	fprintf(inter_code,"\tRET\n");
	fprintf(inter_code,"\tWRITE_SUB\tendp\n\n");
}

void CodeGen_TreeNode(TreeNode * node)
{
	TreeNode * temp;
	int count;
	while (node != NULL) 
	{
	switch(node ->nodekind){
	case Dec:
		switch(node-> kind.dec){
		case FunDecK:
			//	more code to be filled
			break;
		case FunDefK:
			Fun = node;
			count = 0;
			temp = node-> child[0];
			while(temp)
			{
				count ++;
				temp = temp-> sibling;
			}
			ent(node ->attr.name, count, (node -> type != Void)? TRUE:FALSE);
			temp = node -> child[0];	// Param
			if(temp)
				CodeGen_TreeNode(temp);
			CodeGen_TreeNode(node ->child[1]);	// comp_dec
			if(node -> type == Void)
				ret(FALSE,node ->attr.name);
			else
				ret(TRUE,node ->attr.name);
			leave(node ->attr.name);
			break;
		case VarK:
			temp = node -> child[0];
			if(node ->kind.exp == NumK)
			while(temp)
			{
				if(temp -> nodekind == Stmt)	// AssignK ini
						VarDec_ini(temp ->child[0] ->attr.name, temp->child[1]->attr.val.i);
				else
				{
					if(temp ->child[0] == NULL)
						VarDec(temp ->attr.name);	
					else
						ArrDec(temp ->attr.name, temp ->child[0] ->attr.val.i);
				}
				temp = temp ->sibling;
			}
			break;
		case CompK:
			pTable = node ->attr.table;
			temp = node ->child[0];
			if(temp)	// Dec
				CodeGen_TreeNode(temp);
			temp = node ->child[1];
			if(temp)	//stmt
				CodeGen_TreeNode(temp);
			compound_exit();
			break;
		case ParamK:
			break;
		default:
			break;
		}
		break;
	case Stmt:
		switch(node ->kind.stmt){
		case IfK:
			temp = node ->child[0];
			GenLabel(pTable ->lab1);
			GenLabel(pTable ->lab2);
			if(temp ->kind.exp == NumK)	// optimize
			{
				if(temp -> attr.val.i == 0)
					ujp(pTable ->lab1);
			}
			else 
			{
				CodeGen_TreeNode(temp);
				fjp(pTable ->lab1);
			}
			pTable = node ->child[1] ->attr.table;
			if(node ->child[1])
				CodeGen_TreeNode(node ->child[1]);
			
			if(node ->child[2]) 
				ujp(pTable ->lab2);
			lab(pTable ->lab1);
			if(node ->child[2]) 
			{
				pTable = node ->child[2] ->attr.table;
				CodeGen_TreeNode(node ->child[2]);
				lab(pTable ->lab2);
			}
			break;
		case WhileK:
			GenLabel(pTable ->lab1);
			GenLabel(pTable ->lab2);
			lab(pTable ->lab1);
			temp = node ->child[0];
			if(temp ->kind.exp == NumK)	// optimize
			{
				if(temp ->attr.val.i == 0)
					ujp(pTable ->lab2);
			}
			else
			{
				CodeGen_TreeNode(temp);
				fjp(pTable ->lab2);
			}
			if(node -> child[1])
				CodeGen_TreeNode(node -> child[1]);
			ujp(pTable ->lab1);
			lab(pTable ->lab2);
			break;
		case CallK:
			mst(node -> attr.name);
			temp = node ->child[0];
			CodeGen_TreeNode(temp);
			cup(node ->attr.name, count);
			while(temp)		// Param
			{
				pop();
				temp = temp -> sibling;
			}
			
			if(node ->call_stmt == 1)
				pop();
			break;
		case ReturnK:
			temp = node -> child[0];
			if(temp)
			{
				CodeGen_TreeNode(temp);
				ret(TRUE,pTable ->funEntry ->name);
			}
			else ret(FALSE,pTable ->funEntry ->name);
			break;
		case BreakK:
			ujp(pTable ->parent ->lab2);
			break;
        case ContinueK:
			ujp(pTable ->parent ->lab1);			
			break;
		case AssignK:
			temp = node -> child[0];
			lda(temp ->attr.name);
			if(temp -> child[0])  //Arr
			{
				CodeGen_TreeNode(temp -> child[0]);
				ixa_elem_size();
			}
			CodeGen_TreeNode(node -> child[1]);
			stn(node -> child[0] ->attr.name);
			pop();
			break;
		default:
			break;
		}
		break;
	case Exp:
		switch(node -> kind.exp){
		case OpK:
			if(node -> child[0])
				CodeGen_TreeNode(node -> child[0]);
			if(node -> child[1])
				CodeGen_TreeNode(node -> child[1]);
			switch(node -> attr.op) {
			case PLUS:	adi();		break;
			case SUB:	subi();		break;
			case MUT:	multi();	break;
			case DIV:	divi();		break;
			case EQ:	equi();		break;
			case NEQ:	neqi();		break;
			case LE:	lorei();	break;
			case GE:	gorei();	break;
			case LT:	less();		break;
			case GT:	greater();	break;
			case AND:	andi();		break;
			case OR:	ori();		break;
			default:	yyerror("Unknown Operator!");
						break;
			}
			break;
		case FnumK:
			//  more code to be filled
			break;
		case NumK:
			ldc(node -> attr.val.i);
			break;
		case CharK:
//			ldc(node -> attr.val.i);
			break;
		case IdK:
			lod(node -> attr.name);
			break;
		case NotK:
			break;
		default:
			break;
		}
		break;
	default:
		break;
	}
    node = node->sibling;
	}
}