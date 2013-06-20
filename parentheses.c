#include "parentheses.h"

#include <stdio.h>

//parenthesis matching test
int parentheses(const char* src) {
	int left, right;
		int noerr = 1;

		int i, k;
		char parnth[] = {'[', ']', '{', '}', '(', ')'};
		for ( k = 0; k < 6; k += 2){
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

		//TODO: cat err to struct error	
}
