//**********************************************************************
//**********************************************************************
//**                                                                  **
//**        (C)Copyright 1985-2012, American Megatrends, Inc.         **
//**                                                                  **
//**                       All Rights Reserved.                       **
//**                                                                  **
//**             6145-F Northbelt Pkwy, Norcross, GA 30071            **
//**                                                                  **
//**                       Phone: (770)-246-8600                      **
//**                                                                  **
//**********************************************************************
//**********************************************************************

//**********************************************************************
// $Header: /Alaska/Projects/Intel/Haswell/LynxPoint_SharkBay-DT_Crb_1AQQW/Include/Protocol/EdidOverride.h 1     10/30/13 6:44a Ireneyang $
//
// $Revision: 1 $
//
// $Date: 10/30/13 6:44a $
//**********************************************************************
// Revision History
// ----------------
// $Log: /Alaska/Projects/Intel/Haswell/LynxPoint_SharkBay-DT_Crb_1AQQW/Include/Protocol/EdidOverride.h $
// 
// 1     10/30/13 6:44a Ireneyang
// -Fix no display in Win8. It would have a compiler error when 
//  enableing token "OEM_EDID_OVERRIDE_PROTOCOL_SUPPORT".
// 
//**********************************************************************
//<AMI_FHDR_START>
//
// Name:	EdidOverride.h
//
// Description:	EFI_EDID_OVERRIDE_PROTOCOL protocol declaration
//
//<AMI_FHDR_END>
//**********************************************************************
#ifndef __EFI_EDID_OVERRIDE_PROTOCOL__H__
#define __EFI_EDID_OVERRIDE_PROTOCOL__H__
#ifdef __cplusplus
extern "C" {
#endif

#define EFI_EDID_OVERRIDE_PROTOCOL_GUID \
    { 0x48ecb431, 0xfb72, 0x45c0, 0xa9, 0x22, 0xf4, 0x58, 0xfe, 0x4, 0xb, 0xd5 }

GUID_VARIABLE_DECLARATION (gEfiEdidOverrideProtocolGuid, EFI_EDID_OVERRIDE_PROTOCOL_GUID);

#define EFI_EDID_OVERRIDE_DONT_OVERRIDE   0x01
#define EFI_EDID_OVERRIDE_ENABLE_HOT_PLUG 0x02

typedef struct _EFI_EDID_OVERRIDE_PROTOCOL EFI_EDID_OVERRIDE_PROTOCOL;

typedef EFI_STATUS (EFIAPI *EFI_EDID_OVERRIDE_PROTOCOL_GET_EDID) (
  IN  EFI_EDID_OVERRIDE_PROTOCOL        *This,
  IN  EFI_HANDLE                        *ChildHandle,
  OUT UINT32                            *Attributes,
  IN OUT UINTN                          *EdidSize,
  IN OUT UINT8                          **Edid
  );

typedef struct _EFI_EDID_OVERRIDE_PROTOCOL {
  EFI_EDID_OVERRIDE_PROTOCOL_GET_EDID   GetEdid;
} EFI_EDID_OVERRIDE_PROTOCOL;

/****** DO NOT WRITE BELOW THIS LINE *******/
#ifdef __cplusplus
}
#endif
#endif
//**********************************************************************
//**********************************************************************
//**                                                                  **
//**        (C)Copyright 1985-2012, American Megatrends, Inc.         **
//**                                                                  **
//**                       All Rights Reserved.                       **
//**                                                                  **
//**             6145-F Northbelt Pkwy, Norcross, GA 30071            **
//**                                                                  **
//**                       Phone: (770)-246-8600                      **
//**                                                                  **
//**********************************************************************
//**********************************************************************