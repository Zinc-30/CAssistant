// Analyzer.cpp : implementation file
//

#include "stdafx.h"
#include "cminus.h"

#include "Analyzer.h"

/*  *    CAnalyzer
    *    Construction & destruction
  *	* *
   ***   Programer: Â½Ïþ´º
    *    Date:		2004.05.20             */

// static member variables initiation
CSymbolTable	CAnalyzer::m_SymbolTable;
CFunArgsCheck	CAnalyzer::m_FunArgs;
int				CAnalyzer::location;

CAnalyzer::CAnalyzer( CString& str )
{
	m_pParser = new CParser( str );
	m_pProgram = NULL;
	m_SymbolTable.deleteHashTable();
	m_FunArgs.deleteList();

	location = 0;
}

CAnalyzer::~CAnalyzer()
{
	if( m_pParser ) delete m_pParser;
	// DO NOT DELETE m_pProgram, it points to the tree in the m_pParser,
	// which has been destructed above
}

/*  *    CAnalyzer
    *    public operations
  *	* *
   ***   Programer: Â½Ïþ´º
    *    Date:		2004.05.20             */

// build the symbol table
void CAnalyzer::BuildSymbolTable( CTreeNode* pNode )
{
	traverse( pNode, insertNode, nullProc );
}

// Procedure typeCheck performs type checking by a postorder syntax tree traversal
void CAnalyzer::typeCheck( CTreeNode* pNode )
{
	traverse( pNode, nullProc, checkNode );
	// after semantic analysis, check if main() exists
	if( m_SymbolTable.st_lookup( CString("main"), CString("global") ) == -1 )
		OutputErrMsg( "\r\nUnresolved external symbol _main" );
}

// trace the symbol table
void CAnalyzer::Trace( LPCTSTR lpszPathName )
{
	ClearErrFlag();

	OutputPhaseMsg( "building syntax tree..." );
	m_pProgram = m_pParser->BuildSyntaxTree();
	if( bErrFlag ) {
		OutputPhaseMsg( "\r\nerrors occur while parsing, stop constructing symbol table!" );
		return;
	} else
		OutputPhaseMsg( "successfully build the syntax tree!" );
	OutputPhaseMsg( "\r\nconstructing symbol table..." );
	BuildSymbolTable( m_pProgram );
	// ignore errors
	m_SymbolTable.PrintSymbolTable( lpszPathName );
}

// trace type checking
void CAnalyzer::TraceTypeCheck()
{
	ClearErrFlag();

	OutputPhaseMsg( "building syntax tree..." );
	m_pProgram = m_pParser->BuildSyntaxTree();
	if( bErrFlag ) {
		OutputPhaseMsg( "\r\nerrors occur while parsing, stop constructing symbol table!" );
		return;
	}
	OutputPhaseMsg( "\r\nconstructing symbol table..." );
	BuildSymbolTable( m_pProgram );
	if( bErrFlag ) {
		OutputPhaseMsg( "\r\nerrors occur while constructing symbol table, stop type checking!" );
		return;
	}
	OutputPhaseMsg( "\r\ntype checking..." );
	typeCheck( m_pProgram );
	if( bErrFlag )
		OutputPhaseMsg( "\r\nerrors occur while type checking!" );
	else 
		OutputPhaseMsg( "All OK!" );
}

/*  *    CAnalyzer
    *    help routines
  *	* *
   ***   Programer: Â½Ïþ´º
    *    Date:		2004.05.20             */
 
// Procedure traverse is a generic recursive syntax tree traversal routine:
// it applies preProc in preorder and postProc in postorder to tree pointed to by t
void CAnalyzer::traverse( CTreeNode* t, 
						  void(* preProc)(CTreeNode*), void(* postProc)(CTreeNode*) )
{
	if( t ) {
		preProc( t );
		for( int i = 0; i < MAX_CHILDREN; i++ )
			traverse( t->child[i], preProc, postProc );
		postProc( t );
		traverse( t->sibling, preProc, postProc );
	}
}

