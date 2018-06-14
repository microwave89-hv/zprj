//**********************************************************************
//**********************************************************************
//**                                                                  **
//**        (C)Copyright 1985-2013, American Megatrends, Inc.         **
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
// $Header: /Alaska/SOURCE/Modules/SecureBoot_WIN8/ImageVerification_efi/DxeImageVerificationLib.c 79    6/22/15 6:26p Alexp $
//
// $Revision: 79 $
//
// $Date: 6/22/15 6:26p $
//**********************************************************************
// Revision History
// ----------------
// $Log: /Alaska/SOURCE/Modules/SecureBoot_WIN8/ImageVerification_efi/DxeImageVerificationLib.c $
// 
// 79    6/22/15 6:26p Alexp
// EIP219415
// [Category]  Bug Fix
// [Severity]	 Minor
// [Symptom] UEFI PXE can launch unsigned images when 
//                  SecureBoot is enabled.
// [RootCause]  Image from PXE server gets cloned device path 
//            from its parent network controller with PciIo protocol 
//            and embedded PCI ROM attributes
//  [Solution]  Add checking for unique path for embedded 
//                  Pci OpROMs to prevent non-OpROM images
// 
// 77    5/14/15 9:49a Alexp
// DxeImageVerificationHandler()
//  Modify certificate offset calculation to match EDKII version
// 
// 76    3/09/15 4:24p Alexp
// EIP192504: Prevent Built In EFI Shell boot option from being created in
// BDS when Secure Boot is enabled
// [Resolution]: Leave old logic to allow launching embedded shell 
//  based on the token:LOAD_UNSIGNED_EMBEDDED_SHELL
//   enabled by default only in Debug mode
// EIP197749: Need to authenticate images loaded from external FV
// [Resolution]  Add logic inside GetImageType() to detect images loaded
// from external FV
// 
// 75    5/29/14 8:52a Alexp
// minor debug trace message change;
// 
// 74    8/15/13 11:29a Alexp
// EIP#118850: Implement support for Certificate Revocation Storage
// reduction and Timestamp Support.
// Link AmyCryptoLib to make use of os_mktime()
// 
// 73    7/26/13 3:40p Alexp
// 1. EIP118850: Integrate ECR1009 chnages for TimeStamp dbt processing
// 2. Image policy settings are checked against the build time defaults. 
// Prevents un-authorized change to NVRAM policy settings 
// to lower security policy.
// 
// 72    6/26/13 10:48a Alexp
// EIP[125931]: Security review. Fix after follow up review.  
// UINT32 integer wrapping still occurs due to incorrect placement 
// of delimiting parentheses
// 
// 70    6/25/13 7:21p Alexp
// EIP:127292 Item#2. Add dependency on ENABLE_IMAGE_EXEC_POLICY_OVERRIDE
// EIP:127292 Item#3 Only For deprecated Security protocol:
//  DxeImageVerificationHandler Returns Error if FileRead() is
// unsuccessful
// 
// 67    6/21/13 10:41a Alexp
// EIP[125931]: Security review: HashPeImage does not validate certificate
// table offset and size
// 
// 66    5/21/13 4:05p Alexp
// EIP:124444  Secure boot improvement for LoadImage call with NULL
// DevicePath
// EIP:122339  GetImageType() detect if PciOpROM image is loaded from
// internal FV by
//    checking the corresponding PCI I/O instance for the embedded
// attribute.
// 
// 63    3/25/13 3:41p Alexp
// 1. EIP:118243 add support for multi-signed PE Images
// 2. Removed append image certificates to db from User Query dialog.
// 
// 56    3/11/13 5:07p Alexp
// IsSignatureFoundInDatabase(): fix method to calculate CertCount.
// AddImageExeInfo(): code cleanup for cases when *Name is NULL
// DxeImageVerificationHandler(): Optimized code to determine if PE image
// is signed
// 
// 55    3/09/13 4:31p Alexp
// EIP114998: wrong cert size passed in PCR[7] calculation
// 
// 54    12/19/12 10:28a Alexp
// EIP[104046]: Hardened code per #2,3,4,5,6,7 of security review findings
//  
// 
// 53    12/17/12 3:10p Alexp
// code fixes according to "cppcheck" style & performance suggestions
// 
// 52    12/06/12 7:31p Alexp
// Update ImageAuthorization()
// 
// 51    11/26/12 10:46a Alexp
// replaced hardwired Var name L"SecureBootSetup" to generic Var define
// 
// 50    11/19/12 4:42p Alexp
// Fix for Win8 SecureBoot logo requirement: restore Secure Boot state
// across flash updates.
// Move all secure boot Setup settings to a separate varsore variable. 
// Preserve var across re-flash
// 
// 49    11/09/12 4:32p Alexp
// IsPkcsSignedDataVerifiedBySignatureList()
// Fix CertData size - excude EFI_GUID size
// 
// 48    10/17/12 3:03p Alexp
// EIP[104046]: Findings from Security review on Aptio4 Image verification
//  Includes the fix for item #4:
//  HashPeImage returns TRUE even in error case
// 
// 47    10/16/12 3:53p Alexp
// EIP[104046]: Findings from Security review on Aptio4 Image verification
// Includes the fix for item #7 from the list attached to the EIP
// 
// 46    9/25/12 11:22a Alexp
// removed ImageVerify simulation when system in SetupMode.
// 
// 45    9/24/12 12:26p Alexp
// fix code branch for WIN_CERT_TYPE_EFI_GUID certificates
// 
// 44    9/19/12 4:07p Alexp
// fix code branch to set action EFI_IMAGE_EXECUTION_AUTH_SIG_FAILED
// 
// 43    9/14/12 3:42p Alexp
// Hardwire LoadFromFv to AlwaysEnable irrespective of SetupData
// 
// 42    9/13/12 11:38a Alexp
// Fix Bug in HashPeiImage. 
// Last step 16 in hashing of optional data structures after the
// Certificate entry was missing
// 
// 41    9/07/12 9:37a Alexp
// 1. Set all global variables Static
// 2. IsPkcsSignedDataVerifiedBySignatureList(). Compiler optimization for
//  "IsVerified = VerifyWinCertificateForPkcsSignedData(
//   &(PkcsCertData->Hdr));"
//  may not link the main code.
// 3. Run Verify code when platform is in SetupMode and SecureBoot set to
//     Custom
// 
// 39    9/05/12 5:42p Alexp
// GetImageType() : 
// Change Device Path search criteria to match EDKII example: 
//  check FV path first and then Block I/O
// 
// 38    8/29/12 11:16a Alexp
// Add definition for EFI_MAX_ADDRESS if it's not defined elsewhere in
// included header files
// 
// 37    8/28/12 4:21p Alexp
// Restore dependencies on SecureBootMode->Custom Setup option
// 
// 35    8/15/12 4:16p Alexp
// IsPkcsSignedDataVerifiedBySignatureList()
// Fix bug prev version in processing multiple Certs from PE Hdr.
// 
// 34    7/26/12 3:54p Alexp
// Query User -> Append Certificate only available in Setup Mode.
// 
// 33    7/25/12 6:45p Alexp
// 1. Update ImageVerification logic to the latest EDK2 patch (13469)
//     Add support for multiple Signatures within PE/COFF table
//     Additional Header validation checks 
// 2. Add code flow when SecureBoot set to Custom mode.
//    Image Verification is performed but failing images are allowed to
// run
//    Use this mode to append image certificates to DB in User Query mode.
// 
// 32    6/11/12 3:15p Alexp
//  use modified WIN_CERTIFICATE_UEFI_GUID_1 struc in
//  AppendEfiImageSecurityDatabaseVariableEx()  
//  moded struc is shorter by 4 bytes
// 
// 30    5/18/12 9:21a Alexp
// Fine tune User Query messages. Only display the messages if Admin user
// has signed in   
// 
// 29    5/01/12 4:43p Alexp
// PCR[7] - mTrustSigDbOffs contains offset to SigData struct within SigDb
// 
// 28    4/27/12 3:57p Alexp
// Fix Certificate type in AppendEfiImageSecurityDatabaseVariableEx()
// 
// 27    4/23/12 5:19p Alexp
// EIP:80874 Made changes to support PCR[7] measurments for Secure Boot
// state in TCG
// Install "Efi Boot Image Certificate" info strusture on Efi System
// Table.
// 
// 26    4/20/12 5:14p Alexp
// Add new function to install the handle on Efi System Table with the
// location 
// within DB variable of the Trusted Certificate that was used to verify
// signature of Efi OS BootLoader image.
// 
// 25    4/10/12 6:52p Alexp
// Update VerifyCertPkcsSignedData() to support extended search in
// Forbidded db for any leaf certificate, not only Root CA
// 
// 23    4/03/12 7:35p Alexp
// Move ReadImage() under legacy SecureFileAuthentication()
// 
// 22    4/02/12 4:24p Alexp
// Installs EFI_SECURITY2_ARCH_PROTOCOL. 
// Input arguments include File Path and pointer to a File buffer in
// memory.
// 
// 20    3/20/12 10:51a Alexp
// 1. fix in AppendEfiImageSecurityDatabaseVariableEx()
// 2. removed unused global vars
// 
// 18    3/16/12 10:29a Alexp
// [EIP85500] Build problem with (INT)4.6.5.1_SECUREBOOT_WIN8_11
// move "extern EFI_GUID BdsConnectDriversProtocolGuid " outside of #ifdef
// scope
// 
// 17    3/13/12 2:41p Alexp
// Add check for Admin signed credentials while allowing User Querry
// policy
// 
// 16    3/12/12 3:01p Alexp
// 1. Deffer image verification till BdsConnectDriversProtocol event.
// Speeds up the boot time.
// 2. Enforce default (hardwired by SDL token) image veriication policy
// for image device path if SecureBootMode is set to Standard.
// 
// 15    3/09/12 3:39p Alexp
// 1. Fixed Image authentication by Hash certificate in "db"
// 2. Add User interructive controls to append image certificate to Sig
// "db" (test implementation, will change in later releases)
// 
// 14    2/27/12 6:47p Alexp
// Reduce time spent in the DxeImageVerificationHandler function during
// non-Secure Boot mode. Original code caused additional 0.5 sec to boot
// time.
// Note: internal SecureBoot mode flag once registered during
// initializaton - will not change until restart. 
// 
// 13    1/04/12 3:27p Alexp
// Fixed possible security risk:
// GetImageType(). Block I/O Device Path check made higher priority then
// of FV device path. 
// 
// 12    12/29/11 6:49p Alexp
// GetImageType() - Fix for Image Device Path resolution
// Added SubType = MEDIA_FV_FILEPATH_DP to search options for
// MEDIA_DEVICE_PATH.
// It appears SmmDriverDispatcher sets this device path for files loaded
// by SmmDispatcher.
// 
// 11    12/23/11 8:59a Alexp
// Bug fix:
// EIP:78978:Secure boot will hang at CP 0x72
// ConOut & ConIn are not available until later in BDS phase, earlier
// calls to display User Prompt may hang the system
// 
// 10    12/07/11 7:23p Alexp
// Bug fix:
// EIP:77088  SecureBoot: Image can be loaded if click "No" when query
// user after image verification failed
// ImageAuthorization() -> Return EFI_ACCESS_DENIED of User Override
// option
// 
// 9     8/22/11 11:14a Alexp
// optimizations to GetImageType()
// 
// 6     7/18/11 4:12p Alexp
// EIP:65085. LoadImage Error status is different When Secure Boot is ON
// EIP:65194: No way to control the Secure Boot module to not interact
// with the USER without changing the code
// 
// 4     6/23/11 9:27a Alexp
// moved mDigitalSig Protocol check up before API may be called
// 
// 3     6/22/11 5:45p Alexp
// draft change: add Sha256 as valid cert for "db" databases
// 
// 2     6/13/11 7:21p Alexp
// fix Hash calculation for Sha256 Certs in Forbidden database dbx
// 
// 10    5/17/11 5:36p Alexp
// update conOut messages
// 
// 9     5/17/11 12:50p Alexp
// replace AmiPostManager with pST->ConOut
// use pBS instead of gBS
// 
// 6     5/13/11 4:02p Alexp
//  1. add dependency on Core rev. 4.6.5+ to buld for older Aptio cores
//  2. Ignore Querry User policy for internal FV files
// 
//**********************************************************************
/*++
  This file contains an 'Intel Peripheral Driver' and is        
  licensed for Intel CPUs and chipsets under the terms of your  
  license agreement with Intel or your vendor.  This file may   
  be modified by the user, subject to additional terms of the   
  license agreement                                             
--*/
/** @file

  Implement image verification services for secure boot
  service in UEFI2.2.

  Caution: This file requires additional review when modified.
  This library will have external input - PE/COFF image.
  This external input must be validated carefully to avoid security issue like
  buffer overflow, integer overflow.

  DxeImageVerificationLibImageRead() function will make sure the PE/COFF image content
  read is within the image buffer.

  DxeImageVerificationHandler(), HashPeImageByType(), HashPeImage() function will accept
  untrusted PE/COFF image and validate its data structure within this image buffer before use.

Copyright (c) 2009 - 2012, Intel Corporation. All rights reserved.<BR>

This software and associated documentation (if any) is furnished
under a license and may only be used or copied in accordance
with the terms of the license. Except as permitted by such
license, no part of this software or documentation may be
reproduced, stored in a retrieval system, or transmitted in any
form or by any means without the express written consent of
Intel Corporation.

**/

