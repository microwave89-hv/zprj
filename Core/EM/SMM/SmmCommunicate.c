//*************************************************************************
//*************************************************************************
//**                                                                     **
//**        (C)Copyright 1985-2011 American Megatrends, Inc.            **
//**                                                                     **
//**                       All Rights Reserved.                          **
//**                                                                     **
//**      5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093           **
//**                                                                     **
//**                       Phone: (770)-246-8600                         **
//**                                                                     **
//*************************************************************************
//*************************************************************************

//**********************************************************************
// $Header: /Alaska/SOURCE/Modules/SMM/SmmCommunicate/SmmCommunicate.c 5     3/22/12 11:38a Markw $
//
// $Revision: 5 $
//
// $Date: 3/22/12 11:38a $
//**********************************************************************
// Revision History
// ----------------
// $Log: /Alaska/SOURCE/Modules/SMM/SmmCommunicate/SmmCommunicate.c $
// 
// 5     3/22/12 11:38a Markw
// [TAG]  		EIP84198
// [Category]  	Bug Fix
// [Severity]  	Important
// [Symptom]  	Using SMM Communication can cause OS to hang
// [RootCause]  	SMM Communication Protocol�s Communicate API does not
// function in UEFI OS after Exit boot services event because
// ConvertPointer() did not convert SMM_COMMUNICATE_DATA *gCommunicateData
// pointer from a Physical Memory Map Pointer to a Virtual Memory Map
// Pointer. gCommunicateData is allocated in EfiACPIMemoryNVS.
// [Solution]  	Allocate memory gCommunicateData as Runtime Services Data.
// [Files]  		SmmCommunicate.c
// 
// 4     10/03/11 3:56p Markw
// Use tokens for SW SMI. Comment publishing ACPI table until ready.
// Files: SmmCommunicate.sdl, SmmCommunicate.c
// 
// 3     9/14/11 11:30a Markw
// Add comment for pRS->GetVariable in CommunicateCallback, and in SMM
// Communcate generating SW SMI.
// 
// 2     9/12/11 9:58a Markw
// [TAG]  		EIP64115
// [Category]  	Bug Fix
// [Severity]  	Normal
// [Symptom]  	SmmCommuncate hangs in OS.
// [RootCause]  	SMM Communciate not available in OS.
// [Solution]  	Update SMM Communicate to work under OS by making it a
// runtime driver and converting pointers to virtual points on
// EVT_SIGNAL_VIRTUAL_ADDRESS_CHANGE.
// 
// [Files]  		SmmCommunicate.c, SmmCommunicate.mak
// 
// 1     4/18/11 12:03p Markw
// [TAG]  		EIP57440
// [Category]  	New Feature
// [Description]  	Add SMM PI 1.1 Communicate Support.
// [Files]  		SmmCommunicate.cif
// SmmCommunicate.sdl
// SmmCommunicate.c
// SmmCommunicate.dxs
// SmmDxeCommunicate.dxs
// SmmCommunicate.mak
// 
//
//**********************************************************************

//<AMI_FHDR_START>
//---------------------------------------------------------------------------
//
// Name:		SmmCommunicate.c
//
// Description:	Provide SMM Communicate Protocol
//
//---------------------------------------------------------------------------
//<AMI_FHDR_END>

#include <Efi.h>
#include <Acpi.h>
#include <AmiDxeLib.h>
#include <SmmPi.h>
#include <Protocol\SmmBase2.h>
#include <Protocol\SmmCommunication.h>
#include <Protocol\SmmSwDispatch2.h>
#include <Protocol\AcpiSupport.h>
#include <Protocol\AmiInternalSmmComm.h>
#include <Token.h>

typedef struct {
    VOID  *CommBuffer;
    UINTN *CommSize;
    EFI_STATUS Status;
} SMM_COMMUNICATE_DATA;

#define SMM_COMMUNICATE_DATA_VARIABLE L"SMM_COMMUNICATE_DATA"

