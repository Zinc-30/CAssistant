// AsmCodeDoc.cpp : implementation of the CCminusDoc class
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
// CAsmCodeDoc

IMPLEMENT_DYNCREATE(CAsmCodeDoc, CDocument)

BEGIN_MESSAGE_MAP(CAsmCodeDoc, CDocument)
	//{{AFX_MSG_MAP(CAsmCodeDoc)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CAsmCodeDoc construction/destruction

CAsmCodeDoc::CAsmCodeDoc()
{
	memset( &m_lf, 0, sizeof(m_lf) );
	m_lf.lfHeight = -14;
	m_lf.lfWeight = FW_NORMAL;
	strcpy( m_lf.lfFaceName, "ÐÂËÎÌå" );
}

CAsmCodeDoc::~CAsmCodeDoc()
{
}

BOOL CAsmCodeDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	((CCrystalEditView* )m_viewList.GetHead())->SetWindowText("");
	m_TextBuffer.InitNew();

	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// CAsmCodeDoc serialization

void CAsmCodeDoc::Serialize(CArchive& ar)
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
// CAsmCodeDoc diagnostics

#ifdef _DEBUG
void CAsmCodeDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CAsmCodeDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CAsmCodeDoc commands

BOOL CAsmCodeDoc::OnOpenDocument(LPCTSTR lpszPathName) 
{
	if (!CDocument::OnOpenDocument(lpszPathName))
		return FALSE;
	
	return m_TextBuffer.LoadFromFile(lpszPathName);
}

BOOL CAsmCodeDoc::OnSaveDocument(LPCTSTR lpszPathName) 
{
	return m_TextBuffer.SaveToFile(lpszPathName);
}

void CAsmCodeDoc::DeleteContents() 
{
	CDocument::DeleteContents();
	m_TextBuffer.FreeAll();
}