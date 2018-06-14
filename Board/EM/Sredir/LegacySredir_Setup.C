//**********************************************************************
//**********************************************************************
//**                                                                  **
//**        (C)Copyright 1985-2014, American Megatrends, Inc.         **
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
// $Header: /Alaska/SOURCE/Modules/Legacy Serial Redirection/LegacySredir_Setup.C 39    12/08/14 3:38a Anbuprakashp $
//
// $Revision: 39 $
//
// $Date: 12/08/14 3:38a $
//****************************************************************************
//****************************************************************************
// Revision History
// ----------------
// $Log: /Alaska/SOURCE/Modules/Legacy Serial Redirection/LegacySredir_Setup.C $
// 
// 39    12/08/14 3:38a Anbuprakashp
// [TAG]  		EIP192305
// [Category]  	Improvement
// [Description]  	Replacing SmmGetMemoryType usage in LegacySredir module
// with AmiBufferValidationLib
// [Files]  		LegacySredir.mak, LegacySmmSredir.c, LegacySredir_Setup.C
// 
// 38    6/16/14 7:53a Divyac
// [TAG]  		EIP172073
// [Category]  	Improvement
// [Description]  	Setup option for Legacy Serial Redirection.
// [Files]  		Terminal.sd, Terminal.uni, LegacySredir_Setup.c
// 
// 37    6/13/14 6:11a Divyac
// [TAG]  		EIP172101 
// [Category]  	Bug Fix
// [Severity]  	Minor
// [Symptom]  	Build Error in Legacy Serial Redirection Driver when
// COM_MMIO_WIDTH SDL token value is 2.
// [RootCause]  	semicolon was missing.
// [Solution]  	added semicolon.
// [Files]  		LegacySredir_Setup.C
// 
// 36    12/09/13 4:48a Divyac
// [TAG]  		EIP146051
// [Category]  	Improvement
// [Description]  	Refresh Key needs to be configured via SDL token for
// Legacy Serial Redirection.
// [Files]  		LegacySredir.c, LegacySredir_Setup.C, LegacySredir.h,
// Sredir.bin
// 
// 35    6/06/13 2:18a Rameshr
// [TAG]  		EIP122654
// [Category]  	Improvement
// [Description]  	Hardware Loopback device checking added.
// [Files]  		legacySredir_Setup.c, LegacySredir.sdl 
// 
// 34    1/07/13 11:48p Rameshr
// [TAG]  		EIP110859
// [Category]  	Bug Fix
// [Severity]  	Minor
// [Symptom]  	Legacy serial redirection always works on last COM port
// [RootCause]  	COM port selection continued for all the COM ports
// instead breaking when it's find the 1st COM port
// [Solution]  	When the 1st com port found for redirection returned from
// the function
// [Files]  		LegacySredir_Setup.c
// 
// 33    7/06/12 2:48a Rajeshms
// [TAG]  		EIP94504 
// [Category]  	Bug Fix
// [Severity]  	Normal
// [Symptom]  	screen color attributes are not transmitted to the serial
// terminal when the VT100+ terminal type is selected in DOS
// [RootCause]  	Terminal Type VT100+ was taken as VT100 in Legacy Serial
// Redirection.
// [Solution]  	VT100+ is taken as VT100+ type.
// [Files]  		LegacySredir_Setup.c
// 
// 32    3/29/12 11:53p Rajeshms
// [TAG]  		EIP84341
// [Category]  	Improvement
// [Description]  	Added Separate PCI_UART_INPUT_CLOCK token for setting
// the Clock for PCI Serial UART.
// [Files]  		Terminal.sdl, TerminalSetup.c, SerialIo.c, LegacySredir.c,
// LegacySredir_Setup.c
// 
// 31    2/27/12 6:04a Jittenkumarp
// [TAG]  		EIP81401
// [Category]  	New Feature
// [Description]  	Select Redirection After BIOS POST as BootLoader in
// serial redirection, the behaviour is made same as Core8. 
// [Files]  		LegacySredir.c, LegacySredir.mak, LegacySredir.sdl,
// LegacySredir_Setup.c, LegacySredir.h ,SerialBootCall.asm,
// SredirBootFail.asm,GRAPHREDIR.ASM, INT10REDIR.ASM, OR_MOD.EQU,
// SREDIR.ASM,LegacySredir.cif  
// 
// 30    12/28/11 10:54p Rajeshms
// [TAG]  		EIP65051
// [Category]  	Improvement
// [Description]  	Data passing between EFI to Legacy has been changed in
// Legacy console redirection as we are running out of registers to pass
// parameters from EFI to Legacy.
// [Files]  		LegacySredir.c, LegacySredir.h, LegacySredir_Setup.C,
// SREDIR.ASM, OR_MOD.ASM, OR_MOD.EQU
// 
// 29    12/12/11 6:30a Rajeshms
// [TAG]  		EIP71636
// [Category]  	New Feature
// [Description]  	Implement the AMI_SERIAL_DEVICE protocol
// [Files]  		AmiSerial.c, AmiSerial.sdl, AmiSerial.mak, AmiSerial.chm,
// AmiSerial.dxs, AmiSerial.cif, Terminal.c, SerialIo.c, TerminalSetup.c,
// InitTerminalStrings.c, TerminalSetupVar.h, Terminal.cif,
// TerminalAmiSerial.h, LegacySredir_Setup.c
// 
// 28    12/12/11 2:10a Jittenkumarp
// [TAG]  		EIP75982
// [Category]  	New Feature
// [Description]  	Redirection After BIOS POST item on the setup menu
// [Files]  		Terminal.sd, Terminal.uni, LegacySredir.c,
// LegacySredir_Setup.c
// 
// 27    11/09/11 11:54p Rajeshms
// [TAG]- EIP 63665
// [Category]-IMPROVEMENT
// [Description]- Install Linux(Legacy OS) through remote. Some Linux
// versions are forced to text mode to redirect and some are redirected in
// graphics mode itself. It might not work for all the Linux versions as
// the Linux kernel's behave differently.
// [Files]- Terminal.sdl, Terminal.uni, Terminal.sd, LegacySredir.c,
// LegacySredir.h, LegacySredir_Setup.c, GRAPHREDIR.ASM, INT10REDIR.ASM,
// OR_MOD.ASM, OR_MOD.EQU, SREDIR.ASM
// 
// 26    7/13/11 2:39a Rajeshms
// [TAG]- EIP 36444
// [Category]- New Feature
// [Description]- Add Setup option for Various Putty keyPad support in
// Legacy console redirection driver
// [Files]- LegacySredir.c, LegacySredir.h, LegacySredir_Setup.C,
// SREDIR.ASM, KEYREDIR.ASM, OR_MOD.EQU, SREDIR.MAK
// 
// 25    6/17/11 4:42a Rameshr
// [TAG] - EIP 47188
// [Category]- IMPROVEMENT
// [Description]- MMIO COM device access width SDL token support added 
// [Files] - legacysredir.c, LegacySredirSmm.c, LegacySredir_setup.c
// 
// 24    6/16/11 2:07a Rameshr
// [TAG] - EIP 54019
// [Category]- BUG FIX
// [Severity]- Minor
// [Symptom] - legacy console redirection doesn't work from virtual Serial
// Port.
// [RootCause]- Legacy console redirection always ignores the first Node
// in the device path
// [Solution] - For the ACPI node checking , first node of the devicepath
// also included.
// [Files] - Legacysredir_setup.c
// 
// 23    6/14/11 5:39a Rameshr
// [TAG]- EIP 58140
// [Category]- New Feature
// [Description]- Add Setup option for Vt-UTF8 combo key support in Legacy
// console redirection driver 
// [Files]- Sredir.asm, Legacysredir.c, Legacysredir.h,
// Legacysredir_setup.c
// 
// 22    1/19/11 4:25a Rameshr
// [TAG] - EIP 50230
// [Category]- BUG FIX
// [Severity]- Minor
// [Symptom] - SOL is not working correctly.
// [RootCause]- SOL device is visible even though SOL feature is disabled.
// [Solution] - Validated the TerminalDriver presence on SOL device and
// activated it for Legacy console redirection. 
// [Files] - Legacysre_setup.c
// 
// 21    10/28/10 5:22a Rameshr
// 
// 20    9/20/10 4:07a Rameshr
// [TAG]- EIP 44007
// [Category]-IMPROVEMENT
// [Description]- Invalid PCI COM device list added as Elink. These
// devices will not be used for Redirection.
// [Files]- LegacySredir.mak, LegacySredir.sdl, LegacySredir_Setup.c
// 
// 19    8/04/10 12:29a Rameshr
// COM port UID should be from 0 to 3 for SerialIo to work. This
// dependency removed as UID should be unique and it can be from 00 to
// 0xFF
// EIP 39843
// 
// 18    7/14/10 1:17a Rameshr
// 
// 16    6/30/10 5:23a Rameshr
// COM port Validation code added. Skipped the COM port if the port is not
// a valid one 
// EIP 39300
// 
// 15    6/11/10 5:20a Rameshr
// Resolved the programming Error.
// 
// 14    6/01/10 12:47a Rameshr
// Support for Baud Rate 38400 in Legacy Console Redirection Driver
// EIP 38854
// 
// 13    5/05/10 12:24a Rameshr
// Legacy Serial Redirection not working when serial port interrupt set to
// 5
// EIP 37785
// 
// 12    5/03/10 1:38a Rameshr
// Issue:Need to handle different Base Hz values for SerialStatusCode,
// Terminal, and Legacy Serial Redirection.
// Solution: Moved Uart input clock into Core.sdl token and used in all
// the above modules.
// EIP: 37332
// 
// 11    4/22/10 7:32a Rameshr
// Build Error resolved.
// 
// 10    4/13/10 4:14a Rameshr
// Recorder Mode support added
// EIP 36514
// Some of the MMIO COM port has non standard bits implemented. These bits
// are reset to 0 in Sredir.bin
// EIP 37123
// 
// 9     3/05/10 4:22a Rameshr
// MMIO COM device support added.
// EIP 33847
// 
// 8     10/23/09 10:46a Yul
// EIP 24167 and EIP 26405
// Serial redirection selection of 80X24 or 80X25 implemented based on 
// setup question instead of BUILD token
// 
// 7     9/21/09 3:37p Rameshr
// compile Error in legacy sredir when using VS 2008
// EIP 27263
// 
// 6     6/29/09 12:12p Rameshr
// Coding Standard and File header updated.
// 
// 5     4/21/09 12:16p Rameshr
// Updated the Legacy console redirection to get the Databits,Parity and
// Stop bits from the Terminal Driver Setup option
// EIP20874-Legacy serial redirection is using hra coded values for
// Databits as 8, Parity as None and Stop bit as 1
// 
// 4     12/04/08 12:56p Rameshraju
// Added code to get the Serial port base address and IRQ from Device path
// and other settings from Terminal Setup options
// 
// 3     9/08/08 5:30p Pats
// Modified to get port parameters from terminal setup.
// 
// 2     4/17/07 4:42a Rameshraju
// PCIserial support added
// 
//****************************************************************************

