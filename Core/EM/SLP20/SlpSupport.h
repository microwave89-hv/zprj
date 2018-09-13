//****************************************************************************
//****************************************************************************
//**                                                                        **
//**             (C)Copyright 1985-2011, American Megatrends, Inc.          **
//**                                                                        **
//**                          All Rights Reserved.                          **
//**                                                                        **
//**             5555 Oakbrook Pkwy, Suite 200, Norcross, GA 30093          **
//**                                                                        **
//**                          Phone (770)-246-8600                          **
//**                                                                        **
//****************************************************************************
//****************************************************************************

//****************************************************************************
// $Header: /Alaska/BIN/Modules/SLP/SlpSupport.h 4     8/01/11 3:26p Vyacheslava $
//
// $Revision: 4 $
//
// $Date: 8/01/11 3:26p $
//****************************************************************************
// Revision History
// ----------------
// $Log: /Alaska/BIN/Modules/SLP/SlpSupport.h $
// 
// 4     8/01/11 3:26p Vyacheslava
// [TAG]  		EIP64110
// [Category]  	Spec Update
// [Severity]  	Normal
// [Description]  	This file has been updated to be compliant with PI 1.2,
// and UEFI 2.3.1 specifications. 
// 
// 3     7/01/11 12:00p Vyacheslava
// [TAG]  		EIP63678
// [Category]  	New Feature
// [Description]  	Preserve the OEM Activation SLIC during the BIOS
// recovery path.
// [Files]  		SlpSupport.sdl
// SlpSupport.mak
// SlpSupport.c
// SlpSupport.dxs
// SlpSupport.h
// SlpSupport.cif
// 
// 2     8/25/10 11:45a Vyacheslava
// Changed comments for better representation in the CHM file.
// 
// 1     5/18/10 4:11p Vyacheslava
// 
// 
//****************************************************************************
//<AMI_FHDR_START>
//
// Name:  SlpSupport.h
//
// Description: SlpSupport Header file.
//
//<AMI_FHDR_END>
//****************************************************************************

