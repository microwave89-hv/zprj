//**********************************************************************
//**********************************************************************
//**                                                                  **
//**        (C)Copyright 1985-2010, American Megatrends, Inc.         **
//**                                                                  **
//**                       All Rights Reserved.                       **
//**                                                                  **
//**        5555 Oakbrook Pkwy, Suite 200, Norcross, GA 30093         **
//**                                                                  **
//**                       Phone: (770)-246-8600                      **
//**                                                                  **
//**********************************************************************
//*************************************************************************
// $Header: /Alaska/SOURCE/Modules/TCG2/Common/Tpm20PlatformDxe/Tpm20PlatformDxe.c 4     6/14/14 12:39a Fredericko $
//
// $Revision: 4 $
//
// $Date: 6/14/14 12:39a $
//*************************************************************************
// Revision History
// ----------------
// $Log: /Alaska/SOURCE/Modules/TCG2/Common/Tpm20PlatformDxe/Tpm20PlatformDxe.c $
// 
// 4     6/14/14 12:39a Fredericko
// 
// 3     6/09/14 5:02p Fredericko
// Changes for SetVariable vulnerability during Runtime
// 
// 2     4/25/14 4:44p Fredericko
// when secureboot is disabled
// 
// 1     4/21/14 2:18p Fredericko
// 
// 5     3/17/14 3:26p Fredericko
// 
// 4     3/14/14 3:48p Fredericko
// 
// 3     3/11/14 6:49p Fredericko
// [TAG]  		EIP151925
// [Category]  	New Feature
// [Description]  	Changes for TcgGeneric Regression Testing
// 
// 2     10/09/13 6:32p Fredericko
// 
// 1     10/08/13 12:06p Fredericko
// Initial Check-In for Tpm-Next module
// 
// 5     10/03/13 2:52p Fredericko
// 
// 4     9/16/13 1:37p Fredericko
// TPM 2.0 UEFI preboot fixes. 
// 
// 3     8/30/13 11:03p Fredericko
// 
// 2     7/11/13 6:16p Fredericko
// [TAG]  		EIP120969
// [Category]  	New Feature
// [Description]  	TCG (TPM20).
// 
// 1     7/10/13 5:57p Fredericko
// [TAG]  		EIP120969
// [Category]  	New Feature
// [Description]  	TCG (TPM20)
// 
//*************************************************************************
//<AMI_FHDR_START>
//
// Name:	
//
// Description:	
//
//<AMI_FHDR_END>
//*************************************************************************
#include "Tpm20PlatformDxe.h"
#include <ImageAuthentication.h>
#include <EfiImage.h>
#include <DevicePath.h>
#include <Smbios.h>
#include <DiskIo.h>
#include <BlockIo.h>
#include "Protocol/CpuIo.h"
#include "Protocol/FirmwareVolume.h"
#include "Protocol/DevicePath.h"
#include "AMIPostMgr.h"
#include "Tpm20PlatformDxeStrTokens.h"
#include "TcgPlatformSetupPolicy.h"

#pragma optimize("",off)

#if (defined(TCGMeasureSecureBootVariables) && (TCGMeasureSecureBootVariables != 0))
EFI_GUID gEfiImageSecurityDatabaseguid =  EFI_IMAGE_SECURITY_DATABASE_GUID;
#endif
EFI_GUID AmitcgefiOsVariableGuid       = AMI_TCG_EFI_OS_VARIABLE_GUID;

#define AMI_VALID_BOOT_IMAGE_CERT_TBL_GUID \
    { 0x6683D10C, 0xCF6E, 0x4914, 0xB5, 0xB4, 0xAB, 0x8E, 0xD7, 0x37, 0x0E, 0xD7 }

#define BDS_ALL_DRIVERS_CONNECTED_PROTOCOL_GUID \
        {0xdbc9fd21, 0xfad8, 0x45b0, 0x9e, 0x78, 0x27, 0x15, 0x88, 0x67, 0xcc, 0x93}

EFI_GUID    gBdsAllDriversConnectedProtocolGuid = BDS_ALL_DRIVERS_CONNECTED_PROTOCOL_GUID;
EFI_GUID    gAmiPostManagerProtocolGuid = AMI_POST_MANAGER_PROTOCOL_GUID;

EFI_GUID   gEfiGlobalVariableGuid = EFI_GLOBAL_VARIABLE;

EFI_GUID ZeroGuid = {0,0,0,0,0,0,0,0,0,0,0};

EFI_GUID  gEfiSmbiosTableGuid = EFI_SMBIOS_TABLE_GUID;
EFI_GUID  FlagsStatusguid = AMI_TCG_CONFIRMATION_FLAGS_GUID;

UINTN      mMeasureGptCount = 0;
EFI_TREE_PROTOCOL   *TrEEProtocolInstance = NULL;
static UINT8              PpiRequest;

EFI_HII_HANDLE            gHiiHandle;
AMI_POST_MANAGER_PROTOCOL *pAmiPostMgr = NULL;
EFI_HANDLE PlatformProtocolHandle;
static PERSISTENT_BIOS_TPM_FLAGS  TpmNvflags;

#pragma pack (1)
typedef struct
{
    EFI_PHYSICAL_ADDRESS PostCodeAddress;
    #if x64_BUILD
    UINT64               PostCodeLength;
    #else
    UINTN                PostCodeLength;
    #endif
} EFI_TCG_EV_POST_CODE;

typedef struct
{
    EFI_TCG_PCR_EVENT_HEADER Header;
    EFI_TCG_EV_POST_CODE     Event;
} PEI_EFI_POST_CODE;
#pragma pack()

BOOLEAN CompareGuid(
    EFI_GUID *G1,
    EFI_GUID *G2 );

//
//
// Data Table definition
//
typedef struct _AMI_VALID_CERT_IN_SIG_DB {
  UINT32          SigOffset;
  UINT32          SigLength;
} AMI_VALID_CERT_IN_SIG_DB;


typedef struct _AMI_INTERNAL_HLXE_PROTOCOL  AMI_INTERNAL_HLXE_PROTOCOL;

typedef
EFI_STATUS
(EFIAPI * INTERNAL_HASH_LOG_EXTEND_EVENT) (
  IN  UINT8                  *DataToHash,
  IN  UINT64                  Flags,
  IN  UINTN                   DataSize,
  IN OUT  TCG_PCR_EVENT_HDR   *NewEventHdr,
  IN      UINT8               *NewEventData
);


struct _AMI_INTERNAL_HLXE_PROTOCOL {
	INTERNAL_HASH_LOG_EXTEND_EVENT  InternalHashLogExtend;
};

EFI_STATUS EfiGetSystemConfigurationTable(
    IN  EFI_GUID  *TableGuid,
    OUT VOID      **Table)
{
    *Table = GetEfiConfigurationTable(pST, TableGuid);
    return (*Table == NULL) ? EFI_NOT_FOUND : EFI_SUCCESS;
}



EFI_STATUS
EFIAPI
GetRandomAuthPassword(
	IN     UINT16    RNGValueLength,
	IN OUT UINT8    *RNGValue
  )
{
  EFI_STATUS   Status = EFI_SUCCESS;
  return Status;
}


EFI_STATUS
EFIAPI
TpmRevokeTrust (
  )
{
   EFI_STATUS     Status = EFI_SUCCESS;
   return Status;
}


#define GET_HOB_TYPE( Hob )     ((Hob).Header->HobType)
#define GET_HOB_LENGTH( Hob )   ((Hob).Header->HobLength)
#define GET_NEXT_HOB( Hob )     ((Hob).Raw + GET_HOB_LENGTH( Hob ))
#define END_OF_HOB_LIST( Hob )  (GET_HOB_TYPE( Hob ) == \
                                 EFI_HOB_TYPE_END_OF_HOB_LIST)

//**********************************************************************
//<AMI_PHDR_START>
//
// Procedure:   GetHob
//
// Description: Find instance of a HOB type in a HOB list
//
//
// Input:       IN UINT16  Type,
//              IN VOID    *HobStart
//
// Output:      VOID*
//
// Modified:
//
// Referrals:
//
// Notes:
//<AMI_PHDR_END>
//**********************************************************************
VOID* GetHob(
    IN UINT16 Type,
    IN VOID   *HobStart )
{
    EFI_PEI_HOB_POINTERS Hob;

    Hob.Raw = HobStart;

    //
    // Return input if not found
    //
    if ( HobStart == NULL )
    {
        return HobStart;
    }

    //
    // Parse the HOB list, stop if end of list or matching type found.
    //
    while ( !END_OF_HOB_LIST( Hob ))
    {
        if ( Hob.Header->HobType == Type )
        {
            break;
        }

        Hob.Raw = GET_NEXT_HOB( Hob );
    }

    //
    // Return input if not found
    //
    if ( END_OF_HOB_LIST( Hob ))
    {
        return HobStart;
    }

    return (VOID*)(Hob.Raw);
}



EFI_STATUS
MeasureSeparatorEvent (
  IN  UINT32  PCRIndex
)
{    
    UINT32           EventData;
    TrEE_EVENT       *Tpm20Event=NULL;
    UINT64           Flags = 0;
    EFI_STATUS       Status;

    if(TrEEProtocolInstance == NULL) return EFI_NOT_FOUND;
  
    pBS->AllocatePool(EfiBootServicesData, (sizeof(TrEE_EVENT_HEADER) + \
                      sizeof(UINT32) + sizeof(UINT32)), &Tpm20Event);

    if(Tpm20Event==NULL) return EFI_OUT_OF_RESOURCES;

    EventData = 0;
    Tpm20Event->Size  = sizeof(TrEE_EVENT_HEADER) + sizeof(UINT32) + sizeof(EventData);
    Tpm20Event->Header.HeaderSize = sizeof(TrEE_EVENT_HEADER);
    Tpm20Event->Header.HeaderVersion = 1;
    Tpm20Event->Header.PCRIndex    = PCRIndex;
    Tpm20Event->Header.EventType   = EV_SEPARATOR;

    pBS->CopyMem ((UINT32 *)((UINTN)&Tpm20Event->Event[0]),
                 &EventData,
                 sizeof(UINT32));

    Status = TrEEProtocolInstance->HashLogExtendEvent(TrEEProtocolInstance,
                                           Flags, (EFI_PHYSICAL_ADDRESS)&EventData, (UINT64)sizeof(EventData),
                                           Tpm20Event);

    pBS->FreePool(Tpm20Event);  
    
    return Status;
}



