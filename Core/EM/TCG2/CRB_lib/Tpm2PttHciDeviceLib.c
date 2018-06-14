/** @file
  Implements Platform Trust Technology (FTPM) HCI Device Library.

@copyright
  Copyright (c) 2012 - 2013 Intel Corporation. All rights reserved
  This software and associated documentation (if any) is furnished
  under a license and may only be used or copied in accordance
  with the terms of the license. Except as permitted by such
  license, no part of this software or documentation may be
  reproduced, stored in a retrieval system, or transmitted in any
  form or by any means without the express written consent of
  Intel Corporation.

  This file contains an 'Intel Peripheral Driver' and uniquely
  identified as "Intel Reference Module" and is
  licensed for Intel CPUs and chipsets under the terms of your
  license agreement with Intel or your vendor.  This file may
  be modified by the user, subject to additional terms of the
  license agreement

**/
#include <efi.h>
#include <AmiLib.h>
#include "Tpm2PttHciRegs.h"
#include "Tpm2PttHciDeviceLib.h"
#include <Tpm20Includes\Tpm20.h>
//#include <EfiCommonLib.h>


#ifndef ASSERT
#define ASSERT(Condition) if(!(Condition)) { \
	EFI_DEADLOOP() \
	}
#endif

#define MmioAddress(BaseAddr, Register) \
    ( (UINTN)BaseAddr + (UINTN)(Register) )

#define Mmio32Ptr(BaseAddr, Register) \
    ( (volatile UINT32 *)MmioAddress(BaseAddr, Register) )

#define Mmio32(BaseAddr, Register) \
    *Mmio32Ptr(BaseAddr, Register)

#define MmioRead32(Addr) \
    Mmio32(Addr, 0)

#define MmioWrite32(Addr, Value) \
    (Mmio32(Addr, 0) = (UINT32)Value)

#define TPM_H2NS( x ) \
    (((UINT16)(x) << 8) | ((UINT16)(x) >> 8))
#define TPM_H2NL( x ) \
    (UINT32)((((UINT32)(x)) >> 24)    \
             | (((x) >> 8) & 0xff00)  \
             | ((x) << 24)            \
             | (((x) & 0xff00) << 8))

#define TPM_N2HS( x ) TPM_H2NS( x )
#define TPM_N2HL( x ) TPM_H2NL( x )

#pragma pack (push, 1)
typedef struct {
  TPM_ST tag;
  UINT32 paramSize;
  TPM_RC responseCode;
} TPM2_RESPONSE_HEADER;
#pragma pack (pop)

#define EFI_MAX_ADDRESS   0xFFFFFFFFFFFFFFFF


#ifdef INT_EFI_DEBUG
/**
  Prints command or response buffer for debugging purposes.

  @param[in] Buffer     Buffer to print.
  @param[in] BufferSize Buffer data length.
**/
VOID
EFIAPI
PttHciPrintBuffer(IN UINT8 *Buffer, IN UINT32 BufferSize)
{
  UINT32 Index;

  DEBUG ((EFI_D_INFO, "Buffer Address: 0x%08x, Size: 0x%08x, Value:\n", Buffer, BufferSize));
  for(Index = 0; Index < BufferSize; Index++){
    DEBUG ((EFI_D_INFO, "%02x ", *(Buffer + Index)));
   if((Index+1) % 16 == 0) DEBUG ((EFI_D_INFO, "\n"));
  }
  DEBUG ((EFI_D_INFO, "\n"));
}
#endif // EFI_DEBUG


VOID MicroSecDelay (
    UINTN   Delay                         
)
{
    UINTN   Counter, i;
    UINT32  Data32, PrevData;
    UINTN   Remainder;

    Counter = (UINTN)Div64 ((UINT64)(Delay * 10), 3, &Remainder);
    if (Remainder != 0) {
        Counter++;
    }
    //
    // Call WaitForTick for Counter + 1 ticks to try to guarantee Counter tick
    // periods, thus attempting to ensure Microseconds of stall time.
    //
    if (Counter != 0) {

        PrevData = IoRead32(PM_BASE_ADDRESS + 8);
        for (i = 0; i < Counter; ) {
            Data32 = IoRead32(PM_BASE_ADDRESS + 8);    
            if (Data32 < PrevData) {        // Reset if there is a overlap
                PrevData=Data32;
                continue;
            }
            i += (Data32 - PrevData);        
            PrevData = Data32;
        }
    }
    return;
}


