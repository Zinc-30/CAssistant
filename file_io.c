#include <stdio.h>


#include "file_io.h"
#include "char_oper.h"

struct lineending{
	int is_CR, is_LF, is_CRLF;
}; 
// define line ending pattern

static struct lineending LE = {0, 0, 0};

int parse_file2char(const char* filename, char* src) {	
    FILE *fin;	
	fin = fopen(filename, "r");
	int i;
	for (i = 0; src[i] - EOF; i++) {
		src[i] = fgetc(fin);
	}
	fclose(fin);
	
//convert line endings
	//find out which line ending this file is
	for (i = 0; src[i] - EOF; i++) {
		if ( src[i] == '\r' ) {//DONE: /r before EOF
			if ( src[i + 1] == '\n' ) {
				LE.is_CRLF = 1;
				printf(
				"CRLF filefomat, "
				"will be changed to LF\n"); break;
			}
			else{
				LE.is_CR = 1;
				printf(
				"CR filefomat, "
				"will be changed to LF\n"); break;
			}
		}
		if ( src[i] == '\n' && (i == 0 || src[i - 1] != '\r') ) {
			LE.is_LF = 1;
			printf("LF filefoamt, "
			"nothing will be changed\n"); break;
		}
	}
	//convert line endings to LF
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

    return 0;
}

int parse_char2file(const char* filename, char* src) {
	FILE *fout;
	fout = fopen(filename, "w");
	int i;
	for (i = 0; src[i] - EOF; i++) {
		fputc(src[i], fout);
	}
//	fputc(0, fout);
	fclose(fout);
	return 0;
}
