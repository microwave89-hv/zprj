//**********************************************************************
//**********************************************************************
//**                                                                  **
//**        (C)Copyright 1985-2016, American Megatrends, Inc.         **
//**                                                                  **
//**                       All Rights Reserved.                       **
//**                                                                  **
//**         5555 Oakbrook Pkwy, Suite 200, Norcross, GA 30093        **
//**                                                                  **
//**                       Phone: (770)-246-8600                      **
//**                                                                  **
//**********************************************************************
//**********************************************************************
//**********************************************************************
// $Header: /Alaska/SOURCE/Modules/NVMe/NvmeBus.c 8     12/08/16 4:17a Karthikar $
//
// $Revision: 8 $
//
// $Date: 12/08/16 4:17a $
//**********************************************************************
// Revision History
// ----------------
// $Log: /Alaska/SOURCE/Modules/NVMe/NvmeBus.c $
// 
// 8     12/08/16 4:17a Karthikar
// [TAG]  		EIP307568
// [Category]  	Bug Fix
// [Symptom]  	Legacy Installation and booting fails in
// (INT)_a_4.6.5.5_NVMe_006
// [RootCause]  	Since this NvmeSmm_Support token is not included in
// Token.h, TransferNvmeDataToSmram() dint get control.
// [Solution]  	Added NvmeSmm_Support token in Token.h
// [Files]  		NvmeBus.c
// 
// 7     3/17/16 10:25a Anbuprakashp
// [TAG]  		EIP258388
// [Category]  	Bug Fix
// [Severity]  	Minor
// [Symptom]  	Build error when disable CSM_SUPPORT token
// [RootCause]  	NvmeSmm driver is dependent on NvmeInt13 driver which is
// disabled if CSM_SUPPORT token is off.
// [Solution]  	NvmeSmm driver will be disabled if CSM_SUPPORT,
// NVMEINT13_SUPPORT sdl tokens are OFF.
// [Files]  		NvmeSmm.sdl,
// NvmeBus.c
// 
// 6     5/14/15 2:38a Karthikar
// 
// 5     4/08/15 10:21a Anbuprakashp
// [TAG]  		EIP212320
// [Category]  	Bug Fix
// [Severity]  	Critical
// [Symptom]  	CPU exception in Nvme Driver if
// PcdCpuSmmCodeAccessCheckEnable is enabled
// [RootCause]  	BootService call shouldn't be used inside SMM function.
// if PcdCpuSmmCodeAccessCheckEnable is enabled, It causes CPU exception.
// [Solution]  	Changes made to avoid BootService call inside SMM function
// [Files]  		NvmeSmm.c
// NvmeBus.c
// AmiNvmeController.h
// 
// 4     3/09/15 2:51a Rameshr
// [TAG]  		EIP202328
// [Category]  	Improvement
// [Description]  	IO Completion Size decided based on the size reported
// by device.
// [Files]  		NvmeBus.c
// 
// 3     9/23/14 2:28a Anandakrishnanl
// [TAG]  		EIP180861
// [Category]  	Improvement
// [Description]  	Add Legacy Boot support in Aptio 4.x Nvme driver - NON
// PI 1.2 Support
// [Files]  		NvmeBus.c
// NvmeBus.h
// NvmeSmm.c
// NvmeSmm.h
// NvmeSmm.dxs
// NvmeSmm.sdl
// 
// 
// 2     9/04/14 7:34a Anandakrishnanl
// [TAG]  		EIP180861
// [Category]  	Improvement
// [Description]  	Legacy Boot support in Aptio 4.x Nvme driver
// [Files]  		
// Nvme.cif	
// Nvme.mak	
// Nvme.uni
// Nvme.chm	
// NvmeSetup.c
// NvmeBus.c
// NvmeComponentName.c
// NvmeIncludes.h
// NvmeBus.h
// [NvmeControllerLib]
// [NvmeSmm]
// [NVMEINT13]
// [NvmeProtocol]
// 
// 1     6/20/14 6:27a Anandakrishnanl
// [TAG]  		EIP172958
// [Category]  	New Feature
// [Description]  	Nvme Driver Intial Checkin
// [Files]  		Nvme.cif
// Nvme.sdl
// Nvme.mak
// Nvme.sd
// Nvme.uni
// Nvme.chm
// NvmeSetup.c
// NvmeBus.c
// NvmeController.c
// NvmeComponentName.c
// NvmeIncludes.h
// NvmeBus.h
// NvmeController.h
// 
//**********************************************************************
//<AMI_FHDR_START>
//
// Name:        NvmeBus.c
//
// Description: Provides Nvme Block IO protocol
//
//<AMI_FHDR_END>
//**********************************************************************

#include "NvmeIncludes.h"
#include "NvmeBus.h"
#include "NvmePassthru.h"
#include <EFI.h>
#include <AmiLib.h>
#include <AmiDxeLib.h>
#include <Protocol\DevicePath.h>
#include <Protocol\BlockIo.h>

#ifndef EFI_COMPONENT_NAME2_PROTOCOL_GUID
EFI_GUID gComponentNameProtocolGuid = EFI_COMPONENT_NAME_PROTOCOL_GUID;
#else
EFI_GUID gComponentNameProtocolGuid = EFI_COMPONENT_NAME2_PROTOCOL_GUID;
#endif

// Used by NVMe legacy boot support
UINT8    gInt13DeviceAddress = 1;
VOID     *gLegacyNvmeBuffer = NULL;

#if (EFI_SPECIFICATION_VERSION > 0x00020000)
extern EFI_COMPONENT_NAME2_PROTOCOL gNvmeBusControllerDriverName;
#else
extern EFI_COMPONENT_NAME_PROTOCOL gNvmeBusControllerDriverName;
#endif

EFI_GUID gEfiDiskInfoNvmeInterfaceGuid             = EFI_DISK_INFO_NVME_INTERFACE_GUID;
EFI_GUID gEfiDiskInfoProtocolGuid                  = EFI_DISK_INFO_PROTOCOL_GUID;
static EFI_GUID gAmiNvmeControllerProtocolGuid     = AMI_NVME_CONTROLLER_PROTOCOL_GUID;
static EFI_GUID gAmiNvmePassThruProtocolGuid 	   = AMI_NVME_PASS_THRU_PROTOCOL_GUID;
static EFI_GUID gAmiNvmeLegacyProtocolGuid         = AMI_NVME_LEGACY_PROTOCOL_GUID;
static EFI_GUID gAmiSmmNvmeCommunicationGuid 	   = AMI_SMM_NVME_COMMUNICATION_GUID;
EFI_GUID gEfiNvmExpressPassThruProtocolGuid        = EFI_NVM_EXPRESS_PASS_THRU_PROTOCOL_GUID;

EFI_DRIVER_BINDING_PROTOCOL gNvmeBusDriverBinding = {
    NvmeBusSupported, 
    NvmeBusStart,     
    NvmeBusStop,      
    NVME_BUS_DRIVER_VERSION,  // version
    NULL,                    // ImageHandle
    NULL                     // DriverBindingHandle
};

//**********************************************************************
//<AMI_PHDR_START>
//
// Procedure:   NvmeBusEntryPoint
//
// Description: Installs gNvmeBusDriverBinding protocol
//
// Input:
//  IN EFI_HANDLE        ImageHandle,
//  IN EFI_SYSTEM_TABLE  *SystemTable
//
// Output:
//  EFI_STATUS
//
// Modified:
//      
// Referrals: InitAmiLib InstallMultipleProtocolInterfaces DListInit
//
// Notes:   
//  Here is the control flow of this function:
//  1. Initialize Ami Lib.
//  2. Install Driver Binding Protocol
//  3. Return EFI_SUCCESS.
//
//<AMI_PHDR_END>
//**********************************************************************
EFI_STATUS 
NvmeBusEntryPoint(
    IN EFI_HANDLE        ImageHandle,
    IN EFI_SYSTEM_TABLE  *SystemTable
  )
{
    EFI_STATUS  Status;

    // Print Verbose messages
    // Enable NVME_VERBOSE_PRINT in SDL file. Make sure PcdDebugPrintErrorLevel 
    // is set to PcdsPatchableInModule. Sometime is it is overridden in Platform SDL. 
    // So change it accordingly.
    
   
    gNvmeBusDriverBinding.DriverBindingHandle = NULL;
    gNvmeBusDriverBinding.ImageHandle=ImageHandle;

    InitAmiLib(ImageHandle, SystemTable);

    Status = pBS->InstallMultipleProtocolInterfaces(
                    &gNvmeBusDriverBinding.DriverBindingHandle,
                    &gEfiDriverBindingProtocolGuid,&gNvmeBusDriverBinding,
                    &gEfiComponentName2ProtocolGuid, &gNvmeBusControllerDriverName,
                    NULL
                    );

    return Status;
    
}

//**********************************************************************
//<AMI_PHDR_START>
//
// Procedure:   NvmeBusSupported
//
// Description: Checks whether it is a Nvme controller or not. 
//              If 'yes', return SUCCESS else ERROR
//
// Input:
//  IN EFI_DRIVER_BINDING_PROTOCOL    *This,
//  IN EFI_HANDLE                     Controller,
//  IN EFI_DEVICE_PATH_PROTOCOL       *RemainingDevicePath
//
// Output:
//  EFI_STATUS
//
//<AMI_PHDR_END>
//**********************************************************************
EFI_STATUS 
NvmeBusSupported(
    IN EFI_DRIVER_BINDING_PROTOCOL    *This,
    IN EFI_HANDLE                     Controller,
    IN EFI_DEVICE_PATH_PROTOCOL       *RemainingDevicePath )
{

    EFI_STATUS                  Status;
    EFI_PCI_IO_PROTOCOL         *PciIO;
    PCI_TYPE00                  PciConfig;

    // Check for Valid SATA Device Path. If no return UNSUPPORTED
    // Check if Controller is Nvme or not?

    Status = pBS->OpenProtocol( Controller,
                        &gEfiPciIoProtocolGuid,
                        (VOID **)&PciIO,
                        This->DriverBindingHandle,     
                        Controller,   
                        EFI_OPEN_PROTOCOL_GET_PROTOCOL);
    
    if (EFI_ERROR(Status)) {
        return EFI_UNSUPPORTED;
    }

     Status = PciIO->Pci.Read ( PciIO,
                                EfiPciIoWidthUint8,
                                0,
                                sizeof (PCI_TYPE00),
                                &PciConfig
                                );
     
     if (EFI_ERROR(Status)) {
        return EFI_UNSUPPORTED;
    }

     // Check for MASS Storage controller, Non-Volatile and NVMHCI interface
     if (IS_CLASS3 (&PciConfig, 
                 PCI_CLASS_MASS_STORAGE, 
                 PCI_CLASS_MASS_STORAGE_SOLID_STATE, 
                 PCI_IF_MASS_STORAGE_SOLID_STATE_ENTERPRISE_NVMHCI)) {
         
         return EFI_SUCCESS;
         
     }
     
    return EFI_UNSUPPORTED; 
}


