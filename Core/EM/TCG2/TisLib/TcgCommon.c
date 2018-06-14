//*************************************************************************
// $Header: /Alaska/SOURCE/Modules/TCG2/Libraries/TisLib/TcgCommon.c 1     4/21/14 2:14p Fredericko $
//
// $Revision: 1 $
//
// $Date: 4/21/14 2:14p $
//*************************************************************************
// Revision History
// ----------------
// $Log: /Alaska/SOURCE/Modules/TCG2/Libraries/TisLib/TcgCommon.c $
// 
// 1     4/21/14 2:14p Fredericko
// 
// 3     3/17/14 3:04p Fredericko
// 
// 2     3/11/14 6:00p Fredericko
// [TAG]  		EIP151925
// [Category]  	New Feature
// [Description]  	Changes for TcgGeneric Regression Testing
// 
// 1     10/08/13 11:58a Fredericko
// Initial Check-In for Tpm-Next module
// 
// 2     10/03/13 12:34p Fredericko
// Sha256 support policy update
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
// 9     3/19/12 6:13p Fredericko
// 
// 8     3/29/11 12:24p Fredericko
// 
// 7     3/28/11 12:12p Fredericko
// [TAG]        EIP 54642
// [Category] Improvement
// [Description] 1. Checkin Files related to TCG function override
// 2. Include TCM and TPM auto detection
// [Files] Affects all TCG files
// 
// 6     5/19/10 5:07p Fredericko
// Included File Header
// Included File Revision History 
// Include \Updated AMI Function Headers
// Code Beautification
// EIP 37653
//
//*************************************************************************
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

   TcgCommon.c

   Abstract:

   TCG Commands implemented for both PEI and DXE

   --*/
//*************************************************************************
//<AMI_FHDR_START>
//
// Name:  TcgCommon.c
//
// Description: 
//  common TCG functions can be found here
//
//<AMI_FHDR_END>
//*************************************************************************
#include "TcgCommon.h"
#include <AmiDxeLib.h>
#include "token.h"
#include "Sha.h"

#define TCG_EFI_HOB_LIST_GUID \
    { 0x7739f24c, 0x93d7, 0x11d4, 0x9a, 0x3a, 0x0, 0x90, 0x27, 0x3f, 0xc1, 0x4d}

#pragma pack (1)
typedef struct _TCG_PCR_EVENT_HDR2 {
  TCG_PCRINDEX                      PCRIndex;
  TCG_EVENTTYPE                     EventType;
} TCG_PCR_EVENT_HDR2;
#pragma pack()

UINT16
__stdcall TcgCommonH2NS(
    IN UINT16 Val )
{
    return TPM_H2NS( Val );
}

UINT32
__stdcall TcgCommonH2NL(
    IN UINT32 Val )
{
    return TPM_H2NL( Val );
}



VOID
__stdcall TcgCommonCopyMem(
    IN VOID  *CallbackContext,
    OUT VOID *Dest,
    IN VOID  *Src,
    IN UINTN Size )
{
    CHAR8 *Destination8;
    CHAR8 *Source8;

    if ( Src < Dest )
    {
        Destination8 = (CHAR8*) Dest + Size - 1;
        Source8      = (CHAR8*) Src + Size - 1;
        while ( Size-- )
        {
            *(Destination8--) = *(Source8--);
        }
    }
    else {
        Destination8 = (CHAR8*) Dest;
        Source8      = (CHAR8*) Src;
        while ( Size-- )
        {
            *(Destination8++) = *(Source8++);
        }
    }
}


#pragma optimize("",off)
UINTN FindNextLogLocation(TCG_PCR_EVENT_HDR   *TcgLog, UINTN EventNum)
{
    TCG_PCR_EVENT_HDR2 *TcgLogNext = (TCG_PCR_EVENT_HDR2 *)TcgLog;
    UINTN   NextLoc =0;
    UINT32  EventSize=0;
    UINTN i=0;
    
    if(EventNum == 0) return ((UINTN) TcgLogNext);
    //return the location of the next log
    for(i=0;i<EventNum;i++){
        if(TcgLogNext == NULL)break;
        if(TcgLogNext->PCRIndex > 24 || TcgLogNext->PCRIndex < 0)
            break;

        EventSize = *(UINT32 *)(((UINTN)TcgLogNext) + TPM_SHA1_160_HASH_LEN + sizeof(TCG_PCR_EVENT_HDR2));
        NextLoc =  (UINTN)(((UINTN)TcgLogNext)+ EventSize + sizeof(EventSize)+\
                        + TPM_SHA1_160_HASH_LEN + sizeof(TCG_PCR_EVENT_HDR2));

        TcgLogNext = (TCG_PCR_EVENT_HDR2  *)NextLoc;
    }
    return ((UINTN) TcgLogNext);
}
#pragma optimize("",on)


