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
// $Header: /Alaska/SOURCE/Modules/NVMe/NvmeSmm/NvmeSmm.c 10    12/08/16 4:21a Karthikar $
//
// $Revision: 10 $
//
// $Date: 12/08/16 4:21a $
//**********************************************************************
// Revision History
// ----------------
// $Log: /Alaska/SOURCE/Modules/NVMe/NvmeSmm/NvmeSmm.c $
// 
// 10    12/08/16 4:21a Karthikar
// [TAG]  		EIP307568
// [Category]  	Bug Fix
// [Symptom]  	Legacy Installation and booting fails in
// (INT)_a_4.6.5.5_NVMe_006
// [RootCause]  	Since this NvmeSmm_Support token is not included in
// Token.h, TransferNvmeDataToSmram() dint get control.
// [Solution]  	Added NvmeSmm_Support token in Token.h
// [Files]  		NvmeBus.c,NvmeSmm.c,NvmeSmm.sdl
// 
// 9     11/03/16 5:29a Karthikar
// [TAG]  		EIP300640 
// [Category]  	Improvement
// [Description]  	NvmeSmm: Security vulnerability in the NvmeSmm driver
// 
// 8     2/03/16 2:13a Lavanyap
// [TAG]  		EIP254133
// [Category]  	New Feature
// [Description]  	Modify NVMe driver to avoid repeated FALSE THREAT issue
// report in Security Advisory.
// [Files]  		NvmeSmm.c
// 
// 7     2/02/16 1:24a Karthikar
// [TAG]  		EIP254245
// [Category]  	Bug Fix
// [Symptom]  	Static code analysis issues found in Aptio4 Nvme module
// [RootCause]  	In if condition variable is intialized without proper
// braces.
// [Solution]  	                     Removed wrong variable initialization
// from if condition.
// [Files]  		NvmeSmm.c
// 
// 6     5/14/15 2:39a Karthikar
// [TAG]  		EIP216763 
// [Category]  	Improvement
// [Description]  	Update the Aptio 4.x Nvme driver to Aptio 5.x Nvme
// driver Label 05
// [Files]  		Nvme.mak,NvmeBus.c, NvmeBus.h, NvmeController.c,
// NvmePassthru.c,NvmePassthru.h, NvmeSmm.c, NvmExpressPassThru.h,
// PDiskInfo.h
// 
// 5     4/20/15 8:52a Anbuprakashp
// [TAG]  		EIP214300
// [Category]  	Bug Fix
// [Severity]  	Normal
// [Symptom]  	Nvme device with legacy OS can not resume from S4
// [RootCause]  	In Aptio 4.x NvmeSmm Driver, Media buffer in
// EFI_BLOCK_IO_MEDIA holds invalid memory address( i.e. The memory is not
// allocated in SMRAM ).
// [Solution]  	Memory for Media buffer(EFI_BLOCK_IO_MEDIA) is allocated
// in SMRAM region
// [Files]  		NvmeSmm.c
// 
// 4     4/08/15 10:07a Anbuprakashp
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
// 3     12/10/14 5:14a Lavanyap
// [TAG]  		EIP185327
// [Category]  	Improvement
// [Description]  	Security Enhancement for SMIHandler in Aptio4.x NVMe
// Driver
// [Files]  		NvmeSmm.mak, NvmeSmm.c, NvmeSmm.h
// 
// 2     9/23/14 2:32a Anandakrishnanl
// [TAG]  		EIP180861
// [Category]  	Improvement
// [Description]  	
// Add Legacy Boot support in Aptio 4.x Nvme driver - NON PI 1.2 Support
// [Files]  		NvmeBus.c
// NvmeBus.h
// NvmeSmm.c
// NvmeSmm.h
// NvmeSmm.dxs
// NvmeSmm.sdl
// 
// 1     9/04/14 7:54a Anandakrishnanl
// [TAG]  		EIP180861
// [Category]  	Improvement
// [Description]  	Legacy Boot support in Aptio 4.x Nvme driver
// [Files]  		NvmeSmm.cif
// NvmeSmm.mak
// NvmeSmm.dxs
// NvmeSmm.sdl
// NvmeSmm.c
// NvmeSmm.h
// NvmeDef.h
// 
//**********************************************************************
//**********************************************************************
//<AMI_FHDR_START>
//
// Name:        NvmeSmm.c
//
// Description: Nvme SMM driver to handle the Nvme device access
//
//<AMI_FHDR_END>
//**********************************************************************

#include "NvmeSmm.h"

EFI_SMM_BASE2_PROTOCOL          *gSmmBase2;
EFI_SMM_SYSTEM_TABLE2           *pSmst2;
NVME_GLOBAL_DATA                *gNvmeData;
AMI_NVME_CONTROLLER_PROTOCOL    *gNvmeController[MAX_NVME_DEVICES] = {0};
BOOLEAN                         gFirstAPICall = FALSE;

