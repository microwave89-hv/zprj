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
// $Header: /Alaska/SOURCE/Modules/CMOS Manager/CMOS Core/CMOS Interfaces/CmosAccess.h 21    12/11/11 8:53p Michaela $
//
// $Revision: 21 $
//
// $Date: 12/11/11 8:53p $
//**********************************************************************
// Revision History
// ----------------
// $Log: /Alaska/SOURCE/Modules/CMOS Manager/CMOS Core/CMOS Interfaces/CmosAccess.h $
// 
// 21    12/11/11 8:53p Michaela
// 
// 20    3/16/11 2:46p Michaela
// 
// 19    6/15/10 4:28p Michaela
// 
// 18    3/05/10 4:54p Michaela
// 
// 17    12/04/09 7:32p Michaela
// 
// 16    11/10/09 9:13p Michaela
// 
// 15    7/29/09 9:58a Michaela
// updates Aptio Enhancement EIP 22205
// (no code changes)
// 
// 14    6/15/09 5:13p Michaela
// 
// 13    6/02/09 3:27p Michaela
// For label: 4.6.3_CMOSMGR_11
// 
// 12    2/16/09 11:19p Michaela
// 
// 11    2/16/09 10:20p Michaela
// - Update LOCATE_CMOS_ACCESS_API_POINTER to use
//   new SDL tokens for index/data port access and 
//   CMOS_NMI_BIT_VALUE to be OR'ed with the index
//   port value.
// - Added AMI headers.
// 
// 10    1/21/09 3:27p Michaela
// Update LOCATE_CMOS_ACCESS_API_POINTER to use
// CMOS_STD_INDEX and CMOS_STD_DATA
// 
// 9     1/08/09 12:53p Michaela
// CmosGetTokenFromRegister() modified to verify register size is 8
// 
// 4     11/25/08 3:52p Michaela
// Updates for Label 4.6.3_CMOSMGR_08
// - Assembly macro fixes
// - Added assembly macros
// - Moved loading defaults into DXE phase
// - Updated help file example
// 
// 8     11/17/08 4:41p Michaela
// --Removed Token Name strings in debug development code
// 
// 7     11/17/08 3:28p Michaela
// -Updated LOCATE_CMOS_ACCESS_API_POINTER macro to
//  initialize the pointer to NULL if the battery is bad
// -added CMOS_ACCESS_TYPE typedef for client code usage
// -including <SspTokens.h>
// -CMOS Buffer feature is depreciated
// 
// 6     11/14/08 9:05a Michaela
// Width of Cmos Register variables changed to 
// UINT16 instead of UINT8
// 
// 5     11/07/08 5:12p Michaela
// Updated to make CMOS manager available in all phases 
// of the boot process:
// 
// A CMOS API Pointer is maintained in CMOS and accessible
// via provided macros in C and assembly source.
// 
// 4     3/07/08 4:08p Michaela
// Label 4.6.3_CMOSMGR_05 fixes:
// -- write errors to Optimal Defaults buffer before memory detection
// -- CMOS Token table corruption when name strings are disabled
// 
// 3     2/29/08 9:36p Michaela
// - Added recovery path policy
// - fixed other minor bugs
// 
// 2     2/26/08 12:47p Michaela
// Added/modified Helpbuilder headers
// 
// 1     2/22/08 2:29p Michaela
// 
// 1     2/06/08 2:23p MichaelA
// Created
// 
//**********************************************************************

//<AMI_FHDR_START>
//---------------------------------------------------------------------------
//
// Name:    CmosAccess.h
//
// Description:    
//      This file provides declarations for CMOS access functions 
//      for reading CMOS memory. 
//
//---------------------------------------------------------------------------
//<AMI_FHDR_END>


