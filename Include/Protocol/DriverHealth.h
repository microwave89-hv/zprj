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
// $Header: /Alaska/BIN/Core/Include/Protocol/DriverHealth.h 1     4/21/11 12:53p Artems $
//
// $Revision: 1 $
//
// $Date: 4/21/11 12:53p $
//*************************************************************************
// Revision History
// ----------------
// $Log: /Alaska/BIN/Core/Include/Protocol/DriverHealth.h $
// 
// 1     4/21/11 12:53p Artems
// 
//*************************************************************************
//<AMI_FHDR_START>
//
// Name:  DriverHealth.h
//
//  Description:
//  EFI_DRIVER_HEALTH_PROTOCOL definition file
//
//<AMI_FHDR_END>
//*************************************************************************
#ifndef __DRIVER_HEALTH_PROTOCOL__H__
#define __DRIVER_HEALTH_PROTOCOL__H__
#ifdef __cplusplus
extern "C" {
#endif

#include <EFI.h>
#include <UefiHii.h>

#define EFI_DRIVER_HEALTH_PROTOCOL_GUID \
    { 0x2a534210, 0x9280, 0x41d8, 0xae, 0x79, 0xca, 0xda, 0x1, 0xa2, 0xb1, 0x27 }

GUID_VARIABLE_DECLARATION(gEfiDriverHealthProtocolGuid, EFI_DRIVER_HEALTH_PROTOCOL_GUID);


typedef struct _EFI_DRIVER_HEALTH_PROTOCOL EFI_DRIVER_HEALTH_PROTOCOL;

typedef enum {
    EfiDriverHealthStatusHealthy,
    EfiDriverHealthStatusRepairRequired,
    EfiDriverHealthStatusConfigurationRequired,
    EfiDriverHealthStatusFailed,
    EfiDriverHealthStatusReconnectRequired,
    EfiDriverHealthStatusRebootRequired
} EFI_DRIVER_HEALTH_STATUS;

typedef struct {
    EFI_HII_HANDLE HiiHandle;
    EFI_STRING_ID  StringId;
    UINT64         Reserved;
} EFI_DRIVER_HEALTH_HII_MESSAGE;

typedef
EFI_STATUS
(EFIAPI *EFI_DRIVER_HEALTH_REPAIR_NOTIFY) (
    IN UINTN Value,
    IN UINTN Limit
);

typedef
EFI_STATUS
(EFIAPI *EFI_DRIVER_HEALTH_GET_HEALTH_STATUS) (
    IN EFI_DRIVER_HEALTH_PROTOCOL     *This,
    IN EFI_HANDLE                     ControllerHandle, OPTIONAL
    IN EFI_HANDLE                     ChildHandle, OPTIONAL
    OUT EFI_DRIVER_HEALTH_STATUS      *HealthStatus,
    OUT EFI_DRIVER_HEALTH_HII_MESSAGE **MessageList, OPTIONAL
    OUT EFI_HII_HANDLE                *FormHiiHandle OPTIONAL
);

typedef
EFI_STATUS
(EFIAPI *EFI_DRIVER_HEALTH_REPAIR) (
    IN EFI_DRIVER_HEALTH_PROTOCOL       *This,
    IN EFI_HANDLE                       ControllerHandle,
    IN EFI_HANDLE                       ChildHandle, OPTIONAL
    IN EFI_DRIVER_HEALTH_REPAIR_NOTIFY  RepairNotify OPTIONAL
);

struct _EFI_DRIVER_HEALTH_PROTOCOL {
    EFI_DRIVER_HEALTH_GET_HEALTH_STATUS GetHealthStatus;
    EFI_DRIVER_HEALTH_REPAIR            Repair;
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
