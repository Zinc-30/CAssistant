// AsmCodeGenerator.cpp : implementation file
//

#include "stdafx.h"
#include "cminus.h"

#include "AsmCodeGenerator.h"

/*  *    CAsmCodeGenerator
    *    Construction & destruction
  *	* *
   ***   Programer: Â½Ïþ´º
    *    Date:		2004.05.25             */

CAsmCodeGenerator::CAsmCodeGenerator( CString& str )
{
	m_pAnalyzer = new CAnalyzer( str );
	label		= 1;
}

CAsmCodeGenerator::~CAsmCodeGenerator()
{
}

/*  *    CAsmCodeGenerator
    *    Main routine, generating ASM Code
  *	* *
   ***   Programer: Â½Ïþ´º
    *    Date:		2004.05.26             */

void CAsmCodeGenerator::GenerateAsmCode( LPCTSTR lpszPathName )
{
	m_pAnalyzer->TraceTypeCheck();
	if( bErrFlag ) {
		OutputPhaseMsg( "\r\nerrors occur, stop generating code!" );
		return;
	}
	ASSERT( m_pAnalyzer->m_pProgram != NULL );

	// create file
	CFileException e;
	if( !m_file.Open( lpszPathName, CFile::modeCreate | CFile::modeReadWrite, &e ) ) {
		OutputErrMsg( "failed to create file for code generation: %s", lpszPathName );
		return;
	}

	// generating p-code
	OutputPhaseMsg( "\r\ngenerating 80x86 asm code..." );
	genPreSeg();
	genCodeSeg();

	// close the file
	m_file.Close();
}

/*  *    CAsmCodeGenerator
    *    Help routines
  *	* *
   ***   Programer: Â½Ïþ´º
    *    Date:		2004.05.25             */

// write comments to m_file, which must exist
void CAsmCodeGenerator::emitComment( char* format, ... )
{
	ASSERT( m_file.m_hFile != CFile::hFileNull );

	va_list params;
	static char buf[ 1024 ];
	buf[0] = ';';
	
	va_start( params, format );
	_vsnprintf( buf + 1, 1020, format, params );
	strcat( buf, "\r\n" );
	va_end( params );

	try {
		m_file.Write( buf, strlen(buf) );
	} catch( CFileException* ) {
		OutputErrMsg( "failed to write to file: %s", (LPCTSTR)m_file.GetFilePath() );
	}
}

// write label to m_file, which must exist
void CAsmCodeGenerator::emitLabel( char* format, ... )
{
	ASSERT( m_file.m_hFile != CFile::hFileNull );

	va_list params;
	static char buf[ 1024 ];

	va_start( params, format );
	_vsnprintf( buf, 1020, format, params );
	strcat( buf, "\r\n" );

	try {
		m_file.Write( buf, strlen(buf) );
	} catch( CFileException* ) {
		OutputErrMsg( "failed to write to file: %s", (LPCTSTR)m_file.GetFilePath() );
	}
}

// write codes to m_file, which must exist
void CAsmCodeGenerator::emitCode( char* format, ... )
{
	ASSERT( m_file.m_hFile != CFile::hFileNull );

	va_list params;
	static char buf[ 1024 ];
	buf[0] = '\t';
	
	va_start( params, format );
	_vsnprintf( buf + 1, 1020, format, params );
	strcat( buf, "\r\n" );
	va_end( params );

	try {
		m_file.Write( buf, strlen(buf) );
	} catch( CFileException* ) {
		OutputErrMsg( "failed to write to file: %s", (LPCTSTR)m_file.GetFilePath() );
	}
}

// add beginning "\t" & ending "/r/n" manually
void CAsmCodeGenerator::emitCode( CString& code )
{
	ASSERT( m_file.m_hFile != CFile::hFileNull );

	try {
		m_file.Write( (LPCTSTR)code, code.GetLength() );
	} catch( CFileException* ) {
		OutputErrMsg( "failed to write to file: %s", (LPCTSTR)m_file.GetFilePath() );
	}
}