#pragma warning (disable : 4090)

#include <Token.h>
#include <Protocol/Security.h>
#include "DxeImageVerificationLib.h"
#include "EfiImage.h"
#include <AmiDxeLib.h>
#include<Guid/PeiPeCoffLoader.h>
#include <Protocol/AmiDigitalSignature.h>
#include <AmiCertificate.h>
#include <Setup.h>
#include <SecureBootMod.h>
#include <Protocol/PciIo.h> //EIP 122339
#include <cryptlib.h>

extern EFI_GUID BdsConnectDriversProtocolGuid;

// 4.6.5.4
#if defined(CORE_COMBINED_VERSION) && CORE_COMBINED_VERSION >=0x4028e
#include <Protocol/Security2.h>
#endif

// 4.6.5.1
#if defined(CORE_COMBINED_VERSION) && CORE_COMBINED_VERSION >=0x4028b
#include <EdkIICommon.h>
#else
#include <Tiano.h>

//********tmp declaration from EdkIICommon.h
#define MEDIA_RELATIVE_OFFSET_RANGE_DP 0x08

extern VOID ZeroMem (
    OUT VOID    *Buffer,
    IN  UINTN   Size 
);
VOID* CopyMem (
    OUT VOID  *DestinationBuffer,
    IN  VOID  *SourceBuffer,
    IN UINTN  Length
);
#endif
EFI_STATUS
EFIAPI
PeCoffLoaderGetImageInfo (
  IN     EFI_PEI_PE_COFF_LOADER_PROTOCOL       *This,
  IN OUT EFI_PEI_PE_COFF_LOADER_IMAGE_CONTEXT  *ImageContext
  );

#include <Protocol/SimpleTextIn.h>
#include <Protocol/SimpleTextOut.h>

#define AMI_MEDIA_DEVICE_PATH_GUID \
    { 0x5023b95c, 0xdb26, 0x429b, 0xa6, 0x48, 0xbd, 0x47, 0x66, 0x4c, 0x80, 0x12 }

#define STANDARD_SECURE_BOOT       0
#define CUSTOM_SECURE_BOOT         1

static EFI_GUID AmiMediaDevicePathGuid  = AMI_MEDIA_DEVICE_PATH_GUID;
static EFI_GUID gSecureSetupGuid        = SECURITY_FORM_SET_GUID;
static EFI_GUID gEfiGlobalVariableGuid  = EFI_GLOBAL_VARIABLE;

static AMI_DIGITAL_SIGNATURE_PROTOCOL *mDigitalSigProtocol = NULL;
//
// Caution: This is used by a function which may receive untrusted input.
// These global variables hold PE/COFF image data, and they should be validated before use.
//
EFI_IMAGE_OPTIONAL_HEADER_PTR_UNION        mNtHeader;
static UINT8                              *mImageBase = NULL;
static UINTN                               mImageSize;
static EFI_GUID                           *mCertType;
static UINT32                              mPeCoffHeaderOffset; 
static UINT8                               mImageDigest[MAX_DIGEST_SIZE];
static UINTN                               mImageDigestSize;
static SECURE_BOOT_SETUP_VAR               mSecureBootSetup;
static UINT8                               mSecureBootEnable = 0;
static UINTN                               mFvHandlesCount   = 0;
static EFI_HANDLE                          *mFvHandles       = NULL;
static BOOLEAN                             gImageLoadingAfterBDS = FALSE;

//
// Notify string for authorization UI.
//
CHAR16  mNotifyString1[MAX_NOTIFY_STRING_LEN] = L"\r\nImage verification failed!\r\n";
CHAR16  mNotifyString2[MAX_NOTIFY_STRING_LEN] = L"\r\nLaunch this image anyway? (Y/N)";
CHAR16  mNotifyString3[MAX_NOTIFY_STRING_LEN] = L"Image Certificate not found in Authorized database(db)!";
CHAR16  mNotifyString4[MAX_NOTIFY_STRING_LEN] = L"Image Certificate is found in Forbidden database(dbx)!";
CHAR16  mNotifyString5[MAX_NOTIFY_STRING_LEN] = L"Image is unsigned or Certificate is invalid!";

//6683D10C-CF6E-4914-B5B4-AB8ED7370ED7
EFI_GUID gBootImageCertTblGuid  = AMI_VALID_BOOT_IMAGE_CERT_TBL_GUID;
static UINT32   mTrustSigDbOffs = 0;
static UINT32   mTrustSigDbSize = 0;

//---------------------------------------
// NEW TIME STAMP definitions ECR#1009
//---------------------------------------
extern EFI_GUID gEfiCertX509Sha256Guid;
extern EFI_GUID gEfiCertX509Sha384Guid;
extern EFI_GUID gEfiCertX509Sha512Guid;
static INT32     mTimeOfSigningLong;
typedef enum {
    CertUndefined,
    CertSha256,
    CertX509, 
    CertX509Sha256, 
    CertX509Sha384, 
    CertX509Sha512, 
} nCertType;
//---------------------------------------
// NEW TIME STAMP definitions ECR#1009
//---------------------------------------

//************TEMP UTILITY FUNCTIONS. Use EDKII common wrapper lib instead****************
#if defined(CORE_COMBINED_VERSION) && CORE_COMBINED_VERSION >=0x4028b
#else
UINTN StrSize (
    IN CHAR16 *String)
{
  UINTN Size;

  for (Size = 2; *String != L'\0'; String++, Size += 2);

  return Size;
}
#endif

VOID* GetEfiGlobalVariableEx (
    IN CHAR16 *Name,
    IN OUT UINTN *VarSize
    )
{
    EFI_STATUS Status;
    VOID *Var=NULL;

    Status = GetEfiVariable(Name, &gEfiGlobalVariableGuid, NULL, VarSize, &Var);
    return (EFI_ERROR(Status)) ? NULL : Var;
}

VOID* GetEfiImageSecurityDatabaseVariableEx (
    IN CHAR16 *Name,
    IN OUT UINTN *VarSize
    )
{
    EFI_STATUS Status;
    VOID *Var = NULL;

    Status = GetEfiVariable(Name, &gEfiImageSecurityDatabaseGuid, NULL, VarSize, &Var);
    return (EFI_ERROR(Status)) ? NULL : Var;
}

/**
  Reads contents of a PE/COFF image in memory buffer.

  Caution: This function may receive untrusted input.
  PE/COFF image is external input, so this function will make sure the PE/COFF image content
  read is within the image buffer.

  @param  FileHandle      Pointer to the file handle to read the PE/COFF image.
  @param  FileOffset      Offset into the PE/COFF image to begin the read operation.
  @param  ReadSize        On input, the size in bytes of the requested read operation.  
                          On output, the number of bytes actually read.
  @param  Buffer          Output buffer that contains the data read from the PE/COFF image.
  
  @retval EFI_SUCCESS     The specified portion of the PE/COFF image was read and the size 
**/
EFI_STATUS
EFIAPI
DxeImageVerificationLibImageRead (
  IN     VOID    *FileHandle,
  IN     UINTN   FileOffset,
  IN OUT UINTN   *ReadSize,
  OUT    VOID    *Buffer
  )
{

  if (FileHandle == NULL || ReadSize == NULL || Buffer == NULL) {
    return EFI_INVALID_PARAMETER;    
  }

  if ((EFI_MAX_ADDRESS - FileOffset) < *ReadSize) {
    return EFI_INVALID_PARAMETER;
  }

  if (((UINT64)FileOffset + *ReadSize) > mImageSize) {
//    *ReadSize = (UINT32)(mImageSize - FileOffset);
    return EFI_INVALID_PARAMETER;
  }

  if (FileOffset >= mImageSize) {
//    *ReadSize = 0;
    return EFI_INVALID_PARAMETER;
  }

  CopyMem (Buffer, (UINT8 *)((UINTN) FileHandle + FileOffset), *ReadSize);

  return EFI_SUCCESS;
}


