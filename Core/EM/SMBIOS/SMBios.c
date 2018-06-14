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
// $Header: /Alaska/SOURCE/Modules/SMBIOS/SMBios.c 157   4/19/16 4:10p Davidd $
//
// $Revision: 157 $
//
// $Date: 4/19/16 4:10p $
//**********************************************************************//
// Revision History
// ----------------
// $Log: /Alaska/SOURCE/Modules/SMBIOS/SMBios.c $
// 
// 157   4/19/16 4:10p Davidd
// [TAG]  		EIP231162
// [Category]  	New Feature
// [Description]  	Merge Aptio V Smbios -09 changes for Aptio 4
// 4.6.5.5_SMBIOS_40 release
// [Files]  		Smbios.c
//
// 156   4/07/16 6:01p Davidd
// [TAG]  		EIP231162
// [Category]  	New Feature
// [Description]  	Merge Aptio V Smbios -09 changes for Aptio 4
// 4.6.5.5_SMBIOS_40 release
// [Files]  		Smbios.c
// SmbiosDmiEdit.c
// SmbiosDmiEditFunc.c
//
// 155   2/22/16 2:41p Davidd
// [TAG]  		EIP254247
// [Category]  	Bug Fix
// [Severity]  	Minor
// [Symptom]  	Static code analysis issues found in Aptio4 SMBIOS - Core
// Source module
// [RootCause]  	Function CheckForType4AndUpdate is not typed
// [Solution]  	Added VOID type to function CheckForType4AndUpdate
// [Files]  		Smbios.c
//
// 154   8/11/14 10:52a Davidd
// [TAG]  		EIP181005
// [Category]  	Improvement
// [Description]  	Updated version number for Aptio 4 4.6.5.4_SMBIOS_38
// release
// [Files]  		Smbios.c
//
// 153   8/11/14 10:42a Davidd
// [TAG]  		EIP177887
// [Category]  	Bug Fix
// [Severity]  	Minor
// [Symptom]  	Build error if token "SYS_CHASSIS_INFO" set to "0"
// [RootCause]  	Build error caused by non-existence token when
// SYS_CHASSIS_INFO is disabled
// [Solution]  	Added preprocessor checks
// [Files]  		Smbios.c
// SmbiosDmiEditFunc.c
//
// 152   8/08/14 1:19p Davidd
// [TAG]  		EIP103526
// [Category]  	Improvement
// [Description]  	We should update Wake-up Type in SMBIOS type 1
// dynamically
// [Files]  		SMBIOSCore.cif
// SMBios.c
// New SmbiosPeim module part
//
// 151   6/13/14 3:22p Davidd
// [TAG]  		EIP171151
// [Category]  	Bug Fix
// [Severity]  	Minor
// [Symptom]  	Smbios Type 12 - Changes beyond string #8 were not
// persistent across the reboot
// [RootCause]  	Test flag is only 8 bits
// [Solution]  	Create and use array of test flags for specified number of
// Type 12 structure
// [Files]  		Smbios.c
// Smbios.h
//
// 150   4/29/14 4:42p Davidd
// [TAG]  		EIP103526
// [Category]  	Improvement
// [Description]  	We should update Wake-up Type in SMBIOS type 1
// dynamically
// [Files]  		SMBIOSCore.cif
// SMBios.c
// New SmbiosPeim module part
//
// 149   2/14/14 12:41p Davidd
// [TAG]  		EIPEIP152598
// [Category]  	Bug Fix
// [Severity]  	Normal
// [Symptom]  	SMBIOS UUID can't be updated by DMIEdit tool
// [RootCause]  	Update flag not set for changing UUID field
// [Solution]  	Set Update flag when changing UUID field
// [Files]  		Smbios.c
//
// 148   11/18/13 1:00p Davidd
//
//
// [TAG]           EIP143631
// [Category]      Bug Fix
// [Severity]      Normal
// [Symptom]       Silent code corruption caused by AddProducerHandle
// routine
// [RootCause]     Variable "i" declare as unsigned eight bit integer,
// should be sixteen bit because PRODUCER_HANDLE_ELEMENTS is set to value
// 0x200
// [Solution]      Changed variable "i" to 16-bit
// [Files]         Smbios.c
//
// 147   11/15/13 4:32p Davidd
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
// 146   8/23/13 6:23p Davidd
// [TAG]  		EIP132364
// [Category]  	Improvement
// [Description]  	DMIEdit fails to update in the following cases:
// 1. When current string is NULL
// 2. When structure is created by OEM
// 3. When structure is created with strings not numbered sequentially
// [Files]  		Smbios.c
// SmbiosDMIEditFunc.c
//
// 145   6/03/13 6:25p Davidd
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
// 144   6/03/13 4:18p Davidd
// [TAG]  		EIP104836
// [Category]  	New Feature
// [Description]  	DMIEdit support edit type 4
// [Files]  		Smbios.c
//
// 143   5/29/13 12:51p Davidd
// [TAG]  		EIP124735
// [Category]  	Spec Update
// [Severity]  	Normal
// [Description]  	SMBIOS 2.8.0 specification support for Aptio 4
// [Files]  		Smb.equ
// Smbdata.mac
// Smbdesc.def
// Smbstruc.def
// Smbios.c
// Smbios.h
// SmbiosDynamicData.h
//
// 142   5/23/13 2:41p Davidd
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
// 141   5/23/13 10:43a Davidd
// [TAG]  		EIP124483
// [Category]  	Bug Fix
// [Severity]  	Normal
// [Symptom]  	After updating to SMBIOS 33, issue found with smbios type 4
// &7 & 10 & 11 & 13 &14
// [RootCause]  	Changes in EIP99697
// [Solution]  	Added control token SMBIOS_DYNAMIC_UPDATE_POLICY. Default
// setting is 0 to do dynamic update at Ready To Boot event for backward
// compatibility.
// [Files]  		Smbios.sdl
// Smbios.c
//
// 140   3/15/13 3:37p Davidd
// [TAG]  		EIP118222
// [Category]  	Bug Fix
// [Severity]  	Minor
// [Symptom]  	Build error in Core\EM\SMBIOS\SMBios.c
// [RootCause]  	"Status" variable declared outside of all "#if"
// statements therefore when all "#if" statement evaluated to false,
// "Status" variable becomes un-used
// [Solution]  	Initialize "Status" variable on declaration.
// [Files]  		Smbios.c
//
// 139   12/27/12 11:05a Davidd
// [TAG]  		EIP108986
// [Category]  	Bug Fix
// [Severity]  	Minor
// [Symptom]  	SMBIOS type 13 structure not present
// [RootCause]  	This problem is caused by recent change for EIP98861
// (function AddUpdateType13 was moved to UpdateDynamic)
// [Solution]  	Move AddUpdateType13 function back to SmbiosDynamicUpdate
// [Files]  		Smbios.c
//
// 138   9/19/12 1:32p Davidd
// [TAG]  		EIP101114
// [Category]  	Bug Fix
// [Severity]  	Normal
// [Symptom]  	System got an assert and hung after updated Smbios -031 to
// -032 label
// [RootCause]  	Bug in "SmbiosPiGetNextStructure" function.
// [Solution]  	Revised "SmbiosPiGetNextStructure" function.
// [Files]  		Smbios.c
//
// 137   9/04/12 4:49p Davidd
// [TAG]  		EIP100134
// [Category]  	Bug Fix
// [Severity]  	Minor
// [Symptom]  	SMBIOS type 17 dimm Rank information is not correct.
// [RootCause]  	Error in function "DynamicUpdateMemoryData"
// [Solution]  	For DDR3, ranking information is at SPD byte 7 bits 5-3.
// Code has been added to properly shift the value being read before it is
// used.
// [Files]  		Smbios.c
//
// 136   9/04/12 2:49p Davidd
// [TAG]  		EIP99697
// [Category]  	Improvement
// [Description]  	To make a generic fix for the SMBIOS type 19 problem
// (see parent EIP 98861)
// [Files]  		Smbios.c
//
// 135   8/02/12 12:41p Davidd
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
// 134   6/12/12 5:11p Davidd
// [TAG]  		EIP63922
// [Category]  	Improvement
// [Description]  	After udpate SMBIOS to v30, system hang at CKP 0xA0 if
// DEBUG_MODE = 1.
// Note: Changes made for TMP usage of Smbios.
// [Files]  		Smbios.c
//
// 133   6/12/12 10:34a Davidd
// [TAG]  		EIP92170
// [Category]  	Improvement
// [Description]  	Adding DmiEdit support for multiple instances of Smbios
// type 39 structure to match with AMI DmiEdit tool
// [Files]  		Smbios.c
//
// 132   6/11/12 11:30a Davidd
// [TAG]  		EIP92170
// [Category]  	Improvement
// [Description]  	Adding DmiEdit support for multiple instances of Smbios
// type 39 structure to match with AMI DmiEdit tool
// [Files]  		Smbios.h
// Smbios.c
// SmbiosStaticData.sdl
//
// 131   4/09/12 12:45p Davidd
// [TAG]  		EIP86776
// [Category]  	Bug Fix
// [Severity]  	Normal
// [Symptom]  	Build error if "OEM_STRING_INFO" token is set to "0"
// [RootCause]  	SMBIOS_OEM_STRINGS_INFO definition is used even when
// OEM_STRING_INFO is disabled.
// [Solution]  	Removed reference to "SMBIOS_OEM_STRINGS_INFO" in
// "GetStructureLength" function (not really needed).
// [Files]  		Smbios.c
//
// 130   4/09/12 12:32p Davidd
// [TAG]  		EIP86487
// [Category]  	Bug Fix
// [Severity]  	Critical
// [Symptom]  	AMIDEDOS update Type 3 Asset Tag failed
// [RootCause]  	Incorrectly checking for empty string size
// [Solution]  	Corrected code
// [Files]  		Smbios.c
//
// 129   3/26/12 12:06p Davidd
// [TAG]  		EIP84370
// [Category]  	New Feature
// [Description]  	Flash memory(type 16 and 17) on aptio
// [Files]  		Smbdata.mac
// SmbiosStaticData.asm
// SmbiosStaticData.sdl
// Smbios.c
// Smbios.mak
// Smbios.h
//
// 128   3/16/12 5:36p Davidd
// [TAG]  		EIP84942
// [Category]  	Bug Fix
// [Severity]  	Normal
// [Symptom]  	Incorrect "next handle" returned by Smbios->GetNext
// function
// [RootCause]  	Next handle incorrectly return with next sequential
// record handle.
// [Solution]  	Modified code to return next record handle having the same
// input type.
// [Files]  		Smbios.c
//
// 127   3/09/12 10:59a Davidd
// [TAG]  		    EIP81469
// [Category]  	Bug Fix
// [Severity]  	Normal
// [Symptom]  	    SMBIOS protocl didn't compatible with PI1.1
// [RootCause]  	PI1.1 protocol functions incorrectly added after AMI
// functions of Smbios protocols.
// [Solution]  	Moved PI1.1 protocol functions to the top of the protocol.
// [Files]  		Smbios.c
//                 Smbios.h
//
// 126   3/08/12 5:17p Davidd
// [TAG]  		EIP81171
// [Category]  	Bug Fix
// [Severity]  	Normal
// [Symptom]  	Smbios->GetNext function fail when type is NULL
// [RootCause]  	GetNext function does not checked for Type pointer
// [Solution]  	Added code to check for Type pointer in GetNext function
// [Files]  		Smbios.c
//
// 125   2/02/12 12:36p Davidd
// [TAG]  		EIP81514
// [Category]  	Bug Fix
// [Severity]  	Normal
// [Symptom]  		Wrong handle number assigned to the structure when adding
// structure with a specific handle number using Smbios "Add" protocol
// [RootCause]  	Handle number is not updated when "Add" protocol is
// called with a specific handle number.
// [Solution]  	Change code to update handle number
// [Files]  		Smbios.c
//
// 124   2/02/12 10:09a Davidd
// [TAG]  		EIP81010
// [Category]  	Improvement
// [Description]  	Smbios type 13 only supports a subset of languages
// supported by the CORE
// [Files]  		Smbios.c
//
// 123   1/17/12 4:52p Davidd
// [TAG]           EIP78264
// [Category]      Improvement
// [Description]   SMBOS Type 2 (Spec 2.7.1) - No multiple type 2 support
// [Files]         Smbios.c
//                 Smbios.h
//                 Smbdata.mac
//                 Smbdesc.def
//                 SmbiosStaticData.sdl
//
// 122   1/06/12 3:26p Davidd
// [TAG]  		EIP78790
// [Category]  	Improvement
// [Description]  	Locating LegacyRegion2 Protocol fails in SMBIOS31 when
// Bios is Built with PI 1.1 or lesser
// [Files]  		Smbios.c
// Smbios.dxs
//
// 121   12/01/11 5:08p Davidd
// [TAG]           EIP76832
// [Category]      Bug Fix
// [Severity]      Normal
// [Symptom]       On 4641 Core after Updating to 4.6.3_SMBIOS_31 and
// adding 4.6.5.1_ForwCompatibility_01 system asserts in Smbios64.Entry()
// [RootCause]     Problem caused by a redundant FreePool call in
// UpdateStructuresWithNvramData function
// [Solution]      Removed the redundant FreePool call in
// UpdateStructuresWithNvramData function
// [Files]         Smbios.c
//
// 120   11/17/11 2:37p Davidd
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
// 119   10/06/11 5:32p Davidd
// EIP65648 extended change, and some operator usage error corrections.
//
// 118   9/29/11 5:18p Davidd
// [TAG]           EIP71370
// [Category]      Improvement
// [Description]   Customer names in source files
// [Files]         Smbios.c
//
// 117   9/29/11 4:38p Davidd
// [TAG]           EIP68202
// [Category]      NEW FEATURE
// [Description]   Allow Smbios Type 2 Location field and Type 3 SKU
// Number field
//                 to be apdated by dmieditwingui tool
// [Files]         Smbios.c
//                 SmbiosDMIEditFunc.c
//                 Smbdata.mac
//
// 116   8/30/11 4:11p Davidd
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
// 115   8/12/11 10:57a Davidd
// [TAG]           EIP60077
// [Category]      Improvement
// [Description]   BSP waits for all Aps forever when
// SmbiosAddStrucByHandle () function is called from SMM
// [Files]         Smbios.c
//
// 114   8/11/11 12:17p Davidd
// [TAG]           EIP66223
// [Category]      Bug Fix
// [Severity]      Immediate/Critical
// [Symptom]       Status check is missing from Code that tries to call
// LoadRealModeFileSection()
// [RootCause]     Status check is missing
// [Solution]      Added code to check for status after call to
// LoadRealModeFileSection()
// [Files]         Smbios.c
//
// 113   8/03/11 10:53a Davidd
// [TAG]           EIP64029
// [Category]      NEW FEATURE
// [Description]   Allow SMBIOS Type 22 to be modified using DMIEdit
// [Files]         Smbios.h
//                 Smbios.c
//                 SmbiosDmieditFunc.c
//
// 112   8/03/11 10:23a Davidd
// [TAG]           EIP65551
// [Category]      Bug Fix
// [Severity]      Non-Urgent
// [Symptom]       There is an issue in adding a new table to SMBIOS by
// using PI 1.1 protocol
// [RootCause]     SmbiosHandle parameter is not updated with assigned
// handle number
// [Solution]      Update SmbiosHandle parameter with assigned handle
// number
// [Files]         Smbios.c
//
// 111   6/16/11 12:25p Davidd
// [TAG]           EIP61776
// [Category]      Improvement
// [Description]   SMBIOS Type 17 "Type Detail" Registered/Unbuffered,
// needs to be dynamically updated
// [Files]         Smbios.sdl
//                 SmbiosDynamicData.h
//                 Smbios.c
//
// 110   5/25/11 10:20a Davidd
// [TAG]           EIP57961
// [Category]      Bug Fix
// [Severity]      Non-Urgent
// [Symptom]       AMIDEDOS.exe fails to flash UUID & serial number
// [RootCause]     E000-F000 is locked during E000 memory allocation for
// Smbios table.
// [Solution]      Unlock E000 prior to allocation and lock it afterward.
// [Files]         Smbios.c
//
// 109   5/24/11 10:36a Davidd
// [TAG]           EIP60846
// [Category]      Bug Fix
// [Severity]      Normal
// [Symptom]       SMBIOS build error after disable "MEMORY_DEVICE_INFO"
// [RootCause]     Local variable "SmbDmap" is unreferenced when
// MEMORY_DEVICE_INFO token is turned off.
// [Solution]      Added conditional compilation check around "SmbDmap"
// variable.
// [Files]         Smbios.c
//
// 108   5/13/11 5:21p Davidd
// [TAG]           EIP57758
// [Category]      Bug Fix
// [Severity]      Normal
// [Symptom]       DMIEDIT tool shows error message "Cann't update Smbios
// Date with PNP function on current system!!" "Error getting DMI
// data!!(Error code : 12000E)"
// [RootCause]     Because Smbios Structure Table Entry Point header is
// relocated on ReadyToBoot, it could not be found at runtime.
// [Solution]      Allocate runtime memory for Smbios Structure Table
// Entry Point header on Smbios driver entry point.
// [Files]         Smbios.c
//                 Smbios.dxs
//
// 107   5/11/11 12:32p Davidd
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
// 106   5/06/11 10:52a Davidd
// [TAG]           EIP58832
// [Category]      Bug Fix
// [Severity]      Normal
// [Symptom]       [Type 11]Oem String can't be updated from nvram if
// string number >8
// [RootCause]     Size of variable used to test the strings was wrong.
// [Solution]      Corrected the size of the variable.
// [Files]         Smbios.c
//
// 105   5/04/11 3:18p Davidd
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
// 104   4/05/11 11:06a Davidd
// [TAG]           EIP57586
// [Category]      Improvement
// [Description]   Build error in SMBios module when CSM_SUPPORT token
// turned OFF
// [Files]         SmbiosBoard.c - File version: 24
//
// 103   1/27/11 10:52a Davidd
// [TAG]  		EIP52709
// [Category]  	Bug Fix
// [Severity]  	Minor
// [Symptom]  	After we update SMBIOS Type11 using SMBCFG.exe in debug
// mode and then reboot, system will hang up
// [RootCause]  	FreePool in UpdateSmbiosTable function is called with a
// pointer pointing to an allocated memory location plus some offset the
// first time.
// [Solution]  	Skip FreePool call in UpdateSmbiosTable function the first
// time. This memory is freed later in SmbiosDriverEntryPoint function.
// [Files]  		Smbios.c
//
// 102   12/14/10 3:38p Davidd
// Updated StringType_3 table to include SKU string field.
//
// 101   12/10/10 3:04p Davidd
// [TAG]           EIP49728
// [Category]      BUG FIX
// [Severity]      Normal
// [Symptom]       SMBIOS Type 10 Data incorrect
// [RootCause]     Macro to create Type 10 structure is incorrect.
// [Solution]      Modified macro to create one Type 10 Entry containing
// the number of ONBOARD_DEVICES.
// [Files]
//    Smbdata.mac
//    Smbios.c
//
// 100   12/08/10 10:56a Davidd
// [TAG]           EIP48952
// [Category]      Improvement
// [Description]   Customer Request for SMBIOS Type 16
// MemoryErrorCorrection field to be filled out
// [Files]
//    Smbios.c
//    SmbiosDynamicData.h
//
// 99    11/22/10 12:09p Davidd
// [TAG]           EIP44236
// [Category]      BUG FIX
// [Severity]      Normal
// [Symptom]       SMBIOS type 4 Processor Version is incorrect
// [RootCause]     Type 4 Version string is not resized as updated.
// [Solution]      Added code to replace the Version strings as updated.
// Same
// also applied to Manufacturer string.
// [Files]         Smbios.c
//
// 98    11/19/10 6:20p Davidd
// [TAG]           EIP46175
// [Category]      Improvement
// [Description]   Redesign SMBIOS to avoid redundant SPD reading
// [Files]
//    Smbios.c
//    SmbiosDynamicData.h
//
// 97    11/17/10 10:40a Davidd
// [TAG]           EIP48415
// [Category]      BUG FIX
// [Severity]      Normal
// [Symptom]       Logic Operator Error in Smbios.c
// [RootCause]     Wrong operator used.
// [Solution]      Change "Bitwise AND" operator to "Logical AND".
// [Files]         Smbios.c
//
// 96    11/15/10 3:55p Davidd
// [TAG]           EIP46175
// [Category]      Improvement
// [Description]   Redesign SMBIOS to avoid redundant SPD reading
// [Files]
//    Smbios.c
//    SmbiosDynamicData.h
//
// 95    11/15/10 2:46p Davidd
// [TAG]           EIP47697
// [Category]      BUG FIX
// [Severity]      Normal
// [Symptom]       SMBIOS Type 0 BIOS version string update does not
// retain over Reboot
// [RootCause]     Wrong index used for StringSet array.
// [Solution]      Corrected index.
// [Files]         Smbios.c
//
// 94    11/15/10 2:15p Davidd
// [TAG]           EIP46936
// [Category]      Improvement
// [Description]   Generic Smbios module should have the support to
// disable SMBIOS memory update
// [Files]
//    Smbios.c
//    Smbios.sdl
//    SmbiosBoard.c
//    SmbiosDynamicData.h
//
// 93    11/02/10 4:11p Davidd
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
// 92    11/01/10 12:26p Davidd
// [TAG]  		EIP41560
// [Category]  	Improvement
// [Description]  	DMIEDIT modified values are not preserved in reboot
// [Files]
//    Smbios.c
//    Smbios.sdl
//    SmbiosBoard.c
//    SmbiosBoard.mak
//
// 91    10/27/10 7:05p Davidd
//
// 90    10/25/10 5:02p Davidd
// [TAG]  		EIP42457
// [Category]  	Improvement
// [Description]  	SMBIOS data in not legacy boot (when boot to EFI OS)
// [Files]  		Smbios.c
//
// 89    10/21/10 11:33a Davidd
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
// 88    10/20/10 6:12p Davidd
// [TAG]  		EIP46454
// [Category]  	Improvement
// [Description]  	SMBIOS hangs after copying memory to below 1MB after
// installing type 4 structure (This only happened with new changes to let
// CPU module create Type 4 structure instead of the Smbios module).
// [Files]  		Smbios.c
//
// 87    10/19/10 5:49p Davidd
// [TAG]  		EIP46454
// [Category]  	Improvement
// [Description]  	SMBIOS hangs after copying memory to below 1MB after
// installing type 4 structure (This only happened with new changes to let
// CPU module create Type 4 structure instead of the Smbios module).
// [Files]
//    Smbios.c
//
// 86    10/15/10 3:57p Davidd
// [TAG]  		EIPEIP 45855
// [Category]  	Improvement
// [Description]  	[SMBIOS] Type1 will be removed to the latest if it
// updated.
// [Files]  		Smbios.sdl, Smbios.c
//
// 85    10/12/10 11:43a Davidd
// Added code to insert new structure at location specified by
// ADD_STRUCTURE_LOCATION token.
//
// 84    10/08/10 8:00p Davidd
// [TAG]		EIP43278
//
// [Category]	Function Request
//
// [Severity]	Normal
//
// [Description]	SMBIOS 2.7 requirement
//
// [Files]		Core\EM\SMBIOS\Smbios.c
//
// 82    9/09/10 11:28a Davidd
// Fixed Type 13 string format to comply with Smbios specification - EIP
// 43695.
//
// 81    8/18/10 5:54p Davidd
// Changes added to close the Exxxx / F0000 shadow region after being
// opened for update - EIP 42187.
//
// 80    6/30/10 6:42p Davidd
// Fixed some DMI utility, which uses PnP function calls, not working
// issue after type0 structure was updated by SmbiosWriteStructure()
// protocol - EIP 39849.
//
// 79    6/29/10 9:20a Olegi
// EIP40313: removed CSM16_LOCATION token reference.
//
// 78    5/18/10 5:08p Davidd
// Added PnP function 52h commands 3 and 4 support - EIP 38010.
//
// 77    5/14/10 11:28a Davidd
// Added code to update Smbios Table Header after changes to structure
// done in PI 1.1 Add/Remove/Change String functions.
//
// 76    5/06/10 10:39a Davidd
// Added Smbios PI 1.1 support - EIP 37736.
//
// 75    4/27/10 5:24p Davidd
// Added some memory manufacturer names to the JEDEC table - EIP 37608.
//
// 74    4/21/10 12:14p Davidd
// Added function "FilterCharacter" to filter the SPD data for Type 17
// Manufacturer and Part Number string into readable form.
//
// 73    4/20/10 12:49p Davidd
// Fixed incorrect memory type 17 Manufacturer field issue - EIP 37608.
//
// 72    4/09/10 3:49p Davidd
// Corrected the issues listed in the Coverity Code and security analysis
// report - EIP 34502
//
// 71    4/06/10 10:59a Davidd
// Set structure type 13 Reserved field to zero.
//
// 70    4/06/10 10:27a Davidd
// Changes made to dynamically create type 13 structure  (BIOS Language
// Information) based on SUPPORTED_LANGUAGES token if enabled - EIP 34939.
//
// 69    2/26/10 5:46p Davidd
// - Corrected a potential buffer overflow problem in
// UpdateStructuresWithNvramData function - EIP 34379
// - Corrected a potential use of uninitialzied pointer in
// DynamicUpdateCpuData function - EIP 34379
//
// 68    12/03/09 4:39p Davidd
// Corrected a hanging problem when UpdateSmbiosTable function is called
// to add a structure but it is found to be invalid. In this case, memory
// has not been allocated, but at the end of the function memory
// deallocation is called.
//
// 67    11/23/09 5:50p Davidd
// Corrected the DMIEdit data not updated after being updated 5-6 times
// (when NVRAM is used to store DMIEdit data) - EIP 30837.
//
// 66    8/11/09 2:54p Davidd
// Corrected build error when CSM support is not present.
//
// 65    8/06/09 3:30p Davidd
// Fixed a duplicate handle problem in case a structure with handle =
// LastHandle was added by SmbiosAddStrucByHandle, and then another
// structure was added with SmbiosAddStructure.
//
// 64    8/05/09 6:17p Davidd
// Added DMIEDIT support for Type 0 and Type 12 structures - EIP 24878
//
// 63    7/16/09 4:59p Davidd
// Fixed the problem of missing the last character in the Manufacturer and
// Version strings of SMBIOS CPU Type 4. (EIP 23633)
//
// 62    6/02/09 11:12a Davidd
// Updated function headers. (EIP 22180)
//
// 61    6/02/09 10:55a Davidd
//
// 60    5/19/09 10:47a Davidd
// Changes added to improve memory type 17 porting.
//
// 59    1/28/09 11:45a Davidd
// - Removed UpdateStructuresWithNvramType0 and
// UpdateStructuresWithNvramType12 functions (not supported by DMIEdit
// utility)
// - New changes added to support storage locations for DMIEdit data in
// NVRAM.
//
// 58    12/23/08 3:20p Davidd
// Corrected the random hanging issue when PORTABLE_BATTERY_INFO is
// enabled.
//
// 57    11/18/08 10:21a Davidd
// - Fixed a bug calculating the number of rank for the attribute field
// for memory structure type 17.
// - Added code to fill in the Total Width and Data Width fields from SPD
// data.
//
// 56    11/14/08 4:19p Davidd
// - Added GetFreeHandle protocol
// - Added AddStructureByHandle protocol
// - Added ReadStructureByType protocol
// - Added a call to the OEM porting hook OemUpdate. OEM can make changes
// to the SMBIOS table in this hook
//
// 55    10/31/08 10:31a Davidd
// Correct problem of Additional Info structure not updated when
// PORTABLE_BATTERY_INFO is enabled.
//
// 54    10/27/08 2:52p Davidd
// Code clean up.
//
// 53    10/23/08 6:44p Davidd
// - Added changes to support SMBIOS version 2.5 and 2.6.
// - Changes added for dynamic table sizing.
// - Code added to update some memory info obtained from SPD data for type
// 17
//
// 52    10/10/08 5:21p Davidd
// Corrected a build error in x64 bit mode - EIP 16894
//
// 51    10/06/08 1:19p Davidd
// Renamed SMBIOS_TABLE_E000 token to SMBIOS_TABLE_LOCATION.
// Added Auto option to SMBIOS_TABLE_LOCATION token.
// Code added to check for memory allocation error in
// Install16bitPnPSmbiosFunctions.
//
// 50    9/26/08 10:41a Davidd
// Made changes to either put the SMBIOS table at E000 segment or above
// 1MB (selectable via SMBIOS_TABLE_E000 token)
//
// 49    8/12/08 5:45p Davidd
// Added conditional compilation switch based on SmbiosDMIEdit_SUPPORT and
// SmbiosFlashData_SUPPORT SDL tokens to correct build error when either
// one of those tokens is disabled
//
// 48    7/23/08 10:38a Davidd
// Corrected a bug assigning new handle in AddStructure function.
//
// 47    2/13/08 7:24p Davidd
// Corrected a build issue in 64 bit mode.
//
// 46    2/06/08 3:36p Davidd
// - In DynamicUpdateCpuData, use gSmbiosBoardProtocol->NumberOfCPU
// instead of NO_OF_PROCESSOR_SOCKETS to represent the number of
// proccessors in the system in case when project only has SMBIOS binary
// component.
// - Moved the "#if PORTABLE_BATTERY_INFO" to only enclose the
// DynamicUpdateBatteryData function.
// - In DynamicUpdateBatteryData, use
// gSmbiosBoardProtocol->NumberOfBatteries instead of
// NO_OF_PORTABLE_BATTERY to represent the number of batteries in the
// system in case when project only has SMBIOS binary component.
//
// 45    2/05/08 11:21a Davidd
// Rearranged the code flow in DynamicUpdateMemoryData.
//
// 44    2/04/08 1:57p Davidd
// Fixed a problem updating battery data when BIOS is built with multiple
// battery structures but some of them are invalid during POST.
//
// 43    1/30/08 3:51p Davidd
// Changes made to SMBIOS type 17 with multiple memory arrays.
//
// 42    1/22/08 4:29p Olegi
//
// 41    12/26/07 5:07p Olegi
// Added Install16bitPnPSmbiosFunctions() funciton.
//
// 40    12/20/07 11:28a Davidd
// Added code to skip calling SmbiosCreateBatteryDevData when
// PORTABLE_BATTERY_INFO is set to OFF. This fixes the hanging issue when
// BIOS is built with SMBIOS binary only.
//
// 39    12/19/07 4:59p Davidd
// Fixed code to abort updating CPU related data if getting CPU data
// variable resulted in error.
//
// 38    12/14/07 6:53p Davidd
// Corrected build error when Type 18 is enabled.
//
// 37    12/14/07 11:01a Davidd
// Added conditional IF statement for DynamicUpdateOnboardDevData function
// to fix the build error in case ONBOARD_DEVICE_INFO is set to OFF.
//
// 36    12/14/07 10:44a Davidd
//
// 35    12/07/07 12:32p Davidd
// Restore the UpdateEPSHeader call in the Addstructure and
// DeleteStructureByHandle functions.
//
// 34    11/26/07 5:05p Davidd
// Changes added to dynamically update Voltage field in Processor
// Information structure type 4.
//
// 33    11/21/07 10:33a Davidd
// Added code to dynamically update Portable Battery Data structure type
// 22.
//
// 32    9/12/07 2:28p Davidd
// Added changes to set memory type and speed to unknown for unoccupied
// memory slot.
//
// 31    9/06/07 10:57a Davidd
// Corrected the UUID reversal problem.
//
// 30    30/08/07 2:13p Anandakrishnanl
// Added token switch in SMBIOS for checking if iAMT_SUPPORT is Defined.
//
// 29    7/10/07 3:05p Davidd
// Fixed bug for DMIEdit Type 12 support.
//
// 28    6/29/07 5:31p Davidd
// AMT3.0: Update: SMBIOS Module modifed to match Compliance Test For AMT
//
// 27    6/20/07 10:37a Pats
// Modified to support editing of SMBIOS structure type 0, offsets 5 and
// 8.
//
// 26    6/05/07 4:15p Michaela
// Modified DynamicUpdateCpuData() to use
// SMBIOS_CPU_INFO_PROTOCOL and provide backward
// compatibility for old method, which used  the "CPU_DATA" variable
//
// 25    4/13/07 11:35a Davidd
// Updated to coding standard.
//
// 24    3/29/07 5:56p Davidd
// Changed the year in the AMI banner and adjust indentation to coding
// standard.
//
// 23    3/21/07 4:46p Michaela
// made changes to DynamicUpdateMemoryData to support multiple
// memory arrays
//
// 22    3/14/07 1:18p Pavell
// Changes for ITK support
//
// 21    12/15/06 5:39p Davidd
// Code cleanup and reformatted to coding standard.
//
// 20    10/27/06 3:10p Davidd
// Corrected the problem getting the string index in GetType1StringIndex
//
// 19    10/13/06 6:34p Felixp
// UEFI 2.0 compliant handling of ready to boot event
//
// 18    10/05/06 4:48p Davidd
// Changes added for 64 bit support.
//
// 17    3/21/06 5:12p Davidd
// Set L3 Cache Handle to 0xFFFF if L3 cache size is zero.
//
// 16    3/02/06 1:53p Davidd
// Updated include path to SMBios.h. It has been moved to
// Include\Protocol
//
// 15    3/02/06 11:00a Davidd
// Corrected CPU dynamic updation and removed fields deemed static in
// memory structures.
//
// 14    11/07/05 6:17p Davidd
// Changes made to support AMIBCP.
//
// 13    8/10/05 10:32a Davidd
// Added #include SmbiosGetFlashDataProtocol.h (EFI_SMBIOS_PROTOCOL_GUID
// has been moved to this file).
//
// 12    8/05/05 11:31a Davidd
// Made SmbiosVariableSize platform independent to fix the binary issue
// (ex: if binary built with 2 memory slot, SMBIOS will wrongly report the
// memory size on a system with 4 memory slot).
//
// 11    8/01/05 2:47p Davidd
// Added back compilation switches to avoid build error. Make sure to
// enable Memory Error Type 18 support when building the SMBIOS binary.
//
// 10    7/27/05 1:05p Davidd
// Removed all conditional compilation switches. Use the value from the
// SmbiosBoardProtocol.
//
// 9     7/22/05 1:17p Davidd
// Changed code to dynamically update structures just before boot.
//
// 8     7/20/05 12:40p Davidd
// - Corrected dynamic update on-board device problem.
//
// 7     7/20/05 11:38a Davidd
// - Corrected dynamic update on-board device problem.
// - Set structure 20 to inactive if memory slot is not filled.
//
// 6     7/18/05 4:54p Davidd
// - Made changes to update the CPU data according to the number of CPU
// returned from the porting hook.
// - Added code to make calls to porting hooks (protocol) to create
// dynamic data.
//
// 5     7/15/05 6:13p Davidd
// Fixed bug updating on-board device status dynamically.
//
// 4     7/13/05 5:16p Davidd
// Code added to dynamically update Processor  Manufacturer and Processor
// Version.
//
// 3     6/21/05 11:56a Davidd
// Corrected hanging problem as BIOS Version was changed starting from
// label "ALPHA-1.00.12".
//
// 2     5/31/05 11:36a Davidd
// - Corrected intermitten hanging problem after SMBIOS driver is loaded.
// - Added/corrected dynamic memory structure updation.
//
// 1     4/29/05 2:03p Davidd
// Initial checkin.
//
//**********************************************************************//

