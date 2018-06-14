//**********************************************************************
//**********************************************************************
//**                                                                  **
//**        (C)Copyright 1985-2010, American Megatrends, Inc.         **
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
// $Header: /Alaska/SOURCE/Modules/USBRecovery/XhciPei.c 10    11/24/12 5:45a Ryanchou $
//
// $Revision: 10 $
//
// $Date: 11/24/12 5:45a $
//
//**********************************************************************
// Revision History
// ----------------
// $Log: /Alaska/SOURCE/Modules/USBRecovery/XhciPei.c $
// 
// 10    11/24/12 5:45a Ryanchou
// [TAG]  		EIP103990
// [Category]  	Improvement
// [Description]  	Synchronized with USB PEI module 4.6.3_USB_08.10.24.
// [Files]  		EhciPei.c, EhciPei.h, OhciPei.c, OhciPei.h, UhcPeim.c,
// BotPeim.c, BotPeim.h, PeiAtapi.c, UsbBotPeim.c, UsbBotPeim.h,
// HubPeim.c, UsbPeim.c, XhciPei.c, XhciPei.h, HubPeim.h, PeiUsbLib.c,
// PeiUsbLib.h, UsbPeim.h
// 
// 9     4/24/12 10:16p Wilsonlee
// [TAG]  		EIP75547
// [Category]  	Bug Fix
// [Severity]  	Normal
// [Symptom]  	Xhci recovery funtion failed when SS devices on USB 3.0
// port.
// [RootCause]  	The SS device connected to USB2 port.
// [Solution]  	Reset the USB2 port when initial xhci controller, then the
// SS device reconnect to USB3 port.
// [Files]  		XhciPei.c, XhciPei.h
// 
// 8     4/12/11 12:00a Rameshr
// [TAG]- EIP 57444
// [Category]-IMPROVEMENT
// [Description]- PI1.1 Support.
// [Files]- OhciPeiboard.c,Xhcipei.c, Peiusblib.c
// 
// 7     1/18/11 1:08a Ryanchou
// [TAG]  		EIP47931
// [Category]  	Improvement
// [Description]  	Added USB 3.0 hub support.
// [Files]  		EhciPei.c, EhciPei.h, HubPeim.c, HubPeim.h, OhciPei.c,
// OhciPei.h, UhcPeim.c, UhcPeim.h, usb.h, UsbHostController.h,
// UsbIoPeim.c, UsbPeim.c, UsbPeim.h, XhciPei.c, XhciPei.h
// 
// 6     1/17/11 7:08a Ryanchou
// [TAG]  		EIP48013
// [Category]  	Improvement
// [Description]  	Use 32 or 64 byte Context data structures dynamically.
// [Files]  		XhciPei.c, XhciPei.h
// 
// 5     10/27/10 11:27a Olegi
// [TAG]  		EIP46147
// [Category]  	Bug Fix
// 
// 4     10/20/10 10:44a Olegi
// [TAG]  		EIP46492
// [Category]  	Bug Fix
// [Severity]  	Important
// [Symptom]  	TdSize variable should be declared as a 32bit integer
// instead of a 8bit one.
// 
// 3     10/14/10 3:57p Olegi
// Added code that check for PCI device presence.
// 
// 2     10/12/10 5:57p Olegi
// Added (UINTN) typecast when converting pointers to UINT64. Without it
// pointers that have BIT31 will have bits 32..63 set.
// 
// 1     10/11/10 4:53p Olegi
//
//**********************************************************************

//<AMI_FHDR_START>
//----------------------------------------------------------------------------
//
// Name:    XhciPei.c
//
// Description:
//  This file is the main source file for the xHCI PEI USB recovery module.
//  Its entry point at XhciPeiUsbEntryPoint will be executed from the
//  UsbRecoveryInitialize INIT_LIST.
//
//----------------------------------------------------------------------------
//<AMI_FHDR_END>

#include <AmiPeiLib.h>
#include "XhciPei.h"
#include <PPI\stall.h>
#include "token.h"
#include "pci.h"
#include "usbpeim.h"

PCI_BUS_DEV_FUNCTION gXhciControllerPciTable[] = {PEI_XHCI_CONTROLLER_PCI_ADDRESS {0,0,0}};
UINT16 gXhciControllerCount = \
    sizeof(gXhciControllerPciTable) / sizeof(PCI_BUS_DEV_FUNCTION) - 1;

PCI_DEV_REGISTER_VALUE gPeiXhciInitPciTable[] = {PEI_XHCI_CONTROLLER_PCI_REGISTER_VALUES {0,0,0,0,0,0,0}};
UINT16 gPeiXhciInitPciTableCount = \
    sizeof(gPeiXhciInitPciTable) / sizeof(PCI_DEV_REGISTER_VALUE) - 1;

UINT8 gSlotBeingConfigured;

#ifndef PI_SPECIFICATION_VERSION //old Core
extern EFI_STATUS PciCfgModify(
IN CONST EFI_PEI_SERVICES 	**PeiServices,
IN EFI_PEI_PCI_CFG_PPI_WIDTH	Width,
IN UINT64					Address,
IN UINTN					SetBits,
IN UINTN					ClearBits
);
#endif

//<AMI_PHDR_START>
//---------------------------------------------------------------------------
//
// Procedure:   XhciPeiUsbEntryPoint
//
// Description: 
//  This is the entry point into the XHCI initialization.
//
// Input:
//  IN EFI_FFS_FILE_HEADER *FfsHeader
//      --  EFI_FFS_FILE_HEADER pointer
//  IN EFI_PEI_SERVICES **PeiServices
//      --  EFI_PEI_SERVICES pointer
//
// Output: 
//  EFI_STATUS (Return Value)
//      = EFI_SUCCESS on successful completion or valid EFI error code
//
//---------------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS XhciPeiUsbEntryPoint (
    IN EFI_FFS_FILE_HEADER *FfsHeader,
    IN EFI_PEI_SERVICES    **PeiServices )
{

    EFI_STATUS              Status;
    EFI_PEI_STALL_PPI       *StallPpi;
    UINT32                  XhciBaseAddress = PEI_XHCI_MMIOBASE;
    EFI_PHYSICAL_ADDRESS    TempPtr;
    USB3_CONTROLLER         *Usb3Hc;
    UINTN                   MemPages;
    UINT8                   ControllerIndex;
    UINT8                   PciDevIndex;
    UINT8                   CmdRegisterValue = 6;

    //-------------------------------------------
    // Initialize the EFI_PEI_STALL_PPI interface
    //-------------------------------------------
    Status = (**PeiServices).LocatePpi( PeiServices, &gPeiStallPpiGuid,
        0, NULL, &StallPpi );
    if ( EFI_ERROR( Status ) ) {
        return EFI_UNSUPPORTED;
    }

    // Program PCI registers of the host controller and other relevant PCI
    // devices (e.g. bridges that enable this host).

    for (PciDevIndex = 0; PciDevIndex < gPeiXhciInitPciTableCount; PciDevIndex++) {

        EFI_PEI_PCI_CFG_PPI_WIDTH Width;

        switch (gPeiXhciInitPciTable[PciDevIndex].Size) {
            	case 8:     Width = EfiPeiPciCfgWidthUint8; break;
            	case 16:	Width = EfiPeiPciCfgWidthUint16; break;
            	case 32:	Width = EfiPeiPciCfgWidthUint32; break;
            	case 64:	Width = EfiPeiPciCfgWidthUint64; break;
            	default:    continue;
        }
 
        Status = PciCfgModify(
                    PeiServices,
                    Width,
                    PEI_PCI_CFG_ADDRESS(
                        gPeiXhciInitPciTable[PciDevIndex].Bus,
                        gPeiXhciInitPciTable[PciDevIndex].Device,
                        gPeiXhciInitPciTable[PciDevIndex].Function,
                        gPeiXhciInitPciTable[PciDevIndex].Register
                    ),
                    gPeiXhciInitPciTable[PciDevIndex].SetBits,
                    gPeiXhciInitPciTable[PciDevIndex].ClearBits);
    }

    for (ControllerIndex = 0; ControllerIndex < gXhciControllerCount;
         ControllerIndex++, XhciBaseAddress+=0x10000)
    {
        UINT16 Vid;
        UINT16 Did;

        // Get VID/DID, see if controller is visible on PCI
        (*PeiServices)->PciCfg->Read(PeiServices,(*PeiServices)->PciCfg,
            EfiPeiPciCfgWidthUint16, XHCI_PCI_ADDRESS( ControllerIndex, PCI_VID ),&Vid);
        if (Vid == 0xffff) continue;    // Controller not present
    
        (*PeiServices)->PciCfg->Read(PeiServices,(*PeiServices)->PciCfg,
            EfiPeiPciCfgWidthUint16, XHCI_PCI_ADDRESS( ControllerIndex, PCI_DID ), &Did);

        //----------------------------------------------------------
        // Allocate USB3_CONTROLLER object that holds all necessary
        // information for the Host Controller operational registers
        // for each controller.  Initialze the controller and setup
        // data structures, get it ready for operation.
        //----------------------------------------------------------
        MemPages = sizeof(USB3_CONTROLLER) / 0x1000 + 1;
        Status = (**PeiServices).AllocatePages(PeiServices, 
                EfiConventionalMemory,
                MemPages,
                &TempPtr);
        if (EFI_ERROR(Status)) return EFI_OUT_OF_RESOURCES;

        (**PeiServices).SetMem((VOID*)TempPtr, MemPages*4096, 0);  // Clear allocated memory
    
        Usb3Hc = (USB3_CONTROLLER*)(UINTN)TempPtr;
    
        //----------------------------------------------------------
        // USB3 controller data area is allocated, start stuff it in
        // with the useful filling in with the useful data.
        //----------------------------------------------------------
    
        // Program BAR
        (*PeiServices)->PciCfg->Write(PeiServices,(*PeiServices)->PciCfg,
            EfiPeiPciCfgWidthUint32,
            XHCI_PCI_ADDRESS( ControllerIndex, PCI_BAR0 ),
            &XhciBaseAddress
        );
        Usb3Hc->CapRegs = (XHCI_HC_CAP_REGS*)(UINTN)XhciBaseAddress;
    
        // Enable MMIO access and BM
        (*PeiServices)->PciCfg->Write(PeiServices,(*PeiServices)->PciCfg,
            EfiPeiPciCfgWidthUint8,
            XHCI_PCI_ADDRESS( ControllerIndex, PCI_CMD ),
            &CmdRegisterValue
        );

        (UINT8)(UINTN)Usb3Hc->CapRegs &= ~(0x7F);  // Clear attributes

        Usb3Hc->Did = Did;
        Usb3Hc->Vid = Vid;
        Usb3Hc->Access64 = Usb3Hc->CapRegs->HcParams.Ac64;
        Usb3Hc->HciVersion = Usb3Hc->CapRegs->HciVersion;
        Usb3Hc->MaxPorts = Usb3Hc->CapRegs->HcParams1.MaxPorts;
        Usb3Hc->OpRegs = (XHCI_HC_OP_REGS*)((UINTN)Usb3Hc->CapRegs + Usb3Hc->CapRegs->CapLength);
        Usb3Hc->PageSize4K = Usb3Hc->OpRegs->PageSize;
        Usb3Hc->ContextSize = 0x20 << Usb3Hc->CapRegs->HcParams.Csz;
        Usb3Hc->MaxIntrs = Usb3Hc->CapRegs->HcParams1.MaxIntrs;     // Get maximum number of interrupters
        Usb3Hc->DbOffset = Usb3Hc->CapRegs->DbOff;      // Doorbell offset
        Usb3Hc->MaxSlots = PEI_XHCI_MAX_SLOTS;
    
        Usb3Hc->InputContext = (VOID*)&Usb3Hc->InpCtx;
        Usb3Hc->XfrRings = Usb3Hc->XfrRing;
        Usb3Hc->XfrTrbs = (UINTN)Usb3Hc->XfrTrb;
        Usb3Hc->DeviceContext = (VOID*)Usb3Hc->DevCtx;
        
        XhciExtCapParser(PeiServices, Usb3Hc);	//(EIP75547+)

        PEI_TRACE ((-1, PeiServices, "USB recovery xHCI[%d] controller initialization details:\n", ControllerIndex));
        PEI_TRACE ((-1, PeiServices, "  PCI location: B%x/D%x/F%x, VID:DID = %x:%x, BAR0 = %x\n",
            gXhciControllerPciTable[ControllerIndex].Bus,
            gXhciControllerPciTable[ControllerIndex].Device,
            gXhciControllerPciTable[ControllerIndex].Function,
            Usb3Hc->Vid,
            Usb3Hc->Did,
            Usb3Hc->CapRegs
        ));
        PEI_TRACE((-1, PeiServices, "  MaxSlots = %x, InputCtx %x, Device Ctx %x\n",
            Usb3Hc->MaxSlots, (UINT8*)Usb3Hc->InputContext, (UINT8*)Usb3Hc->DeviceContext));
    
        Usb3Hc->PeiServices = PeiServices;
        Usb3Hc->CpuIoPpi = (*PeiServices)->CpuIo;
        Usb3Hc->StallPpi = StallPpi;
        Usb3Hc->PciCfgPpi = (*PeiServices)->PciCfg;

        // Initialize the xHCI Controller for operation
        Status = XhciInitHC(PeiServices, Usb3Hc, ControllerIndex);
        PEI_ASSERT(PeiServices, Status == EFI_SUCCESS);
        if (EFI_ERROR(Status)) return Status;

        // Setup PPI entry point
        Usb3Hc->UsbHostControllerPpi.ControlTransfer = XhciHcControlTransfer;
        Usb3Hc->UsbHostControllerPpi.BulkTransfer = XhciHcBulkTransfer;
        Usb3Hc->UsbHostControllerPpi.GetRootHubPortNumber = XhciHcGetRootHubPortNumber;
        Usb3Hc->UsbHostControllerPpi.GetRootHubPortStatus = XhciHcGetRootHubPortStatus;
        Usb3Hc->UsbHostControllerPpi.SetRootHubPortFeature = XhciHcSetRootHubPortFeature;
        Usb3Hc->UsbHostControllerPpi.ClearRootHubPortFeature = XhciHcClearRootHubPortFeature;
        Usb3Hc->UsbHostControllerPpi.PreConfigureDevice = XhciHcPreConfigureDevice;
        Usb3Hc->UsbHostControllerPpi.EnableEndpoints = XhciEnableEndpoints;

        Usb3Hc->PpiDescriptor.Flags =(EFI_PEI_PPI_DESCRIPTOR_PPI |EFI_PEI_PPI_DESCRIPTOR_TERMINATE_LIST);
        Usb3Hc->PpiDescriptor.Guid = &gPeiUsbHostControllerPpiGuid;
        Usb3Hc->PpiDescriptor.Ppi = &Usb3Hc->UsbHostControllerPpi;

        Status = (**PeiServices).InstallPpi(PeiServices, &Usb3Hc->PpiDescriptor);
        if (EFI_ERROR(Status)) return EFI_NOT_FOUND;

    }

    return EFI_SUCCESS;
}


