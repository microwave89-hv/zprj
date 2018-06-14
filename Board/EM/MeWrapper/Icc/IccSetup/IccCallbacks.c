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
// $Header: /Alaska/SOURCE/Modules/SharkBayRefCodes/ME/MeWrapper/Icc/IccSetup/IccCallbacks.c 11    5/14/14 9:57p Tristinchou $
//
// $Revision: 11 $
//
// $Date: 5/14/14 9:57p $
//
//**********************************************************************
// Revision History
// ----------------
// $Log: /Alaska/SOURCE/Modules/SharkBayRefCodes/ME/MeWrapper/Icc/IccSetup/IccCallbacks.c $
// 
// 11    5/14/14 9:57p Tristinchou
// [TAG]  		EIP167030
// [Category]  	Improvement
// [Description]  	Remove the variable runtime attribute and keep original
// attributes.
// 
// 10    8/09/13 2:17a Klzhan
// [TAG]  		EIP131037
// [Category]  	Improvement
// [Description]  	Skip Using Icc Protocol after End of Post.
// 
// 9     5/13/13 2:42a Klzhan
// [TAG]  		EIPNone
// [Category]  	Improvement
// [Description]  	FIx build error when Icc_OverClocking_Support is
// disabled.
// 
// 8     12/27/12 6:36a Klzhan
// [TAG]  		EIP104882
// [Category]  	Improvement
// [Description]  	Avoid running ICC callbacks when Load Default.
// 
// 7     10/30/12 8:37a Klzhan
// Support DMI Ratio for new ICC.
// 
// 6     9/19/12 5:58a Klzhan
// Avoid time-out in ICC setup Page when return from Shell.
// 
// 5     7/02/12 11:43p Klzhan
// [TAG]  		EIP94113
// [Category]  	Spec Update
// [Severity]  	Important
// [Description]  	Update ME RC0.6
// 
// 4     5/14/12 5:29a Klzhan
// Remove Debug code
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
// 6     9/06/11 6:11a Klzhan
// [TAG]  		EIP67462
// [Category]  	Spec Update
// [Severity]  	Important
// [Description]  	Update ICC 08.00.00.022.1
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
// 5     7/26/11 5:58a Klzhan
// Support EFI 2.3
// 
// 4     6/27/11 3:22a Klzhan
// Correct SscMode when Set frequency.
// 
// 3     6/24/11 7:20a Klzhan
// Remove un-use debug message.
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
// Name:            IccCallbacks.c
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

  IccCallbacks.c

Abstract:

  Setup hooks for ICC.

--*/

#include <AmiDxeLib.h>
#include <Setup.h>
#include <SetupStrTokens.h>
#include "AUTOID.h"
#include "Protocol\AMIPostMgr.h"
#include "Protocol\IccOverClocking\IccOverClocking.h"
#include "IccSetup.h"
#include "IccCallbacks.h"
#include "PchAccess.h"
#ifdef CougarPoint_SUPPORT
#include "Protocol\Wdt\Wdt.h"
#include "Protocol\WdtApp\WdtApp.h"
#endif
#include "Protocol\MePlatformPolicy\MePlatformPolicy.h"

UINT8                      mActiveSubmenu = ICC_CLOCK_COUNT;
ICC_OVERCLOCKING_PROTOCOL* gIccOverClockingProtocol;
ICC_CLOCK_RANGES           mRanges[ICC_CLOCK_COUNT];
CLOCK_DISPLAY_VALUES       values; // Store clock Infomations of current page.
UINT16                     mBootTimeClkDiv[ICC_CLOCK_COUNT];
UINT8                      mWatchdogEnabled;

CHAR16* mClockUsageName[] = {
  L"BCLK", 
  L"DMI", 
  L"PEG", 
  L"PCIe", 
  L"PCI33", 
  L"RESERVED", 
  L"SATA",
  L"USB3", 
  L"IGD", 
  L"IGD Bending", 
  L"RESERVED", 
  L"GFX", 
  L"USB Legacy", 
  L"PCH Legacy"
};

CHAR16* mClockName[] = {
  L"Clock1", 
  L"Clock2", 
  L"Clock3", 
  L"Clock4", 
  L"Clock5", 
  L"Clock6", 
  L"Clock7", 
  L"Clock8"
};

CHAR16* mClockUsageNone = L"Not used";

UINT16* mModeName[] = {
  L"Down", 
  L"Center",
  L"Up",
  L"None"
};

EFI_HII_HANDLE gHiiHandle;
//
// Blocks entry to ICC clock submenus after End Of Post event
//
UINT8          mAfterEndOfPost = 0;

#define NAME_ARRAY_SIZE  (( sizeof(mClockUsageName)/sizeof(mClockUsageName[0]) ))

#if (SUPPORTED_CLOCKS != ICC_CLOCK_COUNT)
#error Ambiguous number of supported clocks 
#endif

#ifndef StrCat
#define StrCat(a,b) Wcscpy (a + Wcslen (a), b)
#endif

#define AMI_CALLBACK_CONTROL_UPDATE 1
#define AMI_CALLBACK_RETRIEVE 2
#define AMI_CALLBACK_FORM_OPEN 3
#define AMI_CALLBACK_FORM_CLOSE 4
#define AMI_CALLBACK_FORM_DEFAULT_STANDARD      0x1000
#define AMI_CALLBACK_FORM_DEFAULT_MANUFACTURING 0x1001

EFI_STATUS 
OnReadyToBoot (
IN EFI_EVENT Event,
IN VOID      *Context
)
/*++
Routine Description: 

  This function is executed on ReadyToBoot event.
  If permanent or temporary ICC modifications were made, platform needs to be restarted.
  Unlike ordinary setup options, ICC modifications can't be programmed to cause automatic reset.
  Instead this function, executed on ReadyToBoot event, causes reset.

Arguments:
  Event    pointer to event that caused this function to be executed
  Context  not used here

Returns:
  always SUCCESS
--*/
{
  mAfterEndOfPost = 1;
  pBS->CloseEvent(Event);
  if (GetIccPersistentData() == ICC_SETTINGS_RECENTLY_MODIFIED) {
    pRS->ResetSystem(EfiResetCold, 0, 0, 0);
  } else if (GetIccPersistentData() == ICC_SETTINGS_PREVIOUSLY_MODIFIED) {
    SetIccPersistentData(ICC_SETTINGS_NOT_MODIFIED);
  }
  return EFI_SUCCESS;
}

