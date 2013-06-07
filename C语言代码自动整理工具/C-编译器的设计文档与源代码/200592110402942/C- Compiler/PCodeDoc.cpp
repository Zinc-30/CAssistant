// PCodeDoc.cpp : implementation of the CCminusDoc class
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
// CPCodeDoc

IMPLEMENT_DYNCREATE(CPCodeDoc, CDocument)

BEGIN_MESSAGE_MAP(CPCodeDoc, CDocument)
	//{{AFX_MSG_MAP(CPCodeDoc)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPCodeDoc construction/destruction

CPCodeDoc::CPCodeDoc()
{
	memset( &m_lf, 0, sizeof(m_lf) );
	m_lf.lfHeight = -14;
	m_lf.lfWeight = FW_NORMAL;
	strcpy( m_lf.lfFaceName, "ÐÂËÎÌå" );
}

CPCodeDoc::~CPCodeDoc()
{
}

BOOL CPCodeDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	((CCrystalEditView* )m_viewList.GetHead())->SetWindowText("");
	m_TextBuffer.InitNew();

	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// CPCodeDoc serialization

void CPCodeDoc::Serialize(CArchive& ar)
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
// CPCodeDoc diagnostics

#ifdef _DEBUG
void CPCodeDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CPCodeDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CPCodeDoc commands

BOOL CPCodeDoc::OnOpenDocument(LPCTSTR lpszPathName) 
{
	if (!CDocument::OnOpenDocument(lpszPathName))
		return FALSE;
	
	return m_TextBuffer.LoadFromFile(lpszPathName);
}

BOOL CPCodeDoc::OnSaveDocument(LPCTSTR lpszPathName) 
{
	return m_TextBuffer.SaveToFile(lpszPathName);
}

void CPCodeDoc::DeleteContents() 
{
	CDocument::DeleteContents();
	m_TextBuffer.FreeAll();
}