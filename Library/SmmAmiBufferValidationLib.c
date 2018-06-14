//**********************************************************************
//**********************************************************************
//**                                                                  **
//**        (C)Copyright 1985-2014, American Megatrends, Inc.         **
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
// $Header: /Alaska/SOURCE/Modules/AmiBufferValidationLib/SmmAmiBufferValidationLib.c 4     1/06/15 10:21a Aaronp $
//
// $Revision: 4 $
//
// $Date: 1/06/15 10:21a $
//**********************************************************************
// Revision History
// ----------------
// $Log: /Alaska/SOURCE/Modules/AmiBufferValidationLib/SmmAmiBufferValidationLib.c $
// 
// 4     1/06/15 10:21a Aaronp
// [TAG]  		EIP198890
// [Category]  	Improvement
// [Description]  	Use of CORE_COMBINED_VERSION requires Token.h to be
// included.
// 
// 3     12/30/14 4:08p Aaronp
// [TAG]  		EIP198005 
// [Category]  	Improvement
// [Description]  	Added support for pre PI 1.2
// 
// 2     11/26/14 10:33a Aaronp
// Updated function headers with additional information that was added to
// the AptioV component.
// 
// 1     11/07/14 12:07p Aaronp
// Initial addition of AmiBufferValidationLib
// 
//**********************************************************************

//**********************************************************************
//<AMI_FHDR_START>
//
// Name:	SmmAmiBufferValidationLib.c
//
// Description:	Source file that defines the AmiBufferValidationLib functions
//              used for validating that buffer addresses and MMIO addreses
//              do not reside in SMM. The file also provides a function to
//              validate that a buffer does reside in SMM.
//
//<AMI_FHDR_END>
//**********************************************************************
#include <Token.h>
#include <AmiDxeLib.h>
#if defined(PI_SPECIFICATION_VERSION)&&(PI_SPECIFICATION_VERSION>=0x0001000A)
#include <Protocol/SmmAccess2.h>
#else
#include <Protocol/SmmAccess.h>
#endif

/// Internal list of SMRAM regions
EFI_SMRAM_DESCRIPTOR *SmmAmiBufferValidationLibSmramRanges = NULL;

