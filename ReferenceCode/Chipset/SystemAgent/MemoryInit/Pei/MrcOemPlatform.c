/** @file
  This file contains platform related functions.

@copyright
  Copyright (c) 1999 - 2013 Intel Corporation. All rights reserved
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
  license agreement.

**/

#ifdef MRC_MINIBIOS_BUILD
#include "MemoryUtils.h"
#else
#include <Tiano.h>
#include <EdkIIGluePeim.h>
#include <EdkIIGlueBaseLib.h>
#include "CpuRegs.h"
#include "CpuPlatformLib.h"
#ifdef SSA_FLAG
#include "SsaCallbackPeim.h"
extern
VOID
SsaBiosInitialize (
  IN MrcParameters       *MrcData
  );
#endif // SSA_FLAG
#endif

//
// Include files
//
#ifndef AMI_OVERRIDE_FOR_MEMORY_DOWN
#include <Token.h>
#include "MrcSpdData.h"
#endif // AMI_OVERRIDE_FOR_MEMORY_DOWN
#include "MrcTypes.h"
#include "MrcApi.h"
#include "McAddress.h"
#include "MrcCommon.h"
#include "MrcGlobal.h"
#include "MrcOem.h"
#include "MrcOemPlatform.h"

#include "PchRegsLpc.h"
#include "MrcReset.h"


// AMI_OVERRIDE_FOR_UPSERVER_SUPPORT
#ifdef UPSERVER_SUPPORT
#include "MrcOemSmbus.h"

const U8 CltmThermalLookUpTable [2][2][2][5] =
{
    {// DRAM Density 2Gb
        {// Frequency 1600
            // 1 DIMM
            {6, 6, 6, 6, 6},
            // 2 DIMMs
            {7, 7, 7, 6, 6}
        },
        {// Frequency 1333
            // 1 DIMM
            {5, 5, 5, 5, 5},
            // 2 DIMMs
            {6, 6, 6, 6, 5}
        }
    },
    {// DRAM Density 4Gb
        {// Frequency 1600
            // 1 DIMM
            {7, 6, 6, 6, 7},
            // 2 DIMMs
            {7, 7, 7, 7, 6}
        },
        {// Frequency 1333
            // 1 DIMM
            {6, 5, 5, 5, 6},
            // 2 DIMMs
            {7, 7, 6, 6, 6}
        }
    }
};

const U16 CltmPowerLookUpTable [2][2][2][8] =
{
    {// DRAM Density 2Gb
        {// Frequency 1600
            // DIMM Position 1
            
            {4, 99, 147, 129, 6, 10, 0x18, 0x0C},
            // DIMM Position 2
            {3, 182, 203, 64, 3, 5, 0x1B, 0x09}
        },
        {// Frequency 1333 
            // DIMM Position 1
            {4, 102, 160, 121, 7, 11, 0x15, 0x08},
            // DIMM Position 2
            {3, 210, 236, 60, 3, 5, 0x18, 0x0C}
        }
    },
    {// DRAM Density 4Gb
        {// Frequency 1600
            // DIMM Position 1
            {4, 111, 158, 132, 8, 12, 0x1B, 0x0E},
            // DIMM Position 2
            {3, 188, 209, 66, 4, 6, 0x1D, 0x07}
        },
        {// Frequency 1333
            // DIMM Position 1
            {4, 115, 171, 124, 9, 13, 0x17, 0x0A},
            // DIMM Position 2
            {3, 217, 241, 62, 4, 6, 0x1B, 0x09}
        }
    }
};

#endif
// AMI_OVERRIDE_FOR_UPSERVER_SUPPORT

#ifdef MRC_DEBUG_PRINT
extern const char CcdString[];
const char TrainEnString[]  = "TrainingEnables";
const char GdxcString[]     = "Gdxc";
const char BaseTimeString[] = "BaseTime";
const char ThermEnString[]  = "ThermalEnables";
#endif // MRC_DEBUG_PRINT

#ifdef ULT_FLAG

//
// The following section contains board-specific CMD/CTL/CLK and DQ/DQS mapping, needed for LPDDR3
//

//
// DQByteMap[0] - ClkDQByteMap:
//   If clock is per rank, program to [0xFF, 0xFF]
//   If clock is shared by 2 ranks, program to [0xFF, 0] or [0, 0xFF]
//   If clock is shared by 2 ranks but does not go to all bytes,
//           Entry[i] defines which DQ bytes Group i services
// DQByteMap[1] - CmdNDQByteMap: Entry[0] is CmdN/CAA and Entry[1] is CmdN/CAB
// DQByteMap[2] - CmdSDQByteMap: Entry[0] is CmdS/CAA and Entry[1] is CmdS/CAB
// DQByteMap[3] - CkeDQByteMap : Entry[0] is CKE /CAA and Entry[1] is CKE /CAB
//                For DDR, DQByteMap[3:1] = [0xFF, 0]
// DQByteMap[4] - CtlDQByteMap : Always program to [0xFF, 0] since we have 1 CTL / rank
//                               Variable only exists to make the code easier to use
// DQByteMap[5] - CmdVDQByteMap: Always program to [0xFF, 0] since we have 1 CA Vref
//                               Variable only exists to make the code easier to use
//

//
// DQ byte mapping to CMD/CTL/CLK, from the CPU side - for Sawtooth Peak and Harris Beach
//
const U8 DqByteMapRvpCh0[6][2] = {
  { 0x0F, 0xF0 }, // CLK0 goes to package 0 - Bytes[3:0], CLK1 goes to package 1 - Bytes[7:4]
  { 0x00, 0xF0 }, // CmdN does not have CAA, CAB goes to Bytes[7:4]
  { 0x0F, 0xF0 }, // CmdS CAA goes to Bytes[3:0], CmdS CAB goes to Byte[7:4]
  { 0x0F, 0x00 }, // CKE CAA goes to Bytes[3:0], CKE does not have CAB
  { 0xFF, 0x00 }, // CTL (CS) goes to all bytes
  { 0xFF, 0x00 }  // CA Vref is one for all bytes
};

const U8 DqByteMapRvpCh1[6][2] = {
  { 0x0F, 0xF0 }, // CLK0 goes to package 0 - Bytes[3:0], CLK1 goes to package 1 - Bytes[7:4]
  { 0x00, 0xF0 }, // CmdN does not have CAA, CAB goes to Bytes[7:4]
  { 0x0F, 0xF0 }, // CmdS CAA goes to Bytes[3:0], CmdS CAB goes to Byte[7:4]
  { 0x0F, 0x00 }, // CKE CAA goes to Bytes[3:0], CKE does not have CAB
  { 0xFF, 0x00 }, // CTL (CS) goes to all bytes
  { 0xFF, 0x00 }  // CA Vref is one for all bytes
};

//
// DQ byte mapping to CMD/CTL/CLK, from the CPU side - for Big Creek
//
const U8 DqByteMapSvCh0[6][2] = {
  { 0x0F, 0xF0 }, // CLK0 goes to package 0 - Bytes[3:0], CLK1 goes to package 1 - Bytes[7:4]
  { 0x00, 0xF0 }, // CmdN does not have CAA, CAB goes to Bytes[7:4]
  { 0x0F, 0xF0 }, // CmdS CAA goes to Bytes[3:0], CmdS CAB goes to Byte[7:4]
  { 0x0F, 0x00 }, // CKE CAA goes to Bytes[3:0], CKE does not have CAB
  { 0xFF, 0x00 }, // CTL (CS) goes to all bytes
  { 0xFF, 0x00 }  // CA Vref is one for all bytes
};

const U8 DqByteMapSvCh1[6][2] = {
  { 0xE8, 0x17 }, // CLK0 goes to package 0 - Bytes[3:0], CLK1 goes to package 1 - Bytes[7:4]
  { 0x00, 0x17 }, // CmdN does not have CAA, CAB goes to Bytes[7:4]
  { 0xE8, 0x17 }, // CmdS CAA goes to Bytes[3:0], CmdS CAB goes to Byte[7:4]
  { 0xE8, 0x00 }, // CKE CAA goes to Bytes[3:0], CKE does not have CAB
  { 0xFF, 0x00 }, // CTL (CS) goes to all bytes
  { 0xFF, 0x00 }  // CA Vref is one for all bytes
};

//
// DQS byte swizzling between CPU and DRAM - for Sawtooth Peak and Harris Beach
//
const U8 DqsMapCpu2DramRvpCh0[8] = { 2, 0, 1, 3, 6, 4, 7, 5 };
const U8 DqsMapCpu2DramRvpCh1[8] = { 1, 3, 2, 0, 5, 7, 6, 4 };

//
// DQS byte swizzling between CPU and DRAM - for Big Creek
//
const U8 DqsMapCpu2DramSvCh0[8] = { 0, 1, 2, 3, 5, 6, 7, 4 };
const U8 DqsMapCpu2DramSvCh1[8] = { 7, 6, 5, 2, 4, 3, 1, 0 };

//
// DQ bit swizzling between CPU and DRAM - for Sawtooth Peak and Harris Beach
//
const U8 DqMapCpu2DramRvpCh0[8][8] = {
  { 16, 21, 18, 19, 20, 17, 22, 23 },  // Byte 0
  {  3,  6,  1,  5,  2,  7,  0,  4 },  // Byte 1
  {  9,  8, 14, 15, 10, 11, 13, 12 },  // Byte 2
  { 29, 28, 27, 31, 24, 25, 30, 26 },  // Byte 3
  { 53, 49, 50, 51, 48, 52, 54, 55 },  // Byte 4
  { 35, 38, 33, 37, 34, 39, 32, 36 },  // Byte 5
  { 63, 59, 61, 57, 56, 60, 58, 62 },  // Byte 6
  { 44, 45, 46, 42, 40, 41, 43, 47 }   // Byte 7
};
const U8 DqMapCpu2DramRvpCh1[8][8] = {
  { 15, 11,  8,  9, 10, 14, 12, 13 },  // Byte 0
  { 24, 29, 30, 26, 28, 25, 27, 31 },  // Byte 1
  { 16, 20, 22, 23, 17, 21, 19, 18 },  // Byte 2
  {  6,  3,  1,  5,  2,  7,  4,  0 },  // Byte 3
  { 47, 42, 40, 41, 43, 46, 44, 45 },  // Byte 4
  { 57, 56, 62, 58, 61, 60, 59, 63 },  // Byte 5
  { 51, 49, 54, 53, 48, 50, 55, 52 },  // Byte 6
  { 38, 35, 36, 32, 34, 39, 33, 37 }   // Byte 7
};

//
// DQ bit swizzling between CPU and DRAM - for Big Creek
//
const U8 DqMapCpu2DramSvCh0[8][8] = {
  {  1,  0,  2,  6,  5,  4,  3,  7 },  // Byte 0
  { 13,  9, 14, 10, 12,  8, 15, 11 },  // Byte 1
  { 22, 18, 21, 16, 17, 20, 19, 23 },  // Byte 2
  { 29, 28, 26, 27, 30, 31, 24, 25 },  // Byte 3
  { 41, 45, 46, 42, 40, 44, 43, 47 },  // Byte 4
  { 53, 49, 54, 50, 52, 48, 55, 51 },  // Byte 5
  { 63, 62, 61, 60, 59, 58, 57, 56 },  // Byte 6
  { 34, 35, 37, 36, 38, 39, 33, 32 }   // Byte 7
};
const U8 DqMapCpu2DramSvCh1[8][8] = {
  { 58, 62, 57, 61, 59, 63, 56, 60 },  // Byte 0
  { 54, 50, 53, 49, 55, 51, 52, 48 },  // Byte 1
  { 46, 47, 45, 44, 43, 42, 41, 40 },  // Byte 2
  { 22, 19, 23, 18, 16, 21, 20, 17 },  // Byte 3
  { 38, 34, 37, 33, 39, 35, 36, 32 },  // Byte 4
  { 26, 30, 25, 29, 27, 31, 24, 28 },  // Byte 5
  { 15, 11,  9, 13, 14, 10, 12,  8 },  // Byte 6
  {  6,  7,  0,  1,  4,  5,  3,  2 }   // Byte 7
};

#endif // ULT_FLAG

const MrcVddSelect MemoryVoltageTable[] = {
  //
  //                       MB     DT                  MB    DT
  // Voltage         //  GPIO24/GPIO60   GPIO46     GPIO8/GPIO45
  //
  1650,           //    0               0            0
  1600,           //    0               0            1
  1550,           //    0               1            0
  1503,           //    0               1            1
  1500,           //    1               0            0
  1450,           //    1               0            1
  1400,           //    1               1            0
  1350            //    1               1            1
};

/**
  Gets CPU ratio

  @param[in] Nothing

  @retval Cpu ratio.
**/
U32
MrcGetCpuRatio (
  void
  )
{
  PCU_CR_PLATFORM_INFO_STRUCT Msr;

  Msr.Data = AsmReadMsr64 (PCU_CR_PLATFORM_INFO);
  return (Msr.Bits.MAX_NON_TURBO_LIM_RATIO);
}

/**
  Gets CPU current time.

  @param[in] Nothing

  @retval The current CPU time in milliseconds.
**/
U64
MrcGetCpuTime (
  void
  )
{
  U32 TimeBase;

  TimeBase = (1000 * MRC_SYSTEM_BCLK) * MrcGetCpuRatio (); //In Millisec
  return ((TimeBase == 0) ? 0 : MrcOemMemoryDivideU64ByU64 (AsmReadTsc (), TimeBase));
}

/**
  Sets CpuModel and CpuStepping in MrcData based on CpuModelStep.

  @param[out] MrcData     - The Mrc Host data structure
  @param[in]  CpuModel    - The CPU Family Model.
  @param[in]  CpuStepping - The CPU Stepping.

  @retval - mrcSuccess if the model and stepping is found.  Otherwise mrcFail
**/
MrcStatus
MrcSetCpuInformation (
  OUT MrcParameters  *MrcData,
  IN  MrcCpuModel    CpuModel,
  IN  MrcCpuStepping CpuStepping
  )
{
  MrcInput  *Inputs;
  MrcDebug  *Debug;
  MrcStatus Status;

  Inputs = &MrcData->SysIn.Inputs;
  Debug  = &MrcData->SysIn.Inputs.Debug;
  Status = mrcFail;

#ifdef ULT_FLAG
  if (CpuModel == cmHSW_ULT) {
    Inputs->CpuModel = cmHSW_ULT;
    MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "Haswell ULT:");

    switch (CpuStepping) {
      case csHswUltB0:
        Inputs->CpuStepping = csHswUltB0;
        MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, " Stepping B0\n");
        break;

      case csHswUltC0:
        Inputs->CpuStepping = csHswUltC0;
        MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, " Stepping C0\n");
        break;

      default:
        Inputs->CpuStepping = csHswUltB0;   // @todo: Update for C0.
        MRC_DEBUG_MSG (
          Debug,
          MSG_LEVEL_WARNING,
          "\nWARNING: Unknown CPU stepping, using MRC for last known step. Step = %Xh\n",
          Inputs->CpuStepping
          );
        break;
    }
    Status = mrcSuccess;
  }
#endif // ULT_FLAG

#ifdef TRAD_FLAG
  if (CpuModel == cmHSW) {
    Inputs->CpuModel = cmHSW;
    MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "Haswell:");

    switch (CpuStepping) {
      case csHswA0:
        Inputs->CpuStepping = csHswA0;
        MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, " Stepping A0\n");
        break;

      case csHswB0:
        Inputs->CpuStepping = csHswB0;
        MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, " Stepping B0\n");
        break;

      case csHswC0:
        Inputs->CpuStepping = csHswC0;
        MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, " Stepping C0\n");
        break;

      default:
        Inputs->CpuStepping = csHswC0;
        MRC_DEBUG_MSG (
          Debug,
          MSG_LEVEL_WARNING,
          "\nWARNING: Unknown CPU stepping, using MRC for last known step. Step = %Xh\n",
          Inputs->CpuStepping
          );
        break;
    }
    Status = mrcSuccess;
  }

  if (CpuModel == cmCRW) {
    Inputs->CpuModel = cmCRW;
    MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "Crystalwell:");

    switch (CpuStepping) {
      case csCrwB0:
        Inputs->CpuStepping = csCrwB0;
        MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, " Stepping B0\n");
        break;

      case csCrwC0:
        Inputs->CpuStepping = csCrwC0;
        MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, " Stepping C0\n");
        break;

      default:
        Inputs->CpuStepping = csCrwB0;  // @todo: Update for C0
        MRC_DEBUG_MSG (
          Debug,
          MSG_LEVEL_WARNING,
          "\nWARNING: Unknown CPU stepping, using MRC for last known step. Step = %Xh\n",
          Inputs->CpuStepping
          );
        break;
    }
    Status = mrcSuccess;
  }
#endif // TRAD_FLAG

  return Status;
}

/**
  Gets a number from the CPU's random number generator.

  @param[in] Nothing

  @retval   Random number or zero if random number is not generated or is invalid.
**/
U32
AsmGetRandomNumber (
  void
  )
{
  U32 Status;
  U32 RandomNumber;

  // Assembly instruction to read CPU's random number generator
  // Instruction is only available 100k cycles after reset
  // rdrand eax
  // db 0Fh, 0C7h, 0F0h
#if defined __GNUC__  // GCC compiler
  __asm__ __volatile__ (
    "\n\t .byte 0x0F, 0xC7, 0xF0"
    "\n\t movl %%eax, %0"
    "\n\t pushf"
    "\n\t pop %%eax"
    "\n\t movl %%eax, %1"
    : "=m" (RandomNumber),
      "=m" (Status)
    );
#else //MSFT compiler
  ASM {
    _emit   0x0F
    _emit   0xC7
    _emit   0xF0
    mov     RandomNumber, eax

    pushfd
    pop     eax
    mov     Status, eax
  }
#endif
  // If CF is cleared, return 0
  return (((Status & 1) == 0) ? 0 : RandomNumber);
}

