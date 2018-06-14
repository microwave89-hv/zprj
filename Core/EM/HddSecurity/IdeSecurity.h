//**********************************************************************
//**********************************************************************
//**                                                                  **
//**        (C)Copyright 1985-2015, American Megatrends, Inc.         **
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
// $Header: /Alaska/SOURCE/Modules/HddSecurity/IdeSecurity.h 13    4/22/15 3:57a Anbuprakashp $
//
// $Revision: 13 $
//
// $Date: 4/22/15 3:57a $
//**********************************************************************
// Revision History
// ----------------
// $Log: /Alaska/SOURCE/Modules/HddSecurity/IdeSecurity.h $
// 
// 13    4/22/15 3:57a Anbuprakashp
// [TAG]  		EIP212319
// [Category]  	Bug Fix
// [Severity]  	Normal
// [Symptom]  	System hang while SW_SMI_AHCI_LOCATE_AHCI_SMM SMI trigger
// after enable SmmChkEn bit
// [RootCause]  	Bootservice call used inside IdeSmm driver which causes
// the Exception
// [Solution]  	Changes made not to use BootService calls inside IdeSmm
// driver
// [Files]  		IdeSecurity.h
// IdeSecurity.c
// IDESMM.c
// 
// 12    10/11/11 1:54a Rameshr
// [TAG]  		EIP69246
// [Category]  	Improvement
// [Description]  	Made the  SECURITY_SUPPORT as the Master token and
// removed the IdeSecurity_Support token.
// [Files]  		IdeSecurity.c, IdeSecurity.h, IdeSecurity.mak,
// IdeSecurity.sdl
// 
// 11    4/06/11 12:53a Rameshr
// [TAG]- EIP 57341
// [Category]-IMPROVEMENT
// [Description]- Added Support for SMM PI 1.1 in HDDSecurity eModule.
// [Files]- IdeSecurity.c , IdeSecurity.h, IdeSecurity.dxs
// 
// 10    10/13/10 4:26a Rameshr
// [TAG] - EIP 43790
// [Category]- BUG FIX
// [Severity]- Minor
// [Symptom] - The IDE_SECURITY_PWNV_GUID in IdeSecurity.h will cause
// compile failed in some case
// [RootCause] - The definition of IDE_SECURITY_PWNV_GUID contains a
// semicolon in the end of line
// [Solution] - Removed the SemiColon in the end of line 
// [Files] - IdeSecurity.h
// 
// 9     9/20/10 4:16a Rameshr
// [TAG]- EIP 44182
// [Category]-IMPROVEMENT
// [Description]- Unable to build the project with HDDSecurity module and
// without AHCI module.
// [Files]- IdeSecurity.h, IdeSmm.c
// 
// 8     2/19/10 12:48p Yul
// Delete the comment out codes.
// 
// 7     1/21/10 12:07p Yul
// Refer to EIP 33848 
// LegacyBios protocol is not needed here.
// 
// 6     1/15/10 10:21a Yul
// Coding Standard
//
// 5     11/25/09 6:03p Krishnakumarg
// Removed Tab spaces to comply with AMI coding standard.
//
// 4     7/14/09 1:55p Pats
// EIP 22925: Request to set HDD password length by token.
// Solution: Token added to IdeSecurity.sdl, and definition removed from
// IdeSecurity.h
//
// 3     4/28/09 6:46p Rameshr
// HDD password support in RAID mode
// EIP:20421
//
// 2     4/11/08 4:28p Rameshraju
// 1)Enter the Emptry string for the master password, will set the default
// OEM password and in setup password status will be not installed.
// 2)If the revision code is not 0, then SecuritySetPassword will use
// revision code from the input parameters.
// 3)HddSecutiyData Nvram variable master password cleared when we set
// user password and user password cleared when we set master password.
// 4)When we disable the password, HddSecutiyData Nvram variable also
// updated properly.
// 5)Password lenght stored in HddSecData structure.
//
// 1     28/02/08 6:40p Anandakrishnanl
// Created new HddSecurity module.  Isolated IdeSecurity and IdeSmm from
// IdeBus driver to be compatable with the AHCI Bus driver.
//
//
//<AMI_FHDR_START>
//----------------------------------------------------------------------------
//
// Name:    <IdeSecurity.h>
//
// Description: This file contains the Includes, Definitions, typedefs,
//              Variable and External Declarations, Structure and
//              function prototypes needed for the IdeSecurity driver
//
//----------------------------------------------------------------------------
//<AMI_FHDR_END>

