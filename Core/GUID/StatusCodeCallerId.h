//**********************************************************************
//**********************************************************************
//**                                                                  **
//**        (C)Copyright 1985-2006, American Megatrends, Inc.         **
//**                                                                  **
//**                       All Rights Reserved.                       **
//**                                                                  **
//**             6145-F Northbelt Pkwy, Norcross, GA 30071            **
//**                                                                  **
//**                       Phone: (770)-246-8600                      **
//**                                                                  **
//**********************************************************************
//**********************************************************************

//**********************************************************************
// $Header: /Alaska/SOURCE/Core/EDK/GUID/StatusCodeCallerId.h 1     5/19/06 11:29p Felixp $
//
// $Revision: 1 $
//
// $Date: 5/19/06 11:29p $
//**********************************************************************
// Revision History
// ----------------
// $Log: /Alaska/SOURCE/Core/EDK/GUID/StatusCodeCallerId.h $
// 
// 1     5/19/06 11:29p Felixp
// 
//**********************************************************************
//<AMI_FHDR_START>
//
// Name:	StatusCodeCallerId.h
//
// Description:	Statuc Code Caller ID GUID
//
//<AMI_FHDR_END>
//**********************************************************************
#ifndef __EFI_STANDARD_CALLER_ID_GUID__H__
#define __EFI_STANDARD_CALLER_ID_GUID__H__
#ifdef __cplusplus
extern "C" {
#endif

#include <StatusCodes.h>

#define EFI_STANDARD_CALLER_ID_GUID \
  {0xC9DCF469, 0xA7C4, 0x11D5, 0x87, 0xDA, 0x00, 0x06, 0x29, 0x45, 0xC3, 0xB9}

GUID_VARIABLE_DECLARATION(gEfiCallerIdGuid, EFI_STANDARD_CALLER_ID_GUID);

/****** DO NOT WRITE BELOW THIS LINE *******/
#ifdef __cplusplus
}
#endif
#endif
//**********************************************************************
//**********************************************************************
//**                                                                  **
//**        (C)Copyright 1985-2006, American Megatrends, Inc.         **
//**                                                                  **
//**                       All Rights Reserved.                       **
//**                                                                  **
//**             6145-F Northbelt Pkwy, Norcross, GA 30071            **
//**                                                                  **
//**                       Phone: (770)-246-8600                      **
//**                                                                  **
//**********************************************************************
//**********************************************************************