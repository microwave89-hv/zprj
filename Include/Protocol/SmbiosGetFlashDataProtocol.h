//**********************************************************************//
//**********************************************************************//
//**                                                                  **//
//**        (C)Copyright 1985-2010, American Megatrends, Inc.         **//
//**                                                                  **//
//**                       All Rights Reserved.                       **//
//**                                                                  **//
//**        5555 Oakbrook Pkwy, Suite 200, Norcross, GA 30093         **//
//**                                                                  **//
//**                       Phone: (770)-246-8600                      **//
//**                                                                  **//
//**********************************************************************//
//**********************************************************************//

//**********************************************************************//
// $Header: /Alaska/BIN/Modules/SMBIOS/SmbiosProtocol/SmbiosGetFlashDataProtocol.h 7     5/18/10 5:15p Davidd $
//
// $Revision: 7 $
//
// $Date: 5/18/10 5:15p $
//**********************************************************************//
// Revision History
// ----------------
// $Log: /Alaska/BIN/Modules/SMBIOS/SmbiosProtocol/SmbiosGetFlashDataProtocol.h $
// 
// 7     5/18/10 5:15p Davidd
// Added PnP function 52h commands 3 and 4 support - EIP 38010.
// 
// 6     6/02/09 3:53p Davidd
// Updated AMI headers (EIP 22180)
// 
// 5     11/14/08 4:42p Davidd
// 
// 4     3/28/07 7:46p Davidd
// Updated the year on the AMI banner
// 
// 3     12/15/06 1:15p Davidd
// Code cleanup and reformatted to coding  standard.
//
// 2     8/10/05 11:12a Davidd
// Added EFI_SMBIOS_PROTOCOL_GUID.
//
// 1     5/02/05 3:23p Davidd
// Initial Check-in.
//
// 1     4/29/05 2:12p Davidd
// Initial checkin.
//
//**********************************************************************//

#ifndef _EFI_SMBOS_GET_FLASH_DATA_PROTOCOL_H_
#define _EFI_SMBOS_GET_FLASH_DATA_PROTOCOL_H_

#include <token.h>

#define EFI_SMBIOS_FLASH_DATA_PROTOCOL_GUID \
	{0xddfb5557,0x3e2e,0x4569,0xb4,0x59,0xbe,0xff,0xe1,0x89,0xb8,0xb0}

typedef struct _EFI_SMBIOS_FLASH_DATA_PROTOCOL EFI_SMBIOS_FLASH_DATA_PROTOCOL;

typedef EFI_STATUS (*GET_FLASH_TABLE_INFO)(
    IN  EFI_SMBIOS_FLASH_DATA_PROTOCOL  *This,
    OUT VOID                            **Location,
    OUT UINT32                          *Size
);

typedef EFI_STATUS (*GET_FIELD) (
    IN  EFI_SMBIOS_FLASH_DATA_PROTOCOL  *This,
    IN  UINT8                           Table,
    IN  UINT8                           Offset,
    OUT VOID                            **String
);

struct _EFI_SMBIOS_FLASH_DATA_PROTOCOL {
    GET_FLASH_TABLE_INFO                GetFlashTableInfo;
    GET_FIELD                           GetField;
};

#endif

//**********************************************************************//
//**********************************************************************//
//**                                                                  **//
//**        (C)Copyright 1985-2010, American Megatrends, Inc.         **//
//**                                                                  **//
//**                       All Rights Reserved.                       **//
//**                                                                  **//
//**        5555 Oakbrook Pkwy, Suite 200, Norcross, GA 30093         **//
//**                                                                  **//
//**                       Phone: (770)-246-8600                      **//
//**                                                                  **//
//**********************************************************************//
//**********************************************************************//