static EFI_GUID gAmiSmmNvmeCommunicationGuid 	    = AMI_SMM_NVME_COMMUNICATION_GUID;

// ]ApiTable - NVMe API Function Dispatch Table

API_FUNC NvmeMassApiTable[] = {
    NvmeMassAPIGetDeviceInformation,    // Nvme Mass API Sub-Func 00h
    NvmeMassAPIGetDeviceGeometry,       // Nvme Mass API Sub-Func 01h
    NvmeMassAPIResetDevice,             // Nvme Mass API Sub-Func 02h
    NvmeMassAPIReadDevice,              // Nvme Mass API Sub-Func 03h
    NvmeMassAPIWriteDevice,             // Nvme Mass API Sub-Func 04h
    NvmeMassAPIPass,                    // Nvme Mass API Sub-Func 05h VerifyDevice
    NvmeMassAPIPass,                    // Nvme Mass API Sub-Func 06h FormatDevice
    NvmeMassAPINotSupported,            // Nvme Mass API Sub-Func 07h CommandPassThru
    NvmeMassAPINotSupported,            // Nvme BIOS API function 08h AssignDriveNumber
    NvmeMassAPINotSupported,            // Nvme BIOS API function 09h CheckDevStatus
    NvmeMassAPINotSupported,            // Nvme BIOS API function 0Ah GetDevStatus
    NvmeMassAPINotSupported             // Nvme BIOS API function 0Bh GetDeviceParameters
};

//**********************************************************************
//<AMI_PHDR_START>
//
// Procedure:   ZeroMemorySmm
//
// Description: Clears input Buffer to zero
//
// Input:
//    void     *Buffer
//    UINTN    Size
//
// Output:
//      NONE
//
//<AMI_PHDR_END>
//********************************************************************** 

void
ZeroMemorySmm (
    void     *Buffer,
    UINTN    Size
 )
{
    UINT8   *Ptr;
    Ptr = Buffer;
    while (Size--) {
        *(Ptr++) = 0;
    }
}

//**********************************************************************
//<AMI_PHDR_START>
//
// Procedure:   GetDevEntry
//
// Description: Get the Index# for the DeviceAddress
//
// Input:
//    UINT8                   DeviceAddress,
//    ACTIVE_NAMESPACE_DATA   **ActiveNameSpace
//
// Output:
//      NONE
//
// Modified:
//      
// Referrals: 
//
// Notes:  None  
//
//
//<AMI_PHDR_END>
//**********************************************************************

VOID
GetDevEntry (
    UINT8                   DeviceAddress,
    ACTIVE_NAMESPACE_DATA   **ActiveNameSpace
)
{

    UINT8                           Count;
    EFI_LIST_ENTRY                      *LinkData;
    AMI_NVME_CONTROLLER_PROTOCOL    *NvmeController;
    
    // Locate a free slot to copy the pointer
     for (Count = 0; Count < MAX_NVME_DEVICES; Count++ ){
         if (gNvmeController[Count]) {
             NvmeController = gNvmeController[Count];
             
             if(IsListEmpty(&NvmeController->ActiveNameSpaceList)) {
                 continue;
             } 
             
             for (LinkData = NvmeController->ActiveNameSpaceList.ForwardLink; \
                     LinkData != &NvmeController->ActiveNameSpaceList; 
                     LinkData = LinkData->ForwardLink) {
                 
                 *ActiveNameSpace = _CR(LinkData ,ACTIVE_NAMESPACE_DATA, Link);
                 if ((*ActiveNameSpace)->Int13DeviceAddress == DeviceAddress) {
                     return;
                 }
             }
         }
     }
    
    ActiveNameSpace = NULL;
    return ;

}

//**********************************************************************
//<AMI_PHDR_START>
//
// Procedure:   NvmeMassAPIGetDeviceInformation
//
// Description: Return Device information
//
// Input:
//      NVME_STRUC  *NvmeURP
//
// Output:
//      NONE
//
// Modified:
//      
// Referrals: 
//
// Notes:  None  
//
//
//<AMI_PHDR_END>
//**********************************************************************
VOID
NvmeMassAPIGetDeviceInformation (
    NVME_STRUC  *NvmeURP
)
{

    NvmeURP->bRetValue = NVME_NOT_SUPPORTED;
    return;
    
}

//**********************************************************************
//<AMI_PHDR_START>
//
// Procedure:   NvmeMassAPIGetDeviceGeometry
//
// Description: Return Device Geometry
//
// Input:
//      NVME_STRUC  *NvmeURP
//
// Output:
//      NONE
//
// Modified:
//      
// Referrals: 
//
// Notes:  None  
//
//
//<AMI_PHDR_END>
//**********************************************************************
VOID
NvmeMassAPIGetDeviceGeometry (
    NVME_STRUC  *NvmeURP
)
{
    NvmeURP->bRetValue = NVME_NOT_SUPPORTED;
    return;
}