#if (defined(TCGMeasureSecureBootVariables) && (TCGMeasureSecureBootVariables != 0))
EFI_STATUS
MeasureCertificate(UINTN sizeOfCertificate, 
                   UINT8 *pterCertificate)
{
    EFI_STATUS                Status;
    TrEE_EVENT               *Tcg20Event;
    EFI_VARIABLE_DATA        *VarLog = NULL;
    BOOLEAN                   AlreadyMeasuredCert = FALSE;
    UINTN                     i=0;
    UINTN                     VarNameLength;
    static BOOLEAN            initialized = 0;
    static TPM_DIGEST         digestTrackingArray[5];
    static TPM_DIGEST         zeroDigest;
    UINT8                     *tempDigest = NULL;
    UINT64                    HashedDataLen = 20; 
    SHA1_CTX                  Sha1Ctx;
    TCG_DIGEST                *Sha1Digest = NULL;
    UINT64                    Flags = 0;
    UINT32                    EventSize = 0;
    UINT8                     *EventDataPtr;

    if(TrEEProtocolInstance == NULL) return EFI_NOT_FOUND;

    VarNameLength = Wcslen(L"db");

    EventSize = (UINT32)( sizeof (*VarLog) + VarNameLength 
                              * sizeof (CHAR16) + sizeOfCertificate) - 3;

    pBS->AllocatePool(EfiBootServicesData, (sizeof(TrEE_EVENT_HEADER) + \
                      sizeof(UINT32) + EventSize), &Tcg20Event);

    if(Tcg20Event==NULL) return EFI_OUT_OF_RESOURCES;

    if(!initialized)
    {
        for(i=0;i<5; i++)
        {
            pBS->SetMem(digestTrackingArray[i].digest,20, 0);
        }
        pBS->SetMem(zeroDigest.digest,20, 0);
        initialized = TRUE;
    }

    Tcg20Event->Size  = sizeof(TrEE_EVENT_HEADER) + sizeof(UINT32) + EventSize;
    Tcg20Event->Header.HeaderSize = sizeof(TrEE_EVENT_HEADER);
    Tcg20Event->Header.HeaderVersion = 1;
    Tcg20Event->Header.PCRIndex    = 7;
    Tcg20Event->Header.EventType   = 0x800000E0;
       
    Status = pBS->AllocatePool(EfiBootServicesData, EventSize, &VarLog);

    if ( VarLog == NULL ){
        return EFI_OUT_OF_RESOURCES;
    }
        
    VarLog->VariableName       = gEfiImageSecurityDatabaseGuid;
    VarLog->UnicodeNameLength  = VarNameLength;
    VarLog->VariableDataLength = sizeOfCertificate;

    pBS->CopyMem((CHAR16*)(VarLog->UnicodeName),
                L"db",
                VarNameLength * sizeof (CHAR16));
   
    pBS->CopyMem((CHAR16*)(VarLog->UnicodeName) + VarNameLength,
                 pterCertificate,
                 sizeOfCertificate);

    //before extending verify if we have already measured it.
    SHA1Init(&Sha1Ctx);
    
    SHA1Update(&Sha1Ctx,
                VarLog,
           (u32)EventSize);

    SHA1Final((unsigned char *)&Sha1Digest->digest, &Sha1Ctx);

    for(i=0; i<5; i++)
    {
        //tempDigest
        if(!MemCmp(digestTrackingArray[i].digest, Sha1Digest, 20))
        return EFI_SUCCESS; //already measured

        if(!MemCmp(digestTrackingArray[i].digest, zeroDigest.digest, 20))
        break; //we need to measure
    }

    pBS->CopyMem(digestTrackingArray[i].digest, Sha1Digest, 20);
    
    EventDataPtr = (UINT8 *)Tcg20Event;

    EventDataPtr += sizeof(TrEE_EVENT_HEADER) + sizeof(UINT32);

    pBS->CopyMem(EventDataPtr, VarLog, EventSize);
    
    Status = TrEEProtocolInstance->HashLogExtendEvent(TrEEProtocolInstance,
                                            Flags, (EFI_PHYSICAL_ADDRESS)(UINT8 *)(UINTN)VarLog, (UINT64)EventSize,
                                            Tcg20Event);
    return Status;
}
#endif



#if (defined(TCGMeasureSecureBootVariables) && (TCGMeasureSecureBootVariables != 0))
EFI_STATUS FindandMeasureSecureBootCertificate()
{
    EFI_STATUS      Status;
    UINTN           VarSize  = 0;
    UINTN           i=0;
    UINT8           *SecureDBBuffer = NULL;
    UINT8           *CertificateBuffer = NULL;
    UINTN           SizeofCerificate = 0;
    EFI_GUID        Certificateguid = AMI_VALID_BOOT_IMAGE_CERT_TBL_GUID;
    AMI_VALID_CERT_IN_SIG_DB    *CertInfo;
    UINT8           *CertOffsetPtr = NULL;
   
    VarSize = 0;

    Status   = pRS->GetVariable(L"db",
                    &gEfiImageSecurityDatabaseGuid,
                    NULL,
                    &VarSize,
                    NULL);

    if ( Status != EFI_BUFFER_TOO_SMALL )
    {
        return EFI_NOT_FOUND;
    }

    Status = pBS->AllocatePool(EfiBootServicesData, VarSize, &SecureDBBuffer);
    
    if ( SecureDBBuffer != NULL )
    {
        Status = pRS->GetVariable(L"db",
                        &gEfiImageSecurityDatabaseGuid,
                        NULL,
                        &VarSize,
                        SecureDBBuffer);

        if ( EFI_ERROR( Status ))
        {
            pBS->FreePool( SecureDBBuffer  );
            SecureDBBuffer = NULL;
            return EFI_NOT_FOUND;
        }
    }else{
        return EFI_OUT_OF_RESOURCES;
    }

    //we need to find the pointer in the EFI system table and work from 
    //there
    CertInfo = NULL;
    EfiGetSystemConfigurationTable(&Certificateguid, &CertInfo );
    if(CertInfo == NULL){
     return EFI_NOT_FOUND;
    }
    if(CertInfo->SigLength == 0){
     return EFI_NOT_READY;
    }

    CertOffsetPtr = NULL;
    CertOffsetPtr = (SecureDBBuffer + CertInfo->SigOffset);
    MeasureCertificate((UINTN)CertInfo->SigLength,CertOffsetPtr);
    
    if(SecureDBBuffer!=NULL){
        pBS->FreePool( SecureDBBuffer  );
    }
    
    return Status;
}
#endif


UINTN Tpm20AsciiStrLen (
    IN CHAR8 *String)
{
  UINTN Length;
  for (Length = 0; *String != '\0'; String++, Length++);
  return Length;
}



EFI_STATUS
EFIAPI
MeasureAction (
  IN  CHAR8 *String
)
{
  TCG_PCR_EVENT_HDR                 TcgEvent;
  AMI_INTERNAL_HLXE_PROTOCOL        *InternalHLXE = NULL;
  EFI_GUID                          gEfiAmiHLXEGuid =  AMI_PROTOCOL_INTERNAL_HLXE_GUID;
  EFI_STATUS                        Status;

  TcgEvent.PCRIndex     = 5;
  TcgEvent.EventType    = EV_EFI_ACTION;
  TcgEvent.EventSize    = (UINT32)Tpm20AsciiStrLen (String);

  Status = pBS->LocateProtocol(&gEfiAmiHLXEGuid, NULL, &InternalHLXE);
  if(EFI_ERROR(Status))return Status;

  Status = InternalHLXE->InternalHashLogExtend((UINT8*)String, 0, TcgEvent.EventSize, &TcgEvent, (UINT8*)String);
  return Status;
}





