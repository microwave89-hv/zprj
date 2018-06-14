//**********************************************************************
//**********************************************************************
//**                                                                  **
//**        (C)Copyright 1985-2014, American Megatrends, Inc.         **
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
// $Header: /Alaska/SOURCE/Modules/AmiGopPolicy/AmiGopPolicySetup.c 9     7/17/14 5:36a Josephlin $
//
// $Revision: 9 $
//
// $Date: 7/17/14 5:36a $
//**********************************************************************
// Revision History
// ----------------
// $Log: /Alaska/SOURCE/Modules/AmiGopPolicy/AmiGopPolicySetup.c $
// 
// 9     7/17/14 5:36a Josephlin
// [TAG]  		EIP176969
// [Category]  	Improvement
// [Description]  	Change "#else if" to "#elif" to improve compiling
// efficiency.
// [Files]  		AmiGopPolicySetup.c
// 
// 8     5/15/14 2:25a Jameswang
// [TAG]  		EIP168961
// [Category]  	Improvement
// [Description]  	- Do not set EFI_VARIABLE_RUNTIME_ACCESS for all
// variables: AmiGopPolicySetupData and AmiGopOutputDp.
// - Do not change attribute of Setup variable.
// - Fixed hanging at InitAmiGopPolicyStrings() if the length of GOP
// driver name >= 0x40. GetDriverName() added a length argument.
// - Change module specific variable's GUID not equal to
// AMI_GLOBAL_VARIABLE_GUID.
// 
// 7     11/07/12 5:00a Josephlin
// [TAG]  		N/A
// [Category]  	Bug Fix
// [Severity]  	Normal
// [Symptom]  	SCT Test Fail
// [RootCause]  	EFI_GLOBAL_VARIABLE guid is used in non EFI defined
// variable.
// [Solution]  	New guid AMI_GLOBAL_VARIABLE_GUID is created and used.
// [Files]  		AmiGopPolicySetup.c
// 
// 6     10/28/12 11:59p Josephlin
// [TAG]  		EIP103432
// [Category]  	Improvement
// [Description]  	Add nVidia GOP switch function support for AmiGopPolicy
// module.
// [Files]  		AmiGopPolicySetup.c
// 
// 5     9/07/12 3:43a Josephlin
// [TAG]  		EIP97375
// [Category]  	Bug Fix
// [Severity]  	Normal
// [Symptom]  	If switch the output from HDMI to CRT then save and exit,
// the setup value still keep in HDMI.
// [RootCause]  	Incorrect input value (void **) for MemCmp().
// [Solution]  	Change the input type to (void *) for MemCmp().
// [Files]  		AmiGopPolicySetup.c
// 
// 4     8/03/12 3:38a Josephlin
// [TAG]  		EIP96705
// [Category]  	Improvement
// [Description]  	If ComponentName2 Protocol doesn't supports "en-us",
// try to use first language of SupportedLanguages. This is able to avoid
// Driver & Device name display "Unknow" always.
// [Files]  		AmiGopPolicySetup.c
// 
// 3     7/26/12 7:30a Josephlin
// Update File Header.
// 
// 2     7/23/12 3:32a Josephlin
// 1. Added input argument SetupData for eLink OemGopSwitchHookList.
// 2. Created token "AmiGopPolicySetupFile" and "AmiGopPolicySetupString"
// for override sd and uni file.
// 3. Rename AmiGopPolicyCallback to AmiGopSwitchCallback in case user
// confuse.
// 
// 1     6/29/12 3:45a Josephlin
// [TAG]  		EIP91970
// [Category]  	New Feature
// [Description]  	Initial Release for Display Switch with UEFI GOP driver
// support.
// [Files]  		AmiGopPolicy.cif
// AmiGopPolicy.c
// AmiGopPolicy.h
// AmiGopPolicy.mak
// AmiGopPolicy.sd
// AmiGopPolicy.sdl
// AmiGopPolicy.uni
// AmiGopPolicyLib.c
// AmiGopPolicySetup.c
// 
//**********************************************************************
//<AMI_FHDR_START>
//
// Name:        AmiGopPolicySetup.c
//
// Description: AmiGopPolicy Setup Routines.
//
//<AMI_FHDR_END>
//**********************************************************************

//----------------------------------------------------------------------
// Include(s)
//----------------------------------------------------------------------

#include <Efi.h>
#include <AmiLib.h>
#include <AmiDxeLib.h>
#include "AmiCspLib.h"
#include <Setup.h>
#include <SetupStrTokens.h>
#include <Token.h>
#include "AmiGopPolicy.h"

#include <Protocol\ComponentName.h>
#include <Protocol\DevicePath.h>
#include <Protocol\GraphicsOutput.h>
#include <Protocol\DriverBinding.h>
#include <Protocol\EdidDiscovered.h>

//----------------------------------------------------------------------
// Constant, Macro and Type Definition(s)
//----------------------------------------------------------------------
// Constant Definition(s)

// Macro Definition(s)

// Type Definition(s)

// Function Prototype(s)

BOOLEAN GetDriverName (
  IN  EFI_HANDLE  DriverBindingHandle,
  IN  UINT16      Length,
  OUT CHAR8       *String
);

BOOLEAN GetDeviceName (
  IN  EFI_HANDLE  DriverBindingHandle,
  IN  EFI_HANDLE  ControllerHandle,
  IN  EFI_HANDLE  ChildControllerHandle,
  OUT CHAR8       *String
);

EFI_STATUS GetDriverBindingHandle (
  IN  EFI_HANDLE  ControllerHandle,
  OUT EFI_HANDLE  *DriverBindingHandle
);

EFI_STATUS GetDriverHandleBuffer (
  IN  EFI_HANDLE  Controller,
  OUT UINTN       *DriverHandleCount,
  OUT EFI_HANDLE  **DriverHandleBuffer
);

EFI_STATUS GetDeviceHandlesManagedByDriver (
  IN  EFI_HANDLE  DriverBindingHandle,
  OUT UINTN       *ControllerHandleCount,
  OUT EFI_HANDLE  **ControllerHandleBuffer
);

EFI_STATUS GetChildDeviceHandlesManagedByDriver (
  IN  EFI_HANDLE  DriverBindingHandle,
  IN  EFI_HANDLE  ControllerHandle,
  OUT UINTN       *ChildControllerHandleCount,
  OUT EFI_HANDLE  **ChildControllerHandleBuffer
);

EFI_STATUS GetEdidDiscoveredHandlesManagedByDriver (
  IN  EFI_HANDLE  DriverBindingHandle,
  IN  EFI_HANDLE  ControllerHandle
);

