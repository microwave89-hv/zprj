/** @file
  This file contines function used for handling strings.

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

#if !defined(EDK_RELEASE_VERSION) || (EDK_RELEASE_VERSION < 0x00020000)
#include "EdkIIGlueDxe.h"
#include "AtAmUiString.h"
#endif

AT_AM_UI_STRING AtAmUiUSStringIDTab[] = {
  {STR_ATAMUI_LOCKED_TEXT,      4, 20,  L"This device has been locked and may have been lost.\r\n    If found, Please use the following information to return the device\r\n    "},
  {STR_ATAMUI_PLATFORM_ID,      4, 23,  L"Platform ID: "},
  {STR_ATAMUI_PROVIDER_ID,      4, 24,  L"Intel(R) Anti-Theft Technology service provider Id: "},
  {STR_ATAMUI_LOCK_DUE_TO,      4,  2,  L"This computer has been disabled using Intel(R) Anti-Theft Technology due to: "},
  {STR_ATAMUI_SELECT_PASS,      4,  5,  L"Please select one of the following for platform recovery:\r\n    1 - Passphrase\r\n    2 - Server Recovery Token"},
  {STR_ATAMUI_TIME_LEFT,        4,  4,  L"Time Left to enter Passphrase: "},
  {STR_ATAMUI_USER_PASS,        4,  5,  L"System Recovery"},
  {STR_ATAMUI_RECO_ENTER_PASS,  4,  6,  L"Enter Passphrase: "},
  {STR_ATAMUI_SERV_BASED_RECOV, 4,  6,  L"Server Based Recovery"},
  {STR_ATAMUI_INVALID_SELECT,   4, 10,  L"Invalid Selection, Press 1 or 2  "},
  {STR_ATAMUI_LOCK_TIME,        4,  0,  L"Disable Timer expired"},
  {STR_ATAMUI_LOCK_STOLEN,      4,  0,  L"Stolen Message received"},
  {STR_ATAMUI_LOCK_THRESHOLD,   4,  0,  L"Logon Threshold exceeded"},
  {STR_ATAMUI_LOCK_ATTACK,      4,  0,  L"Platform Attack detected"},
  {STR_ATAMUI_CHECKING_PASS,    4,  8,  L"Checking Recovery Password..."},
  {STR_ATAMUI_RECO_TRY_AGAIN,   4, 10,  L"Recovery Failed. Please try again ..."},
  {STR_ATAMUI_RECO_FAILED,      4, 11,  L"Intel(R) Anti-Theft Technology Recovery Failed.\r\n    System will shutdown..."},
  {STR_ATAMUI_RECO_SUCCESS,     4, 11,  L"Intel(R) Anti-Theft Technology Recovery Successful.\r\n    System Boot Continue ....."},
  {STR_ATAMUI_SUS_ENTER_INFO,   4,  1,  L"User Has Requested To Enter Intel(R) Anti-Theft Technology Suspend Mode....."},
  {STR_ATAMUI_RES_REFER,        4,  5,  L"Refer the following Platform Resume ID to IT: "},
  {STR_ATAMUI_RECO_REFER,       4,  5,  L"Refer the following Platform Recovery ID to IT: "},
  {STR_ATAMUI_SUS_REFER,        4,  5,  L"Refer the following Platform Suspend ID to IT: "},
  {STR_ATAMUI_SUS_ENTER_TOKEN,  4,  4,  L"Enter Suspend Token: "},
  {STR_ATAMUI_SUS_ATTEMPT_EXC,  4,  9,  L"Exceeded Max Attempts - Exiting ....      "},
  {STR_ATAMUI_SUS_ENTER_SUCCESS,4,  5,  L"Successfully Put Platform in Suspended Mode"},
  {STR_ATAMUI_SUS_ENTER_FAILED, 4,  5,  L"Failed to Put Platform into Suspended Mode"},
  {STR_ATAMUI_SUS_AUTH_FAILED,  4,  5,  L"Failed to Authenticate                    "},
  {STR_ATAMUI_SUS_EXIT_QUESTION,4,  1,  L"Intel(R) Anti-Theft Technology in Suspended State: Exit? (y/n)?"},
  {STR_ATAMUI_SUS_EXIT_INFO,    4,  2,  L"Exit Intel(R) Anti-Theft Technology Suspend Mode....."},
  {STR_ATAMUI_SUS_EXIT_SUCCESS, 4,  7,  L"Successfully Exited Suspend Mode"},
  {STR_ATAMUI_SUS_STAY,         4,  7,  L"Stay in Suspend Mode...."},
  {STR_ATAMUI_SUS_NONCE_FAILED, 0,  0,  L"NONCE unknown"},
  {STR_ATAMUI_TIME_LEFT_SEC,    0,  0,  L" seconds     "},
  {STR_ATAMUI_SELECT_OPTION,    4,  9,  L"Select one of the above options to proceed ..."},
  {STR_ATAMUI_CHECKING_AUTHENT, 4,  6,  L"Checking Authentication .."},
  {STR_ATAMUI_RECO_SEC_TOKEN,   4,  6,  L"Server Recovery Token: "}
};

UINTN AtAmUiUSStringIDTabEntries = sizeof (AtAmUiUSStringIDTab) / sizeof (AT_AM_UI_STRING);

/**
  This function gets character inputted.

  @param[out] Key                 Pointer to buffer for keystroke.

  @retval EFI_SUCCESS             The function completed successfully.
**/
EFI_STATUS
AtAmUiStrGetChar (
  OUT EFI_INPUT_KEY               *Key
  )
{
  EFI_STATUS                      Status;
  UINTN                           Delay = 300000;
  Status = EFI_SUCCESS;

  Key->UnicodeChar = L'\0';
  Key->ScanCode = 0;
  while (Delay) {
    Status = gST->ConIn->ReadKeyStroke (gST->ConIn, Key);
    if (!(EFI_ERROR (Status))) {
      break;
    }
    Delay --;
  }

  return Status;
}

