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

   TcgDxe.c

   Abstract:

   DXE Driver that provides TCG services

   --*/
//*************************************************************************
// $Header: /Alaska/SOURCE/Modules/TCG2/Common/TcgDxe/TcgDxe.c 3     6/14/14 12:28a Fredericko $
//
// $Revision: 3 $
//
// $Date: 6/14/14 12:28a $
//*************************************************************************
// Revision History
// ----------------
// $Log: /Alaska/SOURCE/Modules/TCG2/Common/TcgDxe/TcgDxe.c $
// 
// 3     6/14/14 12:28a Fredericko
// 
// 2     6/09/14 4:50p Fredericko
// Changes for SetVariable vulnerability during Runtime
// 
// 1     4/21/14 2:16p Fredericko
// 
// 4     3/17/14 3:19p Fredericko
// 
// 3     3/14/14 3:22p Fredericko
// 
// 2     3/11/14 6:37p Fredericko
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
// 37    10/30/12 11:18a Fredericko
// 
// 36    10/08/12 10:02a Fredericko
// [TAG]  		EIP90986
// [Category]  	Bug Fix
// [Severity]  	Minor
// [Symptom]  	System Hang
// [RootCause]  	We tried to measure an unexpected FV if FV_MAIN was not
// found. 
// [Solution]  	Verify we found FV_MAIN before trying to measure. 
// [Files]  		TcgDxe.c
// 
// 35    5/21/12 11:44a Fredericko
// Changes for x32 bit build for TCG
// 
// 34    5/18/12 6:06p Fredericko
// Type cast size to UINTN for x64 and x32 bit builds
// 
// 33    5/09/12 6:37p Fredericko
// Tcm changes. For Win Server 8 and reboot test failure.
// 
// 32    4/28/12 3:26p Fredericko
// If PPI request comes in and VGA and USB enumeration is disabled Ppi
// request cannot be dispalyed or executed. So Abort Fastboot when Ppi
// request comes in. 
// 
// 31    4/27/12 6:06p Fredericko
// Measurement of FWVol Changed.
// 
// 30    3/19/12 6:30p Fredericko
// [TAG]  		EIP82769
// [Category]  	Improvement
// [Description]  	Firmware updates disable the TPM when Firmware update
// is done
// Changes for Tcg Performance Metrics Improvement. 
// [Files]  		EIP82769: xTcgPei.c, TcgDxe.c, xTcgDxe,c
// Performance: Files Changed: Tcg.sdl, TcgMisc.h, TcgDxe.c, TcgCommon.c,
// TcgCommon.h, 
// AmiTcgPlatformPeiLib.c, AmiTcgPlatformDxe.c, TcgDxe.dxs
// 
// 29    2/03/12 5:17p Fredericko
// [TAG]  		EIP81665
// [Category]  	Improvement
// [Description]  	Support for MOR feature improvement
// [Files]  		Tcg.sdl, AmiTcgPlatformDxe.c, Tcgdxe.c, Tcglegacy.c
// 
// 28    11/14/11 1:31p Fredericko
// Changes for Tcgprotocol interface. Function is currently not used.
// 
// 27    8/26/11 1:07p Fredericko
// Fastboot Changes.
// 
// 26    8/09/11 6:16p Fredericko
// [TAG]  		EIP66465
// [Category]  	Improvement
// [Description]  	1. Added support to remove EFI_EV_ACTION from the TCG
// logs if customer wants. 
// [Files]  		1. Tcgdxe.c
// 2. Tcgpei.c
// 3. Tcg.sdl
// 
// 25    4/22/11 8:51p Fredericko
// Changes for build in x32 bit mode.
// 
// 24    4/04/11 1:58p Fredericko
// Removed #pragma optimization directives
// 
// 23    4/01/11 9:37a Fredericko
// Updated function Header
// 
// 22    3/29/11 1:12p Fredericko
// 
// 21    3/28/11 2:19p Fredericko
// [TAG]        EIP 54642
// [Category] Improvement
// [Description] 1. Checkin Files related to TCG function override 
// 2. Include TCM and TPM auto detection
// [Files] Affects all TCG files
// 
// 20    5/19/10 5:36p Fredericko
// Included File Header
// Included File Revision History 
// Updated AMI Function Headers
// Code Beautification
// EIP 37653
//
//*************************************************************************
//*************************************************************************
//<AMI_FHDR_START>
//
// Name:  TcgDxe.c
//
// Description: 
//  Abstracted functions for Tcg protocol are defined here
//
//<AMI_FHDR_END>
//*************************************************************************
#include "TcgCommon.h"
#include <sha.h>
#include <TcgMisc.h>
#include <Token.h>
#include <AmiDxeLib.h>
#include <Runtime.h>
#include <AmiPeiLib.h>
#include "protocol\TcgService\TcgTcmService.h"
#include "TcgPlatformSetupPolicy.h"
#include <AcpiSupport.h>
#include "TcgPc.h"
#include "protocol\TcgService\TcgService.h"
#include "protocol\TpmDevice\TpmDevice.h"

#if PI_SPECIFICATION_VERSION<0x00010000
#include <Protocol\FirmwareVolume.h>
#else
#include <Protocol\FirmwareVolume2.h>
#endif


EFI_GUID gEfiAmiDTcgLogHobGuid = EFI_TCG_LOG_HOB_GUID;

UINT8  GetHashPolicy();

#pragma pack (1)
typedef struct
{
    EFI_PHYSICAL_ADDRESS PostCodeAddress;
    #if x64_BUILD
    UINT64               PostCodeLength;
    #else
    UINTN                PostCodeLength;
    #endif
} EFI_TCG_EV_POST_CODE;

typedef struct
{
    EFI_TCG_PCR_EVENT_HEADER Header;
    EFI_TCG_EV_POST_CODE     Event;
} PEI_EFI_POST_CODE;

#pragma pack()


typedef struct _TCG_DXE_PRIVATE_DATA
{
    EFI_TCG_PROTOCOL        TcgServiceProtocol;
    EFI_TPM_DEVICE_PROTOCOL *TpmDevice;
} TCG_DXE_PRIVATE_DATA;


typedef struct _TCM_DXE_PRIVATE_DATA
{
    EFI_TCM_PROTOCOL        TcgServiceProtocol;
    EFI_TPM_DEVICE_PROTOCOL *TpmDevice;
} TCM_DXE_PRIVATE_DATA;



EFI_STATUS EFIAPI TcgDxeLogEvent (
    IN EFI_TCG_PROTOCOL *This,
    IN TCG_PCR_EVENT    *TCGLogData,
    IN OUT UINT32       *EventNumber,
    IN UINT32           Flags );

EFI_STATUS EFIAPI TcmDxeLogEvent(
    IN EFI_TCM_PROTOCOL *This,
    IN TCM_PCR_EVENT    *TCGLogData,
    IN OUT UINT32       *EventNumber,
    IN UINT32           Flags );

EFI_STATUS
__stdcall Tcg20CommonExtend(
    IN VOID         *CallbackContext,
    IN TPM_PCRINDEX PcrIndex,
    IN TCG_DIGEST   *Digest,
    OUT TCG_DIGEST  *NewPCRValue,
    IN  UINT8        DigestSize );

BOOLEAN IsTpm20Device();
UINTN FindNextLogLocation(TCG_PCR_EVENT_HDR   *TcgLog, UINTN EventNum);

EFI_GUID gEfiTcgCapHobGuid = EFI_TCG_CAP_HOB_GUID;
static UINTN    TcmBootVar = 0;
//**********************************************************************
//<AMI_PHDR_START>
//
// Procedure:   TcmBootDone
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
void TcmBootDone(
    IN EFI_EVENT efiev,
    IN VOID      *ctx )
{
    TcmBootVar = 1;
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
EFIAPI TcmOSTransition()
{
   EFI_EVENT  ReadToBootEvent;
   EFI_STATUS Status;

   #if defined(EFI_EVENT_SIGNAL_READY_TO_BOOT)\
        && EFI_SPECIFICATION_VERSION < 0x20000
       
         Status = pBS->CreateEvent( EFI_EVENT_SIGNAL_READY_TO_BOOT,
                                   EFI_TPL_CALLBACK,
                                   TcmBootDone, NULL, &ReadToBootEvent );
        
   #else
        Status = CreateReadyToBootEvent( EFI_TPL_CALLBACK,
                                         TcmBootDone,
                                         NULL,
                                         &ReadToBootEvent );
   #endif

   return Status;
}


#define _CR( Record, TYPE,\
       Field )((TYPE*) ((CHAR8*) (Record) - (CHAR8*) &(((TYPE*) 0)->Field)))

#define TCG_DXE_PRIVATE_DATA_FROM_THIS( This )  \
    _CR( This, TCG_DXE_PRIVATE_DATA, TcgServiceProtocol )

#define TCM_DXE_PRIVATE_DATA_FROM_THIS( This )  \
    _CR( This, TCM_DXE_PRIVATE_DATA, TcgServiceProtocol )


