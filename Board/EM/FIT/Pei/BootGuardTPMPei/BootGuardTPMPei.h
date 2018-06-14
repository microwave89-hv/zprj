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
// $Header: /Alaska/SOURCE/Modules/SharkBayRefCodes/FIT/Pei/BootGuardTPMPei/BootGuardTPMPei.h 2     7/25/13 11:03p Bensonlai $
//
// $Revision: 2 $
//
// $Date: 7/25/13 11:03p $
//**********************************************************************
// Revision History
// ----------------
// $Log: /Alaska/SOURCE/Modules/SharkBayRefCodes/FIT/Pei/BootGuardTPMPei/BootGuardTPMPei.h $
// 
// 2     7/25/13 11:03p Bensonlai
// [TAG]  		EIP130647
// [Category]  	Bug Fix
// [Severity]  	Normal
// [Symptom]  	Detail PCR is incorrect for Boot Guard.
// [RootCause]  	Coding error.
//
// 1     6/04/13 5:15a Bensonlai
// [TAG]  		EIP125148
// [Category]  	Spec Update
// [Severity]  	Normal
// [Description]  	[SBY ULT] Boot Guard for 4th Gen Intel Core Processor
// based on Mobile U-Processor Line - BIOS Writer's Guide - Rev 1.0
// [Files]  		BootGuardTPMPei.cif
// BootGuardTPMPei.c
// BootGuardTPMPei.h
// BootGuardTPMPei.sdl
// BootGuardTPMPei.mak
//
//**********************************************************************
//<AMI_FHDR_START>
//
// Name: BootGuardTPMPei.c
//
// Description: TPM Initialization Flow for Boot Guard
//
//<AMI_FHDR_END>
//**********************************************************************

#ifndef _BOOT_GUARD_TPM_PEI_H_
#define _BOOT_GUARD_TPM_PEI_H_

//
// Define macros to build data structure signatures from characters.
//
#define EFI_SIGNATURE_16(A, B)        ((A) | (B << 8))
#define EFI_SIGNATURE_32(A, B, C, D)  (EFI_SIGNATURE_16 (A, B) | (EFI_SIGNATURE_16 (C, D) << 16))
#define EFI_SIGNATURE_64(A, B, C, D, E, F, G, H) \
    (EFI_SIGNATURE_32 (A, B, C, D) | ((UINT64) (EFI_SIGNATURE_32 (E, F, G, H)) << 32))

#define IBB_ENTRYPOINT_M  0xFFFFFFC0
#define ACM_STATUS        0xFED30328

// The LocateTcgPPi(...) entry is call the AmiTcgPlatformPeiLib.obj
EFI_STATUS LocateTcgPpi(
    IN EFI_PEI_SERVICES **PeiServices,
    IN PEI_TPM_PPI      **gTpmDevicePpi,
    IN PEI_TCG_PPI      **gTcgPpi
);

#pragma pack(1)
typedef struct _TCG_PEI_CALLBACK_CONTEXT
{
    PEI_TPM_PPI      *TpmDevice;
    EFI_PEI_SERVICES **PeiServices;
} TCG_PEI_CALLBACK_CONTEXT;

typedef struct _BOOT_POLICY
{
    UINT8            RSTR0:1;
    UINT8            RSTR1:1;
    UINT8            RSTR2:1;
    UINT8            RSTR3:1;
    UINT8            RSTR4:1;
    UINT8            RSTR5:1;
    UINT8            RSTR6:1;
    UINT8            RSTR7:1;
    UINT8            TYPE0:1;
    UINT8            TYPE1:1;
    UINT8            TYPE2:1;
    UINT8            TYPE3:1;
    UINT8            TYPE4:1;
    UINT8            TYPE5:1;
    UINT8            TYPE6:1;
    UINT8            TYPE7:1;
    UINT16           ACM_SVN;
    UINT8            ACM_Signature[256];
    UINT8            Key_Manifest_Signature[256];
    UINT8            Boot_Policy_Manifest_Signature[256];
    UINT8            Digest_of_Hashed_IBB_Segment[32];
} BOOT_POLICY;

typedef struct _FIT_ENTRY
{
    UINT64           TblAddress;
    UINT32           TblSIZE;
    UINT16           TblVer;
    UINT8            TblType;
    UINT8            TblChkSum;
} FIT_ENTRY;

//
// Manifest definition
//
#define TPM_ALG_SHA1        0x4
#define TPM_ALG_SHA256      0xB
#define SHA1_DIGEST_SIZE    20
#define SHA256_DIGEST_SIZE  32

