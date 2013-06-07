// parser.cpp : implementation file
//

#include "stdafx.h"
#include "cminus.h"

#include "parser.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/*  *    CParser
    *    Construction & destruction
  *	* *
   ***   Programer: Â½Ïþ´º
    *    Date:		2004.05.18             */

// construction
CParser::CParser( CString& str )
{
	m_pScaner = new CScaner( str );
	m_pProgram = NULL;
	indent = -1;
}

// destruction
CParser::~CParser()
{
	delete m_pScaner;
	if( m_pProgram ) delete m_pProgram;
	if( m_fTraceFile.m_hFile != CFile::hFileNull ) 
		m_fTraceFile.Close();
}

/*  *    CParser
    *    public functions
  *	* *
   ***   Programer: Â½Ïþ´º
    *    Date:		2004.05.19             */

// build the parse tree
CTreeNode* CParser::BuildSyntaxTree()
{
	return (m_pProgram = program());
}

// trace the result of parse tree
void CParser::Trace( LPCTSTR lpszPathName )
{
	// build the syntax tree
	if( !m_pProgram ) m_pProgram = program();

	if( bErrFlag ) 
		OutputPhaseMsg( "\r\nerrors occur while parsing, stop printing the syntax tree" );
	else {
		OutputPhaseMsg( "successfully build the syntax tree! printing it..." );
		// create file
		CFileException e;
		if( !m_fTraceFile.Open( lpszPathName, CFile::modeCreate | CFile::modeReadWrite, &e ) ) {
			OutputErrMsg( "failed to create parse trace file: %s", lpszPathName );
			return;
		}
		// print the syntax tree
		PrintTree( m_pProgram );
	}
}

/*  *    CParser
    *    Help routines
  *	* *
   ***   Programer: Â½Ïþ´º
    *    Date:		2004.05.18             */

// construct a new node
CTreeNode* CParser::newNode( NodeKind kind, enum TokenType type, CString& ID )
{
	CTreeNode* t = new CTreeNode();
	t->lineno	 = m_pScaner->LineNo();
	t->nodekind  = kind;
	t->type		 = type;
	t->szName	 = ID;
	t->szScope	 = m_szScope;
	return t;
}

// construct a new statment node
CTreeNode* CParser::newStmtNode( StmtKind kind, CString& ID )
{
	CTreeNode* t = new CTreeNode();
	t->lineno	 = m_pScaner->LineNo();
	t->nodekind  = kStmt;
	t->kind.stmt = kind;
	t->type		 = _NONE;
	t->szName	 = ID;
	t->szScope	 = m_szScope;
	return t;
}

// construct a new expression node
CTreeNode* CParser::newExpNode( ExpKind kind, enum TokenType type, CString& ID )
{
	CTreeNode* t = new CTreeNode();
	t->lineno	 = m_pScaner->LineNo();
	t->nodekind  = kExp;
	t->kind.exp  = kind;
	t->type		 = type;
	t->szName	 = ID;
	t->szScope	 = m_szScope;
	return t;
}

// get the next token, check if its type is expected
BOOL CParser::match( enum TokenType type )
{
	m_token = m_pScaner->NextToken();
	return (m_token.type == type);
}

// for error recovery
void CParser::ConsumeUntil( enum TokenType type )
{
	while( m_token.type != type && m_token.type != _EOF )
		m_token = m_pScaner->NextToken();
}

void CParser::ConsumeUntil( enum TokenType type1, enum TokenType type2 )
{
	while( m_token.type != type1 && m_token.type != type2 && m_token.type != _EOF )
		m_token = m_pScaner->NextToken();
}

/*  *    CParser
    *    functions for all grammars
  *	* *
   ***   Programer: Â½Ïþ´º
    *    Date:		2004.05.18             */

// Grammar:
// 1. program->declaration_list
CTreeNode* CParser::program()
{
	return declaration_list();
}

// Grammar:
// 2. declaration_list->declaration_list declaration | declaration
CTreeNode* CParser::declaration_list()
{
	CTreeNode *first = NULL, *last = NULL, *temp = NULL;
	m_token = m_pScaner->NextToken();
	while( m_token.type != _EOF ) {
		if( m_token.type != _CHAR && m_token.type != _INT &&
			m_token.type != _VOID && m_token.type != _FLOAT ) {
			//throw _error( ERROR_INVALID_TYPE, m_pScaner->LineNo(), m_token.str );
			OutputErrMsg( "error in line %d: invalid type '%s'",
				m_pScaner->LineNo(), (LPCTSTR)m_token.str );
			ConsumeUntil( SEMI/* ';' */, RBRACE/* '}' */ );// error recovery
		} else if( (temp = declaration()) != NULL ) {
			// link all declarations together
			if( !first ) { first = temp; last = temp->LastSibling(); }
			else { last->sibling = temp; last = temp->LastSibling(); }
		}
		// read the next token
		m_token = m_pScaner->NextToken();
	}
	return first;
}

