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
// $Header: /Alaska/SOURCE/Modules/Intel Fast Flash Standby/iRST_SharkBay/RapidStartWrapper/RapidStartWrapperSmm.h 3     5/13/14 4:56a Joshchou $
//
// $Revision: 3 $
//
// $Date: 5/13/14 4:56a $
//**********************************************************************
// Revision History
// ----------------
// $Log: /Alaska/SOURCE/Modules/Intel Fast Flash Standby/iRST_SharkBay/RapidStartWrapper/RapidStartWrapperSmm.h $
// 
// 3     5/13/14 4:56a Joshchou
// [TAG]  		EIP167032
// [Category]  	Improvement
// [Description]  	Review the variable's attribute, we shouldn't use
// runtime attribute with setup variable.
// [Files]  		RapidStartWrapperSmm.c
// RapidStartWrapperSmm.h
// RapidStartWrapperSmm.cif
// 
// 2     4/15/13 2:37a Bensonlai
// [TAG]  		None
// [Category]  	Bug Fix
// [Severity]  	Important
// [Symptom]  	If users change any item from driver then restore to boot
// setting, our SMI can't distinguish between user's and driver's event.
// [RootCause]  	It's an Intel driver issue.
// [Solution]  	1. Removing the sync up with Rapid Start driver and BIOS
// variable as default.
// 2. Remove our BIOS workaround.
// [Files]  		RapidStartWrapperSmm.sdl, RapidStartWrapperSmm.h,
// RapidStartWrapperSmm.sdl, RapidStartWrapperAcpiTables.sdl,
// RapidStartWrapper.sdl
// 
// 1     12/27/12 2:23a Bensonlai
// [TAG]  		EIP110680
// [Category]  	New Feature
// [Description]  	When iRST application is run under OS, and change
// timer.
// BIOS should update the changed to Setup option as well.
// [Files]  		Board\EM\RapidStartWrapper\Smm\RapidStartWrapperSmm.c
// Board\EM\RapidStartWrapper\Smm\RapidStartWrapperSmm.h
// Board\EM\RapidStartWrapper\Smm\RapidStartWrapperSmm.mak
// Board\EM\RapidStartWrapper\Smm\RapidStartWrapperSmm.dxs
// Board\EM\RapidStartWrapper\Smm\RapidStartWrapperSmm.sdl
// Board\EM\RapidStartWrapper\Smm\RapidStartWrapperSmm.cif
// Board\EM\RapidStartWrapper\AcpiTables\RapidStartWrapperAcpiTables.cif
// Board\EM\RapidStartWrapper\AcpiTables\RapidStartWrapperAcpiTables.sdl
// Board\EM\RapidStartWrapper\AcpiTables\Ssdt\RapidStartWrapper.asl
// Board\EM\RapidStartWrapper\RapidStartSetup\RapidStartSetup.sd
// 
//**********************************************************************
//<AMI_FHDR_START>
//
// Name: RapidStartWrapperSmm.h
//
// Description: Sw SMI for RapidStart Wrapper
//
//<AMI_FHDR_END>
//**********************************************************************

#ifndef _RAPID_START_WRAPPER_SMM_H_
#define _RAPID_START_WRAPPER_SMM_H_

//
// External include files do NOT need to be explicitly specified in real EDKII
// environment
//
#if !defined(EDK_RELEASE_VERSION) || (EDK_RELEASE_VERSION < 0x00020000)
#include "EdkIIGlueDxe.h"
#include "RapidStartData.h"
#include <token.h>
//
// Driver Consumed Protocol Prototypes
//
#include EFI_PROTOCOL_CONSUMER (LoadedImage)
#include EFI_PROTOCOL_DEPENDENCY (SmmBase)
#include EFI_PROTOCOL_DEPENDENCY (SmmSwDispatch)
#include EFI_PROTOCOL_DEPENDENCY (DevicePath)
#include EFI_PROTOCOL_DEPENDENCY (RapidStartGlobalNvsArea)
#include EFI_ARCH_PROTOCOL_DEFINITION (Variable)
#endif

#include <SetupDataDefinition.h>
#define  RAPID_START_WRAPPER_SMM_DATA_GUID { 0xc840359f, 0x1c11, 0x4d41,  0x92, 0x4c, 0x89, 0x70, 0x52, 0x22, 0x6a, 0xd4  }
EFI_GUID RapidStartWrapperSmmDataGuid = RAPID_START_WRAPPER_SMM_DATA_GUID;

#define EFI_SMM_RUNTIME_SERVICES_TABLE_GUID \
    { 0x395c33fe, 0x287f, 0x413e, { 0xa0, 0x55, 0x80, 0x88, 0xc0, 0xe1, 0xd4, 0x3e } }

EFI_GUID                             SmmRtServTableGuid = EFI_SMM_RUNTIME_SERVICES_TABLE_GUID;
EFI_SMM_BASE_PROTOCOL                *mSmmBase;
EFI_SMM_SYSTEM_TABLE                 *mSmst = NULL;
EFI_RUNTIME_SERVICES          	     *mySMMgRT = NULL;
RAPID_START_GLOBAL_NVS_AREA          *mRapidStartGlobalNvs;

//
// Define SMI number of AMI Wrapper
//
#define AMI_RAPID_START_SYNC_VARIABLE_FUNCTION 0x01

typedef struct _RAPID_START_WRAPPER_SMM_DATA {
  UINT16                   S3WakeTimerMin;
  UINT8                    EntryOnS3RtcWake;
  UINT8                    EntryOnS3CritBattWake;
} RAPID_START_WRAPPER_SMM_DATA;
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
