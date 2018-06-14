/** @file
  This file contines rouines responsible for handling the UI.

@copyright
  Copyright (c) 2012 - 2013 Intel Corporation. All rights reserved
  This software and associated documentation (if any) is furnished
  under a license and may only be used or copied in accordance
  with the terms of the license. Except as permitted by such
  license, no part of this software or documentation may be
  reproduced, stored in a retrieval system, or transmitted in any
  form or by any means without the express written consent of
  Intel Corporation.

  This file contains a 'Sample Driver' and is licensed as such
  under the terms of your license agreement with Intel or your
  vendor.  This file may be modified by the user, subject to
  the additional terms of the license agreement

**/
#include "AtAmUi.h"
#include EFI_PROTOCOL_CONSUMER (ConsoleControl)
#include EFI_PROTOCOL_CONSUMER (GraphicsOutput)
DXE_AT_POLICY_PROTOCOL    *mDxePlatformAtPolicy;
EFI_GUID                  gAlertAtHandlerGuid   = ME_ALERT_AT_HANDLER_GUID;
EFI_GUID                  gEfiAtAmProtocolGuid  = EFI_ATAM_PROTOCOL_GUID;
EFI_EVENT                 gAlertAtHandlerEvent;
EFI_ATAM_PROTOCOL         *mAtAm = NULL;

//
// Driver entry point
//
EFI_DRIVER_ENTRY_POINT (AtAmUiEntryPoint);

/**
  ATAM UI driver entry point.

  @param[in] ImageHandle          Handle for this drivers loaded image protocol.
  @param[in] SystemTable          EFI system table.

  @retval EFI_SUCCESS             The function completed successfully.
  @retval EFI_UNSUPPORTED         The function is unsupported by this driver
**/
EFI_STATUS
AtAmUiEntryPoint (
  IN EFI_HANDLE                   ImageHandle,
  IN EFI_SYSTEM_TABLE             *SystemTable
  )
{
  EFI_STATUS                      Status;

  EfiInitializeDriverLib (ImageHandle, SystemTable);
  Status = gBS->LocateProtocol (
                  &gDxePlatformAtPolicyGuid,
                  NULL,
                  &mDxePlatformAtPolicy
                  );
  if (EFI_ERROR (Status)) {
    DEBUG ((EFI_D_ERROR, "ATAM: No AT Platform Policy Protocol available"));
    return Status;
  }
  ASSERT_EFI_ERROR (Status);

  if (mDxePlatformAtPolicy->At.AtAmBypass == 1) {
    return EFI_SUCCESS;
  }

  if (mAtAm == NULL) {
    Status = gBS->LocateProtocol (
                    &gEfiAtAmProtocolGuid,
                    NULL,
                    (VOID **) &mAtAm
                    );
    if (EFI_ERROR (Status)) {
      DEBUG ((EFI_D_ERROR, "ATAM: ATAM Protocol failed, Status = %r\n", Status));
      return Status;
    } else {
      DEBUG ((EFI_D_ERROR, "ATAM: ATAM Protocol success, Status = %r\n", Status));
    }
  }

  Status = gBS->CreateEventEx (
                  EFI_EVENT_NOTIFY_SIGNAL,
                  EFI_TPL_CALLBACK,
                  AtAmUiCallback,
                  NULL,
                  &gAlertAtHandlerGuid,
                  &gAlertAtHandlerEvent
                  );

  if (EFI_ERROR (Status)) {
    DEBUG ((EFI_D_ERROR, "ATAM: AT - Error Creating Event to Process Suspend Mode\n"));
  }

  return Status;
}
EFI_CONSOLE_CONTROL_PROTOCOL    *ConsoleControl;
EFI_GRAPHICS_OUTPUT_PROTOCOL    *GraphicsOutput;
EFI_CONSOLE_CONTROL_SCREEN_MODE ScreenMode;
EFI_GRAPHICS_OUTPUT_MODE_INFORMATION *GraphicsModeInfo;
UINTN                           UgaBltSize = 0;
EFI_UGA_PIXEL                   *UgaBlt = NULL;
INT32                           TextMode;
UINTN StyleGetTextMode();

VOID
GraphicsSave
(
    VOID
)
{
  UINTN SizeOfGraphicsModeInfo;

  EFI_STATUS
  Status = gBS->LocateProtocol( &gEfiConsoleControlProtocolGuid, NULL, &ConsoleControl);

  if(EFI_ERROR(Status))
  {
    ConsoleControl = NULL;
    return;
  }

  Status = ConsoleControl->GetMode(ConsoleControl, &ScreenMode, NULL, NULL);
  if(ScreenMode == EfiConsoleControlScreenText)
  {
    ConsoleControl = NULL;
    return;    
  }

  Status = gBS->LocateProtocol( &gEfiGraphicsOutputProtocolGuid, NULL, &GraphicsOutput);
  if(EFI_ERROR(Status))
  {
    GraphicsOutput = NULL;
    return;
  }

  Status = GraphicsOutput->QueryMode( GraphicsOutput, GraphicsOutput->Mode->Mode,
                                      &SizeOfGraphicsModeInfo ,&GraphicsModeInfo);
  if(EFI_ERROR(Status))
  {
    GraphicsModeInfo = NULL;
    return;
  }

  UgaBltSize = GraphicsModeInfo->HorizontalResolution * 
               GraphicsModeInfo->VerticalResolution * 
               sizeof(EFI_UGA_PIXEL);

  UgaBlt = AllocateZeroPool (UgaBltSize);
  if( UgaBlt == NULL )
    return;

  Status = GraphicsOutput->Blt(
           GraphicsOutput,
           UgaBlt,
           EfiBltVideoToBltBuffer,
           0, 0,
           0, 0,
           GraphicsModeInfo->HorizontalResolution,
           GraphicsModeInfo->VerticalResolution,
           0);

  Status = ConsoleControl->SetMode( ConsoleControl, EfiConsoleControlScreenText );
  TextMode = gST->ConOut->Mode->Mode;
  gST->ConOut->SetMode(gST->ConOut, StyleGetTextMode());
}