EFI_STATUS
__stdcall TcgCommonLogEvent(
    IN VOID          *CallbackContext,
    IN TCG_PCR_EVENT *EvtLog,
    IN OUT UINT32    *TableSize,
    IN UINT32        MaxSize,
    IN TCG_PCR_EVENT *NewEntry, 
    IN UINT8         HashAlgorithm )
{
    UINT32    TempSize;

    TempSize = sizeof(TCG_PCR_EVENT)-sizeof(NewEntry->Digest) - sizeof(UINT32)-1;
    TcgCommonCopyMem( CallbackContext, EvtLog, NewEntry, TempSize ); 

    if(HashAlgorithm == 0){  
        TcgCommonCopyMem( CallbackContext, (((UINT8 *)EvtLog) + TempSize), (UINT8 *)&NewEntry->Digest.digest, sizeof(NewEntry->Digest.digest) ); 
        TempSize+=sizeof(NewEntry->Digest.digest);
        TcgCommonCopyMem( CallbackContext, (((UINT8 *)EvtLog) + TempSize), (UINT8 *)&NewEntry->EventSize, sizeof(UINT32));
        TempSize+=sizeof(UINT32);
        TcgCommonCopyMem( CallbackContext, (((UINT8 *)EvtLog) + TempSize), NewEntry->Event, NewEntry->EventSize);
    }
    *TableSize += (TempSize + NewEntry->EventSize);
    return EFI_SUCCESS;
}



EFI_STATUS
__stdcall TcmCommonLogEvent(
    IN VOID          *CallbackContext,
    IN TCM_PCR_EVENT *EvtLog,
    IN OUT UINT32    *TableSize,
    IN UINT32        MaxSize,
    IN TCM_PCR_EVENT *NewEntry )
{
    UINT32   EvtSize;

    EvtSize = NewEntry->EventSize + sizeof (*NewEntry) - 1;

    if ( *TableSize + EvtSize > MaxSize )
    {
        return EFI_OUT_OF_RESOURCES;
    }

    EvtLog = (TCM_PCR_EVENT*)((UINT8*)EvtLog + *TableSize);
    TcgCommonCopyMem( CallbackContext, EvtLog, NewEntry, EvtSize );

    *TableSize += EvtSize;
    return EFI_SUCCESS;
}



EFI_STATUS
__stdcall TcgCommonSha1Start(
    IN VOID             *CallbackContext,
    IN TCG_ALGORITHM_ID AlgId,
    OUT UINT32          *MaxBytes )
{
    EFI_STATUS            Status;
    TPM_1_2_CMD_HEADER    cmdSHA1Start = {
        TPM_H2NS( TPM_TAG_RQU_COMMAND ),
        TPM_H2NL( sizeof (TPM_1_2_CMD_HEADER)),
        TPM_H2NL( TPM_ORD_SHA1Start )
    };
    TPM_1_2_RET_SHA1START retSHA1Start;
    TPM_TRANSMIT_BUFFER   InBuffer[1], OutBuffer[1];

    if ( AlgId != TCG_ALG_SHA )
    {
        return EFI_UNSUPPORTED;
    }

    if(AutoSupportType()){
        cmdSHA1Start.Ordinal = TPM_H2NL(TCM_ORD_SHA1Start);
    }


    InBuffer[0].Buffer  = &cmdSHA1Start;
    InBuffer[0].Size    = sizeof (cmdSHA1Start);
    OutBuffer[0].Buffer = &retSHA1Start;
    OutBuffer[0].Size   = sizeof (retSHA1Start);
    Status              = TCGPASSTHROUGH( CallbackContext, InBuffer, OutBuffer );

    if ( EFI_ERROR( Status ) || retSHA1Start.Header.RetCode != 0 )
    {
        return Status;
    }

    if ( MaxBytes != NULL )
    {
        *MaxBytes = TcgCommonN2HL( retSHA1Start.MaxBytes );
    }
    return EFI_SUCCESS;
}