//<AMI_GHDR_START>
//----------------------------------------------------------------------------
//
// Name:    Terms
//
// Description:        
//      This page defines/clarifies the implied/intended meaning for the 
//      terminology used in the CMOS Manager module's documentation.
//
// Notes:
// Manager -
//                  Refers to the entire collection of subsystems that compose
//                  the CMOS Manager module, including internal and external 
//                  interfaces.
//
// Access Interface -
//                  The collection of public services (functions/data) provided
//                  by the Manager through the EFI_CMOS_ACCESS_INTERFACE 
//                  PPI/Protocol.
//
// API Pointer -
//                  A CMOS-based EFI_CMOS_ACCESS_INTERFACE pointer that is
//                  maintained until DXE phase.  This pointer can be utilized
//                  via macros defined in an assembly include and/or C-source 
//                  header file.
//
// External/Internal Interface -
//                  The external interface is the set of functions/data 
//                  available to other modules, via the Access Interface.  
//                  The Internal Interface is the set of functions/data 
//                  used by the Manager itself, specifically the 
//                  EFI_CMOS_MANAGER_INTERFACE.  Generally speaking, the 
//                  External Interface is a subset of the Internal Interface.
//
// Client -
//                  A module that locates the Access Interface and uses the 
//                  services provided by the CMOS Manager module via this 
//                  external interface.
//
// Managed CMOS - 
//                  Describes the paradigm of using the CMOS Manager to access
//                  a predefined region of CMOS locations.
//
// Managed Region - 
//                  The region of physical CMOS locations for which CMOS  
//                  Manager provides its allocation/access services.  
//                  This region is represented as a contiguous region of 
//                  locations, where the range is defined by SDL Tokens 
//                  (FIRST_MANAGED_CMOS_ADDRESS and MAX_MANAGED_CMOS_ADDRESS).
//
// CMOS Value -
//                  This is one or more bits of data that will be stored at a
//                  location in CMOS.  The maximum size of a CMOS value is 
//                  8 bits.
//
// CMOS Token -
//                  This is an encoded value that represents the location,
//                  size in bits, and offset within the CMOS byte for a 
//                  particular CMOS value.
//
//----------------------------------------------------------------------------
//<AMI_GHDR_END>

//<AMI_GHDR_START>
//----------------------------------------------------------------------------
//
// Name:    CMOS_Manager_Initialization_and_Usage
//
// Description:        
//      This page provides an outline of the steps required for CMOS Manager 
//      initialization and services usage.
//
// Notes:
//      Overview of CMOS Manager usage:
//
//                  1)  Include CmosAccess.h.
//
//                  2)  Declare a pointer to EFI_CMOS_ACCESS_INTERFACE.
//
//                  3)  Use the appropriate macro to locate the interface,
//                        LOCATE_CMOS_ACCESS_PPI(), 
//                        LOCATE_CMOS_ACCESS_API_POINTER(),
//                        LOCATE_CMOS_ACCESS_PROTOCOL() or
//                        LOCATE_CMOS_ACCESS_SMM_PROTOCOL()
//
//                  4)  Use the interface to access CMOS.
//
//                  Note:   Be sure to check the return value of each call!
//
//----------------------------------------------------------------------------
//<AMI_GHDR_END>

//<AMI_GHDR_START>
//----------------------------------------------------------------------------
//
// Name:    Protocols_and_PPI
//
// Description:        
//      This page provides links to the Protocols and PPI installed by this 
//      module.  These are the external interfaces to the CMOS Manager 
//      module's services.
//
// Fields:  Phase  Name  Description
// ------------------------------------------------------------------
// All  EFI_CMOS_ACCESS_INTERFACE   Client interface installed by CMOS Manager
//
//----------------------------------------------------------------------------
//<AMI_GHDR_END>


//<AMI_GHDR_START>
//----------------------------------------------------------------------------
//
// Name:    Macros
//
// Description:        
//      The page provides links to macros that can be used by CMOS Manager 
//      client modules.
//
// Fields:  Phase  Name  Description
// ------------------------------------------------------------------
// PEI  READ_CMOS_PPI                   Use the CMOS Access PPI to read a value from CMOS using a CMOS token from assembly source
// PEI  WRITE_CMOS_PPI                  Use the CMOS Access PPI to write a value to CMOS using a CMOS token from assembly source
// PEI  READ_CMOS_TOKEN                 Use the CMOS-based API/PPI pointer to read a value from CMOS using a CMOS token from assembly source
// PEI  WRITE_CMOS_TOKEN                Use the CMOS-based API/PPI pointer to write a value to CMOS using a CMOS token from assembly source
// PEI  READ_CMOS_REGISTER              Use the CMOS-based API/PPI pointer to read a value from CMOS using a CMOS token from assembly source
// PEI  WRITE_CMOS_REGISTER             Use the CMOS-based API/PPI pointer to write a value to CMOS using a CMOS token from assembly source
// PEI  LOCATE_CMOS_ACCESS_API_POINTER  Get CMOS-based API/PPI pointer
// PEI  LOCATE_CMOS_ACCESS_PPI          Get CMOS Access PPI pointer
// DXE  LOCATE_CMOS_ACCESS_PROTOCOL     Get CMOS Access Protocol pointer
//
//----------------------------------------------------------------------------
//<AMI_GHDR_END>