// Grammar:
// 3. declaration->var_declaration | fun_declaration
// m_token is a supported type-identifier token
CTreeNode* CParser::declaration()
{
	m_szScope = _T( "global" );// global function or variable declaration
	CTreeNode* temp = NULL;

	TypeToken = m_token;
	IDToken = m_token = m_pScaner->NextToken();
	if( IDToken.type != _ID ) {
		//throw _error( ERROR_DECLARATION, m_pScaner->LineNo(), IDToken.str );
		OutputErrMsg( "error in line %d: \"%s\" is a reserved token",
			m_pScaner->LineNo(), (LPCTSTR)IDToken.str );
		ConsumeUntil( SEMI, RBRACE );
	} else {
		m_token = m_pScaner->NextToken();// '(', ';', '[', ',' or error
		if( m_token.type == LPARAN ) temp = fun_declaration();
		else if( m_token.type == SEMI || m_token.type == LSQUARE || m_token.type == COMMA )
			temp = var_declaration();
		else {
			// throw _error( ERROR_SEMICOLON_MISS, m_pScaner->LineNo(), IDToken.str );
			OutputErrMsg( "error in line %d: missing ';' after identifier \"%s\"", 
				m_pScaner->LineNo(), (LPCTSTR)IDToken.str );
			ConsumeUntil( SEMI, RBRACE );
		}
	}

	return temp;
}

// Grammar:
// 4. var_declaration->type_specifier ID(, ...)`;` | type_specifier ID `[` NUM `]`(, ...)`;`
// 5. type_specifier->`int` | `void` | `char`, actually this step is in declaration_list()
// m_token.str == ";" "," or "["
CTreeNode* CParser::var_declaration()
{
	CTreeNode* temp = newNode( kVarDec, TypeToken.type, IDToken.str );

	if( m_token.type == LSQUARE ) {// '['
		m_token = m_pScaner->NextToken();// NUM
		if( m_token.type != _NUM ) {
			OutputErrMsg( "error in line %d: syntax error in declaration of array %s[], missing array size",
				m_pScaner->LineNo(), (LPCTSTR)IDToken.str );
			delete temp;
			ConsumeUntil( SEMI, RBRACE );// error recovery
			return NULL;
		}

		temp->bArray = TRUE;
		temp->iArraySize = m_pScaner->GetIntNumValue();
		
		if( !match(RSQUARE) ) {// `]`
			OutputErrMsg( "error in line %d: syntax error in declaration of array %s[], missing ']'",
				m_pScaner->LineNo(), (LPCTSTR)IDToken.str );
			m_pScaner->PushBack();// error recovery
		}
		m_token = m_pScaner->NextToken();// should be ';' or ','
	}
	if( m_token.type == COMMA ) {
		IDToken = m_token = m_pScaner->NextToken();// ID or error
		if( IDToken.type != _ID ) {
			OutputErrMsg( "error in line %d: \"%s\" is a reserved token",
				m_pScaner->LineNo(), (LPCTSTR)IDToken.str );
			ConsumeUntil( SEMI, RBRACE );// error recovery
			return temp;
		}
		m_token = m_pScaner->NextToken();// ';', '[', ',' or error
		if( m_token.type == SEMI || m_token.type == LSQUARE || m_token.type == COMMA )
			temp->sibling = var_declaration();// link following variable declarations
		else {
			OutputErrMsg( "error in line %d: missing ';' after identifier \"%s\"", 
				m_pScaner->LineNo(), (LPCTSTR)IDToken.str );
			m_pScaner->PushBack();// error recovery
			return temp;
		}
	} else if( m_token.type != SEMI ) {// m_token should be ';' now
		OutputErrMsg( "error in line %d: bad declaration sequence, missing ';'", m_pScaner->LineNo() );
		ConsumeUntil( SEMI, RBRACE );
	}
	
	return temp;
}

// Grammar:
// 6. fun_declaration->type_specifier ID `(` params `)` compound_stmt
// m_token.str == "(", TypeToken contains type_specifier, IDToken contains ID
CTreeNode* CParser::fun_declaration()
{
	CTreeNode* temp = newNode( kFunDec, TypeToken.type, IDToken.str );

	// update function scope
	m_szScope = IDToken.str;

	// params
	CTreeNode* p = temp->child[0] = params();
	if( p ) p->father = temp;
	while( p && p->sibling ) {
		p = p->sibling;	p->father = temp;
	}

	if( !match(RPARAN) ) {
		OutputErrMsg( "error in line %d: missing ')' in function \"%s\"(...) declaration",
			          m_pScaner->LineNo(), (LPCTSTR)m_token.str );
		m_pScaner->PushBack();
	}
	// compound statements
	p = temp->child[1] = compound_stmt();
	if( p ) p->father = temp;
	while( p && p->sibling ) {
		p = p->sibling; p->father = temp;
	}

	return temp;
}

