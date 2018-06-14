//**********************************************************************
//**********************************************************************
//**                                                                  **
//**        (C)Copyright 1985-2014, American Megatrends, Inc.         **
//**                                                                  **
//**                       All Rights Reserved.                       **
//**                                                                  **
//**      5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093        **
//**                                                                  **
//**                       Phone: (770)-246-8600                      **
//**                                                                  **
//**********************************************************************
//**********************************************************************
//**********************************************************************
// $Header: /Alaska/SOURCE/Modules/SecureFlashPkg/FlashUpdate/IsSecRecovery.c 18    10/29/14 5:11p Alexp $
//
// $Revision: 18 $
//
// $Date: 10/29/14 5:11p $
//**********************************************************************
// Revision History
// ----------------
// $Log: /Alaska/SOURCE/Modules/SecureFlashPkg/FlashUpdate/IsSecRecovery.c $
// 
// 18    10/29/14 5:11p Alexp
// GetFlashUpdateVar()  - set default value of CounterHi= -1
// for cases when MC variable is available only in pre-boot.
// 
// 15    3/18/14 3:02p Alexp
// year '2014' in file hdr & ftr
// 
// 14    8/12/13 4:36p Alexp
// fix ChangeBootModeAfterEndofMrc() to change BootMode and install PPI if
// CApsule Upd is pending 
// 
// 13    4/01/13 9:37a Alexp
// exclude capsule recovery code if FWCAPSULE_RECOVERY_SUPPORT is 0
// 
// 12    2/27/13 6:43p Alexp
// GetFlashUpdateVar() to check for AMI Capsule Variable 
// if Ami FwCapsule is pending and update boot mode to
// BOOT_ON_FLASH_UPDATE
// 
// 11    7/09/12 5:30p Alexp
//  IsFlashUpdateS3Capsule
//  Install Capsule Recovery Event whether by checking FlashUpd variable 
//  or if BOOT_ON_FLASH_UPDATE.  It may've already been set by Capsule PEI
// 
// 
// 9     6/01/12 10:44a Alexp
// EIP74625:New Capsule PPI required by latest Intel's MRC code
//     New PPI GUID; 
//     Capsule_2_0 Mailbox does not need extra Cap Hdr
// EIP90678: MonotonicCounter variable guid changed
//    Use AMI_GLOBAL_VARIABLE_GUID
// 
// 7     12/08/11 4:51p Alexp
// Change method of calling IsSecRecovery init routine.
// Replaced IsSecRecovery PEI with function call IsFlashUpdateRecovery
// from PeiCoreInitialize
// 
// 6     11/10/11 7:10p Alexp
// minor optimizations 
// 
// 5     11/03/11 6:41p Alexp
// Add provision to build file as .FFS with new function to install
// callback on gAmiPeiAfterMrcGuid event
// Update BootMode to BOOT_ON_FLASH_UPDATE if Capsule update is detected
// 
// 4     10/17/11 11:33a Alexp
// Replace old method to detect FlashUpd with single IsFlashUpdate() hook
// to be called from SbPei.c ->GetBootMode
// 
// 3     10/11/11 12:23p Alexp
// removed comments
// 
// 2     7/20/11 7:16p Alexp
// remove dependency on Capsule module
// 
// 1     7/01/11 4:39p Alexp
// 
// 
//<AMI_FHDR_START>
//----------------------------------------------------------------------
//
// Name: IsSecRecovery.c - PEI recovery services
//
// Description:   File contains hook to determine if BootMode needs to follow 
//                recovery path due to pending Flash Update
//
//----------------------------------------------------------------------
//<AMI_FHDR_END>
// Module specific Includes
#include "Efi.h"
#include "Pei.h"
#include "token.h"
#include <AmiPeiLib.h>
#include <Hob.h>
#include <Ppi\ReadOnlyVariable.h>
#include <FlashUpd.h>
#if  FWCAPSULE_RECOVERY_SUPPORT == 1
#include "AmiCertificate.h"
#include <Capsule.h>

// Definitions
static EFI_GUID gFWCapsuleGuid          = APTIO_FW_CAPSULE_GUID;
static EFI_GUID gEfiCapsuleVendorGuid   = EFI_CAPSULE_AMI_GUID;
#endif
static EFI_GUID gFlashUpdBootModeGuid   = EFI_PEI_BOOT_IN_FLASH_UPDATE_MODE_PEIM_PPI;
// PPI that are installed
static EFI_PEI_PPI_DESCRIPTOR mFlashUpdateModePpi[] =
  {
   (EFI_PEI_PPI_DESCRIPTOR_PPI | EFI_PEI_PPI_DESCRIPTOR_TERMINATE_LIST),
    &gFlashUpdBootModeGuid,
    NULL
};

static EFI_GUID gPeiReadOnlyVariablePpiGuid = EFI_PEI_READ_ONLY_VARIABLE_PPI_GUID;
static EFI_GUID gFlashUpdGuid               = FLASH_UPDATE_GUID;
// must be defined in AmiLib.h (Core 4.6.5.4 +)
#if defined(AMI_GLOBAL_VARIABLE_GUID)
static EFI_GUID guidVar                     = AMI_GLOBAL_VARIABLE_GUID;    
#else
static EFI_GUID guidVar                     = EFI_GLOBAL_VARIABLE; 
#endif