VOID
InitICCStrings (
  EFI_HII_HANDLE HiiHandle,
  UINT16         Class
  )
/*++
Routine Description: 

  This function is executed when Setup module loads.
  Registers OnReadyToBoot function to be executed on ReadyToBoot event.
  Remembers HiiHandle, pointer to setup browser's runtime variable store
  
Arguments:
  HiiHandle
  Class

Returns:
  always SUCCESS
--*/
{
  static UINT8 mInitStringComplete = 0;
  EFI_EVENT    Event;
  EFI_GUID     EfiEventReadyToBootGuid = EFI_EVENT_GROUP_READY_TO_BOOT;
 
  if (mInitStringComplete == 1) {
    return;
  } else {
    if(Class == ADVANCED_FORM_SET_CLASS) {
      mInitStringComplete = 1;
      gHiiHandle = HiiHandle;

      if (GetIccPersistentData() == ICC_SETTINGS_RECENTLY_MODIFIED) {
        SetIccPersistentData(ICC_SETTINGS_PREVIOUSLY_MODIFIED);
      }
        
#if (EFI_SPECIFICATION_VERSION < 0x00020000) 
      pBS->CreateEvent (
                      EFI_EVENT_SIGNAL_READY_TO_BOOT | EFI_EVENT_NOTIFY_SIGNAL_ALL,
                      TPL_CALLBACK,
                      OnReadyToBoot,
                      NULL,
                      &Event
                      );
#else
      pBS->CreateEventEx (
                      EFI_EVENT_NOTIFY_SIGNAL,
                      TPL_CALLBACK,
                      OnReadyToBoot,
                      NULL,
                      &EfiEventReadyToBootGuid,
                      &Event
                      );
#endif

    }
  }
}

EFI_STATUS
InitIccMenu (
  IN ICC_VOLATILE_SETUP_DATA* IccSetupData
  )
/*++
Routine Description: 
  Initializes text strings and setup variables connected with ICC menu.
  If there is an error during initialization, displays messagebox with error details
Arguments:
  Pointer to Icc setup data structure
Returns:
  EFI_SUCCESS if everything went OK
  otherwise, an ERROR
--*/
{
  UINTN                    VariableSize;
  UINT8                    i;
  EFI_STATUS               Status;
#if IccOverClocking_SUPPORT
  ICC_LIB_STATUS           IccStatus; 
#endif
  ICC_LIB_VERSION          Version;
  SETUP_DATA               SetupData;
  EFI_GUID                 IccOverClockingProtocolGuid = ICC_OVERCLOCKING_PROTOCOL_GUID;
  EFI_GUID                 IccSetupDataGuid = ICC_VOLATILE_SETUP_DATA_GUID;
  EFI_GUID                 SetupGuid = SETUP_GUID;
  CALLBACK_PARAMETERS *CallbackParameter = GetCallbackParameters();

#if EFI_SPECIFICATION_VERSION >= 0x2001E
    if ((CallbackParameter->Action == AMI_CALLBACK_RETRIEVE) ||
        (CallbackParameter->Action == AMI_CALLBACK_FORM_OPEN) ||
        (CallbackParameter->Action == AMI_CALLBACK_FORM_CLOSE) ||
        (CallbackParameter->Action == AMI_CALLBACK_FORM_DEFAULT_STANDARD) ||
        (CallbackParameter->Action == AMI_CALLBACK_FORM_DEFAULT_MANUFACTURING))
        return EFI_SUCCESS;
#endif

  VariableSize  = sizeof (SETUP_DATA);
  
  Status = pRS->GetVariable (
                  L"Setup",
                  &SetupGuid,
                  NULL,
                  &VariableSize,
                  &SetupData
                  );
  if (EFI_ERROR (Status)) {
    return Status;
  }

  VariableSize = sizeof(UINT8);
  Status = pRS->GetVariable (
                  L"AfterReadyToBoot",
                  &IccSetupDataGuid,
                  NULL,
                  &VariableSize,
                  &mAfterEndOfPost);
#if IccOverClocking_SUPPORT
  Status = pBS->LocateProtocol(&IccOverClockingProtocolGuid, NULL, &gIccOverClockingProtocol);
  if (EFI_ERROR (Status)) {
    return Status;
  }
  VariableSize  = sizeof (UINTN);  
  mWatchdogEnabled = SetupData.IccWdtEnabled;

  IccStatus = IccInitOverclocking(&Version);

  if ( IccStatus != ICC_LIB_STATUS_SUCCESS ) {
    MessageBox ( MSGBOX_TYPE_OK, NULL, STRING_TOKEN(STR_ICC_MSGBOX_INIT_ERROR_STRANGE), IccStatus);
    IccSetupData->AllowAdvancedOptions = 0;
    return EFI_DEVICE_ERROR;
  }
#else
  return EFI_SUCCESS;
#endif
  // If init success, Set allowadvancedOption true
//  IccSetupData->AllowAdvancedOptions = 1;

  InitString(
              gHiiHandle,
              STRING_TOKEN(STR_ICC_LIB_VERSION_NR),
              L"%d.%d.%d.%d",
              Version.Major,
              Version.Minor,
              Version.Hotfix,
              Version.Build
              );
  if(mAfterEndOfPost != 1)
  {
    IccSetupData->AllowAdvancedOptions = 1;
    for (i=0; i<ICC_CLOCK_COUNT; i++) {
      IccGetFrequencies(i, &values);
      IccSetupData->Frequency[i]  = values.ClkFreqCurrent;
      IccSetupData->SscPercent[i] = values.SscPercentCurrent;
      IccSetupData->SscMode[i]    = values.SscModeCurrent;
      // Workaround for architecture bugs: read - don't modify - write sequence doesn't work for some clocks
      // These clocks must not be allowed to be modified - they'll cause ICC Lib to return misleading errors
      if (/* (values.ClockUsage & (1<<ICC_CLOCK_USAGE_GFX)) ||
           (values.ClockUsage & (1<<ICC_CLOCK_USAGE_GFX_BENDING)) ||*/
           (values.ClockUsage == 0) 
      ) {
        IccSetupData->ShowSsc[i]   = 0;
        IccSetupData->ShowClock[i] = 0;
      } else {
        IccSetupData->ShowSsc[i]   = values.SscChangeAllowed;
        if (values.ClkFreqMax == values.ClkFreqMin) { 
          IccSetupData->ShowClock[i] = 0;
        } else {
          IccSetupData->ShowClock[i] = 1;
        }
      }
    }
  }else
    IccSetupData->AllowAdvancedOptions = 0;

  return EFI_SUCCESS;
}

