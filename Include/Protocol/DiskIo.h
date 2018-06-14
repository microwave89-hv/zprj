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
// $Header: /Alaska/BIN/Core/Include/Protocol/DiskIo.h 4     4/20/07 3:47p Robert $
//
// $Revision: 4 $
//
// $Date: 4/20/07 3:47p $
//**********************************************************************
// Revision History
// ----------------
// $Log: /Alaska/BIN/Core/Include/Protocol/DiskIo.h $
// 
// 4     4/20/07 3:47p Robert
// Updated File header for Coding standard compliance
// 
// 3     3/13/06 1:40a Felixp
// 
// 2     3/04/05 10:34a Mandal
// 
// 1     1/28/05 12:44p Felixp
// 
// 2     1/18/05 3:22p Felixp
// PrintDebugMessage renamed to Trace
// 
// 1     12/23/04 9:41a Felixp
// 
// 1     8/19/04 6:26p Robert
//
// 1     1/26/04 3:25p Markw
//
//**********************************************************************
//<AMI_FHDR_START>
//
// Name: DiskIo.h
//
// Description: Contains Function Prototypes and Data Structures for 
//      the DiskIo Protocol
//
//<AMI_FHDR_END>
//**********************************************************************
#ifndef __DISK_IO_PROTOCOL_H__
#define __DISK_IO_PROTOCOL_H__
#ifdef __cplusplus
extern "C" {
#endif
#include <EFI.h>

#define EFI_DISK_IO_PROTOCOL_GUID \
		{ 0xCE345171, 0xBA0B, 0x11d2, 0x8e, 0x4F, 0x00, 0xa0, 0xc9, 0x69, 0x72, 0x3b }

GUID_VARIABLE_DECLARATION(gEfiDiskIoProtocolGuid, EFI_DISK_IO_PROTOCOL_GUID);

#define EFI_DISK_IO_PROTOCOL_REVISION 0x00010000


typedef	struct _EFI_DISK_IO_PROTOCOL EFI_DISK_IO_PROTOCOL;


//=============================================================================
// Function Prototypes

//=============================================================================
// Function: ReadDisk
//
// Description: rreads the number of bytes specified by BufferSize from the device
//
// Inputs:
//		This - Indicates a pointer to the calling context. 
//		MediaId - ID of the medium to be read.
//		Offset - The starting byte offset on the logical block I/O device to read from.
//		BufferSize - The size in bytes of Buffer. The number of bytes to read from
//			the device.
//
// Outputs: Returns EFI_STATUS
//		Buffer - A pointer to the destination buffer for the data. The caller is responsible
//			for either having implicit or explicit ownership of the buffer.
//
// Notes:
//
//=============================================================================
typedef EFI_STATUS (*EFI_DISK_READ) (
		IN	EFI_DISK_IO_PROTOCOL		*This,
		IN	UINT32			MediaId,
		IN	UINT64			Offset,
		IN	UINTN			BufferSize,
		OUT	VOID			*Buffer
		);



//=============================================================================
// Function: WriteDisk
//
// Description: writes the number of bytes specified by BufferSize to the device
//
// Inputs:
//		This - Indicates a pointer to the calling context. 
//		MediaId - ID of the medium to be read.
//		Offset - The starting byte offset on the logical block I/O device to read from.
//		BufferSize - The size in bytes of Buffer. The number of bytes to read from
//			the device.
//		Buffer - A pointer to the destination buffer for the data. The caller is responsible
//			for either having implicit or explicit ownership of the buffer.
//
// Outputs: Returns EFI_STATUS
//
// Notes:
//
//=============================================================================
typedef EFI_STATUS (*EFI_DISK_WRITE) (
		IN	EFI_DISK_IO_PROTOCOL		*This,
		IN	UINT32			MediaId,
		IN	UINT64			Offset,
		IN	UINTN			BufferSize,
		IN	VOID			*Buffer
		);



//=============================================================================
// Protocol Definition
typedef struct _EFI_DISK_IO_PROTOCOL {
		UINT64				Revision;
		EFI_DISK_READ		ReadDisk;
		EFI_DISK_WRITE		WriteDisk;
		} EFI_DISK_IO_PROTOCOL;


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
