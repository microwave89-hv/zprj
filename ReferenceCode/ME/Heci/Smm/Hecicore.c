/*++
  This file contains an 'Intel Peripheral Driver' and uniquely
  identified as "Intel Reference Module" and is
  licensed for Intel CPUs and chipsets under the terms of your
  license agreement with Intel or your vendor.  This file may
  be modified by the user, subject to additional terms of the
  license agreement
--*/
/*++

Copyright (c)  2008 - 2010 Intel Corporation. All rights reserved
This software and associated documentation (if any) is furnished
under a license and may only be used or copied in accordance
with the terms of the license. Except as permitted by such
license, no part of this software or documentation may be
reproduced, stored in a retrieval system, or transmitted in any
form or by any means without the express written consent of
Intel Corporation.

Module Name:

  Hecicore.c

Abstract:

  Heci driver core. For Dxe Phase, determines the HECI device and initializes it.

--*/
#include "HeciHpet.h"
#include "HeciCore.h"
#include "HeciRegs.h"
#include "MeState.h"

//
// //////////////////////////////////////////////////////////////////////////////////
// Globals used in Heci driver
////////////////////////////////////////////////////////////////////////////////////
//
UINT16        HECICtlrBDF;
static UINT32 HeciMBAR = 0;

//
// //////////////////////////////////////////////////////////////////////////////////
// Macro definition for function used in Heci driver
////////////////////////////////////////////////////////////////////////////////////
//
#define R_PCH_RCRB_FUNC_DIS2        0x3428

UINT32
MmIoReadDword (
  UINTN a
  )
/*++

Routine Description:

  The routing of MmIo Read Dword

Arguments:

  a - The address of Mmio
  
Returns:

  Return the valut of MmIo Read

--*/
{
  volatile HECI_HOST_CONTROL_REGISTER *HeciRegHCsrPtr;

  HeciRegHCsrPtr = (HECI_HOST_CONTROL_REGISTER *) a;
  return HeciRegHCsrPtr->ul;
}

VOID
MmIoWriteDword (
  UINTN  a,
  UINT32 b
  )
/*++

Routine Description:

  The routing of MmIo Write Dword

Arguments:

  a - The address of Mmio
  b - Value revised

Returns:

  None

--*/
{
  volatile HECI_HOST_CONTROL_REGISTER *HeciRegHCsrPtr;

  HeciRegHCsrPtr      = (HECI_HOST_CONTROL_REGISTER *) a;

  HeciRegHCsrPtr->ul  = b;
}

#define MMIOREADDWORD(a)      MmIoReadDword (a)
#define MMIOWRITEDWORD(a, b)  MmIoWriteDword (a, b)

//
// Extern for shared HECI data and protocols
//
extern HECI_INSTANCE_SMM  *mHeciContext;

//
// //////////////////////////////////////////////////////////////////////////////////
// Forward declaration
////////////////////////////////////////////////////////////////////////////////////
//
UINT8
FilledSlots (
  IN      UINT32                    ReadPointer,
  IN      UINT32                    WritePointer
  );

EFI_STATUS
OverflowCB (
  IN      UINT32                    ReadPointer,
  IN      UINT32                    WritePointer,
  IN      UINT32                    BufferDepth
  );

EFI_STATUS
WaitForMEReady (
  VOID
  );

//
// Heci driver function definitions
//
EFI_STATUS
InitializeHeciPrivate (
  VOID
  )
/*++

  Routine Description:
    Determines if the HECI device is present and, if present, initializes it for
    use by the BIOS.

  Arguments:
    None.

  Returns:
    EFI_STATUS

--*/
{
  HECI_HOST_CONTROL_REGISTER          HeciRegHCsr;
  VOLATILE HECI_HOST_CONTROL_REGISTER *HeciRegHCsrPtr;
  UINT32                              MeMode;
  EFI_STATUS                          Status;
  UINTN                               HeciPciAddressBase;

  Status = EFI_SUCCESS;

  SaveHpet ();

  do {
    //
    // Check for ME FPT Bad
    //
    if ((HeciPciRead32 (R_FWSTATE) & 0x0020) != 0) {
      Status = EFI_DEVICE_ERROR;
      break;
    }
    //
    // Check for ME error status
    //
    if ((HeciPciRead32 (R_FWSTATE) & 0xF000) != 0) {
      //
      // ME failed to start so no HECI
      //
      Status = EFI_DEVICE_ERROR;
      break;
    }
    //
    // Check ME Operation Mode to decice which HECI to use in SMM mode
    //
    Status = HeciGetMeMode (&MeMode);
    ASSERT_EFI_ERROR (Status);

    //
    // HECI MSG is unsupported if ME MODE is in Security Override
    //
    mHeciContext->MeMode = MeMode;
    if (mHeciContext->MeMode == ME_MODE_DEBUG) {
      Status = EFI_UNSUPPORTED;
      break;
    }

    HeciPciAddressBase = PCI_LIB_ADDRESS (
                          ME_BUS,
                          ME_DEVICE_NUMBER,
                          HECI_FUNCTION_NUMBER,
                          0
                          );
    mHeciContext->HeciDevSaveEnable = Heci2DevSaveEnable;
    mHeciContext->PciAddressBase    = HeciPciAddressBase;

    //
    // Store HECI vendor and device information away
    //
    mHeciContext->DeviceInfo = PciRead16 (HeciPciAddressBase + PCI_DEVICE_ID_OFFSET);

    //
    // Check for HECI-2 PCI device availability
    //
    if (mHeciContext->DeviceInfo == 0xFFFF) {
      Status = EFI_DEVICE_ERROR;
      break;
    }
    //
    // Store HECI revision ID
    //
    mHeciContext->RevisionInfo = PciRead8 (HeciPciAddressBase + PCI_REVISION_ID_OFFSET);

    //
    // Get HECI_MBAR and see if it is programmed
    // to a useable value
    //
    mHeciContext->HeciMBAR  = PciRead32 (HeciPciAddressBase + R_HECIMBAR) & 0xFFFFFFF0;
    HeciMBAR                = mHeciContext->HeciMBAR;

    //
    // Load temporary address for HECI_MBAR if one is not assigned
    //
    if (mHeciContext->HeciMBAR == 0) {
      //
      //      mHeciContext->HeciMBAR = mHeciContext->DefaultHeciBar;
      //      PciWrite32 (HeciPciAddressBase + R_HECIMBAR, mHeciContext->HeciMBAR);
      //      HeciMBAR = mHeciContext->HeciMBAR;
      //
      DEBUG ((EFI_D_ERROR, "Heci MMIO Bar not programmed in SMM phase\n"));
    }
    //
    // Enable HECI BME and MSE
    //
    PciOr8 (
      HeciPciAddressBase + PCI_COMMAND_OFFSET,
      EFI_PCI_COMMAND_MEMORY_SPACE | EFI_PCI_COMMAND_BUS_MASTER
      );

    //
    // Set HECI interrupt delivery mode.
    // HECI-2 using legacy/MSI interrupt
    //
    PciAnd8 (HeciPciAddressBase + R_HIDM, 0xFC);

    //
    // Need to do following on ME init:
    //
    //  1) wait for ME_CSR_HA reg ME_RDY bit set
    //
    if (WaitForMEReady () != EFI_SUCCESS) {
      Status = EFI_TIMEOUT;
      break;
    }
    //
    //  2) setup H_CSR reg as follows:
    //     a) Make sure H_RST is clear
    //     b) Set H_RDY
    //     c) Set H_IG
    //
    HeciRegHCsrPtr  = (VOID *) (UINTN) (mHeciContext->HeciMBAR + H_CSR);
    HeciRegHCsr.ul  = HeciRegHCsrPtr->ul;
    if (HeciRegHCsrPtr->r.H_RDY == 0) {
      HeciRegHCsr.r.H_RST = 0;
      HeciRegHCsr.r.H_RDY = 1;
      HeciRegHCsr.r.H_IG  = 1;
      HeciRegHCsrPtr->ul  = HeciRegHCsr.ul;
    }

  } while (EFI_ERROR (Status));

  RestoreHpet ();

  return Status;
}

