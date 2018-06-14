//*************************************************************************
//*************************************************************************
//**                                                                     **
//**        (C)Copyright 1985-2013, American Megatrends, Inc.            **
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
// $Header: /Alaska/BIN/Chipset/Intel/SouthBridge/LynxPoint/Intel Pch SB Chipset/SB SMI/SBSMI.c 19    7/12/15 11:08p Dennisliu $
//
// $Revision: 19 $
//
// $Date: 7/12/15 11:08p $
//*************************************************************************
// Revision History
// ----------------
// $Log: /Alaska/BIN/Chipset/Intel/SouthBridge/LynxPoint/Intel Pch SB Chipset/SB SMI/SBSMI.c $
// 
// 19    7/12/15 11:08p Dennisliu
// [TAG] None
// [Category] Improvement
// [Description] Coding error in ElogGenerateNmiNow()
// [Files] Chipset\SB\SBSMI.c 
// 
// 17    12/30/13 5:59a Barretlin
// [TAG]  		EIP144559
// [Category]  	Improvement
// [Description]  	S3 can't resume via USB KB & MS under usb3.0 port in
// special case
// [Files]  		SBSMI.c SBSMI.h SBGeneric.c
// 
// 16    10/01/13 7:53a Barretlin
// [TAG]  		EIP137385
// [Category]  	Bug Fix
// [Severity]  	Normal
// [Symptom]  	System hang if power button pushed on BSU, after windows
// shutdown / reboot
// [RootCause]  	Push power button key on RF keyboard will triger xhci hw
// smi, but xhci is set D3hot state in power button handler, then we can't
// service it
// [Solution]  	Stop xhci before we set D3hot state and check if
// hciversion is valid
// [Files]  		SBSMI.c
// 
// 15    5/28/13 11:45p Scottyang
// [TAG]  		None
// [Category]  	Bug Fix
// [Severity]  	Normal
// [Symptom]  	GbE cannot wake form S5 under DOS.
// [RootCause]  	The base address is incorrect.
// [Solution]  	Correct base address.
// [Files]  		SBSMI.c
// 
// 14    4/19/13 6:34a Wesleychen
// [TAG]           None
// [Category]      Improvement
// [Description]   Update GbES02SxWorkaround() and add 
//                 UsbS02SxWorkaround() for SBPwrBtnHandler().
// [Files]         SBSMI.c; SBSMI.h; SBGeneric.c; SBCspLib.h
// 
// 12    3/21/13 3:39a Scottyang
// [TAG]  		EIP83075
// [Category]  	Bug Fix
// [Severity]  	Normal
// [Symptom]  	USB3.0 mouse can not resume form S3 if shot down at POST
// before. 
// [Solution]  	Additional xHCI Controller Configurations Prior to Enter
// S5.
// [Files]  		SBSMI.c
// 
// 11    3/19/13 8:37a Scottyang
// [TAG]  		None
// [Category]  	Improvement
// [Description]  	Improve alternate access mode enable/disable routine.
// [Files]  		SBGeneric.c, SBCspLib.h, SBSMI.c
// 
// 10    1/11/13 4:46a Scottyang
// [TAG]  		None
// [Category]  	Improvement
// [Description]  	Fixed coding error.
// [Files]  		SBSMI.c
// 
// 9     1/04/13 2:45a Scottyang
// [TAG]         EIP104199
// [Category]    Improvement
// [Description] Register dummy Handler for all Tco Smi
// [Files]       SBSMI.c;
// 
// 8     10/30/12 10:04p Scottyang
// [TAG]  		None
// [Category]  	Improvement
// [Description]  	Remove clear SMI state and Y2K roller for PFAT
// function.
// [Files]  		SBSMI.c, SBGeneric.c
// 
// 7     10/26/12 1:11a Scottyang
// [TAG]  		CHECK_BS_VARIABLE
// [Category]  	Improvement
// [Description]  	If project has module NVRamSMI then don't need to check
// this.
// [Files]  		SBSMI.c
// 
// 6     10/12/12 8:06a Scottyang
// [TAG]  		None
// [Category]  	Improvement
// [Description]  	Fixed the system hang when Y2K roll over is occur with
// TCO SMI enabled.
// 
// 5     9/26/12 3:58a Victortu
// [TAG]           None
// [Category]      Improvement
// [Description]   Update for PCH LP GPIO compatible.
// [Files]         SB.sdl, SB.H, AcpiModeEnable.c, AcpiModeEnable.sdl,
// SBDxe.c, SBGeneric.c, SBPEI.c, SBSMI.c, SleepSmi.c,
// SmiHandlerPorting.c, SmiHandlerPorting2.c
// 
// 4     8/13/12 10:31a Victortu
// [TAG]           None
// [Category]      Improvement
// [Description]   Implement BIOS Lock function.
// [Files]         SBCspLib.h, SBDxe.c, SBSMI.c, SBSMI.dxs, SBSMI.sdl
// 
// 3     7/27/12 6:17a Victortu
// [TAG]           None
// [Category]      Improvement
// [Description]   Update to support ULT Platform.
// [Files]         SB.H, SB.mak, SB.sdl, SB.sd, SBSetup.c,
// AcpiModeEnable.c, SBDxe.c, SBPEI.c, SBSMI.c, SleepSmi.c,
// SmiHandlerPorting.c, SmiHandlerPorting2.c, SBPPI.h, Pch.sdl
// 
// 2     6/13/12 11:36p Victortu
// [TAG]           None
// [Category]      Improvement
// [Description]   Implement Warm Boot function for Secure Flash feature.
// [Files]         SB.H, SB.mak, SB.sdl, SBDxe.c, SBGeneric.c, SBPEI.c,
// SBSMI.c
// 
// 1     2/08/12 8:31a Yurenlai
// Intel Lynx Point/SB eChipset initially releases.
// 
//*************************************************************************
//<AMI_FHDR_START>
//
// Name:        SBSMI.c
//
// Description: This file contains code for all North Bridge SMI events
//
//<AMI_FHDR_END>
//*************************************************************************

//----------------------------------------------------------------------------
// Include(s)
//----------------------------------------------------------------------------

#include <Token.h>
#include <Setup.h>
#include <AmiDxeLib.h>
#include <AMICSPLIBInc.h>
#include <AmiCspLib.h>
#if defined(PI_SPECIFICATION_VERSION)&&(PI_SPECIFICATION_VERSION>=0x0001000A)&&(CORE_COMBINED_VERSION >= 0x4028B)
#include <Protocol\SmmPowerButtonDispatch2.h>
#include <Protocol\SmmBase2.h>
#include <Protocol\S3SaveState.h>
#include <Protocol\SmmSwDispatch2.h>
#else
#include <Protocol\SmmPowerButtonDispatch.h>
#include <Protocol\SmmBase.h>
#include <Protocol\BootScriptSave.h>
#include <Protocol\SmmSwDispatch.h>
#endif
#if SB_PCIE_ERROR_LOG_SUPPORT
#include <Protocol\GenericElog.h>
#endif
#include <Protocol\SBSmiProtocol.h>
#include <Edk\Foundation\Framework\Protocol\SmmIchnDispatch\SmmIchnDispatch.h>
#include <Protocol\PchPlatformPolicy\PchPlatformPolicy.h>
#include <ReferenceCode\Chipset\LynxPoint\Protocol\SmmIchnDispatchEx\SmmIchnDispatchEx.h>
#include <ReferenceCode\Chipset\LynxPoint\Protocol\SmmIoTrapDispatch\SmmIoTrapDispatch.h>
#include <Protocol\SBPlatformData.h>
#include <SBSMI.h>

//----------------------------------------------------------------------------
// Constant, Macro and Type Definition(s)
//----------------------------------------------------------------------------
// Constant Definition(s)
#define GBE_MAX_LOOP_TIME 4000