/**
  This routine displays the string out to the screen based on defined strings.
  It uses X and Y to calculate the start location of string where it will be displayed. Function
  uses string ID to indicate which strings are going to be shown by AtAmUiDisplay(). There will
  be UseXY flag to indicate if there will be used coordinates from Strings library or not. If
  not, the cursor will be moved behind last printed sign. It will be used to print e.g. '*' sign
  during password entering. In graphic mode it is overridden by requirement. In graphic mode, X
  and Y can be calculated the start location of string.

  @param[in] StringID             Unique string ID crated as enum type of AT_AM_UI_STRING_ID
  @param[in] UseXY                Set the current cursor position for the displayed string if it is TRUE
                                  FALSE - don't use coordinates from String library. Cursor is moved behind
                                  last printed sign.
                                  TRUE - Use coordinates from String library.

  @retval EFI_SUCCESS             The function completed successfully.
**/
EFI_STATUS
AtAmUiStrDisplayFix (
  IN UINT32                       StringID,
  IN BOOLEAN                      UseXY
  )
{
  EFI_STATUS                      Status;
  UINTN                           i;

  for (i = 0; i < AtAmUiUSStringIDTabEntries; i++) {
    if (AtAmUiUSStringIDTab[i].StrID == StringID) {
      if (UseXY) {
        Status = AtAmUiStrSetCursor (AtAmUiUSStringIDTab[i].X, AtAmUiUSStringIDTab[i].Y);
      }

      Status = AtAmUiStrDisplay (AtAmUiUSStringIDTab[i].String);
      return Status;
    }
  }

  return EFI_NOT_FOUND;
}

/**
  This routine displays the string out to the screen.
  For multi-language support, a language table is expected to be selected by customization here. For example,
  the default language table is US-English in AtAmUiUSStringTab[], a second language table is created by
  customization in AtAmUiSECStringTab[].

  @param[in] String               The NULL-terminated Unicode string to be displayed on the output device(s)

  @retval EFI_SUCCESS             The function completed successfully.
**/
EFI_STATUS
AtAmUiStrDisplay (
  IN CHAR16                       *String
  )
{

  return gST->ConOut->OutputString (gST->ConOut, String);
}

/**
  This routine clears the screen.
  In graphic mode it is overridden by requirement.

  @retval EFI_SUCCESS             The function completed successfully.
**/
EFI_STATUS
AtAmUiStrClearScreen (
  VOID
  )
{

  return gST->ConOut->ClearScreen (gST->ConOut);
}

/**
  In text mode it is used to set the place of cursor row and cursor column.
  In graphic mode it is overridden by requirement.

  @param[in] CCol                 The column position to set the cursor to
  @param[in] CRow                 The row position to set the cursor to

  @retval EFI_SUCCESS             The function completed successfully.
**/
EFI_STATUS
AtAmUiStrSetCursor (
  IN UINT32                       CCol,
  IN UINT32                       CRow
  )
{

  return gST->ConOut->SetCursorPosition (gST->ConOut, CCol, CRow);
}

/**
  This function enables or disables cursor.
  In graphic mode it is overridden by requirement.

  @param[in] Enabled              If TRUE, the cursor is set to be visible. If FALSE, the cursor is set to be invisible.

  @retval EFI_SUCCESS             The function completed successfully.
**/
EFI_STATUS
AtAmUiStrEnableCursor (
  IN BOOLEAN                      Enabled
  )
{

  return gST->ConOut->EnableCursor (gST->ConOut, Enabled);
}

/**
  In text mode it returns the place of cursor row and cursor column.
  In graphic mode it is overridden by requirement.

  @param[out] CRow                The pointer to return current cursor row
  @param[out] CCol                The pointer to return current cursor column

  @retval EFI_SUCCESS             The function completed successfully.
**/
EFI_STATUS
AtAmUiStrGetCursor (
  OUT UINT32                      *CRow,
  OUT UINT32                      *CCol
  )
{
  *CRow = gST->ConOut->Mode->CursorRow;
  *CCol = gST->ConOut->Mode->CursorColumn;

  return EFI_SUCCESS;
}

/**
  Function handling delay code.
  In graphic mode it is overridden by requirement.

  @param[in] delay                The number of microseconds to stall execution.

  @retval EFI_SUCCESS             The function completed successfully.
**/
EFI_STATUS
AtAmUiDelay (
  IN UINT32                       delay
  )
{

  return gBS->Stall (delay);;
}

