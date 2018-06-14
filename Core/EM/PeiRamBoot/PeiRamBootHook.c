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
// $Header: /Alaska/SOURCE/Modules/PEI Ram Boot/PeiRamBootHook.c 8     8/28/15 3:51a Tristinchou $
//
// $Revision: 8 $
//
// $Date: 8/28/15 3:51a $
//**********************************************************************
// Revision History
// ----------------
// $Log: /Alaska/SOURCE/Modules/PEI Ram Boot/PeiRamBootHook.c $
// 
// 8     8/28/15 3:51a Tristinchou
// [TAG]  		EIP235157
// [Category]  	Improvement
// [Description]  	Security vulnerability - PeiRamBoot: Should leave cold
// boot optimization only
// 
// 7     6/21/11 2:22a Calvinchen
// ¡P Bug Fixed: 
// Bug Fixed:
// 1. Build failed if Core 4.6.4.0. 
// 2. System could hang if SAVE_ENTIRE_FV_TO_MEM = 1with AMD platform. 
// 
// 6     5/27/11 7:22a Calvinchen
// Build failed if Core 4.6.4.1.
// 
// 5     4/25/11 3:59a Calvinchen
// Build failed if Core version greater than 4.6.4.1 with PI 0.91.
// 
// 4     4/22/11 1:27a Calvinchen
// 
// 3     3/22/11 7:52a Calvinchen
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
// 2     12/14/10 2:25a Calvinchen
// Improvement : 
// 1. Added an eLink "PeiRamBootList" for fast warm boot support
// (PEI_RAM_BOOT_S3_SUPPORT = 1). If system boots in warm boot state, BIOS
// directly boot to previous copied ROM image in RAM to save time of
// copying ROM. 
// 2. Added "PEI_RAM_BOOT_S3_SUPPORT" = "2" for saving runtime memory, it
// only keep necessary PEIM FFS in runtime memory for S3 resume
// improvement. 
// 
// 1     10/27/10 2:48a Calvinchen
// Initial Check-in.
// 
//
//**********************************************************************
//<AMI_FHDR_START>
//
// Name: PeiRamBootHook.c
//
// Description: Hook file for PEI Ram Boot module.
//
//<AMI_FHDR_END>
//**********************************************************************
//----------------------------------------------------------------------------
// Includes
// Statements that include other files
#include <Tiano.h>
#include <PeiCore.h>
#include <Token.h>
#include <PeiRamBoot.h>

//----------------------------------------------------------------------------
// Function Externs

//----------------------------------------------------------------------------
// Local prototypes

//----------------------------------------------------------------------------
// Local Variables

//----------------------------------------------------------------------------
// Function Definitions
//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:   PeiDebugPrint
//
// Description: Worker function for debug print.
//
// Input:       EFI_PEI_SERVICES**  - PeiServices
//              UINTN               - ErrorLevel
//              CHAR8*              - Format
//
// Output:      None.
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
#ifdef EFI_DEBUG
  VOID
  PeiDebugPrint (
#if ((PI_SPECIFICATION_VERSION >= 0x0001000A) || (CORE_COMBINED_VERSION > 262785))
#if (CORE_COMBINED_VERSION > 262785)
    IN CONST EFI_PEI_SERVICES   **PeiServices,
#else
    IN EFI_PEI_SERVICES   **PeiServices,
#endif
#else
    IN EFI_PEI_SERVICES   **PeiServices,
#endif
    IN UINTN              ErrorLevel,
    IN CHAR8              *Format,
    IN ...
    )
  {
	CHAR8  Buffer[256];
	va_list	ArgList = va_start(ArgList,Format);
	PrepareStatusCodeString( Buffer, sizeof(Buffer), Format, ArgList );
	(*PeiServices)->ReportStatusCode (
		(EFI_PEI_SERVICES**)PeiServices, EFI_DEBUG_CODE, 
		EFI_SOFTWARE_UNSPECIFIED, 0, NULL,
		(EFI_STATUS_CODE_DATA *)Buffer
	);
	va_end(ArgList);
  }
