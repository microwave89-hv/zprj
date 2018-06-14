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
// $Header: /Alaska/SOURCE/Modules/SharkBayRefCodes/ME/AmtWrapper/AmtWrapperDxe/AsfSupport.h 1     2/08/12 1:08a Klzhan $
//
// $Revision: 1 $
//
// $Date: 2/08/12 1:08a $
//
//**********************************************************************
// Revision History
// ----------------
// $Log: /Alaska/SOURCE/Modules/SharkBayRefCodes/ME/AmtWrapper/AmtWrapperDxe/AsfSupport.h $
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
// Name:            AsfSupport.h
//
// Description:     ASF BDS Support include file
//
//----------------------------------------------------------------------------
//<AMI_FHDR_END>
/*++
 This file contains an 'Intel Peripheral Driver' and is        
 licensed for Intel CPUs and chipsets under the terms of your  
 license agreement with Intel or your vendor.  This file may   
 be modified by the user, subject to additional terms of the   
 license agreement                                             
--*/

/*++

Copyright (c) 2005-2008 Intel Corporation. All rights reserved
This software and associated documentation (if any) is furnished
under a license and may only be used or copied in accordance
with the terms of the license. Except as permitted by such
license, no part of this software or documentation may be
reproduced, stored in a retrieval system, or transmitted in any
form or by any means without the express written consent of
Intel Corporation.


Module Name:

  AsfSupport.h

Abstract:

  ASF BDS Support include file

--*/

#ifndef _ASF_SUPPORT_H_
#define _ASF_SUPPORT_H_

#include "Tiano.h"
#include "EfiDriverLib.h"
#include "BdsLib.h"
#include "Pci22.h"
#include "Amt.h"
#include "AmtLib.h"
#include "MeAccess.h"

#include EFI_PROTOCOL_DEFINITION (LegacyBios)
#include EFI_PROTOCOL_DEFINITION (SimpleNetwork)
#include EFI_PROTOCOL_DEFINITION (FirmwareVolume)
#include EFI_PROTOCOL_DEFINITION (PciRootBridgeIo)
#include EFI_PROTOCOL_DEFINITION (FormBrowser)

#include EFI_PROTOCOL_CONSUMER (AlertStandardformat)
#include EFI_PROTOCOL_CONSUMER (DiskInfo)

#include EFI_PROTOCOL_DEFINITION (IderControllerDriver)

typedef union {
  UINT32  Data32;
  UINT16  Data16[2];
} DATA32_UNION;

EFI_STATUS
BdsAsfInitialization (
  IN  VOID
  )
/*++

Routine Description:

  Retrieve the ASF boot options previously recorded by the ASF driver.
  
Arguments:

  None.
  
Returns:

  Initialize Boot Options global variable and AMT protocol
  
--*/
;

EFI_STATUS
BdsBootViaAsf (
  IN  VOID
  )
/*++

Routine Description:

  Process ASF boot options and if available, attempt the boot 

Arguments:

  None.

Returns:

  EFI_SUCCESS - The command completed successfully
  Other       - Error!!

--*/
;

VOID
PrintBbsTable (
  IN BBS_TABLE                      *LocalBbsTable
  )
/*++

Routine Description:

  Dump all devices of BBS.

Arguments:

  LocalBbsTable - BBS table entry.

Returns:

  None.

--*/
;

EFI_STATUS
BdsLibDoLegacyBoot (
  IN  BDS_COMMON_OPTION           *Option
  )
/*++

Routine Description:
 
  Boot the legacy system with the boot option

Arguments:

  Option           - The legacy boot option which have BBS device path

Returns:

  EFI_UNSUPPORTED  - There is no legacybios protocol, do not support
                     legacy boot.
                         
  EFI_STATUS       - Return the status of LegacyBios->LegacyBoot ().

--*/
;

BOOLEAN
BdsCheckIderMedia (
  IN  VOID
  )
/*++

Routine Description:
  This will return if Media in IDE-R is present.
  
Arguments:
  None.
      
Returns:
  True    Media is present.
  False   Media is not present.
  
--*/
;

EFI_DEVICE_PATH_PROTOCOL  *
BdsCreateShellDevicePath (
  IN VOID
  )
/*++

Routine Description:
  
  This function will create a SHELL BootOption to boot.

Arguments:

  None.
  
Returns:
  
  Shell Device path for booting.
  
--*/
;

BDS_COMMON_OPTION         *
BdsCreateBootOption (
  IN  EFI_DEVICE_PATH_PROTOCOL       *DevicePath,
  IN  CHAR16                         *Description
  )
/*++

Routine Description:
  
  This function will create a BootOption from the give device path and 
  description string.

Arguments:

  DevicePath       - The device path which the option represent
  Description      - The description of the boot option
  
Returns:
  
  BDS_COMMON_OPTION - A BDS_COMMON_OPTION pointer
  
--*/
;

#endif
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