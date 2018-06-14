//**********************************************************************
//**********************************************************************
//**                                                                  **
//**        (C)Copyright 1985-2014, American Megatrends, Inc.         **
//**                                                                  **
//**                       All Rights Reserved.                       **
//**                                                                  **
//**        5555 Oakbrook Pkwy, Suite 200, Norcross, GA 30093         **
//**                                                                  **
//**                       Phone: (770)-246-8600                      **
//**                                                                  **
//**********************************************************************
//**********************************************************************
//**********************************************************************
// $Header: /Alaska/SOURCE/Modules/SecureFlashPkg/FlashUpdate/SecFlashUpdDxe.c 10    3/18/14 3:01p Alexp $
//
// $Revision: 10 $
//
// $Date: 3/18/14 3:01p $
//**********************************************************************
// Revision History
// ----------------
// $Log: /Alaska/SOURCE/Modules/SecureFlashPkg/FlashUpdate/SecFlashUpdDxe.c $
// 
// 10    3/18/14 3:01p Alexp
// set 2014 in file hdr & ftr
// 
// 9     5/09/13 10:37a Alexp
// EIP#123379 : Disabling FLASH_LOCK_EVENT_NOTIFY causes build error
// 
// 8     10/31/12 1:36p Alexp
// removed #ifdef for CAPSULE_SUPPORTbefore checks for capsule variable. 
// 
// 7     9/06/12 6:15p Alexp
// EIP#100418: Make SecureFlashPkg build independant from ReFlash-Support
// 
// 6     1/06/12 10:37a Alexp
// Streamlined the code for Setup.AutoFlash variable update if FlashUpdate
// is pending
// 
// 4     11/17/11 10:02a Alexp
// Use Core 4.6.5.2 provided name AMI_EVENT_FLASH_WRITE_LOCK as GUID
// define for Flash Lock event
// 
// 3     11/10/11 4:38p Alexp
// 1. UpdateAutoFlash() updates the AutoFlash Variable installed by
// ReFlash driver in Recovery/Flash Update flows
// 2. Issue FlashReadyToLock Event notification based on the Flash Update
// policy.
// 
// 2     7/20/11 7:16p Alexp
// remove dependency on Capsule module
// 
// 1     7/01/11 4:39p Alexp
// 
// 
//**********************************************************************
#include <Token.h>
#include <AmiDxeLib.h>
#include <AmiHobs.h>
#include <FlashUpd.h>

#include <Flash.h>
#if (defined ReFlash_SUPPORT) && (ReFlash_SUPPORT == 1)
#include "ReFlash.h"
#endif
#include "Capsule.h"

//
// Global variables
//
extern EFI_BOOT_SERVICES    *pBS;

#if FLASH_LOCK_EVENT_NOTIFY == 1

VOID     *gSbHobList     = NULL;
static EFI_GUID gHobListGuid = HOB_LIST_GUID;

// Core 4.6.5.2 sources GUID
#ifndef AMI_EVENT_FLASH_WRITE_LOCK
// {49D34AE7-1348-4551-8F71-467D8C0E4EF5}
#define AMI_EVENT_FLASH_WRITE_LOCK \
    { 0x49D34AE7, 0x9454, 0x4551, 0x8F, 0x71, 0x46, 0x7D, 0x8C, 0x0E, 0x4E, 0xF5 }
#endif

#define BDS_CONNECT_DRIVERS_PROTOCOL_GUID \
    { 0x3aa83745, 0x9454, 0x4f7a, 0xa7, 0xc0, 0x90, 0xdb, 0xd0, 0x2f, 0xab, 0x8e }

EFI_GUID  gBiosLockEnableEventGuid = AMI_EVENT_FLASH_WRITE_LOCK;
EFI_GUID  gBdsConnectDriversProtocolGuid = BDS_CONNECT_DRIVERS_PROTOCOL_GUID;

EFI_EVENT mSecureModEvent;
VOID      *mSecureModReg;
#endif //#if FLASH_LOCK_EVENT_NOTIFY == 1

//----------------------------------------------------------------------------
// Function definitions
//----------------------------------------------------------------------------

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure: ReadyToLockCallback
//
// Description: ready to Lock Flash part
//  Signal a event for ready to lock. 
//
// Input:   Event             - The event that triggered this notification function  
//          ParentImageHandle - Pointer to the notification functions context
//
// Output:  VOID
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
#if FLASH_LOCK_EVENT_NOTIFY == 1
VOID
ReadyToLockCallback (
  EFI_EVENT           Event,
  VOID                *ParentImageHandle
  )
{
    EFI_HANDLE  Handle = NULL;
    TRACE((-1,"\nSecure Fl Upd: FlashReadyToLock callback\n"));

// Signal Event.....
    pBS->InstallProtocolInterface (
        &Handle, &gBiosLockEnableEventGuid, EFI_NATIVE_INTERFACE,NULL
    );
    pBS->UninstallProtocolInterface (
        Handle,&gBiosLockEnableEventGuid, NULL
    );
    //
    //Kill the Event
	//
    pBS->CloseEvent(Event);
}

#endif //#if FLASH_LOCK_EVENT_NOTIFY == 1


