#ifndef _SYMBOLTABLE_H_
#define _SYMBOLTABLE_H_

#include "parser.h"

// SIZE is the size of the hash table
#define SIZE 211

// SHIFT is the power of two used as multiplier in hash function
#define SHIFT 4

// the list of line numbers of the source code in which a variable is referenced
class LineListRec
{
public:
	int					lineno;
	LineListRec*		next;

public:
	// initiation
	LineListRec() : lineno( 0 ), next( NULL ) {}
	// for convenient self-destruction
	~LineListRec() { if( next ) delete next; }
};

// The record in the bucket lists for each variable, including name, 
// assigned memory location, and the list of line numbers in which
// it appears in the source code
class BucketListRec
{
public:
	CString				name;	// variable name
	CString				scope;	// function scope
	enum TokenType		type;
	int					memloc;	// memory location for variable
	BOOL				bArray; // for array checking
	LineListRec*		lineno;
	BucketListRec*		next;

public:
	// initiation
	BucketListRec() : memloc( 0 ), lineno( NULL ), next( NULL ) {}
	// for convenient self-destruction
	~BucketListRec()
	{
		if( lineno ) delete lineno;
		if( next ) delete next;
	}
};

class CSymbolTable
{
public:
	CSymbolTable();
	~CSymbolTable();

// Operations
public:
	void		deleteHashTable();

	void		st_insert( CString& name, CString& scope, enum TokenType type,
		                   int lineno, int memloc, BOOL bArray = FALSE );
	int			st_lookup( CString& name, CString& scope );
	BOOL		st_lookup_isarray( CString& name, CString& scope );
	enum TokenType st_lookup_type( CString& name, CString& scope );
	void		PrintSymbolTable( LPCTSTR lpszPathName );

// help routines
private:
	inline int	hash( LPCTSTR key );
	void		initHashTable();

	void		write( char* format, ... );

private:
	BucketListRec*	hashTable[SIZE];
	CFile		m_file;
};

#endif // _SYMBOLTABLE_H_