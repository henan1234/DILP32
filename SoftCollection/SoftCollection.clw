; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CSoftCollectionDlg
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "SoftCollection.h"
ODLFile=SoftCollection.odl

ClassCount=7
Class1=CSoftCollectionApp
Class2=CSoftCollectionDlg
Class3=CAboutDlg
Class4=CSoftCollectionDlgAutoProxy

ResourceCount=7
Resource1=IDD_SOFTCOLLECTION_DIALOG
Resource2=IDR_MAINFRAME
Resource3=IDD_ABOUTBOX
Resource4=IDD_SCANNING
Class5=CMaToolbar
Resource5=IDR_MENU1
Class6=CScanningDlg
Resource6=IDD_RECHERCHE
Class7=CRecherche
Resource7=IDR_TOOLBAR1

[CLS:CSoftCollectionApp]
Type=0
HeaderFile=SoftCollection.h
ImplementationFile=SoftCollection.cpp
Filter=N

[CLS:CSoftCollectionDlg]
Type=0
HeaderFile=SoftCollectionDlg.h
ImplementationFile=SoftCollectionDlg.cpp
Filter=D
LastObject=ID_MEDIAS_SUPPRIMER
BaseClass=CDialog
VirtualFilter=dWC

[CLS:CAboutDlg]
Type=0
HeaderFile=SoftCollectionDlg.h
ImplementationFile=SoftCollectionDlg.cpp
Filter=D

[DLG:IDD_ABOUTBOX]
Type=1
Class=CAboutDlg
ControlCount=4
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308480
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889

[CLS:CSoftCollectionDlgAutoProxy]
Type=0
HeaderFile=DlgProxy.h
ImplementationFile=DlgProxy.cpp
BaseClass=CCmdTarget
Filter=N

[DLG:IDD_SOFTCOLLECTION_DIALOG]
Type=1
Class=CSoftCollectionDlg
ControlCount=10
Control1=IDC_STATIC,button,1342177287
Control2=IDC_LISTEMEDIAS,SysListView32,1350681356
Control3=IDC_STATIC,button,1342177287
Control4=IDC_CONTENUMEDIA,SysTreeView32,1350639143
Control5=IDC_ATTRIBUTS,SysListView32,1350795549
Control6=IDC_AJOUTE_ATTRIBUT,button,1342242816
Control7=IDC_MODIFIE_ATTRIBUT,button,1342242816
Control8=IDC_SUPPRIME_ATTRIBUT,button,1342242816
Control9=ID_MEDIAS_AJOUTER,button,1342242816
Control10=ID_MEDIAS_SUPPRIMER,button,1342242816

[MNU:IDR_MENU1]
Type=1
Class=?
Command1=ID_FILE_OPEN
Command2=ID_MEDIAS_QUITTER
Command3=ID_MEDIAS_AJOUTER
Command4=ID_MEDIAS_SUPPRIMER
Command5=ID_MEDIAS_RAFRAICHIR
Command6=ID_RECHERCHE_CHERCHER
Command7=ID_RECHERCHE_DUPPLIQUS
Command8=ID_OPTIONS_MOTCLS
Command9=ID_OPTIONS_PROPRITES
CommandCount=9

[TB:IDR_TOOLBAR1]
Type=1
Class=CMaToolbar
Command1=ID_MEDIAS_AJOUTER
CommandCount=1

[CLS:CMaToolbar]
Type=0
HeaderFile=MaToolbar.h
ImplementationFile=MaToolbar.cpp
BaseClass=CToolBarCtrl
Filter=W
LastObject=ID_MEDIAS_AJOUTER

[DLG:IDD_SCANNING]
Type=1
Class=CScanningDlg
ControlCount=6
Control1=IDCANCEL,button,1342242816
Control2=IDC_PROGRESS,msctls_progress32,1350565888
Control3=IDC_FICHIER,static,1342312460
Control4=IDC_STATIC,static,1342308352
Control5=IDC_CHECKSUM,msctls_progress32,1350565889
Control6=IDC_ANIMATE1,SysAnimate32,1342177287

[CLS:CScanningDlg]
Type=0
HeaderFile=ScanningDlg1.h
ImplementationFile=ScanningDlg1.cpp
BaseClass=CDialog
Filter=D
LastObject=CScanningDlg
VirtualFilter=dWC

[DLG:IDD_RECHERCHE]
Type=1
Class=CRecherche
ControlCount=7
Control1=IDC_TEXTE,edit,1350762624
Control2=IDC_TOUS_ATTRIBUTS,button,1342373897
Control3=IDC_UN_ATTRIBUT,button,1342177289
Control4=IDC_LISTE_ATTRIBUTS,combobox,1344471299
Control5=IDC_CHERCHER,button,1342373888
Control6=IDC_RESULTAT,SysListView32,1350762505
Control7=IDC_STATIC,static,1342308352

[CLS:CRecherche]
Type=0
HeaderFile=Recherche.h
ImplementationFile=Recherche.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC
LastObject=IDC_RESULTAT