EFI_STATUS
EFIAPI
TreeMeasurePeImage (
  IN      BOOLEAN                   BootPolicy,
  IN      EFI_PHYSICAL_ADDRESS      ImageAddress,
  IN      UINTN                     ImageSize,
  IN      UINTN                     LinkTimeBase,
  IN      UINT16                    ImageType,
  IN      EFI_HANDLE                DeviceHandle,
  IN      EFI_DEVICE_PATH_PROTOCOL  *FilePath
  )
{

  EFI_STATUS                        Status;
  TCG_PCR_EVENT_HDR                 TcgEvent;
  UINT8                             *EventData = NULL;
  EFI_IMAGE_LOAD_EVENT              *ImageLoad;
  EFI_DEVICE_PATH_PROTOCOL          *DevicePath;
  EFI_DEVICE_PATH_PROTOCOL          *FullPath;
  UINT32                            FullPathSize;
  SHA1_CTX                          Sha1Ctx;
  EFI_IMAGE_DOS_HEADER              *DosHdr;
  UINT32                            PeCoffHeaderOffset;
  EFI_IMAGE_NT_HEADERS64            *Hdr;
  EFI_IMAGE_SECTION_HEADER          *Section;
  UINT8                             *HashBase;
  UINTN                             HashSize;
  UINTN                             SumOfBytesHashed;
  EFI_IMAGE_SECTION_HEADER          *SectionHeader;
  UINTN                             Index, iPos;
  TCG_DIGEST                        Sha1Digest;
  AMI_INTERNAL_HLXE_PROTOCOL        *InternalHLXE = NULL;
  EFI_GUID                          gEfiAmiHLXEGuid =  AMI_PROTOCOL_INTERNAL_HLXE_GUID;
  TCG_PLATFORM_SETUP_PROTOCOL       *ProtocolInstance;
  EFI_GUID                          Policyguid = TCG_PLATFORM_SETUP_POLICY_GUID;
  SHA2_CTX                          Sha2Ctx;
//  unsigned char                     Sha2DigestArray[32];
  UINT8                             HashPolicy;


  Status = pBS->LocateProtocol (&Policyguid,  NULL, &ProtocolInstance);
  if (EFI_ERROR (Status)) {
      return 0;
  }

  HashPolicy = ProtocolInstance->ConfigFlags.Reserved1;
    
      
  ImageLoad     = NULL;
  FullPath      = NULL;
  SectionHeader = NULL;
  FullPathSize  = 0;

  TRACE ((TRACE_ALWAYS, "TreeMeasurePeImage Entry\n"));

  if (DeviceHandle != NULL) {
    //
    // Skip images loaded from FVs
    //
    Status = pBS->OpenProtocol (
                    DeviceHandle,
                    &gEfiFirmwareVolumeProtocolGuid,
                    NULL,
                    NULL,
                    NULL,
                    EFI_OPEN_PROTOCOL_TEST_PROTOCOL
                    );

    if (!EFI_ERROR (Status)) {
      goto Done;
    }
    ASSERT (Status == EFI_UNSUPPORTED);

    //
    // Get device path for the device handle
    //
    Status = pBS->HandleProtocol (
                    DeviceHandle,
                    &gEfiDevicePathProtocolGuid,
                    &DevicePath
                    );
    if (EFI_ERROR (Status)) {
      FullPathSize = (UINT32)DPLength (FullPath); 
    }else{                 
        FullPath     = DPAdd (DevicePath, FilePath);
        FullPathSize = (UINT32)DPLength (FullPath); 
    }
  }

    //Allocate Event log memory
  Status = pBS ->AllocatePool(EfiBootServicesData, ((sizeof (*ImageLoad)
                                - sizeof (ImageLoad->DevicePath)) + FullPathSize), &EventData);

  if(EFI_ERROR(Status))return Status;
  //
  // Determine destination PCR by BootPolicy
  //
  TcgEvent.EventSize  = sizeof (*ImageLoad) - sizeof (ImageLoad->DevicePath);
  TcgEvent.EventSize += FullPathSize;

  switch (ImageType) {
    case EFI_IMAGE_SUBSYSTEM_EFI_APPLICATION:
      TcgEvent.PCRIndex   = 4;
      TcgEvent.EventType = EV_EFI_BOOT_SERVICES_APPLICATION;
      break;
    case EFI_IMAGE_SUBSYSTEM_EFI_BOOT_SERVICE_DRIVER:
      TcgEvent.PCRIndex   = 2;
      TcgEvent.EventType = EV_EFI_BOOT_SERVICES_DRIVER;
      goto Done;
      break;
    case EFI_IMAGE_SUBSYSTEM_EFI_RUNTIME_DRIVER:
      TcgEvent.PCRIndex   = 2;
      TcgEvent.EventType = EV_EFI_RUNTIME_SERVICES_DRIVER;
      goto Done;
      break;
    default:
      TcgEvent.EventType = ImageType;
      Status = EFI_UNSUPPORTED;
      goto Done;
  }

  PERF_START(0,L"MeasurePeImg",NULL,0);

  Status = pBS ->AllocatePool(EfiBootServicesData,TcgEvent.EventSize, &ImageLoad);

  if (ImageLoad == NULL) {
    Status = EFI_OUT_OF_RESOURCES;
    goto Done;
  }

  ImageLoad->ImageLocationInMemory = ImageAddress;
  ImageLoad->ImageLengthInMemory   = ImageSize;
  ImageLoad->ImageLinkTimeAddress  = LinkTimeBase;
  ImageLoad->LengthOfDevicePath    = FullPathSize;
  pBS->CopyMem( ImageLoad->DevicePath, FullPath,  FullPathSize );

  //
  // Check PE/COFF image
  //
  DosHdr = (EFI_IMAGE_DOS_HEADER *)(UINTN)ImageAddress;
  PeCoffHeaderOffset = 0;
  if (DosHdr->e_magic == EFI_IMAGE_DOS_SIGNATURE) {
    PeCoffHeaderOffset = DosHdr->e_lfanew;
  }
  if (((EFI_TE_IMAGE_HEADER *)((UINT8 *)(UINTN)ImageAddress + PeCoffHeaderOffset))->Signature 
       == EFI_TE_IMAGE_HEADER_SIGNATURE) {
    goto Done;
  }

  //
  // PE/COFF Image Measurement
  //
  //    NOTE: The following codes/steps are based upon the authenticode image hashing in 
  //      PE/COFF Specification 8.0 Appendix A.
  //      
  //

  // 1.	Load the image header into memory.
  
  // 2.	Initialize a SHA hash context.
  if(HashPolicy == 0){ SHA1Init(&Sha1Ctx);}
  else if(HashPolicy == 1){sha256_init( &Sha2Ctx );};
  

  //
  // Measuring PE/COFF Image Header; 
  // But CheckSum field and SECURITY data directory (certificate) are excluded
  //
  Hdr   = (EFI_IMAGE_NT_HEADERS *)((UINT8 *)(UINTN)ImageAddress + PeCoffHeaderOffset);

  //
  // 3.	Calculate the distance from the base of the image header to the image checksum address.
  // 4.	Hash the image header from its base to beginning of the image checksum.
  //
  HashBase = (UINT8 *)(UINTN)ImageAddress;
  HashSize = (UINTN) ((UINT8 *)(&Hdr->OptionalHeader.CheckSum) - HashBase);
  if(HashPolicy == 0){
     SHA1Update(&Sha1Ctx,
                HashBase,
                (u32)HashSize);
  }else if(HashPolicy == 1){
     sha256_process( &Sha2Ctx, HashBase, (u32)HashSize );
  }



  //
  // 5.	Skip over the image checksum (it occupies a single ULONG).
  // 6.	Get the address of the beginning of the Cert Directory.
  // 7.	Hash everything from the end of the checksum to the start of the Cert Directory.
  //
  HashBase = (UINT8 *) &Hdr->OptionalHeader.CheckSum + sizeof (UINT32);
  HashSize = (UINTN) ((UINT8 *)(&Hdr->OptionalHeader.DataDirectory[EFI_IMAGE_DIRECTORY_ENTRY_SECURITY]) - HashBase);

  if(HashPolicy == 0){
     SHA1Update(&Sha1Ctx,
                HashBase,
                (u32)HashSize);
  }else if(HashPolicy == 1){
     sha256_process( &Sha2Ctx, HashBase, (u32)HashSize );
  }

  //
  // 8.	Skip over the Cert Directory. (It is sizeof(IMAGE_DATA_DIRECTORY) bytes.)
  // 9.	Hash everything from the end of the Cert Directory to the end of image header.
  //
  HashBase = (UINT8 *) &Hdr->OptionalHeader.DataDirectory[EFI_IMAGE_DIRECTORY_ENTRY_SECURITY + 1];
  HashSize = Hdr->OptionalHeader.SizeOfHeaders - 
             (UINTN) ((UINT8 *)(&Hdr->OptionalHeader.DataDirectory[EFI_IMAGE_DIRECTORY_ENTRY_SECURITY + 1]) - (UINT8 *)(UINTN)ImageAddress);
  
  if(HashPolicy == 0){
     SHA1Update(&Sha1Ctx,
                HashBase,
                (u32)HashSize);
  }else if(HashPolicy == 1){
     sha256_process( &Sha2Ctx, HashBase, (u32)HashSize );
  }


  //
  // 10. Set the SUM_OF_BYTES_HASHED to the size of the header 
  //
  SumOfBytesHashed = Hdr->OptionalHeader.SizeOfHeaders;

  //
  // 11. Build a temporary table of pointers to all the IMAGE_SECTION_HEADER 
  //     structures in the image. The 'NumberOfSections' field of the image 
  //     header indicates how big the table should be. Do not include any 
  //     IMAGE_SECTION_HEADERs in the table whose 'SizeOfRawData' field is zero.   
  //
  pBS ->AllocatePool(EfiBootServicesData,sizeof (EFI_IMAGE_SECTION_HEADER) * Hdr->FileHeader.NumberOfSections, &SectionHeader);

  if(SectionHeader==NULL)return EFI_OUT_OF_RESOURCES;
  pBS->SetMem(SectionHeader, (sizeof (EFI_IMAGE_SECTION_HEADER) * Hdr->FileHeader.NumberOfSections), 0);

  //
  // 12.	Using the 'PointerToRawData' in the referenced section headers as 
  //      a key, arrange the elements in the table in ascending order. In other 
  //      words, sort the section headers according to the disk-file offset of 
  //      the section.
  //
  Section = (EFI_IMAGE_SECTION_HEADER *) (
               (UINT8 *)(UINTN)ImageAddress +
               PeCoffHeaderOffset +
               sizeof(UINT32) + 
               sizeof(EFI_IMAGE_FILE_HEADER) + 
               Hdr->FileHeader.SizeOfOptionalHeader
               );  
  for (Index = 0; Index < Hdr->FileHeader.NumberOfSections; Index++) {
    iPos = Index;
    while ((iPos > 0) && (Section->PointerToRawData < SectionHeader[iPos - 1].PointerToRawData)) {
      pBS->CopyMem (&SectionHeader[iPos], &SectionHeader[iPos - 1], sizeof(EFI_IMAGE_SECTION_HEADER));
      iPos--;
    }
      pBS->CopyMem( &SectionHeader[iPos], Section,
                    sizeof(EFI_IMAGE_SECTION_HEADER));
    Section += 1;    
  }
  
  //
  // 13.	Walk through the sorted table, bring the corresponding section 
  //      into memory, and hash the entire section (using the 'SizeOfRawData' 
  //      field in the section header to determine the amount of data to hash).
  // 14.	Add the section's 'SizeOfRawData' to SUM_OF_BYTES_HASHED .
  // 15.	Repeat steps 13 and 14 for all the sections in the sorted table.
  //
  for (Index = 0; Index < Hdr->FileHeader.NumberOfSections; Index++) {
    Section  = (EFI_IMAGE_SECTION_HEADER *) &SectionHeader[Index];
    if (Section->SizeOfRawData == 0) {
      continue;
    }
    HashBase = (UINT8 *)(UINTN)ImageAddress + Section->PointerToRawData;
    HashSize = (UINTN) Section->SizeOfRawData;

    if(HashPolicy == 0){
     SHA1Update(&Sha1Ctx,
                HashBase,
                (u32)HashSize);
    }else if(HashPolicy == 1){
     sha256_process( &Sha2Ctx, HashBase, (u32)HashSize );
    }


    SumOfBytesHashed += HashSize;
  }    

  //
  // 16.	If the file size is greater than SUM_OF_BYTES_HASHED, there is extra
  //      data in the file that needs to be added to the hash. This data begins 
  //      at file offset SUM_OF_BYTES_HASHED and its length is:
  //             FileSize  -  (CertDirectory->Size)
  //
  if (ImageSize > SumOfBytesHashed) {
    HashBase = (UINT8 *)(UINTN)ImageAddress + SumOfBytesHashed;
    HashSize = (UINTN)(ImageSize -
               Hdr->OptionalHeader.DataDirectory[EFI_IMAGE_DIRECTORY_ENTRY_SECURITY].Size -
               SumOfBytesHashed);
    
    if(HashPolicy == 0){
     SHA1Update(&Sha1Ctx,
                HashBase,
                (u32)HashSize);
    }else if(HashPolicy == 1){
     sha256_process( &Sha2Ctx, HashBase, (u32)HashSize );
    }
  }

  //
  // 17.	Finalize the SHA hash.
  //
  if(HashPolicy == 0){
    SHA1Final(Sha1Digest.digest, &Sha1Ctx);
    pBS->CopyMem(&TcgEvent.Digest, Sha1Digest.digest, SHA1_DIGEST_SIZE);
  }else if(HashPolicy == 1){
    //sha256_done( &Sha2Ctx, Sha2DigestArray );
    //pBS->CopyMem(&TcgEvent.Digest.digestSha2, Sha2DigestArray, SHA256_DIGEST_SIZE);
  }

  //
  // HashLogExtendEvent 
  //
  pBS->CopyMem(EventData, ImageLoad, TcgEvent.EventSize);

  Status = pBS->LocateProtocol(&gEfiAmiHLXEGuid, NULL, &InternalHLXE);
  if(EFI_ERROR(Status))return Status;

  InternalHLXE->InternalHashLogExtend(NULL, 0, 0, &TcgEvent, EventData);

  PERF_END(0,L"MeasurePeImg",NULL,0);

  if(BootPolicy == TRUE){
#if (defined(TCGMeasureSecureBootVariables) && (TCGMeasureSecureBootVariables != 0))
    FindandMeasureSecureBootCertificate();
#endif
  }

Done:
  if (ImageLoad != NULL) {
    pBS->FreePool (ImageLoad);
  }

  if (FullPathSize > 0) {
   pBS->FreePool (FullPath);
  }

  if (SectionHeader != NULL) {
    pBS->FreePool (SectionHeader);
  }
  return Status;
}



