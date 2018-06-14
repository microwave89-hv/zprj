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
// $Header: /Alaska/SOURCE/Modules/USBRecovery/OhciPeiBoard.c 6     4/11/11 11:59p Rameshr $
//
// $Revision: 6 $
//
// $Date: 4/11/11 11:59p $
//
//**********************************************************************
// Revision History
// ----------------
// $Log: /Alaska/SOURCE/Modules/USBRecovery/OhciPeiBoard.c $
// 
// 6     4/11/11 11:59p Rameshr
// [TAG]- EIP 57444
// [Category]-IMPROVEMENT
// [Description]- PI1.1 Support.
// [Files]- OhciPeiboard.c,Xhcipei.c, Peiusblib.c
// 
// 5     10/21/08 5:57p Michaela
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
// 4     7/29/08 7:50p Michaela
// cleaned-up SB700-specific code
// 
// 3     7/29/08 5:50p Michaela
// 1) Updated code to move most porting tasks to SDL
// 2) Added more debug break points and improved interactive
//     debugging capability for when a serial port is not available.
// 3) Updated help files
// 
// 2     7/18/08 5:04p Michaela
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
// 1     7/10/08 6:35p Michaela
// Updated to support OHCI controllers
//
//
//**********************************************************************

//<AMI_FHDR_START>
//----------------------------------------------------------------------------
//
// Name:        OhciPeiBoard.c
//
// Description: This file contains routines that are board specific for
//              initializing the OHCI controller in the USB Recovery module.
//
//----------------------------------------------------------------------------
//<AMI_FHDR_END>

#include <PEI.h>
#include <AmiPeiLib.h>
#include <token.h>
#include <PPI/PeiGetUCtrl.h>
#include <PPI/OhciPPI.h>
#include <PPI/stall.h>
#include "OhciPei.h"

#ifndef PI_SPECIFICATION_VERSION //old Core
extern EFI_STATUS PciCfgModify(
IN CONST EFI_PEI_SERVICES 	**PeiServices,
IN EFI_PEI_PCI_CFG_PPI_WIDTH	Width,
IN UINT64					Address,
IN UINTN					SetBits,
IN UINTN					ClearBits
);
#endif

//----------------------------------------------------------------------------
// Porting Steps:
//
// 1)  define/undefine the appropriate southbridge type
// 2)  define the OHCI_BASE register
// 3)  define registers and their set/clear bits for each register to be
//     modified in each controller's PCI configuration space
//
//----------------------------------------------------------------------------


// #define AMD_8111   // define to initialize AMD 8111 SB

// #define AMD_SB700  // define to initialize AMD SB700 SB

#define OHCI_BASE            PEI_OHCI_IOBASE // first OHCI device is defined
                                             // by SDL token and others
                                             // are programmatically 
                                             // determined 

#define OHCI_MMIO_SIZE       0x1000   // size of each MMIO region

// For the SB700, the SMBUS PCI configuration space is used
// to enable USB hardware in the Southbridge
#define SMBUS_PCI_USB_ENABLE_CFG  PEI_PCI_CFG_ADDRESS( 0, 0x14, 0, 0x68 )
#define SMBUS_PCI_EHCI_BITS       BIT2 | BIT6
#define SMBUS_PCI_OHCI_BITS       BIT0 | BIT1 | BIT4 | BIT5 | BIT7



//<AMI_THDR_START>
//---------------------------------------------------------------------------
//
// Name:   gOhciControllerPciTable
//
// Description: 
//      This is an array of type: PCI_BUS_DEV_FUNCTION
//
//      This array is initialized from the PEI_OHCI_PCI_DEVICES SDL 
//      token, which specifies a {bus,device,function} entry for each OHCI 
//      controller.  If no OHCI controllers exist, there will be only one 
//      NULL entry.
//
//      This array is used for PCI initialization of OHCI controllers, 
//      as well as access to PCI configuration registers.
//
// Notes:
//      gOhciControllerPciTable and gOhciControllerCount are accessed via 
//      extern declarations by OHCI generic code to access PCI configuration 
//      space registers.
//
//---------------------------------------------------------------------------
//<AMI_THDR_END>

PCI_BUS_DEV_FUNCTION gOhciControllerPciTable[] = {USBR_OHCI_CONTROLLER_PCI_ADDRESS};
UINT16 gOhciControllerCount = \
    sizeof(gOhciControllerPciTable) / sizeof(PCI_BUS_DEV_FUNCTION);


//<AMI_THDR_START>
//---------------------------------------------------------------------------
//
// Name:   gOhciPciRegisterTable
//
// Description: 
//      This is an array of type: OHCI_PCI_PROGRAMMING_TABLE
//
//      This array is initialized from the OHCI_CONTROLLER_PCI_REGISTER_VALUE
//      SDL eLink, which specifies a { RegisterSize, Register, BitsToSet, 
//      BitsToClear } entry for each register in the PCI configuration space
//      that needs to be modified.
//
//      This array is used for PCI initialization of OHCI controllers.
//
// Notes:
//      If no OHCI controllers exist, there will be only one 
//      NULL entry.
//
//      When this table is used, it is assumed that all OHCI controllers 
//      are identically programmed for the platform.
//
//      Other important notes are:
//
//                  1)  do not include the BAR register (the first BAR is 
//                      PEI_OHCI_IOBASE and subsequent BAR values are 
//                      calculated from there),
//                  2)  the command register should be last, as it enables
//                      the devices MMIO access space.
//
//---------------------------------------------------------------------------
//<AMI_THDR_END>

