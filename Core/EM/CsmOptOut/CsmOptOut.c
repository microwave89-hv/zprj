//**********************************************************************
//**********************************************************************
//**                                                                  **
//**        (C)Copyright 1985-2011, American Megatrends, Inc.         **
//**                                                                  **
//**                       All Rights Reserved.                       **
//**                                                                  **
//**      5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093        **
//**                                                                  **
//**                       Phone: (770)-246-8600                      **
//**                                                                  **
//**********************************************************************
//**********************************************************************

///**********************************************************************
// $Header: /Alaska/SOURCE/Modules/CsmOptOut/CsmOptOut.c 15    11/01/13 9:25p Artems $
//
// $Revision: 15 $
//
// $Date: 11/01/13 9:25p $
//**********************************************************************
// Revision History
// ----------------
// $Log: /Alaska/SOURCE/Modules/CsmOptOut/CsmOptOut.c $
// 
// 15    11/01/13 9:25p Artems
// [TAG]  		EIP126445
// [Category]  	Improvement
// [Description]  	Added UEFI Only option for OpROMS of unknown types
// [Files]  		CsmOptOut.c CsmOptOut.sd CsmOptOut.sdl CsmOptOut.uni
// 
// 14    7/30/12 10:22a Artems
// [TAG]  		EIP N/A
// [Category]  	Bug Fix
// [Severity]  	Minor
// [Symptom]  	Can't disable legacy OpROM execution
// [RootCause]  	CsmOptOut didn't check if anybody already disabled OpROM
// executio
// [Solution]  	Added check of ExecuteThisOpROM flag
// [Files]  		CsmOptOut.c
// 
// 13    6/20/12 6:05p Artems
// [TAG]  		EIP83692
// [Category]  	Improvement
// [Description]  	CSM OptOut setup page grayed out if secure boot is
// enabled
// CSM OptOut PlatformOverride protocol modified to fix SCT bugs
// Removed support for Launch CSM "Auto" option
// [Files]  		CsmOptOut.c CsmOptOut.mak CsmOptOut.sd CsmOptOut.sdl
// CsmOptOut.uni CsmOptOutRuntime.c CsmOptOutSetup.c
// 
// 12    5/21/12 4:46p Artems
// [TAG]  		EIP86097
// [Category]  	Improvement
// [Description]  	Separate control for loading UEFI Oprom Driver
// [Files]  		CsmOptOut.c CsmOptOut.mak PciBus.c
// CsmOptOut.sdl
// 
// 11    5/10/12 5:42p Artems
// [TAG]  		EIP87316
// [Category]  	Improvement
// [Description]  	Revert previous changes, as the improvement were made
// in FixedBootOrder module
// [Files]  		CsmOptOut.c
// 
// 10    4/18/12 4:41p Artems
// [TAG]  		EIP87316
// [Category]  	Improvement
// [Description]  	If legacy boot device is filtered it still appears in
// boot order maintained by FixedBootOrder module
// [Files]  		CsmOptOut.c
// 
// 9     4/05/12 5:14p Artems
// Removed eLinks to ConnectVga and ConnectEverything. Implemented
// Platform specific override protocol instead to control OpROM execution
// sequence
// 
// 8     3/16/12 6:06p Artems
// Fixed bug in CsmOptOutConnectEverything function - not all handles were
// connected
// 
// 7     3/16/12 5:15p Artems
// EIP 82586: CSM must not be loaded if Secure Boot is enabled
// 
// 6     1/27/12 4:34p Artems
// Restored change killed by previous check-in
// 
// 5     1/23/12 7:02p Artems
// Added OpROM handling for PCI devices other than Network, Mass storage
// or Video
// Behavior is same as in previous Core versions
// 
// 3     11/28/11 1:42p Artems
// EIP 75876: Trying to use Setup variable before NVRAM driver is
// available
// 
// 2     11/14/11 3:37p Artems
// Removed unnecessary Trace
// 
// 1     11/12/11 2:57p Artems
// Initial check-in
// 
//**********************************************************************
//<AMI_FHDR_START>
//
// Name:  CsmOptOut.c
//
// Description: This is main file of the CsmOptOut module
//
//<AMI_FHDR_END>
//**********************************************************************


//----------------------------------------------------------------------------

