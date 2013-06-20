#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "file_io.h"
#define MAXLENGTH 204800 //2^31 = 2,147,483,648

//basic_func headers
#include "del_comment.h"
#include "parentheses.h"
#include "indent.h"

//DEPRECATED
/*
#include "style.h"
#include "identifier.h"
#include "memory.h"
#include "compare.h"
*/

/**************************************/
	//global variables
	struct Error
	{
       int code, row;
       struct Error *next;
	};


	struct Error *head;
/**************************************/

int menu_1(char *src, char* filname);
int menu_2(char *src, char* src2);

int main()
{

	int len = 0, len2 = 0, flag = 0;
	char fileName[20], fileName2[20];
	char src[MAXLENGTH], src2[MAXLENGTH];
	int choice;
	
	while(1) {
		printf(
		"Welcome to C Assistant system\n"
		"Please choose an action:\n"
		"[1]Single file operation:\n    indent, parentheses matching check, delete comments, etc\n"
		"[2]Double file operation:\n    compare codes, etc\n"
		"[9]Browse files\n"
		"[0]Exit\n"
		);
		scanf("%d", &choice);
		choice += '0';
		switch (choice) {
			case '1':
				printf("Enter the name of source file:");
	    		scanf("%s", fileName);
	    		parse_file2char(fileName, src);
	    		menu_1(src, fileName); break;
	    	case '2':
	    		printf("Enter the name of first source file:");
	    		scanf("%s", fileName);
	    		printf("Enter the name of another source file:");
	    		scanf("%s", fileName2);
	    		menu_2(src, src2); break;
	    	case '9': system("dir"); break;
	    	case '0':
				return 0;
			default :
				printf("Wrong input\n");
		}
	}
    return 0;
}

//[1] menu
int menu_1(char *src, char* filename) {
	while(1) {
		int index = 0;
		printf(
			"Choose an action:\n"
			"[0]Browse files\n"
			"[1]Indent fix\n"
			"[2]Parentheses matching check\n"
			"[3]Delete comments\n"
			/*"[4]Coding style assesment\n"*/
			"[8]Save and go upper menu\n"
			"[9]Go upper menu without saving\n"
		);
		scanf ("%d", &index);
		index += '0';
		char temp[20];
		switch (index) {
			case '0': system("dir"); break;
			case '1': indent(src); break;
			case '2': parentheses(src); break;
			case '3': del_comment(src); break;
			case '4': //assessment(); break;//TODO
			case '8': 
				strcpy(temp, filename);
				strcpy(filename, "mod_");
				strcat(filename, temp);
				parse_char2file(filename, src);
			case '9': return 0;
			default : printf("Wrong input\n");
		}
	}
	return 0;
}

//[2] menu
int menu_2(char *src, char *src2) {
	char index = 0;
	printf(
		"Choose an action:\n"
		"[0]\n"
		"[1]\n"
		"[2]\n"
		"[3]\n"
		"[4]\n"
		
		"[9]Upper menu\n"
	);
	scanf ("%d", &index);
	switch (index) {
		case '0': ; break;
		case '1': ; break;
		case '2': ; break;
		case '3': ; break;
		case '4': ; break;
		
		case '9': return 0;
	}
}


//DEPRECATED
	/*temp = fin; //save fin 

	//read file into char array
    while ((c = fgetc(fin)) != EOF) src[len++] = c;
    src[len++] = EOF, src[len] = '\0';//len - 1 shoude be EOF

	#ifdef DEBUG
	{
		int k = 0;
		for (k = 0; k <= len; k++){
			printf("%d:%c ",src[k], src[k]);
		}
		printf("\n");
	}
	puts(src);
	#endif
	*/
	
	//using discounts to give a score for code style
	//like .99 * .98 * .87 then you have a score
	//
	//
	/*
    if (flag) compare();
    else
    {
        style();
        identifier();
        memory();
    }
*/