VOID
GraphicsRestore
(
    VOID
)
{
  if(!ConsoleControl)
    return;

  gST->ConOut->SetMode(gST->ConOut, TextMode);
  ConsoleControl->SetMode( ConsoleControl, EfiConsoleControlScreenGraphics ); 

  if(!GraphicsOutput)
    return;

  if(!UgaBlt || !GraphicsModeInfo)
    return;
    
  GraphicsOutput->Blt(
           GraphicsOutput,
           UgaBlt,
           EfiBltBufferToVideo,
           0, 0,
           0, 0,
           GraphicsModeInfo->HorizontalResolution,
           GraphicsModeInfo->VerticalResolution,
           0);

  ZeroMem(UgaBlt, UgaBltSize);
  FreePool(UgaBlt);
}
/**
  ATAM UI callback.

  @param[in] Event                The event registered
  @param[in] Context              Event context. Not used in this event handler.

  @retval None
**/
VOID
EFIAPI
AtAmUiCallback (
  IN EFI_EVENT                    Event,
  IN VOID                         *Context
  )
{
  EFI_STATUS                      Status;
  DXE_AT_POLICY_PROTOCOL          *pAtPlatformPolicy;
  AT_STATE_INFO                   AtStateInfo;
  EFI_TPL                         TplBackup;

  pAtPlatformPolicy = NULL;

  DEBUG ((EFI_D_ERROR, "ATAM: AtAmUiCallback \n"));
  //
  // change TPL to APPLICATION as required by ConIn to function
  //
  TplBackup = gBS->RaiseTPL (TPL_HIGH_LEVEL);
  gBS->RestoreTPL (TplBackup);
  if (TplBackup != TPL_APPLICATION) {
    gBS->RestoreTPL(TPL_APPLICATION);
  }

  Status = gBS->LocateProtocol (
                  &gDxePlatformAtPolicyGuid,
                  NULL,
                  (VOID **) &pAtPlatformPolicy
                  );
  if (EFI_ERROR (Status)) {
    DEBUG ((EFI_D_ERROR, "ATAM: ATAM LocateProtocol failed. \n"));
  }

  if (mAtAm == NULL) {
    Status = gBS->LocateProtocol (
                    &gEfiAtAmProtocolGuid,
                    NULL,
                    (VOID **) &mAtAm
                    );
    if (EFI_ERROR (Status)) {
      DEBUG ((EFI_D_ERROR, "ATAM: ATAM Protocol failed, Status = %r\n", Status));
    }
  }

  mAtAm->AtAmGetAtStateInfo (mAtAm, &AtStateInfo);

  if (AtStateInfo.State == AT_STATE_STOLEN && pAtPlatformPolicy->At.AtPba == 1 && pAtPlatformPolicy->At.AtSupported == 0) {
    AtAmUiTheftNotification ();
    
  } else if (AtStateInfo.State == AT_STATE_STOLEN && AtStateInfo.flags.LockState == 1 && AtStateInfo.flags.AuthenticateModule == AT_AM_SELECTION_ATAM) {
    GraphicsSave();
    AtAmUiRecovery ();
    GraphicsRestore();
  } else if (AtStateInfo.State == AT_STATE_SUSPEND) {
    GraphicsSave();
    AtAmUiExitSuspendState ();
    GraphicsRestore();
  } else if (AtStateInfo.State == AT_STATE_ACTIVE) {
    if (pAtPlatformPolicy->At.AtEnterSuspendState) {
      GraphicsSave();
      AtAmUiEnterSuspendState ();
      GraphicsRestore();
    }
  }

  //
  // Restore TPL
  //
  if (TplBackup != TPL_APPLICATION) {
    gBS->RaiseTPL(TplBackup);
  }


  return;
}