/*  *    CAsmCodeGenerator
    *    80x86 ASM routines
  *	* *
   ***   Programer: Â½Ïþ´º
    *    Date:		2004.05.21             */

// read a character
// use AX register, result is stored in AL
void CAsmCodeGenerator::_inline_readc()
{
	CString temp = "	mov		ah, 1\r\n"
				   "	int		21h\r\n"
				   "	mov		ah, 0\r\n";
	emitCode( temp );
}

// read a integer
// need:
// data segment
// buf		db	64 dup(?)
// count	dw	?
void CAsmCodeGenerator::_readi()
{
	CString temp = ";----------------------------------------------------\r\n"
		           "; GENERAL PRUPOSE ROUTINES\r\n"
				   ";----------------------------------------------------\r\n"
				   "; FOR READI\r\n"
				   ";----------------------------------------------------\r\n"
				   ";input a decimal, result in AX\r\n"
				   "_call_readi_	proc	near pascal uses bx cx dx si\r\n"
				   "	mov		count, 0\r\n"
				   "readi@next:\r\n"
				   "	mov		ah, 7\r\n"
				   "	int		21h\r\n"
				   "	cmp		al, '-'\r\n"
				   "	je		readi@onCHAR\r\n"
				   "	cmp		al, '+'\r\n"
				   "	je		readi@onCHAR\r\n"
				   "	cmp		al, 08h	;DEL\r\n"
				   "	je		readi@onDEL\r\n"
				   "	cmp		al, 0dh	;CR\r\n"
				   "	je		readi@onCR\r\n"
				   "	cmp		al, '0'\r\n"
				   "	jb		readi@next\r\n"
				   "	cmp		al, '9'\r\n"
				   "	ja		readi@next\r\n"
				   "readi@onCHAR:\r\n"
				   "	cmp		count, 63\r\n"
				   "	jae		readi@next\r\n"
			   	   ";process the key input, and show it on screen\r\n"
				   "	mov		si, count\r\n"
				   "	inc 	count\r\n"
				   "	mov		buf[si], al\r\n"
				   "	mov		dl, al\r\n"
				   "	mov		ah, 02h\r\n"
				   "	int		21h\r\n"
				   "	jmp		readi@next\r\n"
				   "readi@onDEL:\r\n"
				   "	call	keydel\r\n"
				   "	jmp		readi@next\r\n"
				   "readi@onCR:\r\n"
				   "	mov		ah, 2\r\n"
				   "	mov		dl, 0ah\r\n"
				   "	int		21h\r\n"
				   "	mov		dl, 0dh\r\n"
				   "	int		21h\r\n"
				   "	mov		si, count\r\n"
				   "	mov		buf[si], 0\r\n"
				   "	call	str2dec\r\n"
				   "	ret\r\n"
				   "_call_readi_	endp\r\n"
				   ";----------------------------------------------------\r\n"
				   ";set the cursor in DX\r\n"
				   "set_cur		proc	near pascal uses ax bx\r\n"
				   "	mov		bh, 0\r\n"
				   "	mov		ah, 02h\r\n"
				   "	int		10h\r\n"
				   "	ret\r\n"
				   "set_cur	endp\r\n"
				   ";----------------------------------------------------\r\n"
				   ";read current cursor to DX\r\n"
				   "read_cur	proc	near pascal uses ax bx cx\r\n"
				   "	mov		bh, 0\r\n"
				   "	mov		ah, 03h\r\n"
				   "	int		10h\r\n"
				   "	ret\r\n"
				   "read_cur endp\r\n"
				   ";----------------------------------------------------\r\n"
				   ";procedure for key DEL\r\n"
				   "keydel		proc	near pascal uses bx cx dx\r\n"
				   "	cmp		count, 0\r\n"
				   "	jle		keydel@ret\r\n"
				   "	dec		count\r\n"
				   "	call	read_cur\r\n"
				   "	dec		dl\r\n"
				   "	call	set_cur\r\n"
				   "	mov		bh, 0\r\n"
				   "	mov		al, 20h\r\n"
				   "	mov		cx, 1\r\n"
				   "	mov		ah, 0ah\r\n"
				   "	int		10h\r\n"
				   "keydel@ret:	\r\n"
				   "	ret\r\n"
				   "keydel	endp\r\n"
				   ";----------------------------------------------------\r\n"
				   ";result in AX\r\n"
				   "str2dec		proc	near pascal uses bx cx dx si\r\n"
				   "	local	minus:byte\r\n"
				   ";init\r\n"
				   "	mov		minus, 0\r\n"
				   "	mov		ax, 0\r\n"
				   "	mov		bx, 10\r\n"
				   "	mov		cx, 0\r\n"
				   ";\r\n"
				   "	cmp		count, 0\r\n"
				   "	je		str2dec@ret\r\n"
				   "	mov		si, 0\r\n"
				   "	cmp		buf[si], '-'\r\n"
				   "	je		str2dec@onMINUS\r\n"
				   "	cmp		buf[si], '+'\r\n"
				   "	je		str2dec@onPLUS\r\n"
				   "str2dec@next:\r\n"
				   "	cmp		buf[si], '0'\r\n"
				   "	jb		str2dec@complete\r\n"
				   "	cmp		buf[si], '9'\r\n"
				   "	ja		str2dec@complete\r\n"
				   "	mul		bx\r\n"
				   "	mov		cx, ax\r\n"
				   "	mov		al, buf[si]\r\n"
				   "	sub		al, '0'\r\n"
				   "	mov		ah, 0\r\n"
				   "	add		ax, cx\r\n"
				   "	inc		si\r\n"
				   "	jmp		str2dec@next\r\n"
				   "str2dec@onMINUS:\r\n"
				   "	mov		minus, 1\r\n"
				   "	inc		si\r\n"
				   "	jmp		str2dec@next\r\n"
				   "str2dec@onPLUS:\r\n"
				   "	inc		si\r\n"
				   "	jmp		str2dec@next\r\n"
				   "str2dec@complete:\r\n"
				   "	cmp		minus, 1\r\n"
				   "	jne		str2dec@ret\r\n"
				   "	mov		cx, ax\r\n"
				   "	mov		ax, 0\r\n"
				   "	sub		ax, cx\r\n"
				   "str2dec@ret:\r\n"
				   "	ret\r\n"
				   "str2dec	endp\r\n";
	emitCode( temp );
}

