//**********************************************************************
//**********************************************************************
//**                                                                  **
//**        (C)Copyright 1985-2010, American Megatrends, Inc.         **
//**                                                                  **
//**                       All Rights Reserved.                       **
//**                                                                  **
//**           5555 Oakbrook Pkwy, Suite 200, Norcross, GA 30093      **
//**                                                                  **
//**                       Phone: (770)-246-8600                      **
//**                                                                  **
//**********************************************************************
//**********************************************************************

//**********************************************************************
// $Header: /Alaska/SOURCE/Modules/CSM/Generic/Chipset/SouthBridge/LegacyInterrupt.c 14    7/28/10 2:46p Olegi $
//
// $Revision: 14 $
//
// $Date: 7/28/10 2:46p $
//**********************************************************************
// Revision History
// ----------------
// $Log: /Alaska/SOURCE/Modules/CSM/Generic/Chipset/SouthBridge/LegacyInterrupt.c $
// 
// 14    7/28/10 2:46p Olegi
// 
// 13    1/12/10 11:51a Olegi
// Copyright message updated.
//
// 12    10/14/09 12:26p Krishnakumarg
// CloseEvent funtion used instead of a static variable in callback
// routines - EIP 27065
// 
// 11    4/27/07 5:43p Olegi
//
// 10    4/27/07 5:39p Olegi
//
// 9     4/27/07 5:21p Olegi
// CSM.CHM preparations.
//
// 8     10/13/06 12:32a Felixp
// UEFI2.0 compliance: use CreateReadyToBootEvent instead of
// CreateEvent(READY_TO_BOOT)
//
// 7     5/27/05 4:24p Markw
// Added Boot Script.
//
// 6     4/04/05 4:19p Sivagarn
// Updated to latest template format
//
// 2     2/22/05 10:00a Sivagarn
// - Updated to latest labeled CSM & Core
//
// 5     1/18/05 3:22p Felixp
// PrintDebugMessage renamed to Trace
//
// 4     12/09/04 10:59a Olegi
//
// 3     12/06/04 9:37a Olegi
// Added interrupt router registers' buffering.
//
// 2     12/03/04 9:55a Olegi
//
// 1     10/26/04 9:48a Olegi
//
// 3     8/31/04 5:46p Markw
// Fixed bug. Using wrong value to index PirqReg.
//
// 2     8/25/04 4:58p Markw
// Added comments.
//
// 1     8/25/04 3:01p Markw
//
// 1     8/13/04 2:39p Markw
//
//**********************************************************************
//<AMI_FHDR_START>
//
// Name: 8259InterruptController.c
//
// Description: Initialize and provide a protocol to set PIRQ values
//
//<AMI_FHDR_END>
//**********************************************************************

#include <AmiDxeLib.h>
#include <Protocol\PciRootBridgeIo.h>
#include <Protocol\LegacyInterrupt.h>
#include <Protocol\BootScriptSave.h>

extern  UINT8   bMaxPIRQ;
extern  UINT8   bRouterBus;
extern  UINT8   bRouterDevice;
extern  UINT8   bRouterFunction;

EFI_GUID gEfiLegacyInterruptProtocolGuid    = EFI_LEGACY_INTERRUPT_PROTOCOL_GUID;
EFI_GUID gEfiPciRootBridgeIoProtocolGuid    = EFI_PCI_ROOT_BRIDGE_IO_PROTOCOL_GUID;
EFI_GUID gEfiBootScriptSaveGuid             = EFI_BOOT_SCRIPT_SAVE_GUID;

EFI_EVENT   gEvtBootScript;

extern
EFI_STATUS
SBGen_InitializeRouterRegisters (
        EFI_PCI_ROOT_BRIDGE_IO_PROTOCOL *gPciRootBridgeIo);

extern
EFI_STATUS
SBGen_ReadPirq (
    IN EFI_LEGACY_INTERRUPT_PROTOCOL    *This,
    IN UINT8                            PirqNumber,
    OUT UINT8                           *PirqData);

EFI_STATUS
SBGen_WritePirq(
    IN EFI_LEGACY_INTERRUPT_PROTOCOL    *This,
    IN UINT8                            PirqNumber,
    IN UINT8                            PirqData);

EFI_STATUS SBGen_WriteBootScript(
    IN EFI_BOOT_SCRIPT_SAVE_PROTOCOL *BootScriptSave
);

//**********************************************************************
//<AMI_PHDR_START>
//
// Procedure:   GetNumberPirqs
//
// Description:  Return number of supported Pirqs.
//
// Input:
//  IN EFI_LEGACY_INTERRUPT_PROTOCOL    *This
//  OUT UINT8                           *NumberPirqs
//
// Output:
//  Status of the operation
//
// Notes:
//  Here is the control flow of this function:
//  1. Set NumberPirqs to number of supported Pirqs.
//  2. Return EFI_SUCCESS;
//
//<AMI_PHDR_END>
//**********************************************************************
EFI_STATUS GetNumberPirqs(
    IN EFI_LEGACY_INTERRUPT_PROTOCOL    *This,
    OUT UINT8                           *NumberPirqs
    )
{
    *NumberPirqs = bMaxPIRQ;
    return EFI_SUCCESS;
}