TCG_ACPI_TABLE                        mTcgAcpiTableTemplate = {
    {
        EFI_ACPI_3_0_TRUSTED_COMPUTING_PLATFORM_ALLIANCE_CAPABILITIES_TABLE_SIGNATURE,
        sizeof (TCG_ACPI_TABLE)
        //
        // Compiler initializes the remaining bytes to 0
        // These fields should be filled in in production
        //
    },
    0,
    TPM_LOG_AREA_MAX_LEN,
    (EFI_PHYSICAL_ADDRESS)( -1 )
};

static TPM_Capabilities_PermanentFlag TcgDxe_Cap;

EFI_STATUS
__stdcall TcgCommonPassThrough(
    IN VOID                    *Context,
    IN UINT32                  NoInputBuffers,
    IN TPM_TRANSMIT_BUFFER     *InputBuffers,
    IN UINT32                  NoOutputBuffers,
    IN OUT TPM_TRANSMIT_BUFFER *OutputBuffers )
{
    TCG_DXE_PRIVATE_DATA *Private;
    EFI_STATUS            Status;

    Private = TCG_DXE_PRIVATE_DATA_FROM_THIS( Context );

    Status = Private->TpmDevice->Init( Private->TpmDevice );

    TRACE(( TRACE_ALWAYS,"TcgDxePassThroughToTpm Init Status = %r \n", Status));

    Status=  Private->TpmDevice->Transmit(
               Private->TpmDevice,
               NoInputBuffers,
               InputBuffers,
               NoOutputBuffers,
               OutputBuffers
               );

    TRACE(( TRACE_ALWAYS,"TcgDxePassThroughToTpm Transmit Status = %r \n", Status));
    
    Private->TpmDevice->Close( Private->TpmDevice );

    return Status;

}


EFI_STATUS EFIAPI TcgDxePassThroughToTpm(
    IN EFI_TCG_PROTOCOL *This,
    IN UINT32           TpmInputParamterBlockSize,
    IN UINT8            *TpmInputParamterBlock,
    IN UINT32           TpmOutputParameterBlockSize,
    IN UINT8            *TpmOutputParameterBlock )
{
    TPM_TRANSMIT_BUFFER InBuffer[1], OutBuffer[1];
    EFI_STATUS Status;
    TCG_DXE_PRIVATE_DATA              *Private;

    //some applications might not set init command before making this call.
    //Just set init commands[locality zero for them]
    Private = TCG_DXE_PRIVATE_DATA_FROM_THIS( This );
    Status = Private->TpmDevice->Init( Private->TpmDevice );

    TRACE(( TRACE_ALWAYS,"TcgDxePassThroughToTpm Init Status = %r \n", Status));
 
    InBuffer[0].Buffer  = TpmInputParamterBlock;
    InBuffer[0].Size    = TpmInputParamterBlockSize;
    OutBuffer[0].Buffer = TpmOutputParameterBlock;
    OutBuffer[0].Size   = TpmOutputParameterBlockSize;

    Status=  Private->TpmDevice->Transmit(
               Private->TpmDevice,
                sizeof (InBuffer) / sizeof (*InBuffer),
                InBuffer,
                sizeof (OutBuffer) / sizeof (*OutBuffer),
                OutBuffer);

    TRACE(( TRACE_ALWAYS,"TcgDxePassThroughToTpm Transmit Status = %r \n", Status));

    Private->TpmDevice->Close( Private->TpmDevice );

    TRACE(( TRACE_ALWAYS,"TcgDxePassThroughToTpm Close Status = %r \n", Status));

    return EFI_SUCCESS;
}


EFI_STATUS
__stdcall TcgDxeCommonExtend(
    IN VOID         *CallbackContext,
    IN TPM_PCRINDEX PCRIndex,
    IN TCG_DIGEST   *Digest,
    OUT TCG_DIGEST  *NewPCRValue )
{
    TPM_1_2_CMD_HEADER  cmdHeader;
    TPM_1_2_RET_HEADER  retHeader;
    TPM_TRANSMIT_BUFFER InBuffer[3], OutBuffer[2];  
    BOOLEAN             Sha2 = TRUE;

    if(IsTpm20Device()){
        TRACE(( TRACE_ALWAYS,"Tpm20 Extend Status \n"));
       
        if(GetHashPolicy()==0){
            return(Tcg20CommonExtend(NULL, PCRIndex, Digest, NewPCRValue, 20));
        }else{
            return(Tcg20CommonExtend((VOID *)&Sha2, PCRIndex, Digest, NewPCRValue,32));
        }
    }

    TRACE(( TRACE_ALWAYS,"Tpm1_2 Extend Status \n"));
    InBuffer[0].Buffer = &cmdHeader;
    InBuffer[0].Size   = sizeof (cmdHeader);
    InBuffer[1].Buffer = &PCRIndex;
    InBuffer[1].Size   = sizeof (PCRIndex);
    InBuffer[2].Buffer = Digest->digest;
    InBuffer[2].Size   = sizeof (Digest->digest);

    OutBuffer[0].Buffer = &retHeader;
    OutBuffer[0].Size   = sizeof (retHeader);
    OutBuffer[1].Buffer = NewPCRValue->digest;
    OutBuffer[1].Size   = sizeof (NewPCRValue->digest);

    cmdHeader.Tag       = TPM_H2NS( TPM_TAG_RQU_COMMAND );
    cmdHeader.ParamSize = TPM_H2NL(sizeof (cmdHeader) 
                          + sizeof (PCRIndex) + sizeof (Digest->digest));

    cmdHeader.Ordinal = TPM_H2NL( TPM_ORD_Extend );
    PCRIndex          = TcgCommonH2NL( PCRIndex );

    return TcgCommonPassThrough( CallbackContext,
                                 sizeof (InBuffer) / sizeof (*InBuffer),
                                 InBuffer,
                                 sizeof (OutBuffer) / sizeof (*OutBuffer),
                                 OutBuffer);
}


//**********************************************************************
//<AMI_PHDR_START>
//
// Procedure:   TcmCommonPassThrough
//
// Description: Helper function for TCM transmit command
//
// Input:       VOID *Context
//              UINT32 NoInputBuffers
//              TPM_TRANSMIT_BUFFER InputBuffers
//              UINT32 NoOutputBuffers
//              TPM_TRANSMIT_BUFFER OutputBuffers
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
EFI_STATUS
__stdcall TcmCommonPassThrough(
    IN VOID                    *Context,
    IN UINT32                  NoInputBuffers,
    IN TPM_TRANSMIT_BUFFER     *InputBuffers,
    IN UINT32                  NoOutputBuffers,
    IN OUT TPM_TRANSMIT_BUFFER *OutputBuffers )
{
    TCM_DXE_PRIVATE_DATA *Private;

    Private = TCM_DXE_PRIVATE_DATA_FROM_THIS( Context );
    return Private->TpmDevice->Transmit(
               Private->TpmDevice,
               NoInputBuffers,
               InputBuffers,
               NoOutputBuffers,
               OutputBuffers
               );
}


EFI_STATUS EFIAPI TcgDxeStatusCheck(
    IN EFI_TCG_PROTOCOL                 *This,
    OUT TCG_EFI_BOOT_SERVICE_CAPABILITY *ProtocolCapability,
    OUT UINT32                          *TCGFeatureFlags,
    OUT EFI_PHYSICAL_ADDRESS            *EventLogLocation,
    OUT EFI_PHYSICAL_ADDRESS            *LastEvent )
{
    TCG_LOG_HOB   *TcgLog;
    TCG_PCR_EVENT *EventStart;
    UINTN         Index;

    if ( ProtocolCapability != NULL )
    {
        pBS->SetMem( ProtocolCapability, sizeof (*ProtocolCapability), 0 );
        ProtocolCapability->Size = sizeof (TCG_EFI_BOOT_SERVICE_CAPABILITY);
        ProtocolCapability->StructureVersion.Major = TCG_SPEC_VERSION_MAJOR;
        ProtocolCapability->StructureVersion.Minor = TCG_SPEC_VERSION_MINOR;
        ProtocolCapability->StructureVersion.RevMajor = 0;
        ProtocolCapability->StructureVersion.RevMinor = 0;
        ProtocolCapability->ProtocolSpecVersion.Major = TCG_SPEC_VERSION_MAJOR;
        ProtocolCapability->ProtocolSpecVersion.Minor = TCG_SPEC_VERSION_MINOR;
        ProtocolCapability->ProtocolSpecVersion.RevMajor = 0;
        ProtocolCapability->ProtocolSpecVersion.RevMinor = 0;
        ProtocolCapability->HashAlgorithmBitmap          = 1;    // SHA-1
        ProtocolCapability->TPMPresentFlag               = 1;   // TPM is present.
        ProtocolCapability->TPMDeactivatedFlag    = TcgDxe_Cap.deactivated;
    }

    if ( TCGFeatureFlags != NULL )
    {
        *TCGFeatureFlags = 0;
    }

    EventStart = (TCG_PCR_EVENT*)(UINTN)mTcgAcpiTableTemplate.LogStart;
    TcgLog     = (TCG_LOG_HOB*)EventStart;
    TcgLog--;


    if ( EventLogLocation != NULL )
    {
        *EventLogLocation
            = (EFI_PHYSICAL_ADDRESS)( UINTN ) mTcgAcpiTableTemplate.LogStart;
    }

    if ( LastEvent != NULL )
    {
        if ( TcgLog->EventNum == 0 )
        {
            *LastEvent = 0;
        }
        else {
            Index = TcgLog->EventNum;
            *LastEvent = (EFI_PHYSICAL_ADDRESS)( UINTN )FindNextLogLocation((TCG_PCR_EVENT_HDR *)mTcgAcpiTableTemplate.LogStart,
                            (TcgLog->EventNum - 1));
        }
    }

    return EFI_SUCCESS;
}



