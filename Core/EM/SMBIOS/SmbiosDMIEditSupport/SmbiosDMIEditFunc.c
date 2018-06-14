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
// $Header: /Alaska/SOURCE/Modules/SMBIOS/SmbiosDMIEditSupport/SmbiosDMIEditFunc.c 69    4/07/16 6:03p Davidd $
//
// $Revision: 69 $
//
// $Date: 4/07/16 6:03p $
//**********************************************************************//
// Revision History
// ----------------
// $Log: /Alaska/SOURCE/Modules/SMBIOS/SmbiosDMIEditSupport/SmbiosDMIEditFunc.c $
// 
// 69    4/07/16 6:03p Davidd
// [TAG]  		EIP231162
// [Category]  	New Feature
// [Description]  	Merge Aptio V Smbios -09 changes for Aptio 4
// 4.6.5.5_SMBIOS_40 release
// [Files]  		Smbios.c
// SmbiosDmiEdit.c
// SmbiosDmiEditFunc.c
//
// 68    4/04/16 11:43a Davidd
// [TAG]  		EIP262865
// [Category]  	Improvement
// [Description]  	[APTIO4][Smbios]DmiEdit needs changes as smiflash
// protocol is being changed to deny calls with Smm buffer
// [Files]  		SmbiosDMIEdit.mak
// SmbiosDMIEdit.h
// SmbiosDMIEdit.c
// SmbiosDMIEditFunc.c
//
// 67    11/25/14 12:50p Davidd
// [TAG]  		EIP193846
// [Category]  	Bug Fix
// [Severity]  	Minor
// [Symptom]  	Generic changes for EIP187631
// [RootCause]  	Function isWriteOnce is called even when the input
// control is zero case (for validating the parameters)
// [Solution]  	Excecute function isWriteOnce only if input control is set
// [Files]  		SmbiosDMIEditFunc.c
//
// 66    8/11/14 10:46a Davidd
// [TAG]  		    EIP177887
// [Category]  	Bug Fix
// [Severity]  	Minor
// [Symptom]  	    Build error if token "SYS_CHASSIS_INFO" set to "0"
// [RootCause]  	Build error caused by non-existence token when
// SYS_CHASSIS_INFO is disabled
// [Solution]  	Added preprocessor checks
// [Files]  		Smbios.c - File version: 153
//                 SmbiosDmiEditFunc.c
//
// 65    8/08/14 3:50p Davidd
// [TAG]  		EIP180676
// [Category]  	Bug Fix
// [Severity]  	Minor
// [Symptom]  	UUID Updated by 3rd party DMI/SMBIOS tools is not working.
// [RootCause]  	UUID is updated 4 bytes at a time instead of 16
// [Solution]  	Modified code to handle all update types (1, 2, or 4
// bytes) as 16 bytes
// [Files]  		SmbiosDMIEditFunc.c
//
// 64    12/05/13 12:05p Davidd
//
// 63    11/15/13 4:34p Davidd
// [TAG]           EIP143321
// [Category]      Improvement
// [Description]   Perform "CppCheck" on Smbios module for
// '4.6.5.1_SMBIOS_36' release
// [Files]         SmbiosBoard.c
//                 Smbios.c
//                 SmbiosDMIEdit.c
//                 SmbiosDMIEditFunc.c
//                 SmbiosNvramFunc.c
//
// 62    10/07/13 1:23p Davidd
// [TAG]  		EIP129122
// [Category]  	Bug Fix
// [Severity]  	Normal
// [Symptom]  	Purchase date is not updated in DMI Data area of NCB
// [RootCause]  	Old data is not cleared when new data size is smaller
// than existing one
// [Solution]  	Clear old data when new data size is smaller than existing
// one
// [Files]  		SmbiosDMIEditFunc.c
//
// 61    9/25/13 2:51p Davidd
// [TAG]  		EIP136093
// [Category]  	New Feature
// [Description]  	SMBIOS Type0 offest 04 can't update by AMIDEDOS
// [Files]  		SmbiosDMIEditFunc.c
//
// 60    8/23/13 6:28p Davidd
// [TAG]  		EIP132364
// [Category]  	Improvement
// [Description]  	DMIEdit fails to update in the following cases:
// 1. When current string is NULL
// 2. When structure is created by OEM
// 3. When structure is created with strings not numbered sequentially
// [Files]  		Smbios.c
// SmbiosDMIEditFunc.c
//
// 59    6/03/13 6:26p Davidd
// [TAG]  		EIP125665
// [Category]  	New Feature
// [Description]  	Request to Support multiple instances of SMBIOS Type 3
// structure (merge EIP106206 into Aptio 4)
// [Files]  		Smbdata.mac
// SmbiosStaticData.sdl
// Smbstruc.def
// Smbios.c
// SmbiosDMIEditFunc.c
// Smbios.h
//
// 58    5/23/13 2:41p Davidd
// [TAG]  		    EIP104836
// [Category]  	New Feature
// [Description]  	DMIEdit support edit type 4
// [Files]  		SmbiosBoard.c
//                 SmbiosDMIEditBoard.sdl
//                 Smbios.c
//                 SmbiosDMIEditFunc.c
//                 Smbios.h
//                 SmbiosDynamicData.h
//
// 57    2/28/13 3:10p Davidd
// [TAG]  		EIP115031
// [Category]  	Bug Fix
// [Severity]  	Important
// [Symptom]  	NVRAM data corruption
// [RootCause]  	In UpdateSmbiosTable function, FlashDataOffset is
// incorrectly calculated for certain case
// [Solution]  	Corrected code.
// [Files]  		SmbiosDMIEditFunc.c
//
// 56    1/16/13 10:49a Davidd
// [TAG]           EIP110905
// [Category]      Bug Fix
// [Severity]      Minor
// [Symptom]       AMI DMIEDIT_DOS tool issue (Type 11 fails to update)
// [RootCause]     Problem is caused by recent change for EIP96221 where a
// line of code
//                 was inadvertently left out when function SetType11 was
// simplified
// [Solution]      Corrected missing code
// [Files]         SmbiosDMIEditFunc.c
//
// 55    8/02/12 12:45p Davidd
// [TAG]  		EIP96064
// [Category]  	Bug Fix
// [Severity]  	Minor
// [Symptom]  	SMBIOS: DmiEdit support creates NVRAM variables with names
// of incorrect length
// [RootCause]  	Swprintf_s function creates 15 characters variable name
// with NULL terminator in last byte.
// [Solution]  	Use Swprintf function instead
// [Files]  		Smbios.c
// SmbiosDMIEditFunc.c
// SmbiosNvramFunc.c
//
// 54    7/27/12 2:56p Davidd
// [TAG]  		EIP96221
// [Category]  	Bug Fix
// [Severity]  	Minor
// [Symptom]  	Smbios DmiEdit: Nvram variables store extraneous data for
// fixed-length structure change.
// [RootCause]  	Input "DataLength" field is used for data size, but this
// field is not valid for fixed-size data change
// [Solution]  	Added code to determine data size based on input command
// byte
// [Files]  		SmbiosDMIEditFunc.c
//
// 53    6/12/12 3:54p Davidd
// [TAG]  		EIP89994
// [Category]  	Bug Fix
// [Severity]  	Important
// [Symptom]  	UpdateSmbiosTable function in SmbiosDMIEdit.c seems have
// problem to handle
// [RootCause]  	Data not checked for cross boundary
// [Solution]  	Added code to check for cross boundary and update flash
// block accordingly.
// [Files]  		SmbiosDMIEditFunc.c
//
// 52    6/12/12 11:30a Davidd
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
// 51    6/08/12 6:03p Davidd
// [TAG]  		EIP88664
// [Category]  	New Feature
// [Description]  	Need tool to update smbios information
// [Files]  		SmbiosDMIEdit.c
// SmbiosDMIEdit.h
// SmbiosDMIEdit.sdl
// SmbiosDMIEditFunc.c
//
// 50    6/06/12 3:09p Davidd
// [TAG]  		EIP81954
// [Category]  	Bug Fix
// [Severity]  	Normal
// [Symptom]  	WriteOnceTable is not supported when
// SMBIOS_DMIEDIT_DATA_LOC is 2
// [RootCause]  	WriteOnce is not properly checked
// [Solution]  	Changes added to check for WriteOnce status
// [Files]  		SmbiosDMIEdit.c
// SmbiosDMIEditFunc.c
//
// 49    4/17/12 10:39a Davidd
// [TAG]  		    EIP86776
// [Category]  	Bug Fix
// [Severity]  	Normal
// [Symptom]  	    Build error if "OEM_STRING_INFO" token is set to "0"
// [RootCause]  	SMBIOS_OEM_STRINGS_INFO definition is used even when
//                 OEM_STRING_INFO is disabled.
// [Solution]  	Removed reference to "SMBIOS_OEM_STRINGS_INFO" in
//                 "GetStructureLength" function (not really needed).
// [Files]  		Smbios.c
//                 SmbiosDMIEditFunc.c
//
// 48    11/17/11 2:41p Davidd
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
// 45    10/06/11 4:47p Davidd
// EIP65648 extended change.
//
// 44    9/29/11 4:39p Davidd
// [TAG]           EIP68202
// [Category]      NEW FEATURE
// [Description]   Allow Smbios Type 2 Location field and Type 3 SKU
// Number field
//                 to be apdated by dmieditwingui tool
// [Files]         Smbios.c
//                 SmbiosDMIEditFunc.c
//                 Smbdata.mac
//
// 43    8/30/11 4:14p Davidd
// [TAG]           EIP65648
// [Category]      Improvement
// [Description]   Update SMBIOS eModules for uEFI 2.3.1 / PI 1.2
// compliance
// [Files]         Smbios.c
//                 Smbios.dxs
//                 SmbiosDMIEdit.c
//                 SmbiosDMIEditFunc.c
//                 SmbiosGetFlashData.c
//                 SmbiosGetFlashData.dxs
//
// 42    8/03/11 10:53a Davidd
// [TAG]           EIP64029
// [Category]      NEW FEATURE
// [Description]   Allow SMBIOS Type 22 to be modified using DMIEdit
// [Files]         Smbios.h
//                 Smbios.c
//                 SmbiosDmieditFunc.c
//
// 41    5/11/11 12:34p Davidd
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
// 40    5/04/11 3:19p Davidd
// [TAG]           EIP57144
// [Category]      NEW FEATURE
// [Description]   Allow SMBIOS Type 39 to be modified using DMIEdit
// [Files]         SmbiosBoard.c
//                 Smbios.h
//                 SmbiosDynamicData.h
//                 Smbios.c
//                 SmbiosDmieditFunc.c
//                 SmbiosNvramFunc.c
//
// 39    3/16/11 3:37p Davidd
// [TAG]           EIP53939
// [Category]      Bug Fix
// [Severity]      Normal
// [Symptom]       SMBIOS DMIEdit Driver always assumes FLASH_BLOCK_SIZE =
// 64KB
// [RootCause]     Block size was assumed to be 64K
// [Solution]      Problem has been fixed with code changes
// [Files]         SmbiosDMIEdit.c
//                 SmbiosDMIEditFunc.c
//
// 38    3/02/11 11:45a Davidd
// [TAG]           EIP54264
// [Category]      Bug Fix
// [Severity]      Normal
// [Symptom]       Data is assumed valid without checking after some
// GetVariable calls
// [RootCause]     No error checking
// [Solution]      Problem has been fixed with code changes
// [Files]         SmbiosNvramFunc.c
//                 SmbiosDMIEditFunc.c
//
// 37    12/14/10 3:40p Davidd
// Updated StringType_3 table to include SKU string field.
//
// 36    11/02/10 4:13p Davidd
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
// 35    10/21/10 11:36a Davidd
// [TAG]           EIP46394
// [Category]      BUG FIX
// [Severity]      Important
// [Symptom]       Incorrect variable size for GetVariable() usage in
// Smbios module
// [RootCause]     GetVariable is called with incorrect "DataSize" type.
// [Solution]      Corrected "DataSize" type in all GetVariable calls.
// [Files]
//    Smbios.c
//    SmbiosDMIEditFunc.c
//    SmbiosNvramFunc.c
//
// 34    5/18/10 5:13p Davidd
// Added PnP function 52h commands 3 and 4 support - EIP 38010.
//
// 33    3/08/10 3:48p Davidd
// Corrected Type1 UUID update problem with customer utility (update by
// dword instead of block command) - EIP 35486
//
// 32    2/12/10 3:59p Davidd
// Added conditional compile switch for Type 12 - EIP 34631
// Same were added for Type 2, 3, and 11.
//
// 31    11/23/09 5:51p Davidd
// Corrected the DMIEdit data not updated after being updated 5-6 times
// (when NVRAM is used to store DMIEdit data) - EIP 30837.
//
// 30    8/05/09 6:19p Davidd
// Added DMIEDIT support for Type 0 and Type 12 structures - EIP 24878
//
// 29    6/02/09 11:21a Davidd
// Updated function headers. (EIP 22180)
//
// 28    2/13/09 10:43a Davidd
// Changes made to return the SMBIOS table size in dmiStorageSize for
// SMBIOS PnP function 50h (EIP 19115)
//
// 27    2/02/09 4:36p Davidd
// Fixed the problem updating the existing DMIEdit data when FV_MAIN is
// used for storage.
//
// 26    1/28/09 11:53a Davidd
// New changes added to support DMIEdit data storage location in flash
// selectable via SMBIOS_DMIEDIT_DATA_LOC SDL token
//
// 25    12/16/08 2:24a Iminglin
// (EIP17767) The function value of GetStructureByHandleThenUpdateHandle
// for compliance.
//
// 24    11/14/08 3:29p Davidd
// - Changed header blocks
// - Corrected build error when NUMBER_OF_BLOCKS is a large number.
//
// 23    2/13/08 12:57p Davidd
// Fixed getting SMBIOS structure type 127 problem.
//
// 22    1/03/08 12:30p Olegi
// Fix in GET_SMBIOS_INFO structure for x64 projects.
//
// 21    11/26/07 11:39a Davidd
// Changes added to allow "Asset Tag" in Type 2 structure to be updated
// per EIP 11283.
//
// 20    9/06/07 10:55a Davidd
// Undo the Rev. 18 check-in. UUID reversal problem is now corrected in
// Smbios.c.
//
// 19    8/30/07 12:23p Davidd
// Fixed bug writing to NVRAM with 1.5MB BIOS size.
//
// 18    8/10/07 12:44p Davidd
// When updating the system UUID, new UUID is saved in NVRAM correctly but
// the UUID is copied to memory in reverse order.
//
// 17    7/10/07 3:05p Davidd
// Fixed bug for DMIEdit Type 12 support.
//
// 16    6/20/07 10:57a Pats
// Modified to support editing of SMBIOS structure type 0, offsets 5 and
// 8.
//
// 15    3/29/07 6:06p Davidd
// Changed the year in the AMI banner and code cleanup.
//
// 14    2/21/07 4:30p Davidd
// Fixed the hanging problem during updating DMI data using DMIEdit
// (multiple times with long strings).
//
// 13    2/05/07 11:59a Davidd
// Corrected resetting problem during updating DMI data with Dmiedit (seen
// with Core 4.5.3).
//
// 12    12/15/06 5:46p Davidd
// Code cleanup and reformatted to coding standard.
//
// 11    11/03/06 11:57a Davidd
// Added code to make Type 1 SKU and Family fields editable by DMIEdit
// utility.
//
// 10    10/27/06 3:12p Davidd
// Corrected the problem getting the string index in GetType1StringIndex
//
// 9     10/05/06 4:52p Davidd
// Changes added for 64 bit support. Also use generic funtion MemCpy
// rather than SmbiosMemCpy.
//
// 8     3/03/06 2:27p Davidd
// Fixed the random hanging problem when using GetFlashInfo to get the
// flash block size.
//
// 7     3/03/06 1:20p Davidd
// In UpdateSmbiosTable, set the flash block size to
// FLASH_BLOCK_SIZE SDL token.
//
// 6     3/02/06 1:57p Davidd
// Updated include path to SMBios.h. It has been moved to
// Include\Protocol
//
// 5     3/02/06 11:27a Davidd
// Made some changes in the Update SmbiosTable routine to get the
// flash information by calling the SMIFlash GetFlashInfo protocol rather
// than hardcoding.
//
// 4     2/24/06 3:47p Davidd
// Corrected the UUID data updated in reverse order (type 1 structure).
//
// 3     8/15/05 1:02p Davidd
// Fixed the issue of updating DMI data when Debug_Mode is set to 0.
//
// 2     8/10/05 10:48a Davidd
// Code cleanup.
//
// 1     4/29/05 2:06p Davidd
// Initial checkin.
//
//**********************************************************************//

