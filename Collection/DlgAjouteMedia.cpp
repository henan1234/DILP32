// DlgAjouteMedia.cpp : implementation file
//

#include "stdafx.h"
#include "Collection.h"
#include "DlgAjouteMedia.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgAjouteMedia dialog


CDlgAjouteMedia::CDlgAjouteMedia(CWnd* pParent /*=NULL*/)
	: CDlgProprietesGenerique(CDlgAjouteMedia::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgAjouteMedia)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CDlgAjouteMedia::DoDataExchange(CDataExchange* pDX)
{
	CDlgProprietesGenerique::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgAjouteMedia)
	DDX_Control(pDX, IDC_LISTE_MEDIAS, m_ListeMedias);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgAjouteMedia, CDlgProprietesGenerique)
	//{{AFX_MSG_MAP(CDlgAjouteMedia)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgAjouteMedia message handlers

/////////////////////////////////////////////////////////////////////////////
/**
  * Retrouve la liste des Drives connectes a la machine et remplit la liste
  * correspondante
  */
/////////////////////////////////////////////////////////////////////////////
void CDlgAjouteMedia::AjouteDrives()
{
	char Buffer[1024*10] ;
	GetLogicalDriveStrings( sizeof( Buffer ), Buffer ) ;

	_ImageListeMedias.Create( GetSystemMetrics( SM_CXICON), GetSystemMetrics( SM_CYICON ),
							  ILC_COLOR32 | ILC_MASK, 0, 1 ) ;

	m_ListeMedias.SetImageList( &_ImageListeMedias, LVSIL_NORMAL ) ;
	char * pDrive	=	Buffer ;
	int	i	=0 ;
	while ( * pDrive )
		{
		char Path[ MAX_PATH ] ;
		WORD	Index ;
		strcpy( Path, pDrive ) ;

		HICON	hIcon	= ExtractAssociatedIcon( AfxGetInstanceHandle(), Path, &Index ) ;
		int Ind			= _ImageListeMedias.Add( hIcon ) ;
		
		m_ListeMedias.InsertItem( i, pDrive, Ind ) ;
		pDrive		+=	strlen( pDrive ) + 1 ;

		i++ ;
		}
}

BOOL CDlgAjouteMedia::OnInitDialog() 
{
	CDlgProprietesGenerique::OnInitDialog();
	
	AjouteDrives() ;
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