EFI_STATUS
WaitForMEReady (
  VOID
  )
/*++

  Routine Description:
    Waits for the ME to report that it is ready for communication over the HECI
    interface.

  Arguments:
    None.

  Returns:
    EFI_STATUS

--*/
{
  UINT32                    TimerStart;
  UINT32                    TimerEnd;
  HECI_ME_CONTROL_REGISTER  HeciRegMeCsrHa;

  //
  //  Wait for ME ready
  //
  //
  // Check for ME ready status
  //
  StartTimer (&TimerStart, &TimerEnd, HECI_INIT_TIMEOUT);
  HeciRegMeCsrHa.ul = MMIOREADDWORD (HeciMBAR + ME_CSR_HA);
  while (HeciRegMeCsrHa.r.ME_RDY_HRA == 0) {
    //
    // If 5 second timeout has expired, return fail
    //
    if (Timeout (TimerStart, TimerEnd) != EFI_SUCCESS) {
      return EFI_TIMEOUT;
    }
    //
    // Perform IO delay
    //
    IoDelay (HECI_WAIT_DELAY);

    HeciRegMeCsrHa.ul = MMIOREADDWORD (HeciMBAR + ME_CSR_HA);
  }
  //
  // ME ready!!!
  //
  return EFI_SUCCESS;
}

BOOLEAN
CheckForHeciReset (
  VOID
  )
/*++

  Routine Description:
    Checks if HECI reset has occured.

  Arguments:
    None.

  Returns:
    TRUE - HECI reset occurred
    FALSE - No HECI reset occurred

--*/
{
  HECI_HOST_CONTROL_REGISTER  HeciRegHCsr;
  HECI_ME_CONTROL_REGISTER    HeciRegMeCsrHa;

  //
  // Init Host & ME CSR
  //
  HeciRegHCsr.ul    = MMIOREADDWORD (HeciMBAR + H_CSR);
  HeciRegMeCsrHa.ul = MMIOREADDWORD (HeciMBAR + ME_CSR_HA);

  if ((HeciRegMeCsrHa.r.ME_RDY_HRA == 0) || (HeciRegHCsr.r.H_RDY == 0)) {
    return TRUE;
  }

  return FALSE;
}

EFI_STATUS
HeciInitialize (
  VOID
  )
/*++

  Routine Description:
    Determines if the HECI device is present and, if present, initializes it for
    use by the BIOS.

  Arguments:
    None.

  Returns:
    EFI_STATUS

--*/
{
  HECI_HOST_CONTROL_REGISTER  HeciRegHCsr;

  //
  // Make sure that HECI device BAR is correct and device is enabled.
  //
  HeciMBAR = CheckAndFixHeciForAccess ();

  //
  // Need to do following on ME init:
  //
  //  1) wait for ME_CSR_HA reg ME_RDY bit set
  //
  if (WaitForMEReady () != EFI_SUCCESS) {
    return EFI_TIMEOUT;
  }
  //
  //  2) setup H_CSR reg as follows:
  //     a) Make sure H_RST is clear
  //     b) Set H_RDY
  //     c) Set H_IG
  //
  HeciRegHCsr.ul = MMIOREADDWORD (HeciMBAR + H_CSR);
  if (HeciRegHCsr.r.H_RDY == 0) {
    HeciRegHCsr.r.H_RST = 0;
    HeciRegHCsr.r.H_RDY = 1;
    HeciRegHCsr.r.H_IG  = 1;
    MMIOWRITEDWORD (HeciMBAR + H_CSR, HeciRegHCsr.ul);
  }

  return EFI_SUCCESS;
}

