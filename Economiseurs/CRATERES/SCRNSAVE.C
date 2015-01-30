/*

			Craters  --  The Screen Saver
			
		by John Walker  --  kelvint@netcom.com
		
		    Release 1.0  --  September 1994

*/ 

#include "craters.h"      

#define ID_TIMER 200

/* Function prototypes */

static void GetIniEntries(void);
static void GetIniSettings(void);
static void WriteProfileInt(LPSTR key, LPSTR tag, int i);

/* Global used by SCRNSAVE.LIB. Required for all screen savers. */

char szAppName[40]="Cratères" ;

/* Globals exported. */

char szName[]="Economiseur Cratères"; 

/* Externals defined in SCRNSAVE.LIB. Required for all screen savers. */

//	Configuration parameters

DWORD resetInterval = 0;						// Reset interval in ticks, 0 = never

static WORD wElapse = 0;						// Speed parameter
static WORD wTimer;								// Timer id
static char szResetScreen[] = "ResetScreen";	// Periodically reset screen ?
static BOOL resetScreen;						// Periodically reset screen
static char szResetInterval[] = "ResetInterval";// Reset interval in minutes
static WORD resetMinutes;						// Reset interval in minutes
static BOOL noMem = FALSE;						// Insufficient memory detected

/* ScreenSaverProc -- Main entry point for screen saver messages.
					  This function is required for all screen savers.

	Params:  Standard window message handler parameters.

	Return:  The return value depends on the message.

	Note that all messages go to the DefScreenSaverProc(), except
	for ones we process.
*/

WindowProc(ScreenSaverProc)
{
    HDC hDC;
    RECT rc;
	SIZE	Size ;

    switch (Message) {

        case WM_CREATE:
        {
            /* Load the strings from the STRINGTABLE */

			hDC = GetDC(hWnd);
            GetIniEntries();
            GetIniSettings();
            
            resetInterval = resetScreen ? (60000L * resetMinutes) : 0;
            
            if (!craterInit()) {
            	noMem = TRUE;
            }

            /* Create a timer to update the image */

            wTimer = SetTimer(hWnd, ID_TIMER, wElapse, NULL);
		    ReleaseDC(hWnd, hDC);
            break;
        }

        case WM_TIMER:
			hDC = GetDC(hWnd);
			if (!noMem)
				{
				if (!craterMake(hWnd, hDC, 100))
					{
					noMem = TRUE;
					}
				}
			
			/*  If we've run out of memory (whether during initialisation or
				during generation), switch the timer to a ten second interval
				and display a randomly-positioned out of memory message on the
				screen.  */
				 
			if (noMem) {
				char s[132];
				int tx, ty;
				DWORD te;
				
				if (wElapse < 10000) {
					// First time.  Change timer interval to 10 seconds
					if (wTimer) {
						KillTimer(hWnd, ID_TIMER);
					}
					wElapse = 10000;
					wTimer = SetTimer(hWnd, ID_TIMER, wElapse, NULL);
					craterTerm();			// Release all memory in use
				}
	    		GetClientRect(hWnd, &rc);
	    		FillRect(hDC, &rc, (HBRUSH) GetStockObject(BLACK_BRUSH));
  				LoadString(hMainInstance, idsInsuffMemory, s, sizeof s);
  				GetTextExtentPoint32( hDC, s, lstrlen(s), &Size ) ;
				
  				SetBkMode(hDC, TRANSPARENT);
  				tx = (int) (((rc.right - Size.cx) * (random() & 32767L)) / 32767L); 
  				ty = (int) (((rc.bottom - Size.cy) * (random() & 32767L)) / 32767L); 
  				SetTextColor(hDC, RGB(255, 255, 255));
  				SetTextAlign(hDC, TA_NOUPDATECP);
  				TextOut(hDC, tx, ty, s, lstrlen(s));
			}
		    ReleaseDC(hWnd, hDC);
            break;

        case WM_DESTROY:
            if (wTimer) {
            	KillTimer(hWnd, ID_TIMER);
            }
            craterTerm();
            break;
            
        case WM_ERASEBKGND:
        	return TRUE;			// No need, since we clear to initial terrain
        	
        case WM_COMPACTING:			// If compacting, release the stampers
        	relstamp();
        	break;
	}

    return DefScreenSaverProc(hWnd, Message, wParam, lParam);
}

