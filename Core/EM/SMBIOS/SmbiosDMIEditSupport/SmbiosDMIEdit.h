//**********************************************************************//
//**********************************************************************//
//**                                                                  **//
//**        (C)Copyright 1985-2016, American Megatrends, Inc.         **//
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
// $Header: /Alaska/SOURCE/Modules/SMBIOS/SmbiosDMIEditSupport/SmbiosDMIEdit.h 15    4/04/16 11:42a Davidd $
//
// $Revision: 15 $
//
// $Date: 4/04/16 11:42a $
//**********************************************************************//
// Revision History
// ----------------
// $Log: /Alaska/SOURCE/Modules/SMBIOS/SmbiosDMIEditSupport/SmbiosDMIEdit.h $
// 
// 15    4/04/16 11:42a Davidd
// [TAG]  		EIP262865
// [Category]  	Improvement
// [Description]  	[APTIO4][Smbios]DmiEdit needs changes as smiflash
// protocol is being changed to deny calls with Smm buffer
// [Files]  		SmbiosDMIEdit.mak
// SmbiosDMIEdit.h
// SmbiosDMIEdit.c
// SmbiosDMIEditFunc.c
//
// 14    6/12/12 11:28a Davidd
// [TAG]  		EIP92073
// [Category]  	Bug Fix
// [Severity]  	Normal
// [Symptom]  	"write once" not updating properly for multiple instances
// of the same structure type using AMI DmiEdit tool
// [RootCause]  	Write-once implementation only supported single instance
// of a structure.
// [Solution]  	Changes made to support more than one instance of a given
// structure.
// [Files]  		SmbiosDMIEdit.h
// SmbiosDMIEditFunc.c
//
// 13    6/08/12 6:02p Davidd
// [TAG]  		EIP88664
// [Category]  	New Feature
// [Description]  	Need tool to update smbios information
// [Files]  		SmbiosDMIEdit.c
// SmbiosDMIEdit.h
// SmbiosDMIEdit.sdl
// SmbiosDMIEditFunc.c
//
// 12    11/17/11 2:39p Davidd
// [TAG]           EIP74579
// [Category]      Improvement
// [Description]   Update SMBIOS moudule to let AMDELNX support SMBIOS
// spec 2.7
//                 (remove the 64 characters string limitation)
// [Files]         Smbios.h
//                 SmbiosStaticData.sdl
//                 Smbios.c
//                 SMBios.dxs
//                 SmbiosDMIEdit.sdl
//                 SmbiosDMIEdit.h
//                 SmbiosDMIEditFunc.c
//                 SmbiosNvram.c
//                 SmbiosFlashData.sdl
//
// 11    5/11/11 12:33p Davidd
// [TAG]           EIP58171
// [Category]      Bug Fix
// [Severity]      Important
// [Symptom]       TABLE_INFO structure of SmbiosDMIEdit is not backward
// compatible for AFU preserve DMI structure feature.
// [RootCause]     TABLE_INFO structure of SmbiosDMIEdit is not backward
// compatible.
// [Solution]      New TABLE_INFO structure defined for backward
// compatibility and support added.
// [Files]         Smbios.c
//                 SmbiosDMIEdit.h
//                 SmbiosDMIEditFunc.c
//                 SmbiosGetFlashData.c
//
// 10    11/02/10 4:13p Davidd
// [TAG]           EIP42938
// [Category]      BUG FIX
// [Severity]      Critical
// [Symptom]       The SMBIOS string field cannot be successfully updated
// if it was programmed to Null by the 3-party SMBIOS tool
// [RootCause]     BIOS did not have support for NULL strings
// [Solution]      Problem has been fixed with code changes
// [Files]
//    Smbios.c
//    SmbiosDMIEditFunc.c
//    SmbiosGetFlashData.c
//    SmbiosDMIEdit.h
//    SmbiosFlashData.sdl
//
// 9     5/18/10 5:10p Davidd
// Added PnP function 52h commands 3 and 4 support - EIP 38010.
//
// 8     8/05/09 6:20p Davidd
// Added DMIEDIT support for Type 0 and Type 12 structures - EIP 24878
//
// 7     1/28/09 11:52a Davidd
// New changes added to support DMIEdit data storage location in flash
// selectable via SMBIOS_DMIEDIT_DATA_LOC SDL token
//
// 6     1/03/08 12:30p Olegi
// Fix in GET_SMBIOS_INFO structure for x64 projects.
//
// 5     3/29/07 6:02p Davidd
// Changed the year in the AMI banner and clean up the code.
//
// 4     12/15/06 5:42p Davidd
// Code cleanup and reformatted to coding standard.
//
// 3     11/30/06 3:33p Davidd
// Changes made for 64 bit support.
//
// 2     3/02/06 11:10a Davidd
// Removed FLASH_START definition. Not needed.
//
// 1     4/29/05 2:06p Davidd
// Initial checkin.
//
//**********************************************************************//

