; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CBitmapWnd
LastTemplate=generic CWnd
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "mosaique.h"
LastPage=0

ClassCount=8
Class1=CChildFrame
Class2=CMainFrame
Class3=CMosaiqueApp
Class4=CAboutDlg
Class5=CMosaiqueDoc
Class6=CMosaiqueView
Class7=CMyDragList

ResourceCount=4
Resource1=IDR_MAINFRAME (French (France))
Resource2=IDD_ABOUTBOX (French (France))
Resource3=IDR_MOSAIQTYPE (French (France))
Resource4=IDD_MOSAIQUE_FORM (French (France))
Class8=CBitmapWnd

[CLS:CChildFrame]
Type=0
BaseClass=CMDIChildWnd
HeaderFile=ChildFrm.h
ImplementationFile=ChildFrm.cpp

[CLS:CMainFrame]
Type=0
BaseClass=CMDIFrameWnd
HeaderFile=MainFrm.h
ImplementationFile=MainFrm.cpp

[CLS:CMosaiqueApp]
Type=0
BaseClass=CWinApp
HeaderFile=Mosaique.h
ImplementationFile=Mosaique.cpp

[CLS:CAboutDlg]
Type=0
BaseClass=CDialog
HeaderFile=Mosaique.cpp
ImplementationFile=Mosaique.cpp
LastObject=CAboutDlg

[CLS:CMosaiqueDoc]
Type=0
BaseClass=CDocument
HeaderFile=MosaiqueDoc.h
ImplementationFile=MosaiqueDoc.cpp

[CLS:CMosaiqueView]
Type=0
BaseClass=CFormView
HeaderFile=MosaiqueView.h
ImplementationFile=MosaiqueView.cpp
Filter=D
VirtualFilter=VWC
LastObject=CMosaiqueView

[CLS:CMyDragList]
Type=0
BaseClass=CDragListBox
HeaderFile=MyDragList.h
ImplementationFile=MyDragList.cpp

[DLG:IDD_ABOUTBOX]
Type=1
Class=CAboutDlg

[DLG:IDD_MOSAIQUE_FORM]
Type=1
Class=CMosaiqueView

[DLG:IDD_MOSAIQUE_FORM (French (France))]
Type=1
Class=?
ControlCount=13
Control1=IDC_NBLIGNES,edit,1350631552
Control2=IDC_SPIN1,msctls_updown32,1342177462
Control3=IDC_NBCOLONNES,edit,1350631552
Control4=IDC_SPIN2,msctls_updown32,1342177462
Control5=IDC_STATIC,static,1342308352
Control6=IDC_STATIC,static,1342308352
Control7=IDC_BORDURE,button,1342242819
Control8=IDC_NOMDEFICHIER,button,1342242819
Control9=IDC_LISTE,listbox,1353777425
Control10=IDC_PLUSHAUT,button,1342251008
Control11=IDC_PLUSBAS,button,1342242816
Control12=IDC_MEMO,edit,1350633600
Control13=IDC_BUTTON3,button,1342242816

[TB:IDR_MAINFRAME (French (France))]
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

[MNU:IDR_MAINFRAME (French (France))]
Type=1
Class=?
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_PRINT_SETUP
Command4=ID_FILE_MRU_FILE1
Command5=ID_APP_EXIT
Command6=ID_VIEW_TOOLBAR
Command7=ID_VIEW_STATUS_BAR
Command8=ID_APP_ABOUT
CommandCount=8

[MNU:IDR_MOSAIQTYPE (French (France))]
Type=1
Class=?
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_CLOSE
Command4=ID_FILE_SAVE
Command5=ID_FILE_SAVE_AS
Command6=ID_FILE_PRINT
Command7=ID_FILE_PRINT_PREVIEW
Command8=ID_FILE_PRINT_SETUP
Command9=ID_FILE_MRU_FILE1
Command10=ID_APP_EXIT
Command11=ID_EDIT_UNDO
Command12=ID_EDIT_CUT
Command13=ID_EDIT_COPY
Command14=ID_EDIT_PASTE
Command15=ID_VIEW_TOOLBAR
Command16=ID_VIEW_STATUS_BAR
Command17=ID_WINDOW_NEW
Command18=ID_WINDOW_CASCADE
Command19=ID_WINDOW_TILE_HORZ
Command20=ID_WINDOW_ARRANGE
Command21=ID_APP_ABOUT
CommandCount=21

[ACL:IDR_MAINFRAME (French (France))]
Type=1
Class=?
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

[DLG:IDD_ABOUTBOX (French (France))]
Type=1
Class=?
ControlCount=4
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308480
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889

[CLS:CBitmapWnd]
Type=0
HeaderFile=BitmapWnd.h
ImplementationFile=BitmapWnd.cpp
BaseClass=CWnd
Filter=W
LastObject=CBitmapWnd
VirtualFilter=WC

