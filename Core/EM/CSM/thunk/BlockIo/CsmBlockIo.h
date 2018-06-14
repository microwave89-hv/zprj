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
// $Header: /Alaska/SOURCE/Modules/CSM/Generic/Thunk/INT13/CsmBlockIo.h 10    12/23/11 2:12p Olegi $
//
// $Revision: 10 $
//
// $Date: 12/23/11 2:12p $
//**********************************************************************
// Revision History
// ----------------
// $Log: /Alaska/SOURCE/Modules/CSM/Generic/Thunk/INT13/CsmBlockIo.h $
// 
// 10    12/23/11 2:12p Olegi
// [TAG]  		EIP78921
// [Category]  	Improvement
// [Description]  	CsmBlockIo should create device handle in BBS table
// [Files]  		CsmBlockIo.c
// CsmBlockIo.h
// 
// 9     6/27/11 4:50p Olegi
// 
// 8     1/12/10 11:50a Olegi
// Copyright message updated.
// 
// 7     9/23/09 11:18a Olegi
// 
// 6     8/07/09 2:46p Rameshr
// SD boot support Added.
// 
// 5     10/03/07 4:42p Yakovlevs
// Removed Component Name Protocol and its Strings in NO DEBUG mode to
// save some space. 
// 
// 4     4/27/07 5:14p Olegi
// CSM.CHM file preparation.
// 
// 3     3/13/06 2:38p Felixp
// 
// 2     3/04/05 1:45p Mandal
// 
// 1     2/15/05 11:00a Olegi
// Initial VSS check-in.
// 
//**********************************************************************
//<AMI_FHDR_START>
//
// Name:            CsmBlockIo.h
//
// Description:     CSM BlockIO driver header file.
//
//<AMI_FHDR_END>
//**********************************************************************

#ifndef _CsmBlockIo_
#define _CsmBlockIo_

