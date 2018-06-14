//**********************************************************************
//**********************************************************************
//**                                                                  **
//**        (C)Copyright 1985-2006, American Megatrends, Inc.         **
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
// $Header: /Alaska/SOURCE/Modules/USBRecovery/OhciPei.c 12    11/24/12 5:44a Ryanchou $
//
// $Revision: 12 $
//
// $Date: 11/24/12 5:44a $
//
//**********************************************************************
// Revision History
// ----------------
// $Log: /Alaska/SOURCE/Modules/USBRecovery/OhciPei.c $
// 
// 12    11/24/12 5:44a Ryanchou
// [TAG]  		EIP103990
// [Category]  	Improvement
// [Description]  	Synchronized with USB PEI module 4.6.3_USB_08.10.24.
// [Files]  		EhciPei.c, EhciPei.h, OhciPei.c, OhciPei.h, UhcPeim.c,
// BotPeim.c, BotPeim.h, PeiAtapi.c, UsbBotPeim.c, UsbBotPeim.h,
// HubPeim.c, UsbPeim.c, XhciPei.c, XhciPei.h, HubPeim.h, PeiUsbLib.c,
// PeiUsbLib.h, UsbPeim.h
// 
// 11    8/23/12 9:59p Wilsonlee
// [TAG]  		EIP97069
// [Category]  	Improvement
// [Description]  	Reset root port algorythm update.
// [Files]  		EhciPei.c, EhciPei.h, OhciPei.c, OhciPei.h, UhcPeim.c,
// UhcPeim.h, UsbPeim.c, usb.h
// 
// 10    1/18/11 12:59a Ryanchou
// [TAG]  		EIP47931
// [Category]  	Improvement
// [Description]  	Added USB 3.0 hub support.
// [Files]  		EhciPei.c, EhciPei.h, HubPeim.c, HubPeim.h, OhciPei.c,
// OhciPei.h, UhcPeim.c, UhcPeim.h, usb.h, UsbHostController.h,
// UsbIoPeim.c, UsbPeim.c, UsbPeim.h, XhciPei.c, XhciPei.h
// 
// 9     10/11/10 4:51p Olegi
// XHCI support added.
// 
// 8     3/17/09 5:09p Olegi
// Added TransactionTranslator for slow/full speed devices behind USB2
// hub.
// 
// 7     3/03/09 7:26p Olegi
// MaximumPacketLength changed from UINT8 to UINT16.
// 
// 6     10/21/08 5:57p Michaela
// Added EHCI-related fixes for issues 
// that may occur if EHCI is used before 
// USB Recovery is invoked:
//   Added SDL Tokens: 
//     PEI_EHCI_PCI_BDFS and 
//     PEI_EHCI_MEM_BASE_ADDRESSES. 
// 
// Removed/modified some debugging 
// development code:
//   Removed SDL Tokens: 
//     USBR_DEBUG_SUPPORT and 
//     USBR_SERIAL_PORT_AVAILABLE 
//   Removed Elinks: 
//     UsbRecoveryDebug_DIR and 
//     $(BUILD_DIR)\UsbRecoveryDebugDxe.ffs 
//   Modified SDL Token: 
//     FORCE_RECOVERY to default value of 0. 
// 
// (See this module's Help documentation 
// for more information.)
// 
// 5     7/29/08 5:50p Michaela
// 1) Updated code to move most porting tasks to SDL
// 2) Added more debug break points and improved interactive
//     debugging capability for when a serial port is not available.
// 3) Updated help files
// 
// 4     7/18/08 5:04p Michaela
// 1  File-level debugging is now available
// 2  AMI_USB_DEBUG_INTERFACE.WaitConsoleKey() now returns
//    the keypress so that conditional debugging can
//    be dynamic (alphanumeric keys only)
// 3  Added more function headers.
// 4  Removed code that will never be used (I.e., Bala?).
// 5  Moved typedef, contants and extern declarations
//    into header files.
// 6  Now all controller blocks are enabled for SB700
//    (EHCI controllers route to companion controller
//    by default)
// 7  Removed unused constants and typedefs n OhciPei.h
//    (also reorganized the file to make it more 
//    readable.)
// 8  Renamed many functions/variables according to
//    coding standard.
// 9  Removed code initializing data structures for
//    periodic lists, as this is not needed.
// 10 Removed the CONTROLLER_TYPE SDL token to
//    allow UHCI and OHCI controllers to supported
//    simultaneously. (modified MAKE files 
//    accordingly)
// 
// 3     7/10/08 6:36p Michaela
// Updated to support OHCI controllers
//
// 2     9/22/06 12:23p Sivagarn
// - Included appropriate headers for flies and functions
// - Updated copyright messages
// - Merged multiple MAK and SDL files into one MAK and SDL file
// - Removed unnecessary files
//
//
//**********************************************************************

//<AMI_FHDR_START>
//----------------------------------------------------------------------------
//
// Name:    OhciPei.c
//
// Description:
//  This file is the main source file for the OHCI PEI USB
//  recovery module.  Its entry point at OhciPeiUsbEntryPoint
//  will be executed from the UsbRecoveryInitialize INIT_LIST.
//
//----------------------------------------------------------------------------
//<AMI_FHDR_END>

#include <PEI.h>
#include <AmiPeiLib.h>
#include <token.h>
#include <PPI\PeiGetUCtrl.h>
#include <PPI\OhciPPI.h>
#include <PPI\stall.h>
#include "Ppi\UsbHostController.h"
#include "OhciPei.h"
#include "usb.h"

// List of PCI addresses for OHCI controllers
extern PCI_BUS_DEV_FUNCTION gOhciControllerPciTable[];
extern UINT16   gOhciControllerCount;

extern EFI_GUID gPeiStallPpiGuid;
extern EFI_GUID gPeiUsbHostControllerPpiGuid;
extern EFI_STATUS OhciPeiBoardInit (
    IN EFI_PEI_SERVICES **PeiServices,
    EFI_PEI_PCI_CFG_PPI *PciCfgPpi,
    EFI_PEI_STALL_PPI   *StallPpi );
extern VOID ZeroMem (
    OUT VOID    *Buffer,
    IN  UINTN   Size );

//<AMI_PHDR_START>
//---------------------------------------------------------------------------
//
// Procedure:   OhciGetOperationalRegisterBase
//
// Description: 
//      This function uses ControllerIndex and the global PCI_BUS_DEV_FUNCTION
//      array to access a particular controller's PCI configuration space in 
//      order to obtain the Operational Register base address.
//
// Input:
//      IN EFI_PEI_SERVICES **PeiServices
//                  --  PEI Sevices table pointer
//      IN UINT16 ControllerIndex
//                  --  Index of the controller in the global
//                      PCI_BUS_DEV_FUNCTION array
//
// Output: 
//      UINT32 (Return Value)
//                  = Base address for this controller's operational
//                      registers.
//
//---------------------------------------------------------------------------
//<AMI_PHDR_END>

