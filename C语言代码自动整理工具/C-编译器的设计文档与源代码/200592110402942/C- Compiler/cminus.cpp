// cminus.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "cminus.h"

#include "MainFrm.h"
#include "ChildFrm.h"

#include "cminusDoc.h"
#include "cminusView.h"

#include "TextDoc.h"
#include "TextView.h"

#include "PCodeDoc.h"
#include "PCodeView.h"

#include "AsmCodeDoc.h"
#include "AsmCodeView.h"

#include "XPButton.h"
#include "MenuWndHook.h"
#include <hyperlink.h>// CJ60LIB

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// GLOBAL FUNCTIONS
// Output Bar
BOOL bErrFlag = FALSE;
CWnd* pOutputAttachedView = NULL;

void ShowOutput()
{
	CMainFrame* pMainFrame = (CMainFrame*)AfxGetMainWnd();
	if( !pMainFrame->m_OutputBar.IsWindowVisible() )
		pMainFrame->OnBarCheck( ID_OUTPUT_BAR );
}

void ClearOutput()
{
	CMainFrame* pMainFrame = (CMainFrame*)AfxGetMainWnd();
	pMainFrame->m_OutputBar.Clear();

	pOutputAttachedView = NULL;
}

void OutputPhaseMsg( LPCTSTR msg )
{
	CMainFrame* pMainFrame = (CMainFrame*)AfxGetMainWnd();
	pMainFrame->m_OutputBar.InsertText( msg );
}

void OutputErrMsg( char* format, ... )
{
	va_list params;
	static char msg[ 1024 ];
	
	va_start( params, format );
	_vsnprintf( msg, 1020, format, params );
	va_end( params );

	CMainFrame* pMainFrame = (CMainFrame*)AfxGetMainWnd();
	pMainFrame->m_OutputBar.InsertText( msg, RGB(230, 172, 66) );

	bErrFlag = TRUE;
}

void ClearErrFlag()
{
	bErrFlag = FALSE;
}

void SetOutputAttachedView( CWnd* pView )
{
	pOutputAttachedView = pView;
}

BOOL IsViewAttached( CWnd* pView )
{
	return (pOutputAttachedView == pView );
}

void DeattachOutputView()
{
	pOutputAttachedView = NULL;
}

// Open a text file
void OpenTextFile( LPCTSTR lpszPathName )
{
	CCminusApp* pApp = (CCminusApp*)AfxGetApp();
	pApp->m_pTextDocTemplate->OpenDocumentFile( lpszPathName );
}

// Open a p-code file
void OpenPCodeFile( LPCTSTR lpszPathName )
{
	CCminusApp* pApp = (CCminusApp*)AfxGetApp();
	pApp->m_pPCodeDocTemplate->OpenDocumentFile( lpszPathName );
}

// Open a asm file
void OpenAsmCodeFile( LPCTSTR lpszPathName )
{
	CCminusApp* pApp = (CCminusApp*)AfxGetApp();
	pApp->m_pAsmCodeDocTemplate->OpenDocumentFile( lpszPathName );
}

/////////////////////////////////////////////////////////////////////////////
// CCminusApp
BEGIN_MESSAGE_MAP(CCminusApp, CWinApp)
	//{{AFX_MSG_MAP(CCminusApp)
	ON_COMMAND(ID_APP_ABOUT, OnAppAbout)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
	// Standard file based document commands
	ON_COMMAND(ID_FILE_NEW, CWinApp::OnFileNew)
	ON_COMMAND(ID_FILE_OPEN, CWinApp::OnFileOpen)
	// Standard print setup command
	ON_COMMAND(ID_FILE_PRINT_SETUP, CWinApp::OnFilePrintSetup)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCminusApp construction

CCminusApp::CCminusApp()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CCminusApp object

CCminusApp theApp;

/////////////////////////////////////////////////////////////////////////////
// CCminusApp initialization

BOOL CCminusApp::InitInstance()
{
	AfxEnableControlContainer();

	// Standard initialization
	// If you are not using these features and wish to reduce the size
	//  of your final executable, you should remove from the following
	//  the specific initialization routines you do not need.

#ifdef _AFXDLL
	Enable3dControls();			// Call this when using MFC in a shared DLL
#else
	Enable3dControlsStatic();	// Call this when linking to MFC statically
#endif

	// Change the registry key under which our settings are stored.
	// TODO: You should modify this string to be something appropriate
	// such as the name of your company or organization.
	SetRegistryKey(_T("Local AppWizard-Generated Applications"));

	LoadStdProfileSettings();  // Load standard INI file options (including MRU)

	// Register the application's document templates.  Document templates
	//  serve as the connection between documents, frame windows and views.

	// cminus type
	m_pCminusDocTemplate = new CMultiDocTemplate(
		IDR_CMINUSTYPE,
		RUNTIME_CLASS(CCminusDoc),
		RUNTIME_CLASS(CChildFrame), // custom MDI child frame
		RUNTIME_CLASS(CCminusView));
	AddDocTemplate(m_pCminusDocTemplate);

	// text type
	m_pTextDocTemplate = new CMultiDocTemplate(
		IDR_TEXTTYPE,
		RUNTIME_CLASS(CTextDoc),
		RUNTIME_CLASS(CChildFrame), // custom MDI child frame
		RUNTIME_CLASS(CTextView));
	AddDocTemplate(m_pTextDocTemplate);

	// pcode type
	m_pPCodeDocTemplate = new CMultiDocTemplate(
		IDR_PCODETYPE,
		RUNTIME_CLASS(CPCodeDoc),
		RUNTIME_CLASS(CChildFrame), // custom MDI child frame
		RUNTIME_CLASS(CPCodeView));
	AddDocTemplate(m_pPCodeDocTemplate);

	// asmcode type
	m_pAsmCodeDocTemplate = new CMultiDocTemplate(
		IDR_ASMCODETYPE,
		RUNTIME_CLASS(CAsmCodeDoc),
		RUNTIME_CLASS(CChildFrame), // custom MDI child frame
		RUNTIME_CLASS(CAsmCodeView));
	AddDocTemplate(m_pAsmCodeDocTemplate);

	// create main MDI Frame window
	CMainFrame* pMainFrame = new CMainFrame;
	if (!pMainFrame->LoadFrame(IDR_MAINFRAME))
		return FALSE;
	m_pMainWnd = pMainFrame;

	// Parse command line for standard shell commands, DDE, file open
	CCommandLineInfo cmdInfo;
	ParseCommandLine(cmdInfo);

	// Dispatch commands specified on the command line
	if (!ProcessShellCommand(cmdInfo))
		return FALSE;

	// The main window has been initialized, so show and update it.
	pMainFrame->ShowWindow(m_nCmdShow);
	pMainFrame->UpdateWindow();

	CMenuWndHook::InstallHook();

	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	CXPButton	m_btnOK;
	CHyperLink	m_lu;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	DDX_Control(pDX, IDOK, m_btnOK);
	DDX_Control(pDX, IDC_STATIC_LU, m_lu);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

// App command to run the dialog
void CCminusApp::OnAppAbout()
{
	CAboutDlg aboutDlg;
	aboutDlg.DoModal();
}

BOOL CAboutDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	m_lu.SetURL(_T("mailto:robert1111@zju.edu.cn"));
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

/////////////////////////////////////////////////////////////////////////////
// CCminusApp message handlers
