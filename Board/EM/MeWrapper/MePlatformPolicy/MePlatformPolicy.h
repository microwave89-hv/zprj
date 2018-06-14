//*************************************************************************
//*************************************************************************
//**                                                                     **
//**        (C)Copyright 1985-2010, American Megatrends, Inc.            **
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
//
// $Header: /Alaska/SOURCE/Modules/SharkBayRefCodes/ME/MeWrapper/MePlatformPolicy/MePlatformPolicy.h 3     5/13/14 4:02a Tristinchou $
//
// $Revision: 3 $
//
// $Date: 5/13/14 4:02a $
//
//**********************************************************************
// Revision History
// ----------------
// $Log: /Alaska/SOURCE/Modules/SharkBayRefCodes/ME/MeWrapper/MePlatformPolicy/MePlatformPolicy.h $
// 
// 3     5/13/14 4:02a Tristinchou
// [TAG]  		EIPNone
// [Category]  	Improvement
// [Description]  	Fix BPF version check error while using MEBX 9.1
// 
// 2     5/14/12 4:40a Klzhan
// [TAG]  		EIP89952
// [Category]  	Spec Update
// [Severity]  	Important
// [Description]  	Update ME RC 0.56
// [Files]  		MePlatformPolicy.c
// MePlatformPolicy.h
// MePlatformPolicy.sdl
// MePlatformPolicy.mak
// MePlatformPolicy.cif
// 
// 1     2/08/12 1:04a Klzhan
// Initial Check in 
// 
// 5     9/07/11 4:49a Klzhan
// Get thermal reporting data from HOB.
// 
// 4     7/11/11 4:41a Klzhan
// Fix system can't boot on ME FW 1076.
// 
// 3     7/08/11 9:14a Klzhan
// Restore to older ME Platform Policy module part.
// To fix system hangs with other modules.
// 
// 2     7/08/11 4:20a Klzhan
// [TAG]  		EIP64189
// [Category]  	Spec Update
// [Severity]  	Important
// [Description]  	Update ME RC to 0.7
// [Files]  		MePlatformPolicy.c
// MePlatformPolicy.h
// MePlatformPolicy.sdl
// MePlatformPolicy.mak
// MePlatformPolicy.cif
// 
// 1     2/25/11 1:41a Klzhan
// Initial Check-in
// 
// 1     12/03/10 5:09a Klzhan
// Initial Check-in.
// 
//
//**********************************************************************

//<AMI_FHDR_START>
//----------------------------------------------------------------------------
//
// Name:            MePlatformPolicy.h
//
// Description:     
//
//----------------------------------------------------------------------------
//<AMI_FHDR_END>
/*++

This file contains a 'Sample Driver' and is licensed as such
under the terms of your license agreement with Intel or your
vendor.  This file may be modified by the user, subject to  
the additional terms of the license agreement               

--*/

/*++
Copyright (c)  2008 Intel Corporation. All rights reserved
This software and associated documentation (if any) is furnished
under a license and may only be used or copied in accordance
with the terms of the license. Except as permitted by such
license, no part of this software or documentation may be
reproduced, stored in a retrieval system, or transmitted in any
form or by any means without the express written consent of
Intel Corporation.
  
Module Name:

 MePlatformPolicy.h

Abstract:

  
--*/
#ifndef _DXE_ME_PLATFORM_POLICY_H_
#define _DXE_ME_PLATFORM_POLICY_H_

#if !defined(EDK_RELEASE_VERSION) || (EDK_RELEASE_VERSION < 0x00020000)
#include "EdkIIGlueDxe.h"
#endif

#include EFI_PROTOCOL_PRODUCER (MEPlatformPolicy)
#include "PchAccess.h"
#include "token.h"
#include "MeLib.h"
#include "HeciRegs.h"
#include "MeChipset.h"
// Debug #include "MePlatformPolicyUpdateDxeLib.h"