// Grammar:
// 7. params->param_list | `void` | empty, `void` is thought as empty
// 8. param_list->param_list `,` param | param
// 9. param->type_specifier ID | type_specifier ID `[` `]`
// m_token.str == "("
CTreeNode* CParser::params()
{
	CTreeNode *first = NULL, *temp = NULL;

	TypeToken = m_token = m_pScaner->NextToken();// type-specifier or ')'
	if( m_token.type == RPARAN ) {
		m_pScaner->PushBack();
		return NULL;
	}
	if( TypeToken.type == _VOID )
		if( match( RPARAN ) ) {
			m_pScaner->PushBack();
			return NULL;
		} else m_pScaner->PushBack();// is not ')', push it back
	while( TypeToken.type == _INT || TypeToken.type == _CHAR ||
		   TypeToken.type == _VOID || TypeToken.type == _FLOAT ) {
		IDToken = m_token = m_pScaner->NextToken();
		if( IDToken.type != _ID ) {
			OutputErrMsg( "error in line %d: invalid parameter \"%s\"",
						  m_pScaner->LineNo(), (LPCTSTR)IDToken.str );
		} else {
			temp = newNode( kParam, TypeToken.type, IDToken.str );
			temp->sibling = first;// the FIRST parameter is the LAST sibling node
			first = temp;
		}
		m_token = m_pScaner->NextToken();
		if( m_token.type == LSQUARE ) {// '['
			temp->bArray = TRUE;
			if( !match( RSQUARE ) ) {//']'
				OutputErrMsg( "error in line %d: bad array parameter, missing ']'", m_pScaner->LineNo() );
				ConsumeUntil( COMMA, RPARAN );// error recovery
			} else
				m_token = m_pScaner->NextToken();// should be ',' or ')'
		}
		if( m_token.type == RPARAN ) break;// ')'
		else if( m_token.type == COMMA )// ','
			TypeToken = m_token = m_pScaner->NextToken();
		else {// just break
			//OutputErrMsg( "error in line %d: bad function parameters", m_pScaner->LineNo() );
			//ConsumeUntil( RPARAN );// error recovery
			break;
		}
	}
	m_pScaner->PushBack();// the next token should be ')'

	return first;
}

// Grammar:
// 10. compound_stmt->`{` loal_declarations statement_list `}` | expression_stmt
// the next token should be '{'
CTreeNode* CParser::compound_stmt()
{
	CTreeNode *first = NULL, *last = NULL, *temp = NULL;
	BOOL bHasNoBraces = FALSE;

	if( !match(LBRACE) ) {// match'{'
		// OutputErrMsg( "error in line %d: missing '{'", m_pScaner->LineNo() );
		bHasNoBraces = TRUE;
		m_pScaner->PushBack();// error recovery
	}

	// local_declarations
	while( 1 ) {
		TypeToken = m_token = m_pScaner->NextToken();
		if( m_token.type == _CHAR || m_token.type == _INT ||
			m_token.type == _VOID || m_token.type == _FLOAT )
			temp = local_declarations();
		else { m_pScaner->PushBack(); break; }
		if( bHasNoBraces ) return temp;// has no braces, return when reach the first ';'
		if( temp )
			// link all local_declarations together
			if( !first ) { first = temp; last = temp->LastSibling(); }
			else { last->sibling = temp; last = temp->LastSibling(); }
	}

	// statement_list
	// m_token contains the first token of statement_list
	m_token = m_pScaner->NextToken();
	while( 1 ) {
		temp = NULL;
		if( m_token.type == RBRACE ) {
			if( bHasNoBraces ) OutputErrMsg( "error in line %d: unpaired '}'", m_pScaner->LineNo() );
			break;// '}'
		}
		if( m_token.type == _EOF ) {
			OutputErrMsg( "error in line %d: missing '}'", m_pScaner->LineNo() );
			m_pScaner->PushBack();
			break;
		}
		switch( m_token.type ) {
		case _READ:
			temp = read_stmt();			break;
		case _WRITE:
			temp = write_stmt();		break;
		case _PRINTF:
			temp = printf_stmt();		break;
		case SEMI:// ';'
		case _NUM:
		case _CHARACTER:
		case LOGICAL_NOT:
		case LPARAN:
			temp = expression_stmt();	break;
		case _ID:
			temp = subcompound_stmt();	break;
		case _IF:
			temp = if_stmt();			break;
		case _WHILE:
			temp = while_stmt();		break;
		case _FOR:
			temp = for_stmt();			break;
		case _GOTO:
			temp = goto_stmt();			break;
		case _BREAK:
			temp = break_stmt();		break;
		case _CONTINUE:
			temp = continue_stmt();		break;
		case _RETURN:
			temp = return_stmt();		break;
		case _ELSE:
			OutputErrMsg( "error in line %d: unpaired 'else' statement", m_pScaner->LineNo() );
			ConsumeUntil( SEMI, RBRACE );
			break;
		default:
			OutputErrMsg( "error in line %d: undefined symbol \"%s\"",
						  m_pScaner->LineNo(), (LPCTSTR)m_token.str );
			ConsumeUntil( SEMI, RBRACE );
		}
		if( bHasNoBraces ) return temp;// has no braces, return when reach the first ';'
		if( temp )
			// link all statements together
			if( !first ) { first = temp; last = temp->LastSibling(); }
			else { last->sibling = temp; last = temp->LastSibling(); }
		m_token = m_pScaner->NextToken();
	}

	return first;
}

