// PropsDisque.cpp : implementation file
//

#include "stdafx.h"
#include <winreg.h>
#include "Jibe96.h"
#include "iconedisque.h"
#include "PropsDisque.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPropsDisque dialog


CPropsDisque::CPropsDisque(CIcone * pIcone, CWnd* pParent /*=NULL*/)
:CWndIcone(pIcone)
{
	//{{AFX_DATA_INIT(CPropsDisque)
	m_Disque = _T("");
	m_Props = _T("");
	//}}AFX_DATA_INIT
}


void CPropsDisque::DoDataExchange(CDataExchange* pDX)
{
	CWndIcone::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CPropsDisque)
	DDX_Control(pDX, IDC_DISQUES,	m_Disques);
	DDX_Control(pDX, IDC_ALARME,	m_Alarme);
	DDX_Text(pDX, IDC_PROPS, m_Props);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CPropsDisque, CWndIcone)
	//{{AFX_MSG_MAP(CPropsDisque)
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_DISQUES, OnItemchangedDisques)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPropsDisque message handlers

BOOL CPropsDisque::OnInitDialog() 
{
	CWndIcone::OnInitDialog();
	
	///////////////////////////////////////////////////////////////////////////
	// Construction de la liste d'images
	///////////////////////////////////////////////////////////////////////////
	_ListeIcones.Create( ::GetSystemMetrics( SM_CXICON ),
						 ::GetSystemMetrics( SM_CYICON ),
						 TRUE,
						 5,
						 1 ) ;

	const int	IndiceCDROM		=	_ListeIcones.Add( AfxGetApp()->LoadIcon( IDI_CDROM )) ;
	const int	IndiceFloppy	=	_ListeIcones.Add( AfxGetApp()->LoadIcon( IDI_FLOPPYDISK )) ;
	const int	IndiceHardDisk	=	_ListeIcones.Add( AfxGetApp()->LoadIcon( IDI_HARDDISK )) ;
	const int	IndiceNetwork	=	_ListeIcones.Add( AfxGetApp()->LoadIcon( IDI_NETWORKDISK )) ;
	const int	IndiceRam		=	_ListeIcones.Add( AfxGetApp()->LoadIcon( IDI_RAMDISK )) ;
	
	m_Disques.SetImageList( &_ListeIcones, LVSIL_NORMAL ) ;

	char	Buffer[2000] ;
	GetLogicalDriveStrings( sizeof( Buffer ), Buffer) ;

	char	*	pDisque	=	Buffer ;

	int		NoItem	=	0 ;
	while (*pDisque )
		{
		const	int	DriveType	=	GetDriveType( pDisque ) ;
		int		IndiceImage		=	IndiceHardDisk ;

		switch( DriveType )
			{
			case DRIVE_REMOVABLE :
				IndiceImage	=	IndiceFloppy ;
				break ;
			case DRIVE_CDROM :
				IndiceImage	=	IndiceCDROM ;
				break ;
			case DRIVE_FIXED :
				IndiceImage	=	IndiceHardDisk ;
				break ;
			case DRIVE_RAMDISK :
				IndiceImage	=	IndiceRam ;
				break ;
			case DRIVE_REMOTE :
				IndiceImage	=	IndiceNetwork ;
				break ;
			}

		const int Indice = m_Disques.InsertItem( NoItem,GetDriveName( pDisque ), IndiceImage ) ;
		if ( m_Disque.CompareNoCase( pDisque )==0)
			m_Disques.SetItem( Indice, 0, LVIF_STATE, NULL, 0,
							   LVIS_SELECTED|LVIS_FOCUSED,
							   LVIS_SELECTED|LVIS_FOCUSED,
							   0 ) ;

		NoItem ++ ;
		pDisque +=	lstrlen( pDisque ) + 1 ;
		}


	m_Alarme.SetRange( 0, 100 ) ;
	m_Alarme.SetPageSize( 10 ) ;
	m_Alarme.SetLineSize( 1 ) ;
	m_Alarme.SetTicFreq( 10 ) ;

	m_Alarme.SetPos( m_PourcentageAlarme ) ;

	SetPropsDisque() ;
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CPropsDisque::OnOK() 
{
	m_PourcentageAlarme	=	m_Alarme.GetPos() ;

	CWndIcone::OnOK();
}

CString CPropsDisque::GetDriveName( const CString & Drive )
{
	if ( Drive.IsEmpty())
		return Drive ;

	HKEY	hKey	;
	CString	Key	=	"Network\\Persistent\\" ;
	Key +=	Drive[0] ;
	
	if ( RegOpenKeyEx( HKEY_CURRENT_USER, Key, 0, KEY_READ, &hKey ) != ERROR_SUCCESS )
		return Drive ;

	unsigned char	Buffer[1024] ;
	DWORD	TailleBuffer	=	sizeof( Buffer ) ;
	if ( RegQueryValueEx( hKey, "RemotePath", 0, 0,
						  Buffer, &TailleBuffer	) != ERROR_SUCCESS )
		return Drive ;

	CString Result ;
	Result.Format( "%s (%s)", (LPCSTR)Drive, (LPCSTR)Buffer ) ;
	return Result ;
}

void CPropsDisque::OnItemchangedDisques(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;
	// TODO: Add your control notification handler code here
	if ( pNMListView->uNewState & LVIS_SELECTED )
		{
		char	Buffer[1024] ;
		LV_ITEM	Item ;
		Item.mask	=	LVIF_TEXT ;
		Item.iItem	=	pNMListView->iItem ;
		Item.iSubItem=	pNMListView->iSubItem ;
		Item.cchTextMax= sizeof( Buffer ) ;

		Item.pszText=	Buffer ;
		m_Disques.GetItem( & Item ) ;

		m_Disque	=	Buffer ;
		m_Disque	=	m_Disque.Left( 3 ) ;
		SetPropsDisque() ;
		}
	*pResult = 0;
}

void CPropsDisque::SetPropsDisque( void )
{
	char	VolumeNameBuffer[255] ;
	DWORD	SerialNumber ;
	DWORD	MaxComponentLength ;
	DWORD	Flags ;
	char	FileSystemName[255] ;

	GetVolumeInformation( m_Disque,
						  VolumeNameBuffer, sizeof( VolumeNameBuffer ),
						  &SerialNumber,
						  &MaxComponentLength,
						  &Flags,
						  FileSystemName, sizeof( FileSystemName )) ;

	// Decodage des flags
	CString	Flgs ;

	if ( Flags & FS_CASE_IS_PRESERVED )
		{
		CString	F ; F.LoadString( IDS_CASE_PRESERVED ) ;
		Flgs += F + "\r\n" ;
		}

	if ( Flags & FS_CASE_SENSITIVE )
		{
		CString	F ; F.LoadString( IDS_CASE_SENSITIVE ) ;
		Flgs += F + "\r\n" ;
		}

	if ( Flags & FS_UNICODE_STORED_ON_DISK )
		{
		CString	F ; F.LoadString( IDS_UNICODE_ON_DISK ) ;
		Flgs += F + "\r\n" ;
		}

	if ( Flags & FS_PERSISTENT_ACLS )
		{
		CString	F ; F.LoadString( IDS_PERSISTENT_ACLS ) ;
		Flgs += F + "\r\n" ;
		}

	
	if ( Flags & FS_FILE_COMPRESSION )
		{
		CString	F ; F.LoadString( IDS_FILE_COMPRESSION ) ;
		Flgs += F + "\r\n" ;
		}

	if ( Flags & FS_VOL_IS_COMPRESSED )
		{
		CString	F ; F.LoadString( IDS_VOL_COMPRESSED ) ;
		Flgs += F + "\r\n" ;
		}

	m_Props.Format( IDS_FORMAT_VOLUME,	VolumeNameBuffer, SerialNumber,
										MaxComponentLength, Flgs,
										FileSystemName ) ;

	UpdateData( FALSE ) ;
	
}

/////////////////////////////////////////////////////////////////////////////
// Demande de confirmation de la fermeture de la fenetre
// On en profite pour sauver les infos
/////////////////////////////////////////////////////////////////////////////
BOOL CPropsDisque::ConfirmeFermetureAuto( void )
{
	ASSERT_VALID(_pIconeAssociee ) ;
	CIconeDisque*	pIcone	=	STATIC_DOWNCAST( CIconeDisque, _pIconeAssociee ) ;

	pIcone->SetPourcentageAlarme( m_Alarme.GetPos()) ;
	pIcone->SetNomDisque( m_Disque ) ;

	return TRUE ;
}
