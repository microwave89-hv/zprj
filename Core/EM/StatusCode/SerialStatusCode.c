//**********************************************************************
//**********************************************************************
//**                                                                  **
//**        (C)Copyright 1985-2009, American Megatrends, Inc.         **
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
// $Header: /Alaska/BIN/Modules/StatusCode/SerialStatusCode.c 13    1/22/13 4:56p Oleksiyy $
//
// $Revision: 13 $
//
// $Date: 1/22/13 4:56p $
//*****************************************************************************
// Revision History
// ----------------
// $Log: /Alaska/BIN/Modules/StatusCode/SerialStatusCode.c $
// 
// 13    1/22/13 4:56p Oleksiyy
// [TAG]	EIP112774
// [Category]	Bug Fix
// [Severity:]	Normal
// [Symptom:]	CPU Exception occurs when TRACE is used in SMM Handler
// [Root Cause]	pBS, used in Delay function, do not exist during  runtime.
// [Solution]	Delay replaced with dummy "for" cycle in SerialOutput
// function.
// [Files]	StatusCodeCommon.c
// 
// 
// 12    3/18/11 12:33p Oleksiyy
// [TAG]  		EIP54959 
// [Category]  	Bug Fix
// [Severity]  	Normal
// [Symptom]  	No debug output in projects with no SIO.
// [RootCause]  	Dependency from SIO added to sdl.
// [Solution]  	Dependency from SIO removed from SerialOutput eLink and
// moved directly to  SerialOutput function body.
// 
// [Files]  		SeriaStatusCode.c and StatusCode.sdl
// 
// 11    10/01/10 6:08p Oleksiyy
// Issue Number:  43888
// 
// Category:  Bug Fix
// 
// Symptom:  System hang endlesly if com port not working and Debug is ON
// 
// Severity:  Normal
// 
// Root Cause:  Infinite loop in SerialOutput.
// 
// Solution:  SEND_BYTE_DELEY and SEND_BYTE_ATEMPTS values is added. In
// SendByte SEND_BYTE_DELEY atempts will be made in loop until the serial
// port is ready for the next byte. 
// 
// Files:  SeriaStatusCode.c, StausCode.sdl
// 
// 10    5/03/10 1:17a Rameshr
// Issue:Need to handle different Base Hz values for SerialStatusCode,
// Terminal, and Legacy Serial Redirection.
// Solution: Moved Uart input clock into Core.sdl token and used in all
// the above modules.
// EIP: 37332
// 
// 9     11/13/09 4:30p Felixp
// Buffer overflow protection is added (calls to Sprintf replaced with
// Sprintf_s).
// 
// 8     7/09/09 5:18p Oleksiyy
// Files clean-up some headers added
//
// 7     3/05/09 1:41p Felixp
// Major update of the StatusCode module.
// See Label Comments and Release Notes in StatusCode.chm for more
// details.
//
// 5     8/24/06 3:33p Felixp
// Preliminary x64 support (work in progress)
//
// 4     5/04/06 12:01p Robert
// Updated to support core release 4.4.10
//
// 15    6/07/05 7:23p Felixp
// Moving toward generic Status Code module
//
// 13    1/20/05 11:31a Felixp
// StatusCodes.h renamed to AmiStatusCode.h
//
// 12    1/18/05 3:21p Felixp
// PrintDebugMessage renamed to Trace
//
// 11    11/15/04 10:35 Dougm
// Change the initialization of SIO
//
// 9     11/10/04 5:21p Felixp
// Serial output implementation changed to send '\r' before every '\n'
//
//*****************************************************************************
//<AMI_FHDR_START>
//
// Name: SerialStatusCode.c
//
// Description: Implementation of the serial port status code handler.
//
//<AMI_FHDR_END>
//*****************************************************************************
#include <PEI.h>
#include <StatusCodes.h>
#include <AMILIB.h>
#include <token.h>

//----------------------------------------------------------------------------
// Local constant definitions
#define CONFIG_PORT0        0x2E
#define INDEX_PORT0         0x2E
#define DATA_PORT0          0x2F
#define SEND_BYTE_DELEY     0x200
#define SEND_BYTE_ATEMPTS   0x10

#ifdef DEBUG_COM_PORT_ADDR
#define COM_BASE_ADDR DEBUG_COM_PORT_ADDR
#else
#define COM_BASE_ADDR       0x03f8
#endif
#define LSR_OFFSET          0x05
#define LCR_OFFSET          0x03
#define DIV_MSB             0x01
#define DIV_LSB             0

#define TRANSMIT_READY_BIT  0x020
#ifdef UART_INPUT_CLOCK
UINTN   UartInputClock=UART_INPUT_CLOCK;
#else
//
// Set the default value((24000000/13)MHz input clock) if the UART_INPUT_CLOCK SDL token is not present.
//
UINTN   UartInputClock=1843200;
#endif

#define BAUD_RATE_DIVISOR   115200

#define DATA_BITS           3   // 0 - 5 bits / 1 - 6 bits
// 2 - 7 bits / 3 - 8 bits
// RSP BUGBUG #define STOP_BIT          0   // 0 - 1 stop bit
#define STOP_BIT            1   // 0 - 1 stop bit
// 1 - mutiple bits depending on the databits
#define PARITY_BITS         0   // 0 - None / 1 enables parity
#define BREAK_BIT           0   // 0 - No break
#define DLAB_BIT            1   // 0 - Divisor Latch Disabled
// 1 - Divisor Latch Enabled

//----------------------------------------------------------------------------
// Module specific type definitions


