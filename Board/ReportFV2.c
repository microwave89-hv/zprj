//**********************************************************************
//**********************************************************************
//**                                                                  **
//**        (C)Copyright 1985-2010, American Megatrends, Inc.         **
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
// $Header: /Alaska/Projects/Intel/Haswell/LynxPoint_SharkBay-DT_Crb_1AQQW/Board/ReportFV2.c 2     10/25/12 9:20a Wesleychen $
//
// $Revision: 2 $
//
// $Date: 10/25/12 9:20a $
//**********************************************************************
// Revision History
// ----------------
// $Log: /Alaska/Projects/Intel/Haswell/LynxPoint_SharkBay-DT_Crb_1AQQW/Board/ReportFV2.c $
// 
// 2     10/25/12 9:20a Wesleychen
// Update Board to 4.6.5.4_Board_31.
// 
// 1     2/24/12 7:59a Victortu
// [TAG]  		EIPEIP71398
// [Category]  	Bug Fix
// [Severity]  	Normal
// [Symptom]  	BIOS Crisis Recovery halt on F1/3b very long time if
// LZMA_SUPPORT = 1
// [Solution]  	Make sure all recovery-related FFS are outside of nested
// FV and do not publish it.
// 
// 11    8/16/12 12:30p Artems
// [TAG]  		EIP N/A
// [Category]  	Improvement
// [Description]  	Added OEM hook to PublishNestedFv function
// [Files]  		Board.sdl Board.mak ReportFv2.c
// 
// 10    8/03/12 5:26p Artems
// [TAG]  		EIP N/A
// [Category]  	Bug Fix
// [Severity]  	Critical
// [Symptom]  	System hangs randomly
// [RootCause]  	Rom layout section beginning is marked with unique GUID.
// However same GUID defined in code also, which leads to presence
// of two instances of the GUID in ROM file. Depending on which
// will be picked system hangs as underlying data can be incorrect
// [Solution]  	Added additional verification of validity of ROM layout
// section
// [Files]  		ReportFV2.c
// 
// 9     11/11/11 3:19p Artems
// Publish ROM layout hob on recovery boot path
// Add verification of parent of nested FV
// 
// 8     11/01/11 4:34p Artems
// Enaabled CheckBeforePublishing for Core 4.6.5.2 compatibility.
// 
// 7     10/05/11 5:25p Artems
// Disabled CheckBeforePublishing for Core 4.6.5.1 compatibility.
// 
// 6     10/05/11 4:49p Artems
// EIP 65805 - fixed problem with too many FVs published on recovery boot
// path
// 
// 5     3/23/11 12:27p Artems
// Enhancement - do not terminate publishing of FVs when corrupted volume
// encountered
// 
// 4     3/04/11 4:15p Artems
// Moved publishing of nested FV to DxeIpl stage for performance reasons
// 
// 3     2/15/11 12:38p Artems
// Added RomLayoutHob publishing
// 
// 2     2/07/11 5:22p Artems
// EIP 53374: Coding standard changes - replaced tabs with spaces, added
// functions headers
// 
// 1     2/04/11 7:56p Artems
// 
// 6     1/13/10 2:13p Felixp
// 
//**********************************************************************
//<AMI_FHDR_START>
//
// Name:  ReportFv.c
//
// Description: Implementation of flexible ROM layout infrastructure support
//
//<AMI_FHDR_END>
//**********************************************************************

#include <Token.h>
#include <AmiPeiLib.h>
#include <AmiHobs.h>
#include <RomLayout.h>
#include <Ppi/FirmwareVolumeInfo.h>

#define ROM_LAYOUT_FFS_GUID \
    { 0x0DCA793A, 0xEA96, 0x42d8, 0xBD, 0x7B, 0xDC, 0x7F, 0x68, 0x4E, 0x38, 0xC1 }

#define ROM_LAYOUT_SECTION_GUID \
    { 0x88A15A4F, 0x977D, 0x4682, 0xB1, 0x7C, 0xDA, 0x1F, 0x31, 0x6C, 0x1F, 0x32 }

#define NULL_GUID \
    { 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0 }

typedef struct _ROM_LAYOUT_SECTION {
    EFI_GUID FfsGuid;
    UINT8 Reserved[12];
    EFI_GUID SectionGuid;
    ROM_AREA Layout[1];
} ROM_LAYOUT_SECTION;

static EFI_GUID NullGuid = NULL_GUID;
static EFI_GUID RomLayoutFfsGuid = ROM_LAYOUT_FFS_GUID;
static EFI_GUID RomLayoutSectionGuid = ROM_LAYOUT_SECTION_GUID;
static EFI_GUID gEfiFirmwareVolumeInfoPpiGuid = EFI_PEI_FIRMWARE_VOLUME_INFO_PPI_GUID;

typedef BOOLEAN (PROCESS_FV_BEFORE_PUBLISHING)(
    IN EFI_PEI_SERVICES **PeiServices, IN OUT ROM_AREA *Area, IN UINT32 FvType
);
typedef BOOLEAN (PROCESS_DXEFV_IN_DXEIPL)(
    IN EFI_PEI_SERVICES **PeiServices, IN OUT ROM_AREA *Area
);

