#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define TYPE_TOTAL	7
#define PRE_TOTAL	7
#define KEY_TOTAL	11
#define MAXVAR		500
#define MAXBAN		50
#define MAXDEF		100
#define MAXSTP		100
#define MAXNAME		50 

const char *TYPE_TABLE[7] = {	"char", "double", "float", 
								"int", "long", "short", 
								"void"
	 						},
			*PRE_TABLE[7] = {	"auto", "const", "extern", 
								"register", "signed", "static", 
								"unsigned"
							},
			*KEY_TABLE[11] = {	"break", "case", "continue", 
								"default", "do", "else", 
								"if", "return", "sizeof", 
								"switch", "while"
							};
			//*SEP_TABLE[] = {	" ", "\t", "\n", "," ,";"}

struct Var
{
	char name[MAXNAME];
	int type, pre, ptr, arr, fun, used;
} var[MAXVAR], tpDef[MAXDEF];
struct StructTp
{
	char name[MAXNAME];
	int t_v;
	struct Var var[MAXVAR];
} sTp[MAXSTP];

int line=1;
int gt_v=0, t_n=0, t_td=0, t_st=0;
int no[MAXBAN];

void workKey(char *, int *, struct Var *, int *);
void ifUsed(int, int, int);
int findFun(int);

int isVar(struct Var *var, char *key, int i)
{
	while (i+1)
	{
		if (strcmp(var[i].name, key) == 0) break;
		--i;
	}
	return i;
}

int isNum(char *key)
{
	int i;
	if (key[0] == '0' && key[1] == 'x')
	{
		i=2;
		while (key[i] != '\0')
		{
			if (!(	isdigit(key[i]) || 
					key[i]>='a' && key[i]<='f' || 
					key[i]>='A' && key[i]<='F')) return 0;
			++i;
		}
	}
	else for (i=0; key[i]!='\0'; ++i) if (!isdigit(key[i])) return 0;
	return 1;
}

int isPre(char *key)
{
	int i;
	for (i = PRE_TOTAL-1; i+1; --i) if (strcmp(PRE_TABLE[i], key) == 0) break;
	return i;
}

int isType(char *key)
{
	int i;
	for (i = TYPE_TOTAL-1; i+1; --i) if (strcmp(TYPE_TABLE[i], key) == 0) break;
	return i;
}

int isDefType(char *key, int i)
{
	while (i+1)
	{
		if (strcmp(tpDef[i].name, key) == 0) break;
		--i;
	}
	return i;
}

int isSTp(char *key, int i)
{
	while (i+1)
	{
		if (strcmp(sTp[i].name, key) == 0) break;
		--i;
	}
	return i;
}

int isKey(char *key)
{
	int i;
	for (i = KEY_TOTAL-1; i+1; --i) if (strcmp(KEY_TABLE[i], key) == 0) break;
	return i;
}

int getKey(char *a, char *key, int i)
{
	int j=0;
	while (!(isalnum(a[i]) || a[i]=='_'))
	{
		if (a[i] == '\n') ++line;
		if (a[i] == '{')
		{
			no[t_n++] = gt_v;
			++i;
			continue;
		}
		if (a[i] == '}')
		{
			ifUsed(gt_v-1, no[t_n-1], findFun(gt_v-1));
			gt_v = no[--t_n];
			++i;
			continue;
		}
		if (a[i] == '\'' || a[i] == '"')
		{
			j = i+1;
			while (a[i] != a[j] || a[j-1] == '\\')
			{
				if (a[j] == '\n') ++line;
				++j;
			}
			i = j;
		}
		++i;
	}
	j = 0;
	while (isalnum(a[i]) || a[i]=='_') key[j++] = a[i++];
	key[j] = '\0';
	return i;
}

void loadTpDef(char *a, int *i,struct Var *lVar, int *_t_v, int tmp)
{
	char key[MAXNAME];
	int t_v=*_t_v, j ,k;
	while (1)
	{
		lVar[t_v].arr = tpDef[tmp].arr;
		lVar[t_v].pre = tpDef[tmp].pre;
		lVar[t_v].ptr = tpDef[tmp].ptr;
		lVar[t_v].type = tpDef[tmp].type;
		*i = getKey(a, key, *i);
		strcpy(lVar[t_v++].name, key);
		while (isspace(a[*i])) if (a[(*i)++] == '\n') ++line;
		if (a[*i] == '(')
		if (!(isdigit(a[*i + 1]) || a[*i + 1] == '"' || a[*i + 1] == '\''))
		{
			lVar[t_v++].fun = 1;
			j = *i;
			while (a[*i]!='{' && a[*i]!=';') ++(*i);
			if (a[*i] == '{')
			{
				a[j] = '{';
				if (a[*i - 1] == '\n') ++line;
				a[*i - 1] = ';';
				a[*i] = ' ';
				for (k=j+1; k<*i; ++k)
				{
					if (a[k] == ',') a[k] = ';';
					if (a[k] == ')') a[k] = ' ';
				}
				*i = j;
			}
			else --t_v;
			*_t_v = t_v;
			return;
		}
		if (a[*i] == ';') break;
	}
	*_t_v = t_v;
}

