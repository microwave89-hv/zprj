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

//**********************************************************************
// $Header: /Alaska/SOURCE/Modules/PEI Ram Boot/PeiRamBootDxe.c 12    8/28/15 3:52a Tristinchou $
//
// $Revision: 12 $
//
// $Date: 8/28/15 3:52a $
//**********************************************************************
// Revision History
// ----------------
// $Log: /Alaska/SOURCE/Modules/PEI Ram Boot/PeiRamBootDxe.c $
// 
// 12    8/28/15 3:52a Tristinchou
// [TAG]  		EIP235157
// [Category]  	Improvement
// [Description]  	Security vulnerability - PeiRamBoot: Should leave cold
// boot optimization only
// 
// 11    5/05/14 5:03a Calvinchen
// [TAG]  		EIP166551
// [Category]  	Spec Update
// [Severity]  	Important
// [Description]  	Runtime attribute set for the some of the variable used
// by PEI Ram Boot driver and needs to be reviewed
// [Files]  		PeiRamBootDxe.c
// PeiRamBootOfbd.c
// PeiRamBoot.chm
// PeiRamBoot.cif
// 
// 10    1/16/13 4:54a Calvinchen
// [TAG]  		EIP108319
// [Category]  	Bug Fix
// [Severity]  	Minor
// [Symptom]  	When we enable PEI RAM BOOT module and set the token
// ¡§PEI_RAM_S3_SUPPOT¡¨ to 0, smbios will not be writable, system will
// hang up when writing smbios under DOS using DMI tool.
// [RootCause]  	Don't Restore the Base Address of Firmware Volume Block
// Protocol from RAM to ROM.
// [Solution]  	Restore the Base Address of Firmware Volume Block Protocol
// from RAM to ROM.
// [Files]  		PeiRamBootDxe.c
// 
// 9     8/08/12 4:53a Calvinchen
// 1. Changed for ReportFv2.c by Artem's suggestion.
// 2. Fixed System hangs if Memory Mapping Changed with warm boot.
// 
// 8     5/04/12 5:03a Calvinchen
// [TAG]  		EIP88796
// [Category]  	Bug Fix
// [Severity]  	Minor
// [Symptom]  	(JP0005-Q208)When define more than two FV which has the
// same CUSTOM_SIZE, GetPhysicalAddress() returns invalid value.
// [RootCause]  	Coding mistake.
// [Solution]  	(JP0005-Q208)When define more than two FV which has the
// same CUSTOM_SIZE, GetPhysicalAddress() returns invalid value.
// [Files]  		PeiRamBootDxe.c
// PeiRamBoot.chm
// PeiRamBoot.cif
// 
// 7     2/23/12 6:35a Calvinchen
// [TAG]  		EIP82264
// [Category]  	Improvement
// [Description]  	Need to do cold boot to get the correct data in rom
// hole when changing data in rom hole.
// [Files]  		PeiRamBoot.sdl
// PeiRamBoot.mak
// PeiRamBoot.h
// PeiRamBoot.c
// PeiRamBootDxe.c
// PeiRamBoot.chm
// PeiRamBoot.cif
// 
// 6     5/27/11 7:22a Calvinchen
// Delete HobRomImage Variable if Recovery mode.
// 
// 5     4/22/11 1:28a Calvinchen
// 
// 4     3/22/11 7:52a Calvinchen
// [TAG]  		EIP56322
// [Category]  	Bug Fix
// [Severity]  	Normal
// [Symptom]  	System hangs after changing TPM settings in SETUP.
// [RootCause]  	System Memory Mappings are changed with warm boot.
// [Solution]  	BIOS always go cold boot path if system memory mappings
// are changed
// [Files]  		PeiRamBoot.sdl
// PeiRamBoot.mak
// PeiRamBoot.dxs
// PeiRamBoot.h
// PeiRamBoot.c
// PeiRamBootHook.c
// PeiRamBootDxe.c
// PeiRamBootOfbd.c
// PeiRamBoot.chm
// PeiRamBoot.cif
// 
// 3     12/14/10 2:25a Calvinchen
// Improvement : 
// 1. Added an eLink "PeiRamBootList" for fast warm boot support
// (PEI_RAM_BOOT_S3_SUPPORT = 1). If system boots in warm boot state, BIOS
// directly boot to previous copied ROM image in RAM to save time of
// copying ROM. 
// 2. Added "PEI_RAM_BOOT_S3_SUPPORT" = "2" for saving runtime memory, it
// only keep necessary PEIM FFS in runtime memory for S3 resume
// improvement. 
// 
// 2     12/02/10 6:18a Calvinchen
// Bug Fixed : Fixed Update SMBIOS Structures failed with DMI Utility.
// 
// 1     10/27/10 2:48a Calvinchen
// Initial Check-in.
// 
//
//**********************************************************************
//<AMI_FHDR_START>
//
// Name: PeiRamBootDxe.c
//
// Description: PEI RAM BOOT DXE driver.
//
//<AMI_FHDR_END>
//**********************************************************************
//----------------------------------------------------------------------------
// Includes
// Statements that include other files
#include <AmiDxeLib.h>
#include <AmiCspLib.h>
#include <PeiRamBoot.h>
#include <Protocol\FirmwareVolumeBlock.h>