//<AMI_FHDR_START>
//****************************************************************************
//
// Name:        LegacySredir_Setup.C
//
// Description: This File is used to get the Terminal Setup values from EFI
//****************************************************************************
//<AMI_FHDR_END>

#pragma warning ( disable : 4214 )

#include "token.h"
#include "Protocol/LegacySredir.h"
#include <Setup.h>
#include <AmiDxeLib.h>          
#include <Protocol/AmiSio.h>
#include <Protocol/DevicePath.h>
#include <AcpiRes.h>
#include <Protocol/PciIo.h>
#include <PCI.h>
#include <Protocol/TerminalAmiSerial.h>

EFI_STATUS GetSetupValuesForLegacySredir(
        OUT AMI_COM_PARAMETERS *AmiComParameters
        );  

//*******************************************************
// EFI_PARITY_TYPE
//*******************************************************
typedef enum {
	DefaultParity,
	NoParity,
	EvenParity,
	OddParity,
	MarkParity,
	SpaceParity
} EFI_PARITY_TYPE;

//*******************************************************
// EFI_STOP_BITS_TYPE
//*******************************************************
typedef enum {
	DefaultStopBits,
	OneStopBit, 		// 1 stop bit
	OneFiveStopBits,	// 1.5 stop bits
	TwoStopBits 		// 2 stop bits
} EFI_STOP_BITS_TYPE;

#define STOPB   0x4                 //      Bit2: Number of Stop Bits
#define PAREN   0x8                 //      Bit3: Parity Enable
#define EVENPAR 0x10                //      Bit4: Even Parity Select
#define STICPAR 0x20                //      Bit5: Sticky Parity
#define SERIALDB 0x3                //      Bit0-1: Number of Serial 
                                    //                 Data Bits

#define SERIAL_REGISTER_THR 0       // WO   Transmit Holding Register
#define SERIAL_REGISTER_RBR 0       // RO   Receive Buffer Register

#define SERIAL_REGISTER_FCR 2       // WO   FIFO Cotrol Register
    #define TRFIFOE 0x1             //      Bit0: Transmit and Receive 
                                    //            FIFO Enable
    #define RESETRF 0x2             //      Bit1: Reset Reciever FIFO
    #define RESETTF 0x4             //      Bit2: Reset Transmistter FIFO
#define SERIAL_REGISTER_MCR 4       // R/W  Modem Control Register
                                    //            interrupts
    #define LME 0x10                //      Bit4: Loopback Mode Enable
#define SERIAL_REGISTER_LSR 5       // R/W  Line Status Register
    #define DR 0x1                  //      Bit0: Receiver Data Ready Status

#define SERIAL_REGISTER_MSR 6       // R/W  Modem Status Register
    #define CTS 0x10                //      Bit4: Clear To Send Status
    #define DSR 0x20                //      Bit5: Data Set Ready Status
    #define RI 0x40                 //      Bit6: Ring Indicator Status
    #define DCD 0x80                //      Bit7: Data Carrier Detect Status

#define SERIAL_REGISTER_SCR 7       // R/W  Scratch Pad Register



AMI_COM_PARAMETERS  gAmiComParameters;
BOOLEAN             IsFound = FALSE;
BOOLEAN             IsPciDevice;


