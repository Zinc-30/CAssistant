// PCodeView.cpp : implementation of the CPCodeView class
//

#include "stdafx.h"
#include "cminus.h"

#include "PCodeDoc.h"
#include "PCodeView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPCodeView

IMPLEMENT_DYNCREATE(CPCodeView, CCrystalEditView)

BEGIN_MESSAGE_MAP(CPCodeView, CCrystalEditView)
	//{{AFX_MSG_MAP(CPCodeView)
	ON_WM_RBUTTONUP()
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CCrystalEditView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CCrystalEditView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CCrystalEditView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPCodeView construction/destruction

CPCodeView::CPCodeView()
{
}

CPCodeView::~CPCodeView()
{
}

/////////////////////////////////////////////////////////////////////////////
// CPCodeView printing

BOOL CPCodeView::OnPreparePrinting(CPrintInfo* pInfo)
{
	return CCrystalEditView::OnPreparePrinting(pInfo);
}

void CPCodeView::OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo)
{
	CCrystalEditView::OnBeginPrinting(pDC, pInfo);
}

void CPCodeView::OnEndPrinting(CDC* pDC, CPrintInfo* pInfo)
{
	CCrystalEditView::OnEndPrinting(pDC, pInfo);
}

/////////////////////////////////////////////////////////////////////////////
// CPCodeView diagnostics

#ifdef _DEBUG
void CPCodeView::AssertValid() const
{
	CCrystalEditView::AssertValid();
}

void CPCodeView::Dump(CDumpContext& dc) const
{
	CCrystalEditView::Dump(dc);
}

#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CPCodeView message handlers
CCrystalTextBuffer* CPCodeView::LocateTextBuffer()
{
	return &((CPCodeDoc* )GetDocument())->m_TextBuffer;
}

void CPCodeView::OnInitialUpdate() 
{
	CCrystalEditView::OnInitialUpdate();
	
	SetFont(((CPCodeDoc*)GetDocument())->m_lf);	
}

void CPCodeView::OnRButtonUp(UINT nFlags, CPoint point) 
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
