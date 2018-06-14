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

//*************************************************************************
// $Header: /Alaska/BIN/Chipset/Intel/SouthBridge/LynxPoint/Intel Pch SB Chipset/PchWrap/WdtApp/WdtAppProtocolLib/WdtApp/WdtApp.h 1     2/08/12 8:36a Yurenlai $
//
// $Revision: 1 $
//
// $Date: 2/08/12 8:36a $
//*************************************************************************
// Revision History
// ----------------
// $Log: /Alaska/BIN/Chipset/Intel/SouthBridge/LynxPoint/Intel Pch SB Chipset/PchWrap/WdtApp/WdtAppProtocolLib/WdtApp/WdtApp.h $
// 
// 1     2/08/12 8:36a Yurenlai
// Intel Lynx Point/SB eChipset initially releases.
// 
//*************************************************************************

#ifndef _WDT_APP_API_H_
#define _WDT_APP_API_H_

#include <Efi.h>
#include <token.h>
#include <AmiLib.h>
#include <AmiDxeLib.h>
#include <Dxe.h>
#include <AmiCspLib.h>
//
// GUID for the WDT application Protocol
//
#if !defined(EDK_RELEASE_VERSION) || (EDK_RELEASE_VERSION < 0x00020000)
#define WDT_APP_PROTOCOL_GUID \
  {0x92c7d0bb, 0x679e, 0x479d, 0x87, 0x8d, 0xd4, 0xb8, 0x29, 0x68, 0x57, 0x8b}
  
#else

#define WDT_APP_PROTOCOL_GUID \
  {0x92c7d0bb, 0x679e, 0x479d, { 0x87, 0x8d, 0xd4, 0xb8, 0x29, 0x68, 0x57, 0x8b } }
 
#endif
//
// Extern the GUID for protocol users.
//
extern EFI_GUID    gWdtAppProtocolGuid;

typedef EFI_STATUS (EFIAPI *WDT_REQUEST) (VOID);

typedef struct _WDT_APP_PROTOCOL {
  WDT_REQUEST  RequestWdtAfterReboot;
  WDT_REQUEST  RequestWdtNow;
} WDT_APP_PROTOCOL;

#endif /* _WDT_APP_API_H_ */
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