#define TERMINAL_VAR_GUID \
{0x560bf58a, 0x1e0d, 0x4d7e, 0x95, 0x3f, 0x29, 0x80, 0xa2, 0x61, 0xe0, 0x31}
EFI_GUID gTerminalVarGuid   = TERMINAL_VAR_GUID;
UINT32 gTotalSioSerialPorts = TOTAL_SIO_SERIAL_PORTS;
#define SIO_SERIAL_PORTS_LOCATION_VAR_C_NAME    L"SioSerialPortsLocationVar"
#define PCI_SERIAL_PORTS_LOCATION_VAR_C_NAME    L"PciSerialPortsLocationVar"
#define SERIAL_PORTS_ENABLED_VAR_C_NAME         L"SerialPortsEnabledVar"

#if (TOTAL_PCI_SERIAL_PORTS > 0)
    typedef struct { 
        UINT8 Segment[ TOTAL_PCI_SERIAL_PORTS ]; 
        UINT8 Bus[ TOTAL_PCI_SERIAL_PORTS ]; 
        UINT8 Device[ TOTAL_PCI_SERIAL_PORTS ]; 
        UINT8 Function[ TOTAL_PCI_SERIAL_PORTS ]; 
        UINT8 AmiPciSerialPresent[ TOTAL_PCI_SERIAL_PORTS ];
        UINT8 Port[ TOTAL_PCI_SERIAL_PORTS ];
    } PCI_SERIAL_PORTS_LOCATION_VAR;
#endif
#if (TOTAL_SIO_SERIAL_PORTS > 0)
    typedef struct { 
        UINT8 PortUid[ TOTAL_SIO_SERIAL_PORTS ];
        UINT8 Valid[ TOTAL_SIO_SERIAL_PORTS ];
    } SIO_SERIAL_PORTS_LOCATION_VAR;
#endif

#if (TOTAL_SERIAL_PORTS > 0)
    typedef struct { 
        UINT8 PortsEnabled[ TOTAL_SERIAL_PORTS ];
    } SERIAL_PORTS_ENABLED_VAR;
#endif

UINT32 gComBaudRates[8] = {0, 0, 0, 9600, 19200, 38400, 57600, 115200};


#pragma pack(1)
typedef struct { 
    UINT16 VendorId; 
    UINT16 DeviceId; 
} INVALID_PCICOM;
#pragma pack()

INVALID_PCICOM InvalidPciCom[] = {INVALID_PCICOM_DEVICELIST
                                  {0xFFFF, 0xFFFF}
                                 };

//<AMI_PHDR_START>
//---------------------------------------------------------------------------
// Name:        InitilizeNonCommonSerialRegsiters
//
// Description: This Function is used to Initilize the Non Standard 
//              Serial Port Registers 
//
// Input:       AmiComParameters-Address of the COM port parameters Structure
//
// Output:      None 
//
// Notes:       Some of the MMIO com ports has non Standard bits in Registers
//              Those regsiters are all initilized on this function.
//---------------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS
InitilizeNonCommonSerialRegsiters(
    IN AMI_COM_PARAMETERS *AmiComParameters
)
{
    return EFI_SUCCESS;
}

//<AMI_PHDR_START>
//---------------------------------------------------------------------------
// Name:        SerialReadPort  
//
// Description: This Function is used to Read the
//
// Input:       IN  UINT32  BaseAddress, 
//              IN  UINT32  Offset,
//              IN  BOOLEAN MmioDevice
//  
// Output:      None 
//
//---------------------------------------------------------------------------
//<AMI_PHDR_END>

UINT8
SerialReadPort(
    IN  UINT32  BaseAddress, 
    IN  BOOLEAN MmioDevice,
    IN  UINT32  Offset
)
{
    UINT8   TempData8;

    if(MmioDevice) {
        //
        // Write into the Scratch Pad Reg
        //

#if COM_MMIO_WIDTH == 4
        {
        UINT32  TempData32;
        TempData32=*(UINT32*)(BaseAddress +(Offset*COM_MMIO_WIDTH));
        return (UINT8)(TempData32);
        }
#else
    #if COM_MMIO_WIDTH == 2
        {
        UINT16  TempData16;
        TempData16=*(UINT16*)(BaseAddress +(Offset*COM_MMIO_WIDTH));
        return (UINT8)(TempData16);
        }
    #else
        TempData8=*(UINT8*)(BaseAddress +(Offset*COM_MMIO_WIDTH));
        return TempData8;
    #endif
#endif 
    } 
    TempData8=IoRead8(BaseAddress + Offset);
    return TempData8;
}

//<AMI_PHDR_START>
//---------------------------------------------------------------------------
// Name:        SerialWritePort 
//
// Description: This Function is used to Read the
//
// Input:       IN  UINT32  BaseAddress, 
//              IN  UINT32  Offset,
//              IN  BOOLEAN MmioDevice
//              IN  UINT8   Data
//  
// Output:      Data
//
//---------------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS
SerialWritePort(
    IN  UINT32  BaseAddress, 
    IN  BOOLEAN MmioDevice,
    IN  UINT32  Offset,
    IN  UINT8   Data
)
{

    if(MmioDevice) {
        //
        // Write into the Scratch Pad Reg
        //

#if COM_MMIO_WIDTH == 4
        {
        UINT32  TempData32=(UINT32)Data;
        *(UINT32*)(BaseAddress +(Offset*COM_MMIO_WIDTH))=TempData32;
        }
#else
    #if COM_MMIO_WIDTH == 2
        {
         UINT16  TempData16=(UINT16)Data;
        *(UINT16*)(BaseAddress +(Offset*COM_MMIO_WIDTH))=(UINT16)TempData16;
        }
    #else
        *(UINT8*)(BaseAddress +(Offset*COM_MMIO_WIDTH))=(UINT8)Data;
    #endif
#endif 
    } else {

        IoWrite8(BaseAddress + Offset, Data);
    }

    return EFI_SUCCESS;
}