//<AMI_PHDR_START>
//---------------------------------------------------------------------------
//
// Procedure:   XhciInitHC
//
// Description: 
//  This function initializes xHCI controller registers and starts it.
//
// Input:
//  EFI_PEI_SERVICES    **PeiServices
//      -- PEI_SERVICES pointer
//  USB3_CONTROLLER     *Usb3Hc
//      -- XHCI controller data structure pointer
//  UINT8               ControllerIndex
//      -- 0-based index of the controller to be initialized
//
// Output: 
//  EFI_STATUS (Return Value)
//      = EFI_SUCCESS on successful initialization completion
//
//---------------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS
XhciInitHC(
    EFI_PEI_SERVICES    **PeiServices,
    USB3_CONTROLLER     *Usb3Hc,
    UINT8               ControllerIndex
)
{
    XHCI_INTERRUPTER_REGS   *Interrupter;
    XHCI_ER_SEGMENT_ENTRY   *Erst0Entry;
    BOOLEAN     PpSet = FALSE;
    UINT8       PortNumber;
    volatile    XHCI_PORTSC *PortSC;
    UINT32      CurrentPortOffset = 0;
    UINT32      i;

	// Wait controller ready
	for (i = 0; i < 100; i++) {
        if (Usb3Hc->OpRegs->UsbSts.Field.Cnr == 0) break;
		XHCI_FIXED_DELAY_MS(Usb3Hc, 1);
    }
    PEI_ASSERT(PeiServices, Usb3Hc->OpRegs->UsbSts.Field.Cnr == 0);
	if (Usb3Hc->OpRegs->UsbSts.Field.Cnr) return EFI_DEVICE_ERROR;

	// Check if the xHC is halted
	if (Usb3Hc->OpRegs->UsbSts.Field.HcHalted == 0)
	{
		Usb3Hc->OpRegs->UsbCmd.RunStop = 0;
		// The xHC should halt within 16 ms. Section 5.4.1.1
		for (i = 0; i < 16; i++) {
        	XHCI_FIXED_DELAY_MS(Usb3Hc, 1);
        	if (Usb3Hc->OpRegs->UsbSts.Field.HcHalted) break;
		}
		PEI_ASSERT(PeiServices, Usb3Hc->OpRegs->UsbSts.Field.HcHalted);
		if (Usb3Hc->OpRegs->UsbSts.Field.HcHalted == 0) return EFI_DEVICE_ERROR;
	}

    // Reset controller
    Usb3Hc->OpRegs->UsbCmd.HcRst = 1;
    for (i = 0; i < 400; i++) {
        XHCI_FIXED_DELAY_MS(Usb3Hc, 1);
        if (Usb3Hc->OpRegs->UsbCmd.HcRst == 0) break;
    }

    PEI_ASSERT(PeiServices, Usb3Hc->OpRegs->UsbCmd.HcRst == 0);
    if (Usb3Hc->OpRegs->UsbCmd.HcRst) return EFI_DEVICE_ERROR;  // Controller can not be reset

	// Wait controller ready
	for (i = 0; i < 100; i++) {
        if (Usb3Hc->OpRegs->UsbSts.Field.Cnr == 0) break;
		XHCI_FIXED_DELAY_MS(Usb3Hc, 1);
    }
    PEI_ASSERT(PeiServices, Usb3Hc->OpRegs->UsbSts.Field.Cnr == 0);
	if (Usb3Hc->OpRegs->UsbSts.Field.Cnr) return EFI_DEVICE_ERROR;

    Usb3Hc->RtRegs = (XHCI_HC_RT_REGS*)((UINTN)Usb3Hc->CapRegs + Usb3Hc->CapRegs->RtsOff);
    PEI_TRACE ((-1, PeiServices, "PEI_XHCI: RT registers are at %x\n", Usb3Hc->RtRegs));

    Usb3Hc->OpRegs->Config = Usb3Hc->MaxSlots;  // Max device slots enabled
    Usb3Hc->DcbaaPtr = (XHCI_DCBAA*)Usb3Hc->Dcbaa;

    XhciMmio64Write(Usb3Hc, (UINTN)&Usb3Hc->OpRegs->DcbAap, (UINT64)(UINTN)Usb3Hc->DcbaaPtr);

    // Define the Command Ring Dequeue Pointer by programming the Command Ring
    // Control Register (5.4.5) with a 64-bit address pointing to the starting
    // address of the first TRB of the Command Ring.

    // Initialize Command Ring Segment: Size TRBS_PER_SEGMENT*16, 64 Bytes aligned
    XhciInitRing(&Usb3Hc->CmdRing, (UINTN)Usb3Hc->CommandRing, TRBS_PER_SEGMENT, TRUE);
    PEI_TRACE ((-1, PeiServices, "CMD Ring is at %x\n", (UINTN)&Usb3Hc->CmdRing));

    // Write CRCR HC register with the allocated address. Set Ring Cycle State to 1.
    XhciMmio64Write(Usb3Hc, (UINTN)&Usb3Hc->OpRegs->Crcr,
            (UINT64)(UINTN)Usb3Hc->CmdRing.Base + CRCR_RING_CYCLE_STATE);

    // Initialize and assign Event Ring
    XhciInitRing(&Usb3Hc->EvtRing, (UINTN)Usb3Hc->EventRing, TRBS_PER_SEGMENT, FALSE);
    PEI_TRACE ((-1, PeiServices, "EVT Ring is at %x\n", (UINTN)&Usb3Hc->EvtRing));

    // NOTE: This driver supports one Interrupter, hence it uses
    // one Event Ring segment with TRBS_PER_SEGMENT TRBs in it.

    // Initialize ERST[0]
    Erst0Entry = &Usb3Hc->Erst;
    Erst0Entry->RsBase = (UINT64)(UINTN)Usb3Hc->EvtRing.Base;
    Erst0Entry->RsSize = TRBS_PER_SEGMENT;

    Interrupter = Usb3Hc->RtRegs->IntRegs;

    // Initialize Interrupter fields
    Interrupter->Erstz = 1; // # of segments
    // ER dequeue pointer
    XhciMmio64Write(Usb3Hc, (UINTN)&Interrupter->Erdp, (UINT64)(UINTN)Usb3Hc->EvtRing.QueuePtr);
    // Seg Table location
    XhciMmio64Write(Usb3Hc, (UINTN)&Interrupter->Erstba, (UINT64)(UINTN)Erst0Entry);
    Interrupter->IMod = XHCI_IMODI; // Max interrupt rate
    Interrupter->IMan |= 2;         // Enable interrupt

    PEI_TRACE((-1, PeiServices, "Transfer Rings structures start at %x\n", Usb3Hc->XfrRings));

    // Set PortPower unless PowerPortControl indicates otherwise
    if (Usb3Hc->CapRegs->HcParams.Ppc != 0) {
        for (PortNumber = 0; PortNumber<Usb3Hc->MaxPorts;
                PortNumber++, CurrentPortOffset+=0x10) {
            PortSC = (XHCI_PORTSC*)((UINTN)Usb3Hc->OpRegs +
                            XHCI_PORTSC_OFFSET + CurrentPortOffset);
            if (PortSC->Field.Pp == 0) {
                PortSC->Field.Pp = 1; // Set port power
                PpSet = TRUE;
            }
        }
        if (PpSet) XHCI_FIXED_DELAY_MS(Usb3Hc, 20);   // Wait for 20 ms, Section 5.4.8
    }

    Usb3Hc->OpRegs->UsbCmd.Inte = 1;
    Usb3Hc->OpRegs->UsbCmd.RunStop = 1;

    XHCI_FIXED_DELAY_MS(Usb3Hc, 100);
    
    XhciResetUsb2Port(PeiServices, Usb3Hc);    //(EIP75547+)
        
    return EFI_SUCCESS;
}


