#include <stdio.h>
/*
#include "style.h"
#include "identifier.h"
#include "memory.h"
#include "compare.h"
*/

#define MAXLENGTH 204800

struct Error
{
       int code, row;
       struct Error *next;
};

int len=0, len2=0, flag=0;
char fileName[20], fileName2[20], c;
char sorce[MAXLENGTH], sorce2[MAXLENGTH];
struct Error *head;

int main()
{

    FILE *fin, *fout;

    printf("Enter the name of sorce file: ");
    scanf("%s", fileName);

    fin = fopen(fileName, "r");
    fout = fopen("result.txt", "w");

    while ((c = fgetc(fin)) != EOF) sorce[len++] = c;
    sorce[len] = '\0';
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