#ifndef _CMOS_ACCESS_H
#define _CMOS_ACCESS_H

#include <EFI.h>
#include <Pei.h>
#include <Token.h>
#include <SspTokens.h>

//----------------------------------------------
// The smallest theoretical CMOS token value is
// one bit at CMOS register address 0:
//
//  Token encoding is as follows:
//
//      [2:0] Bit offset (in the CMOS byte)
//      [11:3] CMOS register address (0-511)
//      [15:12] Size (in bits)
//----------------------------------------------
#define MIN_TOKEN_VALUE (1 << 12)   // 4096


// PEI phase interface GUID
//--------------------------------------------------------------
// {CCBF2786-CD6C-4308-BDFA-625870CEBF81}
#define EFI_PEI_CMOS_ACCESS_GUID \
{ 0xccbf2786, 0xcd6c, 0x4308, 0xbd, 0xfa, 0x62, 0x58, 0x70, 0xce, 0xbf, 0x81 }


// DXE phase interface GUID
//--------------------------------------------------------------
// {9851740C-22E0-440D-9090-EF2D71C251C9}
#define EFI_DXE_CMOS_ACCESS_GUID \
{ 0x9851740c, 0x22e0, 0x440d, 0x90, 0x90, 0xef, 0x2d, 0x71, 0xc2, 0x51, 0xc9 }

// SMM interface GUID
//--------------------------------------------------------------
// {E5D3026A-1CA5-40f0-8FB6-4B1AFA3C6EAA}
#define EFI_SMM_CMOS_ACCESS_GUID \
{ 0xe5d3026a, 0x1ca5, 0x40f0, 0x8f, 0xb6, 0x4b, 0x1a, 0xfa, 0x3c, 0x6e, 0xaa }

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Name:    LOCATE_CMOS_ACCESS_PPI
//
// Description:  
//      This Macro calls (*PeiServices)->LocatePpi() to locate the CMOS 
//      access PPI. 
//
// Input:        
//      IN OUT  InterfacePtr - Pointer whose value will be updated
//      OUT     Status - Return value from LocatePpi()
//
// Output:
//
// Modified:
//
// Referrals:
//      (*PeiServices)->LocatePpi
//
// Notes:
//      This macro assumes PeiServices is defined.
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

#define LOCATE_CMOS_ACCESS_PPI(Status, InterfacePtr) { \
    EFI_GUID Guid = EFI_PEI_CMOS_ACCESS_GUID; \
    Status = (*PeiServices)->LocatePpi( PeiServices, &Guid, \
        0, NULL, &InterfacePtr); }


//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Name:    LOCATE_CMOS_ACCESS_PROTOCOL
//
// Description:  
//      This Macro calls pBS->LocateProtocol() to locate the CMOS access 
//      Protocol. 
//
// Input:        
//      IN OUT  InterfacePtr - Pointer whose value will be updated
//      OUT     Status - Return value from LocateProtocol()
//
// Output:
//
// Modified:
//
// Referrals:
//      pBS->LocateProtocol
//
// Notes:
//      This macro assumes pBS is defined.
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

#define LOCATE_CMOS_ACCESS_PROTOCOL(Status, InterfacePtr) { \
    EFI_GUID Guid = EFI_DXE_CMOS_ACCESS_GUID; \
    Status = pBS->LocateProtocol( &Guid, NULL, &InterfacePtr); }


