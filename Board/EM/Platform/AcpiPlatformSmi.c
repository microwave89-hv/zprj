//*************************************************************************
//*************************************************************************
//**                                                                     **
//**        (C)Copyright 1985-2011, American Megatrends, Inc.            **
//**                                                                     **
//**                       All Rights Reserved.                          **
//**                                                                     **
//**      5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093           **
//**                                                                     **
//**                       Phone: (770)-246-8600                         **
//**                                                                     **
//*************************************************************************
//*************************************************************************

//*************************************************************************
// $Header: /Alaska/SOURCE/Modules/SharkBayRefCodes/Platform/AcpiPlatformSmi.c 1     2/09/12 12:30a Yurenlai $
//
// $Revision: 1 $
//
// $Date: 2/09/12 12:30a $
//*************************************************************************
// Revision History
// ----------------
// $Log: /Alaska/SOURCE/Modules/SharkBayRefCodes/Platform/AcpiPlatformSmi.c $
// 
// 1     2/09/12 12:30a Yurenlai
// Initial check in.
// 
//*************************************************************************

//<AMI_FHDR_START>
//----------------------------------------------------------------------------
//
// Name:        AcpiPlatformSmi.c
//
// Description: This file contains code for all AcpiPlatform SMI events
//
//----------------------------------------------------------------------------
//<AMI_FHDR_END>

//----------------------------------------------------------------------------
// Include(s)
//----------------------------------------------------------------------------

#include <Token.h>
#include <AmiDxeLib.h>
#include <AmiCspLib.h>
#include "SmmChildDispatch.h"

// Produced Protocols

// Consumed Protocols
#include <Protocol\SmmBase.h>

//----------------------------------------------------------------------------
// Constant, Macro and Type Definition(s)
//----------------------------------------------------------------------------
// Constant Definition(s)


// Macro Definition(s)

// Type Definition(s)

// Function Prototype(s)

//----------------------------------------------------------------------------
// Variable and External Declaration(s)
//----------------------------------------------------------------------------
// Variable Declaration(s)


// GUID Definition(s)

EFI_GUID gEfiSmmBaseProtocolGuid      = EFI_SMM_BASE_PROTOCOL_GUID;
EFI_GUID gSxDispatchProtocolGuid      = EFI_SMM_SX_DISPATCH_PROTOCOL_GUID;



//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure: S3PowerReductionFunction
//
// Description: Driving GPIO46 Output to low
//
// Input: None
//
// Output: None
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

VOID S3PowerReductionFunction(VOID)
{
 // UINT32                 Buffer32;

 // Buffer32 = IoRead32(GPIO_BASE_ADDRESS + ICH_GPIO_GP_LVL2);   // GPIO Level Select 2 Register
 // Buffer32 &= 0xFFFFBFFF;
//  IoWrite32(GPIO_BASE_ADDRESS + ICH_GPIO_GP_LVL2, Buffer32);   // Program GPIO level drive to logic high

}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:   AcpiPlatformSxSmiHandler
//
// Description: This is a AcpiPlatform Sx SMI Handler for Calpella Platform.
//
// Input:  DispatchHandle  - EFI Handle
//         DispatchContext - Pointer to the EFI_SMM_SX_DISPATCH_CONTEXT
//
// Output:     None
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

VOID AcpiPlatformSxSmiHandler(
    IN EFI_HANDLE                   DispatchHandle,
    IN EFI_SMM_SX_DISPATCH_CONTEXT  *DispatchContext)
{
        if (DispatchContext->Type == SxS3) 
          S3PowerReductionFunction();        

}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:   InSmmFunction
//
// Description: Installs AcpiPlatform SMM Child Dispatcher Handler.
//
// Parameters:  ImageHandle - Image handle
//              *SystemTable - Pointer to the system table
//
// Returns:     EFI_STATUS
//
// Modified:
//
// Referrals:
//
// Notes:
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS InSmmFunction (
    IN EFI_HANDLE       ImageHandle,
    IN EFI_SYSTEM_TABLE *SystemTable )
{
    EFI_STATUS                   Status;
    EFI_HANDLE                   Handle;
    EFI_SMM_BASE_PROTOCOL        *SmmBaseProtocol;
    // Sx SMI
    EFI_SMM_SX_DISPATCH_PROTOCOL *pSxDispatch;
    EFI_SMM_SX_DISPATCH_CONTEXT  SxS1Context = {SxS1, SxEntry};
    EFI_SMM_SX_DISPATCH_CONTEXT  SxS3Context = {SxS3, SxEntry};
    EFI_SMM_SX_DISPATCH_CONTEXT  SxS4Context = {SxS4, SxEntry};
    EFI_SMM_SX_DISPATCH_CONTEXT  SxS5Context = {SxS5, SxEntry};

    Status = pBS->LocateProtocol( &gEfiSmmBaseProtocolGuid, \
                                  NULL, \
                                  &SmmBaseProtocol );
    if (EFI_ERROR(Status)) return Status;

    // Local SMI Procotol
    Status = pBS->LocateProtocol(
                  &gSxDispatchProtocolGuid,
                  NULL,
                  &pSxDispatch);
    if (EFI_ERROR(Status))
        pSxDispatch = NULL;

    // Register SMIs
    if (pSxDispatch != NULL)
    {
        Status = pSxDispatch->Register(
                      pSxDispatch,
                      AcpiPlatformSxSmiHandler,
                      &SxS1Context,
                      &Handle);

        Status = pSxDispatch->Register(
                      pSxDispatch,
                      AcpiPlatformSxSmiHandler,
                      &SxS3Context,
                      &Handle);

        Status = pSxDispatch->Register(
                      pSxDispatch,
                      AcpiPlatformSxSmiHandler,
                      &SxS4Context,
                      &Handle);

        Status = pSxDispatch->Register(
                      pSxDispatch,
                      AcpiPlatformSxSmiHandler,
                      &SxS5Context,
                      &Handle);
    }



    return EFI_SUCCESS;

}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:   InitializeAcpiPlatformSMISmm
//
// Description: Installs AcpiPlatform SMM Child Dispatcher Handler.
//
// Parameters:  ImageHandle - Image handle
//              *SystemTable - Pointer to the system table
//
// Returns:     EFI_STATUS
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS InitializeAcpiPlatformSMISmm (
    IN EFI_HANDLE       ImageHandle,
    IN EFI_SYSTEM_TABLE *SystemTable )
{

  InitAmiLib(ImageHandle, SystemTable);

  return InitSmmHandler(ImageHandle, SystemTable, InSmmFunction, NULL);
}

//*************************************************************************
//*************************************************************************
//**                                                                     **
//**        (C)Copyright 1985-2011, American Megatrends, Inc.            **
//**                                                                     **
//**                       All Rights Reserved.                          **
//**                                                                     **
//**      5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093           **
//**                                                                     **
//**                       Phone: (770)-246-8600                         **
//**                                                                     **
//*************************************************************************
//*************************************************************************
