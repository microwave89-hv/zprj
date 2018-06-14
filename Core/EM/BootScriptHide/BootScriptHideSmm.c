//**********************************************************************
//**********************************************************************
//**                                                                  **
//**        (C)Copyright 1985-2016, American Megatrends, Inc.         **
//**                                                                  **
//**                       All Rights Reserved.                       **
//**                                                                  **
//**             5555 Oakbrook Pkwy, Norcross, GA 30093               **
//**                                                                  **
//**                       Phone: (770)-246-8600                      **
//**                                                                  **
//**********************************************************************
//**********************************************************************

//**********************************************************************
// $Header: /Alaska/SOURCE/Modules/BootScriptHide/BootScriptHideSmm.c 4     5/24/16 4:28p Robert $
//
// $Revision: 4 $
//
// $Date: 5/24/16 4:28p $
//**********************************************************************
// Revision History
// ----------------
// $Log: /Alaska/SOURCE/Modules/BootScriptHide/BootScriptHideSmm.c $
// 
// 4     5/24/16 4:28p Robert
// [TAG]  		EIP268161
// [Category]  	Improvement
// [Description]  	Update copyrights
// 
// 3     5/20/16 12:11p Robert
// [TAG]  		EIP268161
// [Category]  	Improvement
// [Description]  	Update BootScriptHide to comply with Security
// Vulnerability related to saving other memory regions at the same time
// as the boot scripts
// 
// 2     11/03/14 3:31p Aaronp
// Improved buffer validation and error detection.
//  - IsBufferInSmram is replaced with IsBadBuffer that delas with memory
// range
//  - BootScriptSaved flag is added to signal that saved boot script
// buffer is valid
// 
// 1     9/10/14 6:31p Aaronp
// First addition of BootScriptHide emodule.
//**********************************************************************

//**********************************************************************
//<AMI_FHDR_START>
//
// Name:	BootScriptHideSmm.c
//
// Description:	Source file for the SMM driver. Contains the code that is
//              signalled when it is time to save/restore the boot script
//              tables
//
//<AMI_FHDR_END>
//**********************************************************************

#include <AmiDxeLib.h>
#include <Token.h>
#include <AcpiS3.h>
#include <BootScriptCommon.h>
#include <Protocol/SmmSwDispatch2.h>
#include <Protocol/SmmAccess2.h>

#if PI_SPECIFICATION_VERSION < 0x0001000A
#error This module requires PI 1.1 or higher
#endif

/// Maximum size of the boot script tables
#define MAX_BOOT_SCRIPT_TABLE_SIZE 0x100000 // 1MB

// The definitions below are from BootScriptPrivate.h, but we don't want to include private ACPI headers here.
/// Structure copied out of BootScriptPrivate.h
typedef struct {
    UINT32 UniqueIndex; ///< Index of this entry
    UINT32 Length;      ///< Length of this entry
} BOOT_SCRIPT_INFO_STRUCTURE;

/// Structure copied out of BootScriptPrivate.h
typedef struct {
    UINT16                  Type;       ///< Type of this boot script entry
    EFI_PHYSICAL_ADDRESS    EntryPoint; ///< Entry point of the code to be dispatched.
} BOOT_SCRIPT_DISPATCH;

/// Opcode that signals the current entry is the last entry in the boot script tables
#define TABLE_END_OP_CODE               0xff
// End of BootScriptPrivate.h content

EFI_SMRAM_DESCRIPTOR *SmramRanges;
UINTN SmramRangeCount;