/**
  Gets a random number from the CPU's random number generator.

  @param[in] Nothing

  @retval Random number returned by the CPU instruction or generated from real time clock data.
**/
U32
MrcGetRandomNumber (
  void
  )
{
  U32 RandomNumber;
  U32 Retry;
  U16 Year;
  U8  Month;
  U8  DayOfMonth;
  U8  Hours;
  U8  Minutes;
  U8  Seconds;

  RandomNumber = 0;
  for (Retry = 100000; ((Retry != 0) && (RandomNumber == 0)); --Retry) {
    RandomNumber = AsmGetRandomNumber ();
  }
  if ((Retry == 0) && (RandomNumber == 0)) {
    MrcOemGetRtcTime (&Seconds, &Minutes, &Hours, &DayOfMonth, &Month, &Year);
    RandomNumber = Seconds + (Minutes * 60) + (Hours * 60 * 60);
  }

  return (RandomNumber);
}

/**
  This function enables 2x Refresh through the mailbox.

  @param[in]  MrcData - Pointer to the MRC global data structure

  @retval - Nothing.
**/
void
MrcOemEnable2xRefresh (
  IN MrcParameters *const MrcData
  )
{
#ifndef MRC_MINIBIOS_BUILD
  MrcDebug            *Debug;
  MrcMailbox2xRefresh Write2xRefreshData;
  U32                 MailboxStatus;

  Debug  = &MrcData->SysIn.Inputs.Debug;

  MailboxRead(MAILBOX_TYPE_PCODE, READ_DDR_FORCE_2X_REFRESH, &Write2xRefreshData.Data, &MailboxStatus);
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, " Read Write2xRefreshData: 0x%x\n", Write2xRefreshData.Data);


  if (!Write2xRefreshData.Bits.Lock_Bit) {
    Write2xRefreshData.Bits.Lock_Bit          = 1;
    Write2xRefreshData.Bits.Enable_2x_Refresh = 1;
#ifdef ULT_FLAG
    if (MrcData->SysOut.Outputs.DdrType == MRC_DDR_TYPE_LPDDR3) {
      Write2xRefreshData.Bits.LPDDR_Min_MR4 = RefRate2x; // Matches the JEDEC MR4 Encoding.
    }
#endif
    MailboxWrite(MAILBOX_TYPE_PCODE, WRITE_DDR_FORCE_2X_REFRESH, Write2xRefreshData.Data, &MailboxStatus);

    if (MailboxStatus != PCODE_MAILBOX_CC_SUCCESS) {
      MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "WRITE_DDR_FORCE_2X_REFRESH failed.  MailboxStatus = 0x%x\n", MailboxStatus);
    } else {
      MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "Writing 0x%x to WRITE_DDR_FORCE_2X_REFRESH\n", Write2xRefreshData.Data);
    }
  }
#endif
}

/**
  This function changes the DIMM Voltage to the closest desired voltage without
  going higher. Default wait time is the minimum value of 200us, if more time
  is needed before deassertion of DIMM Reset#, then change the parameter.

  @param[in, out] MrcData            - The MRC "global data" area.
  @param[in]      VddVoltage         - Selects the DDR voltage to use, in mV.
  @param[in, out] VddSettleWaitTime  - Time needed for Vdd to settle after the update

  @retval TRUE if a voltage change occurred, otherwise FALSE.
**/
BOOL
MrcOemVDDVoltageCheckAndSwitch (
  IN OUT MrcParameters      *MrcData,
  IN     const MrcVddSelect VddVoltage,
  IN OUT U32 * const        VddSettleWaitTime
  )
{
  MrcInput  *Inputs;
  MrcOutput *Outputs;
  BOOL      Status;
  U32       GPIOBase;
  U32       GPIO_In_31_0;
  U32       GPIO_In_63_32;
  U32       GPIO_Out_31_0;
  U32       GPIO_Out_63_32;
  U32       Current;
  U8        Index;

  Inputs  = &MrcData->SysIn.Inputs;
  Outputs = &MrcData->SysOut.Outputs;
  Status  = FALSE;

  if (((Inputs->MobilePlatform == TRUE) && (Inputs->BoardType != btUser4)) || (Inputs->MobilePlatform == FALSE)) {
    //
    // Read GPIO base.
    //
    MrcOemMmioRead (
      MrcOemGetPcieDeviceAddress (0, PCI_DEVICE_NUMBER_PCH_LPC, 0, R_PCH_LPC_GPIO_BASE),
      &GPIOBase,
      Inputs->PciEBaseAddress
      );
    GPIOBase &= ~MRC_BIT0;

#ifdef MRC_MINIBIOS_BUILD
    if ((Inputs->MobilePlatform == TRUE) && (Inputs->BoardType != btUser4)) {
      //
      // Setup GPIOs (8,24,46)
      //
      GPIO_In_31_0 = MrcOemInPort32 ((U16) (GPIOBase + R_PCH_GPIO_USE_SEL));
      if ((GPIO_In_31_0 & (MRC_BIT8 | MRC_BIT24)) != (MRC_BIT8 | MRC_BIT24)) {
        GPIO_In_31_0 |= (MRC_BIT8 | MRC_BIT24);
        MrcOemOutPort32 ((U16) (GPIOBase + R_PCH_GPIO_USE_SEL), GPIO_In_31_0);
      }

      GPIO_In_63_32 = MrcOemInPort32 ((U16) (GPIOBase + R_PCH_GPIO_USE_SEL2));
      if ((GPIO_In_63_32 & MRC_BIT14) != MRC_BIT14) {
        GPIO_In_63_32 |= MRC_BIT14;
        MrcOemOutPort32 ((U16) (GPIOBase + R_PCH_GPIO_USE_SEL2), GPIO_In_63_32);
      }

      GPIO_In_31_0 = MrcOemInPort32 ((U16) (GPIOBase + R_PCH_GPIO_IO_SEL));
      if ((GPIO_In_31_0 & (MRC_BIT8 | MRC_BIT24)) != 0) {
        GPIO_In_31_0 &= ~(MRC_BIT8 | MRC_BIT24);
        MrcOemOutPort32 ((U16) (GPIOBase + R_PCH_GPIO_IO_SEL), GPIO_In_31_0);
      }

      GPIO_In_63_32 = MrcOemInPort32 ((U16) (GPIOBase + R_PCH_GPIO_IO_SEL2));
      if ((GPIO_In_63_32 & MRC_BIT14) != 0) {
        GPIO_In_63_32 &= ~MRC_BIT14;
        MrcOemOutPort32 ((U16) (GPIOBase + R_PCH_GPIO_IO_SEL2), GPIO_In_63_32);
      }
    } else if ((Inputs->MobilePlatform == FALSE) && (Inputs->BoardType == btCRBDT)) {
      //
      // Setup GPIOs (45,46,60)
      //
      GPIO_In_63_32 = MrcOemInPort32 ((U16) (GPIOBase + R_PCH_GPIO_USE_SEL2));
      if ((GPIO_In_63_32 & (MRC_BIT28 | MRC_BIT14 | MRC_BIT13)) != (MRC_BIT28 | MRC_BIT14 | MRC_BIT13)) {
        GPIO_In_63_32 |= (MRC_BIT28 | MRC_BIT14 | MRC_BIT13);
        MrcOemOutPort32 ((U16) (GPIOBase + R_PCH_GPIO_USE_SEL2), GPIO_In_63_32);
      }

      GPIO_In_63_32 = MrcOemInPort32 ((U16) (GPIOBase + R_PCH_GPIO_IO_SEL2));
      if ((GPIO_In_63_32 & (MRC_BIT28 | MRC_BIT14 | MRC_BIT13)) != 0) {
        GPIO_In_63_32 &= ~(MRC_BIT28 | MRC_BIT14 | MRC_BIT13);
        MrcOemOutPort32 ((U16) (GPIOBase + R_PCH_GPIO_IO_SEL2), GPIO_In_63_32);
      }
    }
#endif // MRC_MINIBIOS_BUILD

    GPIO_In_31_0   = MrcOemInPort32 ((U16) (GPIOBase + R_PCH_GPIO_LVL));
    GPIO_In_63_32  = MrcOemInPort32 ((U16) (GPIOBase + R_PCH_GPIO_LVL2));
    GPIO_Out_31_0  = GPIO_In_31_0;
    GPIO_Out_63_32 = GPIO_In_63_32;

    for (Index = 0; Index < (sizeof (MemoryVoltageTable) / sizeof (MemoryVoltageTable[0])); Index++) {
      if (VddVoltage >= MemoryVoltageTable[Index]) {
        break;
      }
    }

#ifdef EMBEDDED_FLAG
    if (Inputs->BoardType == btCRBEMB) {
      //
      // Set GP24 to the required value.
      //
      Current = (((GPIO_Out_31_0 & MRC_BIT24) >> 22) ^ MRC_BIT2) | MRC_BIT1 | MRC_BIT0;
      (Index & MRC_BIT1) ? (GPIO_Out_31_0  &= (~MRC_BIT24)) : (GPIO_Out_31_0  |= MRC_BIT24);
    } else
#endif

    if ((Inputs->MobilePlatform == TRUE) && (Inputs->BoardType != btUser4)) {
      //
      // Set GP8, GP24, and GP46 to the required value.
      //
      Current = (((GPIO_Out_31_0 & MRC_BIT24) >> 22) | ((GPIO_Out_63_32 & MRC_BIT14) >> 13) | ((GPIO_Out_31_0 & MRC_BIT8) >> 8));
      (Index & MRC_BIT2) ? (GPIO_Out_31_0  |= MRC_BIT24) : (GPIO_Out_31_0  &= (~MRC_BIT24));
      (Index & MRC_BIT1) ? (GPIO_Out_63_32 |= MRC_BIT14) : (GPIO_Out_63_32 &= (~MRC_BIT14));
      (Index & MRC_BIT0) ? (GPIO_Out_31_0  |= MRC_BIT8)  : (GPIO_Out_31_0  &= (~MRC_BIT8));
    } else if ((Inputs->MobilePlatform == FALSE) && (Inputs->BoardType == btCRBDT)) {
      //
      // Set GP45, GP46, and GP60 to the required value.
      //
      Current = (((GPIO_Out_63_32 & MRC_BIT28) >> 26) | ((GPIO_Out_63_32 & MRC_BIT14) >> 13) | ((GPIO_Out_63_32 & MRC_BIT13) >> 13));
      (Index & MRC_BIT2) ? (GPIO_Out_63_32 |= MRC_BIT28) : (GPIO_Out_63_32 &= (~MRC_BIT28));
      (Index & MRC_BIT1) ? (GPIO_Out_63_32 |= MRC_BIT14) : (GPIO_Out_63_32 &= (~MRC_BIT14));
      (Index & MRC_BIT0) ? (GPIO_Out_63_32 |= MRC_BIT13) : (GPIO_Out_63_32 &= (~MRC_BIT13));
    } else {
      Current = 4;
    }

    MRC_DEBUG_MSG (&Inputs->Debug, MSG_LEVEL_NOTE, "Current VddVoltage is %u mV\n", MemoryVoltageTable[Current]);
    if ((GPIO_In_31_0 != GPIO_Out_31_0) || (GPIO_In_63_32 != GPIO_Out_63_32)) {
        MRC_DEBUG_MSG (&Inputs->Debug, MSG_LEVEL_NOTE, "**** VddVoltage updated to %u mV\n", VddVoltage);
        MrcOemOutPort32 ((U16) (GPIOBase + R_PCH_GPIO_LVL), GPIO_Out_31_0);
        MrcOemOutPort32 ((U16) (GPIOBase + R_PCH_GPIO_LVL2), GPIO_Out_63_32);
        Status = TRUE;
    }

    //
    // Increase the VddSettleWaitTime by the amount requested in the Input structure
    //
    *VddSettleWaitTime += Inputs->VddSettleWaitTime;

    //
    // Either update was already done or change is not necessary every time this is called
    //
    Outputs->VddVoltageDone = TRUE;
  }

  return (Status);
}

/**
  Hook before normal mode is enabled.

  @param[in, out] MrcData  - The MRC "global data" area.

  @retval Nothing.
**/
void
MrcOemBeforeNormalModeTestMenu (
  IN OUT MrcParameters *const MrcData
  )
{

  return;
}

/**
  Hook after normal mode is enabled

  @param[in] MrcData  - The MRC "global data" area.

  @retval Nothing.
**/
void
MrcOemAfterNormalModeTestMenu (
  IN MrcParameters *MrcData
  )
{

  MrcThermalOverwrites (MrcData);

  // @todo: Add lates code  DDR Thermal Management, throttling control. Also UP CLTT code
  //
// AMI_OVERRIDE_FOR_UPSERVER_SUPPORT
#ifdef UPSERVER_SUPPORT
  MrcCltmInit (MrcData);
#endif // UPSERVER_SUPPORT
// AMI_OVERRIDE_FOR_UPSERVER_SUPPORT
  return;
}

