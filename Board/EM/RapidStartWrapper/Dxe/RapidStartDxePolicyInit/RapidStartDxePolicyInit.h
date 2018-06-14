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
// $Header: /Alaska/SOURCE/Modules/Intel Fast Flash Standby/iRST_SharkBay/RapidStartWrapper/RapidStartDxePolicyInit/RapidStartDxePolicyInit.h 6     5/13/14 4:55a Joshchou $
//
// $Revision: 6 $
//
// $Date: 5/13/14 4:55a $
//**********************************************************************
// Revision History
// ----------------
// $Log: /Alaska/SOURCE/Modules/Intel Fast Flash Standby/iRST_SharkBay/RapidStartWrapper/RapidStartDxePolicyInit/RapidStartDxePolicyInit.h $
// 
// 6     5/13/14 4:55a Joshchou
// [TAG]  		EIP167032
// [Category]  	Improvement
// [Description]  	Review the variable's attribute, we shouldn't use
// runtime attribute with setup variable.
// [Files]  		RapidStartDxePolicyInit.h
// RapidStartDxePolicyInit.c
// RapidStartDxePolicyInit.cif
// 
// 5     6/21/13 6:00a Joshchou
// [TAG]  		EIP126792
// [Category]  	Bug Fix
// [Severity]  	Minor
// [Symptom]  	Can't do AMI capsule when Intel Rapid Start eanble
// [RootCause]  	CMOS RapidStartFlag does not clear.
// [Solution]  	Clear RapidStartFlag when cold boot.
// 
// 4     1/13/13 7:47a Bensonlai
// [TAG]  		EIPNone
// [Category]  	Improvement
// [Description]  	Disabling the RapidStart while STAT mode in the IDE
// mode
// [Files]  		RapidStartDxePolicyInit.c, RapidStartDxePolicyInit.h,
// RapidStartDxePolicyInit.mak, RapidStartSetup.c, RapidStartSetup.mak,
// RapidStartSetup.sd, RapidStartSetup.sdl
// 
// 3     12/07/12 1:16a Bensonlai
// [TAG]  		None
// [Category]  	Bug Fix
// [Severity]  	Normal
// [Symptom]  	When installed memory size less than HDD partition size of
// teh RapidStart, it still can work.
// [RootCause]  	The RAPID_START_PERSISTENT_DATA wasn't updated in the
// BdsAllDriversConnectedCallback().
// [Solution]  	Get the real total size of memory directly.
// [Files]  		RapidStartDxePolicyInit.c, RapidStartDxePolicyInit.h,
// RapidStartDxePolicyInit.mak
// 
// 2     11/15/12 1:03a Bensonlai
// [TAG]  		None
// [Category]  	Improvement
// [Description]  	Move the RAPID_START_PARTITION_DETECT_BEFORE_SETUP to
// RapidStartDxePolicyInit.c.
// 
// 1     10/15/12 4:40a Bensonlai
// [TAG]  		None
// [Category]  	Improvement
// [Description]  	[Category] Improvement
// [Severity] Important
// [Description] Rename all IFFS sting to Rapid Start.
// [Files] Board\EM\RapidStartWrapper\*.*, ReferenceCode\RapidStart\*.*
// 
// [Category] Improvement
// [Severity] Important
// [Description] Implementation of the LOCK_DISABLE_RAPID_START_IF_NO_SSD
// using EDKII.
// [Files] Board\EM\RapidStartWrapper\Dxe\RapidStartDxePolicyInit\*.*
// [Files]  		RapidStartDxePolicyInit.cif
// RapidStartDxePolicyInit.sdl
// RapidStartDxePolicyInit.mak
// RapidStartDxePolicyInit.h
// RapidStartDxePolicyInit.c
// RapidStartDxePolicyInit.dxs
// RapidStartDxePolicyInit.inf
//
//**********************************************************************
//<AMI_FHDR_START>
//
// Name: RapidStartDxePolicyInit.h
//
// Description:	Header file for the RapidStartDxePolicyInit Driver.
//
//<AMI_FHDR_END>
//**********************************************************************

