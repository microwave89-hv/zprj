//**********************************************************************
//**********************************************************************
//**                                                                  **
//**        (C)Copyright 1985-2013, American Megatrends, Inc.         **
//**                                                                  **
//**                       All Rights Reserved.                       **
//**                                                                  **
//**         5555 Oakbrook Pkwy, Suite 200, Norcross, GA 30093        **
//**                                                                  **
//**                       Phone: (770)-246-8600                      **
//**                                                                  **
//**********************************************************************
//**********************************************************************
// $Header: /Alaska/SOURCE/Modules/KbcEmulation/ALASKA/KBCEMUL/KbcEmul.c 14    12/04/14 12:49a Rajeshms $
//
// $Revision: 14 $
//
// $Date: 12/04/14 12:49a $
//
//****************************************************************************
// Revision History
// ----------------
// $Log: /Alaska/SOURCE/Modules/KbcEmulation/ALASKA/KBCEMUL/KbcEmul.c $
// 
// 14    12/04/14 12:49a Rajeshms
// [TAG]  		EIP193601
// [Category]  	New Feature
// [Description]  	Aptio4.x - Security Enhancement for SMIHandler in
// KbcEmulation module, Checks if BAR address access is inside SMRAM, if
// yes, return.
// [Files]  		KbcEmul.mak, KbcEmul.c, KbcOhci.c
// 
// 13    9/16/13 6:50a Srikantakumarp
// [TAG]  		EIP135441
// [Category]  	Bug Fix
// [Severity]  	Normal
// [Symptom]  	Option ROM was not getting dispatched in AMD Platforms
// [RootCause]  	Setting the IRQ1 in the Entry Point of the KbcEmulation
// Driver
// [Solution]  	Setting the IRQ1 only if KbcEmulation is Enabled
// [Files]  		KbcEmul.c
// 
// 12    1/09/12 1:24a Rameshr
// [TAG]  		EIP74128
// [Category]  	Improvement
// [Description]  	Disable the KbcEmulation Smi’s on ACPI enable and
// Disable SMI call
// [Files]  		Kbccore.c, KbcEmuulAcpi.c, KbcEmul.c, KbcEmul.cif,
// KbcEmul.h, KbcEmul.sdl
// 
// 11    5/02/11 12:16a Rameshr
// [TAG] - EIP 58434 
// [Category]- BUG FIX
// [Severity]- Major
// [Symptom] - IRQ1 not enabled on LegacyFree(No KBC) system while booting
// to Legacy OS.
// [RootCause]- As there is no KBC, IRQ1 not used by system and it's not
// enabled.
// [Solution] - When the Emulation module enabled, IRQ1 is added to the
// used IRQ list.So it's enabled while booting to Legacy OS.
// [Files] - KbcEmul.c
// 
// 10    4/11/11 2:46a Rameshr
// [TAG]- EIP 57436
// [Category]-IMPROVEMENT
// [Description]- PI1.1 Support.
// [Files]- Ap4x.h, KbcEmul.c
// 
// 9     2/10/11 12:57a Rameshr
// [TAG]  		EIP53687
// [Category]  	Improvement
// [Description]  	AMI headers update for KbcEmulation Module 
// [Files]  		KbcEmul.mak,KbcEmul.dxs,KbcEmul.c,KbcEmul.h,KbcEmulLib.h,Kbc
// EmulLib.c,Kbc.h,KbcDevEmul.h,Kbccore.c,Legacykbc.c,Legacykbd.c,LegacyMo
// use.c,VirtualKbc.c,VirtualKbd.c,VirtualMouse.c,Ap4x.h,Ap4x.c,KbcUhci.c,
// KbcUhci.h,KbcEmulIrq.c, KbcOhci.c, Kbcohci.h
// 
// 8     7/08/10 1:57a Rameshr
// Ohci Emulation support Added.
// EIP 39712
// 
// 7     6/30/09 11:28a Rameshr
// Coding Standard and File header updated.
// 
// 6     2/05/09 9:37a Rameshr
// Symptom : With Latest CSM Emulation doesn't work.
// Solution: Added Emulation enable code in outside SMM. This is called
// from Uhcd.c when ever USB mode changes to Legacy
// EIP:18730
// 
// 5     10/24/08 11:55a Rameshraju
// KBC presence done only based on 0xFF value.
// 
// 3     8/11/08 12:33p Vasudevans
// 
// 4     8/07/08 10:21a Rameshraju
// Removed the IRQ1 changes
// 
// 3     7/08/08 11:09a Rameshraju
// IRQ1 unmasked.
// 
// 2     12/27/07 4:53p Rameshraju
// Detect the KBC presence by reading port 64
// 
// 1     12/14/07 10:26a Rameshraju
// Initial Check-in
//****************************************************************************

//<AMI_FHDR_START>
//****************************************************************************
// Name:  KbcEmul.c
//
// Description: KBC emulation driver entry point and initilize the SMI for port 6064
//****************************************************************************
//<AMI_FHDR_END>