//**********************************************************************
//<AMI_PHDR_START>
//
// Procedure:   NvmeMassAPIResetDevice
//
// Description: Reset device
//
// Input:
//      NVME_STRUC  *NvmeURP
//
// Output:
//      NONE
//
// Modified:
//      
// Referrals: 
//
// Notes:  None  
//
//
//<AMI_PHDR_END>
//**********************************************************************
VOID
NvmeMassAPIResetDevice (
    NVME_STRUC  *NvmeURP
)
{
    NvmeURP->bRetValue = NVME_NOT_SUPPORTED;
    return;
}

//**********************************************************************
//<AMI_PHDR_START>
//
// Procedure:   NvmeMassAPIReadDevice
//
// Description: Read data from the device
//
// Input:
//      NVME_STRUC  *NvmeURP
//
// Output:
//      NONE
//
// Modified:
//      
// Referrals: 
//
// Notes:  None  
//
//
//<AMI_PHDR_END>
//**********************************************************************
VOID
NvmeMassAPIReadDevice (
    NVME_STRUC  *NvmeURP
)
{
    ACTIVE_NAMESPACE_DATA               *ActiveNameSpace = NULL;
    EFI_STATUS                          Status;
    EFI_LBA                             Lba;
    UINT16                              NumBlks;
    UINT16                              BlksPerTransfer;
    VOID                                *Buffer = NULL;
    VOID                                *ReadBuffer;
    UINTN                               BufferSize;
    BOOLEAN                             UnalignedTransfer = FALSE;
    AMI_NVME_CONTROLLER_PROTOCOL        *NvmeController;
    UINT32                              Offset;
    COMPLETION_QUEUE_ENTRY              *pCmdCompletionData;
    
    GetDevEntry(NvmeURP->ApiData.Read.DeviceAddress, &ActiveNameSpace);
    
    if(ActiveNameSpace == NULL) {
        NvmeURP->bRetValue = NVME_PARAMETER_FAILED;
        return;
    }

    // Validate if input Buffer address is an non-SMRAM region to avoid SMRAM data 
    // corruption through SMI handlers.    
    // NOTE: As DMA transfer isn't supported inside SMM, Buffer validation is not needed for 
    // NVMe. But below validation code is added to avoid repeated Security False Threat reports.

    Status = AmiValidateMemoryBuffer((VOID*)NvmeURP->ApiData.Read.BufferAddress, 
    		                                NvmeURP->ApiData.Read.NumBlks * 
    		                                ActiveNameSpace->NvmeBlockIO.Media->BlockSize );
    if (EFI_ERROR(Status)) {
        NvmeURP->bRetValue = NVME_PARAMETER_FAILED;
        return;
    }

    NvmeController = ActiveNameSpace->NvmeController;
    if (NvmeController->Queue1SubmissionQueueTailPtr == 0xFFFF) {
        Offset = QUEUE_DOORBELL_OFFSET( NvmeController->NVMQueueNumber, 1, NvmeController->DoorBellStride);
        NvmeController->Queue1CompletionQueueHeadPtr = CONTROLLER_REG32(NvmeController->NvmeBarOffset, Offset); 
        NvmeController->Queue1SubmissionQueueHeadPtr = NvmeController->Queue1CompletionQueueHeadPtr;
        NvmeController->Queue1SubmissionQueueTailPtr = NvmeController->Queue1CompletionQueueHeadPtr;
        // Check if there is a roller over
        if (NvmeController->Queue1SubmissionQueueTailPtr >= NvmeController->Queue1SubmissionQueueSize) {
            NvmeController->Queue1SubmissionQueueTailPtr = 0;
        }
        
        // Update the phase tag from the Completion queue
        pCmdCompletionData = (COMPLETION_QUEUE_ENTRY *)NvmeController->Queue1CompletionQueueMappedAddr;
        NvmeController->Queue1PhaseTag = (UINT8)pCmdCompletionData->PhaseTag;
        NvmeController->CommandIdentifierQueue1 = 0;
        NvmeController->CommandIdentifierAdmin = 0;
    }
    
        
    Lba=NvmeURP->ApiData.Read.LBA;
    NumBlks=NvmeURP->ApiData.Read.NumBlks;
   
    (UINT32)Buffer= NvmeURP->ApiData.Read.BufferAddress;

    BlksPerTransfer =  NumBlks;
    ReadBuffer = Buffer;
    
    //If Buffer isn't aligned use internal buffer
    if ((UINTN)NvmeURP->ApiData.Read.BufferAddress & ((1 << ActiveNameSpace->NvmeBlockIO.Media->IoAlign)-1)) {
        BlksPerTransfer = 1;
        ReadBuffer = NvmeController->LegacyNvmeBuffer;
        UnalignedTransfer = TRUE;
    }

    BufferSize = BlksPerTransfer * ActiveNameSpace->NvmeBlockIO.Media->BlockSize;
    
    for (  ;  NumBlks; NumBlks -= BlksPerTransfer){
        Status = NvmeReadWriteBlocks (ActiveNameSpace, ActiveNameSpace->NvmeBlockIO.Media->MediaId, Lba, BufferSize, ReadBuffer, NULL, NVME_READ);
        if (EFI_ERROR(Status)) {
            break;
        }
        if  (UnalignedTransfer) {
            MemCpy (Buffer, ReadBuffer, BufferSize); 
        }
        (UINTN)Buffer = (UINTN)Buffer + BufferSize;
        Lba += BlksPerTransfer;

    }
   
    if (EFI_ERROR(Status)) {
        NvmeURP->bRetValue = NVME_READ_ERR;
    } else {
        NvmeURP->bRetValue = NVME_SUCCESS;
    }
    
    return;
    
}

