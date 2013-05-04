#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "char_oper.h"
/*
#include "style.h"
#include "identifier.h"
#include "memory.h"
#include "compare.h"
*/

#define MAXLENGTH 204800 //2^31 = 2,147,483,648



struct Error
{
       int code, row;
       struct Error *next;
};

int len = 0, len2 = 0, flag = 0;
char fileName[20] = {"a.txt"};
char fileName2[20], c;
char src[MAXLENGTH], src2[MAXLENGTH];
struct Error *head;

/**************************************/
	//disabled with block 1
	struct lineending{
		int is_CR, is_LF, is_CRLF;
	}; 
	// define line ending pattern
	//TODO static ?

	struct lineending LE = {0, 0, 0};

	//TODO /r before EOF
/***************************************/

int main()
{

    FILE *fin, *fout;
	FILE *temp;

    printf("Enter the name of sorce file: ");
    //scanf("%s", fileName);

    fin = fopen(fileName, "r");
    fout = fopen("result.txt", "w");



	temp = fin; //save fin 

	//read file into char array
    while ((c = fgetc(fin)) != EOF) src[len++] = c;
    src[len++] = EOF, src[len] = '\0';//len - 1 shoude be EOF

	#ifndef RELEASE
	{
		int k = 0;
		for (k = 0; k <= len; k++){
			printf("%d:%c ", *( src + k ), src[k]);
		}
		printf("\n");
	}
	#endif
/****************************************************/
//convert line endings
	//block 1
	//find out which line endind this file is
	fin = fopen(fileName, "r");
	//TODO change this to universal file manipulation method
	c = fgetc(fin);
	do {
		c = fgetc(fin);
		if ( c == '\r' ) {
			if ((c = fgetc(fin)) == '\n' ) {
				LE.is_CRLF = 1;printf("CRLF filefomat, "
								"will be changed to LF\n");break;
			}
			else{
				LE.is_CR = 1;printf("CR filefomat, "
								"will be changed to LF\n");break;
			}
		}
		if (c == '\n') {
			LE.is_LF = 1;printf("LF filefoamt, "
						"nothing will be changed\n");break;
		}
	}while(c != EOF);


	{	
	//convert line endings to LF
		int i = 0;
		if (LE.is_LF)
				;
		if (LE.is_CR){
			for ( i = 0; src[i] != EOF; i++ ) {
				if ( src[i] == '\r' ) {
					src[i] = '\n';
				}
			}
		}
			
		if (LE.is_CRLF)
		for ( i = 0; src[i] != EOF; i++ ) {
			if ( src[i] == '\r' ) {
				del_at_n(i, src);
			}
		}
	}
/***************************************************/


	//delete spaces before \r
	{
		int i;
		for ( i = 0; src[i] != EOF; i++ ) {
			if ( src[i] == '\n' && src[i - 1] == ' ' ) {
					del_at_n(i - 1, src);
			}
		}
	}
	if( src[len] != '\n') ins_c_at_n(len, src, '\n');
	if( src[0] != '\n') ins_c_at_n(0, src, '\n');

/***************************************************/
//parenthesis 
	{
		int left, right;
		int noerr = 1;

		int i, k;
		char parnth[] = {'[', ']', '{', '}', '(', ')', '<', '>'};
		for ( k = 0; k < 8; k += 2){
			left = right = 0;
			for ( i = 0; src[i] != EOF; i++ ) {
				if ( src[i] == parnth[k]) {
					left++;
				}
				else if ( src[i] == parnth[k + 1]) {
					right++;
				}
			}
			if (left != right){
				noerr = 0, 
				printf("Parentheses:%c%c not match.\n"
					, parnth[k], parnth[k + 1]);
			}
		}
		if (noerr == 1){
			printf("%s\n", "Parentheses all match.\n");
		}

		//TODO cat err to struct error

	}




/***************************************************/


//TODO del comment func


/***************************************************/
//indent fix
	//TODO if no err parentheses match then perform action

	//delete all spaces and /t at the beginning of a line
	{
		int i;
		for ( i = 0; src[i] != EOF; i++ ) {
			while ( src[i] == '\n' && 
				( src[i + 1] == ' ' || src[i + 1] == '\t' ))
			{
					del_at_n(i + 1, src);
			}
		}
	}
	//indent space
	char indt[] = {''};
	

/***************************************************
//discarded implemention
	{
		//find first{
		int scope_in = 0;
		char indt[] = {'\0'};
		for ( i = 0; src[i] != EOF; i++ ) {
			if ( src[i] == '{' ) {
				scope_in = 1;
	 			break;	
			}
		}
		//TODO if ( scope == 0 )
		if ( src[i - 1] != '\n') {
			ins_c_at_n( i++, src, '\n');}
		strcat(indt, usrsty.first_parnth_offset);

		//insert indt at i and mov i forward
		{
			int iter;
			for ( iter = 0; indt[iter] != '\0'; iter++) {
				ins_c_at_n( i++, src, indt[iter]);
			}
		}
		strcat(indt, usrsty.statement_offset);
		
		if ( src[i + 1] != '\n') {
			ins_c_at_n( i + 1, src, '\n');}
			
		//K&R 2 OT
		{
			int iter;
			key_flag
			for ( iter = i; src[iter] != '\0'; iter++) {
				switch ( src[iter] ){
					case 'i' : 
						if (++iter <= len && src[iter] == 'f') {
							if ( ++iter <= len ) {
								int left, right;
								left = right = 0;
								switch ( src[iter] ) {
									case '\n': src[iter] = ' '; 
									case '(' : //if found
									case ' ' : break;
										ins_c_at_n( iter++, src, ' ');
										left++;
										while (left - right) {
											if (src[iter] == '(') {
												left++;
											}
											if (src[iter] == ')' ) {
												right++;
											}
											iter++;
										}
										//iter point to char after ) now

										//)^M
										//{}
										//) {}
										//){}
										if ( usrsty.one_line_substat == '{'){

											if ( src[iter] != '{') {
												iter ++;
												if (src[iter] != '{' ){										{
													ins_c_at_n(iter, src, '{');
													while (src[iter] != ';' ) {
														iter++;
													}
													iter++;
													ins_c_at_n(iter, src, '}');
													ins_c_at_n(iter, src, '\n');
												}
											}
										}
										
									default  : break;
								}
							}
						}
					case 'e' :
					case 'd' :
					case 'w' :
					case 'f' :
					case '{' :
					case '}' :
					case '\n':

					default :
				}
			}
		}
		//if else else if
		//while do switch
		//for
	}
	//something to refer
	//      indntp usrsty
	//      indntp KetR 
	//      typedef struct indent_type {
	//            
	//            char first-parnth-offset
	//            char statement_offset
	//          char one_line_substat '{'
	//
	//
	//      } indntp;
	//* adhere to former line
	//0 gowith former line indent space
	//+ add one \t
	//- sub one \t
***************************************************/


/***************************************************/



	#ifndef RELEASE
	{
		int k = 0;
		for (k = 0; k <= len; k++){
			printf("%d:%c ",src[k], src[k]);
		}
		printf("\n");
	}

	#endif
	//system("ls");
	//system("dir");



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

    fclose(fin);
    fclose(fout);
    return 0;
}
