//**********************************************************************
//**********************************************************************
//**                                                                  **
//**        (C)Copyright 1985-2011, American Megatrends, Inc.         **
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
// $Header: /Alaska/BIN/Core/Include/Protocol/ReportStatusCodeHandler.h 1     6/16/11 9:48a Felixp $
//
// $Revision: 1 $
//
// $Date: 6/16/11 9:48a $
//**********************************************************************
// Revision History
// ----------------
// $Log: /Alaska/BIN/Core/Include/Protocol/ReportStatusCodeHandler.h $
// 
// 1     6/16/11 9:48a Felixp
// 
// 6     1/13/10 2:13p Felixp
// 
//**********************************************************************
//<AMI_FHDR_START>
//
// Name:  ReportStatusCodeHandler.h
//
// Description:	Report Status Code Handler Protocol definitions header.
//
//<AMI_FHDR_END>
//**********************************************************************
#ifndef __REPORT_STATUS_CODE_HANDLER_PROTOCOL_H__
#define __REPORT_STATUS_CODE_HANDLER_PROTOCOL_H__
#ifdef __cplusplus
extern "C" {
#endif

#define EFI_RSC_HANDLER_PROTOCOL_GUID \
                { 0x86212936, 0xe76, 0x41c8, 0xa0, 0x3a, 0x2a, 0xf2, 0xfc, 0x1c, 0x39, 0xe2 }

GUID_VARIABLE_DECLARATION(gEfiRscHandlerProtocolGuid, EFI_RSC_HANDLER_PROTOCOL_GUID);

typedef EFI_STATUS
(EFIAPI *EFI_RSC_HANDLER_CALLBACK)(
    IN EFI_STATUS_CODE_TYPE   CodeType,
    IN EFI_STATUS_CODE_VALUE  Value,
    IN UINT32                 Instance,
    IN EFI_GUID               *CallerId,
    IN EFI_STATUS_CODE_DATA   *Data
);

typedef EFI_STATUS
(EFIAPI *EFI_RSC_HANDLER_REGISTER) (
    IN EFI_RSC_HANDLER_CALLBACK Callback, //A pointer to a function of type EFI_RSC_HANDLER_CALLBACK that is 
                                          //called when a call to ReportStatusCode() occurs.
    IN EFI_TPL Tpl                        //TPL at which callback can be safely invoked.
);

typedef EFI_STATUS
(EFIAPI *EFI_RSC_HANDLER_UNREGISTER) (
    IN EFI_RSC_HANDLER_CALLBACK Callback //A pointer to a function of type EFI_RSC_HANDLER_CALLBACK that is to be
                                         //unregistered.
);

typedef struct {
    EFI_RSC_HANDLER_REGISTER Register; //Register the callback for notification of status code messages.
    EFI_RSC_HANDLER_UNREGISTER Unregister; //Unregister the callback.
} EFI_RSC_HANDLER_PROTOCOL;

/****** DO NOT WRITE BELOW THIS LINE *******/
#ifdef __cplusplus
}
#endif
#endif // __REPORT_STATUS_CODE_HANDLER_H__
//**********************************************************************
//**********************************************************************
//**                                                                  **
//**        (C)Copyright 1985-2011, American Megatrends, Inc.         **
//**                                                                  **
//**                       All Rights Reserved.                       **
//**                                                                  **
//**      5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093        **
//**                                                                  **
//**                       Phone: (770)-246-8600                      **
//**                                                                  **
//**********************************************************************
//**********************************************************************
