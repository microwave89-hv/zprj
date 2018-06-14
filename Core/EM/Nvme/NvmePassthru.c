//**********************************************************************
//**********************************************************************
//**                                                                  **
//**        (C)Copyright 1985-2015, American Megatrends, Inc.         **
//**                                                                  **
//**                       All Rights Reserved.                       **
//**                                                                  **
//**         5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093     **
//**                                                                  **
//**                       Phone: (770)-246-8600                      **
//**                                                                  **
//**********************************************************************
//**********************************************************************
//**********************************************************************
// $Header: /Alaska/SOURCE/Modules/NVMe/NvmePassthru.c 1     5/14/15 2:36a Karthikar $
//
// $Revision: 1 $ 
//
// $Date: 5/14/15 2:36a $ 
//**********************************************************************
//**********************************************************************
//<AMI_FHDR_START>
//
// Name:        NvmePassthru.c
//
// Description: Contain Nvme Express passthru protocol APIs definition 
//
//<AMI_FHDR_END>
//**********************************************************************

#include "NvmeIncludes.h"
#include "NvmeController.h"
#include "NvmeBus.h"
#include "Protocol/AmiNvmeController.h"
#include "NvmePassthru.h"
#include <Protocol\DevicePath.h>
#include <Protocol\BlockIo.h>

// Global Declaration
EFI_BOOT_SERVICES *pBS;

//<AMI_PHDR_START>
//----------------------------------------------------------------------
// Procedure: GetActiveNameSpace
//
// Description:  
//  Routine to get the Active NameSpace
//
// Input: 
//   IN AMI_NVME_CONTROLLER_PROTOCOL   *NvmeController     
//   IN UINT32                         NamespaceId
// Output: 
//      ACTIVE_NAMESPACE_DATA pointer for the NamespaceId
//
// Modified:  
//
// Referrals: 
//
// Notes:
//
//----------------------------------------------------------------------
//<AMI_PHDR_END> 

