//**********************************************************************
//**********************************************************************
//**                                                                  **
//**        (C)Copyright 1985-2005, American Megatrends, Inc.         **
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
// $Header: /Alaska/BIN/Core/CORE_DXE/ArchProtocol/StatusCode.h 2     10/07/06 10:17a Felixp $
//
// $Revision: 2 $
//
// $Date: 10/07/06 10:17a $
//*****************************************************************************
// Revision History
// ----------------
// $Log: /Alaska/BIN/Core/CORE_DXE/ArchProtocol/StatusCode.h $
// 
// 2     10/07/06 10:17a Felixp
// UEFI 2.0 definitions added
// 
// 1     3/13/06 1:45a Felixp
// 
// 1     1/28/05 12:44p Felixp
// 
// 2     1/18/05 3:21p Felixp
// PrintDebugMessage renamed to Trace
// 
// 1     12/23/04 9:42a Felixp
// 
// 1     12/23/04 9:29a Felixp
// 
// 1     4/07/04 5:19p Robert
//
//*****************************************************************************
//<AMI_FHDR_START>
//
// Name:	StatusCode.h
//
// Description:	This file is an include file used to define the Architectural
//		Protocol for the Status Code Reporting.  For questions about the
//		specification refer to the DXE CIS, The Status Code Spec,
//		and the EFI SPEC
//
//<AMI_FHDR_END>
//*****************************************************************************
#ifndef __STATUS_CODE_ARCH_PROTOCOL_H__
#define __STATUS_CODE_ARCH_PROTOCOL_H__
#ifdef __cplusplus
extern "C" {
#endif
#include <EFI.h>

// GUID for the Status Code Architectural Protocol
#define EFI_STATUS_CODE_ARCH_PROTOCOL_GUID \
  { 0xd98e3ea3, 0x6f39, 0x4be4, 0x82, 0xce, 0x5a, 0x89, 0x0c, 0xcb, 0x2c, 0x95 }

GUID_VARIABLE_DECLARATION(gEfiStatusCodeArchProtocolGuid, EFI_STATUS_CODE_ARCH_PROTOCOL_GUID);

// UEFI 2.0 Status Code Runtime Protocol
#define EFI_STATUS_CODE_RUNTIME_PROTOCOL_GUID  \
  { 0xd2b2b828, 0x826, 0x48a7, 0xb3, 0xdf, 0x98, 0x3c, 0x0, 0x60, 0x24, 0xf0}

// Interface stucture for the STATUS CODE Runtime Protocol
typedef struct _EFI_STATUS_CODE_PROTOCOL {
    EFI_REPORT_STATUS_CODE ReportStatusCode;
} EFI_STATUS_CODE_PROTOCOL;

GUID_VARIABLE_DECLARATION(gEfiStatusCodeRuntimeProtocolGuid, EFI_STATUS_CODE_RUNTIME_PROTOCOL_GUID);
/****** DO NOT WRITE BELOW THIS LINE *******/
#ifdef __cplusplus
}
#endif
#endif
//**********************************************************************
//**********************************************************************
//**                                                                  **
//**        (C)Copyright 1985-2005, American Megatrends, Inc.         **
//**                                                                  **
//**                       All Rights Reserved.                       **
//**                                                                  **
//**             6145-F Northbelt Pkwy, Norcross, GA 30071            **
//**                                                                  **
//**                       Phone: (770)-246-8600                      **
//**                                                                  **
//**********************************************************************
//**********************************************************************
