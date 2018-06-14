/** @file
  This file is SampleCode for Boot Guard TPM event log.

@copyright
  Copyright (c) 2013 Intel Corporation. All rights reserved
  This software and associated documentation (if any) is furnished
  under a license and may only be used or copied in accordance
  with the terms of the license. Except as permitted by such
  license, no part of this software or documentation may be
  reproduced, stored in a retrieval system, or transmitted in any
  form or by any means without the express written consent of
  Intel Corporation.
  This file contains a 'Sample Driver' and is licensed as such
  under the terms of your license agreement with Intel or your
  vendor.  This file may be modified by the user, subject to
  the additional terms of the license agreement
**/

#if !defined(EDK_RELEASE_VERSION) || (EDK_RELEASE_VERSION < 0x00020000)
#include "EdkIIGlueBase.h"
#include "EdkIIGluePeim.h"
#include "CpuAccess.h"
#endif

#include <EfiTpm.h>
#include "BootGuardTpmEventLogLib.h"

//
// Data structure definition
//
#pragma pack (1)

#define  BASE_4GB  0x0000000100000000ULL
//
// FIT definition
//
#define FIT_TABLE_TYPE_HEADER                0x0
#define FIT_TABLE_TYPE_MICROCODE             0x1
#define FIT_TABLE_TYPE_STARTUP_ACM           0x2
#define FIT_TABLE_TYPE_BIOS_MODULE           0x7
#define FIT_TABLE_TYPE_KEY_MANIFEST          0xB
#define FIT_TABLE_TYPE_BOOT_POLICY_MANIFEST  0xC

typedef struct {
  UINT64 Address;
  UINT8  Size[3];
  UINT8  Reserved;
  UINT16 Version;
  UINT8  Type : 7;
  UINT8  Cv   : 1;
  UINT8  Chksum;
} FIRMWARE_INTERFACE_TABLE_ENTRY;

//
// ACM definition
//
#define MMIO_ACM_STATUS  (TXT_PUBLIC_BASE + R_CPU_BOOT_GUARD_ACM_STATUS)
#define ACM_KEY_HASH_MMIO_ADDR_0  0xFED30400
#define ACM_KEY_HASH_MMIO_ADDR_1  (ACM_KEY_HASH_MMIO_ADDR_0 + 8)
#define ACM_KEY_HASH_MMIO_ADDR_2  (ACM_KEY_HASH_MMIO_ADDR_0 + 16)
#define ACM_KEY_HASH_MMIO_ADDR_3  (ACM_KEY_HASH_MMIO_ADDR_0 + 24)
#define ACM_PKCS_1_5_RSA_SIGNATURE_SIZE  256
#define ACM_HEADER_FLAG_DEBUG_SIGNED     BIT15
#define ACM_NPW_SVN                      0x2

typedef struct {
  UINT32 ModuleType;
  UINT32 HeaderLen;
  UINT32 HeaderVersion;
  UINT16 ChipsetId;
  UINT16 Flags;
  UINT32 ModuleVendor;
  UINT32 Date;
  UINT32 Size;
  UINT16 AcmSvn;
  UINT16 Reserved1;
  UINT32 CodeControl;
  UINT32 ErrorEntryPoint;
  UINT32 GdtLimit;
  UINT32 GdtBasePtr;
  UINT32 SegSel;
  UINT32 EntryPoint;
  UINT8  Reserved2[64];
  UINT32 KeySize;
  UINT32 ScratchSize;
  UINT8  RsaPubKey[64 * 4];
  UINT32 RsaPubExp;
  UINT8  RsaSig[256];
} ACM_FORMAT;

//
// Manifest definition
//
#define SHA256_DIGEST_SIZE  32

typedef struct {
  UINT16 HashAlg;
  UINT16 Size;
  UINT8  HashBuffer[SHA256_DIGEST_SIZE];
} HASH_STRUCTURE;

#define RSA_PUBLIC_KEY_STRUCT_KEY_SIZE_DEFAULT  2048
#define RSA_PUBLIC_KEY_STRUCT_KEY_LEN_DEFAULT   (RSA_PUBLIC_KEY_STRUCT_KEY_SIZE_DEFAULT/8)

typedef struct {
  UINT8  Version;
  UINT16 KeySize;
  UINT32 Exponent;
  UINT8  Modulus[RSA_PUBLIC_KEY_STRUCT_KEY_LEN_DEFAULT];
} RSA_PUBLIC_KEY_STRUCT;

