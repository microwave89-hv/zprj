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
// $Header: /Alaska/SOURCE/Modules/SMM/SmmStatusCode.h 4     4/18/11 5:11p Markw $
//
// $Revision: 4 $
//
// $Date: 4/18/11 5:11p $
//*****************************************************************************
// Revision History
// ----------------
// $Log: /Alaska/SOURCE/Modules/SMM/SmmStatusCode.h $
// 
// 4     4/18/11 5:11p Markw
// Revert back to Rev 1.
// 
// 3     3/04/11 3:36p Markw
// Update headers.
// 
// 2     7/08/09 8:02p Markw
// Update headers.
// 
// 1     3/18/07 1:54p Markw
// 
// 2     3/13/06 1:40a Felixp
// 
// 1     1/28/05 12:44p Felixp
// 
// 3     1/18/05 3:22p Felixp
// PrintDebugMessage renamed to Trace
// 
// 1     12/23/04 9:41a Felixp
// 
// 2     3/30/04 3:16p Markw
// Removed duplicate definition.
// 
// 1     2/17/04 2:09p Markw
// 
//*****************************************************************************
//<AMI_FHDR_START>
//
// Name:	SmmStatusCode_h
//
// Description:	This file is an include file used to define the Protocol for the
//		        Firmware Volume Block Protocol.
//
//<AMI_FHDR_END>
//*****************************************************************************
#ifndef __SMM_STATUS_CODE_PROTOCOL_H__
#define __SMM_STATUS_CODE_PROTOCOL_H__
#ifdef __cplusplus
extern "C" {
#endif
#include <EFI.h>

#define EFI_SMM_STATUS_CODE_PROTOCOL_GUID \
	{0x6afd2b77,0x98c1,0x4acd,0xa6,0xf9,0x8a,0x94,0x39,0xde,0xf,0xb1}

GUID_VARIABLE_DECLARATION(gEfiSmmStatusCodeProtocolGuid,EFI_SMM_STATUS_CODE_PROTOCOL_GUID);

typedef struct _EFI_SMM_STATUS_CODE_PROTOCOL EFI_SMM_STATUS_CODE_PROTOCOL;

typedef EFI_STATUS (EFIAPI *EFI_SMM_REPORT_STATUS_CODE) (
	IN EFI_SMM_STATUS_CODE_PROTOCOL	*This,
	IN EFI_STATUS_CODE_TYPE			CodeType,
	IN EFI_STATUS_CODE_VALUE		Value,
	IN UINT32						Instance,
	IN EFI_GUID						*CallerId,
	IN EFI_STATUS_CODE_DATA			*Data OPTIONAL
);

struct _EFI_SMM_STATUS_CODE_PROTOCOL {
	EFI_SMM_REPORT_STATUS_CODE ReportStatusCode;
};

/****** DO NOT WRITE BELOW THIS LINE *******/
#ifdef __cplusplus
}
#endif
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
