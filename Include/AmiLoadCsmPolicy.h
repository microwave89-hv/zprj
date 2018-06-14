//**********************************************************************
//**********************************************************************
//**                                                                  **
//**        (C)Copyright 1985-2011, American Megatrends, Inc.         **
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
// $Header: /Alaska/BIN/Core/Include/AmiLoadCsmPolicy.h 2     5/22/12 10:15a Artems $
//
// $Revision: 2 $
//
// $Date: 5/22/12 10:15a $
//**********************************************************************
// Revision History
// ----------------
// $Log: /Alaska/BIN/Core/Include/AmiLoadCsmPolicy.h $
// 
// 2     5/22/12 10:15a Artems
// [TAG]  		EIP86097
// [Description]  	Separate control for loading UEFI Oprom Driver
// [Files]  		AmiLoadCsmPolicy.h, PciBus.c, CsmOptOut.c, CsmOptOut.sdl
// CsmOptOut.mak
// 
// 1     10/28/11 1:18p Artems
// Added header to support CSM opt-out feature
// 
//**********************************************************************
//<AMI_FHDR_START>
//
// Name: AmiLoadCsmPolicy.h
//
// Description: This file contains guid definitions for AMI LoadCsm policy
//
//<AMI_FHDR_END>
//**********************************************************************
#ifndef __AMI_LOAD_CSM_POLICY__H__
#define __AMI_LOAD_CSM_POLICY__H__
#ifdef __cplusplus
extern "C" {
#endif

#define AMI_LOAD_CSM_GUID \
  { 0x16287ba4, 0x5b9d, 0x4d98, 0x91, 0x9f, 0x7b, 0x7b, 0x78, 0xcb, 0x2b, 0xe0 }

#define AMI_CSM_DRIVER_STARTED_GUID \
  { 0x3EA824D1, 0x81E3, 0x4FF5, 0xBD, 0x43, 0xBB, 0x9C, 0x65, 0xDF, 0x7C, 0x46 }

#define OPROM_START_END_PROTOCOL_GUID \
  { 0xf2a128ff, 0x257b, 0x456e, 0x9d, 0xe8, 0x63, 0xe7, 0xc7, 0xdc, 0xdf, 0xac }

#define AMI_CSM_THUNK_PROTOCOL_GUID \
  { 0x2362ea9c, 0x84e5, 0x4dff, 0x83, 0xbc, 0xb5, 0xac, 0xec, 0xb5, 0x7c, 0xbb }

#define AMI_OPROM_POLICY_PROTOCOL_GUID \
  { 0x542d6248, 0x4198, 0x4960, 0x9f, 0x59, 0x23, 0x84, 0x64, 0x6d, 0x63, 0xb4 }

typedef	struct _AMI_OPROM_POLICY_PROTOCOL AMI_OPROM_POLICY_PROTOCOL;

typedef EFI_STATUS (*CHECK_UEFI_OPROM_POLICY) (
    IN	AMI_OPROM_POLICY_PROTOCOL *This,
    IN	EFI_HANDLE                PciHandle
);

struct _AMI_OPROM_POLICY_PROTOCOL {
    CHECK_UEFI_OPROM_POLICY CheckUefiOpromPolicy;
};


/****** DO NOT WRITE BELOW THIS LINE *******/
#ifdef __cplusplus
}
#endif
#endif
//**********************************************************************
//**********************************************************************
//**                                                                  **
//**        (C)Copyright 1985-2009, American Megatrends, Inc.         **
//**                                                                  **
//**                       All Rights Reserved.                       **
//**                                                                  **
//**      5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093        **
//**                                                                  **
//**                       Phone: (770)-246-8600                      **
//**                                                                  **
//**********************************************************************
//**********************************************************************
