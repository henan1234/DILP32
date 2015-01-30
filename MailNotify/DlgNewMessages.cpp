// DlgNewMessages.cpp : implementation file
//
#define _WIN32_WINNT 0x500
#define WIN32 1

#include "stdafx.h"
#include "DlgNewMessages.h"
#include "Mail.h"
#include "CompteMail.h"
#include "common.h"
extern CArray<CCompteMail *,CCompteMail *>	Comptes ;

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

static const char COLUMN_ORDER[]	=	"ColumnOrder" ;
static const char STATE[]			=	"State" ;
static const char FROM[]			=	"From" ;
static const char SUBJECT[]			=	"Subject" ;
static const char CONTENT[]			=	"Content" ;
static const char ACCOUNT[]			=	"Account" ;
static const char HEADER[]			=	"Header" ;
static const char NEWMAILSWINDOW[]	=	"New mails window" ;
static const char LEFT[]			=	"Left" ;
static const char RIGHT[]			=	"Right" ;
static const char TOP[]				=	"Top" ;
static const char BOTTOM[]			=	"Bottom" ;
static const char TRANSPARENCY[]	=	"Transparency" ;
static const char BLEND[]			=	"Blend" ;


extern		HWND		hwndMain ;
extern		UINT	wPrivateMessage ;

/////////////////////////////////////////////////////////////////////////////
// CDlgNewMessages dialog


CDlgNewMessages::CDlgNewMessages(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgNewMessages::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgNewMessages)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	m_hBrush	=	CreateSolidBrush( RGB( 255, 255, 192 ) ) ;
}

CDlgNewMessages::~CDlgNewMessages()
	{
	DeleteObject( m_hBrush ) ;
	}

void CDlgNewMessages::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgNewMessages)
	DDX_Control(pDX, IDC_MESSAGES, m_Messages);
	//}}AFX_DATA_MAP

}


BEGIN_MESSAGE_MAP(CDlgNewMessages, CDialog)
	//{{AFX_MSG_MAP(CDlgNewMessages)
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_MESSAGES, OnItemchangedMessages)
	ON_WM_CTLCOLOR()
	ON_WM_ERASEBKGND()
	ON_WM_SIZE()
	ON_BN_CLICKED(IDC_MAILCLIENT, OnMailclient)
	ON_WM_MOVE()
	ON_NOTIFY(LVN_COLUMNCLICK, IDC_MESSAGES, OnColumnclickMessages)
	ON_WM_CLOSE()
	ON_WM_TIMER()
	ON_NOTIFY(HDN_ITEMCHANGED, IDC_MESSAGES, OnItemchangedMessages)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgNewMessages message handlers

void CDlgNewMessages::Refresh()
{
	RemplitMails() ;
}