UINTN BootScriptTableSize = 0;
VOID *SmmBootScriptBuffer = NULL;
ACPI_VARIABLE_SET *AcpiVariableSet = NULL;
EFI_PHYSICAL_ADDRESS	SmmAcpiReserveMemoryBase;
UINT32					SmmAcpiReserveMemorySize;
EFI_PHYSICAL_ADDRESS	SmmAcpiFacsTable[3];
EFI_PHYSICAL_ADDRESS	SmmBootScriptTable;
BOOLEAN AcpiVariableSetValuesCorrupted;
BOOLEAN BootScriptSaved = FALSE;

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//  Procedure:      IsBadBuffer
//
//  Description:    Function that verifies that the passed address is not contained 
//                  in the region of memory occupied by the SMM code. 
//
//  Input:
//  IN VOID* Buffer - Address to check against the SMM memory region
//  IN UINTN BufferSize - Size of the buffer to check against the Smm Memory Region
//
//  Output:
//  BOOLEAN
//      TRUE - The address is part of the SMRAM region
//      FALSE - The address is not part of the SMRAM region
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
BOOLEAN IsBadBuffer (IN VOID *Buffer, IN UINTN BufferSize){
	UINTN  i;
	UINTN BufferAddress = (UINTN)Buffer;
	
	if (BufferAddress + BufferSize < BufferAddress) return TRUE; // overflow
	for (i = 0; i < SmramRangeCount; i ++) {
		if (    BufferAddress >= SmramRanges[i].CpuStart
    	     && BufferAddress < SmramRanges[i].CpuStart + SmramRanges[i].PhysicalSize
    	) return TRUE; // Buffer starts in SMRAM
        if (    BufferAddress < SmramRanges[i].CpuStart
    	     && BufferAddress+BufferSize > SmramRanges[i].CpuStart
        ) return TRUE; // Buffer overlaps with SMRAM
	}
	
	return FALSE;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//  Procedure:      GetBootScriptTableLength
//
//  Description:    Using the passed BootScriptTablePointer, go through the
//                  entries and determine the total size of the Boot Script
//                  table.
//
//  Input:
//  VOID *BootScriptTablePtr - Pointer to the boot script tables
//
//  Output:
//  UINTN The total size of the boot script tables
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
UINTN GetBootScriptTableLength(VOID *BootScriptTablePtr){
    BOOT_SCRIPT_INFO_STRUCTURE* BootScriptTable = BootScriptTablePtr;
    UINT8 Type;
    UINTN Size = 0;
    do{
        Type = *(UINT8*)(BootScriptTable + 1);
        if (Type == TABLE_END_OP_CODE){
            // The OpCode size comes from BootScriptTable->Length.
            // However, info structure of the End OpCode for some reason comes with the invalid Length.
            // That is why we have to calculate OpCode size differently.
            Size += sizeof(BOOT_SCRIPT_INFO_STRUCTURE) + 2; // 2 is sizeof(BOOT_SCRIPT_TABLE_END);
            break;
        }
        // The dispatch OpCodes are dangerous. If function being dispatching is not in ROM, it can be modified by OS agent.
        // On one hand, we can't allow dispatching of non-ROM function.
        // On the other hand, we can't simply skip the function because it might be doing something important.
        // We're just giving up (not saving the script). 
        // Our companion PEIM will detect that boot script has not been saved and restored and will reset the system.
        if (Type == EFI_BOOT_SCRIPT_DISPATCH_OPCODE || Type == EFI_BOOT_SCRIPT_DISPATCH_2_OPCODE){
            // The entry point is a 64-bit value, but we ignore the upper four bytes because:
            // 1) AMI boot script implementation launches dispatch function in 32-bit mode and ignores the upper 4 bytes.
            // 2) Due to a type casting bug in some projects, the upper 4 bytes are occasionally filled with F's.
            UINT32 EntryPoint = (UINT32)((BOOT_SCRIPT_DISPATCH*)(BootScriptTable + 1))->EntryPoint;
            if (EntryPoint < 0xFFFFFFFF - FLASH_SIZE +1){
                TRACE((TRACE_ALWAYS,
                        "BootScriptHide: ERROR: Boot script dispatch opcode with the Entry Point(%lX) outside of the ROM is found.\n"
                        "It's illegal to call non-ROM functions in the boot script.\n"
                        "Fix your project by searching for %s in the code and reviewing origin of the functions being dispatched.\n",
                        EntryPoint,
                        (Type == EFI_BOOT_SCRIPT_DISPATCH_OPCODE) 
                          ? "\"EFI_BOOT_SCRIPT_DISPATCH_OPCODE\" or \"BOOT_SCRIPT_DISPATCH_MACRO\"" 
                          : "\"EFI_BOOT_SCRIPT_DISPATCH_2_OPCODE\" or \"BOOT_SCRIPT_S3_DISPATCH_MACRO\" or \"BOOT_SCRIPT_S3_DISPATCH_2_MACRO\""
                ));
                ASSERT_EFI_ERROR(EFI_INVALID_PARAMETER);
                return 0;
            }
        }
        if (BootScriptTable->Length == 0 || BootScriptTable->Length > MAX_BOOT_SCRIPT_TABLE_SIZE) return 0;
        Size += BootScriptTable->Length;
        if (Size > MAX_BOOT_SCRIPT_TABLE_SIZE) return 0;
        BootScriptTable = (BOOT_SCRIPT_INFO_STRUCTURE*)((UINT8*)BootScriptTable + BootScriptTable->Length);
    }while(TRUE);
    return Size;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//  Procedure:      SaveBootScriptHandle
//
//  Description:    SMM Dispatch handler to save the Boot Scripts from regular system
//                  memory into SMRAM.
//
//  Input:
//  IN EFI_HANDLE DispatchHandle - Dispatch handle for this handler
//  IN CONST VOID *Context OPTIONAL - Context for this dispatch 
//  IN VOID *CommBuffer OPTIONAL - Pointer to the buffer containing communication data
//  IN UINTN *CommBufferSize OPTIONAL - Pointer to the size of this communication buffer
//
//  Output:
//  EFI_STATUS
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS EFIAPI SaveBootScriptHandle(
  IN EFI_HANDLE  DispatchHandle,
  IN CONST VOID  *Context         OPTIONAL,
  IN OUT VOID    *CommBuffer      OPTIONAL,
  IN OUT UINTN   *CommBufferSize  OPTIONAL
){
    static BOOLEAN BootScriptSaveProcessed = FALSE;
    const CHAR16 AcpiGlobalVariable[] = ACPI_GLOBAL_VARIABLE;
    const EFI_GUID EfiAcpiVariableGuid = EFI_ACPI_VARIABLE_GUID;
    EFI_STATUS Status;
    UINTN VariableSize = sizeof(AcpiVariableSet);
    UINT8* BootScriptTable;

    if (BootScriptSaveProcessed) return EFI_SUCCESS;
    // We are setting the flag early intentionally.
    // We want to make sure the handle is executed once 
    // (even if failed to save the script due to errors).
    BootScriptSaveProcessed = TRUE;

    Status = pRS->GetVariable(
      (CHAR16*)AcpiGlobalVariable, (EFI_GUID*)&EfiAcpiVariableGuid,
      NULL,&VariableSize, &AcpiVariableSet
    );
    if (EFI_ERROR(Status)) return Status;
    BootScriptTable = (UINT8*)(UINTN)AcpiVariableSet->AcpiBootScriptTable;
    if (IsBadBuffer(BootScriptTable,0)) return EFI_NOT_FOUND;
    BootScriptTableSize = GetBootScriptTableLength(BootScriptTable);
    if (   BootScriptTableSize==0 
        || IsBadBuffer(BootScriptTable,BootScriptTableSize)
    ) return EFI_NOT_FOUND;

    Status = pSmst->SmmAllocatePool (EfiRuntimeServicesData, BootScriptTableSize, &SmmBootScriptBuffer);
    if (EFI_ERROR(Status)) return Status;
    MemCpy(SmmBootScriptBuffer, BootScriptTable, BootScriptTableSize);
    TRACE((TRACE_ALWAYS,"BootScriptHide: Boot script has been saved. Address: %X; Size :%X\n",BootScriptTable,BootScriptTableSize));
    
    SmmBootScriptTable = AcpiVariableSet->AcpiBootScriptTable;
    SmmAcpiReserveMemoryBase = AcpiVariableSet->AcpiReservedMemoryBase;
    SmmAcpiReserveMemorySize = AcpiVariableSet->AcpiReservedMemorySize;
    MemCpy(SmmAcpiFacsTable, AcpiVariableSet->AcpiFacsTable, sizeof(EFI_PHYSICAL_ADDRESS)*3);

    BootScriptSaved = TRUE;
    return EFI_SUCCESS;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//  Procedure:      RestoreBootScriptHandle
//
//  Description:    SMM Dispatch handler to restore the Boot Scripts from SMRAM
//                  to the regular system memory
//
//  Input:
//  IN EFI_HANDLE DispatchHandle - Handle of the 
//  IN CONST VOID *Context OPTIONAL - Context for this dispatch 
//  IN VOID *CommBuffer OPTIONAL - Pointer to the buffer containing communication data
//  IN UINTN *CommBufferSize OPTIONAL - Pointer to the size of this communication buffer
//
//  Output:
//  EFI_STATUS 
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS EFIAPI RestoreBootScriptHandle(
  IN EFI_HANDLE  DispatchHandle,
  IN CONST VOID  *Context         OPTIONAL,
  IN OUT VOID    *CommBuffer      OPTIONAL,
  IN OUT UINTN   *CommBufferSize  OPTIONAL
){
    UINT8* BootScriptTable;
    
    if ( !BootScriptSaved )
        return EFI_NOT_FOUND;

    // We are using AcpiReservedMemoryBase field as a communication mail box between this SMI handler
    // and companion PEIM that triggers SW SMI on S3 resume boot path.
    // The PEIM bitwise NOTs the value, and this handler sets it to BOOT_SCRIPT_RESTORE_SW_SMI_VALUE if boot script has been restored.
    // The values for AcpiReservedMemorySize, BootScriptTable, and AcpiFacsTable are also verified to be the same as the previous boot.
    if ((AcpiVariableSet->AcpiReservedMemoryBase != (~SmmAcpiReserveMemoryBase)) ||
        (AcpiVariableSet->AcpiReservedMemorySize != SmmAcpiReserveMemorySize))
        return EFI_NOT_FOUND;
	
    // If FACS entries are not correct, replace the pointers with known saved values and continue
    if (MemCmp(SmmAcpiFacsTable, AcpiVariableSet->AcpiFacsTable, sizeof(EFI_PHYSICAL_ADDRESS)*3))
    	MemCpy(AcpiVariableSet->AcpiFacsTable, SmmAcpiFacsTable, sizeof(EFI_PHYSICAL_ADDRESS)*3);

    // verify that the Boot Script is correct.  If not update it to the correct value
    if (AcpiVariableSet->AcpiBootScriptTable != SmmBootScriptTable)
        AcpiVariableSet->AcpiBootScriptTable = SmmBootScriptTable;
    
    //  Now verify the Boot Script Table 
    BootScriptTable = (UINT8*)(UINTN)AcpiVariableSet->AcpiBootScriptTable;
    // verify that the BootScript buffer location is outside of SMM Memory
    if ( IsBadBuffer(BootScriptTable,BootScriptTableSize) ) 
    	return EFI_NOT_FOUND;
#ifdef EFI_DEBUG
    //Let's see if boot script has actually been changed
    if (MemCmp(BootScriptTable, SmmBootScriptBuffer, BootScriptTableSize))
        TRACE((TRACE_ALWAYS,"BootScriptHide: The boot script has been changed.\n"));
    else
        TRACE((TRACE_ALWAYS,"BootScriptHide: The boot script hasn't been changed.\n"));
#endif
    MemCpy(BootScriptTable, SmmBootScriptBuffer, BootScriptTableSize);
    TRACE((TRACE_ALWAYS,"BootScriptHide: Boot script has been restored. Address: %X; Size :%X\n",BootScriptTable,BootScriptTableSize));
    AcpiVariableSet->AcpiReservedMemoryBase = BOOT_SCRIPT_RESTORE_SW_SMI_VALUE;
    return EFI_SUCCESS;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//  Procedure:      BootScriptHideSmmEntryPoint
//
//  Description:    SMM driver entry point.  This entry point will register SWSMI dispatch
//                  handlers to deal with the save and restore SWSMIs.
//
//  Input:
//  IN EFI_HANDLE ImageHandle - The handle that corresponds this this loaded SMM driver
//  IN EFI_SYSTEM_TABLE *SystemTable - Pointer to the EFI System Table
//
//  Output:
//  EFI_STATUS 
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS EFIAPI BootScriptHideSmmEntryPoint(IN EFI_HANDLE ImageHandle, IN EFI_SYSTEM_TABLE *SystemTable){
    EFI_STATUS Status;
    EFI_SMM_SW_DISPATCH2_PROTOCOL *SwDispatch;
    EFI_HANDLE Handle;
    EFI_SMM_SW_REGISTER_CONTEXT    Context;
    EFI_SMM_ACCESS2_PROTOCOL *SmmAccess;
    UINTN Size;
    
    InitAmiSmmLibPi(ImageHandle,SystemTable);
    
    // Get SMRAM information
    Status = pBS->LocateProtocol (&gEfiSmmAccess2ProtocolGuid, NULL, (VOID **)&SmmAccess);
    if (EFI_ERROR(Status)) return Status;
    
    Size = 0;
    Status = SmmAccess->GetCapabilities (SmmAccess, &Size, NULL);
    if (Status != EFI_BUFFER_TOO_SMALL) return Status;
    Status = pSmst->SmmAllocatePool (EfiRuntimeServicesData, Size, (VOID **)&SmramRanges);
    if (EFI_ERROR(Status)) return Status;
    Status = SmmAccess->GetCapabilities (SmmAccess, &Size, SmramRanges);
    if (EFI_ERROR(Status)) return Status;
    SmramRangeCount = Size / sizeof (EFI_SMRAM_DESCRIPTOR);

    // Register SW SMI handlers
    Status = pSmst->SmmLocateProtocol(&gEfiSmmSwDispatch2ProtocolGuid, NULL, &SwDispatch);
    if (EFI_ERROR(Status)) return Status;

    // Save Boot Script
    Context.SwSmiInputValue = BOOT_SCRIPT_SAVE_SW_SMI_VALUE;
    Status  = SwDispatch->Register(SwDispatch, SaveBootScriptHandle, &Context, &Handle);
    if (EFI_ERROR(Status)) return Status;
    // restore Boot Script
    Context.SwSmiInputValue = BOOT_SCRIPT_RESTORE_SW_SMI_VALUE;
    Status  = SwDispatch->Register(SwDispatch, RestoreBootScriptHandle, &Context, &Handle);
    if (EFI_ERROR(Status)) return Status;

    return EFI_SUCCESS;
}
//**********************************************************************
//**********************************************************************
//**                                                                  **
//**        (C)Copyright 1985-2016, American Megatrends, Inc.         **
//**                                                                  **
//**                       All Rights Reserved.                       **
//**                                                                  **
//**             5555 Oakbrook Pkwy, Norcross, GA 30093               **
//**                                                                  **
//**                       Phone: (770)-246-8600                      **
//**                                                                  **
//**********************************************************************
//**********************************************************************
