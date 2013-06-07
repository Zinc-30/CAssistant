// PCodeGenerator.cpp : implementation file
//

#include "stdafx.h"
#include "cminus.h"

#include "PCodeGenerator.h"

/*  *    CPCodeGenerator
    *    Construction & destruction
  *	* *
   ***   Programer: Â½Ïþ´º
    *    Date:		2004.05.21             */

CPCodeGenerator::CPCodeGenerator( CString& str )
{
	m_pAnalyzer = new CAnalyzer( str );
	m_pProgram  = NULL;
	label		= 1;
}

CPCodeGenerator::~CPCodeGenerator()
{
	if( m_file.m_hFile != CFile::hFileNull ) m_file.Close();// close the output file
	if( m_pAnalyzer ) delete m_pAnalyzer;
	// DO NOT DELETE m_pProgram, it points to the tree in the m_pAnalyzer,
	// which has already been destructed above
}

/*  *    CPCodeGenerator
    *    Main routine, generating p-code
  *	* *
   ***   Programer: Â½Ïþ´º
    *    Date:		2004.05.21             */

void CPCodeGenerator::GeneratePCode( LPCTSTR lpszPathName )
{
	m_pAnalyzer->TraceTypeCheck();
	if( bErrFlag ) {
		OutputPhaseMsg( "\r\nerrors occur, stop generating code!" );
		return;
	}
	m_pProgram = m_pAnalyzer->m_pProgram;
	ASSERT( m_pProgram != NULL );

	// create file
	CFileException e;
	if( !m_file.Open( lpszPathName, CFile::modeCreate | CFile::modeReadWrite, &e ) ) {
		OutputErrMsg( "failed to create file for code generation: %s", lpszPathName );
		return;
	}

	// generating p-code
	OutputPhaseMsg( "\r\ngenerating p-code..." );
	genPCode( m_pProgram );

	// close the file
	m_file.Close();
}

/*  *    CPCodeGenerator
    *    Help routines
  *	* *
   ***   Programer: Â½Ïþ´º
    *    Date:		2004.05.21             */

// write comments to m_file, which must exist
void CPCodeGenerator::emitComment( char* format, ... )
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

// write codes to m_file, which must exist
void CPCodeGenerator::emitCode( char* format, ... )
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
void CPCodeGenerator::emitCode( CString& code )
{
	ASSERT( m_file.m_hFile != CFile::hFileNull );

	try {
		m_file.Write( (LPCTSTR)code, code.GetLength() );
	} catch( CFileException* ) {
		OutputErrMsg( "failed to write to file: %s", (LPCTSTR)m_file.GetFilePath() );
	}
}

/*  *    CPCodeGenerator
    *    private operations
  *	* *
   ***   Programer: Â½Ïþ´º
    *    Date:		2004.05.21             */

