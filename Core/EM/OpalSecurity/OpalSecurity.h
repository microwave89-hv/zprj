//*************************************************************************
//*************************************************************************
//**                                                                     **
//**        (C)Copyright 1985-2011, American Megatrends, Inc.            **
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
// $Header: /Alaska/SOURCE/Modules/OpalSecurity/OPALSECURITY/OpalSecurity.h 3     12/21/11 8:37p Rajkumarkc $
//
// $Revision: 3 $
//
// $Date: 12/21/11 8:37p $
//**********************************************************************
// Revision History
// ----------------
// $Log: /Alaska/SOURCE/Modules/OpalSecurity/OPALSECURITY/OpalSecurity.h $
// 
// 3     12/21/11 8:37p Rajkumarkc
// [TAG]         EIP77142
// [Category]    BUG FIX & IMPROVEMENT
// [Description] BUG FIX - Changed Little Endian format to Big Endian
//               format while sending commands.
//               IMPROVEMENT - Added support to Lock the Opal hdd if
//               it's unlocked on Bios POST.
// [Files]       IdeOpalSec.c, AhciOpalSec.c, OpalSecurity.c,
//               OpalSecurity.h, OpalSecurity.sdl
// 
// 2     8/22/11 3:02a Anandakrishnanl
// [TAG]  		EIP62912
// [Category]  	Improvement
// [Description]  	Opal Security Definitions Should be Moved to PIDEBUS.h
// from StorageSecurityProtocol.h
// StorageSecurityProtocol.h included in OPAL security driver module will
// give build error when disabled without sdl token #if
// OpalSecurity_SUPPORT properly placed in Ahcibus and IdeBus drivers. But
// Bus driver should not depend on any tokens. For this reason need to
// move OPAL_SEC_INIT_PROTOCOL_GUID in Pidebus.h
// [Files]  		IdeBus.c
// Pidebus.h
// OpalSecurity.cif
// OpalSecurity.h
// IdeOpalSec.c
// AhciOpalSec.c
// 
// 1     5/19/11 2:07a Anandakrishnanl
// Opal Security Module Initial Check In
//
//<AMI_FHDR_START>
//----------------------------------------------------------------------------
//
// Name: OpalSecurity.h
//
// Description:	This file contains the Includes, Definitions, typedefs, Variable 
// and External Declarations, Structure and function prototypes needed for the 
// OpalSecurity driver
//
//----------------------------------------------------------------------------
//<AMI_FHDR_END>

#ifndef _OpalSecurity_
#define _OpalSecurity_

