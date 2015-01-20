// TransformsView.h : interface of the CTransformsView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_TRANSFORMSVIEW_H__05300BEC_152F_48F9_9807_572A0185628D__INCLUDED_)
#define AFX_TRANSFORMSVIEW_H__05300BEC_152F_48F9_9807_572A0185628D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CTransformsView : public CFormView
{
protected: // create from serialization only
	CTransformsView();
	DECLARE_DYNCREATE(CTransformsView)

public:
	//{{AFX_DATA(CTransformsView)
	enum { IDD = IDD_TRANSFORMS_FORM };
	CStatic	m_DisplayBmp;
	CString	m_FileName;
	int		m_Selection;
	//}}AFX_DATA

// Attributes
public:
	CTransformsDoc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTransformsView)
	public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual void OnInitialUpdate(); // called first time after construct
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnPrint(CDC* pDC, CPrintInfo* pInfo);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CTransformsView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

public:
	void InverseTransformOperation(int length);
	void WaveletTransformInverse();
	void Periodic_Extension (double *output, int size);
	void TransformOperation(int length);
	void WaveletTransformForward();
	void DWalshTForward();
	void DWalshTInverse();

	void DCTInverse();
	void DisplayMagnitudePhase();
	void DiscreteFourierTransformForward();
	void DiscreteFourierTransformInverse();
	void DCTForward();
	void DFT(double *xVal, double *yVal, int direction, long length, double *xValOut, double *yValOut);
	void ProcessImageData();
	bool displayImage;
// Generated message map functions
protected:
	//{{AFX_MSG(CTransformsView)
	afx_msg void OnLoadimage();
	afx_msg void OnPaint();
	afx_msg void OnButton1();
	afx_msg void OnApplyInverseTransform();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in TransformsView.cpp
inline CTransformsDoc* CTransformsView::GetDocument()
   { return (CTransformsDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TRANSFORMSVIEW_H__05300BEC_152F_48F9_9807_572A0185628D__INCLUDED_)
