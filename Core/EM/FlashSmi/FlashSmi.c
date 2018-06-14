//*************************************************************************
//*************************************************************************
//**                                                                     **
//**        (C)Copyright 1985-2010, American Megatrends, Inc.            **
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
// $Header: /Alaska/SOURCE/Modules/FlashSmi/FlashSmi.c 1     1/20/15 1:36a Tristinchou $
//
// $Revision: 1 $
//
// $Date: 1/20/15 1:36a $
//**********************************************************************
// Revision History
// ----------------
// $Log: /Alaska/SOURCE/Modules/FlashSmi/FlashSmi.c $
// 
// 1     1/20/15 1:36a Tristinchou
// [TAG]  		EIP196554
// [Category]  	New Feature
// [Description]  	Initial check-in
// [Files]  		FlashSmi.cif
// FlashSmi.chm
// FlashSmi.sdl
// FlashSmi.mak
// FlashSmi.c
// FlashSmi.dxs
// 
// 
//
//**********************************************************************
//<AMI_FHDR_START>
//
// Name: FlashSmi.c
//
// Description: FLASH SMI DXE driver.
//
//<AMI_FHDR_END>
//**********************************************************************
//----------------------------------------------------------------------------
// Includes
// Statements that include other files
#include <AmiDxeLib.h>
#include <AmiCspLib.h>
#include <Protocol\SmmBase.h>
#include <Protocol\SmmSwDispatch.h>
#include <Protocol\FlashProtocol.h>

#if defined(PI_SPECIFICATION_VERSION)&&(PI_SPECIFICATION_VERSION>=0x0001000A)
#include <Protocol\SmmBase2.h>
#include <Protocol\SmmCommunication.h>
#endif

//----------------------------------------------------------------------------
// Function Externs

//----------------------------------------------------------------------------
// Local prototypes

typedef struct
{
    UINT32      Signature;
    UINT32      FlashAddress;
    EFI_GUID    VarGuid;
    UINTN       Size;
    EFI_STATUS  Status;
    UINT16      Subfunction;
    CHAR16      DummyName[50];
    UINT32      DataBuffer;

} SMI_FLASH_UPDATE;

typedef struct
{
    BOOLEAN Busy;
    UINT8   IntState[2];

} FLASH_SMI_CRITICAL_SECTION;

#define FSMI_SIGNATURE ('F'+('S'<<8)+(('M'+('I'<<8))<<16))//FSMI
//----------------------------------------------------------------------------
// Local Variables
#define FLASH_SMI_GUID \
{0x4052ACA8, 0x8D90, 0x4F5A, 0xBF, 0xE8, 0xB8, 0x95, 0xB1, 0x64, 0xE4, 0x82}
#define BDS_CONNECT_DRIVERS_PROTOCOL_GUID \
{0x3aa83745, 0x9454, 0x4f7a, 0xa7, 0xc0, 0x90, 0xdb, 0xd0, 0x2f, 0xab, 0x8e}

EFI_GUID    gFlashSmmProtocolGuid = FLASH_SMM_PROTOCOL_GUID;
EFI_GUID    gFlashProtocolGuid = FLASH_PROTOCOL_GUID;
EFI_GUID    gFlashSmiGuid = FLASH_SMI_GUID;
EFI_GUID    gBdsConnectDriversProtocolGuid = BDS_CONNECT_DRIVERS_PROTOCOL_GUID;
VOID        *gFlashBuffer = NULL;
FLASH_PROTOCOL  *gFlash, *gFlashSmm;
FLASH_SMI_CRITICAL_SECTION FlashSmiCs = {FALSE, {0, 0}};
FLASH_ERASE      gSavedFlashErase;
FLASH_READ_WRITE gSavedFlashWrite, gSavedFlashUpdate;
FLASH_ERASE      gSavedFlashEraseSmm;
FLASH_READ_WRITE gSavedFlashWriteSmm;
FLASH_READ_WRITE gSavedFlashUpdateSmm;