BOOL CDlgNewMessages::OnInitDialog() 
{
	CDialog::OnInitDialog();
	Transparence() ;
	ListView_SetExtendedListViewStyle 
		   (m_Messages.m_hWnd, 
			LVS_EX_GRIDLINES  | LVS_EX_TRACKSELECT |
			LVS_EX_UNDERLINEHOT | LVS_EX_HEADERDRAGDROP | LVS_EX_CHECKBOXES |
			LVS_EX_FULLROWSELECT | LVS_EX_FLATSB | LVS_EX_INFOTIP );


	_ImageList.Create( 12, 12, ILC_COLOR32 | ILC_MASK , 3, 3 );
	_ImageList.Add( AfxGetApp()->LoadIcon( IDI_MAIL_FERME )) ;
	_ImageList.Add( AfxGetApp()->LoadIcon( IDI_MAIL_OUVERT )) ;
	_ImageList.Add( AfxGetApp()->LoadIcon( IDI_MAIL_REMOVE )) ;

	m_Messages.SetImageList( &_ImageList,LVSIL_STATE ) ;
	

	m_Messages.SetBkColor( RGB( 255, 255, 192 )) ;
	m_Messages.SetTextBkColor( RGB( 255, 255, 192 )) ;
	m_Messages.SetTextColor( RGB( 0, 0, 0 )) ;
	
	// Ajoute les colonnes
	m_Messages.InsertColumn( 0, STATE, LVCFMT_LEFT, GetConfigurationInt( HEADER, STATE, 80 ), 0 ) ;
	m_Messages.InsertColumn( 1, FROM, LVCFMT_LEFT, GetConfigurationInt( HEADER, FROM, 80 ), 0 ) ;
	m_Messages.InsertColumn( 2, SUBJECT, LVCFMT_LEFT, GetConfigurationInt( HEADER, SUBJECT, 100 ), 1 ) ;
	m_Messages.InsertColumn( 3, CONTENT, LVCFMT_LEFT, GetConfigurationInt( HEADER, CONTENT, 100 ), 2 ) ;
	m_Messages.InsertColumn( 4, ACCOUNT, LVCFMT_LEFT, GetConfigurationInt( HEADER, ACCOUNT, 100 ), 3 ) ;

	CRect	RParent, RMessages ;
	GetClientRect( RParent ) ;
	m_Messages.GetWindowRect( RMessages ) ;
	ScreenToClient( RMessages ) ;

	_EcartGauche	=	RMessages.left - RParent.left ;
	_EcartDroite	=	RParent.right - RMessages.right ;
	_EcartHaut		=	RMessages.top - RParent.top ;
	_EcartBas		=	RParent.bottom - RMessages.bottom ;
	
	RemplitMails() ;

	BougeFenetre() ;

	INT	colonnes[5] ;
	colonnes[0]	=	GetConfigurationInt( COLUMN_ORDER, STATE, 0) ;
	colonnes[1]	=	GetConfigurationInt( COLUMN_ORDER, SUBJECT, 1) ;
	colonnes[2]	=	GetConfigurationInt( COLUMN_ORDER, SUBJECT, 2) ;
	colonnes[3]	=	GetConfigurationInt( COLUMN_ORDER, CONTENT, 3) ;
	colonnes[4]	=	GetConfigurationInt( COLUMN_ORDER, ACCOUNT, 4) ;

	m_Messages.SetColumnOrderArray( sizeof( colonnes )/sizeof( colonnes[0]), colonnes ) ;

	SetTimer( 1, GetTimerDelay( DELAY_BEFORE_HIDE ), 0 ) ;
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CDlgNewMessages::RemplitMails()
{
	int n = 0 ;

	for ( int i = 0; i < Comptes.GetSize(); i++)
		{
		CCompteMail*	pCompte	=	Comptes[i] ;

		for ( int j = 0; j < pCompte->GetNbMails(); j++)
			{
			const CMail*	pMail	=	pCompte->GetMail( j ) ;
			const BOOL bCheck	=	pMail->Acknowledged() ;
			LVITEM item ;
			item.mask	=	LVIF_PARAM | LVIF_STATE | LVIF_STATE | LVIF_TEXT ;
			item.iItem	=	n ;
			item.iSubItem=	0 ;
			item.state	=	INDEXTOSTATEIMAGEMASK ( bCheck ) ;
			item.stateMask= LVIS_STATEIMAGEMASK  ;

			char	Buffer[1024] ;
			strcpy( Buffer, GetState( pMail) ) ;
			item.pszText=	Buffer ;
			item.iImage	=	0 ;
			item.lParam =	(DWORD)pMail ;
			item.iIndent=	0 ;

			const int Indice	=	m_Messages.InsertItem( &item ) ;

			m_Messages.SetItem( Indice, 1, LVIF_TEXT, pMail->From(), 0, 0, 0, 0) ;
			m_Messages.SetItem( Indice, 2, LVIF_TEXT, pMail->Subject(), 0, 0, 0, 0) ;
			m_Messages.SetItem( Indice, 3, LVIF_TEXT, pMail->Content(), 0, 0, 0, 0) ;
			m_Messages.SetItem( Indice, 4, LVIF_TEXT, pCompte->Nom(), 0, 0, 0, 0) ;
			m_Messages.SetCheck( Indice, bCheck ) ;
			
			n ++ ;
			}
		}
}

void CDlgNewMessages::OnItemchangedMessages(NMHDR* pNMHDR, LRESULT* pResult) 
{
	if ( pNMHDR == NULL )
		return ;

	NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;
	*pResult = 0;

	if (pNMListView->uOldState == 0 && pNMListView->uNewState == 0)
		return;	// No change

	BOOL bPrevState = (BOOL)(((pNMListView->uOldState & 
				LVIS_STATEIMAGEMASK)>>12)-1);   // Old check box state
	if (bPrevState < 0)	// On startup there's no previous state 
		bPrevState = 0; // so assign as false (unchecked)

	// New check box state
	int bChecked=(BOOL)(((pNMListView->uNewState & LVIS_STATEIMAGEMASK)>>12)-1);   
	if (bChecked < 0) // On non-checkbox notifications assume false
		bChecked = 0; 

	if (bPrevState == bChecked) // No change in check box
		return;

	const int n		=	pNMListView->iItem ;
	CMail*	pMail	=	(CMail*)m_Messages.GetItemData( n ) ;
	if ( pMail )
		{
		pMail->Acknowledge( bChecked ) ;
		m_Messages.SetItem( n, 0, LVIF_TEXT, GetState( pMail ), 0, 0, 0, 0 ) ;
		}
	
	*pResult = 0;
}
///////////////////////////////////////////////////////////////////////////////
// Get the docking side of a taskbar : ABE_TOP, ABE_BOTTOM, ABE_LEFT, ABE_RIGHT
///////////////////////////////////////////////////////////////////////////////
UINT GetTaskBarPosition(HWND hTaskBar)
{
	// Determine which screen the taskbar is closer
	const LONG	Left	=	0 ;
	const LONG	Right	=	GetSystemMetrics( SM_CXFULLSCREEN ) ;
	const LONG	Top		=	0 ;
	const LONG	Bottom	=	GetSystemMetrics( SM_CYFULLSCREEN ) ;
	
	CRect	R ;
	::GetWindowRect( hTaskBar, R ) ;

	CPoint	MiddleOfTaskBar	=	R.CenterPoint() ;

	const LONG DistanceLeft	=	labs( MiddleOfTaskBar.x- Left ) ;
	const LONG DistanceRight=	labs( MiddleOfTaskBar.x- Right ) ;
	const LONG DistanceTop	=	labs( MiddleOfTaskBar.y- Top ) ;
	const LONG DistanceBottom=	labs( MiddleOfTaskBar.y- Bottom ) ;

	// Determine which distance is smaller
	int	DistanceMin		=	min( DistanceLeft, DistanceRight ) ;
	DistanceMin			=	min( DistanceMin, DistanceTop ) ;
	DistanceMin			=	min( DistanceMin, DistanceBottom ) ;

	if ( DistanceMin	==	DistanceBottom )
		return ABE_BOTTOM ;

	if ( DistanceMin	==	DistanceTop )
		return ABE_TOP ;

	if ( DistanceMin	==	DistanceRight )
		return ABE_RIGHT ;

	return ABE_LEFT ;
}


void CDlgNewMessages::BougeFenetre()
{
	//////////////////////////////////////////////////////// Get the task bar
	HWND hTaskBar	=	::FindWindow( "Shell_TrayWnd", NULL ) ;
	if ( ! hTaskBar )
		return ;

	CRect	TaskBarRect ;
	::GetWindowRect( hTaskBar, TaskBarRect ) ;
	// Get the task position
	const UINT Edge	=	GetTaskBarPosition( hTaskBar ) ;

	/////////////////////////////////////////////// Now find its child window
	HWND hIconTray	=	::FindWindowEx( hTaskBar, NULL, "TrayNotifyWnd", NULL ) ;
	if ( ! hIconTray )
		return ;

	// Get the window position
	CRect	IconTrayRect ;
	::GetWindowRect( hIconTray, IconTrayRect ) ;

	CRect Initial, Final ;
	GetWindowRect( Final ) ;
	GetWindowRect( Initial ) ;

	switch ( Edge )
		{
		case ABE_BOTTOM :
			Final.bottom	=	TaskBarRect.top + 8 ;
			Final.top		=	Final.bottom - Initial.Height() ;
			Final.right		=	TaskBarRect.right - 8 ;
			Final.left		=	Final.right - Initial.Width() ;
		break ;
/*
		case ABE_LEFT :
			Initial.left	=	TaskBarRect.right ;
			Initial.right	=	Initial.left + Width ;
			Initial.top		=	IconTrayRect.top - IconTrayRect.Height() /4 ;
			Initial.bottom	=	Initial.top + Height ;

			Final.left		=	TaskBarRect.right + Width / 2 ;
			Final.right		=	Final.left + Width ;
			Final.top		=	Initial.top ;
			Final.bottom	=	Initial.top + Height ;
			break ;

		case ABE_RIGHT :
			Initial.right	=	TaskBarRect.left;
			Initial.left	=	Initial.right - Width ;
			Initial.top		=	IconTrayRect.top + IconTrayRect.Height() /4 ;
			Initial.bottom	=	Initial.top + Height ;

			Final.right		=	TaskBarRect.right - Width / 2 ;
			Final.left		=	Final.right - Width ;
			Final.top		=	Initial.top ;
			Final.bottom	=	Initial.top + Height ;
			break ;
		
		case ABE_TOP :
			Initial.top		=	TaskBarRect.bottom ;
			Initial.bottom	=	Initial.top + Height ;
			Initial.right	=	IconTrayRect.right -IconTrayRect.Width()/4;
			Initial.left	=	IconTrayRect.right - Width ;

			Final.bottom	=	TaskBarRect.bottom + Height * 3 / 2 ;
			Final.top		=	Final.bottom - Height ;
			Final.left		=	Initial.left ;
			Final.right		=	Final.left + Width ;
			break ;*/
		}

	Final.left	=	GetConfigurationInt( NEWMAILSWINDOW, LEFT, Final.left ) ;
	Final.right	=	GetConfigurationInt( NEWMAILSWINDOW, RIGHT, Final.right ) ;
	Final.top	=	GetConfigurationInt( NEWMAILSWINDOW, TOP, Final.top ) ;
	Final.bottom=	GetConfigurationInt( NEWMAILSWINDOW, BOTTOM, Final.bottom ) ;

	SetWindowPos( &CWnd::wndTop, Final.left, Final.top, Final.Width(), Final.Height(), 0 ) ;
}

HBRUSH CDlgNewMessages::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor) 
{
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);
	
	pDC->SetBkColor( RGB( 255, 255, 192 )) ;
	pDC->SetTextColor( RGB( 0, 0, 0 )) ;
	pDC->SetBkMode(TRANSPARENT);

	return m_hBrush ;
}