#include "KbcEmul.h"
#include "Kbc.h"
#include "KbcDevEmul.h"
#ifdef FRAMEWORK_AP4
#include "token.h"
#include "protocol/usbpolicy.h"
#else
#include "tokens.h"
#endif

#include <AmiBufferValidationLib.h>

extern  EFI_GUID    gEfiLoadedImageProtocolGuid;
extern  EFI_GUID    gEfiDevicePathProtocolGuid;
extern  EFI_GUID    gEfiSetupGuid;


EFI_CPU_IO_PROTOCOL *CpuIo;
KBC*    gVirtualKBC = NULL;
void    Emulation_Init();
void    Smm_Register();

//
//KBC Emulation TRAP protocol.
//
BOOLEAN     Emulation6064TrapEnable(EFI_EMUL6064TRAP_PROTOCOL *This);
BOOLEAN     Emulation6064TrapDisable(EFI_EMUL6064TRAP_PROTOCOL *This);
UINT32      KbcEmulationFeature (EFI_EMUL6064TRAP_PROTOCOL * This);
BOOLEAN     NonSmmEmulation6064TrapEnable(EFI_EMUL6064TRAP_PROTOCOL *This);
BOOLEAN     NonSmmEmulation6064TrapDisable(EFI_EMUL6064TRAP_PROTOCOL *This);

EFI_EMUL6064TRAP_PROTOCOL       Emulation6064Trap= {
    Emulation6064TrapEnable,
    Emulation6064TrapDisable,
    KbcEmulationFeature
};

EFI_EMUL6064TRAP_PROTOCOL       NonSmmEmulation6064Trap= {
    NonSmmEmulation6064TrapEnable,
    NonSmmEmulation6064TrapDisable,
    KbcEmulationFeature
};

EFI_HANDLE      EmulationTrapHandle=NULL;


EFI_DRIVER_ENTRY_POINT(EmulationEntryPoint)


