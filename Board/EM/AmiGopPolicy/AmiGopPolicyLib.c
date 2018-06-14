//**********************************************************************
//**********************************************************************
//**                                                                  **
//**        (C)Copyright 1985-2012, American Megatrends, Inc.         **
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
// $Header: /Alaska/SOURCE/Modules/AmiGopPolicy/AmiGopPolicyLib.c 9     12/18/12 11:04p Josephlin $
//
// $Revision: 9 $
//
// $Date: 12/18/12 11:04p $
//**********************************************************************
// Revision History
// ----------------
// $Log: /Alaska/SOURCE/Modules/AmiGopPolicy/AmiGopPolicyLib.c $
// 
// 9     12/18/12 11:04p Josephlin
// [TAG]  		EIP108311
// [Category]  	Improvement
// [Description]  	Create eLINK "OemGopEdidOverrideGetEdidList" for easy
// to implement EdidOverrideProtocol in project.
// [Files]  		AmiGopPolicy.c
// AmiGopPolicy.sdl
// AmiGopPolicy.mak
// AmiGopPolicyLib.c
// 
// 8     10/29/12 5:53a Josephlin
// [TAG]  		EIP103432
// [Category]  	Bug Fix
// [Severity]  	Normal
// [Symptom]  	System hang up druing display switching with external GOP
// card.
// [RootCause]  	Compiler optimize issue.
// [Solution]  	Using the optimize pragma to prevent system hang up druing
// display switching.
// 
// 7     8/23/12 5:50a Josephlin
// Change eLink handling processing to consider the hierarchy of
// xxxxxHookList. This is able to avoid that get incorrect status.
// 
// 6     8/23/12 2:41a Josephlin
// Remove unnecessary conditionally including to fix build fail problem if
// CSM_SUPPORT = OFF.
// 
// 5     7/30/12 5:31a Josephlin
// Removed bus number checking in AmiDefaultGopDeviceCheck() to consider
// the DSC-only platform supporting.
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
// 1     6/29/12 3:44a Josephlin
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
// Name:        AmiGopPolicyLib.c
//
// Description:	AmiGopPolicy initialization code in the Library stage
//
//<AMI_FHDR_END>
//**********************************************************************

//----------------------------------------------------------------------
// Include(s)
//----------------------------------------------------------------------

#include <Efi.h>
#include <AmiLib.h>
#include <AmiDxeLib.h>
#include <AmiCspLib.h>
#include <Setup.h>
#include <token.h>
#include <AmiLoadCsmPolicy.h>

#include <Protocol\DevicePath.h>
#if OEM_EDID_OVERRIDE_PROTOCOL_SUPPORT
#include <Protocol\EdidOverride.h>
#endif

//----------------------------------------------------------------------
// Constant, Macro and Type Definition(s)
//----------------------------------------------------------------------
// Constant Definition(s)

// Macro Definition(s)

// Type Definition(s)

typedef EFI_STATUS (OEM_GOP_DEVICE_CHECK) (
    IN  EFI_HANDLE                  ControllerHandle, 
    IN  EFI_HANDLE                  DriverBindingHandle,
    IN  EFI_PCI_IO_PROTOCOL         *PciIo
);

typedef EFI_STATUS (OEM_GOP_SWITCH_HOOK) (
    IN  EFI_HANDLE                  ControllerHandle, 
    IN  EFI_HANDLE                  DriverBindingHandle,
    IN  SETUP_DATA                  *SetupData,
    IN  EFI_DEVICE_PATH_PROTOCOL    *DevicePath
);

#if OEM_EDID_OVERRIDE_PROTOCOL_SUPPORT
typedef EFI_STATUS (OEM_GOP_EDID_OVERRIDE_GET_EDID) (
  IN  EFI_EDID_OVERRIDE_PROTOCOL    *This,
  IN  EFI_HANDLE                    *ChildHandle,
  OUT UINT32                        *Attributes,
  IN OUT UINTN                      *EdidSize,
  IN OUT UINT8                      **Edid
);
#endif

extern OEM_GOP_DEVICE_CHECK             OEM_GOP_DEVICE_CHECK_LIST           EndOfOemGopDeviceCheckList;
extern OEM_GOP_SWITCH_HOOK              OEM_GOP_SWITCH_HOOK_LIST            EndOfOemGopSwitchHookList;
#if OEM_EDID_OVERRIDE_PROTOCOL_SUPPORT
extern OEM_GOP_EDID_OVERRIDE_GET_EDID   OEM_GOP_EDID_OVERRIDE_GET_EDID_LIST EndOfOemGopEdidOverrideGetEdidList;
#endif