// Grammar:
// 11. local_declarations->local_declarations var_declaration | var_declaration
// m_token is a supported type-specifier token
CTreeNode* CParser::local_declarations()
{
	CTreeNode* temp = NULL;

	IDToken = m_token = m_pScaner->NextToken();// ID or error
	if( IDToken.type != _ID ) {
		OutputErrMsg( "error in line %d: \"%s\" is a reserved token",
			m_pScaner->LineNo(), (LPCTSTR)IDToken.str );
		ConsumeUntil( SEMI );// error recovery
		return NULL;
	}
	m_token = m_pScaner->NextToken();// ';', '[', ',' or error
	if( m_token.type == SEMI || m_token.type == LSQUARE || m_token.type == COMMA )
		temp = var_declaration();
	else {
		OutputErrMsg( "error in line %d: missing ';' after identifier \"%s\"", 
			m_pScaner->LineNo(), (LPCTSTR)IDToken.str );
		m_pScaner->PushBack();// error recovery
	}
	return temp;
}

// Grammar:
// 12. `read` `(` var `)` `;`
// m_token.str == "read"
CTreeNode* CParser::read_stmt()
{
	CTreeNode* temp = NULL;
	
	if( !match(LPARAN) ) {// '('
		OutputErrMsg( "error in line %d: syntax error, missing '('", m_pScaner->LineNo() );
		ConsumeUntil( SEMI, RBRACE );// error recovery
		return NULL;
	}
	IDToken = m_token = m_pScaner->NextToken();
	if( m_token.type != _ID ) {
		OutputErrMsg( "error in line %d: \"%s\" bad arguments", m_pScaner->LineNo(), (LPCTSTR)m_token.str );
		ConsumeUntil( SEMI, RBRACE );// error recovery
		return NULL;
	}
	temp = newStmtNode( kRead, CString("read") );
	if( (temp->child[0] = var()) != NULL ) temp->child[0]->father = temp;
	if( !match(RPARAN) ) {// ')'
		OutputErrMsg( "error in line %d: syntax error, missing ')'", m_pScaner->LineNo() );
		ConsumeUntil( SEMI, RBRACE );// error recovery
		return temp;
	}
	if( !match(SEMI) ) {// ';'
		OutputErrMsg( "error in line %d: syntax error, missing ';'", m_pScaner->LineNo() );
		m_pScaner->PushBack();// error recovery
	}
	return temp;
}

// Grammar:
// 13. `write` `(` expression `)` `;`
// m_token.str == "write"
CTreeNode* CParser::write_stmt()
{
	CTreeNode* temp = NULL;
	
	if( !match(LPARAN) ) {// '('
		OutputErrMsg( "error in line %d: syntax error, missing '('", m_pScaner->LineNo() );
		ConsumeUntil( SEMI, RBRACE );// error recovery
		return NULL;
	}
	temp = newStmtNode( kWrite, CString("write") );
	m_token = m_pScaner->NextToken();
	// m_token contains the first token of expression
	if( (temp->child[0] = expression()) != NULL ) temp->child[0]->father = temp;
	if( !match(RPARAN) ) {// ')'
		OutputErrMsg( "error in line %d: syntax error, missing ')'", m_pScaner->LineNo() );
		ConsumeUntil( SEMI, RBRACE );// error recovery
		return temp;
	}
	if( !match(SEMI) ) {// ';'
		OutputErrMsg( "error in line %d: syntax error, missing ';'", m_pScaner->LineNo() );
		m_pScaner->PushBack();// error recovery
	}
	return temp;
}

// Grammar:
// 14. `printf` `(` `"` STRING `"` `)` `;`
// m_token.str == "printf"
CTreeNode* CParser::printf_stmt()
{
	CTreeNode* temp = NULL;
	
	if( !match(LPARAN) ) {// '('
		OutputErrMsg( "error in line %d: syntax error, missing '('", m_pScaner->LineNo() );
		ConsumeUntil( SEMI, RBRACE );// error recovery
		return NULL;
	}
	m_token = m_pScaner->NextToken();
	if( m_token.type != _STRING ) {
		OutputErrMsg( "error in line %d: arguments should be strings", m_pScaner->LineNo() );
		ConsumeUntil( SEMI, RBRACE );// error recovery
		return NULL;
	}
	temp = newStmtNode( kPrintf, m_token.str );
	if( !match(RPARAN) ) {// ')'
		OutputErrMsg( "error in line %d: syntax error, missing ')'", m_pScaner->LineNo() );
		ConsumeUntil( SEMI, RBRACE );// error recovery
		return temp;
	}
	if( !match(SEMI) ) {// ';'
		OutputErrMsg( "error in line %d: syntax error, missing ';'", m_pScaner->LineNo() );
		m_pScaner->PushBack();// error recovery
	}
	return temp;
}

// Grammar:
// 15. expression_stmt->expression `;` | `;`
// m_token is '!', '(', ID, NUM, CHARACTER or ';'
CTreeNode* CParser::expression_stmt()
{
	if( m_token.type == SEMI ) return NULL;
	CTreeNode* temp = expression();
	if( !match(SEMI) ) {
		OutputErrMsg( "error in line %d: missing ';'", m_pScaner->LineNo() );
		m_pScaner->PushBack();// error recovery
	}

	return temp;
}

