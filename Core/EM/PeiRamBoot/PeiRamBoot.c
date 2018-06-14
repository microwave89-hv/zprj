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
// $Header: /Alaska/SOURCE/Modules/PEI Ram Boot/PeiRamBoot.c 21    8/28/15 3:55a Tristinchou $
//
// $Revision: 21 $
//
// $Date: 8/28/15 3:55a $
//**********************************************************************
// Revision History
// ----------------
// $Log: /Alaska/SOURCE/Modules/PEI Ram Boot/PeiRamBoot.c $
// 
// 21    8/28/15 3:55a Tristinchou
// [TAG]  		EIP235157
// [Category]  	Improvement
// [Description]  	Security vulnerability - PeiRamBoot: Should leave cold
// boot optimization only
// 
// 20    10/02/14 4:44a Calvinchen
// [TAG]  		EIP184075
// [Category]  	Improvement
// [Description]  	[HWR]FtRecovery support for Intel Top Swap
// Modified PeiRamBoot module for multiple Boot Block Volumes support.
// [Files]  		PeiRamBoot.sdl
// PeiRamBoot.mak
// PeiRamBoot.c
// PeiRamBoot.chm
// PeiRamBoot.cif
// 
// 19    7/24/13 6:15a Calvinchen
// Bug Fixed: System hangs at CP60 if LastFfsFile Guild is installed with
//  DebugMode "ON".
// 
// 18    5/22/13 7:30a Calvinchen
// System hangs if OPTIMIZE_BOOT_FV_COPY = 1 with AMI Debug Rx enabled
// Description : Added Saveing Module Type "EFI_FV_FILETYPE_DRIVER" in
// Optimize Boot FV. 
// 
// 17    3/15/13 4:39a Calvinchen
// Bug Fixed: System hangs if OPTIMIZE_BOOT_FV_COPY = 1 
// Description : RAW and FREEFORM FFS must be saved in Optimize Boot FV. 
// 
// 16    2/05/13 12:51a Calvinchen
// 
// 15    1/16/13 6:31a Calvinchen
// [TAG]  		EIPNone
// [Category]  	Improvement
// [Description]  	1. Added support to minimumize Boot FV copy for
// improving POST time. 
// 2. Added Last Firmware Volume FFS file Override mechanism. 
// [Files]  		PeiRamBoot.sdl
// PeiRamBoot.c
// PeiRamBoot.chm
// PeiRamBoot.cif
// 
// 14    11/29/12 10:48p Calvinchen
// [TAG]  		EIP106511
// [Category]  	Bug Fix
// [Severity]  	Normal
// [Symptom]  	PI 0.9 and 1.0 in Core 4.6.5.4
// [RootCause]  	Build failed if PI 1.0.
// [Files]  		PeiRamBoot.c
// 
// 12    8/08/12 4:25a Calvinchen
// 1. Changed for ReportFv2.c by Artem's suggestion.
// 2. Fixed System hangs if Memory Mapping Changed with warm boot.
// 
// 11    7/18/12 3:38a Calvinchen
// [TAG]  		EIP94448
// [Category]  	Improvement
// [Description]  	Can not Save the DXE IPL Boot time,even add the PEI RAM
// Boot eModule.
// 
// 10    2/23/12 9:06a Calvinchen
// Fixed building error.
// 
// 9     2/23/12 6:35a Calvinchen
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
// 8     5/27/11 7:19a Calvinchen
// [TAG]  		EIP60320
// [Category]  	Bug Fix
// [Severity]  	Normal
// [Symptom]  	System hangs at CP 0x72 when SMM_THUNK_IN_CSM is 0 on
// Huronriver.
// [RootCause]  	InSmmFunction is NULL in InitSmmHandlerEx call.
// [Solution]  	Added dummy InSmmFunction.
// [Files]  		PeiRamBoot.c
// 
// 7     4/22/11 1:27a Calvinchen
// 
// 6     3/22/11 7:52a Calvinchen
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
// 5     2/11/11 3:16a Calvinchen
// Bug Fixed : System hangs after reflashed BIOS with warm reset if
// PEI_RAM_BOOT_S3_SUPPORT = 1 with fast warm boot support.
// 
// 4     12/29/10 5:35a Calvinchen
// Bug Fixed : DMI structure not update in system memory if
// PEI_RAM_BOOT_S3_SUPPORT = 1 with fast warm boot support. 
// 
// 3     12/26/10 9:59p Calvinchen
// Bug Fixed:
// 1. Recovery not work if PEI_RAM_BOOT_S3_SUPPORT = 2. 
// 2. S4 resume failed if PEI_RAM_BOOT_S3_SUPPORT = 1 with fast warm boot
// support. 
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
// Name: PeiRamBoot.c
//
// Description: PEI RAM BOOT Pei driver.
//
//<AMI_FHDR_END>
//**********************************************************************
//----------------------------------------------------------------------------
// Includes
// Statements that include other files
#include <PEI.h>
#include <AmiPeiLib.h>
//#include <AmiCspLib.h>
#include <ppi\ReadOnlyVariable.h>
#include <ppi\RecoveryModule.h>
#include <RomLayout.h>
#include <Token.h>
#include <PeiRamBoot.h>
#if (PI_SPECIFICATION_VERSION >= 0x0001000A)
#include <PeiCore.h>
#endif
#if defined (SecureBoot_SUPPORT) && SecureBoot_SUPPORT == 1
#include <AmiCertificate.h>
#endif
//----------------------------------------------------------------------------
// Function Externs
extern
VOID
SwitchPeiServiceDataToRam (
    IN EFI_PEI_SERVICES             **PeiServices,
    IN HOB_ROM_IMAGE                *HobRomImage
);
#if (PI_SPECIFICATION_VERSION >= 0x0001000A)
extern
BOOLEAN 
IsPeimDispatched (
    IN EFI_PEI_SERVICES             **PeiServices,
    IN EFI_FFS_FILE_HEADER          *FfsFile,
    IN UINTN                        Index
);
#else
extern
UINT64
GetDispatchedPeimBitMap (
    IN EFI_PEI_SERVICES             **PeiServices
);
#endif
extern ROM_AREA RomLayout[];

