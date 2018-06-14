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
// $Header: /Alaska/SOURCE/Modules/CMOS Manager/CMOS Core/CMOS Includes/CmosManager.h 12    6/15/10 2:26p Michaela $
//
// $Revision: 12 $
//
// $Date: 6/15/10 2:26p $
//**********************************************************************
// Revision History
// ----------------
// $Log: /Alaska/SOURCE/Modules/CMOS Manager/CMOS Core/CMOS Includes/CmosManager.h $
// 
// 12    6/15/10 2:26p Michaela
// 
// 11    12/04/09 7:32p Michaela
// 
// 10    7/29/09 10:00a Michaela
// updates Aptio Enhancement EIP 22205
// (no code changes)
// 
// 9     6/15/09 5:11p Michaela
// 
// 8     6/02/09 3:28p Michaela
// For label: 4.6.3_CMOSMGR_11
// 
// 7     11/25/08 3:20p Michaela
// Updates for Label 4.6.3_CMOSMGR_08
// - Assembly macro fixes
// - Added assembly macros
// - Moved loading defaults into DXE phase
// - Updated help file example
// 
// 6     11/17/08 3:51p Michaela
// --CMOS Buffer feature is depreciated
// 
// 5     11/14/08 9:17a Michaela
// **CMOS register variables are changed from UINT8 to UINT16
// 
// 4     11/07/08 5:13p Michaela
// Updated to make CMOS manager available in all phases 
// of the boot process:
// 
// A CMOS API Pointer is maintained in CMOS and accessible
// via provided macros in C and assembly source.
// 
// 3     2/29/08 9:35p Michaela
// - Added recovery path policy
// - fixed other minor bugs
// 
// 2     2/26/08 12:50p Michaela
// Added/modified Helpbuilder headers
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
// Name:    CmosManager.h
//
// Description: Contains the constants, data types and declarations 
//              necessary to support the CMOS manager interface.
//
//---------------------------------------------------------------------------
//<AMI_FHDR_END>


//<AMI_GHDR_START>
//----------------------------------------------------------------------------
//
// Name:    Internal_Interfaces
//
// Description:        
//      The page provides links to descriptions of the internal interfaces 
//      used by the CMOS Manager's subsystems.
//
// Fields:  Phase  Name  Description
// ------------------------------------------------------------------
// All  EFI_CMOS_MANAGER_INTERFACE      Provides general services
//
//----------------------------------------------------------------------------
//<AMI_GHDR_END>


#ifndef _CMOS_MANAGER_H
#define _CMOS_MANAGER_H

#include <Efi.h>
#include <CmosAccess.h>
#include "CmosManagerHob.h"
#include "CmosTypes.h"

typedef struct _EFI_CMOS_MANAGER_INTERFACE EFI_CMOS_MANAGER_INTERFACE;

typedef EFI_STATUS (*CMOS_MANAGER_DISPLAY_TOKEN_TABLE) ( 
    IN EFI_CMOS_MANAGER_INTERFACE       *Manager );

typedef EFI_CMOS_ACCESS_INTERFACE * (*CMOS_MANAGER_GET_ACCESS_INTERFACE) (
    IN EFI_CMOS_MANAGER_INTERFACE       *Manager );
    
typedef EFI_STATUS  (*CMOS_MANAGER_INSTALL_ACCESS_INTERFACE) (
    IN EFI_CMOS_MANAGER_INTERFACE       *Manager );

typedef EFI_STATUS (*CMOS_MANAGER_CALCULATE_CHECKSUM)(
    IN  EFI_CMOS_MANAGER_INTERFACE  *Manager,
    OUT UINT16                      *ChecksumValue );

typedef EFI_STATUS (*CMOS_MANAGER_READ_CHECKSUM)(
    IN  EFI_CMOS_MANAGER_INTERFACE  *Manager,
    OUT UINT16                      *ChecksumValue );
    
typedef EFI_STATUS (*CMOS_MANAGER_WRITE_CHECKSUM)(
    IN  EFI_CMOS_MANAGER_INTERFACE  *Manager,
    OUT UINT16                      ChecksumValue );

