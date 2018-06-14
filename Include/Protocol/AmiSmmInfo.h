//*************************************************************************
//*************************************************************************
//**                                                                     **
//**        (C)Copyright 1985-2010, American Megatrends, Inc.            **
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
// $Header: /Alaska/SOURCE/Modules/SMM/AmiSmmInfo.h 1     2/25/10 5:17p Markw $
//
// $Revision: 1 $
//
// $Date: 2/25/10 5:17p $
//**********************************************************************
// Revision History
// ----------------
// $Log: /Alaska/SOURCE/Modules/SMM/AmiSmmInfo.h $
// 
// 1     2/25/10 5:17p Markw
// Initial version
// 
//**********************************************************************

//<AMI_FHDR_START>
//----------------------------------------------------------------------------
//
// Name: AmiSmmInfo.h
//
// Description:	Provide AMI Smm Info
//
//----------------------------------------------------------------------------
//<AMI_FHDR_END>

#ifndef __AMI_SMM_INFO_H__
#define __AMI_SMM_INFO_H__
#ifdef __cplusplus
extern "C" {
#endif
#include <Efi.h>

// {EB5198EB-E7F5-45a1-9CCB-E53364BB4992}
#define AMI_SMM_INFO_PROTOCOL_GUID \
    {0xeb5198eb, 0xe7f5, 0x45a1, 0x9c, 0xcb, 0xe5, 0x33, 0x64, 0xbb, 0x49, 0x92}

GUID_VARIABLE_DECLARATION(gAmiSmmInfoProtcolGuid, AMI_SMM_INFO_PROTOCOL_GUID);

typedef struct _AMI_SMM_INFO_PROTOCOL AMI_SMM_INFO_PROTOCOL;


typedef EFI_STATUS (EFIAPI *GET_NUM_OF_CPUS_INSIDE_SMM) (
	IN  AMI_SMM_INFO_PROTOCOL   *This,
	OUT UINT32                  *Cpus
);


struct _AMI_SMM_INFO_PROTOCOL {
    UINT32                      ProtocolVer;
	GET_NUM_OF_CPUS_INSIDE_SMM  GetNumOfCpusInsideSmm;
};


/****** DO NOT WRITE BELOW THIS LINE *******/
#ifdef __cplusplus
}
#endif
#endif

//*************************************************************************
//*************************************************************************
//**                                                                     **
//**        (C)Copyright 1985-2009, American Megatrends, Inc.            **
//**                                                                     **
//**                       All Rights Reserved.                          **
//**                                                                     **
//**      5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093           **
//**                                                                     **
//**                       Phone: (770)-246-8600                         **
//**                                                                     **
//*************************************************************************
//*************************************************************************



