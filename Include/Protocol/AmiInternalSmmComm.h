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

//**********************************************************************
// $Header: /Alaska/SOURCE/Modules/SMM/AmiInternalSmmComm.h 1     4/15/11 4:43p Markw $
//
// $Revision: 1 $
//
// $Date: 4/15/11 4:43p $
//**********************************************************************
// Revision History
// ----------------
// $Log: /Alaska/SOURCE/Modules/SMM/AmiInternalSmmComm.h $
// 
// 1     4/15/11 4:43p Markw
// [TAG]  		EIP57440
// [Category]  	New Feature
// [Description]  	Add PI 1.1 SMM Communicate support.
// [Files]  		Smm.cif,  SmmCommunicate.cif, SmmCommunicate.sdl,
// SmmCommunicate.c, SmmCommunicate.dxs, SmmDxeCommunicate.dxs,
// SmmCommunicate.mak, SmmPiProtocols.cif, SmmCommunication.h,
// AmiInternalSmmComm.h
//
//**********************************************************************

//<AMI_FHDR_START>
//----------------------------------------------------------------------------
//
// Name: AmiInternalSmmComm.h
//
// Description: Protocol used by SmmCommunication to Communication DXE driver know SMM has been installed.
//
//----------------------------------------------------------------------------
//<AMI_FHDR_END>

#ifndef __AMI_INT_SMM_COMM_H__
#define __AMI_INT_SMM_COMM_H__
#if PI_SPECIFICATION_VERSION >= 0x0001000A

#ifdef __cplusplus
extern "C" {
#endif
#include <EFI.h>

// {B27DAB38-9814-4e06-A5A2-65AE9A14258F}
#define AMI_INT_SMM_COMM_PROTOCOL_GUID \
    {0xb27dab38, 0x9814, 0x4e06, 0xa5, 0xa2, 0x65, 0xae, 0x9a, 0x14, 0x25, 0x8f}

GUID_VARIABLE_DECLARATION(gAmiIntSmmCommProtocolGuid,AMI_INT_SMM_COMM_PROTOCOL_GUID);

//Currently this is a NULL protocol.


/****** DO NOT WRITE BELOW THIS LINE *******/
#ifdef __cplusplus
}
#endif
#endif
#endif

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
