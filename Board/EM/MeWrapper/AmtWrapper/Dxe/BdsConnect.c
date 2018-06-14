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
// $Header: /Alaska/SOURCE/Modules/SharkBayRefCodes/ME/AmtWrapper/AmtWrapperDxe/BdsConnect.c 1     2/08/12 1:08a Klzhan $
//
// $Revision: 1 $
//
// $Date: 2/08/12 1:08a $
//
//**********************************************************************
// Revision History
// ----------------
// $Log: /Alaska/SOURCE/Modules/SharkBayRefCodes/ME/AmtWrapper/AmtWrapperDxe/BdsConnect.c $
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
// Name:            BdsConnect.c
//
// Description:     Connect the device for AMT Boot.
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

  BdsConnect.c

Abstract:

  BDS Lib functions which relate with connect the device

--*/
#include "BdsLib.h"
#include "EdkIIGlueUefiLib.h"

EFI_STATUS
BdsLibConnectAllEfi (
  VOID
  )
/*++

Routine Description:

  This function will connect all current system handles recursively. The
  connection will finish until every handle's child handle created if it have.
  
Arguments:

  None

Returns:

  EFI_SUCCESS          - All handles and it's child handle have been connected
  
  EFI_STATUS           - Return the status of gBS->LocateHandleBuffer(). 

--*/
{
  EFI_STATUS  Status;
  UINTN       HandleCount;
  EFI_HANDLE  *HandleBuffer;
  UINTN       Index;

  Status = gBS->LocateHandleBuffer (
                  AllHandles,
                  NULL,
                  NULL,
                  &HandleCount,
                  &HandleBuffer
                  );
  if (EFI_ERROR (Status)) {
    return Status;
  }

  for (Index = 0; Index < HandleCount; Index++) {
    Status = gBS->ConnectController (HandleBuffer[Index], NULL, NULL, TRUE);
  }

  gBS->FreePool (HandleBuffer);

  return EFI_SUCCESS;
}

VOID
BdsLibConnectAllDriversToAllControllers (
  VOID
  )
/*++

Routine Description:

  Connects all drivers to all controllers. 
  This function make sure all the current system driver will manage
  the correspoinding controllers if have. And at the same time, make
  sure all the system controllers have driver to manage it if have. 
  
Arguments:
  
  None
  
Returns:
  
  None
  
--*/
{
  EFI_STATUS  Status;

  Status = EfiGetSystemConfigurationTable (&gEfiDxeServicesTableGuid, (VOID**) &gDS);

  do {
    //
    // Connect All EFI 1.10 drivers following EFI 1.10 algorithm
    //
    BdsLibConnectAllEfi ();

    //
    // Check to see if it's possible to dispatch an more DXE drivers.
    // The BdsLibConnectAllEfi () may have made new DXE drivers show up.
    // If anything is Dispatched Status == EFI_SUCCESS and we will try
    // the connect again.
    //
    Status = gDS->Dispatch ();

  } while (!EFI_ERROR (Status));

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