// cminusDoc.h : interface of the CCminusDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_CMINUSDOC_H__077CB5B4_CE6B_4FF0_8199_FD4AB3846F00__INCLUDED_)
#define AFX_CMINUSDOC_H__077CB5B4_CE6B_4FF0_8199_FD4AB3846F00__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Crystal/CCrystalTextBuffer.h"

class CCminusDoc : public CDocument
{
protected: // create from serialization only
	CCminusDoc();
	DECLARE_DYNCREATE(CCminusDoc)

// Attributes
public:
	LOGFONT m_lf;
	CCrystalTextBuffer m_TextBuffer;

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCminusDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	virtual BOOL OnOpenDocument(LPCTSTR lpszPathName);
	virtual BOOL OnSaveDocument(LPCTSTR lpszPathName);
	virtual void DeleteContents();
	virtual void OnCloseDocument();
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CCminusDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	// help routines
	LPCTSTR GetTitleFromPathName( CString& strPathName );

// Generated message map functions
protected:
	//{{AFX_MSG(CCminusDoc)
	afx_msg void OnCompileTraceScan();
	afx_msg void OnCompileTraceParse();
	afx_msg void OnCompileTraceSymbolTable();
	afx_msg void OnCompileTraceTypeCheck();
	afx_msg void OnCompileBuildPcode();
	afx_msg void OnCompileBuildAsm();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CMINUSDOC_H__077CB5B4_CE6B_4FF0_8199_FD4AB3846F00__INCLUDED_)
