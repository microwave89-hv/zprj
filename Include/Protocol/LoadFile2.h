//**********************************************************************
//**********************************************************************
//**                                                                  **
//**        (C)Copyright 1985-2009, American Megatrends, Inc.         **
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
// $Header: /Alaska/BIN/Core/Include/Protocol/LoadFile2.h 2     4/19/11 10:53a Yakovlevs $
//
// $Revision: 2 $
//
// $Date: 4/19/11 10:53a $
//**********************************************************************
// Revision History
// ----------------
// $Log: /Alaska/BIN/Core/Include/Protocol/LoadFile2.h $
// 
// 2     4/19/11 10:53a Yakovlevs
// [TAG]  		EIP 57664
// [Category]  	New Feature
// [Description]  	Aptio PI 1.2; UEFI 2.3.1 Support Extended PCI bus
// driver functionality
// [Files]  		DevicePath.h; LoadFile2.h; PciBus.h; PciBus.c.
// 
// 1     11/19/09 12:53p Felixp
// 
//**********************************************************************
//<AMI_FHDR_START>
//
// Name:  LoadFile2.h
//
// Description:	Load File 2 Protocol Definition
//
//<AMI_FHDR_END>
//**********************************************************************
#ifndef __LOAD_FILE2_PROTOCOL_H__
#define __LOAD_FILE2_PROTOCOL_H__
#ifdef __cplusplus
extern "C" {
#endif
#include <EFI.h>

#define EFI_LOAD_FILE2_PROTOCOL_GUID \
	{0x4006c0c1,0xfcb3,0x403e,0x99, 0x6d, 0x4a, 0x6c, 0x87, 0x24, 0xe0, 0x6d}

GUID_VARIABLE_DECLARATION(gEfiLoadFile2ProtocolGuid, EFI_LOAD_FILE2_PROTOCOL_GUID);

typedef struct _EFI_LOAD_FILE2_PROTOCOL EFI_LOAD_FILE2_PROTOCOL;

typedef EFI_STATUS (EFIAPI *EFI_LOAD_FILE2) (
	IN EFI_LOAD_FILE2_PROTOCOL  *This, 
    IN EFI_DEVICE_PATH_PROTOCOL *FilePath,
	IN BOOLEAN                  BootPolicy, 
    IN OUT UINTN                *BufferSize,
	IN VOID                     *Buffer OPTIONAL
);

struct _EFI_LOAD_FILE2_PROTOCOL{
	EFI_LOAD_FILE2 LoadFile;
};
/****** DO NOT WRITE BELOW THIS LINE *******/
#ifdef __cplusplus
}
#endif
#endif
//**********************************************************************
//**********************************************************************
//**                                                                  **
//**        (C)Copyright 1985-2009, American Megatrends, Inc.         **
//**                                                                  **
//**                       All Rights Reserved.                       **
//**                                                                  **
//**      5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093        **
//**                                                                  **
//**                       Phone: (770)-246-8600                      **
//**                                                                  **
//**********************************************************************
//**********************************************************************
