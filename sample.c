#include <stdio.h>
#include <string.h>

int main()
{
	FILE *fin;
	char c, source[2048000];
	long len=0;
	int no;
	char noo[10];
	
	fin = fopen("sample.c", "r");
	while ((c=fgetc(fin)) != EOF)
	{
		if (c=='\n') continue;
		source[len++] = c;
	}
	
	for (int i=0, notuse; i<len; ++i) printf("%c", source[i]);
	
	return 0;
}
