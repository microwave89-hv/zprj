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
// $Header: /Alaska/SOURCE/Modules/SMBIOS/SmbiosPeim/SmbiosPei.c 1     5/27/14 1:44p Davidd $
//
// $Revision: 1 $
//
// $Date: 5/27/14 1:44p $
//**********************************************************************
// Revision History
// ----------------
// $Log: /Alaska/SOURCE/Modules/SMBIOS/SmbiosPeim/SmbiosPei.c $
// 
// 1     5/27/14 1:44p Davidd
// [TAG]  		EIP103526
// [Category]  	Improvement
// [Files]  		SmbiosPeim.cif
// SmbiosPeim.sdl
// SmbiosPeim.mak
// SmbiosPeim.dxs
// SmbiosPei.c
// 
// 1     4/29/14 4:44p Davidd
// [TAG]  		EIP103526
// [Category]  	Improvement
// [Description]  	We should update Wake-up Type in SMBIOS type 1
// dynamically
// [Files]  		Core\EM\SMBios\SmbiosPeim\SmbiosPeim.cif
// Core\EM\SMBios\SmbiosPeim\SmbiosPeim.sdl
// Core\EM\SMBios\SmbiosPeim\SmbiosPeim.mak
// Core\EM\SMBios\SmbiosPeim\SmbiosPeim.dxs
// Core\EM\SMBios\SmbiosPeim\SmbiosPei.c
// 
//**********************************************************************
//<AMI_FHDR_START>
//
// Name:  SmbiosPei.c
//
// Description:	
//
//<AMI_FHDR_END>
//**********************************************************************

#include <AmiPeiLib.h>
#include <Ppi\ReadOnlyVariable2.h>
#include "Core\Ppi\MemoryDiscovered.h"

extern VOID		OemRuntimeShadowRamWrite(IN BOOLEAN Enable);
extern UINT8	getWakeupTypeForSmbios(VOID);

EFI_STATUS
SmbiosAfterInitMemory(
  IN EFI_PEI_SERVICES           **PeiServices,
  IN EFI_PEI_NOTIFY_DESCRIPTOR  *NotifyDescriptor,
  IN VOID                       *NullPpi
);

static EFI_GUID gPeiPermanentMemInstalledPpiGuid = PEI_PERMANENT_MEMORY_INSTALLED_PPI_GUID;

static EFI_PEI_NOTIFY_DESCRIPTOR SmbiosPeiNotify[] =
{
    {
        EFI_PEI_PPI_DESCRIPTOR_NOTIFY_CALLBACK | EFI_PEI_PPI_DESCRIPTOR_TERMINATE_LIST,
        &gPeiPermanentMemInstalledPpiGuid,
        SmbiosAfterInitMemory
    }
};

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure: UpdateSmbiosWakeupType
//
// Description: Detect and update SMBIOS Type 1 structure "Wake-up Type"
//              data field
//
// Input:IN EFI_PEI_SERVICES  **PeiServices,
//
// Output: Updated SMBIOS Type 1 "Wake-up Type"
//
// Notes:
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID
UpdateSmbiosWakeupType(
    IN EFI_PEI_SERVICES **PeiServices
)
{
    EFI_STATUS                          Status;
    EFI_PEI_READ_ONLY_VARIABLE2_PPI     *ReadOnlyVariable;
    EFI_GUID                            EfiPeiReadOnlyVariablePpiGuid = \
                                        {0x2ab86ef5, 0xecb5, 0x4134, {0xb5, 0x56, 0x38, 0x54, 0xca, 0x1f, 0xe1, 0xb4}};
    EFI_GUID                            EfiSmbiosNvramGuid = \
                                        {0x4b3082a3, 0x80c6, 0x4d7e, {0x9c, 0xd0, 0x58, 0x39, 0x17, 0x26, 0x5d, 0xf1}};
    UINTN                               DataSize = 4;
    UINT32                              WakeupTypePtr;

    Status = (*PeiServices)->LocatePpi(
                                        PeiServices,
                                        &EfiPeiReadOnlyVariablePpiGuid,
                                        0,
                                        NULL,
                                        &ReadOnlyVariable);
    ASSERT_PEI_ERROR(PeiServices, Status);

    if (Status == EFI_SUCCESS){
        Status = ReadOnlyVariable->GetVariable(
                                        ReadOnlyVariable,
                                        L"WakeUpType",
                                        &EfiSmbiosNvramGuid,
                                        NULL,
                                        &DataSize,
                                        &WakeupTypePtr);
        if (Status == EFI_SUCCESS) {
            if (WakeupTypePtr > 0xf0000) {
                *(UINT8*)WakeupTypePtr = getWakeupTypeForSmbios();
            }
            else {
                OemRuntimeShadowRamWrite(TRUE);
                *(UINT8*)WakeupTypePtr = getWakeupTypeForSmbios();
                OemRuntimeShadowRamWrite(FALSE);
            }
        }
    }
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure: SmbiosAfterInitMemory
//
// Description:
//
// Input: IN EFI_PEI_SERVICES           **PeiServices,
//        IN EFI_PEI_NOTIFY_DESCRIPTOR  *NotifyDescriptor,
//        IN VOID                       *NullPpi
//
// Output:
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS
SmbiosAfterInitMemory(
  IN EFI_PEI_SERVICES           **PeiServices,
  IN EFI_PEI_NOTIFY_DESCRIPTOR  *NotifyDescriptor,
  IN VOID                       *NullPpi
)
{
    EFI_STATUS Status;
    EFI_BOOT_MODE BootMode;

    // Determine boot mode
    Status = (*PeiServices)->GetBootMode(PeiServices, &BootMode);
    ASSERT_PEI_ERROR(PeiServices, Status);

    if (BootMode == BOOT_ON_S3_RESUME) {
        UpdateSmbiosWakeupType(PeiServices);
    }

    return EFI_SUCCESS;
}

EFI_STATUS
SmbiosPeiEntryPoint(
	IN EFI_FFS_FILE_HEADER       *FfsHeader,
  	IN EFI_PEI_SERVICES          **PeiServices
)
{
    EFI_STATUS Status;

    // Set the Smbios Notify PPI
    Status = (*PeiServices)->NotifyPpi(PeiServices, SmbiosPeiNotify);
    ASSERT_PEI_ERROR(PeiServices, Status);

	return EFI_SUCCESS;
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