/* RegisterDialogClasses -- Entry point for registering window
							classes required by configuration dialog box.

	Params:  hWnd -- Handle to window

	Return:  None
*/

BOOL WINAPI RegisterDialogClasses(HINSTANCE hInst)
{
    return TRUE;
}

//	DlgRelated  --  Plug other related programs

DialogueProc(DlgRelated)
{
    switch (message) {
        case WM_INITDIALOG:
            return TRUE;

        case WM_COMMAND:
            switch (wParam) {
                case IDOK:
                    EndDialog(hDlg, TRUE);
                    return TRUE;

            }
            break;
    }
    return FALSE;
}

/* ScreenSaverConfigureDialog -- Dialog box function for configuration dialog.

	Params:  hWnd -- Handle to window

	Return:  None
*/

DialogueProc(ScreenSaverConfigureDialog)
{
	static HWND hIDOK;

    switch (message) {
        case WM_INITDIALOG:
            GetIniEntries();
            GetIniSettings();
            SendDlgItemMessage(hDlg, IDC_CH_RESET, BM_SETCHECK, (WPARAM)resetScreen, 0);
            SetDlgItemInt(hDlg, IDC_RESET_INT, resetMinutes, FALSE);
            EnableWindow(GetDlgItem(hDlg, IDC_RESET_INT), resetScreen);  
            hIDOK = GetDlgItem(hDlg, IDOK);
            return TRUE;

        case WM_COMMAND:
            switch (wParam) {
                case IDOK:					// OK
                    resetScreen = IsDlgButtonChecked(hDlg, IDC_CH_RESET);
					resetMinutes = GetDlgItemInt(hDlg, IDC_RESET_INT, NULL, FALSE);
					WriteProfileInt(szAppName, szResetInterval, resetMinutes);
					WriteProfileInt(szAppName, szResetScreen, resetScreen);
            		resetInterval = resetScreen ? (60000L * resetMinutes) : 0;

                    EndDialog(hDlg, TRUE);
                    return TRUE;

                case IDCANCEL:				// Cancel
                    EndDialog(hDlg, FALSE);
                    return TRUE;
                    
                case IDC_CH_RESET:			// Reset terrain on/off
                	EnableWindow(GetDlgItem(hDlg, IDC_RESET_INT),
                					IsDlgButtonChecked(hDlg, IDC_CH_RESET));  
                	return TRUE;

                    
                case IDC_BU_RELATED:		// Other related programs
	                {
	                    FARPROC fpDialog;
	
	                    if ((fpDialog = MakeProcInstance((FARPROC) DlgRelated, hMainInstance)) == NULL)
	                        return FALSE;
	                    DialogBox(hMainInstance, MAKEINTRESOURCE(IDD_DI_RELATED),
	                              hDlg, (DLGPROC) fpDialog);
	                    FreeProcInstance(fpDialog);
	                }
                	break;
            }
            break;
    }
    return FALSE;
}

/* GetIniSettings -- Get initial settings from WIN.INI

	Params:  hWnd -- Handle to window

	Return:  None
*/

static void GetIniSettings(void)
{
	resetMinutes = GetPrivateProfileInt(szAppName, szResetInterval, 10, szIniFile); 
	resetScreen = GetPrivateProfileInt(szAppName, szResetScreen, FALSE, szIniFile); 
}

/* WriteProfileInt - Write an unsigned integer value to CONTROL.INI.

	Params:  name - szSection - [section] name in .INI file
		            szKey     - key= in .INI file
					i         - value for key above

	Return:  None
*/

static void WriteProfileInt(LPSTR szSection, LPSTR szKey, int i)
{
    char achBuf[40];

    /* Write out as unsigned because GetPrivateProfileInt() can't
       cope with signed values! */

    wsprintf(achBuf, "%u", i);
    WritePrivateProfileString(szSection, szKey, achBuf, szIniFile);
}

static void GetIniEntries(void)
{
  // Load Common Strings from stringtable...
  LoadString(hMainInstance, idsIniFile, szIniFile, MAXFILELEN);
  LoadString(hMainInstance, idsScreenSaver, szScreenSaver, 22);
  LoadString(hMainInstance, idsHelpFile, szHelpFile, MAXFILELEN);
  LoadString(hMainInstance, idsNoHelpMemory, szNoHelpMemory, BUFFLEN);
}
