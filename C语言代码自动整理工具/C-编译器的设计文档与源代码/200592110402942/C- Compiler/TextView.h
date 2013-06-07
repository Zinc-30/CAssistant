#if !defined(AFX_TEXTVIEW_H__F1AB2BE2_48E3_41C8_84DB_619DB745A50C__INCLUDED_)
#define AFX_TEXTVIEW_H__F1AB2BE2_48E3_41C8_84DB_619DB745A50C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// TextView.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CTextView view

#include "Crystal/CCrystalEditView.h"

class CTextView : public CCrystalEditView
{
protected: // create from serialization only
	virtual CCrystalTextBuffer* LocateTextBuffer();
	CTextView();
	DECLARE_DYNCREATE(CTextView)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTextView)
	public:
	virtual void OnInitialUpdate();
	protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CTextView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
//	virtual DWORD ParseLine(DWORD dwCookie, int nLineIndex, TEXTBLOCK *pBuf, int &nActualItems);

// Generated message map functions
protected:
	//{{AFX_MSG(CTextView)
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#endif // !defined(AFX_TEXTVIEW_H__F1AB2BE2_48E3_41C8_84DB_619DB745A50C__INCLUDED_)
