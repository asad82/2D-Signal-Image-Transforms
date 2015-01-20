// Transforms.h : main header file for the TRANSFORMS application
//

#if !defined(AFX_TRANSFORMS_H__5491DF88_6C44_4D6B_9510_00B91886836B__INCLUDED_)
#define AFX_TRANSFORMS_H__5491DF88_6C44_4D6B_9510_00B91886836B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CTransformsApp:
// See Transforms.cpp for the implementation of this class
//

class CTransformsApp : public CWinApp
{
public:
	CTransformsApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTransformsApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation
	//{{AFX_MSG(CTransformsApp)
	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TRANSFORMS_H__5491DF88_6C44_4D6B_9510_00B91886836B__INCLUDED_)