//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Name:    LOCATE_CMOS_ACCESS_SMM_PROTOCOL
//
// Description:  
//      This Macro calls pBS->LocateProtocol() to locate the CMOS access 
//      Protocol for SMM access to CMOS. 
//
// Input:        
//      IN OUT  InterfacePtr - Pointer whose value will be updated
//      OUT     Status - Return value from LocateProtocol()
//
// Output:
//
// Modified:
//
// Referrals:
//      pBS->LocateProtocol
//
// Notes:
//      This macro assumes pBS is defined.
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

#define LOCATE_CMOS_ACCESS_SMM_PROTOCOL(Status, InterfacePtr) { \
    EFI_GUID Guid = EFI_SMM_CMOS_ACCESS_GUID; \
    Status = pBS->LocateProtocol( &Guid, NULL, &InterfacePtr); }


//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Name:    LOCATE_CMOS_ACCESS_API_POINTER
//
// Description:  
//      This Macro initializes InterfacePtr = NULL if the battery is bad. 
//      Otherwise, read the four bytes of the CMOS-based API pointer into 
//      InterfacePtr, starting at CMOS_ACCESS_API_BYTE3.
//
// Input:        
//      IN OUT InterfacePtr - Pointer whose value will be updated
//
// Output:
//
// Modified:
//
// Referrals:
//      IoRead8, IoWrite8
//
// Notes:
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

#define LOCATE_CMOS_ACCESS_API_POINTER( InterfacePtr ) { \
    UINT8 i; UINT32 d = 0;\
    IoWrite8( CMOS_BANK0_INDEX, \
        CMOS_RTC_STATUS_REGISTER | CMOS_NMI_BIT_VALUE );\
    if ( !(IoRead8(CMOS_BANK0_DATA) & (0x80)) )\
        InterfacePtr = (EFI_CMOS_ACCESS_INTERFACE*) NULL;\
    else {\
        for (i=0; i < 4; i++){\
            IoWrite8( CMOS_BANK0_INDEX, \
                (CMOS_ACCESS_API_BYTE3 + i) | CMOS_NMI_BIT_VALUE);\
            d <<= 8; \
            d |= IoRead8(CMOS_BANK0_DATA);\
        }\
        InterfacePtr = (EFI_CMOS_ACCESS_INTERFACE*) d;\
    }\
}

typedef enum _CMOS_ACCESS_TYPE {
    WriteType = 0,
    ReadType = 1,
} CMOS_ACCESS_TYPE;

// Aggregate types
//--------------------------------------------------------------
#pragma pack(push, 1)           // force byte alignment

typedef union _StatusRegisterA
    {
        UINT8  AllBits;
        struct _StatusRegisterAFields {     // [Bits] - Description 
                                            //--------------------------------
            UINT8  RateSelect        :4;    // [3-0] - divider output 
                                            //         frequency
            UINT8  BankControl       :1;    // [4] - selects the bank of CMOS
                                            //       RAM that is accessed 
                                            //       through RTC
            UINT8  SelectDivider     :2;    // [6-5] - time-base frequency is
                                            //         being used
            UINT8  UpdateInProgress  :1;    // [7] - RTC update in progress
                                            //       1 = TRUE
                                            //       0 = FALSE
        } Field;
} STATUS_REGISTER_A_BYTE;


typedef union _Diagnostic
    {
        UINT8  AllBits;     
        struct _DiagnosticFields {      // [Bits] - Description 
            UINT8  Bit1_0           :2; // [1-0] - Reserved
            UINT8  TimeIsInvalid    :1; // [2] - CMOS time status indicator
                                        //         0 = valid 
                                        //         1 = invalid
            UINT8  Bit3             :1; // [3] - Not used
            UINT8  Bit4             :1; // [4] - Not used
            UINT8  Bit5             :1; // [5] - Not used
            UINT8  ChecksumIsBad    :1; // [6] - CMOS checksum status 
                                        //         0 = Checksum is good
                                        //         1 = Checksum is bad
            UINT8  RtcPowerIsBad    :1; // [7] - Real time clock power status
                                        //         0 = has not lost power
                                        //         1 = has lost power      
        } Field;
} DIAGNOSTIC_STATUS_BYTE;