void CPCodeGenerator::genPCode( CTreeNode* t, BOOL addr, int lab1, int lab2 )
{
	ASSERT( m_file.m_hFile != CFile::hFileNull );

	CTreeNode* p = NULL;
	int i, _lab1, _lab2;
	CString temp = _T("");

	if( t == NULL ) return;

	switch( t->nodekind ) {
	case kFunDec:
		emitComment( "------------ Copyright Â½Ïþ´º, 2004 ------------" );
		emitComment( "start of function '%s %s(...)' declaration",
			         (LPCTSTR)ReservedKeywordList[(int)t->type], (LPCTSTR)t->szName );
		emitCode( "ent \t%s", (LPCTSTR)t->szName );
		genPCode( t->child[0], addr, lab1, lab2 );
		genPCode( t->child[1], addr, lab1, lab2 );
		emitCode( "ret" );
		emitComment( "end of function '%s %s(...)' declaration",
			         (LPCTSTR)ReservedKeywordList[(int)t->type], (LPCTSTR)t->szName );
		break;
	case kVarDec:
		if( t->bArray ) temp.Format( "[%d]", t->iArraySize );
		emitComment( "declaration: %s %s%s",
			         (LPCTSTR)ReservedKeywordList[(int)t->type], (LPCTSTR)t->szName, (LPCTSTR)temp );
//		if( t->szScope == "global" )
//			emitCode( "global\t%s%s:%s\t;global variable declaration",
//			          (LPCTSTR)t->szName, (LPCTSTR)temp, (LPCTSTR)ReservedKeywordList[(int)t->type] );
//		else
//			emitCode( "local\t%s%s:%s\t;local variable declaration",
//			          (LPCTSTR)t->szName, (LPCTSTR)temp, (LPCTSTR)ReservedKeywordList[(int)t->type] );
		break;
	case kParam:
		emitComment( "parameter: '%s %s%s'", 
					 (LPCTSTR)ReservedKeywordList[(int)t->type], (LPCTSTR)t->szName, (t->bArray ? "[]" : "") );
//		emitCode( "param\t%s%s:%s",
//			      (LPCTSTR)t->szName, (t->bArray ? "[]" : ""), (LPCTSTR)ReservedKeywordList[(int)t->type] );
		break;
	case kStmt:
		switch( t->kind.stmt ) {
		case kRead:
			emitComment( "read" );
			genPCode( t->child[0], TRUE, lab1, lab2 );
			switch( t->type ) {
			case _CHAR:		emitCode( "rdc\t;read a character from terminal" );	break;
			case _INT:		emitCode( "rdi\t;read an integer from terminal" );	break;
			case _FLOAT:	emitCode( "rdf\t;read a float number from terminal" );
			}
			break;
		case kWrite:
			emitComment( "write" );
			genPCode( t->child[0], addr, lab1, lab2 );
			switch( t->type ) {
			case _CHAR:		emitCode( "wrc\t;output a character to terminal" );	break;
			case _INT:		emitCode( "wri\t;output an integer to terminal" );	break;
			case _FLOAT:	emitCode( "wrf\t;output a float number to terminal"	);
			}
			break;
		case kPrintf:
			emitComment( "print \"%s\"", (LPCTSTR)t->szName );
			for( i = 0; i < t->szName.GetLength(); i++ ) {
				if( t->szName[i] == '\r' ) temp = "\\r";
				else if( t->szName[i] == '\n' ) temp = "\\n";
				else if( t->szName[i] == '\t' ) temp = "\\t";
				else if( t->szName[i] == '\a' ) temp = "\\a";
				else if( t->szName[i] == '\b' ) temp = "\\b";
				else if( t->szName[i] == '\f' ) temp = "\\f";
				else if( t->szName[i] == '\v' ) temp = "\\v";
				else temp.Format( "%c", t->szName[i] );
				emitCode( "ldcc\t'%s'", (LPCTSTR)temp );
				emitCode( "wrc\t;output a character to terminal" );
			}
			break;
		case kLabel:
			emitComment( "lab %s@%s", (LPCTSTR)t->szScope, (LPCTSTR)t->szName );
			emitCode( "lab \t%s@%s", (LPCTSTR)t->szScope, (LPCTSTR)t->szName );
			break;
		case kGoto:
			emitComment( "goto %s@%s", (LPCTSTR)t->szScope, (LPCTSTR)t->szName );
			emitCode( "ujp \t%s@%s", (LPCTSTR)t->szScope, (LPCTSTR)t->szName );
			break;
		case kIf:
			emitComment( "start of if statement" );
			emitComment( "if conditions" );
			genPCode( t->child[0], addr, lab1, lab2 );
			_lab1 = label++;
			emitCode( "fjp \tL%d", _lab1 );
			emitComment( "if statements" );
			genPCode( t->child[1], addr, lab1, lab2 );
			if( t->child[2] != NULL ) {
				_lab2 = label++;
				emitCode( "ujp \tL%d", _lab2 );
			}
			emitCode( "lab \tL%d", _lab1 );
			if( t->child[2] != NULL ) {
				emitComment( "else statements" );
				genPCode( t->child[2], addr, lab1, lab2 );
				emitCode( "lab \tL%d", _lab2 );
			}
			emitComment( "end of if statement" );
			break;
		case kWhile:
			emitComment( "start of while statement" );
			_lab1 = label++;
			emitCode( "lab \tL%d", _lab1 );
			emitComment( "while conditions" );
			genPCode( t->child[0], addr, lab1, lab2 );
			_lab2 = label++;
			emitCode( "fjp \tL%d", _lab2 );
			emitComment( "while statements" );
			genPCode( t->child[1], addr, _lab1, _lab2 );
			emitCode( "ujp \tL%d", _lab1 );
			emitCode( "lab \tL%d", _lab2 );
			emitComment( "end of while statement" );
			break;
		case kBreak:
			emitComment( "break statement" );
			emitCode( "ujp \tL%d", lab2 );
			break;
		case kContinue:
			emitComment( "continue statement" );
			emitCode( "ujp \tL%d", lab1 );
			break;
		case kReturn:
			emitComment( "return statement" );
			if( t->child[0] ) // return a value
				genPCode( t->child[0], addr, lab1, lab2 );
			else // void
				emitComment( "return void" );
			if( t->sibling || 
				(t->father && t->father->nodekind != kFunDec) )
				emitCode( "ret" );// not at the end of the routine, add "ret"
			break;
		case kCall:
			emitComment( "call '%s(...)'", (LPCTSTR)t->szName );
			emitCode( "mst" );
			if( t->child[0] ) // generate code of expressions in arguments
				genPCode( t->child[0], addr, lab1, lab2 );
			emitCode( "cup \t%s", (LPCTSTR)t->szName );
			emitComment( "end of call '%s(...)'", (LPCTSTR)t->szName );
		}
		break;
	case kExp:
		switch( t->kind.exp ) {
		case kConst:
			if( t->type == _CHARACTER ) 
				emitCode( "ldcc\t%s", (LPCTSTR)t->szName );
			else {
				if( t->szName.Find('.') == -1 ) // integer
					emitCode( "ldci\t%s", (LPCTSTR)t->szName );
				else // is float number
					emitCode( "ldcf\t%s", (LPCTSTR)t->szName );
			}
			break;
		case kID:
			if( t->bArray ) {
				emitCode( "lda \t%s", (LPCTSTR)t->szName );
				if( t->father && t->father->nodekind == kStmt && t->father->kind.stmt == kCall )
					break;// passing its base-address to the call function is OK
				genPCode( t->child[0], FALSE, lab1, lab2 );
				emitCode( "ixa \telem_size(%s)", (LPCTSTR)t->szName );
				if( !addr ) // load value
					emitCode( "ind \t0" );
			} else {
				if( addr ) // load address
					emitCode( "lda \t%s", (LPCTSTR)t->szName );
				else // load value
					emitCode( "lod \t%s", (LPCTSTR)t->szName );
			}
			break;
		case kOp:
			if( t->szName == "=" ) {
				genPCode( t->child[0], TRUE, lab1, lab2 );
				genPCode( t->child[1], FALSE, lab1, lab2 );
				p = t->father;
				if( (p && p->nodekind == kStmt && t == p->child[0]) ||
					(p && p->nodekind == kExp) )
					// t is a condition expression, or is in a expression,
					// keep the result in stack
					emitCode( "stn" );
				else // otherwise, pop it
					emitCode( "sto" );
			} else if( t->szName == "!" ) {
				genPCode( t->child[0], FALSE, lab1, lab2 );
				emitCode( "not" );
			} else {
				genPCode( t->child[0], FALSE, lab1, lab2 );
				genPCode( t->child[1], FALSE, lab1, lab2 );
				if( t->szName == "==" )
					emitCode( "equ \t;equal expression" );
				else if( t->szName == "!=" )
					emitCode( "neq \t;not equal expression" );
				else if( t->szName == "+" ) {
					if( t->type == _FLOAT ) emitCode( "adr \t;float add" );// float add
					else emitCode( "adi \t;integer add" );// integer add
				} else if( t->szName == "-" ) {
					if( t->type == _FLOAT ) emitCode( "sbr \t;float sub" );// float sub
					else emitCode( "sbi \t;integer sub" );// integer sub
				} else if( t->szName == "*" ) {
					if( t->type == _FLOAT ) emitCode( "mpr \t;float mul" );// float mul
					else emitCode( "mpi \t;integer mul" );// integer mul
				} else if( t->szName == "/" ) {
					if( t->type == _FLOAT ) emitCode( "dvr \t;float div" );// float div
					else emitCode( "dvi \t;integer div" );// integer div
				} else if( t->szName == "%" )
					emitCode( "mod \t;mod expression" );
				else if( t->szName == "<" )
					emitCode( "les \t;less than expression" );
				else if( t->szName == "<=" )
					emitCode( "leq \t;less than or equal expression" );
				else if( t->szName == ">" )
					emitCode( "grt \t;greater than expression" );
				else if( t->szName == ">=" )
					emitCode( "geq \t;greater than or equal expression" );
				else if( t->szName == "&&" )
					emitCode( "and \t;logical and expression" );
				else if( t->szName == "||" )
					emitCode( "or  \t;logical or expression" );
				else
					emitCode( "__error__" );
			}
		}
		break;
	default:
		emitCode( "__error__" );
	}

	if( t->sibling ) genPCode( t->sibling, addr, lab1, lab2 );
}