//**********************************************************************
//<AMI_PHDR_START>
//
// Procedure:   TcgTcmDxeStatusCheck
//
// Description: Tcm Dxe status check function
//
// Input:       IN EFI_TCM_PROTOCOL                 *This,
//              OUT TCM_EFI_BOOT_SERVICE_CAPABILITY *ProtocolCapability,
//              OUT UINT32                          *TCGFeatureFlags,
//              OUT EFI_PHYSICAL_ADDRESS            *EventLogLocation,
//              OUT EFI_PHYSICAL_ADDRESS            *LastEvent
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
EFI_STATUS EFIAPI TcgTcmDxeStatusCheck(
    IN EFI_TCM_PROTOCOL                 *This,
    OUT TCM_EFI_BOOT_SERVICE_CAPABILITY *ProtocolCapability,
    OUT UINT32                          *TCGFeatureFlags,
    OUT EFI_PHYSICAL_ADDRESS            *EventLogLocation,
    OUT EFI_PHYSICAL_ADDRESS            *LastEvent )
{
    TCG_LOG_HOB   *TcgLog;
    TCM_PCR_EVENT *EventStart;
    UINTN         Index;

    if((AutoSupportType()) && (TcmBootVar == 1)){
        pBS->SetMem( ProtocolCapability, sizeof (TCM_EFI_BOOT_SERVICE_CAPABILITY), 0 );
        if ( TCGFeatureFlags != NULL )*TCGFeatureFlags = 0;
        if ( LastEvent != NULL )*LastEvent = 0;
        return EFI_UNSUPPORTED;
    }

    if ( ProtocolCapability != NULL )
    {
        pBS->SetMem( ProtocolCapability, sizeof (*ProtocolCapability), 0 );
        ProtocolCapability->Size = sizeof (TCG_EFI_BOOT_SERVICE_CAPABILITY);
        ProtocolCapability->StructureVersion.Major = TCG_SPEC_VERSION_MAJOR;
        ProtocolCapability->StructureVersion.Minor = TCG_SPEC_VERSION_MINOR;
        ProtocolCapability->StructureVersion.RevMajor = 0;
        ProtocolCapability->StructureVersion.RevMinor = 0;
        ProtocolCapability->ProtocolSpecVersion.Major = TCG_SPEC_VERSION_MAJOR;
        ProtocolCapability->ProtocolSpecVersion.Minor = TCG_SPEC_VERSION_MINOR;
        ProtocolCapability->ProtocolSpecVersion.RevMajor = 0;
        ProtocolCapability->ProtocolSpecVersion.RevMinor = 0;
        ProtocolCapability->HashAlgorithmBitmap          = 1;    // SHA-1
        ProtocolCapability->TPMPresentFlag               = 1;   // TPM is present.
        ProtocolCapability->TPMDeactivatedFlag    = TcgDxe_Cap.deactivated;
    }

    if ( TCGFeatureFlags != NULL )
    {
        *TCGFeatureFlags = 0;
    }

    EventStart = (TCM_PCR_EVENT*)(UINTN)mTcgAcpiTableTemplate.LogStart;
    TcgLog     = (TCG_LOG_HOB*)EventStart;
    TcgLog--;

    if ( EventLogLocation != NULL )
    {
        *EventLogLocation
            = (EFI_PHYSICAL_ADDRESS)( UINTN ) mTcgAcpiTableTemplate.LogStart;
    }

    if ( LastEvent != NULL )
    {
        if ( TcgLog->EventNum == 0 )
        {
            *LastEvent = 0;
        }
        else {
            Index = TcgLog->EventNum;

            do
            {
                *LastEvent = (EFI_PHYSICAL_ADDRESS)( UINTN ) EventStart;
                EventStart = (TCM_PCR_EVENT*)(UINTN)(
                    *LastEvent
                    + _TPM_STRUCT_PARTIAL_SIZE( TCM_PCR_EVENT, Event[  0] )
                    + EventStart->EventSize
                    );
            } while ( --Index > 0 );
        }
    }

    return EFI_SUCCESS;
}






EFI_STATUS EFIAPI TcgDxeHashAll(
    IN EFI_TCG_PROTOCOL *This,
    IN UINT8            *HashData,
    IN UINT64           HashDataLen,
    IN TCG_ALGORITHM_ID AlgorithmId,
    IN OUT UINT64       *HashedDataLen,
    IN OUT UINT8        **HashedDataResult )
{
    if ( AlgorithmId != TCG_ALG_SHA )
    {
        return EFI_UNSUPPORTED;
    }

    if ( *HashedDataResult == NULL || *HashedDataLen == 0 )
    {
        *HashedDataLen = sizeof (TCG_DIGEST);
        pBS->AllocatePool( EfiBootServicesData,
                           (UINTN)*HashedDataLen,
                           HashedDataResult );

        if ( *HashedDataResult == NULL )
        {
            return EFI_OUT_OF_RESOURCES;
        }
    }

    return SHA1HashAll(
                    This,
                    (VOID*)(UINTN)HashData,
                    (UINTN)HashDataLen,
                    (TCG_DIGEST*)*HashedDataResult);
}




//**********************************************************************
//<AMI_PHDR_START>
//
// Procedure:  TcmDxeHashAll 
//
// Description: TcmDxeHashAll function [SHA1]
//
// Input:           IN EFI_TCG_PROTOCOL *This,
//                  IN UINT8            *HashData,
//                  IN UINT64           HashDataLen,
//                  IN TCG_ALGORITHM_ID AlgorithmId,
//                  IN OUT UINT64       *HashedDataLen,
//                  IN OUT UINT8        **HashedDataResult
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
EFI_STATUS EFIAPI TcmDxeHashAll(
    IN EFI_TCM_PROTOCOL *This,
    IN UINT8            *HashData,
    IN UINT64           HashDataLen,
    IN TCG_ALGORITHM_ID AlgorithmId,
    IN OUT UINT64       *HashedDataLen,
    IN OUT UINT8        **HashedDataResult )
{

    if((AutoSupportType()) && (TcmBootVar == 1)){
         return EFI_UNSUPPORTED;
    }

    if ( AlgorithmId != TCG_ALG_SHA )
    {
        return EFI_UNSUPPORTED;
    }

    if ( *HashedDataResult == NULL || *HashedDataLen == 0 )
    {
        *HashedDataLen = sizeof (TCG_DIGEST);
        pBS->AllocatePool( EfiBootServicesData,
                           (UINTN)*HashedDataLen,
                           HashedDataResult );

        if ( *HashedDataResult == NULL )
        {
            return EFI_OUT_OF_RESOURCES;
        }
    }

    return SHA1HashAll(
                    This,
                    (VOID*)(UINTN)HashData,
                    (UINTN)HashDataLen,
                    (TCG_DIGEST*)*HashedDataResult);
}


