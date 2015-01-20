// DlgDisplay.cpp : implementation file
//

#include "stdafx.h"
#include "Transforms.h"
#include "DlgDisplay.h"
#include <math.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

extern CBitmap m_Bitmap;
extern CBitmap bmpDest;
extern int xD,yD;
extern int resizeW,resizeH;
extern BITMAP bmpInfo;
extern CDC dcMemory2;
/////////////////////////////////////////////////////////////////////////////
// CDlgDisplay dialog


CDlgDisplay::CDlgDisplay(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgDisplay::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgDisplay)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CDlgDisplay::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgDisplay)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgDisplay, CDialog)
	//{{AFX_MSG_MAP(CDlgDisplay)
	ON_WM_PAINT()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgDisplay message handlers



void CDlgDisplay::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	
	CDC *pDC =GetDC();

//CDC dcMemoryDlg;

//		dcMemoryDlg.CreateCompatibleDC(pDC);
//		CBitmap* pOldBitmapDlg = dcMemoryDlg.SelectObject(&bmpDest);




	pDC->StretchBlt(10, 10, bmpInfo.bmWidth,bmpInfo.bmHeight,
				&dcMemory2, 0, 0, bmpInfo.bmWidth, bmpInfo.bmHeight, SRCCOPY);
		

	// TODO: Add your message handler code here
	
	// Do not call CDialog::OnPaint() for painting messages
}

void CDlgDisplay::Initialize(double **imageData,int cx,int cy)
{

/*	COLORREF tempData;
	CDC *pDC = GetDC();
	dcMemoryDlg.CreateCompatibleDC(pDC);    
	
	CDC dcDest;
    dcDest.CreateCompatibleDC(NULL);
    CBitmap* pOldBitmap = dcDest.SelectObject(&m_Bitmap);
    BOOL bRet = bmpDest.CreateCompatibleBitmap(&dcDest, cy, cx);
    dcDest.SelectObject(pOldBitmap);
    dcDest.DeleteDC();

	dibDest.CreateDIB(&bmpDest);

	for(int x=0;x<cx;x++)
	{
		for(int y=0;y<cy;y++)
		{
			//BYTE c = (BYTE)max(0,min(255,imageData[x][y]));//log(4+imageData[x][y]);
			int c = 80*log(1+sqrt(imageData[x][y]));
			tempData=RGB(c,c,c);
			dibDest.SetPixel(x,y,tempData);
		}
	}	

	dibDest.SetDIBits(&bmpDest);
	pOldBitmap = dcMemoryDlg.SelectObject(&bmpDest);

	pDC->StretchBlt(10, 10, bmpInfo.bmWidth,bmpInfo.bmHeight,
				&dcMemoryDlg, 0, 0, bmpInfo.bmWidth, bmpInfo.bmHeight, SRCCOPY);

	Invalidate();
*/
}// end of function
