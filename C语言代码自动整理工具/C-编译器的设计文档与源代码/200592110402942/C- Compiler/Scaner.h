#if !defined(AFX_SCANER_H__AB6A94C5_5F1E_402E_B185_BECAEE10706F__INCLUDED_)
#define AFX_SCANER_H__AB6A94C5_5F1E_402E_B185_BECAEE10706F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// scaner.h : header file
//

#include <afxtempl.h>
#include "tokenizer.h"

extern CString ReservedKeywordList[];

enum TokenType
{
	// reserved Keyword
	_AUTO, _DOUBLE, _INT, _STRUCT,
	_BREAK, _ELSE, _LONG, _SWITCH, 
	_CASE, _ENUM, _REGISTER, _TYPEDEF,
	_CHAR, _EXTERN, _RETURN, _UNION,
	_CONST, _FLOAT, _SHORT, _UNSIGNED,
	_CONTINUE, _FOR, _SIGNED, _VOID,
	_DEFAULT, _GOTO, _SIZEOF, _VOLATILE,
	_DO, _IF, _STATIC, _WHILE,
	_READ, _WRITE, _PRINTF,

	// operations
	ASSIGN, PLUS, MINUS, TIMES, DIV, MOD,
	BITWISE_AND, BITWISE_OR, BITWISE_NOT, LOGICAL_NOT, LT, GT,

	// interpunctions
	LPARAN, RPARAN, LBRACE, RBRACE, LSQUARE, RSQUARE, COMMA, DOT, SEMI, COLON,

	// complex operations
	EQ/* == */, NEQ/* != */, PLUS_PLUS/* ++ */, MINUS_MINUS/* -- */,
	PLUS_ASSIGN/* += */, MINUS_ASSIGN/* -= */, TIMES_ASSIGN/* *= */, DIV_ASSIGN/* /= */,
	NGT/* <= */, NLT/* >= */, LOGICAL_AND/* && */, LOGICAL_OR/* || */,

	// others
	_EOF, _ID, _NUM, _STRING, _CHARACTER, _LABEL, _ERROR, _NONE
};

struct TOKEN
{
	enum TokenType	type;
	CString			str;
};

// class CScaner
#define MAX_KW 100

class CScaner : public CTokenizer
{
public:
	CScaner( CString& str );
	virtual ~CScaner();

	void	MapKeyword();
	/********** TRACE **********/
	void	Trace( LPCTSTR lpszPathname );
	void	Flush();

	void	PushBack();
	TOKEN&	NextToken();

public:
	// Help routines

private:
	BOOL	m_bPushedBack;
	BOOL	m_bTrace;

	CFile	m_fTraceFile;
	TOKEN	m_token;
	CMap<CString, LPCSTR, enum TokenType, enum TokenType> m_KeyIndex;
};

#endif // !defined(AFX_SCANER_H__AB6A94C5_5F1E_402E_B185_BECAEE10706F__INCLUDED_)