#define RSASSA_SIGNATURE_STRUCT_KEY_SIZE_DEFAULT  2048
#define RSASSA_SIGNATURE_STRUCT_KEY_LEN_DEFAULT   (RSASSA_SIGNATURE_STRUCT_KEY_SIZE_DEFAULT/8)
typedef struct {
  UINT8  Version;
  UINT16 KeySize;
  UINT16 HashAlg;
  UINT8  Signature[RSASSA_SIGNATURE_STRUCT_KEY_LEN_DEFAULT];
} RSASSA_SIGNATURE_STRUCT;

typedef struct {
  UINT8                   Version;
  UINT16                  KeyAlg;
  RSA_PUBLIC_KEY_STRUCT   Key;
  UINT16                  SigScheme;
  RSASSA_SIGNATURE_STRUCT Signature;
} KEY_SIGNATURE_STRUCT;

#define BOOT_POLICY_MANIFEST_HEADER_STRUCTURE_ID  (*(UINT64 *)"__ACBP__")
typedef struct {
  UINT8  StructureId[8];
  UINT8  StructVersion;
  UINT8  HdrStructVersion;
  UINT8  PMBPMVersion;
  UINT8  BPSVN;
  UINT8  ACMSVN;
  UINT8  Reserved;
  UINT16 NEMDataStack;
} BOOT_POLICY_MANIFEST_HEADER;

#define IBB_SEGMENT_FLAG_IBB      0x0
#define IBB_SEGMENT_FLAG_NON_IBB  0x1
typedef struct {
  UINT8  Reserved[2];
  UINT16 Flags;
  UINT32 Base;
  UINT32 Size;
} IBB_SEGMENT_ELEMENT;

#define BOOT_POLICY_MANIFEST_IBB_ELEMENT_STRUCTURE_ID  (*(UINT64 *)"__IBBS__")
#define IBB_FLAG_AUTHORITY_MEASURE                     0x4

typedef struct {
  UINT8               StructureId[8];
  UINT8               StructVersion;
  UINT8               Reserved1[2];
  UINT8               PbetValue;
  UINT32              Flags;
  UINT64              IbbMchBar;
  UINT64              VtdBar;
  UINT32              PmrlBase;
  UINT32              PmrlLimit;
  UINT64              Reserved2[2];
  HASH_STRUCTURE      PostIbbHash;
  UINT32              EntryPoint;
  HASH_STRUCTURE      Digest;
  UINT8               SegmentCount;
  IBB_SEGMENT_ELEMENT IbbSegment[1];
} IBB_ELEMENT;

#define BOOT_POLICY_MANIFEST_PLATFORM_MANUFACTURER_ELEMENT_STRUCTURE_ID  (*(UINT64 *)"__PMDA__")
typedef struct {
  UINT8  StructureId[8];
  UINT8  StructVersion;
  UINT16 PmDataSize;
} PLATFORM_MANUFACTURER_ELEMENT;

#define BOOT_POLICY_MANIFEST_SIGNATURE_ELEMENT_STRUCTURE_ID  (*(UINT64 *)"__PMSG__")
typedef struct {
  UINT8                StructureId[8];
  UINT8                StructVersion;
  KEY_SIGNATURE_STRUCT KeySignature;
} BOOT_POLICY_MANIFEST_SIGNATURE_ELEMENT;

#define KEY_MANIFEST_STRUCTURE_ID  (*(UINT64 *)"__KEYM__")
typedef struct {
  UINT8                StructureId[8];
  UINT8                StructVersion;
  UINT8                KeyManifestVersion;
  UINT8                KmSvn;
  UINT8                KeyManifestId;
  HASH_STRUCTURE       BpKey;
  KEY_SIGNATURE_STRUCT KeyManifestSignature;
} KEY_MANIFEST_STRAUCTURE;

//
// DetailPCR data
//
typedef struct {
  UINT8  BpRstrLow;
  UINT8  BpTypeLow;
  UINT16 AcmSvn;
  UINT8  AcmRsaSignature[ACM_PKCS_1_5_RSA_SIGNATURE_SIZE];
  UINT8  KmRsaSignature[RSASSA_SIGNATURE_STRUCT_KEY_LEN_DEFAULT];
  UINT8  BpmRsaSignature[RSASSA_SIGNATURE_STRUCT_KEY_LEN_DEFAULT];
  UINT8  IbbHash[SHA256_DIGEST_SIZE];
} DETAIL_PCR_DATA;

