// cminusDoc.cpp : implementation of the CCminusDoc class
//

#include "stdafx.h"
#include "cminus.h"

#include "cminusDoc.h"
#include "cminusView.h"

//#include "Scaner.h"
//#include "Parser.h"
//#include "Analyzer.h"
#include "PCodeGenerator.h"
#include "AsmCodeGenerator.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CCminusDoc

IMPLEMENT_DYNCREATE(CCminusDoc, CDocument)

BEGIN_MESSAGE_MAP(CCminusDoc, CDocument)
	//{{AFX_MSG_MAP(CCminusDoc)
	ON_COMMAND(ID_COMPILE_TRACE_SCAN, OnCompileTraceScan)
	ON_COMMAND(ID_COMPILE_TRACE_PARSE, OnCompileTraceParse)
	ON_COMMAND(ID_COMPILE_TRACE_SYMBOL_TABLE, OnCompileTraceSymbolTable)
	ON_COMMAND(ID_COMPILE_TRACE_TYPE_CHECK, OnCompileTraceTypeCheck)
	ON_COMMAND(ID_COMPILE_BUILD_PCODE, OnCompileBuildPcode)
	ON_COMMAND(ID_COMPILE_BUILD_ASM, OnCompileBuildAsm)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCminusDoc construction/destruction

CCminusDoc::CCminusDoc()
{
	memset(&m_lf, 0, sizeof(m_lf));
	m_lf.lfHeight = -14;
	m_lf.lfWeight = FW_NORMAL;
	strcpy( m_lf.lfFaceName, "新宋体" );
}

CCminusDoc::~CCminusDoc()
{
}

BOOL CCminusDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	((CCrystalEditView* )m_viewList.GetHead())->SetWindowText("");
	m_TextBuffer.InitNew();

	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// CCminusDoc serialization

void CCminusDoc::Serialize(CArchive& ar)
{
	CCrystalEditView* pView = (CCrystalEditView*)m_viewList.GetHead();
	ASSERT_VALID(pView);
	ASSERT_KINDOF(CCrystalEditView, pView);

	if (ar.IsStoring())	
	{
	} 
	else 
	{
	}

	ASSERT_VALID(this);
}

/////////////////////////////////////////////////////////////////////////////
// CCminusDoc diagnostics

#ifdef _DEBUG
void CCminusDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CCminusDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CCminusDoc commands

BOOL CCminusDoc::OnOpenDocument(LPCTSTR lpszPathName) 
{
	if (!CDocument::OnOpenDocument(lpszPathName))
		return FALSE;
	
	return m_TextBuffer.LoadFromFile(lpszPathName);
}

BOOL CCminusDoc::OnSaveDocument(LPCTSTR lpszPathName) 
{
	return m_TextBuffer.SaveToFile(lpszPathName);
}

void CCminusDoc::OnCloseDocument() 
{
	CCminusView* pView = (CCminusView*)m_viewList.GetHead();
	if( pView == pOutputAttachedView ) pOutputAttachedView = NULL;

	if( m_TextBuffer.IsModified() ) {
		int ret = AfxMessageBox( "文件已经改变,要保存吗?",
			MB_YESNOCANCEL | MB_ICONQUESTION );
		if( ret == IDCANCEL ) return;
		else if( ret == IDYES )
			this->OnFileSave();
	}
	
	CDocument::OnCloseDocument();
}

void CCminusDoc::DeleteContents() 
{
	CDocument::DeleteContents();
	m_TextBuffer.FreeAll();
}

LPCTSTR CCminusDoc::GetTitleFromPathName( CString& strPathName )
{
	int index1 = strPathName.ReverseFind( '\\' );
	int index2 = strPathName.ReverseFind( '.' );

	if( index2 > -1 && index2 > index1 )
		strPathName.SetAt( index2, '\0' );

	return (LPCTSTR)strPathName;
}

void CCminusDoc::OnCompileTraceScan() 
{
	CCminusView* pView = (CCminusView*)m_viewList.GetHead();
	ASSERT_VALID( pView );
	ASSERT_KINDOF( CCminusView, pView );

	CString strBuf;
	m_TextBuffer.GetText( 0, 0, m_TextBuffer.GetLineCount() - 1,
		m_TextBuffer.GetLineLength(m_TextBuffer.GetLineCount() - 1), strBuf );
	if( strBuf.IsEmpty() ) return;

	OnFileSave();// save the file

	ShowOutput();
	ClearOutput();
	ClearErrFlag();

	SetOutputAttachedView( pView );

	OutputPhaseMsg( "start scanning..." );

	CScaner* pScaner = new CScaner( strBuf );
	CString strPathName = GetPathName();
	strPathName = GetTitleFromPathName( strPathName );
	strPathName += ".scan";
	pScaner->Trace( strPathName );
	TOKEN token;
	do {
		token = pScaner->NextToken();
	} while( token.type != _EOF );

	delete pScaner;

	OpenTextFile( strPathName );
}