#include <AmiDxeLib.h>
#include <Token.h>
#include <AmiHobs.h>
#include <Sb.h>
#include <SBCspLib.h>
#include "Protocol\SMBios.h"
#include "Protocol\SmbiosDynamicData.h"
#if (PI_SPECIFICATION_VERSION < 0x00010000)
#include <Protocol\FirmwareVolume.h>
#else
#include <Protocol\FirmwareVolume2.h>
#endif

#if ( defined(CSM_SUPPORT) && (CSM_SUPPORT != 0) )
#include <Protocol\LegacyBios.h>
#include <Protocol\LegacyBiosExt.h>
#if PI_SPECIFICATION_VERSION < 0x10014
EFI_LEGACY_REGION_PROTOCOL          *LegacyRegionProtocol = NULL;
#else
#include <Protocol\LegacyRegion2.h>
EFI_LEGACY_REGION2_PROTOCOL         *LegacyRegionProtocol = NULL;
#endif
EFI_LEGACY_BIOS_PROTOCOL	        *LegacyBiosProtocol = NULL;
LEGACY16_TO_EFI_DATA_TABLE_STRUC    *Legacy16Data;
EFI_STATUS Install16bitPnPSmbiosFunctions();
#endif										// CSM_SUPPORT

#if (defined(SmbiosDMIEdit_SUPPORT) && (SmbiosDMIEdit_SUPPORT !=0))
#include "SmbiosDMIEditSupport\SmbiosDMIEdit.h"
#if !defined(SMBIOS_DMIEDIT_DATA_LOC) || SMBIOS_DMIEDIT_DATA_LOC != 2
#include "Protocol\SmbiosGetFlashDataProtocol.h"
#endif										// SMBIOS_DMIEDIT_DATA_LOC
#endif										// SmbiosDMIEdit_SUPPORT

EFI_GUID gEfiSmbiosNvramGuid = EFI_SMBIOS_NVRAM_DATA_GUID;

#if defined iAMT_SUPPORT && iAMT_SUPPORT == 1
#define AMT_SMBIOS_GROUP \
    { 0xed27920d, 0x4422, 0x4b4d, { 0xa4, 0xa3, 0x4d, 0xc2, 0xb3, 0xe5, 0x46, 0x3b } }
#endif										// iAMT_SUPPORT

// Added for TPM
#define SMBIOS_EFI_TABLE_GROUP \
    { 0xb3dae700, 0x2a77, 0x4ea4, 0xaf, 0x79, 0x32, 0x97, 0xb4, 0x84, 0xbe, 0x61 }

extern EFI_BOOT_SERVICES	*pBS;
extern VOID	OemRuntimeShadowRamWrite(IN BOOLEAN Enable);

#if (PI_SPECIFICATION_VERSION < 0x00010000)
EFI_GUID  gEfiFVProtocolGuid = EFI_FIRMWARE_VOLUME_PROTOCOL_GUID;
#else
EFI_GUID  gEfiFVProtocolGuid = EFI_FIRMWARE_VOLUME2_PROTOCOL_GUID;
#endif                                      // PI_SPECIFICATION_VERSION
EFI_GUID  gEfiSmbiosStaticData = EFI_SMBIOS_STATIC_DATA_GUID;
EFI_GUID  gEfiSmbiosDynamicData = EFI_SMBIOS_DYNAMIC_DATA_GUID;
EFI_GUID  gEfiSmbiosBoardProtocolGuid = EFI_SMBIOS_BOARD_PROTOCOL_GUID;
EFI_GUID  gEfiSmbiosProtocolGuid = EFI_SMBIOS_PROTOCOL_GUID;

#if defined iAMT_SUPPORT && iAMT_SUPPORT == 1
VOID AmtNotifyEventFunction(IN EFI_EVENT Event, IN VOID *Context) {}
#endif										// iAMT_SUPPORT

// Added for TPM
VOID NotifyEventFunction(IN EFI_EVENT Event, IN VOID *Context) {}

UINT8       MemType = 0;              // 0 = Not supported
                                      // 1 = DDR2
                                      // 2 = DDR3
BOOLEAN     SmbiosTableAtE000 = FALSE;

SMBIOS_NVRAM_TYPE4      NvramType4;

#ifdef FLASH_PART_STRING_LENGTH
VOID GetFlashPartInfomation(UINT8 *pBlockAddress, UINT8 *Buffer);
#endif										// FLASH_PART_STRING_LENGTH

BOOLEAN
ValidateStringNumber(
    IN UINT8    *StructurePtr,
    IN UINT8    StructureType,
    IN UINTN    StringNumber
);

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

#if (TYPE2_STRUCTURE == 1)
STRING_TABLE    StringType_2[] =   {{0x04, 1, 1},
                                    {0x05, 2, 2},
                                    {0x06, 3, 3},
                                    {0x07, 4, 4},
                                    {0x08, 5, 5},
                                    {0x0a, 6, 6},
                                    {0xff, 0, 0},
                                   };
#else
STRING_TABLE    StringType_2[] =   {{0xff, 0, 0}};
#endif													// TYPE2_STRUCTURE

#if (TYPE3_STRUCTURE == 1)
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
#endif													// NUMBER_OF_SYSTEM_CHASSIS
#if NUMBER_OF_SYSTEM_CHASSIS > 2
                                   {
                                    {0x04, 1, 1},
                                    {0x06, 2, 2},
                                    {0x07, 3, 3},
                                    {0x08, 4, 4},
                                    {0x15 + (ELEMENT_COUNT_3 * ELEMENT_LEN_3), 5, 5},
                                    {0xff, 0, 0},
                                   },
#endif													// NUMBER_OF_SYSTEM_CHASSIS
#if NUMBER_OF_SYSTEM_CHASSIS > 3
                                   {
                                    {0x04, 1, 1},
                                    {0x06, 2, 2},
                                    {0x07, 3, 3},
                                    {0x08, 4, 4},
                                    {0x15 + (ELEMENT_COUNT_4 * ELEMENT_LEN_4), 5, 5},
                                    {0xff, 0, 0},
                                   },
#endif													// NUMBER_OF_SYSTEM_CHASSIS
#if NUMBER_OF_SYSTEM_CHASSIS > 4
                                   {
                                    {0x04, 1, 1},
                                    {0x06, 2, 2},
                                    {0x07, 3, 3},
                                    {0x08, 4, 4},
                                    {0x15 + (ELEMENT_COUNT_5 * ELEMENT_LEN_5), 5, 5},
                                    {0xff, 0, 0},
                                   },
#endif													// NUMBER_OF_SYSTEM_CHASSIS
                                  };                    // StringType_3
#else
STRING_TABLE    StringType_3[] =   {{0xff, 0, 0}};
#endif                                                  // TYPE3_STRUCTURE

STRING_TABLE    StringType_4[] =   {{0x04, 1, 1},
                                    {0x07, 2, 2},
                                    {0x10, 3, 3},
                                    {0x20, 4, 4},
                                    {0x21, 5, 5},
                                    {0x22, 6, 6},
                                    {0xff, 0, 0},
                                   };

STRING_TABLE    StringType_5[] =   {{0xff, 0, 0}};

STRING_TABLE    StringType_6[] =   {{0x04, 1, 1},
                                    {0xff, 0, 0},
                                   };

STRING_TABLE    StringType_7[] =   {{0x04, 1, 1},
                                    {0xff, 0, 0},
                                   };

STRING_TABLE    StringType_8[] =   {{0x04, 1, 1},
                                    {0x06, 2, 2},
                                    {0xff, 0, 0},
                                   };

STRING_TABLE    StringType_9[] =   {{0x04, 1, 1},
                                    {0xff, 0, 0},
                                   };

STRING_TABLE    StringType_10[] =  {{0xff, 0, 0}};

STRING_TABLE    StringType_11[] =  {{0xff, 0, 0}};

STRING_TABLE    StringType_12[] =  {{0xff, 0, 0}};

STRING_TABLE    StringType_13[] =  {{0x15, 1, 1},
                                    {0xff, 0, 0},
                                   };

STRING_TABLE    StringType_14[] =  {{0x04, 1, 1},
                                    {0xff, 0, 0},
                                   };

STRING_TABLE    StringType_15[] =  {{0xff, 0, 0}};

STRING_TABLE    StringType_16[] =  {{0xff, 0, 0}};

STRING_TABLE    StringType_17[] =  {{0x10, 1, 1},
                                    {0x11, 2, 2},
                                    {0x17, 3, 3},
                                    {0x18, 4, 4},
                                    {0x19, 5, 5},
                                    {0x1a, 6, 6},
                                    {0xff, 0, 0},
                                   };

STRING_TABLE    StringType_18[] =  {{0xff, 0, 0}};

STRING_TABLE    StringType_19[] =  {{0xff, 0, 0}};

STRING_TABLE    StringType_20[] =  {{0xff, 0, 0}};

STRING_TABLE    StringType_21[] =  {{0xff, 0, 0}};

STRING_TABLE    StringType_22[] =  {{0x04, 1, 1},
                                    {0x05, 2, 2},
                                    {0x06, 3, 3},
                                    {0x07, 4, 4},
                                    {0x08, 5, 5},
                                    {0x0e, 6, 6},
                                    {0x14, 7, 7},
                                    {0xff, 0, 0},
                                   };

STRING_TABLE    StringType_23[] =  {{0xff, 0, 0}};

STRING_TABLE    StringType_24[] =  {{0xff, 0, 0}};

STRING_TABLE    StringType_25[] =  {{0xff, 0, 0}};

STRING_TABLE    StringType_26[] =  {{0x04, 1, 1},
                                    {0xff, 0, 0},
                                   };

STRING_TABLE    StringType_27[] =  {{0x0e, 1, 1},
                                    {0xff, 0, 0},
                                   };

STRING_TABLE    StringType_28[] =  {{0x04, 1, 1},
                                    {0xff, 0, 0},
                                   };

STRING_TABLE    StringType_29[] =  {{0x04, 1, 1},
                                    {0xff, 0, 0},
                                   };

STRING_TABLE    StringType_30[] =  {{0x04, 1, 1},
                                    {0xff, 0, 0},
                                   };

STRING_TABLE    StringType_31[] =  {{0xff, 0, 0}};

STRING_TABLE    StringType_32[] =  {{0xff, 0, 0}};

STRING_TABLE    StringType_33[] =  {{0xff, 0, 0}};

STRING_TABLE    StringType_34[] =  {{0x04, 1, 1},
                                    {0xff, 0, 0},
                                   };

STRING_TABLE    StringType_35[] =  {{0x04, 1, 1},
                                    {0xff, 0, 0},
                                   };

STRING_TABLE    StringType_36[] =  {{0xff, 0, 0}};

STRING_TABLE    StringType_37[] =  {{0xff, 0, 0}};

STRING_TABLE    StringType_38[] =  {{0xff, 0, 0}};

STRING_TABLE    StringType_39[] =  {{0x05, 1, 1},
                                    {0x06, 2, 2},
                                    {0x07, 3, 3},
                                    {0x08, 4, 4},
                                    {0x09, 5, 5},
                                    {0x0a, 6, 6},
                                    {0x0b, 7, 7},
                                    {0xff, 0, 0},
                                   };

STRING_TABLE    StringType_40[] =  {{0xff, 0, 0}};

STRING_TABLE    StringType_41[] =  {{0x04, 1, 1},
                                    {0xff, 0, 0},
                                   };

STRING_TABLE    StringType_42[] =  {{0xff, 0, 0}};

//
// String table
//
VOID*    StringTable[] = {&StringType_0,        // 0
                          &StringType_1,        // 1
                          &StringType_2,        // 2
                          &StringType_3,        // 3
                          &StringType_4,        // 4
                          &StringType_5,        // 5
                          &StringType_6,        // 6
                          &StringType_7,        // 7
                          &StringType_8,        // 8
                          &StringType_9,        // 9
                          &StringType_10,       // 10
                          &StringType_11,       // 11
                          &StringType_12,       // 12
                          &StringType_13,       // 13
                          &StringType_14,       // 14
                          &StringType_15,       // 15
                          &StringType_16,       // 16
                          &StringType_17,       // 17
                          &StringType_18,       // 18
                          &StringType_19,       // 19
                          &StringType_20,       // 20
                          &StringType_21,       // 21
                          &StringType_22,       // 22
                          &StringType_23,       // 23
                          &StringType_24,       // 24
                          &StringType_25,       // 25
                          &StringType_26,       // 26
                          &StringType_27,       // 27
                          &StringType_28,       // 28
                          &StringType_29,       // 29
                          &StringType_30,       // 30
                          &StringType_31,       // 31
                          &StringType_32,       // 32
                          &StringType_33,       // 33
                          &StringType_34,       // 34
                          &StringType_35,       // 35
                          &StringType_36,       // 36
                          &StringType_37,       // 37
                          &StringType_38,       // 38
                          &StringType_39,       // 39
                          &StringType_40,       // 40
                          &StringType_41,       // 41
                          &StringType_42,       // 42
                         };

JEDEC_MF_ID Bank0Table [] = {{ 0x01, "AMD" },
                             { 0x04, "Fujitsu" },
                             { 0x07, "Hitachi" },
                             { 0x89, "Intel" },
                             { 0x10, "NEC" },
                             { 0x97, "Texas Instrument" },
                             { 0x98, "Toshiba" },
                             { 0x1c, "Mitsubishi" },
                             { 0x1f, "Atmel" },
                             { 0x20, "STMicroelectronics" },
                             { 0xa4, "IBM" },
                             { 0x2c, "Micron Technology" },
                             { 0xad, "SK Hynix" },
                             { 0xb0, "Sharp" },
                             { 0xb3, "IDT" },
                             { 0x3e, "Oracle" },
                             { 0xbf, "SST" },
                             { 0x40, "ProMos/Mosel" },
                             { 0xc1, "Infineon" },
                             { 0xc2, "Macronix" },
                             { 0x45, "SanDisk" },
                             { 0xce, "Samsung" },
                             { 0xda, "Winbond" },
                             { 0xe0, "LG Semi" },
                             { 0x62, "Sanyo" },
                             { 0xff, "Undefined" }
};
JEDEC_MF_ID Bank1Table [] = {{ 0x98, "Kingston" },
                             { 0xba, "PNY" },
                             { 0x4f, "Transcend" },
                             { 0x7a, "Apacer" },
                             { 0xff, "Undefined" }
};
JEDEC_MF_ID Bank2Table [] = {{ 0x9e, "Corsair" },
                             { 0xfe, "Elpida" },
                             { 0xff, "Undefined" }
};
JEDEC_MF_ID Bank3Table [] = {{ 0x0b, "Nanya" },
                             { 0x94, "Mushkin" },
                             { 0x25, "Kingmax" },
                             { 0xff, "Undefined" }
};
JEDEC_MF_ID Bank4Table [] = {{ 0xb0, "OCZ" },
                             { 0xcb, "A-DATA" },
                             { 0xcd, "G Skill" },
                             { 0xef, "Team" },
                             { 0xff, "Undefined" }
};
JEDEC_MF_ID Bank5Table [] = {{ 0x02, "Patriot" },
                             { 0x9b, "Crucial" },
                             { 0x51, "Qimonda" },
                             { 0x57, "AENEON" },
                             { 0xf7, "Avant" },
                             { 0xff, "Undefined" }
};
JEDEC_MF_ID Bank6Table [] = {{ 0x34, "Super Talent" },
                             { 0xd3, "Silicon Power" },
                             { 0xff, "Undefined" }
};
JEDEC_MF_ID Bank7Table [] = {{ 0xff, "Undefined" }
};


JEDEC_MF_ID *ManufacturerJedecIdBankTable [] = {
                                                Bank0Table,
                                                Bank1Table,
                                                Bank2Table,
                                                Bank3Table,
                                                Bank4Table,
                                                Bank5Table,
                                                Bank6Table,
                                                Bank7Table
};

JEDEC_DATA	ManufacturerTable[] = MANUFACTURER_ID_CODE;

SMBIOS_TABLE_ENTRY_POINT	SmbiosEntryPointTable = {
			'_', 'S', 'M', '_',
			0,												// EPS Checksum
			0x1f,											// Entry Point Length
			0x02,											// SMBIOS Major Version
			0x08,											// SMBIOS Minor Version
			0x100,										    // Maximum Structure Size
			0,												// Entry Point Revision
			0, 0, 0, 0, 0,						            // Formatted Area
			'_', 'D', 'M', 'I', '_',	                    // Intermediate Anchor String
			0,												// Intermediate Checksum
			0,												// Structure Table Length
			0,												// Structure Table Address
			0x10,											// Number of SMBIOS Stuctures
			0x28                                            // SMBIOS BCD Revision};
            };

SMBIOS_TABLE_ENTRY_POINT    	*pSmbiosTableEntryPoint = &SmbiosEntryPointTable;
UINT8                       	*ScratchBufferPtr = NULL;
UINT8                       	*SmbiosDataTable = NULL;
UINT16                      	MaximumTableSize;
UINT16                      	LastHandle;
EFI_SMBIOS_BOARD_PROTOCOL   	*gSmbiosBoardProtocol;
BOOLEAN                         UpdateCpuStructure;
BOOLEAN							TableRelocated = FALSE;

EFI_SMBIOS_PROTOCOL   SmbiosProtocol = {
#if ( defined(SMBIOS_PI_1_1) && (SMBIOS_PI_1_1 == 1) )
                                        SmbiosPiAddStructure,
                                        SmbiosPiUpdateString,
                                        SmbiosPiRemoveStructure,
                                        SmbiosPiGetNextStructure,
                                        SMBIOS_MAJOR_VERSION,
                                        SMBIOS_MINOR_VERSION,
#endif
                                        GetSmbiosTableEntryPoint,
                                        GetScratchBufferPtr,
                                        GetBufferMaxSize,
                                        GetFreeHandle,
                                        AddStructure,
                                        AddStructureByHandle,
                                        DeleteStructureByHandle,
                                        ReadStructureByHandle,
                                        ReadStructureByType,
                                        WriteStructureByHandle,
                                        UpdateSmbiosTableHeader};

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   SmbiosPiUpdateString
//
// Description: Update the string associated with an existing SMBIOS record
//
// Input:       IN CONST EFI_SMBIOS_PROTOCOL    *This,
//              IN EFI_SMBIOS_HANDLE            *SmbiosHandle,
//              IN UINTN                        *StringNumber,
//              IN CHAR8                        *String
//
// Output:
//
// Modified:
//
// Referrals:
//
// Notes:
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS
SmbiosPiUpdateString (
    IN CONST EFI_SMBIOS_PROTOCOL    *This,
    IN EFI_SMBIOS_HANDLE            *SmbiosHandle,
    IN UINTN                        *StringNumber,
    IN CHAR8                        *String
)
{
    EFI_STATUS      Status = EFI_SUCCESS;
    UINT8           *StrucPtr = SmbiosDataTable;
    UINT8           *BufferPtr;
    UINT16          BufferSize;

    TRACE((-1, "In SmbiosPiUpdateString\n"));

    if (*StringNumber) {
        if (FindStructureHandle(&StrucPtr, *SmbiosHandle)) {
            TRACE((-1, "Found structure with handle = %x\n", *SmbiosHandle));
            if (ValidateStringNumber(StrucPtr, ((SMBIOS_STRUCTURE_HEADER*)StrucPtr)->Type, *StringNumber)) {
                BufferSize = GetStructureLength(StrucPtr);

                Status = pBS->AllocatePool(EfiBootServicesData,
                                        BufferSize + (UINT16)Strlen(String) + 1,
                                        (void**)&BufferPtr);
                if (EFI_ERROR(Status)) {
                    TRACE((-1, "Memory allocation failed. Exit\n"));
                    return EFI_UNSUPPORTED;
                }

                MemCpy(BufferPtr, StrucPtr, BufferSize);

                if (ReplaceString(BufferPtr, *(UINT8*)StringNumber, (UINT8*)String)) {
                    TRACE((-1, "Failed to replace string\n"));
                    Status = EFI_UNSUPPORTED;
                }
                else {
                    TRACE((-1, "Deleting structure with handle = %x\n", *SmbiosHandle));
                    if (DeleteStructureByHandle(*SmbiosHandle)) {
                        TRACE((-1, "Failed to delete structure\n"));
                        Status = EFI_INVALID_PARAMETER;
                    }

                    BufferSize = GetStructureLength(BufferPtr);

                    TRACE((-1, "Adding structure with handle = %x\n", *SmbiosHandle));
                    if (AddStructureByHandle(*SmbiosHandle, BufferPtr, BufferSize)) {
                        TRACE((-1, "Failed to add structure\n"));
                        Status = EFI_ALREADY_STARTED;
                    }
                }

                pBS->FreePool(BufferPtr);

                UpdateSmbiosTableHeader();

                Status = EFI_SUCCESS;
            }
            else {
                TRACE((-1, "StringNumber validation failed!\n"));
                Status = EFI_NOT_FOUND;
            }
        }
        else {
            TRACE((-1, "Structure not found!\n"));
            Status = EFI_INVALID_PARAMETER;
        }
    }
    else {
        TRACE((-1, "String number missing!\n"));
        Status = EFI_NOT_FOUND;
    }

    TRACE((-1, "Exiting SmbiosPiUpdateString. Status = %r\n", Status));
    return Status;
}

#if ( defined(SMBIOS_PI_1_1) && (SMBIOS_PI_1_1 == 1) )

BOOLEAN
FindStructureType(
    IN OUT UINT8    **Buffer,
    IN OUT UINT8    **StructureFoundPtr,
	IN     UINT8    SearchType,
    IN     UINT8    Instance        // 1-based
);