#if defined(USE_SMM_COMMUNICATION)&&(USE_SMM_COMMUNICATION==1)
VOID FlashSmiHandler (
    IN  EFI_HANDLE                  DispatchHandle,
    IN  EFI_SMM_SW_DISPATCH_CONTEXT *DispatchContext
);

EFI_SMM_COMMUNICATION_PROTOCOL  *gSmmCommunicate = NULL;

VOID
SmmCommunicationReady(
    IN EFI_EVENT    Event, 
    IN VOID         *Context
)
{
    EFI_STATUS  Status;

    pBS->CloseEvent(Event);

    Status = pBS->LocateProtocol(
                    &gEfiSmmCommunicationProtocolGuid,
                    NULL,
                    &gSmmCommunicate );
}

EFI_STATUS
GenerateFlashSmi(
    VOID
)
{
    EFI_STATUS                  Status;
    EFI_SMM_COMMUNICATE_HEADER  SmmCommunicateHdr;
    UINTN                       SmmCommunicateHdrSize;

    MemCpy( &SmmCommunicateHdr.HeaderGuid, &gFlashSmiGuid, sizeof(EFI_GUID) );
    SmmCommunicateHdr.MessageLength = 1;
    SmmCommunicateHdr.Data[0] = 0;
    SmmCommunicateHdrSize = sizeof(EFI_SMM_COMMUNICATE_HEADER);

    Status = gSmmCommunicate->Communicate(
                                gSmmCommunicate,
                                &SmmCommunicateHdr,
                                &SmmCommunicateHdrSize );

    return Status;
}

EFI_STATUS FlashSmiHandlerDummy (
  IN EFI_HANDLE  DispatchHandle,
  IN CONST VOID  *Context         OPTIONAL,
  IN OUT VOID    *CommBuffer      OPTIONAL,
  IN OUT UINTN   *CommBufferSize  OPTIONAL
)
{
    EFI_STATUS                      Status;
    EFI_SMM_SW_DISPATCH_CONTEXT     SwContext;
    
    SwContext.SwSmiInputValue = FLASH_SW_SMI;
    FlashSmiHandler( DispatchHandle, &SwContext );
    
    if( gFlashBuffer )
        Status = ((SMI_FLASH_UPDATE*)gFlashBuffer)->Status;
    else
        Status = EFI_DEVICE_ERROR;

    return Status;
}

EFI_STATUS SmmCommunicateFunction(
    IN EFI_HANDLE          ImageHandle,
    IN EFI_SYSTEM_TABLE    *SystemTable
)
{
    EFI_STATUS              Status;
    EFI_SMM_BASE2_PROTOCOL  *pEfiSmmBase2Protocol = NULL;
    EFI_SMM_SYSTEM_TABLE2   *Smst2 = NULL;
    UINTN                   VariableSize;
    EFI_HANDLE              Handle = NULL;
    
    Status = pBS->LocateProtocol(
                    &gEfiSmmBase2ProtocolGuid,
                    NULL,
                    &pEfiSmmBase2Protocol );
    if( !EFI_ERROR(Status) )
    {
        Status = pEfiSmmBase2Protocol->GetSmstLocation(
                                        pEfiSmmBase2Protocol,
                                        &Smst2 );
        if( EFI_ERROR(Status) ) return Status;
    }

    // Locate SmmFlashProtocol.
    Status = pBS->LocateProtocol ( &gFlashSmmProtocolGuid, NULL, &gFlashSmm );
    if (EFI_ERROR(Status)) gFlashSmm = NULL;

    if( gFlashSmm != NULL )
    {
        gSavedFlashEraseSmm = gFlashSmm->Erase;
        gSavedFlashWriteSmm = gFlashSmm->Write;
        gSavedFlashUpdateSmm = gFlashSmm->Update;
    }

    // Get Flash SMI runimte memory buffer.
    VariableSize = sizeof(gFlashBuffer);
    Status = pRS->GetVariable ( L"FlashSmiBuffer", \
                                &gFlashSmiGuid, \
                                NULL, \
                                &VariableSize, \
                                &gFlashBuffer );
    if ((EFI_ERROR(Status)) || (gFlashBuffer == NULL)) return Status;

    // Register Flash Software SMI.
    Status = Smst2->SmiHandlerRegister(
                        FlashSmiHandlerDummy,
                        &gFlashSmiGuid,
                        &Handle );

    return Status;
}
#endif

