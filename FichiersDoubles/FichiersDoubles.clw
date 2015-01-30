; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CFichiersDoublesDoc
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "FichiersDoubles.h"
LastPage=0

ClassCount=7
Class1=CFichiersDoublesApp
Class2=CFichiersDoublesDoc
Class3=CFichiersDoublesView
Class4=CMainFrame

ResourceCount=3
Resource1=IDR_MAINFRAME
Class5=CLeftView
Class6=CAboutDlg
Resource2=IDD_ABOUTBOX
Class7=CProgressDlg
Resource3=IDD_PROGRESS

[CLS:CFichiersDoublesApp]
Type=0
HeaderFile=FichiersDoubles.h
ImplementationFile=FichiersDoubles.cpp
Filter=N

[CLS:CFichiersDoublesDoc]
Type=0
HeaderFile=FichiersDoublesDoc.h
ImplementationFile=FichiersDoublesDoc.cpp
Filter=N
BaseClass=CDocument
VirtualFilter=DC
LastObject=ID_EDITION_SUPPRIMETOUSLESDUPPLIQUS

[CLS:CFichiersDoublesView]
Type=0
HeaderFile=FichiersDoublesView.h
ImplementationFile=FichiersDoublesView.cpp
Filter=C
BaseClass=CListView
VirtualFilter=VWC
LastObject=CFichiersDoublesView


[CLS:CMainFrame]
Type=0
HeaderFile=MainFrm.h
ImplementationFile=MainFrm.cpp
Filter=T
BaseClass=CFrameWnd
VirtualFilter=fWC
LastObject=ID_EDITION_SUPPRIMEDUPPLIQUS



[CLS:CLeftView]
Type=0
HeaderFile=LeftView.h
ImplementationFile=LeftView.cpp
Filter=T
BaseClass=CTreeView
VirtualFilter=VWC
LastObject=CLeftView

[CLS:CAboutDlg]
Type=0
HeaderFile=FichiersDoubles.cpp
ImplementationFile=FichiersDoubles.cpp
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
Command1=ID_FILE_OPEN
Command2=ID_FILE_MRU_FILE1
Command3=ID_APP_EXIT
Command4=IDM_PROPRIETES
Command5=ID_EDITION_OUVRE
Command6=IDM_SUPPRIME
Command7=ID_EDITION_SUPPRIMEDUPPLIQUS
Command8=ID_EDITION_SUPPRIMETOUSLESDUPPLIQUS
Command9=IDM_NON_DUPLIQUES
Command10=ID_VIEW_TOOLBAR
Command11=ID_VIEW_STATUS_BAR
Command12=ID_APP_ABOUT
CommandCount=12

[ACL:IDR_MAINFRAME]
Type=1
Class=CMainFrame
Command1=ID_FILE_OPEN
Command2=IDM_SUPPRIME
Command3=ID_EDITION_SUPPRIMEDUPPLIQUS
Command4=ID_EDITION_OUVRE
Command5=IDM_PROPRIETES
CommandCount=5

[TB:IDR_MAINFRAME]
Type=1
Class=CMainFrame
Command1=ID_FILE_OPEN
Command2=IDM_NON_DUPLIQUES
Command3=IDM_PROPRIETES
Command4=ID_EDITION_OUVRE
Command5=ID_BUTTON32780
Command6=ID_EDITION_SUPPRIMEDUPPLIQUS
Command7=ID_BUTTON32783
Command8=ID_APP_ABOUT
Command9=ID_BUTTON32784
CommandCount=9

[CLS:CProgressDlg]
Type=0
HeaderFile=ProgressDlg.h
ImplementationFile=ProgressDlg.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC
LastObject=IDC_FICHIER_SEC

[DLG:IDD_PROGRESS]
Type=1
Class=CProgressDlg
ControlCount=9
Control1=IDCANCEL,button,1342242816
Control2=IDC_REPERTOIRE,static,1342308352
Control3=IDC_STATIC,static,1342308352
Control4=IDC_FICHIER_1_SUR,static,1342308352
Control5=IDC_FICHIER_EN_COURS,static,1342308492
Control6=IDC_PROGRESS,msctls_progress32,1342177281
Control7=IDC_DUPLIQUES_TROUVES,static,1342308352
Control8=IDC_ANIMATE1,SysAnimate32,1342177284
Control9=IDC_FICHIER_SEC,static,1342308352