typedef BOOLEAN (PEI_RAM_BOOT_ELINK) (EFI_PEI_SERVICES **PeiServices);
extern PEI_RAM_BOOT_ELINK PEI_RAM_BOOT_LIST EndOfPeiRamBootList;
PEI_RAM_BOOT_ELINK* IsMrcColdBooteLink[] = {PEI_RAM_BOOT_LIST NULL};

//----------------------------------------------------------------------------
// Local prototypes
#define PR_KEY_FFS_FILE_RAW_GUID \
{ 0x3FEEC852, 0xF14C, 0x4E7F, 0x97, 0xFD, 0x4C, 0x3A, 0x8C, 0x5B, 0xBE, 0xCC }
#define ROM_LAYOUT_FFS_GUID \
{ 0x0DCA793A, 0xEA96, 0x42d8, 0xBD, 0x7B, 0xDC, 0x7F, 0x68, 0x4E, 0x38, 0xC1 }
#define FID_FFS_FILE_NAME_GUID \
{ 0x3fd1d3a2, 0x99f7, 0x420b, 0xbc, 0x69, 0x8b, 0xb1, 0xd4, 0x92, 0xa3, 0x32 }
#define PKEY_FILE_GUID \
{ 0xCC0F8A3F, 0x3DEA,  0x4376, 0x96, 0x79, 0x54, 0x26, 0xba, 0x0a, 0x90, 0x7e }
#define KEK_FILE_GUID \
{ 0x9fe7de69, 0xaea, 0x470a, 0xb5, 0xa, 0x13, 0x98, 0x13, 0x64, 0x91, 0x89 }
#define DB_FILE_GUID \
{ 0xfbf95065, 0x427f, 0x47b3, 0x80, 0x77, 0xd1, 0x3c, 0x60, 0x71, 0x9, 0x98 }
#define DBX_FILE_GUID \
{ 0x9d7a05e9, 0xf740, 0x44c3, 0x85, 0x8b, 0x75, 0x58, 0x6a, 0x8f, 0x9c, 0x8e }