//*******************************************************************************
//<AMI_PHDR_START>
//
// Procedure:   FindAndMeasureDxeFWVol
//
// Description: 
//
// Input:      
//
// Output:      EFI_STATUS
//
// Modified:
//
// Referrals:
//
// Notes:
//<AMI_PHDR_END>
//******************************************************************************
EFI_STATUS FindAndMeasureDxeFWVol()
{
    EFI_STATUS              Status;
    EFI_GUID                      NameGuid =\
                            {0x7739f24c, 0x93d7, 0x11d4,\
                             0x9a, 0x3a, 0x0, 0x90, 0x27, 0x3f, 0xc1, 0x4d};
    UINTN                         Size;
    void                          *Buffer = NULL;
    VOID                          *HobStart;
    UINTN                          TableEntries;
    EFI_PEI_HOB_POINTERS           FirmwareVolumeHob;
    BOOLEAN                        Found = FALSE;
    TrEE_EVENT                     *Tcg20Event = NULL;
    EFI_TCG_EV_POST_CODE           EventData; 


   if(TrEEProtocolInstance == NULL) return EFI_NOT_FOUND;  

   Status = pBS->AllocatePool(EfiBootServicesData, (sizeof(TrEE_EVENT_HEADER) + \
                      sizeof(UINT32) + sizeof(EventData)), &Tcg20Event);
   
   if(EFI_ERROR(Status) || (Tcg20Event == NULL))return Status;
    
   
    TableEntries = pST->NumberOfTableEntries;

    while ( TableEntries > 0 )
    {
        TableEntries--;

        if ((!MemCmp(
                 &pST->ConfigurationTable[TableEntries].VendorGuid,
                 &NameGuid, sizeof(EFI_GUID))))
        {            
            HobStart = pST->ConfigurationTable[TableEntries].VendorTable;
            FirmwareVolumeHob.Raw = GetHob (EFI_HOB_TYPE_FV, HobStart);
            if (FirmwareVolumeHob.Header->HobType != EFI_HOB_TYPE_FV) {
                 continue;
            }
            break;   
        }
    }        
   
    for (Status = EFI_NOT_FOUND; EFI_ERROR (Status);) {
        if (END_OF_HOB_LIST (FirmwareVolumeHob)) {
          return EFI_NOT_FOUND;
        }

        if (GET_HOB_TYPE (FirmwareVolumeHob) == EFI_HOB_TYPE_FV) {
        if ((((UINT64)FirmwareVolumeHob.FirmwareVolume->BaseAddress)\
                < (UINT64)NVRAM_ADDRESS ) || 
                ((UINT64)FirmwareVolumeHob.FirmwareVolume->BaseAddress) == FV_MAIN_BASE)
            {
                Found = TRUE;
                break;
            }
        }
        
        FirmwareVolumeHob.Raw = GET_NEXT_HOB (FirmwareVolumeHob);
    }

    if(Found == FALSE)return EFI_NOT_FOUND;

    pBS->AllocatePool(EfiBootServicesData, (UINTN)FirmwareVolumeHob.FirmwareVolume->Length, Buffer);

    if(Buffer == NULL) return EFI_OUT_OF_RESOURCES;
  
    if(FirmwareVolumeHob.FirmwareVolume->BaseAddress == FV_MAIN_BASE)
      {
         if(FirmwareVolumeHob.FirmwareVolume->Length > TCG_SIZE){
              Size = TCG_SIZE;
         }else{
             Size = FirmwareVolumeHob.FirmwareVolume->Length;
         }

         pBS->CopyMem(Buffer, (UINT8 *)(EFI_PHYSICAL_ADDRESS)FirmwareVolumeHob.FirmwareVolume->BaseAddress,\
                    Size);

      }else{

        Buffer = (UINT8 *)(EFI_PHYSICAL_ADDRESS)FirmwareVolumeHob.FirmwareVolume->BaseAddress;
        Size = FirmwareVolumeHob.FirmwareVolume->Length;
      }
      
      EventData.PostCodeAddress = \
                    (EFI_PHYSICAL_ADDRESS)FirmwareVolumeHob.FirmwareVolume->BaseAddress;

  #if defined x64_BUILD &&  x64_BUILD == 1
      EventData.PostCodeLength = Size;
  #else
      EventData.PostCodeLength = Size;
  #endif


      Tcg20Event->Size      = sizeof(TrEE_EVENT_HEADER) + sizeof(UINT32) + sizeof(EventData);
      Tcg20Event->Header.HeaderSize     = sizeof(TrEE_EVENT_HEADER);
      Tcg20Event->Header.HeaderVersion  = 1;
      Tcg20Event->Header.PCRIndex       = 0;
      Tcg20Event->Header.EventType      = EV_POST_CODE;

      pBS->CopyMem(Tcg20Event->Event, &EventData,sizeof(EventData));


      Status = TrEEProtocolInstance->HashLogExtendEvent(TrEEProtocolInstance,
                                           0, EventData.PostCodeAddress, Size,
                                           Tcg20Event);

      return Status;
}


EFI_STATUS
EFIAPI
MeasureHandoffTables (
  VOID
  )
{
    EFI_STATUS                        Status = EFI_SUCCESS;
#if Measure_Smbios_Tables
    SMBIOS_TABLE_ENTRY_POINT          *SmbiosTable;
    TrEE_EVENT                        *Tpm20Event;

    if(TrEEProtocolInstance == NULL) return EFI_NOT_FOUND;

    Status = pBS->AllocatePool(EfiBootServicesData, (sizeof(TrEE_EVENT_HEADER) + \
                      sizeof(UINT32) + sizeof(EFI_HANDOFF_TABLE_POINTERS)), &Tpm20Event);

    if(EFI_ERROR(Status) || (Tpm20Event == NULL))return Status;

    Status = EfiGetSystemConfigurationTable (&gEfiSmbiosTableGuid,
                            (VOID **) &SmbiosTable);

    if (!EFI_ERROR (Status)) {
    ASSERT (SmbiosTable != NULL);
    }
  
    Tpm20Event->Size  = sizeof(TrEE_EVENT_HEADER) + \
                      sizeof(UINT32) + sizeof(EFI_HANDOFF_TABLE_POINTERS);

    Tpm20Event->Header.HeaderSize = sizeof(TrEE_EVENT_HEADER);
    Tpm20Event->Header.HeaderVersion = 1;
    Tpm20Event->Header.PCRIndex    = 1;
    Tpm20Event->Header.EventType   = EV_EFI_HANDOFF_TABLES;

    ((EFI_HANDOFF_TABLE_POINTERS *)((UINTN)&Tpm20Event->Event[0]))->NumberOfTables = 1;
    ((EFI_HANDOFF_TABLE_POINTERS *)((UINTN)&Tpm20Event->Event[0]))->TableEntry[0].VendorGuid = gEfiSmbiosTableGuid;
    ((EFI_HANDOFF_TABLE_POINTERS *)((UINTN)&Tpm20Event->Event[0]))->TableEntry[0].VendorTable = SmbiosTable;

    Status = TrEEProtocolInstance->HashLogExtendEvent(TrEEProtocolInstance,
                                           0, (EFI_PHYSICAL_ADDRESS)(UINT8*)(UINTN)SmbiosTable->TableAddress, 
                                           SmbiosTable->TableLength,
                                           Tpm20Event);
    
    pBS->FreePool(Tpm20Event);
#endif

    return Status;
}



VOID *
EFIAPI
ReadVariable (
  IN    CHAR16      *VarName,
  IN    EFI_GUID    *VendorGuid,
  OUT   UINTN       *VarSize
  )
{
  EFI_STATUS                        Status;
  VOID                              *VarData;

  *VarSize = 0;
  Status = pRS->GetVariable (
                  VarName,
                  VendorGuid,
                  NULL,
                  VarSize,
                  NULL
                  );
  if (Status != EFI_BUFFER_TOO_SMALL) {
    return NULL;
  }

  pBS->AllocatePool (EfiBootServicesData, *VarSize, &VarData);
  if (VarData != NULL) {
    Status = pRS->GetVariable (
                    VarName,
                    VendorGuid,
                    NULL,
                    VarSize,
                    VarData
                    );
    if (EFI_ERROR (Status)) {
      pBS->FreePool (VarData);
      VarData = NULL;
      *VarSize = 0;
    }
  }
  return VarData;
}



EFI_STATUS
EFIAPI
MeasureVariable (
  IN      UINT32                    PCRIndex,
  IN      UINT32                    EventType,
  IN      CHAR16                    *VarName,
  IN      EFI_GUID                  *VendorGuid,
  IN      VOID                      *VarData,
  IN      UINTN                     VarSize
  )
{
    EFI_STATUS            Status;
    TrEE_EVENT            *Tpm20Event;
    UINTN                 EventSize;
    UINTN                 VarNameLength;
    EFI_VARIABLE_DATA    *VarLog;

    VarNameLength = Wcslen (VarName);

    if(TrEEProtocolInstance == NULL) return EFI_NOT_FOUND;

    EventSize = (UINT32)(sizeof (*VarLog) + VarNameLength * sizeof (*VarName) + VarSize
                        - sizeof (VarLog->UnicodeName) - sizeof (VarLog->VariableData));

    pBS->AllocatePool(EfiBootServicesData, (sizeof(TrEE_EVENT_HEADER) + \
                      sizeof(UINT32) + EventSize), &Tpm20Event);

    if(Tpm20Event==NULL)return EFI_OUT_OF_RESOURCES;
    
    Tpm20Event->Size  = sizeof(TrEE_EVENT_HEADER) + \
                      sizeof(UINT32) + (UINT32)EventSize;

    Tpm20Event->Header.HeaderSize = sizeof(TrEE_EVENT_HEADER);
    Tpm20Event->Header.HeaderVersion = 1;
    Tpm20Event->Header.PCRIndex    = PCRIndex;
    Tpm20Event->Header.EventType   = EventType;


    ((EFI_VARIABLE_DATA *)((UINTN)&Tpm20Event->Event[0]))->VariableName       = *VendorGuid;
    ((EFI_VARIABLE_DATA *)((UINTN)&Tpm20Event->Event[0]))->UnicodeNameLength  = VarNameLength;
    ((EFI_VARIABLE_DATA *)((UINTN)&Tpm20Event->Event[0]))->VariableDataLength = VarSize;

    pBS->CopyMem (((EFI_VARIABLE_DATA *)((UINTN)&Tpm20Event->Event[0]))->UnicodeName,
                 VarName,
                 VarNameLength * sizeof (*VarName));

    pBS->CopyMem ((CHAR16 *)((EFI_VARIABLE_DATA *)((UINTN)&Tpm20Event->Event[0]))->UnicodeName + VarNameLength,
                 VarData,
                 VarSize);
    
    Status = TrEEProtocolInstance->HashLogExtendEvent(TrEEProtocolInstance,
                                           0, (EFI_PHYSICAL_ADDRESS)(UINT8 *)(&Tpm20Event->Event[0]), EventSize,
                                           Tpm20Event);

    pBS->FreePool(Tpm20Event);

    return Status;
}