// Grammar:
// 16. expression->var `=` expression | logic1_expression
// FIRST( expression ) = { `!`, `(`, ID, NUM, CHARACTER }
// m_token contains the first token of expression
CTreeNode* CParser::expression()
{
	CTreeNode *temp = logic1_expression(), *p = temp;
	m_token = m_pScaner->NextToken();
	if( m_token.type == ASSIGN ) {
		if( temp->type != _ID && temp->type != ASSIGN ) {// left of '=' should be a ID
			OutputErrMsg( "error in line %d: left of '=' syntax error", m_pScaner->LineNo() );
			ConsumeUntil( SEMI, RPARAN );
			delete temp;
			return NULL;
		}
		p = newExpNode( kOp, m_token.type, m_token.str );
		p->child[0] = temp;
		if( p->child[0] ) p->child[0]->father = p;
		m_token = m_pScaner->NextToken();
		p->child[1] = expression();
		if( p->child[1] ) p->child[1]->father = p;
	} else
		m_pScaner->PushBack();

	return p;
}

// Grammar:
// 17. logic1_expression->logic1_expression `||` logic2_expression | logic2_expression
// m_token contains the first token of logic1_expression
CTreeNode* CParser::logic1_expression()
{
	CTreeNode *p = logic2_expression();

	m_token = m_pScaner->NextToken();
	while( m_token.type == LOGICAL_OR ) {
		CTreeNode* temp = newExpNode( kOp, m_token.type, m_token.str );
		temp->child[0] = p;
		p = temp;
		if( p->child[0] ) p->child[0]->father = p;
		m_token = m_pScaner->NextToken();
		if( (p->child[1] = logic2_expression()) ) p->child[1]->father = p;
		m_token = m_pScaner->NextToken();
	}
	m_pScaner->PushBack();// put the next token back

	return p;
}

// Grammar:
// 18. logic2_expression-> logic2_expression `&&` simple_expression | simple_expression
// m_token contains the first token of logic2_expression
CTreeNode* CParser::logic2_expression()
{
	CTreeNode *p = simple_expression();

	m_token = m_pScaner->NextToken();
	while( m_token.type == LOGICAL_AND ) {
		CTreeNode* temp = newExpNode( kOp, m_token.type, m_token.str );
		temp->child[0] = p;
		p = temp;
		if( p->child[0] ) p->child[0]->father = p;
		m_token = m_pScaner->NextToken();
		if( (p->child[1] = simple_expression()) ) p->child[1]->father = p;
		m_token = m_pScaner->NextToken();
	}
	m_pScaner->PushBack();// put the next token back

	return p;
}

// Grammar:
// 19. simple_expression->additive_expression relop additive_expression | additive_expression
// 20. relop-> `<=` | `<` | `>` | `>=` | `==` | `!=`
// m_token contains the first token of simple_expression
CTreeNode* CParser::simple_expression()
{
	CTreeNode* p = additive_expression();
	
	m_token = m_pScaner->NextToken();
	if( m_token.type == NGT || m_token.type == LT || m_token.type == GT ||
		m_token.type == NLT || m_token.type == EQ || m_token.type == NEQ ) {
		CTreeNode* temp = newExpNode( kOp, m_token.type, m_token.str );
		temp->child[0] = p;
		p = temp;
		if( p->child[0] ) p->child[0]->father = p;
		m_token = m_pScaner->NextToken();
		if( (p->child[1] = additive_expression()) ) p->child[1]->father = p;
	} else
		m_pScaner->PushBack();

	return p;
}

// Grammar:
// 21. additive_expression -> additive_expression addop term | term
// 22. addop-> `+` | `-`
// m_token contains the first token of add_expression
CTreeNode* CParser::additive_expression()
{
	CTreeNode* p = term();

	m_token = m_pScaner->NextToken();
	while( m_token.type == PLUS || m_token.type == MINUS ) {
		CTreeNode* temp = newExpNode( kOp, m_token.type, m_token.str );
		temp->child[0] = p;
		p = temp;
		if( p->child[0] ) p->child[0]->father = p;
		m_token = m_pScaner->NextToken();
		if( (p->child[1] = term()) ) p->child[1]->father = p;
		m_token = m_pScaner->NextToken();
	}
	m_pScaner->PushBack();// put the next token back

	return p;
}

// Grammar:
// 23. term->term mulop logic3_expression | logic3_expression
// 24. mulop-> `*` | `/` | `%`
// m_token contains the first token of term
CTreeNode* CParser::term()
{
	CTreeNode* p = logic3_expression();

	m_token = m_pScaner->NextToken();
	while( m_token.type == TIMES || m_token.type == DIV || m_token.type == MOD ) {
		CTreeNode* temp = newExpNode( kOp, m_token.type, m_token.str );
		temp->child[0] = p;
		p = temp;
		if( p->child[0] ) p->child[0]->father = p;
		m_token = m_pScaner->NextToken();
		if( (p->child[1] = logic3_expression()) ) p->child[1]->father = p;
		m_token = m_pScaner->NextToken();
	}
	m_pScaner->PushBack();// put the next token back

	return p;
}

