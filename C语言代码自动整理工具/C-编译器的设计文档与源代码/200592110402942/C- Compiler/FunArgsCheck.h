#ifndef _FUNARGSCHECK_H_
#define _FUNARGSCHECK_H_

#include "Parser.h"

class ParamListRec
{
public:
	enum TokenType	type;
	BOOL			bArray;
	ParamListRec*	next;
public:
	ParamListRec() : bArray( FALSE ), next( NULL ) {}
	ParamListRec( enum TokenType t, BOOL b ) : type( t ), bArray( b ), next( NULL ) {}
	~ParamListRec() { if( next ) delete next; }
};

class FunDecListRec
{
public:
	CString			name;
	enum TokenType	type;
	int				count;
	ParamListRec*	params;
	FunDecListRec* 	next;
public:
	FunDecListRec() : count( 0 ), next( NULL ) {}
	FunDecListRec( CString& s, enum TokenType t ) : name( s ), type( t ), count( 0 ), next( NULL ) {}
	~FunDecListRec() { if( next ) delete next; }
};

class CFunArgsCheck
{
public:
	CFunArgsCheck();
	~CFunArgsCheck();

public:
	void	deleteList();

	void	fa_insert( CTreeNode* pNode );
	int		fa_check( CTreeNode* pNode );
	
private:
	FunDecListRec	*first, *last;
};

#endif // _FUNARGSCHECK_H_