//----------------------------------------------------------------------------
// Function Prototypes
EFI_STATUS SerialData(
    IN  EFI_STATUS_CODE_TYPE    Type,
    IN  EFI_STATUS_CODE_VALUE   Value,
    IN  EFI_STATUS_CODE_DATA    *Data,
    OUT UINT8                   *String
);
VOID Delay(EFI_PEI_SERVICES **PeiServices, UINT32 Microseconds);
//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure: SendByte
//
// Description: Writes the given byte to the serial port
//
// Input:
//      UINT8 Byte - a byte to write to the serial port
//
// Output: TRUE - Byte was sent, FALSE - serial port was not ready
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
BOOLEAN SendByte(UINT8 Byte)
{
    UINT8 Buffer8;
    UINT32 Cntr = 0;
    
    do
    {
        // Read the ready signal to see if the serial port is
        // ready for the next byte.
        Buffer8 = IoRead8(COM_BASE_ADDR + LSR_OFFSET);
        // Increment timeout counter.
        Cntr++;
        // Loop until the serial port is ready for the next byte.
    }
    while ( (Cntr < SEND_BYTE_DELEY) && 
            ((Buffer8 & TRANSMIT_READY_BIT) == FALSE) );
    if (Cntr < SEND_BYTE_DELEY){
       
        IoWrite8(COM_BASE_ADDR, Byte);
        return TRUE;
    } else return FALSE;

}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   SerialOutput
//
// Description: Writes the given string to the serial port byte by byte
//              using the function SendByte.
//
// Input:
//      IN EFI_PEI_SERVICES **PeiServices - pointer to the PEI Boot Services table
//      CHAR8 *String - String to be sent over the serial port
//
// Output: EFI_SUCCESS
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS SerialOutput(
    IN EFI_PEI_SERVICES **PeiServices,
    IN CHAR8 *String
)
{
#if SERIAL_STATUS_SUPPORT
    UINT8       *Buffer, i;
    UINT32       Delay;
    BOOLEAN     ByteSent;
    
    if (String == NULL) return EFI_SUCCESS;
    // first make data useable
    Buffer = String;
    
    // now send data one byte at a time until the string hits the end of string
    // or we hit the max number of characters
    while (*Buffer)
    {
        // replace "\n" with "\r\n"
        for (i = 0; i <= SEND_BYTE_ATEMPTS; i++){
            ByteSent = TRUE;

            if (*Buffer=='\n') ByteSent = SendByte('\r');
            
            if (ByteSent)  ByteSent = SendByte(*Buffer);
            
            if (ByteSent) break;
            else
                for (Delay = 0; Delay <= 100000; Delay++);
        }
        
        // move Data pointer to the next byte if previous was sent
        if (ByteSent) Buffer++;
        else return EFI_SUCCESS;
    }
#endif    
    return EFI_SUCCESS;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   SerialStatusInit
//
// Description:
//   The function programs the stop bits, data bits, and baud rate
//   of the com port and outputs the debug message "Status Code Available."
//   NOTE: This function does not assumes Super I/O has already been initialized.
//
// Input:
//      IN EFI_FFS_FILE_HEADER *FfsHeader
//      IN EFI_PEI_SERVICES **PeiServices - pointer to the PEI Boot Services table
// Output:
//      EFI_SUCCESS
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS SerialStatusInit(
    IN EFI_FFS_FILE_HEADER *FfsHeader,
    IN EFI_PEI_SERVICES **PeiServices
)
{
    UINT8   Data8;
    UINT16  Divisor;
    UINTN   Remainder;

    //
    // Compute the baud rate divisor.
    //
    Divisor = (UINT32) Div64 (UartInputClock,
                                ((UINT32)BAUD_RATE_DIVISOR * 16), 
                                &Remainder);
    if ( Remainder ) {
        Divisor += 1;
    }
    
    if ((Divisor == 0) || (Divisor & 0xffff0000)) {
        return EFI_INVALID_PARAMETER;
    }
    
    // Programm Serial port
    // Set Line Control Register (LCR)
    Data8 = DLAB_BIT << 7 | STOP_BIT << 2 | DATA_BITS;
    IoWrite8(COM_BASE_ADDR + LCR_OFFSET, Data8 );
    
    IoWrite8(COM_BASE_ADDR + DIV_LSB, Divisor & 0xFF);
    IoWrite8(COM_BASE_ADDR + DIV_MSB, Divisor >> 8);
    
    // Clear DLAB bit in LCR
    Data8 &= ~((UINT8)DLAB_BIT << 7);
    IoWrite8(COM_BASE_ADDR + LCR_OFFSET, Data8 );
#ifdef EFI_DEBUG
#ifndef PEI_STATUS_CODE
    SerialOutput(PeiServices, "DXE Status Code Available\n");
#else
    SerialOutput(PeiServices, "Status Code Available\n");
#endif
#endif
    return EFI_SUCCESS;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   SerialStatusInit
//
// Description:
//   The function sends "Checkpoint #" string to serial port
//
// Input:
//      IN EFI_PEI_SERVICES **PeiServices - pointer to the PEI Boot Services table
//      UINT8 Checkpoint - Checkpoint to send
// Output:
//      VOID
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID SerialCheckpoint(EFI_PEI_SERVICES **PeiServices, UINT8 Checkpoint)
{
    char s[20];
    Sprintf_s(s, sizeof(s), "Checkpoint %X\n",Checkpoint);
    SerialOutput(PeiServices, s);
}

//**********************************************************************
//**********************************************************************
//**                                                                  **
//**        (C)Copyright 1985-2009, American Megatrends, Inc.         **
//**                                                                  **
//**                       All Rights Reserved.                       **
//**                                                                  **
//**      5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093        **
//**                                                                  **
//**                       Phone: (770)-246-8600                      **
//**                                                                  **
//**********************************************************************
//**********************************************************************