//**********************************************************************
//<AMI_PHDR_START>
//
// Procedure:   NvmeBusStart
//
// Description: Installs Nvme Block IO Protocol
//
// Input:
//  IN EFI_DRIVER_BINDING_PROTOCOL    *This,
//  IN EFI_HANDLE                     Controller,
//  IN EFI_DEVICE_PATH_PROTOCOL       *RemainingDevicePath
//
// Output:
//  EFI_STATUS
//
// Modified:
//      
// Referrals: 
//
// Notes:   
// 
//
//<AMI_PHDR_END>
//**********************************************************************                
EFI_STATUS 
NvmeBusStart (
    IN EFI_DRIVER_BINDING_PROTOCOL    *This,
    IN EFI_HANDLE                     Controller,
    IN EFI_DEVICE_PATH_PROTOCOL       *RemainingDevicePath
)
{

    EFI_STATUS                         Status;
    EFI_PCI_IO_PROTOCOL                *PciIO;
    AMI_NVME_CONTROLLER_PROTOCOL       *NvmeController = NULL;
    IDENTIFY_CONTROLLER_DATA           *IdentifyData = NULL;
    UINT32                             *ActiveNameSpaceIDs = NULL;
    UINT32                             i;
    AMI_NVME_PASS_THRU_PROTOCOL        *AmiNvmePassThru;
    NVM_EXPRESS_PASS_THRU_INSTANCE     *NvmePassthruInstance = NULL;
    EFI_NVM_EXPRESS_PASS_THRU_PROTOCOL *EfiNvmExpressPassThru;

    PROGRESS_CODE(EFI_IO_BUS_ATA_ATAPI | EFI_IOB_PC_INIT);

    // Get the PciIO interface
    Status = pBS->OpenProtocol( Controller,
                        &gEfiPciIoProtocolGuid,
                        (VOID **)&PciIO,
                        This->DriverBindingHandle,     
                        Controller,   
                        EFI_OPEN_PROTOCOL_BY_DRIVER);

    if (EFI_ERROR(Status)) {
        return EFI_DEVICE_ERROR;
    }
    
    TRACE((-1,"\nNVMe Driver Detection and Configuratiion starts\n"));

    // Do Controller Init
    Status = InitializeNvmeController(Controller, This->DriverBindingHandle, &NvmeController);
    
    if (EFI_ERROR(Status)) {
        goto Error_Path;
    }
    
    // Get the IdentifyData
    Status = pBS->AllocatePool (
                    EfiBootServicesData,
                    sizeof (IDENTIFY_CONTROLLER_DATA),
                    (VOID**)&IdentifyData
                    );
    
    if (EFI_ERROR(Status)) {
        goto Error_Path_1;
    }
    
    pBS->SetMem(IdentifyData, sizeof(IDENTIFY_CONTROLLER_DATA), 0);
    NvmeController->IdentifyControllerData = IdentifyData;
    
    // Get IdentifyController Data Structure    
    Status = GetIdentifyData (NvmeController, (UINT8 *)IdentifyData, 1, 0);  
    if (EFI_ERROR(Status)) {
        goto Error_Path_1;
    }
    
    // Get the list of Active Namespace IDs
    Status = pBS->AllocatePages (
                        AllocateAnyPages,
                        EfiRuntimeServicesData,
                        EFI_SIZE_TO_PAGES(4096),                            
                        (EFI_PHYSICAL_ADDRESS*)&(ActiveNameSpaceIDs));

    if (EFI_ERROR(Status)) {
        goto Error_Path_1;
    }
    
    pBS->SetMem(ActiveNameSpaceIDs, 4096, 0);
    
    NvmeController->ActiveNameSpaceIDs = ActiveNameSpaceIDs;
    
    // Since "Get list of Active NameSpace IDs" isn't working 
    // use alternate method to get the active name space. Zero is reserved
    for (i=1; i < IdentifyData->NN + 1; i++ ) {
        ActiveNameSpaceIDs[i] = i;
    }
    
    Status = EnumerateActiveNameSpace (NvmeController);
    if (EFI_ERROR(Status)) {
        goto Error_Path_1;
    }

    // Is there any active name space discovered
    if(IsListEmpty(&NvmeController->ActiveNameSpaceList)) {
        goto    exit_NvmeBusStart;
    }
    
    // Create Submission and Completion Queue1
    NvmeController->NVMQueueNumber = 1;
    Status  = CreateAdditionalSubmissionCompletionQueue(NvmeController, 
                                                NvmeController->NvmeCmdWrapper, 
                                                NvmeController->NVMQueueNumber, 
                                                NvmeController->MaxQueueEntrySupported >= QUEUE1_SIZE ? QUEUE1_SIZE : NvmeController->MaxQueueEntrySupported
                                                );
    if (EFI_ERROR(Status)) {
        goto Error_Path;
    }
    Status = InstallBlockIoDiskInfo(This, NvmeController);
    if (EFI_ERROR(Status)) {
        goto Error_Path_1;
    }
    
    // Install NvmePassThru protocol
    Status = pBS->OpenProtocol( 
                  Controller,
                  &gAmiNvmePassThruProtocolGuid,
                  (VOID **)&AmiNvmePassThru,
                  This->DriverBindingHandle,     
                  Controller,   
                  EFI_OPEN_PROTOCOL_GET_PROTOCOL
                  );
    
    if (EFI_ERROR(Status)) {
        Status = pBS->AllocatePool (
                      EfiBootServicesData,
                      sizeof(AMI_NVME_PASS_THRU_PROTOCOL),
                      (VOID**)&AmiNvmePassThru
                      );
        if (!EFI_ERROR(Status)) {
            AmiNvmePassThru->ExecuteNvmeCmd = ExecuteNvmeCmd;
            pBS->InstallMultipleProtocolInterfaces(
                        &Controller,
                        &gAmiNvmePassThruProtocolGuid, 
                        AmiNvmePassThru,
                        NULL
                        );
        }
        
    }
    // Installing EfiNvmExpressPassthru protocol
    Status = pBS->OpenProtocol( 
                  Controller,
                  &gEfiNvmExpressPassThruProtocolGuid,
                  (VOID **)&EfiNvmExpressPassThru,
                  This->DriverBindingHandle,
                  Controller,   
                  EFI_OPEN_PROTOCOL_GET_PROTOCOL
                  );
    
    if ( EFI_ERROR(Status) ) {
        // Allocate memory for NVM_EXPRESS_PASS_THRU_INSTANCE structure
        Status = pBS->AllocatePool (
                      EfiBootServicesData,
                      sizeof(NVM_EXPRESS_PASS_THRU_INSTANCE),
                      (VOID**)&NvmePassthruInstance
                      );

        if( !EFI_ERROR(Status) ) {

            Status = pBS->AllocatePool (
                          EfiBootServicesData,
                          sizeof(EFI_NVM_EXPRESS_PASS_THRU_MODE),
                          (VOID**)&NvmePassthruInstance->EfiNvmExpressPassThru.Mode
                          );
            if(EFI_ERROR(Status)) {
                pBS->FreePool(NvmePassthruInstance);
            }
        } 
        
        if (!EFI_ERROR(Status)) {

            EfiNvmExpressPassThru = (EFI_NVM_EXPRESS_PASS_THRU_PROTOCOL*)&(NvmePassthruInstance->EfiNvmExpressPassThru);

            NvmePassthruInstance->NvmeControllerProtocol = NvmeController;
            NvmePassthruInstance->ControllerHandle = Controller;

            EfiNvmExpressPassThru->Mode->Attributes = EFI_NVM_EXPRESS_PASS_THRU_ATTRIBUTES_PHYSICAL |
                                                       EFI_NVM_EXPRESS_PASS_THRU_ATTRIBUTES_CMD_SET_NVME;
            EfiNvmExpressPassThru->Mode->IoAlign = 2; // DWORD aligned
            EfiNvmExpressPassThru->Mode->NvmeVersion = 0;
            EfiNvmExpressPassThru->PassThru = NvmePassThru;
            EfiNvmExpressPassThru->GetNextNamespace = GetNextNamespace;
            EfiNvmExpressPassThru->BuildDevicePath = BuildDevicePath;
            EfiNvmExpressPassThru->GetNameSpace = GetNamespace;

            pBS->InstallMultipleProtocolInterfaces( &NvmePassthruInstance->ControllerHandle,
                                                    &gEfiNvmExpressPassThruProtocolGuid, 
                                                    &NvmePassthruInstance->EfiNvmExpressPassThru,
                                                    NULL
                                                   );
        }
    }
    
exit_NvmeBusStart:
    TRACE((-1,"\nNVMe Driver Detection and Configuratiion Ends with Status =  EFI_SUCCESS\n"));  
    return EFI_SUCCESS;
Error_Path_1:
    // Uninstall NvmeController
    pBS->UninstallMultipleProtocolInterfaces(
                        Controller,
                        &gAmiNvmeControllerProtocolGuid, 
                        NvmeController,
                        NULL
                        );
Error_Path:
    pBS->CloseProtocol ( Controller,
                  &gEfiPciIoProtocolGuid,
                  This->DriverBindingHandle,
                  Controller);
    TRACE((-1,"\nNVMe Driver Detection and Configuratiion Ends with Status %r\n", Status));
    return Status;

}

//**********************************************************************
//<AMI_PHDR_START>
//
// Procedure:   NvmeBusStop
//
// Description: Uninstall all devices installed in start procedure.
//
// Input:
//  IN EFI_DRIVER_BINDING_PROTOCOL    *This,
//  IN EFI_HANDLE                     Controller,
//  IN UINTN                          NumberOfChildren,
//  IN EFI_HANDLE                     *ChildHandleBuffer
//
// Output:
//  EFI_STATUS
//
// Modified:
//      
// Referrals: OpenProtocol CloseProtocol 
//
// Notes:   
//
//<AMI_PHDR_END>
//**********************************************************************
EFI_STATUS 
NvmeBusStop (
    IN EFI_DRIVER_BINDING_PROTOCOL    *This,
    IN EFI_HANDLE                     Controller,
    IN UINTN                          NumberOfChildren,
    IN EFI_HANDLE                     *ChildHandleBuffer
 )
{

    EFI_STATUS                      Status;
    AMI_NVME_CONTROLLER_PROTOCOL    *NvmeController;
    ACTIVE_NAMESPACE_DATA           *ActiveNameSpace;
    UINTN                           Index = 0;
    EFI_DEVICE_PATH_PROTOCOL        *DevicePath;
    NVME_DEVICE_PATH                *NvmeDevicePath;
    EFI_LIST_ENTRY                  *LinkData;
    EFI_LIST_ENTRY  		    *ForwardLink;
    AMI_NVME_PASS_THRU_PROTOCOL     *AmiNvmePassThru;
    EFI_NVM_EXPRESS_PASS_THRU_PROTOCOL *NvmExpressPassthruProtocol;
    NVM_EXPRESS_PASS_THRU_INSTANCE     *NvmePassthruInstance = NULL;

    // Check if gAmiNvmeControllerProtocolGuid is installed on the device
    Status = pBS->OpenProtocol( Controller,
                        &gAmiNvmeControllerProtocolGuid,
                        (VOID **)&NvmeController,
                        This->DriverBindingHandle,
                        Controller,
                        EFI_OPEN_PROTOCOL_GET_PROTOCOL);
    
    if (EFI_ERROR(Status)) {
        return EFI_DEVICE_ERROR;
    }
    
    //
    // Check if ChildHandleBuffer is valid
    //
    if (NumberOfChildren) {
        while (NumberOfChildren) {
            // Does the child handle have the correct devicepath
            Status = pBS->OpenProtocol(
                            ChildHandleBuffer[Index],
                            &gEfiDevicePathProtocolGuid,
                            (VOID **)&DevicePath,
                            This->DriverBindingHandle,     
                            Controller,
                            EFI_OPEN_PROTOCOL_GET_PROTOCOL);
            
            // Locate Nvme devicepath
            NvmeDevicePath = (NVME_DEVICE_PATH *) DevicePath;
            
            while (!isEndNode((EFI_DEVICE_PATH_PROTOCOL *)NvmeDevicePath)) {
                
                //NvmeDevicePath = (NVME_DEVICE_PATH *)DPNextInstance (&((EFI_DEVICE_PATH_PROTOCOL *)(NvmeDevicePath)), NULL);
                if (NvmeDevicePath && NvmeDevicePath->Header.Type == MESSAGING_DEVICE_PATH && \
                                NvmeDevicePath->Header.SubType == MSG_NVME_DP){
                    
                    for (LinkData = NvmeController->ActiveNameSpaceList.ForwardLink; \
                            LinkData != &NvmeController->ActiveNameSpaceList; 
                            ) {
                        
                        ActiveNameSpace = _CR(LinkData, ACTIVE_NAMESPACE_DATA, Link);
                        
                        // Is it the correct ActiveNameSpace
                        if (ActiveNameSpace->IdentifyNamespaceData.EUI64 == NvmeDevicePath->EUI64 && \
                                    ActiveNameSpace->ActiveNameSpaceID == NvmeDevicePath->Nsid ) {
                            
                            // Uninstall and close the protocols
                            Status = pBS->CloseProtocol ( 
                                                Controller,
                                                &gEfiPciIoProtocolGuid,
                                                This->DriverBindingHandle,
                                                ChildHandleBuffer[Index]);
                            
                            if (EFI_ERROR(Status)) {
                                continue;
                            }
                            
                            // Check if BlockIO is installed
                            Status = pBS->OpenProtocol( ChildHandleBuffer[Index],
                                                &gEfiBlockIoProtocolGuid,
                                                NULL,
                                                This->DriverBindingHandle,     
                                                ChildHandleBuffer[Index],   
                                                EFI_OPEN_PROTOCOL_TEST_PROTOCOL);

                            if (Status == EFI_SUCCESS) {
                                Status = pBS->UninstallMultipleProtocolInterfaces (
                                                ChildHandleBuffer[Index],
                                                &gEfiBlockIoProtocolGuid,
                                                &(ActiveNameSpace->NvmeBlockIO),
                                                NULL);
                            }
                            // Check if DiskInfo is installed
                            Status = pBS->OpenProtocol( ChildHandleBuffer[Index],
                                                        &gEfiDiskInfoProtocolGuid,
                                                        NULL,
                                                        This->DriverBindingHandle,
                                                        ChildHandleBuffer[Index],
                                                        EFI_OPEN_PROTOCOL_TEST_PROTOCOL );

                            if (Status == EFI_SUCCESS) {
                                Status = pBS->UninstallMultipleProtocolInterfaces (
                                                ChildHandleBuffer[Index],
                                                &gEfiDiskInfoProtocolGuid,
                                                &(ActiveNameSpace->NvmeDiskInfo),
                                                NULL);
                            }

                            Status = pBS->UninstallMultipleProtocolInterfaces (
                                            ChildHandleBuffer[Index],
                                            &gEfiDevicePathProtocolGuid,
                                            ActiveNameSpace->EfiDevicePath,
                                            NULL);
                            
                            if (EFI_ERROR(Status)) {
                                return EFI_DEVICE_ERROR;
                            } else {
                                // Delete from the list
//                                RemoveEntryList(&(ActiveNameSpace->Link));
                                
                                // Free up all the memory 
                                NvmeController->PciIO->Unmap(NvmeController->PciIO, 
                                                            ActiveNameSpace->PRP2ListUnMap
                                                            );
                                
                                  if (ActiveNameSpace->PRP2List) { 
                                      NvmeController->PciIO->FreeBuffer (NvmeController->PciIO,
                                                                      EFI_SIZE_TO_PAGES(NvmeController->MemoryPageSize),\
                                                                      ActiveNameSpace->PRP2List
                                                                      );
                                  }
                                  
                                  pBS->FreePool (ActiveNameSpace->NvmeBlockIO.Media);
                                  pBS->FreePool (ActiveNameSpace->EfiDevicePath);
                                  
                                  if (ActiveNameSpace->UDeviceName) {
                                      pBS->FreePool (ActiveNameSpace->UDeviceName->Language);
                                      pBS->FreePool (ActiveNameSpace->UDeviceName->UnicodeString);
                                      pBS->FreePool (ActiveNameSpace->UDeviceName);
                                  }

				  ForwardLink = LinkData->ForwardLink;	
                                  RemoveEntryList (LinkData);
			          LinkData =  ForwardLink;
                                  pBS->FreePool (ActiveNameSpace);
                            }
                        }
                        
                    }

                    break;
                }
                
                (EFI_DEVICE_PATH_PROTOCOL *)NvmeDevicePath = NEXT_NODE ((EFI_DEVICE_PATH_PROTOCOL *)NvmeDevicePath); 
            } 
            Index++;
            NumberOfChildren --;
        }
    } else {
          // Check if all Active namespace has been stopped
          if(!IsListEmpty(&NvmeController->ActiveNameSpaceList)) {
              return EFI_DEVICE_ERROR;
          } 
          // No child is active. 
          // Stop the controller. This will delete all the Queues.
          CONTROLLER_REG32_AND(NvmeController->NvmeBarOffset, Offset_CC, 0xFFFFFFFE);
          
          Status = pBS->UninstallMultipleProtocolInterfaces (
                         Controller,
                         &gAmiNvmeControllerProtocolGuid,
                         NvmeController,
                         NULL);
          ASSERT_EFI_ERROR(Status);
          Status = pBS->OpenProtocol( Controller,
                                &gAmiNvmePassThruProtocolGuid,
                                (VOID **)&AmiNvmePassThru,
                                This->DriverBindingHandle,     
                                Controller,   
                                EFI_OPEN_PROTOCOL_GET_PROTOCOL);
        
          if (!EFI_ERROR(Status)) {
              Status = pBS->UninstallMultipleProtocolInterfaces(
                              Controller,
                              &gAmiNvmePassThruProtocolGuid, 
                              AmiNvmePassThru,
                              NULL
                              );
        
              ASSERT_EFI_ERROR(Status);
          }
          Status = pBS->OpenProtocol( Controller,
                                &gEfiNvmExpressPassThruProtocolGuid,
                                (VOID **)&NvmExpressPassthruProtocol,
                                This->DriverBindingHandle,
                                Controller,   
                                EFI_OPEN_PROTOCOL_GET_PROTOCOL);
        
          if (!EFI_ERROR(Status)) {

              Status = pBS->UninstallMultipleProtocolInterfaces(
                              Controller,
                              &gEfiNvmExpressPassThruProtocolGuid, 
                              NvmExpressPassthruProtocol,
                              NULL
                              );
        
              ASSERT_EFI_ERROR(Status);
              NvmePassthruInstance = _CR( NvmExpressPassthruProtocol ,NVM_EXPRESS_PASS_THRU_INSTANCE, EfiNvmExpressPassThru);
              pBS->FreePool (NvmePassthruInstance->EfiNvmExpressPassThru.Mode);
              pBS->FreePool (NvmePassthruInstance);
          }
       
          // Uninstall and close the protocols
          Status = pBS->CloseProtocol ( 
                            Controller,
                            &gEfiPciIoProtocolGuid,
                            This->DriverBindingHandle,
                            Controller);
        
          ASSERT_EFI_ERROR(Status);
        
          // Free up all the memory allocated
          if (NvmeController->IdentifyControllerData) { 
              pBS->FreePool (NvmeController->IdentifyControllerData);
          }
        
          if (NvmeController->IdentifyControllerData) { 
              pBS->FreePages ((EFI_PHYSICAL_ADDRESS)NvmeController->ActiveNameSpaceIDs, 
                          EFI_SIZE_TO_PAGES(4096)
                          );
        }

          if (NvmeController->AdminSubmissionQueueUnMap) { 
              NvmeController->PciIO->Unmap (NvmeController->PciIO, 
                                    NvmeController->AdminSubmissionQueueUnMap
                                    );
          }
          if (NvmeController->AdminSubmissionUnAligned) { 
              NvmeController->PciIO->FreeBuffer (NvmeController->PciIO, \
                                            EFI_SIZE_TO_PAGES(NvmeController->AdminSubmissionUnAlignedSize), \
                                           (VOID *)NvmeController->AdminSubmissionUnAligned
                                           );
        }
        
          if (NvmeController->AdminCompletionQueueUnMap) {
              NvmeController->PciIO->Unmap (NvmeController->PciIO, 
                                        NvmeController->AdminCompletionQueueUnMap
                                        );
          }
          if (NvmeController->AdminCompletionUnAligned) { 
              NvmeController->PciIO->FreeBuffer (NvmeController->PciIO, \
                                            EFI_SIZE_TO_PAGES(NvmeController->AdminCompletionUnAlignedSize), \
                                            (VOID *)NvmeController->AdminCompletionUnAligned
                                            );
          }
        
          if (NvmeController->Queue1SubmissionQueueUnMap) { 
              NvmeController->PciIO->Unmap (NvmeController->PciIO, 
                                        NvmeController->Queue1SubmissionQueueUnMap
                                        );
          }
          if (NvmeController->Queue1SubmissionUnAligned) { 
              NvmeController->PciIO->FreeBuffer (NvmeController->PciIO, \
                                             EFI_SIZE_TO_PAGES(NvmeController->Queue1SubmissionUnAlignedSize), \
                                             (VOID *)NvmeController->Queue1SubmissionUnAligned
                                             );
          }
        
          if (NvmeController->Queue1CompletionQueueUnMap) {  
              NvmeController->PciIO->Unmap (NvmeController->PciIO, 
                                    NvmeController->Queue1CompletionQueueUnMap
                                    ); 
          }
          if (NvmeController->Queue1CompletionUnAligned) { 
              NvmeController->PciIO->FreeBuffer (NvmeController->PciIO, \
                                             EFI_SIZE_TO_PAGES(NvmeController->Queue1CompletionUnAlignedSize), \
                                             (VOID *)NvmeController->Queue1CompletionUnAligned
                                             );
          }
          
          if (NvmeController->NvmeCmdWrapper) { 
              pBS->FreePool (NvmeController->NvmeCmdWrapper); 
          }
        
          if (NvmeController) { 
              pBS->FreePool (NvmeController);
          }
        
    }
    
    return EFI_SUCCESS;

}