/**
  Get the image type.

  @param[in]    File       This is a pointer to the device path of the file that is
                           being dispatched. 

  @return UINT32           Image Type

**/
UINT32
GetImageType (
  IN  CONST EFI_DEVICE_PATH_PROTOCOL   *File
  )
{
  EFI_STATUS                        Status;
  EFI_HANDLE                        DeviceHandle; 
  EFI_DEVICE_PATH_PROTOCOL          *TempDevicePath;
  EFI_BLOCK_IO_PROTOCOL             *BlockIo;
  UINT8                             nDevicePathSubType;
  //EIP 122339 Start
  EFI_PCI_IO_PROTOCOL               *PciIoInterface = NULL;
  UINT64                            AttributesResult;
  //EIP 122339 Stop
  UINTN                             Index;
  BOOLEAN                           IsFv = FALSE;

  // Unknown device path: image security policy is applied to the image with the least trusted origin.
  if (File == NULL) {
   return IMAGE_UNKNOWN;
  }

  //
  // Check if File is just a Firmware Volume.
  //
  TempDevicePath = (EFI_DEVICE_PATH_PROTOCOL *)File;
  while (!IsDevicePathEndType(TempDevicePath)){
      nDevicePathSubType = DevicePathSubType (TempDevicePath);
      TRACE((TRACE_ALWAYS,"Device PathType %x, SubType %x\n", DevicePathType(TempDevicePath), nDevicePathSubType ));
    //
    // EFI Specification extension on Media Device Path. MEDIA_FW_VOL_FILEPATH_DEVICE_PATH is adopted by UEFI later and added in UEFI2.10. 
    // In EdkCompatibility Package, we only support MEDIA_FW_VOL_FILEPATH_DEVICE_PATH that complies with EFI 1.10 and UEFI 2.10.
    //
    if( (DevicePathType(TempDevicePath) == MEDIA_DEVICE_PATH && nDevicePathSubType == MEDIA_FV_FILEPATH_DP) ||
        (DevicePathType(TempDevicePath) == HARDWARE_DEVICE_PATH && nDevicePathSubType == HW_MEMMAP_DP)
    ){
        IsFv = TRUE;
    } else {
        IsFv = FALSE;
        break;
    }
    TempDevicePath = NextDevicePathNode(TempDevicePath);
  }

  //
  // Check to see if a File or a FV is from internal Firmware Volume.
  //
  if(IsFv) {

      DeviceHandle      = NULL;
      TempDevicePath = (EFI_DEVICE_PATH_PROTOCOL *)File;
      Status = pBS->LocateDevicePath (
#if (PI_SPECIFICATION_VERSION < 0x00010000)
                      &gEfiFirmwareVolumeProtocolGuid,
#else
                      &gEfiFirmwareVolume2ProtocolGuid,
#endif
                      &TempDevicePath,
                      &DeviceHandle
                      );

    if (!EFI_ERROR (Status)) {
        if(!gImageLoadingAfterBDS)
          return IMAGE_FROM_FV;

        Status = pBS->OpenProtocol (
                        DeviceHandle,
#if (PI_SPECIFICATION_VERSION < 0x00010000)
                       &gEfiFirmwareVolumeProtocolGuid,
#else
                       &gEfiFirmwareVolume2ProtocolGuid,
#endif
                        NULL,
                        NULL,
                        NULL,
                        EFI_OPEN_PROTOCOL_TEST_PROTOCOL
                        );
        if (!EFI_ERROR (Status)) {
            for(Index=0;Index < mFvHandlesCount;Index++){
    TRACE((TRACE_ALWAYS,"FV%02d. DeviceHandle %X=%X\n", Index, DeviceHandle, mFvHandles[Index] ));
                if(DeviceHandle == mFvHandles[Index] )
                    return IMAGE_FROM_FV;
            }
        }
    }
    return IMAGE_UNKNOWN;
  }
  //
  // Next check to see if File is from a Block I/O device
  // Must be a Block I/O device since we reached here after Int FV path check
  //
  DeviceHandle   = NULL;
  TempDevicePath = (EFI_DEVICE_PATH_PROTOCOL *)File;
  Status = pBS->LocateDevicePath (
                  &gEfiBlockIoProtocolGuid,
                  &TempDevicePath,
                  &DeviceHandle
                  );
  if (!EFI_ERROR (Status)) {
    BlockIo = NULL;
    Status = pBS->OpenProtocol (
                    DeviceHandle,
                    &gEfiBlockIoProtocolGuid,
                    (VOID **) &BlockIo,
                    NULL,
                    NULL,
                    EFI_OPEN_PROTOCOL_GET_PROTOCOL
                    );
    if (!EFI_ERROR (Status) && BlockIo != NULL) {
      if (BlockIo->Media != NULL) {
        if (BlockIo->Media->RemovableMedia) {
          //
          // Block I/O is present and specifies the media is removable
          //
          return IMAGE_FROM_REMOVABLE_MEDIA;
        } else {
          //
          // Block I/O is present and specifies the media is not removable
          //
          return IMAGE_FROM_FIXED_MEDIA;
        }
      }
    }
  }
  //
  // File is not in a Firmware Volume or on a Block I/O device, so check to see if 
  // the device path supports the Simple File System Protocol.
  //
  DeviceHandle   = NULL;
  TempDevicePath = (EFI_DEVICE_PATH_PROTOCOL *)File;
  Status = pBS->LocateDevicePath (
                  &gEfiSimpleFileSystemProtocolGuid,
                  &TempDevicePath,
                  &DeviceHandle
                  );
  if (!EFI_ERROR (Status)) {
    //
    // Simple File System is present without Block I/O, so assume media is fixed.
    //
    return IMAGE_FROM_FIXED_MEDIA;
  }

  //
  // File is not from an FV, Block I/O or Simple File System, so the only options
  // left are a PCI Option ROM and a Load File Protocol such as a PXE Boot from a NIC.  
  //
  TempDevicePath = (EFI_DEVICE_PATH_PROTOCOL *)File;
  while (!IsDevicePathEndType (TempDevicePath)) {
    nDevicePathSubType = DevicePathSubType (TempDevicePath);
    switch (DevicePathType (TempDevicePath)) {
    //EIP 219415 Start
    //Embedded OpROM
    case HARDWARE_DEVICE_PATH:

        if(nDevicePathSubType == HW_MEMMAP_DP) {
            //EIP 122339 Start: Return IMAGE_FROM_FV if the EFI_PCI_IO_PROTOCOL installed
            //on the same handle as the Device Path has the attribute EFI_PCI_IO_ATTRIBUTE_EMBEDDED_ROM
            DeviceHandle = NULL;
            //
            // Check if an instance of the EFI_PCI_IO_PROTOCOL is installed on the same handle
            // as the Device Path.  If an instance is found WorkAroundDevHandle contains the
            // handle for the Device Path and EFI_PCI_IO_PROTOCOL instance.
            //
            Status = pBS->LocateDevicePath(
                            &gEfiPciIoProtocolGuid,
                            &File,
                            &DeviceHandle
            );
            if(EFI_ERROR(Status)) break;

            Status = pBS->HandleProtocol(
                            DeviceHandle,
                            &gEfiPciIoProtocolGuid,
                            &PciIoInterface
            );
              
            if(EFI_ERROR(Status)) break;

            //
            // Using the EFI_PCI_IO_PROTOCOL get the value of the PCI controller's
            // Embedded Rom attribute (EFI_PCI_IO_ATTRIBUTE_EMBEDDED_ROM)
            //
            Status = PciIoInterface->Attributes(
                                    PciIoInterface,
                                    EfiPciIoAttributeOperationGet,
                                    0, //this parameter is ignored during Get operation
                                    &AttributesResult
            );
            if(EFI_ERROR(Status)) break;
            //
            // Check if the PCI controller's EFI_PCI_IO_ATTRIBUTE_EMBEDDED_ROM is set
            //          
            if(AttributesResult & EFI_PCI_IO_ATTRIBUTE_EMBEDDED_ROM)
                return IMAGE_FROM_FV;
            //EIP 122339 Stop
        }
        break;
    //EIP 219415 end
    case MEDIA_DEVICE_PATH:

      if (nDevicePathSubType == MEDIA_RELATIVE_OFFSET_RANGE_DP) {
        return IMAGE_FROM_OPTION_ROM;
      }
#if LOAD_UNSIGNED_EMBEDDED_SHELL == 1
      // Case for embedded FV application such as Shell(check GUID. BootOptions.h)
      if (nDevicePathSubType == MEDIA_VENDOR_DP && 
          !guidcmp(&((VENDOR_DEVICE_PATH*)TempDevicePath)->Guid, &AmiMediaDevicePathGuid)) {
            return IMAGE_FROM_FV;
      }
#endif
      break;

    case MESSAGING_DEVICE_PATH:

      if (nDevicePathSubType == MSG_MAC_ADDR_DP) {
        return IMAGE_FROM_REMOVABLE_MEDIA;
      } 
      break;
    }
    TempDevicePath = NextDevicePathNode (TempDevicePath);
  }
  
  return IMAGE_UNKNOWN; 
}

