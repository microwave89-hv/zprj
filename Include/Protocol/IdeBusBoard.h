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

//*************************************************************************
// $Header: /Alaska/BIN/Core/Modules/IdeBus/IdeBusBoard.h 2     9/27/11 3:17a Rajeshms $
//
// $Revision: 2 $
//
// $Date: 9/27/11 3:17a $
//*************************************************************************
// Revision History
// ----------------
// $Log: /Alaska/BIN/Core/Modules/IdeBus/IdeBusBoard.h $
// 
// 2     9/27/11 3:17a Rajeshms
// [TAG]  		EIP69295
// [Category]  	Improvement
// [Description]  	The Timeout values used by IDE and AHCI drivers are
// made as SDL tokens, so that the timeout values can be varied.
// [Files]  		IdeBusBoard.c, CORE_DXE.sdl, AhciSmm.h, AhciBus.h, IDESMM.h,
// Ata.c, Atapi.c, IdeBus.c, IdeBus.h, IdeBusMaster.c, IdeBusBoard.h
// 
// 1     8/25/10 5:37a Rameshr
// New Feature: EIP 37748
// Description: Move all the IDEBus Source driver SDL token into IdeBus
// Bin Driver.
// FilesModified: Ata.c, Atapi.c, idebus.c, IdeBus.h,
// IdebuscomponentName.c, IdeBusmaster.c IdeBusSrc.mak IdebusSrc.sdl
// IdeHpa.c, IdePowerManagement.c
// 
//     
//
//*************************************************************************
//<AMI_FHDR_START>
//
// Name:  IdeBusBoard.h
//
// Description: defines Platform IDE Protocol
//
//<AMI_FHDR_END>
//*************************************************************************
#ifndef __IdeBusBoard__H__
#define __IdeBusBoard__H__

#ifdef __cplusplus
extern "C" {
#endif

#include <EFI.h>

#define PLATFORM_IDE_PROTOCOL_GUID \
    { 0x6737f69b, 0xb8cc, 0x45bc, 0x93, 0x27, 0xcc, 0xf5, 0xee, 0xf7, 0xc, 0xde }

//
// Protocol revision number
// Any backwards compatible changes to this protocol will result in an update in the revision number
//
// Revision 2: Changed from Original version to support for ATA/ATAPI timeout values as TOKENS.
//
#define PLATFORM_IDE_PROTOCOL_REVISION  2
//
// Protocol Revision Number supported by IdeBus Source.
//
#define PLATFORM_IDE_PROTOCOL_SUPPORTED_REVISION  2

#ifndef EFI_COMPONENT_NAME2_PROTOCOL_GUID //old Core
#ifndef LANGUAGE_CODE_ENGLISH
#define LANGUAGE_CODE_ENGLISH "eng"
#endif
BOOLEAN LanguageCodesEqual(
    CONST CHAR8* LangCode1, CONST CHAR8* LangCode2
);
#endif 

//
// Interface structure for PLATFORM_IDE_PROTOCOL
//
typedef struct _PLATFORM_IDE_PROTOCOL {
    UINT8       Revision;
    BOOLEAN     MasterSlaveEnumeration;
    BOOLEAN     IdeBusMasterSupport; 
    BOOLEAN     AtapiBusMasterSupport; 
    BOOLEAN     AcousticManagementSupport; 
    BOOLEAN     IdePowerManagementSupport; 
    INT16       StandbyTimeout; 
    BOOLEAN     AdvPowerManagementSupport; 
    UINT8       AdvPowerManagementLevel; 
    BOOLEAN     PowerupInStandbySupport;
    BOOLEAN     PowerupInStandbyMode; 
    BOOLEAN     IdePwrManagementInterfaceSupport; 
    BOOLEAN     HostProtectedAreaSupport; 
    BOOLEAN     IdeHPSupport;
    BOOLEAN     EfiIdeProtocol; 
    BOOLEAN     AhciCompatibleMode; 
    BOOLEAN     SBIdeSupport;
    BOOLEAN     HddPowerLossInS3; 
    BOOLEAN     DiPMSupport;
    BOOLEAN     DisableSoftSetPrev;
    BOOLEAN     ForceHddPasswordPrompt;
    EFI_GUID    gIdeControllerProtocolGuid;
    EFI_GUID    gComponentNameProtocolGuid;
    UINT32      S3BusyClearTimeout;
    UINT32      DmaAtaCompleteCommandTimeout;
    UINT32      DmaAtaPiCompleteCommandTimeout;
    UINT32      AtaPiResetCommandTimeout;
    UINT32      AtaPiBusyClearTimeout;
    UINT32      PoweonBusyClearTimeout;
} PLATFORM_IDE_PROTOCOL;

/****** DO NOT WRITE BELOW THIS LINE *******/
#ifdef __cplusplus
}
#endif
#endif
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