//**********************************************************************
//<AMI_PHDR_START>
//
// Procedure:   InitializeNvmeController
//
// Description: Initialize Nvme controller and ADMIN submission and Completion queues
//
// Input:
//  IN  EFI_HANDLE                      Controller,
//  IN  EFI_HANDLE                      DriverBindingHandle,
//  OUT AMI_NVME_CONTROLLER_PROTOCOL        **NvmeControllerReturnAddress
//
// Output:
//  EFI_STATUS
//
// Modified:
//      
// Referrals: 
//
// Notes:   
//
//<AMI_PHDR_END>
//**********************************************************************
EFI_STATUS
InitializeNvmeController(
    IN  EFI_HANDLE                      Controller,
    IN  EFI_HANDLE                      DriverBindingHandle,
    OUT AMI_NVME_CONTROLLER_PROTOCOL    **NvmeControllerReturnAddress
)
{
    
    EFI_STATUS                      Status;
    EFI_PCI_IO_PROTOCOL             *PciIO;
    PCI_TYPE00                      PciConfig;
    UINT64                          ControllerCapabilities;
    UINT32                          Delay;
    UINT32                          ProgramCC = 0;
    EFI_PHYSICAL_ADDRESS            AdminQueueAddress = 0;
    UINTN                           AllocatePageSize;
    AMI_NVME_CONTROLLER_PROTOCOL    *NvmeController = NULL;
    UINT64                          PciAttributes;
    
    Status = pBS->AllocatePool (EfiBootServicesData,
                    sizeof(AMI_NVME_CONTROLLER_PROTOCOL),
                    (VOID**)&NvmeController
                    );
    
    if (EFI_ERROR(Status)) {
        return Status;
    }
    
    *NvmeControllerReturnAddress = NvmeController;
    
    // Clear memory
    pBS->SetMem(NvmeController, sizeof(AMI_NVME_CONTROLLER_PROTOCOL), 0);

    InitializeListHead (&NvmeController->ActiveNameSpaceList);
    
    // Get the PciIO interface
    Status = pBS->OpenProtocol( Controller,
                        &gEfiPciIoProtocolGuid,
                        (VOID **)&PciIO,
                        DriverBindingHandle,     
                        Controller,   
                        EFI_OPEN_PROTOCOL_GET_PROTOCOL);
    
    if (EFI_ERROR(Status)) {
        return Status;
    }
    
    // Enable PCI Cmd register
    Status = PciIO->Attributes(PciIO, EfiPciIoAttributeOperationSupported, 0, &PciAttributes);
    if (EFI_ERROR(Status)) {
        return Status;
    }
    
    Status = PciIO->Attributes(PciIO, EfiPciIoAttributeOperationEnable, PciAttributes & EFI_PCI_DEVICE_ENABLE, NULL);
    if (EFI_ERROR(Status)) {
        return Status;
    }
    
    Status = PciIO->Pci.Read ( PciIO,
                               EfiPciIoWidthUint8,
                               0,
                               sizeof (PCI_TYPE00),
                               &PciConfig
                               );
    
    if (EFI_ERROR(Status)) {
        return Status;
    }    
    NvmeController->NvmeBarOffset = Shl64(PciConfig.Device.Bar[1], 32) + (PciConfig.Device.Bar[0] & ~(0x07));
    NvmeController->PciIO = PciIO;
    NvmeController->ControllerHandle = Controller;
    
    ControllerCapabilities = Shl64(CONTROLLER_REG32(NvmeController->NvmeBarOffset, 4), 32) + 
                                        CONTROLLER_REG32(NvmeController->NvmeBarOffset, 0);
    
    // Initialize various capability values
    
    NvmeController->RawControllerCapabilities = ControllerCapabilities;
    NvmeController->MaxQueueEntrySupported = (ControllerCapabilities & 0xFFFF) + 1;
    NvmeController->ContiguousQueueRequired = (BOOLEAN)(Shr64((ControllerCapabilities & 0x10000), 16));
    NvmeController->ArbitrationMechanismSupport = (BOOLEAN)(Shr64((ControllerCapabilities & 0x60000), 17));
    NvmeController->TimeOut = (UINT8)(Shr64((ControllerCapabilities & 0xFF000000), 24));  // 500msec units
    NvmeController->DoorBellStride = (UINT8)(UINTN) (Shr64((ControllerCapabilities & 0xF00000000), 32));
    NvmeController->NVMResetSupport = (BOOLEAN) (Shr64((ControllerCapabilities & 0x1000000000), 36));
    NvmeController->CmdSetsSupported = (UINT8)(UINTN) (Shr64((ControllerCapabilities & 0x1FE000000000), 37));
    NvmeController->MemoryPageSizeMin = (UINT32)(UINTN) Shl64(1, (UINT8)(UINTN)(Shr64((ControllerCapabilities & 0xF000000000000), 48) + 12));  // In Bytes
    NvmeController->MemoryPageSizeMax = (UINT32)(UINTN) Shl64(1, (UINT8)(UINTN)(Shr64((ControllerCapabilities & 0xF0000000000000), 52) + 12)); // In Bytes
    
    PrintNvmeCapability(NvmeController);
    
    // Is NVM command set supported
    if (!(NvmeController->CmdSetsSupported & 0x1)) {
        return EFI_UNSUPPORTED;
    }
    
    // Check if the controller is already running. If yes stop it.
    Delay = NvmeController->TimeOut * 500;
    
    // Check if the controller is still in shutdown process occuring state
    do {
     
        if ((CONTROLLER_REG32(NvmeController->NvmeBarOffset, Offset_CSTS) & 0xC) != 4) {
            break;
        }
        pBS->Stall(1000); // 1msec delay
        
    }while (--Delay);

    if (!Delay) {
        return EFI_DEVICE_ERROR;
    }
    
    Delay = NvmeController->TimeOut * 500;
    if (CONTROLLER_REG32(NvmeController->NvmeBarOffset, Offset_CC) & 0x1) {
        
        //  Disable Enable bit
        CONTROLLER_REG32_AND (NvmeController->NvmeBarOffset, Offset_CC, ~0x01);
        do {
            if (!(CONTROLLER_REG32(NvmeController->NvmeBarOffset, Offset_CSTS) & 0x1)) {
                break;
            }
            pBS->Stall(1000); // 1msec delay
        }while (--Delay);
    }
    
    if (!Delay) {
        return EFI_DEVICE_ERROR;
    }
    
    // Initialize Controller configuration register. 
    // Select Round Robin and NVM Command Set (both values are zero)
    // Max Page Size
    NvmeController->MemoryPageSize = NvmeController->MemoryPageSizeMin;
    ProgramCC |= (UINT32) Shl64((UINTN)Shr64(NvmeController->MemoryPageSize, 13), 7);

    
    // Initialize with default value. Later it can be modified
    ProgramCC |= Shl64(6, 16);     // I/O Submission Queue Entry Size
    ProgramCC |= Shl64(4, 20);     // I/O Completion Queue Entry Size
    
    CONTROLLER_REG32(NvmeController->NvmeBarOffset, Offset_CC) =  ProgramCC;

    // Allocate memory for Admin Queue. Each entry is 64bytes long and queue should be aligned on MemoryPageSize
    AllocatePageSize = NvmeController->MemoryPageSize + 
                        ADMIN_QUEUE_SIZE * sizeof (NVME_ADMIN_COMMAND); 

#if  Nvme_VERBOSE_PRINT    
    TRACE((-1, "Value programmed in Control register  : %08X\n", ProgramCC));
#endif
    
    Status = NvmeController->PciIO->AllocateBuffer (NvmeController->PciIO,
                                             AllocateAnyPages,
                                             EfiRuntimeServicesData,
                                             EFI_SIZE_TO_PAGES(AllocatePageSize),
                                             (VOID **)&(AdminQueueAddress),
                                             EFI_PCI_IO_ATTRIBUTE_MEMORY_CACHED | EFI_PCI_IO_ATTRIBUTE_MEMORY_WRITE_COMBINE
                                             );
    
    if (EFI_ERROR(Status)) {
        return Status;
    }
    
    NvmeController->AdminSubmissionUnAligned = AdminQueueAddress;
    NvmeController->AdminSubmissionUnAlignedSize = EFI_SIZE_TO_PAGES(AllocatePageSize);
    NvmeController->AdminSubmissionQueue = (AdminQueueAddress & ~(NvmeController->MemoryPageSize - 1)) + 
                                            NvmeController->MemoryPageSize;

    Status = NvmeController->PciIO->Map ( NvmeController->PciIO, 
                                      EfiPciIoOperationBusMasterCommonBuffer,
                                      (VOID *)NvmeController->AdminSubmissionQueue,
                                      &AllocatePageSize,
                                      &NvmeController->AdminSubmissionQueueMappedAddr,
                                      &NvmeController->AdminSubmissionQueueUnMap
                                      );
    
    if (EFI_ERROR(Status)) {
        return Status;
    }
    
    Status = NvmeController->PciIO->AllocateBuffer (NvmeController->PciIO,
                                              AllocateAnyPages,
                                              EfiRuntimeServicesData,
                                              EFI_SIZE_TO_PAGES(AllocatePageSize),
                                              (VOID **)&(AdminQueueAddress),
                                              EFI_PCI_IO_ATTRIBUTE_MEMORY_CACHED | EFI_PCI_IO_ATTRIBUTE_MEMORY_WRITE_COMBINE
                                              );
    
    if (EFI_ERROR(Status)) {
        return Status;
    }
    
    NvmeController->AdminCompletionUnAligned = AdminQueueAddress;
    NvmeController->AdminCompletionUnAlignedSize = EFI_SIZE_TO_PAGES(AllocatePageSize);
    NvmeController->AdminCompletionQueue = (AdminQueueAddress & ~(NvmeController->MemoryPageSize - 1)) + 
                                            NvmeController->MemoryPageSize;

    Status = NvmeController->PciIO->Map ( NvmeController->PciIO, 
                                       EfiPciIoOperationBusMasterCommonBuffer,
                                       (VOID *)NvmeController->AdminCompletionQueue,
                                       &AllocatePageSize,
                                       &NvmeController->AdminCompletionQueueMappedAddr,
                                       &NvmeController->AdminCompletionQueueUnMap
                                       );
    
    if (EFI_ERROR(Status)) {
        return Status;
    }
    
    NvmeController->AdminSubmissionQueueSize = ADMIN_QUEUE_SIZE;
    NvmeController->AdminCompletionQueueSize = ADMIN_QUEUE_SIZE;

    // Clear memory
    pBS->SetMem((VOID *)NvmeController->AdminSubmissionQueue, NvmeController->AdminSubmissionQueueSize, 0);
    pBS->SetMem((VOID *)NvmeController->AdminCompletionQueue, NvmeController->AdminCompletionQueueSize, 0);
    
    // Program Admin Queue Size and Base Address
    CONTROLLER_REG32(NvmeController->NvmeBarOffset, Offset_Aqa) =  
                                                (UINT32)(Shl64((NvmeController->AdminCompletionQueueSize - 1),16) + 
                                                (NvmeController->AdminSubmissionQueueSize - 1));
    
    CONTROLLER_REG32(NvmeController->NvmeBarOffset, Offset_Asq) = 
                                                (UINT32) NvmeController->AdminSubmissionQueueMappedAddr;
    
    CONTROLLER_REG32(NvmeController->NvmeBarOffset, Offset_Asq + 4) =  
                                                (UINT32)Shr64(NvmeController->AdminSubmissionQueueMappedAddr, 32);
    
    CONTROLLER_REG32(NvmeController->NvmeBarOffset, Offset_Acq) =  
                                                (UINT32)NvmeController->AdminCompletionQueueMappedAddr;
    
    CONTROLLER_REG32(NvmeController->NvmeBarOffset, Offset_Acq + 4) =  
                                                (UINT32)Shr64(NvmeController->AdminCompletionQueueMappedAddr, 32);

#if  NVME_VERBOSE_PRINT
    TRACE ((-1, "Admin Submission Queue Size              : %08X\n", NvmeController->AdminSubmissionQueueSize));
    TRACE ((-1, "Admin Completion Queue Size              : %08X\n", NvmeController->AdminCompletionQueueSize));
    TRACE ((-1, "Admin Submission Queue Offset            : %08X\n", NvmeController->AdminSubmissionQueue));
    TRACE ((-1, "Admin Completion Queue Offset            : %08X\n", NvmeController->AdminCompletionQueue));
#endif
    
    NvmeController->AdminPhaseTag = FALSE;
    
    Status = pBS->AllocatePool (
                    EfiBootServicesData,
                    sizeof(NVME_COMMAND_WRAPPER),
                    (VOID**)&(NvmeController->NvmeCmdWrapper)
                    );
    
    if (EFI_ERROR(Status)) {
        return Status;
    }
    
    // Enable Controller
    CONTROLLER_REG32_OR(NvmeController->NvmeBarOffset, Offset_CC, 0x1);
    
    // Wait for the controller to get ready
    // Check if the cobtroller is already running. If yes stop it.
    Delay = NvmeController->TimeOut * 500;
    do {
        if ((CONTROLLER_REG32(NvmeController->NvmeBarOffset, Offset_CSTS) & 0x1)) {
            break;
        }
        pBS->Stall(1000); // 1msec delay
    } while (--Delay);
        
    if (!Delay) {
        return EFI_DEVICE_ERROR;
    }
    
    Status = SetNumberOfQueues (NvmeController);
    if (EFI_ERROR(Status)) {
        return Status;
    }    
    
    // Install NvmeController
    Status = pBS->InstallMultipleProtocolInterfaces(
                            &Controller,
                            &gAmiNvmeControllerProtocolGuid, 
                            NvmeController,
                            NULL
                            );
    
    
    return Status;
    
}

