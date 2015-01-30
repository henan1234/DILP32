; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CListeAttributs
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "collectionfichiers.h"
LastPage=0

ClassCount=11
Class1=CCollectionFichiersApp
Class2=CAboutDlg
Class3=CCollectionFichiersDoc
Class4=CCollectionFichiersView
Class5=CListeAttributs
Class6=CMainFrame
Class7=CScanningDlg

ResourceCount=7
Resource1=IDD_TIP (English (U.S.))
Resource2=IDD_COLLECTIONFICHIERS_FORM
Resource3=IDD_ABOUTBOX
Resource4=IDD_SCANNING
Resource5=IDD_LISTE_ATTRIBUTS
Class8=CFiltreToolbar
Class9=CRegroupeToolbar
Class10=CSplashWnd
Resource6=IDR_REGROUPE
Class11=CTipDlg
Resource7=IDR_MAINFRAME

[CLS:CCollectionFichiersApp]
Type=0
BaseClass=CWinApp
HeaderFile=CollectionFichiers.h
ImplementationFile=CollectionFichiers.cpp

[CLS:CAboutDlg]
Type=0
BaseClass=CDialog
HeaderFile=CollectionFichiers.cpp
ImplementationFile=CollectionFichiers.cpp
LastObject=CAboutDlg

[CLS:CCollectionFichiersDoc]
Type=0
BaseClass=CDocument
HeaderFile=CollectionFichiersDoc.h
ImplementationFile=CollectionFichiersDoc.cpp
Filter=N
VirtualFilter=DC
LastObject=CCollectionFichiersDoc

[CLS:CCollectionFichiersView]
Type=0
BaseClass=CFormView
HeaderFile=CollectionFichiersView.h
ImplementationFile=CollectionFichiersView.cpp
LastObject=CCollectionFichiersView
Filter=D
VirtualFilter=VWC

[CLS:CListeAttributs]
Type=0
BaseClass=CDialog
HeaderFile=ListeAttributs.h
ImplementationFile=ListeAttributs.cpp
Filter=D
VirtualFilter=dWC
LastObject=IDC_LISTE_ATTRIBUTS

[CLS:CMainFrame]
Type=0
BaseClass=CFrameWnd
HeaderFile=MainFrm.h
ImplementationFile=MainFrm.cpp
LastObject=IDC_FILTRER
Filter=T
VirtualFilter=fWC

[CLS:CScanningDlg]
Type=0
BaseClass=CDialog
HeaderFile=ScanningDlg.h
ImplementationFile=ScanningDlg.cpp
LastObject=CScanningDlg

[DLG:IDD_ABOUTBOX]
Type=1
Class=CAboutDlg
ControlCount=4
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308480
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889

[DLG:IDD_LISTE_ATTRIBUTS]
Type=1
Class=CListeAttributs
ControlCount=10
Control1=IDC_EDIT1,edit,1350762624
Control2=IDC_EDIT2,edit,1350631552
Control3=IDC_BUTTON2,button,1342373888
Control4=IDC_BUTTON3,button,1342242816
Control5=IDC_BUTTON4,button,1342242816
Control6=IDC_LISTE_ATTRIBUTS,SysListView32,1350795277
Control7=IDOK,button,1342373889
Control8=IDCANCEL,button,1342242816
Control9=IDC_STATIC,static,1342308352
Control10=IDC_STATIC,static,1342308352

[DLG:IDD_SCANNING]
Type=1
Class=CScanningDlg
ControlCount=6
Control1=IDCANCEL,button,1342242816
Control2=IDC_PROGRESS,msctls_progress32,1350565888
Control3=IDC_FICHIER,static,1342312460
Control4=IDC_STATIC,static,1342308352
Control5=IDC_CHECKSUM,msctls_progress32,1350565889
Control6=IDC_ANIMATE1,SysAnimate32,1342177284

[DLG:IDR_MAINFRAME]
Type=1
Class=CFiltreToolbar
ControlCount=5
Control1=IDC_LISTE_ATTRIBUTS,combobox,1344340226
Control2=IDC_TEXTE,edit,1350631552
Control3=IDC_FILTRER,button,1342242816
Control4=IDC_STATIC,static,1342308352
Control5=IDC_STATIC,static,1342308352

[MNU:IDR_MAINFRAME]
Type=1
Class=?
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_SAVE
Command4=ID_FILE_SAVE_AS
Command5=ID_FILE_PRINT
Command6=ID_FILE_PRINT_PREVIEW
Command7=ID_FILE_PRINT_SETUP
Command8=ID_APP_EXIT
Command9=ID_FICHIERS_AJOUTER
Command10=ID_FICHIERS_SUPPRIMER
Command11=ID_EDIT_UNDO
Command12=ID_EDIT_CUT
Command13=ID_EDIT_COPY
Command14=ID_EDIT_PASTE
Command15=IDC_FILTRER
Command16=ID_VIEW_TOOLBAR
Command17=ID_VIEW_STATUS_BAR
Command18=ID_APP_ABOUT
CommandCount=18

[ACL:IDR_MAINFRAME]
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

[DLG:IDD_COLLECTIONFICHIERS_FORM]
Type=1
Class=?
ControlCount=2
Control1=IDC_LISTE,SysTreeView32,1350655527
Control2=IDC_HEADER,static,1073741832

[DLG:IDR_REGROUPE]
Type=1
Class=CRegroupeToolbar
ControlCount=2
Control1=IDC_STATIC,static,1342308352
Control2=IDC_LISTE_ATTRIBUTS,combobox,1344340227

[TB:IDR_MAINFRAME]
Type=1
Class=?
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_SAVE
Command4=ID_FICHIERS_AJOUTER
Command5=ID_FICHIERS_SUPPRIMER
Command6=ID_BUTTON32777
Command7=ID_BUTTON32776
Command8=ID_BUTTON32772
CommandCount=8

[CLS:CFiltreToolbar]
Type=0
HeaderFile=FiltreToolbar.h
ImplementationFile=FiltreToolbar.cpp
BaseClass=CDialogBar
Filter=D
LastObject=CFiltreToolbar
VirtualFilter=dWC

[CLS:CRegroupeToolbar]
Type=0
HeaderFile=RegroupeToolbar.h
ImplementationFile=RegroupeToolbar.cpp
BaseClass=CDialogBar
Filter=D
LastObject=IDC_FILTRER
VirtualFilter=dWC

[CLS:CSplashWnd]
Type=0
HeaderFile=Splash.h
ImplementationFile=Splash.cpp
BaseClass=CWnd

[DLG:IDD_TIP (English (U.S.))]
Type=1
Class=?
ControlCount=6
Control1=65535,static,1342177287
Control2=IDC_TIPSTRING,static,1342308352
Control3=IDC_STARTUP,button,1342373891
Control4=IDC_NEXTTIP,button,1342373888
Control5=IDOK,button,1342373889
Control6=IDC_BULB,static,1342177294

[CLS:CTipDlg]
Type=0
HeaderFile=TipDlg.h
ImplementationFile=TipDlg.cpp
BaseClass=CDialog
LastObject=CTipDlg