EFI_STATUS
__stdcall TcgCommonSha1Update(
    IN VOID   *CallbackContext,
    IN VOID   *Data,
    IN UINT32 DataLen,
    IN UINT32 MaxBytes )
{
    EFI_STATUS             Status;
    TPM_1_2_CMD_SHA1UPDATE cmdSHA1Update;
    TPM_1_2_RET_HEADER     retSHA1Update;
    TPM_TRANSMIT_BUFFER    InBuffer[2], OutBuffer[1];
    UINT8                  *DataPtr;

    if ( DataLen < 64 )
    {
        return EFI_SUCCESS;
    }

    cmdSHA1Update.Header.Tag     = TPM_H2NS( TPM_TAG_RQU_COMMAND );
    cmdSHA1Update.Header.Ordinal = TPM_H2NL( TPM_ORD_SHA1Update );

    if(AutoSupportType()){
         cmdSHA1Update.Header.Ordinal = TPM_H2NL(TCM_ORD_SHA1Update);
    }

    InBuffer[0].Buffer           = &cmdSHA1Update;
    InBuffer[0].Size             = sizeof (cmdSHA1Update);
    OutBuffer[0].Buffer          = &retSHA1Update;
    OutBuffer[0].Size            = sizeof (retSHA1Update);

    DataPtr = (UINT8*)Data;

    do
    {
        InBuffer[1].Buffer = DataPtr;
        InBuffer[1].Size   = DataLen < MaxBytes ? DataLen : MaxBytes;

        cmdSHA1Update.NumBytes         = TcgCommonH2NL((UINT32)InBuffer[1].Size );
        cmdSHA1Update.Header.ParamSize = TcgCommonH2NL(
            (UINT32)InBuffer[1].Size + sizeof (cmdSHA1Update)
            );

        DataPtr += InBuffer[1].Size;
        DataLen -= (UINT32)InBuffer[1].Size;

        Status = TCGPASSTHROUGH( CallbackContext, InBuffer, OutBuffer );
    } while ( !EFI_ERROR( Status ) && DataLen >= 64 );

    return Status;
}



EFI_STATUS
__stdcall TcgCommonSha1CompleteExtend(
    IN VOID         *CallbackContext,
    IN VOID         *Data,
    IN UINT32       DataLen,
    IN TPM_PCRINDEX PCRIndex,
    OUT TCG_DIGEST  *Digest,
    OUT TCG_DIGEST  *NewPCRValue )
{
    TPM_1_2_CMD_SHA1COMPLETEEXTEND cmdSHA1Complete;
    TPM_1_2_RET_HEADER             retSHA1Complete;
    TPM_TRANSMIT_BUFFER            InBuffer[2], OutBuffer[3];

    if ( DataLen >= 64 )
    {
        return EFI_INVALID_PARAMETER;
    }

    cmdSHA1Complete.Header.Tag       = TPM_H2NS( TPM_TAG_RQU_COMMAND );
    cmdSHA1Complete.Header.ParamSize = TcgCommonH2NL(sizeof(cmdSHA1Complete) 
                                       + DataLen);
    cmdSHA1Complete.Header.Ordinal = TPM_H2NL( TPM_ORD_SHA1CompleteExtend );

    if(AutoSupportType()){
         cmdSHA1Complete.Header.Ordinal = TPM_H2NL(TCM_ORD_SHA1CompleteExtend);
    }

    cmdSHA1Complete.PCRIndex       = TcgCommonH2NL( PCRIndex );
    cmdSHA1Complete.NumBytes       = TcgCommonH2NL( DataLen );

    InBuffer[0].Buffer = &cmdSHA1Complete;
    InBuffer[0].Size   = sizeof (cmdSHA1Complete);
    InBuffer[1].Buffer = Data;
    InBuffer[1].Size   = DataLen;

    OutBuffer[0].Buffer = &retSHA1Complete;
    OutBuffer[0].Size   = sizeof (retSHA1Complete);
    OutBuffer[1].Buffer = Digest;
    OutBuffer[1].Size   = sizeof (*Digest);
    OutBuffer[2].Buffer = NewPCRValue;
    OutBuffer[2].Size   = sizeof (*NewPCRValue);

    return TCGPASSTHROUGH( CallbackContext, InBuffer, OutBuffer );
}


