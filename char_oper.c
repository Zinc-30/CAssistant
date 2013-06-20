#include "char_oper.h"
#include <stdio.h>

//del char at n
void del_at_n(int n, char *a){
	if ( a[n] == EOF ) return;
	/* for security concern
	int length = 0;
	for (length = 1; a[length] != EOF; length++){
	}
	if (n > length) assert();
	*/
	while (a[n] != EOF) {
		a[n] = a[n + 1], n++;
	}
	
	a[n] = '\0';
	return;
}

//insert char at a[n]
void ins_c_at_n(int n, char *a, char c){
	int ins_posi = n;
	
	int ileng = 0;
	for (ileng = 0; a[ileng] != EOF; ileng++) {
	}
	n = ileng;
	
	a[n + 2] = '\0';
	while ( n != ins_posi ) {
		a[n + 1] = a[n], n--;
	}
	a[n + 1] = a[n];
	a[n] = c;

}
