//**********************************************************************
//**********************************************************************
//**                                                                  **
//**        (C)Copyright 1985-2010, American Megatrends, Inc.         **
//**                                                                  **
//**                       All Rights Reserved.                       **
//**                                                                  **
//**     5555 Oakbrook Pkwy, Suite 200, Norcross, GA 30093            **
//**                                                                  **
//**                       Phone: (770)-246-8600                      **
//**                                                                  **
//**********************************************************************
//**********************************************************************
//**********************************************************************
// $Header: /Alaska/Projects/Intel/Haswell/LynxPoint_SharkBay-DT_Crb_1AQQW/Board/EM/TCG2/Common/Setup/TPMPwd.c 1     7/08/15 4:25a Chienhsieh $
//
// $Revision: 1 $
//
// $Date: 7/08/15 4:25a $
//**********************************************************************
// Revision History
// ----------------
// $Log: /Alaska/Projects/Intel/Haswell/LynxPoint_SharkBay-DT_Crb_1AQQW/Board/EM/TCG2/Common/Setup/TPMPwd.c $
// 
// 1     7/08/15 4:25a Chienhsieh
// 
// 2     6/11/14 4:15p Fredericko
// 
// 1     4/21/14 2:18p Fredericko
// 
// 1     10/08/13 12:05p Fredericko
// Initial Check-In for Tpm-Next module
// 
// 1     7/10/13 5:57p Fredericko
// [TAG]  		EIP120969
// [Category]  	New Feature
// [Description]  	TCG (TPM20)
// 
// 7     10/22/12 1:21a Jittenkumarp
// [TAG]  		EIP100790 
// [Category]  	Improvement
// [Description]  	ActivateApplication in AMITSE delayed if the SoftKbd
// support enabled thereforTPM Message are not displayed
// [Files]  		AmiTcgPlatformDxe.c, TCG.sdl, TPMPwd.c , AmiTcgPlatform.sdl
// 
// 6     11/22/11 6:45p Fredericko
// [TAG]  		EIP67286
// [Category]  	Improvement
// [Description]  	Separate out how load defaults are handled in setup
// from the TpmPwd.c
// [Files]  		1. HandleLoadDefaultsSetup.c
// 2. TcgSetup.cif
// 3. TcgSetup.mak
// 4. TpmPwd.c
// 
// 5     10/07/11 6:55p Fredericko
// 
// 4     9/03/11 8:07p Fredericko
// 
// 3     8/26/11 2:59p Fredericko
// [TAG]  		EIP67286
// [Category]  	Bug Fix
// [Severity]  	Minor
// [Symptom]  	Tpm strings will not update probably when load optimize
// defaults is selected in setup
// [RootCause]  	Tcgsetup.sd did not account for F3 from setup
// [Solution]  	Fix TcgSetup.sd to update setup that status information
// for TPM will be available after reset.
// [Files]  		Tcg.sdl, TPMPwd.c, TcgSetup.sd, TcgSetup.uni
// 
// 2     3/29/11 1:26p Fredericko
// 
// 1     3/28/11 2:58p Fredericko
// [TAG]        EIP 54642
// [Category] Improvement
// [Description] 1. Checkin Files related to TCG function override 
// 2. Include TCM and TPM auto detection
// [Files] Affects all TCG files
// 
// 7     8/09/10 2:32p Fredericko
// UEFI 2.1 changes
// 
// 6     5/19/10 6:25p Fredericko
// Updated AMI Function Headers
// Code Beautification
// EIP 37653
//
// 5     6/02/09 1:18p Fredericko
//
// 4     4/30/09 6:27p Fredericko
// Updated Header Date
//
// 3     4/30/09 5:47p Fredericko
// AMI company Header Address added
//
// 2     10/01/07 5:33p Fasihm
// Corrected the directive for AMIPostMgr.h to point to the correct
// location.
//
// 1     8/09/07 11:35a Pats
// Added to support password authentication. Requires TSE with capability
// of replacing ProcessConInAvailability through elinks.
//
//**********************************************************************
//*************************************************************************
//<AMI_FHDR_START>
//
// Name: TPMPwd.c
//
// Description:
// Contains functions that handle TPM authentication
//
//<AMI_FHDR_END>
//*************************************************************************

#include "token.h"
#include <EFI.h>
#include <Protocol/SimpleTextIn.h>
#include <Protocol/EfiOEMBadging.h>
#include <Setup.h>
#include "AMITSEStrTokens.h"
#include "commonoem.h"
#include "Protocol\AMIPostMgr.h"
#include "LogoLib.h"
#include "Mem.h"
#include "HiiLib.h"
#include "PwdLib.h"
#include "KeyMon.h"
#include "bootflow.h"
#include "commonoem.h"
#include "Core\EM\AMITSE\Inc\Variable.h"
#include "TcgPlatformSetupPolicy.h"

#if EFI_SPECIFICATION_VERSION>0x20000 && !defined(GUID_VARIABLE_DEFINITION)
    #include "Include\UefiHii.h"
    #include "Protocol/HiiDatabase.h"
    #include "Protocol/HiiString.h"
#else
  #include "Protocol/HII.h"
#endif

#if TPM_PASSWORD_AUTHENTICATION
#define TCG_PASSWORD_AUTHENTICATION_GUID \
        {0xB093BDD6, 0x2DE2, 0x4871, 0x87, 0x68, 0xEE, 0x1D, 0xA5, 0x72, 0x49, 0xB4 }
EFI_GUID    TcgPasswordAuthenticationGuid = TCG_PASSWORD_AUTHENTICATION_GUID;
#endif 