// {08F10CB6-3131-4919-9D70-5C8A17366EE8}
#define SMM_COMMUNICATE_DATA_GUID \
    {0x8f10cb6, 0x3131, 0x4919, 0x9d, 0x70, 0x5c, 0x8a, 0x17, 0x36, 0x6e, 0xe8}

EFI_HANDLE gImageHandle;

EFI_GUID gEfiSmmBase2ProtocolGuid = EFI_SMM_BASE2_PROTOCOL_GUID;
EFI_GUID gEfiSmmCommunicationProtocolGuid = EFI_SMM_COMMUNICATION_PROTOCOL_GUID;
EFI_GUID gAmiIntSmmCommProtocolGuid = AMI_INT_SMM_COMM_PROTOCOL_GUID;
EFI_GUID gSmmCommunicateDataGuid = SMM_COMMUNICATE_DATA_GUID;
EFI_GUID gEfiAcpiSupportGuid = EFI_ACPI_SUPPORT_GUID;


EFI_SMM_BASE2_PROTOCOL          *gSmmBase2;


SMM_COMMUNICATE_DATA *gCommunicateData = NULL;

/////////////////////SMM//////////////////
EFI_GUID gEfiSmmSwDispatch2ProtocolGuid = EFI_SMM_SW_DISPATCH2_PROTOCOL_GUID;

EFI_SMM_SW_DISPATCH2_PROTOCOL   *gSmmSw2;
EFI_SMM_SYSTEM_TABLE2           *Smst2;

//<AMI_PHDR_START>
//---------------------------------------------------------------------------
//
// Procedure: CommunicateCallBack
//
// Description: Sw SMI callback to call communicate functions.
//
// Input:
//  IN EFI_HANDLE DispatchHandle  - Unused
//  IN CONST VOID *Context OPTIONAL - Unused
//  IN OUT VOID *CommBuffer OPTIONAL  - Unused
//  IN OUT UINTN *CommBufferSize OPTIONAL  - Unused
//
// Output: EFI_STATUS
//
//---------------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS CommunicateCallBack(
    IN EFI_HANDLE DispatchHandle,
    IN CONST VOID *Context OPTIONAL,
    IN OUT VOID *CommBuffer OPTIONAL,
    IN OUT UINTN *CommBufferSize OPTIONAL
)
{
    EFI_SMM_COMMUNICATE_HEADER *Header;
    EFI_STATUS Status;

    if (gCommunicateData == NULL) {
        UINTN VariableSize = sizeof(EFI_SMM_COMMUNICATE_HEADER*);

        //SMM_COMMUNICATE_DATA_VARIABLE variable is not available during
        // SMM entry. When this variable is set in DXE before BDS,
        // a SW SMI is executed, and gCommunicateData is initialized
        // before SMM Communciate protocol is published. 
        Status = pRS->GetVariable(
            SMM_COMMUNICATE_DATA_VARIABLE,
            &gSmmCommunicateDataGuid,
            NULL,
            &VariableSize,
            &gCommunicateData
        );
        ASSERT_EFI_ERROR(Status);
        if (!EFI_ERROR(Status))  gCommunicateData->Status = Status;
        return EFI_SUCCESS;
    }

    if (gCommunicateData->CommBuffer == NULL) {
        gCommunicateData->Status = EFI_INVALID_PARAMETER;
        return EFI_SUCCESS;
    }

    gCommunicateData->Status = EFI_NOT_FOUND;    //Default no handler found.

    Header = (EFI_SMM_COMMUNICATE_HEADER*)(gCommunicateData->CommBuffer);
    Status = Smst2->SmiManage(&Header->HeaderGuid, NULL, Header->Data, &Header->MessageLength);

    //Default Status of SmiManage is EFI_INTERRUPT_PENDING. Thus, no handler found.
    if (Status != EFI_INTERRUPT_PENDING) gCommunicateData->Status = EFI_SUCCESS;
    return EFI_SUCCESS;
}

