#include "indent.h"
#include "char_oper.h"
#include <stdio.h>
//fix indentation

int indent(char* src) {

	//TODO: if no err parentheses match then perform action

/***************************************************
//TODO:delete spaces before \n
	{
		int i;
		for ( i = 0; src[i] != EOF; i++ ) {
			if ( src[i] == '\n' && src[i - 1] == ' ' ) {
					del_at_n(i - 1, src), i -= 2;
					if ( i < 0 ) break;
			}
		}
	if( src[len] != '\n') ins_c_at_n(len, src, '\n');
	if( src[0] != '\n') ins_c_at_n(0, src, '\n');
	}	
************************************************/


	//delete all spaces and /t at the beginning of a line
	{
		int i;
		for ( i = 0; src[i] != EOF; i++ ) {
			while ( src[i] == '\n' && 
					( src[i + 1] == ' ' ||
					src[i + 1] == '\t' ))
			{
					del_at_n(i + 1, src);
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
					}
					break;
				default: break;
			}
		}
	}

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