/**
  Caculate hash of Pe/Coff image based on the authenticode image hashing in
  PE/COFF Specification 8.0 Appendix A

  Caution: This function may receive untrusted input.
  PE/COFF image is external input, so this function will validate its data structure
  within this image buffer before use.

  @param[in]    HashAlg   Hash algorithm type.

  @retval TRUE            Successfully hash image.
  @retval FALSE           Fail in hash image.

**/
BOOLEAN
HashPeImage (
  IN  UINT32              HashAlg
  )
{
  EFI_STATUS                EfiStatus;    
  BOOLEAN                   Status;
  UINT16                    Magic;
  EFI_IMAGE_SECTION_HEADER  *Section;
  UINT8                     *HashBase;
  UINTN                     HashSize;
  UINTN                     SumOfBytesHashed;
  EFI_IMAGE_SECTION_HEADER  *SectionHeader;
  UINTN                     Index;
  UINTN                     Pos;

  const UINT8             *addr[MAX_ELEM_NUM]; // tbd. test if 20 elements is enough
  UINTN                   num_elem, len[MAX_ELEM_NUM];
  EFI_GUID                *EfiHashAlgorithmGuid;

  UINT32                    CertSize;
  UINT32                    NumberOfRvaAndSizes;

  SectionHeader = NULL;
  Status        = FALSE;
  EfiStatus     = EFI_SECURITY_VIOLATION;
  num_elem      = 0;
  //
  // Initialize context of hash.
  //
  ZeroMem (mImageDigest, MAX_DIGEST_SIZE);
  if (HashAlg == HASHALG_SHA1) {
    mImageDigestSize     = SHA1_DIGEST_SIZE;
    EfiHashAlgorithmGuid = &gEfiHashAlgorithmSha1Guid;
    mCertType            = &gEfiCertSha1Guid;
  } else if (HashAlg == HASHALG_SHA256) {
    mImageDigestSize     = SHA256_DIGEST_SIZE;
    EfiHashAlgorithmGuid = &gEfiHashAlgorithmSha256Guid;
    mCertType            = &gEfiCertSha256Guid;
  } else {
    return FALSE;
  }

  // 1.  Load the image header into memory.

  //
  // Measuring PE/COFF Image Header;
  // But CheckSum field and SECURITY data directory (certificate) are excluded
  //
  if (mNtHeader.Pe32->FileHeader.Machine == EFI_IMAGE_MACHINE_IA64 && mNtHeader.Pe32->OptionalHeader.Magic == EFI_IMAGE_NT_OPTIONAL_HDR32_MAGIC) {
    //
    // NOTE: Some versions of Linux ELILO for Itanium have an incorrect magic value 
    //       in the PE/COFF Header. If the MachineType is Itanium(IA64) and the 
    //       Magic value in the OptionalHeader is EFI_IMAGE_NT_OPTIONAL_HDR32_MAGIC
    //       then override the magic value to EFI_IMAGE_NT_OPTIONAL_HDR64_MAGIC
    //
    Magic = EFI_IMAGE_NT_OPTIONAL_HDR64_MAGIC;
  } else {
    //
    // Get the magic value from the PE/COFF Optional Header
    //
    Magic =  mNtHeader.Pe32->OptionalHeader.Magic;
  }
  
  //
  // 3.  Calculate the distance from the base of the image header to the image checksum address.
  // 4.  Hash the image header from its base to beginning of the image checksum.
  //
  HashBase = mImageBase;
  if (Magic == EFI_IMAGE_NT_OPTIONAL_HDR32_MAGIC) {
    //
    // Use PE32 offset.
    //
    HashSize = (UINTN) ((UINT8 *) (&mNtHeader.Pe32->OptionalHeader.CheckSum) - HashBase);
    NumberOfRvaAndSizes = mNtHeader.Pe32->OptionalHeader.NumberOfRvaAndSizes;
  } else if (Magic == EFI_IMAGE_NT_OPTIONAL_HDR64_MAGIC) {
    //
    // Use PE32+ offset.
    //
    HashSize = (UINTN) ((UINT8 *) (&mNtHeader.Pe32Plus->OptionalHeader.CheckSum) - HashBase);
    NumberOfRvaAndSizes = mNtHeader.Pe32Plus->OptionalHeader.NumberOfRvaAndSizes;
  } else {
    //
    // Invalid header magic number.
    //
    TRACE((TRACE_ALWAYS,"Invalid header magic number.\n"));
    goto Done;
  }

    if (HashSize != 0) 
    {
           addr[num_elem] = HashBase;
           len[num_elem++] =  HashSize;
    } else {
//TRACE((TRACE_ALWAYS,"Hash1.%x\n", HashSize));
        goto Done;}
  //
  // 5.  Skip over the image checksum (it occupies a single ULONG).
  //
  if (NumberOfRvaAndSizes <= EFI_IMAGE_DIRECTORY_ENTRY_SECURITY) {
    //
    // 6.  Since there is no Cert Directory in optional header, hash everything
    //     from the end of the checksum to the end of image header.
    //
    if (Magic == EFI_IMAGE_NT_OPTIONAL_HDR32_MAGIC) {
      //
      // Use PE32 offset.
      //
      HashBase = (UINT8 *) &mNtHeader.Pe32->OptionalHeader.CheckSum + sizeof (UINT32);
      HashSize = mNtHeader.Pe32->OptionalHeader.SizeOfHeaders - (UINTN) (HashBase - mImageBase);
    } else {
      //
      // Use PE32+ offset.
      //
      HashBase = (UINT8 *) &mNtHeader.Pe32Plus->OptionalHeader.CheckSum + sizeof (UINT32);
      HashSize = mNtHeader.Pe32Plus->OptionalHeader.SizeOfHeaders - (UINTN) (HashBase - mImageBase);
    }

    if (HashSize != 0) 
    {
           addr[num_elem] = HashBase;
           len[num_elem++] =  HashSize;
    } else {
//TRACE((TRACE_ALWAYS,"Hash2.%x\n", HashSize));
        goto Done;}
  } else {
    //
    // 7.  Hash everything from the end of the checksum to the start of the Cert Directory.
    //
    if (Magic == EFI_IMAGE_NT_OPTIONAL_HDR32_MAGIC) {
      //
      // Use PE32 offset.
      //
      HashBase = (UINT8 *) &mNtHeader.Pe32->OptionalHeader.CheckSum + sizeof (UINT32);
      HashSize = (UINTN) ((UINT8 *) (&mNtHeader.Pe32->OptionalHeader.DataDirectory[EFI_IMAGE_DIRECTORY_ENTRY_SECURITY]) - HashBase);
    } else {
      //
      // Use PE32+ offset.
      //
      HashBase = (UINT8 *) &mNtHeader.Pe32Plus->OptionalHeader.CheckSum + sizeof (UINT32);
      HashSize = (UINTN) ((UINT8 *) (&mNtHeader.Pe32Plus->OptionalHeader.DataDirectory[EFI_IMAGE_DIRECTORY_ENTRY_SECURITY]) - HashBase);
    }
    if (HashSize != 0) 
    {
           addr[num_elem] = HashBase;
           len[num_elem++] =  HashSize;
    } else {
//TRACE((TRACE_ALWAYS,"Hash3.%x\n", HashSize));
        goto Done;}

    //
    // 8.  Skip over the Cert Directory. (It is sizeof(IMAGE_DATA_DIRECTORY) bytes.)
    // 9.  Hash everything from the end of the Cert Directory to the end of image header.
    //
    if (Magic == EFI_IMAGE_NT_OPTIONAL_HDR32_MAGIC) {
      //
      // Use PE32 offset
      //
      HashBase = (UINT8 *) &mNtHeader.Pe32->OptionalHeader.DataDirectory[EFI_IMAGE_DIRECTORY_ENTRY_SECURITY + 1];
      HashSize = mNtHeader.Pe32->OptionalHeader.SizeOfHeaders - (UINTN) (HashBase - mImageBase);
    } else {
      //
      // Use PE32+ offset.
      //
      HashBase = (UINT8 *) &mNtHeader.Pe32Plus->OptionalHeader.DataDirectory[EFI_IMAGE_DIRECTORY_ENTRY_SECURITY + 1];
      HashSize = mNtHeader.Pe32Plus->OptionalHeader.SizeOfHeaders - (UINTN) (HashBase - mImageBase);
    }
    if (HashSize != 0) 
    {
           addr[num_elem] = HashBase;
           len[num_elem++] =  HashSize;
    } else {
//TRACE((TRACE_ALWAYS,"Hash4.%x\n", HashSize));
        goto Done;}
  }

  //
  // 10. Set the SUM_OF_BYTES_HASHED to the size of the header.
  //
  if (Magic == EFI_IMAGE_NT_OPTIONAL_HDR32_MAGIC) {
    //
    // Use PE32 offset.
    //
    SumOfBytesHashed = mNtHeader.Pe32->OptionalHeader.SizeOfHeaders;
  } else {
    //
    // Use PE32+ offset
    //
    SumOfBytesHashed = mNtHeader.Pe32Plus->OptionalHeader.SizeOfHeaders;
  }


  Section = (EFI_IMAGE_SECTION_HEADER *) (
               mImageBase +
               mPeCoffHeaderOffset +
               sizeof (UINT32) +
               sizeof (EFI_IMAGE_FILE_HEADER) +
               mNtHeader.Pe32->FileHeader.SizeOfOptionalHeader
               );
  //
  // 11. Build a temporary table of pointers to all the IMAGE_SECTION_HEADER
  //     structures in the image. The 'NumberOfSections' field of the image
  //     header indicates how big the table should be. Do not include any
  //     IMAGE_SECTION_HEADERs in the table whose 'SizeOfRawData' field is zero.
  //
// TRACE((TRACE_ALWAYS,"Num Sections = %x\n",  mNtHeader.Pe32->FileHeader.NumberOfSections));

// Security review [305408]: HashPeImage does not validate NumberOfSections field
  Pos = sizeof (EFI_IMAGE_SECTION_HEADER) * mNtHeader.Pe32->FileHeader.NumberOfSections;
  if(Pos > mImageSize)
    goto Done;

  EfiStatus = pBS->AllocatePool(EfiBootServicesData, Pos, &SectionHeader);
  if (SectionHeader == NULL || EFI_ERROR(EfiStatus)) {
//TRACE((TRACE_ALWAYS,"Hash4.\n"));
    goto Done;

  }
  MemSet(SectionHeader, Pos, 0);
  //
  // 12.  Using the 'PointerToRawData' in the referenced section headers as
  //      a key, arrange the elements in the table in ascending order. In other
  //      words, sort the section headers according to the disk-file offset of
  //      the section.
  //
  for (Index = 0; Index < mNtHeader.Pe32->FileHeader.NumberOfSections; Index++) {
    Pos = Index;

    // Security review EIP[104046]:6. HashPeImage does not validate NumberOfSections field
    if(((UINT64)Section + sizeof (EFI_IMAGE_SECTION_HEADER))> ((UINT64)mImageBase+mImageSize) )
        goto Done;

    while ((Pos > 0) && (Section->PointerToRawData < SectionHeader[Pos - 1].PointerToRawData)) {
      CopyMem (&SectionHeader[Pos], &SectionHeader[Pos - 1], sizeof (EFI_IMAGE_SECTION_HEADER));
      Pos--;
    }
    CopyMem (&SectionHeader[Pos], Section, sizeof (EFI_IMAGE_SECTION_HEADER));
    Section += 1;
  }

  //
  // 13.  Walk through the sorted table, bring the corresponding section
  //      into memory, and hash the entire section (using the 'SizeOfRawData'
  //      field in the section header to determine the amount of data to hash).
  // 14.  Add the section's 'SizeOfRawData' to SUM_OF_BYTES_HASHED .
  // 15.  Repeat steps 13 and 14 for all the sections in the sorted table.
  //
  for (Index = 0; Index < mNtHeader.Pe32->FileHeader.NumberOfSections; Index++) {
    Section = &SectionHeader[Index];
    if (Section->SizeOfRawData == 0) {
      continue;
    }

//TRACE((TRACE_ALWAYS,"Section->PointerToRawData = %x\nSection->SizeOfRawData = %x\nSumOfBytesHashed = %x\n",Section->PointerToRawData, Section->SizeOfRawData, SumOfBytesHashed+Section->SizeOfRawData));
    // Security review EIP[104046]: 5.HashPeImage does not validate PointerToRawData and SizeOfRawData fields
    if( ((UINT64)Section->PointerToRawData + Section->SizeOfRawData) > mImageSize )
        goto Done;

    HashBase  = mImageBase + Section->PointerToRawData;
    HashSize  = (UINTN) Section->SizeOfRawData;

    addr[num_elem] = HashBase;
    len[num_elem++] =  HashSize;
    if(num_elem >= MAX_ELEM_NUM)
//        goto Done;
         {
TRACE((TRACE_ALWAYS,"MAX_ELEM_NUM.1 = %d\n", num_elem));
        goto Done;}
    // Security review EIP[125931]: HashPeImage does not validate certificate table offset and size
    if (((UINT64)SumOfBytesHashed+HashSize) > mImageSize) 
        goto Done;

    SumOfBytesHashed += HashSize;
  }

  //
  // 16.  If the file size is greater than SUM_OF_BYTES_HASHED, there is extra
  //      data in the file that needs to be added to the hash. This data begins
  //      at file offset SUM_OF_BYTES_HASHED and its length is:
  //             FileSize  -  (CertDirectory->Size)
  //
//dbg
//TRACE((TRACE_ALWAYS,"mImageSize > SumOfBytesHashed.\n%x > %x\n", mImageSize, SumOfBytesHashed));
//dbg
  if (mImageSize > SumOfBytesHashed) {

    HashBase = mImageBase + SumOfBytesHashed;

    if (NumberOfRvaAndSizes <= EFI_IMAGE_DIRECTORY_ENTRY_SECURITY) {
      CertSize = 0;
    } else {
      if (Magic == EFI_IMAGE_NT_OPTIONAL_HDR32_MAGIC) {
        //
        // Use PE32 offset.
        //
        CertSize = mNtHeader.Pe32->OptionalHeader.DataDirectory[EFI_IMAGE_DIRECTORY_ENTRY_SECURITY].Size;
      } else {
        //
        // Use PE32+ offset.
        //
        CertSize = mNtHeader.Pe32Plus->OptionalHeader.DataDirectory[EFI_IMAGE_DIRECTORY_ENTRY_SECURITY].Size;
      }
    }

    if (mImageSize > ((UINT64)CertSize + SumOfBytesHashed)) {
      HashSize = (UINTN) (mImageSize - CertSize - SumOfBytesHashed);

//TRACE((TRACE_ALWAYS,"\nData beyond nSumOfBytesHashed\nBase = %x, Size = %x\n",SumOfBytesHashed, HashSize));

       addr[num_elem] = HashBase;
       len[num_elem++] =  HashSize;
       if(num_elem >= MAX_ELEM_NUM)
//         goto Done;
         {
TRACE((TRACE_ALWAYS,"MAX_ELEM_NUM.2=%d\n", num_elem));
        goto Done;}

    } else if (mImageSize < ((UINT64)CertSize + SumOfBytesHashed)) {
TRACE((TRACE_ALWAYS,"mImageSize < CertSize + SumOfBytesHashed.\n%d < %d\n", mImageSize, CertSize + SumOfBytesHashed));
          goto Done;
        } 
        else 
            HashSize = 0;
 // ???     HashBase += CertSize;
//TRACE((TRACE_ALWAYS,"\nData beyond CertDir\nBase = %x, Size = %x\n",SumOfBytesHashed+HashSize+CertSize, mImageSize-(SumOfBytesHashed+HashSize+CertSize)));
  }
  EfiStatus = mDigitalSigProtocol->Hash(
              mDigitalSigProtocol, 
              EfiHashAlgorithmGuid, num_elem, addr, len, (UINT8*)&mImageDigest); 

TRACE((TRACE_ALWAYS,"Found HashElements %d\nImageHash: [%2X],[%2X],..\n", num_elem, mImageDigest[0], mImageDigest[1]));

  if(!EFI_ERROR(EfiStatus))
    Status = TRUE;

Done:  

  if (SectionHeader != NULL) {
    pBS->FreePool (SectionHeader);
  }
  // Security review EIP[104046]: 4.HashPeImage returns TRUE even in error case
  // Status = FALSE unless updated to TRUE in the final Hash step before "Done" label
  return Status;
}

/**
  Recognize the Hash algorithm in PE/COFF Authenticode and caculate hash of
  Pe/Coff image based on the authenticode image hashing in PE/COFF Specification
  8.0 Appendix A

  Caution: This function may receive untrusted input.
  PE/COFF image is external input, so this function will validate its data structure
  within this image buffer before use.

  @param[in]  AuthData            Pointer to the Authenticode Signature retrieved from signed image.
  @param[in]  AuthDataSize        Size of the Authenticode Signature in bytes.
  
  @retval EFI_UNSUPPORTED             Hash algorithm is not supported.
  @retval EFI_SUCCESS                 Hash successfully.

**/
EFI_STATUS
HashPeImageByType (
  IN UINT8              *AuthData,
  IN UINTN              AuthDataSize
  )
{
  EFI_STATUS                Status;
  UINT8                     DigestAlgo;  
  UINT8                    *pDigestAlgo;
  UINTN                     Size;

// get Digest Algorithm
  Size         = 0;  
  pDigestAlgo  = (UINT8*)&DigestAlgo;
  Status = mDigitalSigProtocol->Pkcs7Verify (
         mDigitalSigProtocol,
         AuthData,
         AuthDataSize,
         NULL,
         0,
         &pDigestAlgo,        // returns DER Ptr to Sign Cert
         &Size,
         Pkcs7GetDigestAlgorithm,
         LOCK
         );
  if (EFI_ERROR(Status)) 
    return Status;

  switch(DigestAlgo) {
    case SHA1:
          if (!HashPeImage (HASHALG_SHA1)) {
              Status = EFI_SECURITY_VIOLATION;
          }
        break;
    case SHA256:
          if (!HashPeImage (HASHALG_SHA256)) {
              Status = EFI_SECURITY_VIOLATION;
          }
        break;
    default:
        Status = EFI_UNSUPPORTED;
        break;
  }

  return Status;
}

/**
  Returns the size of a given image execution info table in bytes.

  This function returns the size, in bytes, of the image execution info table specified by
  ImageExeInfoTable. If ImageExeInfoTable is NULL, then 0 is returned.

  @param  ImageExeInfoTable          A pointer to a image execution info table structure.
  
  @retval 0       If ImageExeInfoTable is NULL.
  @retval Others  The size of a image execution info table in bytes.

**/
UINTN
GetImageExeInfoTableSize (
  EFI_IMAGE_EXECUTION_INFO_TABLE        *ImageExeInfoTable
  )
{
  UINTN                     Index;
  EFI_IMAGE_EXECUTION_INFO  *ImageExeInfoItem;
  UINTN                     TotalSize;

  if (ImageExeInfoTable == NULL) {
    return 0;
  }

  ImageExeInfoItem  = (EFI_IMAGE_EXECUTION_INFO *) ((UINT8 *) ImageExeInfoTable + sizeof (EFI_IMAGE_EXECUTION_INFO_TABLE));
  TotalSize         = sizeof (EFI_IMAGE_EXECUTION_INFO_TABLE);
  for (Index = 0; Index < ImageExeInfoTable->NumberOfImages; Index++) {
    TotalSize += ImageExeInfoItem->InfoSize;
    ImageExeInfoItem = (EFI_IMAGE_EXECUTION_INFO *) ((UINT8 *) ImageExeInfoItem + ImageExeInfoItem->InfoSize);
  }

  return TotalSize;
}