UINT32 OhciGetOperationalRegisterBase (
    IN EFI_PEI_SERVICES     **PeiServices,
    IN UINT16               ControllerIndex )
{
    UINT32 OhciBaseAddress;

    (*PeiServices)->PciCfg->Read(
        PeiServices,
        (*PeiServices)->PciCfg,
        EfiPeiPciCfgWidthUint32,
        OHCI_PCI_ADDRESS( ControllerIndex, OHCI_BASE_ADDR_REG ),
        &OhciBaseAddress
    );


    return OhciBaseAddress &= 0xfffffff0;    // Mask lower bits
}


//<AMI_PHDR_START>
//---------------------------------------------------------------------------
//
// Procedure:   OhciPeiUsbEntryPoint
//
// Description: 
//      This is the entry point into the OHCI controller initialization
//      subsystem.
//
// Input:
//      IN EFI_FFS_FILE_HEADER *FfsHeader
//                  --  EFI_FFS_FILE_HEADER pointer
//      IN EFI_PEI_SERVICES **PeiServices
//                  --  EFI_PEI_SERVICES pointer
//
// Output: 
//      EFI_STATUS (Return Value)
//                  = EFI_SUCCESS on successful completion
//                      or valid EFI error code
//
//---------------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS OhciPeiUsbEntryPoint (
    IN EFI_FFS_FILE_HEADER *FfsHeader,
    IN EFI_PEI_SERVICES    **PeiServices )
{
    UINT8                Index;
    UINTN                MemPages;
    EFI_STATUS           Status;
    EFI_PHYSICAL_ADDRESS TempPtr;
    PEI_OHCI_DEV         *OhciDevPtr;
    EFI_PEI_STALL_PPI    *StallPpi;

    //-------------------------------------------
    // Initialize the EFI_PEI_STALL_PPI interface
    //-------------------------------------------
    Status = (**PeiServices).LocatePpi( PeiServices, &gPeiStallPpiGuid,
        0, NULL, &StallPpi );
    if ( EFI_ERROR( Status ) ) {
        return EFI_UNSUPPORTED;
    }

    //-----------------------------------------
    // board specific initialization to program
    // PCI bridges and enable MMIO
    //-----------------------------------------

    Status = OhciPeiBoardInit(
        PeiServices,
        (*PeiServices)->PciCfg,
        StallPpi );
    if ( EFI_ERROR( Status ) ) {
        return EFI_UNSUPPORTED;
    }

    //----------------------------------------------------------
    // Allocate OHCI DEVICE OBJECT that holds all necessary
    // information for the Host Controller operational registers
    // for each controller.  Initialze the controller and setup
    // data structures for ready for operation
    //----------------------------------------------------------

    for (Index = 0; Index < gOhciControllerCount; Index++)
    {

        // PAGESIZE = 0x1000
        MemPages = sizeof (PEI_OHCI_DEV) / 0x1000 + 1;
        Status = (**PeiServices).AllocatePages(
            PeiServices,
            EfiConventionalMemory,
            MemPages,
            &TempPtr
                 );
        if ( EFI_ERROR( Status ) )
        {
            return EFI_OUT_OF_RESOURCES;
        }

        OhciDevPtr = (PEI_OHCI_DEV *) ( (UINTN) TempPtr );
        OhciDevPtr->Signature = PEI_OHCI_DEV_SIGNATURE;
        OhciDevPtr->PeiServices = PeiServices;
        OhciDevPtr->CpuIoPpi = (*PeiServices)->CpuIo;
        OhciDevPtr->StallPpi = StallPpi;
        OhciDevPtr->PciCfgPpi = (*PeiServices)->PciCfg;
        ;
        OhciDevPtr->UsbHostControllerBaseAddress =
            OhciGetOperationalRegisterBase( PeiServices, Index );

        //Initialize the OHCI Controller for operation

        OhciInitHC( PeiServices, OhciDevPtr, Index );  // 0xff03

        //Setup PPI entry point
        OhciDevPtr->UsbHostControllerPpi.ControlTransfer =
            OhciHcControlTransfer;
        OhciDevPtr->UsbHostControllerPpi.BulkTransfer =
            OhciHcBulkTransfer;
        OhciDevPtr->UsbHostControllerPpi.GetRootHubPortNumber =
            OhciHcGetRootHubPortNumber;
        OhciDevPtr->UsbHostControllerPpi.GetRootHubPortStatus =
            OhciHcGetRootHubPortStatus;
        OhciDevPtr->UsbHostControllerPpi.SetRootHubPortFeature =
            OhciHcSetRootHubPortFeature;
        OhciDevPtr->UsbHostControllerPpi.ClearRootHubPortFeature =
            OhciHcClearRootHubPortFeature;
        OhciDevPtr->UsbHostControllerPpi.PreConfigureDevice = NULL;
        OhciDevPtr->UsbHostControllerPpi.EnableEndpoints = NULL;

        OhciDevPtr->PpiDescriptor.Flags =
            (EFI_PEI_PPI_DESCRIPTOR_PPI |
             EFI_PEI_PPI_DESCRIPTOR_TERMINATE_LIST);
        OhciDevPtr->PpiDescriptor.Guid = &gPeiUsbHostControllerPpiGuid;
        OhciDevPtr->PpiDescriptor.Ppi = &OhciDevPtr->UsbHostControllerPpi;

        //Now is the time to install the PPI
        Status = (**PeiServices).InstallPpi(
            PeiServices, &OhciDevPtr->PpiDescriptor );
        if ( EFI_ERROR( Status ) )
        {
            return EFI_NOT_FOUND;
        }

    }
    
    return EFI_SUCCESS;

}


//<AMI_PHDR_START>
//---------------------------------------------------------------------------
//
// Procedure:   OhciInitHcca
//
// Description: 
//      This routine allocates memory for the the Host Controller 
//      Communications Area (HCCA), aligned on a 256 byte boundary,
//      and updates the HcHcca operational register pointer, as
//      well as the corresponding PEI_OHCI_DEV.pFrameList
//      pointer.
//
// Input:    
//      IN PEI_OHCI_DEV *OhciDevPtr 
//                  --  This is a pointer to a PEI_OHCI_DEV structure
//                      for an OHCI controller.
//
// Output: 
//      EFI_STATUS (Return Value)
//                  = EFI_SUCCESS on successful completion
//                      or valid EFI error code
//
//---------------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS OhciInitHcca (
    IN PEI_OHCI_DEV *OhciDevPtr )
{
    OHCI_HC_REGISTERS   *OhciHcReg =
        (OHCI_HC_REGISTERS *) OhciDevPtr->UsbHostControllerBaseAddress;

    // Allocate 256 byte aligned Communication Channel area
    // to the PEI_OHCI_DEV.pFrameList pointer.
    ABORT_ON_ERROR( 
        (*OhciDevPtr->PeiServices)->AllocatePages(
            OhciDevPtr->PeiServices,
            EfiConventionalMemory,
            (UINTN) (256 / 0x1000) + 1,
            (EFI_PHYSICAL_ADDRESS *) &OhciDevPtr->pFrameList )
    );
        
    // Zero the memory and update the HcHCCA Host Controller
    // Operational Register.
    ZeroMem((VOID*)OhciDevPtr->pFrameList, sizeof(HC_HCCA));
    OhciHcReg->HcHcca = (HC_HCCA*) OhciDevPtr->pFrameList;
    
    return EFI_SUCCESS;
}