//**********************************************************************
//<AMI_PHDR_START>
//
// Procedure:   NvmeMassAPIWriteDevice
//
// Description: Write data to the device
//
// Input:
//      NVME_STRUC  *NvmeURP
//
// Output:
//      NONE
//
// Modified:
//      
// Referrals: 
//
// Notes:  None  
//
//
//<AMI_PHDR_END>
//**********************************************************************
VOID
NvmeMassAPIWriteDevice (
    NVME_STRUC  *NvmeURP
)
{
    ACTIVE_NAMESPACE_DATA               *ActiveNameSpace = NULL;
    EFI_STATUS                          Status;
    EFI_LBA                             Lba;
    UINT16                              NumBlks;
    UINT16                              BlksPerTransfer;
    VOID                                *Buffer = NULL;
    VOID                                *ReadBuffer;
    UINTN                               BufferSize;
    BOOLEAN                             UnalignedTransfer = FALSE;
    AMI_NVME_CONTROLLER_PROTOCOL        *NvmeController;
    UINT32                              Offset;
    COMPLETION_QUEUE_ENTRY              *pCmdCompletionData;
    
    GetDevEntry(NvmeURP->ApiData.Read.DeviceAddress, &ActiveNameSpace);
    
    if(ActiveNameSpace == NULL) {
        NvmeURP->bRetValue = NVME_PARAMETER_FAILED;
        return;
    }

    // Validate if input Buffer address is an non-SMRAM region to avoid SMRAM data 
    // corruption through SMI handlers.    
    // NOTE: As DMA transfer isn't supported inside SMM, Buffer validation is not needed for 
    // NVMe. But below validation code is added to avoid repeated Security False Threat reports.

    Status = AmiValidateMemoryBuffer((VOID*)NvmeURP->ApiData.Read.BufferAddress, 
    		                                NvmeURP->ApiData.Read.NumBlks * 
    		                                ActiveNameSpace->NvmeBlockIO.Media->BlockSize );
    if (EFI_ERROR(Status)) {
        NvmeURP->bRetValue = NVME_PARAMETER_FAILED;
        return;
    }
    
    NvmeController = ActiveNameSpace->NvmeController;
    if (NvmeController->Queue1SubmissionQueueTailPtr == 0xFFFF) {
        Offset = QUEUE_DOORBELL_OFFSET( NvmeController->NVMQueueNumber, 1, NvmeController->DoorBellStride);
        NvmeController->Queue1CompletionQueueHeadPtr = CONTROLLER_REG32(NvmeController->NvmeBarOffset, Offset); 
        NvmeController->Queue1SubmissionQueueHeadPtr = NvmeController->Queue1CompletionQueueHeadPtr;
        NvmeController->Queue1SubmissionQueueTailPtr = NvmeController->Queue1CompletionQueueHeadPtr;
        // Check if there is a roller over
        if (NvmeController->Queue1SubmissionQueueTailPtr >= NvmeController->Queue1SubmissionQueueSize) {
            NvmeController->Queue1SubmissionQueueTailPtr = 0;
        }
        
        // Update the phase tag from the Completion queue
        pCmdCompletionData = (COMPLETION_QUEUE_ENTRY *)NvmeController->Queue1CompletionQueueMappedAddr;
        NvmeController->Queue1PhaseTag = (UINT8)pCmdCompletionData->PhaseTag;
        NvmeController->CommandIdentifierQueue1 = 0;
        NvmeController->CommandIdentifierAdmin = 0;
        
    }
    
        
    Lba=NvmeURP->ApiData.Read.LBA;
    NumBlks=NvmeURP->ApiData.Read.NumBlks;
   
    (UINT32)Buffer= NvmeURP->ApiData.Read.BufferAddress;

    BlksPerTransfer =  NumBlks;
    ReadBuffer = Buffer;
    
    //If Buffer isn't aligned use internal buffer
    if ((UINTN)NvmeURP->ApiData.Read.BufferAddress & ((1 << ActiveNameSpace->NvmeBlockIO.Media->IoAlign)-1)) {
        BlksPerTransfer = 1;
        ReadBuffer = NvmeController->LegacyNvmeBuffer;
        UnalignedTransfer = TRUE;
    }

    BufferSize = BlksPerTransfer * ActiveNameSpace->NvmeBlockIO.Media->BlockSize;
    
    for (  ;  NumBlks; NumBlks -= BlksPerTransfer){
        
        if  (UnalignedTransfer) {
            MemCpy (ReadBuffer, Buffer, BufferSize); 
        }
        
        Status = NvmeReadWriteBlocks (ActiveNameSpace, ActiveNameSpace->NvmeBlockIO.Media->MediaId, Lba, BufferSize, ReadBuffer, NULL, NVME_WRITE);
        if (EFI_ERROR(Status)) {
            break;
        }

        (UINTN)Buffer = (UINTN)Buffer + BufferSize;
        Lba += BlksPerTransfer;

    }
   
    if (EFI_ERROR(Status)) {
        NvmeURP->bRetValue = NVME_WRITE_ERR;
    }
    else {
        NvmeURP->bRetValue = NVME_SUCCESS;
    }
    
    return;
    
}

