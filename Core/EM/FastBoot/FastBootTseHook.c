//*************************************************************************
//*************************************************************************
//**                                                                     **
//**        (C)Copyright 1985-2010, American Megatrends, Inc.            **
//**                                                                     **
//**                       All Rights Reserved.                          **
//**                                                                     **
//**      5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093           **
//**                                                                     **
//**                       Phone: (770)-246-8600                         **
//**                                                                     **
//*************************************************************************
//*************************************************************************

//*************************************************************************
// $Header: /Alaska/SOURCE/Modules/PTT/FastBootTseHook.c 8     7/17/13 2:59a Simonchen $
//
// $Revision: 8 $
//
// $Date: 7/17/13 2:59a $
//*************************************************************************
// Revision History
// ----------------
// $Log: /Alaska/SOURCE/Modules/PTT/FastBootTseHook.c $
// 
// 8     7/17/13 2:59a Simonchen
// [TAG]  		EIP125309
// [Category]  	New Feature
// [Description]  	Add function to make sure before boot to OS, BIOS is in
// fastboot path.
// [Files]  		FastBoot.sdl
// FastBootTseHook.c
// FastBoot.c
// FastBoot.h
// 
// 7     8/04/12 5:38a Bibbyyeh
// Fix logic defect in the if statement in procedure
// "FastBootCheckForKey".
// 
// 6     6/01/12 6:56a Bibbyyeh
// [TAG]           EIP90455
// [Category]      New Feature
// [Description]   PTT improvement - fastboot policy protocol for dynamic
// control fast boot behavior.
// [Files]         FastBoot.c FastBoot.sdl FastBoot.sd FastBoot.uni
// FastBootRuntime.c FastBootTseHook.c FastBootProtocol.h FastBoot.h
// 
// 5     5/30/12 3:38a Bibbyyeh
// [TAG]           EIP90874
// [Category]      Improvement
// [Description]   Display "Press the DEL or ESC key to enter setup"
// message in fastboot path.
// [Files]         FastBootTseHook.c
// 
// 4     9/08/11 5:26a Bibbyyeh
// [TAG]           EIP68329
// [Category]      Bug Fix
// [Severity]      Important
// [Symptom]       OS can't back to desktop correctly after resumed from
// S3. 
// [RootCause]     TSEIDEPasswordFreezeDevices is skipped in fastboot path
// if SKIP_TSE_HANDSHAKE is enabled. 
// [Solution]      Call TSEIDEPasswordFreezeDevices after ReadyToBoot
// Event in fastboot path.
// [Files]         FastBoot.c FastBootProtocol.h FastBootTseHook.c
// 
// 3     7/07/11 10:38a Bibbyyeh
// [TAG]           EIP63924
// [Category]      Improvement
// [Description]   
// 1. Add elink for FastBoot mode change, default checking rule is check
// post hotkey.
// 2. Timer call back for check hotkey is not necessary. Create a protocol
// for calling checkforkey in TSE.
// 3. Since EIP68383 improve the performance of ps2 keyboard, we don't
// need to exchange the initial order of ConIn/ConOut for getting more
// time to detect hotkey.
// [Files]         FastBoot.sdl FastBoot.mak FastBoot.c FastBootTseHook.c
// FastBoot.h FastBootProtocol.h
// 
// 2     3/11/11 10:01p Bibbyyeh
// [TAG]		EIP54993
// [Category]	Improvement
// [Description]
// 1.Sync with Fastboot_10
// 2.Remove token "SAVE_LAST_BOOT_DEVICE_CHECKSUM"
// 3.Add token "CALL_DISPATCHER_AGAIN_IN_FASTBOOT"
// 4.Use SimpleText protocol to detect mode change hotkey instead of
// pBS->ConIn.
// 5.Simplify the code about "AMILEGACY16_FASTBOOT_SOLUTION".
// 6.Fixed a bug that SATA device can't be found if keep TSE execution on
// fastboot path.
// [Files]		PPT.cif FastBoot.sdl FastBootRuntime.c FastBootTseHook.c
// FastBoot.c FastBoot.h FastBoot.sd FastBootProtocol.cif
// FastBootProtocol.h FastBootSMI.cif FastBootSMI.sdl FastBootSMI.c
// FastBootSMI.dxs FastBootSMI.mak
// 
// 1     10/12/10 9:04a Bibbyyeh
// Initial check in
// 
// 
//*************************************************************************
//<AMI_FHDR_START>
//
// Name:  FastBootTseHook.c
//
//  Description:
//  Implementation of suppress of TSE "Press DEL..." message
//
//<AMI_FHDR_END>
//*************************************************************************
//============================================================================
// Includes
//============================================================================