EFI_STATUS
EFIAPI 
IccMenuEntry (
    IN EFI_HII_HANDLE HiiHandle, 
    IN UINT16         Class, 
    IN UINT16         SubClass, 
    IN UINT16         Key
)
/*++
Routine Description: 
  Setup callback executed when user enters Advanced->ICC menu
  Think of it as an entry point to efi overclocking module
  Initializes ICC OverClocking and if there are errors, disables entry into submenus
  Without access to submenus, it is guaranteed no other callback will be executed.
Arguments:
Returns:
  always SUCCESS, but in case of errors entry into submenus is disabled
--*/
{
  static UINT8             FirstEntry = 1;
  static UINT8             EopReported = 0;
  ICC_VOLATILE_SETUP_DATA* IccSetupData = NULL;
  EFI_STATUS               Status;
  EFI_GUID                 IccSetupDataGuid = ICC_VOLATILE_SETUP_DATA_GUID;
  UINTN                    SelectionBufferSize = sizeof(ICC_VOLATILE_SETUP_DATA);
  CALLBACK_PARAMETERS      *CallbackParameter = GetCallbackParameters();
  EFI_GUID DxePlatformMePolicyGuid = DXE_PLATFORM_ME_POLICY_GUID;
  DXE_ME_POLICY_PROTOCOL  *DxePlatformMePolicy;

#if EFI_SPECIFICATION_VERSION >= 0x2001E
    if ((CallbackParameter->Action == AMI_CALLBACK_RETRIEVE) ||
        (CallbackParameter->Action == AMI_CALLBACK_FORM_OPEN) ||
        (CallbackParameter->Action == AMI_CALLBACK_FORM_CLOSE) ||
        (CallbackParameter->Action == AMI_CALLBACK_FORM_DEFAULT_STANDARD) ||
        (CallbackParameter->Action == AMI_CALLBACK_FORM_DEFAULT_MANUFACTURING))
          return EFI_SUCCESS;
#endif

  if(mAfterEndOfPost == 0) {
      Status = pBS->LocateProtocol(&DxePlatformMePolicyGuid, NULL, &DxePlatformMePolicy);
      if(!EFI_ERROR (Status)) {
          if(DxePlatformMePolicy->MeConfig.EndOfPostDone) {
              mAfterEndOfPost = 1;
          }
      }
  }
  //
  // No changes to ICC menu display
  //
  if (EopReported == 1 || (FirstEntry ==0 && mAfterEndOfPost == 0)) {
    return EFI_SUCCESS;
  }

  FirstEntry = 0;

#if EFI_SPECIFICATION_VERSION>0x20000
  Status = pBS->AllocatePool(EfiBootServicesData, SelectionBufferSize, &IccSetupData);
    if(EFI_ERROR(Status)) {
      return Status;
    }
  
  Status = HiiLibGetBrowserData(&SelectionBufferSize, 
                                IccSetupData,
                                &IccSetupDataGuid, 
                                ICC_VOLATILE_SETUP_DATA_C_NAME
                                );
  ASSERT_EFI_ERROR(Status);
  
#else
  IccSetupData = (ICC_VOLATILE_SETUP_DATA*)CallbackParameter->Data->NvRamMap;
#endif

  if (mAfterEndOfPost == 1 && EopReported == 0) {
    IccSetupData->AllowAdvancedOptions = 0;
    EopReported = 1;
    MessageBox ( MSGBOX_TYPE_OK, NULL, STRING_TOKEN(STR_ICC_MSGBOX_AFTER_EOP));
  } else {
    Status = InitIccMenu(IccSetupData);
    if (EFI_ERROR(Status)) {
//      IccSetupData->AllowAdvancedOptions = 0;
      MessageBox ( MSGBOX_TYPE_OK, NULL, STRING_TOKEN(STR_ICC_MSGBOX_INIT_ERROR_STRANGE));
    } else {
//      IccSetupData->AllowAdvancedOptions = 1;
    }
  }

  Status = pRS->SetVariable(
                    ICC_VOLATILE_SETUP_DATA_C_NAME,
                    &IccSetupDataGuid,
                    EFI_VARIABLE_BOOTSERVICE_ACCESS |
                    EFI_VARIABLE_NON_VOLATILE,
                    sizeof(ICC_VOLATILE_SETUP_DATA),
                    IccSetupData );

#if EFI_SPECIFICATION_VERSION>0x20000
  Status = HiiLibSetBrowserData(
              SelectionBufferSize, IccSetupData,
              &IccSetupDataGuid, ICC_VOLATILE_SETUP_DATA_C_NAME
              );
  ASSERT_EFI_ERROR(Status);
  pBS->FreePool(IccSetupData);

#endif;

  return EFI_SUCCESS;
}



EFI_STATUS
EFIAPI 
IccSubmenuEntry (
    IN EFI_HII_HANDLE HiiHandle, 
    IN UINT16         Class, 
    IN UINT16         SubClass, 
    IN UINT16         Key
)

