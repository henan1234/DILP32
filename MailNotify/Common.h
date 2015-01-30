// COMMON.H
//
//
//

typedef enum
	{
	DELAY_CHECK,
	DELAY_BEFORE_HIDE,
	DELAY_FLASH,
	DELAY_ANIMATION
	}
	T_TIMER_DELAY ;

#define		LAUNCHED_MAIL_CLIENT	0
#define		CLOSED_MAILS_WINDOW		1


const		TCHAR	szClassName	[]				=	TEXT("LPI:MailNotify:IconWarningMessage") ;
const		TCHAR	szMessageWindowClassName[]	=	TEXT("LPI:MailNotify:IconWarningMessage") ;
const		TCHAR	szAppName[]					=	TEXT("LPI:MailNotify:") ;
const		TCHAR	szSurroundingWindowClassName[]=	TEXT("LPI:MailNotify:SurroundingWindow");

// This command line parameter is used by the minimal program to order the Window
// program to launch HP Brio Center
// We are doing so to avoid linking the mini program with MFC
const		TCHAR	szCmdLineForHPCenterRemoteLaunch[]=	TEXT("CenterWarnIcon.exe /LAUNCH_CENTER") ;
const		TCHAR	szCmdLineParameterForLaunchHPCenter[]=	TEXT("/LAUNCH_CENTER") ;


// Configuraion file strings
const TCHAR	INI_FILE_NAME[]				=	TEXT("MailNotify.ini") ;
const TCHAR	CFG_PARAMETERS[]			=	TEXT("Parameters") ;
const TCHAR	CFG_DELAY_CHECK[]			=	TEXT("Delay between mail check" ) ;
const TCHAR	CFG_DELAY_BEFORE_HIDE[]		=	TEXT("Delay Before Hide" ) ;
const TCHAR	CFG_DELAY_FLASH[]			=	TEXT("Delay Flash" ) ;
const TCHAR	CFG_DELAY_ANIMATION[]		=	TEXT("Delay Animation" ) ;
const TCHAR CFG_NBTIPS[]				=	TEXT("Nb Tips") ;
const TCHAR CFG_CURRENTTIP[]			=	TEXT("Current Tip" ) ;
const TCHAR	CFG_TIPVALUE[]				=	TEXT("Tip%d") ;
const TCHAR CFG_TIPS[]					=	TEXT("Tips") ;
const TCHAR	CFG_ICONTIP[]				=	TEXT("Icon Tip") ;
const TCHAR CFG_MENU[]					=	TEXT("Menu") ;
const TCHAR CFG_OPEN_BRIO[]				=	TEXT("Open Brio Center") ;
const TCHAR CFG_QUIT[]					=	TEXT("Quit") ;
const TCHAR CFG_BITMAP_FILE_NAME[]		=	TEXT("Background Bitmap");
const TCHAR CFG_ICON_RECTANGLE[]		=	TEXT("Icon Rectangle" ) ;
const TCHAR CFG_TEXT_RECTANGLE[]		=	TEXT("Text Rectangle" ) ;
const TCHAR CFG_BACKGROUND_ICON[]		=	TEXT("Background icon" ) ;
const TCHAR CFG_LAUNCH_HP_CENTER[]		=	TEXT("Launch Center Command line") ;

void	ToTheExeDirectory( TCHAR * FilePath ) ;
void	GetConfigurationString( const TCHAR * pSectionName, const TCHAR * pValueName,
								TCHAR * Value, int Size ) ;
CString GetConfigurationString( const TCHAR * pSectionName, const TCHAR * pValueName, const TCHAR * pDefault ) ;
int GetConfigurationInt( const TCHAR * pSectionName, const TCHAR * pValueName, int Default ) ;
void WriteConfigurationString( const TCHAR * pSectionName, const TCHAR * pValueName, const TCHAR * pValue ) ;
void WriteConfigurationInt( const TCHAR * pSectionName, const TCHAR * pValueName, int Value ) ;

UINT GetTimerDelay( T_TIMER_DELAY Delay ) ;
void SetTimerDelay( T_TIMER_DELAY Delay, UINT ) ;

BOOL MultipleInstances() ;
void ExitInstance() ;
