//*************************************************************************
//*************************************************************************
//**                                                                     **
//**        (C)Copyright 1985-2009, American Megatrends, Inc.            **
//**                                                                     **
//**                       All Rights Reserved.                          **
//**                                                                     **
//**      5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093           **
//**                                                                     **
//**                       Phone: (770)-246-8600                         **
//**                                                                     **
//*************************************************************************
//*************************************************************************

//**********************************************************************
// $Header: /Alaska/SOURCE/Modules/CMOS Manager/CMOS Board/CmosBoard.h 12    3/05/10 4:53p Michaela $
// 
// $Revision: 12 $
//
// $Date: 3/05/10 4:53p $
//**********************************************************************
// Revision History
// ----------------
// $Log: /Alaska/SOURCE/Modules/CMOS Manager/CMOS Board/CmosBoard.h $
// 
// 12    3/05/10 4:53p Michaela
// 
// 11    12/04/09 7:30p Michaela
// 
// 10    12/03/09 6:12p Michaela
// updated declarations for CmosMgrIsBsp & CmosMgrIsColdBoot
// 
// 9     7/29/09 9:54a Michaela
// updates Aptio Enhancement EIP 22205
// (no code changes)
// 
// 8     6/15/09 5:10p Michaela
// 
// 7     6/02/09 3:25p Michaela
// For label: 4.6.3_CMOSMGR_11
// 
// 6     2/23/09 6:00p Michaela
// --included AmiCspLib.h for exported SB CMOS access functions
// --ReadWriteSecondBankTranslated is commented as an example
//   declaration for SBCsplib.h
// 
// 5     2/16/09 10:11p Michaela
// added prototype for ReadWriteSecondBankTranslated()
// 
// 4     1/21/09 2:38p Michaela
// update for release 4.6.3_CMOSMGR_11:
// 
// **Removed CMOS_CLOCK_RANGE_INDEX and 
//   CMOS_CLOCK_RANGE_DATA SDL Tokens. 
// **Changed the default value of CMOS_STD_INDEX and 
//   CMOS_STD_DATA to 0x70 and 0x71, respectively. 
//   Updated CMOS_PORT_MAPPING elinks to use 
//   ReadWriteStandardRange() for the 0x0 to 0x7f region. 
// **Added CMOS_MGR_SET_NMI_BIT to specify whether or 
//   not to set the NMI bit for access to 0x0 to 0x7f 
//   region. 
// **Removed ReadWriteClockRange() in CmosBoard.c 
// **Modified ReadWriteStandardRange() in CmosBoard.c 
//   to access the NMI range CMOS, where the NMI bit is 
//   set, as specified by the CMOS_MGR_SET_NMI_BIT 
//   Boolean token. 
// Modified ReadWriteStandardRange() in CmosBoard.c to access the NMI
// range CMOS, where the NMI bit is set, as specified by the
// CMOS_MGR_SET_NMI_BIT Boolean token. 
// 
// 3     1/08/09 10:51a Michaela
//   >Added function headers
//   >Updated function parameter modifiers
//   >renamed and updated to CmosBoard module part
//   >Core/Board SDL Tokens and CMOS Tokens are separated
// 
// 2     11/17/08 4:01p Michaela
// --removed development debugging code
// 
// 1     11/14/08 9:25a Michaela
// **Add support for board-specific access functions
// 
// 7     11/07/08 5:13p Michaela
// Updated to make CMOS manager available in all phases 
// of the boot process:
// 
// A CMOS API Pointer is maintained in CMOS and accessible
// via provided macros in C and assembly source.
// 
// 6     3/25/08 3:04p Michaela
// --deleted UpdateLegacyChecksumStatus
// --Modified SynchronizeLegacyStatusRegisters to 
//   update both battery and checksum status bits
// 
// 5     3/07/08 4:07p Michaela
// Label 4.6.3_CMOSMGR_05 fixes:
// -- write errors to Optimal Defaults buffer before memory detection
// -- CMOS Token table corruption when name strings are disabled
// 
// 4     2/29/08 9:35p Michaela
// - Added recovery path policy
// - fixed other minor bugs
// 
// 3     2/26/08 12:49p Michaela
// Added/modified Helpbuilder headers
// 
// 2     2/22/08 3:20p Olegi
// Renamed some of the equates to avoid the naming collisions.
// 
// 1     2/22/08 2:29p Michaela
// 
// 1     2/04/08 6:00p MichaelA
// Created
// 
//**********************************************************************

//<AMI_FHDR_START>
//---------------------------------------------------------------------------
//
// Name:    CmosAccess.c
//
// Description: Contains the routines that constitute the CMOS access
//              implementation.  This file contains source code that is used
//              for both PEI and DXE phases.
//
//---------------------------------------------------------------------------
//<AMI_FHDR_END>


#ifndef _CMOS_BOARD_H
#define _CMOS_BOARD_H

#include <Efi.h>
#ifdef PEI_COMPILE
    #include <Pei.h>
    #include <AmiPeiLib.h>
    #include <Ppi\ReadOnlyVariable.h>
#else
    #include <AmiDxeLib.h>
#endif
#include <CmosAccess.h>
#include <SspTokens.h>
#include "AmiCspLib.h"
#include "CmosManager.h"
#include "CmosManagerHob.h"

#ifdef MSR_XAPIC_BASE
  #undef MSR_XAPIC_BASE
#endif
#ifdef XAPIC_BASE_BSP_BIT
  #undef XAPIC_BASE_BSP_BIT
#endif
#ifdef XAPIC_BASE_BSP_BIT_MASK
  #undef XAPIC_BASE_BSP_BIT_MASK
#endif

#define MSR_XAPIC_BASE 0x1b                     // standard APIC base MSR
#define XAPIC_BASE_BSP_BIT 8 
#define XAPIC_BASE_BSP_BIT_MASK  (1 << XAPIC_BASE_BSP_BIT)

EFI_STATUS ReadWriteStandardRange (
    IN      EFI_PEI_SERVICES      **PeiServices,  // NULL in DXE phase
    IN      CMOS_ACCESS_TYPE      AccessType,
    IN      UINT16                CmosRegister,
    IN OUT  UINT8                 *CmosParameterValue );



//================================================================
//   Southbridge should implement functions to support access
//   to additional CMOS banks (add the following to SBCspLib.h)
//================================================================
/*
EFI_STATUS ReadWriteSecondBankTranslated (
    IN      EFI_PEI_SERVICES      **PeiServices,  // NULL in DXE phase
    IN      CMOS_ACCESS_TYPE      AccessType,
    IN      UINT16                CmosRegister,
    IN OUT  UINT8                 *CmosParameterValue );
*/

BOOLEAN CmosMgrBatteryIsGood (
    IN  EFI_PEI_SERVICES        **PeiServices );

BOOLEAN CmosMgrIsFirstBoot (
    IN  EFI_PEI_SERVICES        **PeiServices );

BOOLEAN CmosMgrIsBsp(
    IN  EFI_PEI_SERVICES        **PeiServices );

BOOLEAN CmosMgrIsColdBoot(
    IN  EFI_PEI_SERVICES        **PeiServices );

BOOLEAN CmosIsUsable(
    IN  EFI_PEI_SERVICES        **PeiServices );

#endif

//*************************************************************************
//*************************************************************************
//**                                                                     **
//**        (C)Copyright 1985-2009, American Megatrends, Inc.            **
//**                                                                     **
//**                       All Rights Reserved.                          **
//**                                                                     **
//**      5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093           **
//**                                                                     **
//**                       Phone: (770)-246-8600                         **
//**                                                                     **
//*************************************************************************
//*************************************************************************