//**********************************************************************
//<AMI_PHDR_START>
//
// Procedure:   CheckForLoopbackDevice
//
// Description: Checks if a hardware loopback plug is attached and sets 
//              the result in Parameters->SerialDevicePresentOnPort. 
//
// Input:       IN EFI_SERIAL_IO_PROTOCOL *SerialIo
//
// Output: VOID
//
//<AMI_PHDR_END>
//**********************************************************************  
BOOLEAN
CheckForLoopbackDevice(
    IN  UINT32  BaseAddress, 
    IN  BOOLEAN MmioDevice
)
{
#if  CHECK_FOR_LOOPBACK_DEVICE
    UINT8   Byte;
    UINT8   Byte2;
    UINT8   FcrValue;


    FcrValue = SerialReadPort(BaseAddress, MmioDevice, SERIAL_REGISTER_FCR);

    //
    // Program the FCR
    //
    SerialWritePort(BaseAddress, MmioDevice, SERIAL_REGISTER_FCR, 
                            TRFIFOE|RESETRF|RESETTF);

    Byte = SerialReadPort(BaseAddress, MmioDevice, SERIAL_REGISTER_FCR);
    if(Byte == 0xff) {
        SerialWritePort(BaseAddress, MmioDevice, SERIAL_REGISTER_FCR, FcrValue); 
        return TRUE;        
    }
    
    //
    // Wait for 2ms is sufficient for the next byte
    //
    pBS->Stall(2000);

    //
    //check if RECV DATA AVAILABLE IS SET. If Available,Read the data till all data is read
    //

    do {
        Byte = SerialReadPort( BaseAddress, MmioDevice, SERIAL_REGISTER_LSR );
        if(Byte & DR) {
            Byte2 = SerialReadPort( BaseAddress, MmioDevice, SERIAL_REGISTER_RBR );
        }
    } while ((Byte & DR) == TRUE );

    //
    // Write into THR
    //
    SerialWritePort(BaseAddress, MmioDevice, SERIAL_REGISTER_THR,0x80); 

    //
    // Send BackSpace to clear the character(0x80) sent for testing
    // the presence of Loop Back Device.
    //
    SerialWritePort(BaseAddress, MmioDevice, SERIAL_REGISTER_THR,0x08);
    SerialWritePort(BaseAddress, MmioDevice, SERIAL_REGISTER_THR,0x20);
    SerialWritePort(BaseAddress, MmioDevice, SERIAL_REGISTER_THR,0x08);

    //
    // Wait for 5ms is sufficient for the next byte
    //
    pBS->Stall(50000);
   
    Byte = SerialReadPort( BaseAddress, MmioDevice, SERIAL_REGISTER_LSR );

    if(Byte & DR) {
        Byte2 = SerialReadPort( BaseAddress, MmioDevice, SERIAL_REGISTER_RBR );
        if(Byte2 == 0x80) {
            SerialWritePort(BaseAddress, MmioDevice, SERIAL_REGISTER_FCR, FcrValue); 
            return TRUE ;  
        }
    }

    // Check for hardware loopback plug...
    Byte2 = SerialReadPort(BaseAddress, MmioDevice, SERIAL_REGISTER_MCR);
    if (!(Byte2 & LME)) { // if hardware loopback not enabled...
        // Test for loopback plug and return error if detected
        // read MSR
        Byte = SerialReadPort(BaseAddress, MmioDevice, SERIAL_REGISTER_MSR); 
        Byte &= (CTS | DSR | DCD | RI); 
        // check these bits 
        if ((Byte == (CTS | DSR | DCD)) || (Byte == (CTS | DSR | DCD | RI))) {              
            // change MCR
            SerialWritePort(BaseAddress, MmioDevice, SERIAL_REGISTER_MCR, 0);
            // read MSR again 
            Byte = SerialReadPort(BaseAddress, MmioDevice, SERIAL_REGISTER_MSR);
            // restore MCR
            SerialWritePort(BaseAddress, MmioDevice, SERIAL_REGISTER_MCR, Byte2);
             // if change loops back...
            if ((Byte & 0xf0) == 0) {
                return TRUE;
            }
        }
    }

    return FALSE;
#else
    return FALSE;
#endif
    
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Name:        ValidateComPort
//
// Description: Validate the COM port using Scratch Pad Registers. 
//
// Input:       IN  UINT32   BaseAddress, 
//              IN  BOOLEAN  MmioDevice
//
// Output:      Comport number
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
BOOLEAN
ValidateComPort(
    IN  UINT32  BaseAddress, 
    IN  BOOLEAN MmioDevice
)
{
    UINT32  TempData32=0xAA;
    UINT8   TempData8=0xAA;

    if(MmioDevice) {
        //
        // Write into the Scratch Pad Reg
        //

#if COM_MMIO_WIDTH == 4
        *(UINT32*)(BaseAddress +(SERIAL_REGISTER_SCR*COM_MMIO_WIDTH))=TempData32;
        TempData32=*(UINT32*)(BaseAddress +(SERIAL_REGISTER_SCR*COM_MMIO_WIDTH));
#else
    #if COM_MMIO_WIDTH == 2
        *(UINT16*)(BaseAddress +(SERIAL_REGISTER_SCR*COM_MMIO_WIDTH))=(UINT16)TempData32;
        TempData32=*(UINT16*)(BaseAddress +(SERIAL_REGISTER_SCR*COM_MMIO_WIDTH));
    #else
        *(UINT8*)(BaseAddress +(SERIAL_REGISTER_SCR*COM_MMIO_WIDTH))=(UINT8)TempData32;
        TempData32=*(UINT8*)(BaseAddress +(SERIAL_REGISTER_SCR*COM_MMIO_WIDTH));
    #endif
#endif 
        //
        // Compare the read value Write Value, Both are same, Port is Valid
        //
        if((UINT8)TempData32 == 0xAA) {
            return TRUE;
        } else {
            return FALSE;
        }
    } else {
        //
        // Write into Scratch Pad ISA Com port 
        //
        IoWrite8(BaseAddress + SERIAL_REGISTER_SCR, TempData8);
        TempData8=IoRead8(BaseAddress + SERIAL_REGISTER_SCR);
        //
        // Compare the read value Write Value, Both are same, Port is Valid
        //
        if(TempData8 == 0xAA) {
            return TRUE;
        } else {
            return FALSE;
        }
    }
    return FALSE;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Name:        GetPciSerialComPortNumber   
//
// Description: This Function is used to get the Comport number to map Terminal Driver Setup values
//
// Input:       IN  UINT8   Device, 
//              IN  UINT8   Function
//
// Output:      Comport number
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
UINT32
GetPciSerialComPortNumber(
IN  UINT8   Device, 
IN  UINT8   Function,
IN  UINT8    PortNo
)
{
#if (TOTAL_PCI_SERIAL_PORTS > 0)
    UINT32      ComPort;
    UINT32      i = 0;
    UINTN       PciSerialPortsLocationVarSize = 
                                    sizeof(PCI_SERIAL_PORTS_LOCATION_VAR);
    UINT32      PciSerialPortsLocationVarAttributes=0;
    PCI_SERIAL_PORTS_LOCATION_VAR PciSerialPortsLocationVar; 
    EFI_STATUS  Status;

    UINTN SerialPortsEnabledVarSize = sizeof(SERIAL_PORTS_ENABLED_VAR); 
    UINT32 SerialPortsEnabledVarAttributes=0;
    SERIAL_PORTS_ENABLED_VAR SerialPortsEnabledVar; 

    Status = pRS->GetVariable(SERIAL_PORTS_ENABLED_VAR_C_NAME, 
                                &gTerminalVarGuid,
                                &SerialPortsEnabledVarAttributes, 
                                &SerialPortsEnabledVarSize, 
                                &SerialPortsEnabledVar);

    if(EFI_ERROR(Status)) {
        return 0xFF;
    }

    Status = pRS->GetVariable(PCI_SERIAL_PORTS_LOCATION_VAR_C_NAME, 
                                &gTerminalVarGuid, 
                                &PciSerialPortsLocationVarAttributes, 
                                &PciSerialPortsLocationVarSize, 
                                &PciSerialPortsLocationVar);

    if(EFI_ERROR(Status)) {
        return 0xFF;
    }

    ComPort = 0xFF; 

    for (i = 0; i < TOTAL_PCI_SERIAL_PORTS; i++) {
        if ((SerialPortsEnabledVar.PortsEnabled[gTotalSioSerialPorts+i]) && 
            (PciSerialPortsLocationVar.Device[i] == Device) && 
            (PciSerialPortsLocationVar.Function[i] == Function)) {
                if( PciSerialPortsLocationVar.AmiPciSerialPresent[i] ) {
                     if( PciSerialPortsLocationVar.Port[i] != PortNo ) continue;
                }
                ComPort = gTotalSioSerialPorts+i; 
                break;            
        }
    }   
    return ComPort;
#else 
    return 0xFF;
#endif
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Name:        SkipInvalidPciComDevice
//
// Description: Skip the Invalid PCI COM device that is provided in the 
//              InvalidPciComDeviceList 
//
// Input:       IN  UINT16 VendorId, 
//              IN  UINT16 DeviceId,
//
// Output:      TRUE - If the device has to be skipped
//              FALSE - Don't Skip the device
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
BOOLEAN
SkipInvalidPciComDevice(
    IN  UINT16 VendorId, 
    IN  UINT16 DeviceId 
)
{
    UINT8   i=0;

    while(  InvalidPciCom[i].VendorId != 0xFFFF && 
            InvalidPciCom[i].DeviceId != 0xFFFF ) {

        if( InvalidPciCom[i].VendorId == VendorId && 
            InvalidPciCom[i].DeviceId == DeviceId ) {

            return TRUE;
        }
        i++;
    }

    return FALSE;
}
    

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Name:        GetSetupValuesForLegacySredir   
//
// Description: This Function is used to get the Setup Values of Terminal Module
//
// Input:       Nothing
//
//
// Output:      AmiComParameters - SerialPort, Baudrate, Terminal Type, Flowcontrol
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS
GetSetupValuesForLegacySredir(
OUT AMI_COM_PARAMETERS *AmiComParameters)
{
#if (TOTAL_SERIAL_PORTS == 0)
    return EFI_NOT_FOUND;
#else
    EFI_STATUS          Status;
    EFI_GUID            SetupGuid = SETUP_GUID; 
    SETUP_DATA          SetupData; 
    EFI_DEVICE_PATH_PROTOCOL    *SerialDevicePath = NULL;
    EFI_DEVICE_PATH_PROTOCOL    *AmiSioDevicePath = NULL;
    EFI_DEVICE_PATH_PROTOCOL    *TruncatedSerialDevicePath = NULL;
    ACPI_HID_DEVICE_PATH        *AcpiPrevDPNodePtr = NULL;
    AMI_SIO_PROTOCOL    *AmiSioProtocol=NULL;
    EFI_HANDLE          *HandleBuffer, AmiSioProtocolHandle=0;
    UINTN               HandleCount, Index;
    ASLRF_S_HDR         *Header=NULL;
    T_ITEM_LIST         *ResourcesList=NULL;
    UINT32              SetupDataAttributes = 0;
    UINTN               SetupDataSize = sizeof(SETUP_DATA); 
    UINT8               TerminalTypes[4] = {1, 2, 2, 0};
    UINT8               DataParityStopBit=0;
    UINT8               TempSetupValue;
    EFI_PCI_IO_PROTOCOL     *PciIo;
    EFI_HANDLE              *PciHandleBuffer;
    UINTN                   PciHandleCount;
    UINT8                   RevisionId[4];
    UINT64                  Supports=0;
    ASLR_QWORD_ASD          *Resources=NULL;
    EFI_DEVICE_PATH_PROTOCOL    *tmpdp=NULL;
    EFI_HANDLE              TempHandle;
    EFI_PCI_IO_PROTOCOL     *RootPciIo=NULL;
    EFI_DEVICE_PATH_PROTOCOL *TruncatedDevPath = NULL;
    EFI_DEVICE_PATH_PROTOCOL *TempDevPath = NULL;
    UINT16                  CommandRegValue; 
    UINT8                   ResIndex;
    UINT16                  CommandReg=0; 
    UINTN                   Bus=0, Device=0, Function=0, SegNum=0;
    UINT8                   Port=0;
    UINT32                  ComPort=0;
    UINT16                  VendorId,DeviceId; 
#if (TOTAL_SIO_SERIAL_PORTS > 0)
    UINTN                   i;
    UINTN                   k;
    UINTN                   ComPortNo;
    UINTN                   SioSerialPortsLocationVarSize = 
                                    sizeof(SIO_SERIAL_PORTS_LOCATION_VAR);
    UINT32                  SioSerialPortsLocationVarAttributes=0;
    SIO_SERIAL_PORTS_LOCATION_VAR SioSerialPortsLocationVar;
#endif
    
#if (TOTAL_PCI_SERIAL_PORTS > 0)
    UINTN       PciSerialPortsLocationVarSize = 
                                    sizeof(PCI_SERIAL_PORTS_LOCATION_VAR);
    UINT32      PciSerialPortsLocationVarAttributes=0;
    PCI_SERIAL_PORTS_LOCATION_VAR PciSerialPortsLocationVar; 
    UINT8       PciComPortforLegacy;
#endif
    
    AMI_SERIAL_PROTOCOL      *AmiSerialProtocol=NULL;
    BOOLEAN                  Pci;
    BOOLEAN                  Mmio;
    UINT64                  BaseAddress;

    if (IsFound) {
        *AmiComParameters = gAmiComParameters;
        return EFI_SUCCESS;
    }

    Status = pRS->GetVariable(L"Setup", &SetupGuid, &SetupDataAttributes,
                                &SetupDataSize, &SetupData);

    if (EFI_ERROR (Status)) {
        return EFI_NOT_FOUND;
    }

    if(SetupData.ComPortforLegacy >= TOTAL_SIO_SERIAL_PORTS)
    {
#if (TOTAL_PCI_SERIAL_PORTS > 0)
        PciComPortforLegacy = SetupData.ComPortforLegacy-TOTAL_SIO_SERIAL_PORTS;
        Status = pRS->GetVariable(PCI_SERIAL_PORTS_LOCATION_VAR_C_NAME, 
                                &gTerminalVarGuid, 
                                &PciSerialPortsLocationVarAttributes, 
                                &PciSerialPortsLocationVarSize, 
                                &PciSerialPortsLocationVar);

        if (EFI_ERROR (Status)) {
            return EFI_NOT_FOUND;
        }
#endif
   
        //
        // Handle AMI_SERIAL_PROTOCOL.
        //
        Status = pBS->LocateHandleBuffer (
                                    ByProtocol,
                                    &gAmiSerialProtocolGuid,
                                    NULL,
                                    &PciHandleCount,
                                    &PciHandleBuffer);

        for (Index = 0; Index < PciHandleCount; Index++) {
            Status = pBS->HandleProtocol (
                                    PciHandleBuffer[Index],
                                    &gAmiSerialProtocolGuid,
                                    &AmiSerialProtocol);
        
             if (EFI_ERROR (Status)) {
                continue;
             }

             AmiSerialProtocol->GetPciLocation(AmiSerialProtocol,&Bus,&Device,&Function,&Port);

             ComPort=GetPciSerialComPortNumber((UINT8)Device, (UINT8)Function,Port);

             if(ComPort==0xFF) {
                continue;
             }
             if (!SetupData.ConsoleRedirectionEnable[ComPort]) {
                 continue;
             }
#if (TOTAL_PCI_SERIAL_PORTS > 0)
             if((!PciSerialPortsLocationVar.AmiPciSerialPresent[PciComPortforLegacy]) ||
                (!PciSerialPortsLocationVar.Bus[PciComPortforLegacy]==Bus) ||
                (!PciSerialPortsLocationVar.Device[PciComPortforLegacy]==Device) ||
                (!PciSerialPortsLocationVar.Function[PciComPortforLegacy]==Function) ||
                (!PciSerialPortsLocationVar.Port[PciComPortforLegacy]==Port)) {
                continue;
             }
#endif
             pBS->SetMem(&gAmiComParameters, (sizeof(AMI_COM_PARAMETERS)), 0);

             AmiSerialProtocol->CheckPciMmio(AmiSerialProtocol,&Pci,&Mmio);
             AmiSerialProtocol->GetBaseAddress(AmiSerialProtocol,&BaseAddress);
            
             if(Mmio) {
                 gAmiComParameters.MMIOBaseAddress= (UINT32)BaseAddress;
             } else {    
                gAmiComParameters.BaseAddress= (UINT16)BaseAddress;
             }

             if(Pci) {
                 IsPciDevice = TRUE;
             } else {
                 IsPciDevice = FALSE;
             }
        
             AmiSerialProtocol->GetSerialIRQ(AmiSerialProtocol,&(gAmiComParameters.SerialIRQ)); 

             //
             //Other settings from Termial Redirection driver
             //
             gAmiComParameters.Baudrate      = gComBaudRates[SetupData.BaudRate[ComPort]];
             gAmiComParameters.TerminalType  = TerminalTypes[SetupData.TerminalType[ComPort]];
             gAmiComParameters.FlowControl   = SetupData.FlowControl[ComPort];
             gAmiComParameters.LegacyOsResolution   = SetupData.LegacyOsResolution[ComPort];
             gAmiComParameters.RecorderMode   = SetupData.RecorderMode[ComPort];
             gAmiComParameters.VtUtf8   = SetupData.VtUtf8[ComPort];
             gAmiComParameters.PuttyKeyPad   = SetupData.PuttyFunctionKeyPad[ComPort];
#if  (INSTALL_LEGACY_OS_THROUGH_REMOTE == 1)
             gAmiComParameters.InstallLegacyOSthroughRemote  = SetupData.InstallLegacyOSthroughRemote[ComPort];
#endif
             gAmiComParameters.RedirectionAfterBiosPost = SetupData.RedirectionAfterBiosPost[ComPort] ;


             TempSetupValue=SetupData.Parity[ComPort];
                // Set parity bits.
             switch (TempSetupValue) {
                    case NoParity:
                            DataParityStopBit &= ~(PAREN | EVENPAR | STICPAR);
                            break;
                    case EvenParity:
                            DataParityStopBit |= (PAREN | EVENPAR);
                            DataParityStopBit &= ~STICPAR;
                            break;
                    case OddParity:
                            DataParityStopBit |= PAREN;
                            DataParityStopBit &= ~(EVENPAR | STICPAR);
                            break;
                    case SpaceParity:
                            DataParityStopBit |= (PAREN | EVENPAR | STICPAR);
                            break;
                    case MarkParity:
                            DataParityStopBit |= (PAREN | STICPAR);
                            DataParityStopBit &= ~EVENPAR;
                            break;
             }
    
             TempSetupValue=SetupData.StopBits[ComPort];

                // Set stop bits.
             switch (TempSetupValue) {
                    case OneStopBit :
                            DataParityStopBit &= ~STOPB;
                            break;
                     case OneFiveStopBits :
                     case TwoStopBits :
                            DataParityStopBit |= STOPB;
                            break;
             }

             TempSetupValue=SetupData.DataBits[ComPort];
   
                // Set data bits.
             DataParityStopBit &= ~SERIALDB;
             DataParityStopBit |= (UINT8)((TempSetupValue - 5) & 0x03);
             gAmiComParameters.DataParityStop= DataParityStopBit;

             IsFound = TRUE;
             *AmiComParameters = gAmiComParameters;
             return EFI_SUCCESS;
        }

        //
        // Handle PCI COM port.
        //
       
        //
        //Locate All devicepath handles
        //
        Status = pBS->LocateHandleBuffer (
                                    ByProtocol,
                                    &gEfiPciIoProtocolGuid,
                                    NULL,
                                    &PciHandleCount,
                                    &PciHandleBuffer);

        if (EFI_ERROR (Status)) {
            return Status;
        }

        for (Index = 0; Index < PciHandleCount; Index++) {
            Status = pBS->HandleProtocol (
                                    PciHandleBuffer[Index],
                                    &gEfiPciIoProtocolGuid,
                                    &PciIo); 


            PciIo->Pci.Read (PciIo,
                        EfiPciIoWidthUint32,
                        PCI_REV_ID_OFFSET,
                        1,
                        &RevisionId
                        );

            if ((RevisionId[3] == PCI_CL_COMM) &&
                ((RevisionId[2] == PCI_CL_COMM_CSL_SERIAL) || (RevisionId[2] == PCI_CL_COMM_CSL_OTHER))) {

                Status = PciIo->GetLocation(PciIo, &SegNum, &Bus,&Device,&Function);
                if (EFI_ERROR (Status)) {
                    continue;
                }
                
                PciIo->Pci.Read (PciIo,
                             EfiPciIoWidthUint16,
                             PCI_VID,
                             1,
                             &VendorId
                             );
                PciIo->Pci.Read (PciIo,
                             EfiPciIoWidthUint16,
                             PCI_DID,
                             1,
                             &DeviceId
                             );

                if(SkipInvalidPciComDevice(VendorId,DeviceId)) {
                    continue;
                }

                ComPort=GetPciSerialComPortNumber((UINT8)Device, (UINT8)Function, Port);
                
                if(ComPort==0xFF) {
                    continue;
                }
                if (!SetupData.ConsoleRedirectionEnable[ComPort]) {
                    continue;
                }
#if (TOTAL_PCI_SERIAL_PORTS > 0)

                if((!PciSerialPortsLocationVar.Segment[PciComPortforLegacy]==SegNum) ||
                   (!PciSerialPortsLocationVar.Bus[PciComPortforLegacy]==Bus) ||
                   (!PciSerialPortsLocationVar.Device[PciComPortforLegacy]==Device) ||
                   (!PciSerialPortsLocationVar.Function[PciComPortforLegacy]==Function)||
                   (!PciSerialPortsLocationVar.Port[PciComPortforLegacy]==Port)) {
                    continue;
                   }
#endif
                Supports = 1;

                pBS->SetMem(&gAmiComParameters, (sizeof(AMI_COM_PARAMETERS)), 0);

                for (ResIndex = 0; ResIndex < PCI_MAX_BAR_NO; ResIndex++) {
                    Status = PciIo->GetBarAttributes (
                                                PciIo,
                                                ResIndex,
                                                &Supports,
                                                &Resources
                                                );

                    //
                    //Find the Serial device Resource type. Based on that Enable the IO and Memory 
                    //
                    if (Resources->Type == ASLRV_SPC_TYPE_IO) {
                        gAmiComParameters.BaseAddress= (UINT16)Resources->_MIN;    
                        Status = PciIo->Pci.Read(PciIo, EfiPciIoWidthUint8, 0x3c, 1, &gAmiComParameters.SerialIRQ);
                        CommandReg = PCI_CMD_IO_SPACE;
                        pBS->FreePool(Resources);
                        break;
                    } else if(Resources->Type == ASLRV_SPC_TYPE_MEM) {
                        gAmiComParameters.MMIOBaseAddress= (UINT32)Resources->_MIN;    
                        Status = PciIo->Pci.Read(PciIo, EfiPciIoWidthUint8, 0x3c, 1, &gAmiComParameters.SerialIRQ);
                        CommandReg = PCI_CMD_MEMORY_SPACE;
                        pBS->FreePool(Resources);
                        break;
                    }
                }

                if(CommandReg != 0) {

                    PciIo->Pci.Read (PciIo,
                                EfiPciIoWidthUint16,
                                PCI_COMMAND_REGISTER_OFFSET,
                                1,
                                &CommandRegValue
                                );
                    CommandRegValue|=CommandReg;
                    PciIo->Pci.Write (PciIo,
                                EfiPciIoWidthUint16,
                                PCI_COMMAND_REGISTER_OFFSET,
                                1,
                                &CommandRegValue
                                );

                    Status = pBS->HandleProtocol (
                                    PciHandleBuffer[Index],
                                    &gEfiDevicePathProtocolGuid,
                                    &tmpdp); 


                    TruncatedDevPath=tmpdp;
                    do {
                        TruncatedDevPath = DPCut(TruncatedDevPath);
                        if(TruncatedDevPath == NULL ) {
                            break;
                        }

                        //
                        // Locate handle using device path
                        //
                        TempHandle= NULL;
                        TempDevPath=TruncatedDevPath;
                        Status = pBS->LocateDevicePath(
                                                &gEfiPciIoProtocolGuid,
                                                &TempDevPath,
                                                &TempHandle);

                        if(Status == EFI_SUCCESS) {

                            RootPciIo=NULL;
                            Status = pBS->HandleProtocol (
                                                    TempHandle,
                                                    &gEfiPciIoProtocolGuid,
                                                    &RootPciIo); // Get Device path protocol

                            if(Status == EFI_SUCCESS) {

                                RootPciIo->Pci.Read (RootPciIo,
                                                    EfiPciIoWidthUint16,
                                                    PCI_COMMAND_REGISTER_OFFSET,
                                                    1,
                                                    &CommandRegValue
                                                    );
                                CommandRegValue|=CommandReg;
                                RootPciIo->Pci.Write (RootPciIo,
                                                    EfiPciIoWidthUint16,
                                                    PCI_COMMAND_REGISTER_OFFSET,
                                                    1,
                                                    &CommandRegValue
                                                    );
                            }
                
                        }
                
                    }while(TruncatedDevPath != NULL);

                    //
                    // Check the Port Presence
                    //
                    if(gAmiComParameters.MMIOBaseAddress != 0) {
                        if(ValidateComPort(gAmiComParameters.MMIOBaseAddress, TRUE) == FALSE) {
                            continue;
                        }
                        if(CheckForLoopbackDevice(gAmiComParameters.MMIOBaseAddress, TRUE) == TRUE) {
                            continue;
                        }
                    } else {
                        if(ValidateComPort(gAmiComParameters.BaseAddress, FALSE) == FALSE) {
                            continue;
                        }
                        if(CheckForLoopbackDevice(gAmiComParameters.BaseAddress, FALSE) == TRUE) {
                            continue;
                        }
                    }

                    //
                    //Other settings from Termial Redirection driver
                    //
                    gAmiComParameters.Baudrate      = gComBaudRates[SetupData.BaudRate[ComPort]];
                    gAmiComParameters.TerminalType  = TerminalTypes[SetupData.TerminalType[ComPort]];
                    gAmiComParameters.FlowControl   = SetupData.FlowControl[ComPort];
                    gAmiComParameters.LegacyOsResolution   = SetupData.LegacyOsResolution[ComPort];
                    gAmiComParameters.RecorderMode   = SetupData.RecorderMode[ComPort];
                    gAmiComParameters.VtUtf8   = SetupData.VtUtf8[ComPort];
                    gAmiComParameters.PuttyKeyPad   = SetupData.PuttyFunctionKeyPad[ComPort];
#if  (INSTALL_LEGACY_OS_THROUGH_REMOTE == 1)
                    gAmiComParameters.InstallLegacyOSthroughRemote  = SetupData.InstallLegacyOSthroughRemote[ComPort];
#endif
                    gAmiComParameters.RedirectionAfterBiosPost = SetupData.RedirectionAfterBiosPost[ComPort] ;
                    TempSetupValue=SetupData.Parity[ComPort];
                    // Set parity bits.
                    switch (TempSetupValue) {
                        case NoParity:
                                DataParityStopBit &= ~(PAREN | EVENPAR | STICPAR);
                                break;
                        case EvenParity:
                                DataParityStopBit |= (PAREN | EVENPAR);
                                DataParityStopBit &= ~STICPAR;
                                break;
                        case OddParity:
                                DataParityStopBit |= PAREN;
                                DataParityStopBit &= ~(EVENPAR | STICPAR);
                                break;
                        case SpaceParity:
                                DataParityStopBit |= (PAREN | EVENPAR | STICPAR);
                                break;
                        case MarkParity:
                                DataParityStopBit |= (PAREN | STICPAR);
                                DataParityStopBit &= ~EVENPAR;
                                break;
                    }
    
                    TempSetupValue=SetupData.StopBits[ComPort];

                    // Set stop bits.
                    switch (TempSetupValue) {
                        case OneStopBit :
                                DataParityStopBit &= ~STOPB;
                                break;
                         case OneFiveStopBits :
                         case TwoStopBits :
                                DataParityStopBit |= STOPB;
                                break;
                    }

                    TempSetupValue=SetupData.DataBits[ComPort];

                    // Set data bits.
                    DataParityStopBit &= ~SERIALDB;
                    DataParityStopBit |= (UINT8)((TempSetupValue - 5) & 0x03);
                    gAmiComParameters.DataParityStop= DataParityStopBit;

                    IsFound = TRUE;
                    IsPciDevice = TRUE;
                    *AmiComParameters = gAmiComParameters;
                    return EFI_SUCCESS;
                }
            }
        }
    } else {
    
        //
        // Handle ISA COM port.
        //


        //
        //Locate All devicepath handles
        //
        Status = pBS->LocateHandleBuffer (
                                    ByProtocol,
                                    &gEfiDevicePathProtocolGuid,
                                    NULL,
                                    &HandleCount,
                                    &HandleBuffer);

        if (EFI_ERROR (Status)) {
            return Status;
        }
    
#if (TOTAL_SIO_SERIAL_PORTS > 0)
        Status = pRS->GetVariable(SIO_SERIAL_PORTS_LOCATION_VAR_C_NAME, 
                                &gTerminalVarGuid, 
                                &SioSerialPortsLocationVarAttributes,
                                &SioSerialPortsLocationVarSize, 
                                &SioSerialPortsLocationVar);

        if (EFI_ERROR (Status)) {
            return Status;
        }

        for (Index = 0; Index < HandleCount; Index++) {
            Status = pBS->HandleProtocol (
                                    HandleBuffer[Index],
                                    &gEfiDevicePathProtocolGuid,
                                    &SerialDevicePath); // Get Device path protocol

        if (EFI_ERROR (Status) || (SerialDevicePath == NULL)) continue;

            TruncatedSerialDevicePath = SerialDevicePath;
            //
            //Check for the Serial Port device path
            //
            for (;!isEndNode(TruncatedSerialDevicePath);TruncatedSerialDevicePath = NEXT_NODE(TruncatedSerialDevicePath)) {
                AcpiPrevDPNodePtr = (ACPI_HID_DEVICE_PATH *)(TruncatedSerialDevicePath); //get ACPI device path
                if ((AcpiPrevDPNodePtr->Header.Type == ACPI_DEVICE_PATH) 
                    && (AcpiPrevDPNodePtr->Header.SubType == ACPI_DP)
                    && (AcpiPrevDPNodePtr->HID == EISA_PNP_ID(0x501))) {

                    if(TOTAL_SIO_SERIAL_PORTS == 0) {
                        continue;
                    }

                    //
                    // Find the Port number ( Setup option offset)
                    //
                    for (k = 0; k < TOTAL_SIO_SERIAL_PORTS; k++) {
                        if ((SioSerialPortsLocationVar.PortUid[k] == (AcpiPrevDPNodePtr->UID) ) &&
                            (SioSerialPortsLocationVar.Valid[k] == 0xFF) &&
                            (k == SetupData.ComPortforLegacy)) {
                            ComPortNo = k; 
                            break;
                        }
                    }

                    if(k == TOTAL_SIO_SERIAL_PORTS) {
                        continue;
                    }
                    //
                    //Check Terminal redirection device status.
                    //
                    if (!SetupData.ConsoleRedirectionEnable[ComPortNo]) continue;

                    //
                    //Locate AmiSioProtocol form this handle to get current resource of this device.
                    //
                    AmiSioDevicePath = SerialDevicePath;        //Truncate End device path

                    Status = pBS->LocateDevicePath(&gEfiDevicePathProtocolGuid, 
                                               &AmiSioDevicePath, 
                                               &AmiSioProtocolHandle);

                    if (EFI_ERROR (Status)) continue;

                    Status = pBS->HandleProtocol (
                                                AmiSioProtocolHandle,
                                                &gEfiAmiSioProtocolGuid,
                                                &AmiSioProtocol);

                    if (EFI_ERROR (Status) || (AmiSioProtocol == NULL)) continue;

                    Status = AmiSioProtocol->CurrentRes(AmiSioProtocol, 
                                                    FALSE, 
                                                    &ResourcesList);
                    if (EFI_ERROR(Status)) continue;
                
                    if(ResourcesList){
                        for(i=0; i<ResourcesList->ItemCount; i++){
                            Header=(ASLRF_S_HDR*)ResourcesList->Items[i];
                            switch(Header->Name) {
                                case ASLV_RT_FixedIO: 
                                    gAmiComParameters.BaseAddress=((ASLR_FixedIO*)Header)->_BAS;
                                    break;
                                case ASLV_RT_IO: 
                                    gAmiComParameters.BaseAddress=((ASLR_IO*)Header)->_MIN;
                                    break;
                                case ASLV_RT_IRQ:
                                    gAmiComParameters.SerialIRQ = (UINT8)((ASLR_IRQNoFlags*)Header)->_INT;
                                    break; 
                            }
                        }
                    }
                    if(ValidateComPort(gAmiComParameters.BaseAddress, FALSE) == FALSE) {
                        continue;
                    }
                
                    if(CheckForLoopbackDevice(gAmiComParameters.BaseAddress, FALSE) == TRUE) {
                        continue;
                    }
                    //
                    //Other settings from Termial Redirection driver
                    //
                    gAmiComParameters.Baudrate      = gComBaudRates[SetupData.BaudRate[ComPortNo]];
                    gAmiComParameters.TerminalType  = TerminalTypes[SetupData.TerminalType[ComPortNo]];
                    gAmiComParameters.FlowControl   = SetupData.FlowControl[ComPortNo];
                    gAmiComParameters.LegacyOsResolution   = SetupData.LegacyOsResolution[ComPortNo];
                    gAmiComParameters.RecorderMode   = SetupData.RecorderMode[ComPortNo];
                    gAmiComParameters.VtUtf8   = SetupData.VtUtf8[ComPortNo];
                    gAmiComParameters.PuttyKeyPad   = SetupData.PuttyFunctionKeyPad[ComPortNo];
#if  (INSTALL_LEGACY_OS_THROUGH_REMOTE == 1)
                    gAmiComParameters.InstallLegacyOSthroughRemote  = SetupData.InstallLegacyOSthroughRemote[ComPortNo];
#endif
                    gAmiComParameters.RedirectionAfterBiosPost = SetupData.RedirectionAfterBiosPost[ComPortNo] ;
                    TempSetupValue=SetupData.Parity[ComPortNo];
                    // Set parity bits.
                    switch (TempSetupValue) {
                        case NoParity:
                            DataParityStopBit &= ~(PAREN | EVENPAR | STICPAR);
                            break;
                        case EvenParity:
                            DataParityStopBit |= (PAREN | EVENPAR);
                            DataParityStopBit &= ~STICPAR;
                            break;
                        case OddParity:
                            DataParityStopBit |= PAREN;
                            DataParityStopBit &= ~(EVENPAR | STICPAR);
                            break;
                        case SpaceParity:
                            DataParityStopBit |= (PAREN | EVENPAR | STICPAR);
                            break;
                        case MarkParity:
                            DataParityStopBit |= (PAREN | STICPAR);
                            DataParityStopBit &= ~EVENPAR;
                            break;
                    }
    
                    TempSetupValue=SetupData.StopBits[ComPortNo];

                    // Set stop bits.
                    switch (TempSetupValue) {
                        case OneStopBit :
                            DataParityStopBit &= ~STOPB;
                            break;
                        case OneFiveStopBits :
                        case TwoStopBits :
                            DataParityStopBit |= STOPB;
                            break;
                    }

                    TempSetupValue=SetupData.DataBits[ComPortNo];
   
                    // Set data bits.
                    DataParityStopBit &= ~SERIALDB;
                    DataParityStopBit |= (UINT8)((TempSetupValue - 5) & 0x03);
                    gAmiComParameters.DataParityStop= DataParityStopBit;

                    IsFound = TRUE;
                    IsPciDevice = FALSE;
                    *AmiComParameters = gAmiComParameters;
                      return EFI_SUCCESS;
                }
            }
        }
    }
#else
    return EFI_NOT_FOUND;
#endif
	return EFI_NOT_FOUND;
#endif
}

//
//TERMINAL TYPE:
//              db      0               ;ANSI
//              db      1               ;VT100
//              db      2               ;VT-UTF8
//FLOWCONTROLlIST:
//              db      0               ;none
//              db      1               ;hardware Flow control
//              db      2               ;software

//**********************************************************************
//**********************************************************************
//**                                                                  **
//**        (C)Copyright 1985-2014, American Megatrends, Inc.         **
//**                                                                  **
//**                       All Rights Reserved.                       **
//**                                                                  **
//**         5555 Oakbrook Pkwy, Suite 200, Norcross, GA 30093        **
//**                                                                  **
//**                       Phone: (770)-246-8600                      **
//**                                                                  **
//**********************************************************************
//**********************************************************************
