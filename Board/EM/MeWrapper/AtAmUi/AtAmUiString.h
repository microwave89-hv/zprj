/** @file
  Heder file.

@copyright
  Copyright (c) 2012 Intel Corporation. All rights reserved
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

#ifndef _ATAMUISTRING_H_
#define _ATAMUISTRING_H_

typedef enum _AT_AM_UI_STRING_ID {
  STR_ATAMUI_LOCKED_TEXT,
  STR_ATAMUI_PLATFORM_ID,
  STR_ATAMUI_PROVIDER_ID,
  STR_ATAMUI_LOCK_DUE_TO,
  STR_ATAMUI_SELECT_PASS,
  STR_ATAMUI_TIME_LEFT,
  STR_ATAMUI_USER_PASS,
  STR_ATAMUI_SERV_BASED_RECOV,
  STR_ATAMUI_INVALID_SELECT,
  STR_ATAMUI_LOCK_TIME,
  STR_ATAMUI_LOCK_STOLEN,
  STR_ATAMUI_LOCK_THRESHOLD,
  STR_ATAMUI_LOCK_ATTACK,
  STR_ATAMUI_CHECKING_PASS,
  STR_ATAMUI_RECO_TRY_AGAIN,
  STR_ATAMUI_RECO_FAILED,
  STR_ATAMUI_RECO_SUCCESS,
  STR_ATAMUI_SUS_ENTER_INFO,
  STR_ATAMUI_RES_REFER,
  STR_ATAMUI_RECO_REFER,
  STR_ATAMUI_SUS_REFER,
  STR_ATAMUI_SUS_ENTER_TOKEN,
  STR_ATAMUI_SUS_ATTEMPT_EXC,
  STR_ATAMUI_SUS_ENTER_SUCCESS,
  STR_ATAMUI_SUS_ENTER_FAILED,
  STR_ATAMUI_SUS_AUTH_FAILED,
  STR_ATAMUI_SUS_EXIT_QUESTION,
  STR_ATAMUI_SUS_EXIT_INFO,
  STR_ATAMUI_SUS_EXIT_SUCCESS,
  STR_ATAMUI_SUS_STAY,
  STR_ATAMUI_SUS_NONCE_FAILED,
  STR_ATAMUI_RECO_ENTER_PASS,
  STR_ATAMUI_TIME_LEFT_SEC,
  STR_ATAMUI_SELECT_OPTION,
  STR_ATAMUI_CHECKING_AUTHENT,
  STR_ATAMUI_FAILED_TO_AUTHENT,
  STR_ATAMUI_RECO_SEC_TOKEN,

  //
  // this has to be a last element of this enum
  //
  STR_ATAMUI_END_OF_TAB
} AT_AM_UI_STRING_ID;

///
/// Strings will be kept in array. There can be created many tables with strings in various
/// languages. A language table can be selected within AtAmUiStrDisplay () to display string in
/// targeted language with the unique string ID. The same unique string ID is applied to all
/// language tables
///
typedef struct _AT_AM_UI_STRING {
  UINTN   StrID;    ///< Unique string ID crated as enum type AT_AM_UI_STRING_ID
  UINT8   X;        ///< The place of cursor row to be display
  UINT8   Y;        ///< The place of cursor column to be display
  CHAR16  *String;  ///< Pointer to the string
} AT_AM_UI_STRING;

#define AT_AM_UI_1_SECOND 1000000

/**
  This function gets character inputted.

  @param[out] Key                 Pointer to buffer for keystroke.

  @retval EFI_SUCCESS             The function completed successfully.
**/
EFI_STATUS
AtAmUiStrGetChar (
  OUT EFI_INPUT_KEY               *Key
  )
;

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
;

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
;

/**
  This routine clears the screen.
  In graphic mode it is overridden by requirement.

  @retval EFI_SUCCESS             The function completed successfully.
**/
EFI_STATUS
AtAmUiStrClearScreen (
  VOID
  )
;

/**
  In text mode it is used to set the place of cursor row and cursor column.
  In graphic mode it is overridden by requirement.

  @param[in] CCol                 The column position to set the cursor to be displayed
  @param[in] CRow                 The row position to set the cursor to be displayed

  @retval EFI_SUCCESS             The function completed successfully.
**/
EFI_STATUS
AtAmUiStrSetCursor (
  IN UINT32                       CCol,
  IN UINT32                       CRow
  )
;

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
;

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
;

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
;

#endif
