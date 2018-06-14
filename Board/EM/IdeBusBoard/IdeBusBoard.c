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
// $Header: /Alaska/BIN/Core/Modules/IdeBus/IdeBusBoard.c 2     9/27/11 2:50a Rajeshms $
//
// $Revision: 2 $
//
// $Date: 9/27/11 2:50a $
//*************************************************************************
// Revision History
// ----------------
// $Log: /Alaska/BIN/Core/Modules/IdeBus/IdeBusBoard.c $
// 
// 2     9/27/11 2:50a Rajeshms
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
// Name: IdeBusBoard.c
//
// Description: Installs PlatformIdeProtocol Interface and Initializes it.
//  
//<AMI_FHDR_END>
//*************************************************************************

#include <AmiDxeLib.h>
#include <EFI.h>
#include <Dxe.h>
#include <Token.h>
#include <Protocol\IdeBusBoard.h>

#include <Protocol\PciIo.h>
#include <Protocol\PIDEController.h>
#include <Protocol\IdeControllerInit.h>
#include <Protocol\ComponentName.h>

EFI_GUID PlatformIdeProtocolGuid = PLATFORM_IDE_PROTOCOL_GUID;

PLATFORM_IDE_PROTOCOL PlatformIdeProtocol= {

//<AMI_SHDR_START>
//----------------------------------------------------------------------------
// Name:    Revision
//
// Description:	Variable contains the Revision of PLATFORM_IDE_PROTOCOL.
//
// Notes: UINT8
//
//----------------------------------------------------------------------------
//<AMI_SHDR_END>
PLATFORM_IDE_PROTOCOL_REVISION,

//<AMI_SHDR_START>
//----------------------------------------------------------------------------
// Name:    MasterSlaveEnumeration
//
// Description:	Variable to replace MASTER_SLAVE_ENUMERATION token.
//
// Notes: BOOLEAN
//
//----------------------------------------------------------------------------
//<AMI_SHDR_END>
#ifdef MASTER_SLAVE_ENUMERATION
    MASTER_SLAVE_ENUMERATION
#else
    0
#endif
    ,
//<AMI_SHDR_START>
//----------------------------------------------------------------------------
// Name:    IdeBusMasterSupport
//
// Description:	Variable to replace IDEBUSMASTER_SUPPORT token.
//
// Notes: BOOLEAN
//
//----------------------------------------------------------------------------
//<AMI_SHDR_END>

#ifdef IDEBUSMASTER_SUPPORT
    IDEBUSMASTER_SUPPORT
#else
    0
#endif
    ,

//<AMI_SHDR_START>
//----------------------------------------------------------------------------
// Name:    AtapiBusMasterSupport
//
// Description:	Variable to replace ATAPI_BUSMASTER_SUPPORT token.
//
// Notes: BOOLEAN
//
//----------------------------------------------------------------------------
//<AMI_SHDR_END>
 
#ifdef ATAPI_BUSMASTER_SUPPORT
    ATAPI_BUSMASTER_SUPPORT
#else
    0
#endif
    ,

//<AMI_SHDR_START>
//----------------------------------------------------------------------------
// Name:    AcousticManagementSupport
//
// Description:	Variable to replace ACOUSTIC_MANAGEMENT_SUPPORT token.
//
// Notes: BOOLEAN
//
//----------------------------------------------------------------------------
//<AMI_SHDR_END>

#ifdef ACOUSTIC_MANAGEMENT_SUPPORT
    ACOUSTIC_MANAGEMENT_SUPPORT
#else
    0
#endif
    ,

//<AMI_SHDR_START>
//----------------------------------------------------------------------------
// Name:    IdePowerManagementSupport
//
// Description:	Variable to replace IDE_POWER_MANAGEMENT_SUPPORT token.
//
// Notes: BOOLEAN
//
//----------------------------------------------------------------------------
//<AMI_SHDR_END>

#ifdef IDE_POWER_MANAGEMENT_SUPPORT
    IDE_POWER_MANAGEMENT_SUPPORT
#else
    0
#endif
    ,

//<AMI_SHDR_START>
//----------------------------------------------------------------------------
// Name:    StandbyTimeout
//
// Description:	Variable to replace STANDBY_TIMEOUT token.
//
// Notes: INT16
//
//----------------------------------------------------------------------------
//<AMI_SHDR_END>

#ifdef STANDBY_TIMEOUT
    STANDBY_TIMEOUT
#else
    0
#endif
    ,

//<AMI_SHDR_START>
//----------------------------------------------------------------------------
// Name:    AdvPowerManagementSupport
//
// Description:	Variable to replace ADVANCED_POWER_MANAGEMENT_SUPPORT token.
//
// Notes: BOOLEAN
//
//----------------------------------------------------------------------------
//<AMI_SHDR_END>
 
#ifdef ADVANCED_POWER_MANAGEMENT_SUPPORT
    ADVANCED_POWER_MANAGEMENT_SUPPORT
#else
    0
#endif
    ,

//<AMI_SHDR_START>
//----------------------------------------------------------------------------
// Name:    AdvPowerManagementLevel
//
// Description:	Variable to replace ADVANCED_POWER_MANAGEMENT_LEVEL token.
//
// Notes: UINT8
//
//----------------------------------------------------------------------------
//<AMI_SHDR_END>
 
#ifdef ADVANCED_POWER_MANAGEMENT_LEVEL
    ADVANCED_POWER_MANAGEMENT_LEVEL
#else
    0
#endif
    ,

//<AMI_SHDR_START>
//----------------------------------------------------------------------------
// Name:    PowerupInStandbySupport
//
// Description:	Variable to replace POWERUP_IN_STANDBY_SUPPORT token.
//
// Notes: BOOLEAN
//
//----------------------------------------------------------------------------
//<AMI_SHDR_END>

#ifdef POWERUP_IN_STANDBY_SUPPORT
    POWERUP_IN_STANDBY_SUPPORT
#else
    0
#endif
    ,

//<AMI_SHDR_START>
//----------------------------------------------------------------------------
// Name:    PowerupInStandbyMode
//
// Description:	Variable to replace POWERUP_IN_STANDBY_MODE token.
//
// Notes: BOOLEAN
//
//----------------------------------------------------------------------------
//<AMI_SHDR_END>

#ifdef POWERUP_IN_STANDBY_MODE
    POWERUP_IN_STANDBY_MODE
#else
    0
#endif
    ,

//<AMI_SHDR_START>
//----------------------------------------------------------------------------
// Name:    IdePwrManagementInterfaceSupport
//
// Description:	Variable to replace IDE_POWER_MANAGEMENT_INTERFACE_SUPPORT token.
//
// Notes: BOOLEAN
//
//----------------------------------------------------------------------------
//<AMI_SHDR_END>

#ifdef IDE_POWER_MANAGEMENT_INTERFACE_SUPPORT
    IDE_POWER_MANAGEMENT_INTERFACE_SUPPORT
#else
    0
#endif
    ,

//<AMI_SHDR_START>
//----------------------------------------------------------------------------
// Name:    HostProtectedAreaSupport
//
// Description:	Variable to replace HOST_PROTECTED_AREA_SUPPORT token.
//
// Notes: BOOLEAN
//
//----------------------------------------------------------------------------
//<AMI_SHDR_END>

#ifdef HOST_PROTECTED_AREA_SUPPORT
    HOST_PROTECTED_AREA_SUPPORT
#else
    0
#endif
    ,

//<AMI_SHDR_START>
//----------------------------------------------------------------------------
// Name:    IdeHPSupport
//
// Description:	Variable to replace IDE_HP_SUPPORT token.
//
// Notes: BOOLEAN
//
//----------------------------------------------------------------------------
//<AMI_SHDR_END>
 
#ifdef IDE_HP_SUPPORT
    IDE_HP_SUPPORT
#else
    0
#endif
    ,

//<AMI_SHDR_START>
//----------------------------------------------------------------------------
// Name:    EfiIdeProtocol
//
// Description:	Variable to replace EFI_IDE_PROTOCOL token.
//
// Notes: BOOLEAN
//
//----------------------------------------------------------------------------
//<AMI_SHDR_END>

#ifdef EFI_IDE_PROTOCOL
    EFI_IDE_PROTOCOL
#else
    0
#endif
    ,

//<AMI_SHDR_START>
//----------------------------------------------------------------------------
// Name:    AhciCompatibleMode
//
// Description:	Variable to replace AHCI_COMPATIBLE_MODE token.
//
// Notes: BOOLEAN
//
//----------------------------------------------------------------------------
//<AMI_SHDR_END>
 
#ifdef AHCI_COMPATIBLE_MODE
    AHCI_COMPATIBLE_MODE
#else
    0
#endif
    ,
//<AMI_SHDR_START>
//----------------------------------------------------------------------------
// Name:    SBIdeSupport
//
// Description:	Variable to replace SBIDE_SUPPORT token.
//
// Notes: const BOOLEAN
//
//----------------------------------------------------------------------------
//<AMI_SHDR_END>
 
#ifdef SBIDE_SUPPORT
    SBIDE_SUPPORT
#else
    0
#endif
    ,

//<AMI_SHDR_START>
//----------------------------------------------------------------------------
// Name:    HddPowerLossInS3
//
// Description:	Variable to replace HDD_POWER_LOSS_IN_S3 token.
//
// Notes: const BOOLEAN
//
//----------------------------------------------------------------------------
//<AMI_SHDR_END>
 
#ifdef HDD_POWER_LOSS_IN_S3
    HDD_POWER_LOSS_IN_S3
#else
    0
#endif
    ,

//<AMI_SHDR_START>
//----------------------------------------------------------------------------
// Name:    DiPMSupport
//
// Description:	Variable to replace DiPM_SUPPORT token.
//
// Notes: BOOLEAN
//
//----------------------------------------------------------------------------
//<AMI_SHDR_END>

#ifdef DiPM_SUPPORT
    DiPM_SUPPORT
#else
    0
#endif
    ,

//<AMI_SHDR_START>
//----------------------------------------------------------------------------
// Name:    DisableSoftSetPrev
//
// Description:	Variable to replace DISABLE_SOFT_SET_PREV token.
//
// Notes: BOOLEAN
//
//----------------------------------------------------------------------------
//<AMI_SHDR_END>

#ifdef DISABLE_SOFT_SET_PREV
    DISABLE_SOFT_SET_PREV
#else
    0
#endif
    ,

//<AMI_SHDR_START>
//----------------------------------------------------------------------------
// Name:    ForceHddPasswordPrompt
//
// Description:	Variable to replace FORCE_HDD_PASSWORD_PROMPT token.
//
// Notes: BOOLEAN
//
//----------------------------------------------------------------------------
//<AMI_SHDR_END>

#ifdef FORCE_HDD_PASSWORD_PROMPT
    FORCE_HDD_PASSWORD_PROMPT
#else
    0
#endif
    ,

//<AMI_SHDR_START>
//----------------------------------------------------------------------------
// Name:    gIdeControllerProtocolGuid
//
// Description:	Variable contains Ide Controller Protocol GUID.
//
// Notes: const EFI_GUID
//
//----------------------------------------------------------------------------
//<AMI_SHDR_END>

#if defined EFI_IDE_PROTOCOL && EFI_IDE_PROTOCOL == 1
    EFI_IDE_CONTROLLER_INIT_PROTOCOL_GUID
#else
    IDE_CONTROLLER_PROTOCOL_GUID
#endif
   ,

//<AMI_SHDR_START>
//----------------------------------------------------------------------------
// Name:    gComponentNameProtocolGuid
//
// Description:	Variable contains Component Name Protocol GUID.
//
// Notes: const EFI_GUID
//
//----------------------------------------------------------------------------
//<AMI_SHDR_END>

#ifdef EFI_COMPONENT_NAME2_PROTOCOL_GUID
    EFI_COMPONENT_NAME2_PROTOCOL_GUID
#else
    EFI_COMPONENT_NAME_PROTOCOL_GUID
#endif
    ,

//<AMI_SHDR_START>
//----------------------------------------------------------------------------
// Name:    S3BusyClearTimeout
//
// Description:	Variable to replace S3_BUSY_CLEAR_TIMEOUT token.
//
// Notes: const EFI_GUID
//
//----------------------------------------------------------------------------
//<AMI_SHDR_END>

#ifdef S3_BUSY_CLEAR_TIMEOUT
    S3_BUSY_CLEAR_TIMEOUT
#else
    10000
#endif
    ,

//<AMI_SHDR_START>
//----------------------------------------------------------------------------
// Name:    DmaAtaCompleteCommandTimeout
//
// Description:	Variable to replace DMA_ATA_COMMAND_COMPLETE_TIMEOUT token.
//
// Notes: const EFI_GUID
//
//----------------------------------------------------------------------------
//<AMI_SHDR_END>

#ifdef DMA_ATA_COMMAND_COMPLETE_TIMEOUT
    DMA_ATA_COMMAND_COMPLETE_TIMEOUT
#else
    5000
#endif
    ,

//<AMI_SHDR_START>
//----------------------------------------------------------------------------
// Name:    DmaAtaPiCompleteCommandTimeout
//
// Description:	Variable to replace DMA_ATAPI_COMMAND_COMPLETE_TIMEOUT token.
//
// Notes: const EFI_GUID
//
//----------------------------------------------------------------------------
//<AMI_SHDR_END>

#ifdef DMA_ATAPI_COMMAND_COMPLETE_TIMEOUT
    DMA_ATAPI_COMMAND_COMPLETE_TIMEOUT
#else
    16000
#endif
    ,

//<AMI_SHDR_START>
//----------------------------------------------------------------------------
// Name:    AtaPiResetCommandTimeout
//
// Description:	Variable to replace ATAPI_RESET_COMMAND_TIMEOUT token.
//
// Notes: const EFI_GUID
//
//----------------------------------------------------------------------------
//<AMI_SHDR_END>

#ifdef ATAPI_RESET_COMMAND_TIMEOUT
    ATAPI_RESET_COMMAND_TIMEOUT
#else
    5000
#endif
    ,

//<AMI_SHDR_START>
//----------------------------------------------------------------------------
// Name:    AtaPiBusyClearTimeout
//
// Description:	Variable to replace ATAPI_BUSY_CLEAR_TIMEOUT token.
//
// Notes: const EFI_GUID
//
//----------------------------------------------------------------------------
//<AMI_SHDR_END>

#ifdef ATAPI_BUSY_CLEAR_TIMEOUT
    ATAPI_BUSY_CLEAR_TIMEOUT
#else
    16000
#endif
    ,

//<AMI_SHDR_START>
//----------------------------------------------------------------------------
// Name:    PoweonBusyClearTimeout
//
// Description:	Variable to replace DMA_ATA_COMMAND_COMPLETE_TIMEOUT token.
//
// Notes: const EFI_GUID
//
//----------------------------------------------------------------------------
//<AMI_SHDR_END>

#ifdef POWERON_BUSY_CLEAR_TIMEOUT
    POWERON_BUSY_CLEAR_TIMEOUT
#else
    10000
#endif
};

