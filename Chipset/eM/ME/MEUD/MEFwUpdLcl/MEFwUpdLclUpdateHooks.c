//*************************************************************************
//*************************************************************************
//**                                                                     **
//**        (C)Copyright 1985-2015, American Megatrends, Inc.            **
//**                                                                     **
//**                       All Rights Reserved.                          **
//**                                                                     **
//**      5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093           **
//**                                                                     **
//**                       Phone: (770)-246-8600                         **
//**                                                                     **
//*************************************************************************
//*************************************************************************
#include <AmiDxeLib.h>
#include <AmiHobs.h>
#include <Capsule.h>
#include <Token.h>
#include <Protocol/Decompress.h>
#include <Protocol/GuidedSectionExtraction.h>
#include <Protocol/AmiPostMgr.h>

#include "MeFwUpdLclProtocol.h"

#define SECTION_SIZE(SectionHeaderPtr) \
    ((UINT32) (*((UINT32 *) ((EFI_COMMON_SECTION_HEADER *) SectionHeaderPtr)->Size) & 0x00ffffff))
#define SIGNATURE_16(A, B)        ((A) | (B << 8))
#define SIGNATURE_32(A, B, C, D)  (SIGNATURE_16 (A, B) | (SIGNATURE_16 (C, D) << 16))

#define EFI_CUSTOMIZED_DECOMPRESS_PROTOCOL_GUID \
  { 0x9a44198e, 0xa4a2, 0x44e6, 0x8a, 0x1f, 0x39, 0xbe, 0xfd, 0xac, 0x89, 0x6f }
#define ME_UPD_LCL_SIGNATURE SIGNATURE_32 ('_', 'M', 'U', 'L')
#define FV_GUID_OFFSET 0x60

extern EFI_GUID gAmiGlobalVariableGuid;
EFI_GUID mMeRegionFfsGuid = \
    { 0xDE90FFA8, 0xB985, 0x4575, 0xAB, 0x8D, 0xAD, 0xE5, 0x2C, 0x36, 0x2C, 0xA3 };
EFI_GUID mMeVersionFfsFileGuid = \
    { 0x0B4AE6BE, 0x6DA6, 0x4908, 0x8A, 0x71, 0x7E, 0x6A, 0x8A, 0x33, 0xB1, 0x1C };
EFI_GUID mMeVersionFfsSectionGuid = \
    { 0x6A6D576A, 0x8F38, 0x45E7, 0x97, 0xC0, 0x8A, 0xCD, 0x9E, 0x99, 0x26, 0x74 };
EFI_GUID mEfiCustomizedDecompressProtocolGuid = \
    { 0X9A44198E, 0XA4A2, 0X44E6, 0X8A, 0X1F, 0X39, 0XBE, 0XFD, 0XAC, 0X89, 0X6F };
static EFI_GUID mAmiPostManagerProtocolGuid = AMI_POST_MANAGER_PROTOCOL_GUID;
static AMI_POST_MANAGER_PROTOCOL *mAmiPostMgr = NULL;
ME_FW_UPD_VERSION  mMeFwImgVersion[] = ME_FW_IMAGE_VERSION;
ME_FW_UPD_VERSION     MbpMeFwVer;

extern UINT8 *RecoveryBuffer;

UINT8*
FvFindFfsFileByGuid (
    UINT8                   *FvAddress,
    EFI_GUID                *pGuid
);

VOID
AutoMeudBeforeReflashHook(
    VOID
);

VOID
AutoMeudAfterReflashHook(
    VOID
);