#ifndef _IdeSecurity_
#define _IdeSecurity_

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
#include "Protocol\PAhciBus.h"
#include <Protocol\ComponentName.h>
#include <Protocol\BootScriptSave.h>
#include <Protocol\SmmBase.h>
#include <Protocol\SmmCommunication.h>
#if defined(PI_SPECIFICATION_VERSION)&&(PI_SPECIFICATION_VERSION>=0x0001000A)
#include <Protocol\SmmControl2.h>
#else
#include <Protocol\SmmControl.h>
#endif
#if ( defined(AhciSrc_SUPPORT) && (AhciSrc_SUPPORT != 0) )
#include <Protocol\AhciSmmProtocol.h>
#endif

#define IDE_SECURITY_PWNV_GUID \
{ 0x69967a8c, 0x1159, 0x4522, 0xaa, 0x89, 0x74, 0xcd, 0xc6, 0xe5, 0x99, 0xa0}

#define EFI_SMM_SAVE_HDD_PASSWORD_GUID \
    { 0xeedcf975, 0x4dd3, 0x4d94, 0x96, 0xff, 0xaa, 0xca, 0x83, 0x53, 0xb8, 0x7b }

#define EFI_SMM_REMOVE_HDD_PASSWORD_GUID \
    { 0xc2b1e795, 0xf9c5, 0x4829, 0x8a, 0x42, 0xc0, 0xb3, 0xfe, 0x57, 0x15, 0x17 }

#define AMI_LOCATE_IDE_AHCI_PROTOCOL_GUID \
    { 0xb3f096e9, 0x2d46, 0x4e8e, 0xa2, 0x2c, 0x7d, 0xe8, 0xb1, 0x6b, 0x3a, 0x5b }

#define HDD_PWD_ENCRYPTION_KEY      "H?p1mA*k920_84o3d^!z@L.x4$kY64"

#define EFI_SEGMENT( _Adr )     (UINT16) ((UINT16) (((UINTN) (_Adr))\
                                                    >> 4) & 0xf000)
#define EFI_OFFSET( _Adr )      (UINT16) (((UINT16) ((UINTN) (_Adr))) & 0xffff)


//###DEBUG  Uncomment the following for Required Debug Level.

//#define   TRACE_IDESMM TRACE

//###DEBUG END

#define     TRACE_IDESMM

#define     ZeroMemory( Buffer, Size ) pBS->SetMem( Buffer, Size, 0 )

// Forward reference for pure ANSI compatability
typedef struct _IDE_BUS_PROTOCOL IDE_BUS_PROTOCOL;

HDD_SECURITY_INIT_PROTOCOL *gHddSecurityInitProtocol;

EFI_GUID gSaveHddPasswordGuid=EFI_SMM_SAVE_HDD_PASSWORD_GUID;
EFI_GUID gRemoveHddPasswordGuid=EFI_SMM_REMOVE_HDD_PASSWORD_GUID;
EFI_GUID gLocateIdeAhciSmmProtocolGuid=AMI_LOCATE_IDE_AHCI_PROTOCOL_GUID;
EFI_GUID gEfiSmmCommunicationProtocolGuid=EFI_SMM_COMMUNICATION_PROTOCOL_GUID;

#pragma pack(1)

typedef struct
{
    UINT8  Bus;
    UINT8  Device;
    UINT8  Function;
    UINT8  Controller;
    UINT32 Reserved;
} EDD_PCI;

typedef struct
{
    UINT16 Base;
    UINT16 Reserved;
    UINT32 Reserved2;
} EDD_LEGACY;

