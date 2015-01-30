//*************************************************************************
//SCLib.cpp
//
// AUTHOR: EZZADEEN Manar
//*************************************************************************

#include "stdafx.h"
#include <winnls.h>
#include "sclib.h"
#include <winnetwk.h>
#include <shlobj.h>	//IShellLink interface 
                        //(you must have WINDOWS 95 SDK for this)	 


//**************************************************************************
//
//  FUNCTION:InitializeSCLib()
//
//  PURPOSE: initialize the component object library
//
//  PARAMETERS:	- 
// 
//  RETURN VALUE: -
//
//  COMMENT : Must be called in "InitInstance" handler
//
//***************************************************************************

void  InitializeSCLib()
{
  CoInitialize(NULL);
}	


//*******************************************************************
//
//  FUNCTION:CreateShortcut(LPSHORTCUTSTRUCT lpsc)
//
//  PURPOSE: Create a shortcut to the file 
//
//  PARAMETERS:	 lpsc : a pointer to SHORTCUTSTRUCT structure
// 
//  RETURN VALUE:
//
//  	     Return  SC_NoError : If the shortcut was successfully created,
//        	 else can be a combination of these SC_ errors
//***************************************************************************

DWORD CreateShortcut(LPSHORTCUTSTRUCT lpsc)
{
    HRESULT	hres;
    IShellLink* psl;
	DWORD Err=SC_NoError;


	// Get a pointer to the IShellLink interface
	hres= CoCreateInstance(CLSID_ShellLink,NULL,CLSCTX_INPROC_SERVER,
						   IID_IShellLink, (void **) &psl);
	if(SUCCEEDED(hres))
	 {
	   IPersistFile *ppf;
	   
	   //Determine whether a specific interface is supported 
	   //for the object and get a pointer to it
	   hres=psl->QueryInterface(IID_IPersistFile,(void **)&ppf);
	   if(SUCCEEDED(hres))
	    {
		  WORD wsz[MAX_PATH];

		 //Set the path to the shortcut
		 hres=psl->SetPath(lpsc->szTargetFile);
		 if(!SUCCEEDED(hres)) Err |= SC_SetPath;

         //Set description to shortcut
		 hres=psl->SetDescription(lpsc->szDescription);
		 if(!SUCCEEDED(hres)) Err |= SC_SetDescription;
			   

		 //Set Icon Location
		 hres=psl->SetIconLocation(lpsc->szIconFile,lpsc->IconIndex);
		 if(!SUCCEEDED(hres)) Err |= SC_SetIconLocation; 

		 //Set Working Directory
		 hres=psl->SetWorkingDirectory(lpsc->szWDirectory);
		 if(!SUCCEEDED(hres)) Err |= SC_WDirectory;

		 //Set Show Command
		 hres=psl->SetShowCmd(lpsc->ShowCmd);
		 if(!SUCCEEDED(hres)) Err |= SC_ShowCmd;

		 //Set Arguments
		 hres=psl->SetArguments(lpsc->szArguments);
		 if(!SUCCEEDED(hres)) Err |= SC_SetArguments;

		 //Ensure that the string is Unicode
		 MultiByteToWideChar(CP_ACP,0,lpsc->szLink,-1,wsz,MAX_PATH);

		 //saves a copy of the object to the 
		 //indicated filename in wsz
		 hres=ppf->Save((LPCOLESTR)wsz,STGM_READ);
		 if(!SUCCEEDED(hres)) Err |= SC_Save;
						
		 ppf->Release();
		}
	   else Err |= SC_QueryInterface; 

	   psl->Release();
	 }
	else Err |= SC_CoCreateInstance;	
	 
  return Err;
}


//************************************************************************************
//
//  FUNCTION: ResolveShortcut(HWND hwnd,LPSHORTCUTSTRUCT lpsc)
//
//  PURPOSE: Resolve a shortcut 
//
//  PARAMETERS:
//
//	  hwnd 				- The handle to the current focus window. We need this 
//	              		  in case the shell needs to display a message box prompting 
//	                      the user to do something.
//	  lpsc              - a pointer to SHORTCUTSTRUCT structure 	
//
//   
//  RETURN VALUE:
//
//  	Return  SC_NoError : If the shortcut was successfully resolved,
//  	else can be a combination of the SC_ errors
//
//***********************************************************************************
	      

DWORD ResolveShortcut(HWND hwnd,LPSHORTCUTSTRUCT lpsc)
{
   HRESULT hres;
   IShellLink* psl;
   DWORD Err=SC_NoError;
   WIN32_FIND_DATA wfd;
   char szGotPath[MAX_PATH];

   //Get a pointer to the IShellLink interface
   hres=CoCreateInstance(CLSID_ShellLink,NULL,CLSCTX_INPROC_SERVER,
   						 IID_IShellLink, (void **) &psl);
   if(SUCCEEDED(hres))
     {
	   IPersistFile *ppf;

	   //Get a pointer to the IPersistFile interface
	   hres=psl->QueryInterface(IID_IPersistFile, (void **)&ppf);
	   if(SUCCEEDED(hres))
         {
		    WORD wsz[MAX_PATH];

			MultiByteToWideChar(CP_ACP,0,lpsc->szLink,-1,wsz,MAX_PATH);
			
			hres=ppf->Load((LPCOLESTR)wsz,STGM_READ);
			if(SUCCEEDED(hres))
              {
			   //Resolve the link
			   hres=psl->Resolve(hwnd,SLR_ANY_MATCH);
			   if(SUCCEEDED(hres))
                 {
				  //Get the path of the target of the shortcut
				  strcpy(szGotPath,lpsc->szLink);
				  hres=psl->GetPath(szGotPath,MAX_PATH,(WIN32_FIND_DATA*)&wfd,SLGP_UNCPRIORITY);
				  if(!SUCCEEDED(hres)) Err |= SC_GetPath;
				  strcpy(lpsc->szTargetFile,szGotPath); 
				  hres=psl->GetDescription(szGotPath,sizeof(szGotPath));
				  if(!SUCCEEDED(hres)) Err |= SC_GeDescription;
				  strcpy(lpsc->szDescription,szGotPath);
				  hres=psl->GetIconLocation(szGotPath,sizeof(szGotPath),&lpsc->IconIndex);
				  if(!SUCCEEDED(hres)) Err |= SC_GeIconLocation;
				  strcpy(lpsc->szIconFile,szGotPath);
				  hres=psl->GetWorkingDirectory(szGotPath,sizeof(szGotPath));
				  if(!SUCCEEDED(hres)) Err |= SC_GWDirectory;
				  strcpy(lpsc->szWDirectory,szGotPath);
				  hres=psl->GetShowCmd(&lpsc->ShowCmd);
				  if(!SUCCEEDED(hres)) Err |= SC_GetShowCmd;
				  hres=psl->GetArguments(szGotPath,sizeof(szGotPath));
				  if(!SUCCEEDED(hres)) Err |= SC_GetArguments;
				  strcpy(lpsc->szArguments,szGotPath);
				 }
			   else Err |= SC_Resolve;
			  }
			else Err |= SC_Load;
		  ppf->Release();
		 }
	   else Err |= SC_QueryInterface; 

	   psl->Release();
     }
   else Err |= SC_CoCreateInstance;

 return Err;
}


//*******************************************************************
//
//  FUNCTION:UnInitializeSCLib()
//
//  PURPOSE: Uninitialize the component object library
//
//  PARAMETERS:	- 
// 
//  RETURN VALUE: -
//
//  COMMENT : Must be called in "ExitInstance" handler
//
//***************************************************************************

void  UnInitializeSCLib()
{
  CoUninitialize();
}	

