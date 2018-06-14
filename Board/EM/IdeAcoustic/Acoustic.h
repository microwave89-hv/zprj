//**********************************************************************//
//**********************************************************************//
//**                                                                  **//
//**        (C)Copyright 1985-2010, American Megatrends, Inc.         **//
//**                                                                  **//
//**                       All Rights Reserved.                       **//
//**                                                                  **//
//**         5555 Oakbrook Pkwy, Suite 200, Norcross, GA 30093        **//
//**                                                                  **//
//**                       Phone: (770)-246-8600                      **//
//**                                                                  **//
//**********************************************************************//
//**********************************************************************//
//**********************************************************************//
// $Header: /Alaska/SOURCE/Modules/HddAcoustic/Acoustic.h 2     1/05/11 6:32p Pats $
//
// $Revision: 2 $
//
// $Date: 1/05/11 6:32p $
//**********************************************************************
// Revision History
// ----------------
// $Log: /Alaska/SOURCE/Modules/HddAcoustic/Acoustic.h $
// 
// 2     1/05/11 6:32p Pats
// Removed inlcude of SB.h, and all south bridge-specific defines.
// 
// 1     1/05/11 12:22a Rameshr
// Initial check-in for Hdd Acoustic Management Support.
// 
//*************************************************************************
//<AMI_FHDR_START>
//
// Name:        Acoustic.h
//
// Description: Acoustic header file
//
//<AMI_FHDR_END>
//*************************************************************************

#ifndef  _Acoustic_H
#define  _Acoustic_H

#ifdef __cplusplus
extern "C" {
#endif

#include <Token.h>
#include <AmiLib.h>
#include <AmiDxeLib.h>
#include <pci.h>
#include <Setup.h>
#include <Protocol\AcousticProtocol.h>
#include <Protocol\PciIo.h>
#include <Protocol\DevicePath.h>
#include <protocol\BlockIo.h>
#include <Protocol\PDiskInfo.h>
#include <Protocol\PIDEController.h>
#include <Protocol\PIDEBus.h>
#include <Protocol\PciRootBridgeIo.h>
#include <Protocol\DriverBinding.h>
#include <Protocol\PAhciBus.h>

//
// PCI Defines
//
#ifndef PCI_SCC
#define PCI_SCC 0x000A // Sub Class Code Register
#endif
#ifndef PCI_CL_MASS_STOR_SCL_IDE
#define PCI_CL_MASS_STOR_SCL_IDE 0x01 // Ide Mode
#endif
#define MmPciAddress(Base, Bus, Device, Function, Register) \
        ( (UINTN)(Base) + \
          (UINTN)(Bus << 20) + \
          (UINTN)(Device << 15) + \
          (UINTN)(Function << 12) + \
          (UINTN)(Register) )

//
// Constant Defines
//
#define AUTOMATIC_ACOUSTIC_FEATURE_SET_SUPPORTED 0x0200

//
// Function defines
//
EFI_STATUS 
Acoustic_BoardInit (
    IN EFI_HANDLE        ImageHandle,
    IN EFI_SYSTEM_TABLE  *SystemTable 
);

EFI_STATUS 
AcousticEntryPoint (
    IN EFI_HANDLE        ImageHandle,
    IN EFI_SYSTEM_TABLE  *SystemTable 
);

EFI_STATUS
IssueSetFeatureCmd (
    EFI_HANDLE  ControllerHandle,
    EFI_HANDLE  DeviceHandle,
    UINT8       SubCommand,
    UINT8       Mode 
);

extern EFI_GUID gEfiDevicePathProtocolGuid;

/****** DO NOT WRITE BELOW THIS LINE *******/
#ifdef __cplusplus
}
#endif

#endif 

//**********************************************************************//
//**********************************************************************//
//**                                                                  **//
//**        (C)Copyright 1985-2010, American Megatrends, Inc.         **//
//**                                                                  **//
//**                       All Rights Reserved.                       **//
//**                                                                  **//
//**         5555 Oakbrook Pkwy, Suite 200, Norcross, GA 30093        **//
//**                                                                  **//
//**                       Phone: (770)-246-8600                      **//
//**                                                                  **//
//**********************************************************************//
//**********************************************************************//
