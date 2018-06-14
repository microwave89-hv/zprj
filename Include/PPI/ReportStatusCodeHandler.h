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
// $Header: /Alaska/BIN/Core/Include/PPI/ReportStatusCodeHandler.h 1     6/16/11 9:45a Felixp $
//
// $Revision: 1 $
//
// $Date: 6/16/11 9:45a $
//**********************************************************************
// Revision History
// ----------------
// $Log: /Alaska/BIN/Core/Include/PPI/ReportStatusCodeHandler.h $
// 
// 1     6/16/11 9:45a Felixp
// 
// 6     1/13/10 2:13p Felixp
// 
//**********************************************************************
//<AMI_FHDR_START>
//
// Name:  ReportStatusCodeHandler.h
//
// Description:	Report Status Code Handler PPI definitions header.
//
//<AMI_FHDR_END>
//**********************************************************************
#ifndef __REPORT_STATUS_CODE_HANDLER_PPI_H__
#define __REPORT_STATUS_CODE_HANDLER_PPI_H__
#ifdef __cplusplus
extern "C" {
#endif

#define EFI_PEI_RSC_HANDLER_PPI_GUID \
  { 0x65d394, 0x9951, 0x4144, 0x82, 0xa3, 0xa, 0xfc, 0x85, 0x79, 0xc2, 0x51 }

GUID_VARIABLE_DECLARATION(gEfiPeiRscHandlerPpiGuid, EFI_PEI_RSC_HANDLER_PPI_GUID);

typedef
EFI_STATUS
(EFIAPI *EFI_PEI_RSC_HANDLER_CALLBACK)(
    IN CONST  EFI_PEI_SERVICES        **PeiServices,
    IN        EFI_STATUS_CODE_TYPE    Type,
    IN        EFI_STATUS_CODE_VALUE   Value,
    IN        UINT32                  Instance,
    IN CONST  EFI_GUID                *CallerId,
    IN CONST  EFI_STATUS_CODE_DATA    *Data
);

typedef
EFI_STATUS
(EFIAPI *EFI_PEI_RSC_HANDLER_REGISTER)(
    IN EFI_PEI_RSC_HANDLER_CALLBACK Callback    //A pointer to a function of type EFI_PEI_RSC_HANDLER_CALLBACK that 
                                                //is called when a call to ReportStatusCode() occurs.
);

typedef
EFI_STATUS
(EFIAPI *EFI_PEI_RSC_HANDLER_UNREGISTER)(
    IN EFI_PEI_RSC_HANDLER_CALLBACK Callback   //A pointer to a function of type EFI_PEI_RSC_HANDLER_CALLBACK that 
                                               // is to be unregistered
);

typedef struct _EFI_PEI_RSC_HANDLER_PPI {
    EFI_PEI_RSC_HANDLER_REGISTER Register;      //Register the callback for notification of status code messages.
    EFI_PEI_RSC_HANDLER_UNREGISTER Unregister;  //Unregister the callback.
} EFI_PEI_RSC_HANDLER_PPI;

/****** DO NOT WRITE BELOW THIS LINE *******/
#ifdef __cplusplus
}
#endif
#endif // __REPORT_STATUS_CODE_HANDLER_PPI_H__
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