/**
  Overwrite Thermal settings

  @param[in] MrcData  - The MRC "global data" area.

  @retval Nothing.
**/
void
MrcThermalOverwrites (
  IN MrcParameters *MrcData
  )
{
  MrcInput                                        *Inputs;
  MrcOutput                                       *Outputs;
  MrcDebug                                        *Debug;
  MrcDdrType                                      DdrType;
  ThermalMngmtEn                                  *ThermalEnables;
  U8                                              Channel;
  U32                                             Offset;
  PCU_CR_DDR_PTM_CTL_PCU_STRUCT                   DdrPtmCtl;
  PCU_CR_DDR_ENERGY_SCALEFACTOR_PCU_STRUCT        DdrEnergyScaleFactor;
  PCU_CR_DDR_RAPL_CHANNEL_POWER_FLOOR_PCU_STRUCT  DdrRaplChannelPowerFloor;
  PCU_CR_DDR_RAPL_LIMIT_PCU_STRUCT                DdrRaplLimit;
  PCU_CR_DDR_WARM_THRESHOLD_CH0_PCU_STRUCT        DdrWarmThresholdCh0;
  PCU_CR_DDR_WARM_THRESHOLD_CH1_PCU_STRUCT        DdrWarmThresholdCh1;
  PCU_CR_DDR_HOT_THRESHOLD_CH0_PCU_STRUCT         DdrHotThresholdCh0;
  PCU_CR_DDR_HOT_THRESHOLD_CH1_PCU_STRUCT         DdrHotThresholdCh1;
  PCU_CR_DDR_WARM_BUDGET_CH0_PCU_STRUCT           DdrWarmBudgetCh0;
  PCU_CR_DDR_WARM_BUDGET_CH1_PCU_STRUCT           DdrWarmBudgetCh1;
  PCU_CR_DDR_HOT_BUDGET_CH0_PCU_STRUCT            DdrHotBudgetCh0;
  PCU_CR_DDR_HOT_BUDGET_CH1_PCU_STRUCT            DdrHotBudgetCh1;
  MCHBAR_CH0_CR_PM_DIMM_IDLE_ENERGY_STRUCT        PmDimmIdleEnergy;
  MCHBAR_CH0_CR_PM_DIMM_PD_ENERGY_STRUCT          PmDimmPdEnergy;
  MCHBAR_CH0_CR_PM_DIMM_ACT_ENERGY_STRUCT         PmDimmActEnergy;
  MCHBAR_CH0_CR_PM_DIMM_RD_ENERGY_STRUCT          PmDimmRdEnergy;
  MCHBAR_CH0_CR_PM_DIMM_WR_ENERGY_STRUCT          PmDimmWrEnergy;
  MCHBAR_CH0_CR_PM_THRT_CKE_MIN_STRUCT            PmThrtCkeMin;
  MCDECS_CR_PM_SREF_CONFIG_MCMAIN_STRUCT          PmSrefConfig;

  Inputs          = &MrcData->SysIn.Inputs;
  Debug           = &Inputs->Debug;
  ThermalEnables  = &Inputs->ThermalEnables;
  Outputs         = &MrcData->SysOut.Outputs;
  DdrType         = Outputs->DdrType;
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "...Thermal Overwrite ...\n");

  if (Inputs->ThermalEnables.UserPowerWeightsEn) {
    //
    // ENERGY SCALE FACTOR
    //
    DdrEnergyScaleFactor.Data             = 0;
    DdrEnergyScaleFactor.Bits.SCALEFACTOR = ThermalEnables->EnergyScaleFact;
    MRC_DEBUG_MSG (
      Debug,
      MSG_LEVEL_NOTE,
      "DDR_ENERGY_SCALEFACTOR %Xh: %Xh \n",
      PCU_CR_DDR_ENERGY_SCALEFACTOR_PCU_REG,
      DdrEnergyScaleFactor.Data
      );
    MrcWriteCR (MrcData, PCU_CR_DDR_ENERGY_SCALEFACTOR_PCU_REG, DdrEnergyScaleFactor.Data);

    //
    // RAPL POWER FLOOR
    //
    DdrRaplChannelPowerFloor.Data     = 0;
    DdrRaplChannelPowerFloor.Bits.CH0 = ThermalEnables->RaplPwrFl[0];
    DdrRaplChannelPowerFloor.Bits.CH1 = ThermalEnables->RaplPwrFl[1];
    MRC_DEBUG_MSG (
      Debug,
      MSG_LEVEL_NOTE,
      "DDR_RAPL_CHANNEL_POWER_FLOOR %Xh: %Xh \n",
      PCU_CR_DDR_RAPL_CHANNEL_POWER_FLOOR_PCU_REG,
      DdrRaplChannelPowerFloor.Data
      );
    MrcWriteCR (MrcData, PCU_CR_DDR_RAPL_CHANNEL_POWER_FLOOR_PCU_REG, DdrRaplChannelPowerFloor.Data);
  }

  //
  // RAPL LIMIT
  //
  DdrRaplLimit.Data                       = 0;
  DdrRaplLimit.Bits.LIMIT1_TIME_WINDOW_X  = ThermalEnables->RaplLim1WindX;
  DdrRaplLimit.Bits.LIMIT1_TIME_WINDOW_Y  = ThermalEnables->RaplLim1WindY;
  DdrRaplLimit.Bits.LIMIT1_ENABLE         = ThermalEnables->RaplLim1Ena;
  DdrRaplLimit.Bits.LIMIT1_POWER          = ThermalEnables->RaplLim1Pwr;
  DdrRaplLimit.Bits.LOCKED                = ThermalEnables->RaplLim2Lock;
  DdrRaplLimit.Bits.LIMIT2_TIME_WINDOW_X  = ThermalEnables->RaplLim2WindX;
  DdrRaplLimit.Bits.LIMIT2_TIME_WINDOW_Y  = ThermalEnables->RaplLim2WindY;
  DdrRaplLimit.Bits.LIMIT2_ENABLE         = ThermalEnables->RaplLim2Ena;
  DdrRaplLimit.Bits.LIMIT2_POWER          = ThermalEnables->RaplLim2Pwr;
  MRC_DEBUG_MSG (
    Debug,
    MSG_LEVEL_NOTE,
    "DDR_RAPL_LIMIT1 %Xh: %Xh \n",
    PCU_CR_DDR_RAPL_LIMIT_PCU_REG,
    DdrRaplLimit.Data32[0]
    );
  MRC_DEBUG_MSG (
    Debug,
    MSG_LEVEL_NOTE,
    "DDR_RAPL_LIMIT2 %Xh: %Xh \n",
    PCU_CR_DDR_RAPL_LIMIT_PCU_REG + 4,
    DdrRaplLimit.Data32[1]
    );
  MrcWriteCR (MrcData, PCU_CR_DDR_RAPL_LIMIT_PCU_REG, DdrRaplLimit.Data32[0]);
  MrcWriteCR (MrcData, PCU_CR_DDR_RAPL_LIMIT_PCU_REG + 4, DdrRaplLimit.Data32[1]);

  //
  // DDR WARM AND HOT THRESHOLD
  //
  DdrWarmThresholdCh0.Data        = 0;
  DdrWarmThresholdCh0.Bits.DIMM1  = ThermalEnables->WarmThreshold[0][1];
  DdrWarmThresholdCh0.Bits.DIMM0  = ThermalEnables->WarmThreshold[0][0];
  MRC_DEBUG_MSG (
    Debug,
    MSG_LEVEL_NOTE,
    "DDR_WARM_THRESHOLD_CH0 %Xh: %Xh \n",
    PCU_CR_DDR_WARM_THRESHOLD_CH0_PCU_REG,
    DdrWarmThresholdCh0.Data
    );
  MrcWriteCR (MrcData, PCU_CR_DDR_WARM_THRESHOLD_CH0_PCU_REG, DdrWarmThresholdCh0.Data);

  DdrWarmThresholdCh1.Data        = 0;
  DdrWarmThresholdCh1.Bits.DIMM1  = ThermalEnables->WarmThreshold[1][1];
  DdrWarmThresholdCh1.Bits.DIMM0  = ThermalEnables->WarmThreshold[1][0];
  MRC_DEBUG_MSG (
    Debug,
    MSG_LEVEL_NOTE,
    "DDR_WARM_THRESHOLD_CH1 %Xh: %Xh \n",
    PCU_CR_DDR_WARM_THRESHOLD_CH1_PCU_REG,
    DdrWarmThresholdCh1.Data
    );
  MrcWriteCR (MrcData, PCU_CR_DDR_WARM_THRESHOLD_CH1_PCU_REG, DdrWarmThresholdCh1.Data);

  DdrHotThresholdCh0.Data       = 0;
  DdrHotThresholdCh0.Bits.DIMM1 = ThermalEnables->HotThreshold[0][1];
  DdrHotThresholdCh0.Bits.DIMM0 = ThermalEnables->HotThreshold[0][0];
  MRC_DEBUG_MSG (
    Debug,
    MSG_LEVEL_NOTE,
    "DDR_HOT_THRESHOLD_CH0 %Xh: %Xh \n",
    PCU_CR_DDR_HOT_THRESHOLD_CH0_PCU_REG,
    DdrHotThresholdCh0.Data
    );
  MrcWriteCR (MrcData, PCU_CR_DDR_HOT_THRESHOLD_CH0_PCU_REG, DdrHotThresholdCh0.Data);

  DdrHotThresholdCh1.Data       = 0;
  DdrHotThresholdCh1.Bits.DIMM1 = ThermalEnables->HotThreshold[1][1];
  DdrHotThresholdCh1.Bits.DIMM0 = ThermalEnables->HotThreshold[1][0];
  MRC_DEBUG_MSG (
    Debug,
    MSG_LEVEL_NOTE,
    "DDR_HOT_THRESHOLD_CH1 %Xh: %Xh \n",
    PCU_CR_DDR_HOT_THRESHOLD_CH1_PCU_REG,
    DdrHotThresholdCh1.Data
    );
  MrcWriteCR (MrcData, PCU_CR_DDR_HOT_THRESHOLD_CH1_PCU_REG, DdrHotThresholdCh1.Data);

  //
  // DDR WARM AND HOT BUDGET
  //
  DdrWarmBudgetCh0.Data       = 0;
  DdrWarmBudgetCh0.Bits.DIMM1 = ThermalEnables->WarmBudget[0][1];
  DdrWarmBudgetCh0.Bits.DIMM0 = ThermalEnables->WarmBudget[0][0];
  MRC_DEBUG_MSG (
    Debug,
    MSG_LEVEL_NOTE,
    "DDR_WARM_BUDGET_CH0 %Xh: %Xh \n",
    PCU_CR_DDR_WARM_BUDGET_CH0_PCU_REG,
    DdrWarmBudgetCh0.Data
    );
  MrcWriteCR (MrcData, PCU_CR_DDR_WARM_BUDGET_CH0_PCU_REG, DdrWarmBudgetCh0.Data);

  DdrWarmBudgetCh1.Data       = 0;
  DdrWarmBudgetCh1.Bits.DIMM1 = ThermalEnables->WarmBudget[1][1];
  DdrWarmBudgetCh1.Bits.DIMM0 = ThermalEnables->WarmBudget[1][0];
  MRC_DEBUG_MSG (
    Debug,
    MSG_LEVEL_NOTE,
    "DDR_WARM_BUDGET_CH1 %Xh: %Xh \n",
    PCU_CR_DDR_WARM_BUDGET_CH1_PCU_REG,
    DdrWarmBudgetCh1.Data
    );
  MrcWriteCR (MrcData, PCU_CR_DDR_WARM_BUDGET_CH1_PCU_REG, DdrWarmBudgetCh1.Data);

  DdrHotBudgetCh0.Data        = 0;
  DdrHotBudgetCh0.Bits.DIMM1  = ThermalEnables->HotBudget[0][1];
  DdrHotBudgetCh0.Bits.DIMM0  = ThermalEnables->HotBudget[0][0];
  MRC_DEBUG_MSG (
    Debug,
    MSG_LEVEL_NOTE,
    "DDR_HOT_BUDGET_CH0 %Xh: %Xh \n",
    PCU_CR_DDR_HOT_BUDGET_CH0_PCU_REG,
    DdrHotBudgetCh0.Data
    );
  MrcWriteCR (MrcData, PCU_CR_DDR_HOT_BUDGET_CH0_PCU_REG, DdrHotBudgetCh0.Data);

  DdrHotBudgetCh1.Data        = 0;
  DdrHotBudgetCh1.Bits.DIMM1  = ThermalEnables->HotBudget[1][1];
  DdrHotBudgetCh1.Bits.DIMM0  = ThermalEnables->HotBudget[1][0];
  MRC_DEBUG_MSG (
    Debug,
    MSG_LEVEL_NOTE,
    "DDR_HOT_BUDGET_CH1 %Xh: %Xh \n",
    PCU_CR_DDR_HOT_BUDGET_CH1_PCU_REG,
    DdrHotBudgetCh1.Data
    );
  MrcWriteCR (MrcData, PCU_CR_DDR_HOT_BUDGET_CH1_PCU_REG, DdrHotBudgetCh1.Data);

  for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
    if (MrcChannelExist (Outputs, Channel)) {
      if (Inputs->ThermalEnables.UserPowerWeightsEn) {
        PmDimmIdleEnergy.Data                   = 0;
        PmDimmIdleEnergy.Bits.DIMM1_IDLE_ENERGY = ThermalEnables->IdleEnergy[Channel][1];
        PmDimmIdleEnergy.Bits.DIMM0_IDLE_ENERGY = ThermalEnables->IdleEnergy[Channel][0];
        Offset = MCHBAR_CH0_CR_PM_DIMM_IDLE_ENERGY_REG +
          (MCHBAR_CH1_CR_PM_DIMM_IDLE_ENERGY_REG - MCHBAR_CH0_CR_PM_DIMM_IDLE_ENERGY_REG) * Channel;
        MRC_DEBUG_MSG (
          Debug,
          MSG_LEVEL_NOTE,
          "C%u PM_DIMM_IDLE_ENERGY %Xh: %Xh \n",
          Channel,
          Offset,
          PmDimmIdleEnergy.Data
          );
        MrcWriteCR (MrcData, Offset, PmDimmIdleEnergy.Data);

        PmDimmPdEnergy.Data                 = 0;
        PmDimmPdEnergy.Bits.DIMM1_PD_ENERGY = ThermalEnables->PdEnergy[Channel][1];
        PmDimmPdEnergy.Bits.DIMM0_PD_ENERGY = ThermalEnables->PdEnergy[Channel][0];
        Offset = MCHBAR_CH0_CR_PM_DIMM_PD_ENERGY_REG +
          (MCHBAR_CH1_CR_PM_DIMM_PD_ENERGY_REG - MCHBAR_CH0_CR_PM_DIMM_PD_ENERGY_REG) * Channel;
        MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "C%u PM_DIMM_PD_ENERGY %Xh: %Xh \n", Channel, Offset, PmDimmPdEnergy.Data);
        MrcWriteCR (MrcData, Offset, PmDimmPdEnergy.Data);

        PmDimmActEnergy.Data                  = 0;
        PmDimmActEnergy.Bits.DIMM1_ACT_ENERGY = ThermalEnables->ActEnergy[Channel][1];
        PmDimmActEnergy.Bits.DIMM0_ACT_ENERGY = ThermalEnables->ActEnergy[Channel][0];
        Offset = MCHBAR_CH0_CR_PM_DIMM_ACT_ENERGY_REG +
          (MCHBAR_CH1_CR_PM_DIMM_ACT_ENERGY_REG - MCHBAR_CH0_CR_PM_DIMM_ACT_ENERGY_REG) * Channel;
        MRC_DEBUG_MSG (
          Debug,
          MSG_LEVEL_NOTE,
          "C%u PM_DIMM_ACT_ENERGY %Xh: %Xh \n",
          Channel,
          Offset,
          PmDimmActEnergy.Data
          );
        MrcWriteCR (MrcData, Offset, PmDimmActEnergy.Data);

        PmDimmRdEnergy.Data                 = 0;
        PmDimmRdEnergy.Bits.DIMM1_RD_ENERGY = ThermalEnables->RdEnergy[Channel][1];
        PmDimmRdEnergy.Bits.DIMM0_RD_ENERGY = ThermalEnables->RdEnergy[Channel][0];
        Offset = MCHBAR_CH0_CR_PM_DIMM_RD_ENERGY_REG +
          (MCHBAR_CH1_CR_PM_DIMM_RD_ENERGY_REG - MCHBAR_CH0_CR_PM_DIMM_RD_ENERGY_REG) * Channel;
        MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "C%u PM_DIMM_RD_ENERGY %Xh: %Xh \n", Channel, Offset, PmDimmRdEnergy.Data);
        MrcWriteCR (MrcData, Offset, PmDimmRdEnergy.Data);

        PmDimmWrEnergy.Data                 = 0;
        PmDimmWrEnergy.Bits.DIMM1_WR_ENERGY = ThermalEnables->WrEnergy[Channel][1];
        PmDimmWrEnergy.Bits.DIMM0_WR_ENERGY = ThermalEnables->WrEnergy[Channel][0];
        Offset = MCHBAR_CH0_CR_PM_DIMM_WR_ENERGY_REG +
          (MCHBAR_CH1_CR_PM_DIMM_WR_ENERGY_REG - MCHBAR_CH0_CR_PM_DIMM_WR_ENERGY_REG) * Channel;
        MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "C%u PM_DIMM_WR_ENERGY %Xh: %Xh \n", Channel, Offset, PmDimmWrEnergy.Data);
        MrcWriteCR (MrcData, Offset, PmDimmWrEnergy.Data);
      }

      PmThrtCkeMin.Data                   = 0;
#ifdef ULT_FLAG
      if (DdrType == MRC_DDR_TYPE_LPDDR3) {
        PmThrtCkeMin.Bits.CKE_MIN_DEFEATURE = ThermalEnables->ThrtCkeMinDefeatLpddr;
        PmThrtCkeMin.Bits.CKE_MIN           = ThermalEnables->ThrtCkeMinTmrLpddr;
      } else
#endif // ULT_FLAG
      {
        PmThrtCkeMin.Bits.CKE_MIN_DEFEATURE = ThermalEnables->ThrtCkeMinDefeat;
        PmThrtCkeMin.Bits.CKE_MIN           = ThermalEnables->ThrtCkeMinTmr;
      }
      Offset = MCHBAR_CH0_CR_PM_THRT_CKE_MIN_REG +
        (MCHBAR_CH1_CR_PM_THRT_CKE_MIN_REG - MCHBAR_CH0_CR_PM_THRT_CKE_MIN_REG) * Channel;
      MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "C%u PM_THRT_CKE_MIN %Xh: %Xh \n", Channel, Offset, PmThrtCkeMin.Data);
      MrcWriteCR (MrcData, Offset, PmThrtCkeMin.Data);
    }
  }

  PmSrefConfig.Data             = 0;
  PmSrefConfig.Bits.SR_Enable   = ThermalEnables->SrefCfgEna;
  PmSrefConfig.Bits.Idle_timer  = ThermalEnables->SrefCfgIdleTmr;
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "PM_SREF_CONFIG %Xh: %Xh\n", MCDECS_CR_PM_SREF_CONFIG_MCMAIN_REG, PmSrefConfig.Data);
  MrcWriteCR (MrcData, MCDECS_CR_PM_SREF_CONFIG_MCMAIN_REG, PmSrefConfig.Data);

  //
  // POWER THERMAL MANAGEMENT CONTROL
  //
  DdrPtmCtl.Data                    = MrcReadCR (MrcData, PCU_CR_DDR_PTM_CTL_PCU_REG);
  DdrPtmCtl.Bits.OLTM_ENABLE        = ThermalEnables->EnableOltm;
  DdrPtmCtl.Bits.CLTM_ENABLE        = ThermalEnables->EnableCltm;
  DdrPtmCtl.Bits.EXTTS_ENABLE       = ThermalEnables->EnableExtts;
  DdrPtmCtl.Bits.REFRESH_2X_MODE    = ThermalEnables->Refresh2X;
#ifdef ULT_FLAG
  if (DdrType == MRC_DDR_TYPE_LPDDR3) {
    DdrPtmCtl.Bits.PDWN_CONFIG_CTL = ThermalEnables->EnablePwrDnLpddr;
    //
    // When enabling 2x Refresh for LPDDR through the Mailbox we must
    // ensure DDR_PTM_CTL.DISABLE_DRAM_TS = 0.  Thus we ignore LpddrThermalSensor.
    //
    if (Inputs->RefreshRate2x == FALSE) {
      DdrPtmCtl.Bits.DISABLE_DRAM_TS = (ThermalEnables->LpddrThermalSensor == 0) ? 1 : 0;
    } else {
       MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "Ignoring ThermalEnables->LpddrThermal Sensor as 2x Refresh is enabled\n");
    }
  } else
#endif // ULT_FLAG
  {
    DdrPtmCtl.Bits.PDWN_CONFIG_CTL = ThermalEnables->EnablePwrDn;
  }
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "DDR_PTM_CTL %Xh: %Xh\n", PCU_CR_DDR_PTM_CTL_PCU_REG, DdrPtmCtl.Data);
  MrcWriteCR (MrcData, PCU_CR_DDR_PTM_CTL_PCU_REG, DdrPtmCtl.Data);

  return;
}


