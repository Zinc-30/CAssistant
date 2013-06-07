#ifndef _ANALYZER_H_
#define _ANALYZER_H_

#include "SymbolTable.h"
#include "FunArgsCheck.h"

// build a syntax tree, then do semantic analysis,
// besides construct a symbol table
class CAnalyzer
{
public:
	CAnalyzer( CString& str );
	~CAnalyzer();

// Attributes
public:
	CTreeNode*		m_pProgram;
	CParser*		m_pParser;
	static CSymbolTable		m_SymbolTable;
	static CFunArgsCheck	m_FunArgs;

// Operations
public:
	void			BuildSymbolTable( CTreeNode* pNode );
	void			typeCheck( CTreeNode* pNode );

	void			Trace( LPCTSTR lpszPathName );
	void			TraceTypeCheck();

// help routines
private:
	void			traverse( CTreeNode* t, 
		                      void(* preProc)(CTreeNode*), void(* postProc)(CTreeNode*) );
	static void		nullProc( CTreeNode* t );
	static void		insertNode( CTreeNode* t );
	static void		checkNode( CTreeNode* t );

private:
	static int		location;
};

#endif // _ANALYZER_H_
