; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CMyTreeCtrl
LastTemplate=CTreeCtrl
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "Decoupe.h"

ClassCount=5
Class1=CDecoupeApp
Class2=CDecoupeDlg
Class3=CAboutDlg

ResourceCount=4
Resource1=IDD_ABOUTBOX
Resource2=IDR_MAINFRAME
Resource3=IDD_DECOUPE_DIALOG
Class4=CDlgDecoupeEnCours
Class5=CMyTreeCtrl
Resource4=IDD_DECOUPE_EN_COURS

[CLS:CDecoupeApp]
Type=0
HeaderFile=Decoupe.h
ImplementationFile=Decoupe.cpp
Filter=N

[CLS:CDecoupeDlg]
Type=0
HeaderFile=DecoupeDlg.h
ImplementationFile=DecoupeDlg.cpp
Filter=D
BaseClass=CDialog
VirtualFilter=dWC
LastObject=CDecoupeDlg

[CLS:CAboutDlg]
Type=0
HeaderFile=DecoupeDlg.h
ImplementationFile=DecoupeDlg.cpp
Filter=D

[DLG:IDD_ABOUTBOX]
Type=1
Class=CAboutDlg
ControlCount=4
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308480
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889

[DLG:IDD_DECOUPE_DIALOG]
Type=1
Class=CDecoupeDlg
ControlCount=16
Control1=IDOK,button,1342242817
Control2=IDC_STATIC,static,1342308352
Control3=IDC_FICHIER_A_DECOUPER,edit,1350631552
Control4=IDC_PARCOURS_FICHIERS,button,1342246656
Control5=IDC_STATIC,static,1342308352
Control6=IDC_REPERTOIRE_CIBLE,edit,1350631552
Control7=IDC_PARCOURS_REPERTOIRE,button,1342246656
Control8=IDC_STATIC,static,1342308352
Control9=IDC_FORMAT_NOM_CIBLE,combobox,1344339971
Control10=IDC_STATIC,static,1342308352
Control11=IDC_TAILLE_MORCEAU,edit,1350631552
Control12=IDC_TAILLES,combobox,1344339971
Control13=IDC_STATIC,static,1342308352
Control14=IDC_TAILLE_FICHIER,static,1342308352
Control15=IDC_STATIC,static,1342308352
Control16=IDC_NB_PARTIES,static,1342308352

[DLG:IDD_DECOUPE_EN_COURS]
Type=1
Class=CDlgDecoupeEnCours
ControlCount=7
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308352
Control3=IDC_NOM_FICHIER,static,1342308352
Control4=IDC_TAILLE_MORCEAU,static,1342308352
Control5=IDC_NO_MORCEAU,static,1342308352
Control6=IDC_NOM_FICHIER_MORCEAU,static,1342308352
Control7=IDC_PROGRESS,msctls_progress32,1342177281

[CLS:CDlgDecoupeEnCours]
Type=0
HeaderFile=DlgDecoupeEnCours.h
ImplementationFile=DlgDecoupeEnCours.cpp
BaseClass=CDialog
Filter=D
LastObject=CDlgDecoupeEnCours
VirtualFilter=dWC

[CLS:CMyTreeCtrl]
Type=0
HeaderFile=MyTreeCtrl.h
ImplementationFile=MyTreeCtrl.cpp
BaseClass=CTreeCtrl
Filter=W