//**********************************************************************
//<AMI_PHDR_START>
//
// Name:  TcgDxeHashLogExtendEventTpm
//
// Description: TcgDxe common function to Hash, Log and Extend data using TPM
//
// Input:       *This
//              *HashData
//              HashDataLen
//              AlgorithmId,
//              *TCGLogData,
//              *EventNum,
//              *EventLogLastEntry
//
// Output:     EFI STATUS
//
// Modified:
//
// Referrals:  TcgCommonSha1Start, TcgCommonSha1Start, TcgCommonSha1CompleteExtend
//
// Notes:
//<AMI_PHDR_END>
//**********************************************************************
EFI_STATUS
EFIAPI TcgDxeHashLogExtendEventTpm(
    IN EFI_TCG_PROTOCOL      *This,
    IN EFI_PHYSICAL_ADDRESS  HashData,
    IN UINT64                HashDataLen,
    IN TCG_ALGORITHM_ID      AlgorithmId,
    IN OUT TCG_PCR_EVENT     *TCGLogData,
    IN OUT UINT32            *EventNum,
    OUT EFI_PHYSICAL_ADDRESS *EventLogLastEntry )
{
    EFI_STATUS           Status;
    UINT32               Sha1MaxBytes;
    TCG_DIGEST           NewPCRValue;
    TCG_DXE_PRIVATE_DATA *Private;

#if defined LOG_EV_EFI_ACTION && LOG_EV_EFI_ACTION == 0
    if(TCGLogData->EventType == EV_EFI_ACTION)
    {
        return EFI_SUCCESS;
    }
#endif

    Private = TCG_DXE_PRIVATE_DATA_FROM_THIS( This );

    Status = Private->TpmDevice->Init( Private->TpmDevice );

    if ( EFI_ERROR( Status ))
    {
        TRACE(( TRACE_ALWAYS,"Private->TpmDevice Status = %r \n", Status));
        goto Exit;
    }

    Status = TcgCommonSha1Start( This, TCG_ALG_SHA, &Sha1MaxBytes );

    if ( EFI_ERROR( Status ))
    {
        TRACE(( TRACE_ALWAYS,"TcgCommonSha1Start Status = %r \n", Status));
        goto Exit;
    }

    Status = TcgCommonSha1Update(
        This,
        (UINT8 *)HashData,
        (UINT32)HashDataLen,
        Sha1MaxBytes
        );

    if ( EFI_ERROR( Status ))
    {
        TRACE(( TRACE_ALWAYS,"TcgCommonSha1Update Status = %r \n", Status));
        goto Exit;
    }

#if defined(TCG_DEBUG_MODE) && (TCG_DEBUG_MODE == 1)
    HashData    += (UINTN)(HashDataLen & ~63);
    HashDataLen &= 63;
#else
    HashData    += (HashDataLen & ~63);
    HashDataLen &= 63;
#endif

    Status = TcgCommonSha1CompleteExtend(
        This,
        (UINT8 *)HashData,
        (UINT32)HashDataLen,
        TCGLogData->PCRIndex,
        &TCGLogData->Digest,
        &NewPCRValue
        );

    if ( EFI_ERROR( Status ))
    {
        TRACE(( TRACE_ALWAYS,"TcgCommonSha1CompleteExtend Status = %r \n", Status));
        goto Exit;
    }

    Status = TcgDxeLogEvent( This, TCGLogData, EventNum, 1 );
    TRACE(( TRACE_ALWAYS,"TcgDxeLogEvent Status = %r \n", Status));    

Exit:
    Private->TpmDevice->Close( Private->TpmDevice );
    return Status;
}




//**********************************************************************
//<AMI_PHDR_START>
//
// Name:  TcgDxeHashLogExtendEventTcm
//
// Description: TcgDxe common function to Hash, Log and Extend data using TPM
//
// Input:       *This
//              *HashData
//              HashDataLen
//              AlgorithmId,
//              *TCGLogData,
//              *EventNum,
//              *EventLogLastEntry
//
// Output:     EFI STATUS
//
// Modified:
//
// Referrals:  TcgCommonSha1Start, TcgCommonSha1Start, TcgCommonSha1CompleteExtend
//
// Notes:
//<AMI_PHDR_END>
//**********************************************************************
EFI_STATUS
EFIAPI TcgDxeHashLogExtendEventTcm(
    IN EFI_TCM_PROTOCOL      *This,
    IN EFI_PHYSICAL_ADDRESS  HashData,
    IN UINT64                HashDataLen,
    IN TCG_ALGORITHM_ID      AlgorithmId,
    IN OUT TCM_PCR_EVENT     *TCGLogData,
    IN OUT UINT32            *EventNum,
    OUT EFI_PHYSICAL_ADDRESS *EventLogLastEntry )
{
    EFI_STATUS           Status;
    UINT32               Sha1MaxBytes;
    TCM_DIGEST           NewPCRValue;
    TCM_DXE_PRIVATE_DATA *Private;

    Private = TCM_DXE_PRIVATE_DATA_FROM_THIS( This );

    if((AutoSupportType()) && (TcmBootVar == 1)){
        return EFI_UNSUPPORTED;
    }

    Status = TcgCommonSha1Start( This, TCG_ALG_SHA, &Sha1MaxBytes );

    if ( EFI_ERROR( Status ))
    {
        goto Exit;
    }

    Status = TcgCommonSha1Update(
        This,
        (UINT8 *)HashData,
        (UINT32)HashDataLen,
        Sha1MaxBytes
        );

    if ( EFI_ERROR( Status ))
    {
        goto Exit;
    }

    HashData    += (HashDataLen & ~63);
    HashDataLen &= 63;

    Status = TcmCommonSha1CompleteExtend(
        This,
        (UINT8 *)HashData,
        (UINT32)HashDataLen,
        TCGLogData->PCRIndex,
        &TCGLogData->Digest,
        &NewPCRValue
        );

    if ( EFI_ERROR( Status ))
    {
        goto Exit;
    }

    Status = TcmDxeLogEvent( This, TCGLogData, EventNum, 1 );

Exit:
    return Status;
}

#pragma optimize("",off)

VOID
EFIAPI
PrintBuffer(IN UINT8 *Buffer, IN UINT32 BufferSize)
{
  UINT32 Index;

  TRACE(( TRACE_ALWAYS, "Buffer Address: 0x%08x, Size: 0x%08x, Value:\n", Buffer, BufferSize));
  for(Index = 0; Index < BufferSize; Index++){
    TRACE(( TRACE_ALWAYS, "%02x ", *(Buffer + Index)));
   if((Index+1) % 16 == 0) TRACE(( TRACE_ALWAYS, "\n"));
  }
  TRACE(( TRACE_ALWAYS, "\n"));
}


EFI_STATUS
__stdcall TcgDxeCommonLogEvent(
    IN VOID          *CallbackContext,
    IN TCG_PCR_EVENT *EvtLog,
    IN OUT UINT32    *TableSize,
    IN UINT32        MaxSize,
    IN TCG_PCR_EVENT *NewEntry, 
    IN UINT8         HashAlgorithm )
{
    UINT32    TempSize;

     //protect Tcglog from possible overflow log operation
    if(NewEntry->EventSize > ((UINT32)(~0) - sizeof(EFI_TCG_PCR_EVENT_HEADER))){
	    return EFI_OUT_OF_RESOURCES;
    }

    TempSize = sizeof(TCG_PCR_EVENT)-sizeof(NewEntry->Digest) - sizeof(UINT32)-1;

    TcgCommonCopyMem( CallbackContext, EvtLog, NewEntry, TempSize ); 

    PrintBuffer((UINT8 *)NewEntry, 0x50);

    TRACE(( TRACE_ALWAYS,"CopyMem 1 \n"));    

    if(HashAlgorithm == 0){  
        TcgCommonCopyMem( CallbackContext, (((UINT8 *)EvtLog) + TempSize), (UINT8 *)&NewEntry->Digest.digest, sizeof(NewEntry->Digest.digest) ); 
        TempSize+=sizeof(NewEntry->Digest.digest);
        TcgCommonCopyMem( CallbackContext, (((UINT8 *)EvtLog) + TempSize), (UINT8 *)&NewEntry->EventSize, sizeof(UINT32));
        TempSize+=sizeof(UINT32);
        TcgCommonCopyMem( CallbackContext, (((UINT8 *)EvtLog) + TempSize), NewEntry->Event, NewEntry->EventSize);
    }else{
        /*TcgCommonCopyMem( CallbackContext, (((UINT8 *)EvtLog) + TempSize), (UINT8 *)&NewEntry->Digest.digestSha2, sizeof(NewEntry->Digest.digestSha2) ); 
        TempSize+=sizeof(NewEntry->Digest.digestSha2);
        TcgCommonCopyMem( CallbackContext, (((UINT8 *)EvtLog) + TempSize), (UINT8 *)&NewEntry->EventSize, sizeof(UINT32));
        TempSize+=sizeof(UINT32);
        TcgCommonCopyMem( CallbackContext, (((UINT8 *)EvtLog) + TempSize), NewEntry->Event, NewEntry->EventSize);
        */
    }

    *TableSize += (TempSize + NewEntry->EventSize);
    return EFI_SUCCESS;
}
#pragma optimize("",on)





