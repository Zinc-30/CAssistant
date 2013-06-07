#if !defined(AFX_RICHEDIT_H__312B509A_50B2_4B23_B61E_B9C138E5ECEA__INCLUDED_)
#define AFX_RICHEDIT_H__312B509A_50B2_4B23_B61E_B9C138E5ECEA__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// RichEdit.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CRichEdit window

class CRichEdit : public CRichEditCtrl
{
// Construction
public:
	CRichEdit();

// Attributes
public:

// Operations
public:
	void Clear();
	void InsertText( LPCTSTR text, COLORREF color = RGB(245, 222, 179) );

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CRichEdit)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CRichEdit();

	// Generated message map functions
protected:
	//{{AFX_MSG(CRichEdit)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_RICHEDIT_H__312B509A_50B2_4B23_B61E_B9C138E5ECEA__INCLUDED_)