/**
  Copy data from the MMIO region to system memory by using 32-bit access.

  Copy data from the MMIO region specified by starting address StartAddress
  to system memory specified by Buffer by using 32-bit access. The total
  number of byte to be copied is specified by Length. Buffer is returned.

  If StartAddress is not aligned on a 32-bit boundary, then ASSERT().

  If Length is greater than (MAX_ADDRESS - StartAddress + 1), then ASSERT().
  If Length is greater than (MAX_ADDRESS - Buffer + 1), then ASSERT().

  If Length is not aligned on a 32-bit boundary, then ASSERT().
  If Buffer is not aligned on a 32-bit boundary, then ASSERT().

  @param  StartAddress    The starting address for the MMIO region to be copied from.
  @param  Length          The size, in bytes, of Buffer.
  @param  Buffer          The pointer to a system memory buffer receiving the data read.

  @return Buffer
**/
UINT32 *
EFIAPI
MmioReadBuffer32 (
  IN  UINTN       StartAddress,
  IN  UINTN       Length,
  OUT UINT32      *Buffer
  )
{
  UINT32    *ReturnBuffer;

  ASSERT ((StartAddress & (sizeof (UINT32) - 1)) == 0);

  ASSERT ((Length - 1) <=  (EFI_MAX_ADDRESS - StartAddress));
  ASSERT ((Length - 1) <=  (EFI_MAX_ADDRESS - (UINTN) Buffer));

  ASSERT ((Length & (sizeof (UINT32) - 1)) == 0);
  ASSERT (((UINTN) Buffer & (sizeof (UINT32) - 1)) == 0);

  ReturnBuffer = Buffer;

  while (Length != 0) {
    *(Buffer++) = MmioRead32 (StartAddress);
    StartAddress += sizeof (UINT32);
    Length -= sizeof (UINT32);
  }

  return ReturnBuffer;
}

/**
  Copy data from system memory to the MMIO region by using 32-bit access.

  Copy data from system memory specified by Buffer to the MMIO region specified
  by starting address StartAddress by using 32-bit access. The total number
  of byte to be copied is specified by Length. Buffer is returned.

  If StartAddress is not aligned on a 32-bit boundary, then ASSERT().

  If Length is greater than (MAX_ADDRESS - StartAddress + 1), then ASSERT().
  If Length is greater than (MAX_ADDRESS -Buffer + 1), then ASSERT().

  If Length is not aligned on a 32-bit boundary, then ASSERT().

  If Buffer is not aligned on a 32-bit boundary, then ASSERT().

  @param  StartAddress    The starting address for the MMIO region to be copied to.
  @param  Length          The size, in bytes, of Buffer.
  @param  Buffer          The pointer to a system memory buffer containing the data to write.

  @return Buffer
**/
UINT32 *
EFIAPI
MmioWriteBuffer32 (
  IN  UINTN        StartAddress,
  IN  UINTN        Length,
  IN  CONST UINT32 *Buffer
  )
{
  UINT32    *ReturnBuffer;

  ASSERT ((StartAddress & (sizeof (UINT32) - 1)) == 0);

  ASSERT ((Length - 1) <=  (EFI_MAX_ADDRESS - StartAddress));
  ASSERT ((Length - 1) <=  (EFI_MAX_ADDRESS - (UINTN) Buffer));

  ASSERT ((Length & (sizeof (UINT32) - 1)) == 0);
  ASSERT (((UINTN) Buffer & (sizeof (UINT32) - 1)) == 0);

  ReturnBuffer = (UINT32 *) Buffer;

  while (Length != 0) {
    MmioWrite32 (StartAddress, *(Buffer++));

    StartAddress += sizeof (UINT32);
    Length -= sizeof (UINT32);
  }

  return ReturnBuffer;
}

