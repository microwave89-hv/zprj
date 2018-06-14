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
// $Header: /Alaska/SOURCE/Core/CORE_DXE/Partition/Gpt.h 6     7/09/09 5:01p Oleksiyy $
//
// $Revision: 6 $
//
// $Date: 7/09/09 5:01p $
//**********************************************************************
// Revision History
// ----------------
// $Log: /Alaska/SOURCE/Core/CORE_DXE/Partition/Gpt.h $
// 
// 6     7/09/09 5:01p Oleksiyy
// Files clean-up
//
// 5     1/08/08 4:37p Robert
//
// 4     1/08/08 4:00p Robert
//
// 3     1/07/08 4:21p Robert
// Updated for coding standard
//
// 2     4/24/07 6:06p Robert
// Update for CHM compliance
//
// 1     1/28/05 1:17p Felixp
//
// 2     1/18/05 3:22p Felixp
// PrintDebugMessage renamed to Trace
//
// 1     12/22/04 6:19p Admin
//
// 1     12/22/04 6:18p Admin
//
// 2     12/02/04 5:54p Robert
// Partition driver version works
//
//**********************************************************************
//<AMI_FHDR_START>
//
// Name:    <GPT.h>
//
// Description: EFI GPT Partition Generic Driver Header.
//
//<AMI_FHDR_END>
//**********************************************************************

#ifndef _GPT_H_
#define _GPT_H_

#pragma pack(1)

#define EFI_GPT_HEADER_ID  "EFI PART"

// GUID Partition Table Header
//<AMI_STHDR_START>
//============================================================================
// Structure:   GPT_HEADER
//
// Description: Data Structure definition of the GPT table
//
// Fields:
//      Header - EFI_TABLE_HEADER - defines generic EFI header information
//      MyLba - EFI_LBA - The LBA that contains this GPT data structure
//      AlternateLba - EFI_LBA - The LBA that contains the alternative GPT
//          data structure
//      FirstUsableLba - EFI_LBA - the first logical block that can be used
//          in a partition that is defined by the GPT
//      LastUsableLba - EFI_LBA - the last logical block that can be used
//          in a partition that is defined by the GPT
//      DiskGuid - EFI_GUID - Unique GUID to identify this hard drive
//      PartitionEntryLba - EFI_LBA - the starting LBA of the GUID Partition
//          Entry Array
//      NumberOfPartitionEntries - UINT32 - the number of partition entries
//          in the Array
//      SizeOfPartitionEntry - UINT32 - the size of each partition entry
//      Crc32 - UINT32 - crc value of the entire GPT block
//
// Referral:
//      EFI_TABLE_HEADER EFI_LBA EFI_GUID
//============================================================================
//<AMI_STHDR_END>
typedef struct
{
    EFI_TABLE_HEADER    Header;
    EFI_LBA             MyLba;
    EFI_LBA             AlternateLba;
    EFI_LBA             FirstUsableLba;
    EFI_LBA             LastUsableLba;
    EFI_GUID            DiskGuid;
    EFI_LBA             PartitionEntryLba;
    UINT32              NumberOfPartitionEntries;
    UINT32              SizeOfPartitionEntry;
    UINT32              Crc32;
} GPT_HEADER;

// GPT Partition Entry
//<AMI_STHDR_START>
//============================================================================
// Structure:   PARTITION_ENTRY
//
// Description: Data Structure definition of a partion entry in the GPT table
//
// Fields:
//      PartitionTypeGuid - EFI_GUID - contains GUID that defines that type
//          of GUID
//      UniquePartitionGuid - EFI_GUID - contains unique GUID for each
//          partition
//      StartingLba - EFI_LBA - first LBA of the partition
//      EndingLba - EFI_LBA - last logical block address
//      Attributes - UINT64 - UEFI defined attributes
//          Bit 0 - Partition is required for platform to function
//          Bits 1 - 47 - undefined
//          Bits 48 - 64 - reserved for GUID specific use
//      PartitionName[36] - CHAR16 - unicode string containing the name of
//          the partition
//
// Referral:
//      EFI_LBA
//============================================================================
//<AMI_STHDR_END>
typedef struct
{
    EFI_GUID    PartitionTypeGuid;
    EFI_GUID    UniquePartitionGuid;
    EFI_LBA     StartingLba;
    EFI_LBA     EndingLba;
    UINT64      Attributes;
    CHAR16      PartitionName[36];
} PARTITION_ENTRY;


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