OHCI_PCI_PROGRAMMING_TABLE gOhciPciRegisterTable[] = {USBR_OHCI_CONTROLLER_PCI_REGISTER_VALUE};
#define OHCI_PCI_REGISTER_TABLE_SIZE \
    sizeof(gOhciPciRegisterTable) / sizeof(OHCI_PCI_PROGRAMMING_TABLE)


//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   DefaultInit
//
// Description: 
//      This function generically initializes the PCI configuration space 
//      registers for all the OHCI controllers whose PCI addresses are 
//      specified by the global PCI_BUS_DEV_FUNCTION array and whose PCI 
//      register programming details are specified by the global 
//      OHCI_PCI_PROGRAMMING_TABLE array.
//
// Input:       
//      IN EFI_PEI_SERVICES **PeiServices
//                  --  EFI_PEI_SERVICES pointer
//      IN EFI_PEI_PCI_CFG_PPI *Pci
//                  --  EFI_PEI_PCI_CFG_PPI pointer
//      IN EFI_PEI_STALL_PPI *StallPpi
//                  --  EFI_PEI_STALL_PPI pointer
//
// Output:     
//      EFI_STATUS (Return Value)
//                  = EFI_SUCCESS on successful completion
//                      or valid EFI error code
//
// Notes:
//      This function should not need porting.  All porting is accomplished
//      in the global PCI_BUS_DEV_FUNCTION and OHCI_PCI_PROGRAMMING_TABLE
//      arrays, where the former is defined by the 
//      USBR_OHCI_CONTROLLER_PCI_ADDRESS SDL eLink and the latter is defined 
//      by the USBR_OHCI_CONTROLLER_PCI_REGISTER_VALUE SDL eLink.
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS DefaultInit (
    IN EFI_PEI_SERVICES         **PeiServices,
    IN EFI_PEI_PCI_CFG_PPI      *Pci,
    IN EFI_PEI_STALL_PPI        *StallPpi )
{
    EFI_STATUS Status;
    UINT32     OhciBaseAddress = OHCI_BASE;
    UINT16     ControllerIndex;
    UINT16     RegisterIndex;


    //------------------------------------------------------------------------
    // PCI configuration space programming for all OHCI controllers
    //------------------------------------------------------------------------
    for (ControllerIndex = 0;
         ControllerIndex < gOhciControllerCount;
         ControllerIndex++, OhciBaseAddress += OHCI_MMIO_SIZE)
    {

        // Program the BAR
        //~~~~~~~~~~~~~~~~
        ABORT_ON_ERROR(
            Pci->Write( PeiServices, Pci,
                EfiPeiPciCfgWidthUint32,
                OHCI_PCI_ADDRESS( ControllerIndex, OHCI_BASE_ADDR_REG ),
                &OhciBaseAddress );
        )

        // Program all other registers using gOhciPciRegisterTable[]
        //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
        for (RegisterIndex = 0;
             RegisterIndex < OHCI_PCI_REGISTER_TABLE_SIZE;
             RegisterIndex++)
        {
            EFI_PEI_PCI_CFG_PPI_WIDTH Width;
            
            switch (gOhciPciRegisterTable[RegisterIndex].Size)
            {
            	case 8:	
                    Width = EfiPeiPciCfgWidthUint8; 
                    break;
            	case 16:	
                    Width = EfiPeiPciCfgWidthUint16; 
                    break;
            	case 32:	
                    Width = EfiPeiPciCfgWidthUint32; 
                    break;
            	case 64:	
                    Width = EfiPeiPciCfgWidthUint64; 
                    break;
            	default:
                    continue;
            }

            ABORT_ON_ERROR(
                PciCfgModify(
                    PeiServices,
                    Width,
                    OHCI_PCI_ADDRESS( ControllerIndex,
                        gOhciPciRegisterTable[RegisterIndex].Register ),
                    gOhciPciRegisterTable[RegisterIndex].SetBits,
                    gOhciPciRegisterTable[RegisterIndex].ClearBits );
            )
        }
    }

    return Status = EFI_SUCCESS;
}


#ifdef AMD_8111
//-----------------------------------------------------
// This code is not tested, it is simply preserved here
//-----------------------------------------------------

#define REG_PRI_MEMBASE     0x20
#define REG_PRI_MEMLIM      0x22

