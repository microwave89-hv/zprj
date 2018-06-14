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
// $Header: /Alaska/SOURCE/Modules/SharkBayRefCodes/ME/AmtWrapper/AmtWrapperDxe/BdsMisc.c 2     5/14/14 9:53p Tristinchou $
//
// $Revision: 2 $
//
// $Date: 5/14/14 9:53p $
//
//**********************************************************************
// Revision History
// ----------------
// $Log: /Alaska/SOURCE/Modules/SharkBayRefCodes/ME/AmtWrapper/AmtWrapperDxe/BdsMisc.c $
// 
// 2     5/14/14 9:53p Tristinchou
// [TAG]  		EIP167030
// [Category]  	Improvement
// [Description]  	Remove the variable runtime attribute and keep original
// attributes.
// 
// 1     2/08/12 1:08a Klzhan
// Initial Check in 
// 
// 1     2/25/11 1:43a Klzhan
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
// Name:            BdsMisc.h
//
// Description:     Misc BDS library function
//
//----------------------------------------------------------------------------
//<AMI_FHDR_END>
/*++

Copyright (c) 2004 - 2005, Intel Corporation                                                         
All rights reserved. This program and the accompanying materials                          
are licensed and made available under the terms and conditions of the BSD License         
which accompanies this distribution.  The full text of the license may be found at        
http://opensource.org/licenses/bsd-license.php                                            
                                                                                          
THE PROGRAM IS DISTRIBUTED UNDER THE BSD LICENSE ON AN "AS IS" BASIS,                     
WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.             

Module Name:

  BdsMisc.c

Abstract:

  Misc BDS library function

--*/

#include "BdsLib.h"

extern UINT16 gPlatformBootTimeOutDefault;

UINT16
BdsLibGetTimeout (
  VOID
  )
/*++

Routine Description:
  
  Return the default value for system Timeout variable.

Arguments:

  None

Returns:
  
  Timeout value.

--*/
{
  UINT16        Timeout;
  UINT32        VarAttr;
  UINTN         Size;
  EFI_STATUS    Status;

  //
  // Return Timeout variable or 0xffff if no valid
  // Timeout variable exists.
  //
  VarAttr = 0;
  Size    = sizeof(UINT16);
  Status  = gRT->GetVariable(
                    L"Timeout",
                    &gEfiGlobalVariableGuid,
                    &VarAttr,
                    &Size,
                    &Timeout );
  if (!EFI_ERROR (Status)) {
    return Timeout;
  }
  
  if( EFI_ERROR (Status) && (Status != EFI_BUFFER_TOO_SMALL) )
  {
    VarAttr = EFI_VARIABLE_BOOTSERVICE_ACCESS | EFI_VARIABLE_RUNTIME_ACCESS | EFI_VARIABLE_NON_VOLATILE;
    Size    = sizeof(UINT16);
  }
  //
  // To make the current EFI Automatic-Test activity possible, just add
  // following code to make AutoBoot enabled when this variable is not
  // present.
  // This code should be removed later.
  //
  Timeout = gPlatformBootTimeOutDefault;

  //
  // Notes: Platform should set default variable if non exists on all error cases!!!
  //
  Status = gRT->SetVariable(
                  L"Timeout",
                  &gEfiGlobalVariableGuid,
                  VarAttr,
                  Size,
                  &Timeout );

  return Timeout;
}
UINT16
BdsLibGetFreeOptionNumber (
  IN  CHAR16    *VariableName
  )
/*++

Routine Description:
  Get the Option Number that does not used 
  Try to locate the specific option variable one by one untile find a free number
  
Arguments:
  VariableName - Indicate if the boot#### or driver#### option
  
Returns:
  The Minimal Free Option Number
  
--*/
{
  UINT16        Number;
  UINTN         Index;
  CHAR16        StrTemp[10];
  UINT16        *OptionBuffer;
  UINTN         OptionSize;

  //
  // Try to find the minimum free number from 0, 1, 2, 3....
  //
  Index = 0;
  do {
    if (*VariableName == 'B') {
      SPrint (StrTemp, sizeof (StrTemp), L"Boot%04x", Index);      
    } else {
      SPrint (StrTemp, sizeof (StrTemp), L"Driver%04x", Index);  
    }
    //
    // try if the option number is used
    //
    OptionBuffer = BdsLibGetVariableAndSize (
              StrTemp,
              &gEfiGlobalVariableGuid,
              &OptionSize
              );
    if (OptionBuffer == NULL) {
      break;
    }
    Index++;
  } while (1);
  
  Number = (UINT16) Index;
  return Number;
}