EFI_PRODUCER_HANDLE  ProducerHandleTable[PRODUCER_HANDLE_ELEMENTS];

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   AddProducerHandle
//
// Description: Add/Register the ProducerHandle associated with SmbiosHandle
//              to the ProducerHandleTable
//
// Input:       IN EFI_SMBIOS_HANDLE    SmbiosHandle
//              IN EFI_HANDLE           ProducerHandle
//
// Output:
//
// Modified:
//
// Referrals:
//
// Notes:
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID
AddProducerHandle (
    IN EFI_SMBIOS_HANDLE    SmbiosHandle,
    IN EFI_HANDLE           ProducerHandle
)
{
    EFI_PRODUCER_HANDLE     *ProducerPtr = &ProducerHandleTable[0];
    UINT16                  i = 0;

    while ((ProducerPtr->SmbiosHandle != 0xffff) &&
            (ProducerPtr->SmbiosHandle != SmbiosHandle) &&
            (i < PRODUCER_HANDLE_ELEMENTS)) {
        ProducerPtr++;
        i++;
    }

    if (i < PRODUCER_HANDLE_ELEMENTS) {
        ProducerPtr->SmbiosHandle = SmbiosHandle;
        ProducerPtr->ProducerHandle = ProducerHandle;
    }
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   InitializeProducerHandleTable
//
// Description: Initialize the ProducerHandleTable
//
// Input:       IN EFI_HANDLE   ProducerHandle
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
InitializeProducerHandleTable (
    IN EFI_HANDLE  ProducerHandle
)
{
    EFI_PRODUCER_HANDLE     *ProdPtr = &ProducerHandleTable[0];
    UINT16                  i;
    UINT8                   *Ptr = SmbiosDataTable;

    for (i = 0; i < PRODUCER_HANDLE_ELEMENTS; i++) {
        ProdPtr->SmbiosHandle = 0xffff;
        ProdPtr->ProducerHandle = 0;
        ProdPtr++;
    };

    // Set ProducerHandle for each Smbios record
    do {
        AddProducerHandle(((EFI_SMBIOS_TABLE_HEADER*)Ptr)->Handle, ProducerHandle);
        Ptr += GetStructureLength(Ptr);
    } while (((EFI_SMBIOS_TABLE_HEADER*)Ptr)->Type != 127);

    AddProducerHandle(((EFI_SMBIOS_TABLE_HEADER*)Ptr)->Handle, ProducerHandle);
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   RemoveProducerHandle
//
// Description: Remove the "SmbiosHandle" entry from the ProducerHandleTable
//
// Input:       IN EFI_SMBIOS_HANDLE    SmbiosHandle
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
RemoveProducerHandle (
    IN EFI_SMBIOS_HANDLE    SmbiosHandle
)
{
    UINT16                  i = 0;
    EFI_PRODUCER_HANDLE     *ProducerPtr = &ProducerHandleTable[0];
    UINT16                  Size;

    if (SmbiosHandle != 127) {
        while ((ProducerPtr->SmbiosHandle != 127) && (ProducerPtr->SmbiosHandle != SmbiosHandle)) {
            i++;
            ProducerPtr++;
        }

        if (ProducerPtr->SmbiosHandle == SmbiosHandle) {
            EFI_PRODUCER_HANDLE     *TempPtr;

            TempPtr = ProducerPtr + 1;
            Size = (PRODUCER_HANDLE_ELEMENTS - i - 1) * sizeof(EFI_PRODUCER_HANDLE);
            MemCpy((UINT8*)ProducerPtr, (UINT8*)TempPtr, Size);
        }
    }
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   GetProducerHandle
//
// Description:
//
// Input:       IN EFI_SMBIOS_HANDLE    SmbiosHandle
//              IN OUT EFI_HANDLE       *ProducerHandle
//
// Output:      ProducerHandle
//
// Modified:
//
// Referrals:
//
// Notes:
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID
GetProducerHandle (
    IN EFI_SMBIOS_HANDLE    SmbiosHandle,
    IN OUT EFI_HANDLE       *ProducerHandle
)
{
    EFI_PRODUCER_HANDLE     *ProducerPtr = &ProducerHandleTable[0];

    if (SmbiosHandle != 127) {
        while ((ProducerPtr->SmbiosHandle != 127) && (ProducerPtr->SmbiosHandle != SmbiosHandle)) {
            ProducerPtr++;
        }

        *ProducerHandle = ProducerPtr->ProducerHandle;
    }
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   SmbiosPiAddStructure
//
// Description: Add an Smbios record
//
// Input:       IN CONST EFI_SMBIOS_PROTOCOL    *This,
//              IN EFI_HANDLE                   ProducerHandle, OPTIONAL
//              IN OUT EFI_SMBIOS_HANDLE        *SmbiosHandle,
//              IN EFI_SMBIOS_TABLE_HEADER      *Record
//
// Output:      SmbiosHandle
//
// Modified:
//
// Referrals:
//
// Notes:
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS
SmbiosPiAddStructure (
    IN CONST EFI_SMBIOS_PROTOCOL    *This,
    IN EFI_HANDLE                   ProducerHandle, OPTIONAL
    IN OUT EFI_SMBIOS_HANDLE        *SmbiosHandle,
    IN EFI_SMBIOS_TABLE_HEADER      *Record
)
{
    EFI_STATUS      Status = EFI_SUCCESS;
    UINT16          RecordSize;

    RecordSize = GetStructureLength((UINT8*)Record);

    if (*SmbiosHandle) {
        if (AddStructureByHandle(*SmbiosHandle, (UINT8*)Record, RecordSize)) {
            Status = EFI_ALREADY_STARTED;
        }
        else {
            AddProducerHandle(*SmbiosHandle, ProducerHandle);
        }
    }
    else {
        if (AddStructure((UINT8*)Record, RecordSize)) {
            Status = EFI_OUT_OF_RESOURCES;
        }
        else {
            *SmbiosHandle = Record->Handle;
            AddProducerHandle(*SmbiosHandle, ProducerHandle);
        }
    }

    if (Status == EFI_SUCCESS) {
        UpdateSmbiosTableHeader();
    }

    return Status;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   SmbiosPiRemoveStructure
//
// Description: Remove an SMBIOS record
//
// Input:       IN CONST EFI_SMBIOS_PROTOCOL    *This,
//              IN EFI_SMBIOS_HANDLE            SmbiosHandle
//
// Output:
//
// Modified:
//
// Referrals:
//
// Notes:
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS
SmbiosPiRemoveStructure (
    IN CONST EFI_SMBIOS_PROTOCOL    *This,
    IN UINTN                        SmbiosHandle
)
{
    if (DeleteStructureByHandle((UINT16)SmbiosHandle)) {
        return EFI_INVALID_PARAMETER;
    }

    RemoveProducerHandle((EFI_SMBIOS_HANDLE)SmbiosHandle);

    UpdateSmbiosTableHeader();

    return EFI_SUCCESS;
};

#if defined PI_SPECIFICATION_VERSION && PI_SPECIFICATION_VERSION >= 0x10014
#define ANY_HANDLE   0xfffe
#else
#define ANY_HANDLE   0
#endif

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   SmbiosPiGetNextStructure
//
// Description: Allow the caller to discover all or some of the SMBIOS records
//
// Input:       IN  CONST EFI_SMBIOS_PROTOCOL   *This,
//              IN  OUT EFI_SMBIOS_HANDLE       *SmbiosHandle
//              IN  EFI_SMBIOS_TYPE             *Type, OPTIONAL
//              OUT EFI_SMBIOS_TABLE_HEADER     **Record,
//              OUT EFI_HANDLE                  *ProducerHandle OPTIONAL
//
// Output:
//
// Modified:
//
// Referrals:
//
// Notes:
//  Implementation:
//  SmbiosHandle = 0xfffe,  Type = NULL ==> Record = 1st record in table,
//                                          SmbiosHandle = handle of record being returned
//  SmbiosHandle != 0xfffe, Type = NULL ==> If record of SmbiosHandle is not found, return EFI_NOT_FOUND, SmbiosHandle = 0xfffe
//                                          else Record = next record after record of SmbiosHandle,
//                                               SmbiosHandle = handle of record being returned
//  SmbiosHandle = 0xfffe,  Type <> 0   ==> If record of input "Type" is not found, return EFI_NOT_FOUND, SmbiosHandle = 0xfffe
//                                          else Record = 1st record of type "*Type",
//                                               SmbiosHandle = handle of record being returned
//  SmbiosHandle != 0xfffe, Type <> 0   ==> If record of SmbiosHandle is not found, or found but no record of type "*Type" after
//                                               record of SmbiosHandle can be found, return EFI_NOT_FOUND, SmbiosHandle = 0xfffe
//                                          else Record = next record after record of SmbiosHandle,
//                                               SmbiosHandle = handle of record being returned
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS
SmbiosPiGetNextStructure (
    IN CONST EFI_SMBIOS_PROTOCOL    *This,
    IN OUT EFI_SMBIOS_HANDLE        *SmbiosHandle,
    IN EFI_SMBIOS_TYPE              *Type OPTIONAL,
    OUT EFI_SMBIOS_TABLE_HEADER     **Record,
    OUT EFI_HANDLE                  *ProducerHandle OPTIONAL
)
{
    EFI_STATUS      Status = EFI_SUCCESS;
    UINT8           *StrucPtr;
    UINT8           *StructureFoundPtr;
    UINT16          StrucSize;

    TRACE((-1, "In SmbiosPiGetNextStructure\n"));

    StrucPtr = SmbiosDataTable;

    if (Type == NULL) {
        if (*SmbiosHandle == 0xfffe) {
            // Type = NULL, *SmbiosHandle = 0xfffe ==> return 1st record in Smbios table
            Status = EFI_SUCCESS;
            goto GetNext_Exit;
        }
        else {
            // Type = NULL, *SmbiosHandle != 0xfffe
            if (FindStructureHandle(&StrucPtr, *SmbiosHandle)) {
                if (((EFI_SMBIOS_TABLE_HEADER*)StrucPtr)->Type != 127) {
                    // Record of *SmbiosHandle is found, return next record
                    StrucSize = GetStructureLength(StrucPtr);
                    StrucPtr += StrucSize;
                    Status = EFI_SUCCESS;
                }
                else {
                    // End of Smbios table, return error
                    Status = EFI_NOT_FOUND;
                }
            }
            else {
                // Record of *SmbiosHandle is not found, return error
                Status = EFI_NOT_FOUND;
            }

            goto GetNext_Exit;
        }
    }
    else {                                      // Type != NULL
        if (*SmbiosHandle == 0xfffe) {
            // Search for 1st record of *Type
            if (FindStructureType(&StrucPtr, &StructureFoundPtr, *Type, 1)) {
                // Type != NULL, *SmbiosHandle = 0xfffe
                // Record of *Type is found ===> return record found
                StrucPtr = StructureFoundPtr;
                Status = EFI_SUCCESS;
            }
            else {
                // Type != NULL, *SmbiosHandle = 0xfffe
                // Record of *Type is not found, return error
                Status = EFI_NOT_FOUND;
            }

            goto GetNext_Exit;
        }
        else {                                  // Type != NULL, *SmbiosHandle != 0xfffe
            if (FindStructureHandle(&StrucPtr, *SmbiosHandle)) {
                if (((EFI_SMBIOS_TABLE_HEADER*)StrucPtr)->Type != 127) {
                    // Record of SmbiosHandle is found, skip to next record
                    StrucSize = GetStructureLength(StrucPtr);
                    StrucPtr += StrucSize;
                    if (FindStructureType(&StrucPtr, &StructureFoundPtr, *Type, 1)) {
                        // Type != NULL, *SmbiosHandle != 0xfffe
                        // Record of *Type is found ===> return record found
                        StrucPtr = StructureFoundPtr;
                        Status = EFI_SUCCESS;
                    }
                    else {
                        // Type != NULL, *SmbiosHandle != 0xfffe,
                        // Record of SmbiosHandle is found but record of *Type is not found, return error
                        Status = EFI_NOT_FOUND;
                    }
                }
                else {
                    // End of Smbios table, return error
                    Status = EFI_NOT_FOUND;
                }
            }
            else {
                // Type != NULL, *SmbiosHandle != 0xfffe,
                // Record of SmbiosHandle is not found, return error
                Status = EFI_NOT_FOUND;
            }
        }
    }

GetNext_Exit:
    if (Status == EFI_SUCCESS) {
        *SmbiosHandle = ((EFI_SMBIOS_TABLE_HEADER*)StrucPtr)->Handle;
        *Record = (EFI_SMBIOS_TABLE_HEADER*)StrucPtr;

        if (ProducerHandle != NULL) {
            GetProducerHandle(*SmbiosHandle, ProducerHandle);
        }
    }
    else {
        *SmbiosHandle = 0xfffe;
    }

    TRACE((-1, "Exit SmbiosPiGetNextStructure. Status = %r\n", Status));
    return Status;
}
#endif

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   SmbiosCheckSum
//
// Description: Returns the checksum of "length" bytes starting from the
//              "*ChecksumSrc"
//
// Input:       IN UINT8 *ChecksumSrc
//              IN UINT8 length
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
    UINT8       Checksum = 0;
    UINT8       i;

    for (i = 0; i < length; i++) {
        Checksum += *ChecksumSrc++;
    }
    return (0 - Checksum);
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   GetStructureLength
//
// Description: Returns the length of the structure pointed by BufferStart
//              in bytes
//
// Input:       IN UINT8 *BufferStart
//
// Output:      UINT16 - Structure Size
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
    IN UINT8    *BufferStart
)
{
    UINT8       *BufferEnd = BufferStart;

    BufferEnd += ((SMBIOS_STRUCTURE_HEADER*)BufferStart)->Length;

    while (*(UINT16*)BufferEnd != 0) {
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
    UINT8   *Table = SmbiosDataTable;
    UINT8   Instance = 0;		// 1-based

    while(((SMBIOS_STRUCTURE_HEADER*)Table)->Type != 127) {
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
    if ((FindStatus == FALSE) && (SearchType == 127)) {
        FindStatus = TRUE;
        *StructureFoundPtr = BufferPtr;
        *Buffer = BufferPtr + GetStructureLength(BufferPtr);
    }
    return FindStatus;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   FindStructureHandle
//
// Description: Find structure handle starting from memory location pointed
//              by Buffer
//
// Input:       IN OUT  UINT8   **Buffer
//              IN      UINT16  Handle
//
// Output:
//              BOOLEAN
//                  TRUE -  Structure found
//                  FALSE - Structure not found
//
//              If SearchType is found:
//                UINT8   **Buffer - Points to the structure that was found
//
// Modified:
//
// Referrals:
//
// Notes:
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
BOOLEAN
FindStructureHandle(
    IN OUT UINT8    **Buffer,
    IN     UINT16   Handle
)
{
    while (((SMBIOS_STRUCTURE_HEADER*)*Buffer)->Handle != Handle) {
        if (((SMBIOS_STRUCTURE_HEADER*)*Buffer)->Type == 127) {
            return FALSE;
        }
        *Buffer += GetStructureLength(*Buffer);
    }
    return TRUE;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   UpdateType127Handle
//
// Description: Updates Structure Type 127 handle and sets global variable
//              LastHandle to the last structure handle.
//
// Input:       IN UINT8   *Buffer
//
// Output:      Sets global variable LastHandle
//
// Modified:
//
// Referrals:
//
// Notes:
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID
UpdateType127Handle(
    IN UINT8    *Buffer
)
{
    UINT8       *BufferPtr = Buffer;
    UINT16      Handle;

    while (((SMBIOS_STRUCTURE_HEADER*)BufferPtr)->Type != 127) {
        Handle = ((SMBIOS_STRUCTURE_HEADER*)BufferPtr)->Handle;
        BufferPtr += GetStructureLength(BufferPtr);
    }
    ((SMBIOS_STRUCTURE_HEADER*)BufferPtr)->Handle = ++Handle;
    LastHandle = Handle;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   GetNumberOfStructures
//
// Description: Returns the number of structures starting from Buffer til
//              (and including) type 127 structure.
//
// Input:       IN UINT8   *Buffer
//
// Output:      UINT16 - Number of structures
//
// Modified:
//
// Referrals:
//
// Notes:
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
UINT16
GetNumberOfStructures(
    IN UINT8    *Buffer
)
{
    UINT8       *BufferPtr = Buffer;
    UINT16      SmbiosStrucCount = 1;

    while (((SMBIOS_STRUCTURE_HEADER*)BufferPtr)->Type != 127) {
        ++SmbiosStrucCount;
        BufferPtr += GetStructureLength(BufferPtr);
    }
    return SmbiosStrucCount;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   GetLargestStructureSize
//
// Description: Returns the largest structure size
//
// Input:       IN UINT8   *Buffer
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
    IN UINT8    *Buffer
)
{
    UINT8       *BufferPtr = Buffer;
    UINT16      LargestStructureSize = 0;
    UINT16      CurrentStructureSize;

    while (((SMBIOS_STRUCTURE_HEADER*)BufferPtr)->Type != 127) {
        UINT8   *LastBufferPtr;

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
    IN UINT8    StructureType
)
{
    if (StructureType < 42) {
        return StringTable[StructureType];
    }
    else {
        return NULL;
    }
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   GetStrIndex
//
// Description: Return the string index, assuming all strings exist and they
//              sequentially numbered according to Smbios specification for
//              the input type structure
//
// Input:       IN  UINT8       Structure Type
//              IN  UINT8       Offset,
//              IN  UINT8       Instance        // 1- based
//
// Output:      String index (0-based)
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
GetStrIndex(
    IN  UINT8       Type,
    IN  UINT8       Offset,
    IN  UINT8       Instance        // 1- based
)
{
    UINT8           i = 0;
    STRING_TABLE    *StrTablePtr;

    StrTablePtr = GetTypeTable(Type);
    if (StrTablePtr != NULL) {
        StrTablePtr += 6 * (Instance - 1);
        while (StrTablePtr->Offset != 0xff) {
            if (StrTablePtr->Offset == Offset) {
                i = StrTablePtr->SpecStrNum - 1;    // 0-based
                break;
            }

            StrTablePtr++;
        }

        if (StrTablePtr->Offset != 0xff) {
            return i;
        }
    }

    return 0xff;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   GetStrNumber
//
// Description: Return the string number for a structure "Type" at "Offset"
//
// Input:       IN UINT8    Pointer to SmbiosTable or Structure
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
    IN  UINT8       *SmbiosTable,
    IN  UINT8       Type,
    UINT8           Offset
)
{
    UINT8       *NextStructPtr = SmbiosTable;
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

    return StrNumber;       // 1-based, 0 if no string
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
// Procedure:   GetStringOffset
//
// Description: Returns the string offset for StringNumber from BufferStart
//
// Input:       IN  UINT8   *BufferStart
//              IN  UINT8   StringNumber
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
    UINT8       *StructurePtr;
    UINT8       *StructureEnd;

    StructurePtr = *BufferPtr;
    StructureEnd = StructurePtr + GetStructureLength(StructurePtr);
    StructurePtr += ((SMBIOS_STRUCTURE_HEADER*)StructurePtr)->Length;
    StructurePtr += GetStringOffset(StructurePtr, StringNumber);
    if (StructurePtr >= StructureEnd) {
        return FALSE;
    }
    else {
        *BufferPtr = StructurePtr;
        return TRUE;
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
    IN UINT8    *StructPtr,
    IN UINT8    StrNumber
)
{
    UINT8       *TempPtr;
    UINT8       *StructEndPtr;
    UINTN       RemainingSize;

    // Delete string number
    DeleteStringNumber(StructPtr, StrNumber);

    FindString(&StructPtr, StrNumber);              // StructPtr = StrNumber string
    TempPtr = StructPtr + Strlen((char*)StructPtr) + 1;    // Move pointer to next string

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

    // Move pointer to the end of last string
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
// Description: Copy strings from NvramData to StructPtr
//
// Input:       IN      SMBIOS_NVRAM_TYPE       *NvramData,
//              IN OUT  UINT8                   *StructPtr
//				IN      UINT8					StrTableInstance    // 1-based
//
// Output:      Updated strings in StructPtr
//
// Modified:
//
// Referrals:
//
// Notes:
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID
UpdateStrings(
    IN     SMBIOS_NVRAM_TYPE    *NvramData,
    IN OUT UINT8                *StructPtr,
	IN     UINT8				StrTableInstance    // 1-based
)
{
    UINT8               TestBit;
    UINT8               i;
    UINT8               Type;
    UINT8               StrNumber;
    STRING_TABLE        *StrTablePtr;

    if (NvramData->Flag != 0) {
        // Set StringTablePtr pointer to the appropriate string table
        StrTablePtr = GetTypeTable(((SMBIOS_STRUCTURE_HEADER*)StructPtr)->Type);
		if (((SMBIOS_STRUCTURE_HEADER*)StructPtr)->Type == 3) {
			StrTablePtr += 6 * (StrTableInstance - 1);
		}

        if (StrTablePtr != NULL)  {
            CHAR8       *String;

            // Update String fields
            for (i = 0; StrTablePtr[i].Offset != 0xff; i++) {
                TestBit = (1 << i);
                if (NvramData->Flag & TestBit) {
    				// Structure string has been changed, update it
                    Type = ((SMBIOS_STRUCTURE_HEADER*)StructPtr)->Type;
                    StrNumber = GetStrNumber(StructPtr, Type, StrTablePtr[i].Offset);
                    String = NvramData->StringSet[i];
                    if (Strlen(String) != 0) {
                        if (StrNumber == 0) {
                            AddStringNumber(StructPtr, Type, StrTablePtr[i].Offset);
                            StrNumber = GetStrNumber(StructPtr, Type, StrTablePtr[i].Offset);
                        }
                        ReplaceString(StructPtr, StrNumber, String);    // StrNumber 1-based
                    }
                    else {
                        DeleteString(StructPtr, StrNumber);
                    }
                }
            }

            // Add structure terminator Null byte
            AddNullTerminator(StructPtr, StrTablePtr);
        }
    }
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   UpdateStructuresWithNvramType0
//
// Description: Copy Type 0 strings to TempBuffer. Strings will be copied
//              from NVRAM if exist, or else from existing strings in ROM image.
//              SrcBuffer and TempBuffer pointers are updated
//
// Input:       IN      SMBIOS_NVRAM_TYPE0      *NvramData,
//              IN OUT  UINT8                   *SrcBuffer
//              IN OUT  UINT8                   *TempBuffer
//
// Output:      Updated SrcBuffer and TempBuffer
//
// Modified:
//
// Referrals:
//
// Notes:
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID
UpdateStructuresWithNvramType0(
    IN     SMBIOS_NVRAM_TYPE0   *NvramData,
    IN OUT UINT8                *SrcBuffer,
    IN OUT UINT8                *TempBuffer
)
{
    UINT16      BlockSize;

    // Copy structure data from SrcBuffer
    BlockSize = GetStructureLength(SrcBuffer);
    MemCpy(TempBuffer, SrcBuffer, BlockSize);

    if (NvramData != NULL) {
        UpdateStrings((SMBIOS_NVRAM_TYPE*)NvramData, TempBuffer, 1);
    }
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   UpdateStructuresWithNvramType1
//
// Description: Copy Type 1 strings to TempBuffer. Strings will be copied
//              from NVRAM if exist, or else from existing strings in ROM image.
//              SrcBuffer and TempBuffer pointers are updated
//
// Input:       IN      SMBIOS_NVRAM_TYPE1      *NvramData,
//              IN OUT  UINT8                   *SrcBuffer
//              IN OUT  UINT8                   *TempBuffer
//
// Output:      Updated SrcBuffer and TempBuffer
//
// Modified:
//
// Referrals:
//
// Notes:
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID
UpdateStructuresWithNvramType1(
    IN     SMBIOS_NVRAM_TYPE1   *NvramData,
    IN OUT UINT8                *SrcBuffer,
    IN OUT UINT8                *TempBuffer
)
{
    UINT16              BlockSize;
    UINT16              i;
    SMBIOS_SYSTEM_INFO  *Ptr;
    UINT8               *NvramUuidPtr;

    // Copy structure data from SrcBuffer
    BlockSize = GetStructureLength(SrcBuffer);
    MemCpy(TempBuffer, SrcBuffer, BlockSize);

    if (NvramData != NULL) {
        // UUID field - Offset 8 (Test Bit16)
        if (NvramData->Flag & 0x00010000) {
            UINT8       *UuidPtr;

            Ptr = (SMBIOS_SYSTEM_INFO*)TempBuffer;
            UuidPtr = (UINT8*)&Ptr->Uuid;
            NvramUuidPtr = (UINT8*)&NvramData->Uuid;
            for (i = 0; i < sizeof(EFI_GUID); i++) {
                UuidPtr[i] = NvramUuidPtr[i];
            }
        }

        UpdateStrings((SMBIOS_NVRAM_TYPE*)NvramData, TempBuffer, 1);
    }
}

#if BASE_BOARD_INFO
//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   UpdateStructuresWithNvramType2
//
// Description: Copy Type 2 strings to TempBuffer. Strings will be copied
//              from NVRAM if exist, or else from existing strings in ROM image.
//              SrcBuffer and TempBuffer pointers are updated
//
// Input:       IN      SMBIOS_NVRAM_TYPE2      *NvramData,
//              IN OUT  UINT8                   *SrcBuffer
//              IN OUT  UINT8                   *TempBuffer
//
// Output:      Updated SrcBuffer and TempBuffer
//
// Modified:
//
// Referrals:
//
// Notes:
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID
UpdateStructuresWithNvramType2(
    IN     SMBIOS_NVRAM_TYPE2   *NvramData,
    IN OUT UINT8                *SrcBuffer,
    IN OUT UINT8                *TempBuffer
)
{
    UINT16      BlockSize;

    // Copy structure data from SrcBuffer
    BlockSize = GetStructureLength(SrcBuffer);
    MemCpy(TempBuffer, SrcBuffer, BlockSize);

    if (NvramData != NULL) {
        UpdateStrings((SMBIOS_NVRAM_TYPE*)NvramData, TempBuffer, 1);
    }
}
#endif

#if SYS_CHASSIS_INFO
//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   UpdateStructuresWithNvramType3
//
// Description: Copy Type 3 strings to TempBuffer. Strings will be copied
//              from NVRAM if exist, or else from existing strings in ROM image.
//              SrcBuffer and TempBuffer pointers are updated
//
// Input:       IN      SMBIOS_NVRAM_TYPE3      *NvramData,
//              IN OUT  UINT8                   *SrcBuffer
//              IN OUT  UINT8                   *TempBuffer
//              IN      UINT8                   StringTableInstance
//
// Output:      Updated SrcBuffer and TempBuffer
//
// Modified:
//
// Referrals:
//
// Notes:
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID
UpdateStructuresWithNvramType3(
    IN     SMBIOS_NVRAM_TYPE3   *NvramData,
    IN OUT UINT8                *SrcBuffer,
    IN OUT UINT8                *TempBuffer,
	IN     UINT8                StrTableInstance    // 1-based
)
{
    UINT16      BlockSize;

    // Copy structure data from SrcBuffer
    BlockSize = GetStructureLength(SrcBuffer);
    MemCpy(TempBuffer, SrcBuffer, BlockSize);

    if (NvramData != NULL) {
        // Type field - Offset 5 (Test Bit16)
        if (NvramData->Flag & 0x00010000) {
            ((SMBIOS_SYSTEM_ENCLOSURE_INFO*)TempBuffer)->Type = NvramData->Type;
        }

        // OEM-Defined field - Offset 0x0D (Test Bit17)
        if (NvramData->Flag & 0x00020000) {
            ((SMBIOS_SYSTEM_ENCLOSURE_INFO*)TempBuffer)->OemDefined = NvramData->OemDefined;
        }

        UpdateStrings((SMBIOS_NVRAM_TYPE*)NvramData, TempBuffer, StrTableInstance);
    }
}
#endif

#if PROCESSOR_DMIEDIT_SUPPORT
//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   UpdateStructuresWithNvramType4
//
// Description: Copy Type 4 strings to TempBuffer. Strings will be copied
//              from NVRAM if exist, or else from existing strings in ROM image.
//              SrcBuffer and TempBuffer pointers are updated
//
// Input:       IN      SMBIOS_NVRAM_TYPE4      *NvramData,
//              IN OUT  UINT8                   *SrcBuffer
//              IN OUT  UINT8                   *TempBuffer
//
// Output:      Updated SrcBuffer and TempBuffer
//
// Modified:
//
// Referrals:
//
// Notes:
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID
UpdateStructuresWithNvramType4(
    IN     SMBIOS_NVRAM_TYPE4   *NvramData,
    IN OUT UINT8                *SrcBuffer,
    IN OUT UINT8                *TempBuffer
)
{
    UINT16      BlockSize;

    // Copy structure data from SrcBuffer
    BlockSize = GetStructureLength(SrcBuffer);
    MemCpy(TempBuffer, SrcBuffer, BlockSize);

    if (NvramData != NULL) {
        UpdateStrings((SMBIOS_NVRAM_TYPE*)NvramData, TempBuffer, 1);
    }
}
#endif

#if OEM_STRING_INFO
//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   UpdateStructuresWithNvramType11
//
// Description: Copy Type 11 strings to TempBuffer. Strings will be copied
//              from NVRAM if exist, or else from existing strings in ROM image.
//              SrcBuffer and TempBuffer pointers are updated
//
// Input:       IN      SMBIOS_NVRAM_TYPE11     *NvramData,
//              IN OUT  UINT8                   *SrcBuffer
//              IN OUT  UINT8                   *TempBuffer
//
// Output:      Updated SrcBuffer and TempBuffer
//
// Modified:
//
// Referrals:
//
// Notes:
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID
UpdateStructuresWithNvramType11(
    IN     SMBIOS_NVRAM_TYPE11  *NvramData,
    IN OUT UINT8                *SrcBuffer,
    IN OUT UINT8                *TempBuffer
)
{
    UINT16      StringSize;
    UINT16      NvramStringSize;
    UINT16      BlockSize;
    UINT32      TestBit;
    UINT8       i;
    UINT8       Count;

    if (NvramData->Flag == 0) {
        BlockSize = GetStructureLength(SrcBuffer);
        MemCpy(TempBuffer, SrcBuffer, BlockSize);
    }
    else {
        // Copy structure data (without string data)
        BlockSize = ((SMBIOS_STRUCTURE_HEADER*)SrcBuffer)->Length;
        MemCpy(TempBuffer, SrcBuffer, BlockSize);

        Count = ((SMBIOS_OEM_STRINGS_INFO*)TempBuffer)->Count;

        // Move pointers
        SrcBuffer += BlockSize;
        TempBuffer += BlockSize;

        // "NUMBER_OF_OEM_STRINGS" string fields
        for (i = 0; (i < Count) && (i < 32); i++) {
            StringSize = (UINT16)(Strlen(SrcBuffer) + 1);       // Size including string NULL terminator
            TestBit = (1 << i);
            if (NvramData->Flag & TestBit) {
                NvramStringSize = (UINT16)(Strlen(NvramData->StringSet[i]) + 1);
                MemCpy(TempBuffer, NvramData->StringSet[i], NvramStringSize);
                TempBuffer += NvramStringSize;
            }
            else {
                MemCpy(TempBuffer, SrcBuffer, StringSize);
                TempBuffer += StringSize;
            }
            SrcBuffer += StringSize;
        }

        // Add NULL byte for end of string-set
        *TempBuffer = 0;
    }
}
#endif

#if SYSTEM_CONFIG_OPTION_INFO
//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   UpdateStructuresWithNvramType12
//
// Description: Copy Type 12 strings to TempBuffer. Strings will be copied
//              from NVRAM if exist, or else from existing strings in ROM image.
//              SrcBuffer and TempBuffer pointers are updated
//
// Input:       IN      SMBIOS_NVRAM_TYPE12     *NvramData,
//              IN OUT  UINT8                   *SrcBuffer
//              IN OUT  UINT8                   *TempBuffer
//
// Output:      Updated SrcBuffer and TempBuffer
//
// Modified:
//
// Referrals:
//
// Notes:
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID
UpdateStructuresWithNvramType12(
    IN     SMBIOS_NVRAM_TYPE12  *NvramData,
    IN OUT UINT8                *SrcBuffer,
    IN OUT UINT8                *TempBuffer
)
{
    UINT16      StringSize;
    UINT16      NvramStringSize;
    UINT16      BlockSize;
    UINT32      TestBit;
    UINT8       i;
    UINT8       Count;

    if (NvramData->Flag == 0) {
        BlockSize = GetStructureLength(SrcBuffer);
        MemCpy(TempBuffer, SrcBuffer, BlockSize);
    }
    else {
        // Copy structure data (without string data)
        BlockSize = ((SMBIOS_STRUCTURE_HEADER*)SrcBuffer)->Length;
        MemCpy(TempBuffer, SrcBuffer, BlockSize);

        Count = ((SMBIOS_SYSTEM_CONFIG_INFO*)TempBuffer)->Count;

        // Move pointers
        SrcBuffer += BlockSize;
        TempBuffer += BlockSize;

        // "NUMBER_OF_SYSTEM_CONFIG_STRINGS" string fields
        for (i = 0; (i < Count) && (i < 32); i++) {
            StringSize = (UINT16)(Strlen((char*)SrcBuffer) + 1);       // Size including string NULL terminator
            TestBit = (1 << i);
            if (NvramData->Flag & TestBit) {
                NvramStringSize = (UINT16)(Strlen(NvramData->StringSet[i]) + 1);
                MemCpy(TempBuffer, NvramData->StringSet[i], NvramStringSize);
                TempBuffer += NvramStringSize;
            }
            else {
                MemCpy(TempBuffer, SrcBuffer, StringSize);
                TempBuffer += StringSize;
            }
            SrcBuffer += StringSize;
        }

        // Add NULL byte for end of string-set
        *TempBuffer = 0;
    }
}
#endif

#if PORTABLE_BATTERY_INFO
//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   UpdateStructuresWithNvramType22
//
// Description: Copy Type 22 strings to TempBuffer. Strings will be copied
//              from NVRAM if exist, or else from existing strings in ROM image.
//              SrcBuffer and TempBuffer pointers are updated
//
// Input:       IN      SMBIOS_NVRAM_TYPE22     *NvramData,
//              IN OUT  UINT8                   *SrcBuffer
//              IN OUT  UINT8                   *TempBuffer
//
// Output:      Updated SrcBuffer and TempBuffer
//
// Modified:
//
// Referrals:
//
// Notes:
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID
UpdateStructuresWithNvramType22(
    IN     SMBIOS_NVRAM_TYPE22  *NvramData,
    IN OUT UINT8                *SrcBuffer,
    IN OUT UINT8                *TempBuffer
)
{
    UINT16      BlockSize;

    // Copy structure data from SrcBuffer
    BlockSize = GetStructureLength(SrcBuffer);
    MemCpy(TempBuffer, SrcBuffer, BlockSize);

    if (NvramData != NULL) {
        // Type field - Offset 9 (Test Bit16)
        if (NvramData->Flag & 0x00010000) {
            ((SMBIOS_PORTABLE_BATTERY_INFO*)TempBuffer)->DeviceChemistry = NvramData->DeviceChemistry;
        }

        // OEM-Defined field - Offset 0x0a (Test Bit17)
        if (NvramData->Flag & 0x00020000) {
            ((SMBIOS_PORTABLE_BATTERY_INFO*)TempBuffer)->DesignCapacity = NvramData->DesignCapacity;
        }

        // OEM-Defined field - Offset 0x0c (Test Bit18)
        if (NvramData->Flag & 0x00040000) {
            ((SMBIOS_PORTABLE_BATTERY_INFO*)TempBuffer)->DesignVoltage = NvramData->DesignVoltage;
        }

        // OEM-Defined field - Offset 0x0f (Test Bit19)
        if (NvramData->Flag & 0x00080000) {
            ((SMBIOS_PORTABLE_BATTERY_INFO*)TempBuffer)->MaxErrorInBatteryData = NvramData->MaxErrorInBatteryData;
        }

        // OEM-Defined field - Offset 0x10 (Test Bit20)
        if (NvramData->Flag & 0x00100000) {
            ((SMBIOS_PORTABLE_BATTERY_INFO*)TempBuffer)->SBDSSerialNumber = NvramData->SbdsSerialNumber;
        }

        // OEM-Defined field - Offset 0x12 (Test Bit21)
        if (NvramData->Flag & 0x00200000) {
            ((SMBIOS_PORTABLE_BATTERY_INFO*)TempBuffer)->SBDSManufacturerDate = NvramData->SbdsManufacturerDate;
        }

        // OEM-Defined field - Offset 0x15 (Test Bit22)
        if (NvramData->Flag & 0x00400000) {
            ((SMBIOS_PORTABLE_BATTERY_INFO*)TempBuffer)->DesignCapabilityMult = NvramData->DesignCapacityMultiplier;
        }

        // OEM-Defined field - Offset 0x16 (Test Bit23)
        if (NvramData->Flag & 0x00800000) {
            ((SMBIOS_PORTABLE_BATTERY_INFO*)TempBuffer)->OEMSpecific = NvramData->OemSpecific;
        }

        UpdateStrings((SMBIOS_NVRAM_TYPE*)NvramData, TempBuffer, 1);
    }
}
#endif

#if SYSTEM_POWER_SUPPLY_INFO
//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   UpdateStructuresWithNvramType39
//
// Description: Copy Type 39 strings to TempBuffer. Strings will be copied
//              from NVRAM if exist, or else from existing strings in ROM image.
//              SrcBuffer and TempBuffer pointers are updated
//
// Input:       IN      SMBIOS_NVRAM_TYPE39     *NvramData,
//              IN OUT  UINT8                   *SrcBuffer
//              IN OUT  UINT8                   *TempBuffer
//
// Output:      Updated SrcBuffer and TempBuffer
//
// Modified:
//
// Referrals:
//
// Notes:
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID
UpdateStructuresWithNvramType39(
    IN     SMBIOS_NVRAM_TYPE39  *NvramData,
    IN OUT UINT8                *SrcBuffer,
    IN OUT UINT8                *TempBuffer
)
{
    UINT16      BlockSize;

    // Copy structure data from SrcBuffer
    BlockSize = GetStructureLength(SrcBuffer);
    MemCpy(TempBuffer, SrcBuffer, BlockSize);

    if (NvramData != NULL) {
        // Type field - Offset 4 (Test Bit16)
        if (NvramData->Flag & 0x00010000) {
            ((SMBIOS_SYSTEM_PWR_SUPPY_INFO*)TempBuffer)->PwrUnitGroup = NvramData->PwrUnitGroup;
        }

        // OEM-Defined field - Offset 0x0c (Test Bit17)
        if (NvramData->Flag & 0x00020000) {
            ((SMBIOS_SYSTEM_PWR_SUPPY_INFO*)TempBuffer)->MaxPwrCapacity = NvramData->MaxPwrCapacity;
        }

        // OEM-Defined field - Offset 0x0e (Test Bit18)
        if (NvramData->Flag & 0x00040000) {
            ((SMBIOS_SYSTEM_PWR_SUPPY_INFO*)TempBuffer)->PwrSupplyChar = NvramData->PwrSupplyChar;
        }

        // OEM-Defined field - Offset 0x10 (Test Bit19)
        if (NvramData->Flag & 0x00080000) {
            ((SMBIOS_SYSTEM_PWR_SUPPY_INFO*)TempBuffer)->InputVoltProbeHandle = NvramData->InputVoltageProbeHandle;
        }

        // OEM-Defined field - Offset 0x12 (Test Bit20)
        if (NvramData->Flag & 0x00100000) {
            ((SMBIOS_SYSTEM_PWR_SUPPY_INFO*)TempBuffer)->CoolingDevHandle = NvramData->CoolingDevHandle;
        }

        // OEM-Defined field - Offset 0x14 (Test Bit21)
        if (NvramData->Flag & 0x00200000) {
            ((SMBIOS_SYSTEM_PWR_SUPPY_INFO*)TempBuffer)->InputCurrentProbeHandle = NvramData->InputCurrentProbeHandle;
        }

        UpdateStrings((SMBIOS_NVRAM_TYPE*)NvramData, TempBuffer, 1);
    }
}
#endif

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   GetType22StringIndex
//
// Description: Returns the string index for Type 22 structure from a given
//              Offset.
//
// Input:       IN UINT8   Offset
//
// Output:      UINT8 - Type 22 Structure String index
//
// Modified:
//
// Referrals:
//
// Notes:
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
UINT8
GetType22StringIndex(
    IN UINT8       Offset
)
{
    switch (Offset) {
        case 0x0e: return 5;
        case 0x14: return 6;
    }
    return (Offset - 4);
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   GetType39StringIndex
//
// Description: Returns the string index for Type 39 structure from a given
//              Offset.
//
// Input:       IN UINT8   Offset
//
// Output:      UINT8 - Type 39 Structure String index
//
// Modified:
//
// Referrals:
//
// Notes:
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
UINT8
GetType39StringIndex(
    IN UINT8       Offset
)
{
    return (Offset - 5);
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   LoadRealModeFileSection
//
// Description: Locates the input specified Guid file in the Firmware Volumn
//              and loads it into the input Buffer
//
// Input:       IN      EFI_GUID *Guid -    File GUID to read
//              IN      EFI_SECTION_TYPE    SectionType
//              IN OUT  VOID                **Buffer
//              IN OUT  UINTN               *BufferSize
//
// Output:      EFI_STATUS
//              VOID  **Buffer - Contains the content of the Guid file
//              UINTN *BufferSize - Size of the output buffer
//
// Modified:
//
// Referrals:
//
// Notes:
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS
LoadRealModeFileSection(
    IN      EFI_GUID  				*Guid,
	IN      EFI_SECTION_TYPE	    SectionType,
    IN OUT  VOID      				**Buffer,
    IN OUT  UINTN     				*BufferSize
)
{
    EFI_STATUS                    Status;
#if (PI_SPECIFICATION_VERSION < 0x00010000)
    EFI_FIRMWARE_VOLUME_PROTOCOL  *Fv;
#else
    EFI_FIRMWARE_VOLUME2_PROTOCOL *Fv;
#endif
    UINT32                        Authentication;
    UINTN                         NumHandles;
    EFI_HANDLE                    *HandleBuffer;
    UINTN                         i;

    Status = pBS->LocateHandleBuffer(ByProtocol,&gEfiFVProtocolGuid,NULL,&NumHandles,&HandleBuffer);
    if (EFI_ERROR(Status)) return Status;

    for (i = 0; i< NumHandles; ++i) {
        Status = pBS->HandleProtocol(HandleBuffer[i],&guidFV,&Fv);
        if (EFI_ERROR(Status)) continue;

        Status = Fv->ReadSection(Fv,
                                Guid,
                                SectionType,
                                0,        //Instance
                                Buffer,
                                BufferSize,
                                &Authentication);

        if (Status == EFI_SUCCESS) break;
    }

    pBS->FreePool(HandleBuffer);
    return Status;
}

#if (defined(SmbiosDMIEdit_SUPPORT) && (SmbiosDMIEdit_SUPPORT != 0))
//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   UpdateStructuresWithNvramData
//
// Description: Updates structures in input Buffer with DMI Data in NVRAM
//
// Input:       IN  UINT8   *Buffer
//              IN  UINT8   BufferSize
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
UpdateStructuresWithNvramData(
    IN  UINT8     *Buffer,
    IN  UINTN     BufferSize
)
{
    EFI_STATUS              Status;
    UINT16                  StructureSize;
    UINT8                   *BufferPtr = Buffer;
    UINT8                   *TempBuffer;
    UINT8                   *TempBufferPtr;
    UINTN                   Index;
    UINTN                   i;
    BOOLEAN                 UpdateFlag = FALSE; // Flag indicating if any structure has been updated

#if (TYPE2_STRUCTURE == 1)
    UINT16                  *Type2Handle;
#endif											// TYPE2_STRUCTURE
#if (TYPE3_STRUCTURE == 1)
    UINT16                  *Type3Handle;
    UINT8                   StrTableInstance;
#endif											// TYPE3_STRUCTURE
    UINT16                  *Type22Handle;
    UINT16                  *Type39Handle;

    UINT8                   *DmiData = NULL;
    UINTN                   DmiDataSize;

    UINT8                   *NvramDataPtrArray[DMI_ARRAY_COUNT];

    SMBIOS_NVRAM_TYPE0      NvramType0;
    SMBIOS_NVRAM_TYPE1      NvramType1;
    SMBIOS_NVRAM_TYPE2      *NvramType2 = NULL;
    SMBIOS_NVRAM_TYPE3      *NvramType3 = NULL;
    SMBIOS_NVRAM_TYPE11     NvramType11;
    SMBIOS_NVRAM_TYPE12     NvramType12;
    SMBIOS_NVRAM_TYPE22     *NvramType22 = NULL;
    SMBIOS_NVRAM_TYPE39     *NvramType39 = NULL;

#if !defined(SMBIOS_DMIEDIT_DATA_LOC) || SMBIOS_DMIEDIT_DATA_LOC != 2
    EFI_GUID                FlashDataFile = {0xfd44820b, 0xf1ab, 0x41c0, 0xae, 0x4e, 0x0c, 0x55, 0x55, 0x6e, 0xb9, 0xbd};
    UINT8                   *FlashData = NULL;
    UINTN                   FlashDataSize = 0;
    UINT8                   *FlashDataPtr;
    UINT8                   *FlashDataEnd;
#endif                                      // SMBIOS_DMIEDIT_DATA_LOC

    TRACE((-1, "***  SMBIOS - UpdateStructuresWithNvramData  ***\n"));

    // Initialize NVRam variables
    for (i = 0; i < DMI_ARRAY_COUNT; i++) {
        NvramDataPtrArray[i] = NULL;
    }

    MemSet(&NvramType0, sizeof(SMBIOS_NVRAM_TYPE0), 0);
    MemSet(&NvramType1, sizeof(SMBIOS_NVRAM_TYPE1), 0);
#if (TYPE2_STRUCTURE == 1)
    pBS->AllocatePool(EfiBootServicesData, NUMBER_OF_BASEBOARDS * sizeof(UINT16), (void**)&Type2Handle);
    pBS->AllocatePool(EfiBootServicesData, NUMBER_OF_BASEBOARDS * sizeof(SMBIOS_NVRAM_TYPE2), (void**)&NvramType2);
    for (i = 0; i < NUMBER_OF_BASEBOARDS; i++) {
        Type2Handle[i] = 0;
        NvramType2[i].Flag = 0;
    }
#endif										// TYPE2_STRUCTURE
#if (TYPE3_STRUCTURE == 1)
    pBS->AllocatePool(EfiBootServicesData, NUMBER_OF_SYSTEM_CHASSIS * sizeof(UINT16), (void**)&Type3Handle);
    pBS->AllocatePool(EfiBootServicesData, NUMBER_OF_SYSTEM_CHASSIS * sizeof(SMBIOS_NVRAM_TYPE3), (void**)&NvramType3);
    for (i = 0; i < NUMBER_OF_SYSTEM_CHASSIS; i++) {
        Type3Handle[i] = 0;
        NvramType3[i].Flag = 0;
    }
#endif                                      // TYPE3_STRUCTURE
    MemSet(&NvramType4, sizeof(SMBIOS_NVRAM_TYPE4), 0);
    MemSet(&NvramType11, sizeof(SMBIOS_NVRAM_TYPE11), 0);
    MemSet(&NvramType12, sizeof(SMBIOS_NVRAM_TYPE12), 0);
    pBS->AllocatePool(EfiBootServicesData, gSmbiosBoardProtocol->NumberOfBatteries * sizeof(UINT16), (void**)&Type22Handle);
    pBS->AllocatePool(EfiBootServicesData, gSmbiosBoardProtocol->NumberOfBatteries * sizeof(SMBIOS_NVRAM_TYPE22), (void**)&NvramType22);
    for (i = 0; i < gSmbiosBoardProtocol->NumberOfBatteries; i++) {
        Type22Handle[i] = 0;
        NvramType22[i].Flag = 0;
    }
    pBS->AllocatePool(EfiBootServicesData, NUMBER_OF_POWER_SUPPLY * sizeof(UINT16), (void**)&Type39Handle);
    pBS->AllocatePool(EfiBootServicesData, NUMBER_OF_POWER_SUPPLY * sizeof(SMBIOS_NVRAM_TYPE39), (void**)&NvramType39);
    for (i = 0; i < NUMBER_OF_POWER_SUPPLY; i++) {
        Type39Handle[i] = 0;
        NvramType39[i].Flag = 0;
    }

#if !defined(SMBIOS_DMIEDIT_DATA_LOC) || SMBIOS_DMIEDIT_DATA_LOC != 2
    // Get SMBios NVRam Data Structure Image
    Status = LoadRealModeFileSection(&FlashDataFile, EFI_SECTION_RAW, &FlashData, &FlashDataSize);
    if (EFI_ERROR(Status)) goto Function_Exit;

    FlashDataPtr = FlashData;
    FlashDataEnd = FlashData + FLASHDATA_SIZE;

    // Skip _ASB signature and _FlashDataSize
    FlashDataPtr += 8;

    while ((FlashDataPtr < FlashDataEnd) && (*(UINT32*)FlashDataPtr != 0xffffffff)) {
        if (((TABLE_INFO*)FlashDataPtr)->Flags & DMIEDIT_DELETE_STRUC) {
            TRACE((-1, "Delete structure. Handle = %x\n", ((TABLE_INFO*)FlashDataPtr)->Handle));
            DeleteStructureByHandle(((TABLE_INFO*)FlashDataPtr)->Handle);
            UpdateFlag = TRUE;
        }
        else if (((TABLE_INFO*)FlashDataPtr)->Flags & DMIEDIT_ADD_STRUC) {
            TRACE((-1, "Add structure by handle. Handle = %x\n", ((TABLE_INFO*)FlashDataPtr)->Handle));
            TempBufferPtr = FlashDataPtr + sizeof (TABLE_INFO);
            AddStructureByHandle(((TABLE_INFO*)FlashDataPtr)->Handle, TempBufferPtr, ((TABLE_INFO*)FlashDataPtr)->Size);
            UpdateFlag = TRUE;
        }
        else {
            TRACE((-1, "Change structure. Type = %x, Handle = %x, Offset = %x\n",\
                                          ((TABLE_INFO*)FlashDataPtr)->Type,\
                                          ((TABLE_INFO*)FlashDataPtr)->Handle,\
                                          ((TABLE_INFO*)FlashDataPtr)->Offset));
            DmiDataSize = ((TABLE_INFO*)FlashDataPtr)->Size;
            Status = pBS->AllocatePool(
                                EfiBootServicesData,
                                DmiDataSize,
                                (void**)&DmiData);
            if (Status == EFI_SUCCESS) {
                MemCpy(DmiData,
                       FlashDataPtr + sizeof(TABLE_INFO),
                       DmiDataSize);

                switch (((TABLE_INFO*)FlashDataPtr)->Type) {
                    case 0  :   {
                                    // Get string index (Smbios spec) at Offset
                                    Index = GetStrIndex(0, ((TABLE_INFO*)FlashDataPtr)->Offset, 1);
                                    if (Index != 0xff) {
                                        NvramType0.StringSet[Index] = (char*)DmiData;
                                        NvramType0.Flag |= (1 << Index);
                                        UpdateFlag = TRUE;
                                    }
                                    break;
                                }
                    case 1  :   {
                                    if (((TABLE_INFO*)FlashDataPtr)->Offset == 8) {
                                        MemCpy(&NvramType1.Uuid, FlashDataPtr + sizeof(TABLE_INFO), ((TABLE_INFO*)FlashDataPtr)->Size);
                                        NvramType1.Flag |= 0x00010000;
                                        UpdateFlag = TRUE;
                                    }
                                    else {
                                        // Get string index (Smbios spec) at Offset
                                        Index = GetStrIndex(1, ((TABLE_INFO*)FlashDataPtr)->Offset, 1);
                                        if (Index != 0xff) {
                                            NvramType1.StringSet[Index] = (char*)DmiData;
                                            NvramType1.Flag |= (1 << Index);
                                            UpdateFlag = TRUE;
                                        }
                                    }
                                    break;
                                }
                    #if BASE_BOARD_INFO
                    case 2  :   {
                                    if (gSmbiosBoardProtocol->BaseBoardInfoSupport) {
                                        // Save handle number in Type2Handle array for each Type 2 structure
                                        for (i = 0; i < NUMBER_OF_BASEBOARDS; i++) {
                                            if (Type2Handle[i] == 0) {
                                                Type2Handle[i] = ((TABLE_INFO*)FlashDataPtr)->Handle;
                                                break;
                                            }
                                            if (((TABLE_INFO*)FlashDataPtr)->Handle == Type2Handle[i]) break;
                                        }
                                        if (i < NUMBER_OF_BASEBOARDS) {
                                            NvramType2[i].Handle = ((TABLE_INFO*)FlashDataPtr)->Handle;

                                            // Get string index (Smbios spec) at Offset
                                            Index = GetStrIndex(2, ((TABLE_INFO*)FlashDataPtr)->Offset, 1);
                                            if (Index != 0xff) {
                                                NvramType2[i].StringSet[Index] = (char*)DmiData;
                                                NvramType2[i].Flag |= (1 << Index);
                                                UpdateFlag = TRUE;
                                            }
                                        }
                                    }
                                    break;
                                }
                    #endif                  // BASE_BOARD_INFO
                    #if SYS_CHASSIS_INFO
                    case 3  :   {
                                    StrTableInstance = GetInstanceByTypeHandle(3, ((TABLE_INFO*)FlashDataPtr)->Handle);

                                    if (gSmbiosBoardProtocol->SysChassisInfoSupport) {
                                        // Save handle number in Type3Handle array for each Type 3 structure
                                        for (i = 0; i < NUMBER_OF_SYSTEM_CHASSIS; i++) {
                                            if (Type3Handle[i] == 0) {
                                                Type3Handle[i] = ((TABLE_INFO*)FlashDataPtr)->Handle;
                                                break;
                                            }
                                            if (((TABLE_INFO*)FlashDataPtr)->Handle == Type3Handle[i]) break;
                                        }
                                        if (i < NUMBER_OF_SYSTEM_CHASSIS) {
                                            NvramType3[i].Handle = ((TABLE_INFO*)FlashDataPtr)->Handle;
                                            if (((TABLE_INFO*)FlashDataPtr)->Offset == 5) {
                                                MemCpy(&NvramType3[i].Type, FlashDataPtr + sizeof(TABLE_INFO), 1);
                                                NvramType3[i].Flag |= 0x00010000;
                                                UpdateFlag = TRUE;
                                            }
                                            else if (((TABLE_INFO*)FlashDataPtr)->Offset == 0x0d) {
                                                MemCpy(&NvramType3[i].OemDefined, FlashDataPtr + sizeof(TABLE_INFO), sizeof(UINT32));
                                                NvramType3[i].Flag |= 0x00020000;
                                                UpdateFlag = TRUE;
                                            }
                                            else {
                                                // Get string index (Smbios spec) at Offset
                                                Index = GetStrIndex(3, ((TABLE_INFO*)FlashDataPtr)->Offset, StrTableInstance);
                                                if (Index != 0xff) {
                                                    NvramType3[i].StringSet[Index] = (char*)DmiData;
                                                    NvramType3[i].Flag |= (1 << Index);
                                                    UpdateFlag = TRUE;
                                                }
                                            }
                                        }
                                    }
                                    break;
                                }
                    #endif                  // SYS_CHASSIS_INFO
                    #if PROCESSOR_DMIEDIT_SUPPORT
                    case 4  :   {
                                    if (gSmbiosBoardProtocol->ProcessorDmiEditSupport) {
                                        // Get string index (Smbios spec) at Offset
                                        Index = GetStrIndex(4, ((TABLE_INFO*)FlashDataPtr)->Offset, 1);
                                        if (Index != 0xff) {
                                            NvramType4.StringSet[Index] = (char*)DmiData;
                                            NvramType4.Flag |= (1 << Index);
                                            UpdateFlag = TRUE;
                                        }
                                    }
                                    break;
                                }
                    #endif                  // SYS_CHASSIS_INFO
                    #if OEM_STRING_INFO
                    case 11 :   {
                                    if (gSmbiosBoardProtocol->OemStringInfoSupport) {
                                        Index = ((TABLE_INFO*)FlashDataPtr)->Offset - 1;
                                        NvramType11.StringSet[Index] = (char*)DmiData;
                                        NvramType11.Flag |= (1 << Index);
	                                    UpdateFlag = TRUE;
                                    }
                                    break;
                                }
                    #endif                  // OEM_STRING_INFO
                    #if SYSTEM_CONFIG_OPTION_INFO
                    case 12 :   {
                                    if (gSmbiosBoardProtocol->SystemConfigOptionInfoSupport) {
                                        Index = ((TABLE_INFO*)FlashDataPtr)->Offset - 1;
                                        NvramType12.StringSet[Index] = (char*)DmiData;
                                        NvramType12.Flag |= (1 << Index);
	                                    UpdateFlag = TRUE;
                                    }
                                    break;
                                }
                    #endif                  // SYSTEM_CONFIG_OPTION_INFO
                    #if PORTABLE_BATTERY_INFO
                    case 22 :   {
                                    // Save handle number in Type22Handle array for each Type 22 structure
                                    for (i = 0; i < gSmbiosBoardProtocol->NumberOfBatteries; i++) {
                                        if (Type22Handle[i] == 0) {
                                            Type22Handle[i] = ((TABLE_INFO*)FlashDataPtr)->Handle;
                                            break;
                                        }
                                        if (((TABLE_INFO*)FlashDataPtr)->Handle == Type22Handle[i]) break;
                                    }
                                    if (i < gSmbiosBoardProtocol->NumberOfBatteries) {
                                        NvramType22[i].Handle = ((TABLE_INFO*)FlashDataPtr)->Handle;
                                        switch (((TABLE_INFO*)FlashDataPtr)->Offset) {
                                            case 0x04:
                                            case 0x05:
                                            case 0x06:
                                            case 0x07:
                                            case 0x08:
                                            case 0x0e:
                                            case 0x14:  Index = GetType22StringIndex(((TABLE_INFO*)FlashDataPtr)->Offset);
                                                        NvramType22[i].StringSet[Index] = (char*)DmiData;
                                                        NvramType22[i].Flag |= (1 << Index);
                                                        break;
                                            case 0x09:  MemCpy(&NvramType22[i].DeviceChemistry, FlashDataPtr + sizeof(TABLE_INFO), 1);
                                                        NvramType22[i].Flag |= 0x00010000;
                                                        break;
                                            case 0x0a:  MemCpy(&NvramType22[i].DesignCapacity, FlashDataPtr + sizeof(TABLE_INFO), 2);
                                                        NvramType22[i].Flag |= 0x00020000;
                                                        break;
                                            case 0x0c:  MemCpy(&NvramType22[i].DesignVoltage, FlashDataPtr + sizeof(TABLE_INFO), 2);
                                                        NvramType22[i].Flag |= 0x00040000;
                                                        break;
                                            case 0x0f:  MemCpy(&NvramType22[i].MaxErrorInBatteryData, FlashDataPtr + sizeof(TABLE_INFO), 1);
                                                        NvramType22[i].Flag |= 0x00080000;
                                                        break;
                                            case 0x10:  MemCpy(&NvramType22[i].SbdsSerialNumber, FlashDataPtr + sizeof(TABLE_INFO), 2);
                                                        NvramType22[i].Flag |= 0x00100000;
                                                        break;
                                            case 0x12:  MemCpy(&NvramType22[i].SbdsManufacturerDate, FlashDataPtr + sizeof(TABLE_INFO), 2);
                                                        NvramType22[i].Flag |= 0x00200000;
                                                        break;
                                            case 0x15:  MemCpy(&NvramType22[i].DesignCapacityMultiplier, FlashDataPtr + sizeof(TABLE_INFO), 1);
                                                        NvramType22[i].Flag |= 0x00400000;
                                                        break;
                                            case 0x16:  MemCpy(&NvramType22[i].OemSpecific, FlashDataPtr + sizeof(TABLE_INFO), 4);
                                                        NvramType22[i].Flag |= 0x00800000;
                                                        break;
                                        }
                                    }
                                    UpdateFlag = TRUE;
                                    break;
                                }
                    #endif                  // PORTABLE_BATTERY_INFO
                    #if SYSTEM_POWER_SUPPLY_INFO
                    case 39 :   {
                                    // Save handle number in Type39Handle array for each Type 39 structure
                                    for (i = 0; i < NUMBER_OF_POWER_SUPPLY; i++) {
                                        if (Type39Handle[i] == 0) {
                                            Type39Handle[i] = ((TABLE_INFO*)FlashDataPtr)->Handle;
                                            break;
                                        }
                                        if (((TABLE_INFO*)FlashDataPtr)->Handle == Type39Handle[i]) break;
                                    }
                                    if (i < NUMBER_OF_POWER_SUPPLY) {
                                        NvramType39[i].Handle = ((TABLE_INFO*)FlashDataPtr)->Handle;
                                        switch (((TABLE_INFO*)FlashDataPtr)->Offset) {
                                            case 0x04:  MemCpy(&NvramType39[i].PwrUnitGroup, FlashDataPtr + sizeof(TABLE_INFO), 1);
                                                        NvramType39[i].Flag |= 0x00010000;
                                                        break;
                                            case 0x05:
                                            case 0x06:
                                            case 0x07:
                                            case 0x08:
                                            case 0x09:
                                            case 0x0a:
                                            case 0x0b:  Index = GetType39StringIndex(((TABLE_INFO*)FlashDataPtr)->Offset);
                                                        NvramType39[i].StringSet[Index] = (char*)DmiData;
                                                        NvramType39[i].Flag |= (1 << Index);
                                                        break;
                                            case 0x0c:  NvramType39[i].MaxPwrCapacity = *(UINT16*)(FlashDataPtr + sizeof(TABLE_INFO));
                                                        NvramType39[i].Flag |= 0x00020000;
                                                        break;
                                            case 0x0e:  NvramType39[i].PwrSupplyChar = *(UINT16*)(FlashDataPtr + sizeof(TABLE_INFO));
                                                        NvramType39[i].Flag |= 0x00040000;
                                                        break;
                                            case 0x10:  NvramType39[i].InputVoltageProbeHandle = *(UINT16*)(FlashDataPtr + sizeof(TABLE_INFO));
                                                        NvramType39[i].Flag |= 0x00080000;
                                                        break;
                                            case 0x12:  NvramType39[i].CoolingDevHandle = *(UINT16*)(FlashDataPtr + sizeof(TABLE_INFO));
                                                        NvramType39[i].Flag |= 0x00100000;
                                                        break;
                                            case 0x14:  NvramType39[i].InputCurrentProbeHandle = *(UINT16*)(FlashDataPtr + sizeof(TABLE_INFO));
                                                        NvramType39[i].Flag |= 0x00200000;
                                                        break;
                                        }
                                    }
                                    UpdateFlag = TRUE;
                                }
                    #endif                  // SYSTEM_POWER_SUPPLY_INFO
                }
            }
        }

        if (((TABLE_INFO*)FlashDataPtr)->Flags & DMIEDIT_DELETE_STRUC) {
            FlashDataPtr += sizeof(TABLE_INFO);
        }
        else {
            FlashDataPtr += (sizeof(TABLE_INFO) + ((TABLE_INFO*)FlashDataPtr)->Size);
        }
    }
#else										// SMBIOS_DMIEDIT_DATA_LOC
{
    CHAR16                  *DmiArrayVar = L"DmiArray";
    DMI_VAR                 *DmiArray;
    UINTN                   DmiArraySize = DMI_ARRAY_COUNT * sizeof(DMI_VAR);
    UINT8                   Count = 0;
    CHAR16                  *S1 = L"                ";
    UINT8                   Type;
	UINT16					Handle;
    UINT8                   Offset;
	UINT8					Flags;

    pBS->AllocatePool(EfiBootServicesData, DmiArraySize, (void**)&DmiArray);
    Status = pRS->GetVariable(
                        DmiArrayVar,
                        &gEfiSmbiosNvramGuid,
                        NULL,
                        &DmiArraySize,
                        DmiArray);

    if (Status == EFI_SUCCESS) {
        Count = DmiArray[0].Type;     // Note: DmiArray[0] has count # instead of Type/Offset

        for (Index = 0; Index < Count; Index++) {
            Type = DmiArray[Index + 1].Type;
			Handle = DmiArray[Index + 1].Handle;
            Offset = DmiArray[Index + 1].Offset;
			Flags = DmiArray[Index + 1].Flags;

            Swprintf(S1, L"DmiVar%02x%04x%02x%02x",
					   Type,
					   Handle,
					   Offset,
					   Flags);

        	// Check if variable already exists
            //
            // Size of zero is used to detect if the variable exists.
            // If the variable exists, an error code of EFI_BUFFER_TOO_SMALL
            // would be returned
            DmiDataSize = 0;
            Status = pRS->GetVariable(
                                S1,
                                &gEfiSmbiosNvramGuid,
                                NULL,
                                &DmiDataSize,
                                &NvramDataPtrArray[Index]);

            if (Status == EFI_NOT_FOUND) {
                continue;
            }

            if (Status == EFI_BUFFER_TOO_SMALL) {
                Status = pBS->AllocatePool(
                                    EfiBootServicesData,
                                    DmiDataSize,
                                    (void**)&NvramDataPtrArray[Index]);

                DmiData = NvramDataPtrArray[Index];

                Status = pRS->GetVariable(
                                    S1,
                                    &gEfiSmbiosNvramGuid,
                                    NULL,
                                    &DmiDataSize,
                                    DmiData);
            }

			if (Flags & DMIEDIT_DELETE_STRUC) {
	            TRACE((-1, "Delete structure. Handle = %x\n", Handle));
	            DeleteStructureByHandle(Handle);
                UpdateFlag = TRUE;
			}
			else if (Flags & DMIEDIT_ADD_STRUC) {
	            if (Status == EFI_SUCCESS) {
	                TRACE((-1, "Add structure by handle. Handle = %x\n", Handle));
		            AddStructureByHandle(Handle, DmiData, (UINT16)DmiDataSize);
                    UpdateFlag = TRUE;
				}
			}
			else {
	            if (Status == EFI_SUCCESS) {
	                TRACE((-1, "Change structure. Type = %x, Handle = %x, Offset = %x\n",\
                                Type, Handle, Offset));
	                switch (Type) {
	                    case 00:
	                            if (Offset == 0x04) {               // Vendor
                                    NvramType0.StringSet[0] = (char*)DmiData;
	                                NvramType0.Flag |= 0x00000001;
	                            }
	                            else if (Offset == 0x05) {          // Version
                                    NvramType0.StringSet[1] = (char*)DmiData;
	                                NvramType0.Flag |= 0x00000002;
	                            }
	                            else if (Offset == 0x08) {          // Release Date
                                    NvramType0.StringSet[2] = (char*)DmiData;
	                                NvramType0.Flag |= 0x00000004;
	                            }
                                UpdateFlag = TRUE;
	                            break;
	                    case 01:
	                            if (Offset == 0x04) {               // Manufacturer
                                    NvramType1.StringSet[0] = (char*)DmiData;
	                                NvramType1.Flag |= 0x00000001;
	                            }
	                            else if (Offset == 0x05) {          // Product Name
                                    NvramType1.StringSet[1] = (char*)DmiData;
	                                NvramType1.Flag |= 0x00000002;
	                            }
	                            else if (Offset == 0x06) {          // Version
                                    NvramType1.StringSet[2] = (char*)DmiData;
	                                NvramType1.Flag |= 0x00000004;
	                            }
	                            else if (Offset == 0x07) {          // Serial Number
                                    NvramType1.StringSet[3] = (char*)DmiData;
	                                NvramType1.Flag |= 0x00000008;
	                            }
	                            else if (Offset == 0x08) {          // UUID
	                                MemCpy(&NvramType1.Uuid,
	                                        DmiData,
	                                        16);
	                                NvramType1.Flag |= 0x00010000;
	                            }
	                            else if (Offset == 0x19) {          // SKU Number
                                    NvramType1.StringSet[4] = (char*)DmiData;
	                                NvramType1.Flag |= 0x00000010;
	                            }
	                            else if (Offset == 0x1a) {          // Family
                                    NvramType1.StringSet[5] = (char*)DmiData;
	                                NvramType1.Flag |= 0x00000020;
	                            }
                                UpdateFlag = TRUE;
	                            break;
#if BASE_BOARD_INFO
	                    case 02:
	                            if (gSmbiosBoardProtocol->BaseBoardInfoSupport) {
                                    // Save handle number in Type2Handle array for each Type 2 structure
                                    for (i = 0; i < NUMBER_OF_BASEBOARDS; i++) {
                                        if (Type2Handle[i] == 0) {
                                            Type2Handle[i] = Handle;
                                            break;
                                        }
                                        if (Handle == Type2Handle[i]) break;
                                    }
                                    if (i < NUMBER_OF_BASEBOARDS) {
                                        NvramType2[i].Handle = Handle;
                                        if (Offset == 0x04) {               // Manufacturer
                                            NvramType2[i].StringSet[0] = (char*)DmiData;
                                            NvramType2[i].Flag |= 0x00000001;
                                        }
                                        else if (Offset == 0x05) {          // Product
                                            NvramType2[i].StringSet[1] = (char*)DmiData;
                                            NvramType2[i].Flag |= 0x00000002;
                                        }
                                        else if (Offset == 0x06) {          // Version
                                            NvramType2[i].StringSet[2] = (char*)DmiData;
                                            NvramType2[i].Flag |= 0x00000004;
                                        }
                                        else if (Offset == 0x07) {          // Serial Number
                                            NvramType2[i].StringSet[3] = (char*)DmiData;
                                            NvramType2[i].Flag |= 0x00000008;
                                        }
                                        else if (Offset == 0x08) {          // Asset Tag
                                            NvramType2[i].StringSet[4] = (char*)DmiData;
                                            NvramType2[i].Flag |= 0x00000010;
                                        }
                                        else if (Offset == 0x0a) {          // Location in Chassis
                                            NvramType2[i].StringSet[5] = (char*)DmiData;
    	                                    NvramType2[i].Flag |= 0x00000020;
                                        }
                                    }
	                            }
                                UpdateFlag = TRUE;
	                            break;
#endif                                      // BASE_BOARD_INFO
#if SYS_CHASSIS_INFO
	                    case 03:
	                            if (gSmbiosBoardProtocol->SysChassisInfoSupport) {
                                    // Save handle number in Type3Handle array for each Type 3 structure
                                    for (i = 0; i < NUMBER_OF_SYSTEM_CHASSIS; i++) {
                                        if (Type3Handle[i] == 0) {
                                            Type3Handle[i] = Handle;
                                            break;
                                        }
                                        if (Handle == Type3Handle[i]) break;
                                    }
                                    if (i < NUMBER_OF_SYSTEM_CHASSIS) {
                                        NvramType3[i].Handle = Handle;
										TempBuffer = SmbiosDataTable;

                                        if (Offset == 0x04) {               // Manufacturer
											NvramType3[i].StringSet[0] = (char*)DmiData;
											NvramType3[i].Flag |= 0x00000001;
                                        }
                                        else if (Offset == 0x05) {          // Type
											NvramType3[i].Type = *(UINT8*)DmiData;
											NvramType3[i].Flag |= 0x00010000;
                                        }
                                        else if (Offset == 0x06) {          // Version
											NvramType3[i].StringSet[1] = (char*)DmiData;
											NvramType3[i].Flag |= 0x00000002;
                                        }
                                        else if (Offset == 0x07) {          // Serial Number
											NvramType3[i].StringSet[2] = (char*)DmiData;
											NvramType3[i].Flag |= 0x00000004;
                                        }
                                        else if (Offset == 0x08) {          // Asset Tag
											NvramType3[i].StringSet[3] = (char*)DmiData;
											NvramType3[i].Flag |= 0x00000008;
                                        }
                                        else if (Offset == 0x0d) {          // OEM-defined
											NvramType3[i].OemDefined = *(UINT32*)DmiData;
											NvramType3[i].Flag |= 0x00020000;
                                        }
										else if (FindStructureHandle(&TempBuffer, Handle)) {
										    if (Offset == 0x15 + (((SMBIOS_SYSTEM_ENCLOSURE_INFO*)TempBuffer)->ElementCount * ((SMBIOS_SYSTEM_ENCLOSURE_INFO*)TempBuffer)->ElementRecordLength)) {  // SKU Number
												NvramType3[i].StringSet[4] = (char*)DmiData;
												NvramType3[i].Flag |= 0x00000010;
										    }
										}
                                    }
	                            }
                                UpdateFlag = TRUE;
	                            break;
#endif                                      // SYS_CHASSIS_INFO
#if ( defined(PROCESSOR_DMIEDIT_SUPPORT) && (PROCESSOR_DMIEDIT_SUPPORT == 1) )
	                    case 04:
	                            if (gSmbiosBoardProtocol->ProcessorDmiEditSupport) {
	                                if (Offset == 0x20) {               // Serial Number
                                        NvramType4.StringSet[3] = (char*)DmiData;
	                                    NvramType4.Flag |= BIT3;
	                                }
	                                else if (Offset == 0x21) {          // Asset Tag
                                        NvramType4.StringSet[4] = (char*)DmiData;
	                                    NvramType4.Flag |= BIT4;
	                                }
	                                else if (Offset == 0x22) {          // Part Number
                                        NvramType4.StringSet[5] = (char*)DmiData;
	                                    NvramType4.Flag |= BIT5;
	                                }
	                            }
                                UpdateFlag = TRUE;
	                            break;
#endif                                      // PROCESSOR_DMIEDIT_SUPPORT
#if OEM_STRING_INFO
	                    case 11:
	                            if (gSmbiosBoardProtocol->OemStringInfoSupport) {
                                    NvramType11.StringSet[Offset] = (char*)DmiData;
	                                NvramType11.Flag |= (1 << Offset);
	                            }
                                UpdateFlag = TRUE;
	                            break;
#endif                                      // OEM_STRING_INFO
#if SYSTEM_CONFIG_OPTION_INFO
	                    case 12:
	                            if (gSmbiosBoardProtocol->SystemConfigOptionInfoSupport) {
                                    NvramType12.StringSet[Offset] = (char*)DmiData;
	                                NvramType12.Flag |= (1 << Offset);
	                            }
                                UpdateFlag = TRUE;
	                            break;
#endif                                      // SYSTEM_CONFIG_OPTION_INFO
#if PORTABLE_BATTERY_INFO
	                    case 22:
                                // Save handle number in Type22Handle array for each Type 22 structure
                                for (i = 0; i < gSmbiosBoardProtocol->NumberOfBatteries; i++) {
                                    if (Type22Handle[i] == 0) {
                                        Type22Handle[i] = Handle;
                                        break;
                                    }
                                    if (Handle == Type22Handle[i]) break;
                                }
                                if (i < gSmbiosBoardProtocol->NumberOfBatteries) {
                                    NvramType22[i].Handle = Handle;
                                    if (Offset == 0x04) {               // Location
                                        NvramType22[i].StringSet[0] = (char*)DmiData;
                                        NvramType22[i].Flag |= 0x00000001;
                                    }
                                    else if (Offset == 0x05) {          // Manufacturer
                                        NvramType22[i].StringSet[1] = (char*)DmiData;
                                        NvramType22[i].Flag |= 0x00000002;
                                    }
                                    else if (Offset == 0x06) {          // Manufacturer Date
                                        NvramType22[i].StringSet[2] = (char*)DmiData;
                                        NvramType22[i].Flag |= 0x00000004;
                                    }
                                    else if (Offset == 0x07) {          // Serial Number
                                        NvramType22[i].StringSet[3] = (char*)DmiData;
                                        NvramType22[i].Flag |= 0x00000008;
                                    }
                                    else if (Offset == 0x08) {          // Device Name
                                        NvramType22[i].StringSet[4] = (char*)DmiData;
                                        NvramType22[i].Flag |= 0x00000010;
                                    }
                                    else if (Offset == 0x09) {          // Device Chemistry
                                        NvramType22[i].DeviceChemistry = *(UINT8*)DmiData;
                                        NvramType22[i].Flag |= 0x00010000;
                                    }
                                    else if (Offset == 0x0a) {          // Design Capacity
                                        NvramType22[i].DesignCapacity = *(UINT16*)DmiData;
                                        NvramType22[i].Flag |= 0x00020000;
                                    }
                                    else if (Offset == 0x0c) {          // Design Voltage
                                        NvramType22[i].DesignVoltage = *(UINT16*)DmiData;
                                        NvramType22[i].Flag |= 0x00040000;
                                    }
                                    else if (Offset == 0x0e) {          // SBDS Version Number
                                        NvramType22[i].StringSet[5] = (char*)DmiData;
                                        NvramType22[i].Flag |= 0x00000020;
                                    }
                                    else if (Offset == 0x0f) {          // Maximum Error in Battery Data
                                        NvramType22[i].MaxErrorInBatteryData = *(UINT8*)DmiData;
                                        NvramType22[i].Flag |= 0x00080000;
                                    }
                                    else if (Offset == 0x10) {          // SBDS Serial Number
                                        NvramType22[i].SbdsSerialNumber = *(UINT16*)DmiData;
                                        NvramType22[i].Flag |= 0x00100000;
                                    }
                                    else if (Offset == 0x12) {          // SBDS Manufacturer Date
                                        NvramType22[i].SbdsManufacturerDate = *(UINT16*)DmiData;
                                        NvramType22[i].Flag |= 0x00200000;
                                    }
                                    else if (Offset == 0x14) {          // SBDS Device Chemistry
                                        NvramType22[i].StringSet[6] = (char*)DmiData;
                                        NvramType22[i].Flag |= 0x00000040;
                                    }
                                    else if (Offset == 0x15) {          // Design Capacity Multiplier
                                        NvramType22[i].DesignCapacityMultiplier = *(UINT8*)DmiData;
                                        NvramType22[i].Flag |= 0x00400000;
                                    }
                                    else if (Offset == 0x16) {          // OEM-specific
                                        NvramType22[i].OemSpecific = *(UINT32*)DmiData;
                                        NvramType22[i].Flag |= 0x00800000;
                                    }
                                }
                                UpdateFlag = TRUE;
                                break;
#endif                                      // PORTABLE_BATTERY_INFO
#if SYSTEM_POWER_SUPPLY_INFO
	                    case 39:
                                // Save handle number in Type39Handle array for each Type 39 structure
                                for (i = 0; i < NUMBER_OF_POWER_SUPPLY; i++) {
                                    if (Type39Handle[i] == 0) {
                                        Type39Handle[i] = Handle;
                                        break;
                                    }
                                    if (Handle == Type39Handle[i]) break;
                                }
                                if (i < NUMBER_OF_POWER_SUPPLY) {
                                    NvramType39[i].Handle = Handle;
	                                if (Offset == 0x04) {               // Power Unit Group
	                                    NvramType39[i].PwrUnitGroup = *(UINT8*)DmiData;
	                                    NvramType39[i].Flag |= 0x00010000;
	                                }
	                                else if (Offset == 0x05) {          // Location
                                        NvramType39[i].StringSet[0] = (char*)DmiData;
	                                    NvramType39[i].Flag |= 0x00000001;
	                                }
	                                else if (Offset == 0x06) {          // Device Name
                                        NvramType39[i].StringSet[1] = (char*)DmiData;
	                                    NvramType39[i].Flag |= 0x00000002;
	                                }
	                                else if (Offset == 0x07) {          // Manufacturer
                                        NvramType39[i].StringSet[2] = (char*)DmiData;
	                                    NvramType39[i].Flag |= 0x00000004;
	                                }
	                                else if (Offset == 0x08) {          // Serial Number
                                        NvramType39[i].StringSet[3] = (char*)DmiData;
	                                    NvramType39[i].Flag |= 0x00000008;
	                                }
	                                else if (Offset == 0x09) {          // Asset Tag Number
                                        NvramType39[i].StringSet[4] = (char*)DmiData;
	                                    NvramType39[i].Flag |= 0x00000010;
	                                }
	                                else if (Offset == 0x0a) {          // Model Part Number
                                        NvramType39[i].StringSet[5] = (char*)DmiData;
	                                    NvramType39[i].Flag |= 0x00000020;
	                                }
	                                else if (Offset == 0x0b) {          // Revision Level
                                        NvramType39[i].StringSet[6] = (char*)DmiData;
	                                    NvramType39[i].Flag |= 0x00000040;
	                                }
	                                else if (Offset == 0x0c) {          // Max Power Capacity
	                                    NvramType39[i].MaxPwrCapacity = *(UINT16*)DmiData;
	                                    NvramType39[i].Flag |= 0x00020000;
	                                }
	                                else if (Offset == 0x0e) {          // Power Supply Characteristics
	                                    NvramType39[i].PwrSupplyChar = *(UINT16*)DmiData;
	                                    NvramType39[i].Flag |= 0x00040000;
	                                }
	                                else if (Offset == 0x10) {          // Input Voltage Proble Handle
	                                    NvramType39[i].InputVoltageProbeHandle = *(UINT16*)DmiData;
	                                    NvramType39[i].Flag |= 0x00080000;
	                                }
	                                else if (Offset == 0x12) {          // Cooling Device Handle
	                                    NvramType39[i].CoolingDevHandle = *(UINT16*)DmiData;
	                                    NvramType39[i].Flag |= 0x00100000;
	                                }
	                                else if (Offset == 0x14) {          // Input Current Probe Handle
	                                    NvramType39[i].InputCurrentProbeHandle = *(UINT16*)DmiData;
	                                    NvramType39[i].Flag |= 0x00200000;
	                                }
	                            }
                                UpdateFlag = TRUE;
#endif                                      // SYSTEM_POWER_SUPPLY_INFO
					}
                }
            }
        }
    }
}
#endif                                      // SMBIOS_DMIEDIT_DATA_LOC

    // Update Smbios table if any structure has been changed
    if (UpdateFlag) {
        TRACE((-1, "Updating structures\n"));
        pBS->AllocatePool(EfiBootServicesData, BufferSize, (void**)&TempBuffer);
        MemSet(TempBuffer, BufferSize, 0);
        TempBufferPtr = TempBuffer;
    	BufferPtr = SmbiosDataTable;
        do {
            switch (((SMBIOS_STRUCTURE_HEADER*)BufferPtr)->Type) {
                case 0  :   {
                                TRACE((-1, "Updating Type 0 structure\n"));
                                UpdateStructuresWithNvramType0(&NvramType0, BufferPtr, TempBufferPtr);
                                break;
                            }
                case 1  :   {
                                TRACE((-1, "Updating Type 1 structure\n"));
                                UpdateStructuresWithNvramType1(&NvramType1, BufferPtr, TempBufferPtr);
                                break;
                            }
                #if BASE_BOARD_INFO
                case 2  :   {
                                TRACE((-1, "Updating Type 2 structure\n"));
                                if (gSmbiosBoardProtocol->BaseBoardInfoSupport) {
                                    // Find the NvramType2 entry for the structure by matching the handle number
                                    for (i = 0; i < NUMBER_OF_BASEBOARDS; i++) {
                                        if (((SMBIOS_STRUCTURE_HEADER*)BufferPtr)->Handle == NvramType2[i].Handle) break;
                                    }
                                    // Update the structure with the data in NvramType2 array if found,
                                    // or just copy the original structure if not found
                                    if (i < NUMBER_OF_BASEBOARDS) {
                                        UpdateStructuresWithNvramType2(&NvramType2[i], BufferPtr, TempBufferPtr);
                                    }
                                    else {
                                        UpdateStructuresWithNvramType2(NULL, BufferPtr, TempBufferPtr);
                                    }
                                }
                                break;
                            }
                #endif										// BASE_BOARD_INFO
                #if SYS_CHASSIS_INFO
                case 3  :   {
                                TRACE((-1, "Updating Type 3 structure\n"));
                                if (gSmbiosBoardProtocol->SysChassisInfoSupport) {
                                    StrTableInstance = GetInstanceByTypeHandle(3, ((SMBIOS_STRUCTURE_HEADER*)BufferPtr)->Handle);

                                    // Find the NvramType3 entry for the structure by matching the handle number
                                    for (i = 0; i < NUMBER_OF_SYSTEM_CHASSIS; i++) {
                                        if (((SMBIOS_STRUCTURE_HEADER*)BufferPtr)->Handle == NvramType3[i].Handle) break;
                                    }
                                    // Update the structure with the data in NvramType3 array if found,
                                    // or just copy the original structure if not found
                                    if (i < NUMBER_OF_SYSTEM_CHASSIS) {
                                        UpdateStructuresWithNvramType3(&NvramType3[i], BufferPtr, TempBufferPtr, StrTableInstance);
                                    }
                                    else {
                                        UpdateStructuresWithNvramType3(NULL, BufferPtr, TempBufferPtr, StrTableInstance);
                                    }
                                }
                                break;
                            }
                #endif										// SYS_CHASSIS_INFO
                #if ( defined(PROCESSOR_DMIEDIT_SUPPORT) && (PROCESSOR_DMIEDIT_SUPPORT == 1) )
                case 4  :   {
                                TRACE((-1, "Updating Type 4 structure\n"));
                                if (gSmbiosBoardProtocol->ProcessorDmiEditSupport) {
                                    UpdateStructuresWithNvramType4(&NvramType4, BufferPtr, TempBufferPtr);
                                }
                                break;
                            }
                #endif										// PROCESSOR_DMIEDIT_SUPPORT
                #if OEM_STRING_INFO
                case 11 :   {
                                TRACE((-1, "Updating Type 11 structure\n"));
                                if (gSmbiosBoardProtocol->OemStringInfoSupport) {
                                    UpdateStructuresWithNvramType11(&NvramType11, BufferPtr, TempBufferPtr);
                                }
                                break;
                            }
                #endif										// OEM_STRING_INFO
                #if SYSTEM_CONFIG_OPTION_INFO
                case 12 :   {
                                TRACE((-1, "Updating Type 12 structure\n"));
                                if (gSmbiosBoardProtocol->SystemConfigOptionInfoSupport) {
                                    UpdateStructuresWithNvramType12(&NvramType12, BufferPtr, TempBufferPtr);
                                }
                                break;
                            }
                #endif										// SYSTEM_CONFIG_OPTION_INFO
                #if PORTABLE_BATTERY_INFO
                case 22:    {
                                TRACE((-1, "Updating Type 22 structure\n"));
                                // Find the NvramType22 entry for the structure by matching the handle number
                                for (i = 0; i < gSmbiosBoardProtocol->NumberOfBatteries; i++) {
                                    if (((SMBIOS_STRUCTURE_HEADER*)BufferPtr)->Handle == NvramType22[i].Handle) break;
                                }
                                // Update the structure with the data in NvramType22 array if found,
                                // or just copy the original structure if not found
                                if (i < gSmbiosBoardProtocol->NumberOfBatteries) {
                                    UpdateStructuresWithNvramType22(&NvramType22[i], BufferPtr, TempBufferPtr);
                                }
                                else {
                                    UpdateStructuresWithNvramType22(NULL, BufferPtr, TempBufferPtr);
                                }
                                break;
                            }
                #endif										// PORTABLE_BATTERY_INFO
                #if SYSTEM_POWER_SUPPLY_INFO
                case 39:    {
                                TRACE((-1, "Updating Type 39 structure\n"));
                                // Find the NvramType39 entry for the structure by matching the handle number
                                for (i = 0; i < NUMBER_OF_POWER_SUPPLY; i++) {
                                    if (((SMBIOS_STRUCTURE_HEADER*)BufferPtr)->Handle == NvramType39[i].Handle) break;
                                }
                                // Update the structure with the data in NvramType39 array if found,
                                // or just copy the original structure if not found
                                if (i < NUMBER_OF_POWER_SUPPLY) {
                                    UpdateStructuresWithNvramType39(&NvramType39[i], BufferPtr, TempBufferPtr);
                                }
                                else {
                                    UpdateStructuresWithNvramType39(NULL, BufferPtr, TempBufferPtr);
                                }
                                break;
                            }
                #endif										// SYSTEM_POWER_SUPPLY_INFO
                default :   {
                                StructureSize = GetStructureLength(BufferPtr);
                                MemCpy(TempBufferPtr, BufferPtr, StructureSize);
                            }
            }
            BufferPtr += GetStructureLength(BufferPtr);
            TempBufferPtr += GetStructureLength(TempBufferPtr);
        } while (((SMBIOS_STRUCTURE_HEADER*)BufferPtr)->Type != 127);

        // Copy Type 127
        StructureSize = GetStructureLength(BufferPtr);
        MemCpy(TempBufferPtr, BufferPtr, StructureSize);

        TRACE((-1, "Replace all DMI data with TempBuffer\n"));
        // Replace all DMI data with TempBuffer
        MemCpy(Buffer, TempBuffer, BufferSize);

        pBS->FreePool(TempBuffer);
    }

#if !defined(SMBIOS_DMIEDIT_DATA_LOC) || SMBIOS_DMIEDIT_DATA_LOC != 2
    pBS->FreePool(FlashData);
#endif										// SMBIOS_DMIEDIT_DATA_LOC
    Status = EFI_SUCCESS;

#if !defined(SMBIOS_DMIEDIT_DATA_LOC) || SMBIOS_DMIEDIT_DATA_LOC != 2
Function_Exit:
#endif										// SMBIOS_DMIEDIT_DATA_LOC
#if (TYPE2_STRUCTURE == 1)
    pBS->FreePool(Type2Handle);
    pBS->FreePool(NvramType2);
#endif										// TYPE2_STRUCTURE
#if (TYPE3_STRUCTURE == 1)
    pBS->FreePool(Type3Handle);
    pBS->FreePool(NvramType3);
#endif										// TYPE3_STRUCTURE
    pBS->FreePool(Type22Handle);
    pBS->FreePool(NvramType22);
    pBS->FreePool(Type39Handle);
    pBS->FreePool(NvramType39);

    TRACE((-1, ":::  SMBIOS - Exit UpdateStructuresWithNvramData. Status = %r  :::\n", Status));

    return Status;
}
#endif

#if UPDATE_BASEBOARD_TYPE2
//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   DynamicBaseBoardData
//
// Description: Updates base board structure (Type 2) in input Buffer with
//              dynamically detected data.
//
// Input:       UINT8       *Buffer
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
DynamicUpdateBaseBoardData(
    IN UINT8        *Buffer
)
{
    EFI_STATUS      Status;
    UINT32          Attributes = EFI_VARIABLE_BOOTSERVICE_ACCESS;
    UINT8           *SrcBuffer;
    UINT8           *StructureFoundPtr;
    UINT8           *SmbiosVariableBuffer;
    UINTN           SmbiosVariableSize;
    UINT16          StructureHandle;
    UINT8           *TempStructure2;
    UINTN           TempStructure2Size;

    TRACE((-1, "***  SMBIOS - DynamicUpdateBaseBoardData  ***\n"));

    SmbiosVariableSize = sizeof(BASE_BOARD_DATA);

    pBS->AllocatePool(
                EfiBootServicesData,
                SmbiosVariableSize,
                &SmbiosVariableBuffer);

    Status = pRS->GetVariable(
                        SmbiosBaseBoardVar,
                        &gEfiSmbiosDynamicData,
                        &Attributes,
                        &SmbiosVariableSize,
                        SmbiosVariableBuffer);
    if (EFI_ERROR(Status) && Status != EFI_NOT_FOUND) {
        pBS->FreePool(SmbiosVariableBuffer);

        TRACE((-1, "Failed to get SmbiosBaseBoardVar\n"));
        return Status;
    }

    if (Status != EFI_NOT_FOUND) {
        SrcBuffer = Buffer;

        //
        // Search for Type 2 (Base Board) structure pointer
        //
        if (FindStructureType(&SrcBuffer, &StructureFoundPtr, 2, 1)) {

            TempStructure2Size = (UINTN)(sizeof(SMBIOS_BASE_BOARD_INFO) + 6*65 + 1);
            pBS->AllocatePool(EfiBootServicesData,
                             TempStructure2Size,
                             &TempStructure2);

            StructureHandle = ((SMBIOS_STRUCTURE_HEADER*)StructureFoundPtr)->Handle;
            MemCpy(TempStructure2, StructureFoundPtr, GetStructureLength(StructureFoundPtr));

#if UPDATE_BOARD_MANUFACTURER
            //
            // Update Board Manufacturer Name
            //
            ReplaceString(TempStructure2, 1, (UINT8*)((BASE_BOARD_DATA*)SmbiosVariableBuffer)->BoardManufacturer);
#endif										// UPDATE_BOARD_MANUFACTURER
#if UPDATE_BOARD_NAME
            //
            // Update Board Name String corresponding to Board ID.
            //
            ReplaceString(TempStructure2, 2, (UINT8*)((BASE_BOARD_DATA*)SmbiosVariableBuffer)->BoardName);
#endif										// UPDATE_BOARD_NAME
            //
            // Add Structure to the table
            //
            WriteStructureByHandle(StructureHandle, TempStructure2, GetStructureLength(TempStructure2));

            pBS->FreePool(TempStructure2);
        }
    }

    pBS->FreePool(SmbiosVariableBuffer);

    TRACE((-1, ":::  SMBIOS - Exit DynamicUpdateBaseBoardData  :::\n"));

    return EFI_SUCCESS;
}
#endif										// UPDATE_BASEBOARD_TYPE2

#if UPDATE_SYSTEM_CHASSIS_TYPE3
//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   DynamicUpdateChassisData
//
// Description: Updates Chassis structure (Type 3) in input Buffer with
//              dynamically detected data.
//
// Input:       UINT8       *Buffer
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
DynamicUpdateChassisData(
    IN UINT8        *Buffer
)
{
    EFI_STATUS      Status;
    UINT32          Attributes = EFI_VARIABLE_BOOTSERVICE_ACCESS;
    UINT8           *SrcBuffer;
    UINT8           *StructureFoundPtr;
    UINT8           *SmbiosVariableBuffer;
    UINTN           SmbiosVariableSize;

    TRACE((-1, "***  SMBIOS - DynamicUpdateChassisData  ***\n"));

    SmbiosVariableSize = sizeof(CHASSIS_DATA);

    pBS->AllocatePool(
                EfiBootServicesData,
                SmbiosVariableSize,
                &SmbiosVariableBuffer);

    Status = pRS->GetVariable(
                        SmbiosChassisVar,
                        &gEfiSmbiosDynamicData,
                        &Attributes,
                        &SmbiosVariableSize,
                        SmbiosVariableBuffer);
    if (EFI_ERROR(Status) && Status != EFI_NOT_FOUND) {
        pBS->FreePool(SmbiosVariableBuffer);

        TRACE((-1, "Failed to get SmbiosChassisVar\n"));
        return Status;
    }

    if (Status != EFI_NOT_FOUND) {
        SrcBuffer = Buffer;
        if (FindStructureType(&SrcBuffer, &StructureFoundPtr, 3, 1)) {
            ((SMBIOS_SYSTEM_ENCLOSURE_INFO*)StructureFoundPtr)->Type = ((CHASSIS_DATA*)SmbiosVariableBuffer)->Type;
        }
    }

    pBS->FreePool(SmbiosVariableBuffer);

    TRACE((-1, ":::  SMBIOS - Exit DynamicUpdateChassisData  :::\n"));

    return EFI_SUCCESS;
}
#endif										// UPDATE_SYSTEM_CHASSIS_TYPE3

#if UPDATE_CPU_TYPE4
//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   DynamicUpdateCpuData
//
// Description: Updates CPU structures (Type 4 & 7) in input Buffer with
//              dynamically detected data.
//
// Input:       IN UINT8    *Buffer
//
// Output:      EFI_STATUS
//
// Modified:
//
// Referrals:
//
// Notes:   If SMBIOS_CPU_INFO_PROTOCOL is not found, this function tries to
//          use the "CPU_DATA" variable (backward compatibility). Otherwise
//          CPU dynamic information is not available.
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS
DynamicUpdateCpuData(
    IN UINT8        *Buffer
)
{
    EFI_STATUS                  Status;
    UINT8                       UseVariable = FALSE;
    UINT8                       i;
    UINT8                       *SrcBuffer =  Buffer;
    UINT8                       *StructureFoundPtr;
    UINT8                       *SmbiosVariableBuffer;
    UINT32                      Attributes = EFI_VARIABLE_BOOTSERVICE_ACCESS;
    UINTN                       Size;
    EFI_GUID                    gSmbiosCpuInfoGuid = AMI_SMBIOS_CPU_INFO_PROTOCOL_GUID;
    SMBIOS_CPU_INFO_PROTOCOL    *SmbiosCpuInfo;
    SMBIOS_PROCESSOR_INFO       *CurCpu;
    SMBIOS_CACHE_INFO           *CurCache;
    SINGLE_CPU_DATA             *DynamicData;

    TRACE((-1, "***  SMBIOS - DynamicUpdateCpuData  ***\n"));

    Status = pBS->LocateProtocol(&gSmbiosCpuInfoGuid, NULL, (void**)&SmbiosCpuInfo);
    if (EFI_ERROR(Status)) {
        UseVariable = TRUE,
        Size = sizeof(CPU_DYNAMIC_DATA);
        pBS->AllocatePool(
                EfiBootServicesData,
                Size,
                (void**)&SmbiosVariableBuffer);
        Status = pRS->GetVariable(
                            SmbiosCpuVar,
                            &gEfiSmbiosDynamicData,
                            &Attributes,
                            &Size,
                            SmbiosVariableBuffer);
        if (EFI_ERROR(Status)) {
            pBS->FreePool(SmbiosVariableBuffer);

            TRACE((-1, "Failed to get SmbiosCpuVar\n"));
            return Status;
        }
    }

    for (i = 0; i < gSmbiosBoardProtocol->NumberOfCPU; i++) {
      if (FindStructureType(&SrcBuffer, &StructureFoundPtr, 4, 1)) {
        Size = GetStructureLength(StructureFoundPtr);
        Status = pBS->AllocatePool(
                                EfiBootServicesData,
                                Size + 1024,            // 1K additional buffer
                                (void**)&CurCpu);

        if (Status == EFI_SUCCESS) {
          UINT16    *L3HandlePtr;

          MemCpy(CurCpu, StructureFoundPtr, Size);
          if (UseVariable)
            DynamicData =
              &((CPU_DYNAMIC_DATA*)SmbiosVariableBuffer)->CpuData[i];
          else
            DynamicData = &SmbiosCpuInfo->CpuData[i];

          CurCpu->Family = DynamicData->CpuData.Family;
          CurCpu->ProcessorID_1 = DynamicData->CpuData.ProcessorID_1;
          CurCpu->ProcessorID_2 = DynamicData->CpuData.ProcessorID_2;
          CurCpu->Voltage = DynamicData->CpuData.Voltage | BIT07;
          CurCpu->ExtClockFreq = DynamicData->CpuData.ExtClockFreq;
          CurCpu->MaxSpeed = DynamicData->CpuData.MaxSpeed;
          CurCpu->CurrentSpeed = DynamicData->CpuData.CurrentSpeed;
          CurCpu->Status = DynamicData->CpuData.Status;
          CurCpu->Upgrade = DynamicData->CpuData.Upgrade;
          CurCpu->CoreCount = DynamicData->CpuData.CoreCount;
          CurCpu->CoreEnabled = DynamicData->CpuData.CoreEnabled;
          CurCpu->ThreadCount = DynamicData->CpuData.ThreadCount;
          CurCpu->Family2 = DynamicData->CpuData.Family2;

          L3HandlePtr = &CurCpu->L3CacheHandle;

          ReplaceString((UINT8*)CurCpu, 2, DynamicData->CpuData.Manufacturer);
          ReplaceString((UINT8*)CurCpu, 3, DynamicData->CpuData.Version);

          if (DynamicData->CpuData.Status & 0x040) {
            // L1 Cache
            if (FindStructureType(&SrcBuffer, &StructureFoundPtr, 7, 1)) {
              CurCache = (SMBIOS_CACHE_INFO*)StructureFoundPtr;
              CurCache->CacheConfig = DynamicData->L1Cache.CacheConfig;
              CurCache->MaxCacheSize = DynamicData->L1Cache.MaxCacheSize;
              CurCache->InstalledSize = DynamicData->L1Cache.InstalledSize;
              CurCache->SupportSRAM = DynamicData->L1Cache.SupportSRAM;
              CurCache->CurrentSRAM = DynamicData->L1Cache.CurrentSRAM;
              CurCache->CacheSpeed = DynamicData->L1Cache.CacheSpeed;
              CurCache->ErrorCorrectionType =
                DynamicData->L1Cache.ErrorCorrectionType;
              CurCache->SystemCacheType = DynamicData->L1Cache.SystemCacheType;
              CurCache->Associativity = DynamicData->L1Cache.Associativity;

              // L2 Cache
              if (FindStructureType(&SrcBuffer, &StructureFoundPtr, 7, 1)) {
                CurCache = (SMBIOS_CACHE_INFO*)StructureFoundPtr;
                CurCache->CacheConfig = DynamicData->L2Cache.CacheConfig;
                CurCache->MaxCacheSize = DynamicData->L2Cache.MaxCacheSize;
                CurCache->InstalledSize = DynamicData->L2Cache.InstalledSize;
                CurCache->SupportSRAM = DynamicData->L2Cache.SupportSRAM;
                CurCache->CurrentSRAM = DynamicData->L2Cache.CurrentSRAM;
                CurCache->CacheSpeed = DynamicData->L2Cache.CacheSpeed;
                CurCache->ErrorCorrectionType =
                  DynamicData->L2Cache.ErrorCorrectionType;
                CurCache->SystemCacheType = DynamicData->L2Cache.SystemCacheType;
                CurCache->Associativity = DynamicData->L2Cache.Associativity;

                // L3 Cache
                if (FindStructureType(&SrcBuffer, &StructureFoundPtr, 7, 1)) {
                  CurCache = (SMBIOS_CACHE_INFO*)StructureFoundPtr;

                  // Hide structure if L3 cache size is 0
                  if (DynamicData->L3Cache.InstalledSize == 0) {
                    CurCache->StructureType.Type = 126;
                    *L3HandlePtr = 0xffff;
                  }
                  else {
                    CurCache->CacheConfig = DynamicData->L3Cache.CacheConfig;
                    CurCache->MaxCacheSize = DynamicData->L3Cache.MaxCacheSize;
                    CurCache->InstalledSize = DynamicData->L3Cache.InstalledSize;
                    CurCache->SupportSRAM = DynamicData->L3Cache.SupportSRAM;
                    CurCache->CurrentSRAM = DynamicData->L3Cache.CurrentSRAM;
                    CurCache->CacheSpeed = DynamicData->L3Cache.CacheSpeed;
                    CurCache->ErrorCorrectionType =
                      DynamicData->L3Cache.ErrorCorrectionType;
                    CurCache->SystemCacheType =
                      DynamicData->L3Cache.SystemCacheType;
                    CurCache->Associativity = DynamicData->L3Cache.Associativity;
                  }
                }
              }
            }
          }

          // L1 Cache
          else if (FindStructureType(&SrcBuffer, &StructureFoundPtr, 7, 1)) {
            CurCache = (SMBIOS_CACHE_INFO*)StructureFoundPtr;
            CurCache->StructureType.Type = 126;

            // L2 Cache
            if (FindStructureType(&SrcBuffer, &StructureFoundPtr, 7, 1)) {
              CurCache = (SMBIOS_CACHE_INFO*)StructureFoundPtr;
              CurCache->StructureType.Type = 126;

              // L3 Cache
              if (FindStructureType(&SrcBuffer, &StructureFoundPtr, 7, 1)) {
                CurCache = (SMBIOS_CACHE_INFO*)StructureFoundPtr;
                CurCache->StructureType.Type = 126;
              }
            }
          }

          WriteStructureByHandle(((SMBIOS_STRUCTURE_HEADER*)CurCpu)->Handle,
                                 (UINT8*)CurCpu,
                                 GetStructureLength((UINT8*)CurCpu)
                                );

          pBS->FreePool(CurCpu);
        }
      }
    }

    if (UseVariable)
        pBS->FreePool(SmbiosVariableBuffer);

    TRACE((-1, ":::  SMBIOS - Exit DynamicUpdateCpuData  :::\n"));

    return EFI_SUCCESS;
}
#endif										// UPDATE_CPU_TYPE4

#if UPDATE_SLOT_TYPE9
//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   DynamicUpdateSlotsData
//
// Description: Updates System Slot structure (Type 9) in input Buffer with
//              dynamically detected data.
//
// Input:       IN UINT8    *Buffer
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
DynamicUpdateSlotsData(
    IN UINT8        *Buffer
)
{
    EFI_STATUS      Status;
    UINT32          Attributes = EFI_VARIABLE_BOOTSERVICE_ACCESS;
    UINT8           *SrcBuffer;
    UINT8           *StructureFoundPtr;
    UINT8           *SmbiosVariableBuffer;
    UINTN           SmbiosVariableSize;
    UINT8           i;

    TRACE((-1, "***  SMBIOS - DynamicUpdateSlotsData  ***\n"));

    SmbiosVariableSize = sizeof(SYSTEM_SLOT_DYNAMIC_DATA);
    pBS->AllocatePool(EfiBootServicesData, SmbiosVariableSize, (void**)&SmbiosVariableBuffer);
    Status = pRS->GetVariable(SmbiosSlotsVar, &gEfiSmbiosDynamicData,
                             &Attributes, &SmbiosVariableSize, SmbiosVariableBuffer);
    if (EFI_ERROR(Status) && Status != EFI_NOT_FOUND) {
        pBS->FreePool(SmbiosVariableBuffer);

        TRACE((-1, "Failed to get SmbiosSlotsVar\n"));
        return Status;
    }

    if (Status != EFI_NOT_FOUND) {
        SrcBuffer = Buffer;
        for (i = 0; i < gSmbiosBoardProtocol->NumberOfSystemSlots; i++) {
            if (FindStructureType(&SrcBuffer, &StructureFoundPtr, 9, 1)) {
                ((SMBIOS_SYSTEM_SLOTS_INFO*)StructureFoundPtr)->CurrentUsage = ((SYSTEM_SLOT_DYNAMIC_DATA*)SmbiosVariableBuffer)->CurrentUsage[i];
                ((SMBIOS_SYSTEM_SLOTS_INFO*)StructureFoundPtr)->BusNumber = ((SYSTEM_SLOT_DYNAMIC_DATA*)SmbiosVariableBuffer)->BusNumber[i];
            }
        }
    }
    pBS->FreePool(SmbiosVariableBuffer);

    TRACE((-1, ":::  SMBIOS - Exit DynamicUpdateSlotsData  :::\n"));

    return EFI_SUCCESS;
}
#endif										// UPDATE_SLOT_TYPE9

#if UPDATE_ONBOARD_DEV_TYPE10
//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   DynamicUpdateOnboardDevData
//
// Description: Updates On Board Devices Information structure (Type 10) in
//              input Buffer with dynamically detected data.
//
// Input:       IN UINT8    *Buffer
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
DynamicUpdateOnboardDevData(
    IN UINT8        *Buffer
)
{
    EFI_STATUS      Status;
    UINT32          Attributes = EFI_VARIABLE_BOOTSERVICE_ACCESS;
    UINT8           *SrcBuffer;
    UINT8           *StructureFoundPtr;
    UINT8           *SmbiosVariableBuffer;
    UINTN           SmbiosVariableSize;
    UINT8           i;

    TRACE((-1, "***  SMBIOS - DynamicUpdateOnboardDevData  ***\n"));

    SmbiosVariableSize = sizeof(ONBOARD_DEV_DYNAMIC_DATA);
    pBS->AllocatePool(EfiBootServicesData, SmbiosVariableSize, (void**)&SmbiosVariableBuffer);
    Status = pRS->GetVariable(SmbiosOnBoardVar, &gEfiSmbiosDynamicData,
                             &Attributes, &SmbiosVariableSize, SmbiosVariableBuffer);
    if (EFI_ERROR(Status) && Status != EFI_NOT_FOUND) {
        pBS->FreePool(SmbiosVariableBuffer);

        TRACE((-1, "Failed to get SmbiosOnBoardVar\n"));
        return Status;
    }

    if (Status != EFI_NOT_FOUND) {
        SrcBuffer = Buffer;
        if (FindStructureType(&SrcBuffer, &StructureFoundPtr, 10, 1)) {
            StructureFoundPtr += 4;
            for (i = 0; i < gSmbiosBoardProtocol->NumberOfOnBoardDevices; i++) {
                ((SINGLE_DEV_INFO*)StructureFoundPtr)->DeviceType &= 0x7f;
                ((SINGLE_DEV_INFO*)StructureFoundPtr)->DeviceType |= ((ONBOARD_DEV_DYNAMIC_DATA*)SmbiosVariableBuffer)->OnBoardDev[i];

                StructureFoundPtr += 2;
            }
        }
    }

    pBS->FreePool(SmbiosVariableBuffer);

    TRACE((-1, ":::  SMBIOS - Exit DynamicUpdateOnboardDevData  :::\n"));

    return EFI_SUCCESS;
}
#endif										// UPDATE_ONBOARD_DEV_TYPE10

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   UpdateSerialNumber
//
// Description: Update Type 17 Serial Number field for the input memory slot
//              with data obtained from the SPD.
//
// Input:       IN UINT8                        *StructureBuffer
//              IN EFI_SMBUS_DEVICE_ADDRESS     SpdSmBusAddr
//
// Output:      EFI_STATUS
//
// Modified:    Type 17 Serial Number field
//
// Referrals:
//
// Notes:
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS
UpdateSerialNumber (
    IN UINT8                    *StructBuffer,
    IN EFI_SMBUS_DEVICE_ADDRESS SpdSmBusAddr,
    IN MEM_SPD_DATA             *SpdData
)
{
    EFI_STATUS              Status;
    UINTN                   i;
    UINT8                   Data8;
    UINTN                   SpdOffset;
    UINT8                   Ascii;

    StructBuffer += ((SMBIOS_STRUCTURE_HEADER*)StructBuffer)->Length;
    StructBuffer += GetStringOffset(StructBuffer, 4);

    if (MemType == 0) return EFI_UNSUPPORTED;       // Not supported
    if (MemType == 1) SpdOffset = 0x5f;
    if (MemType == 2) SpdOffset = 122;
    if (MemType == 3) SpdOffset = 325;

    for (i = 0; i < 4; i++) {
        if (SpdData) {
            if (SpdOffset == 95) {                  // 0x5f
                Data8 = SpdData->Byte95To98[95 + i - 95];
            }
            else if (SpdOffset == 122){
                Data8 = SpdData->Byte122To125[122 + i - 122];
            }
            else {
                Data8 = SpdData->Byte325To328[325 + i - 325];
            }
        }
        else {
            Status = gSmbiosBoardProtocol->GetSpdByte(SpdSmBusAddr, SpdOffset + i, &Data8);
            if (EFI_ERROR(Status)) return Status;
        }

        if (*StructBuffer == 0) return EFI_BUFFER_TOO_SMALL;    // Truncate if string is too long
        Ascii = (Data8 >> 4);
        if (Ascii > 9) *StructBuffer++ = Ascii - 10 + 0x41;
        else *StructBuffer++ = Ascii + 0x30;
        if (*StructBuffer == 0) return EFI_BUFFER_TOO_SMALL;    // Truncate if string is too long
        Ascii = Data8 & 15;
        if (Ascii > 9) *StructBuffer++ = Ascii - 10 + 0x41;
        else *StructBuffer++ = Ascii + 0x30;
    }

    while (*StructBuffer != 0) *StructBuffer++ = 0x20;

    return EFI_SUCCESS;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   FilterCharacter
//
// Description: If input character is in the range of 0x20 to 0x7e (readable
//              character), returns the input character value unchanged.
//              Otherwise returns single space character.
//
// Input:       IN CHAR8    _char
//
// Output:      CHAR8
//
// Modified:
//
// Referrals:
//
// Notes:
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
CHAR8
FilterCharacter (
    IN CHAR8    _char
)
{
    if( (_char >= 0x20 && _char <= 0x7E) ){
        return _char;
    }

    return ' ';
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   UpdatePartNumber
//
// Description: Update Type 17 Part Number field for the input memory slot
//              with data obtained from the SPD.
//
// Input:       IN UINT8                        *StructBuffer
//              IN EFI_SMBUS_DEVICE_ADDRESS     SpdSmBusAddr
//
// Output:      EFI_STATUS
//
// Modified:    Type 17 Part Number field
//
// Referrals:
//
// Notes:
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS
UpdatePartNumber (
    IN UINT8                    *StructBuffer,
    IN EFI_SMBUS_DEVICE_ADDRESS SpdSmBusAddr,
    IN MEM_SPD_DATA             *SpdData
)
{
    EFI_STATUS              Status;
    UINTN                   i;
    UINT8                   Data8;
    UINTN                   SpdOffset;

    StructBuffer += ((SMBIOS_STRUCTURE_HEADER*)StructBuffer)->Length;
    StructBuffer += GetStringOffset(StructBuffer, 6);

    if (MemType == 0) return EFI_UNSUPPORTED;       // Not supported
    if (MemType == 1) SpdOffset = 0x49;
    if (MemType == 2) SpdOffset = 128;
    if (MemType == 3) SpdOffset = 329;

    for (i = 0; i < 18; i++) {
        if (SpdData) {
            if (SpdOffset == 73) {                  // 0x49
                Data8 = SpdData->Byte73To90[73 + i - 73];
            }
            else if (SpdOffset == 128){
                Data8 = SpdData->Byte128To145[128 + i - 128];
            }
            else {
                Data8 = SpdData->Byte329To348[329 + i - 329];
            }
        }
        else {
            Status = gSmbiosBoardProtocol->GetSpdByte(SpdSmBusAddr, SpdOffset + i, &Data8);
            if (EFI_ERROR(Status)) return Status;
        }
        if (*StructBuffer == 0) return EFI_BUFFER_TOO_SMALL;
        if (Data8 == 0) Data8 = 0x20;
        *StructBuffer++ = FilterCharacter(Data8);
    }

    while (*StructBuffer != 0) *StructBuffer++ = 0x20;

    return EFI_SUCCESS;
}

BOOLEAN
ValidateStringNumber(
    IN UINT8    *StructurePtr,
    IN UINT8    StructureType,
    IN UINTN    StringNumber
)
{
    if (StructureType == 11 || StructureType == 12) {
        return (*(StructurePtr + sizeof(SMBIOS_STRUCTURE_HEADER)) >= StringNumber);
    }
    else {
        STRING_TABLE    *StringTablePtr;

        StringTablePtr = (STRING_TABLE*)GetTypeTable(StructureType);

        if (StringTablePtr) {
            while ((StringTablePtr->Offset != 0xff) && --StringNumber) ++StringTablePtr;

            return (StringTablePtr->Offset != 0xff);
        }
        else {
            return FALSE;
        }
    }
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
    UINT8       *StructEndPtr;
    UINTN       RemainingSize;

    if (FindString(&DestStructPtr, StringNum)) {
        UINT8       *TempPtr;
        UINT8       *NextStrPtr;

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
    else {
        // String not found
        return EFI_NOT_FOUND;
    }
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   UpdateManufacturer
//
// Description: Update Type 17 Manufacturer field for the input memory slot
//              with data obtained from the SPD.
//
// Input:       IN UINT8                        *structBuffer
//              IN EFI_SMBUS_DEVICE_ADDRESS     SpdSmBusAddr
//
// Output:      EFI_STATUS
//
// Modified:    Type 17 Manufacturer field
//
// Referrals:
//
// Notes:
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS
UpdateManufacturer(
    IN UINT8                    *StructBuffer,
    IN EFI_SMBUS_DEVICE_ADDRESS SpdSmBusAddr,
    IN MEM_SPD_DATA             *SpdData
)
{
    EFI_STATUS      Status;
    UINTN           i;
    UINT8           Data8;
    UINT8           Index;
    JEDEC_MF_ID     *IdTblPtr = NULL;

    switch (MemType) {
        case 1: for (i = 0; i < 8; i++) {           // DDR2
                    if (SpdData) {
                        Data8 = SpdData->Byte64To71[64 + i - 64];
                    }
                    else {
                        Status = gSmbiosBoardProtocol->GetSpdByte(SpdSmBusAddr, 64 + i, &Data8);
                        if (EFI_ERROR(Status)) return Status;
                    }
                    if (Data8 != 0x7f) break;
                }
                break;
        case 2: if (SpdData) {                      // DDR3
                    i = SpdData->Byte117To118[117 - 117] & 0x7f;    // Remove parity bit
                    Data8 = SpdData->Byte117To118[118 - 117];
                }
                else {
                    Status = gSmbiosBoardProtocol->GetSpdByte(SpdSmBusAddr, 117, &Data8);
                    if (EFI_ERROR(Status)) return Status;
                    i = Data8 & 0x7f;               // Remove parity bit
                    Status = gSmbiosBoardProtocol->GetSpdByte(SpdSmBusAddr, 118, &Data8);
                    if (EFI_ERROR(Status)) return Status;
                }
                break;
        case 3: if (SpdData) {                      // DDR4
                    i = SpdData->Byte320To321[320 - 320] & 0x7f;    // Remove parity bit
                    Data8 = SpdData->Byte320To321[321 - 320];
                }
                else {
                    Status = gSmbiosBoardProtocol->GetSpdByte(SpdSmBusAddr, 320, &Data8);
                    if (EFI_ERROR(Status)) return Status;
                    i = Data8 & 0x7f;               // Remove parity bit
                    Status = gSmbiosBoardProtocol->GetSpdByte(SpdSmBusAddr, 321, &Data8);
                    if (EFI_ERROR(Status)) return Status;
                }
                break;
        default: return EFI_UNSUPPORTED;            // Not supported
    }

    if (i > 7) i = 7;
    IdTblPtr = ManufacturerJedecIdBankTable[i];

    // Search in Manufacturer table
    while ((IdTblPtr->VendorId != Data8) && (IdTblPtr->VendorId != 0xff)) {
        IdTblPtr++;
    }

    if (IdTblPtr->VendorId != 0xff) {
    	Status = ReplaceString(StructBuffer, 3, IdTblPtr->ManufacturerString);
    }
    else {
    	Index = 0;
    	Status = EFI_NOT_FOUND;
		while (Strcmp(ManufacturerTable[Index].Manufacturer, "Undefined")) {
			if (i == ManufacturerTable[Index].NumContCode && Data8 == ManufacturerTable[Index].ModuleManufacturer) {
				  Status = ReplaceString(StructBuffer, 3, ManufacturerTable[Index].Manufacturer);
				  break;
			}

			Index++;
		}
	}

	return Status;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   GetMemoryType
//
// Description: Detect memory device type from SPD data.
//              Only DDR2 and DDR3 are supported
//
// Input:       IN EFI_SMBUS_DEVICE_ADDRESS SpdSmBusAddr
//
// Output:      UINT8
//                  0 -> Memory type not supported
//                  1 -> DDR2
//                  2 -> DDR3
//
// Modified:    MemType = memory type (Global variable)
//
// Referrals:
//
// Notes:
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
UINT8
GetMemoryType(
    IN EFI_SMBUS_DEVICE_ADDRESS		SpdSmBusAddr
)
{
    EFI_STATUS      Status;
    UINT8           Data8;

    MemType = 0;                            // Not supported

    Status = gSmbiosBoardProtocol->GetSpdByte(SpdSmBusAddr, 2, &Data8);
    if (!EFI_ERROR(Status)) {
        if (Data8 == 8) MemType = 1;        // DDR2
        if (Data8 == 11) MemType = 2;       // DDR3
        if (Data8 == 12) MemType = 3;       // DDR4
    }

    return MemType;
}

#if UPDATE_MEMORY_TYPE16
//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   DynamicUpdateMemoryData
//
// Description: Updates Memory related structures (Type 16-20) in
//              input Buffer with dynamically detected data.
//
// Input:       IN UINT8       *Buffer
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
DynamicUpdateMemoryData(
    IN UINT8        *Buffer
)
{
    EFI_STATUS      Status;
    UINT32          Attributes = EFI_VARIABLE_BOOTSERVICE_ACCESS;
    UINT8           *SrcBuffer;
    UINT8           *StructureFoundPtr;
    UINT8           i;
    UINT8           j;
    UINT8           Data8;
    UINT8           MemErrorCorrection;
    UINTN           SmbiosVariableSize = sizeof(SYSTEM_MEM_ARRAY_DYNAMIC_DATA);
    SYSTEM_MEM_ARRAY_DYNAMIC_DATA     *SmbiosVariableBuffer;
    SMBIOS_PHYSICAL_MEM_ARRAY_INFO    *SmbArray;
    SMBIOS_MEMORY_DEVICE_INFO         *SmbDevice;
#if MEMORY_ERROR_INFO
    SMBIOS_MEMORY_ERROR_INFO          *SmbError;
#endif
    SMBIOS_MEM_ARRAY_MAP_ADDR_INFO    *SmbAmap;
#if MEMORY_DEVICE_INFO
    SMBIOS_MEM_DEV_MAP_ADDR_INFO      *SmbDmap;
#endif
    PHYSICAL_MEM_ARRAY                *DynArray;
    MEMORY_DEVICE_GROUP               *DynDevice;
    UINT8                             DataWidth[] = {8, 16, 32, 64};
    EFI_SMBUS_DEVICE_ADDRESS          DummyAddr;
	EFI_GUID                          HobListGuid = HOB_LIST_GUID;
    EFI_GUID                          SpdInfoHobGuid = AMI_SMBIOS_MEMORY_INFO_HOB_GUID;
	VOID		                      *pHobList;
    MEM_SPD_DATA                      *SpdDataPtr;
    UINT8                             *TempBuffer;

    TRACE((-1, "***  SMBIOS - DynamicUpdateMemoryData  ***\n"));

    pBS->AllocatePool(EfiBootServicesData,
                        SmbiosVariableSize,
                        (void**)&SmbiosVariableBuffer);

    pBS->AllocatePool(EfiBootServicesData,
                        0x200,
                        (void**)&TempBuffer);

    MemSet(TempBuffer, 0x200, 0);

    Status = pRS->GetVariable(SmbiosMemVar,
                        &gEfiSmbiosDynamicData,
                        &Attributes,
                        &SmbiosVariableSize,
                        SmbiosVariableBuffer);
    if (EFI_ERROR(Status)) {
        pBS->FreePool(SmbiosVariableBuffer);
        if (Status == EFI_NOT_FOUND)
            return EFI_SUCCESS;
        return Status;
    }

	pHobList = GetEfiConfigurationTable(pST, &HobListGuid);
	if (pHobList != NULL) {
		Status = FindNextHobByGuid(&SpdInfoHobGuid, &pHobList);
        if (EFI_ERROR(Status)) {
            pHobList = NULL;                // Smbios Memory Info Hob not found
        }
        else {
            SpdDataPtr = (MEM_SPD_DATA*)((UINTN)pHobList + sizeof(EFI_HOB_GUID_TYPE));
        }
    }

    SrcBuffer = Buffer;
    for (i = 0; i < gSmbiosBoardProtocol->NumberOfPhysicalMemoryArray; i++)
    {
        // Update Type 16
        if (FindStructureType(&SrcBuffer,
                        &StructureFoundPtr,
                        16,
                        1)) {
            SmbArray = ((SMBIOS_PHYSICAL_MEM_ARRAY_INFO*)StructureFoundPtr);
            DynArray = &(SmbiosVariableBuffer->PhysicalMemArray[i]);
            SmbArray->MaxCapacity = DynArray->MaxCapacity;
            SmbArray->ExtMaxCapacity = DynArray->ExtMaxCapacity;
            MemErrorCorrection = 0x06;                      // Assume Multi-bit ECC

            // Update Type 18
            #if MEMORY_ERROR_INFO
            if (gSmbiosBoardProtocol->MemoryErrorInfoSupport) {
                if (DynArray->ArrayMemoryError.ErrorType == 3) {
                    SmbArray->MemErrInfoHandle = 0xffff;    // No error
                }
                if (FindStructureType(&SrcBuffer, &StructureFoundPtr, 18, 1)) {
                    SmbError = (SMBIOS_MEMORY_ERROR_INFO*)StructureFoundPtr;
                    SmbError->ErrorType = DynArray->ArrayMemoryError.ErrorType;
                    SmbError->ErrorGranularity = DynArray->ArrayMemoryError.ErrorGranularity;
                    SmbError->ErrorOperation = DynArray->ArrayMemoryError.ErrorOperation;
                    SmbError->MemArrayErrorAddress = DynArray->ArrayMemoryError.MemArrayErrorAddress;
                    SmbError->DeviceErrorAddress = DynArray->ArrayMemoryError.DeviceErrorAddress;
                    SmbError->ErrorResolution = DynArray->ArrayMemoryError.ErrorResolution;

                    if (DynArray->ArrayMemoryError.ErrorType != 3) {
                        // Update this device's Memory Error Information Handle
                        SmbArray->MemErrInfoHandle = SmbError->StructureType.Handle;
                    }
                }
            }
            #endif

            // Update Type 19
            if (FindStructureType(&SrcBuffer, &StructureFoundPtr, 19, 1)) {
                SmbAmap = (SMBIOS_MEM_ARRAY_MAP_ADDR_INFO*)StructureFoundPtr;
                SmbAmap->StartingAddress = DynArray->MemArrayMapAddr.StartingAddress;
                SmbAmap->EndingAddress = DynArray->MemArrayMapAddr.EndingAddress;
                SmbAmap->PartitionWidth = DynArray->MemArrayMapAddr.PartitionWidth;
                SmbAmap->ExtendedStartAddr = DynArray->MemArrayMapAddr.ExtendedStartAddr;
                SmbAmap->ExtendedEndAddr = DynArray->MemArrayMapAddr.ExtendedEndAddr;
            }

            TRACE((-1, "Updating memory slots\n"));
            for (j = 0; j < gSmbiosBoardProtocol->NumberOfMemorySlots[i]; j++)
            {
                // Update Type 17
                TRACE((-1, "Searching for slot %x structure\n", j+1));
                if (FindStructureType(&SrcBuffer, &StructureFoundPtr, 17, 1)){
                    TRACE((-1, "Found slot %x structure\n", j+1));
                    SmbDevice = (SMBIOS_MEMORY_DEVICE_INFO*)StructureFoundPtr;
                    DynDevice = &(DynArray->MemoryDeviceData[j]);

                    SmbDevice->Size = DynDevice->Type17.Size;
                    SmbDevice->ExtendedSize = DynDevice->Type17.ExtendedSize;
                    SmbDevice->ConfMemClkSpeed = DynDevice->Type17.ConfMemClkSpeed;
                    SmbDevice->TotalWidth = DynDevice->Type17.TotalWidth;
                    SmbDevice->DeviceSet = DynDevice->Type17.DeviceSet;
                    SmbDevice->MinimumVoltage = DynDevice->Type17.MinimumVoltage;
                    SmbDevice->MaximumVoltage = DynDevice->Type17.MaximumVoltage;
                    SmbDevice->ConfiguredVoltage = DynDevice->Type17.ConfiguredVoltage;
                    if (DynDevice->Type17.TypeDetail != 0) {
                        SmbDevice->TypeDetail = DynDevice->Type17.TypeDetail;
                    }
                    if (SmbDevice->Size == 0) {
                        TRACE((-1, "Slot %x is empty\n", j+1));
                        SmbDevice->MemoryType = 2;      // Set to Unknown if slot empty
                        SmbDevice->Speed = 0;
                        SmbDevice->Attributes = 0;
                    }
                    else {
                        TRACE((-1, "Slot %x populated\n", j+1));
                        SmbDevice->MemoryType = DynDevice->Type17.MemoryType;
                        SmbDevice->Speed = DynDevice->Type17.Speed;

                        if (pHobList) {
                            MemType = 0;

                            switch (SpdDataPtr->Byte2) {
                                case 0x08:              // DDR2
                                        MemType = 1;
                                        SmbDevice->TotalWidth = SpdDataPtr->Byte5To8[6 - 5];
                                        Data8 = SpdDataPtr->Byte11To14[14 - 11];
                                        SmbDevice->DataWidth = SmbDevice->TotalWidth - Data8;
                                        Data8 = SpdDataPtr->Byte5To8[5 - 5];
                                        SmbDevice->Attributes = (Data8 & 0x07) + 1;
                                        if (SpdDataPtr->Byte11To14[11 - 11] != 0x02) {
                                            MemErrorCorrection = 0x03;      // No ECC
                                        }
                                        break;

                                case 0x0b:              // DDR3
                                        MemType = 2;
                                        Data8 = SpdDataPtr->Byte5To8[8 - 5];
                                        SmbDevice->DataWidth = DataWidth[Data8 & 0x07];
                                        Data8 = (Data8 & 0x18) ? 8: 0;
                                        if (Data8 == 0) {
                                            MemErrorCorrection = 0x03;      // No ECC
                                        }
                                        SmbDevice->TotalWidth = SmbDevice->DataWidth + Data8;
                                        Data8 = SpdDataPtr->Byte5To8[7 - 5];
                                        SmbDevice->Attributes = ((Data8 >> 3) & 0x07) + 1;
                                        break;

                                case 0x0c:              // DDR4
                                        MemType = 3;
                                        Data8 = SpdDataPtr->Byte11To14[13 - 11];
                                        SmbDevice->DataWidth = DataWidth[Data8 & 0x07];
                                        Data8 = (Data8 & 0x18) ? 8: 0;
                                        if (Data8 == 0) {
                                            MemErrorCorrection = 0x03;      // No ECC
                                        }
                                        SmbDevice->TotalWidth = SmbDevice->DataWidth + Data8;
                                        Data8 = SpdDataPtr->Byte11To14[12 - 11];
                                        SmbDevice->Attributes = ((Data8 >> 3) & 0x07) + 1;
                            }

                            DummyAddr.SmbusDeviceAddress = 0;
                            MemCpy(TempBuffer, SmbDevice, GetStructureLength((UINT8*)SmbDevice));
                            UpdateManufacturer(TempBuffer, DummyAddr, SpdDataPtr);
                            UpdateSerialNumber(TempBuffer, DummyAddr, SpdDataPtr);
                            UpdatePartNumber(TempBuffer, DummyAddr, SpdDataPtr);
                            WriteStructureByHandle(SmbDevice->StructureType.Handle, TempBuffer, GetStructureLength(TempBuffer));
                        }
                        else {
                            switch (GetMemoryType(DynArray->SpdSmBusAddr[j])) {
                                case 0: break;

                                case 1: gSmbiosBoardProtocol->GetSpdByte(DynArray->SpdSmBusAddr[j], 6, &Data8);    // DDR2
                                        SmbDevice->TotalWidth = Data8;
                                        gSmbiosBoardProtocol->GetSpdByte(DynArray->SpdSmBusAddr[j], 14, &Data8);
                                        SmbDevice->DataWidth = SmbDevice->TotalWidth - Data8;
                                        gSmbiosBoardProtocol->GetSpdByte(DynArray->SpdSmBusAddr[j], 5, &Data8);
                                        SmbDevice->Attributes = (Data8 & 0x07) + 1;
                                        gSmbiosBoardProtocol->GetSpdByte(DynArray->SpdSmBusAddr[j], 11, &Data8);
                                        if (Data8 != 0x02) {
                                            MemErrorCorrection = 0x03;      // No ECC
                                        }
                                        break;

                                case 2: gSmbiosBoardProtocol->GetSpdByte(DynArray->SpdSmBusAddr[j], 8, &Data8);    // DDR3
                                        SmbDevice->DataWidth = DataWidth[Data8 & 0x07];
                                        Data8 = (Data8 & 0x18) ? 8: 0;
                                        if (Data8 == 0) {
                                            MemErrorCorrection = 0x03;      // No ECC
                                        }
                                        SmbDevice->TotalWidth = SmbDevice->DataWidth + Data8;
                                        gSmbiosBoardProtocol->GetSpdByte(DynArray->SpdSmBusAddr[j], 7, &Data8);
                                        SmbDevice->Attributes = ((Data8 >> 3) & 0x07) + 1;
                                        break;

                                case 3: gSmbiosBoardProtocol->GetSpdByte(DynArray->SpdSmBusAddr[j], 13, &Data8);    // DDR4
                                        SmbDevice->DataWidth = DataWidth[Data8 & 0x07];
                                        Data8 = (Data8 & 0x18) ? 8: 0;
                                        if (Data8 == 0) {
                                            MemErrorCorrection = 0x03;      // No ECC
                                        }
                                        SmbDevice->TotalWidth = SmbDevice->DataWidth + Data8;
                                        gSmbiosBoardProtocol->GetSpdByte(DynArray->SpdSmBusAddr[j], 12, &Data8);
                                        SmbDevice->Attributes = ((Data8 >> 3) & 0x07) + 1;
                            }

                            if (GetMemoryType(DynArray->SpdSmBusAddr[j]) != 0) {
                                MemCpy(TempBuffer, SmbDevice, GetStructureLength((UINT8*)SmbDevice));
                                UpdateManufacturer(TempBuffer, DynArray->SpdSmBusAddr[j], 0);
                                UpdateSerialNumber(TempBuffer, DynArray->SpdSmBusAddr[j], 0);
                                UpdatePartNumber(TempBuffer, DynArray->SpdSmBusAddr[j], 0);
                                WriteStructureByHandle(SmbDevice->StructureType.Handle, TempBuffer, GetStructureLength(TempBuffer));
                            }
                        }
                    }

                    // Update Type 18
                    #if MEMORY_ERROR_INFO
                    if (gSmbiosBoardProtocol->MemoryErrorInfoSupport) {
                        if (DynDevice->Type18.ErrorType == 3) {
                            SmbDevice->MemErrorInfoHandle = 0xffff;    // No error
                        }
                        if (FindStructureType(&SrcBuffer, &StructureFoundPtr, 18, 1)) {
                            SmbError = (SMBIOS_MEMORY_ERROR_INFO*)StructureFoundPtr;
                            SmbError->ErrorType = DynDevice->Type18.ErrorType;
                            SmbError->ErrorGranularity = DynDevice->Type18.ErrorGranularity;
                            SmbError->ErrorOperation = DynDevice->Type18.ErrorOperation;
                            SmbError->MemArrayErrorAddress = DynDevice->Type18.MemArrayErrorAddress;
                            SmbError->DeviceErrorAddress = DynDevice->Type18.DeviceErrorAddress;
                            SmbError->ErrorResolution = DynDevice->Type18.ErrorResolution;

                            if (DynDevice->Type18.ErrorType != 3) {
                                // Update this device's Memory Error Information Handle
                                SmbDevice->MemErrorInfoHandle = SmbError->StructureType.Handle;
                            }
                        }
                    }
                    #endif

                    // Update Type 20
                    #if MEMORY_DEVICE_INFO
                    if (FindStructureType(&SrcBuffer, &StructureFoundPtr, 20, 1)) {
                        SmbDmap = (SMBIOS_MEM_DEV_MAP_ADDR_INFO*)StructureFoundPtr;
                        if (SmbDevice->Size) {
                            SmbDmap->StartingAddress = DynDevice->Type20.StartingAddress;
                            SmbDmap->EndingAddress = DynDevice->Type20.EndingAddress;
                            SmbDmap->PartitionRowPosition = DynDevice->Type20.PartitionRowPosition;
                            SmbDmap->InterleavePosition = DynDevice->Type20.InterleavePosition;
                            SmbDmap->InterleaveDataDepth = DynDevice->Type20.InterleaveDataDepth;
                            SmbDmap->ExtendedStartAddr = DynDevice->Type20.ExtendedStartAddr;
                            SmbDmap->ExtendedEndAddr = DynDevice->Type20.ExtendedEndAddr;
                        }
                        else {
                            SmbDmap->StructureType.Type = 126;
                        }
                    }
                    #endif
                }

                SpdDataPtr++;
            }

            SmbArray->MemErrorCorrection = MemErrorCorrection;
        }
    }

    pBS->FreePool(TempBuffer);
    pBS->FreePool(SmbiosVariableBuffer);

    TRACE((-1, ":::  SMBIOS - Exit DynamicUpdateMemoryData  :::\n"));

    return EFI_SUCCESS;
}
#endif

#if FLASH_MEMORY_ARRAY_INFO && defined(FLASH_PART_STRING_LENGTH)
//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   DynamicUpdateFlashMemoryData
//
// Description: Updates Flash Memory related structures (Type 16-20)
//              with dynamically detected data.
//
// Input:       None
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
DynamicUpdateFlashMemoryData(VOID)
{
    UINT32                      Flash4GBMapStart;
    UINT8                       FlashInfo[0x100];
    char                        *Manufacturer = NULL;
    char                        *PartNumber;
    UINT8                       *Buffer;
    UINT8                       *FlashMemoryStructurePtr;
    EFI_SMBIOS_HANDLE           SmbiosHandle;
    UINTN                       StringNumber;

    TRACE((-1, "***  SMBIOS - DynamicUpdateFlashMemoryData  ***\n"));

    Flash4GBMapStart = 0xFFFFFFFF - FLASH_BLOCK_SIZE;
    Flash4GBMapStart ++;
    GetFlashPartInfomation ( (UINT8*)Flash4GBMapStart, FlashInfo );

    Manufacturer = FlashInfo + 8;               // Skip "$FPS" signature and size
    PartNumber = Strstr(Manufacturer, " ");
    // Replace " " with string terminator for Manufacturer
    *PartNumber++ = 0;

    Buffer = SmbiosDataTable;

    // Search for Flash Memory structure
    while (1) {
        FindStructureType(&Buffer, &FlashMemoryStructurePtr, 17, 1);
        if (FlashMemoryStructurePtr == NULL) {
            break;
        }
        else {
            if (((SMBIOS_MEMORY_DEVICE_INFO*)FlashMemoryStructurePtr)->MemoryType == 9) {
                break;
            }
        }
    };

    if (FlashMemoryStructurePtr != NULL) {
        SmbiosHandle = ((SMBIOS_STRUCTURE_HEADER*)FlashMemoryStructurePtr)->Handle;
        StringNumber = 3;
        SmbiosPiUpdateString(NULL, &SmbiosHandle, &StringNumber, Manufacturer);
        StringNumber = 6;
        SmbiosPiUpdateString(NULL, &SmbiosHandle, &StringNumber, PartNumber);

        TRACE((-1, ":::  SMBIOS - Exit DynamicUpdateFlashMemoryData  :::\n"));
        return EFI_SUCCESS;
    }

    TRACE((-1, "Flash Memory Structure not found\n"));
    return EFI_NOT_FOUND;
}
#endif

#if UPDATE_BATTERY_TYPE22
//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   DynamicUpdateBatteryData
//
// Description: Updates Portable Battery structures (Type 22) in
//              input Buffer with dynamically detected data.
//
// Input:       IN UINT8       *Buffer
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
DynamicUpdateBatteryData(
  	IN UINT8        *Buffer
)
{
  	EFI_STATUS      Status;
  	UINT32          Attributes = EFI_VARIABLE_BOOTSERVICE_ACCESS;
    UINT16          StructureHandle;
  	UINT8           *SrcBuffer;
    UINT8           *StructureFoundPtr;
    UINT8           i;
    UINT8           *TempStructure22;
    UINTN           TempStructure22Size;
  	UINT8           *SmbiosVariableBuffer;
  	UINTN           SmbiosVariableSize;

    TRACE((-1, "***  SMBIOS - DynamicUpdateBatteryData  ***\n"));

    SmbiosVariableSize = sizeof(BATTERY_DYNAMIC_DATA);
  	pBS->AllocatePool(EfiBootServicesData,
                    SmbiosVariableSize,
                    &SmbiosVariableBuffer);

  	Status = pRS->GetVariable(SmbiosBatteryVar,
                        &gEfiSmbiosDynamicData,
                        &Attributes,
                        &SmbiosVariableSize,
                        SmbiosVariableBuffer);

  	if (EFI_ERROR(Status) && Status != EFI_NOT_FOUND) {
    	pBS->FreePool(SmbiosVariableBuffer);

    	TRACE((-1, "Failed to get SmbiosBatteryVar\n"));
    	return Status;
  	}

    if (Status != EFI_NOT_FOUND) {
        TempStructure22Size = sizeof(SMBIOS_PORTABLE_BATTERY_INFO) + (7 * 65) + 1;
      	pBS->AllocatePool(EfiBootServicesData,
                        TempStructure22Size,
                        &TempStructure22);

        for (i = 0; i < gSmbiosBoardProtocol->NumberOfBatteries; i++) {
            SrcBuffer = Buffer;
            if (FindStructureType(&SrcBuffer, &StructureFoundPtr, 22, i + 1)) {
                StructureHandle = ((SMBIOS_STRUCTURE_HEADER*)StructureFoundPtr)->Handle;
            	if(((BATTERY_DYNAMIC_DATA*)SmbiosVariableBuffer)->BatteryDynamicData[i].Valid){
                    MemCpy(TempStructure22,
                        StructureFoundPtr,
                        GetStructureLength(StructureFoundPtr));

        			((SMBIOS_PORTABLE_BATTERY_INFO*)TempStructure22)->DesignCapacity =
        				((BATTERY_DYNAMIC_DATA*)SmbiosVariableBuffer)->BatteryDynamicData[i].DesignCapacity;
        			((SMBIOS_PORTABLE_BATTERY_INFO*)TempStructure22)->DesignVoltage =
        				((BATTERY_DYNAMIC_DATA*)SmbiosVariableBuffer)->BatteryDynamicData[i].DesignVoltage;
        			((SMBIOS_PORTABLE_BATTERY_INFO*)TempStructure22)->SBDSSerialNumber =
        				((BATTERY_DYNAMIC_DATA*)SmbiosVariableBuffer)->BatteryDynamicData[i].SbdsSerialNumber;
        			((SMBIOS_PORTABLE_BATTERY_INFO*)TempStructure22)->SBDSManufacturerDate =
        				((BATTERY_DYNAMIC_DATA*)SmbiosVariableBuffer)->BatteryDynamicData[i].SbdsManufacturedDate;
        			((SMBIOS_PORTABLE_BATTERY_INFO*)TempStructure22)->DesignCapabilityMult =
        				((BATTERY_DYNAMIC_DATA*)SmbiosVariableBuffer)->BatteryDynamicData[i].DesignCapacityMult;

                    ReplaceString(TempStructure22,
                        5,
                        ((BATTERY_DYNAMIC_DATA*)SmbiosVariableBuffer)->BatteryDynamicData[i].DeviceName);
                    ReplaceString(TempStructure22,
                        6,
                        ((BATTERY_DYNAMIC_DATA*)SmbiosVariableBuffer)->BatteryDynamicData[i].SbdsVersion);

                    WriteStructureByHandle(StructureHandle,
                                        TempStructure22,
                                        GetStructureLength(TempStructure22));
        		}
            	else {
                    DeleteStructureByHandle(StructureHandle);
                }
            }
        }
        pBS->FreePool(TempStructure22);
    }

    pBS->FreePool(SmbiosVariableBuffer);

    TRACE((-1, ":::  SMBIOS - Exit DynamicUpdateBatteryData  :::\n"));

    return EFI_SUCCESS;
}
#endif

#if UPDATE_ADDITIONAL_INFO_TYPE40
//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   DynamicUpdateAdditionalInfoData
//
// Description: Updates Additional Information structures (Type 40) in
//              input Buffer - Referenced Handle field.
//
// Input:       IN UINT8       *Buffer
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
DynamicUpdateAdditionalInfoData(
  	IN UINT8        *Buffer
)
{
    UINT8           *SrcBuffer;
    UINT8           *AdditionalInfoPtr;
    UINT8           *StructureFoundPtr;
    UINT8           NumAdditionalInfoEntries;
    UINT8           StructureType;
    UINT8           Instance;
    UINT8           i;

    TRACE((-1, "***  SMBIOS - DynamicUpdateAdditionalInfoData  ***\n"));

    SrcBuffer = Buffer;
    if (FindStructureType(&SrcBuffer, &AdditionalInfoPtr, 40, 1))
    {
        NumAdditionalInfoEntries = ((SMBIOS_ADDITIONAL_INFO*)AdditionalInfoPtr)->NumAdditionalInfoEntries;
        for (i = 0; i < NumAdditionalInfoEntries; i++)
        {
            SrcBuffer = Buffer;
            StructureType = ((SMBIOS_ADDITIONAL_INFO*)AdditionalInfoPtr)->AdditionalEntries[i].RefHandle / 16;
            Instance = ((SMBIOS_ADDITIONAL_INFO*)AdditionalInfoPtr)->AdditionalEntries[i].RefHandle % 16;
            if (FindStructureType(&SrcBuffer, &StructureFoundPtr, StructureType, Instance))
            {
                ((SMBIOS_ADDITIONAL_INFO*)AdditionalInfoPtr)->AdditionalEntries[i].RefHandle =
                                                        ((SMBIOS_STRUCTURE_HEADER*)StructureFoundPtr)->Handle;
            }
        }
    }

    TRACE((-1, ":::  SMBIOS - Exit DynamicUpdateAdditionalInfoData  :::\n"));

    return EFI_SUCCESS;
}
#endif

#if UPDATE_DEVICE_EXT_TYPE41
//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   DynamicUpdateOnboardDevExt
//
// Description: Updates On Board Devices Extended Information structure (Type 41)
//              in input Buffer with dynamically detected data.
//
// Input:       IN UINT8       *Buffer
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
DynamicUpdateOnboardDevExt(
    IN UINT8        *Buffer
)
{
    EFI_STATUS      Status;
    UINT32          Attributes = EFI_VARIABLE_BOOTSERVICE_ACCESS;
    UINT8           *SrcBuffer;
    UINT8           *StructureFoundPtr;
    UINT8           *SmbiosVariableBuffer;
    UINTN           SmbiosVariableSize;
    UINT8           i;

    TRACE((-1, "***  SMBIOS - DynamicUpdateOnboardDevExt  ***\n"));

    SmbiosVariableSize = sizeof(ONBOARD_DEV_EXT_DYNAMIC_DATA);
    pBS->AllocatePool(EfiBootServicesData, SmbiosVariableSize, (void**)&SmbiosVariableBuffer);
    Status = pRS->GetVariable(SmbiosOnBoardExtVar, &gEfiSmbiosDynamicData,
                             &Attributes, &SmbiosVariableSize, SmbiosVariableBuffer);
    if (EFI_ERROR(Status) && Status != EFI_NOT_FOUND) {
        pBS->FreePool(SmbiosVariableBuffer);

        TRACE((-1, "Failed to get SmbiosOnBoardExtVar\n"));
        return Status;
    }

    if (Status != EFI_NOT_FOUND) {
        SrcBuffer = Buffer;
        for (i = 0; i < gSmbiosBoardProtocol->NumberOfOnboardDevExt; i++) {
            if (FindStructureType(&SrcBuffer, &StructureFoundPtr, 41, 1)) {
                ((SMBIOS_ONBOARD_DEV_EXT_INFO*)StructureFoundPtr)->DeviceType &= 0x7f;
                ((SMBIOS_ONBOARD_DEV_EXT_INFO*)StructureFoundPtr)->DeviceType |= ((ONBOARD_DEV_EXT_DYNAMIC_DATA*)SmbiosVariableBuffer)->OnBoardDev[i];
                ((SMBIOS_ONBOARD_DEV_EXT_INFO*)StructureFoundPtr)->BusNumber = ((ONBOARD_DEV_EXT_DYNAMIC_DATA*)SmbiosVariableBuffer)->BusNumber[i];
            }
        }
    }
    pBS->FreePool(SmbiosVariableBuffer);

    TRACE((-1, ":::  SMBIOS - Exit DynamicUpdateOnboardDevExt  :::\n"));
    return EFI_SUCCESS;
}
#endif

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   DynamicUpdateStructures
//
// Description: Updates CPU, System Slot, On Board Devices, Memory structures
//              input Buffer with dynamically detected data.
//
// Input:       IN UINT8                       *Buffer
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
DynamicUpdateStructures(
    IN  UINT8                       *Buffer
)
{
    static BOOLEAN FirstRun = TRUE;

    TRACE((-1, "***  SMBIOS - DynamicUpdateStructures  ***\n"));

    if (FirstRun && (gSmbiosBoardProtocol != NULL)) {
        #if (TYPE2_STRUCTURE && UPDATE_BASEBOARD_TYPE2)
            if (gSmbiosBoardProtocol->BaseBoardInfoSupport) {
                DynamicUpdateBaseBoardData(SmbiosDataTable);
            }
        #endif
        #if (TYPE3_STRUCTURE && UPDATE_SYSTEM_CHASSIS_TYPE3)
            if (gSmbiosBoardProtocol->SysChassisInfoSupport) {
                DynamicUpdateChassisData(SmbiosDataTable);
            }
        #endif
        #if (TYPE4_STRUCTURE && UPDATE_CPU_TYPE4)
        if (UpdateCpuStructure) {
            DynamicUpdateCpuData(SmbiosDataTable);
        }
        #endif
        #if (TYPE9_STRUCTURE && UPDATE_SLOT_TYPE9)
            DynamicUpdateSlotsData(SmbiosDataTable);
        #endif
        #if (TYPE10_STRUCTURE && UPDATE_ONBOARD_DEV_TYPE10)
            if (gSmbiosBoardProtocol->OnboardDeviceInfoSupport) {
                DynamicUpdateOnboardDevData(SmbiosDataTable);
            }
        #endif
        #if (TYPE16_STRUCTURE && UPDATE_MEMORY_TYPE16)
            gSmbiosBoardProtocol->EnableSmbusController();
            DynamicUpdateMemoryData(SmbiosDataTable);
            gSmbiosBoardProtocol->RestoreSmbusController();
        #endif
        #if FLASH_MEMORY_ARRAY_INFO && defined(FLASH_PART_STRING_LENGTH)
            DynamicUpdateFlashMemoryData();
        #endif
        #if (TYPE22_STRUCTURE && UPDATE_BATTERY_TYPE22)
            if (gSmbiosBoardProtocol->PortableBatteryInfoSupport) {
                DynamicUpdateBatteryData(SmbiosDataTable);
            }
        #endif
        #if (TYPE40_STRUCTURE && UPDATE_ADDITIONAL_INFO_TYPE40)
            if (gSmbiosBoardProtocol->AdditionalInfoSupport) {
                DynamicUpdateAdditionalInfoData(SmbiosDataTable);
            }
        #endif
        #if (TYPE41_STRUCTURE && UPDATE_DEVICE_EXT_TYPE41)
            if (gSmbiosBoardProtocol->OnboardDeviceExtInfoSupport) {
                DynamicUpdateOnboardDevExt(SmbiosDataTable);
            }
        #endif

        FirstRun = FALSE;
    }

    TRACE((-1, ":::  SMBIOS - Exit DynamicUpdateStructures  :::\n"));
    return EFI_SUCCESS;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   GetSmbiosTableEntryPoint
//
// Description: SMBIOS protocol - Returns the pointer to the SmbiosTableEntryPoint
//
// Input:       None
//
// Output:      VOID* - Pointer to the SmbiosTableEntryPoint
//
// Modified:
//
// Referrals:
//
// Notes:
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID*
GetSmbiosTableEntryPoint(
)
{
    return pSmbiosTableEntryPoint;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   GetScratchBufferPtr
//
// Description: SMBIOS protocol - Returns the pointer to the Scratch buffer
//              equal the SMBIOS data structure in size.
//
// Input:       None
//
// Output:      VOID* - Pointer to the Scratch buffer
//
// Modified:
//
// Referrals:
//
// Notes:
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID*
GetScratchBufferPtr(
)
{
    return ScratchBufferPtr;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   GetScratchBufferPtr
//
// Description: SMBIOS protocol - Returns the maximum size for the SMBIOS
//              data structure table.
//
// Input:       None
//
// Output:      UINT16 - Maximum SMBIOS data table size
//
// Modified:
//
// Referrals:
//
// Notes:
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
UINT16
GetBufferMaxSize(VOID)
{
    return MaximumTableSize;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   CheckForValidStructure
//
// Description: Checks for structure validity
//
// Input:       IN UINT8   *Buffer
//              IN UINT16  Size
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
CheckForValidStructure(
    IN  UINT8   *Buffer,
    IN  UINT16  Size
)
{
    // Check for valid terminator
    if (*(UINT16*)(Buffer + Size - 2) != 0) {
        TRACE((-1, "Invalid structure terminator\n"));
        return DMI_BAD_PARAMETER;
    }

    // Check for valid size
    if (Size < (((SMBIOS_STRUCTURE_HEADER*)Buffer)->Length + 2)) {
        TRACE((-1, "Invalid structure size\n"));
        return DMI_BAD_PARAMETER;
    }
    return DMI_SUCCESS;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   GetTotalStructureSize
//
// Description: Returns the total structure size
//
// Input:       IN UINT8   *Buffer
//
// Output:      UINT16 - Total structure size
//
// Modified:
//
// Referrals:
//
// Notes:
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
UINT16
GetTotalStructureSize(
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
// Procedure:   UpdateEPSHeader
//
// Description: Updates the SMBIOS Entry Point Header
//
// Input:       IN SMBIOS_TABLE_ENTRY_POINT  *pSmbiosTableEntryPoint
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
UpdateEPSHeader(
    IN  SMBIOS_TABLE_ENTRY_POINT  *pSmbiosTableEntryPoint
)
{
#if (defined(SB_WAKEUP_TYPE_FN) && (SB_WAKEUP_TYPE_FN == 1))
	UINT8		    *Buffer;
	UINT8		    *FoundPtr = NULL;

    //
    // Create "WakeUpType" variable containing pointer to this field
    // so that it can be updated on S3 resume
    //
    Buffer = SmbiosDataTable;

    if (FindStructureType(&Buffer, &FoundPtr, 1, 1)) {
        FoundPtr += 0x18;

        pRS->SetVariable(
                        L"WakeUpType",
                        &gEfiSmbiosNvramGuid,
                        EFI_VARIABLE_BOOTSERVICE_ACCESS | EFI_VARIABLE_NON_VOLATILE,
                        4,
                        &FoundPtr);
    }
#endif

#if ( defined(CSM_SUPPORT) && (CSM_SUPPORT != 0) )
    if ((LegacyRegionProtocol != NULL) && (((UINT32)pSmbiosTableEntryPoint & 0xffff0000) == 0x000f0000)) {
    	LegacyRegionProtocol->UnLock (LegacyRegionProtocol,
									  0xf0000,
                                      0x10000,
									  NULL);
	}
#endif
    // Updating EPS Header
    // Update SMBIOS Data Structure Table length in EPS Header
    pSmbiosTableEntryPoint->TableLength = GetTotalStructureSize(SmbiosDataTable);
    pSmbiosTableEntryPoint->TableAddress = (UINT32)(UINTN)SmbiosDataTable;

    // Find and update number of SMBios Structures in EPS Header
    pSmbiosTableEntryPoint->NumberOfSmbiosStructures = GetNumberOfStructures(SmbiosDataTable);

    // Find and update largest SMBios Structure in EPS Header
    pSmbiosTableEntryPoint->MaxStructureSize = GetLargestStructureSize((UINT8*)(UINTN)pSmbiosTableEntryPoint->TableAddress);

    // Update Checksums in EPS Header
    pSmbiosTableEntryPoint->IntermediateChecksum = 0;
    pSmbiosTableEntryPoint->IntermediateChecksum = SmbiosCheckSum((UINT8*)pSmbiosTableEntryPoint + 0x10, 15);

    pSmbiosTableEntryPoint->EntryPointStructureChecksum = 0;
    pSmbiosTableEntryPoint->EntryPointStructureChecksum = SmbiosCheckSum((UINT8*)pSmbiosTableEntryPoint,
                                                                      pSmbiosTableEntryPoint->EntryPointLength);

#if ( defined(CSM_SUPPORT) && (CSM_SUPPORT != 0) )
    if ((LegacyRegionProtocol != NULL) && (((UINT32)pSmbiosTableEntryPoint & 0xffff0000) == 0x000f0000)) {
    	LegacyRegionProtocol->Lock (LegacyRegionProtocol,
									0xf0000,
                                    0x10000,
									NULL);
	}
#endif
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   UpdateSmbiosTable
//
// Description: Update the SMBIOS Table
//
// Input:       IN SMBIOS_OPERATION    Operation
//              IN UINT8               *StructurePtr
//                                        - Adding operation: N/A
//                                        - Delete operation: Pointer to
//                                          structure to be deleted
//              IN UINT8               *Buffer
//                                        - Adding operation: Pointer to buffer
//                                          to be added
//                                        - Delete operation: N/A
//              IN UINT16              Size
//                                        - Adding operation: Size of buffer
//                                          to be added
//                                        - Delete operation: N/A
//              IN UINT16              Handle
//                                        - Adding operation:
//                                          = 0xFFFF to assign next handle number
//                                          = Other value to assign a specific
//                                              handle number
//                                        - Delete operation: N/A
//
// Output:      EFI_STATUS
//
// Modified:
//
// Referrals:
//
// Notes: Dynamic table sizing can only be done when SMBIOS table is at
//        high memory. At E000, table can be expanded up to the padding size.
//        This limitation is due to CSM can only allocate memory, but it does
//        not have memory deallocation feature.
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS
UpdateSmbiosTable(
    IN SMBIOS_OPERATION     Operation,
    IN UINT8                *StructurePtr,
    IN UINT8                *Buffer,
    IN UINT16               Size,
    IN UINT16               Handle
)
{
    EFI_STATUS              Status = -1;
    EFI_STATUS              TableCopyStatus = -1;
    UINT8                   *SmbiosTableCopy;
    UINT8                   *AllocatedMemory;
    UINT8                   *MemoryPtr;
    UINT8                   *TempPtr;
    UINT8                   *TempPtr2;
    UINT8                   *Type127;
    UINT16                  TableLength;
    UINT32                  Length;

#if ( defined(CSM_SUPPORT) && (CSM_SUPPORT != 0) )
    if ((LegacyRegionProtocol != NULL) && SmbiosTableAtE000) {
        LegacyRegionProtocol->UnLock (LegacyRegionProtocol,
                                      (UINT32)SmbiosDataTable,
                                      MaximumTableSize,
                                      NULL);
    }
#endif

    TRACE((-1, "***  SMBIOS - UpdateSmbiosTable  ***\n"));
    TRACE((-1, "Operation = %x, Size = %x, Handle = %x\n", Operation, Size, Handle));

    switch (Operation) {
        case ADD_STRUCTURE:
                if (Buffer == NULL) {
                        Status = EFI_INVALID_PARAMETER;
                        break;
                }

                if (Handle != 0xffff) {
                    // Check for existing handle
                    TempPtr = SmbiosDataTable;
                    if (FindStructureHandle(&TempPtr, Handle)) {
                        Status = EFI_INVALID_PARAMETER;
                        break;
                    }
                }

                // Check input buffer for valid structure according to its size
                Status = CheckForValidStructure(Buffer, Size);
                if (Status != EFI_SUCCESS) {
                    Status = EFI_PROTOCOL_ERROR;
                    break;
                }

                // Make copy of the original Smbios Table
                TableCopyStatus = pBS->AllocatePool(
                                            EfiBootServicesData,
                                            MaximumTableSize,
                                            (void**)&SmbiosTableCopy
                                            );
                if (EFI_ERROR(TableCopyStatus)) {
                    Status = EFI_OUT_OF_RESOURCES;
                    break;
                }

                // TempPtr = pointer to the original Smbios table
                TempPtr = SmbiosTableCopy;
                MemCpy(TempPtr, SmbiosDataTable, MaximumTableSize);

                if (SmbiosTableAtE000) {
                    // Check for enough space
                    TableLength = GetTotalStructureSize(SmbiosDataTable);
                    if (Size > (MaximumTableSize - TableLength)) {
                        Status =  EFI_OUT_OF_RESOURCES;
                        break;
                    }

                    MemoryPtr = SmbiosDataTable;
                }
                else {
                    TRACE((-1, "Allocating memory for new table\n"));
                    // Allocate memory to store new Smbios table
                    TableLength = MaximumTableSize + Size;
                    Status = pBS->AllocatePool(
                                        EfiRuntimeServicesData,
                                        TableLength,
                                        &AllocatedMemory
                                        );
                    if (EFI_ERROR(Status)) {
                        TRACE((-1, "Failed to allocate memory\n"));
                        Status = EFI_OUT_OF_RESOURCES;
                        break;
                    }

                    // Copy current Smbios table to the new location
                    MemCpy(AllocatedMemory, SmbiosDataTable, MaximumTableSize);

                    MemoryPtr = AllocatedMemory;
                    TRACE((-1, "Memory allocated = %x\n", MemoryPtr));
                }

				if (ADD_STRUCTURE_LOCATION == 1) {
	                // Advance the pointers to the first structure whose handle number
	                // is larger than the input handle. In case input handle is FFFF,
	                // move the pointers to the last structure (Type 127).
	                while (((SMBIOS_STRUCTURE_HEADER*)MemoryPtr)->Type != 127) {
	                    if (((SMBIOS_STRUCTURE_HEADER*)MemoryPtr)->Handle > Handle) {
	                        break;
	                    }

	                    Length = GetStructureLength(MemoryPtr);

	                    // Move pointer in the new Smbios table
	                    MemoryPtr += Length;

	                    // Move pointer in the original Smbios table
	                    TempPtr += Length;
	                }
				}
				else {
	                TempPtr2 = TempPtr;
	                FindStructureType(&TempPtr2, &TempPtr, 127, 1);
					MemoryPtr += TempPtr - SmbiosTableCopy;
				}

                if (Handle == 0xffff) {
                    // Assign the LastHandle to the newly added structure
                    ((SMBIOS_STRUCTURE_HEADER*)Buffer)->Handle = LastHandle;
                }
                else {
                    ((SMBIOS_STRUCTURE_HEADER*)Buffer)->Handle = Handle;

                    if (Handle > LastHandle) {
                        LastHandle = Handle;
                    }
                }

                // Insert input structure
                MemCpy(MemoryPtr, Buffer, Size);
                MemoryPtr += Size;

                // Copy remaining structures
                Length = GetRemainingStructuresSize(TempPtr);
                MemCpy(MemoryPtr, TempPtr, Length);

                // Update Type 127 handle if needed
                FindStructureType(&MemoryPtr, &Type127, 127, 1);
                if (LastHandle >= ((SMBIOS_STRUCTURE_HEADER*)Type127)->Handle) {
            		((SMBIOS_STRUCTURE_HEADER*)Type127)->Handle = ++LastHandle;
                }

                TRACE((-1, "Done adding structure\n"));
                Status = EFI_SUCCESS;
                break;

        case DELETE_STRUCTURE:
                TRACE((-1, "Deleting structure\n"));
                // Clear UpdateCpuStructure flag if CPU (type 4) structure is being deleted
                if (((SMBIOS_STRUCTURE_HEADER*)StructurePtr)->Type == 4) {
                    UpdateCpuStructure = FALSE;
                }

                // StructurePtr = Pointer to structure to be deleted
                if (SmbiosTableAtE000) {
                    Length = GetTotalStructureSize(StructurePtr) - GetStructureLength(StructurePtr);
                    TempPtr = StructurePtr + GetStructureLength(StructurePtr);
                    MemCpy(StructurePtr, TempPtr, Length);
                    Status = EFI_SUCCESS;
                TRACE((-1, "Done deleting\n"));
                    break;
                }
                else {
                    Length = (UINT32)(StructurePtr - SmbiosDataTable);    // From start of SmbiosTable to current ptr
                    TableLength = MaximumTableSize - GetStructureLength(StructurePtr);
                    Status = pBS->AllocatePool(
                                        EfiRuntimeServicesData,
                                        TableLength,
                                        &AllocatedMemory
                                        );
                    if (EFI_ERROR(Status)) {
                        Status = EFI_OUT_OF_RESOURCES;
                        break;
                    }
                    MemoryPtr = AllocatedMemory;
                    MemCpy(MemoryPtr, SmbiosDataTable, Length);
                    MemoryPtr += Length;
                    TempPtr = StructurePtr + GetStructureLength(StructurePtr);
                    TempPtr2 = SmbiosDataTable + MaximumTableSize;
                    MemCpy(MemoryPtr, TempPtr, TempPtr2 - TempPtr);
                    Status = EFI_SUCCESS;
                    break;
                }

        default:
                TableCopyStatus = EFI_PROTOCOL_ERROR;
                Status = EFI_PROTOCOL_ERROR;
    }

    if (TableCopyStatus == EFI_SUCCESS) {
        pBS->FreePool(SmbiosTableCopy);
    }

    TRACE((-1, "Status = %r\n", Status));
    if (Status == EFI_SUCCESS) {
        if (!SmbiosTableAtE000) {
			if (TableRelocated) {
	            pBS->FreePool(SmbiosDataTable);
			}
            SmbiosDataTable = AllocatedMemory;
            MaximumTableSize = TableLength;
			TableRelocated = TRUE;
        }
        UpdateEPSHeader(pSmbiosTableEntryPoint);
    }

#if ( defined(CSM_SUPPORT) && (CSM_SUPPORT != 0) )
    if ((LegacyRegionProtocol != NULL) && SmbiosTableAtE000) {
        LegacyRegionProtocol->Lock (LegacyRegionProtocol,
                                    (UINT32)SmbiosDataTable,
                                    MaximumTableSize,
                                    NULL);
    }
#endif

    TRACE((-1, ":::  SMBIOS - Exit UpdateSmbiosTable. Status = %r  :::\n", Status));
    return Status;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   GetFreeHandle
//
// Description: SMBIOS protocol - Searches available handle
//                                of Smbios Data Table
//
//
// Input:       None
//
// Output:      UINT16 - Handle or -1(if not found)
//
// Modified:
//
// Referrals:
//
// Notes:
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
UINT16
GetFreeHandle(VOID)
{
    EFI_STATUS    FoundStatus;

    UINT16        Handle = 0;
	UINT8         *StructurePtr;

    // Count Handle form 0 to 0xFFFF to find available Handle
    for (Handle = 0; Handle < 0xffff; Handle++) {
        StructurePtr = SmbiosDataTable;
        FoundStatus = FindStructureHandle(&StructurePtr, Handle);
        if (!FoundStatus) {
            return Handle;
        }
    }

	return -1; // No available Handle to use;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   CheckForType4AndUpdate
//
// Description: Check input Buffer for Type 4 (CPU structure) and update it
//              with DMIEdit data if exist
//
// Input:       IN UINT8   **Buffer
//              IN UINT16  *Size
//
// Output:      Updated Buffer and Size
//
// Modified:
//
// Referrals:
//
// Notes:
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID
CheckForType4AndUpdate(
    IN OUT  UINT8        **Buffer,
    IN OUT  UINT16       *Size
)
{
    UINT8               *PoolMemory;

    if (((SMBIOS_STRUCTURE_HEADER*)*Buffer)->Type == 4) {
        // Check if there are DMIEdit data for Serial Number, or Asset Tag, or Part Number fields
        if (NvramType4.Flag & 0x3f) {
            // Allocate 1K memory
            pBS->AllocatePool(
                        EfiBootServicesData,
                        0x400,
                        (void**)&PoolMemory);
            MemSet(PoolMemory, 0x400, 0);
            MemCpy(PoolMemory, *Buffer, *Size);

            // Replace DMIEdit strings if exist
            UpdateStrings((SMBIOS_NVRAM_TYPE*)&NvramType4, PoolMemory, 1);

            // Change input Buffer to allocated memory with updated data
            *Buffer = PoolMemory;
            *Size = GetStructureLength(PoolMemory);
        }
    }
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   AddStructure
//
// Description: SMBIOS protocol - Add new structure
//
// Input:       IN UINT8   *Buffer
//              IN UINT16  Size
//
// Output:      EFI_STATUS
//              Buffer->Handle = Assigned handle number
//
// Modified:
//
// Referrals:
//
// Notes:
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS
AddStructure(
    IN UINT8        *Buffer,
    IN UINT16       Size
)
{
    EFI_STATUS      Status;

    TRACE((-1, "***  SMBIOS - AddStructure  ***\n"));

    CheckForType4AndUpdate(&Buffer, &Size);

    Status = UpdateSmbiosTable(
                    ADD_STRUCTURE,
                    NULL,
                    Buffer,
                    Size,
                    0xFFFF                  // Assign next handle number
                    );

    TRACE((-1, ":::  SMBIOS - Exit AddStructure. Status = %r  :::\n", Status));
    return Status;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   AddStructureByHandle
//
// Description: SMBIOS protocol - Add new structure with a specific handle -
//              structure will not be added if another structure with this
//              handle already existed.
//
// Input:       IN UINT16  Handle
//              IN UINT8   *Buffer
//              IN UINT16  Size
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
AddStructureByHandle(
    IN UINT16       Handle,
    IN UINT8        *Buffer,
    IN UINT16       Size
)
{
    EFI_STATUS      Status;

    TRACE((-1, "***  SMBIOS - AddStructureByHandle  ***\n"));

    CheckForType4AndUpdate(&Buffer, &Size);

    return UpdateSmbiosTable(
                    ADD_STRUCTURE,
                    NULL,
                    Buffer,
                    Size,
                    Handle
                    );

    TRACE((-1, ":::  SMBIOS - Exit AddStructureByHandle. Status = %r  :::\n", Status));
    return Status;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   DeleteStructureByHandle
//
// Description: SMBIOS protocol - Searches and deletes structure by handle
//
// Input:       IN UINT16  Handle
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
DeleteStructureByHandle(
    IN UINT16       Handle
)
{
    EFI_STATUS      Status;
    UINT8           *StructurePtr = SmbiosDataTable;

    TRACE((-1, "***  SMBIOS - DeleteStructureByHandle. Handle = %x  ***\n", Handle));

    if (FindStructureHandle(&StructurePtr, Handle)) {
        TRACE((-1, "Deleting structure type %x\n", ((SMBIOS_STRUCTURE_HEADER*)StructurePtr)->Type));
        Status = UpdateSmbiosTable(
                        DELETE_STRUCTURE,
                        StructurePtr,
                        0,
                        0,
                        0
                        );
    }
    else {
        TRACE((-1, "Structure not found\n"));
        Status = EFI_NOT_FOUND;
    }

    TRACE((-1, ":::  SMBIOS - Exit DeleteStructureByHandle. Status = %r  :::\n", Status));
    return Status;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   ReadStructureByHandle
//
// Description: SMBIOS protocol - Searches for a structure with input handle,
//              and return a copy of this structure in BufferPtr if found.
//
// Input:       IN      UINT16      Handle
//              IN OUT  UINT8       **BufferPtr
//              IN OUT  UINT16      *BufferSize
//
// Output:      EFI_STATUS
//
// Modified:
//
// Referrals:
//
// Notes:       Memory will be allocated for the returning structure if
//              structure with input handle is found. Caller is responsible
//              for freeing this memory when done with it.
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS
ReadStructureByHandle(
    IN      UINT16            Handle,
    IN OUT  UINT8             **BufferPtr,
    IN OUT  UINT16            *BufferSize
)
{
    EFI_STATUS    Status;
    UINT8         *StructurePtr = SmbiosDataTable;

    TRACE((-1, "***  SMBIOS - ReadStructureByHandle  ***\n"));

    if (FindStructureHandle(&StructurePtr, Handle)) {
        *BufferSize = GetStructureLength(StructurePtr);
        Status = pBS->AllocatePool(EfiBootServicesData, *BufferSize, (void**)BufferPtr);
        if (Status != EFI_SUCCESS) {
            *BufferPtr = NULL;
            *BufferSize = 0;

            TRACE((-1, "Memory allocation failed. Exit\n"));
            return  EFI_OUT_OF_RESOURCES;
        }
        MemCpy(*BufferPtr, StructurePtr, *BufferSize);

        TRACE((-1, "Exit ReadStructureByHandle\n"));
        return  EFI_SUCCESS;
    }
    else {
        *BufferPtr = NULL;
        *BufferSize = 0;

        TRACE((-1, "Structure not found. Exit\n"));
        return  EFI_INVALID_PARAMETER;
    }
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   ReadStructureByType
//
// Description: SMBIOS protocol - Searches for the (n)th structure of input
//              Type and return a copy of this structure in BufferPtr if found.
//
// Input:       IN      UINT8       Type
//              IN      UINT8       Instance
//              IN OUT  UINT8       **BufferPtr
//              IN OUT  UINT16      *BufferSize
//
// Output:      EFI_STATUS
//
// Modified:
//
// Referrals:
//
// Notes:       Memory will be allocated for the returning structure if
//              structure with input handle is found. Caller is responsible
//              for freeing this memory when done with it.
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS
ReadStructureByType(
    IN      UINT8           Type,
    IN      UINT8           Instance,
    IN OUT  UINT8           **BufferPtr,
    IN OUT  UINT16          *BufferSize
)
{
    EFI_STATUS      Status;
    UINT8           *StructurePtr = SmbiosDataTable;
    UINT8           *FoundStructPtr;

    TRACE((-1, "***  SMBIOS - ReadStructureByType  ***\n"));

    if (FindStructureType(&StructurePtr, &FoundStructPtr, Type, Instance)) {
        *BufferSize = GetStructureLength(FoundStructPtr);
        Status = pBS->AllocatePool(EfiBootServicesData, *BufferSize, (void**)BufferPtr);
        if (Status != EFI_SUCCESS) {
            *BufferPtr = NULL;
            *BufferSize = 0;

            TRACE((-1, "Memory allocation failed. Exit\n"));
            return  EFI_OUT_OF_RESOURCES;
        }
        MemCpy(*BufferPtr, FoundStructPtr, *BufferSize);

        TRACE((-1, ":::  SMBIOS - Exit ReadStructureByType  :::\n"));
        return  EFI_SUCCESS;
    }
    else {
        *BufferPtr = NULL;
        *BufferSize = 0;

        TRACE((-1, "Structure type %x not found\n", Type));
        return  EFI_INVALID_PARAMETER;
    }
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   WriteStructureByHandle
//
// Description: SMBIOS protocol - Overwrite an existing structure by handle
//
// Input:       UINT16  Handle
//              UINT8   *BufferPtr
//              UINT16  BufferSize
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
WriteStructureByHandle(
    IN UINT16   Handle,
    IN UINT8    *BufferPtr,
    IN UINT16   BufferSize
)
{
    EFI_STATUS    Status;

#if WRITE_STRUCTURE_HANDLE_POLICY == 0

    TRACE((-1, "***  SMBIOS - WriteStructureByHandle  ***\n"));

    Status = DeleteStructureByHandle(Handle);
    if (!EFI_ERROR(Status)) {
        CheckForType4AndUpdate(&BufferPtr, &BufferSize);

        Status = UpdateSmbiosTable(
                            ADD_STRUCTURE,
                            NULL,
                            BufferPtr,
                            BufferSize,
                            Handle
                            );
    }

    TRACE((-1, "::: SMBIOS - Exit WriteStructureByHandle. Status = %r  :::\n", Status));
    return Status;

#else

    UINT8       *SmbiosTableCopy;
    UINT8       *TempPtr;
    UINT8       *MemoryPtr;
    UINT16      Size;
#if ( defined(CSM_SUPPORT) && (CSM_SUPPORT != 0) )
    UINT32      Granularity;
#endif                                          // CSM_SUPPORT

    TRACE((-1, "***  SMBIOS - WriteStructureByHandle  ***\n"));

    // Check input buffer for valid structure according to its size
    Status = CheckForValidStructure(BufferPtr, BufferSize);
    if (Status != EFI_SUCCESS) {
        return EFI_PROTOCOL_ERROR;
    }

    MemoryPtr = SmbiosDataTable;
    if (FindStructureHandle(&MemoryPtr, Handle)) {
        // Check for enough space
        Size = GetTotalStructureSize(SmbiosDataTable) - GetStructureLength(MemoryPtr);
        if (BufferSize > (MaximumTableSize - Size)) {
        	if (SmbiosTableAtE000) {
        		// Table can not grow when in E000, so exit
				TRACE((-1, "Not enough space in E000. Exit\n"));
				return  EFI_OUT_OF_RESOURCES;
        	}
        	else {
				Status = DeleteStructureByHandle(Handle);
				if (EFI_ERROR(Status)) {
					TRACE((-1, "Cannot delete handle %x. Exit\n", Handle));
					return EFI_OUT_OF_RESOURCES;
				}
        	}
        }
    }

    // Make copy of the original Smbios Table
    Status = pBS->AllocatePool(
                            EfiBootServicesData,
                            MaximumTableSize,
                            (void**)&SmbiosTableCopy
                            );
    if (EFI_ERROR(Status)) {
        TRACE((-1, "Memory allocation failed. Exit\n"));
        return EFI_OUT_OF_RESOURCES;
    }

    // TempPtr = pointer to copy of original Smbios table
    TempPtr = SmbiosTableCopy;
    MemCpy(TempPtr, SmbiosDataTable, MaximumTableSize);

#if ( defined(CSM_SUPPORT) && (CSM_SUPPORT != 0) )
    if ((LegacyRegionProtocol != NULL) && SmbiosTableAtE000) {
        LegacyRegionProtocol->UnLock (LegacyRegionProtocol,
                                      (UINT32)SmbiosDataTable,
                                      MaximumTableSize,
                                      &Granularity);
    }
#endif                                          // CSM_SUPPORT

    MemoryPtr = SmbiosDataTable;

    if (FindStructureHandle(&MemoryPtr, Handle)) {
	    MemCpy(MemoryPtr, BufferPtr, BufferSize);
		TempPtr += MemoryPtr - SmbiosDataTable;
		TempPtr += GetStructureLength(TempPtr);
		MemoryPtr += GetStructureLength(MemoryPtr);

	    // Copy remaining structures
	    Size = GetRemainingStructuresSize(TempPtr);
	    MemCpy(MemoryPtr, TempPtr, Size);
	}
	else {
        AddStructureByHandle(Handle, BufferPtr, BufferSize);
	}

    pBS->FreePool(SmbiosTableCopy);

    UpdateEPSHeader(pSmbiosTableEntryPoint);

#if ( defined(CSM_SUPPORT) && (CSM_SUPPORT != 0) )
    if ((LegacyRegionProtocol != NULL) && SmbiosTableAtE000) {
        LegacyRegionProtocol->Lock (LegacyRegionProtocol,
                                    (UINT32)SmbiosDataTable,
                                    MaximumTableSize,
                                    &Granularity);
    }
#endif                                          // CSM_SUPPORT

    TRACE((-1, ":::  SMBIOS - Exit WriteStructureByHandle  :::\n"));
    return EFI_SUCCESS;

#endif		                                    // WRITE_STRUCTURE_HANDLE_POLICY
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   UpdateSmbiosTableHeader
//
// Description: SMBIOS protocol - Updates the SMBIOS Table Header
//
// Input:       None
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
UpdateSmbiosTableHeader(VOID)
{
    UpdateEPSHeader(pSmbiosTableEntryPoint);
    return  EFI_SUCCESS;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   FindCsm16Table
//
// Description: Searches for CSM16 Table in F000 segment
//
// Input:       IN OUT  EFI_COMPATIBILITY16_TABLE   **Csm16Table
//
// Output:      EFI_COMPATIBILITY16_TABLE** Csm16Table
//				EFI_STATUS
// Modified:
//
// Referrals:
//
// Notes:
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
#if (defined(ITK_SUPPORT) && (ITK_SUPPORT != 0)) || (SMBIOS_TABLE_LOCATION)
#if (defined(CSM_SUPPORT) && (CSM_SUPPORT != 0))
EFI_STATUS FindCsm16Table(OUT EFI_COMPATIBILITY16_TABLE** Csm16Table){

	UINT32* PtrCsmTable = (UINT32*)0xe0000;

	for( ; PtrCsmTable < (UINT32*)0x100000; PtrCsmTable+=4) {
		if(*PtrCsmTable == (UINT32)'$EFI'){
			*Csm16Table = (EFI_COMPATIBILITY16_TABLE*)PtrCsmTable;
			return EFI_SUCCESS;
		}
    }
	return EFI_NOT_FOUND;
}
#endif
#endif

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   SmbiosE000Alloc
//
// Description: Allocate memory for SMBIOS table in low memory
//
// Input:       IN OUT  UINT8    **TablePtr
//              IN      UINT16   Size
//
// Output:      EFI_STATUS
//              If success, TablePtr points to allocated memory in
//              E000 segment.
//
// Modified:
//
// Referrals:
//
// Notes:
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
#if (defined(ITK_SUPPORT) && (ITK_SUPPORT != 0)) || (SMBIOS_TABLE_LOCATION)
#if (defined(CSM_SUPPORT) && (CSM_SUPPORT != 0))
EFI_STATUS
SmbiosE000Alloc(
    IN OUT  UINT8       **TablePtr,
    IN      UINT16      Size
)
{
    EFI_STATUS                  Status;
	EFI_IA32_REGISTER_SET	    Registers;
	EFI_COMPATIBILITY16_TABLE*  Csm16Table;

    TRACE((-1, "***  SMBIOS - SmbiosE000Alloc  ***\n"));

    if (LegacyBiosProtocol != NULL) {
        MemSet(&Registers, sizeof (EFI_IA32_REGISTER_SET), 0);

        Status = FindCsm16Table(&Csm16Table);
        if (EFI_ERROR (Status)) {
            TRACE((-1, "Csm16 Table not found. Exit\n"));
            return Status;
        }

        Status = LegacyRegionProtocol->UnLock (LegacyRegionProtocol,
                                               0xe0000,
                                               0x20000,
                                               NULL);

        // In case E000-F000 fails to unlock then return error without allocating memory
        if (EFI_ERROR (Status)) {
            TRACE((-1, "Failed to unlock shadow. Exit\n"));
            return Status;
        }

        Registers.X.AX = Compatibility16GetTableAddress;
        Registers.X.BX = E0000_BIT;         // allocate from 0xE0000 64 KB block
        Registers.X.CX = (UINT16)Size;
        Registers.X.DX = 1;                 // alignment

        Status = LegacyBiosProtocol->FarCall86(LegacyBiosProtocol,
                                               Csm16Table->Compatibility16CallSegment,
                                               Csm16Table->Compatibility16CallOffset,
                                               &Registers,
                                               0,
                                               0);

        if (Registers.X.AX) Status = (Registers.X.AX & 0x7fff) | 0x80000000;
        ASSERT_EFI_ERROR(Status);

        if (!EFI_ERROR(Status)) {           // If success
            *TablePtr = (UINT8*)(((UINTN)Registers.X.DS << 4) + Registers.X.BX);
        }

        LegacyRegionProtocol->Lock (LegacyRegionProtocol,
                                    0xe0000,
                                    0x20000,
                                    NULL);
    }
    else {
        TRACE((-1, "No LegacyBiosProtocol. Exit\n"));
        Status = EFI_PROTOCOL_ERROR;
    }

    TRACE((-1, ":::  SMBIOS - Exit SmbiosE000Alloc. Status = %r  :::\n", Status));
    return Status;
}
#endif                                          // CSM_SUPPORT
#endif                                          // ITK_SUPPORT || SMBIOS_TABLE_LOCATION

#if BIOS_LANGUAGE_INFO
//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   AddUpdateType13
//
// Description: Add or update BIOS Language Information structure type 13
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
AddUpdateType13 (VOID)
{
    EFI_STATUS      Status;
    UINT8           i;
    UINT8           j;
    UINT8           *SmbiosTablePtr = SmbiosDataTable;
    UINT8           *TempPtr;
    UINT8           *BufferPtr;
    UINT16          BufferSize;
    UINTN           Size = 0;
    EFI_GUID        guidEfiVar = EFI_GLOBAL_VARIABLE;

//----------------------------------------------------------------------------
//                  ***** BIOS LANGUAGE TYPE 13 Tables *****
//            (Table entries should cover the languages specified
//             in Languages.mak)
//----------------------------------------------------------------------------
#if EFI_SPECIFICATION_VERSION > 0x20000
    #define LANGUAGESIZE 5
    CHAR8   SupportLang[][LANGUAGESIZE] = {
                                "en-US",
                                "fr-FR",
                                "es-ES",
                                "de-DE",
                                "ru-RU",
                                "zh-ch",    // zh-chs
                                "zh-ch",    // zh-cht
                                "ko-KR",
                                "ja-JP",
                                "it-IT",
                                "da-DK",
                                "fi-FI",
                                "nl-NL",
                                "nb-NO",
                                "pt-BR",
                                "sv-FI",
                             };
#else
    #define LANGUAGESIZE 3
    CHAR8   SupportLang[][LANGUAGESIZE] = {
                                "eng",
                                "fra",
                                "spa",
                                "ger",
                                "rus",
                                "zho",
                                "chi",
                                "kor",
                                "jpn",
                                "ita",
                                "dan",
                                "fin",
                                "dut",
                                "nor",
                                "por",
                                "swe",
                             };
#endif                                      // EFI_SPECIFICATION_VERSION
#if BIOS_LANGUAGE_FORMAT
    CHAR8   LangShort[][4] = {  "enUS",
                                "frFR",
                                "esES",
                                "deDE",
                                "ruRU",
                                "zhCN",
                                "zhCN",
                                "koKR",
                                "jaJP",
                                "itIT",
                                "daDK",
                                "fiFI",
                                "nlNL",
                                "noNO",
                                "ptPT",
                                "svSE",
                             };
#else
    CHAR8   LangLong[][16] = {  "en|US|iso8859-1\0",
                                "fr|FR|iso8859-1\0",
                                "es|ES|iso8859-1\0",
                                "de|DE|iso8859-1\0",
                                "ru|RU|iso8859-5\0",
                                "zh|CN|unicode\0",
                                "zh|CN|unicode\0",
                                "ko|KR|unicode\0",
                                "ja|JP|unicode\0",
                                "it|IT|iso8859-1\0",
                                "da|DK|iso8859-1\0",
                                "fi|FI|iso8859-1\0",
                                "nl|NL|iso8859-1\0",
                                "no|NO|iso8859-1\0",
                                "pt|PT|iso8859-1\0",
                                "sv|SE|iso8859-1\0",
                             };
#endif                                          // BIOS_LANGUAGE_FORMAT

    CHAR8           Language[LANGUAGESIZE];         // Current Language
    CHAR8           *Lang = &Language[0];
    CHAR8           LanguageCodes[256];             // Supported Languages - Arbitrary size
    CHAR8           *LangCodes = &LanguageCodes[0];
    UINT8           LangCounts;
//----------------------------------------------------------------------------

    TRACE((-1, "***  SMBIOS - AddUpdateType13  ***\n"));

    Size = sizeof(LanguageCodes);

#if EFI_SPECIFICATION_VERSION > 0x20000             // UEFI 2.1 and later
    Status = GetEfiVariable(L"PlatformLangCodes",
                            &guidEfiVar,
                            NULL,
                            &Size,
                            (void**)&LangCodes);
    if (EFI_ERROR(Status)) {
        TRACE((-1, "Failed to get PlatformLangCodes variable. Exit\n"));
        return;
    }

    LangCounts = (UINT8)((UINT16)Size / (LANGUAGESIZE + 1));    // +1 to compensate for ";" and string terminator

    Size = sizeof(Language) + 1;
    Status = GetEfiVariable(L"PlatformLang",
                            &guidEfiVar,
                            NULL,
                            &Size,
                            (void**)&Lang);
    if (EFI_ERROR(Status)) {
        TRACE((-1, "Failed to get PlatformLang variable. Exit\n"));
        return;
    }

    BufferSize = 1024;

    Status = pBS->AllocatePool(EfiBootServicesData, BufferSize, (void**)&BufferPtr);
    if (EFI_ERROR(Status)) {
        TRACE((-1, "Memory allocation failed. Exit\n"));
        return;
    }

    ((SMBIOS_STRUCTURE_HEADER*)BufferPtr)->Type = 13;
    ((SMBIOS_STRUCTURE_HEADER*)BufferPtr)->Length = sizeof(SMBIOS_BIOS_LANG_INFO);
    ((SMBIOS_BIOS_LANG_INFO*)BufferPtr)->InstallableLang = LangCounts;
    ((SMBIOS_BIOS_LANG_INFO*)BufferPtr)->Flags = BIOS_LANGUAGE_FORMAT;

    pBS->SetMem(((SMBIOS_BIOS_LANG_INFO*)BufferPtr)->Reserved, 15, 0);

    TempPtr = BufferPtr + sizeof(SMBIOS_BIOS_LANG_INFO);

    for (i = 0; i < LangCounts; i++) {
        for (j = 0; j < sizeof(SupportLang)/(LANGUAGESIZE); j++) {
            if (MemCmp(&LangCodes[i * (LANGUAGESIZE + 1)], &SupportLang[j][0], LANGUAGESIZE) == 0) {
#if BIOS_LANGUAGE_FORMAT
                Size = 4;
                MemCpy(TempPtr, &LangShort[j][0], Size);
#else
                Size = Strlen(&LangLong[j][0]);
                MemCpy(TempPtr, &LangLong[j][0], Size);
#endif                                          // BIOS_LANGUAGE_FORMAT

                *(TempPtr + Size) = 0;          // string termination
                break;
            }
        }
        if (MemCmp(&LangCodes[i * (LANGUAGESIZE + 1)], Lang, LANGUAGESIZE) == 0) {
            ((SMBIOS_BIOS_LANG_INFO*)BufferPtr)->CurrentLang = i + 1;
        }
        TempPtr += Size + 1;
    }

#else                                           // UEFI 2.0 and older

    Status = GetEfiVariable(L"LangCodes",
                            &guidEfiVar,
                            NULL,
                            &Size,
                            &LangCodes);
    if (EFI_ERROR(Status)) return;

    LangCounts = (UINT8)(Size / 3);

    Size = sizeof(LanguageCodes);
    Status = GetEfiVariable(L"Lang",
                            &guidEfiVar,
                            NULL,
                            &Size,
                            &Lang);
    if (EFI_ERROR(Status)) return;

    BufferSize = 1024;

    Status = pBS->AllocatePool(EfiBootServicesData, BufferSize, &BufferPtr);
    if (EFI_ERROR(Status)) return;

    ((SMBIOS_STRUCTURE_HEADER*)BufferPtr)->Type = 13;
    ((SMBIOS_STRUCTURE_HEADER*)BufferPtr)->Length = sizeof(SMBIOS_BIOS_LANG_INFO);
    ((SMBIOS_BIOS_LANG_INFO*)BufferPtr)->InstallableLang = LangCounts;
    ((SMBIOS_BIOS_LANG_INFO*)BufferPtr)->Flags = BIOS_LANGUAGE_FORMAT;

    pBS->SetMem(((SMBIOS_BIOS_LANG_INFO*)BufferPtr)->Reserved, 15, 0);

    TempPtr = BufferPtr + sizeof(SMBIOS_BIOS_LANG_INFO);

    for (i = 0; i < LangCounts; i++) {
        for (j = 0; j < sizeof(SupportLang)/3; j++) {
            if (MemCmp(&LangCodes[3 * i], &SupportLang[j][0], 3) == 0) {
#if BIOS_LANGUAGE_FORMAT
                Size = 4;
                MemCpy(TempPtr, &LangShort[j][0], Size);
#else
                Size = Strlen(&LangLong[j][0]);
                MemCpy(TempPtr, &LangLong[j][0], Size);
#endif
                *(TempPtr + Size) = 0;          // string termination
                break;
            }
        }
        if (MemCmp(&LangCodes[3 * i], Lang, 3) == 0) {
            ((SMBIOS_BIOS_LANG_INFO*)BufferPtr)->CurrentLang = i + 1;
        }
        TempPtr += Size + 1;
    }
#endif                                          // EFI_SPECIFICATION_VERSION > 0x20000

    *TempPtr = 0;                               // End of structure

    BufferSize = GetStructureLength(BufferPtr);

    if (FindStructureType(&SmbiosTablePtr, &TempPtr, 13, 1)) {
        ((SMBIOS_STRUCTURE_HEADER*)BufferPtr)->Handle = \
                        ((SMBIOS_STRUCTURE_HEADER*)TempPtr)->Handle;

        // Type 13 exists, overwrite it
        WriteStructureByHandle(
                        ((SMBIOS_STRUCTURE_HEADER*)BufferPtr)->Handle,
                        BufferPtr,
                        BufferSize);
    }
    else {
        // Type 13 not found, add a new one
        AddStructure(BufferPtr, BufferSize);
    }

    pBS->FreePool(BufferPtr);

    TRACE((-1, ":::  SMBIOS - Exit AddUpdateType13  :::\n"));
}
#endif

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   SmbiosDynamicUpdate
//
// Description: Update Processor Information, System Slots, and On-Board
//              Devices Information structures.
//
// Input:       IN EFI_EVENT   Event
//              IN VOID        *Context
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
SmbiosDynamicUpdate (
    IN EFI_EVENT      Event,
    IN VOID           *Context
)
{
    EFI_STATUS                  Status;
    EFI_GUID				    SmbiosGuid = SMBIOS_TABLE_GUID;
#if defined iAMT_SUPPORT && iAMT_SUPPORT == 1
	EFI_EVENT                   SigEvent;
	EFI_GUID                    EfiSmbiosAmtDataGuid = AMT_SMBIOS_GROUP;
#endif
   	EFI_EVENT                   SmbiosTableEvent;
	EFI_GUID                    EfiSmbiosTblPubGuid  = SMBIOS_EFI_TABLE_GROUP;
#if (defined(CSM_SUPPORT) && (CSM_SUPPORT != 0))
	UINTN                       NumberOfHandles;
	EFI_HANDLE                  *HandleBuffer;
#endif

	pBS->CloseEvent(Event);

TRACE((-1, "*** SmbiosDynamicUpdate Entry ***\n"));

#if SMBIOS_DYNAMIC_UPDATE_POLICY == 0
#if (TYPE2_STRUCTURE && UPDATE_BASEBOARD_TYPE2)
    Status = gSmbiosBoardProtocol->SmbiosCreateBaseBoardData();
    ASSERT_EFI_ERROR(Status);
#endif                                          // TYPE2_STRUCTURE && UPDATE_BASEBOARD_TYPE2
#if (TYPE3_STRUCTURE && UPDATE_SYSTEM_CHASSIS_TYPE3)
    Status = gSmbiosBoardProtocol->SmbiosCreateChassisData();
    ASSERT_EFI_ERROR(Status);
#endif                                          // TYPE3_STRUCTURE && UPDATE_SYSTEM_CHASSIS_TYPE3
#if (TYPE4_STRUCTURE && UPDATE_CPU_TYPE4)
    if (UpdateCpuStructure) {
        Status = gSmbiosBoardProtocol->SmbiosCreateCPUData();
        ASSERT_EFI_ERROR(Status);
    }
#endif                                          // TYPE4_STRUCTURE && UPDATE_CPU_TYPE4
#if (TYPE9_STRUCTURE && UPDATE_SLOT_TYPE9)
    Status = gSmbiosBoardProtocol->SmbiosCreateSystemSlotData();
    ASSERT_EFI_ERROR(Status);
#endif                                          // TYPE9_STRUCTURE && UPDATE_SLOT_TYPE9
#if (TYPE10_STRUCTURE && UPDATE_ONBOARD_DEV_TYPE10)
    Status = gSmbiosBoardProtocol->SmbiosCreateOnBoardDevData();
    ASSERT_EFI_ERROR(Status);
#endif                                          // TYPE10_STRUCTURE && UPDATE_ONBOARD_DEV_TYPE10
#if (TYPE22_STRUCTURE && UPDATE_BATTERY_TYPE22)
    if (gSmbiosBoardProtocol->PortableBatteryInfoSupport) {
        Status = gSmbiosBoardProtocol->SmbiosCreateBatteryDevData();
        ASSERT_EFI_ERROR(Status);
    }
#endif                                          // TYPE22_STRUCTURE && UPDATE_BATTERY_TYPE22
#if (TYPE41_STRUCTURE && UPDATE_DEVICE_EXT_TYPE41)
    Status = gSmbiosBoardProtocol->SmbiosCreateOnBoardDevExtInfo();
    ASSERT_EFI_ERROR(Status);
#endif                                          // TYPE41_STRUCTURE && UPDATE_DEVICE_EXT_TYPE41
#endif                                          // SMBIOS_DYNAMIC_UPDATE_POLICY == 0

#if BIOS_LANGUAGE_INFO
    AddUpdateType13();
#endif                                          // BIOS_LANGUAGE_INFO

#if SMBIOS_DYNAMIC_UPDATE_POLICY == 0
TRACE((-1, "*** Before DynamicUpdateStructures (SMBIOS_DYNAMIC_UPDATE_POLICY = 0) ***\n"));
    DynamicUpdateStructures(SmbiosDataTable);
TRACE((-1, "*** After DynamicUpdateStructures (SMBIOS_DYNAMIC_UPDATE_POLICY = 0) ***\n"));
#endif                                          // SMBIOS_DYNAMIC_UPDATE_POLICY

    // Call OEM porting hook in SmbiosBoard.c - OEM can make changes
    // to the SMBIOS table in this hook
    gSmbiosBoardProtocol->OemUpdate();

#if SMBIOS_UPDATE_POLICY == 1
TRACE((-1, "*** Before UpdateStructuresWithNvramData (SMBIOS_UPDATE_POLICY = 1) ***\n"));
    UpdateStructuresWithNvramData(SmbiosDataTable, MaximumTableSize);
TRACE((-1, "*** After UpdateStructuresWithNvramData (SMBIOS_UPDATE_POLICY = 1) ***\n"));
#endif                                          // SMBIOS_UPDATE_POLICY

#if (defined(CSM_SUPPORT) && (CSM_SUPPORT != 0))
#if PI_SPECIFICATION_VERSION < 0x10014
	Status = pBS->LocateHandleBuffer(ByProtocol,
                                     &gEfiLegacyRegionProtocolGuid,
	             					 NULL,
                                     &NumberOfHandles,
                                     &HandleBuffer);

    if (!EFI_ERROR(Status)) {
    	Status = pBS->HandleProtocol(HandleBuffer[0],
                                     &gEfiLegacyRegionProtocolGuid,
    						         &LegacyRegionProtocol);
    	pBS->FreePool(HandleBuffer);
        ASSERT_EFI_ERROR(Status);
    }
#else
	Status = pBS->LocateHandleBuffer(ByProtocol,
                                     &gEfiLegacyRegion2ProtocolGuid,
	             					 NULL,
                                     &NumberOfHandles,
                                     &HandleBuffer);

    if (!EFI_ERROR(Status)) {
    	Status = pBS->HandleProtocol(HandleBuffer[0],
                                     &gEfiLegacyRegion2ProtocolGuid,
    						         &LegacyRegionProtocol);
    	pBS->FreePool(HandleBuffer);
        ASSERT_EFI_ERROR(Status);
    }
#endif                                      // PI_SPECIFICATION_VERSION

	Status = pBS->LocateHandleBuffer(ByProtocol,
                                     &gEfiLegacyBiosProtocolGuid,
	             			         NULL,
                                     &NumberOfHandles,
                                     &HandleBuffer);

    if (!EFI_ERROR(Status)) {
    	Status = pBS->HandleProtocol(HandleBuffer[0],
                                     &gEfiLegacyBiosProtocolGuid,
    	             				 &LegacyBiosProtocol);

    	pBS->FreePool(HandleBuffer);
        ASSERT_EFI_ERROR(Status);
    }

#if (defined(ITK_SUPPORT) && (ITK_SUPPORT != 0)) || (SMBIOS_TABLE_LOCATION)
    {
        UINT8	*SmbiosE000Ptr;

        if (LegacyRegionProtocol != NULL) {
            Status = SmbiosE000Alloc(&SmbiosE000Ptr, MaximumTableSize);

            // If success, relocate table
            if (!EFI_ERROR(Status)) {
                TRACE((-1, "*** SmbiosE000Alloc success ***\n"));
                Status = LegacyRegionProtocol->UnLock(LegacyRegionProtocol,
                                                      (UINT32)SmbiosE000Ptr,
                                                      MaximumTableSize,
                                                      NULL);

                if (!EFI_ERROR(Status)) {
                    TRACE((-1, "*** E000 unlocked, copying Smbios Table to E000 ***\n"));
                    MemCpy(SmbiosE000Ptr, SmbiosDataTable, MaximumTableSize);
                    pBS->FreePool(SmbiosDataTable);
                    SmbiosDataTable = SmbiosE000Ptr;
                    SmbiosTableAtE000 = TRUE;

                    LegacyRegionProtocol->Lock(LegacyRegionProtocol,
                                               (UINT32)SmbiosE000Ptr,
                                               MaximumTableSize,
                                               NULL);
                    TRACE((-1, "*** E000 locked ***\n"));
                }
            }
        }
    }
#endif                                          // ITK_SUPPORT || SMBIOS_TABLE_LOCATION

#if (CSM16_VERSION_MINOR >= 64)
    {
        if (LegacyRegionProtocol != NULL) {
        	LegacyRegionProtocol->UnLock(LegacyRegionProtocol,
    									 0xf0000,
                                         0x10000,
    									 NULL);

            TRACE((-1, "*** F000 unlocked ***\n"));

            Legacy16Data = (LEGACY16_TO_EFI_DATA_TABLE_STRUC*)(UINTN)(0xf0000 + *(UINT16*)0xfff4c);

        	if (*(UINT32*)(0xf0000 + Legacy16Data->Compatibility16TableOfs) == (UINT32)'$EFI') {
                SMBIOS_TABLE_ENTRY_POINT    	*TempPtr;

                TempPtr = pSmbiosTableEntryPoint;
                pSmbiosTableEntryPoint = (SMBIOS_TABLE_ENTRY_POINT*)(0xf0000 + Legacy16Data->SmbiosTableOfs);

                TRACE((-1, "*** Smbios Table Entry Point = %x ***\n", pSmbiosTableEntryPoint));

                MemCpy(pSmbiosTableEntryPoint, TempPtr, sizeof(SMBIOS_TABLE_ENTRY_POINT));
        	}

        	LegacyRegionProtocol->Lock(LegacyRegionProtocol,
    									 0xf0000,
                                         0x10000,
    									 NULL);
        }
    }
#endif                                          // CSM16_VERSION_MINOR >= 64

    TRACE((-1, "*** Installing 16bit PnP Smbios Functions ***\n"));

    Install16bitPnPSmbiosFunctions();
#endif                                          // CSM_SUPPORT

    // Updating EPS Header
    UpdateEPSHeader(pSmbiosTableEntryPoint);

	// Update EFI Configuration Table
	Status = pBS->InstallConfigurationTable(&SmbiosGuid, pSmbiosTableEntryPoint);
    ASSERT_EFI_ERROR(Status);

#if (defined(SB_WAKEUP_TYPE_FN) && (SB_WAKEUP_TYPE_FN == 1))
{
    //
    // If S4/S5 resume, update System Information structure (Type 1)
    // Wake-up Type field with detected wake-up source type.
    //

	UINT8		    *Buffer;
	UINT8		    *FoundPtr = NULL;
    EFI_BOOT_MODE   BootMode;

    BootMode = GetBootMode();

    if ((BootMode == BOOT_ON_S4_RESUME) || (BootMode == BOOT_ON_S5_RESUME)) {
        Buffer = SmbiosDataTable;

        if (FindStructureType(&Buffer, &FoundPtr, 1, 1)) {
            FoundPtr += 0x18;

			if ((UINT32)FoundPtr < 0xfffff) {
				OemRuntimeShadowRamWrite(TRUE);
			}

            *(UINT8*)FoundPtr = getWakeupTypeForSmbios();

            if ((UINT32)FoundPtr < 0xfffff) {
				OemRuntimeShadowRamWrite(FALSE);\
			}
        }
    }
}
#endif                                          // SB_WAKEUP_TYPE_FN

#if defined iAMT_SUPPORT && iAMT_SUPPORT == 1
	Status = pBS->CreateEventEx(
					EVT_NOTIFY_SIGNAL,
					TPL_CALLBACK,
					AmtNotifyEventFunction,
					NULL,
					&EfiSmbiosAmtDataGuid,
					&SigEvent);
    ASSERT_EFI_ERROR(Status);

	pBS->SignalEvent(SigEvent);
	pBS->CloseEvent(SigEvent);
#endif                                          // iAMT_SUPPORT

// Added for TPM
    Status = pBS->CreateEventEx(
					EVT_NOTIFY_SIGNAL,
					TPL_CALLBACK,
					NotifyEventFunction,
					NULL,
					&EfiSmbiosTblPubGuid,
					&SmbiosTableEvent);
    ASSERT_EFI_ERROR(Status);

	pBS->SignalEvent(SmbiosTableEvent);
	pBS->CloseEvent(SmbiosTableEvent);

    TRACE((-1, "::: Exitting SmbiosDynamicUpdate :::\n"));
}

#if SMBIOS_DYNAMIC_UPDATE_POLICY == 1
//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   UpdateDynamicStructures
//
// Description: Update structures dynamically
//
// Input: None
//
// Output: None
//
// Modified:
//
// Referrals:
//
// Notes:
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID
UpdateDynamicStructures(
    VOID)
{
#if UPDATE_BASEBOARD_TYPE2 || \
    UPDATE_SYSTEM_CHASSIS_TYPE3 || \
    UPDATE_CPU_TYPE4 || \
    UPDATE_SLOT_TYPE9 || \
    UPDATE_ONBOARD_DEV_TYPE10 || \
    UPDATE_BATTERY_TYPE22 || \
    UPDATE_DEVICE_EXT_TYPE41
    EFI_STATUS  Status;
#endif

    TRACE((-1, "***  SMBIOS - UpdateDynamicStructures  ***\n"));

#if UPDATE_BASEBOARD_TYPE2
    Status = gSmbiosBoardProtocol->SmbiosCreateBaseBoardData();
    ASSERT_EFI_ERROR(Status);
#endif                                          // UPDATE_BASEBOARD_TYPE2
#if UPDATE_SYSTEM_CHASSIS_TYPE3
    Status = gSmbiosBoardProtocol->SmbiosCreateChassisData();
    ASSERT_EFI_ERROR(Status);
#endif                                          // UPDATE_SYSTEM_CHASSIS_TYPE3
#if UPDATE_CPU_TYPE4
    if (UpdateCpuStructure) {
        Status = gSmbiosBoardProtocol->SmbiosCreateCPUData();
        ASSERT_EFI_ERROR(Status);
    }
#endif                                          // UPDATE_CPU_TYPE4
#if UPDATE_SLOT_TYPE9
    Status = gSmbiosBoardProtocol->SmbiosCreateSystemSlotData();
    ASSERT_EFI_ERROR(Status);
#endif                                          // UPDATE_SLOT_TYPE9
#if UPDATE_ONBOARD_DEV_TYPE10
    Status = gSmbiosBoardProtocol->SmbiosCreateOnBoardDevData();
    ASSERT_EFI_ERROR(Status);
#endif                                          // UPDATE_ONBOARD_DEV_TYPE10
#if UPDATE_BATTERY_TYPE22
    if (gSmbiosBoardProtocol->PortableBatteryInfoSupport) {
        Status = gSmbiosBoardProtocol->SmbiosCreateBatteryDevData();
        ASSERT_EFI_ERROR(Status);
    }
#endif                                          // UPDATE_BATTERY_TYPE22
#if UPDATE_DEVICE_EXT_TYPE41
    Status = gSmbiosBoardProtocol->SmbiosCreateOnBoardDevExtInfo();
    ASSERT_EFI_ERROR(Status);
#endif                                          // UPDATE_DEVICE_EXT_TYPE41

    DynamicUpdateStructures(SmbiosDataTable);

    TRACE((-1, ":::  SMBIOS - Exit UpdateDynamicStructures  :::\n"));
}
#endif

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   SmbiosDriverEntryPoint
//
// Description: SMBIOS driver entry point
//
// Input:       IN EFI_HANDLE           ImageHandle,
//              IN EFI_SYSTEM_TABLE     *SystemTable
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
SmbiosDriverEntryPoint(
	IN EFI_HANDLE               ImageHandle,
	IN EFI_SYSTEM_TABLE         *SystemTable
)
{
    EFI_STATUS                  Status;
    UINT8                       *Buffer = NULL;
    UINT8                       *BufferPtr;
    UINTN                       BufferSize;
    UINT8                       *TempPtr = NULL;
    UINT16                      Size;
    EFI_EVENT                   ReadyToBootEvent;

    InitAmiLib(ImageHandle, SystemTable);

    TRACE((-1, "In SmbiosDriverEntryPoint\n"));

    // Allocate runtime buffer for Smbios Table Entry Point
    pBS->AllocatePool(EfiRuntimeServicesData, sizeof(SMBIOS_TABLE_ENTRY_POINT), &pSmbiosTableEntryPoint);
    MemCpy(pSmbiosTableEntryPoint, &SmbiosEntryPointTable, sizeof(SMBIOS_TABLE_ENTRY_POINT));

    Status = pBS->LocateProtocol(&gEfiSmbiosBoardProtocolGuid,
                                 NULL,
                                 &gSmbiosBoardProtocol);
    ASSERT_EFI_ERROR(Status);

    // Get SMBios Data Structure Image
    Status = LoadRealModeFileSection(&gEfiSmbiosStaticData, \
									EFI_SECTION_FREEFORM_SUBTYPE_GUID, &Buffer, &BufferSize);
	if (EFI_ERROR(Status)) return Status;
    BufferPtr = Buffer;

    // Skip over Section GUID
    BufferPtr += sizeof (EFI_GUID);
    BufferSize -= sizeof (EFI_GUID);

    UpdateType127Handle(BufferPtr);

    SmbiosDataTable = BufferPtr;
    TempPtr = BufferPtr;
    MaximumTableSize = (UINT16)BufferSize;

    // Set UpdateCpuStructure flag to FALSE if CPU type 4 structure does not exist
    Status = ReadStructureByType(4, 1, &TempPtr, &Size);
    if (EFI_ERROR(Status)) {
        // CPU type 4 structure not found
        UpdateCpuStructure = FALSE;
    }
    else {
        UpdateCpuStructure = TRUE;
        pBS->FreePool(TempPtr);                 // TempPtr from ReadStructureByType
    }

    // Update structures with NVRAM data
#if (defined(SmbiosDMIEdit_SUPPORT) && (SmbiosDMIEdit_SUPPORT !=0))
    #if SMBIOS_UPDATE_POLICY == 0
TRACE((-1, "Before UpdateStructuresWithNvramData\n"));
        UpdateStructuresWithNvramData(BufferPtr, BufferSize);
TRACE((-1, "After UpdateStructuresWithNvramData\n"));
    #endif
#endif

	// Allocate Runtime buffer and copy the SMBios Data Structures there
    Status = pBS->AllocatePool(EfiRuntimeServicesData, MaximumTableSize, &SmbiosDataTable);
    ASSERT_EFI_ERROR(Status);
    if (EFI_ERROR(Status)) return Status;

    MemCpy(SmbiosDataTable, BufferPtr, MaximumTableSize);
    pBS->FreePool(Buffer);

#if ( defined(SMBIOS_PI_1_1) && (SMBIOS_PI_1_1 == 1) )
    // Initialize Producer Handle table and set ProducerHandle
    // for each Smbios record to Smbios Driver Image Handle
    InitializeProducerHandleTable(ImageHandle);
#endif

    // Allocate scratch buffer
    pBS->AllocatePool(EfiRuntimeServicesData, BufferSize, &ScratchBufferPtr);
    if (EFI_ERROR(Status)) ScratchBufferPtr = NULL;

    // Updating EPS Header
    UpdateEPSHeader(pSmbiosTableEntryPoint);

#if SMBIOS_DYNAMIC_UPDATE_POLICY == 1
    TRACE((-1, "Before UpdateDynamicStructures\n"));
    // Update dynamic structures
    UpdateDynamicStructures();
    TRACE((-1, "After UpdateDynamicStructures\n"));
#endif

    TRACE((-1, "Registering SmbiosDynamicUpdate callback on ReadyToBoot\n"));
    //
    // Register the event handling function to dynamically update
    // structures.
    //
    Status = CreateReadyToBootEvent(TPL_CALLBACK,
                                    SmbiosDynamicUpdate,
                                    NULL,
                                    &ReadyToBootEvent);
    ASSERT_EFI_ERROR(Status);

    Status = pBS->InstallProtocolInterface(&ImageHandle,
                                          &gEfiSmbiosProtocolGuid,
                                          EFI_NATIVE_INTERFACE,
                                          &SmbiosProtocol);
    ASSERT_EFI_ERROR(Status);

    TRACE((-1, "Exiting SmbiosDriverEntryPoint. Status = %r\n", Status));
    return Status;
}

#if ( defined(CSM_SUPPORT) && (CSM_SUPPORT != 0) )
//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   Install16bitPnPSmbiosFunctions
//
// Description: SMBIOS 16-bit PnP runtime functions installation.
//
// Input:       None
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
Install16bitPnPSmbiosFunctions()
{
	EFI_LEGACY_BIOS_EXT_PROTOCOL    *BiosExtensions = NULL;
    UINTN       Dest;
    UINT32      LockUnlockAddr;
    UINT32      LockUnlockSize;
    EFI_STATUS  Status;
    VOID        *gImage;
    UINTN       ImageSize;
    UINT16      *NewPnPFunctionPtr;

    TRACE((-1, "In Install16bitPnPSmbiosFunctions\n"));

    //
    // Locate 16-bit binary and copy it to F000 segment.
    //
    Status = pBS->LocateProtocol(
        &gEfiLegacyBiosExtProtocolGuid, NULL, &BiosExtensions);
    if (EFI_ERROR(Status)) {
        TRACE((-1, "LegacyBiosExtProtocol not found. Exit\n"));
        return Status;
    }

    Status = BiosExtensions->GetEmbeddedRom(
        CSM16_MODULEID, CSM16_VENDORID, CSM16_PNP_RT_DID, &gImage, &ImageSize);
    if (EFI_ERROR(Status)) {
        TRACE((-1, "Embedded Rom not found. Exit\n"));
        return Status;
    }

    Dest = BiosExtensions->CopyLegacyTable(gImage, (UINT16)ImageSize, 0, 1);
    ASSERT(Dest);

    Legacy16Data = (LEGACY16_TO_EFI_DATA_TABLE_STRUC*)(UINTN)(0xf0000 + *(UINT16*)0xfff4c);
    (UINTN)NewPnPFunctionPtr = 0xf0000 + Legacy16Data->AddedPnpFunctionsOfs;

    if (Dest != NULL) {
        BiosExtensions->UnlockShadow((UINT8*)(UINTN)0xf0000, 0x10000, &LockUnlockAddr, &LockUnlockSize);
        *NewPnPFunctionPtr = (UINT16)Dest;
        BiosExtensions->LockShadow(LockUnlockAddr, LockUnlockSize);

        TRACE((-1, "Exit Install16bitPnPSmbiosFunctions\n"));
        return EFI_SUCCESS;
    }
    else {
        TRACE((-1, "Failed to copy embedded Rom. Exit\n"));
        return EFI_OUT_OF_RESOURCES;
    }
}
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