/*++
Routine Description: 
  Setup callback executed when user enters any submenu of Advanced->ICC
  Personalizes common strings for that particular clock submenu
  Stores information on which submenu we're in, that's needed for other callbacks
Arguments:
Returns:
  always SUCCESS
--*/
{
  UINT8                SubMenuNumber = ICC_CLOCK_COUNT;
  CHAR16               StringBuffer[100];
  UINT8                i;
  UINT8                NeedComma;
  UINT8                LineOverflow;
  CALLBACK_PARAMETERS *CallbackParameter = GetCallbackParameters();
  
#if EFI_SPECIFICATION_VERSION >= 0x2001E
    if ((CallbackParameter->Action == AMI_CALLBACK_RETRIEVE) ||
        (CallbackParameter->Action == AMI_CALLBACK_FORM_OPEN) ||
        (CallbackParameter->Action == AMI_CALLBACK_FORM_CLOSE) ||
        (CallbackParameter->Action == AMI_CALLBACK_FORM_DEFAULT_STANDARD) ||
        (CallbackParameter->Action == AMI_CALLBACK_FORM_DEFAULT_MANUFACTURING))
            return EFI_SUCCESS;
#endif
  
  switch (Key) {
    case KEY_FORM1:
      SubMenuNumber = 0;
      break;
    case KEY_FORM2:
      SubMenuNumber = 1;
      break;
    case KEY_FORM3:
      SubMenuNumber = 2;
      break;
    case KEY_FORM4:
      SubMenuNumber = 3;
      break;
    case KEY_FORM5:
      SubMenuNumber = 4;
      break;
    case KEY_FORM6:
      SubMenuNumber = 5;
      break;
    case KEY_FORM7:
      SubMenuNumber = 6;
      break;
    case KEY_FORM8:
      SubMenuNumber = 7;
      break;
    default:
      ASSERT(FALSE);
  }

  if (SubMenuNumber == mActiveSubmenu) {
    //
    //strings already personalized for this menu, no need to change them
    //
    return EFI_SUCCESS;
  }

  mActiveSubmenu = SubMenuNumber;
  
  IccGetFrequencies(mActiveSubmenu, &values);
  StringBuffer[0] = 0;
  NeedComma = 0;
  LineOverflow = 0;
  
  //
  // Concatenate all clock usages into two strings. If first string gets too long, second will be written
  //
  InitString(gHiiHandle, STRING_TOKEN(STR_ICC_CLOCK_USAGE_2), L"%s", StringBuffer);
  if (values.ClockUsage != 0) {
    for (i=0; i<NAME_ARRAY_SIZE; i++) {
      if (values.ClockUsage & (1<<i)) {
        if (NeedComma == 1) {
          StrCat(StringBuffer, L", ");  
        }
        if ( Wcslen(StringBuffer) + Wcslen(mClockUsageName[i]) > 25 ) {
          LineOverflow = 1;
          InitString(gHiiHandle, STRING_TOKEN(STR_ICC_CLOCK_USAGE_1), L"%s", StringBuffer);
          StringBuffer[0] = 0;        
          NeedComma = 0;
        }      
        StrCat(StringBuffer, mClockUsageName[i]);
        NeedComma = 1;
      }
    }
  } else {
    StrCat(StringBuffer, mClockUsageNone);
  }  
  if (LineOverflow) {
    InitString(gHiiHandle, STRING_TOKEN(STR_ICC_CLOCK_USAGE_2), L"%s", StringBuffer);
  } else {
    InitString(gHiiHandle, STRING_TOKEN(STR_ICC_CLOCK_USAGE_1), L"%s", StringBuffer);
  }

  InitString(gHiiHandle, STRING_TOKEN(STR_ICC_CLOCK_NUMBER), L"%s", mClockName[SubMenuNumber]);
  InitString(gHiiHandle, STRING_TOKEN(STR_ICC_MAX_FREQUENCY_VALUE), L"%d.%02d MHz", values.ClkFreqMax/100, values.ClkFreqMax%100);
  InitString(gHiiHandle, STRING_TOKEN(STR_ICC_MIN_FREQUENCY_VALUE), L"%d.%02d MHz", values.ClkFreqMin/100, values.ClkFreqMin%100);
  InitString(gHiiHandle, STRING_TOKEN(STR_ICC_CURRENT_FREQUENCY_VALUE), L"%d.%02d MHz", values.ClkFreqCurrent/100, values.ClkFreqCurrent%100);
  InitString(gHiiHandle, STRING_TOKEN(STR_ICC_SSC_MODES_VALUE), L"%s%s%s",
                                                               (values.SscModeDownAvailable)  ? L"Down " : L" ",
                                                               (values.SscModeCenterAvailable)? L"Center " : L" ",
                                                               (values.SscModeUpAvailable)    ? L"Up " : L" "
                                                               );
  InitString(gHiiHandle, STRING_TOKEN(STR_ICC_SSC_CURRENT_MODE_VALUE), L"%s", mModeName[values.SscModeCurrent]);
  InitString(gHiiHandle, STRING_TOKEN(STR_ICC_SSC_MAX_VALUE), L"%d.%02d%%", values.SscPercentMax/100, values.SscPercentMax%100);
  InitString(gHiiHandle, STRING_TOKEN(STR_ICC_SSC_CURRENT_VALUE), L"%d.%02d%%", values.SscPercentCurrent/100, values.SscPercentCurrent%100);

  return EFI_SUCCESS;
}

