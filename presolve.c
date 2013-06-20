#include "include.h"
#include <stdio.h>
#include <string.h>

void presolve(char *src){
	int i;
	char c;
    
	i=0;
	while (i<strlen(src)){
		if (src[i]=='\\')
		{
			if (src[i+1]=='\n') removechar(src,i,2);
			else removechar(src,i,1);
		}else i++;
	} 

	
}