//<AMI_PHDR_START>
//---------------------------------------------------------------------------
//
// Procedure:   XhciHcPreConfigureDevice
//
// Description: 
//  This function does preliminary device initialization: enables slot and
//  sets the address.
//
// Output: 
//  EFI_STATUS (Return Value)
//      = EFI_SUCCESS on successful pre-configuration completion
//      = EFI_DEVICE_ERROR on error
//
//---------------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS
XhciHcPreConfigureDevice(
    IN EFI_PEI_SERVICES            **PeiServices,
    IN PEI_USB_HOST_CONTROLLER_PPI *This,
    IN UINT8                       Port,
    IN UINT8                       DeviceSpeed,
    IN UINT16                      TransactionTranslator
)
{
    USB3_CONTROLLER *Usb3Hc = PEI_RECOVERY_USB_XHCI_DEV_FROM_THIS(This);
	UINT8		*Device;
	UINT8		*ParentHubDevice;
    TRB_RING    *XfrRing;
    UINT8       Speed;
    static UINT16 aMaxPacketSize[5] = {0, 8, 8, 64, 512};
    EFI_STATUS  Status;
    UINT8       SlotId;
	XHCI_INPUT_CONTROL_CONTEXT	*CtlCtx;
	XHCI_SLOT_CONTEXT			*SlotCtx;
	XHCI_SLOT_CONTEXT			*ParentHubSlotCtx;
	XHCI_EP_CONTEXT				*Ep0Ctx;
	UINT8	ParentHubSlotId;
	UINT8	i;

//    XHCI_FIXED_DELAY_MS(Usb3Hc, 1000);

    // Obtain device slot using Enable Slot command, 4.3.2, 4.6.3
    Status = XhciExecuteCommand(PeiServices, Usb3Hc, XhciTEnableSlotCmd, &SlotId);
    PEI_ASSERT(PeiServices, Status == EFI_SUCCESS);
    PEI_ASSERT(PeiServices, SlotId != 0);
	if (Status != EFI_SUCCESS) return Status;

    Device = (UINT8*)XhciGetDeviceContext(Usb3Hc, SlotId);

    // Update DCBAA with the new device pointer (index = SlotId)
    Usb3Hc->DcbaaPtr->DevCntxtAddr[SlotId-1] = (UINT64)(UINTN)Device;
    PEI_TRACE((-1, PeiServices, "PEI_XHCI: Slot[%d] enabled, device context at %x\n", SlotId, Device));

    // Initialize data structures associated with the slot 4.3.3

    // Zero the InputContext and DeviceContext
    (**PeiServices).SetMem((UINT8*)Usb3Hc->InputContext, XHCI_INPUT_CONTEXT_ENTRIES * Usb3Hc->ContextSize, 0);
	(**PeiServices).SetMem(Device, XHCI_DEVICE_CONTEXT_ENTRIES * Usb3Hc->ContextSize, 0);

    // Initialize the Input Control Context of the Input Context
    // by setting the A0 and A1 flags to 1

    CtlCtx = (XHCI_INPUT_CONTROL_CONTEXT*)XhciGetContextEntry(Usb3Hc, (UINT8*)Usb3Hc->InputContext, 0);
    CtlCtx->AddContextFlags = BIT0 + BIT1;

    // Initialize the Input Slot Context data structure
    SlotCtx = (XHCI_SLOT_CONTEXT*)XhciGetContextEntry(Usb3Hc, (UINT8*)Usb3Hc->InputContext, 1);
    SlotCtx->RouteString = 0;
    SlotCtx->ContextEntries = 1;
	if (TransactionTranslator == 0)	{
		SlotCtx->RootHubPort = Port;
	} else {
		Status = GetSlotId(Usb3Hc->DeviceMap, &ParentHubSlotId, (UINT8)(TransactionTranslator & 0xF));
		PEI_ASSERT(PeiServices, Status == EFI_SUCCESS);
		ParentHubDevice = (UINT8*)XhciGetDeviceContext(Usb3Hc, ParentHubSlotId);
		ParentHubSlotCtx = (XHCI_SLOT_CONTEXT*)XhciGetContextEntry(Usb3Hc, ParentHubDevice, 0);
		SlotCtx->RootHubPort = ParentHubSlotCtx->RootHubPort;
	}

    switch (DeviceSpeed) {
        case USB_HIGH_SPEED_DEVICE: Speed = XHCI_DEVSPEED_HIGH; break;
        case USB_SLOW_SPEED_DEVICE: Speed = XHCI_DEVSPEED_LOW; break;
        case USB_FULL_SPEED_DEVICE: Speed = XHCI_DEVSPEED_FULL; break;
        case USB_SUPER_SPEED_DEVICE: Speed = XHCI_DEVSPEED_SUPER;
    }

    SlotCtx->Speed = Speed;
    
    XfrRing = XhciInitXfrRing(Usb3Hc, SlotId, 0);

    // Initialize the Input default control Endpoint 0 Context
    Ep0Ctx = (XHCI_EP_CONTEXT*)XhciGetContextEntry(Usb3Hc, (UINT8*)Usb3Hc->InputContext, 2);
    Ep0Ctx->EpType = XHCI_EPTYPE_CTL;
    Ep0Ctx->MaxPacketSize = aMaxPacketSize[Speed];
    Ep0Ctx->TrDequeuePtr =  (UINT64)(UINTN)XfrRing->Base + 1;
	Ep0Ctx->AvgTrbLength = 8;
    Ep0Ctx->ErrorCount = 3;

	// Initialize Route String and TT fields
	if (TransactionTranslator != 0)	{
		if (ParentHubSlotCtx->Speed == XHCI_DEVSPEED_SUPER) {	
			for (i = 0; i < 5; i++) {
				if (((ParentHubSlotCtx->RouteString >> (i << 2)) & 0xF) == 0) {
					break;
				}
			}
	        SlotCtx->RouteString = ParentHubSlotCtx->RouteString | (Port << (i << 2));
		} else {
			// Update TT fields in the Slot context for LS/FS device connected to HS hub
	        if (SlotCtx->Speed == XHCI_DEVSPEED_FULL || SlotCtx->Speed == XHCI_DEVSPEED_LOW) {
	            if(ParentHubSlotCtx->Speed == XHCI_DEVSPEED_HIGH) {
					SlotCtx->TtHubSlotId = ParentHubSlotId;
	                SlotCtx->TtPortNumber = (UINT8)(TransactionTranslator >> 7);
	                SlotCtx->MultiTT = ParentHubSlotCtx->MultiTT;
	            } else {
					SlotCtx->TtHubSlotId = ParentHubSlotCtx->TtHubSlotId;
	                SlotCtx->TtPortNumber = ParentHubSlotCtx->TtPortNumber;
	                SlotCtx->MultiTT = ParentHubSlotCtx->MultiTT;
	            }
	        }
		}
	}

    // Assign a new address 4.3.4, 4.6.5
    Status = XhciExecuteCommand(PeiServices, Usb3Hc, XhciTAddressDeviceCmd, &SlotId);
    PEI_ASSERT(PeiServices, Status == EFI_SUCCESS);
	if (Status != EFI_SUCCESS) {
		XhciExecuteCommand(PeiServices, Usb3Hc, XhciTDisableSlotCmd, &SlotId);
		Usb3Hc->DcbaaPtr->DevCntxtAddr[SlotId-1] = 0;
		return Status;
	}
	PEI_TRACE((-1, PeiServices, "PEI_XHCI: new device address %d\n", ((XHCI_SLOT_CONTEXT*)Device)->DevAddr));

    gSlotBeingConfigured = SlotId;  // Valid from now til SetAddress

    return EFI_SUCCESS;
}


//<AMI_PHDR_START>
//---------------------------------------------------------------------------
//
// Procedure:   UpdateDeviceMap
//
// Description: 
//  This function updates SlotId<->Address mapping table.
//
// Output: 
//  EFI_STATUS (Return Value)
//      = EFI_SUCCESS if update is successful
//      = EFI_NOT_FOUND if there is no room for a new entry in the map
//
//---------------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS
UpdateDeviceMap(
    PEI_XHCI_SLOTADDR_MAP   *DeviceMap,
    UINT8   SlotId,
    UINT8   DevAddr
)
{
    UINT8   i;
    PEI_XHCI_SLOTADDR_MAP   *Map = DeviceMap;

    for (i = 0; i < PEI_XHCI_MAX_SLOTS; i++, Map++) {
        if (Map->SlotId == 0) {
            Map->SlotId = SlotId;
            Map->DevAddr = DevAddr;
            return EFI_SUCCESS;
        }
    }
    return EFI_NOT_FOUND;
}


//<AMI_PHDR_START>
//---------------------------------------------------------------------------
//
// Procedure:   GetSlotId
//
// Description: 
//  This function retrieves SlotId from the Slot<->Address mapping table.
//
// Output: 
//  SlotId variable is updated
//  EFI_STATUS (Return Value)
//      = EFI_SUCCESS if update is successful
//      = EFI_NOT_FOUND if the requested Slot is not found in the mapping table
//
//---------------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS
GetSlotId(
    PEI_XHCI_SLOTADDR_MAP   *DeviceMap,
    UINT8   *SlotId,
    UINT8   DevAddr
)
{
    UINT8   i;
    PEI_XHCI_SLOTADDR_MAP   *Map = DeviceMap;

    for (i = 0; i < PEI_XHCI_MAX_SLOTS; i++, Map++) {
        if (Map->DevAddr == DevAddr) {
            *SlotId = Map->SlotId;
            return EFI_SUCCESS;
        }
    }
    return EFI_NOT_FOUND;
}


//<AMI_PHDR_START>
//---------------------------------------------------------------------------
//
// Name:        XhciClearStalledEp
//
// Description:
//  This function is called to restart endpoint. After Endpoint STALLs, it
//  transitions from Halted to Stopped state. It is restored back to Running
//  state by moving the endpoint ring dequeue pointer past the failed control
//  transfer with a Set TR Dequeue Pointer. Then it is restarted by ringing the
//  doorbell. Alternatively endpint is restarted using Configure Endpoint command.
//
// Input:
//  Stalled EP data - SlotId and DCI
//
//---------------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS
XhciClearStalledEp(
    EFI_PEI_SERVICES    **PeiServices,
    USB3_CONTROLLER     *Usb3Hc,
    UINT8       SlotId,
    UINT8       Dci
)
{
    UINT16      EpInfo;
    TRB_RING    *XfrRing;
    EFI_STATUS  Status;
    XHCI_SET_TRPTR_CMD_TRB  Trb;

    // Reset stalled endpoint
    EpInfo = (Dci << 8) + SlotId;
    Status = XhciExecuteCommand(PeiServices, Usb3Hc, XhciTResetEndpointCmd, &EpInfo);
    PEI_ASSERT(PeiServices, Status == EFI_SUCCESS);

    XfrRing = XhciGetXfrRing(Usb3Hc, SlotId, Dci-1);

    Trb.TrPointer = (UINT64)((UINTN)XfrRing->QueuePtr + XfrRing->CycleBit); // Set up DCS
    Trb.EndpointId = Dci;
    Trb.SlotId = SlotId;

    Status = XhciExecuteCommand(PeiServices, Usb3Hc, XhciTSetTRDequeuePointerCmd, &Trb);
    PEI_ASSERT(PeiServices, Status == EFI_SUCCESS);

    return Status;
}


//<AMI_PHDR_START>
//---------------------------------------------------------------------------
//
// Name:        XhciUpdateEp0MaxPacket
//
// Description:
//  This function verifies the MaxPacket size of the control pipe. If it does
//  not match the one received as a part of GET_DESCRIPTOR, then this function
//  updates the MaxPacket data in DeviceContext and HC is notified via
//  EvaluateContext command.
//
// Input:
//  Usb3Hc  Pointer to the HC structure
//  Device  Evaluated device context pointer
//  SlotId  Device context index in DCBAA
//  Endp0MaxPacket  Max packet size obtained from the device
//
//---------------------------------------------------------------------------
//<AMI_PHDR_END>

VOID
XhciUpdateEp0MaxPacket(
    EFI_PEI_SERVICES    **PeiServices,
    USB3_CONTROLLER     *Usb3Hc,
    UINT8               SlotId,
    UINT8               Endp0MaxPacket
)
{
    UINT8   Status;
	UINT8	*DevCtx;
	XHCI_INPUT_CONTROL_CONTEXT	*CtlCtx;
	XHCI_SLOT_CONTEXT			*SlotCtx;
	XHCI_EP_CONTEXT				*EpCtx;

	DevCtx = (UINT8*)XhciGetDeviceContext(Usb3Hc, SlotId);

	SlotCtx = (XHCI_SLOT_CONTEXT*)XhciGetContextEntry(Usb3Hc, DevCtx, 0);
	if (SlotCtx->Speed != XHCI_DEVSPEED_FULL) return;

	EpCtx = (XHCI_EP_CONTEXT*)XhciGetContextEntry(Usb3Hc, DevCtx, 1);
	if (EpCtx->MaxPacketSize == Endp0MaxPacket) return;

    // Prepare input context for EvaluateContext comand
    (**PeiServices).SetMem((UINT8*)Usb3Hc->InputContext, XHCI_INPUT_CONTEXT_ENTRIES * Usb3Hc->ContextSize, 0);

    CtlCtx = (XHCI_INPUT_CONTROL_CONTEXT*)XhciGetContextEntry(Usb3Hc, (UINT8*)Usb3Hc->InputContext, 0);
    CtlCtx->AddContextFlags = BIT1;

	EpCtx = (XHCI_EP_CONTEXT*)XhciGetContextEntry(Usb3Hc, (UINT8*)Usb3Hc->InputContext, 2);
    EpCtx->MaxPacketSize = Endp0MaxPacket;

    Status = XhciExecuteCommand(PeiServices, Usb3Hc, XhciTEvaluateContextCmd, &SlotId);
    PEI_ASSERT(PeiServices, Status == EFI_SUCCESS);
}