ACTIVE_NAMESPACE_DATA*
GetActiveNameSpace (
    AMI_NVME_CONTROLLER_PROTOCOL   *NvmeController,
    UINT32                         NamespaceId
)
{
    LIST_ENTRY            *LinkData;
    ACTIVE_NAMESPACE_DATA *ActiveNameSpace = NULL;
    
    if(!NvmeController) {
        return NULL;
    }

    for (LinkData = NvmeController->ActiveNameSpaceList.ForwardLink; 
            LinkData != &NvmeController->ActiveNameSpaceList; 
            LinkData = LinkData->ForwardLink) {

        ActiveNameSpace = _CR(LinkData, ACTIVE_NAMESPACE_DATA, Link);

        if(ActiveNameSpace->ActiveNameSpaceID == NamespaceId) {
            return ActiveNameSpace;
        }
    }
    return NULL;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------
// Procedure: NvmePassThru
//
// Description:  
//  Sends an NVM Express Command Packet to an NVM Express controller or namespace
//
// Input: 
//   IN    This         A pointer to the EFI_NVM_EXPRESS_PASS_THRU_PROTOCOL instance
//   IN    NamespaceId  A 32 bit namespace ID as defined in the NVMe specification 
//                        to which the NVM Express Command Packet will be sent.  
//   IN    Packet       A pointer to the NVM Express Command Packet to send to
//                        the NVMe namespace specified by NamespaceId. 
//   IN    Event        Event to be signaled when the NVM Express Command Packet completes
//                        and non-blocking I/O is supported
// Output: 
//   EFI_STATUS
//
// Modified:  
//
// Referrals: 
//
// Notes:
//
//----------------------------------------------------------------------
//<AMI_PHDR_END> 

EFI_STATUS 
NvmePassThru ( 
    IN EFI_NVM_EXPRESS_PASS_THRU_PROTOCOL            *This,
    IN UINT32                                        NamespaceId,
    IN OUT EFI_NVM_EXPRESS_PASS_THRU_COMMAND_PACKET  *Packet,
    IN EFI_EVENT                                     Event
)
{
    EFI_STATUS                    Status;
    ACTIVE_NAMESPACE_DATA         *ActiveNameSpace = NULL;
    NVME_COMMAND_WRAPPER          *NvmeCmdWrapper = NULL;
    AMI_NVME_CONTROLLER_PROTOCOL  *NvmeController;
    UINT32                        AlignmentBoundry;
    VOID                          *BufferUnMap = NULL;
    COMPLETION_QUEUE_ENTRY        *NvmeCompletionData = NULL;
    UINT8                         NvmeOpcode;
    UINT64                        LBA;

    if( !This || !Packet || !Packet->NvmeCmd ) {
        return EFI_INVALID_PARAMETER;
    }

    NvmeOpcode = Packet->NvmeCmd->Cdw0.OpCode;

    // Return if QueueType is invalid
    if (Packet->QueueType != NVME_ADMIN_SUBMISSION_QUEUE && Packet->QueueType != NVME_IO_SUBMISSION_QUEUE) {
        return EFI_INVALID_PARAMETER;
    }

    // Check Transfer buffer is NULL, if not,Check its memory is properly alligned or not
    if( Packet->TransferBuffer && ( This->Mode->IoAlign > 1 ) ) {

        // Should be align in 2's power
        AlignmentBoundry = 1 << This->Mode->IoAlign;
        //
        //Get what is the number in 2 to the power Mode->IoAlign 
        //       
        if((0 !=  ((UINTN)((UINTN)(Packet->TransferBuffer) % AlignmentBoundry) ) ||
           (0 !=  ((UINTN)( Packet->TransferLength % AlignmentBoundry))) )) {
            return EFI_INVALID_PARAMETER;
        }
    }

    NvmeController = NVME_CONTROLLER_PROTOCOL_FROM_THIS(This);

    if(!Packet->NvmeCompletion) {
        return EFI_INVALID_PARAMETER;
    }

    NvmeCompletionData = (COMPLETION_QUEUE_ENTRY*)Packet->NvmeCompletion;

    Status = pBS->AllocatePool (
                  EfiBootServicesData,
                  sizeof(NVME_COMMAND_WRAPPER),
                  (VOID**)&NvmeCmdWrapper
                  );

    if (EFI_ERROR(Status)) {
        return Status;
    }
    // Clear memory
    pBS->SetMem(NvmeCmdWrapper, sizeof(NVME_COMMAND_WRAPPER), 0);
    
    // Fill Common values of command
    NvmeCmdWrapper->NvmCmd.CMD0.Opcode = NvmeOpcode;
    (UINT8)NvmeCmdWrapper->NvmCmd.CMD0.FusedOperation = Packet->NvmeCmd->Cdw0.FusedOperation;
    NvmeCmdWrapper->NvmCmd.CMD0.CommandIdentifier = Packet->QueueType?  NvmeController->CommandIdentifierQueue1 : NvmeController->CommandIdentifierAdmin;
    NvmeCmdWrapper->NvmCmd.NSID = Packet->NvmeCmd->Nsid;
    NvmeCmdWrapper->NvmCmd.MPTR = 0;
    NvmeCmdWrapper->AdminOrNVMCmdSet = Packet->QueueType ? FALSE : TRUE;
    NvmeCmdWrapper->SQIdentifier = Packet->QueueType;           // Queue 0 for Admin cmds,1 for I/O command
    NvmeCmdWrapper->CmdTimeOut = (UINT32)Packet->CommandTimeout;

    if(Packet->NvmeCmd->Flags & CDW10_VALID) {
        NvmeCmdWrapper->NvmCmd.CDW10 = Packet->NvmeCmd->Cdw10;
    }
    if(Packet->NvmeCmd->Flags & CDW11_VALID) {
        NvmeCmdWrapper->NvmCmd.CDW11 = Packet->NvmeCmd->Cdw11;
    }
    if(Packet->NvmeCmd->Flags & CDW12_VALID) {
        NvmeCmdWrapper->NvmCmd.CDW12 = Packet->NvmeCmd->Cdw12;
    }
    if(Packet->NvmeCmd->Flags & CDW13_VALID) {
        NvmeCmdWrapper->NvmCmd.CDW13 = Packet->NvmeCmd->Cdw13;
    }
    if(Packet->NvmeCmd->Flags & CDW14_VALID) {
        NvmeCmdWrapper->NvmCmd.CDW14 = Packet->NvmeCmd->Cdw14;
    }
    if(Packet->NvmeCmd->Flags & CDW15_VALID) {
        NvmeCmdWrapper->NvmCmd.CDW15 = Packet->NvmeCmd->Cdw15;
    }

    // if QueueType is 0, Admin Command
    // if QueueType is 1, I/O Command
    if ( Packet->QueueType == NVME_ADMIN_SUBMISSION_QUEUE ) {

        Status = EFI_SUCCESS;
        switch(NvmeOpcode)
        {
            case DELETE_IO_SUBMISSION_QUEUE:
            case CREATE_IO_SUBMISSION_QUEUE:
            case DELETE_IO_COMPLETION_QUEUE:
            case CREATE_IO_COMPLETION_QUEUE:
            case ABORT:
            case ASYNC_EVENT_REQUEST:
                Status = EFI_UNSUPPORTED;
                break;
            case IDENTIFY:

                if( !( (Packet->NvmeCmd->Flags & CDW10_VALID) && Packet->TransferBuffer ) ) {
                    Status = EFI_INVALID_PARAMETER;
                    goto PassthruErrorExit;
                }

                if( Packet->TransferLength < sizeof(IDENTIFY_CONTROLLER_DATA) ) {
                    Status = EFI_BAD_BUFFER_SIZE;
                    goto PassthruErrorExit;
                }

                 NvmeCmdWrapper->NvmCmd.PRP1 = (UINT64)Packet->TransferBuffer;

                 // If PRP1 isn't aligned on MemoryPageSize, then PRP2 will also be used.
                 NvmeCmdWrapper->NvmCmd.PRP2 = ((UINT64)Packet->TransferBuffer & ~((UINT64)NvmeController->MemoryPageSize-1)) + 
                                               NvmeController->MemoryPageSize;
                break;

            case GET_FEATURES:
            case SET_FEATURES:
                if( (Packet->NvmeCmd->Flags & (CDW10_VALID | CDW11_VALID)) != (CDW10_VALID | CDW11_VALID)) {
                    Status = EFI_INVALID_PARAMETER;
                    goto PassthruErrorExit;
                }
                if( Packet->TransferBuffer ) {
                    NvmeCmdWrapper->NvmCmd.PRP1 = (UINT64)Packet->TransferBuffer;
                
                    // If PRP1 isn't aligned on MemoryPageSize, then PRP2 will also be used.
                    NvmeCmdWrapper->NvmCmd.PRP2 = ((UINT64)Packet->TransferBuffer & ~((UINT64)NvmeController->MemoryPageSize-1)) + 
                                                   NvmeController->MemoryPageSize;
                }
                break;

            case GET_LOG_PAGE:
                if( !( (Packet->NvmeCmd->Flags & CDW10_VALID) && Packet->TransferBuffer) ) {
                    Status = EFI_INVALID_PARAMETER;
                    goto PassthruErrorExit;
                }

                NvmeCmdWrapper->NvmCmd.PRP1 = (UINT64)Packet->TransferBuffer;
                           
                // If PRP1 isn't aligned on MemoryPageSize, then PRP2 will also be used.
                NvmeCmdWrapper->NvmCmd.PRP2 = ((UINT64)Packet->TransferBuffer & ~((UINT64)NvmeController->MemoryPageSize-1)) + 
                                              NvmeController->MemoryPageSize;
                break;

            case FORMAT_NVM:
                if( !(Packet->NvmeCmd->Flags & CDW10_VALID) ) {
                    Status = EFI_INVALID_PARAMETER;
                    goto PassthruErrorExit;
                }
                break;

            case SECURITY_SEND:
            case SECURITY_RECEIVE:
                if( ( (Packet->NvmeCmd->Flags & (CDW10_VALID | CDW11_VALID)) != (CDW10_VALID | CDW11_VALID)) ) {
                    Status = EFI_INVALID_PARAMETER;
                    goto PassthruErrorExit;
                }

                NvmeCmdWrapper->NvmCmd.PRP1 = (UINT64)Packet->TransferBuffer;

                // If PRP1 isn't aligned on MemoryPageSize, then PRP2 will also be used.
                NvmeCmdWrapper->NvmCmd.PRP2 = ((UINT64)Packet->TransferBuffer & ~((UINT64)NvmeController->MemoryPageSize-1)) + 
                                              NvmeController->MemoryPageSize;
                break;

            case FIRMWARE_ACTIVATE:
            case FIRMWARE_IMAGE_DOWNLOAD:
            default:
                Status = EFI_UNSUPPORTED;
                break;
        }
        if( Status != EFI_UNSUPPORTED ) {
            // Send Nvme Command
            Status = ExecuteNvmeCmd (NvmeController, NvmeCmdWrapper, (COMPLETION_QUEUE_ENTRY*)NvmeCompletionData);
        }
    } else {  // Send NVM command to Valid Namespace ID

        Status = EFI_INVALID_PARAMETER;
        switch(NvmeOpcode)
        {
            case NVME_READ:
            case NVME_WRITE:
            case NVME_COMPARE:

                // LBA value is passed through Command Dword 10 & 11, return error if either CDW10 or CDW11 is invalid
                if( ((Packet->NvmeCmd->Flags & (CDW10_VALID | CDW11_VALID)) != (CDW10_VALID | CDW11_VALID)) ) {
                    break;
                }
                
                LBA = Packet->NvmeCmd->Cdw11;
                LBA = Shl64(LBA, 32) | ( (UINT64)Packet->NvmeCmd->Cdw10 & 0x0FFFFFFFF );

                ActiveNameSpace = GetActiveNameSpace( NvmeController, Packet->NvmeCmd->Nsid );

                if( !ActiveNameSpace ) {
                    goto PassthruErrorExit;
                }
                Status = NvmeReadWriteBlocks ( ActiveNameSpace,
                                               0,                                // MediaId = 0
                                               LBA,
                                               (UINT64)Packet->TransferLength,   // BufferSize,
                                               (VOID*)(Packet->TransferBuffer),  // Buffer,
                                               (COMPLETION_QUEUE_ENTRY*)NvmeCompletionData,
                                                NvmeOpcode                       // ReadWriteOpCode
                                              );
                 break;

            case NVME_WRITE_ZEROES:
                // LBA value is passed through Command Dword 10,11,12,13,14 and 15, return error if any one of the
                // Command Dword is invalid
                if( (Packet->NvmeCmd->Flags & (CDW14_VALID|CDW15_VALID)) != (CDW14_VALID|CDW15_VALID)) {
                    break;
                }

            case NVME_WRITE_UNCORRECTABLE:
                // LBA value is passed through Command Dword 10,11 and 12, return error if any one of the
                // Command Dword is invalid
                if( !(Packet->NvmeCmd->Flags & CDW12_VALID)) {
                    break;
                }
            case NVME_DATASET_MANAGEMENT:
                // LBA value is passed through Command Dword 10,11 return error if any one of the
                // Command Dword is invalid
                if( (Packet->NvmeCmd->Flags & (CDW10_VALID |CDW11_VALID)) != (CDW10_VALID |CDW11_VALID)) {
                    break;
                }
            case NVME_FLUSH:
                // Send Nvme Command
                Status = ExecuteNvmeCmd (NvmeController, NvmeCmdWrapper, (COMPLETION_QUEUE_ENTRY*)NvmeCompletionData);
                break;
            default:
                Status = EFI_UNSUPPORTED;
                break;
         }
    }
PassthruErrorExit:

    if( NvmeCmdWrapper ) {
        pBS->FreePool ( NvmeCmdWrapper );
    }

    return Status;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------
// Procedure: GetNextNamespace
//
// Description:  
//  API to get next valid NameSpace ID of the Nvme Device
//
// Input: 
//   IN    This         A pointer to the EFI_NVM_EXPRESS_PASS_THRU_PROTOCOL instance
//   IN    NamespaceId  A pointer to a valid Namespace ID on this NVM Express controller 
//
// Output: 
//   EFI_STATUS
//
// Modified:  
//
// Referrals: 
//
// Notes:
//
//----------------------------------------------------------------------
//<AMI_PHDR_END> 

EFI_STATUS
GetNextNamespace(
    IN EFI_NVM_EXPRESS_PASS_THRU_PROTOCOL    *This,
    IN OUT UINT32                            *NamespaceId
)
{
    AMI_NVME_CONTROLLER_PROTOCOL *NvmeController;
    ACTIVE_NAMESPACE_DATA        *ActiveNameSpaceData;
    LIST_ENTRY                   *LinkData;
    BOOLEAN                      ReturnNextNameSpaceId = FALSE;

    if(!NamespaceId || !This) {
        return EFI_INVALID_PARAMETER;
    }
    if( 0xFFFFFFFF == *NamespaceId) {
        ReturnNextNameSpaceId = TRUE;
    }

    NvmeController = NVME_CONTROLLER_PROTOCOL_FROM_THIS(This);

    for (LinkData = NvmeController->ActiveNameSpaceList.ForwardLink; 
            LinkData != &NvmeController->ActiveNameSpaceList; 
            LinkData = LinkData->ForwardLink) {
        
        ActiveNameSpaceData = _CR(LinkData ,ACTIVE_NAMESPACE_DATA, Link);

        if( TRUE == ReturnNextNameSpaceId) {
            *NamespaceId = ActiveNameSpaceData->ActiveNameSpaceID;
            return EFI_SUCCESS;
        }
        
        if(ActiveNameSpaceData->ActiveNameSpaceID == *NamespaceId) {
            ReturnNextNameSpaceId = TRUE;
        }
    }

    return EFI_NOT_FOUND;
}
//<AMI_PHDR_START>
//----------------------------------------------------------------------
// Procedure: SearchDevicePathNode
//
// Description:  
//  Routine Searches device path by specific Type and SubType
//
// Input: 
//   IN   DevicePath  A pointer to the device path protocol
//   IN   Type       Device path Node Type
//   IN   SubType    Device path node subtype
//
// Output: 
//  EFI_DEVICE_PATH_PROTOCOL*
//
// Modified:  
//
// Referrals: 
//
// Notes:
//
//----------------------------------------------------------------------
//<AMI_PHDR_END> 

EFI_DEVICE_PATH_PROTOCOL*
SearchDevicePathNode (
  IN    OUT     EFI_DEVICE_PATH_PROTOCOL *DevicePath,
  IN    UINT8   Type,
  IN    UINT8   SubType
)
{
    if (DevicePath == NULL) {
        return NULL;
    }

    while (!isEndNode (DevicePath)) {
        if ((DevicePathType (DevicePath) == Type) && (DevicePathSubType (DevicePath) == SubType)) {
            return DevicePath;
        }
        DevicePath = NextDevicePathNode (DevicePath);
    }

    return NULL;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------
// Procedure: BuildDevicePath
//
// Description:  
//  Used to allocate and build a device path node for an NVM Express namespace 
//    on an NVM Express controller
//
// Input: 
//  IN     This         A pointer to the EFI_NVM_EXPRESS_PASS_THRU_PROTOCOL instance
//  IN     NamespaceId  The NVM Express namespace ID for which a device path node is
//                        to be allocated and built
//  IN     DevicePath   A pointer to a single device path node that describes the 
//                        NVM Express namespace specified by NamespaceId. 
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
//----------------------------------------------------------------------
//<AMI_PHDR_END> 

EFI_STATUS 
BuildDevicePath (
    IN EFI_NVM_EXPRESS_PASS_THRU_PROTOCOL    *This,
    IN UINT32                                NamespaceId,
    IN OUT EFI_DEVICE_PATH_PROTOCOL          **DevicePath
)
{
    EFI_STATUS                   Status;
    AMI_NVME_CONTROLLER_PROTOCOL *NvmeController;
    LIST_ENTRY                   *LinkData;
    ACTIVE_NAMESPACE_DATA        *ActiveNameSpaceData;
    EFI_DEVICE_PATH_PROTOCOL     *DevicePathProtocol;
    NVME_DEVICE_PATH              *NvmeDevicePathNode = NULL;
    
    if( !DevicePath || !This ) {
        return EFI_INVALID_PARAMETER;
    }

    Status = pBS->AllocatePool( EfiBootServicesData, 
                                sizeof(NVME_DEVICE_PATH),
                                (void**)DevicePath );
    if(EFI_ERROR(Status)) {
        return EFI_OUT_OF_RESOURCES;
    }       
    
    NvmeController = NVME_CONTROLLER_PROTOCOL_FROM_THIS(This);
    
    for (LinkData = NvmeController->ActiveNameSpaceList.ForwardLink; 
            LinkData != &NvmeController->ActiveNameSpaceList; 
            LinkData = LinkData->ForwardLink) {
        
        ActiveNameSpaceData = _CR(LinkData ,ACTIVE_NAMESPACE_DATA, Link);
        
        if(ActiveNameSpaceData->ActiveNameSpaceID == NamespaceId) {

            Status = pBS->HandleProtocol (
                        ActiveNameSpaceData->NvmeDeviceHandle,
                        &gEfiDevicePathProtocolGuid,
                        &DevicePathProtocol );

            NvmeDevicePathNode = (NVME_DEVICE_PATH*)SearchDevicePathNode ( DevicePathProtocol, MESSAGING_DEVICE_PATH, MSG_NVME_DP);
            
            pBS->CopyMem( (UINT8*)*DevicePath, (UINT8*)NvmeDevicePathNode, sizeof(NVME_DEVICE_PATH) );
 
            return EFI_SUCCESS;
        }
    }
    
    return EFI_NOT_FOUND;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------
// Procedure: GetNamespace
//
// Description:  
//  Used to translate a device path node to a Namespace ID
//
//
// Input: 
//  IN     This         A pointer to the EFI_NVM_EXPRESS_PASS_THRU_PROTOCOL instance
//  IN     DevicePath   A pointer to the device path node that describes an NVM 
//                        Express namespace on the NVM Express controller. 
//  IN     NamespaceId  The NVM Express namespace ID contained in the device path node
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
//----------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS 
GetNamespace (
    IN EFI_NVM_EXPRESS_PASS_THRU_PROTOCOL    *This,
    IN EFI_DEVICE_PATH_PROTOCOL              *DevicePath,
    OUT UINT32                               *NamespaceId
)
{
    UINT16                       DevicePathLength = 0;
        
    if(!DevicePath || !This || !NamespaceId) {
        return EFI_INVALID_PARAMETER;
    }
    
  DevicePathLength = (DevicePath)->Length[0] | (DevicePath)->Length[1] << 8;

    if ((DevicePath->Type != MESSAGING_DEVICE_PATH) || 
        (DevicePath->SubType != MSG_NVME_DP) ||
        (DevicePathLength != sizeof(NVME_DEVICE_PATH))) {
        return EFI_UNSUPPORTED;
    }

    *NamespaceId = ((NVME_DEVICE_PATH* )DevicePath)->Nsid;
    
    return EFI_SUCCESS;
}

//**********************************************************************
//**********************************************************************
//**                                                                  **
//**        (C)Copyright 1985-2015, American Megatrends, Inc.         **
//**                                                                  **
//**                       All Rights Reserved.                       **
//**                                                                  **
//**         5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093     **
//**                                                                  **
//**                       Phone: (770)-246-8600                      **
//**                                                                  **
//**********************************************************************
//**********************************************************************