EFI_STATUS
EFIAPI
TcgMeasureGptTable (
  IN  EFI_HANDLE         GptHandle
  )
{
  EFI_STATUS                        Status;
  EFI_BLOCK_IO_PROTOCOL             *BlockIo;
  EFI_DISK_IO_PROTOCOL              *DiskIo;
  EFI_PARTITION_TABLE_HEADER        *PrimaryHeader;                     
  EFI_PARTITION_ENTRY               *PartitionEntry;
  UINT8                             *EntryPtr;
  UINTN                             NumberOfPartition;
  UINT32                            Index;
  UINT64							Flags;
  EFI_GPT_DATA                      *GptData;
  UINT32                            EventSize;
  MASTER_BOOT_RECORD                *Mbr;
  UINT8                             Count;
  UINT32                            LBAofGptHeader = 0;
  TCG_PCR_EVENT_HDR                 TcgEvent;
  AMI_INTERNAL_HLXE_PROTOCOL        *InternalHLXE = NULL;
  EFI_GUID                          gEfiAmiHLXEGuid =  AMI_PROTOCOL_INTERNAL_HLXE_GUID;

  if (mMeasureGptCount > 0) {
    return EFI_SUCCESS;
  }

  Status = pBS->HandleProtocol (GptHandle, &gEfiBlockIoProtocolGuid, (VOID**)&BlockIo);
  if (EFI_ERROR (Status)) {
    return EFI_UNSUPPORTED;
  }
  Status = pBS->HandleProtocol (GptHandle, &gEfiDiskIoProtocolGuid, (VOID**)&DiskIo);
  if (EFI_ERROR (Status)) {
    return EFI_UNSUPPORTED;
  }

  //Read the protective MBR 
  pBS->AllocatePool (EfiBootServicesData, BlockIo->Media->BlockSize, &Mbr);
  if (Mbr == NULL) {
    return EFI_OUT_OF_RESOURCES;
  }  
 
  Status = DiskIo->ReadDisk (
                     DiskIo,
                     BlockIo->Media->MediaId,
                     0 * BlockIo->Media->BlockSize,
                     BlockIo->Media->BlockSize,
                     (UINT8 *)Mbr
                     );

  for(Count=0; Count<MAX_MBR_PARTITIONS;Count++){
    if(Mbr->Partition[Count].OSIndicator == 0xEE){//(i.e., GPT Protective)
		  LBAofGptHeader = *(Mbr->Partition[Count].StartingLBA);
		  break;
	  }
  }

  if(LBAofGptHeader == 0x00)//Did not find the correct GPTHeader so return EFI_NOT_FOUND
    return EFI_NOT_FOUND;

  //
  // Read the EFI Partition Table Header
  //  
  pBS->AllocatePool (EfiBootServicesData, BlockIo->Media->BlockSize, &PrimaryHeader);
  if (PrimaryHeader == NULL) {
    return EFI_OUT_OF_RESOURCES;
  }  
 
  Status = DiskIo->ReadDisk (
                     DiskIo,
                     BlockIo->Media->MediaId,
                     LBAofGptHeader * BlockIo->Media->BlockSize,
                     BlockIo->Media->BlockSize,
                     (UINT8 *)PrimaryHeader);

//  if(PrimaryHeader->Header.Signature != EFI_GPT_HEADER_ID)//Check for "EFI PART" signature
  if (MemCmp(EFI_GPT_HEADER_ID, &PrimaryHeader->Header.Signature, sizeof(UINT64))) return EFI_NOT_FOUND;

  if (EFI_ERROR (Status)) {
    TRACE ((TRACE_ALWAYS, "Failed to Read Partition Table Header!\n"));
    pBS->FreePool (PrimaryHeader);                                                    
    return EFI_DEVICE_ERROR;
  }  

  //
  // Read the partition entry.
  //
  pBS->AllocatePool (EfiBootServicesData, PrimaryHeader->NumberOfPartitionEntries * PrimaryHeader->SizeOfPartitionEntry, &EntryPtr);
  if (EntryPtr == NULL) {
    pBS->FreePool (PrimaryHeader);
    return EFI_OUT_OF_RESOURCES;
  }
  Status = DiskIo->ReadDisk (
                     DiskIo,
                     BlockIo->Media->MediaId,
                     Mul64(PrimaryHeader->PartitionEntryLBA, BlockIo->Media->BlockSize),
                     PrimaryHeader->NumberOfPartitionEntries * PrimaryHeader->SizeOfPartitionEntry,
                     EntryPtr
                     );
  if (EFI_ERROR (Status)) {
    pBS->FreePool (PrimaryHeader);
    pBS->FreePool (EntryPtr);
    return EFI_DEVICE_ERROR;
  }
  
  //
  // Count the valid partition
  //
  PartitionEntry    = (EFI_PARTITION_ENTRY *)EntryPtr;
  NumberOfPartition = 0;
  for (Index = 0; Index < PrimaryHeader->NumberOfPartitionEntries; Index++) {
    if (MemCmp (&PartitionEntry->PartitionTypeGUID, &ZeroGuid, sizeof(EFI_GUID))) {
      NumberOfPartition++;  
    }
    PartitionEntry++;
  }

  //
  // Parepare Data for Measurement
  // 
  EventSize = (UINT32)(sizeof (EFI_GPT_DATA) - sizeof (GptData->Partitions) 
                        + NumberOfPartition * PrimaryHeader->SizeOfPartitionEntry);
  
  pBS->AllocatePool (EfiBootServicesData, EventSize, &GptData);
  if (GptData == NULL) {
    pBS->FreePool (PrimaryHeader);
    pBS->FreePool (EntryPtr);
    return EFI_OUT_OF_RESOURCES;
  }

  MemSet(GptData, EventSize, 0);

  TcgEvent.PCRIndex   = 5;
  TcgEvent.EventType  = EV_EFI_GPT_EVENT;
  TcgEvent.EventSize  = EventSize;

  Flags = 0;

  //
  // Copy the EFI_PARTITION_TABLE_HEADER and NumberOfPartition
  //  
  pBS->CopyMem ((UINT8 *)GptData, (UINT8*)PrimaryHeader, sizeof (EFI_PARTITION_TABLE_HEADER));
  GptData->NumberOfPartitions = NumberOfPartition;
  //
  // Copy the valid partition entry
  //
  PartitionEntry    = (EFI_PARTITION_ENTRY*)EntryPtr;
  NumberOfPartition = 0;
  for (Index = 0; Index < PrimaryHeader->NumberOfPartitionEntries; Index++) {
    if (MemCmp (&PartitionEntry->PartitionTypeGUID, &ZeroGuid, sizeof(EFI_GUID))) {
      pBS->CopyMem (
        (UINT8 *)&GptData->Partitions + NumberOfPartition * sizeof (EFI_PARTITION_ENTRY),
        (UINT8 *)PartitionEntry,
        sizeof (EFI_PARTITION_ENTRY)
        );
      NumberOfPartition++;
    }
    PartitionEntry++;
  }

  //
  // Measure the GPT data
  //
  if(NumberOfPartition > 0)
  {

    Status = pBS->LocateProtocol(&gEfiAmiHLXEGuid, NULL, &InternalHLXE);
    if(EFI_ERROR(Status))return Status;

    InternalHLXE->InternalHashLogExtend((UINT8 *)GptData, 0, EventSize, &TcgEvent, (UINT8 *)GptData);

    if (!EFI_ERROR (Status)) {
      mMeasureGptCount++;
	  TRACE ((TRACE_ALWAYS, "\n GPT measurement successfull !!!\n"));
    }
  }

  pBS->FreePool (PrimaryHeader);
  pBS->FreePool (EntryPtr);
  pBS->FreePool (GptData);
  return Status;
}





EFI_STATUS
EFIAPI
MeasureGptTable ()
{
  EFI_STATUS                  Status;
  EFI_HANDLE                  Handle;
  EFI_HANDLE                  *HandleArray;
  UINTN                       HandleArrayCount;
  UINTN                       Index;  
  EFI_DEVICE_PATH_PROTOCOL   *BlockIoDevicePath;
  EFI_DEVICE_PATH_PROTOCOL   *DevicePath;

  TRACE ((TRACE_ALWAYS, "MeasureGptTable\n"));


  Status = pBS->LocateHandleBuffer (ByProtocol, &gEfiBlockIoProtocolGuid, NULL, &HandleArrayCount, &HandleArray);
  if (EFI_ERROR (Status)) {
    return Status;
  }
  for (Index=0; Index < HandleArrayCount; Index++) {
    Status = pBS->HandleProtocol (HandleArray[Index], &gEfiDevicePathProtocolGuid, (VOID *) &BlockIoDevicePath);
    if (EFI_ERROR (Status) || BlockIoDevicePath == NULL) {
      continue;
    }
    for (DevicePath = BlockIoDevicePath; !IsDevicePathEnd (DevicePath); DevicePath = NextDevicePathNode (DevicePath)) {
      if ((DevicePathType (DevicePath) == ACPI_DEVICE_PATH) && (DevicePathSubType (DevicePath) == ACPI_DP)) {
        Status = pBS->LocateDevicePath (&gEfiBlockIoProtocolGuid, &DevicePath, &Handle);
        if (!EFI_ERROR (Status)) {
          Status = TcgMeasureGptTable (Handle);
          if (!EFI_ERROR (Status)) {
            //
            // GPT partition check done.
            //
//            mMeasureGptTableFlag = TRUE;
          }
			  }
        break;
      }
	  }
  }
  
  return Status;
}

