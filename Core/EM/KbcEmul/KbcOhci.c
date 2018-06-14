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
//**********************************************************************
// $Header: /Alaska/SOURCE/Modules/KbcEmulation/ALASKA/KBCEMUL/KbcOhci.c 7     12/04/14 12:51a Rajeshms $
//
// $Revision: 7 $
//
// $Date: 12/04/14 12:51a $
//
//***********************************************************************
// Revision History
// ----------------
// $Log: /Alaska/SOURCE/Modules/KbcEmulation/ALASKA/KBCEMUL/KbcOhci.c $
// 
// 7     12/04/14 12:51a Rajeshms
// [TAG]  		EIP193601
// [Category]  	New Feature
// [Description]  	Aptio4.x - Security Enhancement for SMIHandler in
// KbcEmulation module, Checks if BAR address access is inside SMRAM, if
// yes, return.
// [Files]  		KbcEmul.mak, KbcEmul.c, KbcOhci.c
// 
// 6     12/05/13 12:46a Srikantakumarp
// [TAG]  		EIP145881
// [Category]  	Improvement
// [Description]  	Ohci Emulation support needs to be extended for the
// chipset , where the HCE registers defined in some fixed Memory for
// Aptio 4.x
// [Files]  		KbcEmul.sdl, KbcOhci.c, KbcOhci.h
// 
// 5     5/13/13 2:52a Rameshr
// [TAG]  		EIP119870
// [Category]  	Improvement
// [Description]  	Build error with KbcEmulation module if update USB
// module label 4.6.3_USB_08.10.26
// [Files]  		KbcEmul.Mak, KbcEmul.SDl, KbcUhci.c, KbcUhci.h, KbcOhci.c
// 
// 4     2/02/12 12:36a Rameshr
// [TAG]  		EIP80605
// [Category]  	Bug Fix
// [Severity]  	Important
// [Symptom]  	It can not boot to DOS, If to disable 1st TOKEN report OHCI
// by setup on legacy free system(must add KBC Emulation module).
// [RootCause]  	gOHCIBar gets value from disabled controller and its not
// valid value
// [Solution]  	Added condition to check to have valid value in gOHCIBar
// [Files]  		KbcOhci.c
// 
// 3     7/14/11 12:28a Rameshr
// [TAG] - EIP 62672
// [Category]- BUG FIX
// [Severity]- Minor
// [Symptom] - USB PEI (enable KBC emulation) can't boot from USB
// [RootCause]- KbcEmulation gets the wrong BAR address that was
// initilized by USB PEI driver 
// [Solution] - Ohci Base address reading should be done after the PCIbus
// driver allocates the resource for the OHCI controller
// [Files] - KbcOhci.c
// 
// 2     2/10/11 1:14a Rameshr
// [TAG]  		EIP53687
// [Category]  	Improvement
// [Description]  	AMI headers update for KbcEmulation Module
// [Files]  		KbcEmul.mak,KbcEmul.dxs,KbcEmul.c,KbcEmul.h,KbcEmulLib.h,Kbc
// EmulLib.c,Kbc.h,KbcDevEmul.h,Kbccore.c,Legacykbc.c,Legacykbd.c,LegacyMo
// use.c,VirtualKbc.c,VirtualKbd.c,VirtualMouse.c,Ap4x.h,Ap4x.c,KbcUhci.c,
// KbcUhci.h,KbcEmulIrq.c, KbcOhci.c, Kbcohci.h
// 
// 1     7/08/10 2:07a Rameshr
// Ohci Emulation support Added.
// EIP 39712
// 
// Initial Check-in
//
//**********************************************************************

//**********************************************************************
//<AMI_FHDR_START>
//
// Name:        KbcOhci.c
//
// Description: Handles the SMI events for port 60/64
//
//<AMI_FHDR_END>
//**********************************************************************

#ifdef FRAMEWORK_AP4
#include "token.h"
#else
#include "tokens.h"
#endif
#include "KbcEmul.h"
#include "KbcDevEmul.h"
#include "KbcOhci.h"
#include "KbcEmulLib.h"
#include "Kbc.h"

#include <AmiBufferValidationLib.h>

extern KBC*     gVirtualKBC;

//Carries the LEGKEY status information saved before enable/disable trapping from outside trap handler is
//performed; The saving of the status allows recovering legacy I/O accesss event in case when multiple
//sources are serviced at signle SMI# ( legacy I/O and USB keyboard interupt, for example)