BOOL CDlgNewMessages::OnEraseBkgnd(CDC* pDC) 
{
	CRect R ;
	GetClientRect( R ) ;
	pDC->FillRect( R, CBrush::FromHandle( m_hBrush )) ;

	return TRUE ;
}

void CDlgNewMessages::OnSize(UINT nType, int cx, int cy) 
{
	CDialog::OnSize(nType, cx, cy);
	
	CRect R ;
	GetClientRect( R ) ;

	if ( IsWindow( m_Messages ))
		{
		m_Messages.MoveWindow( _EcartGauche, _EcartHaut, 
								R.Width() - (_EcartGauche + _EcartDroite),
								R.Height() - (_EcartHaut + _EcartBas )) ;

		GetWindowRect( R ) ;
		WriteConfigurationInt( NEWMAILSWINDOW, LEFT, R.left ) ;
		WriteConfigurationInt( NEWMAILSWINDOW, RIGHT, R.right ) ;
		WriteConfigurationInt( NEWMAILSWINDOW, TOP, R.top ) ;
		WriteConfigurationInt( NEWMAILSWINDOW, BOTTOM, R.bottom ) ;
		}
}

void CDlgNewMessages::OnMailclient() 
{
	CString	MailClient	=	GetConfigurationString( "Mail", "Client", "" ) ;
	if (! MailClient.IsEmpty())
		{
		SupprimeMailsMarques() ;
		WinExec( MailClient, SW_SHOW ) ;
		DestroyWindow() ;
		::SendMessage( hwndMain, wPrivateMessage, LAUNCHED_MAIL_CLIENT, 0 ) ;
		}
}

