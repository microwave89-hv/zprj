//**********************************************************************
//**********************************************************************
//**                                                                  **
//**        (C)Copyright 1985-2009, American Megatrends, Inc.         **
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
// $Header: /Alaska/SOURCE/Modules/Legacy Serial Redirection/LegacySmmSredir.c 6     12/08/14 3:36a Anbuprakashp $
//
// $Revision: 6 $
//
// $Date: 12/08/14 3:36a $
//****************************************************************************
//****************************************************************************
// Revision History
// ----------------
// $Log: /Alaska/SOURCE/Modules/Legacy Serial Redirection/LegacySmmSredir.c $
// 
// 6     12/08/14 3:36a Anbuprakashp
// [TAG]  		EIP192305
// [Category]  	Improvement
// [Description]  	Replacing SmmGetMemoryType usage in LegacySredir module
// with AmiBufferValidationLib
// [Files]  		LegacySredir.mak, LegacySmmSredir.c, LegacySredir_Setup.C
// 
// 5     6/25/13 4:40a Rameshr
// [TAG]  		EIP125655
// [Category]  	Improvement
// [Description]  	MMIO Address validated before reading or writing to the
// MMIO region in the SW SMI handler
// [Files]  		LegacySmmSredir.c, LegacySredir.dxs
// 
// 4     4/10/12 12:49a Rameshr
// [TAG]  		EIP84345
// [Category]  	Improvement
// [Description]  	Error checking and SMM dependency added
// [Files]  		LegacySmmSredir.c, LegacySredir.dxs
// 
// 3     6/17/11 4:41a Rameshr
// [TAG] - EIP 47188
// [Category]- IMPROVEMENT
// [Description]- MMIO COM device access width SDL token support added 
// [Files] - legacysredir.c, LegacySredirSmm.c, LegacySredir_setup.c
// 
// 2     9/24/10 1:37a Rameshr
// [TAG] - EIP 44133
// [Category]- BUG FIX & IMPROVEMENT
// [Severity]- Major
// [Symptom] - Flowcontrol and Terminal type is not working in Legacy
// console redirection 
// [RootCause] - Baud rate value overwrites the Flowcontrol and Terminal
// Type fields.
// [Solution] - BaudRate programming done in EFI driver. So removed the
// baud rate value passing into Sredir.bin
//              MMIO com device width added based on SDL token.
// [Files] - LegacySmmSredir.c , Legacysredir.c, Legacysredir.sdl
// 
// 1     3/05/10 4:17a Rameshr
// Initial Check-in
// 
// MMIO COM device support added.
// EIP 33847
// 
// 
//****************************************************************************
//****************************************************************************
//<AMI_FHDR_START>
//****************************************************************************
//
// Name:	LegacySmmSredir.C
//
// Description:	Legacy console redirection SMM support
//****************************************************************************
//<AMI_FHDR_END>

#include "token.h"
#include "Protocol/LegacySredir.h"
#include "AmiDxeLib.h"
#if defined(PI_SPECIFICATION_VERSION)&&(PI_SPECIFICATION_VERSION>=0x0001000A)&&(CORE_COMBINED_VERSION>=0x4028B)
#include <Protocol\SmmCpu.h>
#include <Protocol\SmmBase2.h>
#include <Protocol\SmmSwDispatch2.h>
#else
#include <Protocol\SmmBase.h>
#include <Protocol\SmmSwDispatch.h>
#endif
#include <Protocol\DevicePath.h>
#include <Protocol\LoadedImage.h>
#include <AmiSmm.h>
#include <AmiBufferValidationLib.h>


#if defined(PI_SPECIFICATION_VERSION)&&(PI_SPECIFICATION_VERSION>=0x0001000A)&&(CORE_COMBINED_VERSION>=0x4028B)
EFI_SMM_BASE2_PROTOCOL          *gSmmBase2;
EFI_SMM_SYSTEM_TABLE2           *pSmst2;
EFI_GUID gEfiSmmCpuProtocolGuid = EFI_SMM_CPU_PROTOCOL_GUID;
EFI_SMM_CPU_PROTOCOL            *gSmmCpu=NULL;
#define RETURN(status) {return status;}
#else
EFI_GUID gEfiSmmSwDispatchProtocolGuid = EFI_SMM_SW_DISPATCH_PROTOCOL_GUID;
EFI_GUID gSwSmiCpuTriggerGuid = SW_SMI_CPU_TRIGGER_GUID;
#define RETURN(status) {return ;}
#endif