EFI_STATUS
BdsLibRegisterNewOption (
  IN  EFI_LIST_ENTRY                 *BdsOptionList,
  IN  EFI_DEVICE_PATH_PROTOCOL       *DevicePath,
  IN  CHAR16                         *String,
  IN  CHAR16                         *VariableName
  )
/*++

Routine Description:
  
  This function will register the new boot#### or driver#### option base on
  the VariableName. The new registered boot#### or driver#### will be linked
  to BdsOptionList and also update to the VariableName. After the boot#### or
  driver#### updated, the BootOrder or DriverOrder will also be updated.

Arguments:

  BdsOptionList    - The header of the boot#### or driver#### link list
  
  DevicePath       - The device path which the boot####
                     or driver#### option present
                     
  String           - The description of the boot#### or driver####
  
  VariableName     - Indicate if the boot#### or driver#### option

Returns:
  
  EFI_SUCCESS      - The boot#### or driver#### have been success registered
  
  EFI_STATUS       - Return the status of gRT->SetVariable ().

--*/
{
  EFI_STATUS                Status;
  UINTN                     Index;
  UINT16                    MaxOptionNumber;
  UINT16                    RegisterOptionNumber;
  UINT16                    *TempOptionPtr;
  UINTN                     TempOptionSize;
  UINT16                    *OptionOrderPtr;
  VOID                      *OptionPtr;
  UINTN                     OptionSize;
  UINT8                     *TempPtr;
  EFI_DEVICE_PATH_PROTOCOL  *OptionDevicePath;
  CHAR16                    *Description;
  CHAR16                    OptionName[10];
  BOOLEAN                   UpdateDescription;
  UINT16                    BootOrderEntry; 
  UINTN                     OrderItemNum;
  UINT32                    VarAttr;
  UINTN                     VarSize;
  

  OptionPtr             = NULL;
  OptionSize            = 0;
  TempPtr               = NULL;
  OptionDevicePath      = NULL;
  Description           = NULL;
  MaxOptionNumber       = 0;
  OptionOrderPtr        = NULL;
  UpdateDescription     = FALSE;
  EfiZeroMem (OptionName, sizeof (OptionName));

  TempOptionSize = 0;
  TempOptionPtr = BdsLibGetVariableAndSize (
                    VariableName,
                    &gEfiGlobalVariableGuid,
                    &TempOptionSize
                    );

  //
  // Compare with current option variable
  //
  for (Index = 0; Index < TempOptionSize / sizeof (UINT16); Index++) {

    if (*VariableName == 'B') {
      SPrint (OptionName, sizeof (OptionName), L"Boot%04x", TempOptionPtr[Index]);
    } else {
      SPrint (OptionName, sizeof (OptionName), L"Driver%04x", TempOptionPtr[Index]);
    }

    OptionPtr = BdsLibGetVariableAndSize (
                  OptionName,
                  &gEfiGlobalVariableGuid,
                  &OptionSize
                  );
    if (OptionPtr == NULL) {
      continue;
    }
    TempPtr = OptionPtr;
    TempPtr += sizeof (UINT32) + sizeof (UINT16);
    Description = (CHAR16 *) TempPtr;
    TempPtr += EfiStrSize ((CHAR16 *) TempPtr);
    OptionDevicePath = (EFI_DEVICE_PATH_PROTOCOL *) TempPtr;

    //
    // Notes: the description may will change base on the GetStringToken
    //
    if (EfiCompareMem (OptionDevicePath, DevicePath, EfiDevicePathSize (OptionDevicePath)) == 0) {
      if (EfiCompareMem (Description, String, EfiStrSize (Description)) == 0) { 
        //
        // Got the option, so just return
        //
        gBS->FreePool (OptionPtr);
        gBS->FreePool (TempOptionPtr);
        return EFI_SUCCESS;
      } else {
        //
        // Option description changed, need update.
        //
        UpdateDescription = TRUE;
        gBS->FreePool (OptionPtr);
        break;
      }
    } 

    gBS->FreePool (OptionPtr);
  }

  OptionSize          = sizeof (UINT32) + sizeof (UINT16) + EfiStrSize (String) + EfiDevicePathSize (DevicePath);
  OptionPtr           = EfiLibAllocateZeroPool (OptionSize);
  TempPtr             = OptionPtr;
  *(UINT32 *) TempPtr = LOAD_OPTION_ACTIVE;
  TempPtr += sizeof (UINT32);
  *(UINT16 *) TempPtr = (UINT16) EfiDevicePathSize (DevicePath);
  TempPtr += sizeof (UINT16);
  EfiCopyMem (TempPtr, String, EfiStrSize (String));
  TempPtr += EfiStrSize (String);
  EfiCopyMem (TempPtr, DevicePath, EfiDevicePathSize (DevicePath));

  if (UpdateDescription) {
    //
    // The number in option#### to be updated
    //
    RegisterOptionNumber = TempOptionPtr[Index];
  } else {
    //
    // The new option#### number
    //
    RegisterOptionNumber = BdsLibGetFreeOptionNumber(VariableName);
  }
  
  if (*VariableName == 'B') {
    SPrint (OptionName, sizeof (OptionName), L"Boot%04x", RegisterOptionNumber);
  } else {
    SPrint (OptionName, sizeof (OptionName), L"Driver%04x", RegisterOptionNumber);
  }
  
  VarAttr = 0;
  VarSize = 0;

  Status = gRT->GetVariable(
                    OptionName,
                    &gEfiGlobalVariableGuid,
                    &VarAttr,
                    &VarSize,
                    NULL );
  if( EFI_ERROR (Status) && (Status != EFI_BUFFER_TOO_SMALL) )
  {
    VarAttr = EFI_VARIABLE_BOOTSERVICE_ACCESS | EFI_VARIABLE_RUNTIME_ACCESS | EFI_VARIABLE_NON_VOLATILE;
    VarSize = OptionSize;
  }

  Status = gRT->SetVariable (
                  OptionName,
                  &gEfiGlobalVariableGuid,
                  VarAttr,
                  VarSize,
                  OptionPtr );
  //
  // Return if only need to update a changed description or fail to set option.
  //
  if (EFI_ERROR (Status) || UpdateDescription) {
    gBS->FreePool (OptionPtr);
    gBS->FreePool (TempOptionPtr);
    return Status;
  }

  gBS->FreePool (OptionPtr);

  //
  // Update the option order variable
  //
  
  //
  // If no option order
  //
  if (TempOptionSize == 0) {
    VarAttr = 0;
    VarSize = 0;

    Status = gRT->GetVariable(
                      VariableName,
                      &gEfiGlobalVariableGuid,
                      &VarAttr,
                      &VarSize,
                      NULL );
    if( EFI_ERROR (Status) && (Status != EFI_BUFFER_TOO_SMALL) )
    {
      VarAttr = EFI_VARIABLE_BOOTSERVICE_ACCESS | EFI_VARIABLE_RUNTIME_ACCESS | EFI_VARIABLE_NON_VOLATILE;
      VarSize = sizeof(UINT16);
    }
    
    BootOrderEntry = 0;
    
    Status = gRT->SetVariable(
                    VariableName,
                    &gEfiGlobalVariableGuid,
                    VarAttr,
                    VarSize,
                    &BootOrderEntry );
    if (EFI_ERROR (Status)) {
      gBS->FreePool (TempOptionPtr);
      return Status;
    }
    return EFI_SUCCESS;
  }  
  //
  // Append the new option number to the original option order
  //
  OrderItemNum = (TempOptionSize / sizeof (UINT16)) + 1 ;
  OptionOrderPtr = EfiLibAllocateZeroPool ( OrderItemNum * sizeof (UINT16));
  EfiCopyMem (OptionOrderPtr, TempOptionPtr, (OrderItemNum - 1) * sizeof (UINT16));

  OptionOrderPtr[Index] = RegisterOptionNumber;
  
  VarAttr = 0;
  VarSize = 0;

  Status = gRT->GetVariable(
                    VariableName,
                    &gEfiGlobalVariableGuid,
                    &VarAttr,
                    &VarSize,
                    NULL );
  if( EFI_ERROR (Status) && (Status != EFI_BUFFER_TOO_SMALL) )
  {
    VarAttr = EFI_VARIABLE_BOOTSERVICE_ACCESS | EFI_VARIABLE_RUNTIME_ACCESS | EFI_VARIABLE_NON_VOLATILE;
    VarSize = OrderItemNum * sizeof(UINT16);
  }
   
  Status = gRT->SetVariable(
                  VariableName,
                  &gEfiGlobalVariableGuid,
                  VarAttr,
                  VarSize,
                  OptionOrderPtr );
  if (EFI_ERROR (Status)) {
    gBS->FreePool (TempOptionPtr);
    gBS->FreePool (OptionOrderPtr);
    return Status;
  }

  gBS->FreePool (TempOptionPtr);
  gBS->FreePool (OptionOrderPtr);

  return EFI_SUCCESS;
}


