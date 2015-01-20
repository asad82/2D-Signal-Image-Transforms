// TransformsView.cpp : implementation of the CTransformsView class
//

#include "stdafx.h"
#include "Transforms.h"

#include "TransformsDoc.h"
#include "TransformsView.h"
#include "CDibData.h"
#include "DlgDisplay.h"
#include <math.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CTransformsView

IMPLEMENT_DYNCREATE(CTransformsView, CFormView)

BEGIN_MESSAGE_MAP(CTransformsView, CFormView)
	//{{AFX_MSG_MAP(CTransformsView)
	ON_BN_CLICKED(IDC_LOADIMAGE, OnLoadimage)
	ON_WM_PAINT()
	ON_BN_CLICKED(IDC_BUTTON1, OnButton1)
	ON_BN_CLICKED(IDC_BUTTON2, OnApplyInverseTransform)
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CFormView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CFormView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CFormView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTransformsView construction/destruction

CTransformsView::CTransformsView()
	: CFormView(CTransformsView::IDD)
{
	//{{AFX_DATA_INIT(CTransformsView)
	m_FileName = _T("");
	m_Selection = 0;
	//}}AFX_DATA_INIT
	// TODO: add construction code here
	displayImage=false;
}

CTransformsView::~CTransformsView()
{
}

void CTransformsView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CTransformsView)
	DDX_Control(pDX, IDC_ORIGINALBMP, m_DisplayBmp);
	DDX_Text(pDX, IDC_EDIT1, m_FileName);
	DDX_Radio(pDX, IDC_RADIO1, m_Selection);
	//}}AFX_DATA_MAP
}

BOOL CTransformsView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CFormView::PreCreateWindow(cs);
}

void CTransformsView::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();
	GetParentFrame()->RecalcLayout();
	ResizeParentToFit();

}

/////////////////////////////////////////////////////////////////////////////
// CTransformsView printing

BOOL CTransformsView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CTransformsView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CTransformsView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

void CTransformsView::OnPrint(CDC* pDC, CPrintInfo* /*pInfo*/)
{
	// TODO: add customized printing code here
}

/////////////////////////////////////////////////////////////////////////////
// CTransformsView diagnostics

#ifdef _DEBUG
void CTransformsView::AssertValid() const
{
	CFormView::AssertValid();
}

void CTransformsView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}

CTransformsDoc* CTransformsView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CTransformsDoc)));
	return (CTransformsDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CTransformsView message handlers

	CBitmap m_Bitmap;
	BITMAP bmpInfo;
	CDibData m_DibData;
	int resizeW=400,resizeH=350;
	CDC dcMemory,dcMemory1,dcMemory2;
	int xD=40,yD=120;
	

void CTransformsView::OnLoadimage() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
		CFileDialog m_ldFile(TRUE);

		if (m_ldFile.DoModal() == IDOK)
		{
			m_FileName=m_ldFile.GetPathName();
			UpdateData(FALSE);

		}
		
		HBITMAP hBitmap = m_DibData.LoadDIB(m_FileName);
		if( !hBitmap )
			return; 
    
		m_Bitmap.Attach(hBitmap);
		m_Bitmap.GetBitmap(&bmpInfo);
		
		// code for preprocessing for displaying bitmap on the screen

		CDC *pDC = GetDC();
		dcMemory.CreateCompatibleDC(pDC);
		dcMemory1.CreateCompatibleDC(pDC);
		dcMemory2.CreateCompatibleDC(pDC);

		//CBitmap* pOldBitmap = dcMemory.SelectObject(&m_Bitmap);


		ProcessImageData();
		

		pDC->StretchBlt(xD, yD, bmpInfo.bmWidth,bmpInfo.bmHeight,
				&dcMemory, 0, 0, bmpInfo.bmWidth, bmpInfo.bmHeight, SRCCOPY);
		
		displayImage=true; // used by WM_PAINT event so errors could be avoided

		//m_DisplayBmp.SetBitmap(hBitmap); // displays bmp without resetting size


}// end of function



void CTransformsView::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	
	// TODO: Add your message handler code here
	if(displayImage)
	{
		CDC * pDC = GetDC();
		pDC->StretchBlt(xD, yD, bmpInfo.bmWidth/*resizeW*/,bmpInfo.bmHeight/*resizeH*/,
				&dcMemory, 0, 0, bmpInfo.bmWidth, bmpInfo.bmHeight, SRCCOPY);

		pDC->StretchBlt(xD+bmpInfo.bmWidth+50, yD, bmpInfo.bmWidth/*resizeW*/,bmpInfo.bmHeight/*resizeH*/,
				&dcMemory1, 0, 0, bmpInfo.bmWidth, bmpInfo.bmHeight, SRCCOPY);

		if(m_Selection!=3)
			pDC->StretchBlt(xD+bmpInfo.bmWidth*2+50, yD, bmpInfo.bmWidth/*resizeW*/,bmpInfo.bmHeight/*resizeH*/,
					&dcMemory2, 0, 0, bmpInfo.bmWidth, bmpInfo.bmHeight, SRCCOPY);

	}
	// Do not call CFormView::OnPaint() for painting messages
}// end of function