// print the integer in BX
void CAsmCodeGenerator::_writei()
{
	CString temp = ";----------------------------------------------------\r\n"
				   "; FOR WRITEI\r\n"
				   ";----------------------------------------------------\r\n"
				   ";show decimal in BX\r\n"
				   "_call_showi_	proc	near pascal uses ax cx dx\r\n"
				   "	local	can_show:byte\r\n"
				   "	mov		can_show, 0\r\n"
				   "	cmp		bx, 0\r\n"
				   "	jge		show@show\r\n"
				   "	mov		ax, bx\r\n"
				   "	mov		bx, 0\r\n"
				   "	sub		bx, ax\r\n"
				   "	mov		ah, 2\r\n"
				   "	mov		dl, '-'\r\n"
				   "	int		21h\r\n"
				   "show@show:\r\n"
				   "	mov		cx, 10000d\r\n"
				   "	cmp		bx, cx\r\n"
				   "	jb		show@1\r\n"
				   "	mov		can_show, 1\r\n"
				   "	call	dec_div\r\n"
				   "show@1:\r\n"
				   "	mov		cx, 1000d\r\n"
				   "	cmp		can_show, 1\r\n"
				   "	je		show@2\r\n"
				   "	cmp		bx, cx\r\n"
				   "	jb		show@3\r\n"
				   "	mov		can_show, 1\r\n"
				   "show@2:\r\n"
				   "	call	dec_div\r\n"
				   "show@3:\r\n"
				   "	mov		cx, 100d\r\n"
				   "	cmp		can_show, 1\r\n"
				   "	je		show@4\r\n"
				   "	cmp		bx, cx\r\n"
				   "	jb		show@5\r\n"
				   "	mov		can_show, 1\r\n"
				   "show@4:\r\n"
				   "	call	dec_div\r\n"
				   "show@5:\r\n"
				   "	mov		cx, 10d\r\n"
				   "	cmp		can_show, 1\r\n"
				   "	je		show@6\r\n"
				   "	cmp		bx, cx\r\n"
				   "	jb		show@7\r\n"
				   "	mov		can_show, 1\r\n"
				   "show@6:\r\n"
				   "	call	dec_div\r\n"
				   "show@7:\r\n"
				   "	mov		cx, 1d\r\n"
				   "	call	dec_div\r\n"
				   "	ret\r\n"
				   "_call_showi_	endp\r\n"
				   ";----------------------------------------------------\r\n"
				   "dec_div	proc	near pascal uses ax\r\n"
				   "	mov		ax, bx\r\n"
				   "	mov		dx, 0\r\n"
				   "	div		cx\r\n"
				   "	mov		bx, dx\r\n"
				   "	mov		dl, al\r\n"
				   "	add		dl, 30h\r\n"
				   "	mov		ah, 2\r\n"
				   "	int		21h\r\n"
				   "dec_div@ret:\r\n"
				   "	ret\r\n"
				   "dec_div	endp\r\n";
	emitCode( temp );
}