//
// AuthorityPCR data
//
typedef struct {
  UINT8  BpRstrLow;
  UINT8  BpTypeLow;
  UINT16 AcmSvn;
  UINT8  AcmKeyHash[SHA256_DIGEST_SIZE];
  UINT8  BpKeyHash[SHA256_DIGEST_SIZE];
  UINT8  BpmKeyHashFromKm[SHA256_DIGEST_SIZE];
  UINT8  VerifiedBoot;
} AUTHORITY_PCR_DATA;

//
// Boot Policy Restrictions definition
//
typedef union {
  struct {
    UINT8 Facb     : 1;
    UINT8 Dcd      : 1;
    UINT8 Dbi      : 1;
    UINT8 Pbe      : 1;
    UINT8 Bbp      : 1;
    UINT8 Reserved : 2;
    UINT8 BpInvd   : 1;
  } Bits;
  UINT8 Data;
} BP_RSTR_LOW;

//
// Boot Policy Type definition
//
typedef union {
  struct {
    UINT8 MeasuredBoot : 1;
    UINT8 VerifiedBoot : 1;
    UINT8 Hap          : 1;
    UINT8 Reserved     : 5;
  } Bits;
  UINT8    Data;
} BP_TYPE_LOW;

#pragma pack ()

//
// OEM_IMPLEMENTATION_BEGIN
//
// SHA calculation and TPM functions are OEM Core/Platform code depended,
// OEM can customize these empty functions for their specific.
//
// For the detail of SHA algorithm, please refer to FIPS PUB 180-2.
// For TPM event log, please refer to TCG EFI Protocol Specification.
//

//
// Null-defined macro for passing EDK build
//
#define SHA_INIT
#define SHA_UPDATE
#define SHA_FINAL

/**
  Calculate SHA-1 Hash

  @param[in]  Data    Data to be hashed.
  @param[in]  Size    Size of data.
  @param[out] Digest  SHA-1 digest value.
**/
VOID
CreateSha1Hash (
  IN UINT8  *Data,
  IN UINTN  Size,
  OUT UINT8 *Digest
  )
{
  VOID *Context;

  SHA_INIT (Context);
  SHA_UPDATE (Context, Data, Size);
  SHA_FINAL (Context, Digest);

  return;
}

/**
  Calculate SHA256 Hash

  @param[in]  Data    Data to be hashed.
  @param[in]  Size    Size of data.
  @param[out] Digest  SHA256 digest value.
**/
VOID
CreateSha256Hash (
  IN UINT8  *Data,
  IN UINTN  Size,
  OUT UINT8 *Digest
  )
{
  VOID *Context;

  SHA_INIT (Context);
  SHA_UPDATE (Context, Data, Size);
  SHA_FINAL (Context, Digest);

  return;
}

/**
  Add a new entry to the Event Log.

  @param[in] NewEventHdr   Pointer to a TCG_PCR_EVENT_HDR data structure.
  @param[in] NewEventData  Pointer to the new event data.

  @retval EFI_SUCCESS           The new event log entry was added.
  @retval EFI_OUT_OF_RESOURCES  No enough memory to log the new event.
**/
EFI_STATUS
LogEvent (
  IN TCG_PCR_EVENT_HDR *NewEventHdr,
  IN UINT8             *NewEventData
  )
{

  return EFI_SUCCESS;
}
//
// OEM_IMPLEMENTATION_END
//

/**
  Find FIT Entry address data by type

  @param[in] Type  FIT Entry type

  @return  FIT entry address
**/
VOID *
FindFitEntryData (
  IN UINT8 Type
  )
{
  FIRMWARE_INTERFACE_TABLE_ENTRY *FitEntry;
  UINT32                         EntryNum;
  UINT64                         FitTableOffset;
  UINT32                         Index;

  FitTableOffset = *(UINT64 *)(UINTN)(BASE_4GB - 0x40);
  FitEntry = (FIRMWARE_INTERFACE_TABLE_ENTRY *)(UINTN)FitTableOffset;
  if (FitEntry[0].Address != *(UINT64 *)"_FIT_   ") {
    return NULL;
  }
  if (FitEntry[0].Type != FIT_TABLE_TYPE_HEADER) {
    return NULL;
  }
  EntryNum = *(UINT32 *)(&FitEntry[0].Size[0]) & 0xFFFFFF;
  for (Index = 0; Index < EntryNum; Index++) {
    if (FitEntry[Index].Type == Type) {
      return (VOID *)(UINTN)FitEntry[Index].Address;
    }
  }

  return NULL;
}