CDibData dibDest, dibDest1,dibDest2;
CBitmap bmpDest, bmpDest1,bmpDest2;

CDlgDisplay dlg;
double **imageData,**imaginaryData,**magnitudeImage,**phaseImage;
double *real, *imag;
double *real2, *imag2;
COLORREF tempData;
int cx,cy;


void CTransformsView::ProcessImageData()
{


CDibData dibSrc;
dibSrc.CreateDIB(&m_Bitmap);
    
    
int x, y, t;
 cx = dibSrc.GetWidth();
 cy = dibSrc.GetHeight();

BOOL bResult = FALSE;

// Create destination bitmap bits object


    CDC dcDest;
    dcDest.CreateCompatibleDC(NULL);
    CBitmap* pOldBitmap = dcDest.SelectObject(&m_Bitmap);
    BOOL bRet = bmpDest.CreateCompatibleBitmap(&dcDest, cy, cx);
    dcDest.SelectObject(pOldBitmap);
    dcDest.DeleteDC();

	dibDest.CreateDIB(&bmpDest);
   
    // create another destination dc

	CDC dcDest1;
    dcDest1.CreateCompatibleDC(NULL);
    pOldBitmap = dcDest1.SelectObject(&m_Bitmap);
    bRet = bmpDest1.CreateCompatibleBitmap(&dcDest1, cy, cx);
    dcDest1.SelectObject(pOldBitmap);
    dcDest1.DeleteDC();

	dibDest1.CreateDIB(&bmpDest1);

    // create another destination dc

	CDC dcDest2;
    dcDest2.CreateCompatibleDC(NULL);
    pOldBitmap = dcDest2.SelectObject(&m_Bitmap);
    bRet = bmpDest2.CreateCompatibleBitmap(&dcDest2, cy, cx);
    dcDest2.SelectObject(pOldBitmap);
    dcDest2.DeleteDC();

	dibDest2.CreateDIB(&bmpDest1);
		

    for( x = 0; x < cx; ++x )
    {
        //t = cy - 1;
        for( y = 0; y < cy; y++/*, --t*/ )
        {
			tempData=dibSrc.GetPixel(x,y);
			double R=GetRValue(tempData);
			double G=GetGValue(tempData);
			double B=GetBValue(tempData);
			BYTE gray=(R*0.299 + G*0.587 + B*0.114);
			tempData=RGB(gray,gray,gray);
			dibDest.SetPixel(x,y,tempData);
			//dibDest1.SetPixel(x,y,tempData);

//			dibDest.CopyPixelValue( x, y, dibSrc, x, y);
//			dibDest1.CopyPixelValue( x, y, dibSrc, x, y);
		}
    }

	

imageData= new double*[cx];
imaginaryData= new double*[cx];
magnitudeImage= new double*[cx];
phaseImage= new double*[cx];

for(x=0;x<cy;x++)
{
	imageData[x] = new double[cx];
	imaginaryData[x] = new double [cx];
	magnitudeImage[x] = new double [cx];
	phaseImage[x]= new double [cx];

}
real= new double[cx];
imag= new double[cx];
real2= new double[cx];
imag2= new double[cx];



//************************ Copy the image data into an array **********************//
	for(x=0;x<cx;x++)
	{
		for(y=0;y<cy;y++)
		{
			tempData=dibDest.GetPixel(x,y);
			imageData[x][y]=GetRValue(tempData);
		}// end of inner for loop

	}// end of outer for loop


	dibDest.SetDIBits(&bmpDest);
	//CDC *pDC = GetDC();

	//dcMemory.CreateCompatibleDC(pDC);
	pOldBitmap = dcMemory.SelectObject(&bmpDest);


	// display a new dialog and display the transform output on it

	CDC dcMemoryDlg;

/*		CDC *pDCDlg=dlg.GetDC();
		dcMemoryDlg.CreateCompatibleDC(pDCDlg);
		CBitmap* pOldBitmapDlg = dcMemoryDlg.SelectObject(&bmpDest);
		pDCDlg->StretchBlt(xD, yD, resizeW,resizeH,
				&dcMemoryDlg, 0, 0, bmpInfo.bmWidth, bmpInfo.bmHeight, SRCCOPY);
*/	
	
     


}// end of function