//<AMI_PHDR_START>
//---------------------------------------------------------------------------
//
// Procedure:   OhciInitHC
//
// Description: All leading whitespace on this line is removed by Helpbuilder
//      Description of this function can be block aligned in this section.
//      The first tab that Helpbuilder will recognize will be at tab stop 21,
//      which will indent 4 spaces in Helpbuilder.
//
//                  This text is indented 4 spaces in Helpbuilder
//
// Input:
//      IN EFI_PEI_SERVICES **PeiServices
//                  --  EFI_PEI_SERVICES pointer
//      IN PEI_OHCI_DEV *OhciDevPtr
//                  --  PEI_OHCI_DEV pointer
//      IN UINT8 Index
//                  --  Index of this controller in the global 
//                      PCI_BUS_DEV_FUNCTION array
//
// Output: 
//      VOID (Return Value)
//
//---------------------------------------------------------------------------
//<AMI_PHDR_END>

VOID OhciInitHC (
    IN EFI_PEI_SERVICES **PeiServices,
    IN PEI_OHCI_DEV     *OhciDevPtr,
    IN UINT8            Index )
{
    UINT8      bPortNum;
    UINT8      *pPtr;
    UINTN      MemPages;
    EFI_STATUS Status;
    EFI_PHYSICAL_ADDRESS TempPtr;
    EFI_PEI_PCI_CFG_PPI  *PciCfgPpi = OhciDevPtr->PciCfgPpi;
    POHCI_DESC_PTRS      pstOHCIDescPtrs = &(OhciDevPtr->stOHCIDescPtrs);
    OHCI_HC_REGISTERS    *OhciHcReg =
        (OHCI_HC_REGISTERS *) OhciDevPtr->UsbHostControllerBaseAddress;

    OhciDevPtr->wAsyncListSize = 0;  // not used
    OhciDevPtr->dMaxBulkDataSize = MAX_OHCI_BULK_DATA_SIZE;
    //OhciDevPtr->wEndp0MaxPacket = 0x40;
    //OhciDevPtr->bEndpointSpeed = USBSPEED_FULL;


    // Do a Host Controller reset first
    OhciHcReset( PeiServices, OhciDevPtr );


    //-----------------------------------------------------------------
    // Allocate and initialize the Host Controller Communication
    // area aligned on a 256 byte boundary.
    //
    // This is needed only to poll the HccaDoneHead register
    // in the HCCA, as the periodic list is not implemented.
    //-----------------------------------------------------------------

    // Store number of downstream ports into PEI_OHCI_DEV struct
    OhciDevPtr->bNumPorts =
        OhciHcReg->HcRhDescriptorA.Field.NumberDownstreamPorts;

    // Program root hub characteristics:
    OhciHcReg->HcRhDescriptorA.AllBits = 
        (NO_OVERCURRENT_PROTECTION |    // No over current protection
        POWERED_INDIVIDUALLY |          // Ports powered individually
        POWER_SWITCHED);                // Ports individually power switched
    OhciHcReg->HcRhDescriptorB.AllBits =
        (ALL_REMOVEABLE |               // All devices are removbale
        ALL_PER_PORT_POWER_SWITCHED);   // Power control is per-port
    
    OhciHcReg->HcRhStatus.Field.LocalPowerStatusChange = 
        SET_GLOBAL_POWER;               // Turn on power to all ports
        
    // Initialize the frame interval register
    OhciHcReg->HcFmInterval.Field.FrameInterval = 
        FM_INTERVAL_DEFAULT;            // Between Start of Frames (SOFs)
    OhciHcReg->HcFmInterval.Field.FsLargestDataPacket = 
        FS_LARGEST_PACKET_DEFAULT;      // Largest for single transaction

    // Enable the host controller list processing (Bulk/Control only)
    OhciHcReg->HcControl.Field.BulkListEnable = TRUE;
    OhciHcReg->HcControl.Field.ControlListEnable = TRUE;

    // Set the operational bit in the host controller so that power
    // can be applied to the ports.
    OhciHcReg->HcControl.Field.HostControllerFunctionalState = 
        SET_USB_OPERATIONAL;
        
    // Enable all the ports.
    for ( bPortNum = 0; bPortNum < OhciDevPtr->bNumPorts; bPortNum++ ) {
        OhciHcReg->HcRhPortStatus[bPortNum].AllBits = SET_PORT_POWER;
    }

    // Allocate a block of memory and define/initialize 
    // Setup Control and Bulk EDs/TDs
    pstOHCIDescPtrs = &(OhciDevPtr->stOHCIDescPtrs);

    MemPages = ( 3 *
                sizeof (OHCI_ED) ) + ( 5 * sizeof(OHCI_TD) ) / 0x1000 + 1;
    Status = (**PeiServices).AllocatePages(
        PeiServices,
        EfiConventionalMemory,
        MemPages,
        &TempPtr
             );

    pPtr = (UINT8 *) ( (UINTN) TempPtr );
    MemSet( pPtr, 3 * sizeof (OHCI_ED) + 5 * sizeof(OHCI_TD), 0 );
    if (!pPtr) {
        return;
    }
    pstOHCIDescPtrs->pstEDControl = (POHCI_ED) pPtr;
    pPtr += sizeof (OHCI_ED); //This should be okay
    pstOHCIDescPtrs->pstTDControlSetup = (POHCI_TD) pPtr;
    pPtr += sizeof (OHCI_TD);
    pstOHCIDescPtrs->pstTDControlData = (POHCI_TD) pPtr;
    pPtr += sizeof (OHCI_TD);
    pstOHCIDescPtrs->pstTDControlStatus = (POHCI_TD) pPtr;
    pPtr += sizeof (OHCI_TD);
    pstOHCIDescPtrs->pstEDBulk = (POHCI_ED) pPtr;
    pPtr += sizeof (OHCI_ED);
    pstOHCIDescPtrs->pstTDBulkData = (POHCI_TD) pPtr;
    pPtr += sizeof (OHCI_TD);
    pstOHCIDescPtrs->pstEDInterrupt = (POHCI_ED) pPtr;
    pPtr += sizeof (OHCI_ED);
    pstOHCIDescPtrs->pstTDInterruptData = (POHCI_TD) pPtr;

}


