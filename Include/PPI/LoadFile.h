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

//**********************************************************************
// $Header: /Alaska/BIN/Core/Include/PPI/LoadFile.h 7     6/16/11 3:18p Felixp $
//
// $Revision: 7 $
//
// $Date: 6/16/11 3:18p $
//**********************************************************************
// Revision History
// ----------------
// $Log: /Alaska/BIN/Core/Include/PPI/LoadFile.h $
// 
// 7     6/16/11 3:18p Felixp
// Surround backward compatibility definitions with #if
// BACKWARD_COMPATIBLE_MODE
// 
// 6     5/27/11 5:52p Felixp
// Headers are updated to improve separation of the Framework and PI
// interfaces.
// The definitions that will be removed in the future versions are marked
// with the comments.
// 
// 5     2/05/11 2:10p Artems
// Added PI 1.0 support
// 
// 4     3/13/06 1:16a Felixp
// 
// 3     3/24/05 11:45a Felixp
// 
// 2     3/04/05 10:26a Mandal
// 
// 1     1/28/05 12:44p Felixp
// 
// 2     1/18/05 3:21p Felixp
// PrintDebugMessage renamed to Trace
// 
// 1     12/23/04 9:41a Felixp
// 
// 1     10/14/04 12:06p Felixp
// 
//**********************************************************************
//<AMI_FHDR_START>
//
// Name:	LoadFile.h
//
// Description:	EFI_PEI_FV_FILE_LOADER_PPI PPI definition
//
//<AMI_FHDR_END>
//**********************************************************************
#ifndef __LoadFile__H__
#define __LoadFile__H__
#ifdef __cplusplus
extern "C" {
#endif

#include <PEI.h>

#if PI_SPECIFICATION_VERSION >= 0x00010000
#define EFI_PEI_LOAD_FILE_PPI_GUID \
  { 0xb9e0abfe, 0x5979, 0x4914, 0x97, 0x7f, 0x6d, 0xee, 0x78, 0xc2, 0x78, 0xa6 }
#if BACKWARD_COMPATIBLE_MODE
#define EFI_PEI_FV_FILE_LOADER_GUID EFI_PEI_LOAD_FILE_PPI_GUID
#endif
#else
#define EFI_PEI_FV_FILE_LOADER_GUID \
    { 0x7e1f0d85, 0x4ff, 0x4bb2, 0x86, 0x6a, 0x31, 0xa2, 0x99, 0x6a, 0x48, 0xa8 }
GUID_VARIABLE_DECLARATION(gPeiFvFileLoaderPpiGuid, EFI_PEI_FV_FILE_LOADER_GUID);
#define EFI_PEI_LOAD_FILE_PPI_GUID EFI_PEI_FV_FILE_LOADER_GUID
#endif //#if PI_SPECIFICATION_VERSION >= 0x00010000

GUID_VARIABLE_DECLARATION(gEfiPeiLoadFilePpiGuid, EFI_PEI_LOAD_FILE_PPI_GUID);

#if PI_SPECIFICATION_VERSION >= 0x00010000
typedef struct _EFI_PEI_LOAD_FILE_PPI EFI_PEI_LOAD_FILE_PPI;

typedef EFI_STATUS (EFIAPI *EFI_PEI_LOAD_FILE)(
  IN  CONST  EFI_PEI_LOAD_FILE_PPI   *This,
  IN  EFI_PEI_FILE_HANDLE            FileHandle,
  OUT EFI_PHYSICAL_ADDRESS           *ImageAddress,
  OUT UINT64                         *ImageSize,
  OUT EFI_PHYSICAL_ADDRESS           *EntryPoint,
  OUT UINT32                         *AuthenticationState
);

struct _EFI_PEI_LOAD_FILE_PPI {
  EFI_PEI_LOAD_FILE LoadFile;
};

#else //#if PI_SPECIFICATION_VERSION >= 0x00010000

typedef struct _EFI_PEI_FV_FILE_LOADER_PPI EFI_PEI_FV_FILE_LOADER_PPI;

typedef EFI_STATUS (EFIAPI *EFI_PEI_FV_LOAD_FILE) (
	IN EFI_PEI_FV_FILE_LOADER_PPI *This,
	IN EFI_FFS_FILE_HEADER *FfsHeader,
	OUT EFI_PHYSICAL_ADDRESS *ImageAddress,
	OUT UINT64 *ImageSize,
	OUT EFI_PHYSICAL_ADDRESS *EntryPoint
);

struct _EFI_PEI_FV_FILE_LOADER_PPI {
	EFI_PEI_FV_LOAD_FILE FvLoadFile;
};
#endif //#if PI_SPECIFICATION_VERSION >= 0x00010000

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