/*  *    CAsmCodeGenerator
    *    code generation routines
  *	* *
   ***   Programer: Â½Ïþ´º
    *    Date:		2004.05.21             */

// generate data segment for global data and data in _main()
void CAsmCodeGenerator::genPreSeg()
{
	CTreeNode *p = NULL, *t = NULL;
	// add variables used in default routines
	CString temp = "	.model	small\r\n"
				   "	.386\r\n"
				   "	.stack	200h\r\n"
				   ";----------------------------------------------------\r\n"
				   "	.data\r\n"
				   ";variables used in _call_readi_ routine\r\n"
		           "buf		db	64 dup(?)\r\n"
				   "count	dw	?\r\n"
				   ";return values\r\n"
				   "_return	dw	?\r\n"
				   ";global and _main variables\r\n";
	emitCode( temp );
	// add global and _main variables
	p = m_pAnalyzer->m_pProgram;
	while( p ) {
		if( p->nodekind == kVarDec ) genData( p );
		else if( p->szName == "main" ) {
			t = p->child[0]; // main(...) parameters, common none
			while( t ) {
				genData( t );
				t = t->sibling;
			}
			t = p->child[1]; // local variables in _main
			while( t ) {
				if( t->nodekind == kVarDec ) genData( t );
				t = t->sibling;
			}
		}
		p = p->sibling;
	}
	// end of data segment
}

// generate an item in data segment for node p
// all types use the same type "DW"
void CAsmCodeGenerator::genData( CTreeNode* p )
{
	CString temp1, temp2;
	if( p->bArray ) temp1.Format( "%d dup(?)", p->iArraySize );
	else temp1.Format( "?" );
	temp2.Format( "%s@%s\tdw\t%s\r\n", (LPCTSTR)p->szScope, (LPCTSTR)p->szName, (LPCTSTR)temp1 );
	emitCode( temp2 );
}

// generate code segment
void CAsmCodeGenerator::genCodeSeg()
{
	CString temp = ";----------------------------------------------------\r\n"
				   "	.code\r\n"
				   ";_MAIN PROC\r\n"
				   "start		proc	far\r\n"
				   "	mov		ax, @data\r\n"
				   "	mov		ds, ax\r\n"
				   ";\r\n";
	emitCode( temp );

	CTreeNode* p = m_pAnalyzer->m_pProgram;
	while( p ) {
		if( p->nodekind == kFunDec && p->szName == "main" ) {
			genFunc( p ); break;
		}
		p = p->sibling;
	}
	p = m_pAnalyzer->m_pProgram;
	while( p ) {
		if( p->nodekind == kFunDec && p->szName != "main" ) {
			temp.Format( ";----------------------------------------------------\r\n"
						 "%s	proc	near pascal uses ax bx cx dx", (LPCTSTR)p->szName );// for parameters
			emitCode( temp );
			genFunc( p );
		}
		p = p->sibling;
	}
	// add general purpose routines
	_readi();
	_writei();
	// end of code segment
	temp = ";----------------------------------------------------\r\n"
		   "	end 	start\r\n";
	emitCode( temp );
}