//**********************************************************************
//<AMI_PHDR_START>
//
// Procedure:   GetLocation
//
// Description: Return location of device controlling the Pirqs.
//
// Input:
//  IN EFI_LEGACY_INTERRUPT_PROTOCOL    *This
//  OUT UINT8                           *Bus
//  OUT UINT8                           *Device
//  OUT UINT8                           *Function
//
// Output:
//  Status of the operation
//
// Notes:
//  Here is the control flow of this function:
//  1. Set Bus, Device, and Function.
//  2. Return EFI_SUCCESS.
//
//<AMI_PHDR_END>
//**********************************************************************
EFI_STATUS GetLocation(
    IN EFI_LEGACY_INTERRUPT_PROTOCOL    *This,
    OUT UINT8                           *Bus,
    OUT UINT8                           *Device,
    OUT UINT8                           *Function
    )
{
    *Bus        = bRouterBus;
    *Device     = bRouterDevice;
    *Function   = bRouterFunction;
    return EFI_SUCCESS;
}



EFI_LEGACY_INTERRUPT_PROTOCOL gEfiLegacyInterruptProtocol =
{
    GetNumberPirqs, GetLocation,
    SBGen_ReadPirq, SBGen_WritePirq
};

//**********************************************************************
//<AMI_PHDR_START>
//
// Procedure:   CallbackBootScript
//
// Description: Saves the PIRQ registers to Boot Script
//
// Input:
//      IN EFI_EVENT    Event
//      IN VOID         *Context
// Output:
//      None
//
//<AMI_PHDR_END>
//**********************************************************************
VOID CallbackBootScript(IN EFI_EVENT Event, IN VOID *Context)
{
    EFI_BOOT_SCRIPT_SAVE_PROTOCOL *BootScriptSave;
    EFI_STATUS  Status;


    Status = pBS->LocateProtocol(
        &gEfiBootScriptSaveGuid,
        NULL,
        &BootScriptSave
        );
    if (EFI_ERROR(Status)) return;

    SBGen_WriteBootScript(BootScriptSave);
	
    //
    //Kill the Event
	//
    pBS->CloseEvent(Event);

}


//**********************************************************************
//<AMI_PHDR_START>
//
// Procedure:   InitializeLegacyInterrupt
//
// Description: Install Legacy Interrupt Protocol.
//
// Input:
//  IN EFI_HANDLE        ImageHandle
//  IN EFI_SYSTEM_TABLE  *SystemTable
//
// Output:
//  EFI_STATUS
//
// Notes:
//  Here is the control flow of this function:
//  1. Intialize Library.
//  2. Locate PciRootBridgeIo. If error, return error.
//  3. Install Legacy Interrupt protocol.
//  4. Return its Status.
//<AMI_PHDR_END>
//**********************************************************************
EFI_STATUS InitializeLegacyInterrupt(
    IN EFI_HANDLE        ImageHandle,
    IN EFI_SYSTEM_TABLE  *SystemTable
  )
{
    EFI_STATUS                      Status;
    EFI_PCI_ROOT_BRIDGE_IO_PROTOCOL *gPciRootBridgeIo;

    InitAmiLib(ImageHandle, SystemTable);

    Status = pBS->LocateProtocol(
        &gEfiPciRootBridgeIoProtocolGuid,
        NULL,
        &gPciRootBridgeIo
    );
    if (EFI_ERROR(Status)) return Status;

    //Create event for boot script
    Status = CreateReadyToBootEvent(
        TPL_NOTIFY,
        CallbackBootScript,
        NULL,
        &gEvtBootScript
    );
    ASSERT_EFI_ERROR(Status);

    //
    // Initialize router registers buffer
    //
    Status = SBGen_InitializeRouterRegisters (gPciRootBridgeIo);
    if (EFI_ERROR(Status)) return Status;

    return pBS->InstallMultipleProtocolInterfaces(
        &ImageHandle,
        &gEfiLegacyInterruptProtocolGuid, &gEfiLegacyInterruptProtocol,
        NULL
        );
}

//**********************************************************************
//**********************************************************************
//**                                                                  **
//**        (C)Copyright 1985-2010, American Megatrends, Inc.         **
//**                                                                  **
//**                       All Rights Reserved.                       **
//**                                                                  **
//**           5555 Oakbrook Pkwy, Suite 200, Norcross, GA 30093      **
//**                                                                  **
//**                       Phone: (770)-246-8600                      **
//**                                                                  **
//**********************************************************************
//**********************************************************************