#ifndef _SmbiosDMIEdit_DRIVER_H
#define _SmbiosDMIEdit_DRIVER_H

#include <efi.h>
#include <token.h>

#if !defined(SMBIOS_DMIEDIT_DATA_LOC) || SMBIOS_DMIEDIT_DATA_LOC != 2
#include <Protocol/SmiFlash.h>
#include <Protocol/FlashProtocol.h>
#endif

extern EFI_BOOT_SERVICES		*pBS;

UINT16 GetSmbiosInfo(GET_SMBIOS_INFO);
UINT16 GetSmbiosStructure(GET_SMBIOS_STRUCTURE);
UINT16 SetSmbiosStructure(SET_SMBIOS_STRUCTURE);

#pragma pack(1)

//<AMI_SHDR_START>
//----------------------------------------------------------------------------
// Name:  SMBIOS_TABLE_ENTRY
//
// Description: SMBIOS Entry Point structure
//----------------------------------------------------------------------------
//<AMI_SHDR_END>
typedef struct {
    UINT32    AnchorString;
    UINT8     EntryPointStructChecksum;
    UINT8     EntryPointLength;
    UINT8     MajorVersion;
    UINT8     MinorVersion;
    UINT16    MaximumStructSize;
    UINT8     EntryPointRevision;
    UINT8     FormattedArea[5];
    UINT8     IntermediateAnchor[5];
    UINT8     IntermediateChecksum;
    UINT16    StructTableLength;
    UINT32    StructTableAddress;
    UINT16    NumStructs;
    UINT8     SmbiosBCDRevision;
} SMBIOS_TABLE_ENTRY;

//<AMI_SHDR_START>
//----------------------------------------------------------------------------
// Name:  DMI_STRUC
//
// Description: Structure Header
//----------------------------------------------------------------------------
//<AMI_SHDR_END>
typedef struct {
    UINT8		Type;
    UINT8		Length;
    UINT16		Handle;
} DMI_STRUC;

//<AMI_SHDR_START>
//----------------------------------------------------------------------------
// Name:  SET_SMBIOS_STRUCTURE_DATA
//
// Description: Set SMBIOS Structure Data
//----------------------------------------------------------------------------
//<AMI_SHDR_END>
typedef struct {
    UINT8     Command;
    UINT8     FieldOffset;
    UINT32    ChangeMask;
    UINT32    ChangeValue;
    UINT16    DataLength;
    DMI_STRUC StructureHeader;
    UINT8     StructureData[1];
} SET_SMBIOS_STRUCTURE_DATA;

//<AMI_SHDR_START>
//----------------------------------------------------------------------------
// Name:  GET_SMBIOS_INFO
//
// Description: Get SMBIOS Information
//----------------------------------------------------------------------------
//<AMI_SHDR_END>
typedef struct {
    UINT16		Function;
    UINT32		DmiBiosRevision32BitAddr;
    UINT32		NumStructures32BitAddr;
    UINT32		StructureSize32BitAddr;
    UINT32		DmiStorageBase32BitAddr;
    UINT32		DmiStorageSize32BitAddr;
    UINT16		BiosSelector; //Always 0.
/////////////////////////////////////
// The above pointers point below. //
/////////////////////////////////////
    UINT32		DmiBiosRevision;
    UINT32		NumStructures;
    UINT32		StructureSize;
    UINT32		pDmiStorageBase;
    UINT32		DmiStorageSize;
} GET_SMBIOS_INFO;

//<AMI_SHDR_START>
//----------------------------------------------------------------------------
// Name:  GET_SMBIOS_STRUCTURE
//
// Description: Get SMBIOS Structure
//----------------------------------------------------------------------------
//<AMI_SHDR_END>
typedef struct {
    UINT16		Function;
    UINT32		Handle32BitAddr;
    UINT32		Buffer32BitAddr;
    UINT16		DmiSelector;  //Always 0
    UINT16		BiosSelector; //Always 0
/////////////////////////////////////
// The above pointers point below. //
/////////////////////////////////////
    UINT16		Handle;
    UINT8		Buffer[1];    //Variable Length;
} GET_SMBIOS_STRUCTURE;