/**
  Function handling entering suspend mode.

  @retval EFI_SUCCESS             The function completed successfully.
  @retval EFI_OUT_OF_RESOURCES    Unable to allocate necessary data structures.
**/
EFI_STATUS
AtAmUiEnterSuspendState (
  VOID
  )
{
  EFI_STATUS              Status;
  UINT8                   *PasswordASCII;
  CHAR16                  *PasswordUNICODE;
  CHAR16                  *UniCodeNonceStr;
  UINT32                  NumOfAttempts;
  UINT8                   NonceStr[STR_NONCE_LENGTH];
  UINT32                  CRow;
  UINT32                  CCol;
  UINT8                   *IsvString;
  UINT32                  IsvId;
  AT_BIOS_RECOVERY_CONFIG RecoveryConfig;

  Status          = EFI_SUCCESS;
  NumOfAttempts   = ATAMUI_SUSPEND_ATTEMPTS;

  UniCodeNonceStr = AllocateZeroPool ((STR_NONCE_LENGTH + 1) * sizeof (CHAR16));
  PasswordASCII   = AllocateZeroPool ((ATAM_SETUP_PASSWORD_LENGTH + 1) * sizeof (UINT8));
  PasswordUNICODE = AllocateZeroPool ((ATAM_SETUP_PASSWORD_LENGTH + 1) * sizeof (CHAR16));
  IsvString       = AllocateZeroPool ((RECOVERY_STRING_LENGTH + 1) * sizeof (UINT8));

  if (PasswordASCII == NULL || PasswordUNICODE == NULL || UniCodeNonceStr == NULL || IsvString == NULL) {
    return EFI_OUT_OF_RESOURCES;
  }

  if (mAtAm == NULL) {
    Status = gBS->LocateProtocol (
                    &gEfiAtAmProtocolGuid,
                    NULL,
                    (VOID **) &mAtAm
                    );
    if (EFI_ERROR (Status)) {
      DEBUG ((EFI_D_ERROR, "ATAM: ATAM Protocol failed, Status = %r\n", Status));
    }
  }

  AtAmUiStrGetCursor (&CRow, &CCol);

  do {
    AtAmUiStrClearScreen ();

    RecoveryConfig.IsvPlatformId[0] = L'\0';
    Status = mAtAm->AtAmGetRecoveryConfig (mAtAm, &RecoveryConfig);
    if (EFI_ERROR (Status)) {
      DEBUG ((EFI_D_ERROR, "ATAM: AtAmGetRecoveryConfig command failed, Status = %r\n", Status));
    }
    if (RecoveryConfig.IsvPlatformId[0] != L'\0') {
      AtAmUiStrSetCursor(4, 13);
      AtAmUiStrDisplayFix (STR_ATAMUI_PLATFORM_ID, FALSE);
      AtAmUiStrDisplay ((CHAR16 *) RecoveryConfig.IsvPlatformId);
    }

    AtAmUiStrSetCursor(4, 14);
    Status = mAtAm->AtAmGetIsvId (mAtAm, IsvString, &IsvId);
    if (EFI_ERROR (Status)) {
      DEBUG ((EFI_D_ERROR, "ATAM: AtAmGetIsvId command failed, Status = %r\n", Status));
    }
    AtAmUiStrDisplay ((CHAR16 *) IsvString);

    AtAmUiStrEnableCursor (FALSE);

    AtAmUiStrDisplayFix (STR_ATAMUI_SUS_ENTER_INFO, TRUE);

    AtAmUiStrSetCursor (4, 2);
    AtAmUiStrDisplayFix (STR_ATAMUI_SUS_REFER, FALSE);
    Status = mAtAm->AtAmGetNonce (mAtAm, NonceStr);
    if (Status == EFI_SUCCESS) {
      Uint8ToUnicode (NonceStr, UniCodeNonceStr);
      AtAmUiStrDisplay ((UINT16 *) UniCodeNonceStr);
    } else {
      AtAmUiStrDisplayFix (STR_ATAMUI_SUS_NONCE_FAILED, FALSE);
      DEBUG ((EFI_D_ERROR, "ATAM: Get Nonce failed, Status = %r\n", Status));
    }

    AtAmUiStrDisplayFix (STR_ATAMUI_SUS_ENTER_TOKEN, TRUE);
    AtAmUiStrEnableCursor (TRUE);
    AtAmUiGetPassword (PasswordASCII, ATAM_SETUP_PASSWORD_LENGTH, PasswordUNICODE, 1);
    AtAmUiStrEnableCursor (FALSE);

    Status = mAtAm->AtAmSetSuspendState (mAtAm, ATAM_ENTER_SUSPEND_STATE, PasswordASCII);
    if (Status != EFI_SUCCESS) {
      AtAmUiStrDisplayFix (STR_ATAMUI_SUS_ENTER_FAILED, TRUE);
      AtAmUiDelay (2 * AT_AM_UI_1_SECOND);
    }

  } while (--NumOfAttempts && (Status != EFI_SUCCESS));

  if (Status == EFI_SUCCESS) {
    AtAmUiStrDisplayFix (STR_ATAMUI_SUS_ENTER_SUCCESS, TRUE);
  } else {
    AtAmUiStrDisplayFix (STR_ATAMUI_SUS_ATTEMPT_EXC, TRUE);
  }

  ZeroMem (UniCodeNonceStr, (STR_NONCE_LENGTH + 1) * sizeof (UINT16));
  ZeroMem (PasswordASCII, (ATAM_SETUP_PASSWORD_LENGTH + 1) * sizeof (CHAR8));
  ZeroMem (PasswordUNICODE, (ATAM_SETUP_PASSWORD_LENGTH + 1) * sizeof (CHAR16));

  FreePool (UniCodeNonceStr);
  FreePool (PasswordASCII);
  FreePool (PasswordUNICODE);

  AtAmUiDelay (AT_AM_UI_1_SECOND);

  AtAmUiStrClearScreen ();
  AtAmUiStrSetCursor (CCol, CRow);

  return Status;
}