typedef EFI_STATUS (*CMOS_MANAGER_CONFIGURE) ( 
    IN EFI_CMOS_MANAGER_INTERFACE       *Manager,
    IN CMOS_CONFIGURATION_SETTING       Setting );
    
typedef VOID (*CMOS_MANAGER_SET_STATUS)(
    IN EFI_CMOS_MANAGER_INTERFACE   *Manager,
    IN CMOS_MANAGER_STATUS          BitMap );

typedef VOID (*CMOS_MANAGER_CLEAR_STATUS)(
    IN EFI_CMOS_MANAGER_INTERFACE   *Manager,
    IN CMOS_MANAGER_STATUS          BitMap );

typedef BOOLEAN (*CMOS_MANAGER_CHECK_STATUS)(
    IN EFI_CMOS_MANAGER_INTERFACE   *Manager,
    IN CMOS_MANAGER_STATUS          BitMap );

typedef BOOLEAN (*CMOS_MANAGER_CHECK_ANY_STATUS)(
    IN EFI_CMOS_MANAGER_INTERFACE   *Manager,
    IN CMOS_MANAGER_STATUS          BitMap );

typedef EFI_STATUS (*CMOS_MANAGER_LOAD_OPTIMAL_DEFAULTS)(
    IN EFI_CMOS_MANAGER_INTERFACE   *Manager );
    
typedef EFI_STATUS (*CMOS_MANAGER_SAVE_API_POINTER_TO_CMOS)(
    IN EFI_CMOS_MANAGER_INTERFACE   *Manager,
    IN EFI_CMOS_ACCESS_INTERFACE    *ApiPointer  );

typedef EFI_STATUS (*CMOS_MANAGER_GET_API_POINTER_FROM_CMOS)(
    IN EFI_CMOS_MANAGER_INTERFACE   *Manager,
    IN EFI_CMOS_ACCESS_INTERFACE    **ApiPointer  );

    
//<AMI_SHDR_START>
//----------------------------------------------------------------------------
//  Name:   EFI_CMOS_MANAGER_INTERFACE
//
//  Description: 
//      This is the internal interface used by subsystems within the CMOS
//      manager module.
//
//  Fields:  Type  Name  Description
//      EFI_CMOS_ACCESS_INTERFACE               Access                      The external interface
//      CMOS_MANAGER_INSTALL_ACCESS_INTERFACE   InstallAccessInterface      Installs the Access PPI or Protocol, depending on the phase (see InstallCmosAccessInterface)
//      CMOS_MANAGER_GET_ACCESS_INTERFACE       GetAccessInterface          Used internally to get a pointer to the Access interface (see GetCmosAccessInterface)
//      EFI_GUID                                AccessGuid                  The Access PPI (or Protocol) GUID
//      EFI_PEI_PPI_DESCRIPTOR                  Ppi[4]                      Descriptors for the PEIMs installed by this module
//      UINT8                                   FirstManagedRegister        First register in the managed space
//      UINT8                                   LastManagedRegister         Last register in the managed space
//      CMOS_TOKEN                              *TokenTable                 All defined tokens
//      UINT16                                  TokenCount                  Entry count for TokenTable (#Tokens + 1)
//      CMOS_REGISTER                           *OptimalDefaultTable        Default values for all managed CMOS addresses
//      UINT16                                  OptimalDefaultCount         Entry count for OptimalDefaultTable
//      CMOS_REGISTER                           *NoChecksumTable            CMOS address of locations not included in the checksum in the managed area
//      UINT16                                  NoChecksumCount             Entry count for NoChecksumTable
//      CMOS_MANAGER_CONFIGURE                  ConfigureManager            Provides means for specifying configurable settings for CMOS manager during PEI/DXE initialization (see CmosConfigureManager)
//      CMOS_CHECKSUM                           Checksum                    Valid checksum after the call to NewCmosManagerInterface()
//      CMOS_MANAGER_CALCULATE_CHECKSUM         CalculateChecksum           Forces calculation of the checksum over the entire managed region
//      CMOS_MANAGER_READ_CHECKSUM              ReadChecksum                Reads checksum from the CMOS checksum location
//      CMOS_MANAGER_WRITE_CHECKSUM             WriteChecksum               Writes the provided checksum to the CMOS checksum location
//      CMOS_MANAGER_LOAD_OPTIMAL_DEFAULTS      LoadOptimalDefaults         Writes default values from the OptimalDefaultTable to all CMOS registers
//      CMOS_MANAGER_STATUS                     ManagerStatus               Bitmap containing various Manager-related status values
//      CMOS_MANAGER_SET_STATUS                 SetStatus                   Sets bits in the ManagerStatus value (see CmosManagerSetStatus)
//      CMOS_MANAGER_CLEAR_STATUS               ClearStatus                 Clears bits in the ManagerStatus value (see CmosManagerClearStatus)
//      CMOS_MANAGER_CHECK_STATUS               CheckStatus                 Returns true if all of the specified bits are "set" in the ManagerStatus value (see CmosManagerCheckStatus)
//      CMOS_MANAGER_CHECK_ANY_STATUS           CheckAnyStatus              Returns true if any of the specified bits are "set" in the ManagerStatus value (see CmosManagerCheckAnyStatus)
//      CMOS_MANAGER_HOB                        *ManagerHob                 Pointer to the HOB defined after permanent memory detection in PEI
//      CMOS_MANAGER_SAVE_API_POINTER_TO_CMOS   SaveApiPointerToCmos        Pointer to the Access interface is maintained in a 4-byte CMOS location
//      CMOS_MANAGER_GET_API_POINTER_FROM_CMOS  GetApiPointerFromCmos       Retrieve pointer to the Access interface from 4-byte CMOS location
//
//----------------------------------------------------------------------------
//<AMI_SHDR_END>

