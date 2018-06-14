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
// $Header: /Alaska/BIN/Core/Include/Protocol/HiiConfigAccess.h 3     11/25/09 11:23a Felixp $
//
// $Revision: 3 $
//
// $Date: 11/25/09 11:23a $
//**********************************************************************
// Revision History
// ----------------
// $Log: /Alaska/BIN/Core/Include/Protocol/HiiConfigAccess.h $
// 
// 3     11/25/09 11:23a Felixp
// Action parameter of the Callback function is updated  based on UEFI
// errata
// 
// 2     10/13/09 6:06p Felixp
// Hii.h renamed to UefiHii.h
// 
// 1     10/09/09 3:52p Felixp
// 
// 1     2/27/09 3:55p Artems
// Initial check-in
// 
// 1     3/18/07 5:23p Felixp
// 
//**********************************************************************
//<AMI_FHDR_START>
//
// Name:	<HiiConfigAccess.h>
//
// Description:	Hii Config access protocol header file
//
//<AMI_FHDR_END>
//**********************************************************************
#ifndef __HII_CONFIG_ACCESS__H__
#define __HII_CONFIG_ACCESS__H__
#ifdef __cplusplus
extern "C" {
#endif

#include <UefiHii.h>

#define EFI_HII_CONFIG_ACCESS_PROTOCOL_GUID \
    { 0x330d4706, 0xf2a0, 0x4e4f, 0xa3, 0x69, 0xb6, 0x6f, 0xa8, 0xd5, 0x43, 0x85 }

GUID_VARIABLE_DECLARATION(gEfiHiiConfigAccessProtocolGuid, EFI_HII_CONFIG_ACCESS_PROTOCOL_GUID);

typedef struct _EFI_HII_CONFIG_ACCESS_PROTOCOL EFI_HII_CONFIG_ACCESS_PROTOCOL;

typedef EFI_STATUS
(EFIAPI * EFI_HII_ACCESS_EXTRACT_CONFIG ) (
    IN CONST EFI_HII_CONFIG_ACCESS_PROTOCOL *This,
    IN CONST EFI_STRING Request,
    OUT EFI_STRING *Progress,
    OUT EFI_STRING *Results
);

typedef EFI_STATUS
(EFIAPI * EFI_HII_ACCESS_ROUTE_CONFIG ) (
    IN CONST EFI_HII_CONFIG_ACCESS_PROTOCOL *This,
    IN CONST EFI_STRING Configuration,
    OUT EFI_STRING *Progress
);

typedef EFI_STATUS
(EFIAPI *EFI_HII_ACCESS_FORM_CALLBACK) (
    IN CONST EFI_HII_CONFIG_ACCESS_PROTOCOL *This,
//Based on errata for uefi2.1-2.3 approved in the 11/18 USWG meeting 
//the Action parameter is not a pointer
    IN EFI_BROWSER_ACTION Action,
    IN EFI_QUESTION_ID QuestionId,
    IN UINT8 Type,
    IN EFI_IFR_TYPE_VALUE *Value,
    OUT EFI_BROWSER_ACTION_REQUEST *ActionRequest
);

struct _EFI_HII_CONFIG_ACCESS_PROTOCOL {
    EFI_HII_ACCESS_EXTRACT_CONFIG ExtractConfig;
    EFI_HII_ACCESS_ROUTE_CONFIG   RouteConfig;
    EFI_HII_ACCESS_FORM_CALLBACK  Callback;
};

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