#include <Token.h>
#include <AmiDxeLib.h>
#include <Setup.h>
#include <BootOptions.h>
#include <AmiLoadCsmPolicy.h>
#include <Protocol\CsmPlatform.h>
#include <Protocol\PciIo.h>
#include <Protocol\DriverBinding.h>
#include <Protocol\PlatformDriverOverride.h>
#include <Protocol\BusSpecificDriverOverride.h>
#include <Protocol\GraphicsOutput.h>

#define DEFAULT_HANDLE_BUFFER_SIZE 0x40
typedef struct {
    UINTN TotalSize;
    UINTN CurrentSize;
    EFI_HANDLE *Array;
} HANDLE_BUFFER;

HANDLE_BUFFER ThunkHandles;
HANDLE_BUFFER NonThunkHandles;
static EFI_HANDLE SharedGopHandle = 0;
static BOOLEAN UefiGopDisconnected = FALSE;
static BOOLEAN ProceedToBoot = FALSE;


EFI_STATUS CsmOptOutGetDriver(
	IN EFI_PLATFORM_DRIVER_OVERRIDE_PROTOCOL *This,
	IN EFI_HANDLE ControllerHandle,
	IN OUT EFI_HANDLE *DriverImageHandle
);

EFI_STATUS CsmOptOutGetDriverWorker(
	IN EFI_PLATFORM_DRIVER_OVERRIDE_PROTOCOL *This,
	IN EFI_HANDLE ControllerHandle,
	IN OUT EFI_HANDLE *DriverImageHandle
);

EFI_STATUS CsmOptOutGetDriverPath(
	IN EFI_PLATFORM_DRIVER_OVERRIDE_PROTOCOL *This,
	IN EFI_HANDLE ControllerHandle,
	IN OUT EFI_DEVICE_PATH_PROTOCOL **DriverImagePath
) { return EFI_UNSUPPORTED; }

EFI_STATUS CsmOptOutDriverLoaded(
	IN EFI_PLATFORM_DRIVER_OVERRIDE_PROTOCOL *This,
	IN EFI_HANDLE ControllerHandle,
	IN EFI_DEVICE_PATH_PROTOCOL *DriverImagePath,
	IN EFI_HANDLE DriverImageHandle
) { return EFI_UNSUPPORTED; }

static EFI_PLATFORM_DRIVER_OVERRIDE_PROTOCOL CsmOptOutPlatformDriverOverride = {
    CsmOptOutGetDriver,
    CsmOptOutGetDriverPath,
    CsmOptOutDriverLoaded
};


//----------------------------------------------------------------------------

static EFI_GUID SetupGuid = SETUP_GUID;
static EFI_GUID AmiLoadCsmGuid = AMI_LOAD_CSM_GUID;
static EFI_GUID OpRomStartEndProtocolGuid = OPROM_START_END_PROTOCOL_GUID;
static EFI_GUID AmiCsmThunkProtocolGuid = AMI_CSM_THUNK_PROTOCOL_GUID;
static EFI_GUID AmiOpromPolicyProtocolGuid = AMI_OPROM_POLICY_PROTOCOL_GUID;
extern EFI_GUID BdsAllDriversConnectedProtocolGuid;

UINT8 CurrentCsmState;
VOID *ProcessOpRomRegistration;
VOID *DriverBindingRegistration;
static UINTN CurrentCount = 0;
static EFI_HANDLE CurrentHandle = 0;
static EFI_HANDLE LastReturnedImageHandle = 0;
static BOOLEAN TransactionInProgress;
static BOOLEAN ThunkFirst;

typedef EFI_STATUS (OEM_CHECK_UEFI_OPROM_POLICY) (EFI_HANDLE PciHandle);
extern OEM_CHECK_UEFI_OPROM_POLICY OEM_CHECK_UEFI_OPROM_POLICY_LIST EndOfList;
OEM_CHECK_UEFI_OPROM_POLICY* OemCheckUefiOpromPolicyList[] = { OEM_CHECK_UEFI_OPROM_POLICY_LIST NULL };

EFI_BUS_SPECIFIC_DRIVER_OVERRIDE_PROTOCOL *BusSpecific = NULL;

