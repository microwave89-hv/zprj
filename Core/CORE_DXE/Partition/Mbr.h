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
// $Header: /Alaska/SOURCE/Core/CORE_DXE/Partition/Mbr.h 7     7/09/09 5:01p Oleksiyy $
//
// $Revision: 7 $
//
// $Date: 7/09/09 5:01p $
//**********************************************************************
// Revision History
// ----------------
// $Log: /Alaska/SOURCE/Core/CORE_DXE/Partition/Mbr.h $
// 
// 7     7/09/09 5:01p Oleksiyy
// Files clean-up
//
// 6     1/08/08 3:10p Robert
//
// 5     1/08/08 3:08p Robert
//
// 4     1/07/08 4:21p Robert
// Updated for coding standard
//
// 3     4/25/07 11:53a Robert
// Updated for CHM and Coding Standard Compliance
//
// 2     4/24/05 12:45a Felixp
// Definitions of SIGNATURE_TYPE_xxx macroses removed since they are
// already defined in DevicePath.h
//
//**********************************************************************
//<AMI_FHDR_START>
//
// Name:    <Mbr.h>
//
// Description: EFI Mbr Partition Generic Driver Header. This header
//      contains Data structures and Definitions needed to recognize
//      partitions in an MBR
//
//<AMI_FHDR_END>
//**********************************************************************
#ifndef _MBR_H
#define _MBR_H

#define MBR_SIGNATURE               0xaa55
#define NUM_MBR_PARTITIONS          4

// Type definitions for the Hard drive device path
#define MBR_TYPE_MASTER_BOOT_RECORD 0x01
#define MBR_TYPE_EFI_PARTITION_TABLE_HEADER     0x02

// Needed Partition Type definitions for MBR
#define NO_PARTITION                0x0
#define EXTENDED_PARTITION          0x05
#define WIN95_EXTENDED_PARTITION    0x0f


//<AMI_GHDR_START>
//------------------------------------------------------------------
// Name: Data_Structures
//
// Description:
//      Data Structures needed for MBR
//
//      MASTER_BOOT_RECORD - Data Structure definition of the
//          MBR located in the first block on an MBR drive
//
//      MBR_PARTITION - Data Structure definition for each
//          partition in the MBR
//
//------------------------------------------------------------------
//<AMI_GHDR_END>

#pragma pack(1)

//<AMI_STHDR_START>
//============================================================================
// Structure:   MBR_PARTITION
//
// Description: Data Structure that defines a partition within the MBR
//
// Fields:
//      BootIndicator - UINT8 - indicates whether this partition is bootable
//      StartHead - UINT8 - unused in EFI
//      StartSector - UINT8 - unused in EFI
//      StartTrack - UINT8 - unused in EFI
//      OSType - UINT8 - defines type of the partition
//      EndHead - UINT8 - unused in EFI
//      EndSector - UINT8 - unused in EFI
//      EndTrack - UINT8 - unused in EFI
//      StartingLba - UINT32 - LBA where the partiton starts on the hard drive
//      SizeInLba - UINT32 - LBA where the partiton ends on the hard drive
//
// Referral:
//      None
//============================================================================
//<AMI_STHDR_END>
typedef struct _MBR_PARTITION
{
    UINT8       BootIndicator;
    UINT8       StartHead;
    UINT8       StartSector;
    UINT8       StartTrack;
    UINT8       OSType;
    UINT8       EndHead;
    UINT8       EndSector;
    UINT8       EndTrack;
    UINT32      StartingLba;
    UINT32      SizeInLba;
} MBR_PARTITION;


// MBR Partition table
//============================================================================
// Structure:   MASTER_BOOT_RECORD
//
// Description: Data Structure that mimicks the structure of a Master Boot
//      Record on a hard drive
//
// Fields:
//      BootCode[440] - UINT8 - executable code in the first 440 bytes of a
//          hard drive
//      UniqueMbrSig - UINT32 - Uniques signature associated with the hard
//          drive
//      Unknown - UINT16 - an unknown portion of the data structure
//      PartRec[4] - MBR_PARTITION - an array of partition entries that
//          define the partitions that exist on the hard drive
//      Sig - UINT16 - 0xaa55 - value that indicates this is an MBR
//
// Referral:
//      MBR_PARTITION
//============================================================================
//<AMI_STHDR_END>
typedef struct _MASTER_BOOT_RECORD
{
    UINT8                   BootCode[440];
    UINT32                  UniqueMbrSig;
    UINT16                  Unknown;
    MBR_PARTITION           PartRec[4];
    UINT16                  Sig;
} MASTER_BOOT_RECORD;


#pragma pack()
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
