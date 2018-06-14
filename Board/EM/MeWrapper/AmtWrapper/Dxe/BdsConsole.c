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
// $Header: /Alaska/SOURCE/Modules/SharkBayRefCodes/ME/AmtWrapper/AmtWrapperDxe/BdsConsole.c 2     5/14/14 9:53p Tristinchou $
//
// $Revision: 2 $
//
// $Date: 5/14/14 9:53p $
//
//**********************************************************************
// Revision History
// ----------------
// $Log: /Alaska/SOURCE/Modules/SharkBayRefCodes/ME/AmtWrapper/AmtWrapperDxe/BdsConsole.c $
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
// Name:            BdsConsole.c
//
// Description:     Connect the Console device for AMT.
//
//----------------------------------------------------------------------------
//<AMI_FHDR_END>
/*++

Copyright (c) 2004, Intel Corporation                                                         
All rights reserved. This program and the accompanying materials                          
are licensed and made available under the terms and conditions of the BSD License         
which accompanies this distribution.  The full text of the license may be found at        
http://opensource.org/licenses/bsd-license.php                                            
                                                                                          
THE PROGRAM IS DISTRIBUTED UNDER THE BSD LICENSE ON AN "AS IS" BASIS,                     
WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.             

Module Name:

  BdsConsole.c

Abstract:

  BDS Lib functions which contain all the code to connect console device

--*/

#include "BdsLib.h"
#include "EfiPrintLib.h"

EFI_STATUS
BdsLibUpdateConsoleVariable (
  IN  CHAR16                    *ConVarName,
  IN  EFI_DEVICE_PATH_PROTOCOL  *CustomizedConDevicePath,
  IN  EFI_DEVICE_PATH_PROTOCOL  *ExclusiveDevicePath
  )
/*++

Routine Description:

  This function update console variable based on ConVarName, it can 
  add or remove one specific console device path from the variable

Arguments:

  ConVarName   - Console related variable name, ConIn, ConOut, ErrOut.

  CustomizedConDevicePath - The console device path which will be added to
                            the console variable ConVarName, this parameter
                            can not be multi-instance.

  ExclusiveDevicePath     - The console device path which will be removed
                            from the console variable ConVarName, this
                            parameter can not be multi-instance.

Returns:

  EFI_UNSUPPORTED         - Add or remove the same device path.
  
  EFI_SUCCESS             - Success add or remove the device path from 
                            the console variable.

--*/
{
  EFI_STATUS                Status;
  EFI_DEVICE_PATH_PROTOCOL  *VarConsole;
  UINTN                     DevicePathSize;
  EFI_DEVICE_PATH_PROTOCOL  *Instance;
  EFI_DEVICE_PATH_PROTOCOL  *NewDevicePath;
  UINT32                    VarAttr;
  UINTN                     VarSize;
  

  VarConsole      = NULL;
  DevicePathSize  = 0;
  NewDevicePath   = NULL;
  Status          = EFI_UNSUPPORTED;

  //
  // Notes: check the device path point, here should check
  // with compare memory
  //
  if (CustomizedConDevicePath == ExclusiveDevicePath) {
    return EFI_UNSUPPORTED;
  }
  //
  // Delete the ExclusiveDevicePath from current default console
  //
  VarConsole = BdsLibGetVariableAndSize (
                ConVarName,
                &gEfiGlobalVariableGuid,
                &DevicePathSize
                );

  if (ExclusiveDevicePath != NULL && VarConsole != NULL) {
    if (BdsLibMatchDevicePaths (VarConsole, ExclusiveDevicePath)) {

      Instance = EfiDevicePathInstance (&VarConsole, &DevicePathSize);

      while (VarConsole != NULL) {
        if (EfiCompareMem (
              Instance,
              ExclusiveDevicePath,
              DevicePathSize - sizeof (EFI_DEVICE_PATH_PROTOCOL)
              ) == 0) {
          //
          // Remove the match part
          //
          NewDevicePath = EfiAppendDevicePathInstance (NewDevicePath, VarConsole);
          break;
        } else {
          //
          // Continue the next instance
          //
          NewDevicePath = EfiAppendDevicePathInstance (NewDevicePath, Instance);
        }

        Instance = EfiDevicePathInstance (&VarConsole, &DevicePathSize);
      }
      //
      // Reset the console variable with new device path
      //
      VarAttr = 0;
      VarSize = 0;

      Status = gRT->GetVariable(
                        ConVarName,
                        &gEfiGlobalVariableGuid,
                        &VarAttr,
                        &VarSize,
                        NULL );
      if( EFI_ERROR(Status) && Status != EFI_BUFFER_TOO_SMALL )
      {
        VarAttr = EFI_VARIABLE_BOOTSERVICE_ACCESS | EFI_VARIABLE_RUNTIME_ACCESS | EFI_VARIABLE_NON_VOLATILE;
        VarSize = EfiDevicePathSize( NewDevicePath );
      }

      gRT->SetVariable(
            ConVarName,
            &gEfiGlobalVariableGuid,
            VarAttr,
            VarSize,
            NewDevicePath );
    }
  }
  //
  // Try to append customized device path
  //
  VarConsole = BdsLibGetVariableAndSize (
                ConVarName,
                &gEfiGlobalVariableGuid,
                &DevicePathSize
                );

  if (CustomizedConDevicePath != NULL) {
    if (!BdsLibMatchDevicePaths (VarConsole, CustomizedConDevicePath)) {
      //
      // In the first check, the default console variable will be null,
      // just append current customized device path
      //
      VarConsole = EfiAppendDevicePathInstance (VarConsole, CustomizedConDevicePath);

      //
      // Update the variable of the default console
      //
      VarAttr = 0;
      VarSize = 0;

      Status = gRT->GetVariable(
                        ConVarName,
                        &gEfiGlobalVariableGuid,
                        &VarAttr,
                        &VarSize,
                        NULL );
      if( EFI_ERROR(Status) && Status != EFI_BUFFER_TOO_SMALL )
      {
        VarAttr = EFI_VARIABLE_BOOTSERVICE_ACCESS | EFI_VARIABLE_RUNTIME_ACCESS | EFI_VARIABLE_NON_VOLATILE;
        VarSize = EfiDevicePathSize( NewDevicePath );
      }

      gRT->SetVariable(
            ConVarName,
            &gEfiGlobalVariableGuid,
            VarAttr,
            VarSize,
            VarConsole );
    }
  }

  return EFI_SUCCESS;
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