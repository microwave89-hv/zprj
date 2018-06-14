//**********************************************************************
//**********************************************************************
//**                                                                  **
//**        (C)Copyright 1985-2010, American Megatrends, Inc.         **
//**                                                                  **
//**                       All Rights Reserved.                       **
//**                                                                  **
//**        5555 Oakbrook Pkwy, Suite 200, Norcross, GA 30093         **
//**                                                                  **
//**                       Phone: (770)-246-8600                      **
//**                                                                  **
//**********************************************************************
//*************************************************************************
// $Header: /Alaska/SOURCE/Modules/TCG2/Libraries/TisLib/TcmPc.h 1     4/21/14 2:15p Fredericko $
//
// $Revision: 1 $
//
// $Date: 4/21/14 2:15p $
//*************************************************************************
// Revision History
// ----------------
// $Log: /Alaska/SOURCE/Modules/TCG2/Libraries/TisLib/TcmPc.h $
// 
// 1     4/21/14 2:15p Fredericko
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
// 2     3/29/11 12:27p Fredericko
// [TAG]        EIP 54642
// [Category] Improvement
// [Description] 1. Checkin Files related to TCG function override 
// 2. Include TCM and TPM auto detection
// [Files] Affects all TCG files
//
//
//*************************************************************************
//<AMI_FHDR_START>
//
// Name:  TcmPc.h
//
// Description:
//       Header file for Tcm structures
//
//<AMI_FHDR_END>
//*************************************************************************
#ifndef _TCMPC_H_
#define _TCMPC_H_
#include "TcgEfi12.h"


#pragma pack (push)
#pragma pack (1)



typedef struct tdTCM_PCR_EVENT {
  UINT32            PCRIndex;  // PCRIndex event extended to
  UINT32            EventType; // TCG EFI event type
  TCM_DIGEST        Digest;    // Value extended into PCRIndex
  UINT32            EventSize; // Size of the event data
  UINT8             Event[1];  // The event data
} TCM_PCR_EVENT;


struct _EFI_TCM_EV_S_CRTM_VERSION {
  EFI_GUID                          VersionGuid;
};


struct _EFI_TCM_EV_POST_CODE {
  EFI_PHYSICAL_ADDRESS              PostCodeAddress;
  UINT64                            PostCodeLength;
};


struct _EFI_TCM_EV_TAG_OPTION_ROM_EXECUTE
{
    UINT16     Reserved;
    UINT16     PFA;
    TCM_DIGEST Hash;
};


struct _EFI_TCM_EV_CPU_MICROCODE
{
    EFI_PHYSICAL_ADDRESS MicrocodeEntrypoint;
};


union _EFI_TCM_EV_TAG_EVENT_DATA
{
    struct _EFI_TCM_EV_TAG_OPTION_ROM_EXECUTE
    OptionRomExecute;
};


struct _EFI_TCM_EV_TAG
{
    UINT32 EventID;
    UINT32 EventSize;
    union _EFI_TCM_EV_TAG_EVENT_DATA EventData;
};


typedef struct _EFI_TCM_PCR_EVENT_HEADER
{
    TPM_PCRINDEX PCRIndex;
    UINT32       EventType;
    TCM_DIGEST   Digest;
    UINT32       EventDataSize;
} EFI_TCM_PCR_EVENT_HEADER;


typedef union _EFI_TCM_PCR_EVENT_DATA
{
    struct _EFI_TCM_EV_S_CRTM_VERSION SCrtmVersion;
    struct _EFI_TCM_EV_POST_CODE PostCode;
    struct _EFI_TCM_EV_TAG Tagged;
    struct _EFI_TCM_EV_CPU_MICROCODE Mcu;
} EFI_TCM_PCR_EVENT_DATA;



typedef struct _EFI_TCM_PCR_EVENT
{
    EFI_TCM_PCR_EVENT_HEADER Header;
    EFI_TCM_PCR_EVENT_DATA   Event;
} EFI_TCM_PCR_EVENT;

#pragma pack (pop)

#endif  // _TPMPC_H_
