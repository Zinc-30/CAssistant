#ifndef _CODEGEN_H_
#define _CODEGEN_H_

void GenLabel(char lab[LABEL_SIZE]);
void StackSegmentBegin(void);
void StackSegmentEnd(void);
void CodeSegmentBegin(void);
void CodeSegmentEnd(void);
void VarDec_ini(char *name, int value);	//local variable declaration with initial value
void VarDec(char *name); //local variable declaration without initial valu
void ArrDec(char *name, int entitynum);
void ent(char *name, int para, int retvalue);
void adi(void);
void andi(void);
void compound_enter(void);
void compound_exit(void);
void cup(char *name, int paranum);	//function call end, paranem is the number of actual parameters
void divi(void);
void equi(void);
void leave(char *name);
void fjp(char*label);
void gorei(void);
void greater(void);
void ind(char *name);
void ixa_elem_size(void);
void lab(char *label);
void ldl(char value);
void lda(char *name);	//load address
void ldc(int value);	//load constant
void less(void);
void lod(char *name);
void lorei(void);
void mst(char *name);
void multi(void);
void neqi(void);
void ori(void);
void pop(void);
void ret(int r);
void stn(char *name);
void subi(void);
void ujp(char *label);
void write(void);


void CodeGen_TreeNode(TreeNode * node);

extern vari_offset;
extern para_offset;
extern label_num;

#endif