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
// $Header: /Alaska/SOURCE/Modules/USBRecovery/UhciPeiUsb.c 10    10/23/08 1:59p Michaela $
//
// $Revision: 10 $
//
// $Date: 10/23/08 1:59p $
//
//**********************************************************************
// Revision History
// ----------------
// $Log: /Alaska/SOURCE/Modules/USBRecovery/UhciPeiUsb.c $
// 
// 10    10/23/08 1:59p Michaela
// Removed UsbDebug.h include
// 
// 9     10/21/08 5:56p Michaela
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
// 8     7/10/08 6:34p Michaela
// Updated to support OHCI controllers
//
// 7     10/23/07 5:56p Ambikas
//
// 6     10/23/07 5:39p Ambikas
//
// 5     8/17/07 4:05p Ambikas
//
// 4     9/22/06 4:03p Sivagarn
// - Included appropriate headers for flies and functions
// - Updated copyright messages
//
//
//**********************************************************************

//<AMI_FHDR_START>
//----------------------------------------------------------------------------
//
// Name:        UhciPeiUsb.C
//
// Description: This file is the main source file for the UHCI PEI USB
//              recovery module
//
//----------------------------------------------------------------------------
//<AMI_FHDR_END>

#include <PEI.h>
#include <AmiPeiLib.h>
#include <PPI/PeiGetUCtrl.h>
#include <token.h>


//----------------------------------------------------------------------------
// Global Constants
//----------------------------------------------------------------------------

#define PCI_REG_UHCI_COMMAND_REGISTER         0x04
#define PCI_REG_UHCI_BASE_ADDRESS_REGISTER    0x20
#define PCI_REG_UHCI_LEGACY_CONTROL_REGISTER  0xc0
#define PCI_REG_UHCI_RESUME_ENABLE_REGISTER   0xc4

#define PEI_UHCI_CONTROLLER                   0x01

#define PCI_REG_EHCI_MEMORY_BAR               0x10

#define EHCI_HC_OPERATIONAL_CONFIG_FLAG_REG     0x40

UINTN gUhciPciReg[] = PEI_UHCI_PCI_DEVICES;
#define MAX_USB_CTRLERS  sizeof(gUhciPciReg) / sizeof(UINTN)


//----------------------------------------------------------------------------
// Type definitions
//----------------------------------------------------------------------------

typedef struct
{
    //  UINTN                   Signature;
    //  PEI_USB_CONTROLLER_PPI  UsbControllerPpi;
    //  EFI_PEI_PPI_DESCRIPTOR      PpiList;
    //  PEI_PCI_CFG_PPI         *PciCfgPpi;
    //  UINTN                   TotalUsbControllers;
    UINTN IoBase[MAX_USB_CTRLERS];
} PCI_UHCI_DEVICE;

//----------------------------------------------------------------------------
// Function Prototypes
//----------------------------------------------------------------------------

EFI_STATUS GetUhciController (
    IN EFI_PEI_SERVICES           **PeiServices,
    IN EFI_PEI_USB_CONTROLLER_PPI *This,
    IN UINT8                      UsbControllerId,
    IN UINTN                      *ControllerType,
    IN UINTN                      *IoBaseAddress );

EFI_STATUS
EnableUhciController (
    IN EFI_PEI_SERVICES    **PeiServices,
    IN EFI_PEI_PCI_CFG_PPI *PciCfgPpi,
    IN UINTN               BaseAddress,
    IN UINT8               UsbControllerId );

VOID
ClearEhciConfigFlagReg (
    IN EFI_PEI_SERVICES    **PeiServices,
    IN EFI_PEI_PCI_CFG_PPI *PciCfgPpi );

//----------------------------------------------------------------------------
// Global Variables
//----------------------------------------------------------------------------

