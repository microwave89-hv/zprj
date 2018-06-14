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
// $Header: /Alaska/SOURCE/Modules/SharkBayRefCodes/ME/MeWrapper/MeSetup/Dxe/MeSetupDxe.h 2     3/01/13 3:13a Klzhan $
//
// $Revision: 2 $
//
// $Date: 3/01/13 3:13a $
//
//**********************************************************************
// Revision History
// ----------------
// $Log: /Alaska/SOURCE/Modules/SharkBayRefCodes/ME/MeWrapper/MeSetup/Dxe/MeSetupDxe.h $
// 
// 2     3/01/13 3:13a Klzhan
// 
// 1     2/07/13 2:04a Klzhan
// [TAG]  		EIP114344
// [Category]  	Improvement
// [Description]  	Create a setup item for TPM Device Selection
// [Files]  		MeSetupDxe.cif
// MeSetupDxe.c
// MeSetupDxe.h
// MeSetupDxe.sdl
// MeSetupDxe.dxs
// MeSetupDxe.mak
// 
//
//**********************************************************************
#ifndef _MeSetupDxe_H_
#define _MeSetupDxe_H_

#if !defined(EDK_RELEASE_VERSION) || (EDK_RELEASE_VERSION < 0x00020000)
#include "EdkIIGlueDxe.h"
#include "PttHciDeviceDxeLib.h"
#include "PttHeciDxeLib.h"
#include "PchAccess.h"
#include "PchPlatformLib.h"
#include "MELib.h"
#include <token.h>

#include <SetupDataDefinition.h>
#define SYSTEM_CONFIGURATION_GUID { 0xEC87D643, 0xEBA4, 0x4BB5, 0xA1, 0xE5, 0x3F, 0x3E, 0x36, 0xB2, 0x0D, 0xA9 }
#endif

typedef struct {
    BOOLEAN        PTTCapability;
    BOOLEAN        PTTState;
} PTT_INFO_VARIABLE_DATA;

#define PTT_INFO_VARIABLE_GUID \
  {0x9e6eae27, 0xc452, 0x49e6, 0x99, 0xd9, 0xb4, 0x5d, 0x1c, 0xf9, 0x1c, 0x5a}

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