//<AMI_SHDR_START>
//----------------------------------------------------------------------------
// Name:  SET_SMBIOS_STRUCTURE
//
// Description: Set SMBIOS Structure
//----------------------------------------------------------------------------
//<AMI_SHDR_END>
typedef struct {
    UINT16		Function;
    UINT32		Buffer32BitAddr;
    UINT32		DmiWorkBuffer32BitAddr;
    UINT8		Control;    //?
    UINT16		DmiSelector;  //Always 0
    UINT16		BiosSelector; //Always 0
/////////////////////////////////////
// The above pointers point below. //
/////////////////////////////////////
    SET_SMBIOS_STRUCTURE_DATA StructureData;    //Variable Length;
} SET_SMBIOS_STRUCTURE;

//<AMI_SHDR_START>
//----------------------------------------------------------------------------
// Name:  TABLE_INFO
//
// Description: DMI data record
//----------------------------------------------------------------------------
//<AMI_SHDR_END>

#define DMIEDIT_WRITE_ONCE      0x01
#define DMIEDIT_DELETE_STRUC    0x02
#define DMIEDIT_ADD_STRUC       0x04
#define DMIEDIT_EXTENDED_HDR    0x80

typedef struct {
    UINT8   Type;
    UINT8   Offset;     // Structure field offset, or string number for Type 11 and 12
    UINT8   Reserved;   // Size of string including \0 or UUID (16)
    UINT8   Flags;      // Bit0 = Write Once
                        // Bit1 = Delete Structure
                        // Bit2 = Add structure
                        // Bit7 = Extended Header
    UINT8   HdrLength;
    UINT16  Size;
    UINT16  Handle;
} TABLE_INFO;

//<AMI_SHDR_START>
//----------------------------------------------------------------------------
// Name:  WRITE_ONCE_TABLE
//
// Description: Write Once structure
//----------------------------------------------------------------------------
//<AMI_SHDR_END>
typedef struct {
    UINT8   Type;
    UINT8   Offset;
  	BOOLEAN WriteOnce;
} WRITE_ONCE_TABLE;

typedef struct {
    UINT8   Type;
    UINT8   Offset;
    UINT16  Handle;
} WRITE_ONCE_STATUS;

#if !defined(SMBIOS_DMIEDIT_DATA_LOC) || SMBIOS_DMIEDIT_DATA_LOC != 2   // FV_BB or FV_MAIN

//<AMI_SHDR_START>
//----------------------------------------------------------------------------
// Name:  FLASH_DATA_INFO
//
// Description: Flash Data Information
//----------------------------------------------------------------------------
//<AMI_SHDR_END>
typedef struct {
	UINT8		*Location;
	UINT16		Size;
	UINT8		*EndOfData;
} FLASH_DATA_INFO;

extern UINT8  					*gBlockSave;
extern VOID   					*gFlashData;
extern UINT32 					gFlashDataSize;
extern EFI_SMI_FLASH_PROTOCOL   *mSmiFlash;
extern FLASH_PROTOCOL           *mFlash;

#endif                                  // SMBIOS_DMIEDIT_DATA_LOC

#if (defined(NonSmiDmiEdit_Support) && (NonSmiDmiEdit_Support == 1))
#define AMI_DMIEDIT_SMBIOS_GUID \
    { 0x74211cd7, 0x3d8e, 0x496f, { 0xba, 0x2, 0x91, 0x9c, 0x2e, 0x1f, 0x6, 0xcb } }

typedef struct _EFI_SMBIOS_DMIEDIT_PROTOCOL EFI_SMBIOS_DMIEDIT_PROTOCOL;

typedef UINT32  (EFIAPI *DMIEDIT_NONSMI_HANDLER) (
    IN UINT8                    Data,
    IN UINT64                   pCommBuff
);

typedef struct _EFI_SMBIOS_DMIEDIT_PROTOCOL {
    DMIEDIT_NONSMI_HANDLER      DmiEditNonSmiHandler;
};

UINT32 DmiEditNonSmiHandler(
    IN UINT8            Data,
    IN UINT64           pCommBuff
);
#endif                                  // NonSmiDmiEdit_Support

#pragma pack()

#endif

//**********************************************************************//
//**********************************************************************//
//**                                                                  **//
//**        (C)Copyright 1985-2016, American Megatrends, Inc.         **//
//**                                                                  **//
//**                       All Rights Reserved.                       **//
//**                                                                  **//
//**        5555 Oakbrook Pkwy, Suite 200, Norcross, GA 30093         **//
//**                                                                  **//
//**                       Phone: (770)-246-8600                      **//
//**                                                                  **//
//**********************************************************************//
//**********************************************************************//