typedef union
{
    EDD_PCI    Pci;
    EDD_LEGACY Legacy;
} EDD_INTERFACE_PATH;

typedef struct
{
    UINT8 Master;
    UINT8 Reserved[15];
} EDD_ATA;

typedef struct
{
    UINT8 Master;
    UINT8 Lun;
    UINT8 Reserved[14];
} EDD_ATAPI;

typedef struct
{
    UINT16 TargetId;
    UINT64 Lun;
    UINT8  Reserved[6];
} EDD_SCSI;

typedef struct
{
    UINT64 SerialNumber;
    UINT64 Reserved;
} EDD_USB;

typedef struct
{
    UINT64 Guid;
    UINT64 Reserved;
} EDD_1394;

typedef struct
{
    UINT64 Wwn;
    UINT64 Lun;
} EDD_FIBRE;

typedef struct
{
    UINT8 bPortNum;
    UINT8 Reserved[15];
} EDD_SATA;

typedef union
{
    EDD_ATA   Ata;
    EDD_ATAPI Atapi;
    EDD_SCSI  Scsi;
    EDD_USB   Usb;
    EDD_1394  FireWire;
    EDD_FIBRE FibreChannel;
    EDD_SATA  Sata;
} EDD_DEVICE_PATH;

typedef struct
{
    UINT16             StructureSize;
    UINT16             Flags;
    UINT32             MaxCylinders;
    UINT32             MaxHeads;
    UINT32             SectorsPerTrack;
    UINT64             PhysicalSectors;
    UINT16             BytesPerSector;
    UINT32             FDPT;
    UINT16             Key;
    UINT8              DevicePathLength;
    UINT8              Reserved1;
    UINT16             Reserved2;
    CHAR8              HostBusType[4];
    CHAR8              InterfaceType[8];
    EDD_INTERFACE_PATH InterfacePath;
    EDD_DEVICE_PATH    DevicePath;
    UINT8              Reserved3;
    UINT8              Checksum;
} EDD_DRIVE_PARAMETERS;

typedef struct _HDDSECDATA
{
    UINT16 UserMaster;
    UINT32 PasswordLength;
    UINT8  HddUserPassword[IDE_PASSWORD_LENGTH];
    UINT8  HddMasterPassword[IDE_PASSWORD_LENGTH];
} HDDSECDATA;

#pragma pack()



EFI_STATUS InstallSecurityInterface (
    IN VOID    *BusInterface,
    IN BOOLEAN ModeFlag );

EFI_STATUS StopSecurityModeSupport (
    IN VOID    *BusInterface,
    IN BOOLEAN ModeFlag );

EFI_STATUS ReturnSecurityStatus (
    IN IDE_SECURITY_PROTOCOL *This,
    UINT16                   *SecurityStatus );

EFI_STATUS SecuritySetPassword (
    IN IDE_SECURITY_PROTOCOL *This,
    UINT16                   Control,
    UINT8                    *Buffer,
    UINT16                   RevisionCode );

EFI_STATUS SecurityUnlockPassword (
    IN IDE_SECURITY_PROTOCOL *This,
    UINT16                   Control,
    UINT8                    *Buffer );

EFI_STATUS SecurityDisablePassword (
    IN IDE_SECURITY_PROTOCOL *This,
    UINT16                   Control,
    UINT8                    *Buffer );

EFI_STATUS SetDefaultMasterPassword (
    IN IDE_SECURITY_PROTOCOL *This );

EFI_STATUS SecuritySetDefaultMasterPassword (
    IN IDE_SECURITY_PROTOCOL *This,
    UINT16                   Control,
    UINT8                    *Buffer,
    UINT16                   RevisionCode );

EFI_STATUS SecurityFreezeLock (
    IN IDE_SECURITY_PROTOCOL *This );

EFI_STATUS SecurityEraseUnit (
    IN IDE_SECURITY_PROTOCOL *This,
    UINT16                   Control,
    UINT8                    *Buffer );

