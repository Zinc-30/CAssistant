// cminus.h : main header file for the CMINUS application
//

#if !defined(AFX_CMINUS_H__7B450AB3_37F9_4E12_AEF9_7CE77603C0A1__INCLUDED_)
#define AFX_CMINUS_H__7B450AB3_37F9_4E12_AEF9_7CE77603C0A1__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// GLOBAL FUNCTIONS
// Output Bar
extern BOOL bErrFlag;
extern CWnd* pOutputAttachedView;

void ShowOutput();
void ClearOutput();

void OutputPhaseMsg( LPCTSTR msg );
void OutputErrMsg( char* format, ... );

void ClearErrFlag();

void SetOutputAttachedView( CWnd* pView );
BOOL IsViewAttached( CWnd* pView );
void DeattachOutputView();

// Open files
void OpenTextFile( LPCTSTR lpszPathName );
void OpenPCodeFile( LPCTSTR lpszPathName );
void OpenAsmCodeFile( LPCTSTR lpszPathName );

/////////////////////////////////////////////////////////////////////////////
// CCminusApp:
// See cminus.cpp for the implementation of this class
//

class CCminusApp : public CWinApp
{
public:
	CCminusApp();

// Attributes
public:
	CMultiDocTemplate* m_pCminusDocTemplate;
	CMultiDocTemplate* m_pTextDocTemplate;
	CMultiDocTemplate* m_pPCodeDocTemplate;
	CMultiDocTemplate* m_pAsmCodeDocTemplate;

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCminusApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation
	//{{AFX_MSG(CCminusApp)
	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CMINUS_H__7B450AB3_37F9_4E12_AEF9_7CE77603C0A1__INCLUDED_)
