// TransformsDoc.cpp : implementation of the CTransformsDoc class
//

#include "stdafx.h"
#include "Transforms.h"

#include "TransformsDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CTransformsDoc

IMPLEMENT_DYNCREATE(CTransformsDoc, CDocument)

BEGIN_MESSAGE_MAP(CTransformsDoc, CDocument)
	//{{AFX_MSG_MAP(CTransformsDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTransformsDoc construction/destruction

CTransformsDoc::CTransformsDoc()
{
	// TODO: add one-time construction code here

}

CTransformsDoc::~CTransformsDoc()
{
}

BOOL CTransformsDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CTransformsDoc serialization

void CTransformsDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: add storing code here
	}
	else
	{
		// TODO: add loading code here
	}
}

/////////////////////////////////////////////////////////////////////////////
// CTransformsDoc diagnostics

#ifdef _DEBUG
void CTransformsDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CTransformsDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CTransformsDoc commands
