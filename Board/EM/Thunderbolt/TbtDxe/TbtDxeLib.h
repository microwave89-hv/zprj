//*************************************************************************
//*************************************************************************
//**                                                                     **
//**        (C)Copyright 1985-2012, American Megatrends, Inc.            **
//**                                                                     **
//**                       All Rights Reserved.                          **
//**                                                                     **
//**      5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093           **
//**                                                                     **
//**                       Phone: (770)-246-8600                         **
//**                                                                     **
//*************************************************************************
//*************************************************************************
//*************************************************************************
// $Header: /Alaska/SOURCE/Modules/Thunderbolt/TbtDxe/TbtDxeLib.h 2     6/21/13 7:41a Barretlin $
//
// $Revision: 2 $
//
// $Date: 6/21/13 7:41a $
//*************************************************************************
// Revision History
// ----------------
//
//*************************************************************************
#include <Efi.h>
#include <token.h>
#include <AmiLib.h>
#include <AmiDxeLib.h>
#include <AmiCspLib.h>

#ifndef __TBTDXELIB_H__
#define __TBTDXELIB_H__



#ifdef __cplusplus
extern "C" {
#endif

#if defined TBT_INTEL_RC_CONFIG && TBT_INTEL_RC_CONFIG == 1
EFI_STATUS TbtProtectedPciDevice
(
  IN PCI_DEV_INFO *PciDevice
);
#endif

VOID TbtDxeInvokeSmiHandler();

#if defined ULT_SUPPORT && ULT_SUPPORT == 1
BOOLEAN
IsULTPchSeries
( 
  VOID 
);
#endif

#ifdef __cplusplus
}
#endif

#endif
//*************************************************************************
//*************************************************************************
//**                                                                     **
//**        (C)Copyright 1985-2012, American Megatrends, Inc.            **
//**                                                                     **
//**                       All Rights Reserved.                          **
//**                                                                     **
//**      5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093           **
//**                                                                     **
//**                       Phone: (770)-246-8600                         **
//**                                                                     **
//*************************************************************************
//*************************************************************************