#ifndef _RAPID_START_DXE_PLATFORM_POLICY_H_
#define _RAPID_START_DXE_PLATFORM_POLICY_H_
//
// External include files do NOT need to be explicitly specified in real EDKII
// environment
//
#if !defined(EDK_RELEASE_VERSION) || (EDK_RELEASE_VERSION < 0x00020000)
#include "EdkIIGlueDxe.h"
#include EFI_PROTOCOL_PRODUCER (RapidStartPlatformPolicy)
#include EFI_PROTOCOL_CONSUMER (DiskInfo)
#include <token.h>
#include "PchRegs.h"
#include "SaAccess.h"
#include "PchPlatformLib.h"
#include <SetupDataDefinition.h>
#define  SYSTEM_CONFIGURATION_GUID { 0xEC87D643, 0xEBA4, 0x4BB5, 0xA1, 0xE5, 0x3F, 0x3E, 0x36, 0xB2, 0x0D, 0xA9 }
EFI_GUID SetupGuid = SYSTEM_CONFIGURATION_GUID;

#if LOCK_DISABLE_RAPID_START_IF_NO_SSD
#define BDS_ALL_DRIVERS_CONNECTED_PROTOCOL_GUID \
    { 0xdbc9fd21, 0xfad8, 0x45b0, 0x9e, 0x78, 0x27, 0x15, 0x88, 0x67, 0xcc, 0x93 }

EFI_GUID gNotifyProtocolGuid             = BDS_ALL_DRIVERS_CONNECTED_PROTOCOL_GUID;
#endif

#ifdef RAPID_START_PARTITION_DETECT_BEFORE_SETUP
#define BDS_ALL_DRIVERS_CONNECTED_PROTOCOL_GUID \
 { 0xdbc9fd21, 0xfad8, 0x45b0, 0x9e, 0x78, 0x27, 0x15, 0x88, 0x67, 0xcc, 0x93 }

#define RAPID_START_PARTITION_STATUS_PROTOCOL_GUID \
 { 0x65639144, 0xd492, 0x4328, 0xa4, 0x98, 0xf4, 0xb5, 0x54, 0x5e, 0x4a, 0x30 }

EFI_GUID    gBdsAllDriversConnectedProtocolGuid = \
        BDS_ALL_DRIVERS_CONNECTED_PROTOCOL_GUID;
EFI_HANDLE  gImageHandle;
#if SYNC_UP_DRIVER_AND_BIOS_VARIABLE
#define  RAPID_START_WRAPPER_SMM_DATA_GUID { 0xc840359f, 0x1c11, 0x4d41,  0x92, 0x4c, 0x89, 0x70, 0x52, 0x22, 0x6a, 0xd4  }
EFI_GUID RapidStartWrapperSmmDataGuid = RAPID_START_WRAPPER_SMM_DATA_GUID;

typedef struct _RAPID_START_WRAPPER_SMM_DATA {
  UINT16                   S3WakeTimerMin;
  UINT8                    EntryOnS3RtcWake;
  UINT8                    EntryOnS3CritBattWake;
} RAPID_START_WRAPPER_SMM_DATA;
#endif
#include <RapidStartData.h>
#include <RapidStartDxeLib.h>
#include <RapidStartAhciReg.h>
//AMI_OVERRIDE_FOR_RAPID_START
#include <RapidStartCommonLib.h>
//AMI_OVERRIDE_FOR_RAPID_START
#endif
//#include "RapidStartPlatformPolicyUpdateDxeLib.h"
#endif

/**
  Initilize Intel RapidStart DXE Platform Policy

  @param[in] ImageHandle - Image handle of this driver.
  @param[in] SystemTable - Global system service table.

  @retval EFI_SUCCESS           Initialization complete.
  @exception EFI_UNSUPPORTED       The chipset is unsupported by this driver.
  @retval EFI_OUT_OF_RESOURCES  Do not have enough resources to initialize the driver.
  @retval EFI_DEVICE_ERROR      Device error, driver exits abnormally.
**/
EFI_STATUS
RapidStartDxePolicyInitEntryPoint (
  IN EFI_HANDLE           ImageHandle,
  IN OUT EFI_SYSTEM_TABLE *SystemTable
  );

#endif

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