// Grammar:
// 25. logic3_expression-> `!` logic3_expression | factor
// m_token contains the first token of logic3_expression
CTreeNode* CParser::logic3_expression()
{
	CTreeNode *p = NULL, *temp = NULL;

	if( m_token.type == LOGICAL_NOT ) {
		p = newExpNode( kOp, m_token.type, m_token.str );
		m_token = m_pScaner->NextToken();
		if( (temp = factor()) ) {
			p->child[0] = temp;
			p->child[0]->father = p;
		}
	} else
		p = factor();

	return p;
}

// Grammar:
// 26. factor->`(` expression `)` | var | call | NUM
// m_token contains the first token of factor
CTreeNode* CParser::factor()
{
	CTreeNode* temp = NULL;

	switch( m_token.type ) {
	case _NUM:
	case _CHARACTER:
		temp = newExpNode( kConst, m_token.type, m_token.str );
		break;
	case _ID:
		IDToken = m_token;
		m_token = m_pScaner->NextToken();
		if( m_token.type == LPARAN ) temp = call();
		else {
			m_pScaner->PushBack();// push the next token back
			temp = var();
		}
		break;
	case LPARAN:
		m_token = m_pScaner->NextToken();// m_token contain the first token of expression
		temp = expression();
		if( !match(RPARAN) ) {// match ')'
			OutputErrMsg( "error in line %d: missing ')'", m_pScaner->LineNo() );
			m_pScaner->PushBack();// error recovery
		}
		break;
	default:
		OutputErrMsg( "error in line %d: '%s' expression syntax error",
			          m_pScaner->LineNo(), (LPCTSTR)m_token.str );
		ConsumeUntil( SEMI, RBRACE );// error recovery
	}

	return temp;
}

// Grammar:
// 27. var->ID | ID `[` expression `]`
// IDToken contains ID
CTreeNode* CParser::var()
{
	CTreeNode* temp = newExpNode( kID, IDToken.type, IDToken.str );
	m_token = m_pScaner->NextToken();// should be `[` or just push back
	if( m_token.type == LSQUARE ) {
		temp->bArray = TRUE;
		m_token = m_pScaner->NextToken();
		temp->child[0] = expression();
		if( !match(RSQUARE) ) {
			OutputErrMsg( "error in line %d: missing ']'", m_pScaner->LineNo() );
			m_pScaner->PushBack();// error recovery
		}
	} else 
		m_pScaner->PushBack();

	return temp;
}

// Grammar: 
// 28. call->ID `(` args `)`
// m_token.str == "(", IDToken contains ID
CTreeNode* CParser::call()
{
	CTreeNode *p = newStmtNode( kCall, IDToken.str ), *temp = NULL;
	p->szScope = _T("global");
//	CTreeNode* temp = newExpNode( kID, IDToken.type, IDToken.str );
//	p->child[0] = temp;
//	p->child[0]->father = p;
	if( (p->child[0] = args()) ) p->child[0]->father = p;
	temp = p->child[0];
	while( temp && temp->sibling ) {
		temp = temp->sibling;
		temp->father = p;
	}
	if( !match(RPARAN) ) {// match ')'
		OutputErrMsg( "error in line %d: missing ')'", m_pScaner->LineNo() );
		m_pScaner->PushBack();// error recovery
	}

	return p;
}

// Grammar:
// 29. args->args_list | empty
// 30. args_list->args_list `,` expression | expression
// m_token.str == "("
CTreeNode* CParser::args()
{
	CTreeNode *first = NULL, *temp = NULL;

	m_token = m_pScaner->NextToken();
	if( m_token.type == RPARAN ) {
		m_pScaner->PushBack();// push the next token back
		return NULL;
	}
	while( 1 ) {
		if( (temp = expression()) != NULL )
			// link all args together, the LAST argument is the FIRST in the list
			if( !first ) first = temp;
			else { temp->sibling = first; first = temp; }
		m_token = m_pScaner->NextToken();
		if( m_token.type == COMMA ) m_token = m_pScaner->NextToken();
		else break;
	}
	m_pScaner->PushBack();

	return first;
}

// Grammar:
// 31: sub_compoundstmt->ID `:` | call `;` | expression_stmt
// m_token contains the first token of sub_compoundstmt
CTreeNode* CParser::subcompound_stmt()
{
	CTreeNode* temp = NULL;

	IDToken = m_token;
	m_token = m_pScaner->NextToken();
	if( m_token.type == COLON ) {// label
		temp = newStmtNode( kLabel, IDToken.str );
	} else if( m_token.type == LPARAN ) {// call statement
		temp = call();
		if( !match(SEMI) ) {
			OutputErrMsg( "error in line %d: missing ';'", m_pScaner->LineNo() );
			m_pScaner->PushBack();// error recovery
		}
	} else {
		m_pScaner->PushBack();
		m_token = IDToken;
		temp = expression_stmt();
	}

	return temp;
}

