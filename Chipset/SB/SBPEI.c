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
// $Header: /Alaska/BIN/Chipset/Intel/SouthBridge/LynxPoint/Intel Pch SB Chipset/SBPEI.c 57    5/27/15 2:26a Dennisliu $
//
// $Revision: 57 $
//
// $Date: 5/27/15 2:26a $
//*************************************************************************
// Revision History
// ----------------
// $Log: /Alaska/BIN/Chipset/Intel/SouthBridge/LynxPoint/Intel Pch SB Chipset/SBPEI.c $
// 
// 57    5/27/15 2:26a Dennisliu
// [TAG]  		EIP219399
// [Category]  	Improvement
// [Description]  	Static code analysis issue found in Aptio4 Intel
// LynxPoint PCH module
// [Files]  		Chipset\SB\SBPEI.c
// 
// 56    11/17/14 7:24a Mirayang
// [TAG]  		EIP190402 
// [Category]  	New Feature
// [Description]  	Support BootScriptHide eModule on Sharkbay CRB project
// 
// 55    9/23/14 6:12a Mirayang
// [TAG]  		EIP183246
// [Category]  	Bug Fix
// [Severity]  	Important
// [Symptom]  	BIOS capsule update usb issue
// [RootCause]  	Boot mode conditions miss "BOOT_ON_FLASH_UPDATE" in
// InitUsbMisc().
// [Solution]  	Add "BOOT_ON_FLASH_UPDATE" this boot mode conditions .
// 
// 54    7/21/14 10:42p Mirayang
// [TAG]  		EIP176923 
// [Category]  	Improvement
// [Description]  	Program BUC.SDO to 1 on normal boot in PCH component.
// 
// 53    4/01/14 10:18p Barretlin
// [TAG]  		EIP156783
// [Category]  	Improvement
// [Description]  	fix build error when removing usb recovery module
// [Files]  		SbPei.c
// 
// 52    1/14/14 1:37a Barretlin
// [TAG]  		EIP150529
// [Category]  	Improvement
// [Description]  	System hang due to dysfunctional MRC delay routine
// [Files]  		SBPei.c
// 
// 51    1/08/14 11:18p Barretlin
// [TAG]  		EIP149596
// [Category]  	Improvement
// [Description]  	system cannot enter to recovery mode when CMOS is bad
// [Files]  		SBPEI.c
// 
// 50    10/29/13 12:38a Barretlin
// [TAG]  		EIP136997
// [Category]  	Improvement
// [Description]  	fix build error when SUPPORT_RAID_DRIVER token is 0
// [Files]  		SBPei.c
// 
// 49    10/06/13 2:31a Barretlin
// [TAG]  		EIP138340
// [Category]  	Improvement
// [Description]  	SATA drive detection issue in PCH Platform BIOS
// reference code revision 1.6.2
// [Files]  		SB.sdl SBPEI.c
// 
// 48    9/17/13 2:48p Barretlin
// [TAG]  		EIP N/A
// [Category]  	Improvement
// [Description]  	use token to decide SATA RxEq policy vaule
// [Files]  		SB.sdl SBPei.c
// 
// 47    9/17/13 8:43a Barretlin
// [TAG]  		EIP136354
// [Category]  	Improvement
// [Description]  	remove setting RCBA Coprocessor Error Enable bit
// [Files]  		SB.sdl SbPei.c
// 
// 46    8/23/13 4:34a Barretlin
// [TAG]  		EIP133819
// [Category]  	Improvement
// [Description]  	change platform policy revision to 4
// [Files]  		SBPEI.c
// 
// 45    8/23/13 3:42a Barretlin
// [TAG]  		EIP133819
// [Category]  	Improvement
// [Description]  	update for Intel PCH RC 1.6.2.0
// [Files]  		SB.sdl SBPEI.c
// 
// 44    7/17/13 8:01a Scottyang
// [TAG]  		None
// [Category]  	Improvement
// [Description]  	Let's GPIO GPINDIS bit setting by custom define except
// GPO.
// [Files]  		SBPEI.c
// 
// 43    5/23/13 1:56a Scottyang
// [TAG]  		EIP120623
// [Category]  	Improvement
// [Description]  	LCD turn on automatically when resume from S3.
// [Files]  		SBPEI.c, SBDxe.c, AcpiModeEnable.c
// 
// 42    5/13/13 9:14a Scottyang
// [TAG]  		None
// [Category]  	Improvement
// [Description]  	Set time to default  when clear cmos by jumper or
// remove battery.
// [Files]  		SBPEI.c
// 
// 40    5/08/13 4:37a Scottyang
// [TAG]  		EIP123117
// [Category]  	Improvement
// [Description]  	Fixed enable USB precondition, and do power off, power
// on, it will hang 9C.
// [Files]  		SBPEI.c
// 
// 39    5/08/13 3:09a Scottyang
// [TAG]  		None
// [Category]  	Bug Fix
// [Severity]  	Normal
// [Symptom]  	Enable bit set at wrong place.
// [RootCause]  	The offset error.
// [Solution]  	Make offset correct.
// [Files]  		SBPEI.c
// 
// 37    5/03/13 1:42a Scottyang
// [TAG]  		EIP115528
// [Category]  	Improvement
// [Description]  	Support XHCI port recovery when reset after boot to OS
// with XHCI driver.
// [Files]  		SBPEI.c
// 
// 36    4/24/13 6:42a Scottyang
// [TAG]  		EIP114861
// [Category]  	Improvement
// [Description]  	For PTT(Fast boot) 15 can reduce post for CD-ROM.
// [Files]  		SBPEI.c
// 
// 35    4/24/13 4:20a Scottyang
// [TAG]  		EIP118667
// [Category]  	Improvement
// [Description]  	For ULT when GPIO is GPO will also set GPI_DIS_DISABLE.
// [Files]  		SBPEI.c
// 
// 34    4/24/13 2:15a Scottyang
// [TAG]  		None
// [Category]  	Improvement
// [Description]  	Porting GPI interrupt by LPT-LP EDS 1.5.
// [Files]  		SB.sdl, SB.H, SBPPI.h, SBPEI.c
// 
// 33    4/23/13 4:51a Wesleychen
// [TAG]         None
// [Category]    Improvement
// [Description] Add token "ONLY_CLEAR_RTC_EN_IN_PEI" for improve
//               "EIP120623".
// [Files]       AcpiModeEnable.c; SB.SDL; SBPEI.c
// 
// 31    4/18/13 12:18a Wesleychen
// [TAG]        EIP120623
// [Category]   Bug Fix
// [Severity]   Important
// [Symptom]    LCD doesn't turn on automatically when resume from S3.
// [RootCause]  PM1_STS (PMBASE+00h) are cleared in EnableAcpiMode().
// [Solution]   Avoid PM1_STS clearing behavior is occurring in S3
//              resuming.
//              *AcpiModeEnable.c Rev#8~11(EIP101628 & EIP118531) are are
//              no need be existence.
// [Files]      SBPEI.c; AcpiModeEnable.c
// 
// 29    3/15/13 3:33a Scottyang
// [TAG]  		EIP118121
// [Category]  	Improvement
// [Description]  	Update PCH RC 1.3.0.
// [Files]  		..\ReferenceCode\Chipset\LynxPoint\*.*, SBDxe.c, SBPEI.c,
// SB.sd, SB.uni, GetSetupData.c, SbSetupData.h
// 
// 28    3/12/13 7:40a Scottyang
// [TAG]  		EIP115528
// [Category]  	Improvement
// [Description]  	USB ports are connected to EHCI not XHCI When recovery.
// [Files]  		SBPEI.c
// 
// 27    2/26/13 1:02a Scottyang
// [TAG]  		None
// [Category]  	Improvement
// [Description]  	Follow intel BIOS V112 to change IRQ rout.
// [Files]  		SB.sdl, SBPEI.c
// 
// 26    2/09/13 12:12a Scottyang
// [TAG]  		EIP114922
// [Category]  	Improvement
// [Description]  	Update PCH RC 1.1.0.
// [Files]  		..\ReferenceCode\Chipset\LynxPoint\*.*, SBDxe.c, SBPEI.c,
// SB.sd, SB.uni, GetSetupData.c, SbSetupDara.h
// 
// 25    1/31/13 10:51a Scottyang
// [TAG]  		None
// [Category]  	Improvement
// [Description]  	Add delay for HDD recovery.
// [Files]  		SBPEI.c
// 
// 24    1/30/13 1:15a Scottyang
// [TAG]  		None
// [Category]  	Improvement
// [Description]  	Fix build error at 4653.
// [Files]  		SBPEI.c
// 
// 23    1/27/13 11:01p Scottyang
// [TAG]  		None
// [Category]  	Improvement
// [Description]  	Capsule 2.0 crash dump link function.
// [Files]  		SBPEI.c
// SBDxe.c
// SBRun.c
// 
// 22    1/11/13 1:51a Scottyang
// [TAG]  		EIP88358
// [Category]  	Improvement
// [Description]  	Add FORCE_USER_TO_SETUP_IF_CMOS_BAD token
// [Files]  		SBDex.c, SBPei.c, RTC.h, SB.sdl
// 
// 21    12/24/12 5:51a Scottyang
// [TAG]  		None
// [Category]  	Improvement
// [Description]  	Add option for XHCI Idel L1 workaroung.
// [Files]  		GetSetupData.c, SbSetupData.h, SB.sd, SB.uni, SBDxe.c,
// SBPEI.c
// 
// 20    12/18/12 6:10a Scottyang
// [TAG] EIP109697
// [Category] Improvement
// [Description] Update PCH RC 0.8.1
// [Files] ReferenceCode\Chipset\LynxPoint\*.*, SBDxe.c, SBPEI.c, SB.sd,
// SbSetupData.c, GetSetupDate.c
// 
// 19    12/13/12 10:31a Scottyang
// [TAG]  		EIP106687
// [Category]  	Improvement
// [Description]  	Add option for delay to detect PCIE card.
// [Files]  		SBPEI.c, SB.sd, SB.uni, GetSetupData.c, SbSetupData.h,
// PciBus.c
// 
// 18    12/13/12 10:17a Scottyang
// [TAG]  		EIP107424
// [Category]  	Bug Fix
// [Severity]  	Normal
// [Symptom]  	 System stops at CKP 0x9C when system performs a cool boot
// and AMI debugger is enabled.
// [RootCause]  	Unexpected USB EHCI Legacy Support Extended status is
// rised, it is out of USB module control.
// [Solution]  	 Clear unexpected USB EHCI Legacy Support Extended
// status.
// [Files]  		SBPEI.c 
// 
// 17    11/20/12 9:47a Scottyang
// [TAG]  		EIP107014
// [Category]  	Improvement
// [Description]  	Update RC 0.8.0
// [Files]  		ReferenceCode\Chipset\LynxPoint\*.*, SBDxe.c, SBPEI.c,
// SB.sd, SbSetupData.c, GetSetupDate.c
// 
// 16    11/06/12 8:12a Scottyang
// [TAG]  		None
// [Category]  	Improvement
// [Description]  	Reduce function "GetPchSeries()".
// [Files]  		SBPEI.c, SBDxe.c, SmiHandlerPorting.c, SmiHandlerPorting2.c
// 
// 15    10/25/12 8:16a Scottyang
// [TAG]  		None
// [Category]  	Improvement
// [Description]  	Add new device and remove device which no use
// [Files]  		SBPEI.c, SB.sdl
// 
// 14    10/16/12 4:16a Scottyang
// [TAG]  		None
// [Category]  	Improvement
// [Description]  	Assign IRQ for device 21
// 
// 13    10/14/12 8:33a Scottyang
// [TAG]  		None
// [Category]  	Improvement
// [Description]  	One rom for two chip and one chip. 
// [Files]  		SPPEIBoard.c, SB.sd, SBDxe.c, SBPEI.c, PCH.asl
// 
// 12    10/12/12 4:55a Scottyang
// [TAG]  		EIP87695
// [Category]  	Improvement
// [Description]  	System should reboot successfully next time if S3
// resume fail
// [Files]  		SB.sdl, SBPei.c
// 
// 11    10/11/12 11:15p Scottyang
// [TAG]  		EIP86096
// [Category]  	Improvement
// [Description]  	Fix SATA AHCI port4 & 5 can't loading recovery image.
// [Files]  		SBPei.c
// 
// 10    9/26/12 3:55a Victortu
// [TAG]           None
// [Category]      Improvement
// [Description]   Update for Intel PCH LPT RC070.
// [Files]         SB.sdl, SBDXE.c, SBPEI.c, Pch.sdl, SB.sd, SB.uni
// 
// [TAG]           None
// [Category]      Improvement
// [Description]   Update for PCH LP GPIO compatible.
// [Files]         SB.sdl, SB.H, AcpiModeEnable.c, AcpiModeEnable.sdl,
// SBDxe.c, SBGeneric.c, SBPEI.c, SBSMI.c, SleepSmi.c,
// SmiHandlerPorting.c, SmiHandlerPorting2.c
// 
// 9     9/12/12 5:20a Victortu
// [TAG]           None
// [Category]      Improvement
// [Description]   Force HPET enabled for MRC initialization.
// [Files]         SB.sd, SBPEI.c
// 
// [TAG]           None
// [Category]      Improvement
// [Description]   Modify for ULT GPIO changed by PCH LPT-LP EDS 1.0.
// [Files]         SB.H, SB.sdl, AcpiModeEnable.c, AcpiModeEnable.sdl,
// SBPEI.c
// 
// 8     8/24/12 6:51a Victortu
// [TAG]           None
// [Category]      Improvement
// [Description]   Sync USB policy for UsbPrecondition function.
// [Files]         SBPEI.c
// 
// 7     8/14/12 11:26p Victortu
// [TAG]           None
// [Category]      Improvement
// [Description]   Update "SB_TEMP_MMIO_BASE" and
// "EHCI_MMIO_BASE_ADDRESS".
// [Files]         SB.sdl, SBDxe.c, SBPEI.c
// 
// 6     8/13/12 10:29a Victortu
// [TAG]           None
// [Category]      Improvement
// [Description]   Update correct MMIO BASE for TempMemBaseAddr policy.
// [Files]         SBPEI.c
// 
// [TAG]           None
// [Category]      Improvement
// [Description]   Update PCH Policy.
// [Files]         SB.sdl, SBDxe.c, SBPEI.c
// 
// [TAG]           None
// [Category]      Improvement
// [Description]   Implement USB Precondition option for policy
// "UsbPrecondition".
// [Files]         GetSetupData.c, SB.sd, SB.uni, SbSetupData.h, SBDxe.c,
// SBPEI.c
// 
// 5     7/27/12 6:14a Victortu
// [TAG]           None
// [Category]      Improvement
// [Description]   Update setup items and policies.
// [Files]         GetSetupData.c, SB.sdl, SB.sd, SB.uni, SbSetupData.h,
// SBPEI.c, SBDXE.c
// 
// [TAG]           None
// [Category]      Improvement
// [Description]   Update to support ULT Platform.
// [Files]         SB.H, SB.mak, SB.sdl, SB.sd, SBSetup.c,
// AcpiModeEnable.c, SBDxe.c, SBPEI.c, SBSMI.c, SleepSmi.c,
// SmiHandlerPorting.c, SmiHandlerPorting2.c, SBPPI.h, Pch.sdl
// 
// 4     7/02/12 10:17a Victortu
// [TAG]		None
// [Category]	Improvement
// [Description]	Updated and modified for PCH RC 0.6.0.
// [Files]		SBGeneric.c, SB.sdl, SBCspLib.h, SBDxe.c, SBPEI.c
// 
// 3     6/13/12 11:34p Victortu
// [TAG]           None
// [Category]      Improvement
// [Description]   Implement Warm Boot function for Secure Flash feature.
// [Files]         SB.H, SB.mak, SB.sdl, SBDxe.c, SBGeneric.c, SBPEI.c,
// SBSMI.c
// 
// 2     2/24/12 2:35a Victortu
// Support RapidStart_SUPPORT.
// 
// 1     2/08/12 8:24a Yurenlai
// Intel Lynx Point/SB eChipset initially releases.
// 
//*************************************************************************
//<AMI_FHDR_START>
//
// Name:        SBPEI.C
//
// Description: This file contains code for South Bridge initialization
//              in the PEI stage
//
//<AMI_FHDR_END>
//*************************************************************************

//----------------------------------------------------------------------------
// Include(s)
//----------------------------------------------------------------------------

#include <Efi.h>
#include <Pei.h>
#include <Token.h>
#include <AmiPeiLib.h>
#include <Hob.h>
#include <Setup.h>
#include <AmiCspLib.h>
// Produced/used PPI interfaces
#include <ppi\PciCfg2.h>
#include <ppi\SBPPI.h>
#include <ppi\CpuIo.h>
#include <ppi\CspLibPpi.h>
#include <RTC.h>
#include <PchAccess.h>
#include <Ppi\PchUsbPolicy\PchUsbPolicy.h>
#include <Ppi\PchInit\PchInit.h>

#include <Ppi\SmbusPolicy\SmbusPolicy.h>
#include <Ppi\PchPlatformPolicy\PchPlatformPolicy.h>

#if defined   iME_SUPPORT && iME_SUPPORT
#include <Guid\MeBiosExtensionSetup\MeBiosExtensionSetup.h>
#endif

#if SB_RESET_PPI_SUPPORT
#include <Ppi\Reset.h>
#endif

#if ATAPI_RECOVERY_SUPPORT
#include <Ppi\AtaController.h>
#endif

#if SB_STALL_PPI_SUPPORT
#include <Ppi\Stall.h>
#endif

#if WdtPei_SUPPORT
#include "ppi\Wdt\Wdt.h"
#endif
#include <ppi\NBPPI.h>

#if Capsule2_0_SUPPORT
#include <ppi\capsule.h>    //CAPSULE20
#endif

#if defined(SUPPORT_RAID_DRIVER) && SUPPORT_RAID_DRIVER && (PTT_VER > 15)
#include <FastBoot.h>

#define SATA1_BDF (0x1f << 3 | 0x02)
#define SATA2_BDF (0x1f << 3 | 0x05)
#endif
//----------------------------------------------------------------------------
// Constant, Macro and Type Definition(s)
//----------------------------------------------------------------------------
// Constant Definition(s)
#define EHCI_MEMORY_SPACE 0x400
#define TIMER_RESOLUTION  1
#define S3_SLP_TYP        0x05

#ifndef SMM_SUPPORT
  #define SMM_SUPPORT   0
#endif

#define RETRAIN_DELAY      50		// [EIP106687]

// Macro Definition(s)

// Type Definition(s)
#if defined   iME_SUPPORT && iME_SUPPORT
// TS on DIMM defines
#define TS_ON_CHANNEL0_SLOT_0_DIMM                 0x1
#define TS_ON_CHANNEL1_SLOT_0_DIMM                 0x2
#define TS_ON_C0_S0_AND_C1_S0_DIMM                 0x3
#endif

#ifndef CAPSULE_SUPPORT

#if defined Capsule2_0_SUPPORT && Capsule2_0_SUPPORT
#define CAPSULE_SUPPORT 1
#else
#define CAPSULE_SUPPORT 0
#endif

#endif

typedef struct _SATA_LENGTH_CONFIG {
    UINT8   SataGen1RxEqEnable;
    UINT8   SataGen1RxEqValue;
    UINT8   SataGen2RxEqEnable;
    UINT8   SataGen2RxEqValue;
    UINT8   SataGen3RxEqEnable;
    UINT8   SataGen3RxEqValue;
} SATA_LENGTH_CONFIG;
// Function Prototype(s)

BOOLEAN IsRecovery (
    IN EFI_PEI_SERVICES         **PeiServices,
    IN EFI_PEI_PCI_CFG2_PPI     *PciCfg,
    IN EFI_PEI_CPU_IO_PPI       *CpuIo
);

