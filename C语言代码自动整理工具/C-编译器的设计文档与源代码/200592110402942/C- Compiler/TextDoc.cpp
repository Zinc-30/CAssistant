// TextDoc.cpp : implementation of the CCminusDoc class
//

#include "stdafx.h"
#include "cminus.h"

#include "TextDoc.h"
#include "TextView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CTextDoc

IMPLEMENT_DYNCREATE(CTextDoc, CDocument)

BEGIN_MESSAGE_MAP(CTextDoc, CDocument)
	//{{AFX_MSG_MAP(CTextDoc)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTextDoc construction/destruction

CTextDoc::CTextDoc()
{
	memset( &m_lf, 0, sizeof(m_lf) );
	m_lf.lfHeight = -14;
	m_lf.lfWeight = FW_NORMAL;
	strcpy( m_lf.lfFaceName, "ÐÂËÎÌå" );
}

CTextDoc::~CTextDoc()
{
}

BOOL CTextDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	((CCrystalEditView* )m_viewList.GetHead())->SetWindowText("");
	m_TextBuffer.InitNew();

	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// CTextDoc serialization

void CTextDoc::Serialize(CArchive& ar)
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
// CTextDoc diagnostics

#ifdef _DEBUG
void CTextDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CTextDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CTextDoc commands

BOOL CTextDoc::OnOpenDocument(LPCTSTR lpszPathName) 
{
	if (!CDocument::OnOpenDocument(lpszPathName))
		return FALSE;
	
	return m_TextBuffer.LoadFromFile(lpszPathName);
}

BOOL CTextDoc::OnSaveDocument(LPCTSTR lpszPathName) 
{
	return m_TextBuffer.SaveToFile(lpszPathName);
}

void CTextDoc::DeleteContents() 
{
	CDocument::DeleteContents();
	m_TextBuffer.FreeAll();
}