/**
  this function use by the OEM to do dedicated task during the MRC.

  @param[in] MrcData           - include all the MRC data
  @param[in] OemStatusCommand  - A command that indicates the task to perform.
  @param[in] ptr               - general ptr for general use.

  @retval The status of the task.
**/
MrcStatus
MrcOemCheckPoint (
  IN MrcParameters        *MrcData,
  IN MRC_OemStatusCommand OemStatusCommand,
  IN void                 *ptr
  )
{
  MrcInput  *Inputs;
  MrcOutput *Outputs;
  MrcStatus Status;
  MrcDdrType DdrType;

  Status  = mrcSuccess;
  Inputs  = &MrcData->SysIn.Inputs;
  Outputs = &MrcData->SysOut.Outputs;
  DdrType = Outputs->DdrType;


  switch (OemStatusCommand) {
  case OemSpdProcessingRun:
    break;

  case OemPreTraining:
    break;

  case OemMcTrainingRun:
    break;

  case OemEarlyCommandTraining:
    if (DdrType == MRC_DDR_TYPE_LPDDR3) {
      Status = mrcSuccess;  // This is required for LPDDR
    } else if (!Inputs->TrainingEnables.ECT) {
      Status = mrcFail; // Skip this training step
    }
    break;

#ifdef ULT_FLAG
  case OemJedecInitLpddr3:    // MrcJedecInitLpddr3
    if (DdrType == MRC_DDR_TYPE_LPDDR3) {
      Status = mrcSuccess;
    } else {
      Status = mrcFail;  // Skip this step for non-LPDDR
    }
    break;
#endif // ULT_FLAG

  case OemSenseAmpTraining:
    if (!Inputs->TrainingEnables.SOT) {
        Status = mrcFail; // Skip this training step
    }
    break;

  case OemReadMprTraining:
    if (!Inputs->TrainingEnables.RDMPRT) {
        Status = mrcFail; // Skip this training step
    }
    break;

  case OemReceiveEnable:
    if (!Inputs->TrainingEnables.RCVET) {
        Status = mrcFail; // Skip this training step
    }
    break;

  case OemJedecWriteLeveling:
    if (!Inputs->TrainingEnables.JWRL) {
        Status = mrcFail; // Skip this training step
    }
    break;

  case OemWriteLeveling:
    if (!Inputs->TrainingEnables.FWRL) {
        Status = mrcFail; // Skip this training step
    }
    break;

  case OemWriteDqDqs:
    if (!Inputs->TrainingEnables.WRTC1D) {
        Status = mrcFail; // Skip this training step
    }
    break;

  case OemReadDqDqs:
    if (!Inputs->TrainingEnables.RDTC1D) {
        Status = mrcFail; // Skip this training step
    }
    break;

  case OemDimmODTTraining:
    if (!Inputs->TrainingEnables.DIMMODTT) {
      Status = mrcFail; // Skip this training step
    }
    break;

  case OemDimmRonTraining:
    if (!Inputs->TrainingEnables.DIMMRONT) {
      Status = mrcFail; // Skip this training step
    }
    break;

  case OemWriteSlewRate:
    if (!Inputs->TrainingEnables.WRSRT) {
      Status = mrcFail; // Skip this training step
    }
    break;

  case OemDimmODT1dTraining:
    if (!Inputs->TrainingEnables.DIMMODTT1D) {
      Status = mrcFail; // Skip this training step
    }
    break;

  case OemWriteDriveStrength:
    if (!Inputs->TrainingEnables.WRDST) {
        Status = mrcFail; // Skip this training step
    }
    break;

  case OemWriteEQTraining:
    if (!Inputs->TrainingEnables.WREQT) {
        Status = mrcFail; // Skip this training step
    }
    break;

  case OemReadODTTraining:
    if (!Inputs->TrainingEnables.RDODTT) {
        Status = mrcFail; // Skip this training step
    }
    break;

  case OemReadEQTraining:
    if (!Inputs->TrainingEnables.RDEQT) {
        Status = mrcFail; // Skip this training step
    }
    break;

  case OemPostTraining:
    if (DdrType == MRC_DDR_TYPE_LPDDR3) {
      Status = mrcFail; // Skip this training step
      break;
    }
    break;

  case OemReadAmplifierPower:
    if (!Inputs->TrainingEnables.RDAPT) {
        Status = mrcFail; // Skip this training step
    }
    break;

  case OemOptimizeComp:
    break;

  case OemWriteDqDqs2D:
    if (!Inputs->TrainingEnables.WRTC2D) {
        Status = mrcFail; // Skip this training step
    }
    break;

  case OemReadDqDqs2D:
    if (!Inputs->TrainingEnables.RDTC2D) {
        Status = mrcFail; // Skip this training step
    }
    break;

  case OemCmdVoltCentering:
    if (!Inputs->TrainingEnables.CMDVC) {
        Status = mrcFail; // Skip this training step
    }
    break;

  case OemWriteVoltCentering2D:
    if (!Inputs->TrainingEnables.WRVC2D) {
        Status = mrcFail; // Skip this training step
    }
    break;

  case OemReadVoltCentering2D:
    if (!Inputs->TrainingEnables.RDVC2D) {
        Status = mrcFail; // Skip this training step
    }
    break;

  case OemLateCommandTraining:
    if (!Inputs->TrainingEnables.LCT) {
      Status = mrcFail; // Skip this training step
    }
    break;

  case OemRoundTripLatency:
    if (!Inputs->TrainingEnables.RTL) {
        Status = mrcFail; // Skip this training step
    }
    break;

  case OemTurnAroundTimes:
    //
    // @todo: TAT has to be updated for LPDDR3, skip it for now.
    //
    if ((!Inputs->TrainingEnables.TAT) || (DdrType == MRC_DDR_TYPE_LPDDR3)) {
      Status = mrcFail; // Skip this training step
    }
    break;

#ifdef ULT_FLAG
    case OemRcvEnCentering1D:
      if ((!Inputs->TrainingEnables.RCVENC1D) || (DdrType != MRC_DDR_TYPE_LPDDR3)) {
        Status = mrcFail;  // Skip this step for non-LPDDR
      }
      break;
#endif // ULT_FLAG

  case OemRetrainMarginCheck:
    if (!Inputs->TrainingEnables.RMC) {
        Status = mrcFail; // Skip this training step
    }
    break;


  case OemRmt:
    if (!Inputs->TrainingEnables.RMT) {
        Status = mrcFail; // Skip this training step
    }
    break;

  case OemMemTest:
    if (!Inputs->TrainingEnables.MEMTST) {
        Status = mrcFail; // Skip this training step
    }
    break;

  case OemAliasCheck:
    if (!Inputs->TrainingEnables.ALIASCHK) {
      Status = mrcFail; // Skip this training step
    }
    break;

  case OemBeforeNormalMode:
    MrcOemBeforeNormalModeTestMenu (MrcData);
    break;

  case OemAfterNormalMode:
    MrcOemAfterNormalModeTestMenu (MrcData);
    break;

  case OemFrequencySetDone:
#ifdef SSA_FLAG
#ifndef MRC_MINIBIOS_BUILD
    SsaBiosInitialize (MrcData);
#endif
#endif // SSA_FLAG
    break;

  default:
    break;
  }

  return Status;
}

/**
  This function display on port 80 number.
  It can be different debug interface.
  This function can be use for any debug ability according to OEM requirements.

  @param[in] MrcData            - Mrc Global Data
  @param[in] DisplayDebugNumber - the number to display on port 80.

  @retval Nothing
**/
void
MrcOemDebugHook (
  IN MrcParameters *MrcData,
  IN U16           DisplayDebugNumber
  )
{
  MrcInput  *Inputs;
  U8        temp;
  U16       BreakCmos;

  Inputs                    = &MrcData->SysIn.Inputs;
  Inputs->Debug.PostCode[1] = DisplayDebugNumber;
  MrcOemOutPort16 (0x80, DisplayDebugNumber);
  MRC_DEBUG_MSG (&Inputs->Debug, MSG_LEVEL_NOTE, "Post Code: 0x%X\n", DisplayDebugNumber);

  //
  // Check if we should break on this post code.
  //
  do {
    temp = RtcRead (MRC_POST_CODE_LOW_BYTE_ADDR);
    BreakCmos = (RtcRead (MRC_POST_CODE_HIGH_BYTE_ADDR) << 8) | temp;
  } while (DisplayDebugNumber == BreakCmos);

#ifdef SSA_FLAG
#ifndef MRC_MINIBIOS_BUILD
  if ((void *) (Inputs->SsaCallbackPpi) != NULL) {
    (((SSA_BIOS_CALLBACKS_PPI *) (Inputs->SsaCallbackPpi))->MrcCheckpoint) ((EFI_PEI_SERVICES **) (Inputs->Debug.Stream), ((SSA_BIOS_CALLBACKS_PPI *)Inputs->SsaCallbackPpi), DisplayDebugNumber, NULL);
  }
#endif
#endif // SSA_FLAG

  return;
}

#ifdef MRC_DEBUG_PRINT
/**
  Print the input parameters to the debug message output port.

  @param[in] MrcData - The MRC global data.

  @retval mrcSuccess
**/
MrcStatus
MrcPrintInputParameters (
  IN MrcParameters *const MrcData
  )
{
  const MrcDebug                        *Debug;
  const MrcInput                        *Inputs;
  const MrcControllerIn                 *ControllerIn;
  const MrcChannelIn                    *ChannelIn;
  const MrcDimmIn                       *DimmIn;
  const TrainingStepsEn                 *TrainingSteps;
  U8                                    Controller;
  U8                                    Channel;
  U8                                    Dimm;

  Inputs = &MrcData->SysIn.Inputs;
  Debug  = &Inputs->Debug;

  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "*************************************\n");
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "*****MRC INPUT PARAMS DUMP START*****\n");
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "*************************************\n");
  //
  // The following are system level definitions. All memory controllers in the system are set to these values.
  //
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "Debug.Stream : %Xh\n", Inputs->Debug.Stream);
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "Debug.Level : %Xh\n", Inputs->Debug.Level);

  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "FreqMax : %u\n", Inputs->FreqMax);
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "Ratio : %u\n", Inputs->Ratio);
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "RefClk : %uMHz\n", (Inputs->RefClk == MRC_REF_CLOCK_100) ? 100 : 133);
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "BClk : %uHz\n", Inputs->BClkFrequency);
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "BoardType : %Xh\n", Inputs->BoardType);
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "CpuStepping : %Xh\n", Inputs->CpuStepping);
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "CpuModel : %Xh\n", Inputs->CpuModel);
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "GraphicsStolenSize : %Xh\n", Inputs->GraphicsStolenSize);
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "GraphicsGttSize : %Xh\n", Inputs->GraphicsGttSize);

  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "%s.Seconds : %u\n", BaseTimeString, Inputs->BaseTime.Seconds);
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "%s.Minutes : %u\n", BaseTimeString, Inputs->BaseTime.Minutes);
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "%s.Hours : %u\n", BaseTimeString, Inputs->BaseTime.Hours);
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "%s.DayOfMonth : %u\n", BaseTimeString, Inputs->BaseTime.DayOfMonth);
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "%s.Month : %u\n", BaseTimeString, Inputs->BaseTime.Month);
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "%s.Year : %u\n", BaseTimeString, Inputs->BaseTime.Year);

  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "Iteration : %Xh\n", Inputs->Iteration);
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "MrcMode : %Xh\n", Inputs->MrcMode);
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "VddVoltage : %u mV\n", Inputs->VddVoltage);
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "MemoryProfile : %Xh\n", Inputs->MemoryProfile);
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "BootMode : %Xh\n", Inputs->BootMode);
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "TxtFlag : %Xh\n", Inputs->TxtFlag);
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "MobilePlatform : %Xh\n", Inputs->MobilePlatform);
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "EccSupport : %Xh\n", Inputs->EccSupport);
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "SetRxDqs32 : %Xh\n", Inputs->SetRxDqs32);
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "GfxIsVersatileAcceleration : %Xh\n", Inputs->GfxIsVersatileAcceleration);
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "ScramblerEnable : %Xh\n", Inputs->ScramblerEnable);
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "McLock : %Xh\n", Inputs->McLock);
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "RemapEnable : %Xh\n", Inputs->RemapEnable);
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "PowerDownMode : %Xh\n", Inputs->PowerDownMode);
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "PwdwnIdleCounter : %Xh\n", Inputs->PwdwnIdleCounter);
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "RankInterleave : %Xh\n", Inputs->RankInterleave);
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "EnhancedInterleave : %Xh\n", Inputs->EnhancedInterleave);
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "WeaklockEn : %Xh\n", Inputs->WeaklockEn);
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "EnCmdRate : %Xh\n", Inputs->EnCmdRate);
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "CmdTriStateDis : %Xh\n", Inputs->CmdTriStateDis);
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "RefreshRate2x : %Xh\n", Inputs->RefreshRate2x);
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "BaseAddresses\n");
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "  PciE : %Xh\n", Inputs->PciEBaseAddress);
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "  MchBar : %Xh\n", Inputs->MchBarBaseAddress);
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "  Smbus : %Xh\n", Inputs->SmbusBaseAddress);
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "  Gdxc : %Xh\n", Inputs->GdxcBaseAddress);
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "  Hpet : %Xh\n\n", Inputs->HpetBaseAddress);
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "MeStolenSize : %Xh\n", Inputs->MeStolenSize);
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "MmioSize : %Xh\n", Inputs->MmioSize);
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "TsegSize : %Xh\n", Inputs->TsegSize);
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "IedSize : %Xh\n", Inputs->IedSize);
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "DprSize : %Xh\n", Inputs->DprSize);
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "VddSettleWaitTime : %Xh\n", Inputs->VddSettleWaitTime);
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "VccIomV : %Xh\n", Inputs->VccIomV);
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "AutoSelfRefreshSupport : %u\n", Inputs->AutoSelfRefreshSupport);
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "ExtTemperatureSupport : %u\n", Inputs->ExtTemperatureSupport);
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "ChHashEnable : %Xh\n", Inputs->ChHashEnable);
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "ChHashMask : %Xh\n", Inputs->ChHashMask);
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "ChHashInterleaveBit : %Xh\n", Inputs->ChHashInterleaveBit);
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "%sEnable : %Xh\n", GdxcString, Inputs->Gdxc.GdxcEnable);
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "%sIotSize : %Xh\n", GdxcString, Inputs->Gdxc.GdxcIotSize);
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "%sMotSize : %Xh\n", GdxcString, Inputs->Gdxc.GdxcMotSize);
  
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "MemoryTrace: %u\n", Inputs->MemoryTrace);

  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "*************************************\n");
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "*****    MRC TRAINING STEPS     *****\n");
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "*************************************\n");
  TrainingSteps = &Inputs->TrainingEnables;
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "%s : %Xh\n", TrainEnString, Inputs->TrainingEnables);

  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "%s.ECT : %u\n", TrainEnString, TrainingSteps->ECT);
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "%s.SOT : %u\n", TrainEnString, TrainingSteps->SOT);
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "%s.RDMPRT : %u\n", TrainEnString, TrainingSteps->RDMPRT);
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "%s.RCVET : %u\n", TrainEnString, TrainingSteps->RCVET);
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "%s.JWRL : %u\n", TrainEnString, TrainingSteps->JWRL);
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "%s.FWRL : %u\n", TrainEnString, TrainingSteps->FWRL);
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "%s.WRTC1D : %u\n", TrainEnString, TrainingSteps->WRTC1D);
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "%s.RDTC1D : %u\n", TrainEnString, TrainingSteps->RDTC1D);
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "%s.DIMMODTT : %u\n", TrainEnString, TrainingSteps->DIMMODTT);
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "%s.WRDST : %u\n", TrainEnString, TrainingSteps->WRDST);
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "%s.WREQT : %u\n", TrainEnString, TrainingSteps->WREQT);
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "%s.RDODTT : %u\n", TrainEnString, TrainingSteps->RDODTT);
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "%s.RDEQT : %u\n", TrainEnString, TrainingSteps->RDEQT);
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "%s.RDAPT : %u\n", TrainEnString, TrainingSteps->RDAPT);
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "%s.WRTC2D : %u\n", TrainEnString, TrainingSteps->WRTC2D);
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "%s.RDTC2D : %u\n", TrainEnString, TrainingSteps->RDTC2D);
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "%s.WRVC2D : %u\n", TrainEnString, TrainingSteps->WRVC2D);
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "%s.RDVC2D : %u\n", TrainEnString, TrainingSteps->RDVC2D);
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "%s.LCT : %u\n", TrainEnString, TrainingSteps->LCT);
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "%s.RTL : %u\n", TrainEnString, TrainingSteps->RTL);
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "%s.TAT : %u\n", TrainEnString, TrainingSteps->TAT);
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "%s.RMT : %u\n", TrainEnString, TrainingSteps->RMT);
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "%s.MEMTST : %u\n", TrainEnString, TrainingSteps->MEMTST);
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "%s.DIMMODTT1D : %u\n", TrainEnString, TrainingSteps->DIMMODTT1D);
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "%s.WRSRT : %u\n", TrainEnString, TrainingSteps->WRSRT);
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "%s.DIMMRONT : %u\n", TrainEnString, TrainingSteps->DIMMRONT);
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "%s.ALIASCHK : %u\n", TrainEnString, TrainingSteps->ALIASCHK);
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "%s.RCVENC1D : %u\n", TrainEnString, TrainingSteps->RCVENC1D);
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "%s.RMC : %u\n", TrainEnString, TrainingSteps->RMC);

  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "*************************************\n");
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "*****      MRC TIMING DATA      *****\n");
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "*************************************\n");

  for (Controller = 0; Controller < MAX_CONTROLLERS; Controller++) {
    ControllerIn = &Inputs->Controller[Controller];
    MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "Controller[%u] ChannelCount : %Xh\n", Controller, ControllerIn->ChannelCount);
    for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
      ChannelIn = &ControllerIn->Channel[Channel];
      MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "Channel[%u].Status : %Xh\n", Channel, ChannelIn->Status);
      MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "Channel[%u].DimmCount : %Xh\n", Channel, ChannelIn->DimmCount);

      for (Dimm = 0; Dimm < MAX_DIMMS_IN_CHANNEL; Dimm++) {
        DimmIn = &ChannelIn->Dimm[Dimm];
        MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "%s %u/%u/%u Status : %Xh\n", CcdString, Controller, Channel, Dimm, DimmIn->Status);
        if (Inputs->MemoryProfile == USER_PROFILE) {
          MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "%s %u/%u/%u tCK    : %u\n", CcdString, Controller, Channel, Dimm, DimmIn->Timing.tCK);
          MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "%s %u/%u/%u NMode  : %u\n", CcdString, Controller, Channel, Dimm, DimmIn->Timing.NMode);
          MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "%s %u/%u/%u tCL    : %u\n", CcdString, Controller, Channel, Dimm, DimmIn->Timing.tCL);
          MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "%s %u/%u/%u tCWL   : %u\n", CcdString, Controller, Channel, Dimm, DimmIn->Timing.tCWL);
          MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "%s %u/%u/%u tFAW   : %u\n", CcdString, Controller, Channel, Dimm, DimmIn->Timing.tFAW);
          MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "%s %u/%u/%u tRAS   : %u\n", CcdString, Controller, Channel, Dimm, DimmIn->Timing.tRAS);
          MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "%s %u/%u/%u tRC    : %u\n", CcdString, Controller, Channel, Dimm, DimmIn->Timing.tRC);
          MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "%s %u/%u/%u tRCD   : %u\n", CcdString, Controller, Channel, Dimm, DimmIn->Timing.tRCD);
          MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "%s %u/%u/%u tREFI  : %u\n", CcdString, Controller, Channel, Dimm, DimmIn->Timing.tREFI);
          MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "%s %u/%u/%u tRFC   : %u\n", CcdString, Controller, Channel, Dimm, DimmIn->Timing.tRFC);
          MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "%s %u/%u/%u tRP    : %u\n", CcdString, Controller, Channel, Dimm, DimmIn->Timing.tRP);
#ifdef ULT_FLAG
          MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "%s %u/%u/%u tRPab  : %u\n", CcdString, Controller, Channel, Dimm, DimmIn->Timing.tRPab);