#ifndef __SLP_SUPPORT__H__
#define __SLP_SUPPORT__H__
#ifdef __cplusplus
extern "C" {
#endif

//------------------------------------------------------------------------

#include <EFI.h>
#include <Token.h>
#include <Acpi.h>

//------------------------------------------------------------------------

#define SLIC_SIG 0x43494c53  //"SLIC" Microsoft System Locked Preinstallation Table

#define OEM_SLP_PUBLIC_KEY_GUID \
  { 0x996aa1e0, 0x1e8c, 0x4f36, 0xb5, 0x19, 0xa1, 0x70, 0xa2, 0x06, 0xfc, 0x14 }
  
#define OEM_SLP_MARKER_GUID \
  { 0x69009842, 0x63f2, 0x43db, 0x96, 0x4b, 0xef, 0xad, 0x1c, 0x39, 0xec, 0x85 }

#define FLASH_UPPER_ADDRESS             0xFFFFFFFF
#define FLASH_DEVICE_BASE_ADDRESS       (FLASH_UPPER_ADDRESS-FLASH_SIZE+1)

//------------------------------------------------------------------------

#pragma pack (1)

//<AMI_SHDR_START>
//----------------------------------------------------------------------------
//
// Name: OEM_PUBLIC_KEY_STRUCTURE
//
// Description: This structure comes out of the document:
// OEM Activation version 2.0 for M$ Windows Vista (tm) Operating System.
//
// Fields:   
//  Name           Type    Description
//  ------------------------------------------------------------------
//  StructType     UINT32  0x00000000 = PubKey Structure.
//  LicensingData  UINT32  Length, in bytes, of OEM pub key struct (156).
//  bType          UINT8   Public Key Type [PUBLICKEYBLOB (6)].
//  bVersion       UINT8   Version, currently 2 (7/27/2006).
//  Reserved       UINT16  Zero.
//  aiKeyAlg       UINT32  Key Algorithm. [CALG_RSA_SIGN (0x00002400)].
//  Magic          UINT32  bytes: 'RSA1'.
//  BitLen         UINT32  1024 converted to hex.
//  Pubexp         UINT32  Exponent of Public Key, usually 257 converted to hex.
//  Modulus        UINT8   Array. Modulus, modulues of the public key 128 bytes.
//
//----------------------------------------------------------------------------
//<AMI_SHDR_END>

typedef struct {
    UINT32  StructType;
    UINT32  LicensingData;
    UINT8   bType;
    UINT8   bVersion;
    UINT16  Reserved;
    UINT32  aiKeyAlg;
    UINT32  Magic;
    UINT32  Bitlen;
    UINT32  Pubexp;
    UINT8   Modulus[128];
} OEM_PUBLIC_KEY_STRUCTURE;

//<AMI_SHDR_START>
//----------------------------------------------------------------------------
//
// Name: WINDOWS_MARKER_STRUCTURE
//
// Description: This structure comes out of the document:
// OEM Activation version 2.0 for M$ Windows Vista (tm) Operating System.
//
// Fields:   
//  Name            Type    Description
//  ------------------------------------------------------------------
//  StructType      UINT32  0x00000001 = Windows marker structure
//  LicensingData   UINT32  Length, in bytes of Windows Marker (182)
//  dwVersion       UINT32  Version of the Windows Marker (0x0002000)
//  sOEMID          UINT8   The OEMID value from XSDT and RSDT (must match). (6 bytes)
//  sOEMTABLEID     UINT8   the OEMTABLEID from XSDT and RSDT (must match). (8 bytes)
//  sWindowsFlag    UINT8   'WINDOWS ' (notice trailing space, not null terminated). (8 bytes)
//  Reserved        UINT8   Reserved for future use. (20 bytes)
//  Signature       UINT8   SHA256 Signature from the Windows Marker. (128 bytes)
//
//----------------------------------------------------------------------------
//<AMI_SHDR_END>

typedef struct {
    UINT32  StructType;
    UINT32  LicensingData;
    UINT32  dwVersion;
    UINT8   sOEMID[6];
    UINT8   sOEMTABLEID[8];
    UINT8   sWindowsFlag[8];
    UINT8   Reserved[20];
    UINT8   Signature[128];
} WINDOWS_MARKER_STRUCTURE;

//<AMI_SHDR_START>
//----------------------------------------------------------------------------
//
// Name: EFI_ACPI_SLP
//
// Description: This structure comes out of the document:
// OEM Activation version 2.0 for M$ Windows Vista (tm) Operating System.
//
// Fields:      
//  Name       Type                         Description
//  ------------------------------------------------------------------
//  Header      EFI_ACPI_DESCRIPTION_HEADER Common ACPI table header
//  PubKey      OEM_PUBLIC_KEY_STRUCTURE    See above for description
//  WinMarker   WINDOWS_MARKER_STRUCTURE    See above for description
//
//----------------------------------------------------------------------------
//<AMI_SHDR_END>

typedef struct {
    ACPI_HDR Header;
    OEM_PUBLIC_KEY_STRUCTURE PubKey;
    WINDOWS_MARKER_STRUCTURE WinMarker;
} EFI_ACPI_SLP;

#pragma pack()


/****** DO NOT WRITE BELOW THIS LINE *******/
#ifdef __cplusplus
}
#endif
#endif

//****************************************************************************
//****************************************************************************
//**                                                                        **
//**             (C)Copyright 1985-2011, American Megatrends, Inc.          **
//**                                                                        **
//**                          All Rights Reserved.                          **
//**                                                                        **
//**             5555 Oakbrook Pkwy, Suite 200, Norcross, GA 30093          **
//**                                                                        **
//**                          Phone (770)-246-8600                          **
//**                                                                        **
//****************************************************************************
//****************************************************************************
