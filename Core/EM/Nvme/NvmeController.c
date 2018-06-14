//**********************************************************************
//**********************************************************************
//**                                                                  **
//**        (C)Copyright 1985-2014, American Megatrends, Inc.         **
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
// $Header: /Alaska/SOURCE/Modules/NVMe/NvmeController.c 3     5/14/15 2:39a Karthikar $
//
// $Revision: 3 $
//
// $Date: 5/14/15 2:39a $
//**********************************************************************
// Revision History
// ----------------
// $Log: /Alaska/SOURCE/Modules/NVMe/NvmeController.c $
// 
// 3     5/14/15 2:39a Karthikar
// [TAG]  		EIP216763 
// [Category]  	Improvement
// [Description]  	Update the Aptio 4.x Nvme driver to Aptio 5.x Nvme
// driver Label 05
// [Files]  		Nvme.mak,NvmeBus.c, NvmeBus.h, NvmeController.c,
// NvmePassthru.c,NvmePassthru.h, NvmeSmm.c, NvmExpressPassThru.h,
// PDiskInfo.h
// 
// 2     9/04/14 7:47a Anandakrishnanl
// [TAG]  		EIP180861
// [Category]  	Improvement
// [Description]  	Legacy Boot support in Aptio 4.x Nvme driver
// [Files]  		Nvme.cif	
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
//**********************************************************************
//<AMI_FHDR_START>
//
// Name:        NvmeController.c
//
// Description: Provides Access to Nvme Controller
//
//<AMI_FHDR_END>
//**********************************************************************

#include "NvmeIncludes.h"
#include "NvmeBus.h"
#include <AmiLib.h>
#include <AmiDxeLib.h>
#include <Protocol\DevicePath.h>
#include <Protocol\BlockIo.h>


//**********************************************************************
//<AMI_PHDR_START>
//
// Procedure:   SmmStall
//
// Description: Stall Function
//
// Input:
//      UINTN   Usec
//
// Output:
//      NONE
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
VOID 
SmmStall (
    UINTN   Usec
 )
{
    UINTN   Counter, i;
    UINT32  Data32, PrevData;
    UINTN   Remainder;

    Counter = (UINTN)Div64((Usec * 10), 3, &Remainder);

    if (Remainder != 0) {
        Counter++;
    }

    //
    // Call WaitForTick for Counter + 1 ticks to try to guarantee Counter tick
    // periods, thus attempting to ensure Microseconds of stall time.
    //
    if (Counter != 0) {

        PrevData = IoRead32(PM_BASE_ADDRESS + 8);
        for (i=0; i < Counter; ) {
            Data32 = IoRead32(PM_BASE_ADDRESS + 8);    
            if (Data32 < PrevData) {        // Reset if there is a overlap
                PrevData=Data32;
                continue;
            }
            i += (Data32 - PrevData);        
            PrevData = Data32;
        }
    }
    return;
}

//**********************************************************************
//<AMI_PHDR_START>
//
// Procedure:   CreateAdditionalSubmissionCompletionQueue
//
// Description: Creates Submission and Completion Queue
//
// Input:
//      IN  AMI_NVME_CONTROLLER_PROTOCOL    *NvmeController,
//      IN  NVME_COMMAND_WRAPPER            *NvmeCmdWrapper,
//      IN  UINT16                          QueueNumber,
//      IN  UINT32                          QueueSize
//
// Output:
//      EFI_STATUS
//
// Modified:
//      
// Referrals: 
//
// Notes:  Can be called recursively  
//
//
//<AMI_PHDR_END>
//**********************************************************************