/**
  Create an Image Execution Information Table entry and add it to system configuration table.

  @param[in]  Action          Describes the action taken by the firmware regarding this image.
  @param[in]  Name            Input a null-terminated, user-friendly name.
  @param[in]  DevicePath      Input device path pointer.
  @param[in]  Signature       Input signature info in EFI_SIGNATURE_LIST data structure.
  @param[in]  SignatureSize   Size of signature.
  
**/
VOID
AddImageExeInfo (
  IN       EFI_IMAGE_EXECUTION_ACTION       Action, 
  IN       CHAR16                           *Name OPTIONAL, 
  IN CONST EFI_DEVICE_PATH_PROTOCOL         *DevicePath,
  IN       EFI_SIGNATURE_LIST               *Signature OPTIONAL,
  IN       UINTN                            SignatureSize
  )
{
  EFI_STATUS                      Status;
  EFI_IMAGE_EXECUTION_INFO_TABLE  *ImageExeInfoTable;
  EFI_IMAGE_EXECUTION_INFO_TABLE  *NewImageExeInfoTable;
  EFI_IMAGE_EXECUTION_INFO        *ImageExeInfoEntry;
  UINTN                           ImageExeInfoTableSize;
  UINTN                           NewImageExeInfoEntrySize;
  UINTN                           NameStringLen;
  UINTN                           DevicePathSize;

  NewImageExeInfoTable  = NULL;
  ImageExeInfoEntry     = NULL;
  NameStringLen         = sizeof (CHAR16);

  if (DevicePath == NULL) {
    return ;
  }

  if (Name != NULL) {
    NameStringLen = StrSize (Name);
  }

  ImageExeInfoTable = GetEfiConfigurationTable(pST, &gEfiImageSecurityDatabaseGuid);
  if (ImageExeInfoTable != NULL) {
    //
    // The table has been found!
    // We must enlarge the table to accmodate the new exe info entry.
    //
    ImageExeInfoTableSize = GetImageExeInfoTableSize (ImageExeInfoTable);
  } else {
    //
    // Not Found!
    // We should create a new table to append to the configuration table.
    //
    ImageExeInfoTableSize = sizeof (EFI_IMAGE_EXECUTION_INFO_TABLE);
  }

  DevicePathSize            = DPLength(DevicePath);
  NewImageExeInfoEntrySize  = sizeof (EFI_IMAGE_EXECUTION_INFO) + NameStringLen + DevicePathSize + SignatureSize;

  Status = pBS->AllocatePool(EfiRuntimeServicesData, ImageExeInfoTableSize + NewImageExeInfoEntrySize, &NewImageExeInfoTable);
  if(EFI_ERROR(Status)) return;

  if (ImageExeInfoTable != NULL) {
    CopyMem (NewImageExeInfoTable, ImageExeInfoTable, ImageExeInfoTableSize);
  } else {
    NewImageExeInfoTable->NumberOfImages = 0;
  }
  NewImageExeInfoTable->NumberOfImages++;
  ImageExeInfoEntry = (EFI_IMAGE_EXECUTION_INFO *) ((UINT8 *) NewImageExeInfoTable + ImageExeInfoTableSize);
  //
  // Update new item's infomation.
  //
  ImageExeInfoEntry->Action   = Action;
  ImageExeInfoEntry->InfoSize = (UINT32) NewImageExeInfoEntrySize;

  if (Name != NULL) {
    CopyMem ((UINT8 *) &ImageExeInfoEntry->InfoSize + sizeof (UINT32), Name, NameStringLen);
  } else {
    ZeroMem ((UINT8 *) &ImageExeInfoEntry->InfoSize + sizeof (UINT32), NameStringLen);
  }
  CopyMem (
    (UINT8 *) &ImageExeInfoEntry->InfoSize + sizeof (UINT32) + NameStringLen,
    DevicePath,
    DevicePathSize
    );
  if (Signature != NULL) {
    CopyMem (
      (UINT8 *) &ImageExeInfoEntry->InfoSize + sizeof (UINT32) + NameStringLen + DevicePathSize,
      Signature,
      SignatureSize
      );
  }
  //
  // Update/replace the image execution table.
  //
  Status = pBS->InstallConfigurationTable (&gEfiImageSecurityDatabaseGuid, (VOID *) NewImageExeInfoTable);
  ASSERT_EFI_ERROR (Status);
  //
  // Free Old table data!
  //
  if (ImageExeInfoTable != NULL) {
    pBS->FreePool (ImageExeInfoTable);
  }
}

/**
  Create a Boot Image Certificate table entry and add it to system configuration table.

  @param[in]  Name            Input a null-terminated, user-friendly name.
  @param[in]  DevicePath      Input device path pointer.
  @param[in]  Signature       Input signature info in EFI_SIGNATURE_LIST data structure.
  @param[in]  SignatureSize   Size of signature.
  
**/
VOID
AddBootImageCertInfo (
  IN       CHAR16                           *Name OPTIONAL, 
  IN       UINT32                           SignatureOffs,
  IN       UINT32                           SignatureSize
  )
{
    EFI_STATUS                 Status;
    AMI_VALID_CERT_IN_SIG_DB  *BootImageCertInfoTable;
    UINTN                      BootImageCertInfoTableSize;

    if(SignatureOffs == 0 || SignatureSize == 0)
    return;
    
    BootImageCertInfoTable = GetEfiConfigurationTable(pST, &gBootImageCertTblGuid);
    if (BootImageCertInfoTable == NULL) {
        //
        // Not Found!
        // We should create a new table.
        //
        BootImageCertInfoTableSize = sizeof (AMI_VALID_CERT_IN_SIG_DB);
        Status = pBS->AllocatePool(EfiRuntimeServicesData, BootImageCertInfoTableSize, &BootImageCertInfoTable);
        if(EFI_ERROR(Status)) return;
        //
        // Update/replace the image execution table.
        //
        Status = pBS->InstallConfigurationTable (&gBootImageCertTblGuid, (VOID *) BootImageCertInfoTable);
        ASSERT_EFI_ERROR (Status);
        TRACE((TRACE_ALWAYS,"Install BootImageCert Table ...%r\n", Status));
        if (EFI_ERROR (Status)) return;
    }
    //
    // Update Table's infomation.
    //
    BootImageCertInfoTable->SigOffset = SignatureOffs;
    BootImageCertInfoTable->SigLength = SignatureSize;

TRACE((TRACE_ALWAYS,"BootImage Cert in db\nOffset=%X\nLength=%X\n", BootImageCertInfoTable->SigOffset, BootImageCertInfoTable->SigLength));
}

/**
  Discover if the UEFI image is authorized by user's policy setting.

  @param[in]    Policy            Specify platform's policy setting. 
  @param[in]    Action            Image Validation status. 

  @retval EFI_ACCESS_DENIED       Image is not allowed to run.
  @retval EFI_SECURITY_VIOLATION  Image is deferred.
  @retval EFI_SUCCESS             Image is authorized to run.

**/
EFI_STATUS
ImageAuthorization (
  IN UINT32     Policy,
  IN UINT32     Action
  )
{
    EFI_STATUS    Status;
    EFI_INPUT_KEY Key = {0,0};
    UINTN         Index;
    BOOLEAN       bQuery;

    Status = EFI_ACCESS_DENIED;

    switch (Policy) {

    case QUERY_USER_ON_SECURITY_VIOLATION:
        // Conditions to allow overwrite of Execution Policy:
        // 1. Output Console available
        if((pST->ConIn != NULL && pST->ConOut != NULL))
        {
            pST->ConOut->OutputString(pST->ConOut, mNotifyString1);
            bQuery = TRUE;
            switch(Action) {
                case EFI_IMAGE_EXECUTION_AUTH_SIG_NOT_FOUND: // not found in db
                    pST->ConOut->OutputString(pST->ConOut, mNotifyString3);
                    break;
                case EFI_IMAGE_EXECUTION_AUTH_SIG_FOUND:    // found in dbx
                    pST->ConOut->OutputString(pST->ConOut, mNotifyString4);
                    break;
                case EFI_IMAGE_EXECUTION_AUTH_SIG_FAILED:
                case EFI_IMAGE_EXECUTION_AUTH_UNTESTED:
                    pST->ConOut->OutputString(pST->ConOut, mNotifyString5);
                    break;
                default:
                    bQuery = FALSE;
                    break;
            }
            if(!bQuery) break;
            //Wait for key
            pST->ConOut->OutputString(pST->ConOut, mNotifyString2);
Repeat:
            pBS->WaitForEvent( 1, &pST->ConIn->WaitForKey, &Index );
            Status = pST->ConIn->ReadKeyStroke( pST->ConIn, &Key );
            if (!EFI_ERROR (Status)) {
              if ((Key.UnicodeChar == L'y') || (Key.UnicodeChar == L'Y')) { //yes
                Status = EFI_SUCCESS;
              } else if ((Key.UnicodeChar == L'n') || (Key.UnicodeChar == L'N')) { //no
                Status = EFI_ACCESS_DENIED;
              } else {
                goto Repeat;
              }
            }
            pST->ConOut->OutputString(pST->ConOut, L"\r\n");
        } 
        break;

    case DEFER_EXECUTE_ON_SECURITY_VIOLATION:
        Status = EFI_SECURITY_VIOLATION;
        break;

    //  case DENY_EXECUTE_ON_SECURITY_VIOLATION:
    default:
        Status = EFI_ACCESS_DENIED;
        break;
    }

TRACE((TRACE_ALWAYS,"Image Authorization policy...%r\n", Status));

    return Status;
}

/**
  Advanced check in Signature Database
  Check whether signature is located in target database

  @param[in]  Signature           Pointer to signature that is searched for.
  @param[in]  SignatureSize       Size of Signature.
  @param[in]  SignatureType       Type of the Certificate, Guid

  @return TRUE - found in IsSigForbidden            
  @return FALSE            

**/
BOOLEAN
IsSignatureFoundInDatabase (
  IN CHAR16          *Name,
  EFI_GUID           *SignatureType,
  IN UINT8           *Signature, 
  IN UINTN            SignatureSize
  )
{
  EFI_SIGNATURE_LIST  *CertList;
  EFI_SIGNATURE_DATA  *Cert;
  UINT8               *Data;
  UINTN               DataSize;
  UINTN               Index;
  UINTN               CertCount;
  BOOLEAN             IsSigFound;

  //
  // Read signature database variable.
  //
  IsSigFound   = FALSE;

  //
  // Get Signature Database variable.
  //

  Data = GetEfiImageSecurityDatabaseVariableEx (Name, &DataSize);

  if (Data != NULL) {
// not an error if no "dbx" defined
      //
      // Enumerate all signature data in SigDB to check if executable's signature exists.
      //
      CertList = (EFI_SIGNATURE_LIST *) Data;
      while (!IsSigFound && (DataSize > 0) && (DataSize >= CertList->SignatureListSize)) {
        if (!guidcmp(&CertList->SignatureType, SignatureType)) { // Cert types do match 
            CertCount = (CertList->SignatureListSize - sizeof (EFI_SIGNATURE_LIST) - CertList->SignatureHeaderSize) / CertList->SignatureSize;
            Cert      = (EFI_SIGNATURE_DATA *) ((UINT8 *) CertList + sizeof (EFI_SIGNATURE_LIST) + CertList->SignatureHeaderSize);
            if (CertList->SignatureSize == (sizeof(EFI_SIGNATURE_DATA) - 1 + SignatureSize)) {
              for (Index = 0; Index < CertCount; Index++) {
                if (MemCmp(Cert->SignatureData, Signature, SignatureSize) == 0) {
                  //
                  // Find the signature in database.
                  //
                  IsSigFound = TRUE;
                  break;
                }
                Cert = (EFI_SIGNATURE_DATA *) ((UINT8 *) Cert + CertList->SignatureSize);
              }
            }
        } // next CertList
        DataSize -= CertList->SignatureListSize;
        CertList = (EFI_SIGNATURE_LIST *) ((UINT8 *) CertList + CertList->SignatureListSize);
      }
      pBS->FreePool (Data);
  }

  return IsSigFound;
}