EFI_STATUS
EFIAPI
HeciReInitialize (
  VOID
  )
/*++

  Routine Description:
    Heci Re-initializes it for Host

  Arguments:
    None.

  Returns:
    EFI_STATUS

--*/
{
  HECI_HOST_CONTROL_REGISTER  HeciRegHCsr;
  EFI_STATUS                  Status;

  Status = EFI_SUCCESS;
  //
  // Need to do following on ME init:
  //
  //  1) wait for HOST_CSR_HA reg H_RDY bit set
  //
  //    if (WaitForHostReady() != EFI_SUCCESS) {
  //
  if (MeResetWait (HECI_INIT_TIMEOUT) != EFI_SUCCESS) {
    return EFI_TIMEOUT;
  }

  HeciRegHCsr.ul = MMIOREADDWORD (HeciMBAR + H_CSR);
  if (HeciRegHCsr.r.H_RDY == 0) {
    Status = ResetHeciInterface ();

  }

  return Status;
}

EFI_STATUS
EFIAPI
HeciReInitialize2 (
  VOID
  )
/*++

  Routine Description:
    Heci Re-initializes it for Me

  Arguments:
    None.

  Returns:
    EFI_STATUS

--*/
{
  HECI_ME_CONTROL_REGISTER  HeciRegMeCsrHa;
  EFI_STATUS                Status;
  UINT32                    TimerStart;
  UINT32                    TimerEnd;
  Status = EFI_SUCCESS;
  //
  // Need to do following on ME init:
  //
  //  1) wait for HOST_CSR_HA reg H_RDY bit set
  //
  //    if (WaitForHostReady() != EFI_SUCCESS) {
  //
  StartTimer (&TimerStart, &TimerEnd, HECI_INIT_TIMEOUT);
  HeciRegMeCsrHa.ul = MMIOREADDWORD (HeciMBAR + ME_CSR_HA);
  while (HeciRegMeCsrHa.r.ME_RDY_HRA == 1) {
    //
    // If 5 second timeout has expired, return fail
    //
    if (Timeout (TimerStart, TimerEnd) != EFI_SUCCESS) {
      return EFI_TIMEOUT;
    }

    IoDelay (HECI_WAIT_DELAY);

    HeciRegMeCsrHa.ul = MMIOREADDWORD (HeciMBAR + ME_CSR_HA);
  }

  if (WaitForMEReady () != EFI_SUCCESS) {
    return EFI_TIMEOUT;
  }

  return Status;
}

EFI_STATUS
HECIPacketRead (
  IN      UINT32                    Blocking,
  OUT     HECI_MESSAGE_HEADER       *MessageHeader,
  OUT     UINT32                    *MessageData,
  IN OUT  UINT32                    *Length
  )
