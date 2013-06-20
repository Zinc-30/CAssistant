#include "del_comment.h"
#include "char_oper.h"
#include <stdio.h>

//TODO: check /* */ pairs
int del_comment(char* src) {
	int i, k;
	for ( i = 0; src[i] - EOF; i++) {
		if ( src[i] == '/' && src[i + 1] == '/' ) {
			k = i;
			while ( src[k] != '\n' ) {
				del_at_n (k, src);
			}
			if ( src[i - 1] == '\n') del_at_n (i - 1, src); 
		}
		if ( src[i] == '/' && src[i + 1] == '*' ) {
			while ( !( src[i] == '*' &&
						src[i + 1] == '/') ) {
				del_at_n (i, src);		
			}
			del_at_n (i, src);		
			del_at_n (i, src);		
		}
	}
	return 0;	
}