#include <Efi.h>
#include <Setup.h>
#include <Protocol/FastBootProtocol.h>
#include "FastBoot.h"
#include "AMITSEStrTokens.h"
#if FASTBOOT_NEED_RESTART
#include <AmiDxeLib.h>
#endif
//============================================================================
// Define
//============================================================================
#define	BOOT_FLOW_CONDITION_NORMAL	0

#if FASTBOOT_NEED_RESTART
static EFI_GUID FastbootRestartGuid = FAST_BOOT_RESTART_GUID;
static EFI_GUID FastbootRestartCountGuid = FAST_BOOT_RESTART_COUNT_GUID;
#endif

//============================================================================
// External Golbal Variable Declaration
//============================================================================
extern EFI_RUNTIME_SERVICES *gRT;
extern EFI_BOOT_SERVICES 	*gBS;
extern UINT32 gBootFlow;
extern BOOLEAN gEnterSetup;
extern EFI_EVENT gKeyTimer;
extern CHAR16 *HiiGetString( VOID* handle, UINT16 token );
extern EFI_HII_HANDLE  gHiiHandle;
//============================================================================
// External Function Definitions
//============================================================================
EFI_STATUS PostManagerDisplayPostMessage( CHAR16 *message );
BOOLEAN ProcessConInAvailability(VOID);
VOID BbsBoot(VOID);
VOID TSEIDEPasswordFreezeDevices(); 	//(EIP68329)+
VOID CheckForKeyHook( EFI_EVENT Event, VOID *Context );
EFI_STATUS TimerStopTimer( EFI_EVENT *Event );    
//============================================================================
// Golbal Variable Declaration
//============================================================================
FAST_BOOT_POLICY    *gFastBootPolicy;
FAST_BOOT_TSE_PROTOCOL gFastBootTseProtocol = {
    FastBootCheckForKey,
    FastBootStopCheckForKeyTimer,
    TSEIDEPasswordFreezeDevices         //(EIP68329)++
};
//============================================================================
// Function Definitions
//============================================================================
										//(EIP63924+)>
//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	FastBootCheckForKey
//
// Description:	This function check TSE variable,gEnterSetup and gBootFlow.
//              
// Input:		
//          BOOLEAN *EnterSetup
//          UINT32  *BootFlow
// Output:		
//          EFI_SUCCESS - Bootflow is changed or EnterSetup if true
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS FastBootCheckForKey( 
    IN  BOOLEAN *EnterSetup,
    IN  UINT32  *BootFlow)
{
    CheckForKeyHook( (EFI_EVENT)NULL, NULL );

    *EnterSetup = gEnterSetup;
    *BootFlow = gBootFlow;
    
    if ((gEnterSetup) || (gBootFlow != BOOT_FLOW_CONDITION_NORMAL)){
        return EFI_SUCCESS;
    }
    else { 
    	return EFI_NOT_READY;
    }
}
//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	FastBootStopCheckForKeyTimer
//
// Description:	This function stop the timer of CheckForKey callback
//
// Input:		None
//
// Output:		EFI_STATUS
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>                                        
EFI_STATUS FastBootStopCheckForKeyTimer()
{
    return TimerStopTimer(&gKeyTimer);
}
//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   FastBootMinisetupDriverEntryHook
//
// Description: Function that will be called when enter TSE Dxe entry
//
// Input:		
//  None
//
// Output:
//  FALSE - as per TSE requirement, that no password was entered
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID FastBootMinisetupDriverEntryHook(VOID)
{
    EFI_HANDLE Handle = NULL;			
    EFI_GUID   FastBootTseGuid = FAST_BOOT_TSE_PROTOCOL_GUID; 
    EFI_GUID   FastBootPolicyGuid = FAST_BOOT_POLICY_PROTOCOL_GUID;
    EFI_STATUS Status;
    
    gBS->InstallProtocolInterface(&Handle,
                              &FastBootTseGuid,
                              EFI_NATIVE_INTERFACE,
                              &gFastBootTseProtocol);

    Status = gBS->LocateProtocol(&FastBootPolicyGuid,NULL,&gFastBootPolicy);
        
} 
										//<(EIP63924+)
