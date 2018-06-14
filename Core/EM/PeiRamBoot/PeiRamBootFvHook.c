//*************************************************************************
//*************************************************************************
//**                                                                     **
//**        (C)Copyright 1985-2012, American Megatrends, Inc.            **
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
// $Header: /Alaska/SOURCE/Modules/PEI Ram Boot/PeiRamBootFvHook.c 4     1/16/13 6:33a Calvinchen $
//
// $Revision: 4 $
//
// $Date: 1/16/13 6:33a $
//**********************************************************************
// Revision History
// ----------------
// $Log: /Alaska/SOURCE/Modules/PEI Ram Boot/PeiRamBootFvHook.c $
// 
// 4     1/16/13 6:33a Calvinchen
// Update Header.
// 
// 3     8/08/12 4:25a Calvinchen
// 1. Changed for ReportFv2.c by Artem's suggestion.
// 2. Fixed System hangs if Memory Mapping Changed with warm boot.
// 
// 2     7/18/12 3:41a Calvinchen
// 
// 1     7/18/12 3:33a Calvinchen
// [TAG]  		EIPNone
// [Category]  	New Feature
// [Description]  	Added support for Nested Firmware Volume.
// 
//
//**********************************************************************
//<AMI_FHDR_START>
//
// Name:    PeiRamBootFvHook.c
//
// Description: Hook File for Report Firmware Volume.
//
//<AMI_FHDR_END>
//**********************************************************************
//----------------------------------------------------------------------------
// Includes
// Statements that include other files
#include <RomLayout.h>
#include <Token.h>
#include <AmiPeiLib.h>
#include <AmiCspLib.h>
#include <PeiRamBoot.h>
//----------------------------------------------------------------------------
// Function Externs
extern
EFI_STATUS PublishFv(
    IN EFI_PEI_SERVICES **PeiServices,
    IN ROM_AREA         *Area,
    IN BOOLEAN          Nested
);
extern
EFI_STATUS CreateFvHob2(
    IN EFI_PEI_SERVICES **PeiServices,
    IN ROM_AREA         *Area,
    IN EFI_GUID         *FvName,
    IN EFI_GUID         *FfsName
);
extern
EFI_STATUS CreateFvInfoPpi(
    IN EFI_PEI_SERVICES **PeiServices,
    IN ROM_AREA         *Area,
    IN EFI_GUID         *FvName OPTIONAL,
    IN EFI_GUID         *FfsName OPTIONAL
);
//----------------------------------------------------------------------------
// Local prototypes

//----------------------------------------------------------------------------
// Local Variables