EFI_STATUS
__stdcall TcmCommonSha1CompleteExtend(
    IN VOID         *CallbackContext,
    IN VOID         *Data,
    IN UINT32       DataLen,
    IN TPM_PCRINDEX PCRIndex,
    OUT TCM_DIGEST  *Digest,
    OUT TCM_DIGEST  *NewPCRValue )
{
    TPM_1_2_CMD_SHA1COMPLETEEXTEND cmdSHA1Complete;
    TPM_1_2_RET_HEADER             retSHA1Complete;
    TPM_TRANSMIT_BUFFER            InBuffer[2], OutBuffer[3];

    if ( DataLen >= 64 )
    {
        return EFI_INVALID_PARAMETER;
    }

    cmdSHA1Complete.Header.Tag       = TPM_H2NS( TPM_TAG_RQU_COMMAND );
    cmdSHA1Complete.Header.ParamSize = TcgCommonH2NL(sizeof(cmdSHA1Complete) 
                                       + DataLen);
    cmdSHA1Complete.Header.Ordinal = TPM_H2NL( TPM_ORD_SHA1CompleteExtend );

    if(AutoSupportType()){
         cmdSHA1Complete.Header.Ordinal = TPM_H2NL(TCM_ORD_SHA1CompleteExtend);
    }

    cmdSHA1Complete.PCRIndex       = TcgCommonH2NL( PCRIndex );
    cmdSHA1Complete.NumBytes       = TcgCommonH2NL( DataLen );

    InBuffer[0].Buffer = &cmdSHA1Complete;
    InBuffer[0].Size   = sizeof (cmdSHA1Complete);
    InBuffer[1].Buffer = Data;
    InBuffer[1].Size   = DataLen;

    OutBuffer[0].Buffer = &retSHA1Complete;
    OutBuffer[0].Size   = sizeof (retSHA1Complete);
    OutBuffer[1].Buffer = Digest;
    OutBuffer[1].Size   = sizeof (*Digest);
    OutBuffer[2].Buffer = NewPCRValue;
    OutBuffer[2].Size   = sizeof (*NewPCRValue);

    return TCGPASSTHROUGH( CallbackContext, InBuffer, OutBuffer );
}



EFI_STATUS
__stdcall TcmCommonExtend(
    IN  VOID         *CallbackContext,
    IN  TPM_PCRINDEX PCRIndex,
    IN  TCM_DIGEST   *Digest,
    OUT TCM_DIGEST  *NewPCRValue )
{
    TPM_1_2_CMD_HEADER  cmdHeader;
    TPM_1_2_RET_HEADER  retHeader;
    TPM_TRANSMIT_BUFFER InBuffer[3], OutBuffer[2];

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

    cmdHeader.Ordinal = TPM_H2NL( TCM_ORD_Extend );
    PCRIndex          = TcgCommonH2NL( PCRIndex );

    return TCGPASSTHROUGH( CallbackContext, InBuffer, OutBuffer );
}


