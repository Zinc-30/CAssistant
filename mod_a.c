#include <stdio.h>

int main() {
	FILE *fout;
	fout = fopen ("a.txt", "w"); 
	fprintf (fout ,"1234567 8()[{}9 \r\t \t\t\t\t\t987654 3210 \r");
	return 0;
}