/**
  Function handling exiting suspend mode.

  @param[in] None

  @retval EFI_SUCCESS             The function completed successfully.
  @retval EFI_OUT_OF_RESOURCES    Unable to allocate necessary data structures.
**/
EFI_STATUS
AtAmUiExitSuspendState (
  VOID
  )
{
  EFI_STATUS              Status;
  UINT8                   *PasswordASCII;
  CHAR16                  *PasswordUNICODE;
  CHAR16                  *UniCodeNonceStr;
  UINT32                  NumOfAttempts;
  UINT8                   NonceStr[STR_NONCE_LENGTH];
  EFI_INPUT_KEY           Key;
  UINT32                  CRow;
  UINT32                  CCol;
  UINT8                   *IsvString;
  UINT32                  IsvId;
  AT_BIOS_RECOVERY_CONFIG RecoveryConfig;

  Status          = EFI_SUCCESS;
  NumOfAttempts   = 3;

  UniCodeNonceStr = AllocateZeroPool ((STR_NONCE_LENGTH + 1) * sizeof (CHAR16));
  PasswordASCII   = AllocateZeroPool ((ATAM_SETUP_PASSWORD_LENGTH + 1) * sizeof (UINT8));
  PasswordUNICODE = AllocateZeroPool ((ATAM_SETUP_PASSWORD_LENGTH + 1) * sizeof (CHAR16));
  IsvString       = AllocateZeroPool ((RECOVERY_STRING_LENGTH + 1) * sizeof (UINT8));

  if (PasswordASCII == NULL || PasswordUNICODE == NULL || UniCodeNonceStr == NULL || IsvString == NULL) {
    return EFI_OUT_OF_RESOURCES;
  }

  if (mAtAm == NULL) {
    Status = gBS->LocateProtocol (
                    &gEfiAtAmProtocolGuid,
                    NULL,
                    (VOID **) &mAtAm
                    );
    if (EFI_ERROR (Status)) {
      DEBUG ((EFI_D_ERROR, "ATAM: ATAM Protocol failed, Status = %r\n", Status));
    }
  }

  AtAmUiStrGetCursor (&CRow, &CCol);

  do {
    AtAmUiStrClearScreen ();
    AtAmUiStrDisplayFix (STR_ATAMUI_SUS_EXIT_QUESTION, TRUE);

    AtAmUiStrGetChar (&Key);
    if (Key.UnicodeChar == L'y' || Key.UnicodeChar == L'Y' || Key.UnicodeChar == L'n' || Key.UnicodeChar == L'N') {
      AtAmUiStrEnableCursor(FALSE);
      break;
    }
  } while (1);

  if (Key.UnicodeChar == L'y' || Key.UnicodeChar == L'Y') {
    do {
      AtAmUiStrClearScreen ();

      RecoveryConfig.IsvPlatformId[0] = L'\0';
      Status = mAtAm->AtAmGetRecoveryConfig (mAtAm, &RecoveryConfig);
      if (EFI_ERROR (Status)) {
        DEBUG ((EFI_D_ERROR, "ATAM: AtAmGetRecoveryConfig command failed, Status = %r\n", Status));
      }
      if (RecoveryConfig.IsvPlatformId[0] != L'\0') {
        AtAmUiStrSetCursor(4, 13);
        AtAmUiStrDisplayFix (STR_ATAMUI_PLATFORM_ID, FALSE);
        AtAmUiStrDisplay ((CHAR16 *) RecoveryConfig.IsvPlatformId);
      }

      AtAmUiStrSetCursor(4, 14);
      Status = mAtAm->AtAmGetIsvId (mAtAm, IsvString, &IsvId);
      if (EFI_ERROR (Status)) {
        DEBUG ((EFI_D_ERROR, "ATAM: AtAmGetIsvId command failed, Status = %r\n", Status));
      }
      AtAmUiStrDisplay ((CHAR16 *) IsvString);

      AtAmUiStrEnableCursor (FALSE);

      AtAmUiStrDisplayFix (STR_ATAMUI_SUS_EXIT_INFO, TRUE);

      AtAmUiStrSetCursor (4, 3);
      AtAmUiStrDisplayFix (STR_ATAMUI_RES_REFER, FALSE);
      mAtAm->AtAmGetNonce (mAtAm, NonceStr);
      Uint8ToUnicode (NonceStr, UniCodeNonceStr);
      AtAmUiStrDisplay ((UINT16 *) UniCodeNonceStr);

      AtAmUiStrSetCursor (4, 4);
      AtAmUiStrDisplayFix (STR_ATAMUI_SUS_ENTER_TOKEN, FALSE);

      AtAmUiStrEnableCursor (TRUE);
      AtAmUiGetPassword (PasswordASCII, ATAM_SETUP_PASSWORD_LENGTH, PasswordUNICODE, 1);
      AtAmUiStrEnableCursor (FALSE);

      AtAmUiStrDisplayFix (STR_ATAMUI_CHECKING_AUTHENT, TRUE);

      Status = mAtAm->AtAmSetSuspendState (mAtAm, ATAM_EXIT_SUSPEND_STATE, PasswordASCII);
      if (Status != EFI_SUCCESS) {
        AtAmUiStrDisplayFix (STR_ATAMUI_SUS_AUTH_FAILED, FALSE);
        AtAmUiDelay (AT_AM_UI_1_SECOND);
      }

      AtAmUiDelay (AT_AM_UI_1_SECOND);
    } while (--NumOfAttempts && (Status != EFI_SUCCESS));

    if (Status == EFI_SUCCESS) {
      AtAmUiStrDisplayFix (STR_ATAMUI_SUS_EXIT_SUCCESS, TRUE);

    } else {
      AtAmUiStrDisplayFix (STR_ATAMUI_SUS_ATTEMPT_EXC, TRUE);
      AtAmUiDelay (AT_AM_UI_1_SECOND);
    }
  } else if (Key.UnicodeChar == L'n' || Key.UnicodeChar == L'N') {
    AtAmUiStrDisplayFix (STR_ATAMUI_SUS_STAY, TRUE);
    AtAmUiDelay (2  *AT_AM_UI_1_SECOND);
  }

  ZeroMem (UniCodeNonceStr, (STR_NONCE_LENGTH + 1) * sizeof (UINT16));
  ZeroMem (PasswordASCII, (ATAM_SETUP_PASSWORD_LENGTH + 1) * sizeof (CHAR8));
  ZeroMem (PasswordUNICODE, (ATAM_SETUP_PASSWORD_LENGTH + 1) * sizeof (CHAR16));

  FreePool (UniCodeNonceStr);
  FreePool (PasswordASCII);
  FreePool (PasswordUNICODE);

  AtAmUiDelay (AT_AM_UI_1_SECOND);

  AtAmUiStrClearScreen ();
  AtAmUiStrSetCursor (CCol, CRow);

  return Status;
}

