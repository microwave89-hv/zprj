//**********************************************************************
//**********************************************************************
//**                                                                  **
//**        (C)Copyright 1985-2014, American Megatrends, Inc.         **
//**                                                                  **
//**                       All Rights Reserved.                       **
//**                                                                  **
//**         5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093     **
//**                                                                  **
//**                       Phone: (770)-246-8600                      **
//**                                                                  **
//**********************************************************************
//**********************************************************************
//**********************************************************************
// $Header: /Alaska/SOURCE/Modules/NVMe/Nvme Protocol/AmiNvmePassThru.h 1     9/04/14 8:02a Anandakrishnanl $
//
// $Revision: 1 $
//
// $Date: 9/04/14 8:02a $
//**********************************************************************
// Revision History
// ----------------
// $Log: /Alaska/SOURCE/Modules/NVMe/Nvme Protocol/AmiNvmePassThru.h $
// 
// 1     9/04/14 8:02a Anandakrishnanl
// [TAG]  		EIP180861
// [Category]  	Improvement
// [Description]  	Legacy Boot support in Aptio 4.x Nvme driver
// [Files]  		AmiNvmeProtocol.cif
// AmiNvmeController.h
// AmiNvmePassThru.h
// AmiNvmeLegacy.h
// 
//**********************************************************************
//**********************************************************************
//<AMI_FHDR_START>
//
// Name:        AmiNvmePassThru.h
//
// Description: Protocol Header file for the Nvme PassThru Protocol 
//
//<AMI_FHDR_END>
//**********************************************************************

#ifndef _NVME_PASSTHRU_PROTOCOL_H_
#define _NVME_PASSTHRU_PROTOCOL_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <Protocol/AmiNvmeController.h>

typedef struct _AMI_NVME_PASS_THRU_PROTOCOL AMI_NVME_PASS_THRU_PROTOCOL;

typedef EFI_STATUS
(EFIAPI *AMI_NVME_PASS_THRU_EXECUTECMD)(
    IN  AMI_NVME_CONTROLLER_PROTOCOL    *NvmeController,
    IN  NVME_COMMAND_WRAPPER            *NvmeCmdWrapper,
    OUT COMPLETION_QUEUE_ENTRY          *CmdCompletionData
);

typedef struct _AMI_NVME_PASS_THRU_PROTOCOL {
    AMI_NVME_PASS_THRU_EXECUTECMD       ExecuteNvmeCmd;
} AMI_NVME_PASS_THRU_PROTOCOL;

extern EFI_GUID gAmiNvmePassThruProtocolGuid;

/****** DO NOT WRITE BELOW THIS LINE *******/
#ifdef __cplusplus
}
#endif

#endif

//**********************************************************************
//**********************************************************************
//**                                                                  **
//**        (C)Copyright 1985-2014, American Megatrends, Inc.         **
//**                                                                  **
//**                       All Rights Reserved.                       **
//**                                                                  **
//**         5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093     **
//**                                                                  **
//**                       Phone: (770)-246-8600                      **
//**                                                                  **
//**********************************************************************
//**********************************************************************
