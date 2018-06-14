//**********************************************************************
//**********************************************************************
//**                                                                  **
//**        (C)Copyright 1985-2010, American Megatrends, Inc.         **
//**                                                                  **
//**                       All Rights Reserved.                       **
//**                                                                  **
//**           5555 Oakbrook Pkwy, Suite 200, Norcross, GA 30093      **
//**                                                                  **
//**                       Phone: (770)-246-8600                      **
//**                                                                  **
//**********************************************************************
//**********************************************************************

//**********************************************************************
// $Header: /Alaska/BIN/Chipset/Intel/NorthBridge/Haswell/Intel SystemAgent NB Chipset/LegacyRegion/LegacyRegion Protocols/LegacyRegion.h 1     4/02/13 6:28a Ireneyang $
//
// $Revision: 1 $
//
// $Date: 4/02/13 6:28a $
//**********************************************************************
// Revision History
// ----------------
// $Log: /Alaska/BIN/Chipset/Intel/NorthBridge/Haswell/Intel SystemAgent NB Chipset/LegacyRegion/LegacyRegion Protocols/LegacyRegion.h $
// 
// 1     4/02/13 6:28a Ireneyang
// 
// 1     12/20/12 12:40p Olegi
// 
// 5     1/12/10 11:51a Olegi
// Copyright message updated.
// 
// 4     4/27/07 5:17p Olegi
// CSM.CHM file preparation.
//
// 3     3/13/06 2:43p Felixp
//
// 2     1/18/05 3:22p Felixp
// PrintDebugMessage renamed to Trace
//
// 1     10/26/04 9:48a Olegi
//
// 1     8/30/04 3:13p Markw
//
// 2     8/24/04 3:56p Markw
// Fixed ifndef in *.h file.
//
// 1     8/24/04 3:55p Markw
//
//**********************************************************************
//<AMI_FHDR_START>
//
// Name: LegacyRegion.h
//
// Description: LegacyRegion protocol API declaration
//
//<AMI_FHDR_END>
//**********************************************************************
#ifndef __LEGACY_REGION_PROTOCOL_H__
#define __LEGACY_REGION_PROTOCOL_H__
#ifdef __cplusplus
extern "C" {
#endif
#include <EFI.h>

//{0FC9013A-0568-4BA9-9B7E-C9C390A6609B}
#define EFI_LEGACY_REGION_PROTOCOL_GUID \
    {0xfc9013a,0x568,0x4ba9,0x9b,0x7e,0xc9,0xc3,0x90,0xa6,0x60,0x9b}

GUID_VARIABLE_DECLARATION(gEfiLegacyRegionProtocolGuid,EFI_LEGACY_REGION_PROTOCOL_GUID);

typedef struct _EFI_LEGACY_REGION_PROTOCOL EFI_LEGACY_REGION_PROTOCOL;

typedef EFI_STATUS (EFIAPI *EFI_LEGACY_REGION_DECODE) (
    IN EFI_LEGACY_REGION_PROTOCOL   *This,
    IN UINT32                       Start,
    IN UINT32                       Length,
    IN BOOLEAN                      *On
);

typedef EFI_STATUS (EFIAPI *EFI_LEGACY_REGION_LOCK) (
    IN  EFI_LEGACY_REGION_PROTOCOL  *This,
    IN  UINT32                      Start,
    IN  UINT32                      Length,
    OUT UINT32                      *Granularity  OPTIONAL
);

typedef EFI_STATUS (EFIAPI *EFI_LEGACY_REGION_BOOT_LOCK) (
    IN  EFI_LEGACY_REGION_PROTOCOL  *This,
    IN  UINT32                      Start,
    IN  UINT32                      Length,
    OUT UINT32                      *Granularity  OPTIONAL
);

typedef EFI_STATUS (EFIAPI *EFI_LEGACY_REGION_UNLOCK) (
    IN  EFI_LEGACY_REGION_PROTOCOL  *This,
    IN  UINT32                      Start,
    IN  UINT32                      Length,
    OUT UINT32                      *Granularity  OPTIONAL
);


struct _EFI_LEGACY_REGION_PROTOCOL {
    EFI_LEGACY_REGION_DECODE    Decode;
    EFI_LEGACY_REGION_LOCK      Lock;
    EFI_LEGACY_REGION_BOOT_LOCK BootLock;
    EFI_LEGACY_REGION_UNLOCK    UnLock;
};


/****** DO NOT WRITE BELOW THIS LINE *******/
#ifdef __cplusplus
}
#endif
#endif

//**********************************************************************
//**********************************************************************
//**                                                                  **
//**        (C)Copyright 1985-2010, American Megatrends, Inc.         **
//**                                                                  **
//**                       All Rights Reserved.                       **
//**                                                                  **
//**           5555 Oakbrook Pkwy, Suite 200, Norcross, GA 30093      **
//**                                                                  **
//**                       Phone: (770)-246-8600                      **
//**                                                                  **
//**********************************************************************
//**********************************************************************