/**
  Checks whether FTPM is enabled (FTPM_STS::FTPM_EN).

  @retval    TRUE    FTPM is enabled.
  @retval    FALSE   FTPM is disabled. All LT writes will be dropped.
                     All LT reads will be returned with read data value of all 0’s.
                     The bit can only be written once per ME power cycle.

**/
BOOLEAN
EFIAPI
PttHciPresenceCheck (
  VOID
  )
{
  EFI_STATUS Status;
#ifdef INT_EFI_DEBUG
  DEBUG ((EFI_D_INFO, "PTT: PttHciPresenceCheck start\n"));
 
  DEBUG ((EFI_D_INFO, "Check FTPM_STS - ENABLED bit (@ 0x%08x)\n", (R_PTT_HCI_BASE_ADDRESS + R_PTT_HCI_STS)));
#endif
  Status = PttHciWaitRegisterBits(
            (EFI_PHYSICAL_ADDRESS)(UINTN)(R_PTT_HCI_BASE_ADDRESS + R_PTT_HCI_STS),
            B_PTT_HCI_STS_ENABLED,
            V_PTT_HCI_IGNORE_BITS,
            PTT_HCI_TIMEOUT_A
            );
  if(Status == EFI_SUCCESS){
    return TRUE;
  }

  return FALSE;
}

/**
  Checks whether PTT is Ready

  @retval    TRUE    PTT is ready.
  @retval    FALSE   PTT is not ready

**/
BOOLEAN
EFIAPI
PttHciReadyCheck (
  VOID
  )
{
  UINT32 RegRead;

  RegRead = MmioRead32 ((UINTN) ( R_PTT_HCI_BASE_ADDRESS + R_PTT_HCI_STS ));
#ifdef INT_EFI_DEBUG
  DEBUG ((EFI_D_INFO, "Check PTT_STS - READY bit (@ 0x%08x)\n", RegRead));
#endif

  if(( B_PTT_HCI_STS_READY & RegRead) != 0){
    return TRUE;
  }

  return FALSE;
}

/**
  Checks whether TPM2_Startup command has been executed (FTPM_STS::STARTUP_EXEC).
  If command was executed, it should not be redundantly issued again.

  @retval    TRUE    Startup command executed already.
  @retval    FALSE   Startup command not executed yet.

**/
BOOLEAN
EFIAPI
PttHciStartupExecuted (
  VOID
  )
{
  EFI_STATUS Status;

#ifdef INT_EFI_DEBUG
  DEBUG ((EFI_D_INFO, "PTT: PttHciStartupExecuted start\n"));
  DEBUG ((EFI_D_INFO, "Check FTPM_STS - STARTUP_EXECECUTED bit (@ 0x%08x)\n", (R_PTT_HCI_BASE_ADDRESS + R_PTT_HCI_STS)));
#endif
  Status = PttHciWaitRegisterBits(
            (EFI_PHYSICAL_ADDRESS)(UINTN)(R_PTT_HCI_BASE_ADDRESS + R_PTT_HCI_STS),
            B_PTT_HCI_STS_STARTUP_EXEC,
            V_PTT_HCI_IGNORE_BITS,
            PTT_HCI_TIMEOUT_A
            );
  if(Status == EFI_SUCCESS){
    return TRUE;
  }

  return FALSE;
}

