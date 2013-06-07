// cminusView.h : interface of the CCminusView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_CMINUSVIEW_H__3514B12A_A617_4972_BD2E_64CDC6D916D8__INCLUDED_)
#define AFX_CMINUSVIEW_H__3514B12A_A617_4972_BD2E_64CDC6D916D8__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Crystal/CCrystalEditView.h"

class CCminusView : public CCrystalEditView
{
protected: // create from serialization only
	virtual CCrystalTextBuffer* LocateTextBuffer();
	CCminusView();
	DECLARE_DYNCREATE(CCminusView)

	void SetSelection(const CPoint &ptStart, const CPoint &ptEnd)
	{
		CCrystalTextView::SetSelection(ptStart,ptEnd);
	}

	void SelecctLine( int line );

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCminusView)
	public:
	virtual void OnInitialUpdate();
	protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CCminusView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	virtual DWORD ParseLine(DWORD dwCookie, int nLineIndex, TEXTBLOCK *pBuf, int &nActualItems);

// Generated message map functions
protected:
	//{{AFX_MSG(CCminusView)
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#endif // !defined(AFX_CMINUSVIEW_H__3514B12A_A617_4972_BD2E_64CDC6D916D8__INCLUDED_)
