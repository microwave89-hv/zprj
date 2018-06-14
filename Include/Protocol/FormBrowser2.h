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
// $Header: /Alaska/BIN/Core/Include/Protocol/FormBrowser2.h 3     10/26/09 10:46a Felixp $
//
// $Revision: 3 $
//
// $Date: 10/26/09 10:46a $
//**********************************************************************
// Revision History
// ----------------
// $Log: /Alaska/BIN/Core/Include/Protocol/FormBrowser2.h $
// 
// 3     10/26/09 10:46a Felixp
// Declaration of EFI_BROWSER_ACTION_REQUEST type and the values of the
// type are removed (they are already defined in UefiHii.h).
// 
// 2     10/13/09 6:06p Felixp
// Hii.h renamed to UefiHii.h
// 
// 1     10/09/09 3:52p Felixp
// 
//**********************************************************************
//<AMI_FHDR_START>
//
// Name:	FormBrowser2.h
//
// Description:	Form Browser protocol header file
//
//<AMI_FHDR_END>
//**********************************************************************
#ifndef __FORM_BROWSER_2__H__
#define __FORM_BROWSER_2__H__
#ifdef __cplusplus
extern "C" {
#endif
#include <UefiHii.h>

#define EFI_FORM_BROWSER2_PROTOCOL_GUID \
    { 0xb9d4c360, 0xbcfb, 0x4f9b, 0x92, 0x98, 0x53, 0xc1, 0x36, 0x98, 0x22, 0x58 }

GUID_VARIABLE_DECLARATION(gEfiFormBrowser2ProtocolGuid, EFI_FORM_BROWSER2_PROTOCOL_GUID);

typedef struct _EFI_FORM_BROWSER2_PROTOCOL EFI_FORM_BROWSER2_PROTOCOL;

typedef struct {
    UINTN LeftColumn;
    UINTN RightColumn;
    UINTN TopRow;
    UINTN BottomRow;
} EFI_SCREEN_DESCRIPTOR;

typedef EFI_STATUS (EFIAPI *EFI_SEND_FORM2)(
    IN  CONST EFI_FORM_BROWSER2_PROTOCOL *This,
    IN  EFI_HII_HANDLE                   *Handles,
    IN  UINTN                            HandleCount,
    IN  EFI_GUID                         *FormSetGuid, OPTIONAL
    IN  UINT16                           FormId, OPTIONAL
    IN  CONST EFI_SCREEN_DESCRIPTOR      *ScreenDimensions, OPTIONAL
    OUT EFI_BROWSER_ACTION_REQUEST       *ActionRequest  OPTIONAL
);

typedef EFI_STATUS (EFIAPI *EFI_BROWSER_CALLBACK2)(
    IN CONST EFI_FORM_BROWSER2_PROTOCOL  *This,
    IN OUT UINTN                         *ResultsDataSize,
    IN OUT EFI_STRING                    ResultsData,
    IN BOOLEAN                           RetrieveData,
    IN CONST EFI_GUID                    *VariableGuid, OPTIONAL
    IN CONST CHAR16                      *VariableName  OPTIONAL
);

struct _EFI_FORM_BROWSER2_PROTOCOL {
    EFI_SEND_FORM2        SendForm;
    EFI_BROWSER_CALLBACK2 BrowserCallback;
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