#endif
#if (PI_SPECIFICATION_VERSION >= 0x0001000A)
//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:   IsPeimDispatched
//
// Description: 
//
// Input:       EFI_PEI_SERVICES**  - PeiServices
//              EFI_PHYSICAL_ADDRESS - Buffer
//
// Output:      None.
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
BOOLEAN
IsPeimDispatched (
    IN EFI_PEI_SERVICES             **PeiServices,
    IN EFI_FFS_FILE_HEADER          *FfsFile,
    IN UINTN                        Index
)
{
    PEI_CORE_INSTANCE           *Private = NULL;
    Private = PEI_CORE_INSTANCE_FROM_PS_THIS(PeiServices);
    return Private->Fv[Private->CurrentPeimFvCount].PeimState[Index];
}
#else
//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:   GetDispatchedPeimBitMap
//
// Description: This procedure gets current PEIM dispatched BitMap from 
//              DispatchedData of Privatedata of PeiService.
//
// Input:       EFI_PEI_SERVICES**  - PeiServices
//              EFI_PHYSICAL_ADDRESS - Buffer
//
// Output:      None.
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
UINT64
GetDispatchedPeimBitMap (
    IN EFI_PEI_SERVICES     **PeiServices
)
{
    PEI_CORE_INSTANCE           *PrivateData = NULL;
    PrivateData = PEI_CORE_INSTANCE_FROM_PS_THIS(PeiServices);
    return PrivateData->DispatchData.DispatchedPeimBitMap;
}
#endif
//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:   SwitchPeiServiceDataToRam
//
// Description: This procedure redirect the FV Bass Address of Private data of
//              PEI Service from ROM to RAM.
//
// Input:       EFI_PEI_SERVICES**  - PeiServices
//              EFI_PHYSICAL_ADDRESS - Buffer
//
// Output:      None.
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID
SwitchPeiServiceDataToRam (
    IN EFI_PEI_SERVICES     **PeiServices,
    IN HOB_ROM_IMAGE        *HobRomImage
)
{
    PEI_CORE_INSTANCE           *PrivateData = NULL;
  	EFI_PHYSICAL_ADDRESS        FvAddress = 0, PeimAddress = 0, Buffer = 0;
    EFI_PEI_NOTIFY_DESCRIPTOR   *NotifyList =  NULL;
    UINTN                       i = 0, j = 0, Index;
    EFI_STATUS                  Status = EFI_SUCCESS;
    EFI_FFS_FILE_HEADER         *FfsFile = NULL;


    PrivateData = PEI_CORE_INSTANCE_FROM_PS_THIS(PeiServices);
#if defined(PI_SPECIFICATION_VERSION) && (PI_SPECIFICATION_VERSION >= 0x0001000A)
    for (i = 0, Index = 0; i < HobRomImage->NumOfFv; i++) {
      Index = PrivateData->CurrentPeimFvCount;
      FvAddress = \
        (EFI_PHYSICAL_ADDRESS)PrivateData->Fv[Index].FvHeader;
      if ((UINT32)FvAddress != HobRomImage->FvInfo[i].FvAddress) continue;
      Buffer = HobRomImage->FvInfo[i].MemAddress;
      PrivateData->Fv[Index].FvHeader = (EFI_FIRMWARE_VOLUME_HEADER*)Buffer;
      for (j = 0; (j < PEI_CORE_MAX_PEIM_PER_FV) && \
                  (PrivateData->CurrentFvFileHandles[j] != NULL); j++) {
        PrivateData->CurrentFvFileHandles[j] = \
          (EFI_PEI_FILE_HANDLE)(((UINTN)PrivateData->CurrentFvFileHandles[j] - \
                                                   (UINTN)FvAddress) + Buffer);
        PrivateData->Fv[Index].FvFileHandles[j] = \
          (EFI_PEI_FILE_HANDLE)(((UINTN)PrivateData->Fv[Index].FvFileHandles[j] - \
                                                   (UINTN)FvAddress) + Buffer);
      }
    }
#else // // PI 0.9 & 1.0
    // Update PrivateData.DispatchData of PeiService.
    FvAddress = (EFI_PHYSICAL_ADDRESS)PrivateData->DispatchData.BootFvAddress;
    for (i = 0, Index = 0; i < HobRomImage->NumOfFv; i++) {
        if ((UINT32)FvAddress != HobRomImage->FvInfo[i].FvAddress) continue;
        Buffer = HobRomImage->FvInfo[i].MemAddress;
        PrivateData->DispatchData.BootFvAddress = \
                                    (EFI_FIRMWARE_VOLUME_HEADER*)(Buffer);
        PrivateData->DispatchData.CurrentFvAddress = \
                                    (EFI_FIRMWARE_VOLUME_HEADER*)(Buffer);
        // CurrentPeimAddress point to last PEIM, so, dispatcher will start at
        // the 1st in next time.                                     
        // find last FFS..
        PeimAddress = (EFI_PHYSICAL_ADDRESS)PrivateData->DispatchData.CurrentPeimAddress;
        PrivateData->DispatchData.CurrentPeimAddress = \
                    (EFI_FFS_FILE_HEADER*)(Buffer + (PeimAddress - FvAddress));
        break;
    }    
#endif  // PI 0.9 & 1.0        
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