EFI_STATUS GetOutputDeviceHandlesManagedByDriver (
  IN  EFI_HANDLE  DriverBindingHandle,
  IN  EFI_HANDLE  ControllerHandle,
  OUT UINTN       *OutputHandleCount,
  OUT EFI_HANDLE  **OutputHandleBuffer
);

EFI_STATUS AmiGopDeviceCheck (
    IN  EFI_HANDLE                  ControllerHandle,
    IN  EFI_HANDLE                  DriverBindingHandle,
    IN  EFI_PCI_IO_PROTOCOL         *PciIo
);

EFI_STATUS AmiGopSwitchHook (
    IN  EFI_HANDLE                  ControllerHandle, 
    IN  EFI_HANDLE                  DriverBindingHandle,
    IN  SETUP_DATA                  *SetupData,
    IN  EFI_DEVICE_PATH_PROTOCOL    *DevicePath
);

//----------------------------------------------------------------------
// Variable and External Declaration(s)
//----------------------------------------------------------------------
// Variable Declaration(s)

T_ITEM_LIST OutputHndList = { 0, 0, NULL };

UINT16  sDeviceName[] = { 
        STRING_TOKEN(STR_GOP_DEVICE_NAME_0),
        STRING_TOKEN(STR_GOP_DEVICE_NAME_1),
        STRING_TOKEN(STR_GOP_DEVICE_NAME_2),
        STRING_TOKEN(STR_GOP_DEVICE_NAME_3),
        };

UINT16  sDriverName[] = { 
        STRING_TOKEN(STR_GOP_DRIVER_NAME_0),
        STRING_TOKEN(STR_GOP_DRIVER_NAME_1),
        STRING_TOKEN(STR_GOP_DRIVER_NAME_2),
        STRING_TOKEN(STR_GOP_DRIVER_NAME_3),
        };

UINT16  sOutputName[] = {
        STRING_TOKEN(STR_GOP_OUTPUT_NAME_0),
        STRING_TOKEN(STR_GOP_OUTPUT_NAME_1),
        STRING_TOKEN(STR_GOP_OUTPUT_NAME_2),
        STRING_TOKEN(STR_GOP_OUTPUT_NAME_3),
        STRING_TOKEN(STR_GOP_OUTPUT_NAME_4),
        STRING_TOKEN(STR_GOP_OUTPUT_NAME_5),
        STRING_TOKEN(STR_GOP_OUTPUT_NAME_6),
        STRING_TOKEN(STR_GOP_OUTPUT_NAME_7)
        };

// GUID Definition(s)

static EFI_GUID gAmiGopPolicyVariableGuid = AMI_GOP_POLICY_VARIABLE_GUID;    
static EFI_GUID gSetupGuid = SETUP_GUID;

// Protocol Definition(s)

// External Declaration(s)

extern EFI_GUID gEfiComponentName2ProtocolGuid;

// Function Definition(s)

//----------------------------------------------------------------------

//<AMI_PHDR_START>
//----------------------------------------------------------------------
//
// Procedure:   InitAmiGopPolicyStrings
//
// Description: Initializes AmiGopPolicy Setup String
//
// Parameters:  HiiHandle - Handle to HII database
//              Class - Indicates the setup class
//
// Returns:     None
//
// Notes:
//
//----------------------------------------------------------------------
//<AMI_PHDR_END>