//**********************************************************************
//<AMI_PHDR_START>
//
// Procedure:  TcgDxeLogEvent
//
// Description: Logs TCG events in DXE
//
// Input:               IN EFI_TCG_PROTOCOL *This,
//                      IN TCG_PCR_EVENT    *TCGLogData,
//                      IN OUT UINT32       *EventNumber,
//                      IN UINT32           Flags
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
#pragma optimize("",off)
EFI_STATUS EFIAPI TcgDxeLogEvent(
    IN EFI_TCG_PROTOCOL *This,
    IN TCG_PCR_EVENT    *TCGLogData,
    IN OUT UINT32       *EventNumber,
    IN UINT32           Flags )
{
    EFI_STATUS           Status;
    TCG_LOG_HOB          *TcgLog;
    TCG_DXE_PRIVATE_DATA *Private;
    TCG_DIGEST           NewPCR;
    UINTN               NextLocation;
    UINT8               HashAlgo = GetHashPolicy();
    

    Private = TCG_DXE_PRIVATE_DATA_FROM_THIS( This );

#if defined LOG_EV_EFI_ACTION && LOG_EV_EFI_ACTION == 0
    if(TCGLogData->EventType == EV_EFI_ACTION)
    {
        return EFI_SUCCESS;
    }
#endif

    Status = EFI_SUCCESS;

    if ( !(Flags & (UINT32)(0x1)))
    {
        TRACE((TRACE_ALWAYS, "Flags = %x \n", Flags));
        Status = Private->TpmDevice->Init( Private->TpmDevice );

        TRACE((TRACE_ALWAYS, "Private->TpmDevice->Init = %r \n", Status));

        if ( !EFI_ERROR( Status ))
        {
           Status = TcgDxeCommonExtend(
            This,
            TCGLogData->PCRIndex,
            &TCGLogData->Digest,
            &NewPCR
            );
            
            TRACE((TRACE_ALWAYS, "TcgDxeCommonExtend Status = %r \n", Status));
        }
        Private->TpmDevice->Close( Private->TpmDevice );
    }

    if ( !TcgDxe_Cap.deactivated )
    {
        TcgLog = (TCG_LOG_HOB*)(UINTN)mTcgAcpiTableTemplate.LogStart;
        TcgLog--;

        if ( !EFI_ERROR( Status ))
        {
            NextLocation = FindNextLogLocation((TCG_PCR_EVENT_HDR*)(TcgLog + 1), TcgLog->EventNum);
            
            Status = TcgDxeCommonLogEvent(
                This,
                (TCG_PCR_EVENT*)(NextLocation),
                &TcgLog->TableSize,
                TcgLog->TableMaxSize,
                TCGLogData, HashAlgo);


            if ( !EFI_ERROR( Status ))
            {
                TcgLog->EventNum++;
                *EventNumber = TcgLog->EventNum;
            }
        }
    }
    return Status;
}
#pragma optimize("",on)




//**********************************************************************
//<AMI_PHDR_START>
//
// Procedure:  TcmDxeLogEvent
//
// Description: Logs TCM events in DXE
//
// Input:               IN EFI_TCG_PROTOCOL *This,
//                      IN TCG_PCR_EVENT    *TCGLogData,
//                      IN OUT UINT32       *EventNumber,
//                      IN UINT32           Flags
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
EFI_STATUS EFIAPI TcmDxeLogEvent(
    IN EFI_TCM_PROTOCOL *This,
    IN TCM_PCR_EVENT    *TCGLogData,
    IN OUT UINT32       *EventNumber,
    IN UINT32           Flags )
{
    EFI_STATUS           Status;
    TCG_LOG_HOB          *TcgLog;
    TCM_DXE_PRIVATE_DATA *Private;
    TCM_DIGEST           NewPCR;

    Private = TCM_DXE_PRIVATE_DATA_FROM_THIS( This );

    if((AutoSupportType()) && (TcmBootVar == 1)){
        return EFI_UNSUPPORTED;
    }

    Status = EFI_SUCCESS;

    if ( !(Flags & 1))
    {
        if ( !EFI_ERROR( Status ))
        {
            Status = TcmCommonExtend(
                This,
                TCGLogData->PCRIndex,
                &TCGLogData->Digest,
                &NewPCR);
        }
    }

    if ( !TcgDxe_Cap.deactivated )
    {
        TcgLog = (TCG_LOG_HOB*)(UINTN)mTcgAcpiTableTemplate.LogStart;
        TcgLog--;

        if ( !EFI_ERROR( Status ))
        {
            Status = TcmCommonLogEvent(
                This,
                (TCM_PCR_EVENT*)(TcgLog + 1),
                &TcgLog->TableSize,
                TcgLog->TableMaxSize,
                TCGLogData
                );

            if ( !EFI_ERROR( Status ))
            {
                TcgLog->EventNum++;
                *EventNumber = TcgLog->EventNum;
            }
        }
    }
    return Status;
}




//**********************************************************************
//<AMI_PHDR_START>
//
// Procedure:  TcgDxePassThroughToTcm
//
// Description: Helper function for TCM transmit function
//
// Input:               IN EFI_TCM_PROTOCOL *This,
//                      IN UINT32           TpmInputParamterBlockSize,
//                      IN UINT8            *TpmInputParamterBlock,
//                      IN UINT32           TpmOutputParameterBlockSize,
//                      IN UINT8            *TpmOutputParameterBlock
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
EFI_STATUS EFIAPI TcgDxePassThroughToTcm(
    IN EFI_TCM_PROTOCOL *This,
    IN UINT32           TpmInputParamterBlockSize,
    IN UINT8            *TpmInputParamterBlock,
    IN UINT32           TpmOutputParameterBlockSize,
    IN UINT8            *TpmOutputParameterBlock )
{
    TPM_TRANSMIT_BUFFER InBuffer[1], OutBuffer[1];
    EFI_STATUS Status;
    TCM_DXE_PRIVATE_DATA              *Private;

    //some applications might not set init command before making this call.
    //Just set init commands[locality zero for them]
    Private = TCM_DXE_PRIVATE_DATA_FROM_THIS( This );

    if((AutoSupportType()) && (TcmBootVar == 1)){
        return EFI_UNSUPPORTED;
    }

    InBuffer[0].Buffer  = TpmInputParamterBlock;
    InBuffer[0].Size    = TpmInputParamterBlockSize;
    OutBuffer[0].Buffer = TpmOutputParameterBlock;
    OutBuffer[0].Size   = TpmOutputParameterBlockSize;

    Status = TcmCommonPassThrough(
        This,
        sizeof (InBuffer) / sizeof (*InBuffer),
        InBuffer,
        sizeof (OutBuffer) / sizeof (*OutBuffer),
        OutBuffer
        );

    return EFI_SUCCESS;
}



EFI_STATUS EFIAPI TcgDxeHashLogExtendEvent(
    IN EFI_TCG_PROTOCOL      *This,
    IN EFI_PHYSICAL_ADDRESS  HashData,
    IN UINT64                HashDataLen,
    IN TCG_ALGORITHM_ID      AlgorithmId,
    IN OUT TCG_PCR_EVENT     *TCGLogData,
    IN OUT UINT32            *EventNumber,
    OUT EFI_PHYSICAL_ADDRESS *EventLogLastEntry )
{
    EFI_STATUS          Status;
    UINT64              DigestSize;
    UINT8               *HashResult;
    TCG_DXE_PRIVATE_DATA *Private;

    Private = TCG_DXE_PRIVATE_DATA_FROM_THIS( This );

#if defined LOG_EV_EFI_ACTION && LOG_EV_EFI_ACTION == 0
    if(TCGLogData->EventType == EV_EFI_ACTION)
    {
        return EFI_SUCCESS;
    }
#endif

    DigestSize = sizeof (TCGLogData->Digest);
    HashResult = TCGLogData->Digest.digest;
    Status     = TcgDxeHashAll(
        This,
        (UINT8 *)HashData,
        HashDataLen,
        AlgorithmId,
        &DigestSize,
        &HashResult
        );

    TRACE((TRACE_ALWAYS, "TcgDxeHashAll Status = %r \n", Status));


    if ( !EFI_ERROR( Status ))
    {
        Status = TcgDxeLogEvent(
            This,
            TCGLogData,
            EventNumber,
            0
            );

        TRACE((TRACE_ALWAYS, "TcgDxeLogEvent Status = %r \n", Status));
    }

    return Status;
}


static TCG_DXE_PRIVATE_DATA mTcgDxeData = {
    {
        TcgDxeStatusCheck,
        TcgDxeHashAll,
        TcgDxeLogEvent,
        TcgDxePassThroughToTpm,
        TcgDxeHashLogExtendEvent
    },
    NULL
};


static TCM_DXE_PRIVATE_DATA mTcmDxeData = {
    {
        TcgTcmDxeStatusCheck,
        TcmDxeHashAll,
        TcmDxeLogEvent,
        TcgDxePassThroughToTcm,
        TcgDxeHashLogExtendEventTcm       
    },
    NULL
};

//***********************************************************************
//                      MOR RELATED FUNCTIONS
//***********************************************************************