void CTransformsView::OnButton1() 
{
	UpdateData(TRUE);
	// TODO: Add your control notification handler code here
	if(m_Selection==0)
	{
		DiscreteFourierTransformForward();
	}
	else if(m_Selection==1)
	{
		DCTForward();

	}
	else if(m_Selection==2)
	{
		DWalshTForward();
	}
	else if(m_Selection==3)
	{

		WaveletTransformForward();
	}
     //dlg.ShowWindow(SW_SHOW);	
}


void CTransformsView::OnApplyInverseTransform() 
{
	// TODO: Add your control notification handler code here

	if(m_Selection==0)
	{
		DiscreteFourierTransformInverse();	
	}
	else if(m_Selection==1)
	{
		DCTInverse();

	}
	else if(m_Selection==2)
	{
		DWalshTInverse();
	}
	else if(m_Selection==3)
	{

		WaveletTransformInverse();
	}
	
	
}



void CTransformsView::DFT(double *xVal, double *yVal, int direction, long length, double *xValOut, double *yValOut)
{
   double theta;
   double cosTheta,sinTheta;
   
   for (long i=0;i<length;i++) 
   {
      xValOut[i] = 0;
      yValOut[i] = 0;
      theta = - direction * 2.0 * 3.14159265358f * i / (double)length;
      for (long j=0;j<length;j++) 
	  {
         cosTheta = cos(j * theta);
         sinTheta = sin(j * theta);
         xValOut[i] += (xVal[j] * cosTheta - yVal[j] * sinTheta);
         yValOut[i] += (xVal[j] * sinTheta + yVal[j] * cosTheta);
      }
   }
   

   if (direction == 1) // if inverse transform then divide by two
   {
      for (long i=0;i<length;i++) 
	  {
         xVal[i] = xValOut[i] / length;
         yVal[i] = yValOut[i] / length;
      }
   } 
   else  // if forward transform then no need to divide by N i.e length
   {
      for (long i=0;i<length;i++) 
	  {
         xVal[i] = xValOut[i];
         yVal[i] = yValOut[i];
      }
   }



}// end of function





CDlgDisplay dlgM,dlgP;

void CTransformsView::DiscreteFourierTransformForward()
{
int x,y;
// apply transform on the rows first
	for(x=0;x<cx;x++)
	{
		for(y=0;y<cy;y++)
		{
			real[y]=imageData[x][y];
			imag[y]=-128;
		}
		DFT(real,imag,-1,cy,real2,imag2);

		for(y=0;y<cy;y++)
		{
			imageData[x][y] = real[y];
			imaginaryData[x][y]=imag[y];
		}

	}


// apply transform on the columns
	for(y=0;y<cy;y++)
	{
		for(x=0;x<cx;x++)
		{
			real[x]=imageData[x][y];
			imag[x]=imaginaryData[x][y];
		}
		DFT(real,imag,-1,cx,real2,imag2);

		for(x=0;x<cx;x++)
		{
			imageData[x][y]=real[x];
			imaginaryData[x][y]=imag[x];
		}

	}

	// copy the real part of the transform for display
	for(x=0;x<cx;x++)
	{
		for(y=0;y<cy;y++)
		{
			//BYTE c = (BYTE)max(0,min(255,imageData[x][y]));//log(4+imageData[x][y]);
			int c = 80*log(1+sqrt(imageData[x][y]));
			tempData=RGB(c,c,c);
			dibDest.SetPixel(x,y,tempData);
		}
	}	

	dibDest.SetDIBits(&bmpDest);
	CBitmap *pOldBitmap = dcMemory.SelectObject(&bmpDest);

	CDC *pDC=GetDC();
	pDC->StretchBlt(xD, yD, bmpInfo.bmWidth/*resizeW*/,bmpInfo.bmHeight/*resizeH*/,
				&dcMemory, 0, 0, bmpInfo.bmWidth, bmpInfo.bmHeight, SRCCOPY);

	//dlg.Create(IDD_TRANSFORMRESULT, this);
    //dlg.Initialize(imageData,cx,cy);
	//dlg.ShowWindow(SW_SHOW);	

	// compute the magnitude image
	for(x=0;x<cx;x++)
	{
		for(y=0;y<cy;y++)
		{
			magnitudeImage[x][y]=sqrt(imageData[x][y]*imageData[x][y]+imaginaryData[x][y]*imaginaryData[x][y]);
			phaseImage[x][y]=atan((double)imaginaryData[x][y]/(double)imageData[x][y]);
		}

	}

//	dlgM.Create(IDD_TRANSFORMRESULT, this);
//	dlgM.ShowWindow(SW_SHOW);
//    dlgM.Initialize(magnitudeImage,cx,cy);

//	dlgP.Create(IDD_TRANSFORMRESULT, this);
//	dlgP.ShowWindow(SW_SHOW);	
//    dlgP.Initialize(phaseImage,cx,cy);

	DisplayMagnitudePhase();

}// end of function


