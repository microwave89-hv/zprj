//**********************************************************************
//**********************************************************************
//**                                                                  **
//**        (C)Copyright 1985-2013, American Megatrends, Inc.         **
//**                                                                  **
//**                       All Rights Reserved.                       **
//**                                                                  **
//**         5555 Oakbrook Pkwy, Suite 200, Norcross, GA 30093        **
//**                                                                  **
//**                       Phone: (770)-246-8600                      **
//**                                                                  **
//**********************************************************************
//**********************************************************************
//**********************************************************************
// $Header: /Alaska/SOURCE/Modules/Legacy Serial Redirection/LegacySredir.h 22    11/18/14 5:30a Anandakrishnanl $
//
// $Revision: 22 $
//
// $Date: 11/18/14 5:30a $
//**********************************************************************
//**********************************************************************
// Revision History
// ----------------
// $Log: /Alaska/SOURCE/Modules/Legacy Serial Redirection/LegacySredir.h $
// 
// 22    11/18/14 5:30a Anandakrishnanl
// [TAG]  		EIP192802
// [Category]  	Improvement
// [Description]  	Support for legacy redirection by UART polling is added
// for platforms in which serial port does not support IRQ on PIC Mode.
// [Files]  		LegacySredir.c,LegacySredir.h,LegacySredir.sdl
// 
// 21    12/10/13 7:13a Divyac
// [TAG]  		EIP146597 
// [Category]  	Bug Fix
// [Severity]  	Important
// [Symptom]  	Build Error in Legacy Serial Redirection for label
// 4.5.5_LegacySredir_37
// [RootCause]  	Modules Which were consuming EFI_LEGACY_SREDIR_PROTOCOL
// had been throwing error, since the Protocol header file LegacySredir.h
// has been updated.
// [Solution]  	Added #define Macros for backward Compatibility
// [Files]  		LegacySredir.h
// 
// 20    12/09/13 5:21a Divyac
// [TAG]  		EIP129549 
// [Category]  	Improvement
// [Description]  	Serial Redirection has dependency on Amilegacy16.bin
// [Files]  		LegacySredir.c, LegacySredir.h, OR_MOD.EQU, SREDIR.ASM
// 
// 19    12/09/13 4:51a Divyac
// [TAG]  		EIP146051 
// [Category]  	Improvement
// [Description]  	Refresh Key needs to be configured via SDL token for
// Legacy Serial Redirection.
// [Files]  		LegacySredir.c, LegacySredir_Setup.C, LegacySredir.h,
// Sredir.bin
// 
// 18    2/29/12 11:39p Rameshr
// [TAG]  		EIP82480
// [Category]  	Bug Fix
// [Severity]  	Important
// [Symptom]  	System does not boot to Legacy Devices when Launch Video
// OpRom DISABLED
// [RootCause]  	Temp buffer address is not correct
// [Solution]  	Redirection uses the 0x9F000 are temp buffer to save the
// Video data. It should have been calculated in runtime based on the Base
// memory allocated for sredir.bin
// [Files]  		Legacysredir.c, LegacySredir.h
// 
// 17    2/27/12 6:05a Jittenkumarp
// [TAG]  		EIP81401
// [Category]  	New Feature
// [Description]  	Select Redirection After BIOS POST as BootLoader in
// serial redirection, the behaviour is made same as Core8. 
// [Files]  		LegacySredir.c, LegacySredir.mak, LegacySredir.sdl,
// LegacySredir_Setup.c, LegacySredir.h ,SerialBootCall.asm,
// SredirBootFail.asm,GRAPHREDIR.ASM, INT10REDIR.ASM, OR_MOD.EQU,
// SREDIR.ASM,LegacySredir.cif  
// 
// 16    12/28/11 10:56p Rajeshms
// [TAG]  		EIP65051
// [Category]  	Improvement
// [Description]  	Data passing between EFI to Legacy has been changed in
// Legacy console redirection as we are running out of registers to pass
// parameters from EFI to Legacy.
// [Files]  		LegacySredir.c, LegacySredir.h, LegacySredir_Setup.C,
// SREDIR.ASM, OR_MOD.ASM, OR_MOD.EQU
// 
// 15    11/09/11 11:53p Rajeshms
// [TAG]- EIP 63665
// [Category]-IMPROVEMENT
// [Description]- Install Linux(Legacy OS) through remote. Some Linux
// versions are forced to text mode to redirect and some are redirected in
// graphics mode itself. It might not work for all the Linux versions as
// the Linux kernel's behave differently.
// [Files]- Terminal.sdl, Terminal.uni, Terminal.sd, LegacySredir.c,
// LegacySredir.h, LegacySredir_Setup.c, GRAPHREDIR.ASM, INT10REDIR.ASM,
// OR_MOD.ASM, OR_MOD.EQU, SREDIR.ASM
// 
// 14    8/16/11 4:46p Davidd
// [TAG]           EIP55337
// [Category]      New Feature
// [Description]   Add optional code to clear keyboard buffer at
// ReadyToBoot in Legacy Serial Redirection driver
// [Files]         LegacySredir.c
//                 LegacySredir.h
//                 LegacySredir.sdl
//                 Sredir.asm
// 
// 13    7/13/11 2:40a Rajeshms
// [TAG]- EIP 36444
// [Category]- New Feature
// [Description]- Add Setup option for Various Putty keyPad support in
// Legacy console redirection driver
// [Files]- LegacySredir.c, LegacySredir.h, LegacySredir_Setup.C,
// SREDIR.ASM, KEYREDIR.ASM, OR_MOD.EQU, SREDIR.MAK
// 
// 12    6/14/11 5:38a Rameshr
// [TAG]- EIP 58140
// [Category]- New Feature
// [Description]- Add Setup option for Vt-UTF8 combo key support in Legacy
// console redirection driver 
// [Files]- Sredir.asm, Legacysredir.c, Legacysredir.h,
// Legacysredir_setup.c
// 
// 11    5/03/10 1:22a Rameshr
// Issue:Need to handle different Base Hz values for SerialStatusCode,
// Terminal, and Legacy Serial Redirection.
// Solution: Moved Uart input clock into Core.sdl token and used in all
// the above modules.
// EIP: 37332
// 
// 10    4/13/10 4:15a Rameshr
// Recorder Mode support added
// EIP 36514
// Some of the MMIO COM port has non standard bits implemented. These bits
// are reset to 0 in Sredir.bin
// EIP 37123
// 
// 9     3/05/10 4:43a Rameshr
// 
// 8     3/05/10 4:38a Rameshr
// MMIO COM device support added.
// EIP 33847
// 
// 7     3/05/10 1:33a Rameshr
// Sredir.bin Version added 
// 
// 6     10/23/09 10:47a Yul
// EIP 24167 and EIP 26405
// Serial redirection selection of 80X24 or 80X25 implemented based on 
// setup question instead of BUILD token
// 
// 5     6/29/09 12:12p Rameshr
// Coding Standard and File header updated.
// 
// 4     4/21/09 2:09p Rameshr
// Build problem Resolved
// 
// 3     4/21/09 12:16p Rameshr
// Updated the Legacy console redirection to get the Databits,Parity and
// Stop bits from the Terminal Driver Setup option
// EIP20874-Legacy serial redirection is using hra coded values for
// Databits as 8, Parity as None and Stop bit as 1
// 
// 2     4/17/07 4:43a Rameshraju
// PCIserial support added
// 
//**********************************************************************

