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
// $Header: /Alaska/SOURCE/Modules/SharkBayRefCodes/ME/MeWrapper/MeSetup/MeSetup.h 1     2/08/12 1:04a Klzhan $
//
// $Revision: 1 $
//
// $Date: 2/08/12 1:04a $
//
//**********************************************************************
// Revision History
// ----------------
// $Log: /Alaska/SOURCE/Modules/SharkBayRefCodes/ME/MeWrapper/MeSetup/MeSetup.h $
// 
// 1     2/08/12 1:04a Klzhan
// Initial Check in 
// 
// 1     2/25/11 1:41a Klzhan
// Initial Check-in
// 
// 1     12/03/10 5:09a Klzhan
// Initial Check-in.
// 
//
//**********************************************************************

//<AMI_FHDR_START>
//----------------------------------------------------------------------------
//
// Name:            MeSetup.h
//
// Description:     Header file for MeSetup module.
//
//----------------------------------------------------------------------------
//<AMI_FHDR_END>
/*++

This file contains a 'Sample Driver' and is licensed as such
under the terms of your license agreement with Intel or your
vendor.  This file may be modified by the user, subject to  
the additional terms of the license agreement               

--*/

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

 MeSetup.h

Abstract:

  
--*/
#ifndef __ME_SETUP_H__
#define __ME_SETUP_H__

#ifdef __cplusplus
extern "C" {
#endif

#define ME_MODE_MASK        0x0F

#define NORMAL_MODE         0x00
#define   QUALIFIER_MODE      0xE0
#define   LOCAL_FW_UPD_MODE   0xF0

#define TEMP_DISABLE_MODE   0x03
#define ME_IMAGE_1_5MB_FW   0x03
#define ME_IMAGE_5MB_FW     0x04

#define STR_ME_FW_SKU_1_5MB                     "1.5MB"
#define STR_ME_FW_SKU_5MB                       "5MB"
#define STR_ME_FW_SKU_UNIDENTIFIED              "Unidentified"

/****** DO NOT WRITE BELOW THIS LINE *******/
#ifdef __cplusplus
}
#endif
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