#if FASTBOOT_NEED_RESTART										
VOID InitialRebootCount(VOID)
{
	EFI_STATUS Status;
	UINTN RebootFlag = 1;
	UINTN RebootFlagSize = sizeof(RebootFlag);
	UINTN ClearCount = 0;
	UINTN ClearCountSize = sizeof(ClearCount); 
	Status = gRT->SetVariable(FAST_BOOT_RESTART_COUNT, 
				&FastbootRestartCountGuid, 
				EFI_VARIABLE_NON_VOLATILE |
				EFI_VARIABLE_BOOTSERVICE_ACCESS |
				EFI_VARIABLE_RUNTIME_ACCESS,
				ClearCountSize,
				&ClearCount);

	Status = gRT->SetVariable(FAST_BOOT_RESTART, 
				&FastbootRestartGuid, 
				EFI_VARIABLE_NON_VOLATILE |
				EFI_VARIABLE_BOOTSERVICE_ACCESS |
				EFI_VARIABLE_RUNTIME_ACCESS,
				RebootFlagSize,
				&RebootFlag);

}
#endif
//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   FastBootConInAvailHook
//
// Description: Function that will be called instead of generic TSE callback
//              on Console Input device is installed event
//
// Input:		
//  None
//
// Output:
//  FALSE - as per TSE requirement, that no password was entered
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
BOOLEAN FastBootConInAvailHook(VOID)
{
//	    EFI_STATUS Status;
//	    UINTN Size = sizeof(SETUP_DATA);
//	    static EFI_GUID SetupVariableGuid = SETUP_GUID;
//	    SETUP_DATA SetupData;
//	
//		Status = gRT->GetVariable(L"Setup", &SetupVariableGuid, NULL, &Size, &SetupData);
//		if (EFI_ERROR(Status) || SetupData.FastBoot == 0 || ALLOW_CHECKING_PASSWORD) 
//	        return ProcessConInAvailability();

	if(gFastBootPolicy->FastBootEnable == 0 || gFastBootPolicy->CheckPassword == 1) 
        return ProcessConInAvailability();

#if SETUP_PRINT_ENTER_SETUP_MSG 
{
        CHAR16 *text = NULL;
        text = HiiGetString( gHiiHandle, STRING_TOKEN(STR_DEL_ENTER_SETUP) );
        if ( text != NULL )
            PostManagerDisplayPostMessage(text);
        gBS->FreePool(text);
}
#endif

    return FALSE;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   FastBootBbsBootHook
//
// Description: Function that will be called instead of generic TSE callback
//              on BBS popup boot path
//
// Input:		
//  None
//
// Output:
//  None
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID FastBootBbsBootHook(VOID)
{
    static EFI_GUID FastBootVariableGuid = FAST_BOOT_VARIABLE_GUID;
    EFI_STATUS Status;
    UINT32     BbsPopupCalled = 0x55aa55aa;
    Status = gRT->SetVariable(L"BbsPopupCalled", 
                              &FastBootVariableGuid, 
                              EFI_VARIABLE_BOOTSERVICE_ACCESS,
                              sizeof(BbsPopupCalled),
                              &BbsPopupCalled);
    BbsBoot();
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   FastBootLaunch
//
// Description: Function that will be called instead of generic TSE callback
//              on fast boot path
//
// Input:		
//  None
//
// Output:
//  None
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
#if OVERRIDE_FastBootLaunch
EFI_STATUS FastBootLaunch()
{
	EFI_STATUS Status = EFI_UNSUPPORTED;
	AMI_FAST_BOOT_PROTOCOL * FastBootProtocol = NULL;

	// do the Fast Boot
	if (!EFI_ERROR(gBS->LocateProtocol(&AmiFastBootProtocolGuid, NULL, &FastBootProtocol)))
		Status = FastBootProtocol->Launch();

	// If gFastBootProtocolGuid protocol not found or FastBoot Failed. return
	return Status;
}
#endif
//*************************************************************************
//*************************************************************************
//**                                                                     **
//**        (C)Copyright 1985-2010, American Megatrends, Inc.            **
//**                                                                     **
//**                       All Rights Reserved.                          **
//**                                                                     **
//**      5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093           **
//**                                                                     **
//**                       Phone: (770)-246-8600                         **
//**                                                                     **
//*************************************************************************
//*************************************************************************
