//**********************************************************************
//**********************************************************************
//**                                                                  **
//**        (C)Copyright 1985-2011, American Megatrends, Inc.         **
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
// $Header: /Alaska/BIN/Chipset/Intel/NorthBridge/Haswell/Intel SystemAgent NB Chipset/LegacyRegion/LegacyRegion Protocols/LegacyRegion2.h 1     4/02/13 6:28a Ireneyang $
//
// $Revision: 1 $
//
// $Date: 4/02/13 6:28a $
//**********************************************************************
// Revision History
// ----------------
// $Log: /Alaska/BIN/Chipset/Intel/NorthBridge/Haswell/Intel SystemAgent NB Chipset/LegacyRegion/LegacyRegion Protocols/LegacyRegion2.h $
// 
// 1     4/02/13 6:28a Ireneyang
// 
// 1     12/20/12 12:40p Olegi
// 
// 2     5/24/11 2:04p Olegi
// Header/footer updated.
// 
// 6     1/13/10 2:13p Felixp
// 
//**********************************************************************
//<AMI_FHDR_START>
//
// Name:  LegacyRegion2.h
//
// Description:	LegacyRegion2 protocol definition (PI 1.2, Volume 5)
//
//<AMI_FHDR_END>
//**********************************************************************
#ifndef __LEGACY_REGION2_PROTOCOL_H__
#define __LEGACY_REGION2_PROTOCOL_H__
#ifdef __cplusplus
extern "C" {
#endif

#include <Efi.h>

#define EFI_LEGACY_REGION2_PROTOCOL_GUID \
    { 0x70101eaf, 0x85, 0x440c, 0xb3, 0x56, 0x8e, 0xe3, 0x6f, 0xef, 0x24, 0xf0 }

GUID_VARIABLE_DECLARATION(gEfiLegacyRegion2ProtocolGuid,EFI_LEGACY_REGION2_PROTOCOL_GUID);

typedef struct _EFI_LEGACY_REGION2_PROTOCOL EFI_LEGACY_REGION2_PROTOCOL;

typedef EFI_STATUS (EFIAPI *EFI_LEGACY_REGION2_DECODE)(
    IN  EFI_LEGACY_REGION2_PROTOCOL  *This,
    IN  UINT32                       Start,
    IN  UINT32                       Length,
    OUT UINT32                       *Granularity,
    IN  BOOLEAN                      *On
);

typedef EFI_STATUS (EFIAPI *EFI_LEGACY_REGION2_LOCK)(
    IN  EFI_LEGACY_REGION2_PROTOCOL   *This,
    IN  UINT32                        Start,
    IN  UINT32                        Length,
    OUT UINT32                        *Granularity
);

typedef EFI_STATUS (EFIAPI *EFI_LEGACY_REGION2_BOOT_LOCK)(
    IN  EFI_LEGACY_REGION2_PROTOCOL         *This,
    IN  UINT32                              Start,
    IN  UINT32                              Length,
    OUT UINT32                              *Granularity OPTIONAL
);

typedef EFI_STATUS (EFIAPI *EFI_LEGACY_REGION2_UNLOCK)(
    IN  EFI_LEGACY_REGION2_PROTOCOL  *This,
    IN  UINT32                       Start,
    IN  UINT32                       Length,
    OUT UINT32                       *Granularity
);

typedef enum {
    LegacyRegionDecoded,       ///< This region is currently set to allow reads.
    LegacyRegionNotDecoded,    ///< This region is currently set to not allow reads.
    LegacyRegionWriteEnabled,  ///< This region is currently set to allow writes.
    LegacyRegionWriteDisabled, ///< This region is currently set to write protected.
    LegacyRegionBootLocked,    ///< This region's attributes are locked, cannot be modified until
                               ///< after a power cycle.
    LegacyRegionNotLocked      ///< This region's attributes are not locked.
} EFI_LEGACY_REGION_ATTRIBUTE;

typedef struct {
  /// The beginning of the physical address of this
  /// region.
  UINT32                      Start;
  /// The number of bytes in this region.
  UINT32                      Length;
  /// Attribute of the Legacy Region Descriptor that
  /// describes the capabilities for that memory region.
  EFI_LEGACY_REGION_ATTRIBUTE Attribute;
  /// Describes the byte length programmability
  /// associated with the Start address and the specified
  /// Attribute setting.
  UINT32                      Granularity;
} EFI_LEGACY_REGION_DESCRIPTOR;

typedef EFI_STATUS (EFIAPI *EFI_LEGACY_REGION_GET_INFO)(
    IN  EFI_LEGACY_REGION2_PROTOCOL   *This,
    OUT UINT32                        *DescriptorCount,
    OUT EFI_LEGACY_REGION_DESCRIPTOR  **Descriptor
);

/// The EFI_LEGACY_REGION2_PROTOCOL is used to abstract the hardware control of the memory 
/// attributes of the Option ROM shadowing region, 0xC0000 to 0xFFFFF.
/// There are three memory attributes that can be modified through this protocol: read, write and
/// boot-lock. These protocols may be set in any combination.
struct _EFI_LEGACY_REGION2_PROTOCOL {
    EFI_LEGACY_REGION2_DECODE     Decode;
    EFI_LEGACY_REGION2_LOCK       Lock;
    EFI_LEGACY_REGION2_BOOT_LOCK  BootLock;
    EFI_LEGACY_REGION2_UNLOCK     UnLock;
    EFI_LEGACY_REGION_GET_INFO    GetInfo;
};

/****** DO NOT WRITE BELOW THIS LINE *******/
#ifdef __cplusplus
}
#endif
#endif
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