//**********************************************************************
//<AMI_PHDR_START>
//
// Procedure:   GetIdentifyData
//
// Description: Issue Nvme Admin Identify cmd
//
// Input:
//  IN AMI_NVME_CONTROLLER_PROTOCOL		*NvmeController, 
//  OUT UINT8                           *IdentifyData,
//  IN UINT8                            ControllerNameSpaceStructure, 
//  IN UINT32                           NameSpaceID
//
// Output:
//  EFI_STATUS
//
// Modified:
//      
// Referrals: 
//
// Notes:  
// ControllerNameSpaceStructure can take 0/1/2 : See Figure 81 NVM Express 1.1 Spec
// NameSpaceID can be 0 or specific NameSpace ID. See Figure 38 NVM Express 1.1 Spec
//
//<AMI_PHDR_END>
//**********************************************************************
EFI_STATUS  
GetIdentifyData (
    IN AMI_NVME_CONTROLLER_PROTOCOL *NvmeController, 
    OUT UINT8                       *IdentifyData,
    IN UINT8                        ControllerNameSpaceStructure, 
    IN UINT32                       NameSpaceID
)
{
    
    EFI_STATUS              Status;
    NVME_COMMAND_WRAPPER    *NvmeCmdWrapper = NULL;
    COMPLETION_QUEUE_ENTRY  CompletionData;

    Status = pBS->AllocatePool (
                    EfiBootServicesData,
                    sizeof(NVME_COMMAND_WRAPPER),
                    (VOID**)&(NvmeCmdWrapper)
                    );
    
    if (EFI_ERROR(Status)) {
        return Status;
    }
    
    // Clear memory
    pBS->SetMem(NvmeCmdWrapper, sizeof(NVME_COMMAND_WRAPPER), 0);
    
    // Build NVME command
    NvmeCmdWrapper->NvmCmd.CMD0.Opcode = IDENTIFY;
    NvmeCmdWrapper->NvmCmd.CMD0.FusedOperation = 0;
    NvmeCmdWrapper->NvmCmd.CMD0.PSDT = 0;
    NvmeCmdWrapper->NvmCmd.CMD0.CommandIdentifier = NvmeController->CommandIdentifierAdmin;
    NvmeCmdWrapper->NvmCmd.NSID = NameSpaceID;
            
    NvmeCmdWrapper->NvmCmd.PRP1 = (UINT64)IdentifyData;
    
    // If PRP1 isn't aligned on MemoryPageSize, then PRP2 will also be used.
    NvmeCmdWrapper->NvmCmd.PRP2 = ((UINT64)IdentifyData & ~((UINT64)NvmeController->MemoryPageSize-1)) + 
                                   NvmeController->MemoryPageSize; 
    
    NvmeCmdWrapper->NvmCmd.CDW10 = ControllerNameSpaceStructure;
    
    NvmeCmdWrapper->AdminOrNVMCmdSet = TRUE;
    NvmeCmdWrapper->SQIdentifier = 0;           // Queue 0 for Admin cmds
    NvmeCmdWrapper->CmdTimeOut = 1000;
    
    Status = ExecuteNvmeCmd (NvmeController, NvmeCmdWrapper, &CompletionData);
    
    if (!EFI_ERROR(Status)) {
        PrintIdentifyDataStructure (IdentifyData, ControllerNameSpaceStructure);
    }
    
    pBS->FreePool(NvmeCmdWrapper);
    return Status;
}

//**********************************************************************
//<AMI_PHDR_START>
//
// Procedure:   SetNumberOfQueues
//
// Description: Issue Set feature cmd to set the # if queues to 1
//
// Input:
//  IN AMI_NVME_CONTROLLER_PROTOCOL     *NvmeController, 
//
// Output:
//  EFI_STATUS
//
// Modified:
//      
// Referrals: 
//
// Notes:  
//
//<AMI_PHDR_END>
//**********************************************************************
EFI_STATUS
SetNumberOfQueues (
    IN AMI_NVME_CONTROLLER_PROTOCOL     *NvmeController
)
{

    EFI_STATUS              Status;
    NVME_COMMAND_WRAPPER    *NvmeCmdWrapper = NvmeController->NvmeCmdWrapper;
    COMPLETION_QUEUE_ENTRY  CompletionData;
        
    // Issue Set Feature cmd to initilaize # of queues to 1
    pBS->SetMem(NvmeController->NvmeCmdWrapper, sizeof(NVME_COMMAND_WRAPPER), 0);
    
    // Build NVME command
    NvmeCmdWrapper->NvmCmd.CMD0.Opcode = SET_FEATURES;
    NvmeCmdWrapper->NvmCmd.CMD0.CommandIdentifier = NvmeController->CommandIdentifierAdmin;
            
    NvmeCmdWrapper->NvmCmd.CDW10 = 0x7;
    NvmeCmdWrapper->NvmCmd.CDW11 = 0x10001;
    
    NvmeCmdWrapper->AdminOrNVMCmdSet = TRUE;
    NvmeCmdWrapper->SQIdentifier = 0;           // Queue 0 for Admin cmds
    NvmeCmdWrapper->CmdTimeOut = 1000;
    
    Status = ExecuteNvmeCmd (NvmeController, NvmeCmdWrapper, &CompletionData);
    
    return Status;
    
}

