#include "globals.h"
#include "util.h"
#include "scan.h"
#include "parse.h"
#include "symtab.h"
#include "analyze.h"
#include "CodeGen.h"

#define NO_ANALYZE FALSE

/* allocate global variables */
int lineno = 0;
FILE * source;
FILE * listing;
FILE * inter_code;

/* allocate and set tracing flags */
int TraceScan = TRUE;
int TraceParse = TRUE;
int TraceAnalyze = TRUE;

int Error = FALSE;

int main(int argc, char * argv[])
{
	TreeNode * syntaxTree;
	char cfile[20], codefile[20];	/* sourse code file name */

	if(argc != 2)
	{
		fprintf(stderr,"Usage: %s <filename>\n",argv[0]);
		exit(1);
	}
	strcpy(codefile, argv[1]);
	if (strchr(codefile, '.') != NULL) {
		int len = strcspn(codefile, ".");
		strncpy(cfile, codefile, len);
		cfile[len] = '\0';
	}
	else {
		strcpy(cfile, codefile);
		strcat(codefile, ".c");
	}
	source = fopen(codefile,"r");
	if (source==NULL)
	{ 
		printf("File %s not found!\n", codefile);
		exit(1);
	}
	strcpy(codefile, cfile);
	strcat(codefile, ".lst"); 
	listing = fopen(codefile,"w"); 
	if (listing == NULL)
	{ 
		printf("Unable to open %s\n", codefile);
		exit(1);
	}

	/* compilation begins here */
	syntaxTree = parse();
	if (TraceParse) {
		fprintf(listing,"\nSyntax tree:\n");
		printTree(syntaxTree);
	}
#if !NO_ANALYZE
	if (!Error)
	{
		fprintf(listing,"\nBuilding Symbol Table...\n");
		buildSymtab(syntaxTree);
		fprintf(listing,"\nChecking Types...\n");
		typeCheck(syntaxTree);
		fprintf(listing,"\nType Checking Finished\n");
	}
#if !NO_CODE
	if (!Error)
	{ 
		strcpy(codefile, cfile);
		strcat(codefile, ".asm"); 
		inter_code = fopen(codefile,"w");
		if (inter_code == NULL)
		{ 
			printf("Unable to open %s\n", codefile);
			exit(1);
		}
		pTable = GlobalTable;
		StackSegmentBegin();
		StackSegmentEnd();
		CodeSegmentBegin();
		write();
		CodeGen_TreeNode(syntaxTree);
		CodeSegmentEnd();
		fclose(inter_code);
	}
#endif
#endif

	fclose(source);
	fclose(listing);
	return 0;
}