//**********************************************************************
//<AMI_PHDR_START>
//
// Procedure:   NvmeMassAPIPass
//
// Description: Dummy handler to return NVME_SUCCESS
//
// Input:
//      NVME_STRUC  *NvmeURP
//
// Output:
//      NONE
//
// Modified:
//      
// Referrals: 
//
// Notes:  None  
//
//
//<AMI_PHDR_END>
//**********************************************************************
VOID
NvmeMassAPIPass(
    NVME_STRUC *NvmeURP
)
{

    NvmeURP->bRetValue = NVME_SUCCESS;
    return;

}

//**********************************************************************
//<AMI_PHDR_START>
//
// Procedure:   NvmeMassAPINotSupported
//
// Description: Dummy handler to return NVME_NOT_SUPPORTED
//
// Input:
//      NVME_STRUC  *NvmeURP
//
// Output:
//      NONE
//
// Modified:
//      
// Referrals: 
//
// Notes:  None  
//
//
//<AMI_PHDR_END>
//**********************************************************************
VOID
NvmeMassAPINotSupported (
    NVME_STRUC  *NvmeURP
)
{

    NvmeURP->bRetValue = NVME_NOT_SUPPORTED;
    return;

}

//**********************************************************************
//<AMI_PHDR_START>
//
// Procedure:   NvmeInitSmmData
//
// Description: Initialize NVMe SMM data area
//
// Input:
//
//
//
// Output:
//      EFI_STATUS
//
// Modified:
//      
// Referrals: 
//
// Notes:  None  
//
//
//<AMI_PHDR_END>
//**********************************************************************
#if defined(PI_SPECIFICATION_VERSION) && (PI_SPECIFICATION_VERSION >= 0x00010014)
EFI_STATUS
EFIAPI
NvmeInitSmmData (
    IN  EFI_HANDLE  DispatchHandle,
    IN  CONST   VOID    *Context        OPTIONAL,
    IN  OUT     VOID    *CommBuffer     OPTIONAL,
    IN  OUT     UINTN   *CommBufferSize OPTIONAL
  )
