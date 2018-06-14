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
// $Header: /Alaska/SOURCE/Modules/SharkBayRefCodes/Platform/PlatformInfo/PlatformInfo.h 2     10/31/12 4:28a Alanlin $
//
// $Revision: 2 $
//
// $Date: 10/31/12 4:28a $
//*************************************************************************
// Revision History
// ----------------
// $Log: /Alaska/SOURCE/Modules/SharkBayRefCodes/Platform/PlatformInfo/PlatformInfo.h $
// 
// 2     10/31/12 4:28a Alanlin
// [TAG]         None
// [Category]    Improvement
// [Description] Fine tune Platform Board Information.
// 
// 1     2/09/12 12:33a Yurenlai
// Initial check in.
// 
//*************************************************************************


#ifndef _PLATFORM_INFO_DRIVER_H_
#define _PLATFORM_INFO_DRIVER_H_

#include "EFI.h"

#define EFI_PLATFORM_INFO_PROTOCOL_GUID \
  { \
    0xd9035175, 0x8ce2, 0x47de, 0xa8, 0xb8, 0xcc, 0x98, 0xe5, 0xe2, 0xa8, 0x85 \
  }

EFI_FORWARD_DECLARATION (PLATFORM_INFO_PROTOCOL);

typedef struct _PLATFORM_INFO_PROTOCOL {
  UINT8                      RevisonId;           // Structure Revision ID
  UINT8                      PlatformFlavor;      // Platform Flavor
  UINT16                     BoardId;             // Board ID
  UINT8                      BoardRev;            // Board Revision
} PLATFORM_INFO_PROTOCOL;

extern EFI_GUID gPlatformInfoProtocolGuid;


#endif


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