/**
  Sets FTPM_CMD and CA_START register to a defined value to indicate that a command is
  available for processing.
  Any host write to this register shall result in an interrupt to the ME firmware.

  @retval EFI_SUCCESS   Register successfully written.
  @retval TBD

**/
EFI_STATUS
EFIAPI
PttHciRequestCommandExec (
  VOID
  )
{
  EFI_STATUS Status = EFI_SUCCESS;

#ifdef INT_EFI_DEBUG
  DEBUG ((EFI_D_INFO, "PTT: PttHciRequestCommandExec start\n"));

  DEBUG ((EFI_D_INFO, "Command ready for processing - write 0x%08x to FTPM_CA_START register (@ 0x%08x)\n",
                      V_PTT_HCI_COMMAND_AVAILABLE_START,
                      (R_PTT_HCI_BASE_ADDRESS + R_PTT_HCI_CA_START)));
#endif
  MmioWrite32((UINTN)R_PTT_HCI_BASE_ADDRESS + R_PTT_HCI_CA_START, V_PTT_HCI_COMMAND_AVAILABLE_START);

  ///
  /// Write 0x1 to HCI CMD register to indicate that a command is available for processing
  ///
#ifdef INT_EFI_DEBUG
  DEBUG ((EFI_D_INFO, "Command ready for processing - write 0x%08x to FTPM_CMD register (@ 0x%08x)\n",
                      V_PTT_HCI_COMMAND_AVAILABLE_CMD,
                      (R_PTT_HCI_BASE_ADDRESS + R_PTT_HCI_CMD)));
#endif
  MmioWrite32((UINTN)R_PTT_HCI_BASE_ADDRESS + R_PTT_HCI_CMD, V_PTT_HCI_COMMAND_AVAILABLE_CMD);

  return Status;
}

/**
  Checks whether the value of a FTPM register satisfies the input BIT setting.

  @param[in]  Register     Address port of register to be checked.
  @param[in]  BitSet       Check these data bits are set.
  @param[in]  BitClear     Check these data bits are clear.
  @param[in]  TimeOut      The max wait time (unit MicroSecond) when checking register.

  @retval     EFI_SUCCESS  The register satisfies the check bit.
  @retval     EFI_TIMEOUT  The register can't run into the expected status in time.
**/
EFI_STATUS
EFIAPI
PttHciWaitRegisterBits(
  IN      EFI_PHYSICAL_ADDRESS    RegAddress,
  IN      UINT32                  BitSet,
  IN      UINT32                  BitClear,
  IN      UINT32                  TimeOut
  )
{
  UINT32 RegRead;
  UINT32 WaitTime;

#ifdef INT_EFI_DEBUG
  DEBUG ((EFI_D_INFO, "PTT: PttHciWaitRegisterBits start\n"));
#endif

  for (WaitTime = 0; WaitTime < TimeOut; WaitTime += PTT_HCI_POLLING_PERIOD){
    RegRead = MmioRead32 ((UINTN)RegAddress);
#ifdef INT_EFI_DEBUG
    DEBUG ((EFI_D_INFO, "RegRead: 0x%08x, BitSetMask: 0x%08x, BitClearMask: 0x%08x, WaitTime: %d (microsec)\n", RegRead, BitSet, BitClear, WaitTime));
#endif

    if (RegRead == 0xFFFFFFFF)
      continue;

    if ((RegRead & BitSet) == BitSet && (RegRead & BitClear) == 0) {
      return EFI_SUCCESS;
    }
//    MicroSecondDelay (PTT_HCI_POLLING_PERIOD); Override
   MicroSecDelay(PTT_HCI_POLLING_PERIOD); 
  }
  return EFI_TIMEOUT;
}

