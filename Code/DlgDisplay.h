#if !defined(AFX_DLGDISPLAY_H__A22F40FD_787E_44FD_A121_39A65D58D769__INCLUDED_)
#define AFX_DLGDISPLAY_H__A22F40FD_787E_44FD_A121_39A65D58D769__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgDisplay.h : header file
//
#include "CDibData.h"
/////////////////////////////////////////////////////////////////////////////
// CDlgDisplay dialog

class CDlgDisplay : public CDialog
{
// Construction
public:
	void Initialize(double **imageData,int cx,int cy);
	CDlgDisplay(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgDisplay)
	enum { IDD = IDD_TRANSFORMRESULT };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgDisplay)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
	public:
//		CDibData dibDest;
//		CBitmap bmpDest;
//		CDC dcMemoryDlg;
//		BITMAP bmpInfo;

	protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgDisplay)
	afx_msg void OnPaint();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGDISPLAY_H__A22F40FD_787E_44FD_A121_39A65D58D769__INCLUDED_)
