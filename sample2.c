#include <string.h>

typedef int * intPtr;
typedef char charArr[100];
typedef notype ok;

int main()
{
	intPtr a;
	int b, len = 100;
	charArr source;
	
	a = &b;
	
	for (int i=0; i<len; ++i) printf("%c", source[i]);
	
	return 0;
}