#if defined(PI_SPECIFICATION_VERSION)&&(PI_SPECIFICATION_VERSION>=0x0001000A)&&(CORE_COMBINED_VERSION >= 0x4028B)
#define AMI_SMM_SW_DISPATCH_PROTOCOL           EFI_SMM_SW_DISPATCH2_PROTOCOL
#define AMI_SMM_SW_DISPATCH_CONTEXT            EFI_SMM_SW_REGISTER_CONTEXT
#define AMI_SMM_POWER_BUTTON_DISPATCH_PROTOCOL EFI_SMM_POWER_BUTTON_DISPATCH2_PROTOCOL
#define AMI_SMM_POWER_BUTTON_DISPATCH_CONTEXT  EFI_SMM_POWER_BUTTON_REGISTER_CONTEXT
#define SMM_CHILD_DISPATCH_SUCCESS             EFI_SUCCESS
#else
#define AMI_SMM_SW_DISPATCH_PROTOCOL           EFI_SMM_SW_DISPATCH_PROTOCOL
#define AMI_SMM_SW_DISPATCH_CONTEXT            EFI_SMM_SW_DISPATCH_CONTEXT
#define AMI_SMM_POWER_BUTTON_DISPATCH_PROTOCOL EFI_SMM_POWER_BUTTON_DISPATCH_PROTOCOL
#define AMI_SMM_POWER_BUTTON_DISPATCH_CONTEXT  EFI_SMM_POWER_BUTTON_DISPATCH_CONTEXT
#define SMM_CHILD_DISPATCH_SUCCESS
#endif

#ifndef NvramSmiSupport
#define CHECK_BS_VARIABLE 1
#endif

#if defined NvramSmiSupport && NvramSmiSupport
#define CHECK_BS_VARIABLE 0
#else
#define CHECK_BS_VARIABLE 1
#endif


// Macro Definition(s)

// Type Definition(s)

// Function Prototype(s)

//----------------------------------------------------------------------------
// Variable and External Declaration(s)
//----------------------------------------------------------------------------
// Variable Declaration(s)
#if SB_PCIE_ERROR_LOG_SUPPORT

SB_PCIE_ERROR_LOG_DISPATCH_LINK  *gSbPcieErrorLogDispatchHead = 0, *gSbPcieErrorLogDispatchTail = 0;

UINT32 SBPcieBridge[] = 
{
  {(UINT32)SB_PCIE_CFG_ADDRESS(PCIEBRS_BUS,  PCIEBRS_DEV,  PCIEBRS_FUN,  PCI_VID)},
  {(UINT32)SB_PCIE_CFG_ADDRESS(PCIEBRS2_BUS, PCIEBRS2_DEV, PCIEBRS2_FUN, PCI_VID)},
  {(UINT32)SB_PCIE_CFG_ADDRESS(PCIEBRS3_BUS, PCIEBRS3_DEV, PCIEBRS3_FUN, PCI_VID)},
  {(UINT32)SB_PCIE_CFG_ADDRESS(PCIEBRS4_BUS, PCIEBRS4_DEV, PCIEBRS4_FUN, PCI_VID)},
  {(UINT32)SB_PCIE_CFG_ADDRESS(PCIEBRS5_BUS, PCIEBRS5_DEV, PCIEBRS5_FUN, PCI_VID)},
  {(UINT32)SB_PCIE_CFG_ADDRESS(PCIEBRS6_BUS, PCIEBRS6_DEV, PCIEBRS6_FUN, PCI_VID)},
  {(UINT32)SB_PCIE_CFG_ADDRESS(PCIEBRS7_BUS, PCIEBRS7_DEV, PCIEBRS7_FUN, PCI_VID)},
  {(UINT32)SB_PCIE_CFG_ADDRESS(PCIEBRS8_BUS, PCIEBRS8_DEV, PCIEBRS8_FUN, PCI_VID)},
  {0xFFFFFFFF}
};
#endif

BOOLEAN gIsLastState    = FALSE;
BOOLEAN gPchWakeOnLan   = FALSE;
EFI_SMM_ICHN_DISPATCH_PROTOCOL    *gIchnDispatch;
EFI_RESET_SYSTEM gSmmResetSystem = NULL;
#if defined(PI_SPECIFICATION_VERSION)&&(PI_SPECIFICATION_VERSION>=0x0001000A)&&(CORE_COMBINED_VERSION >= 0x4028B)
EFI_SMM_BASE2_PROTOCOL  *gSmmBase2;
#endif

// GUID Definition(s)
#if SB_PCIE_ERROR_LOG_SUPPORT
EFI_GUID gSbPcieErrorLogDispatchProtocolGuid    = EFI_SB_PCIE_ERROR_LOG_DISPATCH_PROTOCOL_GUID;
EFI_GUID gElogProtocolGuid                      = EFI_SM_ELOG_PROTOCOL_GUID;
#endif
EFI_GUID gAmiSbSmiProtocolGuid                  = AMI_SB_SMI_PROTOCOL_GUID;
EFI_GUID gEfiSmmIchnExDispatchProtocolGuid      = EFI_SMM_ICHN_DISPATCH_EX_PROTOCOL_GUID;
EFI_GUID gIchnDispatchProtocolGuid              = EFI_SMM_ICHN_DISPATCH_PROTOCOL_GUID;
EFI_GUID gDxePchPlatformPolicyProtocolGuid      = DXE_PCH_PLATFORM_POLICY_PROTOCOL_GUID;
EFI_GUID gEfiSmmIoTrapDispatchProtocolGuid      = EFI_SMM_IO_TRAP_DISPATCH_PROTOCOL_GUID;

#if defined(PI_SPECIFICATION_VERSION)&&(PI_SPECIFICATION_VERSION<0x0001000A)&&(CORE_COMBINED_VERSION >= 0x4028B)
EFI_GUID gSwDispatchProtocolGuid                = EFI_SMM_SW_DISPATCH_PROTOCOL_GUID;
#endif

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:   AddLink
//
// Description: Create and add link to specified list.
//
// Parameters:  Size -
//              Head - 
//              Tail -
//
// Returns:     VOID Pointer
//
// Modified:
//
// Referrals:   SmmAllocatePool
//
// Notes:       Here is the control flow of this function:
//              1. Allocate Link in Smm Pool.
//              2. Add Link to end.
//              3. Return Link address.
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