//<AMI_PHDR_START>
//---------------------------------------------------------------------------
//
// Procedure:   XhciHcControlTransfer
//
// Description: 
//      This function intiates a USB control transfer and waits on it to 
//      complete.
//
// Input:
//      IN EFI_PEI_SERVICES **PeiServices
//                  --  EFI_PEI_SERVICES pointer
//      IN PEI_USB_HOST_CONTROLLER_PPI *This
//                  --  PEI_USB_HOST_CONTROLLER_PPI pointer
//      IN UINT8 bDeviceAddress
//                  --  USB address of the device for which the control 
//                      transfer is to be issued
//      IN UINT8 DeviceType
//                  --  Not used
//      IN UINT8 MaximumPacketLength
//                  --  Maximum number of bytes that can be sent to or 
//                      received from the endpoint in a single data packet
//      IN EFI_USB_DEVICE_REQUEST *Request
//                  --  EFI_USB_DEVICE_REQUEST pointer
//      IN EFI_USB_DATA_DIRECTION TransferDirection
//                  --  Direction of transfer
//      OPTIONAL IN OUT VOID *DataBuffer        
//                  --  Pointer to source or destination buffer
//      OPTIONAL IN OUT UINTN *DataLength       
//                  --  Length of buffer
//      IN UINTN TimeOut
//                  --  Not used
//      OUT UINT32 *TransferResult
//                  --  Not used
//
// Output: 
//      EFI_STATUS (Return Value)
//                  = EFI_SUCCESS on successful completion
//                      or valid EFI error code
//
//---------------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS XhciHcControlTransfer (
    IN EFI_PEI_SERVICES            **PeiServices,
    IN PEI_USB_HOST_CONTROLLER_PPI *This,
    IN UINT8                       DeviceAddress,
    IN UINT8                       DeviceSpeed,
    IN UINT8                       MaximumPacketLength,
    IN UINT16                      TransactionTranslator    OPTIONAL,
    IN EFI_USB_DEVICE_REQUEST      *Request,
    IN EFI_USB_DATA_DIRECTION      TransferDirection,
    IN OUT VOID *Data              OPTIONAL,
    IN OUT UINTN *DataLength       OPTIONAL,
    IN UINTN                       TimeOut,
    OUT UINT32                     *TransferResult )
{
    USB3_CONTROLLER *Usb3Hc = PEI_RECOVERY_USB_XHCI_DEV_FROM_THIS(This);
    XHCI_TRB    *Trb;
    volatile UINT32 *Doorbell;
    UINT8       SlotId;
    UINT8       CompletionCode;
    UINT8       Status;
    TRB_RING    *XfrRing;
    UINT16      Rq = ((UINT16)Request->Request << 8) + Request->RequestType;

    // Skip SET_ADDRESS request
    if (Request->RequestType == USB_DEV_SET_ADDRESS_REQ_TYPE &&
        Request->Request == USB_DEV_SET_ADDRESS)
    {
        Status = UpdateDeviceMap(Usb3Hc->DeviceMap, gSlotBeingConfigured, (UINT8)Request->Value);
        PEI_ASSERT(PeiServices, Status == EFI_SUCCESS);
        return EFI_SUCCESS;
    }

    if (DeviceAddress == 0) {
        SlotId = gSlotBeingConfigured;
    } else {
        Status = GetSlotId(Usb3Hc->DeviceMap, &SlotId, DeviceAddress);
        PEI_ASSERT(PeiServices, Status == EFI_SUCCESS);
    }

    // Insert Setup, Data(if needed), and Status TRBs into the transfer ring
    XfrRing = XhciGetXfrRing(Usb3Hc, SlotId, 0);

    // Setup TRB
    Trb = XhciAdvanceEnqueuePtr(XfrRing);
    Trb->TrbType = XhciTSetupStage;
    ((XHCI_SETUP_XFR_TRB*)Trb)->Idt = 1;
    *(UINT16*)&((XHCI_SETUP_XFR_TRB*)Trb)->bmRequestType = Rq;
    ((XHCI_SETUP_XFR_TRB*)Trb)->wValue = Request->Value;
    ((XHCI_SETUP_XFR_TRB*)Trb)->wIndex = Request->Index;
    ((XHCI_SETUP_XFR_TRB*)Trb)->wLength = (UINT16)(*DataLength);
    ((XHCI_SETUP_XFR_TRB*)Trb)->XferLength = 8;

	if (Usb3Hc->HciVersion == 0x100) {
		if (*DataLength != 0) {
			if ((Rq & BIT7) != 0) {
				((XHCI_SETUP_XFR_TRB*)Trb)->Trt = XHCI_XFER_TYPE_DATA_IN;
			} else {
				((XHCI_SETUP_XFR_TRB*)Trb)->Trt = XHCI_XFER_TYPE_DATA_OUT;
			}
		} else {
			((XHCI_SETUP_XFR_TRB*)Trb)->Trt = XHCI_XFER_TYPE_NO_DATA;
		}
	}
    
    // Data TRB
    if (*DataLength != 0) {
        Trb = XhciAdvanceEnqueuePtr(XfrRing);
        Trb->TrbType = XhciTDataStage;
        ((XHCI_DATA_XFR_TRB*)Trb)->Dir = ((Rq & BIT7) != 0)? 1 : 0;
        ((XHCI_DATA_XFR_TRB*)Trb)->XferLength = *DataLength;
        ((XHCI_DATA_XFR_TRB*)Trb)->DataBuffer = (UINT64)(UINTN)Data;
    }

    // Status TRB
    Trb = XhciAdvanceEnqueuePtr(XfrRing);
    Trb->TrbType = XhciTStatusStage;
    ((XHCI_STATUS_XFR_TRB*)Trb)->Ioc = 1;
    if ((Rq & BIT7) == 0) {
        ((XHCI_STATUS_XFR_TRB*)Trb)->Dir = 1;   // Status is IN
    }

    // Ring the doorbell and see Event Ring update
    Doorbell = XhciGetTheDoorbell(Usb3Hc, SlotId);
    *Doorbell = 1;  // Control EP0 Enqueue Pointer Update

    Status = XhciWaitForEvent(
                PeiServices, Usb3Hc, Trb, XhciTTransferEvt,
                &CompletionCode, XHCI_CTL_COMPLETE_TIMEOUT_MS, NULL);


    if (CompletionCode == XHCI_TRB_STALL_ERROR) {
        Status = XhciClearStalledEp(PeiServices,
            Usb3Hc, SlotId, 1);    // Dci = 1 for control endpoint
		return 0;
    }

    if (Request->Request == USB_DEV_GET_DESCRIPTOR && *DataLength == 8) {
        // Full speed device requires the update of MaxPacket size
        XhciUpdateEp0MaxPacket(PeiServices, Usb3Hc, SlotId,
            ((EFI_USB_DEVICE_DESCRIPTOR*)Data)->MaxPacketSize0);
    }

    return EFI_SUCCESS;
}


//<AMI_PHDR_START>
//---------------------------------------------------------------------------
//
// Procedure:   XhciHcBulkTransfer
//
// Description: 
//      This function intiates a USB bulk transfer and waits on it to 
//      complete.
//
// Input:
//      IN EFI_PEI_SERVICES **PeiServices
//                  --  EFI_PEI_SERVICES pointer
//      IN PEI_USB_HOST_CONTROLLER_PPI *This
//                  --  PEI_USB_HOST_CONTROLLER_PPI pointer
//      IN UINT8 DeviceAddress
//                  --  USB address of the device for which the control 
//                      transfer is to be issued
//      IN UINT8 EndPointAddress
//                  --  Particular endpoint for the device
//      IN UINT8 MaximumPacketLength
//                  --  Maximum number of bytes that can be sent to or 
//                      received from the endpoint in a single data packet
//      OPTIONAL IN OUT VOID *DataBuffer        
//                  --  Pointer to source or destination buffer
//      OPTIONAL IN OUT UINTN *DataLength       
//                  --  Length of buffer
//      IN OUT UINT8 *DataToggle
//                  --  Used to update the control/status DataToggle field
//                      of the Transfer Descriptor
//      IN UINTN TimeOut
//                  --  Not used
//      OUT UINT32 *TransferResult
//                  --  Not used
//
// Output: 
//      EFI_STATUS (Return Value)
//                  = EFI_SUCCESS on successful completion
//                      or valid EFI error code
//
//---------------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS XhciHcBulkTransfer (
    IN EFI_PEI_SERVICES            **PeiServices,
    IN PEI_USB_HOST_CONTROLLER_PPI *This,
    IN UINT8                       DeviceAddress,
    IN UINT8                       EndPointAddress,
    IN UINT8                       DeviceSpeed,
    IN UINT16                      MaximumPacketLength,
    IN UINT16                      TransactionTranslator    OPTIONAL,
    IN OUT VOID                    *Data,
    IN OUT UINTN                   *DataLength,
    IN OUT UINT8                   *DataToggle,
    IN UINTN                       TimeOut,
    OUT UINT32                     *TransferResult )
{
    USB3_CONTROLLER *Usb3Hc = PEI_RECOVERY_USB_XHCI_DEV_FROM_THIS(This);
    XHCI_TRB    *Trb;
    UINTN       FirstTrb;
    volatile UINT32 *Doorbell;
    UINT8       SlotId;
    UINT8       CompletionCode;
    EFI_STATUS  Status;
    TRB_RING    *XfrRing;
    UINT8       Endpoint;
    UINT8       Dci;
    UINT64      DataPointer;
    UINT32      ResidualData;       // Transferred amount return by Transfer Event
    UINT32      TransferredSize;    // Total transfer amount
    UINT32      RingDataSize;       // One TRB ring transfer amount
    UINT32      RemainingXfrSize;
    UINT32      RemainingDataSize;
    UINT32      XfrSize;
    UINT32      XfrTdSize;
	UINT32		TdPktCnt;
	UINT32		TdSize;

    Endpoint = EndPointAddress;
    Dci = (Endpoint & 0xf)* 2;
    if (Endpoint & BIT7) Dci++;

    GetSlotId(Usb3Hc->DeviceMap, &SlotId, DeviceAddress);

    Doorbell = XhciGetTheDoorbell(Usb3Hc, SlotId);

    XfrRing = XhciGetXfrRing(Usb3Hc, SlotId, Dci-1);

    // Make a chain of TDs to transfer the requested amount of data. If necessary,
    // make multiple transfers in a loop.

    DataPointer = (UINTN)Data;
    RemainingDataSize = *DataLength;

    // Two loops are executing the transfer:
    // The inner loop creates a transfer ring of chained TDs, XHCI_BOT_TD_MAXSIZE
    // bytes each. This makes a ring capable of transferring
    // XHCI_BOT_TD_MAXSIZE * (TRBS_PER_SEGMENT-1) bytes.
    // The outter loop repeats the transfer if the requested transfer size exceeds
    // XHCI_BOT_TD_MAXSIZE * (TRBS_PER_SEGMENT-1).

    for (TransferredSize = 0; TransferredSize < *DataLength;) {
        // Calculate the amount of data to transfer in the ring
        RingDataSize = (RemainingDataSize > XHCI_BOT_MAX_XFR_SIZE)?
            XHCI_BOT_MAX_XFR_SIZE : RemainingDataSize;

        RemainingXfrSize = RingDataSize;
		TdPktCnt = RingDataSize / MaximumPacketLength;

        for (Trb = NULL, XfrSize = 0, FirstTrb = 0; XfrSize < RingDataSize;)
        {
            Trb = XhciAdvanceEnqueuePtr(XfrRing);
            if (FirstTrb == 0) FirstTrb = (UINTN)Trb;

            Trb->TrbType = XhciTNormal;
            ((XHCI_NORMAL_XFR_TRB*)Trb)->Isp = 1;
            ((XHCI_NORMAL_XFR_TRB*)Trb)->DataBuffer = DataPointer;

            // See if we need a TD chain. Note that we do not need to
            // place the chained TRB into Event Ring, since we will not be
            // looking for it anyway. Set IOC only for the last-in-chain TRB.
            if (RemainingXfrSize > XHCI_BOT_TD_MAXSIZE) {
                XfrTdSize = XHCI_BOT_TD_MAXSIZE;
                ((XHCI_NORMAL_XFR_TRB*)Trb)->Chain = 1;
            } else {
                ((XHCI_NORMAL_XFR_TRB*)Trb)->Ioc = 1;
                XfrTdSize = RemainingXfrSize;
            }
			// Data buffers referenced by Transfer TRBs shall not span 64KB boundaries. 
			// If a physical data buffer spans a 64KB boundary, software shall chain 
			// multiple TRBs to describe the buffer.
			if (XfrTdSize > (UINT32)(0x10000 - (DataPointer & (0x10000 - 1))))
			{
				XfrTdSize = (UINT32)(0x10000 - (DataPointer & (0x10000 - 1)));
				((XHCI_NORMAL_XFR_TRB*)Trb)->Chain = 1;
				((XHCI_NORMAL_XFR_TRB*)Trb)->Ioc = 0;
			}

            ((XHCI_NORMAL_XFR_TRB*)Trb)->XferLength = XfrTdSize;
			if(Usb3Hc->HciVersion == 0x100) {
				TdSize = TdPktCnt - ((XfrSize + XfrTdSize)/MaximumPacketLength);
				((XHCI_NORMAL_XFR_TRB*)Trb)->TdSize = (TdSize > 31)? 31 : TdSize;
			} else {
				TdSize = RemainingXfrSize - XfrTdSize;
				((XHCI_NORMAL_XFR_TRB*)Trb)->TdSize = (TdSize < 32768)? (TdSize >> 10) : 31;
			}

            XfrSize += XfrTdSize;
            DataPointer += XfrTdSize;
            RemainingXfrSize -= XfrTdSize;
        }

        // If transfer ring crossed Link TRB, set its Chain flag
        if ((UINTN)Trb < FirstTrb) {
            ((XHCI_NORMAL_XFR_TRB*)XfrRing->LastTrb)->Chain = 1;
        }

        // Ring the door bell and see Event Ring update
        *Doorbell = Dci;

        Status = XhciWaitForEvent(
                PeiServices, Usb3Hc, Trb, XhciTTransferEvt,
                &CompletionCode, XHCI_BULK_COMPLETE_TIMEOUT_MS, &ResidualData);

        // Clear Link TRB chain flag
        ((XHCI_NORMAL_XFR_TRB*)XfrRing->LastTrb)->Chain = 0;

        if (CompletionCode == XHCI_TRB_STALL_ERROR) {
            XhciClearStalledEp(PeiServices, Usb3Hc, SlotId, Dci);
            break;
        }
        TransferredSize += (RingDataSize - ResidualData);
        if (ResidualData != 0) break;   // Short packet detected, no more transfers
        RemainingDataSize -= RingDataSize;
    }

    *DataLength = TransferredSize;

    return Status;
					
}