EFI_STATUS
__stdcall Tcg20CommonExtend(
    IN VOID         *CallbackContext,
    IN TPM_PCRINDEX PcrIndex,
    IN TCG_DIGEST   *Digest,
    OUT TCG_DIGEST  *NewPCRValue,
    IN  UINT8        DigestSize )
{
    TPM2_PCRExtend_cmd_t  Cmd;
    TPM2_PCRExtend_res_t  Res;
    TPM2_PCRExtend_res_t  Tmpres;
    UINT32                CmdSize;
    UINT8                 *Buffer;
    UINT8                 *AuthSizeOffset;
    UINT8                 *ResultBuf = NULL;
    UINT32                ResultBufSize = 0;

    TPM_TRANSMIT_BUFFER InBuffer[1], OutBuffer[1];

    Cmd.Tag          = (TPMI_ST_COMMAND_TAG)TPM_H2NS(TPM_ST_SESSIONS);
    Cmd.CommandSize  = TPM_H2NL(sizeof(Cmd));
    Cmd.CommandCode  = TPM_H2NL(TPM_CC_PCR_Extend);

    Buffer = (UINT8 *)&Cmd.inputParameters;
    *(UINT32 *)Buffer = TPM_H2NL(PcrIndex);
    Buffer += sizeof(UINT32);

    AuthSizeOffset = Buffer;
    *(UINT32 *)Buffer = 0;
    Buffer += sizeof(UINT32);

    //  pcr authHandle
    *(UINT32 *)Buffer = TPM_H2NL(TPM_RS_PW);
    Buffer += sizeof(UINT32);

    // nonce = nullNonce
    *(UINT16 *)Buffer = 0;
    Buffer += sizeof(UINT16);

    // sessionAttributes = 0
    *(UINT8 *)Buffer = 0;
    Buffer += sizeof(UINT8);

    // auth = nullAuth
    *(UINT16 *)Buffer = 0;
    Buffer += sizeof(UINT16);

    // authorizationSize
    *(UINT32 *)AuthSizeOffset = TPM_H2NL((UINT32)(Buffer - AuthSizeOffset - sizeof(UINT32)));

	//Digest count
	*(UINT32 *)Buffer = TPM_H2NL(1);
    Buffer += sizeof(UINT32);

	//Hash alg
	*(UINT16 *)Buffer = TPM_H2NS(TPM2_ALG_SHA1);
    Buffer += sizeof(UINT16);

	// Get the digest size based on Hash Alg
    TcgCommonCopyMem(CallbackContext, Buffer, &Digest->digest, DigestSize);

    Buffer += DigestSize;

    CmdSize = (UINT32)(Buffer - (UINT8 *)&Cmd);
    Cmd.CommandSize = TPM_H2NL(CmdSize);

    ResultBuf     = (UINT8 *) &Tmpres;
    ResultBufSize = sizeof(Res);
    
    InBuffer[0].Buffer = &Cmd;
    InBuffer[0].Size   = CmdSize;
    OutBuffer[0].Buffer = ResultBuf;
    OutBuffer[0].Size   = ResultBufSize;

    return TCGPASSTHROUGH( CallbackContext, InBuffer, OutBuffer );

}




EFI_STATUS
__stdcall SHA1HashAll(
    IN VOID            *CallbackContext,
    IN VOID            *HashData,
    IN UINTN           HashDataLen,
    OUT TCG_DIGEST      *Digest
)
{
    SHA1_CTX       Sha1Ctx;
    unsigned char  DigestArray[20];

    SHA1Init( &Sha1Ctx );

    SHA1Update( &Sha1Ctx, HashData, (u32)HashDataLen );

    SHA1Final( DigestArray, &Sha1Ctx );

    TcgCommonCopyMem(
        CallbackContext,
        Digest->digest,
        DigestArray,
        sizeof (Digest->digest));

    return EFI_SUCCESS;
}


/*
EFI_STATUS
__stdcall SHA2HashAll(
    IN  VOID            *CallbackContext,
    IN  VOID            *HashData,
    IN  UINTN           HashDataLen,
    OUT TCG_DIGEST      *Digest
)
{
    SHA2_CTX       Sha2Ctx;
    unsigned char  DigestArray[32];

    sha256_init( &Sha2Ctx );

    sha256_process( &Sha2Ctx, HashData, (u32)HashDataLen );

    sha256_done( &Sha2Ctx, DigestArray );

    TcgCommonCopyMem(
        CallbackContext,
        Digest->digestSha2,
        DigestArray,
        sizeof (Digest->digestSha2));

    return EFI_SUCCESS;
}*/

//**********************************************************************
//<AMI_PHDR_START>
//
// Procedure:   GetHob
//
// Description: Find instance of a HOB type in a HOB list
//
// Input:
//      Type          The HOB type to return.
//      HobStart      The first HOB in the HOB list.
//
// Output:
//      Pointer to the Hob matching the type or NULL
//
// Modified:
//
// Referrals:
//
// Notes:
//<AMI_PHDR_END>
//**********************************************************************
VOID* GetHob(
    IN UINT16 Type,
    IN VOID   *HobStart  )
{
    EFI_PEI_HOB_POINTERS Hob;

    Hob.Raw = HobStart;

    //
    // Return input if not found
    //
    if ( HobStart == NULL )
    {
        return HobStart;
    }

    //
    // Parse the HOB list, stop if end of list or matching type found.
    //
    while ( !END_OF_HOB_LIST( Hob ))
    {
        if ( Hob.Header->HobType == Type )
        {
            break;
        }

        Hob.Raw = GET_NEXT_HOB( Hob );
    }

    //
    // Return input if not found
    //
    if ( END_OF_HOB_LIST( Hob ))
    {
        return HobStart;
    }

    return (VOID*)(Hob.Raw);
}