#include EFI_PROTOCOL_DEFINITION    (PciRootBridgeIo)
#include EFI_PROTOCOL_CONSUMER      (MePlatformPolicy)
#include EFI_PROTOCOL_CONSUMER      (MebxProtocol)
#include EFI_GUID_DEFINITION        (MeBiosExtensionSetup)
#if EFI_SPECIFICATION_VERSION<=0x20000
#include EFI_PROTOCOL_DEFINITION    (Hii)
#include EFI_PROTOCOL_DEFINITION    (FormCallBack)
#endif
#define EFI_DRIVER_ENTRY_POINT(x)

#define DIMM_TS_INFO_GUID \
  { \
    0xce673a28, 0x800d, 0x4b4a, 0x83, 0x16, 0x26, 0x61, 0xf9, 0xb3, 0xd9, 0xc6 \
  }

#define HECI_MSG_DELAY    2000000   // show warning msg and stay for 2 seconds.
#ifndef GUID_VARIABLE_DECLARATION
#define GUID_VARIABLE_DECLARATION(Variable, Guid) extern EFI_GUID Variable
#endif
typedef struct{
  UINT8         MeFirmwareInfo;
  UINT32        MeMajor;
  UINT32        MeMinor;
  UINT32        MeHotFix;
  UINT32        MeBuildNo;
} ME_INFO_SETUP_DATA;
#ifndef TS_DIMM1_SMBUS_ADDRESS
#define TS_DIMM1_SMBUS_ADDRESS 0x30
#endif

#ifndef TS_DIMM2_SMBUS_ADDRESS
#define TS_DIMM2_SMBUS_ADDRESS 0x32
#endif

#ifndef TS_DIMM3_SMBUS_ADDRESS
#define TS_DIMM3_SMBUS_ADDRESS 0x34
#endif

#ifndef TS_DIMM4_SMBUS_ADDRESS
#define TS_DIMM4_SMBUS_ADDRESS 0x36
#endif

#define SETUP_GUID { 0xEC87D643, 0xEBA4, 0x4BB5, 0xA1, 0xE5, 0x3F, 0x3E, 0x36, 0xB2, 0x0D, 0xA9 }

typedef struct _MEBX_DEBUG_FLAGS_ {
  UINT16  Port80 : 1;   ///< Port 80h
  UINT16  Rsvd : 15;    ///< Reserved
} MEBX_DEBUG_FLAGS;

typedef struct _MEBX_OEM_RESOLUTION_SETTINGS_ {
  UINT16  MebxNonUiTextMode : 4;
  UINT16  MebxUiTextMode : 4;
  UINT16  MebxGraphicsMode : 4;
  UINT16  Rsvd : 4;
} MEBX_OEM_RESOLUTION_SETTINGS;

typedef struct {
  UINT16                        BpfVersion;
  UINT8                         CpuReplacementTimeout;
  UINT8                         Reserved[7];
  UINT8                         ActiveRemoteAssistanceProcess;
  UINT8                         CiraTimeout;
  UINT16                        OemFlags;
  MEBX_DEBUG_FLAGS              MebxDebugFlags;
  UINT32                        MeBiosSyncDataPtr;
  UINT32                        UsbKeyDataStructurePtr;
  MEBX_OEM_RESOLUTION_SETTINGS  OemResolutionSettings;
  UINT8                         Reserved3[0x2E];
} MEBX_BPF;

VOID
EFIAPI
ShowMeReportError (
  IN ME_ERROR_MSG_ID            MsgId
  )
/*++

Routine Description:

  Show Me Error message.
  
Arguments:

  MsgId   Me error message ID.

Returns:

  None.
  
--*/
;
#endif

//*************************************************************************
//*************************************************************************
//**                                                                     **
//**        (C)Copyright 1985-2010, American Megatrends, Inc.            **
//**                                                                     **
//**                       All Rights Reserved.                          **
//**                                                                     **
//**      5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093           **
//**                                                                     **
//**                       Phone: (770)-246-8600                         **
//**                                                                     **
//*************************************************************************
//*************************************************************************