//<AMI_PHDR_START>
//---------------------------------------------------------------------------
//
// Name:        XhciHcGetRootHubPortNumber
//
// Description:
//  This function returns number of root ports supported by the controller.
//
//---------------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS XhciHcGetRootHubPortNumber (
    IN EFI_PEI_SERVICES            **PeiServices,
    IN PEI_USB_HOST_CONTROLLER_PPI *This,
    OUT UINT8                      *PortNumber )
{
    USB3_CONTROLLER *Usb3Hc = PEI_RECOVERY_USB_XHCI_DEV_FROM_THIS(This);

    *PortNumber = Usb3Hc->MaxPorts;
    return EFI_SUCCESS;
}


//<AMI_PHDR_START>
//---------------------------------------------------------------------------
//
// Name:        UpdatePortStatusSpeed
//
// Description:
//  This function converts XHCI speed definition into the terms
//  of PEI_USB_HOST_CONTROLLER_PPI (namely XHCI_DEVSPEED_xyz is converted
//  into USB_PORT_STAT_xyz).
//
//---------------------------------------------------------------------------
//<AMI_PHDR_END>

VOID
UpdatePortStatusSpeed(
    EFI_PEI_SERVICES    **PeiServices,
    UINT8               Speed,
    UINT16              *PortStatus
)
{
    switch (Speed) {
        case XHCI_DEVSPEED_UNDEFINED:
        case XHCI_DEVSPEED_FULL:
            break;
        case XHCI_DEVSPEED_LOW:
            *PortStatus |= USB_PORT_STAT_LOW_SPEED;
            break;
        case XHCI_DEVSPEED_HIGH:
            *PortStatus |= USB_PORT_STAT_HIGH_SPEED;
            break;
        case XHCI_DEVSPEED_SUPER:
            *PortStatus |= USB_PORT_STAT_SUPER_SPEED;
            break;
        default:
            PEI_TRACE((-1, PeiServices, "XHCI ERROR: unknown device speed.\n"));
    }
}


//<AMI_PHDR_START>
//---------------------------------------------------------------------------
//
// Name:        XhciHcGetRootHubPortStatus
//
// Description:
//  Host controller API function; returns root hub port status in terms of
//  PEI_USB_HOST_CONTROLLER_PPI definition.
//
//---------------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS XhciHcGetRootHubPortStatus (
    IN EFI_PEI_SERVICES            **PeiServices,
    IN PEI_USB_HOST_CONTROLLER_PPI *This,
    IN UINT8                       PortNumber,
    OUT EFI_USB_PORT_STATUS        *PortStatus )
{
    USB3_CONTROLLER *Usb3Hc = PEI_RECOVERY_USB_XHCI_DEV_FROM_THIS(This);
    volatile XHCI_PORTSC *PortSC;

    // Find the proper MMIO access offset for a given port
    PortSC = (XHCI_PORTSC*)((UINTN)Usb3Hc->OpRegs +
                            XHCI_PORTSC_OFFSET + (0x10 * (PortNumber - 1)));

	PEI_TRACE((-1, PeiServices, "XHCI port[%d] status: %08x\n", PortNumber, PortSC->AllBits));

	*(UINT32*)PortStatus = 0;

    if (PortSC->Field.Ccs != 0) {
        PortStatus->PortStatus |= USB_PORT_STAT_CONNECTION;
    }
    if (PortSC->Field.Ped != 0) {
        PortStatus->PortStatus |= USB_PORT_STAT_ENABLE;
    }
    if (PortSC->Field.Oca != 0) {
        PortStatus->PortStatus |= USB_PORT_STAT_OVERCURRENT;
    }
    if (PortSC->Field.Pr != 0) {
        PortStatus->PortStatus |= USB_PORT_STAT_RESET;
    }
    if (PortSC->Field.Pp != 0) {
        PortStatus->PortStatus |= USB_PORT_STAT_POWER;
    }
    if (PortSC->Field.Csc != 0) {
        PortStatus->PortChangeStatus |= USB_PORT_STAT_C_CONNECTION;
    }
    if (PortSC->Field.Pec != 0) {
        PortStatus->PortChangeStatus |= USB_PORT_STAT_C_ENABLE;
    }
    if (PortSC->Field.Occ != 0) {
        PortStatus->PortChangeStatus |= USB_PORT_STAT_C_OVERCURRENT;
    }
    if (PortSC->Field.Prc != 0) {
        PortStatus->PortChangeStatus |= USB_PORT_STAT_C_RESET;
    }

    UpdatePortStatusSpeed(PeiServices, PortSC->Field.PortSpeed, &PortStatus->PortStatus);

    return EFI_SUCCESS;
}


//<AMI_PHDR_START>
//---------------------------------------------------------------------------
//
// Name:        XhciHcSetRootHubPortFeature
//
// Description:
//  Host controller PEI_USB_HOST_CONTROLLER_PPI API function; sets a requested
//  feature of a root hub port.
//
//---------------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS XhciHcSetRootHubPortFeature (
    IN EFI_PEI_SERVICES            **PeiServices,
    IN PEI_USB_HOST_CONTROLLER_PPI *This,
    IN UINT8                       PortNumber,
    IN EFI_USB_PORT_FEATURE        PortFeature )
{
    USB3_CONTROLLER *Usb3Hc = PEI_RECOVERY_USB_XHCI_DEV_FROM_THIS(This);
    volatile XHCI_PORTSC *PortSC;

	if (PortNumber > Usb3Hc->MaxPorts) {
		return EFI_INVALID_PARAMETER;
	}

    PortSC = (XHCI_PORTSC*)((UINTN)Usb3Hc->OpRegs +
                            XHCI_PORTSC_OFFSET + (0x10 * (PortNumber - 1)));
	switch (PortFeature) {
		case EfiUsbPortEnable:
		case EfiUsbPortSuspend:
		    break;

		case EfiUsbPortReset:
			PortSC->AllBits = (PortSC->AllBits & XHCI_PCS_PP) | XHCI_PCS_PR;
		    break;

		case EfiUsbPortPower:
			PortSC->AllBits = XHCI_PCS_PP;
		    break; 

		default:
        	return EFI_INVALID_PARAMETER;
    }

    return EFI_SUCCESS;
}


//<AMI_PHDR_START>
//---------------------------------------------------------------------------
//
// Name:        XhciHcClearRootHubPortFeature
//
// Description:
//  Host controller PEI_USB_HOST_CONTROLLER_PPI API function; clears a requested
//  feature of a root hub port.
//
//---------------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS XhciHcClearRootHubPortFeature (
    IN EFI_PEI_SERVICES            **PeiServices,
    IN PEI_USB_HOST_CONTROLLER_PPI *This,
    IN UINT8                       PortNumber,
    IN EFI_USB_PORT_FEATURE        PortFeature )
{
    USB3_CONTROLLER *Usb3Hc = PEI_RECOVERY_USB_XHCI_DEV_FROM_THIS(This);
    volatile XHCI_PORTSC *PortSC;

    if (PortNumber > Usb3Hc->MaxPorts) {
        return EFI_INVALID_PARAMETER;
    }

    PortSC = (XHCI_PORTSC*)((UINTN)Usb3Hc->OpRegs +
                            XHCI_PORTSC_OFFSET + (0x10 * (PortNumber - 1)));

    switch (PortFeature) {
		case EfiUsbPortEnable:
			PortSC->AllBits = (PortSC->AllBits & XHCI_PCS_PP) | XHCI_PCS_PED;
			break;

		case EfiUsbPortSuspend:
		case EfiUsbPortReset:
		    break;

		case EfiUsbPortPower:
			PortSC->AllBits = (PortSC->AllBits & XHCI_PCS_PP) & ~(XHCI_PCS_PP);
		    break; 

		case EfiUsbPortOwner:
			break;

	    case EfiUsbPortConnectChange:
			PortSC->AllBits = (PortSC->AllBits & XHCI_PCS_PP) | XHCI_PCS_CSC;
	        break;

	    case EfiUsbPortEnableChange:
			PortSC->AllBits = (PortSC->AllBits & XHCI_PCS_PP) | XHCI_PCS_PEC;
	        break;

	    case EfiUsbPortSuspendChange:
			break;

	    case EfiUsbPortOverCurrentChange:
			PortSC->AllBits = (PortSC->AllBits & XHCI_PCS_PP) | XHCI_PCS_OCC;
	        break;

	    case EfiUsbPortResetChange:
			PortSC->AllBits = (PortSC->AllBits & XHCI_PCS_PP) | XHCI_PCS_PRC;
	        break;

	    default:
	        return EFI_INVALID_PARAMETER;
    }

    return EFI_SUCCESS;
}