#ifdef __cplusplus
extern "C" {
#endif

#include <Efi.h>
#include <Token.h>
#include <Dxe.h>
#include <AmiDxeLib.h>
#include "Protocol\PciIo.h"
#include "Protocol\DevicePath.h"
#include "protocol\DriverBinding.h"
#include "protocol\BlockIo.h"
#include "Protocol\PDiskInfo.h"
#include "Protocol\PIDEController.h"
#include "Protocol\PIDEBus.h"
#include "Protocol\StorageSecurityCommand.h"
#include "Protocol\PAhciBus.h"

//
// TCG Storage Security Protocol
//
#define SECURITY_PROTOCOL_INFORMATION                   0x00
#define SECURITY_PROTOCOL_1                             0x01
#define SECURITY_PROTOCOL_2                             0x02
#define SECURITY_PROTOCOL_SDCARD_TRUSTED_FLASH          0xED
#define SECURITY_PROTOCOL_IEEE1667                      0xEE

EFI_STATUS InstallOpalSecurityInterface(
    IN VOID    *BusInterface,
    IN BOOLEAN ModeFlag );

EFI_STATUS UnInstallOpalSecurityInterface(
    IN VOID    *BusInterface,
    IN BOOLEAN ModeFlag );

EFI_STATUS IdeSendData(
    IN EFI_STORAGE_SECURITY_COMMAND_PROTOCOL *This,
    IN UINT32                MediaId,
    IN UINT64                Timeout,
    IN UINT8                 SecurityProtocolId,
    IN UINT16                SecurityProtocolSpecificData,
    IN UINTN                 PayloadBufferSize,
    IN VOID                  *PayloadBuffer );

EFI_STATUS IdeReceiveData(
    IN EFI_STORAGE_SECURITY_COMMAND_PROTOCOL *This,
    IN UINT32                MediaId,
    IN UINT64                Timeout,
    IN UINT8                 SecurityProtocolId,
    IN UINT16                SecurityProtocolSpecificData,
    IN UINTN                 PayloadBufferSize,
    OUT VOID                 *PayloadBuffer,
    OUT UINTN		         *PayloadTransferSize
 );

EFI_STATUS AhciReceiveData(
    IN EFI_STORAGE_SECURITY_COMMAND_PROTOCOL *This,
    IN UINT32                MediaId,
    IN UINT64                Timeout,
    IN UINT8                 SecurityProtocolId,
    IN UINT16                SecurityProtocolSpecificData,
    IN UINTN                 PayloadBufferSize,
    OUT VOID                 *PayloadBuffer,
    OUT UINTN		         *PayloadTransferSize
 );

EFI_STATUS AhciSendData(
    IN EFI_STORAGE_SECURITY_COMMAND_PROTOCOL *This,
    IN UINT32                MediaId,
    IN UINT64                Timeout,
    IN UINT8                 SecurityProtocolId,
    IN UINT16                SecurityProtocolSpecificData,
    IN UINTN                 PayloadBufferSize,
    IN VOID                  *PayloadBuffer 
);

EFI_STATUS 
IssueLockOnResetCommand(
    IN EFI_STORAGE_SECURITY_COMMAND_PROTOCOL *This,
    IN VOID    *BusInterface,
    IN BOOLEAN  ModeFlag
);

EFI_STATUS 
GetAndStoreSecurityProtocolInformation(
    IN EFI_STORAGE_SECURITY_COMMAND_PROTOCOL *This,
    IN VOID    *BusInterface
);

EFI_STATUS 
GetSecurityProtocolInformation(
    IN EFI_STORAGE_SECURITY_COMMAND_PROTOCOL *This,
    IN OUT VOID                *QueryBuffer,
    IN OUT UINTN               *QueryBufferSize
);

EFI_STATUS 
IEEE67TPerReset(
    IN EFI_STORAGE_SECURITY_COMMAND_PROTOCOL *This
);

EFI_STATUS 
IssueTPerResetTcgSilo(
    IN EFI_STORAGE_SECURITY_COMMAND_PROTOCOL *This
);

EFI_STATUS 
NativeTcgTPerReset(
    IN EFI_STORAGE_SECURITY_COMMAND_PROTOCOL *This
);

typedef 
struct _SP0_TRUSTED_RECEIVE_PARAMETER_DATA { 
    UINT8      Reserved[6]; 
    UINT8      ListLengthHigh; 
    UINT8      ListLengthLow; 
    UINT8      SupportedSPList[502]; 
    UINT8      PadBytesHigh; 
    UINT8      PadBytesLow; 
}SP0_TRUSTED_RECEIVE_PARAMETER_DATA;

typedef 
struct _TCG_SILO_TYPE_IDENTIFIER { 
    UINT8      Reserved[2]; 
    UINT8      SiloTypeIdentifierHigh; 
    UINT8      SiloTypeIdentifierLow; 
}TCG_SILO_TYPE_IDENTIFIER;

typedef 
struct _STORAGE_SECURITY_COMMAND_PROTOCOL { 
// Any new member field should be added at bottom of the structure below BusInterface
    EFI_STORAGE_SECURITY_RECEIVE_DATA      ReceiveData; 
    EFI_STORAGE_SECURITY_SEND_DATA         SendData; 
    VOID                                   *BusInterface;
    SP0_TRUSTED_RECEIVE_PARAMETER_DATA     *SupportedProtocolList;
}STORAGE_SECURITY_COMMAND_PROTOCOL;

/****** DO NOT WRITE BELOW THIS LINE *******/
#ifdef __cplusplus
}
#endif

#endif

//*************************************************************************
//*************************************************************************
//**                                                                     **
//**        (C)Copyright 1985-2011, American Megatrends, Inc.            **
//**                                                                     **
//**                       All Rights Reserved.                          **
//**                                                                     **
//**      5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093           **
//**                                                                     **
//**                       Phone: (770)-246-8600                         **
//**                                                                     **
//*************************************************************************
//*************************************************************************