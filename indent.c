#include "indent.h"
#include "char_oper.h"
#include <stdio.h>
//fix indentation

int indent(char* src) {

	//TODO: if no err parentheses match then perform action

/***************************************************/
//delete spaces before \n
	{
		int i;
		for ( i = 0; src[i] != EOF; i++ ) {
			if ( src[i] == '\n' && src[i - 1] == ' ' ) {
					del_at_n(i - 1, src), i -= 2;
					if ( i < 0 ) break;
			}
		}
	if( src[i] != '\n') ins_c_at_n(i, src, '\n');
	if( src[0] != '\n') ins_c_at_n(0, src, '\n');
	}	
/************************************************/

	int unmod_count, mod_count;    
	unmod_count = mod_count = 0;
	//delete all spaces and /t at the beginning of a line
	{
		int i;
		for ( i = 0; src[i] != EOF; i++ ) {
			while ( src[i] == '\n' && 
					(
					src[i + 1] == ' ' ||
					src[i + 1] == '\t'||
					src[i + 1] == '\n'/*del surplus \n*/
					)
				)
			{
					del_at_n(i + 1, src);
					unmod_count++;
			}
		}
	}
	
	//insert tab
	{
		int indent_level = 0;
		int i = 0; int k = 0; 
		for ( i = 0; src[i] != EOF; i++ ) {
			switch (src[i]) {
				case '{': indent_level++; break;
				case '}': indent_level--; 
					if (src[i - 1] == '\t') {
						del_at_n(--i, src);
					}
					break;
				case '\n' : 
					k = indent_level;
					while (k--) {
						ins_c_at_n(i + 1, src, '\t');
						mod_count++;
					}
					break;
				default: break;
			}
		}
	}
	float rate = 0;
	if (mod_count > unmod_count)
	rate = 1.0 * unmod_count /(float) mod_count;
	else
	rate = 1.0 * mod_count / (float)unmod_count;
	printf("You've got %.2f/1.00 for your coding style\n", rate);

	return 0;
}

/***************************************************
//discarded implemention
	{
		//find first{
		int scope_in = 0;
		char indt[] = {'\0'};
		for ( i = 0; src[i] != EOF; i++ ) {
			if ( src[i] == '{' ) {
				scope_in = 1;
	 			break;	
			}
		}
		//???? if ( scope == 0 )
		if ( src[i - 1] != '\n') {
			ins_c_at_n( i++, src, '\n');}
		strcat(indt, usrsty.first_parnth_offset);

		//insert indt at i and mov i forward
		{
			int iter;
			for ( iter = 0; indt[iter] != '\0'; iter++) {
				ins_c_at_n( i++, src, indt[iter]);
			}
		}
		strcat(indt, usrsty.statement_offset);
		
		if ( src[i + 1] != '\n') {
			ins_c_at_n( i + 1, src, '\n');}
			
		//K&R 2 OT
		{
			int iter;
			key_flag
			for ( iter = i; src[iter] != '\0'; iter++) {
				switch ( src[iter] ){
					case 'i' : 
						if (++iter <= len && src[iter] == 'f') {
							if ( ++iter <= len ) {
								int left, right;
								left = right = 0;
								switch ( src[iter] ) {
									case '\n': src[iter] = ' '; 
									case '(' : //if found
									case ' ' : break;
										ins_c_at_n( iter++, src, ' ');
										left++;
										while (left - right) {
											if (src[iter] == '(') {
												left++;
											}
											if (src[iter] == ')' ) {
												right++;
											}
											iter++;
										}
										//iter point to char after ) now

										//)^M
										//{}
										//) {}
										//){}
										if ( usrsty.one_line_substat == '{'){

											if ( src[iter] != '{') {
												iter ++;
												if (src[iter] != '{' ){										{
													ins_c_at_n(iter, src, '{');
													while (src[iter] != ';' ) {
														iter++;
													}
													iter++;
													ins_c_at_n(iter, src, '}');
													ins_c_at_n(iter, src, '\n');
												}
											}
										}
										
									default  : break;
								}
							}
						}
					case 'e' :
					case 'd' :
					case 'w' :
					case 'f' :
					case '{' :
					case '}' :
					case '\n':

					default :
				}
			}
		}
		//if else else if
		//while do switch
		//for
	}
	//something to refer
	//      indntp usrsty
	//      indntp KetR 
	//      typedef struct indent_type {
	//            
	//            char first-parnth-offset
	//            char statement_offset
	//          char one_line_substat '{'
	//
	//
	//      } indntp;
	//* adhere to former line
	//0 gowith former line indent space
	//+ add one \t
	//- sub one \t
***************************************************/

/*
????

??/r /n
	??/r /n ????? /t

????,?????
	1, ????
		{} [] () "" '' <>????
	 / * * / pair
	2, ????
	3, ????
		1, ????????
		2, ??????
			1, ??? a*b==c
			2, ??? a * b == c
			3, ;?????
			4, indentation ???
		3, ????
		++ -- * % + - << >> ^ \ | || & && = == 
		! * (?????????*?????????,
			?????????????????????,
			???????*??????????????
			?????,?????????)


The position of braces is less important, although people hold passionate beliefs. We have chosen one of several popular styles. Pick a style that suits you, then use it consistently.
-----The C programming language: Kernighan and Ritchie

K&R style
int main (int argc, char *argv[]) 
{
	if (argc == 2){
		func1();
	} else 
		func2();
	func0();
	return 0;
}

OTBS style
int main (int argc, char *argv[]) 
{
	if (argc == 2){
		func1();
	} else {
		func2();
	}
	func0();
	return 0;
}

Stroustrup style
int main (int argc, char *argv[]) 
{
	if (argc == 2){
		func1();
	}
	else {
		func2();
	}
	func0();
	return 0;
}

Allman style (BSD style)
int main (int argc, char *argv[]) 
{
	if (argc == 2)
	{
		func1();
	}
	else
	{
		func2();
	}
	func0();
	return 0;
}

Whitesmiths style
int main (int argc, char *argv[]) 
	{
	if (argc == 2)
		{
		func1();
		}
	else
		{
		func2();
		}
	func0();
	return 0;
	}

GNU style
int main (int argc, char *argv[]) 
{
  if (argc == 2)
    {
      func1();
	}
  else
    {
      func2();
    }
  func0();
  return 0;
}



for (int i=0; i < x; i++)

(setq realwhitesmith '(
      (c-basic-offset . 3)
      (c-comment-only-line-offset . 0)
      (c-offsets-alist

      (c . 0)
      (comment-intro . 0)

      (statement-block-intro . 0)
      (statement-cont . +)

      (substatement . +)
      (substatement-open . +)

      (block-open . +)
      (block-close . 0)

      (defun-open . +)
      (defun-close . 0)
      (defun-block-intro . 0)
      (func-decl-cont . +)

      (class-open . +)
      (class-close . +)
      (inclass . +)
      (access-label . -)
      (inline-open . +)
      (inline-close . 0)

      (extern-lang-open . 0)
      (extern-lang-close . 0)
      (inextern-lang . 0)

      (statement-case-open +)

      (namespace-open . 0)
      (namespace-close . 0)
      (innamespace . 0)

      (label . 0)
      )
))


*/
