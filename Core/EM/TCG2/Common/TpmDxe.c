/*++

   Copyright (c) 2005 Intel Corporation. All rights reserved
   This software and associated documentation (if any) is furnished
   under a license and may only be used or copied in accordance
   with the terms of the license. Except as permitted by such
   license, no part of this software or documentation may be
   reproduced, stored in a retrieval system, or transmitted in any
   form or by any means without the express written consent of
   Intel Corporation.


   Module Name:

   TpmDxe.h

   Abstract:

   DXE driver for TPM devices

   --*/

//*************************************************************************
// $Header: /Alaska/SOURCE/Modules/TCG2/Common/TcgDxe/TpmDxe.c 2     4/21/14 3:17p Fredericko $
//
// $Revision: 2 $
//
// $Date: 4/21/14 3:17p $
//*************************************************************************
// Revision History
// ----------------
// $Log: /Alaska/SOURCE/Modules/TCG2/Common/TcgDxe/TpmDxe.c $
// 
// 2     4/21/14 3:17p Fredericko
// 
// 1     4/21/14 2:16p Fredericko
// 
// 2     3/11/14 6:35p Fredericko
// [TAG]  		EIP151925
// [Category]  	New Feature
// [Description]  	Changes for TcgGeneric Regression Testing
// 
// 1     10/08/13 12:03p Fredericko
// Initial Check-In for Tpm-Next module
// 
// 2     10/03/13 2:00p Fredericko
// 
// 1     7/10/13 5:51p Fredericko
// [TAG]  		EIP120969
// [Category]  	New Feature
// [Description]  	TCG (TPM20)
// 
// 13    11/14/11 1:27p Fredericko
// Changes for Tcgprotocol interface. Function is currently not used.
// 
// 12    3/31/11 4:57p Fredericko
// Changes for TCG_LEGACY support
// 
// 11    3/29/11 1:12p Fredericko
// 
// 10    3/28/11 2:19p Fredericko
// [TAG]        EIP 54642
// [Category] Improvement
// [Description] 1. Checkin Files related to TCG function override 
// 2. Include TCM and TPM auto detection
// [Files] Affects all TCG files
// 
// 9     5/19/10 5:31p Fredericko
// Included File Header
// Included File Revision History 
// Code Beautification
// EIP 37653
//
//*************************************************************************
//*************************************************************************
//<AMI_FHDR_START>
//
// Name:  TpmDxe.c
//
// Description: 
//  Abstracted functions for Tpm protocol are defined here
//
//<AMI_FHDR_END>
//*************************************************************************
#include <Efi.h>
#include "TcgTpm12.h"
#include <TpmLib.h>
#include <Protocol\TpmDevice\TpmDevice.h>
#include <AmiDxeLib.h>
#include <token.h>
#include "Tpm20CRBLib.h"


#define _CR( Record, TYPE,\
        Field )((TYPE*) ((CHAR8*) (Record) - (CHAR8*) &(((TYPE*) 0)->Field)))
        
EFI_GUID TcgGuid = AMI_TCG_RESETVAR_HOB_GUID;

VOID* LocateATcgHob (
    UINTN                   NoTableEntries,
    EFI_CONFIGURATION_TABLE *ConfigTable,
    EFI_GUID                *HOB_guid );

#define TPM_DXE_PRIVATE_DATA_FROM_THIS( this )  \
    _CR( this, TPM_DXE_PRIVATE_DATA, TpmInterface )

typedef struct _TPM_DXE_PRIVATE_DATA
{
    EFI_TPM_DEVICE_PROTOCOL TpmInterface;
    EFI_PHYSICAL_ADDRESS    BaseAddr;
} TPM_DXE_PRIVATE_DATA;

FixedDelay(UINT32 dCount);

static UINTN                  TpmFuncID;
static TPMTransmitEntryStruct TpmEmptyBuf;
static UINT32                 TpmRet;
static UINTN                  ReadytoBootVar = 0;


#if TCG_LEGACY == 0
EFI_STATUS
EFIAPI TpmDxeInit(
    IN EFI_TPM_DEVICE_PROTOCOL *This )
{
    EFI_STATUS Status;
    volatile TPM_1_2_REGISTERS_PTR TpmReg;
    TpmReg  = (TPM_1_2_REGISTERS_PTR)(( UINTN ) (PORT_TPM_IOMEMBASE));
    Status = TisRequestLocality(TpmReg);
    return Status;
}