typedef struct CSM_OPTOUT_SETUP_DATA {
    UINT8  CsmLaunchPolicy;
    UINT8  BootOptionFilter;
    UINT8  PxeOpRom;
    UINT8  MassStorageOpRom;
    UINT8  VideoOpRom;
/*
    We added the following field to preserve functionality existed in previous
    PciBus versions. For PCI devices other than Network,Mass Storage or Video
    value of following field will determine OpROM behavior as before.
*/
    UINT8  OldOpRom;
} CSM_OPTOUT_SETUP_DATA;

CSM_OPTOUT_SETUP_DATA CsmOptOutSetupData = {
    DEFAULT_CSM_LAUNCH_POLICY,
    DEFAULT_BOOT_OPTION_FILTERING_POLICY,
    DEFAULT_PXE_OPROM_POLICY,
    DEFAULT_MASS_STORAGE_OPROM_POLICY,
    DEFAULT_VIDEO_OPROM_POLICY,
    1
};

EFI_STATUS CheckUefiOpRomPolicy(
    IN	AMI_OPROM_POLICY_PROTOCOL *This,
    IN	EFI_HANDLE                PciHandle
);

AMI_OPROM_POLICY_PROTOCOL AmiOpRomPolicyProtocol = {
    CheckUefiOpRomPolicy
};