//**********************************************************************
//<AMI_PHDR_START>
//
// Procedure:   OverwriteSystemMemory
//
// Description: Overwrites system memory
//
// Input:      
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
EFI_STATUS OverwriteSystemMemory(
)
{

  EFI_STATUS                           Status;
  UINT8                                TmpMemoryMap[1];
  UINTN                                MapKey;
  UINTN                                DescriptorSize;
  UINT32                               DescriptorVersion;
  UINTN                                MemoryMapSize;
  EFI_MEMORY_DESCRIPTOR                *MemoryMap;
  EFI_MEMORY_DESCRIPTOR                *MemoryMapPtr;
  BOOLEAN                              IsRuntime;
  UINTN                                Index;
  UINT64                                Size;
  IsRuntime = FALSE;

  //
  // Get System MemoryMapSize
  //
  MemoryMapSize = 1;
  Status = pBS->GetMemoryMap (
                  &MemoryMapSize,
                  (EFI_MEMORY_DESCRIPTOR *)TmpMemoryMap,
                  &MapKey,
                  &DescriptorSize,
                  &DescriptorVersion
                  );
  ASSERT (Status == EFI_BUFFER_TOO_SMALL);
  //
  // Enlarge space here, because we will allocate pool now.
  //
  MemoryMapSize += EFI_PAGE_SIZE;
  Status = pBS->AllocatePool (
                  EfiBootServicesData,
                  MemoryMapSize,
                  (VOID**)&MemoryMap
                  );
  ASSERT_EFI_ERROR (Status);

  //
  // Get System MemoryMap
  //
  Status = pBS->GetMemoryMap (
                  &MemoryMapSize,
                  MemoryMap,
                  &MapKey,
                  &DescriptorSize,
                  &DescriptorVersion
                  );
  ASSERT_EFI_ERROR (Status);

  MemoryMapPtr = MemoryMap;
  //
  // Search the request Address
  //
  for (Index = 0; Index < (MemoryMapSize / DescriptorSize); Index++) {
      switch (MemoryMap->Type){
            case EfiMemoryMappedIO:
            case EfiReservedMemoryType:
            case EfiRuntimeServicesCode:
            case EfiRuntimeServicesData:
            case EfiUnusableMemory:
            case EfiMemoryMappedIOPortSpace:
            case EfiPalCode:
            case EfiACPIReclaimMemory:
            case EfiACPIMemoryNVS:
            case EfiBootServicesCode:
            case EfiBootServicesData:
            case EfiLoaderCode:
            case EfiLoaderData:
            case EfiMaxMemoryType:
                break;
            default: 
               Size = Shl64(MemoryMap->NumberOfPages, EFI_PAGE_SHIFT); 
               MemSet((VOID*)MemoryMap->PhysicalStart, (UINTN)Size, 0);
        }
    MemoryMap = (EFI_MEMORY_DESCRIPTOR *)((UINTN)MemoryMap + DescriptorSize);
  }

  //
  // Done
  //
  pBS->FreePool (MemoryMapPtr);

  return IsRuntime;



}

//**********************************************************************
//<AMI_PHDR_START>
//
// Procedure:   ReadMORValue
//
// Description: Reads TCG MOR variable
//
// Input:       IN  EFI_PEI_SERVICES  **PeiServices,
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
VOID ReadMORValue( )
{
    CHAR16     UefiMor[]   = L"MemoryOverwriteRequestControl";
    EFI_GUID   MorUefiGuid = MEMORY_ONLY_RESET_CONTROL_GUID;
    UINT8      mor         = 0;
    UINTN      size        = sizeof(mor);
    EFI_STATUS Status;

   
    Status = pRS->GetVariable( UefiMor, &MorUefiGuid,
                               NULL, &size, &mor );

    if(EFI_ERROR(Status))return;

    if ( mor & 1 )
    {

        //clear memory
        TRACE((-1,"MOR: before Clear memory"));
        Status = OverwriteSystemMemory();
        TRACE((-1,"MOR: After Clear memory"));
	}	
}




//**********************************************************************
//                      MOR FUNCTIONS END
//**********************************************************************
//**********************************************************************
//<AMI_PHDR_START>
//
// Name: OnAcpiInstalled
//
// Description: Adds Tcg Table to Acpi Tables
//
// Input:       IN      EFI_EVENT ev
//              IN      Callback Context *ctx
//
// Output:      Device path size
//
// Modified:
//
// Referrals:
//
// Notes:
//<AMI_PHDR_END>
//**********************************************************************
EFI_STATUS OnAcpiInstalled(
    IN EFI_EVENT ev,
    IN VOID      *ctx )
{
    EFI_STATUS                Status;
    EFI_ACPI_SUPPORT_PROTOCOL *acpi;
    UINTN                     handle = 0;

    TRACE((TRACE_ALWAYS, "Adding TCG ACPI table...\n"));
    Status = pBS->LocateProtocol( &gEfiAcpiSupportGuid, NULL, &acpi );

    if ( EFI_ERROR( Status ))
    {
        return EFI_ABORTED;
    }

    mTcgAcpiTableTemplate.Header.Revision = TCG_TBL_REV;
    MemCpy( mTcgAcpiTableTemplate.Header.OemId,
            TCG_OEMID,
            sizeof(mTcgAcpiTableTemplate.Header.OemId));

    mTcgAcpiTableTemplate.Header.OemTableId      = TCG_TBL_OEM_ID;
    mTcgAcpiTableTemplate.Header.OemRevision     = TCG_TBL_OEM_REV;
    mTcgAcpiTableTemplate.Header.CreatorId       = TCG_CREATOR_ID;
    mTcgAcpiTableTemplate.Header.CreatorRevision = TCG_CREATOR_REVISION;
    mTcgAcpiTableTemplate.Reserved               = TCG_PLATFORM_CLASS;

    Status = acpi->SetAcpiTable( acpi, &mTcgAcpiTableTemplate, TRUE,
                                 EFI_ACPI_TABLE_VERSION_ALL,
                                 &handle );
    return Status;
}





EFI_STATUS
EFIAPI SetTcgAcpiTable()
{
   EFI_STATUS                Status;
   EFI_ACPI_SUPPORT_PROTOCOL *acpi;
   EFI_EVENT                 ev;
   UINTN                     handle = 0;
   static    VOID            *reg = NULL;

   TRACE((TRACE_ALWAYS, "SetTcgAcpiTable....\n"));
   Status = pBS->LocateProtocol( &gEfiAcpiSupportGuid, NULL, &acpi );

   if(EFI_ERROR(Status)){
    
      Status = pBS->CreateEvent( EFI_EVENT_NOTIFY_SIGNAL,
                                   EFI_TPL_DRIVER,
                                   OnAcpiInstalled,
                                   NULL,
                                   &ev );

      ASSERT( !EFI_ERROR( Status ));
      Status = pBS->RegisterProtocolNotify( &gEfiAcpiSupportGuid, ev, &reg );
      return Status;
   }

   mTcgAcpiTableTemplate.Header.Revision = TCG_TBL_REV;
   MemCpy( mTcgAcpiTableTemplate.Header.OemId,TCG_OEMID,
           sizeof(mTcgAcpiTableTemplate.Header.OemId));

    mTcgAcpiTableTemplate.Header.OemTableId      = TCG_TBL_OEM_ID;
    mTcgAcpiTableTemplate.Header.OemRevision     = TCG_TBL_OEM_REV;
    mTcgAcpiTableTemplate.Header.CreatorId       = TCG_CREATOR_ID;
    mTcgAcpiTableTemplate.Header.CreatorRevision = TCG_CREATOR_REVISION;
    mTcgAcpiTableTemplate.Reserved               = TCG_PLATFORM_CLASS;

    Status = acpi->SetAcpiTable( acpi, &mTcgAcpiTableTemplate, TRUE,
                                 EFI_ACPI_TABLE_VERSION_ALL,
                                 &handle );

    return Status;
}


static EFI_STATUS CopyLogToAcpiNVS(
    void )
{
    EFI_STATUS Status;
    TCG_LOG_HOB                       *TcgLog = NULL;
    void**                                 DummyPtr;

    TcgLog = (TCG_LOG_HOB*)                   LocateATcgHob(
        pST->NumberOfTableEntries,
        pST->ConfigurationTable,
        &gEfiAmiDTcgLogHobGuid );

    DummyPtr = &TcgLog;

    if ( *DummyPtr == NULL )
    {
        return EFI_NOT_FOUND;
    }

    Status = pBS->AllocatePages(
        AllocateMaxAddress,
        EfiACPIMemoryNVS,
        EFI_SIZE_TO_PAGES( mTcgAcpiTableTemplate.LogMaxLength + sizeof (*TcgLog)),
        (UINT64*)(UINTN)&mTcgAcpiTableTemplate.LogStart
        );

    if ( EFI_ERROR( Status ))
    {
        return Status;
    }

    pBS->SetMem(
        (VOID*)((UINTN)mTcgAcpiTableTemplate.LogStart),
        (UINTN)mTcgAcpiTableTemplate.LogMaxLength,
        0x00 // Clean up this region with this value.
        );

    TcgLog->TableMaxSize = mTcgAcpiTableTemplate.LogMaxLength;
    
    if(TcgDxe_Cap.deactivated){
            TcgLog->EventNum = 0;
            TcgLog->TableSize = 0;

            pBS->CopyMem(
            (VOID*)(UINTN)mTcgAcpiTableTemplate.LogStart,
            TcgLog,
            sizeof (TCG_LOG_HOB));

        mTcgAcpiTableTemplate.LogStart += sizeof (*TcgLog);
    }else{
       pBS->CopyMem(
        (VOID*)(UINTN)mTcgAcpiTableTemplate.LogStart,
        TcgLog,
        TcgLog->TableSize + sizeof (*TcgLog)
        );
        mTcgAcpiTableTemplate.LogStart += sizeof (*TcgLog);
    }

    Status = SetTcgAcpiTable();

    return Status;
}

VOID InsertTailList(
    EFI_LIST_ENTRY *ListHead,
    EFI_LIST_ENTRY *Entry )
{
    EFI_LIST_ENTRY *_ListHead;
    EFI_LIST_ENTRY *_BackLink;

    _ListHead              = ListHead;
    _BackLink              = _ListHead->BackLink;
    Entry->ForwardLink     = _ListHead;
    Entry->BackLink        = _BackLink;
    _BackLink->ForwardLink = Entry;
    _ListHead->BackLink    = Entry;
}