extern PROCESS_FV_BEFORE_PUBLISHING ProcessFvBeforePublishing EndOfFvHookList1;
extern PROCESS_DXEFV_IN_DXEIPL ProcessDxeFvInDxeIpl EndOfFvHookList2;

PROCESS_FV_BEFORE_PUBLISHING* ProcessFvBeforePublishingList[]=
    { ProcessFvBeforePublishing NULL };
PROCESS_DXEFV_IN_DXEIPL* ProcessDxeFvInDxeIplList[]=
    { ProcessDxeFvInDxeIpl NULL };

typedef EFI_STATUS (PROCESS_NESTED_FV_BEFORE_PUBLISHING)(
    IN EFI_PEI_SERVICES **PeiServices, 
    IN OUT ROM_AREA *Area,
    OUT EFI_FIRMWARE_VOLUME_HEADER **Fv, 
    OUT EFI_FIRMWARE_VOLUME_HEADER **NewFv, 
    OUT EFI_FFS_FILE_HEADER **Nfv  
);

extern PROCESS_NESTED_FV_BEFORE_PUBLISHING ProcessNestedFvBeforePublishing EndOfFvHookList3;
PROCESS_NESTED_FV_BEFORE_PUBLISHING* ProcessNestedFvBeforePublishingList[]=
    { ProcessNestedFvBeforePublishing NULL };
