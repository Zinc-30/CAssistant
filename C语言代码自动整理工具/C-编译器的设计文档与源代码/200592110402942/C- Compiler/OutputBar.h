#if !defined(AFX_OUTPUTBAR_H__9670ABBA_2761_40FD_BCA5_8ED9498906AE__INCLUDED_)
#define AFX_OUTPUTBAR_H__9670ABBA_2761_40FD_BCA5_8ED9498906AE__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// OutputBar.h : header file
//

#include "RichEdit.h"

/////////////////////////////////////////////////////////////////////////////
// COutputBar window

class COutputBar : public CControlBar
{
// Construction
public:
	COutputBar();

// Attributes
public:
	CRichEdit m_RichCtrl;

// Operations
public:
	void Clear();
	void InsertText( LPCTSTR text, COLORREF color = RGB(245, 222, 179) );

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(COutputBar)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~COutputBar();

	// Generated message map functions
protected:
	//{{AFX_MSG(COutputBar)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnWindowPosChanged(WINDOWPOS FAR* lpwndpos);
	afx_msg void OnPaint();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#endif // !defined(AFX_OUTPUTBAR_H__9670ABBA_2761_40FD_BCA5_8ED9498906AE__INCLUDED_)
