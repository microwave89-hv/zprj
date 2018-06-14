//**********************************************************************
//**********************************************************************
//**                                                                  **
//**        (C)Copyright 1985-2011, American Megatrends, Inc.         **
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
// $Header: /Alaska/BIN/Chipset/Intel/SouthBridge/LynxPoint/Intel Pch SB Chipset/SmBus/SmBusPorting.c 1     6/06/12 8:00a Victortu $
//
// $Revision: 1 $
//
// $Date: 6/06/12 8:00a $
//**********************************************************************
// Revision History
// ----------------
// $Log: /Alaska/BIN/Chipset/Intel/SouthBridge/LynxPoint/Intel Pch SB Chipset/SmBus/SmBusPorting.c $
// 
// 1     6/06/12 8:00a Victortu
// Implement EFI_PEI_SMBUS2_PPI Support.
// 
// 7     6/27/11 2:26p Artems
// Updated year in file header
// 
// 6     6/17/11 5:53p Artems
// EIP 53378: Replaced tabs with spaces, formatted to follow coding
// standard
// 
// 5     10/16/09 7:24p Artems
// Updated copyright header
// 
// 4     3/03/09 4:36p Artems
// EIP 19949 Added support for multiple SM Bus controllers that
// represented by different PCI devices
// 
// 3     1/29/09 4:20p Artems
// Change "Note" to "Notes" for HelpBuilder
// 
// 2     1/28/09 6:52p Artems
// Modified in accordance with coding standard
// 
// 1     1/09/09 6:53p Artems
// New implementation of SMBus EIP 16730
// 
// 1     3/18/07 5:23p Felixp
// 
//**********************************************************************

//<AMI_FHDR_START>
//----------------------------------------------------------------------
//
// Name:        SmBusPorting.c
//
// Description: SMBUS driver porting functions
//
//----------------------------------------------------------------------
//<AMI_FHDR_END>

#include "SmBusCommon.h"

//Porting Required - Put unique GUID for given SMBUS controller
#define SM_BUS_CONTROLLER_IDENTIFIER_GUID \
  {0x882f2546, 0xef1f, 0x4090, 0x9f, 0x9c, 0x93, 0x84, 0x5a, 0xd7, 0x84, 0x1c}

// Macro Definition(s)

// Type Definition(s)

// Function Prototype(s)

//---------------------------------------------------------------------------
// Variable and External Declaration(s)
//---------------------------------------------------------------------------
// Variable Declaration(s)

                                        // [EIP82310]>
UINT8 SmBusPlatformReservedAddress[] = {
  DIMM1_SMBUS_ADDRESS, 
  DIMM2_SMBUS_ADDRESS, 
  DIMM3_SMBUS_ADDRESS, 
  DIMM4_SMBUS_ADDRESS
};
                                        // <[EIP82310]

UINT8 SmBusPlatformReservedAddressSize = \
                        sizeof(SmBusPlatformReservedAddress) / sizeof(UINT8); 

// GUID Definition(s)

EFI_GUID SmBusIdentifierGuid = SM_BUS_CONTROLLER_IDENTIFIER_GUID;

// Protocol/PPI Definition(s)

// External Declaration(s)

// Function Definition(s)