EFI_STATUS
CreateAdditionalSubmissionCompletionQueue ( 
    IN  AMI_NVME_CONTROLLER_PROTOCOL    *NvmeController,
    IN  NVME_COMMAND_WRAPPER            *NvmeCmdWrapper,
    IN  UINT16                          QueueNumber,
    IN  UINT32                          QueueSize
)
{
   
    EFI_STATUS              Status;
    COMPLETION_QUEUE_ENTRY  CompletionData;
    UINTN                   AllocatePageSize;
    UINT64                  QueueAddress = 0;
    
    // Clear memory
    MemSet(NvmeCmdWrapper, sizeof(NVME_COMMAND_WRAPPER), 0);
    
    // Allocate memory only if the pointer is NULL
    if (NvmeController->Queue1CompletionUnAligned == 0) {
        AllocatePageSize = NvmeController->MemoryPageSize + QueueSize * sizeof(COMPLETION_QUEUE_ENTRY);
    
        Status = NvmeController->PciIO->AllocateBuffer (NvmeController->PciIO,
                                                 AllocateAnyPages,
                                                 EfiRuntimeServicesData,
                                                 EFI_SIZE_TO_PAGES(AllocatePageSize),
                                                 (VOID **)&(QueueAddress),
                                                 EFI_PCI_IO_ATTRIBUTE_MEMORY_CACHED | EFI_PCI_IO_ATTRIBUTE_MEMORY_WRITE_COMBINE
                                                 );
            
        if (EFI_ERROR(Status)) {
            return Status;
        }
    
        NvmeController->Queue1CompletionUnAligned = QueueAddress;
        NvmeController->Queue1CompletionUnAlignedSize = EFI_SIZE_TO_PAGES(AllocatePageSize);
        NvmeController->Queue1CompletionQueue = (QueueAddress & ~(NvmeController->MemoryPageSize - 1)) + 
                                                NvmeController->MemoryPageSize;
    
        NvmeController->Queue1CompletionQueueSize = QueueSize;
        
        MemSet((VOID *)NvmeController->Queue1CompletionQueue, \
                            NvmeController->Queue1CompletionQueueSize * sizeof (COMPLETION_QUEUE_ENTRY), 0);
        
        Status = NvmeController->PciIO->Map ( NvmeController->PciIO, 
                                      EfiPciIoOperationBusMasterCommonBuffer,
                                      (VOID *)NvmeController->Queue1CompletionQueue,
                                      &AllocatePageSize,
                                      &NvmeController->Queue1CompletionQueueMappedAddr,
                                      &NvmeController->Queue1CompletionQueueUnMap
                                      );
        
        if (EFI_ERROR(Status)) {
            return Status;
        }
    }
    
    // Build NVME command
    NvmeCmdWrapper->NvmCmd.CMD0.Opcode = CREATE_IO_COMPLETION_QUEUE;
    NvmeCmdWrapper->NvmCmd.CMD0.FusedOperation = 0;
    NvmeCmdWrapper->NvmCmd.CMD0.PSDT = 0;
    NvmeCmdWrapper->NvmCmd.CMD0.CommandIdentifier = NvmeController->CommandIdentifierAdmin;
    NvmeCmdWrapper->NvmCmd.NSID = 0;
            
    NvmeCmdWrapper->NvmCmd.PRP1 = (UINT64)NvmeController->Queue1CompletionQueueMappedAddr;
    NvmeCmdWrapper->NvmCmd.PRP2 = 0;
    NvmeCmdWrapper->NvmCmd.CDW10 = ((QueueSize - 1) << 16 )+ QueueNumber;
    NvmeCmdWrapper->NvmCmd.CDW11 = 1;           // Contiguous
    
    NvmeCmdWrapper->AdminOrNVMCmdSet = TRUE;
    NvmeCmdWrapper->SQIdentifier = 0;           // Cmd issued in Queue0
    NvmeCmdWrapper->CmdTimeOut = 1000;
    
    Status = ExecuteNvmeCmd (NvmeController, NvmeCmdWrapper, &CompletionData);
    
    if (EFI_ERROR(Status)) {
        goto CreateAdditionalSubmissionCompletionQueue_Exit;
    }

    // Allocate memory only if the pointer is NULL
    if (NvmeController->Queue1SubmissionUnAligned == 0) { 
        
        AllocatePageSize = NvmeController->MemoryPageSize + 
                            QueueSize * sizeof(NVME_ADMIN_COMMAND);  
        
        Status = NvmeController->PciIO->AllocateBuffer (NvmeController->PciIO,
                                             AllocateAnyPages,
                                             EfiRuntimeServicesData,
                                             EFI_SIZE_TO_PAGES(AllocatePageSize),
                                             (VOID **)&(QueueAddress),
                                             EFI_PCI_IO_ATTRIBUTE_MEMORY_CACHED | EFI_PCI_IO_ATTRIBUTE_MEMORY_WRITE_COMBINE
                                             );
                    
        if (EFI_ERROR(Status)) {
            return Status;
        }
    
        NvmeController->Queue1SubmissionUnAligned = QueueAddress;
        NvmeController->Queue1SubmissionUnAlignedSize = EFI_SIZE_TO_PAGES(AllocatePageSize);
        NvmeController->Queue1SubmissionQueue = (QueueAddress & ~(NvmeController->MemoryPageSize - 1)) + 
                                                NvmeController->MemoryPageSize;
    
        NvmeController->Queue1SubmissionQueueSize = QueueSize;
        MemSet((VOID *)NvmeController->Queue1SubmissionQueue, \
                                NvmeController->Queue1SubmissionQueueSize * sizeof(NVME_ADMIN_COMMAND), 0);
    
        Status = NvmeController->PciIO->Map ( NvmeController->PciIO, 
                                         EfiPciIoOperationBusMasterCommonBuffer,
                                         (VOID *)NvmeController->Queue1SubmissionQueue,
                                         &AllocatePageSize,
                                         &NvmeController->Queue1SubmissionQueueMappedAddr,
                                         &NvmeController->Queue1SubmissionQueueUnMap
                                         );
                
        if (EFI_ERROR(Status)) {
            return Status;
        }
                
    }
    
    // Build NVME command
    NvmeCmdWrapper->NvmCmd.CMD0.Opcode = CREATE_IO_SUBMISSION_QUEUE;
    NvmeCmdWrapper->NvmCmd.CMD0.FusedOperation = 0;
    NvmeCmdWrapper->NvmCmd.CMD0.PSDT = 0;
    NvmeCmdWrapper->NvmCmd.CMD0.CommandIdentifier = NvmeController->CommandIdentifierAdmin;
    NvmeCmdWrapper->NvmCmd.NSID = 0;
            
    NvmeCmdWrapper->NvmCmd.PRP1 = (UINT64)NvmeController->Queue1SubmissionQueueMappedAddr;
    NvmeCmdWrapper->NvmCmd.PRP2 = 0;
    NvmeCmdWrapper->NvmCmd.CDW10 = ((QueueSize - 1) << 16 )+ QueueNumber;
    NvmeCmdWrapper->NvmCmd.CDW11 = (QueueNumber << 16) + 1;           // Contiguous
    
    NvmeCmdWrapper->AdminOrNVMCmdSet = TRUE;
    NvmeCmdWrapper->SQIdentifier = 0;           // Cmd issued to admin queue
    NvmeCmdWrapper->CmdTimeOut = 1000;
    
    Status = ExecuteNvmeCmd (NvmeController, NvmeCmdWrapper, &CompletionData);
    
    CreateAdditionalSubmissionCompletionQueue_Exit:

    NvmeController->Queue1PhaseTag = FALSE;
    
    NvmeController->Queue1SubmissionQueueTailPtr = 0;
    NvmeController->Queue1SubmissionQueueHeadPtr = 0;
    
    NvmeController->Queue1CompletionQueueTailPtr = 0;
    NvmeController->Queue1CompletionQueueHeadPtr = 0;
    
    return Status;
   
}


//**********************************************************************
//<AMI_PHDR_START>
//
// Procedure:   ProgramPRP2List
//
// Description: Programs PRP2 with the list of page address for data transfer
//
// Input:
//  IN EFI_BLOCK_IO_PROTOCOL        *This
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
ProgramPRP2List (
    IN UINT64     *PRP2List, 
    IN UINT32      PageSize, 
    IN UINTN       BufferAddress,
    IN UINTN       BufferSize,
    IN UINTN       *PRP2TransferSize
)
{
    
    UINTN          TotalNumberOfEntries = PageSize / 8;        // Each entry 64 bytes long
            
    *PRP2TransferSize = 0;
    
    do {
        
        *PRP2List++ = BufferAddress;
        if (BufferSize >= PageSize) {
            *PRP2TransferSize += PageSize;
            BufferAddress += PageSize;
            BufferSize -= PageSize;
        } else {
              *PRP2TransferSize = *PRP2TransferSize + (UINT32)BufferSize;
              BufferAddress += BufferSize;
              BufferSize = 0;
        }
        
    } while (--TotalNumberOfEntries && (BufferSize > 0));
    
    return  EFI_SUCCESS;
    
}