// Function Prototype(s)

EFI_STATUS ConnectGopDevicePath (
  IN  EFI_HANDLE                DriverBindingHandle,
  IN  EFI_DEVICE_PATH_PROTOCOL  *pPath );

//----------------------------------------------------------------------
// Variable and External Declaration(s)
//----------------------------------------------------------------------
// Variable Declaration(s)

OEM_GOP_DEVICE_CHECK*           OemGopDeviceCheckList[] = {OEM_GOP_DEVICE_CHECK_LIST NULL};
OEM_GOP_SWITCH_HOOK*            OemGopSwitchHookList[] = {OEM_GOP_SWITCH_HOOK_LIST NULL};
#if OEM_EDID_OVERRIDE_PROTOCOL_SUPPORT
OEM_GOP_EDID_OVERRIDE_GET_EDID* OemGopEdidOverrideGetEdidList[] = {OEM_GOP_EDID_OVERRIDE_GET_EDID_LIST NULL};
#endif

// GUID Definition(s)

static EFI_GUID gAmiCsmThunkProtocolGuid = AMI_CSM_THUNK_PROTOCOL_GUID;

// Protocol Definition(s)

// External Declaration(s)

// Function Definition(s)

//----------------------------------------------------------------------

#pragma optimize("", off)

//<AMI_PHDR_START>
//----------------------------------------------------------------------
// Name:        AmiGopDeviceCheck
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
AmiGopDeviceCheck (
    IN  EFI_HANDLE                  ControllerHandle,
    IN  EFI_HANDLE                  DriverBindingHandle,
    IN  EFI_PCI_IO_PROTOCOL         *PciIo )
{
    EFI_STATUS  Status = EFI_SUCCESS;
    UINTN       i;

    for (i = 0; OemGopDeviceCheckList[i] != NULL; i++) {
        Status = OemGopDeviceCheckList[i] (ControllerHandle, DriverBindingHandle, PciIo);
        if(!EFI_ERROR(Status)) break;
    }

    return Status;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------
// Name:        AmiDefaultGopDeviceCheck
//
// Description: Check if this VGA supports Display Switching function.
//
// Input:       IN  EFI_HANDLE              ControllerHandle
//              IN  EFI_HANDLE              DriverBindingHandle
//              IN  EFI_PCI_IO_PROTOCOL     *PciIo
//
// Output:      None.
//
// Notes:       Display Switching function may failed because the GOP
//              Driver is not supporting. Please contact VGA vendor to
//              check for this function supporting.
//
//----------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS
AmiDefaultGopDeviceCheck (
    IN  EFI_HANDLE                  ControllerHandle, 
    IN  EFI_HANDLE                  DriverBindingHandle,
    IN  EFI_PCI_IO_PROTOCOL         *PciIo )
{
    EFI_STATUS  Status;
    UINT8       PciClassCode;

    if (!PciIo) return EFI_INVALID_PARAMETER;

    // Check if this is ThunkDriver
    Status = pBS->OpenProtocol(
                  DriverBindingHandle,
                  &gAmiCsmThunkProtocolGuid,
                  NULL,
                  NULL,
                  NULL,
                  EFI_OPEN_PROTOCOL_TEST_PROTOCOL);
    if (!EFI_ERROR(Status)) return EFI_UNSUPPORTED;

    // Check if this is VGA controller
    Status = PciIo->Pci.Read (PciIo, EfiPciIoWidthUint8, PCI_BCC, 1, &PciClassCode);
    if (EFI_ERROR(Status) || (PciClassCode != PCI_CL_DISPLAY)) return EFI_UNSUPPORTED;

    return EFI_SUCCESS;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------
// Name:        AmiGopSwitchHook
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
AmiGopSwitchHook (
    IN  EFI_HANDLE                  ControllerHandle, 
    IN  EFI_HANDLE                  DriverBindingHandle,
    IN  SETUP_DATA                  *SetupData,
    IN  EFI_DEVICE_PATH_PROTOCOL    *DevicePath )
{
    EFI_STATUS  Status = EFI_SUCCESS;
    UINTN       i;

    for (i = 0; OemGopSwitchHookList[i] != NULL; i++) {
        Status = OemGopSwitchHookList[i] (ControllerHandle, DriverBindingHandle, SetupData, DevicePath);
        if(!EFI_ERROR(Status)) break;
    }

    return Status;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------
// Name:        AmiDefaultGopSwitchFunction
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
AmiDefaultGopSwitchFunction (
    IN  EFI_HANDLE                  ControllerHandle, 
    IN  EFI_HANDLE                  DriverBindingHandle,
    IN  SETUP_DATA                  *SetupData,
    IN  EFI_DEVICE_PATH_PROTOCOL    *DevicePath )
{
    EFI_STATUS  Status = EFI_SUCCESS;

    Status = pBS->DisconnectController (ControllerHandle, NULL, NULL);
    Status = ConnectGopDevicePath(DriverBindingHandle, DevicePath);

    return Status;
}

#if OEM_EDID_OVERRIDE_PROTOCOL_SUPPORT
//<AMI_PHDR_START>
//----------------------------------------------------------------------
// Name:        AmiGopEdidOverrideGetEdid
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
AmiGopEdidOverrideGetEdid (
  IN  EFI_EDID_OVERRIDE_PROTOCOL    *This,
  IN  EFI_HANDLE                    *ChildHandle,
  OUT UINT32                        *Attributes,
  IN OUT UINTN                      *EdidSize,
  IN OUT UINT8                      **Edid )
{
    EFI_STATUS  Status = EFI_SUCCESS;
    UINTN       i;

    for (i = 0; OemGopEdidOverrideGetEdidList[i] != NULL; i++) {
        Status = OemGopEdidOverrideGetEdidList[i] (This, ChildHandle, Attributes, EdidSize, Edid);
        if(!EFI_ERROR(Status)) break;
    }

    return Status;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------
// Name:        AmiDefaultGopEdidOverrideGetEdid
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
AmiDefaultGopEdidOverrideGetEdid (
  IN  EFI_EDID_OVERRIDE_PROTOCOL    *This,
  IN  EFI_HANDLE                    *ChildHandle,
  OUT UINT32                        *Attributes,
  IN OUT UINTN                      *EdidSize,
  IN OUT UINT8                      **Edid )
{
    EFI_STATUS  Status = EFI_UNSUPPORTED;

    return EFI_UNSUPPORTED;
}
#endif

#pragma optimize("", on)

//<AMI_PHDR_START>
//----------------------------------------------------------------------
// Name:        ConnectGopDevicePath
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
ConnectGopDevicePath (
  IN  EFI_HANDLE                DriverBindingHandle,
  IN  EFI_DEVICE_PATH_PROTOCOL  *pPath )
{
    EFI_HANDLE Handle;
    EFI_STATUS Status;
    EFI_STATUS ConnectStatus = EFI_UNSUPPORTED;

    if (pPath == NULL) return EFI_INVALID_PARAMETER;
	while (TRUE)
	{
		EFI_DEVICE_PATH_PROTOCOL *pLastPath=NULL, *pFirstNode = pPath;
		if (isEndNode(pPath))
		{
			if (pPath->SubType == END_ENTIRE_SUBTYPE) break;
			pPath++;
			continue;
		}
		while(TRUE){
            EFI_DEVICE_PATH_PROTOCOL *Dp;
            UINT8 SubType;

	        pPath = pFirstNode;

            //LocateDevicePath can not work with multi-instance device paths.
            //Prepare single instance device path and call LocateDevicePath
            Dp = DPGetEndNode(pPath);
	        SubType = Dp->SubType;
	        Dp->SubType=END_ENTIRE_SUBTYPE;
            Status = pBS->LocateDevicePath(&gEfiDevicePathProtocolGuid, &pPath, &Handle);
            Dp->SubType=SubType;
			if (EFI_ERROR(Status)) break;

			if (pPath==pLastPath) break;
			pLastPath = pPath;
            ConnectStatus = pBS->ConnectController(Handle, &DriverBindingHandle, pPath, TRUE);
			if (EFI_ERROR(ConnectStatus)) break;
            else return ConnectStatus;
		}
		while (!isEndNode(pPath))
			pPath = NEXT_NODE(pPath);
	}

    return ConnectStatus;
}

//**********************************************************************
//**********************************************************************
//**                                                                  **
//**        (C)Copyright 1985-2012, American Megatrends, Inc.         **
//**                                                                  **
//**                       All Rights Reserved.                       **
//**                                                                  **
//**      5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093        **
//**                                                                  **
//**                       Phone: (770)-246-8600                      **
//**                                                                  **
//**********************************************************************
//**********************************************************************
