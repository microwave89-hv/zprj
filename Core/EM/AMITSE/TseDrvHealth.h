//*****************************************************************//
//*****************************************************************//
//*****************************************************************//
//**                                                             **//
//**         (C)Copyright 2012, American Megatrends, Inc.        **//
//**                                                             **//
//**                     All Rights Reserved.                    **//
//**                                                             **//
//**   5555 Oakbrook Pkwy, Building 200,Norcross, Georgia 30093  **//
//**                                                             **//
//**                     Phone (770)-246-8600                    **//
//**                                                             **//
//*****************************************************************//
//*****************************************************************//
//*****************************************************************//
// $Archive: /Alaska/BIN/Modules/AMITSE2_0/AMITSE/TseDrvHealth.h $
//
// $Author: Arunsb $
//
// $Revision: 5 $
//
// $Date: 10/18/12 5:31a $
//
//*****************************************************************//
//*****************************************************************//
// Revision History
// ----------------
// $Log: /Alaska/BIN/Modules/AMITSE2_0/AMITSE/TseDrvHealth.h $
// 
// 5     10/18/12 5:31a Arunsb
// Updated for 2.16.1235 QA submission
// 
// 2     10/10/12 12:23p Arunsb
// Synched the source for v2.16.1232 backup with Aptio
// 
// 4     5/29/12 3:19a Arunsb
// [TAG]  		EIP91109
// [Category]  	Improvement
// [Description]  	Sync the Aptio IV source for AptioV
// 
// 3     5/28/12 11:09a Premkumara
// [TAG]  		EIP83080
// [Category]  	Improvement
// [Description]  	Support REF4 type control.
// [Files]  		TseDrvHealth.h, Hii.c
// 
// 2     7/01/11 5:13a Arunsb
// Build error suppressed when building with binaries alone.
// 
// 1     6/30/11 4:04a Arunsb
// Contains TSE specific driver health declarations.
// 
//*****************************************************************//
//*****************************************************************//
//<AMI_FHDR_START>
//----------------------------------------------------------------------------
//
// Name:		TseDrvHealth.h
//
// Description:	Header file for driver health only contains TSE specific.
//
//----------------------------------------------------------------------------
//<AMI_FHDR_END>
#if EFI_SPECIFICATION_VERSION>=0x20014           
#include "Protocol/DriverHealth.h"
#include "Protocol/DevicePathToText.h"
#else

#ifndef __DRIVER_HEALTH_PROTOCOL__H__
#define __DRIVER_HEALTH_PROTOCOL__H__

#define EFI_DRIVER_HEALTH_PROTOCOL_GUID \
    { 0x2a534210, 0x9280, 0x41d8, 0xae, 0x79, 0xca, 0xda, 0x1, 0xa2, 0xb1, 0x27 }
typedef struct _EFI_DRIVER_HEALTH_PROTOCOL EFI_DRIVER_HEALTH_PROTOCOL;

typedef enum {
    EfiDriverHealthStatusHealthy,
    EfiDriverHealthStatusRepairRequired,
    EfiDriverHealthStatusConfigurationRequired,
    EfiDriverHealthStatusFailed,
    EfiDriverHealthStatusReconnectRequired,
    EfiDriverHealthStatusRebootRequired
} EFI_DRIVER_HEALTH_STATUS;

typedef UINT16 EFI_STRING_ID; 
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

#endif  /* __DRIVER_HEALTH_PROTOCOL__H__ */

#ifndef __DEVICE_PATH_TO_TEXT_PROTOCOL__H__
#define __DEVICE_PATH_TO_TEXT_PROTOCOL__H__


#define EFI_DEVICE_PATH_TO_TEXT_PROTOCOL_GUID \
    { 0x8b843e20, 0x8132, 0x4852, 0x90, 0xcc, 0x55, 0x1a, 0x4e, 0x4a, 0x7f, 0x1c }

GUID_VARIABLE_DECLARATION(gEfiDevicePathToTextProtocolGuid, EFI_DEVICE_PATH_TO_TEXT_PROTOCOL_GUID);


typedef struct _EFI_DEVICE_PATH_TO_TEXT_PROTOCOL EFI_DEVICE_PATH_TO_TEXT_PROTOCOL;

typedef
CHAR16*
(EFIAPI *EFI_DEVICE_PATH_TO_TEXT_NODE) (
    IN CONST EFI_DEVICE_PATH_PROTOCOL *DeviceNode,
    IN       BOOLEAN                  DisplayOnly,
    IN       BOOLEAN                  AllowShortcuts
);

typedef
CHAR16*
(EFIAPI *EFI_DEVICE_PATH_TO_TEXT_PATH) (
    IN CONST EFI_DEVICE_PATH_PROTOCOL *DevicePath,
    IN       BOOLEAN                  DisplayOnly,
    IN       BOOLEAN                  AllowShortcuts
);

struct _EFI_DEVICE_PATH_TO_TEXT_PROTOCOL {
    EFI_DEVICE_PATH_TO_TEXT_NODE ConvertDeviceNodeToText;
    EFI_DEVICE_PATH_TO_TEXT_PATH ConvertDevicePathToText;
};

#endif	/* __DEVICE_PATH_TO_TEXT_PROTOCOL__H__ */
#endif  /* EFI_SPECIFICATION_VERSION */

typedef struct DRV_HEALTH_HNDLS{
	EFI_HANDLE 	ControllerHandle;
	EFI_HANDLE 	ChildHandle;
	EFI_DRIVER_HEALTH_STATUS	HealthStatus;
	struct DRV_HEALTH_HNDLS 	*Next;
}DRV_HEALTH_HNDLS;

CHAR16 *GetDrvHlthCtrlName (DRV_HEALTH_HNDLS *);
VOID AddHandleIntoList (EFI_HANDLE, EFI_HANDLE, EFI_DRIVER_HEALTH_STATUS);
VOID DisplayMsgListMessageBox (EFI_DRIVER_HEALTH_HII_MESSAGE *MessageList);
BOOLEAN AdvancedRepairSupported (VOID);

//*****************************************************************//
//*****************************************************************//
//*****************************************************************//
//**                                                             **//
//**         (C)Copyright 2012, American Megatrends, Inc.        **//
//**                                                             **//
//**                     All Rights Reserved.                    **//
//**                                                             **//
//**   5555 Oakbrook Pkwy, Building 200,Norcross, Georgia 30093  **//
//**                                                             **//
//**                     Phone (770)-246-8600                    **//
//**                                                             **//
//*****************************************************************//
//*****************************************************************//
//*****************************************************************//