/*++

  Routine Description:
    Function to pull one messsage packet off the HECI circular buffer.
    Corresponds to HECI HPS (part of) section 4.2.4


  Arguments:
    Blocking      - Used to determine if the read is BLOCKING or NON_BLOCKING.
    MessageHeader - Pointer to a buffer for the message header.
    MessageData   - Pointer to a buffer to recieve the message in.
    Length        - On input is the size of the callers buffer in bytes.  On
                    output this is the size of the packet in bytes.

  Returns:
    EFI_STATUS

--*/
{
  BOOLEAN                     GotMessage;
  UINT32                      TimerStart;
  UINT32                      TimerEnd;
  UINT32                      TimerStart1;
  UINT32                      TimerEnd1;
  UINT32                      i;
  UINT32                      LengthInDwords;
  HECI_ME_CONTROL_REGISTER    HeciRegMeCsrHa;
  HECI_HOST_CONTROL_REGISTER  HeciRegHCsr;

  GotMessage = FALSE;
  //
  // Initialize memory mapped register pointers
  //
  //  VOLATILE HECI_HOST_CONTROL_REGISTER *HeciRegHCsrPtr     = (VOID*)(mHeciContext->HeciMBAR + H_CSR);
  //  VOLATILE HECI_ME_CONTROL_REGISTER   *HeciRegMeCsrHaPtr  = (VOID*)(mHeciContext->HeciMBAR + ME_CSR_HA);
  //  VOLATILE UINT32                     *HeciRegMeCbrwPtr   = (VOID*)(mHeciContext->HeciMBAR + ME_CB_RW);
  //
  // clear Interrupt Status bit
  //
  HeciRegHCsr.ul      = MMIOREADDWORD (HeciMBAR + H_CSR);
  HeciRegHCsr.r.H_IS  = 1;

  //
  // test for circular buffer overflow
  //
  HeciRegMeCsrHa.ul = MMIOREADDWORD (HeciMBAR + ME_CSR_HA);
  if (OverflowCB (
        HeciRegMeCsrHa.r.ME_CBRP_HRA,
        HeciRegMeCsrHa.r.ME_CBWP_HRA,
        HeciRegMeCsrHa.r.ME_CBD_HRA
        ) != EFI_SUCCESS) {
    //
    // if we get here, the circular buffer is overflowed
    //
    *Length = 0;
    return EFI_DEVICE_ERROR;
  }
  //
  // If NON_BLOCKING, exit if the circular buffer is empty
  //
  HeciRegMeCsrHa.ul = MMIOREADDWORD (HeciMBAR + ME_CSR_HA);;
  if ((FilledSlots (HeciRegMeCsrHa.r.ME_CBRP_HRA, HeciRegMeCsrHa.r.ME_CBWP_HRA) == 0) && (Blocking == NON_BLOCKING)) {
    *Length = 0;
    return EFI_NO_RESPONSE;
  }
  //
  // Start timeout counter
  //
  StartTimer (&TimerStart, &TimerEnd, HECI_READ_TIMEOUT);

  //
  // loop until we get a message packet
  //
  while (!GotMessage) {
    //
    // If 1 second timeout has expired, return fail as we have not yet received a full message.
    //
    if (Timeout (TimerStart, TimerEnd) != EFI_SUCCESS) {
      *Length = 0;
      return EFI_TIMEOUT;
    }
    //
    // Read one message from HECI buffer and advance read pointer.  Make sure
    // that we do not pass the write pointer.
    //
    HeciRegMeCsrHa.ul = MMIOREADDWORD (HeciMBAR + ME_CSR_HA);;
    if (FilledSlots (HeciRegMeCsrHa.r.ME_CBRP_HRA, HeciRegMeCsrHa.r.ME_CBWP_HRA) > 0) {
      //
      // Eat the HECI Message header
      //
      MessageHeader->Data = MMIOREADDWORD (HeciMBAR + ME_CB_RW);

      //
      // Compute required message length in DWORDS
      //
      LengthInDwords = ((MessageHeader->Fields.Length + 3) / 4);

      //
      // Just return success if Length is 0
      //
      if (MessageHeader->Fields.Length == 0) {
        //
        // Set Interrupt Generate bit and return
        //
        MMIOREADDWORD (HeciMBAR + H_CSR);
        HeciRegHCsr.r.H_IG = 1;
        MMIOWRITEDWORD (HeciMBAR + H_CSR, HeciRegHCsr.ul);
        *Length = 0;
        return EFI_SUCCESS;
      }
      //
      // Make sure that the message does not overflow the circular buffer.
      //
      HeciRegMeCsrHa.ul = MMIOREADDWORD (HeciMBAR + ME_CSR_HA);
      if ((MessageHeader->Fields.Length + sizeof (HECI_MESSAGE_HEADER)) > (HeciRegMeCsrHa.r.ME_CBD_HRA * 4)) {
        *Length = 0;
        return EFI_DEVICE_ERROR;
      }
      //
      // Make sure that the callers buffer can hold the correct number of DWORDS
      //
      if ((MessageHeader->Fields.Length) <= *Length) {
        //
        // Start timeout counter for inner loop
        //
        StartTimer (&TimerStart1, &TimerEnd1, HECI_READ_TIMEOUT);

        //
        // Wait here until entire message is present in circular buffer
        //
        HeciRegMeCsrHa.ul = MMIOREADDWORD (HeciMBAR + ME_CSR_HA);
        while (LengthInDwords > FilledSlots (HeciRegMeCsrHa.r.ME_CBRP_HRA, HeciRegMeCsrHa.r.ME_CBWP_HRA)) {
          //
          // If 1 second timeout has expired, return fail as we have not yet received a full message
          //
          if (Timeout (TimerStart1, TimerEnd1) != EFI_SUCCESS) {
            *Length = 0;
            return EFI_TIMEOUT;
          }
          //
          // Wait before we read the register again
          //
          IoDelay (HECI_WAIT_DELAY);

          //
          // Read the register again
          //
          HeciRegMeCsrHa.ul = MMIOREADDWORD (HeciMBAR + ME_CSR_HA);
        }
        //
        // copy rest of message
        //
        for (i = 0; i < LengthInDwords; i++) {
          MessageData[i] = MMIOREADDWORD (HeciMBAR + ME_CB_RW);
        }
        //
        // Update status and length
        //
        GotMessage  = TRUE;
        *Length     = MessageHeader->Fields.Length;

      } else {
        //
        // Message packet is larger than caller's buffer
        //
        *Length = 0;
        return EFI_BUFFER_TOO_SMALL;
      }
    }
    //
    // Wait before we try to get a message again
    //
    IoDelay (HECI_WAIT_DELAY);
  }
  //
  // Read ME_CSR_HA.  If the ME_RDY bit is 0, then an ME reset occurred during the
  // transaction and the message should be discarded as bad data may have been retrieved
  // from the host's circular buffer
  //
  HeciRegMeCsrHa.ul = MMIOREADDWORD (HeciMBAR + ME_CSR_HA);
  if (HeciRegMeCsrHa.r.ME_RDY_HRA == 0) {
    *Length = 0;
    return EFI_DEVICE_ERROR;
  }
  //
  // Set Interrupt Generate bit
  //
  HeciRegHCsr.ul      = MMIOREADDWORD (HeciMBAR + H_CSR);
  HeciRegHCsr.r.H_IG  = 1;
  MMIOWRITEDWORD (HeciMBAR + H_CSR, HeciRegHCsr.ul);

  return EFI_SUCCESS;
}

EFI_STATUS
EFIAPI
HeciReceive (
  IN      UINT32  Blocking,
  IN OUT  UINT32  *MessageBody,
  IN OUT  UINT32  *Length
  )