//**********************************************************************
//<AMI_PHDR_START>
//
// Procedure:   EnumerateActiveNameSpace
//
// Description: Detects active Namespavce and adds it into a linked list
//
// Input:
//  IN OUT AMI_NVME_CONTROLLER_PROTOCOL        *NvmeController
//
// Output:
//  EFI_STATUS
//
// Modified:
//      
// Referrals:  
//
// Notes:   
//
//<AMI_PHDR_END>
//**********************************************************************
EFI_STATUS
EnumerateActiveNameSpace (
    IN OUT AMI_NVME_CONTROLLER_PROTOCOL        *NvmeController       
)
{
    
    EFI_STATUS                  Status;
    ACTIVE_NAMESPACE_DATA       *ActiveNameSpaceData = 0;
    UINT32                      i;
    UINT32                      Index;
    UINT16                      DeviceName[41];
    CHAR8                       Language[] = LANGUAGE_CODE_ENGLISH;
    EFI_UNICODE_STRING_TABLE    *tempUnicodeTable;
    
    NvmeController->ActiveNameSpaceList.ForwardLink = &(NvmeController->ActiveNameSpaceList);
    NvmeController->ActiveNameSpaceList.BackLink = &(NvmeController->ActiveNameSpaceList);
 
    // Get Identify NameSpace Data for each Namespace 
    for (i = 1; (i < 1024) && NvmeController->ActiveNameSpaceIDs[i]; i++){
        
        // Get the list of Active Namespace IDs
        Status = pBS->AllocatePool (
                        EfiBootServicesData,
                        sizeof (ACTIVE_NAMESPACE_DATA),
                        (VOID**)&ActiveNameSpaceData
                        );
        if (EFI_ERROR(Status)) {
            return Status;
        }
        
        pBS->SetMem(ActiveNameSpaceData, sizeof(ACTIVE_NAMESPACE_DATA), 0);
        
        ActiveNameSpaceData->Link.ForwardLink = &(ActiveNameSpaceData->Link);
        ActiveNameSpaceData->Link.BackLink = &(ActiveNameSpaceData->Link);
        
        ActiveNameSpaceData->Signature = ACTIVE_NAME_SPACE_SIG;
        ActiveNameSpaceData->NvmeController = NvmeController;
        ActiveNameSpaceData->ActiveNameSpaceID = NvmeController->ActiveNameSpaceIDs[i];
        
        Status = DetectActiveNameSpace (NvmeController, ActiveNameSpaceData);
        
        if (!EFI_ERROR(Status)) {
            
            TRACE((-1,"NameSpace %02X detected %lx\n", ActiveNameSpaceData->ActiveNameSpaceID, ActiveNameSpaceData));
            InsertTailList (&NvmeController->ActiveNameSpaceList, &ActiveNameSpaceData->Link);
            
        } else {
            
              pBS->FreePool(ActiveNameSpaceData);
              // First instance of zero marks the end of valid namespace IDs
              if (!NvmeController->ActiveNameSpaceIDs[i+1]) {
                  break;
              }
              continue;
        }
        
        //
        // Convert the Device string from Engligh to Unicode
        //
        ActiveNameSpaceData->UDeviceName = NULL;
        
        pBS->SetMem(DeviceName, sizeof(DeviceName), 0);
        
        for (Index = 0; Index < 40; Index ++) {
            DeviceName[Index] = ((UINT8 *)NvmeController->IdentifyControllerData->ModelNumber)[Index];
        }
        DeviceName[40] = 0;                 // Word

        Status = pBS->AllocatePool (EfiBootServicesData,
                         sizeof (EFI_UNICODE_STRING_TABLE) * 2,
                         (VOID**)&tempUnicodeTable
                         );
        
        if (EFI_ERROR(Status)) {
            return Status;
        }
                
        pBS->SetMem(tempUnicodeTable, sizeof(EFI_UNICODE_STRING_TABLE) * 2, 0);
        
        Status = pBS->AllocatePool (EfiBootServicesData,
                         sizeof (Language),
                         (VOID**)&tempUnicodeTable[0].Language
                         );

        if (EFI_ERROR(Status)) {
            return Status;
        }
        
        Status = pBS->AllocatePool (EfiBootServicesData,
                          sizeof (DeviceName),
                          (VOID**)&tempUnicodeTable[0].UnicodeString
                          );

        if (EFI_ERROR(Status)) {
            return Status;
        }
                
        pBS->CopyMem(tempUnicodeTable[0].Language, &Language, sizeof(Language)); 
        pBS->CopyMem(tempUnicodeTable[0].UnicodeString, DeviceName, sizeof (DeviceName)); 
        tempUnicodeTable[1].Language = NULL;
        tempUnicodeTable[1].UnicodeString = NULL;
        ActiveNameSpaceData->UDeviceName = tempUnicodeTable;

        // First instance of zero marks the end of valid namespace IDs
        if (!NvmeController->ActiveNameSpaceIDs[i+1]) {
            break;
        }
    }

    return EFI_SUCCESS;
}

//**********************************************************************
//<AMI_PHDR_START>
//
// Procedure:   InstallBlockIoDiskInfo
//
// Description: Install BlockIo and DevicePath protocol for Active namespace
//
// Input:
// IN EFI_DRIVER_BINDING_PROTOCOL       *This,    
// IN AMI_NVME_CONTROLLER_PROTOCOL      *NvmeController
//
// Output:
//  EFI_STATUS
//
// Modified:
//      
// Referrals:  
//
// Notes:   
//
//<AMI_PHDR_END>
//**********************************************************************
EFI_STATUS
InstallBlockIoDiskInfo (
    IN EFI_DRIVER_BINDING_PROTOCOL     *This,    
    IN AMI_NVME_CONTROLLER_PROTOCOL    *NvmeController
)
{
    
    EFI_STATUS                  Status =  EFI_SUCCESS;
    ACTIVE_NAMESPACE_DATA       *ActiveNameSpace;
    EFI_LIST_ENTRY              *LinkData;
    EFI_BLOCK_IO_MEDIA          *BlkMedia;
    EFI_PCI_IO_PROTOCOL         *PciIO;
    UINT32                      BlockSize;
    UINTN                       AllocatePageSize;
    UINT8                       *Buffer;

    for (LinkData = NvmeController->ActiveNameSpaceList.ForwardLink; 
            LinkData != &NvmeController->ActiveNameSpaceList; 
            LinkData = LinkData->ForwardLink) {
        
        ActiveNameSpace = _CR(LinkData ,ACTIVE_NAMESPACE_DATA, Link);

        Status = pBS->AllocatePool (
                        EfiBootServicesData,
                        sizeof (EFI_BLOCK_IO_MEDIA),
                        (VOID**)&BlkMedia
                        );
        
        if (EFI_ERROR(Status)) return Status;
        
        pBS->SetMem(BlkMedia, sizeof(EFI_BLOCK_IO_MEDIA), 0);
        
        // PRP2List will be cleared when used
        AllocatePageSize = NvmeController->MemoryPageSize;
        Status = NvmeController->PciIO->AllocateBuffer (NvmeController->PciIO,
                                             AllocateAnyPages,
                                             EfiRuntimeServicesData,
                                             EFI_SIZE_TO_PAGES(AllocatePageSize),
                                             (VOID**)&ActiveNameSpace->PRP2List,
                                             EFI_PCI_IO_ATTRIBUTE_MEMORY_CACHED | EFI_PCI_IO_ATTRIBUTE_MEMORY_WRITE_COMBINE
                                             );
        
        if (EFI_ERROR(Status)) {
            return Status;
        }
        
        Status = NvmeController->PciIO->Map ( NvmeController->PciIO, 
                                        EfiPciIoOperationBusMasterCommonBuffer,
                                        (VOID *)ActiveNameSpace->PRP2List,
                                        &AllocatePageSize,
                                        &ActiveNameSpace->PRP2ListMappedAddr,
                                        &ActiveNameSpace->PRP2ListUnMap
                                        );
          
        if (EFI_ERROR(Status)) {
            return Status;
        }
        
        
        BlkMedia->MediaId = 0;
        BlkMedia->RemovableMedia = FALSE;
        BlkMedia->MediaPresent = TRUE;
        BlkMedia->LogicalPartition = FALSE;
        BlkMedia->ReadOnly = FALSE;
        BlkMedia->WriteCaching = FALSE;
        BlockSize =  ActiveNameSpace->IdentifyNamespaceData.LBAF[ActiveNameSpace->IdentifyNamespaceData.FLBAS & 0xF].LBADS;
        BlkMedia->BlockSize = (UINT32) Shl64(1, BlockSize);  
        BlkMedia->IoAlign = 2;      // NvmeController->MemoryPageSize;
        BlkMedia->LastBlock = (EFI_LBA) (ActiveNameSpace->IdentifyNamespaceData.NSIZE - 1);      // Name space Size
        BlkMedia->LowestAlignedLba = 0;
        BlkMedia->LogicalBlocksPerPhysicalBlock = 1;
        BlkMedia->OptimalTransferLengthGranularity = BlkMedia->BlockSize;
        
        ActiveNameSpace->NvmeBlockIO.Revision = EFI_BLOCK_IO_PROTOCOL_REVISION3;
        ActiveNameSpace->NvmeBlockIO.Media = BlkMedia;
        ActiveNameSpace->NvmeBlockIO.Reset = NvmeReset;
        ActiveNameSpace->NvmeBlockIO.ReadBlocks = NvmeReadBlocks;
        ActiveNameSpace->NvmeBlockIO.WriteBlocks = NvmeWriteBlocks;
        ActiveNameSpace->NvmeBlockIO.FlushBlocks = NvmeFlushBlocks;

        // DiskInfo Protocol 
        pBS->CopyMem (&(ActiveNameSpace->NvmeDiskInfo.Interface), &gEfiDiskInfoNvmeInterfaceGuid, sizeof (EFI_GUID));

        ActiveNameSpace->NvmeDiskInfo.Inquiry = NvmeDiskInfoInquiry;
        ActiveNameSpace->NvmeDiskInfo.Identify = NvmeDiskInfoIdentify;
        ActiveNameSpace->NvmeDiskInfo.SenseData = NvmeDiskInfoSenseData;
        ActiveNameSpace->NvmeDiskInfo.WhichIde = NvmeDiskInfoWhichIde;

        // Create DevicePath Protocol
        Status = CreateNvmeDevicePath (This, ActiveNameSpace);
        if (EFI_ERROR(Status)) {
            continue;
        }

        // Install Devicepath and Block IO protocol
        Status = pBS->InstallMultipleProtocolInterfaces (
                        &(ActiveNameSpace->NvmeDeviceHandle),              
                        &gEfiDevicePathProtocolGuid, ActiveNameSpace->EfiDevicePath,
                        &gEfiBlockIoProtocolGuid, &(ActiveNameSpace->NvmeBlockIO),                        
                        &gEfiDiskInfoProtocolGuid, &(ActiveNameSpace->NvmeDiskInfo),
                        NULL);
        
        if (EFI_ERROR(Status)) {
            continue;
        }
        
        // Open PCI IO protocol by CHILD
        Status = pBS->OpenProtocol (
                    NvmeController->ControllerHandle,
                    &gEfiPciIoProtocolGuid,
                    (VOID **)&PciIO,
                    This->DriverBindingHandle,     
                    ActiveNameSpace->NvmeDeviceHandle,   
                    EFI_OPEN_PROTOCOL_BY_CHILD_CONTROLLER);
        
        ASSERT_EFI_ERROR(Status);
        
        ActiveNameSpace->Configured = TRUE;
        
        // Check if the drive ready to return data

        Status = pBS->AllocatePages (
                            AllocateAnyPages,
                            EfiBootServicesData,
                            EFI_SIZE_TO_PAGES(ActiveNameSpace->NvmeBlockIO.Media->BlockSize),  
                            (EFI_PHYSICAL_ADDRESS*)&(Buffer));
        
        if (EFI_ERROR(Status)) {
            return Status;
        }
        

        Status = ReadBlock (NvmeController, ActiveNameSpace, Buffer);
        if (!EFI_ERROR(Status)) {
            // No error check for Int13 installation
        InstallNvmeLegacyDevice(NvmeController, ActiveNameSpace, Buffer);
        }
        
        pBS->FreePages((EFI_PHYSICAL_ADDRESS)Buffer, EFI_SIZE_TO_PAGES(ActiveNameSpace->NvmeBlockIO.Media->BlockSize));
    }

#if NvmeSmm_SUPPORT
    if( gLegacyNvmeBuffer == NULL ) {
        Status = pBS->AllocatePages (
                        AllocateAnyPages,
                        EfiReservedMemoryType,
                        EFI_SIZE_TO_PAGES(ActiveNameSpace->NvmeBlockIO.Media->BlockSize),
                        (EFI_PHYSICAL_ADDRESS*)&(gLegacyNvmeBuffer ));
        if (EFI_ERROR(Status)) {
            ASSERT_EFI_ERROR(Status);
            return Status;
        }
    }
    NvmeController->LegacyNvmeBuffer=gLegacyNvmeBuffer;

    // Move the Controller and ActiveName Space data into SMM also. 
    // This will done for each controller in the system
    TransferNvmeDataToSmram(NvmeController);
#endif

    return Status;
}

#if NvmeSmm_SUPPORT

//**********************************************************************
//<AMI_PHDR_START>
//
// Procedure:   TransferNvmeDataToSmram
//
// Description: Transfer the Nvme Controller information to SMRAM area that would be used
//              by the Nvme SMM driver
//
// Input:
// IN AMI_NVME_CONTROLLER_PROTOCOL    *NvmeController
//
// Output:
//  NONE
//
// Modified:
//      
// Referrals:  
//
// Notes:   
//
//<AMI_PHDR_END>
//**********************************************************************
VOID
TransferNvmeDataToSmram (
    IN  AMI_NVME_CONTROLLER_PROTOCOL    *NvmeController
)
{

    EFI_STATUS                          SmmStatus;
    UINTN                              NvmeControllerAddress = 0;
    static EFI_GUID                    gNvmeSmmGuid = NVME_SMM_GUID;

#if defined(PI_SPECIFICATION_VERSION) && (PI_SPECIFICATION_VERSION >= 0x00010014)  
    EFI_SMM_COMMUNICATION_PROTOCOL     *SmmCommunication;
    EFI_SMM_COMMUNICATE_HEADER         *CommHeader;
    UINT8                              CommBuffer[sizeof(EFI_GUID) + sizeof(UINTN) + sizeof(NvmeController)];
    UINTN                              CommSize = 0;

    // Get needed resource
    SmmStatus = pBS->LocateProtocol (
                    &gEfiSmmCommunicationProtocolGuid,
                    NULL,
                    (VOID **)&SmmCommunication
                    );

    ASSERT_EFI_ERROR (SmmStatus);

    if (EFI_ERROR (SmmStatus)) {
        return;
    }
    
    CommHeader = (EFI_SMM_COMMUNICATE_HEADER *)&CommBuffer[0];
    pBS->CopyMem (&CommHeader->HeaderGuid, &gAmiSmmNvmeCommunicationGuid, sizeof(gAmiSmmNvmeCommunicationGuid));
    CommHeader->MessageLength = sizeof(NvmeController);
    pBS->CopyMem (&(CommHeader->Data[0]), &NvmeController, sizeof(NvmeController));

    // Send command
    CommSize = sizeof(CommBuffer);
    SmmStatus = SmmCommunication->Communicate (
                                 SmmCommunication,
                                 &CommBuffer[0],
                                 &CommSize
                                 );
#else

    NvmeControllerAddress = (UINT64)(NvmeController);

    // Save ComBuffer in NvmeSmmBuffer to use in SMM
    SmmStatus = pRS->SetVariable ( L"NvmeSmmBuffer", 
                                    &gNvmeSmmGuid, 
                                    EFI_VARIABLE_BOOTSERVICE_ACCESS, 
                                    sizeof(UINTN), 
                                    &NvmeControllerAddress);

    TRACE((-1, "CommHeader Data inNvmeBus = %x\n", NvmeControllerAddress));

    IoWrite8 (SW_SMI_IO_ADDRESS, NVME_INIT_SMM_SWSMI);
#endif

    return;

}
#endif

