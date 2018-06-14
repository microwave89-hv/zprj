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
// $Header: /Alaska/SOURCE/Modules/AmiBufferValidationLib/AmiBufferValidationLib Include/AmiBufferValidationLib.h 3     12/30/14 4:09p Aaronp $
//
// $Revision: 3 $
//
// $Date: 12/30/14 4:09p $
//**********************************************************************
// Revision History
// ----------------
// $Log: /Alaska/SOURCE/Modules/AmiBufferValidationLib/AmiBufferValidationLib Include/AmiBufferValidationLib.h $
// 
// 3     12/30/14 4:09p Aaronp
// [TAG]  		EIP198005 
// [Category]  	Improvement
// [Description]  	Added support for pre PI 1.2
// 
// 2     11/26/14 10:33a Aaronp
// Updated function headers with additional information that was added to
// the AptioV component.
// 
// 1     11/07/14 12:07p Aaronp
// initial addition of AmiBufferValidationLib
// 
//**********************************************************************

//**********************************************************************
//<AMI_FHDR_START>
//
// Name:	AmiBufferValidationLib.h
//
// Description:	Header file that defines the AmiBufferValidationLib functions
//
//<AMI_FHDR_END>
//**********************************************************************

#ifndef __AMI_BUFFER_VALIDATION_LIB__H__
#define __AMI_BUFFER_VALIDATION_LIB__H__

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
EFI_STATUS InitAmiBufferValidationLib(IN EFI_HANDLE ImageHandle, IN EFI_SYSTEM_TABLE *SystemTable);


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
EFI_STATUS AmiValidateMemoryBuffer(VOID* Buffer, UINTN BufferSize);

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
EFI_STATUS AmiValidateMmioBuffer(VOID* Buffer, UINTN BufferSize);

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
EFI_STATUS AmiValidateSmramBuffer(VOID* Buffer, UINTN BufferSize);

#endif
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