VOID *
BdsLibGetVariableAndSize (
  IN  CHAR16              *Name,
  IN  EFI_GUID            *VendorGuid,
  OUT UINTN               *VariableSize
  )
/*++

Routine Description:

  Read the EFI variable (VendorGuid/Name) and return a dynamically allocated
  buffer, and the size of the buffer. If failure return NULL.

Arguments:

  Name       - String part of EFI variable name

  VendorGuid - GUID part of EFI variable name

  VariableSize - Returns the size of the EFI variable that was read

Returns:

  Dynamically allocated memory that contains a copy of the EFI variable.
  Caller is responsible freeing the buffer.

  NULL - Variable was not read

--*/
{
  EFI_STATUS  Status;
  UINTN       BufferSize;
  VOID        *Buffer;

  Buffer = NULL;

  //
  // Pass in a zero size buffer to find the required buffer size.
  //
  BufferSize  = 0;
  Status      = gRT->GetVariable (Name, VendorGuid, NULL, &BufferSize, Buffer);
  if (Status == EFI_BUFFER_TOO_SMALL) {
    //
    // Allocate the buffer to return
    //
    Buffer = EfiLibAllocateZeroPool (BufferSize);
    if (Buffer == NULL) {
      return NULL;
    }
    //
    // Read variable into the allocated buffer.
    //
    Status = gRT->GetVariable (Name, VendorGuid, NULL, &BufferSize, Buffer);
    if (EFI_ERROR (Status)) {
      BufferSize = 0;
    }
  }

  *VariableSize = BufferSize;
  return Buffer;
}