/**
  Find the address of ACM.

  @return  A pointer to ACM.
**/
VOID *
FindAcm (
  VOID
  )
{
  return FindFitEntryData (FIT_TABLE_TYPE_STARTUP_ACM);
}

/**
  Find the address of Boot Policy Manifest.

  @return  A pointer to Key Manifest data structure.
**/
VOID *
FindBpm (
  VOID
  )
{
  return FindFitEntryData (FIT_TABLE_TYPE_BOOT_POLICY_MANIFEST);
}

/**
  Find the address of Key Manifest.

  @return  A pointer to Key Manifest data structure.
**/
VOID *
FindKm (
  VOID
  )
{
  return FindFitEntryData (FIT_TABLE_TYPE_KEY_MANIFEST);
}

/**
  Find BPM element by structureID

  @param[in] Bpm          A pointer to BPM data structure.
  @param[in] StructureId  BPM element StructureID

  @return  A pointer to BPM element data structure.
**/
VOID *
FindBpmElement (
  IN BOOT_POLICY_MANIFEST_HEADER *Bpm,
  IN UINT64                      StructureId
  )
{
  BOOT_POLICY_MANIFEST_HEADER            *BpmHeader;
  IBB_ELEMENT                            *IbbElement;
  PLATFORM_MANUFACTURER_ELEMENT          *PmElement;
  BOOT_POLICY_MANIFEST_SIGNATURE_ELEMENT *BpmSignatureElement;
  UINT8                                  *Buffer;

  Buffer = (UINT8 *)Bpm;

  BpmHeader = (BOOT_POLICY_MANIFEST_HEADER *)Buffer;
  if (*(UINT64 *)BpmHeader->StructureId != BOOT_POLICY_MANIFEST_HEADER_STRUCTURE_ID) {
    return NULL;
  }
  if (StructureId == BOOT_POLICY_MANIFEST_HEADER_STRUCTURE_ID) {
    return Buffer;
  }
  Buffer += sizeof(BOOT_POLICY_MANIFEST_HEADER);

  IbbElement = (IBB_ELEMENT *)Buffer;
  if (*(UINT64 *)IbbElement->StructureId != BOOT_POLICY_MANIFEST_IBB_ELEMENT_STRUCTURE_ID) {
    return NULL;
  }
  if (StructureId == BOOT_POLICY_MANIFEST_IBB_ELEMENT_STRUCTURE_ID) {
    return Buffer;
  }
  Buffer += sizeof(IBB_ELEMENT) + sizeof(IBB_SEGMENT_ELEMENT) * (IbbElement->SegmentCount - 1);

  PmElement = (PLATFORM_MANUFACTURER_ELEMENT *)Buffer;
  while (*(UINT64 *)PmElement->StructureId == BOOT_POLICY_MANIFEST_PLATFORM_MANUFACTURER_ELEMENT_STRUCTURE_ID) {
    if (StructureId == BOOT_POLICY_MANIFEST_PLATFORM_MANUFACTURER_ELEMENT_STRUCTURE_ID) {
      return Buffer;
    }
    Buffer += sizeof(PLATFORM_MANUFACTURER_ELEMENT) + PmElement->PmDataSize;
    PmElement = (PLATFORM_MANUFACTURER_ELEMENT *)Buffer;
  }

  BpmSignatureElement = (BOOT_POLICY_MANIFEST_SIGNATURE_ELEMENT *)Buffer;
  if (*(UINT64 *)BpmSignatureElement->StructureId != BOOT_POLICY_MANIFEST_SIGNATURE_ELEMENT_STRUCTURE_ID) {
    return NULL;
  }
  if (StructureId == BOOT_POLICY_MANIFEST_SIGNATURE_ELEMENT_STRUCTURE_ID) {
    return Buffer;
  }
  return NULL;
}