EFI_STATUS Amd8111Init (
    IN EFI_PEI_SERVICES **PeiServices,
    EFI_PEI_PCI_CFG_PPI *Pci,
    EFI_PEI_STALL_PPI   *StallPpi )
{
    EFI_STATUS      Status;
    UINT32          Buffer32;
    UINT16          Buffer16;
    UINT16          CmdReg;
    volatile UINT32 BaseAddress;

    //
    // OHCI is sits behind the PCI brige. So program the PCI bridge
    // First program bus numbers so that PCI slots are available
    //
    Buffer32 = 0x080800;
    Pci->Write( PeiServices, Pci, EfiPeiPciCfgWidthUint32,
        PEI_PCI_CFG_ADDRESS( 0, 30, 0, REG_PRI_BNUM ),
        &Buffer32
    );


    // Defines the base of memory range for PCI. 15:4 this 12 bits corresponds
    // to 31:20 of mem addr 1MB boundary
    BaseAddress = 0xc0c00000;
    BaseAddress >>= 16;
    BaseAddress &= 0xfffffff0;
    Buffer16 = (UINT16) BaseAddress;
    Pci->Write( PeiServices, Pci, EfiPeiPciCfgWidthUint16,
        PEI_PCI_CFG_ADDRESS( 0, 30, 0, REG_PRI_MEMBASE ),
        &Buffer16
    );

    //Defines the top of the memory range
    //  BaseAddress = 0xc0c00000;
    //  BaseAddress += 0x00100000;
    //  BaseAddress >>= 16;
    //  BaseAddress &= 0xfffffff0;
    //  Buffer16 = (UINT16)BaseAddress;
    Pci->Write( PeiServices, Pci, EfiPeiPciCfgWidthUint16,
        PEI_PCI_CFG_ADDRESS( 0, 30, 0, REG_PRI_MEMLIM ),
        &Buffer16
    );

    //Program the prefectable memory space also.
    BaseAddress = 0xc0c00000;
    BaseAddress += 0x00100000;
    BaseAddress >>= 16;
    BaseAddress &= 0xfffffff0;
    Buffer16 = (UINT16) BaseAddress;
    Pci->Write( PeiServices, Pci, EfiPeiPciCfgWidthUint16,
        PEI_PCI_CFG_ADDRESS( 0, 30, 0, 0x24 ),
        &Buffer16
    );

    Pci->Write( PeiServices, Pci, EfiPeiPciCfgWidthUint16,
        PEI_PCI_CFG_ADDRESS( 0, 30, 0, 0x26 ),
        &Buffer16
    );


    //Enable memory space, bus mastering of the root bridge
    Pci->Read(
        PeiServices,
        Pci,
        EfiPeiPciCfgWidthUint16,
        PEI_PCI_CFG_ADDRESS( 0, 30, 0, 0x04 ),
        &CmdReg
    );
    CmdReg = (UINT16) (CmdReg | 0x06);
    Pci->Write(
        PeiServices,
        Pci,
        EfiPeiPciCfgWidthUint16,
        PEI_PCI_CFG_ADDRESS( 0, 30, 0, 0x04 ),
        &CmdReg
    );
}
#endif // #ifdef AMD_8111


#ifdef AMD_SB700
EFI_STATUS AmdSb700Init (
    IN EFI_PEI_SERVICES **PeiServices,
    EFI_PEI_PCI_CFG_PPI *Pci,
    EFI_PEI_STALL_PPI   *StallPpi )
{

    //-----------------------------------------------------------------------
    // Enable OHCI controllers from the SMBUS PCI configuration space
    // using the SMBUS PCI space USB enable register
    //
    // By default, the companion controller (OHCI) should be the owner
    // of the root hub port, so the EHCI controller hardware block
    // does not need to be disabled.
    //-----------------------------------------------------------------------
    ABORT_ON_ERROR(
        PciCfgModify( PeiServices, 
            EfiPeiPciCfgWidthUint8,
            SMBUS_PCI_USB_ENABLE_CFG,
            SMBUS_PCI_OHCI_BITS + SMBUS_PCI_EHCI_BITS,
            0
        )
    )

    return EFI_SUCCESS;
}
#endif // #ifdef AMD_SB700





//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure: OhciPeiBoardInit
//
// Description:
//      This is a porting hook for board-specific OHCI controller
//      initialization
//
// Input:
//      IN EFI_PEI_SERVICES **PeiServices -
//      IN EFI_PEI_PCI_CFG_PPI *Pci -
//      IN EFI_PEI_STALL_PPI *StallPpi -
//
// Output:
//      VOID
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS OhciPeiBoardInit (
    IN EFI_PEI_SERVICES    **PeiServices,
    IN EFI_PEI_PCI_CFG_PPI *Pci,
    IN EFI_PEI_STALL_PPI   *StallPpi )
{
    EFI_STATUS Status = EFI_SUCCESS;

    // SB-specific programming
  #if defined (AMD_8111)
    Status = Amd8111Init( PeiServices, Pci, StallPpi );
  #elif  defined (AMD_SB700)
    Status = AmdSb700Init( PeiServices, Pci, StallPpi );
  #endif

    // Generic programming for all OHCI SB, should be called
    // for all types of southbridges after platform-specific
    // programming has been done.
    if (!EFI_ERROR(Status)){
        Status = DefaultInit( PeiServices, Pci, StallPpi );
    }

    // PCI root bridge programming is done.
    // At this stage the OHCI controller should be visible and
    // Memory mapped IO space should be visible

    return Status;

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