//----------------------------------------------------------------------------
// Function Definitions
//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   BeginCriticalSection
//
// Description: This function calls when critical section begins. It disables interupts, 
//              and Smi and fills CRITICAL_SECTION structure fields
//
// Input:       CRITICAL_SECTION *Cs - pointer to CRITICAL_SECTION structure
//
// Output:      VOID
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS 
FlashSmiBeginCriticalSection (
    FLASH_SMI_CRITICAL_SECTION      *Cs
)
{
    if (Cs->Busy) return EFI_ACCESS_DENIED;
    Cs->IntState[0] = IoRead8(0x21);
    Cs->IntState[1] = IoRead8(0xa1);
    IoWrite8 (0x21, 0xff);
    IoWrite8 (0xa1, 0xff);
    Cs->Busy = TRUE;
    return EFI_SUCCESS;
}
//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   EndCriticalSection
//
// Description: This function calls when critical section ends. It enable interupts,
//              and Smi and fills CRITICAL_SECTION structure fields
//
// Input:       CRITICAL_SECTION *Cs - pointer to CRITICAL_SECTION structure
//
// Output:      VOID
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS
FlashSmiEndCriticalSection (
    FLASH_SMI_CRITICAL_SECTION      *Cs
)
{
    Cs->Busy = FALSE;
    IoWrite8 (0x21, Cs->IntState[0]);
    IoWrite8 (0xa1, Cs->IntState[1]);
    return EFI_SUCCESS;
}
// <AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Name: FlashDriverUpdate
//
// Description: Implementation of the Update Function of the Flash protocol 
//
// Input:
//  VOID*       FlashAddress    Pointer to address of a flash to update (must
//                              be aligned to FlashBlockSize)
//  UINTN       Size            Size to update (must be multiple of FlashBlockSize)
//  VOID*       DataBuffer -    pointer to data to write to the flash part
//
// Output:      EFI_SUCCESS or EFI_DEVICE_ERROR depending on result
//
//--------------------------------------------------------------------------
// <AMI_PHDR_END>
EFI_STATUS EFIAPI FlashDriverUpdateSmi (
    VOID* FlashAddress, UINTN Size, VOID* DataBuffer
)
{
    EFI_STATUS          Status = EFI_SUCCESS;
    SMI_FLASH_UPDATE    *Buffer;

    Status = EFI_NO_RESPONSE;
    if ((gFlashBuffer != NULL) && (gFlash != NULL)) { 
        if (EFI_ERROR(FlashSmiBeginCriticalSection(&FlashSmiCs))) 
            return EFI_ACCESS_DENIED;
        Buffer = (SMI_FLASH_UPDATE*)gFlashBuffer;
        MemSet (Buffer, sizeof(SMI_FLASH_UPDATE), 0);
        Buffer->Subfunction = 'Fu';
        Buffer->Signature = FSMI_SIGNATURE;
        Buffer->FlashAddress = (UINT32)FlashAddress;
        Buffer->Size = Size;
        Buffer->DataBuffer = (UINT32)DataBuffer;
#if defined(USE_SMM_COMMUNICATION)&&(USE_SMM_COMMUNICATION==1)
        GenerateFlashSmi();
#else
        IoWrite8 (SW_SMI_IO_ADDRESS, FLASH_SW_SMI);
#endif
        Status = Buffer->Status;
        MemSet (Buffer, sizeof(SMI_FLASH_UPDATE), 0);
        FlashSmiEndCriticalSection (&FlashSmiCs);
    }
    if (Status == EFI_NO_RESPONSE) {
        Status = gSavedFlashUpdate (FlashAddress, Size, DataBuffer);
    }
    return Status;
}
// <AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Name: FlashDriverWrite
//
// Description: Implementation of the Write Function of the Flash protocol
//
// Input:
//  VOID*       FlashAddress    Pointer to address of a flash to write to 
//  UINTN       Size            Size to write
//  VOID*       DataBuffer -    pointer to data to write to the flash part
//
// Output:      EFI_SUCCESS or EFI_DEVICE_ERROR depending on result
//
//--------------------------------------------------------------------------
// <AMI_PHDR_END>
EFI_STATUS EFIAPI FlashDriverWriteSmi (
    VOID* FlashAddress, UINTN Size, VOID* DataBuffer
)
{
    EFI_STATUS          Status = EFI_SUCCESS;
    SMI_FLASH_UPDATE    *Buffer;

    Status = EFI_NO_RESPONSE;
    if ((gFlashBuffer != NULL) && (gFlash != NULL)) { 
        if (EFI_ERROR(FlashSmiBeginCriticalSection(&FlashSmiCs))) 
            return EFI_ACCESS_DENIED;
        Buffer = (SMI_FLASH_UPDATE*)gFlashBuffer;
        MemSet (Buffer, sizeof(SMI_FLASH_UPDATE), 0);
        Buffer->Subfunction = 'Fw';
        Buffer->Signature = FSMI_SIGNATURE;
        Buffer->FlashAddress = (UINT32)FlashAddress;
        Buffer->Size = Size;
        Buffer->DataBuffer = (UINT32)DataBuffer;
#if defined(USE_SMM_COMMUNICATION)&&(USE_SMM_COMMUNICATION==1)
        GenerateFlashSmi();
#else
        IoWrite8 (SW_SMI_IO_ADDRESS, FLASH_SW_SMI);
#endif
        Status = Buffer->Status;
        MemSet (Buffer, sizeof(SMI_FLASH_UPDATE), 0);
        FlashSmiEndCriticalSection (&FlashSmiCs);
    }
    if (Status == EFI_NO_RESPONSE) {
        Status = gSavedFlashWrite (FlashAddress, Size, DataBuffer);
    }
    return Status;
}
// <AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Name: FlashDriverErase
//
// Description: Implementation of the Erase Function of the Flash protocol
//
// Input:
//  VOID*       FlashAddress    Pointer to address of a flash to erase 
//  UINTN       Size            Size to erase
//
// Output:      EFI_SUCCESS or EFI_DEVICE_ERROR depending on result
//
//--------------------------------------------------------------------------
// <AMI_PHDR_END>
EFI_STATUS EFIAPI FlashDriverEraseSmi (
    VOID* FlashAddress, UINTN Size
)
{
    EFI_STATUS          Status = EFI_SUCCESS;
    SMI_FLASH_UPDATE    *Buffer;

    Status = EFI_NO_RESPONSE;
    if ((gFlashBuffer != NULL) && (gFlash != NULL)) { 
        if (EFI_ERROR(FlashSmiBeginCriticalSection(&FlashSmiCs))) 
            return EFI_ACCESS_DENIED;
        Buffer = (SMI_FLASH_UPDATE*)gFlashBuffer;
        MemSet (Buffer, sizeof(SMI_FLASH_UPDATE), 0);
        Buffer->Subfunction = 'Fe';
        Buffer->Signature = FSMI_SIGNATURE;
        Buffer->FlashAddress = (UINT32)FlashAddress;
        Buffer->Size = Size;
#if defined(USE_SMM_COMMUNICATION)&&(USE_SMM_COMMUNICATION==1)
        GenerateFlashSmi();
#else
        IoWrite8 (SW_SMI_IO_ADDRESS, FLASH_SW_SMI);
#endif
        Status = Buffer->Status;
        MemSet (Buffer, sizeof(SMI_FLASH_UPDATE), 0);
        FlashSmiEndCriticalSection (&FlashSmiCs);
    }
    if (Status == EFI_NO_RESPONSE) {
        gSavedFlashErase (FlashAddress, Size);
    }
    return Status;
}
//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//  Procedure:   FlashSmiConnectDrivers
//
//  Description: This function will be called when Connect Drivers Protocol is 
//               installed and will update FlashProtocol function in RunTime.
//
//  Input:  IN EFI_EVENT Event - signalled event
//          IN VOID *Context - calling context
//
//  Output: VOID
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID FlashSmiConnectDrivers (
    IN EFI_EVENT    Event, 
    IN VOID         *Context
)
{
    pBS->CloseEvent(Event);
    if (gFlashBuffer == NULL) return;

    if (gFlash != NULL)
    {
        gSavedFlashUpdate = gFlash->Update;
        gSavedFlashErase = gFlash->Erase;
        gSavedFlashWrite = gFlash->Write;
        gFlash->Update = FlashDriverUpdateSmi;
        gFlash->Erase = FlashDriverEraseSmi;
        gFlash->Write = FlashDriverWriteSmi;
    }
}
//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//  Procedure:   FlashSmiReadyToBoot
//
//  Description: This function will be called when Ready To Boot and will 
//               restore oringinal FlashProtocol function.
//
//  Input:  IN EFI_EVENT Event - signalled event
//          IN VOID *Context - calling context
//
//  Output: VOID
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS
FlashSmiReadyToBoot (
  EFI_EVENT           Event,
  VOID                *Handle
  )
{
    pBS->CloseEvent(Event);
    gFlash->Update = gSavedFlashUpdate;
    gFlash->Erase = gSavedFlashErase;
    gFlash->Write = gSavedFlashWrite;

    return EFI_SUCCESS;
}
//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//  Procedure:   FlashSmiVirtualFixup
//
//  Description:
//
//  Input:  IN EFI_EVENT Event - signalled event
//          IN VOID *Context - calling context
//
//  Output: VOID
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID FlashSmiVirtualFixup (
    IN EFI_EVENT    Event, 
    IN VOID         *Context
)
{
    pRS->ConvertPointer (0, &gFlashBuffer);
}
//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:   NotInSmmFunction
//
// Description:
//
// Input:       EFI_HANDLE          - ImageHandle
//              EFI_SYSTEM_TABLE*   - SystemTable
//
// Output:      EFI_STATUS
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS NotInSmmFunction(
    IN EFI_HANDLE          ImageHandle,
    IN EFI_SYSTEM_TABLE    *SystemTable
)
{
    EFI_STATUS              Status;
    EFI_EVENT               EvtVirtualFixup, EvtConnectDrivers;
    EFI_EVENT               EvtReadyToBoot;
    VOID                    *RegConnectDrivers =  NULL;
    
#if defined(USE_SMM_COMMUNICATION)&&(USE_SMM_COMMUNICATION==1)
    EFI_EVENT               EvtSmmCommunicationReady;
    VOID                    *RegSmmCommunicationReady;

    Status = pBS->LocateProtocol(
                    &gEfiSmmCommunicationProtocolGuid,
                    NULL,
                    &gSmmCommunicate );
    if( EFI_ERROR(Status) )
    {
        Status = RegisterProtocolCallback(
                    &gEfiSmmCommunicationProtocolGuid,
                    SmmCommunicationReady,
                    NULL,
                    &EvtSmmCommunicationReady,
                    &RegSmmCommunicationReady );
    }
#endif

    // Locate FlashProtocol.
    Status = pBS->LocateProtocol ( &gFlashProtocolGuid, NULL, &gFlash );
    if (EFI_ERROR(Status)) return Status;

    gFlashBuffer = NULL;
    Status = pBS->AllocatePool ( EfiRuntimeServicesData, \
                                 sizeof(SMI_FLASH_UPDATE), \
                                 &gFlashBuffer );
    if (EFI_ERROR(Status)) return EFI_SUCCESS;

    MemSet (gFlashBuffer, sizeof(SMI_FLASH_UPDATE), 0);

    Status = pRS->SetVariable ( L"FlashSmiBuffer", \
                                &gFlashSmiGuid, \
                                EFI_VARIABLE_BOOTSERVICE_ACCESS, \
                                sizeof(gFlashBuffer), \
                               &gFlashBuffer  );
    if (EFI_ERROR(Status)) return EFI_SUCCESS;

    Status = pBS->CreateEvent ( EVT_SIGNAL_VIRTUAL_ADDRESS_CHANGE, \
                                TPL_CALLBACK, \
                                FlashSmiVirtualFixup, \
                                NULL, \
                                &EvtVirtualFixup );
    if (EFI_ERROR(Status)) return EFI_SUCCESS;

    Status = RegisterProtocolCallback ( &gBdsConnectDriversProtocolGuid, \
                                        FlashSmiConnectDrivers, \
                                        NULL, \
                                        &EvtConnectDrivers, \
                                        &RegConnectDrivers );

    Status = CreateReadyToBootEvent( TPL_CALLBACK, FlashSmiReadyToBoot, \
                                    NULL, &EvtReadyToBoot );

    return Status;
}
//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:   FlashSmiHandler
//
// Description:
//
// Input:
//
//
// Output:      EFI_STATUS
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID FlashSmiHandler (
    IN  EFI_HANDLE                  DispatchHandle,
    IN  EFI_SMM_SW_DISPATCH_CONTEXT *DispatchContext
)
{
    SMI_FLASH_UPDATE        *SmmFlashUpdate;
    EFI_STATUS              Status;

    if ((gFlashBuffer == NULL) || \
        ((UINT8)DispatchContext->SwSmiInputValue != FLASH_SW_SMI)) return;

    SmmFlashUpdate = (SMI_FLASH_UPDATE*)gFlashBuffer;
    if (SmmFlashUpdate->Signature != FSMI_SIGNATURE) return;
    
    switch (SmmFlashUpdate->Subfunction)
    {
        // FlashUpdate call
        case 'Fu':
        {
            if (gFlashSmm == NULL) return;
            SmmFlashUpdate = (SMI_FLASH_UPDATE*)gFlashBuffer;
            Status = gSavedFlashUpdateSmm ((VOID*)(SmmFlashUpdate->FlashAddress), \
                                        SmmFlashUpdate->Size, \
                                        (VOID*)(SmmFlashUpdate->DataBuffer));
        }
        break;

        // FlashErase call
        case 'Fe':
        {
            if (gFlashSmm == NULL) return;
            SmmFlashUpdate = (SMI_FLASH_UPDATE*)gFlashBuffer;
            Status = gSavedFlashEraseSmm ((VOID*)(SmmFlashUpdate->FlashAddress), \
                                                SmmFlashUpdate->Size);
        }
        break;
        
        // FlashWrite call
        case 'Fw':
        {
            if (gFlashSmm == NULL) return;
            SmmFlashUpdate = (SMI_FLASH_UPDATE*)gFlashBuffer;
            Status = gSavedFlashWriteSmm ((VOID*)(SmmFlashUpdate->FlashAddress), \
                                        SmmFlashUpdate->Size, \
                                        (VOID*)(SmmFlashUpdate->DataBuffer));
        }
        break;

        // WriteEnable call
        case 'We':
        {
            if (gFlashSmm == NULL) return;
            Status = gFlashSmm->DeviceWriteEnable ();
        }
        break;
        
        default: return;
    }
    
    SmmFlashUpdate->Status = Status;
    SmmFlashUpdate->Subfunction = 0;
    // Invalidate Flash SMI Buffer. 
    SmmFlashUpdate->Signature = ~FSMI_SIGNATURE; 
    return;
}
//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:   FlashSmiSmmSwDispatchCallback
//
// Description:
//
// Input:
//
// Output:
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID FlashSmiSmmSwDispatchCallback(
    IN EFI_EVENT Event,
    IN VOID *Context
)
{
    EFI_SMM_SW_DISPATCH_PROTOCOL    *pSwDispatch;
    EFI_SMM_SW_DISPATCH_CONTEXT     SwContext;
    EFI_HANDLE                      Handle = NULL;
    EFI_STATUS                      Status;
    UINTN                           VariableSize;

    Status = pBS->LocateProtocol ( &gEfiSmmSwDispatchProtocolGuid, \
                                   NULL, \
                                   &pSwDispatch );
    if (EFI_ERROR(Status)) return;
    
    // Locate SmmFlashProtocol.
    Status = pBS->LocateProtocol ( &gFlashSmmProtocolGuid, NULL, &gFlashSmm );
    if (EFI_ERROR(Status)) gFlashSmm = NULL;

    if( gFlashSmm != NULL )
    {
        gSavedFlashEraseSmm = gFlashSmm->Erase;
        gSavedFlashWriteSmm = gFlashSmm->Write;
        gSavedFlashUpdateSmm = gFlashSmm->Update;
    }

    // Get Flash SMI runimte memory buffer.
    VariableSize = sizeof(gFlashBuffer);
    Status = pRS->GetVariable ( L"FlashSmiBuffer", \
                                &gFlashSmiGuid, \
                                NULL, \
                                &VariableSize, \
                                &gFlashBuffer );
    if ((EFI_ERROR(Status)) || (gFlashBuffer == NULL)) return ;

    // Register Flash Software SMI.
    SwContext.SwSmiInputValue = FLASH_SW_SMI;
    Status  = pSwDispatch->Register ( pSwDispatch, \
                                      FlashSmiHandler, \
                                      &SwContext, \
                                      &Handle );
    pBS->CloseEvent(Event);
}
//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:   InSmmFunction
//
// Description: 
//
// Input:       EFI_HANDLE          - ImageHandle
//              EFI_SYSTEM_TABLE*   - SystemTable
//
// Output:      EFI_STATUS
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS InSmmFunction(
    IN EFI_HANDLE          ImageHandle,
    IN EFI_SYSTEM_TABLE    *SystemTable
)
{
    EFI_STATUS          Status;
    EFI_EVENT           EvtFlashSmi;
    VOID                *RegFlashSmi;
    
    Status = RegisterProtocolCallback ( &gEfiSmmSwDispatchProtocolGuid, \
                                        FlashSmiSmmSwDispatchCallback, \
                                        NULL, \
                                        &EvtFlashSmi, \
                                        &RegFlashSmi );
    FlashSmiSmmSwDispatchCallback (EvtFlashSmi, RegFlashSmi);
    return Status;
}
//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:   FlashSmiEntryPoint
//
// Description: DXE Entry Point for FlashSmi Driver.
//
// Input:       EFI_HANDLE          - ImageHandle
//              EFI_SYSTEM_TABLE*   - SystemTable
//
// Output:      EFI_STATUS
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS
FlashSmiEntry (
  IN EFI_HANDLE             ImageHandle,
  IN EFI_SYSTEM_TABLE       *SystemTable
)
{
    EFI_BOOT_MODE   Bootmode;

    InitAmiLib(ImageHandle, SystemTable);

    Bootmode = GetBootMode();
    if( (Bootmode == BOOT_ON_FLASH_UPDATE) ||
        (Bootmode == BOOT_IN_RECOVERY_MODE) )
    {
        return InitSmmHandlerEx(
                    ImageHandle,
                    SystemTable,
#if defined(USE_SMM_COMMUNICATION)&&(USE_SMM_COMMUNICATION==1)
                    SmmCommunicateFunction,
#else
                    InSmmFunction,
#endif
                    NotInSmmFunction );
    }
    else
    {
        return EFI_SUCCESS;
    }
}
//*************************************************************************
//*************************************************************************
//**                                                                     **
//**        (C)Copyright 1985-2009, American Megatrends, Inc.            **
//**                                                                     **
//**                       All Rights Reserved.                          **
//**                                                                     **
//**      5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093           **
//**                                                                     **
//**                       Phone: (770)-246-8600                         **
//**                                                                     **
//*************************************************************************
//*************************************************************************