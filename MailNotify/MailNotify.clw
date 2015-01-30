; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CDerouleMailsWnd
LastTemplate=generic CWnd
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "mailnotify.h"
LastPage=0

ClassCount=11
Class1=CDlgAccounts
Class2=CDlgAddAccount
Class3=CGraphicWnd
Class4=CLinkWindow
Class5=CSetupPropertyPage
Class6=CSetupPropertySheet
Class7=CWarningWnd

ResourceCount=9
Resource1=IDD_ACCOUNTS
Resource2=IDD_PROPPAGE_LARGE (English (U.S.))
Resource3=IDD_MESSAGES
Resource4=IDD_ADD_ACCOUNT
Resource5=IDD_RESTRICTION
Class8=CSetupDlg
Resource6=IDD_SETUP
Class9=CDlgRestriction
Resource7=IDD_MAILNOTIFY_DIALOG (English (U.S.))
Class10=CDlgNewMessages
Class11=CDerouleMailsWnd
Resource8=IDR_MENU
Resource9=IDD_MAIL

[CLS:CDlgAccounts]
Type=0
BaseClass=CDialog
HeaderFile=DlgAccounts.h
ImplementationFile=DlgAccounts.cpp
LastObject=CDlgAccounts
Filter=D
VirtualFilter=dWC

[CLS:CDlgAddAccount]
Type=0
BaseClass=CDialog
HeaderFile=DlgAddAccount.h
ImplementationFile=DlgAddAccount.cpp
Filter=D
VirtualFilter=dWC
LastObject=CDlgAddAccount

[CLS:CGraphicWnd]
Type=0
BaseClass=CWnd
HeaderFile=GraphicWnd.h
ImplementationFile=GraphicWnd.cpp

[CLS:CLinkWindow]
Type=0
BaseClass=CGraphicWnd
HeaderFile=LinkWindow.h
ImplementationFile=LinkWindow.cpp

[CLS:CSetupPropertyPage]
Type=0
BaseClass=CPropertyPage
HeaderFile=SetupPropertyPage.h
ImplementationFile=SetupPropertyPage.cpp

[CLS:CSetupPropertySheet]
Type=0
BaseClass=CPropertySheet
HeaderFile=SetupPropertySheet.h
ImplementationFile=SetupPropertySheet.cpp

[CLS:CWarningWnd]
Type=0
BaseClass=CWnd
HeaderFile=WarningWnd.h
ImplementationFile=WarningWnd.cpp
Filter=W
VirtualFilter=WC
LastObject=CWarningWnd

[DLG:IDD_ACCOUNTS]
Type=1
Class=CDlgAccounts
ControlCount=4
Control1=IDC_LIST_ACCOUNTS,SysListView32,1350664205
Control2=IDC_ADD,button,1342242816
Control3=IDC_EDIT,button,1342242816
Control4=IDC_BUTTON3,button,1342242816

[DLG:IDD_ADD_ACCOUNT]
Type=1
Class=CDlgAddAccount
ControlCount=17
Control1=IDC_NAME,edit,1350631552
Control2=IDC_SERVER,edit,1350631552
Control3=IDC_PORT,edit,1350631552
Control4=IDC_USERNAME,edit,1350631552
Control5=IDC_PASSWORD,edit,1350631584
Control6=IDOK,button,1342242817
Control7=IDCANCEL,button,1342242816
Control8=IDC_STATIC,static,1342308352
Control9=IDC_STATIC,static,1342308352
Control10=IDC_STATIC,static,1342308352
Control11=IDC_STATIC,static,1342308352
Control12=IDC_STATIC,static,1342308352
Control13=IDC_STATIC,button,1342177287
Control14=IDC_RULES,SysListView32,1350664461
Control15=IDC_ADD_RESTRICTION,button,1342242816
Control16=IDC_BUTTON2,button,1342242816
Control17=IDC_BUTTON3,button,1342242816

[DLG:IDD_MAILNOTIFY_DIALOG (English (U.S.))]
Type=1
Class=?
ControlCount=0

[DLG:IDD_PROPPAGE_LARGE (English (U.S.))]
Type=1
Class=?
ControlCount=5
Control1=IDC_STATIC,static,1342308352
Control2=IDC_MAILS,SysListView32,1350631425
Control3=IDC_ADD,button,1342242816
Control4=IDC_REMOVE,button,1342242816
Control5=IDC_EDIT,button,1342242816

[DLG:IDD_SETUP]
Type=1
Class=CSetupDlg
ControlCount=17
Control1=IDC_DELAY,edit,1350631552
Control2=IDC_SPIN1,msctls_updown32,1342177462
Control3=IDC_ANIMATE,button,1342242819
Control4=IDC_SCROLLLOCK,button,1342242819
Control5=IDC_PLAYSOUND,button,1342242819
Control6=IDC_SOUND,edit,1350631552
Control7=IDC_BROWSESOUND,button,1342242816
Control8=IDC_DISPLAYHEADERS,button,1476460547
Control9=IDC_LAUNCHCLIENT,button,1476460547
Control10=IDC_CLIENT,edit,1350631552
Control11=IDC_BROWSEMAILCLIENT,button,1342242816
Control12=IDC_STATIC,static,1342308352
Control13=IDC_STATIC,static,1342308352
Control14=IDC_STATIC,button,1342177287
Control15=IDC_STATIC,button,1342177287
Control16=IDOK,button,1342242817
Control17=IDCANCEL,button,1342242816

[MNU:IDR_MENU]
Type=1
Class=?
Command1=ID_CHECKMAILNOW
Command2=ID_SHOWMESSAGES
Command3=IDM_SETUP
Command4=IDM_ACCOUNTS
Command5=ID_ABOUT
Command6=IDM_QUIT
CommandCount=6

[CLS:CSetupDlg]
Type=0
HeaderFile=SetupDlg.h
ImplementationFile=SetupDlg.cpp
BaseClass=CDialog
Filter=D
LastObject=CSetupDlg
VirtualFilter=dWC

[DLG:IDD_RESTRICTION]
Type=1
Class=CDlgRestriction
ControlCount=5
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_STATIC,static,1342308352
Control4=IDC_RULE,combobox,1344340226
Control5=IDC_TEXTE,edit,1350631552

[CLS:CDlgRestriction]
Type=0
HeaderFile=DlgRestriction.h
ImplementationFile=DlgRestriction.cpp
BaseClass=CDialog
Filter=D
LastObject=CDlgRestriction
VirtualFilter=dWC

[DLG:IDD_MESSAGES]
Type=1
Class=CDlgNewMessages
ControlCount=2
Control1=IDC_MESSAGES,SysListView32,1350664477
Control2=IDC_MAILCLIENT,button,1342242817

[CLS:CDlgNewMessages]
Type=0
HeaderFile=DlgNewMessages.h
ImplementationFile=DlgNewMessages.cpp
BaseClass=CDialog
Filter=W
LastObject=IDC_MAILCLIENT
VirtualFilter=dWC

[CLS:CDerouleMailsWnd]
Type=0
HeaderFile=DerouleMailsWnd.h
ImplementationFile=DerouleMailsWnd.cpp
BaseClass=CWnd
Filter=W
VirtualFilter=WC
LastObject=CDerouleMailsWnd

[DLG:IDD_MAIL]
Type=1
ControlCount=6
Control1=IDC_STATIC,static,1342308352
Control2=IDC_STATIC,static,1342308352
Control3=IDC_FROM,edit,1350633600
Control4=IDC_SUBJECT,edit,1350633600
Control5=IDC_STATIC,static,1342308352
Control6=IDC_EDIT3,edit,1350633600