// Grammar:
// 32: if_stmt->`if` `(` expression `)` compound_stmt
//              | `if` `(` expression `)` compound_stmt `else` compound_stmt
// m_token.str == "if"
CTreeNode* CParser::if_stmt()
{
	CTreeNode *temp = newStmtNode( kIf, m_token.str ), *p = NULL;

	if( !match(LPARAN) )// match '('
		OutputErrMsg( "error in line %d: missing '(' in 'if' statement", m_pScaner->LineNo() );
	else m_token = m_pScaner->NextToken();
	// m_token should be the first token of expression
	temp->child[0] = expression();
	if( temp->child[0] ) temp->child[0]->father = temp;
	if( !match(RPARAN) ) {// match ')'
		OutputErrMsg( "error in line %d: missing ')' in 'if' statement", m_pScaner->LineNo() );
		m_pScaner->PushBack();
	}
	p = temp->child[1] = compound_stmt();
	if( p ) p->father = temp;
	while( p && p->sibling ) { p = p->sibling; p->father = temp; }
	m_token = m_pScaner->NextToken();
	if( m_token.type == _ELSE ) {
		p = temp->child[2] = compound_stmt();
		if( p ) p->father = temp;
		while( p && p->sibling ) { p = p->sibling; p->father = temp; }
	} else 
		m_pScaner->PushBack();// push the next token back

	return temp;
}

// Grammar:
// 33. while_stmt->`while` `(` expression `)` compound_stmt
// m_token.str == "while"
CTreeNode* CParser::while_stmt()
{
	CTreeNode *temp = newStmtNode( kWhile, m_token.str ), *p = NULL;

	if( !match(LPARAN) )// match '('
		OutputErrMsg( "error in line %d: missing '(' in 'while' statement", m_pScaner->LineNo() );
	else m_token = m_pScaner->NextToken();
	// m_token should be the first token of expression
	temp->child[0] = expression();
	if( temp->child[0] ) temp->child[0]->father = temp;
	if( !match(RPARAN) ) {// match ')'
		OutputErrMsg( "error in line %d: missing ')' in 'while' statement", m_pScaner->LineNo() );
		m_pScaner->PushBack();
	}
	// the next token should be '{'
	p = temp->child[1] = compound_stmt();
	if( p ) p->father = temp;
	while( p && p->sibling ) { p = p->sibling; p->father = temp; }

	return temp;
}

// Grammar:
// 34. for_stmt->`for` `(` var `=` expression `;` expression `;` var `=` expression `)` compound_stmt
// m_token.str == "for"
CTreeNode* CParser::for_stmt()
{
	CTreeNode *temp = NULL, *p1 = NULL, *p2 = NULL, *p3 = NULL;
	
	if( !match(LPARAN) ) // match '('
		OutputErrMsg( "error in line %d: missing '(' in 'for' statement", m_pScaner->LineNo() );
	else m_token = m_pScaner->NextToken();
	// m_token should be var or ';'
	if( m_token.type == SEMI )  {
		p1 = temp = newStmtNode( kWhile, CString("while") );
		m_token = m_pScaner->NextToken();
	} else {
		if( (temp = expression()) == NULL ) {
			OutputErrMsg( "error in line %d: syntax error in the first expression, ignore the whole", m_pScaner->LineNo() );
			ConsumeUntil( RBRACE );
			return NULL;
		} else
			p1 = temp->sibling = newStmtNode( kWhile, CString("while") );

		if( !match(SEMI) ) // match ';'
			OutputErrMsg( "error in line %d: missing the first ';' in 'for' statement", m_pScaner->LineNo() );
		else m_token = m_pScaner->NextToken();
	}
	// m_token should be the first token of expression
	p1->child[0] = expression();
	if( !p1->child[0] ) {
		OutputErrMsg( "error in line %d: missing the second parameter in 'for' statement, ignore the whole", m_pScaner->LineNo() );
		ConsumeUntil( RBRACE );
		if( temp ) delete temp;
		return NULL;
	}
	p1->child[0]->father = p1;
	if( !match(SEMI) ) // match ';'
		OutputErrMsg( "error in line %d: missing the second ';' in 'for' statement", m_pScaner->LineNo() );
	else m_token = m_pScaner->NextToken();
	// m_token should be var
	p2 = expression();
	if( p2 ) p2->father = p1;
	if( !match(RPARAN) ) {// match ')'
		OutputErrMsg( "error in line %d: missing ')' in 'for' statement", m_pScaner->LineNo() );
		m_pScaner->PushBack();
	}
	// the next token should be '{'
	p3 = p1->child[1] = compound_stmt();
	if( p3 ) p3->father = p1;
	if( p3 && p3->sibling ) {
		p3 = p3->sibling; p3->father = p1;
	}
	if( p3 ) p3->sibling = p2;
	else p1->child[1] = p2;

	return temp;
}

// Grammar:
// 35. goto_stmt->`goto` ID `;`
// m_token.str == "goto"
CTreeNode* CParser::goto_stmt()
{
	if( !match(_ID) ) {
		OutputErrMsg( "error in line %d: a label should follow 'goto'", m_pScaner->LineNo() );
		ConsumeUntil( SEMI, RBRACE );// error recovery
		return NULL;
	}
	CTreeNode* temp = newStmtNode( kGoto, m_token.str );
	if( !match(SEMI) ) {
		OutputErrMsg( "error in line %d: missing ';' in 'goto' statement", m_pScaner->LineNo() );
		m_pScaner->PushBack();
	}
	return temp;
}

