#include <char_oper.h>

void del_at_n(int n, char* a){
	if ( a[n] == EOF ) return;
	int i = 0;
	/* for security soncern
	int length = 0;
	for (length = 1; a[length] != EOF; length++){
	}
	if (n > length) assert();
	*/
	while (1) {
		a[n] = a[n + 1], n++;
		if ( a[n] == EOF ){
				a[n + 1] = '\0';
				return;
		}
	}

}
