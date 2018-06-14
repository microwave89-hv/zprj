//**********************************************************************
//**********************************************************************
//**                                                                  **
//**        (C)Copyright 1985-2013, American Megatrends, Inc.         **
//**                                                                  **
//**                       All Rights Reserved.                       **
//**                                                                  **
//**      5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093        **
//**                                                                  **
//**                       Phone: (770)-246-8600                      **
//**                                                                  **
//**********************************************************************
//**********************************************************************
// $Header: /Alaska/SOURCE/Modules/SharkBayRefCodes/FIT/Dxe/BootGuardDxe.h 2     3/07/13 5:41a Bensonlai $
//
// $Revision: 2 $
//
// $Date: 3/07/13 5:41a $
//**********************************************************************
// Revision History
// ----------------
// $Log: /Alaska/SOURCE/Modules/SharkBayRefCodes/FIT/Dxe/BootGuardDxe.h $
// 
// 2     3/07/13 5:41a Bensonlai
// [TAG]  		EIP117307
// [Category]  	Improvement
// [Description]  	[Boot Guard] Implementation of speed up the post time
// for Chain of Trust
// [Files]  		BootGuardDxe.h, BootGuardPei.c, BootGuardPei.h,
// BpmKmGen.exe, ReserveBootGuardFvMainHashKey.bin
// 
// 1     2/25/13 1:11a Bensonlai
// [TAG]  		EIP114386
// [Category]  	Spec Update
// [Severity]  	Important
// [Description]  	[SBY] Ultrabook for Shark Bay Platform - : Boot Guard
// for 4th Gen Intel Core Processor based on Mobile U-Processor Line -
// BIOS Writer's Guide - Rev 0.8.1
// [Files]  		BootGuardDxe.cif
// BootGuardDxe.c
// BootGuardDxe.h
// BootGuardDxe.sdl
// BootGuardDxe.dxs
// BootGuardDxe.mak
//
//**********************************************************************
//<AMI_FHDR_START>
//
// Name: BootGuardDxe.h
//
// Description: Header file for BootGuardDxe
//
//<AMI_FHDR_END>
//**********************************************************************

#ifndef _BootGuardDxe_H_
#define _BootGuardDxe_H_

#if !defined(EDK_RELEASE_VERSION) || (EDK_RELEASE_VERSION < 0x00020000)
#include "EdkIIGlueDxe.h"
#include "CpuAccess.h"
#include "PchAccess.h"
#include "PchPlatformLib.h"
#include "BootGuardLibrary.h"
#include <token.h>
#endif

#define BDS_ALL_DRIVERS_CONNECTED_PROTOCOL_GUID \
    { 0xdbc9fd21, 0xfad8, 0x45b0, 0x9e, 0x78, 0x27, 0x15, 0x88, 0x67, 0xcc, 0x93 }

EFI_GUID gNotifyProtocolGuid = BDS_ALL_DRIVERS_CONNECTED_PROTOCOL_GUID;

//
// GUID for the AMI_ANCHOR_COVE Module
//
#if !defined(EDK_RELEASE_VERSION) || (EDK_RELEASE_VERSION < 0x00020000)
#define AMI_ANCHOR_COVE_HOB_GUID \
  { \
    0xb60ab175, 0x498d, 0x429d, 0xad, 0xba, 0xa, 0x62, 0x2c, 0x58, 0x16, 0xe2 \
  }
#else
#define AMI_ANCHOR_COVE_HOB_GUID \
  { \
    0xb60ab175, 0x498d, 0x429d, \
    { \
      0xad, 0xba, 0xa, 0x62, 0x2c, 0x58, 0x16, 0xe2 \
    } \
  }
#endif

#pragma pack (1)

typedef struct {
    EFI_HOB_GUID_TYPE EfiHobGuidType;
    UINT8             AmiBootGuardVerificationforPEItoDXEFlag;
} AMI_ANCHOR_COVE_HOB;

#pragma pack ()

#endif

//**********************************************************************
//**********************************************************************
//**                                                                  **
//**        (C)Copyright 1985-2013, American Megatrends, Inc.         **
//**                                                                  **
//**                       All Rights Reserved.                       **
//**                                                                  **
//**      5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093        **
//**                                                                  **
//**                       Phone: (770)-246-8600                      **
//**                                                                  **
//**********************************************************************
//**********************************************************************