/*++

  Routine Description:
    Reads a message from the ME across HECI.

  Arguments:
    Blocking    - Used to determine if the read is BLOCKING or NON_BLOCKING.
    MessageBody - Pointer to a buffer used to receive a message.
    Length      - Pointer to the length of the buffer on input and the length
                  of the message on return. (in bytes)

  Returns:
    EFI_STATUS

--*/
{
  HECI_MESSAGE_HEADER PacketHeader;
  UINT32              CurrentLength;
  UINT32              MessageComplete;
  EFI_STATUS          Status;
  UINT32              PacketBuffer;
  UINT32              timer_start;
  UINT32              timer_end;
  UINT32              MeDeviceState;
  BOOLEAN             QuitFlag;

  Status          = EFI_SUCCESS;
  CurrentLength   = 0;
  MessageComplete = 0;
  QuitFlag        = FALSE;

  SaveHpet ();

  do {
    if (mHeciContext->MeMode == ME_MODE_SECOVER) {
      Status = EFI_UNSUPPORTED;
      break;
    }
    //
    // Enable HECI and Save the Device State
    //
    mHeciContext->HeciDevSaveEnable (&MeDeviceState);

    //
    // Make sure that HECI device BAR is correct and device is enabled.
    //
    HeciMBAR = CheckAndFixHeciForAccess ();

    //
    // Make sure we do not have a HECI reset
    //
    if (CheckForHeciReset ()) {
      //
      // if HECI reset than try to re-init HECI
      //
      Status = HeciInitialize ();

      if (EFI_ERROR (Status)) {
        HeciDevRestore (MeDeviceState);
        Status = EFI_DEVICE_ERROR;
        break;
      }
    }
    //
    // Make sure that HECI is ready for communication.
    //
    if (WaitForMEReady () != EFI_SUCCESS) {
      HeciDevRestore (MeDeviceState);
      Status = EFI_TIMEOUT;
      break;
    }
    //
    // Set up timer for BIOS timeout.
    //
    StartTimer (&timer_start, &timer_end, HECI_READ_TIMEOUT);
    while ((CurrentLength < *Length) && (MessageComplete == 0)) {
      //
      // If 1 second timeout has expired, return fail as we have not yet received a full message
      //
      if (Timeout (timer_start, timer_end) != EFI_SUCCESS) {
        Status    = EFI_TIMEOUT;
        QuitFlag  = TRUE;
        break;
      }

      PacketBuffer = *Length - CurrentLength;
      Status = HECIPacketRead (
                Blocking,
                &PacketHeader,
                (UINT32 *) &MessageBody[CurrentLength / 4],
                &PacketBuffer
                );

      //
      // Check for error condition on read
      //
      if (EFI_ERROR (Status)) {
        *Length   = 0;
        QuitFlag  = TRUE;
        break;
      }
      //
      // Get completion status from the packet header
      //
      MessageComplete = PacketHeader.Fields.MessageComplete;

      //
      // Check for zero length messages
      //
      if (PacketBuffer == 0) {
        //
        // If we are not in the middle of a message, and we see Message Complete,
        // this is a valid zero-length message.
        //
        if ((CurrentLength == 0) && (MessageComplete == 1)) {
          *Length   = 0;
          QuitFlag  = TRUE;
          break;
        } else {
          //
          // We should not expect a zero-length message packet except as described above.
          //
          *Length   = 0;
          Status    = EFI_DEVICE_ERROR;
          QuitFlag  = TRUE;
          break;
        }
      }
      //
      // Track the length of what we have read so far
      //
      CurrentLength += PacketBuffer;

    }

    if (QuitFlag == TRUE) {
      break;
    }
    //
    // If we get here the message should be complete, if it is not
    // the caller's buffer was not large enough.
    //
    if (MessageComplete == 0) {
      *Length = 0;
      Status  = EFI_BUFFER_TOO_SMALL;
    }

    if (*Length != 0) {
      *Length = CurrentLength;
    }
    //
    // Restore HECI Device State
    //
    HeciDevRestore (MeDeviceState);

  } while (EFI_ERROR (Status) && (Status != EFI_BUFFER_TOO_SMALL));
  RestoreHpet ();

  return Status;
}

EFI_STATUS
EFIAPI
HeciSend (
  IN UINT32                     *Message,
  IN UINT32                     Length,
  IN UINT8                      HostAddress,
  IN UINT8                      MeAddress
  )
/*++

  Routine Description:
    Function sends one messsage (of any length) through the HECI circular buffer.

  Arguments:
    Message     - Pointer to the message data to be sent.
    Length      - Length of the message in bytes.
    HostAddress - The address of the host processor.
    MeAddress   - Address of the ME subsystem the message is being sent to.

  Returns:
    EFI_STATUS

--*/
{
  UINT32                      CBLength;
  UINT32                      SendLength;
  UINT32                      CurrentLength;
  HECI_MESSAGE_HEADER         MessageHeader;
  EFI_STATUS                  Status;
  HECI_HOST_CONTROL_REGISTER  HeciRegHCsr;
  UINT32                      MeDeviceState;

  Status        = EFI_SUCCESS;
  CurrentLength = 0;

  SaveHpet ();

  do {
    if (mHeciContext->MeMode == ME_MODE_SECOVER) {
      Status = EFI_UNSUPPORTED;
      break;
    }
    //
    // Enable HECI and Save the Device State
    //
    mHeciContext->HeciDevSaveEnable (&MeDeviceState);

    //
    // Make sure that HECI device BAR is correct and device is enabled.
    //
    HeciMBAR = CheckAndFixHeciForAccess ();

    //
    // Make sure we do not have a HECI reset
    //
    if (CheckForHeciReset ()) {
      //
      // if HECI reset than try to re-init HECI
      //
      Status = HeciInitialize ();

      if (EFI_ERROR (Status)) {
        HeciDevRestore (MeDeviceState);
        Status = EFI_DEVICE_ERROR;
        break;
      }
    }
    //
    // Make sure that HECI is ready for communication.
    //
    if (WaitForMEReady () != EFI_SUCCESS) {
      HeciDevRestore (MeDeviceState);
      Status = EFI_TIMEOUT;
      break;
    }
    //
    // Set up memory mapped registers
    //
    HeciRegHCsr.ul = MMIOREADDWORD (HeciMBAR + H_CSR);

    //
    // Grab Circular Buffer length
    //
    CBLength = HeciRegHCsr.r.H_CBD;

    //
    // Prepare message header
    //
    MessageHeader.Data                = 0;
    MessageHeader.Fields.MeAddress    = MeAddress;
    MessageHeader.Fields.HostAddress  = HostAddress;

    //
    // Break message up into CB-sized packets and loop until completely sent
    //
    while (Length > CurrentLength) {
      //
      // Set the Message Complete bit if this is our last packet in the message.
      // Needs to be 'less than' to account for the header.
      //
      if ((((Length - CurrentLength) + 3) / 4) < CBLength) {
        MessageHeader.Fields.MessageComplete = 1;
      }
      //
      // Calculate length for Message Header
      //    header length == smaller of circular buffer or remaining message (both account for the size of the header)
      //
      SendLength = ((CBLength < (((Length - CurrentLength) + 3) / 4)) ? ((CBLength - 1) * 4) : (Length - CurrentLength));
      MessageHeader.Fields.Length = SendLength;

      //
      // send the current packet (CurrentLength can be treated as the index into the message buffer)
      //
      Status = HeciPacketWrite (&MessageHeader, (UINT32 *) ((UINTN) Message + CurrentLength));
      if (EFI_ERROR (Status)) {
        break;
      }
      //
      // Update the length information
      //
      CurrentLength += SendLength;
    }

    if (EFI_ERROR (Status)) {
      break;
    }
    //
    // Restore HECI Device State
    //
    HeciDevRestore (MeDeviceState);

  } while (EFI_ERROR (Status));

  RestoreHpet ();

  return Status;
}

