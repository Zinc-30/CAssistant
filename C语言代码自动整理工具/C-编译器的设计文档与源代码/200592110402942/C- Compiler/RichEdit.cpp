// RichEdit.cpp : implementation file
//

#include "stdafx.h"
#include "cminus.h"
#include "RichEdit.h"
#include "cminusview.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CRichEdit

CRichEdit::CRichEdit()
{
}

CRichEdit::~CRichEdit()
{
}


BEGIN_MESSAGE_MAP(CRichEdit, CRichEditCtrl)
	//{{AFX_MSG_MAP(CRichEdit)
	ON_WM_CREATE()
	ON_WM_RBUTTONDOWN()
	ON_WM_LBUTTONDBLCLK()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CRichEdit message handlers
int CRichEdit::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CRichEditCtrl::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	// set richeditctrl background color
	SetBackgroundColor( FALSE, RGB(51, 68, 85) );

	// set richeditctrl default font
	CHARFORMAT cf;
	cf.cbSize		= sizeof (CHARFORMAT);  
	cf.dwMask		= CFM_FACE | CFM_SIZE | CFM_COLOR | CFM_UNDERLINE | CFM_BOLD;
	cf.yHeight		= 200;
	cf.dwEffects	&= ~( CFE_AUTOCOLOR | CFE_UNDERLINE | CFE_BOLD );
	cf.crTextColor	= RGB(245, 222, 179); 
	sprintf(cf.szFaceName, "MS Sans Serif"); 
	SetDefaultCharFormat(cf); 

	return 0;
}

void CRichEdit::OnRButtonDown(UINT nFlags, CPoint point) 
{
	CRichEditCtrl::OnRButtonDown(nFlags, point);
	
	CRect Rect;
	GetClientRect(Rect);
	ClientToScreen(Rect);
	point.Offset( Rect.TopLeft() );

	CMenu menu;
	VERIFY( menu.LoadMenu( IDR_RICHEDIT_POP ) );
	CMenu* pPop = menu.GetSubMenu( 0 );
	ASSERT( pPop );

	CWnd* pWndPopupOwner = this;
		
	while (pWndPopupOwner->GetStyle() & WS_CHILD)
		pWndPopupOwner = pWndPopupOwner->GetParent();
		
	pPop->TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON, point.x, point.y,
		pWndPopupOwner);
}

void CRichEdit::Clear()
{
	SetSel( 0, -1 );
	ReplaceSel( NULL );
}

void CRichEdit::InsertText( LPCTSTR text, COLORREF color )
{
	int iTotalTextLength = GetWindowTextLength();
	SetSel( iTotalTextLength, iTotalTextLength );
	ReplaceSel( (LPCTSTR)text );
	int iStartPos = iTotalTextLength;

	CHARFORMAT cf;
	cf.cbSize		= sizeof(CHARFORMAT);
	cf.dwMask		= CFM_COLOR | CFM_UNDERLINE | CFM_BOLD;
	cf.dwEffects	&= ~( CFE_AUTOCOLOR | CFE_UNDERLINE | CFE_BOLD);
	cf.crTextColor	= color;

	int iEndPos = GetWindowTextLength();
	SetSel( iStartPos, iEndPos );
	SetSelectionCharFormat( cf );
	HideSelection( TRUE, FALSE );

	LineScroll(1);
}

void CRichEdit::OnLButtonDblClk(UINT nFlags, CPoint point) 
{
	static char buf[1024];
	long nStartChar, nEndChar;
	int line = 0;

	CRichEditCtrl::GetSel( nStartChar, nEndChar );
	CRichEditCtrl::GetLine( LineFromChar(nStartChar), buf, 1024 );
	if( pOutputAttachedView && (::sscanf( buf, "error in line %d:", &line ) == 1) ) {
		CCminusView* pView = (CCminusView*)pOutputAttachedView;
		ASSERT_KINDOF( CCminusView, pView );
		pView->SelecctLine( line );
	}
}
