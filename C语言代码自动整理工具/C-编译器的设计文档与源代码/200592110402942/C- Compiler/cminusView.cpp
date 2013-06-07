// cminusView.cpp : implementation of the CCminusView class
//

#include "stdafx.h"
#include "cminus.h"
#include "ChildFrm.h"

#include "cminusDoc.h"
#include "cminusView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CCminusView

IMPLEMENT_DYNCREATE(CCminusView, CCrystalEditView)

BEGIN_MESSAGE_MAP(CCminusView, CCrystalEditView)
	//{{AFX_MSG_MAP(CCminusView)
	ON_WM_RBUTTONUP()
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CCrystalEditView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CCrystalEditView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CCrystalEditView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCminusView construction/destruction

CCminusView::CCminusView()
{
}

CCminusView::~CCminusView()
{
}

/////////////////////////////////////////////////////////////////////////////
// CCminusView printing

BOOL CCminusView::OnPreparePrinting(CPrintInfo* pInfo)
{
	return CCrystalEditView::OnPreparePrinting(pInfo);
}

void CCminusView::OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo)
{
	CCrystalEditView::OnBeginPrinting(pDC, pInfo);
}

void CCminusView::OnEndPrinting(CDC* pDC, CPrintInfo* pInfo)
{
	CCrystalEditView::OnEndPrinting(pDC, pInfo);
}

/////////////////////////////////////////////////////////////////////////////
// CCminusView diagnostics

#ifdef _DEBUG
void CCminusView::AssertValid() const
{
	CCrystalEditView::AssertValid();
}

void CCminusView::Dump(CDumpContext& dc) const
{
	CCrystalEditView::Dump(dc);
}

#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CCminusView message handlers
CCrystalTextBuffer* CCminusView::LocateTextBuffer()
{
	return &((CCminusDoc*)GetDocument())->m_TextBuffer;
}

void CCminusView::OnInitialUpdate() 
{
	CCrystalEditView::OnInitialUpdate();
	
	SetFont(((CCminusDoc*)GetDocument())->m_lf);	
}

void CCminusView::OnRButtonUp(UINT nFlags, CPoint point) 
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

void CCminusView::SelecctLine( int line )
{
	CCrystalTextBuffer* pBuffer = &((CCminusDoc*)GetDocument())->m_TextBuffer;
	ASSERT( pBuffer );

	if( line < 1 ) line = 1;
	if( line > pBuffer->GetLineCount() ) line = pBuffer->GetLineCount();

	WINDOWPLACEMENT pl;
	GetWindowPlacement( &pl );
	pl.flags = WPF_RESTORETOMAXIMIZED;
	pl.showCmd = SW_SHOWMAXIMIZED;
	SetWindowPlacement( &pl );
	this->SetFocus();
	SetSelection( CPoint(0, line - 1),
		          CPoint(pBuffer->GetLineLength(line-1), line - 1) );
	SetCursorPos( CPoint(pBuffer->GetLineLength(line-1), line - 1) );
	EnsureVisible( CPoint(pBuffer->GetLineLength(line-1), line - 1) );
}