VOID
EFIAPI
ShowAtTimerCallback (
  IN EFI_EVENT Event,
  IN VOID      *Context
  )
{
  UINT32            TimerLeft;
  UINT32            TimerInterval;
  static CHAR16     *TimeLeftStr = NULL;
  EFI_STATUS        Status;
  UINT32            CRow;
  UINT32            CCol;

  if(!TimeLeftStr)
    TimeLeftStr     = AllocateZeroPool ((ATAM_TIMER_STRING_LENGTH + 1) * sizeof (CHAR16));

  AtAmUiStrGetCursor (&CRow, &CCol);
  Status = mAtAm->AtAmGetTimer (mAtAm, &TimerLeft, &TimerInterval);

  if(EFI_ERROR(Status))
    return;

  UnicodeValueToString (TimeLeftStr, 0, TimerLeft, 0);
  AtAmUiStrDisplayFix (STR_ATAMUI_TIME_LEFT, TRUE);
  AtAmUiStrDisplay ((CHAR16 *) TimeLeftStr);
  AtAmUiStrDisplayFix (STR_ATAMUI_TIME_LEFT_SEC,FALSE);

  AtAmUiStrSetCursor(CCol,CRow);
}
// Set the default TEXT MODE resolution the same with TSE
#define MAX_ROWS    (UINT8)(31)
#define MAX_COLS    (UINT8)(100)
UINTN StyleGetTextMode()
{
  EFI_STATUS Status;
  INT32 i;
  UINTN ModeRows, ModeCols;


  // Default Implementation
  for ( i = 0; i < gST->ConOut->Mode->MaxMode; i++ )
  {
    Status = gST->ConOut->QueryMode( gST->ConOut, i, &ModeCols, &ModeRows );

    if ( EFI_ERROR( Status ) )
      continue;

    if ( ( MAX_COLS <= ModeCols ) && ( MAX_ROWS <= ModeRows ) )
      return i;
  }

  // return MaxMode if the mode wasn't found
  return i;
}
/**
  Function handling recovery proccess.

  @param[in] None

  @retval EFI_SUCCESS             The function completed successfully.
  @retval EFI_OUT_OF_RESOURCES    Unable to allocate necessary data structures.
**/
EFI_STATUS
AtAmUiRecovery (
  VOID
  )
{
  EFI_STATUS        Status;
  EFI_INPUT_KEY     Key;
  UINT32            PassType;
  UINT8             IsAuthenticated;
  AT_STATE_INFO     StateInfo;
  UINT32            TimerLeft;
  UINT32            TimerInterval;
  UINT8             *PasswordASCII;
  CHAR16            *PasswordUNICODE;
  CHAR16            *TimeLeftStr;
  UINT8             *IsvString;
  UINT32            CRow;
  UINT32            CCol;
  UINT32            NumberOfAttempts;
  UINT32            IsvId;
  CHAR16            *UniCodeNonceStr;
  UINT8             NonceStr[STR_NONCE_LENGTH];

  IsAuthenticated = 0;

  PasswordASCII   = AllocateZeroPool ((ATAM_SETUP_PASSWORD_LENGTH + 1) * sizeof (UINT8));
  PasswordUNICODE = AllocateZeroPool ((ATAM_SETUP_PASSWORD_LENGTH + 1) * sizeof (CHAR16));
  TimeLeftStr     = AllocateZeroPool ((ATAM_TIMER_STRING_LENGTH + 1) * sizeof (CHAR16));
  IsvString       = AllocateZeroPool ((RECOVERY_STRING_LENGTH + 1) * sizeof (UINT8));
  UniCodeNonceStr = AllocateZeroPool ((STR_NONCE_LENGTH + 1) * sizeof (CHAR16));

  if (PasswordASCII == NULL || PasswordUNICODE == NULL || TimeLeftStr == NULL || IsvString == NULL || UniCodeNonceStr == NULL) {
    return EFI_OUT_OF_RESOURCES;
  }

  if (mAtAm == NULL) {
    Status = gBS->LocateProtocol (
                    &gEfiAtAmProtocolGuid,
                    NULL,
                    (VOID **) &mAtAm
                    );
    if (EFI_ERROR (Status)) {
      DEBUG ((EFI_D_ERROR, "ATAM: ATAM Protocol failed, Status = %r\n", Status));
    }
  }

  AtAmUiStrGetCursor (&CRow, &CCol);

  NumberOfAttempts = 3;

  do {
    AtAmUiStrClearScreen ();
    AtAmUiDisplayIsvStrings ();

    do {
      AtAmUiStrEnableCursor (FALSE);

      AtAmUiStrSetCursor(4, 20);
      Status = mAtAm->AtAmGetIsvId (mAtAm, IsvString, &IsvId);
      if (EFI_ERROR (Status)) {
        DEBUG ((EFI_D_ERROR, "ATAM: AtAmGetIsvId command failed, Status = %r\n", Status));
      }
      AtAmUiStrDisplay ((CHAR16 *) IsvString);

      mAtAm->AtAmGetAtStateInfo (mAtAm, &StateInfo);
      AtAmUiStrDisplayFix (STR_ATAMUI_LOCK_DUE_TO, TRUE);
      switch (StateInfo.LastTheftTrigger) {
      case 1:
        AtAmUiStrDisplayFix (STR_ATAMUI_LOCK_TIME, FALSE);
        break;

      case 2:
        AtAmUiStrDisplayFix (STR_ATAMUI_LOCK_STOLEN, FALSE);
        break;

      case 3:
        AtAmUiStrDisplayFix (STR_ATAMUI_LOCK_THRESHOLD, FALSE);
        break;

      case 4:
        AtAmUiStrDisplayFix (STR_ATAMUI_LOCK_ATTACK, FALSE);

      default:
        break;
      }

      mAtAm->AtAmGetTimer (mAtAm, &TimerLeft, &TimerInterval);
      UnicodeValueToString (TimeLeftStr, 0, TimerLeft, 0);

      AtAmUiStrDisplayFix (STR_ATAMUI_TIME_LEFT, TRUE);
      AtAmUiStrDisplay ((CHAR16 *) TimeLeftStr);
      AtAmUiStrDisplayFix (STR_ATAMUI_TIME_LEFT_SEC,FALSE);

      AtAmUiStrDisplayFix (STR_ATAMUI_SELECT_PASS, TRUE);

      AtAmUiStrDisplayFix (STR_ATAMUI_SELECT_OPTION, TRUE);

      AtAmUiStrGetChar (&Key);
      if (Key.UnicodeChar == L'1' || Key.UnicodeChar == L'2') {
        break;
      }

      AtAmUiStrDisplayFix (STR_ATAMUI_INVALID_SELECT, TRUE);
    } while (1);

    AtAmUiStrClearScreen ();
    AtAmUiDisplayIsvStrings ();
    AtAmUiStrSetCursor(4, 20);
    AtAmUiStrDisplay ((CHAR16 *) IsvString);
    AtAmUiStrDisplayFix (STR_ATAMUI_LOCK_DUE_TO, TRUE);
    switch (StateInfo.LastTheftTrigger) {
    case 1:
      AtAmUiStrDisplayFix (STR_ATAMUI_LOCK_TIME, FALSE);
      break;

    case 2:
      AtAmUiStrDisplayFix (STR_ATAMUI_LOCK_STOLEN, FALSE);
      break;

    case 3:
      AtAmUiStrDisplayFix (STR_ATAMUI_LOCK_THRESHOLD, FALSE);
      break;

    case 4:
      AtAmUiStrDisplayFix (STR_ATAMUI_LOCK_ATTACK, FALSE);

    default:
      break;
    }
    mAtAm->AtAmGetTimer (mAtAm, &TimerLeft, &TimerInterval);
    UnicodeValueToString (TimeLeftStr, 0, TimerLeft, 0);
    AtAmUiStrDisplayFix (STR_ATAMUI_TIME_LEFT, TRUE);
    AtAmUiStrDisplay ((CHAR16 *) TimeLeftStr);
    AtAmUiStrDisplayFix (STR_ATAMUI_TIME_LEFT_SEC,FALSE);

    switch (Key.UnicodeChar) {
    case L'1':
      PassType = AT_CREDENTIAL_TYPE_USER_PASSPHRASE;
      AtAmUiStrDisplayFix (STR_ATAMUI_USER_PASS, TRUE);
      AtAmUiStrDisplayFix (STR_ATAMUI_RECO_ENTER_PASS, TRUE);
      AtAmUiStrEnableCursor (TRUE);
      AtAmUiGetPassword (PasswordASCII, ATAM_SETUP_PASSWORD_LENGTH, PasswordUNICODE, 0);
      AtAmUiStrEnableCursor (FALSE);
      AtAmUiStrDisplayFix (STR_ATAMUI_CHECKING_PASS, TRUE);
      AtAmUiDelay (AT_AM_UI_1_SECOND);
      Status = mAtAm->AtAmVerifyPassword (mAtAm, PasswordASCII, PassType, &IsAuthenticated);
      DEBUG ((EFI_D_ERROR, "ATAM: IsAuthenticated %x\n", IsAuthenticated));

      break;

    case L'2':
      AtAmUiStrDisplayFix (STR_ATAMUI_RECO_REFER, TRUE);
      Status = mAtAm->AtAmGetNonce (mAtAm, NonceStr);
      if (Status == EFI_SUCCESS) {
        Uint8ToUnicode (NonceStr, UniCodeNonceStr);
        AtAmUiStrDisplay ((UINT16 *) UniCodeNonceStr);
      } else {
        AtAmUiStrDisplayFix (STR_ATAMUI_SUS_NONCE_FAILED, FALSE);
        DEBUG ((EFI_D_ERROR, "ATAM: Get Nonce failed, Status = %r\n", Status));
      }
      AtAmUiStrDisplayFix (STR_ATAMUI_SERV_BASED_RECOV, TRUE);
      AtAmUiStrSetCursor(4, 6);
      AtAmUiStrDisplayFix (STR_ATAMUI_RECO_SEC_TOKEN, FALSE);

      PassType = AT_CREDENTIAL_TYPE_SRTK;

      AtAmUiStrEnableCursor (TRUE);
      AtAmUiGetPassword (PasswordASCII, ATAM_SETUP_PASSWORD_LENGTH, PasswordUNICODE, 1);
      AtAmUiStrEnableCursor (FALSE);

      AtAmUiStrDisplayFix (STR_ATAMUI_CHECKING_PASS, TRUE);
      AtAmUiDelay (AT_AM_UI_1_SECOND);
      Status = mAtAm->AtAmVerifyPassword (mAtAm, PasswordASCII, PassType, &IsAuthenticated);
      DEBUG ((EFI_D_ERROR, "ATAM: IsAuthenticated %x\n", IsAuthenticated));

      break;

    default:
      DEBUG ((EFI_D_ERROR, "ATAM: Option not supported. \n"));

      break;
    }

    ZeroMem (PasswordASCII, (ATAM_SETUP_PASSWORD_LENGTH + 1) * sizeof (UINT8));
    ZeroMem (PasswordUNICODE, (ATAM_SETUP_PASSWORD_LENGTH + 1) * sizeof (CHAR16));

    NumberOfAttempts--;

    if (NumberOfAttempts && IsAuthenticated == 0) {
      AtAmUiStrDisplayFix (STR_ATAMUI_RECO_TRY_AGAIN, TRUE);
      AtAmUiDelay (AT_AM_UI_1_SECOND);
    }

  } while (NumberOfAttempts && (IsAuthenticated == 0));

  FreePool (TimeLeftStr);
  FreePool (PasswordASCII);
  FreePool (PasswordUNICODE);
  FreePool (IsvString);
  FreePool (UniCodeNonceStr);

  if (IsAuthenticated == 1) {
    AtAmUiStrDisplayFix (STR_ATAMUI_RECO_SUCCESS, TRUE);
    AtAmUiDelay (2 * AT_AM_UI_1_SECOND);
  } else {
    AtAmUiStrDisplayFix (STR_ATAMUI_RECO_FAILED, TRUE);
    AtAmUiDelay (2 * AT_AM_UI_1_SECOND);
    gRT->ResetSystem (EfiResetShutdown, EFI_SUCCESS, 0, NULL);
  }

  AtAmUiDelay (AT_AM_UI_1_SECOND);
  AtAmUiStrClearScreen ();
  AtAmUiStrSetCursor(CCol, CRow);

  return Status;
}

