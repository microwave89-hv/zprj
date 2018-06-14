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
// $Header: /Alaska/SOURCE/Core/CORE_DXE/Partition/Partition.h 10    8/12/11 12:16p Artems $
//
// $Revision: 10 $
//
// $Date: 8/12/11 12:16p $
//**********************************************************************
// Revision History
// ----------------
// $Log: /Alaska/SOURCE/Core/CORE_DXE/Partition/Partition.h $
// 
// 10    8/12/11 12:16p Artems
// EIP 64107: Added changes for module to be compliant with UEFI
// specification v 2.3.1
// 
// 9     7/09/09 5:01p Oleksiyy
// Files clean-up
//
// 8     1/08/08 2:47p Robert
//
// 7     1/08/08 2:47p Robert
//
// 6     1/07/08 4:21p Robert
// Updated for coding standard
//
// 5     4/25/07 12:44p Robert
// updates for CHM and Coding Standard Compliance
//
// 3     4/24/05 12:45a Felixp
// Definitions of SIGNATURE_TYPE_xxx macroses removed since they are
// already defined in DevicePath.h
//
// 6     12/14/04 6:14p Robert
// Added component name protocol support
//
//**********************************************************************
//<AMI_FHDR_START>
//
// Name:    Partition.h
//
// Description: EFI Partition Generic Driver Header.  This file
//      contains the GUIDs used by this driver.  It also contains
//      Definitions and Data Structures needed by the generic portion of
//      the Partition driver.
//
//
//<AMI_FHDR_END>
//**********************************************************************

#ifndef _PARTITION_H
#define _PARTITION_H


#include <AmiDxeLib.h>

// protocols consumed
#include <protocol\BlockIo.h>
#include <protocol\DiskIo.h>
#include <protocol\DevicePath.h>
#include <protocol\DriverBinding.h>
#include <Protocol\ComponentName2.h>

extern EFI_BOOT_SERVICES    *gBS;
extern EFI_GUID             gUnusedPartitionGuid;

//=============================================================================
// GUID Definitions

#define EFI_PART_TYPE_UNUSED_GUID   \
  { 0x00000000, 0x0000, 0x0000, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}

#define EFI_PART_TYPE_EFI_SYSTEM_PART_GUID  \
  { 0xc12a7328, 0xf81f, 0x11d2, 0xba, 0x4b, 0x00, 0xa0, 0xc9, 0x3e, 0xc9, 0x3b}

#define EFI_PART_TYPE_LEGACY_MBR_GUID   \
  { 0x024dee41, 0x33e7, 0x11d3, 0x9d, 0x69, 0x00, 0x08, 0xc7, 0x81, 0xf3, 0x9f}



#define MBR_TYPE_PCAT                           0x01
#define MBR_TYPE_EFI_PARTITION_TABLE_HEADER     0x02

#define     EFI_SYSTEM_PARTITION        0xef


//=============================================================================
// Structure definitions

//<AMI_STHDR_START>
//============================================================================
// Structure:   OPCODE_CMD
//
// Description: Data Structure definition of the Private data for each instance
//      of the Partition Block I/O driver
//
// Fields:
//      BlockIo - EFI_BLOCK_IO_PROTOCOL - Pointer to the EFI_BLOCK_IO_PROTOCOL
//          protocol for this partition
//      Handle - EFI_HANDLE - child handle for this partition
//      ParentBlockIo - EFI_BLOCK_IO_PROTOCOL * - pointer to the
//          EFI_BLOCK_IO_PROTOCOL of the parent device
//      ParentDiskIo - EFI_DISK_IO_PROTOCOL * - pointer to the
//          EFI_DISK_IO_PROTOCOL of the parent device
//      DevPath - EFI_DEVICE_PATH_PROTOCOL * - pointer to the device path
//          for this device
//      StartingLba - EFI_LBA - The starting Lba of the current partition
//      EndingLba - EFI_LBA - The ending Lba of the current partition
//      PartGuid - EFI_GUID - The GUID assigned to the partition
//      ParentHandle - EFI_HANDLE - the handle assigned to the parent device
//
// Referral:
//      None
//============================================================================
//<AMI_STHDR_END>
typedef struct _PARTITION_DATA
{
    EFI_BLOCK_IO_PROTOCOL       BlockIo;
    EFI_HANDLE                  Handle;
    EFI_BLOCK_IO_PROTOCOL       *ParentBlockIo;
    EFI_DISK_IO_PROTOCOL        *ParentDiskIo;
    EFI_DEVICE_PATH_PROTOCOL    *DevPath;
    
    EFI_LBA                     StartingLba;
    EFI_LBA                     EndingLba;
    EFI_GUID                    PartGuid;
    
    EFI_HANDLE                  ParentHandle;
} PARTITION_DATA;


//=============================================================================
// Function Prototypes
EFI_STATUS CreateChildHandle(EFI_DRIVER_BINDING_PROTOCOL *This, PARTITION_DATA *PData,
                             UINT32 BlockSize);

EFI_STATUS GptDiscoverPartitions (
    IN EFI_DRIVER_BINDING_PROTOCOL  *This,
    IN  EFI_BLOCK_IO_PROTOCOL       *BlockIo,
    IN  EFI_DISK_IO_PROTOCOL            *DiskIo,
    IN  EFI_DEVICE_PATH_PROTOCOL        *DevicePath,
    IN  EFI_HANDLE          ControllerHandle
);

EFI_STATUS  ElToritoCreateChildHandle (
    IN EFI_DRIVER_BINDING_PROTOCOL  *This,
    IN  EFI_BLOCK_IO_PROTOCOL       *BlockIo,
    IN  EFI_DISK_IO_PROTOCOL            *DiskIo,
    IN  EFI_DEVICE_PATH_PROTOCOL        *DevicePath,
    IN  EFI_HANDLE          ControllerHandle
);

EFI_STATUS MbrCreateChildHandle(
    IN EFI_DRIVER_BINDING_PROTOCOL  *This,
    IN EFI_BLOCK_IO_PROTOCOL        *BlockIo,
    IN  EFI_DISK_IO_PROTOCOL        *DiskIo,
    IN  EFI_DEVICE_PATH_PROTOCOL    *DevicePath,
    IN  EFI_HANDLE          ControllerHandle
);

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