#pragma pack(1)
typedef struct {
    UINT32          MMIOAddress;
    UINT8           FuncNo;
    UINT8           ReadWrite;      
    UINT8           Offset;
    UINT8           Value;
    UINT8           Count;
    UINT32          BufferAddress;
} SREDIR_INPUT_PARAMETER;
#pragma pack()

EFI_STATUS
LegacySreDirInSmmFunction(
    IN EFI_HANDLE                ImageHandle,
    IN EFI_SYSTEM_TABLE          *SystemTable
 );

#if defined(PI_SPECIFICATION_VERSION)&&(PI_SPECIFICATION_VERSION>=0x0001000A)&&(CORE_COMBINED_VERSION >= 0x4028B)
EFI_STATUS LegacySredirSMIHandler (
	IN EFI_HANDLE       DispatchHandle,
	IN CONST VOID       *DispatchContext OPTIONAL,
	IN OUT VOID         *CommBuffer OPTIONAL,
	IN OUT UINTN        *CommBufferSize OPTIONAL
#else
VOID LegacySredirSMIHandler (
    IN EFI_HANDLE                   DispatchHandle,
    IN EFI_SMM_SW_DISPATCH_CONTEXT  *DispatchContext
#endif
);

//<AMI_PHDR_START>
//----------------------------------------------------------------------
// Procedure:   ReadSerialPort
//
// Description: Read the Data from Serial Port
//
// Input:       SREDIR_INPUT_PARAMETER SredirParam 
//
// Output:      
//
// Returns: 
//
//----------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS ReadSerialPort(
	IN OUT SREDIR_INPUT_PARAMETER	*SredirParam
)
{

    UINT32  TempValue;
#if COM_MMIO_WIDTH == 4
    TempValue=*(UINT32*)(SredirParam->MMIOAddress+(SredirParam->Offset*COM_MMIO_WIDTH));
#else
    #if COM_MMIO_WIDTH == 2
        TempValue=*(UINT16*)(SredirParam->MMIOAddress+(SredirParam->Offset*COM_MMIO_WIDTH));
    #else
        TempValue=*(UINT8*)(SredirParam->MMIOAddress+(SredirParam->Offset*COM_MMIO_WIDTH));
    #endif
#endif    

    SredirParam->Value=(UINT8)TempValue;
    return EFI_SUCCESS;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------
// Procedure:   WriteSerialPort
//
// Description: Write the Data to Serial Port
//
// Input:       SREDIR_INPUT_PARAMETER SredirParam 
//
// Output:      
//
// Returns: 
//
//----------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS WriteSerialPort(
	IN OUT SREDIR_INPUT_PARAMETER	*SredirParam
)
{
    UINT32  TempValue=(UINT32)SredirParam->Value;

#if COM_MMIO_WIDTH == 4
    *(UINT32*)(SredirParam->MMIOAddress+(SredirParam->Offset*COM_MMIO_WIDTH))=TempValue;
#else
    #if COM_MMIO_WIDTH == 2
        *(UINT16*)(SredirParam->MMIOAddress+(SredirParam->Offset*COM_MMIO_WIDTH))=(UINT16)TempValue;
    #else
        *(UINT8*)(SredirParam->MMIOAddress+(SredirParam->Offset*COM_MMIO_WIDTH))=(UINT8)TempValue;
    #endif
#endif   

    return EFI_SUCCESS;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------
// Procedure:   WriteBufferSerialPort
//
// Description: Write the buffer of data to Serial port
//
// Input:       SREDIR_INPUT_PARAMETER SredirParam 
//
// Output:      
//
// Returns: 
//
//----------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS WriteBufferSerialPort(
    IN OUT SREDIR_INPUT_PARAMETER	*SredirParam
)
{
    UINT8       i;
    UINT32      TempValue=0;
    UINT8       *DataBuffer=(UINT8*)SredirParam->BufferAddress;
    EFI_STATUS  Status;

    if(SredirParam->Count == 0) {
        return EFI_SUCCESS;
    }

    if( !DataBuffer ) {
        return EFI_INVALID_PARAMETER;
    }

    // Validate Input buffer is valid and not resides in SMRAM region
    Status = AmiValidateMemoryBuffer ( (VOID*)DataBuffer, SredirParam->Count );
    if( Status != EFI_SUCCESS ) {
        RETURN(Status);
    }

    for(i=0;i<SredirParam->Count;i++) {
        TempValue=*DataBuffer;

#if COM_MMIO_WIDTH == 4
        *(UINT32*)(SredirParam->MMIOAddress+(SredirParam->Offset*COM_MMIO_WIDTH))=TempValue;
#else
    #if COM_MMIO_WIDTH == 2
            *(UINT16*)(SredirParam->MMIOAddress+(SredirParam->Offset*COM_MMIO_WIDTH))=(UINT16)TempValue;
    #else
            *(UINT8*)(SredirParam->MMIOAddress+(SredirParam->Offset*COM_MMIO_WIDTH))=(UINT8)TempValue;
    #endif
#endif   
        DataBuffer++;
    }

    return EFI_SUCCESS;
}
 