//**********************************************************************
//<AMI_PHDR_START>
//
// Procedure:   CreateNVMeDevicePath
//
// Description: Allocate memory and create a NVMe devicepath
//
// Input:
// IN EFI_DRIVER_BINDING_PROTOCOL     *This,    
// IN AMI_NVME_CONTROLLER_PROTOCOL    *NvmeController
//
// Output:
//  EFI_STATUS
//
// Modified:
//      
// Referrals:  
//
// Notes:   
//
//<AMI_PHDR_END>
//**********************************************************************
EFI_STATUS
CreateNvmeDevicePath (
    IN EFI_DRIVER_BINDING_PROTOCOL     *This,    
    IN ACTIVE_NAMESPACE_DATA           *ActiveNameSpace
 )
{

    EFI_STATUS                          Status;
    IN AMI_NVME_CONTROLLER_PROTOCOL     *NvmeController = ActiveNameSpace->NvmeController;
    NVME_DEVICE_PATH                    NewDevicePath;
    EFI_DEVICE_PATH_PROTOCOL            *TempDevicePath;

    NewDevicePath.Header.Type = MESSAGING_DEVICE_PATH;
    NewDevicePath.Header.SubType = MSG_NVME_DP;
    SetDevicePathNodeLength(&(NewDevicePath.Header), sizeof(NVME_DEVICE_PATH));
    NewDevicePath.Nsid = ActiveNameSpace->ActiveNameSpaceID;
    NewDevicePath.EUI64 = ActiveNameSpace->IdentifyNamespaceData.EUI64;
    
    //
    // Append the Device Path
    //
    Status = pBS->OpenProtocol ( 
                    NvmeController->ControllerHandle,
                    &gEfiDevicePathProtocolGuid,
                    (VOID **)&TempDevicePath,
                    This->DriverBindingHandle,     
                    NvmeController->ControllerHandle,   
                    EFI_OPEN_PROTOCOL_GET_PROTOCOL);

    ActiveNameSpace->EfiDevicePath = DPAddNode(TempDevicePath, &NewDevicePath.Header);

    return Status;
}

//**********************************************************************
//<AMI_PHDR_START>
//
// Procedure:   DetectActiveNameSpace
//
// Description: Issue GetIdentifyData cmd to get the list of active name space. 
//
// Input:
//  IN AMI_NVME_CONTROLLER_PROTOCOL    *NvmeController,
//  IN OUT ACTIVE_NAMESPACE_DATA       *ActiveNameSpaceData
//
// Output:
//  EFI_STATUS
//
// Modified:
//      
// Referrals:  
//
// Notes:   
//
//<AMI_PHDR_END>
//**********************************************************************
EFI_STATUS
DetectActiveNameSpace (
    IN  AMI_NVME_CONTROLLER_PROTOCOL    *NvmeController,
    OUT ACTIVE_NAMESPACE_DATA           *ActiveNameSpaceData
)
{

    EFI_STATUS  Status;
    
    // Get list of Active NameSpace Data
    Status = GetIdentifyData (NvmeController, 
                        (UINT8*)&(ActiveNameSpaceData->IdentifyNamespaceData), 
                        0, 
                        ActiveNameSpaceData->ActiveNameSpaceID
                        );
    return Status;
            
}          

//**********************************************************************
//<AMI_PHDR_START>
//
// Procedure:   InstallNvmeLegacyDevice
//
// Description: Add the NVMe active partition as a legacy device 
//
// Input:
//  IN AMI_NVME_CONTROLLER_PROTOCOL    *NvmeController,
//  IN OUT ACTIVE_NAMESPACE_DATA       *ActiveNameSpaceData
//  IN  UINT8                          *Buffer
//
// Output:
//  NONE
//
// Modified:
//      
// Referrals:  
//
// Notes:   
//
//<AMI_PHDR_END>
//**********************************************************************

VOID
InstallNvmeLegacyDevice (
    IN  AMI_NVME_CONTROLLER_PROTOCOL    *NvmeController,
    IN  ACTIVE_NAMESPACE_DATA           *ActiveNameSpace,
    IN  UINT8                           *Buffer
)
{
	
    EFI_STATUS                      Status;
    AMI_NVME_LEGACY_PROTOCOL        *AmiNvmeLegacyProtocol = NULL;
    NVME_LEGACY_MASS_DEVICE         *NvmeLegacyMassDevice;
    NVME_MASS_DEV_INFO              *NvmeMassDevInfo;
    CHAR8                           *NewString;
    UINTN                           PciSeg, PciBus, PciDev, PciFunc;
    
    
    //If block size is not 512 do install INT13
    if (ActiveNameSpace->NvmeBlockIO.Media->BlockSize != 0x200) {
        return;
    }
    
    Status = pBS->LocateProtocol(&gAmiNvmeLegacyProtocolGuid, NULL, (VOID**)&AmiNvmeLegacyProtocol);
    // Legacy Support disabled. 
    if(EFI_ERROR(Status) || AmiNvmeLegacyProtocol == NULL ) {
        return;
    }
        
    Status = pBS->AllocatePool (
                        EfiBootServicesData,
                        sizeof (NVME_LEGACY_MASS_DEVICE),
                        (VOID**)&NvmeLegacyMassDevice
                        );

    if (EFI_ERROR(Status)){
        return;
    }
        

    Status = pBS->AllocatePool (
                        EfiBootServicesData,
                        sizeof (NVME_MASS_DEV_INFO),
                        (VOID**)&NvmeMassDevInfo
                        );

    if (EFI_ERROR(Status)){
        pBS->FreePool (NvmeLegacyMassDevice);
        return;
    }
        
    Status = pBS->AllocatePool(
                      EfiBootServicesData, 
                      256,
                      (VOID *) &NewString);
    ASSERT_EFI_ERROR (Status);
        
    // Read the first sector of the device
    ActiveNameSpace->dMaxLBA = ActiveNameSpace->NvmeBlockIO.Media->LastBlock;
    GetNvmeGeometryData(ActiveNameSpace, NvmeMassDevInfo, Buffer);
        
    NvmeMassDevInfo->wBlockSize=ActiveNameSpace->NvmeBlockIO.Media->BlockSize;
    NvmeMassDevInfo->dMaxLba=ActiveNameSpace->dMaxLBA;     
    NvmeMassDevInfo->bHeads=ActiveNameSpace->NumHeads;
    NvmeMassDevInfo->bSectors=ActiveNameSpace->NumSectors;
    NvmeMassDevInfo->wCylinders=ActiveNameSpace->NumCylinders;
    NvmeMassDevInfo->bNonLBAHeads=ActiveNameSpace->LBANumHeads;
    NvmeMassDevInfo->bNonLBASectors=ActiveNameSpace->LBANumSectors;
    NvmeMassDevInfo->wNonLBACylinders=ActiveNameSpace->LBANumCyls;

    PrintNvmeMassDevInfo (NvmeMassDevInfo);
        
    // Get the NVMe controller Bus,Dev and Fun
    NvmeController->PciIO->GetLocation (NvmeController->PciIO, &PciSeg, &PciBus, &PciDev, &PciFunc);
    UnicodeStrToAsciiStr (ActiveNameSpace->UDeviceName->UnicodeString, NewString);
        
    NvmeLegacyMassDevice->PciBDF=(UINT16)((PciBus << 8)+(PciDev << 3) + PciFunc);
    NvmeLegacyMassDevice->DevString=NewString;
    NvmeLegacyMassDevice->DevInfo=(VOID*)NvmeMassDevInfo;
    ActiveNameSpace->Int13DeviceAddress = gInt13DeviceAddress;
    NvmeLegacyMassDevice->LogicalAddress=ActiveNameSpace->Int13DeviceAddress;
    gInt13DeviceAddress++;
    NvmeLegacyMassDevice->StorageType = NVME_MASS_DEV_HDD;
    NvmeLegacyMassDevice->Handle=ActiveNameSpace->NvmeDeviceHandle;

    AmiNvmeLegacyProtocol->AddNvmeLegacyDevice(NvmeLegacyMassDevice);

    return;
}

//**********************************************************************
//<AMI_PHDR_START>
//
// Procedure:   GetNvmeGeometryData
//
// Description: Get drive geometry data for INT13 support 
//
// Input:
//    IN  OUT ACTIVE_NAMESPACE_DATA   *ActiveNameSpace,
//    IN  OUT NVME_MASS_DEV_INFO      *NvmeMassDevInfo,
//    IN  UINT8                       *Buffer
//
// Output:
//  EFI_STATUS
//
// Modified:
//      
// Referrals:  
//
// Notes:   
//
//<AMI_PHDR_END>
//**********************************************************************
EFI_STATUS
GetNvmeGeometryData (
    IN  OUT ACTIVE_NAMESPACE_DATA   *ActiveNameSpace,
    IN  OUT NVME_MASS_DEV_INFO      *NvmeMassDevInfo,
    IN  UINT8                       *Buffer
)
{
    
    EFI_STATUS  Status;
    UINT8       *ActPartAddr;
    UINT32      dHS;
    
    
    ActiveNameSpace->bStorageType = NVME_MASS_DEV_HDD;
    ActiveNameSpace->bEmuType = 0;
    
    ActiveNameSpace->bHiddenSectors = 0;
    //
    // Check for validity of Boot Record
    //
    if ( *(UINT16*)(Buffer + 0x1FE) != 0xAA55 ) {
        NvmeSetDefaultGeometry(ActiveNameSpace);
        return EFI_NOT_FOUND;
    }

    //
    // Check for validity of the partition table
    //
    if ( NvmeValidatePartitionTable( Buffer, ActiveNameSpace->dMaxLBA, &ActPartAddr) == EFI_SUCCESS ) {

        //
        // Read boot sector, set the LBA number to boot record LBA number
        //
        dHS = *((UINT32*)(ActPartAddr + 8));
        ActiveNameSpace->bHiddenSectors = (UINT8)dHS; // Save hidden sector value

        Status = NvmeReadWriteBlocks (ActiveNameSpace, ActiveNameSpace->NvmeBlockIO.Media->MediaId, (EFI_LBA)dHS, 512, Buffer, NULL, NVME_READ);

        if ( EFI_ERROR(Status) ) {  
            return EFI_NOT_FOUND;
        }

        if ( NvmeUpdateCHSFromBootRecord(ActiveNameSpace, Buffer) == EFI_SUCCESS) {
             return EFI_SUCCESS;
        } else {
            NvmeSetDefaultGeometry(ActiveNameSpace);
            ActiveNameSpace->bHiddenSectors = 0;      // Reset hidden sector value
            return EFI_SUCCESS;
        }
    }

    return EFI_SUCCESS;
}

//**********************************************************************
//<AMI_PHDR_START>
//
// Procedure:   NvmeSetDefaultGeometry
//
// Description: This procedure sets the  default geometry for mass storage devices
//
// Input:
//    IN  OUT ACTIVE_NAMESPACE_DATA   *ActiveNameSpace,
//
// Output:
//  EFI_STATUS
//
// Modified:
//      
// Referrals:  
//
// Notes:   
//
//<AMI_PHDR_END>
//**********************************************************************    
EFI_STATUS 
NvmeSetDefaultGeometry ( 
    IN  OUT ACTIVE_NAMESPACE_DATA   *ActiveNameSpace
)
{
    ActiveNameSpace->NumHeads = 0xFF;
    ActiveNameSpace->LBANumHeads = 0xFF;
    ActiveNameSpace->NumSectors = 0x3F;
    ActiveNameSpace->LBANumSectors = 0x3F;

    NvmeMassUpdateCylinderInfo(ActiveNameSpace);
    return EFI_SUCCESS;
}

//**********************************************************************
//<AMI_PHDR_START>
//
// Procedure:   NvmeMassUpdateCylinderInfo
//
// Description: This procedure updates cylinder parameter for device geometry.
//              head and sector parameters are required before invoking this
//              function.
//
// Input:
//    IN  OUT ACTIVE_NAMESPACE_DATA   *ActiveNameSpace,
//
// Output:
//  NONE
//
// Modified:
//      
// Referrals:  
//
// Notes:   
//
//<AMI_PHDR_END>
//**********************************************************************    
VOID
NvmeMassUpdateCylinderInfo (
    IN  OUT ACTIVE_NAMESPACE_DATA   *ActiveNameSpace
)
{
    UINT32 data = (UINT32)(Div64(ActiveNameSpace->dMaxLBA,(ActiveNameSpace->NumSectors * ActiveNameSpace->NumHeads), NULL));

    if (data <= 1) data++;
    if (data > 0x3FF) data = 0x3FF;   // DOS workaround

    ActiveNameSpace->NumCylinders = (UINT16)data;
    ActiveNameSpace->LBANumCyls = (UINT16)data;
    return;
}