#if SB_RESET_PPI_SUPPORT
EFI_STATUS SBPEI_ResetSystem (
    IN EFI_PEI_SERVICES         **PeiServices
);
#endif

#if SB_STALL_PPI_SUPPORT
EFI_STATUS SBPEI_Stall (
    IN EFI_PEI_SERVICES         **PeiServices, 
    IN EFI_PEI_STALL_PPI        *This,
    IN UINTN                    Microseconds
);
#endif

#if ATAPI_RECOVERY_SUPPORT
EFI_STATUS EFIAPI EnableAtaChannel (
    IN EFI_PEI_SERVICES         **PeiServices,
    IN PEI_ATA_CONTROLLER_PPI   *This,
    IN UINT8                    ChannelIndex
);
#endif

BOOLEAN IsS3 (
    IN EFI_PEI_SERVICES         **PeiServices,
    IN EFI_PEI_CPU_IO_PPI       *CpuIo
);

VOID ProgramGPIO (
    IN EFI_PEI_SERVICES         **PeiServices,
    IN EFI_PEI_CPU_IO_PPI       *CpuIo,
    IN SB_SETUP_DATA            *SbSetupData,
    IN AMI_GPIO_INIT_TABLE_STRUCT  *pTable
);

VOID ProgramSBSubId(
    IN EFI_PEI_SERVICES         **PeiServices,
    IN EFI_PEI_PCI_CFG2_PPI     *PciCfg,
    IN AMI_PEI_SB_CUSTOM_PPI    *SBPeiOemPpi
);

VOID InitPCIe (
    IN EFI_PEI_SERVICES         **PeiServices,
    IN EFI_PEI_CPU_IO_PPI       *CpuIo,
    IN EFI_PEI_PCI_CFG2_PPI     *PciCfg
);

VOID InitSMBus (
    IN EFI_PEI_SERVICES         **PeiServices,
    IN EFI_PEI_CPU_IO_PPI       *CpuIo,
    IN EFI_PEI_PCI_CFG2_PPI     *PciCfg
);

VOID InitUsbMisc (
    IN EFI_PEI_SERVICES         **PeiServices,
    IN EFI_PEI_CPU_IO_PPI       *CpuIo,
    IN EFI_PEI_PCI_CFG2_PPI     *PciCfg,
    IN EFI_BOOT_MODE            BootMode
);

EFI_STATUS UpdateBootMode (
    IN EFI_PEI_SERVICES         **PeiServices,
    IN EFI_PEI_CPU_IO_PPI       *CpuIo,
    IN EFI_PEI_PCI_CFG2_PPI     *PciCfg
);

EFI_STATUS ProgramSBRegAfterMemInstalled (
    IN EFI_PEI_SERVICES         **PeiServices,
    IN EFI_PEI_NOTIFY_DESCRIPTOR *NotifyDescriptor,
    IN VOID                     *InvokePpi
);

EFI_STATUS ProgramSBRegBeforeEndofPei (
    IN EFI_PEI_SERVICES         **PeiServices,
    IN EFI_PEI_NOTIFY_DESCRIPTOR *NotifyDescriptor,
    IN VOID                     *InvokePpi
);

EFI_STATUS ProgramSBRegAfterMrc (
    IN EFI_PEI_SERVICES         **PeiServices,
    IN EFI_PEI_NOTIFY_DESCRIPTOR *NotifyDescriptor,
    IN VOID                     *InvokePpi
);

EFI_STATUS ProgramSBRegEndOfMrc (
    IN EFI_PEI_SERVICES         **PeiServices,
    IN EFI_PEI_NOTIFY_DESCRIPTOR *NotifyDescriptor,
    IN VOID                     *InvokePpi
);

VOID InitPMRegs(
    IN EFI_PEI_SERVICES         **PeiServices,
    IN EFI_PEI_CPU_IO_PPI       *CpuIo,
    IN SB_SETUP_DATA            *SbSetupData
);

VOID InitRTC(
    IN EFI_PEI_SERVICES         **PeiServices,
    IN EFI_PEI_CPU_IO_PPI       *CpuIo
);

VOID WriteSBDefaultSubId (
    IN EFI_PEI_SERVICES         **PeiServices,
    IN EFI_PEI_PCI_CFG2_PPI     *PciCfg
);

VOID ProgramRCRBMmio (
    IN EFI_PEI_SERVICES         **PeiServices,
    IN EFI_PEI_CPU_IO_PPI       *CpuIo 
);

EFI_STATUS
ProgramSBIoDecodeRegs (
    IN EFI_PEI_SERVICES         **PeiServices,
    IN EFI_PEI_PCI_CFG2_PPI     *PciCfg
);

EFI_STATUS
ProgramPchDeviceBase (
    IN EFI_PEI_SERVICES         **PeiServices,
    IN EFI_PEI_PCI_CFG2_PPI      *PciCfg
);

EFI_STATUS
GeneralPowerFailureHandler (
    IN EFI_PEI_SERVICES         **PeiServices,
    IN EFI_PEI_CPU_IO_PPI       *CpuIo,
    IN EFI_PEI_PCI_CFG2_PPI     *PciCfg
);

EFI_STATUS
SetTheStateToGoAfterG3 (
    IN EFI_PEI_SERVICES         **PeiServices,
    IN EFI_PEI_CPU_IO_PPI       *CpuIo,
    IN EFI_PEI_PCI_CFG2_PPI     *PciCfg,
    IN SB_SETUP_DATA            *SbSetupData
);

EFI_STATUS InstallPchPlatformPolicyPpi (
    IN EFI_PEI_SERVICES         **PeiServices,
    IN SB_SETUP_DATA            *SbSetupData
);

EFI_STATUS
InstallAmtPlatformPolicyPpi (
    IN EFI_PEI_SERVICES         **PeiServices,
    IN SB_SETUP_DATA            *SbSetupData
);

EFI_STATUS
CreateAmtForcePushPetPolicyHob(
    IN EFI_PEI_SERVICES         **PeiServices
);

//----------------------------------------------------------------------------
// Variable and External Declaration(s)
//----------------------------------------------------------------------------
// Variable Declaration(s)

// GUID Definition(s)
EFI_GUID gAmiPEISBInitPolicyGuid     = AMI_PEI_SBINIT_POLICY_PPI_GUID;
EFI_GUID gAmiPEIPCITableInitPpiGuid  = AMI_PEI_PCI_TABLE_INIT_PPI_GUID;
EFI_GUID gMasterBootModeGuid         = EFI_PEI_MASTER_BOOT_MODE_PEIM_PPI;
EFI_GUID gRecoveryBootModeGuid       = EFI_PEI_BOOT_IN_RECOVERY_MODE_PEIM_PPI;
EFI_GUID gEfiPeiPermMemInstalledGuid = EFI_PEI_PERMANENT_MEMORY_INSTALLED_PPI;
EFI_GUID gEfiPeiEndOfPeiPhasePpiGuid = EFI_PEI_END_OF_PEI_PHASE_PPI_GUID;
EFI_GUID gPeiSmbusPolicyPpiGuid      = PEI_SMBUS_POLICY_PPI_GUID;
EFI_GUID gPchPlatformPolicyPpiGuid   = PCH_PLATFORM_POLICY_PPI_GUID;
EFI_GUID gSetupGuid                  = SETUP_GUID;
EFI_GUID gPchUsbPolicyPpiGuid        = PCH_USB_POLICY_PPI_GUID;
EFI_GUID gPchInitPpiGuid             = PCH_INIT_PPI_GUID;

EFI_GUID gPeiCompleteMRCGuid         = AMI_PEI_AFTER_MRC_GUID;

#if SB_STALL_PPI_SUPPORT
EFI_GUID gStallPpiGuid = EFI_PEI_STALL_PPI_GUID;
#endif

#if SB_RESET_PPI_SUPPORT
EFI_GUID gPeiResetPpiGuid = EFI_PEI_RESET_PPI_GUID;
#endif

#if ATAPI_RECOVERY_SUPPORT
EFI_GUID gPeiAtaControllerPpiGuid = PEI_ATA_CONTROLLER_PPI_GUID;
#endif

#if WdtPei_SUPPORT
EFI_GUID  gWdtPpiGuid = WDT_PPI_GUID;
#endif

EFI_GUID gOemPchPlatformPolicyOverridePpiGuid   = AMI_PEI_SB_OEM_PLATFORM_POLICY_OVERRIDE_PPI_GUID;

// PPI Definition(s)

static AMI_PEI_SBINIT_POLICY_PPI mAMIPEISBInitPolicyPpi = {
    TRUE
};

#if ATAPI_RECOVERY_SUPPORT
static PEI_ATA_CONTROLLER_PPI mAtaControllerPpi = {
    EnableAtaChannel 
};
#endif

#if SB_STALL_PPI_SUPPORT
static EFI_PEI_STALL_PPI mStallPpi = {
    TIMER_RESOLUTION,
    SBPEI_Stall
};
#endif

#if SB_RESET_PPI_SUPPORT
static EFI_PEI_RESET_PPI mResetPpi = { 
    SBPEI_ResetSystem
};
#endif

// PPI that are installed

#if SB_STALL_PPI_SUPPORT
static EFI_PEI_PPI_DESCRIPTOR mBeforeBootModePpiList[] = {
    { EFI_PEI_PPI_DESCRIPTOR_PPI | EFI_PEI_PPI_DESCRIPTOR_TERMINATE_LIST, \
      &gStallPpiGuid, &mStallPpi },
};
#endif

static EFI_PEI_PPI_DESCRIPTOR mBootModePpi[] = {
    { EFI_PEI_PPI_DESCRIPTOR_PPI | EFI_PEI_PPI_DESCRIPTOR_TERMINATE_LIST, \
      &gMasterBootModeGuid, NULL },
};

static EFI_PEI_PPI_DESCRIPTOR mRecoveryModePpi[] = {
    { EFI_PEI_PPI_DESCRIPTOR_PPI | EFI_PEI_PPI_DESCRIPTOR_TERMINATE_LIST, \
      &gRecoveryBootModeGuid, NULL },
};

static EFI_PEI_PPI_DESCRIPTOR mPpiList[] = {
#if ATAPI_RECOVERY_SUPPORT
    { EFI_PEI_PPI_DESCRIPTOR_PPI, \
      &gPeiAtaControllerPpiGuid, &mAtaControllerPpi },
#endif
#if SB_RESET_PPI_SUPPORT
    { EFI_PEI_PPI_DESCRIPTOR_PPI, &gPeiResetPpiGuid, &mResetPpi },
#endif
    { EFI_PEI_PPI_DESCRIPTOR_PPI | EFI_PEI_PPI_DESCRIPTOR_TERMINATE_LIST, \
      &gAmiPEISBInitPolicyGuid, &mAMIPEISBInitPolicyPpi }
};

// PPI that are notified

static EFI_PEI_NOTIFY_DESCRIPTOR mNotifyList[] = {
    { EFI_PEI_PPI_DESCRIPTOR_NOTIFY_CALLBACK | \
      EFI_PEI_PPI_DESCRIPTOR_TERMINATE_LIST, \
      &gEfiPeiEndOfPeiPhasePpiGuid, ProgramSBRegBeforeEndofPei },
};

static EFI_PEI_NOTIFY_DESCRIPTOR mMemoryReadyNotify[] = {
    { EFI_PEI_PPI_DESCRIPTOR_NOTIFY_CALLBACK | \
      EFI_PEI_PPI_DESCRIPTOR_TERMINATE_LIST,
      &gEfiPeiPermMemInstalledGuid, ProgramSBRegAfterMemInstalled }
};

static EFI_PEI_NOTIFY_DESCRIPTOR AfterMrcNotifyList[] = {
    { EFI_PEI_PPI_DESCRIPTOR_NOTIFY_CALLBACK | \
      EFI_PEI_PPI_DESCRIPTOR_TERMINATE_LIST, \
      &gAmiPeiAfterMrcGuid, ProgramSBRegAfterMrc },
};
static EFI_PEI_NOTIFY_DESCRIPTOR EndOfMrcNotifyList[] = {
    { EFI_PEI_PPI_DESCRIPTOR_NOTIFY_CALLBACK | \
      EFI_PEI_PPI_DESCRIPTOR_TERMINATE_LIST, \
      &gAmiPeiEndOfMemDetectGuid, ProgramSBRegEndOfMrc },
};

static EFI_PEI_PPI_DESCRIPTOR StallPpiDescriptor_InMemory[] =
{ 
  {
    EFI_PEI_PPI_DESCRIPTOR_PPI | EFI_PEI_PPI_DESCRIPTOR_TERMINATE_LIST,
    &gStallPpiGuid, 
    &mStallPpi 
  }
};

// External Declaration(s)

extern AMI_GPIO_INIT_TABLE_STRUCT stSB_GPIODefaultInitTable[];
extern AMI_GPIO_INIT_TABLE_STRUCT stSB_GPIODefaultULTInitTable[];

extern EFI_STATUS CountTime (
    IN UINTN            DelayTime,
    IN UINT16           BaseAddr
);

#if SB_RESET_PPI_SUPPORT
extern VOID SBLib_ResetSystem (
    IN EFI_RESET_TYPE   ResetType
);
#endif

// Function Definition(s)

#ifdef RAPID_START_FLAG

#define RAPID_START_FLAG_ENTRY_DONE   BIT0

EFI_STATUS
RapidStartGetFlag (
  OUT     UINT8                   *Value
  )
{
  *Value = RtcRead (FFS_NV_FLAG_REG);
  return EFI_SUCCESS;
}

BOOLEAN
RapidStartResumeCheck (
  VOID
)
{
  EFI_STATUS                        Status;
  BOOLEAN                           RapidStartFlag;

  Status = RapidStartGetFlag (&RapidStartFlag);
  if ( !EFI_ERROR (Status) && ((RapidStartFlag & RAPID_START_FLAG_ENTRY_DONE) != 0)) {
    return TRUE;
  }

  return FALSE;
}
#endif

//----------------------------------------------------------------------------

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:   IsS3
//
// Description: This function determines if the system is resuming from an S3
//              sleep state.
//
// Input:       PeiServices - Pointer to the Pei Services function and data
//                            structure.
//
// Output:      TRUE - It is an S3 Resume
//              FALSE - It is not an S3 Resume
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

