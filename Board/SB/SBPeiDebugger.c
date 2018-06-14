//*************************************************************************
//*************************************************************************
//**                                                                     **
//**        (C)Copyright 1985-2011, American Megatrends, Inc.            **
//**                                                                     **
//**                       All Rights Reserved.                          **
//**                                                                     **
//**      5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093           **
//**                                                                     **
//**                       Phone: (770)-246-8600                         **
//**                                                                     **
//*************************************************************************
//*************************************************************************

//*************************************************************************
// $Header: /Alaska/BIN/Chipset/Intel/SouthBridge/LynxPoint/Intel Pch SB Board/SBPeiDebugger.c 1     2/08/12 8:22a Yurenlai $
//
// $Revision: 1 $
//
// $Date: 2/08/12 8:22a $
//*************************************************************************
// Revision History
// ----------------
// $Log: /Alaska/BIN/Chipset/Intel/SouthBridge/LynxPoint/Intel Pch SB Board/SBPeiDebugger.c $
// 
// 1     2/08/12 8:22a Yurenlai
// Intel Lynx Point/SB eChipset initially releases.
// 
//*************************************************************************

//<AMI_FHDR_START>
//----------------------------------------------------------------------------
//
// Name:    SBPeiDebugger.C
//
// Description:  This file contains PEI stage board component code for
//        Template SB
//
//----------------------------------------------------------------------------
//<AMI_FHDR_END>

#include <Efi.h>
#include <AmiLib.h>
#include <Token.h>
#include "SB.h"
#include <PchAccess.h>

#include "AmiDebugPort.h"

#define EHCI_DEV_FUN_1A_7               0xD7  //1A Func 7
#define EHCI_DEV_FUN_1A_0               0xD0  //1A Func 0
#define EHCI_DEV_FUN_1D_7               0xEF  //1D Func 7
#define EHCI_DEV_FUN_1D_0               0xE8  //1D Func 0
#define SMBUS_DEV_FUN                   (0x1F << 3) + 3   //1F Func 3
#define THERMAL_DEV_FUN_1F_6            (0x1F << 3) + 6   //1F Func 6

#define ICH5_PMCSR                      0x8000
#define PWR_MGT_CAP_ID                  1
#define DBG_PRT_CAP_ID                  0xA
#define TIMER_CONTROL_PORT              0x43
#define TIMER0_COUNT_PORT               0x40
#define B_PCH_LPC_RID_0                 0xFF
#define V_PCH_LPC_RID_0                 0x00
#define R_PCH_THERMAL_TBARB             0x40
#define R_PCH_THERMAL_TBARBH            0x44

// Function Prototypes
UINT8   ReadPCIRegByte(UINT8 RegNum,UINT8 BusNum,UINT8 DevFunc);
UINT16  ReadPCIRegWord(UINT8 RegNum,UINT8 BusNum,UINT8 DevFunc);
UINT32  ReadPCIRegDWord(UINT8 RegNum,UINT8 BusNum,UINT8 DevFunc);
VOID    WritePCIRegByte(UINT8 RegNum,UINT8 BusNum,UINT8 DevFunc, UINT8 val);
VOID    OrPCIRegByte(UINT8 RegNum,UINT8 BusNum,UINT8 DevFunc, UINT8 val);
VOID    WritePCIRegWord(UINT8 RegNum,UINT8 BusNum,UINT8 DevFunc, UINT16 val);
VOID    WritePCIRegDWord(UINT8 RegNum,UINT8 BusNum,UINT8 DevFunc, UINT32 val);
VOID    OrPCIRegDWord(UINT8 RegNum,UINT8 BusNum,UINT8 DevFunc, UINT32 val);
VOID    ANDPCIRegDWord(UINT8 RegNum,UINT8 BusNum,UINT8 DevFunc, UINT32 val);
VOID    ANDPCIRegByte(UINT8 RegNum,UINT8 BusNum,UINT8 DevFunc, UINT8 val);
VOID    OrWritePCIRegByte(UINT8 RegNum,UINT8 BusNum,UINT8 DevFunc, UINT8 val);

UINT32  GetPCIAddrFormat(UINT8 RegNum,UINT8 BusNum,UINT8 DevFunc);
UINT8   FindCapPtr(UINT8 Bus, UINT8 DevFunc, UINT8 CapId);
VOID    PEI8259WriteMask(UINT16 Mask, UINT16 EdgeLevel);
VOID    PEI8259SetVectorBase (UINT8 MasterBase, UINT8 SlaveBase);
VOID    Program8254Timer0(UINT16 Count);

//Macros for Mmio Read/Write

#define Mmio32(Address)               (*(volatile UINT32*)(UINTN)(Address))
#define MmioOr32(Address, Value)      (*(volatile UINT32*)(UINTN)(Address) |= (Value))
#define MmioAnd32(Address, Value)     (*(volatile UINT32*)(UINTN)(Address) &= (Value))

#define R_PCH_SMBUS_BASE              0x20
#define R_PCH_SMBUS_PCICMD            0x04
#define B_PCH_SMBUS_PCICMD_IOSE       BIT0

#define R_PCH_SMBUS_HOSTC             0x40
#define B_PCH_SMBUS_HOSTC_SSRESET     BIT3
#define B_PCH_SMBUS_HOSTC_I2C_EN      BIT2
#define B_PCH_SMBUS_HOSTC_SMI_EN      BIT1
#define B_PCH_SMBUS_HOSTC_HST_EN      BIT0


