// scaner.cpp : implementation file
//

#include "stdafx.h"
#include "cminus.h"
#include "scaner.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

CString ReservedKeywordList[] =
{
	"auto", "double", "int", "struct",
	"break", "else", "long", "switch",
	"case", "enum", "register", "typedef", 
	"char", "extern", "return", "union",
	"const", "float", "short", "unsigned",
	"continue", "for", "signed", "void",
	"default", "goto", "sizeof", "volatile",
	"do", "if", "static", "while",
	"read", "write", "printf",

	// operations
	"=", "+", "-", "*", "/", "%", "&", "|", "~", "!", "<", ">",
	
	// interpunctions
	"(", ")", "{", "}", "[", "]", ",", ".", ";", ":"
};

/*  *    CScaner
    *    Construction & destruction
  *	* *
   ***   Programer: Â½Ïþ´º
    *    Date:		2004.05.17             */

CScaner::CScaner( CString& str ) : CTokenizer( str )
{
	m_bPushedBack = FALSE;
	m_bTrace = FALSE;
	m_token.type = _ID;

	MapKeyword();
}

CScaner::~CScaner()
{
	if( m_fTraceFile.m_hFile != CFile::hFileNull )
		m_fTraceFile.Close();
}

/*  *    CScaner
    *    public functions
  *	* *
   ***   Programer: Â½Ïþ´º
    *    Date:		2004.05.17             */

// map keyword to TokenType
void CScaner::MapKeyword()
{
	m_KeyIndex.RemoveAll();
	m_KeyIndex.InitHashTable( MAX_KW );

	for( int i = 0; i < sizeof(ReservedKeywordList) / sizeof(*ReservedKeywordList); i++ )
		m_KeyIndex[ ReservedKeywordList[i] ] = (enum TokenType)i;
}

// trace function
void CScaner::Trace( LPCTSTR lpszPathname )
{
	ASSERT( m_fTraceFile.m_hFile == CFile::hFileNull );

	CFileException e;
	if( !m_fTraceFile.Open( lpszPathname, CFile::modeCreate | CFile::modeReadWrite, &e ) ) {
		OutputErrMsg( "failed to create scaner trace file: %s", lpszPathname );
		return;
	}

	m_bTrace = TRUE;
}

void CScaner::Flush()
{
	if( m_fTraceFile.m_hFile == CFile::hFileNull ) return;
	m_fTraceFile.Flush();
}

// get the next token
TOKEN& CScaner::NextToken()
{
	if( m_bPushedBack ) {
		m_bPushedBack = FALSE;
		return m_token;
	}
	if( m_token.type == _EOF ) return m_token;

	enum TokenType type;
	int val = CTokenizer::NextToken();
	int	lineno = LineNo();// the actual line the token is got from
	
	m_token.type = _ERROR;
	m_token.str = "error";

	if( val == TT_EOF ) {
		m_token.type = _EOF;
		m_token.str = "EOF";
		return m_token;
	}

	if( val == TT_WORD ) {
		if( m_KeyIndex.Lookup( m_sVal, type ) )
			m_token.type = type;
		else 
			m_token.type = _ID;
		m_token.str = m_sVal;
	} else if( val == TT_INTEGER || val == TT_REAL ) {
		m_token.type = _NUM;
		m_token.str = GetStrValue();
	} else if( val == TT_STRING ) {
		m_token.type = _STRING;
		m_token.str = m_sVal;
	} else if( val == TT_CHAR ) {
		m_token.type = _CHARACTER;
		m_token.str = (m_sVal.IsEmpty()) ? " " : CString( m_sVal[0] );
	} else if( val == TT_EOL ) {
		return NextToken();
	} else if( ::strchr( "=+-*/&|~!<>(){}[],.;:", val ) ) {
		m_token.str = (TCHAR)val;
		m_token.type = m_KeyIndex[ m_token.str ];

		// complex operations
		switch( val ) {
		case '=':
			if( CTokenizer::NextToken() == '=' ) {
				m_token.str = "==";
				m_token.type = EQ;
			} else
				CTokenizer::PushBack();
			break;
		case '!':
			if( CTokenizer::NextToken() == '=' ) {
				m_token.str = "!=";
				m_token.type = NEQ;
			} else
				CTokenizer::PushBack();
			break;
		case '+':
			if( CTokenizer::NextToken() == '=' ) {
				m_token.str = "+=";
				m_token.type = PLUS_ASSIGN;
			} else {
				CTokenizer::PushBack();
				if( CTokenizer::NextToken() == '+' ) {
					m_token.str = "++";
					m_token.type = PLUS_PLUS;
				} else
					CTokenizer::PushBack();
			}
			break;
		case '-':
			if( CTokenizer::NextToken() == '=' ) {
				m_token.str = "-=";
				m_token.type = MINUS_ASSIGN;
			} else {
				CTokenizer::PushBack();
				if( CTokenizer::NextToken() == '-' ) {
					m_token.str = "--";
					m_token.type = MINUS_MINUS;
				} else
					CTokenizer::PushBack();
			}
			break;
		case '*':
			if( CTokenizer::NextToken() == '=' ) {
				m_token.str = "*=";
				m_token.type = TIMES_ASSIGN;
			} else
				CTokenizer::PushBack();
			break;
		case '/':
			if( CTokenizer::NextToken() == '=' ) {
				m_token.str = "/=";
				m_token.type = DIV_ASSIGN;
			} else
				CTokenizer::PushBack();
			break;
		case '<':
			if( CTokenizer::NextToken() == '>' ) {
				m_token.str = "<>";
				m_token.type = NEQ;
			} else {
				CTokenizer::PushBack();
				if( CTokenizer::NextToken() == '=' ) {
					m_token.str = "<=";
					m_token.type = NGT;
				} else
					CTokenizer::PushBack();
			}
			break;
		case '>':
			if( CTokenizer::NextToken() == '=' ) {
				m_token.str = ">=";
				m_token.type = NLT;
			} else
				CTokenizer::PushBack();
			break;
		case '&':
			if( CTokenizer::NextToken() == '&' ) {
				m_token.str = "&&";
				m_token.type = LOGICAL_AND;
			} else
				CTokenizer::PushBack();
			break;
		case '|':
			if( CTokenizer::NextToken() == '|' ) {
				m_token.str = "||";
				m_token.type = LOGICAL_OR;
			} else
				CTokenizer::PushBack();
			break;
		}
	} else
		OutputErrMsg( "error in line %d: syntax error '%c'", LineNo(), (char)val );

	if( m_bTrace ) {
		CString temp;
		temp.Format( "line:%3d   Token Code: %.2d  %s\r\n", lineno, m_token.type, (LPCTSTR)m_token.str );
		try {
			m_fTraceFile.Write( (LPCTSTR)temp, temp.GetLength() );
		} catch( CFileException* ) {
			OutputErrMsg( "failed to write to file: %s", (LPCTSTR)m_fTraceFile.GetFilePath() );
		}
	}

	return m_token;
}

void CScaner::PushBack()
{
	m_bPushedBack = TRUE;
}