void loadVar(char *a, int *i, struct Var *var, int *_t_v, int tmp)
{
	int t_v=*_t_v;
	int j=0, k=0;
	char key[MAXNAME];
	
	var[t_v].type = tmp;
	while (isspace(a[*i])) if (a[(*i)++]=='\n') ++line;
	if (a[*i] == '*') var[t_v].ptr = 1;
	*i = getKey(a, key ,*i);
	strcpy(var[t_v].name, key);
	while (isspace(a[*i])) ++(*i);
	if (a[*i] == '(')
	if (!(isdigit(a[*i + 1]) || a[*i + 1] == '"' || a[*i + 1] == '\''))
	{
		var[t_v++].fun = 1;
		j = *i;
		while (a[*i]!='{' && a[*i]!=';') ++(*i);
		if (a[*i] == '{')
		{
			a[j] = '{';
			if (a[*i - 1] == '\n') ++line;
			a[*i - 1] = ';';
			a[*i] = ' ';
			for (k=j+1; k<*i; ++k)
			{
				if (a[k] == ',') a[k] = ';';
				if (a[k] == ')') a[k] = ' ';
			}
			*i = j;
		}
		//else --t_v;
		*_t_v = t_v;
		return;
	}
	if (a[*i] == '[') var[t_v].arr = 1;
	++t_v;
	while (a[*i] != ';')
	{
		while (a[*i] != ',' && a[*i] != ';' && a[*i] != '}')
		{
			if (a[*i] == '\n') ++line;
			++(*i);
		}
		if (a[*i] == ';' || a[*i] == '}') break;
		while (isspace(a[++(*i)])) if (a[*i]=='\n') ++line;
		if (a[*i] == '*') var[t_v].ptr = 1;
		*i = getKey(a, key, *i);
		var[t_v].pre = var[t_v - 1].pre;
		var[t_v].type = var[t_v -1].type;
		if (a[*i] == '[') var[t_v].arr = 1;
		strcpy(var[t_v].name, key);
		++t_v;
	}
	*_t_v = t_v;
}

void loadSTp(char *a, int *_i, struct StructTp *s, struct Var *lVar, int *_t_v, int flag)
{
	int j=0, i=*_i, tmp, t_v=*_t_v;
	char key[MAXNAME];
	while (!(a[i] == '{' || isalpha(a[i]) || a[i] == '_'))
	{
		if (a[i] == '\n') ++line;
		++i;
	}
	if (a[i] == '{') strcpy(s[t_st].name, "__temp");
	else
	{
		j = i;
		while (a[j] != '{' && a[j] != ';') ++j;
		i = getKey(a, key, i);
		if (a[j] == ';')
		{
			if ((tmp = isSTp(key, t_st-1)) != -1)
			{
				loadVar(a, &i, lVar, &t_v, TYPE_TOTAL + tmp);
				*_i = i;
				*_t_v = t_v;
				return;
			}
			else
			{
				printf("Line %d: \"struct %s\" is not defined.\n", line, key);
				//adderr();
				*_i = i;
				*_t_v = t_v;
				return;
			}
		}
		strcpy(s[t_st].name, key);
	}
	while (a[i] != '}')
	{
		workKey(a, &i, s[t_st].var, &s[t_st].t_v);
		while (isspace(a[i]) || a[i] == ';')
		{
			if (a[i] == '\n') ++line;
			++i;
		}
	}
	if (!flag)
	{
		j = ++i;
		while (a[j]!='_' && a[j]!=';' && !isalpha(a[j])) ++j;
		if (a[j]!=';') loadVar(a, &i, lVar, &t_v, TYPE_TOTAL + t_st);
	}
	else
	{
		++i;
		tpDef[t_td].type = TYPE_TOTAL + t_st;
		while (!(isalnum(a[i]) || a[i]=='_')) i++;
		while (isspace(a[--i]));
		if (a[i] == '*') tpDef[t_td].ptr = 1;
		++i;
		i = getKey(a, key, i);
		strcpy(tpDef[t_td].name, key);
		while (a[i] != ';')
		{
			if (a[i] == '[')
			{
				tpDef[t_td].arr = 1;
				break;		
			}
			++i;
		}
		++t_td;
	}
	++t_st;
	*_i = i;
	*_t_v = t_v;
}