//**********************************************************************
//<AMI_PHDR_START>
//
// Procedure:   NvmeReadWriteBlocks
//
// Description: Read/Write data from the given LBA address
//
// Input:
//   IN  ACTIVE_NAMESPACE_DATA   *ActiveNameSpace,
//   IN UINT32                       MediaId,
//   IN EFI_LBA                      LBA,
//   IN UINTN                        BufferSize,
//   OUT VOID                        *Buffer
//   IN UINT8                        ReadWriteOpCode
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
NvmeReadWriteBlocks(
    IN  ACTIVE_NAMESPACE_DATA       *ActiveNameSpace,
    IN UINT32                       MediaId,
    IN EFI_LBA                      LBA,
    IN UINTN                        BufferSize,
    OUT VOID                        *Buffer,
    OUT COMPLETION_QUEUE_ENTRY      *NvmeCompletionData,
    IN UINT8                        ReadWriteOpCode
)
{
    
    EFI_STATUS                      Status = EFI_SUCCESS;
    AMI_NVME_CONTROLLER_PROTOCOL    *NvmeController = ActiveNameSpace->NvmeController;
    EFI_BLOCK_IO_MEDIA              *BlkMedia = ActiveNameSpace->NvmeBlockIO.Media;
    NVME_COMMAND_WRAPPER            *NvmeCmdWrapper = NvmeController->NvmeCmdWrapper;
    COMPLETION_QUEUE_ENTRY          CompletionData;
    COMPLETION_QUEUE_ENTRY          *pCompletionData = &CompletionData;
    UINTN                           DataN;
    UINT32                          LBACountInOneTransfer;
    UINTN                           PRP1TransferSize;
    UINTN                           PRP2TransferSize;
    UINTN                           MappedBufferSize = BufferSize;
    EFI_PHYSICAL_ADDRESS            MappedBuffer;
    VOID                            *BufferUnMap;
    
    if (!NvmeController->NvmeInSmm) {
        TRACE((-1,"LBA : %lx BufferSize : %lx Buffer : %lx Opcode : %x", LBA, BufferSize, Buffer, ReadWriteOpCode));
    }

    // Check if Media ID matches
    if (BlkMedia->MediaId != MediaId) {
        return EFI_MEDIA_CHANGED;
    }

    if (BufferSize == 0) {
        return EFI_SUCCESS;
    }
    
    //
    // If IoAlign values is 0 or 1, means that the buffer can be placed 
    // anywhere in memory or else IoAlign value should be power of 2. To be
    // properly aligned the buffer address should be divisible by IoAlign  
    // with no remainder. 
    // 
    if((BlkMedia->IoAlign > 1 ) && ((UINTN)Buffer % BlkMedia->IoAlign)) {
        return EFI_INVALID_PARAMETER;
    }
    
    // Check whether the block size is multiple of BlkMedia->BlockSize
    DataN = BufferSize % BlkMedia->BlockSize;
    if (DataN){
	    return EFI_BAD_BUFFER_SIZE;
    }

    // Check for Valid start LBA #
    if (LBA > BlkMedia->LastBlock) {
        return EFI_INVALID_PARAMETER;
    }

    // Check for Valid End LBA #
    DataN = BufferSize / BlkMedia->BlockSize;
    if (LBA + DataN > BlkMedia->LastBlock + 1) {
        return EFI_INVALID_PARAMETER;
    }

    do {
        // Limit the transfer size to MDTS value
        if (NvmeController->IdentifyControllerData->MDTS && (MappedBufferSize > (UINTN)(Mul64(Shl64(1, NvmeController->IdentifyControllerData->MDTS), NvmeController->MemoryPageSizeMin)))){
    		MappedBufferSize = (UINTN)Mul64(Shl64(1, NvmeController->IdentifyControllerData->MDTS), NvmeController->MemoryPageSizeMin);
        }

       
        // After MAP, Mapped BufferSize may not be same as input. 
        // So need to complete the transfer in multiple loops.
        // When the call originates from SMM, don't call Map function
        MappedBuffer = (EFI_PHYSICAL_ADDRESS) Buffer;
        if (!NvmeController->NvmeInSmm) {

            Status = NvmeController->PciIO->Map ( NvmeController->PciIO, 
                                          ((ReadWriteOpCode == NVME_READ) || (ReadWriteOpCode == NVME_COMPARE)) ? EfiPciIoOperationBusMasterWrite : EfiPciIoOperationBusMasterRead,
                                              Buffer,
                                              &MappedBufferSize,
                                              &MappedBuffer,
                                              &BufferUnMap
                                              );
            if (EFI_ERROR(Status)) {
                return Status;
            }
        }
        
        MemSet(NvmeCmdWrapper, sizeof(NVME_COMMAND_WRAPPER), 0); 
        LBACountInOneTransfer = 0;

        PRP2TransferSize = 0;
       
        NvmeCmdWrapper->NvmCmd.PRP1 = (UINT64) MappedBuffer; 
        PRP1TransferSize = NvmeController->MemoryPageSize - 
                            (MappedBuffer & ((UINTN)(NvmeController->MemoryPageSize) - 1));
        
        // If all data can be transferred using only PRP1 then do that.
        if (PRP1TransferSize >= MappedBufferSize) {
            PRP1TransferSize = MappedBufferSize;
        }
        
        // Do we need PRP2
        if (MappedBufferSize - PRP1TransferSize) {
            
            // Do we need either a PRP2 pointer or a List
            if (MappedBufferSize - PRP1TransferSize <= NvmeController->MemoryPageSize) {
                NvmeCmdWrapper->NvmCmd.PRP2 = NvmeCmdWrapper->NvmCmd.PRP1 + PRP1TransferSize;
                PRP2TransferSize = MappedBufferSize - PRP1TransferSize;
            } else {
                  // We need PRP2 List
                  Status = ProgramPRP2List (ActiveNameSpace->PRP2List, NvmeController->MemoryPageSize, \
                                        (UINTN)MappedBuffer + PRP1TransferSize, \
                                        MappedBufferSize -  PRP1TransferSize, &PRP2TransferSize
                                        );
                
                  if (EFI_ERROR(Status)) {
                    break;
                }
                
                  NvmeCmdWrapper->NvmCmd.PRP2 = (UINT64) ActiveNameSpace->PRP2ListMappedAddr;
            }
        }
        
        LBACountInOneTransfer = (UINT32)((PRP1TransferSize + PRP2TransferSize) / BlkMedia->BlockSize);
        
        // Build NVME command
        NvmeCmdWrapper->NvmCmd.CMD0.Opcode = ReadWriteOpCode;
        NvmeCmdWrapper->NvmCmd.CMD0.FusedOperation = 0;
        NvmeCmdWrapper->NvmCmd.CMD0.PSDT = 0;
        NvmeCmdWrapper->NvmCmd.CMD0.CommandIdentifier = NvmeController->CommandIdentifierQueue1;
        NvmeCmdWrapper->NvmCmd.NSID = ActiveNameSpace->ActiveNameSpaceID;
        
        NvmeCmdWrapper->NvmCmd.MPTR = 0;
        NvmeCmdWrapper->NvmCmd.CDW10 = (UINT32)LBA;       
        NvmeCmdWrapper->NvmCmd.CDW11 = (UINT32)Shr64(LBA, 32);           
        NvmeCmdWrapper->NvmCmd.CDW12 = 0x80000000 + (LBACountInOneTransfer - 1);           
        NvmeCmdWrapper->NvmCmd.CDW13 = 0;           
        NvmeCmdWrapper->NvmCmd.CDW14 = 0;           
            
        NvmeCmdWrapper->AdminOrNVMCmdSet = FALSE;
        NvmeCmdWrapper->SQIdentifier = NvmeController->NVMQueueNumber;
        NvmeCmdWrapper->CmdTimeOut = 1000;
        
        // If caller has passed buffer to return controller status, use it.
        if (NvmeCompletionData) {
            pCompletionData = NvmeCompletionData;
        }
        
        Status = ExecuteNvmeCmd (NvmeController, NvmeCmdWrapper, pCompletionData);
        
        if (EFI_ERROR(Status)) {
            if (!NvmeController->NvmeInSmm) {
                NvmeController->PciIO->Unmap(NvmeController->PciIO, BufferUnMap);
            }
            break;
        }
        
        // Remaining Bytes to be transferred
        MappedBufferSize -= (LBACountInOneTransfer * BlkMedia->BlockSize);

        // Update LBA # for next transfer if needed        
        LBA += LBACountInOneTransfer;
        
       // Adjust the Buffer address
       Buffer =(VOID*) ((UINTN) Buffer + (LBACountInOneTransfer * BlkMedia->BlockSize));
       BufferSize -= (LBACountInOneTransfer * BlkMedia->BlockSize);

       // When PciIO->Map is called, it might not map the complete buffer.
       // After the complete MappedBufferSize is transferred, if there is a left over do that transfer also
       if (MappedBufferSize == 0) {
           MappedBufferSize = BufferSize;
       }
       
       if (!NvmeController->NvmeInSmm) {
           NvmeController->PciIO->Unmap(NvmeController->PciIO, BufferUnMap);
       }    
   
    } while (MappedBufferSize);

    if (!NvmeController->NvmeInSmm) {
        TRACE((-1,"%r \n", Status));
    }
    
    return Status;
    
}