/**
  Function displaing Ivs strings.

  @param[in] None

  @retval EFI_SUCCESS             The function completed successfully.
  @retval EFI_OUT_OF_RESOURCES    Unable to allocate necessary data structures.
**/
EFI_STATUS
AtAmUiDisplayIsvStrings (
  VOID
  )
{
  EFI_STATUS              Status;
  CHAR16                  *IsvIdString;
  AT_BIOS_RECOVERY_CONFIG RecoveryConfig;
  UINT8                   *IsvString;
  UINT32                  IsvId;
  UINT32                  CRow;
  UINT32                  CCol;

  IsvId = 0;

  DEBUG ((EFI_D_ERROR, "ATAM: AtAmUiDisplayIsvStrings. \n"));

  IsvIdString = AllocateZeroPool (ISV_PLATFORM_ID_LENGTH * sizeof (CHAR16));
  IsvString   = AllocateZeroPool ((RECOVERY_STRING_LENGTH + 1) * sizeof (UINT8));
  if (IsvIdString == NULL || IsvString == NULL) {
    return EFI_OUT_OF_RESOURCES;
  }

  if (mAtAm == NULL) {
    Status = gBS->LocateProtocol (
                    &gEfiAtAmProtocolGuid,
                    NULL,
                    (VOID **) &mAtAm
                    );
    if (EFI_ERROR (Status)) {
      DEBUG ((EFI_D_ERROR, "ATAM: ATAM Protocol failed, Status = %r\n", Status));
    }
  }

  AtAmUiStrGetCursor (&CRow, &CCol);

  Status = mAtAm->AtAmGetIsvId (mAtAm, IsvString, &IsvId);
  if (EFI_ERROR (Status)) {
    DEBUG ((EFI_D_ERROR, "ATAM: AtAmGetIsvId command failed, Status = %r\n", Status));
  }

  RecoveryConfig.IsvPlatformId[0] = L'\0';
  Status = mAtAm->AtAmGetRecoveryConfig (mAtAm, &RecoveryConfig);
  if (EFI_ERROR (Status)) {
    DEBUG ((EFI_D_ERROR, "ATAM: AtAmGetRecoveryConfig command failed, Status = %r\n", Status));
  }

  if (RecoveryConfig.IsvPlatformId[0] != L'\0') {
    AtAmUiStrDisplayFix (STR_ATAMUI_PLATFORM_ID, TRUE);
    AtAmUiStrDisplay ((CHAR16 *) RecoveryConfig.IsvPlatformId);
  }

  if (IsvId != 0) {
    UnicodeValueToString (IsvIdString, 0, (UINT32) IsvId, 0);
    AtAmUiStrDisplayFix (STR_ATAMUI_PROVIDER_ID, TRUE);
    AtAmUiStrDisplay (IsvIdString);
  }

  FreePool (IsvString);
  FreePool (IsvIdString);

  return Status;
}