#endif // ULT_FLAG
          MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "%s %u/%u/%u tRRD   : %u\n", CcdString, Controller, Channel, Dimm, DimmIn->Timing.tRRD);
          MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "%s %u/%u/%u tRTP   : %u\n", CcdString, Controller, Channel, Dimm, DimmIn->Timing.tRTP);
          MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "%s %u/%u/%u tWR    : %u\n", CcdString, Controller, Channel, Dimm, DimmIn->Timing.tWR);
          MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "%s %u/%u/%u tWTR   : %u\n", CcdString, Controller, Channel, Dimm, DimmIn->Timing.tWTR);
        }
        MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "%s %u/%u/%u SpdAddress : %Xh\n", CcdString, Controller, Channel, Dimm, DimmIn->SpdAddress);
      }
    }
  }

  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "*************************************\n");
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "*****    THERMAL OVERWRITE    *******\n");
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "*************************************\n");
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "%s.EnableExtts     : %Xh\n",   ThermEnString, Inputs->ThermalEnables.EnableExtts);
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "%s.EnableCltm      : %Xh\n",   ThermEnString, Inputs->ThermalEnables.EnableCltm);
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "%s.EnableOltm      : %Xh\n",   ThermEnString, Inputs->ThermalEnables.EnableOltm);
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "%s.EnablePwrDn     : %Xh\n",   ThermEnString, Inputs->ThermalEnables.EnablePwrDn);
#ifdef ULT_FLAG
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "%s.EnablePwrDnLpddr: %Xh\n",   ThermEnString, Inputs->ThermalEnables.EnablePwrDnLpddr);
#endif // ULT_FLAG
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "%s.Refresh2X       : %Xh\n",   ThermEnString, Inputs->ThermalEnables.Refresh2X);
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "%s.LpddrThermalSensor: %Xh\n", ThermEnString, Inputs->ThermalEnables.LpddrThermalSensor);
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "%s.LockPTMregs     : %Xh\n",   ThermEnString, Inputs->ThermalEnables.LockPTMregs);
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "%s.UserPowerWeightsEn: %Xh\n", ThermEnString, Inputs->ThermalEnables.UserPowerWeightsEn);
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "%s.EnergyScaleFact : %Xh\n",   ThermEnString, Inputs->ThermalEnables.EnergyScaleFact);
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "%s.RaplLim2Lock    : %Xh\n",   ThermEnString, Inputs->ThermalEnables.RaplLim2Lock);
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "%s.RaplLim2WindX   : %Xh\n",   ThermEnString, Inputs->ThermalEnables.RaplLim2WindX);
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "%s.RaplLim2WindY   : %Xh\n",   ThermEnString, Inputs->ThermalEnables.RaplLim2WindY);
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "%s.RaplLim2Ena     : %Xh\n",   ThermEnString, Inputs->ThermalEnables.RaplLim2Ena);
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "%s.RaplLim2Pwr     : %Xh\n",   ThermEnString, Inputs->ThermalEnables.RaplLim2Pwr);
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "%s.RaplLim1WindX   : %Xh\n",   ThermEnString, Inputs->ThermalEnables.RaplLim1WindX);
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "%s.RaplLim1WindY   : %Xh\n",   ThermEnString, Inputs->ThermalEnables.RaplLim1WindY);
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "%s.RaplLim1Ena     : %Xh\n",   ThermEnString, Inputs->ThermalEnables.RaplLim1Ena);
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "%s.RaplLim1Pwr     : %Xh\n",   ThermEnString, Inputs->ThermalEnables.RaplLim1Pwr);
  for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
    MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "%s.RaplPwrFlCh[%u]  : %Xh\n", ThermEnString, Channel, Inputs->ThermalEnables.RaplPwrFl[Channel]);
    for (Dimm = 0; Dimm < MAX_DIMMS_IN_CHANNEL; Dimm++) {
      MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "%s.WarmThresholdCh[%u]Dimm[%u] : %Xh\n", ThermEnString, Channel, Dimm, Inputs->ThermalEnables.WarmThreshold[Channel][Dimm]);
      MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "%s.HotThresholdCh[%u]Dimm[%u]  : %Xh\n", ThermEnString, Channel, Dimm, Inputs->ThermalEnables.HotThreshold[Channel][Dimm]);
      MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "%s.WarmBudgetCh[%u]Dimm[%u]    : %Xh\n", ThermEnString, Channel, Dimm, Inputs->ThermalEnables.WarmBudget[Channel][Dimm]);
      MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "%s.HotBudgetCh[%u]Dimm[%u]     : %Xh\n", ThermEnString, Channel, Dimm, Inputs->ThermalEnables.HotBudget[Channel][Dimm]);
      MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "%s.IdleEnergyCh[%u]Dimm[%u]    : %Xh\n", ThermEnString, Channel, Dimm, Inputs->ThermalEnables.IdleEnergy[Channel][Dimm]);
      MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "%s.PdEnergyCh[%u]Dimm[%u]      : %Xh\n", ThermEnString, Channel, Dimm, Inputs->ThermalEnables.PdEnergy[Channel][Dimm]);
      MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "%s.ActEnergyCh[%u]Dimm[%u]     : %Xh\n", ThermEnString, Channel, Dimm, Inputs->ThermalEnables.ActEnergy[Channel][Dimm]);
      MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "%s.RdEnergyCh[%u]Dimm[%u]      : %Xh\n", ThermEnString, Channel, Dimm, Inputs->ThermalEnables.RdEnergy[Channel][Dimm]);
      MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "%s.WrEnergyCh[%u]Dimm[%u]      : %Xh\n", ThermEnString, Channel, Dimm, Inputs->ThermalEnables.WrEnergy[Channel][Dimm]);
    }
  }
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "%s.SrefCfgEna      : %Xh\n", ThermEnString, Inputs->ThermalEnables.SrefCfgEna);
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "%s.SrefCfgIdleTmr  : %Xh\n", ThermEnString, Inputs->ThermalEnables.SrefCfgIdleTmr);
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "%s.ThrtCkeMinDefeat: %Xh\n", ThermEnString, Inputs->ThermalEnables.ThrtCkeMinDefeat);
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "%s.ThrtCkeMinTmr   : %Xh\n", ThermEnString, Inputs->ThermalEnables.ThrtCkeMinTmr);
#ifdef ULT_FLAG
  if (Inputs->CpuModel == cmHSW_ULT) {
    MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "%s.ThrtCkeMinDefeatLpddr: %Xh\n", ThermEnString, Inputs->ThermalEnables.ThrtCkeMinDefeatLpddr);
    MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "%s.ThrtCkeMinTmrLpddr   : %Xh\n", ThermEnString, Inputs->ThermalEnables.ThrtCkeMinTmrLpddr);
  }
#endif // ULT_FLAG

  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "*************************************\n");
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "*****MRC INPUT PARAMS DUMP END*******\n");
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "*************************************\n\n");

  return mrcSuccess;
}

/**
  Print the specified memory to the serial message debug port.

  @param[in] Debug - Serial message debug structure.
  @param[in] Start - The starting address to dump.
  @param[in] Size  - The amount of data in bytes to dump.

  @retval Nothing.
**/
void
MrcPrintMemory (
  IN const MrcDebug *const Debug,
  IN const U8 *const       Start,
  IN const U32              Size
  )
{
  const U8  *Address;
  const U8  *End;
  U32       Line;
  U32       Offset;

  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "          ");
  for (Offset = 0; Offset < 16; Offset++) {
    MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "%02X ", ((U32) Start + Offset) % 16);
  }
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "\n");
  End = Start + Size;
  for (Line = 0; Line < ((Size / 16) + 1); Line++) {
    Address = Start + (Line * 16);
    MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "% 8X: ", Address);
    for (Offset = 0; Offset < 16; Offset++) {
      MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, ((Address + Offset) < End) ? "%02X " : "   ", Address[Offset]);
    }
    for (Offset = 0; (Offset < 16) && ((Address + Offset) < End); Offset++) {
      MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "%c", isprint (Address[Offset]) ? Address[Offset] : '.');
    }
    MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "\n");
  }
  return;
}
#endif

#if (defined MEMORY_DOWN_SUPPORT && (MEMORY_DOWN_SUPPORT > 0))

/******************************************************************************
  Memory down configuration code starts here.
  Add SPD, and channel/slot population settings here.

  Even though this is a memory down configuration, the MRC needs to know how
  the memory appears to the controller, so indicate here which channels are
  populated. Also, the MRC needs to know which slots are valid, even though
  there are technically no physical slots in a memory down configuration.
  The MRC also needs a valid SPD data for the configuration.
******************************************************************************/
typedef enum {
  MEMORY_ABSENT,    ///< No memory down and no physical memory slot.
  MEMORY_SLOT_ONLY, ///< No memory down and a physical memory slot.
  MEMORY_DOWN_ONLY, ///< Memory down and not a physical memory slot.
} MemorySlotStatus;

#ifndef AMI_OVERRIDE_FOR_MEMORY_DOWN
#if defined(NB_OEM_DIMM1_STATUS) && (NB_OEM_DIMM1_STATUS == 0x02)
static const UINT8 Dimm1SpdTbl[] = NB_OEM_DIMM1_SPD_DATA;
#endif
#if defined(NB_OEM_DIMM2_STATUS) && (NB_OEM_DIMM2_STATUS == 0x02)
static const UINT8 Dimm2SpdTbl[] = NB_OEM_DIMM2_SPD_DATA;
#endif
#if defined(NB_OEM_DIMM3_STATUS) && (NB_OEM_DIMM3_STATUS == 0x02)
static const UINT8 Dimm3SpdTbl[] = NB_OEM_DIMM3_SPD_DATA;
#endif
#if defined(NB_OEM_DIMM4_STATUS) && (NB_OEM_DIMM4_STATUS == 0x02)
static const UINT8 Dimm4SpdTbl[] = NB_OEM_DIMM4_SPD_DATA;
#endif
#endif // AMI_OVERRIDE_FOR_MEMORY_DOWN
///
/// Example board support
///
#ifdef AMI_OVERRIDE_FOR_MEMORY_DOWN
#define EXAMPLE_BOARD_SUPPORT 0
#else
#if (defined MEMORY_DOWN_SUPPORT && (MEMORY_DOWN_SUPPORT == 1))
#define EXAMPLE_BOARD_SUPPORT 1
#else
#define EXAMPLE_BOARD_SUPPORT 0
#endif // MEMORY_DOWN_SUPPORT
#endif // AMI_OVERRIDE_FOR_MEMORY_DOWN
#if (defined EXAMPLE_BOARD_SUPPORT && (EXAMPLE_BOARD_SUPPORT > 0))
///
/// For this example board, we have a dual channel, single slot configuration
/// with the same memory configuration in each channel (DDR3).
///
const MemorySlotStatus ExampleSlotStatus[MAX_CHANNEL][MAX_DIMMS_IN_CHANNEL] = {
#ifndef AMI_OVERRIDE_FOR_MEMORY_DOWN
  NB_OEM_DIMM1_STATUS,    // Channel 0, Slot 0
  NB_OEM_DIMM2_STATUS,    // Channel 0, Slot 1
  NB_OEM_DIMM3_STATUS,    // Channel 1, Slot 0
  NB_OEM_DIMM4_STATUS,    // Channel 1, Slot 1
#else
  MEMORY_DOWN_ONLY,                     ///< Channel 0, Slot 0
  MEMORY_ABSENT,                        ///< Channel 0, Slot 1
  MEMORY_DOWN_ONLY,                     ///< Channel 1, Slot 0
  MEMORY_ABSENT,                        ///< Channel 1, Slot 1
#endif // AMI_OVERRIDE_FOR_MEMORY_DOWN
};

const U8 ExampleSpd[] = {
  0x92,                                 ///< 0   Number of Serial PD Bytes Written / SPD Device Size / CRC Coverage 1, 2
  0x10,                                 ///< 1   SPD Revision
  0x0B,                                 ///< 2   DRAM Device Type
  0x03,                                 ///< 3   Module Type
  0x02,                                 ///< 4   SDRAM Density and Banks
  0x11,                                 ///< 5   SDRAM Addressing
  0x00,                                 ///< 6   Module Nominal Voltage
  0x09,                                 ///< 7   Module Organization
  0x03,                                 ///< 8   Module Memory Bus Width
  0x52,                                 ///< 9   Fine Timebase (FTB) Dividend / Divisor
  0x01,                                 ///< 10  Medium Timebase (MTB) Dividend
  0x08,                                 ///< 11  Medium Timebase (MTB) Divisor
  0x0A,                                 ///< 12  SDRAM Minimum Cycle Time (tCKmin)
  0x00,                                 ///< 13  Reserved0
  0xFE,                                 ///< 14  CAS Latencies Supported, Least Significant Byte
  0x00,                                 ///< 15  CAS Latencies Supported, Most Significant Byte
  0x69,                                 ///< 16  Minimum CAS Latency Time (tAAmin)
  0x78,                                 ///< 17  Minimum Write Recovery Time (tWRmin)
  0x69,                                 ///< 18  Minimum RAS# to CAS# Delay Time (tRCDmin)
  0x30,                                 ///< 19  Minimum Row Active to Row Active Delay Time (tRRDmin)
  0x69,                                 ///< 20  Minimum Row Precharge Delay Time (tRPmin)
  0x11,                                 ///< 21  Upper Nibbles for tRAS and tRC
  0x18,                                 ///< 22  Minimum Active to Precharge Delay Time (tRASmin), Least Significant Byte
  0x81,                                 ///< 23  Minimum Active to Active/Refresh Delay Time (tRCmin), Least Significant Byte
  0x70,                                 ///< 24  Minimum Refresh Recovery Delay Time (tRFCmin), Least Significant Byte
  0x03,                                 ///< 25  Minimum Refresh Recovery Delay Time (tRFCmin), Most Significant Byte
  0x3C,                                 ///< 26  Minimum Internal Write to Read Command Delay Time (tWTRmin)
  0x3C,                                 ///< 27  Minimum Internal Read to Precharge Command Delay Time (tRTPmin)
  0x00,                                 ///< 28  Upper Nibble for tFAW
  0xF0,                                 ///< 29  Minimum Four Activate Window Delay Time (tFAWmin)
  0x83,                                 ///< 30  SDRAM Optional Features
  0x01,                                 ///< 31  SDRAMThermalAndRefreshOptions
  0x00,                                 ///< 32  ModuleThermalSensor
  0x00,                                 ///< 33  SDRAM Device Type
  0x00,                                 ///< 34  Fine Offset for SDRAM Minimum Cycle Time (tCKmin)
  0x00,                                 ///< 35  Fine Offset for Minimum CAS Latency Time (tAAmin)
  0x00,                                 ///< 36  Fine Offset for Minimum RAS# to CAS# Delay Time (tRCDmin)
  0x00,                                 ///< 37  Fine Offset for Minimum Row Precharge Delay Time (tRPmin)
  0x00,                                 ///< 38  Fine Offset for Minimum Active to Active/Refresh Delay Time (tRCmin)
  0x00,                                 ///< 39
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,         ///< 40 - 49
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,         ///< 50 - 59
  0, 0,                                 ///< 60 - 61
  0x45,                                 ///< 62  Reference Raw Card Used
  0x00,                                 ///< 63  Address Mapping from Edge Connector to DRAM
  0x00,                                 ///< 64  ThermalHeatSpreaderSolution
  0, 0, 0, 0, 0,                        ///< 65 - 69
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,         ///< 70 - 79
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,         ///< 80 - 89
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,         ///< 90 - 99
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,         ///< 100 - 109
  0, 0, 0, 0, 0, 0, 0,                  ///< 110 - 116
  0x80,                                 ///< 117 Module Manufacturer ID Code, Least Significant Byte
  0xCE,                                 ///< 118 Module Manufacturer ID Code, Most Significant Byte
  0x01,                                 ///< 119 Module Manufacturing Location
  0x11,                                 ///< 120 Module Manufacturing Date Year
  0x02,                                 ///< 121 Module Manufacturing Date creation work week
  0x44,                                 ///< 122 Module Serial Number A
  0x0A,                                 ///< 123 Module Serial Number B
  0x83,                                 ///< 124 Module Serial Number C
  0x0C,                                 ///< 125 Module Serial Number D
  0xA5,                                 ///< 126 CRC A
  0x50                                  ///< 127 CRC B
};
#endif // EXAMPLE_BOARD_SUPPORT


/**
  Copies information from the Memory Down SPD structure to the SPD Input structure
  in the Host structure.

  Setting the SpdBaseAddress to zero means this slot has a memory down configuration.
  For systems that have both memory down and slots, it is recommended to have the
  memory down in the slot position farthest from the controller.

  @param[in, out] Inputs  - MRC Host Input structure.
  @param[in]      SpdIn   - Pointer to the Memory Down SPD structure to copy.
  @param[in]      Slot    - Pointer to the Memory Down MemorySlotStatus structure.
  @param[in]      SpdSize - Size of the SPD structure to limit MemoryCpy.

  @retval - Nothing.
**/
void
CopyMemoryDownSpd (
  IN OUT MrcInput *const         Inputs,
  IN     const U8                *SpdIn[MAX_CHANNEL][MAX_DIMMS_IN_CHANNEL],
  IN     const MemorySlotStatus  *Slot,
  IN     U16                     SpdSize
  )
{
  MrcDimmIn *DimmIn;
  U8        Channel;
  U8        Dimm;

  if (SpdIn == NULL || Slot == NULL || SpdSize == 0) {
    return;
  }

  for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
    for (Dimm = 0; Dimm < MAX_DIMMS_IN_CHANNEL; Dimm++, Slot++) {
      DimmIn = &Inputs->Controller[0].Channel[Channel].Dimm[Dimm];
      switch (*Slot) {
      case MEMORY_DOWN_ONLY:
        DimmIn->SpdAddress  = 0;
        // Check user request to disable DIMM/rank pair.
        if (DimmIn->Status != DIMM_DISABLED) {
          DimmIn->Status = DIMM_ENABLED;
        MrcOemMemoryCpy ((U8 *) &DimmIn->Spd, (U8 *) SpdIn[Channel][Dimm], SpdSize);
        MRC_DEBUG_MSG (&Inputs->Debug, MSG_LEVEL_NOTE, "Memory down present on channel %u, dimm %u\n", Channel, Dimm);
        } else {
          MRC_DEBUG_MSG (&Inputs->Debug, MSG_LEVEL_NOTE, "Memory down absent on channel %u, dimm %u\n", Channel, Dimm);
        }
        break;

      case MEMORY_ABSENT:
        DimmIn->Status      = DIMM_DISABLED;
        DimmIn->SpdAddress  = 0;
        MRC_DEBUG_MSG (&Inputs->Debug, MSG_LEVEL_NOTE, "Memory down absent on channel %u, dimm %u\n", Channel, Dimm);
        break;

      case MEMORY_SLOT_ONLY:
      default:
        break;
      }
    }
  }

  return;
}