BOOLEAN IsS3 (
  IN EFI_PEI_SERVICES     **PeiServices,
  IN EFI_PEI_CPU_IO_PPI   *CpuIo )
{
  // Check PWR_FLR Bit
  if ((READ_PCI8_SB(R_PCH_LPC_GEN_PMCON_3) & B_PCH_LPC_GEN_PMCON_PWR_FLR) == 0) // 0xA4
    // Check PWRBTN override
    if ((READ_IO16_PM(R_PCH_ACPI_PM1_STS) & B_PCH_ACPI_PM1_STS_PRBTNOR) == 0) // 0x00
      // Check WAK_STS bit
      if ((READ_IO16_PM(R_PCH_ACPI_PM1_STS) & B_PCH_ACPI_PM1_STS_WAK)) // 0x00
        // Check the sleep type
        if ((READ_IO16_PM(R_PCH_ACPI_PM1_CNT) & B_PCH_ACPI_PM1_CNT_SLP_TYP) == V_PCH_ACPI_PM1_CNT_S3) //0x04
          return TRUE;

    return FALSE;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:   IsS4
//
// Description: This function determines if the system is resuming from an S4
//              sleep state.
//
// Input:       PeiServices - Pointer to the Pei Services function and data
//                            structure.
//
// Output:      TRUE - It is an S4 Resume
//              FALSE - It is not an S4 Resume
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

BOOLEAN IsS4 (
    IN EFI_PEI_SERVICES     **PeiServices,
    IN EFI_PEI_CPU_IO_PPI   *CpuIo )
{
    if ((READ_IO16_PM(ACPI_IOREG_PM1_CNTL) & 0x1c00) == 0x1800) //0x04
        return TRUE;
    return FALSE;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:   IsCmosBad
//
// Description: This function determines CMOS data is available.
//
// Input:       PeiServices - Pointer to the Pei Services function and data
//                            structure.
//
// Output:      TRUE - CMOS data is bad
//              FALSE - CMOS DATA is available
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

BOOLEAN IsCmosBad (
    IN EFI_PEI_SERVICES     **PeiServices,
    IN EFI_PEI_CPU_IO_PPI   *CpuIo )
{
    return (READ_IO8_RTC(CMOS_BAD_REG | RTC_NMI_MASK) & 0xc0) ? TRUE : FALSE;
}

#if KBC_SUPPORT && Recovery_SUPPORT
//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:   ResetKbc
//
// Description: This function resets Keyboard controller for Ctrl-Home
//              recovery function.     
//
// Input:       PeiServices - Pointer to the Pei Services function and
//                            data structure
//              CpuIo       - Pointer to the CPU I/O PPI
//              PciCfg      - Pointer to the PCI Configuration PPI
//
// Output:      None
//
// Notes:       No porting required.
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

VOID ResetKbc (
    IN EFI_PEI_SERVICES     **PeiServices,
    IN EFI_PEI_CPU_IO_PPI   *CpuIo,
    IN EFI_PEI_PCI_CFG2_PPI     *PciCfg
)
{
    volatile UINT8      KbcSts = 0;
    volatile UINT8      Buffer8;
    UINT32              TimeOut = 0x100;

    // Reset KBC
    if (CpuIo->IoRead8( PeiServices, CpuIo, KBC_IO_STS ) != 0xff) {
        // Clear KBC buffer
        do {
            Buffer8 = CpuIo->IoRead8( PeiServices, CpuIo, KBC_IO_DATA );
            KbcSts = CpuIo->IoRead8( PeiServices, CpuIo, KBC_IO_STS ); // 0x64
            TimeOut--;
        } while ((KbcSts & 3) && (TimeOut != 0));


        // Send BAT command 
        CpuIo->IoWrite8( PeiServices, CpuIo, KBC_IO_STS, 0xaa ); // 0x64

        // IBFree
        for (TimeOut = 0; TimeOut < 0x1000; TimeOut++) {
            CpuIo->IoWrite8( PeiServices, CpuIo, IO_DELAY_PORT, KbcSts );
            KbcSts = CpuIo->IoRead8( PeiServices, CpuIo, KBC_IO_STS ); // 0x64
            if ((KbcSts & 2) == 0) break;
        }

        // OBFree
        for (TimeOut = 0; TimeOut < 0x500; TimeOut++) {
            CpuIo->IoWrite8( PeiServices, CpuIo, IO_DELAY_PORT, KbcSts );
            KbcSts = CpuIo->IoRead8( PeiServices, CpuIo, KBC_IO_STS ); // 0x64
            if (KbcSts & 1) break;
        }

        // Get result if needed
        if (KbcSts & 1)
            Buffer8 = CpuIo->IoRead8( PeiServices, CpuIo, KBC_IO_DATA );
    }

    // Clear KBC status buffer.
    KbcSts = CpuIo->IoRead8 ( PeiServices, CpuIo, KBC_IO_STS ); // 0x64
}
#endif

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:   UpdateBootMode
//
// Description: This function determines the boot mode of the system.
//              After the correct boot mode has been determined, the PEI 
//              Service function SetBootMode is called and then
//              the MasterBootModePpi is installed
//
// Input:       PeiServices - Pointer to the Pei Services function and
//                            data structure
//              CpuIo       - Pointer to the CPU I/O PPI
//              PciCfg      - Pointer to the PCI Configuration PPI
//
// Output:      Always returns EFI_SUCCESS
//              Also defines the boot mode for the system
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS UpdateBootMode (
    IN EFI_PEI_SERVICES     **PeiServices,
    IN EFI_PEI_CPU_IO_PPI   *CpuIo,
    IN EFI_PEI_PCI_CFG2_PPI     *PciCfg
)
{
    EFI_STATUS              Status;
    EFI_BOOT_MODE           BootMode;

    // Check for changes in the possible boot modes.  This should be made in
    // prioritized order.  At the end of this function the boot mode is
    // determined.  The EFI_BOOT_MODE is defined in the PEI Spec

    Status = (*PeiServices)->GetBootMode (PeiServices, &BootMode);
    if (EFI_ERROR(Status) || (BootMode != BOOT_IN_RECOVERY_MODE))
      BootMode = BOOT_WITH_FULL_CONFIGURATION;

    // Returns 0 if no S3 resume detected returns -1 if this is an S3 boot
    if (IsS3(PeiServices, CpuIo)) {
        BootMode = BOOT_ON_S3_RESUME;
        PEI_TRACE((-1,PeiServices, "Boot mode = BOOT_ON_S3_RESUME\n"));
    } else {
        // Check for S4 resume
        if (IsS4(PeiServices, CpuIo)) {
            BootMode = BOOT_ON_S4_RESUME;
            PEI_TRACE((-1, PeiServices, "Boot mode = BOOT_ON_S4_RESUME\n"));
        }
        // Check for recovery mode
        #if KBC_SUPPORT && Recovery_SUPPORT && PERFORM_KBC_RESET
            ResetKbc(PeiServices,  CpuIo, PciCfg);
        #endif

        if (IsRecovery(PeiServices, PciCfg, CpuIo))
          BootMode = BOOT_IN_RECOVERY_MODE;
    }

    if (IsCmosBad(PeiServices, CpuIo)) {
        if (BootMode != BOOT_IN_RECOVERY_MODE){
            BootMode = BOOT_WITH_DEFAULT_SETTINGS;
            PEI_TRACE((-1,PeiServices,"Boot mode = BOOT_WITH_DEFAULT_SETTING\n"));
        }

#if FORCE_USER_TO_SETUP_IF_CMOS_BAD                                        // [EIP88358] >>
{
        EFI_STATUS          Status;
        UINT16              HobSize = sizeof(CMOS_BAD_HOB);
        EFI_GUID            CmosBadHobGuid = CMOS_BAD_HOB_GUID;
        CMOS_BAD_HOB        *CmosBadHob;

        Status = (*PeiServices)->CreateHob( PeiServices,
                                            EFI_HOB_TYPE_GUID_EXTENSION,
                                            HobSize,
                                            &CmosBadHob);
        if(!EFI_ERROR(Status)) {
            CmosBadHob->Header.Name = CmosBadHobGuid;    
        }
}
#endif                                                                     // [EIP88358] <<
    }
#if Capsule2_0_SUPPORT

#else
  #if CAPSULE_SUPPORT
    if (!EFI_ERROR(CheckIfCapsuleAvailable()))
        BootMode = BOOT_ON_FLASH_UPDATE;
  #endif
#endif
    // Set the system BootMode
    (*PeiServices)->SetBootMode(PeiServices, BootMode);

    // Let everyone know that boot mode has been determined by installing the
    // MasterBootMode PPI
    (*PeiServices)->InstallPpi(PeiServices, mBootModePpi );

    (*PeiServices)->GetBootMode (PeiServices, &BootMode); 

    if (BootMode == BOOT_IN_RECOVERY_MODE) // Recovery Boot Mode PPI
        (*PeiServices)->InstallPpi( PeiServices, mRecoveryModePpi );

                                        // [EIP87695]>
#if SYSTEM_REBOOT_NORMALLY_IF_S3_IS_FAILED
    if (BootMode == BOOT_ON_S3_RESUME) //S3 Boot Mode PPI
        WRITE_IO16_PM(ACPI_IOREG_PM1_CNTL, READ_IO16_PM(ACPI_IOREG_PM1_CNTL) & 0xe3ff ); // Clear S3 for avoiding S3 resume twice
#endif
                                        // <[EIP87695]

    return EFI_SUCCESS;
}

#if defined(SUPPORT_RAID_DRIVER) && SUPPORT_RAID_DRIVER && (PTT_VER > 15)
//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:   DetectSataPortInfo
//
// Description: This function provides SATA Port Information
//
// Input:       PeiServices - Pointer to the PEI services table
//
// Output:      None
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

VOID DetectSataPortInfo (
    IN EFI_PEI_SERVICES     **PeiServices)
{
    EFI_STATUS          Status;
    UINT16              HobSize = sizeof(SATA_PRESENT_HOB);
    EFI_GUID            SataPresentHobGuid = AMI_SATA_PRESENT_HOB_GUID;
    SATA_PRESENT_HOB    *SataPresentHob;
    UINT16              SataClassCode;
    UINT8               SataPortStatus;
    UINT8               SataPortEnable = 0;
    SB_SETUP_DATA       SbSetupData;
    UINT8               i;

    Status = (*PeiServices)->CreateHob (PeiServices,
                                        EFI_HOB_TYPE_GUID_EXTENSION,
                                        HobSize,
                                        &SataPresentHob);
    if(EFI_ERROR(Status)) return;

    SataPresentHob->EfiHobGuidType.Name = SataPresentHobGuid;

    for (i = 0; i < 4; i++) {
      SataPresentHob->SataInfo[i].ClassCode = 0;
      SataPresentHob->SataInfo[i].PresentPortBitMap = 0;
    }

    // The SATA Mode Select should be configured in PchInitPeim.
    SataClassCode = READ_PCI16_SATA(R_PCH_SATA_SUB_CLASS_CODE);
    SataPresentHob->SataInfo[0].ClassCode = SataClassCode;

    if ((SataClassCode & 0xFF) == V_PCH_SATA_SUB_CLASS_CODE_IDE) {
      // Lynx Point-LP didn't support IDE mode, so code should not enter here.
      SataPortStatus = READ_PCI16_SATA(R_PCH_SATA_PCS) >> 8;
      SataPresentHob->SataInfo[0].PresentPortBitMap = (SATA1_BDF << 16) | (SataPortStatus & 0xF); // Port 0~3
      SataPortStatus = READ_PCI16_SATA2(R_PCH_SATA_PCS) >> 8;
      SataPresentHob->SataInfo[1].PresentPortBitMap = (SATA2_BDF << 16) | (SataPortStatus & 0x3); // Port 4~5
      SataPresentHob->SataInfo[1].ClassCode = SataClassCode;
      SataPresentHob->ControllerCount = 2;
    } else { // AHCI or Raid
      GetSbSetupData (PeiServices, &SbSetupData, TRUE);
      SataPortStatus = READ_PCI16_SATA(R_PCH_SATA_PCS) >> 8;
      for (i = 0; i < GetPchMaxSataPortNum(); i++) {
        // SataPort controll is done in DXE, so check Setup value here.
        SataPortEnable |= (SbSetupData.SataPort[i] << i);
      }
      SataPortStatus &= SataPortEnable;
      SataPresentHob->SataInfo[0].PresentPortBitMap = (SATA1_BDF << 16) | (SataPortStatus & 0x3F); // Port 0~5
      SataPresentHob->ControllerCount = 1;
    }
}
#endif

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:   SBPEI_Init
//
// Description: This function is the entry point for this PEI. This function
//              initializes the chipset SB
//
// Input:       FfsHeader   - Pointer to the FFS file header
//              PeiServices - Pointer to the PEI services table
//
// Output:      Return Status based on errors that occurred while waiting for
//              time to expire.
//
// Notes:       This function should initialize South Bridge for memory 
//              detection.
//              Install AMI_PEI_SBINIT_POLICY_PPI to indicate that SB Init
//              PEIM is installed
//              Following things can be done at this point:
//                  - Enabling top of 4GB decode for full flash ROM
//                  - Programming South Bridge ports to enable access to
//                    South Bridge and other I/O bridge access
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS EFIAPI SBPEI_Init (
    IN EFI_FFS_FILE_HEADER      *FfsHeader,
    IN EFI_PEI_SERVICES         **PeiServices )
{
    EFI_STATUS                  Status;
    IN EFI_PEI_PCI_CFG2_PPI     *PciCfg;
    EFI_PEI_CPU_IO_PPI          *CpuIo;
    AMI_PEI_PCI_TABLE_INIT_PPI  *AMIPCITableInit;
    SB_SETUP_DATA               SbSetupData;
    AMI_GPIO_INIT_TABLE_STRUCT  *pTable;
    AMI_PEI_SB_CUSTOM_PPI       *SBPeiOemPpi = NULL;
	  PCH_SERIES PchSeries = GetPchSeries();

    // Get pointer to the PCI config PPI
    PciCfg = (*PeiServices)->PciCfg;
    CpuIo = (*PeiServices)->CpuIo;

    PEI_PROGRESS_CODE (PeiServices, PEI_CAR_SB_INIT);
    WRITE_IO8(PORTB_IO_CNTL, 0x0c); // Disable IOCHK NMI #, PCI SERR#. (0x61)

    // Locate AMI PCI Table Init PPI
    Status = (*PeiServices)->LocatePpi( PeiServices, \
                                        &gAmiPEIPCITableInitPpiGuid, \
                                        0, \
                                        NULL, \
                                        &AMIPCITableInit );

    // Assert if not found - the AMI PCI Table Init PPI should exist
    ASSERT_PEI_ERROR( PeiServices, Status );

    GetSbSetupData( PeiServices, &SbSetupData, TRUE );

#if WdtPei_SUPPORT
{
    WDT_PPI                     *WdtPpi;

    // Locate WDT PPI for access to Wdt->Disable()
    //
    Status = (*PeiServices)->LocatePpi (
                      PeiServices,
                      &gWdtPpiGuid,
                      0,
                      NULL,
                      &WdtPpi
                      );
    if (!EFI_ERROR (Status)) {
        WdtPpi->Disable();
    }
}
#endif
    // Program Pch devices bar base
    ProgramPchDeviceBase(PeiServices, PciCfg);

#if SB_STALL_PPI_SUPPORT
    // Install the SB Stall PPI
    Status = (*PeiServices)->InstallPpi( PeiServices, \
                                         &mBeforeBootModePpiList[0] );
    ASSERT_PEI_ERROR( PeiServices, Status );
#endif

    // Program Pch RCBA base
    ProgramRCRBMmio(PeiServices, CpuIo);

    UpdateBootMode( PeiServices, CpuIo, PciCfg );

    // Install PchPlatformPolicyPpi, it will notify to PchInitialize.
    InstallPchPlatformPolicyPpi( PeiServices, &SbSetupData);

    //DeCode LPC IO
    ProgramSBIoDecodeRegs( PeiServices, PciCfg);

    //Program GPIOs.
    //Program the default GPIO Setting for chipset.
#if defined PROGRAM_DEFAULT_GPIO && PROGRAM_DEFAULT_GPIO == 1
	if (PchSeries == PchLp) {
		pTable = stSB_GPIODefaultULTInitTable;
	}else{
    	pTable = stSB_GPIODefaultInitTable;
	}
		
    ProgramGPIO( PeiServices, \
                 CpuIo, \
                 &SbSetupData, \
                 pTable);
#endif

    //Program the OEM GPIO Setting for board.
    Status = (*PeiServices)->LocatePpi( PeiServices, \
                                        &gAmiPeiSBCustomPpiGuid, \
                                        0, \
                                        NULL, \
                                        &SBPeiOemPpi );

    if (Status == EFI_SUCCESS) {
        if (SBPeiOemPpi->GpioInit != NULL) {
            pTable = SBPeiOemPpi->GpioInit->GpioTable;
            ProgramGPIO( PeiServices, \
                         CpuIo, \
                         &SbSetupData, \
                         pTable);
        }
    } else {
      SBPeiOemPpi = NULL;
    }

    // Program SB Devices' Subsystem Vendor ID & Subsystem ID
    ProgramSBSubId( PeiServices, PciCfg, SBPeiOemPpi );

    //Program PM Regs.
    InitPMRegs(PeiServices, CpuIo, &SbSetupData);
   
    // General power failure handling
    GeneralPowerFailureHandler(PeiServices, CpuIo, PciCfg);

    InitRTC( PeiServices, CpuIo );
  
    // Set what state (S0/S5) to go to when power is re-applied after a power failure (G3 state)
    SetTheStateToGoAfterG3(PeiServices, CpuIo, PciCfg, &SbSetupData);
 
    InitPCIe( PeiServices, CpuIo, PciCfg );

    InitSMBus( PeiServices, CpuIo, PciCfg );


    // Install the SB Init Policy PPI
    Status = (*PeiServices)->InstallPpi( PeiServices, &mPpiList[0] );
    ASSERT_PEI_ERROR( PeiServices, Status );

    // Setup a SBPEI entry after PEI permantent memory be installed

    Status = (*PeiServices)->NotifyPpi( PeiServices, AfterMrcNotifyList );

    Status = (*PeiServices)->NotifyPpi ( PeiServices, mMemoryReadyNotify );
    ASSERT_PEI_ERROR( PeiServices, Status );

#if defined iME_SUPPORT && iME_SUPPORT == 0
    if (!IsS3(PeiServices, CpuIo)) {
        WRITE_IO16_PM(ACPI_IOREG_PM1_CNTL, 0x20); // Clear Sleep Type
    }
#endif

    return EFI_SUCCESS;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:   ProgramGPIO
//
// Description: This function initializes SB GPIOs
//
// Input:       PeiServices - Pointer to the PEI services table
//              CpuIo       - Pointer to the CPU I/O PPI
//
// Output:      None
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

VOID ProgramGPIO (
    IN EFI_PEI_SERVICES     **PeiServices,
    IN EFI_PEI_CPU_IO_PPI   *CpuIo,
    IN SB_SETUP_DATA        *SbSetupData,
    IN AMI_GPIO_INIT_TABLE_STRUCT *pTable
)
{
    UINT16 i;
    UINT32 OWN1;
    UINT32 OWN2;
    UINT32 OWN3;
    UINT32 GPN_CFG1[96];
    UINT32 GPN_CFG2[96];
    UINT32 USE1_SEL;
    UINT32 USE2_SEL;
    UINT32 USE3_SEL;
    UINT32 IO1_SEL;
    UINT32 IO2_SEL;
    UINT32 IO3_SEL;
    UINT32 LVL1_SEL;
    UINT32 LVL2_SEL;
    UINT32 LVL3_SEL;
    UINT32 INV1_SEL;
    UINT32 RST1_SEL;
    UINT32 RST2_SEL;
    UINT32 RST3_SEL;
    UINT32 BLNK_SEL;
    UINT32 INT1_SEL;
    UINT32 INT2_SEL;
    UINT32 INT3_SEL;
    UINT16 Offset;
    UINT16 LpcDeviceId;
    PCH_SERIES PchSeries = GetPchSeries();

    LpcDeviceId = READ_PCI16_SB(R_PCH_LPC_DEVICE_ID);

    if (pTable[0].GpioNo != 0xffff) {
        if (PchSeries == PchLp) {
          OWN1 = READ_IO32(GPIO_BASE_ADDRESS + GP_IOREG_GP_OWN1);   // 0x00
          OWN2 = READ_IO32(GPIO_BASE_ADDRESS + GP_IOREG_GP_OWN2);   // 0x04
          OWN3 = READ_IO32(GPIO_BASE_ADDRESS + GP_IOREG_GP_OWN3);   // 0x08
          INT1_SEL = READ_IO32(GPIO_BASE_ADDRESS + GP_IOREG_GP_INT_SEL1);   // 0x90
          INT2_SEL = READ_IO32(GPIO_BASE_ADDRESS + GP_IOREG_GP_INT_SEL2);   // 0x94
          INT3_SEL = READ_IO32(GPIO_BASE_ADDRESS + GP_IOREG_GP_INT_SEL3);   // 0x98
        } else {
          USE1_SEL = READ_IO32(GPIO_BASE_ADDRESS + GP_IOREG_USE_SEL);     // 0x00
          IO1_SEL  = READ_IO32(GPIO_BASE_ADDRESS + GP_IOREG_IO_SEL);      // 0x04
          LVL1_SEL = READ_IO32(GPIO_BASE_ADDRESS + GP_IOREG_GP_LVL);      // 0x0C
          INV1_SEL = READ_IO32(GPIO_BASE_ADDRESS + GP_IOREG_GPI_INV);     // 0x2C

          USE2_SEL = READ_IO32(GPIO_BASE_ADDRESS + GP_IOREG_USE_SEL2);    // 0x30
          IO2_SEL  = READ_IO32(GPIO_BASE_ADDRESS + GP_IOREG_IO_SEL2);     // 0x34
          LVL2_SEL = READ_IO32(GPIO_BASE_ADDRESS + GP_IOREG_GP_LVL2);     // 0x38

          USE3_SEL = READ_IO32(GPIO_BASE_ADDRESS + GP_IOREG_USE_SEL3);    // 0x40
          IO3_SEL  = READ_IO32(GPIO_BASE_ADDRESS + GP_IOREG_IO_SEL3);     // 0x44
          LVL3_SEL = READ_IO32(GPIO_BASE_ADDRESS + GP_IOREG_GP_LVL3);     // 0x48
        }
        BLNK_SEL = READ_IO32(GPIO_BASE_ADDRESS + GP_IOREG_GPO_BLINK);   // 0x18
        RST1_SEL = READ_IO32(GPIO_BASE_ADDRESS + GP_IOREG_GP_RST_SEL1); // 0x60
        RST2_SEL = READ_IO32(GPIO_BASE_ADDRESS + GP_IOREG_GP_RST_SEL2); // 0x64
        RST3_SEL = READ_IO32(GPIO_BASE_ADDRESS + GP_IOREG_GP_RST_SEL3); // 0x68

        for (i = 0; pTable[i].GpioNo != 0xffff; i++) {

          Offset = pTable[i].GpioNo;
            if (PchSeries == PchLp) {
              GPN_CFG1[Offset] = READ_IO32(GPIO_BASE_ADDRESS + (GP_IOREG_GP_GPN_CFG1 + GP_GPIO_CONFIG_SIZE*Offset));  // 0x100 + n*8h
              GPN_CFG2[Offset] = READ_IO32(GPIO_BASE_ADDRESS + (GP_IOREG_GP_GPN_CFG2 + GP_GPIO_CONFIG_SIZE*Offset));  // 0x104 + n*8h

              GPN_CFG1[Offset] =  (GPN_CFG1[Offset] & ~(BIT31))	| (pTable[i].GpioCfg.Fileds.LVL << 31);
              GPN_CFG1[Offset] =  (GPN_CFG1[Offset] & ~(BIT4))	| (pTable[i].GpioCfg.Fileds.LEB << 4);
              GPN_CFG1[Offset] =  (GPN_CFG1[Offset] & ~(BIT3))	| (pTable[i].GpioCfg.Fileds.INV << 3);
              GPN_CFG1[Offset] =  (GPN_CFG1[Offset] & ~(BIT2))	| (pTable[i].GpioCfg.Fileds.IO << 2);
              GPN_CFG1[Offset] =  (GPN_CFG1[Offset] & ~(1))	| (pTable[i].GpioCfg.Fileds.USE);
              GPN_CFG2[Offset] =  (GPN_CFG2[Offset] & ~(BIT2))	| (pTable[i].GpioCfg.Fileds.DIS << 2);
			                                                                              //(EIP118667)>>
              if(pTable[i].GpioCfg.Fileds.IO == 0 && pTable[i].GpioCfg.Fileds.USE == 1){
                GPN_CFG2[Offset] =  (GPN_CFG2[Offset] & ~(BIT2))	| (BIT2);
              }
			                                                                              //(EIP118667)<<
              GPN_CFG2[Offset] =  (GPN_CFG2[Offset] & ~(3))	| (pTable[i].GpioCfg.Fileds.WP);	
            }

          if (Offset < 32) {
            if (PchSeries == PchLp) {
              OWN1 = (OWN1 & ~(1 << Offset)) | (pTable[i].GpioCfg.Fileds.OWN << Offset);
              INT1_SEL = (INT1_SEL & ~(1 << Offset)) | (pTable[i].GpioCfg.Fileds.INT << Offset);
            } else {
              USE1_SEL = (USE1_SEL & ~(1 << Offset)) | (pTable[i].GpioCfg.Fileds.USE << Offset);
              IO1_SEL  = (IO1_SEL  & ~(1 << Offset)) | (pTable[i].GpioCfg.Fileds.IO  << Offset);
              LVL1_SEL = (LVL1_SEL & ~(1 << Offset)) | (pTable[i].GpioCfg.Fileds.LVL << Offset);
              INV1_SEL = (INV1_SEL & ~(1 << Offset)) | (pTable[i].GpioCfg.Fileds.INV << Offset);
            }
            RST1_SEL = (RST1_SEL & ~(1 << Offset)) | (pTable[i].GpioCfg.Fileds.RST << Offset);
            BLNK_SEL = (BLNK_SEL & ~(1 << Offset)) | (pTable[i].GpioCfg.Fileds.BLK << Offset);
          } else if ((Offset >= 32) && (Offset < 64)) {
            if (PchSeries == PchLp) {
              OWN2 = (OWN2 & ~(1 << (Offset - 32))) | (pTable[i].GpioCfg.Fileds.OWN << (Offset - 32));
              INT2_SEL = (INT2_SEL & ~(1 << (Offset - 32))) | (pTable[i].GpioCfg.Fileds.INT << (Offset - 32));
            } else {
              USE2_SEL = (USE2_SEL & ~(1 << (Offset - 32))) | (pTable[i].GpioCfg.Fileds.USE << (Offset - 32));
              IO2_SEL  = (IO2_SEL  & ~(1 << (Offset - 32))) | (pTable[i].GpioCfg.Fileds.IO  << (Offset - 32));
              LVL2_SEL = (LVL2_SEL & ~(1 << (Offset - 32))) | (pTable[i].GpioCfg.Fileds.LVL << (Offset - 32));
            }
            RST2_SEL = (RST2_SEL & ~(1 << (Offset - 32))) | (pTable[i].GpioCfg.Fileds.RST << (Offset - 32));
          } else {
            if (PchSeries == PchLp) {
              OWN3 = (OWN3 & ~(1 << (Offset - 64))) | (pTable[i].GpioCfg.Fileds.OWN << (Offset - 64));
              INT3_SEL = (INT3_SEL & ~(1 << (Offset - 64))) | (pTable[i].GpioCfg.Fileds.INT << (Offset - 64));
            } else {
              USE3_SEL = (USE3_SEL & ~(1 << (Offset - 64))) | (pTable[i].GpioCfg.Fileds.USE << (Offset - 64));
              IO3_SEL  = (IO3_SEL  & ~(1 << (Offset - 64))) | (pTable[i].GpioCfg.Fileds.IO  << (Offset - 64));
              LVL3_SEL = (LVL3_SEL & ~(1 << (Offset - 64))) | (pTable[i].GpioCfg.Fileds.LVL << (Offset - 64));
            }
            RST3_SEL = (RST3_SEL & ~(1 << (Offset - 64))) | (pTable[i].GpioCfg.Fileds.RST << (Offset - 64));
          }
            if (PchSeries == PchLp) {
              WRITE_IO32(GPIO_BASE_ADDRESS + (GP_IOREG_GP_GPN_CFG1 + GP_GPIO_CONFIG_SIZE*Offset), GPN_CFG1[Offset]);   // 0x100 + n*8h
              WRITE_IO32(GPIO_BASE_ADDRESS + (GP_IOREG_GP_GPN_CFG2 + GP_GPIO_CONFIG_SIZE*Offset), GPN_CFG2[Offset]);   // 0x104 + n*8h
            }
        }

        if (PchSeries == PchLp) {
          WRITE_IO32(GPIO_BASE_ADDRESS + GP_IOREG_GP_OWN1, OWN1);   // 0x00
          WRITE_IO32(GPIO_BASE_ADDRESS + GP_IOREG_GP_OWN2, OWN2);   // 0x04
          WRITE_IO32(GPIO_BASE_ADDRESS + GP_IOREG_GP_OWN3, OWN3);   // 0x08
          WRITE_IO32(GPIO_BASE_ADDRESS + GP_IOREG_GP_INT_SEL1, INT1_SEL);   // 0x90
          WRITE_IO32(GPIO_BASE_ADDRESS + GP_IOREG_GP_INT_SEL2, INT2_SEL);   // 0x94
          WRITE_IO32(GPIO_BASE_ADDRESS + GP_IOREG_GP_INT_SEL3, INT3_SEL);   // 0x98
          WRITE_IO32(GPIO_BASE_ADDRESS + GPI_IRQ_2_IOAPIC, GPI_IRQ_2_IOXAPIC);   // 0x10
        } else {
          WRITE_IO32(GPIO_BASE_ADDRESS + GP_IOREG_USE_SEL,     USE1_SEL);   // 0x00
          WRITE_IO32(GPIO_BASE_ADDRESS + GP_IOREG_IO_SEL,      IO1_SEL);    // 0x04
          WRITE_IO32(GPIO_BASE_ADDRESS + GP_IOREG_GP_LVL,      LVL1_SEL);   // 0x0C

          WRITE_IO32(GPIO_BASE_ADDRESS + GP_IOREG_GPI_INV,     INV1_SEL);   // 0x2C

          WRITE_IO32(GPIO_BASE_ADDRESS + GP_IOREG_USE_SEL2,    USE2_SEL);   // 0x30
          WRITE_IO32(GPIO_BASE_ADDRESS + GP_IOREG_IO_SEL2,     IO2_SEL);    // 0x34
          WRITE_IO32(GPIO_BASE_ADDRESS + GP_IOREG_GP_LVL2,     LVL2_SEL);   // 0x38

          WRITE_IO32(GPIO_BASE_ADDRESS + GP_IOREG_USE_SEL3,    USE3_SEL);   // 0x40
          WRITE_IO32(GPIO_BASE_ADDRESS + GP_IOREG_IO_SEL3,     IO3_SEL);    // 0x44
          WRITE_IO32(GPIO_BASE_ADDRESS + GP_IOREG_GP_LVL3,     LVL3_SEL);   // 0x48
        }
        WRITE_IO32(GPIO_BASE_ADDRESS + GP_IOREG_GPO_BLINK,   BLNK_SEL);   // 0x18
        WRITE_IO32(GPIO_BASE_ADDRESS + GP_IOREG_GP_RST_SEL1, RST1_SEL);   // 0x60
        WRITE_IO32(GPIO_BASE_ADDRESS + GP_IOREG_GP_RST_SEL2, RST2_SEL);   // 0x64
        WRITE_IO32(GPIO_BASE_ADDRESS + GP_IOREG_GP_RST_SEL3, RST3_SEL);   // 0x68
    }

    // BIOS implementation for SUS_PWR_DN_ACK
    // As soon as platform BARs are initialized, BIOS must ensure that the following things
    // are set high on all boot flows:
    // (1) GPIO_BASE_ADDRESS + 0x60[30]
    // (2) GPIO[30] pin (GPIO_BASE_ADDRESS + GP_LVL) (Done in GPIO.SDL)
    if (IS_PCH_LPT_LPC_DEVICE_ID_MOBILE (LpcDeviceId)) {
       SET_IO32 (GPIO_BASE_ADDRESS + GP_IOREG_GP_RST_SEL1, BIT30); // 0x60
    }
    //
    // Now enable LANPHY_PC GPIO if LAN is enabled in the setup.
    // Enabling this GPIO for all the boards. Both Red Fort and Buffalo Trail uses GPIO12 for this.
    // Electric Peak does not use GPIO12, so changing the value for all boards should not effect
    if (SbSetupData->PchLan) {
      if (PchSeries == PchLp) {
        SET_IO32 (GPIO_BASE_ADDRESS + (GP_IOREG_GP_GPN_CFG1 + GP_GPIO_CONFIG_SIZE*22), BIT31); // 0x190
      } else {
        SET_IO32 (GPIO_BASE_ADDRESS + GP_IOREG_GP_LVL, BIT12); // 0x0C
      }
    }

    // Clear GPI Status 
    if (PchSeries == PchLp) {
      WRITE_IO16_PM(ACPI_PCHLP_IOREG_GPE0_STS, 0xffff); // 0x80
      WRITE_IO16_PM(ACPI_PCHLP_IOREG_GPE0_STS + 4, 0xffff); // 0x84
      WRITE_IO16_PM(ACPI_PCHLP_IOREG_GPE0_STS + 8, 0xffff); // 0x88
    } else {
      WRITE_IO16_PM(ACPI_IOREG_GPE0_STS + 2, 0xffff); // 0x22
    }
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:   IsSBDevice
//
// Description: This function detimines SB PCI devices
//
// Input:       UINT64 PciAddress
//              UINT8  *PciSidReg
//
// Output:      EFI_STATUS
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS IsSBDevice(
    IN UINT64    PciAddress,
    IN OUT UINT8 *PciSidReg
)
{
    UINT8  i;
    AMI_SB_PCI_DEVICES_TABLE_STRUCT PchDeviceTable[] = { HECI_BUS_DEV_FUN,     ME_REG_SVID,
                                                         HECI2_BUS_DEV_FUN,    ME_REG_SVID,
                                                         IDER_BUS_DEV_FUN,     ME_REG_SVID,
                                                         KT_BUS_DEV_FUN,       ME_REG_SVID,
                                                         XHCI_BUS_DEV_FUN,     XHCI_REG_SVID,
                                                         LAN_BUS_DEV_FUN,      LAN_REG_SVID,
                                                         EHCI2_BUS_DEV_FUN,    EHCI_REG_SVID,
                                                         HDA_BUS_DEV_FUN,      HDA_REG_SVID,
                                                         PCIEBRS_BUS_DEV_FUN,  PCIEBRS_REG_SVID,
                                                         PCIEBRS2_BUS_DEV_FUN, PCIEBRS_REG_SVID,
                                                         PCIEBRS3_BUS_DEV_FUN, PCIEBRS_REG_SVID,
                                                         PCIEBRS4_BUS_DEV_FUN, PCIEBRS_REG_SVID,
                                                         PCIEBRS5_BUS_DEV_FUN, PCIEBRS_REG_SVID,
                                                         PCIEBRS6_BUS_DEV_FUN, PCIEBRS_REG_SVID,
                                                         PCIEBRS7_BUS_DEV_FUN, PCIEBRS_REG_SVID,
                                                         PCIEBRS8_BUS_DEV_FUN, PCIEBRS_REG_SVID,
                                                         PCIBR_BUS_DEV_FUN,    PCIBR_REG_SVID,
                                                         EHCI_BUS_DEV_FUN,     EHCI_REG_SVID,
                                                         SB_BUS_DEV_FUN,       R_PCH_LPC_SS,
                                                         SATA_BUS_DEV_FUN,     SATA_REG_SVID,
                                                         SMBUS_BUS_DEV_FUN,    SMBUS_REG_SVID,
                                                         SATA2_BUS_DEV_FUN,    SATA_REG_SVID,
                                                         THERMAL_BUS_DEV_FUN,  R_PCH_LPC_SS
                                                       };
    UINT32 TableSize = sizeof(PchDeviceTable) / sizeof(AMI_SB_PCI_DEVICES_TABLE_STRUCT);

    for (i = 0; i < TableSize; i++) {

      if (PciAddress != PchDeviceTable[i].PciAddr) {
        continue;
      } else {
        if (READ_PCI32((UINT8)(Shr64(PchDeviceTable[i].PciAddr, 24) & 0xff), \
                       (UINT8)(Shr64(PchDeviceTable[i].PciAddr, 16) & 0xff), \
                       (UINT8)(Shr64(PchDeviceTable[i].PciAddr, 8) & 0xff), \
                        0) == 0xffffffff) 
           return EFI_UNSUPPORTED;

        *PciSidReg = PchDeviceTable[i].PciSidReg;
        return EFI_SUCCESS;
      }
    }
    return EFI_UNSUPPORTED;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:   ProgramSBSubId
//
// Description: This function programs SB PCI devices sub-vendor ID and
//              sub-system ID.
//
// Input:       PeiServices - Pointer to the PEI services table
//              PciCfg      - Pointer to the PCI Configuration PPI
//
// Output:      VOID
//
// Notes:       1. This routine only programs the PCI device in SB, hence, we
//                 have to check the bus/device/function numbers whether they
//                 are a SB PCI device or not.
//              2. This routine is invoked by PEI phase.(After PEI permantent
//                 memory be installed)
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

VOID ProgramSBSubId (
    IN EFI_PEI_SERVICES         **PeiServices,
    IN EFI_PEI_PCI_CFG2_PPI     *PciCfg,
    IN AMI_PEI_SB_CUSTOM_PPI    *SBPeiOemPpi
)
{
    EFI_STATUS                  Status = EFI_SUCCESS;
    UINTN                       i = 0;
    UINT32                      PciSid = 0xffffffff;
    UINT8                       PciSidReg = 0xff;
    AMI_SB_PCI_SSID_TABLE_STRUCT DefaultSIdTbl[] = {SB_PCI_DEVICES_SSID_TABLE};
    AMI_SB_PCI_SSID_TABLE_STRUCT *SsidTblPtr = DefaultSIdTbl;

    if ((SBPeiOemPpi != NULL) && (SBPeiOemPpi->SsidTable != NULL))
      SsidTblPtr = SBPeiOemPpi->SsidTable;

    while (SsidTblPtr[i].PciAddr != 0xffffffffffffffff) {
        if (IsSBDevice(SsidTblPtr[i].PciAddr, &PciSidReg) == EFI_SUCCESS) {
            if (SsidTblPtr[i].Sid == 0xffffffff) {
                Status = PciCfg->Read( PeiServices,
                                       PciCfg,
                                       EfiPeiPciCfgWidthUint32,
                                       SsidTblPtr[i].PciAddr,
                                       &PciSid);
            } else {
                PciSid = SsidTblPtr[i].Sid;
            }

            if (SsidTblPtr[i].PciAddr == EHCI_BUS_DEV_FUN)
              SET_PCI8_EHCI(R_PCH_EHCI_ACCESS_CNTL, 1);
            else if (SsidTblPtr[i].PciAddr == EHCI2_BUS_DEV_FUN)
              SET_PCI8_EHCI2(R_PCH_EHCI_ACCESS_CNTL, 1);

            Status = PciCfg->Write( PeiServices,
                                    PciCfg,
                                    EfiPeiPciCfgWidthUint32,
                                    SsidTblPtr[i].PciAddr | PciSidReg,
                                    &PciSid);

            if (SsidTblPtr[i].PciAddr == EHCI_BUS_DEV_FUN)
              RESET_PCI8_EHCI(R_PCH_EHCI_ACCESS_CNTL, 1);
            else if (SsidTblPtr[i].PciAddr == EHCI2_BUS_DEV_FUN)
              RESET_PCI8_EHCI2(R_PCH_EHCI_ACCESS_CNTL, 1);
        }
        i++;
    }
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:   InitPCIe
//
// Description: This function initializes SB PCI Express controller(s)
//
// Input:       PeiServices - Pointer to the PEI services table
//              CpuIo       - Pointer to the CPU I/O PPI
//              PciCfg      - Pointer to the PCI Configuration PPI
//
// Output:      None
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

VOID InitPCIe (
    IN EFI_PEI_SERVICES     **PeiServices,
    IN EFI_PEI_CPU_IO_PPI   *CpuIo,
    IN EFI_PEI_PCI_CFG2_PPI     *PciCfg
)
{
    // TODO
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:   InitSMBus
//
// Description: This function initializes SB SMBUS controller(s)
//
// Input:       PeiServices - Pointer to the PEI services table
//              CpuIo       - Pointer to the CPU I/O PPI
//              PciCfg      - Pointer to the PCI Configuration PPI
//
// Output:      None
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

VOID InitSMBus (
    IN EFI_PEI_SERVICES     **PeiServices,
    IN EFI_PEI_CPU_IO_PPI   *CpuIo,
    IN EFI_PEI_PCI_CFG2_PPI     *PciCfg
)
{
    // TODO
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:   InitUsbMisc
//
// Description: Miscellaneous USB initialization.
//
// Input:       PeiServices - Pointer to the PEI services table
//              CpuIo       - Pointer to the CPU I/O PPI
//              PciCfg      - Pointer to the PCI Configuration PPI
//              BootMode    - Boot Mode
//
// Output:      None
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

VOID InitUsbMisc (
    IN EFI_PEI_SERVICES     **PeiServices,
    IN EFI_PEI_CPU_IO_PPI   *CpuIo,
    IN EFI_PEI_PCI_CFG2_PPI *PciCfg,
    IN EFI_BOOT_MODE        BootMode
)
{
  PCH_SERIES PchSeries = GetPchSeries();
#ifndef PEI_XHCI_MMIOBASE
  UINT32      XhciMmioBase = 0xFE400000;                           //[EIP156783]
#else
  UINT32      XhciMmioBase = PEI_XHCI_MMIOBASE;                    //[EIP115528] >>
#endif
  UINT8       XhciCapLength;
  UINT8       XhciMaxPorts;
  UINT32      XhciPort;
  EFI_PEI_STALL_PPI   *StallPpi;
  StallPpi = &mStallPpi;

if ((BootMode == BOOT_IN_RECOVERY_MODE) || (BootMode == BOOT_ON_FLASH_UPDATE)) {       
    WRITE_PCI32( DEFAULT_PCI_BUS_NUMBER_PCH, \
                 PCI_DEVICE_NUMBER_PCH_XHCI, \
                 PCI_FUNCTION_NUMBER_PCH_XHCI, \
                 0x10, \
                 XhciMmioBase);
    WRITE_PCI8( DEFAULT_PCI_BUS_NUMBER_PCH, \
                 PCI_DEVICE_NUMBER_PCH_XHCI, \
                 PCI_FUNCTION_NUMBER_PCH_XHCI, \
                 0x04, \
                 0x06);    
    WRITE_PCI8( DEFAULT_PCI_BUS_NUMBER_PCH, \
                 PCI_DEVICE_NUMBER_PCH_XHCI, \
                 PCI_FUNCTION_NUMBER_PCH_XHCI, \
                 R_PCH_XHCI_USB3PR, \
                 0x3F);
    
    //Add some delay to wait that device links are stable
    StallPpi->Stall(PeiServices, StallPpi, 500 * 1000); 
    
    XhciCapLength = READ_MEM8(XhciMmioBase);
    if (PchSeries == PchH) {
        switch ((READ_MEM8(XhciMmioBase + R_PCH_XHCI_FUS)) & B_PCH_XHCI_FUS_SSPRTCNT) {
            case V_PCH_XHCI_FUS_SSPRTCNT_11B:
                XhciMaxPorts = 0x0F;
                break;

            case V_PCH_XHCI_FUS_SSPRTCNT_10B:
                XhciMaxPorts = 0x11;
                break;

            case V_PCH_XHCI_FUS_SSPRTCNT_01B:
                XhciMaxPorts = 0x13;
                break;

            case V_PCH_XHCI_FUS_SSPRTCNT_00B:
            default:
                XhciMaxPorts = 0x15;
                break;
        }
    } else {
        XhciMaxPorts = READ_MEM8(XhciMmioBase + 0x7);
    }
    //Clear each xHCI port power
    for (XhciPort = 0; XhciPort < XhciMaxPorts; XhciPort++) {
      RESET_MEM32(XhciMmioBase + XhciCapLength + 0x400 + (0x10 * XhciPort), BIT9);
    }
    // Set xHCI D0h & D8h as power-on default value.
    WRITE_PCI16( DEFAULT_PCI_BUS_NUMBER_PCH, \
                 PCI_DEVICE_NUMBER_PCH_XHCI, \
                 PCI_FUNCTION_NUMBER_PCH_XHCI, \
                 R_PCH_XHCI_USB2PR, \
                 0 );
    WRITE_PCI8( DEFAULT_PCI_BUS_NUMBER_PCH, \
                 PCI_DEVICE_NUMBER_PCH_XHCI, \
                 PCI_FUNCTION_NUMBER_PCH_XHCI, \
                 R_PCH_XHCI_USB3PR, \
                 0 );
    WRITE_PCI8( DEFAULT_PCI_BUS_NUMBER_PCH, \
                 PCI_DEVICE_NUMBER_PCH_XHCI, \
                 PCI_FUNCTION_NUMBER_PCH_XHCI, \
                 0x04, \
                 0);
    WRITE_PCI32( DEFAULT_PCI_BUS_NUMBER_PCH, \
                 PCI_DEVICE_NUMBER_PCH_XHCI, \
                 PCI_FUNCTION_NUMBER_PCH_XHCI, \
                 0x10, \
                 0);
  }


                                        // [EIP107424] [EIP123117]>
  if (BootMode != BOOT_ON_S3_RESUME) { 
    //
    // Clear unexpected USB EHCI Legacy Support Extended status.
    // Set B0:D1A/1D:F0 Reg#6Ch[31:29] = '111b'.
    //
    WRITE_PCI32_EHCI  ( R_PCH_EHCI_LEGEXT_CS, \
                      B_PCH_EHCI_LEGEXT_CS_SMIBAR | \
                      B_PCH_EHCI_LEGEXT_CS_SMIPCI | \
                      B_PCH_EHCI_LEGEXT_CS_SMIOS);
    if (PchSeries == PchH) {
      WRITE_PCI32_EHCI ( R_PCH_EHCI_LEGEXT_CS, \
                        B_PCH_EHCI_LEGEXT_CS_SMIBAR | \
                        B_PCH_EHCI_LEGEXT_CS_SMIPCI | \
                        B_PCH_EHCI_LEGEXT_CS_SMIOS);
    }                                    
  }
                                        // <[EIP107424] [EIP123117]    
										//[EIP115528]<<
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:   ProgramSBRegAfterMemInstalled
//
// Description: This function can be used to program any SB regisater after
//              PEI permantent memory be installed.
//
// Input:       FfsHeader        - Pointer to the desired FFS header.
//              PeiServices      - Pointer to the PEI services table.
//
// Output:      EFI_STATUS
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS ProgramSBRegAfterMemInstalled (
    IN EFI_PEI_SERVICES         **PeiServices,
    IN EFI_PEI_NOTIFY_DESCRIPTOR *NotifyDescriptor,
    IN VOID                     *InvokePpi )
{
    EFI_STATUS                  Status = EFI_SUCCESS;
    EFI_PEI_CPU_IO_PPI          *CpuIo;
    IN EFI_PEI_PCI_CFG2_PPI     *PciCfg;
    EFI_BOOT_MODE               BootMode;
    EFI_PEI_READ_ONLY_VARIABLE2_PPI *ReadOnlyVariable;
    UINTN                       VariableSize;
    UINT32                      SbAslBufVarPtr;
    EFI_GUID                    SbAslBufPtrGuid = SB_ASL_BUFFER_PTR_GUID;
    CHAR16                      SbAslBufPtrVar[] = SB_ASL_BUFFER_PTR_VARIABLE;

    CpuIo = (*PeiServices)->CpuIo;
    PciCfg = (*PeiServices)->PciCfg;

    PEI_PROGRESS_CODE (PeiServices, PEI_MEM_SB_INIT);

    Status = (*PeiServices)->GetBootMode (PeiServices, &BootMode);

    InitUsbMisc( PeiServices, CpuIo, PciCfg, BootMode );

#if (ACPI_SUPPORT)
    if (BootMode == BOOT_ON_S3_RESUME) {
        Status = (*PeiServices)->LocatePpi( PeiServices, \
                                            &gEfiPeiReadOnlyVariable2PpiGuid, \
                                            0, \
                                            NULL, \
                                            &ReadOnlyVariable );
        ASSERT_PEI_ERROR( PeiServices, Status );
        VariableSize = sizeof(SbAslBufVarPtr);
        Status = ReadOnlyVariable->GetVariable( ReadOnlyVariable, \
                                                SbAslBufPtrVar, \
                                                &SbAslBufPtrGuid, \
                                                NULL, \
                                                &VariableSize, \
                                                &SbAslBufVarPtr );
        if (!EFI_ERROR(Status)) {
            // Update ACPI RTC status
            RESET_MEM8(SbAslBufVarPtr, 1); // Clear ACPI RTC status
            if (READ_IO16_PM(ACPI_IOREG_PM1_STS) & 0x400)
                SET_MEM8(SbAslBufVarPtr, 1); // Set ACPI RTC status
        }
#if defined BootScriptHide_SUPPORT && BootScriptHide_SUPPORT
        //SCI_EN = 1
        SET_IO8_PM(ACPI_IOREG_PM1_CNTL, B_PCH_ACPI_PM1_CNT_SCI_EN); //PM1_CNT
#endif
    }
#endif
    // Clear Global Reset Bit
    RESET_PCI32_SB(SB_REG_LPC_PMIR, B_ICH_LPC_PMIR_CF9GR);

    // Set up necessary PPI notifications after PEI permantent memory
    // be installed
    Status = (*PeiServices)->NotifyPpi( PeiServices, &mNotifyList[0] );
    ASSERT_PEI_ERROR ( PeiServices, Status );

#if defined RapidStart_SUPPORT && RapidStart_SUPPORT
    if (BootMode == BOOT_ON_S4_RESUME)
        if (RtcRead(FFS_NV_FLAG_REG) & BIT0)
          return EFI_SUCCESS;
#endif

    return  EFI_SUCCESS;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:   ProgramSBRegBeforeEndofPei
//
// Description: This function can be used to program any SB regisater before
//              end of PEI phase.
//
// Input:       PeiServices      - Pointer to the PEI services table
//              NotifyDescriptor - Pointer to the descriptor for the
//                                 notification event.
//              InvokePpi        - Pointer to the PPI that was installed
//
// Output:      EFI_STATUS
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS ProgramSBRegBeforeEndofPei (
    IN EFI_PEI_SERVICES             **PeiServices,
    IN EFI_PEI_NOTIFY_DESCRIPTOR    *NotifyDescriptor,
    IN VOID                         *InvokePpi )
{
    EFI_STATUS                  Status = EFI_SUCCESS;
    EFI_PEI_CPU_IO_PPI          *CpuIo;
    IN EFI_PEI_PCI_CFG2_PPI     *PciCfg;
    EFI_BOOT_MODE               BootMode;

    CpuIo = (*PeiServices)->CpuIo;
    PciCfg = (*PeiServices)->PciCfg;

    Status = (*PeiServices)->GetBootMode (PeiServices, &BootMode);

    if (BootMode == BOOT_ON_S3_RESUME) {
                                        // [EIP87695]>
#if SYSTEM_REBOOT_NORMALLY_IF_S3_IS_FAILED
    WRITE_IO16_PM(ACPI_IOREG_PM1_CNTL, READ_IO16_PM(ACPI_IOREG_PM1_CNTL) & 0xe3ff | (S3_SLP_TYP << 10)); // Clear S3 for avoiding S3 resume twice
#endif
                                        // <[EIP87695]
        // Porting if needed.
    } else {
        // Porting if needed.
    }

    // Setting 8254
    // program timer 1 as refresh timer
    IoWrite8(LEGACY_TIMER_CTRL,0x54);
    IoWrite8(LEGACY_TIMER_1_COUNT,0x12);

#if defined(SUPPORT_RAID_DRIVER) && SUPPORT_RAID_DRIVER && (PTT_VER > 15)
    DetectSataPortInfo(PeiServices);
#endif

    return  EFI_SUCCESS;
}


//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:   IsRtcUipAlwaysSet
//
// Description: Check RTC Time Update In Progress.
//
// Input:       PeiServices - Pointer to the PEI services table
//
// Output:      Boolean
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
BOOLEAN IsRtcUipAlwaysSet(
  IN EFI_PEI_SERVICES       **PeiServices
  )
{

  EFI_PEI_STALL_PPI   *StallPpi;
  UINTN               Count;

  StallPpi = &mStallPpi;

  for (Count = 0; Count < 500; Count++) {   // Maximum waiting approximates to 1.5 seconds (= 3 msec * 500) 
    if ((READ_IO8_RTC(RTC_NMI_MASK | RTC_REG_A_INDEX) & BIT07) == 0) {
      return FALSE;
    }
    StallPpi->Stall (PeiServices, StallPpi, 3000); 
  }

  return TRUE;  
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:   InitRTC
//
// Description: This function initializes SB RTC related registers
//
// Input:       PeiServices - Pointer to the PEI services table
//              CpuIo       - Pointer to the CPU I/O PPI
//
// Output:      None
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

VOID InitRTC (
    IN EFI_PEI_SERVICES     **PeiServices,
    IN EFI_PEI_CPU_IO_PPI   *CpuIo )
{
    UINT8        Buffer8;
    UINT16       Buffer16;
    BOOLEAN      RtcUipIsAlwaysSet;

    //
    // PCH BIOS Specification 0.6.0 - Section 19.2, "Power Failure Consideration"
    // 
    // When the RTC_PWR_STS bit is set, it indicates that the RTCRST# signal went low.
    // Software should clear this bit. For example, changing the RTC battery sets this bit.
    // System BIOS should reset CMOS to default values if the RTC_PWR_STS is set.
    //
    // The System BIOS should execute the sequence below if the RTC_PWR_STS bit is set before memory initialization.
    // This will ensure that the RTC state machine has been initialized.
    //  1.    If the RTC_PWR_STS bit is set, which indicates a new coin-cell batttery
    //        insertion or a battery failure, steps 2 through 5 should be executed.
    //  2.    Set RTC Register 0Ah[6:4] to '110b' or '111b'.
    //  3.    Set RTC Register 0Bh[7].
    //  4.    Set RTC Register 0Ah[6:4] to '010b'.
    //  5.    Clear RTC Register 0Bh[7].
    Buffer16 = READ_PCI16_SB(R_PCH_LPC_GEN_PMCON_3); // 0xA4 
    RtcUipIsAlwaysSet = IsRtcUipAlwaysSet(PeiServices);
    if ((Buffer16 & B_PCH_LPC_GEN_PMCON_RTC_PWR_STS) || RtcUipIsAlwaysSet) { 

        //
        // Step 1.
        // BIOS clears this bit by writing a '0' to it.
        //
        if (Buffer16 & B_PCH_LPC_GEN_PMCON_RTC_PWR_STS) {
          Buffer16 &= ~B_PCH_LPC_GEN_PMCON_RTC_PWR_STS;
          WRITE_PCI16_SB(R_PCH_LPC_GEN_PMCON_3, Buffer16);
          WRITE_IO8_RTC((RTC_NMI_MASK | RTC_DAY_OF_MONTH_REG), 0xFF);
          WRITE_IO8_RTC((RTC_NMI_MASK | RTC_HOURS_REG), 0xFF);
        }

        //      
        // Step 2.
        // Set RTC Register 0Ah[6:4] to '110' or '111'.
        //
        WRITE_IO8_RTC((RTC_NMI_MASK | RTC_REG_A_INDEX), 0x66);

        //      
        // Step 3.
        // Set RTC Register 0Bh[7].
        //
        Buffer8 = (READ_IO8_RTC(RTC_NMI_MASK | RTC_REG_B_INDEX) | 0x80);
        WRITE_IO8_RTC((RTC_NMI_MASK | RTC_REG_B_INDEX), Buffer8);
  
        //      
        // Step 4.
        // Set RTC Register 0Ah[6:4] to '010'.
        //
        WRITE_IO8_RTC((RTC_NMI_MASK | RTC_REG_A_INDEX), 0x26);

        //      
        // Step 5.
        // Clear RTC Register 0Bh[7].
        //
        Buffer8 = (READ_IO8_RTC(RTC_NMI_MASK | RTC_REG_B_INDEX) & ~0x80);
        WRITE_IO8_RTC((RTC_NMI_MASK | RTC_REG_B_INDEX), Buffer8);
    }

}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:   InitPMRegs
//
// Description: This function initializes SB Power Management registers.
//
// Input:       PeiServices - Pointer to the PEI services table
//              CpuIo       - Pointer to the CPU I/O PPI
//
// Output:      None
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

VOID InitPMRegs (
    IN EFI_PEI_SERVICES     **PeiServices,
    IN EFI_PEI_CPU_IO_PPI   *CpuIo,
    IN SB_SETUP_DATA        *SbSetupData)
{
  EFI_STATUS     Status = EFI_SUCCESS;
  EFI_BOOT_MODE  BootMode = 0;
  PCH_SERIES     PchSeries = GetPchSeries();

  Status = (*PeiServices)->GetBootMode (PeiServices, &BootMode);
  if (BootMode != BOOT_ON_S3_RESUME) {
    WRITE_IO16_PM(ACPI_IOREG_PM1_EN, 0);
  }
  if (PchSeries == PchLp) {
    WRITE_IO32_PM(ACPI_PCHLP_IOREG_GPE0_EN+0x0c, 0);
  } else {
    WRITE_IO32_PM(ACPI_IOREG_GPE0_EN, 0);
    WRITE_IO32_PM(ACPI_IOREG_GPE0_EN + 4, 0);
  }

  // Clear Alternate GPI SMI Status Reg.
  if (PchSeries == PchLp) {
    WRITE_IO32(GPIO_BASE_ADDRESS + GP_IOREG_ALTGP_SMI_STS, 0xFFFFFFFF);
  } else {
    WRITE_IO16_PM(ACPI_IOREG_ALTGP_SMI_STS, 0xFFFF);
  }

#if EHCI_CON_DISCON_WAKE_UP_SUPPORT
    if (SbSetupData->EhciConDisConWakeUp)
      RESET_MEM8_RCRB(RCRB_MMIO_RMHWKCTL , 0xFF);
    else
      SET_MEM8_RCRB(RCRB_MMIO_RMHWKCTL , (BIT00 | BIT01 | BIT04 | BIT05));
#endif

}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:   ProgramRCRBMmio
//
// Description: This function initializes SB Root Complex registers
//
// Input:       PeiServices - Pointer to the PEI services table
//              CpuIo       - Pointer to the CPU I/O PPI
//
// Output:      None
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

VOID ProgramRCRBMmio (
    IN EFI_PEI_SERVICES     **PeiServices,
    IN EFI_PEI_CPU_IO_PPI   *CpuIo )
{
  PCH_SERIES              PchSeries = GetPchSeries();

  //Enable IOAPIC Decoding and FERR#
  if(PchSeries == PchLp){
    SET_MEM16_RCRB(R_PCH_RCRB_OIC, B_PCH_RCRB_OIC_AEN);  
  } else {
    SET_MEM16_RCRB(R_PCH_RCRB_OIC, (B_PCH_RCRB_OIC_AEN | (PCH_RCRB_OIC_CEN << 9)));
  }

  // Enable No Reboot, Boot BIOS Destination
  SET_MEM32_RCRB(R_PCH_RCRB_GCS, (BIT06 | B_PCH_RCRB_GCS_NR));

  SET_MEM32_RCRB (R_PCH_RCRB_FD2, BIT00); //0x3428

  // PIRQ routing Info
  // Device 31 Interrupt Pin, reg#3100h
  WRITE_MEM32_RCRB(R_PCH_RCRB_D31IP, (RCRB_IRQB << 8)  +
                                     (RCRB_IRQC << 12) +
                                     (RCRB_IRQD << 16) +
                                     (RCRB_IRQB << 20) +
                                     (RCRB_IRQC << 24));

  // Device 30 Interrupt Pin, reg#3104h - Read Only

  // Device 29 Interrupt Pin, reg#3108h
  WRITE_MEM32_RCRB(R_PCH_RCRB_D29IP, (RCRB_IRQA << 0) +
                                     (RCRB_IRQB << 4) +
                                     (RCRB_IRQC << 8) +
                                     (RCRB_IRQD << 12) +
                                     (RCRB_IRQA << 16));

  // Device 28 Interrupt Pin, reg#310Ch
  WRITE_MEM32_RCRB(R_PCH_RCRB_D28IP, (RCRB_IRQA << 0) +
                                     (RCRB_IRQB << 4) +
                                     (RCRB_IRQC << 8) +
                                     (RCRB_IRQD << 12) +
                                     (RCRB_IRQA << 16) +
                                     (RCRB_IRQB << 20) +
                                     (RCRB_IRQC << 24) +
                                     (RCRB_IRQD << 28));

  // Device 27 Interrupt Pin, reg#3110h
  WRITE_MEM32_RCRB(R_PCH_RCRB_D27IP, (RCRB_IRQA << 0));

  // Device 26 Interrupt Pin, reg#3114h
  WRITE_MEM32_RCRB(R_PCH_RCRB_D26IP, (RCRB_IRQA << 0) +
                                     (RCRB_IRQB << 4) +
                                     (RCRB_IRQC << 8) +
                                     (RCRB_IRQD << 12));

  // Device 25 Interrupt Pin, reg#3118h
  WRITE_MEM32_RCRB(R_PCH_RCRB_D25IP, (RCRB_IRQA << 0));

  // Device 22 Interrupt Pin, reg#3124h
  WRITE_MEM16_RCRB(R_PCH_RCRB_D22IP, (RCRB_IRQA << 0) +
                                     (RCRB_IRQB << 4) +
                                     (RCRB_IRQC << 8) +
                                     (RCRB_IRQB << 12));

  // Device 20 Interrupt Pin, reg#3128h
  WRITE_MEM32_RCRB(R_PCH_RCRB_D20IP, (RCRB_IRQA << 0));

  // Device 31 Interrupt Route, reg#3140h
  WRITE_MEM16_RCRB(R_PCH_RCRB_D31IR, (RCRB_PIRQD << 4) +
                                     (RCRB_PIRQC << 8) +
                                     (RCRB_PIRQA << 12));

  // Device 29 Interrupt Route, reg#3144h
  WRITE_MEM16_RCRB(R_PCH_RCRB_D29IR, (RCRB_PIRQH << 0) +
                                     (RCRB_PIRQD << 4) +
                                     (RCRB_PIRQA << 8) +
                                     (RCRB_PIRQC << 12));

  // Device 28 Interrupt Route, reg#3146h
  WRITE_MEM16_RCRB(R_PCH_RCRB_D28IR, (RCRB_PIRQA << 0) +
                                     (RCRB_PIRQB << 4) +
                                     (RCRB_PIRQC << 8) +
                                     (RCRB_PIRQD << 12));

  // Device 27 Interrupt Route, reg#3148h
  WRITE_MEM16_RCRB(R_PCH_RCRB_D27IR, (RCRB_PIRQG << 0) +
                                     (RCRB_PIRQB << 4) +
                                     (RCRB_PIRQC << 8) +
                                     (RCRB_PIRQD << 12));

  // Device 26 Interrupt Route, reg#314Ch
  WRITE_MEM16_RCRB(R_PCH_RCRB_D26IR, (RCRB_PIRQA << 0) +
                                     (RCRB_PIRQF << 4) +
                                     (RCRB_PIRQC << 8) +
                                     (RCRB_PIRQD << 12));

  // Device 25 Interrupt Route, reg#3150h
  WRITE_MEM16_RCRB(R_PCH_RCRB_D25IR, (RCRB_PIRQE << 0) +
                                     (RCRB_PIRQF << 4) +
                                     (RCRB_PIRQG << 8) +
                                     (RCRB_PIRQH << 12));

  if (PchSeries == PchLp) {
  // Device 23 Interrupt Route, reg#3158h
  	WRITE_MEM16_RCRB(R_PCH_RCRB_D23IR, (RCRB_PIRQG << 0));
  }

  // Device 22 Interrupt Route, reg#315Ch
  WRITE_MEM16_RCRB(R_PCH_RCRB_D22IR, (RCRB_PIRQA << 0) +
                                     (RCRB_PIRQD << 4) +
                                     (RCRB_PIRQC << 8) +
                                     (RCRB_PIRQB << 12));

  if (PchSeries == PchLp) {
  // Device 21 Interrupt Route, reg#3164h
  	WRITE_MEM16_RCRB(R_PCH_RCRB_D21IR, (RCRB_PIRQE << 0) +
                                       (RCRB_PIRQE << 4) +
                                       (RCRB_PIRQF << 8) +
                                       (RCRB_PIRQF << 12));
  }

  // Device 20 Interrupt Route, reg#3160h
  WRITE_MEM16_RCRB(R_PCH_RCRB_D20IR, (RCRB_PIRQA << 0) +
                                     (RCRB_PIRQB << 4) +
                                     (RCRB_PIRQC << 8) +
                                     (RCRB_PIRQD << 12));

  if (PchSeries == PchLp) {
  // Device 19 Interrupt Route, reg#3168h
  	WRITE_MEM16_RCRB(R_PCH_RCRB_D19IR, (RCRB_PIRQH << 0));
  }

  // EIP176923
  #if defined DISABLE_DAYLIGHT_SAVINGS && DISABLE_DAYLIGHT_SAVINGS == 1
    SET_MEM16_RCRB(R_PCH_RCRB_BUC, B_PCH_RCRB_BUC_SDO);
  #endif
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:   ProgramSBIoDecodeRegs
//
// Description: This function initializes SB IO Decide Registers.
//
// Input:       PeiServices - Pointer to the PEI services table
//              PciCfg      - Pointer to the PCI Configuration PPI
//
// Output:      EFI_STATUS
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS
ProgramSBIoDecodeRegs (
  IN EFI_PEI_SERVICES       **PeiServices,
  IN EFI_PEI_PCI_CFG2_PPI   *PciCfg
)
{

#if defined EMUL6064_SUPPORT && EMUL6064_SUPPORT == 1
    // Force KBC_LPC_EN bit (B0:D31:F0 Reg 82h[10]) = 1 if EMUL6064_SUPPORT = 1.
    SbLib_SetLpcDeviceDecoding(NULL, 0x60, 0, dsPS2K);
#endif
   return EFI_SUCCESS;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:   ProgramPchDeviceBase
//
// Description: This function initializes SB Devices Base
//
// Input:       PeiServices - Pointer to the PEI services table
//              PciCfg      - Pointer to the PCI Configuration PPI
//
// Output:      EFI_STATUS
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS
ProgramPchDeviceBase (
  IN EFI_PEI_SERVICES       **PeiServices,
  IN EFI_PEI_PCI_CFG2_PPI   *PciCfg
)
{

  // Program RCBA Base
  WRITE_PCI32_SB(SB_REG_RCBA, SB_RCRB_BASE_ADDRESS | 1);//0xF0

  // Write Heci Base Address and enable Heci device
  WRITE_PCI32_HECI(ME_REG_HECI_MBAR, HECI_BASE_ADDRESS);
  WRITE_PCI16_HECI(ME_REG_PCICMD, 0x06);

  // Write Heci Base Address and enable Heci device
  WRITE_PCI32_HECI2(ME_REG_HECI_MBAR, HECI2_BASE_ADDRESS);
  WRITE_PCI16_HECI2(ME_REG_PCICMD, 0x06);

  // Program PM Base
  WRITE_PCI16_SB(SB_REG_PMBASE, PM_BASE_ADDRESS);
  WRITE_PCI8_SB(SB_REG_ACPI_CNTL, 0x80);

  // Program GPIO Base
  WRITE_PCI16_SB(SB_REG_GPIOBASE, GPIO_BASE_ADDRESS);
  WRITE_PCI8_SB(SB_REG_GC, 0x10);
  
  return EFI_SUCCESS;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:   GeneralPowerFailureHandler
//
// Description: When the PWR_FLR bit is set, it indicates the trickle power
//              from the main battery or tricle supply failed while in suspend
//              or since last boot. This bit us ub the RTC well and is cleared
//              only by RTCRST#. Software writes a "1" to clear this bit.
//              System BIUOS should follow cold boot path if PWR_FLR, GEN_RST_STS
//              or PWRBTNOR_STS is set to 1 regardless of the value in the SLP_TYP
//              field.
//
// Input:       PeiServices - Pointer to the PEI services table
//              CpuIo       - Pointer to the CPU I/O PPI
//              PciCfg      - Pointer to the PCI Configuration PPI
//
// Output:      EFI_STATUS
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS
GeneralPowerFailureHandler (
  IN EFI_PEI_SERVICES       **PeiServices,
  IN EFI_PEI_CPU_IO_PPI     *CpuIo,
  IN EFI_PEI_PCI_CFG2_PPI   *PciCfg
)
{

  UINT16       DataUint16;  
  UINT8        DataUint8;

  //
  // PCH BIOS Specification 0.6.0 - Section 19.2, "Power Failure Considerations"
  // 
  // When the PWR_FLR bit is set, it indicates the trickle power from the main
  // battery or tricle supply failed while in suspend or since last boot.
  // System BIOS should follow cold boot path if PWR_FLR, GEN_RST_STS or
  // PWRBTNOR_STS is set to 1 regardless of the value in the SLP_TYP field.
  //
  DataUint16 = READ_PCI16_SB(R_PCH_LPC_GEN_PMCON_3);
  if ((DataUint16 & (B_PCH_LPC_GEN_PMCON_GEN_RST_STS | B_PCH_LPC_GEN_PMCON_PWR_FLR)) || \
      (READ_IO16_PM(R_PCH_ACPI_PM1_STS) & B_PCH_ACPI_PM1_STS_PRBTNOR)) {
    //
    // BIOS clears these bits by writing a '1' to them.
    //
    WRITE_PCI16_SB(R_PCH_LPC_GEN_PMCON_3, DataUint16);
    WRITE_IO16_PM(R_PCH_ACPI_PM1_STS, B_PCH_ACPI_PM1_STS_PRBTNOR);

    //
    // Clear Wake Status (WAK_STS) and Sleep Type (SLP_TYP)
    //
    WRITE_IO16_PM(ACPI_IOREG_PM1_STS, B_PCH_ACPI_PM1_STS_WAK);
    DataUint16 = (READ_IO16_PM(ACPI_IOREG_PM1_CNTL) & ~B_PCH_ACPI_PM1_CNT_SLP_TYP);
    WRITE_IO16_PM(ACPI_IOREG_PM1_CNTL, DataUint16);
  }

  // 
  // When the CPUPWR_FLR bit is set, it indicates VRMPWRGD signal from
  // the CPU VRM went low. This bit is now set if VRMPWRGD goes low
  // during Intel (R) SpeedStep Technology transition.
  // Software must clear this bit if set.
  //
  DataUint8 = READ_PCI8_SB(R_PCH_LPC_GEN_PMCON_2);
  if (DataUint8 & B_PCH_LPC_GEN_PMCON_SYSPWR_FLR) {
    //
    // BIOS clears this bit by writing a '0' to it.
    //
    DataUint8 &= ~B_PCH_LPC_GEN_PMCON_SYSPWR_FLR;
    WRITE_PCI8_SB(R_PCH_LPC_GEN_PMCON_2, DataUint8);
  }

  return EFI_SUCCESS;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:   SetTheStateToGoAfterG3
//
// Description: Set what state (S0/S5) to go to when power is re-applied
//              after a power failure (G3 state)
//
// Input:       PeiServices - Pointer to the PEI services table
//              CpuIo       - Pointer to the CPU I/O PPI
//              PciCfg      - Pointer to the PCI Configuration PPI
//              SbSetupData - Pointer to the SbSetupData
//
// Output:      EFI_STATUS
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS
SetTheStateToGoAfterG3 (
  IN EFI_PEI_SERVICES       **PeiServices,
  IN EFI_PEI_CPU_IO_PPI     *CpuIo,
  IN EFI_PEI_PCI_CFG2_PPI   *PciCfg,
  IN SB_SETUP_DATA          *SbSetupData
)
{
  UINT16                              DataUint16;
  //
  // Make sure we have a setup data, if not, just return.
  //
  if (SbSetupData == NULL) {
    return EFI_UNSUPPORTED;
  }
 
  DataUint16 = READ_PCI16_SB(R_PCH_LPC_GEN_PMCON_3);
  if(SbSetupData->LastState == 0) {
    DataUint16 |= B_PCH_LPC_GEN_PMCON_AFTERG3_EN;
  } else {
    DataUint16 &= ~B_PCH_LPC_GEN_PMCON_AFTERG3_EN;
  }

// Done in PchMisc.c
//####  DataUint16 |= (SbSetupData->SlpS4AssW << 4);

  WRITE_PCI16_SB(R_PCH_LPC_GEN_PMCON_3, DataUint16);

  return EFI_SUCCESS;
}

static UINT8 mSmbusRsvdAddresses[DIMM_SLOT_NUM] = {
  DIMM1_SMBUS_ADDRESS, 
  DIMM2_SMBUS_ADDRESS, 
  DIMM3_SMBUS_ADDRESS, 
  DIMM4_SMBUS_ADDRESS
};

static PEI_SMBUS_POLICY_PPI mSmbusPolicyPpi = {
  SMBUS_BASE_ADDRESS,
  SMBUS_BUS_DEV_FUN,
  DIMM_SLOT_NUM,
  mSmbusRsvdAddresses
};

EFI_PEI_PPI_DESCRIPTOR SmbusPolicy_PpiDescriptor = {
  EFI_PEI_PPI_DESCRIPTOR_PPI | EFI_PEI_PPI_DESCRIPTOR_TERMINATE_LIST, 
  &gPeiSmbusPolicyPpiGuid, 
  &mSmbusPolicyPpi
};
																// [EIP106687]>
//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:   SbPcieDetectNonComplaintPcieDevice
//
// Description: 
//
// Input:       IN UINT8           Index,
//              IN PCH_PCIE_CONFIG *PcieConfig
//
// Output:      None
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID
SbPcieDetectNonComplaintPcieDevice (
  IN EFI_PEI_SERVICES       **PeiServices,
  IN UINT8                  Index,
  IN PCH_PCIE_CONFIG        *PcieConfig,
  IN SB_SETUP_DATA          *SbSetupData
)
{
  if ((PcieConfig->PcieSpeed[Index] == PchPcieAuto) && \
      (SbSetupData->PcieRootPortEn[Index]!= 0))
  {
     PEI_TRACE((-1,PeiServices, "Enhance Detect Non-Compliance PCIE Device @B:0|D:1C|F:%x Start .\n", Index));
     // Assign temp bus
     PEI_TRACE((-1,PeiServices, "Assign temp bus ...\n"));
     WRITE_PCI16(PCIEBRS_BUS, PCIEBRS_DEV, Index, R_PCH_PCIE_BNUM+1, 0x0101);
     // Do a dummy Write
     WRITE_PCI32(1, 0, 0, PCI_VID, 0x12345678);
        
     if (READ_PCI16(1, 0, 0, PCI_VID) == 0xFFFF) {
        PEI_TRACE((-1,PeiServices, "Can't find Device... Retrain device first.\n"));
        WRITE_PCI8(PCIEBRS_BUS, PCIEBRS_DEV, Index, R_PCH_PCIE_LCTL, B_PCH_PCIE_LCTL_LD);
        CountTime((RETRAIN_DELAY * 10), PM_BASE_ADDRESS); //delay 500us
        WRITE_PCI8(PCIEBRS_BUS, PCIEBRS_DEV, Index, R_PCH_PCIE_LCTL, B_PCH_PCIE_LCTL_RL);
        CountTime((RETRAIN_DELAY * 8000), PM_BASE_ADDRESS); //delay 400ms
        if (READ_PCI16(1, 0, 0, PCI_VID) == 0xFFFF) {
           PEI_TRACE((-1,PeiServices, "Still can't find Device in Gen2 Speed... Speed is setted in Gen1 and delay 200 ms.\n"));
           // Set Speed to Gen1
           RW_PCI8(PCIEBRS_BUS, PCIEBRS_DEV, Index, R_PCH_PCIE_LCTL2, 0x01, 0x03);
           CountTime((RETRAIN_DELAY * 4000), PM_BASE_ADDRESS); //delay 200ms
                 
           if (READ_PCI16(1, 0, 0, PCI_VID) == 0xFFFF) {
              PEI_TRACE((-1,PeiServices, "Still can't find Device in Gen1 Speed... Retrain device again !!!\n"));
              WRITE_PCI8(PCIEBRS_BUS, PCIEBRS_DEV, Index, R_PCH_PCIE_LCTL, B_PCH_PCIE_LCTL_LD);
              CountTime((RETRAIN_DELAY * 10), PM_BASE_ADDRESS); //delay 500us
              WRITE_PCI8(PCIEBRS_BUS, PCIEBRS_DEV, Index, R_PCH_PCIE_LCTL, B_PCH_PCIE_LCTL_RL);
              CountTime((RETRAIN_DELAY * 8000), PM_BASE_ADDRESS); //delay 400ms
                   
              if (READ_PCI16(1, 0, 0, PCI_VID) != 0xFFFF) PcieConfig->PcieSpeed[Index] = PchPcieGen1;
           }
           else PcieConfig->PcieSpeed[Index] = PchPcieGen1;
        }
     }

     // Remove temp bus
     PEI_TRACE((-1,PeiServices, "Remove temp bus.\n"));
     WRITE_PCI32(PCIEBRS_BUS, PCIEBRS_DEV, Index, PCI_PBUS, 0xFF000000);
     
     PEI_TRACE((-1,PeiServices, "Enhance Detect Non-Compliance PCIE Device end.\n"));
  }
}
																		// <[EIP106687]
//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:   InstallPchPlatformPolicyPpi
//
// Description: Install Pch Platform Policy Ppi 
//
// Input:       IN EFI_PEI_SERVICES                   **PeiServices,
//              IN SB_SETUP_DATA                      *SbSetupData
//
// Output:      EFI_STATUS
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS
InstallPchPlatformPolicyPpi (
  IN EFI_PEI_SERVICES                   **PeiServices,
  IN SB_SETUP_DATA                      *SbSetupData
)
{

  UINT8                                 *SbRcba = (UINT8*)(UINTN)SB_RCRB_BASE_ADDRESS;
  EFI_STATUS                            Status;
  EFI_PEI_PPI_DESCRIPTOR                *PchPlatformPolicyPpiDesc;
  PCH_PLATFORM_POLICY_PPI               *PchPlatformPolicyPpi;
  PCH_THERMAL_MANAGEMENT                *ThermalMgmt;
  PCH_MEMORY_THROTTLING                 *MemoryThrottling;
  PCH_HPET_CONFIG                       *HpetConfig;
  PCH_IOAPIC_CONFIG                     *IoApicConfig;
  PCH_SATA_CONTROL                      *SataConfig;
  PCH_SATA_TRACE_CONFIG                 *SataTraceConfig;
  PCH_GBE_CONFIG                        *GbeConfig;
  PCH_PCIE_CONFIG                       *PcieConfig;
  PCH_USB_CONFIG                        *UsbConfig;
  EFI_BOOT_MODE                         BootMode;
  UINT8                                 Index;
  PCH_PLATFORM_DATA                     *PlatformData;
  UINT16                                LpcDeviceId = READ_PCI16_SB(R_PCH_LPC_DEVICE_ID);
  UINT16                                Data16;
  UINT8                                 PortIndex;
  UINT16                                UsbPortLength[LPTH_USB_MAX_PHYSICAL_PORTS] = {USB_PORTS_LENGTH};
  UINT8                                 UsbPortLocation[LPTH_USB_MAX_PHYSICAL_PORTS] = {USB_PORT_LOCATION_CONFIG};
  UINT8                                 UsbOverCurrentMapping[LPTH_USB_MAX_PHYSICAL_PORTS] = {USB_OVER_CURRENT_MAPPING_SETTINGS};
  UINT8                                 Usb30OverCurrentMapping[LPTH_XHCI_MAX_USB3_PORTS] = {USB30_OVER_CURRENT_MAPPING_SETTINGS};
  PCH_SERIES                            PchSeries = GetPchSeries();
  SATA_LENGTH_CONFIG                    SataLengthConfigTable[] = {SATA_PORT1_LENGTH_CONFIG, 
                                                                   SATA_PORT2_LENGTH_CONFIG, 
                                                                   SATA_PORT3_LENGTH_CONFIG, 
                                                                   SATA_PORT4_LENGTH_CONFIG, 
                                                                   SATA_PORT5_LENGTH_CONFIG, 
                                                                   SATA_PORT6_LENGTH_CONFIG};
#if defined   iME_SUPPORT && iME_SUPPORT
  EFI_PEI_READ_ONLY_VARIABLE2_PPI       *ReadOnlyVariable;
  UINTN                                 VariableSize;
  ME_BIOS_EXTENSION_SETUP               MeBiosExtensionSetupData;
  EFI_GUID                              EfiMeBiosExtensionSetupGuid    = EFI_ME_BIOS_EXTENSION_SETUP_GUID;
  CHAR16                                EfiMeBiosExtensionSetupName[]  = EFI_ME_BIOS_EXTENSION_SETUP_VARIABLE_NAME;
#endif

  BootMode = BOOT_WITH_FULL_CONFIGURATION; 

  //  Install SmbusPolicy PPI
  Status = (**PeiServices).InstallPpi (PeiServices, &SmbusPolicy_PpiDescriptor);
  ASSERT_PEI_ERROR (PeiServices, Status);

  // Allocate descriptor and PPI structures.  Since these are dynamically updated
  // we cannot do a global variable PPI.
  Status = (*PeiServices)->AllocatePool (PeiServices, sizeof (EFI_PEI_PPI_DESCRIPTOR), &PchPlatformPolicyPpiDesc);
  ASSERT_PEI_ERROR (PeiServices, Status);
  (*PeiServices)->SetMem ((VOID*) PchPlatformPolicyPpiDesc, sizeof (EFI_PEI_PPI_DESCRIPTOR), 0);

  Status = (*PeiServices)->AllocatePool (PeiServices, sizeof (PCH_PLATFORM_POLICY_PPI), &PchPlatformPolicyPpi);
  ASSERT_PEI_ERROR (PeiServices, Status);
  (*PeiServices)->SetMem ((VOID*) PchPlatformPolicyPpi, sizeof (PCH_PLATFORM_POLICY_PPI), 0);

  Status = (*PeiServices)->AllocatePool (PeiServices, sizeof (PCH_HPET_CONFIG), &HpetConfig);
  ASSERT_PEI_ERROR (PeiServices, Status);
  (*PeiServices)->SetMem ((VOID*) HpetConfig, sizeof (PCH_HPET_CONFIG), 0);

  Status = (*PeiServices)->AllocatePool (PeiServices, sizeof (PCH_THERMAL_MANAGEMENT), &ThermalMgmt);
  ASSERT_PEI_ERROR (PeiServices, Status);
  (*PeiServices)->SetMem ((VOID*) ThermalMgmt, sizeof (PCH_THERMAL_MANAGEMENT), 0);

  Status = (*PeiServices)->AllocatePool (PeiServices, sizeof (PCH_IOAPIC_CONFIG), &IoApicConfig);
  ASSERT_PEI_ERROR (PeiServices, Status);
  (*PeiServices)->SetMem ((VOID*) IoApicConfig, sizeof (PCH_IOAPIC_CONFIG), 0);

  Status = (*PeiServices)->AllocatePool (PeiServices, sizeof (PCH_MEMORY_THROTTLING), &MemoryThrottling);
  ASSERT_PEI_ERROR (PeiServices, Status);
  (*PeiServices)->SetMem ((VOID*) MemoryThrottling, sizeof (PCH_MEMORY_THROTTLING), 0);

  Status = (*PeiServices)->AllocatePool (PeiServices, sizeof (PCH_SATA_CONTROL), &SataConfig);
  ASSERT_PEI_ERROR (PeiServices, Status);
  (*PeiServices)->SetMem ((VOID*) SataConfig, sizeof (PCH_SATA_CONTROL), 0);

  Status = (*PeiServices)->AllocatePool (PeiServices, sizeof (PCH_SATA_TRACE_CONFIG), &SataTraceConfig);
  ASSERT_PEI_ERROR (PeiServices, Status);
  (*PeiServices)->SetMem ((VOID*) SataTraceConfig, sizeof (PCH_SATA_TRACE_CONFIG), 0);

  Status = (*PeiServices)->AllocatePool (PeiServices, sizeof (PCH_GBE_CONFIG), &GbeConfig);
  ASSERT_PEI_ERROR (PeiServices, Status);
  (*PeiServices)->SetMem ((VOID*) GbeConfig, sizeof (PCH_GBE_CONFIG), 0);

  Status = (*PeiServices)->AllocatePool (PeiServices, sizeof (PCH_PCIE_CONFIG), &PcieConfig);
  ASSERT_PEI_ERROR (PeiServices, Status);
  (*PeiServices)->SetMem ((VOID*) PcieConfig, sizeof (PCH_PCIE_CONFIG), 0);

  Status = (*PeiServices)->AllocatePool (PeiServices, sizeof (PCH_PLATFORM_DATA), &PlatformData);
  ASSERT_PEI_ERROR (PeiServices, Status);
  (*PeiServices)->SetMem ((VOID*) PlatformData, sizeof (PCH_PLATFORM_DATA), 0);

  Status = (*PeiServices)->AllocatePool (PeiServices, sizeof (PCH_USB_CONFIG), &UsbConfig);
  ASSERT_PEI_ERROR (PeiServices, Status);
  (*PeiServices)->SetMem ((VOID*) UsbConfig, sizeof (PCH_USB_CONFIG), 0);

  PchPlatformPolicyPpi->Revision = PCH_PLATFORM_POLICY_PPI_REVISION_4;
  PchPlatformPolicyPpi->BusNumber = 0;
  PchPlatformPolicyPpi->Rcba = SB_RCRB_BASE_ADDRESS;
  PchPlatformPolicyPpi->PmBase = PM_BASE_ADDRESS;
  PchPlatformPolicyPpi->GpioBase = GPIO_BASE_ADDRESS;
  PchPlatformPolicyPpi->Port80Route = RESERVED_PAGE_ROUTE;
  
  PchPlatformPolicyPpi->GbeConfig = GbeConfig;
  PchPlatformPolicyPpi->ThermalMgmt = ThermalMgmt;
  PchPlatformPolicyPpi->HpetConfig = HpetConfig;
  PchPlatformPolicyPpi->SataConfig = SataConfig;
  PchPlatformPolicyPpi->PcieConfig = PcieConfig;
  PchPlatformPolicyPpi->IoApicConfig = IoApicConfig;
  PchPlatformPolicyPpi->PlatformData = PlatformData;
  PchPlatformPolicyPpi->UsbConfig = UsbConfig;

//-  ThermalMgmt->ThermalBaseB = SB_THERMAL_BASE_ADDRESS;
  ThermalMgmt->MemoryThrottling = MemoryThrottling;

  GbeConfig->EnableGbe = 1;
//-  GbeConfig->GbeMemBaseAddr = 0xFFFF8000; //PCH_LAN_MBARB_BASE_ADDRESS;

  for (Index = 0; Index < GetPchMaxPciePortNum (); Index++)
    PcieConfig->PcieSpeed[Index] = PchPcieAuto;

  HpetConfig->Enable = PCH_DEVICE_ENABLE;
  HpetConfig->Base = HPET_BASE_ADDRESS;


  IoApicConfig->IoApicId = PCH_IO_APIC_ID;
  IoApicConfig->ApicRangeSelect = PCH_APIC_RANGE_SELECT;
  IoApicConfig->IoApicEntry24_39 = PCH_DEVICE_ENABLE;

  if(SbSetupData != NULL) {
      GbeConfig->EnableGbe = SbSetupData->PchLan;

      if ((READ_MEM16_RCRB(R_PCH_SPI_HSFS) & B_PCH_SPI_HSFS_FDV) == B_PCH_SPI_HSFS_FDV) {
        RESET_MEM32_RCRB(R_PCH_SPI_FDOC, (UINT32) (B_PCH_SPI_FDOC_FDSS_MASK | B_PCH_SPI_FDOC_FDSI_MASK));
        SET_MEM32_RCRB(R_PCH_SPI_FDOC, (UINT32) (V_PCH_SPI_FDOC_FDSS_PCHS | R_PCH_SPI_STRP9));
        if ((READ_MEM32_RCRB (R_PCH_SPI_FDOD) & B_PCH_SPI_STRP9_GBE_PCIE_EN) == 0) {
           GbeConfig->EnableGbe = PCH_DEVICE_DISABLE;
        }
      }

      PchPlatformPolicyPpi->Port80Route = SbSetupData->Port80Route; // 0 - Forward to LPC. 1 - Forward to PCI.
      SataConfig->SataMode = SbSetupData->SataInterfaceMode;
      SataConfig->SataTraceConfig = SataTraceConfig;
//      HpetConfig->Enable = SbSetupData->Hpet; // Force HPET enabled for MRC initialization.
																			// [EIP106687]>
      for (Index = 0; Index < GetPchMaxPciePortNum (); Index++){
         PcieConfig->PcieSpeed[Index] = SbSetupData->PcieRootPortSpeed[Index];

         //Enhance Detect Non-Compliance PCIE Device
         if ((SbSetupData->PcieRPDetectNonComplaint[Index] == 1) && (SbSetupData->PcieRootPortEn[0]!= 0))
            SbPcieDetectNonComplaintPcieDevice(PeiServices, Index, PcieConfig, SbSetupData);
      }
																			// <[EIP106687]
      //In case of recovery change the SATA mode to IDE
      (*PeiServices)->GetBootMode (PeiServices, &BootMode);
      if(BootMode == BOOT_IN_RECOVERY_MODE) {
        SataConfig->SataMode = PchSataModeIde;
      }

      SataTraceConfig->TestMode        = PCH_DEVICE_DISABLE;
      PEI_TRACE((-1,PeiServices, "SBPei SATA RxEq Policy setting:\n"));
      for( PortIndex = 0; PortIndex < GetPchMaxSataPortNum(); PortIndex++ ) {
          SataTraceConfig->PortRxEq[PortIndex].GenSpeed[0].Enable = SataLengthConfigTable[PortIndex].SataGen1RxEqEnable;
          SataTraceConfig->PortRxEq[PortIndex].GenSpeed[1].Enable = SataLengthConfigTable[PortIndex].SataGen2RxEqEnable;
          SataTraceConfig->PortRxEq[PortIndex].GenSpeed[2].Enable = SataLengthConfigTable[PortIndex].SataGen3RxEqEnable;
          SataTraceConfig->PortRxEq[PortIndex].GenSpeed[0].RxEq = SataLengthConfigTable[PortIndex].SataGen1RxEqValue;
          SataTraceConfig->PortRxEq[PortIndex].GenSpeed[1].RxEq = SataLengthConfigTable[PortIndex].SataGen2RxEqValue;
          SataTraceConfig->PortRxEq[PortIndex].GenSpeed[2].RxEq = SataLengthConfigTable[PortIndex].SataGen3RxEqValue;
          PEI_TRACE((-1,PeiServices, "SATA Port%x: %x %x %x %x %x %x\n", PortIndex,\
                        SataLengthConfigTable[PortIndex].SataGen1RxEqEnable, SataLengthConfigTable[PortIndex].SataGen1RxEqValue,\
                        SataLengthConfigTable[PortIndex].SataGen2RxEqEnable, SataLengthConfigTable[PortIndex].SataGen2RxEqValue,\
                        SataLengthConfigTable[PortIndex].SataGen3RxEqEnable, SataLengthConfigTable[PortIndex].SataGen3RxEqValue));
      }
      // 
      // Thermal configuration - Initialize policy to SETUP values.
      // 
#if defined   iME_SUPPORT && iME_SUPPORT
      MemoryThrottling->Enable = SbSetupData->TrEnabled;
#else
      MemoryThrottling->Enable = PCH_DEVICE_DISABLE;
#endif
      MemoryThrottling->TsGpioPinSetting[TsGpioC].PmsyncEnable     = TSGPIO_C_PMSYN;
      MemoryThrottling->TsGpioPinSetting[TsGpioD].PmsyncEnable     = TSGPIO_D_PMSYN;
      MemoryThrottling->TsGpioPinSetting[TsGpioC].C0TransmitEnable = TSGPIO_C_C0_TRANSMIT;
      MemoryThrottling->TsGpioPinSetting[TsGpioD].C0TransmitEnable = TSGPIO_D_C0_TRANSMIT;
      MemoryThrottling->TsGpioPinSetting[TsGpioC].PinSelection     = TSGPIO_C_PIN_SEL;
      MemoryThrottling->TsGpioPinSetting[TsGpioD].PinSelection     = TSGPIO_D_PIN_SEL;
      ///
      /// UsbConfig should be initialized based on platform configuration if UsbPrecondition feature is
      /// enabled. Otherwise, the remaining data of UsbConfig can stay in zero.
      ///
      UsbConfig->UsbPrecondition = SbSetupData->UsbPrecondition;
#ifdef RAPID_START_FLAG
      if (RapidStartResumeCheck () == TRUE) {
        ///
        /// This is RapidStart resume, skip the UsbPrecondition feature in PEI phase
        ///
    	  UsbConfig->UsbPrecondition = 0;
  	  }
#endif

#ifdef USB_PRECONDITION_ENABLE_FLAG
  ///
  /// Update Precondition option for S4 resume. 
  /// Skip Precondition for S4 resume in case this boot may not connect BIOS USB driver.
  /// If BIOS USB driver will be connected always for S4, then disable below update.
  /// To keep consistency during boot, must enabled or disabled below function in both PEI and DXE
  /// PlatformPolicyInit driver.
  ///
  if (UsbConfig->UsbPrecondition == TRUE) {
    (*PeiServices)->GetBootMode (PeiServices, &BootMode);
    if ((BootMode == BOOT_ON_S4_RESUME) || (BootMode == BOOT_IN_RECOVERY_MODE)){
      UsbConfig->UsbPrecondition = FALSE;
      PEI_TRACE((-1,PeiServices, "BootMode is BOOT_ON_S4_RESUME or BOOT_IN_RECOVERY_MODE, disable Precondition"));
    }
  }
#endif  // USB_PRECONDITION_ENABLE_FLAG

      if (UsbConfig->UsbPrecondition) {
#if defined   iAMT_SUPPORT && iAMT_SUPPORT
        UsbConfig->Ehci1Usbr         = PCH_DEVICE_DISABLE;
        UsbConfig->Ehci2Usbr         = PCH_DEVICE_DISABLE;
#else
        UsbConfig->Ehci1Usbr         = PCH_DEVICE_DISABLE;
        UsbConfig->Ehci2Usbr         = PCH_DEVICE_DISABLE;
#endif

#if defined   iME_SUPPORT && iME_SUPPORT
        Status = (*PeiServices)->LocatePpi( PeiServices,
                                            &gEfiPeiReadOnlyVariable2PpiGuid,
                                            0,
                                            NULL,
                                            &ReadOnlyVariable );
        if (ReadOnlyVariable != NULL) {
          VariableSize = sizeof (MeBiosExtensionSetupData);
          Status = ReadOnlyVariable->GetVariable( ReadOnlyVariable,
                                                  EfiMeBiosExtensionSetupName,
                                                  &EfiMeBiosExtensionSetupGuid,
                                                  NULL,
                                                  &VariableSize,
                                                  &MeBiosExtensionSetupData );
          if (!EFI_ERROR (Status)) {
            UsbConfig->Ehci1Usbr |= (MeBiosExtensionSetupData.KvmEnable & KVM_ENABLE);
            UsbConfig->Ehci2Usbr |= (MeBiosExtensionSetupData.KvmEnable & KVM_ENABLE);
          }
        }
#endif

        UsbConfig->Usb20Settings[0].Enable = SbSetupData->PchUsb20[0];
        if (PchSeries == PchLp) {
          // [ EIP219399 ]
    	  //UsbOverCurrentMapping[LPTH_USB_MAX_PHYSICAL_PORTS]=ULT_USB_OVER_CURRENT_MAPPING_SETTINGS;
          UINT8     UltUsbOverCurrentMapping[LPTH_USB_MAX_PHYSICAL_PORTS] = {ULT_USB_OVER_CURRENT_MAPPING_SETTINGS};          
          (*PeiServices)->CopyMem(UsbOverCurrentMapping, UltUsbOverCurrentMapping, LPTH_USB_MAX_PHYSICAL_PORTS);

          UsbConfig->Usb20Settings[1].Enable = PCH_DEVICE_DISABLE;
        } else {
          UsbConfig->Usb20Settings[1].Enable = SbSetupData->PchUsb20[1];
        }

        if ((UsbConfig->Usb20Settings[0].Enable == PCH_DEVICE_DISABLE) &&
            (UsbConfig->Usb20Settings[1].Enable == PCH_DEVICE_DISABLE)) {
          UsbConfig->Usb20Settings[0].Enable = PCH_DEVICE_ENABLE;
          if (PchSeries == PchLp) {
            UsbConfig->Usb20Settings[1].Enable = PCH_DEVICE_ENABLE;
          }
        }

        UsbConfig->UsbPerPortCtl = SbSetupData->PchUsbPerPortCtl;

        for (PortIndex = 0; PortIndex < GetPchUsbMaxPhysicalPortNum (); PortIndex++) {
          if (SbSetupData->PchUsbPerPortCtl != PCH_DEVICE_DISABLE) {
            UsbConfig->PortSettings[PortIndex].Enable = SbSetupData->PchUsbPort[PortIndex];
          } else {
            UsbConfig->PortSettings[PortIndex].Enable = PCH_DEVICE_ENABLE;
          }

          UsbConfig->Usb20OverCurrentPins[PortIndex]  = UsbOverCurrentMapping[PortIndex];
          UsbConfig->PortSettings[PortIndex].Usb20PortLength = UsbPortLength[PortIndex];
          UsbConfig->PortSettings[PortIndex].Location = UsbPortLocation[PortIndex];

          if (PchSeries == PchH) {
            if (IS_PCH_LPT_LPC_DEVICE_ID_DESKTOP (LpcDeviceId)) {
              if (UsbConfig->PortSettings[PortIndex].Location == PchUsbPortLocationBackPanel) {
                UsbConfig->PortSettings[PortIndex].Usb20EyeDiagramTuningParam1 = 4; //Back Panel
              } else {
                UsbConfig->PortSettings[PortIndex].Usb20EyeDiagramTuningParam1 = 3; //Front Panel        
              }

              if (UsbConfig->PortSettings[PortIndex].Location == PchUsbPortLocationBackPanel) {
                if (UsbConfig->PortSettings[PortIndex].Usb20PortLength < 0x80) {
                  UsbConfig->PortSettings[PortIndex].Usb20EyeDiagramTuningParam2 = 2; //Back Panel, less than 7.9"
                } else if (UsbConfig->PortSettings[PortIndex].Usb20PortLength < 0x130) {
                  UsbConfig->PortSettings[PortIndex].Usb20EyeDiagramTuningParam2 = 3; //Back Panel, 8"-12.9"
                } else {
                  UsbConfig->PortSettings[PortIndex].Usb20EyeDiagramTuningParam2 = 4; //Back Panel, 13" onward
                }
              } else {
                UsbConfig->PortSettings[PortIndex].Usb20EyeDiagramTuningParam2 = 2; //Front Panel
              }
            } else if (IS_PCH_LPT_LPC_DEVICE_ID_MOBILE (LpcDeviceId)) {
              	if (UsbConfig->PortSettings[PortIndex].Location == PchUsbPortLocationInternalTopology) {
          			UsbConfig->PortSettings[PortIndex].Usb20EyeDiagramTuningParam1 = 5; // Internal Topology
        		} else if (UsbConfig->PortSettings[PortIndex].Location == PchUsbPortLocationDock) {
          			UsbConfig->PortSettings[PortIndex].Usb20EyeDiagramTuningParam1 = 4; // Dock
        		} else {
          			if (UsbConfig->PortSettings[PortIndex].Usb20PortLength < 0x70) {
            			UsbConfig->PortSettings[PortIndex].Usb20EyeDiagramTuningParam1 = 5; //Back Panel, less than 7"
          			} else {
            			UsbConfig->PortSettings[PortIndex].Usb20EyeDiagramTuningParam1 = 6; //Back Panel, 7" onward
          			}
        		}

        		if (UsbConfig->PortSettings[PortIndex].Location == PchUsbPortLocationInternalTopology) {
          			UsbConfig->PortSettings[PortIndex].Usb20EyeDiagramTuningParam2 = 2; // Internal Topology
        		} else if (UsbConfig->PortSettings[PortIndex].Location == PchUsbPortLocationDock) {
          			if (UsbConfig->PortSettings[PortIndex].Usb20PortLength < 0x50) {
            			UsbConfig->PortSettings[PortIndex].Usb20EyeDiagramTuningParam2 = 1; //Dock, less than 5"
          			} else {
            			UsbConfig->PortSettings[PortIndex].Usb20EyeDiagramTuningParam2 = 2; //Dock, 5" onward
          			}
        		} else {
          			if (UsbConfig->PortSettings[PortIndex].Usb20PortLength < 0x100) {
            			UsbConfig->PortSettings[PortIndex].Usb20EyeDiagramTuningParam2 = 2; //Back Panel, less than 10"
          			} else {
            			UsbConfig->PortSettings[PortIndex].Usb20EyeDiagramTuningParam2 = 3; //Back Panel, 10" onward
          			}
        		}
            }
          } else if (PchSeries == PchLp) {
            if ((UsbConfig->PortSettings[PortIndex].Location == PchUsbPortLocationBackPanel) || 
          	(UsbConfig->PortSettings[PortIndex].Location == PchUsbPortLocationMiniPciE)) {
        		if (UsbConfig->PortSettings[PortIndex].Usb20PortLength < 0x70) {
          			UsbConfig->PortSettings[PortIndex].Usb20EyeDiagramTuningParam1 = 5; //Back Panel, less than 7"
        		} else {
          			UsbConfig->PortSettings[PortIndex].Usb20EyeDiagramTuningParam1 = 6; //Back Panel, 7" onward
        		}
      		} else if (UsbConfig->PortSettings[PortIndex].Location == PchUsbPortLocationDock) {
        		UsbConfig->PortSettings[PortIndex].Usb20EyeDiagramTuningParam1 = 4; // Dock
      		} else {
        		UsbConfig->PortSettings[PortIndex].Usb20EyeDiagramTuningParam1 = 5; // Internal Topology
      		} 

      		if ((UsbConfig->PortSettings[PortIndex].Location == PchUsbPortLocationBackPanel) || 
          	(UsbConfig->PortSettings[PortIndex].Location == PchUsbPortLocationMiniPciE)) {
        		if (UsbConfig->PortSettings[PortIndex].Usb20PortLength < 0x100) {
          			UsbConfig->PortSettings[PortIndex].Usb20EyeDiagramTuningParam2 = 2; //Back Panel, less than 10"
        		} else {
          			UsbConfig->PortSettings[PortIndex].Usb20EyeDiagramTuningParam2 = 3; //Back Panel, 10" onward
        		}
      		} else if (UsbConfig->PortSettings[PortIndex].Location == PchUsbPortLocationDock) {
        		if (UsbConfig->PortSettings[PortIndex].Usb20PortLength < 0x50) {
          			UsbConfig->PortSettings[PortIndex].Usb20EyeDiagramTuningParam2 = 1; //Dock, less than 5"
        		} else {
          			UsbConfig->PortSettings[PortIndex].Usb20EyeDiagramTuningParam2 = 2; //Dock, 5" onward
        		}
      		} else {
        		UsbConfig->PortSettings[PortIndex].Usb20EyeDiagramTuningParam2 = 2; // Internal Topology
      		}
          }
        }

        UsbConfig->Usb30Settings.Mode             = SbSetupData->PchUsb30Mode;

  		//
  		// Automatically disable EHCI when XHCI Mode is Enabled to save power.
  		//
  		if (UsbConfig->Usb30Settings.Mode == 1) {
    		UsbConfig->Usb20Settings[0].Enable = PCH_DEVICE_DISABLE;
    		if (PchSeries == PchH) {
      			UsbConfig->Usb20Settings[1].Enable = PCH_DEVICE_DISABLE;
    		}
  		}

        if (SbSetupData->PchUsb30Mode == 3) {
          UsbConfig->Usb30Settings.PreBootSupport = 1;
        } else {
          UsbConfig->Usb30Settings.PreBootSupport = SbSetupData->PchUsb30PreBootSupport;
        }

        if (SbSetupData->PchUsb30Mode == 4) {
          UsbConfig->Usb30Settings.Mode           = 2;
          UsbConfig->Usb30Settings.ManualMode     = PCH_DEVICE_ENABLE;
        } else {
          UsbConfig->Usb30Settings.ManualMode     = PCH_DEVICE_DISABLE;
        }

  		//
  		// XhciIdleL1 can be set to disable for LPT-LP Ax stepping to workaround USB3 hot plug will fail after 1 hot plug removal. 
  		//
  		UsbConfig->Usb30Settings.XhciIdleL1 = SbSetupData->PchUsb30IdleL1;

      //
      // Btcg is for enabling/disabling trunk clock gating.
      //
      UsbConfig->Usb30Settings.Btcg = SbSetupData->PchUsb30Btcg;

        for (PortIndex = 0; PortIndex < GetPchUsbMaxPhysicalPortNum (); PortIndex++) {
          if (SbSetupData->PchUsb20PinRoute == 1){
            UsbConfig->Usb30Settings.ManualModeUsb20PerPinRoute[PortIndex] = 0;
          } else if (SbSetupData->PchUsb20PinRoute == 2){
            UsbConfig->Usb30Settings.ManualModeUsb20PerPinRoute[PortIndex] = 1;
          } else {
            UsbConfig->Usb30Settings.ManualModeUsb20PerPinRoute[PortIndex] = SbSetupData->ManualModeUsb20PerPinRoute[PortIndex];
          }
        }

        for (PortIndex = 0; PortIndex < GetPchXhciMaxUsb3PortNum (); PortIndex++) {
          if (SbSetupData->PchUsb30PinEnable == 1){
            UsbConfig->Usb30Settings.ManualModeUsb30PerPinEnable[PortIndex] = 0;
          } else if (SbSetupData->PchUsb30PinEnable == 2){
            UsbConfig->Usb30Settings.ManualModeUsb30PerPinEnable[PortIndex] = 1;
          } else {
            UsbConfig->Usb30Settings.ManualModeUsb30PerPinEnable[PortIndex] = SbSetupData->ManualModeUsb30PerPinEnable[PortIndex];
          }
          UsbConfig->Usb30OverCurrentPins[PortIndex]   = Usb30OverCurrentMapping[PortIndex];
        }
      } // if (UsbConfig->UsbPrecondition)

    if (IS_PCH_LPT_LPC_DEVICE_ID_MOBILE (LpcDeviceId)) {
      // Save R_PCH_LPC_ENABLES in Data16.
      Data16 = READ_PCI16_SB(R_PCH_LPC_ENABLES);

      if (!(Data16 & B_PCH_LPC_ENABLES_MC_EN))
        SET_PCI16_SB(R_PCH_LPC_ENABLES, B_PCH_LPC_ENABLES_MC_EN);

      if (READ_IO8(0x66) != 0xFF) PlatformData->EcPresent = 1;

      // Restore R_PCH_LPC_ENABLES.
      WRITE_PCI16_SB(R_PCH_LPC_ENABLES, Data16);
    }

  } // (SbSetupData != NULL)

  ///
  /// PlatformData->SmmBwp value directly depends on the value of CpuConfig->Pfat
  /// (found in CpuPolicyInitPei.c file)
  /// If CpuConfig->Pfat is set to 1 (enabled) then
  ///   PlatformData->SmmBwp has to be set to 1 (enabled)
  /// This is a PFAT Security requirement that needs to be addressed
  /// If CpuConfig->Pfat is set to 0 (disabled) then
  ///   PlatformData->SmmBwp value don't care, it can be set to either
  ///   1 (enabled) or 0 (disabled) based on customer implementation
  ///
  PlatformData->SmmBwp    = 0;

  ///
  /// Temporary Memory Base Address for PCI devices to be used to initialize MMIO registers.
  /// Minimum size is 64KB bytes.
  ///
  PlatformData->TempMemBaseAddr = SB_TEMP_MMIO_BASE;

  PchPlatformPolicyPpiDesc->Flags = EFI_PEI_PPI_DESCRIPTOR_PPI | EFI_PEI_PPI_DESCRIPTOR_TERMINATE_LIST;
  PchPlatformPolicyPpiDesc->Ppi = PchPlatformPolicyPpi;

  //
  // Install OEM PCH Platform Policy Override PPI
  //
  PchPlatformPolicyPpiDesc->Guid = &gOemPchPlatformPolicyOverridePpiGuid;
  Status = (**PeiServices).InstallPpi (PeiServices, PchPlatformPolicyPpiDesc);
  ASSERT_PEI_ERROR (PeiServices, Status);

  //
  // Install PCH Platform Policy PPI
  //
  PchPlatformPolicyPpiDesc->Guid = &gPchPlatformPolicyPpiGuid;
  Status = (**PeiServices).InstallPpi (PeiServices, PchPlatformPolicyPpiDesc);
  ASSERT_PEI_ERROR (PeiServices, Status);

                                        // [EIP120438]>
  if ((HpetConfig->Enable) && (HpetConfig->Base != 0)) {
    WRITE_MEM32(HpetConfig->Base + 0xF0, 0);
  }
                                        // <[EIP120438]

  return EFI_SUCCESS;

}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:   ProgramSBRegAfterMrc 
//
// Description: This function can be used to program any SB regisater after
//              memory is detected.
//
// Input:       PeiServices      - Pointer to the PEI services table
//              NotifyDescriptor - Pointer to the descriptor for the
//                                 notification event.
//              InvokePpi        - Pointer to the PPI that was installed
//
// Output:      EFI_STATUS
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS ProgramSBRegAfterMrc (
    IN EFI_PEI_SERVICES             **PeiServices,
    IN EFI_PEI_NOTIFY_DESCRIPTOR    *NotifyDescriptor,
    IN VOID                         *InvokePpi )
{
    EFI_STATUS                      Status = EFI_SUCCESS;
    IN EFI_BOOT_MODE                BootMode;
    EFI_PEI_READ_ONLY_VARIABLE2_PPI *ReadOnlyVariable;
    UINTN                           VariableSize;
    EFI_GUID                        WarmResetGuid = SB_WARM_RESET_GUID;
    CHAR16                          WarmResetVar[] = SB_WARM_RESET_VARIABLE;
    UINT32                          WarmResetFlag = 0;
#if Capsule2_0_SUPPORT
    PEI_CAPSULE_PPI                 *Capsule;
#endif

    PEI_TRACE((-1,PeiServices, "ProgramSBRegAfterMrc(): Start.\n"));

    Status = (*PeiServices)->GetBootMode( PeiServices, &BootMode );

    if (BootMode == BOOT_ON_S3_RESUME) {

        PEI_TRACE((-1,PeiServices, "ProgramSBRegAfterMrc(): S3 Resume.\n"));

        Status = (*PeiServices)->LocatePpi( PeiServices, \
                                        &gEfiPeiReadOnlyVariable2PpiGuid, \
                                        0, \
                                        NULL, \
                                        &ReadOnlyVariable );
        if (!EFI_ERROR(Status)) {
            VariableSize = sizeof(WarmResetFlag);
            Status = ReadOnlyVariable->GetVariable( ReadOnlyVariable, \
                                                    WarmResetVar, \
                                                    &WarmResetGuid, \
                                                    NULL, \
                                                    &VariableSize, \
                                                    &WarmResetFlag );
            if (WarmResetFlag == SB_WARM_RESET_TAG) {
                PEI_TRACE((-1,PeiServices, "ProgramSBRegAfterMrc(): Update BootMode.\n"));
                BootMode = BOOT_WITH_FULL_CONFIGURATION;

#if Capsule2_0_SUPPORT
                //
                // Update BootMode, if Capsule 2.0 PPI is available.
                //
                Status = (*PeiServices)->LocatePpi ( PeiServices, \
                                                     &gPeiCapsulePpiGuid, \
                                                     0, \
                                                     NULL, \
                                                     &Capsule);

                if (!EFI_ERROR(Status)) {
                  BootMode = BOOT_ON_FLASH_UPDATE;
                  Status = (*PeiServices)->NotifyPpi( PeiServices, EndOfMrcNotifyList );

                } else {
                  // Clear ACPI Sleep Type 
                  RESET_IO32_PM(ACPI_IOREG_PM1_CNTL, 0x1c00 ); // 0x04
                }

                (*PeiServices)->SetBootMode(PeiServices, BootMode);
#else
                (*PeiServices)->SetBootMode(PeiServices, BootMode);
                // Clear ACPI Sleep Type 
                RESET_IO32_PM(ACPI_IOREG_PM1_CNTL, 0x1c00 ); // 0x04
#endif
            }
        }
    }

    PEI_TRACE((-1,PeiServices, "ProgramSBRegAfterMrc(): End.\n"));

    return EFI_SUCCESS;
}


//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:   ProgramSBRegEndOfMrc
//
// Description: This function can be used to program any SB regisater at
//              end of MRC.
//
// Input:       PeiServices      - Pointer to the PEI services table
//              NotifyDescriptor - Pointer to the descriptor for the
//                                 notification event.
//              InvokePpi        - Pointer to the PPI that was installed
//
// Output:      EFI_STATUS
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS ProgramSBRegEndOfMrc (
    IN EFI_PEI_SERVICES             **PeiServices,
    IN EFI_PEI_NOTIFY_DESCRIPTOR    *NotifyDescriptor,
    IN VOID                         *InvokePpi )
{
    IN EFI_BOOT_MODE                BootMode;
    EFI_STATUS                      Status;
    VOID                            *RecoveryModePpi;

    PEI_TRACE((-1,PeiServices, "ProgramSBRegEndOfMrc(): Start.\n"));

    Status = (*PeiServices)->LocatePpi (PeiServices, \
                                        &gRecoveryBootModeGuid, \
                                        0, \
                                        NULL, \
                                        &RecoveryModePpi);

    if (EFI_ERROR(Status)) {
      // Update Bootmode
      (*PeiServices)->GetBootMode( PeiServices, &BootMode );
      PEI_TRACE((-1,PeiServices, "Before change BootMode = %X\n", BootMode));
      BootMode = BOOT_WITH_FULL_CONFIGURATION;
      (*PeiServices)->SetBootMode(PeiServices, BootMode);
    }
    PEI_TRACE((-1,PeiServices, "ProgramSBRegEndOfMrc(): End.\n"));

    return EFI_SUCCESS;
}

#if SB_RESET_PPI_SUPPORT

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:   SBPEI_ResetSystem
//
// Description: This function is the reset call interface function published
//              by the reset PPI
//
// Input:       PeiServices     Pointer to the PEI services table
//
// Output:      SYSTEM RESET
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS SBPEI_ResetSystem (
    IN EFI_PEI_SERVICES         **PeiServices )
{
#if WdtPei_SUPPORT
    WDT_PPI      *Wdt;
    EFI_STATUS   Status;

    Status = (*PeiServices)->LocatePpi ( PeiServices, \
                                         &gWdtPpiGuid, \
                                         0, \
                                         NULL, \
                                         &Wdt );
  
    ASSERT_PEI_ERROR (PeiServices, Status);
  
    Wdt->AllowKnownReset();
#endif

    SBLib_ResetSystem(EfiResetCold);

    // We should never get this far
    return EFI_SUCCESS;
}

#endif

#if SB_STALL_PPI_SUPPORT

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:   SBPEI_Stall
//
// Description: This function provides a blocking stall at least number
//              of microseconds by SB ACPI timer
//
// Input:       PeiServices  - Pointer to the PEI services table
//              This         - Pointer to the Stall PPI
//              MicroSeconds - Number of microseconds for which to stall
//
// Output:      None
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS SBPEI_Stall (
    IN EFI_PEI_SERVICES     **PeiServices, 
    IN EFI_PEI_STALL_PPI    *This, 
    IN UINTN                MicroSeconds )
{
    EFI_STATUS              Status;
    EFI_PEI_PCI_CFG2_PPI     *PciCfg;

    // Locate PciCfg PPI
    PciCfg = (*PeiServices)->PciCfg;

    // At this time no manipulation needed.  The value passed in is in
    // MicroSeconds(us) and that is what the library function uses

    // Call Library function that is shared with Metronome
    // Architecture Protocol


    Status = CountTime(MicroSeconds, PM_BASE_ADDRESS);

    return Status;
}

#endif

#if ATAPI_RECOVERY_SUPPORT

EFI_GUID gIdeRecoveryNativeModePpiGuid = \
                                        PEI_IDE_RECOVERY_NATIVE_MODE_PPI_GUID;

PEI_IDE_RECOVERY_NATIVE_MODE_PPI IdeRecoveryNativeModePpi = {
                                                    SB_TEMP_IO_BASE+0x200,
                                                    SB_TEMP_IO_BASE+0x282,
                                                    SB_TEMP_IO_BASE+0x300,
                                                    SB_TEMP_IO_BASE+0x382
};

EFI_PEI_PPI_DESCRIPTOR IdeRecoveryNativeModePpiDescriptor = {
    (EFI_PEI_PPI_DESCRIPTOR_PPI | EFI_PEI_PPI_DESCRIPTOR_TERMINATE_LIST), \
    &gIdeRecoveryNativeModePpiGuid, &IdeRecoveryNativeModePpi
};

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:   InitSATARegs
//
// Description: This function initializes SATA controller registers
//              for ATA/ATAPI recovery support.
//
// Input:       PeiServices - Pointer to the PEI services table
//              PciCfg      - Pointer to the PCI Configuration PPI
//
// Output:      None
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

VOID InitSATARegs (
    IN EFI_PEI_SERVICES         **PeiServices,
    IN EFI_PEI_PCI_CFG2_PPI     *PciCfg
)
{
    // TODO
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:   EnableAtaChannel
//
// Description: This function enables the specific channel of ATA/SATA
//              controller(s) depend on input ChannelMask
//
// Input:       PeiServices - Pointer to the PEI services table
//              This        - Pointer to the ATA Controller PPI
//              ChannelMask - Mask for the specific channel.
//
// Output:      EFI_STATUS
//
// Notes:       Normally we have to enables all chennels on ATA/SATA
//              controller(s) regardless of ChannelMask.
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS EnableAtaChannel (
    IN EFI_PEI_SERVICES               **PeiServices,
    IN PEI_ATA_CONTROLLER_PPI         *This,
    IN UINT8                          ChannelMask )
{
  EFI_STATUS              Status;

  // SATA 0 (B0:D31:F2)
  // Initialize the controller to IDE mode
  RW_PCI8_SATA(R_PCH_SATA_MAP, 0, B_PCH_SATA_MAP_SMS_MASK | B_PCH_SATA_PORT_TO_CONTROLLER_CFG);  // [EIP86096]>>

  //Enable the SATA2 for setting IDE mode to recovery
  RESET_MEM32_RCRB (R_PCH_RCRB_FUNC_DIS ,BIT25);						 // <<[EIP86096]

  // Initialize Primary/Secondary IDE controller to operate in Legacy mode
  RW_PCI8_SATA(R_PCH_SATA_PI_REGISTER, 0, B_PCH_SATA_PI_REGISTER_PNE | B_PCH_SATA_PI_REGISTER_SNE);

  // Enable IO space decode
  RW_PCI16_SATA(R_PCH_SATA_COMMAND, B_PCH_SATA_COMMAND_IOSE, 0);

  if ((ChannelMask & PEI_ICH_IDE_PRIMARY) == PEI_ICH_IDE_PRIMARY)
    // Enable Primary IDE Controller decode
    RW_PCI16_SATA(R_PCH_SATA_TIMP, B_PCH_SATA_TIM_IDE, 0);

  if ((ChannelMask & PEI_ICH_IDE_SECONDARY) == PEI_ICH_IDE_SECONDARY)
    // Enable Secondary IDE Controller decode
    RW_PCI16_SATA(R_PCH_SATA_TIMS, B_PCH_SATA_TIM_IDE, 0);

  // Enable SATA ports 0, 1, 2 and 3.
  RW_PCI16_SATA(R_PCH_SATA_PCS, (B_PCH_SATA_PCS_PORT0_EN | B_PCH_SATA_PCS_PORT1_EN | B_PCH_SATA_PCS_PORT2_EN | B_PCH_SATA_PCS_PORT3_EN), 0);

  // SATA 1 (B0:D31:F5)
  RW_PCI16_SATA2(R_PCH_SATA_PCMD_BAR, SB_TEMP_IO_BASE + 0x200, 0);
  RW_PCI16_SATA2(R_PCH_SATA_PCNL_BAR, SB_TEMP_IO_BASE + 0x282, 0);
  RW_PCI16_SATA2(R_PCH_SATA_SCMD_BAR, SB_TEMP_IO_BASE + 0x300, 0);
  RW_PCI16_SATA2(R_PCH_SATA_SCNL_BAR, SB_TEMP_IO_BASE + 0x382, 0);

  // Enable IO space decode
  RW_PCI16_SATA2(R_PCH_SATA_COMMAND, B_PCH_SATA_COMMAND_IOSE, 0);

  if ((ChannelMask & PEI_ICH_IDE_PRIMARY) == PEI_ICH_IDE_PRIMARY)
    // Enable Primary IDE Controller decode
    RW_PCI16_SATA2(R_PCH_SATA_TIMP, B_PCH_SATA_TIM_IDE, 0);

  if ((ChannelMask & PEI_ICH_IDE_SECONDARY) == PEI_ICH_IDE_SECONDARY)
    // Enable Secondary IDE Controller decode
    RW_PCI16_SATA2(R_PCH_SATA_TIMS, B_PCH_SATA_TIM_IDE, 0);

  // Enable SATA1 ports 0(4) and 1(5).
  RW_PCI16_SATA2(R_PCH_SATA_PCS, (B_PCH_SATA_PCS_PORT0_EN | B_PCH_SATA_PCS_PORT1_EN), 0);

  // Delay 1ms for HDD devices ready.
  CountTime(1000, PM_BASE_ADDRESS);

  Status = (**PeiServices).InstallPpi( PeiServices, \
                                         &IdeRecoveryNativeModePpiDescriptor);
  if (EFI_ERROR (Status)) return Status;

  return EFI_SUCCESS;
}
#endif // ATAPI_RECOVERY_SUPPORT



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