#ifdef __cplusplus
extern "C" {
#endif

#include <Efi.h>
#include <Token.h>
#include <Dxe.h>
#include <PCI.h>
#include <AmiDxeLib.h>
#include <Protocol\PciIo.h>
#include <Protocol\DevicePath.h>
#include <Protocol\LegacyBios.h>
#include <Protocol\LegacyBiosExt.h>
#include <protocol\DriverBinding.h>
#include <Protocol\ComponentName.h>
#include <protocol\BlockIo.h>

#include "CsmEdd.h"


// Global Variables
#if EFI_DEBUG
extern EFI_COMPONENT_NAME_PROTOCOL gBiosBlockIoComponentName;
#endif


// Define the I2O class code

#define PCI_BASE_CLASS_INTELLIGENT      0x0e
#define PCI_SUB_CLASS_INTELLIGENT       0x00

// SD class/subclass defined in PCI.H in 4.6.3.7
#ifndef PCI_CL_SYSTEM_PERIPHERALS
#define PCI_CL_SYSTEM_PERIPHERALS		0x08
#endif
#ifndef PCI_CL_SYSTEM_PERIPHERALS_SCL_SD
#define PCI_CL_SYSTEM_PERIPHERALS_SCL_SD	0x05
#endif


// Number of pages needed for our buffer under 1MB

#define BLOCK_IO_BUFFER_PAGE_SIZE (((sizeof (EDD_DEVICE_ADDRESS_PACKET) + sizeof (CSM_LEGACY_DRIVE) + MAX_EDD11_XFER) / EFI_PAGE_SIZE) + 1)


// PROTOTYPES

// Driver Binding Protocol functions

EFI_STATUS
CsmBlockIoSupported (
  IN EFI_DRIVER_BINDING_PROTOCOL  *This,
  IN EFI_HANDLE                   Controller,
  IN EFI_DEVICE_PATH_PROTOCOL     *RemainingDevicePath
  );

EFI_STATUS
CsmBlockIoStart (
  IN EFI_DRIVER_BINDING_PROTOCOL  *This,
  IN EFI_HANDLE                   Controller,
  IN EFI_DEVICE_PATH_PROTOCOL     *RemainingDevicePath
  );

EFI_STATUS
CsmBlockIoStop (
  IN  EFI_DRIVER_BINDING_PROTOCOL  *This,
  IN  EFI_HANDLE                   Controller,
  IN  UINTN                        NumberOfChildren,
  IN  EFI_HANDLE                   *ChildHandleBuffer
  );
  
// Block I/O functions

EFI_STATUS 
CsmBlockIoFlushBlocks (
    IN  EFI_BLOCK_IO_PROTOCOL           *This
    );

EFI_STATUS 
CsmBlockIoReset (
    IN  EFI_BLOCK_IO_PROTOCOL           *This,
    IN  BOOLEAN                ExtendedVerification
    );

// These prototypes aren't actually used -- they are the generic for the specific
// functions below
EFI_STATUS
CsmBlockIoReadBlocks (
    IN  EFI_BLOCK_IO_PROTOCOL          *This,
    IN  UINT32                MediaId,
    IN  EFI_LBA               LBA,
    IN  UINTN                 BufferSize,
    OUT VOID                  *Buffer
    );

EFI_STATUS
CsmBlockIoWriteBlocks (
    IN  EFI_BLOCK_IO_PROTOCOL           *This,
    IN  UINT32                 MediaId,
    IN  EFI_LBA                LBA,
    IN  UINTN                  BufferSize,
    OUT VOID                   *Buffer
    );

// Specific read/write function prototypes
EFI_STATUS
Edd30CsmReadBlocks (
    IN  EFI_BLOCK_IO_PROTOCOL          *This, 
    IN  UINT32                MediaId, 
    IN  EFI_LBA               LBA, 
    IN  UINTN                 BufferSize, 
    OUT VOID                  *Buffer
    );

EFI_STATUS
Edd30CsmWriteBlocks (
    IN  EFI_BLOCK_IO_PROTOCOL          *This,
    IN  UINT32                MediaId,
    IN  EFI_LBA               LBA,
    IN  UINTN                 BufferSize,
    OUT VOID                  *Buffer
    );

EFI_STATUS
Edd11CsmReadBlocks (
    IN  EFI_BLOCK_IO_PROTOCOL          *This,
    IN  UINT32                MediaId,
    IN  EFI_LBA               LBA,
    IN  UINTN                 BufferSize,
    OUT VOID                  *Buffer
    );

EFI_STATUS
Edd11CsmWriteBlocks (
    IN  EFI_BLOCK_IO_PROTOCOL          *This,
    IN  UINT32                MediaId,
    IN  EFI_LBA               LBA,
    IN  UINTN                 BufferSize,
    OUT VOID                  *Buffer
    );

EFI_STATUS
LegacyCsmReadBlocks (
    IN  EFI_BLOCK_IO_PROTOCOL          *This,
    IN  UINT32                MediaId,
    IN  EFI_LBA               LBA,
    IN  UINTN                 BufferSize,
    OUT VOID                  *Buffer
    );

EFI_STATUS
LegacyCsmWriteBlocks (
    IN  EFI_BLOCK_IO_PROTOCOL          *This,
    IN  UINT32                MediaId,
    IN  EFI_LBA               LBA,
    IN  UINTN                 BufferSize,
    OUT VOID                  *Buffer
    );

// Local support function prototypes
BOOLEAN
InitBlockIo (
    IN  CSM_BLOCK_IO_DEV        *Dev
    );

// Local function prototypes
VOID
BuildDevicePath (
    IN  EFI_DEVICE_PATH_PROTOCOL  *BaseDevicePath,
    IN  CSM_LEGACY_DRIVE          *Drive,
    IN  EFI_DEVICE_PATH_PROTOCOL  **DevPath
    );

EFI_DEVICE_PATH_PROTOCOL *
AppendDevicePathNode (
    IN EFI_DEVICE_PATH_PROTOCOL  *DevPath,
    IN EFI_DEVICE_PATH_PROTOCOL  *Node
    );

UINTN AlignAddress (
    UINTN                       Address
    );

VOID ZeroMemory (
    VOID                        *Buffer,
    UINTN                       Size
);

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