/**
  Find BPM IBB element

  @param[in] Bpm  A pointer to BPM data structure.

  @return  A pointer to BPM IBB element data structure.
**/
VOID *
FindBpmIbb (
  IN BOOT_POLICY_MANIFEST_HEADER *Bpm
  )
{
  return FindBpmElement (Bpm, BOOT_POLICY_MANIFEST_IBB_ELEMENT_STRUCTURE_ID);
}

/**
  Find BPM Signature element

  @param[in] Bpm  BPM address

  @return BPM Signature element
**/
VOID *
FindBpmSignature (
  IN BOOT_POLICY_MANIFEST_HEADER *Bpm
  )
{
  return FindBpmElement (Bpm, BOOT_POLICY_MANIFEST_SIGNATURE_ELEMENT_STRUCTURE_ID);
}

/**
  Check if ACM is a NPW ACM.

  @retval TRUE   It is a NPW ACM
  @retval FALSE  It is NOT a NPW ACM
**/
BOOLEAN
IsNpwAcm (
  VOID
  )
{
  ACM_FORMAT *Acm;

  Acm = FindAcm ();
  ASSERT (Acm != NULL);
  if (Acm == NULL) {
    return FALSE;
  }

  if (((Acm->Flags & ACM_HEADER_FLAG_DEBUG_SIGNED) == 0) && (Acm->AcmSvn < ACM_NPW_SVN)) {
    return TRUE;
  } else {
    return FALSE;
  }
}

/**
  Check if Boot Guard verifies the IBB.

  @retval TRUE   It is VerifiedBoot
  @retval FALSE  It is NOT VerifiedBoot
**/
BOOLEAN
IsVerifiedBoot (
  VOID
  )
{
  if ((AsmReadMsr64 (MSR_BOOT_GUARD_SACM_INFO) & B_VERIFIED) != 0) {
    return TRUE;
  } else {
    return FALSE;
  }
}

/**
  Check if Boot Guard measures IBB into TPM's PCRs.

  @retval TRUE   It is MeasuredBoot
  @retval FALSE  It is NOT MeasuredBoot
**/
BOOLEAN
IsMeasuredBoot (
  VOID
  )
{
  if ((AsmReadMsr64 (MSR_BOOT_GUARD_SACM_INFO) & B_MEASURED) != 0) {
    return TRUE;
  } else {
    return FALSE;
  }
}

/**
  Get the lower 8 bits of Boot Policy Restrictions

  @return The lower 8 bits of BP.RSTR
**/
UINT8
GetBpRstrLow (
  VOID
  )
{
  BP_RSTR_LOW BpRstr;
  UINT32      AcmStatus;
  UINT64      SacmInfo;

  AcmStatus = MmioRead32 (MMIO_ACM_STATUS);
  SacmInfo  = AsmReadMsr64 (MSR_BOOT_GUARD_SACM_INFO);

  BpRstr.Bits.Facb = (UINT8)((SacmInfo  & BIT4)  >> 4);
  BpRstr.Bits.Dcd  = (UINT8)((AcmStatus & BIT21) >> 21);
  BpRstr.Bits.Dbi  = (UINT8)((AcmStatus & BIT22) >> 22);
  BpRstr.Bits.Pbe  = (UINT8)((AcmStatus & BIT23) >> 23);
  BpRstr.Bits.Bbp  = (UINT8)((AcmStatus & BIT24) >> 24);
  BpRstr.Bits.Reserved = 0;
  BpRstr.Bits.BpInvd   = 0;

  return BpRstr.Data;
}

/**
  Get the lower 8 bits of Boot Policy Type

  @return The lower 8 bits of BP.TYPE
**/
UINT8
GetBpTypeLow (
  VOID
  )
{
  BP_TYPE_LOW BpType;
  UINT32      AcmStatus;
  UINT64      SacmInfo;

  AcmStatus = MmioRead32 (MMIO_ACM_STATUS);
  SacmInfo  = AsmReadMsr64 (MSR_BOOT_GUARD_SACM_INFO);

  BpType.Bits.MeasuredBoot = (UINT8)((SacmInfo & BIT5) >> 5);
  BpType.Bits.VerifiedBoot = (UINT8)((SacmInfo & BIT6) >> 6);
  BpType.Bits.Hap      = (UINT8)((AcmStatus & BIT20) >> 20);
  BpType.Bits.Reserved = 0;

  return BpType.Data;
}

