//**********************************************************************
//**********************************************************************
//**                                                                  **
//**        (C)Copyright 1985-2009, American Megatrends, Inc.         **
//**                                                                  **
//**                       All Rights Reserved.                       **
//**                                                                  **
//**         5555 Oakbrook Pkwy, Suite 200, Norcross, GA 30093        **
//**                                                                  **
//**                       Phone: (770)-246-8600                      **
//**                                                                  **
//**********************************************************************
//**********************************************************************
//**********************************************************************
//
// $Header: /Alaska/BIN/Board/OemDxe.c 32    11/01/11 4:29p Artems $
//
// $Revision: 32 $
//
// $Date: 11/01/11 4:29p $
//
//*****************************************************************************
// Revision History
// ----------------
// $Log: /Alaska/BIN/Board/OemDxe.c $
// 
// 32    11/01/11 4:29p Artems
// EIP 71380: CSM opt-out feature support. Legacy OpROM policy moved into
// CSM opt-out module
// 
// 31    7/21/11 8:53a Felixp
// Bug fix in the GOP detection logic introduced by previous check in
// (EIP64103)
// 
// 30    7/19/11 4:59p Felixp
// [TAG]  		EIP64103
// [Category]  	New Feature
// [Description]  	Setup control to enable/disable execution of the Legacy
// Option ROM for video devices 
// is extended to support "Enable if no GOP on the handle" option.
// [Files]  		Board.sdl
// Oem.sd
// Oem.uni
// OemDxe.c
// 
// 29    7/13/11 2:23p Felixp
// [TAG]  		EIP64103
// [Category]  	New Feature
// [Description]  	Setup control to enable/disable execution of the Legacy
// Option ROM for video devices is implemented.
// [Files]  		Board.sdl
// Oem.sd
// Oem.uni
// OemDxe.c
// 
// 28    3/10/11 5:58a Rajeshms
// [TAG] - EIP 39307
// [Category]- BUG FIX
// [Severity]- Normal
// [Symptom] - Enter DOS no screen when legacy serial redirection enable
// with option rom message display option is set to " Keep current" in
// setup.
// [RootCause] - Actual INT 10h handler was not replaced after dispatching
// option rom. Legacy console redirection driver INT10h was replaced
// instead of actual handler when option rom message display option was
// set to " Keep current".
// [Solution] - Legacy Console redirection is disabled after its handler
// is replaced in INT 10h place by the dummy handler so that actual INT10h
// handler is replaced by Legacy Console redirection driver. To Support
// redirection for ISA oprom's , enable and disable of legacy console
// redirection has been moved to CsmOpRom.c from OemDxe.c.
// [Files] - CsmOpRom.c, OemDxe.c
// 
// 27    3/08/11 1:52p Olegi
// [TAG]  		EIP54455
// [Category]  	Improvement
// [Description]  	In some cases signaling the Option ROM execution event
// is not in sync between PreprocessOprom and PostProcessOprom.
// [Files]  		oemdxe.c
// 
// 26    2/07/11 4:44p Artems
// EIP 53374: Replaced tabs with spaces
// 
// 25    12/17/10 12:57p Davidd
// [TAG]        EIP47366
// [Category]   Improvement
// [Description]    Preserve Bios password when CMOS is bad
// [Files]          OemDxe.c
// OemPort.c
// 
// 24    10/06/10 2:03p Felixp
// 
// 22    3/01/10 3:42p Olegi
// Modified Pre/PostProcessOprom functions: added new argument that points
// to the ROM to be executed. This is needed for cases where PciIo is NULL
// (User ROMs). EIP34085.
// 
// 21    11/25/09 5:51p Felixp
// 
// 19    11/17/09 10:12p Olegi
// Fix in CsmPlatform_PostProcessOpRom related to the previous check-in.
// 
// 18    11/17/09 3:11p Olegi
// CSM specific call that would let OEM function recieve control before
// OpROM execution. EIP#20571.
// 
// 17    6/25/09 6:09p Robert
// Updated Comments and function headers
//
// 15    12/17/07 3:43p Felixp
// 1. Signal protocol event before and after OpROM execution
// 2. Setup option to enable/disable mass storage OpROM execution added
//
// 14    8/31/07 10:10a Rameshraju
// Legacy Console Redirection enabled only when the option rom is
// dispatched.
//
// 13    4/19/07 10:03a Olegi
// CSMSREDIR_SUPPORT token is replaced with LEGACYSREDIR_SUPPORT
//
// 12    17/04/07 11:05a Anandakrishnanl
// Reverting Back to Version9
//
// 9     3/28/07 10:39a Olegi
// Legacy Serial Redirection Support added
//
// 8     3/28/07 10:22a Yakovlevs
// Code cleanup
//
// 6     10/24/06 12:22p Felixp
// Cosmetic changes
//
// 5     8/30/06 2:59p Fredericko
// -Fix problem with CD-ROM not showing as a boot option in setup
//
// 4     7/25/06 7:07p Ambikas
//
// 3     7/17/06 7:20p Felixp
// #if CSM_SUPPORT added so that module builds without CSM
//
// 1     6/13/06 4:54p Sivagarn
// Initial Checkin
//
//
//*****************************************************************************