/**
  This GetRecoveryPassword() process the AT recovery password user input.

  @param[out] PasswordASCII       Pointer to an array of ASCII user input
  @param[in] MaxPasswordLength    Integer value for max password length
  @param[out] PasswordUNICODE     Pointer to an array of UNICODE user input
  @param[in] ShowPassword         TRUE - password is shown, FALSE - pasword is hidden by *

  @retval EFI_SUCCESS             The function completed successfully.
  @retval EFI_OUT_OF_RESOURCES Do not have enough resources to allocate memory or password too long.
**/
EFI_STATUS
AtAmUiGetPassword (
  OUT UINT8                       *PasswordASCII,
  IN INTN                         MaxPasswordLength,
  OUT CHAR16                      *PasswordUNICODE,
  IN UINT8                        ShowPassword
  )
{
  INTN                            StrIndex;
  EFI_INPUT_KEY                   Key         = { 0, 0 };
  CHAR16                          StarChar[2] = { L' ', L'\0' };

  DEBUG ((EFI_D_ERROR, "ATAM: AtAmUiGetRecoveryPassword \n"));

  PasswordASCII[0]    = L'\0';
  PasswordUNICODE[0]  = L'\0';

  Key.UnicodeChar     = 0;
  Key.ScanCode        = 0;
  StrIndex            = 0;

  DEBUG ((EFI_D_ERROR, "ATAM: Wait for Key \n"));

  AtAmUiStrEnableCursor (TRUE);
  do {
    Key.ScanCode    = 0;
    Key.UnicodeChar = 0;
    AtAmUiStrGetChar (&Key);
    DEBUG ((EFI_D_ERROR, "ATAM: PasswordUNICODE: %s\n", PasswordUNICODE));

    switch (Key.UnicodeChar) {
    case CHAR_NULL:
      ///
      /// Non-printable characters handling: do not print caps/numlock, pgup/dn, Fx, cursors etc.
      /// When escape pressed, return with empty password and ask for password again
      ///
      if (Key.ScanCode == SCAN_ESC) {
        PasswordASCII[0]    = L'\0';
        PasswordUNICODE[0]  = L'\0';
        StrIndex            = 0;
        return EFI_SUCCESS;
      }
      break;

  case CHAR_CARRIAGE_RETURN:
      ///
      /// Enter handling: when enter pressed, return with the password
      ///
      StrIndex  = 0;

      DEBUG ((EFI_D_ERROR, "ATAM: Passphrase Entered: %s\n", PasswordUNICODE));
      return EFI_SUCCESS;

    case CHAR_BACKSPACE:
      ///
      /// Backspace handling
      ///
      if (StrIndex > 0) {
        StrIndex--;
        PasswordASCII[StrIndex] = L'\0';
        PasswordUNICODE[StrIndex] = L'\0';
        ///
        /// Backspace printing on screen
        ///
        AtAmUiStrDisplay (L"\b \b");
      }
      break;

    default:
      ///
      /// Normal (printable) characters handling
      /// Do not hide password on screen for Server Token Password recovery (usrRsp=2)
      /// Hide password with '*' for User Password recovery (usrRsp=1)
      ///
      StarChar[0] = (ShowPassword == 1) ? Key.UnicodeChar : L'*';

      if (StrIndex >= 0 && StrIndex < MaxPasswordLength) {
        ///
        /// Index in range
        ///
        PasswordASCII[StrIndex] = (UINT8) Key.UnicodeChar;
        PasswordUNICODE[StrIndex] = Key.UnicodeChar;
        StrIndex++;
        ///
        /// Print hidden (*) or unhidden password character
        ///
        AtAmUiStrDisplay (StarChar);
      } else if (StrIndex < 0) {
        ///
        /// Index out of range: StrIndex < 0 - should never go here
        ///
        AtAmUiStrEnableCursor (FALSE);
        StrIndex = 0;
      } else {
        ///
        /// Index out of range: StrIndex >= ATAM_SETUP_PASSWORD_LENGTH - max password length (49 chars) exceeded,
        /// only backspace, enter or escape will be accepted
        ///
        DEBUG ((EFI_D_ERROR, "ATAM: Password Length Exceeded\n"));
      }
      break;
    }

  } while (1);

  AtAmUiStrEnableCursor (FALSE);

  return EFI_TIMEOUT;
}

