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
// $Header: /Alaska/SOURCE/Modules/PTT/FastBootDxe.c 2     4/07/11 8:20a Bibbyyeh $
//
// $Revision: 2 $
//
// $Date: 4/07/11 8:20a $
//*************************************************************************
// Revision History
// ----------------
// $Log: /Alaska/SOURCE/Modules/PTT/FastBootDxe.c $
// 
// 2     4/07/11 8:20a Bibbyyeh
// [TAG]  		EIP57430
// [Category]  	New Feature
// [Description]  	PTT module is not compatible with core 4.6.5.0. Modify
// it to make build pass.
// [Files]  		FastBootDxe.c
// 
// 1     3/02/11 2:23a Bibbyyeh
// [TAG]  		EIP51391
// [Category]  	Bug Fix
// [Severity]  	Normal
// [Symptom]  	In windows, use DmiEdit to change SMBIOS data, and update.
// SMBIOS will update failure in next boot.
// [RootCause]  	The reason cause this issue is, ROM will copy to ram in
// end of PEI phase. When SMBIOS Dxe driver update modified data to flash,
// the firmware volume block protocol is pointer to RAM, not flash. So it
// will cause update failure.
// [Solution]  	Before SMBIOS Dxe driver, restore the Base Address of
// Firmware Volume Block Protocol from RAM to ROM.
// [Files]         FastBoot.sdl FastBoot.mak FastBoot.cif FastBootDxe.c
// 
//
//*************************************************************************
//<AMI_FHDR_START>
//
// Name:  FastBootDxe.c
//
//  Description:
//  Implementation of fast boot Dxe functionality
//
//<AMI_FHDR_END>
//*************************************************************************
//----------------------------------------------------------------------------
// Includes
// Statements that include other files
#include <AmiDxeLib.h>
#include <AmiCspLib.h>
#include <Protocol\FirmwareVolumeBlock.h>
#include <FFS.h>
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

#define FVB_DEVICE_FROM_THIS(a) \
  CR(a, EFI_FW_VOL_BLOCK_DEVICE, FwVolBlockInstance, FVB_DEVICE_SIGNATURE)


//----------------------------------------------------------------------------
// Local Variables
//----------------------------------------------------------------------------
// Function Definitions
//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:   FastBootDxeEntry
//
// Description: DXE Entry Point for FastBoot Driver.
//
// Input:       EFI_HANDLE          - ImageHandle
//              EFI_SYSTEM_TABLE*   - SystemTable
//
// Output:      EFI_STATUS
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS
FastBootDxeEntry (
  IN EFI_HANDLE             ImageHandle,
  IN EFI_SYSTEM_TABLE       *SystemTable
)
{

    EFI_GUID    EfiFirmwareVolumeBlockProtocolGuid = FW_VOLUME_BLOCK_PROTOCOL_GUID;
    EFI_STATUS              Status;
    UINTN                   NumHandles;
    UINT8                   i;

	EFI_HANDLE				*HandleBuffer;
    EFI_FW_VOL_BLOCK_DEVICE *FvbDevice;
    EFI_FIRMWARE_VOLUME_BLOCK_PROTOCOL  *FvBlock;


    InitAmiLib(ImageHandle, SystemTable);

    TRACE((-1,"FB:Restore the Base Address of Firmware Volume Block Protocol from RAM to ROM\n"));
// Restore the Base Address of Firmware Volume Block Protocol from RAM 
// to ROM.
    Status = pBS->LocateHandleBuffer ( ByProtocol, \
                                       &EfiFirmwareVolumeBlockProtocolGuid, \
                                       NULL, \
                                       &NumHandles, \
                                       &HandleBuffer    );
	if (EFI_ERROR(Status)) return Status;

    for (i = 0; i < NumHandles; ++i) {
        Status = pBS->HandleProtocol ( HandleBuffer[i], \
                                       &EfiFirmwareVolumeBlockProtocolGuid, \
                                       &FvBlock );
        if (EFI_ERROR(Status)) continue;
        FvbDevice = FVB_DEVICE_FROM_THIS (FvBlock);
#if PI_SPECIFICATION_VERSION < 0x00010000
        if (!(FvbDevice->FvbAttributes & EFI_FVB_MEMORY_MAPPED)) continue;
#else
        if (!(FvbDevice->FvbAttributes & EFI_FVB2_MEMORY_MAPPED)) continue;
#endif
        if (FvbDevice->NumBlocks == FV_BB_BLOCKS)
            FvbDevice->BaseAddress = FV_BB_BASE;
        else if (FvbDevice->NumBlocks == FV_MAIN_BLOCKS)    
            FvbDevice->BaseAddress = FV_MAIN_BASE;            
 
    }

    return EFI_SUCCESS;
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