//<AMI_PHDR_START>
//---------------------------------------------------------------------------
//
// Procedure:   OhciHcReset
//
// Description: 
//      This function performs a software reset of the host controller.
//
// Input:
//      IN EFI_PEI_SERVICES **PeiServices
//                  --  EFI_PEI_SERVICES pointer
//      IN PEI_OHCI_DEV *OhciDevPtr
//                  --  PEI_OHCI_DEV pointer
//
// Output: 
//      VOID (Return Value)
//
// Notes:
//      It is assumed that all necessary operational register data has been 
//      saved prior to calling this function.
//
//---------------------------------------------------------------------------
//<AMI_PHDR_END>

VOID OhciHcReset (
    EFI_PEI_SERVICES **PeiServices,
    PEI_OHCI_DEV     *OhciDevPtr )
{
    OHCI_HC_REGISTERS   *OhciHcReg =
        (OHCI_HC_REGISTERS *) OhciDevPtr->UsbHostControllerBaseAddress;

    // Initiate a software reset 
    OhciHcReg->HcCommandStatus.AllBits = SET_CONTROLLER_RESET;

    //Wait for 2ms
    OHCI_FIXED_DELAY_MS( OhciDevPtr, 2);

    //Do USBRESET to reset roothub and downstream port
    OhciHcReg->HcControl.Field.HostControllerFunctionalState = SET_USB_RESET;

    //wait for 10ms
    OHCI_FIXED_DELAY_MS( OhciDevPtr, 10);

    // Note:    HcInterruptStatus.Field.RootHubStatusChange bit should 
    //          now be set if any devices are connected to a port
    //          on this controller. 
    
    return;
}


//<AMI_PHDR_START>
//---------------------------------------------------------------------------
//
// Procedure:   OhciHcGetRootHubPortStatus
//
// Description: 
//      This function obtains the port status and port change status for
//      a port specified by PortNumber and updates the EFI_USB_PORT_STATUS 
//      data structure as specified the the PortStatus pointer parameter.
//
// Input:
//      IN EFI_PEI_SERVICES **PeiServices
//                  --  EFI_PEI_SERVICES pointer
//      IN PEI_USB_HOST_CONTROLLER_PPI *This
//                  --  PEI_USB_HOST_CONTROLLER_PPI pointer
//      IN UINT8 PortNumber
//                  --  Port number for which status is requested
//      OUT EFI_USB_PORT_STATUS *PortStatus
//                  --  EFI_USB_PORT_STATUS pointer's data is updated
//
// Output: 
//      EFI_STATUS (Return Value)
//                  = EFI_SUCCESS on successful completion
//                      or valid EFI error code
//
//---------------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS OhciHcGetRootHubPortStatus (
    IN EFI_PEI_SERVICES            **PeiServices,
    IN PEI_USB_HOST_CONTROLLER_PPI *This,
    IN UINT8                       PortNumber,
    OUT EFI_USB_PORT_STATUS        *PortStatus )
{
    PEI_OHCI_DEV      *OhciDevPtr =
        PEI_RECOVERY_USB_OHCI_DEV_FROM_THIS( This );
    HC_RH_PORT_STATUS HcPortStatus;

    HcPortStatus = ( (OHCI_HC_REGISTERS *)
                    OhciDevPtr->UsbHostControllerBaseAddress )->
                       HcRhPortStatus[PortNumber - 1];

    PortStatus->PortStatus = 0;
    PortStatus->PortChangeStatus = 0;

    if (HcPortStatus.Field.CurrentConnectStatus) {
        PortStatus->PortStatus |= USB_PORT_STAT_CONNECTION;
    }
    if (HcPortStatus.Field.PortEnableStatus) {
        PortStatus->PortStatus |= USB_PORT_STAT_ENABLE;
    }
    if (HcPortStatus.Field.PortSuspendStatus) {
        PortStatus->PortStatus |= USB_PORT_STAT_SUSPEND;
    }
    if (HcPortStatus.Field.PortResetStatus) {
        PortStatus->PortStatus |= USB_PORT_STAT_RESET;
    }
    if (HcPortStatus.Field.LowSpeedDeviceAttached) {
        PortStatus->PortStatus |= USB_PORT_STAT_LOW_SPEED;
    }
    if (HcPortStatus.Field.ConnectStatusChange) {
        PortStatus->PortChangeStatus |= USB_PORT_STAT_C_CONNECTION;
    }
    if (HcPortStatus.Field.PortEnableStatusChange) {
        PortStatus->PortChangeStatus |= USB_PORT_STAT_C_ENABLE;
    }
    if (HcPortStatus.Field.CurrentConnectStatus) {
        PortStatus->PortChangeStatus |= USB_PORT_STAT_C_CONNECTION;
    }

    return EFI_SUCCESS;

}


//<AMI_PHDR_START>
//---------------------------------------------------------------------------
//
// Procedure:   OhciHcGetRootHubPortNumber
//
// Description: 
//      This function returns the number of downstream ports as specified 
//      in the HcRhDescriptorA operational register.
//
// Input:
//      IN EFI_PEI_SERVICES **PeiServices
//                  --  EFI_PEI_SERVICES pointer
//      IN PEI_USB_HOST_CONTROLLER_PPI *This
//                  --  PEI_USB_HOST_CONTROLLER_PPI pointer
//      OUT UINT8 *PortNumber
//                  --  Number of downstream ports
//
// Output: 
//      EFI_STATUS (Return Value)
//                  = EFI_SUCCESS on successful completion
//                      or valid EFI error code
//
//---------------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS OhciHcGetRootHubPortNumber (
    IN EFI_PEI_SERVICES            **PeiServices,
    IN PEI_USB_HOST_CONTROLLER_PPI *This,
    OUT UINT8                      *PortNumber )
{

    PEI_OHCI_DEV        *OhciDevPtr = PEI_RECOVERY_USB_OHCI_DEV_FROM_THIS( This );
    OHCI_HC_REGISTERS   *OhciHcReg =
        (OHCI_HC_REGISTERS *) OhciDevPtr->UsbHostControllerBaseAddress;
        
    if (PortNumber == NULL) {
        return EFI_INVALID_PARAMETER;
    }
    
    *PortNumber = OhciHcReg->HcRhDescriptorA.Field.NumberDownstreamPorts;

    return EFI_SUCCESS;
}