EFI_STATUS AddHandle(
    IN OUT HANDLE_BUFFER *Target,
    EFI_HANDLE Handle
);

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:    CsmOptOutFilter
// 
// Description:  This function filters available boot options based on Setup
//               control value
//               
//  Input:
// 	IN BOOT_DEVICE *Device - pointer to boot device
//
//  Output:
//  TRUE - boot option will be removed from boot list
//  FALSE - boot option won't be removed from boot list
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
BOOLEAN CsmOptOutFilter( 
    IN BOOT_DEVICE *Device 
)
{
    BOOLEAN Result = FALSE;

    if(CurrentCsmState == 0)    //CSM is disabled on current boot - no need to filter boot options
        return Result;

    switch (CsmOptOutSetupData.BootOptionFilter) {
        case 0: // Enable all boot options
        break;

        case 1: // Disable UEFI boot options
            Result = (Device->BbsEntry == NULL);
        break;

        case 2: // Disable Legacy boot options
            Result = (Device->BbsEntry != NULL);
        break;

        default:
        break;
    }
    return Result;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   GetOpRomPolicy
//
// Description: This function returns OpROM policy for given PCI class of the device
//
// Input:		
//  UINT8 PciClass - class of PCI device to check
//
// Output:
//  UINT8 - policy (0-disable all, 1-disable Legacy, 2-disable UEFI, 3-Legacy before UEFI
//                  4-UEFI before Legacy)
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
UINT8 GetOpRomPolicy(
    IN UINT8 PciClass
)
{
    UINT8 Policy = 0xff;

    switch(PciClass) {
        case PCI_CL_NETWORK:
            Policy = CsmOptOutSetupData.PxeOpRom;
            break;

        case PCI_CL_MASS_STOR:
            Policy = CsmOptOutSetupData.MassStorageOpRom;
            break;

        case PCI_CL_DISPLAY:
            Policy = CsmOptOutSetupData.VideoOpRom;
            break;

        default:
/*
    For PCI devices with PCI class different from Network, Mass Storage or Video
    behavior will be as in previous versions of PciBus driver - UEFI OpROM will
    be executed first or not executed at all
*/
#if OLD_OPROM_POLICY_SUPPORT
            Policy = (CsmOptOutSetupData.OldOpRom == 1) ? 4 : 2;
#else
            Policy = CsmOptOutSetupData.OldOpRom;
#endif
            break;
    }
    return Policy;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   CheckOpRomExecution
//
// Description: This function determines should OpROM be executed
//
// Input:		
//  UINT8 PciClass - class of PCI device to check
//  BOOLEAN UefiOprom - TRUE if verifying UEFI OpROM, FALSE for Legacy OpROM
//
// Output:
//  EFI_SUCCESS - OpROM should be executed
//  EFI_UNSUPPORTED - OpROM should not be executed
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS CheckOpRomExecution(
    IN UINT8 PciClass,
    IN BOOLEAN UefiOprom
)
{
    UINT8 Policy;
    BOOLEAN Result = TRUE;

    Policy = GetOpRomPolicy(PciClass);

    switch(Policy) {
        case 0:     //all OpROMs are disabled
            Result = FALSE;
            break;

        case 1:     //only UEFI OpROMs are enabled
            Result = (UefiOprom) ? TRUE : FALSE;
            break;

        case 2:     //only Legacy OpROMs are enabled
            Result = (UefiOprom) ? FALSE : TRUE;
            break;

        default:    //all OpROMs are enabled
            break;
    }
    return (Result) ? EFI_SUCCESS : EFI_UNSUPPORTED;       
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   DisconnectUefiGop
//
// Description: This function disconnects native UEFI GOP driver before
//              executing legacy video BIOS
//
// Input:		
//  IN EFI_PCI_IO_PROTOCOL *PciIo - instance of PciIo protocol on handle,
//                                  that have to be disconnected
//
// Output:
//  EFI_SUCCESS - driver was disconnected
//  EFI_UNSUPPORTED - driver can't be disconnected
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS DisconnectUefiGop(
    IN EFI_PCI_IO_PROTOCOL *PciIo
)
{
    EFI_STATUS Status;
    EFI_HANDLE *Handles;
    EFI_HANDLE TmpHandle;
    UINTN Count;
    UINTN i;
    VOID *Interface;
    EFI_OPEN_PROTOCOL_INFORMATION_ENTRY *Entries;
    UINT64 Capabilities;
    
/* first find corresponding handle */
    Status = pBS->LocateHandleBuffer(ByProtocol, &gEfiPciIoProtocolGuid, NULL, &Count, &Handles);
    if(EFI_ERROR(Status))
        return Status;

    for(i = 0; i < Count; i++) {
        Status = pBS->HandleProtocol(Handles[i], &gEfiPciIoProtocolGuid, &Interface);
        if(EFI_ERROR(Status))
            continue;

        if((VOID *)PciIo == Interface) {
            SharedGopHandle = Handles[i];
            break;
        }
    }
    pBS->FreePool(Handles);

    if(i == Count)              //no matches
        return EFI_NOT_FOUND;

/* now find child handle where Gop is installed */
    Status = pBS->OpenProtocolInformation(SharedGopHandle, &gEfiPciIoProtocolGuid, &Entries, &Count);
    if(EFI_ERROR(Status))
        return Status;

    for(i = 0; i < Count; i++) {
        if(!(Entries[i].Attributes & EFI_OPEN_PROTOCOL_BY_CHILD_CONTROLLER))
            continue;

        Status = pBS->HandleProtocol(Entries[i].ControllerHandle, &gEfiGraphicsOutputProtocolGuid, &Interface);
        if(!EFI_ERROR(Status)) {
            TmpHandle = Entries[i].AgentHandle;
            break;
        }
    }
    pBS->FreePool(Entries);

    if(i == Count)              //no matches
        return EFI_NOT_FOUND;

/* now check if AgentHandle is our CSM thunk */
    Status = pBS->HandleProtocol(TmpHandle, &AmiCsmThunkProtocolGuid, &Interface);
    if(!EFI_ERROR(Status))
        return EFI_SUCCESS;

    Status = pBS->DisconnectController(SharedGopHandle, NULL, NULL);
/* we have to restore PCI attributes so video BIOS can be executed */
    Status = PciIo->Attributes (PciIo, EfiPciIoAttributeOperationSupported, 
                0, &Capabilities); 
    Status = PciIo->Attributes (PciIo, EfiPciIoAttributeOperationEnable,
                Capabilities & EFI_PCI_DEVICE_ENABLE, NULL);        
    return Status;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   ProcessOpRomCallback
//
// Description: This callback will be called before and after installing legacy OpROM
//
// Input:		
//  IN EFI_EVENT Event - Callback event
//  IN VOID *Context - pointer to calling context
//
// Output:      None
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID ProcessOpRomCallback(
    IN EFI_EVENT Event, 
    IN VOID *Context
)
{
    EFI_STATUS Status;
    EFI_HANDLE Handle;
    UINTN Size = sizeof(EFI_HANDLE);
    CSM_PLATFORM_POLICY_DATA *OpRomStartEndProtocol;
    EFI_PCI_IO_PROTOCOL *PciIo;
    UINT8 PciClassCode;

    Status = pBS->LocateHandle(ByRegisterNotify, NULL, ProcessOpRomRegistration, &Size, &Handle);
    ASSERT_EFI_ERROR(Status);
    if (EFI_ERROR(Status)) 
        return;

    Status = pBS->HandleProtocol(Handle, &OpRomStartEndProtocolGuid, &OpRomStartEndProtocol);
    ASSERT_EFI_ERROR(Status);
    if (EFI_ERROR(Status)) 
        return;

    if(OpRomStartEndProtocol == NULL) { //post-process OpROM callback
        if(UefiGopDisconnected && !ProceedToBoot)
/* if this is last OpROM, and Gop was disconnected and we're not on legacy boot path */
            pBS->ConnectController(SharedGopHandle, NULL, NULL, TRUE);
        return;
    }

//check if someone already disabled execution of this OpROM
    if(OpRomStartEndProtocol->PciIo == NULL || OpRomStartEndProtocol->ExecuteThisRom == FALSE)
        return;

    PciIo = OpRomStartEndProtocol->PciIo;
    Status = PciIo->Pci.Read(PciIo, EfiPciIoWidthUint8, 0xB, 1, &PciClassCode);
    if (EFI_ERROR(Status)) 
        return;

    Status = CheckOpRomExecution(PciClassCode, FALSE);
    if(EFI_ERROR(Status)) {
        OpRomStartEndProtocol->ExecuteThisRom = FALSE;
        return;
    }

/* OK, we're decided to execute OpROM */
    OpRomStartEndProtocol->ExecuteThisRom = TRUE;

    if(PciClassCode == PCI_CL_DISPLAY) {
        Status = DisconnectUefiGop(PciIo);
    /* 
        we are executing video OpROM even if we can't disconnect
        native UEFI driver - possible bug
    */
        if(!EFI_ERROR(Status))
            UefiGopDisconnected = TRUE;
    }
    return;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   LocateHandlesCallback
//
// Description: This callback executed every time DriverBinding is installed
//
// Input:		
//  IN EFI_EVENT Event - Callback event
//  IN VOID *Context - pointer to calling context
//
// Output:      None
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID LocateHandlesCallback(
    IN EFI_EVENT Event, 
    IN VOID *Context
)
{
    EFI_STATUS Status;
    EFI_STATUS Status1;
    UINTN Count = sizeof(EFI_HANDLE);
    EFI_HANDLE Handle;
    VOID *DummyInterface;

    do {
        Status = pBS->LocateHandle(ByRegisterNotify, 
                    NULL, 
                    DriverBindingRegistration, 
                    &Count, 
                    &Handle);
        if(!EFI_ERROR(Status)) {
            Status1 = pBS->HandleProtocol(Handle, 
                        &AmiCsmThunkProtocolGuid, 
                        &DummyInterface);
            if(EFI_ERROR(Status1)) { 
                Status = AddHandle(&NonThunkHandles, Handle);
            } else {
                Status = AddHandle(&ThunkHandles, Handle);
            }
        }
    } while (!EFI_ERROR(Status));
            
    return;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   InitHandleBuffer
//
// Description: This function allocates buffer to store DriverBinding handles
//
// Input:		
//  IN OUT HANDLE_BUFFER *Target - pointer to buffer to be initialized
//
// Output:
//  EFI_STATUS
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS InitHandleBuffer(
    IN OUT HANDLE_BUFFER *Target
)
{
    EFI_STATUS Status;

    Status = pBS->AllocatePool(EfiBootServicesData, 
                    sizeof(EFI_HANDLE) * DEFAULT_HANDLE_BUFFER_SIZE, 
                    (VOID **)&(Target->Array));
    if(!EFI_ERROR(Status)) {
        Target->TotalSize = DEFAULT_HANDLE_BUFFER_SIZE;
        Target->CurrentSize = 0;
    }
    return Status;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   IncreaseHandleBuffer
//
// Description: This function increases and reallocates buffer to store 
//              DriverBinding handles
//
// Input:		
//  IN OUT HANDLE_BUFFER *Target - pointer to buffer to be increased
//
// Output:
//  EFI_STATUS
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS IncreaseHandleBuffer(
    IN OUT HANDLE_BUFFER *Target
)
{
    EFI_STATUS Status;
    VOID *NewArray;

    Status = pBS->AllocatePool(EfiBootServicesData, 
                    sizeof(EFI_HANDLE) * (Target->TotalSize + DEFAULT_HANDLE_BUFFER_SIZE), 
                    &NewArray);
    if(!EFI_ERROR(Status)) {
        MemCpy(NewArray, Target->Array, sizeof(EFI_HANDLE) * Target->CurrentSize);
        Target->TotalSize += DEFAULT_HANDLE_BUFFER_SIZE;

        pBS->FreePool(Target->Array);
        Target->Array = (EFI_HANDLE *)NewArray;
    }
    return Status;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   AddHandle
//
// Description: This function stores handles in allocated buffer
//
// Input:		
//  IN OUT HANDLE_BUFFER *Target - pointer to buffer to store handle in
//  EFI_HANDLE Handle - handle to be stored
//
// Output:
//  EFI_STATUS
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS AddHandle(
    IN OUT HANDLE_BUFFER *Target,
    EFI_HANDLE Handle
)
{
    EFI_STATUS Status;

    if(Target->CurrentSize >= Target->TotalSize) {
        Status = IncreaseHandleBuffer(Target);
        if(EFI_ERROR(Status))
            return Status;
    }

    Target->Array[Target->CurrentSize] = Handle;
    Target->CurrentSize++;
    return EFI_SUCCESS;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   ProceedToBootCallback
//
// Description: This callback executed when all drivers are connected and system
//              proceeds to boot
//
// Input:		
//  IN EFI_EVENT Event - Callback event
//  IN VOID *Context - pointer to calling context
//
// Output:      None
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID ProceedToBootCallback(
    IN EFI_EVENT Event, 
    IN VOID *Context
)
{
    ProceedToBoot = TRUE;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//  Procedure:   CsmOptOutEntry
//
//  Description:
//  This function is CsmOptOut driver entry point 
//
//  Input:
// 	IN EFI_HANDLE ImageHandle - Image handle
// 	IN EFI_SYSTEM_TABLE *SystemTable - pointer to system table
//
//  Output:
//  EFI_SUCCESS - Function executed successfully
//  EFI_ERROR - Some error occured during execution
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS CsmOptOutEntry(
	IN EFI_HANDLE ImageHandle,
	IN EFI_SYSTEM_TABLE *SystemTable
)
{
    EFI_STATUS Status;
    EFI_HANDLE Handle;
    SETUP_DATA SetupData;
    UINTN Size = sizeof(SETUP_DATA);
    EFI_EVENT OptOutEvent;
    VOID *Registration;

    Status = pRS->GetVariable(L"Setup", &SetupGuid, NULL, &Size, &SetupData);

    if(!EFI_ERROR(Status)) {
        CsmOptOutSetupData.CsmLaunchPolicy = SetupData.CsmLaunchPolicy;
        CsmOptOutSetupData.BootOptionFilter = SetupData.BootOptionFilter;
        CsmOptOutSetupData.PxeOpRom = SetupData.PxeOpRom;
        CsmOptOutSetupData.MassStorageOpRom = SetupData.MassStorageOpRom;
        CsmOptOutSetupData.VideoOpRom = SetupData.VideoOpRom;
        CsmOptOutSetupData.OldOpRom = SetupData.OldOpRom;
    }

//Determine current CSM state based on whether AmiLoadCsmGuid protocol is installed
    Size = sizeof(EFI_HANDLE);
    Status = pBS->LocateHandle(ByProtocol, &AmiLoadCsmGuid, NULL, &Size, &Handle);
    CurrentCsmState = (EFI_ERROR(Status)) ? 0 : 1;

    if(CurrentCsmState == 1) {
        Status = RegisterProtocolCallback(&OpRomStartEndProtocolGuid, 
                         ProcessOpRomCallback, 
                         NULL, 
                         &OptOutEvent, 
                         &ProcessOpRomRegistration);
        if(EFI_ERROR(Status))
            return Status;

        Status = RegisterProtocolCallback(&BdsAllDriversConnectedProtocolGuid, 
                         ProceedToBootCallback, 
                         NULL, 
                         &OptOutEvent, 
                         &Registration);
        if(EFI_ERROR(Status))
            return Status;

        /* Init platform driver override protocol */
        Status = InitHandleBuffer(&ThunkHandles);
        if(EFI_ERROR(Status))
            return Status;

        Status = InitHandleBuffer(&NonThunkHandles);
        if(EFI_ERROR(Status))
            return Status;

        Status = RegisterProtocolCallback(&gEfiDriverBindingProtocolGuid, 
                        LocateHandlesCallback, 
                        NULL, 
                        &OptOutEvent, 
                        &DriverBindingRegistration);
        if(EFI_ERROR(Status))
            return Status;

        /*call callback manually to get already registered handles */
        LocateHandlesCallback(OptOutEvent, NULL);
        
        Status = pBS->InstallMultipleProtocolInterfaces(&Handle,
                        &AmiOpromPolicyProtocolGuid, 
                        &AmiOpRomPolicyProtocol,
                        &gEfiPlatformDriverOverrideProtocolGuid, 
                        &CsmOptOutPlatformDriverOverride,
                        NULL);
    } else {
//Reset Boot option filter to avoid situation, when no boot options are available
        CsmOptOutSetupData.BootOptionFilter = 0;
//Set video policy to UEFI only
        CsmOptOutSetupData.VideoOpRom = 1;
    }

    return EFI_SUCCESS;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//  Procedure:   GetUefiOpRomPolicy
//
//  Description:
//  This function is HII driver entry point 
//
//  Input:
// 	IN EFI_HANDLE ImageHandle - Image handle
// 	IN EFI_SYSTEM_TABLE *SystemTable - pointer to system table
//
//  Output:
//  EFI_SUCCESS - Function executed successfully, HII protocols installed
//  EFI_ERROR - Some error occured during execution
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS CheckUefiOpRomPolicy(
    IN	AMI_OPROM_POLICY_PROTOCOL *This,
    IN	EFI_HANDLE                PciHandle
)
{
    UINT32 i;
    EFI_STATUS Status;
    EFI_PCI_IO_PROTOCOL *PciIo;
    UINT8 PciClass;

    for(i = 0; OemCheckUefiOpromPolicyList[i] != NULL; i++) {
        Status = OemCheckUefiOpromPolicyList[i](PciHandle);
        if(Status == EFI_SUCCESS || Status == EFI_UNSUPPORTED)
            return Status;
    }

    Status = pBS->HandleProtocol(PciHandle, &gEfiPciIoProtocolGuid, &PciIo);
    if(EFI_ERROR(Status))
        return Status;

    Status = PciIo->Pci.Read(PciIo, EfiPciIoWidthUint8, 0xB, 1, &PciClass);

    return (EFI_ERROR(Status))? Status : CheckOpRomExecution(PciClass, TRUE);
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   GetBusSpecificHandle
//
// Description: This function returns bus-specific handle for given controller
//
// Input:		
//  IN EFI_HANDLE ControllerHandle - handle of the controller
//  IN OUT EFI_HANDLE *DriverImageHandle - pointer to returned handle placeholder
//
// Output:
//  EFI_SUCCESS - handle returned
//  EFI_NOT_FOUND - handle not found
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS GetBusSpecificHandle(
	IN EFI_HANDLE ControllerHandle,
	IN OUT EFI_HANDLE *DriverImageHandle
)
{
    EFI_STATUS Status;

    if(BusSpecific == NULL) {
        Status = pBS->HandleProtocol(
                        ControllerHandle,  
                        &gEfiBusSpecificDriverOverrideProtocolGuid, 
                        &BusSpecific);
        if(EFI_ERROR(Status))
            return Status;
    }

    return BusSpecific->GetDriver(BusSpecific, DriverImageHandle);
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   IsManageable
//
// Description: This function returns if given PCI device class supports 
//              controlled UEFI/Legacy OpROM execution sequence
//
// Input:		
//  IN UINT8 PciClass - class of the device
//
// Output:
//  TRUE - controlled sequence supported
//  FALSE - controlled sequence not supported
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
BOOLEAN IsManageable(
    IN UINT8 PciClass
)
{
    if(PciClass == PCI_CL_DISPLAY ||
       PciClass == PCI_CL_NETWORK ||
       PciClass == PCI_CL_MASS_STOR)
        return TRUE;

    return FALSE;
}

VOID UpdateTransaction(
    IN EFI_STATUS Status,
    IN EFI_HANDLE ControllerHandle,
    IN EFI_HANDLE DriverImageHandle
)
{
    if(!EFI_ERROR(Status)) {
        TransactionInProgress = TRUE;
        CurrentHandle = ControllerHandle;
        LastReturnedImageHandle = DriverImageHandle;
    } else {
        TransactionInProgress = FALSE;
        CurrentHandle = NULL;
        LastReturnedImageHandle = NULL;
    }
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   CsmOptOutGetDriver
//
// Description: Implementation of Platform Drive Override protocol
//              GetDriver function
//
// Input:		
//  IN EFI_PLATFORM_DRIVER_OVERRIDE_PROTOCOL *This - pointer to the instance of
//          the protocol
//  IN EFI_HANDLE ControllerHandle - handle of controller for which to retrieve
//          DriverBinding handle
//  IN OUT EFI_HANDLE *DriverImageHandle - pointer to returned handle placeholder
//
// Output:
//  EFI_SUCCESS - handle returned
//  EFI_NOT_FOUND - handle not found
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS CsmOptOutGetDriver(
	IN EFI_PLATFORM_DRIVER_OVERRIDE_PROTOCOL *This,
	IN EFI_HANDLE ControllerHandle,
	IN OUT EFI_HANDLE *DriverImageHandle
)
{
    EFI_STATUS Status;
    if(TransactionInProgress) {
        if(*DriverImageHandle != LastReturnedImageHandle || 
           ControllerHandle != CurrentHandle) {
            Status = EFI_INVALID_PARAMETER;
            UpdateTransaction(Status, NULL, NULL);
            return Status;
        }
    }
        
    Status = CsmOptOutGetDriverWorker(This, ControllerHandle, DriverImageHandle);
    UpdateTransaction(Status, ControllerHandle, *DriverImageHandle);
    return Status;
}

EFI_STATUS CsmOptOutGetDriverWorker(
	IN EFI_PLATFORM_DRIVER_OVERRIDE_PROTOCOL *This,
	IN EFI_HANDLE ControllerHandle,
	IN OUT EFI_HANDLE *DriverImageHandle
)
{
    EFI_STATUS Status;
    EFI_PCI_IO_PROTOCOL *PciIo;
    UINT8 PciClass;
    UINT8 Policy;

    if(ControllerHandle == NULL)
        return EFI_INVALID_PARAMETER;

    if(*DriverImageHandle == NULL) { //This is first call
        Status = pBS->HandleProtocol(ControllerHandle, &gEfiPciIoProtocolGuid, &PciIo);
        if(EFI_ERROR(Status))
            return EFI_NOT_FOUND;      //we don't care about non pci handles

        Status = PciIo->Pci.Read(PciIo, EfiPciIoWidthUint8, 0xB, 1, &PciClass);
        if(EFI_ERROR(Status))
            return EFI_NOT_FOUND; 

        Policy = GetOpRomPolicy(PciClass);
        if(Policy == 0)                 //OpROM execution is disabled
            return EFI_NOT_FOUND;

    /* check if this pci class supported for controlled OpROM
       execution sequence
    */
        if(!IsManageable(PciClass)) 
            return EFI_NOT_FOUND;

        ThunkFirst = (Policy == 2 || Policy == 3) ? TRUE : FALSE;
    }

    if(ThunkFirst) {
        if(CurrentCount < ThunkHandles.CurrentSize) {
            *DriverImageHandle = ThunkHandles.Array[CurrentCount];
            CurrentCount++;
            return EFI_SUCCESS;
        } else {
            CurrentCount = 0;               //reset counter
            return EFI_NOT_FOUND;
        }
    } else {
/* first get handles provided by bus specific override protocol */
        if((UINTN)BusSpecific != 0xfffffffa) {
            Status = GetBusSpecificHandle(ControllerHandle, DriverImageHandle);
            if(!EFI_ERROR(Status)) {
                return Status;
            }

            (UINTN)BusSpecific = 0xfffffffa;    //set flag we're done with bus specific override
        }
/* now get other Driver binding handles except those with thunk protocol */
        if(CurrentCount < NonThunkHandles.CurrentSize) {
            *DriverImageHandle = NonThunkHandles.Array[CurrentCount];
            CurrentCount++;
            return EFI_SUCCESS;
        } else {
            CurrentCount = 0;
            (UINTN)BusSpecific = 0;             //set flag we need to start from bus specific next time we're called
        }
    }
    return EFI_NOT_FOUND;
}

//**********************************************************************
//**********************************************************************
//**                                                                  **
//**        (C)Copyright 1985-2011, American Megatrends, Inc.         **
//**                                                                  **
//**                       All Rights Reserved.                       **
//**                                                                  **
//**      5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093        **
//**                                                                  **
//**                       Phone: (770)-246-8600                      **
//**                                                                  **
//**********************************************************************
//**********************************************************************
