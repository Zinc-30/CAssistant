#include <stdio.h>
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

int len=0, len2=0, flag=0;
char fileName[20], fileName2[20], c;
char source[MAXLENGTH], source2[MAXLENGTH];
struct Error *head;

struct lineending{
	int is_CR, is_LF, is_CRLF;
}; // define line ending pattern
//TODO static ?

lineending LE = {0, 0, 0};

//insert exectly at a[iterator]
int insert_char(char *a, int iterator, char c){
	int i;
	for (i = 0; i < iterator; a++);

}

//TODO /r before EOF



int main()
{

    FILE *fin, *fout;

    printf("Enter the name of sorce file: ");
    scanf("%s", fileName);

    fin = fopen(fileName, "r");
    fout = fopen("result.txt", "w");
	FILE *temp = fin;

	//find out which line endind this file is
	do {
		c = fgetc(fin);
		if (c == '\r') {
			if ((c = fgetc(fin)) == '\n') {
				LE.is_CRLF = 1;printf("CRLF filefomat, "
								"will be changed to LF\n");break;
			}
			else{
				LE.is_CR = 1;printf("CR filefomat, "
								"will be changed to LF\n");break;
			}
		}
		if (c == '\n') LE.is_LF = 1;printf("LF filefoamt, "
						"nothing will be changed\n");break;
	}while(c != EOF);
	fin = temp;
    while ((c = fgetc(fin)) != EOF) source[len++] = c;
    source[len] = EOF; //shoude be EOF

	//TODO
	if (LE.is_LF)
			;
	if (LE.is_CR)
			;
	if (LE.is_CRLF)
			;

	int k = 0;
	for (k = 0; k <= len; k++){
		printf("%d %c ", source[k], source[k]);
	}




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