VOID * AddLink (
    IN UINT32       Size,
    IN VOID         **Head,
    IN VOID         **Tail )
{
    VOID *Link;

    if (pSmst->SmmAllocatePool(0, Size, &Link) != EFI_SUCCESS) return 0;

    ((GENERIC_LINK*)Link)->Link = 0;
    if (!*Head) {
        *Head = *Tail = Link;
    } else {
        ((GENERIC_LINK*)*Tail)->Link = Link;
        *Tail = Link;
    }

    return Link;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:   RemoveLink
//
// Description: Remove link from specified list.
//
// Parameters:  Handle - EFI Handle
//              Head -
//              Tail -
//
// Returns:     BOOLEAN
//                  TRUE if link was removed. FALSE if link not in the list.
//
// Modified:
//
// Referrals:   SmmFreePool
//
// Notes:       Here is the control flow of this function:
//              1. Search link list for Link.
//              2. Remove link from list.
//              3. Free link.
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

BOOLEAN RemoveLink (
    IN EFI_HANDLE   Handle,
    IN VOID         **Head,
    IN VOID         **Tail )
{
    GENERIC_LINK *PrevLink,*Link;

    PrevLink = *Head;

    // Is link first. Link address is the same as the Handle. 
    if (((GENERIC_LINK*)*Head) == Handle) {
        if (PrevLink == *Tail) *Tail = 0; // If Tail = Head, then 0.
        *Head = PrevLink->Link;
        pSmst->SmmFreePool(PrevLink);
        return TRUE;
    }

    // Find Link.
    for (Link=PrevLink->Link; Link; PrevLink=Link, Link=Link->Link) {
        if (Link == Handle) {   // Link address is the same as the Handle.
            if (Link == *Tail) *Tail = PrevLink;
            PrevLink->Link = Link->Link;
            pSmst->SmmFreePool(Link);
            return TRUE;
        }
    }

    return FALSE;
}

#if SB_PCIE_ERROR_LOG_SUPPORT
//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:   EfiSbPcieErrorLogEnRegister
//
// Description: Register a Link on SbPcieErrorLog enable SMI.
//
// Parameters:  This - 
//              Function -
//              Context - 
//              
//
// Returns:     Handle -
//              EFI_STATUS
//
// Modified:    gSbPcieErrorLogDispatchHead, gSbPcieErrorLogDispatchTail
//
// Referrals:   AddLink
//
// Notes:       Here is the control flow of this function:
//              1. Verify if Context if valid. If invalid,
//                 return EFI_INVALID_PARAMETER.
//              2. Allocate structure and add to link list.
//              3. Fill link.
//              4. Enable Smi Source.
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS SbPcieErrorLogRegister (
    IN EFI_SB_PCIE_ERROR_LOG_DISPATCH_PROTOCOL   *This,
    IN EFI_SB_PCIE_ERROR_LOG_DISPATCH            Function,
    OUT EFI_HANDLE                  *Handle )
{
    SB_PCIE_ERROR_LOG_DISPATCH_LINK *NewLink;

    NewLink = AddLink( sizeof(SB_PCIE_ERROR_LOG_DISPATCH_LINK), \
                       &gSbPcieErrorLogDispatchHead, \
                       &gSbPcieErrorLogDispatchTail );
    if (!NewLink) return EFI_OUT_OF_RESOURCES;

    NewLink->Function = Function;
    *Handle = NewLink;

    return EFI_SUCCESS;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:   SbPcieErrorLogUnregister
//
// Description: Unregister a Link on SbPcieErrorLog enable SMI.
//
// Parameters:  This -
//              Handle -
//
// Returns:     EFI_STATUS
//
// Modified:    gSbPcieErrorLogDispatchHead, gSbPcieErrorLogDispatchTail
//
// Referrals:   RemoveLink
//
// Notes:       Here is the control flow of this function:
//              1. Remove link. If no link, return EFI_INVALID_PARAMETER.
//              2. Disable SMI Source if no other handlers using source.
//              3. Return EFI_SUCCESS.
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS SbPcieErrorLogUnregister (
    IN EFI_SB_PCIE_ERROR_LOG_DISPATCH_PROTOCOL   *This,
    IN EFI_HANDLE                   Handle )
{
    if (!RemoveLink(Handle, &gSbPcieErrorLogDispatchHead, &gSbPcieErrorLogDispatchTail))
        return EFI_INVALID_PARAMETER;
    return EFI_SUCCESS;
}
#endif

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:   CheckReadyFlag
//
// Description: Check ready flag to see if writing to MDIC is done.
//
// Parameters:  GbEBar        - GbE Memory Base Address Register
//
// Returns:     EFI_SUCCESS - Successfully completed.
//              EFI_TIMEOUT - Checking flag time out.
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS CheckReadyFlag ( IN UINT32 GbEBar )
{
  UINT32  ReadyFlag;
  UINT32  LoopTime;

  ReadyFlag = 0;

  for (LoopTime = 0; LoopTime < GBE_MAX_LOOP_TIME; LoopTime++) {
    ReadyFlag = READ_MEM32 (GbEBar + R_PCH_MBARA_GBECSR3) & B_PCH_MBARA_GBECSR3_RB;

    if (ReadyFlag) {
      break;
    }

    CountTime((10), PM_BASE_ADDRESS);
  }

  if (LoopTime >= GBE_MAX_LOOP_TIME) {
    return EFI_TIMEOUT;
  }

  return EFI_SUCCESS;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:   GbES02SxWorkaround
//
// Description: PCH BIOS Spec Rev 0.7.0 Section 10.6
//              Additional Internal GbE Controller special cases WOL Support
//
// Parameters:  None
//
// Returns:     None
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID GbES02SxWorkaround ( VOID )
{
  UINTN       PciD25F0RegBase;
  UINTN       PciD31F0RegBase;
  UINT32      GbEBar;
  UINT32      GbEBarB;
  UINT16      CmdReg;
  UINT32      RAL0;
  UINT32      RAH0;
  UINT32      PhyCtrl;
  UINT32      ExtCnfCtrl;
  UINT32      Buffer;
  UINT32      LoopTime;
  UINT32      RootComplexBar;
  UINT32      PchGpioBase;
  EFI_STATUS  Status;

  PciD25F0RegBase = MmPciAddress (
                      PCIEX_BASE_ADDRESS,
                      PCI_BUS_NUMBER_PCH_LAN,
                      PCI_DEVICE_NUMBER_PCH_LAN,
                      PCI_FUNCTION_NUMBER_PCH_LAN,
                      0
                      );
  PciD31F0RegBase = MmPciAddress (
                      PCIEX_BASE_ADDRESS,
                      0,
                      PCI_DEVICE_NUMBER_PCH_LPC,
                      PCI_FUNCTION_NUMBER_PCH_LPC,
                      0
                      );
  RootComplexBar  = (READ_MEM32 (PciD31F0RegBase + SB_REG_RCBA)) & ~BIT0;
  PchGpioBase     = (MmioRead32 (PciD31F0RegBase + R_PCH_LPC_GPIO_BASE)) &~BIT0;
  GbEBar          = 0;
  GbEBarB         = 0;
  CmdReg          = 0;
  Buffer          = 0;

  if (((MmioRead16 (RootComplexBar + R_PCH_RCRB_BUC)) & BIT5) == 0) {
    ///
    /// System BIOS requires to program the registers listed below for internal GbE to function upon S0 to S3,4,5 transition
    /// (When ME off and GbE device in D0)
    ///
    /// Note: Time out should be applied for MBARA + Offset 20h[28] verification to avoid non respond loop. Upon time out,
    ///       system BIOS is required to clear MBARA + Offset F00h [5] = 0b before exiting the WA.
    ///
    /// Check if GbE device is in D0 state
    ///
    if ((MmioRead16 (PciD25F0RegBase + R_PCH_LAN_PMCS) & (UINT16) B_PCH_LAN_PMCS_PS) == (UINT16) V_PCH_LAN_PMCS_PS0) {
      GbEBar = MmioRead32 (PciD25F0RegBase + R_PCH_LAN_MEM_BASE_A);
      ///
      /// Step 1
      /// If MBARA + Offset 5800h [0] = 1b then proceed the steps below
      ///
      if (MmioRead32 (GbEBar + R_PCH_MBARA_GBECSR9) & B_PCH_MBARA_GBECSR9_APME) {
        ///
        /// Step 2
        /// System BIOS perform read to MBARA + Offset 5400h [31:0], MBARA + Offset 5404h [31:0]
        /// and MBARA + Offset F00h [31:0]
        ///
        RAL0        = MmioRead32 (GbEBar + R_PCH_MBARA_GBECSR7);
        RAH0        = MmioRead32 (GbEBar + R_PCH_MBARA_GBECSR8);
        ExtCnfCtrl  = MmioRead32 (GbEBar + R_PCH_MBARA_GBECSR5);
        ///
        /// Step 3
        /// Ensure that MBARA + Offset F00h [5] = 1b
        /// a. Set MBARA + Offset F00h [31:0] value with the value read in step 2 or with 0x20 (set bit 5)
        /// b. Read MBARA + Offset F00h
        /// c. If MBARA + Offset F00h [5] = 1b (true) continue else wait X Sec and go back to step 3.b for Y times
        ///    (X*Y  totals to ~200mSec) if false - exit flow by jumping to step 32.
        ///
        MmioWrite32 (GbEBar + R_PCH_MBARA_GBECSR5, ExtCnfCtrl | B_PCH_MBARA_GBECSR5_SWFLAG);

        for (LoopTime = 0; LoopTime < GBE_MAX_LOOP_TIME; LoopTime++) {
          ExtCnfCtrl = MmioRead32 (GbEBar + R_PCH_MBARA_GBECSR5);

          if (ExtCnfCtrl & B_PCH_MBARA_GBECSR5_SWFLAG) {
            break;
          }

          CountTime((50), PM_BASE_ADDRESS);
        }

        if (LoopTime >= GBE_MAX_LOOP_TIME) {
          goto ExitGbEWa;
        }
        ///
        /// Step 4
        /// If MBARA + Offset 5B54h [15] = 1b then jump to Step 10
        ///
        if ((MmioRead32 (GbEBar + 0x5B54) & BIT15) != BIT15) {
          ///
          /// Step 5
          /// If MBARA + Offset F10h [2] = 1b, then set MBARA + Offset F10h[1] = 1b. Else clear MBARA + Offset F10h[1] = 0b
          ///
          if (MmioRead32 (GbEBar + R_PCH_MBARA_GBECSR6) & B_PCH_MBARA_GBECSR6_LPLUND) {
              SET_MEM32(GbEBar + R_PCH_MBARA_GBECSR6, (UINT32) B_PCH_MBARA_GBECSR6_LPLUD);
          } else {
            RESET_MEM32 (GbEBar + R_PCH_MBARA_GBECSR6, (UINT32)B_PCH_MBARA_GBECSR6_LPLUD);
          }
          ///
          /// Step 6
          /// Set MBARA + Offset 20h = 0x043f0000. Verify MBARA + Offset 20h[28] = 1b
          ///
          MmioWrite32 ((GbEBar + R_PCH_MBARA_GBECSR3), 0x043f0000);

          Status = CheckReadyFlag (GbEBar);
          if (EFI_ERROR (Status)) {
            goto ExitGbEWa;
          }
          ///
          /// Step 7
          /// Wait 4 mSec
          ///
          CountTime((4 * 1000), PM_BASE_ADDRESS);
          ///
          /// Step 8
          /// Set MBARA + Offset 20h = 0x04390000 or with 0x400 or with 0x40 if MBARA + Offset F10h [3] = 1b
          /// or with 0x04 if MBARA + Offset F10h [2] = 1b
          ///
          Buffer = 0x04390000 | 0x400;
          if (MmioRead32 (GbEBar + R_PCH_MBARA_GBECSR6) & B_PCH_MBARA_GBECSR6_GbE_DIS) {
            Buffer |= 0x40;
          }

          if (MmioRead32 (GbEBar + R_PCH_MBARA_GBECSR6) & B_PCH_MBARA_GBECSR6_LPLUND) {
            Buffer |= 0x04;
          }

          MmioWrite32 ((GbEBar + R_PCH_MBARA_GBECSR3), Buffer);
          ///
          /// Step 9
          /// Verify MBARA + Offset 20h[28] = 1b
          ///
          Status = CheckReadyFlag (GbEBar);
          if (EFI_ERROR (Status)) {
            goto ExitGbEWa;
          }
        }
        ///
        /// Step 10
        /// Set MBARA + Offset 20h = 0x043f6400
        ///
        MmioWrite32 ((GbEBar + R_PCH_MBARA_GBECSR3), 0x043f6400);
        ///
        /// Step 11
        /// Wait 4 mSec
        ///
        CountTime((4 * 1000), PM_BASE_ADDRESS);
        ///
        /// Step 12
        /// Set MBARA + Offset F10h [6] = 1b (read modify write)
        ///
        PhyCtrl = MmioRead32 (GbEBar + R_PCH_MBARA_GBECSR6);
        MmioWrite32 (GbEBar + R_PCH_MBARA_GBECSR6, PhyCtrl | B_PCH_MBARA_GBECSR6_GGD);
        ///
        /// Step 13
        /// Verify MBARA + Offset 20h[28] = 1b, set MBARA + Offset 20h = 0x4310010
        ///
        Status = CheckReadyFlag (GbEBar);
        if (EFI_ERROR (Status)) {
          goto ExitGbEWa;
        }

        MmioWrite32 ((GbEBar + R_PCH_MBARA_GBECSR3), 0x4310010);
        ///
        /// Step 14
        /// Verify MBARA + Offset 20h[28] = 1b, set MBARA + Offset 20h = 0x4320000 or with
        /// the least significant word of MBARA + offset 5400 that read in step 2
        ///
        Status = CheckReadyFlag (GbEBar);
        if (EFI_ERROR (Status)) {
          goto ExitGbEWa;
        }

        MmioWrite32 ((GbEBar + R_PCH_MBARA_GBECSR3), (0x4320000 | (RAL0 & 0x0000FFFF)));
        ///
        /// Step 15
        /// Verify MBARA + Offset 20h[28] = 1b, set MBARA + Offset 20h = 0x4310011
        ///
        Status = CheckReadyFlag (GbEBar);
        if (EFI_ERROR (Status)) {
          goto ExitGbEWa;
        }

        MmioWrite32 ((GbEBar + R_PCH_MBARA_GBECSR3), 0x4310011);
        ///
        /// Step 16
        /// Verify MBARA + Offset 20h[28] = 1b, set MBARA + Offset 20h = 0x4320000 or with
        /// the most significant word of MBARA + offset 5400 that read in step 2
        ///
        Status = CheckReadyFlag (GbEBar);
        if (EFI_ERROR (Status)) {
          goto ExitGbEWa;
        }

        MmioWrite32 ((GbEBar + R_PCH_MBARA_GBECSR3), (0x4320000 | (RAL0 >> 16)));
        ///
        /// Step 17
        /// Verify MBARA + Offset 20h[28] = 1b, set MBARA + Offset 20h = 0x4310012
        ///
        Status = CheckReadyFlag (GbEBar);
        if (EFI_ERROR (Status)) {
          goto ExitGbEWa;
        }

        MmioWrite32 ((GbEBar + R_PCH_MBARA_GBECSR3), 0x4310012);
        ///
        /// Step 18
        /// Verify MBARA + Offset 20h[28] = 1b, set MBARA + Offset 20h = 0x4320000 or with
        /// the least significant word of MBARA + offset 5404 that read in step 2
        ///
        Status = CheckReadyFlag (GbEBar);
        if (EFI_ERROR (Status)) {
          goto ExitGbEWa;
        }

        MmioWrite32 ((GbEBar + R_PCH_MBARA_GBECSR3), (0x4320000 | (RAH0 & B_PCH_MBARA_GBECSR8_RAH)));
        ///
        /// Step 19
        /// Verify MBARA + Offset 20h[28] = 1b, set MBARA + Offset 20h = 0x4310013
        ///
        Status = CheckReadyFlag (GbEBar);
        if (EFI_ERROR (Status)) {
          goto ExitGbEWa;
        }

        MmioWrite32 ((GbEBar + R_PCH_MBARA_GBECSR3), 0x4310013);
        ///
        /// Step 20
        /// Verify MBARA + Offset 20h[28] = 1b, set MBARA + Offset 20h = 0x4328000
        ///
        Status = CheckReadyFlag (GbEBar);
        if (EFI_ERROR (Status)) {
          goto ExitGbEWa;
        }

        MmioWrite32 ((GbEBar + R_PCH_MBARA_GBECSR3), 0x4328000);
        ///
        /// Step 21
        /// Verify MBARA + Offset 20h[28] = 1b, set MBARA + Offset 20h = 0x4310001
        ///
        Status = CheckReadyFlag (GbEBar);
        if (EFI_ERROR (Status)) {
          goto ExitGbEWa;
        }

        MmioWrite32 ((GbEBar + R_PCH_MBARA_GBECSR3), 0x4310001);
        ///
        /// Step 22
        /// Verify MBARA + Offset 20h[28] = 1b, set MBARA + Offset 20h = 0x8320000
        ///
        Status = CheckReadyFlag (GbEBar);
        if (EFI_ERROR (Status)) {
          goto ExitGbEWa;
        }

        MmioWrite32 ((GbEBar + R_PCH_MBARA_GBECSR3), 0x8320000);
        ///
        /// Step 23
        /// Verify MBARA + Offset 20h[28] = 1b, TEMP[15:0] = MBARA + Offset 20h [15:0]
        ///
        Status = CheckReadyFlag (GbEBar);
        if (EFI_ERROR (Status)) {
          goto ExitGbEWa;
        }

        Buffer = MmioRead32 (GbEBar + R_PCH_MBARA_GBECSR3) & B_PCH_MBARA_GBECSR3_DATA;
        ///
        /// Step 24
        /// Set MBARA + Offset 20h = 0x4320000 or TEMP[15:0] or 0x0001
        ///
        MmioWrite32 ((GbEBar + R_PCH_MBARA_GBECSR3), 0x4320000 | Buffer | 0x0001);
        ///
        /// Step 25
        /// Verify MBARA + Offset 20h[28] = 1b, set MBARA + Offset 20h = 0x43f6460
        ///
        Status = CheckReadyFlag (GbEBar);
        if (EFI_ERROR (Status)) {
          goto ExitGbEWa;
        }

        MmioWrite32 ((GbEBar + R_PCH_MBARA_GBECSR3), 0x43f6460);
        ///
        /// Step 26
        /// Wait 4 mSec
        ///
        CountTime((4 * 1000), PM_BASE_ADDRESS);
        ///
        /// Step 27
        /// Verify MBARA + Offset 20h[28] = 1b, set MBARA + Offset 20h = 0x4310042
        ///
        Status = CheckReadyFlag (GbEBar);
        if (EFI_ERROR (Status)) {
          goto ExitGbEWa;
        }

        MmioWrite32 ((GbEBar + R_PCH_MBARA_GBECSR3), 0x4310042);
        ///
        /// Step 28
        /// Verify MBARA + Offset 20h[28] = 1b.
        ///
        Status = CheckReadyFlag (GbEBar);
        if (EFI_ERROR (Status)) {
          goto ExitGbEWa;
        }

        MmioWrite32 ((GbEBar + R_PCH_MBARA_GBECSR3), 0x43F6020);

        ///
        /// Step 29
        /// Wait 4 mSec
        ///
        CountTime((4 * 1000), PM_BASE_ADDRESS);

        ///
        /// Step 30
        /// Verify MBARA + Offset 20h[28] = 1b, set MBARA + Offset 20h = 0x8310000
        ///
        Status = CheckReadyFlag (GbEBar);
        if (EFI_ERROR (Status)) {
          goto ExitGbEWa;
        }

        MmioWrite32 ((GbEBar + R_PCH_MBARA_GBECSR3), 0x8310000);
        ///
        /// Step 31
        /// Verify MBARA + Offset 20h[28] = 1b, TEMP[15:0] = MBARA + 20[15:0]
        ///
        Status = CheckReadyFlag (GbEBar);
        if (EFI_ERROR (Status)) {
          goto ExitGbEWa;
        }

        Buffer = MmioRead32 (GbEBar + R_PCH_MBARA_GBECSR3) & 0x0000FFFF;

        ///
        /// Step 32
        /// Verify MBARA + 20h[28] = 1b, set MBARA + 20h = 4310000h or with the TEMP[15:0] or with 10h
        ///
        Status = CheckReadyFlag (GbEBar);
        if (EFI_ERROR (Status)) {
          goto ExitGbEWa;
        }

ExitGbEWa:

        MmioWrite32 ((GbEBar + R_PCH_MBARA_GBECSR3), 0x4310000 | Buffer | 0x10);
        ///
        /// Step 33
        /// Verify MBARA + Offset 20h[28] = 1b
        ///
        Status = CheckReadyFlag (GbEBar);

        ///
        /// Step 34
        /// Clear MBARA + Offset F00h [5] = 0b (read modify write)
        ///
        MmioWrite32 ((GbEBar + R_PCH_MBARA_GBECSR5), (ExtCnfCtrl & (UINT32) (~BIT5)));

      }
    }
  }
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure: SBPwrBtnHandler
//
// Description: If the power button is pressed, then this function is called.
//
// Input: DispatchHandle  - Handle of dispatch function, for when interfacing
//                          with the parent SMM driver, will be the address of linked
//                          list link in the call back record.
//        DispatchContext - Pointer to the dispatch function's context.
//
// Output: VOID
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
#if defined(PI_SPECIFICATION_VERSION)&&(PI_SPECIFICATION_VERSION>=0x0001000A)&&(CORE_COMBINED_VERSION >= 0x4028B)
EFI_STATUS SBPwrBtnHandler (
    IN EFI_HANDLE       DispatchHandle,
    IN CONST VOID       *DispatchContext OPTIONAL,
    IN OUT VOID         *CommBuffer OPTIONAL,
    IN OUT UINTN        *CommBufferSize OPTIONAL )
#else
VOID SBPwrBtnHandler(
    IN EFI_HANDLE                               DispatchHandle,
    IN AMI_SMM_POWER_BUTTON_DISPATCH_CONTEXT    *DispatchContext)
#endif
{

// Usage sample code shows that user how to decide NMI_EN bit is diabled or enabled in SMI.
//####    EFI_CMOS_ACCESS_INTERFACE   *CmosInterface;
//####    EFI_STATUS  Status;
//####
//####    LOCATE_CMOS_ACCESS_SMM_PROTOCOL(Status, CmosInterface);
//####    if( !EFI_ERROR(Status) ) {
//####       // Example1:Disable NMI
//####       CmosInterface->Write( CmosInterface,
//####                             SB_SSP_NMI_CONTROL_BITS,
//####                             DISABLE_NMI_BEFORE_SMI_EXIT );
//####       // Example2:Enable NMI
//####//       CmosInterface->Write( CmosInterface,
//####//                             SB_SSP_NMI_CONTROL_BITS,
//####//                             ENABLE_NMI_BEFORE_SMI_EXIT );
//####    }

    // Program AfterG3 bit depend the setup question.
    if (gIsLastState) SET_PCI8_SB(SB_REG_GEN_PMCON_3, 1); // 0xA4

    if (gPchWakeOnLan) GbES02SxWorkaround();

    return SMM_CHILD_DISPATCH_SUCCESS;
}

#if SB_PCIE_ERROR_LOG_SUPPORT
//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure: ElogGenerateNmiNow
//
// Description: Generate NmiNow.
//
// Input: None
//
// Output: None
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID ElogGenerateNmiNow (VOID)
{
  UINT16          PmBase;
  UINT8           SaveNmi2SmiEn;
  UINT8           SavePort70;

  //
  // Get the PM Base Address
  //
  PmBase = READ_PCI16_SB (SB_REG_PMBASE) & 0xFF80;

  // Read the NMI2SMI_EN bit, save it for future restore
  SaveNmi2SmiEn = READ_IO8(PmBase + TCO1_CNT_OFFSET + 1);

  // Set the NMI2SMI_EN bit to 0
  RESET_IO8(PmBase + TCO1_CNT_OFFSET + 1, BIT01);

  SavePort70 = ReadPort70h();							//Improve alternate access mode 

  // Enable NMI_EN
  WRITE_IO8(CMOS_ADDR_PORT, (SavePort70 & ~BIT07));		//Improve alternate access mode 

  // Set NMI_NOW = 1
  SET_IO8(PmBase + TCO1_CNT_OFFSET + 1, BIT00);

  // Clear NMI_NOW = 0 by writing 1 to NMI_NOW bit
  RESET_IO8(PmBase + TCO1_CNT_OFFSET + 1, BIT00);

  // Restore NMI2SMI_EN
  WRITE_IO8(PmBase + TCO1_CNT_OFFSET + 1, SaveNmi2SmiEn);

  // Clear the DMISERR_STS bit, bit 12
  WRITE_IO16(PmBase + TCO1_STS_OFFSET, BIT12);

  // Clear the NMI2SMI_STS bit if set
  if ((READ_IO16(PmBase + TCO1_STS_OFFSET)) & 0x0001) {
    // check port 0x61
    if (READ_IO8(NMI_SC_PORT) & 0x80) {
        SET_IO8(NMI_SC_PORT, BIT02);
        RESET_IO8(NMI_SC_PORT, BIT02);
    }
  }

  // Restore NMI_EN
  WRITE_IO8(CMOS_ADDR_PORT, SavePort70);

  return;
  
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure: SBErrLogHandler
//
// Description: South bridge error logging handler.
//
// Input: DispatchHandle  - Handle of dispatch function, for when interfacing
//                          with the parent SMM driver, will be the address of linked
//                          list link in the call back record.
//        DispatchContext - Pointer to the dispatch function's context.
//
// Output: None
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID SBErrLogHandler (
    IN EFI_HANDLE                       DispatchHandle,
    IN EFI_SMM_ICHN_DISPATCH_CONTEXT    *DispatchContext
)
{
  EFI_STATUS Status = EFI_SUCCESS;
  SB_PCIE_ERROR_LOG_DISPATCH_LINK       *Link;
  SB_PCIE_ERR ErrorInfo;
  UINT8      i;
  UINT8      CapPtr;
  UINT16     PciStatus;
  UINT16     PcieStatus;
  UINT16     DeviceStatus;
  UINT32     DevBaseAddr;

  if (READ_IO8(NMI_SC_PORT) & BIT7)                   // SERR#_NMI_STS?
  {
    // Clear SERR#_NMI_STS & NMI2SMI_STS by set Port 61h[2] = 1 then set it to 0.
    SET_IO8(NMI_SC_PORT, BIT02);
    RESET_IO8(NMI_SC_PORT, BIT02);

    for (i = 0; SBPcieBridge[i] != 0xFFFFFFFF; i++)
    {
      DevBaseAddr = SBPcieBridge[i];
      if (READ_MEM32(DevBaseAddr) == 0xFFFFFFFF)
        continue;

      PciStatus = READ_MEM16(DevBaseAddr + 0x06);
      PcieStatus = READ_MEM16(DevBaseAddr + 0x1E);

      CapPtr = SbFindCapPtr(DevBaseAddr, 0x10);
      if (CapPtr != 0)
        DeviceStatus = READ_MEM16(DevBaseAddr + CapPtr + 0x0A);

      if ((PciStatus & (BIT8 | BIT15)) || (PcieStatus & (BIT8 | BIT15)))
        ErrorInfo.ParityError = TRUE;
      else
        ErrorInfo.ParityError = FALSE;

      if ((PciStatus & BIT14) || (PcieStatus & BIT14))
        ErrorInfo.SystemError = TRUE;
      else
        ErrorInfo.SystemError = FALSE;

      if ((ErrorInfo.ParityError) || (ErrorInfo.SystemError)) {
        ErrorInfo.PcieAddress = DevBaseAddr;
        ErrorInfo.Bus = (DevBaseAddr >> 20) & ((UINT8)((PCIEX_LENGTH >> 20) - 1));
        ErrorInfo.Dev = (DevBaseAddr >> 15) & 0x1F;
        ErrorInfo.Fun = (DevBaseAddr >> 12) & 0x07;
        ErrorInfo.VendorId   = READ_MEM16(DevBaseAddr + 0x00);
        ErrorInfo.DeviceId   = READ_MEM16(DevBaseAddr + 0x02);
        ErrorInfo.PciCommand = READ_MEM16(DevBaseAddr + 0x04);
        ErrorInfo.PciCCode   = READ_MEM16(DevBaseAddr + 0x0A);
        ErrorInfo.BridgeControl = READ_MEM16(DevBaseAddr + 0x3E);
        ErrorInfo.Version    = READ_MEM8(DevBaseAddr + CapPtr + 0x02) & 0x0F;
        ErrorInfo.PortType   = (UINT32)((READ_MEM8(DevBaseAddr + CapPtr + 0x02) & 0xF0) >> 4);

        if (CapPtr != 0) {
          ErrorInfo.Correctable = (DeviceStatus & BIT0)? TRUE : FALSE;
          ErrorInfo.NonFatal = (DeviceStatus & BIT1)? TRUE : FALSE;
          ErrorInfo.Fatal = (DeviceStatus & BIT2)? TRUE : FALSE;
        }

        // Clear Error status
        WRITE_MEM16(DevBaseAddr + 0x06, PciStatus);
        WRITE_MEM16(DevBaseAddr + 0x1E, PcieStatus);

        if (CapPtr != 0)
          // Clear Error Status
          WRITE_MEM16(DevBaseAddr + CapPtr + 0x0A, DeviceStatus);

//####        if (!ErrorInfo.Correctable)
//####          ElogGenerateNmiNow();

        for(Link = gSbPcieErrorLogDispatchHead; Link; Link = Link->Link) {
          Link->Function(Link, ErrorInfo);
        }
      } // if ((ErrorInfo.ParityError) || (ErrorInfo.SystemError))
    }
  }
}


//----------------------------------------------------------------------------
VOID InitSbSmiLogic(VOID)
{
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure: InitSbSmiLogicHandler
//
// Description: Initialize SB SMI Logic Handler.
//              This handler should be performed in ready to boot
//              and S3 rerume.
//
// Input: DispatchHandle  - Handle of dispatch function, for when interfacing
//                          with the parent SMM driver, will be the address of linked
//                          list link in the call back record.
//        DispatchContext - Pointer to the dispatch function's context.
//
// Output: None
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
#if defined(PI_SPECIFICATION_VERSION)&&(PI_SPECIFICATION_VERSION>=0x0001000A)&&(CORE_COMBINED_VERSION >= 0x4028B)
EFI_STATUS InitSbSmiLogicHandler (
    IN EFI_HANDLE       DispatchHandle,
    IN CONST VOID       *DispatchContext OPTIONAL,
    IN OUT VOID         *CommBuffer OPTIONAL,
    IN OUT UINTN        *CommBufferSize OPTIONAL )
#else
VOID InitSbSmiLogicHandler (
    IN EFI_HANDLE                   DispatchHandle,
    IN AMI_SMM_SW_DISPATCH_CONTEXT  *DispatchContext)
#endif
{
  UINT32        PmBase;
  UINT32        Buffer32;

  PmBase = READ_PCI16_SB (SB_REG_PMBASE) & 0xFF80;

  //
  //Every SERR (System Erors) will generate NMI. So route NMI as a SMI to handle Errors
  //Steps to route NMI as a SMI
  //Enable NMI2SMI_EN bit in TCO1 Control Register
  //UnMask NMI Enable bit in NMI Enable (and Real Time Clock Index) Register
  //

  // Set NMI2SMI_EN = '1b', TCO_BASE + 08h[9]
  SET_IO16_PM(TCO1_CNT_OFFSET, BIT09);

  // Enable NMI by set Port 70h[7] = '0b'
  SwitchAlternateAccessMode (TRUE);				//Improve alternate access mode
  RESET_IO8(CMOS_ADDR_PORT, BIT07);
  SwitchAlternateAccessMode (FALSE);			//Improve alternate access mode

  //
  //Clear all Spurious Sources of the SMI.
  //  
  Buffer32 = READ_IO32_PM(SMI_STS_OFFSET);
  WRITE_IO32_PM(SMI_STS_OFFSET, Buffer32);

  Buffer32 = READ_IO32_PM(TCO1_STS_OFFSET);
  WRITE_IO32_PM(TCO1_STS_OFFSET, Buffer32);

  SET_IO8(NMI_SC_PORT, BIT02);
  RESET_IO8(NMI_SC_PORT, BIT02);

  return SMM_CHILD_DISPATCH_SUCCESS;
}

EFI_SB_PCIE_ERROR_LOG_DISPATCH_PROTOCOL gEfiSbPcieErrorLogDispatchProtocol = \
                                   {SbPcieErrorLogRegister, SbPcieErrorLogUnregister};
#endif

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:   GetSbSmiContext
//
// Description: This is a template SB SMI GetContext for Porting.
//
// Input:       None
//
// Output:      BOOLEAN
//
// Notes:       Here is the control flow of this function:
//              1. Check if NB Smi source.
//              2. If yes, return TRUE.
//              3. If not, return FALSE.
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

BOOLEAN GetSbSmiContext (VOID)
{
        return FALSE;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:   SbSmiHandler
//
// Description: This is a template SB SMI Handler for Porting.
//
// Input:       None
//
// Output:      None
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

VOID SbSmiHandler (VOID)
{

}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:   SbIchnExGpioUnlockSmiHandler
//
// Description: If the GPIO Lockdown Enable(GLE, B0:D31:F0 R4Ch[0]) bit is
//              changed from 1 to 0, then this function is called.
//
// Input:       DispatchHandle  - EFI Handle
//              DispatchContext - Pointer to the EFI_SMM_ICHN_DISPATCH_EX_CONTEXT
//
// Output:      None
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID SbIchnExGpioUnlockSmiHandler (
    IN EFI_HANDLE                        DispatchHandle,
    IN EFI_SMM_ICHN_DISPATCH_EX_CONTEXT  *DispatchContext )
{
    // Set GPIO Lockdown Enable(GLE) bit.
    SET_PCI8_SB(SB_REG_GC, BIT00);
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:   PchBiosWpCallback
//
// Description: This hardware SMI handler will be run every time the BIOS Write Enable bit is set.
//
// Input:       DispatchHandle      Not used
//              DispatchContext     Not used
//
// Output:      None
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
static
VOID
PchBiosWpCallback (
  IN  EFI_HANDLE                              DispatchHandle,
  IN  EFI_SMM_ICHN_DISPATCH_CONTEXT           *DispatchContext
  )
{
#if CHECK_BS_VARIABLE
  // Do not need to check the BS attribute variable
  // if NvramSmi is enabled.
  EFI_STATUS          Status; 
  SB_PLATFORM_DATA    SbPlatformData;
  EFI_GUID            SetupGuid = SETUP_GUID;
  UINTN               VarSize;

  VarSize = sizeof(SB_PLATFORM_DATA);
  Status = pRS->GetVariable(
                  L"SbPlatformData",
                  &SetupGuid,
                  NULL,
                  &VarSize,
                  &SbPlatformData );
  if(!EFI_ERROR(Status) || (Status == EFI_ACCESS_DENIED)) return;
#endif
  //
  // Disable BIOSWE bit to protect BIOS
  //
  RESET_PCI8_SB(R_PCH_LPC_BIOS_CNTL, B_PCH_LPC_BIOS_CNTL_BIOSWE);

}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:   PchBiosLockIoTrapCallback
//
// Description: Register an IchnBiosWp callback function to handle TCO BIOSWR SMI
//              SMM_BWP and BLE bits will be set here
//
// Input:       DispatchHandle      Not used
//              DispatchContext     Not used
//
// Output:      None
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID PchBiosLockIoTrapCallback (
    IN  EFI_HANDLE                                  DispatchHandle,
    IN  EFI_SMM_IO_TRAP_DISPATCH_CALLBACK_CONTEXT   *DispatchContext )
{
  EFI_STATUS                      Status;
  EFI_SMM_ICHN_DISPATCH_CONTEXT   IchnContext;
  EFI_HANDLE                      IchnHandle = NULL;

  if (READ_PCI8_SB(R_PCH_LPC_BIOS_CNTL) & B_PCH_LPC_BIOS_CNTL_BLE) {
    return;
  }

  if ((DispatchContext->Type != WriteTrap) || (DispatchContext->WriteData != PCH_BWP_SIGNATURE)) {
    return;
  }

  if (gIchnDispatch == NULL) {
    return;
  }

#if defined NvramSmiSupport && NvramSmiSupport
#if SMM_BIOS_WRITE_PROTECT_DISABLE
  //
  // Set SMM_BWP bit before registering IchnBiosWp
  //
  SET_PCI8_SB(R_PCH_LPC_BIOS_CNTL, B_PCH_LPC_BIOS_CNTL_SMM_BWP);
#endif
#endif
  //
  // Register an IchnBiosWp callback function to handle TCO BIOSWR SMI
  //
  IchnContext.Type = IchnBiosWp;
  Status = gIchnDispatch->Register (
                          gIchnDispatch,
                          PchBiosWpCallback,
                          &IchnContext,
                          &IchnHandle
                          );
  ASSERT_EFI_ERROR (Status);

  return;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:   SbChildDispatcher
//
// Description: South Bridge SMM Child Dispatcher Handler.
//
// Input:       SmmImageHandle - 
//              *CommunicationBuffer - OPTIONAL
//              *SourceSize - OPTIONAL
//
// Output:      EFI_STATUS
//
// Modified:
//
// Referrals:   EfiSmmSwDispatch EfiSmmSxDispatch 
//
// Notes:       Here is the control flow of this function:
//              1. Read SMI source status registers.
//              2. If source, call handler.
//              3. Repeat #2 for all sources registered.
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS SbChildDispatcher (
#if defined(PI_SPECIFICATION_VERSION)&&(PI_SPECIFICATION_VERSION>=0x0001000A)&&(CORE_COMBINED_VERSION >= 0x4028B)
    IN EFI_HANDLE       DispatchHandle,
    IN CONST VOID       *DispatchContext OPTIONAL,
    IN OUT VOID         *CommBuffer OPTIONAL,
    IN OUT UINTN        *CommBufferSize OPTIONAL )
#else
    IN EFI_HANDLE       SmmImageHandle,
    IN OUT VOID         *CommunicationBuffer OPTIONAL,
    IN OUT UINTN        *SourceSize OPTIONAL )
#endif
{
    if (GetSbSmiContext()) SbSmiHandler();

    return EFI_HANDLER_SUCCESS;
}

//<AMI_PHDR_START>                                      //EIP104199 >>
//----------------------------------------------------------------------------
//
// Procedure:   DummyTcoSmiCallback
//
// Description: 
//
// Input:       
//
// Output:      None
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
static VOID DummyTcoSmiCallback (
  IN  EFI_HANDLE                              DispatchHandle,
  IN  EFI_SMM_ICHN_DISPATCH_CONTEXT           *DispatchContext
  )
{
  // Dummy routine for clear any unexpected TCO SMIs status.
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:   RegisterAllTcoSmiDummyHandler
//
// Description: 
//
// Input:       None
//
// Output:      None
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID RegisterAllTcoSmiDummyHandler ( VOID )
{
  EFI_STATUS                     Status;
	EFI_HANDLE                     IchnHandle[12];
	EFI_SMM_ICHN_DISPATCH_CONTEXT  IchnContext[12];
	UINT8                          Index=0;

	IchnContext[0].Type = IchnMch;
	IchnContext[1].Type = IchnPme;
	IchnContext[2].Type = IchnRtcAlarm;
	IchnContext[3].Type = IchnRingIndicate;
	IchnContext[4].Type = IchnAc97Wake;
	IchnContext[5].Type = IchnSerialIrq;
	IchnContext[6].Type = IchnY2KRollover;
	IchnContext[7].Type = IchnTcoTimeout;
	IchnContext[8].Type = IchnOsTco;
	IchnContext[9].Type = IchnNmi;
	IchnContext[10].Type = IchnIntruderDetect;
	IchnContext[11].Type = 	IchnBiosWp;

	for(Index = 0; Index<12; Index++){
	  Status = gIchnDispatch->Register (
	                          gIchnDispatch,
	                          DummyTcoSmiCallback,
	                          &IchnContext[Index],
	                          &IchnHandle[Index]
	                          );
	  ASSERT_EFI_ERROR (Status);	
	}
}
                                                        //EIP104199 <<
//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:   InSmmFunction
//
// Description: Installs North Bridge SMM Child Dispatcher Handler.
//
// Input:       ImageHandle  - Image handle
//              *SystemTable - Pointer to the system table
//
// Output:      EFI_STATUS
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS InSmmFunction (
    IN EFI_HANDLE           ImageHandle,
    IN EFI_SYSTEM_TABLE     *SystemTable )
{
    AMI_SMM_POWER_BUTTON_DISPATCH_PROTOCOL  *PowerButton;
#if defined(PI_SPECIFICATION_VERSION)&&(PI_SPECIFICATION_VERSION>=0x0001000A)&&(CORE_COMBINED_VERSION >= 0x4028B)
    AMI_SMM_POWER_BUTTON_DISPATCH_CONTEXT DispatchContext = {EfiPowerButtonEntry};
    EFI_HANDLE                        RootHandle;
#else
    AMI_SMM_POWER_BUTTON_DISPATCH_CONTEXT DispatchContext = {PowerButtonEntry};
    EFI_SMM_BASE_PROTOCOL             *SmmBaseProtocol;
#endif
    EFI_HANDLE                        Handle = NULL;
    EFI_STATUS                        Status;
    AMI_S3_SAVE_PROTOCOL             *BootScriptSave;

    EFI_HANDLE                        DummyHandle = NULL;
#if SB_PCIE_ERROR_LOG_SUPPORT
    EFI_SM_ELOG_PROTOCOL              *GenericElogProtocol = NULL;
    AMI_SMM_SW_DISPATCH_CONTEXT       SbErrorLogS3PatchContext = {SW_SMI_SB_EL_S3};
    EFI_SMM_ICHN_DISPATCH_CONTEXT     IchnContext;
#endif
    EFI_SMM_ICHN_DISPATCH_EX_CONTEXT  IchnExContext;
    EFI_SMM_ICHN_DISPATCH_EX_PROTOCOL *pIchnExDispatch;

    SB_SETUP_DATA                     *SbSetupData = NULL;
    UINTN                             VariableSize = sizeof(SB_SETUP_DATA);
    DXE_PCH_PLATFORM_POLICY_PROTOCOL  *PchPlatformPolicy;
    EFI_HANDLE                        SwHandle = NULL;
    AMI_SMM_SW_DISPATCH_PROTOCOL      *SwDispatch;
//    AMI_SMM_SW_DISPATCH_CONTEXT       SwContext;
#if defined(PI_SPECIFICATION_VERSION)&&(PI_SPECIFICATION_VERSION>=0x0001000A)&&(CORE_COMBINED_VERSION >= 0x4028B)
    EFI_SMM_SYSTEM_TABLE2   *pSmst2;
#endif
    EFI_SMM_IO_TRAP_DISPATCH_PROTOCOL         *PchIoTrap;
    EFI_HANDLE                                PchIoTrapHandle;
    EFI_SMM_IO_TRAP_DISPATCH_REGISTER_CONTEXT PchIoTrapContext;
    //
    // Locate PCH Platform Policy protocol
    //
    Status = pBS->LocateProtocol ( &gDxePchPlatformPolicyProtocolGuid, \
                                   NULL, \
                                   &PchPlatformPolicy);
    if (EFI_ERROR (Status)) return Status;

#if defined(PI_SPECIFICATION_VERSION)&&(PI_SPECIFICATION_VERSION>=0x0001000A)&&(CORE_COMBINED_VERSION >= 0x4028B)
    Status = InitAmiSmmLib( ImageHandle, SystemTable );

    // We are in SMM, retrieve the pointer to SMM System Table
    Status = gSmmBase2->GetSmstLocation( gSmmBase2, &pSmst2);
    if (EFI_ERROR(Status)) return EFI_UNSUPPORTED;

#else
    Status = pBS->LocateProtocol( &gEfiSmmBaseProtocolGuid, \
                                  NULL, \
                                  &SmmBaseProtocol );
#endif
    if (EFI_ERROR(Status)) return Status;


    Status = pBS->LocateProtocol( AMI_S3_SAVE_PROTOCOL_GUID, \
                                  NULL, \
                                  &BootScriptSave );

    Status = pBS->AllocatePool( EfiBootServicesData, \
                                VariableSize, \
                                &SbSetupData );

    GetSbSetupData( pRS, SbSetupData, FALSE );

    gPchWakeOnLan = (SbSetupData->PchWakeOnLan == 1) ? TRUE : FALSE;
    gIsLastState = (SbSetupData->LastState == 2) ? TRUE : FALSE;

    Status = pBS->FreePool( SbSetupData );

#if defined(PI_SPECIFICATION_VERSION)&&(PI_SPECIFICATION_VERSION>=0x0001000A)&&(CORE_COMBINED_VERSION >= 0x4028B)
    Status  = pSmst2->SmmLocateProtocol( &gEfiSmmPowerButtonDispatch2ProtocolGuid, \
                                        NULL, \
                                        &PowerButton );
#else
    Status = pBS->LocateProtocol(
        &gEfiSmmPowerButtonDispatchProtocolGuid,
        NULL,
        &PowerButton
    );
#endif

    if (EFI_ERROR(Status)) return Status;

    Status = PowerButton->Register( PowerButton,
                                    SBPwrBtnHandler,
                                    &DispatchContext,
                                    &Handle );

#if defined(PI_SPECIFICATION_VERSION)&&(PI_SPECIFICATION_VERSION>=0x0001000A)&&(CORE_COMBINED_VERSION >= 0x4028B)
    Status  = pSmst2->SmmLocateProtocol( &gEfiSmmSwDispatch2ProtocolGuid, \
                                          NULL, \
                                          &SwDispatch );
#else
    Status = pBS->LocateProtocol( &gSwDispatchProtocolGuid, \
                                  NULL, \
                                  &SwDispatch );
#endif

    if (EFI_ERROR(Status)) return Status;

    Status = pBS->LocateProtocol ( &gIchnDispatchProtocolGuid, \
                                   NULL, \
                                   &gIchnDispatch );
    if (EFI_ERROR(Status)) return Status;

#if REGISTER_ALL_TCO_SMI_IN_DUMMY     //EIP104199 >>
//Please define this token if need support this function.
    RegisterAllTcoSmiDummyHandler();
#endif                                //EIP104199 <<

#if SB_PCIE_ERROR_LOG_SUPPORT
    Status = pBS->LocateProtocol( &gElogProtocolGuid,
                                  NULL,
                                  &GenericElogProtocol );
    if (!EFI_ERROR (Status)) {

      Status = SwDispatch->Register( SwDispatch, \
                                     InitSbSmiLogicHandler, \
                                     &SbErrorLogS3PatchContext, \
                                     &Handle );
      if (EFI_ERROR(Status)) return Status;

      ASSERT_EFI_ERROR (Status);

      IchnContext.Type = IchnNmi;
      Status = gIchnDispatch->Register( gIchnDispatch, \
                                        SBErrLogHandler, \
                                        &IchnContext, \
                                        &Handle );
      ASSERT_EFI_ERROR (Status);

      Status = pBS->InstallProtocolInterface( &DummyHandle, \
                                              &gSbPcieErrorLogDispatchProtocolGuid, \
                                              EFI_NATIVE_INTERFACE, \
                                              &gEfiSbPcieErrorLogDispatchProtocol );
    }

#endif

    if (PchPlatformPolicy->LockDownConfig->GpioLockDown == PCH_DEVICE_ENABLE) {
      Status = pBS->LocateProtocol( &gEfiSmmIchnExDispatchProtocolGuid, \
                                    NULL, \
                                    &pIchnExDispatch );
      if (!EFI_ERROR(Status)) {
          IchnExContext.Type = IchnExGpioUnlock;
          Status  = pIchnExDispatch->Register( pIchnExDispatch, \
                                               SbIchnExGpioUnlockSmiHandler, \
                                               &IchnExContext, \
                                               &Handle );
      }
    }

    if (PchPlatformPolicy->LockDownConfig->BiosLock == PCH_DEVICE_ENABLE) {
      ///
      /// Locate the PCH IO TRAP Dispatch protocol
      ///
      PchIoTrapHandle = NULL;
      Status = pBS->LocateProtocol (&gEfiSmmIoTrapDispatchProtocolGuid, NULL, &PchIoTrap);
      ASSERT_EFI_ERROR (Status);

      if (!EFI_ERROR(Status)) {
        ///
        /// Register BIOS Lock IO Trap SMI handler
        ///
        PchIoTrapContext.Type         = WriteTrap;
        PchIoTrapContext.Length       = 4;
        PchIoTrapContext.Address      = PchPlatformPolicy->LockDownConfig->PchBiosLockIoTrapAddress;
        PchIoTrapContext.Context      = NULL;
        PchIoTrapContext.MergeDisable = FALSE;
        Status = PchIoTrap->Register (
                              PchIoTrap,
                              PchBiosLockIoTrapCallback,
                              &PchIoTrapContext,
                              &PchIoTrapHandle );
        if (EFI_ERROR(Status)) return Status;

        if ((PchPlatformPolicy->LockDownConfig->PchBiosLockIoTrapAddress == 0) &&
            (PchIoTrapContext.Address == 0)) {
          TRACE((TRACE_ALWAYS, "Invalid PchIoTrapContext.Address!!!\n"));
        } else {
          if ((PchPlatformPolicy->LockDownConfig->PchBiosLockIoTrapAddress != 0) &&
              (PchPlatformPolicy->LockDownConfig->PchBiosLockIoTrapAddress != PchIoTrapContext.Address)) {
            TRACE((TRACE_ALWAYS, "Invalid PchIoTrapContext.Address!!!\n"));
          } else {
            PchPlatformPolicy->LockDownConfig->PchBiosLockIoTrapAddress = PchIoTrapContext.Address;
          }
        }
      }

    }

    Status = pBS->InstallProtocolInterface( &DummyHandle, \
                                            &gAmiSbSmiProtocolGuid, \
                                            EFI_NATIVE_INTERFACE, \
                                            NULL );

    // Register Callbacks
#if defined(PI_SPECIFICATION_VERSION)&&(PI_SPECIFICATION_VERSION>=0x0001000A)&&(CORE_COMBINED_VERSION >= 0x4028B)
    Status  = pSmst2->SmiHandlerRegister( SbChildDispatcher, \
                                         NULL, \
                                         &RootHandle );
#else
    Status  = SmmBaseProtocol->RegisterCallback( SmmBaseProtocol, \
                                       ImageHandle, \
                                       SbChildDispatcher, \
                                       FALSE, \
                                       FALSE );
#endif

    // Update SMM Runtime Service Table
    pRS->ResetSystem = gSmmResetSystem;

    return Status;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure: NotInSmmFunction
//
// Description: This function is called from outside of SMM during SMM registration.
//
// Input: IN EFI_HANDLE ImageHandle
//        IN EFI_SYSTEM_TABLE *SystemTable
//
// Output: EFI_STATUS
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS NotInSmmFunction( IN EFI_HANDLE ImageHandle, IN EFI_SYSTEM_TABLE *SystemTable)
{
    UINT16 Value = 0;

#if defined PowerButton_SUPPORT && PowerButton_SUPPORT == 0
    //Clear All PM  Statuses
    Value = IoRead16(PM_BASE_ADDRESS);
    IoWrite16(PM_BASE_ADDRESS,Value);

    //Enable PowerButton and Global Enable
    IoWrite16(PM_BASE_ADDRESS + 0x02, BIT05 + BIT08);
#endif

    return EFI_SUCCESS;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:   InitializeSBSmm
//
// Description: Installs North Bridge SMM Child Dispatcher Handler.
//
// Input:       ImageHandle  - Image handle
//              *SystemTable - Pointer to the system table
//
// Output:      EFI_STATUS
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS InitializeSBSmm (
    IN EFI_HANDLE           ImageHandle,
    IN EFI_SYSTEM_TABLE     *SystemTable )
{
    EFI_STATUS Status = EFI_SUCCESS;

    InitAmiLib(ImageHandle, SystemTable);

    gSmmResetSystem = pRS->ResetSystem;

#if defined(PI_SPECIFICATION_VERSION)&&(PI_SPECIFICATION_VERSION>=0x0001000A)&&(CORE_COMBINED_VERSION >= 0x4028B)
    Status = SystemTable->BootServices->LocateProtocol( \
                                                &gEfiSmmBase2ProtocolGuid, \
                                                NULL, \
                                                &gSmmBase2 );
    ASSERT_EFI_ERROR(Status);
#endif

    return InitSmmHandler(ImageHandle, SystemTable, InSmmFunction, NotInSmmFunction);
}

//*************************************************************************
//*************************************************************************
//**                                                                     **
//**        (C)Copyright 1985-2013, American Megatrends, Inc.            **
//**                                                                     **
//**                       All Rights Reserved.                          **
//**                                                                     **
//**      5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093           **
//**                                                                     **
//**                       Phone: (770)-246-8600                         **
//**                                                                     **
//*************************************************************************
//*************************************************************************