/**
  Verify PKCS#7 SignedData using certificate found in Variable which formatted
  as EFI_SIGNATURE_LIST. The Variable may be PK, KEK, DB or DBX.

  @param VariableName  Name of Variable to search for Certificate.

  @retval TRUE         Image pass verification.
  @retval FALSE        Image fail verification.

**/
BOOLEAN
IsPkcsSignedDataVerifiedBySignatureList (
  IN UINT8          *AuthData,
  IN UINTN           AuthDataSize,
  IN CHAR16         *VariableName,
  IN UINT8           Operation
  )
{
    EFI_STATUS               Status;
    EFI_SIGNATURE_LIST      *CertList;
    EFI_SIGNATURE_DATA      *Cert;
    UINT32                   CertCount;
    UINT32                   Index;
    UINT8                   *Data;
    UINTN                    DataSize;
    UINT8                   *RootCert;
    UINTN                    RootCertSize;
    UINT8                   *SigCert;
    UINTN                    SigCertSize;
    BOOLEAN                  IsVerified;
    EFI_TIME                *TimeStamp;
    INT32                    TimeOfRevocationLong;
    UINT8                    ValidCertType;
    BOOLEAN                  bVerifyTimeStampStatus;
    BOOLEAN                  bProcessVerifyTimeStampStatus;

    CertList              = NULL;
    Cert                  = NULL;
    RootCert              = NULL;
    RootCertSize          = 0;
    IsVerified            = FALSE;
    ValidCertType         = CertUndefined;
    bVerifyTimeStampStatus= FALSE;
    bProcessVerifyTimeStampStatus = FALSE;

    mTimeOfSigningLong    = 0;
    TimeOfRevocationLong  = 0;
    // Verify the certificate's header
    //
    // Find certificate in store and verify authenticode struct.
    //
    Data = GetEfiImageSecurityDatabaseVariableEx (VariableName, &DataSize);

    if (!Data) 
        return IsVerified;

TRACE((TRACE_ALWAYS,"\nLook for a match in '%S'===>\n\n", VariableName));

    CertList = (EFI_SIGNATURE_LIST *)Data; 

    //
    // TO DO Optimization. 
    //  1. Find Root CA Cert Ptr or Signer Cert if Root is not found
    //  2. loop thru Trust Cert list and compare each one against Root CA cert(verify SignCert signature with Trust Cert)
    //  3. If found, break the 'while' loop and Pkcs7Verify with Trust Cert
    //  
    //
    // Find Cert Enrolled in database to verify the signature in pkcs7 signed data.
    // 
    // here should be a loop thru Cert list till CertCount
    while ((DataSize > 0) && (DataSize >= CertList->SignatureListSize)) {

        if(!guidcmp(&CertList->SignatureType, &gEfiCertX509Guid))
            ValidCertType = CertX509;
        else
            if(!guidcmp(&CertList->SignatureType, mCertType))
                ValidCertType = CertSha256;
            else
                if(!guidcmp(&CertList->SignatureType, &gEfiCertX509Sha256Guid))
                    ValidCertType = CertX509Sha256;
                else
                    if(!guidcmp(&CertList->SignatureType, &gEfiCertX509Sha384Guid))
                        ValidCertType = CertX509Sha384;
                    else
                        if(!guidcmp(&CertList->SignatureType, &gEfiCertX509Sha512Guid))
                            ValidCertType = CertX509Sha512;

          if (ValidCertType)
          {
            Cert       = (EFI_SIGNATURE_DATA *) ((UINT8 *) CertList + sizeof (EFI_SIGNATURE_LIST) + CertList->SignatureHeaderSize);
            CertCount  = (CertList->SignatureListSize - sizeof (EFI_SIGNATURE_LIST) - CertList->SignatureHeaderSize) / CertList->SignatureSize;
            RootCertSize  = CertList->SignatureSize-sizeof(EFI_GUID); // sig data structure starts with SigOwner Guid
TRACE((TRACE_ALWAYS,"Signature Type %g\nRootCertSize = %X\n",CertList->SignatureType, RootCertSize));

            for (Index = 0; Index < CertCount; Index++) {
              //
              // Iterate each Signature Data Node within this CertList for verify.
              //
                RootCert = Cert->SignatureData;
                switch(ValidCertType) {
// is Sha256/Sha1 
                case CertSha256:
                    if(RootCertSize == mImageDigestSize && 
                        MemCmp(RootCert, mImageDigest, mImageDigestSize) == 0) {
TRACE((TRACE_ALWAYS,"Hash Cert match found...\n"));
                      //
                      // Found the signature in database.
                      //
                        IsVerified = TRUE;
                    }
                    break;
// x509, x509_ShaXXX
/*
Revocation is true:
- return success && Time = 0
- return success && Time != 0 && VerifyTimeStampStatus
- success 
if success but mVerifyTimeStampStatus = ACCESS_DENIED = return FAIL
timestamp non-0 Year > 0
*/
                case CertX509Sha256:
                case CertX509Sha384:
                case CertX509Sha512:
                    switch(ValidCertType) {
                        case CertX509Sha256:
                            TimeStamp = &((EFI_CERT_X509_SHA256*)RootCert)->TimeOfRevocation;
                            break;
                        case CertX509Sha384:
                            TimeStamp = &((EFI_CERT_X509_SHA384*)RootCert)->TimeOfRevocation;
                            break;
                        case CertX509Sha512:
                            TimeStamp = &((EFI_CERT_X509_SHA512*)RootCert)->TimeOfRevocation;
                            break;
                    }
                    // Check the timestamp cert validity the valid certificate in allowed database (dbt).
                    if(!bProcessVerifyTimeStampStatus) {
                        bVerifyTimeStampStatus = IsPkcsSignedDataVerifiedBySignatureList (AuthData, AuthDataSize, EFI_IMAGE_SECURITY_DATABASE2, Pkcs7TimeStampCertValidateGet); 
                        bProcessVerifyTimeStampStatus = TRUE;
                    }
                    if(os_mktime(TimeStamp->Year, TimeStamp->Month, TimeStamp->Day, TimeStamp->Hour, TimeStamp->Minute, TimeStamp->Second,&TimeOfRevocationLong))
                        TimeOfRevocationLong = 0;
TRACE((TRACE_ALWAYS,"\nTimeStamp cert validate %s\nTimeOfSigning %X\nTimeOfRevocation %X\n",  (!bVerifyTimeStampStatus?"FAIL":"PASS"), mTimeOfSigningLong, TimeOfRevocationLong));
                    if(TimeOfRevocationLong) {
                        if(!bVerifyTimeStampStatus) {
                            IsVerified = TRUE;  // found in dbx -> image is revoked!
                            break;
                        }
                        // keep looking for cert with sign time passed revocation
                       if(mTimeOfSigningLong < TimeOfRevocationLong)
                            break;
                    }
                    case CertX509:
TRACE((TRACE_ALWAYS,"proceed with Pkcs7Verify...\n"));  
                    //
                    //
                    // Verify Authenticode struct for image's current certificate.
                    //
                    // using protocol
                    SigCert       = mImageDigest;
                    SigCertSize   = mImageDigestSize;
                    Status = mDigitalSigProtocol->Pkcs7Verify (
                         mDigitalSigProtocol,
                         AuthData,
                         AuthDataSize,
                         RootCert,
                         RootCertSize,
                        // mDigest, DigestLen
                         &SigCert,
                         &SigCertSize,
                         Operation,             // Operation; Pkcs7CertValidate OR Pkcs7CertGetMatchInCertChain
                         KEEP                   // Flags 
                         );
TRACE((TRACE_ALWAYS,"====> %r\n", Status));
                    if (!EFI_ERROR(Status)) {
                        IsVerified = TRUE; // found matching certificate in the image 
                        switch(Operation) {
                            case Pkcs7TimeStampCertValidateGet:
                                mTimeOfSigningLong = (INT32)SigCertSize;
                                break;    
                            case Pkcs7CertValidate:
                                // only x509 certs frm db are measured in PCR[7]
                                mTrustSigDbOffs = (UINT32)(UINT8*)(((UINT8*)Cert-Data));
                                mTrustSigDbSize = CertList->SignatureSize;
                                break;    
                        }
                    }
                    break;
                   default :
                       goto Exit;
                } // switch
                if (IsVerified)
                {
                    goto Exit;
                }
                Cert = (EFI_SIGNATURE_DATA *) ((UINT8 *) Cert + CertList->SignatureSize);
            }  // end for    
        } // end If 

        DataSize -= CertList->SignatureListSize;
        CertList = (EFI_SIGNATURE_LIST *) ((UINT8 *) CertList + CertList->SignatureListSize);
    } // end while
Exit:
    pBS->FreePool (Data);
TRACE((TRACE_ALWAYS,"\n<===%s cert match in '%S'\n",(IsVerified?"Got":"No"), VariableName));
    return IsVerified;
}


//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   DxeImageVerificationHandler
//
// Description: Handle for Security Architectural Protocol
//        Provide verification service for signed images, which include both signature validation
//        and platform policy control. For signature types, both UEFI WIN_CERTIFICATE_UEFI_GUID and
//        MSFT Authenticode type signatures are supported.
//
//        In this implementation, only verify external executables when in USER MODE.
//        Executables from FV is bypass, so pass in AuthenticationStatus is ignored.
//
//        The image verification policy is:
//          If the image is signed,
//            At least one valid signature or at least one hash value of the image must match a record
//            in the security database "db", and no valid signature nor any hash value of the image may
//            be reflected in the security database "dbx".
//          Otherwise, the image is not signed,
//            The SHA256 hash value of the image must match a record in the security database "db", and
//            not be reflected in the security data base "dbx".
//
//        Caution: This function may receive untrusted input.
//          PE/COFF image is external input, so this function will validate its data structure
//          within this image buffer before use.
//
//  Input:
//     File                   This is a pointer to the device path of the file that is
//                            being dispatched. This will optionally be used for logging.
//     FileBuffer             File buffer matches the input file device path.
//     FileSize               Size of File buffer matches the input file device path.
//
// Output:      EFI_STATUS
//
//      EFI_SUCCESS            The file specified by File did authenticate, and the
//                             platform policy dictates that the DXE Core may use File.
//      EFI_INVALID_PARAMETER  File is NULL.
//      EFI_SECURITY_VIOLATION The file specified by File did not authenticate, and
//                             the platform policy dictates that File should be placed
//                             in the untrusted state. A file may be promoted from
//                             the untrusted to the trusted state at a future time
//                             with a call to the Trust() DXE Service.
//      EFI_ACCESS_DENIED      The file specified by File did not authenticate, and
//                             the platform policy dictates that File should not be
//                             used for any purpose.
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS
DxeImageVerificationHandler (
  IN  CONST EFI_DEVICE_PATH_PROTOCOL   *File,
  IN VOID                      *FileBuffer,
  IN UINTN                     FileSize,
  IN  BOOLEAN                  BootPolicy
  )