#else
EFI_STATUS 
NvmeInitSmmData (
    IN  EFI_HANDLE                      DispatchHandle,
    IN  EFI_SMM_SW_DISPATCH_CONTEXT     *DispatchContext 
)
#endif
{
    EFI_STATUS                      Status = EFI_SUCCESS;
    ACTIVE_NAMESPACE_DATA           *OrgActiveNameSpace;
    ACTIVE_NAMESPACE_DATA           *ActiveNameSpace;
    AMI_NVME_CONTROLLER_PROTOCOL    *NvmeController;
    AMI_NVME_CONTROLLER_PROTOCOL    *OrgNvmeController;
    UINT8                           Count;
    EFI_LIST_ENTRY                  *LinkData;
    UINTN                           NvmeComBuffer = 0;
    static EFI_GUID                 gNvmeSmmGuid = NVME_SMM_GUID;
    UINTN                           VariableSize = sizeof(UINTN);
    EFI_BLOCK_IO_MEDIA              *Media = NULL;
    
    // After the first API call is invoked, don't initialize SMM data area. This is an additional
    // Security check so that data won't get corrupted.
    if (gFirstAPICall) {
        return EFI_SUCCESS;
    }
#if defined(PI_SPECIFICATION_VERSION) && (PI_SPECIFICATION_VERSION >= 0x00010014)
    
    // If input is invalid, stop processing this SMI
    if (CommBuffer == NULL || CommBufferSize == NULL) {
        return EFI_SUCCESS;
    }
    (UINTN)OrgNvmeController = *(UINTN *)CommBuffer;
#else

    Status = pRS->GetVariable ( L"NvmeSmmBuffer", 
                                &gNvmeSmmGuid, 
                                NULL, 
                                &VariableSize, 
                                &NvmeComBuffer );

//    TRACE((-1, "NvmeComBuffer in  NvmeInitSmmData = %x\n", NvmeComBuffer));

    (UINTN)OrgNvmeController = NvmeComBuffer;

#endif
    
            
    // Locate a free slot to copy the pointer
     for (Count = 0; Count < MAX_NVME_DEVICES; Count++ ){
         if (!gNvmeController[Count]) {
             break;
         }
     }
     
     if (Count == MAX_NVME_DEVICES) {
         return EFI_OUT_OF_RESOURCES;
     }

#if defined(PI_SPECIFICATION_VERSION) && (PI_SPECIFICATION_VERSION >= 0x00010014)     
    Status = pSmst2->SmmAllocatePool ( 
#else
    Status = pSmst->SmmAllocatePool ( 
#endif
                                EfiRuntimeServicesData, 
                                sizeof (AMI_NVME_CONTROLLER_PROTOCOL),
                                (VOID**)&NvmeController);
    ASSERT_EFI_ERROR(Status);
    
    // Copy input NvmeController passed in OrgNvmeController into SMM
    MemCpy ((VOID *)NvmeController, OrgNvmeController, sizeof (AMI_NVME_CONTROLLER_PROTOCOL));
    
    
    // Copy IDENTIFY_CONTROLLER_DATA
#if defined(PI_SPECIFICATION_VERSION) && (PI_SPECIFICATION_VERSION >= 0x00010014)     
    Status = pSmst2->SmmAllocatePool ( 
#else
    Status = pSmst->SmmAllocatePool ( 
#endif
                                EfiRuntimeServicesData, 
                                sizeof (IDENTIFY_CONTROLLER_DATA),
                                (VOID**)&(NvmeController->IdentifyControllerData));
    ASSERT_EFI_ERROR(Status);
    
    MemCpy (NvmeController->IdentifyControllerData, OrgNvmeController->IdentifyControllerData, sizeof(IDENTIFY_CONTROLLER_DATA));
    
    gNvmeController[Count] = NvmeController;
 
    
    // Initialize some of the pointers to NULL which aren't applicable during runtime
    NvmeController->PciIO = NULL;
    NvmeController->NvmeInSmm = TRUE;
    NvmeController->Queue1SubmissionQueueTailPtr = 0xFFFF;
    
    InitializeListHead (&NvmeController->ActiveNameSpaceList);
    
#if defined(PI_SPECIFICATION_VERSION) && (PI_SPECIFICATION_VERSION >= 0x00010014)     
    Status = pSmst2->SmmAllocatePool ( 
#else
    Status = pSmst->SmmAllocatePool ( 
#endif
                              EfiRuntimeServicesData, 
                              sizeof (NVME_COMMAND_WRAPPER),
                              (VOID**)&(NvmeController->NvmeCmdWrapper));
    
    // Clear memory
    ZeroMemorySmm (NvmeController->NvmeCmdWrapper, sizeof(NVME_COMMAND_WRAPPER));
    
    // use original NVMe buffer for this as original address value is used.
    // Update the NvmeController pointer inside ActiveNameSpace
    for (LinkData = OrgNvmeController->ActiveNameSpaceList.ForwardLink; 
            LinkData != &OrgNvmeController->ActiveNameSpaceList; 
            LinkData = LinkData->ForwardLink) {
    
        OrgActiveNameSpace = _CR(LinkData ,ACTIVE_NAMESPACE_DATA, Link);
        
#if defined(PI_SPECIFICATION_VERSION) && (PI_SPECIFICATION_VERSION >= 0x00010014)
        Status = pSmst2->SmmAllocatePool ( 
#else
        Status = pSmst->SmmAllocatePool ( 
#endif
                                  EfiRuntimeServicesData, 
                                  sizeof (ACTIVE_NAMESPACE_DATA),
                                  (VOID**)&(ActiveNameSpace));
        if(EFI_ERROR(Status)) {
            ASSERT_EFI_ERROR(Status);
            return Status;
        }
        
        MemCpy (ActiveNameSpace, OrgActiveNameSpace, sizeof(ACTIVE_NAMESPACE_DATA));
        
        ActiveNameSpace->NvmeController = NvmeController;
        ActiveNameSpace->EfiDevicePath = NULL;
        ActiveNameSpace->UDeviceName = NULL;

#if defined(PI_SPECIFICATION_VERSION) && (PI_SPECIFICATION_VERSION >= 0x00010014)
        Status = pSmst2->SmmAllocatePool (
#else
        Status = pSmst->SmmAllocatePool ( 
#endif
                                  EfiRuntimeServicesData, 
                                  sizeof (EFI_BLOCK_IO_MEDIA),
                                  (VOID**)&(Media) );
        if(EFI_ERROR(Status)) {
            ASSERT_EFI_ERROR(Status);
            return Status;
        }

        MemCpy ( Media, OrgActiveNameSpace->NvmeBlockIO.Media, sizeof(EFI_BLOCK_IO_MEDIA) );
        ActiveNameSpace->NvmeBlockIO.Media = Media;

        InsertTailList (&NvmeController->ActiveNameSpaceList, &ActiveNameSpace->Link);
        
    }

    return Status;
    
}

//**********************************************************************
//<AMI_PHDR_START>
//
// Procedure:   NvmeSWSMIHandler
//
// Description: Handle SWSMI generated from NVMe CSM16 module 
//
// Input:
//
//
// Output:
//      EFI_STATUS
//
// Modified:
//      
// Referrals: 
//
// Notes:  None  
//
//
//<AMI_PHDR_END>
//**********************************************************************
#if defined(PI_SPECIFICATION_VERSION) && (PI_SPECIFICATION_VERSION >= 0x00010014)
EFI_STATUS
NvmeSWSMIHandler (
    IN  EFI_HANDLE      DispatchHandle,
    IN  CONST   VOID    *DispatchContext OPTIONAL,
    IN  OUT     VOID    *CommBuffer OPTIONAL,
    IN  OUT     UINTN   *CommBufferSize OPTIONAL
)
#else
EFI_STATUS
NvmeSWSMIHandler (
    IN  EFI_HANDLE                      DispatchHandle,
    IN  EFI_SMM_SW_DISPATCH_CONTEXT     *DispatchContext 
)
#endif
{
    EFI_STATUS  Status = EFI_SUCCESS;
    NVME_STRUC  *NvmeURP=NULL;
    UINT8       bFuncIndex;
    UINT8       bNumberOfFunctions;
    UINT16      EbdaSeg;

    gFirstAPICall = TRUE;
 
    //
    // Get the fpURP pointer from EBDA
    //

    EbdaSeg = *((UINT16*)0x40E);
    NvmeURP = *(NVME_STRUC**)(UINTN)(((UINT32)EbdaSeg << 4) + NVME_DATA_EBDA_OFFSET);
    NvmeURP = (NVME_STRUC*)((UINTN)NvmeURP & 0xFFFFFFFF);

    // Validate if URP address is an non-SMRAM region to avoid SMRAM data 
    // corruption through SMI handlers
    Status = AmiValidateMemoryBuffer((VOID*)NvmeURP, sizeof(NVME_STRUC));
    if (EFI_ERROR(Status)) {
        return EFI_SUCCESS;
    }
    
    if  (NvmeURP->bFuncNumber != NVME_API_MASS_DEVICE_REQUEST) {
        NvmeURP->bRetValue = NVME_PARAMETER_FAILED;
        return Status;    
    }
    
    bFuncIndex = NvmeURP->bSubFunc;
    bNumberOfFunctions = sizeof NvmeMassApiTable / sizeof (API_FUNC *);

    //
    // Make sure function number is valid; if function number is not zero
    // check for valid extended SDIO API function
    //
    if (bFuncIndex >= bNumberOfFunctions ) {
        NvmeURP->bRetValue = NVME_PARAMETER_FAILED;
        return Status;
    }

    //
    // Call the appropriate function
    //

    NvmeMassApiTable[bFuncIndex](NvmeURP);

    return Status;
}

//**********************************************************************
//<AMI_PHDR_START>
//
// Procedure:   InSmmFunction
//
// Description: Nvme InSmmFunction
//
// Input:
//    IN  EFI_HANDLE       ImageHandle,
//    IN  EFI_SYSTEM_TABLE *SystemTable
//
// Output:
//      EFI_STATUS
//
// Modified:
//      
// Referrals: 
//
// Notes:  None  
//
//
//<AMI_PHDR_END>
//**********************************************************************
EFI_STATUS 
InSmmFunction(
    IN EFI_HANDLE          ImageHandle,
    IN EFI_SYSTEM_TABLE    *SystemTable
)
{
    EFI_STATUS                      Status;
    EFI_HANDLE                      SwHandle = NULL;
#if defined(PI_SPECIFICATION_VERSION) && (PI_SPECIFICATION_VERSION >= 0x00010014)
    EFI_SMM_SW_REGISTER_CONTEXT     SwContext;
    EFI_HANDLE                      DispatchHandle;
    EFI_SMM_SW_DISPATCH2_PROTOCOL   *pSwDispatch = NULL;
#else
    EFI_SMM_BASE_PROTOCOL           *pSmmBase;
    EFI_SMM_SW_DISPATCH_PROTOCOL    *pSwDispatch = NULL;
    EFI_SMM_SYSTEM_TABLE            *pSmst;
    EFI_SMM_SW_DISPATCH_CONTEXT     NvmeSmmSwContext = { NVME_SWSMI };
    EFI_SMM_SW_DISPATCH_CONTEXT     SwContext;
#endif

    InitAmiBufferValidationLib(ImageHandle, SystemTable);

#if defined(PI_SPECIFICATION_VERSION) && (PI_SPECIFICATION_VERSION >= 0x00010014)

    // PI_1.2 -->>

    Status = pBS->LocateProtocol(&gEfiSmmBase2ProtocolGuid, NULL, &gSmmBase2);
    if (EFI_ERROR(Status)) {
        return EFI_SUCCESS;
    }

    Status = gSmmBase2->GetSmstLocation (gSmmBase2, &pSmst2);
    if (EFI_ERROR(Status)) {
        return EFI_SUCCESS;
    }

    Status = pSmst2->SmmLocateProtocol(&gEfiSmmSwDispatch2ProtocolGuid,
                                       NULL,
                                       &pSwDispatch);
    if (EFI_ERROR(Status)) {
        return EFI_SUCCESS;
    }

    SwContext.SwSmiInputValue = NVME_SWSMI;
    Status = pSwDispatch->Register (pSwDispatch,
                                    NvmeSWSMIHandler,
                                    &SwContext,
                                    &SwHandle);
    if (EFI_ERROR (Status)) {
        return Status;
    }
    
    //
    //Allocate Memory for NVMe global Data.
    //
    Status = pSmst2->SmmAllocatePool(EfiRuntimeServicesData,sizeof(NVME_GLOBAL_DATA), &gNvmeData);
    ASSERT_EFI_ERROR(Status);
    //
    //  Clear the Buffer
    //
    pBS->SetMem((VOID*)gNvmeData, sizeof(NVME_GLOBAL_DATA), 0);
    
    
    //
    // Register Nvme handler to transfer data from DXE driver to SMM
    //
    Status = pSmst2->SmiHandlerRegister (
                      NvmeInitSmmData,
                      &gAmiSmmNvmeCommunicationGuid,
                      &DispatchHandle
                      );
    
    ASSERT_EFI_ERROR (Status);

    // PI_1.2 <<--
#else

    // NON PI 1.2 -->>

	Status	= pBS->LocateProtocol(&gEfiSmmSwDispatchProtocolGuid, NULL, &pSwDispatch);
	ASSERT_EFI_ERROR(Status);
    if (EFI_ERROR(Status)) { 
        return Status;
    }

    Status = pBS->LocateProtocol(&gEfiSmmBaseProtocolGuid, NULL, &pSmmBase);
	ASSERT_EFI_ERROR(Status);
    if (EFI_ERROR(Status)) { 
        return Status;
    }

	pSmmBase->GetSmstLocation (pSmmBase, &pSmst);

    Status = pSwDispatch->Register (pSwDispatch,
                                    NvmeSWSMIHandler,
                                    &NvmeSmmSwContext,
                                    &SwHandle);
    if (EFI_ERROR (Status)) {
        return Status;
    }
      
    //
    //Allocate Memory for NVMe global Data.
    //
    Status = pSmst->SmmAllocatePool(EfiRuntimeServicesData,sizeof(NVME_GLOBAL_DATA), &gNvmeData);
    ASSERT_EFI_ERROR(Status);
    //
    //  Clear the Buffer
    //
    pBS->SetMem((VOID*)gNvmeData, sizeof(NVME_GLOBAL_DATA), 0);

    SwContext.SwSmiInputValue = NVME_INIT_SMM_SWSMI;
    Status = pSwDispatch->Register (pSwDispatch,
                                    NvmeInitSmmData,
                                    &SwContext,
                                    &SwHandle);

    // NON PI_1.2 <<--

#endif
   
    return EFI_SUCCESS;
}

//**********************************************************************
//<AMI_PHDR_START>
//
// Procedure:   NvmeSmmDriverEntryPoint
//
// Description: Loads NVMe SMM module into SMM and registers SMI handler
//
// Input:
//    IN  EFI_HANDLE       ImageHandle,
//    IN  EFI_SYSTEM_TABLE *SystemTable
//
// Output:
//      EFI_STATUS
//
// Modified:
//      
// Referrals: 
//
// Notes:  None  
//
//
//<AMI_PHDR_END>
//**********************************************************************
EFI_STATUS 
NvmeSmmDriverEntryPoint (
    IN  EFI_HANDLE       ImageHandle,
    IN  EFI_SYSTEM_TABLE *SystemTable
    )
{
    

    InitAmiLib(ImageHandle, SystemTable);
    return InitSmmHandler (ImageHandle, SystemTable, InSmmFunction, NULL);

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
