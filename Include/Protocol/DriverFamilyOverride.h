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

//*************************************************************************
// $Header: /Alaska/BIN/Core/Include/Protocol/DriverFamilyOverride.h 1     4/22/11 6:45p Artems $
//
// $Revision: 1 $
//
// $Date: 4/22/11 6:45p $
//*************************************************************************
// Revision History
// ----------------
// $Log: /Alaska/BIN/Core/Include/Protocol/DriverFamilyOverride.h $
// 
// 1     4/22/11 6:45p Artems
// 
//*************************************************************************
//<AMI_FHDR_START>
//
// Name:  DriverFamilyOverride.h
//
//  Description:
//  EFI_DRIVER_FAMILY_OVERRIDE_PROTOCOL definition file
//
//<AMI_FHDR_END>
//*************************************************************************
#ifndef __DRIVER_FAMILY_OVERRIDE_PROTOCOL__H__
#define __DRIVER_FAMILY_OVERRIDE_PROTOCOL__H__
#ifdef __cplusplus
extern "C" {
#endif

#include <EFI.h>

#define EFI_DRIVER_FAMILY_OVERRIDE_PROTOCOL_GUID \
    {0xb1ee129e, 0xda36, 0x4181, 0x91, 0xf8, 0x4, 0xa4, 0x92, 0x37, 0x66, 0xa7 }

GUID_VARIABLE_DECLARATION(gEfiDriverFamilyOverrideProtocolGuid, EFI_DRIVER_FAMILY_OVERRIDE_PROTOCOL_GUID);


typedef struct _EFI_DRIVER_FAMILY_OVERRIDE_PROTOCOL EFI_DRIVER_FAMILY_OVERRIDE_PROTOCOL;

typedef
UINT32
(EFIAPI *EFI_DRIVER_FAMILY_OVERRIDE_GET_VERSION) (
    IN EFI_DRIVER_FAMILY_OVERRIDE_PROTOCOL *This
);

struct _EFI_DRIVER_FAMILY_OVERRIDE_PROTOCOL {
    EFI_DRIVER_FAMILY_OVERRIDE_GET_VERSION GetVersion;
};


/****** DO NOT WRITE BELOW THIS LINE *******/
#ifdef __cplusplus
}
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