{
  EFI_STATUS                  Status;
  UINT16                      Magic;
  EFI_IMAGE_DOS_HEADER        *DosHdr;
  EFI_STATUS                  VerifyStatus;
  EFI_SIGNATURE_LIST          *SignatureList;
  UINTN                       SignatureListSize;
  EFI_SIGNATURE_DATA          *Signature;
  EFI_IMAGE_EXECUTION_ACTION  Action;
  WIN_CERTIFICATE             *WinCertificate;
  UINT32                      Policy;
  BOOLEAN                     bFileRead;  

  EFI_PEI_PE_COFF_LOADER_IMAGE_CONTEXT ImageContext;
  UINT32                               NumberOfRvaAndSizes;

  WIN_CERTIFICATE_EFI_PKCS             *PkcsCertData;
  WIN_CERTIFICATE_UEFI_GUID            *WinCertUefiGuid;
  UINT8                                *AuthData;
  UINTN                                 AuthDataSize;
  EFI_IMAGE_DATA_DIRECTORY            *SecDataDir;
  UINT32                                OffSet;


  SignatureList     = NULL;
  SignatureListSize = 0;
  WinCertificate    = NULL;
  SecDataDir        = NULL;
  PkcsCertData      = NULL;
  Action            = EFI_IMAGE_EXECUTION_AUTH_UNTESTED;
  VerifyStatus      = EFI_ACCESS_DENIED;
  Status            = EFI_ACCESS_DENIED;
  bFileRead         = FALSE;

  mImageDigestSize  = 0;
  mCertType         = NULL;
  //
  // Check the image type and get policy setting.
  //
  switch (GetImageType (File)) {

  case IMAGE_FROM_FV:
    Policy = ALWAYS_EXECUTE;
    break;

  case IMAGE_FROM_OPTION_ROM:
    Policy = mSecureBootSetup.Load_from_OROM;
    break;

  case IMAGE_FROM_REMOVABLE_MEDIA:
    Policy = mSecureBootSetup.Load_from_REMOVABLE_MEDIA;
    break;

  case IMAGE_FROM_FIXED_MEDIA:
    Policy = mSecureBootSetup.Load_from_FIXED_MEDIA;
    break;

  default:
TRACE((TRACE_ALWAYS,"Unknown Image Path\n"));
    Policy = DENY_EXECUTE_ON_SECURITY_VIOLATION;
    break;
  }

  //
  // If policy is always/never execute, return directly.
  //
  if (Policy == ALWAYS_EXECUTE) {
    return EFI_SUCCESS;
  } else 
    if (Policy == NEVER_EXECUTE) {
        return EFI_ACCESS_DENIED;
    }

  if (FileBuffer == NULL) {
  //
  // Read the PE/COFF file.
  //
    TRACE((TRACE_ALWAYS,"FileAuthentication\nFileType = %x, SubType = %x\n", File->Type, File->SubType));    
    Status = ReadImage(FALSE, File, &FileBuffer, &FileSize, NULL, NULL, NULL);
    TRACE((TRACE_ALWAYS,"File read(1)...%r\n", Status));
    if(EFI_ERROR(Status)) {
        Status = ReadImage(TRUE, File, &FileBuffer, &FileSize, NULL, NULL, NULL);
        TRACE((TRACE_ALWAYS,"File read(2)...%r\n", Status));
        if(EFI_ERROR(Status))
            return EFI_ACCESS_DENIED;
    }

    bFileRead = TRUE;
  }
  //
  // Read the Dos header.
  //
  ASSERT (FileBuffer != NULL);
  if (FileBuffer == NULL) {
    return EFI_INVALID_PARAMETER;
  }
  mImageBase  = (UINT8 *) FileBuffer;
  mImageSize  = FileSize;

  ZeroMem (&ImageContext, sizeof (ImageContext));
  ImageContext.Handle    = (VOID *) FileBuffer;
  ImageContext.ImageRead = (EFI_PEI_PE_COFF_LOADER_READ_FILE) DxeImageVerificationLibImageRead;

  //
  // Get information about the image being loaded
  //
  if (EFI_ERROR (PeCoffLoaderGetImageInfo (NULL, &ImageContext)) ||
      ( mImageSize< sizeof(EFI_IMAGE_DOS_HEADER)) ) {
    //
    // The information can't be gotten from the invalid PeImage
    //
    TRACE((TRACE_ALWAYS,"PeCoffLoaderGetImageInfo Error\n"));
    goto Done;
  }

  DosHdr = (EFI_IMAGE_DOS_HEADER *) mImageBase;
  if (DosHdr->e_magic == EFI_IMAGE_DOS_SIGNATURE) {
    //
    // DOS image header is present,
    // so read the PE header after the DOS image header.
    //
    mPeCoffHeaderOffset = DosHdr->e_lfanew;
  } else {
    mPeCoffHeaderOffset = 0;
  }
  // Security review EIP[104046]: 3.HashPeImage does not validate minimum image size
  // Validate mPeCoffHeaderOffset is within the Image size range
  if(((UINT64)mPeCoffHeaderOffset+sizeof(EFI_IMAGE_NT_HEADERS32)) > mImageSize)  {
    TRACE((TRACE_ALWAYS,"EFI_IMAGE_NT_SIGNATURE Error\n"));
    goto Done;
  }

  //
  // Check PE/COFF image.
  //
  mNtHeader.Pe32 = (EFI_IMAGE_NT_HEADERS32 *) (mImageBase + mPeCoffHeaderOffset);
  if (mNtHeader.Pe32->Signature != EFI_IMAGE_NT_SIGNATURE) {
    //
    // It is not a valid Pe/Coff file.
    //
    TRACE((TRACE_ALWAYS,"EFI_IMAGE_NT_SIGNATURE Error\n"));
    goto Done;
  }

  if (mNtHeader.Pe32->FileHeader.Machine == EFI_IMAGE_MACHINE_IA64 && mNtHeader.Pe32->OptionalHeader.Magic == EFI_IMAGE_NT_OPTIONAL_HDR32_MAGIC) {
    //
    // NOTE: Some versions of Linux ELILO for Itanium have an incorrect magic value 
    //       in the PE/COFF Header. If the MachineType is Itanium(IA64) and the 
    //       Magic value in the OptionalHeader is EFI_IMAGE_NT_OPTIONAL_HDR32_MAGIC
    //       then override the magic value to EFI_IMAGE_NT_OPTIONAL_HDR64_MAGIC
    //
    Magic = EFI_IMAGE_NT_OPTIONAL_HDR64_MAGIC;
  } else {
    //
    // Get the magic value from the PE/COFF Optional Header
    //
    Magic = mNtHeader.Pe32->OptionalHeader.Magic;
  }
  
  if (Magic == EFI_IMAGE_NT_OPTIONAL_HDR32_MAGIC) {
    //
    // Use PE32 offset.
    //
    NumberOfRvaAndSizes = mNtHeader.Pe32->OptionalHeader.NumberOfRvaAndSizes;
    if (NumberOfRvaAndSizes > EFI_IMAGE_DIRECTORY_ENTRY_SECURITY) {
      SecDataDir = (EFI_IMAGE_DATA_DIRECTORY *) &mNtHeader.Pe32->OptionalHeader.DataDirectory[EFI_IMAGE_DIRECTORY_ENTRY_SECURITY];
    }        
  } else {
    //
    // Use PE32+ offset.
    //
    NumberOfRvaAndSizes = mNtHeader.Pe32Plus->OptionalHeader.NumberOfRvaAndSizes;
    if (NumberOfRvaAndSizes > EFI_IMAGE_DIRECTORY_ENTRY_SECURITY) {
      SecDataDir = (EFI_IMAGE_DATA_DIRECTORY *) &mNtHeader.Pe32Plus->OptionalHeader.DataDirectory[EFI_IMAGE_DIRECTORY_ENTRY_SECURITY];
    }
  }

  TRACE((TRACE_ALWAYS,"mImageSize %x\n", mImageSize));

  //
  // Start Image Validation.
  //
  if (SecDataDir && SecDataDir->Size) {
  //  
  // Image is possibly signed
  //
    TRACE((TRACE_ALWAYS,"SecDataDir->VirtualAddress %x\nSecDataDir->Size = %x\nIMAGE is Signed\n",
          SecDataDir->VirtualAddress, SecDataDir->Size));
  // Security review EIP[104046]: 2.Multiple integer underflows calculating size of certificate data in PE file
    if(((UINT64)SecDataDir->VirtualAddress+SecDataDir->Size) > mImageSize)
        goto Done;

  //
  // Verify the signature of the image, multiple signatures are allowed as per PE/COFF Section 4.7 
  // "Attribute Certificate Table".
  // The first certificate starts at offset (SecDataDir->VirtualAddress) from the start of the file.
  //
    Action = EFI_IMAGE_EXECUTION_AUTH_SIG_FAILED;
    for (OffSet = SecDataDir->VirtualAddress;
         OffSet < (SecDataDir->VirtualAddress + SecDataDir->Size);
//         OffSet += WinCertificate->dwLength, OffSet += ALIGN_SIZE (OffSet)) {
         OffSet +=(WinCertificate->dwLength + ALIGN_SIZE (WinCertificate->dwLength))) {
    
        WinCertificate = (WIN_CERTIFICATE *) (mImageBase + OffSet);
        TRACE((TRACE_ALWAYS,"\nOffSet = %x, WinCertificate->dwLength %x\n\n", OffSet, WinCertificate->dwLength));
        if ((SecDataDir->VirtualAddress + SecDataDir->Size - OffSet) <= sizeof (WIN_CERTIFICATE) ||
            (SecDataDir->VirtualAddress + SecDataDir->Size - OffSet) < WinCertificate->dwLength) {
          break;
        }
        //
        // Verify the image's Authenticode signature, only DER-encoded PKCS#7 signed data is supported.
        //
        //
        // Verify signature of executables.
        //

        if (WinCertificate->wCertificateType == WIN_CERT_TYPE_PKCS_SIGNED_DATA) {
          //
          // The certificate is formatted as WIN_CERTIFICATE_EFI_PKCS which is described in the 
          // Authenticode specification.
          //
          PkcsCertData = (WIN_CERTIFICATE_EFI_PKCS *) WinCertificate;
          if (PkcsCertData->Hdr.dwLength <= sizeof (PkcsCertData->Hdr)) {
            break;
          }
          AuthData   = PkcsCertData->CertData;
          AuthDataSize = PkcsCertData->Hdr.dwLength - sizeof(PkcsCertData->Hdr);

        } else if (WinCertificate->wCertificateType == WIN_CERT_TYPE_EFI_GUID) {
          //
          // The certificate is formatted as WIN_CERTIFICATE_UEFI_GUID which is described in UEFI Spec.
          //
          WinCertUefiGuid = (WIN_CERTIFICATE_UEFI_GUID *) WinCertificate;
          if (WinCertUefiGuid->Hdr.dwLength <= OFFSET_OF(WIN_CERTIFICATE_UEFI_GUID, CertData)) {
            break;
          }
          if (guidcmp (&WinCertUefiGuid->CertType, &gEfiCertTypePkcs7Guid)) {
            continue;
          }
          AuthData = WinCertUefiGuid->CertData;
          AuthDataSize = WinCertUefiGuid->Hdr.dwLength - OFFSET_OF(WIN_CERTIFICATE_UEFI_GUID, CertData);

        } else {
          if (WinCertificate->dwLength < sizeof (WIN_CERTIFICATE)) {
            break;
          }
          continue;
        }
        //
        // Verify Pkcs signed data type.
        //
        // At least 1 Cert from Pe Image should be in DB
        // None of Certs should be found in DBX 
        //
        // get Digest Algorithm, set mCertType
        // lock mutex, preserve Pkcs7 context
        Status = HashPeImageByType (AuthData, AuthDataSize);
        if (EFI_ERROR (Status)) {
            continue;
        }

        //
        // Check the digital signature against the revoked certificate in forbidden database (dbx).
        //
        if (IsPkcsSignedDataVerifiedBySignatureList (AuthData, AuthDataSize, EFI_IMAGE_SECURITY_DATABASE1, Pkcs7CertGetMatchInCertChain)) {

            Action = EFI_IMAGE_EXECUTION_AUTH_SIG_FOUND;
            VerifyStatus = EFI_ACCESS_DENIED;
            break;
        } 
        //
        // Check the digital signature against the valid certificate in allowed database (db).
        //
        if (EFI_ERROR (VerifyStatus)) {
            if(IsPkcsSignedDataVerifiedBySignatureList (AuthData, AuthDataSize, EFI_IMAGE_SECURITY_DATABASE, Pkcs7CertValidate)) {

                VerifyStatus = EFI_SUCCESS;
            }
        }
        // clear context
        Status = mDigitalSigProtocol->Pkcs7Verify (
             mDigitalSigProtocol,
             AuthData, AuthDataSize,
             NULL, 0,
             NULL, NULL,
             Pkcs7Arg0,             // Dummy op
             RESET                  // Flags 
             );

    } // end multi-sig for
        
//    if (OffSet != (SecDataDir->VirtualAddress + SecDataDir->Size + ALIGN_SIZE(SecDataDir->Size))) {
    if(Action != EFI_IMAGE_EXECUTION_AUTH_SIG_FOUND) {
        if (OffSet != (SecDataDir->VirtualAddress + SecDataDir->Size)) {
            TRACE((TRACE_ALWAYS,"Offset outside of CertDir boundary %X != %x\n", OffSet, SecDataDir->VirtualAddress + SecDataDir->Size));
            //
            // The Size in Certificate Table or the attribute certificate table is corrupted.
            //
            VerifyStatus = EFI_ACCESS_DENIED;
        } else 
            Action = EFI_IMAGE_EXECUTION_AUTH_SIG_NOT_FOUND;
    }

  } // end Signed cert branch

  // Image not Signed or 
  // Image is Signed, its Cert verified in db but not found in DBX
  if(mCertType != &gEfiCertSha256Guid && 
        Action != EFI_IMAGE_EXECUTION_AUTH_SIG_FOUND) {

    //
    // This image is not signed or signed but found only in db or failed previous checks. 
    // Expected:
    // The SHA256 hash value of the image must match a record in the security database "db", 
    // and not be reflected in the security data base "dbx".
    //
    TRACE((TRACE_ALWAYS,"IMAGE not Signed\n\tor signed with non-Sha256, Try Sha256 Hash Cert...\n"));

    if(!HashPeImage (HASHALG_SHA256))   // init Hash type and calculate PE hash if not done already
      goto Done;

    if(IsSignatureFoundInDatabase (EFI_IMAGE_SECURITY_DATABASE1, &gEfiCertSha256Guid, mImageDigest, mImageDigestSize)) {
        //
        // Image Hash in forbidden database (DBX)
        //
        VerifyStatus = EFI_ACCESS_DENIED;
        Action = EFI_IMAGE_EXECUTION_AUTH_SIG_FOUND;
    } else
        // no - try in allowed db if not there already
        if(EFI_ERROR (VerifyStatus) && 
            IsSignatureFoundInDatabase (EFI_IMAGE_SECURITY_DATABASE, &gEfiCertSha256Guid, mImageDigest, mImageDigestSize)) {
            //
            // Image Hash is in allowed database (DB).
            //
            VerifyStatus = EFI_SUCCESS;
        }
  } 
  //
  // Signature database check after verification.
  //
  if(!EFI_ERROR (VerifyStatus) ) {
    //
    // Executable signature is found in authorized signature database.
    //
      Status = EFI_SUCCESS;
  } else {
      Status = EFI_ACCESS_DENIED;

      if(Action == EFI_IMAGE_EXECUTION_AUTH_SIG_FOUND) {
        //
        // Executable signature is found in forbidden signature database.
        //
        TRACE((TRACE_ALWAYS,"Certificate IS FOUND in Forbidden database!\n"));
      } else 
        //
        // Verification failure.
        //
        if(Action == EFI_IMAGE_EXECUTION_AUTH_SIG_NOT_FOUND) {
        //
        // Executable signature cannot be found in authorized signature database.
        // Use platform policy to determine the action.
        //
            TRACE((TRACE_ALWAYS,"Certificate NOT FOUND in authorized database!\n"));
        } 
        else 
            TRACE((TRACE_ALWAYS,"Image Certificate is Invalid!\n"));

        TRACE((TRACE_ALWAYS,"%r Record added to Image Execution Table\n", Status));

        if(!mCertType || !mImageDigestSize ) {
            goto Done;
        }
        SignatureListSize = sizeof (EFI_SIGNATURE_LIST) + sizeof (EFI_SIGNATURE_DATA) - 1 + mImageDigestSize;
        
        // Security review EIP[104046]:7. Unchecked AllocatePool may result in NULL pointer dereference
        if (!EFI_ERROR(pBS->AllocatePool(EfiBootServicesData, SignatureListSize, &SignatureList))) 
        {  
          MemSet(SignatureList, SignatureListSize, 0);
          SignatureList->SignatureHeaderSize  = 0;
          SignatureList->SignatureListSize    = (UINT32) SignatureListSize;
          SignatureList->SignatureSize        = (UINT32) mImageDigestSize;
          CopyMem (&SignatureList->SignatureType, mCertType, sizeof (EFI_GUID));
          Signature = (EFI_SIGNATURE_DATA *) ((UINT8 *) SignatureList + sizeof (EFI_SIGNATURE_LIST));
          CopyMem (Signature->SignatureData, mImageDigest, mImageDigestSize);
        }
        if (SignatureList != NULL) {
            pBS->FreePool (SignatureList);
        }
    }
Done:
  if (Status != EFI_SUCCESS) {
    //
    // Policy decides to defer or reject the image; add its information in image executable information table.
    //
    AddImageExeInfo (Action, NULL, File, SignatureList, SignatureListSize);
    // Treat unsecured images according to Image Authorization policy
    Status = ImageAuthorization (Policy, Action);
  }
  if(bFileRead)
      pBS->FreePool (FileBuffer);
    
TRACE((TRACE_ALWAYS,"Image Verification ...%r\n", Status));
  return Status;
}