// generate codes for one function
void CAsmCodeGenerator::genFunc( CTreeNode* pNode )
{
	CString temp;
	CTreeNode* p = pNode->child[0];
	if( pNode->szName != "main" )
		genLocal( pNode );
	p = pNode->child[1];
	while( p ) {
		genStmt( p );
		p = p->sibling;
	}
	if( pNode->szName == "main" )
		temp.Format( "	mov 	ax, 4c00h\r\n"
					 "	int		21h\r\n"
					 "start		endp\r\n" );
	else
		temp.Format( "	ret\r\n"
					 "%s	endp\r\n", (LPCTSTR)pNode->szName );
	emitCode( temp );
}

// generate local variables
void CAsmCodeGenerator::genLocal( CTreeNode* pNode )
{
	BOOL first = TRUE;
	CString local = _T(""), temp, temp2;
	CTreeNode* p = pNode->child[0];// parameters
	while( p ) {
		temp.Format( ", %s@%s:word", (LPCTSTR)p->szScope, (LPCTSTR)p->szName );
		emitCode( temp );
		p = p->sibling;
	}
	temp = "\r\n"; emitCode( temp );

	p = pNode->child[1];// make local variables
	while( p ) {
		if( p->nodekind == kVarDec ) {
			if( p->bArray ) temp2.Format( "%s@%s[%d]:word", (LPCTSTR)p->szScope, (LPCTSTR)p->szName, p->iArraySize );
			else temp2.Format( "%s@%s:word", (LPCTSTR)p->szScope, (LPCTSTR)p->szName );
			if( first ) {
				first = FALSE;
				temp.Format( "\tlocal\t%s", (LPCTSTR)temp2 );
			} else
				temp.Format( ", %s", (LPCTSTR)temp2 );
			local += temp;
		}
		p = p->sibling;
	}
	if( !first ) emitCode( local + "\r\n" );
}