BOOLEAN
BdsLibMatchDevicePaths (
  IN  EFI_DEVICE_PATH_PROTOCOL  *Multi,
  IN  EFI_DEVICE_PATH_PROTOCOL  *Single
  )
/*++

Routine Description:

  Function compares a device path data structure to that of all the nodes of a
  second device path instance.

Arguments:

  Multi        - A pointer to a multi-instance device path data structure.

  Single       - A pointer to a single-instance device path data structure.

Returns:

  TRUE   - If the Single is contained within Multi
  
  FALSE  - The Single is not match within Multi
  

--*/
{
  EFI_DEVICE_PATH_PROTOCOL  *DevicePath;
  EFI_DEVICE_PATH_PROTOCOL  *DevicePathInst;
  UINTN                     Size;

  if (!Multi || !Single) {
    return FALSE;
  }

  DevicePath      = Multi;
  DevicePathInst  = EfiDevicePathInstance (&DevicePath, &Size);
  Size -= sizeof (EFI_DEVICE_PATH_PROTOCOL);

  //
  // Search for the match of 'Single' in 'Multi'
  //
  while (DevicePathInst != NULL) {
    //
    // If the single device path is found in multiple device paths,
    // return success
    //
    if (Size == 0) {
      return FALSE;
    }

    if (EfiCompareMem (Single, DevicePathInst, Size) == 0) {
      return TRUE;
    }

    gBS->FreePool (DevicePathInst);
    DevicePathInst = EfiDevicePathInstance (&DevicePath, &Size);
    Size -= sizeof (EFI_DEVICE_PATH_PROTOCOL);
  }

  return FALSE;
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