typedef struct _TCG_DXE_FWVOL_LIST
{
    EFI_LIST_ENTRY Link;
    EFI_HANDLE FvHandle;
} TCG_DXE_FWVOL_LIST;

static EFI_LIST_ENTRY mMeasuredFvs = {
    &mMeasuredFvs,
    &mMeasuredFvs
};

static EFI_STATUS AddFvToMeasuredFvList(
    EFI_HANDLE FvHandle )
{
    TCG_DXE_FWVOL_LIST                *NewEntry;

    pBS->AllocatePool( EfiBootServicesData, sizeof (*NewEntry), &NewEntry );

    if ( NewEntry == NULL )
    {
        return EFI_OUT_OF_RESOURCES;
    }

    NewEntry->FvHandle = FvHandle;
    InsertTailList( &mMeasuredFvs, &NewEntry->Link );
    return EFI_SUCCESS;
}

static EFI_STATUS HashAllFilesInFv(
    IN SHA1_CTX        *Sha1Ctx,
    IN EFI_FIRMWARE_VOLUME_PROTOCOL
                       *FwVol,
    IN EFI_FV_FILETYPE FileType )
{
    EFI_STATUS Status;
    VOID                              *KeyBuffer = NULL;
    EFI_GUID FileName;
    EFI_FV_FILE_ATTRIBUTES FileAttr;
    UINTN FileSize;
    VOID                              *FileBuffer;
    UINT32 AuthStat;


    Status = pBS->AllocatePool( EfiBootServicesData, FwVol->KeySize, KeyBuffer );

    if ( KeyBuffer != NULL )
    {
        pBS->SetMem( KeyBuffer, FwVol->KeySize, 0 );
    }

    if ( KeyBuffer == NULL )
    {
        return EFI_OUT_OF_RESOURCES;
    }

    do
    {
        Status = FwVol->GetNextFile(
            FwVol,
            KeyBuffer,
            &FileType,
            &FileName,
            &FileAttr,
            &FileSize
            );

        if ( !EFI_ERROR( Status ))
        {
            FileBuffer = NULL;
            Status     = FwVol->ReadFile(
                FwVol,
                &FileName,
                &FileBuffer,
                &FileSize,
                &FileType,
                &FileAttr,
                &AuthStat
                );
            ASSERT( !EFI_ERROR( Status ));

            SHA1Update(Sha1Ctx, FileBuffer, (u32)FileSize );
            pBS->FreePool( FileBuffer );
        }
    } while ( !EFI_ERROR( Status ));

    pBS->FreePool( KeyBuffer );
    return EFI_SUCCESS;
}



static EFI_STATUS MeasureFv(
    IN EFI_TCG_PROTOCOL *This,
    IN EFI_HANDLE       FvHandle )
{
    EFI_STATUS Status;
    EFI_FIRMWARE_VOLUME_PROTOCOL      *FwVol;
    EFI_LIST_ENTRY                    *Link;
    TCG_DXE_FWVOL_LIST                *FwVolList;
    SHA1_CTX Sha1Ctx;
    TCG_DIGEST                        *FvDigest;
    EFI_TCG_PCR_EVENT TcgEvent;
    UINT32 EventNum;

    for ( Link = mMeasuredFvs.ForwardLink;
          Link != &mMeasuredFvs;
          Link = Link->ForwardLink )
    {
        FwVolList = _CR( Link, TCG_DXE_FWVOL_LIST, Link );

        if ( FvHandle == FwVolList->FvHandle )
        {
            return EFI_SUCCESS;
        }
    }

    Status = AddFvToMeasuredFvList( FvHandle );

    if ( EFI_ERROR( Status ))
    {
        return Status;
    }

    Status = pBS->HandleProtocol(
        FvHandle,
        &gEfiFirmwareVolumeProtocolGuid,
        &FwVol
        );
    ASSERT( !EFI_ERROR( Status ));

    SHA1Init(&Sha1Ctx );
    Status = HashAllFilesInFv( &Sha1Ctx, FwVol, EFI_FV_FILETYPE_DRIVER );

    if ( EFI_ERROR( Status ))
    {
        goto Exit;
    }
    Status = HashAllFilesInFv( &Sha1Ctx, FwVol, EFI_FV_FILETYPE_APPLICATION );

    if ( EFI_ERROR( Status ))
    {
        goto Exit;
    }
    SHA1Final((unsigned char *)&FvDigest->digest, &Sha1Ctx);

    TcgEvent.Header.PCRIndex      = PCRi_OPROM_CODE;
    TcgEvent.Header.EventType     = EV_EVENT_TAG;
    TcgEvent.Event.Tagged.EventID = EV_ID_OPROM_EXECUTE;
    TcgEvent.Event.Tagged.EventSize
        = sizeof (TcgEvent.Event.Tagged.EventData.OptionRomExecute);
    TcgEvent.Header.EventDataSize
        = _TPM_STRUCT_PARTIAL_SIZE( struct _EFI_TCG_EV_TAG, EventData )
        + TcgEvent.Event.Tagged.EventSize;

    TcgEvent.Event.Tagged.EventData.OptionRomExecute.PFA      = 0;
    TcgEvent.Event.Tagged.EventData.OptionRomExecute.Reserved = 0;
    TcgEvent.Event.Tagged.EventData.OptionRomExecute.Hash     = *FvDigest;

    Status = TcgDxeHashLogExtendEvent(
        This,
        (UINTN)&TcgEvent.Event,
        TcgEvent.Header.EventDataSize,
        TCG_ALG_SHA,
        (TCG_PCR_EVENT*)&TcgEvent,
        &EventNum,
        0
        );

Exit:
    return Status;
}




static
VOID
EFIAPI OnFwVolInstalled(
    IN EFI_EVENT Event,
    IN VOID      *Context )
{
    EFI_STATUS Status;
    EFI_HANDLE                        *Handles;
    UINTN NumHandles;

    Handles    = NULL;
    NumHandles = 0;
    Status     = pBS->LocateHandleBuffer(
        ByRegisterNotify,
        NULL,
        *(VOID**)Context,
        &NumHandles,
        &Handles
        );

    ASSERT(!EFI_ERROR( Status ));

    while (!EFI_ERROR( Status ) && NumHandles > 0 )
    {
        NumHandles--;
        Status = MeasureFv( &mTcgDxeData.TcgServiceProtocol,
                            Handles[NumHandles] );
    }

    if ( Handles != NULL )
    {
        pBS->FreePool( Handles );
    }
}

static EFI_STATUS MonitorFvs(
    void )
{
    EFI_STATUS Status;
    EFI_EVENT Event;
    static VOID                       *RegFwVol;

    Status = pBS->CreateEvent(
        EFI_EVENT_NOTIFY_SIGNAL,
        EFI_TPL_DRIVER,
        OnFwVolInstalled,
        (VOID*)&RegFwVol,
        &Event
        );
    ASSERT( !EFI_ERROR( Status ));

    Status = pBS->RegisterProtocolNotify(
        &gEfiFirmwareVolumeProtocolGuid,
        Event,
        &RegFwVol
        );
    ASSERT( !EFI_ERROR( Status ));

    return Status;
}


#define FAST_BOOT_VARIABLE_GUID \
    { 0xb540a530, 0x6978, 0x4da7, 0x91, 0xcb, 0x72, 0x7, 0xd7, 0x64, 0xd2, 0x62 }
EFI_GUID FastBootVariableGuid = FAST_BOOT_VARIABLE_GUID;
EFI_GUID AmitcgefiOsVariableGuid = AMI_TCG_EFI_OS_VARIABLE_GUID;