void CTransformsView::DisplayMagnitudePhase()
{
	int x,y;

	for(x=0;x<cx;x++)
	{
		for(y=0;y<cy;y++)
		{
			//BYTE c = (BYTE)max(0,min(255,imageData[x][y]));//log(4+imageData[x][y]);
			int c = 80*log(1+sqrt(magnitudeImage[x][y]));
			tempData=RGB(c,c,c);
			dibDest1.SetPixel(x,y,tempData);
		}
	}	
	dibDest1.SetDIBits(&bmpDest1);
	CBitmap *pOldBitmap = dcMemory1.SelectObject(&bmpDest1);


	for(x=0;x<cx;x++)
	{
		for(y=0;y<cy;y++)
		{
			//BYTE c = (BYTE)max(0,min(255,imageData[x][y]));//log(4+imageData[x][y]);
			int c = 150*log(1+sqrt(phaseImage[x][y]));
			tempData=RGB(c,c,c);
			dibDest2.SetPixel(x,y,tempData);
		}
	}	
	dibDest2.SetDIBits(&bmpDest2);
	pOldBitmap = dcMemory2.SelectObject(&bmpDest2);

	CDC *pDC=GetDC();

		pDC->StretchBlt(xD+bmpInfo.bmWidth+50, yD, bmpInfo.bmWidth,bmpInfo.bmHeight,
				&dcMemory1, 0, 0, bmpInfo.bmWidth, bmpInfo.bmHeight, SRCCOPY);

		pDC->StretchBlt(xD+(bmpInfo.bmWidth*2)+50*2, yD, bmpInfo.bmWidth,bmpInfo.bmHeight,
				&dcMemory2, 0, 0, bmpInfo.bmWidth, bmpInfo.bmHeight, SRCCOPY);


}// end of function




void CTransformsView::DiscreteFourierTransformInverse()
{
int x,y;
//************************* Inverse Transform ************************************//

// apply inverse transform on the rows first
	for(x=0;x<cx;x++)
	{
		for(y=0;y<cy;y++)
		{
			real[y]=imageData[x][y];
			imag[y]=imaginaryData[x][y];
		}
		DFT(real,imag,1,cy,real2,imag2);

		for(y=0;y<cy;y++)
		{
			imageData[x][y] = real[y];
			imaginaryData[x][y] = imag[y];//=-128;
		}

	}


// apply inverse transform on the columns
	for(y=0;y<cy;y++)
	{
		for(x=0;x<cx;x++)
		{
			real[x]=imageData[x][y];
			imag[x]=imaginaryData[x][y];
		}
		DFT(real,imag,1,cx,real2,imag2);

		for(x=0;x<cx;x++)
		{
			imageData[x][y]=real[x];
			imaginaryData[x][y]=imag[x];//=-128;
		}

	}

	for(x=0;x<cx;x++)
	{
		for(y=0;y<cy;y++)
		{
			BYTE c = imageData[x][y];//(BYTE)max(0,min(255,imageData[x][y]));//log(4+imageData[x][y]);
			//BYTE c = log(imageData[x][y])*5;
			tempData=RGB(c,c,c);
			dibDest.SetPixel(x,y,tempData);
		}
	}


//**********************************************************************************
	dibDest.SetDIBits(&bmpDest);
	CBitmap *pOldBitmap = dcMemory.SelectObject(&bmpDest);

	CDC * pDC = GetDC();
	pDC->StretchBlt(xD, yD, bmpInfo.bmWidth/*resizeW*/,bmpInfo.bmHeight/*resizeH*/,
				&dcMemory, 0, 0, bmpInfo.bmWidth, bmpInfo.bmHeight, SRCCOPY);
	
	//dlg.Create(IDD_TRANSFORMRESULT, this);
    //dlg.ShowWindow(SW_SHOW);	

}// end of function




















//		HINSTANCE h;
//		HBITMAP hbitmap =::LoadBitmap(h,m_FileName);
//		CBitmap bmp;
//		bmp.LoadBitmap((UINT)m_FileName);
		//::LoadImage