#if (defined(TCGMeasureSecureBootVariables) && (TCGMeasureSecureBootVariables != 0))
EFI_STATUS
MeasureSecureBootState(
  VOID
  )
{
  EFI_STATUS          Status;
  UINT32              Attribute;
  UINTN               DataSize;
  UINT8               *Variable;
  UINT64              MaxStorSize;
  UINT64              RemStorSize;
  UINT64              MaxVarSize;
  TCG_PCR_EVENT_HDR   TcgEvent;
  CHAR16              *VarName;
  EFI_GUID            VendorGuid;

  Attribute = EFI_VARIABLE_NON_VOLATILE | EFI_VARIABLE_RUNTIME_ACCESS | EFI_VARIABLE_BOOTSERVICE_ACCESS | EFI_VARIABLE_AUTHENTICATED_WRITE_ACCESS;
	
  TcgEvent.PCRIndex      = 7;
  TcgEvent.EventType     =  EV_EFI_VARIABLE_DRIVER_CONFIG;

  // Query maximum size of the variable and allocate memory

  Status = pRS->QueryVariableInfo(Attribute, &MaxStorSize, &RemStorSize, &MaxVarSize);
  if (EFI_ERROR(Status)) {
    return (Status);
  }
  
  DataSize = (UINTN)MaxStorSize;
  pBS->AllocatePool(EfiBootServicesData, DataSize, &Variable);
  if (Variable == NULL) {
    return EFI_OUT_OF_RESOURCES;
  }
  MemSet(Variable, DataSize, 0);  // Clear the buffer

  // 1.Measure Secure Boot Variable Value

  Status = pRS->GetVariable (
                  EFI_SECURE_BOOT_NAME,
                  &gEfiGlobalVariableGuid,
                  NULL,
                  &DataSize, 
                  Variable
                  ); 

  VarName = EFI_SECURE_BOOT_NAME;
  VendorGuid = gEfiGlobalVariableGuid;

  if(EFI_ERROR(Status) || *Variable == 0){
		DataSize = 0;
        *Variable = 0;
  }


  Status = MeasureVariable (
             7,
             EV_EFI_VARIABLE_DRIVER_CONFIG,
             VarName,
             &VendorGuid,
             Variable,
             DataSize
             );

	// 2.Measure PK Variable Value

	DataSize = (UINTN)MaxStorSize; // DataSize gets updated by GetVariable. So initialize everytime before the call
	MemSet(Variable, DataSize, 0);  // Clear the buffer

    Status = pRS->GetVariable (
                  EFI_PLATFORM_KEY_NAME,
                  &gEfiGlobalVariableGuid,
                  NULL,
                  &DataSize, 
                  Variable
                  ); 

	VarName = EFI_PLATFORM_KEY_NAME;
    VendorGuid = gEfiGlobalVariableGuid;

    if(EFI_ERROR(Status)){
      DataSize = 0;
      *Variable = 0;
    }

    Status = MeasureVariable (
             7,
             EV_EFI_VARIABLE_DRIVER_CONFIG,
             VarName,
             &VendorGuid,
             Variable,
             DataSize
             );

  // 3.Measure KEK Variable Value

  DataSize = (UINTN)MaxStorSize; // DataSize gets updated by GetVariable. So initialize everytime before the call
  MemSet(Variable, DataSize, 0);  // Clear the buffer

  Status = pRS->GetVariable (
                          EFI_KEY_EXCHANGE_KEY_NAME,
                          &gEfiGlobalVariableGuid,
                          NULL,
                          &DataSize, 
                          Variable
                          ); 

	VarName = EFI_KEY_EXCHANGE_KEY_NAME;
    VendorGuid = gEfiGlobalVariableGuid;

    if(EFI_ERROR(Status)){
      DataSize = 0;
      *Variable = 0;
    }

    Status = MeasureVariable (
             7,
             EV_EFI_VARIABLE_DRIVER_CONFIG,
             VarName,
             &VendorGuid,
             Variable,
             DataSize
             );

	if(EFI_ERROR(Status)){
		goto Exit;
	}

	// 4.Measure EFI_IMAGE_SECURITY_DATABASE Variable Value

	DataSize = (UINTN)MaxStorSize; // DataSize gets updated by GetVariable. So initialize everytime before the call
	MemSet(Variable, DataSize, 0);  // Clear the buffer

  Status = pRS->GetVariable (
                          EFI_IMAGE_SECURITY_DATABASE,
                          &gEfiImageSecurityDatabaseGuid,
                          NULL,
                          &DataSize, 
                          Variable
                          ); 

	VarName = EFI_IMAGE_SECURITY_DATABASE;
    VendorGuid = gEfiImageSecurityDatabaseGuid;

    if(EFI_ERROR(Status)){
      DataSize = 0;
      *Variable = 0;
    }

    Status = MeasureVariable (
             7,
             EV_EFI_VARIABLE_DRIVER_CONFIG,
             VarName,
             &VendorGuid,
             Variable,
             DataSize
             );

	if(EFI_ERROR(Status)){
		goto Exit;
	}

	// 5.Measure EFI_IMAGE_SECURITY_DATABASE1 Variable Value

	DataSize = (UINTN)MaxStorSize; // DataSize gets updated by GetVariable. So initialize everytime before the call
	MemSet(Variable, DataSize, 0);  // Clear the buffer

  Status = pRS->GetVariable (
                          EFI_IMAGE_SECURITY_DATABASE1,
                          &gEfiImageSecurityDatabaseGuid,
                          NULL,
                          &DataSize, 
                          Variable
                          ); 

	VarName = EFI_IMAGE_SECURITY_DATABASE1;
    VendorGuid = gEfiImageSecurityDatabaseGuid;

    if(EFI_ERROR(Status)){
      DataSize = 0;
      *Variable = 0;
    }

    Status = MeasureVariable (
             7,
             EV_EFI_VARIABLE_DRIVER_CONFIG,
             VarName,
             &VendorGuid,
             Variable,
             DataSize
             );

	if(EFI_ERROR(Status)){
		goto Exit;
	}

Exit:
	pBS->FreePool(Variable);
	return EFI_SUCCESS;
}
#endif


EFI_STATUS ResetMorVariable()
{
    EFI_STATUS      Status;
    EFI_GUID MorGuid = MEMORY_ONLY_RESET_CONTROL_GUID;
    UINT32 Attribs   = EFI_VARIABLE_NON_VOLATILE
                       | EFI_VARIABLE_BOOTSERVICE_ACCESS;

    UINT8 Temp       = 0;
    UINTN TempSize = sizeof (UINT8);



    Status = pRS->GetVariable(
        L"MemoryOverwriteRequestControl",
        &MorGuid,
        &Attribs,
        &TempSize,
        &Temp );

    if ( EFI_ERROR( Status ) || (Temp&01) != 0 )
    {
        Temp &= 0xFE;
        Status = pRS->SetVariable(
            L"MemoryOverwriteRequestControl",
            &MorGuid,
            EFI_VARIABLE_NON_VOLATILE | EFI_VARIABLE_BOOTSERVICE_ACCESS
            | EFI_VARIABLE_RUNTIME_ACCESS,
            sizeof (UINT8),
            &Temp );
    }

    return Status;
}

EFI_STATUS
InternalMeasureAction (
  IN      CHAR8                     *ActionString
  )
{
   return EFI_SUCCESS; //not supported
}


EFI_STATUS
InternalMeasureGpt (
  IN      EFI_DEVICE_PATH_PROTOCOL  *DevicePath
  )
{

    return EFI_SUCCESS; //not supported;
}



EFI_TCG_PLATFORM_PROTOCOL  mTcgPlatformProtocol = {
  TreeMeasurePeImage,
  InternalMeasureAction,
  InternalMeasureGpt
};


EFI_STATUS InstallTcgPlatformProtocol(
    VOID    
)
{

 EFI_GUID  gEfiTcgPrivateInterfaceGuid = EFI_TCG_PLATFORM_PROTOCOL_GUID;

 return pBS->InstallProtocolInterface (
                &PlatformProtocolHandle,
                &gEfiTcgPrivateInterfaceGuid,
                EFI_NATIVE_INTERFACE,
                &mTcgPlatformProtocol
                );

}


VOID
EFIAPI
Tpm20OnReadyToBoot (
  IN      EFI_EVENT                 Event,
  IN      VOID                      *Context
  )
{
  EFI_STATUS                Status;
  UINT32                    PcrIndex;
  static  BOOLEAN           mBootAttempts=0;
 
  if (mBootAttempts == 0) {

    ResetMorVariable();
    //
    // Measure handoff tables
    //
    Status = MeasureHandoffTables ();
    if (EFI_ERROR (Status)) {
      TRACE ((TRACE_ALWAYS, "HandoffTables not measured.\n"));
    }
    else {
      TRACE((TRACE_ALWAYS, "HandoffTables measured.\n"));
    }

    //
	// Measure the fact that Secure Boot is disabled
    //
#if (defined(TCGMeasureSecureBootVariables) && (TCGMeasureSecureBootVariables != 0))
    Status = MeasureSecureBootState();
    if (EFI_ERROR (Status)) {
      TRACE ((TRACE_ALWAYS, "Measuring secure boot state failed.\n"));
    }
    else {
      TRACE((TRACE_ALWAYS, "Secure boot state measured.\n"));
    }
#endif

	
    //
    // This is the first boot attempt
    //
    Status = MeasureAction (
               "EFI_CALLING_EFI_APPLICATION"
             );
    if (EFI_ERROR (Status)) {
      TRACE ((TRACE_ALWAYS, "First boot attempt not Measured.\n"));
    }
    else {
      TRACE((TRACE_ALWAYS, "First boot attempt measured.\n"));
    }

    //
    // Draw a line between pre-boot env and entering post-boot env
    //
    for (PcrIndex = 0; PcrIndex < 8; PcrIndex++) {
      Status = MeasureSeparatorEvent (PcrIndex);
      if (EFI_ERROR (Status)) {
        TRACE ((TRACE_ALWAYS, "Measuring separtator event failed.\n"));
      }
      else {
        TRACE((TRACE_ALWAYS, "Separator event measured.\n"));
      }

    }

    //
    // Measure GPT
    //
    Status = MeasureGptTable ();
    if (EFI_ERROR (Status)) {
      TRACE ((TRACE_ALWAYS, "Measuring GPT failed.\n"));
    }
    else {
      TRACE((TRACE_ALWAYS, "GPT measured.\n"));
    }
  } 
  else {
    //
    // Not first attempt, meaning a return from last attempt
    //
/*
    Status = MeasureAction (
               "EFI_RETURNING_FROM_EFI_APPLICATOIN"
               );
    if (EFI_ERROR (Status)) {
      TRACE ((TRACE_ALWAYS, "Measuring additional boot attempt failed.\n"));
    }
*/
  }
  //
  // Increase boot attempt counter.
  //
  mBootAttempts++;

}



//**********************************************************************
//<AMI_PHDR_START>
//
// Procedure:   GetStringFromToken
//
// Description: Gets a UNI string by Token
//
// Input:       IN      STRING_REF                Token,
//              OUT     CHAR16                    **String
//
// Output:      EFI_STATUS
//
// Modified:
//
// Referrals:
//
// Notes:
//<AMI_PHDR_END>
//**********************************************************************
EFI_STATUS GetStringFromToken(
    IN STRING_REF Token,
    OUT CHAR16    **String )
{
    EFI_STATUS Status;
    UINTN      StringBufferLength;
    UINT16     *Temp;
    UINTN      Size = 0;


    //
    // Find the string based on the current language
    //
    StringBufferLength = 0x500;
    Status             = pBS->AllocatePool( EfiBootServicesData,
                                            sizeof (CHAR16) * 0x500,
                                            String );
    Temp               = *String;
    while ( Temp < *String + StringBufferLength )
    {
        *Temp = 0x0;
        Temp++;
    }

#if EFI_SPECIFICATION_VERSION>0x20000 

    Status = HiiLibGetString (
        gHiiHandle,
        Token,
        &StringBufferLength,
        *String
    );
    if (EFI_ERROR(Status)) {
        return Status;
    }

#else
    if ( Hii == NULL )
    {
        return EFI_NOT_FOUND;
    }

    Status = Hii->GetString(
        Hii,
        gHiiHandle,
        Token,
        TRUE,
        NULL,
        &StringBufferLength,
        *String
        );
#endif


    if ( EFI_ERROR( Status ))
    {
        pBS->FreePool( *String );
        return EFI_NOT_FOUND;
    }

    return EFI_SUCCESS;
}