//<AMI_FHDR_START>
//****************************************************************************
//
// Name:        LegacySreDir.h
//
// Description: Legacy console redirection Protocol header file
//****************************************************************************
//<AMI_FHDR_END>

#ifndef __LEGACY_SREDIR_PROTOCOL_H__
#define __LEGACY_SREDIR_PROTOCOL_H__
#ifdef __cplusplus
extern "C" {
#endif

#include <EFI.h>

#define AMI_LEGACY_SREDIR_PROTOCOL_GUID \
  { 0xA062CF1F, 0x8473, 0x4aa3, 0x87, 0x93, 0x60, 0x0B, 0xC4, 0xFF, 0xA9, 0xA9 }

#define EFI_LEGACY_SREDIR_PROTOCOL_GUID AMI_LEGACY_SREDIR_PROTOCOL_GUID

#ifndef GUID_VARIABLE_DECLARATION
#define GUID_VARIABLE_DECLARATION(Variable, Guid) extern EFI_GUID Variable
#endif

GUID_VARIABLE_DECLARATION( gAmiLegacySredirProtocolGuid, AMI_LEGACY_SREDIR_PROTOCOL_GUID);
#define gEfiLegacySredirProtocolGuid gAmiLegacySredirProtocolGuid

#ifndef GUID_VARIABLE_DEFINITION
typedef struct _AMI_LEGACY_SREDIR_PROTOCOL AMI_LEGACY_SREDIR_PROTOCOL;

#define SREDIR_VENDORID 0x7
#define SREDIR_DEVICEID 0x9
#define SREDIR_MODULEID 0x3

//<AMI_SHDR_START>
//----------------------------------------------------------------------------
// Name:        AMI_LEGACYSREDIR_TABLE
//
// Desription:  There is a table located within the traditional BIOS.It is located on a 16-byte
//              boundary and provides the physical address of the entry point for the Legacy Redirection
//              functions. These functions provide the platform-specific information that is 
//              required by the generic EfiCompatibility code. The functions are invoked via 
//              thunking by using EFI_LEGACY_BIOS_PROTOCOL.FarCall86() with the 32-bit physical 
//              entry point defined below. 
//
//----------------------------------------------------------------------------
//<AMI_SHDR_END>
#pragma pack(1)
typedef struct _AMI_LEGACYSREDIR_TABLE {
    UINT32      Signature;
    UINT8       Version;
    UINT8       TableChecksum;
    UINT8       TableLength;
    UINT16      SreDirSegment;
    UINT16      SreDirOffset;
    UINT16      SreDirEfiToLegacyOffset;
} AMI_LEGACYSREDIR_TABLE;
#pragma pack()

//<AMI_SHDR_START>
//----------------------------------------------------------------------------
// Name:    AMI_LEGACYSREDIR_FUNCTIONS
//
// Description: This structure consists of functions which are used for Leagcy Redirection
//
// Fields:
//
// LEGACY_SreDirInitializeSerialPort : Initialises the Serial Port
// LEGACY_SerialRedirection          : Starts the Legacy Serial Redirection by hooking the required interrupts
// LEGACY_ReleaseSerialRedirection   : Stops the Legacy Serial Redirection by Releasing the corresponding interrupts
// LEGACY_InvalidFunction_FAR        : Invalid function
//
//----------------------------------------------------------------------------
//<AMI_SHDR_END>

typedef enum {
    LEGACY_SreDirInitializeSerialPort,  // 0000,
    LEGACY_SerialRedirection,           // 0001,
    LEGACY_ReleaseSerialRedirection,    // 0002,
    LEGACY_GetInterruptAddress,         // 0003,
    LEGACY_ClearKbCharBuffer,           // 0004,
    LEGACY_InvalidFunction_FAR,         // 0005
} AMI_LEGACYSREDIR_FUNCTIONS;

//<AMI_SHDR_START>
//----------------------------------------------------------------------------
// Name:       AMI_COM_PARAMETERS
//
// Description: This structure consists of Com parameters and setup values
//              which are used to transfer the data from EFI to Legacy for
//              Legacy Redirection.
//
//
// Notes:       Don't Change this structure,as the same structure is defined in
//              CSM16 Serial Redirection. 
//----------------------------------------------------------------------------
//<AMI_SHDR_END>
#pragma pack(1)
typedef struct _AMI_COM_PARAMETERS {
    UINT32  SdlParameters;
    UINT16  BaseAddress;
    UINT32  MMIOBaseAddress;
    UINT8   SerialIRQ;
    UINT32  Baudrate;
    UINT8   TerminalType;
    UINT8   FlowControl;
    UINT8   DataParityStop;
    UINT8   LegacyOsResolution;
    UINT8   RecorderMode;
    UINT8   VtUtf8;
    UINT8   PuttyKeyPad;
    UINT8   SwSMIValue;
    UINT8   InstallLegacyOSthroughRemote;
    UINT16  SredirBinSize; 

    UINT8   RedirectionAfterBiosPost;
    UINT8   Flag;                    //This is not a setup variable rather than used as 
                                     // a flag to start or stop Serial Redirection
    UINT8   RefreshScreenKey;
    UINT8   SwSMIPort;               // Sw SMI port Address
    UINT8   UartPollingRedirection;
} AMI_COM_PARAMETERS;
#pragma pack()


//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Name:        LEGACY_SREDIR_ENABLE
//
// Description: Enable the Legacy Serial Redirection 
//
// Input:
//  This        Legacy Serial Redirection Protocol address
//
// Output:
//  EFI_SUCCESS     Redirection Enabled 
//  EFI_NOT_FOUND   Redirection Not enabled 
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
typedef EFI_STATUS (EFIAPI *LEGACY_SREDIR_ENABLE) (
    IN AMI_LEGACY_SREDIR_PROTOCOL   *This
);

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Name:        LEGACY_SREDIR_DISABLE
//
// Description: Disable the Legacy Serial Redirection 
//
// Input:
//  This        Legacy Serial Redirection Protocol address
//
// Output:
//  EFI_SUCCESS     Redirection Disabled 
//  EFI_NOT_FOUND   Redirection Not disabled 
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
typedef EFI_STATUS (EFIAPI *LEGACY_SREDIR_DISABLE) (
    IN AMI_LEGACY_SREDIR_PROTOCOL   *This
);

typedef struct _AMI_LEGACY_SREDIR_PROTOCOL {
    LEGACY_SREDIR_ENABLE    EnableLegacySredir;
    LEGACY_SREDIR_DISABLE   DisableLegacySredir;
} AMI_LEGACY_SREDIR_PROTOCOL;

#define EFI_LEGACY_SREDIR_PROTOCOL AMI_LEGACY_SREDIR_PROTOCOL

/****** DO NOT WRITE BELOW THIS LINE *******/
#endif // #ifndef GUID_VARIABLE_DEFINITION
#ifdef __cplusplus
}
#endif
#endif

//**********************************************************************
//**********************************************************************
//**                                                                  **
//**        (C)Copyright 1985-2013, American Megatrends, Inc.         **
//**                                                                  **
//**                       All Rights Reserved.                       **
//**                                                                  **
//**         5555 Oakbrook Pkwy, Suite 200, Norcross, GA 30093        **
//**                                                                  **
//**                       Phone: (770)-246-8600                      **
//**                                                                  **
//**********************************************************************
//**********************************************************************