void CDlgNewMessages::OnMove(int x, int y) 
{
	CDialog::OnMove(x, y);

	if ( IsWindow( m_Messages ))
		{
		CRect R ;
		GetWindowRect( R ) ;
		WriteConfigurationInt( NEWMAILSWINDOW, LEFT, R.left ) ;
		WriteConfigurationInt( NEWMAILSWINDOW, RIGHT, R.right ) ;
		WriteConfigurationInt( NEWMAILSWINDOW, TOP, R.top ) ;
		WriteConfigurationInt( NEWMAILSWINDOW, BOTTOM, R.bottom ) ;
		}
}

void CDlgNewMessages::OnColumnclickMessages(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;
	// TODO: Add your control notification handler code here
	
	*pResult = 0;
}




void CDlgNewMessages::OnClose() 
{
	SupprimeMailsMarques() ;

	CDialog::OnClose();
}

void CDlgNewMessages::OnTimer(UINT nIDEvent) 
{
	if ( GetFocus() != this )
		OnClose() ;		
}

CString CDlgNewMessages::GetState( const CMail * pMail )
{
	switch( pMail->Acknowledged() )
		{
		case 0 :
			return "new mail" ;
		case 1 :
			return "acknowledged, do not notify anymore for this mail" ;
		case 2 :
			return "to be removed from the list when the window will be closed" ;
		default:
			return "unknown" ;			
		}
}