static BOOLEAN  gInTrapHandler = FALSE;
BOOLEAN         KBDDisabled = FALSE;

OHCI_EMUL_DEVICE Ohci_Hc_Array[] = { OHCI_EMUL_PCI_DEVICES };
UINTN Ohci_Hc_Array_Size = sizeof(Ohci_Hc_Array) / sizeof(Ohci_Hc_Array[0]);

volatile OHCI_LEG_SUP_REGS	*gLegSupRegs = NULL;

void DisableLegKeyRegs();
void trap64w();
void trap60w();
void trap64r();
void trap60r();
UINT8 GetHceInput();
void SetHceOutput (UINT8 Data);
BOOLEAN KBC_WaitForOutputBufferToBeFilled();
BOOLEAN CheckPS2KBDMouseIRQEnabled();
void CheckNumberofResponseBytes ();
void WaitForOBFSMM();
void SerialOutput (UINT8 Data);
BOOLEAN gClearCharacterPending = FALSE;
BOOLEAN MouseCmdInProgress = FALSE;

// cmd, response, cmd, response ... 0
UINT8 KBDCmdResponse[] =   {0xF2, 3, 0xFF, 2, 0xF0, 1, 0xF3, 1, 0xF4, 1, 0xF5, 1, 0xF6, 1, 0xF7, 1, 0xF8, 1, 0xF9, 1, 0xFA, 1, 0xFB, 1, 0xFC, 1, 0xFD, 1, 0};
UINT8 MouseCmdResponse[] = {0xFF, 3, 0xF2, 2, 0xE9, 4, 0xEb, 4, 0xE6, 1, 0xE7, 1, 0xE8, 1, 0xEA, 1, 0xEE, 1, 0xF0, 1, 0xF3, 1, 0xF4, 1, 0xF5, 1, 0};
UINT8 ResponseBytes = 0;

//status bits for SMI#, parenthesis is needed for ~ or other conversion
#define OHCI_TRAPBY_MASK        (HCE_CNTRL_EMULATION_INTERRUPT)

//enable bits for traps
#define OHCI_TRAPEN_MASK        (HCE_CNTRL_EMULATION_ENABLE | HCE_CNTRL_EXT_IRQ_ENABLE)

void Trap6064_Handler (
  IN  EFI_HANDLE                    DispatchHandle,
  IN  EFI_SMM_USB_DISPATCH_CONTEXT  * DispatchContext
  );