//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   UpdateAutoFlash
//
// Description: This is the standard EFI driver entry point called for
//              Recovery flash module initlaization
// Input:       IN EFI_HANDLE ImageHandle - ImageHandle of the loaded driver
//              IN EFI_SYSTEM_TABLE SystemTable - Pointer to the System Table
//
// Output:      EFI_SUCCESS
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS UpdateAutoFlash ()
{
    EFI_STATUS              Status;
    UINT32                  Attributes;
    UINTN                   Size;
#if (defined ReFlash_SUPPORT) && (ReFlash_SUPPORT == 1)
    AUTOFLASH               AutoFlash;
    static EFI_GUID         guidReFlash     = RECOVERY_FORM_SET_GUID;
#endif //#if (defined ReFlash_SUPPORT) && (ReFlash_SUPPORT == 1)
    static EFI_GUID         FlashUpdGuid    = FLASH_UPDATE_GUID;
    static EFI_GUID         CapsuleBootModeGuid = EFI_CAPSULE_AMI_GUID;
    AMI_FLASH_UPDATE_BLOCK  FlashUpdDesc;

// Prep the FlashOp variable
    Attributes = 0;
    Size = sizeof(AMI_FLASH_UPDATE_BLOCK);
    Status = pRS->GetVariable( FLASH_UPDATE_VAR,&FlashUpdGuid,&Attributes,&Size, &FlashUpdDesc);
    if(!EFI_ERROR(Status))
    {
        // Erase Flash Var
        pRS->SetVariable (FLASH_UPDATE_VAR,&FlashUpdGuid,Attributes,0,NULL);
        // Clear pending Capsule Update Var
        // only if FlashOp is pending. We don't want to interfere with other types of Capsule Upd
        Size = 0;
        if(pRS->GetVariable(CAPSULE_UPDATE_VAR,&CapsuleBootModeGuid, &Attributes, &Size, NULL)==EFI_BUFFER_TOO_SMALL)
            pRS->SetVariable(CAPSULE_UPDATE_VAR,&CapsuleBootModeGuid, Attributes, 0, NULL);
#if (defined ReFlash_SUPPORT) && (ReFlash_SUPPORT == 1)
        // Update ReFlash parameters 
        Size = sizeof(AUTOFLASH);
        Status = pRS->GetVariable(L"Setup",&guidReFlash, &Attributes, &Size, &AutoFlash);   
        if(!EFI_ERROR(Status))
        {
        
            AutoFlash.UpdateNv = (FlashUpdDesc.ROMSection & (1<<FV_NV)) ? 1 : 0;
            AutoFlash.UpdateBb = (FlashUpdDesc.ROMSection & (1<<FV_BB)) ? 1 : 0;
            AutoFlash.UpdateMain=(FlashUpdDesc.ROMSection & (1<<FV_MAIN)) ? 1 : 0;
            // EC block
#if (defined EC_FIRMWARE_UPDATE_INTERFACE_SUPPORT) && (EC_FIRMWARE_UPDATE_INTERFACE_SUPPORT == 1)
            AutoFlash.UpdateEC  =(FlashUpdDesc.ROMSection & (1<<ROM_EC))   ? 1 : 0;
#endif       
            pRS->SetVariable(L"Setup",&guidReFlash, Attributes, sizeof(AUTOFLASH), &AutoFlash);
        }
#endif //#if (defined ReFlash_SUPPORT) && (ReFlash_SUPPORT == 1)
    }

    return EFI_SUCCESS;
}


//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   SecFlashUpdDxe_Init
//
// Description: Entry point of Flash Update Policy driver
//
// Input:       EFI_HANDLE           ImageHandle,
//              EFI_SYSTEM_TABLE     *SystemTable
//
// Output:      EFI_STATUS
//
// Modified:
//
// Referrals:
//
// Notes:
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS
SecFlashUpdDxe_Init (
    IN EFI_HANDLE         ImageHandle,
    IN EFI_SYSTEM_TABLE   *SystemTable
)
{
    EFI_STATUS  Status;

    InitAmiLib(ImageHandle, SystemTable);

    Status = UpdateAutoFlash();
///////////////////////////////////////////////////////////////////////////////
//
// Create Flash Lock event.
//
///////////////////////////////////////////////////////////////////////////////
#if FLASH_LOCK_EVENT_NOTIFY == 1
    // Get Hob List
    gSbHobList = GetEfiConfigurationTable(SystemTable, &gHobListGuid);
    if (!gSbHobList)
        return EFI_INVALID_PARAMETER;

// Locking SPI before BDS Connect on normal boot
    if (((EFI_HOB_HANDOFF_INFO_TABLE*)gSbHobList)->BootMode!=BOOT_IN_RECOVERY_MODE && 
        ((EFI_HOB_HANDOFF_INFO_TABLE*)gSbHobList)->BootMode!=BOOT_ON_FLASH_UPDATE
    ) 
        Status = RegisterProtocolCallback ( &gBdsConnectDriversProtocolGuid, \
                                            ReadyToLockCallback, \
                                            NULL, \
                                            &mSecureModEvent, \
                                            &mSecureModReg );
// Locking SPI after ReFlash(BDS) if in Recoovery/Flash Upd mode
    else
        Status = CreateReadyToBootEvent ( TPL_CALLBACK,
                                        ReadyToLockCallback,
                                        NULL,
                                        &mSecureModEvent);

    ASSERT_EFI_ERROR (Status);
#endif

    return Status;
}

//**********************************************************************
//**********************************************************************
//**                                                                  **
//**        (C)Copyright 1985-2014, American Megatrends, Inc.         **
//**                                                                  **
//**                       All Rights Reserved.                       **
//**                                                                  **
//**        5555 Oakbrook Pkwy, Suite 200, Norcross, GA 30093         **
//**                                                                  **
//**                       Phone: (770)-246-8600                      **
//**                                                                  **
//**********************************************************************
//**********************************************************************
