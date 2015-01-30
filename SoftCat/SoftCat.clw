; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CRsCgDlg
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "SoftCat.h"
LastPage=0

ClassCount=8
Class1=CSoftCatApp
Class2=CSoftCatDoc
Class3=CSoftCatView
Class4=CMainFrame
Class6=CLeftView

ResourceCount=4
Resource1=IDD_SOFTCAT_FORM
Resource2=IDD_ABOUTBOX
Resource3=IDR_MAINFRAME
Class5=CSoftCatSet
Class7=CAboutDlg
Resource4=CG_IDD_RECORDSET (English (U.S.))
Class8=CRsCgDlg

[CLS:CSoftCatApp]
Type=0
HeaderFile=SoftCat.h
ImplementationFile=SoftCat.cpp
Filter=N

[CLS:CSoftCatDoc]
Type=0
HeaderFile=SoftCatDoc.h
ImplementationFile=SoftCatDoc.cpp
Filter=N

[CLS:CSoftCatView]
Type=0
HeaderFile=SoftCatView.h
ImplementationFile=SoftCatView.cpp
Filter=D
BaseClass=CRecordView
VirtualFilter=RVWC
LastObject=CSoftCatView


[CLS:CSoftCatSet]
Type=0
HeaderFile=SoftCatSet.h
ImplementationFile=SoftCatSet.cpp
Filter=N

[DB:CSoftCatSet]
DB=1
DBType=ODBC
ColumnCount=18
Column1=[Fichiers].[Numero], 4, 4
Column2=[Fichiers].[Nom], 12, 400
Column3=[Fichiers].[Description], 12, 100
Column4=[NumeroDeMedia], 4, 4
Column5=[FichierIcone], 12, 510
Column6=[IndexIcone], 5, 2
Column7=[Fichiers Requête].[Numero], 4, 4
Column8=[Fichiers Requête].[Nom], 12, 400
Column9=[Fichiers Requête].[Description], 12, 100
Column10=[MotCles], -2, 0
Column11=[N°], 4, 4
Column12=[Medias].[Nom], 12, 400
Column13=[Date], 11, 16
Column14=[Support], 12, 200
Column15=[Commentaire], 12, 510
Column16=[Icone], 5, 2
Column17=[MotCle], 12, 200
Column18=[NoFichier], 4, 4


[CLS:CMainFrame]
Type=0
HeaderFile=MainFrm.h
ImplementationFile=MainFrm.cpp
Filter=T



[CLS:CLeftView]
Type=0
HeaderFile=LeftView.h
ImplementationFile=LeftView.cpp
Filter=T

[CLS:CAboutDlg]
Type=0
HeaderFile=SoftCat.cpp
ImplementationFile=SoftCat.cpp
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
Command1=ID_FILE_PRINT
Command2=ID_FILE_PRINT_PREVIEW
Command3=ID_FILE_PRINT_SETUP
Command4=ID_APP_EXIT
Command5=ID_EDIT_UNDO
Command6=ID_EDIT_CUT
Command7=ID_EDIT_COPY
Command8=ID_EDIT_PASTE
Command9=ID_RECORD_FIRST
Command10=ID_RECORD_PREV
Command11=ID_RECORD_NEXT
Command12=ID_RECORD_LAST
Command13=ID_VIEW_TOOLBAR
Command14=ID_VIEW_STATUS_BAR
Command15=ID_APP_ABOUT
CommandCount=15

[ACL:IDR_MAINFRAME]
Type=1
Class=CMainFrame
Command1=ID_FILE_PRINT
Command2=ID_EDIT_UNDO
Command3=ID_EDIT_CUT
Command4=ID_EDIT_COPY
Command5=ID_EDIT_PASTE
Command6=ID_EDIT_UNDO
Command7=ID_EDIT_CUT
Command8=ID_EDIT_COPY
Command9=ID_EDIT_PASTE
Command10=ID_NEXT_PANE
Command11=ID_PREV_PANE
CommandCount=11

[DLG:IDD_SOFTCAT_FORM]
Type=1
Class=CSoftCatView
ControlCount=2
Control1=IDC_STATIC,static,1342308352
Control2=IDC_NOM,edit,1350631552

[TB:IDR_MAINFRAME]
Type=1
Class=?
Command1=ID_EDIT_CUT
Command2=ID_EDIT_COPY
Command3=ID_EDIT_PASTE
Command4=ID_FILE_PRINT
Command5=ID_RECORD_FIRST
Command6=ID_RECORD_PREV
Command7=ID_RECORD_NEXT
Command8=ID_RECORD_LAST
Command9=ID_APP_ABOUT
CommandCount=9

[DLG:CG_IDD_RECORDSET (English (U.S.))]
Type=1
Class=CRsCgDlg
ControlCount=18
Control1=1,button,1342242817
Control2=2,button,1342242816
Control3=1001,static,1342308352
Control4=2001,edit,1350631552
Control5=1002,static,1342308352
Control6=2002,edit,1350631552
Control7=1003,static,1342308352
Control8=2003,edit,1350631552
Control9=1004,static,1342308352
Control10=2004,edit,1350631552
Control11=1005,static,1342308352
Control12=2005,edit,1350631552
Control13=1006,static,1342308352
Control14=2006,edit,1350631552
Control15=204,button,1342242816
Control16=201,button,1342242816
Control17=202,button,1342242816
Control18=203,button,1342242816

[CLS:CRsCgDlg]
Type=0
HeaderFile=RsCgDlg.h
ImplementationFile=RsCgDlg.cpp
BaseClass=CDialog

