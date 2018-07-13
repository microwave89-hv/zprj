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
// $Header: /Alaska/BIN/Chipset/Intel/SouthBridge/LynxPoint/Intel Pch SB Chipset/SBGeneric.c 27    1/29/15 4:14a Mirayang $
//
// $Revision: 27 $
//
// $Date: 1/29/15 4:14a $
//*************************************************************************
// Revision History
// ----------------
// $Log: /Alaska/BIN/Chipset/Intel/SouthBridge/LynxPoint/Intel Pch SB Chipset/SBGeneric.c $
// 
// 27    1/29/15 4:14a Mirayang
// [TAG]  		EIP200269 
// [Category]  	New Feature
// [Description]  	For add FlashSmi : Label 4.6.5.5_FlashSmi_00
// ($/Alaska/SOURCE/Modules/FlashSmi)
// 
// 26    5/16/14 6:16a Barretlin
// [TAG]  		EIP167087
// [Category]  	Improvement
// [Description]  	BIOS security improvement on Haswell CRB project
// [Files]  		SBGeneric.c SBDxe.c SBCspLib.h Sb.sdl Sb.sd
// 
// 25    1/24/14 2:49a Barretlin
// [TAG]  		EIP136638
// [Category]  	Improvement
// [Description]  	fix programming error
// [Files]  		SBGeneric.c PchResetCommon.c
// 
// 24    12/30/13 6:01a Barretlin
// [TAG]  		EIP144559
// [Category]  	Improvement
// [Description]  	S3 can't resume via USB KB & MS under usb3.0 port in
// special case
// [Files]  		SBSMI.c SBSMI.h SBGeneric.c
// 
// 23    11/19/13 7:32a Barretlin
// [TAG]  		EIP141917
// [Category]  	New Feature
// [Description]  	Support SetTimer() with HPET Timer on Lynx Point
// [Files]  		SB.sdl SBGeneric.c SBDxe.c SbHpet.h sbProtocal.cif
// SamrtTimer.sdl
// 
// 22    4/29/13 1:58a Scottyang
// [TAG]  		None
// [Category]  	Improvement
// [Description]  	THe NMI read port should before index update.
// [Files]  		SBGeneric.c
// 
// 21    4/19/13 6:35a Wesleychen
// [TAG]           None
// [Category]      Improvement
// [Description]   Update GbES02SxWorkaround() and add 
//                 UsbS02SxWorkaround() for SBPwrBtnHandler().
// [Files]         SBSMI.c; SBSMI.h; SBGeneric.c; SBCspLib.h
// 
// 20    4/01/13 6:43a Scottyang
// [TAG]  		EIP119703
// [Category]  	Improvement
// [Description]  	Clear RTC before BIOS flash capsule function enter S3.
// [Files]  		SBGeneric.c
// 
// 19    3/19/13 8:33a Scottyang
// [TAG]  		None
// [Category]  	Improvement
// [Description]  	Improve alternate access mode enable/disable routine.
// [Files]  		SBGeneric.c, SBCspLib.h, SBSMI.c
// 
// 18    3/19/13 8:19a Scottyang
// [TAG]  		EIP118158
// [Category]  	Improvement
// [Description]  	Correct SBLib_CmosRead () offset.
// [Files]  		SmiHandlerPorting2.c, SBDxe.c, SBGeneric.c, SBSmm.c,
// SmiHandlerPorting.c
// 
// 17    3/12/13 7:44a Scottyang
// [TAG]  		EIP106722
// [Category]  	Improvement
// [Description]  	Clear RTC before capsule function enter S3.
// [Files]  		SBGeneric.c
// 
// 16    1/11/13 4:36a Scottyang
// [TAG]  		None
// [Category]  	Improvement
// [Description]  	Add ReadCmos() / WriteCmos() from SB template.
// [Files]  		SBGeneric.c
// 
// 15    1/11/13 12:46a Scottyang
// [TAG]         EIP81593
// [Category]    Improvement
// [Description] Added new SDL token "COLD_RESET_WITH_POWER_CYCLE".
// [Files]       SB.sdl,  SBGeneric.c,  PchResetCommon.c,
// PchResetCommonLib.sdl
// 
// 14    1/10/13 8:20a Scottyang
// [TAG]  		EIP111666
// [Category]  	New Feature
// [Description]  	Support OEM reset callback function Elink.
// [Files]  		SB.mak, SBCspLib.h, SBGeneric.c, SB.sdl, PchReset.c
// 
// 13    11/21/12 3:07a Scottyang
// 
// 11    11/19/12 3:52a Scottyang
// [TAG]  		EIP106353
// [Category]  	Bug Fix
// [Severity]  	Critical
// [Symptom]  	The system has assert error when PFAT is Disabled and Debug
// Mode is Enabled.
// [RootCause]  	Use build time PFAT flag that make some code not run whrn
// PFAT disable.
// [Solution]  	Detect PFAT flag useing MSR. 
// [Files]  		SBGeneric, SB.mak
// 
// 10    10/30/12 10:02p Scottyang
// [TAG]  		None
// [Category]  	Improvement
// [Description]  	Remove clear SMI state and Y2K roller for PFAT
// function.
// [Files]  		SBSMI.c, SBGeneric.c
// 
// 9     10/25/12 11:57p Scottyang
// [TAG]  		EIP100108
// [Category]  	Improvement
// [Description]  	Support Capsule 2.0.
// [Files]  		SBGeneric.c
// 
// 8     10/19/12 2:46a Scottyang
// [TAG]       EIP93461
// [Category]  Bug Fix
// [Severity]  Normal
// [Symptom]   System halt when AFUDOS is running with /N /ME command.
// [RootCause] An unexpected BIOSWR_STS is set, it causes BIOS stuck
//             at SMM dispatcher.
// [Solution]  Clear BIOSWR_STS if BIOS Lock Enable is not set.
// [Files]     SmiHandlerPorting2.c; SmmChildDispatch2Main.c
//             SmmChildDispatcher2.sdl; SmmChildDispatch2.h
//             SB\SBGeneric.c
// 
// 7     10/01/12 5:53a Victortu
// [TAG]           None
// [Category]      Improvement
// [Description]   Update for PFTA support.
// [Files]         SBGeneric.c
// 
// 6     9/26/12 3:54a Victortu
// [TAG]           None
// [Category]      Improvement
// [Description]   Update for PCH LP GPIO compatible.
// [Files]         SB.sdl, SB.H, AcpiModeEnable.c, AcpiModeEnable.sdl,
// SBDxe.c, SBGeneric.c, SBPEI.c, SBSMI.c, SleepSmi.c,
// SmiHandlerPorting.c, SmiHandlerPorting2.c
// 
// 5     9/12/12 5:19a Victortu
// [TAG]           None
// [Category]      Improvement
// [Description]   Remove useless HdmiVerbTable.
// [Files]         SB.sdl, SBCspLib.h, SBDxe.c, SBGeneric.c 
// 
// 4     8/24/12 6:50a Victortu
// [TAG]           None
// [Category]      Improvement
// [Description]   Remove useless SB_SHADOW_CONTROL.
// [Files]         SB.sdl, SBCspLib.h, SBGeneric.c
// 
// 3     7/02/12 10:17a Victortu
// [TAG]		None
// [Category]	Improvement
// [Description]	Updated and modified for PCH RC 0.6.0.
// [Files]		SBGeneric.c, SB.sdl, SBCspLib.h, SBDxe.c, SBPEI.c
// 
// 2     6/13/12 11:34p Victortu
// [TAG]           None
// [Category]      Improvement
// [Description]   Implement Warm Boot function for Secure Flash feature.
// [Files]         SB.H, SB.mak, SB.sdl, SBDxe.c, SBGeneric.c, SBPEI.c,
// SBSMI.c
// 
// 1     2/08/12 8:24a Yurenlai
// Intel Lynx Point/SB eChipset initially releases.
// 
//*************************************************************************
//<AMI_FHDR_START>
//
// Name:        SBGeneric.C
//
// Description: This file contains south bridge related code that is needed
//              for both PEI & DXE stage. 
//              To avoid code duplication this file is made as a library and
//              linked both in PEI & DXE south bridge FFS.
//
// Notes:       MAKE SURE NO PEI OR DXE SPECIFIC CODE IS NEEDED
//
//<AMI_FHDR_END>
//*************************************************************************

//---------------------------------------------------------------------------
// Include(s)
//---------------------------------------------------------------------------

#include <Efi.h>
#include <Token.h>
#include <AmiPeiLib.h>
#include <AmiDxeLib.h>
#include <Protocol\PciRootBridgeIo.h>
#include <AmiCspLib.h>
#include "PchAccess.h"
#include "RTC.h"
#if Capsule2_0_SUPPORT
#include <capsule.h>    //CAPSULE20
#endif
#include <Include\PchRegs.h>
#include <Include\PchRegs\PchRegsLpc.h>

#if CSM_SUPPORT
#include <Protocol\LegacyInterrupt.h>
#endif

#include "CpuRegs.h"					// EIP106353

#if defined HPET_PROTOCOL_SUPPORT && HPET_PROTOCOL_SUPPORT == 1
#include <Protocol\SbHpet.h>
#endif

//---------------------------------------------------------------------------
// Constant, Macro and Type Definition(s)
//---------------------------------------------------------------------------
// Constant Definition(s)

#ifndef BIT35							// EIP106353 >>
#define BIT35 0x0000000800000000ULL
#endif									// EIP106353 <<

#if CSM_SUPPORT

#define MAX_PIRQS               8  // Porting Required.

#endif

#ifndef CAPSULE_SUPPORT

#if defined Capsule2_0_SUPPORT && Capsule2_0_SUPPORT
#define CAPSULE_SUPPORT 1
#else
#define CAPSULE_SUPPORT 0
#endif

#endif

// Macro Definition(s)

// Type Definition(s)

typedef VOID (SB_OEM_S3_WARMRESET_CALLBACK) (VOID);

typedef EFI_STATUS (SB_RUN_RESET_CALLBACK) (
  IN  EFI_RESET_TYPE  ResetType
);

typedef struct {
  UINT8   Device;
  UINT8   Function;
} USB_CONTROLLER;

// Function Prototype(s)

//---------------------------------------------------------------------------
// Variable and External Declaration(s)
//---------------------------------------------------------------------------
// Variable Declaration(s)
#if defined CAPSULE_SUPPORT && CAPSULE_SUPPORT == 1
extern SB_OEM_S3_WARMRESET_CALLBACK \
                                 SB_OEM_S3_WARMRESET_CALLBACK_LIST EndOfList;
SB_OEM_S3_WARMRESET_CALLBACK* SbS3InsteadOfWarmResetCallBackList[] = \
                                    {SB_OEM_S3_WARMRESET_CALLBACK_LIST NULL};
#endif

extern SB_RUN_RESET_CALLBACK SB_RUN_RESET_CALLBACK_LIST EndOfList1;
SB_RUN_RESET_CALLBACK* SbRunResetCallbackList[] = {SB_RUN_RESET_CALLBACK_LIST NULL};

//---------------------------------------------------------------------------
// The following table contains the information regarding the PIRQ routing
// registers and other South Bridge registers that need to be restored
// during the S3 wakeup.
// Mention all register address (bus, device, function , register), specify
// the size of the register ans the mask also.
//---------------------------------------------------------------------------
 
BOOT_SCRIPT_SB_PCI_REG_SAVE gSBRegsSaveTbl[] = {
    {SB_REG(SB_REG_PIRQ_A),     EfiBootScriptWidthUint8, 0xff},
    {SB_REG(SB_REG_PIRQ_B),     EfiBootScriptWidthUint8, 0xff},
    {SB_REG(SB_REG_PIRQ_C),     EfiBootScriptWidthUint8, 0xff},
    {SB_REG(SB_REG_PIRQ_D),     EfiBootScriptWidthUint8, 0xff},
    {SB_REG(SB_REG_PIRQ_E),     EfiBootScriptWidthUint8, 0xff},
    {SB_REG(SB_REG_PIRQ_F),     EfiBootScriptWidthUint8, 0xff},
    {SB_REG(SB_REG_PIRQ_G),     EfiBootScriptWidthUint8, 0xff},
    {SB_REG(SB_REG_PIRQ_H),     EfiBootScriptWidthUint8, 0xff},
    {SB_REG(SB_REG_GEN_PMCON_1),EfiBootScriptWidthUint16, 0xffff},// SMI Timer
    {SB_REG(SB_REG_GEN_PMCON_3),EfiBootScriptWidthUint16, 0xffff},// SMI Timer
    {SB_REG(SB_REG_LPC_IO_DEC), EfiBootScriptWidthUint16, 0xffff},
    {SB_REG(SB_REG_LPC_EN),     EfiBootScriptWidthUint16, 0xffff},
    {SB_REG(SB_REG_GEN1_DEC),   EfiBootScriptWidthUint32, 0xffffffff},
    {SB_REG(SB_REG_GEN2_DEC),   EfiBootScriptWidthUint32, 0xffffffff},
    {SB_REG(SB_REG_GEN3_DEC),   EfiBootScriptWidthUint32, 0xffffffff},
    {SB_REG(SB_REG_GEN4_DEC),   EfiBootScriptWidthUint32, 0xffffffff},
};

#define NUM_SB_PCI_REG_SAVE \
                  sizeof(gSBRegsSaveTbl)/ sizeof(BOOT_SCRIPT_SB_PCI_REG_SAVE)

#if CSM_SUPPORT

UINT8   bMaxPIRQ = MAX_PIRQS; // For CSM
UINT8   bRouterBus = SB_BUS; // PORTING REQUIRED (Use appropriate Equate)
UINT8   bRouterDevice = SB_DEV; // PORTING REQUIRED (Use appropriate Equate)
UINT8   bRouterFunction = SB_FUN; // PORTING REQUIRED (Use appropriate Equate)
UINT8   RRegs[MAX_PIRQS] = { SB_REG_PIRQ_A, \
                             SB_REG_PIRQ_B, \
                             SB_REG_PIRQ_C, \
                             SB_REG_PIRQ_D, \
                             SB_REG_PIRQ_E, \
                             SB_REG_PIRQ_F, \
                             SB_REG_PIRQ_G, \
                             SB_REG_PIRQ_H }; // Porting required

#endif
// Local variable
static EFI_PCI_ROOT_BRIDGE_IO_PROTOCOL   *gPciRootBridgeIo;

// GUID Definition(s)

// Protocol Definition(s)

// External Declaration(s)

// Function Definition(s)
BOOLEAN CheckOff20hBit28(IN UINT32 GbEBase);
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
// Start OF CSM Related Porting Hooks
//---------------------------------------------------------------------------