//===================== Security Architectural Protocol ======================
#ifndef EFI_SECURITY2_ARCH_PROTOCOL_GUID
#define EFI_SECURITY2_ARCH_PROTOCOL_GUID  \
  { 0x94ab2f58, 0x1438, 0x4ef1, 0x91, 0x52, 0x18, 0x94, 0x1a, 0x3a, 0xe, 0x68 }

typedef struct _EFI_SECURITY2_ARCH_PROTOCOL EFI_SECURITY2_ARCH_PROTOCOL;

typedef EFI_STATUS (EFIAPI *EFI_SECURITY2_FILE_AUTHENTICATION) (
    IN CONST EFI_SECURITY2_ARCH_PROTOCOL *This,
    IN CONST EFI_DEVICE_PATH_PROTOCOL *File,
    IN VOID *FileBuffer,
    IN UINTN FileSize,
    IN BOOLEAN BootPolicy
);

struct _EFI_SECURITY2_ARCH_PROTOCOL {
    EFI_SECURITY2_FILE_AUTHENTICATION FileAuthentication;
};

static EFI_GUID gEfiSecurity2ArchProtocolGuid = EFI_SECURITY2_ARCH_PROTOCOL_GUID;
#endif

EFI_STATUS SecureFileAuthentication2(
    IN CONST EFI_SECURITY2_ARCH_PROTOCOL *This,
    IN CONST EFI_DEVICE_PATH_PROTOCOL *File,
    IN VOID *FileBuffer,
    IN UINTN FileSize,
    IN BOOLEAN BootPolicy
    )
{
    EFI_STATUS Status;

    TRACE((TRACE_ALWAYS,"...............Call Security2 Arch proto.. File=%x, FileBuffer=%x, FileSize=%d\n",File,FileBuffer,FileSize ));

    //
    // skip verification if platform is NOT in SECURE BOOT MODE 
    //
    if(mSecureBootEnable == 0)
        return  EFI_SUCCESS;

    //
    // Protocol should have been installed by AmiDigitalSig Driver once it's dispatched 
    //
    if( mDigitalSigProtocol == NULL )
        return EFI_ACCESS_DENIED;

    Status = DxeImageVerificationHandler(File, FileBuffer, FileSize, BootPolicy);
    // Install Tbl only on the Boot Loader launch
    if (!EFI_ERROR (Status)/* && BootPolicy*/) {
        AddBootImageCertInfo(NULL, mTrustSigDbOffs, mTrustSigDbSize);
        mTrustSigDbOffs = 0;
        mTrustSigDbSize = 0;
    }
    TRACE((TRACE_ALWAYS,"...............return status %r\n",Status));
    return Status; 
}

EFI_STATUS SecureFileAuthentication(
    IN EFI_SECURITY_ARCH_PROTOCOL *This,
    IN UINT32 AuthenticationStatus,
    IN EFI_DEVICE_PATH_PROTOCOL *File
    )
{
    BOOLEAN BootPolicy;
    VOID    *FileBuffer;
    UINTN   FileSize;

    BootPolicy  = TRUE;
    FileBuffer  = NULL;
    FileSize    = 0;

    TRACE((TRACE_ALWAYS,".........Call Security Arch proto.. File=%x\n",File));

    if (File == NULL) 
        return EFI_INVALID_PARAMETER;

  //Security Protocol w/a: BootPolicy == 1 if File->Type == 4 Media Dev Path
//    if(File->Type == 4) // Media Dev Path
//        BootPolicy=TRUE;

    return SecureFileAuthentication2(NULL, File, FileBuffer, FileSize, BootPolicy);
}

EFI_SECURITY2_ARCH_PROTOCOL mSecurity2 = {SecureFileAuthentication2};
EFI_SECURITY_ARCH_PROTOCOL mSecurity = {SecureFileAuthentication};

//----------------------------------------------------------------------------
//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   InitDigitalProtocolCallback
//
// Description: This function initialize mDigitalSigProtocol ptr
//              
//
//  Input:      IN EFI_EVENT Event - Event that was triggered
//              IN VOID *Context - data pointer to information that is defined 
//              when the event is registered
//
// Output:      EFI_STATUS
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
static EFI_STATUS  InitDigitalProtocolCallback(IN EFI_EVENT Event, IN VOID *Context)
{
    EFI_STATUS Status;
    UINTN      DataSize;
    UINT8      *pSecureBootEnable=NULL;
    //
    // Look up for image authorization policy in "SetupData" variable
    //
#if (defined(ENABLE_IMAGE_EXEC_POLICY_OVERRIDE) && ENABLE_IMAGE_EXEC_POLICY_OVERRIDE == 1)
    DataSize = sizeof(mSecureBootSetup);
    Status = pRS->GetVariable (AMI_SECURE_BOOT_SETUP_VAR,&gSecureSetupGuid,NULL,&DataSize,&mSecureBootSetup);
    if(EFI_ERROR(Status) ||
       // Standard boot mode policy->apply defaults
       mSecureBootSetup.SecureBootMode == STANDARD_SECURE_BOOT || 
       // Policy check against fixed settings
       mSecureBootSetup.Load_from_OROM < LOAD_FROM_OROM ||
       mSecureBootSetup.Load_from_REMOVABLE_MEDIA < LOAD_FROM_REMOVABLE_MEDIA ||
       mSecureBootSetup.Load_from_FIXED_MEDIA < LOAD_FROM_FIXED_MEDIA
    )
#endif
    { 
        mSecureBootSetup.Load_from_OROM = LOAD_FROM_OROM;
        mSecureBootSetup.Load_from_REMOVABLE_MEDIA = LOAD_FROM_REMOVABLE_MEDIA;
        mSecureBootSetup.Load_from_FIXED_MEDIA = LOAD_FROM_FIXED_MEDIA;
    }
    //
    // SecureBoot variable to be installed along with NVRAM driver
    //
    pSecureBootEnable = GetEfiGlobalVariableEx (EFI_SECURE_BOOT_NAME, &DataSize);
    if(pSecureBootEnable && DataSize==1) 
        mSecureBootEnable = *pSecureBootEnable;
    //
    // will skip verification if platform is NOT in SECURE BOOT MODE 
    //
    if(mSecureBootEnable == 0)
        return EFI_SUCCESS;

    Status = pBS->LocateHandleBuffer (
                       ByProtocol,
     #if (PI_SPECIFICATION_VERSION < 0x00010000)
                       &gEfiFirmwareVolumeProtocolGuid,
     #else
                       &gEfiFirmwareVolume2ProtocolGuid,
     #endif
                       NULL,
                       &mFvHandlesCount,
                       &mFvHandles
                       );
    if(!EFI_ERROR(Status)){
      gImageLoadingAfterBDS = TRUE;
    }

    return  pBS->LocateProtocol( &gAmiDigitalSignatureProtocolGuid, NULL, &mDigitalSigProtocol );
}

extern BOOLEAN const InstallDummySecurityProtocol;
//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   InstallSecurityArchProtocol
//
// Description: This function installs the EFI_SECURITY_ARCH_PROTOCOL.
//              It is called at DxeCoreInitialize.
//
// Input:
//  EFI_HANDLE          ImageHandle     Image handle.
//  EFI_SYSTEM_TABLE    *SystemTable    Pointer to the EFI system table.
//
// Output:
//  EFI_SUCCESS : Security Architecture protocols are successfully installed.
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID InstallSecurityArchProtocol( 
    IN  EFI_HANDLE              ImageHandle,
    IN  EFI_SYSTEM_TABLE        *SystemTable
)
{
    EFI_HANDLE Handle = NULL;
    EFI_EVENT  Event;
    VOID       *p;

    if (InstallDummySecurityProtocol)
        return; 

    // Enable Security verification at beginning of BDS connect controller phase, 
    // We assume all drivers before the event were launched from internal FV
    // !!! This bds event is only available since core 4.6.3.5.
    RegisterProtocolCallback(
        &BdsConnectDriversProtocolGuid,
        InitDigitalProtocolCallback,
        NULL,
        &Event,
        &p
    );
   // Security2 Arch protocol must be installed before Security Arch protocol
    pBS->InstallMultipleProtocolInterfaces(
        &Handle, 
        &gEfiSecurity2ArchProtocolGuid, &mSecurity2, 
        &gEfiSecurityArchProtocolGuid, &mSecurity,
        NULL
    );
}

#pragma warning (default : 4090)
//**********************************************************************
//**********************************************************************
//**                                                                  **
//**        (C)Copyright 1985-2011, American Megatrends, Inc.         **
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