EFI_STATUS
EFIAPI TpmDxeClose(
    IN EFI_TPM_DEVICE_PROTOCOL *This )
{
    EFI_STATUS Status;
    volatile TPM_1_2_REGISTERS_PTR TpmReg;
    TpmReg  = (TPM_1_2_REGISTERS_PTR)(( UINTN ) (PORT_TPM_IOMEMBASE));
    Status = TisReleaseLocality(TpmReg);
    return Status;  
}

EFI_STATUS
EFIAPI TpmDxeGetStatusInfo(
    IN EFI_TPM_DEVICE_PROTOCOL *This )
{
    return EFI_UNSUPPORTED;
}

EFI_STATUS
EFIAPI TpmDxeTransmit(
    IN EFI_TPM_DEVICE_PROTOCOL *This,
    IN UINTN                   NoInBuffers,
    IN TPM_TRANSMIT_BUFFER     *InBuffers,
    IN UINTN                   NoOutBuffers,
    IN OUT TPM_TRANSMIT_BUFFER *OutBuffers )
{
    volatile TPM_1_2_REGISTERS_PTR TpmReg;
    TpmReg  = (TPM_1_2_REGISTERS_PTR)(( UINTN ) (PORT_TPM_IOMEMBASE));

    TRACE(( TRACE_ALWAYS,"TpmReg.Access = %x \n", TpmReg->Access));
    return TpmLibPassThrough(
               TpmReg,
               NoInBuffers,
               InBuffers,
               NoOutBuffers,
               OutBuffers
               );
}

#else


//**********************************************************************
//<AMI_PHDR_START>
//
// Name: TpmDxeInit
//
// Description: Call to OEM driver to initialize TPM.
//
// Input:       IN  EFI_TPM_DEVICE_PROTOCOL   *This
//
// Returns:     EFI_STATUS
//
// Output:
//
// Modified:
//
// Referrals:
//
// Notes:
//<AMI_PHDR_END>
//**********************************************************************
EFI_STATUS
EFIAPI TpmDxeInit(
    IN EFI_TPM_DEVICE_PROTOCOL *This )
{
    return EFI_SUCCESS;  //init command is only sent once and done in PEI
}



//**********************************************************************
//<AMI_PHDR_START>
//
// Name:  TpmDxeClose
//
// Description: Close TPM connection for locality 0
//
// Input:       IN  PEI_TPM_PPI               *This,
//              IN  EFI_PEI_SERVICES          **PeiServices
//
// Output:      EFI STATUS
///
// Output:
//
// Modified:
//
// Referrals:
//
// Notes:
//<AMI_PHDR_END>
//**********************************************************************
EFI_STATUS
EFIAPI TpmDxeClose(
    IN EFI_TPM_DEVICE_PROTOCOL *This )
{
    return EFI_SUCCESS;
}




//**********************************************************************
//<AMI_PHDR_START>
//
//
// Name:  TpmDxeGetStatusInfo
//
// Description: GetStatus Info from MP driver
//
// Input:       IN  PEI_TPM_PPI               *This,
//              IN  EFI_PEI_SERVICES          **PeiServices
//
// Output:      EFI STATUS
//
// Output:
//
// Modified:
//
// Referrals:
//
// Notes:
//<AMI_PHDR_END>
//**********************************************************************
EFI_STATUS
EFIAPI  TpmDxeGetStatusInfo(
    IN EFI_TPM_DEVICE_PROTOCOL   * This
    )
{
    return EFI_UNSUPPORTED;
}



//**********************************************************************
//<AMI_PHDR_START>
//
// Procedure:   SetEfiOSTransitions
//
// Description: SetEfiOSTransitions
//
// Input:       IN  EFI_EVENT       efiev
//              IN  VOID            *ctx
//
// Output:      EFI_STATUS
//
// Modified:
//
// Referrals:
//
// Notes:
//<AMI_PHDR_END>
//**********************************************************************
void SetEfiOSTransitions(
    IN EFI_EVENT efiev,
    IN VOID      *ctx )
{
    ReadytoBootVar = 1;
}