#if  FWCAPSULE_RECOVERY_SUPPORT == 1
///////////////////////////////////////////////////////
// {64C96700-6B4C-480C-A3E1-B8BDE8F602B2}
#define AMI_PEI_AFTER_MRC_GUID \
 {0x64c96700, 0x6b4c, 0x480c, 0xa3, 0xe1, 0xb8, 0xbd, 0xe8, 0xf6, 0x2, 0xb2}

static EFI_GUID gAmiPeiAfterMrcGuid         = AMI_PEI_AFTER_MRC_GUID;

EFI_STATUS ChangeBootModeAfterEndofMrc (
    IN EFI_PEI_SERVICES         **PeiServices,
    IN EFI_PEI_NOTIFY_DESCRIPTOR *NotifyDescriptor,
    IN VOID                     *InvokePpi
);

static EFI_PEI_NOTIFY_DESCRIPTOR EndOfMrcNotifyList[] = {
    { EFI_PEI_PPI_DESCRIPTOR_NOTIFY_CALLBACK | \
      EFI_PEI_PPI_DESCRIPTOR_TERMINATE_LIST, \
      &gAmiPeiAfterMrcGuid, ChangeBootModeAfterEndofMrc },
};
#endif
//--------------------------------------------------------------------------
//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   GetFlashUpdateVar
//
// Description:
//  This function checks if recovery flow is needed due to pending Flash Update
//
// Input:
//  PeiServices Pointer to the PEI services table
//
// Output:
//  TRUE - recovery is requested
//  FALSE - recovery is not requested
//
// Notes:
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
BOOLEAN 
GetFlashUpdateVar (
    EFI_PEI_SERVICES    **PeiServices,
    AMI_FLASH_UPDATE_BLOCK *FlashUpdDesc,
    UINT32                  *CounterHi
){
    EFI_STATUS      Status;
    UINTN           Size;
    EFI_PEI_READ_ONLY_VARIABLE_PPI  *ReadOnlyVariable;
#if  FWCAPSULE_RECOVERY_SUPPORT == 1
    EFI_PHYSICAL_ADDRESS          IoData;
    EFI_CAPSULE_HEADER           *CapsuleHeader;
    EFI_CAPSULE_BLOCK_DESCRIPTOR *pCapsuleMailboxPtr;
#endif
// Check FlashOp variable for Recovery Flash operation 
// Detect if we are in Flash Update mode and set some recovery global variables
// Read "FlashOp" Variable to update global RecoveryFileName, Size
    Status = (*PeiServices)->LocatePpi( PeiServices,
                                &gPeiReadOnlyVariablePpiGuid,
                                0,
                                NULL,
                                &ReadOnlyVariable );
    if(EFI_ERROR(Status)) 
        return FALSE;

    Size = sizeof(AMI_FLASH_UPDATE_BLOCK);
    Status = ReadOnlyVariable->GetVariable( PeiServices,
                                    FLASH_UPDATE_VAR,
                                    &gFlashUpdGuid,
                                    NULL,
                                    &Size,
                                    FlashUpdDesc );
    if (!EFI_ERROR(Status)) 
    {
        Size = sizeof(UINT32);
        Status = ReadOnlyVariable->GetVariable(PeiServices,
                                        L"MonotonicCounter", 
                                        &guidVar,
                                        NULL, 
                                        &Size,
                                        CounterHi);
        if (EFI_ERROR(Status) || FlashUpdDesc->MonotonicCounter == 0xffffffff)
            *CounterHi = 0xffffffff;

        return TRUE;
#if  FWCAPSULE_RECOVERY_SUPPORT == 1
    } else {
        Size=sizeof(EFI_PHYSICAL_ADDRESS);
        Status = ReadOnlyVariable->GetVariable( PeiServices,
                                        CAPSULE_UPDATE_VAR, &gEfiCapsuleVendorGuid, 
                                        NULL,
                                        &Size,
                                        &IoData );
        if (!EFI_ERROR(Status)) 
        {
            // verify the FW capsule is in memory. May first check if pCapsuleMailboxPtr == IoData
            pCapsuleMailboxPtr = (EFI_CAPSULE_BLOCK_DESCRIPTOR*)IoData;
            CapsuleHeader = (EFI_CAPSULE_HEADER*)pCapsuleMailboxPtr[0].DataBlock;
            //
            // Compare GUID with APTIO_FW_CAPSULE_GUID 
            //
            if (guidcmp (&CapsuleHeader->CapsuleGuid, &gFWCapsuleGuid)==0) {
                FlashUpdDesc->FlashOpType = FlCapsule;
                return TRUE;  
            }
        }
#endif
    }

    return FALSE;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   IsFlashUpdate
//
// Description:
//  This function returns proper BootMode if Flash Update mode is pending
//
// Input:
//  **PeiServices - Pointer to the PEI services table
//  *BootMode     - Pointer to a BootMode variable
//
// Output:
//  BOOLEAN 
//      TRUE - recovery is requested
//      FALSE - recovery is not requested
//  BootMode - updated BootMode value if TRUE
//
// Notes:
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
BOOLEAN 
IsFlashUpdate(
    EFI_PEI_SERVICES    **PeiServices,
    EFI_BOOT_MODE       *BootMode
){
    UINT32          CounterHi = 0;
    AMI_FLASH_UPDATE_BLOCK FlashUpdDesc;

    FlashUpdDesc.MonotonicCounter = 0;
    FlashUpdDesc.FlashOpType = FlDisabled;

//SetMode should have set FlashUpd var even if no MC var detected.
// MC check should fail Recovery
    if(/**BootMode != BOOT_IN_RECOVERY_MODE && */
        GetFlashUpdateVar(PeiServices, &FlashUpdDesc, &CounterHi) &&
        CounterHi==(UINT32)FlashUpdDesc.MonotonicCounter)
    {
        if(FlashUpdDesc.FlashOpType == FlRecovery)
        {
            *BootMode = BOOT_IN_RECOVERY_MODE;
            return TRUE;
        }
        if(FlashUpdDesc.FlashOpType == FlCapsule/* && *BootMode == BOOT_ON_S3_RESUME*/)
        {
            *BootMode = BOOT_ON_FLASH_UPDATE;
            return TRUE;  
        }
    }
    return FALSE;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   IsFlashUpdateRecovery
//
// Description:
//  This function checks if recovery flow is needed due to pending Flash Update
//
// Input:
//  PeiServices Pointer to the PEI services table
//
// Output:
//  TRUE - recovery is requested
//  FALSE - recovery is not requested
//
// Notes:
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
BOOLEAN 
IsFlashUpdateRecovery (
    EFI_PEI_SERVICES    **PeiServices
){
    EFI_BOOT_MODE       BootMode;
    if(IsFlashUpdate(PeiServices, &BootMode) && BootMode == BOOT_IN_RECOVERY_MODE)
        return TRUE;
    return FALSE;
}

#if  FWCAPSULE_RECOVERY_SUPPORT == 1

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:   ChangeBootModeAfterEndofMrc
//
// Description: Change BootMode to BOOT_ON_FLASH_UPDATE if Capsule update is pending
//
// Input:       PeiServices      - Pointer to the PEI services table
//              NotifyDescriptor - Pointer to the descriptor for the
//                                 notification event.
//              InvokePpi        - Pointer to the PPI that was installed
//
// Output:      EFI_STATUS
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS ChangeBootModeAfterEndofMrc (
    IN EFI_PEI_SERVICES             **PeiServices,
    IN EFI_PEI_NOTIFY_DESCRIPTOR    *NotifyDescriptor,
    IN VOID                         *InvokePpi )
{
    EFI_STATUS                      Status;
    EFI_BOOT_MODE        BootMode;

    Status = (*PeiServices)->GetBootMode( PeiServices, &BootMode );
//    if (!EFI_ERROR(Status) &&  (BootMode != BOOT_IN_RECOVERY_MODE))
// BOOT_ON_FLASH_UPDATE may already be set by Capsule PEI
    if(!EFI_ERROR(Status) && (BootMode == BOOT_ON_S3_RESUME || BootMode == BOOT_ON_FLASH_UPDATE))
    {
    // Change the Boot Mode to Recovery from S3_RESUME/BOOT_ON_FLASH_UPDATE
       if (IsFlashUpdate(PeiServices, &BootMode) && BootMode == BOOT_ON_FLASH_UPDATE)
           (*PeiServices)->SetBootMode(PeiServices, BootMode);
    }
    //install Flash Update Boot Mode PPI
    if(BootMode == BOOT_ON_FLASH_UPDATE)
        (*PeiServices)->InstallPpi( PeiServices, mFlashUpdateModePpi);

    return EFI_SUCCESS;
}
#endif
//<AMI_PHDR_START>
//----------------------------------------------------------------------
//
// Procedure:    IsFlashUpdateCapsuleInit
//
// Description:    Installs callback to ChangeBootModeAfterEndofMrc
//
//---------------------------------------------------------------------- 
//<AMI_PHDR_END>
EFI_STATUS
IsFlashUpdateCapsuleInit (
    IN    EFI_FFS_FILE_HEADER        *FfsHeader,
    IN    EFI_PEI_SERVICES        **PeiServices
)
{
#if  FWCAPSULE_RECOVERY_SUPPORT == 1
    return (*PeiServices)->NotifyPpi( PeiServices, EndOfMrcNotifyList);
#else 
    return EFI_SUCCESS;
#endif

}
//**********************************************************************
//**********************************************************************
//**                                                                  **
//**        (C)Copyright 1985-2014, American Megatrends, Inc.         **
//**                                                                  **
//**                       All Rights Reserved.                       **
//**                                                                  **
//**      5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093        **
//**                                                                  **
//**                       Phone: (770)-246-8600                      **
//**                                                                  **
//**********************************************************************
//**********************************************************************