typedef struct {
    UINT16   HashAlg;
    UINT16   Size;
    UINT8    HashBuffer[SHA256_DIGEST_SIZE];
} HASH_STRUCTURE;

#define RSA_PUBLIC_KEY_STRUCT_KEY_SIZE_DEFAULT  2048
#define RSA_PUBLIC_KEY_STRUCT_KEY_LEN_DEFAULT   (RSA_PUBLIC_KEY_STRUCT_KEY_SIZE_DEFAULT/8)
#define RSA_PUBLIC_KEY_STRUCT_KEY_EXPONENT_DEFAULT  0x10001 // NOT 0x10001
typedef struct {
    UINT8    Version;
    UINT16   KeySize;
    UINT32   Exponent;
    UINT8    Modulus[RSA_PUBLIC_KEY_STRUCT_KEY_LEN_DEFAULT];
} RSA_PUBLIC_KEY_STRUCT;

#define RSASSA_SIGNATURE_STRUCT_KEY_SIZE_DEFAULT  2048
#define RSASSA_SIGNATURE_STRUCT_KEY_LEN_DEFAULT   (RSASSA_SIGNATURE_STRUCT_KEY_SIZE_DEFAULT/8)
typedef struct {
    UINT8    Version;
    UINT16   KeySize;
    UINT16   HashAlg;
    UINT8    Signature[RSASSA_SIGNATURE_STRUCT_KEY_LEN_DEFAULT];
} RSASSA_SIGNATURE_STRUCT;

typedef struct {
    UINT8                    Version;
    UINT16                   KeyAlg;
    RSA_PUBLIC_KEY_STRUCT    Key;
    UINT16                   SigScheme;
    RSASSA_SIGNATURE_STRUCT  Signature;
} KEY_SIGNATURE_STRUCT;

typedef struct {
    UINT8              StructureID[8];
    UINT8              StructVersion;
    UINT8              HdrStructVersion;
    UINT8              PMBPMVersion;
    UINT8              BPSVN_BPM;
    UINT8              ACMSVN_BPM;
    UINT8              Reserved;
    UINT16             NEMDataStack;
} BOOT_POLICY_MANIFEST_HEADER;

typedef struct {
    UINT16   Reserved;
    UINT16   Flags;
    UINT32   Base;
    UINT32   Size;
} IBB_SEGMENT_ELEMENT;

typedef struct {
    UINT8               StructureID[8];
    UINT8               StructVersion;
    UINT8               SetNumber;
    UINT8               Reserved;
    UINT8               PBETValue;
    UINT32              Flags;
    UINT64              IBB_MCHBAR;
    UINT64              VTD_BAR;
    UINT32              PMRL_Base;
    UINT32              PMRL_Limit;
    UINT64              PMRH_Base;
    UINT64              PMRH_Limit;
    HASH_STRUCTURE      PostIbbHash;
    UINT32              EntryPoint;
    HASH_STRUCTURE      Digest;
    UINT8               SegmentCount; // 1 ~ 8
    IBB_SEGMENT_ELEMENT IBBSegment[1];
} IBB_ELEMENT;

typedef struct {
    UINT8    StructureID[8];
    UINT8    StructVersion;
    UINT16   PMDataSize;
//UINT8    PMData[PMDataSize];
} PLATFORM_MANUFACTURER_ELEMENT;

typedef struct {
    UINT8                 StructureID[8];
    UINT8                 StructVersion;
    KEY_SIGNATURE_STRUCT  KeySignature;
} BOOT_POLICY_MANIFEST_SIGNATURE_ELEMENT;

typedef struct {
    BOOT_POLICY_MANIFEST_HEADER                   Bpm_Header;
    IBB_ELEMENT                                   Ibb_Element;
    //PLATFORM_MANUFACTURER_ELEMENT                 Platform_Manufacture_Element;
    BOOT_POLICY_MANIFEST_SIGNATURE_ELEMENT        Bpm_Signature_Element;
} BpmStruct;

typedef struct {
    UINT8                  StructureID[8];
    UINT8                  StructVersion;
    UINT8                  KeyManifestVersion;
    UINT8                  KMSVN;
    UINT8                  KeyManifestID;
    HASH_STRUCTURE         BPKey;
    KEY_SIGNATURE_STRUCT   KeyManifestSignature;
} KEY_MANIFEST_STRAUCTURE;

#pragma pack()

#endif

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