EFI_STATUS
EFIAPI 
IccAccept (
    IN EFI_HII_HANDLE HiiHandle, 
    IN UINT16         Class, 
    IN UINT16         SubClass, 
    IN UINT16         Key
)
/*++
Routine Description: 
  Setup callback executed when user chooses 'Accept'
  Sends requested clock parameters to ICC OverClocking
Arguments:
  interface to ITEM_CALLBACK_EX
Returns:
  always SUCCESS
--*/
{
  EFI_STATUS               Status;
  ICC_VOLATILE_SETUP_DATA* IccSetupData = NULL;
  CLOCK_DISPLAY_VALUES     values;
  UINT8                    TypeOfChange;
  UINTN                    VarSize = 0;
#if EFI_SPECIFICATION_VERSION>0x20000
  UINTN SelectionBufferSize = sizeof(ICC_VOLATILE_SETUP_DATA);
  EFI_GUID IccSetupDataGuid = ICC_VOLATILE_SETUP_DATA_GUID;
#endif
  CALLBACK_PARAMETERS *CallbackParameter = GetCallbackParameters();

#if EFI_SPECIFICATION_VERSION >= 0x2001E
    if ((CallbackParameter->Action == AMI_CALLBACK_RETRIEVE) ||
        (CallbackParameter->Action == AMI_CALLBACK_FORM_OPEN) ||
        (CallbackParameter->Action == AMI_CALLBACK_FORM_CLOSE) ||
        (CallbackParameter->Action == AMI_CALLBACK_FORM_DEFAULT_STANDARD) ||
        (CallbackParameter->Action == AMI_CALLBACK_FORM_DEFAULT_MANUFACTURING))
          return EFI_SUCCESS;
#endif

  switch (Key) {
    case  KEY_CHANGE_NOW1:
    case  KEY_CHANGE_NOW2:
    case  KEY_CHANGE_NOW3:
    case  KEY_CHANGE_NOW4:
    case  KEY_CHANGE_NOW5:
    case  KEY_CHANGE_NOW6:
      TypeOfChange = IMMEDIATE;
      break;
    case  KEY_CHANGE_ONCE1:
    case  KEY_CHANGE_ONCE2:
    case  KEY_CHANGE_ONCE3:
    case  KEY_CHANGE_ONCE4:
    case  KEY_CHANGE_ONCE5:
    case  KEY_CHANGE_ONCE6:
      TypeOfChange = TEMPORARY;
      break;
    case  KEY_CHANGE_PERM1:
    case  KEY_CHANGE_PERM2:
    case  KEY_CHANGE_PERM3:
    case  KEY_CHANGE_PERM4:
    case  KEY_CHANGE_PERM5:
    case  KEY_CHANGE_PERM6:
      TypeOfChange = PERMANENT;
      break;
    default:
      ASSERT(FALSE);
      TypeOfChange = 0; //prevent compilator warning
  }
  
#if EFI_SPECIFICATION_VERSION>0x20000
    Status = pBS->AllocatePool(EfiBootServicesData, SelectionBufferSize, &IccSetupData);
        if(EFI_ERROR(Status))
            return Status;

        Status = HiiLibGetBrowserData(
            &SelectionBufferSize, IccSetupData,
            &IccSetupDataGuid, ICC_VOLATILE_SETUP_DATA_C_NAME
        );
        ASSERT_EFI_ERROR(Status);
#else
  IccSetupData = (ICC_VOLATILE_SETUP_DATA*)CallbackParameter->Data->NvRamMap;
#endif
  Status = SendClockChangeRequest(IccSetupData, mActiveSubmenu, TypeOfChange);
  IccGetFrequencies(mActiveSubmenu, &values);

  InitString(gHiiHandle, STRING_TOKEN(STR_ICC_CURRENT_FREQUENCY_VALUE), L"%d.%02d MHz", values.ClkFreqCurrent/100, values.ClkFreqCurrent%100);
  InitString(gHiiHandle, STRING_TOKEN(STR_ICC_SSC_CURRENT_MODE_VALUE), L"%s", mModeName[values.SscModeCurrent]);
  InitString(gHiiHandle, STRING_TOKEN(STR_ICC_SSC_CURRENT_VALUE), L"%d.%02d%%", values.SscPercentCurrent/100, values.SscPercentCurrent%100);

#if EFI_SPECIFICATION_VERSION>0x20000
  pBS->FreePool(IccSetupData);
#endif;

  return EFI_SUCCESS;
}