extern EFI_BOOT_SERVICES    *gBS;
extern EFI_SYSTEM_TABLE     *gST;
extern EFI_RUNTIME_SERVICES *gRT;


typedef struct
{   UINT16   VID;
    UINT16   DID;
} TCM_ID_STRUC;


TCM_ID_STRUC  TCMSupportedArray[NUMBER_OF_SUPPORTED_TCM_DEVICES]={
    {SUPPORTED_TCM_DEVICE_1_VID,SUPPORTED_TCM_DEVICE_1_DID},  //ZTEIC
    {SUPPORTED_TCM_DEVICE_2_VID,SUPPORTED_TCM_DEVICE_2_DID}  //ZTEIC2
};



//****************************************************************************************
//<AMI_PHDR_START>
//
// Procedure: TCGProcessConInAvailability
//
// Description: This is a replacement for the ProcessConInAvailability
//              hook in TSE, to provide password verification in the
//              TCG eModule.
//              This function is a hook called when TSE determines
//              that console is available. This function is available
//              as ELINK. In the generic implementation boot password
//              is prompted in this function.
//
//
// Input:       VOID
//
// Output:      BOOLEAN
//
// Modified:
//
// Referrals:
//
// Notes:
//<AMI_PHDR_END>
//****************************************************************************************
BOOLEAN TCGProcessConInAvailability (
     EFI_EVENT Event,
     VOID      *Context )
{
    CHAR16        *text = NULL;
    UINTN         NoOfRetries;
    UINT32        PasswordInstalled = AMI_PASSWORD_NONE;
    UINTN         Index;
    EFI_INPUT_KEY Key;
    BOOLEAN       bScreenUsed  = FALSE;
    UINTN         VariableSize = sizeof(UINT32);
    UINT32        VariableData;
    BOOLEAN       PasswordRequest = FALSE;
    EFI_GUID      TcgEfiGlobalVariableGuid = TCG_EFI_GLOBAL_VARIABLE_GUID;
    EFI_STATUS    Status;

    Status = gRT->GetVariable(
        L"AskPassword",
        &TcgEfiGlobalVariableGuid,
        NULL,
        &VariableSize,
        &VariableData
        );

    if ( VariableData == 0x58494d41 )   // "AMIX"
    {
        PasswordRequest = TRUE;
    }

    PasswordInstalled = PasswordCheckInstalled( );
    NoOfRetries       = 3;

    #if SETUP_USER_PASSWORD_POLICY

    if ((PasswordInstalled & AMI_PASSWORD_USER) || (PasswordRequest))
    {
    #else

    if ((PasswordInstalled & AMI_PASSWORD_ANY) || (PasswordRequest))
    {
        #endif

        bScreenUsed = TRUE;

        if ( AMI_PASSWORD_NONE ==
             CheckSystemPassword( AMI_PASSWORD_NONE, &NoOfRetries, NULL ))
        {
            while ( 1 )
            {
                //Patch
                //Ctl-Alt-Del is not recognized by core unless a
                //ReadKeyStroke is issued
                gBS->WaitForEvent( 1, &(gST->ConIn->WaitForKey), &Index );
                gST->ConIn->ReadKeyStroke( gST->ConIn, &Key );
            }
        }
    }

    return bScreenUsed;
}



//**********************************************************************
//<AMI_PHDR_START>
//
// Procedure:   AutoSupportType
//
// Description: verifies support for a TCM module on a platform
//
// Input:       NONE
//
// Output:      BOOLEAN
//
// Modified:
//
// Referrals:   
//
// Notes:       
//<AMI_PHDR_END>
//**********************************************************************
extern
BOOLEAN
__stdcall AutoSupportType ()
{
#if TCG_LEGACY == 0
  UINTN i=0;

   for(i=0;i<(sizeof(TCMSupportedArray)/sizeof(TCM_ID_STRUC));i++){
     if((TCMSupportedArray[i].VID == *(UINT16 *)(UINTN)(PORT_TPM_IOMEMBASE + 0xF00)) &&
        (TCMSupportedArray[i].DID == *(UINT16 *)(UINTN)(PORT_TPM_IOMEMBASE + 0xF02))){
         return TRUE;
      }
    }
#endif
    return FALSE;
}

//****************************************************************************************
//<AMI_PHDR_START>
//
// Procedure: PasswordAuthentication
//
// Description: This function is available as ELINK. In will create a Event for password 
//              authenication 
//
//
// Input:       VOID
//
// Output:     
// Notes:
//<AMI_PHDR_END>
//****************************************************************************************

VOID PasswordAuthentication( VOID )
{  
    EFI_STATUS    Status;
    VOID       *Registration;
    EFI_EVENT    Event;
        
    Status = gBS->CreateEvent (
                    EVT_NOTIFY_SIGNAL,
                    TPL_CALLBACK,
                    TCGProcessConInAvailability,
                    NULL,
                    &Event
                    );
    if(EFI_ERROR(Status)) {
        return ;
    }

    Status = gBS->RegisterProtocolNotify (
                    &TcgPasswordAuthenticationGuid,
                    Event,
                    &Registration
                    );
    if(EFI_ERROR(Status)) {
        return ;
    }
    
}

//**********************************************************************
//**********************************************************************
//**                                                                  **
//**        (C)Copyright 1985-2010, American Megatrends, Inc.         **
//**                                                                  **
//**                       All Rights Reserved.                       **
//**                                                                  **
//**     5555 Oakbrook Pkwy, Suite 200, Norcross, GA 30093            **
//**                                                                  **
//**                       Phone: (770)-246-8600                      **
//**                                                                  **
//**********************************************************************
//**********************************************************************
//**********************************************************************
