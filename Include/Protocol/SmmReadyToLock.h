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
//**********************************************************************
// $Header: /Alaska/SOURCE/Modules/SMM/SmmReadyToLock.h 3     6/24/11 2:11p Felixp $
//
// $Revision: 3 $
//
// $Date: 6/24/11 2:11p $
//**********************************************************************
// Revision History
// ----------------
// $Log: /Alaska/SOURCE/Modules/SMM/SmmReadyToLock.h $
// 
// 3     6/24/11 2:11p Felixp
// DxeSmmReadyToLock protocol definitions are moved to DxeSmmReadyToLock.h
// 
// 6     1/13/10 2:13p Felixp
// 
//**********************************************************************
//<AMI_FHDR_START>
//
// Name:  SmmReadyToLock.h
//
// Description:	SmmReadyToLock protocol definition
//
//<AMI_FHDR_END>
//**********************************************************************
#ifndef __SMM_READY_TO_LOCK__H__
#define __SMM_READY_TO_LOCK__H__
#if PI_SPECIFICATION_VERSION >= 0x0001000A

#ifdef __cplusplus
extern "C" {
#endif

#define EFI_SMM_READY_TO_LOCK_PROTOCOL_GUID \
    {0x47b7fa8c, 0xf4bd, 0x4af6, 0x82, 0x00, 0x33, 0x30, 0x86, 0xf0, 0xd2, 0xc8 } 
  
GUID_VARIABLE_DECLARATION(gEfiSmmReadyToLockProtocolGuid,EFI_SMM_READY_TO_LOCK_PROTOCOL_GUID);

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