//**********************************************************************
//<AMI_PHDR_START>
//
// Procedure:   EfiOSReadyToBoot
//
// Description: Sets ready to boot callback on ready to boot
//
// Input:   NONE    
//
// Output:   EFI_STATUS   
//
// Modified:
//
// Referrals:   
//
// Notes:       
//<AMI_PHDR_END>
//**********************************************************************
EFI_STATUS
EFIAPI EfiOSReadyToBoot()
{
   EFI_EVENT  ReadToBootEvent;
   EFI_STATUS Status;

   #if defined(EFI_EVENT_SIGNAL_READY_TO_BOOT)\
        && EFI_SPECIFICATION_VERSION < 0x20000
       
         Status = pBS->CreateEvent( EFI_EVENT_SIGNAL_READY_TO_BOOT,
                                   EFI_TPL_CALLBACK,
                                   SetEfiOSTransitions, NULL, &ReadToBootEvent );
        
   #else
        Status = CreateReadyToBootEvent( EFI_TPL_CALLBACK-1,
                                         SetEfiOSTransitions,
                                         NULL,
                                         &ReadToBootEvent );
   #endif

   return Status;
}



EFI_STATUS
EFIAPI EfiPreOSTransition(
    IN EFI_TPM_DEVICE_PROTOCOL *This,
    IN UINTN                   NoInBuffers,
    IN TPM_TRANSMIT_BUFFER     *InBuffers,
    IN UINTN                   NoOutBuffers,
    IN OUT TPM_TRANSMIT_BUFFER *OutBuffers )
{
    TPM_DXE_PRIVATE_DATA  *Private;
    TPM_1_2_REGISTERS_PTR TpmReg;
    EFI_STATUS            Status;

    Private = TPM_DXE_PRIVATE_DATA_FROM_THIS( This );

    TisRequestLocality(
               (TPM_1_2_REGISTERS_PTR)( UINTN ) Private->BaseAddr);

    TpmReg  = (TPM_1_2_REGISTERS_PTR)( UINTN ) Private->BaseAddr;

    Status = TpmLibPassThrough(
               TpmReg,
               NoInBuffers,
               InBuffers,
               NoOutBuffers,
               OutBuffers
               );

    TisReleaseLocality(
               (TPM_1_2_REGISTERS_PTR)( UINTN ) Private->BaseAddr);

    return Status;
}



//**********************************************************************
//<AMI_PHDR_START>
//
//
// Name: TpmDxeTransmit
//
// Description: Dxe Transmit Tcg Data
//
// Input:    IN      EFI_TPM_DEVICE_PROTOCOL   *This,
//           IN      UINTN                     NoInBuffers,
//           IN      TPM_TRANSMIT_BUFFER       *InBuffers,
//           IN      UINTN                     NoOutBuffers,
//           IN OUT  TPM_TRANSMIT_BUFFER       *OutBuffers
//
// Output:     EFI STATUS
//
// Output:
//
// Modified:
//
// Referrals:
//
// Notes:
//<AMI_PHDR_END>
//**********************************************************************

