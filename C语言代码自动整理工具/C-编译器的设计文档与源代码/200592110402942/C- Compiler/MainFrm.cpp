// MainFrm.cpp : implementation of the CMainFrame class
//

#include "stdafx.h"
#include "cminus.h"

#include "MainFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMainFrame

IMPLEMENT_DYNAMIC(CMainFrame, CMDIFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CMDIFrameWnd)
	//{{AFX_MSG_MAP(CMainFrame)
	ON_WM_CREATE()
	ON_WM_PAINT()
	ON_COMMAND(ID_RICHEDIT_COPY, OnRicheditCopy)
	ON_COMMAND(ID_RICHEDIT_CLEAR, OnRicheditClear)
	//}}AFX_MSG_MAP
	ON_COMMAND_EX(ID_OUTPUT_BAR, OnBarCheck)
	ON_UPDATE_COMMAND_UI(ID_OUTPUT_BAR, OnUpdateControlBarMenu)
END_MESSAGE_MAP()

static UINT indicators[] =
{
	ID_SEPARATOR,           // status line indicator
	ID_INDICATOR_CAPS,
	ID_INDICATOR_NUM,
	ID_INDICATOR_SCRL,
};

/////////////////////////////////////////////////////////////////////////////
// CMainFrame construction/destruction

CMainFrame::CMainFrame()
{
}

CMainFrame::~CMainFrame()
{
}

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CMDIFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	if (!m_wndToolBar.CreateEx(this, TBSTYLE_FLAT, WS_CHILD | WS_VISIBLE | CBRS_TOP
		| CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC) ||
		!m_wndToolBar.LoadToolBar(IDR_MAINFRAME))
	{
		TRACE0("Failed to create toolbar\n");
		return -1;      // fail to create
	}

	if (!m_wndStatusBar.Create(this) ||
		!m_wndStatusBar.SetIndicators(indicators,
		  sizeof(indicators)/sizeof(UINT)))
	{
		TRACE0("Failed to create status bar\n");
		return -1;      // fail to create
	}

	// TODO: Delete these three lines if you don't want the toolbar to
	//  be dockable
	m_wndToolBar.EnableDocking(CBRS_ALIGN_ANY);
	EnableDocking(CBRS_ALIGN_ANY);
	DockControlBar(&m_wndToolBar);

	//Install image for the Output Bar
	m_ImageList.Create( IDB_IMAGELIST, 13, 1, RGB(0,255,0) );

	//Create Output Bar
	m_OutputBar.SetBtnImageList( &m_ImageList );
	// Initialize Output Bar
	if (!m_OutputBar.Create(this, ID_OUTPUT_BAR, _T("OutputBar"), CSize(220,100)))
	{
		TRACE0("Failed to create tab bar\n");
 		return -1;		// fail to create
	}

    // allow bar to be resized when floating
    m_OutputBar.SetBarStyle(m_OutputBar.GetBarStyle() | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC);

	m_OutputBar.EnableDocking(CBRS_ALIGN_ANY);
	EnableDocking(CBRS_ALIGN_ANY);
	DockControlBar(&m_OutputBar, AFX_IDW_DOCKBAR_BOTTOM);

	m_OutputBar.ShowWindow( SW_HIDE );

	// install cool menus.
	//--- this routine call will cause ERRORS
	InstallCoolMenus(this, IDR_MAINFRAME);

	return 0;
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	cs.cy = ::GetSystemMetrics(SM_CYSCREEN) - 40; 
	cs.cx = ::GetSystemMetrics(SM_CXSCREEN) - 20;
	cs.y = 10;
	cs.x = 10;

	if( !CMDIFrameWnd::PreCreateWindow(cs) )
		return FALSE;

	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// CMainFrame diagnostics

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
	CMDIFrameWnd::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	CMDIFrameWnd::Dump(dc);
}

#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMainFrame message handlers


void CMainFrame::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
}

void CMainFrame::OnRicheditCopy() 
{
	m_OutputBar.m_RichCtrl.Copy();
}

void CMainFrame::OnRicheditClear() 
{
	m_OutputBar.Clear();
}