// nullProc is a do-nothing procedure to generate preorder-only or
// postorder-only traversals from traverse
void CAnalyzer::nullProc( CTreeNode* t )
{
	return;
}

// Procedure insertNode inserts identifiers stored in t into 
// the symbol table 
void CAnalyzer::insertNode( CTreeNode* t )
{
	ASSERT( t );
	switch( t->nodekind ) {
	case kFunDec:
		if( m_SymbolTable.st_lookup( t->szName, t->szScope ) == -1 ) {
			// not defined, so add it to the symbol table
			m_SymbolTable.st_insert( t->szName, t->szScope, t->type, t->lineno, location++ );
			// add it to function declaration list
			m_FunArgs.fa_insert( t );
		} else // redefinition
			OutputErrMsg( "error in line %d: function '%s()' redefinition", t->lineno, (LPCTSTR)t->szName );
		break;
	case kVarDec:
	case kParam:
		if( m_SymbolTable.st_lookup( t->szName, t->szScope ) == -1 )
			// not defined, so add it to the symbol table
			m_SymbolTable.st_insert( t->szName, t->szScope, t->type, t->lineno, location++, t->bArray );
		else // redefinition
			OutputErrMsg( "error in line %d: variable '%s' redefinition", t->lineno, (LPCTSTR)t->szName );
		break;
	case kStmt:
		switch( t->kind.stmt ) {
		case kLabel:
			if( m_SymbolTable.st_lookup( t->szName, t->szScope ) == -1 )
				// first time encountered in the scope, add it to the symbol table
				m_SymbolTable.st_insert( t->szName, t->szScope, _LABEL, t->lineno, location++ );
			else // label redifition
				OutputErrMsg( "error in line %d: lable '%s' in scope '%s' has already defined", 
							  t->lineno, (LPCTSTR)t->szName, (LPCTSTR)t->szScope );
			break;
		case kGoto:
			if( m_SymbolTable.st_lookup( t->szName, t->szScope ) == -1 )
				// label undeclared
				OutputErrMsg( "error in line %d: lable '%s' in scope '%s' undeclared",
							  t->lineno, (LPCTSTR)t->szName, (LPCTSTR)t->szScope );
			else
				m_SymbolTable.st_insert( t->szName, t->szScope, _LABEL, t->lineno, 0 );
			break;
		case kCall:
			if( m_SymbolTable.st_lookup( t->szName, t->szScope ) == -1 )
				OutputErrMsg( "error in line %d: unresolved external symbol %s", t->lineno, t->szName );
			else
				m_SymbolTable.st_insert( t->szName, t->szScope, _ID, t->lineno, 0 );
		default:
			break;
		}
		break;
	case kExp:
		switch( t->kind.exp ) {
		case kID:
			if( m_SymbolTable.st_lookup( t->szName, t->szScope ) == -1 &&
				m_SymbolTable.st_lookup( t->szName, CString("global") ) == -1 )
				// undeclared
				OutputErrMsg( "error in line %d: '%s': undeclared identifier", t->lineno, (LPCTSTR)t->szName );
			else if( m_SymbolTable.st_lookup( t->szName, t->szScope ) != -1 ) {
				// local variable
				if( t->father && (t->father->nodekind != kStmt || t->father->kind.stmt != kCall)/* not in call statement */ &&
					t->bArray != m_SymbolTable.st_lookup_isarray(t->szName, t->szScope) ) {
					// one is array but the other is not
					OutputErrMsg( "error in line %d: '%s' is%sdeclared as array", t->lineno,
								  (LPCTSTR)t->szName, t->bArray ? " not " : " " );
					break;
				}
				m_SymbolTable.st_insert( t->szName, t->szScope, t->type, t->lineno, 0 );
			} else { // global variable
				t->szScope = _T("global");
				if( t->father && (t->father->nodekind != kStmt || t->father->kind.stmt != kCall)/* not in call statement */ &&
					t->bArray != m_SymbolTable.st_lookup_isarray(t->szName, t->szScope) ) {
					// one is array but the other is not
					OutputErrMsg( "error in line %d: '%s' is%sdeclared as array", t->lineno,
								  (LPCTSTR)t->szName, t->bArray ? " not " : " " );
					break;
				}
				m_SymbolTable.st_insert( t->szName, t->szScope, t->type, t->lineno, 0 );
			}
			break;
		default:
			break;
		}
	default:
		break;
	}
}