/**
  Function displaing Ivs strings.

  @param[in] None

  @retval EFI_SUCCESS             The function completed successfully.
  @retval EFI_OUT_OF_RESOURCES    Unable to allocate necessary data structures.
**/
EFI_STATUS
AtAmUiTheftNotification (
  VOID
  )
{
  EFI_STATUS        Status;
  AT_STATE_INFO     StateInfo;
  UINT32            TimerLeft;
  UINT32            TimerInterval;
  UINT8             *IsvString;
  UINT32            IsvId;
  CHAR16            *TimeLeftStr;
  UINT8             PbaFailedExceeded;
  UINT16            PbaFailedAttempts;
  UINT16            PbaFailedThreshold;

  DEBUG ((EFI_D_ERROR, "ATAM: AtAmUiTheftNotification\n"));

  Status              = EFI_SUCCESS;
  PbaFailedExceeded   = FALSE;

  Status = gBS->LocateProtocol (
                  &gEfiAtAmProtocolGuid,
                  NULL,
                  (VOID **) &mAtAm
                  );
  if (EFI_ERROR (Status)) {
    DEBUG ((EFI_D_ERROR, "ATAM: ATAM failed = %r\n", Status));
    return Status;
  }

  Status = mAtAm->AtAmGetPbaCounter(&PbaFailedExceeded, &PbaFailedAttempts, &PbaFailedThreshold);
  if (EFI_ERROR (Status)) {
    DEBUG ((EFI_D_ERROR, "ATAM: AtAmGetIsvId  = %r\n", Status));
    return Status;
  }

  if (PbaFailedThreshold >= PbaFailedAttempts) {
    return EFI_SUCCESS;
  } else {

    IsvString     = AllocateZeroPool ((RECOVERY_STRING_LENGTH + 1) * sizeof (UINT8));
    TimeLeftStr   = AllocateZeroPool ((ATAM_TIMER_STRING_LENGTH + 1) * sizeof (CHAR16));

    if (IsvString == NULL  || TimeLeftStr == NULL) {
      return EFI_OUT_OF_RESOURCES;
    }

    AtAmUiStrClearScreen ();

    AtAmUiDisplayIsvStrings ();

    AtAmUiStrEnableCursor (FALSE);

    AtAmUiStrSetCursor(4, 20);
    Status = mAtAm->AtAmGetIsvId (mAtAm, IsvString, &IsvId);
    if (EFI_ERROR (Status)) {
      DEBUG ((EFI_D_ERROR, "ATAM: AtAmGetIsvId, Status = %r\n", Status));
    }

    AtAmUiStrDisplay ((CHAR16 *) IsvString);

    mAtAm->AtAmGetAtStateInfo (mAtAm, &StateInfo);
    AtAmUiStrDisplayFix (STR_ATAMUI_LOCK_DUE_TO, TRUE);
    switch (StateInfo.LastTheftTrigger) {
      case 1:
        AtAmUiStrDisplayFix (STR_ATAMUI_LOCK_TIME, FALSE);
        break;

      case 2:
        AtAmUiStrDisplayFix (STR_ATAMUI_LOCK_STOLEN, FALSE);
        break;

      case 3:
        AtAmUiStrDisplayFix (STR_ATAMUI_LOCK_THRESHOLD, FALSE);
        break;

      case 4:
        AtAmUiStrDisplayFix (STR_ATAMUI_LOCK_ATTACK, FALSE);

      default:
        break;
    }

    mAtAm->AtAmGetTimer (mAtAm, &TimerLeft, &TimerInterval);
    UnicodeValueToString (TimeLeftStr, 0, TimerLeft, 0);
    
    AtAmUiStrDisplayFix (STR_ATAMUI_TIME_LEFT, TRUE);
    AtAmUiStrDisplay ((CHAR16 *) TimeLeftStr);
    AtAmUiStrDisplayFix (STR_ATAMUI_TIME_LEFT_SEC,FALSE);

    AtAmUiDelay ((PbaFailedAttempts - PbaFailedThreshold) * 10 * AT_AM_UI_1_SECOND);

    AtAmUiStrClearScreen ();

    return Status;
  }
}

