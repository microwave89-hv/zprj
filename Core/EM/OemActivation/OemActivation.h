//****************************************************************************
//****************************************************************************
//**                                                                        **
//**             (C)Copyright 1985-2011, American Megatrends, Inc.          **
//**                                                                        **
//**                          All Rights Reserved.                          **
//**                                                                        **
//**             5555 Oakbrook Pkwy, Suite 200, Norcross, GA 30093          **
//**                                                                        **
//**                          Phone (770)-246-8600                          **
//**                                                                        **
//****************************************************************************
//****************************************************************************

//*****************************************************************************
// $Header: /Alaska/SOURCE/Modules/OemActivation/OemActivation.h 13    5/22/12 4:28p Vyacheslava $
//
// $Revision: 13 $
//
// $Date: 5/22/12 4:28p $
//*****************************************************************************
// Revision History
// ----------------
// $Log: /Alaska/SOURCE/Modules/OemActivation/OemActivation.h $
// 
// 13    5/22/12 4:28p Vyacheslava
// Added AMI_GLOBAL_VARIABLE_GUID definition.
// 
// 12    1/12/12 9:22a Vyacheslava
// The SW_SMI_OA3_FUNCTION_NUMBER token removed to SDL file.
// 
// 11    9/29/11 4:18p Vyacheslava
// [TAG]  		EIP70134
// [Description]  	Changed definition of the SW_SMI_OA3_FUNCTION_NUMBER to
// 0xDF.
// 
// 10    8/08/11 10:14a Vyacheslava
// 
// 9     6/16/11 10:56a Vyacheslava
// [TAG]  		EIP62009
// [Category]  	New Feature
// [Description]  	Preserve the OA30 key during the BIOS recovery path. 
// 
// 8     6/10/11 10:57a Vyacheslava
// 
// 7     5/26/11 11:10a Vyacheslava
// 
// 6     5/20/11 12:35p Vyacheslava
// [TAG]  		EIP59717
// [Category]  	New Feature
// [Description]  	added structure for updating ACPI. 
// 
// 5     5/18/11 11:34a Vyacheslava
// [TAG]  		EIP59717
// [Category]  	New Feature
// [Description]  	Implementation according comment#8 in the EIP#59717.
// 
// 4     12/17/10 1:45p Vyacheslava
// [TAG]  		EIP48520 
// [Category]  	Improvement
// [Description]  	 - Deleted temporary structure for testing FID;
//  - Simplified MSDM structure;
// 
// 3     12/16/10 5:03p Vyacheslava
// Added definition for FID table version
// 
// 2     11/19/10 4:19p Vyacheslava
// [TAG]  		EIP48520 
// [Category]  	Improvement
// [Description]  	EIP#48520 comment#2
// 
// 1     11/18/10 1:15p Vyacheslava
// Initial creation
// 
//
//*****************************************************************************
//<AMI_FHDR_START>
//
// Name: OemActivation.h
//
// Description: Header file for OEM Activation eModule.
//
//<AMI_FHDR_END>
//*****************************************************************************

#ifndef __MS_OEM_ACTIVATION_H
#define __MS_OEM_ACTIVATION_H

//----------------------------------------------------------------------------

#include <EFI.h>
#include <ACPI.h>

//----------------------------------------------------------------------------

#define MSDM_SIG                0x4D44534D  // "MSDM" - M$ Digital Marker
#define MSDM_REVISION           0x03        // 
#define MSDM_VERSION            0x01        // 
#define MSDM_DATA_TYPE          0x01        // 
#define FID_SUPPORTED_VERSION   0x04        // Supported version of the FID table

#define FID_TABLE_GUID \
  { 0x3fd1d3a2, 0x99f7, 0x420b, 0xbc, 0x69, 0x8b, 0xb1, 0xd4, 0x92, 0xa3, 0x32 }

#define FID_TABLE_SECTION_GUID \
  { 0x2ebe0275, 0x6458, 0x4af9, 0x91, 0xed, 0xd3, 0xf4, 0xed, 0xb1, 0x00, 0xaa }

// This GUID should be defined in the next Core label (4.6.5.4 or greater)
#ifndef AMI_GLOBAL_VARIABLE_GUID
#define AMI_GLOBAL_VARIABLE_GUID \
 {0x1368881,0xc4ad,0x4b1d,0xb6,0x31,0xd5,0x7a,0x8e,0xc8,0xdb,0x6b}
#endif

#define EFI_OA3_MSDM_VARIABLE       L"OA3MSDMvariable"

// if Product Key located in the NBC
#if OEM_ACTIVATION_TABLE_LOCATION == 1
#define FLASH_DEVICE_BASE_ADDRESS       (0xFFFFFFFF-FLASH_SIZE+1)
#define OEM_ACTIVATION_BLOCK_ADDRESS    (OEM_ACTIVATION_TABLE_ADDRESS-FLASH_DEVICE_BASE_ADDRESS)
#define OEM_ACTIVATION_BLOCK_END        (OEM_ACTIVATION_BLOCK_ADDRESS+OEM_ACTIVATION_TABLE_SIZE)
#define OEM_ACTIVATION_TABLE_OFFSET     (0xFFFFFFFF-OEM_ACTIVATION_TABLE_ADDRESS+1)
#endif

#ifndef FV_BB_END_ADDR
#define FV_BB_END_ADDR                  (0xFFFFFFFF-16-sizeof(EFI_GUID)+1)
#endif

#ifndef FV_BB_SIZE
#define FV_BB_SIZE                      (0xFFFFFFFF-FV_BB_BASE+1)
#endif

//----------------------------------------------------------------------------

#pragma pack (1)

//<AMI_SHDR_START>
//----------------------------------------------------------------------------
//
// Name: MSDM_STRUCTURE
//
// Description: This structure comes out of the document "M$ Digital Marker Pilot"
//
// Fields:   
//  Name            Length      Description
//  ------------------------------------------------------------------
//  Header          -           Standard ACPI header
//  Version         4           0x1
//  Reserved        4           0x0
//  DataType        4           0x1
//  DataReserved    4           0x0
//  DataLength      4           0x1D
//  Data            29          5x5 Product Key, including "-" (BH3RN-B7FDM-C7WGT-4CR4X-6CKHM) 
//
//----------------------------------------------------------------------------
//<AMI_SHDR_END>

typedef struct _EFI_ACPI_MSDM_TABLE {
    ACPI_HDR    Header;
    UINT32      Version;
    UINT32      Reserved;
    UINT32      DataType;
    UINT32      DataReserved;
    UINT32      DataLength;
    UINT8       Data[29];
} EFI_ACPI_MSDM_TABLE;


typedef struct _EFI_OA3_MSDM_STRUCTURE {
    EFI_PHYSICAL_ADDRESS  XsdtAddress;
    EFI_PHYSICAL_ADDRESS  MsdmAddress;
    EFI_PHYSICAL_ADDRESS  ProductKeyAddress;
} EFI_OA3_MSDM_STRUCTURE;


#pragma pack()

//---------------------------------------------------------------------------

#endif


//****************************************************************************
//****************************************************************************
//**                                                                        **
//**             (C)Copyright 1985-2011, American Megatrends, Inc.          **
//**                                                                        **
//**                          All Rights Reserved.                          **
//**                                                                        **
//**             5555 Oakbrook Pkwy, Suite 200, Norcross, GA 30093          **
//**                                                                        **
//**                          Phone (770)-246-8600                          **
//**                                                                        **
//****************************************************************************
//****************************************************************************