//**********************************************************************
//<AMI_PHDR_START>
//
// Procedure:   ExecuteNvmeCmd
//
// Description: Execute Admin and Nvme cmds
//
// Input:
//  IN  AMI_NVME_CONTROLLER_PROTOCOL    *NvmeController, 
//  IN  NVME_COMMAND_WRAPPER            *NvmeCmdWrapper,
//  OUT COMPLETION_QUEUE_ENTRY          *CmdCompletionData
//
// Output:
//  EFI_STATUS
//
// Modified:
//      
// Referrals: 
//
// Notes: If the cmd needs to be retried due to a failure, caller can initialize the RetryCount.
//        Can be called recursively.
//
//
//<AMI_PHDR_END>
//**********************************************************************
EFI_STATUS
ExecuteNvmeCmd (
    IN  AMI_NVME_CONTROLLER_PROTOCOL    *NvmeController,
    IN  NVME_COMMAND_WRAPPER            *NvmeCmdWrapper,
    OUT COMPLETION_QUEUE_ENTRY          *CmdCompletionData
)

{
    EFI_STATUS      Status;
    
    do {
        // Because of recursive nature and retry mechnism, cmd identifer needs to be updated just before giving the call.
        NvmeCmdWrapper->NvmCmd.CMD0.CommandIdentifier = NvmeCmdWrapper->AdminOrNVMCmdSet ? NvmeController->CommandIdentifierAdmin : \
                                                         NvmeController->CommandIdentifierQueue1;
        
        NvmeCmdWrapper->AdminOrNVMCmdSet ? (Status = AddToAdminSubmissionQueue(NvmeController, NvmeCmdWrapper)) : \
                (Status = AddToQueue1SubmissionQueue(NvmeController, NvmeCmdWrapper));
    
        if (EFI_ERROR(Status)) {
            continue;
        }
    
        Status = UpdateDoorBellRegister(NvmeController, 
                                        NvmeCmdWrapper->SQIdentifier,
                                        NvmeCmdWrapper->AdminOrNVMCmdSet ? NvmeController->AdminSubmissionQueueTailPtr :
                                        NvmeController->Queue1SubmissionQueueTailPtr 
                                        );

        if (EFI_ERROR(Status)) {
            continue;
        }

        //Wait for cmd to complete
        if (NvmeCmdWrapper->NvmCmd.CMD0.Opcode != ASYNC_EVENT_REQUEST) {
            Status = WaitForCompletionQueueUpdate(NvmeController, NvmeCmdWrapper, CmdCompletionData);
        }
    
    } while (EFI_ERROR(Status) && NvmeCmdWrapper->RetryCount--);
    
    return  Status;
    
}


//**********************************************************************
//<AMI_PHDR_START>
//
// Procedure:   AddToAdminSubmissionQueue
//
// Description: Submits the cmd to the Admin Submission queue
//
// Input:
//  IN  AMI_NVME_CONTROLLER_PROTOCOL    *NvmeController,
//  IN  NVME_COMMAND_WRAPPER            *NvmeCmdWrapper
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
AddToAdminSubmissionQueue (
    IN AMI_NVME_CONTROLLER_PROTOCOL    *NvmeController,
    IN NVME_COMMAND_WRAPPER            *NvmeCmdWrapper
)
{
    EFI_STATUS          Status;
    UINT64              DestinationAddress;
    
    // Is Admin Queue full?
    if (NvmeController->AdminSubmissionQueueHeadPtr) {  // Non-zero value
        if ((NvmeController->AdminSubmissionQueueTailPtr - 1) == NvmeController->AdminSubmissionQueueHeadPtr){
            
            // In this design, queue should never get filled up. 
            // If it does something is wrong. Delete and start all over again.
            
            Status = RecreateAllQueues (NvmeController);
            if (EFI_ERROR(Status)) {            
                return EFI_OUT_OF_RESOURCES;
            }
          
        }
    } else {
        // If Head is at the start and Tail is at the end, then queue is full
          if (NvmeController->AdminSubmissionQueueTailPtr == (NvmeController->AdminSubmissionQueueHeadPtr + 
                                                            NvmeController->AdminSubmissionQueueSize - 1)) {
            
            // In this design, queue should never get filled up. 
            // If it does something is wrong. Delete and start all over again.
              Status = RecreateAllQueues (NvmeController);
              if (EFI_ERROR(Status)) {            
                  return EFI_OUT_OF_RESOURCES;
              }
          }
    }
    
    // Copy cmd to Admin Queue
    DestinationAddress = NvmeController->AdminSubmissionQueue + (
                        NvmeController->AdminSubmissionQueueTailPtr * sizeof(NVME_ADMIN_COMMAND));
    
#if  NVME_VERBOSE_PRINT
    if (!NvmeController->NvmeInSmm) {
        TRACE((-1, "Destination Address for Cmd               : %016lx\n", DestinationAddress));
    }
#endif
    
    MemCpy ((VOID *)DestinationAddress, &(NvmeCmdWrapper->NvmCmd), sizeof(NVME_ADMIN_COMMAND));
    
    NvmeController->AdminSubmissionQueueTailPtr++;
    
    // Check if there is a roller over
    if (NvmeController->AdminSubmissionQueueTailPtr >= (NvmeController->AdminSubmissionQueueSize)) {
        NvmeController->AdminSubmissionQueueTailPtr = 0;
    }
    
    return EFI_SUCCESS;
    
}