//**********************************************************************
//<AMI_PHDR_START>
//
// Procedure:   NvmeValidatePartitionTable
//
// Description: This procedure checks whether the partition table is valid.
//
// Input:
//    IN  UINT8   *Buffer,
//    IN  UINT64  dMaxLBA,
//    OUT UINT8   **ActPartAddr
//
// Output:
//  EFI_STATUS
//
// Modified:
//      
// Referrals:  
//
// Notes:   
//
//<AMI_PHDR_END>
//********************************************************************** 
EFI_STATUS
NvmeValidatePartitionTable (
    IN  UINT8   *Buffer,
    IN  UINT64  dMaxLBA,
    OUT UINT8   **ActPartAddr
)
{

    UINT8   *PartPtr;
    UINT8   PartNo = 0;
    UINT8   *ActPart = NULL;
    UINT8   ValidEntryCount = 0;

    //
    // Drive has a partition table, start from 1st bootable partition
    //
    PartPtr = Buffer + 0x1BE;

    for (; PartNo<4; PartNo++, PartPtr+=0x10 ) {

        if (*PartPtr & 0x7F ) { 
            return EFI_NOT_FOUND; //BootFlag should be 0x0 or 0x80
        }
        //
        // Check whether beginning LBA is reasonable
        //
        if (*(UINT32*)(PartPtr + 8) > dMaxLBA) { 
            return EFI_NOT_FOUND;
        }
        
        ValidEntryCount++;                      // Update valid entry count
        //
        // Update active entry offset
        //
        if (!(*PartPtr & 0x80)) continue;
        if (ActPart) continue;
        ActPart = PartPtr;
    }

    if (ValidEntryCount < 1) return EFI_NOT_FOUND; // At least one valid partition is found
    //
    // If no active partition table entry found use first entry
    //
    if (ActPart == NULL) ActPart = Buffer + 0x1BE;

    *ActPartAddr = ActPart;

    return EFI_SUCCESS;

}

//**********************************************************************
//<AMI_PHDR_START>
//
// Procedure:   NvmeUpdateCHSFromBootRecord
//
// Description: This function parses the boot record and extract the CHS
//              information of the formatted media from the boot record.
//              This routine checks for DOS & NTFS formats only
//
// Input:
//    IN  OUT ACTIVE_NAMESPACE_DATA   *ActiveNameSpace,
//    IN  UINT8*                      BootRecord
//
// Output:
//  EFI_STATUS
//
// Modified:
//      
// Referrals:  
//
// Notes:   The amount of data that will get printed can be controlled 
//          using DEBUG_ERROR_LEVEL_MASK SDL token. Make sure 
//          PcdDebugPrintErrorLevel is properly cloned and set to 
//          PcdsPatchableInModule in the project.
//
//<AMI_PHDR_END>
//********************************************************************** 
EFI_STATUS
NvmeUpdateCHSFromBootRecord (
    IN  OUT ACTIVE_NAMESPACE_DATA   *ActiveNameSpace,
    IN  UINT8*                      BootRecord
)
{
    UINT32      OemName;
    UINT8       Heads;
    UINT8       SecPerTrack;
    UINT16      SecTimesHeads;
    UINT16      TotalSect;

    if (*((UINT16*)(BootRecord + 0x1FE)) != 0xAA55) { 
        return EFI_NOT_FOUND;
    }

    //
    // Read succeeded so the drive is formatted
    // Check for valid MSDOS/MSWIN/NTFS boot record
    //
    OemName = *(UINT32*)(BootRecord + 3);
    
    if ((OemName != 0x4F44534D) &&   // 'ODSM' for MSDO
        (OemName != 0x4957534D) &&   // 'IWSM' for MSWI
        (OemName != 0x5346544E)) {   // 'SFTN' for NTFS
        //
        // Check for valid FAT,FAT16,FAT32 boot records
        //
        *(BootRecord + 0x36 + 3) = 0x20;              // Ignore the 4th byte and fill it with space
        if ((*(UINT32*)(BootRecord + 0x36) != 0x20544146) &&      // " TAF" for FATx
            (*(UINT32*)(BootRecord + 0x52) != 0x33544146)) {      // "3TAF" for FAT3
            //
            // Boot Record is invalid. Return with error
            //
            return EFI_NOT_FOUND;
        }
    }

    Heads = *(BootRecord + 0x1A);         // Number of heads
    SecPerTrack = *(BootRecord + 0x18);   // Sectors/track
    SecTimesHeads = Heads * SecPerTrack;

    // Zero check added to prevent invalid sector/head information in BPB
    if (SecTimesHeads == 0) {
        return EFI_NOT_FOUND;
    }

    TotalSect = *(UINT16*)(BootRecord + 0x13);
    if ( TotalSect ) {
        ActiveNameSpace->dMaxLBA = TotalSect;
    }

    ActiveNameSpace->NumHeads = Heads;
    ActiveNameSpace->LBANumHeads = Heads;
    ActiveNameSpace->NumSectors = SecPerTrack;
    ActiveNameSpace->LBANumSectors = SecPerTrack;


    NvmeMassUpdateCylinderInfo(ActiveNameSpace);

    return  EFI_SUCCESS;
}
            
//**********************************************************************
//<AMI_PHDR_START>
//
// Procedure:   PrintIdentifyDataStructure
//
// Description: Prints Identify data structure
//
// Input:
//  UINT8       *IdentifyData, 
//  UINT8       ControllerNameSpaceStructure
//
// Output:
//  None
//
// Modified:
//      
// Referrals: 
//
//<AMI_PHDR_END>
//**********************************************************************
VOID
PrintIdentifyDataStructure (
    IN UINT8       *IdentifyData, 
    IN UINT8       ControllerNameSpaceStructure
)
{

	
#if  NVME_VERBOSE_PRINT
    
    IDENTIFY_CONTROLLER_DATA    *IdentifyControllerData = (IDENTIFY_CONTROLLER_DATA *)IdentifyData;
    IDENTIFY_NAMESPACE_DATA     *IdentifyNameSpaceData = (IDENTIFY_NAMESPACE_DATA *)IdentifyData;
    UINT32                      *ActiveNameSapceID = (UINT32 *)IdentifyData;
    UINT32                      i;
    UINT64                      FirmwareVersion;
    
    switch (ControllerNameSpaceStructure){
    
        case 1:
            
            FirmwareVersion = *(UINT64 *)(IdentifyControllerData->FirmwareRevision);
            TRACE((-1,"\nIdentify Controller Data Structure\n"));
            TRACE((-1, "Vendor ID                                 : %08X\n", IdentifyControllerData->VID));
            TRACE((-1, "SubSystem Vendor ID                       : %08X\n", IdentifyControllerData->SSVID));
            TRACE((-1, "Firmware Version                          : %16lX\n", FirmwareVersion));
            TRACE((-1, "NameSpace Sharing Capability              : %08X\n", IdentifyControllerData->CMIC));
            TRACE((-1,   "Max. Data Transfer Size                   : %08X\n", IdentifyControllerData->MDTS));
            TRACE((-1,   "Controller ID                             : %08X\n", IdentifyControllerData->ControllerID));
            TRACE((-1, "Optional Admin Cmd Support                : %08X\n", IdentifyControllerData->OACS));
            TRACE((-1, "Abort Command Limit                       : %08X\n", IdentifyControllerData->ACL));
            TRACE((-1, "Asyn. Event Request Limit                 : %08X\n", IdentifyControllerData->AERL));
            TRACE((-1, "Firmware Updates                          : %08X\n", IdentifyControllerData->FRMW));
            TRACE((-1, "Log Page Attribute                        : %08X\n", IdentifyControllerData->LPA));
            TRACE((-1, "# of Power state supported                : %08X\n", IdentifyControllerData->NPSS));
            TRACE((-1, "Admin Vendor Specific cmd                 : %08X\n", IdentifyControllerData->AVSCC));
            TRACE((-1, "Autonomous Power state attrib             : %08X\n", IdentifyControllerData->APSTA));
            TRACE((-1,   "Submission queue Entry Size               : %08X\n", IdentifyControllerData->SQES));
            TRACE((-1,   "Completion queue Entry Size               : %08X\n", IdentifyControllerData->CQES));
            TRACE((-1,   "Number of NameSpace                       : %08X\n", IdentifyControllerData->NN));
            TRACE((-1, "Optional NVM Command Support              : %08X\n", IdentifyControllerData->ONCS));
            TRACE((-1, "Fused Operation Support                   : %08X\n", IdentifyControllerData->FUSES));
            TRACE((-1, "Format NVM Attribute                      : %08X\n", IdentifyControllerData->FNA));
            TRACE((-1, "Volatile Write Cache                      : %08X\n", IdentifyControllerData->VWC));
            TRACE((-1, "Atomic Write Unit Normal                  : %08X\n", IdentifyControllerData->AWUN));
            TRACE((-1, "Atomic Write Unit Power Fail              : %08X\n", IdentifyControllerData->AWUPF));
            TRACE((-1, "NVM VS CMD Config                         : %08X\n", IdentifyControllerData->NVSCC));
            TRACE((-1, "Atomic Compare & Write Unit               : %08X\n", IdentifyControllerData->ACWU));
            TRACE((-1,   "SGL Support                               : %08X\n", IdentifyControllerData->SGLS));
            break;
            
        case 0:
            TRACE((-1, "\nIdentify NameSpace Data Structure\n"));
            TRACE((-1,  "NameSpace Size                             : %08X\n", IdentifyNameSpaceData->NSIZE));
            TRACE((-1,  "NameSpace Capacity                         : %08X\n", IdentifyNameSpaceData->NCAP));
            TRACE((-1,  "NameSpace Utilization                      : %08X\n", IdentifyNameSpaceData->NUSE));
            TRACE((-1,  "NameSpace Features                         : %08X\n", IdentifyNameSpaceData->NSFEAT));
            TRACE((-1,  "No. of LBA Formats (0 Based)               : %08X\n", IdentifyNameSpaceData->NLBAF));
            TRACE((-1,  "Formatted LBA Size                         : %08X\n", IdentifyNameSpaceData->FLBAS));
            TRACE((-1,  "Metadata Capabilities                      : %08X\n", IdentifyNameSpaceData->MC));
            TRACE((-1,  "End-to-end data Protection cap             : %08X\n", IdentifyNameSpaceData->DPC));
            TRACE((-1,  "End-to-end data Protection settings        : %08X\n", IdentifyNameSpaceData->DPS));
            TRACE((-1,  "NameSpace Sharing                          : %08X\n", IdentifyNameSpaceData->NMIC));
            TRACE((-1,  "Reservation Capabilites                    : %08X\n", IdentifyNameSpaceData->RESCAP));
            TRACE((-1,  "IEEE Extended Unique Identifier            : %016lx\n", IdentifyNameSpaceData->EUI64));
            for (i=0; i<16; i++){
                TRACE((-1, "LBA Format %02X Support                  : %08X\n", i, *(UINT32 *)&(IdentifyNameSpaceData->LBAF[i])));
            }
            break;
            
        case 2:
            TRACE((-1,"\nActive NameSpace IDs\n"));
            for (i=0; i<1024 && ActiveNameSapceID[i]; i++){
                TRACE((-1, "    %08X\n", i, ActiveNameSapceID[i]));
            }    
            
    }
#endif   
}

//**********************************************************************
//<AMI_PHDR_START>
//
// Procedure:   PrintNvmeCapability
//
// Description: Prints Controller capabilities
//
// Input:
//  IN AMI_NVME_CONTROLLER_PROTOCOL        *NvmeController
//
// Output:
//  None
//
// Modified:
//      
// Referrals: 
//
// Notes:  The amount of data that will get printed can be controlled using DEBUG_ERROR_LEVEL_MASK SDL token.
//  Make sure PcdDebugPrintErrorLevel is properly cloned and set to PcdsPatchableInModule in the project.
//
//<AMI_PHDR_END>
//**********************************************************************
VOID
PrintNvmeCapability (
    IN AMI_NVME_CONTROLLER_PROTOCOL        *NvmeController
)
{
    
#if  NVME_VERBOSE_PRINT
    TRACE ((-1,   "Controller Capabilitites Reg Value       : %16lx\n", NvmeController->RawControllerCapabilities));
    TRACE ((-1, "Max. Queue Entrys Supported              : %08X\n", NvmeController->MaxQueueEntrySupported));
    TRACE ((-1, "Contiguous Queue Required                : %08X\n", NvmeController->ContiguousQueueRequired));
    TRACE ((-1, "Arbitration Mode Supported               : %08X\n", NvmeController->ArbitrationMechanismSupport));
    TRACE ((-1, "TimeOut in 500msec unit                  : %08X\n", NvmeController->TimeOut));
    TRACE ((-1, "Doorbell Stride                          : %08X\n", NvmeController->DoorBellStride));
    TRACE ((-1, "NVM Subsystem Reset Support              : %08X\n", NvmeController->NVMResetSupport));
    TRACE ((-1, "Command Sets Supported                   : %08X\n", NvmeController->CmdSetsSupported));
    TRACE ((-1, "Memory Page Size Min.in Bytes            : %08X\n", NvmeController->MemoryPageSizeMin));
    TRACE ((-1, "Memory Page Size Max.in Bytes            : %08X\n", NvmeController->MemoryPageSizeMax));
#endif
    
}

