//**********************************************************************
//**********************************************************************
//**                                                                  **
//**        (C)Copyright 1985-2010, American Megatrends, Inc.         **
//**                                                                  **
//**                       All Rights Reserved.                       **
//**                                                                  **
//**           5555 Oakbrook Pkwy, Suite 200, Norcross, GA 30093      **
//**                                                                  **
//**                       Phone: (770)-246-8600                      **
//**                                                                  **
//**********************************************************************
//**********************************************************************

//**********************************************************************
// $Header: /Alaska/SOURCE/Modules/CSM/Generic/Protocol/CsmPlatform.h 13    1/27/14 12:59p Olegi $
//
// $Revision: 13 $
//
// $Date: 1/27/14 12:59p $
//**********************************************************************
// Revision History
// ----------------
// $Log: /Alaska/SOURCE/Modules/CSM/Generic/Protocol/CsmPlatform.h $
// 
// 13    1/27/14 12:59p Olegi
// EIP151588: added Rom field to CSM_PLATFORM_POLICY_DATA
// 
// 12    11/14/11 12:05p Olegi
// 
// 11    11/10/11 7:31p Olegi
// Added thunk GUID protocol definition.
// 
// 10    10/03/11 3:19p Olegi
// [TAG]  		EIP71591
// [Category]  	Improvement
// [Description]  	CSM opt-out changes
// 
// 9     8/19/11 4:30p Olegi
// [TAG]  		EIP65477
// [Category]  	Improvement
// [Description]  	CSM Opt-out mechanism
// [Files]  		csmplatform.h, csm.dxs
// 
// 8     3/01/10 3:57p Olegi
// Changed the prototypes of Pre/PostOptionRom functions; requires the
// update of AMI Board component. EIP34085.
// 
// 7     1/12/10 11:51a Olegi
// Copyright message updated.
// 
// 6     6/18/09 10:06a Olegi
// Added definition of CSM OpROM policy related data.
// 
// 5     4/27/07 5:17p Olegi
// CSM.CHM file preparation.
//
// 4     4/13/07 9:51a Olegi
//
//**********************************************************************
//<AMI_FHDR_START>
//
// Name:    CsmPlatform.h
//
// Description: CsmPlatform protocol declaration
//
//<AMI_FHDR_END>
//**********************************************************************

#ifndef __CSM_PLATFORM_PROTOCOL_H__
#define __CSM_PLATFORM_PROTOCOL_H__

#ifdef __cplusplus
extern "C" {
#endif

#include <EFI.h>

// {91FA9DFD-DBD4-44ae-97A4-BD1837D5B462}
#define CSM_PLATFORM_PROTOCOL_GUID \
    {0x91fa9dfd,0xdbd4,0x44ae,0x97,0xa4,0xbd,0x18,0x37,0xd5,0xb4,0x62}

GUID_VARIABLE_DECLARATION(gCsmPlatformProtocolGuid,CSM_PLATFORM_PROTOCOL_GUID);

#ifndef GUID_VARIABLE_DEFINITION
#include <Protocol/PciIo.h>
#include <Protocol/LegacyBios.h>

typedef struct _CSM_PLATFORM_PROTOCOL CSM_PLATFORM_PROTOCOL;

typedef EFI_STATUS (EFIAPI *CSM_PLATFORM_PROTOCOL_PRE_PROCESS_OPROM) (
    IN CSM_PLATFORM_PROTOCOL *This,
    IN EFI_PCI_IO_PROTOCOL *PciIo,
    IN VOID **RomImage
);

typedef EFI_STATUS (EFIAPI *CSM_PLATFORM_PROTOCOL_POST_PROCESS_OPROM) (
    IN CSM_PLATFORM_PROTOCOL *This,
    IN EFI_PCI_IO_PROTOCOL *PciIo,
    IN VOID **RomImage
);

typedef EFI_STATUS (EFIAPI *CSM_PLATFORM_PROTOCOL_GET_ATAPI_DEVICE_TYPE) (
    IN CSM_PLATFORM_PROTOCOL *This,
    IN struct _ATAPI_IDENTIFY *IdentifyDriveData,
    OUT UINT16 *DevType
);

typedef struct _CSM_PLATFORM_PROTOCOL {
    CSM_PLATFORM_PROTOCOL_PRE_PROCESS_OPROM PreProcessOpRom;
    CSM_PLATFORM_PROTOCOL_POST_PROCESS_OPROM PostProcessOpRom;
    CSM_PLATFORM_PROTOCOL_GET_ATAPI_DEVICE_TYPE GetAtapiDeviceType;
} CSM_PLATFORM_PROTOCOL;

#define CSM_OPRROM_POLICY_GUID \
    {0xf2a128ff,0x257b,0x456e,0x9d,0xe8,0x63,0xe7,0xc7,0xdc,0xdf,0xac}

typedef struct _CSM_PLATFORM_POLICY_DATA {
    EFI_PCI_IO_PROTOCOL *PciIo;
    BOOLEAN             ExecuteThisRom;
    VOID                **Rom;
} CSM_PLATFORM_POLICY_DATA;

// The following GUID is used in DXS; it can be installed by the driver that
// has minimum or no dependencies so that it is launched earlier than CSM.
//  
#ifndef AMI_LOAD_CSM_GUID
#define AMI_LOAD_CSM_GUID  \
  { 0x16287ba4, 0x5b9d, 0x4d98, 0x91, 0x9f, 0x7b, 0x7b, 0x78, 0xcb, 0x2b, 0xe0 }
#endif

#ifndef AMI_CSM_DRIVER_STARTED_GUID
#define AMI_CSM_DRIVER_STARTED_GUID  \
  { 0x3EA824D1, 0x81E3, 0x4FF5, 0xBD, 0x43, 0xBB, 0x9C, 0x65, 0xDF, 0x7C, 0x46}
#endif

#ifndef AMI_CSM_THUNK_PROTOCOL_GUID
#define AMI_CSM_THUNK_PROTOCOL_GUID \
  { 0x2362ea9c, 0x84e5, 0x4dff, 0x83, 0xbc, 0xb5, 0xac, 0xec, 0xb5, 0x7c, 0xbb }
#endif

/****** DO NOT WRITE BELOW THIS LINE *******/
#endif // #ifndef GUID_VARIABLE_DEFINITION
#ifdef __cplusplus
}
#endif
#endif

//**********************************************************************
//**********************************************************************
//**                                                                  **
//**        (C)Copyright 1985-2010, American Megatrends, Inc.         **
//**                                                                  **
//**                       All Rights Reserved.                       **
//**                                                                  **
//**           5555 Oakbrook Pkwy, Suite 200, Norcross, GA 30093      **
//**                                                                  **
//**                       Phone: (770)-246-8600                      **
//**                                                                  **
//**********************************************************************
//**********************************************************************