EFI_STATUS ReturnIdePasswordFlags (
    IN IDE_SECURITY_PROTOCOL *This,
    UINT32                   *IdePasswordFlags );

EFI_STATUS SecurityCommonRoutine (
    IN VOID *IdeBusInterface,
    UINT16  Control,
    UINT8   *Buffer,
    UINT8   SecurityCommand,
    UINT16  RevisionCode,
    BOOLEAN ModeFlag );

EFI_STATUS ConnectController (
    IN EFI_HANDLE                                   ControllerHandle,
    IN EFI_HANDLE*DriverImageHandle                 OPTIONAL,
    IN EFI_DEVICE_PATH_PROTOCOL*RemainingDevicePath OPTIONAL,
    IN BOOLEAN                                      Recursive );

EFI_STATUS GatherIdeInfo (
    IN VOID    *BusInterface,
    IN BOOLEAN ModeFlag,
    OUT UINT32 *HddDataId );

EFI_STATUS UpdateIdentifyData (
    IN VOID    *BusInterface,
    IN BOOLEAN ModeFlag );

EFI_STATUS SetHddSecDataInNvram (
    IN VOID *BusInterface,
    UINT32  *HddDataId,
    UINT16  Control,
    UINT8   *Buffer );

EFI_STATUS TransferPwDataFromNvramToSmram (
    IN IDE_SECURITY_PROTOCOL *This );

VOID ConvertHddDataIdToString (
    IN UINT32  DataId,
    OUT CHAR16 *String );

VOID EncodeDecodePassword (
    IN UINT8  *InputString,
    OUT UINT8 *OutputString,
    IN UINT32 StringLength );

EFI_STATUS OEMSetMasterPassword (
    IN IDE_SECURITY_PROTOCOL *This );

EFI_STATUS SmmHDDPasswordInterface (
    IN IDE_SECURITY_PROTOCOL *This,
    UINT16                   Control,
    UINT8                    *Buffer,
    UINT8                    Action );

VOID IdeBusCallbackBootScript (
    IN EFI_EVENT Event,
    IN VOID      *Context );

VOID IdeBusMiscSmmFeatureCallback (
    IN EFI_EVENT Event,
    IN VOID      *Context );

BOOLEAN CheckAhciMode (
    IN IDE_BUS_PROTOCOL *IdeBusInterface );

UINTN EfiValueToString (
    IN OUT CHAR16 *Buffer,
    IN INT64      Value,
    IN UINTN      Flags,
    IN UINTN      Width );

EFI_STATUS CommonNonDataHook (
    IN VOID              *BusInterface,
    IN COMMAND_STRUCTURE CommandStructure,
    IN BOOLEAN           ModeFlag );

EFI_STATUS CommonPioDataHook (
    IN VOID              *BusInterface,
    IN COMMAND_STRUCTURE CommandStructure,
    IN BOOLEAN           ModeFlag );

EFI_STATUS CommonReadWritePioHook (
    IN VOID     *BusInterface,
    IN OUT VOID *Buffer,
    IN UINTN    ByteCount,
    IN UINT64   LBA,
    IN UINT8    ReadWriteCommand,
    IN BOOLEAN  ReadWrite,
    IN BOOLEAN  ModeFlag );

EFI_STATUS CommonWfccHook (
    IN VOID    *BusInterface,
    IN BOOLEAN ModeFlag );

VOID LocateAhciSmmServiceEvent (
    EFI_EVENT Event,
    VOID      *Context );



/****** DO NOT WRITE BELOW THIS LINE *******/
#ifdef __cplusplus
}
#endif

#endif

//**********************************************************************
//**********************************************************************
//**                                                                  **
//**        (C)Copyright 1985-2015, American Megatrends, Inc.         **
//**                                                                  **
//**                       All Rights Reserved.                       **
//**                                                                  **
//**         5555 Oakbrook Pkwy, Suite 200, Norcross, GA 30093        **
//**                                                                  **
//**                       Phone: (770)-246-8600                      **
//**                                                                  **
//**********************************************************************
//**********************************************************************