// Grammar:
// 36. break_stmt->`break` `;`
// m_token.str == "break"
CTreeNode* CParser::break_stmt()
{
	CTreeNode* temp = newStmtNode( kBreak, m_token.str );
	if( !match(SEMI) ) {// match ';'
		OutputErrMsg( "error in line %d: missing ';' in 'break' statement", m_pScaner->LineNo() );
		m_pScaner->PushBack();
	}
	return temp;
}

// Grammar:
// 37. continue_stmt->`continue` `;`
// m_token.str = "continue"
CTreeNode* CParser::continue_stmt()
{
	CTreeNode* temp = newStmtNode( kContinue, m_token.str );
	if( !match(SEMI) ) {
		OutputErrMsg( "error in line %d: missing ';' in 'continue' statement", m_pScaner->LineNo() );
		m_pScaner->PushBack();
	}
	return temp;
}

// Grammar:
// 38. return_stmt->`return` `;` | `return` expression `;`
// m_token.str = "return"
CTreeNode* CParser::return_stmt()
{
	CTreeNode* temp = newStmtNode( kReturn, m_token.str );
	m_token = m_pScaner->NextToken();
	if( m_token.type != SEMI ) {
		temp->child[0] = expression();
		if( !match(SEMI) ) {
			OutputErrMsg( "error in line %d: missing ';' in 'return' statement", m_pScaner->LineNo() );
			m_pScaner->PushBack();
		}
	}
	return temp;
}

/*  *    CParser
    *    print the tree from the specified node to the trace file, the file must be existed
  *	* *
   ***   Programer: Â½Ïþ´º
    *    Date:		2004.05.19             */

void CParser::PrintTree( CTreeNode* pNode )
{
	int i;
	indent++;
	while( pNode != NULL ) {
		for( i = 0; i < indent; i++ ) write( "\t" );
		switch( pNode->nodekind ) {
		case kFunDec:
			write( "Function declaration: " );
			write( ReservedKeywordList[(int)pNode->type] );
			write( " " );
			write( pNode->szName );
			write( "\r\n" );
			break;
		case kVarDec:
			write( "Variable declaration: " );
			write( ReservedKeywordList[(int)pNode->type] );
			write( " " );
			write( pNode->szName );
			if( pNode->bArray )	write( "[%d]", pNode->iArraySize );
			write( "\r\n" );
			break;
		case kParam:
			write( "parameter: " );
			write( ReservedKeywordList[(int)pNode->type] );
			write( " " );
			write( pNode->szName );
			if( pNode->bArray ) write( "[]" );
			write( "\r\n" );
			break;
		case kStmt:
			switch( pNode->kind.stmt ) {
			case kRead:
				write( "call write(), args:\r\n" );
				break;
			case kWrite:
				write( "call read(), args:\r\n" );
				break;
			case kPrintf:
				write( "printf( \"%s\" )\r\n", (LPCTSTR)pNode->szName );
				break;
			case kLabel:
				write( "label: \"%s\"\r\n", (LPCTSTR)pNode->szName );
				break;
			case kGoto:
				write( "goto\r\n" );
				for( i = 0; i <= indent; i++ ) write( "\t" );
				write( "label: \"%s\"\r\n", (LPCTSTR)pNode->szName );
				break;
			case kCall:
				write( "call %s(), args:\r\n", (LPCTSTR)pNode->szName );
				break;
			case kIf:		write( "if\r\n" );				break;
			case kWhile:	write( "while\r\n" );			break;
			case kBreak:	write( "break\r\n" );			break;
			case kContinue:	write( "continue\r\n" );		break;
			case kReturn:	write( "return\r\n" );			break;
			default:		write( "Unknown node kind\r\n" );
			}
			break;
		case kExp:
			switch( pNode->kind.exp ) {
			case kOp:
				write( "Op: %s\r\n", (LPCTSTR)pNode->szName );
				break;
			case kConst:
				write( "const: %s\r\n", (LPCTSTR)pNode->szName );
				break;
			case kID:
				write( "ID: %s", (LPCTSTR)pNode->szName );
				if( pNode->bArray ) {
					pNode = pNode->child[0];
					write( "[%s]", pNode->szName );
				}
				write( "\r\n" );
				break;
			default:
				write( "Unkown node kind\r\n" );
			}
			break;
		default:
			write( "Unkown node kind\r\n" );
		}

		for( i = 0; i < MAX_CHILDREN; i++ ) PrintTree( pNode->child[i] );
		pNode = pNode->sibling;
	}
	indent--;
}

// write the string into the trace file, which must be existed
void CParser::write( char* format, ... )
{
	va_list params;
	static char buf[ 1024 ];
	
	va_start( params, format );
	_vsnprintf( buf, 1020, format, params );
	va_end( params );

	try {
		m_fTraceFile.Write( buf, strlen(buf) );
	} catch( CFileException* ) {
		OutputErrMsg( "failed to write to file: %s", (LPCTSTR)m_fTraceFile.GetFilePath() );
	}
}

void CParser::write( CString& str )
{
	try {
		m_fTraceFile.Write( (LPCTSTR)str, str.GetLength() );
	} catch( CFileException* ) {
		OutputErrMsg( "failed to write to file: %s", (LPCTSTR)m_fTraceFile.GetFilePath() );
	}
}