EFI_STATUS
EFIAPI 
IccFreqChange (
    IN EFI_HII_HANDLE HiiHandle, 
    IN UINT16         Class, 
    IN UINT16         SubClass, 
    IN UINT16         Key
)
/*++
Routine Description: 
  Setup callback executed when user changes frequency
  Calls IccFrequencyRounding() which fixes frequency and SSC parameters to allowed values
  Having these parameters fixed decreases number of errors caused by sending wrong parameters
Arguments:
Returns:
  always SUCCESS
--*/
{
  EFI_STATUS               Status;
  ICC_VOLATILE_SETUP_DATA* IccSetupData = NULL;
  ICC_CLOCK_FREQUENCY      ExpectFrequency, UserFrequency;
  BOOLEAN                  HigherFrequency = FALSE;
  ICC_LIB_STATUS           IccStatus; 
#if EFI_SPECIFICATION_VERSION>0x20000
  UINTN SelectionBufferSize = sizeof(ICC_VOLATILE_SETUP_DATA);
  EFI_GUID IccSetupDataGuid = ICC_VOLATILE_SETUP_DATA_GUID;
#endif

  CALLBACK_PARAMETERS *CallbackParameter = GetCallbackParameters();

#if EFI_SPECIFICATION_VERSION >= 0x2001E
  if ((CallbackParameter->Action == AMI_CALLBACK_RETRIEVE) ||
    (CallbackParameter->Action == AMI_CALLBACK_FORM_OPEN) ||
    (CallbackParameter->Action == AMI_CALLBACK_FORM_CLOSE))
        return EFI_SUCCESS;
#endif

#if EFI_SPECIFICATION_VERSION>0x20000
    Status = pBS->AllocatePool(EfiBootServicesData, SelectionBufferSize, &IccSetupData);
        if(EFI_ERROR(Status))
            return Status;

        Status = HiiLibGetBrowserData(
            &SelectionBufferSize, IccSetupData,
            &IccSetupDataGuid, ICC_VOLATILE_SETUP_DATA_C_NAME
        );
		ASSERT_EFI_ERROR(Status);
#else
  IccSetupData = (ICC_VOLATILE_SETUP_DATA*)CallbackParameter->Data->NvRamMap;
#endif

  UserFrequency = IccSetupData->Frequency[mActiveSubmenu];

  if(UserFrequency >= values.ClkFreqMax)
  {
    IccSetupData->Frequency[mActiveSubmenu] = values.ClkFreqMax;
#if EFI_SPECIFICATION_VERSION>0x20000
    Status = HiiLibSetBrowserData(
                SelectionBufferSize, IccSetupData,
                &IccSetupDataGuid, ICC_VOLATILE_SETUP_DATA_C_NAME
                );
    ASSERT_EFI_ERROR(Status);

    pBS->FreePool(IccSetupData);
#endif;
    return EFI_SUCCESS;
  }

  if(UserFrequency <= values.ClkFreqMin)
  {
    IccSetupData->Frequency[mActiveSubmenu] = values.ClkFreqMin;
#if EFI_SPECIFICATION_VERSION>0x20000
    Status = HiiLibSetBrowserData(
                SelectionBufferSize, IccSetupData,
                &IccSetupDataGuid, ICC_VOLATILE_SETUP_DATA_C_NAME
                );
    ASSERT_EFI_ERROR(Status);

    pBS->FreePool(IccSetupData);
#endif;
    return EFI_SUCCESS;
  }

  if(UserFrequency > values.ClkFreqCurrent)
    HigherFrequency =  TRUE;

  {
    UserFrequency = (UserFrequency) * 10000;
    gIccOverClockingProtocol->GetNextFrequency(mActiveSubmenu, 
                                               UserFrequency, 
                                               &UserFrequency,
                                               &IccStatus);

    gIccOverClockingProtocol->GetPreviousFrequency(mActiveSubmenu,
                                                   UserFrequency, 
                                                   &ExpectFrequency,
                                                   &IccStatus);
  }

  if (IccStatus == ICC_LIB_STATUS_SUCCESS) {
    IccSetupData->Frequency[mActiveSubmenu]  = ExpectFrequency/10000;
  }

#if EFI_SPECIFICATION_VERSION>0x20000
  Status = HiiLibSetBrowserData(
              SelectionBufferSize, IccSetupData,
              &IccSetupDataGuid, ICC_VOLATILE_SETUP_DATA_C_NAME
              );
  ASSERT_EFI_ERROR(Status);

  pBS->FreePool(IccSetupData);
#endif;

  return EFI_SUCCESS;
}

EFI_STATUS 
SendClockChangeRequest (
  IN ICC_VOLATILE_SETUP_DATA* IccSetupData, 
  IN UINT8                    ClockID,
  IN UINT8                    TypeOfChange
  )
/*++
Routine Description: 
  Executed by setup calback function
  Based on data entered by user, sends clock change requests to ICC OverClocking
  Writing to susram or flash requires that old susram and flash contents be invalidated
  In case of any problem, messagebox is displayed so user can know what corrective action is required
Arguments:
  initial clock divider value
Returns: 
  validated clock divider value
--*/
{

  UINT8                 answer = 1;
  ICC_LIB_STATUS        IccStatus;
  ICC_CLOCK_SETTINGS    RequestSetting;
  BOOLEAN               freqConsolidationBypass = TRUE, permanentChange;

  if(TypeOfChange == PERMANENT)
    permanentChange = TRUE;

  if(TypeOfChange == TEMPORARY)
    permanentChange = FALSE;

  // Prepare Setting
  gIccOverClockingProtocol->GetCurrentClockSettings(ClockID, &RequestSetting, &IccStatus);
  RequestSetting.Frequency  = IccSetupData->Frequency[ClockID] * 10000;
  RequestSetting.SscMode    = SscNumberToSscMode(IccSetupData->SscMode[ClockID]);
  RequestSetting.SscPercent = (UINT8)IccSetupData->SscPercent[ClockID];
  // Only ICC_DMI_PEG_RATIO_5_TO_5 is support in PPT.
  RequestSetting.DmiPegRatio = (UINT8)IccSetupData->DmiPegRatio[ClockID];

  if(TypeOfChange == IMMEDIATE)
  {
    gIccOverClockingProtocol->SetCurrentClockSettings(ClockID, 
                                                      RequestSetting,
                                                      &IccStatus);
  }else
  {
    gIccOverClockingProtocol->SetBootClockSettings(ClockID, 
                                                   RequestSetting,
                                                   &IccStatus);
  }

  if (IccStatus != ICC_LIB_STATUS_SUCCESS) {
    if (TypeOfChange == TEMPORARY) {
      MessageBox (MSGBOX_TYPE_OKCANCEL, &answer, STRING_TOKEN(STR_ICC_MSGBOX_ONCE_OVERWRITE));
    } else if (TypeOfChange == PERMANENT) {
      MessageBox (MSGBOX_TYPE_OKCANCEL, &answer, STRING_TOKEN(STR_ICC_MSGBOX_PERM_OVERWRITE));
    }
    if (answer != MSGBOX_YES) {
      return ICC_LIB_STATUS_SUCCESS;
    }
  }

  switch (IccStatus) {
    case ICC_LIB_STATUS_DYNAMIC_CHANGE_NOT_ALLOWED:
      MessageBox (MSGBOX_TYPE_OKCANCEL, &answer, STRING_TOKEN(STR_ICC_MSGBOX_NO_DYNAMIC), mClockName[ClockID]);      
      break;
    case ICC_LIB_STATUS_REGISTER_IS_LOCKED:
      MessageBox ( MSGBOX_TYPE_OK, NULL, STRING_TOKEN(STR_ICC_MSGBOX_LOCKED));
      break;            
    case ICC_LIB_STATUS_FREQ_TOO_HIGH:
      MessageBox ( MSGBOX_TYPE_OK, NULL, STRING_TOKEN(STR_ICC_MSGBOX_FREQ_HIGH), mClockName[ClockID] );
      break;
    case ICC_LIB_STATUS_FREQ_TOO_LOW:
      MessageBox (MSGBOX_TYPE_OK, NULL, STRING_TOKEN(STR_ICC_MSGBOX_FREQ_LOW), mClockName[ClockID] );
      break;
    case ICC_LIB_STATUS_SSC_TOO_HIGH:
    case ICC_LIB_STATUS_SSC_OUT_OF_RANGE:
      MessageBox ( MSGBOX_TYPE_OK, NULL, STRING_TOKEN(STR_ICC_MSGBOX_SSC_HIGH), mClockName[ClockID] );
      break;
    case ICC_LIB_STATUS_SSC_TOO_LOW:
      MessageBox (MSGBOX_TYPE_OK, NULL, STRING_TOKEN(STR_ICC_MSGBOX_SSC_LOW), mClockName[ClockID] );
      break;
    case ICC_LIB_STATUS_SSC_MODE_NOT_SUPPORTED:
      MessageBox ( MSGBOX_TYPE_OK, NULL, STRING_TOKEN(STR_ICC_MSGBOX_SSC_MODE), mClockName[ClockID] );
      break;
    case ICC_LIB_STATUS_FREQ_MUST_HAVE_ZERO_SSC:
      MessageBox ( MSGBOX_TYPE_OK, NULL, STRING_TOKEN(STR_ICC_MSGBOX_SSC_DISABLED), mClockName[ClockID] );
      break;
    case ICC_LIB_STATUS_SSC_CHANGE_NOT_ALLOWED:
      MessageBox ( MSGBOX_TYPE_OK, NULL, STRING_TOKEN(STR_ICC_MSGBOX_SSC_CONSTANT), mClockName[ClockID] );
      break;
    case ICC_LIB_STATUS_MEI_INITIALIZATION_FAILED:
    case ICC_LIB_STATUS_MEI_CONNECTION_FAILED:
      MessageBox ( MSGBOX_TYPE_OK, NULL, STRING_TOKEN(STR_ICC_MSGBOX_HECI));
      break;            
    case ICC_LIB_STATUS_SUCCESS:
      if (TypeOfChange == IMMEDIATE) {
        MessageBox ( MSGBOX_TYPE_OK, NULL, STRING_TOKEN(STR_ICC_MSGBOX_SUCCESS));
      } else {
        MessageBox ( MSGBOX_TYPE_OK, NULL, STRING_TOKEN(STR_ICC_MSGBOX_SUCCESS_NEED_REBOOT));
      }
      break;
    default:
      MessageBox ( MSGBOX_TYPE_OK, NULL, STRING_TOKEN(STR_ICC_MSGBOX_UNKNOWN), IccStatus );
      break;
  }

  return IccStatus;
}