/*	HBITMAP	hBitmap= CreateDIBitmap(pDC->GetSafeHdc(),(BITMAPINFOHEADER*)lpbi, 
					 CBM_INIT, tempImage,(LPBITMAPINFO)lpbi,DIB_RGB_COLORS);

	m_setAvi.SetBitmap(hBitmap);
*/

/*
	pDC=m_movieDisplay.GetDC();
	if(frameNo<length)
	{
		if (pFrame)
        {
            lpbi = (LPBITMAPINFOHEADER)AVIStreamGetFrame(pFrame, frameNo);            
			pdata=(char *)lpbi+lpbi->biSize+lpbi->biClrUsed * sizeof(RGBQUAD);	// Pointer To Data Returned By AVIStreamGetFrame			

			TrackObject();

//		lpbi->biWidth=176;
//		lpbi->biHeight=144;
int check=StretchDIBits( 
		pDC->GetSafeHdc(),
		0,
		0,
		width,
		height,
		0,					// Row position to display bitmap on screen
		0,					// Col position to display bitmap on screen
		lpbi->biWidth,		// m_SourceBmp's number of columns
		lpbi->biHeight,		// m_SourcdeBmp's number of rows
		pdata,				// The bitmap to display; 
		(BITMAPINFO*)lpbi,  // The bitmap's header info e.g. width, height, number of bits etc
		DIB_RGB_COLORS,		// Use default 24-bit color table
		SRCCOPY				// Just display
	);


CBitmap Bmp;
	CBrush brBits;
	WORD wBits[] = { 0x00, 0x22, 0x44, 0x88, 0x00, 0x22, 0x44, 0x88,
		        0x22, 0x44, 0x88, 0x00, 0x22, 0x44, 0x88, 0x00,
		        0x44, 0x88, 0x00, 0x22, 0x44, 0x88, 0x00, 0x22,
		        0x88, 0x00, 0x22, 0x44, 0x88, 0x00, 0x22, 0x44 };

	Bmp.CreateBitmap(32, 32, 1, 1, wBits);

	brBits.CreatePatternBrush(&Bmp);
	CBrush* pOldBrush = (CBrush*)pDC->SelectObject(&brBits);

	pDC->Rectangle(20, 20, 400, 400);



*/

void CTransformsView::DCTForward()
{
	int u,v,x,y;
	const double PI = 3.141;

		for(u=0;u<cx;u++)
			for(v=0;v<cy;v++)
				magnitudeImage[u][v]=0;

		for (u=0; u<cx; u++) 
		{
			for (v=0; v<cy; v++) 
			{
				for (x=0; x<cx; x++) 
				{
					for (y=0; y<cy; y++) 
					{
						double cosArg1=( (2*x+1)*u*PI )/(double)(2*cx);
						double cosArg2=( (2*y+1)*v*PI )/(double)(2*cy);
						magnitudeImage[u][v] += ( imageData[x][y] * cos( cosArg1) * cos( cosArg2)   );
					}
				}
				if(u==0 && v==0)
					magnitudeImage[u][v]=magnitudeImage[u][v]*(double)1/(double)cx;
				else if (u==0 && v>0)
					magnitudeImage[u][v]=magnitudeImage[u][v]*sqrt((double)1/(double)cx)*sqrt((double)2/(double)cy);
				else if (u>0 && v==0)
					magnitudeImage[u][v]=magnitudeImage[u][v]*sqrt((double)2/(double)cx)*sqrt((double)1/(double)cy);
				else
					magnitudeImage[u][v]=magnitudeImage[u][v]*(double)2/(double)cx;
				
			}
		}// end of outer for loop


	// copy the data for display
	for(x=0;x<cx;x++)
	{
		for(y=0;y<cy;y++)
		{
			int c = 80*log(1+sqrt(magnitudeImage[x][y]));
			tempData=RGB(c,c,c);
			dibDest1.SetPixel(x,y,tempData);
		}
	}	

	dibDest1.SetDIBits(&bmpDest1);
	CBitmap *pOldBitmap = dcMemory1.SelectObject(&bmpDest1);

	CDC *pDC=GetDC();
	pDC->StretchBlt(xD+bmpInfo.bmWidth+50, yD, bmpInfo.bmWidth,bmpInfo.bmHeight,
				&dcMemory1, 0, 0, bmpInfo.bmWidth, bmpInfo.bmHeight, SRCCOPY);




}// end of function