int workS(char *a, int i, int tmp)
{
	int tmp_tp, p, pp, tmp_, j;
	char key[MAXNAME];
	
	tmp_tp = tmp - TYPE_TOTAL;
	if (a[i] == '.' || a[i] == '-' && a[i+1] == '>')
	{
			i = getKey(a, key, i);
			if ((pp=isVar(sTp[tmp_tp].var, key, sTp[tmp_tp].t_v-1)) == -1)
			{
				printf("Line %d: \"%s\" has not been defined. \n", line, key);
				//addErr();
				return i;
			}
			if (sTp[tmp_tp].var[pp].type < TYPE_TOTAL) return i;
			return workS(a, i, sTp[tmp_tp].var[pp].type);
	}
	else 
		if (a[i] == '[')
		{
			p = i+1;
			tmp_ = 1;
			while (tmp_)
			{
				++i;
				if (a[i] == '[') ++tmp_;
				if (a[i] == ']') --tmp_;
			}
			++i;
			if (a[i] == '.' || a[i] == '-' && a[i+1] == '>')
			{
				j = i;
				i = getKey(a, key, i);
				if ((pp=isVar(sTp[tmp_tp].var, key, sTp[tmp_tp].t_v-1)) == -1)
				{
					printf("Line %d: \"%s\" has not been defined. \n", line, key);
					//addErr();
					return p;
				}
				if (sTp[tmp_tp].var[pp].type < TYPE_TOTAL)
				{
					while (j<i) a[j++] = ' ';
					return p;
				}
				else
				{
					workS(a, i, sTp[tmp_tp].var[pp].type);
					return p;
				}
			}
			else
			{
				printf("Line %d: synax error. \n", line);
				//addErr();
				return p;
			}
		}
/*		else
		{
			tmp_ = 1;
			while (tmp_)
			{
				++i;
				if (a[i] == '(') ++tmp_;
				if (a[i] == ')') --tmp_;
			}
			if (a[i] == '.' || a[i] == '-' && a[i+1] == '>')
			{
				j = i;
				i = getKey(a, key, i);
				if ((pp=isVar(sTp[tmp_tp].var, key, sTp[tmp_tp].t_v-1)) == -1)
				{
					printf("Line %d: \"%s\" has not been defined. \n", line, key);
					//addErr();
					return p;
				}
				if (sTp[tmp_tp].var[pp].type < TYPE_TOTAL)
				{
					while (j<i) a[j++] = ' ';
					return p;
				}
				else
				{
					workS(a, i, sTp[tmp_tp].var[pp].type);
					return p;
				}
			}
			else
			{
				printf("Line %d: synax error. \n", line);
				//addErr();
				return p;
			}
		}
*/
return i;
}