//<AMI_PHDR_START>
//---------------------------------------------------------------------------
//
// Procedure:   OhciHcSetRootHubPortFeature
//
// Description: 
//      This function sets an OHCI specification port feature as specified by
//      PortFeature for the port specified by PortNumber.
//
// Input:
//      IN EFI_PEI_SERVICES **PeiServices
//                  --  EFI_PEI_SERVICES pointer
//      IN PEI_USB_HOST_CONTROLLER_PPI *This
//                  --  PEI_USB_HOST_CONTROLLER_PPI pointer
//      IN UINT8 PortNumber
//                  --  Port number whose feature is to be set
//      IN EFI_USB_PORT_FEATURE PortFeature
//                  --  Feature to set
//
// Output: 
//      EFI_STATUS (Return Value)
//                  = EFI_SUCCESS on successful completion
//                      or valid EFI error code
//
//---------------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS OhciHcSetRootHubPortFeature (
    IN EFI_PEI_SERVICES            **PeiServices,
    IN PEI_USB_HOST_CONTROLLER_PPI *This,
    IN UINT8                       PortNumber,
    IN EFI_USB_PORT_FEATURE        PortFeature )
{
    PEI_OHCI_DEV        *OhciDevPtr = 
        PEI_RECOVERY_USB_OHCI_DEV_FROM_THIS( This );
    OHCI_HC_REGISTERS    *OhciHcReg =
        (OHCI_HC_REGISTERS *) OhciDevPtr->UsbHostControllerBaseAddress;

    if (PortNumber > OhciHcReg->HcRhDescriptorA.Field.NumberDownstreamPorts){
        return EFI_INVALID_PARAMETER;
    }

    switch (PortFeature)
    {

    case EfiUsbPortSuspend:
        OhciHcReg->HcRhPortStatus[PortNumber - 1].AllBits = SET_PORT_SUSPEND;
        break;

    case EfiUsbPortReset:
        OhciHcReg->HcRhPortStatus[PortNumber - 1].AllBits = SET_PORT_RESET;
        break;

    case EfiUsbPortPower:
        break;

    case EfiUsbPortEnable:
        OhciHcReg->HcRhPortStatus[PortNumber - 1].AllBits = SET_PORT_ENABLE;
        break;

    default:
        return EFI_INVALID_PARAMETER;
    }

    return EFI_SUCCESS;
}


//<AMI_PHDR_START>
//---------------------------------------------------------------------------
//
// Procedure:   OhciHcClearRootHubPortFeature
//
// Description: 
//      This function clears an OHCI specification port feature as specified
//      by PortFeature for the port specified by PortNumber.
//
// Input:
//      IN EFI_PEI_SERVICES **PeiServices
//                  --  EFI_PEI_SERVICES pointer
//      IN PEI_USB_HOST_CONTROLLER_PPI *This
//                  --  PEI_USB_HOST_CONTROLLER_PPI pointer
//      IN UINT8 PortNumber
//                  --  Port number whose feature is to be set
//      IN EFI_USB_PORT_FEATURE PortFeature
//                  --  Feature to set
//
// Output: 
//      EFI_STATUS (Return Value)
//                  = EFI_SUCCESS on successful completion
//                      or valid EFI error code
//
//---------------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS OhciHcClearRootHubPortFeature (
    IN EFI_PEI_SERVICES            **PeiServices,
    IN PEI_USB_HOST_CONTROLLER_PPI *This,
    IN UINT8                       PortNumber,
    IN EFI_USB_PORT_FEATURE        PortFeature )
{
    PEI_OHCI_DEV        *OhciDevPtr = 
        PEI_RECOVERY_USB_OHCI_DEV_FROM_THIS( This );
    OHCI_HC_REGISTERS   *OhciHcReg =
        (OHCI_HC_REGISTERS *) OhciDevPtr->UsbHostControllerBaseAddress;
    HC_RH_PORT_STATUS   *Pstatus;

    if (PortNumber > OhciHcReg->HcRhDescriptorA.Field.NumberDownstreamPorts){
        return EFI_INVALID_PARAMETER;
    }

    Pstatus = &OhciHcReg->HcRhPortStatus[PortNumber - 1];
    
    switch (PortFeature)
    {
        // clear PORT_ENABLE feature means disable port.
        // This is accomplished by writing a 1 to the CurrentConnectStatus
        // field.
    case EfiUsbPortEnable:
        Pstatus->AllBits = CLEAR_PORT_ENABLE;
        break;

        // clear PORT_SUSPEND feature means resume the port.
        // (cause a resume on the specified port if in suspend mode)
        // This is accomplished by writing a 1 to the PortOverCurrentIndicator
        // field.     
    case EfiUsbPortSuspend:
        Pstatus->AllBits = CLEAR_SUSPEND_STATUS;
        break;

    case EfiUsbPortPower:
        break;


        // clear PORT_RESET means clear the reset signal.
        // This is accomplished by writing a 1 to the PortResetStatusChange
        // field.  No assumption is made that the appropriate delay
        // was implemented.
    case EfiUsbPortReset:

        break;

        // clear connect status change by writing
        // a 1 to the ConnectStatusChange field
    case EfiUsbPortConnectChange:
        Pstatus->AllBits = CLEAR_CONNECT_STATUS_CHANGE;
        break;

        // clear enable/disable status change by writing
        // a 1 to the PortEnableStatusChange field
    case EfiUsbPortEnableChange:
        Pstatus->AllBits = CLEAR_PORT_ENABLE_STATUS_CHANGE;
        break;

        // root hub does not support these requests
    case EfiUsbPortSuspendChange:
    case EfiUsbPortOverCurrentChange:
    case EfiUsbPortResetChange:
        Pstatus->AllBits = CLEAR_PORT_RESET_STATUS_CHANGE;
        break;

    default:
        return EFI_INVALID_PARAMETER;
    }

    return EFI_SUCCESS;
}

//<AMI_PHDR_START>
//---------------------------------------------------------------------------
//
// Procedure:   OhciHcControlTransfer
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

typedef struct _D_REQUEST
{
    UINT8  RequestType;
    UINT8  Request;
    UINT16 Value;
    UINT16 Index;
    UINT16 Length;
} D_REQUEST;

