//**********************************************************************
//**********************************************************************
//**                                                                  **
//**        (C)Copyright 1985-2010, American Megatrends, Inc.         **
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
// $Header: /Alaska/SOURCE/Modules/CSM/Generic/Protocol/CsmVideoPolicy.h 1     4/26/10 11:08a Felixp $
//
// $Revision: 1 $
//
// $Date: 4/26/10 11:08a $
//**********************************************************************
// Revision History
// ----------------
// $Log: /Alaska/SOURCE/Modules/CSM/Generic/Protocol/CsmVideoPolicy.h $
// 
// 1     4/26/10 11:08a Felixp
// 
// 6     1/13/10 2:13p Felixp
// 
//**********************************************************************
//<AMI_FHDR_START>
//
// Name:  CsmVideoPolicy.h
//
// Description:	CSM Video Policy Protocol Declaration
//
//<AMI_FHDR_END>
//**********************************************************************
#ifndef __CSM_VIDEO_POLICY_PROTOCOL__H__
#define __CSM_VIDEO_POLICY_PROTOCOL__H__
#ifdef __cplusplus
extern "C" {
#endif
#include <Efi.h>

// {3A4E4376-4871-4b0e-A02F-ED36F2AECD00}
#define CSM_VIDEO_POLICY_PROTOCOL_GUID\
    { 0x3a4e4376, 0x4871, 0x4b0e, 0xa0, 0x2f, 0xed, 0x36, 0xf2, 0xae, 0xcd, 0x0 }

GUID_VARIABLE_DECLARATION(gCsmVideoPolicyProtocolGuid, CSM_VIDEO_POLICY_PROTOCOL_GUID);

typedef struct _CSM_VIDEO_POLICY_PROTOCOL CSM_VIDEO_POLICY_PROTOCOL;

typedef EFI_STATUS (EFIAPI *CSM_VIDEO_POLICY_GET_MODE)(
    IN CSM_VIDEO_POLICY_PROTOCOL *This, IN BOOLEAN *IsTextMode
);

typedef EFI_STATUS (EFIAPI *CSM_VIDEO_POLICY_SET_MODE)(
    IN CSM_VIDEO_POLICY_PROTOCOL *This,
    IN BOOLEAN TextMode, IN BOOLEAN ForceModeChange
);

struct _CSM_VIDEO_POLICY_PROTOCOL{
    CSM_VIDEO_POLICY_GET_MODE GetMode;
    CSM_VIDEO_POLICY_SET_MODE SetMode;
};
/****** DO NOT WRITE BELOW THIS LINE *******/
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
//**      5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093        **
//**                                                                  **
//**                       Phone: (770)-246-8600                      **
//**                                                                  **
//**********************************************************************
//**********************************************************************