//**********************************************************************
//<AMI_PHDR_START>
//
// Procedure:   AddToQueue1SubmissionQueue
//
// Description: Submits the Nvme cmd to the Queue1 Submission queue
//
// Input:
//  IN  AMI_NVME_CONTROLLER_PROTOCOL    *NvmeController,
//  IN  NVME_COMMAND_WRAPPER            *NvmeCmdWrapper,
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
AddToQueue1SubmissionQueue (
    IN AMI_NVME_CONTROLLER_PROTOCOL    *NvmeController,
    IN NVME_COMMAND_WRAPPER            *NvmeCmdWrapper
)
{
    EFI_STATUS          Status;
    UINT64              DestinationAddress;
    
    // Is Queue full? If Tail is one less than the Head queue is full.
    if (NvmeController->Queue1SubmissionQueueHeadPtr) {  // Non-zero value
        if ((NvmeController->Queue1SubmissionQueueTailPtr - 1) == NvmeController->Queue1SubmissionQueueHeadPtr){
            
            // In this design, queue should never get filled up. 
            // If it does something is wrong. Delete and start all over again.
            Status = RecreateQueue1 (NvmeController);
            if (EFI_ERROR(Status)) {    
                return EFI_OUT_OF_RESOURCES;
            }
            
        }
    } else { 
          // If Head is at the start and Tail is at the end, then queue is full
          if (NvmeController->Queue1SubmissionQueueTailPtr == (NvmeController->Queue1SubmissionQueueHeadPtr + 
                                                        NvmeController->Queue1SubmissionQueueSize - 1)) {
              
              // In this design, queue should never get filled up. 
              // If it does something is wrong. Delete and start all over again.
              
              Status = RecreateQueue1 (NvmeController);
              if (EFI_ERROR(Status)) {		    
                  return EFI_OUT_OF_RESOURCES;
              }
          }
    }
    
    // Copy cmd to Admin Queue
    DestinationAddress = NvmeController->Queue1SubmissionQueue + 
                        (NvmeController->Queue1SubmissionQueueTailPtr * sizeof(NVME_ADMIN_COMMAND));

#if NVME_VERBOSE_PRINT
    if (!NvmeController->NvmeInSmm) {
        TRACE((-1, "Destination Address for Cmd               : %016lx\n", DestinationAddress));
    }
#endif
    
    MemCpy ((VOID *)DestinationAddress, &(NvmeCmdWrapper->NvmCmd), sizeof(NVME_ADMIN_COMMAND));
    
    NvmeController->Queue1SubmissionQueueTailPtr++; 
    
    // Check if there is a roller over
    if (NvmeController->Queue1SubmissionQueueTailPtr >= NvmeController->Queue1SubmissionQueueSize) {
        NvmeController->Queue1SubmissionQueueTailPtr = 0;
    }
    
    return EFI_SUCCESS;
    
}

//**********************************************************************
//<AMI_PHDR_START>
//
// Procedure:   UpdateDoorBellRegister
//
// Description: Update door bell register for the controller to start executing the cmd
//
// Input:
// IN AMI_NVME_CONTROLLER_PROTOCOL      *NvmeController,
// IN UINT16                            QueueNumber,
// IN UINT32                            Value
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
UpdateDoorBellRegister (
    IN AMI_NVME_CONTROLLER_PROTOCOL    *NvmeController,
    IN UINT16                          QueueNumber,
    IN UINT32                          Value
)
{
    
    UINT32      Offset;
    
    // Update Door Bell Register
    Offset = QUEUE_DOORBELL_OFFSET(QueueNumber, 0, NvmeController->DoorBellStride);
    
#if  NVME_VERBOSE_PRINT    
    if (!NvmeController->NvmeInSmm) {
        TRACE((-1, "\nDoorBell Offset %016lx Value %08X\n", NvmeController->NvmeBarOffset + Offset, Value));
    }
#endif
    
    CONTROLLER_REG32(NvmeController->NvmeBarOffset, Offset) = Value;
    return EFI_SUCCESS;
    
}

