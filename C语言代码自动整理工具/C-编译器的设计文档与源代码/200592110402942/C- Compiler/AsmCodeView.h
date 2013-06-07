#if !defined(AFX_ASMCODEVIEW_H__F1AB2BE2_48E3_41C8_84DB_619DB745A50C__INCLUDED_)
#define AFX_ASMCODEVIEW_H__F1AB2BE2_48E3_41C8_84DB_619DB745A50C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// AsmCodeView.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CAsmCodeView view

#include "Crystal/CCrystalEditView.h"

class CAsmCodeView : public CCrystalEditView
{
protected: // create from serialization only
	virtual CCrystalTextBuffer* LocateTextBuffer();
	CAsmCodeView();
	DECLARE_DYNCREATE(CAsmCodeView)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAsmCodeView)
	public:
	virtual void OnInitialUpdate();
	protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CAsmCodeView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	virtual DWORD ParseLine(DWORD dwCookie, int nLineIndex, TEXTBLOCK *pBuf, int &nActualItems);

// Generated message map functions
protected:
	//{{AFX_MSG(CAsmCodeView)
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#endif // !defined(AFX_ASMCODEVIEW_H__F1AB2BE2_48E3_41C8_84DB_619DB745A50C__INCLUDED_)