void CTransformsView::DCTInverse()
{
	int x,y,u,v;
	double tempVar=0;

	const double PI = 3.141;

	for(u=0;u<cx;u++)
		for(v=0;v<cy;v++)
			phaseImage[u][v]=0;


	for (x=0; x<cx; x++) 
		{
			for (y=0; y<cy; y++) 
			{
				for (u=0; u<cx; u++) 
				{
					for (v=0; v<cy; v++) 
					{
						double cosArg1=( (2*x+1)*u*PI )/(double)(2*cx);
						double cosArg2=( (2*y+1)*v*PI )/(double)(2*cy);
						tempVar= ( magnitudeImage[u][v] * cos( cosArg1) * cos( cosArg2)   );
						
						if(u==0 && v==0)
							tempVar=tempVar*(double)1/(double)cx;
						else if(u==0 && v >0)
							tempVar=tempVar*sqrt((double)1/(double)cx)*sqrt((double)2/(double)cy);
						else if(v==0 && u >0)
							tempVar=tempVar*sqrt((double)2/(double)cx)*sqrt((double)1/(double)cy);
						else 
							tempVar=tempVar*(double)2/(double)cx;
						
						phaseImage[x][y]+=tempVar;
					}
				}				
			}
		}// end of outer for loop

	// copy the data for display
	for(x=0;x<cx;x++)
	{
		for(y=0;y<cy;y++)
		{
			int c = phaseImage[x][y];
			tempData=RGB(c,c,c);
			dibDest2.SetPixel(x,y,tempData);
		}
	}	

	dibDest2.SetDIBits(&bmpDest2);
	CBitmap *pOldBitmap = dcMemory2.SelectObject(&bmpDest2);

	CDC *pDC=GetDC();
	pDC->StretchBlt(xD+(bmpInfo.bmWidth*2)+50*2, yD, bmpInfo.bmWidth,bmpInfo.bmHeight,
				&dcMemory2, 0, 0, bmpInfo.bmWidth, bmpInfo.bmHeight, SRCCOPY);





}// end of function

void CTransformsView::DWalshTForward()
{

		int x,y,u,v;
		// NOTE: Input image must be square cx=cy
		// compute the value of small n from the value of Capital N
		int N = cx;
		int n=0;
		int value=0;
		while(value!=N)
		{
			n++;
			value=pow(2,n);
		}

		int tempX,tempY,tempU,tempV,bix,biy,piu,piv,b1u,b2u,b1v,b2v;
		int summation;

		// clear the buffer
		for(x=0;x<cx;x++)
			for(y=0;y<cy;y++)
			{
				magnitudeImage[x][y]=0;
				phaseImage[x][y]=0; // to store inverse transform later
			}

		for (u=0; u<N; u++) 
		{
			for (v=0; v<N; v++) 
			{
				for (x=0; x<N; x++) 
				{
					for (y=0; y<N; y++) 
					{
						summation=0;
						for(int i=0;i<n;i++)
						{
							tempX=x; tempY=y; tempU=u,tempV=v;
							tempX >>= i;
							tempY >>= i;
							bix = tempX & 1;
							biy = tempY & 1;
							// compute the value of p for u
							if(i==0)
							{
								tempU >>= n-1;
								piu = tempU & 1;
							}
							else
							{
								tempU >>= n-i;
								b1u = tempU & 1;
								tempU=u; // reset the value and compute again
								tempU >>= (n-(i+1));
								b2u = tempU & 1;
								piu = b1u + b2u;
							}
							
							// compute the value of p for v
							if(i==0)
							{
								tempV >>= n-1;
								piv = tempV & 1;
							}
							else
							{
								tempV >>= n-i;
								b1v = tempV & 1;
								tempV=v; // reset the value and compute again
								tempV >>= (n-(i+1));
								b2v = tempV & 1;
								piv = b1v + b2v;
							}
							
							int sum=(bix*piu) + (biy*piv);
							summation+=sum;

						}// end of for loop on i
						magnitudeImage[u][v] += ( imageData[x][y] *( pow(-1,summation) )  );
					}
				}
				magnitudeImage[u][v]=(magnitudeImage[u][v]/(double)N);
			}
		}// end of outer for loop



	// copy the data for display
	for(x=0;x<cx;x++)
	{
		for(y=0;y<cy;y++)
		{
			int c = 80*log(1+sqrt(magnitudeImage[x][y]));
			tempData=RGB(c,c,c);
			dibDest1.SetPixel(x,y,tempData);
		}
	}	

	dibDest1.SetDIBits(&bmpDest1);
	CBitmap *pOldBitmap = dcMemory1.SelectObject(&bmpDest1);

	CDC *pDC=GetDC();
	pDC->StretchBlt(xD+bmpInfo.bmWidth+50, yD, bmpInfo.bmWidth,bmpInfo.bmHeight,
				&dcMemory1, 0, 0, bmpInfo.bmWidth, bmpInfo.bmHeight, SRCCOPY);



}// end of function