//*******************************************************************************
//<AMI_PHDR_START>
//
// Procedure:   FindAndMeasureDxeFWVol
//
// Description: 
//
// Input:      
//
// Output:      EFI_STATUS
//
// Modified:
//
// Referrals:
//
// Notes:
//<AMI_PHDR_END>
//******************************************************************************
EFI_STATUS FindAndMeasureDxeFWVol()
{
    PEI_EFI_POST_CODE       ev;
    UINT32                   n;
    UINTN                   last;
    EFI_STATUS              Status;
    EFI_GUID                      NameGuid =\
                            {0x7739f24c, 0x93d7, 0x11d4,\
                             0x9a, 0x3a, 0x0, 0x90, 0x27, 0x3f, 0xc1, 0x4d};
    UINTN                         Size;
    void                          *Buffer = NULL;
    EFI_TCG_PROTOCOL			  *TcgProtocol;
    VOID                          *HobStart;
    UINTN                          TableEntries;
    EFI_PEI_HOB_POINTERS           FirmwareVolumeHob;
    BOOLEAN                        Found=FALSE;
   
    TableEntries = pST->NumberOfTableEntries;

    while ( TableEntries > 0 )
    {
        TableEntries--;

        if ((!MemCmp(
                 &pST->ConfigurationTable[TableEntries].VendorGuid,
                 &NameGuid, sizeof(EFI_GUID))))
        {            
            HobStart = pST->ConfigurationTable[TableEntries].VendorTable;
            FirmwareVolumeHob.Raw = GetHob (EFI_HOB_TYPE_FV, HobStart);
            if (FirmwareVolumeHob.Header->HobType != EFI_HOB_TYPE_FV) {
                 continue;
            }
            break;   
        }
    }        
   
    for (Status = EFI_NOT_FOUND; EFI_ERROR (Status);) {
        if (END_OF_HOB_LIST (FirmwareVolumeHob)) {
          return EFI_NOT_FOUND;
        }

        if (GET_HOB_TYPE (FirmwareVolumeHob) == EFI_HOB_TYPE_FV) {
        if ((((UINT64)FirmwareVolumeHob.FirmwareVolume->BaseAddress)\
                < (UINT64)NVRAM_ADDRESS ) || 
                ((UINT64)FirmwareVolumeHob.FirmwareVolume->BaseAddress) == FV_MAIN_BASE)
            {
                Found = TRUE;
                break;
            }
        }
        
        FirmwareVolumeHob.Raw = GET_NEXT_HOB (FirmwareVolumeHob);
    }

    if(Found== FALSE)return EFI_NOT_FOUND;

    TRACE((-1,"TcgDxe:: Found Volume: Base = %x Length = %x",\
         FirmwareVolumeHob.FirmwareVolume->BaseAddress,\
         FirmwareVolumeHob.FirmwareVolume->Length));

    Status = pBS->AllocatePool(
                    EfiBootServicesData, 
					(UINTN)FirmwareVolumeHob.FirmwareVolume->Length, 
					&Buffer);

    if(EFI_ERROR(Status) || Buffer == NULL) return EFI_OUT_OF_RESOURCES;
  
     Status = pBS->LocateProtocol (&gEfiTcgProtocolGuid,\
                                                 NULL, &TcgProtocol);
     if(EFI_ERROR(Status)){
                  return Status;
      }

      if(FirmwareVolumeHob.FirmwareVolume->BaseAddress == FV_MAIN_BASE)
      {
         if(FirmwareVolumeHob.FirmwareVolume->Length > TCG_SIZE){
              Size = TCG_SIZE;
         }else{
             Size = (UINTN)FirmwareVolumeHob.FirmwareVolume->Length;
         }

         pBS->CopyMem(Buffer, (UINT8 *)(EFI_PHYSICAL_ADDRESS)FirmwareVolumeHob.FirmwareVolume->BaseAddress,\
                    Size);

      }else{

        Buffer = (UINT8 *)(EFI_PHYSICAL_ADDRESS)FirmwareVolumeHob.FirmwareVolume->BaseAddress;
        Size = (UINTN)FirmwareVolumeHob.FirmwareVolume->Length;
      }
      
      ev.Header.PCRIndex      = PCRi_CRTM_AND_POST_BIOS;
      ev.Header.EventType     = EV_POST_CODE;
      ev.Header.EventDataSize = sizeof (EFI_TCG_EV_POST_CODE);
      ev.Event.PostCodeAddress = \
                    (EFI_PHYSICAL_ADDRESS)FirmwareVolumeHob.FirmwareVolume->BaseAddress;

  #if defined x64_BUILD &&  x64_BUILD == 1
      ev.Event.PostCodeLength = Size;
  #else
      ev.Event.PostCodeLength = Size;
  #endif
                            
      Status = TcgProtocol->HashLogExtendEvent (TcgProtocol,
				                            (EFI_PHYSICAL_ADDRESS)Buffer,
				                            Size,
				                            TCG_ALG_SHA,
				                            (TCG_PCR_EVENT*)&ev,
 #if defined x64_BUILD &&  x64_BUILD == 1
				                            &n,
				                            &last);
 #else
				                            &n,
				                            (EFI_PHYSICAL_ADDRESS *)&last);
 #endif

      return Status;
}



EFI_STATUS
EFIAPI TcgDxeEntry(
    IN EFI_HANDLE       ImageHandle,
    IN EFI_SYSTEM_TABLE *SystemTable )
{
    EFI_STATUS Status;
    BOOLEAN Support  = FALSE;
    TPM_GetCapabilities_Input   cmdGetCap;
    TPM_RQU_COMMAND_HDR         NuvotoncmdGetTpmStatus;
    UINT8                       result[0x100];
   
    Status = pBS->LocateProtocol(
                &gEfiTpmDeviceProtocolGuid,
                NULL,
                &mTcgDxeData.TpmDevice);    

    Status = pBS->LocateProtocol(
        &gEfiTpmDeviceProtocolGuid,
        NULL,
        &mTcmDxeData.TpmDevice); 
  
    if ( EFI_ERROR( Status )){
        return Status;
    }

    Status = CopyLogToAcpiNVS( );
 
    if ( EFI_ERROR( Status ))
    {
        return Status;
    }

    if(*(UINT16 *)(UINTN)(PORT_TPM_IOMEMBASE + 0xF00) != 0x1050) 
    {
        cmdGetCap.Tag         = TPM_H2NS( TPM_TAG_RQU_COMMAND );
        cmdGetCap.ParamSize   = TPM_H2NL( sizeof (cmdGetCap));

        if(AutoSupportType()){
            cmdGetCap.CommandCode = TPM_H2NL( TCM_ORD_GetCapability );
            cmdGetCap.CommandCode = TPM_H2NL( TCM_ORD_GetCapability );
            cmdGetCap.caparea     = TPM_H2NL( TPM_CAP_FLAG );   
        }else{
            cmdGetCap.CommandCode = TPM_H2NL( TPM_ORD_GetCapability );
            cmdGetCap.CommandCode = TPM_H2NL( TPM_ORD_GetCapability );
            cmdGetCap.caparea     = TPM_H2NL( TPM_CAP_FLAG );
        }

        cmdGetCap.subCapSize  = TPM_H2NL( 4 ); // subCap is always 32bit long
        cmdGetCap.subCap      = TPM_H2NL( TPM_CAP_FLAG_PERMANENT );

        if(AutoSupportType()){
              Status = TcgDxePassThroughToTcm( &mTcmDxeData.TcgServiceProtocol,
                                               sizeof (cmdGetCap),
                                               (UINT8*)&cmdGetCap,
                                               sizeof (TPM_Capabilities_PermanentFlag),
                                               (UINT8*)&TcgDxe_Cap );
         }else{
                Status = TcgDxePassThroughToTpm( &mTcgDxeData.TcgServiceProtocol,
                                             sizeof (cmdGetCap),
                                             (UINT8*)&cmdGetCap,
                                             sizeof (TPM_Capabilities_PermanentFlag),
                                             (UINT8*)&TcgDxe_Cap );
         }
    }else{
        MemSet(&TcgDxe_Cap,sizeof(TPM_Capabilities_PermanentFlag), 0);
        NuvotoncmdGetTpmStatus.tag         = TPM_H2NS( TPM_TAG_RQU_COMMAND );
        NuvotoncmdGetTpmStatus.paramSize   = TPM_H2NL( sizeof (TPM_RQU_COMMAND_HDR));
        NuvotoncmdGetTpmStatus.ordinal     = TPM_H2NL( NTC_ORD_GET_TPM_STATUS );

        Status = TcgDxePassThroughToTpm( &mTcgDxeData.TcgServiceProtocol,
                                    sizeof (NuvotoncmdGetTpmStatus),
                                    (UINT8*)&NuvotoncmdGetTpmStatus,
                                    0x100,
                                    result );

        if(((NUVOTON_SPECIFIC_FLAGS *) result)->RetCode == 0)
        {
            if(((NUVOTON_SPECIFIC_FLAGS *)result)->isdisabled){
               TcgDxe_Cap.disabled = 1; 
            }

            if(((NUVOTON_SPECIFIC_FLAGS *)result)->isdeactivated){
                TcgDxe_Cap.deactivated = 1; 
            }

            if(((NUVOTON_SPECIFIC_FLAGS *)result)->isOwnerSet){
                TcgDxe_Cap.ownership = 1; 
            }
        }else{

            TcgDxe_Cap.RetCode = ((NUVOTON_SPECIFIC_FLAGS *)result)->RetCode;
        }
    }

    if ( TPM_H2NL(TcgDxe_Cap.RetCode)!=0)
    {
        return EFI_SUCCESS;
    }

    Support = AutoSupportType();

    ReadMORValue();

    if(!Support){
        Status = pBS->InstallMultipleProtocolInterfaces(
                   &ImageHandle,
                   &gEfiTcgProtocolGuid,
                   &mTcgDxeData.TcgServiceProtocol,
                   NULL);
#if defined (USE_BIOS_IMAGE_AS_CRTM) && (USE_BIOS_IMAGE_AS_CRTM == 0)
        FindAndMeasureDxeFWVol();
#endif
        return Status;
    }else{

        TcmOSTransition();
        return pBS->InstallMultipleProtocolInterfaces(
                   &ImageHandle,
                   &gEfiTcgProtocolGuid,
                   &mTcmDxeData.TcgServiceProtocol,
                   NULL);
    }

}
