// OutputBar.cpp : implementation file
//

#include "stdafx.h"
#include "cminus.h"
#include "OutputBar.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// COutputBar

COutputBar::COutputBar()
{
}

COutputBar::~COutputBar()
{
}


BEGIN_MESSAGE_MAP(COutputBar, CControlBar)
	//{{AFX_MSG_MAP(COutputBar)
	ON_WM_CREATE()
	ON_WM_WINDOWPOSCHANGED()
	ON_WM_PAINT()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// COutputBar message handlers
void COutputBar::OnWindowPosChanged(WINDOWPOS FAR* lpwndpos) 
{
	CControlBar::OnWindowPosChanged(lpwndpos);
	
	if( IsFloating() ) {
		m_RichCtrl.MoveWindow( 5, 5, lpwndpos->cx-10, lpwndpos->cy-10 );
	} else if( IsHorzDocked() ) {
		m_RichCtrl.MoveWindow( 17, 3, lpwndpos->cx-25, lpwndpos->cy-17 );
	} else {
		m_RichCtrl.MoveWindow( 3, 17, lpwndpos->cx-17, lpwndpos->cy-30 );
	}
}

int COutputBar::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if( CControlBar::OnCreate(lpCreateStruct) == -1 )
		return -1;

	if( !m_RichCtrl.Create( WS_CHILD | WS_VISIBLE | WS_HSCROLL | WS_VSCROLL |
		ES_AUTOHSCROLL | ES_AUTOVSCROLL |  ES_MULTILINE |
		ES_LEFT | ES_READONLY, CRect(0,0,0,0), this ,1 ) )
	{
		TRACE0("Failed to create view for COutputBar\n");
		return -1;
	}

	m_RichCtrl.ModifyStyleEx(0, WS_EX_CLIENTEDGE | WS_EX_WINDOWEDGE);

	m_RichCtrl.InsertText( "--------------------------------- C- Compiler run-time report ---------------------------------" );

	return 0;
}

void COutputBar::Clear()
{
	m_RichCtrl.Clear();
	m_RichCtrl.InsertText( "--------------------------------- C- Compiler run-time report ---------------------------------" );
}

void COutputBar::InsertText( LPCTSTR text, COLORREF color )
{
	m_RichCtrl.InsertText( "\r\n" );
	m_RichCtrl.InsertText( text, color );
}

void COutputBar::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
}