//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   EmulationEntryPoint
//
// Description: Entry point for Emulation driver. If the port 6064 emulation enabled by setup 
//              it enables the SMI event for port 6064 and install the Trap handle protocol.    
//
//
// Input:       Standard EFI Image entry - EFI_IMAGE_ENTRY_POINT
//
// Output:      Status: EFI_SUCCESS = Success
//                      EFI_ERROR = Failure
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS
EmulationEntryPoint(
    IN EFI_HANDLE ImageHandle,
    IN EFI_SYSTEM_TABLE *SystemTable
)
{
    EFI_STATUS                  Status      = 0;
    UINTN                       VariableSize;
    BOOLEAN                     InSmm     = 0;
    USB_SUPPORT_SETUP           SetupData;

    //
    // Initialize the EFI Runtime Library
    //
    initializeLib(ImageHandle, SystemTable);


    //
    //Check the setup option, if the emulation disabled in setup return with EFI_SUCCESS
    //
    VariableSize = sizeof(USB_SUPPORT_SETUP);
    Status = pRS->GetVariable( L"UsbSupport", &gEfiSetupGuid, NULL, &VariableSize, &SetupData );

    if (EFI_ERROR(Status) || (SetupData.UsbEmul6064 == 0)) {
        return EFI_SUCCESS;
    }

    //
    // Save the system table pointer
    //
    gSMM->GetSmstLocation (gSMM, &gSmst);

    //
    // Find out whether we're in SMM
    //
    gSMM->InSmm (gSMM, &InSmm);

    if (!InSmm) {
        EFI_HANDLE                  hSmmCode = NULL;
        EFI_DEVICE_PATH_PROTOCOL    *FilePath;
        EFI_LOADED_IMAGE_PROTOCOL   *LoadedImage;
        EFI_DEVICE_PATH_PROTOCOL    *ImageDevicePath;

        //
        // Load this driver's image to memory
        //

        Status = gBS->HandleProtocol(
                                    ImageHandle, &gEfiLoadedImageProtocolGuid, &LoadedImage);
        if (EFI_ERROR(Status)) return Status;

        Status = gBS->HandleProtocol(
            LoadedImage->DeviceHandle, &gEfiDevicePathProtocolGuid, (VOID*)&ImageDevicePath
        );
        if (EFI_ERROR(Status)) return Status;

        Status = gBS->LocateProtocol (&gEfiCpuIoProtocolGuid, NULL, &CpuIo);

        if (EFI_ERROR(Status)) return Status;

        gBS->InstallProtocolInterface(&EmulationTrapHandle,
                                      &gNonSmmEmul6064TrapProtocolGuid,EFI_NATIVE_INTERFACE,&NonSmmEmulation6064Trap);

        FilePath = AppendDevicePath(
                                    ImageDevicePath, LoadedImage->FilePath
                                    );

        //
        // Load the image in memory to SMRAM; it will automatically generate SMI.
        //
        Status = gSMM->Register(gSMM, FilePath, NULL, 0, &hSmmCode, FALSE);
    }else {
        //
        // We're now in SMM, registering all USB SMM callback functions
        //
#if OHCI_EMUL_SUPPORT
        InitAmiBufferValidationLib(ImageHandle, SystemTable);
#endif
        Emulation_Init();

        gBS->InstallProtocolInterface(&EmulationTrapHandle,
                                      &gEmul6064TrapProtocolGuid,EFI_NATIVE_INTERFACE,&Emulation6064Trap);
        RegisterAcpiEnableCallBack();
    }

    return EFI_SUCCESS;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   Emulation_Init
//
// Description: Initilize the Keyboard Controller, Keyboard and Mouse device.Regsiter the SMI for port 6064
//              access.
//
// Input:       None
//
// Output:      None
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
void Emulation_Init()
{
    static      VIRTKBC     VirtualKBC;
    static      VIRTMOUSE   VirtualMouse;
    static      VIRTKBD     VirtualKbd;
    static      LEGACYKBC       LegacyKbc;
    static      LEGACYKBD       LegacyKbd;
    static      LEGACYMOUSE LegacyMouse;
    BOOLEAN     KbcPresent=FALSE;
    UINT8       port64 = IoRead8(0x64);


    //
    //Detect the KBC presence by reading port 64.
    //    
    KbcPresent = ((port64==0xFF))? 0 : 1; 

    if(KbcPresent) {

        gVirtualKBC = &LegacyKbc.kbc_;

        //
        //Initialize the Legacy Mouse Device
        //
        InitLegacyMouse(gVirtualKBC,&LegacyMouse);

        //
        //Initialize the Legacy Keyboard Device
        //
        InitLegacyKbd(gVirtualKBC,&LegacyKbd);

        //
        //Initialize the Legacy Keyboard Controller
        //
        InitLegacyKBC(&LegacyKbc,&LegacyKbd.sink,&LegacyMouse.sink);


    } else {

        gVirtualKBC = &VirtualKBC.kbc;

        //
        //Initialize the Virtual Mouse Device
        //
        InitVirtualMouse(gVirtualKBC,&VirtualMouse);

        //
        //Initialize the Virtual Keyboard Device
        //
        InitVirtualKbd(gVirtualKBC,&VirtualKbd);

        //
        //Initialize the Virtual Keyboard Controller
        //
        InitVirtualKBC(&VirtualKBC,&VirtualKbd.sink,&VirtualMouse.sink);

    }

    //
    // Hardware specific SMM registration
    Smm_Register();

    return;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   Emulation6064TrapEnable
//
// Description: Enable the SMI source for port 6064
//
// Input:       None
//
// Output:      TRUE/FALSE
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
BOOLEAN
Emulation6064TrapEnable (
    EFI_EMUL6064TRAP_PROTOCOL           * This
    )
{
    return TrapEnable(TRUE);
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   Emulation6064TrapDisable
//
// Description: Disable the SMI source for port 6064
//
// Input:       None
//
// Output:      TRUE/FALSE
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
BOOLEAN
Emulation6064TrapDisable (
    EFI_EMUL6064TRAP_PROTOCOL           * This
    )
{
    return TrapEnable(FALSE);
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   NonSmmEmulation6064TrapEnable
//
// Description: Enable the SMI source for port 6064 in Non SMM
//
// Input:       None
//
// Output:      None
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
BOOLEAN
NonSmmEmulation6064TrapEnable (
    EFI_EMUL6064TRAP_PROTOCOL           * This
    )
{
    UINT16      IrqMask;
    EFI_STATUS  Status;

    //
    // Reserve IRQ1 if the Emulation enabled
    //
    Status=AmiIsaIrqMask(&IrqMask, TRUE);

    if(Status==EFI_NOT_FOUND){
        IrqMask=ISA_IRQ_MASK;
        IrqMask |= 2;
        AmiIsaIrqMask(&IrqMask, FALSE);
    } else {
        IrqMask |= 2;
        AmiIsaIrqMask(&IrqMask, FALSE);
    }

    return NonSmmTrapEnable(TRUE);
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   NonSmmEmulation6064TrapDisable
//
// Description: Disable the SMI source for port 6064 in Non SMM
//
// Input:       None
//
// Output:      None
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
BOOLEAN
NonSmmEmulation6064TrapDisable (
    EFI_EMUL6064TRAP_PROTOCOL           * This
    )
{
    return NonSmmTrapEnable(FALSE);
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   KbcEmulationFeature
//
// Description: Returns all the feature supported by Emulation
//
// Input:       None
//
// Output:      None
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
UINT32
KbcEmulationFeature (
    EFI_EMUL6064TRAP_PROTOCOL           * This
    )
{
    UINT32          KbcEmulFeature=0;

#if IRQ_EMUL_SUPPORT
    KbcEmulFeature |= IRQ_SUPPORTED;
#endif
    return  KbcEmulFeature;
}

//**********************************************************************
//**********************************************************************
//**                                                                  **
//**        (C)Copyright 1985-2013, American Megatrends, Inc.         **
//**                                                                  **
//**                       All Rights Reserved.                       **
//**                                                                  **
//**         5555 Oakbrook Pkwy, Suite 200, Norcross, GA 30093        **
//**                                                                  **
//**                       Phone: (770)-246-8600                      **
//**                                                                  **
//**********************************************************************
//**********************************************************************
