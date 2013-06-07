// AsmCodeView.cpp : implementation of the CAsmCodeView class
//

#include "stdafx.h"
#include "cminus.h"

#include "AsmCodeDoc.h"
#include "AsmCodeView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAsmCodeView

IMPLEMENT_DYNCREATE(CAsmCodeView, CCrystalEditView)

BEGIN_MESSAGE_MAP(CAsmCodeView, CCrystalEditView)
	//{{AFX_MSG_MAP(CAsmCodeView)
	ON_WM_RBUTTONUP()
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CCrystalEditView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CCrystalEditView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CCrystalEditView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CAsmCodeView construction/destruction

CAsmCodeView::CAsmCodeView()
{
}

CAsmCodeView::~CAsmCodeView()
{
}

/////////////////////////////////////////////////////////////////////////////
// CAsmCodeView printing

BOOL CAsmCodeView::OnPreparePrinting(CPrintInfo* pInfo)
{
	return CCrystalEditView::OnPreparePrinting(pInfo);
}

void CAsmCodeView::OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo)
{
	CCrystalEditView::OnBeginPrinting(pDC, pInfo);
}

void CAsmCodeView::OnEndPrinting(CDC* pDC, CPrintInfo* pInfo)
{
	CCrystalEditView::OnEndPrinting(pDC, pInfo);
}

/////////////////////////////////////////////////////////////////////////////
// CAsmCodeView diagnostics

#ifdef _DEBUG
void CAsmCodeView::AssertValid() const
{
	CCrystalEditView::AssertValid();
}

void CAsmCodeView::Dump(CDumpContext& dc) const
{
	CCrystalEditView::Dump(dc);
}

#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CAsmCodeView message handlers
CCrystalTextBuffer* CAsmCodeView::LocateTextBuffer()
{
	return &((CAsmCodeDoc* )GetDocument())->m_TextBuffer;
}

void CAsmCodeView::OnInitialUpdate() 
{
	CCrystalEditView::OnInitialUpdate();
	
	SetFont(((CAsmCodeDoc*)GetDocument())->m_lf);	
}

void CAsmCodeView::OnRButtonUp(UINT nFlags, CPoint point) 
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