EFI_GUID gHobRomImageGuid = ROM_IMAGE_MEMORY_HOB_GUID;
EFI_GUID gEfiPeiEndOfPeiPhasePpiGuid = EFI_PEI_END_OF_PEI_PHASE_PPI_GUID;
EFI_GUID gCacheInstallGuid = EFI_PEI_PERMANENT_MEMORY_INSTALLED_PPI;
EFI_GUID gEfiPeiReadOnlyVariablePpiGuid = EFI_PEI_READ_ONLY_VARIABLE_PPI_GUID;
EFI_GUID gEfiPeiRecoveryModePpiGuid = EFI_PEI_BOOT_IN_RECOVERY_MODE_PEIM_PPI;
EFI_GUID gEfiPeiRecoveryModulePpiGuid = EFI_PEI_RECOVERY_MODULE_PPI_GUID;
EFI_GUID gSmbiosFlashDataFfsGuid = SMBIOS_FLASH_DATA_FFS_GUID;
EFI_GUID gRomCacheEnablePpiGuid = ROM_CACHE_ENABLE_PPI_GUID;
EFI_GUID gPrKeyFfsFileRawGuid = PR_KEY_FFS_FILE_RAW_GUID;
EFI_GUID gLastFfsFileOverrideGuid = \
{0x45B9618F, 0xBAA1, 0x421B, { 0x94, 0xF0, 0xB9, 0xEB, 0xDD, 0x2B, 0xA1, 0x77 }};

EFI_STATUS
PeiRamBootMemoryReady (
    IN EFI_PEI_SERVICES             **PeiServices,
    IN EFI_PEI_NOTIFY_DESCRIPTOR    *NotifyDescriptor,
    IN VOID                         *NullPpi
);

EFI_STATUS
PeiRamBootEndOfPei (
    IN EFI_PEI_SERVICES             **PeiServices,
    IN EFI_PEI_NOTIFY_DESCRIPTOR    *NotifyDescriptor,
    IN VOID                         *NullPpi
);
static EFI_PEI_NOTIFY_DESCRIPTOR PeiRamBootMemoryReadyNotify[] =
{
    {
        EFI_PEI_PPI_DESCRIPTOR_NOTIFY_CALLBACK | \
        EFI_PEI_PPI_DESCRIPTOR_TERMINATE_LIST,
        &gCacheInstallGuid,
        PeiRamBootMemoryReady
    }
};
static EFI_PEI_NOTIFY_DESCRIPTOR PeiRamBootEndOfPeiNotify[] =
{
    {
        EFI_PEI_PPI_DESCRIPTOR_NOTIFY_CALLBACK | \
        EFI_PEI_PPI_DESCRIPTOR_TERMINATE_LIST,
        &gEfiPeiEndOfPeiPhasePpiGuid,
        PeiRamBootEndOfPei
    }
};
//----------------------------------------------------------------------------
// Local Variables
UINT32 FvBootBlocksList[] = {
    PEI_RAM_BOOT_FV_BOOTBLOCK_LIST
    FV_BB_BASE,
    { -1 }
};