EFI_STATUS
HeciPacketWrite (
  IN  HECI_MESSAGE_HEADER       *MessageHeader,
  IN  UINT32                    *MessageData
  )
/*++

  Routine Description:
   Function sends one messsage packet through the HECI circular buffer
   Corresponds to HECI HPS (part of) section 4.2.3

  Arguments:
    MessageHeader - Pointer to the message header.
    MessageData   - Pointer to the actual message data.

  Returns:
    EFI_STATUS

--*/
{
  UINT32                      timer_start;
  UINT32                      timer_end;
  UINT32                      i;
  UINT32                      LengthInDwords;
  HECI_HOST_CONTROL_REGISTER  HeciRegHCsr;
  HECI_ME_CONTROL_REGISTER    HeciRegMeCsrHa;

  //
  //  VOLATILE HECI_HOST_CONTROL_REGISTER *HeciRegHCsrPtr     = (VOID*)(mHeciContext->HeciMBAR + H_CSR);
  //  VOLATILE HECI_ME_CONTROL_REGISTER   *HeciRegMeCsrHaPtr  = (VOID*)(mHeciContext->HeciMBAR + ME_CSR_HA);
  //  VOLATILE UINT32                     *HeciRegHCbwwPtr    = (VOID*)(mHeciContext->HeciMBAR + H_CB_WW);
  //
  // Make sure that HECI is ready for communication.
  //
  if (WaitForMEReady () != EFI_SUCCESS) {
    return EFI_TIMEOUT;
  }
  //
  // Start timeout counter
  //
  StartTimer (&timer_start, &timer_end, HECI_SEND_TIMEOUT);

  //
  // Compute message length in DWORDS
  //
  LengthInDwords = ((MessageHeader->Fields.Length + 3) / 4);

  //
  // Wait until there is sufficient room in the circular buffer
  // Must have room for message and message header
  //
  HeciRegHCsr.ul = MMIOREADDWORD (HeciMBAR + H_CSR);
  while ((LengthInDwords + 1) > (HeciRegHCsr.r.H_CBD - FilledSlots (HeciRegHCsr.r.H_CBRP, HeciRegHCsr.r.H_CBWP))) {
    //
    // If 1 second timeout has expired, return fail as the circular buffer never emptied
    //
    if (Timeout (timer_start, timer_end) != EFI_SUCCESS) {
      return EFI_TIMEOUT;
    }
    //
    // Wait before we read the register again
    //
    IoDelay (HECI_WAIT_DELAY);

    //
    // Read Host CSR for next iteration
    //
    HeciRegHCsr.ul = MMIOREADDWORD (HeciMBAR + H_CSR);
  }
  //
  // Write Message Header
  //
  MMIOWRITEDWORD (HeciMBAR + H_CB_WW, MessageHeader->Data);

  //
  // Write Message Body
  //
  for (i = 0; i < LengthInDwords; i++) {
    MMIOWRITEDWORD (HeciMBAR + H_CB_WW, MessageData[i]);
  }
  //
  // Set Interrupt Generate bit
  //
  HeciRegHCsr.ul      = MMIOREADDWORD (HeciMBAR + H_CSR);
  HeciRegHCsr.r.H_IG  = 1;
  MMIOWRITEDWORD (HeciMBAR + H_CSR, HeciRegHCsr.ul);

  //
  // Test if ME Ready bit is set to 1, if set to 0 a fatal error occured during
  // the transmission of this message.
  //
  HeciRegMeCsrHa.ul = MMIOREADDWORD (HeciMBAR + ME_CSR_HA);
  if (HeciRegMeCsrHa.r.ME_RDY_HRA == 0) {
    return EFI_DEVICE_ERROR;
  }

  return EFI_SUCCESS;
}

EFI_STATUS
EFIAPI
HeciSendwACK (
  IN OUT  UINT32  *Message,
  IN      UINT32  Length,
  IN OUT  UINT32  *RecLength,
  IN      UINT8   HostAddress,
  IN      UINT8   MeAddress
  )
/*++

  Routine Description:
    Function sends one messsage through the HECI circular buffer and waits
    for the corresponding ACK message.

  Arguments:
    Message     - Pointer to the message buffer.
    SendLength  - Length of the message in bytes.
    RecLength   - Length of the message response in bytes.
    HostAddress - Address of the sending entity.
    MeAddress   - Address of the ME entity that should receive the message.

  Returns:
    EFI_STATUS

--*/
{
  EFI_STATUS  Status;
  UINT16      RetryCount;
  UINT32      TempRecLength;

  if (mHeciContext->MeMode == ME_MODE_SECOVER) {
    return EFI_UNSUPPORTED;
  }
  //
  // Send the message
  //
  Status = HeciSend (Message, Length, HostAddress, MeAddress);
  if (EFI_ERROR (Status)) {
    return Status;
  }
  //
  // Wait for ACK message
  //
  TempRecLength = *RecLength;
  for (RetryCount = 0; RetryCount < HECI_MAX_RETRY; RetryCount++) {
    //
    // Read Message
    //
    Status = HeciReceive (BLOCKING, Message, &TempRecLength);
    if (!EFI_ERROR (Status)) {
      break;
    }
    //
    // Reload receive length as it has been modified by the read function
    //
    TempRecLength = *RecLength;
  }
  //
  // Return read length and status
  //
  *RecLength = TempRecLength;
  return Status;
}