#ifdef PEI_EHCI_MEM_BASE_ADDRESSES
UINTN  mEhciPciBDFs[USB_EHCI] = PEI_EHCI_PCI_BDFS;
UINT32 mEhciMemBaseAddresses[USB_EHCI] = PEI_EHCI_MEM_BASE_ADDRESSES;
#endif

static EFI_GUID guidGetUhciController = EFI_PEI_GET_UHCI_CTRLER_GUID;
PCI_UHCI_DEVICE gPeiUhciDev;
EFI_PEI_USB_CONTROLLER_PPI GetUhciControllerPpi = {
    GetUhciController
};

// PPI to be installed
static
EFI_PEI_PPI_DESCRIPTOR PpiList[] = {
    {EFI_PEI_PPI_DESCRIPTOR_PPI | EFI_PEI_PPI_DESCRIPTOR_TERMINATE_LIST,
     &guidGetUhciController, &GetUhciControllerPpi}
};

//----------------------------------------------------------------------------
// Function Definitions
//----------------------------------------------------------------------------


//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   UhciPeiUsbEntryPoint
//
// Description: This function is the entry point for this PEI. This function
//              initializes the UHCI Controller
//
// Input:       FfsHeader   Pointer to the FFS file header
//              PeiServices Pointer to the PEI services table
//
// Output:      Return Status based on errors that occurred while waiting for
//              time to expire.
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS UhciPeiUsbEntryPoint (
    IN EFI_FFS_FILE_HEADER *FfsHeader,
    IN EFI_PEI_SERVICES    **PeiServices )
{

    UINTN      i;
    EFI_STATUS Status;
    EFI_PEI_PCI_CFG_PPI *PciCfgPpi;

    // Set PCI Config pointer
    PciCfgPpi = (*PeiServices)->PciCfg;

  #ifdef PEI_EHCI_MEM_BASE_ADDRESSES
    ClearEhciConfigFlagReg( PeiServices, PciCfgPpi );
  #endif

    // Assign resources and enable UHCI controllers
    for (i = 0; i < MAX_USB_CTRLERS; i++) {
        // PEI_UHCI_IOBASE = 0x4000
        gPeiUhciDev.IoBase[i] = PEI_UHCI_IOBASE + 0x40 * i;
        Status = EnableUhciController( PeiServices, PciCfgPpi,
            gPeiUhciDev.IoBase[i], (UINT8) i );
    }

    // Install USB Controller PPI
    return (*PeiServices)->InstallPpi( PeiServices, PpiList );
}


//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   EnableUhciController
//
// Description: This function enables the UHCI controller
//
// Input:       **PeiServices       Pointer to the PEI services table
//              *PciCfgPpi          Pointer to the PCI Configuration PPI
//              BaseAddress         I/O base Address to be programmed for the
//                                  UHCI controller
//              UsbControllerId     USB Controller ID
//
// Output:      EFI_STATUS
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS EnableUhciController (
    IN EFI_PEI_SERVICES    **PeiServices,
    IN EFI_PEI_PCI_CFG_PPI *PciCfgPpi,
    IN UINTN               BaseAddress,
    IN UINT8               UsbControllerId )
{
    UINT16 CmdReg;


    // Validate USB Controller ID
    if (UsbControllerId >= MAX_USB_CTRLERS) {
        return EFI_INVALID_PARAMETER;
    }

    // Assign base address register
    PciCfgPpi->Write( PeiServices, PciCfgPpi, EfiPeiPciCfgWidthUint32,
        gUhciPciReg[UsbControllerId] |
        PCI_REG_UHCI_BASE_ADDRESS_REGISTER, &BaseAddress );

    // Enable UHCI PCI Command register
    PciCfgPpi->Read( PeiServices, PciCfgPpi, EfiPeiPciCfgWidthUint16,
        gUhciPciReg[UsbControllerId] |
        PCI_REG_UHCI_COMMAND_REGISTER, &CmdReg );

    CmdReg = (UINT16) (CmdReg | 0x05);

    PciCfgPpi->Write( PeiServices, PciCfgPpi, EfiPeiPciCfgWidthUint16,
        gUhciPciReg[UsbControllerId] |
        PCI_REG_UHCI_COMMAND_REGISTER, &CmdReg );

    return EFI_SUCCESS;
}


