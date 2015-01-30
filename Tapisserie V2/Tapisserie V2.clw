; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CPage2
LastTemplate=CListCtrl
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "tapisserie v2.h"
LastPage=0

ClassCount=6
Class1=CPage1
Class2=CPage2
Class3=CTapisserieV2App
Class4=CTapisserieV2Dlg
Class5=CTapisserieSheet

ResourceCount=3
Resource1=IDD_PAGE1 (English (U.S.))
Resource2=IDD_PAGE2 (English (U.S.))
Class6=CMyImageList
Resource3=IDR_MENU (English (U.S.))

[CLS:CPage1]
Type=0
BaseClass=CPropertyPage
HeaderFile=Page1.h
ImplementationFile=Page1.cpp
LastObject=CPage1

[CLS:CPage2]
Type=0
BaseClass=CPropertyPage
HeaderFile=Page2.h
ImplementationFile=Page2.cpp
Filter=D
VirtualFilter=idWC
LastObject=CPage2

[CLS:CTapisserieV2App]
Type=0
BaseClass=CWinApp
HeaderFile=Tapisserie V2.h
ImplementationFile=Tapisserie V2.cpp

[CLS:CTapisserieV2Dlg]
Type=0
BaseClass=CDialog
HeaderFile=Tapisserie V2Dlg.h
ImplementationFile=Tapisserie V2Dlg.cpp

[CLS:CTapisserieSheet]
Type=0
BaseClass=CPropertySheet
HeaderFile=TapisserieSheet.h
ImplementationFile=TapisserieSheet.cpp

[DLG:IDD_PAGE1]
Type=1
Class=CPage1

[DLG:IDD_PAGE2]
Type=1
Class=CPage2

[DLG:IDD_TAPISSERIEV2_DIALOG]
Type=1
Class=CTapisserieV2Dlg

[DLG:IDD_PAGE1 (English (U.S.))]
Type=1
Class=?
ControlCount=1
Control1=IDC_STATIC,static,1342179342

[DLG:IDD_PAGE2 (English (U.S.))]
Type=1
Class=CPage2
ControlCount=16
Control1=IDC_LISTE,SysListView32,1350795533
Control2=IDC_AJOUTER,button,1342373888
Control3=IDC_SUPPRIMER,button,1342242816
Control4=IDC_TESTER,button,1342242816
Control5=IDC_MINUTES,edit,1350762624
Control6=IDC_SPIN1,msctls_updown32,1342177462
Control7=IDC_Mosaique,button,1342373897
Control8=IDC_CENTRE,button,1342177289
Control9=IDC_STATIC,static,1342308352
Control10=IDC_STATIC,button,1342177287
Control11=IDC_STATIC,button,1342177287
Control12=IDC_ECONOMISEUR,button,1342242819
Control13=IDC_STATIC,button,1342177287
Control14=IDC_CHANGE_COULEUR,button,1342242816
Control15=IDC_CHANGE,button,1342242819
Control16=IDC_COULEUR,static,1342177286

[MNU:IDR_MENU (English (U.S.))]
Type=1
Class=?
Command1=ID_F_CONFIGURATION
Command2=ID_F_CHANGERMAINTENANT
Command3=ID_F_FERMER
CommandCount=3

[CLS:CMyImageList]
Type=0
HeaderFile=MyImageList.h
ImplementationFile=MyImageList.cpp
BaseClass=CListCtrl
Filter=W
VirtualFilter=FWC
LastObject=CMyImageList

