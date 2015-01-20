; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CTransformsView
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "Transforms.h"
LastPage=0

ClassCount=6
Class1=CTransformsApp
Class2=CTransformsDoc
Class3=CTransformsView
Class4=CMainFrame

ResourceCount=4
Resource1=IDD_TRANSFORMS_FORM
Resource2=IDR_MAINFRAME
Class5=CAboutDlg
Resource3=IDD_ABOUTBOX
Class6=CDlgDisplay
Resource4=IDD_TRANSFORMRESULT

[CLS:CTransformsApp]
Type=0
HeaderFile=Transforms.h
ImplementationFile=Transforms.cpp
Filter=N

[CLS:CTransformsDoc]
Type=0
HeaderFile=TransformsDoc.h
ImplementationFile=TransformsDoc.cpp
Filter=N

[CLS:CTransformsView]
Type=0
HeaderFile=TransformsView.h
ImplementationFile=TransformsView.cpp
Filter=D
BaseClass=CFormView
VirtualFilter=VWC
LastObject=IDC_RADIO4


[CLS:CMainFrame]
Type=0
HeaderFile=MainFrm.h
ImplementationFile=MainFrm.cpp
Filter=T




[CLS:CAboutDlg]
Type=0
HeaderFile=Transforms.cpp
ImplementationFile=Transforms.cpp
Filter=D

[DLG:IDD_ABOUTBOX]
Type=1
Class=CAboutDlg
ControlCount=4
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308480
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889

[MNU:IDR_MAINFRAME]
Type=1
Class=CMainFrame
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_SAVE
Command4=ID_FILE_SAVE_AS
Command5=ID_FILE_PRINT
Command6=ID_FILE_PRINT_PREVIEW
Command7=ID_FILE_PRINT_SETUP
Command8=ID_FILE_MRU_FILE1
Command9=ID_APP_EXIT
Command10=ID_EDIT_UNDO
Command11=ID_EDIT_CUT
Command12=ID_EDIT_COPY
Command13=ID_EDIT_PASTE
Command14=ID_VIEW_TOOLBAR
Command15=ID_VIEW_STATUS_BAR
Command16=ID_APP_ABOUT
CommandCount=16

[ACL:IDR_MAINFRAME]
Type=1
Class=CMainFrame
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_SAVE
Command4=ID_FILE_PRINT
Command5=ID_EDIT_UNDO
Command6=ID_EDIT_CUT
Command7=ID_EDIT_COPY
Command8=ID_EDIT_PASTE
Command9=ID_EDIT_UNDO
Command10=ID_EDIT_CUT
Command11=ID_EDIT_COPY
Command12=ID_EDIT_PASTE
Command13=ID_NEXT_PANE
Command14=ID_PREV_PANE
CommandCount=14

[DLG:IDD_TRANSFORMS_FORM]
Type=1
Class=CTransformsView
ControlCount=13
Control1=IDC_STATIC,button,1342177287
Control2=IDC_EDIT1,edit,1350631552
Control3=IDC_STATIC,static,1342308352
Control4=IDC_LOADIMAGE,button,1342242816
Control5=IDC_STATIC,static,1342308352
Control6=IDC_ORIGINALBMP,static,1342177294
Control7=IDC_BUTTON1,button,1342242816
Control8=IDC_RADIO1,button,1342308361
Control9=IDC_RADIO2,button,1342177289
Control10=IDC_RADIO3,button,1342177289
Control11=IDC_RADIO4,button,1342177289
Control12=IDC_BUTTON2,button,1342242816
Control13=IDC_STATIC,button,1342177287

[TB:IDR_MAINFRAME]
Type=1
Class=?
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_SAVE
Command4=ID_EDIT_CUT
Command5=ID_EDIT_COPY
Command6=ID_EDIT_PASTE
Command7=ID_FILE_PRINT
Command8=ID_APP_ABOUT
CommandCount=8

[DLG:IDD_TRANSFORMRESULT]
Type=1
Class=CDlgDisplay
ControlCount=0

[CLS:CDlgDisplay]
Type=0
HeaderFile=DlgDisplay.h
ImplementationFile=DlgDisplay.cpp
BaseClass=CDialog
Filter=D
LastObject=CDlgDisplay
VirtualFilter=dWC