//<AMI_FHDR_START>
//----------------------------------------------------------------------------
//
// Name: OEMDXE.C
//
// Description:
//  This file contains code for Template OEM initialization in the DXE stage
//
//----------------------------------------------------------------------------
//<AMI_FHDR_END>

//============================================================================
// Module specific Includes
#include "Efi.h"
#include "token.h"
#include <AmiLib.h>
#include <AmiDxeLib.h>
#include <AmiLoadCsmPolicy.h>
//============================================================================
// Consumed Protocols
#include <Protocol\PciIo.h>
#include <Setup.h>
#include <Protocol\Cpu.h>
#include <Protocol\PciRootBridgeIo.h>
#include <Pci.h>
#if CSM_SUPPORT
#include <Protocol\CsmPlatform.h>
#endif
#if CLEAR_NVRAM_IF_CMOS_BAD
#include <hob.h>
#include <Protocol\SimpleTextIn.h>
#endif      // CLEAR_NVRAM_IF_CMOS_BAD
#include <Protocol/ConsoleControl.h>
#include <Protocol/GraphicsOutput.h>
#include <Protocol/DevicePath.h>

//============================================================================
// Constant definitions
#define PCIE_CFG_ADDR(bus,dev,func,reg) \
  ((VOID*) (PCIEX_BASE_ADDRESS + ((bus) << 20) + ((dev) << 15) + ((func) << 12) + reg))

//============================================================================
// GUID Definitions

//============================================================================
//  Variable Declaration
SETUP_DATA *SetupData = NULL;
EFI_GUID SetupGuid = SETUP_GUID;
EFI_GUID OpromStartEndProtocolGuid = OPROM_START_END_PROTOCOL_GUID;

typedef struct {
    UINT8   Device;
    UINT8   Function;
} PCI_BRG_INFO;

//============================================================================
// Function Prototypes
#if CSM_SUPPORT

#if !defined(CSM_VERSION_BUILD) || (CSM_VERSION_BUILD < 72)
EFI_STATUS
CsmPlatform_PreProcessOpRom (
  IN CSM_PLATFORM_PROTOCOL *This,
  IN EFI_PCI_IO_PROTOCOL *PciIo
  );

EFI_STATUS
CsmPlatform_PostProcessOpRom (
  IN CSM_PLATFORM_PROTOCOL *This,
  IN EFI_PCI_IO_PROTOCOL *PciIo
  );
#else
EFI_STATUS
CsmPlatform_PreProcessOpRom (
  IN CSM_PLATFORM_PROTOCOL *This,
  IN EFI_PCI_IO_PROTOCOL *PciIo,
  IN VOID **RomImage
  );

EFI_STATUS
CsmPlatform_PostProcessOpRom (
  IN CSM_PLATFORM_PROTOCOL *This,
  IN EFI_PCI_IO_PROTOCOL *PciIo,
  IN VOID **RomImage
  );
#endif

EFI_STATUS
CsmPlatform_GetAtapiDeviceType (
  IN CSM_PLATFORM_PROTOCOL *This,
  IN struct _ATAPI_IDENTIFY *IdentifyDriveData,
  OUT UINT16 *DevType
);

CSM_PLATFORM_PROTOCOL CsmPlatformProtocol =
  { CsmPlatform_PreProcessOpRom,
    CsmPlatform_PostProcessOpRom,
    CsmPlatform_GetAtapiDeviceType
  };

EFI_STATUS InstallCsmPlatformProtocol();
#endif


//============================================================================
// Function Definitions

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   SignalProtocolEvent
//
// Description: 
//  Internal function that installs/uninstall protocol with a specified GUID.
//  Such protocols can be used as event signaling mechanism.
//
// Input:       
//  IN EFI_GUID *ProtocolGuid - Pointer to the protocol GUID
//  IN VOID *Interface - Pointer to the interface that allows to pass data
//  pointer to the event consumer.
//
// Output:      
//  None
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID SignalProtocolEvent(IN EFI_GUID *ProtocolGuid, IN VOID *Interface){
    EFI_HANDLE  Handle = NULL;
    pBS->InstallProtocolInterface (
        &Handle, ProtocolGuid, EFI_NATIVE_INTERFACE, Interface
    );
    pBS->UninstallProtocolInterface (
        Handle, ProtocolGuid, Interface
    );
}

