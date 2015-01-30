; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CDupplicateFilesDlg
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "dupplicatefiles.h"
LastPage=0

ClassCount=5
Class1=CDupplicateFilesApp
Class2=CAboutDlg
Class3=CDupplicateFilesDlg
Class4=CScanningDlg

ResourceCount=8
Resource1=IDD_DUPPLICATEFILES_DIALOG
Resource2=IDD_DIALOG1
Resource3=IDD_ABOUTBOX
Class5=CMultipleDelete
Resource4=IDD_MULTIPLE
Resource5=IDD_ABOUTBOX (English (U.S.))
Resource6=IDD_DIALOG1 (English (U.S.))
Resource7=IDD_DUPPLICATEFILES_DIALOG (English (U.S.))
Resource8=IDD_MULTIPLE (English (U.S.))

[CLS:CDupplicateFilesApp]
Type=0
BaseClass=CWinApp
HeaderFile=DupplicateFiles.h
ImplementationFile=DupplicateFiles.cpp

[CLS:CAboutDlg]
Type=0
BaseClass=CDialog
HeaderFile=DupplicateFilesDlg.cpp
ImplementationFile=DupplicateFilesDlg.cpp

[CLS:CDupplicateFilesDlg]
Type=0
BaseClass=CDialog
HeaderFile=DupplicateFilesDlg.h
ImplementationFile=DupplicateFilesDlg.cpp
LastObject=IDC_PREV
Filter=D
VirtualFilter=dWC

[CLS:CScanningDlg]
Type=0
BaseClass=CDialog
HeaderFile=ScanningDlg.h
ImplementationFile=ScanningDlg.cpp
LastObject=CScanningDlg
Filter=D
VirtualFilter=dWC

[DLG:IDD_ABOUTBOX]
Type=1
Class=CAboutDlg
ControlCount=4
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308480
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889

[DLG:IDD_DUPPLICATEFILES_DIALOG]
Type=1
Class=CDupplicateFilesDlg
ControlCount=9
Control1=IDC_TREE1,SysTreeView32,1350631463
Control2=IDC_PREV,button,1342242816
Control3=IDC_NEXT,button,1342242816
Control4=IDC_OPEN,button,1342242816
Control5=IDC_SHOW_DUPP,button,1342242816
Control6=IDC_DELETEFILE,button,1342242816
Control7=IDC_DELETE,button,1342242816
Control8=IDC_DELETE_ALL,button,1342242816
Control9=IDC_DELETE_MULTIPLE,button,1342242816

[DLG:IDD_DIALOG1]
Type=1
Class=CScanningDlg
ControlCount=8
Control1=IDCANCEL,button,1342242816
Control2=IDC_STATIC,static,1342308364
Control3=IDC_STATIC,static,1342308352
Control4=IDC_FILE,static,1342308491
Control5=IDC_FOUND,static,1342308352
Control6=IDC_STATIC,static,1342177283
Control7=IDC_PROCESSED,static,1342308352
Control8=IDC_STATIC,static,1342181394

[DLG:IDD_MULTIPLE]
Type=1
Class=CMultipleDelete
ControlCount=11
Control1=IDC_RADIO1,button,1342308361
Control2=IDC_RADIO2,button,1342177289
Control3=IDC_RADIO3,button,1342177289
Control4=IDC_DIR,edit,1350631552
Control5=IDC_BROWSEDIR,button,1342242816
Control6=IDC_MASK,edit,1350631552
Control7=IDOK,button,1342242817
Control8=IDCANCEL,button,1342242816
Control9=IDC_STATIC,static,1342308352
Control10=IDC_STATIC,button,1342177287
Control11=IDC_TIP,edit,1350633540

[CLS:CMultipleDelete]
Type=0
HeaderFile=MultipleDelete.h
ImplementationFile=MultipleDelete.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC
LastObject=IDC_TIP

[DLG:IDD_ABOUTBOX (English (U.S.))]
Type=1
Class=?
ControlCount=4
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308480
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889

[DLG:IDD_DUPPLICATEFILES_DIALOG (English (U.S.))]
Type=1
Class=CDupplicateFilesDlg
ControlCount=10
Control1=IDC_TREE1,SysTreeView32,1350631463
Control2=IDC_PREV,button,1342242816
Control3=IDC_NEXT,button,1342242816
Control4=IDC_PROPS,button,1342242816
Control5=IDC_OPEN,button,1342242816
Control6=IDC_SHOW_DUPP,button,1342242816
Control7=IDC_DELETEFILE,button,1342242816
Control8=IDC_DELETE,button,1342242816
Control9=IDC_DELETE_ALL,button,1342242816
Control10=IDC_DELETE_MULTIPLE,button,1073807360

[DLG:IDD_DIALOG1 (English (U.S.))]
Type=1
Class=?
ControlCount=8
Control1=IDCANCEL,button,1342242816
Control2=IDC_STATIC,static,1342308364
Control3=IDC_STATIC,static,1342308352
Control4=IDC_FILE,static,1342308491
Control5=IDC_FOUND,static,1342308352
Control6=IDC_STATIC,static,1342177283
Control7=IDC_PROCESSED,static,1342308352
Control8=IDC_STATIC,static,1342181394

[DLG:IDD_MULTIPLE (English (U.S.))]
Type=1
Class=?
ControlCount=11
Control1=IDC_RADIO1,button,1342308361
Control2=IDC_RADIO2,button,1342177289
Control3=IDC_RADIO3,button,1342177289
Control4=IDC_DIR,edit,1350631552
Control5=IDC_BROWSEDIR,button,1342242816
Control6=IDC_MASK,edit,1350631552
Control7=IDOK,button,1342242817
Control8=IDCANCEL,button,1342242816
Control9=IDC_STATIC,static,1342308352
Control10=IDC_STATIC,button,1342177287
Control11=IDC_TIP,edit,1350633540

