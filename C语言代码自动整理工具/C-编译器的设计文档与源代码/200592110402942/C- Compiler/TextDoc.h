#if !defined(AFX_TEXTDOC_H__364D98BC_84E2_4578_A3E6_0769F0BAF001__INCLUDED_)
#define AFX_TEXTDOC_H__364D98BC_84E2_4578_A3E6_0769F0BAF001__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// TextDoc.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CTextDoc document

#include "Crystal/CCrystalTextBuffer.h"

class CTextDoc : public CDocument
{
protected: // create from serialization only
	CTextDoc();
	DECLARE_DYNCREATE(CTextDoc)

// Attributes
public:
	LOGFONT m_lf;
	CCrystalTextBuffer m_TextBuffer;

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTextDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	virtual BOOL OnOpenDocument(LPCTSTR lpszPathName);
	virtual BOOL OnSaveDocument(LPCTSTR lpszPathName);
	virtual void DeleteContents();
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CTextDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CTextDoc)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TEXTDOC_H__364D98BC_84E2_4578_A3E6_0769F0BAF001__INCLUDED_)
