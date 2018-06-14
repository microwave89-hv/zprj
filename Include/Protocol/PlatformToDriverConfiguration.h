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
// $Header: /Alaska/BIN/Core/Include/Protocol/PlatformToDriverConfiguration.h 1     4/22/11 6:45p Artems $
//
// $Revision: 1 $
//
// $Date: 4/22/11 6:45p $
//*************************************************************************
// Revision History
// ----------------
// $Log: /Alaska/BIN/Core/Include/Protocol/PlatformToDriverConfiguration.h $
// 
// 1     4/22/11 6:45p Artems
// 
//*************************************************************************
//<AMI_FHDR_START>
//
// Name:  PlatformToDriverConfiguration.h
//
//  Description:
//  EFI_PLATFORM_TO_DRIVER_CONFIGURATION_PROTOCOL definition file
//
//<AMI_FHDR_END>
//*************************************************************************
#ifndef __PLATFORM_TO_DRIVER_CONFIGURATION_PROTOCOL__H__
#define __PLATFORM_TO_DRIVER_CONFIGURATION_PROTOCOL__H__
#ifdef __cplusplus
extern "C" {
#endif

#include <EFI.h>

#define EFI_PLATFORM_TO_DRIVER_CONFIGURATION_PROTOCOL_GUID \
    { 0x642cd590, 0x8059, 0x4c0a, 0xa9, 0x58, 0xc5, 0xec, 0x7, 0xd2, 0x3c, 0x4b }

GUID_VARIABLE_DECLARATION(gEfiPlatformToDriverConfigurationProtocolGuid, EFI_PLATFORM_TO_DRIVER_CONFIGURATION_PROTOCOL_GUID);

typedef struct _EFI_PLATFORM_TO_DRIVER_CONFIGURATION_PROTOCOL EFI_PLATFORM_TO_DRIVER_CONFIGURATION_PROTOCOL;

typedef enum {
    EfiPlatformConfigurationActionNone              = 0,
    EfiPlatformConfigurationActionStopController    = 1,
    EfiPlatformConfigurationActionRestartController = 2,
    EfiPlatformConfigurationActionRestartPlatform   = 3,
    EfiPlatformConfigurationActionNvramFailed       = 4,
    EfiPlatformConfigurationActionMaximum
} EFI_PLATFORM_CONFIGURATION_ACTION;

typedef
EFI_STATUS
(EFIAPI *EFI_PLATFORM_TO_DRIVER_CONFIGURATION_QUERY) (
    IN  EFI_PLATFORM_TO_DRIVER_CONFIGURATION_PROTOCOL *This,
    IN  EFI_HANDLE                                    ControllerHandle,
    IN  EFI_HANDLE                                    ChildHandle OPTIONAL,
    IN  UINTN                                         *Instance,
    OUT EFI_GUID                                      **ParameterTypeGuid,
    OUT VOID                                          **ParameterBlock,
    OUT UINTN                                         *ParameterBlockSize
);

typedef
EFI_STATUS
    (EFIAPI *EFI_PLATFORM_TO_DRIVER_CONFIGURATION_RESPONSE) (
    IN EFI_PLATFORM_TO_DRIVER_CONFIGURATION_PROTOCOL *This,
    IN EFI_HANDLE                                    ControllerHandle,
    IN EFI_HANDLE                                    ChildHandle OPTIONAL,
    IN UINTN                                         *Instance,
    IN EFI_GUID                                      *ParameterTypeGuid,
    IN VOID                                          *ParameterBlock,
    IN UINTN                                         ParameterBlockSize,
    IN EFI_PLATFORM_CONFIGURATION_ACTION             ConfigurationAction
);

struct _EFI_PLATFORM_TO_DRIVER_CONFIGURATION_PROTOCOL {
    EFI_PLATFORM_TO_DRIVER_CONFIGURATION_QUERY Query;
    EFI_PLATFORM_TO_DRIVER_CONFIGURATION_RESPONSE Response;
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