void workKey(char *a, int *_i, struct Var *lVar, int *_t_v)
{
	int i=*_i, j=0, tmp=0, p=0;
	int t_v = *_t_v;
	char key[MAXNAME];
	
	i = getKey(a, key, i);
/*	if (key[0] == '{' || key[0] == '}')
	{
		*_i = i;
		return;
	}
*/
	if (strcmp(key, "for") == 0)
	{
		var[gt_v].fun = 1;
		strcpy(var[gt_v].name, "for");
		var[gt_v].type = 6;
		++gt_v;
		no[t_n++] = gt_v;
		j = i;
		while (a[i] != ';')	++i;
		++i;
		while (a[i] != ';')	++i;
		++i;
		while (a[i] != ';' && a[i] != '{') ++i;
		if (a[i] == ';') a[i] = '}';
		else a[i] = ' ';
		i = j+1;
		*_i = i;
		return;
	}
	if (strcmp(key, "struct") == 0)
	{
		loadSTp(a, &i, sTp, lVar, &t_v, 0);
		++i;
		*_i = i;
		*_t_v = t_v;
		return;
	}
	if (strcmp(key, "typedef") == 0)
	{
		i = getKey(a, key, i);
		if (strcmp(key, "struct") == 0)
		{
			loadSTp(a, &i, sTp, lVar, &t_v, 1);
			++i;
			*_i = i;
			*_t_v = t_v;
			return;
		}
		if ((tpDef[t_td].pre=isPre(key)) != -1)
		{
			j = i;
			i = getKey(a, key, i);
			if ((tpDef[t_td].type=isType(key)) == -1)
			{
				i = j;
				tpDef[t_td].type = 3;
				while (!(isalnum(a[i]) || a[i]=='_')) i++;
				while (isspace(a[--i]));
				if (a[i] == '*') tpDef[t_td].ptr = 1;
				++i;
				i = getKey(a, key, i);
				strcpy(tpDef[t_td].name, key);
				while (a[i] != ';')
				{
					if (a[i] == '[')
					{
						tpDef[t_td].arr = 1;
						break;		
					}
					++i;
				}
				++t_td;
				++i;
				*_i = i;
				*_t_v = t_v;
				return;
			}
		}
		if ((tpDef[t_td].type=isType(key)) == -1)
		{
			printf("Line %d: Type \"%s\" is unkown.\n", line, key);
			//addErr();
		}
		else
		{
			while (!(isalnum(a[i]) || a[i]=='_')) i++;
			while (isspace(a[--i]));
			if (a[i] == '*') tpDef[t_td].ptr = 1;
			++i;
			i = getKey(a, key, i);
			strcpy(tpDef[t_td].name, key);
			while (a[i] != ';')
			{
				if (a[i] == '[')
				{
					tpDef[t_td].arr = 1;
					break;		
				}
				++i;
			}
			++t_td;
			++i;
			*_i = i;
			*_t_v = t_v;
			return;
		}
	}
	if ((tmp = isPre(key)) != -1)
	{
		var[t_v].pre = tmp;
		j = i;
		i = getKey(a, key, i);
		if ((tmp = isType(key)) != -1)
		{
			loadVar(a, &i, lVar, &t_v, tmp);
			*_i = i;
			*_t_v = t_v;
			return;
		}
		i = j;
		loadVar(a, &i, lVar, &t_v, 3);
		*_i = i;
		*_t_v = t_v;
		return;
	}
	if ((tmp = isDefType(key, t_td-1)) != -1)
	{
		loadTpDef(a, &i, lVar, &t_v, tmp);
		++i;
		*_i = i;
		*_t_v = t_v;
		return;
	}
	if ((tmp = isType(key)) != -1)
	{
		loadVar(a, &i, lVar, &t_v, tmp);
		*_i = i;
		*_t_v = t_v;
		return;
	}
	if (isKey(key) != -1 || isdigit(key[0]) && isNum(key))
	{
		++i;
		*_i = i;
		*_t_v = t_v;
		return;
	}
	if ((tmp = isVar(var, key, gt_v-1)) == -1)
	{
		printf("Line %d: \"%s\" has not been defined. \n", line, key);
		//addErr();
		*_i = i;
		*_t_v = t_v;
		return;
	}
	var[tmp].used = 1;
	if (var[tmp].type >= TYPE_TOTAL)
	{
		i = workS(a, i, var[tmp].type);
	}
	*_i = i;
	*_t_v = t_v;
}


int findFun(int i)
{
	while (i+1 && !var[i].fun) --i;
	return i;
}

void ifUsed(int from, int end, int p)
{
	char fun[MAXNAME];
	if (p == -1) strcpy(fun, "Global");
	else
	{
		strcpy(fun, var[p].name);
		strcat(fun, "()");
	}
	while (from >= end)
	{
		if (!var[from].fun && !var[from].used)
		{
			printf("In %s: \"%s\" is not used.\n", fun, var[from].name);
			//addErr();
		}
		--from;
	}
}

int examine(char *a, int len)
{
	int i, j, k, tmp;

	for (i=0; i<MAXVAR; ++i) var[i].arr = var[i].fun = var[i].ptr = var[i].used = 0, 
							var[i].type = var[i].pre = -1;
	
	i = 0;
	while (i<len)
	{
		//printf("%d	%c%c%c%c\n", i, a[i], a[i+1], a[i+2], a[i+3]);
		//printf("i=%d\na[i]=%c\nt_n=%d", i, a[i], t_n);
		//getchar();
		
		if (a[i] == '\n')
		{
			++line;
			++i;
			continue;
		}
		if (a[i] == '#')
		{
			while (a[++i] != '\n');
			continue;
		}
		if (a[i] == '{')
		{
			no[t_n++] = gt_v;
			++i;
			continue;
		}
		if (a[i] == '}')
		{
			ifUsed(gt_v-1, no[t_n-1], tmp=findFun(gt_v-1));
			gt_v = no[--t_n];
			if (tmp == gt_v-1) --gt_v;
			++i;
			continue;
		}
		if (a[i] == '(' || a[i] == ')' || a[i] == ';' ||
			a[i] == '[' || a[i] == ']' || isspace(a[i]))
		{
			++i;
			continue;
		}
		
		workKey(a, &i, var, &gt_v);
	}
	
	return 0;
}

/*
int main()
{
	FILE *fin;
	char c, source[2048000];
	long i, len=0;
	
	fin = fopen("sample3.c", "r");
	while ((c=fgetc(fin)) != EOF)
	{
		if (c=='\t') c=' ';
		source[len++] = c;
	}
	//for (i=0; i<len; ++i) printf("%c", source[i]);
	
	examine(source, len);
	
	return 0;
}
*/