#if CLEAR_NVRAM_IF_CMOS_BAD

#define AMITSESETUP_GUID \
 { 0xc811fa38, 0x42c8, 0x4579, 0xa9, 0xbb, 0x60, 0xe9, 0x4e, 0xdd, 0xfb, 0x34 }

#define PASSWORD_HOB_GUID \
 { 0x79ce097a, 0x91aa, 0x41ff, 0xb3, 0xa8, 0x53, 0x45, 0x59, 0xb3, 0x0d, 0xb1 }

typedef struct {
    EFI_HOB_GUID_TYPE   EfiHobGuidType;
    AMITSESETUP         AmiTseData;
} 
PASSWORD_HOB;

//<AMI_PHDR_START>
//----------------------------------------------------------------------
// Procedure:   RestoreSetupPassword
//
// Description: Restore previous Password
//
// Input:       IN EFI_EVENT  Event
//              IN VOID       *Context
//
// Output:      NONE
//
// Returns:     NONE
//
//----------------------------------------------------------------------
//<AMI_PHDR_END>
VOID
RestoreSetupPassword (
    IN EFI_EVENT  Event,
    IN VOID       *Context
)
{
    EFI_STATUS      Status;
    EFI_GUID        HobListGuid = HOB_LIST_GUID;
    EFI_GUID        PwdHobGuid = PASSWORD_HOB_GUID;
    EFI_GUID        AmiTseSetupGuid = AMITSESETUP_GUID;
    VOID            *pHobList;
    UINTN           VariableSize = sizeof(AMITSESETUP);

    pHobList = GetEfiConfigurationTable(pST, &HobListGuid);

    if (pHobList != NULL) {
        Status = FindNextHobByGuid(&PwdHobGuid, &pHobList);
    }

    if (Status == EFI_SUCCESS) {
        pRS->SetVariable(
                        L"AMITSESetup",
                        &AmiTseSetupGuid,
                        EFI_VARIABLE_RUNTIME_ACCESS | EFI_VARIABLE_BOOTSERVICE_ACCESS | EFI_VARIABLE_NON_VOLATILE,
                        VariableSize,
                        &((PASSWORD_HOB*)pHobList)->AmiTseData);
    }

    pBS->CloseEvent(Event);
}
#endif      // CLEAR_NVRAM_IF_CMOS_BAD


//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   OEMDXE_Init
//
// Description: 
//  This function is the entry point for this DXE. This function programs 
//  OEM defined values in the DXE stage
//
// Input:       
//  IN EFI_HANDLE ImageHandle - Image handle
//  IN EFI_SYSTEM_TABLE *SystemTable - Pointer to the system table
//
// Output:      
//  EFI_SUCCESS
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS
OEMDXE_Init (
IN EFI_HANDLE           ImageHandle,
IN EFI_SYSTEM_TABLE   *SystemTable )
{
    UINTN       SetupSize = 0;
#if CLEAR_NVRAM_IF_CMOS_BAD
    EFI_EVENT   HobPwdEvent;
    VOID        *Registration;
    EFI_GUID    gSimpleInGuid = EFI_SIMPLE_TEXT_INPUT_PROTOCOL_GUID;
#endif      // CLEAR_NVRAM_IF_CMOS_BAD

    InitAmiLib(ImageHandle,SystemTable);
    GetEfiVariable(L"Setup", &SetupGuid, NULL, &SetupSize, &SetupData);

#if CLEAR_NVRAM_IF_CMOS_BAD
    HobPwdEvent = NULL;

    //
    // Create event for SimpleInProtocol Callback notification
    //
    pBS->CreateEvent (
                EVT_NOTIFY_SIGNAL,
                TPL_NOTIFY,
                RestoreSetupPassword,
                NULL,
                &HobPwdEvent
                );

    pBS->RegisterProtocolNotify (&gSimpleInGuid, HobPwdEvent, &Registration);
#endif      // CLEAR_NVRAM_IF_CMOS_BAD

#if CSM_SUPPORT
    InstallCsmPlatformProtocol();
#endif
    return EFI_SUCCESS;
}