//
// SMBus I/O Registers
//
#define R_PCH_SMBUS_HSTS                    0x00  // Host Status Register R/W
#define B_PCH_SMBUS_HBSY                    0x01
#define B_PCH_SMBUS_INTR                    0x02
#define B_PCH_SMBUS_DERR                    0x04
#define B_PCH_SMBUS_BERR                    0x08
#define B_PCH_SMBUS_FAIL                    0x10
#define B_PCH_SMBUS_SMBALERT_STS            0x20
#define B_PCH_SMBUS_IUS                     0x40
#define B_PCH_SMBUS_BYTE_DONE_STS           0x80
#define B_PCH_SMBUS_HSTS_ALL                0xFF
#define R_PCH_SMBUS_HCTL                    0x02  // Host Control Register R/W
#define B_PCH_SMBUS_INTREN                  0x01
#define B_PCH_SMBUS_KILL                    0x02

#define STALL_PERIOD                        10      // 10 microseconds
#define STALL_TIME                          1000000 // 1,000,000 microseconds = 1 second
#define BUS_TRIES                           3       // How many times to retry on Bus Errors

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:  SmbusGetIoBase
//
// Description:  Get SMBUS IO Base address
//
// Input:    None
//
// Output:   Rerturn SMBUS IO Base Address
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
UINT32
SmbusGetIoBase (VOID)
{
    return SMBUS_BASE_ADDRESS;
}
//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:  SmbusIoRead
//
// Description:  This function provides a standard way to read PCH Smbus IO registers.
//
// Input:    Offset -  Register offset from Smbus base IO address.
//
// Output:   Returns data read from IO.
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
UINT8
SmbusIoRead (IN UINT8 Offset)
{
    return IoRead8 ((UINT16)(SmbusGetIoBase () + Offset));
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:  SmbusIoWrite
//
// Description:  This function provides a standard way to write PCH Smbus IO registers.
//
// Input:    Offset -  Register offset from Smbus base IO address.
//           Data   -  Data to write to register.
//
// Output:   None
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID
SmbusIoWrite (
  IN      UINT8           Offset,
  IN      UINT8           Data
)
{
    //
    // Write New Value
    //
    IoWrite8 ((UINT16)(SmbusGetIoBase () + Offset), Data);
    return ;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:    PchPmTimerStall
//
// Description:  Delay for at least the request number of microseconds.
//
// Input:    Usec -  Number of microseconds to delay.
//
// Output:   None
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID PchPmTimerStall (IN UINTN Usec)
{
    UINTN   Counter = Usec * 3;
    UINTN   i;
    UINT32  Data32;
    UINT32  PrevData;

    PrevData = IoRead32(PM_BASE_ADDRESS + 8);
    for (i=0; i < Counter; ) {
       Data32 = IoRead32(PM_BASE_ADDRESS + 8);    
        if (Data32 < PrevData) {        // Reset if there is a overlap
            PrevData=Data32;
            continue;
        }
        i += (Data32 - PrevData); 
        PrevData=Data32;
    }

    return;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:    IoDone
//
// Description:  This function provides a standard way to write PCH Smbus IO registers.
//
// Input:    *StsReg -  Not used for input.
//
// Output:  On return, contains the value of the SMBus status register.
//          Returns TRUE if transaction is complete, FALSE otherwise.
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
BOOLEAN IoDone (IN OUT UINT8 *StsReg)
{
    //
    // Wait for IO to complete
    //
    UINTN StallIndex;
    UINTN StallTries;

    StallTries  = STALL_TIME / STALL_PERIOD;
  
    for (StallIndex  = 0; StallIndex < StallTries; StallIndex++) {
        *StsReg = SmbusIoRead (R_PCH_SMBUS_HSTS);
        if (*StsReg & (B_PCH_SMBUS_INTR | B_PCH_SMBUS_BYTE_DONE_STS | B_PCH_SMBUS_DERR | B_PCH_SMBUS_BERR)) {
        return TRUE;
        } else {
        PchPmTimerStall (STALL_PERIOD);
        }
    }
    return FALSE;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:  AcquireBus
//
// Description:  Check if it's ok to use the bus.
//
// Input:    None
//
// Output:   EFI_TIMEOUT -  SmBus is busy, it's not safe to send commands.
//           EFI_SUCCESS -  SmBus is acquired and it's safe to send commands.
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS AcquireBus (VOID)
{
    UINT8 StsReg;

    StsReg  = 0;
    StsReg  = SmbusIoRead (R_PCH_SMBUS_HSTS);
    if (StsReg & B_PCH_SMBUS_IUS) {
        return EFI_TIMEOUT;
    } else if (StsReg & B_PCH_SMBUS_HBSY) {
        //
        // Clear Status Register and exit
        //
        SmbusIoWrite (R_PCH_SMBUS_HSTS, B_PCH_SMBUS_HSTS_ALL);
        return EFI_TIMEOUT;
    } else {
        //
        // Clear out any odd status information (Will Not Clear In Use)
        //
        SmbusIoWrite (R_PCH_SMBUS_HSTS, StsReg);
        return EFI_SUCCESS;
    }
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:  SmbusExec
//
// Description:  This function provides a standard way to execute Smbus protocols
//               as defined in the SMBus Specification.
//
// Input:    *Length -  How many bytes to read. Must be 0 <= Length <= 32 depending on Operation
//                      It will contain the actual number of bytes read/written.
//           *Buffer -  Contain the data read/written.
//
// Output:   EFI_SUCCESS           -  The operation completed successfully.
//           EFI_INVALID_PARAMETER -  Length or Buffer is NULL for any operation besides
//                                    quick read or quick write.
//           EFI_CRC_ERROR         -  Failed due to CRC error.
//           EFI_DEVICE_ERROR      -  There was an Smbus error (NACK) during the operation.
//                                    This could indicate the slave device is not present
//                                    or is in a hung condition.
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS
SmbusExec (
  IN OUT  UINTN                     *Length,
  IN OUT  VOID                      *Buffer
  )
{
  EFI_STATUS  Status;
  UINT8       AuxcReg;
  UINT8       AuxStsReg;
  UINT8       SmbusOperation;
  UINT8       StsReg;
  UINT8       SlvAddrReg;
  UINT8       HostCmdReg;
  UINT8       BlockCount;
  UINTN       Index;
  UINTN       BusIndex;
  UINT8       *CallBuffer;
  UINT8       ClockAddress = CLOCK_GENERATOR_ADDRESS;


    CallBuffer  = Buffer;
    BlockCount  = 0;
    
    //
    // See if its ok to use the bus based upon INUSE_STS bit.
    //
    Status = AcquireBus ();
    if (EFI_ERROR (Status)) {
        return Status;
    }
    //
    // This is the main operation loop.  If the operation results in a Smbus
    // collision with another master on the bus, it attempts the requested
    // transaction again at least BUS_TRIES attempts.
    //
    for (BusIndex = 0; BusIndex < BUS_TRIES; BusIndex++) {
        //
        // Operation Specifics (pre-execution)
        //
        Status          = EFI_SUCCESS;
        SmbusOperation  = V_PCH_SMBUS_SMB_CMD_QUICK;
        SlvAddrReg      = (UINT8) (ClockAddress | 1);
        HostCmdReg      = 0;
        AuxcReg         = 0;

        SmbusIoWrite (R_PCH_SMBUS_HD0, *(UINT8 *) Length);
        SlvAddrReg--;
        BlockCount = (UINT8) (*Length);

        // The "break;" command is not present here to allow code execution
        // do drop into the next case, which contains common code to this case.
        SmbusOperation = V_PCH_SMBUS_SMB_CMD_BLOCK;
        if ((*Length < 1) || (*Length > 32)) {
            Status = EFI_INVALID_PARAMETER;
        }

        AuxcReg |= B_PCH_SMBUS_E32B;

        //
        // Set Auxiliary Control register
        //
        SmbusIoWrite (R_PCH_SMBUS_AUXC, AuxcReg);

        //
        // Reset the pointer of the internal buffer
        //
        SmbusIoRead (R_PCH_SMBUS_HCTL);

        //
        // Now that the 32 byte buffer is turned on, we can write th block data
        // into it
        //
        for (Index = 0; Index < BlockCount; Index++) {
            //
            // Write next byte
            //
            SmbusIoWrite (R_PCH_SMBUS_HBD, CallBuffer[Index]);
        }
        //
        // Set SMBus slave address for the device to send/receive from
        //
        SmbusIoWrite (R_PCH_SMBUS_TSA, SlvAddrReg);

        //
        // Set Command register
        //
        SmbusIoWrite (R_PCH_SMBUS_HCMD, HostCmdReg);

        //
        // Set Control Register (Initiate Operation, Interrupt disabled)
        //
        SmbusIoWrite (R_PCH_SMBUS_HCTL, (UINT8) (SmbusOperation + B_PCH_SMBUS_START));

        //
        // Wait for IO to complete
        //
        if (!IoDone (&StsReg)) {
            Status = EFI_TIMEOUT;
            break;
        } else if (StsReg & B_PCH_SMBUS_DERR) {
            AuxStsReg = SmbusIoRead (R_PCH_SMBUS_AUXS);
            if (AuxStsReg & B_PCH_SMBUS_CRCE) {
                Status = EFI_CRC_ERROR;
            } else {
                Status = EFI_DEVICE_ERROR;
            }
            break;
        } else if (StsReg & B_PCH_SMBUS_BERR) {
            //
            // Clear the Bus Error for another try
            //
            Status = EFI_DEVICE_ERROR;
            SmbusIoWrite (R_PCH_SMBUS_HSTS, B_PCH_SMBUS_BERR);
            //
            // Clear Status Registers
            //
            SmbusIoWrite (R_PCH_SMBUS_HSTS, B_PCH_SMBUS_HSTS_ALL);
            SmbusIoWrite (R_PCH_SMBUS_AUXS, B_PCH_SMBUS_CRCE);
            //
            // If bus collision happens, stall some time, then try again
            // Here we choose 10 milliseconds to avoid MTCP transfer.
            //
            PchPmTimerStall (STALL_PERIOD);
            continue;
        }

        //
        // successfull completion
        // Operation Specifics (post-execution)
        //
        SmbusIoWrite (R_PCH_SMBUS_HSTS, B_PCH_SMBUS_BYTE_DONE_STS);

        if ((StsReg & B_PCH_SMBUS_BERR) && (Status != EFI_BUFFER_TOO_SMALL)) {
            //
            // Clear the Bus Error for another try
            //
            Status = EFI_DEVICE_ERROR;
            SmbusIoWrite (R_PCH_SMBUS_HSTS, B_PCH_SMBUS_BERR);
            //
            // If bus collision happens, stall some time, then try again
            // Here we choose 10 milliseconds to avoid MTCP transfer.
            //
            PchPmTimerStall (STALL_PERIOD);
            continue;
        } else {
            break;
        }
    }

    //
    // Clear Status Registers and exit
    //
    SmbusIoWrite (R_PCH_SMBUS_HSTS, B_PCH_SMBUS_HSTS_ALL);
    SmbusIoWrite (R_PCH_SMBUS_AUXS, B_PCH_SMBUS_CRCE);
    SmbusIoWrite (R_PCH_SMBUS_AUXC, 0);
    return Status;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:  SmbusInit
//
// Description:  Initialize SMBUS.
//
// Input:    None
//
// Output:   None
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID SmbusInit(VOID)
{
  UINT8   ConfigurationTableDefault[] = CLOCK_GENERATOR_SETTINGS;
  UINTN   Length = sizeof (ConfigurationTableDefault);
    //
    // set the BAR & I/O space enable ourselves
    //
    WritePCIRegDWord(R_PCH_SMBUS_BASE, 0, SMBUS_DEV_FUN,(UINT32)SMBUS_BASE_ADDRESS);
    OrWritePCIRegByte(R_PCH_SMBUS_PCICMD, 0, SMBUS_DEV_FUN,(UINT8) B_PCH_SMBUS_PCICMD_IOSE);

    //
    // Reset the SMBus host controller
    //
    OrWritePCIRegByte(B_PCH_SMBUS_HOSTC_SSRESET, 0, SMBUS_DEV_FUN,(UINT8) R_PCH_SMBUS_HOSTC);

    //
    // Enable the SMBus host controller
    //  
    ANDPCIRegByte(R_PCH_SMBUS_HOSTC, 0, SMBUS_DEV_FUN,(UINT8)((B_PCH_SMBUS_HOSTC_SMI_EN | B_PCH_SMBUS_HOSTC_I2C_EN)));
    OrWritePCIRegByte(R_PCH_SMBUS_HOSTC, 0, SMBUS_DEV_FUN,(UINT8) B_PCH_SMBUS_HOSTC_HST_EN);

    //
    // Clear Status Register before anyone uses the interfaces
    //
    SmbusIoWrite (R_PCH_SMBUS_HSTS, B_PCH_SMBUS_HSTS_ALL);

    //
    //Do the RedFort CRB Clock Programming
    //
    SmbusExec(&Length, ConfigurationTableDefault);
    return;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:  InitEhciDebugPort
//
// Description:  Initialize PCH EHCI.
//
// Input:    None
//
// Output:   None
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID InitEhciDebugPort(VOID)
{
    UINT32 Rcba = SB_RCBA;

    MmioOr32 ((UINTN)(Rcba + 0x3598), BIT0);
    Mmio32 ((UINTN)(Rcba + 0x3598));
    OrPCIRegDWord(0xF4, 0, EHCI_DEV_FUN_1D_7,(UINT32)(BIT31) );
    OrPCIRegDWord(0xF4, 0, EHCI_DEV_FUN_1D_7,(UINT32) (BIT16 | BIT17 | BIT18 | BIT19));
    ANDPCIRegDWord(0xF4, 0, EHCI_DEV_FUN_1D_7,(UINT32) (BIT31));
    OrPCIRegDWord(0xF4, 0, EHCI_DEV_FUN_1A_7,(UINT32) (BIT31) );
    OrPCIRegDWord(0xF4, 0, EHCI_DEV_FUN_1A_7,(UINT32) (BIT16 | BIT17 | BIT18 | BIT19));
    ANDPCIRegDWord(0xF4, 0, EHCI_DEV_FUN_1A_7,(UINT32) (BIT31));
    //
    //Enable RMH
    //
    MmioAnd32 ((UINTN)(Rcba + 0x3598), (UINT32)(~BIT0));
    Mmio32 ((UINTN)(Rcba + 0x3598));
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:  SBPEIDBG_InitUsbEhci
//
// Description:  This eLink function is used to initialize the EHCI controller
//               debug port for USB PEI Debugging. It also fills the transport
//               interface structure with appropriate information
//
// Input:    DebugPort    Debug transport interface structure
//
// Output:    EFI_STATUS
//
// Notes:    PORTING REQUIRED
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

#ifdef  USB_DEBUGGER

EFI_STATUS
SBPEIDBG_InitUsbEhci (
  IN OUT  PEI_DBG_PORT_INFO  *DebugPort
)
{
  UINT8        PwrMgtCapReg;
  UINT8        DbgPrtCapReg;
  UINT16       CmdReg;
  UINT16       DbgPrtBaseOffset;
  UINT32       EhciBaseAddress = 0;

  if (DebugPort->UsbDebugPort.USBBaseAddr)
    EhciBaseAddress = DebugPort->UsbDebugPort.USBBaseAddr;
  else
    EhciBaseAddress = EHCI_MMIO_BASE_ADDRESS;

  InitEhciDebugPort();

  //Clear Thermal Base
  WritePCIRegDWord(R_PCH_THERMAL_TBARB, 0, THERMAL_DEV_FUN_1F_6, 0);
  WritePCIRegDWord(R_PCH_THERMAL_TBARBH, 0, THERMAL_DEV_FUN_1F_6, 0);

  SmbusInit();

  //First disable the EHCI device by programming PCI command register
  CmdReg = ReadPCIRegWord(0x4, PCI_EHCI_BUS_NUMBER, PCI_EHCI_DEV_FUNC_NUMBER);

  if(CmdReg & 2) {
    WritePCIRegWord(0x4, PCI_EHCI_BUS_NUMBER, PCI_EHCI_DEV_FUNC_NUMBER, 0);
  }

  // Assign MMIO base address register in appropriate PCI register 
  WritePCIRegDWord(0x10, PCI_EHCI_BUS_NUMBER, PCI_EHCI_DEV_FUNC_NUMBER, EhciBaseAddress);

  //Set the Power state of the device to D0
  PwrMgtCapReg = FindCapPtr(PCI_EHCI_BUS_NUMBER, PCI_EHCI_DEV_FUNC_NUMBER, PWR_MGT_CAP_ID);

  WritePCIRegWord(PwrMgtCapReg + 4, PCI_EHCI_BUS_NUMBER, PCI_EHCI_DEV_FUNC_NUMBER, ICH5_PMCSR);
            
  // Enable ICH5 EHCI register & make it Bus master
  CmdReg = CmdReg | 0x06;
  WritePCIRegWord(0x4, PCI_EHCI_BUS_NUMBER, PCI_EHCI_DEV_FUNC_NUMBER, CmdReg);

  // Locate the Debug port register Interface location
  DbgPrtCapReg = FindCapPtr(PCI_EHCI_BUS_NUMBER, PCI_EHCI_DEV_FUNC_NUMBER, DBG_PRT_CAP_ID);
  DbgPrtBaseOffset = ReadPCIRegWord(DbgPrtCapReg + 2, PCI_EHCI_BUS_NUMBER, PCI_EHCI_DEV_FUNC_NUMBER);
  DbgPrtBaseOffset &= 0x1fff;

  if (DebugPort->UsbDebugPort.USBBaseAddr == 0) {
    DebugPort->UsbDebugPort.USBBaseAddr = EHCI_MMIO_BASE_ADDRESS;
    DebugPort->UsbDebugPort.MemoryMappedIoSpaceSize = EHCI_MMIO_SIZE;
  }
  DebugPort->UsbDebugPort.USBDebugPortStartAddr = EhciBaseAddress + DbgPrtBaseOffset;
  DebugPort->UsbDebugPort.PciBusNumber = PCI_EHCI_BUS_NUMBER;
  DebugPort->UsbDebugPort.PciDeviceNumber = (PCI_EHCI_DEV_FUNC_NUMBER >> 3);
  DebugPort->UsbDebugPort.PciFunctionNumber = PCI_EHCI_DEV_FUNC_NUMBER & 0x7;
  DebugPort->UsbDebugPort.PciBAROffset = PCI_EHCI_BAR_OFFSET;
  DebugPort->UsbDebugPort.InitUSBEHCI = SBPEIDBG_InitUsbEhci;

  return EFI_SUCCESS;
}

#endif

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:  EnableSerialIRQ
//
// Description:  This function programs the SB register to enable the serial
//               IRQ
//
// Input:     None
//
// Output:    None
//
// Notes:     PORTING REQUIRED
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

VOID
EnableSerialIRQ (VOID)
{
  WritePCIRegByte (R_PCH_LPC_SERIRQ_CNT,0x00, 0xf8, 0xD0);  // Device 31 , Function 0 , Bus 0 , Reg 64h, Value d0
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:  Enable_LPC_IO_Decode
//
// Description:  This function programs the SB register to enable the LPC IO
//               Decoding ranges to enable the programming of SIO and Serial Port.
//
// Input:     None
//
// Output:    None
//
// Notes:     PORTING REQUIRED
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

VOID
Enable_LPC_IO_Decode (VOID)
{
  UINT32  GEN1_DEC = 0,GEN2_DEC = 0;
  UINT16  LPC_EN = 0, LPC_IO_DEC = 0;

#if SIO_SUPPORT && Smsc1007_PME_BASE_ADDRESS
// Enable SIO Runtime Register decode
  GEN1_DEC = ReadPCIRegDWord(R_PCH_LPC_GEN1_DEC, 0x00, 0xf8);
  GEN1_DEC |=  0xFFFFFFFF & ((0x7C << 16) | ((Smsc1007_PME_BASE_ADDRESS & 0xFFF0) + 1));
  WritePCIRegDWord (R_PCH_LPC_GEN1_DEC, 0x00, 0xf8, GEN1_DEC);
#endif

// Enables SIO Configuration Ports decode
  GEN2_DEC = ReadPCIRegDWord (R_PCH_LPC_GEN2_DEC, 0x00, 0xf8);
  GEN2_DEC |= 0xFFFFFFFF & ((0x0C << 16) | ((0x16 << 8) | 0x41));
  WritePCIRegDWord (R_PCH_LPC_GEN2_DEC, 0x00, 0xf8, GEN2_DEC);


// Enable COMA decode
  LPC_EN = ReadPCIRegWord (R_PCH_LPC_ENABLES, 0x00, 0xf8);  //82h
  LPC_EN |= 0x0001;
  WritePCIRegWord (R_PCH_LPC_ENABLES, 0x00, 0xf8, LPC_EN);

  LPC_IO_DEC = ReadPCIRegWord (R_PCH_LPC_IO_DEC, 0x00, 0xf8);  //80h
  LPC_IO_DEC &= 0xFF00;
  WritePCIRegWord (R_PCH_LPC_IO_DEC, 0x00, 0xf8, LPC_IO_DEC);
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:  ProgramACPIBaseToDisableTCO
//
// Description:  This function programs the SB register to disable
//               the TCO timer. If this timer is not disabled the system
//               will shutdown or reset as soon as the timer is expired
//
// Input:     None
//
// Output:    None
//
// Notes:     PORTING REQUIRED
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

VOID ProgramACPIBaseToDisableTCO (VOID)
{
  UINT32        dData;
  UINT16        TCOBASE;

  dData = PM_BASE_ADDRESS;              //Port base addr Value of SDL token
  
  WritePCIRegDWord(0x40,                        //ACPI Base Addr (LPC I/F D31:F0)
                   0,                           //bus #
                   (UINT8)((31 << 3) | 0),      //dev & func #
                   dData);

  TCOBASE = (UINT16)(dData + 0x60);        //TCO base addr = 0xFF80 + 0x60

  //
  //Now! Enable the decode of IO range pointed by ACPI base address.
  //  (Note: ACPI power management function is also enabled)
  dData = 0x00000080;                  //bit 4 = 1 to enable ACPI

  WritePCIRegDWord(0x44,                        //ACPI_CNTL - ACPI control (LPC I/F D31:F0)
                   0,                           //bus #
                   (UINT8)((31 << 3) | 0),      //dev & func #
                   dData);

  // Halt the TCO timer
  IoWrite16(TCOBASE + 8, IoRead16(TCOBASE + 8) | 0x0800); //TCOBASE+8 = TCO1 control register
  IoWrite16(TCOBASE + 6, IoRead16(TCOBASE + 6) | 0x0002);
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:  SBPEIDBG_Initialize
//
// Description:  This eLink function is used to initialize the South Bridge
//               for PEI Debugger support
//
// Input:        DebugPort    Debug transport interface structure
//
// Output:       EFI_STATUS
//
// Notes:        Normally no PORTING REQUIRED
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS
SBPEIDBG_Initialize (
  IN OUT  PEI_DBG_PORT_INFO  *DebugPort
)
{
  //Program the TCO IO to avoid rebooting of the hardware 
  ProgramACPIBaseToDisableTCO();

  // Init 8259 Controller 
  PEI8259SetVectorBase (LEGACY_MODE_BASE_VECTOR_MASTER, LEGACY_MODE_BASE_VECTOR_SLAVE ); //testing

  // Set all 8259 Interrupts to edge triggered and disabled
  PEI8259WriteMask (0xffff , 0x0000);

  Enable_LPC_IO_Decode();

  EnableSerialIRQ();
  Program8254Timer0(0);
  return EFI_SUCCESS;
}

/** 
//----------------------------------------------------------------------------
  NO PORTING IS GENERALLY REQUIRED FOR THE ROUTINES BELOW.
//----------------------------------------------------------------------------
 **/ 


//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:  GetPCIAddrFormat
//
// Description:  Converts the provided bus, device, function and register
//               number of a PCI register into 32bit PCI access format
//
// Input:    RegNum    PCI Register number
//           BusNum    PCI Bus number
//           DevFunc    PCI Device and function number
//
// Output:   Converted 32 bit PCI register access value
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

UINT32  
GetPCIAddrFormat(
  IN UINT8  RegNum,
  IN UINT8  BusNum,
  IN UINT8  DevFunc
)
{
  UINT32  addr;

  addr = ((UINT32) (( (UINT16) BusNum ) << 8) +  DevFunc) << 8;
  addr += (RegNum & 0xfc);
  addr |= 0x80000000;
  return addr;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:  ReadPCIRegByte
//
// Description:  Reads a byte value from the PCI address space
//
// Input:    RegNum    PCI Register number
//           BusNum    PCI Bus number
//           DevFunc    PCI Device and function number
//
// Output:   Byte read
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

UINT8
ReadPCIRegByte(
  IN UINT8  RegNum,
  IN UINT8  BusNum,
  IN UINT8  DevFunc
)
{ 
  UINT32 PciAddr = GetPCIAddrFormat(RegNum,BusNum,DevFunc);

  IoWrite32(0xcf8, PciAddr);
  return IoRead8(0xcfc +(RegNum & 0x3));
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:  ReadPCIRegWord
//
// Description:  Reads a word value from the PCI address space
//
// Input:    RegNum    PCI Register number
//           BusNum    PCI Bus number
//           DevFunc    PCI Device and function number
//
// Output:   Word read
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

UINT16
ReadPCIRegWord(
  IN UINT8  RegNum,
  IN UINT8  BusNum,
  IN UINT8  DevFunc
)
{ 
  UINT32 PciAddr = GetPCIAddrFormat(RegNum,BusNum,DevFunc);

  IoWrite32(0xcf8, PciAddr);
  return IoRead16(0xcfc +(RegNum & 0x3));
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:  ReadPCIRegDWord
//
// Description:  Reads a double word value from the PCI address space
//
// Input:    RegNum    PCI Register number
//           BusNum    PCI Bus number
//           DevFunc    PCI Device and function number
//
// Output:   Double word read
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

UINT32
ReadPCIRegDWord(
  IN UINT8  RegNum,
  IN UINT8  BusNum,
  IN UINT8  DevFunc
)
{ 
  UINT32 PciAddr = GetPCIAddrFormat(RegNum,BusNum,DevFunc);

  IoWrite32(0xcf8, PciAddr);
  return IoRead32(0xcfc +(RegNum & 0x3));
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:  WritePCIRegByte
//
// Description:  Writes a byte value to the PCI address space
//
// Input:    RegNum    PCI Register number
//           BusNum    PCI Bus number
//           DevFunc    PCI Device and function number
//           Val      Value to write to the PCI address space
//
// Output:   None
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

VOID 
WritePCIRegByte(
  IN UINT8  RegNum,
  IN UINT8  BusNum,
  IN UINT8  DevFunc,
  IN UINT8  val
)
{ 
  UINT32 PciAddr = GetPCIAddrFormat(RegNum,BusNum,DevFunc);

  IoWrite32(0xcf8, PciAddr);
  IoWrite8(0xcfc +(RegNum & 0x3), val);
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:  OrWritePCIRegByte
//
// Description:  Or a byte value to the PCI address space
//
// Input:    RegNum    PCI Register number
//           BusNum    PCI Bus number
//           DevFunc   PCI Device and function number
//           Val       Value to write to the PCI address space
//
// Output:   None
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

VOID 
OrWritePCIRegByte(
  IN UINT8  RegNum,
  IN UINT8  BusNum,
  IN UINT8  DevFunc,
  IN UINT8  val
)
{ 
  UINT32 PciAddr = GetPCIAddrFormat(RegNum,BusNum,DevFunc);
  UINT8 Value;

  IoWrite32(0xcf8, PciAddr);
  Value=IoRead8(0xcfc +(RegNum & 0x3));
  Value|=val;
  IoWrite32(0xcf8, PciAddr);
  IoWrite8(0xcfc +(RegNum & 0x3), Value);
  return;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:  OrPCIRegByte
//
// Description:  Or a byte value to the PCI address space
//
// Input:    RegNum    PCI Register number
//           BusNum    PCI Bus number
//           DevFunc   PCI Device and function number
//           Val       Value to write to the PCI address space
//
// Output:   None
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

VOID 
OrPCIRegByte(
  IN UINT8  RegNum,
  IN UINT8  BusNum,
  IN UINT8  DevFunc,
  IN UINT8  val
)
{ 
  UINT32 PciAddr = GetPCIAddrFormat(RegNum,BusNum,DevFunc);
    UINT8 Value;


  IoWrite32(0xcf8, PciAddr);
  Value=IoRead8(0xcfc +(RegNum & 0x3));
  Value |=val;
  IoWrite32(0xcf8, PciAddr);
  IoWrite8(0xcfc +(RegNum & 0x3), Value);
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:  ANDPCIRegByte
//
// Description:  And a byte value to the PCI address space
//
// Input:    RegNum    PCI Register number
//           BusNum    PCI Bus number
//           DevFunc   PCI Device and function number
//           Val       Value to write to the PCI address space
//
// Output:   None
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID 
ANDPCIRegByte(
  IN UINT8  RegNum,
  IN UINT8  BusNum,
  IN UINT8  DevFunc,
  IN UINT8  val
)
{ 
  UINT32 PciAddr = GetPCIAddrFormat(RegNum,BusNum,DevFunc);
    UINT8 Value;


  IoWrite32(0xcf8, PciAddr);
  Value=IoRead8(0xcfc +(RegNum & 0x3));
  Value &=~val;
  IoWrite32(0xcf8, PciAddr);
  IoWrite8(0xcfc +(RegNum & 0x3), Value);
}


//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:  WritePCIRegWord
//
// Description:  Writes a word value to the PCI address space
//
// Input:    RegNum    PCI Register number
//           BusNum    PCI Bus number
//           DevFunc   PCI Device and function number
//           Val       Value to write to the PCI address space
//
// Output:   None
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

VOID 
WritePCIRegWord(
  IN UINT8  RegNum,
  IN UINT8  BusNum,
  IN UINT8  DevFunc,
  IN UINT16  val
)
{ 
  UINT32 PciAddr = GetPCIAddrFormat(RegNum,BusNum,DevFunc);

  IoWrite32(0xcf8, PciAddr);
  IoWrite16(0xcfc +(RegNum & 0x3), val);
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:  WritePCIRegDword
//
// Description:  Writes a double word value to the PCI address space
//
// Input:    RegNum    PCI Register number
//           BusNum    PCI Bus number
//           DevFunc   PCI Device and function number
//           Val       Value to write to the PCI address space
//
// Output:   None
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

VOID 
WritePCIRegDWord(
  IN UINT8  RegNum,
  IN UINT8  BusNum,
  IN UINT8  DevFunc,
  IN UINT32  val
)
{ 
  UINT32 PciAddr = GetPCIAddrFormat(RegNum,BusNum,DevFunc);

  IoWrite32(0xcf8, PciAddr);
  IoWrite32(0xcfc +(RegNum & 0x3), val);
}

//<AMI_PHDR_START>
//---------------------------------------------------------------------------
// Procedure:  OrPCIRegDWord
//
// Description:  Or a double word value to the PCI address space
//
// Input:    RegNum    PCI Register number
//           BusNum    PCI Bus number
//           DevFunc   PCI Device and function number
//           Val       Value to write to the PCI address space
//
// Output:    None
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

VOID 
OrPCIRegDWord(
  IN UINT8  RegNum,
  IN UINT8  BusNum,
  IN UINT8  DevFunc,
  IN UINT32  val
)
{ 
    UINT32  Value;
  UINT32 PciAddr = GetPCIAddrFormat(RegNum,BusNum,DevFunc);

  IoWrite32(0xcf8, PciAddr);
  Value=IoRead32(0xcfc +(RegNum & 0x3));
  Value|=val;
  IoWrite32(0xcf8, PciAddr);
  IoWrite32(0xcfc +(RegNum & 0x3), Value);

  return;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:  ANDPCIRegDWord
//
// Description:  AND a double word value to the PCI address space
//
// Input:    RegNum    PCI Register number
//           BusNum    PCI Bus number
//           DevFunc   PCI Device and function number
//           Val       Value to write to the PCI address space
//
// Output:    None
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

VOID 
ANDPCIRegDWord(
  IN UINT8  RegNum,
  IN UINT8  BusNum,
  IN UINT8  DevFunc,
  IN UINT32  val
)
{ 
    UINT32  Value;
  UINT32 PciAddr = GetPCIAddrFormat(RegNum,BusNum,DevFunc);

  IoWrite32(0xcf8, PciAddr);
  Value=IoRead32(0xcfc +(RegNum & 0x3));
  Value &=~val;
  IoWrite32(0xcf8, PciAddr);
  IoWrite32(0xcfc +(RegNum & 0x3), Value);

  return;
}


//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:  FindCapPtr
//
// Description: This function searches the PCI address space for the PCI
//              device specified for a particular capability ID and returns
//              the offset in the PCI address space if one found
//
// Input:    Bus      PCI Bus number
//           DevFunc  PCI Device and function number
//           CapId    Capability ID to look for
//
// Output:    Capability ID location if one found
//            Otherwise returns 0
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

UINT8 
FindCapPtr(
  IN UINT8  Bus,
  IN UINT8  DevFunc,
  IN UINT8  CapId
)
{
  UINT8  Value;
  UINT8  Reg;

  Value = ReadPCIRegByte(6, Bus, DevFunc);

  if (Value == 0xff) return 0;          //No device.
  if (!(Value & (1 << 4))) return 0;    // Check if capabilities list.
  
  Reg = 0x34;        // Register to First capabilities pointer
                      //if 0, then capabilities
  for(;;)
  {
    Value = ReadPCIRegByte(Reg, Bus, DevFunc);
    if (!Value) return 0;
    
    Reg = Value;    // ptr to CapID
    Value = ReadPCIRegByte(Reg, Bus, DevFunc);    //If capablity ID, return register that points to it.
    if (Value == CapId) return (UINT8)Reg; 

    ++Reg;      //equals to next capability pointer.
  }
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:  PEI8259WriteMask
//
// Description:  Writes PC 8259 interrupt Controller mask register
//
// Input:    Mask    Mask to write
//           EdgeLevel  Edge/level trigger to be programmed
//
// Output:    None
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

VOID 
PEI8259WriteMask (
  IN UINT16    Mask, 
  IN UINT16    EdgeLevel)
{
  IoWrite8 (LEGACY_8259_MASK_REGISTER_MASTER, (UINT8)Mask);
  IoWrite8 (LEGACY_8259_MASK_REGISTER_SLAVE,  (UINT8)(Mask >> 8));
  IoWrite8 (LEGACY_8259_EDGE_LEVEL_TRIGGERED_REGISTER_MASTER, (UINT8)EdgeLevel);
  IoWrite8 (LEGACY_8259_EDGE_LEVEL_TRIGGERED_REGISTER_SLAVE,  (UINT8)(EdgeLevel >> 8));
}


//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:  PEI8259SetVectorBase
//
// Description:  Set up the 8259 interrupt controller master and slave
//               base values
//
// Input:    MasterBase    Master base to be programmed
//           SlaveBase    Slave base to be programmed
//
// Output:    None
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

VOID 
PEI8259SetVectorBase (
  IN UINT8    MasterBase, 
  IN UINT8    SlaveBase
)
{
  UINT8      Mask;
  
  // Initialize Slave interrupt controller.
  Mask = IoRead8 (LEGACY_8259_MASK_REGISTER_SLAVE);
  IoWrite8 (LEGACY_8259_CONTROL_REGISTER_SLAVE, 0x11);
  IoWrite8 (LEGACY_8259_MASK_REGISTER_SLAVE,    SlaveBase);
  IoWrite8 (LEGACY_8259_MASK_REGISTER_SLAVE,    0x02); 
  IoWrite8 (LEGACY_8259_MASK_REGISTER_SLAVE,    0x01);
  IoWrite8 (LEGACY_8259_MASK_REGISTER_SLAVE,    Mask);

  // Initialize Master interrupt controller.
  Mask = IoRead8 (LEGACY_8259_MASK_REGISTER_MASTER);
  IoWrite8 (LEGACY_8259_CONTROL_REGISTER_MASTER, 0x11);
  IoWrite8 (LEGACY_8259_MASK_REGISTER_MASTER,    MasterBase);
  IoWrite8 (LEGACY_8259_MASK_REGISTER_MASTER,    0x04);
  IoWrite8 (LEGACY_8259_MASK_REGISTER_MASTER,    0x01); 
  IoWrite8 (LEGACY_8259_MASK_REGISTER_MASTER,    Mask); 

  IoWrite8 (LEGACY_8259_CONTROL_REGISTER_SLAVE,  LEGACY_8259_EOI);
  IoWrite8 (LEGACY_8259_CONTROL_REGISTER_MASTER, LEGACY_8259_EOI);
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:  Program8254Timer0
//
// Description:  Programs the 8254 Timer channel 0
//
// Input:    Count  Timer tick count
//
// Output:    None
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

VOID 
Program8254Timer0(
  IN UINT16    Count
)
{
  UINT8  LCntbyte,HCntbyte;

  LCntbyte = (UINT8)Count;
  HCntbyte = (UINT8)(Count >> 8);

  //Write the timer control port to select timer 0 and set to mode 3
  IoWrite8(TIMER_CONTROL_PORT, 0x36);

  //Write the Counter 0 with initial count value
  IoWrite8(TIMER0_COUNT_PORT, LCntbyte);
  IoWrite8(TIMER0_COUNT_PORT, HCntbyte);

  //Enable the IRQ0 interrupt for this timer 0 in USB Xport module
  //......

}

//**********************************************************************
//**********************************************************************
//**                                                                  **
//**        (C)Copyright 1985-2011, American Megatrends, Inc.         **
//**                                                                  **
//**                       All Rights Reserved.                       **
//**                                                                  **
//**         5555 Oakbrook Pkwy, Suite 200, Norcross, GA 30093        **
//**                                                                  **
//**                       Phone: (770)-246-8600                      **
//**                                                                  **
//**********************************************************************
//**********************************************************************
