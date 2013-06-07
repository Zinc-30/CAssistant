// cminusView.cpp : implementation of the CTextView class
//

#include "stdafx.h"
#include "cminus.h"

#include "TextDoc.h"
#include "TextView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CTextView

IMPLEMENT_DYNCREATE(CTextView, CCrystalEditView)

BEGIN_MESSAGE_MAP(CTextView, CCrystalEditView)
	//{{AFX_MSG_MAP(CTextView)
	ON_WM_RBUTTONUP()
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CCrystalEditView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CCrystalEditView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CCrystalEditView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTextView construction/destruction

CTextView::CTextView()
{
}

CTextView::~CTextView()
{
}

/////////////////////////////////////////////////////////////////////////////
// CTextView printing

BOOL CTextView::OnPreparePrinting(CPrintInfo* pInfo)
{
	return CCrystalEditView::OnPreparePrinting(pInfo);
}

void CTextView::OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo)
{
	CCrystalEditView::OnBeginPrinting(pDC, pInfo);
}

void CTextView::OnEndPrinting(CDC* pDC, CPrintInfo* pInfo)
{
	CCrystalEditView::OnEndPrinting(pDC, pInfo);
}

/////////////////////////////////////////////////////////////////////////////
// CTextView diagnostics

#ifdef _DEBUG
void CTextView::AssertValid() const
{
	CCrystalEditView::AssertValid();
}

void CTextView::Dump(CDumpContext& dc) const
{
	CCrystalEditView::Dump(dc);
}

#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CTextView message handlers
CCrystalTextBuffer* CTextView::LocateTextBuffer()
{
	return &((CTextDoc* )GetDocument())->m_TextBuffer;
}

void CTextView::OnInitialUpdate() 
{
	CCrystalEditView::OnInitialUpdate();
	
	SetFont(((CTextDoc*)GetDocument())->m_lf);	
}

void CTextView::OnRButtonUp(UINT nFlags, CPoint point) 
{
	ClientToScreen( &point );

	CMenu menu;
	VERIFY( menu.LoadMenu( IDR_CRYSTAL ) );
	CMenu* pPop = menu.GetSubMenu( 0 );
	ASSERT( pPop );

	CWnd* pWndPopupOwner = this;
		
	while (pWndPopupOwner->GetStyle() & WS_CHILD)
		pWndPopupOwner = pWndPopupOwner->GetParent();
		
	pPop->TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON, point.x, point.y,
		pWndPopupOwner);

	CCrystalEditView::OnRButtonUp(nFlags, point);
}
