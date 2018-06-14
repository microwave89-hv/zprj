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


   --*/
//*************************************************************************
// $Header: /Alaska/SOURCE/Modules/TCG2/CommonHeaders/TpmDevice_Protocol/TpmDevice/TpmDevice.h 1     4/21/14 2:15p Fredericko $
//
// $Revision: 1 $
//
// $Date: 4/21/14 2:15p $
//*************************************************************************
// Revision History
// ----------------
// $Log: /Alaska/SOURCE/Modules/TCG2/CommonHeaders/TpmDevice_Protocol/TpmDevice/TpmDevice.h $
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
// 7     3/29/11 3:10p Fredericko
// 
// 6     3/28/11 3:27p Fredericko
// [TAG]        EIP 54642
// [Category] Improvement
// [Description] 1. Checkin Files related to TCG function override
// 2. Include TCM and TPM auto detection
// [Files] Affects all TCG files
// 
// 5     5/20/10 8:47a Fredericko
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
//  Header file for TpmDevice.c[Protocol]
//
//<AMI_FHDR_END>
//*************************************************************************
#ifndef _EFI_TPM_DEVICE_H_
#define _EFI_TPM_DEVICE_H_

#include "TcgEfiTpm.h"
#include "TcgEFI12.h"
#include "TCGMisc.h"
#include "TcgCommon.h"

#define EFI_TPM_DEVICE_PROTOCOL_GUID \
    { 0xde161cfe, 0x1e60, 0x42a1, 0x8c, 0xc3, 0xee, 0x7e, 0xf0, 0x73, 0x52,\
      0x12 }


EFI_FORWARD_DECLARATION( EFI_TPM_DEVICE_PROTOCOL );


typedef
EFI_STATUS
(EFIAPI * EFI_TPM_MP_INIT)(
    IN EFI_TPM_DEVICE_PROTOCOL *This
    );

/*++

   Routine Description:
    This service Open the TPM interface

   Arguments:
    This              - A pointer to the EFI_TPM_MP_DRIVER_PROTOCOL.

   Returns:
    EFI_SUCCESS       - Operation completed successfully
    EFI_DEVICE_ERROR  - The command was unsuccessful
    EFI_NOT_FOUND     - The component was not running

   --*/

typedef
EFI_STATUS
(EFIAPI * EFI_TPM_MP_CLOSE)(
    IN EFI_TPM_DEVICE_PROTOCOL *This
    );
/*++

   Routine Description:
    This service close the TPM interface and deactivate TPM

   Arguments:
    This              - A pointer to the EFI_TPM_MP_DRIVER_PROTOCOL.

   Returns:
    EFI_SUCCESS       - Operation completed successfully
    EFI_DEVICE_ERROR  - The command was unsuccessful
    EFI_NOT_FOUND     - The component was not running

   --*/

typedef
EFI_STATUS
(EFIAPI * EFI_TPM_MP_GET_STATUS_INFO)(
    IN EFI_TPM_DEVICE_PROTOCOL *This
    );
/*++

   Routine Description:
    This service get the current status infomation of TPM

   Arguments:
    This              - A pointer to the EFI_TPM_MP_DRIVER_PROTOCOL.
    ReqStatusType     - Requested type of status information, driver or device.
    Status            - Pointer to the returned status.

   Returns:
    EFI_SUCCESS           - Operation completed successfully
    EFI_DEVICE_ERROR      - The command was unsuccessful
    EFI_INVALID_PARAMETER - One or more of the parameters are incorrect
    EFI_BUFFER_TOO_SMALL  - The receive buffer is too small
    EFI_NOT_FOUND         - The component was not running

   --*/


typedef
EFI_STATUS
(EFIAPI * EFI_TPM_MP_TRANSMIT)(
    IN EFI_TPM_DEVICE_PROTOCOL *This,
    IN UINTN                   NoInBuffers,
    IN TPM_TRANSMIT_BUFFER     *InBuffers,
    IN UINTN                   NoOutBuffers,
    IN OUT TPM_TRANSMIT_BUFFER *OutBuffers
    );
/*++

   Routine Description:
    This service transmit data to the TPM and get response from TPM

   Arguments:
    This            - A pointer to the EFI_TPM_MP_DRIVER_PROTOCOL.

   Returns:
    EFI_SUCCESS           - Operation completed successfully
    EFI_DEVICE_ERROR      - The command was unsuccessful
    EFI_INVALID_PARAMETER - One or more of the parameters are incorrect
    EFI_BUFFER_TOO_SMALL  - The receive buffer is too small
    EFI_NOT_FOUND         - The component was not running

   --*/


void Prepare2Thunkproc (
    UINT32 TcgOffset,
    UINT16 TcgSelector );

void TcmDxeCallMPDriver (
    IN UINTN               CFuncID,
    TPMTransmitEntryStruct *CData,
    UINT32* OUT            CRetVal );

void TpmDxeCallMPDriver (
    IN UINTN               CFuncID,
    TPMTransmitEntryStruct *CData,
    UINT32* OUT            CRetVal );


typedef struct _EFI_TPM_DEVICE_PROTOCOL
{
    EFI_TPM_MP_INIT            Init;
    EFI_TPM_MP_CLOSE           Close;
    EFI_TPM_MP_GET_STATUS_INFO GetStatusInfo;
    EFI_TPM_MP_TRANSMIT        Transmit;
} EFI_TPM_DEVICE_PROTOCOL;

extern EFI_GUID gEfiTpmDeviceProtocolGuid;

#endif
