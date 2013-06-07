// SymbolTable.cpp : implementation file
//

#include "stdafx.h"
#include "cminus.h"

#include "SymbolTable.h"

/*  *    CSymbolTable
    *    Construction & destruction
  *	* *
   ***   Programer: Â½Ïþ´º
    *    Date:		2004.05.20             */

CSymbolTable::CSymbolTable()
{
	initHashTable();
}

CSymbolTable::~CSymbolTable()
{
	for( int i = 0; i < SIZE; i++ ) if( hashTable[i] ) delete hashTable[i];
}

/*  *    CSymbolTable
    *    help routines
  *	* *
   ***   Programer: Â½Ïþ´º
    *    Date:		2004.05.20             */

// hash function
int CSymbolTable::hash( LPCTSTR key )
{
	int temp, i;

	for( temp = 0, i = 0; key[i] != '\0'; i++ )
		temp = ((temp << SHIFT) + key[i]) % SIZE;

	return temp;
}

void CSymbolTable::initHashTable()
{
	for( int i = 0; i < SIZE; i++ ) hashTable[i] = NULL;
}

void CSymbolTable::deleteHashTable()
{
	for( int i = 0; i < SIZE; i++ ) 
		if( hashTable[i] ) {
			delete hashTable[i];
			hashTable[i] = NULL;
		}
}

// write a string to m_file, m_file must exist
void CSymbolTable::write( char* format, ... )
{
	ASSERT( m_file.m_hFile != CFile::hFileNull );

	va_list params;
	static char buf[ 1024 ];
	
	va_start( params, format );
	_vsnprintf( buf, 1020, format, params );
	va_end( params );

	try {
		m_file.Write( buf, strlen(buf) );
	} catch( CFileException* ) {
		OutputErrMsg( "failed to write to file: %s", (LPCTSTR)m_file.GetFilePath() );
	}
}

/*  *    CSymbolTable
    *    public functions
  *	* *
   ***   Programer: Â½Ïþ´º
    *    Date:		2004.05.20             */

// insert a node into the hash table,
// memloc is inserted only the first time, otherwise ignored
void CSymbolTable::st_insert( CString& name, CString& scope, enum TokenType type,
							  int lineno, int memloc, BOOL bArray )
{
	int h = hash( (LPCTSTR)name );
	BucketListRec* l = hashTable[h];

	while( l && ((l->name != name) || (l->scope != scope)) ) l = l->next;
	if( l == NULL ) {
		// variable not yet in table
		l = new BucketListRec();
		l->name = name;
		l->scope = scope;
		l->type = type;
		l->memloc = memloc;
		l->bArray = bArray;
		l->lineno = new LineListRec();
		l->lineno->lineno = lineno;
		l->next = hashTable[h];
		hashTable[h] = l;
	} else {
		// found in table, so just add line number
		LineListRec* t = l->lineno;
		while( t->next ) t = t->next;
		t->next = new LineListRec();
		t->next->lineno = lineno;
	}
}

// lookup a node with specified name and scope from the hash table,
// return the memloc
int CSymbolTable::st_lookup( CString& name, CString& scope )
{
	int h = hash( (LPCTSTR)name );
	BucketListRec* l = hashTable[h];

	while( l && ((l->name != name) || (l->scope != scope)) ) l = l->next;
	return (l == NULL) ? -1 : l->memloc;
}

// check if it is array
BOOL CSymbolTable::st_lookup_isarray( CString& name, CString& scope )
{
	int h = hash( (LPCTSTR)name );
	BucketListRec* l = hashTable[h];

	while( l && ((l->name != name) || (l->scope != scope)) ) l = l->next;
	return (l == NULL) ? FALSE : l->bArray;
}

// return the type of the specified table node
enum TokenType CSymbolTable::st_lookup_type( CString& name, CString& scope )
{
	int h = hash( (LPCTSTR)name );
	BucketListRec* l = hashTable[h];

	while( l && ((l->name != name) || (l->scope != scope)) ) l = l->next;
	return (l == NULL ) ? _ERROR : l->type;
}

// print a formatted listing of the symbol table contents to lpszPathName
void CSymbolTable::PrintSymbolTable( LPCTSTR lpszPathName )
{
	// create file
	CFileException e;
	if( !m_file.Open( lpszPathName, CFile::modeCreate | CFile::modeReadWrite, &e ) ) {
		OutputErrMsg( "\r\nfailed to create file for printing symbol table: %s", lpszPathName );
		return;
	}

	write( "           Scope        Variable Name     Type     Location    Line Numbers\r\n" );
	write( "       -------------    -------------    ------    --------    ------------\r\n" );
	for( int i = 0; i < SIZE; i++ )
		if( hashTable[i] != NULL ) {
			BucketListRec* l = hashTable[i];
			while( l ) {
				write( "%18s", (LPCTSTR)l->scope );
				write( "%17s", (LPCTSTR)l->name );
				if( l->type == _LABEL )
					write( "%11s", "label" );
				else
					write( "%11s", (LPCTSTR)(ReservedKeywordList[l->type] + ((l->bArray) ? "[]" : "")) );
				write( "%12d     ", l->memloc );
				LineListRec* t = l->lineno;
				while( t ) {
					write( "%3d ", t->lineno );
					t = t->next;
				}
				write( "\r\n" );
				l = l->next;
			}
		}

		m_file.Close();
}
