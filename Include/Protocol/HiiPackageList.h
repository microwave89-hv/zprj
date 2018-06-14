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
// $Header: /Alaska/BIN/Core/Include/Protocol/HiiPackageList.h 1     11/19/09 12:53p Felixp $
//
// $Revision: 1 $
//
// $Date: 11/19/09 12:53p $
//**********************************************************************
// Revision History
// ----------------
// $Log: /Alaska/BIN/Core/Include/Protocol/HiiPackageList.h $
// 
// 1     11/19/09 12:53p Felixp
// 
//**********************************************************************
//<AMI_FHDR_START>
//
// Name:  HiiPackageList.h
//
// Description:	HII Package List Protocol Definition
//
//<AMI_FHDR_END>
//**********************************************************************
#ifndef __HII_PACKAGE_LIST_PROTOCOL__H__
#define __HII_PACKAGE_LIST_PROTOCOL__H__
#ifdef __cplusplus
extern "C" {
#endif
#include <UefiHii.h>

#define EFI_HII_PACKAGE_LIST_PROTOCOL_GUID \
  { 0x6a1ee763, 0xd47a, 0x43b4, {0xaa, 0xbe, 0xef, 0x1d, 0xe2, 0xab, 0x56, 0xfc}}

GUID_VARIABLE_DECLARATION(gEfiHiiPackageListProtocolGuid, EFI_HII_PACKAGE_LIST_PROTOCOL_GUID);

typedef EFI_HII_PACKAGE_LIST_HEADER* EFI_HII_PACKAGE_LIST_PROTOCOL;
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
