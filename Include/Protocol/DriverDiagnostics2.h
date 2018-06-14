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
// $Header: /Alaska/BIN/Core/Include/Protocol/DriverDiagnostics2.h 1     4/21/11 12:53p Artems $
//
// $Revision: 1 $
//
// $Date: 4/21/11 12:53p $
//*************************************************************************
// Revision History
// ----------------
// $Log: /Alaska/BIN/Core/Include/Protocol/DriverDiagnostics2.h $
// 
// 1     4/21/11 12:53p Artems
// 
//
//*************************************************************************
//<AMI_FHDR_START>
//
// Name:  DriverDiagnostics2.h
//
//  Description:
//  EFI_DRIVER_DIAGNOSTICS2_PROTOCOL definition file
//
//<AMI_FHDR_END>
//*************************************************************************
#ifndef __DRIVER_DIAGNOSTICS2_PROTOCOL__H__
#define __DRIVER_DIAGNOSTICS2_PROTOCOL__H__
#ifdef __cplusplus
extern "C" {
#endif

#include <EFI.h>

#define EFI_DRIVER_DIAGNOSTICS_PROTOCOL_GUID \
    { 0x4d330321, 0x025f, 0x4aac, 0x90, 0xd8, 0x5e, 0xd9, 0x00, 0x17, 0x3b, 0x63 }

GUID_VARIABLE_DECLARATION(gEfiDriverDiagnostics2ProtocolGuid, EFI_DRIVER_DIAGNOSTICS_PROTOCOL_GUID);


typedef struct _EFI_DRIVER_DIAGNOSTICS2_PROTOCOL EFI_DRIVER_DIAGNOSTICS2_PROTOCOL;

typedef enum {
    EfiDriverDiagnosticTypeStandard      = 0,
    EfiDriverDiagnosticTypeExtended      = 1,
    EfiDriverDiagnosticTypeManufacturing = 2,
    EfiDriverDiagnosticTypeMaximum
} EFI_DRIVER_DIAGNOSTIC_TYPE;

typedef
EFI_STATUS
(EFIAPI *EFI_DRIVER_DIAGNOSTICS2_RUN_DIAGNOSTICS) (
    IN  EFI_DRIVER_DIAGNOSTICS2_PROTOCOL *This,
    IN  EFI_HANDLE                       ControllerHandle,
    IN  EFI_HANDLE                       ChildHandle OPTIONAL,
    IN  EFI_DRIVER_DIAGNOSTIC_TYPE       DiagnosticType,
    IN  CHAR8                            *Language,
    OUT EFI_GUID                         **ErrorType,
    OUT UINTN                            *BufferSize,
    OUT CHAR16                           **Buffer
);


struct _EFI_DRIVER_DIAGNOSTICS2_PROTOCOL {
    EFI_DRIVER_DIAGNOSTICS2_RUN_DIAGNOSTICS RunDiagnostics;
    CHAR8                                   *SupportedLanguages;
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