void CTransformsView::DWalshTInverse()
{

		int x,y,u,v;
		// NOTE: Input image must be square cx=cy
		// compute the value of small n from the value of Capital N
		int N = cx;
		int n=0;
		int value=0;
		while(value!=N)
		{
			n++;
			value=pow(2,n);
		}

		int tempX,tempY,tempU,tempV,bix,biy,piu,piv,b1u,b2u,b1v,b2v;
		int summation;

		for (x=0; x<N; x++) 
		{
			for (y=0; y<N; y++) 
			{
				for (u=0; u<N; u++) 
				{
					for (v=0; v<N; v++) 
					{
						summation=0;
						for(int i=0;i<n;i++)
						{
							tempX=x; tempY=y; tempU=u,tempV=v;
							tempX >>= i;
							tempY >>= i;
							bix = tempX & 1;
							biy = tempY & 1;
							// compute the value of p for u
							if(i==0)
							{
								tempU >>= n-1;
								piu = tempU & 1;
							}
							else
							{
								tempU >>= n-i;
								b1u = tempU & 1;
								tempU=u; // reset the value and compute again
								tempU >>= (n-(i+1));
								b2u = tempU & 1;
								piu = b1u + b2u;
							}
							
							// compute the value of p for v
							if(i==0)
							{
								tempV >>= n-1;
								piv = tempV & 1;
							}
							else
							{
								tempV >>= n-i;
								b1v = tempV & 1;
								tempV=v; // reset the value and compute again
								tempV >>= (n-(i+1));
								b2v = tempV & 1;
								piv = b1v + b2v;
							}
							
							int sum=(bix*piu) + (biy*piv);
							summation+=sum;

						}// end of for loop on i
						phaseImage[x][y] += ( magnitudeImage[u][v] *( pow(-1,summation) )  );
					}
				}
				phaseImage[x][y]=(phaseImage[x][y]/(double)N);
			}
		}// end of outer for loop


	// copy the data for display
	for(x=0;x<cx;x++)
	{
		for(y=0;y<cy;y++)
		{
			int c = phaseImage[x][y];
			tempData=RGB(c,c,c);
			dibDest2.SetPixel(x,y,tempData);
		}
	}	

	dibDest2.SetDIBits(&bmpDest2);
	CBitmap *pOldBitmap = dcMemory2.SelectObject(&bmpDest2);

	CDC *pDC=GetDC();
	pDC->StretchBlt(xD+(bmpInfo.bmWidth*2)+50*2, yD, bmpInfo.bmWidth,bmpInfo.bmHeight,
				&dcMemory2, 0, 0, bmpInfo.bmWidth, bmpInfo.bmHeight, SRCCOPY);




}// end of function


const int filterLength=4;
		// filters
		double db4ALowpass[4]={0.482963, 0.836516, 0.224144, -0.129910};
		double db4AHighpass[4]={-0.129910, -0.224144, 0.836516, -0.482963};
double *outputData,*inputData;

void CTransformsView::WaveletTransformForward()
{

	int x,y,N=cx;
	inputData = new double[(N+(filterLength*2))];
	outputData = new double[(N+(filterLength*2))];


		// first of all convolve the lowpass & Highpass filters with the rows
		for( x=0;x<(N);x++)
		{	
			// copy the row data
			for( y=0;y<(N);y++)
			{
				outputData[y]=0;
				inputData[y+filterLength]=imageData[x][y];
			}
			TransformOperation(N);

			// copy back the transformed data
			for(y=0;y<(N);y++)
			{
				magnitudeImage[x][y]=outputData[y+filterLength];
			}

		}// end of outer for loop


		
		// now convolve the columns with the lowpass & highpass filters
		for( y=0;y<(N);y++)
		{	
			// copy the column data
			for( x=0;x<(N);x++)
			{
				outputData[x]=0;
				inputData[x+filterLength]=magnitudeImage[x][y];
			}
			TransformOperation(N);

			// copy back the transformed data
			for(x=0;x<(N);x++)
			{
				magnitudeImage[x][y]=outputData[x+filterLength];
			}

		}// end of outer for loop


	// copy the data for display
	for(x=0;x<cx;x++)
	{
		for(y=0;y<cy;y++)
		{
			int c = 80*log(1+sqrt(magnitudeImage[x][y]));//abs(magnitudeImage[x][y]);
			tempData=RGB(c,c,c);
			dibDest1.SetPixel(x,y,tempData);
		}
	}	

	dibDest1.SetDIBits(&bmpDest1);
	CBitmap *pOldBitmap = dcMemory1.SelectObject(&bmpDest1);

	CDC *pDC=GetDC();
	pDC->StretchBlt(xD+bmpInfo.bmWidth+50, yD, bmpInfo.bmWidth,bmpInfo.bmHeight,
				&dcMemory1, 0, 0, bmpInfo.bmWidth, bmpInfo.bmHeight, SRCCOPY);



}// end of function