EFI_STATUS
EFIAPI TpmDxeTransmit(
    IN EFI_TPM_DEVICE_PROTOCOL *This,
    IN UINTN                   NoInBuffers,
    IN TPM_TRANSMIT_BUFFER     *InBuffers,
    IN UINTN                   NoOutBuffers,
    IN OUT TPM_TRANSMIT_BUFFER *OutBuffers )
{
    TPM_DXE_PRIVATE_DATA   *Private;
    TPMTransmitEntryStruct FillESI;
    UINTN                  FuncID = (UINTN)MP_FUNCTION_TRANSMIT;
    UINT32                 Ret;
    UINT8                  *SHA_ARRAY_OUT = NULL;
    BOOLEAN                FillBuff   = FALSE;
    BOOLEAN                Other      = FALSE;
    UINTN                  i = 0, loc = 0;
    UINT8                  *Tpm_SHA_ARRAY= NULL;
    EFI_STATUS             Status;


    if(NoInBuffers == 0 || InBuffers == NULL || NoOutBuffers == 0 || OutBuffers == NULL)
    return EFI_INVALID_PARAMETER;
    
    if(ReadytoBootVar == 1)
    {
         return EfiPreOSTransition(This, NoInBuffers, InBuffers, NoOutBuffers, OutBuffers);
    }


    FillESI.dwInLen = 0;
    FillESI.dwOutLen = 0;

 	for (; i < NoInBuffers; i++ )
   	{
       	FillESI.dwInLen += (UINT32)InBuffers[i].Size;
   	}

   	Status = pBS-> AllocatePool( EfiBootservicesData, FillESI.dwInLen, &Tpm_SHA_ARRAY);
    if(EFI_ERROR(Status))return Status;


    for (i = 0; i < NoOutBuffers; i++ )
   	{
      FillESI.dwOutLen += (UINT32)OutBuffers[i].Size;
	}
   	
    Status = pBS-> AllocatePool( EfiBootservicesData, FillESI.dwOutLen, &SHA_ARRAY_OUT );
    if(EFI_ERROR(Status))return Status;


    for (i = 0; i < NoInBuffers; i++ )
    {
        pBS->CopyMem(Tpm_SHA_ARRAY + loc,
                     InBuffers[i].Buffer,
                     InBuffers[i].Size );

        loc += InBuffers[i].Size;
    }

    FillESI.pbInBuf  = (UINT32)(EFI_PHYSICAL_ADDRESS) Tpm_SHA_ARRAY;
    FillESI.pbOutBuf = (UINT32)(EFI_PHYSICAL_ADDRESS) SHA_ARRAY_OUT;

    Private = TPM_DXE_PRIVATE_DATA_FROM_THIS( This );
    TpmDxeCallMPDriver( FuncID, &FillESI, &Ret );

    if ( Tpm_SHA_ARRAY != NULL )
    {
        pBS->FreePool( Tpm_SHA_ARRAY );
    }

    loc = 0;

    for (i=0; i < NoOutBuffers; i++ )
    {
       pBS->CopyMem( OutBuffers[i].Buffer,
                    &SHA_ARRAY_OUT[loc],
                    OutBuffers[i].Size );
       loc += (UINTN)OutBuffers[i].Size;
    }

    if ( SHA_ARRAY_OUT != NULL )
    {
        pBS->FreePool( SHA_ARRAY_OUT );
    }

    return EFI_SUCCESS;
}

#endif

static TPM_DXE_PRIVATE_DATA mTpmPrivate = {
    {
        TpmDxeInit,
        TpmDxeClose,
        TpmDxeGetStatusInfo,
        TpmDxeTransmit
    },
    TPM_BASE_ADDRESS
};




EFI_STATUS
EFIAPI TpmDxeEntry(
    IN EFI_HANDLE       ImageHandle,
    IN EFI_SYSTEM_TABLE *SystemTable )
{
    EFI_STATUS Status;
#if TCG_LEGACY == 1
    EFI_GUID        gMpDriverHobGuid = EFI_TCG_MPDriver_HOB_GUID;
    FAR32LOCALS     	 *TempLoc   = NULL;
#endif

#if TCG_LEGACY == 0
    Status = IsTpmPresent((TPM_1_2_REGISTERS_PTR)( UINTN ) mTpmPrivate.BaseAddr );

    if ( EFI_ERROR( Status ))
    {
        if(isTpm20CrbPresent())return EFI_SUCCESS;
        return EFI_UNLOAD_IMAGE;
    }
#else
    TempLoc = (FAR32LOCALS*)LocateATcgHob( pST->NumberOfTableEntries,
                                           pST->ConfigurationTable,
                                           &gMpDriverHobGuid );


    if(TempLoc == NULL || TempLoc->Offset == NULL  ) return EFI_NOT_FOUND;
    Prepare2Thunkproc( TempLoc->Offset, TempLoc->Selector ); 
    Status = EfiOSReadyToBoot();   
#endif

    Status = pBS->InstallMultipleProtocolInterfaces(
        &ImageHandle,
        &gEfiTpmDeviceProtocolGuid,
        &mTpmPrivate.TpmInterface,
        NULL
        );

    return Status;
}



EFI_GUID gEfiTpmDeviceProtocolGuid = EFI_TPM_DEVICE_PROTOCOL_GUID;
