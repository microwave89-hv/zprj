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

//**********************************************************************
// $Header: /Alaska/BIN/Core/Include/Protocol/HiiConfigRouting.h 2     10/13/09 6:06p Felixp $
//
// $Revision: 2 $
//
// $Date: 10/13/09 6:06p $
//**********************************************************************
// Revision History
// ----------------
// $Log: /Alaska/BIN/Core/Include/Protocol/HiiConfigRouting.h $
// 
// 2     10/13/09 6:06p Felixp
// Hii.h renamed to UefiHii.h
// 
// 1     10/09/09 3:52p Felixp
// 
// 1     2/27/09 3:55p Artems
// Initial check-in
// 
// 1     3/18/07 5:23p Felixp
// 
//**********************************************************************
//<AMI_FHDR_START>
//
// Name:	HiiConfigRouting.h
//
// Description:	Hii Configuration Routing protocol header file
//
//<AMI_FHDR_END>
//**********************************************************************
#ifndef __HII_CONFIG_ROUTING_PROTOCOL__H__
#define __HII_CONFIG_ROUTING_PROTOCOL__H__
#ifdef __cplusplus
extern "C" {
#endif

#include <UefiHii.h>

#define EFI_HII_CONFIG_ROUTING_PROTOCOL_GUID \
    { 0x587e72d7, 0xcc50, 0x4f79, 0x82, 0x09, 0xca, 0x29, 0x1f, 0xc1, 0xa1, 0x0f }

GUID_VARIABLE_DECLARATION(gEfiHiiConfigRoutingProtocolGuid, EFI_HII_CONFIG_ROUTING_PROTOCOL_GUID);

typedef struct _EFI_HII_CONFIG_ROUTING_PROTOCOL EFI_HII_CONFIG_ROUTING_PROTOCOL;

typedef EFI_STATUS
(EFIAPI * EFI_HII_EXTRACT_CONFIG ) (
    IN CONST EFI_HII_CONFIG_ROUTING_PROTOCOL *This,
    IN CONST EFI_STRING Request,
    OUT EFI_STRING      *Progress,
    OUT EFI_STRING      *Results
);

typedef EFI_STATUS
(EFIAPI * EFI_HII_EXPORT_CONFIG ) (
    IN CONST EFI_HII_CONFIG_ROUTING_PROTOCOL *This,
    OUT EFI_STRING *Results
);

typedef EFI_STATUS
(EFIAPI * EFI_HII_ROUTE_CONFIG ) (
    IN CONST EFI_HII_CONFIG_ROUTING_PROTOCOL *This,
    IN CONST EFI_STRING Configuration,
    OUT EFI_STRING      *Progress
);

typedef EFI_STATUS
(EFIAPI * EFI_HII_BLOCK_TO_CONFIG ) (
    IN CONST EFI_HII_CONFIG_ROUTING_PROTOCOL *This,
    IN CONST EFI_STRING ConfigRequest,
    IN CONST UINT8      *Block,
    IN CONST UINTN      BlockSize,
    OUT EFI_STRING      *Config,
    OUT EFI_STRING      *Progress
);

typedef EFI_STATUS
(EFIAPI * EFI_HII_CONFIG_TO_BLOCK ) (
    IN CONST EFI_HII_CONFIG_ROUTING_PROTOCOL *This,
    IN CONST EFI_STRING ConfigResp,
    IN OUT CONST UINT8 *Block,
    IN OUT UINTN *BlockSize,
    OUT EFI_STRING *Progress
);

typedef EFI_STATUS
(EFIAPI * EFI_HII_GET_ALT_CFG ) (
    IN CONST EFI_HII_CONFIG_ROUTING_PROTOCOL *This,
    IN CONST EFI_STRING ConfigResp,
    IN CONST EFI_GUID   *Guid,
    IN CONST EFI_STRING Name,
    IN CONST EFI_DEVICE_PATH_PROTOCOL *DevicePath,
    IN CONST EFI_STRING AltCfgId,
    OUT EFI_STRING      *AltCfgResp
);

struct _EFI_HII_CONFIG_ROUTING_PROTOCOL {
    EFI_HII_EXTRACT_CONFIG ExtractConfig;
    EFI_HII_EXPORT_CONFIG ExportConfig;
    EFI_HII_ROUTE_CONFIG RouteConfig;
    EFI_HII_BLOCK_TO_CONFIG BlockToConfig;
    EFI_HII_CONFIG_TO_BLOCK ConfigToBlock;
    EFI_HII_GET_ALT_CFG GetAltConfig;
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