//**********************************************************************
//<AMI_PHDR_START>
//
// Procedure:   WaitForCompletionQueueUpdate
//
// Description: Checks for the completion queue for the correct PhaseTag, Queue Identified and Cmd Identifier
//
// Input:
//  IN  AMI_NVME_CONTROLLER_PROTOCOL        *NvmeController,
//  IN  NVME_COMMAND_WRAPPER                *NvmeCmdWrapper,
//  OUT COMPLETION_QUEUE_ENTRY              *CmdCompletionData 
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
WaitForCompletionQueueUpdate (
    IN  AMI_NVME_CONTROLLER_PROTOCOL        *NvmeController,
    IN  NVME_COMMAND_WRAPPER                *NvmeCmdWrapper,
    OUT COMPLETION_QUEUE_ENTRY              *CmdCompletionData 
)
{
    
    EFI_STATUS              Status;
    UINT32                  TimeOut = NvmeCmdWrapper->CmdTimeOut;
    UINT32                  Offset;
    COMPLETION_QUEUE_ENTRY  *pCmdCompletionData;
    UINT16                  CommandIdentifier = NvmeCmdWrapper->AdminOrNVMCmdSet ? NvmeController->CommandIdentifierAdmin : \
                                                        NvmeController->CommandIdentifierQueue1; 
    
    UINT64                  CompletionQueueStart = NvmeCmdWrapper->AdminOrNVMCmdSet ? NvmeController->AdminCompletionQueue : \
                                                NvmeController->Queue1CompletionQueue; 
    
    UINT16                  CompletionQueueHeadPtr = NvmeCmdWrapper->AdminOrNVMCmdSet ? NvmeController->AdminCompletionQueueHeadPtr :\
                                                NvmeController->Queue1CompletionQueueHeadPtr;
    
    // Toggle extected phasetag on every rollover
    if (CompletionQueueHeadPtr == 0) {
            NvmeCmdWrapper->AdminOrNVMCmdSet ? (NvmeController->AdminPhaseTag = ~NvmeController->AdminPhaseTag) : \
                        (NvmeController->Queue1PhaseTag = ~NvmeController->Queue1PhaseTag);
    }
    
    // Get the offset to the Command Completion Queue Head Ptr
    pCmdCompletionData = (COMPLETION_QUEUE_ENTRY *)(CompletionQueueStart + CompletionQueueHeadPtr * sizeof(COMPLETION_QUEUE_ENTRY));
    
    do {
        // Check whether Command Identifier, SQ ID matches and Phase Tag matches with the cmd issued.
        if ((pCmdCompletionData->CommandIdentifier == CommandIdentifier) && \
            (pCmdCompletionData->SQIdentifier == NvmeCmdWrapper->SQIdentifier) && \
            (pCmdCompletionData->PhaseTag == (NvmeCmdWrapper->AdminOrNVMCmdSet ? NvmeController->AdminPhaseTag : NvmeController->Queue1PhaseTag)))
        {
            break;
        }
        
        // check if there are any fatal errors
        if (CONTROLLER_REG32(NvmeController->NvmeBarOffset, Offset_CSTS) & CSTS_CFS){
            if (!NvmeController->NvmeInSmm) {
                TRACE((-1, "Nvme Fatal Error\n"));
            }
            return EFI_DEVICE_ERROR;            
            
        }
        
        if (!NvmeController->NvmeInSmm) {
            pBS->Stall(1000); // 1msec delay
        } else {
            SmmStall (1000);
        }
    } while (--TimeOut);
    
    if (!NvmeController->NvmeInSmm) { 
        PrintCommandCompletionData (pCmdCompletionData);
    }

    if (!TimeOut) {
        
        // This is a fatal condition. We should expect some kind of response from the controller. 
        // If not we have to either wait for more time or delete and recreate the queue
        
        NvmeCmdWrapper->AdminOrNVMCmdSet ? NvmeController->CommandIdentifierAdmin++ : \
                                            NvmeController->CommandIdentifierQueue1++;
        
        if (NvmeCmdWrapper->AdminOrNVMCmdSet) {
            Status = RecreateAllQueues(NvmeController);
        } else {
            Status = RecreateQueue1(NvmeController);
        }
        
        if (EFI_ERROR(Status)) {
            // If recreating the queue gets an error. nothing can be done.
            NvmeCmdWrapper->RetryCount = 0;
        } else {
            // Retry the cmd one more time
            NvmeCmdWrapper->RetryCount++;
        }
        
        return EFI_DEVICE_ERROR;
    }
    
    // Update HeadPtr from Completion Queue. 
    // Check what Queue was cmd posted to and then update the corresponding Head/Tail ptr
    if (NvmeCmdWrapper->AdminOrNVMCmdSet) {
        NvmeController->AdminSubmissionQueueHeadPtr = pCmdCompletionData->SQHeadPointer;
        NvmeController->AdminCompletionQueueHeadPtr = NvmeController->AdminSubmissionQueueHeadPtr;
        Offset = QUEUE_DOORBELL_OFFSET(NvmeCmdWrapper->SQIdentifier, 1, NvmeController->DoorBellStride);
        CONTROLLER_REG32(NvmeController->NvmeBarOffset, Offset) = NvmeController->AdminCompletionQueueHeadPtr;
    } else { 
        NvmeController->Queue1SubmissionQueueHeadPtr = pCmdCompletionData->SQHeadPointer;
        NvmeController->Queue1CompletionQueueHeadPtr = NvmeController->Queue1SubmissionQueueHeadPtr;
        Offset = QUEUE_DOORBELL_OFFSET(NvmeCmdWrapper->SQIdentifier, 1, NvmeController->DoorBellStride);
        CONTROLLER_REG32(NvmeController->NvmeBarOffset, Offset) = NvmeController->Queue1CompletionQueueHeadPtr;   
    }
    
    // Todo Todo
    // Check whether all cmds submitted has been completed. CompletionQueue Head Ptr should give a clue on
    // how many cmds where executed.
    if (pCmdCompletionData->StatusCode || pCmdCompletionData->StatusCodeType) {
        Status = EFI_DEVICE_ERROR;
    } else {
        Status = EFI_SUCCESS;
    }

#if  NVME_VERBOSE_PRINT
    if (!NvmeController->NvmeInSmm) {
        if (NvmeCmdWrapper->AdminOrNVMCmdSet) {
            TRACE((-1, "AdminSubmissionQueueHeadPtr %08X\n", NvmeController->AdminSubmissionQueueHeadPtr));
            TRACE((-1, "AdminSubmissionQueueTailPtr %08X\n", NvmeController->AdminSubmissionQueueTailPtr));
            TRACE((-1, "AdminCompletionQueueHeadPtr %08X\n", NvmeController->AdminCompletionQueueHeadPtr));
            TRACE((-1, "AdminCompletionQueueTailPtr %08X\n", NvmeController->AdminCompletionQueueTailPtr));
        } else {
            TRACE((-1, "Queue1SubmissionQueueHeadPtr %08X\n", NvmeController->Queue1SubmissionQueueHeadPtr));
            TRACE((-1, "Queue1SubmissionQueueTailPtr %08X\n", NvmeController->Queue1SubmissionQueueTailPtr));
            TRACE((-1, "Queue1CompletionQueueHeadPtr %08X\n", NvmeController->Queue1CompletionQueueHeadPtr));
            TRACE((-1, "Queue1CompletionQueueTailPtr %08X\n", NvmeController->Queue1CompletionQueueTailPtr));
        }
    }
#endif
    
    // Update o/p buffer
    MemCpy ((VOID *)CmdCompletionData, pCmdCompletionData, sizeof(COMPLETION_QUEUE_ENTRY));
    NvmeCmdWrapper->AdminOrNVMCmdSet ? NvmeController->CommandIdentifierAdmin++ : NvmeController->CommandIdentifierQueue1++;
    
    return Status;
    
}

