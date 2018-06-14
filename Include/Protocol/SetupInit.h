//**********************************************************************
//**********************************************************************
//**                                                                  **
//**        (C)Copyright 1985-2009, American Megatrends, Inc.         **
//**                                                                  **
//**                       All Rights Reserved.                       **
//**                                                                  **
//**      5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093        **
//**                                                                  **
//**                       Phone: (770)-246-8600                      **
//**                                                                  **
//**********************************************************************
//**********************************************************************

//**********************************************************************
// $Header: /Alaska/BIN/Core/Include/Protocol/SetupInit.h 4     11/23/09 7:07p Felixp $
//
// $Revision: 4 $
//
// $Date: 11/23/09 7:07p $
//**********************************************************************
// Revision History
// ----------------
// $Log: /Alaska/BIN/Core/Include/Protocol/SetupInit.h $
// 
// 4     11/23/09 7:07p Felixp
// The content is removed. The protocol is deprecated.
// 
// 3     3/13/06 1:40a Felixp
// 
// 2     3/25/05 11:21a Felixp
// 
// 1     3/25/05 11:19a Felixp
// 
//**********************************************************************
//<AMI_FHDR_START>
//
// Name:	SetupInit.h
//
// Description:	SetupInit Protocol
//
//<AMI_FHDR_END>
//**********************************************************************
#ifndef __SETUP_INIT_PROTOCOL_H__
#define __SETUP_INIT_PROTOCOL_H__
#ifdef __cplusplus
extern "C" {
#endif
#if !defined(GUID_VARIABLE_DEFINITION)
#pragma message("The SETUP_INIT_INTERFACE protocol is depricated.")
#pragma message("Use LoadResources library function instead.")
#if EFI_SPECIFICATION_VERSION>0x20000
#error the protocol is depricated
#endif
#endif
/****** DO NOT WRITE BELOW THIS LINE *******/
#ifdef __cplusplus
}
#endif
#endif
//**********************************************************************
//**********************************************************************
//**                                                                  **
//**        (C)Copyright 1985-2009, American Megatrends, Inc.         **
//**                                                                  **
//**                       All Rights Reserved.                       **
//**                                                                  **
//**      5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093        **
//**                                                                  **
//**                       Phone: (770)-246-8600                      **
//**                                                                  **
//**********************************************************************
//**********************************************************************