EFI_STATUS
MessageBox (
  IN UINT8 type, 
  OPTIONAL OUT UINT8* answer, 
  IN UINT16 StringId,
  ...
  )
/*++
Routine Description: 
  Wrapper function that displays messagebox. Text for Messagebox is specified with printf-like parameters.
 Arguments:
  type - messagebox type
  answer - pointer to where user's answer will be stored
  format, ... - parameters to printf
Returns: 
--*/
{
  static AMI_POST_MANAGER_PROTOCOL* pAmiPostMgr = NULL;
  EFI_GUID                          AmiPostManagerProtocolGuid = AMI_POST_MANAGER_PROTOCOL_GUID;
  EFI_STATUS                        Status;
  UINT8                             LocalAnswer;
  CHAR16*                           StrBuffer = 0;
  CHAR16*                           LocalBuffer;
  UINTN                             LocalBufferSize;
  UINTN                             StrLen = 0;
  va_list                           ArgList = va_start(ArgList,StringId);

  if (pAmiPostMgr == NULL) {
    Status = pBS->LocateProtocol(&AmiPostManagerProtocolGuid, NULL, &pAmiPostMgr);
    ASSERT (pAmiPostMgr);
    ASSERT_EFI_ERROR (Status);
  }
  
  HiiLibGetString(gHiiHandle, StringId, &StrLen, StrBuffer);
  Status = pBS->AllocatePool(EfiBootServicesData, StrLen, &StrBuffer);
  ASSERT_EFI_ERROR(Status);
  HiiLibGetString(gHiiHandle, StringId, &StrLen, StrBuffer);

  LocalBufferSize = (StrLen+1)*2;

  while (1) {
    Status = pBS->AllocatePool(EfiBootServicesData, LocalBufferSize, &LocalBuffer);
    ASSERT_EFI_ERROR(Status);
    if (LocalBufferSize <= Swprintf_s_va_list(LocalBuffer, LocalBufferSize, StrBuffer, ArgList) ) {
      Status = pBS->FreePool(LocalBuffer);
      ASSERT_EFI_ERROR(Status);
      LocalBufferSize*=2;
    } else {
      break;
    }
  }
      
  va_end(ArgList);
  
  Status = pAmiPostMgr->DisplayMsgBox(L"Intel ICC", LocalBuffer, type, &LocalAnswer);
  pBS->FreePool(StrBuffer);
  pBS->FreePool(LocalBuffer);

  ASSERT_EFI_ERROR (Status);
  if (answer != NULL) {
    *answer = LocalAnswer;
  }
  return Status;
}

ICC_LIB_STATUS 
EFIAPI
IccInitOverclocking (
  ICC_LIB_VERSION* Version
  )
