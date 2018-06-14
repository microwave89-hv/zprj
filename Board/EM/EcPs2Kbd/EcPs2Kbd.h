//**********************************************************************
//**********************************************************************
//**                                                                  **
//**        (C)Copyright 1985-2008, American Megatrends, Inc.         **
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
//
// $Header: /Alaska/SOURCE/Modules/EcPs2Kbd/EcPs2Kbd.h 3     7/18/11 5:58p Stacyh $
//
// $Revision: 3 $
//
// $Date: 7/18/11 5:58p $
//
//*****************************************************************************
// Revision History
// ----------------
// $Log: /Alaska/SOURCE/Modules/EcPs2Kbd/EcPs2Kbd.h $
// 
// 3     7/18/11 5:58p Stacyh
// [TAG]  		EIP65200
// [Category]  	Improvement
// [Description]  	Port EcPs2Kbd to be compliant with PI 1.2, and UEFI
// 2.3.1 specifications.
// [Files]  		EcPs2Kbd.h
// 
// 2     6/03/08 10:05a Stacyh
// 
// 1     5/30/08 4:23p Stacyh
// 
//
//*****************************************************************************


//<AMI_FHDR_START>
//----------------------------------------------------------------------------
//
// Name:		EcPs2Kbd.h
//
// Description:	defines needed for EcPs2Kbd.
//
// Notes:		
//
//----------------------------------------------------------------------------
//<AMI_FHDR_END>
#include <GenericSIO.h>
#include <Protocol\DevicePath.h>
#include <AmiDxeLib.h>

#define END_DEVICE_PATH_TYPE			0x7f
#define END_ENTIRE_DEVICE_PATH_SUBTYPE	0xff

typedef struct {
	ACPI_HID_DEVICE_PATH		AcpiDevicePath;
	EFI_DEVICE_PATH_PROTOCOL	EndDevicePath;
} PS2_KBD_DEVICE_PATH;


typedef struct _PS2KBD_DEV {
	EFI_DEVICE_PATH_PROTOCOL	*DevicePath;
	EFI_HANDLE					Handle;
} PS2KBD_DEV;

//**********************************************************************
//**********************************************************************
//**                                                                  **
//**        (C)Copyright 1985-2008, American Megatrends, Inc.         **
//**                                                                  **
//**                       All Rights Reserved.                       **
//**                                                                  **
//**             6145-F Northbelt Pkwy, Norcross, GA 30071            **
//**                                                                  **
//**                       Phone: (770)-246-8600                      **
//**                                                                  **
//**********************************************************************
//**********************************************************************