//<AMI_PHDR_START>
//----------------------------------------------------------------------
// Procedure:   DecompressBinary
//
// Description:
//
// Input:
//
// Output:
//
// Returns:
//
//----------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS
DecompressBinary(
    IN  UINTN               *BinaryBuffer,
    IN  UINTN               BinaryBufferSize,
    OUT UINTN               **DecompressBuffer,
    OUT UINTN               *DecompressBufferSize
    )
{
    EFI_STATUS                              Status;
    EFI_FFS_FILE_HEADER                     *FfsFileHeader = NULL;
    EFI_COMMON_SECTION_HEADER               *SectionHeader = NULL;
    UINTN                                   NvarSize = 0;
    VOID                                    *NvarBuffer = NULL;
    EFI_COMPRESSION_SECTION                 *CompressSection = NULL;
    EFI_GUID_DEFINED_SECTION                *GuidedSection = NULL;
    EFI_DECOMPRESS_PROTOCOL                 *Decompress = NULL;
    EFI_GUIDED_SECTION_EXTRACTION_PROTOCOL  *GuidedExtraction = NULL;
    VOID                                    *CompressionSource = NULL;
    UINT32                                  CompressionSourceSize = 0;
    UINT32                                  UncompressedLength = 0;
    UINT8                                   CompressionType;
    VOID                                    *ScratchBuffer = NULL;
    UINT32                                  ScratchSize = 0;
    VOID                                    *NewBuffer = NULL;
    UINTN                                   NewBufferSize = 0;
    UINT32                                  AuthenticationStatus = 0;

    FfsFileHeader = (EFI_FFS_FILE_HEADER*)BinaryBuffer;
    SectionHeader = (EFI_COMMON_SECTION_HEADER*)((UINT8*)FfsFileHeader + sizeof(EFI_FFS_FILE_HEADER));

    if( FfsFileHeader->Type == EFI_FV_FILETYPE_RAW ) {
        //The binary is the NVRAM ffs without any section,
        //allocate the memory and copy it.

        NvarSize = BinaryBufferSize - sizeof(EFI_FFS_FILE_HEADER);

        Status = pBS->AllocatePool( EfiBootServicesData,
                                    NvarSize,
                                    &NvarBuffer );
        if( EFI_ERROR(Status) )
            return Status;

        MemCpy( NvarBuffer, (VOID*)SectionHeader, NvarSize );

        *DecompressBuffer = NvarBuffer;
        *DecompressBufferSize = NvarSize;

        return EFI_SUCCESS;
    }
    //The binary is the NVRAM ffs with section,
    //determine the section type.

    switch( SectionHeader->Type )
    {
        case EFI_SECTION_COMPRESSION:
            //The section is compressed by PI_STD
            CompressSection = (EFI_COMPRESSION_SECTION*)SectionHeader;

            CompressionSource = (VOID*)((UINT8*)CompressSection + sizeof(EFI_COMPRESSION_SECTION));
            CompressionSourceSize = (UINT32)(SECTION_SIZE(CompressSection) - sizeof(EFI_COMPRESSION_SECTION));
            UncompressedLength = CompressSection->UncompressedLength;
            CompressionType = CompressSection->CompressionType;

            if( UncompressedLength > 0 )
            {
                NewBufferSize = UncompressedLength;

                Status = pBS->AllocatePool( EfiBootServicesData,
                                            NewBufferSize,
                                            &NewBuffer );
                if( EFI_ERROR(Status) )
                    return Status;

                if( CompressionType == EFI_NOT_COMPRESSED )
                {
                    MemCpy( NewBuffer, (VOID*)CompressionSource, NewBufferSize );
                }
                else if ( CompressionType == EFI_STANDARD_COMPRESSION || 
                          CompressionType == EFI_CUSTOMIZED_COMPRESSION )
                {

                    if( CompressionType == EFI_STANDARD_COMPRESSION )
                    {
                        Status = pBS->LocateProtocol(
                                        &gEfiDecompressProtocolGuid,
                                        NULL,
                                        &Decompress );
                    }
                    else
                    {
                        Status = pBS->LocateProtocol(
                                        &mEfiCustomizedDecompressProtocolGuid,
                                        NULL,
                                        &Decompress );
                    }
                    if( EFI_ERROR(Status) )
                    {
                        pBS->FreePool( NewBuffer );
                        return Status;
                    }

                    Status = Decompress->GetInfo( Decompress,
                                                  CompressionSource,
                                                  CompressionSourceSize,
                                                  (UINT32 *)&NewBufferSize,
                                                  &ScratchSize );
                    if( EFI_ERROR(Status) || (NewBufferSize != UncompressedLength))
                    {
                        pBS->FreePool( NewBuffer );
                        if(!EFI_ERROR (Status))
                            Status = EFI_BAD_BUFFER_SIZE;
                        return Status;
                    }

                    Status = pBS->AllocatePool( EfiBootServicesData,
                                                ScratchSize,
                                                &ScratchBuffer );
                    if( EFI_ERROR(Status) )
                    {
                        pBS->FreePool( NewBuffer );
                        return Status;
                    }

                    Status = Decompress->Decompress( Decompress,
                                                     CompressionSource,
                                                     CompressionSourceSize,
                                                     NewBuffer,
                                                     (UINT32)NewBufferSize,
                                                     ScratchBuffer,
                                                     ScratchSize );
                    pBS->FreePool( ScratchBuffer );
                    if( EFI_ERROR(Status) )
                    {
                        pBS->FreePool( NvarBuffer );
                        return Status;
                    }

                    //The decompressed data is the EFI_SECTION_RAW
                    //Add the section header length to get data
                    SectionHeader = (EFI_COMMON_SECTION_HEADER*)NewBuffer;

                    NvarSize = SECTION_SIZE(SectionHeader) - sizeof(EFI_COMMON_SECTION_HEADER);
                    NvarBuffer = (VOID*)((UINT8*)NewBuffer + sizeof(EFI_COMMON_SECTION_HEADER));
                }
            }

            break;

        case EFI_SECTION_GUID_DEFINED:

            //The section is compressed by LZMA
            GuidedSection = (EFI_GUID_DEFINED_SECTION*)SectionHeader;

            Status = pBS->LocateProtocol( &(GuidedSection->SectionDefinitionGuid),
                                          NULL,
                                          &GuidedExtraction );
            if( EFI_ERROR(Status) )
                return Status;

            Status = GuidedExtraction->ExtractSection(
                                        GuidedExtraction,
                                        GuidedSection,
                                        &NewBuffer,
                                        &NewBufferSize,
                                        &AuthenticationStatus );
            if( EFI_ERROR(Status) )
                return Status;

            //The decompressed data is the EFI_SECTION_RAW
            //Add the section header length to get data
            SectionHeader = (EFI_COMMON_SECTION_HEADER*)NewBuffer;

            NvarSize = SECTION_SIZE(SectionHeader) - sizeof(EFI_COMMON_SECTION_HEADER);
            NvarBuffer = (VOID*)((UINT8*)NewBuffer + sizeof(EFI_COMMON_SECTION_HEADER));

            break;

        case EFI_SECTION_RAW:

            //The section is not compressed.
            NvarSize = BinaryBufferSize - (sizeof(EFI_FFS_FILE_HEADER) + sizeof(EFI_COMMON_SECTION_HEADER));

            Status = pBS->AllocatePool( EfiBootServicesData,
                                        NvarSize,
                                        &NvarBuffer );
            if( EFI_ERROR(Status) )
                return Status;

            MemCpy( NvarBuffer, (VOID*)((UINT8*)SectionHeader + sizeof(EFI_COMMON_SECTION_HEADER)), NvarSize );

            break;

        default:

            NvarBuffer = NULL;
            NvarSize = 0;

            break;
    }

    *DecompressBuffer = NvarBuffer;
    *DecompressBufferSize = NvarSize;
    
    return Status;
}
//<AMI_PHDR_START>
//----------------------------------------------------------------------
// Procedure:   MeFwUpdateViaIntelLib
//
// Description:
//
// Input:
//
// Output:
//
// Returns:
//
//----------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS 
MeFwUpdateViaIntelLib(
    IN UINT8                        *pBuffer,
    IN AMI_POST_MANAGER_PROTOCOL    *AmiPostMgr
    )
{
    EFI_STATUS          Status;
    UINTN               *pMeRegionFile, *UcMeBuffer, UcMeBufferSize;
    EFI_GUID            mMeFwUpdLclProtocolGuid = ME_FW_UPD_LOCAL_PROTOCOL_GUID;
    ME_FW_UPDATE_LOCAL_PROTOCOL     *mMeFwUpdateLclProtocol = NULL;
    EFI_FFS_FILE_HEADER *pHdr;

    // Locate ME FW Update Local Protocol.
    Status = pBS->LocateProtocol (&mMeFwUpdLclProtocolGuid, \
                                        NULL, (VOID**)&mMeFwUpdateLclProtocol);
    if(EFI_ERROR(Status) || (pBuffer == NULL)) return Status;
        
    // Check ME is in Normal mode.    
    Status = mMeFwUpdateLclProtocol->MeFwCheckMode(mMeFwUpdateLclProtocol, MeModeNormal);
    if(EFI_ERROR(Status)) return Status;

    // Search the ME FW file from buffer.
    if (((UINT8*)pMeRegionFile = FvFindFfsFileByGuid( \
                            pBuffer, &mMeRegionFfsGuid)) == NULL) return Status;

    // Decompress the ME FW file..
    pHdr = (EFI_FFS_FILE_HEADER*)pMeRegionFile;
    Status = DecompressBinary ( pMeRegionFile, \
                                (UINTN)(*(UINT32*)pHdr->Size & 0xffffff), \
                                &UcMeBuffer, &UcMeBufferSize);
    if (EFI_ERROR(Status)) return Status;

    // Update reflash progress bar only if Secure flash capsule update.
    // Do not display any messages if Windwos Firmware Update Capsule.
    mMeFwUpdateLclProtocol->AmiPostMgr = NULL;
    if (AmiPostMgr != NULL) mMeFwUpdateLclProtocol->AmiPostMgr = AmiPostMgr;
    Status = mMeFwUpdateLclProtocol->FwUpdLcl(mMeFwUpdateLclProtocol, \
                                        (UINT8*)UcMeBuffer, UcMeBufferSize);
    return Status;                                    
}
//<AMI_PHDR_START>
//----------------------------------------------------------------------
// Procedure:   GetFvMeFwRegionAddress
//
// Description:
//
// Input:
//
// Output:
//
// Returns:
//
//----------------------------------------------------------------------
//<AMI_PHDR_END>
UINT8* 
GetFvMeFwRegionAddress(
    UINT8       *StartAddress
    )
{
    EFI_GUID    mMeFwCapsuleFirmwareVolumeGuid = ME_FW_CAPSULE_FIRMWARE_VOLUME_GUID;
    if (!guidcmp((UINT8*)StartAddress + FV_GUID_OFFSET, \
                            &mMeFwCapsuleFirmwareVolumeGuid)) return StartAddress;
    if (!guidcmp((UINT8*)StartAddress + FLASH_SIZE + FV_GUID_OFFSET, \
                &mMeFwCapsuleFirmwareVolumeGuid)) return StartAddress + FLASH_SIZE;
    return NULL;
}
//<AMI_PHDR_START>
//----------------------------------------------------------------------
// Procedure:   FvFindFfsFileByGuid
//
// Description:
//
// Input:
//
// Output:
//
// Returns:
//
//----------------------------------------------------------------------
//<AMI_PHDR_END>
UINT8*
FvFindFfsFileByGuid(
    UINT8                   *FvAddress,
    EFI_GUID                *pGuid
    )
{
    EFI_FFS_FILE_HEADER     *pFfsFile;
    UINT32                  i, FvLength = FLASH_SIZE, FileSize;
    UINT8                   *p = (UINT8*)NULL;
    EFI_GUID EfiFirmwareFileSystem2Guid = EFI_FIRMWARE_FILE_SYSTEM2_GUID;
              
    if ((p = GetFvMeFwRegionAddress(FvAddress)) == NULL) return NULL;
    FvLength = (UINT32)((EFI_FIRMWARE_VOLUME_HEADER*)p)->FvLength;
    for (i = 0; (i + 16) < FvLength; i += 16) {
        if (guidcmp (&((EFI_FIRMWARE_VOLUME_HEADER*)(p + i))->FileSystemGuid, \
                                         &EfiFirmwareFileSystem2Guid)) continue;
        FileSize = ((EFI_FIRMWARE_VOLUME_HEADER*)(p + i))->HeaderLength;
        pFfsFile = (EFI_FFS_FILE_HEADER*)(p + i + FileSize);
        do {
            if (!guidcmp (&((EFI_FFS_FILE_HEADER*)pFfsFile)->Name, pGuid)) {
                return ((UINT8*)pFfsFile);    
            }
            FileSize = *(UINT32 *)pFfsFile->Size & 0x00FFFFFF;
            pFfsFile = (EFI_FFS_FILE_HEADER*)((UINT32)pFfsFile + FileSize);
            pFfsFile = (EFI_FFS_FILE_HEADER*)(((UINT32)pFfsFile + 7) & 0xfffffff8);
         } while(((*(UINT32 *)pFfsFile->Size & 0x00FFFFFF) != 0xFFFFFF) && \
                 ((*(UINT32 *)pFfsFile->Size & 0x00FFFFFF) != 0));
        i += (UINT32)(((EFI_FIRMWARE_VOLUME_HEADER*)(p + i))->FvLength - 16);        
    }        
    return ((UINT8*)NULL);
}
//<AMI_PHDR_START>
//----------------------------------------------------------------------
// Procedure:   CheckMeFirmwareVersion
//
// Description:
//
// Input:
//
// Output:
//
// Returns:
//
//----------------------------------------------------------------------
//<AMI_PHDR_END>
BOOLEAN 
CheckMeFirmwareVersion(
    UINT8       *pFileSection
    )
{
    UINT8                   *p = pFileSection + sizeof(EFI_COMMON_SECTION_HEADER);
    ME_FW_UPD_VERSION       *NewMeFwVer;

    if (guidcmp (p, &mMeVersionFfsSectionGuid)) return FALSE;
    NewMeFwVer = (ME_FW_UPD_VERSION*)(p + sizeof (EFI_GUID));

    // ??? PORTING REQUEST ??? [TO DO] if can't get ME FW version from MBP ??                    
    //    ==== PORTING REQUEST ==== >> 
    if (MbpMeFwVer.MajorVersion != NewMeFwVer->MajorVersion) return FALSE;
    if (MbpMeFwVer.MinorVersion  < NewMeFwVer->MinorVersion) return FALSE;
    if ((UINT32)((NewMeFwVer->HotfixVersion << 16) + NewMeFwVer->BuildVersion) > 
        (UINT32)((MbpMeFwVer.HotfixVersion << 16) + MbpMeFwVer.BuildVersion)) {
        return TRUE;
    }    
    // << ==== PORTING REQUEST ==== 
    return FALSE;
}
//<AMI_PHDR_START>
//----------------------------------------------------------------------
// Procedure:   IsMeFirmawareUpgraded
//
// Description:
//
// Input:
//
// Output:
//
// Returns:
//
//----------------------------------------------------------------------
//<AMI_PHDR_END>
BOOLEAN 
IsMeFirmawareUpgraded(
    EFI_GUID            *pGuid
    )
{
    UINT8           *pFfsFile;
    if ((pFfsFile = FvFindFfsFileByGuid(RecoveryBuffer, pGuid)) == NULL) return FALSE;
    return CheckMeFirmwareVersion (pFfsFile + sizeof(EFI_FFS_FILE_HEADER));
}
//<AMI_PHDR_START>
//----------------------------------------------------------------------
// Procedure:   IsWindowsFwUpdate
//
// Description:
//
// Input:
//
// Output:
//
// Returns:
//
//----------------------------------------------------------------------
//<AMI_PHDR_END>
BOOLEAN
IsWindowsFwUpdate(
    VOID
    )
{
    EFI_STATUS              Status;
    EFI_CAPSULE_HEADER      *Capsule;
    EFI_HOB_UEFI_CAPSULE    *Hob;
    static EFI_GUID ImageCapsuleGuid = W8_SCREEN_IMAGE_CAPSULE_GUID;
    static EFI_GUID HobListGuid = HOB_LIST_GUID;

    if ((Hob = GetEfiConfigurationTable(pST, &HobListGuid)) == NULL) return FALSE;
    do {
        Status = FindNextHobByType(EFI_HOB_TYPE_UEFI_CAPSULE, &Hob);
        if(!EFI_ERROR(Status)) { 
            Capsule = (EFI_CAPSULE_HEADER *)(VOID *)(UINTN)Hob->BaseAddress;
            if(!guidcmp(&(Capsule->CapsuleGuid), &ImageCapsuleGuid)) return TRUE;
        }
    } while(!EFI_ERROR(Status));
    return FALSE;
}
//<AMI_PHDR_START>
//----------------------------------------------------------------------
// Procedure:   AutoMeudBeforeReflashHook
//
// Description:
//
// Input:
//
// Output:
//
// Returns:
//
//----------------------------------------------------------------------
//<AMI_PHDR_END>
VOID
AutoMeudBeforeReflashHook(
    VOID
    )
{
    UINTN           Length = sizeof(ME_FW_UPD_VERSION);
    EFI_STATUS      Status;

    // Save "MeAutoUpdateReq" variable here for avoiding NVRAM could be updated later.
	Status = pRS->GetVariable (L"MbpMeFwVersion", \
                        &gAmiGlobalVariableGuid, NULL, &Length, &MbpMeFwVer);
    if (EFI_ERROR(Status)) MemSet(&MbpMeFwVer, sizeof(ME_FW_UPD_VERSION), 0); 

    // Start ME FW update process here if ME FW Capsule only.
    if (RecoveryBuffer == GetFvMeFwRegionAddress(RecoveryBuffer)) {
        EFI_EVENT event;
        AutoMeudAfterReflashHook();
        if (mAmiPostMgr != NULL) 
            mAmiPostMgr->DisplayInfoBox(L"ME FW update", L"ME FW update completed, Press any key to reset the system", 5, &event);
        pRS->ResetSystem(EfiResetCold, EFI_SUCCESS, 0, NULL);
    }

    return;
}
//<AMI_PHDR_START>
//----------------------------------------------------------------------
// Procedure:   AutoMeudAfterReflashHook
//
// Description:
//
// Input:
//
// Output:
//
// Returns:
//
//----------------------------------------------------------------------
//<AMI_PHDR_END>
VOID
AutoMeudAfterReflashHook(
    VOID
    )
{
    EFI_STATUS          Status = EFI_VOLUME_CORRUPTED;
    UINT32              MeMode;

    if ((mMeFwImgVersion->MajorVersion != 0) && \
        (!IsMeFirmawareUpgraded(&mMeVersionFfsFileGuid))) return ;
    if (!IsWindowsFwUpdate())
        Status = pBS->LocateProtocol(&mAmiPostManagerProtocolGuid, NULL, &mAmiPostMgr);
    // ME FW Update API could returns error "EFI_VOLUME_CORRUPTED" if capsule mode
    // in S3 resume path, so, we set the MeAutoUpdateReq variable to "_MUL" for 
    // trying update ME FW again if error.
    MeMode = ME_UPD_LCL_SIGNATURE;
    Status = MeFwUpdateViaIntelLib (RecoveryBuffer, mAmiPostMgr);
    if (EFI_ERROR(Status))
    {    
        pRS->SetVariable (L"MeAutoUpdateReq",
                          &gAmiGlobalVariableGuid,
                          EFI_VARIABLE_NON_VOLATILE | \
                          EFI_VARIABLE_BOOTSERVICE_ACCESS, \
                          sizeof(UINT32), \
                          &MeMode);
    }
    return;
}
//*************************************************************************
//*************************************************************************
//**                                                                     **
//**        (C)Copyright 1985-2015, American Megatrends, Inc.            **
//**                                                                     **
//**                       All Rights Reserved.                          **
//**                                                                     **
//**      5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093           **
//**                                                                     **
//**                       Phone: (770)-246-8600                         **
//**                                                                     **
//*************************************************************************
//*************************************************************************