/// Number of SMRAM regions in the internal list
UINTN SmmAmiBufferValidationLibNumberOfSmramRange = 0;

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//  Procedure:      AmiValidateMemoryBuffer
//
//  Description:    Function verifies the buffer to make sure its address range is legal for a memory buffer. A legal memory 
//                  buffer is one that lies entirely outside of SMRAM.  SMI handlers that receive buffer address and/or size 
//                  from outside of SMM at runtime must validate the buffer using this function prior to using it or passing 
//                  to other SMM interfaces.
//
//  Input:
//      VOID *Buffer - Buffer address 
//      UINTN BufferSize - Size of the Buffer
//
//  Output:
//      EFI_SUCCESS - The buffer address range is valid and can be safely used.
//      EFI_ACCESS_DENIED - The buffer can't be used because its address range overlaps with protected area such as SMRAM.
//      EFI_INVALID_PARAMETER - The buffer can't be used because its address range is invalid.
//      EFI_NOT_FOUND - The buffer can't be used because its validity cannot be verified. Normally due to the SMRAM ranges were not available.
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS AmiValidateMemoryBuffer(VOID* Buffer, UINTN BufferSize){
	UINTN  i;
	UINTN BufferAddress;

	if (SmmAmiBufferValidationLibNumberOfSmramRange==0) return EFI_NOT_FOUND;

	BufferAddress = (UINTN)Buffer;
	if (BufferAddress + BufferSize < BufferAddress) return EFI_INVALID_PARAMETER; // overflow
	for (i = 0; i < SmmAmiBufferValidationLibNumberOfSmramRange; i ++) {
		if (    BufferAddress >= SmmAmiBufferValidationLibSmramRanges[i].CpuStart
    	     && BufferAddress < SmmAmiBufferValidationLibSmramRanges[i].CpuStart + SmmAmiBufferValidationLibSmramRanges[i].PhysicalSize
    	) return EFI_ACCESS_DENIED; // Buffer starts in SMRAM
        if (    BufferAddress < SmmAmiBufferValidationLibSmramRanges[i].CpuStart
    	     && BufferAddress+BufferSize > SmmAmiBufferValidationLibSmramRanges[i].CpuStart
        ) return EFI_ACCESS_DENIED; // Buffer overlaps with SMRAM
	}
	
	return EFI_SUCCESS;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//  Procedure:      AmiValidateMmioBuffer
//
//  Description:    Function verifies the buffer to make sure its address range is legal for a MMIO buffer.  A legal MMIO buffer is one that lies 
//                  entirely outside of SMRAM.  SMI handlers that receive a buffer address and/or size from outside of SMM at runtime must validate 
//                  the buffer using this function prior to using the MMIO Buffer or passing to other SMM interfaces.
//
//  Input:
//      VOID *Buffer - Buffer address 
//      UINTN BufferSize - Size of the Buffer
//
//  Output:
//      EFI_SUCCESS - The buffer address range is valid and can be safely used.
//      EFI_ACCESS_DENIED - The buffer can't be used because its address range overlaps with protected area such as SMRAM.
//      EFI_INVALID_PARAMETER - The buffer can't be used because its address range is invalid.
//      EFI_NOT_FOUND - The buffer can't be used because its validity cannot be verified. Normally due to the SMRAM ranges were not available.
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS AmiValidateMmioBuffer(VOID* Buffer, UINTN BufferSize){
	return AmiValidateMemoryBuffer(Buffer,BufferSize);
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//  Procedure:      AmiValidateSmramBuffer
//
//  Description:    Function verifies the buffer to make sure it wholly resides in the SMRAM.
//
//  Input:
//      IN VOID *Buffer - Buffer address 
//      IN UINTN BufferSize - Size of the Buffer
//
//  Output:
//      EFI_SUCCESS - The buffer resides in the SMRAM and can be safely used.
//      EFI_ACCESS_DENIED - The buffer can't be used because at least one byte of the buffer is outside of SMRAM.
//      EFI_INVALID_PARAMETER - The buffer can't be used because its address range is invalid.
//      EFI_NOT_FOUND - The buffer can't be used because its validity cannot be verified. Normally due to the SMRAM ranges were not available.
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS AmiValidateSmramBuffer(VOID* Buffer, UINTN BufferSize){
	UINTN  i;
	UINTN BufferAddress;

	if (SmmAmiBufferValidationLibNumberOfSmramRange==0) return EFI_NOT_FOUND;

	BufferAddress = (UINTN)Buffer;
	if (BufferAddress + BufferSize < BufferAddress) return EFI_INVALID_PARAMETER; // overflow
	for (i = 0; i < SmmAmiBufferValidationLibNumberOfSmramRange; i ++) {
		if (    BufferAddress >= SmmAmiBufferValidationLibSmramRanges[i].CpuStart
    	     && BufferAddress+BufferSize <= SmmAmiBufferValidationLibSmramRanges[i].CpuStart + SmmAmiBufferValidationLibSmramRanges[i].PhysicalSize
    	) return EFI_SUCCESS; // Entire Buffer is in SMRAM
	}
	
	return EFI_ACCESS_DENIED;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//  Procedure:      InitAmiBufferValidationLib
//
//  Description:    Performs the necessary initialization so that the buffer validation functions will operate 
//                  correctly when they are called.
//
//  Input:
//  IN EFI_HANDLE ImageHandle - The handle of this image
//  IN EFI_SYSTEM_TABLE *SystemTable - Pointer to the EFI_SYSTEM_TABLE
//
//  Output:
//      EFI_NOT_FOUND - The Smm Access protocol could not be found
//      EFI_OUT_OF_RESOURCES - An allocation failed because it could not find any memory resources 
//      EFI_INVALID_PARAMETER - An invalid parameter was passed to one of the functions
//      EFI_SUCCESS - The necessary functions were initialized
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS EFIAPI InitAmiBufferValidationLib(IN EFI_HANDLE ImageHandle, IN EFI_SYSTEM_TABLE *SystemTable){
    EFI_STATUS Status;
#if defined(PI_SPECIFICATION_VERSION)&&(PI_SPECIFICATION_VERSION>=0x0001000A)
    EFI_SMM_ACCESS2_PROTOCOL *SmmAccess;
#else	
    EFI_SMM_ACCESS_PROTOCOL *SmmAccess;
#endif	
    UINTN Size;

#if defined(CORE_COMBINED_VERSION)&&(CORE_COMBINED_VERSION>0x4028a)
    InitAmiSmmLib(ImageHandle,SystemTable);
#endif

    // Get SMRAM information
#if defined(PI_SPECIFICATION_VERSION)&&(PI_SPECIFICATION_VERSION>=0x0001000A)	
    Status = pBS->LocateProtocol (&gEfiSmmAccess2ProtocolGuid, NULL, (VOID **)&SmmAccess);
#else	
    Status = pBS->LocateProtocol (&gEfiSmmAccessProtocolGuid, NULL, (VOID **)&SmmAccess);
#endif	
    if (EFI_ERROR(Status)) return Status;
    
    Size = 0;
    Status = SmmAccess->GetCapabilities (SmmAccess, &Size, NULL);
    if (Status != EFI_BUFFER_TOO_SMALL) return Status;
    Status = pSmst->SmmAllocatePool (EfiRuntimeServicesData, Size, (VOID **)&SmmAmiBufferValidationLibSmramRanges);
    if (EFI_ERROR(Status)){
    	SmmAmiBufferValidationLibSmramRanges = NULL;
    	return Status;
    }
    Status = SmmAccess->GetCapabilities (SmmAccess, &Size, SmmAmiBufferValidationLibSmramRanges);
    if (EFI_ERROR(Status)){
    	pSmst->SmmFreePool (SmmAmiBufferValidationLibSmramRanges);
    	SmmAmiBufferValidationLibSmramRanges = NULL;
    	return Status;
    }
    SmmAmiBufferValidationLibNumberOfSmramRange = Size / sizeof (EFI_SMRAM_DESCRIPTOR);

    return EFI_SUCCESS;
}

//**********************************************************************
//**********************************************************************
//**                                                                  **
//**        (C)Copyright 1985-2014, American Megatrends, Inc.         **
//**                                                                  **
//**                       All Rights Reserved.                       **
//**                                                                  **
//**      5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093        **
//**                                                                  **
//**                       Phone: (770)-246-8600                      **
//**                                                                  **
//**********************************************************************
//**********************************************************************