//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   ProcessFvBeforePublishingHook
//
// Description: Porting hook to support OEM-specific FV validation control flow
//
// Input:       IN EFI_PEI_SERVICES **PeiServices - pointer to PEI services
//              IN OUT ROM_AREA *Area - pointer to ROM Area, which contains FV
//                                      to be processed
//              IN UINT32 FvType - FV type
//
// Output:      TRUE if validation is passed, FALSE otherwise
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS ProcessNestedFvBeforePublishingHook(
    IN      EFI_PEI_SERVICES            **PeiServices, 
    IN OUT  ROM_AREA                    *Area,
    OUT     EFI_FIRMWARE_VOLUME_HEADER  **Fv,
    OUT     EFI_FIRMWARE_VOLUME_HEADER  **NewFv,
    OUT     EFI_FFS_FILE_HEADER         **Nfv)
{
    UINTN i;
    EFI_STATUS  Status = EFI_NOT_FOUND;

    for(i = 0; ProcessNestedFvBeforePublishingList[i] && EFI_ERROR(Status); i++)
        Status = ProcessNestedFvBeforePublishingList[i](PeiServices, Area, Fv, NewFv, Nfv);

    return Status;
}
//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   ProcessFvBeforePublishingHook
//
// Description: Porting hook to support OEM-specific FV validation control flow
//
// Input:       IN EFI_PEI_SERVICES **PeiServices - pointer to PEI services
//              IN OUT ROM_AREA *Area - pointer to ROM Area, which contains FV
//                                      to be processed
//              IN UINT32 FvType - FV type
//
// Output:      TRUE if validation is passed, FALSE otherwise
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
BOOLEAN ProcessFvBeforePublishingHook(
    IN EFI_PEI_SERVICES **PeiServices, 
    IN OUT ROM_AREA *Area, 
    IN UINT32 FvType)
{
    UINTN i;
    BOOLEAN Result = TRUE;
    for(i=0; ProcessFvBeforePublishingList[i] && Result; i++) 
        Result = ProcessFvBeforePublishingList[i](PeiServices, Area, FvType);
    return Result;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   ProcessDxeFvInDxeIplHook
//
// Description: Porting hook to support OEM-specific FV validation control flow
//              before passing control to DXE
//
// Input:       IN EFI_PEI_SERVICES **PeiServices - pointer to PEI services
//              IN OUT ROM_AREA *Area - pointer to ROM Area, which contains FV
//                                      to be processed
//
// Output:      TRUE if validation is passed, FALSE otherwise
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
BOOLEAN ProcessDxeFvInDxeIplHook(
    IN EFI_PEI_SERVICES **PeiServices, 
    IN OUT ROM_AREA *Area)
{
    UINTN i;
    BOOLEAN Result = TRUE;
    for(i=0; ProcessDxeFvInDxeIplList[i] && Result; i++) 
        Result = ProcessDxeFvInDxeIplList[i](PeiServices, Area);
    return Result;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   EfiReadSection
//
// Description: Function to read section of specific type from given FFS file
//
// Input:       IN EFI_PEI_SERVICES **ppPS - pointer to PEI services
//              IN EFI_SECTION_TYPE SectionType - type of section to read
//              IN EFI_FFS_FILE_HEADER *pFile - pointer to FFS file to read from
//              OUT VOID **ppData - pointer for output buffer
//
// Output:      EFI_SUCCESS if reading completed successfully
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS EfiReadSection(
    IN EFI_PEI_SERVICES **ppPS, 
    IN EFI_SECTION_TYPE SectionType,
    IN EFI_FFS_FILE_HEADER *pFile, 
    OUT VOID **ppData)
{
    EFI_STATUS Status;
    UINT32 SrcSize, DstSize, TmpSize;
    VOID *pSrc;
    EFI_PHYSICAL_ADDRESS DstAddress;
    EFI_HOB_HANDOFF_INFO_TABLE *pHob;
    EFI_COMPRESSION_SECTION_HEADER *pCs;

    if (!ppData) 
        return EFI_INVALID_PARAMETER;

    //TODO: Support for GUIDed sections
    Status = (*ppPS)->FfsFindSectionData(ppPS, SectionType, pFile, &pSrc);
    if (!EFI_ERROR(Status)) {
        *ppData = pSrc; 
        return Status; 
    }

    Status = (*ppPS)->FfsFindSectionData(ppPS, EFI_SECTION_COMPRESSION, pFile, &pCs);
    if (EFI_ERROR(Status)) 
        return Status;

    SrcSize = FVSECTION_SIZE(pCs) - sizeof(EFI_COMPRESSION_SECTION_HEADER);
    pSrc = pCs + 1;
    if (pCs->CompressionType != EFI_NOT_COMPRESSED) {
        GET_INFO GetInfoPtr;
        DECOMPRESS DecompressPtr;
        BOOLEAN KnownCompressionType;

        KnownCompressionType = GetDecompressInterface(pCs->CompressionType, &GetInfoPtr, &DecompressPtr);
        if (!KnownCompressionType) 
            return EFI_UNSUPPORTED;

        Status = GetInfoPtr(pSrc, SrcSize, &DstSize, &TmpSize);
        if (EFI_ERROR(Status)) 
            return Status;

        //No FreePool, so the memory is never freed
        Status = (*ppPS)->AllocatePages(ppPS, EfiBootServicesCode,( DstSize >> 12) + 1, &DstAddress);
        if (EFI_ERROR(Status)) 
            return Status;

        (*ppPS)->GetHobList(ppPS,&pHob);
        if (pHob->EfiFreeMemoryTop - pHob->EfiFreeMemoryBottom <  TmpSize)
            return EFI_OUT_OF_RESOURCES;

        Status = DecompressPtr(pSrc, SrcSize, (VOID*)DstAddress, DstSize, (VOID*)pHob->EfiFreeMemoryBottom, TmpSize);
        if (EFI_ERROR(Status)) 
            return Status;

        pSrc = (VOID*)(UINTN)DstAddress;
    }

    do {
        if (((EFI_COMMON_SECTION_HEADER*)pSrc)->Type == SectionType) {
            *ppData = (EFI_COMMON_SECTION_HEADER*)pSrc+1;
            return EFI_SUCCESS;
        }

        TmpSize = FVSECTION_SIZE(pSrc);
        TmpSize += (4 - (TmpSize & 3)) & 3;
        if (TmpSize>=DstSize) 
            return EFI_NOT_FOUND;

        DstSize -= TmpSize;
        pSrc =  (UINT8*)pSrc + TmpSize;
    }while(TRUE);
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   GetRomLayout
//
// Description: Function to read ROM_LAYOUT data from FFS file
//
// Input:       IN EFI_PEI_SERVICES **PeiServices - pointer to PEI services
//              OUT ROM_AREA **Layout - pointer to output buffer
//
// Output:      EFI_SUCCESS if ROM layout is retrieved
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS GetRomLayout(
    IN  EFI_PEI_SERVICES **PeiServices,
    OUT ROM_AREA         **Layout
)
{
    EFI_STATUS Status;
    EFI_FIRMWARE_VOLUME_HEADER *BootFv;
    EFI_FFS_FILE_HEADER *File = NULL;
    ROM_LAYOUT_SECTION *Section;

    Status = (*PeiServices)->FfsFindNextVolume(PeiServices, 0, &BootFv);
    if (EFI_ERROR(Status)) 
        return Status;

    do {
        Status = (*PeiServices)->FfsFindNextFile(PeiServices, EFI_FV_FILETYPE_FREEFORM, BootFv, &File);
        if (!EFI_ERROR(Status) && !guidcmp(&(File->Name), &RomLayoutFfsGuid)) {
            break;
        }
    } while(Status == EFI_SUCCESS);

    if (EFI_ERROR(Status)) 
        return Status;

    Section = (ROM_LAYOUT_SECTION *)File;

    *Layout = Section->Layout;
    return EFI_SUCCESS;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   GetRomLayout
//
// Description: Function to read ROM_LAYOUT data from given data buffer
//
// Input:       IN EFI_PEI_SERVICES **PeiServices - pointer to PEI services
//              OUT ROM_AREA **Layout - pointer to output buffer
//              IN  VOID *RecoveryCapsule - pointer to data buffer to read from
//
// Output:      EFI_SUCCESS if ROM layout is retrieved
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS GetRecoveryRomLayout(
    IN  EFI_PEI_SERVICES **PeiServices,
    OUT ROM_AREA         **Layout,
    IN  VOID             *RecoveryCapsule
)
{
    UINT32 Signature;
    UINT32 *SearchPointer;
    ROM_LAYOUT_SECTION *Section;

    SearchPointer = (UINT32 *)((UINT8 *)RecoveryCapsule - sizeof(EFI_GUID) + FLASH_SIZE);
    Signature = RomLayoutFfsGuid.Data1;

    do {
        if(*SearchPointer == Signature) {
            Section = (ROM_LAYOUT_SECTION *)SearchPointer;
            if(!guidcmp(&RomLayoutFfsGuid, &(Section->FfsGuid)) &&
               !guidcmp(&RomLayoutSectionGuid, &(Section->SectionGuid))) {
                *Layout = Section->Layout;
                return EFI_SUCCESS;
            }
        }
    } while(SearchPointer-- != RecoveryCapsule);

    return EFI_NOT_FOUND;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   VerifyFwVolume
//
// Description: Function to verify that FV is not corrupted
//
// Input:       IN EFI_PEI_SERVICES **PeiServices - pointer to PEI services
//              IN EFI_FIRMWARE_VOLUME_HEADER *Fv - pointer to FV to verify
//
// Output:      EFI_SUCCESS if verification passed
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS VerifyFwVolume(
    IN EFI_PEI_SERVICES **PeiServices,
    IN EFI_FIRMWARE_VOLUME_HEADER *Fv
)
{
    return EFI_SUCCESS;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   CreateFvHob
//
// Description: Function to create FV hob for given ROM layout unit
//
// Input:       IN EFI_PEI_SERVICES **PeiServices - pointer to PEI services
//              IN ROM_AREA *Area - pointer to ROM layout unit to process
//
// Output:      EFI_SUCCESS if Hob created successfully
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS CreateFvHob(
    IN EFI_PEI_SERVICES **PeiServices,
    IN ROM_AREA         *Area
)
{
    EFI_STATUS Status;
    EFI_HOB_FIRMWARE_VOLUME *FVHob;

    Status = (*PeiServices)->CreateHob(
                                PeiServices, 
                                EFI_HOB_TYPE_FV,
                                sizeof(EFI_HOB_FIRMWARE_VOLUME),
                                &FVHob);
    if (EFI_ERROR(Status)) 
        return Status;

    FVHob->BaseAddress = Area->Address;
    FVHob->Length = (UINT64)Area->Size;

    return EFI_SUCCESS;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   CreateFvHob2
//
// Description: Function to create FV hob type 2 for given ROM layout unit
//
// Input:       IN EFI_PEI_SERVICES **PeiServices - pointer to PEI services
//              IN ROM_AREA *Area - pointer to ROM layout unit to process
//              IN EFI_GUID *FvName - pointer to FV name
//              IN EFI_GUID *FfsName - pointer to parent FFS file
//
// Output:      EFI_SUCCESS if Hob created successfully
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS CreateFvHob2(
    IN EFI_PEI_SERVICES **PeiServices,
    IN ROM_AREA         *Area,
    IN EFI_GUID         *FvName,
    IN EFI_GUID         *FfsName
)
{
    EFI_STATUS Status;
    EFI_HOB_FIRMWARE_VOLUME2 *FVHob;

    Status = (*PeiServices)->CreateHob(
                                PeiServices, 
                                EFI_HOB_TYPE_FV2,
                                sizeof(EFI_HOB_FIRMWARE_VOLUME2),
                                &FVHob);
    if (EFI_ERROR(Status)) 
        return Status;

    FVHob->BaseAddress = Area->Address;
    FVHob->Length = (UINT64)Area->Size;
    FVHob->FvName = *FvName;
    FVHob->FileName = *FfsName;

    return EFI_SUCCESS;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   CheckBeforePublishing
//
// Description: Function to verify if FvPPI should be installed.
//              On recovery only PPI for FV with DXE_CORE FFS should be installed 
//              from recovery capsule
//
// Input:       IN EFI_PEI_SERVICES **PeiServices - pointer to PEI services
//              IN EFI_FIRMWARE_VOLUME_HEADER *Fv - pointer to FV to check
//
// Output:      EFI_SUCCESS if FV should be published, EFI_ERROR otherwise
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS CheckBeforePublishing(
    IN EFI_PEI_SERVICES           **PeiServices,
    IN EFI_FIRMWARE_VOLUME_HEADER *Fv
)
{
    EFI_STATUS Status;
    RECOVERY_IMAGE_HOB *RecoveryHob;
    EFI_FFS_FILE_HEADER *File = NULL;
    static EFI_GUID RecoveryHobGuid = AMI_RECOVERY_IMAGE_HOB_GUID;

//check if we are on recovery boot path, with recovery capsule already loaded

    Status = (*PeiServices)->GetHobList(PeiServices, &RecoveryHob);
    if(EFI_ERROR(Status))
        return EFI_SUCCESS;     //we are not on recovery boot path

    Status = FindNextHobByGuid(&RecoveryHobGuid, &RecoveryHob);
    if(EFI_ERROR(Status))
        return EFI_SUCCESS;     //we are not on recovery boot path

    if(RecoveryHob->Status == EFI_SUCCESS && RecoveryHob->Address != NULL) { //we're on recovery boot path
        Status = (*PeiServices)->FfsFindNextFile(PeiServices, EFI_FV_FILETYPE_DXE_CORE, Fv, &File);
        return Status;
    }

    return EFI_SUCCESS;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   CreateFvInfoPpi
//
// Description: Function to install FwVolume info PPI for given ROM layout unit
//
// Input:       IN EFI_PEI_SERVICES **PeiServices - pointer to PEI services
//              IN ROM_AREA *Area - pointer to ROM layout unit to process
//              IN EFI_GUID *FvName - pointer to parent FV name
//              IN EFI_GUID *FfsName - pointer to parent FFS file
//
// Output:      EFI_SUCCESS if PPI installed
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS CreateFvInfoPpi(
    IN EFI_PEI_SERVICES **PeiServices,
    IN ROM_AREA         *Area,
    IN EFI_GUID         *FvName OPTIONAL,
    IN EFI_GUID         *FfsName OPTIONAL
)
{
    EFI_STATUS Status;

    EFI_PEI_PPI_DESCRIPTOR *FirmwareVolume;
    EFI_PEI_FIRMWARE_VOLUME_INFO_PPI *FirmwareVolumeInfo;

    Status = CheckBeforePublishing(PeiServices, (EFI_FIRMWARE_VOLUME_HEADER*)Area->Address);
    if(EFI_ERROR(Status))
        return EFI_VOLUME_FULL;

    Status = (*PeiServices)->AllocatePool(
                                PeiServices,
                                sizeof(EFI_PEI_PPI_DESCRIPTOR) + sizeof(EFI_PEI_FIRMWARE_VOLUME_INFO_PPI),
                                &FirmwareVolume);
    if(EFI_ERROR(Status))
        return EFI_VOLUME_FULL;

    FirmwareVolumeInfo = (EFI_PEI_FIRMWARE_VOLUME_INFO_PPI*)(FirmwareVolume + 1);

    FirmwareVolumeInfo->FvFormat = ((EFI_FIRMWARE_VOLUME_HEADER*)Area->Address)->FileSystemGuid;
    FirmwareVolumeInfo->FvInfo = (VOID *)(UINTN)Area->Address;
    FirmwareVolumeInfo->FvInfoSize = Area->Size;
    FirmwareVolumeInfo->ParentFvName = FvName;
    FirmwareVolumeInfo->ParentFileName = FfsName;


    FirmwareVolume->Ppi =   FirmwareVolumeInfo;
    FirmwareVolume->Flags = EFI_PEI_PPI_DESCRIPTOR_PPI | EFI_PEI_PPI_DESCRIPTOR_TERMINATE_LIST;
    FirmwareVolume->Guid =  &gEfiFirmwareVolumeInfoPpiGuid;
  
    return (*PeiServices)->InstallPpi(PeiServices, FirmwareVolume);
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   FindFvHob
//
// Description: Function to find FV Hob for corresponding ROM layout unit
//
// Input:       IN EFI_PEI_SERVICES **PeiServices - pointer to PEI services
//              IN ROM_AREA *Area - pointer to ROM layout unit to find matching Hob
//              OUT EFI_HOB_FIRMWARE_VOLUME **FvHob - pointer to output buffer
//
// Output:      EFI_SUCCESS if corresponding Hob found
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS FindFvHob(
    IN  EFI_PEI_SERVICES **PeiServices, 
    IN  ROM_AREA *Area,
    OUT EFI_HOB_FIRMWARE_VOLUME **FvHob
)
{
    EFI_HOB_FIRMWARE_VOLUME *FvHob2;

    (*PeiServices)->GetHobList(PeiServices, FvHob);

    FvHob2 = *FvHob;
    while(!EFI_ERROR(FindNextHobByType(EFI_HOB_TYPE_FV, FvHob))){
        if ((*FvHob)->BaseAddress == Area->Address) 
            return EFI_SUCCESS;
    }

    while(!EFI_ERROR(FindNextHobByType(EFI_HOB_TYPE_FV2, &FvHob2))){
        if (FvHob2->BaseAddress == Area->Address) {
            *FvHob = FvHob2;
            return EFI_SUCCESS;
        }
    }
    return EFI_NOT_FOUND;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   RemoveFvHob
//
// Description: Function to remove FV Hob for corresponding ROM layout unit
//
// Input:       IN EFI_PEI_SERVICES **PeiServices - pointer to PEI services
//              IN ROM_AREA *Area - pointer to ROM layout unit to remove matching Hob
//                                  or NULL to remove all FV Hobs
//
// Output:      None
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID RemoveFvHob(
    IN EFI_PEI_SERVICES **PeiServices,
    IN ROM_AREA         *Area OPTIONAL
)
{
    EFI_STATUS Status;
    EFI_HOB_FIRMWARE_VOLUME *FvHob;
    EFI_HOB_FIRMWARE_VOLUME2 *FvHob2;

    if(Area == NULL) { //delete all Fv hobs
        (*PeiServices)->GetHobList(PeiServices, &FvHob);
        FvHob2 = (EFI_HOB_FIRMWARE_VOLUME2 *)FvHob;
        while(!EFI_ERROR(FindNextHobByType(EFI_HOB_TYPE_FV, &FvHob))) {
            FvHob->Header.HobType = EFI_HOB_TYPE_UNUSED;
        }

        while(!EFI_ERROR(FindNextHobByType(EFI_HOB_TYPE_FV2, &FvHob2))) {
            FvHob2->Header.HobType = EFI_HOB_TYPE_UNUSED;
        }
    } else {
        Status = FindFvHob(PeiServices, Area, &FvHob);
        if(!EFI_ERROR(Status))
            FvHob->Header.HobType = EFI_HOB_TYPE_UNUSED;
    }
    return;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   PublishFv
//
// Description: Function to publish Firmware Volume for corresponding ROM layout unit
//
// Input:       IN EFI_PEI_SERVICES **PeiServices - pointer to PEI services
//              IN ROM_AREA *Area - pointer to ROM layout unit describing FV
//              IN BOOLEAN Nested - TRUE if published FV is nested, FALSE otherwise
//
// Output:      EFI_SUCCESS if FV published successfully
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS PublishFv(
    IN EFI_PEI_SERVICES **PeiServices,
    IN ROM_AREA         *Area,
    IN BOOLEAN          Nested
)
{
    EFI_FIRMWARE_VOLUME_HEADER *Fv;
    EFI_STATUS Status = EFI_SUCCESS;

    if(!ProcessFvBeforePublishingHook(PeiServices, Area, Area->Attributes))
        return EFI_VOLUME_CORRUPTED;

    Fv = (EFI_FIRMWARE_VOLUME_HEADER*)Area->Address;
    if(Fv->Signature != FV_SIGNATURE)
        return EFI_VOLUME_CORRUPTED;

    if(Area->Attributes & ROM_AREA_FV_VERIFY)
        Status = VerifyFwVolume(PeiServices, Fv);
    
    if(EFI_ERROR(Status) || Nested) //for nested FV PublishNestedFv will call CreateFvInfoPpi and CreateHob
        return Status;

    Status = CreateFvHob(PeiServices, Area);
    if(EFI_ERROR(Status))
        return Status;

#if PI_SPECIFICATION_VERSION >= 0x00010000
    Status = CreateFvInfoPpi(PeiServices, Area, NULL, NULL);
#endif

    return Status;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   InitRecovery
//
// Description: Function to initialize recovery process
//
// Input:       IN EFI_PEI_SERVICES **PeiServices - pointer to PEI services
//
// Output:      None
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID InitRecovery(
    IN EFI_PEI_SERVICES **PeiServices
)
{
    static EFI_GUID RecoveryBootModeGuid = EFI_PEI_BOOT_IN_RECOVERY_MODE_PEIM_PPI;
    static EFI_PEI_PPI_DESCRIPTOR RecoveryModePpi = {
        EFI_PEI_PPI_DESCRIPTOR_PPI | EFI_PEI_PPI_DESCRIPTOR_TERMINATE_LIST,
        &RecoveryBootModeGuid, NULL
    };

    EFI_BOOT_MODE BootMode;
    EFI_STATUS Status;

    Status = (*PeiServices)->GetBootMode(PeiServices, &BootMode);

    if(EFI_ERROR(Status) || (BootMode != BOOT_IN_RECOVERY_MODE)) {
        (*PeiServices)->SetBootMode(PeiServices, BOOT_IN_RECOVERY_MODE);
        (*PeiServices)->InstallPpi(PeiServices, &RecoveryModePpi);
        PEI_PROGRESS_CODE(PeiServices, PEI_RECOVERY_AUTO);
    }
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   ReportFV2Pei
//
// Description: Function to publish PEI Firmware Volumes early in PEI phase
//
// Input:       IN EFI_FFS_FILE_HEADER *FfsHeader - pointer to image FFS file
//              IN EFI_PEI_SERVICES **PeiServices - pointer to PEI services
//
// Output:      EFI_SUCCESS if all FVs published successfully
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS ReportFV2Pei(
    IN EFI_FFS_FILE_HEADER *FfsHeader,
    IN EFI_PEI_SERVICES **PeiServices
)
{
    ROM_AREA *Area;
    EFI_STATUS Status;
    ROM_AREA Current;

    Status = GetRomLayout(PeiServices, &Area);

    while(Area->Size != 0) {
        Current = *Area;
        if(Area->Attributes & ROM_AREA_FV_PEI) {
            Status = PublishFv(PeiServices, &Current, FALSE);
            if(EFI_ERROR(Status) && !(Area->Attributes & ROM_AREA_FV_NON_CRITICAL)) {
                InitRecovery(PeiServices);
            }
        }
        Area++;
    }
    return EFI_SUCCESS;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   RelocateFv
//
// Description: Function to relocate Firmware Volume into memory for corresponding 
//              ROM layout unit
//
// Input:       IN EFI_PEI_SERVICES **PeiServices - pointer to PEI services
//              IN ROM_AREA *Area - pointer to ROM layout unit describing FV
//
// Output:      EFI_SUCCESS if FV relocated successfully
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS RelocateFv(
    IN EFI_PEI_SERVICES **PeiServices,
    IN ROM_AREA         *Area
)
{
    EFI_STATUS Status;
    EFI_PHYSICAL_ADDRESS Dest;
    UINTN Pages;

    Pages = EFI_SIZE_TO_PAGES(Area->Size);
    Status = (*PeiServices)->AllocatePages(PeiServices, EfiBootServicesData, Pages, &Dest);
    if(EFI_ERROR(Status))
        return Status;

    MemCpy((VOID *)(UINTN)Dest, (VOID *)(UINTN)Area->Address, Area->Size);
    Area->Address = Dest;
    return Status;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   PublishNestedFv
//
// Description: Function to publish Nested Firmware Volume for corresponding ROM layout unit
//
// Input:       IN EFI_PEI_SERVICES **PeiServices - pointer to PEI services
//              IN ROM_AREA *Area - pointer to ROM layout unit describing FV
//
// Output:      EFI_SUCCESS if FV published successfully
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS PublishNestedFv(
    IN EFI_PEI_SERVICES **PeiServices,
    IN ROM_AREA         *Area
)
{
    EFI_FIRMWARE_VOLUME_HEADER *Fv;
    EFI_FIRMWARE_VOLUME_HEADER *NewFv;
    EFI_FIRMWARE_VOLUME_EXT_HEADER *ExtFv;
    EFI_FFS_FILE_HEADER *Nfv = NULL;
    ROM_AREA NewArea;
    EFI_STATUS Status;

    Fv = (EFI_FIRMWARE_VOLUME_HEADER*)Area->Address;
    if(Fv->Signature != FV_SIGNATURE)
        return EFI_VOLUME_CORRUPTED;

    Status = ProcessNestedFvBeforePublishingHook(PeiServices, Area, &Fv, &NewFv, &Nfv);
    if(EFI_ERROR(Status)) {
        Status = (*PeiServices)->FfsFindNextFile (PeiServices, EFI_FV_FILETYPE_FIRMWARE_VOLUME_IMAGE, Fv, &Nfv);
        if(EFI_ERROR(Status))
            return Status;

        Status = EfiReadSection(PeiServices, EFI_SECTION_FIRMWARE_VOLUME_IMAGE, Nfv, &NewFv);
        if(EFI_ERROR(Status))
            return Status;
    }

    NewArea.Address = (EFI_PHYSICAL_ADDRESS)(UINTN)NewFv;
    NewArea.Size = (UINT32)NewFv->FvLength;
    NewArea.Type = RomAreaTypeFv;
    NewArea.Attributes = Area->Attributes;

    Status = PublishFv(PeiServices, &NewArea, TRUE);
    if(EFI_ERROR(Status))
        return Status;

    if(NewFv->ExtHeaderOffset == 0) { //no FvName Guid
        Status = CreateFvHob2(PeiServices, &NewArea, &NullGuid, &(Nfv->Name));
    } else {
        ExtFv = (EFI_FIRMWARE_VOLUME_EXT_HEADER *)((UINT8 *)NewFv + NewFv->ExtHeaderOffset);
        Status = CreateFvHob2(PeiServices, &NewArea, &(ExtFv->FvName), &(Nfv->Name));
    }
    if(EFI_ERROR(Status))
        return Status;

#if PI_SPECIFICATION_VERSION >= 0x00010000
    if(Fv->ExtHeaderOffset == 0) { //no FvName Guid
        Status = CreateFvInfoPpi(PeiServices, &NewArea, NULL, &(Nfv->Name));
    } else {
        ExtFv = (EFI_FIRMWARE_VOLUME_EXT_HEADER *)((UINT8 *)Fv + Fv->ExtHeaderOffset);
        Status = CreateFvInfoPpi(PeiServices, &NewArea, &(ExtFv->FvName), &(Nfv->Name));
    }
#endif

    return Status;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   ReportFV2PeiAfterMem
//
// Description: Function to publish PEI Firmware Volumes in PEI phase after
//              memory is available
//
// Input:       IN EFI_FFS_FILE_HEADER *FfsHeader - pointer to image FFS file
//              IN EFI_PEI_SERVICES **PeiServices - pointer to PEI services
//
// Output:      EFI_SUCCESS if all FVs published successfully
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS ReportFV2PeiAfterMem(
    IN EFI_FFS_FILE_HEADER *FfsHeader,
    IN EFI_PEI_SERVICES **PeiServices
)
{
    ROM_AREA *Area;
    EFI_STATUS Status;
    EFI_BOOT_MODE BootMode;
    BOOLEAN CorruptedVolume;
    ROM_AREA Current;

    Status = (*PeiServices)->GetBootMode(PeiServices, &BootMode);
    Status = GetRomLayout(PeiServices, &Area);

    while(Area->Size != 0) {
        Current = *Area;
        CorruptedVolume = FALSE;
        if(Area->Attributes & ROM_AREA_FV_PEI_MEM) {
            Status = PublishFv(PeiServices, &Current, FALSE);
            if(EFI_ERROR(Status) && !(Area->Attributes & ROM_AREA_FV_NON_CRITICAL)) {
                InitRecovery(PeiServices);
                CorruptedVolume = TRUE;
            }
        } else if(Area->Attributes & ROM_AREA_FV_PEI_SHADOW && BootMode != BOOT_ON_S3_RESUME) {
            Status = RelocateFv(PeiServices, &Current);
            if(!EFI_ERROR(Status))
                Status = PublishFv(PeiServices, &Current, FALSE);

            if(EFI_ERROR(Status) && !(Area->Attributes & ROM_AREA_FV_NON_CRITICAL)) {
                InitRecovery(PeiServices);
                CorruptedVolume = TRUE;
            }
        }
/* (EIP71398)>
        if(!CorruptedVolume &&
           Area->Attributes & ROM_AREA_FV_NFV_PRESENT && 
           Area->Attributes & ROM_AREA_FV_PEI_ACCESS && 
           BootMode == BOOT_IN_RECOVERY_MODE) {
            Status = PublishNestedFv(PeiServices, &Current);
            if(EFI_ERROR(Status) && !(Area->Attributes & ROM_AREA_FV_NON_CRITICAL)) {
                InitRecovery(PeiServices);
            }
        }
<(EIP71398) */ 
        Area++;
    }
    return EFI_SUCCESS;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   ReportFV2Dxe
//
// Description: Function to publish PEI Firmware Volumes in PEI phase right before
//              passing control to DXE core
//
// Input:       IN VOID* RecoveryCapsule - pointer to recovery capsule if in Recovery mode
//              IN EFI_PEI_SERVICES **PeiServices - pointer to PEI services
//
// Output:      EFI_SUCCESS if all FVs published successfully
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS ReportFV2Dxe(
    IN VOID* RecoveryCapsule OPTIONAL,
    IN EFI_PEI_SERVICES **PeiServices
)
{
    ROM_AREA *Area;
    EFI_STATUS Status;
    ROM_AREA Current;

    static EFI_GUID AmiRomLayoutHobGuid = AMI_ROM_LAYOUT_HOB_GUID;
    ROM_LAYOUT_HOB *RomLayoutHob;
    UINTN RomLayoutSize;
    UINT8 *RomLayoutStart;

    if(RecoveryCapsule == NULL) {
        Status = GetRomLayout(PeiServices, &Area);
    } else {
        Status = GetRecoveryRomLayout(PeiServices, &Area, RecoveryCapsule);
         if(EFI_ERROR(Status))
            return Status;              //recovery will fail and we will boot from existing ROM
        RemoveFvHob(PeiServices, NULL);
    }

    RomLayoutStart = (UINT8*)Area;

    while(Area->Size != 0) {
        Current = *Area;
        if(RecoveryCapsule != NULL)
            Current.Address = Area->Offset + (UINTN)RecoveryCapsule;
            
        if(Area->Attributes & ROM_AREA_FV_DXE) {
            if((Area->Attributes & ROM_AREA_FV_PEI_ACCESS) && RecoveryCapsule == NULL) {
                if(Area->Attributes & ROM_AREA_FV_NFV_PRESENT) {
                    Status = PublishNestedFv(PeiServices, &Current);
                }
                Area++;
                continue;           //all PEI-related HOBs were processed earlier
            }

            Status = PublishFv(PeiServices, &Current, FALSE);
            
            if(Area->Attributes & ROM_AREA_FV_NFV_PRESENT) {
                Status = PublishNestedFv(PeiServices, &Current);
            }

        } else {
            if((Area->Attributes & ROM_AREA_FV_PEI_ACCESS) && RecoveryCapsule == NULL) {
                RemoveFvHob(PeiServices, Area);
            }
        }
        Area++;
    }

    // Create a HOB for the entire ROM layout defined in the RomLayout Variable
    RomLayoutSize = (UINT8*)(Area + 1) - RomLayoutStart;
    Status = (*PeiServices)->CreateHob(PeiServices, 
                                       EFI_HOB_TYPE_GUID_EXTENSION,
                                       sizeof(ROM_LAYOUT_HOB) + RomLayoutSize,
                                       &RomLayoutHob);
    if (!EFI_ERROR(Status)) {
        RomLayoutHob->Header.Name = AmiRomLayoutHobGuid;
        MemCpy(RomLayoutHob + 1, RomLayoutStart, RomLayoutSize);
    }

    return EFI_SUCCESS;    
}    


//**********************************************************************
//**********************************************************************
//**                                                                  **
//**        (C)Copyright 1985-2010, American Megatrends, Inc.         **
//**                                                                  **
//**                       All Rights Reserved.                       **
//**                                                                  **
//**      5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093        **
//**                                                                  **
//**                       Phone: (770)-246-8600                      **
//**                                                                  **
//**********************************************************************
//**********************************************************************