#include <AmiDxeLib.h>
#include "SmbiosDMIEdit.h"
#include "Protocol\Smbios.h"
#include <Protocol\FlashProtocol.h>
#include "AmiLib.h"

#define FLASH_DEVICE_BASE (0xFFFFFFFF - FLASH_SIZE + 1)
#define WRITE_ONCE_ENTRIES  0x10    // Maximum number of WRITE_ONCE_STATUS entries

#if PI_SPECIFICATION_VERSION >= 0x0001000a && SMM_MINOR_VER >= 43
    extern EFI_SMM_SYSTEM_TABLE2    *mSmst;
#else
    extern EFI_SMM_SYSTEM_TABLE     *mSmst;
#endif

#if !defined(SMBIOS_DMIEDIT_DATA_LOC) || SMBIOS_DMIEDIT_DATA_LOC != 2
#if defined(NonSmiDmiEdit_Support) && (NonSmiDmiEdit_Support == 1)
extern FLASH_PROTOCOL       *FlashProtocol;
#endif                                  // NonSmiDmiEdit_Support

VOID                        *gFlashData;
UINT32                      gFlashDataSize;
#else
CHAR16                      *DmiArrayVar = L"DmiArray";
DMI_VAR                     DmiArray[DMI_ARRAY_COUNT] = {0};
UINTN                       DmiArraySize = DMI_ARRAY_COUNT * sizeof(DMI_VAR);
UINT8                       *DmiData;
UINTN                       DmiDataSize;
CHAR16                      *Var = L"                ";
UINT8                       Index;
#endif                                  // SMBIOS_DMIEDIT_DATA_LOC

EFI_GUID                    EfiSmbiosNvramGuid = EFI_SMBIOS_NVRAM_DATA_GUID;

SMBIOS_TABLE_ENTRY_POINT    *SmbiosTableEntryPoint = NULL;
UINT8                       *ScratchBufferPtr = NULL;
UINT16						MaximumBufferSize;

BOOLEAN                     SwSmiMethod;

//
// String type tables
//
STRING_TABLE    StringType_0[] =   {{0x04, 1, 1},
                                    {0x05, 2, 2},
                                    {0x08, 3, 3},
                                    {0xff, 0, 0},
                                   };

STRING_TABLE    StringType_1[] =   {{0x04, 1, 1},
                                    {0x05, 2, 2},
                                    {0x06, 3, 3},
                                    {0x07, 4, 4},
                                    {0x19, 5, 5},
                                    {0x1a, 6, 6},
                                    {0xff, 0, 0},
                                   };

STRING_TABLE    StringType_2[] =   {{0x04, 1, 1},
                                    {0x05, 2, 2},
                                    {0x06, 3, 3},
                                    {0x07, 4, 4},
                                    {0x08, 5, 5},
                                    {0x0a, 6, 6},
                                    {0xff, 0, 0},
                                   };

#if (SYS_CHASSIS_INFO == 1)
STRING_TABLE    StringType_3[NUMBER_OF_SYSTEM_CHASSIS][6] =
                                  {{{0x04, 1, 1},
                                    {0x06, 2, 2},
                                    {0x07, 3, 3},
                                    {0x08, 4, 4},
                                    {0x15 + (ELEMENT_COUNT_1 * ELEMENT_LEN_1), 5, 5},
                                    {0xff, 0, 0},
                                   },
#if NUMBER_OF_SYSTEM_CHASSIS > 1
                                   {
                                    {0x04, 1, 1},
                                    {0x06, 2, 2},
                                    {0x07, 3, 3},
                                    {0x08, 4, 4},
                                    {0x15 + (ELEMENT_COUNT_2 * ELEMENT_LEN_2), 5, 5},
                                    {0xff, 0, 0},
                                   },
#endif
#if NUMBER_OF_SYSTEM_CHASSIS > 2
                                   {
                                    {0x04, 1, 1},
                                    {0x06, 2, 2},
                                    {0x07, 3, 3},
                                    {0x08, 4, 4},
                                    {0x15 + (ELEMENT_COUNT_3 * ELEMENT_LEN_3), 5, 5},
                                    {0xff, 0, 0},
                                   },
#endif
#if NUMBER_OF_SYSTEM_CHASSIS > 3
                                   {
                                    {0x04, 1, 1},
                                    {0x06, 2, 2},
                                    {0x07, 3, 3},
                                    {0x08, 4, 4},
                                    {0x15 + (ELEMENT_COUNT_4 * ELEMENT_LEN_4), 5, 5},
                                    {0xff, 0, 0},
                                   },
#endif
#if NUMBER_OF_SYSTEM_CHASSIS > 4
                                   {
                                    {0x04, 1, 1},
                                    {0x06, 2, 2},
                                    {0x07, 3, 3},
                                    {0x08, 4, 4},
                                    {0x15 + (ELEMENT_COUNT_5 * ELEMENT_LEN_5), 5, 5},
                                    {0xff, 0, 0},
                                   },
#endif
                                   };
#endif  // #if (SYS_CHASSIS_INFO == 1)

STRING_TABLE    StringType_4[] =   {{0x04, 1, 1},
                                    {0x07, 2, 2},
                                    {0x10, 3, 3},
                                    {0x20, 4, 4},
                                    {0x21, 5, 5},
                                    {0x22, 6, 6},
                                    {0xff, 0, 0},
                                   };

STRING_TABLE    StringType_22[] =  {{0x04, 1, 1},
                                    {0x05, 2, 2},
                                    {0x06, 3, 3},
                                    {0x07, 4, 4},
                                    {0x08, 5, 5},
                                    {0x0e, 6, 6},
                                    {0x14, 7, 7},
                                    {0xff, 0, 0},
                                   };

STRING_TABLE    StringType_39[] =  {{0x05, 1, 1},
                                    {0x06, 2, 2},
                                    {0x07, 3, 3},
                                    {0x08, 4, 4},
                                    {0x09, 5, 5},
                                    {0x0a, 6, 6},
                                    {0x0b, 7, 7},
                                    {0xff, 0, 0},
                                   };

//
// String table
//
VOID*    StringTable[] = {&StringType_0,        // 0
                          &StringType_1,        // 1
                          &StringType_2,        // 2
#if (SYS_CHASSIS_INFO == 1)
                          &StringType_3,        // 3
#endif  // #if (SYS_CHASSIS_INFO == 1)
                          &StringType_4,        // 4
                          &StringType_22,       // 5
                          &StringType_39,       // 6
                         };

