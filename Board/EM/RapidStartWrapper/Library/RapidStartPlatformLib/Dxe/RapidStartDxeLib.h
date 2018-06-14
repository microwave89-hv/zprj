//**********************************************************************
//**********************************************************************
//**                                                                  **
//**        (C)Copyright 1985-2012, American Megatrends, Inc.         **
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
// $Header: /Alaska/SOURCE/Modules/Intel Fast Flash Standby/iRST_SharkBay/RapidStartWrapper/RapidStartDxeLib/RapidStartDxeLib.h 2     3/14/14 9:56a Joshchou $
//
// $Revision: 2 $
//
// $Date: 3/14/14 9:56a $
//**********************************************************************
// Revision History
// ----------------
// $Log: /Alaska/SOURCE/Modules/Intel Fast Flash Standby/iRST_SharkBay/RapidStartWrapper/RapidStartDxeLib/RapidStartDxeLib.h $
// 
// 2     3/14/14 9:56a Joshchou
// 
// 1     10/15/12 4:41a Bensonlai
// [TAG]  		None
// [Category]  	Improvement
// [Description]  	[Category] Improvement
// [Severity] Important
// [Description] Rename all IFFS sting to Rapid Start.
// [Files] Board\EM\RapidStartWrapper\*.*, ReferenceCode\RapidStart\*.*
// 
// [Files]  		RapidStartDxeLib.cif
// RapidStartDxeLib.sdl
// RapidStartDxeLib.mak
// RapidStartDxeLib.c
// RapidStartDxeLib.h
// RapidStartDxeLib.inf
//
//**********************************************************************
//<AMI_FHDR_START>
//
// Name: RapidStartDxeLib.h
//
// Description: RapidStart Dxe Platform Library header file.
//
//<AMI_FHDR_END>
//**********************************************************************

#ifndef _RAPID_START_DXE_LIB_H_
#define _RAPID_START_DXE_LIB_H_
#if !defined(EDK_RELEASE_VERSION) || (EDK_RELEASE_VERSION < 0x00020000)
#include EFI_PROTOCOL_CONSUMER (RapidStartPlatformPolicy)
#endif

#define RAPID_START_PART_TYPE_MBR 0x84  /* Hibernation partition -- APM 1.1f */
///
/// Partition Name: Intel RapidStart Reserved
/// GUID: D3BFE2DE-3DAF-11DF-BA40-E3A556D89593
///
#define RAPID_START_GPT_GUID \
  { \
    0xD3BFE2DE, 0x3DAF, 0x11DF, 0xba, 0x40, 0xe3, 0xa5, 0x56, 0xd8, 0x95, 0x93 \
  }

/**
  Search if any type of RapidStart Store partition present

  This function will search all connected/initialized SSD and see if any valid and
  supported Rapid Start Store present or not. It will scan both GPT and MBR type
  partitions and return the required information for accessing Rapid Start Store.
  If no valid/supported Rapid Start Store found the Rapid Start will be disabled.
  The method and algorithm for searching Rapid Start Store could be implemented by
  platform design.

  @param[in] RapidStartPolicy  - RapidStart Platform Policy protocol
  @param[out] StoreSectors     - Size of RapidStart store partition
  @param[out] StoreLbaAddr     - Address of RapidStart store partition
  @param[out] StoreSataPort    - Port number for RapidStart store partition

  @retval EFI_SUCCESS   - GPT or MBR type RapidStart Store found
  @retval EFI_NOT_FOUND - GPT or MBR type RapidStart Store not found
**/
EFI_STATUS
SearchRapidStartStore (
  IN     RAPID_START_PLATFORM_POLICY_PROTOCOL *RapidStartPolicy,
  OUT    UINT32                               *StoreSectors,
  OUT    UINT64                               *StoreLbaAddr,
  OUT    UINT8                                *StoreSataPort
  );

/**
  Generate RapidStart Store UID

  This function will generate a unique ID which will be stored into Rapid Start
  Store for identifying Rapid Start Store changing condition. When Rapid Start
  Store changed during Rapid Start Resume, the Rapid Start Resume should be
  aborted. By default this ID is combining the CPU TSC and HPET counter. This UID
  will only be generated when Rapid Start Persistent Data not present or Rapid
  Start Store has changed in previous resume.

  @retval UINT64 as RapidStart Store UID
**/
UINT64
GenerateRapidStartStoreUid (
  VOID
  );

/**
  Re-enable Hibernation when RapidStart enabled but RapidStart Store not present.

  It's recommended to disable ACPI Hibernate support when Rapid Start feature
  enabled. In this case, if Rapid Start Store not present or invalid (Rapid Start
  will not be executed), ACPI Hibernate should be re-enabled. This function
  required porting to fit platform implementation.
**/
VOID
EnableHibernate (
  VOID
  );
#endif
//*************************************************************************
//*************************************************************************
//**                                                                     **
//**        (C)Copyright 1985-2012, American Megatrends, Inc.            **
//**                                                                     **
//**                       All Rights Reserved.                          **
//**                                                                     **
//**      5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093           **
//**                                                                     **
//**                       Phone: (770)-246-8600                         **
//**                                                                     **
//*************************************************************************
//*************************************************************************
