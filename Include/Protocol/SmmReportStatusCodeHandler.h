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
// $Header: /Alaska/BIN/Core/Include/Protocol/SmmReportStatusCodeHandler.h 1     6/16/11 9:48a Felixp $
//
// $Revision: 1 $
//
// $Date: 6/16/11 9:48a $
//**********************************************************************
// Revision History
// ----------------
// $Log: /Alaska/BIN/Core/Include/Protocol/SmmReportStatusCodeHandler.h $
// 
// 1     6/16/11 9:48a Felixp
// 
// 6     1/13/10 2:13p Felixp
// 
//**********************************************************************
//<AMI_FHDR_START>
//
// Name:  SmmReportStatusCodeHandler.h
//
// Description:	Smm Report Status Code Handler Protocol definitions header.
//
//<AMI_FHDR_END>
//**********************************************************************
#ifndef __SMM_REPORT_STATUS_CODE_HANDLER_PROTOCOL_H__
#define __SMM_REPORT_STATUS_CODE_HANDLER_PROTOCOL_H__
#ifdef __cplusplus
extern "C" {
#endif

#define EFI_SMM_RSC_HANDLER_PROTOCOL_GUID \
    {0x2ff29fa7, 0x5e80, 0x4ed9, 0xb3, 0x80, 0x1, 0x7d, 0x3c, 0x55, 0x4f, 0xf4}

GUID_VARIABLE_DECLARATION(gEfiSmmRscHandlerProtocolGuid, EFI_SMM_RSC_HANDLER_PROTOCOL_GUID);

typedef EFI_STATUS 
(EFIAPI *EFI_SMM_RSC_HANDLER_CALLBACK) (
    IN EFI_STATUS_CODE_TYPE CodeType,
    IN EFI_STATUS_CODE_VALUE Value,
    IN UINT32 Instance,
    IN EFI_GUID * CallerId,
    IN EFI_STATUS_CODE_DATA * Data
);

typedef EFI_STATUS
(EFIAPI *EFI_SMM_RSC_HANDLER_REGISTER) (
    IN EFI_SMM_RSC_HANDLER_CALLBACK Callback //A pointer to a function of type EFI_SMM_RSC_HANDLER_CALLBACK that is 
                                             //called when call to ReportStatusCode() occurs.
);

typedef EFI_STATUS
(EFIAPI *EFI_SMM_RSC_HANDLER_UNREGISTER) (
    IN EFI_SMM_RSC_HANDLER_CALLBACK Callback //A pointer to a function of type EFI_SMM_RSC_HANDLER_CALLBACK that is 
                                             //to be unregistered.
);

typedef struct _EFI_SMM_RSC_HANDLER_PROTOCOL {
    EFI_SMM_RSC_HANDLER_REGISTER Register;   //Register the callback for notification of status code messages.
    EFI_SMM_RSC_HANDLER_UNREGISTER Unregister; //Unregister the callback.
} EFI_SMM_RSC_HANDLER_PROTOCOL;

/****** DO NOT WRITE BELOW THIS LINE *******/
#ifdef __cplusplus
}
#endif
#endif // __SMM_REPORT_STATUS_CODE_HANDLER_PROTOCOL_H__
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