#if CSM_SUPPORT

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   CsmPlatform_PreProcessOpRom
//
// Description: 
//  This function is the member function PreProcessOpRom of the CsmPlatformProtocol.
//
// Input:       
//  CSM_PLATFORM_PROTOCOL *This - Pointer to this instance of the CSM_PLATFORM_PROTOCOL
//  EFI_PCI_IO_PROTOCOL *PciIo - OPTIONAL - pointer to the instance of the PciIo Protocol
//
// Output:  
//  EFI_SUCCESS - run the option rom for this device
//  EFI_ABORTED - code determined to not run Oprom for this device
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
#if defined(CSM_VERSION_BUILD) && (CSM_VERSION_BUILD > 71)
EFI_STATUS 
CsmPlatform_PreProcessOpRom (
    IN CSM_PLATFORM_PROTOCOL *This,
    IN EFI_PCI_IO_PROTOCOL *PciIo,
    IN VOID **RomImage
)
#else
EFI_STATUS 
CsmPlatform_PreProcessOpRom (
    IN CSM_PLATFORM_PROTOCOL *This,
    IN EFI_PCI_IO_PROTOCOL *PciIo
)
#endif
{
    CSM_PLATFORM_POLICY_DATA CsmOpromPolicyData;
#if defined(CSM_VERSION_BUILD) && (CSM_VERSION_BUILD > 71)
    VOID* RomLocation = *RomImage;

    if (RomImage != NULL){
        if (((LEGACY_OPT_ROM_HEADER*)RomLocation)->Signature == 0xAA55) {
            //
            // TODO:  Add platform pre-OpROM function here for that ROM image  
            //        is no hardware associated.
        }
    }
#endif
    // See if any callback function wishes to cancel this OpROM execution
    CsmOpromPolicyData.PciIo = PciIo;
    CsmOpromPolicyData.ExecuteThisRom = TRUE;

    SignalProtocolEvent(&OpromStartEndProtocolGuid, &CsmOpromPolicyData);

    return ( CsmOpromPolicyData.ExecuteThisRom == FALSE) ? EFI_ABORTED : EFI_SUCCESS;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   CsmPlatform_PostProcessOpRom
//
// Description: 
//  This function is member function PostProcessOpRom of the CsmPlatformProtocol.
//
// Input:   
//  CSM_PLATFORM_PROTOCOL *This - Pointer to this instance of the CSM_PLATFORM_PROTOCOL
//  EFI_PCI_IO_PROTOCOL *PciIo - OPTIONAL - pointer to the instance of the PciIo Protocol
//
// Output:      
//  EFI_STATUS
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

#if defined(CSM_VERSION_BUILD) && (CSM_VERSION_BUILD > 71)
EFI_STATUS
CsmPlatform_PostProcessOpRom (
    IN CSM_PLATFORM_PROTOCOL *This,
    IN EFI_PCI_IO_PROTOCOL *PciIo,
    IN VOID **RomImage
    )
#else
EFI_STATUS 
CsmPlatform_PostProcessOpRom (
    IN CSM_PLATFORM_PROTOCOL *This,
    IN EFI_PCI_IO_PROTOCOL *PciIo
    )
#endif
{   

    // signal the OpromStartEndProtocolGuid event
    SignalProtocolEvent(&OpromStartEndProtocolGuid, NULL);
    return EFI_SUCCESS;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   InstallCsmPlatformProtocol
//
// Description: 
//  This function is the entry point for the OEM DXE portion of the Board 
//  template driver
//
// Input:       
//  None
//
// Output:  
//  EFI_STATUS value determined by the call to InstallProtocolInterface
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS InstallCsmPlatformProtocol()
{
  EFI_HANDLE Handle = 0;

  return pBS->InstallProtocolInterface (
                  &Handle, &gCsmPlatformProtocolGuid,
                EFI_NATIVE_INTERFACE, &CsmPlatformProtocol
    );
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   CsmPlatform_GetAtapiDeviceType
//
// Description: 
//  This function is the member function GetAtapiDeviceType of the 
//  CsmPlatformProtocol.  Until ported, this function returns EFI_UNSUPPORTED
//
// Input:       
//  IN CSM_PLATFORM_PROTOCOL *This - pointer to the instance of the CSM Platform Protocol
//  IN struct _ATAPI_IDENTIFY *IdentifyDriveData - pointer to Atapi Drive Data structure
//  OUT UINT16 *DevType - type of the device the IdentifyDeviceData is for
//
// Output:  
//  EFI_UNSUPPORTED
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS
CsmPlatform_GetAtapiDeviceType (
    IN CSM_PLATFORM_PROTOCOL *This,
    IN struct _ATAPI_IDENTIFY *IdentifyDriveData,
    OUT UINT16 *DevType
)
{
  return EFI_UNSUPPORTED;
}
#endif
//**********************************************************************
//**********************************************************************
//**                                                                  **
//**        (C)Copyright 1985-2009, American Megatrends, Inc.         **
//**                                                                  **
//**                       All Rights Reserved.                       **
//**                                                                  **
//**         5555 Oakbrook Pkwy, Suite 200, Norcross, GA 30093        **
//**                                                                  **
//**                       Phone: (770)-246-8600                      **
//**                                                                  **
//**********************************************************************
//**********************************************************************
