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
// $Header: /Alaska/SOURCE/Modules/SharkBayRefCodes/FIT/Dxe/BootGuardTPM2Dxe/BootGuardTPM2Dxe.h 1     9/06/13 6:17a Bensonlai $
//
// $Revision: 1 $
//
// $Date: 9/06/13 6:17a $
//**********************************************************************
// Revision History
// ----------------
// $Log: /Alaska/SOURCE/Modules/SharkBayRefCodes/FIT/Dxe/BootGuardTPM2Dxe/BootGuardTPM2Dxe.h $
// 
// 1     9/06/13 6:17a Bensonlai
// [TAG]  		EIP135513 
// [Category]  	New Feature
// [Description]  	Implementation of Boot Guard of PTT flow for WHCK test.
// [Files]  		BootGuardTPM2Dxe.cif
// BootGuardTPM2Dxe.c
// BootGuardTPM2Dxe.h
// BootGuardTPM2Dxe.sdl
// BootGuardTPM2Dxe.mak
//
//**********************************************************************
//<AMI_FHDR_START>
//
// Name: BootGuardTPM2Dxe.c
//
// Description: TPM2 Initialization Flow for Boot Guard
//
//<AMI_FHDR_END>
//**********************************************************************

#ifndef _BOOT_GUARD_TPM2_H_
#define _BOOT_GUARD_TPM2_H_

#ifndef _EFI_MMIO_ACCESS_H_
#define _EFI_MMIO_ACCESS_H_

#define MmioAddress(BaseAddr, Register) \
    ( (UINTN)BaseAddr + (UINTN)(Register) )

// 32-bit
#define Mmio32Ptr(BaseAddr, Register) \
    ( (volatile UINT32 *)MmioAddress(BaseAddr, Register) )

#define Mmio32(BaseAddr, Register) \
    *Mmio32Ptr(BaseAddr, Register)

#define MmioRead32(Addr) \
    Mmio32(Addr, 0)

#define MmioWrite32(Addr, Value) \
    (Mmio32(Addr, 0) = (UINT32)Value)

#define MmioRW32(Addr, set, reset) \
    (Mmio32(Addr, 0) = ((Mmio32(Addr, 0) & (UINT32)~(reset)) | (UINT32)set))

// 16-bit
#define Mmio16Ptr(BaseAddr, Register) \
    ( (volatile UINT16 *)MmioAddress(BaseAddr, Register) )

#define Mmio16(BaseAddr, Register) \
    *Mmio16Ptr(BaseAddr, Register)

#define MmioRead16(Addr) \
    Mmio16(Addr, 0)

#define MmioWrite16(Addr, Value) \
    (Mmio16(Addr, 0) = (UINT16)Value)

#define MmioRW16(Addr, set, reset) \
    (Mmio16(Addr, 0) = ((Mmio16(Addr, 0) & (UINT16)~(reset)) | (UINT16)set))

// 8-bit
#define Mmio8Ptr(BaseAddr, Register) \
    ( (volatile UINT8 *)MmioAddress(BaseAddr, Register) )

#define Mmio8(BaseAddr, Register) \
    *Mmio8Ptr(BaseAddr, Register)

#define MmioRead8(Addr) \
    Mmio8(Addr, 0)

#define MmioWrite8(Addr, Value) \
    (Mmio8(Addr, 0) = (UINT8)Value)

#define MmioRW8(Addr, set, reset) \
    (Mmio8(Addr, 0) = ((Mmio8(Addr, 0) & (UINT8)~(reset)) | (UINT8)set))

#endif

//
// Define macros to build data structure signatures from characters.
//
#define EFI_SIGNATURE_16(A, B)        ((A) | (B << 8))
#define EFI_SIGNATURE_32(A, B, C, D)  (EFI_SIGNATURE_16 (A, B) | (EFI_SIGNATURE_16 (C, D) << 16))
#define EFI_SIGNATURE_64(A, B, C, D, E, F, G, H) \
    (EFI_SIGNATURE_32 (A, B, C, D) | ((UINT64) (EFI_SIGNATURE_32 (E, F, G, H)) << 32))

#define IBB_ENTRYPOINT_M  0xFFFFFFC0

#pragma pack(1)

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