//<AMI_THDR_START>
//----------------------------------------------------------------------------
// Name:        WriteOnceTable
//
// Description: Table indicating which structure and offset can be written
//              only once or multiple times
//
// Notes:
//----------------------------------------------------------------------------
//<AMI_THDR_END>
WRITE_ONCE_TABLE WriteOnceTable[] = {
                                      {1, 4, TRUE},
                                      {2, 4, TRUE},
                                    };

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   WriteOnceStatusInit
//
// Description: Initialize NVRAM variable holding WriteOnce statuses
//
// Input:       None
//
// Output:      None
//
// Modified:
//
// Referrals:
//
// Notes:
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID
WriteOnceStatusInit(VOID)
{
    EFI_STATUS          Status;
    WRITE_ONCE_STATUS   *Buffer;
    UINTN               BufferSize;

    BufferSize = WRITE_ONCE_ENTRIES * sizeof(WRITE_ONCE_STATUS);
    pBS->AllocatePool(EfiBootServicesData, BufferSize, &Buffer);

    // Create "WriteOnceStatus" variable if it does not exist
    Status = pRS->GetVariable(L"WriteOnceStatus",
                                &EfiSmbiosNvramGuid,
                                NULL,
                                &BufferSize,
                                Buffer);

    if (Status == EFI_NOT_FOUND) {
        // WriteOnceStatus variable does not exist
        // Create one with default value of Type 127
        MemSet(Buffer, BufferSize, 127);

    	pRS->SetVariable(L"WriteOnceStatus",
                        &EfiSmbiosNvramGuid,
                        EFI_VARIABLE_RUNTIME_ACCESS | EFI_VARIABLE_BOOTSERVICE_ACCESS | EFI_VARIABLE_NON_VOLATILE,
                        BufferSize,
                        Buffer);
    }

    pBS->FreePool(Buffer);
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   isWriteOnce
//
// Description: Determines if a given structure type and offset can only
//              be written once or multiple times.
//
// Input:       IN UINT8   Type
//              IN UINT8   Offset
//
// Output:      BOOLEAN - TRUE/FALSE for Write Once/Multiple
//
// Modified:
//
// Referrals:
//
// Notes:
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
BOOLEAN
isWriteOnce(
    IN UINT8    Type,
    IN UINT8    Offset,
    IN UINT16   Handle
)
{
    EFI_STATUS          Status;
    BOOLEAN             WriteOnce = FALSE;
    UINT8               TableEntries = sizeof(WriteOnceTable)/sizeof(WRITE_ONCE_TABLE);
    WRITE_ONCE_STATUS   Buffer[WRITE_ONCE_ENTRIES];
    UINTN               BufferSize;
    UINT8               i;
    UINT8               j;

    BufferSize = WRITE_ONCE_ENTRIES * sizeof(WRITE_ONCE_STATUS);
    Status = pRS->GetVariable(L"WriteOnceStatus",
                                &EfiSmbiosNvramGuid,
                                NULL,
                                &BufferSize,
                                Buffer);

    for (i = 0; i < TableEntries; ++i) {
        // Check for WriteOnce condition in WriteOnce table
        if (WriteOnceTable[i].Type == Type \
            && WriteOnceTable[i].Offset == Offset \
            && WriteOnceTable[i].WriteOnce) {
            // WriteOnce is set for input Type and Offset,
            // Check if WriteOnce was set already in WriteOnceStatus table
            // If "WriteOnceStatus" variable was not found then assume
            // WriteOnce was not set for this data field
            if (Status == EFI_SUCCESS) {
                for (j = 0; j < WRITE_ONCE_ENTRIES; ++j) {
                    if (Buffer[j].Type == 127) {
                        break;
                    }
                    if (Buffer[j].Type == Type && Buffer[j].Offset == Offset && Buffer[j].Handle == Handle) {
                        // WriteOnce was already set for input Type and Offset
                        WriteOnce = TRUE;
                        break;
                    }
                }
            }

            if (j < WRITE_ONCE_ENTRIES) {           // Make sure we are still within the WRITE_ONCE_ENTRIES
                // Create new WriteOnce entry if it did not exist for input Type and Offset
                if (WriteOnce == FALSE) {
                    Buffer[j].Type = Type;
                    Buffer[j].Offset = Offset;
                    Buffer[j].Handle = Handle;

                	pRS->SetVariable(L"WriteOnceStatus",
                                    &EfiSmbiosNvramGuid,
                                    EFI_VARIABLE_RUNTIME_ACCESS | EFI_VARIABLE_BOOTSERVICE_ACCESS | EFI_VARIABLE_NON_VOLATILE,
                                    BufferSize,
                                    Buffer);
                }
            }
        }
    }

    return WriteOnce;
}

#if !defined(SMBIOS_DMIEDIT_DATA_LOC) || SMBIOS_DMIEDIT_DATA_LOC != 2
//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   WriteToFlash
//
// Description: Write to the flash part starting at "Address" for a length
//              of "Size".
//
// Input:       IN VOID    *Address,
//              IN VOID    *Data,
//              IN UINTN   Size
//
// Output:      EFI_STATUS
//
// Modified:
//
// Referrals:
//
// Notes:
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS
WriteToFlash(
    IN VOID    *Address,
    IN VOID    *Data,
    IN UINTN   Size
)
{
	EFI_STATUS	Status;

	Status = mFlash->DeviceWriteEnable();
	if (EFI_ERROR(Status)) return Status;

	Status = mFlash->Write(Address, Size, Data);

	mFlash->DeviceWriteDisable();

	return Status;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   GetFlashDataInfo
//
// Description: Searches the Flash Data Table for a record of Type and
//              Offset. If found, returns the location found, the data size,
//              and the end of data.
//
// Input:       IN TABLE_INFO   RecordInfo
//
// Output:      FLASH_DATA_INFO
//
// Modified:
//
// Referrals:
//
// Notes:
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
FLASH_DATA_INFO
GetFlashDataInfo(
    IN TABLE_INFO   *RecordInfo
)
{
    TABLE_INFO        *FlashDataPtr = gFlashData;
    FLASH_DATA_INFO   FlashDataInfo = {0, 0, 0};

    while (FlashDataPtr->Handle != 0xffff) {
        if (FlashDataPtr->Type == RecordInfo->Type &&
		    FlashDataPtr->Handle == RecordInfo->Handle &&
		    FlashDataPtr->Offset == RecordInfo->Offset &&
			FlashDataPtr->Flags == RecordInfo->Flags) {
			FlashDataInfo.Location = (UINT8*)FlashDataPtr;
			FlashDataInfo.Size = FlashDataPtr->Size;
		}

        FlashDataPtr = (TABLE_INFO*)((UINT8*)(FlashDataPtr + 1) + FlashDataPtr->Size);
	}
	FlashDataInfo.EndOfData = (UINT8*)FlashDataPtr;
	return FlashDataInfo;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   UpdateSmbiosTable
//
// Description: Searches the Flash Data Table for a record of Type and
//              Offset. If found, the existing data will be replaced with
//              the new data, else the data will be added as a new record.
//
// Input:       IN TABLE_INFO  TableInfo,
//              IN UINT8       *Data
//
// Output:      EFI_STATUS
//
// Modified:
//
// Referrals:
//
// Notes:
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
UINT16
UpdateSmbiosTable(
    IN TABLE_INFO  *TableInfo,
    IN UINT8       *Data
)
{
    UINT16              	i;
    UINT8                   *BufferPtr = NULL;
    UINT16               	BufferSize = 0;
    UINT16               	Count = 0;
    UINT32              	SpaceAvailable;
    EFI_STATUS          	Status;
    FLASH_DATA_INFO     	FlashDataInfo;
    UINT8               	*FlashDataPtr;
    FUNC_BLOCK          	FuncBlock[2];
    EFI_PHYSICAL_ADDRESS    SmmBuffer;
    EFI_PHYSICAL_ADDRESS    Buffer;
#if defined(NonSmiDmiEdit_Support) && (NonSmiDmiEdit_Support == 1)
    EFI_PHYSICAL_ADDRESS    FlashDataBlock;
    UINT8                   BlockCount;
    UINT8                   *DataBuffer;
    UINTN                   RemainingSize;
#endif                                  // NonSmiDmiEdit_Support

    FlashDataInfo = GetFlashDataInfo(TableInfo);

    // Check Size
    SpaceAvailable = (UINT32)((UINT8*)gFlashData + gFlashDataSize - FlashDataInfo.EndOfData);
    if (FlashDataInfo.Location) SpaceAvailable += FlashDataInfo.Size + sizeof(TABLE_INFO);

    if (sizeof(TABLE_INFO) + TableInfo->Size > SpaceAvailable) {
        return DMI_ADD_STRUCTURE_FAILED;
    }

    if (SwSmiMethod) {
        // Initialize FuncBlock
        for (i = 0; i < 2; i++) {
            FuncBlock[i].BufAddr = 0;
            FuncBlock[i].BlockAddr = 0;
            FuncBlock[i].BlockSize = 0;
            FuncBlock[i].ErrorCode = 0;
        }

        // Allocate 4K working buffer in SMM.
        Status = mSmst->SmmAllocatePages ( AllocateAnyPages, EfiRuntimeServicesData, 1, &Buffer);
        if (EFI_ERROR(Status)) return DMI_ADD_STRUCTURE_FAILED;
        BufferPtr = (UINT8*)Buffer;

        // Update String;
        *(TABLE_INFO *)BufferPtr = *TableInfo;
        BufferPtr += sizeof(TABLE_INFO);

        for(i = 0; i < TableInfo->Size; ++i) {
            *BufferPtr++ = Data[i];
        }

        if (FlashDataInfo.Location) {
            UINT32     FlashDataOffset;

            // Allocate 64K GetFlashInfo buffer in SMM.
            Status = mSmst->SmmAllocatePages ( AllocateAnyPages, \
                                               EfiRuntimeServicesData, \
                                               16, \
                                               &SmmBuffer);
            if (EFI_ERROR(Status)) {
                // Free buffer and return error.
                mSmst->SmmFreePages (Buffer, 1);
                return DMI_ADD_STRUCTURE_FAILED;
            }

            ((INFO_BLOCK*)SmmBuffer)->Length = 0x10000;

            Status = mSmiFlash->GetFlashInfo((INFO_BLOCK*)SmmBuffer);

            if (Status) {
                // Free buffers and return error.
                mSmst->SmmFreePages (Buffer, 1);
                mSmst->SmmFreePages (SmmBuffer, 16);
                return DMI_ADD_STRUCTURE_FAILED;
            }

            // Initialize FUNC_BLOCK structure for SMIFlash used.
            for (i = 0, Count = 1; i < ((INFO_BLOCK*)SmmBuffer)->TotalBlocks; i++) {
                if (((UINT32)FlashDataInfo.Location - FLASH_DEVICE_BASE) > \
                        (((INFO_BLOCK*)SmmBuffer)->Blocks[i].StartAddress + \
                         ((INFO_BLOCK*)SmmBuffer)->Blocks[i].BlockSize)) continue;
                FuncBlock[0].BlockSize = \
                                ((INFO_BLOCK*)SmmBuffer)->Blocks[i].BlockSize;
                FuncBlock[0].BlockAddr = \
                                ((INFO_BLOCK*)SmmBuffer)->Blocks[i].StartAddress;

                // Check whether SmbiosFlashData exceeds the block boundary.
                if (((UINT32)gFlashData + (UINT32)FLASHDATA_SIZE - FLASH_DEVICE_BASE) > \
                    (((INFO_BLOCK*)SmmBuffer)->Blocks[i+1].StartAddress)) {
                    Count = 2;
                    FuncBlock[1].BlockSize = \
                                ((INFO_BLOCK*)SmmBuffer)->Blocks[i+1].BlockSize;
                    FuncBlock[1].BlockAddr = \
                                ((INFO_BLOCK*)SmmBuffer)->Blocks[i+1].StartAddress;
                }
                break;
            }

            // Free the GetFlashInfo buffer.
            Status = mSmst->SmmFreePages (SmmBuffer, 16);
            ASSERT_EFI_ERROR(Status);

            // Allocate the blocks buffer.
            Status = mSmst->SmmAllocatePages ( \
                                AllocateAnyPages, \
                                EfiRuntimeServicesData, \
                                (FuncBlock[0].BlockSize * Count) / 0x1000, \
                                &SmmBuffer);
            if (EFI_ERROR(Status)) {
                // Free buffer and return error.
                mSmst->SmmFreePages (Buffer, 1);
                return DMI_ADD_STRUCTURE_FAILED;
            }
            FuncBlock[0].BufAddr = SmmBuffer;
            FuncBlock[1].BufAddr = SmmBuffer + FuncBlock[0].BlockSize;

            // Read the whole SmbiosFlashData Blocks.
            for (i = 0; i < Count; i++) {
                Status = mFlash->Read((VOID*)(FuncBlock[i].BlockAddr + FLASH_DEVICE_BASE), \
                                    FuncBlock[i].BlockSize, (VOID*)FuncBlock[i].BufAddr);
                if (Status) {
                    // Free buffer and return error.
                    mSmst->SmmFreePages (Buffer, 1);

                    mSmst->SmmFreePages ( \
                                SmmBuffer, \
                                (FuncBlock[0].BlockSize * Count) / 0x1000);
                    return DMI_ADD_STRUCTURE_FAILED;
                }
            }

            // Initialize SmbiosFlashData buffer.
            for (i = 0; i < FLASHDATA_SIZE; i++, *((UINT8*)Buffer + i) = 0xff);

            // Re-collect the Smbios structures to SmbiosFlashData buffer.
            FlashDataPtr = gFlashData;
            BufferPtr = (UINT8*)Buffer;

            while((((TABLE_INFO*)FlashDataPtr)->Size != 0xffff) &&
                  (((TABLE_INFO*)FlashDataPtr)->Size != 0)) {
                if ((((TABLE_INFO*)FlashDataPtr)->Type == TableInfo->Type) && \
                    (((TABLE_INFO*)FlashDataPtr)->Handle == TableInfo->Handle) && \
                    (((TABLE_INFO*)FlashDataPtr)->Offset == TableInfo->Offset)) {
                    // Replace the structure with updated data.
                    MemCpy(BufferPtr, (UINT8*)TableInfo, sizeof(TABLE_INFO));
                    BufferSize = TableInfo->Size;
                    MemCpy (BufferPtr + sizeof(TABLE_INFO), Data, BufferSize);
                    BufferSize += sizeof(TABLE_INFO);
                } else {
                    // Copy the structure.
                    BufferSize = (((TABLE_INFO*)FlashDataPtr)->Size + sizeof(TABLE_INFO));
                    MemCpy (BufferPtr, FlashDataPtr, BufferSize);
                }

                BufferPtr += BufferSize;
                FlashDataPtr += (((TABLE_INFO*)FlashDataPtr)->Size + sizeof(TABLE_INFO));
            }

            // Copy the new SmbiosFlashData to read buffer.
            FlashDataOffset = ((UINT32)FlashDataInfo.Location - \
                                        FLASH_DEVICE_BASE - FuncBlock[0].BlockAddr);
            BufferPtr = (UINT8*)Buffer + (UINT32)FlashDataInfo.Location - (UINT32)gFlashData;
            MemCpy((UINT8*)(FuncBlock[0].BufAddr + FlashDataOffset),
                           (UINT8*)BufferPtr,
                           (UINT32)gFlashData + (UINT32)FLASHDATA_SIZE - (UINT32)FlashDataInfo.Location);

            // Write the block buffer with updated SmbiosFlashData back.
            if (!EFI_ERROR(Status)) {
                for (i = 0; i < Count; i++) {
                    Status = mFlash->Update( \
    										(VOID*)(FuncBlock[i].BlockAddr + FLASH_DEVICE_BASE), \
    										FuncBlock[i].BlockSize, (VOID*)FuncBlock[i].BufAddr
    										);
                    if (EFI_ERROR(Status)) break;
                }
    		}

            // Free the Block Buffer in SMM.
            mSmst->SmmFreePages ( SmmBuffer, \
                                  (FuncBlock[0].BlockSize * Count) / 0x1000);
        }
        else {
            UINT32 EndOfData;

            EndOfData = (UINT32)FlashDataInfo.EndOfData & 0x0ffff;

            if ((EndOfData + (UINT32)(BufferPtr - (UINT8*)Buffer)) > 0x10000) {
                UINT32 NewOffsetOfData;
                UINT32 ExtraSize;
                UINT32 DataLength;

                NewOffsetOfData = (UINT32)(((UINT32)FlashDataInfo.EndOfData & 0xffff0000) + 0x10000);
                ExtraSize = EndOfData + (UINT32)(BufferPtr - (UINT8*)Buffer) - 0x10000;
                DataLength = (UINT32)(BufferPtr - (UINT8*)Buffer);

                Status = WriteToFlash(FlashDataInfo.EndOfData,
                                    (UINT8*)Buffer,
                                    DataLength - ExtraSize);
                ASSERT_EFI_ERROR(Status);

                Status = WriteToFlash( (VOID *)NewOffsetOfData,
                                    (UINT8*)(Buffer + DataLength - ExtraSize),
                                    ExtraSize);
                ASSERT_EFI_ERROR(Status);
            }
            else {
                Status = WriteToFlash(FlashDataInfo.EndOfData,
                                    (UINT8*)Buffer,
                                    BufferPtr - (UINT8*)Buffer);
            }

            mSmst->SmmFreePages (Buffer, 1);

            if (Status) return DMI_ADD_STRUCTURE_FAILED;
        }
    }                                   // SwSmiMethod
#if defined(NonSmiDmiEdit_Support) && (NonSmiDmiEdit_Support == 1)
    else {                                          // Protocol Method
        // Determine the base block that contains the DmiEdit data
        FlashDataBlock = (UINTN)gFlashData & (0xFFFFFFFF - FLASH_BLOCK_SIZE + 1);

        // Check to see if it spans more than one block
        if (((UINTN)gFlashData + FLASHDATA_SIZE) > (FlashDataBlock + FLASH_BLOCK_SIZE)) {
            BlockCount = 2;
        }
        else {
            BlockCount = 1;
        }

        // Allocate Flash Data buffer and get the data
        // Note: additional 4K reserved for data manipulation
        pBS->AllocatePool(EfiBootServicesData, BlockCount * FLASH_BLOCK_SIZE, &DataBuffer);
        FlashProtocol->Read((UINT8*)FlashDataBlock, BlockCount * FLASH_BLOCK_SIZE, DataBuffer);

        if (FlashDataInfo.Location) {
            // Some data is already present for input type
            // Determine location of existing data
            BufferPtr = DataBuffer + \
                        (UINTN)gFlashData - FlashDataBlock + \
                        (UINTN)FlashDataInfo.Location - (UINTN)gFlashData;      // Existing DmiEdit data location

            // Calculate remaining size from the existing data location
            // to end of DmiEdit data storage block
            RemainingSize = (UINTN)FlashDataInfo.EndOfData - \
                            (UINTN)FlashDataInfo.Location - \
                            (sizeof(TABLE_INFO) + ((TABLE_INFO*)BufferPtr)->Size);

            // Copy the remaining data (without the existing data) to location
            // after input data entry insertion
            MemCpy(BufferPtr + sizeof(TABLE_INFO) + TableInfo->Size,
                    BufferPtr + sizeof(TABLE_INFO) + ((TABLE_INFO*)BufferPtr)->Size,
                    RemainingSize);

	        // In case new data size is smaller than existing one, clear old data
	        // from (EndOfData - size difference) to EndOfData to 0xff
	        if (((TABLE_INFO*)BufferPtr)->Size > TableInfo->Size) {
                UINT8   *DataEndPtr;

	            RemainingSize = ((TABLE_INFO*)BufferPtr)->Size - TableInfo->Size;
	            DataEndPtr = DataBuffer + \
	                        ((UINTN)FlashDataInfo.EndOfData - FlashDataBlock) - \
	                        RemainingSize;

	            for (i = 0; i < RemainingSize; ++i) {
	                *DataEndPtr++ = 0xff;
	            }
	        }
        }
        else {
            // Determine the end location of current DmiEdit data
            BufferPtr = DataBuffer + \
                        (UINTN)gFlashData - FlashDataBlock + \
                        (UINTN)FlashDataInfo.EndOfData - (UINTN)gFlashData;     // End of DmiEdit data
        }

        // Insert data
        *(TABLE_INFO *)BufferPtr = *TableInfo;
        BufferPtr += sizeof(TABLE_INFO);

        for(i = 0; i < TableInfo->Size; ++i) {
            *BufferPtr++ = Data[i];
        }

        // Update DmiEdit data block
        FlashProtocol->Update((UINT8*)FlashDataBlock, BlockCount * FLASH_BLOCK_SIZE, DataBuffer);

        pBS->FreePool(DataBuffer);
    }
#endif                                  // NonSmiDmiEdit_Support

    return 0;
}
#endif

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   GetSmbiosInfo
//
// Description: Returns the SMBIOS information
//
// Input:       IN OUT  GET_SMBIOS_INFO   *p
//
// Output:      Returns 0
//
// Modified:
//
// Referrals:
//
// Notes:
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
UINT16
GetSmbiosInfo(
    IN OUT  GET_SMBIOS_INFO   *p
)
{
    if (!SmbiosTableEntryPoint) return DMI_FUNCTION_NOT_SUPPORTED;
    p->DmiBiosRevision = SmbiosTableEntryPoint->SmbiosBCDRevision;
    p->NumStructures = SmbiosTableEntryPoint->NumberOfSmbiosStructures;
    p->StructureSize = SmbiosTableEntryPoint->MaxStructureSize;
    p->pDmiStorageBase = SmbiosTableEntryPoint->TableAddress;
    p->DmiStorageSize = MaximumBufferSize;

    return 0;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   GetStructureByHandle
//
// Description: Searches the structure table for a record with its handle
//              equal to the input Handle.
//              Returns the pointer to the structure if found.
//              Returns NULL if not found
//
// Input:       IN UINT16    *Handle
//
// Output:      UINT8* - Pointer to structure found
//
// Modified:
//
// Referrals:
//
// Notes:
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
UINT8*
GetStructureByHandle(
    IN UINT16    *Handle
)
{
    UINT8   *SmbiosTable = (UINT8*)((SMBIOS_TABLE_ENTRY_POINT*)SmbiosTableEntryPoint)->TableAddress;
    UINT8   *SmbiosTableEnd = SmbiosTable + ((SMBIOS_TABLE_ENTRY_POINT*)SmbiosTableEntryPoint)->TableLength;
    UINT8   *SmbiosTableNext;

    while(SmbiosTable < SmbiosTableEnd && ((SMBIOS_STRUCTURE_HEADER*)SmbiosTable)->Type != 127) {
        SmbiosTableNext = SmbiosTable + GetStructureLength(SmbiosTable);
        if (((SMBIOS_STRUCTURE_HEADER*)SmbiosTable)->Handle == *Handle) {
            return SmbiosTable;
        }
        SmbiosTable = SmbiosTableNext;
    }
    return NULL;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   GetStructureByHandleThenUpdateHandle
//
// Description: Searches the structure table for a record with its handle
//              equal to the input Handle.
//              Returns the pointer to the structure if found.
//              Returns NULL if not found
//
// Input:       IN UINT16    *Handle
//
// Output:      UINT8* - Pointer to structure found
//              Sets Handle to the handle of the next structure
//
// Modified:
//
// Referrals:
//
// Notes:
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
UINT8*
GetStructureByHandleThenUpdateHandle(
    IN UINT16    *Handle
)
{
    UINT8   *SmbiosTable = (UINT8*)((SMBIOS_TABLE_ENTRY_POINT*)SmbiosTableEntryPoint)->TableAddress;
    UINT8   *SmbiosTableEnd = SmbiosTable + ((SMBIOS_TABLE_ENTRY_POINT*)SmbiosTableEntryPoint)->TableLength;
    UINT8   *SmbiosTableNext;

    if (*Handle == 0) {
        SmbiosTableNext = SmbiosTable + GetStructureLength(SmbiosTable);
        if (SmbiosTableNext >= SmbiosTableEnd) *Handle = 0xffff;  //Last handle?
        else *Handle = ((DMI_STRUC*)SmbiosTableNext)->Handle;     //Return next handle
        return SmbiosTable;
    }

    while(SmbiosTable < SmbiosTableEnd) {
        SmbiosTableNext = SmbiosTable + GetStructureLength(SmbiosTable);
        if (((DMI_STRUC*)SmbiosTable)->Handle == *Handle) {
            if (SmbiosTableNext >= SmbiosTableEnd || ((DMI_STRUC*)SmbiosTable)->Type == 127 ) *Handle = 0xffff;  //Last handle?
            else *Handle = ((DMI_STRUC*)SmbiosTableNext)->Handle;     //Return next handle
            return SmbiosTable;
        }

        SmbiosTable = SmbiosTableNext;
    }

  return NULL;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   GetSmbiosStructure
//
// Description: Searches the structure table for a record with its handle
//              equal to the input Handle and copies its content into
//              the provided buffer.
//
// Input:       IN OUT  GET_SMBIOS_STRUCTURE    *p
//
// Output:      GET_SMBIOS_STRUCTURE* - Input pointer "p" is loaded with
//                                      structure data.
//
// Modified:
//
// Referrals:
//
// Notes:
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
UINT16
GetSmbiosStructure(
    IN OUT  GET_SMBIOS_STRUCTURE    *p
)
{
    UINT8     *SmbStructurePtr;
    UINT32    TableSize;
    UINT8     *src, *dest;

    if (!SmbiosTableEntryPoint) return DMI_FUNCTION_NOT_SUPPORTED;

    SmbStructurePtr = GetStructureByHandleThenUpdateHandle((UINT16*)p->Handle32BitAddr);
    if (!SmbStructurePtr) return DMI_INVALID_HANDLE;

    TableSize = GetStructureLength(SmbStructurePtr);

    src = SmbStructurePtr;
    dest = (UINT8*)p->Buffer32BitAddr;
    while(TableSize--) *dest++ = *src++;  //Copy Table

    return 0;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   GetStructureLength
//
// Description: Returns the length of the structure pointed by BufferStart
//              in bytes
//
// Input:       IN UINT8     *BufferStart
//
// Output:      UINT16 - Size of the structure
//
// Modified:
//
// Referrals:
//
// Notes:
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
UINT16
GetStructureLength(
    IN UINT8     *BufferStart
)
{
    UINT8       *BufferEnd = BufferStart;

    BufferEnd += ((SMBIOS_STRUCTURE_HEADER*)BufferStart)->Length;

    while(*(UINT16*)BufferEnd != 0) {
        BufferEnd++;
    }

    return (UINT16)(BufferEnd + 2 - BufferStart);   // +2 for double zero terminator
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   GetInstanceByTypeHandle
//
// Description: Returns the instance of the input structure type and its handle
//
// Input:       IN UINT8    Type
//              IN UINT16   Handle
//
// Output:      Instance number (1-based) if found, or 0 if not found
//
// Modified:
//
// Referrals:
//
// Notes:
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
UINT8
GetInstanceByTypeHandle(
    IN UINT8    Type,
    IN UINT16   Handle
)
{
    UINT8   *Table = (UINT8*)((SMBIOS_TABLE_ENTRY_POINT*)SmbiosTableEntryPoint)->TableAddress;
    UINT8   *TableEnd = Table + ((SMBIOS_TABLE_ENTRY_POINT*)SmbiosTableEntryPoint)->TableLength;
    UINT8   Instance = 0;		// 1-based

    while ((Table < TableEnd) && ((SMBIOS_STRUCTURE_HEADER*)Table)->Type != 127) {
        if (((SMBIOS_STRUCTURE_HEADER*)Table)->Type == Type) {
        	Instance ++;
        }

        if (((SMBIOS_STRUCTURE_HEADER*)Table)->Handle == Handle) {
            return Instance;
        }

        Table = Table + GetStructureLength(Table);
    }

    return 0;					// Not found
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   FindStructureType
//
// Description: Find structure type starting from memory location pointed by
//              Buffer
//
// Input:       IN OUT  UINT8   **Buffer
//              IN OUT  UINT8   **StructureFoundPtr
//              IN      UINT8   SearchType
//              IN      UINT8   Instance
//
// Output:
//              BOOLEAN
//                  TRUE  - Structure found
//                  FALSE - Structure not found
//
//              If SearchType is found:
//                UINT8   **Buffer - Points to the next structure
//                UINT8   **StructureFoundPtr - Points to the structure
//                                              that was found
//              If SearchType is not found:
//                UINT8   **Buffer - No change
//                UINT8   **StructureFoundPtr = NULL
//
// Modified:
//
// Referrals:
//
// Notes:
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
BOOLEAN
FindStructureType(
    IN OUT UINT8    **Buffer,
    IN OUT UINT8    **StructureFoundPtr,
	IN     UINT8    SearchType,
    IN     UINT8    Instance        // 1-based
)
{
    UINT8       *BufferPtr = *Buffer;
    BOOLEAN     FindStatus = FALSE;

    *StructureFoundPtr = NULL;
    while (((SMBIOS_STRUCTURE_HEADER*)BufferPtr)->Type != 127) {
        if (((SMBIOS_STRUCTURE_HEADER*)BufferPtr)->Type == SearchType) {
            // If this instance, set the find status flag and update the Buffer pointer
            if (--Instance == 0) {
                FindStatus = TRUE;
                *StructureFoundPtr = BufferPtr;
                *Buffer = BufferPtr + GetStructureLength(BufferPtr);
                break;
            }
        }
        BufferPtr += GetStructureLength(BufferPtr);
    }
    if ((FindStatus == FALSE) & (SearchType == 127)) {
        FindStatus = TRUE;
        *StructureFoundPtr = BufferPtr;
        *Buffer = BufferPtr + GetStructureLength(BufferPtr);
    }
    return FindStatus;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   GetStringTableIndex
//
// Description: Returns the string array index for a given Offset in
//              structure pointed by input StringTablePtr
//
// Input:       STRING_TABLE    *StringTablePtr
//              IN UINT8        Offset
//
// Output:      UINT8 - String array index
//
// Modified:
//
// Referrals:
//
// Notes:
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
UINT8
GetStringTableIndex(
    STRING_TABLE    *StringTablePtr,
    IN UINT8        Offset
)
{
    UINT8       i;

    for (i = 0; StringTablePtr->Offset != 0xff; i++) {
        if (StringTablePtr->Offset == Offset) break;
        StringTablePtr++;
    }

    return i;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   StrLen
//
// Description: Returns the length of an input string
//
// Input:       IN CHAR8    *Str
//
// Output:      UINT8 - Length of the string (without zero terminator)
//
// Modified:
//
// Referrals:
//
// Notes:
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
UINT16
StrLen(
	IN CHAR8    *Str
)
{
	UINT16  Length = 0;

	while (*Str++) Length++;

	return Length;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   GetRemainingStructuresSize
//
// Description: Return the size from the Pointer Buffer to the last
//              structure 127.
//
// Input:       IN UINT8    *Buffer
//
// Output:      Size of remaining structure
//
// Modified:
//
// Referrals:
//
// Notes:
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
UINT16
GetRemainingStructuresSize(
    IN UINT8  *Buffer
)
{
    UINT16  Length = 0;
    UINT16  BlockSize;

    while (((SMBIOS_STRUCTURE_HEADER*)Buffer)->Type != 127) {
        BlockSize = GetStructureLength(Buffer);
        Length += BlockSize;
        Buffer += BlockSize;
    }
    Length += GetStructureLength(Buffer);
    return Length;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   SmbiosCheckSum
//
// Description: Returns the checksum of "length" bytes starting from the
//              "*ChecksumSrc"
//
// Input:       IN UINT8    *ChecksumSrc
//              IN UINT8    length
//
// Output:      UINT8 - Checksum value
//
// Modified:
//
// Referrals:
//
// Notes:
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
UINT8
SmbiosCheckSum(
    IN UINT8    *ChecksumSrc,
    IN UINT8    length
)
{
    UINT8     Checksum = 0;
    UINT8     i;

    for (i= 0; i < length; i++) {
        Checksum += *ChecksumSrc++;
    }
    return (0 - Checksum);
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   GetLargestStructureSize
//
// Description: Returns the largest structure size
//
// Input:       IN UINT8    *Buffer
//
// Output:      UINT16 - Largest structure size
//
// Modified:
//
// Referrals:
//
// Notes:
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
UINT16
GetLargestStructureSize(
    IN UINT8     *Buffer
)
{
    UINT8     *BufferPtr = Buffer;
    UINT16    LargestStructureSize = 0;
    UINT16    CurrentStructureSize;

    while (((SMBIOS_STRUCTURE_HEADER*)BufferPtr)->Type != 127) {
        UINT8     *LastBufferPtr;

        LastBufferPtr = BufferPtr;
        BufferPtr += ((SMBIOS_STRUCTURE_HEADER*)BufferPtr)->Length;
        while(TRUE) {
            if ((*(UINT16*)BufferPtr) == 0) {
                BufferPtr += 2;
                break;
            }
            BufferPtr++;
        }
        CurrentStructureSize = (UINT16)(BufferPtr - LastBufferPtr);
        if (CurrentStructureSize > LargestStructureSize) {
            LargestStructureSize = CurrentStructureSize;
        }
    }
    return LargestStructureSize;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   UpdateHeaderInfo
//
// Description: Updates SMBIOS Entry Point Header
//
// Input:       None
//
// Output:      None
//
// Modified:
//
// Referrals:
//
// Notes:
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID
UpdateHeaderInfo(VOID)
{
    SmbiosTableEntryPoint->TableLength = GetRemainingStructuresSize((UINT8*)SmbiosTableEntryPoint->TableAddress);
    SmbiosTableEntryPoint->IntermediateChecksum = 0;
    SmbiosTableEntryPoint->IntermediateChecksum = SmbiosCheckSum((UINT8*)SmbiosTableEntryPoint + 0x10, 15);
    SmbiosTableEntryPoint->MaxStructureSize = GetLargestStructureSize((UINT8*)SmbiosTableEntryPoint->TableAddress);
    SmbiosTableEntryPoint->EntryPointStructureChecksum = 0;
    SmbiosTableEntryPoint->EntryPointStructureChecksum = SmbiosCheckSum((UINT8*)SmbiosTableEntryPoint,
                                                                          SmbiosTableEntryPoint->EntryPointLength);
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   GetTypeTable
//
// Description: Return pointer to the input type string table
//
// Input:       IN UINT8      Structure Type
//
// Output:      Pointer to the input type string table
//              (or NULL if not found)
//
// Modified:
//
// Referrals:
//
// Notes:
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID*
GetTypeTable(
    IN UINT8    StructType
)
{
    UINT8       Index;

    switch (StructType) {
        case    0:
        case    1:
        case    2:
        case    3:
        case    4:  Index = StructType;
                    break;
        case   22:  Index = 5;
                    break;
        case   39:  Index = 6;
                    break;
        default:    Index = 0xff;
    }

    if (Index != 0xff) {
        return StringTable[Index];
    }
    else {
        return NULL;
    }
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   GetStringOffset
//
// Description: Returns the string offset for StringNumber from input string
//              buffer BufferStart
//
// Input:       IN  UINT8   *BufferStart
//              IN  UINT8   StringNumber (1-based)
//
// Output:      UINT16 - Offset from BufferStart
//
// Modified:
//
// Referrals:
//
// Notes:
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
UINT16
GetStringOffset(
    IN UINT8    *BufferStart,
    IN UINT8    StringNumber          // 1-based
)
{
    UINT8       *BufferEnd = BufferStart;

    while (--StringNumber) {
        while(*BufferEnd != 0) {
            BufferEnd++;
        }
        BufferEnd++;
    }

    return (UINT16)(BufferEnd - BufferStart);
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   FindString
//
// Description: Returns pointer to the string number in structure BufferPtr
//
// Input:       IN OUT  UINT8    **BufferPtr
//              IN      UINT8    StringNumber
//
// Output:      UINT8   *BufferPtr = Pointer to the #StringNumber string
//
// Modified:
//
// Referrals:
//
// Notes:
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
BOOLEAN
FindString(
    IN OUT UINT8    **BufferPtr,
    IN     UINT8    StringNumber          // 1-based
)
{
    *BufferPtr += ((SMBIOS_STRUCTURE_HEADER*)*BufferPtr)->Length;
    *BufferPtr += GetStringOffset(*BufferPtr, StringNumber);
    return TRUE;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   FindLargestStrNumber
//
// Description: Return the largest string number in a structure
//
// Input:       IN UINT8    *StructPtr
//              IN UINT8    *StrTablePtr
//
// Output:      String number (1-based)
//              (or 0 if not found)
//
// Modified:
//
// Referrals:
//
// Notes:
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
UINT8
FindLargestStrNumber (
    IN UINT8            *StructPtr,
    IN STRING_TABLE     *StrTablePtr
)
{
    UINT8       Number;
    UINT8       StrNumber = 0;

    // Find largest string number from structure
    while (StrTablePtr->Offset != 0xff) {
        Number = *(StructPtr + StrTablePtr->Offset);
        if (Number > StrNumber) {
            StrNumber = Number;
        }
        StrTablePtr++;
    }

    return StrNumber;       // 1-based
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   GetStrNumber
//
// Description: Return the string number for a structure "Type" at "Offset"
//
// Input:       IN UINT8    Pointer to structure
//              IN UINT8    Type
//              IN UINT8    Offset
//
// Output:      String number (1-based)
//              (or 0xff if not found)
//
// Modified:
//
// Referrals:
//
// Notes:
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
UINT8
GetStrNumber(
    IN  UINT8       *StructPtr,
    IN  UINT8       Type,
    UINT8           Offset
)
{
    UINT8       *NextStructPtr = StructPtr;
    UINT8       *TempPtr;

    if (FindStructureType(&NextStructPtr, &TempPtr, Type, 1)) {
        return *(TempPtr + Offset);
    }
    else {
        return 0xff;
    }
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   DeleteStringNumber
//
// Description: Zero out the string number in StructPtr
//
// Input:       IN  UINT8   *StructurePtr
//              IN UINT8    StrNumber
//
// Output:      None
//
// Modified:
//
// Referrals:
//
// Notes:
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID
DeleteStringNumber (
    IN UINT8    *StructPtr,
    IN UINT8    StrNumber
)
{
    UINT8           Number;
    STRING_TABLE    *StrTablePtr;

    StrTablePtr = GetTypeTable(((SMBIOS_STRUCTURE_HEADER*)StructPtr)->Type);

    while (StrTablePtr->Offset != 0xff) {
        Number = *(StructPtr + StrTablePtr->Offset);
        if (Number > StrNumber) {
            *(StructPtr + StrTablePtr->Offset) = Number - 1;
        }
        if (Number == StrNumber) {
            *(StructPtr + StrTablePtr->Offset) = 0;
        }
        StrTablePtr++;
    }
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   DeleteString
//
// Description: Delete string at Offset
//
// Input:       IN  UINT8   *StructPtr
//              IN UINT8    Offset
//
// Output:      None
//
// Modified:
//
// Referrals:
//
// Notes:
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID
DeleteString (
    IN UINT8            *StructPtr,
    IN UINT8            Offset
)
{
    UINT8       StrNumber;
    UINT8       *TempPtr;
    UINT8       *StructEndPtr;
    UINTN       RemainingSize;

    StrNumber = GetStrNumber(StructPtr, ((SMBIOS_STRUCTURE_HEADER*)StructPtr)->Type, Offset);

    // Delete string number
    DeleteStringNumber(StructPtr, StrNumber);

    FindString(&StructPtr, StrNumber);              // StructPtr = StrNumber string
    TempPtr = StructPtr + StrLen(StructPtr) + 1;    // Move pointer to next string

    // Find end of structure
    StructEndPtr = TempPtr;
    while(*(UINT16*)StructEndPtr != 0) {
        StructEndPtr++;
    }

    // Copy remaining strings
    RemainingSize = StructEndPtr + 2 - TempPtr;     // Including double NULL characters
    MemCpy(StructPtr, TempPtr, RemainingSize);
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   ReplaceString
//
// Description: Replace the #StringNum in the input buffer *DestStructPtr
//              with StringData
//
// Input:       IN UINT8       *DestStructPtr  Pointer to structure to be updated
//              IN UINT8       StringNum       String number (1 based)
//              IN UINT8       *StringData     String with NULL terminated character
//
// Output:      EFI_STATUS
//
// Modified:
//
// Referrals:
//
// Notes:
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS
ReplaceString(
    IN UINT8    *DestStructPtr,
    IN UINT8    StringNum,
    IN UINT8    *StringData
)
{
    UINT8       StringSize = 0;
    UINT8       *TempPtr;
    UINT8       *NextStrPtr;
    UINT8       *StructEndPtr;
    UINTN       RemainingSize;

    FindString(&DestStructPtr, StringNum);
    NextStrPtr = DestStructPtr;
    StructEndPtr = DestStructPtr;

    while(*NextStrPtr != 0) {
        NextStrPtr++;
    }

    // NextStrPtr = Pointer to the next string
    NextStrPtr++;

    while(*(UINT16*)StructEndPtr != 0) {
        StructEndPtr++;
    }

    RemainingSize = StructEndPtr + 2 - NextStrPtr;  // Including double NULL characters

    TempPtr = StringData;
    while (*(TempPtr++) != 0) {
        StringSize++;
    }
    StringSize++;                   // Including NULL character

    // Copy remaining strings
    MemCpy(DestStructPtr + StringSize, NextStrPtr, RemainingSize);

    // Copy the string
    MemCpy(DestStructPtr, StringData, StringSize);

    return EFI_SUCCESS;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   AddStringNumber
//
// Description: Add new string number for a structure "Type" at "Offset".
//              Return the string index, assuming all strings exist in the
//              structure according to the Smbios specification
//
// Input:       IN UINT8    Pointer to SmbiosTable or Structure
//              IN UINT8    Type
//              IN UINT8    Offset
//
// Output:      String index (0-based)
//              (0xff if not found)
//
// Modified:
//
// Referrals:
//
// Notes:
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
UINT8
AddStringNumber(
    IN  UINT8       *SmbiosTable,
    IN  UINT8       Type,
    UINT8           Offset
)
{
    STRING_TABLE    *StrTablePtr;
    UINT8           *NextStructPtr = SmbiosTable;
    UINT8           *TempPtr;
    UINT8           Index = 0xff;
    UINT8           StrNumber = 0;
    UINT8           Number;

    if (FindStructureType(&NextStructPtr, &TempPtr, Type, 1)) {
        StrTablePtr = GetTypeTable(Type);
        if (StrTablePtr != NULL) {
            // Find largest string number from structure
            while (StrTablePtr->Offset != 0xff) {
                if (StrTablePtr->Offset == Offset) {
                    // String index in Smbios spec
                    Index = StrTablePtr->SpecStrNum - 1;        // 0-based
                }

                Number = *(TempPtr + StrTablePtr->Offset);
                if (Number > StrNumber) {
                    StrNumber = Number;
                }
                StrTablePtr++;
            }

            // Assign next string number to structure at input Offset
            *(TempPtr + Offset) = ++StrNumber;

            return Index;           // 0-based
        }
    }

    return 0xff;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   AddNullTerminator
//
// Description: Add NULL terminator to the end of the structure
//
// Input:       IN UINT8   *StructPtr
//              IN UINT8   *StrTablePtr
//
// Output:      None
//
// Modified:
//
// Referrals:
//
// Notes:
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID
AddNullTerminator (
    IN UINT8            *StructPtr,
    IN STRING_TABLE     *StrTablePtr
)
{
    UINT8       StrNumber;
    UINT8       i;

    // Find largest string number
    StrNumber = FindLargestStrNumber(StructPtr, StrTablePtr);

    // Skip to string section
    StructPtr += ((SMBIOS_STRUCTURE_HEADER*)StructPtr)->Length;

    // Move pointer to end of last string
    for (i = 0; i < StrNumber; i++) {
        while (*StructPtr != NULL) StructPtr++;
        StructPtr++;
    }

    // Add NULL terminator
    *StructPtr = 0;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   UpdateStrings
//
// Description: Updates strings in SMBIOS Structure with input Handle
//              in Runtime with DMI data
//
// Input:       IN UINT16      Handle,
//              IN TABLE_INFO  TableInfo,
//              IN UINT8       *Data
//
// Output:      UINT8 - Status
//
// Modified:
//
// Referrals:
//
// Notes:
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
UINT16
UpdateStrings(
    IN UINT16           Handle,
    IN TABLE_INFO       TableInfo,
    IN UINT8            *Data
)
{
    UINT8               *TablePtr;
    UINT8               *TempBuffer;
    UINT8               *StructPtr;
    UINT8               i;
    UINT16              BlockSize;
    UINT16              AvailableBlkSize;
    STRING_TABLE        *StrTablePtr;
    UINT8               StrNumber;
    UINT8               Instance;

    // Check if enough space
    AvailableBlkSize = MaximumBufferSize - SmbiosTableEntryPoint->TableLength;
    if (AvailableBlkSize < (StrLen(Data) + 1)) {
        return DMI_BAD_PARAMETER;               // Not enough space
    }

    // Get pointer to structure to be updated
    StructPtr = GetStructureByHandle(&Handle);
    if (StructPtr == NULL) {
        return DMI_INVALID_HANDLE;
    }

    // Get pointer to the StringTable
    StrTablePtr = GetTypeTable(((SMBIOS_STRUCTURE_HEADER*)StructPtr)->Type);
    if (((SMBIOS_STRUCTURE_HEADER*)StructPtr)->Type == 3) {
        Instance = GetInstanceByTypeHandle(3, Handle);
        StrTablePtr += 6 * (Instance - 1);
    }

    if (StrTablePtr == NULL) return DMI_BAD_PARAMETER;

    // Copy structure data
    TempBuffer = ScratchBufferPtr;
    BlockSize = GetStructureLength(StructPtr);
    MemCpy(TempBuffer, StructPtr, BlockSize);

    // Set TablePtr to next structure
    TablePtr = StructPtr + BlockSize;


    // Update String fields
    for (i = 0; StrTablePtr[i].Offset != 0xff; i++) {
        // Update string at input Offset
        if (StrTablePtr[i].Offset == TableInfo.Offset) {
            // Update string if input data not empty, else delete it
            if (StrLen(Data)) {
                BlockSize = StrLen(Data) + 1;
                // Add string if does not exist, else replace it
                StrNumber = GetStrNumber(TempBuffer, TableInfo.Type, TableInfo.Offset);
                if (StrNumber == 0) {
                    AddStringNumber(TempBuffer, TableInfo.Type, TableInfo.Offset);
                    StrNumber = GetStrNumber(TempBuffer, TableInfo.Type, TableInfo.Offset);
                }
                ReplaceString(TempBuffer, StrNumber, Data);
            }
            else {
                DeleteString(TempBuffer, TableInfo.Offset);
            }
        }
    }

    // Add structure terminator Null byte
    AddNullTerminator(TempBuffer, StrTablePtr);

    BlockSize = GetRemainingStructuresSize(TablePtr);
    MemCpy(TempBuffer + GetStructureLength(TempBuffer), TablePtr, BlockSize);

    // Replace all DMI data with TempBuffer
    TempBuffer = ScratchBufferPtr;
    BlockSize = GetRemainingStructuresSize(TempBuffer);
    MemCpy(StructPtr, TempBuffer, BlockSize);

    // Update SMBIOS Structure Table Entry Point - Structure Table Length, Intermediate checksum
    UpdateHeaderInfo();

    return DMI_SUCCESS;
}

#if OEM_STRING_INFO
//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   DynamicUpdateType11
//
// Description: Updates SMBIOS Type 11 Structure in Runtime with DMI data
//
// Input:       IN UINT16      Handle,
//              IN TABLE_INFO  TableInfo,
//              IN UINT8       *Data
//
// Output:      UINT8 - Status
//
// Modified:
//
// Referrals:
//
// Notes:
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
UINT8
DynamicUpdateType11(
    IN UINT16      Handle,
    IN TABLE_INFO  TableInfo,
    IN UINT8       *Data
)
{
    UINT8               *TablePtr;
    UINT8               *TempBuffer;
    UINT8               *StructPtr;
    UINT16              BlockSize;
    UINT16              StringSize;
    UINT8               i;
    UINT16              AvailableBlkSize;
    UINT8               Count;

    StructPtr = GetStructureByHandle(&Handle);
    if (StructPtr == NULL) {
        return DMI_INVALID_HANDLE;
    }

    TablePtr = StructPtr;
    TempBuffer = ScratchBufferPtr;

    AvailableBlkSize = MaximumBufferSize - SmbiosTableEntryPoint->TableLength;
    if (AvailableBlkSize < (StrLen(Data) + 1)) {
        return DMI_BAD_PARAMETER;               // Not enough space
    }

    // Copy structure data (without string data)
    BlockSize = ((SMBIOS_STRUCTURE_HEADER*)TablePtr)->Length;
    MemCpy(TempBuffer, TablePtr, BlockSize);
    Count = ((SMBIOS_OEM_STRINGS_INFO*)TempBuffer)->Count;

    TablePtr += BlockSize;
    TempBuffer += BlockSize;

    // string fields
    for (i = 1; i < (Count + 1); i++) {
        StringSize = StrLen(TablePtr) + 1;       // Size including string NULL terminator
        if (TableInfo.Offset == i) {
            BlockSize = StrLen(Data) + 1;
            MemCpy(TempBuffer, Data, BlockSize);
            TempBuffer += BlockSize;
        }
        else {
            MemCpy(TempBuffer, TablePtr, StringSize);
            TempBuffer += StringSize;
        }
        TablePtr += StringSize;
    }

    // Add NULL byte for end of string-set
    *TempBuffer = 0;
    TempBuffer++;
    TablePtr++;

    BlockSize = GetRemainingStructuresSize(TablePtr);
    MemCpy(TempBuffer, TablePtr, BlockSize);

    // Replace all DMI data with TempBuffer
    TempBuffer = ScratchBufferPtr;
    BlockSize = GetRemainingStructuresSize(TempBuffer);
    MemCpy(StructPtr, TempBuffer, BlockSize);

    // Update SMBIOS Structure Table Entry Point - Structure Table Length, Intermediate checksum
    UpdateHeaderInfo();

    return DMI_SUCCESS;
}
#endif

#if SYSTEM_CONFIG_OPTION_INFO
//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   DynamicUpdateType12
//
// Description: Updates SMBIOS Type 12 Structure in Runtime with DMI data
//
// Input:       IN UINT16      Handle,
//              IN TABLE_INFO  TableInfo,
//              IN UINT8       *Data
//
// Output:      UINT8 - Status
//
// Modified:
//
// Referrals:
//
// Notes:
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
UINT8
DynamicUpdateType12(
    IN UINT16      Handle,
    IN TABLE_INFO  TableInfo,
    IN UINT8       *Data
)
{
    UINT8               *TablePtr;
    UINT8               *TempBuffer;
    UINT8               *StructPtr;
    UINT16              BlockSize;
    UINT16              StringSize;
    UINT8               i;
    UINT16              AvailableBlkSize;
    UINT8               Count;

    StructPtr = GetStructureByHandle(&Handle);
    if (StructPtr == NULL) {
        return DMI_INVALID_HANDLE;
    }

    TablePtr = StructPtr;
    TempBuffer = ScratchBufferPtr;

    AvailableBlkSize = MaximumBufferSize - SmbiosTableEntryPoint->TableLength;
    if (AvailableBlkSize < (StrLen(Data) + 1)) {
        return DMI_BAD_PARAMETER;               // Not enough space
    }

    // Copy structure data (without string data)
    BlockSize = ((SMBIOS_STRUCTURE_HEADER*)TablePtr)->Length;
    MemCpy(TempBuffer, TablePtr, BlockSize);
    Count = ((SMBIOS_SYSTEM_CONFIG_INFO*)TempBuffer)->Count;

    TablePtr += BlockSize;
    TempBuffer += BlockSize;

    // string fields
    for (i = 1; i < (Count + 1); i++) {
        StringSize = StrLen(TablePtr) + 1;       // Size including string NULL terminator
        if (TableInfo.Offset == i) {
            BlockSize = StrLen(Data) + 1;
            MemCpy(TempBuffer, Data, BlockSize);
            TempBuffer += BlockSize;
        }
        else {
            MemCpy(TempBuffer, TablePtr, StringSize);
            TempBuffer += StringSize;
        }
        TablePtr += StringSize;
    }

    // Add NULL byte for end of string-set
    *TempBuffer = 0;
    TempBuffer++;
    TablePtr++;

    BlockSize = GetRemainingStructuresSize(TablePtr);
    MemCpy(TempBuffer, TablePtr, BlockSize);

    // Replace all DMI data with TempBuffer
    TempBuffer = ScratchBufferPtr;
    BlockSize = GetRemainingStructuresSize(TempBuffer);
    MemCpy(StructPtr, TempBuffer, BlockSize);

    // Update SMBIOS Structure Table Entry Point - Structure Table Length, Intermediate checksum
    UpdateHeaderInfo();

    return DMI_SUCCESS;
}
#endif

/////////////////////////////////////////////
// Worker function for setting structures. //
/////////////////////////////////////////////

#if !defined(SMBIOS_DMIEDIT_DATA_LOC) || SMBIOS_DMIEDIT_DATA_LOC == 2
//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   StoreNvramData
//
// Description: Store DMIEdit data into input variable
//
// Input:       IN  CHAR16  *Var
//              IN  VOID    *Data
//              IN  UINTN   DataSize
//
//              Global variable "DmiArray", "DmiArraySize",
//
// Output:      UINT8 - Status
//
// Modified:
//
// Referrals:
//
// Notes:
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS
StoreNvramData(
    IN  CHAR16  *Var,
    IN  VOID    *Data,
    IN  UINTN   DataSize
)
{
    EFI_STATUS  Status;
    UINTN       Size;
    UINT8       *Buffer;

	// Check if variable already exists
    //
    // Size of zero is used to detect if the variable exists.
    // If the variable exists, an error code of EFI_BUFFER_TOO_SMALL
    // would be returned
    Size = 0;
    Status = pRS->GetVariable(
                        Var,
                        &EfiSmbiosNvramGuid,
                        NULL,
                        &Size,
                        &Buffer);

    if (Status == EFI_NOT_FOUND) {
		// Record not present, increment record count
        DmiArray[0].Type += 1;

        Status = pRS->SetVariable(
                            DmiArrayVar,
                            &EfiSmbiosNvramGuid,
                            EFI_VARIABLE_RUNTIME_ACCESS | EFI_VARIABLE_BOOTSERVICE_ACCESS | EFI_VARIABLE_NON_VOLATILE,
                            DmiArraySize,
                            &DmiArray);
        ASSERT_EFI_ERROR(Status);
    }

	// Update DMI data record if already exists,
	// or store new record if total record count in DmiArray was successfully
	// updated
    if (Status == EFI_BUFFER_TOO_SMALL || Status == EFI_SUCCESS) {
	    Status = pRS->SetVariable(
	                        Var,
	                        &EfiSmbiosNvramGuid,
	                        EFI_VARIABLE_RUNTIME_ACCESS | EFI_VARIABLE_BOOTSERVICE_ACCESS | EFI_VARIABLE_NON_VOLATILE,
                            DataSize,
	                        Data);
	    ASSERT_EFI_ERROR(Status);
	}

    return Status;
}
#endif

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   GetDmiDataSize
//
// Description: Returns the data size for DMI Function 0x52
//
// Input:       IN SET_SMBIOS_STRUCTURE_DATA   *Data,
//
// Output:      UINT16 - Data Size
//
// Modified:
//
// Referrals:
//
// Notes:
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
UINT16
GetDmiDataSize(
    IN SET_SMBIOS_STRUCTURE_DATA   *Data
)
{
    switch(Data->Command) {
        case 0:
                return 1;
        case 1:
                return 2;
        case 2:
                return 4;
        case 4:
                return 0;                   // Delete command, size does not matter
        default:
                return Data->DataLength;    // Add, String, or Block change command
    }
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   GetInputDataInfo
//
// Description: Fills "TableInfo" with data from DMI Function 0x52
//
// Input:       IN      UINT16                      Handle,
//              IN      SET_SMBIOS_STRUCTURE_DATA   *Data,
//              IN OUT  TABLE_INFO                  *TableInfo
//
// Output:      UINT16 - Data Size
//
// Modified:
//
// Referrals:
//
// Notes:
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID
GetInputDataInfo(
    IN      UINT16                      Handle,
    IN      SET_SMBIOS_STRUCTURE_DATA   *Data,
    IN OUT  TABLE_INFO                  *TableInfo
)
{
    TableInfo->Type = Data->StructureHeader.Type;
    TableInfo->Offset = Data->FieldOffset;
    TableInfo->Reserved = 0;
    TableInfo->Flags = DMIEDIT_EXTENDED_HDR;
    TableInfo->HdrLength = sizeof(TABLE_INFO);
    TableInfo->Size = GetDmiDataSize(Data);
    TableInfo->Handle = Handle;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   SetType0
//
// Description: Updates Flash Data record with input DMI data
//              Updates SMBIOS Type 0 Structure in Runtime with DMI data
//
// Input:       IN UINT16                      Handle,
//              IN SET_SMBIOS_STRUCTURE_DATA   *Data,
//              IN BOOLEAN                     Set
//
// Output:      UINT8 - Status
//
// Modified:
//
// Referrals:
//
// Notes:       Type 0 Offset 8 (Release Date) is a fixed form string. This
//              function only checks for proper length. It is up to the DMI
//              editing utility to check for the proper format.
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
UINT16
SetType0(
    IN UINT16                      Handle,
    IN SET_SMBIOS_STRUCTURE_DATA   *Data,
    IN BOOLEAN                     Set
)
{
    EFI_STATUS  Status;
    TABLE_INFO  TableInfo;

    if (Data->Command != 5) return DMI_BAD_PARAMETER;

    if ( Data->FieldOffset != 4
      && Data->FieldOffset != 5
      && Data->FieldOffset != 8
    ) return DMI_BAD_PARAMETER;

    if ((Data->FieldOffset == 8) && (Data->DataLength != 11)) {
        return DMI_BAD_PARAMETER; // Date string is fixed size
    }

    if (Set == FALSE) return DMI_SUCCESS;

    if (isWriteOnce(0, Data->FieldOffset, Handle)) return DMI_READ_ONLY;

    // Fill TableInfo with input data
    GetInputDataInfo(Handle, Data, &TableInfo);

#if !defined(SMBIOS_DMIEDIT_DATA_LOC) || SMBIOS_DMIEDIT_DATA_LOC != 2

    Status = UpdateSmbiosTable(&TableInfo, Data->StructureData);

#else
{
	//
	// Get number of DMI data records in NVRAM
	//
	// Note: DMI data record actually starts with record #1,
	//		 first record #0 holds total number of DMI data records
	//       instead of TABLE_INFO
	//       ===> DmiArray[0].Type = count
	//
    Status = pRS->GetVariable(
                        DmiArrayVar,
                        &EfiSmbiosNvramGuid,
                        NULL,
                        &DmiArraySize,
                        &DmiArray);

	if (Status == EFI_SUCCESS) {
	    Index = DmiArray[0].Type;	// Note: DmiArray[0] has count # instead of Type/Offset
	    ++Index;
	}
	else {
		Index = 1;
	}

    DmiArray[Index].Type = 0;
    DmiArray[Index].Handle = Handle;
    DmiArray[Index].Offset = Data->FieldOffset;
    DmiArray[Index].Flags = 0;

    Swprintf(Var, L"DmiVar%02x%04x%02x%02x",
			   DmiArray[Index].Type,
			   DmiArray[Index].Handle,
			   DmiArray[Index].Offset,
			   DmiArray[Index].Flags);

    if (Set == FALSE) return DMI_SUCCESS;

    Status = StoreNvramData(Var, &Data->StructureData, (UINTN)TableInfo.Size);
}
#endif

    if (Status) {
        return (UINT16)Status;
    }

    // Dynamically update strings in Smbios table
    return UpdateStrings(Handle, TableInfo, Data->StructureData);
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   SetType1
//
// Description: Updates Flash Data record with input DMI data
//              Updates SMBIOS Type 1 Structure in Runtime with DMI data
//
// Input:       IN UINT16                      Handle,
//              IN SET_SMBIOS_STRUCTURE_DATA   *Data,
//              IN BOOLEAN                     Set
//
// Output:      UINT8 - Status
//
// Modified:
//
// Referrals:
//
// Notes:
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
UINT16
SetType1(
    IN UINT16                      Handle,
    IN SET_SMBIOS_STRUCTURE_DATA   *Data,
    IN BOOLEAN                     Set
)
{
    EFI_STATUS          Status;
    TABLE_INFO          TableInfo;
    UINT8               *UuidPtr;
    UINT8               i;

    // Fill TableInfo with input data
    GetInputDataInfo(Handle, Data, &TableInfo);

#if !defined(SMBIOS_DMIEDIT_DATA_LOC) || SMBIOS_DMIEDIT_DATA_LOC != 2
    switch (Data->FieldOffset) {
        case 0x04 :
        case 0x05 :
        case 0x06 :
        case 0x07 :
        case 0x19 :
        case 0x1a : if (Data->Command != 5) return DMI_BAD_PARAMETER;

                    if (Set == FALSE) return DMI_SUCCESS;

				    if (isWriteOnce(1, Data->FieldOffset, Handle)) return DMI_READ_ONLY;

                    Status = UpdateSmbiosTable(&TableInfo, Data->StructureData);
                    break;

        default:    if ((Data->FieldOffset > 0x07) && (Data->FieldOffset < 0x18)) {
                        UINT8       *Ptr;

                        Ptr = GetStructureByHandle(&Handle);
                        UuidPtr = (UINT8*)&((SMBIOS_SYSTEM_INFO*)Ptr)->Uuid;
                        Ptr = UuidPtr + Data->FieldOffset - 8;

                        if (Data->Command < 3) {
                            if (Data->Command == 0) {
                                *Ptr &= (UINT8)Data->ChangeMask;
                                *Ptr |= (UINT8)Data->ChangeValue;
                            }
                            if (Data->Command == 1) {
                                *(UINT16*)Ptr &= (UINT16)Data->ChangeMask;
                                *(UINT16*)Ptr |= (UINT16)Data->ChangeValue;
                            }
                            if (Data->Command == 2) {
                                *(UINT32*)Ptr &= Data->ChangeMask;
                                *(UINT32*)Ptr |= Data->ChangeValue;
                            }
                        }
                        else if (Data->Command == 6) {
                            for (i = 0; i < (UINT8)TableInfo.Size; i++) {
                                Ptr[i] = Data->StructureData[i];
                            }
                        }
                        else {
                            return DMI_BAD_PARAMETER;
                        }

                        if (Set == FALSE) return DMI_SUCCESS;

					    if (isWriteOnce(1, Data->FieldOffset, Handle)) return DMI_READ_ONLY;

                        TableInfo.Offset = 8;
                        TableInfo.Size = sizeof(EFI_GUID);

                        Status = UpdateSmbiosTable(&TableInfo, UuidPtr);
                    }
                    else {
                        return DMI_BAD_PARAMETER;
                    }
    }
#else
{
    VOID    *NvramData;

    NvramData = &Data->StructureData;

	//
	// Get number of DMI data records in NVRAM
	//
	// Note: DMI data record actually starts with record #1,
	//		 first record #0 holds total number of DMI data records
	//       instead of TABLE_INFO
	//       ===> DmiArray[0].Type = count
	//
    Status = pRS->GetVariable(
                        DmiArrayVar,
                        &EfiSmbiosNvramGuid,
                        NULL,
                        &DmiArraySize,
                        &DmiArray);

	if (Status == EFI_SUCCESS) {
	    Index = DmiArray[0].Type;	// Note: DmiArray[0] has count # instead of Type/Offset
	    ++Index;
	}
	else {
		Index = 1;
	}

    DmiArray[Index].Type = 1;
    DmiArray[Index].Handle = Handle;
    DmiArray[Index].Offset = Data->FieldOffset;
    DmiArray[Index].Flags = 0;

    switch (Data->FieldOffset) {
        case 0x04 :
        case 0x05 :
        case 0x06 :
        case 0x07 :
        case 0x19 :
        case 0x1a : if (Data->Command != 5) return DMI_BAD_PARAMETER;
                    break;

        default:    if ((Data->FieldOffset > 0x07) && (Data->FieldOffset < 0x18)) {
                        UINT8       *Ptr;

                        Ptr = GetStructureByHandle(&Handle);
                        UuidPtr = (UINT8*)&((SMBIOS_SYSTEM_INFO*)Ptr)->Uuid;
                        Ptr = UuidPtr + Data->FieldOffset - 8;

                        if (Data->Command < 3) {
                            if (Data->Command == 0) {
                                *Ptr &= (UINT8)Data->ChangeMask;
                                *Ptr |= (UINT8)Data->ChangeValue;
                            }
                            if (Data->Command == 1) {
                                *(UINT16*)Ptr &= (UINT16)Data->ChangeMask;
                                *(UINT16*)Ptr |= (UINT16)Data->ChangeValue;
                            }
                            if (Data->Command == 2) {
                                *(UINT32*)Ptr &= Data->ChangeMask;
                                *(UINT32*)Ptr |= Data->ChangeValue;
                            }
                        }
                        else if (Data->Command == 6) {
                            for (i = 0; i < (UINT8)TableInfo.Size; i++) {
                                Ptr[i] = Data->StructureData[i];
                            }
                        }
                        else {
                            return DMI_BAD_PARAMETER;
                        }

                        DmiArray[Index].Offset = 0x08;
                        NvramData = UuidPtr;
                        TableInfo.Offset = 8;
                        TableInfo.Size = sizeof(EFI_GUID);
                    }
                    else {
                        return DMI_BAD_PARAMETER;
                    }
    }

    if (Set == FALSE) return DMI_SUCCESS;

    if (isWriteOnce(1, Data->FieldOffset, Handle)) return DMI_READ_ONLY;

    Swprintf(Var, L"DmiVar%02x%04x%02x%02x",
			   DmiArray[Index].Type,
			   DmiArray[Index].Handle,
			   DmiArray[Index].Offset,
			   DmiArray[Index].Flags);

    Status = StoreNvramData(Var, NvramData, (UINTN)TableInfo.Size);
}
#endif

    TRACE((-1, "Change structure. Type = %x, Handle = %x, Offset = %x\n",\
                                  TableInfo.Type,\
                                  TableInfo.Handle,\
                                  TableInfo.Offset));

    if (Status) {
        return (UINT16)Status;
    }

    if ((Data->FieldOffset > 0x07) && (Data->FieldOffset < 0x18)) {
        return DMI_SUCCESS;
    }
    else {
        // Dynamically update strings in Smbios table
        return UpdateStrings(Handle, TableInfo, Data->StructureData);
    }
}

#if BASE_BOARD_INFO
//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   SetType2
//
// Description: Updates Flash Data record with input DMI data
//              Updates SMBIOS Type 2 Structure in Runtime with DMI data
//
// Input:       IN UINT16                      Handle,
//              IN SET_SMBIOS_STRUCTURE_DATA   *Data,
//              IN BOOLEAN                     Set
//
// Output:      UINT8 - Status
//
// Modified:
//
// Referrals:
//
// Notes:
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
UINT16
SetType2(
    IN UINT16                      Handle,
    IN SET_SMBIOS_STRUCTURE_DATA   *Data,
    IN BOOLEAN                     Set
)
{
    EFI_STATUS          Status;
    TABLE_INFO          TableInfo;

    if (Data->Command != 5) return DMI_BAD_PARAMETER;
    if ( Data->FieldOffset != 4
      && Data->FieldOffset != 5
      && Data->FieldOffset != 6
      && Data->FieldOffset != 7
      && Data->FieldOffset != 8
      && Data->FieldOffset != 0x0a
    ) return DMI_BAD_PARAMETER;

    if (Set == FALSE) return DMI_SUCCESS;

    if (isWriteOnce(2, Data->FieldOffset, Handle)) return DMI_READ_ONLY;

    // Fill TableInfo with input data
    GetInputDataInfo(Handle, Data, &TableInfo);

#if !defined(SMBIOS_DMIEDIT_DATA_LOC) || SMBIOS_DMIEDIT_DATA_LOC != 2

    Status = UpdateSmbiosTable(&TableInfo, Data->StructureData);

#else
{
	//
	// Get number of DMI data records in NVRAM
	//
	// Note: DMI data record actually starts with record #1,
	//		 first record #0 holds total number of DMI data records
	//       instead of TABLE_INFO
	//       ===> DmiArray[0].Type = count
	//
    Status = pRS->GetVariable(
                        DmiArrayVar,
                        &EfiSmbiosNvramGuid,
                        NULL,
                        &DmiArraySize,
                        &DmiArray);

	if (Status == EFI_SUCCESS) {
	    Index = DmiArray[0].Type;	// Note: DmiArray[0] has count # instead of Type/Offset
	    ++Index;
	}
	else {
		Index = 1;
	}

    DmiArray[Index].Type = 2;
    DmiArray[Index].Handle = Handle;
    DmiArray[Index].Offset = Data->FieldOffset;
    DmiArray[Index].Flags = 0;

    Swprintf(Var, L"DmiVar%02x%04x%02x%02x",
			   DmiArray[Index].Type,
			   DmiArray[Index].Handle,
			   DmiArray[Index].Offset,
			   DmiArray[Index].Flags);

    Status = StoreNvramData(Var, &Data->StructureData, (UINTN)TableInfo.Size);
}
#endif

    if (Status) {
        return (UINT16)Status;
    }

    // Dynamically update strings in Smbios table
    return UpdateStrings(Handle, TableInfo, Data->StructureData);
}
#endif

#if SYS_CHASSIS_INFO
//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   SetType3
//
// Description: Updates Flash Data record with input DMI data
//              Updates SMBIOS Type 3 Structure in Runtime with DMI data
//
// Input:       IN UINT16                      Handle,
//              IN SET_SMBIOS_STRUCTURE_DATA   *Data,
//              IN BOOLEAN                     Set
//
// Output:      UINT8 - Status
//
// Modified:
//
// Referrals:
//
// Notes:
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
UINT16
SetType3(
    IN UINT16                      Handle,
    IN SET_SMBIOS_STRUCTURE_DATA   *Data,
    IN BOOLEAN                     Set
)
{
    EFI_STATUS          Status;
    TABLE_INFO          TableInfo;
    UINT8               *StructPtr;
    UINT8               Instance;
    STRING_TABLE        *StringTablePtr;

    switch (Data->FieldOffset) {
        case 4:
        case 6:
        case 7:
        case 8:     if (Data->Command != 5) return DMI_BAD_PARAMETER;
                    break;
        case 5:     if (Data->Command != 0) return DMI_BAD_PARAMETER;
                    break;
        case 0x0d:  if (Data->Command != 2) return DMI_BAD_PARAMETER;
                    break;
        default:    {
                        // Get instance number
                        Instance = GetInstanceByTypeHandle(3, Handle);
                        StringTablePtr = &StringType_3[0][0];
                        StringTablePtr += 6 * (Instance - 1);

                        while (StringTablePtr->Offset != 0xff) {
                            if (StringTablePtr->Offset == Data->FieldOffset) {
                                break;
                            }

                            StringTablePtr++;
                        };

                        if (StringTablePtr->Offset != 0xff) {
                            if (Data->Command != 0x5) {
                                return DMI_BAD_PARAMETER;
                            }
                        }
                        else {
                            return DMI_BAD_PARAMETER;
                        }
                    }
    }

    if (Set == FALSE) return DMI_SUCCESS;

    if (isWriteOnce(3, Data->FieldOffset, Handle)) return DMI_READ_ONLY;

    // Fill TableInfo with input data
    GetInputDataInfo(Handle, Data, &TableInfo);

#if !defined(SMBIOS_DMIEDIT_DATA_LOC) || SMBIOS_DMIEDIT_DATA_LOC != 2
    if (Data->Command == 0 || Data->Command == 0x2)
        *(UINT32*)Data->StructureData = Data->ChangeValue;

    Status = UpdateSmbiosTable(&TableInfo, Data->StructureData);

#else
{
	//
	// Get number of DMI data records in NVRAM
	//
	// Note: DMI data record actually starts with record #1,
	//		 first record #0 holds total number of DMI data records
	//       instead of TABLE_INFO
	//       ===> DmiArray[0].Type = count
	//
    Status = pRS->GetVariable(
                        DmiArrayVar,
                        &EfiSmbiosNvramGuid,
                        NULL,
                        &DmiArraySize,
                        &DmiArray);

	if (Status == EFI_SUCCESS) {
	    Index = DmiArray[0].Type;	// Note: DmiArray[0] has count # instead of Type/Offset
	    ++Index;
	}
	else {
		Index = 1;
	}

    DmiArray[Index].Type = 3;
    DmiArray[Index].Handle = Handle;
    DmiArray[Index].Offset = Data->FieldOffset;
    DmiArray[Index].Flags = 0;

    Swprintf(Var, L"DmiVar%02x%04x%02x%02x",
			   DmiArray[Index].Type,
			   DmiArray[Index].Handle,
			   DmiArray[Index].Offset,
			   DmiArray[Index].Flags);

    if (Data->Command == 0 || Data->Command == 0x2)
        *(UINT32*)Data->StructureData = Data->ChangeValue;

    Status = StoreNvramData(Var, &Data->StructureData, (UINTN)TableInfo.Size);
}
#endif

    if (Status) {
        return (UINT16)Status;
    }

    // Dynamically update the structure in the Smbios table
    StructPtr = GetStructureByHandle(&Handle);
    if (StructPtr != NULL) {
        switch (Data->FieldOffset) {
            case 0x05:  ((SMBIOS_SYSTEM_ENCLOSURE_INFO*)StructPtr)->Type &= (UINT8)Data->ChangeMask;
                        ((SMBIOS_SYSTEM_ENCLOSURE_INFO*)StructPtr)->Type |= (UINT8)Data->ChangeValue;
                        break;
            case 0x0d:  ((SMBIOS_SYSTEM_ENCLOSURE_INFO*)StructPtr)->OemDefined &= (UINT32)Data->ChangeMask;
                        ((SMBIOS_SYSTEM_ENCLOSURE_INFO*)StructPtr)->OemDefined |= (UINT32)Data->ChangeValue;
        }
    }

    return UpdateStrings(Handle, TableInfo, Data->StructureData);
}
#endif

#if PROCESSOR_DMIEDIT_SUPPORT
//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   SetType4
//
// Description: Updates Flash Data record with input DMI data
//              Updates SMBIOS Type 4 Structure in Runtime with DMI data
//
// Input:       IN UINT16                      Handle,
//              IN SET_SMBIOS_STRUCTURE_DATA   *Data,
//              IN BOOLEAN                     Set
//
// Output:      UINT8 - Status
//
// Modified:
//
// Referrals:
//
// Notes:
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
UINT16
SetType4(
    IN UINT16                      Handle,
    IN SET_SMBIOS_STRUCTURE_DATA   *Data,
    IN BOOLEAN                     Set
)
{
    EFI_STATUS          Status;
    TABLE_INFO          TableInfo;

    switch (Data->FieldOffset) {
        case 0x20:
        case 0x21:
        case 0x22:  if (Data->Command != 0x5) return DMI_BAD_PARAMETER;
                    break;
        default:    return DMI_BAD_PARAMETER;
    }

    if (Set == FALSE) return DMI_SUCCESS;

    // Fill TableInfo with input data
    GetInputDataInfo(Handle, Data, &TableInfo);

#if !defined(SMBIOS_DMIEDIT_DATA_LOC) || SMBIOS_DMIEDIT_DATA_LOC != 2
    Status = UpdateSmbiosTable(&TableInfo, Data->StructureData);
#else
{
	//
	// Get number of DMI data records in NVRAM
	//
	// Note: DMI data record actually starts with record #1,
	//		 first record #0 holds total number of DMI data records
	//       instead of TABLE_INFO
	//       ===> DmiArray[0].Type = count
	//
    Status = pRS->GetVariable(
                        DmiArrayVar,
                        &EfiSmbiosNvramGuid,
                        NULL,
                        &DmiArraySize,
                        &DmiArray);

	if (Status == EFI_SUCCESS) {
	    Index = DmiArray[0].Type;	// Note: DmiArray[0] has count # instead of Type/Offset
	    ++Index;
	}
	else {
		Index = 1;
	}

    DmiArray[Index].Type = 4;
    DmiArray[Index].Handle = Handle;
    DmiArray[Index].Offset = Data->FieldOffset;
    DmiArray[Index].Flags = 0;

    Swprintf(Var, L"DmiVar%02x%04x%02x%02x",
			   DmiArray[Index].Type,
			   DmiArray[Index].Handle,
			   DmiArray[Index].Offset,
			   DmiArray[Index].Flags);

    Status = StoreNvramData(Var, &Data->StructureData, (UINTN)TableInfo.Size);
}
#endif

    if (Status) {
        return (UINT16)Status;
    }

    // Dynamically update the structure in the Smbios table
    return UpdateStrings(Handle, TableInfo, Data->StructureData);
}
#endif

#if OEM_STRING_INFO
//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   SetType11
//
// Description: Updates Flash Data record with input DMI data
//              Updates SMBIOS Type 11 Structure in Runtime with DMI data
//
// Input:       IN UINT16                      Handle,
//              IN SET_SMBIOS_STRUCTURE_DATA   *Data,
//              IN BOOLEAN                     Set
//
// Output:      UINT8 - Status
//
// Modified:
//
// Referrals:
//
// Notes:
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
UINT16
SetType11(
    IN UINT16                      Handle,
    IN SET_SMBIOS_STRUCTURE_DATA   *Data,
    IN BOOLEAN                     Set
)
{
    EFI_STATUS          Status;
    TABLE_INFO          TableInfo;
    static UINT8        StringNumber = 0;

    if (isWriteOnce(11, Data->FieldOffset, Handle)) return DMI_READ_ONLY;

    // Fill TableInfo with input data
    GetInputDataInfo(Handle, Data, &TableInfo);

    if (Data->Command == 0) {
        if (Data->FieldOffset != 4) return DMI_BAD_PARAMETER;
        if (Set == FALSE) return DMI_SUCCESS;

        StringNumber = (UINT8) Data->ChangeValue;
        return DMI_SUCCESS;
    }

    if (Data->Command != 5) return DMI_BAD_PARAMETER;
    if (Data->FieldOffset != 4) return DMI_BAD_PARAMETER;
    if (!StringNumber)  return DMI_BAD_PARAMETER;
    if (Set == FALSE) return DMI_SUCCESS;

    TableInfo.Offset = StringNumber;

#if !defined(SMBIOS_DMIEDIT_DATA_LOC) || SMBIOS_DMIEDIT_DATA_LOC != 2

    Status = UpdateSmbiosTable(&TableInfo, Data->StructureData);

#else
{
	//
	// Get number of DMI data records in NVRAM
	//
	// Note: DMI data record actually starts with record #1,
	//		 first record #0 holds total number of DMI data records
	//       instead of TABLE_INFO
	//       ===> DmiArray[0].Type = count
	//
    Status = pRS->GetVariable(
                        DmiArrayVar,
                        &EfiSmbiosNvramGuid,
                        NULL,
                        &DmiArraySize,
                        &DmiArray);

	if (Status == EFI_SUCCESS) {
	    Index = DmiArray[0].Type;	// Note: DmiArray[0] has count # instead of Type/Offset
	    ++Index;
	}
	else {
		Index = 1;
	}

    DmiArray[Index].Type = 11;
    DmiArray[Index].Handle = Handle;
    DmiArray[Index].Offset = StringNumber - 1;
    DmiArray[Index].Flags = 0;

    Swprintf(Var, L"DmiVar%02x%04x%02x%02x",
			   DmiArray[Index].Type,
			   DmiArray[Index].Handle,
			   DmiArray[Index].Offset,
			   DmiArray[Index].Flags);

    Status = StoreNvramData(Var, &Data->StructureData, (UINTN)TableInfo.Size);
}
#endif

    if (Status) {
        return (UINT16)Status;
    }
    return DynamicUpdateType11(Handle, TableInfo, Data->StructureData);
}
#endif

#if SYSTEM_CONFIG_OPTION_INFO
//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   SetType12
//
// Description: Updates Flash Data record with input DMI data
//              Updates SMBIOS Type 12 Structure in Runtime with DMI data
//
// Input:       IN UINT16                      Handle,
//              IN SET_SMBIOS_STRUCTURE_DATA   *Data,
//              IN BOOLEAN                     Set
//
// Output:      UINT8 - Status
//
// Modified:
//
// Referrals:
//
// Notes:
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
UINT16
SetType12(
    UINT16                      Handle,
    SET_SMBIOS_STRUCTURE_DATA   *Data,
    BOOLEAN                     Set
)
{
    EFI_STATUS  	Status;
    TABLE_INFO  	TableInfo;
    static UINT8	StringNumber = 0;

    if (Data->Command == 0) {
        if (Data->FieldOffset != 4) return DMI_BAD_PARAMETER;
        if (Set == FALSE) return DMI_SUCCESS;

        StringNumber = (UINT8) Data->ChangeValue;
        return DMI_SUCCESS;
    }

    if (Data->Command != 5) return DMI_BAD_PARAMETER;
    if (Data->FieldOffset != 4) return DMI_BAD_PARAMETER;
    if (!StringNumber)  return DMI_BAD_PARAMETER;
    if (Set == FALSE) return DMI_SUCCESS;

    if (isWriteOnce(12, Data->FieldOffset, Handle)) return DMI_READ_ONLY;

    // Fill TableInfo with input data
    GetInputDataInfo(Handle, Data, &TableInfo);

    TableInfo.Offset = StringNumber;

#if !defined(SMBIOS_DMIEDIT_DATA_LOC) || SMBIOS_DMIEDIT_DATA_LOC != 2
    Status = UpdateSmbiosTable(&TableInfo, Data->StructureData);
    if (Status != 0) {
        return (UINT16)Status;
    }
#else
{
	//
	// Get number of DMI data records in NVRAM
	//
	// Note: DMI data record actually starts with record #1,
	//		 first record #0 holds total number of DMI data records
	//       instead of TABLE_INFO
	//       ===> DmiArray[0].Type = count
	//
    Status = pRS->GetVariable(
                        DmiArrayVar,
                        &EfiSmbiosNvramGuid,
                        NULL,
                        &DmiArraySize,
                        &DmiArray);

	if (Status == EFI_SUCCESS) {
	    Index = DmiArray[0].Type;	// Note: DmiArray[0] has count # instead of Type/Offset
	    ++Index;
	}
	else {
		Index = 1;
	}

    DmiArray[Index].Type = 12;
    DmiArray[Index].Handle = Handle;
    DmiArray[Index].Offset = StringNumber - 1;
    DmiArray[Index].Flags = 0;

    Swprintf(Var, L"DmiVar%02x%04x%02x%02x",
			   DmiArray[Index].Type,
			   DmiArray[Index].Handle,
			   DmiArray[Index].Offset,
			   DmiArray[Index].Flags);

    Status = StoreNvramData(Var, &Data->StructureData, (UINTN)TableInfo.Size);
}
#endif

    if (Status) {
        return (UINT16)Status;
    }
    return DynamicUpdateType12(Handle, TableInfo, Data->StructureData);
}
#endif

#if PORTABLE_BATTERY_INFO
//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   SetType22
//
// Description: Updates Flash Data record with input DMI data
//              Updates SMBIOS Type 22 Structure in Runtime with DMI data
//
// Input:       IN UINT16                      Handle,
//              IN SET_SMBIOS_STRUCTURE_DATA   *Data,
//              IN BOOLEAN                     Set
//
// Output:      UINT8 - Status
//
// Modified:
//
// Referrals:
//
// Notes:
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
UINT16
SetType22(
    IN UINT16                      Handle,
    IN SET_SMBIOS_STRUCTURE_DATA   *Data,
    IN BOOLEAN                     Set
)
{
    EFI_STATUS          Status;
    TABLE_INFO          TableInfo;
    UINT8               *StructPtr;

    switch (Data->FieldOffset) {
        case 0x09:
        case 0x0f:
        case 0x15:  if (Data->Command != 0) return DMI_BAD_PARAMETER;
                    break;
        case 0x0a:
        case 0x0c:
        case 0x10:
        case 0x12:  if (Data->Command != 1) return DMI_BAD_PARAMETER;
                    break;
        case 0x16:  if (Data->Command != 2) return DMI_BAD_PARAMETER;
                    break;
        case 0x04:
        case 0x05:
        case 0x06:
        case 0x07:
        case 0x08:
        case 0x0e:
        case 0x14:  if (Data->Command != 5) return DMI_BAD_PARAMETER;
                    break;
        default:    return DMI_BAD_PARAMETER;
    }

    if (Set == FALSE) return DMI_SUCCESS;

    if (isWriteOnce(22, Data->FieldOffset, Handle)) return DMI_READ_ONLY;

    // Fill TableInfo with input data
    GetInputDataInfo(Handle, Data, &TableInfo);

    if (Data->Command == 0 || Data->Command == 0x1 || Data->Command == 0x2)
        *(UINT32*)Data->StructureData = Data->ChangeValue;

#if !defined(SMBIOS_DMIEDIT_DATA_LOC) || SMBIOS_DMIEDIT_DATA_LOC != 2

    Status = UpdateSmbiosTable(&TableInfo, Data->StructureData);

#else
	//
	// Get number of DMI data records in NVRAM
	//
	// Note: DMI data record actually starts with record #1,
	//		 first record #0 holds total number of DMI data records
	//       instead of TABLE_INFO
	//       ===> DmiArray[0].Type = count
	//
    Status = pRS->GetVariable(
                        DmiArrayVar,
                        &EfiSmbiosNvramGuid,
                        NULL,
                        &DmiArraySize,
                        &DmiArray);

	if (Status == EFI_SUCCESS) {
	    Index = DmiArray[0].Type;	// Note: DmiArray[0] has count # instead of Type/Offset
	    ++Index;
	}
	else {
		Index = 1;
	}

    DmiArray[Index].Type = 22;
    DmiArray[Index].Handle = Handle;
    DmiArray[Index].Offset = Data->FieldOffset;
    DmiArray[Index].Flags = 0;

    Swprintf(Var, L"DmiVar%02x%04x%02x%02x",
			   DmiArray[Index].Type,
			   DmiArray[Index].Handle,
			   DmiArray[Index].Offset,
			   DmiArray[Index].Flags);

    Status = StoreNvramData(Var, &Data->StructureData, (UINTN)TableInfo.Size);
#endif

    if (Status) {
        return (UINT16)Status;
    }

    // Dynamically update the structure in the Smbios table
    StructPtr = GetStructureByHandle(&Handle);
    if (StructPtr != NULL) {
        switch (Data->FieldOffset) {
            case 0x09:  ((SMBIOS_PORTABLE_BATTERY_INFO*)StructPtr)->DeviceChemistry &= (UINT8)Data->ChangeMask;
                        ((SMBIOS_PORTABLE_BATTERY_INFO*)StructPtr)->DeviceChemistry |= (UINT8)Data->ChangeValue;
                        break;
            case 0x0a:  ((SMBIOS_PORTABLE_BATTERY_INFO*)StructPtr)->DesignCapacity &= (UINT16)Data->ChangeMask;
                        ((SMBIOS_PORTABLE_BATTERY_INFO*)StructPtr)->DesignCapacity |= (UINT16)Data->ChangeValue;
                        break;
            case 0x0c:  ((SMBIOS_PORTABLE_BATTERY_INFO*)StructPtr)->DesignVoltage &= (UINT16)Data->ChangeMask;
                        ((SMBIOS_PORTABLE_BATTERY_INFO*)StructPtr)->DesignVoltage |= (UINT16)Data->ChangeValue;
                        break;
            case 0x0f:  ((SMBIOS_PORTABLE_BATTERY_INFO*)StructPtr)->MaxErrorInBatteryData &= (UINT16)Data->ChangeMask;
                        ((SMBIOS_PORTABLE_BATTERY_INFO*)StructPtr)->MaxErrorInBatteryData |= (UINT16)Data->ChangeValue;
                        break;
            case 0x10:  ((SMBIOS_PORTABLE_BATTERY_INFO*)StructPtr)->SBDSSerialNumber &= (UINT16)Data->ChangeMask;
                        ((SMBIOS_PORTABLE_BATTERY_INFO*)StructPtr)->SBDSSerialNumber |= (UINT16)Data->ChangeValue;
                        break;
            case 0x12:  ((SMBIOS_PORTABLE_BATTERY_INFO*)StructPtr)->SBDSManufacturerDate &= (UINT16)Data->ChangeMask;
                        ((SMBIOS_PORTABLE_BATTERY_INFO*)StructPtr)->SBDSManufacturerDate |= (UINT16)Data->ChangeValue;
                        break;
            case 0x15:  ((SMBIOS_PORTABLE_BATTERY_INFO*)StructPtr)->DesignCapabilityMult &= (UINT16)Data->ChangeMask;
                        ((SMBIOS_PORTABLE_BATTERY_INFO*)StructPtr)->DesignCapabilityMult |= (UINT16)Data->ChangeValue;
                        break;
            case 0x16:  ((SMBIOS_PORTABLE_BATTERY_INFO*)StructPtr)->OEMSpecific &= (UINT32)Data->ChangeMask;
                        ((SMBIOS_PORTABLE_BATTERY_INFO*)StructPtr)->OEMSpecific |= (UINT32)Data->ChangeValue;
                        break;
        }
    }

    return UpdateStrings(Handle, TableInfo, Data->StructureData);
}
#endif

#if SYSTEM_POWER_SUPPLY_INFO
//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   SetType39
//
// Description: Updates Flash Data record with input DMI data
//              Updates SMBIOS Type 39 Structure in Runtime with DMI data
//
// Input:       IN UINT16                      Handle,
//              IN SET_SMBIOS_STRUCTURE_DATA   *Data,
//              IN BOOLEAN                     Set
//
// Output:      UINT8 - Status
//
// Modified:
//
// Referrals:
//
// Notes:
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
UINT16
SetType39(
    IN UINT16                      Handle,
    IN SET_SMBIOS_STRUCTURE_DATA   *Data,
    IN BOOLEAN                     Set
)
{
    EFI_STATUS          Status;
    TABLE_INFO          TableInfo;
    UINT8               *StructPtr;

    switch (Data->FieldOffset) {
        case 0x04:  if (Data->Command != 0) return DMI_BAD_PARAMETER;
                    break;
        case 0x05:
        case 0x06:
        case 0x07:
        case 0x08:
        case 0x09:
        case 0x0a:
        case 0x0b:  if (Data->Command != 5) return DMI_BAD_PARAMETER;
                    break;
        case 0x0c:
        case 0x0e:
        case 0x10:
        case 0x12:
        case 0x14:  if (Data->Command != 1) return DMI_BAD_PARAMETER;
                    break;
        default:    return DMI_BAD_PARAMETER;
    }

    if (Set == FALSE) return DMI_SUCCESS;

    if (isWriteOnce(39, Data->FieldOffset, Handle)) return DMI_READ_ONLY;

    // Fill TableInfo with input data
    GetInputDataInfo(Handle, Data, &TableInfo);

    if (Data->Command == 0 || Data->Command == 0x1)
        *(UINT32*)Data->StructureData = Data->ChangeValue;

#if !defined(SMBIOS_DMIEDIT_DATA_LOC) || SMBIOS_DMIEDIT_DATA_LOC != 2

    Status = UpdateSmbiosTable(&TableInfo, Data->StructureData);

#else
{
	//
	// Get number of DMI data records in NVRAM
	//
	// Note: DMI data record actually starts with record #1,
	//		 first record #0 holds total number of DMI data records
	//       instead of TABLE_INFO
	//       ===> DmiArray[0].Type = count
	//
    Status = pRS->GetVariable(
                        DmiArrayVar,
                        &EfiSmbiosNvramGuid,
                        NULL,
                        &DmiArraySize,
                        &DmiArray);

	if (Status == EFI_SUCCESS) {
	    Index = DmiArray[0].Type;	// Note: DmiArray[0] has count # instead of Type/Offset
	    ++Index;
	}
	else {
		Index = 1;
	}

    DmiArray[Index].Type = 39;
    DmiArray[Index].Handle = Handle;
    DmiArray[Index].Offset = Data->FieldOffset;
    DmiArray[Index].Flags = 0;

    Swprintf(Var, L"DmiVar%02x%04x%02x%02x",
			   DmiArray[Index].Type,
			   DmiArray[Index].Handle,
			   DmiArray[Index].Offset,
			   DmiArray[Index].Flags);

    Status = StoreNvramData(Var, &Data->StructureData, (UINTN)TableInfo.Size);
}
#endif

    if (Status) {
        return (UINT16)Status;
    }

    // Dynamically update the structure in the Smbios table
    StructPtr = GetStructureByHandle(&Handle);
    if (StructPtr != NULL) {
        switch (Data->FieldOffset) {
            case 0x04:  ((SMBIOS_SYSTEM_PWR_SUPPY_INFO*)StructPtr)->PwrUnitGroup &= (UINT8)Data->ChangeMask;
                        ((SMBIOS_SYSTEM_PWR_SUPPY_INFO*)StructPtr)->PwrUnitGroup |= (UINT8)Data->ChangeValue;
                        break;
            case 0x0c:  ((SMBIOS_SYSTEM_PWR_SUPPY_INFO*)StructPtr)->MaxPwrCapacity &= (UINT16)Data->ChangeMask;
                        ((SMBIOS_SYSTEM_PWR_SUPPY_INFO*)StructPtr)->MaxPwrCapacity |= (UINT16)Data->ChangeValue;
                        break;
            case 0x0e:  ((SMBIOS_SYSTEM_PWR_SUPPY_INFO*)StructPtr)->PwrSupplyChar &= (UINT16)Data->ChangeMask;
                        ((SMBIOS_SYSTEM_PWR_SUPPY_INFO*)StructPtr)->PwrSupplyChar |= (UINT16)Data->ChangeValue;
                        break;
            case 0x10:  ((SMBIOS_SYSTEM_PWR_SUPPY_INFO*)StructPtr)->InputVoltProbeHandle &= (UINT16)Data->ChangeMask;
                        ((SMBIOS_SYSTEM_PWR_SUPPY_INFO*)StructPtr)->InputVoltProbeHandle |= (UINT16)Data->ChangeValue;
                        break;
            case 0x12:  ((SMBIOS_SYSTEM_PWR_SUPPY_INFO*)StructPtr)->CoolingDevHandle &= (UINT16)Data->ChangeMask;
                        ((SMBIOS_SYSTEM_PWR_SUPPY_INFO*)StructPtr)->CoolingDevHandle |= (UINT16)Data->ChangeValue;
                        break;
            case 0x14:  ((SMBIOS_SYSTEM_PWR_SUPPY_INFO*)StructPtr)->InputCurrentProbeHandle &= (UINT16)Data->ChangeMask;
                        ((SMBIOS_SYSTEM_PWR_SUPPY_INFO*)StructPtr)->InputCurrentProbeHandle |= (UINT16)Data->ChangeValue;
                        break;
        }
    }

    return UpdateStrings(Handle, TableInfo, Data->StructureData);
}
#endif

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   PnPFn52AddStructure
//
// Description: PnP function 52 Command 03: Add structure
//
// Input:       IN SET_SMBIOS_STRUCTURE_DATA    *dmiDataBuffer
//              IN BOOLEAN                      Set
//
// Output:      UINT8 - Status
//
// Modified:
//
// Referrals:
//
// Notes:
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
UINT16
PnPFn52AddStructure (
    IN SET_SMBIOS_STRUCTURE    *p
)
{
    UINT16  Status;
    UINT8   *SmbiosTable = (UINT8*)((SMBIOS_TABLE_ENTRY_POINT*)SmbiosTableEntryPoint)->TableAddress;
    UINT8   *SmbiosTableEnd = SmbiosTable + ((SMBIOS_TABLE_ENTRY_POINT*)SmbiosTableEntryPoint)->TableLength;
    UINT8   *SrcPtr;
    UINT8   *DestPtr;
    UINT8   Type127Buffer[4];
    SET_SMBIOS_STRUCTURE_DATA    *dmiDataBuffer;
    TABLE_INFO  TableInfo;

    dmiDataBuffer = (SET_SMBIOS_STRUCTURE_DATA*)p->Buffer32BitAddr;
    DestPtr = GetStructureByHandle(&dmiDataBuffer->StructureHeader.Handle);

    if (DestPtr) {
        Status = DMI_INVALID_HANDLE;
    }
    else {
        SrcPtr = SmbiosTable;
        if (FindStructureType(&SrcPtr, &DestPtr, 127, 1)) {
            if ((MaximumBufferSize - ((SMBIOS_TABLE_ENTRY_POINT*)SmbiosTableEntryPoint)->TableLength) >= dmiDataBuffer->DataLength) {
                if (p->Control & 1) {
                    TableInfo.Type = dmiDataBuffer->StructureHeader.Type;
                    TableInfo.Offset = dmiDataBuffer->FieldOffset;
                    TableInfo.Reserved = 0;
                    TableInfo.Flags = DMIEDIT_ADD_STRUC | DMIEDIT_EXTENDED_HDR;
                    TableInfo.HdrLength = sizeof(TABLE_INFO);
                    TableInfo.Size = dmiDataBuffer->DataLength;
                    TableInfo.Handle = dmiDataBuffer->StructureHeader.Handle;

#if !defined(SMBIOS_DMIEDIT_DATA_LOC) || SMBIOS_DMIEDIT_DATA_LOC != 2
                    Status = UpdateSmbiosTable(&TableInfo, (UINT8*)&dmiDataBuffer->StructureHeader);
                    if (Status != 0) {
                        return Status;
                    }
#else
{
					EFI_STATUS	Status;

                    Swprintf(Var, L"DmiVar%02x%04x%02x%02x",
							   TableInfo.Type,
							   TableInfo.Handle,
							   TableInfo.Offset,
							   TableInfo.Flags);

					//
					// Get number of DMI data records in NVRAM
					//
					// Note: DMI data record actually starts with record #1,
					//		 first record #0 holds total number of DMI data records
					//       instead of TABLE_INFO
					//       ===> DmiArray[0].Type = count
					//
				    Status = pRS->GetVariable(
				                        DmiArrayVar,
				                        &EfiSmbiosNvramGuid,
				                        NULL,
				                        &DmiArraySize,
				                        &DmiArray);

					if (Status == EFI_SUCCESS) {
					    Index = DmiArray[0].Type;	// Note: DmiArray[0] has count # instead of Type/Offset
					    ++Index;
					}
					else {
						Index = 1;
					}

					// Check if record already exists
                    //
                    // DmiDataSize can be anything since the purpose of this GetVariable
                    // call is to detect if the variable already exists or not. Its
                    // content is not used.
                    DmiDataSize = 0;                        // Dummy value
				    Status = pRS->GetVariable(
				                        Var,
				                        &EfiSmbiosNvramGuid,
				                        NULL,
				                        &DmiDataSize,
				                        &DmiData);

				    if (Status == EFI_NOT_FOUND) {
						// Record not present, increment record count
				        DmiArray[Index].Type = TableInfo.Type;
				        DmiArray[Index].Handle = TableInfo.Handle;
				        DmiArray[Index].Offset = TableInfo.Offset;
				        DmiArray[Index].Flags = TableInfo.Flags;

				        DmiArray[0].Type += 1;          // Increment # variable counter

				        Status = pRS->SetVariable(
				                            DmiArrayVar,
				                            &EfiSmbiosNvramGuid,
				                            EFI_VARIABLE_RUNTIME_ACCESS | EFI_VARIABLE_BOOTSERVICE_ACCESS | EFI_VARIABLE_NON_VOLATILE,
				                            DmiArraySize,
				                            &DmiArray);
				        ASSERT_EFI_ERROR(Status);
                        if (Status != 0) {
                            return (UINT16)Status;
                        }
				    }

					// Update DMI data record if already exists,
					// or store new record if total record count in DmiArray was successfully
					// updated
                    if (Status == EFI_BUFFER_TOO_SMALL || Status == EFI_SUCCESS) {
                        DmiDataSize = (UINTN)dmiDataBuffer->DataLength;
					    Status = pRS->SetVariable(
					                        Var,
					                        &EfiSmbiosNvramGuid,
					                        EFI_VARIABLE_RUNTIME_ACCESS | EFI_VARIABLE_BOOTSERVICE_ACCESS | EFI_VARIABLE_NON_VOLATILE,
                                            DmiDataSize,
					                        (UINT8*)&dmiDataBuffer->StructureHeader);
					    ASSERT_EFI_ERROR(Status);
					}

                    if (Status != 0) {
                        return (UINT16)Status;
                    }
}
#endif

                    // Copy Type 127
                    MemCpy(&Type127Buffer, DestPtr, 4);
                    MemCpy(DestPtr, (UINT8*)&dmiDataBuffer->StructureHeader, dmiDataBuffer->DataLength);
                    DestPtr = DestPtr + GetStructureLength(DestPtr);
                    MemCpy(DestPtr, &Type127Buffer, 4);

                    // Update SMBIOS Structure Table Entry Point - Structure Table Length, Intermediate checksum
                    UpdateHeaderInfo();
                }

                Status = DMI_SUCCESS;
            }
            else {
                Status = DMI_ADD_STRUCTURE_FAILED;
            }
        }
        else {
            Status = DMI_ADD_STRUCTURE_FAILED;
        }
    }

    return Status;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   PnPFn52DeleteStructure
//
// Description: PnP function 52 Command 04: Delete structure
//
// Input:       IN SET_SMBIOS_STRUCTURE_DATA    *dmiDataBuffer
//              IN BOOLEAN                      Set
//
// Output:      UINT8 - Status
//
// Modified:
//
// Referrals:
//
// Notes:
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
UINT16
PnPFn52DeleteStructure (
    IN SET_SMBIOS_STRUCTURE    *p
)
{
    UINT16  Status;
    UINT8   *SmbiosTable = (UINT8*)((SMBIOS_TABLE_ENTRY_POINT*)SmbiosTableEntryPoint)->TableAddress;
    UINT8   *SmbiosTableEnd = SmbiosTable + ((SMBIOS_TABLE_ENTRY_POINT*)SmbiosTableEntryPoint)->TableLength;
    UINT8   *DestPtr;
    UINT16  i;
    UINT16  RemainingSize;
    SET_SMBIOS_STRUCTURE_DATA    *dmiDataBuffer;
    TABLE_INFO  TableInfo;

    dmiDataBuffer = (SET_SMBIOS_STRUCTURE_DATA*)p->Buffer32BitAddr;
    DestPtr = GetStructureByHandle(&((SET_SMBIOS_STRUCTURE_DATA*)dmiDataBuffer)->StructureHeader.Handle);
    if (DestPtr) {
        if (p->Control & 1) {
            UINT8           *SrcPtr;

            TableInfo.Type = dmiDataBuffer->StructureHeader.Type;
            TableInfo.Offset = 0xff;
            TableInfo.Reserved = 0;
            TableInfo.Flags = DMIEDIT_DELETE_STRUC | DMIEDIT_EXTENDED_HDR;
            TableInfo.HdrLength = sizeof(TABLE_INFO);
            TableInfo.Size = 0;
            TableInfo.Handle = dmiDataBuffer->StructureHeader.Handle;

#if !defined(SMBIOS_DMIEDIT_DATA_LOC) || SMBIOS_DMIEDIT_DATA_LOC != 2
            Status = UpdateSmbiosTable(&TableInfo, (UINT8*)&dmiDataBuffer->StructureHeader);
            if (Status != 0) {
                return Status;
            }
#else
{
			EFI_STATUS	Status;

            Swprintf(Var, L"DmiVar%02x%04x%02x%02x",
					   TableInfo.Type,
					   TableInfo.Handle,
					   TableInfo.Offset,
					   TableInfo.Flags);

			//
			// Get number of DMI data records in NVRAM
			//
			// Note: DMI data record actually starts with record #1,
			//		 first record #0 holds total number of DMI data records
			//       instead of TABLE_INFO
			//       ===> DmiArray[0].Type = count
			//
		    Status = pRS->GetVariable(
		                        DmiArrayVar,
		                        &EfiSmbiosNvramGuid,
		                        NULL,
		                        &DmiArraySize,
		                        &DmiArray);

			if (Status == EFI_SUCCESS) {
			    Index = DmiArray[0].Type;	// Note: DmiArray[0] has count # instead of Type/Offset
			    ++Index;
			}
			else {
				Index = 1;
			}

			// Check if record already exists
            //
            // DmiDataSize can be anything since the purpose of this GetVariable
            // call is to detect if the variable already exists or not. Its
            // content is not used.
            DmiDataSize = 0;                        // Dummy value
		    Status = pRS->GetVariable(
		                        Var,
		                        &EfiSmbiosNvramGuid,
		                        NULL,
		                        &DmiDataSize,
		                        &DmiData);

		    if (Status == EFI_NOT_FOUND) {
				// Record not present, increment record count
		        DmiArray[Index].Type = TableInfo.Type;
		        DmiArray[Index].Handle = TableInfo.Handle;
		        DmiArray[Index].Offset = TableInfo.Offset;
		        DmiArray[Index].Flags = TableInfo.Flags;

		        DmiArray[0].Type += 1;          // Increment # variable counter

		        Status = pRS->SetVariable(
		                            DmiArrayVar,
		                            &EfiSmbiosNvramGuid,
		                            EFI_VARIABLE_RUNTIME_ACCESS | EFI_VARIABLE_BOOTSERVICE_ACCESS | EFI_VARIABLE_NON_VOLATILE,
		                            DmiArraySize,
		                            &DmiArray);
		        ASSERT_EFI_ERROR(Status);
                if (Status != 0) {
                    return (UINT16)Status;
                }
		    }

			// Update DMI data record if already exists,
			// or store new record if total record count in DmiArray was successfully
			// updated
            if (Status == EFI_BUFFER_TOO_SMALL || Status == EFI_SUCCESS) {
                DmiDataSize = (UINTN)sizeof(TABLE_INFO);
			    Status = pRS->SetVariable(
			                        Var,
			                        &EfiSmbiosNvramGuid,
			                        EFI_VARIABLE_RUNTIME_ACCESS | EFI_VARIABLE_BOOTSERVICE_ACCESS | EFI_VARIABLE_NON_VOLATILE,
                                    DmiDataSize,
			                        &TableInfo);
			    ASSERT_EFI_ERROR(Status);
			}

            if (Status != 0) {
                return (UINT16)Status;
            }
}
#endif

			// Copy / update the remaining structures in the Smbios Table
            SrcPtr = DestPtr + GetStructureLength(DestPtr);
            RemainingSize = (UINT16)(SmbiosTableEnd - SrcPtr);

            for (i = 0; i < RemainingSize; i++) {
                *DestPtr = *SrcPtr;
                SrcPtr++;
                DestPtr++;
            }

            // Update SMBIOS Structure Table Entry Point - Structure Table Length, Intermediate checksum
            UpdateHeaderInfo();
        }

        Status = DMI_SUCCESS;
    }
    else {
        Status = DMI_INVALID_HANDLE;
    }

    return Status;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   SetSmbiosStructure
//
// Description: DMIEdit function to update the structures and saves the
//              DMI data in the Flash Part for subsequent boot.
//
// Input:       IN SET_SMBIOS_STRUCTURE    *p
//
// Output:      UINT8 - Status
//
// Modified:
//
// Referrals:
//
// Notes:
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
UINT16
SetSmbiosStructure(
    IN SET_SMBIOS_STRUCTURE    *p
)
{
    SET_SMBIOS_STRUCTURE_DATA *Data = (SET_SMBIOS_STRUCTURE_DATA *)p->Buffer32BitAddr;
    UINT8                     *SmbTable;
    UINT16                    Handle = Data->StructureHeader.Handle;

    if (!SmbiosTableEntryPoint) return DMI_FUNCTION_NOT_SUPPORTED;

    if (Data->Command == 3) {           // Add structure
        return PnPFn52AddStructure(p);
    }

    if (Data->Command == 4) {           // Delete structure
        return PnPFn52DeleteStructure(p);
    }

    SmbTable = GetStructureByHandle(&Handle);
    if (!SmbTable) return DMI_INVALID_HANDLE;

    // Verify header
    if (*(UINT16*)&Data->StructureHeader != *(UINT16*)SmbTable) return DMI_BAD_PARAMETER;

    // Currently only accept certain table types;
    switch (Data->StructureHeader.Type) {
        case 0:
                return SetType0(Handle, Data, p->Control&1);
        case 1:
                return SetType1(Handle, Data, p->Control&1);
#if BASE_BOARD_INFO
        case 2:
                return SetType2(Handle, Data, p->Control&1);
#endif
#if SYS_CHASSIS_INFO
        case 3:
                return SetType3(Handle, Data, p->Control&1);
#endif
#if PROCESSOR_DMIEDIT_SUPPORT
        case 4:
                return SetType4(Handle, Data, p->Control&1);
#endif
#if OEM_STRING_INFO
        case 11:
                return SetType11(Handle, Data, p->Control&1);
#endif
#if SYSTEM_CONFIG_OPTION_INFO
        case 12:
                return SetType12(Handle, Data, p->Control&1);
#endif
#if PORTABLE_BATTERY_INFO
        case 22:
                return SetType22(Handle, Data, p->Control&1);
#endif
#if SYSTEM_POWER_SUPPLY_INFO
        case 39:
                return SetType39(Handle, Data, p->Control&1);
#endif
    }
    return DMI_BAD_PARAMETER;
}

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