typedef union _Battery
    {
        UINT8  AllBits;
        struct _BatteryFields {     // [Bits] - Description 
            UINT8  Reserved     :7; // [6-0] - Not used
            UINT8  IsGood       :1; // [7] - Valid CMOS RAM flag 
                                    //          0 = CMOS battery dead
                                    //          1 = CMOS battery good
        } Field;
} BATTERY_STATUS_BYTE;

typedef struct _CmosConfigurationStatus
{
                                // Boolean status bits (0=FALSE, 1=TRUE)
    UINT8  IsVirtualized    :1; //  [0] - Optimal defaults buffer
                                //        is being used.
    UINT8  NotUsable        :1; //  [1] - CMOS hardware is not usable
    UINT8  BadBattery       :1; //  [2] - CMOS Battery is bad
    UINT8  BadChecksum      :1; //  [3] - Bad checksum was detected,
                                //        (recovery may have been initiated)
    UINT8  DefaultsLoaded   :1; //  [4] - CMOS default values were loaded
    UINT8  IsFirstBoot      :1; //  [5] - First boot detected 
                                //        (or NVRAM was reset)
    UINT8  Reserved         :2; //  [7-6] - Reserved
} CMOS_CONFIGURATION_STATUS;


//<AMI_SHDR_START>
//----------------------------------------------------------------------------
// Name:   CMOS_STATUS_BYTES
//
// Description: 
//      This structure type is used to define particular CMOS status bytes.
//
// Fields: Type    Name                      Description
// ----------------------------------------------------------------
// UINT8                   DiagnosticStatusRegister Address of the diagnostic status register
// DIAGNOSTIC_STATUS_BYTE  Diagnostic               CMOS register that contains clock & checksum information 
// UINT8                   BatteryStatusRegister    Address of the battery status register
// BATTERY_STATUS_BYTE     Battery                  CMOS register that contains CMOS battery information
// CMOS_STATUS_BYTES       ConfigurationStatus      State information for the CMOS manager's access mechanisms
//
// Notes: 
// The bit-field naming convention affirms the bit-set condition, so that TRUE
// conditions can be tested.  For example, here is one possible usage 
// scenario:
//
//                  CMOS_STATUS_BYTES CmosStatus;
//                  MyGetStatusBytes(&CmosStatus);
//
//                  if (CmosStatus.Diagnostic.Field.ChecksumIsBad)
//                      MyInitiateRecovery();
//
// The union provides access to all the bits of the CMOS byte or to
// a specific data field within the byte:
//
// Battery.AllBits                  All bits of the battery status byte
// Battery.Field.IsGood             Bit is set if battery is good
//
// Diagnostic.AllBits               All bits of the diagnostics status byte
// Diagnostic.Field.TimeIsInvalid   Bit is set if time is invalid
// Diagnostic.Field.ChecksumIsBad   Bit is set if checksum is bad
// Diagnostic.Field.RtcPowerIsBad   Bit is set if real time clock has lost power
//
// ConfigurationStatus.IsVirtualized Bit is set if the optimal defaults buffer is in use
//
//----------------------------------------------------------------------------
//<AMI_SHDR_END>

typedef struct _CMOS_STATUS_BYTES
{
    UINT8                      DiagnosticStatusRegister;  
    DIAGNOSTIC_STATUS_BYTE     Diagnostic;
    UINT8                      BatteryStatusRegister;  
    BATTERY_STATUS_BYTE        Battery;
    CMOS_CONFIGURATION_STATUS  ConfigurationStatus;
}CMOS_STATUS_BYTES;


typedef struct _CMOS_SMM_CONTEXT {
    UINT8   Opcode;         // 0 = Write, 1 = Read
    UINT16  CmosToken;
    UINT8   CmosByte;
    UINT8   Status;         // 0/FALSE => error, 1/TRUE => success
} CMOS_SMM_CONTEXT;


#pragma pack(pop)


typedef struct _EFI_CMOS_ACCESS_INTERFACE EFI_CMOS_ACCESS_INTERFACE;