//---------------------------------------------------------------------------

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:   BeforeSMBusTransfer
//
// Description: Set an enviornment for SMBus transfering.
//
// Input:       SmBusIoAddr16 - I/O base address of the SMBus Controller
//              Protocol8     - SMBus operation to be performed
//
// Output:      EFI_STATUS
//                  EFI_TIMEOUT - The caller can't obtain ownership of SMBus.
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS BeforeSMBusTransfer (
    IN UINT16           SmBusIoAddr16,
    IN UINT8            Protocol8 )
{
    UINT16               Timeout = 0xffff;

    // Waiting for other software's usage.
    while (IoRead8(SmBusIoAddr16 + SMB_IOREG_HST_STS) & HST_STS_INUSE_STS) {
        IoRead8(0xed); // I/O Delay
        Timeout--;
        if (Timeout == 0) return EFI_TIMEOUT; 
    }

    // BIOS obtains ownership of SMBus & Waiting for transmission completed.
    while (IoRead8(SmBusIoAddr16 + SMB_IOREG_HST_STS) & HST_STS_HOST_BUSY) {
        Timeout--;
        if (Timeout == 0) break; 
    }

    // Clears all statues
    IoWrite8(SmBusIoAddr16 + SMB_IOREG_HST_STS, HST_STS_ALL);

    if (Protocol8 == SMB_CMD_BLOCK) {
//#### SET_IO8(SmBusIoAddr16 + SMB_IOREG_AUX_CTL, AUX_CTL_E32B); // 0x0D
//#### // Reset Buffer Pointer
//#### IoRead8(SmBusIoAddr16 + SMB_IOREG_HST_CNT); // 0x02
    }

    return EFI_SUCCESS;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:   WriteCommand
//
// Description: This support function writes command field to SMBus Controller
//
// Input:       SmBusIoAddr16 - I/O base address of the SMBus Controller
//              Command8      - SMBus command to be performed
//
// Output:      None
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

VOID WriteCommand (
    IN UINT16           SmBusIoAddr16,
    IN UINT8            Command8 )
{
    IoWrite8(SmBusIoAddr16 + SMB_IOREG_HST_CMD, Command8);
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:   WriteSlAddr
//
// Description: This support function writes slave address to SMBus Controller
//
// Input:       SmBusIoAddr16 - I/O base address of the SMBus Controller
//              SlAddr8       - Address of the SMBus device
//
// Output:      None
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

VOID WriteSlAddr (
    IN UINT16           SmBusIoAddr16,
    IN UINT8            SlAddr8 )
{
    IoWrite8(SmBusIoAddr16 + SMB_IOREG_XMIT_SLVA, SlAddr8);
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:   WriteSMBusData
//
// Description: This support function writes data(s) to SMBus Controller for
//              SMBus write operation.
//
// Input:       SmBusIoAddr16 - I/O base address of the SMBus Controller
//              Protocol8     - SMBus operation to be performed
//              Length8       - Size of data buffer in bytes
//              *Data8        - Buffer to be written
//
// Output:      None
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

VOID WriteSMBusData (
    IN UINT16           SmBusIoAddr16,
    IN UINT8            Protocol8,
    IN UINT8            Length8,
    IN UINT8            *Data8 )
{
    UINT8               i;

    for (i = 0; i < Length8; i++) {
        if (Protocol8 == SMB_CMD_BLOCK) {
            IoWrite8(SmBusIoAddr16 + SMB_IOREG_HST_D0, Length8);
            IoWrite8(SmBusIoAddr16 + SMB_IOREG_HOST_BLOCK_DB, *Data8++);
            break;
        } else {
            IoWrite8(SmBusIoAddr16 + SMB_IOREG_HST_D0 + i, *Data8++);
        }
    }
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:   WaitForHostByteDoneStatus
//
// Description: This support function waits the Byte Done bit to be set for
//              SMBus Block operation.
//
// Input:       SmBusStsReg - 16 Bit I/O address for SMBus status register
//
// Output:      EFI_STATUS
//                  EFI_DEVICE_ERROR - An error on the SMBus device.
//                  EFI_SUCCESS      - The Byte Done bit had been set.
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS WaitForHostByteDoneStatus (
    IN UINT16           SmBusStsReg )
{
    UINT8           HostSts;

    while (1) {
        HostSts = IoRead8( SmBusStsReg );
        IoWrite8( IO_DELAY_PORT, HostSts );
        if ( HostSts & HST_STS_ERROR ) return EFI_DEVICE_ERROR;
        if ( HostSts & HST_STS_BDS ) return EFI_SUCCESS;
    }
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:   WriteSmBusBlockData
//
// Description: This support function writes to SMBus Controller
//
// Input:       SmBusIoAddr16 - I/O base address of the SMBus Controller
//              Length8       - Size of data buffer in bytes
//              *Data8        - Buffer to be written
//
// Output:      EFI_STATUS
//                  EFI_DEVICE_ERROR - An error on the SMBus device.
//                  EFI_SUCCESS      - Write SMBus Block data successfully.
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS WriteSmBusBlockData (
    IN UINT16           SmBusIoAddr16,
    IN UINT8            Length8,
    IN UINT8            *Data8 )
{
    EFI_STATUS          Status;
    UINT8               i;
    UINT16              StatusReg = SmBusIoAddr16 + SMB_IOREG_HST_STS;

    for (i = 1; i < Length8; i++) {
        if (WaitForHostByteDoneStatus(StatusReg)) return EFI_DEVICE_ERROR;
        IoWrite8(SmBusIoAddr16 + SMB_IOREG_HOST_BLOCK_DB, *Data8++);
        IoWrite8(StatusReg, HST_STS_BDS);
    }
    Status = WaitForHostByteDoneStatus(StatusReg);
    IoWrite8(StatusReg, HST_STS_BDS);
    return Status;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:   ReadSmBusData
//
// Description: This support function reads from SMBus Controller
//
// Input:       SmBusIoAddr16 - I/O base address of the SMBus Controller
//              Protocol8 - SMBus operation to be performed
//              Length8 - Size of data buffer in bytes
//              *Data8 - Buffer for the read data
//
// Output:      EFI_STATUS
//                  EFI_DEVICE_ERROR - An error on the SMBus device.
//                  EFI_SUCCESS      - Read SMBus data successfully.
//
// Modified:    *Data8 - The Pointer will store data(s) read from the SMBus
//                       device if EFI_SUCCESS is returned.
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS ReadSmBusData (
    IN UINT16           SmBusIoAddr16,
    IN UINT8            Protocol8,
    IN UINT8            Length8,
    OUT UINT8           *Data8 )
{
    UINT8               i;

    if (Protocol8 == SMB_CMD_BLOCK)
        Length8 = IoRead8(SmBusIoAddr16 + SMB_IOREG_HST_D0);

    for (i = 0; i < Length8; i++) {
        if (Protocol8 == SMB_CMD_BLOCK) {
            if (WaitForHostByteDoneStatus(SmBusIoAddr16 + SMB_IOREG_HST_STS))
                return EFI_DEVICE_ERROR;
            *Data8++ = IoRead8(SmBusIoAddr16 + SMB_IOREG_HOST_BLOCK_DB);
            if (i == (Length8 - 1)) {
                IoWrite8(SmBusIoAddr16 + SMB_IOREG_HST_CNT, \
                                           HST_CNT_LAST_BYTE | SMB_CMD_BLOCK);
            }
            IoWrite8(SmBusIoAddr16 + SMB_IOREG_HST_STS, HST_STS_BDS);
        } else {
            *Data8++ = IoRead8(SmBusIoAddr16 + SMB_IOREG_HST_D0 + i);
        }
    }
    return EFI_SUCCESS;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:   StartSmBusTransition
//
// Description: This support function starts SMBus operation.
//
// Input:       SmBusIoAddr16 - I/O base address of the SMBus Controller
//              Protocol8 - SMBus operation to be performed
//              PecCheck - TRUE will set PecCheck bit.
//
// Ouput:       None
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

VOID StartSmBusTransition (
    IN UINT16           SmBusIoAddr16,
    IN UINT8            Protocol8,
    IN BOOLEAN          PecCheck )
{
    UINT8               Buffer8;

    Buffer8 = Protocol8;
    if (PecCheck) {
        Buffer8 |= HST_CNT_PEC_EN;
        SET_IO8(SmBusIoAddr16 + SMB_IOREG_AUX_CTL, AUX_CTL_AAC); // 0x0D
    }
    IoWrite8(SmBusIoAddr16 + SMB_IOREG_HST_CNT, Buffer8);

    Buffer8 |= HST_CNT_START;

    if (Protocol8 == SMB_CMD_BLOCK)
        // Clear SECOND_TO_STS status before SMBus block read/write.
        WRITE_IO8_TCO(TCO_IOREG_STS2, 2); // 0x06

    IoWrite8(SmBusIoAddr16 + SMB_IOREG_HST_CNT, Buffer8);
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:   WaitForSmBusComplete
//
// Description: This support function waits for the operation complete
//
// Input:       SmBusIoAddr16 - I/O base address of the SMBus Controller
//
// Output:      EFI_STATUS
//                  EFI_DEVICE_ERROR - An error on the SMBus device.
//                  EFI_SUCCESS      - SMBus transaction is successfully
//                                     completed.
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS WaitForSmBusComplete (
    IN UINT16           SmBusIoAddr16,
    IN UINT8            Protocol8 )
{
    volatile UINT8      Buffer8;
    UINT8               StsChkBit;
    UINT16              TimeoutCounter;

    for (TimeoutCounter = 0; TimeoutCounter < 0x6000; TimeoutCounter++) {
        Buffer8 = IoRead8(IO_DELAY_PORT); // I/O Delay
        Buffer8 = IoRead8(SmBusIoAddr16 + SMB_IOREG_HST_STS);
        if (Buffer8 & (HST_STS_BDS | HST_STS_ERROR | HST_STS_INTR)) break;
    }

    StsChkBit = (Protocol8 == SMB_CMD_BLOCK) ? HST_STS_BDS : HST_STS_INTR;
    if (Buffer8 & StsChkBit)
        return (Buffer8 & HST_STS_ERROR) ? EFI_DEVICE_ERROR : EFI_SUCCESS;
    return EFI_DEVICE_ERROR;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:   ClearSmBusStatusAndDelay
//
// Description: This support function clears all statues of the SMBus
//              controller
//
// Input:       SmBusIoAddr16 - I/O base address of the SMBus Controller
//
// Ouptut:      None
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

VOID ClearSmBusStatusAndDelay (
    IN UINT16           SmBusIoAddr16 )
{
    UINT16              Timeout = 0x4000;
    volatile UINT8      HstSts;

    // Waiting for transmission completed.
    do {
        Timeout--;
        if (Timeout == 0) break; 
        HstSts = IoRead8(SmBusIoAddr16 + SMB_IOREG_HST_STS);
        if (HstSts & HST_STS_HOST_BUSY) continue;
    } while ((HstSts & (HST_STS_ERROR | HST_STS_INTR | HST_STS_BDS)) == 0);

    // Clears all statues.
    IoWrite8(SmBusIoAddr16 + SMB_IOREG_HST_STS, HST_STS_ALL);
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:   AfterSMBusTransfer
//
// Description: Restore the enviornment.
//
// Input:       SmBusIoAddr16 - I/O base address of the SMBus Controller
//              Protocol8     - SMBus operation to be performed
//
// Output:      None
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

VOID AfterSMBusTransfer (
    IN UINT16           SmBusIoAddr16,
    IN UINT8            Protocol8 )
{
//#### if (Protocol8 == SMB_CMD_BLOCK)
//####    RESET_IO8(SmBusIoAddr16 + SMB_IOREG_AUX_CTL, AUX_CTL_E32B); // 0x0D
    RESET_IO8(SmBusIoAddr16 + SMB_IOREG_AUX_CTL, AUX_CTL_AAC); // 0x0D

    // BIOS releases the ownership of SMBus.    
    IoWrite8(SmBusIoAddr16 + SMB_IOREG_HST_STS, HST_STS_INUSE_STS);

}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:   RwSmBusData
//
// Description: This support function reads/writes from/to SMBus Controller.
//
// Input:       SmBusIoAddr16 - I/O base address of the SMBus Controller
//              SlAddr8       - Address of the SMBus device
//              Command8      - SMBus command to be performed
//              Protocol8     - SMBus operation to be performed
//              PecCheck - TRUE will set PecCheck bit.
//              Length8       - Size of data buffer in bytes
//              Data8         - Buffer for the read/write data(s)
//
// Output:      Return Status based on errors that occurred while SMBus
//              transaction.
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS RwSmBusData (
    IN UINT16               SmBusIoAddr16,
    IN UINT8                SlAddr8,
    IN UINT8                Command8,
    IN UINT8                Protocol8,
    IN BOOLEAN              PecCheck,
    IN UINT8                Length8,
    IN OUT UINT8            *Data8 )
{
    EFI_STATUS          Status;
    BOOLEAN             IsWriteOperation = (!(SlAddr8 & XMIT_SLVA_RW));

    Status = BeforeSMBusTransfer(SmBusIoAddr16, Protocol8);
    if (Status != EFI_SUCCESS) return Status;
    WriteCommand(SmBusIoAddr16, Command8);
    WriteSlAddr(SmBusIoAddr16, SlAddr8);
    if (IsWriteOperation)
        WriteSMBusData(SmBusIoAddr16, Protocol8, Length8, Data8);
    StartSmBusTransition(SmBusIoAddr16, Protocol8, PecCheck);
    Status = WaitForSmBusComplete(SmBusIoAddr16, Protocol8);
    if (Status == EFI_SUCCESS) {
        if (IsWriteOperation) {
            if (Protocol8 == SMB_CMD_BLOCK)
                WriteSmBusBlockData(SmBusIoAddr16, Length8, &Data8[1]);
        } else {
            Status = ReadSmBusData(SmBusIoAddr16, Protocol8, Length8, Data8);
        }
    }

    ClearSmBusStatusAndDelay(SmBusIoAddr16);
    AfterSMBusTransfer(SmBusIoAddr16, Protocol8);

    return Status;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   Execute
//
// Description: This function sends commands via SMBUS interface
//
// Input:       IN SMBUS_PRIVATE *Context - SMBUS device private data
//              IN EFI_SMBUS_DEVICE_ADDRESS SlaveAddress - slave address value
//              IN EFI_SMBUS_DEVICE_COMMAND Command - command
//              IN EFI_SMBUS_OPERATION Operation - operation
//              IN BOOLEAN PecCheck - parity check flag
//              IN OUT UINTN *Length - pointer to size of data buffer
//              IN OUT VOID *Buffer - pointer to data buffer
//
// Output:      EFI_STATUS
//
// Notes:       Porting required
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS Execute (
    IN     SMBUS_PRIVATE            *Context,
    IN     EFI_SMBUS_DEVICE_ADDRESS SlaveAddress,
    IN     EFI_SMBUS_DEVICE_COMMAND Command,
    IN     EFI_SMBUS_OPERATION      Operation,
    IN     BOOLEAN                  PecCheck,
    IN OUT UINTN                    *Length,
    IN OUT VOID                     *Buffer
)
{
    // Porting required - implement internal Smbus protocols here
    EFI_STATUS      Status = EFI_UNSUPPORTED;
    UINT8           *bData = (UINT8 *)Buffer; 
    UINT8           bSlAddr = (UINT8)(SlaveAddress.SmbusDeviceAddress << 1);
    UINT8           bCommand = (UINT8)Command; 
    UINT8           bLength = (UINT8)(*Length);

    // Wait for SMBus transaction to finish if needed.
//#### while (IoRead8(Context->SmBusBase + SMB_IOREG_CNTL) & 3);

    if (bLength > 32) bLength = 32;
    if (bLength == 0) return EFI_INVALID_PARAMETER;

    switch (Operation) {
            case EfiSmbusQuickRead:
            case EfiSmbusQuickWrite:
                break;
            
            case EfiSmbusReceiveByte:
                break;

            case EfiSmbusSendByte:
                Status = RwSmBusData( Context->SmBusBase , \
                                      bSlAddr, \
                                      bCommand, \
                                      SMB_CMD_BYTE, \
                                      PecCheck, \
                                      1, \
                                      bData );
                break;
        
            case EfiSmbusReadByte:
                Status = RwSmBusData( Context->SmBusBase , \
                                      (bSlAddr | XMIT_SLVA_RW), \
                                      bCommand, \
                                      SMB_CMD_BYTE_DATA, \
                                      PecCheck, \
                                      1, \
                                      bData );
                break;
            case EfiSmbusReadWord:
                Status = RwSmBusData( Context->SmBusBase , \
                                      (bSlAddr | XMIT_SLVA_RW), \
                                      bCommand, \
                                      SMB_CMD_WORD_DATA, \
                                      PecCheck, \
                                      2, \
                                      bData );
                break;
    
            case EfiSmbusWriteByte:
                Status = RwSmBusData( Context->SmBusBase , \
                                      bSlAddr, \
                                      bCommand, \
                                      SMB_CMD_BYTE_DATA, \
                                      PecCheck, \
                                      1, \
                                      bData );
                break;
            case EfiSmbusWriteWord:
                Status = RwSmBusData( Context->SmBusBase , \
                                      bSlAddr, \
                                      bCommand, \
                                      SMB_CMD_WORD_DATA, \
                                      PecCheck, \
                                      2, \
                                      bData );
                break;  
    
            case EfiSmbusReadBlock:
                Status = RwSmBusData( Context->SmBusBase , \
                                      (bSlAddr | XMIT_SLVA_RW), \
                                      bCommand, \
                                      SMB_CMD_BLOCK, \
                                      PecCheck, \
                                      bLength, \
                                      bData );
                *Length = IoRead8( Context->SmBusBase + SMB_IOREG_HST_D0 );
                break;
    
            case EfiSmbusWriteBlock:
                Status = RwSmBusData( Context->SmBusBase , \
                                      bSlAddr, \
                                      bCommand, \
                                      SMB_CMD_BLOCK, \
                                      PecCheck, \
                                      bLength, \
                                      bData );
                *Length = IoRead8( Context->SmBusBase + SMB_IOREG_HST_D0 );
                break;
            
            case EfiSmbusProcessCall:
                break;
            
            case EfiSmbusBWBRProcessCall:
                break;
            
            default:
                break;
    }

    return Status;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   CheckNotify
//
// Description: This function checks if SMBUS host received any notifications
//
// Input:       IN SMBUS_PRIVATE *Context - SMBUS device private data
//              OUT EFI_SMBUS_DEVICE_ADDRESS *SlaveAddress - pointer to return address of notificaion device
//              OUT UINTN *Data - pointer to notification data
//
// Output:      EFI_STATUS
//
// Notes:       Porting required
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS CheckNotify (
    IN  SMBUS_PRIVATE            *Context,
    OUT EFI_SMBUS_DEVICE_ADDRESS *SlaveAddress,
    OUT UINTN                    *Data
)
{
//Porting required
    return EFI_UNSUPPORTED;
}

//**********************************************************************
//**********************************************************************
//**                                                                  **
//**        (C)Copyright 1985-2011, American Megatrends, Inc.         **
//**                                                                  **
//**                       All Rights Reserved.                       **
//**                                                                  **
//**      5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093        **
//**                                                                  **
//**                       Phone: (770)-246-8600                      **
//**                                                                  **
//**********************************************************************
//**********************************************************************