//<AMI_PHDR_START>
//---------------------------------------------------------------------------
//
// Name:        XhciMmio64Write
//
// Description:
//  MMIO write; depending on 64-bit access availability executes either one
//  64-bit write or two 32-bit writes.
//
//---------------------------------------------------------------------------
//<AMI_PHDR_END>

VOID
XhciMmio64Write(
    USB3_CONTROLLER *Usb3Hc,
    UINTN   Address,
    UINT64  Data
)
{
    if (Usb3Hc->Access64) {
        *(UINT64*)Address = Data;
    }
    else {
        *(UINT32*)Address = (UINT32)Data;
        *(UINT32*)(Address + sizeof(UINT32)) = (UINT32)(Shr64(Data, 32));
    }
}


//<AMI_PHDR_START>
//---------------------------------------------------------------------------
//
// Name:        XhciInitRing
//
// Description:
//  Transfer ring initialization. There is an option to create a Link TRB in
//  the end of the ring.
//
//---------------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS
XhciInitRing (
    IN OUT TRB_RING *Ring,
    IN UINTN    RingBase,
    IN UINT32   RingSize,
    IN BOOLEAN  PlaceLinkTrb
)
{
    XHCI_LINK_TRB   *LinkTrb;

    Ring->Base = (XHCI_TRB*)RingBase;
    Ring->Size = RingSize;
    Ring->LastTrb = Ring->Base + RingSize - 1;
    Ring->CycleBit = 1;
    Ring->QueuePtr = (XHCI_TRB*)RingBase;

    // Initialize ring with zeroes
    {
        UINT8   *p = (UINT8*)RingBase;
        UINTN   i;
        for (i = 0; i < RingSize*sizeof(XHCI_TRB); i++, p++) *p = 0;
    }

    if (PlaceLinkTrb) {
        // Place a Link TRB in the end of the ring pointing to the beginning
        LinkTrb = (XHCI_LINK_TRB*)Ring->LastTrb;
        LinkTrb->NextSegPtr = (UINT64)(UINTN)RingBase;
        LinkTrb->ToggleCycle = 1;
        LinkTrb->TrbType = XhciTLink;
    }

    return EFI_SUCCESS;
}


//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:   XhciAdvanceEnqueuePtr
//
// Description:
//  This function advances returns the pointer to the current TRB and anvances
//  dequeue pointer. If the advance pointer is Link TRB, then it: 1) activates
//  Link TRB by updating its cycle bit, 2) updates dequeue pointer to the value
//  pointed by Link TRB.
//
// Input:
//  Ring - TRB ring to be updated
//
// Output:
//  TRB that can be used for command, transfer, etc.
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

XHCI_TRB*
XhciAdvanceEnqueuePtr(
    TRB_RING    *Ring
)
{
    XHCI_TRB* Trb = Ring->QueuePtr;

    if (Trb->TrbType == XhciTLink) {
        Trb->CycleBit = Ring->CycleBit;
        Ring->CycleBit ^= 1;
        Ring->QueuePtr = Ring->Base;

        Trb = Ring->QueuePtr;
    }
    // Clear the TRB
    {
        UINT32 *p = (UINT32*)Trb;
        UINT8 i = 0;
        for (i=0; i<(sizeof(XHCI_TRB)/sizeof(UINT32)); i++) {
            *p++ = 0;
        }
    }

    Trb->CycleBit = Ring->CycleBit;
    Ring->QueuePtr++;

    return Trb;
}


//<AMI_PHDR_START>
//---------------------------------------------------------------------------
//
// Procedure:   XHCI_ProcessInterrupt
//
// Description: This is the XHCI controller event handler. It walks through
//  the Event Ring and executes the event associated code if needed. Updates
//  the Event Ring Data Pointer in the xHC to let it know which events are
//  completed.
//
// Output:
//  EFI_NOT_READY   - Need more Interrupt processing
//  EFI_SUCCESS     - No interrupts pending
//
//---------------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS
XhciProcessInterrupt(
    EFI_PEI_SERVICES    **PeiServices,
    USB3_CONTROLLER     *Usb3Hc
)
{
    XHCI_TRB        *Trb;
    XHCI_EVENT_TRB  *EvTrb;

    if ((UINT32)Usb3Hc->OpRegs->DcbAap != (UINT32)Usb3Hc->DcbaaPtr) return EFI_SUCCESS;
/*
    if (Usb3Hc->OpRegs->UsbSts.Field.Pcd) {
        XHCI_EnumeratePorts(HcStruc);
        Usb3Hc->OpRegs->UsbSts.AllBits = XHCI_STS_PCD;    // Clear PortChangeDetect
    }
*/
	if (Usb3Hc->OpRegs->UsbSts.Field.Eint)
	{
		Usb3Hc->OpRegs->UsbSts.AllBits = XHCI_STS_EVT_INTERRUPT;
		Usb3Hc->RtRegs->IntRegs[0].IMan |= BIT0;
	}
	
    // Check for pending interrupts:
    // check the USBSTS[3] and IMAN [0] to determine if any interrupt generated
    if (Usb3Hc->EvtRing.QueuePtr->CycleBit != Usb3Hc->EvtRing.CycleBit) return EFI_SUCCESS;

    // See if there are any TRBs waiting in the event ring
    //for (Count = 0; Count < Usb3Hc->EvtRing.Size; Count++) {
    for (;;) {
        Trb = Usb3Hc->EvtRing.QueuePtr;

        if (Trb->CycleBit != Usb3Hc->EvtRing.CycleBit) break;  // past the last

		if (Usb3Hc->EvtRing.QueuePtr == Usb3Hc->EvtRing.LastTrb) {
			// Reached the end of the ring, wrap around
			Usb3Hc->EvtRing.QueuePtr = Usb3Hc->EvtRing.Base;
			Usb3Hc->EvtRing.CycleBit ^= 1;
		} else {
			Usb3Hc->EvtRing.QueuePtr++;
		}
        // TODO:: error manager
        if (Trb->CompletionCode == XHCI_TRB_SHORTPACKET) {
            PEI_TRACE((-1, PeiServices, "PEI_XHCI: short packet detected."));
        }

        if (Trb->CompletionCode == XHCI_TRB_STALL_ERROR) {
            PEI_TRACE((-1, PeiServices, "PEI_XHCI: device STALLs."));
        }

        if (Trb->CompletionCode != XHCI_TRB_SUCCESS
                && Trb->CompletionCode != XHCI_TRB_STALL_ERROR
                && Trb->CompletionCode != XHCI_TRB_SHORTPACKET) {
            PEI_TRACE((-1, PeiServices, "Trb completion code: %d\n", Trb->CompletionCode));
            PEI_ASSERT(PeiServices, FALSE);
        }

        // Process TRB pointed by Usb3Hc->EvtRing->QueuePtr
        EvTrb = (XHCI_EVENT_TRB*)Trb;

        switch (Trb->TrbType) {
            case XhciTTransferEvt:
// very frequent, debug message here might affect timings,
// uncomment only when needed
//              PEI_TRACE((-1, PeiServices, "TransferEvt\n"));

// DEBUG
/*                XhciProcessXferEvt(
                    PeiServices,
                    Usb3Hc,
                    EvTrb->TransferEvt.TrbPtr,
                    EvTrb->TransferEvt.SlotId,
                    EvTrb->TransferEvt.EndpointId);*/
                break;
            case XhciTCmdCompleteEvt:
                PEI_TRACE((-1, PeiServices, "CmdCompleteEvt\n"));
                break;
            case XhciTPortStatusChgEvt:
                PEI_TRACE((-1, PeiServices, "PortStatusChgEvt, port #%d\n", EvTrb->PortStsChgEvt.PortId));
                break;
            case XhciTDoorbellEvt:
                PEI_TRACE((-1, PeiServices, "DoorbellEvt\n"));
                break;
            case XhciTHostControllerEvt:
                PEI_TRACE((-1, PeiServices, "HostControllerEvt\n"));
                break;
            case XhciTDevNotificationEvt:
                PEI_TRACE((-1, PeiServices, "DevNotificationEvt\n"));
                break;
            case XhciTMfIndexWrapEvt:
                PEI_TRACE((-1, PeiServices, "MfIndexWrapEvt\n"));
                break;
            default:
                PEI_TRACE((-1, PeiServices, "UNKNOWN EVENT\n"));
        }
    }
    //PEI_ASSERT(PeiServices, Count<Usb3Hc->EvtRing.Size);    // Event ring is full

	// Update ERDP to inform xHC that we have processed another TRB
    XhciMmio64Write(Usb3Hc,
        (UINTN)&Usb3Hc->RtRegs->IntRegs->Erdp, (UINT64)(UINTN)Usb3Hc->EvtRing.QueuePtr | BIT3);

    return  EFI_SUCCESS;    // Set as interrupt processed
}


//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:   XhciWaitForEvent
//
// Description:
//  This function walks through the active TRBs in the event ring and looks for
//  the command TRB to be complete. If found, returns SlotId and CompletionCode
//  from the completed event TRB. In the end it processes the event ring,
//  adjusting its Dequeue Pointer.
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS
XhciWaitForEvent(
    EFI_PEI_SERVICES    **PeiServices,
    USB3_CONTROLLER     *Usb3Hc,
    XHCI_TRB            *TrbToCheck,
    TRB_TYPE            EventType,
    UINT8               *CompletionCode,
    UINT16              TimeOutMs,
    VOID                *Data
)
{
    XHCI_TRB    *Trb;
    UINT32      TimeOut;
    EFI_STATUS  Status;
    UINT8       CycleBit;
//	UINT32		TimeOutValue = TimeOutMs << 6;	// *64, 15 us unit
	UINT32		TimeOutValue = TimeOutMs + 1;

    for (TimeOut = 0; TimeOut < TimeOutValue; TimeOut++) {
        for (Trb = Usb3Hc->EvtRing.QueuePtr,
			CycleBit = Usb3Hc->EvtRing.CycleBit;;) {
            if (Trb->CycleBit != CycleBit) {
                // Command is not complete, break and retry
                break;
            }

            *CompletionCode = Trb->CompletionCode;
			if (Trb->CompletionCode == XHCI_TRB_STALL_ERROR || 
				Trb->CompletionCode == XHCI_TRB_TRANSACTION_ERROR) {
                Status = EFI_DEVICE_ERROR;
                goto DoneWaiting;
            }

            // Active TRB found
            if (Trb->TrbType == EventType) {
                if ((*(UINTN*)&Trb->Param1) == (UINTN)TrbToCheck) {

                    if (Trb->CompletionCode != XHCI_TRB_SUCCESS && Trb->CompletionCode != XHCI_TRB_SHORTPACKET) {
                        PEI_TRACE((-1, PeiServices, "TRB Completion Error: %d\n", Trb->CompletionCode));
                        PEI_ASSERT(PeiServices, FALSE);
                    }

                    if (EventType == XhciTCmdCompleteEvt) {
                        *(UINT8*)Data = ((XHCI_CMDCOMPLETE_EVT_TRB*)Trb)->SlotId;
                    }
                    if (EventType == XhciTTransferEvt) {
                        if (Data != NULL) {
                            *(UINT32*)Data = ((XHCI_TRANSFER_EVT_TRB*)Trb)->TransferLength;
                        }
                    }

                    Status = (Trb->CompletionCode == XHCI_TRB_SUCCESS ||
                        Trb->CompletionCode == XHCI_TRB_SHORTPACKET)? EFI_SUCCESS:EFI_DEVICE_ERROR;
                    goto DoneWaiting;
                }
            }
            // Advance TRB pointer
            if (Trb == Usb3Hc->EvtRing.LastTrb) {
                Trb = Usb3Hc->EvtRing.Base;
                CycleBit ^= 1;
            } else {
                Trb++;
            }
            if (Trb == Usb3Hc->EvtRing.QueuePtr) {
                // Event ring is full, return error
                PEI_TRACE((-1, PeiServices, "PEI_XHCI: Event Ring is full...\n"));
                PEI_ASSERT(PeiServices, FALSE);
                *CompletionCode = XHCI_TRB_EVENTRINGFULL_ERROR;
                Status = EFI_DEVICE_ERROR;
                break;
            }
        }
//        XHCI_FIXED_DELAY_15MCS(Usb3Hc, 1);    // 15 us out of TimeOutMs
        XHCI_FIXED_DELAY_MS(Usb3Hc, 1);    // 1 ms out of TimeOutMs
    }

    PEI_TRACE((-1, PeiServices, "PEI_XHCI: execution time-out.\n"));

    *CompletionCode = XHCI_TRB_EXECUTION_TIMEOUT_ERROR;
    Status = EFI_DEVICE_ERROR;

DoneWaiting:
    XhciProcessInterrupt(PeiServices, Usb3Hc);

    return Status;
}


