//**********************************************************************
//**********************************************************************
//**                                                                  **
//**        (C)Copyright 1985-2010, American Megatrends, Inc.         **
//**                                                                  **
//**                       All Rights Reserved.                       **
//**                                                                  **
//**             5555 Oakbrook Pkwy   , Norcross, GA 30071            **
//**                                                                  **
//**                       Phone: (770)-246-8600                      **
//**                                                                  **
//**********************************************************************
//**********************************************************************

//**********************************************************************
// $Header: /Alaska/BIN/Core/Include/Protocol/SimpleFileSystem.h 6     1/27/10 1:36p Aaronp $
//
// $Revision: 6 $
//
// $Date: 1/27/10 1:36p $
//**********************************************************************
// Revision History
// ----------------
// $Log: /Alaska/BIN/Core/Include/Protocol/SimpleFileSystem.h $
// 
// 6     1/27/10 1:36p Aaronp
// Updated comments and formatting.
// 
// 5     3/13/06 1:40a Felixp
// 
// 4     3/16/05 3:48p Felixp
// 
// 3     3/16/05 2:46p Felixp
// 
// 2     3/04/05 10:37a Mandal
// 
// 1     1/28/05 12:44p Felixp
// 
// 2     1/18/05 3:22p Felixp
// PrintDebugMessage renamed to Trace
// 
// 1     12/23/04 9:41a Felixp
// 
// 5     7/20/04 7:10p Yakovlevs
// 
// 4     7/20/04 7:06p Yakovlevs
// 
// 3     3/25/04 4:53p Felixp
// 
// 2     3/19/04 12:23a Felixp
// 
// 1     3/19/04 12:17a Felixp
// 
//**********************************************************************
//<AMI_FHDR_START>
//
// Name:	SimpleFileSystem.h
//
// Description:	EFI_SIMPLE_FILE_SYSTEM Protocol Definition
//
//<AMI_FHDR_END>
//**********************************************************************
#ifndef __SIMPLE_FILE_SYSTEM_PROTOCOL_H__
#define __SIMPLE_FILE_SYSTEM_PROTOCOL_H__
#ifdef __cplusplus
extern "C" {
#endif
#include <EFI.h>

#define EFI_SIMPLE_FILE_SYSTEM_PROTOCOL_GUID \
	{ 0x964e5b22,0x6459,0x11d2,0x8e,0x39,0x0,0xa0,0xc9,0x69,0x72,0x3b }

GUID_VARIABLE_DECLARATION(gEfiSimpleFileSystemProtocolGuid, EFI_SIMPLE_FILE_SYSTEM_PROTOCOL_GUID);

#define EFI_FILE_PROTOCOL_REVISION 0x00010000

typedef struct _EFI_FILE_PROTOCOL EFI_FILE_PROTOCOL;

// Open Modes used by the EFI_FILE_OPEN function
#define EFI_FILE_MODE_READ      0x0000000000000001
#define EFI_FILE_MODE_WRITE     0x0000000000000002
#define EFI_FILE_MODE_CREATE    0x8000000000000000

// File Attributes 
#define EFI_FILE_READ_ONLY      0x0000000000000001
#define EFI_FILE_HIDDEN         0x0000000000000002
#define EFI_FILE_SYSTEM         0x0000000000000004
#define EFI_FILE_RESERVED       0x0000000000000008
#define EFI_FILE_DIRECTORY      0x0000000000000010
#define EFI_FILE_ARCHIVE        0x0000000000000020
#define EFI_FILE_VALID_ATTR     0x0000000000000037

// Opens an existing file, or creates a new file, or open a directory
typedef EFI_STATUS (EFIAPI *EFI_FILE_OPEN) (
	IN EFI_FILE_PROTOCOL        *This, 
    OUT EFI_FILE_PROTOCOL       **NewHandle, 
    IN CHAR16                   *FileName,
	IN UINT64                   OpenMode, 
    IN UINT64                   Attributes
);

// Closes a file, or direcotry
typedef EFI_STATUS (EFIAPI *EFI_FILE_CLOSE) ( IN EFI_FILE_PROTOCOL *This );

// Deletes a file, or directory
typedef EFI_STATUS (EFIAPI *EFI_FILE_DELETE) ( IN EFI_FILE_PROTOCOL *This );

// Read out of a file
typedef EFI_STATUS (EFIAPI *EFI_FILE_READ) (
	IN EFI_FILE_PROTOCOL        *This,
    IN OUT UINTN                *BufferSize, 
    OUT VOID                    *Buffer
);

// Writes to a file
typedef EFI_STATUS (EFIAPI *EFI_FILE_WRITE) (
	IN EFI_FILE_PROTOCOL        *This, 
    IN OUT UINTN                *BufferSize, 
    IN VOID                     *Buffer
);

// Returns the current position in a file
typedef EFI_STATUS (EFIAPI *EFI_FILE_GET_POSITION) (
	IN EFI_FILE_PROTOCOL        *This, 
    OUT UINT64                  *Position
);

// Sets the current position in a file
typedef EFI_STATUS (EFIAPI *EFI_FILE_SET_POSITION) (
	IN EFI_FILE_PROTOCOL        *This, 
    IN UINT64                   Position
);

#define EFI_FILE_INFO_ID \
	{ 0x9576e92,0x6d3f,0x11d2,0x8e,0x39,0x0,0xa0,0xc9,0x69,0x72,0x3b }

typedef struct {
	UINT64                      Size;
	UINT64                      FileSize;
	UINT64                      PhysicalSize;
	EFI_TIME                    CreateTime;
	EFI_TIME                    LastAccessTime;
	EFI_TIME                    ModificationTime;
	UINT64                      Attribute;
//TODO//TODO//TODO//TODO//TODO//TODO//TODO//TODO//TODO//TODO
//S.Y.
//GetFileInfo was retunring EFI_BUFFER_TOO_SMALL because of this
//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
//we must take care of this in SimpleFileSystem Driver this is not right definition 
//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	CHAR16 FileName[1];
//TODO//TODO//TODO//TODO//TODO//TODO//TODO//TODO//TODO//TODO
} EFI_FILE_INFO;

// File Attribute Bits returned by 
#define EFI_FILE_READ_ONLY      0x0000000000000001
#define EFI_FILE_HIDDEN         0x0000000000000002
#define EFI_FILE_SYSTEM         0x0000000000000004
#define EFI_FILE_RESERVED       0x0000000000000008
#define EFI_FILE_DIRECTORY      0x0000000000000010
#define EFI_FILE_ARCHIVE        0x0000000000000020
#define EFI_FILE_VALID_ATTR     0x0000000000000037

#define EFI_FILE_SYSTEM_INFO_ID \
	{ 0x9576e93,0x6d3f,0x11d2,0x8e,0x39,0x0,0xa0,0xc9,0x69,0x72,0x3b }

typedef struct {
	UINT64                      Size;
	BOOLEAN                     ReadOnly;
	UINT64                      VolumeSize;
	UINT64                      FreeSpace;
	UINT32                      BlockSize;
	CHAR16                      VolumeLabel[];
} EFI_FILE_SYSTEM_INFO;


#define EFI_FILE_SYSTEM_VOLUME_LABEL_ID \
	{ 0xDB47D7D3,0xFE81,0x11d3,0x9A,0x35,0x00,0x90,0x27,0x3F,0xC1,0x4D }

typedef struct {
	CHAR16 VolumeLabel[];
} EFI_FILE_SYSTEM_VOLUME_LABEL;

// Reads the requested file or direcotry info
typedef EFI_STATUS (EFIAPI *EFI_FILE_GET_INFO) (
	IN EFI_FILE_PROTOCOL        *This, 
    IN EFI_GUID                 *InformationType,
	IN OUT UINTN                *BufferSize, 
    OUT VOID                    *Buffer
);

// Sets the requested file's info
typedef EFI_STATUS (EFIAPI *EFI_FILE_SET_INFO) (
	IN EFI_FILE_PROTOCOL        *This, 
    IN EFI_GUID                 *InformationType,
	IN UINTN                    BufferSize, 
    IN VOID                     *Buffer
);

// Flushes all modified information to the device
typedef EFI_STATUS (EFIAPI *EFI_FILE_FLUSH) ( IN EFI_FILE_PROTOCOL *This );

struct _EFI_FILE_PROTOCOL {
	UINT64                      Revision;
	EFI_FILE_OPEN               Open;
	EFI_FILE_CLOSE              Close;
	EFI_FILE_DELETE             Delete;
	EFI_FILE_READ               Read;
	EFI_FILE_WRITE              Write;
	EFI_FILE_GET_POSITION       GetPosition;
	EFI_FILE_SET_POSITION       SetPosition;
	EFI_FILE_GET_INFO           GetInfo;
	EFI_FILE_SET_INFO           SetInfo;
	EFI_FILE_FLUSH              Flush;
};

#define EFI_SIMPLE_FILE_SYSTEM_PROTOCOL_REVISION 0x00010000

typedef struct _EFI_SIMPLE_FILE_SYSTEM_PROTOCOL EFI_SIMPLE_FILE_SYSTEM_PROTOCOL;

typedef EFI_STATUS (EFIAPI *EFI_VOLUME_OPEN) (
	IN EFI_SIMPLE_FILE_SYSTEM_PROTOCOL *This, 
    OUT EFI_FILE_PROTOCOL       **Root
);

struct _EFI_SIMPLE_FILE_SYSTEM_PROTOCOL {
	UINT64                      Revision;
	EFI_VOLUME_OPEN             OpenVolume;
};

/****** DO NOT WRITE BELOW THIS LINE *******/
#ifdef __cplusplus
}
#endif
#endif
//**********************************************************************
//**                                                                  **
//**        (C)Copyright 1985-2010, American Megatrends, Inc.         **
//**                                                                  **
//**                       All Rights Reserved.                       **
//**                                                                  **
//**             5555 Oakbrook Pkwy   , Norcross, GA 30071            **
//**                                                                  **
//**                       Phone: (770)-246-8600                      **
//**                                                                  **
//**********************************************************************
//**********************************************************************