void CAsmCodeGenerator::genStmt( CTreeNode* p, int lab1, int lab2 )
{
	CTreeNode* t = NULL;
	int i, _lab1, _lab2;
	CString temp = _T("");

	if( p == NULL ) return;
	switch( p->nodekind ) {
	case kStmt:
		switch( p->kind.stmt ) {
		case kRead:
			emitComment( "read statement" );
			// read in a char or a num
			if( p->type == _CHAR ) _inline_readc();
			else emitCode( "call\t_call_readi_" );
			// store
			t = p->child[0];
			if( t->bArray ) {
				emitCode( "push\tax" );
				if( isAddr(t) ) emitCode( "mov \tbx, %s@%s", (LPCTSTR)t->szScope, (LPCTSTR)t->szName );
				else emitCode( "lea \tbx, %s@%s", (LPCTSTR)t->szScope, (LPCTSTR)t->szName );
				emitCode( "push\tbx" );
				genStmt( t->child[0] );
				emitCode( "pop \tsi" );
				emitCode( "add \tsi, si" );// all use "WORD"
				emitCode( "pop \tbx" );
				emitCode( "pop \tax" );
				emitCode( "mov \t[bx + si], ax" );
			} else
				emitCode( "mov \t%s@%s, ax", (LPCTSTR)t->szScope, (LPCTSTR)t->szName );
			break;
		case kWrite:
			emitComment( "write statement" );
			t = p->child[0];
			if( p->type == _CHAR || p->type == _CHARACTER ) {
				if( t->nodekind == kExp && t->kind.exp == kConst ) {
					emitCode( "mov \tah, 2" );
					emitCode( "mov \tdl, '%c'", t->szName[0] );
				} else {
					genStmt( t );
					emitCode( "pop \tdx" );
					emitCode( "mov \tah, 2" );
				}
				emitCode( "int \t21h" );
			} else {
				genStmt( t );
				emitCode( "pop \tbx" );
				emitCode( "call\t_call_showi_" );
			}
			break;
		case kPrintf:
			emitComment( "printf statement" );
			emitCode( "push\tax" );
			emitCode( "push\tdx" );
			emitCode( "mov \tah, 2" );
			for( i = 0; i < p->szName.GetLength(); i++ ) {
				if( p->szName[i] == '\n' ) {
					temp = "	mov		dl, 00ah\r\n"
						   "	int		21h\r\n"
						   "	mov		dl, 00dh\r\n"
						   "	int		21h\r\n";
					emitCode( temp );
				} else {
					emitCode( "mov \tdl, %.3xh", (int)p->szName[i] );
					emitCode( "int \t21h" );
				}
			}
			emitCode( "pop \tdx" );
			emitCode( "pop \tax" );
			emitComment( "end of printf statement" );
			break;
		case kLabel:
			emitComment( "label %s@%s", (LPCTSTR)p->szScope, (LPCTSTR)p->szName );
			emitLabel( "%s@%s:", (LPCTSTR)p->szScope, (LPCTSTR)p->szName );
			break;
		case kGoto:
			emitComment( "goto %s@%s", (LPCTSTR)p->szScope, (LPCTSTR)p->szName );
			emitCode( "jmp \t%s@%s", (LPCTSTR)p->szScope, (LPCTSTR)p->szName );
			break;
		case kIf:
			emitComment( "start of if statement" );
			emitComment( "if conditions" );
			t = p->child[0];
			genStmt( t );
			emitCode( "pop \tax" );
			emitCode( "cmp \tax, 0" );
			_lab1 = label++;
			emitCode( "je  \tL%d", _lab1 );
			emitComment( "if statements" );
			t = p->child[1];
			while( t ) {
				genStmt( t, lab1, lab2 ); t = t->sibling;
			}
			if( p->child[2] ) {
				_lab2 = label++;
				emitCode( "jmp \tL%d", _lab2 );
			}
			emitLabel( "L%d:", _lab1 );
			if( p->child[2] ) {
				emitComment( "else statements" );
				t = p->child[2];
				while( t ) {
					genStmt( t, lab1, lab2 ); t = t->sibling;
				}
				emitLabel( "L%d:", _lab2 );
			}
			emitComment( "end of if statement" );
			break;
		case kWhile:
			emitComment( "start of while statement" );
			_lab1 = label++;
			emitLabel( "L%d:", _lab1 );
			emitComment( "while conditions" );
			t = p->child[0];
			genStmt( t );
			emitCode( "pop \tax" );
			emitCode( "cmp \tax, 0" );
			_lab2 = label++;
			emitCode( "je  \tL%d", _lab2 );
			emitComment( "while statements" );
			t = p->child[1];
			while( t ) {
				genStmt( t, _lab1, _lab2 ); t = t->sibling;
			}
			emitCode( "jmp \tL%d", _lab1 );
			emitLabel( "L%d:", _lab2 );
			emitComment( "end of while statement" );
			break;
		case kBreak:
			emitComment( "break statement" );
			emitCode( "jmp \tL%d", lab2 );
			break;
		case kContinue:
			emitComment( "continue statement" );
			emitCode( "jmp \tL%d", lab1 );
			break;
		case kReturn:
			emitComment( "return statement" );
			if( p->child[0] && p->szName != "main" ) {
				genStmt( p->child[0] );
				emitCode( "pop \tax" );
				emitCode( "mov \t_return, ax" );
			}
			if( p->sibling ||
				(p->father && p->father->nodekind != kFunDec) )
				emitCode( "ret" );
			break;
		case kCall:
			emitComment( "call '%s(...)'", (LPCTSTR)p->szName );
			t = p->child[0];
			while( t ) {
				genStmt( t ); t = t->sibling;
			}
			emitCode( "call\t%s", (LPCTSTR)p->szName );
			if( p->type != _VOID ) {
				emitCode( "mov \tax, _return" );
				emitCode( "push\tax" );
			}
			break;
		}
		break;
	case kExp:
		switch( p->kind.exp ) {
		case kConst:
			if( p->type == _CHARACTER ) {
				emitCode( "mov \tal, '%c'", p->szName[0] );
				emitCode( "mov \tah, 0" );
			} else
				emitCode( "mov \tax, %s", (LPCTSTR)p->szName );
			emitCode( "push\tax" );
			break;
		case kID:
			if( p->bArray ) {
				if( isAddr(p) )
					emitCode( "mov \tbx, %s@%s", (LPCTSTR)p->szScope, (LPCTSTR)p->szName );
				else
					emitCode( "lea \tbx, %s@%s", (LPCTSTR)p->szScope, (LPCTSTR)p->szName );
				if( p->father && p->father->nodekind == kStmt && p->father->kind.stmt == kCall )
					emitCode( "mov \tax, bx" );// passing its base-address to the call function is OK
				else {
					genStmt( p->child[0] );
					emitCode( "pop \tsi" );
					emitCode( "add \tsi, si" );// all use "WORD"
					emitCode( "mov \tax, [bx + si]" );
				}
			} else
				emitCode( "mov \tax, %s@%s", (LPCTSTR)p->szScope, (LPCTSTR)p->szName );
			emitCode( "push\tax" );
			break;
		case kOp:
			if( p->szName == "=" ) {
				if( p->father && p->father->szName == "=" && p->father->child[0] == p )
					break; // continuous ASSIGN the same ID
				emitComment( "" );
				genStmt( p->child[1] );
				// process the left-hand of "="
				t = p->child[0];
				while( t && (t->nodekind != kExp || t->kind.exp != kID) ) t = t->child[0];
				if( t->bArray ) {
					if( isAddr(t) )
						emitCode( "mov \tbx, %s@%s", (LPCTSTR)t->szScope, (LPCTSTR)t->szName );
					else
						emitCode( "lea \tbx, %s@%s", (LPCTSTR)t->szScope, (LPCTSTR)t->szName );
					genStmt( t->child[0] );
					emitCode( "pop \tsi" );
					emitCode( "add \tsi, si" );
					emitCode( "add \tbx, si" );
					emitCode( "pop \tax" );
					emitCode( "mov \t[bx], ax" );
				} else {
					emitCode( "pop \tax" );
					emitCode( "mov \t%s@%s, ax", (LPCTSTR)t->szScope, (LPCTSTR)t->szName );
				}
			} else if( p->szName == "!" ) {
				genStmt( p->child[0] );
				_lab1 = label++; _lab2 = label++;
				temp.Format( "	pop		ax\r\n"
						     "	cmp		ax, 0\r\n"
						     "	je		__not@@%d\r\n"
						     "	mov		ax, 0\r\n"
						     "	jmp		__not@@%d\r\n"
							 "__not@@%d:\r\n"
							 "	mov		ax, 1\r\n"
							 "__not@@%d:\r\n", _lab1, _lab2, _lab1, _lab2 );
				emitCode( temp );
			} else {
				// binary operations
				genStmt( p->child[0] );
				genStmt( p->child[1] );
				emitCode( "pop \tbx" );
				emitCode( "pop \tax" );
				if( p->szName == "==" ) {
					_lab1 = label++; _lab2 = label++;
					temp.Format( "	sub		ax, bx\r\n"
								 "	cmp		ax, 0\r\n"
								 "	je		__eq@@%d\r\n"
								 "	mov		ax, 0\r\n"
								 "	jmp		__eq@@%d\r\n"
								 "__eq@@%d:\r\n"
								 "	mov		ax, 1\r\n"
								 "__eq@@%d:\r\n", _lab1, _lab2, _lab1, _lab2 );
					emitCode( temp );
				} else if( p->szName == "!=" ) {
					_lab1 = label++;
					temp.Format( "	sub		ax, bx\r\n"
								 "	cmp		ax, 0\r\n"
								 "	je		__neq@@%d\r\n"
								 "	mov		ax, 1\r\n"
								 "__neq@@%d:\r\n", _lab1, _lab1 );
					emitCode( temp );
				} else if( p->szName == "<" ) {
					_lab1 = label++; _lab2 = label++;
					temp.Format( "	sub		ax, bx\r\n"
								 "	cmp		ax, 0\r\n"
								 "	jl		__lt@@%d\r\n"
								 "	mov		ax, 0\r\n"
								 "	jmp		__lt@@%d\r\n"
								 "__lt@@%d:\r\n"
								 "	mov		ax, 1\r\n"
								 "__lt@@%d:\r\n", _lab1, _lab2, _lab1, _lab2 );
					emitCode( temp );
				} else if( p->szName == "<=" ) {
					_lab1 = label++; _lab2 = label++;
					temp.Format( "	sub		ax, bx\r\n"
								 "	cmp		ax, 0\r\n"
								 "	jle		__ngt@@%d\r\n"
								 "	mov		ax, 0\r\n"
								 "	jmp		__ngt@@%d\r\n"
								 "__ngt@@%d:\r\n"
								 "	mov		ax, 1\r\n"
								 "__ngt@@%d:\r\n", _lab1, _lab2, _lab1, _lab2 );
					emitCode( temp );
				} else if( p->szName == ">=" ) {
					_lab1 = label++; _lab2 = label++;
					temp.Format( "	sub		ax, bx\r\n"
								 "	cmp		ax, 0\r\n"
								 "	jge		__nlt@@%d\r\n"
								 "	mov		ax, 0\r\n"
								 "	jmp		__nlt@@%d\r\n"
								 "__nlt@@%d:\r\n"
								 "	mov		ax, 1\r\n"
								 "__nlt@@%d:\r\n", _lab1, _lab2, _lab1, _lab2 );
					emitCode( temp );
				} else if( p->szName == ">" ) {
					_lab1 = label++; _lab2 = label++;
					temp.Format( "	sub		ax, bx\r\n"
								 "	cmp		ax, 0\r\n"
								 "	jg		__gt@@%d\r\n"
								 "	mov		ax, 0\r\n"
								 "	jmp		__gt@@%d\r\n"
								 "__gt@@%d:\r\n"
								 "	mov		ax, 1\r\n"
								 "__gt@@%d:\r\n", _lab1, _lab2, _lab1, _lab2 );
					emitCode( temp );
				} else if( p->szName == "+" )
					emitCode( "add \tax, bx" );
				else if( p->szName == "-" )
					emitCode( "sub \tax, bx" );
				else if( p->szName == "*" )
					emitCode( "imul\tbx" );
				else if( p->szName == "/" )
					emitCode( "idiv\tbx" );
				else if( p->szName == "&&" )
					emitCode( "and \tax, bx" );
				else if( p->szName == "||" )
					emitCode( "or  \tax, bx" );
			}
			// situations
			t = p->father;
			if( t && (t->nodekind == kExp || (t->nodekind == kStmt && p == t->child[0])) )
				emitCode( "push\tax" );
			break;
		}
		break;
	}
}

// check if pNode->szName is an address
// in this simple situation, pNode->szName is a parameter passed as array address
BOOL CAsmCodeGenerator::isAddr( CTreeNode* pNode )
{
	if( !pNode || pNode->nodekind != kExp || pNode->kind.exp != kID ) return FALSE;
	CTreeNode* p = pNode->father;
	while( p && p->nodekind != kFunDec ) p = p->father;
	CTreeNode* t = p->child[0];// parameters
	while( t ) {
		if( t->bArray && t->szName == pNode->szName ) return TRUE;
		t = t->sibling;
	}
	return FALSE;
}