//----------------------------------------------------------------------------
// Function Definitions

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:   IsBootFirmwareVolume
//
// Description:
//
// Input:       EFI_PEI_SERVICES**      - PeiServices
//              EFI_PHYSICAL_ADDRESS    - Address
//
// Output:      None.
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
BOOLEAN
IsBootBlockFirmwareVolumes (
    IN EFI_PEI_SERVICES             **PeiServices,
    IN EFI_PHYSICAL_ADDRESS         Address
)
{
    UINT8           i;
#if (PI_SPECIFICATION_VERSION >= 0x0001000A)
    PEI_CORE_INSTANCE           *Private = NULL;
    Private = PEI_CORE_INSTANCE_FROM_PS_THIS(PeiServices);
    if (Private->Fv[0].FvHeader == (EFI_FIRMWARE_VOLUME_HEADER*)Address) 
        return TRUE;
#endif
    for (i = 0; FvBootBlocksList[i] != -1; i++)
        if (Address == (EFI_PHYSICAL_ADDRESS)FvBootBlocksList[i]) return TRUE;
    return FALSE;    
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:   PrepareForCopyRomToRam
//
// Description: This procedure allocate memroy buffer for copying rom to ram.
//
// Input:       EFI_PEI_SERVICES**  - PeiServices
//              HOB_ROM_IMAGE       - *HobRomImage
//
// Output:      EFI_STATUS
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS
PrepareForCopyRomToRam (
    IN EFI_PEI_SERVICES         **PeiServices,
    IN HOB_ROM_IMAGE            *HobRomImage
)
{
    UINT8                   i;
    EFI_STATUS              Status = EFI_SUCCESS;
    UINTN                   NumOfPages;
  	EFI_PHYSICAL_ADDRESS    Buffer = 0;

    for (i = 0; i < HobRomImage->NumOfFv; i++) {
        NumOfPages = HobRomImage->FvInfo[i].UsedBytes;
        if (HobRomImage->FvInfo[i].FvLength != 
                                    HobRomImage->FvInfo[i].UsedBytes) {
#if SAVE_ENTIRE_FV_IN_MEM == 0
            // 0x1200 = 1)4k aligned, 2)NULL bytes of FV
            NumOfPages = HobRomImage->FvInfo[i].UsedBytes + 0x1200;
#else
            NumOfPages = HobRomImage->FvInfo[i].FvLength;
#endif            
        }
        Status = (*PeiServices)->AllocatePages ( PeiServices,
       	                                         EfiBootServicesData,
      	                                         NumOfPages >> 12,
       	                                         &Buffer);
        if (EFI_ERROR(Status)) return EFI_UNSUPPORTED;
        // If HobValid is "TRUE", it means FV memories aren't destroyed, just 
        // reserve the necessary memory space for FV then exit.    
        if (HobRomImage->HobValid == TRUE) continue;
        HobRomImage->FvInfo[i].NumOfPages = NumOfPages >> 12;
        HobRomImage->FvInfo[i].MemAddress = (UINT32)Buffer;
        HobRomImage->FvInfo[i].FvMemReady = FALSE;
    }        
    return EFI_SUCCESS;
}
#if (PI_SPECIFICATION_VERSION >= 0x0001000A) && (OPTIMIZE_BOOT_FV_COPY == 1)
//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:   MinimumizeBootFv
//
// Description: This routine copy only undispatched PEIM and Preserved FFS Guid
//              to memory and FFS Header only if dispatched PEIM.
//
// Input:       EFI_PEI_SERVICES**  - PeiServices
//              HOB_ROM_IMAGE*      - HobRomImage,
//              UINT8               - Index
//
// Output:      EFI_STATUS
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID
MinimumizeBootFv (
    IN EFI_PEI_SERVICES         **PeiServices,
    IN HOB_ROM_IMAGE            *HobRomImage,
    IN UINT8                    Index
)
{
    UINTN       k = 0, n = 0, FfsLength;
    UINT8       *p = (UINT8*)HobRomImage->FvInfo[Index].MemAddress;
    UINT8       *q = (UINT8*)HobRomImage->FvInfo[Index].FvAddress;
    EFI_FFS_FILE_HEADER     *FfsFile = NULL;
    EFI_GUID                *pGuid = NULL;
    EFI_STATUS              Status = EFI_SUCCESS;

    // 1. Copy Firmware Volume Header to Memory buffer.
    (*PeiServices)->CopyMem ( \
                p, q, ((EFI_FIRMWARE_VOLUME_HEADER*)q)->HeaderLength);
    p += ((EFI_FIRMWARE_VOLUME_HEADER*)q)->HeaderLength; 
    do {
        Status = (*PeiServices)->FfsFindNextFile (PeiServices, \
              EFI_FV_FILETYPE_ALL, (EFI_FIRMWARE_VOLUME_HEADER*)q, &FfsFile );
        if (EFI_ERROR(Status)) break;

        // calculate file alignment (Align on 8 bytes).
        FfsLength = *(UINT32*)FfsFile->Size & 0xffffff;
        FfsLength = (FfsLength + 7) & 0xfffffff8;
        // Copy undispatched PEIMs and FFS File Header only if dispatched PEIM 
        if ((FfsFile->Type == EFI_FV_FILETYPE_PEI_CORE) || \
            ((FfsFile->Type == EFI_FV_FILETYPE_PEIM) && \
            (!IsPeimDispatched(PeiServices, FfsFile, k)))) n = FfsLength; 
        else {
            n = sizeof(EFI_FFS_FILE_HEADER);
            // Copy RAW and FREEFORM FFS file..
            if ((FfsFile->Type == EFI_FV_FILETYPE_FREEFORM) || \
                (FfsFile->Type == EFI_FV_FILETYPE_DRIVER) || \
                (FfsFile->Type == EFI_FV_FILETYPE_RAW)) n = FfsLength;
        }
        // Increase PEIM index meeting PEI Core Private Data of PI 1.2  
        if (FfsFile->Type == EFI_FV_FILETYPE_PEIM) k++;    
        (*PeiServices)->CopyMem (p, (UINT8*)FfsFile, n);
        p = p + FfsLength;
    } while(!EFI_ERROR(Status));
}
#endif  // #if (PI_SPECIFICATION_VERSION >= 0x0001000A) && (OPTIMIZE_BOOT_FV_COPY == 1)
//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:   CopyFirmwareVolumesToRam
//
// Description: This procedure copy in used Firmware Volume to memroy. 
//
// Input:       EFI_PEI_SERVICES**  - PeiServices
//              HOB_ROM_IMAGE*      - HobRomImage,
//              BOOLEAN             - IsEndOfPei
//
// Output:      EFI_STATUS
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS
CopyFirmwareVolumesToRam (
    IN EFI_PEI_SERVICES         **PeiServices,
    IN HOB_ROM_IMAGE            *HobRomImage,
    IN BOOLEAN                  IsEndOfPei
)
{
    UINT8                   i;
    EFI_STATUS              Status = EFI_SUCCESS;

    for (i = 0; i < HobRomImage->NumOfFv; i++) {
        if ((!IsEndOfPei) && (!HobRomImage->FvInfo[i].IsBootFv)) continue;
        else if (IsEndOfPei && HobRomImage->FvInfo[i].IsBootFv) continue;
        HobRomImage->FvInfo[i].FvMemReady = TRUE;
        if (HobRomImage->HobValid) continue;

#if (PI_SPECIFICATION_VERSION >= 0x0001000A) && (OPTIMIZE_BOOT_FV_COPY == 1)
        if (HobRomImage->FvInfo[i].IsBootFv == TRUE) {
            MinimumizeBootFv (PeiServices, HobRomImage, i);
        }
        else
#endif  // #if (OPTIMIZE_BOOT_FV_COPY == 1)
        {    
            (*PeiServices)->CopyMem ((UINT8*)HobRomImage->FvInfo[i].MemAddress, \
                                     (UINT8*)HobRomImage->FvInfo[i].FvAddress, \
                                     HobRomImage->FvInfo[i].UsedBytes);
        }
        if (HobRomImage->FvInfo[i].UsedBytes != HobRomImage->FvInfo[i].FvLength) 
        {
            UINT32          NumofNullBytes;
#if SAVE_ENTIRE_FV_IN_MEM == 1
            // Fill Null Bytes after Used Data
            NumofNullBytes = HobRomImage->FvInfo[i].FvLength - \
                                    HobRomImage->FvInfo[i].UsedBytes;
#else
            // Fill Max 512 Null Bytes after Used Data
            NumofNullBytes = (HobRomImage->FvInfo[i].NumOfPages << 12) - \
                                    HobRomImage->FvInfo[i].UsedBytes;
            if (NumofNullBytes > 512) NumofNullBytes = 512;
#endif  // #if SAVE_ENTIRE_FV_IN_MEM == 1
            (*PeiServices)->SetMem (
                (UINT8*)(HobRomImage->FvInfo[i].MemAddress + \
                                    HobRomImage->FvInfo[i].UsedBytes), \
                NumofNullBytes, FLASH_EMPTY_BYTE );
        }                         
    }

    return EFI_SUCCESS;
}
//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:   CollectRomImageInfo
//
// Description: 
//
// Input:       EFI_PEI_SERVICES**  - PeiServices
//              EFI_PHYSICAL_ADDRESS - Buffer
//
// Output:      EFI_STATUS
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS
CollectRomImageInfo (
    IN EFI_PEI_SERVICES         **PeiServices,
    IN HOB_ROM_IMAGE            *HobRomImage
)
{
    ROM_AREA                *Area;
    UINT32                  FileSize;
    UINT8                   i = 0, j = 0, n = 0;
    UINTN                   k = 0;
    EFI_STATUS              Status = EFI_SUCCESS;
    EFI_FFS_FILE_HEADER     *FfsFile = NULL, *LastFfsFile = NULL;
    BOOLEAN                 IsDispatched = FALSE;
    UINT64                  DispatchedPeimBitMap = 0;
    EFI_GUID                *pGuid = NULL, *pLastFileOvrdeGuid = NULL;
    
    if (RomLayout == NULL) return EFI_UNSUPPORTED;
#if (PI_SPECIFICATION_VERSION < 0x0001000A)
    DispatchedPeimBitMap = GetDispatchedPeimBitMap(PeiServices);
#endif

    // Get Last File Override Guid for skiping unnecessary files copied
    // for reducing POST time. 
    Status = (*PeiServices)->LocatePpi ( PeiServices, \
                                         &gLastFfsFileOverrideGuid, \
                                         0, \
                                         NULL, \
                                         &pLastFileOvrdeGuid);
    if (EFI_ERROR(Status)) pLastFileOvrdeGuid = NULL;

    // find last ffs file for calculating used rom space for each Firmware Volume.
    for (Area = RomLayout; Area->Size != 0; Area++, FfsFile = NULL, FileSize = 0) {
        if (Area->Type != RomAreaTypeFv) continue;
        if (!(Area->Attributes & (ROM_AREA_FV_PEI_ACCESS + ROM_AREA_FV_DXE))) 
            continue;
        // find last ffs file for calculating used rom space.
        do {
            IsDispatched = TRUE;
            Status = (*PeiServices)->FfsFindNextFile ( 
                                PeiServices, \
                                EFI_FV_FILETYPE_ALL, \
                                (EFI_FIRMWARE_VOLUME_HEADER*)(Area->Address), \
                                &FfsFile );
            if (!EFI_ERROR(Status)) {
                // Terminate searching Last File if Last File Override Guid 
                // is defined and is identified.
                if ((pLastFileOvrdeGuid != NULL) && \
                    (!guidcmp(&FfsFile->Name, pLastFileOvrdeGuid))) {
                    FfsFile = LastFfsFile;
                    Status = EFI_NOT_FOUND;        
                } else LastFfsFile = FfsFile;
            }

        } while(!EFI_ERROR(Status));
        FileSize = *(UINT32*)FfsFile->Size & 0xffffff;
        FileSize += ((UINT32)FfsFile - (UINT32)Area->Address);
        HobRomImage->FvInfo[i].FvAddress = (UINT32)Area->Address;
        HobRomImage->FvInfo[i].FvLength = Area->Size;
        HobRomImage->FvInfo[i].UsedBytes = FileSize;
        HobRomImage->FvInfo[i].MemAddress = 0;
        if (IsBootBlockFirmwareVolumes(PeiServices, Area->Address))
            HobRomImage->FvInfo[i].IsBootFv = TRUE;
        else HobRomImage->FvInfo[i].IsBootFv = FALSE;
        HobRomImage->NumOfFv = ++i;
    }
    if (HobRomImage->NumOfFv == 0) return EFI_UNSUPPORTED;
    return EFI_SUCCESS;
}
//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:   FvHobSwitchToRam
//
// Description: This procedure redirect the FV Base Address of FV HOB to RAM.
//
// Input:       EFI_PEI_SERVICES**  - PeiServices
//              EFI_PHYSICAL_ADDRESS - RomImageBuffer
//
// Output:      EFI_STATUS
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS
FvHobSwitchToRam (
    IN EFI_PEI_SERVICES         **PeiServices,
    IN HOB_ROM_IMAGE            *HobRomImage
)
{
 	VOID                    *p;
	EFI_HOB_FIRMWARE_VOLUME	*FvHob;
	UINT8                   i, j = 0;
    EFI_BOOT_MODE           BootMode;
    EFI_STATUS              Status = EFI_SUCCESS;
#if (PI_SPECIFICATION_VERSION >= 0x0001000A)
    PEI_CORE_INSTANCE       *PrivateData;
    PrivateData = PEI_CORE_INSTANCE_FROM_PS_THIS (PeiServices);
#endif                    
    
    // Get current Boot Mode.
    Status = (*PeiServices)->GetBootMode (PeiServices, &BootMode);
    if (EFI_ERROR(Status)) return EFI_UNSUPPORTED;
    
 	// Update FV HOB (BaseAddress)
	for ((*PeiServices)->GetHobList(PeiServices,&p); 
	     !(FindNextHobByType(EFI_HOB_TYPE_FV,&p)); ) {
		FvHob = (EFI_HOB_FIRMWARE_VOLUME*)p;
        for (i = 0; i < HobRomImage->NumOfFv; i++) {
            if ((FvHob->BaseAddress == HobRomImage->FvInfo[i].FvAddress) && \
                (FvHob->Length == HobRomImage->FvInfo[i].FvLength) && \
                (HobRomImage->FvInfo[i].MemAddress != 0) && \
                (HobRomImage->FvInfo[i].FvMemReady)) {
#if (PI_SPECIFICATION_VERSION >= 0x0001000A)
				for(j = 0; j < PrivateData->AllFvCount; ++j){
					if((UINT32)FvHob->BaseAddress == (UINT32)PrivateData->AllFv[j]) {
						PrivateData->AllFv[j] = (EFI_PEI_FV_HANDLE)HobRomImage->FvInfo[i].MemAddress;
					}
				}
#endif  // #if (PI_SPECIFICATION_VERSION >= 0x0001000A)
                FvHob->BaseAddress = HobRomImage->FvInfo[i].MemAddress;
                break;
            }
        }
    }         
    return EFI_SUCCESS;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:   PeiRamBootEndOfPei
//
// Description: This procedure redirect the FV Base Address of FV HOB to RAM in
//              End of PEI Phase PPI.
//
// Input:       EFI_PEI_SERVICES**          - PeiServices
//              EFI_PEI_NOTIFY_DESCRIPTOR*  - NotifyDescriptor
//              VOID*                       - NullPpi
//
// Output:      EFI_STATUS
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS
PeiRamBootEndOfPei (
    IN EFI_PEI_SERVICES             **PeiServices,
    IN EFI_PEI_NOTIFY_DESCRIPTOR    *NotifyDescriptor,
    IN VOID                         *NullPpi
)
{
 	VOID                    *p;
    INTN                    Result;
    EFI_STATUS              Status;
    EFI_BOOT_MODE           BootMode;

    // Update BaseAddress of FV HOB again if new FV is reported.
	for ((*PeiServices)->GetHobList(PeiServices,&p); \
	     !(FindNextHobByType(EFI_HOB_TYPE_GUID_EXTENSION, &p));	) {
        Result = guidcmp(&((EFI_HOB_GUID_TYPE*)p)->Name, &gHobRomImageGuid);
        if (!Result) break;
	}	    
    if (Result) return EFI_UNSUPPORTED;

    Status = (*PeiServices)->GetBootMode (PeiServices, &BootMode);
    if (EFI_ERROR(Status)) return EFI_UNSUPPORTED;

    if (BootMode != BOOT_ON_S3_RESUME) {
        CopyFirmwareVolumesToRam(PeiServices, (HOB_ROM_IMAGE*)p, TRUE);
    }
    FvHobSwitchToRam (PeiServices, (HOB_ROM_IMAGE*)p);
    return EFI_SUCCESS;
}    
//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:   PeiRamBootMemoryReady
//
// Description: This procedure allocate a Memory buffer and redirect the FV from
//              ROM to RAM in PERMANENT MEMORY INSTALLED PPI;
//
// Input:       EFI_PEI_SERVICES**          - PeiServices
//              EFI_PEI_NOTIFY_DESCRIPTOR*  - NotifyDescriptor
//              VOID*                       - NullPpi
//
// Output:      EFI_STATUS
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS
PeiRamBootMemoryReady (
    IN EFI_PEI_SERVICES             **PeiServices,
    IN EFI_PEI_NOTIFY_DESCRIPTOR    *NotifyDescriptor,
    IN VOID                         *NullPpi
)
{
    EFI_STATUS                  Status;
    HOB_ROM_IMAGE               *HobRomImage = NULL;
    EFI_BOOT_MODE               BootMode;

    // Get current Boot Mode.
    Status = (*PeiServices)->GetBootMode (PeiServices, &BootMode);
    if (EFI_ERROR(Status)) return EFI_UNSUPPORTED;
    // Check Boot mode again, do nothing if recovery mode.
    if ((BootMode == BOOT_IN_RECOVERY_MODE) || \
        (BootMode == BOOT_ON_FLASH_UPDATE)) return EFI_SUCCESS;

        Status = (*PeiServices)->CreateHob ( PeiServices, \
                                             EFI_HOB_TYPE_GUID_EXTENSION, \
                                             sizeof(HOB_ROM_IMAGE), \
                                             &HobRomImage   );
        if (EFI_ERROR(Status)) return EFI_UNSUPPORTED;
        HobRomImage->EfiHobGuidType.Name = gHobRomImageGuid;


            HobRomImage->HobValid = FALSE;

            HobRomImage->NumOfFv = 0; 
            Status = CollectRomImageInfo (PeiServices, HobRomImage); 
            if (EFI_ERROR(Status)) return EFI_UNSUPPORTED;
        Status = PrepareForCopyRomToRam (PeiServices, HobRomImage);
        if (EFI_ERROR(Status)) return EFI_UNSUPPORTED;
        Status = CopyFirmwareVolumesToRam (PeiServices, HobRomImage, FALSE);
        if (EFI_ERROR(Status)) return EFI_UNSUPPORTED;
    SwitchPeiServiceDataToRam (PeiServices, HobRomImage);
    FvHobSwitchToRam (PeiServices, HobRomImage);
    return EFI_SUCCESS;
}
//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:   PeiRamBootEntry
//
// Description: PEI Entry Point for PeiRamBoot Driver.
//
// Input:       EFI_FFS_FILE_HEADER*    - FfsHeader
//              EFI_PEI_SERVICES**      - PeiServices
//
// Output:      EFI_STATUS
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS
PeiRamBootEntry (
    IN EFI_FFS_FILE_HEADER  *FfsHeader,
    IN EFI_PEI_SERVICES     **PeiServices
)
{
    EFI_STATUS          Status;
    EFI_BOOT_MODE       BootMode;

    Status = (*PeiServices)->GetBootMode (PeiServices, &BootMode);
    if (EFI_ERROR(Status)) return Status;
    if ((BootMode == BOOT_IN_RECOVERY_MODE) || \
        (BootMode == BOOT_ON_FLASH_UPDATE) || \
        (BootMode == BOOT_ON_S3_RESUME)) return EFI_SUCCESS;

    Status = (*PeiServices)->NotifyPpi ( PeiServices, \
                                         PeiRamBootMemoryReadyNotify );
    Status = (*PeiServices)->NotifyPpi ( PeiServices, \
                                         PeiRamBootEndOfPeiNotify );

    return EFI_SUCCESS;
}
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