/**
  Sends command to FTPM for execution.

  @param[in] FtpmBuffer   Buffer for TPM command data.
  @param[in] DataLength   TPM command data length.

  @retval EFI_SUCCESS     Operation completed successfully.
  @retval EFI_TIMEOUT     The register can't run into the expected status in time.
**/
EFI_STATUS
EFIAPI
PttHciSend(
  IN     UINT8      *FtpmBuffer,
  IN     UINT32     DataLength
  )
{
  EFI_STATUS Status;

#ifdef INT_EFI_DEBUG
  DEBUG ((EFI_D_INFO, "PTT: PttHciSend start\n"));
#endif
  Status = PttHciWaitRegisterBits(
            (EFI_PHYSICAL_ADDRESS)(UINTN)(R_PTT_HCI_BASE_ADDRESS + R_PTT_HCI_CA_START),
            V_PTT_HCI_IGNORE_BITS,
            V_PTT_HCI_START_CLEAR,
            PTT_HCI_TIMEOUT_A
            );

  if(EFI_ERROR (Status)){
#ifdef INT_EFI_DEBUG
    DEBUG ((EFI_D_ERROR, "FTPM_CA_START register not clear - TPM2 command cannot be sent! EFI_ERROR = %r\n", Status));
#endif
    return EFI_NOT_READY;
  }
  ///
  /// Align command size to dword before writing to FTPM_CRB
  ///
  if(DataLength % 4 != 0){
#ifdef INT_EFI_DEBUG
    DEBUG ((EFI_D_INFO, "Alignment: DataLength change from %d ", DataLength));
#endif
    DataLength += (4 - (DataLength % 4));
#ifdef INT_EFI_DEBUG
    DEBUG ((EFI_D_INFO, "to %d\n", DataLength));
#endif
  }

  MmioWriteBuffer32((UINTN)(R_PTT_HCI_BASE_ADDRESS + R_PTT_HCI_CRB), (UINTN)DataLength, (UINT32*)FtpmBuffer);

  ///
  /// FTPM_CA_CMD - the physical address to which the TPM 2.0 driver will write the command to execute
  ///
  MmioWrite32((UINTN)(R_PTT_HCI_BASE_ADDRESS + R_PTT_HCI_CA_CMD), R_PTT_HCI_BASE_ADDRESS + R_PTT_HCI_CRB);
  MmioWrite32((UINTN)(R_PTT_HCI_BASE_ADDRESS + R_PTT_HCI_CA_CMD_SZ), S_PTT_HCI_CRB_LENGTH);

#ifdef INT_EFI_DEBUG
  DEBUG ((EFI_D_INFO, "FTPM_CA_CMD (@ 0x%08x) written, value = 0x%08x\n",
                       (R_PTT_HCI_BASE_ADDRESS + R_PTT_HCI_CA_CMD),
                       R_PTT_HCI_BASE_ADDRESS + R_PTT_HCI_CRB));
  DEBUG ((EFI_D_INFO, "FTPM_CA_CMD_SZ (@ 0x%08x) written, value = 0x%08x\n",
                       (R_PTT_HCI_BASE_ADDRESS + R_PTT_HCI_CA_CMD_SZ), DataLength));
#endif

  ///
  /// Set FTPM_CMD and FTPM_CA_START registers to indicate TPM command ready for execution
  ///
  Status = PttHciRequestCommandExec();
#ifdef INT_EFI_DEBUG
  if(Status == EFI_SUCCESS){
    DEBUG ((EFI_D_INFO, "FTPM_CMD register written - TPM2 command available for processing\n"));
  }
#endif

  return Status;
}

