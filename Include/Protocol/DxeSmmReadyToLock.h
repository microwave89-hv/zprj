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
// $Header: /Alaska/SOURCE/Modules/SMM/DxeSmmReadyToLock.h 1     6/22/11 11:54a Markw $
//
// $Revision: 1 $
//
// $Date: 6/22/11 11:54a $
//**********************************************************************
// Revision History
// ----------------
// $Log: /Alaska/SOURCE/Modules/SMM/DxeSmmReadyToLock.h $
// 
// 1     6/22/11 11:54a Markw
// 
// 6     1/13/10 2:13p Felixp
// 
//**********************************************************************
//<AMI_FHDR_START>
//
// Name:  DxeSmmReadyToLock.h
//
// Description:	DxeSmmReadyToLock protocol definition
//
//<AMI_FHDR_END>
//**********************************************************************

#ifndef __DXE_SMM_READY_TO_LOCK__H__
#define __DXE_SMM_READY_TO_LOCK__H__
#if PI_SPECIFICATION_VERSION >= 0x0001000A

#ifdef __cplusplus
extern "C" {
#endif

#define EFI_DXE_SMM_READY_TO_LOCK_PROTOCOL_GUID \
    {0x60ff8964, 0xe906, 0x41d0, 0xaf, 0xed, 0xf2, 0x41, 0xe9, 0x74, 0xe0, 0x8e } 
  
GUID_VARIABLE_DECLARATION(gEfiDxeSmmReadyToLockProtocolGuid,EFI_DXE_SMM_READY_TO_LOCK_PROTOCOL_GUID);

/****** DO NOT WRITE BELOW THIS LINE *******/
#ifdef __cplusplus
}
#endif
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