typedef CHAR8* (*EFI_CMOS_GET_NAME) (
    IN  EFI_CMOS_ACCESS_INTERFACE   *Cmos,
    IN  UINT16                      CmosToken
);

typedef EFI_STATUS (*EFI_CMOS_READ) (
    IN  EFI_CMOS_ACCESS_INTERFACE   *Cmos,
    IN  UINT16                      CmosToken,
    OUT UINT8                       *CmosValue
);

typedef EFI_STATUS (*EFI_CMOS_WRITE) (
    IN  EFI_CMOS_ACCESS_INTERFACE   *Cmos,
    IN  UINT16                      CmosToken,
    IN  UINT8                       CmosValue
);

typedef EFI_STATUS (*EFI_CMOS_READ_STATUS_BYTES) (
    IN  EFI_CMOS_ACCESS_INTERFACE   *Cmos,
    IN  CMOS_STATUS_BYTES           *StatusBytes
);
    
typedef UINT16 (*EFI_CMOS_GET_TOKEN_FROM_REGISTER) (
    IN  EFI_CMOS_ACCESS_INTERFACE   *Cmos,
    IN  UINT16                      CmosRegister 
);

typedef EFI_STATUS (*EFI_CMOS_GET_DATE_TIME) (
    IN  EFI_CMOS_ACCESS_INTERFACE   *Cmos,
    OUT EFI_TIME                    *Time
);

typedef EFI_STATUS (*EFI_CMOS_SET_DATE_TIME) (
    IN  EFI_CMOS_ACCESS_INTERFACE   *Cmos,
    IN  EFI_TIME                    *Time
);

//<AMI_SHDR_START>
//----------------------------------------------------------------------------
//  Name:   EFI_CMOS_ACCESS_INTERFACE
//
//  Description: 
//      This is the external interface to all the functionality provided by  
//      the CMOS Manager to external modules.
//
//  Fields:  Type  Name  Description
//      EFI_PEI_SERVICES                    **PeiServices           pointer to the PEI services table
//      EFI_CMOS_READ                       Read                    read a value from a CMOS register (see CmosRead)
//      EFI_CMOS_WRITE                      Write                   write a value to a CMOS register (see CmosWrite)
//      EFI_CMOS_GET_TOKEN_FROM_REGISTER    GetTokenFromRegister    returns the token from the register address (see CmosGetTokenFromRegister)
//      EFI_CMOS_READ_STATUS_BYTES          ReadCmosStatusBytes     updates a CMOS_STATUS_BYTES structure
//      EFI_CMOS_GET_DATE_TIME              GetTime                 Reads the RTC CMOS registers and updates the EFI_TIME structure output parameter (see CmosGetDateTime)
//      EFI_CMOS_SET_DATE_TIME              SetTime                 Writes the RTC CMOS registers from information in the EFI_TIME input parameter (see CmosSetDateTime)
//      EFI_HANDLE                          *Oem                    provide interface extensibility
//
//  Notes:
//      The user of this interface should check the returns of all functions
//      and take the appropriate action if an error is returned.
//
//      Important!! changes in this structure must also be implemented in
//                  CmosAccess32.inc (EFI_CMOS_ACCESS_INTERFACE struct).
//
//----------------------------------------------------------------------------
//<AMI_SHDR_END>

#pragma pack(push, 1)                   // force byte alignment
typedef struct _EFI_CMOS_ACCESS_INTERFACE 
{
    // This structure must be identical to the one in CmosAccess32.inc
    EFI_PEI_SERVICES                    **PeiServices; // NULL in DXE phase
    EFI_CMOS_READ                       Read;
    EFI_CMOS_WRITE                      Write;
    EFI_CMOS_GET_TOKEN_FROM_REGISTER    GetTokenFromRegister;
    EFI_CMOS_READ_STATUS_BYTES          ReadCmosStatusBytes;
    EFI_CMOS_GET_DATE_TIME              GetTime;
    EFI_CMOS_SET_DATE_TIME              SetTime;
    EFI_HANDLE                          *Oem; // can extend, but should not 
                                              // modify, this structure
};
#pragma pack(pop)

#endif  // #ifndef _CMOS_ACCESS_H


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