/**
  Receives response data of last command from FTPM.

  @param[out] FtpmBuffer        Buffer for response data.
  @param[out] RespSize          Response data length.

  @retval EFI_SUCCESS           Operation completed successfully.
  @retval EFI_TIMEOUT           The register can't run into the expected status in time.
  @retval EFI_DEVICE_ERROR      Unexpected device status.
  @retval EFI_BUFFER_TOO_SMALL  Response data is too long.
**/
EFI_STATUS
EFIAPI
PttHciReceive(
  OUT     UINT8     *FtpmBuffer,
  OUT     UINT32    *RespSize
  )
{
  EFI_STATUS Status;
  UINT16 Data16;
  UINT32 Data32;
#ifdef INT_EFI_DEBUG
  DEBUG ((EFI_D_INFO, "PTT: PttHciReceive start\n"));
#endif

  ///
  /// Wait for the command completion - poll FTPM_CA_START clear
  ///
#ifdef INT_EFI_DEBUG
  DEBUG ((EFI_D_INFO, "PTT: Check Start status (FTPM_CA_START)\n"));
#endif
  Status = PttHciWaitRegisterBits(
            (EFI_PHYSICAL_ADDRESS)(UINTN)(R_PTT_HCI_BASE_ADDRESS + R_PTT_HCI_CA_START),
            V_PTT_HCI_IGNORE_BITS,
            V_PTT_HCI_START_CLEAR,
            PTT_HCI_TIMEOUT_D
            );
  if(EFI_ERROR (Status)){
#ifdef INT_EFI_DEBUG
    DEBUG ((EFI_D_ERROR, "FTPM_CA_START register not clear - TPM2 response cannot be read! EFI_ERROR = %r\n", Status));
#endif
    goto Exit;
  }

  ///
  /// Check for error condition - FTPM_CA_ERROR
  ///
#ifdef INT_EFI_DEBUG
  DEBUG ((EFI_D_INFO, "PTT: Check Error status (FTPM_CA_ERROR)\n"));
#endif
  Status = PttHciWaitRegisterBits(
            (EFI_PHYSICAL_ADDRESS)(UINTN)(R_PTT_HCI_BASE_ADDRESS + R_PTT_HCI_CA_ERROR),
            V_PTT_HCI_IGNORE_BITS,
            V_PTT_HCI_ALL_BITS_CLEAR,
            PTT_HCI_TIMEOUT_A
            );
  if(EFI_ERROR (Status)){
#ifdef INT_EFI_DEBUG
    DEBUG ((EFI_D_ERROR, "FTPM_CA_ERROR register set - TPM2 response cannot be provided! EFI_ERROR = %r\n", Status));
#endif
    Status = EFI_DEVICE_ERROR;
    goto Exit;
  }

#ifdef INT_EFI_DEBUG
  DEBUG ((EFI_D_INFO, "FTPM_CA_START register clear - TPM2 command processing completed - ready to read\n"));
#endif

  ///
  /// Read the response data header
  ///
  MmioReadBuffer32((UINTN)R_PTT_HCI_BASE_ADDRESS + R_PTT_HCI_CRB, PTT_HCI_RESPONSE_HEADER_SIZE, (UINT32*)FtpmBuffer);

  ///
  /// Check the reponse data header (tag, parasize and returncode)
  ///
  MemCpy (&Data16, FtpmBuffer, sizeof (UINT16));

#ifdef INT_EFI_DEBUG
  DEBUG ((EFI_D_INFO, "TPM2_RESPONSE_HEADER.tag = 0x%04x\n", TPM_H2NS(Data16)));
#endif

  ///
  /// TPM Rev 2.0 Part 2 - 6.9 TPM_ST (Structure Tags)
  /// TPM_ST_RSP_COMMAND - Used in a response that has an error in the tag.
  ///
  if (TPM_H2NS(Data16) == TPM_ST_RSP_COMMAND) {
#ifdef INT_EFI_DEBUG
    DEBUG ((EFI_D_ERROR, "TPM2_RESPONSE_HEADER.tag = TPM_ST_RSP_COMMAND - Error in response!\n"));
#endif
    Status = EFI_DEVICE_ERROR;
    goto Exit;
  }

  MemCpy(&Data32, (FtpmBuffer + 2), sizeof(UINT32));
#ifdef INT_EFI_DEBUG
  DEBUG ((EFI_D_INFO, "TPM2_RESPONSE_HEADER.paramSize = 0x%08x\n", TPM_H2NL(Data32)));
#endif

  *RespSize = TPM_H2NL(Data32);

  if(*RespSize == sizeof(TPM2_RESPONSE_HEADER)) {
    Status = EFI_SUCCESS;
    goto Exit;
  }
  if(*RespSize < sizeof(TPM2_RESPONSE_HEADER)) {
    Status = EFI_DEVICE_ERROR;
    goto Exit;
  }
  if(*RespSize > S_PTT_HCI_CRB_LENGTH) {
    Status = EFI_BUFFER_TOO_SMALL;
    goto Exit;
  }

  ///
  /// Align command size to dword before writing to FTPM_CRB
  ///
  if(*RespSize % 4 != 0){
#ifdef INT_EFI_DEBUG
    DEBUG ((EFI_D_INFO, "Alignment: RespSize change from %d ", *RespSize));
#endif
    *RespSize += (4 - (*RespSize % 4));
#ifdef INT_EFI_DEBUG
    DEBUG ((EFI_D_INFO, "to %d\n", *RespSize));
#endif
  }

  ///
  /// Reading the entire response data
  ///
  MmioReadBuffer32((UINTN)R_PTT_HCI_BASE_ADDRESS + R_PTT_HCI_CRB, *RespSize, (UINT32*)FtpmBuffer);

  Exit:
    if(!EFI_ERROR(Status)){
      ///
      /// FTPM_CA_CMD - the physical address from which the TPM 2.0 driver will read command responses
      ///
      MmioWrite32((UINTN)(R_PTT_HCI_BASE_ADDRESS + R_PTT_HCI_CA_RSP), R_PTT_HCI_BASE_ADDRESS + R_PTT_HCI_CRB);
      MmioWrite32((UINTN)(R_PTT_HCI_BASE_ADDRESS + R_PTT_HCI_CA_RSP_SZ),S_PTT_HCI_CRB_LENGTH);
#ifdef INT_EFI_DEBUG
      DEBUG ((EFI_D_INFO, "FTPM_CA_RSP (@ 0x%08x) written, value = 0x%08x\n",
                          (R_PTT_HCI_BASE_ADDRESS + R_PTT_HCI_CA_RSP),
                          (R_PTT_HCI_BASE_ADDRESS + R_PTT_HCI_CRB)));
      DEBUG ((EFI_D_INFO, "FTPM_CA_RSP_SZ (@ 0x%08x) written, value = 0x%08x\n",
                          (R_PTT_HCI_BASE_ADDRESS + R_PTT_HCI_CA_RSP_SZ), *RespSize));
#endif
    }

    return Status;
}