//<AMI_PHDR_START>
//---------------------------------------------------------------------------
//
// Procedure: InitSmm
//
// Description: Initialize SMM part of SMM Communicate.
//
// Input: VOID
//
// Output: EFI_STATUS
//
//---------------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS InitSmm()
{
    EFI_STATUS Status;
    EFI_SMM_SW_REGISTER_CONTEXT  RegisterContext = {SMM_COMM_SW_SMI};
    EFI_HANDLE ImageHandle = NULL;
    EFI_HANDLE DispatchHandle;

    Status = gSmmBase2->GetSmstLocation(gSmmBase2, &Smst2);
    ASSERT_EFI_ERROR(Status);

    Status = Smst2->SmmLocateProtocol(&gEfiSmmSwDispatch2ProtocolGuid, NULL, &gSmmSw2);
    ASSERT_EFI_ERROR(Status);

    Status = gSmmSw2->Register(
            gSmmSw2,
            CommunicateCallBack,
            &RegisterContext,
            &DispatchHandle
    );
    ASSERT_EFI_ERROR(Status);
    if (EFI_ERROR(Status)) return Status;


//Signal that Handler is ready
    Status = pBS->InstallMultipleProtocolInterfaces(
        &ImageHandle,
        &gAmiIntSmmCommProtocolGuid, NULL,
        NULL
    );

    return Status;
}


/////////////////////ACPI//////////////////

#pragma pack(push, 1)
typedef struct {
    ACPI_HDR Hdr;
    EFI_GUID Identifier;
    UINT16   DataOffset;
    UINT32   SwSmi;
    UINT64   BufferPtr;
} ACPI_SMM_COMM_TABLE;
#pragma pack(pop)

ACPI_SMM_COMM_TABLE gAcpiSmmCommTable =
{
     'UEFI',
     sizeof(ACPI_SMM_COMM_TABLE),
     1, //Revision
     0, //Checksum
     T_ACPI_OEM_ID, //CONVERT_TO_STRING(T_ACPI_OEM_ID),
     T_ACPI_OEM_TBL_ID, //CONVERT_TO_STRING(T_ACPI_OEM_TBL_ID),
     ACPI_OEM_REV,
     0, //Creator ID
     0, //Creator Revision,
     EFI_SMM_COMMUNICATION_PROTOCOL_GUID,
     EFI_FIELD_OFFSET(ACPI_SMM_COMM_TABLE, SwSmi),
     SMM_COMM_SW_SMI,
     0
};

EFI_ACPI_SUPPORT_PROTOCOL *gAcpiSupport;

//<AMI_PHDR_START>
//---------------------------------------------------------------------------
//
// Procedure: InitAcpi
//
// Description: Initialize Acpi SMM Communicate part.
//
// Input: VOID
//
// Output: EFI_STATUS
//
//---------------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS InitAcpi()
{
//TODO: Proper support for ACPI SMM communicate will be in SMM label 45.
#if 0
    EFI_STATUS Status;
    UINTN AcpiHandle = 0;

    Status = pBS->LocateProtocol(&gEfiAcpiSupportGuid, NULL, &gAcpiSupport);
    ASSERT_EFI_ERROR(Status);
    if (EFI_ERROR(Status)) return Status;

    Status = gAcpiSupport->SetAcpiTable(
            gAcpiSupport,
            &gAcpiSmmCommTable,
            TRUE,
            EFI_ACPI_TABLE_VERSION_ALL,
            &AcpiHandle
    );
    ASSERT_EFI_ERROR(Status);
    if (EFI_ERROR(Status)) return Status;
#endif

    return EFI_SUCCESS;
}

/////////////////////DXE//////////////////

//<AMI_PHDR_START>
//---------------------------------------------------------------------------
//
// Procedure: SmmCommunicate
//
// Description: SmmCommunicate Protocol function. This will generate SW SMI.
//
// Input:
//  IN CONST EFI_SMM_COMMUNICATION_PROTOCOL *This,
//  IN OUT VOID     *CommBuffer,
//  IN OUT UINTN    *CommSize
//
// Output: EFI_STATUS
//
//---------------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS SmmCommunicate(
        IN CONST EFI_SMM_COMMUNICATION_PROTOCOL *This,
        IN OUT VOID     *CommBuffer,
        IN OUT UINTN    *CommSize
)
{
    gCommunicateData->CommBuffer = CommBuffer;
    gCommunicateData->CommSize = CommSize;
    gCommunicateData->Status = EFI_DEVICE_ERROR;    //Pre-initialize status in case SMI doesn't happen.

    //Execute SW SMI to initialize 
    IoWrite8(SW_SMI_IO_ADDRESS, SMM_COMM_SW_SMI);

    return gCommunicateData->Status;
}

