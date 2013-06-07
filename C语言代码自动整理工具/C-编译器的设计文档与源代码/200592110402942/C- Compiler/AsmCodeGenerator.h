#ifndef _ASMCODEGENERATOR_H_
#define _ASMCODEGENERATOR_H_

#include "Analyzer.h"

class CAsmCodeGenerator
{
public:
	CAsmCodeGenerator( CString& str );
	~CAsmCodeGenerator();

// Operation
public:
	void			GenerateAsmCode( LPCTSTR lpszPathName );

// help routines
private:
	void			emitComment( char* format, ... );
	void			emitLabel( char* format, ... );
	void			emitCode( char* format, ... );
	void			emitCode( CString& code );

	// 80x86 ASM routines
	void			_inline_readc();
	void			_readi();
	void			_writei();

	// code generation routines
	void			genPreSeg();
	void			genData( CTreeNode* p );
	void			genCodeSeg();
	void			genFunc( CTreeNode* pNode );
	void			genLocal( CTreeNode* pNode );
	void			genStmt( CTreeNode* pNode, int lab1 = 0, int lab2 = 0 );

	BOOL			isAddr( CTreeNode* pNode );

private:
	CAnalyzer*		m_pAnalyzer;

	CFile			m_file;
	int				label;// generator unique lable;
};

#endif // _ASMCODEGENERATOR_H_