/**
  Sends formatted command to FTPM for execution and returns formatted response data.

  @param[in]  InputBuffer       Buffer for the input data.
  @param[in]  InputBufferSize   Size of the input buffer.
  @param[out] ReturnBuffer      Buffer for the output data.
  @param[out] ReturnBufferSize  Size of the output buffer.

  @retval EFI_SUCCESS  Operation completed successfully.
  @retval EFI_TIMEOUT  The register can't run into the expected status in time.
**/
EFI_STATUS
EFIAPI
PttHciSubmitCommand(
  IN      UINT8     *InputBuffer,
  IN      UINT32     InputBufferSize,
  OUT     UINT8     *ReturnBuffer,
  OUT     UINT32    *ReturnBufferSize
  )
{
  EFI_STATUS Status;
#ifdef INT_EFI_DEBUG
  DEBUG ((EFI_D_INFO, "PTT: PttHciSubmitCommand start\n"));
#endif

  if(!PttHciReadyCheck()){
#ifdef INT_EFI_DEBUG
    DEBUG ((EFI_D_ERROR, "PTT device not ready. \n"));
#endif
    return EFI_NOT_READY;
  }

  if(InputBuffer == NULL || ReturnBuffer == NULL || InputBufferSize == 0){
#ifdef INT_EFI_DEBUG
    DEBUG ((EFI_D_ERROR, "Buffer == NULL or InputBufferSize == 0\n"));
#endif
    return EFI_INVALID_PARAMETER;
  }

#ifdef INT_EFI_DEBUG
  DEBUG ((EFI_D_INFO, "PTT: Command Buffer dump\n"));
#endif

  ///
  /// Send the command to TPM
  ///
  Status = PttHciSend(InputBuffer, InputBufferSize);
  if (EFI_ERROR (Status))  {
#ifdef INT_EFI_DEBUG
    DEBUG ((EFI_D_ERROR, "FTpmHciSend EFI_ERROR = %r\n", Status));
#endif
    return Status;
  }

  ///
  /// Receive the response data from TPM
  ///
  Status = PttHciReceive(ReturnBuffer, ReturnBufferSize);
  if (EFI_ERROR (Status)) {
#ifdef INT_EFI_DEBUG
    DEBUG ((EFI_D_ERROR, "FTpmHciReceive EFI_ERROR = %r\n", Status));
#endif
    return Status;
  }

#ifdef INT_EFI_DEBUG
  DEBUG ((EFI_D_INFO, "PTT: Response Buffer dump\n"));
#endif

  return Status;
}