//**********************************************************************
//<AMI_PHDR_START>
//
// Procedure:   RecreateAllQueues
//
// Description: Delete Admin and other Completion/Submission queue and create it back again.
//
// Input:
//  IN  AMI_NVME_CONTROLLER_PROTOCOL        *NvmeController
//
// Output:
//  EFI_STATUS
//
// Modified:
//      
// Referrals: 
//
// Notes: This procedure will be called if the queue gets filled up. This situation shouldn't generally happen as each cmd
// is completed in our case. So both Head and Tail should point to the same location before and after cmd is executed.
// One possibility for calling this routine will be when the cmd doesn't get completed and Completion Queue doesn't get updated
// by the controller. Also any Set Feature cmd that was issued during initilization should be re-issued here.
//
//
//<AMI_PHDR_END>
//**********************************************************************
EFI_STATUS
RecreateAllQueues (
    IN  AMI_NVME_CONTROLLER_PROTOCOL        *NvmeController
)
{
    
    EFI_STATUS      Status = EFI_SUCCESS;
    UINT32          ProgramCC = 0;
    UINT32          Delay;


    // In SMM, this function is not supported
    if (NvmeController->NvmeInSmm) {
        return EFI_DEVICE_ERROR;
    }

#if  NVME_VERBOSE_PRINT
    if (!NvmeController->NvmeInSmm) {
        TRACE((-1, "Recreate Admin Queue : "));
    }
#endif
 
    ProgramCC = CONTROLLER_REG32(NvmeController->NvmeBarOffset, Offset_CC);
    
    // Check if the controller is already running. If yes stop it.
    Delay = NvmeController->TimeOut * 500;
    if (CONTROLLER_REG32(NvmeController->NvmeBarOffset, Offset_CC) & 0x1) {
        
        //  Clear Control register
        CONTROLLER_REG32 (NvmeController->NvmeBarOffset, Offset_CC) = 0;
        do {
            if (!(CONTROLLER_REG32(NvmeController->NvmeBarOffset, Offset_CSTS) & 0x1)) {
                break;
            }

            if (!NvmeController->NvmeInSmm) {
                pBS->Stall(1000); // 1msec delay
            }
            else {
                SmmStall (1000);
            }

        } while (--Delay);
        
    }
    
    if (!Delay) {
        goto  RecreateAllQueues_Error;  
    }
    
    // Program Admin Queue Size and Base Address
    CONTROLLER_REG32(NvmeController->NvmeBarOffset, Offset_Aqa) =  
             (UINT32)(Shl64((NvmeController->AdminCompletionQueueSize - 1), 16) + (NvmeController->AdminSubmissionQueueSize - 1));
     
    CONTROLLER_REG32(NvmeController->NvmeBarOffset, Offset_Asq) = 
             (UINT32) NvmeController->AdminSubmissionQueue;
     
    CONTROLLER_REG32(NvmeController->NvmeBarOffset, Offset_Asq + 4) =  
             (UINT32)Shr64(NvmeController->AdminSubmissionQueue, 32);
     
    CONTROLLER_REG32(NvmeController->NvmeBarOffset, Offset_Acq) =  
             (UINT32)NvmeController->AdminCompletionQueue;
     
    CONTROLLER_REG32(NvmeController->NvmeBarOffset, Offset_Acq + 4) =  
             (UINT32)Shr64(NvmeController->AdminCompletionQueue, 32);

    NvmeController->AdminPhaseTag = FALSE;

    // Enable Controller
    CONTROLLER_REG32(NvmeController->NvmeBarOffset, Offset_CC) = (ProgramCC | 1);
     
    // Wait for the controller to get ready
    // Check if the cobtroller is already running. If yes stop it.
    Delay = NvmeController->TimeOut * 500;
    do {
        if ((CONTROLLER_REG32(NvmeController->NvmeBarOffset, Offset_CSTS) & 0x1)) {
            break;
        }

        if (!NvmeController->NvmeInSmm) {
            pBS->Stall(1000); // 1msec delay
        }
        else {
            SmmStall (1000);
        }

    } while (--Delay);
         
RecreateAllQueues_Error:  
   
    if (!Delay) {
        Status = EFI_DEVICE_ERROR;

#if  NVME_VERBOSE_PRINT
    if (!NvmeController->NvmeInSmm) {
        TRACE((-1, "Status  %r\n", Status));
    }
#endif

        return Status;
    }
    
    NvmeController->AdminSubmissionQueueHeadPtr = 0;
    NvmeController->AdminSubmissionQueueTailPtr = 0;
    NvmeController->AdminCompletionQueueHeadPtr = 0;
    NvmeController->AdminCompletionQueueTailPtr = 0;
    NvmeController->AdminPhaseTag = FALSE;
    
    if (!NvmeController->ReInitializingQueue1) {
        Status = RecreateQueue1 (NvmeController);
    }
    
    return Status;
}

//**********************************************************************
//<AMI_PHDR_START>
//
// Procedure:   RecreateQueue1
//
// Description: Delete Completion and Submission queue and create it back again.
//
// Input:
//  IN  AMI_NVME_CONTROLLER_PROTOCOL        *NvmeController
//
// Output:
//  EFI_STATUS
//
// Modified:
//      
// Referrals: 
//
// Notes: This procedure will be called if the queue gets filled up. This situation shouldn't generally happen as each cmd
// is completed in our case. So both Head and Tail should point to the same location before and after cmd is executed.
// One possibility for calling this routine will be when the cmd doesn't get completed and Completion Queue doesn't get updated
// by the controller. Can be called recursively.
//
//<AMI_PHDR_END>
//**********************************************************************
EFI_STATUS
RecreateQueue1 (
    IN  AMI_NVME_CONTROLLER_PROTOCOL        *NvmeController
)
{
    
    EFI_STATUS                      Status;
    NVME_COMMAND_WRAPPER            *NvmeCmdWrapper;
    COMPLETION_QUEUE_ENTRY          CompletionData;

    // In SMM, this function not supported
    if (NvmeController->NvmeInSmm) {
        return EFI_DEVICE_ERROR;
    }
    
#if  NVME_VERBOSE_PRINT
    if (!NvmeController->NvmeInSmm) {
        TRACE((-1, "Recreate Queue1 : "));
    }
#endif
    
    NvmeController->ReInitializingQueue1 = TRUE;
    
    Status = pBS->AllocatePool (
                  EfiBootServicesData,
                  sizeof(NVME_COMMAND_WRAPPER),
                  (VOID**)&NvmeCmdWrapper
                  );
    
    if (EFI_ERROR(Status)) {
        NvmeController->ReInitializingQueue1 = FALSE;
        return Status;
    }
    
    // Clear memory
    MemSet(NvmeCmdWrapper, sizeof(NVME_COMMAND_WRAPPER), 0);
    
    // Build NVME command to delete Submission queue
    NvmeCmdWrapper->NvmCmd.CMD0.Opcode = DELETE_IO_SUBMISSION_QUEUE;
    NvmeCmdWrapper->NvmCmd.CMD0.CommandIdentifier = NvmeController->CommandIdentifierAdmin;
    NvmeCmdWrapper->NvmCmd.CDW10 = NvmeController->NVMQueueNumber;
    
    NvmeCmdWrapper->AdminOrNVMCmdSet = TRUE;
    NvmeCmdWrapper->SQIdentifier = 0;           // Queue 0 for Admin cmds
    NvmeCmdWrapper->CmdTimeOut = 1000;
    
    Status = ExecuteNvmeCmd (NvmeController, NvmeCmdWrapper, &CompletionData);
    if (EFI_ERROR(Status)) {
        goto RecreateQueue1_Error;
    }
    
    // Build NVME command to delete Completion queue
    NvmeCmdWrapper->NvmCmd.CMD0.Opcode = DELETE_IO_COMPLETION_QUEUE;
    NvmeCmdWrapper->NvmCmd.CMD0.CommandIdentifier = NvmeController->CommandIdentifierAdmin;
    NvmeCmdWrapper->NvmCmd.CDW10 = NvmeController->NVMQueueNumber;
    
    NvmeCmdWrapper->AdminOrNVMCmdSet = TRUE;
    NvmeCmdWrapper->SQIdentifier = 0;           // Queue 0 for Admin cmds
    NvmeCmdWrapper->CmdTimeOut = 1000;
    
    Status = ExecuteNvmeCmd (NvmeController, NvmeCmdWrapper, &CompletionData);
    if (EFI_ERROR(Status)) {
        goto RecreateQueue1_Error;
    }
    
    // Create Submission and Completion Queue1
    Status  = CreateAdditionalSubmissionCompletionQueue(
                                NvmeController, 
                                NvmeCmdWrapper, 
                                NvmeController->NVMQueueNumber, 
                                NvmeController->Queue1SubmissionQueueSize
                                );
    
RecreateQueue1_Error:

    NvmeController->ReInitializingQueue1 = FALSE;
    
    pBS->FreePool (NvmeCmdWrapper);
    
#if  NVME_VERBOSE_PRINT
    if (!NvmeController->NvmeInSmm) {
        TRACE((-1, "Status %r\n", Status));
    }
#endif
        
    return Status;
}