EFI_SMM_COMMUNICATION_PROTOCOL gEfiSmmCommunicationProtocol = {
    SmmCommunicate
};

//<AMI_PHDR_START>
//---------------------------------------------------------------------------
//
// Procedure: VirtAddrChg
//
// Description: Change pointer of gCommunicateData to virtual address.
//
// Input:
//  IN EFI_EVENT Event
//  IN VOID *Context
//
// Output: VOID
//
//---------------------------------------------------------------------------
//<AMI_PHDR_END>

VOID VirtAddrChg(IN EFI_EVENT Event, IN VOID *Context)
{
    pRS->ConvertPointer(0, (VOID**)&gCommunicateData);
}


//<AMI_PHDR_START>
//---------------------------------------------------------------------------
//
// Procedure: InitDxe
//
// Description: Initialize DXE SMM Communicate part.
//
// Input: VOID
//
// Output: EFI_STATUS
//
//---------------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS InitDxe()
{
    EFI_STATUS Status;
    EFI_EVENT VirtAddrChgEvt;

    Status = pBS->AllocatePool(EfiRuntimeServicesData, sizeof(SMM_COMMUNICATE_DATA), &gCommunicateData);
    ASSERT_EFI_ERROR(Status);

    //Pass gCommunicateData to SMM Dispatcher.
    gCommunicateData->Status = EFI_DEVICE_ERROR;    //Pre-initialize status in case SMI doesn't happen.

    //Set Value
    Status = pRS->SetVariable(
        SMM_COMMUNICATE_DATA_VARIABLE,
        &gSmmCommunicateDataGuid,
        EFI_VARIABLE_BOOTSERVICE_ACCESS,
        sizeof(SMM_COMMUNICATE_DATA*),
        &gCommunicateData
    );

    IoWrite8(SW_SMI_IO_ADDRESS, SMM_COMM_SW_SMI);

    if (gCommunicateData->Status == EFI_DEVICE_ERROR) return EFI_DEVICE_ERROR;

    InitAcpi();

    Status = pBS->CreateEvent(
        EVT_SIGNAL_VIRTUAL_ADDRESS_CHANGE,
        TPL_CALLBACK, 
        &VirtAddrChg, 
        NULL, 
        &VirtAddrChgEvt
    );
    ASSERT_EFI_ERROR(Status);


    Status = pBS->InstallMultipleProtocolInterfaces(
        &gImageHandle,
        &gEfiSmmCommunicationProtocolGuid, &gEfiSmmCommunicationProtocol,
        NULL
    );

    return Status;
}

//<AMI_PHDR_START>
//---------------------------------------------------------------------------
//
// Procedure: SmmCommunicateEntry
//
// Description: Smm Communciation entry point to initialize provide SMM Communicate Protocol.
//
// Input:
//  IN EFI_HANDLE       ImageHandle,
//  IN EFI_SYSTEM_TABLE *SystemTable
//
// Output: EFI_STATUS
//
//---------------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS SmmCommunicateEntry(
    IN EFI_HANDLE       ImageHandle,
    IN EFI_SYSTEM_TABLE *SystemTable
)
{
    EFI_STATUS Status;
    BOOLEAN InSmram;

    InitAmiLib(ImageHandle,SystemTable);

    gImageHandle = ImageHandle;

    Status = pBS->LocateProtocol(&gEfiSmmBase2ProtocolGuid, NULL, &gSmmBase2);
    ASSERT_EFI_ERROR(Status);

    Status = gSmmBase2->InSmm(gSmmBase2, &InSmram);
    ASSERT_EFI_ERROR(Status);

    if (InSmram) return InitSmm();
    return InitDxe();
}