//<AMI_PHDR_START>
//---------------------------------------------------------------------------
//
// Procedure:	IdeBusBoardEntryPoint
//
// Description:	Installs PlatformIdeProtocol Interface
//
// Input:
//  IN EFI_HANDLE        ImageHandle,
//  IN EFI_SYSTEM_TABLE  *SystemTable
//
// Output:
//  EFI_STATUS
//
// Modified:
//
// Referrals: InitAmiLib, InstallProtocolInterface
//
// Notes:
//  Here is the control flow of this function:
//  1. Initialize Ami Lib.
//  2. Install PlatformIdeProtocol.
//  3. Return EFI_SUCCESS.
//---------------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS
IdeBusBoardEntryPoint (
IN EFI_HANDLE     ImageHandle,
IN EFI_SYSTEM_TABLE   *SystemTable )
{
    EFI_STATUS Status;
    InitAmiLib(ImageHandle,SystemTable);
    Status = pBS->InstallProtocolInterface(\
                    &ImageHandle,\
                    &PlatformIdeProtocolGuid,\
                    EFI_NATIVE_INTERFACE,\
                    &PlatformIdeProtocol\
                        );
    return Status;
}

#ifndef EFI_COMPONENT_NAME2_PROTOCOL_GUID //old Core Support
//*************************************************************************
//<AMI_PHDR_START>
//
// Name: LanguageCodesEqual
//
// Description:	
//  BOOLEAN LanguageCodesEqual(CONST CHAR8* LangCode1, CONST CHAR8* LangCode2) 
// compares two language codes and returns TRUE if they are equal.
//
// Input:
//  CONST CHAR8* LangCode1 - first language code
//  CONST CHAR8* LangCode2 - second language code
//
// Output:
//  BOOLEAN TRUE - the language codes are equal
//          FALSE - the language codes are not equal
//
//<AMI_PHDR_END>
//*************************************************************************
BOOLEAN LanguageCodesEqual(
    CONST CHAR8* LangCode1, CONST CHAR8* LangCode2
){
    return    LangCode1[0]==LangCode2[0] 
           && LangCode1[1]==LangCode2[1]
           && LangCode1[2]==LangCode2[2];
}
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
