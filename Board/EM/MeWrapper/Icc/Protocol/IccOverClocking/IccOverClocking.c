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
// $Header: /Alaska/SOURCE/Modules/SharkBayRefCodes/ME/MeWrapper/Icc/IccProtocolLib/IccOverClocking/IccOverClocking.c 1     2/08/12 1:05a Klzhan $
//
// $Revision: 1 $
//
// $Date: 2/08/12 1:05a $
//
//**********************************************************************
// Revision History
// ----------------
// $Log: /Alaska/SOURCE/Modules/SharkBayRefCodes/ME/MeWrapper/Icc/IccProtocolLib/IccOverClocking/IccOverClocking.c $
// 
// 1     2/08/12 1:05a Klzhan
// Initial Check in 
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
// Name:            IccOverClocking.c
//
// Description:     ICC OverClocking protocol
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

  IccOverClocking.c

Abstract:

  ICC OverClocking protocol

--*/

#if !defined(EDK_RELEASE_VERSION) || (EDK_RELEASE_VERSION < 0x00020000)

#include "EdkIIGlueDxe.h"
#endif

#include "IccOverClocking.h"

//
// Protocol GUID definition
//
EFI_GUID  gIccOverClockingProtocolGuid = ICC_OVERCLOCKING_PROTOCOL_GUID;

//
// Protocol description
//
EFI_GUID_STRING
  (&gIccOverClockingProtocolGuid, "ICC OverClocking Protocol", "Integrated Clock Control OverClocking Protocol");

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