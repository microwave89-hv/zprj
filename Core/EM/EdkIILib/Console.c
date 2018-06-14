/** @file
  This module provide help function for displaying unicode string.

  Copyright (c) 2006 - 2009, Intel Corporation<BR>
  All rights reserved. This program and the accompanying materials                          
  are licensed and made available under the terms and conditions of the BSD License         
  which accompanies this distribution.  The full text of the license may be found at        
  http://opensource.org/licenses/bsd-license.php                                            

  THE PROGRAM IS DISTRIBUTED UNDER THE BSD LICENSE ON AN "AS IS" BASIS,                     
  WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.             

**/




#include <EdkIICommon.h>
#include <AmiDxeLib.h>
#include <Protocol/SimpleTextIn.h>


#define EFI_SIMPLE_TEXT_OUT_PROTOCOL EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL
#define EFI_SIMPLE_TEXT_OUTPUT_MODE SIMPLE_TEXT_OUTPUT_MODE



/**
  Draws a dialog box to the console output device specified by 
  ConOut defined in the EFI_SYSTEM_TABLE and waits for a keystroke
  from the console input device specified by ConIn defined in the 
  EFI_SYSTEM_TABLE.

  If there are no strings in the variable argument list, then ASSERT().
  If all the strings in the variable argument list are empty, then ASSERT().

  @param[in]   Attribute  Specifies the foreground and background color of the popup.
  @param[out]  Key        A pointer to the EFI_KEY value of the key that was 
                          pressed.  This is an optional parameter that may be NULL.
                          If it is NULL then no wait for a keypress will be performed.
  @param[in]  ...         The variable argument list that contains pointers to Null-
                          terminated Unicode strings to display in the dialog box.  
                          The variable argument list is terminated by a NULL.

**/
VOID
EFIAPI
CreatePopUp (
  IN  UINTN          Attribute,                
  OUT EFI_INPUT_KEY  *Key,      OPTIONAL
  ...
  )
{
  VA_LIST                          Args;
  EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL  *ConOut;
  EFI_SIMPLE_TEXT_OUTPUT_MODE      SavedConsoleMode;
  UINTN                            Columns;
  UINTN                            Rows;
  UINTN                            Column;
  UINTN                            Row;
  UINTN                            NumberOfLines;
  UINTN                            MaxLength;
  CHAR16                           *String;
  UINTN                            Length;
  CHAR16                           *Line;
  UINTN                            EventIndex;

  //
  // Determine the length of the longest line in the popup and the the total 
  // number of lines in the popup
  //
  VA_START (Args, Key);
  MaxLength = 0;
  NumberOfLines = 0;
  while ((String = VA_ARG (Args, CHAR16 *)) != NULL) {
    MaxLength = MAX (MaxLength, StrLen (String));
    NumberOfLines++;
  }
  VA_END (Args);

  //
  // If the total number of lines in the popup is zero, then ASSERT()
  //
  ASSERT (NumberOfLines != 0);

  //
  // If the maximum length of all the strings is zero, then ASSERT()
  //
  ASSERT (MaxLength != 0);

  //
  // Cache a pointer to the Simple Text Output Protocol in the EFI System Table
  //
  ConOut = gST->ConOut;
  
  //
  // Save the current console cursor position and attributes
  //
  CopyMem (&SavedConsoleMode, ConOut->Mode, sizeof (SavedConsoleMode));

  //
  // Retrieve the number of columns and rows in the current console mode
  //
  ConOut->QueryMode (ConOut, SavedConsoleMode.Mode, &Columns, &Rows);

  //
  // Disable cursor and set the foreground and background colors specified by Attribute
  //
  ConOut->EnableCursor (ConOut, FALSE);
  ConOut->SetAttribute (ConOut, Attribute);

  //
  // Limit NumberOfLines to height of the screen minus 3 rows for the box itself
  //
  NumberOfLines = MIN (NumberOfLines, Rows - 3);

  //
  // Limit MaxLength to width of the screen minus 2 columns for the box itself
  //
  MaxLength = MIN (MaxLength, Columns - 2);

  //
  // Compute the starting row and starting column for the popup
  //
  Row    = (Rows - (NumberOfLines + 3)) / 2;
  Column = (Columns - (MaxLength + 2)) / 2;

  //
  // Allocate a buffer for a single line of the popup with borders and a Null-terminator
  //
  Line = AllocateZeroPool ((MaxLength + 3) * sizeof (CHAR16));
  ASSERT (Line != NULL);

  //
  // Draw top of popup box   
  //
  SetMem16 (Line, (MaxLength + 2) * 2, BOXDRAW_HORIZONTAL);
  Line[0]             = BOXDRAW_DOWN_RIGHT;
  Line[MaxLength + 1] = BOXDRAW_DOWN_LEFT;
  Line[MaxLength + 2] = L'\0';
  ConOut->SetCursorPosition (ConOut, Column, Row++);
  ConOut->OutputString (ConOut, Line);

  //
  // Draw middle of the popup with strings
  //
  VA_START (Args, Key);
  while ((String = VA_ARG (Args, CHAR16 *)) != NULL && NumberOfLines > 0) {
    Length = StrLen (String);
    SetMem16 (Line, (MaxLength + 2) * 2, L' ');
    if (Length <= MaxLength) {
      //
      // Length <= MaxLength
      //
      CopyMem (Line + 1 + (MaxLength - Length) / 2, String , Length * sizeof (CHAR16));
    } else {
      //
      // Length > MaxLength
      //
      CopyMem (Line + 1, String + (Length - MaxLength) / 2 , MaxLength * sizeof (CHAR16));
    }
    Line[0]             = BOXDRAW_VERTICAL;
    Line[MaxLength + 1] = BOXDRAW_VERTICAL;
    Line[MaxLength + 2] = L'\0';
    ConOut->SetCursorPosition (ConOut, Column, Row++);
    ConOut->OutputString (ConOut, Line);
    NumberOfLines--;
  }
  VA_END (Args);

  //
  // Draw bottom of popup box
  //
  SetMem16 (Line, (MaxLength + 2) * 2, BOXDRAW_HORIZONTAL);
  Line[0]             = BOXDRAW_UP_RIGHT;
  Line[MaxLength + 1] = BOXDRAW_UP_LEFT;
  Line[MaxLength + 2] = L'\0';
  ConOut->SetCursorPosition (ConOut, Column, Row++);
  ConOut->OutputString (ConOut, Line);

  //
  // Free the allocated line buffer
  //
  FreePool (Line);

  //
  // Restore the cursor visibility, position, and attributes
  //
  ConOut->EnableCursor      (ConOut, SavedConsoleMode.CursorVisible);
  ConOut->SetCursorPosition (ConOut, SavedConsoleMode.CursorColumn, SavedConsoleMode.CursorRow);
  ConOut->SetAttribute      (ConOut, SavedConsoleMode.Attribute);

  //
  // Wait for a keystroke
  //
  if (Key != NULL) {
    gBS->WaitForEvent (1, &gST->ConIn->WaitForKey, &EventIndex);
    gST->ConIn->ReadKeyStroke (gST->ConIn, Key);
  }
}
