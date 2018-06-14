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
// $Header: /Alaska/BIN/Core/Include/Protocol/IncompatiblePciDeviceSupport.h 1     3/13/06 1:40a Felixp $
//
// $Revision: 1 $
//
// $Date: 3/13/06 1:40a $
//**********************************************************************
// Revision History
// ----------------
// $Log: /Alaska/BIN/Core/Include/Protocol/IncompatiblePciDeviceSupport.h $
// 
// 1     3/13/06 1:40a Felixp
// 
//**********************************************************************
//<AMI_FHDR_START>
//
// Name:	<This File Name>
//
// Description:	
//
//<AMI_FHDR_END>
//**********************************************************************
#ifndef __INCOMPATIBLE_PCI_DEVICE_SUPPORT_PROTOCOL_H__
#define __INCOMPATIBLE_PCI_DEVICE_SUPPORT_PROTOCOL_H__
#ifdef __cplusplus
extern "C" {
#endif
#include <EFI.h>

#define EFI_INCOMPATIBLE_PCI_DEVICE_SUPPORT_PROTOCOL_GUID \
        {0xeb23f55a, 0x7863, 0x4ac2, 0x8d, 0x3d, 0x95, 0x65, 0x35, 0xde, 0x03, 0x75}

GUID_VARIABLE_DECLARATION(gEfiIncompatiblePciDeviceSupportProtocolGuid,EFI_INCOMPATIBLE_PCI_DEVICE_SUPPORT_PROTOCOL_GUID);

typedef struct _EFI_INCOMPATIBLE_PCI_DEVICE_SUPPORT_PROTOCOL EFI_INCOMPATIBLE_PCI_DEVICE_SUPPORT_PROTOCOL;
  
typedef EFI_STATUS (EFIAPI *EFI_INCOMPATIBLE_PCI_DEVICE_SUPPORT_CHECK_DEVICE) (
	IN  EFI_INCOMPATIBLE_PCI_DEVICE_SUPPORT_PROTOCOL	*This,
	IN  UINTN								VendorId,
	IN  UINTN								DeviceId,
	IN  UINTN								Revision,
	IN  UINTN								SubVendorId,OPTIONAL
	IN  UINTN								SubDeviceId,OPTIONAL
	OUT VOID								*Configuration
); 


typedef struct _EFI_INCOMPATIBLE_PCI_DEVICE_SUPPORT_PROTOCOL {
  EFI_INCOMPATIBLE_PCI_DEVICE_SUPPORT_CHECK_DEVICE      CheckDevice;  
} EFI_INCOMPATIBLE_PCI_DEVICE_SUPPORT_PROTOCOL;

 
/****** DO NOT WRITE BELOW THIS LINE *******/
#ifdef __cplusplus
}
#endif

#endif
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