//**********************************************************************
//<AMI_PHDR_START>
//
// Procedure:   PrintCommandCompletionData
//
// Description: Prints the cmd completion status
//
// Input:
//      IN  COMPLETION_QUEUE_ENTRY  *pCmdCompletionData
//
// Output:
//      NONE
//
// Modified:
//      
// Referrals: 
//
// Notes:   The amount of data that will get printed can be controlled 
//          using DEBUG_ERROR_LEVEL_MASK SDL token.
//          Make sure PcdDebugPrintErrorLevel is properly cloned and set to 
//          PcdsPatchableInModule in the project.
//
//<AMI_PHDR_END>
//**********************************************************************

VOID
PrintCommandCompletionData (
    IN  COMPLETION_QUEUE_ENTRY  *pCmdCompletionData
)
{
    
#if  NVME_VERBOSE_PRINT
    // Fig 25 NVM Express 1.1 spec
    // Print Completion Cmd Data
    TRACE((-1, "Completion Queue DW2                      : %08X\n", *((UINT32 *)pCmdCompletionData + 2)));
    TRACE((-1, "Completion Queue DW3                      : %08X\n", *((UINT32 *)pCmdCompletionData + 3)));
    TRACE((-1, "Completion Queue DW0                      : %08X\n", pCmdCompletionData->DW0));
    TRACE((-1, "Completion Queue Reserved                 : %08X\n", pCmdCompletionData->DW1));
#endif
    
}


//**********************************************************************
//<AMI_PHDR_START>
//
// Procedure:   PrintNvmeCmdWrapper
//
// Description: Prints Nvme cmd parameters
//
// Input:
//      NVME_COMMAND_WRAPPER    *NvmeCmdWrapper
//
// Output:
//      NONE
//
// Modified:
//      
// Referrals: 
//
// Notes:   The amount of data that will get printed can be controlled 
//          using DEBUG_ERROR_LEVEL_MASK SDL token.
//          Make sure PcdDebugPrintErrorLevel is properly cloned and set to 
//          PcdsPatchableInModule in the project.
//
//<AMI_PHDR_END>
//**********************************************************************
VOID
PrintNvmeCmdWrapper (
    NVME_COMMAND_WRAPPER    *NvmeCmdWrapper
)
{

    
#if  NVME_VERBOSE_PRINT    
    TRACE((-1,"\nCMD DW0                                  : %08X\n", *(UINT32 *)&(NvmeCmdWrapper->NvmCmd)));
    TRACE((-1, "MPTR                                      : %016lX\n", NvmeCmdWrapper->NvmCmd.MPTR));
    TRACE((-1, "PRP1                                      : %016lX\n", NvmeCmdWrapper->NvmCmd.PRP1));
    TRACE((-1, "PRP2                                      : %016lX\n", NvmeCmdWrapper->NvmCmd.PRP2));
    TRACE((-1, "CDW10                                     : %08X\n",  NvmeCmdWrapper->NvmCmd.CDW10));
    TRACE((-1, "CDW11                                     : %08X\n",  NvmeCmdWrapper->NvmCmd.CDW11));
    TRACE((-1, "CDW12                                     : %08X\n",  NvmeCmdWrapper->NvmCmd.CDW12));
    TRACE((-1, "CDW13                                     : %08X\n",  NvmeCmdWrapper->NvmCmd.CDW13));
    TRACE((-1, "CDW14                                     : %08X\n",  NvmeCmdWrapper->NvmCmd.CDW14));
    TRACE((-1, "CDW15                                     : %08X\n",  NvmeCmdWrapper->NvmCmd.CDW15));
    TRACE((-1, "Cmd sent to Queue                         : %08X\n",  NvmeCmdWrapper->SQIdentifier));
#endif   
    
}

//**********************************************************************
//<AMI_PHDR_START>
// Procedure:   UnicodeStrToAsciiStr
//
// Description: This function converts the content of the Unicode string Source
//              to the ASCII string Destination by copying the lower 8 bits of
//              each Unicode character and returns Destination
//
// Input:       Source        A pointer to a Null-terminated Unicode string.
//              Destination   A pointer to a Null-terminated ASCII string.
//
// Output:      None
//
//<AMI_PHDR_END>
//**********************************************************************
CHAR8* 
UnicodeStrToAsciiStr (
  IN      CONST CHAR16              *Source,
  OUT     CHAR8                     *Destination
  )
{
  CHAR8                               *ReturnValue;
  UINTN                               TempReturnValue;
  UINTN                               TempSource;
  
  ASSERT (Destination != NULL);
  //
  // ASSERT if Source is long than PcdMaximumUnicodeStringLength.
  // Length tests are performed inside StrLen().
  //
  TempSource = (Wcslen ((CHAR16 *)Source) + 1) * sizeof (*Source);
  ASSERT (TempSource != 0);
  //
  // Source and Destination should not overlap
  //
  ASSERT ((UINTN) ((CHAR16 *) Destination -  Source) > Wcslen ((CHAR16 *)Source));
  ASSERT ((UINTN) ((CHAR8 *) Source - Destination) > Wcslen ((CHAR16 *)Source));


  ReturnValue = Destination;
  while (*Source != '\0') {
    //
    // If any Unicode characters in Source contain 
    // non-zero value in the upper 8 bits, then ASSERT().
    //
    ASSERT (*Source < 0x100);
    *(Destination++) = (CHAR8) *(Source++);
  }

  *Destination = '\0';

  //
  // ASSERT Original Destination is less long than PcdMaximumAsciiStringLength.
  // Length tests are performed inside AsciiStrLen().
  //
  TempReturnValue = (Strlen((CHAR8 *)ReturnValue) + 1) * sizeof (*ReturnValue);
  ASSERT (TempReturnValue!= 0);

  return ReturnValue;
}

//**********************************************************************
//**********************************************************************
//**                                                                  **
//**        (C)Copyright 1985-2014, American Megatrends, Inc.         **
//**                                                                  **
//**                       All Rights Reserved.                       **
//**                                                                  **
//**         5555 Oakbrook Pkwy, Suite 200, Norcross, GA 30093        **
//**                                                                  **
//**                       Phone: (770)-246-8600                      **
//**                                                                  **
//**********************************************************************
//**********************************************************************