//**********************************************************************
//<AMI_PHDR_START>
//
// Procedure:   CompareGuid
//
// Description: Compares two input GUIDs
//
// Input:       Comparision status
//
// Output:      None
//
// Modified:
//
// Referrals:
//
// Notes:
//<AMI_PHDR_END>
//**********************************************************************
BOOLEAN CompareGuid(
    EFI_GUID *G1,
    EFI_GUID *G2 )
{
    UINT32 *p1 = (UINT32*)G1, *p2 = (UINT32*)G2;
    UINTN  i;

    for ( i = 0; i < 4; ++i )
    {
        if ( p1[i] != p2[i] )
        {
            return FALSE;
        }
    }
    return TRUE;
    ;
}

//**********************************************************************
//<AMI_PHDR_START>
//
// Procedure:   LocateATcgHob
//
// Description:
//
// Input:
//
// Output:      None
//
// Modified:
//
// Referrals:
//
// Notes:
//<AMI_PHDR_END>
//**********************************************************************
EFI_GUID gEfiAmiTHobListGuid = TCG_EFI_HOB_LIST_GUID;
VOID* LocateATcgHob(
    UINTN                   NoTableEntries,
    EFI_CONFIGURATION_TABLE *ConfigTable,
    EFI_GUID                *HOB_guid )
{
    VOID *HobStart;
    VOID *PtrHob;

    while ( NoTableEntries > 0 )
    {
        NoTableEntries--;

        if ((!MemCmp(
                 &ConfigTable[NoTableEntries].VendorGuid,
                 &gEfiAmiTHobListGuid, sizeof(EFI_GUID)
                 )))
        {
            HobStart = ConfigTable[NoTableEntries].VendorTable;

            if ( !EFI_ERROR(
                     GetNextGuidHob( &HobStart, HOB_guid, &PtrHob, NULL )
                     ))
            {
                return PtrHob;
            }
        }
    }
    return NULL;
}

//**********************************************************************
//<AMI_PHDR_START>
//
// Procedure:   GetNextGuidHob
//
// Description: Find GUID HOB
//
// Input:       HobStart    A pointer to the start hob.
//              Guid        A pointer to a guid.
// Output:
//              Buffer          A pointer to the buffer.
//              BufferSize      Buffer size.
//
// Modified:
//
// Referrals:
//
// Notes:
//<AMI_PHDR_END>
//**********************************************************************
EFI_STATUS GetNextGuidHob(
    IN OUT VOID          **HobStart,
    IN EFI_GUID          * Guid,
    OUT VOID             **Buffer,
    OUT UINTN            *BufferSize OPTIONAL )
{
    EFI_STATUS           Status;
    EFI_PEI_HOB_POINTERS GuidHob;

    if ( Buffer == NULL )
    {
        return EFI_INVALID_PARAMETER;
    }

    for ( Status = EFI_NOT_FOUND; EFI_ERROR( Status );)
    {
        GuidHob.Raw = *HobStart;

        if ( END_OF_HOB_LIST( GuidHob ))
        {
            return EFI_NOT_FOUND;
        }

        GuidHob.Raw = GetHob( EFI_HOB_TYPE_GUID_EXTENSION, *HobStart );

        if ( GuidHob.Header->HobType == EFI_HOB_TYPE_GUID_EXTENSION )
        {
            if ( CompareGuid( Guid, &GuidHob.Guid->Name ))
            {
                Status  = EFI_SUCCESS;
                *Buffer = (VOID*)((UINT8*)(&GuidHob.Guid->Name) 
                          + sizeof (EFI_GUID));

                if ( BufferSize != NULL )
                {
                    *BufferSize = GuidHob.Header->HobLength
                                  - sizeof (EFI_HOB_GUID_TYPE);
                }
            }
        }

        *HobStart = GET_NEXT_HOB( GuidHob );
    }

    return Status;
}
