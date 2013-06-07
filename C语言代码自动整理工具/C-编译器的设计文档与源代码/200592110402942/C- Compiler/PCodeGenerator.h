#ifndef _PCODEGENERATOR_H_
#define _PCODEGENERATOR_H_

#include "Analyzer.h"

class CPCodeGenerator
{
public:
	CPCodeGenerator( CString& str );
	~CPCodeGenerator();

// Operations
public:
	void			GeneratePCode( LPCTSTR lpszPathName );

// help routines
private:
	void			emitComment( char* format, ... );
	void			emitCode( char* format, ... );
	void			emitCode( CString& code );

	void			genPCode( CTreeNode* t, BOOL addr = FALSE, int lab1 = 0, int lab2 = 0 );

private:
	CAnalyzer*		m_pAnalyzer;
	CTreeNode*		m_pProgram;

	CFile			m_file;
	int				label;// generator unique lable;
};

#endif // _PCODEGENERATOR_H_