EFI_STATUS TcgSetVariableWithNewAttributes(
    IN CHAR16 *Name, IN EFI_GUID *Guid, IN UINT32 Attributes,
    IN UINTN DataSize, IN VOID *Data    
)
{
    EFI_STATUS Status;
    
    Status = pRS->SetVariable(Name, Guid, Attributes, DataSize, Data);
    if (!EFI_ERROR(Status) || Status != EFI_INVALID_PARAMETER) return Status;

    Status = pRS->SetVariable(Name, Guid, 0, 0, NULL);
    if (EFI_ERROR(Status)) return Status;

    return pRS->SetVariable(Name, Guid, Attributes, DataSize, Data);
}


//****************************************************************************************
//<AMI_PHDR_START>
//
// Procedure: write_PPI_result
//
// Description: Updates TCG PPI variable in NVRAM
//
//
// Input:       IN  UINT8 last_op,
//              IN  UINT16 status
//
// Output:      VOID
//
// Modified:
//
// Referrals:
//
// Notes:
//<AMI_PHDR_END>
//****************************************************************************************
void WritePpiResult(
    IN UINT8  last_op,
    IN UINT16 status )
{
    UINTN          Size = sizeof(AMI_PPI_NV_VAR);
    AMI_PPI_NV_VAR Temp;
    EFI_STATUS     Status;
    UINT8          Manip = 0;

    Status = pRS->GetVariable( L"AMITCGPPIVAR", \
                               &AmitcgefiOsVariableGuid, \
                               NULL, \
                               &Size, \
                               &Temp );

    //now set variable to data
    Temp.RQST  = Manip;
    Manip      = (UINT8)( status & 0xFFFF );
    Temp.ERROR = Manip;

    if(status>0xFF && status<0xFFFF)
    {
        Temp.AmiMisc = (UINT8)(status >> 8);
    }else{
        Temp.AmiMisc = 0;
    }

    if ( EFI_ERROR( Status ))
    {
        TRACE((TRACE_ALWAYS, "Error Setting Return value\n"));
        return;
    }


    Status =  TcgSetVariableWithNewAttributes(L"AMITCGPPIVAR", &AmitcgefiOsVariableGuid, \
                                   EFI_VARIABLE_NON_VOLATILE   \
                                    | EFI_VARIABLE_BOOTSERVICE_ACCESS,\
                                   Size, &Temp  );

}



/**
  Send ClearControl command to TPM2.

  @param Disable           if we need disable owner clear flag.

  @retval EFI_SUCCESS      Operation completed successfully.
  @retval EFI_DEVICE_ERROR Unexpected device behavior.
**/
EFI_STATUS
EFIAPI
Tpm2ClearControl (
  IN TPMI_YES_NO          Disable
  )
{
  EFI_STATUS                        Status;
  TPM2_CLEAR_CONTROL_COMMAND        Cmd;
  TPM2_CLEAR_CONTROL_RESPONSE       Res;
  UINT32                            ResultBufSize;
  UINT32                            CmdSize;
  UINT32                            RespSize;
  UINT8                             *Buffer;
  UINT8                             *AuthSizeOffset;

  Cmd.Header.tag         = (TPMI_ST_COMMAND_TAG)TPM_H2NS(TPM_ST_SESSIONS);
  Cmd.Header.commandCode = TPM_H2NL(TPM_CC_ClearControl);
  Cmd.Auth               = TPM_H2NL(TPM_RH_PLATFORM);

  Buffer = (UINT8 *)&Cmd.AuthorizationSize;

  //
  // Add in Auth session
  //
  AuthSizeOffset = Buffer;
  *(UINT32 *)Buffer = 0;
  Buffer += sizeof(UINT32);

  // authHandle
  *(UINT32 *)Buffer = TPM_H2NL(TPM_RS_PW);
  Buffer += sizeof(UINT32);

  // nonce = nullNonce
  *(UINT16 *)Buffer = 0;
  Buffer += sizeof(UINT16);

  // sessionAttributes = 0
  *(UINT8 *)Buffer = 0;
  Buffer += sizeof(UINT8);

  // auth = nullAuth
  *(UINT16 *)Buffer = 0;
  Buffer += sizeof(UINT16);

  // authorizationSize
  *(UINT32 *)AuthSizeOffset = TPM_H2NL((UINT32)(Buffer - AuthSizeOffset - sizeof(UINT32)));

  // disable
  *(UINT8 *)Buffer = Disable;
  Buffer += sizeof(UINT8);

  CmdSize = (UINT32)(Buffer - (UINT8 *)&Cmd);
  Cmd.Header.paramSize   = TPM_H2NL(CmdSize);

  ResultBufSize = sizeof(Res);
  Status = TrEEProtocolInstance->SubmitCommand(TrEEProtocolInstance,CmdSize,(UINT8 *)&Cmd , ResultBufSize , (UINT8 *)&Res);

  if (EFI_ERROR(Status)) {
    return Status;
  }

  if (ResultBufSize > sizeof(Res)) {
    TRACE((TRACE_ALWAYS, "ClearControl: Failed ExecuteCommand: Buffer Too Small\r\n"));
    Status = EFI_BUFFER_TOO_SMALL;
    goto ClearControlEND;
  }

  //
  // Validate response headers
  //
  RespSize = TPM_H2NL(Res.Header.paramSize);
  if (RespSize > sizeof(Res)) {
    TRACE((TRACE_ALWAYS, "ClearControl: Response size too large! %d\r\n", RespSize));
    Status = EFI_BUFFER_TOO_SMALL;
    goto ClearControlEND;
  }

  //
  // Fail if command failed
  //
  if (TPM_H2NL(Res.Header.responseCode) != TPM_RC_SUCCESS) {
    TRACE((TRACE_ALWAYS, "ClearControl: Response Code error! 0x%08x\r\n", TPM_H2NL(Res.Header.responseCode)));
    Status = EFI_DEVICE_ERROR;
    goto ClearControlEND;
  }

  //
  // Unmarshal the response
  //

  // None

  Status = EFI_SUCCESS;
 
ClearControlEND:
  return Status;
}



EFI_STATUS
EFIAPI
Tpm2Clear (
  VOID
  )
{
  EFI_STATUS                        Status;
  TPM2_CLEAR_COMMAND                Cmd;
  TPM2_CLEAR_RESPONSE               Res;
  UINT32                            ResultBufSize;
  UINT32                            CmdSize;
  UINT32                            RespSize;
  UINT8                             *Buffer;
  UINT8                             *AuthSizeOffset;

  Cmd.Header.tag         = (TPMI_ST_COMMAND_TAG)TPM_H2NS(TPM_ST_SESSIONS);
  Cmd.Header.commandCode = TPM_H2NL(TPM_CC_Clear);
  Cmd.Auth               = TPM_H2NL(TPM_RH_PLATFORM);

  Buffer = (UINT8 *)&Cmd.AuthorizationSize;

  //
  // Add in Auth session
  //
  AuthSizeOffset = Buffer;
  *(UINT32 *)Buffer = 0;
  Buffer += sizeof(UINT32);

  // authHandle
  *(UINT32 *)Buffer = TPM_H2NL(TPM_RS_PW);
  Buffer += sizeof(UINT32);

  // nonce = nullNonce
  *(UINT16 *)Buffer = 0;
  Buffer += sizeof(UINT16);

  // sessionAttributes = 0
  *(UINT8 *)Buffer = 0;
  Buffer += sizeof(UINT8);

  // auth = nullAuth
  *(UINT16 *)Buffer = 0;
  Buffer += sizeof(UINT16);

  // authorizationSize
  *(UINT32 *)AuthSizeOffset = TPM_H2NL((UINT32)(Buffer - AuthSizeOffset - sizeof(UINT32)));

  CmdSize = (UINT32)(Buffer - (UINT8 *)&Cmd);
  Cmd.Header.paramSize   = TPM_H2NL(CmdSize);

  ResultBufSize = sizeof(Res);
  
  Status = TrEEProtocolInstance->SubmitCommand(TrEEProtocolInstance,CmdSize,(UINT8 *)&Cmd , ResultBufSize , (UINT8 *)&Res);
  if (EFI_ERROR(Status)) {
    return Status;
  }

  if (ResultBufSize > sizeof(Res)) {
    TRACE((TRACE_ALWAYS, "Clear: Failed ExecuteCommand: Buffer Too Small\r\n"));
    Status = EFI_BUFFER_TOO_SMALL;
    goto ClearEND;
  }

  //
  // Validate response headers
  //
  RespSize = TPM_H2NL(Res.Header.paramSize);
  if (RespSize > sizeof(Res)) {
    TRACE((TRACE_ALWAYS, "Clear: Response size too large! %d\r\n", RespSize));
    Status = EFI_BUFFER_TOO_SMALL;
    goto ClearEND;
  }

  //
  // Fail if command failed
  //
  if (TPM_H2NL(Res.Header.responseCode) != TPM_RC_SUCCESS) {
    TRACE((TRACE_ALWAYS, "Clear: Response Code error! 0x%08x\r\n", TPM_H2NL(Res.Header.responseCode)));
    Status = EFI_DEVICE_ERROR;
    goto ClearEND;
  }

  //
  // Unmarshal the response
  //

  // None

  Status = EFI_SUCCESS;
 
ClearEND:
  return Status;
}



//**********************************************************************
//<AMI_PHDR_START>
//
// Procedure:  read_PPI_request
//
// Description: Reads and returns TCG PPI requests Value
//
//
// Input:
//
// Output:      UINT8
//
// Modified:
//
// Referrals:
//
// Notes:
//<AMI_PHDR_END>
//**********************************************************************
UINT8 ReadPpiRequest( )
{
    UINTN          Size = sizeof(AMI_PPI_NV_VAR);
    AMI_PPI_NV_VAR Temp;
    EFI_STATUS     Status;

    Status = pRS->GetVariable( L"AMITCGPPIVAR", \
                               &AmitcgefiOsVariableGuid, \
                               NULL, \
                               &Size, \
                               &Temp );

    if(Status == EFI_NOT_FOUND)
    {
        Temp.RQST    = 0;
        Temp.RCNT    = 0;
        Temp.ERROR   = 0;
        Temp.Flag    = 0;
        Temp.AmiMisc = 0;

        Status =  TcgSetVariableWithNewAttributes(L"AMITCGPPIVAR", &AmitcgefiOsVariableGuid, \
                                   EFI_VARIABLE_NON_VOLATILE   \
                                   | EFI_VARIABLE_BOOTSERVICE_ACCESS,\
                                   Size, &Temp  );

    }

    return Temp.RQST;
}