void CDlgNewMessages::Transparence()
{
	static const int Blend	=	GetConfigurationInt( TRANSPARENCY, BLEND, 70 ) ;
	if ( Blend == 100 )
		return ;

	typedef BOOL (WINAPI * FCT_SetLayeredWindowAttributes)(	HWND hwnd,           // handle to the layered window
													COLORREF crKey,      // specifies the color key
													BYTE bAlpha,         // value for the blend function
													DWORD dwFlags        // action
				);
	
	HINSTANCE	hLib	=	LoadLibrary( "user32" ) ;
	if ( ! hLib )
		return ;

	FCT_SetLayeredWindowAttributes fct	=	(FCT_SetLayeredWindowAttributes)GetProcAddress( hLib, "SetLayeredWindowAttributes" ) ;
	if ( ! fct )
		{
		FreeLibrary( hLib ) ;
		return ;
		}	

#ifndef WS_EX_LAYERED
#define WS_EX_LAYERED			0x00080000
#endif
#ifndef LWA_ALPHA
#define LWA_COLORKEY            0x00000001
#define LWA_ALPHA               0x00000002
#endif

	ModifyStyleEx( 0, WS_EX_LAYERED ) ;
	fct( *this, RGB( 255, 255, 192 ), (255*Blend)/100, LWA_COLORKEY|LWA_ALPHA ) ;

	FreeLibrary( hLib ) ;
}

void CDlgNewMessages::SupprimeMailsMarques()
{
// Fait la tournee des mails pour supprimer ceux qui sont 'a supprimer'
	for (int i = 0; i < m_Messages.GetItemCount(); i++)
		{
		const int	State		=	(m_Messages.GetItemState( i, LVIS_STATEIMAGEMASK) >> 12) - 1 ;
	
		if ( State == 2 )
			{
			CMail* pMail	=	(CMail*)m_Messages.GetItemData( i ) ;
			if ( pMail )
				{
				for (int j = 0; j < Comptes.GetSize(); j++)
					Comptes[j]->SupprimeMail( pMail ) ;
				}
			}
		}
	// Sauver les tailles des colonnes
	WriteConfigurationInt( 	HEADER, STATE,	m_Messages.GetColumnWidth( 0 )) ;
	WriteConfigurationInt( 	HEADER, FROM,	m_Messages.GetColumnWidth( 1 )) ;
	WriteConfigurationInt( 	HEADER, SUBJECT, m_Messages.GetColumnWidth( 2 )) ;
	WriteConfigurationInt( 	HEADER, CONTENT, m_Messages.GetColumnWidth( 3 )) ;
	WriteConfigurationInt( 	HEADER, ACCOUNT, m_Messages.GetColumnWidth( 4 )) ;


	INT	colonnes[5] ;
	m_Messages.GetColumnOrderArray( colonnes, sizeof( colonnes )/sizeof( colonnes[0])) ;
	
	WriteConfigurationInt( COLUMN_ORDER, STATE, colonnes[0]) ;
	WriteConfigurationInt( COLUMN_ORDER, FROM, colonnes[1]) ;
	WriteConfigurationInt( COLUMN_ORDER, SUBJECT, colonnes[2]) ;
	WriteConfigurationInt( COLUMN_ORDER, CONTENT, colonnes[3]) ;
	WriteConfigurationInt( COLUMN_ORDER, ACCOUNT, colonnes[4]) ;
}
