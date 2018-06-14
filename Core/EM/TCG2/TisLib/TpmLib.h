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

   TpmLib.h

   Abstract:

   Header file for tpm device drivers

   --*/
//*************************************************************************
// $Header: /Alaska/SOURCE/Modules/TCG2/Libraries/TisLib/TpmLib.h 1     4/21/14 2:14p Fredericko $
//
// $Revision: 1 $
//
// $Date: 4/21/14 2:14p $
//*************************************************************************
// Revision History
// ----------------
// $Log: /Alaska/SOURCE/Modules/TCG2/Libraries/TisLib/TpmLib.h $
// 
// 1     4/21/14 2:14p Fredericko
// 
// 1     10/08/13 11:58a Fredericko
// Initial Check-In for Tpm-Next module
// 
// 1     7/10/13 5:50p Fredericko
// [TAG]  		EIP120969
// [Category]  	New Feature
// [Description]  	TCG (TPM20)
// [Files]  		TisLib.cif
// TisLib.mak
// TcgTpm12.h
// TpmLib.h
// TcgCommon.h
// ZTEICTcmOrdinals.h
// TpmLib.c
// TcgCommon.c
// TisLib.sdl
// sha1.h
// INTTcgAcpi.h
// TcgPc.h
// TcmPc.h
// TcgEfiTpm.h
// TcgEFI12.h
// 
// 3     5/19/10 5:11p Fredericko
// Included File Header
// Included File Revision History 
// EIP 37653
//
//*************************************************************************
//*************************************************************************
//<AMI_FHDR_START>
//
// Name:  TpmLib.c
//
// Description: 
//  Header file for TpmLib.c
//
//<AMI_FHDR_END>
//*************************************************************************

#ifndef _TPMLIB_H_
#define _TPMLIB_H_

#include "TcgPc.h"

#define TisCompleteCommand          TisPrepareSendCommand

extern
EFI_STATUS
__stdcall TisRequestLocality (
    IN TPM_1_2_REGISTERS_PTR TpmReg );

extern
EFI_STATUS
__stdcall TisReleaseLocality (
    IN TPM_1_2_REGISTERS_PTR TpmReg );

extern
EFI_STATUS
__stdcall TisPrepareSendCommand (
    IN TPM_1_2_REGISTERS_PTR TpmReg );

extern
EFI_STATUS
__stdcall TisSendCommand (
    IN TPM_1_2_REGISTERS_PTR TpmReg,
    IN const VOID            *CmdStream,
    IN UINTN                 Size,
    IN BOOLEAN               Last );

extern
EFI_STATUS
__stdcall TisWaitForResponse (
    IN TPM_1_2_REGISTERS_PTR TpmReg );

extern
EFI_STATUS
__stdcall TisReceiveResponse (
    IN TPM_1_2_REGISTERS_PTR TpmReg,
    OUT VOID                 *Buffer,
    OUT UINTN                *Size );

extern
EFI_STATUS
__stdcall IsTpmPresent (
    IN TPM_1_2_REGISTERS_PTR TpmReg );

extern
EFI_STATUS
__stdcall TpmLibPassThrough (
    IN TPM_1_2_REGISTERS_PTR   TpmReg,
    IN UINTN                   NoInputBuffers,
    IN TPM_TRANSMIT_BUFFER     *InputBuffers,
    IN UINTN                   NoOutputBuffers,
    IN OUT TPM_TRANSMIT_BUFFER *OutputBuffers );

extern
EFI_STATUS
__stdcall TpmLibStartup (
    IN UINT16 StartupType );

#endif