EFI_STATUS
EFIAPI
MeResetWait (
  IN  UINT32  Delay
  )
/*++

Routine Description:

  Me reset and waiting for ready

Arguments:

  Delay - The biggest waiting time

Returns:

  EFI_TIMEOUT - Time out
  EFI_SUCCESS - Me ready

--*/
{
  HECI_HOST_CONTROL_REGISTER  HeciRegHCsr;
  UINT32                      TimerStart;
  UINT32                      TimerEnd;

  //
  // Make sure that HECI device BAR is correct and device is enabled.
  //
  HeciMBAR = CheckAndFixHeciForAccess ();

  //
  // Wait for the HOST Ready bit to be cleared to signal a reset
  //
  StartTimer (&TimerStart, &TimerEnd, Delay);
  HeciRegHCsr.ul = MMIOREADDWORD (HeciMBAR + H_CSR);
  while (HeciRegHCsr.r.H_RDY == 1) {
    //
    // If timeout has expired, return fail
    //
    if (Timeout (TimerStart, TimerEnd) != EFI_SUCCESS) {
      return EFI_TIMEOUT;
    }

    HeciRegHCsr.ul = MMIOREADDWORD (HeciMBAR + H_CSR);
  }

  return EFI_SUCCESS;
}

EFI_STATUS
EFIAPI
ResetHeciInterface (
  VOID
  )
/*++

  Routine Description:
    Function forces a reinit of the heci interface by following the reset heci interface via host algorithm
    in HPS 0.90 doc 4-17-06 njy

  Arguments:
    none

  Returns:
    EFI_STATUS

--*/
{
  HECI_HOST_CONTROL_REGISTER  HeciRegHCsr;
  HECI_ME_CONTROL_REGISTER    HeciRegMeCsrHa;
  UINT32                      TimerStart;
  UINT32                      TimerEnd;

  //
  // Make sure that HECI device BAR is correct and device is enabled.
  //
  HeciMBAR = CheckAndFixHeciForAccess ();

  //
  // Enable Reset
  //
  HeciRegHCsr.ul      = MMIOREADDWORD (HeciMBAR + H_CSR);
  HeciRegHCsr.r.H_RST = 1;
  HeciRegHCsr.r.H_IG  = 1;
  MMIOWRITEDWORD (HeciMBAR + H_CSR, HeciRegHCsr.ul);

  //
  // Make sure that the reset started
  //
  // HeciRegHCsr.ul = MMIOREADDWORD(HeciMBAR + H_CSR);
  //
  StartTimer (&TimerStart, &TimerEnd, HECI_INIT_TIMEOUT);
  do {
    //
    // If 5 second timeout has expired, return fail
    //
    if (Timeout (TimerStart, TimerEnd) != EFI_SUCCESS) {
      return EFI_TIMEOUT;
    }
    //
    // Read the ME CSR
    //
    HeciRegHCsr.ul = MMIOREADDWORD (HeciMBAR + H_CSR);
  } while (HeciRegHCsr.r.H_RDY == 1);

  //
  // Wait for ME to perform reset
  //
  // HeciRegMeCsrHa.ul = MMIOREADDWORD(HeciMBAR + ME_CSR_HA);
  //
  StartTimer (&TimerStart, &TimerEnd, HECI_INIT_TIMEOUT);
  do {
    //
    // If 5 second timeout has expired, return fail
    //
    if (Timeout (TimerStart, TimerEnd) != EFI_SUCCESS) {
      return EFI_TIMEOUT;
    }
    //
    // Read the ME CSR
    //
    HeciRegMeCsrHa.ul = MMIOREADDWORD (HeciMBAR + ME_CSR_HA);
  } while (HeciRegMeCsrHa.r.ME_RDY_HRA == 0);

  //
  // Make sure IS has been signaled on the HOST side
  //
  // HeciRegHCsr.ul = MMIOREADDWORD(HeciMBAR + H_CSR);
  //
  StartTimer (&TimerStart, &TimerEnd, HECI_INIT_TIMEOUT);
  do {
    //
    // If 5 second timeout has expired, return fail
    //
    if (Timeout (TimerStart, TimerEnd) != EFI_SUCCESS) {
      return EFI_TIMEOUT;
    }
    //
    // Read the ME CSR
    //
    HeciRegHCsr.ul = MMIOREADDWORD (HeciMBAR + H_CSR);
  } while (HeciRegHCsr.r.H_IS == 0);

  //
  // Enable host side interface
  //
  HeciRegHCsr.ul      = MMIOREADDWORD (HeciMBAR + H_CSR);;
  HeciRegHCsr.r.H_RST = 0;
  HeciRegHCsr.r.H_IG  = 1;
  HeciRegHCsr.r.H_RDY = 1;
  MMIOWRITEDWORD (HeciMBAR + H_CSR, HeciRegHCsr.ul);

  return EFI_SUCCESS;
}

UINT8
FilledSlots (
  IN  UINT32 ReadPointer,
  IN  UINT32 WritePointer
  )