//----------------------------------------------------------------------------
// Function Externs

//----------------------------------------------------------------------------
// Local prototypes
typedef struct {
  UINTN                       Base;
  UINTN                       Length;
} LBA_CACHE;

typedef struct {
  MEMMAP_DEVICE_PATH          MemMapDevPath;
  EFI_DEVICE_PATH_PROTOCOL    EndDevPath;
} FV_DEVICE_PATH;


typedef struct {
  UINTN                                 Signature;
  EFI_HANDLE                            Handle;
  FV_DEVICE_PATH                        DevicePath;
  EFI_FIRMWARE_VOLUME_BLOCK_PROTOCOL    FwVolBlockInstance;
  UINTN                                 NumBlocks;
  LBA_CACHE                             *LbaCache;
  UINT32                                FvbAttributes;
  EFI_PHYSICAL_ADDRESS                  BaseAddress;
} EFI_FW_VOL_BLOCK_DEVICE;

#define FVB_DEVICE_SIGNATURE       EFI_SIGNATURE_32('_','F','V','B')

#ifndef _CR
#define _CR(Record, TYPE, Field)  ((TYPE *) ((CHAR8 *) (Record) - (CHAR8 *) &(((TYPE *) 0)->Field)))
#endif
#ifndef CR
#define CR(Record, TYPE, Field, Signature)  _CR (Record, TYPE, Field)
#endif
#ifndef EFI_FVB_MEMORY_MAPPED
#define EFI_FVB_MEMORY_MAPPED EFI_FVB2_MEMORY_MAPPED
#endif

#define FVB_DEVICE_FROM_THIS(a) \
  CR(a, EFI_FW_VOL_BLOCK_DEVICE, FwVolBlockInstance, FVB_DEVICE_SIGNATURE)

EFI_GUID gEfiFirmwareVolumeBlockProtocolGuid = FW_VOLUME_BLOCK_PROTOCOL_GUID;