//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	LegacySredirSMIHandler
//
// Description:	Legacy Serial Redirection Smm handler function
//
// Input:	    DispatchHandle  - EFI Handle
//              DispatchContext - Pointer to the EFI_SMM_SW_DISPATCH_CONTEXT
//
// Output:      
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
#if defined(PI_SPECIFICATION_VERSION)&&(PI_SPECIFICATION_VERSION>=0x0001000A)&&(CORE_COMBINED_VERSION >= 0x4028B)
EFI_STATUS LegacySredirSMIHandler (
	IN EFI_HANDLE       DispatchHandle,
	IN CONST VOID       *DispatchContext OPTIONAL,
	IN OUT VOID         *CommBuffer OPTIONAL,
	IN OUT UINTN        *CommBufferSize OPTIONAL
#else
VOID LegacySredirSMIHandler (
    IN EFI_HANDLE                   DispatchHandle,
    IN EFI_SMM_SW_DISPATCH_CONTEXT  *DispatchContext
#endif
)
{
    EFI_STATUS  Status = EFI_SUCCESS;
	UINT8		Data;
	UINT64		pCommBuff;
	UINT32		HighBufferAddress = 0;
	UINT32		LowBufferAddress = 0;
    UINTN       Cpu=(UINTN)-1;
    SREDIR_INPUT_PARAMETER  *SredirParam;
#if PI_SPECIFICATION_VERSION < 0x1000A   
    EFI_SMM_CPU_SAVE_STATE  *pCpuSaveState;
    SW_SMI_CPU_TRIGGER      *SwSmiCpuTrigger;
    UINTN       i;
#endif

#if defined(PI_SPECIFICATION_VERSION)&&(PI_SPECIFICATION_VERSION>=0x0001000A)&&(CORE_COMBINED_VERSION >= 0x4028B)

    Cpu = ((EFI_SMM_SW_CONTEXT*)CommBuffer)->SwSmiCpuIndex;
    //
    // Found Invalid CPU number, return 
    //
    if(Cpu == (UINTN)-1) RETURN(Status);

    Status = gSmmCpu->ReadSaveState ( gSmmCpu, \
                                      4, \
                                      EFI_SMM_SAVE_STATE_REGISTER_RBX, \
                                      Cpu, \
                                      &LowBufferAddress );

    Status = gSmmCpu->ReadSaveState ( gSmmCpu, \
                                      4, \
                                      EFI_SMM_SAVE_STATE_REGISTER_RCX, \
                                      Cpu, \
                                      &HighBufferAddress );

    Data = ((EFI_SMM_SW_CONTEXT*)CommBuffer)->CommandPort;
#else
  	for (i = 0; i < pSmst->NumberOfTableEntries; ++i) {
		if (guidcmp(&pSmst->SmmConfigurationTable[i].VendorGuid,&gSwSmiCpuTriggerGuid) == 0) {
			break;
		}
  	}
	
  	//If found table, check for the CPU that caused the software Smi.
  	if (i != pSmst->NumberOfTableEntries) {
		SwSmiCpuTrigger = pSmst->SmmConfigurationTable[i].VendorTable;
		Cpu = SwSmiCpuTrigger->Cpu;
  	}

    //
    // Found Invalid CPU number, return 
    //
    if(Cpu == (UINTN) -1) { 
        RETURN(Status);
    }

	Data	= (UINT8)DispatchContext->SwSmiInputValue;
	
	pCpuSaveState		= pSmst->CpuSaveState;
	HighBufferAddress	= pCpuSaveState[Cpu].Ia32SaveState.ECX;
	LowBufferAddress	= pCpuSaveState[Cpu].Ia32SaveState.EBX;

#endif

	pCommBuff			= HighBufferAddress;
	pCommBuff			= Shl64(pCommBuff, 32);
	pCommBuff			+= LowBufferAddress;
    SredirParam         =(SREDIR_INPUT_PARAMETER *)pCommBuff; 

    // Validate COM port register's MMIO address space are valid and not reside in SMRAM region
    Status = AmiValidateMmioBuffer( (VOID*)SredirParam->MMIOAddress, 8*COM_MMIO_WIDTH );
    if( Status != EFI_SUCCESS ) {
        SredirParam->Value=0;
        RETURN(Status);
    }

    switch(SredirParam->FuncNo) {

        case 0x1:
                ReadSerialPort(SredirParam);
                break;

        case 0x2:
                WriteSerialPort(SredirParam);
                break;

        case 0x3:
                Status = WriteBufferSerialPort(SredirParam);
                break;

    }

    RETURN(Status);
}


//<AMI_PHDR_START>
//---------------------------------------------------------------------------
//
// Name:          LegacySreDirInSmmFunction
//
// Description:   Legacy Serial Redirection  Smm entry point
//
// Input:         Standard EFI Image entry - EFI_IMAGE_ENTRY_POINT
//                EFI System Table - Pointer to System Table
//
// Output:        EFI_STATUS OR EFI_NOT_FOUND
//
//---------------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS
LegacySreDirInSmmFunction(
    IN EFI_HANDLE                ImageHandle,
    IN EFI_SYSTEM_TABLE          *SystemTable
 )
{

    EFI_HANDLE	Handle;
    EFI_STATUS	Status;
#if defined(PI_SPECIFICATION_VERSION)&&(PI_SPECIFICATION_VERSION>=0x0001000A)&&(CORE_COMBINED_VERSION >= 0x4028B)
    EFI_SMM_SW_DISPATCH2_PROTOCOL    *pSwDispatch = NULL;
    EFI_SMM_SW_REGISTER_CONTEXT      SwContext;
#else
    EFI_SMM_SW_DISPATCH_PROTOCOL    *pSwDispatch;
    EFI_SMM_SW_DISPATCH_CONTEXT     SwContext;
#endif

#if defined(PI_SPECIFICATION_VERSION)&&(PI_SPECIFICATION_VERSION>=0x0001000A)&&(CORE_COMBINED_VERSION >= 0x4028B)
    Status = InitAmiSmmLib( ImageHandle, SystemTable );

    Status = pBS->LocateProtocol(&gEfiSmmBase2ProtocolGuid, NULL, &gSmmBase2);
    
    if (EFI_ERROR(Status)) { 
        return Status;
    }

    //
    // We are in SMM, retrieve the pointer to SMM System Table
    //
    Status = gSmmBase2->GetSmstLocation( gSmmBase2, &pSmst2);
    if (EFI_ERROR(Status)) {  
        return EFI_UNSUPPORTED;
    }

    Status  = pSmst2->SmmLocateProtocol( &gEfiSmmSwDispatch2ProtocolGuid, \
                                          NULL, \
                                          &pSwDispatch );

    if(EFI_ERROR(Status)) {
        return Status;
    }

    Status = pSmst2->SmmLocateProtocol(&gEfiSmmCpuProtocolGuid, NULL, &gSmmCpu);

#else
	Status	= pBS->LocateProtocol(&gEfiSmmSwDispatchProtocolGuid, NULL, &pSwDispatch);
#endif

	ASSERT_EFI_ERROR(Status);

    if(EFI_ERROR(Status)) {
        return Status;
    }

    InitAmiBufferValidationLib( ImageHandle, SystemTable );

    SwContext.SwSmiInputValue	= LEGACY_SREDIR_SWSMI;
    Status	= pSwDispatch->Register(pSwDispatch, LegacySredirSMIHandler, &SwContext, &Handle);
    return EFI_SUCCESS;
}

//**********************************************************************
//**********************************************************************
//**                                                                  **
//**        (C)Copyright 1985-2009, American Megatrends, Inc.         **
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