void HandleTpm20Ppi(IN EFI_EVENT ev,
                    IN VOID *ctx)
{
    BOOLEAN             UserAction;
    UINT8               StringType = 0;
    UINTN               CurX, CurY;
    CHAR16              *StrBuffer = NULL;
    CHAR16              *String;
    EFI_INPUT_KEY       key;
    TSE_POST_STATUS     TsePostStatus;
    EFI_STATUS          Status;
    

    TRACE((TRACE_ALWAYS, "HandleTpm20Ppi Entry \n"));
    if (pAmiPostMgr == NULL) {
        Status = pBS->LocateProtocol( &gAmiPostManagerProtocolGuid,
                                      NULL,
                                      &pAmiPostMgr );
        if (EFI_ERROR(Status)) {
            return;
        }
    }

    //
    // Calling GetPostStatus() to check current TSE_POST_STATUS
    //
    TsePostStatus = pAmiPostMgr->GetPostStatus();

    if ( pST->ConIn == NULL || pST->ConOut == NULL || TsePostStatus == TSE_POST_STATUS_BEFORE_POST_SCREEN )
    {
        TRACE((TRACE_ALWAYS, "\tTextIn/Out not ready: in=%x; out=%x\n",
               pST->ConIn, pST->ConOut));
        return;
    }

    switch(PpiRequest){
        case TPM20_PP_NO_ACTION_MAX:
                return;
                
        case TPM20_PP_CLEAR_CONTROL_CLEAR_2:
        case TPM20_PP_CLEAR_CONTROL_CLEAR_3:
        case TPM20_PP_CLEAR_CONTROL_CLEAR_4:
            if(TpmNvflags.NoPpiClear != 1)
            {
                UserAction = TRUE;
                StringType = 1;
                break;
            }
        case TPM20_PP_SET_NO_PPI_CLEAR_FALSE:
            UserAction = FALSE;
            StringType = 0;
            break;

        case TPM20_PP_SET_NO_PPI_CLEAR_TRUE:
            if(TpmNvflags.NoPpiClear != 1)
            {
                UserAction = TRUE;
                StringType = 2;
                break;
            }
        
        default:
            if (PpiRequest <= TPM20_PP_NO_ACTION_MAX){
                WritePpiResult( PpiRequest, (UINT16)(0));
            }else{
                WritePpiResult( PpiRequest, (UINT16)(TCPA_PPI_BIOSFAIL));
            }
            return;
    }

    if(UserAction)
    {
         pAmiPostMgr->SwitchToPostScreen( );

         Status = pBS->AllocatePool(EfiBootServicesData,
                        sizeof (CHAR16) * 0x100,
                        (VOID*) &StrBuffer);

         if ( EFI_ERROR( Status ) || StrBuffer == NULL )
         {
            return;
         }

         MemSet( StrBuffer, sizeof (CHAR16) * 0x100, 0 );

         pAmiPostMgr->DisplayPostMessage( StrBuffer );

         pAmiPostMgr->GetCurPos(&CurX, &CurY);  

         CurX =  0;
         CurY -= PPI_DISPLAY_OFFSET;  
    
         if(StringType == 1){
             
             GetStringFromToken( STRING_TOKEN(TPM_CLEAR_STR), &String );
             pAmiPostMgr->DisplayPostMessage( String );
             GetStringFromToken( STRING_TOKEN( TPM_WARNING_CLEAR ), &String );
             pAmiPostMgr->DisplayPostMessage( String );
             GetStringFromToken( STRING_TOKEN( TPM_CAUTION_KEY ), &String );
             pAmiPostMgr->DisplayPostMessage( String );

         }else if(StringType == 2){
             
             GetStringFromToken( STRING_TOKEN(TPM_PPI_HEAD_STR), &String );
             pAmiPostMgr->DisplayPostMessage( String );
             GetStringFromToken( STRING_TOKEN( TPM_NOTE_CLEAR ), &String );
             pAmiPostMgr->DisplayPostMessage( String );
             GetStringFromToken( STRING_TOKEN( TPM_ACCEPT_KEY ), &String );
             pAmiPostMgr->DisplayPostMessage( String );
         }
         
        GetStringFromToken( STRING_TOKEN( TPM_REJECT_KEY ), &String );
        pAmiPostMgr->DisplayPostMessage( String );

        if ( pST->ConIn )
        {
            while ( TRUE )
            {
                Status = pST->ConIn->ReadKeyStroke( pST->ConIn, &key );
                if ( Status == EFI_SUCCESS )
                {
                    if ( PpiRequest == TPM20_PP_CLEAR_CONTROL_CLEAR_2 ||
                         PpiRequest == TPM20_PP_CLEAR_CONTROL_CLEAR_3 ||
                         PpiRequest == TPM20_PP_CLEAR_CONTROL_CLEAR_4 )
                    {
                        if ( key.ScanCode == TCG_CLEAR_REQUEST_KEY )
                        {
                            break;
                        }
                     }
                    else if(PpiRequest == TPM20_PP_SET_NO_PPI_CLEAR_FALSE ||
                             PpiRequest == TPM20_PP_SET_NO_PPI_CLEAR_TRUE)
                    {                                
    
                        if ( key.ScanCode == TCG_CONFIGURATION_ACCEPT_KEY )
                        {
                            break;
                        }
                    }
                    else if ( key.ScanCode == TCG_CONFIGURATION_IGNORE_KEY )
                    {
                        return;
                    }
                }
            } 
        }       

    }

    if ( PpiRequest == TPM20_PP_CLEAR_CONTROL_CLEAR_2 ||
         PpiRequest == TPM20_PP_CLEAR_CONTROL_CLEAR_3 ||
         PpiRequest == TPM20_PP_CLEAR_CONTROL_CLEAR_4 )
    {
         Status = Tpm2ClearControl(0);
         if(!EFI_ERROR(Status)){
            
            Status = Tpm2Clear();
            if(EFI_ERROR(Status)){
                TRACE((TRACE_ALWAYS, "Error Clearing TPM20 device\n"));
                WritePpiResult( PpiRequest, (UINT16)(TCPA_PPI_BIOSFAIL));
            }else{
                WritePpiResult( PpiRequest, (UINT16)(0));
            }
         }else{
            TRACE((TRACE_ALWAYS, "Tpm2ClearControl failure\n"));
            WritePpiResult( PpiRequest, (UINT16)(TCPA_PPI_BIOSFAIL));
        }
    }
    else if(PpiRequest == TPM20_PP_SET_NO_PPI_CLEAR_FALSE ||
            PpiRequest == TPM20_PP_SET_NO_PPI_CLEAR_TRUE)
    {
        if(PpiRequest == TPM20_PP_SET_NO_PPI_CLEAR_FALSE)
        {
            TpmNvflags.NoPpiClear = 0;

        }else{
            TpmNvflags.NoPpiClear = 1;
        }
              
        Status =  TcgSetVariableWithNewAttributes(L"TPMPERBIOSFLAGS", &FlagsStatusguid, \
                                   EFI_VARIABLE_NON_VOLATILE \
                                   | EFI_VARIABLE_BOOTSERVICE_ACCESS,
                                   sizeof (PERSISTENT_BIOS_TPM_FLAGS), &TpmNvflags);

        if(EFI_ERROR(Status)){
                TRACE((TRACE_ALWAYS, "Error Clearing TPM20 device\n"));
                WritePpiResult( PpiRequest, (UINT16)(TCPA_PPI_BIOSFAIL));
         }
         else{
            WritePpiResult( PpiRequest, (UINT16)(0));    
        }
    }else{
        WritePpiResult( PpiRequest, (UINT16)(0));
    }

    TRACE((TRACE_ALWAYS, "TPM20 changes made reseting system\n"));
    pRS->ResetSystem (EfiResetCold, EFI_SUCCESS, 0, NULL);
}

VOID
EFIAPI
Tpm20OnExitBootServices (
  IN      EFI_EVENT                 Event,
  IN      VOID                      *Context
  )
{
  EFI_STATUS    Status;

  //
  // Measure invocation of ExitBootServices,
  //
  Status = MeasureAction (
             "Exit Boot Services Invocation");

  //
  // Measure success of ExitBootServices
  //
  Status = MeasureAction (
             "Exit Boot Services Returned with Success");
}



EFI_STATUS
Tpm20PlatformEntry(
    IN EFI_HANDLE       ImageHandle,
    IN EFI_SYSTEM_TABLE *SystemTable )
{
    EFI_STATUS          Status;
    EFI_GUID            gEfiTrEEProtocolGuid = EFI_TREE_PROTOCOL_GUID;
    EFI_EVENT           ReadyToBootEvent;
    EFI_EVENT           ev;
    EFI_EVENT           ExitBSEvent;
    static VOID         *reg;
    UINTN               Size = sizeof(PERSISTENT_BIOS_TPM_FLAGS);
    

    InitAmiLib( ImageHandle, SystemTable );

    TRACE((TRACE_ALWAYS, "Tpm20PlatformEntry\n"));

    Status = pBS->LocateProtocol(&gEfiTrEEProtocolGuid, NULL, &TrEEProtocolInstance);
    if(EFI_ERROR(Status))return Status;

    Status = InstallTcgPlatformProtocol();
    if(EFI_ERROR(Status))return Status;

    //we found TrEE protocol do Tpm20 
    //Initializations set ready to boot callback
    //install platform protocol

    Status = CreateReadyToBootEvent(TPL_CALLBACK,
                                    Tpm20OnReadyToBoot, 
                                    NULL, 
                                    &ReadyToBootEvent);

    Status = pBS->CreateEvent (
                      EVT_SIGNAL_EXIT_BOOT_SERVICES,
                      EFI_TPL_NOTIFY,
                      Tpm20OnExitBootServices,
                      NULL,
                      &ExitBSEvent
                      );
    LoadStrings( ImageHandle, &gHiiHandle );

    Status = pRS->GetVariable( L"TPMPERBIOSFLAGS", \
                               &FlagsStatusguid, \
                               NULL, \
                               &Size, \
                               &TpmNvflags );

    if(EFI_ERROR(Status))
    {
        TpmNvflags.NoPpiProvision = 1;  
        TpmNvflags.NoPpiClear = 0;
        TpmNvflags.NoPpiMaintenance = 0;

        Status =  TcgSetVariableWithNewAttributes(L"TPMPERBIOSFLAGS", &FlagsStatusguid, \
                                   EFI_VARIABLE_NON_VOLATILE \
                                   | EFI_VARIABLE_BOOTSERVICE_ACCESS,
                                   sizeof (PERSISTENT_BIOS_TPM_FLAGS), &TpmNvflags);

        if(EFI_ERROR(Status))return Status;
    }

    PpiRequest = ReadPpiRequest();
    PpiRequest &= 0xFF;

    if(PpiRequest > 0  &&  PpiRequest <= TCPA_PPIOP_ENABLE_ACTV_CLEAR_ENABLE_ACTV){
        
        Status = pBS->CreateEvent( EFI_EVENT_NOTIFY_SIGNAL,
                                   EFI_TPL_CALLBACK,
                                   HandleTpm20Ppi,
                                   0,
                                   &ev );

        if(EFI_ERROR(Status)){
            return Status;
        }

        Status = pBS->RegisterProtocolNotify( 
                        &gBdsAllDriversConnectedProtocolGuid,
                        ev,
                        &reg );
        if(EFI_ERROR(Status)) {
            return Status;
        }
    }

    return Status;
}

//**********************************************************************
//**********************************************************************
//**                                                                  **
//**        (C)Copyright 1985-2010, American Megatrends, Inc.         **
//**                                                                  **
//**                       All Rights Reserved.                       **
//**                                                                  **
//**     5555 Oakbrook Pkwy, Suite 200, Norcross, GA 30093            **
//**                                                                  **
//**                       Phone: (770)-246-8600                      **
//**                                                                  **
//**********************************************************************
//**********************************************************************
