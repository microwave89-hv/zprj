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
// $Header: /Alaska/SOURCE/Modules/NVMe/Nvme Protocol/AmiNvmeLegacy.h 1     9/04/14 8:02a Anandakrishnanl $
//
// $Revision: 1 $
//
// $Date: 9/04/14 8:02a $
//**********************************************************************
// Revision History
// ----------------
// $Log: /Alaska/SOURCE/Modules/NVMe/Nvme Protocol/AmiNvmeLegacy.h $
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
// Name:        AmiNvmeLegacy.h
//
// Description: Protocol header file the Ami Nvme Legacy interface 
//
//<AMI_FHDR_END>
//**********************************************************************

#ifndef __NVME_LEGACY_PROTOCOL_H__
#define __NVME_LEGACY_PROTOCOL_H__

#ifdef __cplusplus
extern "C" {
#endif

typedef struct _NVME_LEGACY_MASS_DEVICE NVME_LEGACY_MASS_DEVICE;

typedef EFI_STATUS
(EFIAPI *AMI_NVME_LEGACY_DEVICE_INSTALL)(
    IN OUT NVME_LEGACY_MASS_DEVICE      *AddNvmeLegacyDevice
);

typedef struct {
    AMI_NVME_LEGACY_DEVICE_INSTALL       AddNvmeLegacyDevice;
} AMI_NVME_LEGACY_PROTOCOL;


extern EFI_GUID gAmiNvmeLegacyProtocolGuid;


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
