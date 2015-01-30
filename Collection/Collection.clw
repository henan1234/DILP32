; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CDlgAjouteMedia
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "Collection.h"
LastPage=0

ClassCount=9
Class1=CCollectionApp
Class2=CCollectionDoc
Class3=CCollectionView
Class4=CMainFrame
Class7=CAboutDlg

ResourceCount=5
Resource1=IDD_ABOUTBOX
Resource2=IDR_MAINFRAME
Resource3=IDD_PROPRIETES_GENERIQUE
Class5=CChildFrame
Class6=CLeftView
Resource4=IDR_COLLECTYPE
Class8=CDlgProprietesGenerique
Class9=CDlgAjouteMedia
Resource5=IDD_AJOUTE_MEDIA

[CLS:CCollectionApp]
Type=0
HeaderFile=Collection.h
ImplementationFile=Collection.cpp
Filter=N

[CLS:CCollectionDoc]
Type=0
HeaderFile=CollectionDoc.h
ImplementationFile=CollectionDoc.cpp
Filter=N
BaseClass=CDocument
VirtualFilter=DC

[CLS:CCollectionView]
Type=0
HeaderFile=CollectionView.h
ImplementationFile=CollectionView.cpp
Filter=C


[CLS:CMainFrame]
Type=0
HeaderFile=MainFrm.h
ImplementationFile=MainFrm.cpp
Filter=T
LastObject=ID_MDIA_AJOUTERUNMDIA


[CLS:CChildFrame]
Type=0
HeaderFile=ChildFrm.h
ImplementationFile=ChildFrm.cpp
Filter=M

[CLS:CLeftView]
Type=0
HeaderFile=LeftView.h
ImplementationFile=LeftView.cpp
Filter=T

[CLS:CAboutDlg]
Type=0
HeaderFile=Collection.cpp
ImplementationFile=Collection.cpp
Filter=D
LastObject=CAboutDlg

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
Command3=ID_FILE_PRINT_SETUP
Command4=ID_FILE_MRU_FILE1
Command5=ID_APP_EXIT
Command6=ID_VIEW_TOOLBAR
Command7=ID_VIEW_STATUS_BAR
Command8=ID_WINDOW_SPLIT
Command9=ID_VIEW_LARGEICON
Command10=ID_VIEW_SMALLICON
Command11=ID_VIEW_LIST
Command12=ID_VIEW_DETAILS
Command13=ID_VIEW_BYNAME
Command14=ID_VIEW_AUTOARRANGE
Command15=ID_VIEW_LINEUP
Command16=ID_APP_ABOUT
CommandCount=16

[TB:IDR_MAINFRAME]
Type=1
Class=CMainFrame
Command1=ID_MDIA_AJOUTERUNMDIA
Command2=ID_FILE_NEW
Command3=ID_FILE_OPEN
Command4=ID_FILE_SAVE
Command5=ID_EDIT_CUT
Command6=ID_EDIT_COPY
Command7=ID_EDIT_PASTE
Command8=ID_FILE_PRINT
Command9=ID_VIEW_LARGEICON
Command10=ID_VIEW_SMALLICON
Command11=ID_VIEW_LIST
Command12=ID_VIEW_DETAILS
Command13=ID_APP_ABOUT
Command14=ID_BUTTON32771
CommandCount=14

[MNU:IDR_COLLECTYPE]
Type=1
Class=CCollectionView
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
Command11=ID_MDIA_AJOUTERUNMDIA
Command12=ID_MDIA_SUPPRIMERLEMDIA
Command13=ID_EDIT_UNDO
Command14=ID_EDIT_CUT
Command15=ID_EDIT_COPY
Command16=ID_EDIT_PASTE
Command17=ID_VIEW_TOOLBAR
Command18=ID_VIEW_STATUS_BAR
Command19=ID_WINDOW_SPLIT
Command20=ID_VIEW_LARGEICON
Command21=ID_VIEW_SMALLICON
Command22=ID_VIEW_LIST
Command23=ID_VIEW_DETAILS
Command24=ID_VIEW_BYNAME
Command25=ID_VIEW_AUTOARRANGE
Command26=ID_VIEW_LINEUP
Command27=ID_WINDOW_NEW
Command28=ID_WINDOW_CASCADE
Command29=ID_WINDOW_TILE_HORZ
Command30=ID_WINDOW_ARRANGE
Command31=ID_APP_ABOUT
CommandCount=31

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

[DLG:IDD_PROPRIETES_GENERIQUE]
Type=1
Class=CDlgProprietesGenerique
ControlCount=9
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_LISTE_PROPRIETES,SysListView32,1350664461
Control4=IDC_STATIC,static,1342308352
Control5=IDC_NOM_PROPRIETE,edit,1350631552
Control6=IDC_STATIC,static,1342308352
Control7=IDC_VALEUR_PROPRIETE,edit,1350631552
Control8=IDC_CHANGER_PROPRIETE,button,1342242816
Control9=IDC_SUPPRIMER_PROPRIETE,button,1342242816

[DLG:IDR_MAINFRAME]
Type=1
Class=?
ControlCount=1
Control1=IDC_STATIC,static,1342308352

[CLS:CDlgProprietesGenerique]
Type=0
HeaderFile=DlgProprietesGenerique.h
ImplementationFile=DlgProprietesGenerique.cpp
BaseClass=CDialog
Filter=D
LastObject=CDlgProprietesGenerique

[DLG:IDD_AJOUTE_MEDIA]
Type=1
Class=CDlgAjouteMedia
ControlCount=17
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_LISTE_MEDIAS,SysListView32,1350631692
Control4=IDC_STATIC,static,1342308352
Control5=IDC_EDIT1,edit,1350631552
Control6=IDC_SOUS_REPERTOIRE,button,1342242816
Control7=IDC_STATIC,static,1342308352
Control8=IDC_EDIT2,edit,1350631552
Control9=IDC_LISTE_PROPRIETES,SysListView32,1350664461
Control10=IDC_STATIC,static,1342308352
Control11=IDC_NOM_PROPRIETE,edit,1350631552
Control12=IDC_STATIC,static,1342308352
Control13=IDC_VALEUR_PROPRIETE,edit,1350631552
Control14=IDC_CHANGER_PROPRIETE,button,1342242816
Control15=IDC_SUPPRIMER_PROPRIETE,button,1342242816
Control16=IDC_STATIC,button,1342177287
Control17=IDC_STATIC,button,1342177287

[CLS:CDlgAjouteMedia]
Type=0
HeaderFile=DlgAjouteMedia.h
ImplementationFile=DlgAjouteMedia.cpp
BaseClass=CDlgProprietesGenerique
Filter=D
LastObject=CDlgAjouteMedia
VirtualFilter=dWC