EFI_STATUS OhciHcControlTransfer (
    IN EFI_PEI_SERVICES            **PeiServices,
    IN PEI_USB_HOST_CONTROLLER_PPI *This,
    IN UINT8                       bDeviceAddress,
    IN UINT8                       DeviceSpeed,
    IN UINT8                       MaximumPacketLength,
    IN UINT16                      TransactionTranslator    OPTIONAL,
    IN EFI_USB_DEVICE_REQUEST      *Request,
    IN EFI_USB_DATA_DIRECTION      TransferDirection,
    IN OUT VOID *DataBuffer        OPTIONAL,
    IN OUT UINTN *DataLength       OPTIONAL,
    IN UINTN                       TimeOut,
    OUT UINT32                     *TransferResult )
{
    UINT16            *fpData;
    POHCI_ED          fpED;
    POHCI_TD          fpTD;
    UINT32            DwordData;
    UINT16            WordData;
    UINT16            WordRequest;
    UINT16            WordIndex;
    UINT16            WordValue;
    EFI_STATUS        Status = EFI_SUCCESS;
    PEI_OHCI_DEV      *OhciDevPtr =
        PEI_RECOVERY_USB_OHCI_DEV_FROM_THIS( This );
    POHCI_DESC_PTRS   fpDescPtrs =
        &(OhciDevPtr->stOHCIDescPtrs);
    OHCI_HC_REGISTERS *HcReg =
        (OHCI_HC_REGISTERS *) OhciDevPtr->UsbHostControllerBaseAddress;

    // 5 ms delay is necessary for OHCI host controllers
    OHCI_FIXED_DELAY_MS( OhciDevPtr, 5 );

    WordRequest = (Request->Request << 8) | Request->RequestType;
    WordValue = Request->Value;
    WordIndex = Request->Index;

    //
    // Build the device request in the data area of the control setup qTD
    //
    fpData = (UINT16 *) fpDescPtrs->pstTDControlSetup->aSetupData;
    *fpData++ = WordRequest;
    *fpData++ = WordValue;
    *fpData++ = WordIndex;
    *fpData++ = (UINT16) *DataLength;
    *(UINT32 *) fpData = (UINT32) DataBuffer;

    //
    // Prepare some registers that will be used in building the TDs below.
    // wLength  contains the data length.
    // fpBuffer contains the absolute address of the data buffer.
    // WordRequest contains the request type (bit 7 = 0/1 for Out/In).
    // fpDevInfo will contain a pointer to the DeviceInfo structure for
    // the given device.
    //
    // Ready the EDControl for the control transfer.
    //
    fpED = fpDescPtrs->pstEDControl;
    //
    // The ED control field will be set so
    //   Function address & Endpoint number = ESI,
    //   Direction = From TD,
    //   Speed = DeviceInfo.bEndpointSpeed,
    //   Skip = 1, Format = 0,
    //   Max packet size  = DeviceInfo.wEndp0MaxPacket
    // The HeadPointer field will be set to TDControlSetup
    // The TailPointer field will be set to OHCI_TERMINATE
    // The LinkPointer field will be set to OHCI_TERMINATE
    //

    // if wEndp0MaxPacket is NULL, then use default
    // packet size
    DwordData = MaximumPacketLength;

    // Force the max packet size to 64 bytes
    if (DwordData > 0x40 || DwordData == 0) {
        DwordData = 0x40;
    }
    DwordData <<= 16;                                       // DwordData[26:16] = device's packet size
    WordData = (UINT16) DeviceSpeed;       					// 00/01/10 for HI/LO/FULL
    WordData = (WordData & 1) << 13;                          // WordData[13] = full/low speed flag
    WordData |= bDeviceAddress | ED_SKIP_TDQ;
    fpED->dControl = DwordData | WordData;
    fpED->fpTailPointer = 0;
    fpED->fpEDLinkPointer = 0;

    fpTD = fpDescPtrs->pstTDControlSetup;
    //
    // The ControlStatus field will be set so
    //   Buffer Rounding = 1,
    //   Direction PID = GTD_SETUP_PACKET,
    //   Delay Interrupt = GTD_INTD,
    //   Data Toggle = GTD_SETUP_TOGGLE,
    //   Error Count = GTD_NO_ERRORS,
    //   Condition Code = GTD_NOT_ACCESSED
    // The CurrentBufferPointer field will point to the TD's SetupData buffer
    //   which was before initialized to contain a DeviceRequest struc.
    // The BufferEnd field will point to the last byte of the TD's SetupData
    //   buffer.
    // The LinkPointer field will point to the TDControlData if data will
    //   be sent/received or to the TDControlStatus if no data is expected.
    // The CSReloadValue field will contain 0 because this is a "one shot"
    //   packet.
    // The pCallback will be set to point to the OHCI_ControlTDCallback
    //   routine.
    // The ActiveFlag field will be set to TRUE.
    // The DeviceAddress field does not need to be set since the Control TDs
    //  do not need rebinding to the EDControl.
    //
    fpTD->dControlStatus = (UINT32) ( GTD_BUFFER_ROUNDING |
                                     GTD_SETUP_PACKET | GTD_SETUP_TOGGLE |
                                     GTD_NO_ERRORS | (GTD_NOT_ACCESSED << 28) );

    fpTD->fpCurrentBufferPointer = fpTD->aSetupData;
    fpTD->fpBufferEnd = fpTD->aSetupData + 7; // size of aSetupData - 1

    if (*DataLength) {  // some data to transfer

        // Fill in various fields in the TDControlData.
        fpTD = fpDescPtrs->pstTDControlData;
        //
        // The ControlStatus field will be set so
        //   Buffer Rounding = 1,
        //   Direction PID = GTD_OUT_PACKET/GTD_IN_PACKET,
        //   Delay Interrupt = GTD_INTD,
        //   Data Toggle = GTD_DATA1_TOGGLE,
        //   Error Count = GTD_NO_ERRORS,
        //   Condition Code = GTD_NOT_ACCESSED
        // The CurrentBufferPointer field will point to the caller's buffer
        //   which is now in EBP.
        // The BufferEnd field will point to the last byte of the caller's
        //   buffer.
        // The LinkPointer field will point to the TDControlStatus.
        // The CSReloadValue field will contain 0 because this is a
        //   "one shot" packet.
        // The pCallback will be set to point to the OHCI_ControlTDCallback
        //   routine.
        // The ActiveFlag field will be set to TRUE.
        // The DeviceAddress field does not need to be set since the Control
        //   TDs do not need rebinding to the EDControl.
        // The CSReloadValue field will contain 0 because this is a
        //   "one shot" packet.
        // The pCallback will be set to point to the OHCI_ControlTDCallback
        //   routine.
        // The ActiveFlag field will be set to TRUE.    return  USB_SUCCESS;
        // The DeviceAddress field does not need to be set since the Control
        //   TDs do not need rebinding to the EDControl.
        //
        DwordData = (UINT32) ( GTD_BUFFER_ROUNDING | GTD_DATA1_TOGGLE
                          | GTD_NO_ERRORS | (GTD_NOT_ACCESSED << 28) );
        DwordData = (WordRequest & BIT7)
                ? (DwordData | GTD_IN_PACKET | GTD_INTD)
                : (DwordData | GTD_OUT_PACKET);
        fpTD->dControlStatus = DwordData;
        fpTD->fpCurrentBufferPointer = (UINT8 *) DataBuffer;

        WordData = (*DataLength < MAX_CONTROL_DATA_SIZE)
                ? *DataLength
                : MAX_CONTROL_DATA_SIZE;
        fpTD->fpBufferEnd = (UINT8 *) DataBuffer + WordData - 1;
    }

    // Fill in various fields in the TDControlStatus.
    fpTD = fpDescPtrs->pstTDControlStatus;
    //
    // The ControlStaus field will be set so
    //   Buffer Rounding = 1,
    //   Direction PID = GTD_OUT_PACKET/GTD_IN_PACKET,
    //   Delay Interrupt = GTD_INTD,
    //   Data Toggle = GTD_DATA1_TOGGLE,
    //   Error Count = GTD_NO_ERRORS,
    //   Condition Code = GTD_NOT_ACCESSED
    // The CurrentBufferPointer field will point to NULL
    // The BufferEnd field will point to NULL.
    // The LinkPointer field will point to OHCI_TERMINATE.
    // The CSReloadValue field will contain 0 because this is a
    //   "one shot" packet.
    // The pCallback will be set to point to the OHCI_ControlTdCallback
    //   routine.
    // The ActiveFlag field will be set to TRUE.
    // The DeviceAddress field does not need to be set since the Control
    //   TDs do not need rebinding to the EdControl.
    //
    // Note: For OUT control transfer status should be IN and
    //       for IN cotrol transfer, status should be OUT.
    //
    DwordData = (UINT32) ( GTD_BUFFER_ROUNDING | GTD_DATA1_TOGGLE
                      | GTD_NO_ERRORS | (GTD_NOT_ACCESSED << 28) );
    DwordData = (WordRequest & BIT7)
            ? (DwordData | GTD_OUT_PACKET)
            : (DwordData | GTD_IN_PACKET | GTD_INTD);
    fpTD->dControlStatus = DwordData;
    fpTD->fpCurrentBufferPointer = NULL;
    fpTD->fpBufferEnd = NULL;
    fpTD->fpLinkPointer = NULL;

    //
    // Link all the pointers together
    //
    fpTD = fpDescPtrs->pstTDControlSetup;
    fpED->fpHeadPointer = fpTD;
    if (*DataLength) {  // chain in data TD
        fpTD->fpLinkPointer = (UINT8 *) fpDescPtrs->pstTDControlData;
        fpTD = fpDescPtrs->pstTDControlData;
    }
    fpTD->fpLinkPointer = (UINT8 *) fpDescPtrs->pstTDControlStatus;

    fpDescPtrs->pstTDControlStatus->fpLinkPointer = NULL;

    fpTD = fpDescPtrs->pstTDControlSetup;
    do {
        fpTD->dCSReloadValue = 0;
        fpTD->bActiveFlag = TRUE;
        fpTD = (POHCI_TD) fpTD->fpLinkPointer;
    } while (fpTD);

    // clear the WriteBackDoneHead status bit in
    // the HcInterruptStatus register
    HcReg->HcInterruptStatus.Field.WriteBackDoneHead = HCINT_STATUS_CLEAR;

    //
    // Now control queue is complete, so set ED_SKIP_TDQ=0
    //
    fpED->dControl &= ~ED_SKIP_TDQ;
    //
    // Set the HcControlHeadED register to point to the EDControl.
    //
    HcReg->HcControlHeadEd = (UINTN) fpED;

    //
    // Now put the control setup, data and status into the HC's schedule by
    // setting the ControllListFilled field of HcCommandStatus reg.
    // This will cause the HC to execute the transaction in the next
    // active frame.
    //
    HcReg->HcCommandStatus.AllBits = SET_CONTROL_LIST_FILLED;

    //
    // Now wait for the control status TD to complete.  When it has completed,
    // the OHCI_ControlTDCallback will set its active flag to FALSE.
    Status = OhciHcWaitForTransferComplete( PeiServices, OhciDevPtr,
        fpDescPtrs->pstTDControlStatus );

    //
    // Stop the HC from processing the EDControl by setting its Skip bit.
    //
    fpED->dControl |= ED_SKIP_TDQ;

    //
    // Finally check for any error bits set in both the TDControlStatus.
    // If the TD did not complete successfully, return STC.
    //

    // DwordData[3:0] = Completion status
    DwordData = fpDescPtrs->pstTDControlStatus->dControlStatus >> 28;

    return ( (UINT8) DwordData == 0 ) ? EFI_SUCCESS : EFI_DEVICE_ERROR;
    //TODO: CHange the return status more meaningfull
}