void CTransformsView::TransformOperation(int length)
{


	// do periodic extension
	Periodic_Extension(inputData,length);
	
	// clear the output array
	for(int k=0;k<(length+filterLength*2);k++)
		outputData[k]=0;

	int index=length/2;
	
	for(int x=0;x<(length/2);x++)
	{
		for(int i=0;i<filterLength;i++)
		{
			double value = inputData[2*x+i] * db4ALowpass[i];
			outputData[x+filterLength]+=value;			
		}
	}			

	for(x=0;x<(length/2);x++,index++)
	{
		for(int i=0;i<filterLength;i++)
		{
			double value = inputData[2*x+i] * db4AHighpass[i];
			outputData[index+filterLength]+=value;			
		}
	}			



}// end of function

void CTransformsView::Periodic_Extension(double *output, int size)
{
  int npad=filterLength;	
  int first = npad, last = npad + size-1;

  // extend left periodically
  while (first > 0) 
  {
    first--;
    output[first] = output[first+size];
  }

  // extend right periodically
  while (last < 2*npad+size-1) 
  {
    last++;
    output[last] = output[last-size];
  }

}// end of function



void CTransformsView::WaveletTransformInverse()
{

	int x,y,N=cx;
	inputData = new double[(N+(filterLength*2))];
	outputData = new double[(N+(filterLength*2))];


		// first of all convolve the lowpass & Highpass filters with the columns
		for( y=0;y<(N);y++)
		{	
			// copy the row data
			for(int x=0;x<N;x++)
			{
				outputData[x]=0;
				inputData[x+filterLength]=magnitudeImage[x][y];
			}
			InverseTransformOperation(N);

			// copy back the transformed data
			for(x=0;x<N;x++)
			{
				phaseImage[x][y]=outputData[x+filterLength];
			}

		}// end of outer for loop

		
		// now convolve the rows with the lowpass & highpass filters
		for( x=0;x<(N);x++)
		{	
			// copy the column data
			for(int y=0;y<N;y++)
			{
				outputData[y]=0;
				inputData[y+filterLength]=phaseImage[x][y];
			}
			InverseTransformOperation(N);

			// copy back the transformed data
			for(y=0;y<N;y++)
			{
				phaseImage[x][y]=outputData[y+filterLength];
			}

		}// end of outer for loop


	// copy the data for display
	for(x=0;x<cx;x++)
	{
		for(y=0;y<cy;y++)
		{
			int c = (int) min(phaseImage[x][y],255);
			tempData=RGB(c,c,c);
			dibDest2.SetPixel(x,y,tempData);
		}
	}	

	dibDest2.SetDIBits(&bmpDest2);
	CBitmap *pOldBitmap = dcMemory2.SelectObject(&bmpDest2);

//	CDC *pDC=GetDC();
//	pDC->StretchBlt(xD+(bmpInfo.bmWidth*2)+50*2, yD, bmpInfo.bmWidth,bmpInfo.bmHeight,
//				&dcMemory2, 0, 0, bmpInfo.bmWidth, bmpInfo.bmHeight, SRCCOPY);


	dlg.Create(IDD_TRANSFORMRESULT, this);
  	dlg.ShowWindow(SW_SHOW);	


}// end of function

void CTransformsView::InverseTransformOperation(int length)
{

	int index=length/2;
	double * halfInput;

	halfInput = new double [(length/2)+(filterLength*2)];

	//****************************************
	// do periodic extension for Lowpass data

	for(int k=0;k<length/2;k++)
		halfInput[filterLength + k] = inputData[k];
	
	Periodic_Extension(halfInput,length/2);


	for(int x=0;x<(length/2);x++)
	{
		for(int i=0;i<filterLength;i++)
		{
			double value = halfInput[filterLength+x+i] * db4ALowpass[i];
			outputData[2*x+i+filterLength]+=value;
		}
	}			

	//****************************************
	// do periodic extension for Highpass data
	int j=0;
	for( k=length/2;k<length;k++)
		halfInput[filterLength + j++]=inputData[k];

	Periodic_Extension(halfInput,length/2);


	for(x=0;x<(length/2);x++,index++)
	{
		for(int i=0;i<filterLength;i++)
		{
			double value = halfInput[filterLength+x+i] * db4AHighpass[i];
			outputData[2*x+i+filterLength]+=value;			

		}
	}			



}// end of function