/**
  Enables Memory Down support and sets SPD data for all DIMMs needing support.

  @param[in] Inputs  - MRC Input data structure.
  @param[in] BoardId - The ID of the board.

  @retval Nothing
**/
void
EnableMemoryDown (
  IN MrcInput *const Inputs,
  IN U16             BoardId
  )
{
  const U8                *SpdIn[MAX_CHANNEL][MAX_DIMMS_IN_CHANNEL];
  const MemorySlotStatus  *Slot;
  U16                     SpdSize;
  U8                      Channel;
  U8                      Dimm;
#ifndef AMI_OVERRIDE_FOR_MEMORY_DOWN
  const U8 *DimmSpdTbl = NULL;
#endif // AMI_OVERRIDE_FOR_MEMORY_DOWN

  Channel = 0;
  Dimm    = 0;
  SpdSize = 0;

  switch (BoardId) {
#if (defined EXAMPLE_BOARD_SUPPORT && (EXAMPLE_BOARD_SUPPORT > 0))

  case 0:
    //
    // BoardIdExample:
    //
    for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
      for (Dimm = 0; Dimm < MAX_DIMMS_IN_CHANNEL; Dimm++) {
#ifndef AMI_OVERRIDE_FOR_MEMORY_DOWN
#if defined(NB_OEM_DIMM1_STATUS) && (NB_OEM_DIMM1_STATUS == 0x02)         
          if (Channel == 0 && Dimm == 0) {
             DimmSpdTbl = Dimm1SpdTbl;
          }
#endif
#if defined(NB_OEM_DIMM2_STATUS) && (NB_OEM_DIMM2_STATUS == 0x02)         
          if (Channel == 0 && Dimm == 1) {
             DimmSpdTbl = Dimm2SpdTbl;
          }
#endif
#if defined(NB_OEM_DIMM3_STATUS) && (NB_OEM_DIMM3_STATUS == 0x02)         
          if (Channel == 1 && Dimm == 0) {
             DimmSpdTbl = Dimm3SpdTbl;
          }
#endif     
#if defined(NB_OEM_DIMM4_STATUS) && (NB_OEM_DIMM4_STATUS == 0x02)         
          if (Channel == 1 && Dimm == 1) {
             DimmSpdTbl = Dimm4SpdTbl;
          }
#endif
          SpdIn[Channel][Dimm] = DimmSpdTbl;
          if (DimmSpdTbl != NULL) {
             DimmSpdTbl = NULL;
          }
#else
        SpdIn[Channel][Dimm] = ExampleSpd;
#endif // AMI_OVERRIDE_FOR_MEMORY_DOWN
      }
    }

    Slot = (const MemorySlotStatus *) &ExampleSlotStatus[0][0];
    SpdSize = sizeof(ExampleSpd);
    break;
#endif // EXAMPLE_BOARD_SUPPORT


  //
  // Add additional boards that support memory down here.
  //

  //
  // The default case means the board ID was not recognized.  Instead
  // we set Slot = NULL thus forcing us to read from the SPD.
  //
  default:
    Slot  = NULL;
  }

  CopyMemoryDownSpd (Inputs, SpdIn, Slot, SpdSize);

  return;
}
#endif // MEMORY_DOWN_SUPPORT

#ifdef ULT_FLAG
/**
  Initialize the board-specific CMD/CTL/CLK and DQ/DQS mapping for LPDDR3.

  @param[in, out] Inputs  - MRC Input data structure.
  @param[in]      BoardId - The ID of the board.

  @retval none
**/
void
MrcOemLpddrBoardMapping (
  IN OUT  MrcInput *Inputs,
  IN      U16      BoardId
  )
{
  MrcControllerIn *ControllerIn;
  U8              *DqByteMapCh0;
  U8              *DqByteMapCh1;
  U8              *DqsMapCpu2DramCh0;
  U8              *DqsMapCpu2DramCh1;
  U8              *DqMapCpu2DramCh0;
  U8              *DqMapCpu2DramCh1;
  U32             Channel;
  U32             Byte;


  ControllerIn = &Inputs->Controller[0];
  DqByteMapCh0      = NULL;
  DqByteMapCh1      = NULL;
  DqsMapCpu2DramCh0 = NULL;
  DqsMapCpu2DramCh1 = NULL;
  DqMapCpu2DramCh0  = NULL;
  DqMapCpu2DramCh1  = NULL;

  //
  // CKE to Rank mapping:       CKE  | 0 1 2 3
  // (same on both channels)    --------------
  //                            Rank | 0 1 0 1
  //
  Inputs->CkeRankMapping = 0xAA;

  //
  // @todo: pass these via SaPlatformPolicy PPI
  //
  DqByteMapCh0      = (U8 *) DqByteMapRvpCh0;
  DqByteMapCh1      = (U8 *) DqByteMapRvpCh1;
  DqsMapCpu2DramCh0 = (U8 *) DqsMapCpu2DramRvpCh0;
  DqsMapCpu2DramCh1 = (U8 *) DqsMapCpu2DramRvpCh1;
  DqMapCpu2DramCh0  = (U8 *) DqMapCpu2DramRvpCh0;
  DqMapCpu2DramCh1  = (U8 *) DqMapCpu2DramRvpCh1;


  //
  // DQ byte mapping to CMD/CTL/CLK
  //
  MrcOemMemoryCpy ((U8 *) ControllerIn->Channel[0].DQByteMap, DqByteMapCh0, sizeof (DqByteMapRvpCh0));
  MrcOemMemoryCpy ((U8 *) ControllerIn->Channel[1].DQByteMap, DqByteMapCh1, sizeof (DqByteMapRvpCh1));

  //
  // DQS byte swizzling between CPU and DRAM
  //
  MrcOemMemoryCpy (ControllerIn->Channel[0].DqsMapCpu2Dram, DqsMapCpu2DramCh0, sizeof (DqsMapCpu2DramRvpCh0));
  MrcOemMemoryCpy (ControllerIn->Channel[1].DqsMapCpu2Dram, DqsMapCpu2DramCh1, sizeof (DqsMapCpu2DramRvpCh1));

  for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
    MRC_DEBUG_MSG (&Inputs->Debug, MSG_LEVEL_ERROR, "Ch %d DqsMapCpu2Dram: ", Channel);
    for (Byte = 0; Byte < 8; Byte++) {
      MRC_DEBUG_MSG (&Inputs->Debug, MSG_LEVEL_ERROR, "%d ", ControllerIn->Channel[Channel].DqsMapCpu2Dram[Byte]);
    }
    MRC_DEBUG_MSG (&Inputs->Debug, MSG_LEVEL_ERROR, "\n");
  }

  //
  // DQ bit swizzling between CPU and DRAM
  //
  MrcOemMemoryCpy ((U8 *) ControllerIn->Channel[0].DqMapCpu2Dram, DqMapCpu2DramCh0, sizeof (DqMapCpu2DramRvpCh0));
  MrcOemMemoryCpy ((U8 *) ControllerIn->Channel[1].DqMapCpu2Dram, DqMapCpu2DramCh1, sizeof (DqMapCpu2DramRvpCh0));
}
#endif // ULT_FLAG
// AMI_OVERRIDE_FOR_UPSERVER_SUPPORT
#ifdef UPSERVER_SUPPORT
void
MrcCltmDisable (
  MrcParameters          *MrcData
  )
/*++

Routine Description:

  Disable CLTM configuration register if Outputs->CLTM_SPD_Conf = PROCESS_FAILED

Arguments:

  MrcData          - include all the MRC data.

Returns:
 None

--*/
{
  MrcDebug                *Debug;
  PCU_CR_DDR_PTM_CTL_PCU_STRUCT                         DdrPtmCtl;
  ThermalMngmtEn          *ThermalEnables;
  MrcInput                *Inputs;

  Inputs          = &MrcData->SysIn.Inputs;
  Debug           = &Inputs->Debug;
  ThermalEnables  = &Inputs->ThermalEnables;

    DdrPtmCtl.Data                    = MrcReadCR (MrcData, PCU_CR_DDR_PTM_CTL_PCU_REG);
    DdrPtmCtl.Bits.OLTM_ENABLE        = ThermalEnables->EnableOltm;//Disable , 0,  Not available for UP Platforms
    DdrPtmCtl.Bits.CLTM_ENABLE        = CLTM_DISABLE;//0, Disable.
    MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "CLTM is Disabled - Exiting.\n");
    MrcWriteCR (MrcData, PCU_CR_DDR_PTM_CTL_PCU_REG, DdrPtmCtl.Data);
    MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "DDR_PTM_CTL %Xh: %Xh \n", PCU_CR_DDR_PTM_CTL_PCU_REG, MrcReadCR (MrcData, PCU_CR_DDR_PTM_CTL_PCU_REG));
}

void
MrcCltmInit (
  MrcParameters          *MrcData
  )
