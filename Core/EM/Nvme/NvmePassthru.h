//**********************************************************************
//**********************************************************************
//**                                                                  **
//**        (C)Copyright 1985-2015, American Megatrends, Inc.         **
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
// $Header: /Alaska/SOURCE/Modules/NVMe/NvmePassthru.h 1     5/14/15 2:36a Karthikar $
//
// $Revision: 1 $
//
// $Date: 5/14/15 2:36a $ 
//**********************************************************************
//**********************************************************************
//<AMI_FHDR_START>
//
// Name:        NvmePassthru.h
//
// Description: Header file for NvmePassthru.h file 
//
//<AMI_FHDR_END>
//**********************************************************************


#ifndef __NVM_PASS_THRU_H__
#define __NVM_PASS_THRU_H__

#ifdef __cplusplus
extern "C" {
#endif

#include <Efi.h>
#include "Protocol/AmiNvmeController.h"
#include "Protocol/NvmExpressPassThru.h"
#include "EdkIICommon.h"

#define LIST_ENTRY EFI_LIST_ENTRY


#define NVME_ADMIN_SUBMISSION_QUEUE 0x00
#define NVME_IO_SUBMISSION_QUEUE    0x01

#define NVME_CONTROLLER_PROTOCOL_FROM_THIS(NvmePassthruProtocol) \
        ((_CR( NvmePassthruProtocol ,NVM_EXPRESS_PASS_THRU_INSTANCE, EfiNvmExpressPassThru))->NvmeControllerProtocol)

typedef
struct _NVM_EXPRESS_PASS_THRU_INSTANCE {
    EFI_NVM_EXPRESS_PASS_THRU_PROTOCOL   EfiNvmExpressPassThru;       // Instance of EFI_NVM_EXPRESS_PASS_THRU_PROTOCOL
    AMI_NVME_CONTROLLER_PROTOCOL         *NvmeControllerProtocol;
    EFI_HANDLE                           ControllerHandle;
} NVM_EXPRESS_PASS_THRU_INSTANCE;

EFI_STATUS 
NvmePassThru ( 
    IN EFI_NVM_EXPRESS_PASS_THRU_PROTOCOL            *This,
    IN UINT32                                        NamespaceId,
    IN OUT EFI_NVM_EXPRESS_PASS_THRU_COMMAND_PACKET  *Packet,
    IN EFI_EVENT                                     Event
);

EFI_STATUS
GetNextNamespace(
    IN EFI_NVM_EXPRESS_PASS_THRU_PROTOCOL    *This,
    IN OUT UINT32                            *NamespaceId
);

EFI_STATUS 
BuildDevicePath (
    IN EFI_NVM_EXPRESS_PASS_THRU_PROTOCOL    *This,
    IN UINT32                                NamespaceId,
    IN OUT EFI_DEVICE_PATH_PROTOCOL          **DevicePath
);

EFI_STATUS 
GetNamespace (
    IN EFI_NVM_EXPRESS_PASS_THRU_PROTOCOL    *This,
    IN EFI_DEVICE_PATH_PROTOCOL              *DevicePath,
    OUT UINT32                               *NamespaceId
);

#ifdef __cplusplus
}
#endif

#endif // __NVM_PASS_THRU_H__

//**********************************************************************
//**********************************************************************
//**                                                                  **
//**        (C)Copyright 1985-2015, American Megatrends, Inc.         **
//**                                                                  **
//**                       All Rights Reserved.                       **
//**                                                                  **
//**      5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093        **
//**                                                                  **
//**                       Phone: (770)-246-8600                      **
//**                                                                  **
//**********************************************************************
//**********************************************************************