void Trap6064_Handler_LegFree (
  IN  EFI_HANDLE                    DispatchHandle,
  IN  EFI_SMM_USB_DISPATCH_CONTEXT  * DispatchContext
  );

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   Smm_Register
//
// Description: Enable the SMI for port 6064 access.
//
// Input:       None
//
// Output:      None
//
// Note :       Called inside SMM
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
void Smm_Register()
{
    EFI_SMM_USB_DISPATCH_CONTEXT    context;
    EFI_SMM_USB_DISPATCH_PROTOCOL*  pDispatch;
    EFI_HANDLE hDisp;
    EFI_STATUS Status;
    static FULL_USB_DEVICE_PATH hc_dp =  USB1_1_DEVICE_PATH;
    UINTN OhciCount;

    //
    // Register the USB HW SMI handler
    //
    Status = gBS->LocateProtocol(&gEfiSmmUsbDispatchProtocolGuid, NULL, &pDispatch);
    ASSERT_EFI_ERROR(Status);

    //
    // SMI registration routines will install the handlers, set enable bit
    // and clear status in PM IO space.
    //
    for( OhciCount = 0; OhciCount < Ohci_Hc_Array_Size; ++OhciCount ){
        hc_dp.pci.Device=(Ohci_Hc_Array[OhciCount].BusDevFunc >> 3);
        hc_dp.pci.Function=(Ohci_Hc_Array[OhciCount].BusDevFunc & 07);
        context.Type = UsbLegacy;
        context.Device = (EFI_DEVICE_PATH_PROTOCOL *)&hc_dp;
        if (IoRead8(0x64) == 0xFF) {
            Status = pDispatch->Register(pDispatch,Trap6064_Handler_LegFree, &context, &hDisp);
        } else {
            Status = pDispatch->Register(pDispatch,Trap6064_Handler, &context, &hDisp);
        }
    }

    //The SMI source for the port6064 is disabled. it will be enabled when we are in legacy enviorment.
    //EFI enviorment Emulation is Disabled.
    DisableLegKeyRegs();
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   DisableLegKeyRegs
//
// Description: Disable the port6064 SMI source based on the Trap enable mask.
//
// Input:       None
//
// Output:      None
//
// Note :       Called inside SMM
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
void DisableLegKeyRegs()
{

    if (gLegSupRegs != NULL) {
        gLegSupRegs->HceControl = 0;
    }

    return;

}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   HandleGA20Sequence
//
// Description: SMI triggered becauase of GA20 sequence change
//
// Input:       None
//
// Output:      None
//
// Note :       Called inside SMM
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID HandleGA20Sequence()
{
    UINT8   Data;

    if (IoRead8(0x64) == 0xFF) {
        //
        //Legacy Free system. Handle it using PORT 92
        //
        Data = GetHceInput();
        IoWrite8(0x92, (IoRead8(0x92) & 0xFD) | (Data & 0x2));
        SetHceControl(GetHceControl() & 0xFFFFFE3F | ((Data & 0x2) << 7));
    }
    else {
        //
        //Legacy Free system. Handle it using PORT 92. Maybe need to be chnaged if KBC needs to be used.
        //
        Data = GetHceInput();
        IoWrite8(0x92, (IoRead8(0x92) & 0xFD) | (Data & 0x2));
        SetHceControl(GetHceControl() & 0xFFFFFE3F | ((Data & 0x2) << 7));
    }
    ((VIRTKBC* )gVirtualKBC)->st_ = 0x1c;

    return;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   Trap6064_Handler_LegFree
//
// Description: SMI handler to handle the 64write, 64read, 60 write and 60 read SMI.
//
// Input:       DispatchHandle  - EFI Handle
//              DispatchContext - Pointer to the EFI_SMM_SW_DISPATCH_CONTEXT

// Output:      None
//
// Note :   Called inside SMM
//          Used only when KBC is NOT present on the system
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
void Trap6064_Handler_LegFree (
  IN  EFI_HANDLE                    DispatchHandle,
  IN  EFI_SMM_USB_DISPATCH_CONTEXT  * DispatchContext
  )
{
    UINT8 LegacyStatus;
    UINTN OhciCount;
    volatile EFI_PHYSICAL_ADDRESS   OHCIBar = 0;
    VIRTKBD* kbd = (VIRTKBD*)gVirtualKBC->kbd_dev;
    VIRTMOUSE* mouse = (VIRTMOUSE*)gVirtualKBC->mouse_dev;

    ((VIRTKBC* )gVirtualKBC)->DelaySendingDataCmd = FALSE;

    //
    // check if gOHCIBar has a valid address
    //
    if (gLegSupRegs == NULL) {
        for( OhciCount = 0; OhciCount < Ohci_Hc_Array_Size; ++OhciCount ){
			if (Ohci_Hc_Array[OhciCount].Type == PciDevice) {
            	OHCIBar = ReadPCIConfig( Ohci_Hc_Array[OhciCount].BusDevFunc, 0x10) ; 
            	if (OHCIBar != 0xFFFFFFFF && OHCIBar != 0) {
                	gLegSupRegs = (OHCI_LEG_SUP_REGS*)((OHCIBar & 0xFFFFFF00) + OHCI_HCE_CONTROL);
                	break;
            	}
			} else if (Ohci_Hc_Array[OhciCount].Type == FixedMemory) {
				gLegSupRegs = (OHCI_LEG_SUP_REGS*)Ohci_Hc_Array[OhciCount].MemAddr;
				break;
			}
        }
		if (gLegSupRegs == NULL) {
			return;
		} else {
            // Check if MMIO address space of Legacy Support registers resides in SMRAM region. If yes, don't proceed.
            if( AmiValidateMemoryBuffer( (VOID*)gLegSupRegs, sizeof(OHCI_LEG_SUP_REGS) ) ) {
                return;
            }
        }
    }

    //
    // Check emulation is enabled if not exit.
    //
    if ((GetHceControl() & (HCE_CNTRL_EMULATION_ENABLE | HCE_CNTRL_EMULATION_INTERRUPT)) != 
		(HCE_CNTRL_EMULATION_ENABLE | HCE_CNTRL_EMULATION_INTERRUPT)) {
        return;
    }

    LegacyStatus = GetHceStatus();


    //
    // Set the variable that we are processing the Trap
    //
    gInTrapHandler = TRUE;

    //
    // Disable Emulation ( in responce to i/o handler can try to access a real KBC)
    //
    SetHceControl(GetHceControl() & (~(HCE_CNTRL_EMULATION_ENABLE | HCE_CNTRL_IRQ_ENABLE)));

    //
    // if Character Pending interrupt is enabled and OBF is not set, handle Port read 60
    //
    if (GetHceControl() & HCE_CNTRL_CHARACTER_PENDING && !(LegacyStatus & HCE_STS_OUTPUTFULL)){
        trap60r();
    } else {
        //
        //Clear OBF in internal structure
        //
        ((VIRTKBC*)gVirtualKBC)->st_ &= (~(KBC_STATUS_OBF | KBC_STATUS_AUXB));
        // OBF is not full, clear AUX BUF also
        if (!(LegacyStatus & KBC_STATUS_OBF)) {
            LegacyStatus &=  ~KBC_STATUS_AUXB;
        }
        //
        // Update the Internal stucture with the correct value
        //
        ((VIRTKBC*)gVirtualKBC)->st_ |= LegacyStatus & (KBC_STATUS_OBF | KBC_STATUS_AUXB);
    }

    //
    //Check for GA20 Sequence change
    //
    if ((LegacyStatus & HCE_STS_INPUTFULL) && GetHceControl() & HCE_CNTRL_GA20_SEQ){
        HandleGA20Sequence();
    } else {
        // Dispatch the interrupt depending on saved status
        if (LegacyStatus & HCE_STS_INPUTFULL) {
            if (LegacyStatus & HCE_STS_CMDDATA) {
                trap64w();
            } else {
                trap60w();
            }
        }
    }

    // Update Status
    SetHceStatus(((VIRTKBC* )gVirtualKBC)->st_);

    // If more data needs to be sent set Character Pending interrupt
    if (kbd->qhead != kbd->qtail || mouse->qhead != mouse->qtail) {
        SetHceControl(GetHceControl() | HCE_CNTRL_CHARACTER_PENDING);
        gClearCharacterPending = FALSE;
    } else {
        if (gClearCharacterPending == TRUE){
            SetHceControl(GetHceControl() & (~HCE_CNTRL_CHARACTER_PENDING));
            gClearCharacterPending = FALSE;
        } else {
            // Clear Character Pending bit and OBF in next SMI
            gClearCharacterPending = TRUE;
        }
    }

    //
    // Enable Traps
    //
    SetHceControl(GetHceControl() | HCE_CNTRL_EMULATION_ENABLE);
    gInTrapHandler = FALSE;

    return;
}


//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   Trap6064_Handler
//
// Description: SMI handler to handle the 64write, 64read, 60 write and 60 read SMI.
//
// Input:       DispatchHandle  - EFI Handle
//              DispatchContext - Pointer to the EFI_SMM_SW_DISPATCH_CONTEXT

// Output:      None
//
// Note :       Called inside SMM
//              Used only when KBC is present on the system
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
void Trap6064_Handler (
  IN  EFI_HANDLE                    DispatchHandle,
  IN  EFI_SMM_USB_DISPATCH_CONTEXT  * DispatchContext
  )
{
    UINT8 EmulationStatus;
    UINTN OhciCount;
    volatile EFI_PHYSICAL_ADDRESS   OHCIBar = 0;
    UINT8   Data;
    VIRTMOUSE* mouse = (VIRTMOUSE*)gVirtualKBC->mouse_dev;

    //
    // check if gOHCIBar has a valid address
    //
    if (gLegSupRegs == NULL) {
        for( OhciCount = 0; OhciCount < Ohci_Hc_Array_Size; ++OhciCount ){
			if (Ohci_Hc_Array[OhciCount].Type == PciDevice) {
            	OHCIBar = ReadPCIConfig( Ohci_Hc_Array[OhciCount].BusDevFunc, 0x10) ; 
            	if (OHCIBar != 0xFFFFFFFF && OHCIBar != 0) {
                	gLegSupRegs = (OHCI_LEG_SUP_REGS*)((OHCIBar & 0xFFFFFF00) + OHCI_HCE_CONTROL);
                	break;
            	}
			} else if (Ohci_Hc_Array[OhciCount].Type == FixedMemory) {
				gLegSupRegs = (OHCI_LEG_SUP_REGS*)Ohci_Hc_Array[OhciCount].MemAddr;
				break;
			}
        }
		if (gLegSupRegs == NULL) {
			return;
        } else {
            // Check if MMIO address space of Legacy Support registers resides in SMRAM region. If yes, don't proceed.
            if( AmiValidateMemoryBuffer( (VOID*)gLegSupRegs, sizeof(OHCI_LEG_SUP_REGS) ) ) {
                return;
            }
		}
    }

    //
    // Check emulation is enabled if not exit.
    //
    if (!( GetHceControl() & HCE_CNTRL_EMULATION_ENABLE)) {
        return;
    }

    ((VIRTKBC*)gVirtualKBC)->st_ = EmulationStatus = GetHceStatus();

    // Set the variable that we are processing the Trap
    gInTrapHandler = TRUE;

    //
    // Disable Emulation ( in response to i/o handler can try to access a real KBC)
    //
    SetHceControl(GetHceControl() & (~(HCE_CNTRL_EMULATION_ENABLE | HCE_CNTRL_IRQ1_ACTIVE | HCE_CNTRL_IRQ12_ACTIVE)));

    //
    // Check if IRQ1 and IRQ12 is active
    //
    if (GetHceControl() & (HCE_CNTRL_IRQ1_ACTIVE | HCE_CNTRL_IRQ12_ACTIVE )){

        // Update Status
        Data = ByteReadIO(KBC_STATUS_REG);

        if (Data & (KBC_STATUS_OBF | KBC_STATUS_AUXB)) {
            // Update Data
            SetHceOutput(ByteReadIO(KBC_DATA_REG));
            ((VIRTKBC* )gVirtualKBC)->DelaySendingDataCmd = TRUE;
            SerialOutput(GetHceOutput());
        } else {
            // No data but only IRQ, then use emulation status
            Data = EmulationStatus;
        }

        //
        // Clear the IRQ12/IRQ1 Active bit. Enable IRQEn only if data is pending
        //
        if ((Data & (KBC_STATUS_OBF | KBC_STATUS_AUXB)) == (KBC_STATUS_OBF | KBC_STATUS_AUXB)) {
            SetHceControl (GetHceControl() | HCE_CNTRL_IRQ12_ACTIVE | HCE_CNTRL_IRQ_ENABLE);
        } else if ((Data & (KBC_STATUS_OBF | KBC_STATUS_AUXB)) == KBC_STATUS_OBF ) {
            SetHceControl (GetHceControl() | HCE_CNTRL_IRQ1_ACTIVE | HCE_CNTRL_IRQ_ENABLE);
        }

        //
        // This is a catch all condition. If IRQ generatd with out data just clear the status.
        //
        if (!(Data & KBC_STATUS_OBF)) {
            SetHceControl (GetHceControl() | HCE_CNTRL_IRQ1_ACTIVE | HCE_CNTRL_IRQ12_ACTIVE | HCE_CNTRL_IRQ_ENABLE);
        }

        SetHceStatus(Data);
        SerialOutput(Data);
    } else {

        //
        // Enable HCE_CNTRL_EXT_IRQ_ENABLE
        //
        SetHceControl(GetHceControl() & ~(HCE_CNTRL_IRQ1_ACTIVE | HCE_CNTRL_IRQ12_ACTIVE | HCE_CNTRL_IRQ_ENABLE) | HCE_CNTRL_EXT_IRQ_ENABLE);
        ((VIRTKBC* )gVirtualKBC)->DelaySendingDataCmd = FALSE;


        //
        // if Character Pending interrupt is enabled and OBF is not set, handle Port read 60
        //
        if (GetHceControl() & HCE_CNTRL_CHARACTER_PENDING && !(EmulationStatus & HCE_STS_OUTPUTFULL)){
            if (ResponseBytes){
                if (!mouse->sink.present_) {
                    trap60r();
                } else {
                    WaitForOBFSMM();
                }
            }
            Data=ByteReadIO(KBC_STATUS_REG);
            if (Data & KBC_STATUS_OBF) {
                ResponseBytes--;
                SetHceOutput(ByteReadIO(KBC_DATA_REG));
                SerialOutput(GetHceOutput());
                ((VIRTKBC* )gVirtualKBC)->st_ = Data;
            }
        }

        //Check for GA20 Sequence change
        if ((EmulationStatus & HCE_STS_INPUTFULL) && GetHceControl() & HCE_CNTRL_GA20_SEQ){
            HandleGA20Sequence();
            // Clear the i/p full bit once the cmd/data is processed
            ((VIRTKBC*)gVirtualKBC)->st_ = ((VIRTKBC*)gVirtualKBC)->st_ & ~(HCE_STS_INPUTFULL);
        } else {
            // Dispatch the interrupt depending on saved status
            if (EmulationStatus & HCE_STS_INPUTFULL) {
                if (EmulationStatus & HCE_STS_CMDDATA) {
                    MouseCmdInProgress = FALSE;
                    if (GetHceInput() == 0xD4) {
                        MouseCmdInProgress = TRUE;
                    }
                    SerialOutput(GetHceInput());
                    trap64w();
                } else {
                    SerialOutput(GetHceInput());
                    trap60w();
                    CheckNumberofResponseBytes();
                    if (!CheckPS2KBDMouseIRQEnabled() && ResponseBytes) {
                        WaitForOBFSMM();
                    }
                    MouseCmdInProgress = FALSE;
                    Data=ByteReadIO(KBC_STATUS_REG);
                    if (!(Data & KBC_STATUS_OBF)) {
                        ResponseBytes = 0;
                    }
                    //
                    // if no data in emulation o/p register then update it
                    //
                    if (!(GetHceStatus() & KBC_STATUS_OBF) && (Data & KBC_STATUS_OBF)){
                        // Update Data
                        SetHceOutput(ByteReadIO(KBC_DATA_REG));
                        SerialOutput(GetHceOutput());
                        ((VIRTKBC* )gVirtualKBC)->st_ = Data;
                        if (ResponseBytes) {
                            ResponseBytes--;
                        }
                    }
                }
                // Clear the i/p full bit once the cmd/data is processed
                ((VIRTKBC*)gVirtualKBC)->st_ = ((VIRTKBC*)gVirtualKBC)->st_ & ~(HCE_STS_INPUTFULL);
            }
        }

        // Update Status
        SetHceStatus(((VIRTKBC* )gVirtualKBC)->st_);

        if (ResponseBytes) {
            SetHceControl(GetHceControl() & ~(HCE_CNTRL_IRQ1_ACTIVE | HCE_CNTRL_IRQ12_ACTIVE) | HCE_CNTRL_CHARACTER_PENDING);
        } else {
            SetHceControl(GetHceControl() & ~(HCE_CNTRL_IRQ1_ACTIVE | HCE_CNTRL_IRQ12_ACTIVE) & (~HCE_CNTRL_CHARACTER_PENDING));
        }
    }

    //
    // Enable Traps
    //
    SetHceControl(GetHceControl() & ~(HCE_CNTRL_IRQ1_ACTIVE | HCE_CNTRL_IRQ12_ACTIVE) | HCE_CNTRL_EMULATION_ENABLE);
    gInTrapHandler = FALSE;

    return;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   Ohci_TrapEnable
//
// Description: Enable/Disable traping in OHCI HC.
//
// Input:       Boolean
//
// Output:      TRUE/FALSE
//
// Note :       Called inside SMM
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

BOOLEAN    Ohci_TrapEnable(BOOLEAN TrapEnable)
{
    UINTN OhciCount;
    volatile EFI_PHYSICAL_ADDRESS   OHCIBar = 0;

    if(gInTrapHandler)
        return FALSE;

    // The idea is, since data has not been pushed, don't let USB module to send more data. By keeping emulation enabled
    // emulation status will be sent, which will return O/P full so next byte will not be sent from USB
    if (GetHceStatus() & KBC_STATUS_OBF) {
        return FALSE;
    }

    if (gLegSupRegs == NULL) {
        for( OhciCount = 0; OhciCount < Ohci_Hc_Array_Size; ++OhciCount ){
			if (Ohci_Hc_Array[OhciCount].Type == PciDevice) {
            	OHCIBar = ReadPCIConfig( Ohci_Hc_Array[OhciCount].BusDevFunc, 0x10) ; 
            	if (OHCIBar != 0xFFFFFFFF && OHCIBar != 0) {
                	gLegSupRegs = (OHCI_LEG_SUP_REGS*)((OHCIBar & 0xFFFFFF00) + OHCI_HCE_CONTROL);
                	break;
            	}
			} else if (Ohci_Hc_Array[OhciCount].Type == FixedMemory) {
				gLegSupRegs = (OHCI_LEG_SUP_REGS*)Ohci_Hc_Array[OhciCount].MemAddr;
				break;
			}
        }
		if (gLegSupRegs == NULL) {
			return FALSE;
        } else {
            // Check if MMIO address space of Legacy Support registers resides in SMRAM region. If yes, don't proceed.
            if( AmiValidateMemoryBuffer( (VOID*)gLegSupRegs, sizeof(OHCI_LEG_SUP_REGS) ) ) {
                return FALSE;
            }
		}
    }

    if(TrapEnable){
        //
        // Enable Traps
        //
        SetHceControl(GetHceControl() & ~(HCE_CNTRL_IRQ1_ACTIVE | HCE_CNTRL_IRQ12_ACTIVE) | HCE_CNTRL_EMULATION_ENABLE);
    } else {
        //
        // Disable Traps;
        //
        SetHceControl((GetHceControl() & ~HCE_CNTRL_EMULATION_ENABLE) | HCE_CNTRL_IRQ1_ACTIVE | HCE_CNTRL_IRQ12_ACTIVE);
    }
    return TRUE;
}


//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   Ohci_HasTrapStatus
//
// Description: Return whether Emulation Interrupt has been generated or not
//
// Input:       None
//
// Output:      BOOLEAN
//
// Note :       Called inside SMM. No usage for now. Present for compatible reason with OHCI.
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
BOOLEAN Ohci_HasTrapStatus()
{
    return FALSE;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   NonSmmOhci_TrapEnable
//
// Description: Enable/Disable traping in OHCI HC.
//
// Input:       Boolean
//
// Output:      TRUE/FALSE
//
// Note:        Called outside SMM
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

BOOLEAN    NonSmmOhci_TrapEnable(BOOLEAN TrapEnable)
{
	UINTN OhciCount;
	volatile EFI_PHYSICAL_ADDRESS   OHCIBar = 0;
    EFI_TPL   OldTpl;

    if (gLegSupRegs == NULL) {
        for( OhciCount = 0; OhciCount < Ohci_Hc_Array_Size; ++OhciCount ){
			if (Ohci_Hc_Array[OhciCount].Type == PciDevice) {
            	OHCIBar = NonSmmReadPCIConfig( Ohci_Hc_Array[OhciCount].BusDevFunc, 0x10) ; 
            	if (OHCIBar != 0xFFFFFFFF && OHCIBar != 0) {
                	gLegSupRegs = (OHCI_LEG_SUP_REGS*)((OHCIBar & 0xFFFFFF00) + OHCI_HCE_CONTROL);
                	break;
            	}
			} else if (Ohci_Hc_Array[OhciCount].Type == FixedMemory) {
				gLegSupRegs = (OHCI_LEG_SUP_REGS*)Ohci_Hc_Array[OhciCount].MemAddr;
				break;
			}
        }
		if (gLegSupRegs == NULL) {
			return FALSE;
		}
    }

    OldTpl = pBS->RaiseTPL(TPL_HIGH_LEVEL);

    if (TrapEnable) {
        // Initialize the status to default value
        gLegSupRegs->HceStatus = 0x1C;

        // Enable Traps and clear status(es) that might be asserted by our handlers
        if (IoRead8(0x64) == 0xFF) {
			gLegSupRegs->HceControl = HCE_CNTRL_EMULATION_ENABLE | HCE_CNTRL_A20_STATE;			
        } else {
        	gLegSupRegs->HceControl = OHCI_TRAPEN_MASK | HCE_CNTRL_A20_STATE;
        }
    } else {
        // Disable Traps; Clear the status
        gLegSupRegs->HceControl &= ~OHCI_TRAPEN_MASK;
    }
    pBS->RestoreTPL(OldTpl);

    return TRUE;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   GetHceInput
//
// Description: Reads the HceInput register which holds the data written to port 60/64
//
// Input:       None
//
// Output:      UINT8
//
// Note :       Called only inside SMM
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
UINT8   GetHceInput()
{
    return (UINT8)(gLegSupRegs->HceInput & 0xFF);

}


//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   GetHceOutput
//
// Description: Reads the HceOutPut register in OHCI controller
//
// Input:       None
//
// Output:      UINT8
//
// Note :       Called only inside SMM
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
UINT8   GetHceOutput()
{
	return (UINT8)(gLegSupRegs->HceOutput & 0xFF);
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   GetHceStatus
//
// Description: Reads the HceStatus register in OHCI controller
//
// Input:       None
//
// Output:      UINT8
//
// Note :       Called only inside SMM
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
UINT8   GetHceStatus()
{
    return (UINT8)(gLegSupRegs->HceStatus & 0xFF);
}


//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   SetHceStatus
//
// Description: Writes to HceStatus in OHCI controller
//
// Input:       UINT8
//
// Output:      None
//
// Note :       Called only inside SMM
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
void SetHceStatus (UINT8 Data)
{
    gLegSupRegs->HceStatus = (UINT32)Data;
    return;
}


//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   SetHceOutput
//
// Description: Writes to HceOutput which is returned on IO port 60h read
//
// Input:       UINT8
//
// Output:      None
//
// Note :       Called only inside SMM
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
void SetHceOutput (UINT8 Data)
{
    gLegSupRegs->HceOutput = (UINT32)Data;
    return;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   SetHceControl
//
// Description: Writes to HceControl in OHCI controller
//
// Input:       UINT8
//
// Output:      None
//
// Note :       Called only inside SMM
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
void SetHceControl (UINT16 Data)
{
    gLegSupRegs->HceControl = (UINT32)Data;
    return;
}


//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   SetHceControl
//
// Description: Reads the HceStatus register in OHCI controller
//
// Input:       None
//
// Output:      UINT8
//
// Note :       Called only inside SMM
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
UINT16  GetHceControl()
{
	return (UINT16)(gLegSupRegs->HceControl & 0x1FF);
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   WaitForOBFSMM
//
// Description: Wait till O/P buffer is full
//
// Input:       None
//
// Output:      None
//
// Note :       Called only inside SMM
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
void
WaitForOBFSMM()
{
    UINT8   bCount = 8;
    UINT8   bStatus;
    UINT32  wCount;
    do {
        wCount = 0xffff;
        bStatus = (UINT8)(ByteReadIO(KBC_STATUS_REG) & BIT0);
        while (!bStatus) {
            if(wCount == 0) break;
                bStatus = (UINT8)(ByteReadIO(KBC_STATUS_REG) & BIT0);
                wCount--;
            }
            bCount--;
    } while (bCount && (!bStatus));

    return;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   CheckPS2KBDMousePresence
//
// Description: Check whether PS2 KBD/Mouse IRQ has been enabled or not
//
// Input:       None
//
// Output:      TRUE: if PS2 KBD/MOUSE IRQ enabled
//
// Note :   Called only inside SMM
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
BOOLEAN
CheckPS2KBDMouseIRQEnabled()
{


    LEGACYKBC* legkbc = _CR(gVirtualKBC,LEGACYKBC,kbc_);

    // If the device and IRQ is enabled in CCB return TRUE else return FALSE
    // The idea being, we don't have to wait for the response after the cmd is issued to the device.
    // IRQ will be generated when the response is ready.

    if (!legkbc->fCcb_loaded) {
        return FALSE;
    }

    if (MouseCmdInProgress){
        if (!(legkbc->ccb_ & KBC_CCB_EN2) && (legkbc->ccb_ & KBC_CCB_INT2)) {
            return TRUE;
        }
    } else {
        if (!(legkbc->ccb_ & KBC_CCB_EN) && (legkbc->ccb_ & KBC_CCB_INT)) {
            return TRUE;
        }
    }

    return FALSE;

}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   CheckNumberofResponseBytes
//
// Description: Based on KBD/Mouse cmd, determine how many response bytes should be provided
//
// Input:      None
//
// Output:     Updates ResponseBytes
//
// Note :       Called only inside SMM
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
void CheckNumberofResponseBytes ()
{

    UINT8   bData;
    UINT8*  CmdResponseArray;

    ResponseBytes = 0;
    bData = GetHceInput();
    if (MouseCmdInProgress) {
        ResponseBytes = 1;
        CmdResponseArray = MouseCmdResponse;
    } else  {
        CmdResponseArray = KBDCmdResponse;
    }

    do {
        if (*CmdResponseArray == bData) {
            ResponseBytes = *(CmdResponseArray +1);
            break;
        }
        CmdResponseArray+=2;
    } while (*CmdResponseArray);

}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   SerialOutput
//
// Description: Directly writes to 3F8 COM port. Using this routine will be faster and
//              debug output delay will have no impact on debugging time sensitive routines
//              O/P the byte and give a space after that;
//
// Input:      Byte to output
//
// Output:     None
//
// Note :
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
//
void SerialOutput (
    UINT8   Data
)
{
/*
    UINT8 HigherNibble = Data >> 4;
    UINT8 LowerBibble = Data & 0xF;

    HigherNibble = HigherNibble > 9 ? HigherNibble + 0x37 : HigherNibble + 0x30;
    IoWrite8 (0x3f8, HigherNibble);

    LowerBibble = LowerBibble > 9 ? LowerBibble + 0x37 : LowerBibble + 0x30;
    IoWrite8 (0x3f8, LowerBibble);

    // Space
    IoWrite8 (0x3f8, 0x20);
*/
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