/*++
Routine Description: 
  Initializes ICC OverClocking and asks about initial clock-related data. The data is:
  clock parameters from CURRENT record (will be displayed as current and boot-time frequencies)
  clock parameters from FLASH record (needed in case we try to write flash record later)
  clock ranges - max/min supported frequencies
Arguments:
  
Returns:
  EFI_SUCCESS      - if there were no errors, updates global variables
  EFI_DEVICE_ERROR - if there were errors when interfacing ICC OverClocking
  
--*/
{
  UINT8          i;
  ICC_LIB_STATUS IccStatus;

  gIccOverClockingProtocol->GetInfo(Version, &i, &IccStatus);

  if (IccStatus != ICC_LIB_STATUS_SUCCESS) {
    TRACE ((TRACE_ALWAYS, "(ICC) IccOverClocking failed to start. IccStatus=0x%x, version = %d.%d.%d.%d\n", IccStatus, Version->Major, Version->Minor, Version->Hotfix, Version->Build));
    return IccStatus;
  }

  return 0;
}

VOID
IccGetFrequencies (
  IN UINT8                  ClockNumber, 
  OUT CLOCK_DISPLAY_VALUES* Values
  )
/*++
Routine Description: 
  Called by Setup module, feeds it with clock data required to display all clock related information on bios setup screen
  Converts data from clock divider value to clock frequency
Arguments:
  ClockNumber - data for which clock should be returned
Returns:
  values - clock-related data required to display values on ICC setup screen
--*/
{
  ICC_LIB_STATUS     IccStatus;
  ICC_CLOCK_RANGES   ClockRange;
  ICC_CLOCK_SETTINGS Clocksetting;

  gIccOverClockingProtocol->GetClockRanges(ClockNumber, &ClockRange, &IccStatus);
  Values->ClockUsage =             (UINT16)ClockRange.UsageMask;
  Values->ClkFreqMax =             ClockRange.FrequencyMax/10000;
  Values->ClkFreqMin =             ClockRange.FrequencyMin/10000;
  Values->SscChangeAllowed =       (UINT8)ClockRange.SscChangeAllowed;
  Values->SscModeCenterAvailable = (UINT8)ClockRange.SscCenterAllowed;
  Values->SscModeUpAvailable =     (UINT8)ClockRange.SscUpAllowed;
  Values->SscModeDownAvailable =   (UINT8)ClockRange.SscDownAllowed;
  Values->SscPercentMax =          (UINT16)ClockRange.SscPercentMax;

  gIccOverClockingProtocol->GetCurrentClockSettings(ClockNumber, &Clocksetting, &IccStatus);
  Values->ClkFreqCurrent =         Clocksetting.Frequency/10000;
  Values->SscPercentCurrent =      (UINT16)Clocksetting.SscPercent;
  Values->SscModeCurrent =         SscModeToSscNumber(Clocksetting.SscMode);

}

UINT32 
SscNumberToSscMode (
  IN UINT8 SscModeNumber
  )
/*++
Routine Description: 
  Converts SSC mode description. ICC OverClocking uses 3 bit one-hot format. 
  For displaying things in BIOS setup, numeric value is more convenient
  This function should be called 3 times, once for each bit in ICC OverClocking format.
Arguments:
  SscModeNumber - mode number from BIOS setup  
  Mode - particular mode we're checking for
Returns:
  0 - SSC number does not represent Mode
  1 - SSC number represents Mode
--*/
{
  switch(SscModeNumber)
  {
    case SSC_MODE_NONE:
      return ICC_SSC_NONE;

    case SSC_MODE_UP:
      return ICC_SSC_UP;

    case SSC_MODE_CENTER:
      return ICC_SSC_CENTER;

    case SSC_MODE_DOWN:
      return ICC_SSC_DOWN;

    default:
      TRACE ((TRACE_ALWAYS, "(ICC) Invalid SscModeNumber value \n"));
      EFI_DEADLOOP();
      return 0;
  }
};

UINT8  
SscModeToSscNumber (
  IN UINT8 SscMode
  )
/*++
Routine Description: 
  Converts SSC mode description. ICC OverClocking uses 3 bit one-hot format. BIOS setup requires 8bit numeric value.
Arguments:
  three bits from ICC OverClocking format  
Returns:
  SSC mode in BIOS setup format
--*/
{
  switch(SscMode)
  {
    case ICC_SSC_NONE:
      return SSC_MODE_NONE;

    case ICC_SSC_UP:
      return SSC_MODE_UP;

    case ICC_SSC_CENTER:
      return SSC_MODE_CENTER;

    case ICC_SSC_DOWN:
      return SSC_MODE_DOWN;

    default:
      TRACE ((TRACE_ALWAYS, "(ICC) Invalid SscMode value \n"));
      EFI_DEADLOOP();
      return 0;
  }
}

VOID
SetIccPersistentData (
  IN UINT8 FlowPhase
)
/*++
Routine Description: 
  Sets ClocksModified field of IccPersistentData EFI variable
Arguments:
  new value of IccPersistentData  
Returns:
  none
--*/
{

  EFI_GUID            IccPersistentDataGuid = ICC_PERSISTENT_DATA_GUID;
  ICC_PERSISTENT_DATA IccPersistentData;

  IccPersistentData.ClocksModified = FlowPhase;

  pRS->SetVariable(
        L"IccPersistentData",
        &IccPersistentDataGuid,
        EFI_VARIABLE_NON_VOLATILE | EFI_VARIABLE_BOOTSERVICE_ACCESS,
        sizeof(IccPersistentData),
        &IccPersistentData );
}

UINT8
GetIccPersistentData (
  VOID
)
/*++
Routine Description: 
  Reads IccPersistentData EFI variable
Arguments:
  none  
Returns:
  value of ClocksModified field
--*/
{
  EFI_GUID            IccPersistentDataGuid = ICC_PERSISTENT_DATA_GUID;
  ICC_PERSISTENT_DATA IccPersistentData;
  UINTN               VariableSize;
  EFI_STATUS          Status;
  VariableSize = sizeof(IccPersistentData);
  
  Status = pRS->GetVariable(
                    L"IccPersistentData",
                    &IccPersistentDataGuid,
                    NULL,
                    &VariableSize,
                    &IccPersistentData );
  if(EFI_ERROR(Status))
    return ICC_SETTINGS_NOT_MODIFIED;
  else
    return IccPersistentData.ClocksModified;
}

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