#if CSM_SUPPORT

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:   SBGen_InitializeRouterRegisters
//
// Description: This function is clears the routing registers to default
//              values
//
// Input:       PciRBIo - Root bridge IO protocol pointer
//
// Output:      EFI_SUCCESS
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS SBGen_InitializeRouterRegisters (
    IN EFI_PCI_ROOT_BRIDGE_IO_PROTOCOL      *PciRBIo )
{
    UINT8       RegIdx;

    gPciRootBridgeIo = PciRBIo; // Save RB IO value for later use

    for (RegIdx = 0; RegIdx < MAX_PIRQS; RegIdx++)
        WRITE_PCI8_SB(RRegs[RegIdx], 0x80);

    return EFI_SUCCESS;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:   SBGen_GetPIRQIndex
//
// Description: This function returns the 0 based PIRQ index (PIRQ0, 1 etc)
//              based on the PIRQ register number specified in the routing
//              table.
//
// Input:       PIRQRegister - Register number of the PIR
//
// Output:      An 8Bit Index for RRegs table, its range is 0 - (MAX_PIRQ -1)
//              if PIRQRegister is invalid, then 0xff will be returned.
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

UINT8 SBGen_GetPIRQIndex (
    IN UINT8        PIRQRegister )
{
  UINT8   rrIndx = 0;

  while ((rrIndx < MAX_PIRQS) && (RRegs[rrIndx] != PIRQRegister)) rrIndx++;

  if (rrIndx == MAX_PIRQS) return 0xff;

  return rrIndx;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:   SBGen_ReadPirq
//
// Description: This function reads the IRQ associated with the PIRQ from
//              the chipset register
//
// Input:       This       - Pointer to Legacy interrupt protocol
//              PirqNumber - PIRQ number to read
//              PirqData   - IRQ programmed for this PIRQ (BIT7 will be
//                           set if the PIRQ is not programmed)
//
// Output:      EFI_STATUS
//                  EFI_SUCCESS           - On successfull IRQ value return
//                  EFI_INVALID_PARAMETER - If PirqNumber is greater than max
//                                          PIRQs
//
// Notes:       Here is the control flow of this function:
//                1. If Invalid PirqNumber, return EFI_INVALID_PARAMETER.
//                2. Read into *PriqData from PIRQ register for Pirq requested
//                3. Return EFI_SUCCESS.
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS SBGen_ReadPirq (
  IN EFI_LEGACY_INTERRUPT_PROTOCOL    *This,
  IN UINT8                            PirqNumber,
  OUT UINT8                           *PirqData )
{
    if (PirqNumber > MAX_PIRQS) return EFI_INVALID_PARAMETER;

    // If Pirq is not routed, bit 7 is set, however specification does not
    // specify a return error for this condition.
    *PirqData = READ_PCI8_SB(RRegs[PirqNumber]);

    return EFI_SUCCESS;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:   SBGen_WritePirq
//
// Description: This function writes an IRQ value allocated for the PIRQ by
//              programming the chipset register
//
// Input:       This       - Pointer to Legacy interrupt protocol
//              PirqNumber - PIRQ number to read
//              PirqData   - IRQ to be programmed
//
// Output:      EFI_STATUS
//                  EFI_SUCCESS           - On successfull IRQ value return
//                  EFI_INVALID_PARAMETER - If PirqNumber is greater than
//                                          max PIRQs or PirqData is greater
//                                          than 15 (MAX IRQ)
//
// Notes:       Here is the control flow of this function:
//                1. If Invalid PirqNumber or PirqData is greater than 15,
//                   return EFI_INVALID_PARAMETER.    
//                2. Write PirqData to PIRQ register for Pirq requested.
//                3. Return EFI_SUCCESS.
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS SBGen_WritePirq (
  IN EFI_LEGACY_INTERRUPT_PROTOCOL    *This,
  IN UINT8                            PirqNumber,
  IN UINT8                            PirqData )
{
    UINT8           PirqValue = PirqData & 0x0f;

    if (PirqNumber > MAX_PIRQS) return EFI_INVALID_PARAMETER;
    if (PirqData > 15) return EFI_INVALID_PARAMETER;

    WRITE_PCI8_SB(RRegs[PirqNumber], PirqValue);

    return EFI_SUCCESS;
}

//---------------------------------------------------------------------------
#endif  // END OF CSM Related Porting Hooks
//---------------------------------------------------------------------------
//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure: SbFindCapPtr
//
// Description: This function searches the PCI address space for the PCI
//              device specified for a particular capability ID and returns
//              the offset in the PCI address space if one found
//
// Input:    UINT64  PciAddress,
//           UINT8   CapId
//
// Output:  Capability ID Address if one found
//          Otherwise returns 0
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
UINT32 SbFindCapPtr(
 IN UINT64  PciAddress,
 IN UINT8   CapId
)
{
  UINT8   Value;
  UINT32  Address = (UINT32)PciAddress;

  Address = (Address & 0xffffff00) | 6; //PCI Status Register.
  Value = READ_MEM8(Address + 0);

  if (Value == 0xff) return 0;          // No device.
  if (!(Value & (1 << 4))) return 0;    // Check if capabilities list.
   
  *(UINT8*)&Address = 0x34;             // Register to First capabilities pointer
                                        // if 0, then capabilities
  for(;;)
  {
    Value = READ_MEM8(Address + 0);
    if (Value == 0) return 0;

    *(UINT8*)&Address = Value;          // PciAddress = ptr to CapID
    Value = READ_MEM8(Address + 0);     // New cap ptr.

    //If capablity ID, return register that points to it.
    if (Value == CapId) return Address; 

    ++Address;                          // Equals to next capability pointer.
  }
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:   SBSwSmiWriteToBootScript
//
// Description: Write SB necessary SW SMIs to boot script.
//
// Input:       *BootScriptSave - Pointer to Boot Scrpit Save Protocol.
//
// Output:      EFI_SUCCESS
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID SBSwSmiWriteToBootScript (
  IN AMI_S3_SAVE_PROTOCOL *BootScriptSave )
{

    UINT8       Value8;

    // Generate an ACPI Enable SMI when S3 resuming.
    Value8 = SW_SMI_ACPI_ENABLE;
    BOOT_SCRIPT_S3_IO_WRITE_MACRO( BootScriptSave, \
                                   EfiBootScriptWidthUint8, \
                                   SW_SMI_IO_ADDRESS, \
                                   1, \
                                   &Value8 );

    // Generate a Software SMI to enable SB patched codes when S3 resuming.
    Value8 = SW_SMI_SB_ACPI_S3;
    BOOT_SCRIPT_S3_IO_WRITE_MACRO( BootScriptSave, \
                                   EfiBootScriptWidthUint8, \
                                   SW_SMI_IO_ADDRESS, \
                                   1, \
                                   &Value8);
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:   SBGen_WriteBootScript
//
// Description: This writes the PIRQ to boot script before booting.
//
// Input:       *BootScriptSave - Pointer to Boot Scrpit Save Protocol.
//
// Output:      EFI_SUCCESS
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS SBGen_WriteBootScript (
  IN AMI_S3_SAVE_PROTOCOL *BootScriptSave )
{
    UINTN       i;
    UINT32      Value32;

    //Porting required: Write Boot Script
    for (i = 0; i < NUM_SB_PCI_REG_SAVE; ++i) {
        gPciRootBridgeIo->Pci.Read( gPciRootBridgeIo, \
                                    gSBRegsSaveTbl[i].Width,
                                    gSBRegsSaveTbl[i].Address,
                                    1,
                                    &Value32 );
        Value32 &= gSBRegsSaveTbl[i].Mask;
        BOOT_SCRIPT_S3_PCI_CONFIG_WRITE_MACRO( BootScriptSave, \
                                               gSBRegsSaveTbl[i].Width, \
                                               gSBRegsSaveTbl[i].Address, \
                                               1, \
                                               &Value32 );
    }

    SBSwSmiWriteToBootScript(BootScriptSave);

    return EFI_SUCCESS;
}

#if SB_RESET_PPI_SUPPORT
#if defined CAPSULE_SUPPORT && CAPSULE_SUPPORT == 1
//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:   SBLib_S3InsteadOfWarmResetCallBack
//
// Description: This function calls registered callbacks for S3 RTC/Timer
//              (WarmBoot) eLink.
//
// Input:       None
//
// Output:      None
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

VOID SBLib_S3InsteadOfWarmResetCallBack (VOID)
{
    UINTN   i;

    for (i = 0; SbS3InsteadOfWarmResetCallBackList[i] != NULL; i++) 
        SbS3InsteadOfWarmResetCallBackList[i]();
}
//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:   SBLib_S3InsteadOfWarmReset
//
// Description: This function puts system into ACPI S3 State.
//              if token ENABLE_RTC_ONE_SECOND_WAKEUP = 1, then it setups RTC
//              1 second alarm as well.
//
// Input:       None
//
// Output:      None, system will enter ACPI S3 State.
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

VOID SBLib_S3InsteadOfWarmReset (VOID)
{
#if ENABLE_RTC_ONE_SECOND_WAKEUP
    UINT8       Hour;
    UINT8       Minute;
    UINT8       Second;
    BOOLEAN     InBCD = TRUE;

    // Determine if RTC is in BCD mode
    if ( READ_IO8_RTC(0x0b) & 0x4 ) InBCD = FALSE; // Bit 2
        
    // Wait for time update to complete before reading the values,
    // while bit 7 is set the time update is in progress.
    while( READ_IO8_RTC(0x0a) & 0x80 );

    // Read current hour, minute, second
    Hour = READ_IO8_RTC(0x04); // Hours
    Minute = READ_IO8_RTC(0x02); // Minutes
    Second = READ_IO8_RTC(0x00); // Seconds

    // Convert second to decimal from BCD and increment by 1
    if (InBCD) Second = (Second >> 4) * 10 + (Second & 0x0F);
    Second += 2;
    
    if (Second > 59) {
        Second -= 60;
        if (InBCD) Minute = (Minute >> 4) * 10 + (Minute & 0x0F);
        Minute++;
        if (Minute > 59){
            Minute = 0;
            if (InBCD) Hour = (Hour >> 4) * 10 + (Hour & 0x0F);
            Hour++;
            // Check 24 hour mode/12 hour mode, Bit1 1=24hour else 12 hour
            if ( READ_IO8_RTC(0x0b) & 0x2 ) {
                if(Hour > 23) Hour = 0;
            } else {
                if(Hour > 11) Hour = 0;
            }

            if (InBCD) Hour = Hour % 10 + ( (Hour / 10) << 4 ) ;
        }

        if (InBCD) Minute = Minute % 10 + ( (Minute / 10) << 4 ) ;
    }

    // Convert from decimal to BCD
    if (InBCD) Second = Second % 10 + ( (Second / 10) << 4 ) ;
    
    // Set the alarm
    WRITE_IO8_RTC(0x05, Hour); // Hours Alarm
    WRITE_IO8_RTC(0x03, Minute); // Minutes Alarm
    WRITE_IO8_RTC(0x01, Second); // Seconds Alarm

                                        // [EIP119703]>
    // Clear date alarm.
    WRITE_IO8_RTC(0x0D, READ_IO8_RTC(0x0D) & BIT07);
                                        // <[EIP119703]

    // Enable the alarm
    SET_IO8_RTC(0x0b, 0x20); // Bit 5

    if (READ_IO16_PM(ACPI_IOREG_PM1_STS) & 0x400) {
      READ_IO8_RTC(0x8C);
      WRITE_IO16_PM(ACPI_IOREG_PM1_STS, 0x400);  // 0x00
    }

    // Set RTC_EN bit in PM1_EN to wake up from the alarm
    SET_IO16_PM(ACPI_IOREG_PM1_EN, 0x400 ); // 0x02
#endif

    // Do any specific porting if needed.
    SBLib_S3InsteadOfWarmResetCallBack();

    // Enable Sleep SMI for all S3 sleep SMI callback functions.
    SET_IO32_PM(ACPI_IOREG_SMI_EN, BIT04); // 0x30
    // Triger S3 sleep callback functions.
    RW_IO32_PM(ACPI_IOREG_PM1_CNTL, 0x1400, 0x1c00 ); // 0x04
    SET_IO32_PM(ACPI_IOREG_PM1_CNTL, 0x2000 ); // 0x04
}
#endif

//<AMI_PHDR_START>
//----------------------------------------------------------------------------------------
// Procedure: SB_Shutdown
// Description: This function Shuts the system down (S5)
//
// Input: VOID
//
// Output: VOID
//
//-----------------------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID SB_Shutdown(VOID)
{
    //Check if Sleep SMI is enabled we will disable it.
    RESET_IO16_PM(R_PCH_SMI_EN, BIT04);  // 0x30

    //Clear All PM Statuses
    WRITE_IO16_PM(R_PCH_ACPI_PM1_STS, \
           READ_IO16_PM(R_PCH_ACPI_PM1_STS)); // 0x00

    //Go to S5
    SET_IO16_PM(R_PCH_ACPI_PM1_CNT, 0x0f << 10); // 0x04

    EFI_DEADLOOP()
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   ClearGPIOResetSelect
//
// Description: Intel PCH Specification update rev 1.02,
//              Document Changes 24. Update sec 19.5
//              19.5 Addttional Consideration, Step 2
//              System BIOS is recommended to clear "GPIO Reset Select"
//              registers [GP_RST_SEL1(GPIOBASE + offset 60h), GP_RST_SEL2
//              (GPIOBASE + offset 64h), GP_RST_SEL3(GPIOBASE + offset 68h)
//              before issuing a hard or global reset unless specially
//              requested by the platform designer.
//              
// Input:       None
//
// Output:      None
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID ClearGPIOResetSelect(VOID)
{
  WRITE_IO32 (GPIO_BASE_ADDRESS + GP_IOREG_GP_RST_SEL1, BIT30); // 0x60
  WRITE_IO32 (GPIO_BASE_ADDRESS + GP_IOREG_GP_RST_SEL2, BIT30); // 0x64
  WRITE_IO32 (GPIO_BASE_ADDRESS + GP_IOREG_GP_RST_SEL3, BIT30); // 0x68
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   SbLib_RunTimeResetCallback
//
// Description: Dispatch E-Link SbRuntimeResetElinkList.
//              
// Input:       IN EFI_RESET_TYPE ResetType
//
// Output:      EFI_STATUS
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS
SbLib_RunTimeResetCallback(
  IN     EFI_RESET_TYPE           ResetType
  )
{
  EFI_STATUS  Status = EFI_SUCCESS;
  UINTN       i;

  for (i = 0; SbRunResetCallbackList[i] != NULL; i++)
    Status = SbRunResetCallbackList[i](ResetType);

  return Status;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:   SBLib_ResetSystem
//
// Description: This function is the reset call interface function published
//              by the reset PPI
//
// Input:       ResetType - Type of reset to be generated
//
// Output:      SYSTEM RESET
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

VOID SBLib_ResetSystem (
  IN EFI_RESET_TYPE         ResetType )
{
  UINT8               OutputData;
  UINT32              Data32;
  UINT16              Data16;
#if defined CAPSULE_SUPPORT && CAPSULE_SUPPORT == 1
  EFI_GUID        SbWarmResetGuid = SB_WARM_RESET_GUID;
  CHAR16          SbWarmResetVar[] = SB_WARM_RESET_VARIABLE;
  UINT32          SbWarmResetFlag = SB_WARM_RESET_TAG;
  EFI_STATUS      Status = EFI_SUCCESS;
  EFI_GUID        gCapsuleVendorGuid = EFI_CAPSULE_AMI_GUID;
  EFI_PHYSICAL_ADDRESS  IoData;
  UINTN           Size = sizeof(EFI_PHYSICAL_ADDRESS);
#endif

  SbLib_RunTimeResetCallback(ResetType); 

  switch (ResetType) {
    case EfiResetWarm:
#if defined CAPSULE_SUPPORT && CAPSULE_SUPPORT == 1
    if (pRS->GetVariable(CAPSULE_UPDATE_VAR,&gCapsuleVendorGuid, NULL, &Size, &IoData) == EFI_SUCCESS) {
      Status = pRS->SetVariable( SbWarmResetVar, \
                                 &SbWarmResetGuid, \
                                 EFI_VARIABLE_NON_VOLATILE | \
                                 EFI_VARIABLE_BOOTSERVICE_ACCESS | \
                                 EFI_VARIABLE_RUNTIME_ACCESS, \
                                 sizeof(SbWarmResetFlag), \
                                 &SbWarmResetFlag );

      SBLib_S3InsteadOfWarmReset();
      return;
    }
#endif
      WRITE_IO8 (R_PCH_RST_CNT, V_PCH_RST_CNT_SOFTSTARTSTATE);
      OutputData  = V_PCH_RST_CNT_SOFTRESET;
      break;

    case EfiResetCold:
      WRITE_IO8 (R_PCH_RST_CNT, V_PCH_RST_CNT_HARDSTARTSTATE);
                                        // [EIP81593]>
#if defined COLD_RESET_WITH_POWER_CYCLE && \
            COLD_RESET_WITH_POWER_CYCLE == 1
      OutputData  = V_PCH_RST_CNT_FULLRESET;
#else
      OutputData  = V_PCH_RST_CNT_HARDRESET;
#endif
                                        // <[EIP81593]
      break;

    case EfiResetShutdown:
      //
      // Firstly, ACPI decode must be enabled
      //
      SET_PCI8_SB(R_PCH_LPC_ACPI_CNT, B_PCH_LPC_ACPI_CNT_ACPI_EN);

      //
      // Then, GPE0_EN should be disabled to avoid any GPI waking up the system from S5
      //
      Data16 = 0;

      WRITE_IO32_PM(R_PCH_ACPI_GPE0a_EN, Data16);
      WRITE_IO16_PM(R_PCH_ACPI_GPE0b_EN, Data16);

      //
      // Secondly, PwrSts register must be cleared
      //
      // Write a "1" to bit[8] of power button status register at
      // (PM_BASE + PM1_STS_OFFSET) to clear this bit
      //
      Data16 = B_PCH_SMI_STS_PM1_STS_REG;
      WRITE_IO16_PM(R_PCH_ACPI_PM1_STS, Data16);

      //
      // Finally, transform system into S5 sleep state
      //
      Data32 = READ_IO32_PM(R_PCH_ACPI_PM1_CNT);
      Data32 &= ~(B_PCH_ACPI_PM1_CNT_SLP_TYP + B_PCH_ACPI_PM1_CNT_SLP_EN);
      Data32 |= V_PCH_ACPI_PM1_CNT_S5;
      WRITE_IO32_PM(R_PCH_ACPI_PM1_CNT, Data32);
      Data32 = Data32 | B_PCH_ACPI_PM1_CNT_SLP_EN;
      WRITE_IO32_PM(R_PCH_ACPI_PM1_CNT, Data32);

      EFI_DEADLOOP ()

    default:
      return;
  }

  WRITE_IO8 (R_PCH_RST_CNT, OutputData);
  //
  // Waiting for system reset
  //
  EFI_DEADLOOP ()
}

#endif

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:   SBLib_ExtResetSystem
//
// Description: This function is the extended reset call interface function
//              provided by SB.
//
// Input:       ResetType - The extended type of reset to be generated
//
// Output:      SYSTEM RESET
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

VOID SBLib_ExtResetSystem (
  IN SB_EXT_RESET_TYPE      ResetType )
{
  UINT16              GpioBase;
  UINT8               OutputData;
  EFI_STATUS          Status = EFI_SUCCESS;

  GpioBase = READ_PCI16_SB (R_PCH_LPC_GPIO_BASE) & B_PCH_LPC_GPIO_BASE_BAR;

  // Issue some delay before system reset.
#if SB_STALL_PPI_SUPPORT
  Status = CountTime(4000, PM_BASE_ADDRESS); // 1ms
#endif

  // Disable All SMI Enables, include the Global SMI.
  WRITE_IO32_PM(ACPI_IOREG_SMI_EN, 0); // 0x30

  switch (ResetType) {
    case SbResetFull:
    case SbResetGlobal:
      WRITE_IO32 ((GpioBase + R_PCH_GP_RST_SEL), 0);
      WRITE_IO32 ((GpioBase + R_PCH_GP_RST_SEL2), 0);
      WRITE_IO32 ((GpioBase + R_PCH_GP_RST_SEL3), 0);

      if (ResetType == SbResetGlobal)
        SET_PCI32_SB(R_PCH_LPC_PMIR, B_PCH_LPC_PMIR_CF9GR);

      OutputData = V_PCH_RST_CNT_FULLRESET;
      break;

    default:
      return;
  }

  WRITE_IO8 (R_PCH_RST_CNT, OutputData);

  // We should never get this far
  EFI_DEADLOOP();
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:   StopUsb
//
// Description: This routine stops all USB controller action. 
//
// Input:       Bus - The PCI bus number for the USB controller
//              Dev - The PCI device number for the USB controller
//              Fun - The PCI function number for the USB controller
//
// Output:      None
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

VOID StopUsb (
    IN UINT8        Bus,
    IN UINT8        Dev, 
    IN UINT8        Fun )
{
//####    UINT32          MmioBase;
//####    UINT16          IoBase;
//####    UINT16          TimeOut = 0x1000;

//####    if (READ_PCI32(Bus, Dev, Fun, 0) != 0xffffffff) {
//####    if ((READ_PCI32(Bus, Dev, Fun, 4) & 0x3) == 0) return;
//####        if (READ_PCI8(Bus, Dev, Fun, USB_REG_PI) == 0x20) { // USB 2.0
//####            WRITE_PCI8(Bus, Dev, Fun, USB20_REG_LEGSUP_EXTCS, 0); // 0x6C
//####            MmioBase = READ_PCI32(Bus, Dev, Fun, USB20_REG_MEM_BASE_ADDR);
//####            RESET_MEM32(MmioBase | 0x20, 1);
//####            while (READ_MEM32(MmioBase | 0x20) & 1) {
//####                TimeOut--;
//####                if (TimeOut == 0) break;
//####            }
//####        } else { // USB 1.1
//####            WRITE_PCI8(Bus, Dev, Fun, USB_REG_LEGSUP, 0); // 0xC0
//####            IoBase = READ_PCI32(Bus, Dev, Fun, USB_REG_BASE_ADDR) & 0xfffe;
//####            RESET_IO16(IoBase, 1);
//####            while (IoRead16(IoBase) & 1) {
//####                TimeOut--;
//####                if (TimeOut == 0) break;
//####            }
//####        }
//####    }
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure: UsbS02SxWorkaround
//
// Description: PCH BIOS Spec Rev 0.5.0, Section 12.10.1
//              Additional Programming Requirements prior to enter S4/S5
//
// Input: None
//
// Output: None
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID
UsbS02SxWorkaround (
  VOID
  )
{
  UINT8           Index;
  UINTN           EhciPciRegBase;
  UINT32          UsbBar;
  UINT16          CmdReg;
  UINT16          PowerState;
  USB_CONTROLLER  EhciControllersMap[PchEhciControllerMax] = {
    {
      PCI_DEVICE_NUMBER_PCH_USB,
      PCI_FUNCTION_NUMBER_PCH_EHCI
    },
    {
      PCI_DEVICE_NUMBER_PCH_USB_EXT,
      PCI_FUNCTION_NUMBER_PCH_EHCI2
    }
  };

  ///
  /// System BIOS must execute the following steps prior to enter S4/S5.
  ///
  for (Index = 0; Index < GetPchEhciMaxControllerNum (); Index++) {
    ///
    /// Step 1
    /// Read "Memory Base Address (MEM_BASE) Register" of D26/D29:F0
    ///
    EhciPciRegBase  = MmPciAddress (PCIEX_BASE_ADDRESS, 0, EhciControllersMap[Index].Device, EhciControllersMap[Index].Function, 0);
    UsbBar          = MmioRead32 (EhciPciRegBase + R_PCH_EHCI_MEM_BASE);
    CmdReg          = MmioRead16 (EhciPciRegBase + R_PCH_EHCI_COMMAND_REGISTER);
    PowerState      = MmioRead16 (EhciPciRegBase + R_PCH_EHCI_PWR_CNTL_STS);

    if (UsbBar != 0xFFFFFFFF) {
      ///
      /// Check if the Ehci device is in D3 power state
      ///
      if ((PowerState & B_PCH_EHCI_PWR_CNTL_STS_PWR_STS) == V_PCH_EHCI_PWR_CNTL_STS_PWR_STS_D3) {
        ///
        /// Step 2
        /// Set "Power State" bit of PWR_CNTL_STS register, D26/D29:F0:54h [1:0] = 0h
        ///
        MmioWrite16 (EhciPciRegBase + R_PCH_EHCI_PWR_CNTL_STS, (PowerState &~B_PCH_EHCI_PWR_CNTL_STS_PWR_STS));
        ///
        /// Step 3
        /// Write back the value from step 1 to the "Memory Base Address (MEM_BASE) Register" of D26/D29:F0
        ///
        MmioWrite32 (EhciPciRegBase + R_PCH_EHCI_MEM_BASE, UsbBar);
        ///
        /// Step 4
        /// Enable "Memory Space Enable (MSE)" bit, set D26/D29:F0:04h [1] = 1b.
        ///
        SET_MEM16 (
          EhciPciRegBase + R_PCH_EHCI_COMMAND_REGISTER,
          (UINT16) (B_PCH_EHCI_COMMAND_MSE)
          );
      }
      ///
      /// Step 5
      /// Clear "Asynchronous Schedule Enable" and "Periodic Schedule Enable" bits, if "Run/Stop (RS)" bit, MEM_BASE + offset 20h [0] = 1b.
      /// Proceed to steps below if "Run/Stop (RS)" bit, MEM_BASE + offset 20h [0] = 0b.
      ///
      if (!(MmioRead32 (UsbBar + R_PCH_EHCI_USB2CMD) & B_PCH_EHCI_USB2CMD_RS)) {
        RESET_MEM32 (UsbBar + R_PCH_EHCI_USB2CMD, (UINT32)(B_PCH_EHCI_USB2CMD_ASE | B_PCH_EHCI_USB2CMD_PSE));
        SET_MEM32 (UsbBar + R_PCH_EHCI_USB2CMD, B_PCH_EHCI_USB2CMD_RS);
      }
      ///
      /// Step 6
      /// If "Port Enabled/Disabled" bit of Port N Status and Control (PORTSC) Register is set, MEM_BASE + 64h [2] = 1b,
      /// proceed steps below else continue with S4/S5.
      ///
      if ((MmioRead32 (UsbBar + R_PCH_EHCI_PORTSC0) & R_PCH_EHCI_PORTSC0_PORT_EN_DIS)) {
        ///
        /// Step 7
        /// Ensure that "Suspend" bit of Port N Status and Control (PORTSC) Register is set, MEM_BASE + 64h [7] = 1b.
        ///
        if (!(MmioRead32 (UsbBar + R_PCH_EHCI_PORTSC0) & R_PCH_EHCI_PORTSC0_SUSPEND)) {
          SET_MEM32 (UsbBar + R_PCH_EHCI_PORTSC0, R_PCH_EHCI_PORTSC0_SUSPEND);
        }
        ///
        /// Step 8
        /// Set delay of 25ms
        ///
        CountTime((25 * 1000), PM_BASE_ADDRESS);
        ///
        /// Step 9
        /// Clear "Run/Stop (RS)" bit, MEM_BASE + offset 20h [0] = 0b.
        ///
        RESET_MEM32 (UsbBar + R_PCH_EHCI_USB2CMD, (UINT32)(B_PCH_EHCI_USB2CMD_RS));
      }
      ///
      /// If the EHCI device is in D3 power state before executing this WA
      ///
      if ((PowerState & B_PCH_EHCI_PWR_CNTL_STS_PWR_STS) == V_PCH_EHCI_PWR_CNTL_STS_PWR_STS_D3) {
        ///
        /// Restore PCI Command Register
        ///
        MmioWrite16 (EhciPciRegBase + R_PCH_EHCI_COMMAND_REGISTER, CmdReg);
        ///
        /// Set "Power State" bit of PWR_CNTL_STS register to D3 state, D26/D29:F0:54h [1:0] = 3h
        ///
        MmioWrite16 (EhciPciRegBase + R_PCH_EHCI_PWR_CNTL_STS, PowerState);
      }
      ///
      /// Step 10
      /// Continue with S4/S5
      ///
    }
  }
}
                                        // [EIP83075]>
//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure: XhciS5Workaround
//
// Description: PCH BIOS Spec Rev 0.7.0, Section 13.5
//              Additional xHCI Controller Configurations Prior to Entering S5
//
// Input: None
//
// Output: None
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID XhciS5Workaround ( VOID )
{
  UINT32      XhciMmioBase;
  //
  // Check if XHCI controller is enabled
  //
  if ((READ_MEM32_RCRB(R_PCH_RCRB_FUNC_DIS) & B_PCH_RCRB_FUNC_DIS_XHCI) != 0) {
    return ;
  }
  //
  // System BIOS must execute the following steps for all steppings prior to S5
  //
  //
  XhciMmioBase = READ_PCI32( DEFAULT_PCI_BUS_NUMBER_PCH, \
                              PCI_DEVICE_NUMBER_PCH_XHCI, \
                              PCI_FUNCTION_NUMBER_PCH_XHCI, \
                              R_PCH_XHCI_MEM_BASE
                              ) & ~(0x0F);
  
  if (XhciMmioBase != 0) {
    //Clear "Run/Stop (RS)" bit,
    RESET_MEM32(XhciMmioBase + R_PCH_XHCI_USBCMD, B_PCH_XHCI_USBCMD_RS);
  }
  // Step 1
  // Set D3hot state - 11b
  //
  SET_PCI8( DEFAULT_PCI_BUS_NUMBER_PCH, \
            PCI_DEVICE_NUMBER_PCH_XHCI, \
            PCI_FUNCTION_NUMBER_PCH_XHCI, \
            R_PCH_XHCI_PWR_CNTL_STS, \
            (BIT00 | BIT01)
          );

  //
  // Step 2
  // Set "PME Enable" bit of PWR_CNTL_STS register, D20:F0:74h[8] = 1h
  //
  SET_PCI16( DEFAULT_PCI_BUS_NUMBER_PCH, \
             PCI_DEVICE_NUMBER_PCH_XHCI, \
             PCI_FUNCTION_NUMBER_PCH_XHCI, \
             R_PCH_XHCI_PWR_CNTL_STS, \
             BIT08
           );
}
                                        // <[EIP83075]

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:   SBLib_BeforeShutdown
//
// Description: This routine will be called before shutdown or ACPI S5,(If 
//              S5 Sleep SMI is enabled.
//
// Input:       None
//
// Output:      None
//
// Notes:       Porting required if any workaround is needed.
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

VOID SBLib_BeforeShutdown (VOID)
{
    UINT8           DevNo;
    UINT8           FunNo;

//####    StopUsb( EUSB_BUS, EUSB_DEV, EUSB_FUN );

    for (DevNo = 0; DevNo < 0x20 ; DevNo++) {
        if (READ_PCI32(0, DevNo, 0, PCI_VID) != 0xffffffff) {
            FunNo = (READ_PCI8(0, DevNo, 0, PCI_HDR) & 0x80) ? 8 : 1;
            do {
                FunNo--;
                if (READ_PCI32(0, DevNo, FunNo, PCI_VID) != 0xffffffff) {
                    RESET_PCI16(0, DevNo, FunNo, PCI_CMD, 4);
                }
            } while (FunNo);
        }
    }
}


//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:   SBLib_Shutdown
//
// Description: Shutdown the system (Enter soft-off/S5)
//
// Input:       None
//
// Output:      None
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

VOID SBLib_Shutdown (VOID)
{
    UINT16          Buffer16;

    // Clear ME wake status
    ClearMeWakeSts();

    UsbS02SxWorkaround();
    XhciS5Workaround();                 // [EIP83075]

    // Disable Sleep SMI
    RESET_IO32_PM(ACPI_IOREG_SMI_EN, 0x10); // 0x30

    SBLib_BeforeShutdown();

    // Clear power button status
    Buffer16 = READ_IO16(PM_BASE_ADDRESS) | (UINT16)(1 << 8);
    do {
        WRITE_IO16(PM_BASE_ADDRESS, Buffer16);
        for (Buffer16 = 0; Buffer16 < 0x100; Buffer16++)
            WRITE_IO8(IO_DELAY_PORT, (UINT8)Buffer16);
        Buffer16 = READ_IO16(PM_BASE_ADDRESS);
    } while (Buffer16 & 0x100);

    // Enter soft-off/S5
    RW_IO16(PM_BASE_ADDRESS + ACPI_IOREG_PM1_CNTL, \
                                              (SLP_S5 | 8 ) << 10, 15 << 10);

    // We should never get this far
    EFI_DEADLOOP();
}


//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:ClearMeWakeSts
//
// Description: Clear the ME wake up status.
//
// Input: None
//
// Output: None
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

VOID ClearMeWakeSts(VOID)
{
//    Mmio32(SB_RCBA, ICH_RCRB_PRSTS) |= BIT00;
    SET_MEM8_RCRB(R_PCH_RCRB_PRSTS, BIT00);
}


//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure: Enable_GbE_PME
//
// Description: Enable the Gigabit Ethernet Controller PME
//
// Input: None
//
// Output: None
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

VOID Enable_GbE_PME(VOID)
{
  if (READ_PCI16_LAN(R_PCH_LAN_VENDOR_ID) != 0xffff)
  {
    if (GetPchSeries() == PchLp) {
      WRITE_IO16_PM(ACPI_PCHLP_IOREG_GPE0_STS+0x0c, BIT13);
      SET_IO16_PM(ACPI_PCHLP_IOREG_GPE0_EN+0x0c, BIT13);
    } else {
      WRITE_IO16_PM(ACPI_IOREG_GPE0_STS, BIT13);
      SET_IO16_PM(ACPI_IOREG_GPE0_EN, BIT13);
    }
    SET_PCI16_LAN(R_PCH_LAN_PMCS, BIT08);
  }
}

VOID EnablePs2KeyboardMousePme(VOID)
{
      WRITE_IO16_PM(ACPI_IOREG_GPE0_STS, BIT11);
      SET_IO16_PM(ACPI_IOREG_GPE0_EN, BIT11);
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:   HighBitSet32
//
// Description: Returns the bit position of the highest bit set in a 32-bit value. Equivalent
//              to log2(x).
//
// Input:       Operand -  Operand The 32-bit operand to evaluate.
//
// Output:      Position of the highest bit set in Operand if found.
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
INTN
EFIAPI
HighBitSet32 (
  IN      UINT32                    Operand
  )
{
  INTN                              BitIndex;

  for (BitIndex = -1; Operand != 0; BitIndex++, Operand >>= 1);
  return BitIndex;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:   GetPowerOfTwo32
//
// Description: Returns the value of the highest bit set in a 32-bit value. Equivalent to
//              1 << HighBitSet32(x).
//
// Input:       Operand -  Operand The 32-bit operand to evaluate.
//
// Output:      Return 1 << HighBitSet32(Operand)
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
UINT32
EFIAPI
GetPowerOfTwo32 (
  IN      UINT32                    Operand
  )
{
  if (Operand == 0) {
    return 0;
  }

  return 1ul << HighBitSet32 (Operand);
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:   ChipsetFlashDeviceWriteEnable
//
// Description: This function is invoked to do any chipset specific
//              operations, that are necessary when enabling the Flash Part
//              for writing.
//
// Input:       None
//
// Output:      None
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

VOID ChipsetFlashDeviceWriteEnable (VOID)
{
//  UINT32 Data32;

  //
  // Set BIOSWE bit (B0:D31:F0 Offset DCh [0]) = 1b
  //
  RW_PCI8_SB(SB_REG_BIOS_CNTL, BIT00, BIT05);

  //
  // PCH BIOS Spec Section 3.7 BIOS Region SMM Protection Enabling
  // If the following steps are implemented:
  //  - Set the SMM_BWP bit (B0:D31:F0 Offset DCh [5]) = 1b
  //  - Follow the 1st recommendation in section 3.6
  // the BIOS Region can only be updated by following the steps bellow:
  //  - Once all threads enter SMM
  //  - Read memory location FED30880h OR with 00000001h, place the result in EAX,
  //    and write data to lower 32 bits of MSR 1FEh (sample code available)
  //  - Set BIOSWE bit (B0:D31:F0 Offset DCh [0]) = 1b
  //  - Modify BIOS Region
  //  - Clear BIOSWE bit (B0:D31:F0 Offset DCh [0]) = 0b
  //  - Read memory location FED30880h AND with FFFFFFFEh, place the result in EAX,
  //    and write data to lower 32 bits of MSR 1FEh (sample code available)
  //

  //
  // Check if SMM_BWP bit and BLE bit are both set
  //
  if ((READ_PCI8_SB(SB_REG_BIOS_CNTL) & 0x22) == 0x22) {
    //
    // Read memory location FED30880h OR with 00000001h, place the result in EAX,
    // and write data to lower 32 bits of MSR 1FEh (sample code available)
    //
																						// EIP106353 >>
    if ( !((ReadMsr (MSR_PLATFORM_INFO) & B_MSR_PLATFORM_INFO_PFAT_AVAIL) && 
           (ReadMsr (MSR_PLAT_FRMW_PROT_CTRL) & B_MSR_PLAT_FRMW_PROT_CTRL_EN)) ) {  
//          Data32 = MmioRead32 ((UINTN) (0xFED30880)) | (UINT32) (BIT0);
//          WriteMsr(0x1FE, Data32);
    }
																						// EIP106353 <<
  }

}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:   ChipsetFlashDeviceWriteDisable
//
// Description: This function is invoked to do any chipset specific
//              operations, that are necessary when disabling the Flash Part
//              for writing.
//
// Input:       None
//
// Output:      None
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

VOID ChipsetFlashDeviceWriteDisable (VOID)
{
//  UINT32 Data32;

  //
  // Clear BIOSWE bit (B0:D31:F0 Offset DCh [0]) = 0b
  //
  RESET_PCI8_SB(SB_REG_BIOS_CNTL, BIT00);
  //
  // Check if SMM_BWP bit and BLE bit are both set
  //
  if ((READ_PCI8_SB(SB_REG_BIOS_CNTL) & 0x22) == 0x22) {
    //
    // Read memory location FED30880h AND with FFFFFFFEh, place the result in EAX,
    // and write data to lower 32 bits of MSR 1FEh (sample code available)
    //
																						// EIP106353 >>
    if ( !((ReadMsr (MSR_PLATFORM_INFO) & B_MSR_PLATFORM_INFO_PFAT_AVAIL) && 
           (ReadMsr (MSR_PLAT_FRMW_PROT_CTRL) & B_MSR_PLAT_FRMW_PROT_CTRL_EN)) ) {  
//          Data32 = MmioRead32 ((UINTN) (0xFED30880)) & (UINT32) (~BIT0);
//          WriteMsr (0x1FE, Data32);
    }
																						// EIP106353 <<
  }
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------
// Procedure:   BiosLockEnableSMIFlashHook
//
// Description: The procedure clears BIOSWR_STS after Enable Flash SWSMI,
//              for prevent that AFU write operation fail when BIOS Lock
//              is enabled.
//
// Input:       UINT8        SwSmiNum
//              UINT64       Buffer
//
// Output:      UINT64       Buffer
//
// Returns:     NONE
//
//----------------------------------------------------------------------
//<AMI_PHDR_END>
VOID 
BiosLockEnableSMIFlashHook (
    IN UINT8            SwSmiNum,
    IN OUT UINT64       Buffer
)
{
    if ((SwSmiNum != 0x20) || \
        ((READ_PCI8_SB(R_PCH_LPC_BIOS_CNTL) & B_PCH_LPC_BIOS_CNTL_BLE) == 0))
      return;

    // Clear BIOSWR_STS
    SET_IO16_TCO(R_PCH_TCO1_STS, B_PCH_TCO1_STS_BIOSWR);

    // Clear TCO_STS
    SET_IO16_PM(R_PCH_SMI_STS, B_PCH_SMI_STS_TCO);
}   

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:   SBIsDefaultConfigMode
//
// Description: This function determines if the system should boot with the
//              default configuration. 
//
// Input:       EFI_PEI_SERVICES - Pointer to the PEI services table
//              EFI_PEI_READ_ONLY_VARIABLE2_PPI - Pointer to the Read 
//                                                Variable#2 PPI
//              (The pointer can be used to read and enumerate existing NVRAM
//               variables)
//
// Output:      TRUE - Firmware will boot with default configuration.
//
// Notes:       1. If boot with default configuration is detected, default
//                 values for NVRAM variables are used.
//              2. Normally we have to check RTC power status or CMOS clear
//                 jumper status to determine whether the system should boot
//                 with the default configuration.
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

BOOLEAN SBIsDefaultConfigMode (
    IN EFI_PEI_SERVICES                 **PeiServices,
    IN EFI_PEI_READ_ONLY_VARIABLE2_PPI  *ReadVariablePpi )
{
    UINT8           Buffer8;

    Buffer8 = READ_PCI8_SB(SB_REG_GEN_PMCON_3); // 0xA4 
    return (Buffer8 & 4) ? TRUE : FALSE;
}

#if SB_STALL_PPI_SUPPORT

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:   CountTime
//
// Description: This function delays for the number of micro seconds passed in
//
// Input:       DelayTime - Number of microseconds(us) to delay
//              BaseAddr  - The I/O base address of the ACPI registers
//
// Output:      EFI_SUCCESS
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS CountTime (
    IN UINTN        DelayTime,
    IN UINT16       BaseAddr ) // Only needs to be 16 bit for I/O address
{
// The following code is to generate delay for specified amount of micro
// seconds using ACPI timer.
    UINTN           TicksNeeded;
    UINT32          TimerValue;
    UINT32          NewTimerValue;
    UINTN           OverFlow;
    UINTN           TheRest;
    UINTN           EndValue;

    // Set up timer to point to the ACPI Timer register
    BaseAddr += ACPI_IOREG_PM1_TMR; // *** PORTING NEEDED

    // There are 3.58 ticks per us, so we have to convert the number of us
    // passed in to the number of ticks that need to pass before the timer has
    // expired convert us to Ticks, don't loose significant figures or as few
    // as possible do integer math in ticks/tens of ns and then divide by 100
    // to get ticks per us
    OverFlow = 0;

//#### TheRest = TicksNeeded = (DelayTime * 358) /100;
    TicksNeeded = DelayTime * 3;            //(DelayTime * 3)
    TicksNeeded += (DelayTime) / 2;         //(DelayTime * 5)/10
    TicksNeeded += (DelayTime * 2) / 25;        //(DelayTime * 8)/100
    TheRest = TicksNeeded;

    // 32 bits corresponds to approz 71 mins  no delay should be that long
    // otherwise get the number of times the counter will have to overflow
    // to delay as long as needed
    if (NUM_BITS_IN_ACPI_TIMER < MAX_ACPI_TIMER_BITS) {
        OverFlow = TicksNeeded / (1 << NUM_BITS_IN_ACPI_TIMER);
        TheRest = TicksNeeded % (1 << NUM_BITS_IN_ACPI_TIMER);
    }

    // Read ACPI Timer
    TimerValue = IoRead32( BaseAddr );

    // Need to adjust the values based off of the start time
    EndValue = TheRest + TimerValue;

    // Check for overflow on addition.  possibly a problem
    if (EndValue < TimerValue) {
        OverFlow++;
    } else {
        if (NUM_BITS_IN_ACPI_TIMER < MAX_ACPI_TIMER_BITS) { 
            // Here make sure that EndValue is less than the max value
            // of the counter
            OverFlow += EndValue / (1 << NUM_BITS_IN_ACPI_TIMER);
            EndValue = EndValue % (1 << NUM_BITS_IN_ACPI_TIMER);
        }
    }

    // Let the timer wrap around as many times as calculated
    while (OverFlow) {
        // read timer amd look to see if the new value read is less than
        // the current timer value.  if this happens the timer overflowed
        NewTimerValue = IoRead32(BaseAddr);

        if (NewTimerValue < TimerValue) OverFlow--;

        TimerValue = NewTimerValue;
    }

    // Now wait for the correct number of ticks that need to occur after
    // all the needed overflows
    while (EndValue > TimerValue) {
        NewTimerValue = IoRead32(BaseAddr);

        // check to see if the timer overflowed.  if it did then
        // the time has elapsed. Because EndValue should be greater than
        // TimerValue
        if (NewTimerValue < TimerValue) break;

        TimerValue = NewTimerValue;
      }

    return EFI_SUCCESS;
}


#endif

//---------------------------------------------------------------------------

#if CMOS_MANAGER_SUPPORT
//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// 
// Procedure:   ReadWriteCmosBank2
//
// Description: This function is used to access addresses in the CMOS
//              register range (0x80-0xff), for PEI and DXE boot phases.
//
// Input:       **PeiServices       - PEI Services table pointer
//                                    (NULL in DXE phase)
//              AccessType          - ReadType or WriteType to specify the
//                                    type of access
//              CmosRegister        - The CMOS register to access
//              *CmosParameterValue - Pointer to the data variable to be
//                                    accessed
//
// Output:      EFI_STATUS (return value) 
//                  EFI_SUCCESS - The access operation was successfull.
//                  Otherwise   - A valid EFI error code is returned.
//
// Modified:    None
//
// Referrals:   IoRead8, IoWrite8
//
// Notes:       This function is used when a translation from logical address
//              to index port value is required.
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS ReadWriteCmosBank2 (
    IN EFI_PEI_SERVICES         **PeiServices,  // NULL in DXE phase
    IN CMOS_ACCESS_TYPE         AccessType,
    IN UINT16                   CmosRegister,
    IN OUT UINT8                *CmosParameterValue )
{
    if ((CmosRegister < 0x80) || (CmosRegister > 0xff))
        return EFI_INVALID_PARAMETER;

    // Some chipsets require tranlation from the logical CMOS address to a
    // physical CMOS index port value. However, other chipsets do not require
    // a translation and the index/data port can be directly used for 
    // accessing the second bank.

    IoWrite8( CMOS_IO_EXT_INDEX, (UINT8)CmosRegister );

    if (AccessType == ReadType) {
        *CmosParameterValue = IoRead8( CMOS_IO_EXT_DATA );
    } else {
        IoWrite8( CMOS_IO_EXT_DATA, *CmosParameterValue );
    }

    return EFI_SUCCESS;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// 
// Procedure:   SbGetRtcPowerStatus
//
// Description: This function is checked CMOS battery is good or not.
//
// Input:       **PeiServices - PEI Services table pointer (NULL in DXE phase)
//
// Output:      BOOLEAN  
//                  TRUE  - The CMOS is battery is good.
//                  FALSE - The CMOS is battery is bad.
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

BOOLEAN SbGetRtcPowerStatus (
    IN EFI_PEI_SERVICES     **PeiServices )
{
    return (READ_PCI8_SB(SB_REG_GEN_PMCON_3) & 4) ? FALSE : TRUE; // 0xA4
}

#endif  // #if CMOS_MANAGER_SUPPORT
														//Improve alternate access mode >>
//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:   SwitchAlternateAccessMode
//
// Description: Enable or disable Alternate Access Mode.
//
// Input:       TRUE: Enable Alternate Access Mode
//              FALSE: Disable Alternate Access Mode
//
// Output:      None
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID SwitchAlternateAccessMode
(
  BOOLEAN Switch
)
{
  if (Switch) { 
    do { 
      // Enable Alternate Access Mode
      SET_MEM32_RCRB(R_PCH_RCRB_GCS, B_PCH_RCRB_GCS_AME);
    } while((READ_MEM32_RCRB(R_PCH_RCRB_GCS) & B_PCH_RCRB_GCS_AME) == 0);
  } else {
    do {
      // Disable Alternate Access Mode
      RESET_MEM32_RCRB(R_PCH_RCRB_GCS, B_PCH_RCRB_GCS_AME);
    } while(READ_MEM32_RCRB(R_PCH_RCRB_GCS) & B_PCH_RCRB_GCS_AME);
  }
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:   ReadPort70h
//
// Description: Read port 70h.
//
// Input:       None
//
// Output:      Data of port 70h.
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
UINT8 ReadPort70h ( VOID )
{
  UINT8  Port70h;

  SwitchAlternateAccessMode (TRUE);

  Port70h = IoRead8(RTC_INDEX_REG);

  SwitchAlternateAccessMode (FALSE);

  return Port70h;
}														//Improve alternate access mode <<

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   ReadCmos
//
// Description: This function reads one byte from CMOS register addressed by Index
//
// Input:       UINT8 Index
//
// Output:      UINT8 - read value
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
UINT8 ReadCmos(
    IN UINT8 Index
)
{
    // Read bit 7 (NMI setting).
    UINT8           NMI = 0;
    volatile UINT8  Value;
    BOOLEAN         IntState = CPULib_GetInterruptState();
    UINT8           RtcIndexPort;
    UINT8           RtcDataPort;

    CPULib_DisableInterrupt();

    if (Index < 0x80) {
      // Standard CMOS
      RtcIndexPort  = RTC_INDEX_REG;
      RtcDataPort   = RTC_DATA_REG;

      if (Index < 0x80)									          //Improve alternate access mode >>
      // Save current NMI_EN.
      NMI = ReadPort70h()  & RTC_NMI_MASK;				//Improve alternate access mode <<

    } else {
      // Upper CMOS
      RtcIndexPort  = CMOS_IO_EXT_INDEX;
      RtcDataPort   = CMOS_IO_EXT_DATA;
    }

    Index &= ~RTC_NMI_MASK;

    IoWrite8(RtcIndexPort, Index | NMI);
    Value = IoRead8(RtcDataPort); // Read register.

    if (IntState) CPULib_EnableInterrupt();

    return (UINT8)Value;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   WriteCmos
//
// Description: This function writes value to CMOS register addressed by Index
//
// Input:       UINT8 Index - CMOS register index
//              UINT8 Value - value to write
//
// Output:      None
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID WriteCmos(
    IN UINT8 Index, 
    IN UINT8 Value
)
{
    // Read bit 7 (NMI setting).
    UINT8   NMI = 0;
    BOOLEAN IntState = CPULib_GetInterruptState();
    UINT8   RtcIndexPort;
    UINT8   RtcDataPort;

    CPULib_DisableInterrupt();

    if (Index < 0x80) {
      // Standard CMOS
      RtcIndexPort  = RTC_INDEX_REG;
      RtcDataPort   = RTC_DATA_REG;

                                        //Improve alternate access mode >>
      // Save current NMI_EN.
      NMI = ReadPort70h()  & RTC_NMI_MASK;
                                        //Improve alternate access mode <<
    } else {
      // Upper CMOS
      RtcIndexPort  = CMOS_IO_EXT_INDEX;
      RtcDataPort   = CMOS_IO_EXT_DATA;
    }

    Index &= ~RTC_NMI_MASK; 

    IoWrite8(RtcIndexPort, Index | NMI);
    IoWrite8(RtcDataPort, Value); // Write Register.

    if (IntState) CPULib_EnableInterrupt();
}
//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:   SbLib_GetSmiState
//
// Description: This function returns SMI state
//              
// Input:       None
//
// Output:      TRUE - SMI enabled, FALSE - SMI disabled
//
// Note:        This function must work at runtime. Do not use boot time
//              services/protocols.
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

BOOLEAN SbLib_GetSmiState (VOID)
{
#if SMM_SUPPORT
    static BOOLEAN    OriginalSmiState = FALSE;
    static BOOLEAN    HadBeenCame = FALSE;
    volatile BOOLEAN  SmiState = (READ_IO32_PM(ACPI_IOREG_SMI_EN) & 1) ? \
                                                                 TRUE : FALSE;

    if (HadBeenCame && SmiState) HadBeenCame = FALSE;

    if (HadBeenCame) {
        SmiState = OriginalSmiState;
    } else {
        OriginalSmiState = SmiState;
        HadBeenCame = TRUE;
    }

    return SmiState;
#else
    return FALSE;
#endif
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:   SbLib_SmiDisable
//
// Description: This function disables SMI
//              
// Input:       None
//
// Output:      None
//
// Note:        This function should be used ONLY in critical parts of code.
//              This function must work at runtime. Do not use boot time
//              services/protocols 
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

VOID SbLib_SmiDisable (VOID)
{
#if SMM_SUPPORT
    RESET_IO32_PM(ACPI_IOREG_SMI_EN, 3); // 0x30
#endif
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:   SbLib_SmiEnable
//
// Description: This function enables SMI
//              
// Input:       None
//
// Output:      None
//
// Note:        This function should be used ONLY in critical parts of code.
//              This function must work at runtime. Do not use boot time
//              services/protocols 
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

VOID SbLib_SmiEnable (VOID)
{

#if SMM_SUPPORT
    SET_IO32_PM(ACPI_IOREG_SMI_EN, 2); // 0x30
    SET_IO32_PM(ACPI_IOREG_SMI_EN, 1); // 0x30
#endif
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:   CspLibCheckPowerLoss
//
// Description: This function is PM Specific function to check and Report to
//              the System Status Code - CMOS Battary and Power Supply Power 
//              loss/failure. Also it responcibe of clearing PM Power Loss
//              Statuses
//
// Input:       None
//
// Output:      None
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID CspLibCheckPowerLoss (VOID)
{

}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:   SbLib_SetLpcDeviceDecoding
//
// Description: This function sets LPC Bridge Device Decoding
//              
// Input:       *LpcPciIo - Pointer to LPC PCI IO Protocol
//              Base      - I/O base address, if Base is 0 means disabled the
//                          decode of the device 
//              DevUid    - The device Unique ID
//              Type      - Device Type, please refer to AMISIO.h
//
// Output:      EFI_STATUS
//                  EFI_SUCCESS - Set successfully.
//                  EFI_UNSUPPORTED - There is not proper Device Decoding 
//                                    register for the device UID.
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS SbLib_SetLpcDeviceDecoding (
    IN EFI_PCI_IO_PROTOCOL      *LpcPciIo,
    IN UINT16                   Base,
    IN UINT8                    DevUid,
    IN SIO_DEV_TYPE             Type )
{
    EFI_STATUS              Status = EFI_UNSUPPORTED;

    // Porting Required
    UINT16                  ComRng[] = { 0x3f8, 0x2f8, 0x220, 0x228, \
                                         0x238, 0x2e8, 0x338, 0x3e8, 0};
    UINT16                  LptRange[] = { 0x378, 0x278, 0x3bc, 0};
    UINT16                  FpcRange[] = { 0x3f0, 0x370, 0};
    UINT16                  IoRangeMask16 = 0xffff;
    UINT16                  IoRangeSet16 = 0;
    UINT16                  IoEnMask16 = 0xffff;
    UINT16                  IoEnSet16 = 0;
    UINT8                   i;    

    switch (Type) {
        // FDC Address Range
        case (dsFDC) :
            if (Base == 0) IoEnMask16 &= ~BIT03;
            else {
                for (i = 0; (FpcRange[i] != 0) && (FpcRange[i] != Base); i++);
                if (FpcRange[i]) {
                    IoEnSet16 |= BIT03;
                    IoRangeMask16 &= ~BIT12;
                    IoRangeSet16 |= (i << 12);
                }
                else return EFI_UNSUPPORTED;
            }
            break;

        // LPT Address Range
        case (dsLPT) :
            if (Base == 0) IoEnMask16 &= ~BIT02;
            else {
                for (i = 0; (LptRange[i] != 0) && (LptRange[i] != Base); i++);
                if (LptRange[i]) {
                    IoEnSet16 |= BIT02;
                    IoRangeMask16 &= ~(BIT09 | BIT08);
                    IoRangeSet16 |= (i << 8);
                } else return EFI_UNSUPPORTED;
            }
            break;

        // COM x Address Range
        case (dsUART) :
            if (Base == 0) {
                switch (DevUid) {
                    case 0 :
                            IoEnMask16 &= ~BIT00;
                            break;
                    case 1 :
                            IoEnMask16 &= ~BIT01;
                            break;
                    case 2 :
                            break;
                    case 3 :
                            break;
                    default:
                            break;
                }
            } else {
                if (DevUid < 2) {
                    for (i = 0; (ComRng[i] != 0) && (ComRng[i] != Base); i++);
                    if (ComRng[i]) {
                        if (DevUid) {
                            IoEnSet16 |= BIT01;
                            IoRangeMask16 &= ~(BIT06 | BIT05 | BIT04);
                            IoRangeSet16 |= (i << 4);
                        } else {
                            IoEnSet16 |= BIT00;
                            IoRangeMask16 &= ~(BIT02 | BIT01 | BIT00);
                            IoRangeSet16 |= i;
                        }
                    } else return EFI_UNSUPPORTED;
                } else {
                        SbLib_SetLpcGenericDecoding( LpcPciIo, \
                                                     Base , \
                                                     8, \
                                                     TRUE );
                }
            }
            break;

        // KBC Address Enable
        case (dsPS2K) :
        case (dsPS2M) :
        case (dsPS2CK) :
        case (dsPS2CM) :
            if (Base == 0) IoEnMask16 &= ~BIT10;
            else IoEnSet16 |= BIT10;
            break;

        // Game Port Address Enable
        case (dsGAME) :
            if (Base == 0) IoEnMask16 &= ~(BIT09 | BIT08);
            else {
                if (Base == 0x200) {
                    IoEnSet16 |= BIT08;
                } else {
                    if (Base == 0x208) IoEnSet16 |= BIT09;
                    else return EFI_UNSUPPORTED;
                }
            }
            break;

        // Other Address Enable
        case (0xff) :
            switch (Base) {
                case (0x2e) :
                    IoEnSet16 |= BIT12;
                    break;
                case (0x4e) :
                    IoEnSet16 |= BIT13;
                    break;
                case (0x62) :
                case (0x63) :
                case (0x64) :
                case (0x65) :
                case (0x66) :
                    IoEnSet16 |= BIT11;
                    break;
                case (0) :
                    return EFI_UNSUPPORTED;
                    break;
                default :
                    SbLib_SetLpcGenericDecoding( LpcPciIo, \
                                                 Base , \
                                                 4, \
                                                 TRUE );
                    break;
            }

//####            if (Base == 0x2e) IoEnSet16 |= BIT12;
//####            else {
//####                if (Base == 0x4e) IoEnSet16 |= BIT13;
//####                else {
//####                    if (Base) SbLib_SetLpcGenericDecoding( LpcPciIo, \
//####                                                           Base , \
//####                                                           4, \
//####                                                           TRUE );
//####                    else return EFI_UNSUPPORTED;
//####                }
//####            }

            break;

        default :
            return EFI_UNSUPPORTED;
    }

    RW_PCI16_SB(SB_REG_LPC_IO_DEC, IoRangeSet16, ~IoRangeMask16); // 0x80
    RW_PCI16_SB(SB_REG_LPC_EN, IoEnSet16, ~IoEnMask16); // 0x82
    // Porting End

    return EFI_SUCCESS;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:   SbLib_SetLpcGenericDecoding
//
// Description: This function sets LPC Bridge Generic Decoding
//              
// Input:       *LpcPciIo - Pointer to LPC PCI IO Protocol
//              Base      - I/O base address
//              Length    - I/O Length
//              Enabled   - Enable/Disable the generic decode range register
//
// Output:      EFI_STATUS
//                  EFI_SUCCESS - Set successfully.
//                  EFI_UNSUPPORTED - This function is not implemented or the
//                                    Length more than the maximum supported
//                                    size of generic range decoding.
//                  EFI_INVALID_PARAMETER - the Input parameter is invalid.
//                  EFI_OUT_OF_RESOURCES - There is not available Generic
//                                         Decoding Register.
//                  EFI_NOT_FOUND - the generic decode range will be disabled
//                                  is not found.
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS SbLib_SetLpcGenericDecoding (
    IN EFI_PCI_IO_PROTOCOL      *LpcPciIo,
    IN UINT16                   Base,
    IN UINT16                   Length,
    IN BOOLEAN                  Enable )
{
    // Porting Required
    UINT32                  IoGenDecode32;
    UINT16                  IoGenDecIndex;
    UINT16                  Buffer16;
    UINT8                   Bsf8 = 0;
    UINT8                   Bsr8 = 0;

    if (Length > 0x100) return EFI_UNSUPPORTED;

    if (Length == 0) return EFI_INVALID_PARAMETER;

    if (Length < 4) Length = 4;

    // Read I/O Generic Decodes Register.
    for (IoGenDecIndex = 0; IoGenDecIndex < 4; IoGenDecIndex++) {
        IoGenDecode32 = READ_PCI32_SB(SB_REG_GEN1_DEC + IoGenDecIndex * 4);
        if (Enable) {
            if ((IoGenDecode32 & 1) == 0) break;
        } else {
            if (((IoGenDecode32 & 0xfffc) == Base) && (IoGenDecode32 & 1)) {
                IoGenDecode32 = 0; // Disable & clear the base/mask fields
                break;
            }
        }
    }

    if (Enable) {
        if (IoGenDecIndex == 4) return EFI_OUT_OF_RESOURCES;

        Buffer16 = Length;
        while ((Buffer16 % 2) == 0) {
            Buffer16 /= 2;
            Bsf8++;
        }

        while (Length) {
            Length >>= 1;
            Bsr8++;
        }

        if (Bsf8 == (Bsr8 - 1)) Bsr8--;
    
        Length = (1 << Bsr8) - 1 ;

        Base &= (~Length);

        IoGenDecode32 = Base | (UINT32)((Length >> 2) << 18) | 1;

    } else {
        if (IoGenDecIndex == 4) return EFI_NOT_FOUND;
    }

    WRITE_PCI32_SB(SB_REG_GEN1_DEC + IoGenDecIndex * 4, IoGenDecode32);
    // Porting End

    return EFI_SUCCESS;

}

//---------------------------------------------------------------------------
#if SMM_SUPPORT
//---------------------------------------------------------------------------

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:   SBSmmSaveRestoreStates
//
// Description: This hook is called in the very SMI entry and exit.
//              Save/Restore chipset data if needed.
//
// Input:       Save - TRUE = Save / FALSE = Restore
//
// Output:      EFI_SUCCESS
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS SBSmmSaveRestoreStates (
    IN BOOLEAN                      Save )
{
    static volatile UINT8   StoreCMOS;
    static volatile UINT8   StoreExtCMOS;
    static volatile UINT32  StoreCF8;
    static volatile UINT32  AltAcc;
    static volatile UINT8   RtcRegA;
    UINT8 SbCmosMiscFlag = 0;
#if defined(HPET_APIC_INTERRUPT_MODE) && (HPET_APIC_INTERRUPT_MODE != 0)
    static volatile BOOLEAN IsHpetApicEn = FALSE;
    static volatile UINT8   StoreIoApicIndex;
    volatile UINT8  Irq;
#endif
    UINT32 Data32 =0;

    if (Save) {
        StoreCF8 = IoRead32(0xcf8);    // Store CF8 (PCI index)

        // Save Alternate access bit.
        AltAcc = READ_MEM32_RCRB(RCRB_MMIO_GCS) & 0x10;

        StoreCMOS = ReadPort70h(); // Save 0x70

        StoreExtCMOS = IoRead8(CMOS_IO_EXT_INDEX);  // Save 0x72
 
#if defined CMOS_MANAGER_SUPPORT && CMOS_MANAGER_SUPPORT
        IoWrite8(CMOS_IO_EXT_INDEX, SB_CMOS_MISC_FLAG_REG);
        IoWrite8(CMOS_IO_EXT_DATA, 0);
#endif
#if defined(HPET_APIC_INTERRUPT_MODE) && (HPET_APIC_INTERRUPT_MODE != 0)
        StoreIoApicIndex = MMIO_READ8(APCB);
        IsHpetApicEn = IsHpetApicEnable();
        if (IsHpetApicEn) {
        	Irq = GetHpetApicPin();
        	IoApicMaskIrq(Irq);
        }
#endif

        Data32 = MmioRead32 ((UINTN) (0xFED30880)) | (UINT32) (BIT0);
        WriteMsr(0x1FE, Data32);

    } else {
        do {
            RtcRegA = SBLib_CmosRead(RTC_REG_A_INDEX);
        } while (RtcRegA & 0x80);

#if defined CMOS_MANAGER_SUPPORT && CMOS_MANAGER_SUPPORT
        IoWrite8(CMOS_IO_EXT_INDEX, SB_CMOS_MISC_FLAG_REG);
        SbCmosMiscFlag = IoRead8(CMOS_IO_EXT_DATA);

        if (SbCmosMiscFlag & ENABLE_NMI_BEFORE_SMI_EXIT)
          StoreCMOS &= ~BIT07;          // Enable NMI_EN

        if (SbCmosMiscFlag & DISABLE_NMI_BEFORE_SMI_EXIT)
          StoreCMOS |= BIT07;           // Disable NMI_EN
#endif

        IoWrite8(CMOS_ADDR_PORT, StoreCMOS);       // Restore 0x70
        IoWrite8(CMOS_IO_EXT_INDEX, StoreExtCMOS); // Restore 0x72

        // Restore Alternate access bit.
        do {																//Improve alternate access mode >>
          RW_MEM32_RCRB(RCRB_MMIO_GCS, AltAcc, 0x10);
        } while ((READ_MEM32_RCRB(RCRB_MMIO_GCS) & 0x10) != AltAcc);		//Improve alternate access mode <<

        IoWrite32(0xcf8, StoreCF8);    // Restore 0xCF8 (PCI index)

#if defined(HPET_APIC_INTERRUPT_MODE) && (HPET_APIC_INTERRUPT_MODE != 0)
        if (IsHpetApicEn) {
        	Irq = GetHpetApicPin();
        	IoApicUnmaskIrq(Irq);
        	IoApicEoi(Irq);
        }

        MMIO_WRITE8(APCB, StoreIoApicIndex);
        StoreIoApicIndex = MMIO_READ8(APCB);
#endif

        Data32 = MmioRead32 ((UINTN) (0xFED30880)) & (UINT32) (~BIT0);
        WriteMsr(0x1FE, Data32);

    }

    return EFI_SUCCESS;
}

//---------------------------------------------------------------------------
#endif  // END OF SMM Related Porting Hooks
//---------------------------------------------------------------------------

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:   SBProtectedPciDevice
//
// Description: This function is called by PCI Bus Driver before configuring
//              or disabling any PCI device. This function should examine the
//              Vendor/Device ID or PCI Bus, Device and Function numbers to
//              make sure it is not a south bridge device or any other device
//              which should no be configured by PCI Bus Driver.
//
// Input:       *PciDevice - Pointer to PCI Device Info structure.
//
// Output:      EFI_STATUS
//                  EFI_SUCCESS     - SKIP this device, do not touch
//                                    PCI Command register.
//                  EFI_UNSUPPORTED - DON'T SKIP this device do complete
//                                    enumeration as usual.
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS SBProtectedPciDevice (
    IN PCI_DEV_INFO             *PciDevice )
{

//####if ((PciDevice->Address.Addr.Bus == SMBUS_BUS) && \
//####    (PciDevice->Address.Addr.Device == SMBUS_DEV) && \
//####    (PciDevice->Address.Addr.Function == SMBUS_FUN)) {
//####
//####    return EFI_SUCCESS;
//####}

    return EFI_UNSUPPORTED;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:   SBProgramPciDevice
//
// Description: This function is called by PCI Bus Driver before installing
//              Protocol Interface for the input device.
//
// Input:       *PciDevice - Pointer to PCI Device Info structure.
//
// Output:      EFI_SUCCESS
//
// Notes:       All resource in the device had been assigned, but the command
//              register is disabled.
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS SBProgramPciDevice (
    IN PCI_DEV_INFO             *PciDevice )
{

//####if ((PciDevice->Address.Addr.Bus == EUSB_BUS) && \
//####    (PciDevice->Address.Addr.Device == EUSB_DEV) && \
//####    (PciDevice->Address.Addr.Function == EUSB_FUN)) {
//####    // Do any porting if needed.
//####}

    return EFI_SUCCESS;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:   SBUpdatePciDeviceAttributes
//
// Description: This function is called by PCI Bus Driver, can be used to
//              the attributes of the PCI device.
//
// Input:       *PciDevice   - Pointer to PCI Device Info structure.
//              *Attributes  - Attributes bitmask which caller whants to
//                             change.
//              Capabilities - The PCI device supports Capabilityes
//              Set          - Specifies weathere to set or reset given
//                             "Attributes".
//
// Output:      EFI_SUCCESS
//
// Notes:       This routine may be invoked twice depend on the device type,
//              the first time is at BDS phase, the second is before
//              legacy boot.
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS SBUpdatePciDeviceAttributes (
    IN PCI_DEV_INFO             *PciDevice,
    IN OUT UINT64               *Attributes,
    IN UINT64                   Capabilities,
    IN BOOLEAN                  Set )
{

//####if ((PciDevice->Address.Addr.Bus == EUSB_BUS) && \
//####    (PciDevice->Address.Addr.Device == EUSB_DEV) && \
//####    (PciDevice->Address.Addr.Function == EUSB_FUN)) {
//####    // Do any porting if needed.
//####}

    return EFI_SUCCESS;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure: ReadSPIDescriptor
//
// Description: Read SPI Descriptor.
//
// Input: FDSS -  Flash Descriptor Section Select.
//        FDSI -  Flash Descriptor Section Index.
//        FDOD -  Flash Descriptor Observability Data
//
// Output:EFI_SUCCESS
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS ReadSPIDescriptor(
    IN UINT8 FDSS,
    IN UINT8 FDSI,
    OUT UINT32 *FDOD
)
{
    UINT32 Buffer32;

    WRITE_MEM32_SPI(R_RCRB_SPI_FDOC, 0);
    
    Buffer32 = READ_MEM32_SPI(R_RCRB_SPI_FDOD);

    if (Buffer32 != 0x0ff0a55a)						//Improve alternate access mode 
        return EFI_NOT_FOUND;

    Buffer32 = ((UINT32)FDSS << 12) | ((UINT32)FDSI << 2);
    WRITE_MEM32_SPI(R_RCRB_SPI_FDOC, Buffer32);
    *FDOD = READ_MEM32_SPI(R_RCRB_SPI_FDOD);

    return EFI_SUCCESS;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure: GetTotalFlashRomSize
//
// Description: Read SPI Descriptor to get Total Flash size.
//
// Input: None
//
// Output: UINT32 - Flash Rom Size
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
UINT32 GetTotalFlashRomSize ( VOID )
{
    UINT32  TotalRomSize = 0;
    UINT32  CtrlData;
    UINT8   NumSpi = 0;
    
    // Select to Flash Map 0 Register to get the number of flash Component
    CtrlData = MmioRead32((SB_RCRB_BASE_ADDRESS + SPI_BASE_ADDRESS + R_RCRB_SPI_FDOC));
    CtrlData &= (UINT32)(~(B_PCH_SPI_FDOC_FDSS_MASK | B_PCH_SPI_FDOC_FDSI_MASK));
    CtrlData |= (UINT32)(V_PCH_SPI_FDOC_FDSS_FSDM | R_PCH_SPI_FDBAR_FLASH_MAP0);
    MmioWrite32((SB_RCRB_BASE_ADDRESS + SPI_BASE_ADDRESS + R_RCRB_SPI_FDOC), CtrlData);

    switch ( MmioRead16 (SB_RCBA + R_PCH_SPI_FDOD) & B_PCH_SPI_FDBAR_NC ) {
        case V_PCH_SPI_FDBAR_NC_1:
            NumSpi = 1;
            break;
        case V_PCH_SPI_FDBAR_NC_2:
            NumSpi = 2;
            break;
        default:
            break;
    }
    //if (NumSpi == 0) ASSERT_EFI_ERROR(EFI_DEVICE_ERROR);

    // Select to Flash Components Register to get the Component 1 Density
    CtrlData = MmioRead32((SB_RCRB_BASE_ADDRESS + SPI_BASE_ADDRESS + R_RCRB_SPI_FDOC));
    CtrlData &= (UINT32)(~(B_PCH_SPI_FDOC_FDSS_MASK | B_PCH_SPI_FDOC_FDSI_MASK));
    CtrlData |= (UINT32)(V_PCH_SPI_FDOC_FDSS_COMP | R_PCH_SPI_FCBA_FLCOMP);
    MmioWrite32((SB_RCRB_BASE_ADDRESS + SPI_BASE_ADDRESS + R_RCRB_SPI_FDOC), CtrlData);

    /// Copy Component 1 Density
    switch ( (UINT8) MmioRead32 (SB_RCRB_BASE_ADDRESS + SPI_BASE_ADDRESS + R_RCRB_SPI_FDOD) & B_PCH_SPI_FLCOMP_COMP1_MASK ) {
        case V_PCH_SPI_FLCOMP_COMP1_512KB:
            TotalRomSize += (UINT32) (512 << KBShift);
            break;
        case V_PCH_SPI_FLCOMP_COMP1_1MB:
            TotalRomSize += (UINT32) (1 << MBShift);
            break;
        case V_PCH_SPI_FLCOMP_COMP1_2MB:
            TotalRomSize += (UINT32) (2 << MBShift);
            break;
        case V_PCH_SPI_FLCOMP_COMP1_4MB:
            TotalRomSize += (UINT32) (4 << MBShift);
            break;
        case V_PCH_SPI_FLCOMP_COMP1_8MB:
            TotalRomSize += (UINT32) (8 << MBShift);
            break;
        case V_PCH_SPI_FLCOMP_COMP1_16MB:
            TotalRomSize += (UINT32) (16 << MBShift);
            break;
        case V_PCH_SPI_FLCOMP_COMP1_32MB:
            TotalRomSize += (UINT32) (32 << MBShift);
            break;
        case V_PCH_SPI_FLCOMP_COMP1_64MB:
            TotalRomSize += (UINT32) (64 << MBShift);
            break;
        default:
            break;
    } // end of switch

    // Copy Component 2 Density
    if(NumSpi == 2){
        switch ( (UINT8) MmioRead32 (SB_RCRB_BASE_ADDRESS + SPI_BASE_ADDRESS + R_RCRB_SPI_FDOD) & B_PCH_SPI_FLCOMP_COMP2_MASK ) {
            case V_PCH_SPI_FLCOMP_COMP2_512KB:
                TotalRomSize += (UINT32) (512 << KBShift);
                break;
            case V_PCH_SPI_FLCOMP_COMP2_1MB:
                TotalRomSize += (UINT32) (1 << MBShift);
                break;
            case V_PCH_SPI_FLCOMP_COMP2_2MB:
                TotalRomSize += (UINT32) (2 << MBShift);
                break;
            case V_PCH_SPI_FLCOMP_COMP2_4MB:
                TotalRomSize += (UINT32) (4 << MBShift);
                break;
            case V_PCH_SPI_FLCOMP_COMP2_8MB:
                TotalRomSize += (UINT32) (8 << MBShift);
                break;
            case V_PCH_SPI_FLCOMP_COMP2_16MB:
                TotalRomSize += (UINT32) (16 << MBShift);
                break;
            case V_PCH_SPI_FLCOMP_COMP2_32MB:
                TotalRomSize += (UINT32) (32 << MBShift);
                break;
            case V_PCH_SPI_FLCOMP_COMP2_64MB:
                TotalRomSize += (UINT32) (64 << MBShift);
                break;
            default:
                break;
        } // end of switch
    }// end of if
    //if (TotalRomSize == 0) ASSERT_EFI_ERROR(EFI_DEVICE_ERROR);

    return TotalRomSize;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure: SbGetSpiRegionAddresses
//
// Description: Read SPI Descriptor to get flash rom base address and length  
//              of one region
//
// Input:  AMI_SB_SPI_RANGE_TYPE - Region Type
//
// Output: UINT32 - BaseAddress
//         UINT32 - EndAddress
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS SbGetSpiRangeAddresses(
    IN   AMI_SB_SPI_RANGE_TYPE    RangeType,
    OUT  UINT32                   *BaseAddress,
    OUT  UINT32                   *EndAddress )
{
  UINT32                ReadValue = 0;

  if (!((RangeType > AnyType) && (RangeType < PchSpiRangeTypeMax))) {
    return EFI_INVALID_PARAMETER;
  }
 
  if (RangeType <= SecondaryBiosType) {
    ReadValue = MmioRead32 (SB_RCRB_BASE_ADDRESS + SPI_BASE_ADDRESS + R_SB_RCRB_SPI_FREG0_FLASHD + (S_SB_SPI_FREGX * ((UINTN) (RangeType - 1))));
    *BaseAddress = (ReadValue & B_SB_SPI_FREGX_BASE_MASK) << 12;
    *EndAddress  = ((ReadValue & B_SB_SPI_FREGX_LIMIT_MASK) >> 4) | 0x00000FFF;
  } else if (RangeType == BfpregType) {
    ReadValue = MmioRead32 (SB_RCRB_BASE_ADDRESS + SPI_BASE_ADDRESS + R_SB_RCRB_SPI_BFPR);
    *BaseAddress = (ReadValue & B_SB_SPI_BFPR_PRB) << 12;
    *EndAddress  = ((ReadValue & B_SB_SPI_BFPR_PRL) >> 4) | 0x00000FFF;
  }

  return EFI_SUCCESS;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:   SbFlashProtectedRegion
//
// Description: This routine provides H/W read/write-protection of the BIOS
//              region. If chipset supports "SPI Flash Protected Range
//              registers", then program them to protect BIOS region in SPI
//              Flash.
//
// Input:       None
//
// Output:      EFI_STATUS
//                  EFI_SUCCESS - Set successfully.
//                  EFI_OUT_OF_RESOURCES - There is no available register
//                                         for this call.
//                  EFI_INVALID_PARAMETER - The parameter of input is
//                                          invalid
//                  EFI_UNSUPPORTED - Chipset or H/W is not supported.
//
// Notes:       Porting required
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS SbFlashProtectedRange( VOID )
{
    //
    // Porting required if chipset is able to support H/W protection of
    // BIOS region.
    //
    EFI_STATUS      Status = EFI_SUCCESS;
    UINT32          RegIndex;
    UINT32          TotalFlashRomSize;
    UINT32          FlashRangeBaseAddr = 0;
    UINT32          FlashRangeEndAddr  = 0;
    volatile UINT32 Value32, AddrCheck;
    SPI_PROTECTED_RANGE_CONIFG SpiProtectedRange[] = {SPI_PROTECTED_RANGE_0,
                                                      SPI_PROTECTED_RANGE_1,
                                                      SPI_PROTECTED_RANGE_2,
                                                      SPI_PROTECTED_RANGE_3,
                                                      SPI_PROTECTED_RANGE_4};
    
    // Get Total ROM size first
    TotalFlashRomSize = GetTotalFlashRomSize();
    
    for (RegIndex = 0; RegIndex < 5; RegIndex++) {
        // Check Read or Write protected is enable or not
        if (!(SpiProtectedRange[RegIndex].ReadProtectEnable || \
              SpiProtectedRange[RegIndex].WriteProtectEnable))
            continue;

        // Check Protected Range Length should not be 0
        if(SpiProtectedRange[RegIndex].ProtectedRangeLength == 0)
            continue;

        switch (SpiProtectedRange[RegIndex].ProtectedRangeType){
            case BiosType:
            case MeType:
            case GbeType:
                Status = SbGetSpiRangeAddresses(SpiProtectedRange[RegIndex].ProtectedRangeType, &FlashRangeBaseAddr, &FlashRangeEndAddr);
                if(!EFI_ERROR(Status)){
                    AddrCheck = (UINT32)(SpiProtectedRange[RegIndex].ProtectedRangeBase) + FlashRangeBaseAddr;
                    if (AddrCheck > FlashRangeEndAddr)
                        return EFI_INVALID_PARAMETER;
                    AddrCheck += (UINT32)(SpiProtectedRange[RegIndex].ProtectedRangeLength - 1);
                    if (AddrCheck > FlashRangeEndAddr)
                        return EFI_INVALID_PARAMETER;
                    
                    Value32 = *(UINT32 *)(SB_RCBA + SPI_BASE_ADDRESS + (R_SB_RCRB_SPI_PR0 + (RegIndex * 4)));
                    Value32 =  (((UINT32)(SpiProtectedRange[RegIndex].ProtectedRangeBase) + FlashRangeBaseAddr) & 0x1FFF000) >> 12;
                    Value32 |= ((((UINT32)(SpiProtectedRange[RegIndex].ProtectedRangeBase + SpiProtectedRange[RegIndex].ProtectedRangeLength - 1) + FlashRangeBaseAddr) & 0x1FFF000) << 4);
                } else return Status;

                break;
            case AnyType:
                // Exceed the address of protected range base.
                if (SpiProtectedRange[RegIndex].ProtectedRangeBase >= (UINTN)TotalFlashRomSize)
                    return EFI_INVALID_PARAMETER;

                Value32 = *(UINT32 *)(SB_RCBA + SPI_BASE_ADDRESS + (R_SB_RCRB_SPI_PR0 + (RegIndex * 4)));
                Value32 = (UINT32)(SpiProtectedRange[RegIndex].ProtectedRangeBase & 0x1FFF000) >> 12;
                Value32 |= (((UINT32)(SpiProtectedRange[RegIndex].ProtectedRangeBase + SpiProtectedRange[RegIndex].ProtectedRangeLength - 1) & 0x1FFF000) << 4);
                break;
        } // end of switch

        if (SpiProtectedRange[RegIndex].ReadProtectEnable) Value32 |= B_SB_SPI_PRx_RPE;
        if (SpiProtectedRange[RegIndex].WriteProtectEnable) Value32 |= B_SB_SPI_PRx_WPE;        
        *(UINT32 *)(SB_RCBA + SPI_BASE_ADDRESS + (R_SB_RCRB_SPI_PR0 + (RegIndex * 4))) = Value32;
    } // for loop

    return Status;
}

//---------------------------------------------------------------------------
// Standard I/O Access Routines, No Porting Required.
//---------------------------------------------------------------------------

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:   RtcRead 
//
// Description: Read specific RTC/CMOS RAM
//
// Input:       Location        Point to RTC/CMOS RAM offset for read
//
// Output:      nONE
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
UINT8 RtcRead ( IN UINT8 Location )
{
  return ReadCmos(Location);
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:   RtcWrite
//
// Description: Write specific RTC/CMOS RAM
//
// Parameters:  Location        Point to RTC/CMOS RAM offset for write
//              Value           The data that will be written to RTC/CMOS RAM
//
// Returns:     None
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID
RtcWrite (
  IN      UINT8        Location,
  IN      UINT8        Value
  )
{
  WriteCmos(Location, Value);
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:   ReadIo8IdxData
//
// Description: This function reads an 8bit value from a specific I/O
//              Index/Data port.
//
// Input:       IoBase16 - A 16 Bit I/O Address for Index I/O Port 
//              RegIdx8  - An 8 Bit Register offset
//
// Output:      An 8Bit data read from the specific Index/Data I/O port.
//
// Notes:       The default Data I/O Port is the Index I/O Port plus 1, if
//              your Data I/O Port is not that, please modify below 
//              "++IoBase16".
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

UINT8 ReadIo8IdxData (
    IN UINT16           IoBase16,
    IN UINT8            RegIdx8 )
{
    IoWrite8( IoBase16, RegIdx8 );
    return IoRead8( ++IoBase16 );
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:   WriteIo8IdxData
//
// Description: This function writes an 8bit value to a specific I/O
//              Index/Data port.
//
// Input:       IoBase16 - A 16 Bit I/O Address for Index I/O Port 
//              RegIdx8  - An 8 Bit Register Index
//              Value8   - An 8 Bit Value to write.
//
// Output:      None
//
// Notes:       The default Data I/O Port is the Index I/O Port plus 1, if
//              your Data I/O Port is not that, please modify below 
//              "++IoBase16".
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

VOID WriteIo8IdxData (
    IN UINT16       IoBase16,
    IN UINT8        RegIdx8,
    IN UINT8        Value8 )
{
    IoWrite8( IoBase16, RegIdx8 );
    IoWrite8( ++IoBase16, Value8 );
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:   RwIo8IdxData
//
// Description: This function reads an 8bit value from a specific I/O
//              Index/Data port, then applies Set/Reset masks and writes
//              it back. 
//
// Input:       IoBase16  - A 16 Bit I/O Address for Index I/O Port 
//              RegIdx8   - An 8 Bit Register Index
//              SetBit8   - Mask of 8bits to set (1 = Set)
//              ResetBit8 - Mask of 8bits to reset (1 = Reset)
//
// Output:      None
//
// Notes:       The default Data I/O Port is the Index I/O Port plus 1, if
//              your Data I/O Port is not that, please modify IoRead8IdxData 
//              and IoWrite8IdxData's "++IoBase16".
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

VOID RwIo8IdxData (
    IN UINT16       IoBase16,
    IN UINT8        RegIdx8,
    IN UINT8        SetBit8,
    IN UINT8        ResetBit8 )
{
    UINT8           Buffer8 ;

    Buffer8 = ReadIo8IdxData( IoBase16, RegIdx8 ) & ~ResetBit8 | SetBit8;
    WriteIo8IdxData( IoBase16, RegIdx8, Buffer8 );
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:   WriteIo8S3
//
// Description: This function writes an 8bit value to a specific I/O port
//              and writes a copy to Boot Script Table.
//
// Input:       *mBootScriptSave - Pointer to Boot Script Save Protocal
//              IoBaseReg16      - A 16 Bit I/O Port Address
//              Value8           - An 8 Bit Value to write.
//
// Output:      None
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

VOID WriteIo8S3 (
    IN AMI_S3_SAVE_PROTOCOL             *mBootScriptSave,
    IN UINT16                           IoBaseReg16,
    IN UINT8                            Value8 )
{
    IoWrite8( IoBaseReg16, Value8 );

    BOOT_SCRIPT_S3_IO_WRITE_MACRO( mBootScriptSave, \
                                   EfiBootScriptWidthUint8, \
                                   IoBaseReg16, \
                                   1, \
                                   &Value8 );
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:   WriteIo16S3
//
// Description: This function writes a 16bit value to a specific I/O port
//              and writes a copy to Boot Script Table.
//
// Input:       *mBootScriptSave - Pointer to Boot Script Save Protocal
//              IoBaseReg16      - A 16 Bit I/O Port Address
//              Value16          - A 16 Bit Value to write.
//
// Output:      None
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

VOID WriteIo16S3 (
    IN AMI_S3_SAVE_PROTOCOL             *mBootScriptSave,
    IN UINT16                           IoBaseReg16,
    IN UINT16                           Value16 )
{
    IoWrite16( IoBaseReg16, Value16 );

    BOOT_SCRIPT_S3_IO_WRITE_MACRO( mBootScriptSave, \
                                   EfiBootScriptWidthUint16,\
                                   IoBaseReg16, \
                                   1, \
                                   &Value16 );
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:   WriteIo32S3
//
// Description: This function writes a 32bit value to a specific I/O port
//              and writes a copy to Boot Script Table.
//
// Input:       *mBootScriptSave - Pointer to Boot Script Save Protocal
//              IoBaseReg16      - A 16 Bit I/O Port Address
//              Value32          - a 32 Bit Value to write.
//
// Output:      None
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

VOID WriteIo32S3 (
    IN AMI_S3_SAVE_PROTOCOL             *mBootScriptSave,
    IN UINT16                           IoBaseReg16,
    IN UINT32                           Value32 )
{
    IoWrite32( IoBaseReg16, Value32 );

    BOOT_SCRIPT_S3_IO_WRITE_MACRO( mBootScriptSave, \
                                   EfiBootScriptWidthUint32,\
                                   IoBaseReg16, \
                                   1, \
                                   &Value32 );
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:   RwIo8S3
//
// Description: This function reads an 8bit value from a specific I/O port, 
//              then applies Set/Reset masks, and writes it back, then
//              writes a copy to Boot Script Table.
//
// Input:       *mBootScriptSave - Pointer to Boot Script Save Protocal
//              IoBaseReg16      - A 16 Bit I/O Port Address
//              SetBit8          - Mask of 8bits to set (1 = Set)
//              ResetBit8        - Mask of 8bits to reset (1 = Reset)
//
// Output:      None
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

VOID RwIo8S3 (
    IN AMI_S3_SAVE_PROTOCOL             *mBootScriptSave,
    IN UINT16                           IoBaseReg16,
    IN UINT8                            SetBit8,
    IN UINT8                            ResetBit8 )
{   

    RW_IO8( IoBaseReg16, SetBit8, ResetBit8 );

    ResetBit8 = ~ResetBit8;

    BOOT_SCRIPT_S3_IO_READ_WRITE_MACRO( mBootScriptSave, \
                                        EfiBootScriptWidthUint8, \
                                        IoBaseReg16, \
                                        &SetBit8, \
                                        &ResetBit8 );
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:   RwIo16S3
//
// Description: This function reads a 16bit value from a specific I/O port, 
//              then applies Set/Reset masks, and writes it back, then
//              writes a copy to Boot Script Table.
//
// Input:       *mBootScriptSave - Pointer to Boot Script Save Protocal
//              IoBaseReg16      - A 16 Bit I/O Port Address
//              SetBit16         - Mask of 16bits to set (1 = Set)
//              ResetBit16       - Mask of 16bits to reset (1 = Reset)
//
// Output:      None
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

VOID RwIo16S3 (
    IN AMI_S3_SAVE_PROTOCOL             *mBootScriptSave,
    IN UINT16                           IoBaseReg16,
    IN UINT16                           SetBit16,
    IN UINT16                           ResetBit16 )
{   
    RW_IO16( IoBaseReg16, SetBit16, ResetBit16 );

    ResetBit16 = ~ResetBit16;

    BOOT_SCRIPT_S3_IO_READ_WRITE_MACRO( mBootScriptSave, \
                                        EfiBootScriptWidthUint16, \
                                        IoBaseReg16, \
                                        &SetBit16, \
                                        &ResetBit16 );
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:   RwIo32S3
//
// Description: This function reads a 32bit value from a specific I/O port, 
//              then applies Set/Reset masks, and writes it back, then
//              writes a copy to Boot Script Table.
//
// Input:       *mBootScriptSave - Pointer to Boot Script Save Protocal
//              IoBaseReg16      - A 16 Bit I/O Port Address
//              SetBit32         - Mask of 32bits to set (1 = Set)
//              ResetBit32       - Mask of 32bits to reset (1 = Reset)
//
// Output:      None
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

VOID RwIo32S3 (
    IN AMI_S3_SAVE_PROTOCOL             *mBootScriptSave,
    IN UINT16                           IoBaseReg16,
    IN UINT32                           SetBit32,
    IN UINT32                           ResetBit32 )
{   
    RW_IO32( IoBaseReg16, SetBit32, ResetBit32 );

    ResetBit32 = ~ResetBit32;

    BOOT_SCRIPT_S3_IO_READ_WRITE_MACRO( mBootScriptSave, \
                                        EfiBootScriptWidthUint32, \
                                        IoBaseReg16, \
                                        &SetBit32, \
                                        &ResetBit32 );
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:   WriteIo8IdxDataS3
//
// Description: This function writes an 8bit value to a specific I/O
//              Index/Data ports and writes a copy to Boot Script Table.
//
// Input:       *mBootScriptSave - Pointer to Boot Script Save Protocal
//              IoBase16         - A 16 Bit I/O Address for Index I/O Port 
//              RegIdx8          - An 8 Bit Register Index
//              Value8           - An 8 Bit Value to write.
//
// Output:      None
//
// Notes:       The default Data I/O Port is the Index I/O Port plus 1, if
//              your Data I/O Port is not that, please modify below 
//              "IoBase16+1".
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

VOID WriteIo8IdxDataS3 (
    IN AMI_S3_SAVE_PROTOCOL             *mBootScriptSave,
    IN UINT16                           IoBase16,
    IN UINT8                            IoReg8,
    IN UINT8                            Value8 )
{
    WriteIo8S3(mBootScriptSave, IoBase16, IoReg8);
    WriteIo8S3(mBootScriptSave, IoBase16 + 1, Value8);
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:   RwIo8IdxDataS3
//
// Description: This function reads an 8bit value from a specific I/O
//              Index/Data ports, then applies Set/Reset masks, and writes
//              it back. Also writes a copy to Boot Script Table.
//
// Input:       *mBootScriptSave - Pointer to Boot Script Save Protocal
//              IoBase16         - A 16 Bit I/O Address for Index I/O Port 
//              RegIdx8          - An 8 Bit Register Index
//              SetBit8          - Mask of 8bits to set (1 = Set)
//              ResetBit8        - Mask of 8bits to reset (1 = Reset)
//
// Output:      An 8Bit data read from the specific Index/Data I/O port
//              after appling Set/Reset masks. 
//
// Notes:       The default Data I/O Port is the Index I/O Port plus 1, if
//              your Data I/O Port is not that, please modify below 
//              "IoBase16+1" and IoWrite8IdxData's "++IoBase16".
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

VOID RwIo8IdxDataS3 (
    IN AMI_S3_SAVE_PROTOCOL             *mBootScriptSave,
    IN UINT16                           IoBase16,
    IN UINT8                            IoReg8,
    IN UINT8                            SetBit8,
    IN UINT8                            ResetBit8 )
{
    RwIo8IdxData(IoBase16, IoReg8, SetBit8, ResetBit8);

    BOOT_SCRIPT_S3_IO_WRITE_MACRO( mBootScriptSave, \
                                   EfiBootScriptWidthUint8,\
                                   IoBase16, \
                                   1, \
                                   &IoReg8 );
    ResetBit8 = ~ResetBit8;
    BOOT_SCRIPT_S3_IO_READ_WRITE_MACRO( mBootScriptSave, \
                                        EfiBootScriptWidthUint8, \
                                        IoBase16 + 1, \
                                        &SetBit8, \
                                        &ResetBit8 );
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:   SBLib_CmosRead
//
// Description: Read the RTC value at the given Index.
//
// Input:       Index - RTC Index
//
// Output:      RTC Value read from the provided Index
//
// Notes:       Here is the control flow of this function:
//              1. Read port 0x70 (RTC Index Register) to get bit 7.
//                 Bit 7 is the NMI bit-it should not be changed.
//              2. Set Index with the NMI bit setting.
//              3. Output 0x70 with the Index and NMI bit setting.
//              4. Read 0x71 for Data. Getting Dec when appropriate.
//              5. Return the Data.
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

UINT8 SBLib_CmosRead (
    IN UINT8        Index )
{
  return ReadCmos(Index);
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:   SBLib_CmosWrite
//
// Description: Write the RTC value at the given Index.
//
// Input:       Index - RTC Index
//              Value - Value to write
//
// Output:      None
//
// Notes:       Here is the control flow of this function:
//              1. Read port 0x70 (RTC Index Register) to get bit 7.
//                 Bit 7 is the NMI bit-it should not be changed.
//              2. Set Index with the NMI bit setting.
//              3. Output 0x70 with the Index. Switch to BCD when needed.
//              4. Write the data to 0x71.
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

VOID SBLib_CmosWrite (
    IN UINT8        Index,
    IN UINT8        Value )
{
  WriteCmos(Index, Value);
}

PCH_SERIES
EFIAPI
GetPchSeries (
  VOID
  )
/**

  Return Pch Series

  @param[in] None

  @retval PCH_SERIES            Pch Series

**/
{
  UINT16  LpcDeviceId;
  UINT32  PchSeries;

  LpcDeviceId = READ_PCI16_SB(R_PCH_LPC_DEVICE_ID);

  if (IS_PCH_LPTH_LPC_DEVICE_ID (LpcDeviceId)) {
    PchSeries = PchH;
  } else if (IS_PCH_LPTLP_LPC_DEVICE_ID (LpcDeviceId)) {
    PchSeries = PchLp;
  } else {
    PchSeries = PchUnknownSeries;
  }

  return PchSeries;
}

UINT8
EFIAPI
GetPchMaxPciePortNum (
  VOID
  )
/**

  Get Pch Maximum Pcie Root Port Number

  @param[in] None

  @retval Pch Maximum Pcie Root Port Number

**/
{
  PCH_SERIES  PchSeries;

  PchSeries = GetPchSeries();
  switch (PchSeries) {
    case PchLp:
      return LPTLP_PCIE_MAX_ROOT_PORTS;

    case PchH:
      return LPTH_PCIE_MAX_ROOT_PORTS;

    default:
      return 0;
  }
}

UINT8
EFIAPI
GetPchMaxSataPortNum (
  VOID
  )
/**

  Get Pch Maximum Sata Port Number

  @param[in] None

  @retval Pch Maximum Sata Port Number

**/
{
  PCH_SERIES  PchSeries;

  PchSeries = GetPchSeries();
  switch (PchSeries) {
    case PchLp:
      return LPTLP_AHCI_MAX_PORTS;

    case PchH:
      return LPTH_AHCI_MAX_PORTS;

    default:
      return 0;
  }
}

UINT8
EFIAPI
GetPchUsbMaxPhysicalPortNum (
  VOID
  )
/**

  Get Pch Usb Maximum Physical Port Number

  @param[in] None

  @retval Pch Usb Maximum Physical Port Number

**/
{
  PCH_SERIES  PchSeries;

  PchSeries = GetPchSeries();
  switch (PchSeries) {
    case PchLp:
      return LPTLP_USB_MAX_PHYSICAL_PORTS;

    case PchH:
      return LPTH_USB_MAX_PHYSICAL_PORTS;

    default:
      return 0;
  }
}

UINT8
EFIAPI
GetPchXhciMaxUsb3PortNum (
  VOID
  )
/**

  Get Pch Maximum Usb3 Port Number of XHCI Controller

  @param[in] None

  @retval Pch Maximum Usb3 Port Number of XHCI Controller

**/
{
  PCH_SERIES  PchSeries;

  PchSeries = GetPchSeries();
  switch (PchSeries) {
    case PchLp:
      return LPTLP_XHCI_MAX_USB3_PORTS;

    case PchH:
      return LPTH_XHCI_MAX_USB3_PORTS;

    default:
      return 0;
  }
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:   GetPchEhciMaxControllerNum
//
// Description: Get Pch Maximum EHCI Controller Number
//
// Input:       None
//
// Output:      Pch Maximum EHCI Controller Number
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
UINT8
EFIAPI
GetPchEhciMaxControllerNum (
  VOID
  )
{
  PCH_SERIES  PchSeries;

  PchSeries = GetPchSeries();
  switch (PchSeries) {
    case PchLp:
      return LPTLP_EHCI_MAX_CONTROLLERS;

    case PchH:
      return LPTH_EHCI_MAX_CONTROLLERS;

    default:
      return 0;
  }
}

UINT32 DummyVerbTable[] = {
  //                            
  // Dummy Verb Table
  //                           
  0xFFFFFFFF,
  0xFFFFFFFF,
  0xFFFFFFFF,
  0xFFFFFFFF
};

#if defined(HPET_APIC_INTERRUPT_MODE) && (HPET_APIC_INTERRUPT_MODE != 0)
//----------------------------------------------------------------------------
// Generic IO APIC routine.
//----------------------------------------------------------------------------
UINT8 gBspLocalApicID = 0;
//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:   IoApicBase
//
// Description: This routine returns a structure pointer to the I/O APIC.
//
// Input:       None
//
// Output:      IO_APIC structure.
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
struct IO_APIC* IoApicBase( VOID )
{
	static UINT32 IoApicAddr = 0;
	if (IoApicAddr == 0 || IoApicAddr == -1) {
        // This value may need to read from chipset registers.
		IoApicAddr = APCB;
	}

	return (struct IO_APIC*)IoApicAddr;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:   IoApicWrite
//
// Description: This function writes a 32bits data to the register of
//              I/O APIC.
//
// Input:       UINT8  Reg - The register offset to be written.
//              UINT32 Value - A 32bits data will be written to the register
//                             of I/O APIC.
//
// Output:      EFI_SUCCESS
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS IoApicWrite (
    IN UINT8        Reg,
    IN UINT32       Value )
{
	struct IO_APIC *IoApicStruct = IoApicBase();

	MMIO_WRITE8((UINT64)&IoApicStruct->Index, Reg);
	MMIO_WRITE32((UINT64)&IoApicStruct->Data, Value);

	return EFI_SUCCESS;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:   IoApicRead
//
// Description: This function reads a 32bits data from the register of
//              I/O APIC.
//
// Input:       UINT8 Reg - the register offset to be read.
//
// Output:      UINT32 - A 32bits data read from the register of I/O APIC.
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

UINT32 IoApicRead (
    IN UINT8        Reg )
{
	struct IO_APIC *IoApicStruct = IoApicBase();

	MMIO_WRITE8((UINT64)&IoApicStruct->Index, Reg);
	return MMIO_READ32((UINT64)&IoApicStruct->Data);
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:   IoApicEnableIrq
//
// Description: This function enables the specific interrupt pin of I/O APIC.
//
// Input:       UINT8   Irq - The pin number of I/O APIC
//              BOOLEAN LevelTriggered - Trigger mechanism (level or edge)
//                                       for this INT pin.
//              BOOLEAN Polarity - Specifies the polarity of the INT pin.
//                                 (Active High or Active Low)
// Output:      EFI_SUCCESS
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS IoApicEnableIrq (
    IN UINT8        Irq,
    IN BOOLEAN      LevelTriggered,
    IN BOOLEAN      Polarity )
{
	IO_APIC_ROUTE_ENTRY	ApicEntry;
	union ENTRY_UNION			Eu = {{0, 0}};

	ApicEntry.DestMode = 0; // 0: physical
	ApicEntry.Mask = 0;		 // 0 : enable
	ApicEntry.Dest = gBspLocalApicID; // suppose the BSP handle interrupt.
	ApicEntry.DeliveryMode = 0;      // 000: FIXED
	ApicEntry.Polarity = (Polarity) ? 1 : 0;
	ApicEntry.Trigger = (LevelTriggered) ? 1 : 0;
	ApicEntry.Vector = MASTER_INTERRUPT_BASE + Irq;

	Eu.Entry = ApicEntry;
	IoApicWrite(IO_APIC_REDIR_TABLE_HIGH + 2 * Irq, Eu.W2);
	IoApicWrite(IO_APIC_REDIR_TABLE_LOW + 2 * Irq, Eu.W1);
	return EFI_SUCCESS;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:   IoApicDisableIrq
//
// Description: This function disables the specific interrupt pin of I/O APIC.
//
// Input:       UINT8 Irq - The pin number of I/O APIC
//
// Output:      EFI_SUCCESS
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS IoApicDisableIrq (
    IN UINT8        Irq )
{
	union ENTRY_UNION Eu = {{0, 0}};

	Eu.W1 = IoApicRead(IO_APIC_REDIR_TABLE_LOW + 2 * Irq);
	Eu.W2 = IoApicRead(IO_APIC_REDIR_TABLE_HIGH + 2 * Irq);
	Eu.Entry.Mask = 1;
	IoApicWrite(IO_APIC_REDIR_TABLE_LOW + 2 * Irq, Eu.W1);
	IoApicWrite(IO_APIC_REDIR_TABLE_HIGH + 2 * Irq, Eu.W2);
	IoApicEoi(Irq);

	return EFI_SUCCESS;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:   IoApicMaskIrq
//
// Description: This routine masks the specific interrupt pin of I/O APIC.
//
// Input:       UINT8 Irq - The pin number of I/O APIC
//
// Output:      EFI_SUCCESS
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS IoApicMaskIrq (
    IN UINT8        Irq )
{
	union ENTRY_UNION Eu = {{0, 0}};

	Eu.W1 = IoApicRead(IO_APIC_REDIR_TABLE_LOW + 2 * Irq);
	Eu.Entry.Mask = 1;
	IoApicWrite(IO_APIC_REDIR_TABLE_LOW + 2 * Irq, Eu.W1);

	return EFI_SUCCESS;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:   IoApicUnmaskIrq
//
// Description: This routine unmasks the specific interrupt pin of I/O APIC.
//
// Input:       UINT8 Irq - The pin number of I/O APIC
//
// Output:      EFI_SUCCESS
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS IoApicUnmaskIrq (
    IN UINT8        Irq )
{
	union ENTRY_UNION Eu = {{0, 0}};

	Eu.W1 = IoApicRead(IO_APIC_REDIR_TABLE_LOW + 2 * Irq);
	Eu.Entry.Mask = 0;
	IoApicWrite(IO_APIC_REDIR_TABLE_LOW + 2 * Irq, Eu.W1);

	return EFI_SUCCESS;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:   IoApicEoi
//
// Description: This routine issues an EOI to the specific pin of I/O APIC.
//
// Input:       UINT8 Irq - The pin number of I/O APIC
//
// Output:      EFI_SUCCESS
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS IoApicEoi (
    IN UINT8        Irq )
{
	EFI_STATUS 	Status = EFI_SUCCESS;
	UINT32		Vector = MASTER_INTERRUPT_BASE + Irq;
	struct IO_APIC *IoApicStruct = IoApicBase();
	UINT32		Isr = 0;
	union ENTRY_UNION Eu = {{0, 0}};

	do {
		MMIO_WRITE32((UINT64)&IoApicStruct->Eoi, Vector);
		Eu.W1 = IoApicRead(IO_APIC_REDIR_TABLE_LOW + 2 * Irq);
	} while (Eu.Entry.Irr);

	do {
		MMIO_WRITE32(LOCAL_APIC_BASE + APIC_EOI_REGISTER, Vector);
		Isr = MMIO_READ32(LOCAL_APIC_BASE + ISR_REG (Vector));
	} while (Isr & ISR_BIT(Vector));

	return EFI_SUCCESS;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:   GetHpetApicPin
//
// Description: This routine gets the pin number of I/O APIC for HPET.
//
// Input:       None
//
// Output:      UINT8 Irq - The pin number of I/O APIC for HPET.
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

UINT8 GetHpetApicPin (VOID)
{
	EFI_STATUS 	Status = EFI_SUCCESS;
	UINT8		Irq = 0;

    volatile HPET_TIMER_CONFIGURATION_REGISTER   TimerConfiguration;

    TimerConfiguration.Uint64 = MMIO_READ64( HPET_BASE_ADDRESS + HPET_TIMER_CONFIGURATION_OFFSET + HPET_OFFSET * HPET_TIMER_STRIDE );
	Irq = TimerConfiguration.Bits.InterruptRoute;

	return Irq;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:   IsHpetApicEnable
//
// Description: This routine checks the pin of I/O APIC for HPET is enabled or
//              not.
//
// Input:       None
//
// Output:      TRUE  - The pin of I/O APIC for HPET is enabled
//              FALSE - The pin of I/O APIC for HPET is disabled
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

BOOLEAN IsHpetApicEnable (VOID)
{
	union ENTRY_UNION Eu = {{0, 0}};
	UINT8 Irq;

	Irq = GetHpetApicPin();

	Eu.W1 = IoApicRead(IO_APIC_REDIR_TABLE_LOW + 2 * Irq);

	return (Eu.Entry.Mask) ? FALSE : TRUE;
}
#endif

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