/**
  Calculate IBB Hash

  @param[in]  BpmIbb  A pointer to BPM IBB element data structure.
  @param[out] Digest  IBB digest value.
**/
VOID
CreateIbbHash (
  IN IBB_ELEMENT *BpmIbb,
  OUT UINT8      *Digest
  )
{
  VOID  *Context;
  UINTN Index;

  SHA_INIT (Context);

  for (Index = 0; Index < BpmIbb->SegmentCount; Index++) {
    if (BpmIbb->IbbSegment[Index].Flags == IBB_SEGMENT_FLAG_IBB) {
      SHA_UPDATE (Context, (VOID *)(UINTN)BpmIbb->IbbSegment[Index].Base, BpmIbb->IbbSegment[Index].Size);
    }
  }

  SHA_FINAL (Context, Digest);

  return;
}

/**
  Calculate DetailPCR extend value

  @param[out] Digest  DetailPCR digest
**/
VOID
CaculateDetailPCRExtendValue (
  OUT TCG_DIGEST *Digest
  )
{
  ACM_FORMAT                             *Acm;
  KEY_MANIFEST_STRAUCTURE                *Km;
  BOOT_POLICY_MANIFEST_HEADER            *Bpm;
  IBB_ELEMENT                            *BpmIbb;
  BOOT_POLICY_MANIFEST_SIGNATURE_ELEMENT *BpmSignature;
  DETAIL_PCR_DATA                        DetailPcrData;

  Acm = FindAcm ();
  ASSERT (Acm != NULL);

  Km = FindKm ();
  ASSERT (Km != NULL);

  Bpm = FindBpm ();
  ASSERT (Bpm != NULL);

  BpmIbb = FindBpmIbb (Bpm);
  ASSERT (BpmIbb != NULL);

  BpmSignature = FindBpmSignature (Bpm);
  ASSERT (BpmSignature != NULL);

  DetailPcrData.BpRstrLow = GetBpRstrLow ();
  DetailPcrData.BpTypeLow = GetBpTypeLow ();
  DetailPcrData.AcmSvn = Acm->AcmSvn;
  CopyMem (&DetailPcrData.AcmRsaSignature, &Acm->RsaSig, sizeof(DetailPcrData.AcmRsaSignature));
  CopyMem (&DetailPcrData.KmRsaSignature, &Km->KeyManifestSignature.Signature.Signature, sizeof(DetailPcrData.KmRsaSignature));
  CopyMem (&DetailPcrData.BpmRsaSignature, &BpmSignature->KeySignature.Signature.Signature, sizeof(DetailPcrData.BpmRsaSignature));
  if (IsVerifiedBoot ()) {
    CopyMem (&DetailPcrData.IbbHash, &BpmIbb->Digest.HashBuffer, sizeof(DetailPcrData.IbbHash));
  } else {
    //
    // Calculate IBB hash because it is NOT verified boot, the Digest from IBB can not be trust.
    //
    CreateIbbHash (BpmIbb, (UINT8 *)&DetailPcrData.IbbHash);
  }

  CreateSha1Hash ((UINT8 *)&DetailPcrData, sizeof(DetailPcrData), (UINT8 *)Digest);
}

/**
  Calculate AuthorityPCR extend value

  @param[out] Digest  AuthorityPCR digest
**/
VOID
CaculateAuthorityPCRExtendValue (
  OUT TCG_DIGEST *Digest
  )
{
  ACM_FORMAT              *Acm;
  KEY_MANIFEST_STRAUCTURE *Km;
  AUTHORITY_PCR_DATA      AuthorityPcrData;

  Acm = FindAcm ();
  ASSERT (Acm != NULL);

  Km = FindKm ();
  ASSERT (Km != NULL);

  AuthorityPcrData.BpRstrLow = GetBpRstrLow ();
  AuthorityPcrData.BpTypeLow = GetBpTypeLow ();
  AuthorityPcrData.AcmSvn = Acm->AcmSvn;

  //
  // Get ACM Key hash
  //
  *(UINT64 *)&AuthorityPcrData.AcmKeyHash[0]  = MmioRead64 (ACM_KEY_HASH_MMIO_ADDR_0);
  *(UINT64 *)&AuthorityPcrData.AcmKeyHash[8]  = MmioRead64 (ACM_KEY_HASH_MMIO_ADDR_1);
  *(UINT64 *)&AuthorityPcrData.AcmKeyHash[16] = MmioRead64 (ACM_KEY_HASH_MMIO_ADDR_2);
  *(UINT64 *)&AuthorityPcrData.AcmKeyHash[24] = MmioRead64 (ACM_KEY_HASH_MMIO_ADDR_3);

  //
  // Calculate BP Key hash
  //
  CreateSha256Hash ((UINT8 *)&Km->KeyManifestSignature.Key.Modulus, sizeof(Km->KeyManifestSignature.Key.Modulus), (UINT8 *)&AuthorityPcrData.BpKeyHash);

  CopyMem (&AuthorityPcrData.BpmKeyHashFromKm, &Km->BpKey.HashBuffer, sizeof(AuthorityPcrData.BpmKeyHashFromKm));
  if (IsVerifiedBoot ()) {
    AuthorityPcrData.VerifiedBoot = 0;
  } else {
    AuthorityPcrData.VerifiedBoot = 1;
  }

  CreateSha1Hash ((UINT8 *)&AuthorityPcrData, sizeof(AuthorityPcrData), (UINT8 *)Digest);
}

