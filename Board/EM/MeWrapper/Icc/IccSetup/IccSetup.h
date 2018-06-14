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
// $Header: /Alaska/SOURCE/Modules/SharkBayRefCodes/ME/MeWrapper/Icc/IccSetup/IccSetup.h 4     10/30/12 8:37a Klzhan $
//
// $Revision: 4 $
//
// $Date: 10/30/12 8:37a $
//
//**********************************************************************
// Revision History
// ----------------
// $Log: /Alaska/SOURCE/Modules/SharkBayRefCodes/ME/MeWrapper/Icc/IccSetup/IccSetup.h $
// 
// 4     10/30/12 8:37a Klzhan
// Support DMI Ratio for new ICC.
// 
// 3     5/14/12 4:47a Klzhan
// [TAG]  		EIP89676
// [Category]  	Spec Update
// [Severity]  	Important
// [Description]  	Support New ICC library
// [Files]  		IccSetup.mak
// IccSetup.sdl
// IccCallbacks.c
// IccCallbacks.h
// IccSetup.h
// IccSetupMenu.sd
// IccSetupSubmenu.sd
// IccStrings.uni
// IccLoadDefault.c
// IccSetup.cif
// 
// 2     4/24/12 12:30a Klzhan
// Update modulepart to latest
// 
// 1     2/08/12 1:07a Klzhan
// Initial Check in 
// 
// 1     2/25/11 1:42a Klzhan
// Initial Check-in
// 
// 1     12/03/10 5:10a Klzhan
// Initial Check-in.
// 
//
//**********************************************************************

//<AMI_FHDR_START>
//----------------------------------------------------------------------------
//
// Name:            IccSetup.h
//
// Description:     Setup hooks for ICC.
//
//----------------------------------------------------------------------------
//<AMI_FHDR_END>
/*++
Copyright (c)  2009 Intel Corporation. All rights reserved
This software and associated documentation (if any) is furnished
under a license and may only be used or copied in accordance
with the terms of the license. Except as permitted by such
license, no part of this software or documentation may be
reproduced, stored in a retrieval system, or transmitted in any
form or by any means without the express written consent of
Intel Corporation.

Module Name:

  IccSetup.h 

Abstract:

  Setup hooks for ICC

--*/
#define SUPPORTED_CLOCKS 8

//
// Icc Persistent Data - needs to be remembered after platform power cycle
//
#define ICC_PERSISTENT_DATA_GUID \
{0x64192dca, 0xd034, 0x49d2, 0xa6, 0xde, 0x65, 0xa8, 0x29, 0xeb, 0x4c, 0x74}
        
#define ICC_PERSISTENT_DATA_C_NAME         L"IccPersistentData"
        
typedef struct _ICC_PERSISTENT_DATA {
  UINT8  ClocksModified;
} ICC_PERSISTENT_DATA;

#define ICC_SETTINGS_NOT_MODIFIED     0
#define ICC_SETTINGS_RECENTLY_MODIFIED 1
#define ICC_SETTINGS_PREVIOUSLY_MODIFIED 2

//
// Icc Volatile Setup Data - volatile (to prevent flash wear) data used by TSE
//
#define ICC_VOLATILE_SETUP_DATA_GUID \
{0x7b77fb8b, 0x1e0d, 0x4d7e, 0x95, 0x3f, 0x39, 0x80, 0xa2, 0x61, 0xe0, 0x77}

#define ICC_VOLATILE_SETUP_DATA_C_NAME         L"IccAdvancedSetupDataVar"
#pragma pack(1)
typedef struct _ICC_VOLATILE_SETUP_DATA {
  UINT16 Frequency[SUPPORTED_CLOCKS];
  UINT8  SscMode[SUPPORTED_CLOCKS];
  UINT16 SscPercent[SUPPORTED_CLOCKS];
  UINT8  ShowSsc[SUPPORTED_CLOCKS];
  UINT8  ShowClock[SUPPORTED_CLOCKS];
  UINT8  ShowDmiPegRatio[SUPPORTED_CLOCKS];  
  UINT8  DmiPegRatio[SUPPORTED_CLOCKS];
  UINT8  ShowProfile;
  UINT8  AllowAdvancedOptions;
} ICC_VOLATILE_SETUP_DATA;
#pragma pack()
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