//<AMI_PHDR_START>
//---------------------------------------------------------------------------
//
// Procedure:   OhciHcBulkTransfer
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

EFI_STATUS OhciHcBulkTransfer (
    IN EFI_PEI_SERVICES            **PeiServices,
    IN PEI_USB_HOST_CONTROLLER_PPI *This,
    IN UINT8                       DeviceAddress,
    IN UINT8                       EndPointAddress,
    IN UINT8                       DeviceSpeed,
    IN UINT16                      MaximumPacketLength,
    IN UINT16                      TransactionTranslator    OPTIONAL,
    IN OUT VOID                    *DataBuffer,
    IN OUT UINTN                   *DataLength,
    IN OUT UINT8                   *DataToggle,
    IN UINTN                       TimeOut,
    OUT UINT32                     *TransferResult )
{
    UINT32          DwordData;
    UINT8           ByteData;
    UINT16          wMaxPkt;
    EFI_STATUS      Status;
    UINT8           bEndp;
    UINT8           Toggle;
    PEI_OHCI_DEV        *OhciDevPtr = 
        PEI_RECOVERY_USB_OHCI_DEV_FROM_THIS( This );
    POHCI_DESC_PTRS     fpDescPtrs = &(OhciDevPtr->stOHCIDescPtrs);
    OHCI_HC_REGISTERS   *HcReg =
        (OHCI_HC_REGISTERS *) OhciDevPtr->UsbHostControllerBaseAddress;

    wMaxPkt = MaximumPacketLength;

    if (wMaxPkt == 0) {
        *DataLength = 0;
        return EFI_NOT_FOUND;
    }

    //Clear Bulk ED and TD
    MemSet( fpDescPtrs->pstEDBulk, sizeof(OHCI_ED), 0 );
    MemSet( fpDescPtrs->pstTDBulkData, sizeof(OHCI_TD), 0 );
    //
    //  Set the SKIP bit in the EdBulk to avoid accidental scheduling
    //
    fpDescPtrs->pstEDBulk->dControl = ED_SKIP_TDQ;
    //
    // Set the ED's head pointer field to bulk data TD and tail pointer
    // field to OHCI_TERMINATE. Also set ED's link pointer to
    // OHCI_TERMINATE.
    //
    fpDescPtrs->pstEDBulk->fpHeadPointer = fpDescPtrs->pstTDBulkData;
    fpDescPtrs->pstEDBulk->fpTailPointer = OHCI_TERMINATE;
    fpDescPtrs->pstEDBulk->fpEDLinkPointer = OHCI_TERMINATE;
    //
    // Form the data needed for ED's control field with the available
    // information
    //
    bEndp = EndPointAddress & 0x7f;
    DwordData = (EndPointAddress & 0x80) ? ED_IN_PACKET : ED_OUT_PACKET;
    DwordData |= DeviceAddress;
    DwordData |= (UINT16) bEndp << 7;
    DwordData |= (UINT32) wMaxPkt << 16;

    //
    // Update the ED's control field with the data formed
    // ASSUME ALL MASS DEVICES ARE FULL SPEED DEVICES.
    //
    fpDescPtrs->pstEDBulk->dControl = DwordData;
    //
    // Fill the general bulk data TD with relevant information.  Set the
    // TD's control field with buffer rounding set to 1, direction PID to
    // don't care, delay interrupt to INTD, data toggle to the latest data
    // toggle value, error count to no errors and condition code to not
    // accessed.
    //
    // Set the data toggle to DATA0 (SETUP_TOGGLE)
    fpDescPtrs->pstTDBulkData->dControlStatus = (UINT32) (
        GTD_BUFFER_ROUNDING |
        GTD_IN_PACKET |
        GTD_INTD |
        GTD_SETUP_TOGGLE |
        GTD_NO_ERRORS |
        (GTD_NOT_ACCESSED << 28)
                                                );
    fpDescPtrs->pstTDBulkData->dControlStatus |= (UINT32) *DataToggle << 24;

    //
    // GTD current buffer pointer field will point to the caller's buffer which
    // now in the variable fpBuffer
    //
    fpDescPtrs->pstTDBulkData->fpCurrentBufferPointer = (UINT8 *) DataBuffer;
    fpDescPtrs->pstTDBulkData->fpBufferEnd = (UINT8 *) DataBuffer +
                                             *DataLength - 1;
    fpDescPtrs->pstTDBulkData->fpLinkPointer = OHCI_TERMINATE;
    //
    // GTD's CSReloadValue field will contain 0 because this is a
    // "one shot" packet
    //
    fpDescPtrs->pstTDBulkData->dCSReloadValue = 0;
    fpDescPtrs->pstTDBulkData->bActiveFlag = TRUE;

    // Set the HCBulkHeadED register to point to the bulk ED
    fpDescPtrs->pstEDBulk->dControl &= ~ED_SKIP_TDQ;
    HcReg->HcBulkHeadEd = (UINT32) fpDescPtrs->pstEDBulk;
    
    // Enable the bulk list processing
    HcReg->HcCommandStatus.AllBits = SET_BULK_LIST_FILLED;

    Status = OhciHcWaitForTransferComplete( PeiServices, OhciDevPtr,
        fpDescPtrs->pstTDBulkData );
    //
    // Stop the HC from processing the EDBulk by setting its Skip bit.
    //
    fpDescPtrs->pstEDBulk->dControl |= ED_SKIP_TDQ;
    //
    // Update the data toggle value into the mass info structure
    //

    *DataToggle = (UINT8) ( ( (fpDescPtrs->pstTDBulkData->dControlStatus &
                               GTD_DATA_TOGGLE) >> 24 ) & 1 );
    Toggle = (UINT8) ( (fpDescPtrs->pstTDBulkData->dControlStatus &
                        GTD_DATA_TOGGLE) >> 24 );
    if ( (Toggle & 0x02) == 0 )
    {
        //Use the Carry
        DwordData = (UINT32) fpDescPtrs->pstEDBulk->fpHeadPointer;
        DwordData &= 0x00000002;
        DwordData = DwordData >> 1;
        DwordData &= 0x00000001;
        *DataToggle = DwordData;
    }
    //
    // Check for the error conditions - if possible recover from them
    //
    ByteData = (UINT8) (fpDescPtrs->pstTDBulkData->dControlStatus >> 28);
    if (ByteData) {
        if (ByteData == GTD_DEVICE_NOT_RESPOND) {
            //TODO          fpUSBData->bLastCommandStatus |= USB_BULK_TIMEDOUT;
            *DataLength = 0;
            return EFI_NOT_FOUND;
        }
        if (ByteData == GTD_STALL) {
            //TODO          fpUSBData->bLastCommandStatus |= USB_BULK_STALLED;
            *DataLength = 0;
            return EFI_NOT_FOUND;
        }
    }
    //
    // Get the size of data transferred
    //
    // Size transferred is calculated by subtracting end address with current
    // buffer pointer and subtracting that value from the total size
    //
    if (!fpDescPtrs->pstTDBulkData->fpCurrentBufferPointer)
    {
        //All data are transfered.
        return EFI_SUCCESS;
    }
    DwordData = (UINT32) fpDescPtrs->pstTDBulkData->fpBufferEnd;
    DwordData = DwordData -
            (UINT32) fpDescPtrs->pstTDBulkData->fpCurrentBufferPointer;
    if (DwordData != 0)
    {
        *DataLength = *DataLength - DwordData - 1;
    }
    else {
        ;
    }
    return Status;

}


