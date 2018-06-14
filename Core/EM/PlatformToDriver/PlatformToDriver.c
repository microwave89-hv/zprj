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
// $Header: /Alaska/BIN/Core/Modules/PlatformToDriverConfiguration/PlatformToDriver.c 1     5/02/11 5:30p Artems $
//
// $Revision: 1 $
//
// $Date: 5/02/11 5:30p $
//**********************************************************************
// Revision History
// ----------------
// $Log: /Alaska/BIN/Core/Modules/PlatformToDriverConfiguration/PlatformToDriver.c $
// 
// 1     5/02/11 5:30p Artems
// Platform-to-Driver confuguration protocol supporting infrastructure
// 
//**********************************************************************
//<AMI_FHDR_START>
//
// Name: PlatformToDriver.c
//
// Description: 
//
//<AMI_FHDR_END>
//**********************************************************************
#include <Token.h>
#include <AmiDxeLib.h>
#include <Protocol\PlatformToDriverConfiguration.h>

typedef EFI_STATUS (PLATFORM_TO_DRIVER_AGENT_SUPPORTED) (
   IN EFI_HANDLE ControllerHandle,
   IN EFI_HANDLE ChildHandle OPTIONAL
);

typedef EFI_STATUS (PLATFORM_TO_DRIVER_AGENT_QUERY) (
    IN  EFI_HANDLE ControllerHandle,
    IN  EFI_HANDLE ChildHandle OPTIONAL,
    IN  UINTN      *Instance,
    OUT EFI_GUID   **ParameterTypeGuid,
    OUT VOID       **ParameterBlock,
    OUT UINTN      *ParameterBlockSize
);

typedef EFI_STATUS (PLATFORM_TO_DRIVER_AGENT_RESPONSE) (
    IN EFI_HANDLE                        ControllerHandle,
    IN EFI_HANDLE                        ChildHandle OPTIONAL,
    IN UINTN                             *Instance,
    IN EFI_GUID                          *ParameterTypeGuid,
    IN VOID                              *ParameterBlock,
    IN UINTN                             ParameterBlockSize,
    IN EFI_PLATFORM_CONFIGURATION_ACTION ConfigurationAction
);

typedef struct{
	PLATFORM_TO_DRIVER_AGENT_SUPPORTED  *Supported;
    PLATFORM_TO_DRIVER_AGENT_QUERY      *Query;
	PLATFORM_TO_DRIVER_AGENT_RESPONSE   *Response;
} PLATFORM_TO_DRIVER_AGENT;


#define OEM_PLATFORM_TO_DRIVER_AGENT(Supported, Query, Response) Supported
extern PLATFORM_TO_DRIVER_AGENT_SUPPORTED PlatformToDriverAgentList EndOfList1;
#undef OEM_PLATFORM_TO_DRIVER_AGENT

#define OEM_PLATFORM_TO_DRIVER_AGENT(Supported, Query, Response) Query
extern PLATFORM_TO_DRIVER_AGENT_QUERY PlatformToDriverAgentList EndOfList2;
#undef OEM_PLATFORM_TO_DRIVER_AGENT

#define OEM_PLATFORM_TO_DRIVER_AGENT(Supported, Query, Response) Response
extern PLATFORM_TO_DRIVER_AGENT_RESPONSE PlatformToDriverAgentList EndOfList3;
#undef OEM_PLATFORM_TO_DRIVER_AGENT

#define OEM_PLATFORM_TO_DRIVER_AGENT(Supported, Query, Response) { Supported, Query, Response }
PLATFORM_TO_DRIVER_AGENT AgentList[] = {
    PlatformToDriverAgentList
    { NULL, NULL, NULL }
};

EFI_HANDLE CurrentControllerHandle = NULL;
UINT32 CurrentAgentIndex;

EFI_STATUS PlatformToDriverConfigurationQuery (
    IN  EFI_PLATFORM_TO_DRIVER_CONFIGURATION_PROTOCOL *This,
    IN  EFI_HANDLE                                    ControllerHandle,
    IN  EFI_HANDLE                                    ChildHandle OPTIONAL,
    IN  UINTN                                         *Instance,
    OUT EFI_GUID                                      **ParameterTypeGuid,
    OUT VOID                                          **ParameterBlock,
    OUT UINTN                                         *ParameterBlockSize
)
{
    EFI_STATUS Status;

    if(ControllerHandle == NULL || Instance == NULL)
        return EFI_INVALID_PARAMETER;

    if(ControllerHandle != CurrentControllerHandle) {
        CurrentAgentIndex = 0;
        Status = EFI_UNSUPPORTED;
        while(AgentList[CurrentAgentIndex].Supported != NULL) {
            Status = AgentList[CurrentAgentIndex].Supported(ControllerHandle, ChildHandle);
            if(!EFI_ERROR(Status))
                break;
            CurrentAgentIndex++;
        }
        if(EFI_ERROR(Status)) {
            CurrentControllerHandle = NULL;
            return EFI_NOT_FOUND;
        }

        CurrentControllerHandle = ControllerHandle;
    }

    return AgentList[CurrentAgentIndex].Query(ControllerHandle,
                                              ChildHandle,
                                              Instance,
                                              ParameterTypeGuid,
                                              ParameterBlock,
                                              ParameterBlockSize);
}

EFI_STATUS PlatformToDriverConfigurationResponse (
    IN EFI_PLATFORM_TO_DRIVER_CONFIGURATION_PROTOCOL *This,
    IN EFI_HANDLE                                    ControllerHandle,
    IN EFI_HANDLE                                    ChildHandle OPTIONAL,
    IN UINTN                                         *Instance,
    IN EFI_GUID                                      *ParameterTypeGuid,
    IN VOID                                          *ParameterBlock,
    IN UINTN                                         ParameterBlockSize,
    IN EFI_PLATFORM_CONFIGURATION_ACTION             ConfigurationAction
)
{
    if(ControllerHandle == NULL || Instance == NULL)
        return EFI_INVALID_PARAMETER;

    if(ControllerHandle != CurrentControllerHandle)
        return EFI_NOT_FOUND;

    return AgentList[CurrentAgentIndex].Response(ControllerHandle,
                                                 ChildHandle,
                                                 Instance,
                                                 ParameterTypeGuid,
                                                 ParameterBlock,
                                                 ParameterBlockSize,
                                                 ConfigurationAction);
}

EFI_PLATFORM_TO_DRIVER_CONFIGURATION_PROTOCOL EfiPlatformToDriverConfigurationProtocol = {
    PlatformToDriverConfigurationQuery,
    PlatformToDriverConfigurationResponse
};

EFI_STATUS PlatformToDriverEntryPoint(
    IN EFI_HANDLE ImageHandle,
    IN EFI_SYSTEM_TABLE *SystemTable
)
{
    EFI_STATUS  Status;
    EFI_HANDLE  Handle = NULL;

    InitAmiLib(ImageHandle,SystemTable);

    Status = pBS->InstallMultipleProtocolInterfaces(
                                &Handle,
                                &gEfiPlatformToDriverConfigurationProtocolGuid, 
                                &EfiPlatformToDriverConfigurationProtocol,
                                NULL);


    return Status;
}



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