//----------------------------------------------------------------------------
// Function Definitions
//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:   PeiRamBootNestedFvPublishing
//
// Description: 
//
// Input:       EFI_PEI_SERVICES**  - PeiServices
//              ROM_AREA*           - Area
//
// Output:      EFI_STATUS
//              ROM_AREA*           - Area
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS 
PeiRamBootNestedFvPublishing (
    IN      EFI_PEI_SERVICES            **PeiServices,
    IN OUT  ROM_AREA                    *Area,
    OUT     EFI_FIRMWARE_VOLUME_HEADER  **Fv,
    OUT     EFI_FIRMWARE_VOLUME_HEADER  **NewFv,
    OUT     EFI_FFS_FILE_HEADER         **Nfv
)
{
 	VOID                    *p, *p2;
    static UINT8            NestedFvIndex = 0;
    INTN                    Result;
    EFI_STATUS              Status;
    EFI_BOOT_MODE           BootMode;
    EFI_GUID                HobRomImageGuid = ROM_IMAGE_MEMORY_HOB_GUID;
   	EFI_PHYSICAL_ADDRESS    NestedFvBuffer = 0, NestedFvInMem = 0, TopOfMemory = 0;
   	UINT32                  NestedFvLength = 0;
    EFI_FIRMWARE_VOLUME_HEADER *pFv;

    Status = (*PeiServices)->GetBootMode (PeiServices, &BootMode);
    if (EFI_ERROR(Status) || \
        (BootMode == BOOT_IN_RECOVERY_MODE) || \
        (BootMode == BOOT_ON_FLASH_UPDATE)) return EFI_UNSUPPORTED;

	for ((*PeiServices)->GetHobList(PeiServices,&p); \
	     !(FindNextHobByType(EFI_HOB_TYPE_GUID_EXTENSION, &p));	) {
        Result = guidcmp(&((EFI_HOB_GUID_TYPE*)p)->Name, &HobRomImageGuid);
        if (!Result) break;
	}	    
    if (Result) return EFI_UNSUPPORTED;
    if (((HOB_ROM_IMAGE*)p)->HobValid == 0) {
        // Try to decompress the Nested FV from memory if possible
        UINT8       i;
        ((HOB_ROM_IMAGE*)p)->NestedFvValid = 0;
        for (i = 0; i < ((HOB_ROM_IMAGE*)p)->NumOfFv; i++) {
            if ((Area->Address == ((HOB_ROM_IMAGE*)p)->FvInfo[i].FvAddress) && \
                (((HOB_ROM_IMAGE*)p)->FvInfo[i].FvMemReady == TRUE))
                *Fv = (EFI_FIRMWARE_VOLUME_HEADER*)((HOB_ROM_IMAGE*)p)->FvInfo[i].MemAddress;
        }
        return EFI_UNSUPPORTED;
    }
    pFv = (EFI_FIRMWARE_VOLUME_HEADER*)Area->Address;
    NestedFvLength = ((HOB_ROM_IMAGE*)p)->NestedFvInfo[NestedFvIndex].FvLength;
    NestedFvInMem = (EFI_PHYSICAL_ADDRESS)((HOB_ROM_IMAGE*)p)->NestedFvInfo[NestedFvIndex++].MemAddress;
    // check whether NestFv memory is valid.
	for ((*PeiServices)->GetHobList(PeiServices,&p2); \
	     !(FindNextHobByType(EFI_HOB_TYPE_MEMORY_ALLOCATION, &p2));	) {
	    TopOfMemory = ((EFI_HOB_MEMORY_ALLOCATION*)p2)->AllocDescriptor.MemoryBaseAddress;     
    }
    if (TopOfMemory != ((NestedFvInMem & (EFI_PHYSICAL_ADDRESS)~0xfff) + NestedFvLength + 0x1000)) {
        // Memory Mapping changed, decompress Nested FV and re-collect Nested FV information
        ((HOB_ROM_IMAGE*)p)->NestedFvValid = 0;
        return EFI_UNSUPPORTED;
    }
    
    Status = (*PeiServices)->FfsFindNextFile (PeiServices, \
                            EFI_FV_FILETYPE_FIRMWARE_VOLUME_IMAGE, pFv, Nfv);
    if(EFI_ERROR(Status)) return Status;

    Status = (*PeiServices)->AllocatePages(PeiServices, \
           EfiRuntimeServicesData, (NestedFvLength >> 12) + 1, &NestedFvBuffer);
    if (EFI_ERROR(Status)) return EFI_UNSUPPORTED;
    if ((NestedFvInMem & (EFI_PHYSICAL_ADDRESS)~0xfff) != NestedFvBuffer) {
        return EFI_UNSUPPORTED;
    }
    *NewFv = (EFI_FIRMWARE_VOLUME_HEADER*)(EFI_PHYSICAL_ADDRESS)NestedFvInMem;
    ((HOB_ROM_IMAGE*)p)->NestedFvValid = 1;
    return EFI_SUCCESS;           
}
//*************************************************************************
//*************************************************************************
//**                                                                     **
//**        (C)Copyright 1985-2012, American Megatrends, Inc.            **
//**                                                                     **
//**                       All Rights Reserved.                          **
//**                                                                     **
//**      5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093           **
//**                                                                     **
//**                       Phone: (770)-246-8600                         **
//**                                                                     **
//*************************************************************************
//*************************************************************************