/**
  Check if we need AuthorityPCR measurement

  @retval TRUE   Need AuthorityPCR measurement
  @retval FALSE  Do NOT need AuthorityPCR measurement
**/
BOOLEAN
NeedAuthorityMeasure (
  VOID
  )
{
  BOOT_POLICY_MANIFEST_HEADER *Bpm;
  IBB_ELEMENT                 *BpmIbb;

  Bpm = FindBpm ();
  ASSERT (Bpm != NULL);

  BpmIbb = FindBpmIbb (Bpm);
  ASSERT (BpmIbb != NULL);

  if ((BpmIbb->Flags & IBB_FLAG_AUTHORITY_MEASURE) != 0) {
    return TRUE;
  } else {
    return FALSE;
  }
}

/**
  Create DetailPCR event log

  @param[in] TpmType  TPM type
**/
VOID
CreateDetailPcrEvent (
  IN TPM_TYPE TpmType
  )
{
  TCG_PCR_EVENT_HDR NewEventHdr;

  NewEventHdr.PCRIndex  = 0;
  NewEventHdr.EventType = EV_S_CRTM_CONTENTS;
  CaculateDetailPCRExtendValue (&NewEventHdr.Digest);

  if (IsNpwAcm()) {
    NewEventHdr.EventSize = sizeof ("Boot Guard Debug Measured S-CRTM");
    LogEvent (&NewEventHdr, "Boot Guard Debug Measured S-CRTM");
  } else {
    NewEventHdr.EventSize = sizeof ("Boot Guard Measured S-CRTM");
    LogEvent (&NewEventHdr, "Boot Guard Measured S-CRTM");
  }
}

/**
  Create AuthorityPCR event log

  @param[in] TpmType  TPM type
**/
VOID
CreateAuthorityPcrEvent (
  IN TPM_TYPE TpmType
  )
{
  TCG_PCR_EVENT_HDR NewEventHdr;

  if (NeedAuthorityMeasure() && IsVerifiedBoot()) {
    if (TpmType == dTpm12) {
      NewEventHdr.PCRIndex  = 6;
    } else {
      NewEventHdr.PCRIndex  = 7;
    }
    NewEventHdr.EventType = EV_EFI_VARIABLE_DRIVER_CONFIG;
    CaculateAuthorityPCRExtendValue (&NewEventHdr.Digest);

    if (IsNpwAcm()) {
      NewEventHdr.EventSize = sizeof (L"Boot Guard Debug Measured S-CRTM");
      LogEvent (&NewEventHdr, (UINT8 *)L"Boot Guard Debug Measured S-CRTM");
    } else {
      NewEventHdr.EventSize = sizeof (L"Boot Guard Measured S-CRTM");
      LogEvent (&NewEventHdr, (UINT8 *)L"Boot Guard Measured S-CRTM");
    }
  }
}

/**
  Create Boot Guard TPM event log

  @param[in] TpmType  Which type of TPM is available on system.
**/
VOID
CreateTpmEventLog (
  IN TPM_TYPE TpmType
  )
{
  if (IsMeasuredBoot()) {
    CreateDetailPcrEvent (TpmType);
    CreateAuthorityPcrEvent (TpmType);
  }
}