//**********************************************************************
//<AMI_PHDR_START>
//
// Procedure:   ReadBlock
//
// Description: Read the Data from device 
//
// Input:
//              AMI_NVME_CONTROLLER_PROTOCOL    *NvmeController,
//              ACTIVE_NAMESPACE_DATA       *ActiveNameSpace
//
// Output:
//  None
//
// Modified:
//      
// Referrals: 
//
//
//<AMI_PHDR_END>
//**********************************************************************
EFI_STATUS
ReadBlock (
    IN AMI_NVME_CONTROLLER_PROTOCOL    *NvmeController,
    IN ACTIVE_NAMESPACE_DATA           *ActiveNameSpace,
    OUT UINT8                           *Buffer

)
{
    
    EFI_STATUS              Status;
    NVME_COMMAND_WRAPPER    *NvmeCmdWrapper = NvmeController->NvmeCmdWrapper;
    COMPLETION_QUEUE_ENTRY  CompletionData;
    UINT64                  DataAddress = (UINTN)Buffer;
    UINT32                  LBANumber = 0;
    UINT32                  Retries = 0x800;
    
    do { 
    
        // Clear memory
        pBS->SetMem(NvmeCmdWrapper, sizeof(NVME_COMMAND_WRAPPER), 0);
        
        // Build NVME command
        NvmeCmdWrapper->NvmCmd.CMD0.Opcode = NVME_READ;
        NvmeCmdWrapper->NvmCmd.CMD0.FusedOperation = 0;
        NvmeCmdWrapper->NvmCmd.CMD0.PSDT = 0;
        NvmeCmdWrapper->NvmCmd.CMD0.CommandIdentifier = NvmeController->CommandIdentifierQueue1;
        NvmeCmdWrapper->NvmCmd.NSID = 1;
                
        NvmeCmdWrapper->NvmCmd.MPTR = 0;
        NvmeCmdWrapper->NvmCmd.PRP1 = DataAddress;
        NvmeCmdWrapper->NvmCmd.PRP2 = 0;
        NvmeCmdWrapper->NvmCmd.CDW10 = LBANumber;       // LBA 0
        NvmeCmdWrapper->NvmCmd.CDW11 = 0;           
        NvmeCmdWrapper->NvmCmd.CDW12 = 0x80000000;           
        NvmeCmdWrapper->NvmCmd.CDW13 = 0;           
        NvmeCmdWrapper->NvmCmd.CDW14 = 0;           
        
        NvmeCmdWrapper->AdminOrNVMCmdSet = FALSE;
        NvmeCmdWrapper->SQIdentifier = 1;           // Cmd issued in Queue0
        NvmeCmdWrapper->CmdTimeOut = 1000;
        
        Status = ExecuteNvmeCmd (NvmeController, NvmeCmdWrapper, &CompletionData);
        
    } while (Retries-- && Status != EFI_SUCCESS);
    
    return Status;
}
//**********************************************************************
//<AMI_PHDR_START>
//
// Procedure:   NvmeReadBlocks
//
// Description: Reads data from the given LBA address
//
// Input:
//    IN  EFI_BLOCK_IO_PROTOCOL   *This,
//    IN  UINT32                  MediaId,
//    IN  EFI_LBA                 LBA,
//    IN  UINTN                   BufferSize,
//    OUT VOID                    *Buffer
//
// Output:
//  None
//
// Modified:
//      
// Referrals: 
//
//
//<AMI_PHDR_END>
//**********************************************************************

EFI_STATUS
NvmeReadBlocks (
    IN  EFI_BLOCK_IO_PROTOCOL   *This,
    IN  UINT32                  MediaId,
    IN  EFI_LBA                 LBA,
    IN  UINTN                   BufferSize,
    OUT VOID                    *Buffer
)
{
    
    ACTIVE_NAMESPACE_DATA           *ActiveNameSpace = ACTIVE_NAMESPACE_DATA_FROM_THIS(This);
    
    return NvmeReadWriteBlocks (ActiveNameSpace, MediaId, LBA, BufferSize, Buffer, NULL, NVME_READ);
    
}
//**********************************************************************
//<AMI_PHDR_START>
//
// Procedure:   NvmeWriteBlocks
//
// Description:  Write data from the given LBA address
//
// Input:
//    IN  EFI_BLOCK_IO_PROTOCOL   *This,
//    IN  UINT32                  MediaId,
//    IN  EFI_LBA                 LBA,
//    IN  UINTN                   BufferSize,
//    OUT VOID                    *Buffer
//
// Output:
//      EFI_STATUS
//
// Modified:
//      
// Referrals: 
//
//
//<AMI_PHDR_END>
//**********************************************************************

EFI_STATUS
NvmeWriteBlocks (
    IN  EFI_BLOCK_IO_PROTOCOL   *This,
    IN  UINT32                  MediaId,
    IN  EFI_LBA                 LBA,
    IN  UINTN                   BufferSize,
    OUT VOID                    *Buffer
)
{
   
    ACTIVE_NAMESPACE_DATA           *ActiveNameSpace = ACTIVE_NAMESPACE_DATA_FROM_THIS(This);
    
    return NvmeReadWriteBlocks (ActiveNameSpace, MediaId, LBA, BufferSize, Buffer, NULL, NVME_WRITE);
    
}
//**********************************************************************
//<AMI_PHDR_START>
//
// Procedure:   NvmeReset
//
// Description: Resets Nvme Controller
//
// Input:
//      IN  EFI_BLOCK_IO_PROTOCOL   *This,
//      IN  BOOLEAN                 ExtendedVerification
//
// Output:
//  None
//
// Modified:
//      
// Referrals: 
//
//
//<AMI_PHDR_END>
//**********************************************************************

EFI_STATUS
NvmeReset (
    IN  EFI_BLOCK_IO_PROTOCOL   *This,
    IN  BOOLEAN                 ExtendedVerification
)
{
    
    EFI_STATUS  Status = EFI_SUCCESS;
    
    return Status;
}
//**********************************************************************
//<AMI_PHDR_START>
//
// Procedure:   NvmeFlushBlocks
//
// Description: Flushes the data 
//
// Input:
//     IN  EFI_BLOCK_IO_PROTOCOL   *This
//
// Output:
//      EFI_STATUS
//
// Modified:
//      
// Referrals: 
//
//
//<AMI_PHDR_END>
//**********************************************************************

EFI_STATUS
NvmeFlushBlocks (
    IN  EFI_BLOCK_IO_PROTOCOL   *This
)
{
    
    EFI_STATUS                      Status;
    ACTIVE_NAMESPACE_DATA           *ActiveNameSpace = ACTIVE_NAMESPACE_DATA_FROM_THIS(This);
    AMI_NVME_CONTROLLER_PROTOCOL    *NvmeController = ActiveNameSpace->NvmeController;
    NVME_COMMAND_WRAPPER            *NvmeCmdWrapper = NvmeController->NvmeCmdWrapper;
    COMPLETION_QUEUE_ENTRY          CompletionData;
    
    TRACE((-1,"NvmeFlushBlocks \n"));

    pBS->SetMem(NvmeCmdWrapper, sizeof(NVME_COMMAND_WRAPPER), 0); 
    
    // Build NVME command
    NvmeCmdWrapper->NvmCmd.CMD0.Opcode = NVME_FLUSH;
    NvmeCmdWrapper->NvmCmd.CMD0.FusedOperation = 0;
    NvmeCmdWrapper->NvmCmd.CMD0.PSDT = 0;
    NvmeCmdWrapper->NvmCmd.CMD0.CommandIdentifier = NvmeController->CommandIdentifierQueue1;
    NvmeCmdWrapper->NvmCmd.NSID = ActiveNameSpace->ActiveNameSpaceID;
        
    NvmeCmdWrapper->AdminOrNVMCmdSet = FALSE;
    NvmeCmdWrapper->SQIdentifier = NvmeController->NVMQueueNumber;
    NvmeCmdWrapper->CmdTimeOut = 1000;      // 1secs
    
    Status = ExecuteNvmeCmd (NvmeController, NvmeCmdWrapper, &CompletionData);
    
    TRACE((-1,"NvmeFlushBlocks Status %r \n", Status));
    
    return Status;
    
}
//**********************************************************************
//<AMI_PHDR_START>
//
// Procedure:   NvmeDiskInfoInquiry
//
// Description:  Return Nvme device Inquiry data
//
// Input:
//     IN  EFI_DISK_INFO_PROTOCOL   *This
//     IN  VOID                   *InquiryData,
//     IN  UINT32                 *InquiryDataSize
// Output:
//       EFI_STATUS /EFI_NOT_FOUND
//
// Modified:
//      
// Referrals: 
//
//
//<AMI_PHDR_END>
//**********************************************************************

EFI_STATUS
NvmeDiskInfoInquiry (
    IN EFI_DISK_INFO_PROTOCOL    *This,
    IN OUT VOID                  *InquiryData,
    IN OUT UINT32                *InquiryDataSize
)
{

    return EFI_NOT_FOUND;
}

//**********************************************************************
//<AMI_PHDR_START>
//
// Procedure:   NvmeDiskInfoIdentify
//
// Description:   Return Identify Data
//
// Input:
//     IN  EFI_DISK_INFO_PROTOCOL   *This
//     IN  VOID                   *IdentifyData,
//     IN  UINT32                 *IdentifyDataSize
// Output:
//       EFI_STATUS
// Note:
//    Return the Nvme device Identify command data.
// Modified:
//      
// Referrals: 
//
//
//<AMI_PHDR_END>
//**********************************************************************

EFI_STATUS
NvmeDiskInfoIdentify (
    EFI_DISK_INFO_PROTOCOL    *This,
    IN OUT VOID               *IdentifyData,
    IN OUT UINT32             *IdentifyDataSize
)
{
    ACTIVE_NAMESPACE_DATA       *ActiveNameSpace = ACTIVE_NAMESPACE_DATA_FROM_THIS_FOR_DISKINFO(This);

    if (*IdentifyDataSize < sizeof (IDENTIFY_NAMESPACE_DATA)) {
        *IdentifyDataSize = sizeof (IDENTIFY_NAMESPACE_DATA);
        return EFI_BUFFER_TOO_SMALL;
    }

    pBS->CopyMem (IdentifyData, &(ActiveNameSpace->IdentifyNamespaceData), sizeof (IDENTIFY_NAMESPACE_DATA)); 
    *IdentifyDataSize =  sizeof (IDENTIFY_NAMESPACE_DATA);
    return EFI_SUCCESS;
}

//**********************************************************************
//<AMI_PHDR_START>
//
// Procedure:   NvmeDiskInfoSenseData
//
// Description:     Return InfoSenseData.
//
// Input:
//     IN  EFI_DISK_INFO_PROTOCOL   *This
//     IN  VOID                     *SenseData,
//     IN  UINT32                   *SenseDataSize
//     IN  UINT8                    *SenseDataNumber
// Output:
//       EFI_STATUS / EFI_NOT_FOUND
// Modified:
//      
// Referrals: 
//
//
//<AMI_PHDR_END>
//**********************************************************************

EFI_STATUS
NvmeDiskInfoSenseData (
    IN EFI_DISK_INFO_PROTOCOL    *This,
    OUT VOID                     *SenseData,
    OUT UINT32                   *SenseDataSize,
    OUT UINT8                    *SenseDataNumber
)
{
    return EFI_NOT_FOUND;
}

//**********************************************************************
//<AMI_PHDR_START>
//
// Procedure:   NvmeDiskInfoWhichIde
//
// Description: Returns info about where the device is connected.
//
// Input:
//     IN  EFI_DISK_INFO_PROTOCOL   *This
//     IN  UINT32                   *IdeChannel 
//     IN  UINT32                   *IdeDevice
// Output:
//       EFI_STATUS
// Note:
//   Return Port and PMPort
// Modified:
//      
// Referrals: 
//
//
//<AMI_PHDR_END>
//**********************************************************************

EFI_STATUS
NvmeDiskInfoWhichIde (
    IN EFI_DISK_INFO_PROTOCOL    *This,
    OUT UINT32                   *IdeChannel,
    OUT UINT32                   *IdeDevice
)
{

    ACTIVE_NAMESPACE_DATA    *ActiveNameSpace = ACTIVE_NAMESPACE_DATA_FROM_THIS_FOR_DISKINFO(This);

    *IdeChannel = ActiveNameSpace->ActiveNameSpaceID; 
    *IdeDevice = 0;
    return EFI_SUCCESS;
}


//**********************************************************************
//<AMI_PHDR_START>
//
// Procedure:   PrintNvmeMassDevInfo
//
// Description: Prints Nvme Mass Device Information 
//
// Input:
//    NVME_MASS_DEV_INFO              *NvmeMassDevInfo
//
// Output:
//  None
//
// Modified:
//      
// Referrals: 
//
//
//<AMI_PHDR_END>
//**********************************************************************
VOID
PrintNvmeMassDevInfo (
    NVME_MASS_DEV_INFO              *NvmeMassDevInfo
)
{
    
#if  NVME_VERBOSE_PRINT    
    TRACE((-1,"********** NvmeMassDevInfo **********\n"));
    TRACE((-1, "wBlockSize                                  : %08X\n", NvmeMassDevInfo->wBlockSize));
    TRACE((-1, "dMaxLba                                     : %lX\n",  NvmeMassDevInfo->dMaxLba));
    TRACE((-1, "bHeads                                      : %08X\n", NvmeMassDevInfo->bHeads));
    TRACE((-1, "bSectors                                    : %08X\n", NvmeMassDevInfo->bSectors));
    TRACE((-1, "wCylinders                                  : %08X\n", NvmeMassDevInfo->wCylinders));
    TRACE((-1, "bNonLBAHeads                                : %08X\n", NvmeMassDevInfo->bNonLBAHeads));
    TRACE((-1, "bNonLBASectors                              : %08X\n", NvmeMassDevInfo->bNonLBASectors));
    TRACE((-1, "wNonLBACylinders                            : %08X\n", NvmeMassDevInfo->wNonLBACylinders));
#endif  
    
}


//**********************************************************************
//**********************************************************************
//**                                                                  **
//**        (C)Copyright 1985-2016, American Megatrends, Inc.         **
//**                                                                  **
//**                       All Rights Reserved.                       **
//**                                                                  **
//**         5555 Oakbrook Pkwy, Suite 200, Norcross, GA 30093        **
//**                                                                  **
//**                       Phone: (770)-246-8600                      **
//**                                                                  **
//**********************************************************************
//**********************************************************************