//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:   XhciExecuteCommand
//
// Description:
//  This function places a given command in the Command Ring, rings HC doorbell,
//  and waits for the command completion.
//
// Output:
//  EFI_DEVICE_ERROR on execution failure, otherwise EFI_SUCCESS
//  Params - pointer to the command specific data.
//
// Notes:
//  Caller is responsible for a data placeholder.
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS
XhciExecuteCommand(
    EFI_PEI_SERVICES    **PeiServices,
    USB3_CONTROLLER     *Usb3Hc,
    TRB_TYPE            Cmd,
    VOID                *Params
)
{
    volatile UINT32      *Doorbell;
    UINT8       CompletionCode;
    UINT8       SlotId;
    EFI_STATUS  Status;
    XHCI_TRB    *Trb = XhciAdvanceEnqueuePtr(&Usb3Hc->CmdRing);

    Trb->TrbType = Cmd; // Set TRB type

    // Fill in the command TRB fields
    switch (Cmd) {
        case XhciTAddressDeviceCmd:
        case XhciTEvaluateContextCmd:
        case XhciTConfigureEndpointCmd:
            ((XHCI_ADDRESSDEV_CMD_TRB*)Trb)->InpCtxAddress = (UINT64)(UINTN)Usb3Hc->InputContext;
            ((XHCI_ADDRESSDEV_CMD_TRB*)Trb)->SlotId = *((UINT8*)Params);
            ((XHCI_ADDRESSDEV_CMD_TRB*)Trb)->Bsr = 0;
            break;
        case XhciTResetEndpointCmd:
			((XHCI_RESET_EP_CMD_TRB*)Trb)->Tsp = 0;
            ((XHCI_RESET_EP_CMD_TRB*)Trb)->SlotId = *((UINT8*)Params);
            ((XHCI_RESET_EP_CMD_TRB*)Trb)->EndpointId = *((UINT8*)Params+1);
            break;
        case XhciTSetTRDequeuePointerCmd:
            ((XHCI_SET_TRPTR_CMD_TRB*)Trb)->TrPointer = ((XHCI_SET_TRPTR_CMD_TRB*)Params)->TrPointer;
            ((XHCI_SET_TRPTR_CMD_TRB*)Trb)->EndpointId = ((XHCI_SET_TRPTR_CMD_TRB*)Params)->EndpointId;
            ((XHCI_SET_TRPTR_CMD_TRB*)Trb)->SlotId = ((XHCI_SET_TRPTR_CMD_TRB*)Params)->SlotId;
            break;
        case XhciTDisableSlotCmd:
            ((XHCI_DISABLESLOT_CMD_TRB*)Trb)->SlotId = *((UINT8*)Params);
            break;
    }

    // Ring the door bell and see Event Ring update
    Doorbell = (UINT32*)((UINTN)Usb3Hc->CapRegs + Usb3Hc->DbOffset);
    *Doorbell = 0;  // HC doorbell is #0

    Status = XhciWaitForEvent(
                PeiServices, Usb3Hc, Trb, XhciTCmdCompleteEvt,
                &CompletionCode, XHCI_CMD_COMPLETE_TIMEOUT_MS, &SlotId);

    if (Status == EFI_DEVICE_ERROR) {
        PEI_TRACE((-1, PeiServices, "XHCI command completion error code: %d\n", CompletionCode));
        PEI_ASSERT(PeiServices, Status != EFI_DEVICE_ERROR);
        return Status;
    }

    switch (Cmd) {
        case XhciTEnableSlotCmd:
            PEI_TRACE((-1, PeiServices, "PEI_XHCI: Enable Slot command complete, SlotID %d\n", SlotId));
            *((UINT8*)Params) = SlotId;
            break;
        case XhciTEvaluateContextCmd:
            PEI_TRACE((-1, PeiServices, "PEI_XHCI: Evaluate Context command complete.\n"));
            break;
        case XhciTConfigureEndpointCmd:
            PEI_TRACE((-1, PeiServices, "PEI_XHCI: Configure Endpoint command complete.\n"));
            break;
        case XhciTResetEndpointCmd:
            PEI_TRACE((-1, PeiServices, "PEI_XHCI: Reset Endpoint command complete (slot#%x dci#%x).\n",
                *((UINT8*)Params), *((UINT8*)Params+1)));
            break;
        case XhciTSetTRDequeuePointerCmd:
            PEI_TRACE((-1, PeiServices, "PEI_XHCI: Set TR pointer command complete.\n"));
            break;
        case XhciTDisableSlotCmd:
            PEI_TRACE((-1, PeiServices, "PEI_XHCI: DisableSlot command complete.\n"));
            break;
    }

    return EFI_SUCCESS;
}


//<AMI_PHDR_START>
//---------------------------------------------------------------------------
//
// Name:        XhciInitXfrRing
//
// Description:
//  This function initializes transfer ring of given endpoint
//
// Output:
//  Pointer to the transfer ring
//
//---------------------------------------------------------------------------
//<AMI_PHDR_END>

TRB_RING*
XhciInitXfrRing(
    USB3_CONTROLLER* Usb3Hc,
    UINT8   Slot,
    UINT8   Ep
)
{
    TRB_RING    *XfrRing = Usb3Hc->XfrRings + (Slot-1)*32 + Ep;
    UINTN       Base = Usb3Hc->XfrTrbs + ((Slot-1)*32+Ep)*RING_SIZE;

    XhciInitRing(XfrRing, Base, TRBS_PER_SEGMENT, TRUE);

    return XfrRing;
}


//<AMI_PHDR_START>
//---------------------------------------------------------------------------
//
// Name:        XhciTranslateInterval
//
// Description:
//  This routine calculates the Interval field to be used in device's endpoint
//  context. Interval is calculated using the following rules (Section 6.2.3.6):
//
//  For SuperSpeed bulk and control endpoints, the Interval field shall not be
//  used by the xHC. For all other endpoint types and speeds, system software
//  shall translate the bInterval field in the USB Endpoint Descriptor to the
//  appropriate value for this field.
//
//  For high-speed and SuperSpeed Interrupt and Isoch endpoints the bInterval
//  field the Endpoint Descriptor is computed as 125æs * 2^(bInterval-1), where
//  bInterval = 1 to 16, therefore Interval = bInterval - 1.
//
//  For low-speed Interrupt and full-speed Interrupt and Isoch endpoints the
//  bInterval field declared by a Full or Low-speed device is computed as
//  bInterval * 1ms., where bInterval = 1 to 255.
//
//  For Full- and Low-speed devices software shall round the value of Endpoint
//  Context Interval field down to the nearest base 2 multiple of bInterval * 8.
//
// Input:
//  EpType      Endpoint type, see XHCI_EP_CONTEXT.DW1.EpType field definitions
//  Speed       Endpoint speed, 1..4 for XHCI_DEVSPEED_FULL, _LOW, _HIGH, _SUPER
//  Interval    Poll interval value from endpoint descriptor
//
// Output:
//  Interval value to be written to the endpoint context
//
//---------------------------------------------------------------------------
//<AMI_PHDR_END>

UINT8
XhciTranslateInterval(
    UINT8   EpType,
    UINT8   Speed,
    UINT8   Interval
)
{
    UINT8  TempData;
    UINT8  BitCount;

    if (EpType == XHCI_EPTYPE_CTL || 
        EpType == XHCI_EPTYPE_BULK_OUT || 
        EpType == XHCI_EPTYPE_BULK_IN) {

        if (Speed == XHCI_DEVSPEED_HIGH) {
            return Interval;
        } else {
            return 0;   // Interval field will not be used for LS, FS and SS
        }
    }

    // Control and Bulk endpoints are processed; translate intervals for Isoc and Interrupt
    // endpoints

    // Translate SS and HS endpoints
    if (Speed == XHCI_DEVSPEED_SUPER || Speed == XHCI_DEVSPEED_HIGH) {
        return (Interval - 1);
    }

    for (TempData = Interval, BitCount = 0; TempData != 0; BitCount++) {
        TempData >>= 1;
    }
    return (BitCount + 2);  // return value, where Interval = 0.125*2^value
}