#pragma pack(push, 1)           // force byte alignment
typedef struct _EFI_CMOS_MANAGER_INTERFACE 
{
    // Note: EFI_CMOS_ACCESS_INTERFACE must be first in this structure
    EFI_CMOS_ACCESS_INTERFACE               Access;                 // Access
    CMOS_MANAGER_INSTALL_ACCESS_INTERFACE   InstallAccessInterface;
    CMOS_MANAGER_GET_ACCESS_INTERFACE       GetAccessInterface;
    EFI_GUID                                AccessGuid;
    EFI_PEI_PPI_DESCRIPTOR                  Ppi[4];
    UINT16                                  FirstManagedRegister;
    UINT16                                  LastManagedRegister;
    CMOS_TOKEN                              *TokenTable;            // Tables
    UINT16                                  TokenCount;
    CMOS_REGISTER                           *OptimalDefaultTable;
    UINT16                                  OptimalDefaultCount;
    CMOS_REGISTER                           *NoChecksumTable;
    UINT16                                  NoChecksumCount;
    CMOS_REGISTER                           *UnmanagedTable;
    UINT16                                  UnmanagedTableCount;
    CMOS_MANAGER_CONFIGURE                  ConfigureManager;       // Manager
    CMOS_CHECKSUM                           Checksum;
    CMOS_MANAGER_CALCULATE_CHECKSUM         CalculateChecksum;
    CMOS_MANAGER_READ_CHECKSUM              ReadChecksum;
    CMOS_MANAGER_WRITE_CHECKSUM             WriteChecksum;
    CMOS_MANAGER_LOAD_OPTIMAL_DEFAULTS      LoadOptimalDefaults;
    CMOS_MANAGER_STATUS                     ManagerStatus;
    CMOS_MANAGER_SET_STATUS                 SetStatus;
    CMOS_MANAGER_CLEAR_STATUS               ClearStatus;
    CMOS_MANAGER_CHECK_STATUS               CheckStatus;
    CMOS_MANAGER_CHECK_ANY_STATUS           CheckAnyStatus;
    CMOS_MANAGER_HOB                        *ManagerHob;
    CMOS_MANAGER_SAVE_API_POINTER_TO_CMOS   SaveApiPointerToCmos;
    CMOS_MANAGER_GET_API_POINTER_FROM_CMOS  GetApiPointerFromCmos;
};
#pragma pack(pop)           // force byte alignment

// This is the only exposed internal CMOS manager function
EFI_CMOS_MANAGER_INTERFACE* NewCmosManagerInterface( 
    EFI_PEI_SERVICES                **PeiServices );

#endif  // #ifndef _CMOS_MANAGER_H


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
