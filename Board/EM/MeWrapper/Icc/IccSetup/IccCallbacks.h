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
// $Header: /Alaska/SOURCE/Modules/SharkBayRefCodes/ME/MeWrapper/Icc/IccSetup/IccCallbacks.h 3     10/30/12 8:37a Klzhan $
//
// $Revision: 3 $
//
// $Date: 10/30/12 8:37a $
//
//**********************************************************************
// Revision History
// ----------------
// $Log: /Alaska/SOURCE/Modules/SharkBayRefCodes/ME/MeWrapper/Icc/IccSetup/IccCallbacks.h $
// 
// 3     10/30/12 8:37a Klzhan
// Support DMI Ratio for new ICC.
// 
// 2     5/14/12 4:47a Klzhan
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
// 1     2/08/12 1:07a Klzhan
// Initial Check in 
// 
// 3     6/27/11 10:46p Klzhan
// Update SscNumberToSscMode() for New Icc Control Library.
// 
// 2     6/23/11 11:31p Klzhan
// [TAG]  		EIP62129
// [Category]  	Spec Update
// [Severity]  	Important
// [Description]  	Support ICC Control Library 8.0.0.19.
// [Files]  		IccCallbacks.c, IccCallbacks.h
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
// Name:            IccCallbacks.h
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

  IccCallbacks.h 

Abstract:

  Setup hooks for ICC

--*/

#define MAX(a, b) ((a) > (b) ? (a) : (b))
#define MIN(a, b) ((a) > (b) ? (b) : (a))

#define ICC_CLOCK_COUNT 8

typedef struct _CLOCK_DISPLAY_VALUES {
  UINT32 ClkFreqMax;
  UINT32 ClkFreqMin;
  UINT32 ClkFreqCurrent;
  UINT16 SscPercentMax;
  UINT16 SscPercentCurrent;
  UINT16 ClockUsage;
  UINT8  SscChangeAllowed;
  UINT8  SscModeUpAvailable;
  UINT8  SscModeCenterAvailable;
  UINT8  SscModeDownAvailable;
  UINT8  SscModeCurrent;
  UINT8  DmiPegRatio;
} CLOCK_DISPLAY_VALUES;

typedef struct _ICC_CLK_REQUEST {
  UINT16 Frequency;
  UINT16 SscPercent;
  UINT8  SscAllowed;
  UINT8  SscMode;
  UINT8  EveryBoot;
} ICC_CLK_REQUEST;

#define IMMEDIATE 0
#define TEMPORARY 1
#define PERMANENT 2

#define SSC_MODE_NONE   3
#define SSC_MODE_UP     2
#define SSC_MODE_CENTER 1
#define SSC_MODE_DOWN   0

#define ROUND_UP 1
#define ROUND_DOWN 0

EFI_STATUS        SendClockChangeRequest (IN ICC_VOLATILE_SETUP_DATA* IccSetupData, IN UINT8 ClkMask, IN UINT8 TypeOfChange);
EFI_STATUS        MessageBox (IN UINT8 type, OUT UINT8* answer, IN UINT16 StringId, ...);
UINT16            FrequencyToDivider    (IN UINT16 Frequency);
UINT16            DividerToFrequency    (IN UINT16 Divider);
UINT16            FixDividerValue       (IN UINT16 Divider, IN UINT8  Direction);
UINT32            SscNumberToSscMode    (IN UINT8 SscModeNumber);
UINT8             SscModeToSscNumber    (IN UINT8 SscMode);
ICC_LIB_STATUS    IccInitOverclocking (ICC_LIB_VERSION*);
ICC_LIB_STATUS    IccInvalidateRecord (IN UINT8 RecordType);
VOID              IccGetFrequencies (IN UINT8 ClockNumber, OUT CLOCK_DISPLAY_VALUES* values);
EFI_STATUS        IccRoundFrequency (IN OUT ICC_CLK_REQUEST* IccSetupData, IN UINT8 ClockNumber);
ICC_LIB_STATUS    IccSendRequestRecord (IN UINT8 TypeOfChange, IN UINT32 ClockMask, IN ICC_CLK_REQUEST* IccExchange, OUT UINT8* ErrorLocation);
UINTN             Wcslen(CHAR16 *string);
CHAR16*           Wcscpy(CHAR16 *string1, CHAR16* string2);
VOID              StrCat (IN OUT CHAR16 *Destination, IN CHAR16 *Source);
VOID              SetIccPersistentData (IN UINT8 FlowPhase);
UINT8             GetIccPersistentData (VOID);
 
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