void CCminusDoc::OnCompileTraceParse() 
{
	CCminusView* pView = (CCminusView*)m_viewList.GetHead();
	ASSERT_VALID( pView );
	ASSERT_KINDOF( CCminusView, pView );

	CString strBuf;
	m_TextBuffer.GetText( 0, 0, m_TextBuffer.GetLineCount() - 1,
		m_TextBuffer.GetLineLength(m_TextBuffer.GetLineCount() - 1), strBuf );
	if( strBuf.IsEmpty() ) return;

	OnFileSave();// save the file

	ShowOutput();
	ClearOutput();
	ClearErrFlag();

	SetOutputAttachedView( pView );

	OutputPhaseMsg( "building syntax tree..." );

	CParser* pParser = new CParser( strBuf );
	CString strPathName = GetPathName();
	strPathName = GetTitleFromPathName( strPathName );
	strPathName += ".parse";
	pParser->Trace( strPathName );

	delete pParser;

	if( !bErrFlag ) OpenTextFile( strPathName );
}

void CCminusDoc::OnCompileTraceSymbolTable() 
{
	CCminusView* pView = (CCminusView*)m_viewList.GetHead();
	ASSERT_VALID( pView );
	ASSERT_KINDOF( CCminusView, pView );

	CString strBuf;
	m_TextBuffer.GetText( 0, 0, m_TextBuffer.GetLineCount() - 1,
		m_TextBuffer.GetLineLength(m_TextBuffer.GetLineCount() - 1), strBuf );
	if( strBuf.IsEmpty() ) return;

	OnFileSave();// save the file

	ShowOutput();
	ClearOutput();
	ClearErrFlag();

	SetOutputAttachedView( pView );

	CAnalyzer* pAnalyzer = new CAnalyzer( strBuf );
	CString strPathName = GetPathName();
	strPathName = GetTitleFromPathName( strPathName );
	strPathName += ".st";
	pAnalyzer->Trace( strPathName );

	delete pAnalyzer;

	if( !bErrFlag ) OpenTextFile( strPathName );
}

void CCminusDoc::OnCompileTraceTypeCheck() 
{
	CCminusView* pView = (CCminusView*)m_viewList.GetHead();
	ASSERT_VALID( pView );
	ASSERT_KINDOF( CCminusView, pView );

	CString strBuf;
	m_TextBuffer.GetText( 0, 0, m_TextBuffer.GetLineCount() - 1,
		m_TextBuffer.GetLineLength(m_TextBuffer.GetLineCount() - 1), strBuf );
	if( strBuf.IsEmpty() ) return;

	OnFileSave();// save the file

	ShowOutput();
	ClearOutput();
	ClearErrFlag();

	SetOutputAttachedView( pView );

	CAnalyzer* pAnalyzer = new CAnalyzer( strBuf );
	pAnalyzer->TraceTypeCheck();
	delete pAnalyzer;
}

void CCminusDoc::OnCompileBuildPcode() 
{
	CCminusView* pView = (CCminusView*)m_viewList.GetHead();
	ASSERT_VALID( pView );
	ASSERT_KINDOF( CCminusView, pView );

	CString strBuf;
	m_TextBuffer.GetText( 0, 0, m_TextBuffer.GetLineCount() - 1,
		m_TextBuffer.GetLineLength(m_TextBuffer.GetLineCount() - 1), strBuf );
	if( strBuf.IsEmpty() ) return;

	OnFileSave();// save the file

	ShowOutput();
	ClearOutput();
	ClearErrFlag();

	SetOutputAttachedView( pView );

	CPCodeGenerator* pGen = new CPCodeGenerator( strBuf );
	CString strPathName = GetPathName();
	strPathName = GetTitleFromPathName( strPathName );
	strPathName += ".p";
	pGen->GeneratePCode( (LPCTSTR)strPathName );

	delete pGen;

	if( !bErrFlag ) OpenPCodeFile( strPathName );
}

void CCminusDoc::OnCompileBuildAsm() 
{
	CCminusView* pView = (CCminusView*)m_viewList.GetHead();
	ASSERT_VALID( pView );
	ASSERT_KINDOF( CCminusView, pView );

	CString strBuf;
	m_TextBuffer.GetText( 0, 0, m_TextBuffer.GetLineCount() - 1,
		m_TextBuffer.GetLineLength(m_TextBuffer.GetLineCount() - 1), strBuf );
	if( strBuf.IsEmpty() ) return;

	OnFileSave();// save the file

	ShowOutput();
	ClearOutput();
	ClearErrFlag();

	SetOutputAttachedView( pView );

	CAsmCodeGenerator* pGen = new CAsmCodeGenerator( strBuf );
	CString strPathName = GetPathName();
	strPathName = GetTitleFromPathName( strPathName );
	strPathName += ".asm";
	pGen->GenerateAsmCode( (LPCTSTR)strPathName );

	delete pGen;

	if( !bErrFlag ) OpenAsmCodeFile( strPathName );
}