// Procedure checkNode performs type checking at a single tree node
void CAnalyzer::checkNode( CTreeNode* t )
{
	CTreeNode* p = t;
	int ret;

	switch( t->nodekind ) {
	case kStmt:
		switch( t->kind.stmt ) {
		case kRead:
			if( t->child[0] == NULL ) {
				OutputErrMsg( "fatal error: compiler error!" );
				break;
			}
			t->type = t->child[0]->type;
			if( t->type != _CHAR && t->type != _INT && t->type != _FLOAT )
				OutputErrMsg( "error in line %d: read a character, int or float number", t->lineno );
			break;
		case kWrite:
			if( t->child[0] == NULL ) {
				OutputErrMsg( "fatal error: compiler error!" ); break;
			}
			t->type = t->child[0]->type;
			if( t->type != _CHAR && t->type != _INT && t->type != _FLOAT )
				OutputErrMsg( "error in line %d: read a character, int or float number", t->lineno );
			break;
		case kReturn:
			if( t->child[0] == NULL ) { // 'return' returns 'void'
				if( m_SymbolTable.st_lookup_type(t->szName, CString("global")) != _VOID )
					OutputErrMsg( "error in line %d: function '%s' must return a value", 
					              t->lineno, (LPCTSTR)t->szName );
			}
			break;
		case kBreak:
			while( p->father && (p->father->nodekind != kStmt || p->father->kind.stmt != kWhile) )
				p = p->father;
			if( p->father == NULL )
				// 'break' is not within a while statment
				OutputErrMsg( "error in line %d: illegal 'break'", t->lineno );
			break;
		case kContinue: // treat it like kBreak
			while( p->father && (p->father->nodekind != kStmt || p->father->kind.stmt != kWhile) )
				p = p->father;
			if( p->father == NULL )
				// 'continue' is not within a while statment
				OutputErrMsg( "error in line %d: illegal 'continue'", t->lineno );
			break;
		case kCall:
			// check if its arguments match declaration
			ret = m_FunArgs.fa_check( t );
			if( ret != -3 ) {// errors 
				if( ret >= 0 )
					OutputErrMsg( "error in line %d: function '%s()' takes %d parameters", t->lineno, (LPCTSTR)t->szName, ret );
				else if( ret == -1 )
					OutputErrMsg( "error in line %d: function '%s()' is not declared", t->lineno, (LPCTSTR)t->szName );
				else
					OutputErrMsg( "error in line %d: arguments type not match with function '%s()' declaration", t->lineno, (LPCTSTR)t->szName );
				break;
			}
			t->type = m_SymbolTable.st_lookup_type( t->szName, t->szScope );
			break;
		default:
			break;
		}
		break;
	case kExp:
		switch( t->kind.exp ) {
		case kOp:// assign a type to this op node
			if( t->type == LOGICAL_NOT || t->type == ASSIGN )
				t->type = t->child[0]->type;
			else {
				// the others are binary operations, 
				// and the type should be the subexpression with higher precision
				if( t->child[0]->type == _VOID || t->child[1]->type == _VOID )
					OutputErrMsg( "error in line %d: illegal use of type 'void'", t->lineno );
				else if( t->child[0]->type == _FLOAT || t->child[1]->type == _FLOAT )
					t->type = _FLOAT;
				else if( t->child[0]->type == _INT || t->child[1]->type == _INT )
					t->type = _INT;
				else
					t->type = _CHAR;
			}
			break;
		case kID:
			// find the type in the symbol table, assign it to the node
			t->type = m_SymbolTable.st_lookup_type( t->szName, t->szScope );
			t->bArray = m_SymbolTable.st_lookup_isarray( t->szName, t->szScope );
			break;
		default:
			break;
		}
	default:
		break;
	}
}
