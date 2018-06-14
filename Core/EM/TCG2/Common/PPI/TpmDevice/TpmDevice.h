//**********************************************************************
//**********************************************************************
//**                                                                  **
//**        (C)Copyright 1985-2013, American Megatrends, Inc.         **
//**                                                                  **
//**                       All Rights Reserved.                       **
//**                                                                  **
//**     5555 Oakbrook Pkwy, Suite 200, Norcross, GA 30093            **
//**                                                                  **
//**                       Phone: (770)-246-8600                      **
//**                                                                  **
//**********************************************************************
//**********************************************************************
/*++

   Copyright (c)  2005 Intel Corporation. All rights reserved
   This software and associated documentation (if any) is furnished
   under a license and may only be used or copied in accordance
   with the terms of the license. Except as permitted by such
   license, no part of this software or documentation may be
   reproduced, stored in a retrieval system, or transmitted in any
   form or by any means without the express written consent of
   Intel Corporation.

   Abstract:

   TPM PPI as defined in EFI 2.0

   --*/
//*************************************************************************
// $Header: /Alaska/SOURCE/Modules/TCG2/CommonHeaders/TpmDevice_PPI/TpmDevice/TpmDevice.h 1     4/21/14 2:15p Fredericko $
//
// $Revision: 1 $
//
// $Date: 4/21/14 2:15p $
//*************************************************************************
// Revision History
// ----------------
// $Log: /Alaska/SOURCE/Modules/TCG2/CommonHeaders/TpmDevice_PPI/TpmDevice/TpmDevice.h $
// 
// 1     4/21/14 2:15p Fredericko
// 
// 1     10/08/13 12:01p Fredericko
// Initial Check-In for Tpm-Next module
// 
// 1     7/10/13 5:59p Fredericko
// [TAG]  		EIP120969
// [Category]  	New Feature
// [Description]  	TCG (TPM20)
// 
// 8     3/31/13 6:42p Fredericko
// [TAG]  		EIP113715
// [Category]  	Improvement
// [Description]  	Please update the copyright header according to AMI
// copyright rule
// [Files]  		Multiple Files
// 
// 7     3/29/11 3:09p Fredericko
// 
// 6     3/28/11 3:25p Fredericko
// [TAG]        EIP 54642
// [Category] Improvement
// [Description] 1. Checkin Files related to TCG function override 
// 2. Include TCM and TPM auto detection
// [Files] Affects all TCG files
// 
// 5     5/20/10 8:45a Fredericko
// Included File Header
// Included File Revision History 
// EIP 37653
//
//*************************************************************************
//*************************************************************************
//<AMI_FHDR_START>
//
// Name:  TpmDevice.h
//
// Description: 
//  Header file for TpmDevice.c[Ppi]
//
//<AMI_FHDR_END>
//*************************************************************************
#ifndef _PEI_TPMDEVICE_H_
#define _PEI_TPMDEVICE_H_

#include <TcgEfiTpm.h>
#include <TcgEfi12.h>

#define PEI_TPM_PPI_GUID \
    {0xca4853f4, 0xe94b, 0x42b4, 0x86, 0x42, 0xcd, 0xe2, 0x8a, 0x7f, 0xac, 0x2d}

#define TPM_DEACTIVATED_VARIABLE_NAME \
    L"IsTpmDeactivated"

struct _PEI_TPM_PPI;
typedef struct _PEI_TPM_PPI PEI_TPM_PPI;

typedef
EFI_STATUS
(EFIAPI * PEI_TPM_INIT)(
    IN PEI_TPM_PPI      *This,
    IN EFI_PEI_SERVICES **PeiServices
    );

typedef
EFI_STATUS
(EFIAPI * PEI_TPM_CLOSE)(
    IN PEI_TPM_PPI      *This,
    IN EFI_PEI_SERVICES **PeiServices
    );

typedef
EFI_STATUS
(EFIAPI * PEI_TPM_GET_STATUS_INFO)(
    IN PEI_TPM_PPI      *This,
    IN EFI_PEI_SERVICES **PeiServices
    );


VOID FillDriverLoc (
    UINT32           * Offset,
    EFI_PEI_SERVICES **ps,
    EFI_GUID         *Driveguid );

VOID MAFillDriverLoc (
    MASTRUCT         *Data,
    EFI_PEI_SERVICES **ps,
    EFI_GUID         *Driveguid );

EFI_STATUS FillDriverLocByFile (
    UINT32           * Offset,
    EFI_PEI_SERVICES **ps,
    EFI_GUID         *Driveguid,
    void             **MAStart,
    UINTN            *MASize );


EFI_STATUS
EFIAPI TpmPeiEntry (
    IN EFI_FFS_FILE_HEADER *FfsHeader,
    IN EFI_PEI_SERVICES    **PeiServices );


typedef
EFI_STATUS
(EFIAPI * PEI_TPM_TRANSMIT)(
    IN PEI_TPM_PPI             *This,
    IN EFI_PEI_SERVICES        **PeiServices,
    IN UINTN                   NoInputBuffers,
    IN TPM_TRANSMIT_BUFFER     *InputBuffers,
    IN UINTN                   NoOutputBuffers,
    IN OUT TPM_TRANSMIT_BUFFER *OutputBuffers
    );

typedef struct _PEI_TPM_PPI
{
    PEI_TPM_INIT            Init;
    PEI_TPM_CLOSE           Close;
    PEI_TPM_GET_STATUS_INFO GetStatusInfo;
    PEI_TPM_TRANSMIT        Transmit;
} PEI_TPM_PPI;

extern EFI_GUID gPeiTpmPpiGuid;

#endif

//**********************************************************************
//**********************************************************************
//**                                                                  **
//**        (C)Copyright 1985-2013, American Megatrends, Inc.         **
//**                                                                  **
//**                       All Rights Reserved.                       **
//**                                                                  **
//**     5555 Oakbrook Pkwy, Suite 200, Norcross, GA 30093            **
//**                                                                  **
//**                       Phone: (770)-246-8600                      **
//**                                                                  **
//**********************************************************************
//**********************************************************************
