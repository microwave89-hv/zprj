//**********************************************************************
//**********************************************************************
//**                                                                  **
//**        (C)Copyright 1985-2005, American Megatrends, Inc.         **
//**                                                                  **
//**                       All Rights Reserved.                       **
//**                                                                  **
//**             6145-F Northbelt Pkwy, Norcross, GA 30071            **
//**                                                                  **
//**                       Phone: (770)-246-8600                      **
//**                                                                  **
//**********************************************************************
//**********************************************************************

//**********************************************************************
// $Header: /Alaska/BIN/Core/Include/Protocol/BusSpecificDriverOverride.h 3     3/13/06 1:40a Felixp $
//
// $Revision: 3 $
//
// $Date: 3/13/06 1:40a $
//**********************************************************************
// Revision History
// ----------------
// $Log: /Alaska/BIN/Core/Include/Protocol/BusSpecificDriverOverride.h $
// 
// 3     3/13/06 1:40a Felixp
// 
// 2     3/04/05 10:32a Mandal
// 
// 1     1/28/05 12:44p Felixp
// 
// 2     1/18/05 3:21p Felixp
// PrintDebugMessage renamed to Trace
// 
// 1     12/23/04 9:41a Felixp
// 
// 2     3/13/04 5:13p Felixp
// 
// 1     3/13/04 4:36p Felixp
// 
//**********************************************************************
//<AMI_FHDR_START>
//
// Name:	BusSpecificDriverOverride
//
// Description:	EFI_BUS_SPECIFIC_DRIVER_OVERRIDE Protocol Definition
//
//<AMI_FHDR_END>
//**********************************************************************
#ifndef __EFI_BUS_SPECIFIC_DRIVER_OVERRIDE_PROTOCOL__H__
#define __EFI_BUS_SPECIFIC_DRIVER_OVERRIDE_PROTOCOL__H__
#ifdef __cplusplus
extern "C" {
#endif
#include <EFI.h>

#define EFI_BUS_SPECIFIC_DRIVER_OVERRIDE_PROTOCOL_GUID \
	{ 0x3bc1b285,0x8a15,0x4a82,0xaa,0xbf,0x4d,0x7d,0x13,0xfb,0x32,0x65 }

GUID_VARIABLE_DECLARATION(gEfiBusSpecificDriverOverrideProtocolGuid,EFI_BUS_SPECIFIC_DRIVER_OVERRIDE_PROTOCOL_GUID);

typedef struct _EFI_BUS_SPECIFIC_DRIVER_OVERRIDE_PROTOCOL EFI_BUS_SPECIFIC_DRIVER_OVERRIDE_PROTOCOL;

typedef EFI_STATUS (EFIAPI *EFI_BUS_SPECIFIC_DRIVER_OVERRIDE_GET_DRIVER) (
	IN EFI_BUS_SPECIFIC_DRIVER_OVERRIDE_PROTOCOL *This,
	IN OUT EFI_HANDLE *DriverImageHandle
);

struct _EFI_BUS_SPECIFIC_DRIVER_OVERRIDE_PROTOCOL {
	EFI_BUS_SPECIFIC_DRIVER_OVERRIDE_GET_DRIVER GetDriver;
};
/****** DO NOT WRITE BELOW THIS LINE *******/
#ifdef __cplusplus
}
#endif
#endif
//**********************************************************************
//**                                                                  **
//**        (C)Copyright 1985-2005, American Megatrends, Inc.         **
//**                                                                  **
//**                       All Rights Reserved.                       **
//**                                                                  **
//**             6145-F Northbelt Pkwy, Norcross, GA 30071            **
//**                                                                  **
//**                       Phone: (770)-246-8600                      **
//**                                                                  **
//**********************************************************************
//**********************************************************************