/*++

  Routine Description:
    Calculate if the circular buffer has overflowed.
    Corresponds to HECI HPS (part of) section 4.2.1

  Arguments:
    ReadPointer  - Location of the read pointer.
    WritePointer - Location of the write pointer.

  Returns:
    Number of filled slots.

--*/
{
  UINT8 FilledSlots;

  //
  // Calculation documented in HECI HPS 0.68 section 4.2.1
  //
  FilledSlots = (((INT8) WritePointer) - ((INT8) ReadPointer));

  return FilledSlots;
}

EFI_STATUS
OverflowCB (
  IN  UINT32 ReadPointer,
  IN  UINT32 WritePointer,
  IN  UINT32 BufferDepth
  )
/*++

  Routine Description:
    Calculate if the circular buffer has overflowed
    Corresponds to HECI HPS (part of) section 4.2.1

  Arguments:
    ReadPointer - Value read from host/me read pointer
    WritePointer - Value read from host/me write pointer
    BufferDepth - Value read from buffer depth register

  Returns:
    EFI_STATUS

--*/
{
  UINT8 FilledSlots;

  //
  // Calculation documented in HECI HPS 0.68 section 4.2.1
  //
  FilledSlots = (((INT8) WritePointer) - ((INT8) ReadPointer));

  //
  // test for overflow
  //
  if (FilledSlots > ((UINT8) BufferDepth)) {
    return EFI_DEVICE_ERROR;
  }

  return EFI_SUCCESS;
}

EFI_STATUS
EFIAPI
HeciGetMeStatus (
  IN UINT32                     *MeStatus
  )
/*++

  Routine Description:
    Return ME Status

  Arguments:
    MeStatus pointer for status report

  Returns:
    EFI_STATUS

--*/
{
  HECI_FWS_REGISTER MeFirmwareStatus;
  UINT32            MeDeviceState;

  if (MeStatus == NULL) {
    return EFI_INVALID_PARAMETER;
  }
  //
  // Save HECI1 Device State and Enable it
  //
  Heci1DevSaveEnable (&MeDeviceState);

  MeFirmwareStatus.ul = HeciPciRead32 (R_FWSTATE);

  if (MeFirmwareStatus.r.CurrentState == ME_STATE_NORMAL && MeFirmwareStatus.r.ErrorCode == ME_ERROR_CODE_NO_ERROR) {
    *MeStatus = ME_READY;
  } else if (MeFirmwareStatus.r.CurrentState == ME_STATE_RECOVERY) {
    *MeStatus = ME_IN_RECOVERY_MODE;
  } else {
    *MeStatus = ME_NOT_READY;
  }

  if (MeFirmwareStatus.r.FwInitComplete == ME_FIRMWARE_COMPLETED) {
    *MeStatus |= ME_FW_INIT_COMPLETE;
  }
  //
  // Save HECI Device State and Enable it
  //
  HeciDevRestore (MeDeviceState);

  return EFI_SUCCESS;
}

EFI_STATUS
EFIAPI
HeciGetMeMode (
  IN UINT32                     *MeMode
  )
/*++

  Routine Description:
    Return ME Mode

  Arguments:
    MeMode pointer for ME Mode report

  Returns:
    EFI_STATUS

--*/
{
  HECI_FWS_REGISTER MeFirmwareStatus;
  UINT32            MeDeviceState;

  if (MeMode == NULL) {
    return EFI_INVALID_PARAMETER;
  }
  //
  // Save HECI1 Device State and Enable it
  //
  Heci1DevSaveEnable (&MeDeviceState);

  MeFirmwareStatus.ul = HeciPciRead32 (R_FWSTATE);
    switch (MeFirmwareStatus.r.MeOperationMode) {
    case ME_OPERATION_MODE_NORMAL:
      *MeMode = ME_MODE_NORMAL;
      break;

    case ME_OPERATION_MODE_DEBUG:
      *MeMode = ME_MODE_DEBUG;
      break;

    case ME_OPERATION_MODE_SOFT_TEMP_DISABLE:
      *MeMode = ME_MODE_TEMP_DISABLED;
      break;

    case ME_OPERATION_MODE_SECOVR_JMPR:
    case ME_OPERATION_MODE_SECOVR_HECI_MSG:
      *MeMode = ME_MODE_SECOVER;
      break;

    default:
      *MeMode = ME_MODE_FAILED;
    }
  //
  // Save HECI Device State and Enable it
  //
  HeciDevRestore (MeDeviceState);

  return EFI_SUCCESS;
}

EFI_STATUS
Heci1DevSaveEnable (
  IN OUT  UINT32 *DevState
  )
/*++

  Routine Description:
   Save HECI1 State and Enable it

  Arguments:
    DevState          - Device State Save Buffer

  Returns:
    EFI_STATUS

--*/
{
  *DevState = MMIOREADDWORD (PCH_RCRB_BASE + R_PCH_RCRB_FUNC_DIS2);
  HeciEnable ();
  return EFI_SUCCESS;
}

EFI_STATUS
Heci2DevSaveEnable (
  IN OUT  UINT32 *DevState
  )
/*++

  Routine Description:
   Save HECI2 State and Enable it

  Arguments:
    DevState          - Device State Save Buffer

  Returns:
    EFI_STATUS

--*/
{
  *DevState = MMIOREADDWORD (PCH_RCRB_BASE + R_PCH_RCRB_FUNC_DIS2);
  Heci2Enable ();
  return EFI_SUCCESS;
}

EFI_STATUS
HeciDevRestore (
  IN  UINT32 DevState
  )
/*++

  Routine Description:
  Restore HECI1&HECI2 State

  Arguments:
    DevState          - Device State Save Buffer

  Returns:
    EFI_STATUS

--*/
{
  MMIOWRITEDWORD (PCH_RCRB_BASE + R_PCH_RCRB_FUNC_DIS2, DevState);
  MMIOREADDWORD (PCH_RCRB_BASE + R_PCH_RCRB_FUNC_DIS2);
  return EFI_SUCCESS;
}