//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   ClearEhciConfigFlagReg
//
// Description:
//
// Input:       **PeiServices       Pointer to the PEI services table
//              *PciCfgPpi          Pointer to the PCI Configuration PPI
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
#ifdef PEI_EHCI_MEM_BASE_ADDRESSES
VOID ClearEhciConfigFlagReg (
    IN EFI_PEI_SERVICES    **PeiServices,
    IN EFI_PEI_PCI_CFG_PPI *PciCfgPpi )
{
    UINT32 i;
    UINT16 CmdReg;
    UINT32  ConfigureFlagAddress;
    

    for (i = 0; i < USB_EHCI; i++) {
        // Assign Memory Base Address
        PciCfgPpi->Write( PeiServices, PciCfgPpi, EfiPeiPciCfgWidthUint32,
            mEhciPciBDFs[i] |
            PCI_REG_EHCI_MEMORY_BAR,
            &mEhciMemBaseAddresses[i] );

        // Set the Memory Space Enable and Bus Master Enable bits in the
        // PCI Command register.
        PciCfgPpi->Read( PeiServices, PciCfgPpi, EfiPeiPciCfgWidthUint16,
            mEhciPciBDFs[i] |
            PCI_REG_UHCI_COMMAND_REGISTER, &CmdReg );

        CmdReg = (UINT16) (CmdReg | 0x06);

        PciCfgPpi->Write( PeiServices, PciCfgPpi, EfiPeiPciCfgWidthUint16,
            mEhciPciBDFs[i] |
            PCI_REG_UHCI_COMMAND_REGISTER, &CmdReg );

        //Clear Config Flag Register
        ConfigureFlagAddress=mEhciMemBaseAddresses[i]+(UINT32)MMIO_READ8(mEhciMemBaseAddresses[i])+EHCI_HC_OPERATIONAL_CONFIG_FLAG_REG;
        MMIO_WRITE32(ConfigureFlagAddress, 0);

        // Clear the Memory Space Enable and Bus Master Enable bits in the
        // PCI Command register.
        PciCfgPpi->Read( PeiServices, PciCfgPpi, EfiPeiPciCfgWidthUint16,
            mEhciPciBDFs[i] |
            PCI_REG_UHCI_COMMAND_REGISTER, &CmdReg );

        CmdReg = (UINT16) ( CmdReg &= ~(0x6) );

        PciCfgPpi->Write( PeiServices, PciCfgPpi, EfiPeiPciCfgWidthUint16,
            mEhciPciBDFs[i] |
            PCI_REG_UHCI_COMMAND_REGISTER, &CmdReg );
    }
}


#endif

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   GetUhciController
//
// Description: This function returns controller type and I/O base address
//              value for the controller specified
//
// Input:       **PeiServices       Pointer to the PEI services table
//              *PciCfgPpi          Pointer to the PCI Configuration PPI
//              UsbControllerId     USB Controller ID
//
// Output:      EFI_STATUS
//              *ControllerType     Type of the USB controller
//              *IoBaseAddress      I/O base Address programmed for this
//                                  controller
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS GetUhciController (
    IN EFI_PEI_SERVICES           **PeiServices,
    IN EFI_PEI_USB_CONTROLLER_PPI *This,
    IN UINT8                      UsbControllerId,
    OUT UINTN                     *ControllerType,
    OUT UINTN                     *IoBaseAddress )
{

    if (UsbControllerId >= MAX_USB_CTRLERS) {
        return EFI_INVALID_PARAMETER;
    }

    *ControllerType = PEI_UHCI_CONTROLLER;
    *IoBaseAddress = gPeiUhciDev.IoBase[UsbControllerId];

    return EFI_SUCCESS;
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