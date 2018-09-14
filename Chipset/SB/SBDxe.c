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
// $Header: /Alaska/Projects/Intel/Haswell/LynxPoint_SharkBay-DT_Crb_1AQQW/Chipset/SB/SBDxe.c 1     11/02/17 1:48a Chienhsieh $
//
// $Revision: 1 $
//
// $Date: 11/02/17 1:48a $
//*************************************************************************
// Revision History
// ----------------
// $Log: /Alaska/Projects/Intel/Haswell/LynxPoint_SharkBay-DT_Crb_1AQQW/Chipset/SB/SBDxe.c $
// 
// 1     11/02/17 1:48a Chienhsieh
// [TAG]  		EIP357393
// [Category]  	Improvement
// [Description]  	[SAx0039] SPI opcode Security Vulnerability
// [Files]  		Chipset\SB\SBDxe.c
// ReferenceCode\Chipset\LynxPoint\PchInit\Dxe\PchInit.c
// 
// 100   1/29/15 4:09a Mirayang
// [TAG]  		EIP200269 
// [Category]  	New Feature
// [Description]  	For add FlashSmi : Label 4.6.5.5_FlashSmi_00
// ($/Alaska/SOURCE/Modules/FlashSmi)
// 
// 99    9/05/14 3:30a Mirayang
// [TAG]  		EIP182598
// [Category]  	Bug Fix
// [Severity]  	Normal
// [Symptom]  	Missing ULT differentiation in
// InstallDxePchPlatformPolicy() for GbE slot number detection
// [RootCause]  	In InstallDxePchPlatformPolicy(), there is a ULT
// differentiation missing. 
// [Solution]  	The strap readout, is not the same for LynxPoint LP. Add
// determine to set value.
// 
// 98    5/20/14 2:15a Barretlin
// [TAG]  		EIP N/A
// [Category]  	Improvement
// [Description]  	remove unnecessary source code
// [Files]  		SBDxe.c
// 
// 97    5/16/14 6:16a Barretlin
// [TAG]  		EIP167087
// [Category]  	Improvement
// [Description]  	BIOS security improvement on Haswell CRB project
// [Files]  		SBGeneric.c SBDxe.c SBCspLib.h Sb.sdl Sb.sd
// 
// 96    5/14/14 1:08p Barretlin
// [TAG]  		EIP167028
// [Category]  	Improvement
// [Description]  	Variable attribute improment
// [Files]  		SB.sd SBDxe.c WdtAppDxe.c
// 
// 95    3/21/14 4:44a Barretlin
// 
// 94    3/20/14 8:41a Barretlin
// [TAG]  		EIP158783
// [Category]  	Improvement
// [Description]  	Fix programming error
// [Files]  		SbDxe.c
// 
// 93    3/13/14 11:30a Barretlin
// [TAG]  		EIP153695
// [Category]  	Improvement
// [Description]  	USB Per port control is not reasonable when
// OEM_USBPREPORT_DISABLE_SUPPORT token is Enabled and USB devices are
// behind hubs
// [Files]  		Sb.sdl Sb.sd Sb.uni GetSetupData.c SbDxe.c PchUsbCommon.c
// PchRegsUsb.h
// 
// 92    3/13/14 10:13a Barretlin
// [TAG]  		EIP N/A
// [Category]  	Improvement
// [Description]  	Fix build error when remove or disable CSM module
// [Files]  		SbDxe.c
// 
// 91    11/19/13 7:32a Barretlin
// [TAG]  		EIP141917
// [Category]  	New Feature
// [Description]  	Support SetTimer() with HPET Timer on Lynx Point
// [Files]  		SB.sdl SBGeneric.c SBDxe.c SbHpet.h sbProtocal.cif
// SamrtTimer.sdl
// 
// 90    11/11/13 6:26a Barretlin
// [TAG]  		EIP N/A
// [Category]  	Improvement
// [Description]  	Fix build error
// [Files]  		SBDxe.c
// 
// 89    10/28/13 10:58p Barretlin
// [TAG]  		EIP141266
// [Category]  	Bug Fix
// [Severity]  	Normal
// [Symptom]  	CPU exception error after apply "Save/Restore Bit25 of
// PxCMD" solution
// [RootCause]  	PciIO point is NULL
// [Solution]  	if PciIO point is NULL, skip this Option ROM, because it
// must not be SATA Option Rom
// [Files]  		SBDxe.c
// 
// 88    10/06/13 2:22a Barretlin
// 
// 86    9/17/13 2:00p Barretlin
// [TAG]  		EIP N/A
// [Category]  	Improvement
// [Description]  	set a token to enable/disable SATA DLAE bit
// [Files]  		SB.sdl SBDxe.c
// 
// 85    9/17/13 9:31a Barretlin
// [TAG]  		EIP134850
// [Category]  	New Feature
// [Description]  	Save/Restore Bit25 of PxCMD in Aptio Chipset Module
// [Files]  		SBDxe.c
// 
// 84    9/17/13 8:51a Barretlin
// [TAG]  		EIP N/A
// [Category]  	Improvement
// [Description]  	update AhciPlatformPolicy default value for AHCI module
// rev.24
// [Files]  		SBDxe.c
// 
// 83    8/13/13 7:46a Scottyang
// [TAG]  		EIP132701
// [Category]  	Bug Fix
// [Severity]  	Normal
// [Symptom]  	Coding error.
// [RootCause]  	Incorrect offset of IO APIC data register.
// [Solution]  	Correct the offset.
// [Files]  		SBDxe.c
// 
// 82    8/01/13 4:26a Scottyang
// [TAG]  		None
// [Category]  	Improvement
// [Description]  	Add PCIE LTR setup items.
// [Files]  		SB.sd, SB.uni, SBDxe.c, GetSetupData.c, SbSetupData.c
// 
// 81    7/15/13 10:13p Scottyang
// [TAG]  		None
// [Category]  	Improvement
// [Description]  	Fixed build error at SharkBay DT.
// [Files]  		SBDxe.c
// 
// 80    7/15/13 3:19a Scottyang
// [TAG]  		EIP129089
// [Category]  	Improvement
// [Description]  	Update PCH RC 1.6.1.
// [Files]  		SBDxe.c, SB.asl, ..\ReferenceCode\Chipset\LynxPoint\*.*
// 
// 79    7/12/13 1:51a Scottyang
// [TAG]  		EIP126943
// [Category]  	Improvement
// [Description]  	Create S3 boot script tabel for SATA2 controller even
// SATA1 hiden.
// [Files]  		SBDxe.c
// 
// 78    7/09/13 5:15a Scottyang
// [TAG]  		None
// [Category]  	Improvement
// [Description]  	Create "PCH Cross Throttling" setup item.(Only ULT
// support)
// [Files]  		SBDxe.c, SB.sd, SB.uni, GetSetupData.c, SB.sd 
// 
// 77    7/07/13 10:14p Scottyang
// [TAG]  		EIP127410
// [Category]  	Improvement
// [Description]  	Update DSDT taable when PCIE port swap function enable.
// [Files]  		SBDxe.c
// 
// 76    7/03/13 8:00a Scottyang
// [TAG]  		EIP124410
// [Category]  	Improvement
// [Description]  	Implement SMBIOS type 88h for CRID.
// [Files]  		SBDxe.c, SB.sdl, SB.sd, SBSetup.c, SBSetup.sdl
// 
// 75    6/24/13 7:04a Scottyang
// [TAG]  		EIP127217
// [Category]  	Improvement
// [Description]  	Only update RC's ASL code for L event.
// [Files]  		SBDxe.c, GPE.asl
// 
// 74    6/24/13 6:29a Scottyang
// [TAG]  		EIP127297
// [Category]  	Improvement
// [Description]  	Update PCH RC 1.6.0.
// [Files]  		SB.sd, SBDxe.c, ..\ReferenceCode\Chipset\LynxPoint\*.*
// 
// 73    6/14/13 12:00a Scottyang
// [TAG]  		None
// [Category]  	Improvement
// [Description]  	Make sure the USB preport disable call back function
// processing is performed only once.
// [Files]  		SBDxe.c
// 
// 72    6/13/13 11:53p Scottyang
// [TAG]  		None
// [Category]  	Improvement
// [Description]  	Update RC 150 GNVS.
// [Files]  		SBDxe.c, SB.uni, SB.sd
// 
// 71    6/06/13 10:25p Scottyang
// [TAG]  		None
// [Category]  	Improvement
// [Description]  	Remove XHCB at Dsdt table update.
// [Files]  		SBDxe.c
// 
// 70    6/03/13 3:40a Scottyang
// [TAG]  		EIP125453
// [Category]  	Bug Fix
// [Severity]  	Normal
// [Symptom]  	Build field when enable "FORCE_USER_TO_SETUP_IF_CMOS_BAD"
// [RootCause]  	Miss the header file.
// [Files]  		SBDxe.c
// 
// 69    5/23/13 1:56a Scottyang
// [TAG]  		EIP120623
// [Category]  	Improvement
// [Description]  	LCD turn on automatically when resume from S3.
// [Files]  		SBPEI.c, SBDxe.c, AcpiModeEnable.c
// 
// 68    5/21/13 8:49a Scottyang
// [TAG]  		EIP121740
// [Category]  	Bug Fix
// [Severity]  	Critical
// [Symptom]  	Event log has HAL error after resume from S3.
// [RootCause]  	Coding error for S3 script type.
// [Solution]  	Correct the S3 script type.
// [Files]  		SBDxe.c
// 
// 67    5/20/13 6:21a Scottyang
// [TAG]  		EIP124245
// [Category]  	Improvement
// [Description]  	On S3 resume under Raid mode System may gets hangs.
// [Files]  		SBDxe.c
// 
// 66    5/13/13 8:56a Scottyang
// [TAG]  		EIP123496
// [Category]  	Improvement
// [Description]  	Update PCH RC 1.5.0.
// [Files]  		..\ReferenceCode\Chipset\LynxPoint\*.* , SBDxe.C, SBPEI.c,
// SB.sd, SB.uni, SbSetupData.h, GetSetupData.c
// 
// 65    5/03/13 4:39a Scottyang
// [TAG]  		None
// [Category]  	Improvement
// [Description]  	Make sure Clear the Start and FIS Receive Enable bit
// [Files]  		SBDxe.c
// 
// 64    4/24/13 6:48a Scottyang
// [TAG]  		EIP82149
// [Category]  	Improvement
// [Description]  	 Intel(R) 8 Series Chipset Family Deep Sx and CPU
// Soft-Strap BIOS Override Co-Existence Issue. If the soft-strap override
// feature is required and enabled, BIOS must disable Deep Sx
// functionality.
// [Files]  		SBDxe.c, SB.sd, SBPlatformData.h
// 
// 63    4/15/13 10:50p Wesleychen
// [TAG]           None
// [Category]      Improvement
// [Description]   Hide HPET device if it is disabled. 
// [Files]         SBDXE.c
// 
// 62    4/15/13 10:47p Wesleychen
// [TAG]         EIP120857
// [Category]    Bug Fix
// [Severity]    Normal
// [Symptom]     TCO S3 Boot Script in wrong order.
//               After S3 resume, TCO_EN bit din't be
//               restored.
// [RootCause]   Lockdown TCO bit is set before TCO_EN
//               restore.
// [Solution]    Relocate PM_BASE+ALTGP_SMI_EN & SMI_EN
//               save/restore to SbExitPmAuthProtocolCallback().
// [Files]       SBDxe.c
// 
// 61    4/09/13 11:35p Wesleychen
// [TAG]           EIP120480
// [Category]      Improvement
// [Description]   Always disabling PCH platform policy "ExternalObffEn".
// [Files]         SB.SDL, SBDXE.c
// 
// 59    4/08/13 2:47a Wesleychen
// [TAG]           EIP120159
// [Category]      Improvement
// [Description]   Update for Intel PCH LPT RC140.
//                 Added new tokens:
//                 1. "PCH_RESET_CYCLE_DURATION"
//                 2. "LEGACY_DMA_DISABLE"
// [Files]         SB.SDL, SBDXE.c
// 
// 58    4/08/13 2:37a Wesleychen
// [TAG]         EIP116939
// [Category]    Bug Fix
// [Severity]    Normal
// [Symptom]     The available memory size is less than
//               2GB in Windowss 7 32 bit.
// [RootCause]   The "SB_TEMP_MMIO_BASE" is too low.
// [Solution]    Rearrange "SB_TEMP_MMIO_BASE" to
//               4GB - 16M(ROM) - 64KB (Intel Required).
// [Files]       SB.SDL; SBDxe.c
// 
// 57    3/26/13 5:54a Wesleychen
// [TAG]          None
// [Category]     Improvement
// [Description]  Update the address of operation region "XHCB" for
//                Intel ACPI RC 1.3.1 compatible.
// [Files]        SBDxe.c
// 
// 56    3/22/13 5:15a Scottyang
// [TAG]  		None
// [Category]  	Improvement
// [Description]  	Wireless LAN PHY use SLP_WLAN# pin
// [Files]  		SB.sdl, SBDxe.c
// 
// 55    3/19/13 8:19a Scottyang
// [TAG]  		EIP118158
// [Category]  	Improvement
// [Description]  	Correct SBLib_CmosRead () offset.
// [Files]  		SmiHandlerPorting2.c, SBDxe.c, SBGeneric.c, SBSmm.c,
// SmiHandlerPorting.c
// 
// 54    3/19/13 4:56a Scottyang
// [TAG]  		EIP118480
// [Category]  	Improvement
// [Description]  	Use another array for
// ULT_USB_OVER_CURRENT_MAPPING_SETTINGS.
// [Files]  		SBDxe.c
// 
// 53    3/15/13 3:33a Scottyang
// [TAG]  		EIP118121
// [Category]  	Improvement
// [Description]  	Update PCH RC 1.3.0.
// [Files]  		..\ReferenceCode\Chipset\LynxPoint\*.*, SBDxe.c, SBPEI.c,
// SB.sd, SB.uni, GetSetupData.c, SbSetupData.h
// 
// 51    3/14/13 2:50a Scottyang
// [TAG]  		None
// [Category]  	Improvement
// [Description]  	Fixed coding error for OEM USB preport disable after
// setup menu.
// [Files]  		SBDxe.c
// 
// 49    2/26/13 1:21a Scottyang
// [TAG]  		EIP116154
// [Category]  	Improvement
// [Description]  	Update PCH RC 1.2.0.
// [Files]  		.\ReferenceCode\Chipset\LynxPoint\*.*, SBDxe.c
// 
// 48    2/25/13 5:12a Scottyang
// [TAG]  		EIP113678
// [Category]  	Improvement
// [Description]  	Disable BIOS lock when recovery and capsule BIOS flash.
// [Files]  		SBDxe.c
// 
// 47    2/19/13 10:35p Scottyang
// [TAG]  		None
// [Category]  	Improvement
// [Description]  	Correct UsbOverCurrentMapping array size fot LPT-LP
// [Files]  		SBDxe.c
// 
// 46    2/09/13 12:12a Scottyang
// [TAG]  		EIP114922
// [Category]  	Improvement
// [Description]  	Update PCH RC 1.1.0.
// [Files]  		..\ReferenceCode\Chipset\LynxPoint\*.*, SBDxe.c, SBPEI.c,
// SB.sd, SB.uni, GetSetupData.c, SbSetupDara.h
// 
// 45    1/31/13 10:54a Scottyang
// [TAG]  		None
// [Category]  	Improvement
// [Description]  	Add Serial IO GNVS setup option. 
// [Files]  		SBDxe.c, SB.sd, SB.uni, SbSetupData.h, GetSetupData.c
// 
// 44    1/28/13 4:16a Scottyang
// [TAG]  		EIP108803
// [Category]  	Improvement
// [Description]  	Disable usb port after setup.
// [Files]  		SB.sdl, SBDxe.c, PchUsbCommon.c
// 
// 43    1/27/13 11:01p Scottyang
// [TAG]  		None
// [Category]  	Improvement
// [Description]  	Capsule 2.0 crash dump link function.
// [Files]  		SBPEI.c
// SBDxe.c
// SBRun.c
// 
// 42    1/11/13 2:34a Scottyang
// [TAG]  		EIP92011
// [Category]  	Improvement
// [Description]  	EC SMI inactive when system resume from iRST sleep
// [Files]  		SBDxe.c
// 
// 41    1/11/13 1:51a Scottyang
// [TAG]  		EIP88358
// [Category]  	Improvement
// [Description]  	Add FORCE_USER_TO_SETUP_IF_CMOS_BAD token
// [Files]  		SBDex.c, SBPei.c, RTC.h, SB.sdl
// 
// 40    1/10/13 4:53a Scottyang
// [TAG]  		None
// [Category]  	Improvement
// [Description]  	Create DTIO value and DM value option
// [Files]  		SB.sd, SB.uni, SbSetupData.h, GetSetupData.c, SBDxe.c
// 
// 39    1/04/13 4:47a Scottyang
// [TAG]  		None
// [Category]  	Improvement
// [Description]  	ADSP Interrupt Mode should same with LPSS Interrupt
// Mode
// [Files]  		SBDxe.c
// 
// 38    12/24/12 5:51a Scottyang
// [TAG]  		None
// [Category]  	Improvement
// [Description]  	Add option for XHCI Idel L1 workaroung.
// [Files]  		GetSetupData.c, SbSetupData.h, SB.sd, SB.uni, SBDxe.c,
// SBPEI.c
// 
// 37    12/22/12 2:07a Scottyang
// [TAG]  		None
// [Category]  	Improvement
// [Description]  	Add PCIE "L1 Substates"setup option.
// [Files]  		GetSetupData.c, SbSetupData.h, SB.sd, SB.uni, SBDxe.c
// 
// 36    12/18/12 6:10a Scottyang
// [TAG] EIP109697
// [Category] Improvement
// [Description] Update PCH RC 0.8.1
// [Files] ReferenceCode\Chipset\LynxPoint\*.*, SBDxe.c, SBPEI.c, SB.sd,
// SbSetupData.c, GetSetupDate.c
// 
// 35    12/17/12 6:45a Scottyang
// [TAG]  		None
// [Category]  	Improvement
// [Description]  	Add setup menu for LPSS and ECTG.
// [Files]  		GetSetupData.c
// SbSetupData.h
// SB.sd
// SB.uni
// SBDxe.c
// 
// 34    11/20/12 9:47a Scottyang
// [TAG]  		EIP107014
// [Category]  	Improvement
// [Description]  	Update RC 0.8.0
// [Files]  		ReferenceCode\Chipset\LynxPoint\*.*, SBDxe.c, SBPEI.c,
// SB.sd, SbSetupData.c, GetSetupDate.c
// 
// 33    11/19/12 9:57p Scottyang
// [TAG]  		None
// [Category]  	Improvement
// [Description]  	Support RAID mode device ID for WS and server.
// [Files]  		SBDxe.c, PchSata.c
// 
// 32    11/08/12 9:46a Scottyang
// [TAG] Initialize8259
// 
// [Category] Improvement
// 
// [Description] To prevent the unexpected interrupt asserted in 8259
// initialization.
// 
// [Files] SBDxe.c
// 
// 31    11/08/12 8:44a Scottyang
// [TAG]  		None
// [Category]  	Improvement
// [Description]  	Add device item that connect LPSS.
// [Files]  		GetSetupData.c, SbSetupData.h, SBDxe.c, SB.sd, SB.uni
// 
// 30    11/06/12 8:12a Scottyang
// [TAG]  		None
// [Category]  	Improvement
// [Description]  	Reduce function "GetPchSeries()".
// [Files]  		SBPEI.c, SBDxe.c, SmiHandlerPorting.c, SmiHandlerPorting2.c
// 
// 29    11/05/12 6:24a Scottyang
// [TAG]  		None
// [Category]  	Improvement
// [Description]  	Change memory type for RTC.
// [Files]  		SBDxe.c
// 
// 28    11/01/12 4:57a Scottyang
// [TAG]  		None
// [Category]  	Improvement
// [Description]  	Remove token "SOLUTION_FOR_EIP95440".
// [Files]  		SBDxe.c, SB.sdl
// 
// 27    10/30/12 8:40a Scottyang
// [TAG]  		None
// [Category]  	Improvement
// [Description]  	ULT do not need.
// 
// 26    10/26/12 3:05a Scottyang
// [TAG]  		None
// [Category]  	Bug Fix
// [Severity]  	Normal
// [Symptom]  	After S3 resime R_PCH_SPI_VSCC1 cannot restore.
// [RootCause]  	R_PCH_SPI_VSCC0 set first than R_PCH_SPI_VSCC1 cannot
// restore. 
// [Solution]  	change order for R_PCH_SPI_VSCC1 restore first.
// [Files]  		SBDxe.c
// 
// 25    10/26/12 3:00a Scottyang
// [TAG]  		None
// [Category]  	Improvement
// [Description]  	Change all L event, GPRW and pcidock at DSDT for ULT.
// [Files]  		SBDxe.c
// 
// 24    10/23/12 10:30p Scottyang
// [TAG]  		None
// [Category]  	Improvement
// [Description]  	After S3 resume EC can not use GPI to trigger SMI
// [Files]  		SBDxe.c
// 
// 23    10/23/12 8:28a Scottyang
// [TAG]  		None
// [Category]  	Improvement
// [Description]  	Create Device Sleep at setup menu
// [Files]  		SB.sd, SB.uni, SBDxe.c, GetSetupData.c, SbSetupData.h
// 
// 22    10/23/12 8:17a Scottyang
// [TAG]         EIP73607
// [Category]    Bug Fix
// [Severity]    Normal
// [Symptom]     Intruder Detect state is cleaned by BIOS POST.
// [Files]       SBDXE.c; SBSECInit.asm
// 
// 21    10/23/12 2:09a Scottyang
// [TAG]  		None
// [Category]  	Improvement
// [Description]  	Already program at SBPEI.c
// 
// 20    10/18/12 5:56a Scottyang
// [TAG]  		EIP101204
// [Category]  	Bug Fix
// [Severity]  	Normal
// [Symptom]  	 Azalia PME bit doesn't been set when Enabled "Azalia PME"
// [RootCause]  	 PME bit will be cleared by AMI PCI bus driver.
// [Solution]  	Reprogram PME bit in SbInitAfterDeviceInstall().
// [Files]  		SBDXE.c
// 
// 19    10/16/12 3:56a Scottyang
// [TAG] EIP103924
// 
// [Category] Improvement
// 
// [Description] Update RC 0.7.1
// 
// [Files] ReferenceCode\Chipset\LynxPoint\*.*, SBDxe.c, SB.sd,
// SbSetupData.c, GetSetupDate.c
// 


// 17    10/15/12 8:42a Scottyang
// [TAG]  		ULTDsdtTableUpdate
// [Category]  	Improvement
// [Description]  	Update DSDT when ULT.
// 
// 16    10/14/12 8:33a Scottyang
// [TAG]  		None
// [Category]  	Improvement
// [Description]  	One rom for two chip and one chip. 
// [Files]  		SPPEIBoard.c, SB.sd, SBDxe.c, SBPEI.c, PCH.asl
// 
// 15    10/12/12 7:46a Scottyang
// [TAG]  		None
// [Category]  	Improvement
// [Description]  	Clear all SB warm reset flag
// 
// 14    10/12/12 2:04a Scottyang
// [TAG]  		EIP76432
// [Category]  	Bug Fix
// [Severity]  	Normal
// [Symptom]  	It will BSOD ,while system boot to OS at "starting windows"
// press the KB in succession.
// [RootCause]  	System BSOD is caused by a large number of SMI generated.
// [Solution]  	Disable legacy USB SMI in ACPI enable stage.
// [Files]  		AcpiModeEnable.c; SBDXE.c
// 
// 13    10/12/12 2:02a Scottyang
// [TAG]  		ULT_SUBID
// [Category]  	Bug Fix
// [Severity]  	Important
// [Symptom]  	Win8 BSOD for ULT A0 CPU
// [RootCause]  	The Sub-device ID not match LPT-LP A0 stepping.
// [Solution]  	Use old Sub-device ID
// [Files]  		SBDxe.c
// 
// 12    10/01/12 5:53a Victortu
// [TAG]           None
// [Category]      Improvement
// [Description]   Create new token "SOLUTION_FOR_EIP95440" for EIP#95440
// changed.
// [Files]         SB.sdl, SBDXE.c
// 
// 11    9/26/12 3:53a Victortu
// [TAG]           None
// [Category]      Improvement
// [Description]   If SPI Flash module support VSCC updated, skip
// programming VSCC.
// [Files]         SB.sdl, SBDxe.c
// 
// [TAG]           None
// [Category]      Improvement
// [Description]   Update from EIP#95440 to resolve the RAID driver
// compatibility issue.
// [Files]         SB.mak, SB.sdl, SBDXE.c
// 
// [TAG]           None
// [Category]      Improvement
// [Description]   Update for Intel PCH LPT RC070.
// [Files]         SB.sdl, SBDXE.c, SBPEI.c, Pch.sdl, SB.sd, SB.uni
// 
// [TAG]           None
// [Category]      Improvement
// [Description]   Update EIP#101515.
// [Files]         SBDXE.c
// 
// [TAG]           None
// [Category]      Improvement
// [Description]   Update for PCH LP GPIO compatible.
// [Files]         SB.sdl, SB.H, AcpiModeEnable.c, AcpiModeEnable.sdl,
// SBDxe.c, SBGeneric.c, SBPEI.c, SBSMI.c, SleepSmi.c,
// SmiHandlerPorting.c, SmiHandlerPorting2.c
// 
// [TAG]           None
// [Category]      Improvement
// [Description]   Implement ULT platform LPSS and ADSP setup option.
// [Files]         GetSetupData.c, SB.sd, SB.uni, SbSetupData.h, SBDxe.c,
// SB.sdl
// 
// 10    9/12/12 5:18a Victortu
// [TAG]           None
// [Category]      Improvement
// [Description]   Remove useless HdmiVerbTable.
// [Files]         SB.sdl, SBCspLib.h, SBDxe.c, SBGeneric.c 
// 
// [TAG]           None
// [Category]      Improvement
// [Description]   Support OEM update VSCC table.
// [Files]         SB.H, SB.mak, SB.sdl, SBDXE.c
// 
// 9     8/30/12 9:49a Victortu
// [TAG]           None
// [Category]      Improvement
// [Description]   Fixed building error when disable RC_PORT_0.
// [Files]         SBDxe.c
// 
// 8     8/24/12 6:50a Victortu
// [TAG]           None
// [Category]      Improvement
// [Description]   Update RC_PORT_x for PCIe.
// [Files]         SB.sdl, SB.sd, SBDxe.c
// 
// [TAG]           None
// [Category]      Improvement
// [Description]   Report HPET Function Number to zero for VTD.
// [Files]         SBDxe.c
// 
// [TAG]           None
// [Category]      Improvement
// [Description]   Implement USB Skip MASS Storage function.
// [Files]         SBDxe.c
// 
// 7     8/15/12 12:53a Victortu
// [TAG]           None
// [Category]      Improvement
// [Description]   Remove ME_SERVER_SUPPORT.
// [Files]         SBDxe.c, SBPEI.c
// 
// [TAG]           None
// [Category]      Improvement
// [Description]   Update "SB_TEMP_MMIO_BASE" and
// "EHCI_MMIO_BASE_ADDRESS".
// [Files]         SB.sdl, SBDxe.c, SBPEI.c
// 
// 6     8/13/12 10:27a Victortu
// [TAG]		EIP96150
// [Category]	Bug Fix
// [Severity]	Normal
// [Symptom]	USB Device still can be detected even set USB controllers as
// "Disabled" in BIOS Setup.
// [Solution]	Set XHCI disable bit of FD Reg.
// [Files]		SBDxe.c
// 
// [TAG]           None
// [Category]      Improvement
// [Description]   Implement BIOS Lock function.
// [Files]         SBCspLib.h, SBDxe.c, SBSMI.c, SBSMI.dxs, SBSMI.sdl
// 
// [TAG]           None
// [Category]      Improvement
// [Description]   Create the token "USB30_OVER_CURRENT_MAPPING_SETTINGS"
// for the policy "Usb30OverCurrentPins".
// [Files]         SB.sdl, SBDxe.c
// 
// [TAG]           None
// [Category]      Improvement
// [Description]   Improve CheckDisableUsbControllers function.
// [Files]         SBDxe.c
// 
// [TAG]           None
// [Category]      Improvement
// [Description]   Remove PCH_A0PWRON_SAFEMODE.
// [Files]         SBDxe.c, Pch.sdl
// 
// [TAG]           None
// [Category]      Improvement
// [Description]   Remove useless Dppm items.
// [Files]         GetSetupData.c, SB.sd, SbSetupData.h, SBDxe.c
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
// 5     7/27/12 6:13a Victortu
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
// 4     7/02/12 10:18a Victortu
// [TAG]		None
// [Category]	Improvement
// [Description]	SETUP.MassStorageOpRom will instead of SETUP.SataRaidRom
// to decide the launching policy of RAID UEFI driver/Legacy OpRom if
// CsmOptOut_SUPPORT enabled.
// [Files]		SBDex.c, SB.sd
// 
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
// 2     4/25/12 9:10a Victortu
// [TAG]         None
// [Category]    Improvement
// [Description] Relayout PCH USB Setup.
// [Files]       GetSetupData.c; SB.sd; SB.uni; SbSetupData.h; SBDxe.c
// 
// [TAG]         None
// [Category]    Improvement
// [Description] Fixed GenericSio use 0x0 ~ 0xfff issue.
// [Files]       SBDxe.c
// 
// 1     2/08/12 8:24a Yurenlai
// Intel Lynx Point/SB eChipset initially releases.
// 
//*************************************************************************
//<AMI_FHDR_START>
//
// Name:        SBDxe.C
//
// Description: This file contains code for Template Southbridge
//              initialization in the DXE stage
//
//<AMI_FHDR_END>
//*************************************************************************

//---------------------------------------------------------------------------
// Include(s)
//---------------------------------------------------------------------------

#include <Efi.h>
#include <token.h>
#include <AmiLib.h>
#include <AmiDxeLib.h>
#include <Setup.h>
#include <Dxe.h>
#include <PCI.h>
#include <AmiHobs.h>
#include <AmiCspLib.h>
#include "HDAVBTBL.h"
#include <AcpiRes.h>
#include <Protocol\BusSpecificDriverOverride.h>
#include <Protocol\LoadedImage.h>
#include <protocol\DriverBinding.h>

// Consumed Protocols
#include <Protocol\PciIo.h>
#include <Protocol\Cpu.h>
#include <Protocol\PciRootBridgeIo.h>
#include <Protocol\DevicePath.h>
#if SB_PCIE_ERROR_LOG_SUPPORT
#include <Protocol\GenericElog.h>
#endif

#if ACPI_SUPPORT
 #if defined(PI_SPECIFICATION_VERSION)&&(PI_SPECIFICATION_VERSION>=0x00010014)
 #include <Protocol\AcpiSystemDescriptionTable.h>
 #else
 #include <Protocol\AcpiSupport.h>
 #endif
#endif

#if defined(CsmOptOut_SUPPORT) && (CsmOptOut_SUPPORT == 1)
#include <AmiLoadCsmPolicy.h>
#endif

#if CSM_SUPPORT
#include <Protocol\CsmPlatform.h>
#include <Protocol\LegacyBiosExt.h>
#endif

// Produced Protocols
#include <Protocol\RealTimeClock.h>
#include <Protocol\WatchdogTimer.h>
#include <Protocol\Timer.h>
#include <Protocol\Legacy8259.h>

#if defined HPET_PROTOCOL_SUPPORT && HPET_PROTOCOL_SUPPORT == 1
#include <Protocol\SbHpet.h>
#endif

#if defined(IntelPchInclude_SUPPORT) && IntelPchInclude_SUPPORT
#include <PchAccess.h>
#endif
#include <Protocol\PchPlatformPolicy\PchPlatformPolicy.h>

#if defined   iME_SUPPORT && iME_SUPPORT
#include <Guid\MeBiosExtensionSetup\MeBiosExtensionSetup.h>
#endif

#include <Protocol\SBPlatformData.h>
#include <Board\EM\Platform\PlatformSetup.h>

#if defined INTEL_CRB_DXE_KSC_LIB_SUPPORT && INTEL_CRB_DXE_KSC_LIB_SUPPORT
#if defined CRB_EC_SUPPORT && CRB_EC_SUPPORT
#include <KscLib.h>
#include <Protocol\ECACCESS.h>
#endif
#endif

#if SecureMod_SUPPORT
#include <Flash.h>
#endif
#if defined (SPI_INITIALIZE_WITH_VSCC) && (SPI_INITIALIZE_WITH_VSCC == 1)
#include <Protocol\FlashProtocol.h>
#endif
#if defined AMIUSB_SUPPORT && AMIUSB_SUPPORT == 1
#include <Protocol\AmiUsbController.h>
#endif

#if defined OEM_USB_PER_PORT_DISABLE_SUPPORT && OEM_USB_PER_PORT_DISABLE_SUPPORT == 1
#include <Protocol\UsbIo.h>
#endif

#include <Protocol\GlobalNvsArea\GlobalNvsArea.h>
#include <RTC.h>
#include "protocol\BlockIo.h"
#include "Protocol\PDiskInfo.h"
#include "Protocol\PIDEController.h"
#include "Protocol\PIDEBus.h"
#include "Protocol\PAhciBus.h"
#include <Protocol\SMBios.h>			//(EIP124410)

//---------------------------------------------------------------------------
// Constant, Macro and Type Definition(s)
//---------------------------------------------------------------------------
// Constant Definition(s)

// Build flag adjustments
#ifndef     SMM_SUPPORT
#define     SMM_SUPPORT 0
#endif

// Timer Constants
#define SYSTEM_TIMER_IRQ 0

// Timer Period
#define TIMER_TICK 838 // ns

// default duration is 0xffff ticks
#define DEFAULT_TICK_DURATION ((65535 * 838 + 50) / 100)
#define MAX_TICK_DURATION DEFAULT_TICK_DURATION

//8259 PIC defines
#define ICW1            0x11    // Slave exists and ICW4 required.
#define ICW3_M          1 << 2  // IRQ 2 connects to slave
#define ICW3_S          2       // IRQ 2 connects to master
#define ICW4            1       // Bit 4 Normal Nested Mode
                                // Bit 3 Non-buffered Mode
                                // Bit 2 Unused with non-buffered mode
                                // Bit 1 Set manual EOI instead of automatic
                                // Bit 0 8086/8088 mode

#define OCW1_M          0xff    // Master Mask
#define OCW1_S          0xff    // Slave Mask

#define EOI_COMMAND     0x20    // EOI Command

#define FLASH_DEVICE_BASE_ADDRESS (0xffffffff - FLASH_SIZE + 1)

#define PCI_CLASS_NETWORK             0x02
#define PCI_CLASS_NETWORK_ETHERNET    0x00
#define PCI_CLASS_NETWORK_OTHER       0x80

#define SPI_OPCODE_READ_ID_INDEX      0x4

#if defined HPET_PROTOCOL_SUPPORT && HPET_PROTOCOL_SUPPORT == 1
#define LEGACY_TIMER_0_COUNT    0x40
#define LEGACY_TIMER_1_COUNT    0x41
#define LEGACY_TIMER_CTRL       0x43
#define TIMER_1_COUNT           LEGACY_TIMER_1_COUNT
#endif

// Macro Definition(s)

// Type Definition(s)

// Function Prototype(s)

EFI_STATUS WatchdogInit (
    IN EFI_HANDLE        ImageHandle, 
    IN EFI_SYSTEM_TABLE  *SystemTable
);

EFI_STATUS Initialize8259(
    IN EFI_HANDLE        ImageHandle,
    IN EFI_SYSTEM_TABLE  *SystemTable
);

EFI_STATUS PciPlatformInit (
    IN EFI_HANDLE        ImageHandle,
    IN EFI_SYSTEM_TABLE  *SystemTable
);

EFI_STATUS
SBDXE_BoardInit (
    IN EFI_HANDLE       ImageHandle,
    IN EFI_SYSTEM_TABLE *SystemTable
);

VOID SbInitAfterDeviceInstall (
    IN EFI_EVENT        Event,
    IN VOID             *Context
);

VOID EFIAPI WatchdogHandler (
    IN EFI_EVENT        Event, 
    IN VOID             *Context
);

EFI_STATUS EFIAPI RegisterHandler (
    IN EFI_WATCHDOG_TIMER_ARCH_PROTOCOL  *This,
    IN EFI_WATCHDOG_TIMER_NOTIFY         NotifyFunction
);

EFI_STATUS EFIAPI WatchdogSetTimerPeriod (
    IN EFI_WATCHDOG_TIMER_ARCH_PROTOCOL  *This,
    IN UINT64                            TimerPeriod
);

EFI_STATUS EFIAPI WatchdogGetTimerPeriod (
    IN EFI_WATCHDOG_TIMER_ARCH_PROTOCOL  *This,
    IN UINT64                            *TimerPeriod
);

EFI_STATUS EFIAPI TimerInit (
    IN EFI_EVENT        Event,
    IN VOID             *Context
);

EFI_STATUS TimerRegisterHandler (
    IN EFI_TIMER_ARCH_PROTOCOL  *This, 
    IN EFI_TIMER_NOTIFY         NotifyFunction
);

EFI_STATUS SetTimerPeriod (
    IN EFI_TIMER_ARCH_PROTOCOL  *This, 
    IN UINT64                   TimerPeriod
);

EFI_STATUS GetTimerPeriod (
    IN EFI_TIMER_ARCH_PROTOCOL  *This, 
    IN UINT64                   *TimerPeriod
);

EFI_STATUS GenerateSoftIntr (
    IN EFI_TIMER_ARCH_PROTOCOL  *This
);

VOID SaveRestoreRegisters (
    IN BOOLEAN                  Save
);

VOID CreateSbAcpiComponent ( VOID );

EFI_STATUS ReserveSbResources (
    IN EFI_HANDLE      ImgHandle,
    IN EFI_HANDLE      CntrHandle
);

EFI_STATUS AddLpcStdIoSpace ( VOID );
								//(EIP124410)>>
VOID UpdateSmbios136Table(
    IN EFI_EVENT    Event,
    IN VOID         *Context
);
								//(EIP124410)<<
                                // [EIP134850] >>
#if defined CSM_SUPPORT && CSM_SUPPORT == 1
VOID SBSataRegSaveRestore(
    IN EFI_EVENT    Event, 
    IN VOID         *Context
);
#endif
                                // [EIP134850] <<

VOID InitSbRegsBeforeBoot (
    IN EFI_EVENT    Event,
    IN VOID *Context
);

VOID InitSbRegsBeforeLagecyBoot (
    IN EFI_EVENT    Event,
    IN VOID *Context
);

#if defined OEM_USB_PER_PORT_DISABLE_SUPPORT && OEM_USB_PER_PORT_DISABLE_SUPPORT == 1
VOID USBPrePortDisableCallback (
    IN EFI_EVENT    Event,
    IN VOID *Context
);
#endif

VOID EHCIWorkAround (
    IN UINT8            EhciDev
);

VOID ConfigPciDevices (
    IN EFI_SYSTEM_TABLE     *SystemTable
);

VOID ReportSBDxeError (
    IN EFI_STATUS       Status
);

#ifdef CSM_OPRROM_POLICY_GUID
VOID SbCheckOprom (
    IN EFI_EVENT        Event,
    IN VOID             *Context
);
#endif

VOID SbSetupNvramUpdatedCallback (
    IN EFI_EVENT        Event,
    IN VOID             *Context
);

VOID SbExitPmAuthProtocolCallback (
    IN EFI_EVENT        Event,
    IN VOID             *Context
);

EFI_STATUS
InstallDxePchPlatformPolicy (VOID);

VOID SBSpiProgramVSCC(VOID);
VOID SBS3SaveSpi(VOID);                         // [ EIP357393 ]

VOID SBClearRTC_AlarmFlag(VOID);

VOID LocatePublishIdeSataAcpiTables(VOID);

EFI_STATUS SbSmmInit(
    IN EFI_EVENT        Event,
    IN VOID             *Context
);

//---------------------------------------------------------------------------
// Variable and External Declaration(s)
//---------------------------------------------------------------------------
// Variable Declaration(s)
typedef struct {
    UINT16 Address;
    UINT16 Length;
} LPC_IO_STD_DECODE;

typedef struct {
    UINT8 Bus;
    UINT8 Dev;
    UINT8 Fun;
    VOID *Process;
} DEVICES_AFTER_PCIIO;

typedef struct {
  UINT32  Signature;
  UINT32  Length;
} EFI_ACPI_COMMON_HEADER;

DEVICES_AFTER_PCIIO gDevicesTable[] = {
    { PCIEBRS_BUS,  PCIEBRS_DEV,  PCIEBRS_FUN,  NULL },
    { PCIEBRS2_BUS, PCIEBRS2_DEV, PCIEBRS2_FUN, NULL },
    { PCIEBRS3_BUS, PCIEBRS3_DEV, PCIEBRS3_FUN, NULL },
    { PCIEBRS4_BUS, PCIEBRS4_DEV, PCIEBRS4_FUN, NULL },
    { PCIEBRS5_BUS, PCIEBRS5_DEV, PCIEBRS5_FUN, NULL },
    { PCIEBRS6_BUS, PCIEBRS6_DEV, PCIEBRS6_FUN, NULL },
    { PCIEBRS7_BUS, PCIEBRS7_DEV, PCIEBRS7_FUN, NULL },
    { PCIEBRS8_BUS, PCIEBRS8_DEV, PCIEBRS8_FUN, NULL },
    { HDA_BUS,      HDA_DEV,      HDA_FUN,      NULL },		//(EIP101204)
    { SMBUS_BUS,    SMBUS_DEV,    SMBUS_FUN,    NULL },
    { SATA_BUS,     SATA_DEV,     SATA_FUN,     NULL },
    { 0xFF,         0xFF,         0xFF,         NULL }
};
UINTN gEventCount = sizeof(gDevicesTable) / sizeof(DEVICES_AFTER_PCIIO);

typedef struct {
    UINT32                      VidDid;
    UINT32                      Vscc;
} SPI_VSCC_TABLE;
								//(EIP124410)>>
#pragma pack (1)
typedef struct {
  SMBIOS_STRUCTURE_HEADER        Header;
  UINT16                         OemInfo;
  UINT16                         Zero;   //terminator
} EFI_MISC_OEM_TYPE_0x88;
#pragma pack ()
								//(EIP124410)<<
EFI_HANDLE  mTimerProtocolHandle    = NULL;
EFI_HANDLE  mWatchdogHandle         = NULL;
EFI_EVENT   mWatchdogEvent;

// Save daylight when set. 
UINT8       gDaylight               = 0;
UINT8       gMasterBase;
UINT8       gSlaveBase;

// Initially in protected mode. (0 = Real, 1 = 32 bit protected) 
UINT8       gMode                   = 1;

// Initially all Real IRQs masked, protected masked 
UINT16      gIrqMask[2]             = {0xffff, 0xffff}; 

// Initially all Real IRQs Edge, protected Edge. 
UINT16      gIrqTrigger[2]          = {0, 0};
UINT64      mWatchdogPeriod         = 0;
UINT64      mProgrammedTimerValue;

BOOLEAN gErrorLoggingFlag = FALSE;

EFI_TIMER_NOTIFY                mNotifyFunction;
EFI_LEGACY_8259_PROTOCOL        *mLegacy8259 = NULL;
EFI_WATCHDOG_TIMER_NOTIFY       mWatchdogNotifyFunction = NULL;
EFI_PCI_ROOT_BRIDGE_IO_PROTOCOL *gPciRootBridgeIo = NULL;
AMI_S3_SAVE_PROTOCOL            *gBootScript = NULL;
VOID                            *gSbInitNotifyReg = NULL;
VOID                            *gCsmOpromReg = NULL;
VOID                            *gSbSetupNvramUpdatedReg = NULL;
VOID                            *gSbExitPmAuthProtocolReg = NULL;
VOID                            *gSbSataIdeProtocolReg = NULL; 
EFI_STATUS LocateSBSATAIDESupportProtocol (IN EFI_GUID *Protocol,OUT VOID **Instance,IN BOOLEAN Type );

 
SB_SETUP_DATA                   *gSbSetupData = NULL;
SB_PLATFORM_DATA                SbPlatformData;
#if defined(CsmOptOut_SUPPORT) && (CsmOptOut_SUPPORT == 1)
VOID *gInterface = NULL;
#endif
#if defined CSM_SUPPORT && CSM_SUPPORT == 1                               // [EIP134850] >>
VOID *SataOpRomRegistration;
static EFI_GUID OpRomStartEndProtocolGuid = OPROM_START_END_PROTOCOL_GUID;
UINT8                           SaveSataReg = 0;
UINT8                           IsSataOpROM = 0;
UINT8                           DLAE = 0;
#endif                                                                    // [EIP134850] <<
BOOLEAN                         gDisableAllUsbControllers = FALSE;
#if defined AMIUSB_SUPPORT && AMIUSB_SUPPORT == 1
EFI_EVENT                       gEvtUsbProtocol  = NULL;
VOID                            *gRegUsbProtocol = NULL;
EFI_USB_PROTOCOL                *gUsbProtocol = NULL;
#endif
								//(EIP124410)>>
EFI_SMBIOS_PROTOCOL             *gSmbiosProtocol = NULL;
EFI_GUID                        gEfiSmbiosProtocolGuid = EFI_SMBIOS_PROTOCOL_GUID;
								//(EIP124410)<<
#if SB_PCIE_ERROR_LOG_SUPPORT
EFI_GUID gElogProtocolGuid	= EFI_SM_ELOG_PROTOCOL_GUID;
#endif
#define IDE_SATA_ACPI_TABLE_STORAGE_GUID \
  { 0x22046D50,0xF390,0x498c,0x92,0xE5,0x5B,0xA4,0xF8,0xE7,0xF8,0xB6}
EFI_GUID IdeSataAcpiTableStorageGuid = IDE_SATA_ACPI_TABLE_STORAGE_GUID;
#if defined(CsmOptOut_SUPPORT) && (CsmOptOut_SUPPORT == 1)
EFI_GUID  gAmiLoadCsmGuid = AMI_LOAD_CSM_GUID;
#endif
#if SecureMod_SUPPORT
EFI_GUID  gBiosLockEnableEventGuid = AMI_EVENT_FLASH_WRITE_LOCK;
#endif

#if defined(HPET_APIC_INTERRUPT_MODE) && (HPET_APIC_INTERRUPT_MODE != 0)
extern UINT8 gBspLocalApicID;
#endif

CSP_RES_ITEM gSbResTable[] = {
//----------------------------------------------------------------------------
// ResBase      ResLength       ResType                         Attributes  
//----------------------------------------------------------------------------
// Always reserve 16MB for ROM image.
{ RESERVED_ROM_BASE,   RESERVED_ROM_LENGTH,         EfiGcdMemoryTypeMemoryMappedIo ,\
                                          (EFI_MEMORY_UC | EFI_MEMORY_RUNTIME)},
// IOAPICs dedicated Space
{ APCB,         APCL,              EfiGcdMemoryTypeMemoryMappedIo , \
                                          (EFI_MEMORY_UC|EFI_MEMORY_RUNTIME)},
#if FEC00000_APIC_AUTODETECT
{ APCB + APCL,  0x00100000 - APCL, EfiGcdMemoryTypeMemoryMappedIo , \
                                           EFI_MEMORY_UC},
#endif

#if HPET_SUPPORT
// HPET dedicated Space
{ HPET_BASE_ADDRESS, 0x00004000,   EfiGcdMemoryTypeMemoryMappedIo , \
                                          (EFI_MEMORY_UC|EFI_MEMORY_RUNTIME)},
#endif
// Reserve for RCRB Base, the attributes of this region should be defined to
// RUNTIME because it includes the SPI_BASE_ADDRESS.
{ SB_RCRB_BASE_ADDRESS, SB_RCRB_LENGTH,    EfiGcdMemoryTypeMemoryMappedIo , \
                                          (EFI_MEMORY_UC|EFI_MEMORY_RUNTIME)},
// SB Temp Memory Mapped Space
{ SB_TEMP_MMIO_BASE, SB_TEMP_MMIO_BASE_LENGTH, EfiGcdMemoryTypeMemoryMappedIo, (EFI_MEMORY_UC) },
// HECI Memory Mapped Space
{ HECI_BASE_ADDRESS, 0x10000,  EfiGcdMemoryTypeMemoryMappedIo, (EFI_MEMORY_UC) },
// HECI2 Memory Mapped Space
{ HECI2_BASE_ADDRESS, 0x10000, EfiGcdMemoryTypeMemoryMappedIo, (EFI_MEMORY_UC) },
// IO Used by PM register block
{ PM_BASE_ADDRESS,    PMLN         ,EfiGcdIoTypeIo      ,       -1  },
// IO Used by SMBus register block
{ SMBUS_BASE_ADDRESS, SMBL         ,EfiGcdIoTypeIo      ,       -1  },
// IO Used by GPIO register block
{ GPIO_BASE_ADDRESS,  GPLN         ,EfiGcdIoTypeIo      ,       -1  },
};

UINTN   gSbResTableCount = sizeof(gSbResTable) / sizeof(CSP_RES_ITEM);

#define ONBOARD_RAID_GUID \
    { 0x5d206dd3, 0x516a, 0x47dc, 0xa1, 0xbc, 0x6d, 0xa2, 0x4, 0xaa, 0xbe, 0x8 };

#define EXIT_PM_AUTH_PROTOCOL_GUID \
    { 0xd088a413, 0xa70, 0x4217, 0xba, 0x55, 0x9a, 0x3c, 0xb6, 0x5c, 0x41, 0xb3 };

#if SataDriver_SUPPORT
#define PCH_EFI_RAID_DRIVER_EXECUTION_GUID \
    { 0x99D5757C, 0xD906, 0x11E0, 0x8D, 0x78, 0x8D, 0xE4, 0x48, 0x24, 0x01, 0x9B };
#endif

// GUID Definition(s)
EFI_GUID gOnboardRaidGuid                  = ONBOARD_RAID_GUID;
EFI_GUID gEfiTimerArchProtocolGuid         = EFI_TIMER_ARCH_PROTOCOL_GUID;
EFI_GUID gEfiLegacy8259ProtocolGuid        = EFI_LEGACY_8259_PROTOCOL_GUID;
EFI_GUID gEfiPciIoProtocolGuid             = EFI_PCI_IO_PROTOCOL_GUID;
EFI_GUID gDevicePathProtocolGuid           = EFI_DEVICE_PATH_PROTOCOL_GUID;
EFI_GUID gEfiPciPlatformProtocolGuid       = EFI_PCI_PLATFORM_PROTOCOL_GUID;
EFI_GUID gDxeSvcTblGuid                    = DXE_SERVICES_TABLE_GUID;
EFI_GUID gSetupNvramUpdatedGuid            = AMITSE_NVRAM_UPDATE_GUID;
EFI_GUID gDxePchPlatformPolicyProtocolGuid = DXE_PCH_PLATFORM_POLICY_PROTOCOL_GUID;
EFI_GUID gWatchdogGuid                     = EFI_WATCHDOG_TIMER_ARCH_PROTOCOL_GUID;
EFI_GUID gEfiPciRootBridgeIoProtocolGuid   = EFI_PCI_ROOT_BRIDGE_IO_PROTOCOL_GUID;
EFI_GUID gExitPmAuthProtocolGuid           = EXIT_PM_AUTH_PROTOCOL_GUID;
#if defined AMIUSB_SUPPORT && AMIUSB_SUPPORT == 1
EFI_GUID gEfiUsbProtocolGuid               = EFI_USB_PROTOCOL_GUID;
#endif

EFI_GUID BeforeBootProtocolGuid            = AMITSE_EVENT_BEFORE_BOOT_GUID;
#if CSM_SUPPORT
EFI_GUID BeforeLegacyBootProtocolGuid      = EFI_AMI_LEGACYBOOT_PROTOCOL_GUID;
#endif

#ifdef CSM_OPRROM_POLICY_GUID
EFI_GUID gCsmOpromPolicyGuid = CSM_OPRROM_POLICY_GUID;
#endif

extern EFI_GUID gEfiSmmControlProtocolGuid;

EFI_GUID   GuidListCheckForRaid[] = { BUS_OVERRIDE_GUIDS_FOR_RAID NULL };
EFI_HANDLE ImageHandleArray[5] = {NULL};
BOOLEAN    LoadedImageDone = FALSE;

EFI_STATUS RaidGetDriver(
	IN EFI_BUS_SPECIFIC_DRIVER_OVERRIDE_PROTOCOL *This,
	IN OUT EFI_HANDLE *DriverImageHandle
);

static EFI_BUS_SPECIFIC_DRIVER_OVERRIDE_PROTOCOL RaidBusSpecificDriverOverride = {
    RaidGetDriver
};

static AHCI_PLATFORM_POLICY_PROTOCOL AhciPlatformPolicy= {
#ifndef DiPM_SUPPORT
    FALSE,                              // Legacy Raid option selected 
    TRUE                                // Ahcibus driver handles the ATAPI devices
#else
    FALSE,                              // Legacy Raid option selected 
    TRUE,                               // Ahcibus driver handles the ATAPI devices
#if !defined SB_SATA_DLAE || SB_SATA_DLAE == 0
    FALSE,                              // Drive LED on ATAPI Enable (DLAE)
#else
    TRUE,
#endif
#ifdef POWERUP_IN_STANDBY_SUPPORT
    POWERUP_IN_STANDBY_SUPPORT,         // PowerUpInStandby feature is supported or not
#else
    FALSE,
#endif
#ifdef POWERUP_IN_STANDBY_MODE
    POWERUP_IN_STANDBY_MODE,            // PowerUpInStandby mode
#else
    FALSE,
#endif
    DiPM_SUPPORT                        // Device Initiated power management
#endif
};

// Protocol Definition(s)

// Architectural Protocol Definitions
EFI_WATCHDOG_TIMER_ARCH_PROTOCOL mWatchdog = {
    RegisterHandler,
    WatchdogSetTimerPeriod,
    WatchdogGetTimerPeriod
};

EFI_TIMER_ARCH_PROTOCOL mTimerProtocol = {
    TimerRegisterHandler,
    SetTimerPeriod,
    GetTimerPeriod,
    GenerateSoftIntr
};

#if defined AMIUSB_SUPPORT && AMIUSB_SUPPORT == 1
VOID SbUsbProtocolCallback (
    IN EFI_EVENT        Event,
    IN VOID             *Context
);
#endif

#if SecureMod_SUPPORT
VOID BiosLockEnableCallback (
    IN EFI_EVENT        Event,
    IN VOID             *Context
);
#endif

VOID ULTDsdtTableUpdate (
  IN ACPI_HDR   *DsdtTable
);

VOID DsdtTableUpdate (
  IN ACPI_HDR   *DsdtTable
);
// External Declaration(s)

extern EFI_STATUS CountTime (
    IN UINTN            DelayTime, 
    IN UINT16           BaseAddr
);

VOID ClearWarmResetFlag (VOID);

//---------------------------------------------------------------------------

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure: RetrainLink
//
// Description: Retrain PCIE Device Link
//
// Input: IN UINT32 Address
//
// Output:
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID RetrainLink(IN UINT32 Address) 
{
   SET_MEM8(Address + R_PCH_PCIE_LCTL, BIT05); // 0x50
   CountTime(10, PM_BASE_ADDRESS);
   while (READ_MEM16(Address + R_PCH_PCIE_LSTS) & BIT11); // 0x52
}

#if SataDriver_SUPPORT
//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:   InstallPchSataUefiDriver
//
// Description: Install SATA UEFI RAID driver GUID for PCH SataDriver. 
//
// Input:       None
//
// Output:      None
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID InstallPchSataUefiDriver ( VOID )
{
#if defined(CsmOptOut_SUPPORT) && (CsmOptOut_SUPPORT == 1)
  SETUP_DATA  SetupData;
  EFI_GUID    SetupGuid = SETUP_GUID;
  UINTN       Size = sizeof(SETUP_DATA);
#endif // CsmOptOut_SUPPORT
  BOOLEAN     InstallRaidDriver = TRUE;
  EFI_HANDLE  Handle = NULL;
  EFI_STATUS  Status;
  EFI_HANDLE  RaidDriverHandle=NULL;
  EFI_GUID    PchEfiRaidDriverExecutionGuid = \
                                 PCH_EFI_RAID_DRIVER_EXECUTION_GUID;

  if (gSbSetupData->SataInterfaceMode == SATA_MODE_RAID) {

#if defined(CsmOptOut_SUPPORT) && (CsmOptOut_SUPPORT == 1)
    Status = pBS->LocateProtocol( &gAmiLoadCsmGuid, \
                                  NULL, \
                                  &gInterface );
    if(!EFI_ERROR(Status)) {

      Status = pRS->GetVariable ( L"Setup", \
                                  &SetupGuid, \
                                  NULL,\
                                  &Size, \
                                  &SetupData );
      if (!EFI_ERROR(Status)) {
        if ((SetupData.MassStorageOpRom == 0) || \
            (SetupData.MassStorageOpRom == 2))
          InstallRaidDriver = FALSE;
      }
    }
#else
    if (gSbSetupData->SataRaidRom == 0) InstallRaidDriver = FALSE;
#endif // CsmOptOut_SUPPORT

    //
    // By default Legacy Raid option settings initilized
    //
    AhciPlatformPolicy.RaidDriverMode= FALSE;
    AhciPlatformPolicy.AhciBusAtapiSupport= TRUE;

    if (InstallRaidDriver) {
      Status = pBS->InstallProtocolInterface( \
                                   &Handle, \
                                   &PchEfiRaidDriverExecutionGuid, \
                                   EFI_NATIVE_INTERFACE, \
                                   NULL);
      ASSERT_EFI_ERROR(Status);

      //
      // UEFI Raid driver enabled
      //
      AhciPlatformPolicy.RaidDriverMode= TRUE;
      //
      // Uefi Raid driver supports the ATAPI device. So Ahcibus doesn't need to handle the ATAPI devices
      //
      AhciPlatformPolicy.AhciBusAtapiSupport= FALSE;
    }

    Status = pBS->InstallProtocolInterface( &RaidDriverHandle,
                                   &gAciPlatformPolicyProtocolGuid,
                                   EFI_NATIVE_INTERFACE,
                                   &AhciPlatformPolicy);
  }
}
#endif

#if FORCE_USER_TO_SETUP_IF_CMOS_BAD                                  // [EIP88358] >>
//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:   ForceSetupIfCmosBad
//
// Description: BIOS force to enter setup if CMOS was bad.
//
// Input:       None
//
// Output:      None
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID ForceSetupIfCmosBad (VOID)
{
    EFI_STATUS              Status = EFI_SUCCESS;
    CMOS_BAD_HOB            *CmosBadHob;
    UINT32                  BootFlow = BOOT_FLOW_CONDITION_FIRST_BOOT;
    EFI_GUID                guidBootFlow = BOOT_FLOW_VARIABLE_GUID;
    EFI_GUID                ghoblistguid = HOB_LIST_GUID;   
    EFI_GUID                CmosBadHobGuid = CMOS_BAD_HOB_GUID;
 
    CmosBadHob = GetEfiConfigurationTable(    //get hob list
                    pST,
                    &ghoblistguid);  
 
    if(CmosBadHob == NULL) return;

    Status = FindNextHobByGuid(    //the hob exit when cmos is bad and creat hob success. 
                &CmosBadHobGuid,            
                &CmosBadHob);
                     
    if(!EFI_ERROR(Status)) {
        TRACE((-1, "SB: Force to Setup.\n"));
        pRS->SetVariable(
                L"BootFlow",
                &guidBootFlow,
                EFI_VARIABLE_BOOTSERVICE_ACCESS,
                sizeof(BootFlow),
                &BootFlow);
    }
}
#endif                                                               // [EIP88358] <<

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:   SBDXE_Init
//
// Description: This function is the entry point for this DXE. This function
//              initializes the chipset SB
//
// Input:       ImageHandle - Image handle
//              SystemTable - Pointer to the system table
//
// Output:      Return Status based on errors that occurred while waiting for
//              time to expire.
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS SBDXE_Init (
    IN EFI_HANDLE       ImageHandle,
    IN EFI_SYSTEM_TABLE *SystemTable )
{

    EFI_STATUS              Status = EFI_SUCCESS;
    EFI_EVENT               Event;
    CPUINFO_HOB             *CpuInfoHob;
    EFI_GUID                HobListGuid = HOB_LIST_GUID;
    EFI_GUID                AmiCpuinfoHobGuid = AMI_CPUINFO_HOB_GUID;
    EFI_GUID                SetupGuid = SETUP_GUID;
    UINTN                   VariableSize = sizeof(SB_SETUP_DATA);
    EFI_EVENT               BeforeBootEvent;
    EFI_EVENT               LegacyBootEvent;
    EFI_EVENT               CRIDSmbiosEvent;		//(EIP124410)
#if defined CSM_SUPPORT && CSM_SUPPORT == 1
    EFI_EVENT               SbSataOptEvent;         // [EIP134850]
#endif
    VOID *Protocol = NULL;
    VOID *NotifyReg = NULL;
#if SecureMod_SUPPORT
    EFI_EVENT               BleEvtProtocol  = NULL;
    VOID                    *BleProtocolReg = NULL;
#endif
    VOID                    *Registration = NULL;

    InitAmiLib(ImageHandle, SystemTable);

    PROGRESS_CODE (DXE_SB_INIT);

    ClearWarmResetFlag();

    Status = pBS->LocateProtocol( &gEfiPciRootBridgeIoProtocolGuid, \
                                  NULL, \
                                  &gPciRootBridgeIo );
    ReportSBDxeError(Status);

    Status = pBS->LocateProtocol( AMI_S3_SAVE_PROTOCOL_GUID, \
                                  NULL, \
                                  &gBootScript );
    ReportSBDxeError(Status);

    //Find APIC ID Hob.
    CpuInfoHob = (CPUINFO_HOB*)GetEfiConfigurationTable( SystemTable, \
                                                         &HobListGuid );
    if (CpuInfoHob == NULL) Status = EFI_UNSUPPORTED;
    else Status = FindNextHobByGuid( &AmiCpuinfoHobGuid, (VOID**)&CpuInfoHob);
    ASSERT_EFI_ERROR(Status);

#if defined(HPET_APIC_INTERRUPT_MODE) && (HPET_APIC_INTERRUPT_MODE != 0)
    gBspLocalApicID = CpuInfoHob->Cpuinfo[0].ApicId;
#endif

    // Put the I/O APIC in Virtual wire mode
    // CHIPSET PROGRAMMING TO ENABLE IOAPIC GOES HERE

    WRITE_MEM8_S3(gBootScript, APCB, 0); // IO APIC index (0)
    WRITE_MEM32_S3(gBootScript, APCB + 0x10, (NCPU << 24));  // APIC ID    // [EIP132701]
    WRITE_MEM8_S3(gBootScript, APCB, 0x10);         // Index 0x10
    // INT0 - EXT INT unmasked 
    WRITE_MEM32_S3(gBootScript, APCB + 0x10, 0x700);                       // [EIP132701]

    // Install 8259 services
    Initialize8259(ImageHandle, SystemTable);

    // Install watchdog timer services
    WatchdogInit(ImageHandle, SystemTable);

#if SmartTimer_SUPPORT == 0
    // Install Legacy timer services
    TimerInit(ImageHandle, SystemTable);
#endif
    

    Status = pBS->AllocatePool( EfiBootServicesData, \
                                VariableSize, \
                                &gSbSetupData );
    ASSERT_EFI_ERROR(Status);

    GetSbSetupData( pRS, gSbSetupData, FALSE );

    //
    // Enable or Disable the Devices depending upon the Setup.
    //

    PROGRESS_CODE (DXE_SB_DEVICES_INIT);

    ConfigPciDevices(SystemTable);

    CreateSbAcpiComponent();

    // Clear RTC Reg C Alarm Flag
    SBClearRTC_AlarmFlag();

    Status = SBDXE_BoardInit(ImageHandle, SystemTable);

    Status = RegisterProtocolCallback( &gEfiPciIoProtocolGuid, \
                                       SbInitAfterDeviceInstall, \
                                       NULL, \
                                       &Event, \
                                       &gSbInitNotifyReg );
    ReportSBDxeError( Status );

#ifdef CSM_OPRROM_POLICY_GUID
    Status = RegisterProtocolCallback( &gCsmOpromPolicyGuid, \
                                       SbCheckOprom, \
                                       NULL, \
                                       &Event, \
                                       &gCsmOpromReg );

    ReportSBDxeError( Status );
#endif

    Status = RegisterProtocolCallback( &gSetupNvramUpdatedGuid, \
                                       SbSetupNvramUpdatedCallback, \
                                       NULL, \
                                       &Event, \
                                       &gSbSetupNvramUpdatedReg );
    ReportSBDxeError( Status );


    Status = ReserveSbResources(ImageHandle, SystemTable);

    ReportSBDxeError(Status);

    Status = RegisterProtocolCallback( &gExitPmAuthProtocolGuid, \
                                       SbExitPmAuthProtocolCallback, \
                                       NULL, \
                                       &Event, \
                                       &gSbExitPmAuthProtocolReg );
    ReportSBDxeError( Status );

#if defined AMIUSB_SUPPORT && AMIUSB_SUPPORT == 1
    Status = RegisterProtocolCallback( &gEfiUsbProtocolGuid,\
                                       SbUsbProtocolCallback,\
                                       NULL,\
                                       &gEvtUsbProtocol,\
                                       &gRegUsbProtocol );
#endif

#if SecureMod_SUPPORT
    Status = RegisterProtocolCallback( &gBiosLockEnableEventGuid,\
                                       BiosLockEnableCallback,\
                                       NULL,\
                                       &BleEvtProtocol,\
                                       &BleProtocolReg );
#endif

    Status = CreateReadyToBootEvent( TPL_NOTIFY, InitSbRegsBeforeBoot, \
                                     NULL, &BeforeBootEvent );
    ReportSBDxeError(Status);
										//(EIP124410)>>
    Status = CreateReadyToBootEvent( TPL_NOTIFY, UpdateSmbios136Table, \
                                     NULL, &CRIDSmbiosEvent );
    ReportSBDxeError(Status);
										//(EIP124410)<<
    Status = CreateLegacyBootEvent( TPL_CALLBACK, \
                                    InitSbRegsBeforeLagecyBoot, \
                                    NULL, \
                                    &LegacyBootEvent );
    ReportSBDxeError(Status);

#if defined OEM_USB_PER_PORT_DISABLE_SUPPORT && OEM_USB_PER_PORT_DISABLE_SUPPORT == 1 
    RegisterProtocolCallback(
        &BeforeBootProtocolGuid,
        USBPrePortDisableCallback,
        NULL, &Event, &Registration
    );
	
#if CSM_SUPPORT
    RegisterProtocolCallback(
        &BeforeLegacyBootProtocolGuid,
        USBPrePortDisableCallback,
        NULL, &Event, &Registration
    );

    CreateLegacyBootEvent(TPL_CALLBACK, &USBPrePortDisableCallback, NULL, &LegacyBootEvent);
#endif

	  pBS->CreateEvent(
        EVT_SIGNAL_EXIT_BOOT_SERVICES,TPL_CALLBACK, 
        &USBPrePortDisableCallback, NULL, &Event
    );
#endif

    Status = InstallDxePchPlatformPolicy();
    ReportSBDxeError(Status);

    //Program SPI base VSCC 
    SBSpiProgramVSCC();
    //Restore SPI register for S3 resume        // [ EIP357393 ]
    SBS3SaveSpi();                              // [ EIp357393 ]

//-    Status = AddLpcStdIoSpace();

#if SataDriver_SUPPORT
    InstallPchSataUefiDriver();
#endif
#if defined CSM_SUPPORT && CSM_SUPPORT == 1                                                                          // [EIP134850] >>
    if(gSbSetupData->SataInterfaceMode == SATA_MODE_RAID){
        Status = RegisterProtocolCallback(&OpRomStartEndProtocolGuid, 
                                          SBSataRegSaveRestore, 
                                          NULL, 
                                          &SbSataOptEvent, 
                                          &SataOpRomRegistration);
        TRACE((TRACE_ALWAYS, "Register OpRomStartEndProtocol callback() = %r\n", Status));
    }
#endif                                                                                // [EIP134850] <<

#if FORCE_USER_TO_SETUP_IF_CMOS_BAD                                  // [EIP88358] >>
    ForceSetupIfCmosBad();
#endif                                                               // [EIP88358] <<

#if defined SMM_SUPPORT && SMM_SUPPORT == 1
    Status = pBS->LocateProtocol(&gEfiSmmControlProtocolGuid, NULL, &Protocol);
    if (EFI_ERROR(Status))
    {
        Status = RegisterProtocolCallback(
                        &gEfiSmmControlProtocolGuid,
                        SbSmmInit,
                        NULL,
                        &Event,
                        &NotifyReg);
        ASSERT_EFI_ERROR(Status);
    }
    else
    {
        Status = SbSmmInit(NULL, NULL);
        if (Status != EFI_SUCCESS)
        {
            TRACE((TRACE_ALWAYS, "SbSmmInit() = %r\n", Status));
            ASSERT_EFI_ERROR(Status);
        }
    }
#endif

    return EFI_SUCCESS;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure: SBClearRTC_AlarmFlag
//
// Description: Clear RTC Reg C Alarm Flag
//
// Input: None
//
// Output: None
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

VOID SBClearRTC_AlarmFlag(VOID)
{

    // Clear all SMI status here.
    // Must read RTC Reg C to be able to clear SMM RTC alarm flag.
    SBLib_CmosRead(0x0C);

    WRITE_IO16_PM(ACPI_IOREG_PM1_STS,       0xcd31);     // 0x00
    if (GetPchSeries() == PchLp) {
      WRITE_IO32_PM(ACPI_PCHLP_IOREG_GPE0_STS + 0x0c, 0xffffffff);  // 0x8C
      WRITE_IO32(GPIO_BASE_ADDRESS + GP_IOREG_ALTGP_SMI_STS, 0xffffffff);   // 0x50
    } else {
      WRITE_IO32_PM(ACPI_IOREG_GPE0_STS,      0xffffffff); // 0x20
      WRITE_IO32_PM(ACPI_IOREG_GPE0_STS + 4,  0xffffffff); // 0x24
      WRITE_IO16_PM(ACPI_IOREG_ALTGP_SMI_STS, 0xffff);     // 0x3A
    }
    WRITE_IO16_PM(ACPI_IOREG_DEVACT_STS,    0xffff);     // 0x44
    WRITE_IO16_TCO(TCO_IOREG_STS1,          0xffff);     // 0x04
    WRITE_IO16_TCO(TCO_IOREG_STS2,          0xfffe);     // 0x06, Skip Intrusion [EIP73607]
    WRITE_IO32_PM(ACPI_IOREG_SMI_STS,       0xffffffff); // 0x34
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure: SBSpiProgramVSCC
//
// Description: Program SPI VSCC.
//
// Input: None
//
// Output: None
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

VOID SBSpiProgramVSCC(VOID)
{
    EFI_STATUS Status;
    UINT32 Data32 = 0;
    UINT32 dUVSCC = 0;
    UINT32 Mask = 0xFFFFFFFF;
    UINT8  Data8 = 0;
#if defined (SPI_INITIALIZE_WITH_VSCC) && (SPI_INITIALIZE_WITH_VSCC == 1)
    static FLASH_PROTOCOL *Flash = NULL;
#endif
#if defined (OEM_UPDATE_VSCC_TABLE_SUPPORT) && (OEM_UPDATE_VSCC_TABLE_SUPPORT == 1)
    SPI_VSCC_TABLE                  SpiVsccTbl[] = { OEM_SPI_VSCC_TABLE };
    UINTN  VsccTableCount = sizeof (SpiVsccTbl) / sizeof (SPI_VSCC_TABLE);
    UINT16 SpiCmd =0;
    UINT32 Timeout;
    UINTN  i;
#endif

  TRACE((TRACE_ALWAYS, "[[ SBSpiProgramVSCC() Start. ]]\n"));

  // If Flash module support VSCC updated, skip programming VSCC.
  // If enable OEM_UPDATE_VSCC_TABLE_SUPPORT, override VSCC value by ELINK.
  if (((0 == READ_MEM32_SPI(R_RCRB_SPI_UVSCC)) &&
       (0 == READ_MEM32_SPI(R_RCRB_SPI_LVSCC))) || 
       (OEM_UPDATE_VSCC_TABLE_SUPPORT == 1)) {
#if defined (SPI_INITIALIZE_WITH_VSCC) && (SPI_INITIALIZE_WITH_VSCC == 1)
    Status = pBS->LocateProtocol(&gFlashProtocolGuid, NULL, &Flash);
    if (!EFI_ERROR(Status)) {
        // Identify Flash through FlashWriteEnable Hook.
        Flash->DeviceWriteEnable();
        Flash->DeviceWriteDisable();
    }
    if (((0 == READ_MEM32_SPI(R_RCRB_SPI_UVSCC)) &&
         (0 == READ_MEM32_SPI(R_RCRB_SPI_LVSCC))) || 
         (OEM_UPDATE_VSCC_TABLE_SUPPORT == 1))
#endif
    {
    dUVSCC = ((UINT32)(READ_MEM8_SPI(R_RCRB_SPI_OPMENU + 2)) << 8);

    Data8 = READ_MEM8_SPI(R_RCRB_SPI_PREOP + 1);
    if ((Data8 == 0x50) || (Data8 == 0x39))
        dUVSCC |= BIT03;

    if (Data8 == 0x39 ) {
        dUVSCC |= (BIT04 + BIT02);
    } else if(Data8 != 0x50) {
        dUVSCC |= BIT02;
    }

    if (READ_MEM8_SPI(R_RCRB_SPI_OPMENU + 2) == 0xD8)
        dUVSCC |= (BIT00 + BIT01);
    else
        dUVSCC |= (BIT00);

#if defined (OEM_UPDATE_VSCC_TABLE_SUPPORT) && (OEM_UPDATE_VSCC_TABLE_SUPPORT == 1)
    // Set SPI read-address = 0
    WRITE_MEM32_SPI(R_RCRB_SPI_FADDR, 0);
    SpiCmd = SPI_OPCODE_READ_ID_INDEX << 4;
    SpiCmd += ( ( 3 - 1 ) << 8 );
    SpiCmd += ( 1 << 14 );
    // Go (BIT1)
    WRITE_MEM16_SPI(R_RCRB_SPI_SSFCTL, SpiCmd | BIT01);

    // WaitForSpiCycleDone
    for ( Timeout = 0, i = 0; Timeout < 0x4000000; Timeout++ ) {
        i = READ_MEM8_SPI(R_RCRB_SPI_SSFSTS);
        if ( i & BIT02 ) break;
    }
    // IoDelay
    for ( Timeout = 0; Timeout < 33; Timeout++ ) {
        IoWrite8( 0xEB, 0x55 );
        IoWrite8( 0xEB, 0xAA );
    }
    // write BIT2 to clear CycleDone status
    WRITE_MEM8_SPI(R_RCRB_SPI_SSFSTS, BIT02);
    // Get Flash ID
    Data32 = READ_MEM32_SPI(R_RCRB_SPI_FDATA0) & 0x00FFFFFF;
    // Swap MSB/LSB
    Data32 = (((Data32 & 0xff) << 16) | ((Data32 & 0xff0000) >>16) | ((Data32 & 0xff00)));

    for ( i =0; i < VsccTableCount; i++ ) {
        if (SpiVsccTbl[i].VidDid == Data32) {
            dUVSCC = SpiVsccTbl[i].Vscc;
        }
    }
#endif
    WRITE_MEM32_SPI(R_RCRB_SPI_UVSCC, dUVSCC);
    WRITE_MEM32_SPI(R_RCRB_SPI_LVSCC, dUVSCC);
    }
  }
//####    }

    Status = ReadSPIDescriptor(0x01, 0x00, &Data32);
    if (!EFI_ERROR(Status))
    {
        Data8 = (UINT8)((Data32 & (BIT27 | BIT28 | BIT29)) >> 27);
        SET_MEM8_SPI(R_RCRB_SPI_SSFCTL + 2, Data8);
    }
    TRACE((TRACE_ALWAYS, "[[ SBSpiProgramVSCC() Done. ]]\n"));
}
//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:   IsMobileSku
//
// Description: This function will check the South Bridge whether it is 
//              mobile SKU. 
//
// Input:       None
//
// Output:      BOOLEAN
//                  TRUE  - The South Bridge is mobile SKU.
//                  FALSE - The South Bridge is not mobile SKU.
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

BOOLEAN IsMobileSku (VOID)
{
    return TRUE;    // TODO
}

//----------------------------------------------------------------------------
#if (ACPI_SUPPORT)

#include <Acpi20.h>
#include <Protocol\AcpiSupport.h>

EFI_EVENT       mAcpiEvent;
VOID            *mAcpiReg;
UINT64          gHpetBase = HPET_BASE_ADDRESS;
UINTN           mHpetTblHandle;
SB_ASL_BUFFER   *gSbAslBufPtr = NULL;

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:   CreateSbAcpiCallback
//
// Description: This function will create all ACPI components for SB when
//              ACPI support protocol is available.
//
// Input:       Event   - Event of callback
//              Context - Context of callback.
//
// Output:      None
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

VOID CreateSbAcpiCallback (
    IN EFI_EVENT        Event,
    IN VOID             *Context )
{
    EFI_STATUS                  Status = EFI_SUCCESS;
    EFI_GUID                    SbAslBufPtrGuid = SB_ASL_BUFFER_PTR_GUID;
    CHAR16                      SbAslBufPtrVar[] = SB_ASL_BUFFER_PTR_VARIABLE;
    HPET_20                     *Hpet;
    EFI_ACPI_SUPPORT_PROTOCOL   *As;
    ACPI_HDR                     *DsdtPtr = NULL;
    FACP_20                     *Table = NULL;
    UINT8                       *OtRegDataPtr = NULL;
    ASL_OBJ_INFO                AslObj;
    EFI_ACPI_TABLE_VERSION        Version;
    UINTN                        Handle;
    UINTN                       Index;
    UINT32                      SbAslBufVarPtr;
    UINT32                      OldSbAslBufVarPtr = 0;
    UINT32                      Attributes = 0;
    UINTN                       VarSize;
    UINT8                       OemId[6] = T_ACPI_OEM_ID ;//CONVERT_TO_STRING(T_ACPI_OEM_ID);
    UINT8                       OemTblId[8] = \
                                        T_ACPI_OEM_TBL_ID ;//CONVERT_TO_STRING(T_ACPI_OEM_TBL_ID);

    // It must be only one instance of such protocol
    Status = pBS->LocateProtocol(&gEfiAcpiSupportGuid, NULL, &As);
    if(EFI_ERROR(Status)) {
        TRACE((-1, "ACPI Support Protocol is not ready for SB components\n"));
        return;
    }
    TRACE((-1,"SB Locate Protocol(ACPISupport)- %r Success\n", Status));

    if (gSbSetupData->Hpet) {

        Hpet = MallocZ(sizeof(HPET_20));
        ASSERT(Hpet);
        if (Hpet) {
            // Fill Table header;
            Hpet->Header.Signature = HPET_SIG;
            Hpet->Header.Length    = sizeof(HPET_20);
            Hpet->Header.Revision  = 1;
            Hpet->Header.Checksum  = 0;
            MemCpy(&(Hpet->Header.OemId[0]), OemId, 6);
            MemCpy(&(Hpet->Header.OemTblId[0]), OemTblId, 8);
            Hpet->Header.OemRev     = ACPI_OEM_REV;
            Hpet->Header.CreatorId  = 0x2e494d41;//"AMI."
            Hpet->Header.CreatorRev = CORE_REVISION;

            // Fill HPET Fields  
            // The GAS structure
            Hpet->BaseAddress.AddrSpcID   = GAS_SYS_MEM;
            Hpet->BaseAddress.RegBitWidth = 64;
            Hpet->BaseAddress.RegBitOffs  = 0;
            // Base address of 1K HPET RegBlock space 
            Hpet->BaseAddress.Address = gHpetBase; 

            Hpet->EvtTmrBlockId.TMR_BLK_ID = *(UINT32*)(UINTN)gHpetBase;

            Hpet->MinTickPeriod = 14318; // Approx 1ms
                
            // Add table 
            Status = As->SetAcpiTable( As, \
                                       Hpet, \
                                       TRUE, \
                                       EFI_ACPI_TABLE_VERSION_ALL, \
                                       &mHpetTblHandle );
            TRACE((-1,"ACPISupport.SetAcpiTable() = %r \n", Status));
            ASSERT_EFI_ERROR(Status);
    
            // Free memory used for table image
            pBS->FreePool(Hpet);
        }
    }       

    // Find DSDT ACPI Table
    for (Index = 0; Index < ACPI_RSDT_TABLE_NUM; Index++) {
        Status = As->GetAcpiTable(As, Index, &Table, &Version, &Handle);
        if (EFI_ERROR(Status)) break;//no more tables left    

        if ((Table->Header.Signature == FACP_SIG) && (DsdtPtr == NULL)) {
            DsdtPtr = (ACPI_HDR*)Table->DSDT;
            TRACE((-1, "SBDXE: Found DSDT Table at 0x%08X\n", DsdtPtr));
            break;
        }
    }

    Status = pBS->AllocatePool( EfiReservedMemoryType, \
                                sizeof(SB_ASL_BUFFER), \
                                (VOID**)&gSbAslBufPtr );
    if (!EFI_ERROR(Status)) {
        MemSet(gSbAslBufPtr, sizeof(SB_ASL_BUFFER), 0); 
        Status = GetAslObj( (UINT8*)(DsdtPtr + 1), \
                            DsdtPtr->Length - sizeof(ACPI_HDR)-1, \
                            "CPSB", \
                            otOpReg, \
                            &AslObj );
        if (!EFI_ERROR(Status)) {
            OtRegDataPtr = (UINT8*)AslObj.DataStart;
            SbAslBufVarPtr = (UINT32)gSbAslBufPtr;
            *(UINT32*)(OtRegDataPtr + 2) = SbAslBufVarPtr;

            VarSize = sizeof(SbAslBufVarPtr);
            Status = pRS->GetVariable( SbAslBufPtrVar, \
                                       &SbAslBufPtrGuid, \
                                       &Attributes, \
                                       &VarSize, \
                                       &OldSbAslBufVarPtr );
            if ((EFI_ERROR(Status)) || (SbAslBufVarPtr != OldSbAslBufVarPtr))
                if (EFI_ERROR(Status)) Attributes = (EFI_VARIABLE_NON_VOLATILE | EFI_VARIABLE_BOOTSERVICE_ACCESS);
                Status = pRS->SetVariable( SbAslBufPtrVar, \
                                           &SbAslBufPtrGuid, \
                                           Attributes,
                                           sizeof(SbAslBufVarPtr), \
                                           &SbAslBufVarPtr );
        }
    }
       
    LocatePublishIdeSataAcpiTables();

    // Kill the Event
    pBS->CloseEvent(Event);
}

#endif 

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:   ConfigPciDevices
//
// Description: This function will Enable/Disable onchip PCI device in SB 
//              depend on SETUP questions.
//
// Input:       SystemTable - Pointer to the system table 
//
// Output:      None
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

VOID ConfigPciDevices (
    IN EFI_SYSTEM_TABLE *SystemTable )
{

}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:   CreateSbAcpiComponent
//
// Description: This function creates all ACPI components supported by SB.
//
// Input:       None
//
// Output:      None
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

VOID CreateSbAcpiComponent (VOID)
{
    EFI_STATUS      Status = EFI_SUCCESS;
    UINT8           Buffer8 = 0;

//HPET Support
#if (HPET_SUPPORT)
    if (gSbSetupData->Hpet) {
        Buffer8 = (UINT8)((HPET_BASE_ADDRESS >> 12) & 3) | 0x80;
        // Enable HPET (0x3404)
        WRITE_MEM32_RCRB_S3(gBootScript, RCRB_MMIO_HPTC, Buffer8);
    } else {
        RESET_MEM32_RCRB_S3(gBootScript, RCRB_MMIO_HPTC, 0x80);
    }
#endif

#if (ACPI_SUPPORT)
        Status = RegisterProtocolCallback( &gEfiAcpiSupportGuid, \
                                           CreateSbAcpiCallback, \
                                           NULL, \
                                           &mAcpiEvent, \
                                           &mAcpiReg );
        // If AcpiSupport protocol has been installed we can use it rigth on
        // the way
        pBS->SignalEvent( mAcpiEvent );
#endif


}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:   GetExtCapStrucAddr
//
// Description: This function tries to find the specific PCI Express extended
//              capabilities ID structure address.
//
// Input:       Bus       - The PCI Bus number.
//              Dev       - The PCI Device number.
//              Fun       - The PCI Function number.
//              FindCapId - the specific extended capabilities ID will be
//                          found.
//
// Output:      EFI_STATUS
//                  EFI_SUCCESS   - Found the extended capabilities structure
//                                  successfully, the input CapPtr16 will
//                                  have the structure address.
//                  EFI_NOT_FOUND - Not found the extended capabilities
//                                  structure. 
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS GetExtCapStrucAddr (
    IN UINT8                Bus,
    IN UINT8                Dev,
    IN UINT8                Fun,
    IN UINT16               FindCapId,
    IN UINT16               *CapPtr16 )
{
    UINT32          Buffer32;

    *CapPtr16 = 0x100;

    Buffer32 = READ_PCI32(Bus, Dev, Fun, *CapPtr16);
    while (Buffer32 != 0xffffffff) {
        if ((UINT16)Buffer32 == FindCapId) return EFI_SUCCESS;
        *CapPtr16 = (UINT16)((Buffer32 >> 20) & 0xfffc);
        if (*CapPtr16 == 0) break;
        Buffer32 = READ_PCI32(Bus, Dev, Fun, *CapPtr16);
    }
    return EFI_NOT_FOUND;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:   GetLegCapStrucAddr
//
// Description: This function tries to find the specific capabilities
//              ID structure address.
//
// Input:       Bus       - The PCI Bus number.
//              Dev       - The PCI Device number.
//              Fun       - The PCI Function number.
//              FindCapId - the specific legacy capabilities ID will be
//                          found.
//
// Output:      EFI_STATUS
//                  EFI_SUCCESS   - Found the legacy capabilities structure
//                                  successfully, the input CapPtr16 will
//                                  have the structure address.
//                  EFI_NOT_FOUND - Not found the extended capabilities
//                                  structure. 
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS GetLegCapStrucAddr (
    IN UINT8                Bus,
    IN UINT8                Dev,
    IN UINT8                Fun,
    IN UINT8                FindCapId,
    IN UINT16               *CapPtr16 )
{
    UINT8           Buffer8;

    if (READ_PCI32(Bus, Dev, Fun, PCI_VID) != 0xffffffff) {
        if (READ_PCI16(Bus, Dev, Fun, PCI_STS) & 0x10) {
            *CapPtr16 = ((READ_PCI8(Bus, Dev, Fun, PCI_HDR) & 0x7f) == 2) ? \
                                                                    0x14:0x34;
            *CapPtr16 = (UINT16)READ_PCI8(Bus, Dev, Fun, *CapPtr16);
            if (*CapPtr16 == 0) return EFI_NOT_FOUND;
            Buffer8 = READ_PCI8(Bus, Dev, Fun, *CapPtr16);
            while (Buffer8 != 0) {
                if (Buffer8 == FindCapId) return EFI_SUCCESS;
                Buffer8 = (UINT8)(*CapPtr16) + 1;
                *CapPtr16 = (UINT16)(READ_PCI8(Bus, Dev, Fun, Buffer8));
                if (*CapPtr16 == 0) break;
                Buffer8 = READ_PCI8(Bus, Dev, Fun, *CapPtr16);
            }
        }
    }

    return EFI_NOT_FOUND;
}

#if SB_PCIE_ERROR_LOG_SUPPORT
//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:   SbEnablePciDevErr
//
// Description: Enable the error register of PCI-Express Device.
//
// Input:      Address -  PCI Express Config MMIO of device.
//
// Output:     None
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID SbEnablePciDevErr(IN UINT64 Address)
{
  UINT32 DevBaseAddr = (UINT32)Address;
  UINT8  CapPtr;

  CapPtr = SbFindCapPtr(DevBaseAddr, 0x10);
  if(CapPtr != 0)
  {
    // Clear Error Status
    WRITE_MEM8_S3(gBootScript, DevBaseAddr + CapPtr + 0x0A, (BIT0 | BIT1 | BIT2));

    // Enable CEE/NFE/FEE
    // Root?
    if ((READ_MEM8(DevBaseAddr + CapPtr + 0x02) & 0xF0) == 0x40)
      WRITE_MEM8_S3(gBootScript, DevBaseAddr + CapPtr + 0x1C, (BIT0 | BIT1 | BIT2));

    // End-Device?
    else if ((READ_MEM8(DevBaseAddr + CapPtr + 0x02) & 0xF0) == 0x00)
      WRITE_MEM8_S3(gBootScript, DevBaseAddr + CapPtr + 0x08, (BIT0 | BIT1 | BIT2));
  }
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   SbPciExpressDeviceInitialize
//
// Description: Initialize PCI Express Device Error Handle.
//
// Input:       Address -  PCI Express Config MMIO of device.
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID SbPciExpressDeviceInitialize(IN UINT64 Address)
{
  UINT8   Dev;
  UINT8   Func;
  UINT8   CurrentBus;
  UINT16  Buffer16;
  UINT64  DevAddress;
  UINT8   PciFun = (Address >> 12) & 0x07;
  UINT8   CapPtr;
  UINT8   Buffer8;

  CapPtr = SbFindCapPtr(Address, 0x10);
  Buffer8 = READ_MEM8(Address + CapPtr + 0x08);
  Buffer8 &= 0xF0;
  if (gSbSetupData->PcieRootPortURE[PciFun])
    Buffer8 |= BIT03;

  if (gSbSetupData->PcieRootPortFEE[PciFun])
    Buffer8 |= BIT02;

  if (gSbSetupData->PcieRootPortNFE[PciFun])
    Buffer8 |= BIT01;

  if (gSbSetupData->PcieRootPortCEE[PciFun])
    Buffer8 |= BIT00;

  WRITE_MEM8_S3( gBootScript, \
                 Address + CapPtr + 0x08, \
                 Buffer8 );

  CurrentBus = READ_MEM8((UINT32)Address + PCIBR_REG_SBUSN);

  for (Dev = 0; Dev < 32; Dev++)
  {
    for (Func = 0; Func < 8; Func++)
    {
      DevAddress = (UINT64)SB_PCIE_CFG_ADDRESS(CurrentBus, Dev, Func, 0);

      if (READ_MEM16(DevAddress) == 0xFFFF)
        continue;

      SbEnablePciDevErr(DevAddress);

      Buffer16 = READ_MEM16((UINT32)SB_PCIE_CFG_ADDRESS(CurrentBus, Dev, 0, 0) + PCI_SCC);
      if (Buffer16 == 0x0604)
      {
        DevAddress = (UINT64)SB_PCIE_CFG_ADDRESS(CurrentBus, Dev, 0, 0);
        SbPciExpressDeviceInitialize(DevAddress);
      }
    }
  }
}
#endif

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:   SbInitAfterDeviceInstall
//
// Description: This callback function is called when a PCI I/O Protocol is
//              installed.
//
// Input:       Event   - Event of callback
//              Context - Context of callback.
//
// Output:      EFI_SUCCESS
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

VOID SbInitAfterDeviceInstall (
    IN EFI_EVENT        Event,
    IN VOID             *Context )
{
    EFI_STATUS              Status;
    UINTN                   BufferSize = 20 * sizeof(EFI_HANDLE);
    EFI_HANDLE              Handle;
    EFI_PCI_IO_PROTOCOL     *PciIo;
    PCI_STD_DEVICE          Pci;
    UINTN                   i = 0;
    UINTN                   PciSeg;
    UINTN                   PciBus;
    UINTN                   PciDev;
    UINTN                   PciFun;
#if SB_PCIE_ERROR_LOG_SUPPORT
    UINT64                  Address = 0;
    EFI_SM_ELOG_PROTOCOL    *GenericElogProtocol = NULL;
#endif

    Status = pBS->LocateHandle( ByRegisterNotify, \
                                NULL, \
                                gSbInitNotifyReg, \
                                &BufferSize, \
                                &Handle );
    ASSERT_EFI_ERROR(Status);
    if (EFI_ERROR(Status)) return;
    //
    // Locate PciIo protocol installed on Handle
    //

    Status = pBS->HandleProtocol( Handle, &gEfiPciIoProtocolGuid, &PciIo );
    ASSERT_EFI_ERROR(Status);
    if (EFI_ERROR(Status)) return;

    // Get PCI Device Bus/Device/Function Numbers
    Status = PciIo->GetLocation( PciIo, &PciSeg, &PciBus, &PciDev, &PciFun );
    ASSERT_EFI_ERROR(Status);
    if (EFI_ERROR(Status)) return;

    TRACE((TRACE_ALWAYS, "PCI Bus, Device, function = %X, %X,%X\n", PciBus, PciDev, PciFun ));

    if (((UINT8)PciBus == SMBUS_BUS) && \
        ((UINT8)PciDev == SMBUS_DEV) && \
        ((UINT8)PciFun == SMBUS_FUN)) {
      if ((READ_PCI32_SMBUS(SMBUS_REG_MBASE0_ADDR) & 0xFFFFFFF0) && \
          ((READ_PCI8_SMBUS(SMBUS_REG_PCICMD) & B_PCH_SMBUS_PCICMD_MSE) == 0))
        SET_PCI8_SMBUS(SMBUS_REG_PCICMD, B_PCH_SMBUS_PCICMD_MSE);

      if ((READ_PCI16_SMBUS(SMBUS_REG_BASE_ADDR) & 0xFFC0) && \
          ((READ_PCI8_SMBUS(SMBUS_REG_PCICMD) & B_PCH_SMBUS_PCICMD_IOSE) == 0))
        SET_PCI8_SMBUS(SMBUS_REG_PCICMD, B_PCH_SMBUS_PCICMD_IOSE);

      gEventCount -= 1;
    }
									//(EIP101204)>> 
    if (((UINT8)PciBus == HDA_BUS) && \
        ((UINT8)PciDev == HDA_DEV) && \
        ((UINT8)PciFun == HDA_FUN)) {
      if(gSbSetupData->AzaliaPme){
          SET_PCI16_HDA(R_PCH_HDA_PCS, B_PCH_HDA_PCS_PMEE);
      }
      gEventCount -= 1;
    }									//<<(EIP101204)

    if (((UINT8)PciBus == SATA_BUS) && \
        ((UINT8)PciDev == SATA_DEV) && \
        ((UINT8)PciFun == SATA_FUN)) {
      Status = PciIo->Pci.Read (PciIo,
                                EfiPciIoWidthUint32,
                                0,
                                sizeof (Pci) / sizeof (UINT32),
                                &Pci);

      //Check for Onboard Raid controller and if's it's onboard install the Guid on that Handle. 
      if (!EFI_ERROR (Status))
      {
        if ( Pci.Header.ClassCode[1] == PCI_CL_MASS_STOR_SCL_RAID && \
             Pci.Header.VendorId == 0x8086 && \
             (Pci.Header.DeviceId == 0x282A || Pci.Header.DeviceId == 0x2822 || Pci.Header.DeviceId == 0x2826) ) { // for mobile, Desktop, WS and Server

           pBS->InstallProtocolInterface(&Handle, \
                                         &gOnboardRaidGuid, \
                                         EFI_NATIVE_INTERFACE, \
                                         NULL);

            //
            // Install the Bus Specific Override Protocol on the Raid Controller Handle
            //
            Status = pBS->InstallMultipleProtocolInterfaces(&Handle,
                        &gEfiBusSpecificDriverOverrideProtocolGuid,
                        &RaidBusSpecificDriverOverride,
                        NULL);

           ASSERT_EFI_ERROR(Status);
        }
      }
      gEventCount -= 1;
    }

    if (((UINT8)PciBus == PCIEBRS_BUS) && \
        ((UINT8)PciDev == PCIEBRS_DEV) && \
        (((UINT8)PciFun >= PCIEBRS_FUN) || ((UINT8)PciFun >= PCIEBRS8_FUN))) {
#if SB_PCIE_ERROR_LOG_SUPPORT
      Status = pBS->LocateProtocol( &gElogProtocolGuid,
                                    NULL,
                                    &GenericElogProtocol );
      if (!EFI_ERROR (Status)) {
        gErrorLoggingFlag = TRUE;
        Address = SB_PCIE_CFG_ADDRESS((UINT8)PciBus, (UINT8)PciDev, (UINT8)PciFun, 0);
        SbPciExpressDeviceInitialize(Address);
      }
#endif
      gEventCount -= 1;
    }

    // Kill the Event
    if (gEventCount == 1)
        pBS->CloseEvent(Event);
}

#ifdef CSM_OPRROM_POLICY_GUID
//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:   SbCheckOprom
//
// Description: This callback function is called before/after processing all
//              PCI optonal ROM.
//
// Input:       Event   - Event of callback
//              Context - Context of callback.
//
// Output:      None
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

VOID SbCheckOprom (
    IN EFI_EVENT   Event,
    IN VOID        *Context )
{
    EFI_STATUS                  Status;
    UINTN                       BufferSize = sizeof(EFI_HANDLE);
    EFI_HANDLE                  Handle;
    CSM_PLATFORM_POLICY_DATA    *Data;
    UINTN                       Seg;
    UINTN                       Bus;
    UINTN                       Dev;
    UINTN                       Fun;
    
    Status = pBS->LocateHandle( ByRegisterNotify, \
                                NULL, \
                                gCsmOpromReg, \
                                &BufferSize, \
                                &Handle );
    ASSERT_EFI_ERROR(Status);
    if (EFI_ERROR(Status)) return;

    // Locate CSM Platform Policy data
    Status = pBS->HandleProtocol( Handle, &gCsmOpromPolicyGuid, &Data );

    if ( EFI_ERROR(Status) ) return;
    if (Data == NULL) return;
    if (Data->ExecuteThisRom == FALSE) return;
	if(Data->PciIo == NULL) return;

    Status = Data->PciIo->GetLocation( Data->PciIo, &Seg, &Bus, &Dev, &Fun );

#if SataDriver_SUPPORT
#if !defined(CsmOptOut_SUPPORT) || (CsmOptOut_SUPPORT == 0)
    if ((Bus == SATA_BUS) && (Dev == SATA_DEV) && (Fun == SATA_FUN)) {
      if (gSbSetupData->SataInterfaceMode == SATA_MODE_RAID) {
        if (gSbSetupData->SataRaidRom != 1)
          Data->ExecuteThisRom = TRUE;
        else
          Data->ExecuteThisRom = FALSE;
      }
    }
#endif
#endif

    // Close the event if needed.
    // pBS->CloseEvent(Event);
}
#endif

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:   ReserveSbResources
//
// Description: This function reserves system resources for SB internal 
//              device(s).
//
// Input:       ImgHandle - Image handle
//              CntrHandle - Control handle
//
// Output:      Return Status based on errors that occurred while waiting for
//              time to expire.
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS ReserveSbResources (
    IN EFI_HANDLE       ImgHandle,
    IN EFI_HANDLE       CntrHandle )
{
    EFI_STATUS          Status;

#if (CORE_VERSION >= 4600)
    Status = LibAllocCspResource( gSbResTable, \
                                  gSbResTableCount, \
                                  ImgHandle, \
                                  CntrHandle );
#else
    DXE_SERVICES        *gDxeSvcTbl;
    UINTN               i;

    gDxeSvcTbl = (DXE_SERVICES*)GetEfiConfigurationTable(pST,&gDxeSvcTblGuid);
    if(gDxeSvcTbl == NULL) return EFI_NOT_AVAILABLE_YET;
    
    for (i = 0; i < gSbResTableCount; i++) {
        // Remove gSbResTable existant IO to non-existant IO
        if (gSbResTable[i].Attributes == 0xffffffffffffffff) {
            Status = gDxeSvcTbl->RemoveIoSpace( gSbResTable[i].ResBase, \
                                                gSbResTable[i].ResLength );
        } else {
            Status = gDxeSvcTbl->RemoveMemorySpace( gSbResTable[i].ResBase, \
                                                    gSbResTable[i].ResLength);
        }                    
        if (EFI_ERROR(Status)) {
            TRACE((-1, "RemoveSpace B=%lX, L=%X, i=%d, S=%r\n", \
                gSbResTable[i].ResBase, gSbResTable[i].ResLength, i, Status));
            ASSERT_EFI_ERROR(Status);
            break;
        }
    }   

    // Convert gSbResTable non-existant IO to existant IO
    Status = AllocCspResource( gDxeSvcTbl, gSbResTable, gSbResTableCount, \
                               ImgHandle, CntrHandle, TRUE );
    if(EFI_ERROR(Status)) return  Status;
#endif

    return Status;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:   AddLpcStdIoSpace
//
// Description: This function adds LPC I/O or I/O resources to the global
//              coherency domain of the processor.
//
// Input:       None
//
// Output:      Return Status based on errors that occurred while waiting for
//              time to expire.
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS AddLpcStdIoSpace ( VOID )
{
    EFI_STATUS          Status;
    DXE_SERVICES        *DxeSvcTbl;
    LPC_IO_STD_DECODE   LpcIoStdDecode[] = {
                                             {0x3F8, 8}, {0x2F8, 8}, {0x220, 8}, {0x228, 8},\
                                             {0x238, 8}, {0x2E8, 8}, {0x338, 8}, {0x3E8, 8},\
                                             {0x378, 8}, {0x778, 8}, {0x278, 8}, {0x678, 8},\
                                             {0x3BC, 4}, {0x7BC, 4}, {0x3F0, 6}, {0x3F7, 1},\
                                             {0x370, 6}, {0x377, 1}, {0x200, 8}, {0x208, 8},\
                                             {0x060, 1}, {0x064, 1}, {0x062, 1}, {0x066, 1},\
                                             {0x02E, 1}, {0x02F, 1}, {0x04E, 1}, {0x04F, 1}
                                           };
    UINT8               TableLength = sizeof(LpcIoStdDecode) / sizeof(LPC_IO_STD_DECODE);
    UINT8               i;
    UINT8               j;
    UINT8               AddressMask;
    UINT16              GenDecodeBase;
    UINT16              GenDecodeLength = 0;

    DxeSvcTbl = (DXE_SERVICES*)GetEfiConfigurationTable(pST,&gDxeSvcTblGuid);
    if(DxeSvcTbl == NULL) return EFI_NOT_AVAILABLE_YET;

    for (i = 0; i < TableLength; i++) {

      Status = DxeSvcTbl->AddIoSpace ( EfiGcdIoTypeIo,\
                                       LpcIoStdDecode[i].Address, \
                                       LpcIoStdDecode[i].Length );
    }

    for (i = 0; i < 4; i++) {
      GenDecodeBase = READ_PCI16_SB(SB_REG_GEN1_DEC + i * 4) & 0xFFFC;
      AddressMask = READ_PCI8_SB((SB_REG_GEN1_DEC + 2) + i * 4) & 0x00FC;

      if (GenDecodeBase == 0) continue;

      for (j = 2; j < 8; j++) {
        if (AddressMask & (BIT00 << j)) GenDecodeLength += (BIT00 << j);
      }
      GenDecodeLength += 4;

      Status = DxeSvcTbl->AddIoSpace ( EfiGcdIoTypeIo,\
                                       GenDecodeBase, \
                                       GenDecodeLength );
    }

    return Status;
}

//**********************************************************************

BOOT_SCRIPT_SB_PCI_REG_SAVE gPciRegistersSave[] = {
  SB_REG(SB_REG_PIRQ_A)           , EfiBootScriptWidthUint32, 0xffffffff, // 0x60 The register will be filled in later.
  SB_REG(SB_REG_PIRQ_E)           , EfiBootScriptWidthUint32, 0xffffffff, // 0x68 The register will be filled in later.
  SB_REG(SB_REG_LPC_IO_DEC)       , EfiBootScriptWidthUint16, 0xffff,     // 0x80
  SB_REG(SB_REG_LPC_EN)           , EfiBootScriptWidthUint16, 0xffff,     // 0x82
  SB_REG(SB_REG_GEN1_DEC)         , EfiBootScriptWidthUint32, 0xffffffff, // 0x84
  SB_REG(SB_REG_GEN2_DEC)         , EfiBootScriptWidthUint32, 0xffffffff, // 0x88
  SB_REG(SB_REG_GEN3_DEC)         , EfiBootScriptWidthUint32, 0xffffffff, // 0x8C
  SB_REG(SB_REG_GEN4_DEC)         , EfiBootScriptWidthUint32, 0xffffffff, // 0x90
  SB_REG(SB_REG_GEN_PMCON_1)      , EfiBootScriptWidthUint16, 0xffffffff, // 0xA0
  SB_REG(SB_REG_BIOS_CNTL)        , EfiBootScriptWidthUint8,  0xffffffff, // 0xDC,

  PCIBR_REG(PCIBR_REG_PBUSN)      , EfiBootScriptWidthUint32, 0xffffffff, // 0x18
  PCIBR_REG(PCIBR_REG_IOBASE)     , EfiBootScriptWidthUint16, 0xffffffff, // 0x1C
  PCIBR_REG(PCIBR_REG_MBASE)      , EfiBootScriptWidthUint32, 0xffffffff, // 0x20
  PCIBR_REG(PCIBR_REG_PMBASE)     , EfiBootScriptWidthUint32, 0xffffffff, // 0x24
  PCIBR_REG(PCIBR_REG_PMBASEU)    , EfiBootScriptWidthUint32, 0xffffffff, // 0x28
  PCIBR_REG(PCIBR_REG_INTR_LN)    , EfiBootScriptWidthUint8,  0xffffffff, // 0x3C
  PCIBR_REG(PCIBR_REG_SPDH)       , EfiBootScriptWidthUint16, 0xffffffff, // 0x40
  PCIBR_REG(PCIBR_REG_DTC)        , EfiBootScriptWidthUint32, 0xffffffff, // 0x44
  PCIBR_REG(PCIBR_REG_BPC)        , EfiBootScriptWidthUint32, 0xffffffff, // 0x4C
  PCIBR_REG(PCIBR_REG_PCICMD)     , EfiBootScriptWidthUint8,  0xffffffff, // 0x04

  HDA_REG(R_PCH_HDA_HDBARL)       , EfiBootScriptWidthUint32, 0xffffffff, // 0x10
  HDA_REG(R_PCH_HDA_HDBARU)       , EfiBootScriptWidthUint32, 0xffffffff, // 0x14

  SMBUS_REG(SMBUS_REG_MBASE0_ADDR), EfiBootScriptWidthUint32, 0xffffffff, // 0x10
  SMBUS_REG(SMBUS_REG_MBASE1_ADDR), EfiBootScriptWidthUint32, 0xffffffff, // 0x14
  SMBUS_REG(SMBUS_REG_BASE_ADDR)  , EfiBootScriptWidthUint32, 0xffffffff, // 0x20
  SMBUS_REG(SMBUS_REG_INTR_LN)    , EfiBootScriptWidthUint16, 0xffffffff, // 0x3C
  SMBUS_REG(SMBUS_REG_PCICMD)     , EfiBootScriptWidthUint16, 0xffffffff, // 0x04

  THERMAL_REG(THERMAL_REG_TBAR)  ,  EfiBootScriptWidthUint32, 0xffffffff, // 0x10 Thermal device is not getting restored, don't know why
  THERMAL_REG(THERMAL_REG_PCICMD),  EfiBootScriptWidthUint16, 0xffffffff, // 0x04 Thermal device is not getting restored, don't know why
  THERMAL_REG(THERMAL_REG_INTR_LN), EfiBootScriptWidthUint32, 0xffffffff, // 0x3C Thermal device is not getting restored, don't know why
};

BOOT_SCRIPT_SB_PCI_REG_SAVE gSata1RegistersSave[] = {
  SATA_REG(SATA_REG_MAP)       , EfiBootScriptWidthUint8,  0xffffffff, // 0x90
  SATA_REG(SATA_REG_PCIPI)     , EfiBootScriptWidthUint8,  0xffffffff, // 0x09
  SATA_REG(SATA_REG_INTR_LN)   , EfiBootScriptWidthUint8,  0xffffffff, // 0x3c
  SATA_REG(SATA_REG_IDETIM)    , EfiBootScriptWidthUint32, 0xffffffff, // 0x40
  SATA_REG(SATA_REG_SIDETIM)   , EfiBootScriptWidthUint8,  0xffffffff, // 0x44
  SATA_REG(SATA_REG_SDMACTL)   , EfiBootScriptWidthUint8,  0xffffffff, // 0x48
  SATA_REG(SATA_REG_SDMATIM)   , EfiBootScriptWidthUint16, 0xffffffff, // 0x4a
  SATA_REG(SATA_REG_IDE_CONFIG), EfiBootScriptWidthUint32, 0xffffffff, // 0x54
  SATA_REG(SATA_REG_PMCS)      , EfiBootScriptWidthUint16, 0xffffffff, // 0x74
  SATA_REG(SATA_REG_PCS)       , EfiBootScriptWidthUint16, 0xffffffff, // 0x92
  SATA_REG(SATA_REG_PCMD_BAR)  , EfiBootScriptWidthUint32, 0xffffffff, // 0x10
  SATA_REG(SATA_REG_PCNL_BAR)  , EfiBootScriptWidthUint32, 0xffffffff, // 0x14
  SATA_REG(SATA_REG_SCMD_BAR)  , EfiBootScriptWidthUint32, 0xffffffff, // 0x18
  SATA_REG(SATA_REG_SCNL_BAR)  , EfiBootScriptWidthUint32, 0xffffffff, // 0x1c
  SATA_REG(SATA_REG_BM_BASE)   , EfiBootScriptWidthUint32, 0xffffffff, // 0x20
  SATA_REG(SATA_REG_ABAR)      , EfiBootScriptWidthUint32, 0xffffffff, // 0x24
  SATA_REG(SATA_REG_PCICMD)    , EfiBootScriptWidthUint8,  0xffffffff, // 0x04
};

BOOT_SCRIPT_SB_PCI_REG_SAVE gSata2RegistersSave[] = {
  SATA2_REG(SATA_REG_MAP)       , EfiBootScriptWidthUint8,  0xffffffff, // 0x90
  SATA2_REG(SATA_REG_PCIPI)     , EfiBootScriptWidthUint8,  0xffffffff, // 0x09
  SATA2_REG(SATA_REG_INTR_LN)   , EfiBootScriptWidthUint8,  0xffffffff, // 0x3c
  SATA2_REG(SATA_REG_IDETIM)    , EfiBootScriptWidthUint32, 0xffffffff, // 0x40
  SATA2_REG(SATA_REG_SIDETIM)   , EfiBootScriptWidthUint8,  0xffffffff, // 0x44
  SATA2_REG(SATA_REG_SDMACTL)   , EfiBootScriptWidthUint8,  0xffffffff, // 0x48
  SATA2_REG(SATA_REG_SDMATIM)   , EfiBootScriptWidthUint16, 0xffffffff, // 0x4a
  SATA2_REG(SATA_REG_IDE_CONFIG), EfiBootScriptWidthUint32, 0xffffffff, // 0x54
  SATA2_REG(SATA_REG_PMCS)      , EfiBootScriptWidthUint16, 0xffffffff, // 0x74
  SATA2_REG(SATA_REG_PCS)       , EfiBootScriptWidthUint16, 0xffffffff, // 0x92
  SATA2_REG(SATA_REG_PCMD_BAR)  , EfiBootScriptWidthUint32, 0xffffffff, // 0x10
  SATA2_REG(SATA_REG_PCNL_BAR)  , EfiBootScriptWidthUint32, 0xffffffff, // 0x14
  SATA2_REG(SATA_REG_SCMD_BAR)  , EfiBootScriptWidthUint32, 0xffffffff, // 0x18
  SATA2_REG(SATA_REG_SCNL_BAR)  , EfiBootScriptWidthUint32, 0xffffffff, // 0x1c
  SATA2_REG(SATA_REG_BM_BASE)   , EfiBootScriptWidthUint32, 0xffffffff, // 0x20
  SATA2_REG(SATA_REG_ABAR)      , EfiBootScriptWidthUint32, 0xffffffff, // 0x24
  SATA2_REG(SATA_REG_PCICMD)    , EfiBootScriptWidthUint8,  0xffffffff, // 0x04
};

#if defined AMIUSB_SUPPORT && AMIUSB_SUPPORT == 1
VOID CheckDisableUsbControllers(VOID)
{
  UINT32 FunctionDisable;
  EFI_STATUS Status;
  EFI_GUID   EfiGlobalVariableGuid = EFI_GLOBAL_VARIABLE;
  UINTN      BootOrderSize = 0;
  UINT16     *BootOrder = NULL;
  PCH_SERIES PchSeries = GetPchSeries();

  Status = pBS->LocateProtocol( &gEfiUsbProtocolGuid,
                                NULL,
                                &gUsbProtocol );
  if (EFI_ERROR(Status)) return;

  if (gDisableAllUsbControllers) {

    Status = pRS->GetVariable( L"BootOrder", \
                               &EfiGlobalVariableGuid, \
                               NULL, \
                               &BootOrderSize, \
                               &BootOrder );
    if (Status == EFI_NOT_FOUND) return;

    // Shutdown legacy
    gUsbProtocol->UsbRtShutDownLegacy();

    WRITE_PCI16_EHCI(EHCI_REG_PCICMD, 0);
    if (PchSeries != PchLp) {
      WRITE_PCI16_EHCI2(EHCI_REG_PCICMD, 0);
    }
    WRITE_PCI16(XHCI_BUS, XHCI_DEV, XHCI_FUN, XHCI_REG_PCICMD, 0);

    FunctionDisable = (READ_MEM32_RCRB(RCRB_MMIO_FD) | BIT13 | BIT15 | BIT27);
    WRITE_MEM32_RCRB_S3(gBootScript, RCRB_MMIO_FD, FunctionDisable);
  }/* else if ((gSbSetupData->PchUsb20[0] == 0) && (gSbSetupData->PchUsb20[1] == 0)) {
    WRITE_PCI16_EHCI(EHCI_REG_PCICMD, 0);
    if (PchSeries != PchLp) {
      WRITE_PCI16_EHCI2(EHCI_REG_PCICMD, 0);
    }
    FunctionDisable = (READ_MEM32_RCRB(RCRB_MMIO_FD) | BIT13 | BIT15);
    WRITE_MEM32_RCRB_S3(gBootScript, RCRB_MMIO_FD, FunctionDisable);
  }*/
}
#endif
									//(EIP124410)>>
//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure: UpdateSmbios136Table
//
// Description: Build and fill SmBios type 0x88 for CRID.
//
// Input:       EFI_EVENT   - Event,
//              VOID        - *Context
//
// Output:      EFI_STATUS  - EFI_SUCCESS.
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID
UpdateSmbios136Table(
    IN EFI_EVENT    Event,
    IN VOID         *Context
)
{
    EFI_STATUS                        Status;
    EFI_MISC_OEM_TYPE_0x88            Data88;
    DXE_PCH_PLATFORM_POLICY_PROTOCOL  *PchPlatformPolicy;

    Status = pBS->LocateProtocol(&gEfiSmbiosProtocolGuid, NULL, &gSmbiosProtocol);
    if (EFI_ERROR(Status)) return;
    
    //Clear all data
    pBS->SetMem (&Data88, sizeof(EFI_MISC_OEM_TYPE_0x88), 0);

    Data88.Header.Type = 0x88;
    Data88.Header.Length = 6;
    Data88.Header.Handle = 0;

    Status = pBS->LocateProtocol ( &gDxePchPlatformPolicyProtocolGuid, \
                                   NULL, \
                                   &PchPlatformPolicy);
    if (!EFI_ERROR (Status)) {
        if (PchPlatformPolicy->DeviceEnabling->Crid == 1){
            Data88.OemInfo = 0x5a5a;
        }
    }

    Status = gSmbiosProtocol->SmbiosAddStructure((UINT8 *)&Data88, sizeof(EFI_MISC_OEM_TYPE_0x88));

    pBS->CloseEvent(Event);
}
									//(EIP124410)<<
#if defined CSM_SUPPORT && CSM_SUPPORT == 1                                       // [EIP134850] >>
//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   SBSataRegSaveRestore
//
// Description: This callback will be called before and after installing legacy OpROM
//
// Input:		
//  IN EFI_EVENT Event - Callback event
//  IN VOID *Context - pointer to calling context
//
// Output:      None
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID SBSataRegSaveRestore(
    IN EFI_EVENT Event, 
    IN VOID *Context
)
{
    EFI_STATUS                  Status;
    EFI_HANDLE                  Handle;
    UINTN                       Size = sizeof(EFI_HANDLE);
    UINTN                       Seg, Bus, Dev, Fun;
    UINT32                      ABar, RegVal;
    UINT8                       Index = 0;
    CSM_PLATFORM_POLICY_DATA    *OpRomStartEndProtocol;
    EFI_PCI_IO_PROTOCOL         *PciIo;
    PCH_SERIES                  PchSeries = GetPchSeries();

    TRACE((TRACE_ALWAYS, "SBSataRegSaveRestore() !!!\n"));
    Status = pBS->LocateHandle(ByRegisterNotify, NULL, SataOpRomRegistration, &Size, &Handle);
    ASSERT_EFI_ERROR(Status);
    if (EFI_ERROR(Status)) return;

    Status = pBS->HandleProtocol(Handle, &OpRomStartEndProtocolGuid, &OpRomStartEndProtocol);
    ASSERT_EFI_ERROR(Status);
    if (EFI_ERROR(Status)) return;

    if(OpRomStartEndProtocol != NULL) {
        //pre-process OpROM callback
        PciIo = OpRomStartEndProtocol->PciIo;

        if (PciIo == NULL){
            // this OpROM is not Intel SATA RAID OpROM
            IsSataOpROM = 0;
            return;
        }

        PciIo->GetLocation(PciIo, &Seg, &Bus, &Dev, &Fun);
        TRACE((TRACE_ALWAYS, "OpRom Location: Seg:%x, Bus:%x, Dev:%x, Fun:%x\n", Seg, Bus, Dev, Fun));
        if((Bus == SATA_BUS) && (Dev == SATA_DEV) && (Fun == SATA_FUN)){
            // This OpROM is Intel SATA RAID OpROM
            TRACE((TRACE_ALWAYS, "Before execute SATA OpROM... save sata regs...\n"));
            if (SaveSataReg != 0) return;
            SaveSataReg = 1;
            IsSataOpROM = 1;
            DLAE = 0;
            // Save PxCMD bit 25 of each Sata ports
            ABar = READ_MMIO32(SATA_PCIE_REG(SATA_REG_ABAR));
            TRACE((TRACE_ALWAYS, "ABar = %x Index = %x MaxPortNumber = %x\n", ABar, Index, GetPchMaxSataPortNum()));
            while(Index < GetPchMaxSataPortNum()){
                RegVal = READ_MMIO32((UINT64)(ABar + 0x118 + (0x80 * Index)));   // R_PCH_SATA_AHCI_P0CMD
                TRACE((TRACE_ALWAYS, "Index = %x, RegVal = %x\n", Index, RegVal));
                if ((RegVal != 0xFFFFFFFF) && (RegVal & BIT24)){
                    DLAE |= (UINT8)((RegVal & BIT25) >> (25 - Index));
                }
                Index++;
            }
            TRACE((TRACE_ALWAYS, "DLAE = %x\n", DLAE));
        } else {
            // this OpROM is not Intel SATA RAID OpROM
            IsSataOpROM = 0;
        }
    } else { 
        //post-process OpROM callback
        if ((SaveSataReg == 1) && (IsSataOpROM == 1)){
            TRACE((TRACE_ALWAYS, "After execute SATA OpROM... restore sata regs...\n"));
            // Restore PxCMD bit 25 of each Sata ports
            ABar = READ_MMIO32(SATA_PCIE_REG(SATA_REG_ABAR));
            while(Index < GetPchMaxSataPortNum()){
                RegVal = READ_MMIO32((UINT64)(ABar + 0x118 + (0x80 * Index)));   // R_PCH_SATA_AHCI_P0CMD
                if(RegVal != 0xFFFFFFFF){
                    if(DLAE & (BIT0 << Index)){
                        RegVal |= BIT25;
                        WRITE_MMIO32((UINT64)(ABar + 0x118 + (0x80 * Index)), RegVal);
                        TRACE((TRACE_ALWAYS, "Sata Port %x restore done\n", Index));
                    }
                }
                Index++;
            }
        }
    }
}
#endif                                                                                // [EIP134850] <<

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:   InitSbRegsBeforeBoot
//
// Description: This function can initialize any SB registers before DXE
//              stage exiting.
//
// Input:       Event   - Event of callback
//              Context - Context of callback.
//
// Output:      None
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

VOID InitSbRegsBeforeBoot (
    IN EFI_EVENT        Event,
    IN VOID             *Context )
{
  UINT32      i, j;
  UINT8       *SbRcba = (UINT8*)(UINTN)SB_RCRB_BASE_ADDRESS; 
  UINT32      Data32;
  UINT32      PortImplemented = 0x0f;
  UINT32      GlobalPchControl;
  UINT64      AHCIBar = 0;
//  UINT16      Offset;                                       //[EIP124245]
  UINT8       Data8;
  UINT32                     Index;
  EFI_ACPI_SUPPORT_PROTOCOL  *As;
  FACP_20                    *Table = NULL;
  EFI_ACPI_TABLE_VERSION     Version;
  UINTN                      Handle;
  ACPI_HDR                   *DsdtPtr = NULL;
  EFI_STATUS                 Status;
  PCH_SERIES 				 PchSeries = GetPchSeries();

  for (i = 0; i < sizeof(gPciRegistersSave)/ sizeof(BOOT_SCRIPT_SB_PCI_REG_SAVE); ++i) {
    gPciRootBridgeIo->Pci.Read( \
                            gPciRootBridgeIo, \
                            gPciRegistersSave[i].Width, \
                            gPciRegistersSave[i].Address, \
                            1, \
                            &Data32);

    Data32 &= gPciRegistersSave[i].Mask;
    BOOT_SCRIPT_S3_PCI_CONFIG_WRITE_MACRO( \
                            gBootScript, \
                            gPciRegistersSave[i].Width, \
                            gPciRegistersSave[i].Address, \
                            1, \
                            &Data32);
  }
  if (PchSeries != PchLp) {   
    gPciRootBridgeIo->Pci.Read( \
                            gPciRootBridgeIo, \
                            EfiBootScriptWidthUint32, \
                            SB_REG(SB_REG_GPI_ROUT) , \
                            1, \
                            &Data32);

    Data32 &= 0xffffffff;
    BOOT_SCRIPT_S3_PCI_CONFIG_WRITE_MACRO( \
                            gBootScript, \
                            EfiBootScriptWidthUint32, \
                            SB_REG(SB_REG_GPI_ROUT) , \
                            1, \
                            &Data32);
  }else{
    Data32 = IoRead32(GPIO_BASE_ADDRESS + GP_IOREG_GPI_ROUT2);
    Data32 &= 0xffffffff;
    BOOT_SCRIPT_S3_IO_WRITE_MACRO( \
                            gBootScript, \
                            EfiBootScriptWidthUint32, \
                            GPIO_BASE_ADDRESS + GP_IOREG_GPI_ROUT2, \
                            1, \
                            &Data32);
  }

#if defined (HOST_WLAN_PP_EN) && HOST_WLAN_PP_EN == 1

  Data32 = READ_MEM32_RCRB(ICH_RCRB_PMCFG) | BIT04; // 0x3318
  WRITE_MEM32_RCRB (ICH_RCRB_PMCFG , Data32);
  BOOT_SCRIPT_S3_MEM_WRITE_MACRO( \
                            gBootScript, \
                            EfiBootScriptWidthUint32, \
                            SbRcba + ICH_RCRB_PMCFG, \
                            1, \
                            &Data32);

#endif

  Data32 = READ_MEM32_RCRB(RCRB_MMIO_FD); // 0x3418
  BOOT_SCRIPT_S3_MEM_WRITE_MACRO( \
                            gBootScript, \
                            EfiBootScriptWidthUint32, \
                            SbRcba + R_PCH_RCRB_FUNC_DIS, \
                            1, \
                            &Data32);

  // Trap Configuration
  for (i = RCRB_MMIO_IO_TRAP_0; i < (RCRB_MMIO_IO_TRAP_3 + 8); i += 4) {
    Data32 = *(UINT32 *)(SbRcba + i);
    BOOT_SCRIPT_S3_MEM_WRITE_MACRO( \
                            gBootScript, \
                            EfiBootScriptWidthUint32, \
                            SbRcba + i, \
                            1, \
                            &Data32);
  }

  //RootPort register save
  for(i = 0; i <= 7; i++)
  {
    gPciRootBridgeIo->Pci.Read ( 
                            gPciRootBridgeIo, \
                            EfiPciWidthUint32, \
                            SB_PCI_CFG_ADDRESS(PCIEBRS_BUS, PCIEBRS_DEV, i, 0x00), \
                            1, \
                            &Data32);
    if(Data32 != 0xffffffff)
    {
      for(j = 0x18; j < 0x34; j += 4)
      {
        gPciRootBridgeIo->Pci.Read ( \
                            gPciRootBridgeIo, \
                            EfiPciWidthUint32, \
                            SB_PCI_CFG_ADDRESS(PCIEBRS_BUS, PCIEBRS_DEV, i, j), \
                            1, \
                            &Data32);

        BOOT_SCRIPT_S3_PCI_CONFIG_WRITE_MACRO( \
                            gBootScript, \
                            EfiBootScriptWidthUint32, \
                            SB_PCI_CFG_ADDRESS(PCIEBRS_BUS, PCIEBRS_DEV, i, j), \
                            1, \
                            &Data32);
      }
    }
  }
  //End  

//Save Onboard LAN BAR- Efi aware Vista GBE bar is not restored by OS if network driver is not installed.

  gPciRootBridgeIo->Pci.Read ( \
                          gPciRootBridgeIo, \
                          EfiPciWidthUint32, \
                          LAN_REG(0x00), \
                          1, \
                          &Data32);
  if(Data32 != 0xffffffff)
  {
    for(j = 0x10; j < 0x1B; j += 4)
    {
      gPciRootBridgeIo->Pci.Read ( \
                          gPciRootBridgeIo, \
                          EfiPciWidthUint32, \
                          LAN_REG(j), \
                          1, \
                          &Data32);
     
      BOOT_SCRIPT_S3_PCI_CONFIG_WRITE_MACRO(
      gBootScript, \
      EfiBootScriptWidthUint32, \
      LAN_REG(j), \
      1, \
      &Data32);
    }
  }

//Save Sata and ABAR S3 reg.
  gPciRootBridgeIo->Pci.Read( \
    gPciRootBridgeIo, \
    EfiBootScriptWidthUint32, \
    SATA_REG(PCI_VID), \
    1, \
    &Data32);
  if (Data32 != 0xffffffff) {
    for (i = 0; i < sizeof(gSata1RegistersSave)/ sizeof(BOOT_SCRIPT_SB_PCI_REG_SAVE); ++i) {
        gPciRootBridgeIo->Pci.Read( \
            gPciRootBridgeIo, \
            gSata1RegistersSave[i].Width, \
            gSata1RegistersSave[i].Address, \
            1, \
            &Data32);
        Data32 &= gSata1RegistersSave[i].Mask;
        BOOT_SCRIPT_S3_PCI_CONFIG_WRITE_MACRO(
            gBootScript, \
            gSata1RegistersSave[i].Width, \
            gSata1RegistersSave[i].Address, \
            1, \
            &Data32);
    }

    //If SATA is in AHCI or RAID Mode Save/Restore additional registers.
    gPciRootBridgeIo->Pci.Read(gPciRootBridgeIo, EfiBootScriptWidthUint8, SATA_REG(SATA_REG_MAP), 1, &Data8); // 0x90
    if ( Data8 & 0xC0 ) { // AHCI or RAID

        gPciRootBridgeIo->Pci.Read(gPciRootBridgeIo, EfiBootScriptWidthUint32, SATA_REG(SATA_REG_ABAR), 1, &(UINT32)AHCIBar); // 0x24
        AHCIBar &= 0xFFFFFFF0;
    
        gPciRootBridgeIo->Mem.Read(gPciRootBridgeIo, EfiPciIoWidthUint32, AHCIBar + 0x04, 1, &GlobalPchControl);
        BOOT_SCRIPT_S3_MEM_WRITE_MACRO(gBootScript, EfiBootScriptWidthUint32, AHCIBar + 0x04, 1, &GlobalPchControl);

        gPciRootBridgeIo->Mem.Read(gPciRootBridgeIo, EfiPciIoWidthUint32, AHCIBar + 0x0c, 1, &PortImplemented);
        BOOT_SCRIPT_S3_MEM_WRITE_MACRO(gBootScript, EfiBootScriptWidthUint32, AHCIBar + 0xc, 1, &PortImplemented);


                                                                                                                        //[EIP124245]>>
/*      for (i = 0, Offset = 0x100; i < 6 ; i++, Offset += 0x80) {
          if ( PortImplemented & (BIT00 << i) ) {
            gPciRootBridgeIo->Mem.Read(gPciRootBridgeIo, EfiPciIoWidthUint32, AHCIBar + Offset, 1, &Data32);
            BOOT_SCRIPT_S3_MEM_WRITE_MACRO(gBootScript, EfiBootScriptWidthUint32, AHCIBar + Offset, 1, &Data32);

            gPciRootBridgeIo->Mem.Read(gPciRootBridgeIo, EfiPciIoWidthUint32, AHCIBar + Offset + 0x04, 1, &Data32);
            BOOT_SCRIPT_S3_MEM_WRITE_MACRO(gBootScript, EfiBootScriptWidthUint32, AHCIBar + Offset + 0x04, 1, &Data32);

            gPciRootBridgeIo->Mem.Read(gPciRootBridgeIo, EfiPciIoWidthUint32, AHCIBar + Offset + 0x04, 1, &Data32);
            BOOT_SCRIPT_S3_MEM_WRITE_MACRO(gBootScript, EfiBootScriptWidthUint32, AHCIBar + Offset + 0x04, 1, &Data32);

            gPciRootBridgeIo->Mem.Read(gPciRootBridgeIo, EfiPciIoWidthUint32, AHCIBar + Offset + 0x08, 1, &Data32);
            BOOT_SCRIPT_S3_MEM_WRITE_MACRO(gBootScript, EfiBootScriptWidthUint32, AHCIBar + Offset + 0x08, 1, &Data32);

            gPciRootBridgeIo->Mem.Read(gPciRootBridgeIo, EfiPciIoWidthUint32, AHCIBar + Offset + 0x0c, 1, &Data32);
            BOOT_SCRIPT_S3_MEM_WRITE_MACRO(gBootScript, EfiBootScriptWidthUint32, AHCIBar + Offset + 0x0c, 1, &Data32);

            gPciRootBridgeIo->Mem.Read(gPciRootBridgeIo, EfiPciIoWidthUint32, AHCIBar + Offset + 0x18, 1, &Data32);
            Data32 &= 0xFFFFFFEE; //Make sure Clear the Start and FIS Receive Enable bit
            BOOT_SCRIPT_S3_MEM_WRITE_MACRO(gBootScript, EfiBootScriptWidthUint32, AHCIBar + Offset + 0x18, 1, &Data32);

            gPciRootBridgeIo->Mem.Read(gPciRootBridgeIo, EfiPciIoWidthUint32, AHCIBar + Offset + 0x2c, 1, &Data32);
            BOOT_SCRIPT_S3_MEM_WRITE_MACRO(gBootScript, EfiBootScriptWidthUint32, AHCIBar + Offset + 0x2c, 1, &Data32);
          }
        }*/                                                                                                             //[EIP124245]<<

        gPciRootBridgeIo->Mem.Read (gPciRootBridgeIo, EfiPciIoWidthUint32, AHCIBar, 1, &Data32);
        BOOT_SCRIPT_S3_MEM_WRITE_MACRO(gBootScript, EfiBootScriptWidthUint32, AHCIBar,1,&Data32);
    }
  } // if SATA 1 = ffffffff
                                                           //(EIP126943)>>
             //Controller in IDE Mode. Save/Restore Secondary SataController (B0:D1F:F5) Registers also.
        
  gPciRootBridgeIo->Pci.Read(
          gPciRootBridgeIo,
          EfiBootScriptWidthUint32,
          SATA2_REG(0),
          1,
          &Data32
          );
  if (Data32 != 0xFFFFFFFF) {
    for (i = 0; i < sizeof(gSata2RegistersSave)/ sizeof(BOOT_SCRIPT_SB_PCI_REG_SAVE); ++i) {
      gPciRootBridgeIo->Pci.Read(
          gPciRootBridgeIo,
          gSata2RegistersSave[i].Width,
          gSata2RegistersSave[i].Address,
          1,
          &Data32
        );
      Data32 &= gSata2RegistersSave[i].Mask;
      BOOT_SCRIPT_S3_PCI_CONFIG_WRITE_MACRO(
          gBootScript,
          gSata2RegistersSave[i].Width,
          gSata2RegistersSave[i].Address,
          1,
          &Data32
      );
    }
  }// if SATA 2 = ffffffff                                 //(EIP126943)<<
   

  if (gErrorLoggingFlag == TRUE) {
    Data8 = SW_SMI_SB_EL_S3;
    WRITE_IO8(SW_SMI_IO_ADDRESS, Data8 );
    BOOT_SCRIPT_S3_IO_WRITE_MACRO( gBootScript, \
                                   EfiBootScriptWidthUint8, \
                                   SW_SMI_IO_ADDRESS, \
                                   1, \
                                   &Data8);
  }

#if SB_SWSMI_WRITE_TO_BOOTSCRIPT
  SBSwSmiWriteToBootScript(gBootScript);
#endif

#if defined AMIUSB_SUPPORT && AMIUSB_SUPPORT == 1
  CheckDisableUsbControllers();
#endif
                                                               //(EIP127410)>>
  if (PchSeries == PchLp) {
    WRITE_PCI16_SB(SB_REG_GEN_PMCON_1, (READ_PCI16_SB(SB_REG_GEN_PMCON_1) | 0x800));
    TRACE((TRACE_ALWAYS, "SB_REG_GEN_PMCON_1= %x\n", READ_PCI16_SB(SB_REG_GEN_PMCON_1)));
  }

  Status = pBS->LocateProtocol(&gEfiAcpiSupportGuid, NULL, &As);

  // Find DSDT ACPI Table
  for (Index = 0; Index < ACPI_RSDT_TABLE_NUM; Index++) {
    Status = As->GetAcpiTable(As, Index, &Table, &Version, &Handle);
    if (EFI_ERROR(Status)) break;//no more tables left    

    if ((Table->Header.Signature == FACP_SIG) && (DsdtPtr == NULL)) {
        DsdtPtr = (ACPI_HDR*)Table->DSDT;
        TRACE((-1, "SBDxe: Found DSDT Table at 0x%08X\n", DsdtPtr));
        if (PchSeries == PchLp) {
          ULTDsdtTableUpdate (DsdtPtr);
        } else {
          DsdtTableUpdate (DsdtPtr);
        }
        break;
    }
  }                                                            //(EIP127410)<<
  
  //
  //Kill the Event
  //
  pBS->CloseEvent(Event);

}

#if defined AMIUSB_SUPPORT && AMIUSB_SUPPORT == 1
//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:   SbUsbProtocolCallback
//
// Description: This callback function is called after USB Protocol is 
//              installed.
//
// Input:       Event   - Event of callback
//              Context - Context of callback.
//
// Output:      None
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

VOID SbUsbProtocolCallback (
    IN EFI_EVENT                    Event,
    IN VOID                         *Context )
{
    EFI_STATUS    Status = EFI_SUCCESS;
    USB_SKIP_LIST SkipMassTable[] = { {1, 0, 0xff, 0, 0, 0x8},
                                      {0, 0, 0,    0, 0, 0  }
                                    };

    if (gDisableAllUsbControllers)
    {
        Status = pBS->LocateProtocol( &gEfiUsbProtocolGuid,
                                      NULL,
                                      &gUsbProtocol );
        if (EFI_ERROR(Status)) return;
        gUsbProtocol->UsbCopySkipTable(SkipMassTable, sizeof(SkipMassTable)/sizeof (USB_SKIP_LIST));
    }

    pBS->CloseEvent(Event);
}
#endif

#if SecureMod_SUPPORT
//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:   BiosLockEnableCallback
//
// Description: This callback function is called after AMI_EVENT_FLASH_WRITE_LOCK is 
//              installed.
//
// Input:       Event   - Event of callback
//              Context - Context of callback.
//
// Output:      None
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

VOID BiosLockEnableCallback (
    IN EFI_EVENT                    Event,
    IN VOID                         *Context )
{
    EFI_STATUS                        Status;
    DXE_PCH_PLATFORM_POLICY_PROTOCOL  *PchPlatformPolicy;

    Status = pBS->LocateProtocol ( &gDxePchPlatformPolicyProtocolGuid, \
                                   NULL, \
                                   &PchPlatformPolicy);
    if (!EFI_ERROR (Status)) {
      if ((gSbSetupData->BiosLock == PCH_DEVICE_ENABLE) &&
          (PchPlatformPolicy->LockDownConfig->PchBiosLockIoTrapAddress != 0)) {
        IoWrite32 (PchPlatformPolicy->LockDownConfig->PchBiosLockIoTrapAddress, PCH_BWP_SIGNATURE);
      }
    }

    pBS->CloseEvent(Event);
}
#endif

//**********************************************************************
//<AMI_PHDR_START>
//
// Procedure   : LocatePublishIdeSataAcpiTables
//
// Description : This function  will locate and publish the IDE.asl or SATA.asl 
//               depending upon the mode IDE/AHCI. 
//
// Input       :None
//    
// Output      :None
//
//<AMI_PHDR_END>
//**********************************************************************
VOID LocatePublishIdeSataAcpiTables(VOID)
{
  EFI_STATUS                    Status;
  EFI_HANDLE                    *HandleBuffer;
  UINTN                         NumberOfHandles;
  EFI_FV_FILETYPE               FileType;
  UINT32                        FvStatus;
  EFI_FV_FILE_ATTRIBUTES        Attributes;
  UINTN                         Size;
  UINTN                         k;
  EFI_FIRMWARE_VOLUME_PROTOCOL  *FwVol = NULL;
  INTN                          Instance;
  EFI_ACPI_TABLE_VERSION        Version;
  EFI_ACPI_COMMON_HEADER        *CurrentTable;
  UINTN                         AcpiTableHandle;
  ACPI_HDR                      *AcpiTable = NULL;
  ACPI_HDR                      *TableHeader;
  UINT8                         Data;
  EFI_ACPI_SUPPORT_PROTOCOL     *AcpiSupport =0;
  BOOLEAN                       AhciFlag = FALSE;

  //Locate the PcirootbridgeIoprotocol
  Status = pBS->LocateProtocol(&gEfiPciRootBridgeIoProtocolGuid, NULL, &gPciRootBridgeIo);
  ASSERT_EFI_ERROR(Status);

  //Read the Sub class code register to check for ide/Ahci mode.
  Data = READ_PCI8_SATA(R_PCH_SATA_SUB_CLASS_CODE);

  if (Data == V_PCH_SATA_SUB_CLASS_CODE_AHCI || \
      Data == V_PCH_SATA_SUB_CLASS_CODE_RAID)
    AhciFlag = TRUE;
  //
  // Locate protocol.
  // There is little chance we can't find an FV protocol
  //
  Status = pBS->LocateHandleBuffer (
                  ByProtocol,
                  &gEfiFirmwareVolumeProtocolGuid,
                  NULL,
                  &NumberOfHandles,
                  &HandleBuffer
                  );
  ASSERT_EFI_ERROR (Status);

  //
  // Looking for FV with ACPI storage file
  //
  for (k = 0; k < NumberOfHandles; k++) {
    //
    // Get the protocol on this handle
    // This should not fail because of LocateHandleBuffer
    //
    Status = pBS->HandleProtocol (
                  HandleBuffer[k],
                  &gEfiFirmwareVolumeProtocolGuid,
                  &FwVol
                  );
    ASSERT_EFI_ERROR (Status);

    //
    // See if it has the ACPI storage file
    //
    Size      = 0;
    FvStatus  = 0;
    Status = FwVol->ReadFile (
                    FwVol,
                    &IdeSataAcpiTableStorageGuid,
                    NULL,
                    &Size,
                    &FileType,
                    &Attributes,
                    &FvStatus
                    ); 

    //
    // If we found it, then we are done
    //
    if (Status == EFI_SUCCESS) {
      break;
    }
  }

  //
  // Our exit status is determined by the success of the previous operations
  // If the protocol was found, Instance already points to it.
  //
  //
  // Free any allocated buffers
  //
  pBS->FreePool (HandleBuffer);

  //
  // Sanity check that we found our data file
  //
  ASSERT (FwVol);

  //
  // By default, a table belongs in all ACPI table versions published.
  //
  Version = EFI_ACPI_TABLE_VERSION_1_0B | EFI_ACPI_TABLE_VERSION_2_0 | EFI_ACPI_TABLE_VERSION_3_0;

  //
  // Find the AcpiSupport protocol
  //
  Status = LocateSBSATAIDESupportProtocol (
            &gEfiAcpiSupportGuid,
            &AcpiSupport,
            FALSE
            );
  ASSERT_EFI_ERROR (Status);
  //
  // Read tables from the storage file.
  //
  Instance = 0;
  CurrentTable = NULL;

  while (Status == EFI_SUCCESS) {
    Status = FwVol->ReadSection (
                      FwVol,
                      &IdeSataAcpiTableStorageGuid,
                      EFI_SECTION_RAW,
                      Instance,
                      &CurrentTable,
                      &Size,
                      &FvStatus
                      );

    if (!EFI_ERROR (Status)) {
      //
      // Check the table ID to modify the table
      //
      TableHeader = (ACPI_HDR *) CurrentTable;

      if(AhciFlag) {
      //AHCI mode is Enabled
      //Locate and publish ACPItable for SATA.asl

           if (MemCmp (&TableHeader->OemTblId, "SataTabl", 8) == 0) {
             AcpiTable = (ACPI_HDR*) CurrentTable;
           }
      } else {
      //AHCI mode is Disabled
      //Locate and publish ACPItable for Ide.asl
           if (MemCmp (&TableHeader->OemTblId, "IdeTable", 8) == 0) {
             AcpiTable = (ACPI_HDR*) CurrentTable;
           }
      }
      //
      // Increment the instance
      //
      Instance++;
      CurrentTable = NULL;
    }
  }

  //
  // Update the  SSDT table in the ACPI tables.
  //
  AcpiTableHandle = 0;
  
  Status = AcpiSupport->SetAcpiTable (AcpiSupport, AcpiTable, TRUE, Version, &AcpiTableHandle);
  ASSERT_EFI_ERROR (Status);
  pBS->FreePool (AcpiTable);

  //
  // Publish all ACPI Tables
  //
  Status = AcpiSupport->PublishTables (AcpiSupport, Version);
  ASSERT_EFI_ERROR (Status);

}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:   LocateSBSATAIDESupportProtocol
//
// Description: Locate the first instance of a protocol.  If the protocol requested is an
//              FV protocol, then it will return the first FV that contains the ACPI table
//              storage file.
//
// Input:       Protocol      The protocol to find.
//              Instance      Return pointer to the first instance of the protocol
//              Type          TRUE if the desired protocol is a FV protocol
//
// Output:      EFI_SUCCESS           The function completed successfully.
//              EFI_NOT_FOUND         The protocol could not be located.
//              EFI_OUT_OF_RESOURCES  There are not enough resources to find the protocol.
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS
LocateSBSATAIDESupportProtocol (
  IN EFI_GUID                       *Protocol,
  OUT VOID                          **Instance,
  IN     BOOLEAN                    Type
  )
{
  EFI_STATUS              Status;
  EFI_HANDLE              *HandleBuffer;
  UINTN                   NumberOfHandles;
  EFI_FV_FILETYPE         FileType;
  UINT32                  FvStatus;
  EFI_FV_FILE_ATTRIBUTES  Attributes;
  UINTN                   Size;
  UINTN                   i;

  FvStatus = 0;
  //
  // Locate protocol.
  //
  Status = pBS->LocateHandleBuffer (
                  ByProtocol,
                  Protocol,
                  NULL,
                  &NumberOfHandles,
                  &HandleBuffer
                  );
  if (EFI_ERROR (Status)) {
    //
    // Defined errors at this time are not found and out of resources.
    //
    return Status;
  }
  //
  // Looking for FV with ACPI storage file
  //
  for (i = 0; i < NumberOfHandles; i++) {
    //
    // Get the protocol on this handle
    // This should not fail because of LocateHandleBuffer
    //
    Status = pBS->HandleProtocol (
                    HandleBuffer[i],
                    Protocol,
                    Instance
                    );
    ASSERT (!EFI_ERROR (Status));

    if (!Type) {
      //
      // Not looking for the FV protocol, so find the first instance of the
      // protocol.  There should not be any errors because our handle buffer
      // should always contain at least one or LocateHandleBuffer would have
      // returned not found.
      //
      break;
    }

    //
    // See if it has the ACPI storage file
    //
    Status = ((EFI_FIRMWARE_VOLUME_PROTOCOL *) (*Instance))->ReadFile (
                                                              *Instance,
                                                              &IdeSataAcpiTableStorageGuid,
                                                              NULL,
                                                              &Size,
                                                              &FileType,
                                                              &Attributes,
                                                              &FvStatus
                                                              );

    //
    // If we found it, then we are done
    //
    if (Status == EFI_SUCCESS) {
      break;
    }
  }

  //
  // Our exit status is determined by the success of the previous operations
  // If the protocol was found, Instance already points to it.
  //

  //
  // Free any allocated buffers
  //
  pBS->FreePool (HandleBuffer);

  return Status;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:   InitSbRegsBeforeLagecyBoot
//
// Description: This function can initialize any SB registers before legacy
//              OS booting.
//
// Input:       Event   - Event of callback
//              Context - Context of callback.
//
// Output:      None
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

VOID InitSbRegsBeforeLagecyBoot (
    IN EFI_EVENT        Event,
    IN VOID             *Context )
{
    pBS->CloseEvent(Event);
}

#if defined OEM_USB_PER_PORT_DISABLE_SUPPORT && OEM_USB_PER_PORT_DISABLE_SUPPORT == 1
//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:   DisableRmhDownPort
//
// Description:             
//
// Input:       EFI_USB_IO_PROTOCOL - *UsbIo
//              UINT8               - Port
//
// Output:      EFI_STATUS            Status
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS  DisableRmhDownPort (
    IN EFI_USB_IO_PROTOCOL      *UsbIo,
    IN UINT8                    Port
)
{
    EFI_STATUS  Status;
    EFI_USB_DEVICE_REQUEST DevReq;
    UINT32 Timeout;
    UINT32 UsbStatus;
    
    DevReq.RequestType = 0x23;
    DevReq.Request = 0x01;
    DevReq.Value = 0x1;
    DevReq.Index = Port;
    DevReq.Length = 0;
    Timeout = 3000;
    Status = UsbIo->UsbControlTransfer(UsbIo, &DevReq, 
                            EfiUsbNoData, Timeout, NULL, 0, &UsbStatus);
  
    return Status;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:   USBPrePortDisableCallback
//
// Description: This function can disable USB preport before OS booting.             
//
// Input:       Event   - Event of callback
//              Context - Context of callback.
//
// Output:      None
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID USBPrePortDisableCallback (
    IN EFI_EVENT    Event,
    IN VOID *Context
)
{
    EFI_STATUS                  Status;
    EFI_HANDLE                  *HandleBuffer;
    EFI_GUID                    EfiUsbIoProtocolGuid = EFI_USB_IO_PROTOCOL_GUID;
    UINTN                       HandleCount = 0;
    PCH_SERIES                  PchSeries = GetPchSeries();
    EFI_USB_IO_PROTOCOL         *UsbIo;
    EFI_USB_IO_PROTOCOL         *Ehci1RmhUsbIo = NULL;
    EFI_USB_IO_PROTOCOL         *Ehci2RmhUsbIo = NULL;
    EFI_USB_DEVICE_DESCRIPTOR   DevDesc   = {0};
    UINT32                      Index;
    UINT8                       EHCIPort1 = 0;
    UINT8                       EHCIPort2 = 0;
    UINT8                       XhciPortDisableFlage[21];
    UINT32                      XhciUsb2Pdo = 0;
    UINT32                      XhciUsb3Pdo = 0;
    UINT32                      XhciIndex;
    UINT16                      RegData16;
    UINT32                      XhciUsb2InternalPortNumberLookUpTable[] = {0,1,2,3,8,9,12,13,4,5,6,7,10,11,12,13};
    static BOOLEAN              USBPrePortDisableDone = FALSE;

    ///
    ///  Table: USB2 Pins Mapping between XHCI/EHCI Port
    ///   -------------------------------------------
    ///  | USB2 Pin     | EHCI Port      | XHCI Port |
    ///  |--------------+----------------+-----------|
    ///  | USB[P,N][0]  | EHCI 1 Port 0  | Port 0    |
    ///  | USB[P,N][1]  | EHCI 1 Port 1  | Port 1    |
    ///  | USB[P,N][2]  | EHCI 1 Port 2  | Port 2    |
    ///  | USB[P,N][3]  | EHCI 1 Port 3  | Port 3    |
    ///  | USB[P,N][4]  | EHCI 1 Port 4  | Port 8    |
    ///  | USB[P,N][5]  | EHCI 1 Port 5  | Port 9    |
    ///  | USB[P,N][6]  | EHCI 1 Port 6  | Port 12   |
    ///  | USB[P,N][7]  | EHCI 1 Port 7  | Port 13   |
    ///  | USB[P,N][8]  | EHCI 2 Port 8  | Port 4    |
    ///  | USB[P,N][9]  | EHCI 2 Port 9  | Port 5    |
    ///  | USB[P,N][10] | EHCI 2 Port 10 | Port 6    |
    ///  | USB[P,N][11] | EHCI 2 Port 11 | Port 7    |
    ///  | USB[P,N][12] | EHCI 2 Port 12 | Port 10   |
    ///  | USB[P,N][13] | EHCI 2 Port 13 | Port 11   |
    ///   -------------------------------------------
    ///

    //Make sure the processing is performed only once. 
    if (USBPrePortDisableDone){
        pBS->CloseEvent(Event);
        return;
    }

    TRACE((-1, "OEM_USB_PER_PORT_DISABLE_SUPPORT - Start\n"));

    // Locate handle buffer for USB Io Protocol
    Status = pBS->LocateHandleBuffer( ByProtocol,
                                      &EfiUsbIoProtocolGuid,
                                      NULL,
                                      &HandleCount,
                                      &HandleBuffer);
    if (EFI_ERROR(Status)){
        TRACE((-1, "ERROR: Cannot Locate handle buffer for USB Io Protocol !!!\n"));
    } else {
        TRACE((-1, "USB Io Protocol user are %d Handles!!!\n", HandleCount));
    }

    // Initial Xhci Port Disable Flage
    // for PCH-LP
    // Index: 00 01 02 03 04 05 06 07 08 09 10 11 12 13 14 15 16 17 18 19 20
    // SS/HS: HS HS HS HS HS HS HS HS HS xx SS SS SS SS
    // for PCH-H
    // SS/HS: HS HS HS HS HS HS HS HS HS HS HS HS HS HS xx SS SS SS SS SS SS
    for (Index=0;Index<21;Index++) XhciPortDisableFlage[Index] = 0;

    for ( Index=0; Index < HandleCount; Index++ ) {
        pBS->HandleProtocol(HandleBuffer[Index], &gEfiUsbIoProtocolGuid, &UsbIo);
        Status = UsbIo->UsbGetDeviceDescriptor(UsbIo, &DevDesc);
        if (EFI_ERROR(Status)) {
            continue;
        }
        if (DevDesc.IdVendor != 0x8087) {
            continue;
        }
        switch (DevDesc.IdProduct) {
            case 0x8000:
                Ehci1RmhUsbIo = UsbIo;
                break;
            case 0x8008:
                Ehci2RmhUsbIo = UsbIo;
                break;
            default:
                break;
        } // switch
    } // for loop

// Intel_RC >>>
    if (gSbSetupData->PchUsbPerPortCtl == PCH_DEVICE_ENABLE){
        ///
        /// Open the Per-Port Disable Control Override
        ///
        
        RegData16 = IoRead16 ((UINTN) ((UINT64) (PM_BASE_ADDRESS + R_PCH_UPRWC)));
        RegData16 |= B_PCH_UPRWC_WR_EN;
        IoWrite16 ((UINTN) ((UINT64) (PM_BASE_ADDRESS + R_PCH_UPRWC)), RegData16);

        ///
        /// To support RapidStart resume from G3 state, all resume well registers need to be saved
        /// into S3 Script table.
        ///
        BOOT_SCRIPT_S3_IO_WRITE_MACRO ( gBootScript, 
                                        EfiBootScriptWidthUint16, 
                                        (PM_BASE_ADDRESS + R_PCH_UPRWC),
                                        1,
                                        &RegData16);

        for (Index = 0; Index < GetPchUsbMaxPhysicalPortNum (); Index++) {
            if ((Index < 8) && (gSbSetupData->PchUsb20[0] == PCH_DEVICE_ENABLE) && (gSbSetupData->PchUsb30Mode != 1)) {
                ///
                /// EHCI1 PDO for Port 0 to 7
                ///
                if (gSbSetupData->PchUsbPort[Index] == PCH_DEVICE_DISABLE) {
                    EHCIPort1 |= B_PCH_EHCI_PDO_DIS_PORT0 << Index;
                    if (Ehci1RmhUsbIo != NULL) {
                        DisableRmhDownPort(Ehci1RmhUsbIo, (Index + 1));
                    }
                } else {
                    EHCIPort1 &= ~(B_PCH_EHCI_PDO_DIS_PORT0 << Index);
                }
            } // EHCI1 PDO
            if (PchSeries == PchH) { 
                if ((Index >= 8) && (Index < 14) && (gSbSetupData->PchUsb20[1] == PCH_DEVICE_ENABLE) && (gSbSetupData->PchUsb30Mode != 1)) {
                    ///
                    /// EHCI2 PDO for Port 8 to 13
                    ///
                    if (gSbSetupData->PchUsbPort[Index] == PCH_DEVICE_DISABLE) {
                        EHCIPort2 |= B_PCH_EHCI_PDO_DIS_PORT0 << (Index - 8);
                        if (Ehci1RmhUsbIo != NULL) {
                            DisableRmhDownPort(Ehci2RmhUsbIo, (Index - 7));
                        }
                    } else {
                        EHCIPort2 &= ~(B_PCH_EHCI_PDO_DIS_PORT0 << (Index - 8));
                    }
                } // EHCI2 PDO
            } // PchSeries == PchH
        } // for loop
        
        if((gSbSetupData->PchUsb20[0] == PCH_DEVICE_ENABLE) && (gSbSetupData->PchUsb30Mode != 1)){
            ///
            /// To support RapidStart resume from G3 state, all resume well registers need to be saved
            /// into S3 Script table.
            ///
            TRACE((-1, "Write back Ehci1 PDO value: %x to PDO register\n", EHCIPort1));
            WRITE_PCI8 (0, 29, 0, R_PCH_EHCI_PDO, EHCIPort1);
            BOOT_SCRIPT_S3_PCI_CONFIG_WRITE_MACRO( gBootScript,
                                                   EfiBootScriptWidthUint32,
                                                   SB_PCI_CFG_ADDRESS(0, 29, 0, R_PCH_EHCI_PDO),
                                                   1,
                                                   &EHCIPort1);
            
            if (PchSeries == PchH && (gSbSetupData->PchUsb20[1] == PCH_DEVICE_ENABLE)) { 
                TRACE((-1, "Write back Ehci2 PDO value: %x to PDO register\n", EHCIPort2));
                WRITE_PCI8 (0, 26, 0, R_PCH_EHCI_PDO, EHCIPort2);
                    BOOT_SCRIPT_S3_PCI_CONFIG_WRITE_MACRO( gBootScript,
                                                           EfiBootScriptWidthUint32,
                                                           SB_PCI_CFG_ADDRESS(0, 26, 0, R_PCH_EHCI_PDO),
                                                           1,
                                                           &EHCIPort2);
            } // PchSeries == PchH && Echi2 enable
        } // Echi1 enable
        
        if (gSbSetupData->PchUsb30Mode != 0){
            for (Index = 0; Index < GetPchUsbMaxPhysicalPortNum (); Index++) {
                XhciIndex = Index;
                if (PchSeries == PchH) {
                    ///
                    /// Translate physical pins to internal ports numbering
                    ///
                    XhciIndex = XhciUsb2InternalPortNumberLookUpTable[Index];
                }
                if (gSbSetupData->PchUsbPort[Index] == PCH_DEVICE_DISABLE) {
                    XhciUsb2Pdo |= (UINT32) (B_PCH_XHCI_USB2PDO_DIS_PORT0 << XhciIndex);
                    XhciPortDisableFlage[XhciIndex] |= 1;
                } else {
                    XhciUsb2Pdo &= (UINT32)~(B_PCH_XHCI_USB2PDO_DIS_PORT0 << XhciIndex);
                } // XCHI PDO
            } // for loop
            
            ///
            /// XHCI PDO for SS
            ///
            for (Index = 0; Index < GetPchXhciMaxUsb3PortNum (); Index++) {
                if (gSbSetupData->PchUsb30Port[Index] == PCH_DEVICE_DISABLE) {
                    XhciUsb3Pdo |= (UINT32) (B_PCH_XHCI_USB3PDO_DIS_PORT0 << Index);
                    if (PchSeries == PchH){
                        XhciPortDisableFlage[Index + 15] |= 1;
                    } else {
                        XhciPortDisableFlage[Index + 10] |= 1;
                    } // PCH sku
                } else {
                    XhciUsb3Pdo &= (UINT32)~(B_PCH_XHCI_USB3PDO_DIS_PORT0 << Index);
                } // XHCI PDO
            } // for loop
            ///
            /// USB2PDO and USB3PDO are Write-Once registers and bits in them are in the SUS Well.
            ///
            TRACE((-1, "Write back Xhci HS PDO value: %x to HS PDO register\n", XhciUsb2Pdo));
            WRITE_PCI32(0, 20, 0, R_PCH_XHCI_USB2PDO, XhciUsb2Pdo);
            BOOT_SCRIPT_S3_PCI_CONFIG_WRITE_MACRO( gBootScript,
                                                   EfiBootScriptWidthUint32,
                                                   SB_PCI_CFG_ADDRESS(0, 20, 0, R_PCH_XHCI_USB2PDO),
                                                   1,
                                                   &XhciUsb2Pdo);
            
            TRACE((-1, "Write back Xhci SS PDO value: %x to SS PDO register\n", XhciUsb3Pdo));
            WRITE_PCI32(0, 20, 0, R_PCH_XHCI_USB3PDO, XhciUsb3Pdo);
            BOOT_SCRIPT_S3_PCI_CONFIG_WRITE_MACRO( gBootScript,
                                                   EfiBootScriptWidthUint32,
                                                   SB_PCI_CFG_ADDRESS(0, 20, 0, R_PCH_XHCI_USB3PDO),
                                                   1,
                                                   &XhciUsb3Pdo);
            
            ///
            /// Close the Per-Port Disable Control Override
            ///
            
            RegData16 &= (~B_PCH_UPRWC_WR_EN);
            IoWrite16 ((UINTN) ((UINT64) (PM_BASE_ADDRESS + R_PCH_UPRWC)), RegData16);
            
            ///
            /// To support RapidStart resume from G3 state, all resume well registers need to be saved
            /// into S3 Script table.
            ///
            
            BOOT_SCRIPT_S3_IO_WRITE_MACRO ( gBootScript, 
                                            EfiBootScriptWidthUint16, 
                                            (PM_BASE_ADDRESS + R_PCH_UPRWC),
                                            1,
                                            &RegData16);
        } // gSbSetupData->PchUsb30Mode != 0
    } // gSbSetupData->PchUsbPerPortCtl == PCH_DEVICE_ENABLE
// Intel_RC <<<
// Disable usb port under Xhci controller >>>
{
    UINT8                     counter;
    UINT32                    RegVal;
    UINT64                    XhciBar;
    
    // Read back Xhci MMIO addrss
    if ((MmPciRead32(XHCI_BUS, XHCI_DEV, XHCI_FUN, R_PCH_XHCI_MEM_BASE) & 0x6) == 0x4){
        XhciBar = (((UINT64) MmPciRead32(XHCI_BUS, XHCI_DEV, XHCI_FUN, R_PCH_XHCI_MEM_BASE + 4) << 32) | 
                   ((UINT64) MmPciRead32(XHCI_BUS, XHCI_DEV, XHCI_FUN, R_PCH_XHCI_MEM_BASE) & (~0x0F)));
    } else {
        XhciBar = MmPciRead32(XHCI_BUS, XHCI_DEV, XHCI_FUN, R_PCH_XHCI_MEM_BASE) & (~0x0F);
    }
    TRACE((-1, "Xhci Bar = %x\n", XhciBar));

    // Disable Xhci port which are disconnected
    for(Index=0;Index<21;Index++){
        if (XhciPortDisableFlage[Index] != 0){
            TRACE((-1, "Disable port%d under Xhci controller(start number:1)\n", (Index + 1)));
            if (PchSeries ==PchLp){
                // for PCH-LP
                // Index: 00 01 02 03 04 05 06 07 08 09 10 11 12 13 14 15 16 17 18 19 20
                // SS/HS: HS HS HS HS HS HS HS HS HS xx SS SS SS SS 
                TRACE((-1, "this PCH is ULT sku\n"));
                if (Index > 13) break;
                
                if (Index < 9){
                    //HS port
                    RegVal = MmioRead32(XhciBar + R_PCH_XHCI_PORTSC01USB2 + 0x10 * Index);
                    if (RegVal & B_PCH_XHCI_PORTSCXUSB2_PED){
                        RegVal = (B_PCH_XHCI_PORTSCXUSB2_PED | B_PCH_XHCI_PORTSCXUSB2_PP);
                        MmioWrite32((XhciBar + R_PCH_XHCI_PORTSC01USB2 + 0x10 * Index), RegVal);
                        for(counter=0;counter<200;counter++){
                            RegVal = MmioRead32(XhciBar + R_PCH_XHCI_PORTSC01USB2 + 0x10 * Index);
                            if(!(RegVal & B_PCH_XHCI_PORTSCXUSB2_PED)) break;
                            pBS->Stall(100);
                        } // for loop
                    } // PED bit is enable
                } else {
                    //SS port
                    RegVal = MmioRead32(XhciBar + R_PCH_LP_XHCI_PORTSC1USB3 + 0x10 * Index);
                    if (RegVal & B_PCH_XHCI_PORTSCXUSB3_PED){
                        RegVal = (B_PCH_XHCI_PORTSCXUSB3_PR | B_PCH_XHCI_PORTSCXUSB3_PP);
                        MmioWrite32((XhciBar + R_PCH_LP_XHCI_PORTSC1USB3 + 0x10 * Index), RegVal);
                        for(counter=0;counter<3000;counter++){
                            RegVal = MmioRead32(XhciBar + R_PCH_LP_XHCI_PORTSC1USB3 + 0x10 * Index);
                            if(RegVal & B_PCH_XHCI_PORTSCXUSB3_PRC) break;
                            pBS->Stall(100);
                        } // for loop
                        
                        // Clear Warm Port Reset Change and Port Reset Change bits
                        //RegVal = (B_PCH_XHCI_PORTSCXUSB3_WRC | B_PCH_XHCI_PORTSCXUSB3_PRC | B_PCH_XHCI_PORTSCXUSB3_PP);
                        //MmioWrite32((XhciBar + R_PCH_LP_XHCI_PORTSC1USB3 + 0x10 * Index), RegVal);
                    } // PED bit is enable
                }// SS/HS port
            } else {
                // for PCH-H
                // Index: 00 01 02 03 04 05 06 07 08 09 10 11 12 13 14 15 16 17 18 19 20
                // SS/HS: HS HS HS HS HS HS HS HS HS HS HS HS HS HS xx SS SS SS SS SS SS
                TRACE((-1, "this PCH is MB/DT sku\n"));
                if (Index < 14){
                    //HS port
                    RegVal = MmioRead32(XhciBar + R_PCH_XHCI_PORTSC01USB2 + 0x10 * Index);
                    if (RegVal & B_PCH_XHCI_PORTSCXUSB2_PED){
                        RegVal = (B_PCH_XHCI_PORTSCXUSB2_PED | B_PCH_XHCI_PORTSCXUSB2_PP);
                        MmioWrite32((XhciBar + R_PCH_XHCI_PORTSC01USB2 + 0x10 * Index), RegVal);
                        for(counter=0;counter<200;counter++){
                            RegVal = MmioRead32(XhciBar + R_PCH_XHCI_PORTSC01USB2 + 0x10 * Index);
                            if(!(RegVal & B_PCH_XHCI_PORTSCXUSB2_PED)) break;
                            pBS->Stall(100);
                        } // for loop
                    } // PED bit is enable
                } else {
                    //SS port
                    RegVal = MmioRead32(XhciBar + R_PCH_H_XHCI_PORTSC1USB3 + 0x10 * Index);
                    if (RegVal & B_PCH_XHCI_PORTSCXUSB3_PED){
                        RegVal = (B_PCH_XHCI_PORTSCXUSB3_PR | B_PCH_XHCI_PORTSCXUSB3_PP);
                        MmioWrite32((XhciBar + R_PCH_H_XHCI_PORTSC1USB3 + 0x10 * Index), RegVal);
                        for(counter=0;counter<3000;counter++){
                            RegVal = MmioRead32(XhciBar + R_PCH_H_XHCI_PORTSC1USB3 + 0x10 * Index);
                            if(RegVal & B_PCH_XHCI_PORTSCXUSB3_PRC) break;
                            pBS->Stall(100);
                        } // for loop
                        
                        // Clear Warm Port Reset Change and Port Reset Change bits
                        //RegVal = (B_PCH_XHCI_PORTSCXUSB3_WRC | B_PCH_XHCI_PORTSCXUSB3_PRC | B_PCH_XHCI_PORTSCXUSB3_PP);
                        //MmioWrite32((XhciBar + R_PCH_H_XHCI_PORTSC1USB3 + 0x10 * Index), RegVal);
                    } // PED bit is enable
                } // SS/HS port
            } // PCH sku
        } // XhciPortDisableFlage[counter] != 0
    } // for loop

    pBS->FreePool(HandleBuffer);
}
// Disable usb port under Xhci controller <<<

    USBPrePortDisableDone = TRUE;
    TRACE((-1, "OEM_USB_PER_PORT_DISABLE_SUPPORT - End\n"));
    pBS->CloseEvent(Event);
}
#endif

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:   SbSetupNvramUpdatedCallback
//
// Description: This callback function is called after Setup NVRAM variable
//              being updated.
//
// Input:       Event   - Event of callback
//              Context - Context of callback.
//
// Output:      None
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

VOID SbSetupNvramUpdatedCallback (
    IN EFI_EVENT                    Event,
    IN VOID                         *Context )
{
    EFI_STATUS              Status;
    SB_SETUP_DATA           *SetupData = NULL;
    UINTN                   VariableSize = sizeof(SB_SETUP_DATA);
    
    Status = pBS->AllocatePool( EfiBootServicesData, \
                                VariableSize, \
                                &SetupData );
    ASSERT_EFI_ERROR(Status);

    GetSbSetupData( pRS, SetupData, FALSE );

    // Free memory used for setup data
    pBS->FreePool( SetupData );

    pBS->CloseEvent(Event);
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:   SbExitPmAuthProtocolCallback
//
// Description: This callback function is called after Setup NVRAM variable
//              being updated.
//
// Input:       Event   - Event of callback
//              Context - Context of callback.
//
// Output:      None
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

VOID SbExitPmAuthProtocolCallback (
  IN EFI_EVENT                    Event,
  IN VOID                         *Context )
{
  EFI_STATUS  Status;
                                        // [EIP120623]>
  UINT8       Data8;
                                        // <[EIP120623]
// [ EIP357393 ]->>>                                       
//  UINT32      Data32;
//  UINT32      i;
//  UINT32      SpiRegister[] = {
//                                R_PCH_SPI_SSFS,
//                                R_PCH_SPI_PREOP,
//                                R_PCH_SPI_OPMENU,
//                                R_PCH_SPI_OPMENU + 4,
//                                R_PCH_SPI_VSCC1,
//                                R_PCH_SPI_VSCC0
//                              };
// [ EIP357393 ]-<<<
  VOID        *ProtocolPointer;
  UINT32      SmiEn;
  UINT16      Pm1Sts;
  PCH_SERIES  PchSeries = GetPchSeries();

  //
  // Check whether this is real ExitPmAuth notification, or just a SignalEvent
  //
  Status = pBS->LocateProtocol (&gExitPmAuthProtocolGuid, NULL, &ProtocolPointer);
  if (EFI_ERROR (Status)) return;

  //
  // Save SPI Registers for S3 resume usage
  //
// [ EIP357393 ]->>>
//  for (i = 0; i < sizeof (SpiRegister) / sizeof (UINT32); i++) {
//    Data32 = READ_MEM32_RCRB (SpiRegister[i]);
//    BOOT_SCRIPT_S3_MEM_WRITE_MACRO( gBootScript, \
//                                    EfiBootScriptWidthUint32, \
//                                    SB_RCRB_BASE_ADDRESS + SpiRegister[i], \
//                                    1, \
//                                    &Data32
//                                  );
//  }
// [ EIP357393 ]-<<<

                                        // [EIP120623]>
  Data8 = IoRead8 (PM_BASE_ADDRESS + ACPI_IOREG_PM1_CNTL);   //0x04
  Data8 |= B_PCH_ACPI_PM1_CNT_SCI_EN;

  BOOT_SCRIPT_S3_IO_WRITE_MACRO ( \
    gBootScript, \
    EfiBootScriptWidthUint8, \
    PM_BASE_ADDRESS + ACPI_IOREG_PM1_CNTL, \
    1, \
    &Data8);
                                        // <[EIP120623]

  SmiEn = IoRead32 (PM_BASE_ADDRESS + ACPI_IOREG_SMI_EN);   //0x30        
  SmiEn &= ~B_PCH_SMI_EN_SWSMI_TMR;
                                        // [EIP76432]>>
#if defined EMUL6064_SUPPORT && EMUL6064_SUPPORT == 1
  SmiEn &= ~B_PCH_SMI_EN_LEGACY_USB;
#endif
                                        // <<[EIP76432]
  BOOT_SCRIPT_S3_IO_WRITE_MACRO ( \
    gBootScript, \
    EfiBootScriptWidthUint32, \
    PM_BASE_ADDRESS + ACPI_IOREG_SMI_EN, \
    1, \
    &SmiEn);
                                        // [EIP92011] >>
  if (PchSeries != PchLp) {
    SmiEn = IoRead16 (PM_BASE_ADDRESS + ACPI_IOREG_ALTGP_SMI_EN);   // Alternate GPI SMI Enable Reg. 
    //0x38
    BOOT_SCRIPT_S3_IO_WRITE_MACRO ( \
      gBootScript, \
      EfiBootScriptWidthUint16, \
      PM_BASE_ADDRESS + ACPI_IOREG_ALTGP_SMI_EN, \
      1, \
      &SmiEn);
  }else{
    SmiEn = IoRead16 (GPIO_BASE_ADDRESS + GP_IOREG_ALTGP_SMI_EN);   // Alternate GPI SMI Enable Reg.
    //0x54
    BOOT_SCRIPT_S3_IO_WRITE_MACRO ( \
      gBootScript, \
      EfiBootScriptWidthUint16, \
      GPIO_BASE_ADDRESS + GP_IOREG_ALTGP_SMI_EN, \
      1, \
      &SmiEn);    
  }
                                        //[EIP92011] <<

  // Clear bus master status bit on S3 resume
  Pm1Sts = B_PCH_ACPI_PM1_STS_BM;
  //0x00
  BOOT_SCRIPT_S3_IO_WRITE_MACRO ( \
    gBootScript, \
    EfiBootScriptWidthUint16, \
    PM_BASE_ADDRESS + ACPI_IOREG_PM1_STS, \
    1, \
    &Pm1Sts);
/*  // [ EIP357393 ]->>>
  // EIP167087 >>>
  TRACE((-1, "Programming SPI Protected Range registers"));
  Status = SbFlashProtectedRange();
  TRACE((-1, " %r !!!\n", Status));
  ASSERT_EFI_ERROR(Status);
  
  // Write SPI Protected Range registers to S3 script
  for(i=0;i<5;i++){
    Data32 = READ_MEM32_RCRB(SPI_BASE_ADDRESS + (R_SB_RCRB_SPI_PR0 + (i * 4)));
    TRACE((-1, "PR%d value @ %x: %x\n", i, (SB_RCBA + SPI_BASE_ADDRESS + (R_SB_RCRB_SPI_PR0 + (i * 4))), Data32));
    BOOT_SCRIPT_S3_MEM_WRITE_MACRO( gBootScript, \
                                    EfiBootScriptWidthUint32, \
                                    SB_RCBA + SPI_BASE_ADDRESS + (R_SB_RCRB_SPI_PR0 + (i * 4)), \
                                    1, \
                                    &Data32
                                   );
  }
  // EIP167087 <<<
*/  // [ EIP357393 ]-<<<

  pBS->CloseEvent(Event);
}


// [ EIP357393 ]+>>>
//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:   SBS3SaveSpi
//
// Description: Restore SPI register for S3 resume
//
// Input:       NoneE
//
// Output:      None
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

VOID SBS3SaveSpi(VOID)
{
  EFI_STATUS  Status;
  UINT32      Data32;
  UINT32      i;
  UINT32      SpiRegister[] = {
                                R_PCH_SPI_SSFS,
                                R_PCH_SPI_PREOP,
                                R_PCH_SPI_OPMENU,
                                R_PCH_SPI_OPMENU + 4,
                                R_PCH_SPI_VSCC1,
                                R_PCH_SPI_VSCC0
                              };

  //
  // Save SPI Registers for S3 resume usage
  //
  for (i = 0; i < sizeof (SpiRegister) / sizeof (UINT32); i++) {
    Data32 = READ_MEM32_RCRB (SpiRegister[i]);
    BOOT_SCRIPT_S3_MEM_WRITE_MACRO( gBootScript, \
                                    EfiBootScriptWidthUint32, \
                                    SB_RCRB_BASE_ADDRESS + SpiRegister[i], \
                                    1, \
                                    &Data32
                                  );
  }

  // EIP167087 >>>
  TRACE((-1, "Programming SPI Protected Range registers"));
  Status = SbFlashProtectedRange();
  TRACE((-1, " %r !!!\n", Status));
  ASSERT_EFI_ERROR(Status);
  
  // Write SPI Protected Range registers to S3 script
  for(i=0;i<5;i++){
    Data32 = READ_MEM32_RCRB(SPI_BASE_ADDRESS + (R_SB_RCRB_SPI_PR0 + (i * 4)));
    TRACE((-1, "PR%d value @ %x: %x\n", i, (SB_RCBA + SPI_BASE_ADDRESS + (R_SB_RCRB_SPI_PR0 + (i * 4))), Data32));
    BOOT_SCRIPT_S3_MEM_WRITE_MACRO( gBootScript, \
                                    EfiBootScriptWidthUint32, \
                                    SB_RCBA + SPI_BASE_ADDRESS + (R_SB_RCRB_SPI_PR0 + (i * 4)), \
                                    1, \
                                    &Data32
                                   );
  }
  // EIP167087 <<<
}
// [ EIP357393 ]+<<<


//----------------------------------------------------------------------------
// USUALLY NO PORTING REQUIRED FOR THE FOLLOWING ROUTINES
//----------------------------------------------------------------------------

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:   ClearWarmResetFlag
//
// Description: This function resets warm reset variable.
//
// Input:       None
//
// Output:      None
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

VOID ClearWarmResetFlag (VOID)
{
    EFI_STATUS          Status;
    EFI_GUID            SbWarmResetGuid = SB_WARM_RESET_GUID;
    CHAR16              SbWarmResetVar[] = SB_WARM_RESET_VARIABLE;
    UINT32              SbWarmResetFlag = 0;
    UINT32              Attributes = 0;
    UINTN               VarSize = sizeof(SbWarmResetFlag);
    static EFI_GUID     guidHob = HOB_LIST_GUID;
    EFI_HOB_HANDOFF_INFO_TABLE *pHit;

    Status = pRS->GetVariable( SbWarmResetVar, \
                               &SbWarmResetGuid, \
                               &Attributes, \
                               &VarSize, \
                               &SbWarmResetFlag );
    if ((!EFI_ERROR(Status)) && (SbWarmResetFlag == SB_WARM_RESET_TAG)) {
        SbWarmResetFlag ^= 0xffffffff;
        Status = pRS->SetVariable( SbWarmResetVar, \
                                   &SbWarmResetGuid, \
                                   Attributes, \
                                   0, \
                                   &SbWarmResetFlag );

        //Get Boot Mode
        pHit = GetEfiConfigurationTable(pST, &guidHob);
        if (pHit && (pHit->BootMode == BOOT_WITH_FULL_CONFIGURATION)) {
            // Update Boot mode for ME.
            pHit->BootMode = BOOT_ASSUMING_NO_CONFIGURATION_CHANGES;
        }    
    }
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:   ReportSBDxeError
//
// Description: This function reports DXE_SB_ERROR code to system during SB
//              DXE initialzation if needed.
//
// Input:       Status - EFI status.
//
// Output:      None
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

VOID ReportSBDxeError (
    IN EFI_STATUS       Status )
{
    if (Status != EFI_SUCCESS) {
        // Report Error code
        ERROR_CODE (DXE_SB_ERROR, EFI_ERROR_MAJOR);
        ASSERT_EFI_ERROR(Status);
    }
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:   WatchdogHandler
//
// Description: This function is called when the watchdog timer event is 
//              signalled.  It calls the registered handler and then
//              resets the system
//
// Inout:       Event   - Watchdog event
//              Context - Context pointer
//
// Output:      None
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

VOID EFIAPI WatchdogHandler (
    IN EFI_EVENT            Event,
    IN VOID                 *Context )
{
    // Call the registered handler if there is one
    if (mWatchdogNotifyFunction != NULL) {
        mWatchdogNotifyFunction (mWatchdogPeriod);
    }

    // Reset the system
    pRS->ResetSystem( EfiResetCold, EFI_TIMEOUT, 0, NULL );
}


//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:   RegisterHandler
//
// Description: This function registers a handler that is called when the
//              Timer event has been signalled
//
// Input:       *This          - Pointer to the instance of the Architectural
//                               Protocol
//              NotifyFunction - The function to call when the interrupt fires
//
// Output:      EFI_STATUS
//                  EFI_SUCCESS           - When new handle is registered
//                  EFI_ALREADY_STARTED   - If notify function is already
//                                          defined
//                  EFI_INVALID_PARAMETER - If notify function is NULL
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS EFIAPI RegisterHandler (
    IN EFI_WATCHDOG_TIMER_ARCH_PROTOCOL  *This,
    IN EFI_WATCHDOG_TIMER_NOTIFY         NotifyFunction )
{
    // Only register the handler if it is still NULL
    if (NotifyFunction && mWatchdogNotifyFunction)
        return EFI_ALREADY_STARTED;
    if (!NotifyFunction && !mWatchdogNotifyFunction)
        return EFI_INVALID_PARAMETER;

    mWatchdogNotifyFunction = NotifyFunction;

    return EFI_SUCCESS;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:   WatchdogSetTimerPeriod
//
// Description: This function sets the timer period before the watchdog goes
//              off every TimerPeriod number of 100ns intervals, if the 
//              period is set to 0 the timer event is cancelled
//
// Input:       *This       - Pointer to the instance of the Architectural
//                            Protocol
//              TimerPeriod - The number of 100ns intervals to which the
//                            watchdog will be programmed.
//
// Output:      EFI_STATUS
//                  EFI_SUCCESS           - The event has been set to be
//                                          signaled at the requested time.
//                  EFI_INVALID_PARAMETER - WatchdogEvent or TimerDelayType
//                                          is not valid.
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS EFIAPI WatchdogSetTimerPeriod (
    IN EFI_WATCHDOG_TIMER_ARCH_PROTOCOL  *This,
    IN UINT64                            TimerPeriod )
{
    EFI_TIMER_DELAY     TimerDelayType;

    // Store new timer length
    mWatchdogPeriod = TimerPeriod;

    // Cancel timer event if Timer Period is 0
    TimerDelayType = (TimerPeriod) ? TimerRelative : TimerCancel;

    // Set the timer for the event
    return pBS->SetTimer( mWatchdogEvent, TimerDelayType, mWatchdogPeriod );
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:   WatchdogGetTimerPeriod
//
// Description: This function returns the current watchdog timer period
//
// Input:       *This        - Pointer to the instance of the Architectural
//                             Protocol
//              *TimerPeriod - Pointer to a memory location to load the
//                             current Timer period into
//
// Output:      *TimerPeriod - Current Timer Period if function returns
//                             EFI_SUCCESS
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS EFIAPI WatchdogGetTimerPeriod (
  IN EFI_WATCHDOG_TIMER_ARCH_PROTOCOL  *This,
  IN UINT64                            *TimerPeriod )
{
    // return the current Watchdog period
    *TimerPeriod = mWatchdogPeriod;

    return EFI_SUCCESS;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:   WatchdogInit
//
// Description: This function installs the the Watchdog Timer protocol on its
//              handle, and initializes the Watchdog timer.
//
// Input:       ImageHandle - ImageHandle of the loaded driver
//              SystemTable - Pointer to the System Table
//
// Output:      EFI_STATUS
//                  EFI_SUCCESS           - The Watchdog Timer protocol was
//                                          installed.
//                  EFI_OUT_OF_RESOURCES  - Space for a new handle could not
//                                          be allocated.
//                  EFI_INVALID_PARAMETER - One of the parameters has an 
//                                          invalid value.
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS WatchdogInit (
    IN EFI_HANDLE        ImageHandle,
    IN EFI_SYSTEM_TABLE  *SystemTable )
{
    EFI_STATUS  Status;

    // Use the Timer event to trigger the Watchdog.  No specific hardware
    // exists for this
    Status = pBS->CreateEvent( EVT_TIMER | EVT_NOTIFY_SIGNAL, \
                               TPL_NOTIFY, \
                               WatchdogHandler, \
                               NULL, \
                               &mWatchdogEvent );

    // Create a handle for the ArchProtocol and install Watchdog Arch
    // Protocol on the handle
    Status = pBS->InstallProtocolInterface( &mWatchdogHandle, \
                                            &gWatchdogGuid, \
                                            EFI_NATIVE_INTERFACE, \
                                            &mWatchdog );

    return Status;
}

#if defined(HPET_PROTOCOL_SUPPORT) && (HPET_PROTOCOL_SUPPORT != 0)
// Mask used for counter and comparator calculations to adjust for a 32-bit or 64-bit counter.
UINT64  gCounterMask;
// Cached state of the HPET General Capabilities register managed by this driver.
// Caching the state reduces the number of times the configuration register is read.
volatile HPET_GENERAL_CAPABILITIES_ID_REGISTER   gHpetGeneralCapabilities;
// Cached state of the HPET General Configuration register managed by this driver.
// Caching the state reduces the number of times the configuration register is read.
volatile HPET_GENERAL_CONFIGURATION_REGISTER     gHpetGeneralConfiguration;
// Cached state of the Configuration register for the HPET Timer managed by
// this driver.  Caching the state reduces the number of times the configuration
// register is read.
volatile HPET_TIMER_CONFIGURATION_REGISTER       gTimerConfiguration;

EFI_EVENT                               gHpetLegacyBootEvent;

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:   EnableHpetInChipset
//
// Description: This function enables HPET register decode.
//
// Input:       None
//
// Output:      None
//
// Notes:       Porting required.
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

VOID EnableHpetInChipset( VOID )
{
    // Porting required.
//    WRITE_MEM32_RCRB_S3(gBootScriptSave, RCRB_MMIO_HPTC, ((HPET_BASE_ADDRESS >> 12) & 3) | 0x80);
WRITE_MEM32_RCRB_S3(gBootScript, RCRB_MMIO_HPTC, ((HPET_BASE_ADDRESS >> 12) & 3) | 0x80);
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:   HpetRead
//
// Description: This function reads a 64-bit register from the HPET register.
//
// Input:       Offset - Specifies the offset of the HPET register to read.
//
// Output:      The 64-bit value read from the HPET register specified by
//              Offset.
//
// Notes:       No porting required.
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

UINT64 HpetRead (
    IN UINTN        Offset )
{
    return MMIO_READ64( HPET_BASE_ADDRESS + Offset );
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:   HpetWrite
//
// Description: This function writes a 64-bit HPET register.
//
// Input:       Offset - Specifies the ofsfert of the HPET register to write.
//              Value  - Specifies the value to write to the HPET register
//                       specified by Offset.
//
// Output:      The 64-bit value written to HPET register specified by Offset.
//
// Notes:       No porting required.
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

UINT64 HpetWrite (
    IN UINTN        Offset,
    IN UINT64       Value )
{
    MMIO_WRITE64( HPET_BASE_ADDRESS + Offset, Value );
    return HpetRead( Offset );
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:   HpetEnable
//
// Description: This function enables or disables the main counter in the
//              HPET Timer.
//
// Input:       Enable  TRUE  - Enable the main counter in the HPET Timer.
//                      FALSE - Disable the main counter in the HPET Timer.
// Output:      None
//
// Notes:       No porting required.
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

VOID HpetEnable (
    IN BOOLEAN      Enable )
{
    gHpetGeneralConfiguration.Bits.MainCounterEnable = Enable ? 1 : 0;
    HpetWrite( HPET_GENERAL_CONFIGURATION_OFFSET,
                                          gHpetGeneralConfiguration.Uint64);
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:   StopHpetBeforeLagecyBoot
//
// Description: This function stops HPET counter & interrupt.
//
// Input:       Event   - Event of callback
//              Context - Context of callback.
//
// Output:      None
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID StopHpetBeforeLagecyBoot (
    IN EFI_EVENT        Event,
    IN VOID             *Context )
{
    // Disable HPET and Legacy Replacement Support.
    HpetEnable (FALSE);
    CountTime ((HPET_DEFAULT_TICK_DURATION / 10) * 2, PM_BASE_ADDRESS);
    HpetWrite (HPET_TIMER_CONFIGURATION_OFFSET + HPET_OFFSET * HPET_TIMER_STRIDE, 0);

#if defined(HPET_APIC_INTERRUPT_MODE) && (HPET_APIC_INTERRUPT_MODE != 0)
    IoApicDisableIrq(HPET_APIC_INTERRUPT_PIN);
#else
    gHpetGeneralConfiguration.Bits.LegacyRouteEnable = 0;

    HpetEnable (FALSE);
#endif

    pBS->CloseEvent(Event);
}
#endif

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:   TimerRegisterHandler
//
// Description: This function registers a handler that is called every time
//              the timer interrupt fires
//
// Input:       *This          - Pointer to the instance of the Architectural
//                               Protocol
//              NotifyFunction - The function to call when the interrupt fires
//
// Output:      EFI_STATUS
//                  EFI_SUCCESS         - New handle registered
//                  EFI_ALREADY_STARTED - if Notify function is already
//                                        defined   
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS TimerRegisterHandler (
    IN EFI_TIMER_ARCH_PROTOCOL      *This,
    IN EFI_TIMER_NOTIFY             NotifyFunction )
{
    // Check to see if the handler has already been installed
    if ((NotifyFunction != NULL) && (mNotifyFunction != NULL)) {
        return EFI_ALREADY_STARTED;
    }

    // If not install it
    mNotifyFunction = NotifyFunction;

    return EFI_SUCCESS;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:   SetTimerPeriod
//
// Description: This function sets the timer to create an Intr on IRQ0
//              every TimerPeriod number of 100ns intervals
//
// Input:       *This       - Pointer to the instance of the Architectural
//                            Protocol
//              TimerPeriod - The number of 100ns intervals to which the
//                            timer will be programmed. This value will 
//                            be rounded up to the nearest timer interval.
//
// Output:      EFI_SUCCESS
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS SetTimerPeriod (
    IN EFI_TIMER_ARCH_PROTOCOL      *This,
    IN UINT64                       TimerPeriod )
{
#if defined(HPET_PROTOCOL_SUPPORT) && (HPET_PROTOCOL_SUPPORT != 0)
    UINTN                   Remainder;
    UINT64                  TimerCount;

    // Disable HPET timer when adjusting the timer period
    HpetEnable (FALSE);
#else
//    EFI_STATUS              Status;
    UINT32                  NumberOfTicks;
	UINT8                   Value8;
#endif

    // Find the CPU Architectural Protocol
    //Status = pBS->LocateProtocol( &gEfiCpuArchProtocolGuid, NULL, &CpuArch );

    // If timer period is 0 then disable the Timer interrupt
    if (TimerPeriod == 0) {
#if defined(HPET_APIC_INTERRUPT_MODE) && (HPET_APIC_INTERRUPT_MODE != 0)
        IoApicDisableIrq(HPET_APIC_INTERRUPT_PIN);
#endif
        // DisableIrq(SYSTEM_TIMER_IRQ);
        mLegacy8259->DisableIrq( mLegacy8259, SYSTEM_TIMER_IRQ );
    } else {
#if defined(HPET_PROTOCOL_SUPPORT) && (HPET_PROTOCOL_SUPPORT != 0)
        // Convert TimerPeriod to femtoseconds and divide by the number if
        // femtoseconds per tick of the HPET counter to determine the number
        // of HPET counter ticks in TimerPeriod 100 ns units.
        TimerCount = Div64( Mul64( TimerPeriod, 100000000 ),
                     gHpetGeneralCapabilities.Bits.CounterClockPeriod,
                     &Remainder );

        // Reset Main Counter
        HpetWrite (HPET_MAIN_COUNTER_OFFSET, 0);
        // ValueSetEnable must be set if the timer is set to periodic mode.
        gTimerConfiguration.Bits.ValueSetEnable = 1;
        HpetWrite (HPET_TIMER_CONFIGURATION_OFFSET + HPET_OFFSET * HPET_TIMER_STRIDE, gTimerConfiguration.Uint64);
        // Clear ValueSetEnable bit.
        gTimerConfiguration.Bits.ValueSetEnable = 0;
        HpetWrite (HPET_TIMER_COMPARATOR_OFFSET + HPET_OFFSET * HPET_TIMER_STRIDE, TimerCount);

#else
    // otherwise change the timer period into number of ticks and set
    // the timer
        if (TimerPeriod > MAX_TICK_DURATION) TimerPeriod = MAX_TICK_DURATION;
        // NumberOfTicks = TimerPeriod * 100 /TIMER_TICK;
        // Since TimerPeriod in 100ns units and TIMER_TICK in ns
        // We have to multiple TimerPeriod by 100
        // To round up result:
        //      NumberOfTicks = TimerPeriod * 100/TIMER_TICK + 0.5 =
        //                      (TimerPeriod*100+TIMER_TICK/2)/TIMER_TICK
        NumberOfTicks = ((UINT32)TimerPeriod * 100 + TIMER_TICK / 2) \
                                                                / TIMER_TICK;
        // Write to port 0x43 to setup the timer
        IoWrite8 ( LEGACY_TIMER_CTRL, 0x36 );
        // Write to port 0x40 to set the time
        IoWrite8 ( LEGACY_TIMER_0_COUNT, (UINT8)NumberOfTicks );
        IoWrite8 ( LEGACY_TIMER_0_COUNT, *(((UINT8*)&NumberOfTicks) + 1) );

        Value8 = 0x36;
        BOOT_SCRIPT_S3_IO_WRITE_MACRO(gBootScript, EfiBootScriptWidthUint8, LEGACY_TIMER_CTRL, 1, &Value8);
        Value8 = (UINT8)NumberOfTicks;
        BOOT_SCRIPT_S3_IO_WRITE_MACRO(gBootScript, EfiBootScriptWidthUint8, LEGACY_TIMER_0_COUNT, 1, &Value8);
        Value8 = *(((UINT8*)&NumberOfTicks)+1);
        BOOT_SCRIPT_S3_IO_WRITE_MACRO(gBootScript, EfiBootScriptWidthUint8, LEGACY_TIMER_0_COUNT, 1, &Value8);

#endif

        // Now enable the interrupt
#if defined(HPET_APIC_INTERRUPT_MODE) && (HPET_APIC_INTERRUPT_MODE != 0)
        IoApicEnableIrq(HPET_APIC_INTERRUPT_PIN, HPET_INTERRUPT_TRIGGER, (HPET_INTERRUPT_POLARITY == 0) ? TRUE : FALSE);
#endif
        // EnableIrq(SYSTEM_TIMER_IRQ);
        mLegacy8259->EnableIrq( mLegacy8259, SYSTEM_TIMER_IRQ, FALSE );
        
#if defined(HPET_PROTOCOL_SUPPORT) && (HPET_PROTOCOL_SUPPORT != 0)
        // Enable HPET Interrupt Generation
        gTimerConfiguration.Bits.InterruptEnable = 1;
        HpetWrite (HPET_TIMER_CONFIGURATION_OFFSET + HPET_OFFSET * HPET_TIMER_STRIDE, gTimerConfiguration.Uint64);

        // Enable the HPET counter once new timer period has been established
        // The HPET counter should run even if the HPET Timer interrupts are
        // disabled.  This is used to account for time passed while the interrupt
        // is disabled.
        HpetEnable (TRUE);
#endif
    }

    mProgrammedTimerValue = TimerPeriod;

    return EFI_SUCCESS;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:   GetTimerPeriod
//
// Description: This function returns the current timer period
//
// Input:       *This        - Pointer to the instance of the Architectural
//                             Protocol 
//              *TimerPeriod - pointer to a memory location to load the
//                             current Timer period into
//
// Output:      EFI_SUCCESS - *TimerPeriod - Current Timer Period
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS GetTimerPeriod (
    IN EFI_TIMER_ARCH_PROTOCOL      *This,
    IN OUT UINT64                   *TimerPeriod )
{
    *TimerPeriod = mProgrammedTimerValue;

    return EFI_SUCCESS;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:   GenerateSoftIntr

//
// Description: This function generates a soft timer interrupt
//
// Input:       *This - Pointer to the instance of the Architectural Protocol
//
// Output:      EFI_UNSUPPORTED
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS GenerateSoftIntr (
    IN EFI_TIMER_ARCH_PROTOCOL      *This )
{
    return EFI_UNSUPPORTED;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:   TimerInterruptHandler
//
// Description: This function is called when the Timer reaches 0.  It raises
//              the TPL and then calls the registered notify function
//
// Input:       InterruptType - Interrupt type
//              SystemContext - System context
//
// Output:      None
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

VOID TimerInterruptHandler (
    IN EFI_EXCEPTION_TYPE   InterruptType,
    IN EFI_SYSTEM_CONTEXT   SystemContext )
{
    EFI_TPL                 OldTpl;
    static volatile UINT32  StoreCF8;
#if defined(HPET_APIC_INTERRUPT_MODE) && (HPET_APIC_INTERRUPT_MODE != 0) && defined(HPET_INTERRUPT_TRIGGER) && (HPET_INTERRUPT_TRIGGER == 1)
    static volatile UINT64  HpetGenIntSts;
#endif

    OldTpl = pBS->RaiseTPL (TPL_HIGH_LEVEL);

    SaveRestoreRegisters( TRUE );

    StoreCF8 = IoRead32(0xcf8);    // Store CF8 (PCI index)

#if defined(HPET_APIC_INTERRUPT_MODE) && (HPET_APIC_INTERRUPT_MODE != 0)
    IoApicEoi(GetHpetApicPin());

#if defined(HPET_INTERRUPT_TRIGGER) && (HPET_INTERRUPT_TRIGGER == 1)
    HpetGenIntSts = HpetRead(HPET_GENERAL_INTERRUPT_STATUS_OFFSET);
    HpetWrite (HPET_GENERAL_INTERRUPT_STATUS_OFFSET, Shl64(BIT0, HPET_OFFSET));
#endif
#else
    // Clear the interrupt flag
    mLegacy8259->EndOfInterrupt(mLegacy8259,SYSTEM_TIMER_IRQ);
#endif

    // This checks for the existance of a registered notify function and
    // if it exists it calls the function with the current programmed Timer
    // Period
    if (mNotifyFunction)
    {
#if defined(HPET_APIC_INTERRUPT_MODE) && (HPET_APIC_INTERRUPT_MODE != 0) && defined(HPET_INTERRUPT_TRIGGER) && (HPET_INTERRUPT_TRIGGER == 1)
        if (HpetGenIntSts & Shl64(BIT0, HPET_OFFSET))
        {
            mNotifyFunction (mProgrammedTimerValue);
        }
#else
        mNotifyFunction (mProgrammedTimerValue);
#endif
    }

    IoWrite32(0xcf8, StoreCF8);    // Restore 0xCF8 (PCI index)

    SaveRestoreRegisters( FALSE );

    pBS->RestoreTPL (OldTpl);
}

#if defined(HPET_APIC_INTERRUPT_MODE) && (HPET_APIC_INTERRUPT_MODE != 0)
//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:   Irq0InterruptHandler
//
// Description: This function is called when the 8254 Timer 0 reaches 0.
//              It raises the TPL and then calls the registered notify
//              function.
//
// Input:       InterruptType - Interrupt type
//              SystemContext - System context
//
// Output:      None
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

VOID Irq0InterruptHandler (
    IN EFI_EXCEPTION_TYPE   InterruptType,
    IN EFI_SYSTEM_CONTEXT   SystemContext )
{
    EFI_TPL                 OldTpl;


    OldTpl = pBS->RaiseTPL (TPL_HIGH_LEVEL);

    // Clear the interrupt flag
    mLegacy8259->EndOfInterrupt(mLegacy8259, SYSTEM_TIMER_IRQ);

    pBS->RestoreTPL (OldTpl);
}
#endif

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:   TimerInit
//
// Description: This function installs the the timer protocol on its handle,
//              and initializes the timer.
//
// Input:       Event   - Event of callback
//              Context - Context of callback.
//
// Output:      EFI_STATUS
//                  EFI_SUCCESS           - The Timer protocol was installed
//                  EFI_OUT_OF_RESOURCES  - Space for a new handle could not
//                                          be allocated.
//                  EFI_INVALID_PARAMETER - One of the parameters has an 
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS EFIAPI TimerInit (
    IN EFI_EVENT            Event,
    IN VOID                 *Context )
{
    EFI_STATUS              Status;
    EFI_CPU_ARCH_PROTOCOL   *CpuArch;
    // TimerVector must be initialized to 0, since GetVector only modifies
    // the lowest byte, and RegisterInterruptHandler requires TimerVector
    // to be 4 bytes.
    UINT32      TimerVector = 0;
    UINT32      Irq0TimerVector = 0;
    UINT8       Value;

    Status = pBS->LocateProtocol ( &gEfiLegacy8259ProtocolGuid, \
                                   NULL, \
                                   &mLegacy8259 );
    ASSERT_EFI_ERROR(Status);

#if defined(HPET_PROTOCOL_SUPPORT) && (HPET_PROTOCOL_SUPPORT != 0)
    // Enable HPET (0x3404)
    EnableHpetInChipset();

    // Retrieve HPET Capabilities and Configuration Information
    gHpetGeneralCapabilities.Uint64  = HpetRead (HPET_GENERAL_CAPABILITIES_ID_OFFSET);
    gHpetGeneralConfiguration.Uint64 = HpetRead (HPET_GENERAL_CONFIGURATION_OFFSET);

    // If Revision is not valid, then ASSERT() and unload the driver because the HPET
    // device is not present.
    if (gHpetGeneralCapabilities.Uint64 == 0 || gHpetGeneralCapabilities.Uint64 == 0xFFFFFFFFFFFFFFFF) {
        TRACE((-1, "HPET device is not present.  Unload HPET driver.\n"));
        return EFI_DEVICE_ERROR;
    }

    // Force the HPET timer to be disabled while setting everything up
    HpetEnable (FALSE);
#if defined(HPET_APIC_INTERRUPT_MODE) && (HPET_APIC_INTERRUPT_MODE == 0)
    // Enable Legacy Interrupt
    gHpetGeneralConfiguration.Bits.LegacyRouteEnable = 1;
#endif
#endif

    // Disable timer, make sure no interrupt will be created
    Status = SetTimerPeriod ( &mTimerProtocol, 0 );
    ASSERT_EFI_ERROR(Status);

#if defined(HPET_PROTOCOL_SUPPORT) && (HPET_PROTOCOL_SUPPORT != 0)
    // Configure the selected HPET Timer (Timer#0), clear InterruptEnable to keep
    // interrupts disabled until full init is complete
    // Enable PeriodicInterruptEnable to use perioidic mode
    // Configure as a 32-bit counter
    gTimerConfiguration.Uint64 = HpetRead (HPET_TIMER_CONFIGURATION_OFFSET + HPET_OFFSET * HPET_TIMER_STRIDE);
    gTimerConfiguration.Bits.InterruptEnable         = 0;
    gTimerConfiguration.Bits.PeriodicInterruptEnable = 1;
    gTimerConfiguration.Bits.CounterSizeEnable       = 1;   // 32bit
    gTimerConfiguration.Bits.LevelTriggeredInterrupt = HPET_INTERRUPT_TRIGGER;
#if defined(HPET_APIC_INTERRUPT_MODE) && (HPET_APIC_INTERRUPT_MODE != 0)
    gTimerConfiguration.Bits.InterruptRoute = HPET_APIC_INTERRUPT_PIN;
#endif
    HpetWrite (HPET_TIMER_CONFIGURATION_OFFSET + HPET_OFFSET * HPET_TIMER_STRIDE, gTimerConfiguration.Uint64);

    // Read the HPET Timer Capabilities and Configuration register back again.
    // CounterSizeEnable will be read back as a 0 if it is a 32-bit only timer
    gTimerConfiguration.Uint64 = HpetRead (HPET_TIMER_CONFIGURATION_OFFSET + HPET_OFFSET * HPET_TIMER_STRIDE);
#if defined(HPET_APIC_INTERRUPT_MODE) && (HPET_APIC_INTERRUPT_MODE != 0)
    // If the interrupt pin isn't supported by the particular timer, then the value read back won't match that is written.
    if (gTimerConfiguration.Bits.InterruptRoute != HPET_APIC_INTERRUPT_PIN) {
        ASSERT_EFI_ERROR (EFI_UNSUPPORTED);
        return EFI_UNSUPPORTED;
    }
#endif
    if ((gTimerConfiguration.Bits.CounterSizeEnable == 1) && (sizeof (UINTN) == sizeof (UINT64))) {
        // 64-bit BIOS can use 64-bit HPET timer
        gCounterMask = 0xffffffffffffffff;
        // Set timer back to 64-bit
        gTimerConfiguration.Bits.CounterSizeEnable = 0;
        HpetWrite (HPET_TIMER_CONFIGURATION_OFFSET + HPET_OFFSET * HPET_TIMER_STRIDE, gTimerConfiguration.Uint64);
    } else {
        gCounterMask = 0x00000000ffffffff;
    }
#endif

    // Find the CPU Arch Protocol
    Status = pBS->LocateProtocol ( &gEfiCpuArchProtocolGuid, \
                                   NULL, \
                                   &CpuArch );
    ASSERT_EFI_ERROR(Status);

#if defined(HPET_APIC_INTERRUPT_MODE) && (HPET_APIC_INTERRUPT_MODE != 0)
    TimerVector = MASTER_INTERRUPT_BASE + HPET_APIC_INTERRUPT_PIN;

    Status = mLegacy8259->GetVector ( mLegacy8259, \
                                      Efi8259Irq0, \
                                      (UINT8 *)&Irq0TimerVector );
    ASSERT_EFI_ERROR(Status);

    Status = CpuArch->RegisterInterruptHandler ( CpuArch, \
                                                 Irq0TimerVector, \
                                                 Irq0InterruptHandler );
    ASSERT_EFI_ERROR(Status);
#else
    Status = mLegacy8259->GetVector ( mLegacy8259, \
                                      Efi8259Irq0, \
                                      (UINT8 *)&TimerVector );
    ASSERT_EFI_ERROR(Status);
#endif

    Status = CpuArch->RegisterInterruptHandler ( CpuArch, \
                                                 TimerVector, \
                                                 TimerInterruptHandler );
    ASSERT_EFI_ERROR(Status);

    // Initialize the handle pointer
    mNotifyFunction = NULL;

#if defined(HPET_PROTOCOL_SUPPORT) && (HPET_PROTOCOL_SUPPORT != 0)
    // Init default for Timer 1
	IoWrite8( LEGACY_TIMER_CTRL, 0x36 );
	IoWrite8( LEGACY_TIMER_0_COUNT, 0 );
	IoWrite8( LEGACY_TIMER_0_COUNT, 0 );
    // Add boot script programming
    Value = 0x36;
    BOOT_SCRIPT_S3_IO_WRITE_MACRO(gBootScript, EfiBootScriptWidthUint8, LEGACY_TIMER_CTRL, 1, &Value);
    Value = 0x0;
    BOOT_SCRIPT_S3_IO_WRITE_MACRO(gBootScript, EfiBootScriptWidthUint8, LEGACY_TIMER_0_COUNT, 1, &Value);
    BOOT_SCRIPT_S3_IO_WRITE_MACRO(gBootScript, EfiBootScriptWidthUint8, LEGACY_TIMER_0_COUNT, 1, &Value);

    // The default value of 10000 100 ns units is the same as 1 ms.
    Status = SetTimerPeriod ( &mTimerProtocol, HPET_DEFAULT_TICK_DURATION );



    Status = CreateLegacyBootEvent( TPL_CALLBACK,
                                    StopHpetBeforeLagecyBoot,
                                    NULL,
                                    &gHpetLegacyBootEvent );
#else
    // Force the timer to be enabled at its default period
    Status = SetTimerPeriod ( &mTimerProtocol, DEFAULT_TICK_DURATION );
#endif
    ASSERT_EFI_ERROR (Status);

    //Program Timer1 to pass certain customer's test
    IoWrite8( LEGACY_TIMER_CTRL, 0x54 );
    IoWrite8( LEGACY_TIMER_1_COUNT, 0x12 );
    //add boot script programming
    Value = 0x54;
    BOOT_SCRIPT_S3_IO_WRITE_MACRO(gBootScript, EfiBootScriptWidthUint8, LEGACY_TIMER_CTRL, 1, &Value);
    Value = 0x12;
    BOOT_SCRIPT_S3_IO_WRITE_MACRO(gBootScript, EfiBootScriptWidthUint8, LEGACY_TIMER_1_COUNT, 1, &Value);


    // Install the Timer Architectural Protocol onto a new handle
    Status = pBS->InstallProtocolInterface ( &mTimerProtocolHandle, \
                                             &gEfiTimerArchProtocolGuid, \
                                             EFI_NATIVE_INTERFACE, \
                                             &mTimerProtocol );
    ASSERT_EFI_ERROR(Status);

    return Status;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:   ProgramIrqMaskTrigger
//
// Description: Program the Irq Mask and Trigger.
//
// Input:       None
//
// Output:      None
//
// Notes:       Here is the control flow of this function:
//              1. Program Master Irq Mask.
//              2. Program Slave Irq Mask.
//              3. Program Trigger Level.
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

VOID ProgramIrqMaskTrigger (VOID)
{
    IoWrite8(LEGACY_8259_MASK_REGISTER_MASTER, (UINT8)gIrqMask[gMode]);
    IoWrite8(LEGACY_8259_MASK_REGISTER_SLAVE, (UINT8)(gIrqMask[gMode] >> 8));

    // 4d0 can not be accessed as by IoWrite16, we have to split
    IoWrite8(LEGACY_8259_EDGE_LEVEL_TRIGGERED_REGISTER_MASTER, \
                                            (UINT8)gIrqTrigger[gMode]);
    IoWrite8(LEGACY_8259_EDGE_LEVEL_TRIGGERED_REGISTER_SLAVE, \
                                            (UINT8)(gIrqTrigger[gMode] >> 8));
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:   SetVectorBase
//
// Description: Initializes the interrupt controller and program the Irq 
//              Master and Slave Vector Base.
//
// Input:       *This      - Pointer to this object
//              MasterBase - IRQ base for the master 8259 controller
//              SlaveBase  - IRQ base for the slave 8259 controller
//
// Output:      EFI_SUCCESS - Interrupt on the interrupt controllers was
//                            enabled.
//
// Notes:       Here is the control flow of this function:
//              1. If Master base is changed, initialize master 8259 setting 
//                  the interrupt offset.
//              2. If Slave base is changed, initialize slave 8259 setting 
//                  the interrupt offset.
//              3. Return EFI_SUCCESS.
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS SetVectorBase (
    IN EFI_LEGACY_8259_PROTOCOL *This,
    IN UINT8                    MasterBase,
    IN UINT8                    SlaveBase )
{
    // 8259 Master
    if (MasterBase != gMasterBase) {
        // Start 8259 Master Initialization. 
        IoWrite8(LEGACY_8259_CONTROL_REGISTER_MASTER, ICW1); // 0x20
        // Set Interrupt Offset 
        IoWrite8(LEGACY_8259_MASK_REGISTER_MASTER, MasterBase); // 0x21
        // Set Slave IRQ. 
        IoWrite8(LEGACY_8259_MASK_REGISTER_MASTER, ICW3_M); // 0x21
        // Set 8259 mode. See ICW4 comments with #define. 
        IoWrite8(LEGACY_8259_MASK_REGISTER_MASTER, ICW4); // 0x21
        gMasterBase = MasterBase;
    }

    // 8259 Slave
    if (SlaveBase != gSlaveBase) {
        // Start 8259 Slave  Initialization. 
        IoWrite8(LEGACY_8259_CONTROL_REGISTER_SLAVE, ICW1); // 0xA0
        // Set Interrupt Offset 
        IoWrite8(LEGACY_8259_MASK_REGISTER_SLAVE, SlaveBase); // 0xA1
        // Set Slave IRQ. 
        IoWrite8(LEGACY_8259_MASK_REGISTER_SLAVE, ICW3_S); // 0xA1
        // Set 8259 mode. See ICW4 comments with #define. 
        IoWrite8(LEGACY_8259_MASK_REGISTER_SLAVE, ICW4); // 0xA1
        gSlaveBase = SlaveBase;
    }

    return EFI_SUCCESS;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:   GetMask
//
// Description: Get the Master/Slave Irq Mask, Irq Level for Legacy real 
//              mode and protected mode.
//
// Input:       *This               - Pointer to this object
//              *LegacyMask         - Legacy mode interrupt mask
//              *LegacyEdgeLevel    - Legacy mode edge/level trigger value
//              *ProtectedMask      - Protected mode interrupt mask
//              *ProtectedEdgeLevel - Protected mode edge/level trigger value
//
// Output:      EFI_SUCCESS - Returned irq mask/level.
//
// Notes:       Here is the control flow of this function:
//              1. If *LegacyMask not NULL, get legacy Mask.
//              2. If *LegacyEdgeLevel not NULL, get legacy Trigger Level.
//              3. If *ProtectedMask not NULL, get protected Mask.
//              4. If *ProtectedEdgeLevel not NULL, get protected trigger 
//                 level.
//              5. Return EFI_SUCCESS.
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS GetMask (
    IN EFI_LEGACY_8259_PROTOCOL *This,
    OUT UINT16                  *LegacyMask         OPTIONAL,
    OUT UINT16                  *LegacyEdgeLevel    OPTIONAL,
    OUT UINT16                  *ProtectedMask      OPTIONAL,
    OUT UINT16                  *ProtectedEdgeLevel OPTIONAL )
{
    if (LegacyMask)         *LegacyMask         = gIrqMask[0];
    if (LegacyEdgeLevel)    *LegacyEdgeLevel    = gIrqTrigger[0];
    if (ProtectedMask)      *ProtectedMask      = gIrqMask[1];
    if (ProtectedEdgeLevel) *ProtectedEdgeLevel = gIrqTrigger[1];

    return EFI_SUCCESS;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:   SetMask
//
// Description: Set the Master/Slave Irq Mask, Irq Level for Legacy real mode
//              and protected mode.
//
// Input:       *This               - Pointer to this object
//              *LegacyMask         - Legacy mode interrupt mask
//              *LegacyEdgeLevel    - Legacy mode edge/level trigger value
//              *ProtectedMask      - Protected mode interrupt mask
//              *ProtectedEdgeLevel - Protected mode edge/level trigger value
//
// Output:      EFI_SUCCESS - Set irq mask/level.
//
// Notes:       Here is the control flow of this function:
//              1. If *LegacyMask not NULL, set legacy mask variable.
//              2. If *LegacyEdgeLevel not NULL, set legacy Trigger Level
//                 variable.
//              3. If *ProtectedMask not NULL, set protected mask variable.
//              4. If *ProtectedEdgeLevel not NULL, set protected trigger 
//                 level variable.
//              5. Call function to program 8259 with mask/trigger of
//                 current mode.
//              6. Return EFI_SUCCESS.
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS SetMask (
    IN EFI_LEGACY_8259_PROTOCOL *This,
    IN UINT16                   *LegacyMask         OPTIONAL,
    IN UINT16                   *LegacyEdgeLevel    OPTIONAL,
    IN UINT16                   *ProtectedMask      OPTIONAL,
    IN UINT16                   *ProtectedEdgeLevel OPTIONAL )
{
    if (LegacyMask)         gIrqMask[0]    = *LegacyMask;
    if (LegacyEdgeLevel)    gIrqTrigger[0] = *LegacyEdgeLevel;
    if (ProtectedMask)      gIrqMask[1]    = *ProtectedMask;
    if (ProtectedEdgeLevel) gIrqTrigger[1] = *ProtectedEdgeLevel;

    ProgramIrqMaskTrigger();

    return EFI_SUCCESS;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:   SetMode
//
// Description: Sets the interrupt mode operation to legacy or protected. 
//              New mask and edge/level status can be provided as input
//
// Input:       *This      - Pointer to this object
//              Mode       - Interrupt mode setting
//              *Mask      - New interrupt mask for this mode
//              *EdgeLevel - New edge/level trigger value for this mode
//
// Output:      EFI_SUCCESS - Set mode was successful
//
// Notes:       Here is the control flow of this function:
//              1. If invalid mode, return EFI_INVALID_PARAMETER.
//              2. If *Mask not NULL, set mode mask variable.
//              3. If *EdgeLevel not NULL, set mode trigger level variable.
//              4. Call function to program 8259 with mask/trigger of
//                 current mode.
//              5. Return EFI_SUCCESS.
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS SetMode (
    IN EFI_LEGACY_8259_PROTOCOL *This,
    IN EFI_8259_MODE            Mode,
    IN UINT16                   *Mask       OPTIONAL,
    IN UINT16                   *EdgeLevel  OPTIONAL )
{
    if (Mode >= Efi8259MaxMode) return EFI_INVALID_PARAMETER;
#if defined (HPET_INTERRUPT_TRIGGER) && (HPET_INTERRUPT_TRIGGER == 1)
    if (Mode == Efi8259LegacyMode)
        gTimerConfiguration.Bits.InterruptEnable = 0;
    else    // Efi8259ProtectedMode
        gTimerConfiguration.Bits.InterruptEnable = 1;

    HpetWrite (HPET_TIMER_CONFIGURATION_OFFSET + HPET_OFFSET * HPET_TIMER_STRIDE, gTimerConfiguration.Uint64);
#endif

    gMode = Mode;
    if (Mask) gIrqMask[Mode] = *Mask;
    if (EdgeLevel) gIrqTrigger[Mode] = *EdgeLevel;

    ProgramIrqMaskTrigger();

    return EFI_SUCCESS;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:   GetVector
//
// Description: Returns the vector number for the requested IRQ
//
// Input:       This   - Legacy8259 protocol object
//              Irq    - IRQ number for which vector is needed
//              Vector - Vector value is returned in this pointer
//
// Output:      EFI_STATUS
//                  EFI_INVALID_PARAMETER - Invalid IRQ.
//                  EFI_SUCCESS           - Get Irq Vector for IRQ.
//
// Notes:       Here is the control flow of this function:
//              1. If invalid IRQ, return EFI_INVALID_PARAMETER.
//              2. If Set *Vector to Irq base + interrupt offset.
//              3. Return EFI_SUCCESS.
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS GetVector (
    IN EFI_LEGACY_8259_PROTOCOL *This,
    IN EFI_8259_IRQ             Irq,
    OUT UINT8                   *Vector )
{
    if ((UINT8)Irq >= (UINT8)Efi8259IrqMax) return EFI_INVALID_PARAMETER;
    *Vector = (Irq <= Efi8259Irq7) ? gMasterBase + Irq : gSlaveBase + Irq - 8;

    return EFI_SUCCESS;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:   EnableIrq
//
// Description: Enable the Interrupt controllers to respond in a specific IRQ.
//
// Input:       This           - Legacy8259 protocol object
//              Irq            - IRQ that has to be enabled
//              LevelTriggered - Trigger mechanism (level or edge) for this
//                               IRQ
//
// Output:      EFI_STATUS
//                  EFI_SUCCESS           - Interrupt on the interrupt 
//                                          controllers was enabled.
//                  EFI_INVALID_PARAMETER - Interrupt not existent. 
//                                          The 8259 master/slave supports
//                                          IRQ 0-15.
//
// Notes:       Here is the control flow of this function:
//              1. Check if IRQ is valid. If not, return EFI_INVALID_PARAMETER
//              2. Clear interrupt mask bit in variable of current mode.
//              3. Set/Clear bit of trigger level variable of current mode.
//              4. Program mask/trigger.
//              5. Return EFI_SUCCESS.
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS EnableIrq (
    IN EFI_LEGACY_8259_PROTOCOL *This,
    IN EFI_8259_IRQ             Irq,
    IN BOOLEAN                  LevelTriggered )
{
    if ((UINT8)Irq > (UINT8)15) return EFI_INVALID_PARAMETER;

    gIrqMask[gMode] &= (UINT16)(~(1 << Irq)); // Clear mask for the Irq.

    gIrqTrigger[gMode] &= (UINT16)(~(1 << Irq)); // Mask Irq to change.

    // Change irq bit, 0 = edge, 1 = level. 
    if (LevelTriggered) gIrqTrigger[gMode] |= (1 << Irq);

    ProgramIrqMaskTrigger();

    return EFI_SUCCESS;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:   DisableIrq
//
// Description: Disable the Interrupt controllers to stop responding to 
//              a specific IRQ.
//
// Input:       This - Legacy8259 protocol object
//              Irq  - IRQ that has to be disabled
//
// Output:      EFI_STATUS
//                  EFI_SUCCESS           - Interrupt on the interrupt
//                                          controllers was enabled.
//                  EFI_INVALID_PARAMETER - Interrupt not existent. 
//                                          The 8259 master/slave supports
//                                          IRQ 0-15.
//
// Notes:       Here is the control flow of this function:
//              1. Check if IRQ is valid. If not, return EFI_INVALID_PARAMETER
//              2. Set interrupt mask bit in variable of current mode.
//              3. Program mask/trigger.
//              4. Return EFI_SUCCESS.
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS DisableIrq (
    IN EFI_LEGACY_8259_PROTOCOL *This,
    IN EFI_8259_IRQ             Irq )
{
    if ((UINT8)Irq > (UINT8)15) return EFI_INVALID_PARAMETER;

    gIrqMask[gMode] |= (1 << Irq);  // Set mask for the IRQ.

    ProgramIrqMaskTrigger();

    return EFI_SUCCESS;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:   GetInterruptLine
//
// Description: Get IRQ vector asigned to PCI card.
//
// Input:       This      - Pointer to this object
//              PciHandle - PCI handle for this device
//              Vector    - Interrupt vector this device
//
// Output:      EFI_STATUS
//                  EFI_SUCCESS           - Vector returned.
//                  EFI_INVALID_PARAMETER - Invalid PciHandle.
//
// Notes:       Here is the control flow of this function:
//              1. Get Handle of PciIo installed on PciHandle.
//              2. If PciIo not installed, return EFI_INVALID_DEVICE.
//              3. Set *vector to Irq vector programmed into card.
//              4. Return EFI_SUCCESS.
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS GetInterruptLine (
    IN EFI_LEGACY_8259_PROTOCOL *This,
    IN EFI_HANDLE               PciHandle,
    OUT UINT8                   *Vector )
{
    EFI_STATUS              Status;
    EFI_PCI_IO_PROTOCOL     *PciIo;

    Status = pBS->HandleProtocol( PciHandle, \
                                  &gEfiPciIoProtocolGuid, \
                                  &PciIo );
    if (EFI_ERROR(Status)) return EFI_INVALID_PARAMETER;

    // Read vector from card. 
    PciIo->Pci.Read( PciIo, \
                     EfiPciIoWidthUint8, \
                     PCI_INTLINE, \
                     1, \
                     Vector );

    return EFI_SUCCESS;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:   EndOfInterrupt
//
// Description: Send end of interrupt command to interrupt controller(s).
//
// Input:       This - Pointer to this object
//              Irq  - IRQ number for this EOI has to be sent
//
// Output:      EFI_STATUS
//                  EFI_SUCCESS           - EOI command sent to controller(s)
//                  EFI_INVALID_PARAMETER - Interrupt not existent. The 8259
//                                          master/slave supports IRQ 0-15.
//
// Notes:       Here is the control flow of this function:
//              1. Check if IRQ is valid. If not, return EFI_INVALID_PARAMETER
//              2. If Irq >= 8, then Send EOI to slave controller.
//              3. Send EOI to master controller. (This is for both master /
//                 slave IRQs)
//              4. Return EFI_SUCCESS.
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS EndOfInterrupt (
    IN EFI_LEGACY_8259_PROTOCOL     *This,
    IN EFI_8259_IRQ                 Irq )
{
    if (Irq > 15) return EFI_INVALID_PARAMETER;

    if (Irq >= 8) {                     // If Slave, send EOI to slave first.
        // Send Slave EOI 
        IoWrite8 (LEGACY_8259_CONTROL_REGISTER_SLAVE, EOI_COMMAND);
    }
    // Send Master EOI 
    IoWrite8 (LEGACY_8259_CONTROL_REGISTER_MASTER, EOI_COMMAND);

    return EFI_SUCCESS;
}

EFI_LEGACY_8259_PROTOCOL gLegacy8259Protocol = {
    SetVectorBase,
    GetMask, SetMask,
    SetMode,
    GetVector,
    EnableIrq, DisableIrq,
    GetInterruptLine,
    EndOfInterrupt
};

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:   Initialize8259
//
// Description: Initialize 8259 Interrupt Controller.
//
// Input:       ImageHandle - Image handle for this driver
//              SystemTable - Pointer to the sytem table
//
// Output:      EFI_STATUS
//                  EFI_SUCCESS          - The legacy 8259 Protocols were
//                                         installed.  
//                  EFI_ALREADY_STARTED  - The legacy 8259 Protocol was passed
//                                         in that is already present in the
//                                         handle database.
//                  EFI_OUT_OF_RESOURCES - There was not enought memory in
//                                         pool to install all the protocols.
//
// Notes:       Here is the control flow of this function:
//              1. Initialize the Cpu setting vector bases.
//              2. Set Cpu Mode, mask, and trigger level.
//              3. Install Legacy 8259 Interface.
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS Initialize8259 (
    IN EFI_HANDLE        ImageHandle,
    IN EFI_SYSTEM_TABLE  *SystemTable )
{
    EFI_STATUS  Status;
    UINT16      Mask = 0xffff;      // Mask all interrupts.
    UINT16      EdgeLevel = 0x00;   // Set all edge.
    BOOLEAN IntState = CPULib_GetInterruptState();
 
    CPULib_DisableInterrupt();

    // Set the protected mode vectors for MASTER and SLAVE PICs
    SetVectorBase(0, MASTER_INTERRUPT_BASE, SLAVE_INTERRUPT_BASE);
    SetMode(0, Efi8259ProtectedMode, &Mask, &EdgeLevel);

    // Install the Legacy8259Protocol
    Status = pBS->InstallMultipleProtocolInterfaces( \
                                                &ImageHandle, \
                                                &gEfiLegacy8259ProtocolGuid, \
                                                &gLegacy8259Protocol, \
                                                NULL );
    if (EFI_ERROR(Status)) return Status;

    if(IntState)CPULib_EnableInterrupt();

    return EFI_SUCCESS;
}


// Protocols that are installed
DXE_PCH_PLATFORM_POLICY_PROTOCOL  mPchPolicyData        = { 0 };
PCH_DEVICE_ENABLING               mPchDeviceEnabling    = { 0 };
PCH_USB_CONFIG                    mPchUsbConfig         = { 0 };
PCH_PCI_EXPRESS_CONFIG            mPchPciExpressConfig  = { 0 };
PCH_SATA_CONFIG                   mPchSataConfig        = { 0 };
PCH_AZALIA_CONFIG                 mPchAzaliaConfig      = { 0 };
PCH_SMBUS_CONFIG                  mPchSmbusConfig       = { 0 };
PCH_MISC_PM_CONFIG                mPchMiscPmConfig      = { 0 };
PCH_IO_APIC_CONFIG                mPchIoApicConfig      = { 0 };
PCH_DEFAULT_SVID_SID              mPchDefaultSvidSid    = { 0 };
PCH_LOCK_DOWN_CONFIG              mPchLockDownConfig    = { 0 };
PCH_THERMAL_CONFIG                mPchThermalConfig     = { 0 };
PCH_LPC_HPET_CONFIG               mPchHpetConfig        = { 0 };
PCH_LPC_SIRQ_CONFIG               mSerialIrqConfig      = { 0 };
PCH_DMI_CONFIG                    mPchDmiConfig         = { 0 };
PCH_PWR_OPT_CONFIG                mPchPwrOptConfig      = { 0 };
PCH_MISC_CONFIG                   mPchMiscConfig        = { 0 };
PCH_AUDIO_DSP_CONFIG              mPchAudioDspConfig    = { 0 };
PCH_SERIAL_IO_CONFIG              mSerialIoConfig      = { 0 };

UINT8 mSmbusRsvdAddresses[DIMM_SLOT_NUM] = {
  DIMM1_SMBUS_ADDRESS,
  DIMM2_SMBUS_ADDRESS,
  DIMM3_SMBUS_ADDRESS,
  DIMM4_SMBUS_ADDRESS
};

PCH_PCIE_DEVICE_ASPM_OVERRIDE    mDevAspmOverride[] = {
  //
  // Intel PRO/Wireless
  //
  {0x8086, 0x422b, 0xff, 0xff, 0xff, PchPcieAspmL1, PchPcieL1L2Override, 0xFFFF, 0xFFFFFFFF},
  {0x8086, 0x422c, 0xff, 0xff, 0xff, PchPcieAspmL1, PchPcieL1L2Override, 0xFFFF, 0xFFFFFFFF},
  {0x8086, 0x4238, 0xff, 0xff, 0xff, PchPcieAspmL1, PchPcieL1L2Override, 0xFFFF, 0xFFFFFFFF},
  {0x8086, 0x4239, 0xff, 0xff, 0xff, PchPcieAspmL1, PchPcieL1L2Override, 0xFFFF, 0xFFFFFFFF},
  //
  // Intel WiMAX/WiFi Link
  //
  {0x8086, 0x0082, 0xff, 0xff, 0xff, PchPcieAspmL1, PchPcieL1L2Override, 0xFFFF, 0xFFFFFFFF},
  {0x8086, 0x0085, 0xff, 0xff, 0xff, PchPcieAspmL1, PchPcieL1L2Override, 0xFFFF, 0xFFFFFFFF},
  {0x8086, 0x0083, 0xff, 0xff, 0xff, PchPcieAspmL1, PchPcieL1L2Override, 0xFFFF, 0xFFFFFFFF},
  {0x8086, 0x0084, 0xff, 0xff, 0xff, PchPcieAspmL1, PchPcieL1L2Override, 0xFFFF, 0xFFFFFFFF},
  {0x8086, 0x0086, 0xff, 0xff, 0xff, PchPcieAspmL1, PchPcieL1L2Override, 0xFFFF, 0xFFFFFFFF},
  {0x8086, 0x0087, 0xff, 0xff, 0xff, PchPcieAspmL1, PchPcieL1L2Override, 0xFFFF, 0xFFFFFFFF},
  {0x8086, 0x0088, 0xff, 0xff, 0xff, PchPcieAspmL1, PchPcieL1L2Override, 0xFFFF, 0xFFFFFFFF},
  {0x8086, 0x0089, 0xff, 0xff, 0xff, PchPcieAspmL1, PchPcieL1L2Override, 0xFFFF, 0xFFFFFFFF},
  {0x8086, 0x008F, 0xff, 0xff, 0xff, PchPcieAspmL1, PchPcieL1L2Override, 0xFFFF, 0xFFFFFFFF},
  {0x8086, 0x0090, 0xff, 0xff, 0xff, PchPcieAspmL1, PchPcieL1L2Override, 0xFFFF, 0xFFFFFFFF},
  //
  // Intel Crane Peak WLAN NIC
  //
  {0x8086, 0x08AE, 0xff, PCI_CLASS_NETWORK, PCI_CLASS_NETWORK_OTHER, PchPcieAspmL1,       PchPcieL1L2Override,               0xFFFF, 0xFFFFFFFF},
  {0x8086, 0x08AF, 0xff, PCI_CLASS_NETWORK, PCI_CLASS_NETWORK_OTHER, PchPcieAspmL1,       PchPcieL1L2Override,               0xFFFF, 0xFFFFFFFF},
  //
  // Intel Crane Peak w/BT WLAN NIC
  //
  {0x8086, 0x0896, 0xff, PCI_CLASS_NETWORK, PCI_CLASS_NETWORK_OTHER, PchPcieAspmL1,       PchPcieL1L2Override,               0xFFFF, 0xFFFFFFFF},
  {0x8086, 0x0897, 0xff, PCI_CLASS_NETWORK, PCI_CLASS_NETWORK_OTHER, PchPcieAspmL1,       PchPcieL1L2Override,               0xFFFF, 0xFFFFFFFF},
  //
  // Intel Kelsey Peak WiFi, WiMax
  //
  {0x8086, 0x0885, 0xff, PCI_CLASS_NETWORK, PCI_CLASS_NETWORK_OTHER, PchPcieAspmL1,       PchPcieL1L2Override,               0xFFFF, 0xFFFFFFFF},
  {0x8086, 0x0886, 0xff, PCI_CLASS_NETWORK, PCI_CLASS_NETWORK_OTHER, PchPcieAspmL1,       PchPcieL1L2Override,               0xFFFF, 0xFFFFFFFF},
  //
  // Intel Centrino Wireless-N 105
  //
  {0x8086, 0x0894, 0xff, PCI_CLASS_NETWORK, PCI_CLASS_NETWORK_OTHER, PchPcieAspmL1,       PchPcieL1L2Override,               0xFFFF, 0xFFFFFFFF},
  {0x8086, 0x0895, 0xff, PCI_CLASS_NETWORK, PCI_CLASS_NETWORK_OTHER, PchPcieAspmL1,       PchPcieL1L2Override,               0xFFFF, 0xFFFFFFFF},
  //
  // Intel Centrino Wireless-N 135
  //
  {0x8086, 0x0892, 0xff, PCI_CLASS_NETWORK, PCI_CLASS_NETWORK_OTHER, PchPcieAspmL1,       PchPcieL1L2Override,               0xFFFF, 0xFFFFFFFF},
  {0x8086, 0x0893, 0xff, PCI_CLASS_NETWORK, PCI_CLASS_NETWORK_OTHER, PchPcieAspmL1,       PchPcieL1L2Override,               0xFFFF, 0xFFFFFFFF},
  //
  // Intel Centrino Wireless-N 2200
  //
  {0x8086, 0x0890, 0xff, PCI_CLASS_NETWORK, PCI_CLASS_NETWORK_OTHER, PchPcieAspmL1,       PchPcieL1L2Override,               0xFFFF, 0xFFFFFFFF},
  {0x8086, 0x0891, 0xff, PCI_CLASS_NETWORK, PCI_CLASS_NETWORK_OTHER, PchPcieAspmL1,       PchPcieL1L2Override,               0xFFFF, 0xFFFFFFFF},
  //
  // Intel Centrino Wireless-N 2230
  //
  {0x8086, 0x0887, 0xff, PCI_CLASS_NETWORK, PCI_CLASS_NETWORK_OTHER, PchPcieAspmL1,       PchPcieL1L2Override,               0xFFFF, 0xFFFFFFFF},
  {0x8086, 0x0888, 0xff, PCI_CLASS_NETWORK, PCI_CLASS_NETWORK_OTHER, PchPcieAspmL1,       PchPcieL1L2Override,               0xFFFF, 0xFFFFFFFF},
  //
  // Intel Centrino Wireless-N 6235
  //
  {0x8086, 0x088E, 0xff, PCI_CLASS_NETWORK, PCI_CLASS_NETWORK_OTHER, PchPcieAspmL1,       PchPcieL1L2Override,               0xFFFF, 0xFFFFFFFF},
  {0x8086, 0x088F, 0xff, PCI_CLASS_NETWORK, PCI_CLASS_NETWORK_OTHER, PchPcieAspmL1,       PchPcieL1L2Override,               0xFFFF, 0xFFFFFFFF},
  //
  // Intel CampPeak 2 Wifi
  //
  {0x8086, 0x08B5, 0xff, PCI_CLASS_NETWORK, PCI_CLASS_NETWORK_OTHER, PchPcieAspmL1,       PchPcieL1L2Override,               0xFFFF, 0xFFFFFFFF},
  {0x8086, 0x08B6, 0xff, PCI_CLASS_NETWORK, PCI_CLASS_NETWORK_OTHER, PchPcieAspmL1,       PchPcieL1L2Override,               0xFFFF, 0xFFFFFFFF},
  //
  // Intel WilkinsPeak 1 Wifi
  //
  {0x8086, 0x08B3, 0xff, PCI_CLASS_NETWORK, PCI_CLASS_NETWORK_OTHER, PchPcieAspmL1,       PchPcieL1L2AndL1SubstatesOverride, 0x0154, 0x00000003},
  {0x8086, 0x08B3, 0xff, PCI_CLASS_NETWORK, PCI_CLASS_NETWORK_OTHER, PchPcieAspmL1,       PchPcieL1SubstatesOverride,        0x0158, 0x00000003},
  {0x8086, 0x08B4, 0xff, PCI_CLASS_NETWORK, PCI_CLASS_NETWORK_OTHER, PchPcieAspmL1,       PchPcieL1L2AndL1SubstatesOverride, 0x0154, 0x00000003},
  {0x8086, 0x08B4, 0xff, PCI_CLASS_NETWORK, PCI_CLASS_NETWORK_OTHER, PchPcieAspmL1,       PchPcieL1SubstatesOverride,        0x0158, 0x00000003},
  //
  // Intel Wilkins Peak 2 Wifi
  //
  {0x8086, 0x08B1, 0xff, PCI_CLASS_NETWORK, PCI_CLASS_NETWORK_OTHER, PchPcieAspmL1,       PchPcieL1L2AndL1SubstatesOverride, 0x0154, 0x00000003},
  {0x8086, 0x08B1, 0xff, PCI_CLASS_NETWORK, PCI_CLASS_NETWORK_OTHER, PchPcieAspmL1,       PchPcieL1SubstatesOverride,        0x0158, 0x00000003},
  {0x8086, 0x08B2, 0xff, PCI_CLASS_NETWORK, PCI_CLASS_NETWORK_OTHER, PchPcieAspmL1,       PchPcieL1L2AndL1SubstatesOverride, 0x0154, 0x00000003},
  {0x8086, 0x08B2, 0xff, PCI_CLASS_NETWORK, PCI_CLASS_NETWORK_OTHER, PchPcieAspmL1,       PchPcieL1SubstatesOverride,        0x0158, 0x00000003},
  //
  // Intel Wilkins Peak PF Wifi
  //
  {0x8086, 0x08B0, 0xff, PCI_CLASS_NETWORK, PCI_CLASS_NETWORK_OTHER, PchPcieAspmL1,       PchPcieL1L2Override,               0xFFFF, 0xFFFFFFFF}

#if defined OEM_SB_PCIE_ASPM_OVERRIDE_TABLE
  OEM_SB_PCIE_ASPM_OVERRIDE_TABLE,
#endif
};

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure: InstallDxePchPlatformPolicy
//
// Description: Install Dxe Pch Platform Policy.
//
// Input:   ImageHandle -  Image handle
//          SystemTable -  Pointer to the system table
//
// Output:  Return Status based on errors that occurred while waiting for
//          time to expire.
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS
InstallDxePchPlatformPolicy (VOID)
{
  EFI_HANDLE              Handle;
  EFI_STATUS              Status;
  UINT8                   PortIndex;
  UINT8                   PortDataOut = 0;
  UINTN                   VariableSize;
  EFI_GUID                SetupGuid = SETUP_GUID;
  SETUP_DATA              SetupData;
  UINT32                  SetupDataAttributes = 0;
  UINT32                  PchSpiStrp9;
#if defined   iME_SUPPORT && iME_SUPPORT
  ME_BIOS_EXTENSION_SETUP MeBiosExtensionSetupData;
  EFI_GUID                EfiMeBiosExtensionSetupGuid    = EFI_ME_BIOS_EXTENSION_SETUP_GUID;
  CHAR16                  EfiMeBiosExtensionSetupName[]  = EFI_ME_BIOS_EXTENSION_SETUP_VARIABLE_NAME;
#endif
  UINT16                  GpioBase = 0;
  UINT16                  UsbPortLength[LPTH_USB_MAX_PHYSICAL_PORTS] = {USB_PORTS_LENGTH};
  UINT8                   UsbPortLocation[LPTH_USB_MAX_PHYSICAL_PORTS] = {USB_PORT_LOCATION_CONFIG};
  UINT8                   UsbOverCurrentMapping[LPTH_USB_MAX_PHYSICAL_PORTS] = {USB_OVER_CURRENT_MAPPING_SETTINGS};
  UINT8                   ULTUsbOverCurrentMapping[LPTLP_USB_MAX_PHYSICAL_PORTS]= {ULT_USB_OVER_CURRENT_MAPPING_SETTINGS};    //[EIP118480]
  UINT8                   Usb30OverCurrentMapping[LPTH_XHCI_MAX_USB3_PORTS] = {USB30_OVER_CURRENT_MAPPING_SETTINGS};
  UINT16                  LpcDeviceId;
  EFI_GLOBAL_NVS_AREA_PROTOCOL  *GlobalNvsArea;
  EFI_GUID                gEfiGlobalNvsAreaProtocolGuid = EFI_GLOBAL_NVS_AREA_PROTOCOL_GUID;
  PCH_SERIES              PchSeries = GetPchSeries();
  UINT32                  GbePortSel;
#if defined(RC_PORT_0) && (RC_PORT_0 == 1)
  BOOLEAN                 PcieRPMap[] = { RC_PORT_0, RC_PORT_1, RC_PORT_2, RC_PORT_3,
                                          RC_PORT_4, RC_PORT_5, RC_PORT_6, RC_PORT_7 };
#endif
  static EFI_GUID     guidHob = HOB_LIST_GUID;
  EFI_HOB_HANDOFF_INFO_TABLE *pHit;

  //
  //  Locate the Global NVS Protocol.
  //
  Status = pBS->LocateProtocol (
                  &gEfiGlobalNvsAreaProtocolGuid,
                  NULL,
                  &GlobalNvsArea
                  );
  ASSERT_EFI_ERROR (Status);

  LpcDeviceId = READ_PCI16_SB(R_PCH_LPC_DEVICE_ID);

  // Read the SB Platform Data
  VariableSize = sizeof (SB_PLATFORM_DATA);
  Status = pRS->GetVariable (
    L"SbPlatformData",
    &SetupGuid,
    NULL,
    &VariableSize,
    &SbPlatformData
    );

  VariableSize = sizeof (SETUP_DATA);
  Status = pRS->GetVariable (
    L"Setup",
    &SetupGuid,
    &SetupDataAttributes,
    &VariableSize,
    &SetupData
    );
  ASSERT_EFI_ERROR (Status);

  if ((READ_MEM16_RCRB(R_PCH_SPI_HSFS) & B_PCH_SPI_HSFS_FDV) == B_PCH_SPI_HSFS_FDV) {
    RESET_MEM32_RCRB(R_PCH_SPI_FDOC, (UINT32) (B_PCH_SPI_FDOC_FDSS_MASK | B_PCH_SPI_FDOC_FDSI_MASK));
    SET_MEM32_RCRB(R_PCH_SPI_FDOC, (UINT32) (V_PCH_SPI_FDOC_FDSS_PCHS | R_PCH_SPI_STRP9));
    PchSpiStrp9 = READ_MEM32_RCRB(R_PCH_SPI_FDOD);

    // Get GbePortSel
    GbePortSel = (UINT8)(( PchSpiStrp9 & B_PCH_SPI_STRP9_GBE_PCIE_PSC) >> N_PCH_SPI_STRP9_GBE_PCIE_PSC);
    
    // Get GbE slot number (zero based value) from descriptor and Get Subtractive decode enable bit from descriptor
    if ( PchSeries == PchLp ) {
        switch(GbePortSel) {
            case 0: 
                SbPlatformData.GbePciePortNum = 2; // Root Port 3
                break;
            case 1: 
                SbPlatformData.GbePciePortNum = 3; // Root Port 4
                break;
            case 2: // Root Port 5, lane 0
            case 3: // Root Port 5, lane 1
            case 4: // Root Port 5, lane 2
            case 5: // Root Port 5, lane 3
                SbPlatformData.GbePciePortNum = 4;
                break;
            default:
                SbPlatformData.GbePciePortNum = GbePortSel;
                break;
        }
    } else {
        SbPlatformData.GbePciePortNum = GbePortSel;
    }
                                  
    SbPlatformData.PcieSBDE = (UINT8)(( PchSpiStrp9 &
                                  B_PCH_SPI_STRP9_PCIE_SBDE_EN) >>
                                  N_PCH_SPI_STRP9_PCIE_SBDE_EN);
  } else {
    SbPlatformData.GbePciePortNum = 5;
    SbPlatformData.PcieSBDE = 0;
  }

  // General intialization
  mPchPolicyData.Revision             = DXE_PCH_PLATFORM_POLICY_PROTOCOL_REVISION_7;
  mPchPolicyData.BusNumber            = 0;
  mPchPolicyData.DeviceEnabling       = &mPchDeviceEnabling;
  mPchPolicyData.UsbConfig            = &mPchUsbConfig;
  mPchPolicyData.PciExpressConfig     = &mPchPciExpressConfig;
  mPchPolicyData.SataConfig           = &mPchSataConfig;
  mPchPolicyData.AzaliaConfig         = &mPchAzaliaConfig;
  mPchPolicyData.SmbusConfig          = &mPchSmbusConfig;
  mPchPolicyData.MiscPmConfig         = &mPchMiscPmConfig;
  mPchPolicyData.IoApicConfig         = &mPchIoApicConfig;
  mPchPolicyData.DefaultSvidSid       = &mPchDefaultSvidSid;
  mPchPolicyData.LockDownConfig       = &mPchLockDownConfig;
  mPchPolicyData.ThermalConfig        = &mPchThermalConfig;
  mPchPolicyData.HpetConfig           = &mPchHpetConfig;
  mPchPolicyData.SerialIrqConfig      = &mSerialIrqConfig;
  mPchPolicyData.DmiConfig            = &mPchDmiConfig;
  mPchPolicyData.PwrOptConfig         = &mPchPwrOptConfig;
  mPchPolicyData.MiscConfig           = &mPchMiscConfig;
  mPchPolicyData.AudioDspConfig       = &mPchAudioDspConfig;
  mPchPolicyData.SerialIoConfig       = &mSerialIoConfig;

  // PCH BIOS Spec Section 5.1.1 security recommendations,
  // Intel strongly recommends that BIOS sets the BIOS Interface Lock Down bit. Enabling this bit
  // will mitigate malicious software attempts to replace the system BIOS option ROM with its own code.
  // We always enable this as a platform policy.
  mPchPolicyData.LockDownConfig->BiosInterface = gSbSetupData->BiosInterfaceLock;

  // Intel strongly recommends that BIOS enables SMI_LOCK (B0:D31:F0:Offset A0h [4]=1)
  // which prevent writes to the Global SMI Enable bit (GLB_SMI_EN PMBASE + 30h Bit
  // [0]). Enabling this bit will mitigate malicious software attempts to gain system management
  // mode privileges.
  // We always enable this as a platform policy.
  mPchPolicyData.LockDownConfig->GlobalSmi    = gSbSetupData->SmiLock;

  mPchPolicyData.LockDownConfig->GpioLockDown = gSbSetupData->GpioLock;
  mPchPolicyData.LockDownConfig->RtcLock      = gSbSetupData->RtcLock;

  //
  // While BiosLock is enabled, BIOS can only be modified from SMM after ExitPmAuth.
  //
  mPchPolicyData.LockDownConfig->BiosLock     = gSbSetupData->BiosLock;
                                                                      // [EIP113678] >>
  pHit = GetEfiConfigurationTable(pST, &guidHob);
//  if (pHit && ((pHit->BootMode == BOOT_IN_RECOVERY_MODE) || \
//                    (pHit->BootMode == BOOT_ON_FLASH_UPDATE))) {
//    mPchPolicyData.LockDownConfig->BiosLock     = 0;
//  }
                                                                      // <<[EIP113678]
//  mPchPolicyData.LockDownConfig->PchBiosLockSwSmiNumber = SW_SMI_BIOS_LOCK;   // Deprecated from Revision 2 !!! DO NOT USE !!!
  mPchPolicyData.LockDownConfig->PchBiosLockIoTrapAddress = 0;      // Dynamic updated by IoTrap driver.

  // DeviceEnables
  mPchPolicyData.DeviceEnabling->Lan          = gSbSetupData->PchLan;
  if ((READ_MEM16_RCRB(R_PCH_SPI_HSFS) & B_PCH_SPI_HSFS_FDV) == B_PCH_SPI_HSFS_FDV) {
    if ((PchSpiStrp9 & B_PCH_SPI_STRP9_GBE_PCIE_EN) == 0) {
       mPchPolicyData.DeviceEnabling->Lan = PCH_DEVICE_DISABLE;
    }
  }
  mPchPolicyData.DeviceEnabling->Azalia       = gSbSetupData->PchAzalia;
  mPchPolicyData.DeviceEnabling->Sata         = gSbSetupData->PchSata;
  mPchPolicyData.DeviceEnabling->Smbus        = PCH_DEVICE_ENABLE;
  mPchPolicyData.DeviceEnabling->PciClockRun  = gSbSetupData->PchPciClockRun;
  mPchPolicyData.DeviceEnabling->Display      = gSbSetupData->PchDisplay;
  mPchPolicyData.DeviceEnabling->Crid         = gSbSetupData->PchEnableCrid;
  if (PchSeries == PchLp) {
    SbPlatformData.LPTType = 1;
    mPchPolicyData.DeviceEnabling->SerialIoDma    = gSbSetupData->LpssDmaEnable;
    mPchPolicyData.DeviceEnabling->SerialIoI2c0   = gSbSetupData->LpssI2c0Enable;
    mPchPolicyData.DeviceEnabling->SerialIoI2c1   = gSbSetupData->LpssI2c1Enable;
    mPchPolicyData.DeviceEnabling->SerialIoSpi0   = gSbSetupData->LpssSpi0Enable;
    mPchPolicyData.DeviceEnabling->SerialIoSpi1   = gSbSetupData->LpssSpi1Enable;
    mPchPolicyData.DeviceEnabling->SerialIoUart0  = gSbSetupData->LpssUart0Enable;
    mPchPolicyData.DeviceEnabling->SerialIoUart1  = gSbSetupData->LpssUart1Enable;
    mPchPolicyData.DeviceEnabling->SerialIoSdio   = gSbSetupData->LpssSdioEnable;
    mPchPolicyData.DeviceEnabling->AudioDsp   = gSbSetupData->ADspEnable;
	if(	mPchPolicyData.DeviceEnabling->AudioDsp == PCH_DEVICE_ENABLE)
		mPchPolicyData.DeviceEnabling->Azalia  = PCH_DEVICE_DISABLE;
  } else {
    SbPlatformData.LPTType = 0;
    mPchPolicyData.DeviceEnabling->SerialIoDma    = PCH_DEVICE_DISABLE;
    mPchPolicyData.DeviceEnabling->SerialIoI2c0   = PCH_DEVICE_DISABLE;
    mPchPolicyData.DeviceEnabling->SerialIoI2c1   = PCH_DEVICE_DISABLE;
    mPchPolicyData.DeviceEnabling->SerialIoSpi0   = PCH_DEVICE_DISABLE;
    mPchPolicyData.DeviceEnabling->SerialIoSpi1   = PCH_DEVICE_DISABLE;
    mPchPolicyData.DeviceEnabling->SerialIoUart0  = PCH_DEVICE_DISABLE;
    mPchPolicyData.DeviceEnabling->SerialIoUart1  = PCH_DEVICE_DISABLE;
    mPchPolicyData.DeviceEnabling->SerialIoSdio   = PCH_DEVICE_DISABLE;
    mPchPolicyData.DeviceEnabling->AudioDsp   = PCH_DEVICE_DISABLE;
  }
#if defined   iAMT_SUPPORT && iAMT_SUPPORT
  mPchPolicyData.UsbConfig->Ehci1Usbr         = PCH_DEVICE_DISABLE; //gSbSetupData->KvmEnabled;
  mPchPolicyData.UsbConfig->Ehci2Usbr         = PCH_DEVICE_DISABLE; //gSbSetupData->KvmEnabled;
#else
  mPchPolicyData.UsbConfig->Ehci1Usbr         = PCH_DEVICE_DISABLE;
  mPchPolicyData.UsbConfig->Ehci2Usbr         = PCH_DEVICE_DISABLE;
#endif

#if defined   iME_SUPPORT && iME_SUPPORT
  VariableSize = sizeof (MeBiosExtensionSetupData);
  Status = pRS->GetVariable (
                  EfiMeBiosExtensionSetupName,
                  &EfiMeBiosExtensionSetupGuid,
                  NULL,
                  &VariableSize,
                  &MeBiosExtensionSetupData );
  if (!EFI_ERROR (Status)) {
    mPchPolicyData.UsbConfig->Ehci1Usbr |= (MeBiosExtensionSetupData.KvmEnable & KVM_ENABLE);
    mPchPolicyData.UsbConfig->Ehci2Usbr |= (MeBiosExtensionSetupData.KvmEnable & KVM_ENABLE);
  }
#endif

  if (PchSeries == PchLp) {
    if ((gSbSetupData->PchUsb20[0] == 0) &&
        (gSbSetupData->PchUsb30Mode == 0)) {
      gDisableAllUsbControllers = TRUE;
    }
  } else {
    if ((gSbSetupData->PchUsb20[0] == 0) &&
        (gSbSetupData->PchUsb20[1] == 0) &&
        (gSbSetupData->PchUsb30Mode == 0)) {
      gDisableAllUsbControllers = TRUE;
    }
  }

  mPchPolicyData.UsbConfig->Usb20Settings[0].Enable = gSbSetupData->PchUsb20[0];
  if (PchSeries == PchLp) {
    mPchPolicyData.UsbConfig->Usb20Settings[1].Enable = PCH_DEVICE_DISABLE;
  } else {
    mPchPolicyData.UsbConfig->Usb20Settings[1].Enable = gSbSetupData->PchUsb20[1];
  }

  if ((mPchPolicyData.UsbConfig->Usb20Settings[0].Enable == PCH_DEVICE_DISABLE) &&
      (mPchPolicyData.UsbConfig->Usb20Settings[1].Enable == PCH_DEVICE_DISABLE)) {
    // Force enable EHCI#1 & 2 then disable them in InitSbRegsBeforeBoot()
    // if all USB controllers are disabled.
    // USB Device 29 configuration
    mPchPolicyData.UsbConfig->Usb20Settings[0].Enable = PCH_DEVICE_ENABLE;
    if (PchSeries != PchLp) {
      // USB Device 26 configuration
      mPchPolicyData.UsbConfig->Usb20Settings[1].Enable = PCH_DEVICE_ENABLE;
    }
  }

  mPchPolicyData.UsbConfig->UsbPerPortCtl = gSbSetupData->PchUsbPerPortCtl;

  for (PortIndex = 0; PortIndex < GetPchXhciMaxUsb3PortNum (); PortIndex++) {

    if (gSbSetupData->PchUsbPerPortCtl != PCH_DEVICE_DISABLE) {
      mPchPolicyData.UsbConfig->Port30Settings[PortIndex].Enable = gSbSetupData->PchUsb30Port[PortIndex];
    } else {
      mPchPolicyData.UsbConfig->Port30Settings[PortIndex].Enable = PCH_DEVICE_ENABLE;
    }
  }
  for (PortIndex = 0; PortIndex < GetPchUsbMaxPhysicalPortNum (); PortIndex++) {

    if (gSbSetupData->PchUsbPerPortCtl != PCH_DEVICE_DISABLE) {
      mPchPolicyData.UsbConfig->PortSettings[PortIndex].Enable = gSbSetupData->PchUsbPort[PortIndex];
    } else {
      mPchPolicyData.UsbConfig->PortSettings[PortIndex].Enable = PCH_DEVICE_ENABLE;
    }

    mPchPolicyData.UsbConfig->PortSettings[PortIndex].Usb20PortLength = UsbPortLength[PortIndex];
    mPchPolicyData.UsbConfig->PortSettings[PortIndex].Location = UsbPortLocation[PortIndex];

    if (PchSeries == PchH) {
      mPchPolicyData.UsbConfig->Usb20OverCurrentPins[PortIndex] = UsbOverCurrentMapping[PortIndex];    //[EIP118480]
      if (IS_PCH_LPT_LPC_DEVICE_ID_DESKTOP (LpcDeviceId)) {
        if (mPchPolicyData.UsbConfig->PortSettings[PortIndex].Location == PchUsbPortLocationBackPanel) {
          mPchPolicyData.UsbConfig->PortSettings[PortIndex].Usb20EyeDiagramTuningParam1 = 4; //Back Panel
        } else {
          mPchPolicyData.UsbConfig->PortSettings[PortIndex].Usb20EyeDiagramTuningParam1 = 3; //Front Panel        
        }

        if (mPchPolicyData.UsbConfig->PortSettings[PortIndex].Location == PchUsbPortLocationBackPanel) {
          if (mPchPolicyData.UsbConfig->PortSettings[PortIndex].Usb20PortLength < 0x80) {
            mPchPolicyData.UsbConfig->PortSettings[PortIndex].Usb20EyeDiagramTuningParam2 = 2; //Back Panel, less than 7.9"
          } else if (mPchPolicyData.UsbConfig->PortSettings[PortIndex].Usb20PortLength < 0x130) {
            mPchPolicyData.UsbConfig->PortSettings[PortIndex].Usb20EyeDiagramTuningParam2 = 3; //Back Panel, 8"-12.9"
          } else {
            mPchPolicyData.UsbConfig->PortSettings[PortIndex].Usb20EyeDiagramTuningParam2 = 4; //Back Panel, 13" onward
          }
        } else {
          mPchPolicyData.UsbConfig->PortSettings[PortIndex].Usb20EyeDiagramTuningParam2 = 2; //Front Panel
        }
      } else if (IS_PCH_LPT_LPC_DEVICE_ID_MOBILE (LpcDeviceId)) {
        if (mPchPolicyData.UsbConfig->PortSettings[PortIndex].Location == PchUsbPortLocationInternalTopology) {
          	mPchPolicyData.UsbConfig->PortSettings[PortIndex].Usb20EyeDiagramTuningParam1 = 5; // Internal Topology
        } else if (mPchPolicyData.UsbConfig->PortSettings[PortIndex].Location == PchUsbPortLocationDock) {
          	mPchPolicyData.UsbConfig->PortSettings[PortIndex].Usb20EyeDiagramTuningParam1 = 4; // Dock
        } else {
          	if (mPchPolicyData.UsbConfig->PortSettings[PortIndex].Usb20PortLength < 0x70) {
            	mPchPolicyData.UsbConfig->PortSettings[PortIndex].Usb20EyeDiagramTuningParam1 = 5; //Back Panel, less than 7"
          	} else {
            	mPchPolicyData.UsbConfig->PortSettings[PortIndex].Usb20EyeDiagramTuningParam1 = 6; //Back Panel, 7" onward
          	}
        }

        if (mPchPolicyData.UsbConfig->PortSettings[PortIndex].Location == PchUsbPortLocationInternalTopology) {
          	mPchPolicyData.UsbConfig->PortSettings[PortIndex].Usb20EyeDiagramTuningParam2 = 2; // Internal Topology
        } else if (mPchPolicyData.UsbConfig->PortSettings[PortIndex].Location == PchUsbPortLocationDock) {
          	if (mPchPolicyData.UsbConfig->PortSettings[PortIndex].Usb20PortLength < 0x50) {
            	mPchPolicyData.UsbConfig->PortSettings[PortIndex].Usb20EyeDiagramTuningParam2 = 1; //Dock, less than 5"
          	} else {
            	mPchPolicyData.UsbConfig->PortSettings[PortIndex].Usb20EyeDiagramTuningParam2 = 2; //Dock, 5" onward
          	}
        } else {
          	if (mPchPolicyData.UsbConfig->PortSettings[PortIndex].Usb20PortLength < 0x100) {
            	mPchPolicyData.UsbConfig->PortSettings[PortIndex].Usb20EyeDiagramTuningParam2 = 2; //Back Panel, less than 10"
          	} else {
            	mPchPolicyData.UsbConfig->PortSettings[PortIndex].Usb20EyeDiagramTuningParam2 = 3; //Back Panel, 10" onward
          	}
        }
      }
    } else if (PchSeries == PchLp) {
      mPchPolicyData.UsbConfig->Usb20OverCurrentPins[PortIndex] = ULTUsbOverCurrentMapping[PortIndex];    //[EIP118480]
      if ((mPchPolicyData.UsbConfig->PortSettings[PortIndex].Location == PchUsbPortLocationBackPanel) || 
          (mPchPolicyData.UsbConfig->PortSettings[PortIndex].Location == PchUsbPortLocationMiniPciE)) {
        if (mPchPolicyData.UsbConfig->PortSettings[PortIndex].Usb20PortLength < 0x70) {
          mPchPolicyData.UsbConfig->PortSettings[PortIndex].Usb20EyeDiagramTuningParam1 = 5; //Back Panel, less than 7"
        } else {
          mPchPolicyData.UsbConfig->PortSettings[PortIndex].Usb20EyeDiagramTuningParam1 = 6; //Back Panel, 7" onward
        }
      } else if (mPchPolicyData.UsbConfig->PortSettings[PortIndex].Location == PchUsbPortLocationDock) {
        mPchPolicyData.UsbConfig->PortSettings[PortIndex].Usb20EyeDiagramTuningParam1 = 4; // Dock
      } else {
        mPchPolicyData.UsbConfig->PortSettings[PortIndex].Usb20EyeDiagramTuningParam1 = 5; // Internal Topology
      } 

      if ((mPchPolicyData.UsbConfig->PortSettings[PortIndex].Location == PchUsbPortLocationBackPanel) || 
          (mPchPolicyData.UsbConfig->PortSettings[PortIndex].Location == PchUsbPortLocationMiniPciE)) {
        if (mPchPolicyData.UsbConfig->PortSettings[PortIndex].Usb20PortLength < 0x100) {
          mPchPolicyData.UsbConfig->PortSettings[PortIndex].Usb20EyeDiagramTuningParam2 = 2; //Back Panel, less than 10"
        } else {
          mPchPolicyData.UsbConfig->PortSettings[PortIndex].Usb20EyeDiagramTuningParam2 = 3; //Back Panel, 10" onward
        }
      } else if (mPchPolicyData.UsbConfig->PortSettings[PortIndex].Location == PchUsbPortLocationDock) {
        if (mPchPolicyData.UsbConfig->PortSettings[PortIndex].Usb20PortLength < 0x50) {
          mPchPolicyData.UsbConfig->PortSettings[PortIndex].Usb20EyeDiagramTuningParam2 = 1; //Dock, less than 5"
        } else {
          mPchPolicyData.UsbConfig->PortSettings[PortIndex].Usb20EyeDiagramTuningParam2 = 2; //Dock, 5" onward
        }
      } else {
        mPchPolicyData.UsbConfig->PortSettings[PortIndex].Usb20EyeDiagramTuningParam2 = 2; // Internal Topology
      }
    }
  }

  //
  // PCH BIOS Spec Section 13.1 xHCI controller options in Reference Code
  // Please refer to Table 13-1 in PCH BIOS Spec for USB Port Operation with no xHCI
  // pre-boot software.
  // Please refer to Table 13-2 in PCH BIOS Spec for USB Port Operation with xHCI
  // pre-boot software.
  //
  // The xHCI modes that available in BIOS are:
  // Disabled   - forces only USB 2.0 to be supported in the OS. The xHCI controller is turned off
  //              and hidden from the PCI space.
  // Enabled    - allows USB 3.0 to be supported in the OS. The xHCI controller is turned on. The
  //              shareable ports are routed to the xHCI controller. OS needs to provide drivers
  //              to support USB 3.0.
  // Auto       - This mode uses ACPI protocol to provide an option that enables the xHCI controller
  //              and reroute USB ports via the _OSC ACPI method call. Note, this mode switch requires
  //              special OS driver support for USB 3.0.
  // Smart Auto - This mode is similar to Auto, but it adds the capability to route the ports to xHCI
  //              or EHCI according to setting used in previous boots (for non-G3 boot) in the pre-boot
  //              environment. This allows the use of USB 3.0 devices prior to OS boot. Note, this mode
  //              switch requires special OS driver support for USB 3.0 and USB 3.0 software available
  //              in the pre-boot enviroment.
  // Recommendations:
  //  - If BIOS supports xHCI pre-boot driver then use Smart Auto mode as default
  //  - If BIOS does not support xHCI pre-boot driver then use AUTO mode as default
  //
  mPchPolicyData.UsbConfig->Usb30Settings.Mode             = gSbSetupData->PchUsb30Mode;

  //
  // Automatically disable EHCI when XHCI Mode is Enabled to save power.
  //
  if (mPchPolicyData.UsbConfig->Usb30Settings.Mode == 1) {
    mPchPolicyData.UsbConfig->Usb20Settings[0].Enable = PCH_DEVICE_DISABLE;
    if (PchSeries == PchH) {
      	mPchPolicyData.UsbConfig->Usb20Settings[1].Enable = PCH_DEVICE_DISABLE;
    }
  }

  if (gSbSetupData->PchUsb30Mode == 3) {
    mPchPolicyData.UsbConfig->Usb30Settings.PreBootSupport = 1;
  } else {
    mPchPolicyData.UsbConfig->Usb30Settings.PreBootSupport = gSbSetupData->PchUsb30PreBootSupport;
  }
//  mPchPolicyData.UsbConfig->Usb30Settings.XhciStreams      = gSbSetupData->XhciStreams;

  if (gSbSetupData->PchUsb30Mode == 4) {
    mPchPolicyData.UsbConfig->Usb30Settings.Mode           = 2;
    mPchPolicyData.UsbConfig->Usb30Settings.ManualMode     = PCH_DEVICE_ENABLE;
  } else {
    mPchPolicyData.UsbConfig->Usb30Settings.ManualMode     = PCH_DEVICE_DISABLE;
  }

  //
  // XhciIdleL1 can be set to disable for LPT-LP Ax stepping to workaround USB3 hot plug will fail after 1 hot plug removal. 
  //
  mPchPolicyData.UsbConfig->Usb30Settings.XhciIdleL1 = gSbSetupData->PchUsb30IdleL1;

  //
  // Btcg is for enabling/disabling trunk clock gating.
  //
  mPchPolicyData.UsbConfig->Usb30Settings.Btcg = gSbSetupData->PchUsb30Btcg;

  for (PortIndex = 0; PortIndex < GetPchUsbMaxPhysicalPortNum (); PortIndex++) {
    if (gSbSetupData->PchUsb20PinRoute == 1){
      mPchPolicyData.UsbConfig->Usb30Settings.ManualModeUsb20PerPinRoute[PortIndex] = 0;
    } else if (gSbSetupData->PchUsb20PinRoute == 2){
      mPchPolicyData.UsbConfig->Usb30Settings.ManualModeUsb20PerPinRoute[PortIndex] = 1;
    } else {
      mPchPolicyData.UsbConfig->Usb30Settings.ManualModeUsb20PerPinRoute[PortIndex] = gSbSetupData->ManualModeUsb20PerPinRoute[PortIndex];
    }
  }

  for (PortIndex = 0; PortIndex < GetPchXhciMaxUsb3PortNum (); PortIndex++) {
    if (gSbSetupData->PchUsb30PinEnable == 1){
      mPchPolicyData.UsbConfig->Usb30Settings.ManualModeUsb30PerPinEnable[PortIndex] = 0;
    } else if (gSbSetupData->PchUsb30PinEnable == 2){
      mPchPolicyData.UsbConfig->Usb30Settings.ManualModeUsb30PerPinEnable[PortIndex] = 1;
    } else {
      mPchPolicyData.UsbConfig->Usb30Settings.ManualModeUsb30PerPinEnable[PortIndex] = gSbSetupData->ManualModeUsb30PerPinEnable[PortIndex];
    }
    mPchPolicyData.UsbConfig->Usb30OverCurrentPins[PortIndex]   = Usb30OverCurrentMapping[PortIndex];
  }
  mPchPolicyData.UsbConfig->UsbPrecondition = gSbSetupData->UsbPrecondition;

#ifdef USB_PRECONDITION_ENABLE_FLAG
  ///
  /// Update Precondition option for S4 resume. 
  /// Skip Precondition for S4 resume in case this boot may not connect BIOS USB driver.
  /// If BIOS USB driver will be connected always for S4, then disable below update.
  /// To keep consistency during boot, must enabled or disabled below function in both PEI and DXE
  /// PlatformPolicyInit driver.
  ///
  if (mPchUsbConfig.UsbPrecondition == TRUE) {
    if (pHit && (pHit->BootMode == BOOT_ON_S4_RESUME)) {
      mPchUsbConfig.UsbPrecondition = FALSE;
      TRACE((-1, "BootMode is BOOT_ON_S4_RESUME, disable Precondition\n"));
    }
  }
#endif  // USB_PRECONDITION_ENABLE_FLAG

  GlobalNvsArea->Area->XhciMode = (UINT8)gSbSetupData->PchUsb30Mode;

  // PCI Express related settings from setup variable
  mPchPolicyData.PciExpressConfig->RootPortClockGating      = gSbSetupData->PcieClockGating;
  mPchPolicyData.PciExpressConfig->DevAspmOverride          = mDevAspmOverride;
  mPchPolicyData.PciExpressConfig->NumOfDevAspmOverride     = sizeof (mDevAspmOverride) / sizeof (PCH_PCIE_DEVICE_ASPM_OVERRIDE);
  mPchPolicyData.PciExpressConfig->RootPortFunctionSwapping = gSbSetupData->RootPortFunctionSwapping;

  mPchPolicyData.PciExpressConfig->TempRootPortBusNumMin  = PCH_PCIE_TEMP_RP_BUS_NUM_MIN;
  mPchPolicyData.PciExpressConfig->TempRootPortBusNumMax  = PCH_PCIE_TEMP_RP_BUS_NUM_MAX;

  for (PortIndex = 0; PortIndex < GetPchMaxPciePortNum (); PortIndex++) {
#if defined(RC_PORT_0) && (RC_PORT_0 == 1)
    if (PcieRPMap[PortIndex])
      mPchPolicyData.PciExpressConfig->RootPort[PortIndex].Enable                       = gSbSetupData->PcieRootPortEn[PortIndex];
    else
#endif
      mPchPolicyData.PciExpressConfig->RootPort[PortIndex].Enable                       = PCH_DEVICE_DISABLE;

    mPchPolicyData.PciExpressConfig->RootPort[PortIndex].SlotImplemented                = gSbSetupData->PcieRootPortEn[PortIndex];
    mPchPolicyData.PciExpressConfig->RootPort[PortIndex].FunctionNumber                 = PortIndex;
    mPchPolicyData.PciExpressConfig->RootPort[PortIndex].PhysicalSlotNumber             = PortIndex;
    mPchPolicyData.PciExpressConfig->RootPort[PortIndex].Aspm                           = gSbSetupData->PcieRootPortAspm[PortIndex];
    mPchPolicyData.PciExpressConfig->RootPort[PortIndex].PmSci                          = gSbSetupData->PcieRootPortPMCE[PortIndex];
    mPchPolicyData.PciExpressConfig->RootPort[PortIndex].HotPlug                        = gSbSetupData->PcieRootPortHPE[PortIndex];
    mPchPolicyData.PciExpressConfig->RootPort[PortIndex].AdvancedErrorReporting         = PCH_PCIE_ADVANCED_ERROR_REPORTING;
    mPchPolicyData.PciExpressConfig->RootPort[PortIndex].UnsupportedRequestReport       = gSbSetupData->PcieRootPortURE[PortIndex];
    mPchPolicyData.PciExpressConfig->RootPort[PortIndex].FatalErrorReport               = gSbSetupData->PcieRootPortFEE[PortIndex];
    mPchPolicyData.PciExpressConfig->RootPort[PortIndex].NoFatalErrorReport             = gSbSetupData->PcieRootPortNFE[PortIndex];
    mPchPolicyData.PciExpressConfig->RootPort[PortIndex].CorrectableErrorReport         = gSbSetupData->PcieRootPortCEE[PortIndex];
    mPchPolicyData.PciExpressConfig->RootPort[PortIndex].PmeInterrupt                   = PCH_PCIE_PME_INTERRUPT;
    mPchPolicyData.PciExpressConfig->RootPort[PortIndex].SystemErrorOnFatalError        = gSbSetupData->PcieRootPortSFE[PortIndex];
    mPchPolicyData.PciExpressConfig->RootPort[PortIndex].SystemErrorOnNonFatalError     = gSbSetupData->PcieRootPortSNE[PortIndex];
    mPchPolicyData.PciExpressConfig->RootPort[PortIndex].SystemErrorOnCorrectableError  = gSbSetupData->PcieRootPortSCE[PortIndex];
    mPchPolicyData.PciExpressConfig->RootPort[PortIndex].CompletionTimeout              = PCH_PCIE_COMPLETION_TIME_OUT;
    mPchPolicyData.PciExpressConfig->RootPort[PortIndex].L1Substates              		= gSbSetupData->PcieRootPortL1S[PortIndex];
  }

  if (SbPlatformData.PcieSBDE) {
    mPchPolicyData.PciExpressConfig->EnableSubDecode = gSbSetupData->PcieRootPortSBDE;
    mPchPolicyData.PciExpressConfig->PchPcieSbdePort = gSbSetupData->PcieSBDEPort;
  } else {
    mPchPolicyData.PciExpressConfig->EnableSubDecode = PCH_DEVICE_DISABLE;
    mPchPolicyData.PciExpressConfig->PchPcieSbdePort = 0;
  }

    // SATA configuration
  for (PortIndex = 0; PortIndex < GetPchMaxSataPortNum (); PortIndex++) {
    if ((gSbSetupData->SataInterfaceMode) == 0) { // for IDE
       mPchPolicyData.SataConfig->PortSettings[PortIndex].Enable = PCH_DEVICE_ENABLE;
    } else {
       mPchPolicyData.SataConfig->PortSettings[PortIndex].Enable = gSbSetupData->SataPort[PortIndex];
    }

    mPchPolicyData.SataConfig->PortSettings[PortIndex].HotPlug         	= gSbSetupData->SataHotPlug[PortIndex];
    mPchPolicyData.SataConfig->PortSettings[PortIndex].InterlockSw     	= gSbSetupData->SataMechanicalSw[PortIndex];
    mPchPolicyData.SataConfig->PortSettings[PortIndex].External        	= gSbSetupData->ExternalSata[PortIndex];
    mPchPolicyData.SataConfig->PortSettings[PortIndex].SolidStateDrive 	= gSbSetupData->SolidStateDrive[PortIndex];
    mPchPolicyData.SataConfig->PortSettings[PortIndex].SpinUp          	= gSbSetupData->SataSpinUp[PortIndex];
    mPchPolicyData.SataConfig->PortSettings[PortIndex].DevSlp          	= gSbSetupData->SataDevSlp[PortIndex];
    mPchPolicyData.SataConfig->PortSettings[PortIndex].EnableDitoConfig	= gSbSetupData->EnableDitoConfig[PortIndex];
    mPchPolicyData.SataConfig->PortSettings[PortIndex].DmVal           	= gSbSetupData->DmVal[PortIndex];
    mPchPolicyData.SataConfig->PortSettings[PortIndex].DitoVal         	= gSbSetupData->DitoVal[PortIndex];
  }
  GlobalNvsArea->Area->DVS0                  		= gSbSetupData->SataDevSlp[0];
  GlobalNvsArea->Area->DVS1                  		= gSbSetupData->SataDevSlp[1];
  GlobalNvsArea->Area->DVS2                  		= gSbSetupData->SataDevSlp[2];
  GlobalNvsArea->Area->DVS3                  		= gSbSetupData->SataDevSlp[3];

  mPchPolicyData.SataConfig->RaidAlternateId          = gSbSetupData->SataAlternateId;
  mPchPolicyData.SataConfig->Raid0                    = gSbSetupData->SataRaidR0;
  mPchPolicyData.SataConfig->Raid1                    = gSbSetupData->SataRaidR1;
  mPchPolicyData.SataConfig->Raid10                   = gSbSetupData->SataRaidR10;
  mPchPolicyData.SataConfig->Raid5                    = gSbSetupData->SataRaidR5;
  mPchPolicyData.SataConfig->Irrt                     = gSbSetupData->SataRaidIrrt;
  mPchPolicyData.SataConfig->OromUiBanner             = gSbSetupData->SataRaidOub;
  mPchPolicyData.SataConfig->HddUnlock                = gSbSetupData->SataHddlk;
  mPchPolicyData.SataConfig->LedLocate                = gSbSetupData->SataLedl;
  mPchPolicyData.SataConfig->IrrtOnly                 = gSbSetupData->SataRaidIooe;
  mPchPolicyData.SataConfig->SmartStorage             = gSbSetupData->SmartStorage; 
  mPchPolicyData.SataConfig->OromUiDelay              = gSbSetupData->OromUiDelay;
  mPchPolicyData.SataConfig->TestMode                 = gSbSetupData->SataTestMode; 
  mPchPolicyData.SataConfig->SalpSupport              = gSbSetupData->SalpSupport;
  mPchPolicyData.SataConfig->LegacyMode               = 1;//PCH_DEVICE_DISABLE;
  mPchPolicyData.SataConfig->SpeedSupport             = gSbSetupData->SataControllerSpeed;

  // AzaliaConfig
  mPchPolicyData.AzaliaConfig->Pme                    = gSbSetupData->AzaliaPme;
  mPchPolicyData.AzaliaConfig->DS                     = gSbSetupData->AzaliaDs;

  if (!IS_PCH_LPT_LPC_DEVICE_ID_MOBILE (LpcDeviceId)) {
    // These boards do not have KSC - set Azalia as "Not Docked"
    mPchPolicyData.AzaliaConfig->DA = 0;
  } else {
    // Call KSC lib to get dock status
#if defined INTEL_CRB_DXE_KSC_LIB_SUPPORT && INTEL_CRB_DXE_KSC_LIB_SUPPORT
#if defined CRB_EC_SUPPORT && CRB_EC_SUPPORT
    if (mPchPolicyData.AzaliaConfig->DS == PCH_DEVICE_ENABLE) {
      InitializeKscLib ();
      Status = SendKscCommand (KSC_C_DOCK_STATUS);
      if (Status == EFI_SUCCESS) {
        Status = ReceiveKscData ((UINT8 *) &PortDataOut);
        if (PortDataOut & KSC_B_DOCK_STATUS_ATTACH) {

          // Bit 0 is dock status: 1 = docked
          mPchPolicyData.AzaliaConfig->DA = 1;
        } else {
          mPchPolicyData.AzaliaConfig->DA = 0;
        }
       }
     }
#endif
#endif
  }

  mPchPolicyData.AzaliaConfig->AzaliaVerbTableNum = sizeof (HdaVerbTbl) / sizeof (PCH_AZALIA_VERB_TABLE);
  mPchPolicyData.AzaliaConfig->AzaliaVerbTable    = (PCH_AZALIA_VERB_TABLE*)HdaVerbTbl;
  mPchPolicyData.AzaliaConfig->ResetWaitTimer     = HDA_RESET_WAIT_TIMER;

  // Reserved SMBus Address
  mPchPolicyData.SmbusConfig->NumRsvdSmbusAddresses = DIMM_SLOT_NUM;
  mPchPolicyData.SmbusConfig->RsvdSmbusAddressTable = mSmbusRsvdAddresses;

  // MiscPm Configuration
  if (IS_PCH_LPT_LPC_DEVICE_ID_MOBILE (LpcDeviceId)) {
    mPchPolicyData.MiscPmConfig->PchDeepSxPol                       = gSbSetupData->DeepSxBattMode;
    if (gSbSetupData->BoardCapability == 0)
      mPchPolicyData.MiscPmConfig->PchDeepSxPol                     = PchDeepSxPolDisable;
  } else {
    mPchPolicyData.MiscPmConfig->PchDeepSxPol                       = gSbSetupData->DeepSxMode;
  }

                                        // [EIP82149]>
  // Intel(R) 8 Series Chipset Family Deep Sx and CPU Soft-Strap BIOS Override Co-Existence Issue.
  // If the soft-strap override feature is required and enabled, BIOS must disable Deep Sx functionality.
  if (READ_MEM32_RCRB(R_PCH_SPI_SRD) & B_PCH_SPI_SRD_SSD) {
    mPchPolicyData.MiscPmConfig->PchDeepSxPol                       = PchDeepSxPolDisable;
    SbPlatformData.HideDeepSx = 1;
  }
                                        // <[EIP82149]

  mPchPolicyData.MiscPmConfig->WakeConfig.PmeB0S5Dis                = PCH_DEVICE_DISABLE;
  mPchPolicyData.MiscPmConfig->WakeConfig.WolEnableOverride         = gSbSetupData->PchWakeOnLan;
  mPchPolicyData.MiscPmConfig->WakeConfig.Gp27WakeFromDeepSx        = gSbSetupData->Gp27Wake;
  mPchPolicyData.MiscPmConfig->WakeConfig.PcieWakeFromDeepSx        = gSbSetupData->PcieWake;
  mPchPolicyData.MiscPmConfig->PowerResetStatusClear.MeWakeSts      = ME_WAKE_STS;
  mPchPolicyData.MiscPmConfig->PowerResetStatusClear.MeHrstColdSts  = ME_HRST_COLD_STS;
  mPchPolicyData.MiscPmConfig->PowerResetStatusClear.MeHrstWarmSts  = ME_HRST_WARM_STS;
  mPchPolicyData.MiscPmConfig->PchSlpS3MinAssert                    = PCH_SLP_S3_MIN_ASSERT_VALUE;
  mPchPolicyData.MiscPmConfig->PchSlpS4MinAssert                    = gSbSetupData->SlpS4AssW;
  mPchPolicyData.MiscPmConfig->PchSlpSusMinAssert                   = PCH_SLP_SUS_MIN_ASSERT_VALUE;
  mPchPolicyData.MiscPmConfig->PchSlpAMinAssert                     = PCH_SLPA_MIN_ASSERT_VALUE;
  mPchPolicyData.MiscPmConfig->PchPwrCycDur                         = PCH_RESET_CYCLE_DURATION;  // 4-5 seconds (PCH default setting)
  mPchPolicyData.MiscPmConfig->SlpStrchSusUp                        = SLP_STRCH_SUS_UP;
  mPchPolicyData.MiscPmConfig->SlpLanLowDc                          = gSbSetupData->SlpLanLow;

  // Thermal configuration - Initialize policy to SETUP values.
  mPchPolicyData.ThermalConfig->ThermalAlertEnable.TselLock         = PCH_DEVICE_ENABLE;
//  mPchPolicyData.ThermalConfig->ThermalAlertEnable.TspcLock         = gSbSetupData->TSPCLock; // Deprecated from Revision 2 !!! DO NOT USE !!!
  mPchPolicyData.ThermalConfig->ThermalAlertEnable.TscLock          = PCH_DEVICE_ENABLE;
  mPchPolicyData.ThermalConfig->ThermalAlertEnable.TsmicLock        = PCH_DEVICE_ENABLE;
  mPchPolicyData.ThermalConfig->ThermalAlertEnable.PhlcLock         = PCH_DEVICE_ENABLE;

  mPchPolicyData.ThermalConfig->ThermalThrottling.TTLevels.SuggestedSetting = TTLEVELS_SUGGEST;
  mPchPolicyData.ThermalConfig->ThermalThrottling.TTLevels.PchCrossThrottling = gSbSetupData->PchCrossThrottling;
  mPchPolicyData.ThermalConfig->ThermalThrottling.DmiHaAWC.SuggestedSetting = DMIHAAWC_SUGGEST;
  mPchPolicyData.ThermalConfig->ThermalThrottling.SataTT.SuggestedSetting   = SATATT_SUGGEST;
  mPchPolicyData.ThermalConfig->PchHotLevel                         = gSbSetupData->PchHotLevel;;

  // PCH thermal device D31:F6 needs to be enabled for DPPM or validation.
  mPchPolicyData.ThermalConfig->ThermalDeviceEnable                 = gSbSetupData->ThermalDeviceEnable;

  if (mPchPolicyData.DeviceEnabling->Lan != PCH_DEVICE_ENABLE)
    SbPlatformData.GbePciePortNum = 0xff;

  // Set IOAPIC BDF
  mPchPolicyData.IoApicConfig->BdfValid = 1;
  mPchPolicyData.IoApicConfig->BusNumber = 0xF0;
  mPchPolicyData.IoApicConfig->DeviceNumber = 0x1F;
  mPchPolicyData.IoApicConfig->FunctionNumber = 0;
  mPchPolicyData.IoApicConfig->IoApicEntry24_39 = PCH_DEVICE_ENABLE;
  
  // Set HPET BDF
  mPchPolicyData.HpetConfig->BdfValid = 1;
  for (PortIndex=0; PortIndex<PCH_HPET_BDF_MAX; PortIndex++) {
     mPchPolicyData.HpetConfig->Hpet[PortIndex].BusNumber = 0xF0;
     mPchPolicyData.HpetConfig->Hpet[PortIndex].DeviceNumber = 0x0F;
     mPchPolicyData.HpetConfig->Hpet[PortIndex].FunctionNumber = 0;
  }

  // Initialize Serial IRQ Config
  mPchPolicyData.SerialIrqConfig->SirqEnable       = SIRQ_ENABLE;
  mPchPolicyData.SerialIrqConfig->StartFramePulse  = SIRQ_START_FRAME_PULSE;
  mPchPolicyData.SerialIrqConfig->SirqMode         = gSbSetupData->SirqMode;

  // Set these two policies to 0 for skip ProgramSvidSid(). (PchInit.c)
                                        // ULT_SUBID>>
  // SB SSID programming has done in ProgramSBSubId(). (SBPEI.c)

  mPchPolicyData.DefaultSvidSid->SubSystemVendorId = 0;
  mPchPolicyData.DefaultSvidSid->SubSystemId = 0;
                                        // <<ULT_SUBID

  //
  // DMI related settings
  //
  mPchPolicyData.DmiConfig->DmiAspm = gSbSetupData->PchDmiAspm;
  mPchPolicyData.DmiConfig->DmiExtSync = gSbSetupData->PchDmiExtSync;
  mPchPolicyData.DmiConfig->DmiIot = PCH_DEVICE_DISABLE;
  ///
  /// Power Optimizer related settings
  ///
  mPchPolicyData.PwrOptConfig->PchPwrOptDmi      = PCH_PWR_OPT_DMI;
  mPchPolicyData.PwrOptConfig->PchPwrOptGbe      = PCH_PWR_OPT_GBE;
  mPchPolicyData.PwrOptConfig->PchPwrOptXhci     = PCH_PWR_OPT_XHCI;
  mPchPolicyData.PwrOptConfig->PchPwrOptEhci     = PCH_PWR_OPT_EHCI;
  mPchPolicyData.PwrOptConfig->PchPwrOptSata     = PCH_PWR_OPT_SATA;
  mPchPolicyData.PwrOptConfig->MemCloseStateEn   = MEM_CLOSE_STATE_EN;
  mPchPolicyData.PwrOptConfig->InternalObffEn    = INTERNAL_OBFF_EN;
  mPchPolicyData.PwrOptConfig->ExternalObffEn    = PCH_DEVICE_DISABLE;   // De-feature OBFF from LPT-H/LPT-LP.(RC v1.2.0)
  mPchPolicyData.PwrOptConfig->NumOfDevLtrOverride  = NUM_OF_DEVLTR_OVERRID;
#if defined DEVLTR_OVERRID && DEVLTR_OVERRID == 1
  mPchPolicyData.PwrOptConfig->DevLtrOverride    = 1;
#else
  mPchPolicyData.PwrOptConfig->DevLtrOverride    = NULL;
#endif
  for (PortIndex = 0; PortIndex < GetPchMaxPciePortNum (); PortIndex++) {
    mPchPolicyData.PwrOptConfig->PchPwrOptPcie[PortIndex].LtrEnable             = gSbSetupData->PcieLtrEnable[PortIndex];
    //
    // De-feature OBFF from LPT-H/LPT-LP.
    // Doesn't enable Obff policy anymore.
    //
    mPchPolicyData.PwrOptConfig->PchPwrOptPcie[PortIndex].ObffEnable            = PCH_DEVICE_DISABLE;
  }

  GlobalNvsArea->Area->LTRE1  = gSbSetupData->PcieLtrEnable[0];
  GlobalNvsArea->Area->LTRE2  = gSbSetupData->PcieLtrEnable[1];
  GlobalNvsArea->Area->LTRE3  = gSbSetupData->PcieLtrEnable[2];
  GlobalNvsArea->Area->LTRE4  = gSbSetupData->PcieLtrEnable[3];
  GlobalNvsArea->Area->LTRE5  = gSbSetupData->PcieLtrEnable[4];
  GlobalNvsArea->Area->LTRE6  = gSbSetupData->PcieLtrEnable[5];
  GlobalNvsArea->Area->LTRE7  = gSbSetupData->PcieLtrEnable[6];
  GlobalNvsArea->Area->LTRE8  = gSbSetupData->PcieLtrEnable[7];

  mPchPolicyData.PwrOptConfig->LegacyDmaDisable  = LEGACY_DMA_DISABLE;
  for (PortIndex = 0; PortIndex < GetPchMaxPciePortNum (); PortIndex++) {
    if (PchSeries == PchLp) {
      mPchPolicyData.PwrOptConfig->PchPwrOptPcie[PortIndex].LtrMaxSnoopLatency                 = 0x1003;
      mPchPolicyData.PwrOptConfig->PchPwrOptPcie[PortIndex].LtrMaxNoSnoopLatency               = 0x1003;
    }
    if (PchSeries == PchH) {
      mPchPolicyData.PwrOptConfig->PchPwrOptPcie[PortIndex].LtrMaxSnoopLatency                 = 0x0846;
      mPchPolicyData.PwrOptConfig->PchPwrOptPcie[PortIndex].LtrMaxNoSnoopLatency               = 0x0846;
    }
    mPchPolicyData.PwrOptConfig->PchPwrOptPcie[PortIndex].LtrConfigLock                      = gSbSetupData->PcieLtrConfigLock[PortIndex];
    mPchPolicyData.PwrOptConfig->PchPwrOptPcie[PortIndex].SnoopLatencyOverrideMode           = gSbSetupData->PcieSnoopLatencyOverrideMode[PortIndex];
    mPchPolicyData.PwrOptConfig->PchPwrOptPcie[PortIndex].SnoopLatencyOverrideMultiplier     = gSbSetupData->PcieSnoopLatencyOverrideMultiplier[PortIndex];
    mPchPolicyData.PwrOptConfig->PchPwrOptPcie[PortIndex].SnoopLatencyOverrideValue          = gSbSetupData->PcieSnoopLatencyOverrideValue[PortIndex];
    mPchPolicyData.PwrOptConfig->PchPwrOptPcie[PortIndex].NonSnoopLatencyOverrideMode        = gSbSetupData->PcieNonSnoopLatencyOverrideMode[PortIndex];
    mPchPolicyData.PwrOptConfig->PchPwrOptPcie[PortIndex].NonSnoopLatencyOverrideMultiplier  = gSbSetupData->PcieNonSnoopLatencyOverrideMultiplier[PortIndex];
    mPchPolicyData.PwrOptConfig->PchPwrOptPcie[PortIndex].NonSnoopLatencyOverrideValue       = gSbSetupData->PcieNonSnoopLatencyOverrideValue[PortIndex];
  }
  /// 
  /// Interrupt Settings
  ///
  mPchPolicyData.IoApicConfig->IoApicEntry24_39 = PCH_DEVICE_ENABLE;

  ///
  /// Misc. Config
  ///
  /// FviSmbiosType is the SMBIOS OEM type (0x80 to 0xFF) defined in SMBIOS Type 14 - Group 
  /// Associations structure - item type. FVI structure uses it as SMBIOS OEM type to provide
  /// version information. The default value is type 221.
  ///
  mPchPolicyData.MiscConfig->FviSmbiosType  = 0xDD;

  ///
  /// DCI (Direct Connect Interface) Configuration
  ///
  mPchPolicyData.MiscConfig->DciEn  = PCH_DEVICE_DISABLE;

  mPchPolicyData.AudioDspConfig->AudioDspD3PowerGating  = gSbSetupData->ADspD3PG;
  GlobalNvsArea->Area->AudioDspCodec = (UINT8)gSbSetupData->ADspCodecSelect;
  mPchPolicyData.AudioDspConfig->AudioDspBluetoothSupport = gSbSetupData->ADspBluetooth;
  mPchPolicyData.AudioDspConfig->AudioDspAcpiMode  = gSbSetupData->ADspMode;   //1: ACPI mode, 0: PCI mode
  mPchPolicyData.AudioDspConfig->AudioDspAcpiInterruptMode = !(gSbSetupData->LpssIntMode); //1: ACPI mode, 0: PCI mode
  mPchPolicyData.AudioDspConfig->AudioDspBluetoothSupport  = PCH_DEVICE_DISABLE; // Bluetooth SCO disabled 

  mPchPolicyData.SerialIoConfig->SerialIoMode           = gSbSetupData->LpssMode;
  mPchPolicyData.SerialIoConfig->SerialIoInterruptMode  = gSbSetupData->LpssIntMode;
  mPchPolicyData.SerialIoConfig->Ddr50Support       = PCH_DEVICE_DISABLE;
  mPchPolicyData.SerialIoConfig->I2c0VoltageSelect  = gSbSetupData->I2C0VoltageSelect;
  mPchPolicyData.SerialIoConfig->I2c1VoltageSelect  = gSbSetupData->I2C1VoltageSelect;
  if(gSbSetupData->SensorHub){
  	GlobalNvsArea->Area->SDS0                  		= GlobalNvsArea->Area->SDS0 | BIT0;
  }
  if(gSbSetupData->TPD4){
  	GlobalNvsArea->Area->SDS0                  		= GlobalNvsArea->Area->SDS0 | BIT2;
  }
  if(gSbSetupData->AtmelTPL){
  	GlobalNvsArea->Area->SDS1                  		= GlobalNvsArea->Area->SDS1 | BIT0;
  }
  if(gSbSetupData->ElanTPL){
  	GlobalNvsArea->Area->SDS1                  		= GlobalNvsArea->Area->SDS1 | BIT1;
  }
  if(gSbSetupData->ElanTPD){
  	GlobalNvsArea->Area->SDS1                  		= GlobalNvsArea->Area->SDS1 | BIT2;
  }
  if(gSbSetupData->SynaTPD){
  	GlobalNvsArea->Area->SDS1                  		= GlobalNvsArea->Area->SDS1 | BIT3;
  }
  if(gSbSetupData->NtriTPL){
  	GlobalNvsArea->Area->SDS1                  		= GlobalNvsArea->Area->SDS1 | BIT5;
  }
  if(gSbSetupData->EetiTPL){
  	GlobalNvsArea->Area->SDS1                  		= GlobalNvsArea->Area->SDS1 | BIT6;
  }
  if(gSbSetupData->AlpsTPD){
  	GlobalNvsArea->Area->SDS1                  		= GlobalNvsArea->Area->SDS1 | BIT7;
  }
  if(gSbSetupData->CyprTPD){
  	GlobalNvsArea->Area->SDS1                  		= GlobalNvsArea->Area->SDS1 | BIT8;
  }
  if(gSbSetupData->LpssI2c0Enable){
  	GlobalNvsArea->Area->PEPC                  		= GlobalNvsArea->Area->PEPC | BIT5;
  }
  if(gSbSetupData->LpssI2c1Enable){
  	GlobalNvsArea->Area->PEPC                  		= GlobalNvsArea->Area->PEPC | BIT6;
  }
  if(gSbSetupData->LpssUart0Enable){
  	GlobalNvsArea->Area->PEPC                  		= GlobalNvsArea->Area->PEPC | BIT2;
  }
  if(gSbSetupData->LpssUart1Enable){
  	GlobalNvsArea->Area->PEPC                  		= GlobalNvsArea->Area->PEPC | BIT3;
  }
  if(gSbSetupData->LpssSdioEnable){
  	GlobalNvsArea->Area->PEPC                  		= GlobalNvsArea->Area->PEPC | BIT4;
  }
  if(gSbSetupData->ADspEnable){
  	GlobalNvsArea->Area->PEPC                  		= GlobalNvsArea->Area->PEPC | BIT9;
  }
  if(gSbSetupData->PchAzalia){
  	GlobalNvsArea->Area->PEPC                  		= GlobalNvsArea->Area->PEPC | BIT8;
  }
  if(gSbSetupData->PchUsb30Mode != 0){
  	GlobalNvsArea->Area->PEPC                  		= GlobalNvsArea->Area->PEPC | BIT7;
  }
  GlobalNvsArea->Area->DOSD                     = gSbSetupData->LpssDmaEnable;
  GlobalNvsArea->Area->SDS4                  		= gSbSetupData->Bluetooth0;
  GlobalNvsArea->Area->SDS5                  		= gSbSetupData->Bluetooth1;

  GlobalNvsArea->Area->SSH0                  		= gSbSetupData->I2C0SSH;
  GlobalNvsArea->Area->SSL0                  		= gSbSetupData->I2C0SSL;
  GlobalNvsArea->Area->SSD0                  		= gSbSetupData->I2C0SSD;
  GlobalNvsArea->Area->FMH0                  		= gSbSetupData->I2C0FMH;
  GlobalNvsArea->Area->FML0                  		= gSbSetupData->I2C0FML;
  GlobalNvsArea->Area->FMD0                  		= gSbSetupData->I2C0FMD;
  GlobalNvsArea->Area->FPH0                  		= gSbSetupData->I2C0FPH;
  GlobalNvsArea->Area->FPL0                  		= gSbSetupData->I2C0FPL;
  GlobalNvsArea->Area->FPD0                  		= gSbSetupData->I2C0FPD;
  GlobalNvsArea->Area->M0C0                  		= gSbSetupData->I2C0M0C0;
  GlobalNvsArea->Area->M1C0                  		= gSbSetupData->I2C0M1C0;
  GlobalNvsArea->Area->M2C0                  		= gSbSetupData->I2C0M2C0;

  GlobalNvsArea->Area->SSH1                  		= gSbSetupData->I2C1SSH;
  GlobalNvsArea->Area->SSL1                  		= gSbSetupData->I2C1SSL;
  GlobalNvsArea->Area->SSD1                  		= gSbSetupData->I2C1SSD;
  GlobalNvsArea->Area->FMH1                  		= gSbSetupData->I2C1FMH;
  GlobalNvsArea->Area->FML1                  		= gSbSetupData->I2C1FML;
  GlobalNvsArea->Area->FMD1                  		= gSbSetupData->I2C1FMD;
  GlobalNvsArea->Area->FPH1                  		= gSbSetupData->I2C1FPH;
  GlobalNvsArea->Area->FPL1                  		= gSbSetupData->I2C1FPL;
  GlobalNvsArea->Area->FPD1                  		= gSbSetupData->I2C1FPD;
  GlobalNvsArea->Area->M0C1                  		= gSbSetupData->I2C1M0C1;
  GlobalNvsArea->Area->M1C1                  		= gSbSetupData->I2C1M1C1;
  GlobalNvsArea->Area->M2C1                  		= gSbSetupData->I2C1M2C1;

  GlobalNvsArea->Area->M0C2                  		= gSbSetupData->SPI0M0C2;
  GlobalNvsArea->Area->M1C2                  		= gSbSetupData->SPI0M1C2;

  GlobalNvsArea->Area->M0C3                  		= gSbSetupData->SPI1M0C3;
  GlobalNvsArea->Area->M1C3                  		= gSbSetupData->SPI1M1C3;

  GlobalNvsArea->Area->M0C4                  		= gSbSetupData->UAR0M0C4;
  GlobalNvsArea->Area->M1C4                  		= gSbSetupData->UAR0M1C4;

  GlobalNvsArea->Area->M0C5                  		= gSbSetupData->UAR1M0C5;
  GlobalNvsArea->Area->M1C5                  		= gSbSetupData->UAR1M1C5;

  GlobalNvsArea->Area->ECTG                  		= gSbSetupData->ECTG;

  SbPlatformData.PchRid = READ_PCI8_SB(R_PCH_LPC_RID);

  // Save SB PLATFORM DATA variables.
  Status = pRS->SetVariable (
    L"SbPlatformData",
    &SetupGuid,
    EFI_VARIABLE_BOOTSERVICE_ACCESS,
    sizeof (SB_PLATFORM_DATA),
    &SbPlatformData
    );
  ASSERT_EFI_ERROR (Status);

#if (defined SB_SETUP_SUPPORT && SB_SETUP_SUPPORT) || \
    (defined OEM_SB_SETUP_SUPPORT && OEM_SB_SETUP_SUPPORT)
  SetupData.TrEnabled = gSbSetupData->TrEnabled;
#endif

  Status = pRS->SetVariable (
    L"Setup",
    &SetupGuid,
    SetupDataAttributes,
    sizeof (SETUP_DATA),
    &SetupData
    );
  ASSERT_EFI_ERROR (Status);

  Handle = NULL;
  Status = pBS->InstallMultipleProtocolInterfaces (
                  &Handle,
                  &gDxePchPlatformPolicyProtocolGuid,
                  &mPchPolicyData,
                  NULL
                  );
  ASSERT_EFI_ERROR (Status);

  return EFI_SUCCESS;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   RaidGetDriver
//
// Description: Get the the DriverImage Handle order to Start the 
//              Raid Controller handle 
//
// Input:       This -  EFI_BUS_SPECIFIC_DRIVER_OVERRIDE_PROTOCOL 
//              DriverImageHandle -  Driver Image Handle 
//
// Output:      DriverImageHandle - Returns the Driver Image handle 
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS RaidGetDriver(
	IN EFI_BUS_SPECIFIC_DRIVER_OVERRIDE_PROTOCOL *This,
	IN OUT EFI_HANDLE *DriverImageHandle
)
{
    UINTN       HandleCount;
    EFI_HANDLE  *HandleBuffer=NULL;
    UINTN       Index;
    EFI_LOADED_IMAGE_PROTOCOL   *LoadedImage;
    EFI_DRIVER_BINDING_PROTOCOL *DriverBindingProtocol=NULL;
    EFI_GUID    gEfiLoadedImageGuid  = EFI_LOADED_IMAGE_PROTOCOL_GUID;
    static UINT8       GuidCount=0;
    EFI_STATUS  Status;


    //
    // Validate the the Input parameters
    //
    if (DriverImageHandle == NULL) {
        return EFI_INVALID_PARAMETER;
    }

    //
    // If already Found all the images,proceed to return the data
    //
    if( !LoadedImageDone ) {
        
        LoadedImageDone = TRUE;

        //
        // Locate all the driver binding protocols
        //
        Status = pBS->LocateHandleBuffer (
                                      ByProtocol,
                                      &gEfiDriverBindingProtocolGuid,
                                      NULL,
                                      &HandleCount,
                                      &HandleBuffer
                                      );
    
        if (EFI_ERROR(Status)) {
            return Status;
        }
       
        for (Index = 0; Index < HandleCount; Index++) {            

            //
            // Get the Driver Binding Protocol Interface
            //
            Status = pBS->HandleProtocol(HandleBuffer[Index], 
                                        &gEfiDriverBindingProtocolGuid, 
                                        &DriverBindingProtocol);

            if(EFI_ERROR(Status) || DriverBindingProtocol == NULL){
                continue;
            }

            //
            // Get the LoadedImage Protocol from ImageHandle
            //
            Status = pBS->HandleProtocol(DriverBindingProtocol->ImageHandle, 
                                        &gEfiLoadedImageGuid, 
                                        &LoadedImage);

            if(EFI_ERROR(Status)){
                continue;
            }

            //
            //Compare the File guid with driver's needs to launched first
            //
            if(guidcmp(&(((MEDIA_FW_VOL_FILEPATH_DEVICE_PATH*)(LoadedImage->FilePath))->NameGuid)
                   , &GuidListCheckForRaid[GuidCount]) != 0) {
                continue;
            }

            //
            // Driver Image handle found. Add it in the Array
            //    
            ImageHandleArray[GuidCount] = DriverBindingProtocol->ImageHandle;
            GuidCount++;

            //
            // Start from the begining
            //
            Index = -1;

            //
            // Check All the Guid's are found. If found break the loop
            //
            if(GuidCount >= (sizeof(GuidListCheckForRaid)/sizeof(EFI_GUID) -1 )) {
                break;
            }            

        }

        //
        // Free the HandleBuffer Memory.
        //
        if (HandleBuffer) {
            pBS->FreePool (HandleBuffer);
        }

    }

    if(GuidCount == 0) {
        //
        // Image handle not found
        //    
        return EFI_NOT_FOUND;
    }

    //
    //If the *DriverImageHandle is NULL , return the first Imagehandle
    //            
    if( *DriverImageHandle == NULL ) {
        if(ImageHandleArray[0] != NULL) {
            *DriverImageHandle = ImageHandleArray[0];
            return EFI_SUCCESS;
        }
    } else {
        //
        // If *DriverImageHandle not NULL , return the next Imagehandle 
        // from the avilable image handle list 
        //
        for (Index = 0; Index < 4; Index++) {
            if( *DriverImageHandle == ImageHandleArray[Index] && (ImageHandleArray[Index+1] != NULL) ) {
                *DriverImageHandle = ImageHandleArray[Index+1];
                return EFI_SUCCESS;
            }
        }
    }

    //
    // No more Image handle found to handle the controller.
    //
    return EFI_NOT_FOUND;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:   ULTDsdtTableUpdate
//
// Description: Update the ULT DSDT table
//
// Input:       DsdtTable   - The table points to DSDT table.
//
// Output:      None
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID
ULTDsdtTableUpdate (
  IN ACPI_HDR   *DsdtTable
  )
{
  UINT8       *CurrPtr;
  UINT8       *DsdtPointer;
  UINT32      *Signature;
  UINT8       HexStr[36] = {'0','1','2','3','4','5','6','7','8','9','A','B','C','D','E','F','G','H',\
                            'I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z'};
  UINT8       ReturnVaule = 0;  
  UINT32      *SignaturePcieAdrs;                              //(EIP127410)>>
  UINT8       RPFN[6]; //Root Port Function Number     
  UINT8       i;                                               //(EIP127410)<<
  UINT8       RP06Done = 0;
#if LOW_POWER_S0_IDLE_CAPABLE == 1
  SETUP_DATA  *SetupData   = NULL;
  EFI_GUID    SetupGuid = SETUP_GUID;
  UINTN       VariableSize = sizeof(SETUP_DATA);
  EFI_STATUS  Status;
  UINT8       S0ID;

  Status = pBS->AllocatePool( EfiBootServicesData,
                              VariableSize,
                              &SetupData );
  ASSERT_EFI_ERROR(Status);

  Status = pRS->GetVariable( L"Setup",
                             &SetupGuid,
                             NULL,
                             &VariableSize,
                             SetupData );

  S0ID = SetupData->AcpiLowPowerS0Idle;

  if (SetupData != NULL) {
     pBS->FreePool(SetupData);
  }
#endif
                                                               //(EIP127410)>>
  for(i = 0 ; i < 6; i++){
    RPFN[i] = ((UINT8)(MmioRead32(SB_RCRB_BASE_ADDRESS + R_PCH_RCRB_RPFN) >> 4*i)) & 0x07;
    TRACE((-1, "\nRCBA RPFN%x = %x\n", i, RPFN[i]));
  }
                                                               //(EIP127410)<<
  CurrPtr = (UINT8 *) DsdtTable;
  for (DsdtPointer = CurrPtr;
       DsdtPointer <= (CurrPtr + ((EFI_ACPI_COMMON_HEADER *) CurrPtr)->Length);
       DsdtPointer++ )
  {
      Signature = (UINT32 *) DsdtPointer;
      switch(*Signature){
      //************** GPE event case **************
          case (EFI_SIGNATURE_32 ('X', 'L', '0', 'B')):
          case (EFI_SIGNATURE_32 ('X', 'L', '0', '3')):
          case (EFI_SIGNATURE_32 ('X', 'L', '0', '4')):
          case (EFI_SIGNATURE_32 ('X', 'L', '0', 'C')):
          case (EFI_SIGNATURE_32 ('X', 'L', '0', 'E')):
          case (EFI_SIGNATURE_32 ('X', 'L', '0', '5')):
      //*************************************************
          case (EFI_SIGNATURE_32 ('X', 'L', '0', '9')):
          case (EFI_SIGNATURE_32 ('X', 'L', '0', 'D')):
          case (EFI_SIGNATURE_32 ('X', 'L', '0', '1')):
          case (EFI_SIGNATURE_32 ('X', 'L', '0', '2')):
          case (EFI_SIGNATURE_32 ('X', 'L', '0', '6')):
          case (EFI_SIGNATURE_32 ('X', 'L', '0', '7')):
          case (EFI_SIGNATURE_32 ('X', 'L', '0', '8')):
               *DsdtPointer = '_';
               *(DsdtPointer + 2) = HexStr[6]; //6
               DsdtPointer = DsdtPointer + 3;
               break;
          case (EFI_SIGNATURE_32 ('X', 'L', '1', 'E')):
               *DsdtPointer = '_';
               *(DsdtPointer + 3) = HexStr[11]; //B
               DsdtPointer = DsdtPointer + 3;
               break;
      //************** Return vaule case **************
          case (EFI_SIGNATURE_32 ('G', 'P', 'R', 'W')):
               ReturnVaule = *(DsdtPointer + 5);
               switch (ReturnVaule){
                   case 0x03:
                   case 0x04:
                   case 0x05:
                   case 0x08:
                   case 0x09:
                   case 0x0B:
                   case 0x0C:
                   case 0x0D:
                   case 0x0E:
                        *(DsdtPointer + 5) = ReturnVaule + 0x60;
                        break;
                   default:
                        break;
               }

               DsdtPointer = DsdtPointer + 7;
               break;
      #if LOW_POWER_S0_IDLE_CAPABLE == 1
      //************** Change Dock case **************
          case (EFI_SIGNATURE_32 ('_', 'D', 'C', 'K')):
               if (S0ID == 1){
                  *DsdtPointer = HexStr[33]; //X
                  DsdtPointer = DsdtPointer + 3;
               }
               break;
      #endif
      //************** PCIE Adress ****************            //(EIP127410)>>
          case (EFI_SIGNATURE_32 ('R', 'P', '0', '1')):
               if (gSbSetupData->RootPortFunctionSwapping){
                  DsdtPointer = DsdtPointer + 5;
                  SignaturePcieAdrs = (UINT32 *) DsdtPointer;
                  switch(*SignaturePcieAdrs){
                    case (EFI_SIGNATURE_32 ('_', 'A', 'D', 'R')):
                      DsdtPointer = DsdtPointer + 5;
                      *DsdtPointer = RPFN[0];
                      break;
                  default:
                      break;
                  }
               }
               break;
          case (EFI_SIGNATURE_32 ('R', 'P', '0', '2')):
               if (gSbSetupData->RootPortFunctionSwapping){
                  DsdtPointer = DsdtPointer + 5;
                  SignaturePcieAdrs = (UINT32 *) DsdtPointer;
                  switch(*SignaturePcieAdrs){
                    case (EFI_SIGNATURE_32 ('_', 'A', 'D', 'R')):
                      DsdtPointer = DsdtPointer + 5;
                      *DsdtPointer = RPFN[1];
                      break;
                  default:
                      break;
                  }
               }
               break;
          case (EFI_SIGNATURE_32 ('R', 'P', '0', '3')):
               if (gSbSetupData->RootPortFunctionSwapping){
                  DsdtPointer = DsdtPointer + 5;
                  SignaturePcieAdrs = (UINT32 *) DsdtPointer;
                  switch(*SignaturePcieAdrs){
                    case (EFI_SIGNATURE_32 ('_', 'A', 'D', 'R')):
                      DsdtPointer = DsdtPointer + 5;
                      *DsdtPointer = RPFN[2];
                      break;
                  default:
                      break;
                  }
               }
               break;
          case (EFI_SIGNATURE_32 ('R', 'P', '0', '4')):
               if (gSbSetupData->RootPortFunctionSwapping){
                  DsdtPointer = DsdtPointer + 5;
                  SignaturePcieAdrs = (UINT32 *) DsdtPointer;
                  switch(*SignaturePcieAdrs){
                    case (EFI_SIGNATURE_32 ('_', 'A', 'D', 'R')):
                      DsdtPointer = DsdtPointer + 5;
                      *DsdtPointer = RPFN[3];
                      break;
                  default:
                      break;
                  }
               }
               break;
          case (EFI_SIGNATURE_32 ('R', 'P', '0', '5')):
               if (gSbSetupData->RootPortFunctionSwapping){
                  DsdtPointer = DsdtPointer + 5;
                  SignaturePcieAdrs = (UINT32 *) DsdtPointer;
                  switch(*SignaturePcieAdrs){
                    case (EFI_SIGNATURE_32 ('_', 'A', 'D', 'R')):
                      DsdtPointer = DsdtPointer + 5;
                      *DsdtPointer = RPFN[4];
                      break;
                  default:
                      break;
                  }
               }
               break;
          case (EFI_SIGNATURE_32 ('R', 'P', '0', '6')):
               if (gSbSetupData->RootPortFunctionSwapping){
                  DsdtPointer = DsdtPointer + 5;
                  SignaturePcieAdrs = (UINT32 *) DsdtPointer;
                  switch(*SignaturePcieAdrs){
                    case (EFI_SIGNATURE_32 ('_', 'A', 'D', 'R')):
                      DsdtPointer = DsdtPointer + 5;
                      *DsdtPointer = RPFN[5];
                      break;
                  default:
                      break;
                  }
               }
               while(RP06Done != 1){
                 DsdtPointer++;
                 SignaturePcieAdrs = (UINT32 *) DsdtPointer;

                 switch(*SignaturePcieAdrs){
                   case (EFI_SIGNATURE_32 ('A', 'R', '0', '9')):
                     *(DsdtPointer + 3) = HexStr[8]; //8
                     DsdtPointer = DsdtPointer + 3;
                     break;

                   case (EFI_SIGNATURE_32 ('P', 'R', '0', '9')):
                     *(DsdtPointer + 3) = HexStr[8]; //8
                     DsdtPointer = DsdtPointer + 3;
                     RP06Done = 1;
                     break;

                   default:
                     break;
                 }
               }  
               break;                                          //(EIP127410)<<
          default:
               break;
      }// end switch      
  }// end of for loop
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:   DsdtTableUpdate
//
// Description: Update the DSDT table
//
// Input:       DsdtTable   - The table points to DSDT table.
//
// Output:      None
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID
DsdtTableUpdate (
  IN ACPI_HDR   *DsdtTable
  )
{
  UINT8       *CurrPtr;
  UINT8       *DsdtPointer;
  UINT32      *Signature;
  UINT8       HexStr[36] = {'0','1','2','3','4','5','6','7','8','9','A','B','C','D','E','F','G','H',\
                            'I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z'};
  UINT8       ReturnVaule = 0;  
  UINT32      *SignaturePcieAdrs;                              //(EIP127410)>>
  UINT8       RPFN[8]; //Root Port Function Number     
  UINT8       i;                                               //(EIP127410)<<

  CurrPtr = (UINT8 *) DsdtTable;
                                                               //(EIP127410)>>
  for(i = 0 ; i < 8; i++){
    RPFN[i] = ((UINT8)(MmioRead32(SB_RCRB_BASE_ADDRESS + R_PCH_RCRB_RPFN) >> 4*i)) & 0x07;
    TRACE((-1, "\nRCBA RPFN%x = %x\n", i, RPFN[i]));
  }
                                                               //(EIP127410)<<
  for (DsdtPointer = CurrPtr;
       DsdtPointer <= (CurrPtr + ((EFI_ACPI_COMMON_HEADER *) CurrPtr)->Length);
       DsdtPointer++ )
  {
      Signature = (UINT32 *) DsdtPointer;
      switch(*Signature){
      //************** GPE event case **************
          case (EFI_SIGNATURE_32 ('X', 'L', '0', 'B')):
          case (EFI_SIGNATURE_32 ('X', 'L', '0', '3')):
          case (EFI_SIGNATURE_32 ('X', 'L', '0', '4')):
          case (EFI_SIGNATURE_32 ('X', 'L', '0', 'C')):
          case (EFI_SIGNATURE_32 ('X', 'L', '0', 'E')):
          case (EFI_SIGNATURE_32 ('X', 'L', '0', '5')):
      //*************************************************
          case (EFI_SIGNATURE_32 ('X', 'L', '0', '9')):
          case (EFI_SIGNATURE_32 ('X', 'L', '0', 'D')):
          case (EFI_SIGNATURE_32 ('X', 'L', '0', '1')):
          case (EFI_SIGNATURE_32 ('X', 'L', '0', '2')):
          case (EFI_SIGNATURE_32 ('X', 'L', '0', '6')):
          case (EFI_SIGNATURE_32 ('X', 'L', '0', '7')):
          case (EFI_SIGNATURE_32 ('X', 'L', '0', '8')):
               *DsdtPointer = '_';
               DsdtPointer = DsdtPointer + 3;
               break;
          case (EFI_SIGNATURE_32 ('X', 'L', '1', 'E')):
               *DsdtPointer = '_';
               DsdtPointer = DsdtPointer + 3;
               break;
      //************** PCIE Adress ****************            //(EIP127410)>>
          case (EFI_SIGNATURE_32 ('R', 'P', '0', '1')):
               if (gSbSetupData->RootPortFunctionSwapping){
                  DsdtPointer = DsdtPointer + 5;
                  SignaturePcieAdrs = (UINT32 *) DsdtPointer;
                  switch(*SignaturePcieAdrs){
                    case (EFI_SIGNATURE_32 ('_', 'A', 'D', 'R')):
                      DsdtPointer = DsdtPointer + 5;
                      *DsdtPointer = RPFN[0];
                      break;
                  default:
                      break;
                  }
               }
               break;
          case (EFI_SIGNATURE_32 ('R', 'P', '0', '2')):
               if (gSbSetupData->RootPortFunctionSwapping){
                  DsdtPointer = DsdtPointer + 5;
                  SignaturePcieAdrs = (UINT32 *) DsdtPointer;
                  switch(*SignaturePcieAdrs){
                    case (EFI_SIGNATURE_32 ('_', 'A', 'D', 'R')):
                      DsdtPointer = DsdtPointer + 5;
                      *DsdtPointer = RPFN[1];
                      break;
                  default:
                      break;
                  }
               }
               break;
          case (EFI_SIGNATURE_32 ('R', 'P', '0', '3')):
               if (gSbSetupData->RootPortFunctionSwapping){
                  DsdtPointer = DsdtPointer + 5;
                  SignaturePcieAdrs = (UINT32 *) DsdtPointer;
                  switch(*SignaturePcieAdrs){
                    case (EFI_SIGNATURE_32 ('_', 'A', 'D', 'R')):
                      DsdtPointer = DsdtPointer + 5;
                      *DsdtPointer = RPFN[2];
                      break;
                  default:
                      break;
                  }
               }
               break;
          case (EFI_SIGNATURE_32 ('R', 'P', '0', '4')):
               if (gSbSetupData->RootPortFunctionSwapping){
                  DsdtPointer = DsdtPointer + 5;
                  SignaturePcieAdrs = (UINT32 *) DsdtPointer;
                  switch(*SignaturePcieAdrs){
                    case (EFI_SIGNATURE_32 ('_', 'A', 'D', 'R')):
                      DsdtPointer = DsdtPointer + 5;
                      *DsdtPointer = RPFN[3];
                      break;
                  default:
                      break;
                  }
               }
               break;
          case (EFI_SIGNATURE_32 ('R', 'P', '0', '5')):
               if (gSbSetupData->RootPortFunctionSwapping){
                  DsdtPointer = DsdtPointer + 5;
                  SignaturePcieAdrs = (UINT32 *) DsdtPointer;
                  switch(*SignaturePcieAdrs){
                    case (EFI_SIGNATURE_32 ('_', 'A', 'D', 'R')):
                      DsdtPointer = DsdtPointer + 5;
                      *DsdtPointer = RPFN[4];
                      break;
                  default:
                      break;
                  }
               }
               break;
          case (EFI_SIGNATURE_32 ('R', 'P', '0', '6')):
               if (gSbSetupData->RootPortFunctionSwapping){
                  DsdtPointer = DsdtPointer + 5;
                  SignaturePcieAdrs = (UINT32 *) DsdtPointer;
                  switch(*SignaturePcieAdrs){
                    case (EFI_SIGNATURE_32 ('_', 'A', 'D', 'R')):
                      DsdtPointer = DsdtPointer + 5;
                      *DsdtPointer = RPFN[5];
                      break;
                  default:
                      break;
                  }
               }
               break;
          case (EFI_SIGNATURE_32 ('R', 'P', '0', '7')):
               if (gSbSetupData->RootPortFunctionSwapping){
                  DsdtPointer = DsdtPointer + 5;
                  SignaturePcieAdrs = (UINT32 *) DsdtPointer;
                  switch(*SignaturePcieAdrs){
                    case (EFI_SIGNATURE_32 ('_', 'A', 'D', 'R')):
                      DsdtPointer = DsdtPointer + 5;
                      *DsdtPointer = RPFN[6];
                      break;
                  default:
                      break;
                  }
               }
               break;
          case (EFI_SIGNATURE_32 ('R', 'P', '0', '8')):
               if (gSbSetupData->RootPortFunctionSwapping){
                  DsdtPointer = DsdtPointer + 5;
                  SignaturePcieAdrs = (UINT32 *) DsdtPointer;
                  switch(*SignaturePcieAdrs){
                    case (EFI_SIGNATURE_32 ('_', 'A', 'D', 'R')):
                      DsdtPointer = DsdtPointer + 5;
                      *DsdtPointer = RPFN[7];
                      break;
                  default:
                      break;
                  }
               }
               break;                                          //(EIP127410)<<
          default:
               break;
      }// end switch      
  }// end of for loop
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