/*++

Routine Description:

  CLTM Initialization

Arguments:

  MrcData          - include all the MRC data.

Returns:
 None

--*/
{
  MrcInput                *Inputs;
  MrcOutput               *Outputs;
  MrcDebug                *Debug;
  ThermalMngmtEn          *ThermalEnables;
  U8                      Controller;
  U8                      Channel, Dimm;
  U8                      OffsetDimm[2];
  BOOL                    FirstValue;
  PCU_CR_DDR_PTM_CTL_PCU_STRUCT                         DdrPtmCtl;
  PCU_CR_DDR_ENERGY_SCALEFACTOR_PCU_STRUCT              DdrEnergyScaleFactor;
  PCU_CR_DDR_WARM_THRESHOLD_CH0_PCU_STRUCT              DdrWarmThresholdCh0;
  PCU_CR_DDR_WARM_THRESHOLD_CH1_PCU_STRUCT              DdrWarmThresholdCh1;
  PCU_CR_DDR_HOT_THRESHOLD_CH0_PCU_STRUCT               DdrHotThresholdCh0;
  PCU_CR_DDR_HOT_THRESHOLD_CH1_PCU_STRUCT               DdrHotThresholdCh1;
  PCU_CR_DDR_WARM_BUDGET_CH0_PCU_STRUCT                 DdrWarmBudgetCh0;
  PCU_CR_DDR_WARM_BUDGET_CH1_PCU_STRUCT                 DdrWarmBudgetCh1;
  PCU_CR_DDR_HOT_BUDGET_CH0_PCU_STRUCT                  DdrHotBudgetCh0;
  PCU_CR_DDR_HOT_BUDGET_CH1_PCU_STRUCT                  DdrHotBudgetCh1;
  MCHBAR_CH0_CR_PM_DIMM_IDLE_ENERGY_STRUCT              PmDimmIdleEnergy;
  MCHBAR_CH0_CR_PM_DIMM_PD_ENERGY_STRUCT                PmDimmPdEnergy;
  MCHBAR_CH0_CR_PM_DIMM_ACT_ENERGY_STRUCT               PmDimmActEnergy;
  MCHBAR_CH0_CR_PM_DIMM_RD_ENERGY_STRUCT                PmDimmRdEnergy;
  MCHBAR_CH0_CR_PM_DIMM_WR_ENERGY_STRUCT                PmDimmWrEnergy;
  TSOD_CONF_REGISTER_STRUCT                             TsodConfReg;

  U8             h=0,i = 0, j = 0, k1 =2, k0=2 ; //h=2xRefreshMode i = Density , j = Frequency , k1 = Adjacent DIMM prescence in Channel 1, k0 = Adjacent DIMM prescence in Channel 0 
  U8             iprev = 2, hotThreshold = 0, warmThreshold=0;
  U8             ControllerSave = CONTROLLER_NOT_LOADED;
  const U16      *PwrWeight0 = NULL, *PwrWeight1 = NULL ;
  U16            MtsData = 0, Thigh = 0, Tcrit = 0, Temp = 0;
  U16            freq=0, density= 0; 
  Inputs          = &MrcData->SysIn.Inputs;
  Debug           = &Inputs->Debug;
  ThermalEnables  = &Inputs->ThermalEnables;
  Outputs         = &MrcData->SysOut.Outputs;
  TsodConfReg.Data =0;
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "MrcCltmInit - Start.\n");
 
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "EnableCltm %d EccSupport %d - \n", ThermalEnables->EnableCltm, Outputs->EccSupport);
  if (ThermalEnables->EnableCltm  && (Outputs->EccSupport == TRUE)) {
    FirstValue = FALSE;
    if(Outputs->CLTM_SPD_Conf == PROCESS_NOT_INITIALIZED) {
    MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE,"CLTM_SPD_Config = %u\n",Outputs->CLTM_SPD_Conf);
    for (Controller = 0; Controller < MAX_CONTROLLERS; Controller++) {
    // Check in every DIMM for CLTM capabilities
    for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {

      if (Outputs->Controller[Controller].Channel[Channel].Status != CHANNEL_PRESENT) continue;

      for (Dimm = 0; Dimm < MAX_DIMMS_IN_CHANNEL; Dimm++) {

        if (Outputs->Controller[Controller].Channel[Channel].Dimm[Dimm].Status != DIMM_PRESENT) continue;

        MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "Channel %d Dimm %d - Check for CLTM Capabilities\n", Channel, Dimm);

        // CHECK CLTM RESTRICTIONS

        // Check ECC support. Do not enable CLTM if not supported.
        if (Outputs->Controller[Controller].Channel[Channel].Dimm[Dimm].EccSupport == FALSE) {
          MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "CLTM is Disable - Channel %d Dimm %d is non ECC - Exiting.\n", Channel, Dimm);
          Outputs->CLTM_SPD_Conf = PROCESS_FAILED;
          MrcCltmDisable(MrcData);
          return;
        }

        // Check thermal sensor presence. Do not enable CLTM if no sensor.
        if (Inputs->Controller[Controller].Channel[Channel].Dimm[Dimm].Spd.Ddr3.General.ModuleThermalSensor.Bits.ThermalSensorPresence == 0) {
          MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "CLTM is Disable - Channel %d Dimm %d do not have Thermal Sensor Incorporated - Exiting.\n", Channel, Dimm);
          Outputs->CLTM_SPD_Conf = PROCESS_FAILED;
          MrcCltmDisable(MrcData);
          return;
        }
/*All dimms will be taken as Raw Card E
        // Check Refernce Raw Card = E . Do not enable CLTM if no Raw Card.
        if (Inputs->Controller[Controller].Channel[Channel].Dimm[Dimm].Spd.Ddr3.Module.Unbuffered.ReferenceRawCardUsed.Bits.Card != rcE) {
          MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "Channel %d Dimm %d RAW Card is not E - CLTM disable.\n", Channel, Dimm);
          Outputs->CLTM_SPD_Conf = PROCESS_FAILED;
          MrcCltmDisable(MrcData);
          return;
        }
*/
         // Check if UDIMM. Do not enable CLTM if not UDIM 
        if (Inputs->Controller[Controller].Channel[Channel].Dimm[Dimm].Spd.Ddr3.General.ModuleType.Bits.ModuleType != MRC_UDIMM_TYPE_NUMBER) {
          MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "Channel %d Dimm %d Module Type is not UDIMM - CLTM disable.\n", Channel, Dimm);
          Outputs->CLTM_SPD_Conf = PROCESS_FAILED;
          MrcCltmDisable(MrcData);
          return;
        }
 /* All dimms will be configure as Dual Rank and x8
       // Check if Dual Rank. Do not enable CLTM if not Dual Rank 
        if (Outputs->Controller[Controller].Channel[Channel].Dimm[Dimm].RankInDIMM != 2) {
          MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "Channel %d Dimm %d not Dual Rank - CLTM disable.\n", Channel, Dimm);
          Outputs->CLTM_SPD_Conf = PROCESS_FAILED;
          MrcCltmDisable(MrcData);
          return;
        }

        // Check if x8. Do not enable CLTM if not x8 
        if (Outputs->Controller[Controller].Channel[Channel].Dimm[Dimm].SdramWidth != 8) {
          Outputs->CLTM_SPD_Conf = PROCESS_FAILED;
          MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "Channel %d Dimm %d Width is not x8 - CLTM disable.\n", Channel, Dimm);
          MrcCltmDisable(MrcData);
          return;
        } 
*/
           //switch (Outputs->Controller[Controller].Channel[Channel].Dimm[Dimm].DimmCapacity) {
           switch (Inputs->Controller[Controller].Channel[Channel].Dimm[Dimm].Spd.Ddr3.General.SdramDensityAndBanks.Bits.Density) {
          //case 2048:
          case 3:  
            i = 0;
            if(FirstValue == FALSE) { iprev = i; }
            if(iprev != i) {
                //MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "Channel %d Dimm %d Capacity is 2Gb and different from other previous DIMM - CLTM disable\n", Channel, Dimm);
                MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "Channel %d Dimm %d Density is 2Gb and different from other previous DIMM - configure as 4Gb\n", Channel, Dimm);
                i = 1;
            }
            iprev =i;
            //MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "Channel %d Dimm %d Capacity is 2Gb\n", Channel, Dimm);
            MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "Channel %d Dimm %d Density is 2Gb\n", Channel, Dimm);
            break;
          //case 4096:
           case 4:
            i = 1;
            if(FirstValue == FALSE) { iprev = i; }
            if(iprev != i) {
                //MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "Channel %d Dimm %d Capacity is 4Gb and different from other previous DIMM\n", Channel, Dimm);
                MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "Channel %d Dimm %d Density is 4Gb and different from other previous DIMM\n", Channel, Dimm);
                i = 1; 
            }
            iprev =i;
            //MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "Channel %d Dimm %d Capacity is 4Gb\n", Channel, Dimm);
            MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "Channel %d Dimm %d Density is 4Gb\n", Channel, Dimm);
            break;
          default:
            //MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "Channel %d Dimm %d Capacity is different than 4Gb and 2GB - CLTM disable \n", Channel, Dimm);
            MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "Channel %d Dimm %d Density is different than 4Gb and 2GB \n", Channel, Dimm);
            i = 1; 
            iprev =i;
            break;
          }
         
          if (Outputs->Controller[Controller].Channel[Channel].DimmCount > 1) {
            if(Channel == 0) {k0 = 1;}
            else{k1=1;}
            MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "Adjacent DIMM next to Dimm %d in Channel %d.\n", Dimm, Channel); 
          } 
          else {
            if(Channel == 0) {k0 = 0;}
            else{k1=0;}
            MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "No adjacent DIMM next to Dimm %d in Channel %d.\n", Dimm, Channel);
          }

        // Check if DIMM supports dual refresh
        if (((Inputs->Controller[Controller].Channel[Channel].Dimm[Dimm].Spd.Ddr3.General.ThermalAndRefreshOptions.Data & (MRC_BIT1 | MRC_BIT0)) == MRC_BIT0)) {
          MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "Channel %d Dimm %d Supports 2x Self Refresh\n", Channel, Dimm);
        } else {
          MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "Channel %d Dimm %d DO NOT Support 2x Self Refresh\n", Channel, Dimm);
          ThermalEnables->Refresh2X = DISABLE_REFRESH2X;
          
        }
        h = ThermalEnables->Refresh2X;
      FirstValue = TRUE;
      } //for (Dimm = 0; Dimm < MAX_DIMMS_IN_CHANNEL; Dimm++)
     } //for (Channel = 0; Channel < MAX_CHANNEL; Channel++)
    }// for Controller
    
     //Frequency calculated from Common Memory Controller Frequency
     switch (Outputs->Frequency) {
          case f1600:
            j = 0;
            break;
          case f1333:
            j = 1;
            break;
          default:
            j=0;
            MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "MC Frequency is other than 1600 and 1333 - CLTM configure as 1600 .\n");
            break;
          }
     MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE,"CLTM_SPD_Config check has finished for first time\n");
    }
    
    if((Outputs->CLTM_SPD_Conf != PROCESS_FAILED) && (Outputs->CLTM_SPD_Conf != PROCESS_NOT_INITIALIZED) ) 
     {
         h = (((Outputs->CLTM_SPD_Conf)& (0x0300))>> 8); // mask with 0000 0011 0000 0000 and shift right 8, 2xRefreshMode
         i = (((Outputs->CLTM_SPD_Conf)& (0x00C0))>> 6); // mask with 0000 0000 1100 0000 and shift right 6, Density index
         j = (((Outputs->CLTM_SPD_Conf)& (0x0030))>> 4); // mask with 0000 0000 0011 0000 and shift right 4, Frequency
         k1 = (((Outputs->CLTM_SPD_Conf)& (0x000C))>> 2); //mask 0000 0000 0000 1100 and shift right 2, Adjacent DIMM prescence of channel 1
         k0 = ((Outputs->CLTM_SPD_Conf)& 0x0003);//mask with 0000 0000 0000 0011,  Adjacent DIMM prescence of channel 0
         MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE,"DIMM variables: 2xRefresh Support,  frequency , adjacent, density has been initialized. \n "); 
     }
     else if (Outputs->CLTM_SPD_Conf == PROCESS_FAILED) 
     {
      MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "CLTM_SPD_Config already executed and Failed\n");
      MrcCltmDisable(MrcData);
      return; 
     }

     Outputs->CLTM_SPD_Conf = (h << 8)+ (i << 6) + (j<<4) + (k1<<2) + k0;
     (i == 0)? (density = 2) : (density = 4);
     (j == 0)? (freq = 1600) : (freq = 1333);


     if ( ((k0==0)||(k0==1)) && ((k1==0)||(k1==1)) ){
 
         MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE,"CLTM_SPD_Config interpret = \n  2xRefresh Support = %d , density = 2GB%d, frequency=%d, \n Channel 1 adjacent DIMM=%d, Channel 0 Adjacent DIMM =%d \n",h,density,freq,k1,k0);
     }
     else if (k1==2) {
         MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE,"CLTM_SPD_Config interpret = \n 2xRefresh Support = %d ,density index=%d, frequency=%d, \n Channel 0 Adjacent DIMM =%d \n",h,density,freq,k0); 
     }
     else if (k0==2) {
         MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE,"CLTM_SPD_Config interpret = \n 2xRefresh Support = %d ,density index=%d, frequency =%d, \n Channel 1 Adjacent DIMM =%d \n",h,density,freq,k1);
     }
     else{
          MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE,"CLTM_SPD_Config interpret incorrectly k1=%d, or k0=%d are incorrect \n",k1,k0);
         Outputs->CLTM_SPD_Conf = PROCESS_FAILED;
         MrcCltmDisable(MrcData);
         return;
     }
     
      
     MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE,"CLTM_SPD_Config = %u\n",Outputs->CLTM_SPD_Conf);  
     
     //Configuration Register of TSOD
     TsodConfReg.Bits.EVENT_MODE             = ThermalEnables->TSOD_EventMode;//Default 1, Interrupt
     TsodConfReg.Bits.EVENT_POLARITY         = ThermalEnables->TSOD_EventPolarity;//Default 0, Low
     TsodConfReg.Bits.CRICAL_EVENT_ONLY      = ThermalEnables->TSOD_CriticalEventOnly;//Default 1, Enable
     TsodConfReg.Bits.EVENT_OUTPUT_CONTROL   = ThermalEnables->TSOD_EventOutputControl; //Default 1, Enable
     TsodConfReg.Bits.ALARM_WINDOW_LOCK      = ThermalEnables->TSOD_AlarmwindowLockBit; //Default 0, Unlock
     TsodConfReg.Bits.CRITICAL_LOCK          = ThermalEnables->TSOD_CriticaltripLockBit; //Default 0, Unlock
     TsodConfReg.Bits.SHUTDOWNMODE           = ThermalEnables->TSOD_ShutdownMode; // Default 0, TSOD Enable
     TsodConfReg.Bits.HYST_ENABLE            = HYST_DISABLE; 

     
     DdrWarmThresholdCh0.Data        = 0;
     DdrWarmThresholdCh1.Data        = 0;
     DdrHotThresholdCh0.Data         = 0;
     DdrHotThresholdCh1.Data         = 0;

       if (!ThermalEnables->UserThresholdEn) {//Configuration of warm and hot threshold depending of single or dual refresh
         if(h != DISABLE_REFRESH2X ) {
          warmThreshold = ( WarmThreshold_2X_MAX_TEMP  );
          hotThreshold = ( HotThreshold_2X_MAX_TEMP  );
          
         }
         else{
          warmThreshold = ( WarmThreshold_1X_MAX_TEMP  );
          hotThreshold = ( HotThreshold_1X_MAX_TEMP  );
          
         }
       }

    for (Controller = 0; Controller < MAX_CONTROLLERS; Controller++) {
    for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {

      //OffsetChannel[Channel] = 0;

      if (Outputs->Controller[Controller].Channel[Channel].Status != CHANNEL_PRESENT) continue;

      for (Dimm = 0; Dimm < MAX_DIMMS_IN_CHANNEL; Dimm++) {

        OffsetDimm[Dimm] = 0;
        if (Outputs->Controller[Controller].Channel[Channel].Dimm[Dimm].Status != DIMM_PRESENT) continue;
               ControllerSave = Controller;
        MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "CLTM Configuration for Channel %d Dimm %d\n", Channel, Dimm);

        // Get offset temperature
        (Channel ==0) ? (OffsetDimm[Dimm] = CltmThermalLookUpTable[i][j][k0][ThermalEnables->Altitude]): (OffsetDimm[Dimm] = CltmThermalLookUpTable[i][j][k1][ThermalEnables->Altitude]);
        
        MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "Offset = %d degreeC\n", OffsetDimm[Dimm]);

        if (ThermalEnables->TSOD_ManEn) {
          Thigh = ((ThermalEnables->TSOD_ThigMax) << 4);
          Tcrit = ((ThermalEnables->TSOD_TcritMax) << 4);
           
        }
        else{
          Tcrit = (( (CRITICAL_TEMP) - OffsetDimm[Dimm]) << 4);
          if(h != DISABLE_REFRESH2X ) {
          Thigh = (( (THOT_2X_MAX_TEMP) - OffsetDimm[Dimm]) << 4);
          }
          else{
          Thigh = (( (THOT_1X_MAX_TEMP) - OffsetDimm[Dimm]) << 4);
          }
          
        }
 
        // SPD Thermal sensor registers Configurations Begin
        //((SpdDeviceAddress & 0x0F) | THERMAL_MODULE_MASK )         
        //Thermal Sensor Information 
        //  MFG ID
        if (MrcOemSmbusRead16 (Inputs->SmbusBaseAddress, ((Inputs->Controller[Controller].Channel[Channel].Dimm[Dimm].SpdAddress & 0x0F) | THERMAL_MODULE_MASK ), MTS_MFGID, &MtsData) == mrcFail) {
          MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "Error - Channel %d Dimm %d Temp Sensor NACK\n", Channel, Dimm);
        } else {
          Temp = (((MtsData & 0xFF00) >> 8) | ((MtsData & 0x00FF) << 8));
          MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "Channel %d Dimm %d Temp Sensor Mfg Id = 0x%04X\n", Channel, Dimm, Temp);
        }

        // SPD thermal sensor DEV ID
        
        if (MrcOemSmbusRead16 (Inputs->SmbusBaseAddress, ((Inputs->Controller[Controller].Channel[Channel].Dimm[Dimm].SpdAddress & 0x0F) | THERMAL_MODULE_MASK ) , MTS_DID, &MtsData) == mrcFail) {
          MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "Error - Channel %d Dimm %d Temp Sensor NACK\n", Channel, Dimm);
        } else {
          Temp = (((MtsData & 0xFF00) >> 8) | ((MtsData & 0x00FF) << 8));
          MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "Channel %d Dimm %d Temp Sensor Dev/Rev Id = 0x%04X\n", Channel, Dimm, Temp);
        }

       // Configuration Register // Disabling Configuration Register
        MtsData = 0;
        Temp = (((MtsData & 0xFF00) >> 8) | ((MtsData & 0x00FF) << 8));
       MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "Thermal Sensor Configuration value to be programmed into TS2002 is 0x%X\n", Temp);
        MrcOemSmbusWrite16 (Inputs->SmbusBaseAddress, ((Inputs->Controller[Controller].Channel[Channel].Dimm[Dimm].SpdAddress & 0x0F) | THERMAL_MODULE_MASK ), MTS_CFG, Temp);
        MrcOemSmbusRead16 (Inputs->SmbusBaseAddress, ((Inputs->Controller[Controller].Channel[Channel].Dimm[Dimm].SpdAddress & 0x0F) | THERMAL_MODULE_MASK ), MTS_CFG, &MtsData);
        Temp = (((MtsData & 0xFF00) >> 8) | ((MtsData & 0x00FF) << 8));
        MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "Thermal Sensor Configuration value read from TS2002 is 0x%X\n", MtsData);
        MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "Thermal Sensor Configuration value is 0x%X\n", Temp);

        // THigh 0x02
        
        Temp = (((Thigh & 0xFF00) >> 8) | ((Thigh & 0x00FF) << 8));
        MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "High Temp value is 0x%X = %d degreeC\n", Thigh, (Thigh >> 4));
        MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "High Temp value to be programmed into TS2002 is 0x%X\n", Temp);
        MrcOemSmbusWrite16 (Inputs->SmbusBaseAddress, ((Inputs->Controller[Controller].Channel[Channel].Dimm[Dimm].SpdAddress & 0x0F) | THERMAL_MODULE_MASK ), MTS_THIGH, Temp);
        MrcOemSmbusRead16 (Inputs->SmbusBaseAddress, ((Inputs->Controller[Controller].Channel[Channel].Dimm[Dimm].SpdAddress & 0x0F) | THERMAL_MODULE_MASK ), MTS_THIGH, &Thigh);
        Temp = (((Thigh & 0xFF00) >> 8) | ((Thigh & 0x00FF) << 8));
        MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "High Temp value read from TS2002 is 0x%X\n", Thigh);
        MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "High Temp value is 0x%X = %d degreeC\n", Temp, (Temp >> 4));
        

        // TCrit 0x04
        Temp = (((Tcrit & 0xFF00) >> 8) | ((Tcrit & 0x00FF) << 8));
        MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "Critical Temp value is 0x%X = %d degreeC\n", Tcrit, (Tcrit >> 4));
        MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "Critical Temp value to be programmed into TS2002 is 0x%X\n", Temp);
        MrcOemSmbusWrite16 (Inputs->SmbusBaseAddress, ((Inputs->Controller[Controller].Channel[Channel].Dimm[Dimm].SpdAddress & 0x0F) | THERMAL_MODULE_MASK ), MTS_TCRIT, Temp);
        MrcOemSmbusRead16 (Inputs->SmbusBaseAddress, ((Inputs->Controller[Controller].Channel[Channel].Dimm[Dimm].SpdAddress & 0x0F) | THERMAL_MODULE_MASK ), MTS_TCRIT, &Tcrit);
        Temp = (((Tcrit & 0xFF00) >> 8) | ((Tcrit & 0x00FF) << 8));
        MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "Critical Temp value read from TS2002 is 0x%X\n", Tcrit);
        MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "Critical Temp value is 0x%X = %d degreeC\n", Temp, (Temp >> 4));

       // Configuration Register
        MtsData = TsodConfReg.Data;
        Temp = (((MtsData & 0xFF00) >> 8) | ((MtsData & 0x00FF) << 8));
        MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "Thermal Sensor Configuration value is 0x%X\n", MtsData);
        MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "Thermal Sensor Configuration value to be programmed into TS2002 is 0x%X\n", Temp);
        MrcOemSmbusWrite16 (Inputs->SmbusBaseAddress, ((Inputs->Controller[Controller].Channel[Channel].Dimm[Dimm].SpdAddress & 0x0F) | THERMAL_MODULE_MASK ), MTS_CFG, Temp);
        MrcOemSmbusRead16 (Inputs->SmbusBaseAddress, ((Inputs->Controller[Controller].Channel[Channel].Dimm[Dimm].SpdAddress & 0x0F) | THERMAL_MODULE_MASK ), MTS_CFG, &MtsData);
        Temp = (((MtsData & 0xFF00) >> 8) | ((MtsData & 0x00FF) << 8));
        MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "Thermal Sensor Configuration value read from TS2002 is 0x%X\n", MtsData);
        MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "Thermal Sensor Configuration value is 0x%X\n", Temp);
       // SPD thermal sensor registers Configurations End

        //Read current temperature of the TSOD 0x05
        MrcOemSmbusRead16 (Inputs->SmbusBaseAddress, ((Inputs->Controller[Controller].Channel[Channel].Dimm[Dimm].SpdAddress & 0x0F) | THERMAL_MODULE_MASK ), TEMPERATURE_REGISTER, &Thigh);
        Temp = (((Thigh & 0xFF00) >> 8) | ((Thigh & 0x001F) << 8));//This will get rid of the firt three bits of the register and hold only the themperatur value
        MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "SMBUS base Address is 0x%X\n", Inputs->SmbusBaseAddress);
        MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "SPD address offset 0x%X of Channel:%d  DIMM:%d \n", Inputs->Controller[Controller].Channel[Channel].Dimm[Dimm].SpdAddress & 0x0F, Channel, Dimm);
        MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "Module thermal SPD address 0x%X of Channel:%d  DIMM:%d\n", ((Inputs->Controller[Controller].Channel[Channel].Dimm[Dimm].SpdAddress & 0x0F) | THERMAL_MODULE_MASK ), Channel, Dimm);
        MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "Offset to temperature register 0x%X\n", TEMPERATURE_REGISTER );
        MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "Temperature register value read from TS2002 is 0x%X\n", Thigh);
        MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "Current TSOD Temperatur value is 0x%X = %d degreeC\n", Temp, (Temp >> 4));
        
        //Warm and hot threshold Configuration begin
       if(!ThermalEnables->UserThresholdEn) {
          
        if((Channel ==0)&& (Dimm == 0) ) {
          DdrWarmThresholdCh0.Bits.DIMM0  = warmThreshold;
          DdrHotThresholdCh0.Bits.DIMM0  = hotThreshold;
        }
         if((Channel ==0)&& (Dimm == 1) ) {
          DdrWarmThresholdCh0.Bits.DIMM1  = warmThreshold;
          DdrHotThresholdCh0.Bits.DIMM1  = hotThreshold;
        }

         if((Channel ==1)&& (Dimm == 0) ) {
          DdrWarmThresholdCh1.Bits.DIMM0  = warmThreshold;
          DdrHotThresholdCh1.Bits.DIMM0  = hotThreshold;
        }

         if((Channel ==1)&& (Dimm == 1) ) {
          DdrWarmThresholdCh1.Bits.DIMM1  = warmThreshold;
          DdrHotThresholdCh1.Bits.DIMM1  = hotThreshold;
        }

       }//Warm and hot threshold Configuration End

     

      } //for (Dimm = 0; Dimm < MAX_DIMMS_IN_CHANNEL; Dimm++)
          
    } //for (Channel = 0; Channel < MAX_CHANNEL; Channel++)
    } // for Controller

    if(!ThermalEnables->UserThresholdEn) {//Warm and hot threshold Write Registers begin
              
        MrcWriteCR (MrcData, PCU_CR_DDR_WARM_THRESHOLD_CH0_PCU_REG, DdrWarmThresholdCh0.Data);
        MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "DDR_WARM_THRESHOLD_CH0 %Xh: %Xh \n", PCU_CR_DDR_WARM_THRESHOLD_CH0_PCU_REG, MrcReadCR (MrcData, PCU_CR_DDR_WARM_THRESHOLD_CH0_PCU_REG));
    
        MrcWriteCR (MrcData, PCU_CR_DDR_HOT_THRESHOLD_CH0_PCU_REG, DdrHotThresholdCh0.Data);
        MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "DDR_HOT_THRESHOLD_CH0 %Xh: %Xh \n", PCU_CR_DDR_HOT_THRESHOLD_CH0_PCU_REG, MrcReadCR (MrcData, PCU_CR_DDR_HOT_THRESHOLD_CH0_PCU_REG));
        
        MrcWriteCR (MrcData, PCU_CR_DDR_WARM_THRESHOLD_CH1_PCU_REG, DdrWarmThresholdCh1.Data);
        MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "DDR_WARM_THRESHOLD_CH1 %Xh: %Xh \n", PCU_CR_DDR_WARM_THRESHOLD_CH1_PCU_REG, MrcReadCR (MrcData, PCU_CR_DDR_WARM_THRESHOLD_CH1_PCU_REG));
        
        MrcWriteCR (MrcData, PCU_CR_DDR_HOT_THRESHOLD_CH1_PCU_REG, DdrHotThresholdCh1.Data);
        MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "DDR_HOT_THRESHOLD_CH1 %Xh: %Xh \n", PCU_CR_DDR_HOT_THRESHOLD_CH1_PCU_REG, MrcReadCR (MrcData, PCU_CR_DDR_HOT_THRESHOLD_CH1_PCU_REG));
        

     }//Warm and hot threshold threshold Write Register End

    
    

    ASSERT (ControllerSave != CONTROLLER_NOT_LOADED ); //If no controller is Save The system asserts
    

  if(!ThermalEnables->UserPowerWeightsEn) {
      MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "UP Server overriding Power weight Energy registers...\n");
      DdrEnergyScaleFactor.Data = 0;

    if((k0==0)||(k0==1)) {
        PwrWeight0 = &CltmPowerLookUpTable[i][j][k0][0];
        ASSERT(PwrWeight0 != NULL);//If PwrWeight0 is Null the system asserts.
        DdrEnergyScaleFactor.Bits.SCALEFACTOR = *PwrWeight0;
    }
    if((k1==0)||(k1==1)) {
        PwrWeight1 = &CltmPowerLookUpTable[i][j][k1][0];
        ASSERT(PwrWeight1 != NULL);//If PwrWeight1 is Null the system asserts.
        DdrEnergyScaleFactor.Bits.SCALEFACTOR = *PwrWeight1;
    }
    
    if ( ((k0==0)||(k0==1)) && ((k1==0)||(k1==1))) {
        (k0 >= k1) ? (DdrEnergyScaleFactor.Bits.SCALEFACTOR = *PwrWeight0) : (DdrEnergyScaleFactor.Bits.SCALEFACTOR = *PwrWeight1);
    }
    
    
    
    MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "DDR_ENERGY_SCALEFACTOR %Xh: %Xh \n", PCU_CR_DDR_ENERGY_SCALEFACTOR_PCU_REG, DdrEnergyScaleFactor.Data);
    MrcWriteCR (MrcData, PCU_CR_DDR_ENERGY_SCALEFACTOR_PCU_REG, DdrEnergyScaleFactor.Data);
    

    if((k0==0)||(k0==1)) {PwrWeight0++;}
    if((k1==0)||(k1==1)) {PwrWeight1++;}
    
    PmDimmRdEnergy.Data = 0;

    if ((k0==0)||(k0==1)){
        if (Outputs->Controller[ControllerSave].Channel[0].Dimm[0].Status == DIMM_PRESENT){
            PmDimmRdEnergy.Bits.DIMM0_RD_ENERGY = *PwrWeight0;
        }
        if (Outputs->Controller[ControllerSave].Channel[0].Dimm[1].Status == DIMM_PRESENT){
            PmDimmRdEnergy.Bits.DIMM1_RD_ENERGY = *PwrWeight0;
        }
        
    }
    MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "MCHBAR_CH0_CR_PM_DIMM_RD_ENERGY_REG %Xh: %Xh \n", MCHBAR_CH0_CR_PM_DIMM_RD_ENERGY_REG, PmDimmRdEnergy.Data);
    MrcWriteCR (MrcData, MCHBAR_CH0_CR_PM_DIMM_RD_ENERGY_REG, PmDimmRdEnergy.Data); 


    PmDimmRdEnergy.Data = 0;

    if ((k1==0)||(k1==1)){
        if (Outputs->Controller[ControllerSave].Channel[1].Dimm[0].Status == DIMM_PRESENT){
            PmDimmRdEnergy.Bits.DIMM0_RD_ENERGY = *PwrWeight1; 
            
        }
        if (Outputs->Controller[ControllerSave].Channel[1].Dimm[1].Status == DIMM_PRESENT){
            PmDimmRdEnergy.Bits.DIMM1_RD_ENERGY = *PwrWeight1;
        }

    }
        MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "MCHBAR_CH1_CR_PM_DIMM_RD_ENERGY_REG %Xh: %Xh \n", MCHBAR_CH1_CR_PM_DIMM_RD_ENERGY_REG, PmDimmRdEnergy.Data);
        MrcWriteCR (MrcData, MCHBAR_CH1_CR_PM_DIMM_RD_ENERGY_REG, PmDimmRdEnergy.Data);    

    if((k0==0)||(k0==1)) {PwrWeight0++;}
    if((k1==0)||(k1==1)) {PwrWeight1++;}
    PmDimmWrEnergy.Data                 = 0;

    if ((k0==0)||(k0==1)){
        if (Outputs->Controller[ControllerSave].Channel[0].Dimm[0].Status == DIMM_PRESENT){
            PmDimmWrEnergy.Bits.DIMM0_WR_ENERGY = *PwrWeight0;
        }
        if (Outputs->Controller[ControllerSave].Channel[0].Dimm[1].Status == DIMM_PRESENT){
            PmDimmWrEnergy.Bits.DIMM1_WR_ENERGY = *PwrWeight0;
        }
        
    }
   
    MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "MCHBAR_CH0_CR_PM_DIMM_WR_ENERGY_REG %Xh: %Xh \n", MCHBAR_CH0_CR_PM_DIMM_WR_ENERGY_REG, PmDimmWrEnergy.Data);
    MrcWriteCR (MrcData, MCHBAR_CH0_CR_PM_DIMM_WR_ENERGY_REG, PmDimmWrEnergy.Data);

    PmDimmWrEnergy.Data                 = 0;

    if ((k1==0)||(k1==1)){
        if (Outputs->Controller[ControllerSave].Channel[1].Dimm[0].Status == DIMM_PRESENT){
             PmDimmWrEnergy.Bits.DIMM0_WR_ENERGY = *PwrWeight1;
            
        }
        if (Outputs->Controller[ControllerSave].Channel[1].Dimm[1].Status == DIMM_PRESENT){
            PmDimmWrEnergy.Bits.DIMM1_WR_ENERGY = *PwrWeight1;
        }

    }
    MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "MCHBAR_CH1_CR_PM_DIMM_WR_ENERGY_REG %Xh: %Xh \n", MCHBAR_CH1_CR_PM_DIMM_WR_ENERGY_REG, PmDimmWrEnergy.Data);
    MrcWriteCR (MrcData, MCHBAR_CH1_CR_PM_DIMM_WR_ENERGY_REG, PmDimmWrEnergy.Data);

    if((k0==0)||(k0==1)) {PwrWeight0++;}
    if((k1==0)||(k1==1)) {PwrWeight1++;}
    PmDimmActEnergy.Data                  = 0;
    if ((k0==0)||(k0==1)){
        if (Outputs->Controller[ControllerSave].Channel[0].Dimm[0].Status == DIMM_PRESENT){
            PmDimmActEnergy.Bits.DIMM0_ACT_ENERGY = *PwrWeight0;
        }
        if (Outputs->Controller[ControllerSave].Channel[0].Dimm[1].Status == DIMM_PRESENT){
            PmDimmActEnergy.Bits.DIMM1_ACT_ENERGY = *PwrWeight0;
        }
        
    }
        
    MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "MCHBAR_CH0_CR_PM_DIMM_ACT_ENERGY_REG %Xh: %Xh \n", MCHBAR_CH0_CR_PM_DIMM_ACT_ENERGY_REG, PmDimmActEnergy.Data);
    MrcWriteCR (MrcData, MCHBAR_CH0_CR_PM_DIMM_ACT_ENERGY_REG, PmDimmActEnergy.Data);

    PmDimmActEnergy.Data                  = 0;
    if ((k1==0)||(k1==1)){
        if (Outputs->Controller[ControllerSave].Channel[1].Dimm[0].Status == DIMM_PRESENT){
            PmDimmActEnergy.Bits.DIMM0_ACT_ENERGY = *PwrWeight1;
        }
        if (Outputs->Controller[ControllerSave].Channel[1].Dimm[1].Status == DIMM_PRESENT){
            PmDimmActEnergy.Bits.DIMM1_ACT_ENERGY = *PwrWeight1;
        }
        
    }
    MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "MCHBAR_CH1_CR_PM_DIMM_ACT_ENERGY_REG %Xh: %Xh \n", MCHBAR_CH1_CR_PM_DIMM_ACT_ENERGY_REG, PmDimmActEnergy.Data);
    MrcWriteCR (MrcData, MCHBAR_CH1_CR_PM_DIMM_ACT_ENERGY_REG, PmDimmActEnergy.Data);

    if((k0==0)||(k0==1)) {PwrWeight0++;}
    if((k1==0)||(k1==1)) {PwrWeight1++;}
    PmDimmIdleEnergy.Data                   = 0;
    if ((k0==0)||(k0==1)){
        if (Outputs->Controller[ControllerSave].Channel[0].Dimm[0].Status == DIMM_PRESENT){
            PmDimmIdleEnergy.Bits.DIMM0_IDLE_ENERGY = *PwrWeight0;
        }
        if (Outputs->Controller[ControllerSave].Channel[0].Dimm[1].Status == DIMM_PRESENT){
            PmDimmIdleEnergy.Bits.DIMM1_IDLE_ENERGY = *PwrWeight0;
        }

    }
    MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "MCHBAR_CH0_CR_PM_DIMM_IDLE_ENERGY_REG %Xh: %Xh \n", MCHBAR_CH0_CR_PM_DIMM_IDLE_ENERGY_REG, PmDimmIdleEnergy.Data);
    MrcWriteCR (MrcData, MCHBAR_CH0_CR_PM_DIMM_IDLE_ENERGY_REG, PmDimmIdleEnergy.Data);

    PmDimmIdleEnergy.Data                   = 0;
    if ((k1==0)||(k1==1)){
        if (Outputs->Controller[ControllerSave].Channel[1].Dimm[0].Status == DIMM_PRESENT){
            PmDimmIdleEnergy.Bits.DIMM0_IDLE_ENERGY = *PwrWeight1;
        }
        if (Outputs->Controller[ControllerSave].Channel[1].Dimm[1].Status == DIMM_PRESENT){
            PmDimmIdleEnergy.Bits.DIMM1_IDLE_ENERGY = *PwrWeight1;
        }

    }
    MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "MCHBAR_CH1_CR_PM_DIMM_IDLE_ENERGY_REG %Xh: %Xh \n", MCHBAR_CH1_CR_PM_DIMM_IDLE_ENERGY_REG, PmDimmIdleEnergy.Data);
    MrcWriteCR (MrcData, MCHBAR_CH1_CR_PM_DIMM_IDLE_ENERGY_REG, PmDimmIdleEnergy.Data);

    if((k0==0)||(k0==1)) {PwrWeight0++;}
    if((k1==0)||(k1==1)) {PwrWeight1++;}
    PmDimmPdEnergy.Data                 = 0;
    if ((k0==0)||(k0==1)){
        if (Outputs->Controller[ControllerSave].Channel[0].Dimm[0].Status == DIMM_PRESENT){
            PmDimmPdEnergy.Bits.DIMM0_PD_ENERGY = *PwrWeight0;
        }
        if (Outputs->Controller[ControllerSave].Channel[0].Dimm[1].Status == DIMM_PRESENT){
            PmDimmPdEnergy.Bits.DIMM1_PD_ENERGY = *PwrWeight0;
        }

    }
    MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "MCHBAR_CH0_CR_PM_DIMM_PD_ENERGY_REG %Xh: %Xh \n", MCHBAR_CH0_CR_PM_DIMM_PD_ENERGY_REG, PmDimmPdEnergy.Data);
    MrcWriteCR (MrcData, MCHBAR_CH0_CR_PM_DIMM_PD_ENERGY_REG, PmDimmPdEnergy.Data);

    PmDimmPdEnergy.Data                 = 0;
    if ((k1==0)||(k1==1)){
        if (Outputs->Controller[ControllerSave].Channel[1].Dimm[0].Status == DIMM_PRESENT){
            PmDimmPdEnergy.Bits.DIMM0_PD_ENERGY = *PwrWeight1;
        }
        if (Outputs->Controller[ControllerSave].Channel[1].Dimm[1].Status == DIMM_PRESENT){
            PmDimmPdEnergy.Bits.DIMM1_PD_ENERGY = *PwrWeight1;
        }

    }
    MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "MCHBAR_CH1_CR_PM_DIMM_PD_ENERGY_REG %Xh: %Xh \n", MCHBAR_CH1_CR_PM_DIMM_PD_ENERGY_REG, PmDimmPdEnergy.Data);
    MrcWriteCR (MrcData, MCHBAR_CH1_CR_PM_DIMM_PD_ENERGY_REG, PmDimmPdEnergy.Data);

  }

  if(!ThermalEnables->UserBudgetEn) {
      MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "UP Server Overriding Power budget registers...\n");
     
    if((k0==0)||(k0==1)) {
        PwrWeight0 = &CltmPowerLookUpTable[i][j][k0][0];
        PwrWeight0 = PwrWeight0 + WARM_BUDGET_POSITION;
        ASSERT(PwrWeight0 != NULL);//If PwrWeight0 is Null the system asserts.
        
    }
    if((k1==0)||(k1==1)) {
        PwrWeight1 = &CltmPowerLookUpTable[i][j][k1][0];
        PwrWeight1 = PwrWeight1 + WARM_BUDGET_POSITION;
        ASSERT(PwrWeight1 != NULL);//If PwrWeight1 is Null the system asserts.
        
    }

    DdrWarmBudgetCh0.Data        = 0;
    if ((k0==0)||(k0==1)){
        if (Outputs->Controller[ControllerSave].Channel[0].Dimm[0].Status == DIMM_PRESENT){
            DdrWarmBudgetCh0.Bits.DIMM0  = *PwrWeight0;
        }
        if (Outputs->Controller[ControllerSave].Channel[0].Dimm[1].Status == DIMM_PRESENT){
            DdrWarmBudgetCh0.Bits.DIMM1  = *PwrWeight0;
        }

    }
        
    MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "DDR_WARM_BUDGET_CH0 %Xh: %Xh \n", PCU_CR_DDR_WARM_BUDGET_CH0_PCU_REG, DdrWarmBudgetCh0.Data);
    MrcWriteCR (MrcData, PCU_CR_DDR_WARM_BUDGET_CH0_PCU_REG, DdrWarmBudgetCh0.Data);

    DdrWarmBudgetCh1.Data        = 0;
    if ((k1==0)||(k1==1)){
        if (Outputs->Controller[ControllerSave].Channel[1].Dimm[0].Status == DIMM_PRESENT){
            DdrWarmBudgetCh1.Bits.DIMM0  = *PwrWeight1;
        }
        if (Outputs->Controller[ControllerSave].Channel[1].Dimm[1].Status == DIMM_PRESENT){
            DdrWarmBudgetCh1.Bits.DIMM1  = *PwrWeight1;
        }

    }
    MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "DDR_WARM_BUDGET_CH1 %Xh: %Xh \n", PCU_CR_DDR_WARM_BUDGET_CH1_PCU_REG, DdrWarmBudgetCh1.Data);
    MrcWriteCR (MrcData, PCU_CR_DDR_WARM_BUDGET_CH1_PCU_REG, DdrWarmBudgetCh1.Data);

    if((k0==0)||(k0==1)) {PwrWeight0++;}
    if((k1==0)||(k1==1)) {PwrWeight1++;}
    DdrHotBudgetCh0.Data        = 0;
    if ((k0==0)||(k0==1)){
        if (Outputs->Controller[ControllerSave].Channel[0].Dimm[0].Status == DIMM_PRESENT){
            DdrHotBudgetCh0.Bits.DIMM0  = *PwrWeight0;
        }
        if (Outputs->Controller[ControllerSave].Channel[0].Dimm[1].Status == DIMM_PRESENT){
            DdrHotBudgetCh0.Bits.DIMM1  = *PwrWeight0;
        }

    }

    MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "DDR_HOT_BUDGET_CH0 %Xh: %Xh \n", PCU_CR_DDR_HOT_BUDGET_CH0_PCU_REG, DdrHotBudgetCh0.Data);
    MrcWriteCR (MrcData, PCU_CR_DDR_HOT_BUDGET_CH0_PCU_REG, DdrHotBudgetCh0.Data);

    DdrHotBudgetCh1.Data        = 0;

    if ((k1==0)||(k1==1)){
        if (Outputs->Controller[ControllerSave].Channel[1].Dimm[0].Status == DIMM_PRESENT){
            DdrHotBudgetCh1.Bits.DIMM0  = *PwrWeight1;
        }
        if (Outputs->Controller[ControllerSave].Channel[1].Dimm[1].Status == DIMM_PRESENT){
            DdrHotBudgetCh1.Bits.DIMM1  = *PwrWeight1;
        }

    }

    MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "DDR_HOT_BUDGET_CH1 %Xh: %Xh \n", PCU_CR_DDR_HOT_BUDGET_CH1_PCU_REG, DdrHotBudgetCh1.Data);
    MrcWriteCR (MrcData, PCU_CR_DDR_HOT_BUDGET_CH1_PCU_REG, DdrHotBudgetCh1.Data);

 }

 
    //
    // POWER THERMAL MANAGEMENT CONTROL
    //
    DdrPtmCtl.Data                    = MrcReadCR (MrcData, PCU_CR_DDR_PTM_CTL_PCU_REG);
    DdrPtmCtl.Bits.OLTM_ENABLE        = ThermalEnables->EnableOltm;//Disable , 0,  Not available for UP Platforms
    DdrPtmCtl.Bits.CLTM_ENABLE        = ThermalEnables->EnableCltm;//Default 1
    DdrPtmCtl.Bits.REFRESH_2X_MODE    = ThermalEnables->Refresh2X;//Default 1, REFRESH_2X_WARM_HOT if dimm do not support then equals 0
    /*
    DdrPtmCtl.Bits.EXTTS_ENABLE       = ThermalEnables->EnableExtts;//Default 0
    DdrPtmCtl.Bits.PDWN_CONFIG_CTL    = ThermalEnables->EnablePwrDn;//Default 1, BIOS is in control of powednmodes  
    
    //DdrPtmCtl.Bits.DISABLE_DRAM_TS  = !ThermalEnables->LpddrThermalSensor; //If not ULT this is disable or Value 1
    */

    MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "DDR_PTM_CTL  %Xh to program: %Xh \n", PCU_CR_DDR_PTM_CTL_PCU_REG, DdrPtmCtl.Data);
    MrcWriteCR (MrcData, PCU_CR_DDR_PTM_CTL_PCU_REG, DdrPtmCtl.Data);
    MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "DDR_PTM_CTL %Xh: %Xh \n", PCU_CR_DDR_PTM_CTL_PCU_REG, MrcReadCR (MrcData, PCU_CR_DDR_PTM_CTL_PCU_REG));
     

  } else {
     //
    // POWER THERMAL MANAGEMENT CONTROL
    //
    Outputs->CLTM_SPD_Conf = PROCESS_FAILED;
    MrcCltmDisable(MrcData);
    return;


  }

  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "MrcCltmInit - End.\n");
 
}
#endif // AMI_OVERRIDE_FOR_UPSERVER_SUPPORT
