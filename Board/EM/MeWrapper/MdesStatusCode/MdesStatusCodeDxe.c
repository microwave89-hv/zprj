//*************************************************************************
//*************************************************************************
//**                                                                     **
//**        (C)Copyright 1985-2011, American Megatrends, Inc.            **
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
// $Header: /Alaska/SOURCE/Modules/SharkBayRefCodes/ME/MeWrapper/MdesStatusCode/MdesStatusCodeDxe.c 1     7/27/12 5:12a Klzhan $
//
// $Revision: 1 $
//
// $Date: 7/27/12 5:12a $
//**********************************************************************
// Revision History
// ----------------
// $Log: /Alaska/SOURCE/Modules/SharkBayRefCodes/ME/MeWrapper/MdesStatusCode/MdesStatusCodeDxe.c $
// 
// 1     7/27/12 5:12a Klzhan
// [TAG]  		EIPNone
// [Category]  	New Feature
// [Description]  	Add support MDES
// [Files]  		MdesStatusCode.cif
// MdesStatusCode.sdl
// MdesStatusCode.mak
// MdesStatusCodeDxe.c
// 
// 1     10/19/11 9:06a Calvinchen
// [TAG]  		EIPNone
// [Category]  	New Feature
// [Description]  	Added MDES BIOS Status Code Support.
// [Files]  		MdesStatusCode.cif
// MdesStatusCode.sdl
// MdesStatusCode.mak
// MdesStatusCodeDxe.c
// 
//
//**********************************************************************
//
//<AMI_FHDR_START>
//---------------------------------------------------------------------------
// Name:		MdesStatusCodeDxe.c
//
// Description:	Processes ASF messages for DXE.
//
//---------------------------------------------------------------------------
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

  AmtStatusCodeDxe.c

Abstract:
  Processes ASF messages

--*/

//#include "Tiano.h"
#include <AmiDxeLib.h>
#ifdef DXE_STATUS_CODE
#include <AmiDxeLib.h>
#include <token.h>
#include <Setup.h>
#include "MePlatformPolicy.h"
#include "MdesStatusCodeDxe.h"
EFI_GUID gSetupGuid = SETUP_GUID;
EFI_GUID gMdesStatusCodeProtocolGuid = MDES_STATUS_CODE_PROTOCOL_GUID;
EFI_GUID gDxePlatformMePolicyGuid = DXE_PLATFORM_ME_POLICY_GUID;
extern EFI_BOOT_SERVICES        *pBS;
#endif

VOID MdesBiosStatusCode(
    IN  VOID                        **Dummy,
    IN  EFI_STATUS_CODE_TYPE        Type,
    IN  EFI_STATUS_CODE_VALUE       Value,
    IN  UINT32                      Instance,
    IN  EFI_GUID                    *CallerId OPTIONAL,
    IN  EFI_STATUS_CODE_DATA        *Data OPTIONAL
)
/*++
Routine Description: 

  Provides an interface that a software module can call to report an ASF DXE status code.

Arguments:

  PeiServices - PeiServices pointer.

  Type     - Indicates the type of status code being reported.
  
  Value    - Describes the current status of a hardware or software entity.
             This included information about the class and subclass that is 
             used to classify the entity as well as an operation.
  
  Instance - The enumeration of a hardware or software entity within 
             the system. Valid instance numbers start with 1.
  
  CallerId - This optional parameter may be used to identify the caller.
             This parameter allows the status code driver to apply different 
             rules to different callers.
  
  Data     - This optional parameter may be used to pass additional data.

Returns: 
  
  None

--*/
{
#ifdef DXE_STATUS_CODE
    //
    // Do nothing, because AMT ASF driver will handle that.
    //
  EFI_STATUS                Status;
  MDES_STATUS_CODE_PROTOCOL *MdesStatusCodeProtocol;
  static UINTN              MdesEnable        = 0;
  static UINTN              MdesEnableChecked = 0;
  DXE_ME_POLICY_PROTOCOL   *MePlatformPolicy;

  if (MdesEnableChecked == 0) {
    Status = pBS->LocateProtocol (&gDxePlatformMePolicyGuid, NULL, &MePlatformPolicy);
    if (EFI_ERROR(Status)) {
      //
      // Check if GetVariable function has been initialized
      //
      return;
    } else {
      MdesEnableChecked = 1;
      //
      // set gfMDESCheck to 1 to lock geting variable next time
      //
      if (!(EFI_ERROR (Status))) {
        if (MePlatformPolicy->MeConfig.MdesForBiosState == 1) {
          //
          // check if function is set in BIOS Menu
          //
          MdesEnable = 1;
        }
      }
    }
  }
  if (MdesEnable == 1) {
    Status = pBS->LocateProtocol (&gMdesStatusCodeProtocolGuid, NULL, &MdesStatusCodeProtocol);
    if (EFI_ERROR (Status)) {
      return;
    }

    MdesStatusCodeProtocol->SendMdesStatusCode (Type, Value, Instance, CallerId, Data);
  }
#endif
    return ;
}

EFI_STATUS
MdesBiosStatusCodeInit(
    IN EFI_HANDLE *ImageHandle, 
    IN EFI_SYSTEM_TABLE *SystemTable
)
/*++
Routine Description: 

  Init routine for DXE ASF StatusCode.

Arguments:

  FfsHeader   - FfsHeader pointer.
  PeiServices - PeiServices pointer.

Returns: 
  
  EFI_SUCCESS      - The function completed successfully

--*/
{
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