//<AMI_PHDR_START>
//---------------------------------------------------------------------------
//
// Name:        XhciEnableEndpoints
//
// Description:
//  This function parses the device descriptor data and enables the endpoints
//  by 1)assigning the Transfer TRB and 2)executing ConfigureEndpoint command
//  for the slot. Section 4.3.5.
//
// Input:
//  Desc    - Device Configuration Descriptor data pointer
//
// Output:
//  EFI_DEVICE_ERROR on error, EFI_SUCCESS on success
//
// Notes:
//  1) This call is executed before SET_CONFIGURATION control transfer
//  2) Device slot is addressed by gSlotBeingConfigured
//  3) EP0 information is valid in the Device
//
//---------------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS
XhciEnableEndpoints (
    IN EFI_PEI_SERVICES            **PeiServices,
    IN PEI_USB_HOST_CONTROLLER_PPI *This,
    IN UINT8                       *Desc
)
{
    UINT16          TotalLength;
    UINT16          CurPos;
    UINT8           Dci;
	EFI_USB_INTERFACE_DESCRIPTOR    *IntrfDesc;
    EFI_USB_ENDPOINT_DESCRIPTOR     *EpDesc;
    TRB_RING        *XfrRing;
    UINT8           EpType;
    UINT8           Status;
	UINT8			IsHub;
	UINT8			DevSpeed;
	XHCI_INPUT_CONTROL_CONTEXT	*CtlCtx;
	XHCI_SLOT_CONTEXT			*SlotCtx;
	XHCI_EP_CONTEXT 			*EpCtx;

    USB3_CONTROLLER *Usb3Hc = PEI_RECOVERY_USB_XHCI_DEV_FROM_THIS(This);
    UINT8 SlotId = gSlotBeingConfigured;
    UINT8 *DevCtx = (UINT8*)XhciGetDeviceContext(Usb3Hc, SlotId);

    if (((EFI_USB_CONFIG_DESCRIPTOR*)Desc)->DescriptorType != USB_DT_CONFIG) return EFI_DEVICE_ERROR;

	SlotCtx = (XHCI_SLOT_CONTEXT*)XhciGetContextEntry(Usb3Hc, DevCtx, 0);
	DevSpeed = SlotCtx->Speed;

    // Note (From 4.6.6): The Add Context flag A1 and Drop Context flags D0 and D1
    // of the Input Control Context (in the Input Context) shall be cleared to 0.
    // Endpoint 0 Context does not apply to the Configure Endpoint Command and
    // shall be ignored by the xHC. A0 shall be set to 1.

    // Note (From 6.2.2.2): If Hub = 1 and Speed = High-Speed (3), then the
    // TT Think Time and Multi-TT (MTT) fields shall be initialized.
    // If Hub = 1, then the Number of Ports field shall be initialized, else
    // Number of Ports = 0.

    // Prepare input context for EvaluateContext comand
    (**PeiServices).SetMem((UINT8*)Usb3Hc->InputContext, XHCI_INPUT_CONTEXT_ENTRIES * Usb3Hc->ContextSize, 0);

    CtlCtx = (XHCI_INPUT_CONTROL_CONTEXT*)XhciGetContextEntry(Usb3Hc, (UINT8*)Usb3Hc->InputContext, 0);
    CtlCtx->AddContextFlags = BIT0;    // EP0

	SlotCtx = (XHCI_SLOT_CONTEXT*)XhciGetContextEntry(Usb3Hc, (UINT8*)Usb3Hc->InputContext, 1);

    // Collect the endpoint information and update the Device Input Context
    TotalLength = ((EFI_USB_CONFIG_DESCRIPTOR*)Desc)->TotalLength;

    if (TotalLength > (MAX_CONTROL_DATA_SIZE - 1)) {
        TotalLength = MAX_CONTROL_DATA_SIZE - 1;
    }

    for (CurPos = 0; CurPos < TotalLength; CurPos += EpDesc->Length) {
		EpDesc = (EFI_USB_ENDPOINT_DESCRIPTOR*)(IntrfDesc = (EFI_USB_INTERFACE_DESCRIPTOR*)(Desc + CurPos));
	
		if (IntrfDesc->DescriptorType == USB_DT_INTERFACE) {
			IsHub = IntrfDesc->InterfaceClass == BASE_CLASS_HUB;
			continue;
		}
	
        if (EpDesc->DescriptorType != USB_DT_ENDPOINT) continue;

        // Found Endpoint, fill up the information in the InputContext

        // Calculate Device Context Index (DCI), Section 4.5.1.
        // 1) For Isoch, Interrupt, or Bulk type endpoints the DCI is calculated
        // from the Endpoint Number and Direction with the following formula:
        //  DCI = (Endpoint Number * 2) + Direction, where Direction = 0 for OUT
        // endpoints and 1 for IN endpoints.
        // 2) For Control type endpoints:
        //  DCI = (Endpoint Number * 2) + 1
        //
        // Also calculate XHCI EP type out of EpDesc->bEndpointFlags

        if ((EpDesc->Attributes & EP_DESC_FLAG_TYPE_BITS) == EP_DESC_FLAG_TYPE_CONT) {
            Dci = (EpDesc->EndpointAddress & 0xf) * 2 + 1;
            EpType = XHCI_EPTYPE_CTL;
        } else {
            // Isoc, Bulk or Interrupt endpoint
            Dci = (EpDesc->EndpointAddress & 0xf) * 2;
            EpType = EpDesc->Attributes & EP_DESC_FLAG_TYPE_BITS;   // 1, 2, or 3

            if (EpDesc->EndpointAddress & BIT7) {
                Dci++;          // IN
                EpType += 4;    // 5, 6, or 7
            }
        }

        // Update ContextEntries in the Slot context
        if (Dci > SlotCtx->ContextEntries) {
            SlotCtx->ContextEntries = Dci;
        }

        EpCtx = (XHCI_EP_CONTEXT*)XhciGetContextEntry(Usb3Hc, (UINT8*)Usb3Hc->InputContext, Dci + 1);

        EpCtx->EpType = EpType;
        EpCtx->MaxPacketSize = EpDesc->MaxPacketSize;
        EpCtx->ErrorCount = 3;

        // Set Interval 
        EpCtx->Interval = XhciTranslateInterval(EpType, DevSpeed, EpDesc->Interval);

        XfrRing = XhciInitXfrRing(Usb3Hc, SlotId, Dci - 1);
        EpCtx->TrDequeuePtr = (UINT64)(UINTN)XfrRing->Base + 1;

        CtlCtx->AddContextFlags |= (1 << Dci);
    }

    // For a HUB update NumberOfPorts and TTT fields in the Slot context. For that get hub descriptor
    // and use bNbrPorts and TT Think time fields (11.23.2.1 of USB2 specification)
    // Notes:
    //  - Slot.Hub field is already updated
    //  - Do not set NumberOfPorts and TTT fields for 0.95 controllers

	if (IsHub) {

		EFI_STATUS	Status;
        EFI_USB_HUB_DESCRIPTOR  HubDesc;
        UINT8   Speed;
        EFI_USB_DEVICE_REQUEST  DevReq;
        UINT32  Timeout;
        UINTN   DataLength = sizeof(EFI_USB_HUB_DESCRIPTOR);
        UINT32  TransferResult;

        //
        // Fill Device request packet
        //
        (**PeiServices).SetMem((VOID*)&DevReq, sizeof(EFI_USB_DEVICE_REQUEST), 0);
        DevReq.RequestType = USB_RT_HUB | 0x80;
        DevReq.Request = USB_DEV_GET_DESCRIPTOR;
		DevReq.Value = DevSpeed == XHCI_DEVSPEED_SUPER ? USB_DT_SS_HUB << 8 : USB_DT_HUB << 8;
        DevReq.Index = 0;
        DevReq.Length = sizeof(EFI_USB_HUB_DESCRIPTOR);
    
        Timeout = 3000;

        switch (DevSpeed) {
            case XHCI_DEVSPEED_HIGH: Speed = USB_HIGH_SPEED_DEVICE; break;
            case XHCI_DEVSPEED_LOW: Speed = USB_SLOW_SPEED_DEVICE; break;
            case XHCI_DEVSPEED_FULL: Speed = USB_FULL_SPEED_DEVICE; break;
            case XHCI_DEVSPEED_SUPER: Speed = USB_SUPER_SPEED_DEVICE;
        }

		EpCtx = (XHCI_EP_CONTEXT*)XhciGetContextEntry(Usb3Hc, DevCtx, 1);

		Status = XhciHcControlTransfer(PeiServices, This,
            0,  // Current address
            Speed,
            EpCtx->MaxPacketSize,
            0,  // Transaction translator
            &DevReq,
            EfiUsbDataIn,
            &HubDesc,
            &DataLength,
            Timeout,
            &TransferResult);

		if (!EFI_ERROR(Status)) {
			SlotCtx->Hub = 1;
			SlotCtx->PortsNum = HubDesc.NbrPorts;
		
			if (DevSpeed == XHCI_DEVSPEED_HIGH) {
				SlotCtx->TThinkTime = (HubDesc.HubCharacteristics[0] >> 5) & 0x3;
			}
		}
	}

// check route string here
    // Input context is updated with the endpoint information. Execute ConfigureEndpoint command.
    Status = XhciExecuteCommand(PeiServices, Usb3Hc, XhciTConfigureEndpointCmd, &SlotId);
    PEI_ASSERT(PeiServices, Status == EFI_SUCCESS);

    return Status;
}

//<AMI_PHDR_START>
//---------------------------------------------------------------------------
//
// Name:        XhciGetXfrRing
//
// Description:
//  This routine calculates the address of the address ring of a particular
//  Slot/Endpoint.
//
// Output:
//  Pointer to the transfer ring
//
//---------------------------------------------------------------------------
//<AMI_PHDR_END>

TRB_RING*
XhciGetXfrRing(
    USB3_CONTROLLER* Usb3Hc,
    UINT8   Slot,
    UINT8   Ep
)
{
    return Usb3Hc->XfrRings + (Slot-1)*32 + Ep;
}


//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:   XhciGetTheDoorbell
//
// Description:
//  This function calculates and returns the pointer to a doorbell for a
//  given Slot.
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

UINT32*
XhciGetTheDoorbell(
    USB3_CONTROLLER    *Usb3Hc,
    UINT8              SlotId
)
{
    return (UINT32*)((UINTN)Usb3Hc->CapRegs + Usb3Hc->DbOffset + sizeof(UINT32)*SlotId);
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:   XhciGetDeviceContext
//
// Description:
//  This function calculates and returns the pointer to a device context for
//  a given Slot.
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

UINT8*
XhciGetDeviceContext(
	USB3_CONTROLLER	*Usb3Hc,
	UINT8			SlotId
)
{
	UINT32 DevCtxSize = XHCI_DEVICE_CONTEXT_ENTRIES * Usb3Hc->ContextSize;
	return (UINT8*)((UINTN)Usb3Hc->DeviceContext + (SlotId - 1) * DevCtxSize);
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:   XhciGetContextEntry
//
// Description:
//  This function calculates and returns the pointer to a context entry for
//  a given index.
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

UINT8*
XhciGetContextEntry(
	USB3_CONTROLLER	*Usb3Hc,
	VOID			*Context,
	UINT8			Index
)
{
	return (UINT8*)((UINTN)Context + Index * Usb3Hc->ContextSize);
}
										//(EIP75547+)>
//<AMI_PHDR_START>
//---------------------------------------------------------------------------
//
// Name:        XhciEnableUsb2Port
//
// Description:
//
//---------------------------------------------------------------------------
//<AMI_PHDR_END>

VOID
XhciResetUsb2Port(
    EFI_PEI_SERVICES    **PeiServices,
    USB3_CONTROLLER *Usb3Hc
)
{
    UINT8	    Count;
    UINT8       PortNumber;
    volatile    XHCI_PORTSC *PortSC;
    UINT32      i;
    
    if (Usb3Hc->Usb2Protocol) {
		for(Count = 0; Count < Usb3Hc->Usb2Protocol->PortCount; Count++) {
			PortNumber = Count + Usb3Hc->Usb2Protocol->PortOffset;
			PortSC =(XHCI_PORTSC*)((UINTN)Usb3Hc->OpRegs +
                            XHCI_PORTSC_OFFSET + (0x10 * (PortNumber - 1)));
            if (PortSC->Field.Ccs) {
                if(!(PortSC->Field.Ped)) {
                    PortSC->AllBits = XHCI_PCS_PR | XHCI_PCS_PP;
                    for (i = 0; i < 200; i++) {
			            XHCI_FIXED_DELAY_MS(Usb3Hc, 1);
			            if (PortSC->Field.Prc) break;
		            }
                    PortSC->AllBits = XHCI_PCS_WRC | XHCI_PCS_PRC | XHCI_PCS_PP;
                }
            }
		}
	}
    
 }
 
//<AMI_PHDR_START>
//---------------------------------------------------------------------------
//
// Name:        XhciExtCapParser
//
// Description:
//
//---------------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS
XhciExtCapParser(
    EFI_PEI_SERVICES    **PeiServices,
    USB3_CONTROLLER *Usb3Hc
)
{
	XHCI_EXT_CAP	*CurPtr;

	if (Usb3Hc->CapRegs->HcParams.Xecp == 0) return EFI_SUCCESS;

	// Starts from first capability
	CurPtr = (XHCI_EXT_CAP *)((UINTN)Usb3Hc->CapRegs + (Usb3Hc->CapRegs->HcParams.Xecp << 2));

    // Traverse all capability structures
	for(;;) {
		switch (CurPtr->CapId) {
			case XHCI_EXT_CAP_USB_LEGACY:
                break;
			case XHCI_EXT_CAP_SUPPORTED_PROTOCOL:
				if (((XHCI_EXT_PROTOCOL*)CurPtr)->MajorRev == 0x02) {
					Usb3Hc->Usb2Protocol = (XHCI_EXT_PROTOCOL*)CurPtr;
					PEI_TRACE((-1, PeiServices, "XHCI: USB2 Support Protocol %x, PortOffset %x PortCount %x\n", 
						Usb3Hc->Usb2Protocol, Usb3Hc->Usb2Protocol->PortOffset, Usb3Hc->Usb2Protocol->PortCount));
				} else if (((XHCI_EXT_PROTOCOL*)CurPtr)->MajorRev == 0x03) {
					Usb3Hc->Usb3Protocol = (XHCI_EXT_PROTOCOL*)CurPtr;
					PEI_TRACE((-1, PeiServices, "XHCI: USB3 Support Protocol %x, PortOffset %x PortCount %x\n", 
						Usb3Hc->Usb3Protocol, Usb3Hc->Usb3Protocol->PortOffset, Usb3Hc->Usb3Protocol->PortCount));
				}
				break;

			case XHCI_EXT_CAP_POWERMANAGEMENT:
			case XHCI_EXT_CAP_IO_VIRTUALIZATION:
			case XHCI_EXT_CAP_USB_DEBUG_PORT:
				break;
		}
		if(CurPtr->NextCapPtr == 0) break;
	    // Point to next capability
	    CurPtr=(XHCI_EXT_CAP *)((UINTN)CurPtr+ (((UINTN)CurPtr->NextCapPtr) << 2));
	}

	return EFI_SUCCESS;
}
										//(EIP75547+)

//**********************************************************************
//**********************************************************************
//**                                                                  **
//**        (C)Copyright 1985-2010, American Megatrends, Inc.         **
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