//----------------------------------------------------------------------------
// Local Variables
//----------------------------------------------------------------------------
// Function Definitions
//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:   DeleteHobRomImageVariable
//
// Description: Delete HobRomImage Variable event.
//
// Input:       None.
//
// Output:      None.
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS
DeleteHobRomImageVariable  (
    IN EFI_EVENT            Event,
    IN VOID                 *ParentImageHandle
)
{
    EFI_GUID            RomImageAddressGuid = ROM_IMAGE_ADDRESS_GUID;
    
    pRS->SetVariable ( L"HobRomImage", 
                       &RomImageAddressGuid, \
                       EFI_VARIABLE_NON_VOLATILE | \
                       EFI_VARIABLE_BOOTSERVICE_ACCESS, \
                       0, \
                       ParentImageHandle );
    return EFI_SUCCESS;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:   PeiRamBootDxeInit
//
// Description: DXE Entry Point for PeiRamBoot Driver.
//
// Input:       EFI_HANDLE          - ImageHandle
//              EFI_SYSTEM_TABLE*   - SystemTable
//
// Output:      EFI_STATUS
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS
PeiRamBootDxeInit (
  IN EFI_HANDLE             ImageHandle,
  IN EFI_SYSTEM_TABLE       *SystemTable
)
{
    EFI_GUID                GuidHob = HOB_LIST_GUID;
    EFI_STATUS              Status;
    EFI_GUID                RomImageHobGuid = ROM_IMAGE_MEMORY_HOB_GUID;
    EFI_GUID                RomImageAddressGuid = ROM_IMAGE_ADDRESS_GUID;
    UINTN                   VarSize = 0, NumHandles;
    UINT8                   i, j;
    EFI_PHYSICAL_ADDRESS    HobRomImageAddress = 0;
    VOID                    *p =  NULL;
    EFI_HOB_FIRMWARE_VOLUME	*FvHob =  NULL;
    HOB_ROM_IMAGE           *HobRomImage;
	EFI_HANDLE				*HandleBuffer;
    EFI_FW_VOL_BLOCK_DEVICE *FvbDevice;
    EFI_FIRMWARE_VOLUME_BLOCK_PROTOCOL  *FvBlock;
    EFI_EVENT               EvtSetupChange = NULL;
    VOID                    *RgnSetupChange = NULL;
    EFI_GUID                AmitseSetupNvramUpdateGuid = \
    {0xd84beff0, 0x159a, 0x4b60, 0x9a, 0xb9, 0xac, 0x5c, 0x47, 0x4b, 0xd3, 0xb1};

    InitAmiLib(ImageHandle, SystemTable);
    
    // Get RamBoot Informatoin from HOB.    
    HobRomImage = (HOB_ROM_IMAGE*)GetEfiConfigurationTable (pST, &GuidHob);
    Status = FindNextHobByGuid (&RomImageHobGuid, (VOID**)&HobRomImage);
    if (EFI_ERROR(Status)) return EFI_UNSUPPORTED;

    // Redirect the FV address to RAM and Free memory.
	for (p = GetEfiConfigurationTable (pST, &GuidHob); 
	     !(FindNextHobByType(EFI_HOB_TYPE_FV,&p)); ) {
		FvHob = (EFI_HOB_FIRMWARE_VOLUME*)p;
        for (i = 0; i < HobRomImage->NumOfFv; i++) {
            if ((FvHob->BaseAddress == HobRomImage->FvInfo[i].MemAddress) && \
                (FvHob->Length == HobRomImage->FvInfo[i].FvLength)) {
                FvHob->BaseAddress = HobRomImage->FvInfo[i].FvAddress;
                pBS->FreePages (HobRomImage->FvInfo[i].MemAddress, \
                                HobRomImage->FvInfo[i].NumOfPages);
                break;
            }
        }
    }

    // Restore the Base Address of Firmware Volume Block Protocol from RAM 
    // to ROM.
    Status = pBS->LocateHandleBuffer ( ByProtocol, \
                                       &gEfiFirmwareVolumeBlockProtocolGuid, \
                                       NULL, \
                                       &NumHandles, \
                                       &HandleBuffer    );
	if (EFI_ERROR(Status)) return Status;

    for (i = 0; i < NumHandles; ++i) {
        Status = pBS->HandleProtocol ( HandleBuffer[i], \
                                       &gEfiFirmwareVolumeBlockProtocolGuid, \
                                       &FvBlock );
        if (EFI_ERROR(Status)) continue;
        FvbDevice = FVB_DEVICE_FROM_THIS (FvBlock);
        if (!(FvbDevice->FvbAttributes & EFI_FVB_MEMORY_MAPPED)) continue;
//-TRACE((-1, "FvBaseAddress[%02X] = %08X\n", i, FvbDevice->BaseAddress));        
        for (j = 0; j < HobRomImage->NumOfFv; j++) {
            if ((FvbDevice->BaseAddress == HobRomImage->FvInfo[j].MemAddress) && \
                (FvbDevice->NumBlocks == \
                        (HobRomImage->FvInfo[j].FvLength / FLASH_BLOCK_SIZE))) {
                FvbDevice->BaseAddress = HobRomImage->FvInfo[j].FvAddress;
            }
        }
    }

    return EFI_SUCCESS;
}
//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:   PeiRamBootSmmInit
//
// Description: PeiRamBoot InSmm Function.
//
// Input:       EFI_HANDLE          - ImageHandle
//              EFI_SYSTEM_TABLE*   - SystemTable
//
// Output:      EFI_STATUS
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS
PeiRamBootDxeSmmInit (
  IN EFI_HANDLE             ImageHandle,
  IN EFI_SYSTEM_TABLE       *SystemTable
)
{
    return EFI_SUCCESS;
}
//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:   PeiRamBootDxeEntry
//
// Description: DXE Entry Point for PeiRamBoot Driver.
//
// Input:       EFI_HANDLE          - ImageHandle
//              EFI_SYSTEM_TABLE*   - SystemTable
//
// Output:      EFI_STATUS
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS
PeiRamBootDxeEntry (
  IN EFI_HANDLE             ImageHandle,
  IN EFI_SYSTEM_TABLE       *SystemTable
)
{
    InitAmiLib(ImageHandle,SystemTable);
    return InitSmmHandlerEx(ImageHandle, \
                SystemTable, PeiRamBootDxeSmmInit, PeiRamBootDxeInit);
}
//*************************************************************************
//*************************************************************************
//**                                                                     **
//**        (C)Copyright 1985-2009, American Megatrends, Inc.            **
//**                                                                     **
//**                       All Rights Reserved.                          **
//**                                                                     **
//**      5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093           **
//**                                                                     **
//**                       Phone: (770)-246-8600                         **
//**                                                                     **
//*************************************************************************
//*************************************************************************