VOID InitAmiGopPolicyStrings (
    IN EFI_HII_HANDLE   HiiHandle,
    IN UINT16           Class )
{
    EFI_STATUS                  Status = EFI_SUCCESS;

    UINTN                       VariableSize = 0;
    AMI_GOP_POLICY_SETUP_DATA   AmiGopPolicySetupData;

    UINTN                       ControllerHandleCount = 0;
    EFI_HANDLE                  *ControllerHandleBuffer = NULL;
    EFI_HANDLE                  ControllerHandle;
    UINTN                       ControllerHandleIndex;

    EFI_HANDLE                  DriverBindingHandle;

    EFI_PCI_IO_PROTOCOL         *PciIo;

    UINTN                       ChildHandleCount = 0;
    EFI_HANDLE                  *ChildHandleBuffer = NULL;
    EFI_HANDLE                  ChildHandle;
    UINTN                       ChildHandleIndex = 0;
    EFI_DEVICE_PATH_PROTOCOL    *ChildHandleDp;
    CHAR16                      ChildHandleDpVar[0x40];
    EFI_DEVICE_PATH_PROTOCOL    *AmiGopOutputDp = NULL;

    UINTN                       SetupSize;
    SETUP_DATA                  SetupData;

    CHAR8                       String[0x40];

    UINTN                       Index = 0;
    UINTN                       SelectIndex = 0;

    UINT32                      VarAttr;

    if (Class != ADVANCED_FORM_SET_CLASS) return;

    // Save default AmiGopPolicySetupData on memory.
    AmiGopPolicySetupData.GopDeviceCount = 0;
    AmiGopPolicySetupData.GopOutputCount = 0;
    VariableSize = sizeof(AMI_GOP_POLICY_SETUP_DATA);
    Status = pRS->SetVariable (
                  L"AmiGopPolicySetupData",
                  &gAmiGopPolicyVariableGuid,
                  EFI_VARIABLE_BOOTSERVICE_ACCESS,
                  VariableSize,
                  &AmiGopPolicySetupData );

    // Init String buffer
    pBS->SetMem(String, sizeof(String), 0);

    //
    // Get all drivers handles which has PCI IO Protocol
    //
    Status = pBS->LocateHandleBuffer(
                  ByProtocol,
                  &gEfiPciIoProtocolGuid,
                  NULL,
                  &ControllerHandleCount,
                  &ControllerHandleBuffer);
    if (EFI_ERROR(Status)) return;

    for (ControllerHandleIndex = 0; ControllerHandleIndex < ControllerHandleCount; ControllerHandleIndex++) {
        ControllerHandle = ControllerHandleBuffer[ControllerHandleIndex];
        Status = pBS->HandleProtocol (ControllerHandle, &gEfiPciIoProtocolGuid, &PciIo);
        if (EFI_ERROR(Status)) continue;

        Status = GetDriverBindingHandle (ControllerHandle, &DriverBindingHandle);
        if (EFI_ERROR(Status)) continue;

        Status = AmiGopDeviceCheck (ControllerHandle, DriverBindingHandle, PciIo);
        if (EFI_ERROR(Status)) continue;

        if (GetDeviceName(DriverBindingHandle, ControllerHandle, NULL, String)) {
            InitString(HiiHandle, sDeviceName[Index], L"%S", String);
            pBS->SetMem(String, sizeof(String), 0);
        }

        if (GetDriverName(DriverBindingHandle, 0x40, String)) {
            InitString(HiiHandle, sDriverName[Index], L"%S", String);
            pBS->SetMem(String, sizeof(String), 0);
        }

        Status = GetOutputDeviceHandlesManagedByDriver (DriverBindingHandle, ControllerHandle, &ChildHandleCount, &ChildHandleBuffer);
        if (!EFI_ERROR(Status)) {
            VariableSize = 0;
            Status = GetEfiVariable (
                     L"AmiGopOutputDp",
                     &gAmiGopPolicyVariableGuid,
                     NULL,
                     &VariableSize,
                     &AmiGopOutputDp);
            for (ChildHandleIndex = 0; ChildHandleIndex < ChildHandleCount; ChildHandleIndex++) {
                ChildHandle = ChildHandleBuffer[ChildHandleIndex];
                if (GetDeviceName(DriverBindingHandle, ControllerHandle, ChildHandle, String)) {
                    Status = pBS->OpenProtocol (
                                  ChildHandle,
                                  &gEfiDevicePathProtocolGuid,
                                  (VOID**)&ChildHandleDp,
                                  NULL,
                                  NULL,
                                  EFI_OPEN_PROTOCOL_BY_HANDLE_PROTOCOL);
                    if (!EFI_ERROR(Status)) {
                        Swprintf (ChildHandleDpVar, L"ChildHandleDpVar%01x", ChildHandleIndex);
                        Status = pRS->SetVariable (
                                      ChildHandleDpVar,
                                      &gAmiGopPolicyVariableGuid,
                                      EFI_VARIABLE_BOOTSERVICE_ACCESS,
                                      DPLength (ChildHandleDp),
                                      ChildHandleDp );
                        if (AmiGopOutputDp != NULL) {
                            if (MemCmp (AmiGopOutputDp, ChildHandleDp, DPLength(ChildHandleDp)) == 0) {
                                SelectIndex = ChildHandleIndex;
                            }
                        }
                    }
                    InitString(HiiHandle, sOutputName[ChildHandleIndex], L"%S", String);
                    pBS->SetMem(String, sizeof(String), 0);
                }
            }
        }

        Index ++;
    }

    pBS->FreePool(AmiGopOutputDp);
    pBS->FreePool(ControllerHandleBuffer);

    // Update Gop Output Device Count
    SetupSize = sizeof(SETUP_DATA);
    Status = pRS->GetVariable(L"Setup", &gSetupGuid, &VarAttr, &SetupSize, &SetupData);
    if (!EFI_ERROR(Status)) {
        SetupData.GopOutputSelect = (UINT8)SelectIndex;
        Status = pRS->SetVariable(
                      L"Setup",
                      &gSetupGuid,
                      VarAttr,
                      sizeof(SETUP_DATA),
                      &SetupData);
    }

    // Save AmiGopPolicySetupData on memory.
    AmiGopPolicySetupData.GopDeviceCount = (UINT8)Index;
    AmiGopPolicySetupData.GopOutputCount = (UINT8)ChildHandleIndex;
    VariableSize = sizeof(AMI_GOP_POLICY_SETUP_DATA);
    Status = pRS->SetVariable (
                  L"AmiGopPolicySetupData",
                  &gAmiGopPolicyVariableGuid,
                  EFI_VARIABLE_BOOTSERVICE_ACCESS,
                  VariableSize,
                  &AmiGopPolicySetupData );
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------
//
// Procedure:   AmiGopSwitchCallback
//
// Description: None.
//
// Input:       None.
//
// Output:      None.
//
// Notes:       None.
//
//----------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS AmiGopSwitchCallback (
    IN EFI_HII_HANDLE           HiiHandle, 
    IN UINT16                   Class, 
    IN UINT16                   SubClass, 
    IN UINT16                   Key )
{
    EFI_STATUS                  Status = EFI_SUCCESS;
    SETUP_DATA                  *SetupData = NULL;
    UINTN                       SetupSize = sizeof(SETUP_DATA);
    UINTN                       VariableSize = 0;
    CALLBACK_PARAMETERS         *CallbackParameters = NULL;

    UINTN                       ControllerHandleCount = 0;
    EFI_HANDLE                  *ControllerHandleBuffer = NULL;
    EFI_HANDLE                  ControllerHandle;
    UINTN                       ControllerHandleIndex;

    EFI_PCI_IO_PROTOCOL         *PciIo;

    EFI_HANDLE                  DriverBindingHandle;
    EFI_DRIVER_BINDING_PROTOCOL *DriverBinding = NULL;

    UINTN                       DriverHandleCount = 0;
    EFI_HANDLE                  *DriverHandleBuffer = NULL;

    UINTN                       ChildHandleCount = 0;
    EFI_HANDLE                  *ChildHandleBuffer = NULL;
    UINTN                       ChildHandleIndex;
    CHAR16                      ChildHandleDpVar[0x40];

    EFI_DEVICE_PATH_PROTOCOL    *GopDevicePath = NULL;
    UINTN                       GopDevicePathLength = 0;

  	EFI_GRAPHICS_OUTPUT_PROTOCOL *Gop = NULL;
    UINTN                       HorizontalResolution = 0;
    UINTN                       VerticalResolution = 0;
    UINTN                       GopHandleCount = 0;
    EFI_HANDLE                  *GopHandleBuffer = NULL;
    UINTN                       GopHandleIndex;
	UINTN                       SizeOfInfo = 0;
    UINT32                      Mode;
    UINT32                      MaxMode = 0;
    EFI_GRAPHICS_OUTPUT_MODE_INFORMATION *Info = NULL;

    //
    // Get Setup Buffer
    //
    CallbackParameters = GetCallbackParameters();

#if ((TSE_BUILD >= 0x1224) && (EFI_SPECIFICATION_VERSION >= 0x2000A))
    if (CallbackParameters->Action != EFI_BROWSER_ACTION_CHANGED) return Status;
#elif ((TSE_BUILD > 0x1208) && (EFI_SPECIFICATION_VERSION >= 0x2000A))
    if (CallbackParameters->Action != EFI_BROWSER_ACTION_CHANGING) return Status;
#endif

    Status = pBS->AllocatePool (EfiBootServicesData, SetupSize, &SetupData);
    if(EFI_ERROR(Status)) return Status;

#if defined(EFI_SPECIFICATION_VERSION) && EFI_SPECIFICATION_VERSION > 0x20000
    Status = HiiLibGetBrowserData (&SetupSize, SetupData, &gSetupGuid, L"Setup");
    if(EFI_ERROR(Status)) return Status;
#else
    SetupData = (SETUP_DATA*)CallbackParameters->Data->NvRamMap;
#endif

    //
    // Get all drivers handles which has PCI IO Protocol
    //
    Status = pBS->LocateHandleBuffer (
                  ByProtocol,
                  &gEfiPciIoProtocolGuid,
                  NULL,
                  &ControllerHandleCount,
                  &ControllerHandleBuffer);
    if (EFI_ERROR(Status)) return Status;

    for (ControllerHandleIndex = 0; ControllerHandleIndex < ControllerHandleCount; ControllerHandleIndex++) {
        ControllerHandle = ControllerHandleBuffer[ControllerHandleIndex];
        Status = pBS->HandleProtocol (ControllerHandle, &gEfiPciIoProtocolGuid, &PciIo);
        if (EFI_ERROR(Status)) continue;

        //
        // Get Driver Binding Protocol for this VGA
        //
        Status = GetDriverBindingHandle (ControllerHandle, &DriverBindingHandle);
        if (EFI_ERROR(Status)) continue;

        Status = AmiGopDeviceCheck (ControllerHandle, DriverBindingHandle, PciIo);
        if (EFI_ERROR(Status)) continue;

        Status = pBS->OpenProtocol(
                      DriverBindingHandle,
                      &gEfiDriverBindingProtocolGuid,
                      (VOID**)&DriverBinding,
                      NULL,
                      NULL,
                      EFI_OPEN_PROTOCOL_GET_PROTOCOL);
        if (EFI_ERROR(Status)) continue;

        //
        // Find out Current GOP Output Mode
        //
        if (!EFI_ERROR(GetOutputDeviceHandlesManagedByDriver (DriverBindingHandle, ControllerHandle, &ChildHandleCount, &ChildHandleBuffer))) {
            for (ChildHandleIndex = 0; ChildHandleIndex < ChildHandleCount; ChildHandleIndex++) {
                Status = pBS->OpenProtocol (
                              ChildHandleBuffer[ChildHandleIndex],
                              &gEfiGraphicsOutputProtocolGuid,
                              (VOID**)&Gop,
                              NULL,
                              NULL,
                              EFI_OPEN_PROTOCOL_GET_PROTOCOL);
                if (!EFI_ERROR(Status)) {
                    HorizontalResolution = Gop->Mode->Info->HorizontalResolution;
                    VerticalResolution = Gop->Mode->Info->VerticalResolution;
                    break;
                }
            }
        }

        //
        // Get User Selected Gop Output Handle.
        //
        Swprintf (ChildHandleDpVar, L"ChildHandleDpVar%01x", SetupData->GopOutputSelect);
        GopDevicePathLength = 0;
        Status = GetEfiVariable (
                 ChildHandleDpVar,
                 &gAmiGopPolicyVariableGuid,
                 NULL,
                 &GopDevicePathLength,
                 &GopDevicePath);
        if (EFI_ERROR(Status)) continue;

        Status = AmiGopSwitchHook (ControllerHandle, DriverBindingHandle, SetupData, GopDevicePath);
        if (!EFI_ERROR(Status)) {
            //
            // Save AmiGop Outut Device path for next boot
            //
            Status = pRS->SetVariable (
                          L"AmiGopOutputDp",
                          &gAmiGopPolicyVariableGuid,
                          EFI_VARIABLE_NON_VOLATILE | EFI_VARIABLE_BOOTSERVICE_ACCESS,
                          DPLength(GopDevicePath),
                          GopDevicePath);
            if (EFI_ERROR(Status)) continue;

            //
            // Set GOP Output Mode
            //
            Status = GetOutputDeviceHandlesManagedByDriver (DriverBindingHandle, ControllerHandle, &GopHandleCount, &GopHandleBuffer);
            if (!EFI_ERROR(Status)) {
                for (GopHandleIndex = 0; GopHandleIndex < GopHandleCount; GopHandleIndex++) {
                    Status = pBS->OpenProtocol (
                                  GopHandleBuffer[GopHandleIndex],
                                  &gEfiGraphicsOutputProtocolGuid,
                                  (VOID**)&Gop,
                                  NULL,
                                  NULL,
                                  EFI_OPEN_PROTOCOL_GET_PROTOCOL);
                    if (!EFI_ERROR(Status)) {
                        if ((HorizontalResolution == Gop->Mode->Info->HorizontalResolution) &&
                            (VerticalResolution == Gop->Mode->Info->VerticalResolution))
                            break;
                        MaxMode = Gop->Mode->MaxMode;
                        for (Mode = 0; Mode <= MaxMode; Mode++) {
                            if (!EFI_ERROR (Gop->QueryMode (Gop, Mode, &SizeOfInfo, &Info))) {
                                if ((HorizontalResolution == Info->HorizontalResolution) &&
                                    (VerticalResolution == Info->VerticalResolution)) {
                                    Status = Gop->SetMode (Gop, Mode);
                                    if (!EFI_ERROR(Status)) break;
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    pBS->FreePool(SetupData);

    return Status;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------
//
// Procedure:   GetDriverName
//
// Description: Get driver's name from DriverBindingHandle first using 
//              LANGUAGE_CODE_ENGLISH then "eng" codes.
//
// Input:       DriverBindingHandle - handle with gEfiComponentName2ProtocolGuid
//              Length - Length of name to be copied to String including null
//
// Output:      String - driver name got
//
// Notes:       None.
//
//----------------------------------------------------------------------
//<AMI_PHDR_END>

BOOLEAN
GetDriverName (
  IN  EFI_HANDLE  DriverBindingHandle,
  IN  UINT16      Length,
  OUT CHAR8       *String )
{
    EFI_STATUS                      Status;
    CHAR16                          *DriverName;
    EFI_COMPONENT_NAME_PROTOCOL     *ComponentName;
    CHAR8                           *Lang = NULL;
    CHAR8                           *TempChar;

    //
    // Get driver name from UEFI 2.0 Component Name 2 protocol interface.
    //
    Status = pBS->OpenProtocol(
                  DriverBindingHandle,
                  &gEfiComponentName2ProtocolGuid,
                  (VOID**)&ComponentName,
                  NULL,
                  NULL,
                  EFI_OPEN_PROTOCOL_GET_PROTOCOL);
    if (!EFI_ERROR(Status)) {
        Status = ComponentName->GetDriverName(ComponentName, LANGUAGE_CODE_ENGLISH, &DriverName);
        if (EFI_ERROR(Status)) {
            //
            // Driver does not support "en-us", try to get SupportedLanguages
            //
            pBS->AllocatePool(EfiBootServicesData, Strlen(ComponentName->SupportedLanguages)+1, &Lang);
            if (Lang != NULL) {
                Strcpy(Lang, ComponentName->SupportedLanguages);
                TempChar = Strstr(Lang, ";");
                if (TempChar != NULL) *TempChar = 0x0000;
                Status = ComponentName->GetDriverName(ComponentName, Lang, &DriverName);
                pBS->FreePool(Lang);
                Lang = NULL;
            }
        }
        if (!EFI_ERROR(Status)) {
            DriverName[Length-1]=0; // avoid overflowed, copy only length
            Sprintf(String, "%S", DriverName);
            return TRUE;
        }
    }

    //
    // If it fails to get the driver name from Component Name protocol interface, we should fall back on
    // EFI 1.1 Component Name protocol interface.
    //
    Status = pBS->OpenProtocol(
                  DriverBindingHandle,
                  &gEfiComponentNameProtocolGuid,
                  (VOID**)&ComponentName,
                  NULL,
                  NULL,
                  EFI_OPEN_PROTOCOL_GET_PROTOCOL);
    if (!EFI_ERROR(Status)) {
        Status = ComponentName->GetDriverName(ComponentName, "eng", &DriverName);
        if (!EFI_ERROR(Status)) {
            DriverName[Length-1]=0; // avoid overflowed, copy only length
            Sprintf(String, "%S", DriverName);
            return TRUE;
        }
    }

    return FALSE;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Name:        GetDriverBindingHandle
//
// Description: None.
//
// Input:       None.
//
// Output:      None.
//
// Notes:       None.
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS
GetDriverBindingHandle (
  IN  EFI_HANDLE  ControllerHandle,
  OUT EFI_HANDLE  *DriverBindingHandle )
{
    EFI_STATUS                          Status;
    UINTN                               HandleCount;
    EFI_HANDLE                          *HandleBuffer;
    UINTN                               HandleIndex;
    EFI_GUID                            **ProtocolGuidArray;
    UINTN                               ArrayCount;
    UINTN                               ProtocolIndex;
    EFI_OPEN_PROTOCOL_INFORMATION_ENTRY *OpenInfo;
    UINTN                               OpenInfoCount;
    UINTN                               OpenInfoIndex;
    UINTN                               Index;

    Status = pBS->LocateHandleBuffer(
                  AllHandles,   
                  NULL,
                  NULL,
                  &HandleCount, 
                  &HandleBuffer);
    if (EFI_ERROR(Status)) return EFI_NOT_FOUND;

    for (HandleIndex = 0; HandleIndex < HandleCount; HandleIndex++) {
        ProtocolGuidArray = NULL;
        Status = pBS->ProtocolsPerHandle(
                      HandleBuffer[HandleIndex], 
                      &ProtocolGuidArray, 
                      &ArrayCount);
        if (EFI_ERROR(Status)) continue;

        for (ProtocolIndex = 0; ProtocolIndex < ArrayCount; ProtocolIndex++) {
            Status = pBS->OpenProtocolInformation(
                          HandleBuffer[HandleIndex], 
                          ProtocolGuidArray[ProtocolIndex],
                          &OpenInfo,
                          &OpenInfoCount);
            if (EFI_ERROR(Status)) continue;

            for (OpenInfoIndex = 0; OpenInfoIndex < OpenInfoCount; OpenInfoIndex++) {
                if (OpenInfo[OpenInfoIndex].ControllerHandle == ControllerHandle) {
                    if ((OpenInfo[OpenInfoIndex].Attributes & EFI_OPEN_PROTOCOL_BY_DRIVER) == EFI_OPEN_PROTOCOL_BY_DRIVER) {
                        for(Index = 0; Index < HandleCount; Index++) {
                            if(HandleBuffer[Index] == OpenInfo[OpenInfoIndex].AgentHandle) {
                                *DriverBindingHandle=HandleBuffer[Index];
                                pBS->FreePool(OpenInfo);
                                pBS->FreePool(ProtocolGuidArray);
                                pBS->FreePool(HandleBuffer);
                                return EFI_SUCCESS;
                            }
                        }
                    }
                }
            }
            if (OpenInfo != NULL) pBS->FreePool(OpenInfo);
        }
         if (ProtocolGuidArray != NULL) pBS->FreePool(ProtocolGuidArray);
    }
    if (HandleBuffer != NULL) pBS->FreePool(HandleBuffer);
    return EFI_NOT_FOUND;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Name:        GetDriverHandleBuffer
//
// Description: None.
//
// Input:       None.
//
// Output:      None.
//
// Notes:       None.
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS
GetDriverHandleBuffer (
  IN  EFI_HANDLE                        Controller,
  OUT UINTN                             *DriverHandleCount,
  OUT EFI_HANDLE                        **DriverHandleBuffer )
{
    EFI_STATUS                          Status;
    UINTN                               HandleCount;
    BOOLEAN                             *HandleBufferMap;
    EFI_HANDLE                          *HandleBuffer;
    UINTN                               HandleIndex;
    EFI_GUID                            **ProtocolGuidArray;
    UINTN                               ArrayCount;
    UINTN                               ProtocolIndex;
    EFI_OPEN_PROTOCOL_INFORMATION_ENTRY *OpenInfo;
    UINTN                               OpenInfoCount;
    UINTN                               OpenInfoIndex;
    UINTN                               Index;
    UINTN                               AvailableIndex = 0;

    Status = pBS->LocateHandleBuffer(
                  AllHandles,   
                  NULL,
                  NULL,
                  &HandleCount, 
                  &HandleBuffer);
    if (EFI_ERROR(Status)) return EFI_NOT_FOUND;

    HandleBufferMap = MallocZ (sizeof (BOOLEAN) * HandleCount);
    for (HandleIndex = 0; HandleIndex < HandleCount; HandleIndex++) {
        HandleBufferMap[HandleIndex] = FALSE;
    }

    for (HandleIndex = 0; HandleIndex < HandleCount; HandleIndex++) {
        ProtocolGuidArray = NULL;
        Status = pBS->ProtocolsPerHandle(
                      HandleBuffer[HandleIndex], 
                      &ProtocolGuidArray, 
                      &ArrayCount);
        if (EFI_ERROR(Status)) continue;

        for (ProtocolIndex = 0; ProtocolIndex < ArrayCount; ProtocolIndex++) {
            Status = pBS->OpenProtocolInformation(
                          HandleBuffer[HandleIndex], 
                          ProtocolGuidArray[ProtocolIndex],
                          &OpenInfo,
                          &OpenInfoCount);
            if (EFI_ERROR(Status)) continue;

            for (OpenInfoIndex = 0; OpenInfoIndex < OpenInfoCount; OpenInfoIndex++) {
                if (OpenInfo[OpenInfoIndex].ControllerHandle == Controller) {
                    if ((OpenInfo[OpenInfoIndex].Attributes & EFI_OPEN_PROTOCOL_BY_DRIVER) == EFI_OPEN_PROTOCOL_BY_DRIVER) {
                        for (Index = 0; Index < HandleCount; Index++) {
                            if (HandleBuffer[Index] == OpenInfo[OpenInfoIndex].AgentHandle) {
                                HandleBufferMap[Index] = TRUE;
                                (*DriverHandleCount)++; 
                            }
                        }
                    }
                }
            }
            pBS->FreePool(OpenInfo);
        }
        pBS->FreePool(ProtocolGuidArray);
    }

    if (*DriverHandleCount > 0) {
        //
        // Copy the found device handle to returned buffer
        //
        *DriverHandleBuffer = MallocZ (sizeof (EFI_HANDLE) * (*DriverHandleCount));
        for (HandleIndex = 0, AvailableIndex = 0; HandleIndex < HandleCount; HandleIndex++) {
            if (HandleBufferMap[HandleIndex]) {
                (*DriverHandleBuffer)[AvailableIndex] = HandleBuffer[HandleIndex];
                AvailableIndex++;
            }
        }
    }

    pBS->FreePool(HandleBuffer);

    if (*DriverHandleCount > 0)
        return EFI_SUCCESS;
    else
        return EFI_NOT_FOUND;
}

// <AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure: GetDeviceHandlesManagedByDriver
//
// Description:
//  Get all device handles which are being opened by a specific driver. The
//  rountine will allocate pool buffer for the found device handles, and it
//  is the caller's responsibility to safe free the buffer.
//
// Input:
//  IN  EFI_HANDLE  DriverBindingHandle - the handle of a driver which
//                                        contains the binding protocol
//  OUT UINTN       ControllerHandleCount - the number of available device handles
//                                          returned in ControllerHandleBuffer
//  OUT EFI_HANDLE  ControllerHandleBuffer - a pointer to the buffer to return
//                                           the array of device handles
//
// Output:
//     EFI_STATUS
//      If returned status is not succeful or find no available device,
//      the *ControllerHandleBuffer will be NULL
//
// Modified:
//
// Referrals:
//
// Notes:
//
//----------------------------------------------------------------------------
// <AMI_PHDR_END>

EFI_STATUS
GetDeviceHandlesManagedByDriver (
  IN  EFI_HANDLE  DriverBindingHandle,
  OUT UINTN       *ControllerHandleCount,
  OUT EFI_HANDLE  **ControllerHandleBuffer )
{
    UINTN                               HandleCount;
    EFI_HANDLE                          *HandleBuffer;
    BOOLEAN                             *HandleBufferMap;
    EFI_STATUS                          Status;
    UINTN                               HandleIndex;
    UINTN                               AvailableIndex;
    EFI_GUID                            **ProtocolGuidArray;
    UINTN                               ArrayCount;
    UINTN                               ProtocolIndex;
    EFI_OPEN_PROTOCOL_INFORMATION_ENTRY *OpenInfo;
    UINTN                               OpenInfoCount;
    UINTN                               OpenInfoIndex;

    *ControllerHandleCount  = 0;
    *ControllerHandleBuffer = NULL;
    HandleCount = 0;
    HandleBuffer = NULL;

    if (DriverBindingHandle == NULL) {
        Status = EFI_INVALID_PARAMETER;
        goto Error;
    }

    //
    // Retrieve the list of all handles from the handle database
    //
    Status = pBS->LocateHandleBuffer (
                  AllHandles,
                  NULL,
                  NULL,
                  &HandleCount,
                  &HandleBuffer
                  );
    if (EFI_ERROR (Status)) goto Error;

    //
    //Create a map for HandleBuffer. If a handle in HandleBuffer is the wanted device handle, its map item is true.
    //
    HandleBufferMap = MallocZ (sizeof (BOOLEAN) * HandleCount);
    for (HandleIndex = 0; HandleIndex < HandleCount; HandleIndex++) {
        HandleBufferMap[HandleIndex] = FALSE;
    }

    for (HandleIndex = 0; HandleIndex < HandleCount; HandleIndex++) {
        //
        // Check if it is a device handle
        //
        Status = pBS->OpenProtocol (
                      HandleBuffer[HandleIndex],
                      &gEfiDevicePathProtocolGuid,
                      NULL,
                      NULL,
                      NULL,
                      EFI_OPEN_PROTOCOL_TEST_PROTOCOL);
        if (EFI_ERROR(Status)) continue;

        //
        // Retrieve the list of all the protocols on each handle
        //
        Status = pBS->ProtocolsPerHandle (
                      HandleBuffer[HandleIndex],
                      &ProtocolGuidArray,
                      &ArrayCount);

        if (!EFI_ERROR (Status)) {
            for (ProtocolIndex = 0; ProtocolIndex < ArrayCount; ProtocolIndex++) {
                //
                // Retrieve the list of agents that have opened each protocol
                //
                Status = pBS->OpenProtocolInformation (
                              HandleBuffer[HandleIndex],
                              ProtocolGuidArray[ProtocolIndex],
                              &OpenInfo,
                              &OpenInfoCount);
                if (!EFI_ERROR (Status)) {
                    for (OpenInfoIndex = 0; OpenInfoIndex < OpenInfoCount; OpenInfoIndex++) {
                        if (OpenInfo[OpenInfoIndex].AgentHandle == DriverBindingHandle) {
                            if ((OpenInfo[OpenInfoIndex].Attributes & EFI_OPEN_PROTOCOL_BY_DRIVER) == EFI_OPEN_PROTOCOL_BY_DRIVER) {
                                //
                                // HandleBufferMap[HandleIndex] is the wanted device handle, find it in the handlebuffer
                                // A bus driver maybe open a Controller with BY_DRIVER attribute for different protocol  many times,
                                //
                                HandleBufferMap[HandleIndex] = TRUE;
                            }
                        }
                    }
                    pBS->FreePool (OpenInfo);
                }
            }
        pBS->FreePool (ProtocolGuidArray);
        }
    }

    //
    // count how many device handles are found
    //
    for (HandleIndex = 0; HandleIndex < HandleCount; HandleIndex++) {
        if (HandleBufferMap[HandleIndex]) {
            (*ControllerHandleCount)++;
        }
    }

    if (*ControllerHandleCount > 0) {
        //
        // Copy the found device handle to returned buffer
        //
        *ControllerHandleBuffer = MallocZ (sizeof (EFI_HANDLE) * (*ControllerHandleCount));
        for (HandleIndex = 0, AvailableIndex = 0; HandleIndex < HandleCount; HandleIndex++) {
            if (HandleBufferMap[HandleIndex]) {
                (*ControllerHandleBuffer)[AvailableIndex] = HandleBuffer[HandleIndex];
                AvailableIndex++;
            }
        }
    }

    if (HandleBuffer != NULL) pBS->FreePool (HandleBuffer);
    return EFI_SUCCESS;

Error:

    if (HandleBuffer != NULL) pBS->FreePool (HandleBuffer);
    return Status;
}

// <AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Name: GetChildDeviceHandlesManagedByDriver
//
// Description:
//  Get all child device handles which are being opened by a specific driver.
//  The rountine will allocate pool buffer for the found child device handles,
//  and it is the caller's responsibility to safe free the buffer.
//
// Input:
//  IN  EFI_HANDLE  DriverBindingHandle - the handle of a driver which
//                                        contains the binding protocol
//  IN  EFI_HANDLE  ControllerHandle - the device controller handle be opened
//                                     by its child device 
//  OUT UINTN       ChildControllerHandleCount - the number of available
//                                               device handles returned in
//                                               ControllerHandleBuffer
//  OUT EFI_HANDLE  ChildControllerHandleBuffer - a pointer to the buffer to
//                                                return the array of child
//                                                device handles
//
// Output:
//     EFI_STATUS
//      If returned status is not succeful or find no available device,
//      the *ChildControllerHandleBuffer will be NULL
//
// Modified:
//
// Referrals:
//
// Notes:
//
//----------------------------------------------------------------------------
// <AMI_PHDR_END>

EFI_STATUS
GetChildDeviceHandlesManagedByDriver (
  IN  EFI_HANDLE  DriverBindingHandle,
  IN  EFI_HANDLE  ControllerHandle,
  OUT UINTN       *ChildControllerHandleCount,
  OUT EFI_HANDLE  **ChildControllerHandleBuffer )
{
    UINTN                               HandleCount;
    EFI_HANDLE                          *HandleBuffer;
    BOOLEAN                             *HandleBufferMap;
    EFI_STATUS                          Status;
    UINTN                               HandleIndex;
    UINTN                               AvailableIndex;
    EFI_GUID                            **ProtocolGuidArray;
    UINTN                               ArrayCount;
    UINTN                               ProtocolIndex;
    EFI_OPEN_PROTOCOL_INFORMATION_ENTRY *OpenInfo;
    UINTN                               OpenInfoCount;
    UINTN                               OpenInfoIndex;

    *ChildControllerHandleCount  = 0;
    *ChildControllerHandleBuffer = NULL;
    HandleCount = 0;
    HandleBuffer = NULL;

    if ((DriverBindingHandle == NULL) || (ControllerHandle == NULL)) {
        Status = EFI_INVALID_PARAMETER;
        goto Error;
    }

    //
    // Retrieve the list of all handles from the handle database
    //
    Status = pBS->LocateHandleBuffer (
                  AllHandles,
                  NULL,
                  NULL,
                  &HandleCount,
                  &HandleBuffer);
    if (EFI_ERROR(Status)) goto Error;

    //
    // Create a map for HandleBuffer. If a handle in HandleBuffer is the wanted device handle, its map item is true.
    //
    HandleBufferMap = MallocZ (sizeof (BOOLEAN) * HandleCount);
    for (HandleIndex = 0; HandleIndex < HandleCount; HandleIndex++) {
        HandleBufferMap[HandleIndex] = FALSE;
    }

    //
    // Retrieve the list of all the protocols on each handle
    //
    Status = pBS->ProtocolsPerHandle (
                  ControllerHandle,
                  &ProtocolGuidArray,
                  &ArrayCount);
    if (!EFI_ERROR (Status)) {
        for (ProtocolIndex = 0; ProtocolIndex < ArrayCount; ProtocolIndex++) {
            //
            // Retrieve the list of agents that have opened each protocol
            //
            Status = pBS->OpenProtocolInformation (
                          ControllerHandle,
                          ProtocolGuidArray[ProtocolIndex],
                          &OpenInfo,
                          &OpenInfoCount);
            if (!EFI_ERROR (Status)) {
                for (OpenInfoIndex = 0; OpenInfoIndex < OpenInfoCount; OpenInfoIndex++) {
                    if (OpenInfo[OpenInfoIndex].AgentHandle == DriverBindingHandle) {
                        if ((OpenInfo[OpenInfoIndex].Attributes & EFI_OPEN_PROTOCOL_BY_CHILD_CONTROLLER) == EFI_OPEN_PROTOCOL_BY_CHILD_CONTROLLER) {
                            //
                            // OpenInfo[OpenInfoIndex].ControllerHandle is the wanted child device handle, find it in the handlebuffer
                            // A bus driver maybe open a Controller with BY_CHILD_CONTROLLER attribute for different protocol many times,
                            //
                            for (HandleIndex = 0; HandleIndex < HandleCount; HandleIndex++) {
                                if (OpenInfo[OpenInfoIndex].ControllerHandle == HandleBuffer[HandleIndex]) {
                                    HandleBufferMap[HandleIndex] = TRUE;
                                }
                            }
                        }
                    }
                }
            pBS->FreePool (OpenInfo);
            }
        }
        pBS->FreePool (ProtocolGuidArray);
    }

    //
    // count how many device handles are found
    //
    for (HandleIndex = 0; HandleIndex < HandleCount; HandleIndex++) {
        if (HandleBufferMap[HandleIndex]) {
            (*ChildControllerHandleCount)++;
        }
    }

    if (*ChildControllerHandleCount > 0) {
        //
        // Copy the found device handle to returned buffer
        //
        *ChildControllerHandleBuffer = MallocZ (sizeof (EFI_HANDLE) * (*ChildControllerHandleCount));
        for (HandleIndex = 0, AvailableIndex = 0; HandleIndex < HandleCount; HandleIndex++) {
            if (HandleBufferMap[HandleIndex]) {
                (*ChildControllerHandleBuffer)[AvailableIndex] = HandleBuffer[HandleIndex];
                AvailableIndex++;
            }
        }
    }

    if (HandleBuffer != NULL) pBS->FreePool (HandleBuffer);
    return EFI_SUCCESS;

Error:
    if (HandleBuffer != NULL) pBS->FreePool (HandleBuffer);
    return Status;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------
//
// Procedure:   GetEdidDiscoveredHandlesManagedByDriver
//
// Description: None.
//
// Input:       None.
//
// Output:      None.
//
// Notes:       None.
//
//----------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS
GetEdidDiscoveredHandlesManagedByDriver (
  IN  EFI_HANDLE  DriverBindingHandle,
  IN  EFI_HANDLE  ControllerHandle )
{
    EFI_STATUS      Status = EFI_SUCCESS;
    UINTN           ChildHandleCount = 0;
    EFI_HANDLE      *ChildHandleBuffer = NULL;
    UINTN           ChildHandleIndex = 0;

    Status = GetChildDeviceHandlesManagedByDriver (DriverBindingHandle, ControllerHandle, &ChildHandleCount, &ChildHandleBuffer);
    if (EFI_ERROR(Status)) return Status;

    for (ChildHandleIndex = 0; ChildHandleIndex < ChildHandleCount; ChildHandleIndex++) {
        Status = pBS->OpenProtocol(
                      ChildHandleBuffer[ChildHandleIndex],
                      &gEfiEdidDiscoveredProtocolGuid,
                      NULL, NULL, NULL,
                      EFI_OPEN_PROTOCOL_TEST_PROTOCOL);
        if (EFI_ERROR(Status)) Status = GetEdidDiscoveredHandlesManagedByDriver (DriverBindingHandle, ChildHandleBuffer[ChildHandleIndex]);
        else AppendItemLst(&OutputHndList, &ChildHandleBuffer[ChildHandleIndex]);
    }

    return EFI_SUCCESS;
}

// <AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Name: GetOutputDeviceHandlesManagedByDriver
//
// Description:
//  Get all output device handles which are produced by a specific driver.
//  The rountine will allocate pool buffer for the found output device handles,
//  and it is the caller's responsibility to safe free the buffer.
//
// Input:
//  IN  EFI_HANDLE  DriverBindingHandle - the handle of a driver which contains
//                                        the binding protocol
//  IN  EFI_HANDLE  ControllerHandle - the device controller handle be opened
//                                     by its child device 
//  OUT UINTN       OutputHandleCount - the number of available device handles
//                                      returned in OutputHandleBuffer.
//  OUT EFI_HANDLE  OutputHandleBuffer - a pointer to the buffer to return
//                                       the array of Output device handles.
//
// Output:
//     EFI_STATUS
//      If returned status is not succeful or find no available device,
//      the *OutputHandleBuffer will be NULL
//
// Modified:
//
// Referrals:
//
// Notes:
//
//----------------------------------------------------------------------------
// <AMI_PHDR_END>

EFI_STATUS
GetOutputDeviceHandlesManagedByDriver (
  IN  EFI_HANDLE    DriverBindingHandle,
  IN  EFI_HANDLE    ControllerHandle,
  OUT UINTN         *OutputHandleCount,
  OUT EFI_HANDLE    **OutputHandleBuffer )
{
    EFI_STATUS      Status;
    UINTN           HandleIndex = 0;

    *OutputHandleCount  = 0;
    *OutputHandleBuffer = NULL;

    Status = GetEdidDiscoveredHandlesManagedByDriver (DriverBindingHandle, ControllerHandle);
    if (OutputHndList.ItemCount) {
        *OutputHandleCount = OutputHndList.ItemCount;
        *OutputHandleBuffer = MallocZ(sizeof(EFI_HANDLE) * (*OutputHandleCount));
        for (HandleIndex = 0; HandleIndex < *OutputHandleCount; HandleIndex++) {
            (*OutputHandleBuffer)[HandleIndex] = *(EFI_HANDLE*)(OutputHndList.Items[HandleIndex]);
        }
    }

    return Status;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------
//
// Procedure:   GetDeviceName
//
// Description: None.
//
// Input:       None.
//
// Output:      None.
//
// Notes:       None.
//
//----------------------------------------------------------------------
//<AMI_PHDR_END>

BOOLEAN
GetDeviceName (
  IN  EFI_HANDLE  DriverBindingHandle,
  IN  EFI_HANDLE  ControllerHandle,
  IN  EFI_HANDLE  ChildControllerHandle,
  OUT CHAR8       *String )
{
    EFI_STATUS                      Status;
    CHAR16                          *DeviceName;
    EFI_COMPONENT_NAME_PROTOCOL     *ComponentName;
    CHAR8                           *Lang = NULL;
    CHAR8                           *TempChar;


    //
    // Get driver name from UEFI 2.0 Component Name 2 protocol interface.
    //
    Status = pBS->OpenProtocol(
                  DriverBindingHandle,
                  &gEfiComponentName2ProtocolGuid,
                  (VOID**)&ComponentName,
                  NULL,
                  NULL,
                  EFI_OPEN_PROTOCOL_GET_PROTOCOL);
    if (!EFI_ERROR(Status)) {
        Status = ComponentName->GetControllerName(ComponentName, ControllerHandle, ChildControllerHandle, LANGUAGE_CODE_ENGLISH, &DeviceName);
        if (EFI_ERROR(Status)) {
            //
            // Driver does not support "en-us", try to get SupportedLanguages
            //
            pBS->AllocatePool(EfiBootServicesData, Strlen(ComponentName->SupportedLanguages)+1, &Lang);
            if (Lang != NULL) {
                Strcpy(Lang, ComponentName->SupportedLanguages);
                TempChar = Strstr(Lang, ";");
                if (TempChar != NULL) *TempChar = 0x0000;
                Status = ComponentName->GetControllerName(ComponentName, ControllerHandle, ChildControllerHandle, Lang, &DeviceName);
                pBS->FreePool(Lang);
                Lang = NULL;
            }
        }
        if (!EFI_ERROR(Status)) {
            Sprintf(String, "%S", DeviceName);
            return TRUE;
        }
    }

    //
    // If it fails to get the driver name from Component Name protocol interface, we should fall back on
    // EFI 1.1 Component Name protocol interface.
    //
    Status = pBS->OpenProtocol(
                  DriverBindingHandle,
                  &gEfiComponentNameProtocolGuid,
                  (VOID**)&ComponentName,
                  NULL,
                  NULL,
                  EFI_OPEN_PROTOCOL_GET_PROTOCOL);
    if (!EFI_ERROR(Status)) {
        Status = ComponentName->GetControllerName(ComponentName, ControllerHandle, ChildControllerHandle, "eng", &DeviceName);
        if (!EFI_ERROR(Status)) {
            Sprintf(String, "%S", DeviceName);
            return TRUE;
        }
    }

    return FALSE;
}

//**********************************************************************
//**********************************************************************
//**                                                                  **
//**        (C)Copyright 1985-2014, American Megatrends, Inc.         **
//**                                                                  **
//**                       All Rights Reserved.                       **
//**                                                                  **
//**      5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093        **
//**                                                                  **
//**                       Phone: (770)-246-8600                      **
//**                                                                  **
//**********************************************************************
//**********************************************************************
