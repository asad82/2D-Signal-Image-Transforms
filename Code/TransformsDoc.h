// TransformsDoc.h : interface of the CTransformsDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_TRANSFORMSDOC_H__96578F18_9D77_413C_80EA_21CA65F00E80__INCLUDED_)
#define AFX_TRANSFORMSDOC_H__96578F18_9D77_413C_80EA_21CA65F00E80__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CTransformsDoc : public CDocument
{
protected: // create from serialization only
	CTransformsDoc();
	DECLARE_DYNCREATE(CTransformsDoc)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTransformsDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CTransformsDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CTransformsDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TRANSFORMSDOC_H__96578F18_9D77_413C_80EA_21CA65F00E80__INCLUDED_)