//<AMI_PHDR_START>
//---------------------------------------------------------------------------
//
// Procedure:   OhciHcWaitForTransferComplete
//
// Description: 
//      This function waits for a tranfer to complete by polling the 
//      HcInterruptStatus register's WritebackDoneHead field.
//      
// Input:
//      IN PEI_OHCI_DEV *OhciDevPtr
//                  --  PEI_OHCI_DEV pointer
//      IN POHCI_TD Td
//                  --  Not used
//
// Output: 
//      EFI_STATUS (Return Value)
//                  = EFI_SUCCESS on successful completion
//                      or valid EFI error code
//
//---------------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS OhciHcWaitForTransferComplete (
	IN EFI_PEI_SERVICES	**PeiServices,
    IN PEI_OHCI_DEV *OhciDevPtr,
    IN POHCI_TD     Td )
{
    UINT32              Count;
    OHCI_HC_REGISTERS   *HcReg =
        (OHCI_HC_REGISTERS *) OhciDevPtr->UsbHostControllerBaseAddress;
    HC_INTERRUPT_STATUS *HcIntStatus = &HcReg->HcInterruptStatus;
	UINT32				DoneHead = 0;

    // Poll (up to 4 seconds) or until the
    // WriteBackDoneHead status bit is set in
    // the HcInterruptStatus operational register.

    // if the WriteBackDoneHead is set, then clear 
    // HccaDoneHead in the HCCA and WriteBackDoneHead
    // and then return EFI_SUCCESS to continue execution.

    for (Count = 0; Count < 1000; Count++) {
        if (HcIntStatus->Field.WriteBackDoneHead == HCINT_WB_DONE ) {
			DoneHead = HcReg->HcHcca->HccaDoneHead;
			HcReg->HcHcca->HccaDoneHead = 0;
            HcIntStatus->Field.WriteBackDoneHead = HCINT_STATUS_CLEAR;
			if (DoneHead == (UINT32)Td) {
            	return EFI_SUCCESS;
			}
        }
        OHCI_FIXED_DELAY_MS( OhciDevPtr, 4 ); // 4 ms

    }
	
	PEI_TRACE ((EFI_D_ERROR, PeiServices, "OHCI Time-Out:\n"));
    return EFI_NOT_FOUND;

}


//**********************************************************************
//**********************************************************************
//**                                                                  **
//**        (C)Copyright 1985-2006, American Megatrends, Inc.         **
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