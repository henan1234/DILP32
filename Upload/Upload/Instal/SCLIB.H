//*************************************************************************
// SCLib.h
//************************************************************************* 
// Some functions that allow to create and resolve shortcuts
//
//	  19/06/1995
//
//You must:
//	 - Call the function "InitializeSCLib()" in "InitInstance" handler
//	   for initializing the component object library
//	 - Call the function "UnInitializeSCLib()" in "ExitInstance" handler
//     for uninitializing the component object library
//
//AUTHOR : EZZADEEN Manar
//
//**************************************************************************

#ifndef _SCLIB_H
#define _SCLIB_H
#endif


// Error codes
#define	SC_NoError				0x00000000	//No errors occured
#define	SC_CoCreateInstance		0x00000001	//"CoCreateInstance" is failed
#define	SC_QueryInterface		0x00000002	//"QueryInterface" is failed
#define	SC_SetPath				0x00000004	//"SetPath" is failed
#define	SC_SetDescription		0x00000008	//"SetDescription" is failed
#define	SC_SetIconLocation		0x00000010	//"SetIconLocation" is failed
#define	SC_Save					0x00000020	//"Save" is failed
#define SC_WDirectory			0x00000040	//"SetWorkingDirectory" is failed
#define SC_Load           		0x00000080	//"Load" is failed
#define SC_Resolve				0x00000100	//"Resolve" is failed
#define SC_GetPath				0x00000200	//"GetPath" is failed
#define SC_GeDescription    	0x00000400	//"GetDescription" is failed
#define SC_GeIconLocation		0x00000800	//"GetIconLocation" is failed
#define SC_GWDirectory			0x00001000 	//"GetWorkingDirectory" is failed
#define SC_ShowCmd				0x00002000	//"SetShowCmd" is failed
#define SC_GetShowCmd			0x00004000  //"GetShowCmd" is failed
#define SC_SetArguments			0x00008000	//"SetArguments" is failed
#define SC_GetArguments			0x00010000	//"GetArguments" is failed 


typedef struct {

char szLink[MAX_PATH];				//The Shell Link (shortcut)
  					                //ex: c:\windows\desktop\Name of shortcut.lnk  
  					                //(on the desktop)
					                //or ex: c:\titi\tata\Name of shortcut.lnk
					                //(not on the desktop)
char szTargetFile[MAX_PATH];  		//The file with its path
  					          		//ex: c:\toto\coco\filename.ext
char szDescription[MAX_PATH];		//The description of the shortcut
char szIconFile[MAX_PATH];			//The path of the file containing the icon
int  IconIndex;						//Index of the icon
char szWDirectory[MAX_PATH];		//The path of the new working directory
int  ShowCmd;						//Sets the show command for a shell link object:
  					                //SW_SHOWNORMAL      :	Normal window
                                    //SW_SHOWMINNOACTIVE :	Minimized window
	                                //SW_MAXIMIZE        :	Maximized window
char szArguments[MAX_PATH];			//Sets the command-line arguments for a shell link object

} SHORTCUTSTRUCT,FAR *LPSHORTCUTSTRUCT;


void  InitializeSCLib();	
DWORD CreateShortcut(LPSHORTCUTSTRUCT lpsc);
DWORD ResolveShortcut(HWND hwnd,LPSHORTCUTSTRUCT lpsc);
void  UnInitializeSCLib();

