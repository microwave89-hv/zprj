//**********************************************************************
//**********************************************************************
//**                                                                  **
//**        (C)Copyright 1985-2012, American Megatrends, Inc.         **
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
// $Header: /Alaska/Projects/Intel/Haswell/LynxPoint_SharkBay-DT_Crb_1AQQW/Core/EM/PCI/PciBus.c 3     12/19/12 7:07a Wesleychen $
//
// $Revision: 3 $
//
// $Date: 12/19/12 7:07a $
//**********************************************************************
// Revision History
// ----------------
// $Log: /Alaska/Projects/Intel/Haswell/LynxPoint_SharkBay-DT_Crb_1AQQW/Core/EM/PCI/PciBus.c $
// 
// 3     12/19/12 7:07a Wesleychen
// Update to rev#152 for EIP107491.
// 
// 152   11/26/12 4:23p Yakovlevs
// [TAG]  		EIP107491 
// [Category]  	Bug Fix
// [Severity]  	Minor
// [Symptom]  	PciBus can not detect some pcie card (LSI).
// [RootCause]  	A config write is required in order for the device to
// re-capture the Bus number
// [Solution]  	Add a dummy config write to VID/DID register offset 0
// [Files]  		PciBus.c
// 
// 150   9/20/12 12:15p Yakovlevs
// [TAG]  		EIP100249
// [Category]  	New Feature
// [Description]  	Token to set PCIE capabilities  Clock PM default value.
// Clock PM Settings was excluded for GEN1 devices.
// 
// [Files]  		PciBus.c
// 
// 149   9/12/12 11:55a Yakovlevs
// Restoring overrided Artem's changes.
// 
// 148   9/12/12 11:51a Yakovlevs
// [TAG]  		EIP99393
// [Category]  	Bug Fix
// [Severity]  	Normal
// [Symptom]  	I350 Powerville LOM UEFI driver is not loading
// [RootCause]  	Issue in invocation following function.
// DoubleCheckOpRom((VOID*)&PciRomHdr, &Pcir);
// variable PciRomHd was defined as buffer in stack but function requeres
// actual pointer at the ROM
// [Solution]  	Replace Parameters passing from PciRomHd to (base + trs)
// [Files]  		PciBus,c
// 
// 146   9/10/12 12:51p Yakovlevs
// [TAG]  		EIP93341
// [Category]  	Improvement
// [Description]  	Preserve PCI DEV/LNK/SLT control register in S3 resume
// path.
// [Files]  		PciBus.c  PciBus.sd PciBus.uni PciSetup.h PciPort.c
// 
// 145   7/20/12 12:50p Artems
// [TAG]  		EIP N/A
// [Category]  	Improvement
// [Description]  	Call GetOptRom before installing PciIO protocol, so ROM
// pointer has valid vaule
// [Files]  		Pcibus.c
// 
// 144   7/13/12 5:14p Yakovlevs
// [TAG]  		EIP94699
// [Category]  	Bug Fix
// [Severity]  	Minor
// [Symptom]  	Coding error in PciBus.c
// [RootCause]  	Typo
// [Solution]  	fixing typo replace tBarMmio64 with tBarMmio64pf
// [Files]  		PciBus.c
// 
// 143   6/26/12 5:53p Yakovlevs
// [TAG]  		EIP93341 
// [Category]  	Improvement
// [Description]  	Preserve PCI DEV/LNK/SLT control register in S3 resume
// path.
// [Files]  		PciBus.c
// 
// 142   6/20/12 12:25p Olegi
// [TAG]  		EIP93141
// [Description]  	PCI_IO_PROTOCOL.Attributes may fail
// 
// 141   5/22/12 4:49p Yakovlevs
// Removing wrong comment
// 
// 140   5/21/12 3:39p Artems
// [TAG]  		EIP86097
// [Category]  	Improvement
// [Description]  	Separate control for loading UEFI Oprom Driver
// Added porting hook to CsmOptOut to enable/disable UEFI
// OpROM execution for particular PCI device, identified by PCI handle
// [Files]  		PciBus.c CsmOptOut.c
// 
// 139   5/01/12 5:07p Yakovlevs
// [TAG]  		EIP84986
// [Category]  	Bug Fix
// [Severity]  	Normal
// [Symptom]  	Yellow mark issue in windows device manager on
// PCIe slots if only 2 CPU for potter city platform.
// [RootCause]  	For multy root system where root socets partialy
// populated SDL data interfered with 
// Actual Hardware configuration.
// [Solution]  	Allow control flow keep going when certain 
// ERROR_STATUS received.
// [Files]  		PciBus.c; PciHostBridge.c
// 
// 138   5/01/12 4:25p Yakovlevs
// [TAG]  		EIP88259 
// [Category]  	Improvement
// [Description]  	Have valid PCI handle before processing OpROM
// [Files]  		PciBus.c
// 
// 137   4/10/12 10:16a Yakovlevs
// [TAG]  		EIP87005
// [Category]  	Bug Fix
// [Symptom]  	Aptio4.6.5.3...SCT Execution test failed.(PCI Bus Support
// Test\PCI IO Protocol Test)
// [RootCause]  	In DevAttributes() function we have masking 
// Platform specific attributes since they don't affect 
// functionality but may hung the system when somebody ties 
// to set or reset it.
// [Solution]  	Remove code masking attributes  0x2000 0x4000
// [Files]  		PciBus.c
// 
// 136   12/19/11 2:08p Yakovlevs
// [TAG]  		EIP73172
// [Category]  	Bug Fix
// [RootCause]  	It tires to read the PCI ROM header in DWORD unit.
// However the size of PCI_STD_OPT_ROM_HEADER is 26 which can not be
// divided by 4 without reminders.
// After this change it will only read 24 bytes, the last 2 bytes
// (PCI_STD_OPT_ROM_HEADER.PcirOffset) will not be read.
// The code then read memory from the PcirOffset pointer which is
// undefined....
// 
// [Solution]  	Roll back changes keeping 1 Byte access to the opt ROM
// header
// [Files]  		PCiBus.c
// 
// 135   12/19/11 11:06a Yakovlevs
// 
// 134   12/19/11 11:05a Yakovlevs
// [TAG]  		EIP73172
// [Description]  	(JPJP000D) It stops POST Code 94h, when connected PCIE
// media read/write device.
// [Files]  		Added 4 byte alligned structure definition to handle 4 byte
// header read.
// 
// 133   12/14/11 6:44p Yakovlevs
// [TAG]  		EIP73172
// [Description]  	(JPJP000D) It stops POST Code 94h, when connected PCIE
// media read/write device.
// Also: fixed Init pci_address var in SetSlotProprties(); 
// Fixed reconnect -r issue in PciBusStart()
// Changed size of access to the ROM BAR register in GetOpRom() from 1
// byte to 4 - some cards could hang the system if 1 byte is used
// 
// [Files]  		PciBus.c
// 
// 132   12/07/11 11:00a Yakovlevs
// Fixed potential bug in PcieSetSlotProperties() routine. It was using
// uninitialized ADDRESS var.
// 
// 131   12/02/11 2:30p Yakovlevs
// According to AMD GOP Driver GetBarAttributes() must return _GRA field
// set as a bar type NOT A RESOURCE TYPE.
// 
// 130   11/09/11 2:03p Yakovlevs
// [TAG]  		EIP71380
// [Category]  	New Feature
// [Description]  	Core support for CSM opt-out feature
// [Files]  		PciBus.c; PciPort.c; PciBus.sd; PciBus.uni; PciSetup.h;
// PciBusSetup.c; 
// 
// 129   11/08/11 11:03a Yakovlevs
// [TAG]  		EIP72803
// [Category]  	Improvement
// [Description]  	Small fixes of previous checkin
// [Files]  		PciBus.c
// 
// 128   11/03/11 5:59p Yakovlevs
// Added some debug messages.
// 
// 127   11/03/11 5:39p Yakovlevs
// [TAG]  		EIP72803 
// [Category]  	Bug Fix
// [Severity]  	Important
// [Symptom]  	Incorrect Max Payload setting
// [RootCause]  	The issue was that recorded MPL value was updated before
// PcieProgramPayloadUp() function was invoked.
// In that function we check condition again since it was needed to
// maintain loop exit.
// But control newer enter the loop since conditions were not met at that
// point for reason stated above.
// 
// [Solution]  	Move code that updates recorded MPL with a new value 
// after call to PcieProgramPayloadUp().
// [Files]  		PciBus.c
// 
// 126   10/17/11 2:39p Yakovlevs
// [TAG]  		EIP71694 
// [Category]  	Bug Fix
// [Symptom]  	Option ROM is corrupted when copied from device on Rosecity
// Core 4.6.5.1.
// [RootCause]  	MemCopy routine was updated to use 64 bit access but PCI
// BAR
// Copy cannot handle this
// 
// [Solution]  	Introduced MemCpy32 routine to handle fast copy 4 byte at
// a time
// [Files]  		PciBus.c; MemCpy32.asm; AmiLib.h
// 
// 124   8/03/11 2:19p Artems
// Added changes discarded by previous check-in
// 
// 123   8/03/11 1:14p Artems
// EIP 64107: Added changes for module to be compliant with UEFI
// specification v 2.3.1
// 122   8/02/11 3:51p Yakovlevs
// [TAG]  		EIP66216
// [Category]  	Bug Fix
// [Severity]  	Normal
// [Symptom]  	Hotplug resource padding not working for ROOT bridges other
// than 0
// [RootCause]  	Hot plug slots was incorrectly associated alvays withthe
// RootBridge #0
// [Solution]  	Changed algorithm to beter distinguish between Root
// Bridges.
// Added debug messagers to monitor HPC_LOCATION_DATA.
// [Files]  		PciBus.c; PciHostBridge.c. 
// 
// 121   7/20/11 11:59a Yakovlevs
// Added IO 3C0-3DF reservation when VGA attributes set.
// 
// 120   7/06/11 11:52a Yakovlevs
// Fixed build issue when PCI_EXPRESS_GEN2_SUPPORT token set to OFF.
// 
// 119   6/28/11 5:33p Yakovlevs
// [TAG]  		EIP63430; 61101 
// [Category]  	Improvement
// [Description]  	1. Replace use of PciIo->MemRead with MemCpy() for
// Option ROMs.
// 2.The secondary bus reset in the link retraining code causes downstream
// PLX bridges to disappear.
// [Files]  		PciBus.c
// 
// 118   6/11/11 1:24p Yakovlevs
// [TAG]  		EIP 61311 
// [Category]  	Improvement
// [Description]  	PCI Express controllers may not be correctly
// initialized, because of missing delays, while resetting the link.
// 
// [Files]  		Added delay code and tokens PCI_T_RST and PCI_T_RST_RECOVERY
// to fine tune delay.
// 
// 117   6/11/11 1:05p Yakovlevs
// [TAG]  		EIP 61310
// [Category]  	Bug Fix
// [Severity]  	Normal
// [Symptom]  	Unable to enter OpROM on Adaptec 1430 card. OpROM executes,
// attached drives will boot but pressing Ctrl A to enter utility hangs
// system
// [RootCause]  	Card option ROM has 2 images The second one was a BOOT
// AGENT which does not have MATCHING DID in PCIR Header. 
// [Solution]  	Considered DID==0 as a valid option meaning all devices.
// 
// 
// [Files]  		PciBus.c
// 
// 116   5/12/11 11:30a Yakovlevs
// Fixed bug in PcieRetrainLink function it was not doing other attempts
// to retrain link because of missing else statement.
// 
// 115   5/05/11 12:27p Yakovlevs
// Added LinkSpeed trace when link reset or retrain called.
// 
// 114   5/04/11 6:18p Yakovlevs
// [TAG]  		EIP53475; 54911
// [Category]  	New Feature
// [Description]  	PCI Express support issue fixed.
// Reconnect -r issue fixed.
// [Files]  		PCIBus.c
// 
// 113   4/25/11 4:26p Yakovlevs
// Revert back changes in DeviceAttributes() function it was done by
// mistake.
// 
// 112   4/21/11 6:04p Yakovlevs
// [TAG]  		EIP54911
// [Category]  	Bug Fix
// [Severity]  	Normal
// [Symptom]  	Calling Stop function was causing ASSERT
// [RootCause]  	Incorrect setting of the attributes and handling Stop
// function for Device of Type tRootBridge.
// [Solution]  	Change functions DeviceAttribute StopPciDevice.
// [Files]  		PciBus.c
// 
// 111   4/20/11 11:54a Yakovlevs
// 
// 110   4/19/11 5:39p Yakovlevs
// [TAG]  		EIP58702
// [Category]  	New Feature
// [Description]  	Aptio PI 1.2; UEFI 2.3.1 Support
// Changes in Bus Drivers protocols (PCI bus driver)
// 
// [Files]  		PciBus.c
// 
// 109   4/19/11 11:02a Yakovlevs
// [TAG]  		EIP 57664 
// [Category]  	New Feature
// [Description]  	Aptio PI 1.2; UEFI 2.3.1 Support Extended PCI bus
// driver functionality
// Genericaly supported PCI_DEV_REVERSE_SCAN_ORDER.
// [Files]  		DevicePath.h; LoadFile2.h; PciBus.h; PciBus.c.
// 
// 108   4/05/11 11:36a Yakovlevs
// [TAG]  		EIP 38174 EIP 53475; 
// [Category]  	New Feature
// [Description]  	38174 Generic support to handle PCI OUT OF RESOURDCES
// added. 
// 53475 PCI Express 3.0 support added.
// 
// [Files]  		PciBus.c; PciHostBridge.c;
// 
// 107   2/02/11 3:42p Yakovlevs
// 
// 106   1/28/11 4:26p Yakovlevs
// [TAG]  		EIP48290
// [Category]  	New Feature
// [Description]  	Added PCI_AMI_COMBINE_MEM_PMEM32 token that tells to
// map 32 bit sized PF MMIO BARs trough NON PF MMIO Bridge registers.
// 
// [Files]  		PciBus.c; PciBus.sdl;
// 
// 105   1/28/11 2:55p Yakovlevs
// [TAG]  		EIP43879
// [Category]  	New Feature
// [Description]  	Added PciPortOemGetOptRom() OEM Hook to override
// content of the PCI Device Option ROM.
// [Files]  		PciBus.c; PciPort.c; PciPort.h; PciBus.mak; PciBus.sdl
// 
// 104   1/20/11 3:07p Yakovlevs
// [TAG]  		EIP45278
// [Category]  	Improvement
// [Description]  	Added PCI_MMIO_RES_TOP_ALLIGN token to control Resource
// allocation algorithm selection.
// [Files]  		PciBus.c; PciHostBridge.c; PciBus.sdl.
// 
// 103   1/14/11 10:50a Yakovlevs
// [TAG]  		EIPEIP49743
// [Category]  	Bug Fix
// [Severity]  	Normal
// [Symptom]  	Incorrect initialization complicated PCI infrastructure
// [RootCause]  	wrong condition to breake {do while loop}.
// [Solution]  	Change conditions
// [Files]  		PciBus.c
// 
// 102   1/13/11 2:59p Yakovlevs
// [TAG]  		EIP49743
// [Category]  	Bug Fix
// [Severity]  	Minor
// [Symptom]  	In the PcieCalcLatency(), the do-while loop condition have
// issue in this.
// [RootCause]  	It may be a condition when while loop in function
// PcieCalcLatency(), will never break.
// [Solution]  	Cahnge conditiondn iinstead of logical OR use AND.
// [Files]  		PciBus.c
// 
// 101   1/13/11 1:31p Yakovlevs
// [TAG]  		EIP45278
// [Category]  	Improvement
// [Description]  	Changed default resource allocation algorithm to work
// more efficiently. 
// [Files]  		PciBus.c; PciHostBridge.c.
// 
// 100   1/13/11 1:21p Yakovlevs
// [TAG]  		EIP49743
// [Category]  	Improvement
// [Description]  	Workaround for devices which having Link Retrain bit
// "sticky"
// [Files]  		PciBus.c
// 
// 99    1/13/11 1:14p Yakovlevs
// [TAG]  		EIP50097 
// [Category]  	Improvement
// [Description]  	Fixed issue when with PCI_FIXED_BUS_ASSIGNMENT==1
// system was ASSERTING.
// Reason was that with complicated PCI structure next bridge XLAT entry
// that used to determine Subordinate bus #, selected incorrectly.
// 
// [Files]  		PciBus.c
// 
// 98    12/09/10 2:53p Yakovlevs
// Fixed bug in PcieCalcLatency() function. It was not calculating L1
// latency correctly.
// 
// 97    12/08/10 3:17p Yakovlevs
// Removed Setup Option "Selectable DeEmphasis" since it is HwInit Bit.
// 
// 96    11/18/10 3:50p Yakovlevs
// 1.Changed Install Option ROM debug messages to make it more precise.
// 2. Added call to DoubleCheckOpRom() to verify ROM size before
// processing UEFI OpROM.
// 
// 95    11/12/10 6:37p Yakovlevs
// PcieDoubleCheckCard() routine added to support cards that slowly
// respond on CFG transactions.
// 
// 94    11/08/10 6:16p Felixp
// 
// 93    11/08/10 6:13p Felixp
// The Core source files are updated to remove upper ASCII characters
// (above 128) 
// from the comment blocks. The characters caused build errors 
// with Japanese version of Microsoft compiler.
// 
// 92    11/05/10 5:06p Yakovlevs
// Changed if Default (AUTO) MaxReadRequest selected don't change value
// sitting there.
// Removed assert in PcieConvertLatency function. 
// 
// 90    10/07/10 12:13p Felixp
// PEI_TRACE on TPL_HIGH is removed.
// Headers updated.
// 
// 89    10/05/10 4:46p Yakovlevs
// Changed Default (AUTO) MaxReadRequest Size value from == MPL to spec.
// default == 512.
// 
// 88    10/01/10 6:05p Yakovlevs
// Fixed issue with low level PciCfgXX() access functions. When
// ExtendedRgister used.
// 
// 87    9/01/10 11:52a Yakovlevs
// Improved Override ASPM Porting hook, now it called for UPSTREAM as well
// as DOWNSTREAM port.  
// 
// 86    8/16/10 1:05p Yakovlevs
// New Incompatibility Type Sypport: icBad64BitBar - Device has a bar that
// is 64bit capable, but the card does not function properly when it is
// allocated.
// 
// 85    7/08/10 6:00p Yakovlevs
// Removed EFI_EADLOOP() left in InstallEfiRom() function
// 
// 84    7/08/10 3:12p Yakovlevs
// Fixed UEFI Option ROM Size miscalculation. 
// 
// 83    6/30/10 11:11a Yakovlevs
// Fixed WDK Build Issue EIP 40554
// 
// 82    6/08/10 3:31p Yakovlevs
// Minor fix for EIP 38289 Klocwork Issues II.
// 
// 81    6/07/10 3:36p Yakovlevs
// Improved logic to select matching PCI Bus Xlat table entry.
// 
// 80    5/25/10 3:16p Yakovlevs
// Fixed condition to disable device using 64 bit resource threshold
// 
// 79    5/19/10 12:43p Yakovlevs
// 
// 78    5/07/10 12:24p Yakovlevs
// Bug fix in PcieProgramPayloadUp() function. canged order when recording
// calculated PayLoad.
// It use to recursive call was made after reduced value of MPL was
// recorded. It was preventing function to program MPL correctly.
// 
// 77    4/28/10 11:33a Yakovlevs
// Fixed bug in DoubleCheckOpRom() when OpROM is a Single Image ROM.
// 
// 76    4/20/10 5:46p Yakovlevs
// Fixed build error with SRIOV token ON; Fixed InitDevCahain() function
// Logic.
// 
// 75    4/15/10 4:28p Yakovlevs
// Fixed issue with PCIe Switches and MPL programming UP
// 
// 74    4/14/10 4:43p Yakovlevs
// Fixed Possible issue with incorrect MPL Programming.
// 
// 73    3/03/10 12:46p Yakovlevs
// Fixed bug in IsFunc0() function.
// 
// 72    3/01/10 6:18p Yakovlevs
// PCI Express V2.1 support added.
// 
// 68    12/24/09 10:45a Yakovlevs
// Fixed issue when removing unused entries from IRQ routing tables, PIC
// and APIC.
// 
// 67    9/24/09 1:51p Yakovlevs
// Fixed EIP 26787. If P2P Bridge has ExpROM BAR, value that has to go
// there was programmed as Secondary Interface Forward Range.
// 
// 66    9/22/09 6:09p Yakovlevs
// 6.	Fixed conditions in ApplyAcpiResources() where function assumes
// validity of Resource Range. In case of Fixed Resource Allocation
// Resource window allocated by custom unction might be bigger than actual
// hardware resource request
// 
// 65    9/08/09 12:57p Yakovlevs
// Fixed ~0LU statement to 0ULL. This is correct statement for 64 bit
// Value
// Made QueryPciDevice() routine set Interrupt Line register(0x3C) to 0xFF
// 
// 64    8/28/09 10:27a Felixp
// Component Name protocol implementation is upadted  to support both 
// ComponentName and ComponentName2 protocols
// (based on value of the EFI_SPECIFICATION_VERSION SDL token).
// 
// 63    8/21/09 3:53p Yakovlevs
// Fixed: EIP 19106 If 1 Bus set to be paded in Setup, PCI Bus driver
// still creates 1 BUS for this bridge instead of 2.
// 
// 
// 62    7/07/09 12:39p Yakovlevs
// Moved DisableBridgeDecoding() call before Disable device decoding since
// it could decode 0-4K of IO and 0-1M of Mem. 
// 
// 61    5/22/09 2:16p Yakovlevs
// 
// 60    5/05/09 5:46p Yakovlevs
// Fixed build issue in IA32 mode with SRIOV_SUPPORT == ON.
// 
// 59    4/24/09 11:49a Yakovlevs
// 
// 58    4/23/09 8:28p Yakovlevs
// Fixed some minor issues related to PCI IRQ entries usage and updating.
// 
// 57    4/23/09 2:02p Yakovlevs
// Fixed potentiial Memory Coruption issue when assigning Ext->XlatEntry
// ->BusRun 
// for bridges who doesnot have it's XlatTbl Entry.
// 
// 56    4/19/09 2:14p Yakovlevs
// Fixed issue with Multiple Root Bridges, when PCI Bus Driver was
// incorrectly calculating ranges buses to scan.  
// 
// 55    4/17/09 6:38p Yakovlevs
// Fixed issue EIP 21366 with OptimizeBrgResource() function see EIP for
// more details.
// 
// 54    4/16/09 1:49p Yakovlevs
// Fixed issue where for Second Root Bridge Bus numbers were assifned
// started fron LAST ROOT_0_BUS + 1
// 
// 53    4/01/09 9:57a Yakovlevs
// Minor fixes
// 
// 52    3/30/09 5:23p Yakovlevs
// Fixed issue in AssignBridgeResources function when there are no bars to
// program function was returning ERROR Status.
// 
// 51    3/27/09 7:02p Yakovlevs
// Fixed Uninitialized PCI DB issue.
// 
// 50    3/27/09 11:47a Yakovlevs
// Fixed some issues with re starting driver.
// 
// 49    3/25/09 11:02a Yakovlevs
// ADDED Generic implementation of #PERR, #SERR; and VGA Palette Snoop.
// 
// 48    3/23/09 2:27p Yakovlevs
// ADDED support for VGA_16_BIT_DECODE. VGA aliasing support pending. 
// 
// 47    2/04/09 4:03p Yakovlevs
// Fixed PciPortSkipThisDevice() function was not preserving PCI.CMD
// register. 
// 
// 46    2/04/09 4:01p Yakovlevs
// 
// 45    2/03/09 3:27p Yakovlevs
// Added fixes for EIP 19144. Break the PCI Express Extended Capability
// header access routine if read of offset 0x100 returns 0xFFFF
// 
// 44    1/30/09 1:03p Yakovlevs
// Minor bug fixes and improuvements EIP 8874; EIP 17947
// 
// 43    11/26/08 3:55p Yakovlevs
// 
// 42    11/26/08 3:54p Yakovlevs
// Start function NOW returns  EFI_ALREADY_STARTED, when all PCI devices
// installed PciIo interface.
// 
// 41    11/26/08 11:37a Yakovlevs
// Fixed connect -r issue when shell was hunging in infinite loop.
// 
// 40    11/14/08 3:34p Yakovlevs
// Removed EFI_DEADLOOP() used for debug
// 
// 39    11/14/08 1:21p Yakovlevs
// Introduced AMI Board Info Protocol which has *.inc OUTPUTS generated 
// by AMISDL tool. To keep it in one place and Make PciBus Driver use it.
// 
// 38    10/31/08 6:10p Yakovlevs
// 
// 36    10/15/08 10:45a Yakovlevs
// Fixed EIP 16990 CsmVideo can't work
// 
// 35    10/14/08 1:15p Yakovlevs
// Rearrange Function order to support ROM BARs as PCI incompatible BARs
// 
// 33    10/10/08 5:40p Yakovlevs
// Added Pci Compliance tests workarounds
// 
// 32    10/01/08 7:12p Yakovlevs
// Updated AMI FUNC HEADER information
// 
// 31    9/24/08 6:41p Yakovlevs
// New features and bug fixes: 
// New features.
// 1. Make PCI Bus Driver use VeB generated structures.
// 2. Added SRIOV support
// 3. Added Fixed Bus Allocation (Buses for the bridges will be allocated
// same way as in Build time)
// 4. Scan full bus ranges. 
// 5. Added support for UEFI 2.1 PCI requirements.
// 6. Added Token to disable PCI Bus Driver Debug Messages.
// 7. Removed dependency from SETUP_DATA fields layout.
// 8. Progress/Error codes.
// 9. Support for S3 Video Repost. 
// 
// Bug fixes:
// 1. Attribute function.
// 2. If device decodes only PFMMIO Bridge MMIO Base and Limit register
// was initialized with 0 making it decode space from 0x10000.
// 3. OptimizeBridgeResources() function was not working correctly in some
// rare cases.
// 
// 29    5/13/08 11:59a Felixp
// ComponentName protocol converted to ComponentName2
// 
// 28    4/29/08 6:55p Yakovlevs
// Generic S3 Video Repost support added.
// Added mechanism to suppress PCI BUs driver debug messages(Latest
// PciBus.sdl and PciBus.h required).
// 
// 27    4/24/08 12:19p Yakovlevs
// Added generic support for S3 VIDEO Repost feature.
// 
// 26    4/18/08 3:53p Yakovlevs
// Added missing function headers
// 
// 25    4/17/08 6:23p Yakovlevs
// fixed potencial issue in OptimizeBridgeResources.
// 
// 24    3/12/08 12:45p Felixp
// Progress/Error codes reporting added
// 
// 23    2/21/08 4:37p Felixp
// 1. Bug fix in StartPciChildDevice. Handling of remaining device path
// has changed.
// 2. Handling of setup data structure in PciBusStart updated to work fine
// without PCI sources
// 
// 22    1/31/08 8:31p Yakovlevs
// Fixed issue with hotplug resource padding.
// 
// 21    1/31/08 2:51p Yakovlevs
// 1. Fixed resource allocation issue on bridges only branches.
// 2. Cahnged Default Padding routine for Card bus bridges. 
// 
// 20    12/10/07 4:15p Yakovlevs
// 1.Fixed bug in OprimizeBrgResources() function, (it might hung in
// infinite loop).
// 2.Corrected ApplyCrdPadding () implementation to take care of
// EFI_PCI_HOST_BRIDGE_COMBINE_MEM_PMEM allocation attribute.
// 
// 19    11/08/07 4:51p Felixp
// Code updated to compile and work without CSM.
// 
// 18    10/23/07 5:28p Felixp
// VC8 warnings fixed
// 
// 17    10/18/07 11:22a Felixp
// ASPN SDL tokens replaced with external constants defined in PciPort.c
// 
// 16    10/15/07 4:11p Yakovlevs
// Fixed bug in OptimizeResources function.
// 
// 15    10/08/07 5:26p Yakovlevs
// Fix to handle not compliant PCI Option Roms.
// 
// 4     9/21/07 6:38p Yakovlevs
// Sinchronize with recent PCI Bus updates
// 
// 14    9/21/07 6:24p Yakovlevs
// Fixed ASPM related bugs.
// 
// 13    9/18/07 5:23p Yakovlevs
// Inplemented Intel's recomendation of calculating EP Acceptable ASPM
// Latency.
// 
// 12    8/31/07 11:18a Yakovlevs
// Improuvements in PCI Resource Allocation Algorithm.
// 
// 10    7/25/07 12:54p Felixp
// AMI Debugger-related code is updated to enable Debugger in non-debug
// mode. 
// The code is enabled when USB_DEBUG_TRANSPORT or EFI_DEBUG is on.
// 
// 9     7/17/07 6:29p Felixp
// Minor bug fix in GetOptRom: GetEmbeddedRom was called with UINT32 image
// size pointer instead of UINTN
// 
// 8     7/04/07 5:51a Yakovlevs
//  Version of this file will work with 4.5.3_CSM.6.37_51 label of CSM, 
//  which requires USB module upgrade to Label 4.05.03_USB_08.07.11.
//  1. Fixed Disabling VGA attributes for Devices behind multiple bridges.
// 2. Added some debug messages for Installing Devices PciIo interface.
//  3. Changed GetOptRom() function to search for Embeded ROMs(onboard) as
//  well and populate PciIo.OptionRom*.
// 
// 7     5/23/07 5:32p Yakovlevs
// Previouse fix had some side effects on protocol installation side -
// this one fixes these.
// Also some debug messages at protocol installation phase was added.
// 
// 6     5/18/07 6:30p Yakovlevs
// Fixed Issue with incorrect Status returning from StartPciChildDevice().
// 
// 5     5/14/07 7:49p Yakovlevs
// Somehow changes to impruve PCI Config Acces were lost. Resored them.
// 
// 4     5/04/07 3:50p Yakovlevs
// 
// 3     5/04/07 11:51a Yakovlevs
// 
// 2     5/02/07 4:41p Yakovlevs
// 
// 1     3/12/07 12:02p Yakovlevs
// 
// 48    12/28/06 7:16p Yakovlevs
// In ActivateOptRom function removed upate of OptROM size where
// PciIo->OptionRom points
// It is not needed.
// 
// 47    12/22/06 9:42p Yakovlevs
// Code Cleanup and CHM headers added
// 
// 46    12/21/06 5:13p Yakovlevs
// Code cleanup. Added CHM headers.
// 
// 44    12/19/06 11:54a Yakovlevs
// Fixed Padding for the bridge if CombineMemPmem Allocation Attribute is
// set 
// 
// 43    12/05/06 3:27p Yakovlevs
// Fixed SCT 2.0 PciIo  Disable Attributes  ISSUE.
// 
// 42    12/05/06 11:54a Felixp
// 
// 41    11/22/06 10:27a Olegi
// 
// 40    11/22/06 10:26a Olegi
// InstallPciDevice is modified so that the device with DebugPort
// enumeration will not be skipped.
// 
// 39    10/20/06 5:50p Yakovlevs
// 
// 38    10/13/06 4:42p Yakovlevs
// 
// 37    10/13/06 4:10p Yakovlevs
// Function Headers Added!!!!! IDE Attributes support added, Hotplug
// support fix (NULL pointer).
// 
// 36    9/11/06 11:51a Yakovlevs
// Fixed CacheLineSize rergister programming issue
// 
// 35    8/24/06 10:11a Felixp
// x64 support: warning/error fixes
// 
// 34    8/09/06 5:08p Yakovlevs
// VC initialization and boot sript support for PCI Express.
// This fixes NVIDIA 7800 GT issue
// 
// 31    6/04/06 9:06p Yakovlevs
// Fixed issue when PciBus driver was writting in IRQ Line Reg some junk.
// 
// 30    6/04/06 8:22p Yakovlevs
// Fixed PCI_EXPRESS_SUPPORT and HOTPLUG_SUPPORT featueses.
// Added some debug messages during PCI bus enumeration process. 
// 
// 29    6/01/06 12:21p Yakovlevs
// Changes to accomodate HbCspAdjustMemoryMmioOverlap function in PciRB.
// 
// 28    5/19/06 10:45p Felixp
// Device Path code updated to use NEXT_NODE/NODE_LENGTH/SET_NODE_LENGTH
// macros to remove direct access to the Length field
// 
// 27    4/25/06 4:49p Stacyh
// 
// 26    4/03/06 3:52p Felixp
// Major changes in PCI and Super I/O:
// PCI - Root Bridge Resource Allocation Sepcification support
// Super I/O - multiple Super I/O support; SIO Setup page added;
// 
// 25    3/20/06 9:26a Felixp
// Bug fix in attribute clearing logic.
// 
// 24    3/13/06 10:07a Felixp
// 
// 21    11/08/05 4:08a Felixp
// AMI Debugger ifdefs changed from AMI_DEBUGGER_SUPPORT to EFI_DEBUG
// 
// 20    10/27/05 5:39p Felixp
// 
// 19    10/12/05 7:19p Felixp
// AMI Debugger support added
// 
// 18    7/18/05 3:25p Felixp
// 
// 17    6/26/05 6:50p Olegi
// Incompatible PCI device list updated.
// 
// 16    6/26/05 6:43p Yakovlevs
// Card Bus Support Added
// Some other bug fixes
// Incompatibility list extended with icBarFixedSize.
// 
// 15    5/25/05 6:26p Yakovlevs
// 
// 14    5/11/05 3:09p Yakovlevs
// Fixed: CacheLine Size register Latency timer Reg, gets programmed,
// IO resource lesser than 16 bytes padded to 16 bytes.
// 
// 13    4/21/05 2:03p Sivagarn
// - Option ROM signature is validated before copying into the memory
// - Option ROM size is obtained from the header instead of using size
// calculated from PCI base register
// 
// 12    4/06/05 10:33a Felixp
// Bug fix in StartPciDevices
// 
// 11    3/29/05 5:16p Olegi
// Problem with ATI Video fixed.
// 
// 10    3/23/05 6:17p Yakovlevs
// 
// 9     3/23/05 5:48p Yakovlevs
// Changes to avoid clearing HostBridge Command register.
// 
// 8     3/15/05 5:23p Yakovlevs
// Option ROM issue for on bord device with implemented ROM BAR and ROM
// image at ROM BIOS fixed.
// Now if ActivateOptionRom routine fails to validate option rom it frees
// OptROM buffer. 
// 
// 7     3/04/05 9:26a Mandal
// 
// 6     2/14/05 7:36p Yakovlevs
// Handled situation when Start Function calls multiple times for every
// next DP node.
// Fixed Option Rom Size issue
// 
// 5     2/14/05 6:12p Yakovlevs
// 
// 4     2/13/05 4:54p Yakovlevs
// Fixed issue with 64 bit width BARs; PCI incompatible device support
// added.
// 
// 3     2/11/05 7:48p Yakovlevs
// Incompatible Pci Device Support added.
// 
// 2     2/01/05 1:16a Felixp
// 
// 1     1/28/05 12:45p Felixp
// 
// 8     1/21/05 7:00p Yakovlevs
// 
// 7     1/21/05 5:19p Yakovlevs
// Fixed some stuff from TODO list:
// 1.Made ajustments to exchange information with RB Driver.
// 2.Support of 64 bit resources on P2P Brg (EnableBrgPfmmDecoding)
// routine,
// 
// 4     1/13/05 8:26p Yakovlevs
// 
// 3     1/11/05 5:25p Yakovlevs
// 
// 1     12/22/04 6:19p Admin
// 
// 1     12/22/04 6:18p Admin
// 
// 55    12/21/04 4:20p Markw
// Renamed hardware device path definition for consistency.
// 
// 54    12/06/04 5:14p Yakovlevs
// 
// 53    12/06/04 4:51p Robert
// PciIoCheckConfig - the comparison for the buffer length should not 
// exceed 256 bytes.  Therefore it should be > not >=
// 
// 52    10/22/04 7:26p Yakovlevs
// 
// 51    10/20/04 3:02p Yakovlevs
// 
// 50    10/20/04 11:43a Yakovlevs
// InstallMultipleProtocol and Close Protocol opened by Child Controller
// added
// 
// 49    10/20/04 9:28a Yakovlevs
// 
// 48    10/04/04 1:44p Yakovlevs
// Make use of AcpuRes.h resource Tamplete Definitions
// 
// 47    9/24/04 9:31p Yakovlevs
// Uncachable  Attributes set  for PCI Bus MMIO regions
// 
// 46    9/22/04 6:51p Yakovlevs
// 
// 45    9/16/04 10:24a Yakovlevs
// 
// 44    9/15/04 6:01p Yakovlevs
// 
// 43    9/15/04 9:42a Yakovlevs
// 
// 42    9/09/04 3:06p Yakovlevs
// Bug fixes:
// 1. Handling of RemainingDevicePath in Start routine
// 2. Option ROM handling
// Path:
// Temporary patch to make Cirrus Logic and some other Add-On cards work
// 
// 41    9/03/04 11:58a Yakovlevs
// 
// 40    8/27/04 6:36p Yakovlevs
// 
// 39    8/26/04 7:47p Yakovlevs
// SCT PCI Bus Support -> OK!
// 
// 38    8/24/04 1:01p Yakovlevs
// 
// 37    8/15/04 7:32p Yakovlevs
// 
// 36    8/13/04 9:21a Yakovlevs
// 
// 35    7/13/04 10:42a Felixp
// 
// 34    5/27/04 10:30a Yakovlevs
// 
// 33    5/06/04 8:20p Felixp
// 
// 32    5/06/04 6:31p Felixp
// 
// 31    5/06/04 10:25a Yakovlevs
// 
// 30    5/05/04 8:14p Yakovlevs
// 
// 28    5/03/04 8:13p Felixp
// 
// 27    5/03/04 6:15p Yakovlevs
// 
// 26    5/03/04 6:04p Yakovlevs
// 
// 25    5/03/04 12:24p Yakovlevs
// 
// 24    5/03/04 11:52a Yakovlevs
// Changes to avoid hardcoded Array size and accomodate all resource types
// 
// 23    4/23/04 5:43p Felixp
// 
// 22    4/23/04 3:20p Felixp
// 
// 21    4/23/04 2:36p Felixp
// 
// 20    4/23/04 12:08p Felixp
// 
// 19    4/22/04 12:27p Yakovlevs
// 
// 18    4/21/04 8:33p Yakovlevs
// 
// 17    4/21/04 12:49p Yakovlevs
// 
// 16    4/20/04 9:19p Yakovlevs
// 
// 15    4/20/04 11:51a Yakovlevs
// 
// 14    4/19/04 11:56a Yakovlevs
// 
// 13    4/18/04 4:05p Felixp
// 
// 12    4/16/04 7:12p Felixp
// 
// 11    4/12/04 4:59p Yakovlevs
// 
// 10    4/12/04 4:12p Yakovlevs
// 
// 9     4/09/04 6:40p Yakovlevs
// 
// 8     4/02/04 6:28p Yakovlevs
// 
// 7     4/02/04 6:23p Yakovlevs
// 
// 6     4/02/04 6:05p Yakovlevs
// 
// 5     3/28/04 2:11p Felixp
// 1. PE Loader and some other commonly used code moved to the Library
// 2. Warnings fixed (from now on warning will be treated as error)
// 
// 4     3/26/04 1:50p Yakovlevs
// 
// 3     3/26/04 1:19p Felixp
// 
// 2     3/22/04 10:29a Yakovlevs
// 
// 1     3/15/04 11:20a Felixp
// 
// 1     3/12/04 6:47p Yakovlevs
// 
// 3     2/04/04 6:50p Yakovlevs
// 
// 2     2/04/04 4:22p Yakovlevs
// 
//**********************************************************************
//<AMI_FHDR_START>
//
// Name:	<PciBus.c>
//
// Description:	EFI PCI Bus Generic Driver.
//
// Tabsize:		4
//
//<AMI_FHDR_END>
//**********************************************************************

//---------------------------------------------------------------------------
// Include Files
//---------------------------------------------------------------------------
#include <Efi.h>
#include <Token.h>
#include <Protocol\PciRootBridgeIo.h>
#include <Protocol\DevicePath.h>
#include <Protocol\DriverBinding.h>
#include <Protocol\BusSpecificDriverOverride.h>
#include <Protocol\Decompress.h>
#include <Protocol\ComponentName2.h>
#include <Protocol\PciHostBridgeResourceAllocation.h>
#include <Protocol\PciHotplugInit.h>
#include <Protocol\PciPlatform.h>
#include <Protocol\IncompatiblePciDeviceSupport.h>
#include <Protocol\BootScriptSave.h>
#include <Dxe.h>
#include <AmiDxeLib.h>
#include <AMIHobs.h>
#include <PciBus.h>
#include <PciBusEx.h>
#include <AcpiRes.h>
#include <AmiLoadCsmPolicy.h>

#if PCI_OUT_OF_RESOURCE_SETUP_SUPPORT
#include <Setup.h>
#endif
#include "PciPort.h"

#if CSM_SUPPORT
#include <Protocol\LegacyBiosExt.h>
#endif

#if EFI_DEBUG || USB_DEBUG_TRANSPORT
#include <AmiDebugPort.h>
#endif

#include "PciSetup.h"

//==================================================================================
//Function Prototypes for Driver Binding Protocol Interface
//==================================================================================
EFI_STATUS PciBusSupported(IN EFI_DRIVER_BINDING_PROTOCOL	*This,
						   IN EFI_HANDLE                    Controller,
						   IN EFI_DEVICE_PATH_PROTOCOL      *RemainingDevicePath);

EFI_STATUS PciBusStart(IN EFI_DRIVER_BINDING_PROTOCOL		*This,
					   IN EFI_HANDLE						Controller,
					   IN EFI_DEVICE_PATH_PROTOCOL			*RemainingDevicePath );

EFI_STATUS PciBusStop(IN EFI_DRIVER_BINDING_PROTOCOL			*This,
					   IN EFI_HANDLE						Controller,
					   IN UINTN								NumberOfChildren,
					   IN EFI_HANDLE						*ChildHandleBuffer);

EFI_STATUS EnumerateAll(EFI_HANDLE Controller);

EFI_STATUS StartPciDevices(IN EFI_HANDLE ControllerHandle, 
					   IN EFI_DEVICE_PATH_PROTOCOL *RemainingDevicePath);

//-------------------------------------------------------
//Forward declarations for Extended PCI Bus Protocol
EFI_STATUS PciExtIsPciExpresss(
	IN  AMI_PCI_EXT_PROTOCOL	              			*This,
	IN  EFI_HANDLE                               		PciDeviceHandle,
	IN  EFI_PCI_IO_PROTOCOL								*PciIo 		    OPTIONAL,
    OUT PCIE_DATA                                       **PciExpData    OPTIONAL
);

EFI_STATUS PciExtIsPciX(
	IN  AMI_PCI_EXT_PROTOCOL	              			*This,
	IN  EFI_HANDLE                               		PciDeviceHandle,
	IN  EFI_PCI_IO_PROTOCOL								*PciIo 		    OPTIONAL,
    OUT PCIX_DATA                                       **PciXData      OPTIONAL
);

EFI_STATUS PciExtIsPciBrg(
	IN  AMI_PCI_EXT_PROTOCOL	              			*This,
	IN  EFI_HANDLE                               		PciDeviceHandle,
	IN  EFI_PCI_IO_PROTOCOL								*PciIo 		    OPTIONAL,
    OUT PCI_BRG_EXT                                     **BrgData       OPTIONAL
);


EFI_STATUS PciExtIsCrdBrg(
	IN  AMI_PCI_EXT_PROTOCOL	              			*This,
	IN  EFI_HANDLE                               		PciDeviceHandle,
	IN  EFI_PCI_IO_PROTOCOL								*PciIo 		    OPTIONAL,
    OUT PCI_BRG_EXT                                     **BrgData       OPTIONAL
);


EFI_STATUS PciExtIsDevice(
	IN  AMI_PCI_EXT_PROTOCOL	              			*This,
	IN  EFI_HANDLE                               		PciDeviceHandle,
	IN  EFI_PCI_IO_PROTOCOL								*PciIo          OPTIONAL
);


EFI_STATUS PciExtClassCodes(
	IN  AMI_PCI_EXT_PROTOCOL	              			*This,
	IN  EFI_HANDLE                               		PciDeviceHandle,
	IN  EFI_PCI_IO_PROTOCOL								*PciIo 		OPTIONAL,
	OUT PCI_DEV_CLASS									*CassCodes
);


EFI_STATUS PciExtPicIrqRout (
	IN  AMI_PCI_EXT_PROTOCOL	              			*This,
	IN  EFI_HANDLE                               		PciDeviceHandle,
	IN  EFI_PCI_IO_PROTOCOL						 		*PciIo 		OPTIONAL,
    OUT PCI_IRQ_PIC_ROUTE                               **PicIrqTblEntry,
    OUT EFI_PCI_CONFIGURATION_ADDRESS                   **ParentDevices,
    OUT UINTN                                           *EntryCount
);

EFI_STATUS PciExtApicIrqRout (
	IN  AMI_PCI_EXT_PROTOCOL	              			*This,
	IN  EFI_HANDLE                               		PciDeviceHandle,
	IN  EFI_PCI_IO_PROTOCOL						 		*PciIo 		OPTIONAL,
    OUT PCI_IRQ_APIC_ROUTE                              **ApicIrqTblEntry,
    OUT EFI_PCI_CONFIGURATION_ADDRESS                   **ParentDevices,
    OUT UINTN                                           *EntryCount
);

EFI_STATUS ReadEfiRom(PCI_DEV_INFO	*Dev, PCI_ROM_IMAGE_DATA *RomData, VOID **ImgBase, UINT32 *ImgSize);

//==================================================================================
//Some Protocole GUIDs needed here
//==================================================================================
static EFI_GUID gDriverBindingProtocolGuid 				= EFI_DRIVER_BINDING_PROTOCOL_GUID;
static EFI_GUID gPciRootBridgeIoProtocolGuid 			= EFI_PCI_ROOT_BRIDGE_IO_PROTOCOL_GUID;
static EFI_GUID gDevicePathProtocolGuid					= EFI_DEVICE_PATH_PROTOCOL_GUID;
static EFI_GUID gPciIoProtocolGuid						= EFI_PCI_IO_PROTOCOL_GUID;
static EFI_GUID gBusSpecificDriverOverrideProtocolGuid 	= EFI_BUS_SPECIFIC_DRIVER_OVERRIDE_PROTOCOL_GUID;
static EFI_GUID gEfiDecompressProtocolGuid				= EFI_DECOMPRESS_PROTOCOL_GUID;
static EFI_GUID gEfiPciHostBrgResAllocProtocolGuid		= EFI_PCI_HOST_BRIDGE_RESOURCE_ALLOCATION_PROTOCOL_GUID;
static EFI_GUID gEfiPciHotPlugInitProtocolGuid			= EFI_PCI_HOT_PLUG_INIT_PROTOCOL_GUID;
static EFI_GUID gEfiPciPlatformProtocolGuid				= EFI_PCI_PLATFORM_PROTOCOL_GUID;
static EFI_GUID gEfiIncompatiblePciDeviceProtocolGuid	= EFI_INCOMPATIBLE_PCI_DEVICE_SUPPORT_PROTOCOL_GUID;
static EFI_GUID gEfiBootScriptSaveGuid           		= EFI_BOOT_SCRIPT_SAVE_GUID;
static EFI_GUID gAmiExtPciBusProtocolGuid               = AMI_PCI_BUS_EXT_PROTOCOL_GUID;
static EFI_GUID gAmiBoardInfoProtocolGuid               = AMI_BOARD_INFO_PROTOCOL_GUID;

#if CSM_SUPPORT
static EFI_GUID gEfiLegacyBiosExtProtocolGuid          	= EFI_LEGACY_BIOS_EXT_PROTOCOL_GUID;
#endif


#if PCI_EXPRESS_SUPPORT
static T_ITEM_LIST  gPcieEpList = {0,0,NULL}; 
#endif


//=============================================================================
//<AMI_SHDR_START>
//----------------------------------------------------------------------------
// Name:		gBadPciDevList
//
// Description:	Incompatible PCI Devices List known so far.
//
// Notes: 
//  See PCI_BAD_BAR for field names and usage details.
//  If BarType field == tBarMaxType then BarOffset field should be used. 
//  For "BarType" field only tBarIo, tBarMem and tBarMaxType allowed!
//----------------------------------------------------------------------------
//<AMI_SHDR_END>
PCI_BAD_BAR gBadPciDevList[]={ 
//-----------------------------------------------------------------------------------------------------------------------
//enum			UINT16		UINT16		UINT16		UINT16	  PCI_BAR_TYPE 	UINTN		UINT64		UINT64
//IncompType;	VendorId;	DeviceId;	DevIdMask;	Reserved;	BarType;	BarOffset;	BarBase;	BarLength;
//-----------------------------------------------------------------------------------------------------------------------
//Device Adaptec 9004
{	icBarBad,	0x9004,		0xFFFF,		0x0000,		0x0000,		tBarIo,		0x0000, 	0, 			0 			},
//Device Adaptec 9005
{	icBarBad,	0x9005,		0xFFFF,		0x0000,		0x0000,		tBarIo,		0x0000, 	0, 			0 			},
//Device QLogic  1007
{	icBarBad,	0x1007,		0xFFFF,		0x0000,		0x0000,		tBarIo,		0x0000, 	0,			0 			},
//Device Agilent 103C
{	icBarBad,	0x103C,		0xFFFF,		0x0000,		0x0000,		tBarIo,		0x0000,		0,			0 			},
//Device Agilent 15BC
{	icBarBad,	0x15BC,		0xFFFF,		0x0000,		0x0000,		tBarIo,		0x0000, 	0,			0			},
//Device AMI Mega RAID 493
{icBarFixedSize,0x1077,		0x1216,		0xFFFF,		0x0000,	 	tBarMaxType,0x0014, 	0,			0x400000	},
//ICH8 smbus controller 
{icNotBar,		0x8086,		0x283E,		0xFFFF,		0x0000,	 	tBarMaxType,0x0014, 	0,			0			},
//RTL8111E
{   icNotBar,   0x10EC,     0x8168,     0xFFFF,     0x0000,     tBarMaxType,0x0030,     0,          0           },
//NVIDIA 7200 GS
{icBad64BitBar,	0x10de,		0x01d3,		0xFFFF,		0x0000,	 	tBarMaxType,0x0014, 	0,			0			}
};

//<AMI_SHDR_START>
//----------------------------------------------------------------------------
// Name:		gBadPciDevCount
//
// Description:	Number or records in gBadPciDevList table.
// Notes: UINTN
//
//----------------------------------------------------------------------------
//<AMI_SHDR_END>
UINTN gBadPciDevCount=sizeof(gBadPciDevList)/sizeof(PCI_BAD_BAR);


//==================================================================================
// PCI Bus Driver Global Variables
//==================================================================================

//<AMI_SHDR_START>
//----------------------------------------------------------------------------
// Name:		gAllocationAttributes
//
// Description:	Root Bridge Allocation Attributes
// Notes: UINT64
//
//----------------------------------------------------------------------------
//<AMI_SHDR_END>
UINT64	gAllocationAttributes=0;

//<AMI_SHDR_START>
//----------------------------------------------------------------------------
// Name:		gPciOutOfRes
//
// Description:	Indicates Out Of Resources Condition.
// Notes: BOOLEAN
//
//----------------------------------------------------------------------------
//<AMI_SHDR_END>
BOOLEAN	gPciOutOfRes=FALSE;

BOOLEAN	gPciOutOfResHit=FALSE;


//<AMI_SHDR_START>
//----------------------------------------------------------------------------
// Name:		gLowResType
//
// Description:	Indicates what type of resource has Out Of Resources Condition.
// Notes: MRES_TYPE
//
//----------------------------------------------------------------------------
//<AMI_SHDR_END>
MRES_TYPE gLowResType=rtMaxRes;

AMI_OUT_OF_RES_VAR	gPciOutOfResData={0};


//----------------------------------------------------------------------------------
//EfiDBE Key field definition used to sort resources by size 
//Function prototypes used for Compare keys we will use a custom way.
//We will be using combination UINT64 Length (LS64) + UINT64 Granularity (MS64).
INTN Cmp128IntRR(IN VOID *pContext, VOID *pRecord1, VOID *pRecord2);
INTN Cmp128IntKR(IN DBE_OFFSET_KEY_CONTEXT *pContext, VOID *pKey, VOID *pRecord);
//Initialize BAR DataBase KeyField Structure  
DBE_OFFSET_KEY_CONTEXT  BarKeyInfo = { EFI_FIELD_OFFSET(PCI_BAR,Length), 
                                    EFI_FIELD_SIZE(PCI_BAR,Length)+EFI_FIELD_SIZE(PCI_BAR,Gran)};
DBE_KEY_FIELD           gBarKey = {&Cmp128IntRR, &Cmp128IntKR, &BarKeyInfo};

//<AMI_SHDR_START>
//----------------------------------------------------------------------------
// Name:		gPciBusDb
//
// Description:	Bus order Data Base if fixed bus allocation selected we need 
//              to know how many buses does this bridge suppose to decode
// Notes: T_ITEM_LIST
//
//----------------------------------------------------------------------------
//<AMI_SHDR_END>
T_ITEM_LIST             gPciBusDb={0,0,NULL};

//<AMI_SHDR_START>
//----------------------------------------------------------------------------
// Name:		*gPciSetupData
//
// Description:	Global Setup Variable to get the setup settings pointer.
//
// Notes: PCI_SETUP_DATA
//
//----------------------------------------------------------------------------
//<AMI_SHDR_END>
PCI_SETUP_DATA		*gPciSetupData=NULL;

//<AMI_SHDR_START>
//----------------------------------------------------------------------------
// Name:		mMaxBusFound; mMaxBusScan; mMaxBusReport.
//
// Description:	Global counter of buses found.
//
// Notes: UINT8
//
//----------------------------------------------------------------------------
//<AMI_SHDR_END>
UINT8				mMaxBusFound;
UINTN               mMaxBusScan;
UINT8               mMaxBusReport=0;

//<AMI_SHDR_START>
//----------------------------------------------------------------------------
// Name:		gHostCnt
//
// Description:	Initial Global Variable to store Host Bridge Count.
//
// Notes: UINTN
//
//----------------------------------------------------------------------------
//<AMI_SHDR_END>
UINTN							gHostCnt;

//<AMI_SHDR_START>
//----------------------------------------------------------------------------
// Name:		gPciHost
//
// Description:	Initial Global Variable to store pointer on PCI Subsystem
// Host (This is very ROOT of the PCI Bus Driver Data).  
//
// Notes: PCI_HOST_INFO
//
//----------------------------------------------------------------------------
//<AMI_SHDR_END>
PCI_HOST_INFO					*gPciHost=NULL;

//----------------------------------------------------------------------------------
//Bot script save protocol interface
EFI_BOOT_SCRIPT_SAVE_PROTOCOL   *gBootScriptSave=NULL;

//----------------------------------------------------------------------------------
#if CSM_SUPPORT
EFI_LEGACY_BIOS_EXT_PROTOCOL	   		*gLegacyBiosExt=NULL;
#endif

//----------------------------------------------------------------------------------
#if S3_VIDEO_REPOST_SUPPORT == 1
EFI_EVENT           gVgaS3Event=NULL;
#endif

//----------------------------------------------------------------------------------
//Initial Global Variable to store RootBridge info
UINT16				gCpuCaheLineSize=0x10;
UINT8				gPciCaheLineSize=0;		

//----------------------------------------------------------------------------------
//To Avoid Enumerating AmiDebug Port Usb Device 
#if EFI_DEBUG || USB_DEBUG_TRANSPORT
AMI_DEBUGPORT_INFORMATION_HOB 	*gDbgPortHob=NULL;
DEBUG_PORT_INFO					gDbgPortInfo={0,0,0,0,0,0,0,0};
#endif

//==================================================================================
//Externals produced by VeB used by Pci Bus Driver
//==================================================================================
//Legacy IRQ routing table delivered from oempir.inc and PCIBoard.ASM
//IOAPIC IRQ routing table delivered from mppciirq.inc and PCIBoard.ASM
//PCI Buses Xlate Table
//Instead we have now AMI_BOARD_INFO_PROTOCOL
AMI_BOARD_INFO_PROTOCOL *gAmiBoardInfo=NULL;


//<AMI_SHDR_START>
//----------------------------------------------------------------------------
// Name:		gPciBusDriverBinding
//
// Description:	Extended PCI Bus Protocol instance for PciBus Driver
//
// Notes: AMI_PCI_EXT_PROTOCOL
//
//----------------------------------------------------------------------------
//<AMI_SHDR_END>

AMI_PCI_EXT_PROTOCOL gAmiExtPciBusProtocol = {
    PciExtIsPciExpresss,
    PciExtIsPciX,
    PciExtIsPciBrg,
    PciExtIsCrdBrg,
    PciExtIsDevice,
    PciExtClassCodes,    
    PciExtPicIrqRout,
    PciExtApicIrqRout,
    NULL
};



//<AMI_SHDR_START>
//----------------------------------------------------------------------------
// Name:		gPciBusDriverBinding
//
// Description:	Driver binding protocol instance for PciBus Driver
//
// Notes: EFI_DRIVER_BINDING_PROTOCOL
//
//----------------------------------------------------------------------------
//<AMI_SHDR_END>
EFI_DRIVER_BINDING_PROTOCOL gPciBusDriverBinding = {
	PciBusSupported,	//Supported
	PciBusStart,		//PciBusDrvStart,
	PciBusStop,			//PciBusDrvStop,
	((PCI_BUS_MAJOR_VER<<16)|(PCI_BUS_MINOR_VER<<8)|(PCI_BUS_REVISION)),				//Version 					
	NULL,				//Image Handle
	NULL				//DriverBindingHandle
};

#ifdef EFI_DEBUG
#ifndef EFI_COMPONENT_NAME2_PROTOCOL_GUID //old Core
#ifndef LANGUAGE_CODE_ENGLISH
#define LANGUAGE_CODE_ENGLISH "eng"
#endif
static BOOLEAN LanguageCodesEqual(
    CONST CHAR8* LangCode1, CONST CHAR8* LangCode2
){
    return    LangCode1[0]==LangCode2[0] 
           && LangCode1[1]==LangCode2[1]
           && LangCode1[2]==LangCode2[2];
}
static EFI_GUID gEfiComponentName2ProtocolGuid = EFI_COMPONENT_NAME_PROTOCOL_GUID;
#endif
//---------------------------------------------------------------------------
//Driver Name Interface of the PCI Bus Driver
//---------------------------------------------------------------------------
static UINT16 *gDriverName=L"AMI PCI Bus Driver";


//---------------------------------------------------------------------------
// Function Definitions
//---------------------------------------------------------------------------

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   ComponentNameGetControllerName()
//
// Description: This function is the one of interface functions of the
// OPTIONAL, EFI_COMPONENT_NAME_PROTOCOL. Suppose to retun Controller
// Name String. Currently returning EFI_UNSUPPORTED.
//
// Input:
//	EFI_COMPONENT_NAME_PROTOCOL 
//              *This               Pointer to EFI_COMPONENT_NAME_PROTOCOL.
//	EFI_HANDLE  ControllerHandle    EFI_HANDLE of the device which to return.
//	EFI_HANDLE  ChildHandle         OPTIONAL, an EFI_HANDLE of child device.
//	CHAR8       *Language           Pointer to 3 char Language name.
//	CHAR16      **ControllerName    Pointer to the data buffer for Name Sring.
//
// Output:	EFI_STATUS
//  EFI_SUCCESS         When everything is going on fine!
//	EFI_UNSUPPORTED     When feature not supported by the Driver.
//
// Reference: EFI_COMPONENT_NAME2_PROTOCOL
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
static EFI_STATUS ComponentNameGetControllerName (
		IN  EFI_COMPONENT_NAME2_PROTOCOL  *This,
		IN  EFI_HANDLE                   ControllerHandle,
		IN  EFI_HANDLE                   ChildHandle        OPTIONAL,
		IN  CHAR8                        *Language,
		OUT CHAR16                       **ControllerName )
{
	return EFI_UNSUPPORTED;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	ComponentNameGetDriverName()
//
// Description: This function is the one of interface functions of the OPTIONAL
// EFI_COMPONENT_NAME_PROTOCOL.	Retuning Driver Name String of the PCI BUS Driver.
//
// Input:
//	EFI_COMPONENT_NAME_PROTOCOL 
//              *This               Pointer to EFI_COMPONENT_NAME_PROTOCOL.
//	CHAR8       *Language           Pointer to 3 char Language name.
//	CHAR16      **ControllerName    Pointer to the data buffer for Name Sring.
//
// Output:	EFI_STATUS
//  EFI_SUCCESS         When everything is going on fine!
//	EFI_UNSUPPORTED     When feature not supported by the Driver.
//
// Reference:	EFI_COMPONENT_NAME_PROTOCOL
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
static EFI_STATUS ComponentNameGetDriverName(IN  EFI_COMPONENT_NAME2_PROTOCOL  *This,
						IN  CHAR8                        *Language,
						OUT CHAR16                       **DriverName)
{
	//Supports only English
	if(!Language || !DriverName) return EFI_INVALID_PARAMETER;

	if (!LanguageCodesEqual( Language, LANGUAGE_CODE_ENGLISH))
        return EFI_UNSUPPORTED;
	else 
        *DriverName=gDriverName;
	
	return EFI_SUCCESS;
}

//<AMI_SHDR_START>
//----------------------------------------------------------------------------
// Name:		gComponentName
//
// Description:	Declaration of the EFI_COMPONENT_NAME_PROTOCOL
//
// Fields:		Name				Type					Description
//          ------------------------------------------------------------------
//  ComponentNameGetDriverName,		F_PTR 		DriverName function pointer.
//  ComponentNameGetControllerName, F_PTR		ControllerName function pointer.
//  "eng"							CHAR8 		Language list Buffer.
//----------------------------------------------------------------------------
//<AMI_SHDR_END>
static EFI_COMPONENT_NAME2_PROTOCOL gComponentName = {
  ComponentNameGetDriverName,
  ComponentNameGetControllerName,
  LANGUAGE_CODE_ENGLISH
};

#endif

//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
//PCI BUS Driver Entry Point
//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	PciBusEntryPoint()
//
// Description:	This function is the entry point for PCI BUS Driver. 
// Since PCI BUS Driver follows EFI 1.1 driver model in it's entry point
// it will initialize some global data and install
// EFI_DRIVER_BINDING_PROTOCOL. 
//
// Input:
//	EFI_HANDLE          ImageHandle     Image handle.
//	EFI_SYSTEM_TABLE    *SystemTable    Pointer to the EFI system table.
//
// Output:	EFI_STATUS
//	EFI_SUCCESS         When everything is going on fine!
//	EFI_NOT_FOUND       When something required is not found!
//	EFI_DEVICE_ERROR    When the device is not responding!
//
// Notes: 
//  Entry Points are used to locate or install protocol interfaces and
// notification events. 
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS PciBusEntryPoint(IN EFI_HANDLE			ImageHandle,
							IN EFI_SYSTEM_TABLE   *SystemTable )
{
	static EFI_GUID CpuInfoHobGuid = AMI_CPUINFO_HOB_GUID;
#if EFI_DEBUG || USB_DEBUG_TRANSPORT
	static EFI_GUID DbgPortHobGuid = AMI_DEBUGPORT_HOB_GUID;
#endif
	static EFI_GUID HobListGuid	= HOB_LIST_GUID;
	CPUINFO_HOB					*CpuInfoHob;
	EFI_STATUS					Status;	
//--------------------------------------------------------------------

	//Init some Global Data
	InitAmiLib(ImageHandle,SystemTable);
	gPciBusDriverBinding.DriverBindingHandle=NULL;
	gPciBusDriverBinding.ImageHandle=ImageHandle;

	//Get CPU Cache Line Size 
	CpuInfoHob=(CPUINFO_HOB*)GetEfiConfigurationTable(pST,&HobListGuid);
	if(CpuInfoHob==NULL) Status=EFI_UNSUPPORTED;
	else Status=FindNextHobByGuid(&CpuInfoHobGuid,(VOID**)&CpuInfoHob);
	
	if(!EFI_ERROR(Status)){
		gCpuCaheLineSize=CpuInfoHob->CacheLineSize; //in bytes
  		gPciCaheLineSize=(UINT8)gCpuCaheLineSize/4; //in DWORDs
		PCI_TRACE((TRACE_PCI,"PciBus: Find CpuInfo HOB! gCpuCaheLineSize=%X; gPciCaheLineSize=%X;\n", gCpuCaheLineSize, gPciCaheLineSize));
	} else {
        PCI_TRACE((TRACE_PCI,"PciBus: Unable to find CpuInfo HOB! Setting default CacheLineSize -> %X\n", gCpuCaheLineSize));
    }
		
#if EFI_DEBUG || USB_DEBUG_TRANSPORT
//Get Ami Debug Port Settings
	gDbgPortHob=(AMI_DEBUGPORT_INFORMATION_HOB*)GetEfiConfigurationTable(pST,&HobListGuid);
	if(gDbgPortHob) Status=FindNextHobByGuid(&DbgPortHobGuid,(VOID**)&gDbgPortHob);
	if(EFI_ERROR(Status)) gDbgPortHob=NULL;
	else {
		Status=gDbgPortHob->GetDebugPortProperties(gDbgPortHob, &gDbgPortInfo);
		ASSERT_EFI_ERROR(Status);
	}
#endif

	//Install Multiple Prot Drv. Binding and Comp. Name
	Status = pBS->InstallMultipleProtocolInterfaces(
					&gPciBusDriverBinding.DriverBindingHandle,
					&gDriverBindingProtocolGuid,&gPciBusDriverBinding,
#ifdef EFI_DEBUG
					&gEfiComponentName2ProtocolGuid,&gComponentName,
#endif
					NULL);
	//Here we can set up notification events if needed


	//------------------------------------
	return Status;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   IsFunc0OfMfDev()
//
// Description: Checks if PCI_DEV_INFO data passed belongs to Function 0 of 
// Multy-Functional device.
//
// Input:
//  PCI_DEV_INFO    *Device     Pointer to PCI Device Private Data structure.
//
// Output:	BOOLEAN
//  TRUE    Device is Function 0 of Mulifunctional device.
//  FALSE   Device is not Function 0 of Mulifunctional device.
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
BOOLEAN IsFunc0OfMfDev(PCI_DEV_INFO *Device ){
    //If (Func0==NULL && FuncCount==0) function is a single function device, following fields are not used and reserved;
    //If (Func0!=NULL && FuncCount==0) function is one of the Func1..Func7 of multyfunc device Func0 points on DevFunc0;
    //If (Func0!=NULL && (FuncCount!=0 || FuncInitCnt!=0)) function is Func0 of multyfunc device DevFunc holds pointers at all other Func1..7 found
    //If (Func0==NULL && FuncCount!=0) Illehgal combination - reserved!
    if((Device->Func0!=NULL) && ((Device->FuncInitCnt!=0)||(Device->FuncCount!=0))) return TRUE; 
    return FALSE;      
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   IsFunc0()
//
// Description: Checks if PCI_DEV_INFO is Function 0 of PCI device.
//
// Input:
//  PCI_DEV_INFO    *Device     Pointer to PCI Device Private Data structure.
//
// Output:	BOOLEAN
//  TRUE    Device is Function 0 of Mulifunctional device.
//  FALSE   Device is not Function 0 of Mulifunctional device.
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
BOOLEAN IsFunc0(PCI_DEV_INFO *Device ){
    //If (Func0==NULL && FuncCount==0) function is a single function device, following fields are not used and reserved;
    //If (Func0!=NULL && FuncCount==0) function is one of the Func1..Func7 of multyfunc device Func0 points on DevFunc0;
    //If (Func0!=NULL && (FuncCount!=0 || FuncInitCnt!=0)) function is Func0 of multyfunc device DevFunc holds pointers at all other Func1..7 found
    //If (Func0==NULL && FuncCount!=0) Illehgal combination - reserved!
    if(IsFunc0OfMfDev(Device)) return TRUE;
    if((Device->Func0==NULL) && (Device->FuncInitCnt==0) && (Device->FuncCount==0)) return TRUE; 
    return FALSE;      
}


//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   CpyItemLst()
//
// Description: Creates a copy of T_ITEM_LST structure.
//
// Input:
//  T_ITEM_LIST *Lst        Pointer to the structure to copy.
//  T_ITEM_LIST **NewLstPtr Double Pointer to the copied data (Memory allocation is done by this function).
//
// Output:	EFI_STATUS
//  EFI_SUCCESS             When everything is going on fine!
//  EFI_OUT_OF_RESOURCES    When system runs out of resources.
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS CpyItemLst(T_ITEM_LIST *Lst, T_ITEM_LIST **NewLstPtr)
{	
    T_ITEM_LIST     *NewLst;
//--------------------------
	if(*NewLstPtr == NULL) *NewLstPtr = MallocZ(sizeof(T_ITEM_LIST));

	if (*NewLstPtr==NULL) return EFI_OUT_OF_RESOURCES;
	
	NewLst = *NewLstPtr; 
	NewLst->InitialCount = Lst->InitialCount;
	if (Lst->InitialCount == 0) return EFI_SUCCESS; 

	NewLst->Items = MallocZ( Lst->InitialCount * sizeof(VOID*) );
	if (!NewLst->Items) return EFI_OUT_OF_RESOURCES;

	pBS->CopyMem((VOID*)NewLst->Items,(VOID*)Lst->Items,sizeof(VOID*)*Lst->ItemCount);

	NewLst->ItemCount = Lst->ItemCount; 

    return EFI_SUCCESS;    
}


#if HOTPLUG_SUPPORT
//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
//Following function to initialize PCI Root Hotplug Controller
//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	CheckRootHotplug()
//
// Description: This function will update pointer to PCI_RHPC_INFO of
// Bridge Type device which creates a hot plug bus. Also if "Device" 
// creates the 'home bus' for Root HPC it will initialize Root HPC and
// record the HPC state;
//
// Input:
//  PCI_DEV_INFO    *Device     Pointer to PCI Device Private Data structure.
//
// Output:	EFI_STATUS
//  EFI_SUCCESS             When everything is going on fine!
//  EFI_NOT_FOUND           When Device not present in the system.
//  EFI_OUT_OF_RESOURCES    When system runs out of resources.
//  EFI_DEVICE_ERROR        When driver fails access PCI Bus.
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS CheckRootHotplug(PCI_DEV_INFO *Device){
	EFI_STATUS			Status=EFI_SUCCESS;
	EFI_DEVICE_PATH_PROTOCOL *dp=NULL;
	PCI_HPC_INFO		*rhpc;
	UINTN				i;
//---------------
	if(Device->Type==tPci2PciBrg || Device->Type==tPci2CrdBrg || Device->Type==tPciRootBrg){
		//we have identify and Init all the Root Hpc and HPB
		if(Device->HostData->InitRhpcCount==Device->HostData->RhpcCount) return EFI_SUCCESS;
        PROGRESS_CODE(DXE_PCI_BUS_HPC_INIT);
		//here we must check if 2 things:
		//	1.If "Device" Device Path mutches with one of Root Hpc Device pathes 
		//	2.If "Device" Device Path mutches with one of Root Hpb Device pathes 
		for(i=0; i<Device->HostData->RhpcCount; i++){
			rhpc=Device->HostData->RhpcList[i];
			//if this controller already has been initialized - keep going
			if(rhpc->Initialized && rhpc->BusFound)	continue;
			
	
			//check if it is a secondary interface of the bridge where RHPC is sitting
			if(!rhpc->BusFound){
				if(!DPCmp(Device->DevicePath, rhpc->HpcLocation->HpbDevicePath)){
					rhpc->HpbBridge=Device;
					rhpc->BusFound=TRUE;
					Device->HotPlug=rhpc;
					PCI_TRACE((TRACE_PCI,"PciBus: Found HP Bus Bridge @ B%X|D%X|F%X \n\n", Device->Address.Addr.Bus,Device->Address.Addr.Device, Device->Address.Addr.Function));
				}
			}	
			
			if(!rhpc->Initialized){
				//We will cut the last node of the HPC device path
				//resulting Device Path will correspond to the ParentBridge.DevicePath of the HPC
				dp=DPCut(rhpc->HpcLocation->HpcDevicePath); 
				//if the HPC sits behind this bridge get the secondary I/F bus number 
				if(!DPCmp(Device->DevicePath,dp)){
					EFI_DEVICE_PATH_PROTOCOL	*tdp;
				//-----------------------------------
					rhpc->HpcPciAddr.Addr.Bus=mMaxBusFound; 
					tdp=DPGetLastNode(rhpc->HpcLocation->HpcDevicePath);			
				
					rhpc->HpcPciAddr.Addr.Device=((PCI_DEVICE_PATH*)tdp)->Device;
					rhpc->HpcPciAddr.Addr.Function=((PCI_DEVICE_PATH*)tdp)->Function;

					//we will not set up an event to signal when HPC initialization is ready
					//that will give us a possibility to enumerate PCI BUS in one pass
					Status=Device->HostData->HpInitProt->InitializeRootHpc(
							Device->HostData->HpInitProt, rhpc->HpcLocation->HpcDevicePath,
							rhpc->HpcPciAddr.ADDR, NULL, &rhpc->HpcState);
					
					ASSERT_EFI_ERROR(Status);	
					rhpc->Owner=Device;
					rhpc->Initialized=TRUE;
					PCI_TRACE((TRACE_PCI,"PciBus: Found RHPC @ B%X|D%X|F%X \n", Device->Address.Addr.Bus,Device->Address.Addr.Device, Device->Address.Addr.Function)); 
				}			
			}
			
			//if we come here we did some step of the initialization process
			//let's check if this controller has been completly initialized.
			//if so we did our job. there are no reasons to stay in this loop any longer
			if(rhpc->Initialized && rhpc->BusFound)	{
				Device->HostData->InitRhpcCount++;
				break;
			}
  
		}//for
	} 
	if(dp)pBS->FreePool(dp);
	return Status;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	IsHpb()
//
// Description: This function will check if "Device" passed is the Bridge
// Type Device with hotplug support.
//
// Input:
//  PCI_DEV_INFO    *Device     Pointer to PCI Device Private Data structure.
//
// Output:  BOOLEAN
//  TRUE    If "Device" is a Bridge with HPC on it.
//  FALSE   Otherwice.
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

BOOLEAN IsHpb(PCI_DEV_INFO *Device){

	//check if it is the right type of device to have Hotplug capabilities 
	if(!((Device->Type==tPci2PciBrg)||(Device->Type==tPci2CrdBrg)||(Device->Type==tPciRootBrg))) return FALSE;

	//Check if it has Root Hpc or PciExpress capabilities
	if(!Device->HotPlug && !Device->PciExpress) return FALSE;
	
	//If Device is PciExpress, check if SLOT CAPABILITIES Register supports Hotplug
	if(Device->PciExpress && (!Device->PciExpress->SlotCap.HpCapable))return FALSE; 

	return TRUE;
}


//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   GetHpbResPadding()
//
// Description: This function will get and apply resource padding
// requirements for the PCI to PCI Bridge or Card Bus Bridge, if this
// Bridge is supports hot plug.
//
// Input:
//  PCI_DEV_INFO    *Device     Pointer to PCI Device Private Data structure.
//
// Output:	EFI_STATUS
//  EFI_SUCCESS             When everything is going on fine!
//  EFI_NOT_FOUND           When Device not present in the system.
//  EFI_OUT_OF_RESOURCES    When system runs out of resources.
//  EFI_DEVICE_ERROR        When driver fails access PCI Bus.
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS GetHpbResPadding(PCI_DEV_INFO *Device){
	EFI_STATUS		Status=0;
//-----------------------------
	if(IsHpb(Device)){
		PCI_BRG_EXT		*ext=(PCI_BRG_EXT*)(Device+1);
		ASLR_QWORD_ASD	*cnf, *res;
		PCI_BAR			*bar;
	//----------------------------
		Status=Device->HostData->HpInitProt->GetResourcePadding(Device->HostData->HpInitProt, 
						Device->HotPlug->HpcLocation->HpcDevicePath, Device->HotPlug->HpcPciAddr.ADDR, 
						&Device->HotPlug->HpcState,&cnf,&ext->PaddAttr);
		
		ASSERT_EFI_ERROR(Status);
		if(EFI_ERROR(Status)) return Status;
		
		if(ext->PaddAttr==EfiPaddingPciRootBridge){
			pBS->FreePool(cnf);
			return Status;
		}

		//Check if we got a valid descriptors in cfg buffer
		if(!ValidateDescriptorBlock(cnf, tResAll, FALSE))return EFI_INVALID_PARAMETER;
		
		res=cnf;	
		while(res->Hdr.HDR!=ASLV_END_TAG_HDR) {
			bar=NULL;
			switch(res->Type){
				case ASLRV_SPC_TYPE_BUS	:
					bar=&ext->Pad[rtBus];
				break;
				case ASLRV_SPC_TYPE_IO	:
						bar=&ext->Pad[rtIo16];
						bar->Type=tBarIo16;
						if(res->_GRA==32){
							bar=&ext->Pad[rtIo32];
							bar->Type=tBarIo32;
						}
				break;
				case ASLRV_SPC_TYPE_MEM	:
					if(res->_GRA==32){
						if(res->TFlags.MEM_FLAGS._MEM==ASLRV_MEM_CEPF)	{
							bar=&ext->Pad[rtMmio32p];
							bar->Type=tBarMmio32pf;
						} else {
							bar=&ext->Pad[rtMmio32];
							bar->Type=tBarMmio32;
						}
					} else {
						if(res->_GRA==64){
							if(res->TFlags.MEM_FLAGS._MEM==ASLRV_MEM_CEPF){
								bar=&ext->Pad[rtMmio64p];
								bar->Type=tBarMmio64pf;
							} else {
								bar=&ext->Pad[rtMmio64];
								bar->Type=tBarMmio64;
							}
						} else return EFI_INVALID_PARAMETER; //no other options alloud
					}
				break;
				default: return EFI_INVALID_PARAMETER;
			} //switch

			bar->Length=res->_LEN;
			bar->Gran=res->_MAX;
			res++;		
		} //while
		pBS->FreePool(cnf); 
	} 
	return Status;
}

//==============================================================================
#endif

//==============================================================================
// Device Handle Helper Functions
//==============================================================================

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   MakePciDevicePath()
//
// Description: This function will take Parent DevPath and extand it with
// Current ""Dev", Device Path and update pointer of the "Dev->DevPath"
//
// Input:
//  PCI_DEV_INFO    *Dev    Pointer to PCI Device Private Data structure.
//
// Output:	EFI_STATUS
//  EFI_SUCCESS             When everything is going on fine!
//  EFI_NOT_FOUND           When Device not present in the system.
//  EFI_OUT_OF_RESOURCES    When system runs out of resources.
//  EFI_DEVICE_ERROR        When driver fails access PCI Bus.
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS MakePciDevicePath(PCI_DEV_INFO *Dev)
{
	static PCI_DEVICE_PATH			pcidp;	
//-------------------------------------------
	//we have a wonderful Lib function DPAddNode - use it!
	pcidp.Header.SubType=HW_PCI_DP;
	pcidp.Header.Type=HARDWARE_DEVICE_PATH;
	SET_NODE_LENGTH(&pcidp.Header,HW_PCI_DEVICE_PATH_LENGTH);

	pcidp.Function=Dev->Address.Addr.Function;
	pcidp.Device=Dev->Address.Addr.Device;
	
	Dev->DevicePath=DPAddNode(Dev->ParentBrg->DevicePath, &pcidp.Header);
	if(Dev->DevicePath)return EFI_SUCCESS;	
	else return EFI_OUT_OF_RESOURCES;
}


//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   FindRbHandle()
//
// Description: This function will finds Root Bridge Device Handle for
// the "Device".
//
// Input:
//  PCI_DEV_INFO    *Device Pointer to PCI Device Private Data structure.
//
// Output:	EFI_HANDLE
//  !=NULL          When everything is going on fine!
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_HANDLE FindRbHandle(PCI_DEV_INFO *Device){
	EFI_HANDLE  	rbh=NULL;
	PCI_DEV_INFO	*dev=Device;
//---------------------
	while(dev->Type!=tPciRootBrg)dev=dev->ParentBrg; 
	rbh=dev->Handle;
	return rbh; 
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   FindPciDeviceByHandleBrg()
//
// Description: This function Searches PCI Bridge Subsystem Database to find
// device which have passed "Handle"
//
// Input:
//  PCI_BRG_INFO    *Brg    Pointer to PCI Bridge Device Private Data structure.
//  EFI_HANDLE      Handle  Device Handle to search for.
//
// Output:	PCI_DEV_INFO
//  !=NULL          When everything is going on fine!
//  ==NULL          Not Found.
//
// Notes: This is a subordinate function of FindPciDeviceByHandle()
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
PCI_DEV_INFO *FindPciDeviceByHandleBrg(PCI_BRG_INFO *Brg, EFI_HANDLE Handle)
{
	PCI_DEV_INFO	*dev, *res=NULL;	
	INTN			i;
//--------------------------------------------------------------------
	if(Brg->Common.Handle==Handle) return &Brg->Common;

	for(i=0; i<(INTN)Brg->Bridge.ChildCount; i++){
		dev=Brg->Bridge.ChildList[i];
		res=NULL;
		if(dev->Handle==Handle) {
			res=dev;
			break;
		}
	
		if(dev->Type==tPci2PciBrg) res=FindPciDeviceByHandleBrg((PCI_BRG_INFO*)dev,Handle);
		
		if(res) break;
	}
	return res;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   FindPciDeviceByHandle()
//
// Description: This function finds Pci Device by "Handle" passed
//
// Input:
//  EFI_HANDLE  Handle  PCI Device Handle.
//
// Output:	PCI_DEV_INFO
//  !=NULL      When everything is going on fine!
//  ==NULL      Not Found.
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
PCI_DEV_INFO *FindPciDeviceByHandle(EFI_HANDLE Handle)
{
	PCI_BRG_INFO	*brg;
	UINTN			i,j;
	PCI_HOST_INFO	*lhst;
	PCI_DEV_INFO	*res;
//--------------------------------------------------------------------
	for(j=0; j<gHostCnt; j++){
		lhst=&gPciHost[j];
		for(i=0; i<lhst->RbCount; i++){ 
			brg=(PCI_BRG_INFO*)lhst->RootBridges[i];
			res=FindPciDeviceByHandleBrg(brg, Handle);
			if(res) return res;
		}
	}
	return NULL;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   DoPrepController()
//
// Description: This function will follow the rules of calling seqence of
// Platform Preprocess Controller it will call:
//	1.Platform PreprocessController with ChipsetEntery
//	2.Host Brg Preprocess Controller 
//	3.Platform PreprocessController with ChipsetExit
//
// Input:
//  PCI_DEV_INFO    *Device Pointer to PCI Device Private Data structure.
//
// Output:	EFI_STATUS
//  EFI_SUCCESS             When everything is going on fine!
//  EFI_NOT_FOUND           When Device not present in the system.
//  EFI_OUT_OF_RESOURCES    When system runs out of resources.
//  EFI_DEVICE_ERROR        When driver fails access PCI Bus.
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS DoPrepController(PCI_DEV_INFO* Device)
{
	EFI_STATUS										Status=0;	
	EFI_PCI_CONTROLLER_RESOURCE_ALLOCATION_PHASE 	ph;
	EFI_HANDLE  									rbh=FindRbHandle(Device);
//-----------
	if(Device->Type==tPci2PciBrg) ph=EfiPciBeforeChildBusEnumeration;
	else ph=EfiPciBeforeResourceCollection;

	//If System has PciPlatform protocol installed
	if(Device->HostData->PlatformProt){
		Status=Device->HostData->PlatformProt->PlatformPrepController(
  				Device->HostData->PlatformProt, Device->HostData->HostHandle,
				rbh,Device->Address.Addr, ph, ChipsetEntry);
		ASSERT_EFI_ERROR(Status);
	}

	Status=Device->HostData->ResAllocProt->PreprocessController(
				Device->HostData->ResAllocProt,rbh,Device->Address.Addr, ph);
	ASSERT_EFI_ERROR(Status);

	if(Device->HostData->PlatformProt){
		Status=Device->HostData->PlatformProt->PlatformPrepController(
  				Device->HostData->PlatformProt, Device->HostData->HostHandle,
				rbh, Device->Address.Addr, ph, ChipsetExit);
		ASSERT_EFI_ERROR(Status);
	}	
	return Status;
}


//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   DoPciNotify()
//
// Description: This function will follow the rules of calling seqence of
// Platform Notify it will call: 
//	1.Platform NotifyPhase with ChipsetEntery
//	2.Host Brg NotifyPhase 
//	3.Platform NotifyPhase with ChipsetExit
//
// Input:
//  PCI_DEV_INFO    *Device Pointer to PCI Device Private Data structure.
//
// Output:	EFI_STATUS
//  EFI_SUCCESS             When everything is going on fine!
//  EFI_NOT_FOUND           When Device not present in the system.
//  EFI_OUT_OF_RESOURCES    When system runs out of resources.
//  EFI_DEVICE_ERROR        When driver fails access PCI Bus.
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS DoPciNotify(PCI_HOST_INFO *Host, EFI_PCI_HOST_BRIDGE_RESOURCE_ALLOCATION_PHASE Phase)
{
	EFI_STATUS	Status=0;	
//-----------
	if(Host->PlatformProt){
		Status=Host->PlatformProt->PhaseNotify(Host->PlatformProt,Host->HostHandle,Phase,ChipsetEntry);
		ASSERT_EFI_ERROR(Status);
	}
	
	Status=Host->ResAllocProt->NotifyPhase(Host->ResAllocProt,Phase);
	ASSERT_EFI_ERROR(Status);

	if(Host->PlatformProt){
		Status=Host->PlatformProt->PhaseNotify(Host->PlatformProt,Host->HostHandle,Phase,ChipsetExit);
		ASSERT_EFI_ERROR(Status);
	}
	return Status;
}


//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	PciCfg8()
//
// Description: Will do PCI Configuration Space Access 8 bit width
//
// Input:
//  ROOT_BRIDGE_IO_PROTOCOL *RbIo   Pointer to PciRootBridgeIO Protocol.
//  PCI_CFG_ADDR            addr    PCI_CFG_ADDR filled by caller
//  BOOLEAN                 wr      TRUE = Write FALSE = Read 
//  UINT8                   *buff   Pointer Data Buffer. 
//
// Output:  EFI_STATUS
//  EFI_SUCCESS             When everything is going on fine!
//  EFI_NOT_FOUND           When Device not present in the system.
//  EFI_DEVICE_ERROR        When driver fails access PCI Bus.
//
// Referals:PCI_CFG_ADDR
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS PciCfg8(EFI_PCI_ROOT_BRIDGE_IO_PROTOCOL *RbIo, PCI_CFG_ADDR addr, BOOLEAN wr, UINT8 *buff){
	if(wr)return RbIo->Pci.Write(RbIo, EfiPciWidthUint8, addr.ADDR, 1, (VOID*)buff);
	else return RbIo->Pci.Read(RbIo, EfiPciWidthUint8, addr.ADDR, 1, (VOID*)buff);
}
//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	PciCfg16()
//
// Description: Will do PCI Configuration Space Access 16 bit width
//
// Input:
//  ROOT_BRIDGE_IO_PROTOCOL *RbIo   Pointer to PciRootBridgeIO Protocol.
//  PCI_CFG_ADDR            addr    PCI_CFG_ADDR filled by caller
//  BOOLEAN                 wr      TRUE = Write FALSE = Read 
//  UINT16                  *buff   Pointer Data Buffer. 
//
// Output:  EFI_STATUS
//  EFI_SUCCESS             When everything is going on fine!
//  EFI_NOT_FOUND           When Device not present in the system.
//  EFI_DEVICE_ERROR        When driver fails access PCI Bus.
//
// Referals:PCI_CFG_ADDR
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS PciCfg16(EFI_PCI_ROOT_BRIDGE_IO_PROTOCOL *RbIo, PCI_CFG_ADDR addr, BOOLEAN wr, UINT16 *buff){
	EFI_STATUS	Status;
//------------
	if(wr)Status=RbIo->Pci.Write(RbIo, EfiPciWidthUint16, addr.ADDR, 1, (VOID*)buff);
	else Status=RbIo->Pci.Read(RbIo, EfiPciWidthUint16, addr.ADDR, 1, (VOID*)buff);
	//it might be a Width issue on Pci Root bridge level 
	if(Status==EFI_INVALID_PARAMETER) {
		UINT8	*b=(UINT8*)buff;
	//--------------------
		Status=PciCfg8(RbIo, addr, wr, b);
		if(EFI_ERROR(Status)) return Status;
      
        //Check if Extended register used then Addr.Register is ignored.
        if( addr.Addr.ExtendedRegister != 0) addr.Addr.ExtendedRegister += 1;
        else addr.Addr.Register += 1;

		b++;
		Status=PciCfg8(RbIo, addr, wr, b);
	}
	return Status;
}


//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	PciCfg32()
//
// Description: Will do PCI Configuration Space Access 32 bit width
//
// Input:
//  ROOT_BRIDGE_IO_PROTOCOL *RbIo   Pointer to PciRootBridgeIO Protocol.
//  PCI_CFG_ADDR            addr    PCI_CFG_ADDR filled by caller
//  BOOLEAN                 wr      TRUE = Write FALSE = Read 
//  UINT32                  *buff   Pointer Data Buffer. 
//
// Output:  EFI_STATUS
//  EFI_SUCCESS             When everything is going on fine!
//  EFI_NOT_FOUND           When Device not present in the system.
//  EFI_DEVICE_ERROR        When driver fails access PCI Bus.
//
// Referals:PCI_CFG_ADDR
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS PciCfg32(EFI_PCI_ROOT_BRIDGE_IO_PROTOCOL *RbIo, PCI_CFG_ADDR addr, BOOLEAN wr, UINT32 *buff){
	EFI_STATUS	Status;
//------------
	if(wr)Status=RbIo->Pci.Write(RbIo, EfiPciWidthUint32, addr.ADDR, 1, (VOID*)buff);
	else Status=RbIo->Pci.Read(RbIo, EfiPciWidthUint32, addr.ADDR, 1, (VOID*)buff);
	//it might be a Width issue on Pci Root bridge level 
	if(Status==EFI_INVALID_PARAMETER) {
		UINT16	*b=(UINT16*)buff;
	//--------------------
		Status=PciCfg16(RbIo, addr, wr, b);
		if(EFI_ERROR(Status)) return Status;

        //Check if Extended register used then Addr.Register is ignored.
        if( addr.Addr.ExtendedRegister != 0) addr.Addr.ExtendedRegister += 2;
        else addr.Addr.Register += 2;

		b++;
		Status=PciCfg16(RbIo, addr, wr, b);
	}
	return Status;
}


//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	PciCfg64()
//
// Description: Will do PCI Configuration Space Access 64 bit width
//
// Input:
//  ROOT_BRIDGE_IO_PROTOCOL *RbIo   Pointer to PciRootBridgeIO Protocol.
//  PCI_CFG_ADDR            addr    PCI_CFG_ADDR filled by caller
//  BOOLEAN                 wr      TRUE = Write FALSE = Read 
//  UINT64                  *buff   Pointer Data Buffer. 
//
// Output:  EFI_STATUS
//  EFI_SUCCESS             When everything is going on fine!
//  EFI_NOT_FOUND           When Device not present in the system.
//  EFI_DEVICE_ERROR        When driver fails access PCI Bus.
//
// Referals:PCI_CFG_ADDR
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS PciCfg64(EFI_PCI_ROOT_BRIDGE_IO_PROTOCOL *RbIo, PCI_CFG_ADDR addr, BOOLEAN wr, UINT64 *buff){
	EFI_STATUS	Status;
//------------
	if(wr)Status=RbIo->Pci.Write(RbIo, EfiPciWidthUint64, addr.ADDR, 1, (VOID*)buff);
	else Status=RbIo->Pci.Read(RbIo, EfiPciWidthUint64, addr.ADDR, 1, (VOID*)buff);
	//it might be a Width issue on Pci Root bridge level 
	if((Status==EFI_INVALID_PARAMETER) && (buff!=NULL)) {
		UINT32	*b=(UINT32*)buff;
	//--------------------
		Status=PciCfg32(RbIo, addr, wr, b);
		if(EFI_ERROR(Status)) return Status;
        
        //Check if Extended register used then Addr.Register is ignored.
        if( addr.Addr.ExtendedRegister != 0) addr.Addr.ExtendedRegister += 4;
        else addr.Addr.Register += 4;
        
		b++;
		Status=PciCfg32(RbIo, addr, wr, b);
	}
	return Status;
}


//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
//	PCI IO Protocol Functions Implementation Protocol 
//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

//==================================================================================
// PciIoProtocol Supporting Functions
//==================================================================================

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	BarCheckType()
//
// Description: 
//  This helper function will check if Base Address Register(BAR) selected
// for PciIo operation is of valid type and has been initialized;
//
// Input:
//  PCI_DEV_INFO    *Dev        Pointer to PciDevice Info structure.
//  UINT8           BarIndex    Index of the BAR within PCI device 
//  PCI_BAR_TYPE    BarType     Indicating what to check - IO or Memory.
//
// Output:  BOOLEAN
//  TRUE    BAR supports selected transaction.
//	FALSE   BAR does not support selected transaction.
//
// Referals: PCI_DEV_INFO; PCI_BAR_TYPE
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
BOOLEAN BarCheckType(PCI_DEV_INFO  *Dev, UINT8 BarIndex, PCI_BAR_TYPE BarType)
{
	PCI_BAR *bar=&Dev->Bar[BarIndex];
//-------------------------------------
	switch(BarType){
    	case tBarMem:
			if (bar->Type != tBarMmio32 && 
				bar->Type != tBarMmio32pf &&
				bar->Type != tBarMmio64 &&
				bar->Type != tBarMmio64pf ) return FALSE;
			break;

		case tBarIo:
			if (bar->Type != tBarIo32 && bar->Type != tBarIo16) 
				return FALSE;
			break;
		default: return FALSE; 
	}
 
  return TRUE;
}


//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	PciIoCheckBar()
//
// Description: This helper function will check if parameters passed to the 
// PCI IO Protocol to read or write a PCI resources are correct.
//
// Input:
//  PCI_DEV_INFO    *Dev    Pointer to PciDevice Info structure.
//  UINT8           BarInd  Index of the BAR within PCI device.
//	PCI_BAR_TYPE    BarType Indicating what to check - IO or Memory.
//  EFI_PCI_IO_PROTOCOL_WIDTH   Width   Width of transaction.
//  UINTN           Count   Number of bytes been transfered.
//  UINT64          *Offset Offset within BAR address space to start from.
//
// Output:  EFI_STATUS
//  EFI_SUCCESS             When everything is going on fine!
//  EFI_INVALID_PARAMETER   When some of the parameters are invalid.
//
// Referals: PCI_DEV_INFO; PCI_BAR_TYPE;EFI_PCI_IO_PROTOCOL_WIDTH
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS PciIoCheckBar(PCI_DEV_INFO *Dev, UINT8 BarInd, PCI_BAR_TYPE Type,
						EFI_PCI_IO_PROTOCOL_WIDTH Width, UINTN Count, UINT64 *Offset)
{
	if ( Width<0 || Width>=EfiPciIoWidthMaximum ) return EFI_INVALID_PARAMETER;

	if (BarInd==0xFF) return EFI_SUCCESS;
	
	if (BarInd>=MAX_PCI_BAR) return EFI_INVALID_PARAMETER;

	if (!BarCheckType(Dev,BarInd,Type))return EFI_INVALID_PARAMETER;

	// If Width is EfiPciIoWidthFillUintX then convert to EfiPciIoWidthUintX
	if (Width >= EfiPciWidthFifoUint8 && Width <= EfiPciWidthFifoUint64) Count = 1;
	Width &= 0x03;

	if((*Offset+Count*((UINTN)1<<Width))-1 >= Dev->Bar[BarInd].Length) return EFI_INVALID_PARAMETER;

	*Offset = *Offset+(UINTN)Dev->Bar[BarInd].Base;

	return EFI_SUCCESS;
}


//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   PciIoCheckConfig()
//
// Description: This helper function will check if parameters passed to the
// PCI IO Protocol to made a PCI Config Space Access are correct
//
// Input:
//  PCI_DEV_INFO                *Dev    Pointer to PciDevice Info structure.
//  EFI_PCI_IO_PROTOCOL_WIDTH   Width   Width of transaction been performed.
//  UINTN                       Count   Number of bytes been transfered.
//  UINT64                      *Offset Offset to start from.
//
// Output:  EFI_STATUS
//  EFI_SUCCESS             When everything is going on fine!
//  EFI_INVALID_PARAMETER   When some of the parameters are invalid.
//
// Referals: PCI_DEV_INFO; PCI_BAR_TYPE; EFI_PCI_IO_PROTOCOL_WIDTH
//
//<AMI_PHDR_END>
//**********************************************************************
EFI_STATUS PciIoCheckConfig(PCI_DEV_INFO  *Dev, EFI_PCI_IO_PROTOCOL_WIDTH Width,
							UINTN Count, UINT64 *Offset)
{
	if(Width<0 || Width>= EfiPciIoWidthMaximum) return EFI_INVALID_PARAMETER;

	// If Width is EfiPciIoWidthFillUintX then convert to EfiPciIoWidthUintX
	Width &= 0x03;
	if((*Offset + Count * ((UINTN)1 << Width)) - 1 > 0xFF) return EFI_UNSUPPORTED;

	*Offset=PCI_ASSEMBLE_ADDR(Dev->Address.Addr.Bus,
		Dev->Address.Addr.Device,Dev->Address.Addr.Function,*Offset);
  return EFI_SUCCESS;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   SetIdeDevMode()
//
// Description: This function will Change IDE Device Mode LEGACY/NATIVE
//
// Input:
//  PCI_DEV_INFO    *Dev      Pointer to PCI Device Private Data structure.
//  BOOLEAN         Primary   Indicate Primary/Secondary controller 
//  BOOLEAN         Legacy    Indicate Mode to programm
//  UINT8           *Override If not NULL value to programm in PI register 
//
// Output:	EFI_STATUS
//  EFI_SUCCESS             When everything is going on fine!
//  EFI_UNSUPPORTED         When device does not support mode programming.
//  EFI_INVALID_PARAMETER   When some of the parameters are invalid.
//
// Referals: PCI_DEV_INFO; 
//
// Notes:
//	This function does not check if SecIde/PriIde Property of the Dev->HostData
//  is tacken already caller must do that before call;
//  This function does not update SecIde/PriIde Property of the Dev->HostData
//  object. Caller must do that upon successfull return.
//	
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS SetIdeDevMode(PCI_DEV_INFO *Dev, BOOLEAN Primary, BOOLEAN Legacy, UINT8 *Override){

	PCI_CFG_ADDR	addr;
	EFI_STATUS		Status=EFI_SUCCESS;
	UINT8			newpi=0, oldpi=Dev->Class.ProgInterface, tmp=oldpi=Dev->Class.ProgInterface; 
	BOOLEAN 		canprog=FALSE, needprog=FALSE;
//--------        
	if(Dev->Class.BaseClassCode!=PCI_CL_MASS_STOR && Dev->Class.SubClassCode!=PCI_CL_MASS_STOR_SCL_IDE)	
		return EFI_INVALID_PARAMETER;
	
	addr.ADDR=Dev->Address.ADDR;
	addr.Addr.Register=PCI_PI_OFFSET;


	if(Override!=NULL){
		Status=PciCfg8(Dev->RbIo,addr,TRUE,Override);
		if(!EFI_ERROR(Status)) {
			UINT8	b=0;
		//----------------
			//read back what we have write there
			Status=PciCfg8(Dev->RbIo,addr,FALSE,&b);
			if(b==(*Override))Dev->Class.ProgInterface=(*Override);
			else Status=EFI_UNSUPPORTED;
			PCI_TRACE((TRACE_PCI, "\nPciBus: SetIdeMode(Pri=N/A, Legacy=N/A, PciPI=0x%X) @ B%X|D%X|F%X = %r,\n",*Override,
			Dev->Address.Addr.Bus,Dev->Address.Addr.Device,Dev->Address.Addr.Function, Status));
		}
	} else {
		if(Primary){
			canprog=(Dev->Class.ProgInterface & 0x02);
			oldpi&=(~0x01);
			tmp&=0x01;
			if(!Legacy) newpi|=0x01;
		} else {
			canprog=(Dev->Class.ProgInterface & 0x08);
			oldpi&=(~0x04);
			tmp&=0x04;
			if(!Legacy) newpi|=0x04;
		}
		needprog = (tmp ^ newpi); 
		if(needprog){
			if(canprog){	
				newpi|=oldpi;			
				Status=PciCfg8(Dev->RbIo,addr,TRUE,&newpi);
				if(!EFI_ERROR(Status)) Dev->Class.ProgInterface=newpi;	
			} else Status=EFI_UNSUPPORTED;
		} 
		PCI_TRACE((TRACE_PCI, "\nPciBus: SetIdeMode(Pri=%d, Legacy=%d, PciPI=0x%X)  @ B%X|D%X|F%X = %r,\n", Primary, Legacy, 
		newpi,Dev->Address.Addr.Bus,Dev->Address.Addr.Device,Dev->Address.Addr.Function, Status));
	}
	
	return Status;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	InCurVgaChain()
//
// Description: Helper function to check if device referenced as "Dev" sits
// within Current VGA device parents bridges.
//
// Input:
//  PCI_DEV_INFO    *Dev        Pointer to PciDevice Info structure.
//
// Output:  BOOLEAN
//  TRUE    "Dev" in Current VGA device parents bridges.
//	FALSE   "Dev" is not in Current VGA device parents bridges.
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
BOOLEAN InCurVgaChain(PCI_DEV_INFO *Dev)
{
	PCI_DEV_INFO *d=Dev->HostData->VgaDev;
//------------------------------------
	if(!d) return FALSE;
	while (d->Type!=tPciRootBrg){
		if(d==Dev) return TRUE;
		d=d->ParentBrg;
	}
	return FALSE;
}


//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	DeviceAttributes()
//
// Description: Protocol Function Sets or resets PCI Device Arttributs.
//
// Input:
//  PCI_DEV_INFO    *Dev        Pointer to PciDevice Info structure.
//  UINT64          Attributes  Attributes bitmask which caller whants to change.
//  BOOLEAN         Set         Specifies weathere to set or reset given "Attributes".
//
// Output:  EFI_STATUS
//  EFI_SUCCESS             When everything is going on fine!
//  EFI_UNSUPPORTED         When some of the "Attributes" not supported by the "Dev".
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS DeviceAttributes(PCI_DEV_INFO *Dev, UINT64 Attributes, BOOLEAN Set)
{
	EFI_STATUS		Status=0;
	UINT16			tmp=0;
    PCI_CMD_REG     cmd;
    PCI_BRG_CNT_REG bc;
	PCI_CFG_ADDR	addr;
	UINT64			newattr=0, capab=Dev->Capab; //| PCI_ALLOWED_ATTRIBUTES;
//------------------------------

	addr.ADDR=Dev->Address.ADDR;
    bc.BRG_CNT_REG=0;
    cmd.CMD_REG=0;

    //Remove platform specific attributes...
    //Attributes&=(~(PCI_ALLOWED_ATTRIBUTES));

	//If Devices for special attributes has been selected already we can't set it for different device
	if(Dev->HostData->VgaDev != NULL){
        if(Dev != Dev->HostData->VgaDev){
    		if(!InCurVgaChain(Dev) ) capab&=(~PCI_VGA_ATTRIBUTES);
        }
    }

	if((Dev->HostData->PriIde!=NULL)&& (Dev!=Dev->HostData->PriIde))
		capab&=(~EFI_PCI_IO_ATTRIBUTE_IDE_PRIMARY_IO);
	if((Dev->HostData->SecIde!=NULL)&& (Dev!=Dev->HostData->SecIde))
		capab&=(~EFI_PCI_IO_ATTRIBUTE_IDE_SECONDARY_IO);

    //If OEMs want to add some more filters...
    Status=PciPortOemAttributes(Dev, &Attributes, capab, Set);

	//if Attributes requested NOT SUPPORTED by the device...
	if((capab & Attributes)!=Attributes) {
		Status=EFI_UNSUPPORTED;
		goto Exit;
	}
 
	//if requested Attributes already match Device current Attributes
	if( (((Dev->Attrib & Attributes)==Attributes) && Set ) || (((Dev->Attrib & Attributes)==0) && (!Set)) )
	{
		Status=EFI_SUCCESS;
		goto Exit;
	}

	//So far so good - apply attributes
	
	//For IDE controller it is a special case
	if( Attributes & (EFI_PCI_IO_ATTRIBUTE_IDE_PRIMARY_IO | EFI_PCI_IO_ATTRIBUTE_IDE_SECONDARY_IO)){
		BOOLEAN Primary=(BOOLEAN)(Attributes & EFI_PCI_IO_ATTRIBUTE_IDE_PRIMARY_IO);
	//--------------
		Status=SetIdeDevMode(Dev, Primary, Set, NULL);
		if(EFI_ERROR(Status))goto Exit;

		if(Set){
			if(Primary) Dev->HostData->PriIde=Dev;
			else  Dev->HostData->SecIde=Dev;
		} else {
			if(Primary) Dev->HostData->PriIde=Dev;
			else  Dev->HostData->SecIde=Dev;
		}
	}

	//the 
        if(Attributes & EFI_PCI_IO_ATTRIBUTE_ISA_MOTHERBOARD_IO ||
            Attributes & EFI_PCI_IO_ATTRIBUTE_ISA_IO) bc.IsaEnable=1;

        if(Attributes & EFI_PCI_IO_ATTRIBUTE_VGA_MEMORY ||
            Attributes & EFI_PCI_IO_ATTRIBUTE_VGA_IO){
            	DXE_SERVICES		    *dxe;	
                EFI_PHYSICAL_ADDRESS    addr=0x3C0;
            //-----------------------------
               	Status=LibGetDxeSvcTbl(&dxe);
	            if(EFI_ERROR(Status)) return Status;
            
                
                bc.VgaEnable=1;
                if (gPciSetupData->VgaPallete) cmd.VgaPaletteSnoop=1;
                
                if(Set) Status=dxe->AllocateIoSpace(EfiGcdAllocateAddress,
							EfiGcdIoTypeIo,
                            0,
							0x20,
							&addr,
							gPciBusDriverBinding.ImageHandle, 
                            gPciBusDriverBinding.DriverBindingHandle);
                else Status=dxe->FreeIoSpace(addr,0x20);
                if(EFI_ERROR(Status)){
	                PCI_TRACE((TRACE_PCI, "\nPciBus: Fail to allocate/free IO 0x3C0 ~ 0x3DF; Set=%d; Status=%r,\n", Set, Status));
                    //If it was allocated - fine just keep going.
                    Status=EFI_SUCCESS;
                }
        }

        if(Attributes & EFI_PCI_IO_ATTRIBUTE_IO) cmd.IoSpace=1;

        if(Attributes & EFI_PCI_IO_ATTRIBUTE_MEMORY) cmd.MemSpace=1;

        if(Attributes & EFI_PCI_IO_ATTRIBUTE_BUS_MASTER) cmd.BusMaster=1;
	
	//Recoursevely Set attributes to all parents
	//if Parent bridge is the RootBrg use it native function to set Attributes
    //keep in mind that per UIEFI 2.1 Spec Bridges are suppose to be always open,
    //so we will filter Device Enable attributes from setting/resetting them for bridges.
	newattr=(Attributes & (~(EFI_PCI_IO_ATTRIBUTE_IO|EFI_PCI_IO_ATTRIBUTE_MEMORY|EFI_PCI_IO_ATTRIBUTE_BUS_MASTER|PCI_ALLOWED_ATTRIBUTES)));
	if(Dev->ParentBrg->Type == tPciRootBrg )Status=Dev->RbIo->SetAttributes(Dev->RbIo,newattr,NULL,NULL);
	else Status=DeviceAttributes(Dev->ParentBrg,newattr,Set);
	if(EFI_ERROR(Status))goto Exit;

	//bridge control register for P2P and P2C at the same place
	if((Dev->Type==tPci2PciBrg || Dev->Type==tPci2CrdBrg) && bc.BRG_CNT_REG){
		//update bridge control reg if we have to
		addr.Addr.Register=PCI_BRIDGE_CNTL; //brg controll reg
		
		//read what it has
		Status=PciCfg16(Dev->RbIo,addr,FALSE,&tmp);
		if(EFI_ERROR(Status)) goto Exit;

		if(Set) bc.BRG_CNT_REG=bc.BRG_CNT_REG|tmp;
		else bc.BRG_CNT_REG=tmp&(~bc.BRG_CNT_REG);

		//write updated value
		Status=PciCfg16(Dev->RbIo,addr,TRUE,&bc.BRG_CNT_REG);
		if(EFI_ERROR(Status)) goto Exit;
	}

	if(cmd.CMD_REG){
		//update PCI command reg if we have to
		addr.Addr.Register=PCI_CMD; //command reg
		
		//read what it has
		Status=PciCfg16(Dev->RbIo,addr,FALSE,&tmp);
		if(EFI_ERROR(Status)) goto Exit;

		if(Set) cmd.CMD_REG=cmd.CMD_REG|tmp;
		else cmd.CMD_REG=tmp&(~cmd.CMD_REG);

		//write updated value
		Status=PciCfg16(Dev->RbIo,addr,TRUE,&cmd.CMD_REG);
		if(EFI_ERROR(Status)) goto Exit;
	}
	//Update Recorded Attributes
	if(Set)Dev->Attrib|=Attributes;	
	else Dev->Attrib&=(~Attributes);

Exit:
	PCI_TRACE((TRACE_PCI, "\nPciBus: SetAttributes(%d) @ B%X|D%X|F%X Attr=0x%lX; Capab=0x%lX; Status=%r,\n", Set,
	Dev->Address.Addr.Bus,Dev->Address.Addr.Device,Dev->Address.Addr.Function, Attributes, capab, Status));

	return Status;
}


//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	PciIoPollMem()
//
// Description: Protocol Function Poll PCI Memmory
//
// Notes: See EFI Specification for detail description
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS PciIoPollMem(IN  EFI_PCI_IO_PROTOCOL        *This,
						IN  EFI_PCI_IO_PROTOCOL_WIDTH  Width,
						IN  UINT8                      BarIndex,
						IN  UINT64                     Offset,
						IN  UINT64                     Mask,
						IN  UINT64                     Value,
						IN  UINT64                     Delay,
						OUT UINT64                     *Result)
{
	EFI_STATUS    Status;
	PCI_DEV_INFO	*dev=(PCI_DEV_INFO*)This;
//----------------------------------------------------------------------

	if (((UINT32)Width) > ((UINT32)EfiPciIoWidthUint64)) return EFI_INVALID_PARAMETER;

	Status = PciIoCheckBar(dev, BarIndex, tBarMem, Width, 1, &Offset);
	if(EFI_ERROR(Status)) return EFI_UNSUPPORTED;

	Status=dev->RbIo->PollMem(dev->RbIo,(EFI_PCI_ROOT_BRIDGE_IO_PROTOCOL_WIDTH)Width,Offset,
		Mask,Value,Delay,Result);
	return Status;
}


//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	PciIoPollIo()
//
// Description: Protocol Function Poll PCI IO
//
// Notes: See EFI Specification for detail description
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS PciIoPollIo (IN  EFI_PCI_IO_PROTOCOL        *This,
						IN  EFI_PCI_IO_PROTOCOL_WIDTH  Width,
						IN  UINT8                      BarIndex,
						IN  UINT64                     Offset,
						IN  UINT64                     Mask,
						IN  UINT64                     Value,
						IN  UINT64                     Delay,
						OUT UINT64                     *Result )
{
	EFI_STATUS		Status;
	PCI_DEV_INFO	*dev=(PCI_DEV_INFO*)This;
//----------------------------------
	if (((UINT32)Width) > ((UINT32)EfiPciIoWidthUint64)) return EFI_INVALID_PARAMETER;
 
	Status=PciIoCheckBar(dev, BarIndex, tBarIo, Width, 1, &Offset);
	if(EFI_ERROR(Status)) return EFI_UNSUPPORTED;

	if (Width > EfiPciIoWidthUint64) return EFI_INVALID_PARAMETER;

	Status=dev->RbIo->PollIo(dev->RbIo,(EFI_PCI_ROOT_BRIDGE_IO_PROTOCOL_WIDTH)Width,
                             Offset, Mask, Value, Delay, Result);
	return Status;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	PciIoMemRead()
//
// Description: Protocol Function Performs a PCI Memory Read Cycle
//
// Notes: See EFI Specification for detail description
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS PciIoMemRead(IN EFI_PCI_IO_PROTOCOL        *This,
						IN EFI_PCI_IO_PROTOCOL_WIDTH  Width,
						IN UINT8                      BarIndex,
						IN UINT64                     Offset,
						IN UINTN                      Count,
						IN OUT VOID                   *Buffer)
{
	EFI_STATUS     Status;
	PCI_DEV_INFO	*dev=(PCI_DEV_INFO*)This;
//---------------------------------------------

	if (Width < 0 || Width >= EfiPciIoWidthMaximum) return EFI_INVALID_PARAMETER;

	Status=PciIoCheckBar(dev, BarIndex, tBarMem, Width, Count, &Offset);
	if(EFI_ERROR(Status)) return EFI_UNSUPPORTED;

	Status=dev->RbIo->Mem.Read(dev->RbIo,(EFI_PCI_ROOT_BRIDGE_IO_PROTOCOL_WIDTH)Width,
							   Offset, Count, Buffer);
	
	return Status;
}


//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	PciIoMemWrite()
//
// Description: Protocol Function Performs a PCI Memory Write Cycle
//
// Notes: See EFI Specification for detail description
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS PciIoMemWrite(IN EFI_PCI_IO_PROTOCOL        *This,
						 IN EFI_PCI_IO_PROTOCOL_WIDTH  Width,
						 IN UINT8                      BarIndex,
						 IN UINT64                     Offset,
						 IN UINTN                      Count,
						 IN OUT VOID                   *Buffer)
{
	EFI_STATUS     Status;
	PCI_DEV_INFO	*dev=(PCI_DEV_INFO*)This;
//-------------------------------------------
  
	if(Width<0 || Width>=EfiPciIoWidthMaximum) return EFI_INVALID_PARAMETER;

	Status = PciIoCheckBar(dev, BarIndex, tBarMem, Width, Count, &Offset);
	if (EFI_ERROR(Status)) return EFI_UNSUPPORTED;
  
	Status=dev->RbIo->Mem.Write(dev->RbIo,(EFI_PCI_ROOT_BRIDGE_IO_PROTOCOL_WIDTH)Width,
                                Offset, Count, Buffer);

	return Status;
}


//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	PciIoIoRead()
//
// Description: Protocol Function Performs a PCI I/O Read Cycle
//
// Notes: See EFI Specification for detail description
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS PciIoIoRead(IN EFI_PCI_IO_PROTOCOL        *This,
					   IN EFI_PCI_IO_PROTOCOL_WIDTH  Width,
					   IN UINT8                      BarIndex,
					   IN UINT64                     Offset,
					   IN UINTN                      Count,
					   IN OUT VOID                   *Buffer)
{
	EFI_STATUS     Status;
	PCI_DEV_INFO	*dev=(PCI_DEV_INFO*)This;
//----------------------------------------------------

	if (Width < 0 || Width >= EfiPciIoWidthMaximum) return EFI_INVALID_PARAMETER;

	Status=PciIoCheckBar(dev, BarIndex, tBarIo, Width, Count, &Offset);
	if (EFI_ERROR(Status))return EFI_UNSUPPORTED;
  
	Status=dev->RbIo->Io.Read(dev->RbIo,(EFI_PCI_ROOT_BRIDGE_IO_PROTOCOL_WIDTH)Width,
                              Offset, Count, Buffer);
	
	return Status;
}


//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	PciIoIoWrite()
//
// Description: Protocol Function Performs a PCI I/O Write Cycle
//
// Notes: See EFI Specification for detail description
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS PciIoIoWrite(IN EFI_PCI_IO_PROTOCOL        *This,
						IN EFI_PCI_IO_PROTOCOL_WIDTH  Width,
						IN UINT8                      BarIndex,
						IN UINT64                     Offset,
						IN UINTN                      Count,
						IN OUT VOID                   *Buffer)
{
	EFI_STATUS     Status;
	PCI_DEV_INFO	*dev=(PCI_DEV_INFO*)This;
//----------------------------------------------------

	if (Width < 0 || Width >= EfiPciIoWidthMaximum) return EFI_INVALID_PARAMETER;
  
	Status=PciIoCheckBar(dev, BarIndex, tBarIo, Width, Count, &Offset);
	if (EFI_ERROR(Status)) return EFI_UNSUPPORTED;

	Status=dev->RbIo->Io.Write(dev->RbIo,(EFI_PCI_ROOT_BRIDGE_IO_PROTOCOL_WIDTH)Width,
                               Offset, Count, Buffer);

	return Status;
}


//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	PciIoConfigRead()
//
// Description: Protocol Function Performs a PCI Configuration Read Cycle
//
// Notes: See EFI Specification for detail description
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS PciIoConfigRead(IN EFI_PCI_IO_PROTOCOL        *This,
						   IN EFI_PCI_IO_PROTOCOL_WIDTH  Width,
						   IN UINT32                     Offset,
						   IN UINTN                      Count,
						   IN OUT VOID                   *Buffer)
{
  
	EFI_STATUS     Status;
	PCI_DEV_INFO	*dev=(PCI_DEV_INFO*)This;
	UINT64         Address;
//---------------------------------------------------
	Address = Offset;
	Status = PciIoCheckConfig(dev, Width, Count, &Address);
	if(EFI_ERROR(Status))return Status;

	Status=dev->RbIo->Pci.Read(dev->RbIo,(EFI_PCI_ROOT_BRIDGE_IO_PROTOCOL_WIDTH)Width,
							   Address, Count, Buffer);
	return Status;
}


//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	PciIoConfigWrite()
//
// Description: Protocol Function Performs a PCI Configuration Write Cycle
//
// Notes: See EFI Specification for detail description
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS PciIoConfigWrite(IN EFI_PCI_IO_PROTOCOL        *This,
							IN EFI_PCI_IO_PROTOCOL_WIDTH  Width,
							IN UINT32                     Offset,
							IN UINTN                      Count,
							IN OUT VOID                   *Buffer)
{
	EFI_STATUS     Status;
	PCI_DEV_INFO	*dev=(PCI_DEV_INFO*)This;
	UINT64         Address;
//---------------------------------------------------
	Address = Offset;
	Status = PciIoCheckConfig(dev, Width, Count, &Address);
	if (EFI_ERROR(Status)) return Status;
	
	Status=dev->RbIo->Pci.Write(dev->RbIo,(EFI_PCI_ROOT_BRIDGE_IO_PROTOCOL_WIDTH)Width,
							   Address, Count, Buffer);
	return Status;
}


//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	PciIoCopyMem()
//
// Description: Protocol Function Copyes PCI Memory
//
// Notes: See EFI Specification for detail description
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS PciIoCopyMem(IN EFI_PCI_IO_PROTOCOL			*This,
						IN EFI_PCI_IO_PROTOCOL_WIDTH    Width,
						IN UINT8                        DestBarIndex,
						IN UINT64                       DestOffset,
						IN UINT8                        SrcBarIndex,
						IN UINT64                       SrcOffset,
						IN UINTN                        Count)
{
	EFI_STATUS     Status;
	PCI_DEV_INFO	*dev=(PCI_DEV_INFO*)This;
//---------------------------------------------------

	if (Width < 0 || Width >= EfiPciIoWidthMaximum) return EFI_INVALID_PARAMETER;

	if(Width == EfiPciIoWidthFifoUint8     ||
	   Width == EfiPciIoWidthFifoUint16    ||
	   Width == EfiPciIoWidthFifoUint32    ||
	   Width == EfiPciIoWidthFifoUint64    ||
       Width == EfiPciIoWidthFillUint8     ||
       Width == EfiPciIoWidthFillUint16    ||
       Width == EfiPciIoWidthFillUint32    ||
       Width == EfiPciIoWidthFillUint64) return EFI_INVALID_PARAMETER;

	Status=PciIoCheckBar(dev, DestBarIndex, tBarMem, Width, Count, &DestOffset);
	if (EFI_ERROR(Status)) return EFI_UNSUPPORTED;
  
	Status=PciIoCheckBar(dev, SrcBarIndex, tBarMem, Width, Count, &SrcOffset);
	if (EFI_ERROR(Status)) return EFI_UNSUPPORTED;
  
	Status=dev->RbIo->CopyMem(dev->RbIo,(EFI_PCI_ROOT_BRIDGE_IO_PROTOCOL_WIDTH)Width,
                            DestOffset, SrcOffset, Count);
                                           
	return Status;
}


//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	PciIoMap()
//
// Description: Protocol Function Maps a memory region for DMA
//
// Notes: See EFI Specification for detail description
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS PciIoMap(IN EFI_PCI_IO_PROTOCOL            *This,
					IN EFI_PCI_IO_PROTOCOL_OPERATION  Operation,
					IN VOID                           *HostAddress,
					IN OUT UINTN                      *NumberOfBytes,
					OUT EFI_PHYSICAL_ADDRESS          *DeviceAddress,
					OUT VOID                          **Mapping)
{
	EFI_STATUS     Status;
	PCI_DEV_INFO	*dev=(PCI_DEV_INFO*)This;
//---------------------------------------------------

	if(Operation<0 || Operation>=EfiPciIoOperationMaximum) return EFI_INVALID_PARAMETER;

    if(HostAddress==NULL || NumberOfBytes==NULL || DeviceAddress==NULL || Mapping==NULL)
		return EFI_INVALID_PARAMETER;

	if (dev->Attrib & EFI_PCI_IO_ATTRIBUTE_DUAL_ADDRESS_CYCLE) 
		Operation = Operation + EfiPciOperationBusMasterRead64;
  
	Status=dev->RbIo->Map(dev->RbIo,(EFI_PCI_ROOT_BRIDGE_IO_PROTOCOL_OPERATION)Operation,
                          HostAddress, NumberOfBytes, DeviceAddress, Mapping);

    return Status;
}


//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	PciIoUnmap()
//
// Description: Protocol Function Unmaps a memory region for DMA
//
// Notes: See EFI Specification for detail description
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS PciIoUnmap(IN EFI_PCI_IO_PROTOCOL  *This,
					  IN VOID                 *Mapping)
{
	EFI_STATUS     Status;
	PCI_DEV_INFO	*dev=(PCI_DEV_INFO*)This;
//---------------------------------------------------

	Status=dev->RbIo->Unmap(dev->RbIo,Mapping);
                                        
	return Status;
}


//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   PciIoAllocateBuffer()
//
// Description: Protocol Function Allocates a common buffer for DMA
//
// Notes: See EFI Specification for detail description
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS PciIoAllocateBuffer(IN  EFI_PCI_IO_PROTOCOL   *This,
							   IN  EFI_ALLOCATE_TYPE     Type,
							   IN  EFI_MEMORY_TYPE       MemoryType,
							   IN  UINTN                 Pages,
							   OUT VOID                  **HostAddress,
							   IN  UINT64                Attributes)
{
	EFI_STATUS     Status;
	PCI_DEV_INFO	*dev=(PCI_DEV_INFO*)This;
//---------------------------------------------------
  
	if (Attributes & (~(EFI_PCI_ATTRIBUTE_MEMORY_WRITE_COMBINE | EFI_PCI_ATTRIBUTE_MEMORY_CACHED))) 
		return EFI_UNSUPPORTED;
  
	if (dev->Attrib & EFI_PCI_IO_ATTRIBUTE_DUAL_ADDRESS_CYCLE) 
		Attributes|=EFI_PCI_ATTRIBUTE_DUAL_ADDRESS_CYCLE;
  
	Status=dev->RbIo->AllocateBuffer(dev->RbIo,Type,MemoryType,Pages,HostAddress,Attributes);

	return Status;
}


//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	PciIoFreeBuffer()
//
// Description: Protocol Function Frees a common buffer 
//
// Notes: See EFI Specification for detail description
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS PciIoFreeBuffer(IN  EFI_PCI_IO_PROTOCOL   *This,
						   IN  UINTN                 Pages,
						   IN  VOID                  *HostAddress)
{
	EFI_STATUS     Status;
	PCI_DEV_INFO	*dev=(PCI_DEV_INFO*)This;
//---------------------------------------------------
	
	Status=dev->RbIo->FreeBuffer(dev->RbIo,Pages,HostAddress);
	return Status;
}


//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	PciIoFlush()
//
// Description: Protocol Function Flushes a DMA buffer 
//
// Notes: See EFI Specification for detail description
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS PciIoFlush (IN  EFI_PCI_IO_PROTOCOL  *This)
{
	PCI_DEV_INFO	*dev=(PCI_DEV_INFO*)This;
//--------------------------------------------
	return dev->RbIo->Flush(dev->RbIo);
}


//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	PciIoGetLocation()
//
// Description: Protocol Function Proides Device Address on PCI BUS like
// Bus#, Dev#, Fun# for the device who has PciIoProtocol == "This".
//
// Notes: See EFI Specification for detail description
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS PciIoGetLocation(IN  EFI_PCI_IO_PROTOCOL  *This,
							OUT UINTN                *Segment,
							OUT UINTN                *Bus,
							OUT UINTN                *Device,
							OUT UINTN                *Function)
{
	PCI_DEV_INFO	*dev=(PCI_DEV_INFO*)This;
//--------------------------------------------

	if(Segment==NULL || Bus==NULL || Device==NULL || Function==NULL)
		return EFI_INVALID_PARAMETER;
  
	*Segment  = dev->RbIo->SegmentNumber;
	*Bus      = dev->Address.Addr.Bus;
	*Device   = dev->Address.Addr.Device;
	*Function = dev->Address.Addr.Function;

	return EFI_SUCCESS;
}


//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   PciIoAttributes()
//
// Description: Protocol Function Provides Arttribute operation for the PCI device
//
// Notes: See EFI Specification for detail description
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS PciIoAttributes(IN EFI_PCI_IO_PROTOCOL						*This,
						   IN  EFI_PCI_IO_PROTOCOL_ATTRIBUTE_OPERATION  Operation,
						   IN  UINT64                                   Attributes,
						   OUT UINT64                                   *Result   OPTIONAL )
{
	EFI_STATUS     Status;
	PCI_DEV_INFO	*dev=(PCI_DEV_INFO*)This;
	BOOLEAN 		f=FALSE;	
	UINT64			capab=dev->Capab;
//--------------------------------------------

	switch (Operation) {
		case EfiPciIoAttributeOperationGet:
		case EfiPciIoAttributeOperationSupported:
			if (Result == NULL) return EFI_INVALID_PARAMETER;
			if(Operation==EfiPciIoAttributeOperationGet)*Result = dev->Attrib;
			else {

            	if(dev->HostData->VgaDev != NULL){
                    if(dev != dev->HostData->VgaDev){
    		            if(!InCurVgaChain(dev) ) capab&=(~PCI_VGA_ATTRIBUTES);
                    }
                }
				*Result=capab; 
			}
			return EFI_SUCCESS;
			break;
		case EfiPciIoAttributeOperationSet:
		case EfiPciIoAttributeOperationEnable:
			//only one VGA legacy resources may be decoded
			if(Attributes&PCI_VGA_ATTRIBUTES){ //special case for VGA attr
				if(dev->HostData->VgaDev==NULL)f=TRUE;
            }
				//else if (dev!=dev->HostData->VgaDev) return EFI_UNSUPPORTED;
			Status=DeviceAttributes(dev, Attributes,TRUE);
			if((!EFI_ERROR(Status))&& f) dev->HostData->VgaDev=dev; 
			break;
		case EfiPciIoAttributeOperationDisable:      
			if(Attributes&PCI_VGA_ATTRIBUTES) {//special case for VGA attr
                if(dev->HostData->VgaDev==dev)f=TRUE;       
            }
			Status=DeviceAttributes(dev, Attributes,FALSE);
			if((!EFI_ERROR(Status))&& f ) dev->HostData->VgaDev=NULL; //clear default VGA Device ptr somebody reset it's status 
			break;
		default : return EFI_INVALID_PARAMETER;
	}//switch
  return Status;
}


//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	PciIoGetBarAttributes()
//
// Description: Protocol Function Gets respective BAR Attributes
//
// Notes: See EFI Specification for detail description
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS PciIoGetBarAttributes(IN EFI_PCI_IO_PROTOCOL		*This,
								 IN UINT8                   BarIndex,
								 OUT UINT64                 *Supports,   OPTIONAL
								 OUT VOID                   **Resources  OPTIONAL )
{
	PCI_DEV_INFO	*dev=(PCI_DEV_INFO*)This;
	ASLR_QWORD_ASD	*resdsc;
	ASLR_EndTag		*enddsc;
//--------------------------------------------
 
	if(Supports==NULL && Resources == NULL) return EFI_INVALID_PARAMETER;
 	if(BarIndex>=MAX_PCI_BAR) return EFI_UNSUPPORTED;
  
	if(Supports!=NULL) {
//TODO//TODO//TODO//TODO//TODO//TODO//TODO//TODO//TODO
//implement changing attributes for BAR using Cpu Protocol 
		*Supports = (dev->Capab & (BAR_ATTR));
//TODO//TODO//TODO//TODO//TODO//TODO//TODO//TODO//TODO
	}
	if(Resources != NULL) {
		UINTN		sz=sizeof(ASLR_EndTag);
	//------------------------------------------------	
		if(dev->Bar[BarIndex].Type!=tBarUnused)sz+=sizeof(ASLR_QWORD_ASD);

		resdsc=MallocZ(sz);
		if(!resdsc) return EFI_OUT_OF_RESOURCES;


		if(dev->Bar[BarIndex].Type!=tBarUnused){

			enddsc=(ASLR_EndTag*)(resdsc+1);
	
			//fill BAR descriptor
			resdsc->Hdr.Name=ASLV_RT_QWORD_ASD;
			resdsc->Hdr.Type=ASLV_LARGE_RES;
			resdsc->Hdr.Length=sizeof(ASLR_QWORD_ASD)-sizeof(ASLRF_L_HDR);
			resdsc->_MIN=dev->Bar[BarIndex].Base;
			resdsc->_LEN=dev->Bar[BarIndex].Length;
			resdsc->_MAX=resdsc->_MIN+resdsc->_LEN-1;

			switch (dev->Bar[BarIndex].DiscoveredType) {
				case tBarIo16:
				case tBarIo32:       
					resdsc->Type=ASLRV_SPC_TYPE_IO;			// Io             
					break;
				case tBarMmio32:
					resdsc->Type=ASLRV_SPC_TYPE_MEM;		// Mem
					resdsc->_GRA=32;						// 32 bit
					break;
				case tBarMmio32pf:
	   				resdsc->Type=ASLRV_SPC_TYPE_MEM;		// Mem             
					resdsc->TFlags.TFLAGS=0x6;				// prefechable
					resdsc->_GRA=32;						// 32 bit
					break;
				case tBarMmio64:
					resdsc->Type=ASLRV_SPC_TYPE_MEM;		// Mem             
	   		        resdsc->_GRA=64;						// 32 bit
		    	    break;
				case tBarMmio64pf:
					resdsc->Type=ASLRV_SPC_TYPE_MEM;		// Mem             
					resdsc->TFlags.TFLAGS=0x6;				// prefechable
					resdsc->_GRA=64;						// 32 bit
					break;
			}//switch
		} else enddsc=(ASLR_EndTag*)(resdsc);
		//fix End tag
		enddsc->Hdr.Name=ASLV_SR_EndTag;
		enddsc->Hdr.Type=ASLV_SMALL_RES;
		enddsc->Hdr.Length=sizeof(ASLR_EndTag)-sizeof(ASLRF_S_HDR);
		enddsc->Chsum=0;
		*Resources = resdsc;
	}//if(Resources!=NULL) 

	return EFI_SUCCESS;
}


//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	PciIoSetBarAttributes()
//
// Description: Protocol Function Sets respective BAR Attributes
//
// Notes: See EFI Specification for detail description
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS PciIoSetBarAttributes(IN EFI_PCI_IO_PROTOCOL		*This,
								 IN UINT64                  Attributes,
								 IN UINT8                   BarIndex,
								 IN OUT UINT64              *Offset,
								 IN OUT UINT64              *Length)
{
	EFI_STATUS			Status;
	PCI_DEV_INFO		*dev=(PCI_DEV_INFO*)This;
	UINT64				offs, attr;
//--------------------------------------------------

	if(Offset==NULL || Length==NULL) return EFI_INVALID_PARAMETER;
  
	if(dev->Bar[BarIndex].Type==tBarUnused) return EFI_UNSUPPORTED;
 
	// This driver does not support setting the WRITE_COMBINE or the CACHED attributes.
	// If Attributes is not 0, then return EFI_UNSUPPORTED.
	attr = Attributes & (~BAR_ATTR);
//TODO//TODO//TODO//TODO//TODO//TODO//TODO//TODO//TODO
//implement changing attributes for bar trough Cpu Protocol  
	if (attr)return EFI_UNSUPPORTED;
//TODO//TODO//TODO//TODO//TODO//TODO//TODO//TODO//TODO
 
	//Make sure the BAR range describd by BarIndex, Offset, and Length are valid for this PCI device.
	offs = *Offset; 
	Status=PciIoCheckBar(dev, BarIndex, tBarMem, EfiPciIoWidthUint8, (UINT32)*Length, &offs);

	if (EFI_ERROR(Status)) return EFI_UNSUPPORTED;

	return Status;
}


//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
//============================================================================
// Pci Io Protocol Interface
//============================================================================
//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

//<AMI_SHDR_START>
//----------------------------------------------------------------------------
// Name:		gPciIoInstance
//
// Description:	PCI IO Protocol Instance for Child Devices of the PciBus Driver.
//
// Notes: EFI_PCI_IO_PROTOCOL
//
//----------------------------------------------------------------------------
//<AMI_SHDR_END>
static EFI_PCI_IO_PROTOCOL gPciIoInstance = {
    PciIoPollMem,
    PciIoPollIo, 
    {
        PciIoMemRead,  
        PciIoMemWrite
    },
    {
        PciIoIoRead,   
        PciIoIoWrite
    },
    {
        PciIoConfigRead, 
        PciIoConfigWrite
    },
    PciIoCopyMem,
    PciIoMap,
    PciIoUnmap,
    PciIoAllocateBuffer,
    PciIoFreeBuffer,
    PciIoFlush,
    PciIoGetLocation,
    PciIoAttributes,
    PciIoGetBarAttributes,
    PciIoSetBarAttributes,
    0,                      //RomSize;
    NULL                    //RomImage
};


//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
//======================================================================
// Here follows worker functions used for 
// PCI Bus Enumeration and Resource Allocation
//======================================================================
//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   EnableDeviceDecoding()
//
// Description: Enables PCI Device Decoding.
//
// Input:
//  PCI_DEV_INFO    *Dev        Pointer to PCI Device Private Data structure.
//  PCI_SPACE_TYPE  WhatSpace   Type of PCI Device Space for Action.
//
// Output:	EFI_STATUS
//  EFI_SUCCESS             When everything is going on fine!
//  EFI_DEVICE_ERROR        When driver fails access PCI Bus.
//  EFI_INVALID_PARAMETER   When some of the parameters are invalid.
//
// Referals: PCI_DEV_INFO; PCI_SPACE_TYPE.
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS EnableDeviceDecoding(PCI_DEV_INFO *Dev, PCI_SPACE_TYPE WhatSpace)
{
	EFI_STATUS		Status;
	UINT16			b16;
	PCI_CFG_ADDR	addr;
//------------------
	
	if(Dev->Type<tPci2PciBrg) return EFI_SUCCESS;
#if EFI_DEBUG || USB_DEBUG_TRANSPORT
	if(Dev->DebugPort) return EFI_SUCCESS;
#endif

	addr.ADDR=Dev->Address.ADDR;
	//first read Command reg contents
	addr.Addr.Register=PCI_COMMAND_REGISTER_OFFSET;
	Status=PciCfg16(Dev->RbIo,addr,FALSE,&b16);
	if(EFI_ERROR(Status)) return Status;

	switch (WhatSpace){
		case stOptRomSpace:
		case stMemSpace: b16|=(PCI_CMD_MEMORY_SPACE); break;
		case stIoSpace:  b16|=(PCI_CMD_IO_SPACE); break;
		case stMemIoSpace: b16|=(PCI_CMD_IO_SPACE | PCI_CMD_MEMORY_SPACE); break;
		default: return EFI_INVALID_PARAMETER;
	} //switch
	//if Enabling PCI ROM space
	if(WhatSpace==stOptRomSpace && Dev->Bar[PCI_MAX_BAR_NO].Type!=tBarUnused){
		UINT32		b32;
	//----------------------	
		addr.Addr.Register=Dev->Bar[PCI_MAX_BAR_NO].Offset;

		Status=PciCfg32(Dev->RbIo,addr,FALSE,&b32);
		if(EFI_ERROR(Status)) return Status;

		b32|=1;
		Status=PciCfg32(Dev->RbIo,addr,TRUE,&b32);
		if(EFI_ERROR(Status)) return Status;
	}

	//Write Data to the Command Register
	addr.Addr.Register=PCI_COMMAND_REGISTER_OFFSET;
	return PciCfg16(Dev->RbIo,addr,TRUE,&b16);
}


//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   DisableDeviceDecoding()
//
// Description: Disables PCI Device Decoding.
//
// Input:
//  PCI_DEV_INFO    *Dev        Pointer to PCI Device Private Data structure.
//  PCI_SPACE_TYPE  WhatSpace   Type of PCI Device Space for Action.
//
// Output:	EFI_STATUS
//  EFI_SUCCESS             When everything is going on fine!
//  EFI_DEVICE_ERROR        When driver fails access PCI Bus.
//  EFI_INVALID_PARAMETER   When some of the parameters are invalid.
//
// Referals: PCI_DEV_INFO; PCI_SPACE_TYPE.
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS DisableDeviceDecoding(PCI_DEV_INFO *Dev, PCI_SPACE_TYPE WhatSpace)
{
	EFI_STATUS		Status;
	UINT16			b16;
	PCI_CFG_ADDR	addr;
//------------------
	//Don't toch Host brg device as a PCI Device
	if(Dev->Type==tPciHostDev || Dev->Type==tUncompatibleDevice) return EFI_SUCCESS;
#if EFI_DEBUG || USB_DEBUG_TRANSPORT
	if(Dev->DebugPort) return EFI_SUCCESS;
#endif
 
	addr.ADDR=Dev->Address.ADDR;
	//first read Command reg contents
	addr.Addr.Register=PCI_COMMAND_REGISTER_OFFSET;
	Status=PciCfg16(Dev->RbIo,addr,FALSE,&b16);
	if(EFI_ERROR(Status)) return Status;

	switch (WhatSpace){
		case stOptRomSpace:
		case stMemSpace: 
            b16 &= (~PCI_CMD_MEMORY_SPACE); 
            break;
		case stIoSpace:  
            b16 &= (~PCI_CMD_IO_SPACE); 
            break;
		case stMemIoSpace: 
            b16 &= (~(PCI_CMD_IO_SPACE | PCI_CMD_MEMORY_SPACE)); 
            break;
		case stDisableAll: 
            b16 &= (~(PCI_CMD_IO_SPACE | PCI_CMD_MEMORY_SPACE | PCI_CMD_BUS_MASTER)); 
            break;
		default: return EFI_INVALID_PARAMETER;
	} //switch

	//if Disabling PCI ROM space
	if( (WhatSpace == stOptRomSpace ) && (Dev->Bar[PCI_MAX_BAR_NO].Type!=tBarUnused)){
		UINT32		b32;
	//----------------------	
		addr.Addr.Register=Dev->Bar[PCI_MAX_BAR_NO].Offset;

		Status=PciCfg32(Dev->RbIo,addr,FALSE,&b32);
		if(EFI_ERROR(Status)) return Status;

		b32&=(~1);
		Status=PciCfg32(Dev->RbIo,addr,TRUE,&b32);
		if(EFI_ERROR(Status)) return Status;
	}
	
	//Write Data to the Command Register
	addr.Addr.Register=PCI_COMMAND_REGISTER_OFFSET;
	Status=PciCfg16(Dev->RbIo,addr,TRUE,&b16);
	
	return Status;
}


//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   EnableBridgeIoDecoding()
//
// Description: Enables PCI Bridge I/O Space Decoding.
//
// Input:
//  PCI_DEV_INFO    *Brg        Pointer to PCI Bridge Private Data structure.
//  UINT64          Base        Base Address of the Bridge I/O Window.
//  UINT64          Length      Length of the Bridge I/O Window.
//
// Output:	EFI_STATUS
//  EFI_SUCCESS             When everything is going on fine!
//  EFI_DEVICE_ERROR        When driver fails access PCI Bus.
//  EFI_INVALID_PARAMETER   When some of the parameters are invalid.
//
// Referals: PCI_DEV_INFO.
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS EnableBridgeIoDecoding(PCI_DEV_INFO *Brg, UINT64 Base, UINT64 Length)
{
	PCI_CFG_ADDR	BrgDevAddr;
	UINT64			buff;
	EFI_STATUS		Status;
//----------------------------------------
    PCI_TRACE((TRACE_PCI,"PciBus: Enabling Brg I/O  @ B%X|D%X|F%X\n, B=%lX; L=%lX\n", 
	Brg->Address.Addr.Bus, Brg->Address.Addr.Device,Brg->Address.Addr.Function,
    Base, Length));

	BrgDevAddr.ADDR=Brg->Address.ADDR;
	//Set IObase to 0xFF and IO limit to 0
	BrgDevAddr.Addr.Register=0x1C; 
	buff=Shr64(Base,8);

	Status = PciCfg8(Brg->RbIo, BrgDevAddr,TRUE,(UINT8*)&buff);
	if(EFI_ERROR(Status))return Status;

	buff=Shr64(Base,16); 
	BrgDevAddr.Addr.Register=0x30; //Upper 16 Base Reg 

	Status = PciCfg16(Brg->RbIo, BrgDevAddr,TRUE,(UINT16*)&buff);
	if(EFI_ERROR(Status))return Status;

	//Set IO limit 
	buff=Shr64(Base+(Length-1),8);
	BrgDevAddr.Addr.Register=0x1D; 

	Status = PciCfg8(Brg->RbIo, BrgDevAddr,TRUE,(UINT8*)&buff);
	if(EFI_ERROR(Status))return Status;

	//Set IO limit  Upper 16
	buff=Shr64(Base+(Length-1),16);
	BrgDevAddr.Addr.Register=0x32; 

	return PciCfg16(Brg->RbIo, BrgDevAddr,TRUE,(UINT16*)&buff);
}


//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   DisableBridgeIoDecoding()
//
// Description: Disables PCI Bridge I/O Space Decoding.
//
// Input:
//  PCI_BRG_INFO    *Brg        Pointer to PCI Bridge Private Data structure.
//
// Output:	EFI_STATUS
//  EFI_SUCCESS             When everything is going on fine!
//  EFI_DEVICE_ERROR        When driver fails access PCI Bus.
//  EFI_INVALID_PARAMETER   When some of the parameters are invalid.
//
// Referals: PCI_BRG_INFO.
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS DisableBridgeIoDecoding(PCI_BRG_INFO *Brg)
{
	PCI_CFG_ADDR	BrgDevAddr;
	UINT32			buff=0x00FF;
	EFI_STATUS		Status;
//----------------------------------------
	BrgDevAddr.ADDR=Brg->Common.Address.ADDR;
	//Set IObase to 0xFF and IO limit to 0
	BrgDevAddr.Addr.Register=0x1C; 
	Status = PciCfg16(Brg->Common.RbIo, BrgDevAddr,TRUE,(UINT16*)&buff);
	if(EFI_ERROR(Status))return Status;

	//Set IO limit upper 32 base and limit to 0
	BrgDevAddr.Addr.Register=0x30; 
	return PciCfg32(Brg->Common.RbIo, BrgDevAddr,TRUE,&buff);
}


//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   EnableBridgeMmioDecoding()
//
// Description: Enables PCI Bridge MMIO Space Decoding.
//
// Input:
//  PCI_DEV_INFO    *Brg        Pointer to PCI Bridge Private Data structure.
//  UINT64          Base        Base Address of the Bridge I/O Window.
//  UINT64          Length      Length of the Bridge I/O Window.
//
// Output:	EFI_STATUS
//  EFI_SUCCESS             When everything is going on fine!
//  EFI_DEVICE_ERROR        When driver fails access PCI Bus.
//  EFI_INVALID_PARAMETER   When some of the parameters are invalid.
//
// Referals: PCI_DEV_INFO.
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS EnableBridgeMmioDecoding(PCI_DEV_INFO *Brg, UINT64 Base, UINT64 Length)
{
	PCI_CFG_ADDR	BrgDevAddr;
	UINT64			buff;
	EFI_STATUS		Status;
//----------------------------------------
    PCI_TRACE((TRACE_PCI,"PciBus: Enabling Brg MMIO @ [B%X|D%X|F%X] --> B=%lX; L=%lX\n", 
	Brg->Address.Addr.Bus, Brg->Address.Addr.Device,Brg->Address.Addr.Function,
    Base, Length));

	BrgDevAddr.ADDR=Brg->Address.ADDR;
	//Set Memory Base 
	BrgDevAddr.Addr.Register=PCI_MEMBASE; 
	//buff=Base>>16;
	buff=Shr64(Base,16);	

	Status=PciCfg16(Brg->RbIo, BrgDevAddr,TRUE,(UINT16*)&buff);
	if(EFI_ERROR(Status))return Status;

	//Set Memory limt
	BrgDevAddr.Addr.Register=PCI_MEMLIMIT;
	buff=Shr64(Base+(Length-1),16);
	return 	PciCfg16(Brg->RbIo, BrgDevAddr,TRUE,(UINT16*)&buff);
}


//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   DisableBridgeMmioDecoding()
//
// Description: Disables PCI Bridge MMIO Space Decoding.
//
// Input:
//  PCI_BRG_INFO    *Brg        Pointer to PCI Bridge Private Data structure.
//
// Output:	EFI_STATUS
//  EFI_SUCCESS             When everything is going on fine!
//  EFI_DEVICE_ERROR        When driver fails access PCI Bus.
//  EFI_INVALID_PARAMETER   When some of the parameters are invalid.
//
// Referals: PCI_BRG_INFO.
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS DisableBridgeMmioDecoding(PCI_BRG_INFO *Brg)
{
	PCI_CFG_ADDR	BrgDevAddr;
	UINT32			buff=0x0000FFFF;
//----------------------------------------
	BrgDevAddr.ADDR=Brg->Common.Address.ADDR;
	//Set Memory Base to FFFF and Limit to 0;
	BrgDevAddr.Addr.Register=0x20; 
	return PciCfg32(Brg->Common.RbIo, BrgDevAddr,TRUE,&buff);
}


//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   EnableBridgePfmmDecoding()
//
// Description: Enables PCI Bridge Prefetchable MMIO Space Decoding.
//
// Input:
//  PCI_DEV_INFO    *Brg        Pointer to PCI Bridge Private Data structure.
//  UINT64          Base        Base Address of the Bridge I/O Window.
//  UINT64          Length      Length of the Bridge I/O Window.
//
// Output:	EFI_STATUS
//  EFI_SUCCESS             When everything is going on fine!
//  EFI_DEVICE_ERROR        When driver fails access PCI Bus.
//  EFI_INVALID_PARAMETER   When some of the parameters are invalid.
//
// Referals: PCI_DEV_INFO.
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS EnableBridgePfmmDecoding(PCI_DEV_INFO *Brg, UINT64 Base, UINT64 Length)
{
	PCI_CFG_ADDR	BrgDevAddr;
	UINT64			buff;
	EFI_STATUS		Status;
//----------------------------------------
    PCI_TRACE((TRACE_PCI,"PciBus: Enabling Brg PFMM @ B%X|D%X|F%X\n, B=%lX; L=%lX\n", 
	Brg->Address.Addr.Bus, Brg->Address.Addr.Device,Brg->Address.Addr.Function,
    Base, Length));

	BrgDevAddr.ADDR=Brg->Address.ADDR;

	//Set Pf Memory Base 
	BrgDevAddr.Addr.Register=0x24; 
	buff=Shr64(Base,16);
	
	Status = PciCfg16(Brg->RbIo, BrgDevAddr, TRUE,(UINT16*)&buff);
	if(EFI_ERROR(Status))return Status;

	//Set PF Memory Limit
	BrgDevAddr.Addr.Register=0x26; 
	buff=Shr64(Base+(Length-1),16);
	
	Status = PciCfg16(Brg->RbIo, BrgDevAddr, TRUE, (UINT16*)&buff);
	if(EFI_ERROR(Status))return Status;

	buff=Shr64(Base,32);
	//Set Pf Memory Upper 32 Base
	BrgDevAddr.Addr.Register=0x28; 
	Status = PciCfg32(Brg->RbIo, BrgDevAddr,TRUE,(UINT32*)&buff);
	if(EFI_ERROR(Status))return Status;

	buff=Shr64(Base+(Length-1),32);
	//Set Pf Memory Upper 32 Limit 
    BrgDevAddr.Addr.Register=0x2C; 
	return PciCfg32(Brg->RbIo, BrgDevAddr,TRUE,(UINT32*)&buff);
}


//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   DisableBridgePfmmDecoding()
//
// Description: Disables PCI Bridge Prefetchable MMIO Space Decoding.
//
// Input:
//  PCI_BRG_INFO    *Brg        Pointer to PCI Bridge Private Data structure.
//
// Output:	EFI_STATUS
//  EFI_SUCCESS             When everything is going on fine!
//  EFI_DEVICE_ERROR        When driver fails access PCI Bus.
//  EFI_INVALID_PARAMETER   When some of the parameters are invalid.
//
// Referals: PCI_BRG_INFO.
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS DisableBridgePfmmDecoding(PCI_BRG_INFO *Brg)
{
	PCI_CFG_ADDR	BrgDevAddr;
	UINT32			buff=0x0000FFFF;
	EFI_STATUS		Status;
//----------------------------------------
	BrgDevAddr.ADDR=Brg->Common.Address.ADDR;

	//Set Pf Memory Base to FFFF Limit to 0;
	BrgDevAddr.Addr.Register=0x24; 
	Status = PciCfg32(Brg->Common.RbIo, BrgDevAddr,TRUE,&buff);
	if(EFI_ERROR(Status))return Status;

	buff=0;
	//Set Pf Memory Upper 32 Base to 0;
	BrgDevAddr.Addr.Register=0x28; 
	Status = PciCfg32(Brg->Common.RbIo, BrgDevAddr,TRUE,&buff);
	if(EFI_ERROR(Status))return Status;

	//Set Pf Memory Upper 32 Limit to 0; 
    BrgDevAddr.Addr.Register=0x2c; 
	return PciCfg32(Brg->Common.RbIo, BrgDevAddr,TRUE,&buff);
}


//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   DisableBridgeDecoding()
//
// Description: Disables PCI Bridge Decoding of ALL resources.
//
// Input:
//  PCI_BRG_INFO    *Brg        Pointer to PCI Bridge Private Data structure.
//
// Output:	EFI_STATUS
//  EFI_SUCCESS             When everything is going on fine!
//  EFI_DEVICE_ERROR        When driver fails access PCI Bus.
//  EFI_INVALID_PARAMETER   When some of the parameters are invalid.
//
// Referals: PCI_BRG_INFO.
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS DisableBridgeDecoding(PCI_BRG_INFO *Brg)
{
	EFI_STATUS		Status;
//---------------------------------------
	
    PCI_TRACE((TRACE_PCI,"PciBus: Disabling Brg @ B%X|D%X|F%X\n", 
	Brg->Common.Address.Addr.Bus, Brg->Common.Address.Addr.Device,Brg->Common.Address.Addr.Function));
	Status=DisableBridgeIoDecoding(Brg);
	if(EFI_ERROR(Status))return Status;

	Status=DisableBridgeMmioDecoding(Brg);
	if(EFI_ERROR(Status))return Status;

	return DisableBridgePfmmDecoding(Brg);
}


//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   SetSubBus()
//
// Description: Programm SubordinateBusNumber Register of PCI Bridge.
//
// Input:
//  PCI_DEV_INFO    *Brg        Pointer to PCI Bridge Private Data structure.
//  UINT8           SubBusNo    Number to programm.
//
// Output:	EFI_STATUS
//  EFI_SUCCESS             When everything is going on fine!
//  EFI_DEVICE_ERROR        When driver fails access PCI Bus.
//  EFI_INVALID_PARAMETER   When some of the parameters are invalid.
//
// Referals: PCI_BRG_INFO.
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS SetSubBus(PCI_DEV_INFO *Brg, UINT8 SubBusNo)
{
	PCI_CFG_ADDR	addr;
//---------------------------------------
	addr.ADDR=Brg->Address.ADDR;
	addr.Addr.Register=PCI_BRIDGE_SUBORDINATE_BUS_REGISTER_OFFSET; //Sub Bus No reg
	
	return PciCfg8(Brg->RbIo, addr,TRUE,&SubBusNo);
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   AddBusDbEntry()
//
// Description: Fills gPciBusDb Array in ascending  order.
//
// Input:
//  PCI_BRG_EXT     *Ext        Pointer to PCI Bridge Extension Private Data structure.
//
// Output:	EFI_STATUS
//  EFI_SUCCESS             When everything is going on fine!
//  EFI_DEVICE_ERROR        When driver fails access PCI Bus.
//  EFI_INVALID_PARAMETER   When some of the parameters are invalid.
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS  AddBusDbEntry(PCI_BUS_XLAT_HDR *BusHdr, T_ITEM_LIST *BusDb){
    EFI_STATUS          Status;
    UINTN               i;
    PCI_BUS_XLAT_HDR    *xhdr;        
//--------------------------
    
    if(BusDb->ItemCount==0) {
         Status=AppendItemLst(BusDb, BusHdr);
    } else {
        for(i=0; i<BusDb->ItemCount; i++){
            xhdr = (PCI_BUS_XLAT_HDR*)BusDb->Items[i];
            if(xhdr->BusBuild > BusHdr->BusBuild){
                return InsertItemLst(BusDb, BusHdr, i);
            }
        }//for
        // if we here and didn't returned yet - BusHdr->BusBuild is the bidggest one.
        Status = AppendItemLst(BusDb, BusHdr);
    }
#if AMI_BOARD_VER_COMBINED >= 100
    //Increase BusXlatTable entry count...
    if(!EFI_ERROR(Status)) gAmiBoardInfo->BusXlatEntries++;
#endif
    return Status;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   PopulateBusDb()
//
// Description: Fills gPciBusDb Array in ascending  order.
//
// Input:       Nothing;
//
// Output:	EFI_STATUS
//  EFI_SUCCESS             When everything is going on fine!
//  EFI_DEVICE_ERROR        When driver fails access PCI Bus.
//  EFI_INVALID_PARAMETER   When some of the parameters are invalid.
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS  PopulateBusDb(){
    PCI_BUS_XLAT_HDR    *xhdr=gAmiBoardInfo->BusXlatTable;
    PCI_DEV_FUN         *devf = (PCI_DEV_FUN*)(xhdr+1);
    EFI_STATUS          Status=EFI_SUCCESS;
//--------------------------------
    while((UINTN)devf<=(UINTN)(gAmiBoardInfo->BusXlatTable) + gAmiBoardInfo->BusXlatLength){
        if(devf->DEV_FUN == 0xFF){
            //if we are looking for host device it shouldn't be any other guys in it's chain.
            Status=AddBusDbEntry(xhdr, &gPciBusDb);
            ASSERT_EFI_ERROR(Status);
            if(EFI_ERROR(Status)) return Status;
            //Advance to the next record in BusXlatTbl.
#if AMI_BOARD_VER_COMBINED >= 100
            //Now we have AslName[5] following devf data (sizeof(PCI_DEV_FUN)==1 byte)
            xhdr=(PCI_BUS_XLAT_HDR*)(devf+1+5);
#else
            xhdr=(PCI_BUS_XLAT_HDR*)(devf+1);
#endif
            devf = (PCI_DEV_FUN*)(xhdr+1);
            continue;
        } else {
            devf++;
        }
    }
    return Status;
}

/*
//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   FindRootXlatEntry()
//
// Description: Finds corresponded BusXlatTable entry for the bridge.
//
// Input:
//  PCI_DEV_INFO        *Dev        Pointer to PCI Bridge Private Data structure.
//  PCI_BUS_XLAT_HDR    *XlatHdr    Double Pointer to XLAT_HEADER will be initialized by this function 
//
// Output:	EFI_STATUS
//  EFI_SUCCESS             When everything is going on fine!
//  EFI_DEVICE_ERROR        When driver fails access PCI Bus.
//  EFI_INVALID_PARAMETER   When some of the parameters are invalid.
//
// Referals: PCI_DEV_INFO; PCI_BRG_INFO; PCI_BRG_EXT.
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS FindRootXlatEntry(PCI_DEV_INFO *Dev, PCI_BUS_XLAT_HDR **XlatHdr){
    PCI_DEV_INFO    *brg=Dev;
    PCI_BRG_EXT     *ext=NULL;
//-------------------------
    while(brg->Type==tPciRootBrg){
        brg=brg->ParentBrg;
        //this code just to double check the loop will be exited.
        //
        if(brg->ParentBrg==NULL){
            ext=(PCI_BRG_EXT*)(brg+1);
            
            if(ext->XlatTblEntry==NULL) return EFI_NOT_FOUND; 

            *XlatHdr=ext->XlatTblEntry;
                
            break;
        }
    }

    if(ext==NULL) return EFI_NOT_FOUND;

    return EFI_SUCCESS;

}
*/

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   FindBridgeXlatEntry()
//
// Description: Finds corresponded BusXlatTable entry for the bridge.
//
// Input:
//  PCI_DEV_INFO    *Dev        Pointer to PCI Bridge Private Data structure.
//  PCI_BRG_EXT     *Ext        Pointer to PCI Bridge Extension Private Data structure.
//
// Output:	EFI_STATUS
//  EFI_SUCCESS             When everything is going on fine!
//  EFI_DEVICE_ERROR        When driver fails access PCI Bus.
//  EFI_INVALID_PARAMETER   When some of the parameters are invalid.
//
// Referals: PCI_DEV_INFO; PCI_BRG_INFO; PCI_BRG_EXT.
//
// Notes:
//  BaseBus         =   PCI_DEV_INFO->Address.Addr.Bus;
//  SecondaryBus    =   PCI_BRG_EXT->Res[rtBus].Base;
//  SubordinateBus  =   PCI_BRG_EXT->Res[rtBus].Base + PCI_BRG_EXT->Res[rtBus].Length-1;
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS FindBridgeXlatEntry(PCI_DEV_INFO *Dev, PCI_BRG_EXT *Ext){
    PCI_BUS_XLAT_HDR    *xhdr;
    PCI_DEV_FUN         *devf;
    UINTN               i, chncnt; //Xlat Tbl Elemnts count (number of Dev/Fn instances)
    PCI_BRG_EXT         *ext;
//-----------------------------
    //Now we will go trough BusXlatTbl entryes.
    for(i=0; i<gPciBusDb.ItemCount; i++){
        xhdr=gPciBusDb.Items[i];
        devf = (PCI_DEV_FUN*)(xhdr+1);
        for (chncnt=0; ; devf++,chncnt++){
            //Got to the end of PCI device chain 
            if(devf->DEV_FUN == 0xFF){
                //if we are looking for host device it shouldn't be any other guys in it's chain.
                if((Dev->ParentBrg == NULL) && (chncnt==1) && (Dev->Type==tPciRootBrg)){
                //Check first if it is a correct host.
                    if( (xhdr->BusBuild == Dev->Address.Addr.Bus) )
                    {
                        //xhdr->BusRun = Dev->Address.Addr.Bus;
                        Ext->XlatTblEntry=xhdr;
                        Ext->ChainNumber=(UINT8)chncnt;
                        Ext->ItemNumber=(UINT8)i;
                
                        PCI_TRACE((TRACE_PCI,"PciBus: Found BusXlat for Host [B%X|D%X|F%X] BusBuild=%X\n", 
                        Dev->Address.Addr.Bus,Dev->Address.Addr.Device, Dev->Address.Addr.Function, xhdr->BusBuild));                
                        
                        return EFI_SUCCESS;
                    }
                } else { 
                //NOT HOST Device !((Dev->ParentBrg == NULL) && (chncnt==1)) 
                    PCI_DEV_FUN         *df=devf-1;      
                //----------------------
                    if(Dev->ParentBrg!=NULL){
                        
                        //Here we will define a criteria when XLAT TBL entrie considered a match..
                        //1. ParentBrg->Ext->XlatTblEntry must be initialized
                        //2. ParentBrg->ChainNumber must be  (chncnt-1) so this one will be the same elememnt
                        //3. ParentBrg->Ext->XlatTblEntry->BusBuild must not exceed THIS xhdr->BusBuild
                        //4. df->Dev==Dev->Address.Addr.Device AND df->Fun==Dev->Address.Addr.Function
                        //5. THIS Dev->Ext->XlatTbEntry must not be initialized yet..                        
                        
                        //Get Parent Bridge ext of this device.
                        ext=(PCI_BRG_EXT*)(Dev->ParentBrg+1);
                            
                        //1. ParentBrg->Ext->XlatTblEntry must be initialized
                        //2. ParentBrg->Ext->ChainNumber must be  (chncnt-1) so this one will be the same elememnt in it's Chain
                        //5. THIS Dev->Ext->XlatTbEntry must not be initialized yet...
                        if((Ext->XlatTblEntry==NULL)&&(ext->XlatTblEntry!=NULL) && (ext->ChainNumber == (UINT8)chncnt-1)){                        
                            
                            //3. ParentBrg->Ext->XlatTblEntry->BusBuild must not exceed THIS xhdr->BusBuild
                            if( xhdr->BusBuild > ext->XlatTblEntry->BusBuild  ) {
                            
                               //4. df->Dev==Dev->Address.Addr.Device AND df->Fun==Dev->Address.Addr.Function
                               if((Dev->Address.Addr.Device == df->Dev)&&(Dev->Address.Addr.Function == df->Fun)){
                                    
                                    if(MemCmp((VOID*)(ext->XlatTblEntry+1),(VOID*)(xhdr+1), ext->ChainNumber)==0){
                                        //xhdr->BusRun = Dev->Address.Addr.Bus;
                                        Ext->XlatTblEntry=xhdr;
                                        Ext->ChainNumber=(UINT8)chncnt;
                                        Ext->ItemNumber=(UINT8)i;
                                        PCI_TRACE((TRACE_PCI,"PciBus: Found BusXlat for Brg  [B%X|D%X|F%X] BusBuild=%X\n", 
                                        Dev->Address.Addr.Bus,Dev->Address.Addr.Device, Dev->Address.Addr.Function, xhdr->BusBuild));                
                                        return EFI_SUCCESS;
                                    }
                                }//Cond 4
                                
                            }//cond 3;
                            
                        }//cond 1;2;5;
                    }//if(Dev->ParentBrg!=NULL)
                } //else
                break;
            }//devf->DEV_FUN == 0xFF  
        } //for chncnt
    } //for i
          
    return EFI_NOT_FOUND;        
}


//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   FindBridgeXlatEntry()
//
// Description: Finds corresponded BusXlatTable entry for the next bridge
//              of the same level (same number of nodes/chain-counts).
//
// Input:
//  PCI_BRG_EXT     *Ext        Pointer to PCI Bridge Extension Private Data structure.
//
// Output:	UINT8   Number of buses decoded by the Bridge which "Ext" passed.
//
// Notes:
//  BaseBus         =   PCI_DEV_INFO->Address.Addr.Bus;
//  SecondaryBus    =   PCI_BRG_EXT->Res[rtBus].Base;
//  SubordinateBus  =   PCI_BRG_EXT->Res[rtBus].Base + PCI_BRG_EXT->Res[rtBus].Length-1;
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
UINT8 FindNextSameLevelBrgXlatEntry(PCI_BRG_EXT *Ext){
    PCI_BUS_XLAT_HDR    *xhdr;
    PCI_DEV_FUN         *devf;
    UINTN               i, chncnt; //Xlat Tbl Elemnts count (number of Dev/Fn instances)
//-----------------------------
    //Now we will go trough BusXlatTbl entryes.
    if(gPciBusDb.ItemCount <= (UINTN)(Ext->ItemNumber+1) ) return (UINT8)mMaxBusScan;

    for(i=Ext->ItemNumber+1; i<gPciBusDb.ItemCount; i++){
        xhdr=gPciBusDb.Items[i];
        devf = (PCI_DEV_FUN*)(xhdr+1);
        for (chncnt=0; ; devf++,chncnt++){
            //Got to the end of PCI device chain 
            if(devf->DEV_FUN == 0xFF) break;
        } //for chncnt
        //here we found record terminator 
        //go and check the following.
        //1. if this Xlat node of the same or less 
        if(chncnt<=Ext->ChainNumber) return (UINT8)(xhdr->BusBuild-1);
    } //for i
          
    return (UINT8)mMaxBusScan;
}


//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   FindDevIrqEntry()
//
// Description: Finds corresponded BusXlatTable entry for the bridge.
//
// Input:
//  PCI_DEV_INFO    *Dev        Pointer to PCI Bridge Private Data structure.
//
// Output:	EFI_STATUS
//  EFI_SUCCESS             When everything is going on fine!
//  EFI_DEVICE_ERROR        When driver fails access PCI Bus.
//  EFI_INVALID_PARAMETER   When some of the parameters are invalid.
//
// Referals: PCI_DEV_INFO; PCI_BRG_INFO; PCI_BRG_EXT.
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS FindDevIrqEntry(PCI_DEV_INFO *Dev){
    UINTN               i, cnt;
    PCI_DEV_INFO        *brg=Dev->ParentBrg;
    PCI_BRG_EXT         *ext=(PCI_BRG_EXT*)(brg+1);
    PCI_BUS_XLAT_HDR    *xhdr=ext->XlatTblEntry;
    PCI_IRQ_PIC_ROUTE   *pic;
    PCI_IRQ_APIC_ROUTE  *apic;
//-----------------------------------

    //Find Matching IRQ Routing entry for PIC 
    //cnt=((UINTN)gPicIrqTblEnd-(UINTN)gPicIrqRoutTbl)/sizeof(PCI_IRQ_PIC_ROUTE)-1;
    cnt=gAmiBoardInfo->PicRoutLength/sizeof(PCI_IRQ_PIC_ROUTE);

    for(i=0; i<cnt; i++){         
        pic=&gAmiBoardInfo->PicRoutTable[i];
        if(xhdr->BusBuild==pic->PciBusNumber){
            //pic->PciBusNumber=xhdr->BusRun;
            
            if( pic->DevFun.Dev == Dev->Address.Addr.Device){
                Dev->PicIrqEntry = pic;    
                break;
            }
        }                    
    }
    //Find Matching IRQ Routing entry for APIC 
    //cnt=((UINTN)gApicIrqTblEnd-(UINTN)gApicIrqRoutTbl)/sizeof(PCI_IRQ_APIC_ROUTE)-1;
    cnt=gAmiBoardInfo->ApicRoutLength/sizeof(PCI_IRQ_APIC_ROUTE);

    for(i=0; i<cnt; i++){         
        apic=&gAmiBoardInfo->ApicRoutTable[i];        
        if(xhdr->BusBuild==apic->PciBusNumber){
            //apic->PciBusNumber=xhdr->BusRun;
            
            if( apic->DeviceNumber == Dev->Address.Addr.Device){
                Dev->ApicIrqEntry = apic;   
                break;
            }
        }                    
    }

    return EFI_SUCCESS;
}

//<AMI_SHDR_START>
//----------------------------------------------------------------------------
// Name:		*mPicIrqSta[]; *mPicIrqSta[]
//
// Description: To make sure we are not updating entries we have updated 
// already, we would need array of BBOLEANs to mark updated entries.
//
//  NOTE: BOOLEAN Aarray [IrqRoiting Table enytries Number] 
//----------------------------------------------------------------------------
//<AMI_SHDR_END>
BOOLEAN *mPicIrqSta = NULL;
BOOLEAN *mApicIrqSta= NULL;

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   UpdateItqTbl()
//
// Description: Updtaes all matching entries in Irqrouting tables with 
// runtime values.
//
// Input:
//  PCI_BUS_XLAT_HDR    *XlatHdr    Updated BusTranslate table entry.
//
// Output:	NOTHING
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID UpdateIrqTables(PCI_BUS_XLAT_HDR *XlatHdr){
    UINTN   i;
    PCI_IRQ_PIC_ROUTE   *pic;
    PCI_IRQ_APIC_ROUTE  *apic;
//------------------------------

    if(mPicIrqSta==NULL) mPicIrqSta=MallocZ(gAmiBoardInfo->PicRoutLength/sizeof(PCI_IRQ_PIC_ROUTE));
    if(mApicIrqSta==NULL) mApicIrqSta=MallocZ(gAmiBoardInfo->ApicRoutLength/sizeof(PCI_IRQ_APIC_ROUTE));

    for(i=0; i<gAmiBoardInfo->PicRoutLength/sizeof(PCI_IRQ_PIC_ROUTE); i++){   
        pic=&gAmiBoardInfo->PicRoutTable[i];
        if(pic->PciBusNumber==XlatHdr->BusBuild && mPicIrqSta[i]==FALSE) {
            pic->PciBusNumber=XlatHdr->BusRun;
            mPicIrqSta[i]=TRUE;
        }
    }      

    //Not likely but who knows... it could be that gAmiBoardInfo->PicRoutLength 
    //different from gAmiBoardInfo->ApicRoutLength... so teke care of that!
    for(i=0; i<gAmiBoardInfo->ApicRoutLength/sizeof(PCI_IRQ_APIC_ROUTE); i++){   
        apic=&gAmiBoardInfo->ApicRoutTable[i];      
        if(apic->PciBusNumber==XlatHdr->BusBuild && mApicIrqSta[i]==FALSE) {
            apic->PciBusNumber=XlatHdr->BusRun;
            mApicIrqSta[i]=TRUE;
        }
    }
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   RemoveUnusedIrqEntries()
//
// Description: Removes IRQ routing entries which got there by porting mistake
// in order not to confuse other consumers of AmiBoardInfoProtocol...
//
// Input:   NOTHING
//
// Output:	NOTHING
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID RemoveUnusedIrqEntries(){
    UINTN   i, j, cnt; 
    PCI_IRQ_PIC_ROUTE   *tmpp;
    PCI_IRQ_APIC_ROUTE  *tmpa;
//------------------------------
    cnt=gAmiBoardInfo->PicRoutLength/sizeof(PCI_IRQ_PIC_ROUTE);
    tmpp=(PCI_IRQ_PIC_ROUTE*)Malloc(gAmiBoardInfo->PicRoutLength);
    ASSERT(tmpp);

    for(j=0,i=0; j<cnt; j++){
        if(mPicIrqSta[j]==TRUE){
            MemCpy(&tmpp[i],&gAmiBoardInfo->PicRoutTable[j],sizeof(PCI_IRQ_PIC_ROUTE));
            i++;
        } else {
            gAmiBoardInfo->PicRoutLength -= sizeof(PCI_IRQ_PIC_ROUTE);
			PCI_TRACE((TRACE_PCI,"PciBus: Removing unused entry #%d from PIC Routing Table\n", j));
        }
    }
    //Copy updated tabe from tmp buffer to AmiBoardInfo Location 
    MemCpy(&gAmiBoardInfo->PicRoutTable[0], &tmpp[0], gAmiBoardInfo->PicRoutLength);

    //Not likely but who knows... it could be that gAmiBoardInfo->PicRoutLength 
    //different from gAmiBoardInfo->ApicRoutLength... so teke care of that!
    cnt=gAmiBoardInfo->ApicRoutLength/sizeof(PCI_IRQ_APIC_ROUTE);
    tmpa=(PCI_IRQ_APIC_ROUTE*)Malloc(gAmiBoardInfo->ApicRoutLength);
    ASSERT(tmpa);

    for(j=0,i=0; j<cnt;j++){
        if(mApicIrqSta[j]==TRUE){
            MemCpy(&tmpa[i],&gAmiBoardInfo->ApicRoutTable[j],sizeof(PCI_IRQ_APIC_ROUTE));
            i++;
        } else {
            gAmiBoardInfo->ApicRoutLength -= sizeof(PCI_IRQ_APIC_ROUTE);
			PCI_TRACE((TRACE_PCI,"PciBus: Removing unused entry #%d from APIC Routing Table\n", j));
        }
    }
    //Copy updated tabe from tmp buffer to AmiBoardInfo Location 
    MemCpy(&gAmiBoardInfo->ApicRoutTable[0], &tmpa[0], gAmiBoardInfo->ApicRoutLength);

    //free buffers allocated, functions depending on it 
    //not suppose to be called anymore.
    if(mPicIrqSta!=NULL){
        pBS->FreePool(mPicIrqSta);
        mPicIrqSta=NULL;
    }
    if(mApicIrqSta!=NULL){
        pBS->FreePool(mApicIrqSta);
        mApicIrqSta=NULL;
    }
    if(tmpp!=NULL) pBS->FreePool(tmpp);
    if(tmpa!=NULL) pBS->FreePool(tmpa);
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   MapBridgeBuses()
//
// Description: Maps Bridge's Primary Secondary Subordinate Bus Numbers
// according information stored in PCI_DEV_INFO and PCI_BRG_EXT structures
// of the PCI Bridge.
//
// Input:
//  PCI_DEV_INFO    *Brg        Pointer to PCI Bridge Private Data structure.
//
// Output:	EFI_STATUS
//  EFI_SUCCESS             When everything is going on fine!
//  EFI_DEVICE_ERROR        When driver fails access PCI Bus.
//  EFI_INVALID_PARAMETER   When some of the parameters are invalid.
//
// Referals: PCI_DEV_INFO; PCI_BRG_INFO; PCI_BRG_EXT.
//
// Notes:
//  BaseBus         =   PCI_DEV_INFO->Address.Addr.Bus;
//  SecondaryBus    =   PCI_BRG_EXT->Res[rtBus].Base;
//  SubordinateBus  =   PCI_BRG_EXT->Res[rtBus].Base + PCI_BRG_EXT->Res[rtBus].Length-1;
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS MapBridgeBuses(PCI_DEV_INFO *Brg)
{
	EFI_STATUS		Status;
	PCI_CFG_ADDR	addr;
	UINT8			bus;
	PCI_BRG_EXT		*ext=(PCI_BRG_EXT*)(Brg+1);
//--------------------------------
	//Get Bridge Initial Address
	addr.ADDR=Brg->Address.ADDR;
	//Primary bus;
	addr.Addr.Register=PCI_BRIDGE_PRIMARY_BUS_REGISTER_OFFSET;    //Primary BusNo
	bus=Brg->Address.Addr.Bus;
	Status=PciCfg8(Brg->RbIo,addr,TRUE,&bus);
	if(EFI_ERROR(Status))return Status;

	//SecondaryBus Register
	addr.Addr.Register=PCI_BRIDGE_SECONDARY_BUS_REGISTER_OFFSET; //Secondary BusNo

	bus=(UINT8)ext->Res[rtBus].Base;
	Status=PciCfg8(Brg->RbIo,addr,TRUE,&bus);
	if(EFI_ERROR(Status))return Status;

	//Now Programm SubordinateBusNo reg
	bus=(UINT8)(ext->Res[rtBus].Base+ext->Res[rtBus].Length-1);
	return SetSubBus(Brg, bus);
}


//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   CheckPciCompatibility()
//
// Description: This function will check if PCI "Device" listed in Bad PCI 
// Device Table - gBadPciDevList[].
//
// Input:
//  PCI_DEV_INFO    *Device     Pointer to PCI Device Private Data structure.
//  PCI_BAR_TYPE    BarType     Type of Bar Register.
//
// Output:	EFI_STATUS
//  EFI_SUCCESS             When everything is going on fine!
//  EFI_DEVICE_ERROR        When driver fails access PCI Bus.
//  EFI_INVALID_PARAMETER   When some of the parameters are invalid.
//
// Referals: PCI_DEV_INFO; PCI_BAR_TYPE.
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
PCI_BAD_BAR *CheckPciCompatibility(PCI_DEV_INFO *Device, PCI_BAR *Bar, PCI_BAR_TYPE BarType) //(EIP41687)
{
	UINTN				i;
	PCI_BAD_BAR			*bbp;
	PCI_DEV_ID			d,t;
//-----------------------
	d.DEV_VEN_ID=Device->DevVenId.DEV_VEN_ID;
	for(i=0; i<gBadPciDevCount; i++){
		bbp=&gBadPciDevList[i];
        //(EIP41687)>
        if(Bar) {
            if (bbp->BarOffset) {
                if (Bar->Offset != bbp->BarOffset) continue;
            }
        }
        //<(EIP41687)
		t.VenId=bbp->VendorId;
		t.DevId=bbp->DeviceId & bbp->DevIdMask;
		d.DevId=Device->DevVenId.DevId & bbp->DevIdMask;
		if(d.DEV_VEN_ID==t.DEV_VEN_ID){
			if(BarType) {
				if(BarType==bbp->BarType) return bbp;
			} else return bbp;
		}
	}
	return NULL;
}


//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   AdjustBarGra()
//
// Description: This function will Check and Adjust PCI Device's BAR
// Granularity according information found in gBadPciDevList[].
//
// Input:
//  PCI_BAR     Bar         Type of Bar Register.
//
// Output:	NOTHING
//
// Referals: PCI_BAR; PCI_BAR_TYPE; gBadPciDevList.
//
// Notes:
//  This function will be invoked only if PCI Device owning this BAR is in
// gBadPciDevList.
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID AdjustBarGra(PCI_BAR *Bar){
	UINTN			i,s,e;
	PCI_BAR_TYPE	bt;
	PCI_BAD_BAR		*bbp;
	UINT64			t=0,g=~(Bar->Gran);	
//----------------------------	
	switch(Bar->Type){
		case 	tBarIo16:		//2
		case 	tBarIo32:		//3
			bt=tBarIo;
			s=2;
			break;
		case tBarMmio32:		//4
		case tBarMmio32pf:	//5
		case tBarMmio64:		//6
		case tBarMmio64pf:	//7
			bt=tBarMem;
			s=4;
            break;
        default: 
            bt=tBarUnused;
		    s=0;
	}	
	
	bbp=CheckPciCompatibility(Bar->Owner,Bar,bt); //(EIP41687)
	if(!bbp)bbp=CheckPciCompatibility(Bar->Owner,Bar,tBarMaxType); //(EIP41687)
	//this function will be called only if compatibility issue exists with the device
	//so bbp must be valid or this is not the BAR which needs Adjustment;
	if(!bbp) return; 
	if(bbp->BarType==tBarMaxType && Bar->Offset!=bbp->BarOffset) return;
	
	//Here let's do the adjustment...
	switch(bbp->IncompType){
		case 	icBarBad:
			for(i=s; i<64; i++){
				//find the very first bit set as 1;
				t=Shl64(1,(UINT8)i);
				if(g&t)break;
			}
			//Assume that all other bits must be 1
			e=i;
			t=0;
			//Generate Granularity value for this BAR
			for(i=0;i<e;i++)t|=Shl64(1,(UINT8)i);
			if(Bar->Type!= tBarMmio64pf	&& Bar->Type!=tBarMmio64) t&=0xFFFFFFFF;
			Bar->Gran=t;
		break;

		case 	icBarFixedSize:
			Bar->Length=bbp->BarLength;
			Bar->Gran=bbp->BarLength-1;
		break;
	
		case 	icNotBar	:
			Bar->Type=tBarUnused;
			Bar->Length=0;
			Bar->Gran=0;
		break;

		case 	icBad64BitBar	:
			if(Bar->Type == tBarMmio64pf) Bar->Type=tBarMmio32pf;
			else if (Bar->Type == tBarMmio64) Bar->Type=tBarMmio32;
		break;
	}//switch
	
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   OptionRom()
//
// Description: This function will detect PCI Option ROMs BAR requirements.
//
// Input:
//  PCI_DEV_INFO    *Device     Pointer to PCI Device Private Data structure.
//
// Output:	EFI_STATUS
//  EFI_SUCCESS             When everything is going on fine!
//  EFI_DEVICE_ERROR        When driver fails access PCI Bus.
//  EFI_INVALID_PARAMETER   When some of the parameters are invalid.
//
// Referals: PCI_DEV_INFO.
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS  OptionRom(PCI_DEV_INFO *Device)
{
	PCI_CFG_ADDR	devaddr;
	EFI_STATUS		Status=0;
	UINT32			b32;
	PCI_BAR			*rombar;
//---------------------------------
	//Our Device still in disable decoding mode which it entered in   
	//Now Query Expansion ROM reg 
	// the bit0 is 0 to prevent the enabling of the Rom address decoder
	devaddr.ADDR=Device->Address.ADDR;
	switch (Device->Type){
		case tPci2PciBrg : devaddr.Addr.Register=PCI_P2P_ROM_BAR;
			break;
		case tPciDevice	 : 
		case tPciHostDev :	
			devaddr.Addr.Register=PCI_DEV_ROM_BAR;
			break;
		case tPci2CrdBrg : //this one doesnot have ROM BAR
		default	:	return EFI_SUCCESS; //other devices not suppose to be examined
	}

	rombar=&Device->Bar[PCI_MAX_BAR_NO];
	rombar->Offset=devaddr.Addr.Register;

	b32=0xFFFFFFFE;

	//Write query pattern to PCI Rom Bar Register
	Status=PciCfg32(Device->RbIo,devaddr,TRUE,&b32);
	if(EFI_ERROR (Status)) return Status;
    
	Status=PciCfg32(Device->RbIo,devaddr,FALSE,&b32);
	if(EFI_ERROR (Status)) return Status;
   
	b32&=0xFFFFFFFE;
	if ((b32 != 0) && (b32 != 0xFFFFFFFE)){
		rombar->Type=tBarMmio32;
		rombar->Gran=~b32;
		rombar->Length=(~b32)+1;
	}

	if(Device->Incompatible) AdjustBarGra(rombar);

	return Status;
}


//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   GetDeviceCapabilities()
//
// Description: This function will detect PCI Device Capabilities of the Device's
// Command Cegister and Bridge Command register (if any).
//
// Input:
//  PCI_DEV_INFO    *Device     Pointer to PCI Device Private Data structure.
//
// Output:	EFI_STATUS
//  EFI_SUCCESS             When everything is going on fine!
//  EFI_DEVICE_ERROR        When driver fails access PCI Bus.
//  EFI_INVALID_PARAMETER   When some of the parameters are invalid.
//
// Referals: PCI_DEV_INFO.
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS GetDeviceCapabilities(PCI_DEV_INFO *Dev)
{
	PCI_CFG_ADDR	addr;
	EFI_STATUS		Status;
	UINT16			oldcmd, tstcmd, oldbc, tstbc=0;
	EFI_TPL			OldTpl;
	UINT8			z, tcls;
//--------------------------------

	if(Dev->ParentBrg)Dev->Capab=Dev->ParentBrg->Capab;
	
	addr.ADDR=Dev->Address.ADDR;
	tstcmd=(PCI_CMD_IO_SPACE | PCI_CMD_MEMORY_SPACE | PCI_CMD_MEMORY_WRITE_AND_INVALIDATE |
			PCI_CMD_BUS_MASTER | PCI_CMD_VGA_PALETTE_SNOOP);

	OldTpl=pBS->RaiseTPL(TPL_HIGH_LEVEL);

	//Set Latency Timer to 20 and Cacheline size to 0 - just in case
	addr.Addr.Register=0x0c;//Cacheline size & Latency Timer
	Status=PciCfg16(Dev->RbIo,addr,FALSE,&oldcmd);
	//PciX devices upon reset initialize Latency Timer reg with value of 0x40
	//regular PCI devices initialize it with 0
	if(!(oldcmd&0xff00)){//so we will program it only for Regular PCI devices
		oldcmd=0x2000;
		Status=PciCfg16(Dev->RbIo,addr,TRUE,&oldcmd);
		if(EFI_ERROR(Status))return Status;
	}
	addr.Addr.Register=0x04;//Command Reg

	//Read initial value
	Status=PciCfg16(Dev->RbIo,addr,FALSE,&oldcmd);
	if(EFI_ERROR(Status))return Status;

	//Write cmdval there and see if it supports it;
	Status=PciCfg16(Dev->RbIo,addr,TRUE,&tstcmd);
	if(EFI_ERROR(Status))return Status;

	//Read it back and see which bits remains set
	Status=PciCfg16(Dev->RbIo,addr,FALSE,&tstcmd);
	if(EFI_ERROR(Status))return Status;
	
	//Restore what was there
	Status=PciCfg16(Dev->RbIo,addr,TRUE,&oldcmd);
	if(EFI_ERROR(Status))return Status;

	if(Dev->Type==tPci2PciBrg){
	//Set Latency Timer to 20 and Cacheline size to 0 - just in case
		addr.Addr.Register=0x1b;//Secondary Latency Timer
		oldcmd=0x20;
		Status=PciCfg8(Dev->RbIo,addr,TRUE,(UINT8*)&oldcmd);
		if(EFI_ERROR(Status))return Status;

		addr.Addr.Register=0x3E; //Bridge controll reg
		tstbc=(P2P_BRG_CONTROL_ISA | P2P_BRG_CONTROL_VGA | P2P_BRG_CONTROL_VGA_16);
        
		//Read initial value
		Status=PciCfg16(Dev->RbIo,addr,FALSE,&oldbc);
		if(EFI_ERROR(Status))return Status;

		//Write cmdval there and see if it supports it;
		Status=PciCfg16(Dev->RbIo,addr,TRUE,&tstbc);
		if(EFI_ERROR(Status))return Status;

		//Read it back and see which bits remains set
		Status=PciCfg16(Dev->RbIo,addr,FALSE,&tstbc);
		if(EFI_ERROR(Status))return Status;
	
		//Restore what was there
		Status=PciCfg16(Dev->RbIo,addr,TRUE,&oldbc);
		if(EFI_ERROR(Status))return Status;
	}

	//Analize tstcmd Value and update Device->Capab;
	if(tstcmd & PCI_CMD_IO_SPACE)Dev->Capab|=EFI_PCI_IO_ATTRIBUTE_IO;
	else Dev->Capab&=(~EFI_PCI_IO_ATTRIBUTE_IO);

	if(tstcmd & PCI_CMD_MEMORY_SPACE)Dev->Capab|=EFI_PCI_IO_ATTRIBUTE_MEMORY;
	else Dev->Capab&=(~EFI_PCI_IO_ATTRIBUTE_MEMORY);

	if(tstcmd & PCI_CMD_BUS_MASTER)Dev->Capab|=EFI_PCI_IO_ATTRIBUTE_BUS_MASTER;
	else Dev->Capab&=(~EFI_PCI_IO_ATTRIBUTE_BUS_MASTER);

	if(tstcmd & PCI_CMD_VGA_PALETTE_SNOOP)Dev->Capab|=EFI_PCI_IO_ATTRIBUTE_VGA_PALETTE_IO;
	else Dev->Capab&=(~EFI_PCI_IO_ATTRIBUTE_VGA_PALETTE_IO);

//BUG//BUG//BUG//BUG//BUG//BUG//BUG
// This bits in cmd register does not identically maps to EFI_PCI_IO_ATTRIBUTE_MEMORY_WRITE_COMBINE
//	if( (tstcmd & PCI_CMD_MEMORY_WRITE_AND_INVALIDATE)||(tstcmd & PCI_CMD_FAST_BACK_TO_BACK) )
//		Dev->Capab|= EFI_PCI_IO_ATTRIBUTE_MEMORY_WRITE_COMBINE;
	
	//Check Device Capability on CacheLine Size Register	
	Dev->Capab|=MY_PCI_IO_ATTRIBUTE_MEM_WR_INVALIDATE;
	addr.Addr.Register=0x0c;//Cacheline size & Latency Timer

	//probe Cache Line Size register if it will accept proposed Cache line size
	tcls=0xFF;
	Status=PciCfg8(Dev->RbIo,addr,TRUE,&tcls);
	if(EFI_ERROR(Status))return Status;

	//Read it back and see which bits remains set
	Status=PciCfg8(Dev->RbIo,addr,FALSE,&z);
	if(EFI_ERROR(Status))return Status;

	tcls=gPciCaheLineSize;		

	//we have tested CLS register it will not accept any value we are proposing
	if(!( z && (z&(tcls-1)) ))Dev->Capab&=(~MY_PCI_IO_ATTRIBUTE_MEM_WR_INVALIDATE);
	else{
		while(!(tcls&z)) tcls=tcls>>1; //same as div 2		
		if(tcls<gPciCaheLineSize) gPciCaheLineSize=tcls;
	}
	//clear the register we will program it later when resources will be allocated
	tcls=0;
	Status=PciCfg8(Dev->RbIo,addr,TRUE,&tcls);
	if(EFI_ERROR(Status))return Status;

	//we have additional work to do if Device is P2P bridge
	if(Dev->Type==tPci2PciBrg){ 
		if(tstbc & P2P_BRG_CONTROL_ISA)Dev->Capab|=EFI_PCI_IO_ATTRIBUTE_ISA_IO;
		else Dev->Capab&=(~EFI_PCI_IO_ATTRIBUTE_ISA_IO);

        if(tstbc & P2P_BRG_CONTROL_VGA)Dev->Capab|=( EFI_PCI_IO_ATTRIBUTE_VGA_IO | 
					EFI_PCI_IO_ATTRIBUTE_VGA_MEMORY|EFI_PCI_IO_ATTRIBUTE_VGA_PALETTE_IO);
		else Dev->Capab&=(~(EFI_PCI_IO_ATTRIBUTE_VGA_IO | 
					EFI_PCI_IO_ATTRIBUTE_VGA_MEMORY|EFI_PCI_IO_ATTRIBUTE_VGA_PALETTE_IO));
        if(tstbc & P2P_BRG_CONTROL_VGA_16) Dev->Capab|=( EFI_PCI_IO_ATTRIBUTE_VGA_IO_16 | 
					EFI_PCI_IO_ATTRIBUTE_VGA_PALETTE_IO_16);
		else Dev->Capab&=(~(EFI_PCI_IO_ATTRIBUTE_VGA_IO_16 | EFI_PCI_IO_ATTRIBUTE_VGA_PALETTE_IO_16));

		//bridge should support IDE attributes
		Dev->Capab|=(EFI_PCI_IO_ATTRIBUTE_IDE_SECONDARY_IO | EFI_PCI_IO_ATTRIBUTE_IDE_PRIMARY_IO);
	} else {
		//Some special atributes could be supported by PCI devices based on class code
		switch (Dev->Class.BaseClassCode){
			case PCI_CL_OLD :
				if (Dev->Class.SubClassCode==PCI_CL_OLD_SCL_VGA)     
					Dev->Capab|=(EFI_PCI_IO_ATTRIBUTE_VGA_MEMORY | EFI_PCI_IO_ATTRIBUTE_VGA_IO);
				else 
					Dev->Capab&=(~(EFI_PCI_IO_ATTRIBUTE_VGA_MEMORY | EFI_PCI_IO_ATTRIBUTE_VGA_IO));
				break;
			case PCI_CL_DISPLAY:
				if (Dev->Class.SubClassCode==PCI_CL_DISPLAY_SCL_VGA)     
					Dev->Capab|=(EFI_PCI_IO_ATTRIBUTE_VGA_MEMORY | EFI_PCI_IO_ATTRIBUTE_VGA_IO);
				else 
					Dev->Capab&=(~(EFI_PCI_IO_ATTRIBUTE_VGA_MEMORY | EFI_PCI_IO_ATTRIBUTE_VGA_IO));

				if (Dev->Class.SubClassCode==PCI_CL_DISPLAY_SCL_OTHER) //GFX device can snoop pallete
					Dev->Capab|=EFI_PCI_IO_ATTRIBUTE_VGA_PALETTE_IO;
				else Dev->Capab&=(~EFI_PCI_IO_ATTRIBUTE_VGA_PALETTE_IO);
				break;
			case PCI_CL_MASS_STOR :
				if(Dev->Class.SubClassCode==PCI_CL_MASS_STOR_SCL_IDE){
					UINT8	pib=Dev->Class.ProgInterface, pif=0;
				//---------------
					Dev->Capab|=(EFI_PCI_IO_ATTRIBUTE_IDE_SECONDARY_IO|EFI_PCI_IO_ATTRIBUTE_IDE_PRIMARY_IO);
					//Now if device is IDE controller check PI on order determine how it was programmed
					//Just in case overwrite bus master capab if IDE device sets bit 7 in PI Reg
					if(Dev->Class.ProgInterface & 0x80) Dev->Capab|=EFI_PCI_IO_ATTRIBUTE_BUS_MASTER;

					//primary Controller in LEGACY mode?
					if( !(Dev->Class.ProgInterface & 0x01)){
						if(Dev->HostData->PriIde==NULL){
							//Set the current PCI Device attributes to LEGACY 
							Dev->Attrib|=EFI_PCI_IO_ATTRIBUTE_IDE_PRIMARY_IO;
							Dev->HostData->PriIde=Dev;
						} else {
							//set native mode bit since this Legacy IO space has been taken already
							pif++;
							pib |= 0x01;
						}
					} 
					
					//secondary Controller in LEGACY mode?
					if( !(Dev->Class.ProgInterface & 0x04) ){
						if(Dev->HostData->SecIde==NULL){
							//Set the current PCI Device attributes to LEGACY 
							Dev->Attrib|=EFI_PCI_IO_ATTRIBUTE_IDE_SECONDARY_IO;
							Dev->HostData->SecIde=Dev;
						} else {
							//set native mode bit since this Legacy IO space has been taken already
							pif++;
							pib |= 0x04;
						}
					} 
					if(pif){
						Status=SetIdeDevMode(Dev, 0,0, &pib);
						if(!EFI_ERROR(Status)) Dev->Class.ProgInterface = pib; 
 					}
				} else Dev->Capab&=(~(EFI_PCI_IO_ATTRIBUTE_IDE_SECONDARY_IO|EFI_PCI_IO_ATTRIBUTE_IDE_PRIMARY_IO));

				break;
		}//switch;
	}
	
	//device caps should not exsceed parent;
	if(Dev->Capab & EFI_PCI_IO_ATTRIBUTE_IO)
		Dev->Capab|=(EFI_PCI_IO_ATTRIBUTE_ISA_MOTHERBOARD_IO | EFI_PCI_IO_ATTRIBUTE_ISA_IO);
	else 
		Dev->Capab&=(~(EFI_PCI_IO_ATTRIBUTE_ISA_MOTHERBOARD_IO | EFI_PCI_IO_ATTRIBUTE_ISA_IO));

	pBS->RestoreTPL(OldTpl);
	PCI_TRACE((TRACE_PCI, "Supported Attributes -> 0x%lX\n", Dev->Capab));
	return Status;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   FindFirstBit(UINT64 Value, BOOLEAN Set, BOOLEAN Right2Left)
//
// Description: This function will find first bit Set or Reset 
// going Left to Right.
//
// Input:
//  UINT64  Value           Value to scan.
//  BOOLEAN Set             What condition to test
// Output:	
//  UINT8                   First bit set/reset
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
UINT8 FindFirstBit(UINT64 Value, BOOLEAN Set){
	UINT64	msk=1, iv=~Value;
	UINT8	bit;
//---------------------
	for(bit=0;bit<64;bit++){
		msk=Shl64(1,bit);		
		if(Set) {
			if( (Value & msk) == msk ) break;
		} else {
			if(( iv & msk ) == msk ) break;
		}
	}
	if(bit==64)	bit=0xFF;
	return bit;
}

///////////////////////////////////////////////////////////////
//   Capability pointers operation Including PCI Express...
///////////////////////////////////////////////////////////////

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	GetPciCapPtrs()
//
// Description: This function will collect information about PCI "Device"
// Capability Headers (Including PCI Express, Hot Plug and PCI-X/X2) and
// record them.
//
// Input:
//  PCI_DEV_INFO    *Device     Pointer to PCI Device Private Data structure.
//
// Output:	EFI_STATUS
//  EFI_SUCCESS             When everything is going on fine!
//  EFI_NOT_FOUND           When Device not present in the system.
//  EFI_OUT_OF_RESOURCES    When system runs out of resources.
//  EFI_DEVICE_ERROR        When driver fails access PCI Bus.
//  EFI_INVALID_PARAMETER   When some of the parameters - invalid.
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS GetPciCapPtrs(PCI_DEV_INFO *Device)
{
	PCI_CFG_ADDR		devaddr;		
	EFI_STATUS			Status=0;
	EFI_PCI_CAPABILITY_HDR	cp;	
	UINT16				sr;
//-------------------------------
	devaddr.ADDR=Device->Address.ADDR;
	devaddr.Addr.Register=0x06; //Status Register;
	//bit 4 in status register is set if device supports capabilities pointer
	Status=PciCfg16(Device->RbIo,devaddr,FALSE,&sr);
	ASSERT_EFI_ERROR(Status);
	if(EFI_ERROR(Status)) return Status;
	if(!(sr&0x10)) return Status; //no reason to continue - capabilities is not supported!
		
	//if device Supports Capabilityes
	cp.CAP_HDR=0;
	if(Device->Type==tPci2CrdBrg) devaddr.Addr.Register=EFI_PCI_CARDBUS_BRIDGE_CAPABILITY_PTR;	
	else  devaddr.Addr.Register=EFI_PCI_CAPABILITY_PTR;

	Status=PciCfg8(Device->RbIo,devaddr,FALSE,&cp.NextItemPtr);
	ASSERT_EFI_ERROR(Status);
	if(EFI_ERROR(Status)) return Status;

	//we got something here. 
	while(cp.NextItemPtr)
	{
		devaddr.Addr.Register=cp.NextItemPtr;

		Status=PciCfg16(Device->RbIo,devaddr,FALSE,&cp.CAP_HDR);
		ASSERT_EFI_ERROR(Status);
		if(cp.CapabilityID==PCI_CAP_ID_PMI) Device->PmiCapOffs=devaddr.Addr.Register;

//Enables PCI Express Handling only if PCI Express Base is Defined and !=0
#if PCI_EXPRESS_SUPPORT

		if(cp.CapabilityID==PCI_CAP_ID_PCIEXP){
			Device->PciExpress=MallocZ(sizeof(PCIE_DATA));
			ASSERT(Device->PciExpress);
			if(!Device->PciExpress) return EFI_OUT_OF_RESOURCES;
			
			//Save Current Offset of PCIE Std Compatibility Registers Block 
			Device->PciExpress->PcieOffs=devaddr.Addr.Register;
			Device->PciExpress->Owner=Device;
		}
#endif

#if HOTPLUG_SUPPORT
		if(cp.CapabilityID==PCI_CAP_ID_HOTPLUG){
			//we may process this controller as root HPC so check that.
			if(!Device->HotPlug){
				Device->HotPlug=MallocZ(sizeof(PCI_HPC_INFO));
				ASSERT(Device->HotPlug);
				if(!Device->HotPlug) return EFI_OUT_OF_RESOURCES;
			
				//Save Current Offset of PCIE Std Compatibility Registers Block 
				Device->HotPlug->HpcLocation->HpcDevicePath=Device->DevicePath;	
				Device->HotPlug->HpcLocation->HpcDevicePath=Device->DevicePath;	
				Device->HotPlug->HpcPciAddr.ADDR=Device->Address.ADDR;
				Device->HotPlug->HpbBridge=Device;
				Device->HotPlug->BusFound=TRUE;
				//For SHPC it must be initialized and enabled by hardware 
				Device->HotPlug->HpcState=EFI_HPC_STATE_INITIALIZED|EFI_HPC_STATE_ENABLED;
				Device->HotPlug->HpcOffs=devaddr.Addr.Register;
				Device->HotPlug->Owner=Device;
			}
		}
#endif

//this is for feautufe use if we will support BootTime hotplug events
#if PCI_X_SUPPORT
		if(cp.CapabilityID==PCI_CAP_ID_PCIX){

			Device->PciX=MallocZ(sizeof(PCIX_DATA));
			ASSERT(Device->PciX);
			if(!Device->PciX) return EFI_OUT_OF_RESOURCES;

			//fill out fields within PciX structure
			devaddr.Addr.Register=Device->PciX->PcixOffs+PCIX_DEV_STA_OFFSET;
			Status=PciCfg32(Device->RbIo, devaddr, FALSE, &Device->PciX->PcixDevStatus.DEV_STA);
			ASSERT_EFI_ERROR(Status);
			if(EFI_ERROR(Status)) return Status;

			devaddr.Addr.Register=Device->PciX->PcixOffs+PCIX_SEC_STA_OFFSET;
			Status=PciCfg16(Device->RbIo, devaddr, FALSE, &Device->PciX->PcixSecStatus.SEC_STA);
			ASSERT_EFI_ERROR(Status);
			if(EFI_ERROR(Status)) return Status;
	
			Device->PciX->PcixOffs=devaddr.Addr.Register;
			Device->PciX->Owner=Device;	

		}
#endif		
	}	
	return Status;
}

//----------------------------------------------------------------------------
//Enable PCI Express Handling only if PCI Express Base is Defined and !=0
#if PCI_EXPRESS_SUPPORT 
//////////////////////////////////////////////////////////////////////////////
//----------------------------------------------------------------------------
// PCI Express Helper Functions
//----------------------------------------------------------------------------
//////////////////////////////////////////////////////////////////////////////
EFI_STATUS PcieDoubleCheckCard(PCI_DEV_INFO *Brg, PCI_CFG_ADDR *DevAddr, UINT32 *VenDevId){
    EFI_STATUS          Status;
    PCI_CFG_ADDR        addr;
    PCIE_SLT_STA_REG    slts;
//    PCIE_LNK_STA_REG    lnks;
//    PCIE_DEV_STA_REG    devs;
//------------------------


    //Read PCIe.DEV_STA_REG;
    addr.ADDR=Brg->Address.ADDR;
/*    
    addr.Addr.Register=Brg->PciExpress->PcieOffs+PCIE_DEV_STA_OFFSET;
    Status=PciCfg16(Brg->RbIo, addr, FALSE, &devs.DEV_STA);
	ASSERT_EFI_ERROR(Status);
    
    //Read PCIe.LNK_STA_REG;
    addr.Addr.Register=Brg->PciExpress->PcieOffs+PCIE_LNK_STA_OFFSET;
    Status=PciCfg16(Brg->RbIo, addr, FALSE, &lnks.LNK_STA);
	ASSERT_EFI_ERROR(Status);
*/
    //Read PCIe.SLT_STA_REG;
    addr.Addr.Register=Brg->PciExpress->PcieOffs+PCIE_SLT_STA_OFFSET;
    Status=PciCfg16(Brg->RbIo, addr, FALSE, &slts.SLT_STA);
	ASSERT_EFI_ERROR(Status);

/*
    TRACE((-1, "\n!!!!!!DEV_STA[ 0x%X ].TrasactPend(5)=%d;\n",devs.DEV_STA, devs.TrasactPend));
    TRACE((-1, "!!!!!!LNK_STA[0x%X].LnkTraining(11)=%d;\n",lnks.LNK_STA, lnks.LnkTraining));
    TRACE((-1, "!!!!!!SLT_STA[%X].CardPresent(6)=%d;\n",slts.SLT_STA, slts.CardPresent));
    TRACE((-1, "!!!!!!for the BRIDGE @ [B%X|D%X|F%X];\n",Brg->Address.Addr.Bus,Brg->Address.Addr.Device, Brg->Address.Addr.Function));
    TRACE((-1, "!!!!!!VID/DID=%X of [B%X|D0|F0]\n",*VenDevId, addr.Addr.Bus));
*/

    //if we are here that means card did not come up first time...
    //so try to read it one more time, before taking some invasive actions.
    addr.ADDR = DevAddr->ADDR;
    addr.Addr.Register=0;

    //SOMETHING present there, but need some time to completely come up
    if(slts.CardPresent != 0  || slts.PresenceDet !=0 ){
        UINTN   i;
    //---------
        for(i=0; i<=gPciSetupData->LnkTrRetry; i++){

            Status=PciCfg32(Brg->RbIo, addr, FALSE, VenDevId);
            ASSERT_EFI_ERROR(Status);
            if( (*VenDevId) != 0xFFFFFFFF ) break;

            //Use same setup value for retry timeut and number
            pBS->Stall(gPciSetupData->LnkTrTimeout*100);
        }
//  TRACE((-1, "!!!!!!VID/DID=%X after %d retry (timeout=%d) \n",*VenDevId, i+1, gPciSetupData->LnkTrTimeout*100));
    } 

    //If nothing workeded just exit...
    return Status;
}

///////////////////////////////////////////////////////////////////////////////
//Exclude support fot PCIe GEN2 to save space in projects w/o PCIE_GEN2
#if PCI_EXPRESS_GEN2_SUPPORT


///////////////////////////////////////////////////////////////////////////////
//Exclude support fot PCIe GEN3 to save space in projects w/o PCIE_GEN3
#if PCI_EXPRESS_GEN3_SUPPORT //GEN3 support is a subset of GEN2 support!!!

EFI_STATUS Pcie3EqualizeLink(PCI_DEV_INFO *Device, BOOLEAN *LnkRetrain){
    EFI_STATUS          Status=EFI_SUCCESS;
	PCI_CFG_ADDR		addr;
    PCIE_LNK_CNT3_REG   LnkCnt3;
    PCIE_LNK_STA2_REG   LnkSta2;
//-----------------------------

    //If device don't have GEN 3 Cap Hdr, or link is operating on lell then 8.0 GT/s speed - just exit...
    if(Device->PciExpress->Pcie3==NULL) return EFI_SUCCESS;

    //Get LNK_STA2 regiser 
	addr.ADDR=Device->Address.ADDR;
    addr.Addr.Register=Device->PciExpress->PcieOffs+PCIE_LNK_STA2_OFFSET;
    Status=PciCfg16(Device->RbIo, addr, FALSE,&LnkSta2.LNK_STA2);
	ASSERT_EFI_ERROR(Status);

    //Display Content of the LNK_STA2 register.
    PCI_TRACE((TRACE_PCI," LNK_STA2-> [R=%X|EqReq=%X|EqP3=%X|EqP2=%X|EqP1=%X|EqCompl=%X|SelDeEmp=%X]\n",
        LnkSta2.Reserved,
        LnkSta2.EqRequest,
        LnkSta2.EqPhase3Ok,
        LnkSta2.EqPhase2Ok,
        LnkSta2.EqPhase1Ok,
        LnkSta2.EqComplete,
        LnkSta2.SelDeEmphasis));

    //Check if equalization was requested or we are about to enter lLNK training session...
    if(LnkSta2.EqRequest || *LnkRetrain){

        PCI_TRACE((TRACE_PCI," PciE3: Equalization for Device @ [B%X|D%X|F%X] LnkRetrain=%X Before\n",
            addr.Addr.Bus,addr.Addr.Device,addr.Addr.Function, *LnkRetrain));
        //read Lnk Control 3 register in Sec PCIe Ext Cap Header.
        addr.Addr.ExtendedRegister=Device->PciExpress->Pcie3->SecPcieCapOffs+PCIE_LNK_CNT3_OFFSET;    
        Status=PciCfg32(Device->RbIo, addr, FALSE,&LnkCnt3.LNK_CNT3);
	    ASSERT_EFI_ERROR(Status);

        //Set Prform Equalization bit and disable Equalization Request Interrupt, just in case.
        LnkCnt3.LnkEqReqIntEn=0;        
        LnkCnt3.PerformEqualiz=1;

        //Write it back into LNK_CNT3 register.
        Status=PciCfg32(Device->RbIo, addr, TRUE, &LnkCnt3.LNK_CNT3);
	    ASSERT_EFI_ERROR(Status);

        *LnkRetrain=TRUE;

        //Display Content of the LNK_CNT3 register.
        PCI_TRACE((TRACE_PCI," LNK_CNT3-> [R=%X|LnkEqReqIntEn=%X|DoEq=%X] LnkRetrain=%X After\n",
            LnkCnt3.Reserved,
            LnkCnt3.LnkEqReqIntEn,
            LnkCnt3.PerformEqualiz,
            *LnkRetrain));

    }
    return Status;
}


EFI_STATUS Pcie3GetEqualizationStatus(PCI_DEV_INFO *Device){
	PCI_CFG_ADDR		addr;
    PCIE_LNK_STA2_REG   LnkSta2;
    EFI_STATUS          Status=EFI_SUCCESS;
//-----------------------------

    //If device don't have GEN 3 Cap Hdr, or link is operating on lell then 8.0 GT/s speed - just exit...
    if(Device->PciExpress->Pcie3==NULL) return EFI_SUCCESS;

    //Get LNK_STA2 regiser 
	addr.ADDR=Device->Address.ADDR;
    addr.Addr.Register=Device->PciExpress->PcieOffs+PCIE_LNK_STA2_OFFSET;
    Status=PciCfg16(Device->RbIo, addr, FALSE,&LnkSta2.LNK_STA2);
	ASSERT_EFI_ERROR(Status);

    //Display Content of the LNK_STA2 register.
    PCI_TRACE((TRACE_PCI,"Pcie3-> Checking Equalization Status...\n LNK_STA2-> [R=%X|EqReq=%X|EqP3=%X|EqP2=%X|EqP1=%X|EqCompl=%X|SelDeEmp=%X]\n",
        LnkSta2.Reserved,
        LnkSta2.EqRequest,
        LnkSta2.EqPhase3Ok,
        LnkSta2.EqPhase2Ok,
        LnkSta2.EqPhase1Ok,
        LnkSta2.EqComplete,
        LnkSta2.SelDeEmphasis));

    //Check equalization sesults...
    if (LnkSta2.EqComplete) return EFI_SUCCESS;
    
    //Check if any of the equalization phases were completed...
    if(LnkSta2.LNK_STA2 & 0x1C) return EFI_NOT_AVAILABLE_YET;

    return EFI_DEVICE_ERROR;
}    

#endif //GEN3

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   Pcie2GetGen2Info()
//
// Description: This function will collect information about PCIE GEN2 Device
// and initialize PCIE2_DATA structure based on information collected.
//
// Input:
//  PCI_DEV_INFO    *Device Pointer to PCI Device Private Data structure.
//
// Output:	EFI_STATUS
//  EFI_SUCCESS             When everything is going on fine!
//  EFI_DEVICE_ERROR        When driver fails access PCI Bus.
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS Pcie2GetGen2Info(PCI_DEV_INFO *Device){
    EFI_STATUS          Status=EFI_SUCCESS;
	PCI_CFG_ADDR		addr;
//-----------------------------
	addr.ADDR=Device->Address.ADDR;
    //PCI_TRACE((TRACE_PCI," PciE2: Device @ [B%X|D%X|F%X] is PCIE GEN2 Device:\n",
    //        addr.Addr.Bus,addr.Addr.Device,addr.Addr.Function));

    //Get PCI Express Device CAP2 - 32 bit
    addr.Addr.Register=Device->PciExpress->PcieOffs+PCIE_DEV_CAP2_OFFSET;
    Status=PciCfg32(Device->RbIo, addr, FALSE,&Device->PciExpress->Pcie2->DeviceCap2.DEV_CAP2);
	ASSERT_EFI_ERROR(Status);

    PCI_TRACE((TRACE_PCI," DEV_CAP2-> [R2=%X|MEEP=%X|EETP=%X|EFF=%X|R1=%X|TPH=%X|LTR=%X|NRP=%X|C128=%X|AtC64=%X|AtC32=%X|AtR=%X|Ari=%d|CTD=%X|CmTO=%X]\n",
        Device->PciExpress->Pcie2->DeviceCap2.Reserved2,
        Device->PciExpress->Pcie2->DeviceCap2.MaxEndEndPrefix,
        Device->PciExpress->Pcie2->DeviceCap2.EndEndTlpPrefix,
        Device->PciExpress->Pcie2->DeviceCap2.ExtFmtField,
        Device->PciExpress->Pcie2->DeviceCap2.Reserved1,
        Device->PciExpress->Pcie2->DeviceCap2.TphCompleter,
        Device->PciExpress->Pcie2->DeviceCap2.LtrMechanism,
        Device->PciExpress->Pcie2->DeviceCap2.NoRoPrPrPassing,
        Device->PciExpress->Pcie2->DeviceCap2.Cas128Completer,
        Device->PciExpress->Pcie2->DeviceCap2.AtomicOpCompl64,
        Device->PciExpress->Pcie2->DeviceCap2.AtomicOpCompl32,
        Device->PciExpress->Pcie2->DeviceCap2.AtomicOpRouting,
        Device->PciExpress->Pcie2->DeviceCap2.AriForwarding,
        Device->PciExpress->Pcie2->DeviceCap2.ComplToutDisable,
        Device->PciExpress->Pcie2->DeviceCap2.ComplToutRanges));

    //Get PCI Express Link CAP2 - 32 bit
    addr.Addr.Register=Device->PciExpress->PcieOffs+PCIE_LNK_CAP2_OFFSET;
    Status=PciCfg32(Device->RbIo, addr, FALSE,&Device->PciExpress->Pcie2->LinkCap2.LNK_CAP2);
	ASSERT_EFI_ERROR(Status);
    
    if(Device->PciExpress->PcieCap.SlotImpl){
        //Get PCI Express Link SLOT2 - 32 bit
        addr.Addr.Register=Device->PciExpress->PcieOffs+PCIE_SLT_CAP2_OFFSET;
        Status=PciCfg32(Device->RbIo, addr, FALSE,&Device->PciExpress->Pcie2->SlotCap2.SLT_CAP2);
	    ASSERT_EFI_ERROR(Status);
    }

#if PCI_EXPRESS_GEN3_SUPPORT 
    //Do some additional checks if device has GEN 3 Secondary PCIe Cap Header.
    //At that point if we have discovered Sec PCIe Cap HDR Defice->PciExpress->Pcie3 must be initializad.
    if(Device->PciExpress->Pcie3 != NULL){


        //Update Speed encoding it is defined differently for devices Supporting V3.0 spec.
                
        Device->PciExpress->Pcie3->MaxLanesCount=Device->PciExpress->LinkCap.MaxLnkWidth;

        //Display first LNK_CAP2_REG
        PCI_TRACE((TRACE_PCI,"PCIe3 -> Device is PCIe v3.0 Compliant!!! LNK_CAP2 present!!! \n LNK_CAP2-> [R2=%X|CrossL=%X|SuppLnkSpeedVect=%X|R1=%X]; LANE_ERR_STA->[%X]; MaxLanes=%X\n",
            Device->PciExpress->Pcie2->LinkCap2.Reserved2,
            Device->PciExpress->Pcie2->LinkCap2.CrossLnk,
            Device->PciExpress->Pcie2->LinkCap2.SuppLnkSpeeds,
            Device->PciExpress->Pcie2->LinkCap2.Reserved1,
            Device->PciExpress->Pcie3->LaneErrSts,
            Device->PciExpress->Pcie3->MaxLanesCount));

    }
#endif

    Device->PciExpress->Pcie2->Owner=Device;

    return Status;
}


//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   Pcie2EnableAri()
//
// Description: This function will Enable ARI Forwarding in DownSream Port of 
// the device passed if 
//  1.Device referenced is an ARI device;
//  2.Parenting Bridge supports ARI Forwarding. 
//  3.ARI Firvarding Setup Question Set to "Enabled"
//
// Input:
//  PCI_DEV_INFO    *Device Pointer to PCI Device Private Data structure.
//
// Output:	EFI_STATUS
//  EFI_SUCCESS             When everything is going on fine!
//  EFI_UNSUPPORTED         When Device or Parenting Bridge does not support ARI
//  EFI_DEVICE_ERROR        When driver fails access PCI Bus.
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS Pcie2EnableAri(PCI_DEV_INFO *Device){
    EFI_STATUS          Status=EFI_SUCCESS;
    PCI_DEV_INFO        *brg;
	PCI_CFG_ADDR		addr;
	PCIE_DEV_CNT2_REG	dcnt2;
//-----------------------------------    
    //Setup Don't have it enabled
    if(gPciSetupData->AriFwd == 0) {
        PCI_TRACE((TRACE_PCI," -> Setup=%d", gPciSetupData->AriFwd));
        return EFI_UNSUPPORTED; 
    }
    
    if(Device->Type != tPciDevice) {
        PCI_TRACE((TRACE_PCI," -> not tDevice Type", gPciSetupData->AriFwd));
        return EFI_UNSUPPORTED; 
    }
    
    if(Device->PciExpress == NULL) {
        PCI_TRACE((TRACE_PCI," -> not PCIe Device", gPciSetupData->AriFwd));
        return EFI_UNSUPPORTED; 
    }

    //Device don't have ARI Ext Cap
    if(Device->PciExpress->AriData==NULL){
        PCI_TRACE((TRACE_PCI," -> non-ARI Device"));
        return EFI_UNSUPPORTED;
    }
    //If we are here - device is an ARI Device. Now check if Parenting Bridge can do it...
    brg=Device->ParentBrg;
    //Check if Parenting Brg is Gen 2 device
    if(brg->PciExpress->Pcie2==NULL){
        PCI_TRACE((TRACE_PCI," -> ParentBrg non-GEN2"));
        return EFI_UNSUPPORTED;
    }

    //Check if bridge can do ARI Forvarding
    if(brg->PciExpress->Pcie2->DeviceCap2.AriForwarding==0){
        PCI_TRACE((TRACE_PCI," -> ParentBrg.Cap.AriFwd=0"));
        return EFI_UNSUPPORTED;
    }

    //Now check if this bridge has ARI Forwarding Enabled allready
    if(brg->PciExpress->Pcie2->AriEnabled==TRUE){
        //Set Device ARI Falg        
        Device->PciExpress->Pcie2->AriEnabled=brg->PciExpress->Pcie2->AriEnabled;
        PCI_TRACE((TRACE_PCI," -> Parent Bridge AriEnabled=1"));
        return EFI_SUCCESS;
    }

    //At that Point we must enable ARI.
	addr.ADDR=brg->Address.ADDR;
    addr.Addr.Register=brg->PciExpress->PcieOffs+PCIE_DEV_CNT2_OFFSET;
    Status=PciCfg16(brg->RbIo, addr, FALSE,&dcnt2.DEV_CNT2);
    ASSERT_EFI_ERROR(Status);
    if(EFI_ERROR(Status)) return Status;


    dcnt2.AriForwarding=TRUE;
    PCI_TRACE((TRACE_PCI,"  ARI -> Enabling ARI for Parent Bridge!"));
    Status=PciCfg16(Device->RbIo, addr, TRUE,&dcnt2.DEV_CNT2);
    ASSERT_EFI_ERROR(Status);


    if(EFI_ERROR(Status)) return Status;

    Device->PciExpress->Pcie2->AriEnabled=(BOOLEAN)dcnt2.AriForwarding;
    brg->PciExpress->Pcie2->AriEnabled=(BOOLEAN)dcnt2.AriForwarding;        
    return Status;
}


//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   Pcie2CheckAri()
//
// Description: This function will Enable ARI Forwarding in DownSream Port of 
// the device passed if 
//  1.Device referenced is an ARI device;
//  2.Parenting Bridge supports ARI Forwarding. 
//  3.ARI Firvarding Setup Question Set to "Enabled"
// 
// Input:
//  PCI_DEV_INFO    *Device     Pointer to PCI Device Private Data structure.
//  BOOLEAN         *MultiFunc  Pointer to a Flag to modify if Device is MF Device 
//  BOOLEAN         *AriEnabled Pointer to a Flag to modify if this function was able to ENABLE ARI. 
//
// Output:	EFI_STATUS
//  EFI_SUCCESS             When everything is going on fine!
//  EFI_DEVICE_ERROR        When driver fails access PCI Bus.
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS Pcie2CheckAri(PCI_DEV_INFO *Device, BOOLEAN *MultiFunc, BOOLEAN *AriEnabled){
    EFI_STATUS  Status;
//--------------------
    PCI_TRACE((TRACE_PCI," PciE2: Checking ARI @ [B%X|D%X|F%X]:",
            Device->Address.Addr.Bus,Device->Address.Addr.Device,Device->Address.Addr.Function));

    Status=Pcie2EnableAri(Device);
    PCI_TRACE((TRACE_PCI," Status=%r\n",Status));

    if((!EFI_ERROR(Status)) && 
       (Device->PciExpress->AriData!=NULL) &&
       (Device->PciExpress->Pcie2->AriEnabled==TRUE)) 
    {
        *MultiFunc=TRUE;
        *AriEnabled=TRUE;
    } else {
        if(Status==EFI_UNSUPPORTED){
            *AriEnabled=FALSE;    
            Status=EFI_SUCCESS;
        } 
    }

    //PCI_TRACE((TRACE_PCI," AriEn=%d %r\n\n",*AriEnabled, Status));

    return Status;
}



//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   Pcie2SetLnkProperties()
//
// Description: This function will Select values for Link Control2 register on 
// both sides of the LINK based on Setup Settings and hardware capabilities.
// 
// Input:
//  PCI_DEV_INFO        *DnStreamPort   Pointer to PCI Device Private Data of Downstream Port of the link.
//  PCIE_LNK_CNT2_REG   *DnLnkCnt2      Pointer to the LNK_CNT2 Reg of the Downstream Port of the link.
//  PCI_DEV_INFO        *UpStreamPort   Pointer to PCI Device Private Data of Upwnstream Port of the link.
//  PCIE_LNK_CNT2_REG   *UpLnkCnt2      Pointer to the LNK_CNT2 Reg of the Downstream Port of the link. 
//  BOOLEAN             *LinkHotResetRequired Flag to modify if Link will need HOT RESET after programming.
//
// Output:	EFI_STATUS
//  EFI_SUCCESS             When everything is going on fine!
//  EFI_DEVICE_ERROR        When driver fails access PCI Bus.
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS Pcie2SetLnkProperties(PCI_DEV_INFO           *DnStreamPort, 
                                 PCIE_LNK_CNT2_REG      *DnLnkCnt2, 
                                 PCI_DEV_INFO           *UpStreamPort,
                                 PCIE_LNK_CNT2_REG      *UpLnkCnt2, 
                                 BOOLEAN                *LinkHotResetRequired,
                                 BOOLEAN                *LinkRetrainRequired  )    
{
    EFI_STATUS          Status;
    PCIE_LNK_STA_REG    dnls, upls; //link status reg content of up and down side of the link
	PCI_CFG_ADDR		addr;
    UINT16              ls, maxls, curls;//link speed variables
//------------------------------

    PCI_TRACE((TRACE_PCI,"PciE2: Pcie2SetLnkProperties() ENTRY:\n"));

    //Get DownStream Port Properties
    addr.ADDR=DnStreamPort->Address.ADDR;

    PCI_TRACE((TRACE_PCI," DN STREAM PORT -> [B%X|D%X|F%X] <--> [B%X|D%X|F%X] <- UP STREAM PORT\n",
            DnStreamPort->Address.Addr.Bus,DnStreamPort->Address.Addr.Device, DnStreamPort->Address.Addr.Function,
            UpStreamPort->Address.Addr.Bus,UpStreamPort->Address.Addr.Device, UpStreamPort->Address.Addr.Function));

    addr.Addr.Register=DnStreamPort->PciExpress->PcieOffs+PCIE_LNK_CNT2_OFFSET;
    Status=PciCfg16(DnStreamPort->RbIo,addr,FALSE, &DnLnkCnt2->LNK_CNT2);
    ASSERT_EFI_ERROR(Status);
    if(EFI_ERROR(Status)) return Status;

    PCI_TRACE((TRACE_PCI," LNK_CNT2-> [CmDe=%X|CmSOS=%X|ECm=%X|TrM=%X|SlDe=%X|AuSp=%X|EnCm=%X|TLS=%X]\n",
                DnLnkCnt2->ComplDeEmphasis,
                DnLnkCnt2->ComplianceSos,
                DnLnkCnt2->EnterModCompl,
                DnLnkCnt2->TrsMargin,
                DnLnkCnt2->SelDeEmphasis,
                DnLnkCnt2->HwAutoSpeedDis,
                DnLnkCnt2->EnterCompliance,
                DnLnkCnt2->TargetLnkSpeed));


    addr.Addr.Register=DnStreamPort->PciExpress->PcieOffs+PCIE_LNK_STA_OFFSET;
    Status=PciCfg16(DnStreamPort->RbIo,addr,FALSE, &dnls.LNK_STA);
    ASSERT_EFI_ERROR(Status);
    if(EFI_ERROR(Status)) return Status;

    //Get UpStream Stream Port Properties
    addr.ADDR=UpStreamPort->Address.ADDR;

    //PCI_TRACE((TRACE_PCI," UP STREAM PORT @ [B%X|D%X|F%X]:\n",
    //        addr.Addr.Bus,addr.Addr.Device, addr.Addr.Function));

    addr.Addr.Register=UpStreamPort->PciExpress->PcieOffs+PCIE_LNK_CNT2_OFFSET;
    Status=PciCfg16(UpStreamPort->RbIo,addr,FALSE, &UpLnkCnt2->LNK_CNT2);
    ASSERT_EFI_ERROR(Status);
    if(EFI_ERROR(Status)) return Status;

    PCI_TRACE((TRACE_PCI," LNK_CNT2-> [CmDe=%X|CmSOS=%X|ECm=%X|TrM=%X|SlDe=%X|AuSp=%X|EnCm=%X|TLS=%X]\n    ....... UPDATINNG .......\n",
                UpLnkCnt2->ComplDeEmphasis,
                UpLnkCnt2->ComplianceSos,
                UpLnkCnt2->EnterModCompl,
                UpLnkCnt2->TrsMargin,
                UpLnkCnt2->SelDeEmphasis,
                UpLnkCnt2->HwAutoSpeedDis,
                UpLnkCnt2->EnterCompliance,
                UpLnkCnt2->TargetLnkSpeed));
    
    //Get Lnk Status Content... 
    addr.Addr.Register=UpStreamPort->PciExpress->PcieOffs+PCIE_LNK_STA_OFFSET;
    Status=PciCfg16(UpStreamPort->RbIo,addr,FALSE, &upls.LNK_STA);
    ASSERT_EFI_ERROR(Status);
    if(EFI_ERROR(Status)) return Status;


    //Check link Speed selected in Setup and calculate applcable Link speed...
    //get max possible link speed
    maxls=DnStreamPort->PciExpress->LinkCap.MaxLnkSpeed;
    if(maxls>UpStreamPort->PciExpress->LinkCap.MaxLnkSpeed) maxls=UpStreamPort->PciExpress->LinkCap.MaxLnkSpeed;

    //get the current speed of the link...
    curls=DnStreamPort->PciExpress->CurrLnkSpeed;
    //must be the same on both sides of the link
    ASSERT(curls==UpStreamPort->PciExpress->CurrLnkSpeed);

	if(maxls>=PCIE_LINK_SPEED_80G){
		if(DnStreamPort->PciExpress->Pcie3==NULL || UpStreamPort->PciExpress->Pcie3==NULL) 
				maxls=PCIE_LINK_SPEED_50G;
	}

    //Check Link Speed setup options... 
    //AUTO==55
    ls=curls;
    if(gPciSetupData->LnkSpeed==55)ls=maxls;
    
    //Force 5.0GT/s == 2
    if(gPciSetupData->LnkSpeed==2){
        //check if it is supported
        if(DnStreamPort->PciExpress->Pcie2->LinkCap2.SuppLnkSpeeds!=0){
            //if device is compatible with V3.0 spec it must report supported speeds 
            if(DnStreamPort->PciExpress->Pcie2->LinkCap2.SuppLnkSpeeds & PCIE_LINK_SPEED_VECT_50G) ls=PCIE_LINK_SPEED_50G;
        } else {
            //for devices compliand to spec v 2.1 check maxls value 
            if(maxls>=PCIE_LINK_SPEED_50G) ls=PCIE_LINK_SPEED_50G;
        }       
    }

    //Force 2.5GT/s == 1
    if(gPciSetupData->LnkSpeed==1){
        //check if it is supported
        if(DnStreamPort->PciExpress->Pcie2->LinkCap2.SuppLnkSpeeds!=0){
            //if device is compatible with V3.0 spec it must report supported speeds 
            if(DnStreamPort->PciExpress->Pcie2->LinkCap2.SuppLnkSpeeds & PCIE_LINK_SPEED_VECT_25G)ls=PCIE_LINK_SPEED_25G;
        } else {
            //for devices compliand to spec v 2.1 check maxls value 
            if(maxls>=PCIE_LINK_SPEED_25G) ls=PCIE_LINK_SPEED_25G;
        }       
    }

    PCI_TRACE((TRACE_PCI," LNK SPEED SETTINGS: MaxLS=%X; CurrentLS=%X; SelectedLS=%X; Setup=%d\n",
            maxls,curls,ls, gPciSetupData->LnkSpeed ));

    //Call porting hook to override link speed settings.
    Status=PciPortOemSetLnkSpeed(DnStreamPort, (UINT8*)&ls, (UINT8)DnStreamPort->PciExpress->Pcie2->LinkCap2.SuppLnkSpeeds);
    //one more time for Upstreamport
    Status=PciPortOemSetLnkSpeed(UpStreamPort, (UINT8*)&ls, (UINT8)UpStreamPort->PciExpress->Pcie2->LinkCap2.SuppLnkSpeeds);

    //now check if curls different from ls 
    if(ls<curls){
//        DnLnkCnt2->EnterCompliance=TRUE;
//        UpLnkCnt2->EnterCompliance=TRUE;
//        *LinkHotResetRequired=TRUE;
        *LinkRetrainRequired=TRUE;
    } 
    
    if(ls>curls){
        *LinkRetrainRequired=TRUE;
//        *LinkHotResetRequired=TRUE;
    }

    //Set selected speed on both sides of the link
    DnLnkCnt2->TargetLnkSpeed=ls;
    UpLnkCnt2->TargetLnkSpeed=ls;

    //Check;  HwAutoSpeedDis; HwAutoWidth settings
    DnLnkCnt2->HwAutoSpeedDis=gPciSetupData->HwAutoSpeed;
    UpLnkCnt2->HwAutoSpeedDis=gPciSetupData->HwAutoSpeed;

    PCI_TRACE((TRACE_PCI," LNK_CNT2-> [CmDe=%X|CmSOS=%X|ECm=%X|TrM=%X|SlDe=%X|AuSp=%X|EnCm=%X|TLS=%X]\n",
                DnLnkCnt2->ComplDeEmphasis,
                DnLnkCnt2->ComplianceSos,
                DnLnkCnt2->EnterModCompl,
                DnLnkCnt2->TrsMargin,
                DnLnkCnt2->SelDeEmphasis,
                DnLnkCnt2->HwAutoSpeedDis,
                DnLnkCnt2->EnterCompliance,
                DnLnkCnt2->TargetLnkSpeed));

    PCI_TRACE((TRACE_PCI," LNK_CNT2-> [CmDe=%X|CmSOS=%X|ECm=%X|TrM=%X|SlDe=%X|AuSp=%X|EnCm=%X|TLS=%X]\n\n",
                UpLnkCnt2->ComplDeEmphasis,
                UpLnkCnt2->ComplianceSos,
                UpLnkCnt2->EnterModCompl,
                UpLnkCnt2->TrsMargin,
                UpLnkCnt2->SelDeEmphasis,
                UpLnkCnt2->HwAutoSpeedDis,
                UpLnkCnt2->EnterCompliance,
                UpLnkCnt2->TargetLnkSpeed));


#if PCI_EXPRESS_GEN3_SUPPORT
	if(DnStreamPort->PciExpress->Pcie3!=NULL && UpStreamPort->PciExpress->Pcie3!=NULL){

    if(ls >=PCIE_LINK_SPEED_80G) {
        Status=Pcie3EqualizeLink(DnStreamPort, LinkRetrainRequired);
        ASSERT_EFI_ERROR(Status);
        if(EFI_ERROR(Status)) return Status;
        //Equalize link must be set for Upstream Port if it has closslink 
        if(UpStreamPort->PciExpress->Pcie2->LinkCap2.CrossLnk){
            Status=Pcie3EqualizeLink(UpStreamPort, LinkRetrainRequired);
            ASSERT_EFI_ERROR(Status);
        	}
		}
    }
#endif

    return Status;
}



//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   Pcie2SelectComplTimeOut()
//
// Description: This function will select appropriate Completion Timeout range
// from supported by the device.
// 
// Input:
//  UINT32      Support     Supported by Device Completion Timeout ranges.
//  BOOLEAN     Short       A Flag to Indicate wahat type of ranges to select Biggest or Smallest 
//
// Output:	UINT16
//  Value to be programmed in DEV_CNT2 Register.
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
UINT16 Pcie2SelectComplTimeOut(UINT32 Support, BOOLEAN Short){ 
    //Completion Timeout Programability is not supported by HW.
    if(Support==0) return 0;

    if(Short){
        //It is strongly recommended that the Completion Timeout
        //mechanism not expire in less than 10 ms

        //Values available if Range A (50 mks to 10 ms) programmability range is supported:
        // 0001b 50 mks to 100 mks; 0010b; 1 ms to 10 ms
        if(Support & PCIE_CAP2_RANGE_A) return 0x2;
      
        //Values available if Range B (10 ms to 250 ms) programmability range is supported:
        // 0101b 16 ms to 55 ms; 0110b 65 ms to 210 ms
        if(Support & PCIE_CAP2_RANGE_B) return 0x5;

        //Values available if Range C (250 ms to 4 s) programmability range is supported:
        // 1001b 260 ms to 900 ms; 1010b 1 s to 3.5 s
        if(Support & PCIE_CAP2_RANGE_C) return 0x9;

        //Values available if the Range D (4 s to 64 s) programmability range is supported:
        // 1101b 4 s to 13 s; 1110b 17 s to 64 s
        if(Support & PCIE_CAP2_RANGE_D) return 0xD;
    
    } else {
        //Values available if the Range D (4 s to 64 s) programmability range is supported:
        // 1101b 4 s to 13 s; 1110b 17 s to 64 s
        if(Support & PCIE_CAP2_RANGE_D) return 0xE;

        //Values available if Range C (250 ms to 4 s) programmability range is supported:
        // 1001b 260 ms to 900 ms; 1010b 1 s to 3.5 s
        if(Support & PCIE_CAP2_RANGE_C) return 0xA;

        //Values available if Range B (10 ms to 250 ms) programmability range is supported:
        // 0101b 16 ms to 55 ms; 0110b 65 ms to 210 ms
        if(Support & PCIE_CAP2_RANGE_B) return 0x6;

        //Values available if Range A (50 mks to 10 ms) programmability range is supported:
        // 0001b 50 mks to 100 mks; 0010b; 1 ms to 10 ms
        if(Support & PCIE_CAP2_RANGE_A) return 0x2;
    }
    return 0;
}


//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   Pcie2SetDevProperties()
//
// Description: This function will Select values for DEVICE CCONTROL2 register 
// based on Setup Settings and hardware capabilities.
// 
// Input:
//  PCI_DEV_INFO        *DnStreamPort   Pointer to PCI Device Private Data of Downstream Port of the link.
//
// Output:	EFI_STATUS
//  EFI_SUCCESS             When everything is going on fine!
//  EFI_DEVICE_ERROR        When driver fails access PCI Bus.
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS Pcie2SetDevProperties(PCI_DEV_INFO *Device){
    EFI_STATUS          Status;
	PCI_CFG_ADDR		addr;
    PCIE_DEV_CNT2_REG   dcnt2;
//------------------------------

    //Get Device Properties
    addr.ADDR=Device->Address.ADDR;

    PCI_TRACE((TRACE_PCI,"PciE2: Pcie2SetDevProperties() Device @ [B%X|D%X|F%X] ENTRY:\n",
            addr.Addr.Bus,addr.Addr.Device, addr.Addr.Function));

    if (Device->PciExpress == NULL)
        return EFI_SUCCESS;

    addr.Addr.Register=Device->PciExpress->PcieOffs+PCIE_DEV_CNT2_OFFSET;
    Status=PciCfg16(Device->RbIo,addr, FALSE, &dcnt2.DEV_CNT2);
    ASSERT_EFI_ERROR(Status);
    if(EFI_ERROR(Status)) return Status;

    PCI_TRACE((TRACE_PCI," DEV_CNT2-> [EEPrB=%X|R=%X|LTR=%X|IDOCm=%X|IDORq=%X|AtEgB=%X|AtRq=%X|ARI=%X|CToD=%X|CTo=%X]\n    ....... UPDATINNG .......\n",
                dcnt2.EndEndTlpBlk,
                dcnt2.Reserved,
                dcnt2.LtrEn,
                dcnt2.IdoComplEn,
                dcnt2.IdoRequestEn,
                dcnt2.AtomicOpEgresBlk,
                dcnt2.AtomicOpRequer,
                dcnt2.AriForwarding,
                dcnt2.ComplToutDisable,
                dcnt2.ComplToutRanges));

    //Now check setup settingds and apply it. But do't touch ARI Forwarding it was updated earlier.
    dcnt2.EndEndTlpBlk=gPciSetupData->E2ETlpPrBlk;
    dcnt2.LtrEn=gPciSetupData->LtrReport;
    dcnt2.IdoComplEn=gPciSetupData->IDOCompl;
    dcnt2.IdoRequestEn=gPciSetupData->IDOReq;
    dcnt2.AtomicOpEgresBlk=gPciSetupData->AtomOpEgressBlk;
    dcnt2.AtomicOpRequer=gPciSetupData->AtomOpReq;

    //Now check what ompletion Timeout ranges to select?
    dcnt2.ComplToutDisable=FALSE;
    dcnt2.ComplToutRanges=0; //set to default

    //In Setup 0=Disable;0x55=SHORT; 0xAA=LONG; 0xFF=DEFAULT 
    if(gPciSetupData->ComplTimeOut == 0) dcnt2.ComplToutDisable=TRUE;
    else {
        if(gPciSetupData->ComplTimeOut == 0xFF) dcnt2.ComplToutRanges=0;
        else{ 
            //use SHORT timeout srom supported ranges option.
            if(gPciSetupData->ComplTimeOut == 0x55) 
                dcnt2.ComplToutRanges=Pcie2SelectComplTimeOut(Device->PciExpress->Pcie2->DeviceCap2.ComplToutRanges, TRUE); 
            //use LONG timeout srom supported ranges option.
            else 
                dcnt2.ComplToutRanges=Pcie2SelectComplTimeOut(Device->PciExpress->Pcie2->DeviceCap2.ComplToutRanges, FALSE); 
        }
    }
    

    Status=PciCfg16(Device->RbIo,addr, TRUE, &dcnt2.DEV_CNT2);

    PCI_TRACE((TRACE_PCI," DEV_CNT2-> [EEPrB=%X|R=%X|LTR=%X|IDOCm=%X|IDORq=%X|AtEgB=%X|AtRq=%X|ARI=%X|CToD=%X|CTo=%X]\n\n",
                dcnt2.EndEndTlpBlk,
                dcnt2.Reserved,
                dcnt2.LtrEn,
                dcnt2.IdoComplEn,
                dcnt2.IdoRequestEn,
                dcnt2.AtomicOpEgresBlk,
                dcnt2.AtomicOpRequer,
                dcnt2.AriForwarding,
                dcnt2.ComplToutDisable,
                dcnt2.ComplToutRanges));
//    PCI_TRACE((TRACE_PCI,"Status = %r.\n",Status));

    ASSERT_EFI_ERROR(Status);
    return Status;
}










#endif
//GEN 2 Helper Functions END
///////////////////////////////////////////////////////////////////////////////


//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   PcieUpdateClockPm()
//
// Description: This function will update Device's referenced as "Func0" 
// Clock Power Management based on Setup Settings and hardware capabilities.
//
// Input:
//  PCI_DEV_INFO    *Func0    Pointer to PCI Device Private Data structure.
//  CNT_REG         *LnkCnt   Pointer to the Device's LNK_CNT register data.
//
// Output:	NOTHING
//
// NOTE: Must be called only for PCI Express devices (Device->PciExpress!=NULL)
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID PcieUpdateClockPm(PCI_DEV_INFO *Func0, PCIE_LNK_CNT_REG *LnkCnt){
    UINTN           i;
    PCI_DEV_INFO    *dev;
//------------------------
    //Check if Clock PM was set for F0 than we need not to scam caps of the other devices.
    if(LnkCnt->ClockPm == FALSE) return; 
    //we will come here if we get a multifunction NON-ARI device and Device Points @ Function 0    
    //"LnkCnt" has parameters filled in calculated for Func0 of a MF device.
    //Func0->DevFunc[] includes all other functions except Func 0;
    for(i=0; i<Func0->FuncCount; i++){
        dev=Func0->DevFunc[i];
        //For a non-ARI multi-Function device, power-managementconfiguration
        //software must only Set this bit if all Functions of
        //the multi-Function device indicate a 1b in the Clock Power
        //Management bit of the Link Capabilities register. The
        //component is permitted to use the CLKREQ# signal to power
        //manage Link clock only if this bit is Set for all Functions.

        //For ARI Devices, Clock Power Management is enabled solely by
        //the setting in Function 0. The settings in the other Functions
        //always return whatever value software programmed for each,
        //but otherwise are ignored by the component.
        if(dev->PciExpress->LinkCap.ClockPm == FALSE) {
            LnkCnt->ClockPm=FALSE;
            return;
        }
    }    
}



//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   PcieDisableLink()
//
// Description: This function will Disable Link of DNSTREAM port referenced as 
// "Device" based on Setup Settings and hardware STATUS. Used to disable "EMPTY"
// links to save some POWER or "Force" LINK to Disable state if Link can not be 
// trained correctly. 
//
// Input: 
//  PCI_DEV_INFO    *Device    Pointer to PCI Device Private Data structure.
//  BOOLEAN         Force      Flag to indicate to disable link unconditionally.
//
// Output:	EFI_STATUS
//  EFI_SUCCESS             When everything is going on fine!
//  EFI_DEVICE_ERROR        When driver fails access PCI Bus.
//
// NOTE: Must be called only for PCI Express devices (Device->PciExpress!=NULL)
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS PcieDisableLink(PCI_DEV_INFO *Device, BOOLEAN Force){
    EFI_STATUS          Status=0;
	PCI_CFG_ADDR		addr;
    PCIE_LNK_CNT_REG    lcnt;    
    BOOLEAN             val;
//------------------------------------------

    //Get Device Link Control Register
    addr.ADDR=Device->Address.ADDR;
    addr.Addr.Register=Device->PciExpress->PcieOffs+PCIE_LNK_CNT_OFFSET;

    Status=PciCfg16(Device->RbIo, addr, FALSE, &lcnt.LNK_CNT);
    ASSERT_EFI_ERROR(Status);
    
    if(Force)val=TRUE;
    else val=gPciSetupData->LnkDisable;

    //Program Link only if it different from what we have. 
    if((UINT8)lcnt.LnkDisable!=val){
        lcnt.LnkDisable=val;
        Status=PciCfg16(Device->RbIo, addr, TRUE, &lcnt.LNK_CNT);
        ASSERT_EFI_ERROR(Status);
    }

    return Status;
}


//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   PcieProgramLink()
//
// Description: This function will Program Link with provided VALUEs
// trained correctly. 
//
// Input: 
//  PCI_DEV_INFO    *Device    Pointer to PCI Device Private Data structure.
//  UINT16          Data       Value to put in LNK_CNT register
//  BOOLEAN         Reg2       Flag to select LNK_CNT or LNK_CNT2 register.
//
// Output:	EFI_STATUS
//  EFI_SUCCESS             When everything is going on fine!
//  EFI_DEVICE_ERROR        When driver fails access PCI Bus.
//
// NOTE: Must be called only for PCI Express devices (Device->PciExpress!=NULL)
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS PcieProgramLink(PCI_DEV_INFO *Device, UINT16 Data, BOOLEAN Reg2){
    EFI_STATUS          Status=0;
	PCI_CFG_ADDR		addr;
//------------------------------------------

    //Get DownStream Port Properties
    addr.ADDR=Device->Address.ADDR;
    if(Reg2)addr.Addr.Register=Device->PciExpress->PcieOffs+PCIE_LNK_CNT2_OFFSET;
    else addr.Addr.Register=Device->PciExpress->PcieOffs+PCIE_LNK_CNT_OFFSET;

    Status=PciCfg16(Device->RbIo, addr, TRUE, &Data);
    ASSERT_EFI_ERROR(Status);
    
    return Status;

}


//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   PcieResetLink()
//
// Description: This function will issue HOT RESET on a LINK referenced by "Device". 
//
// Input: 
//  PCI_DEV_INFO    *Device    Pointer to PCI Device Private Data structure.
//
// Output:	EFI_STATUS
//  EFI_SUCCESS             When everything is going on fine!
//  EFI_DEVICE_ERROR        When driver fails access PCI Bus.
//
// NOTE: Must be called only for PCI Express devices (Device->PciExpress!=NULL)
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS PcieResetLink(PCI_DEV_INFO *Device, UINT8 LnkSpeed){
    EFI_STATUS          Status=0;
	PCI_CFG_ADDR		addr;
    PCI_BRG_CNT_REG     bcnt;
    BOOLEAN             lnkrst=TRUE;
//--------------------------------
    //For any Root or Switch Downstream Port, setting the Secondary Bus Reset bit of the Bridge
    //Control register associated with the Port must cause a hot reset to be sent (see Section 4.2.4.7). 

    PCI_TRACE((TRACE_PCI," Link RESETING (LnkSpeed=0x%X)... ",LnkSpeed));
    addr.ADDR=Device->Address.ADDR;
    addr.Addr.Register=PCI_BRIDGE_CNTL;

#if PCI_EXPRESS_GEN3_SUPPORT
    if(LnkSpeed>=PCIE_LINK_SPEED_80G){
        Status=Pcie3EqualizeLink(Device, &lnkrst);
        ASSERT_EFI_ERROR(Status);
    }
#endif

    //Read BRG_CNT_REG
    Status=PciCfg16(Device->RbIo, addr, FALSE, &bcnt.BRG_CNT_REG);
    ASSERT_EFI_ERROR(Status);
    
    //ASSERT reset Signal 
    bcnt.SecBusReset=TRUE;
    Status=PciCfg16(Device->RbIo, addr, TRUE, &bcnt.BRG_CNT_REG);
    ASSERT_EFI_ERROR(Status);
    pBS->Stall(PCI_T_RST);

    //DE-ASSERT reset Signal 
    bcnt.SecBusReset=FALSE;
    Status=PciCfg16(Device->RbIo, addr, TRUE, &bcnt.BRG_CNT_REG);
    ASSERT_EFI_ERROR(Status);
    PCI_TRACE((TRACE_PCI,"Status = %r.\n",Status));
    pBS->Stall(PCI_T_RST_RECOVERY);
        
    return Status;

}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   PcieRetrainLink()
//
// Description: This function will initiate LINK training of the 
// Down Stream Port referenced as "Device". 
//
// Input: 
//  PCI_DEV_INFO    *Device    Pointer to PCI Device Private Data structure.
//  UINT16          Data       Value to put in LNK_CNT register
//
// Output:	EFI_STATUS
//  EFI_SUCCESS             When everything is going on fine!
//  EFI_DEVICE_ERROR        When driver fails access PCI Bus.
//
// NOTE: Must be called only for PCI Express devices (Device->PciExpress!=NULL)
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS PcieRetrainLink(PCI_DEV_INFO *Device, UINT16 Data, UINT8 LnkSpeed){
    EFI_STATUS          Status=0;
	PCI_CFG_ADDR		staa, cnta;
    PCIE_LNK_STA_REG    sta;
    PCIE_LNK_CNT_REG    cnt;
    UINTN               i=0, j=0;
    BOOLEAN             ltok, lnkrt=TRUE;
//-------------------------------------

    PCI_TRACE((TRACE_PCI," Link RETRAINING...(LnkSpeed=0x%X); # of retry %d ",LnkSpeed, gPciSetupData->LnkTrRetry));

    staa.ADDR=Device->Address.ADDR;
    cnta.ADDR=Device->Address.ADDR;
    cnta.Addr.Register=Device->PciExpress->PcieOffs+PCIE_LNK_CNT_OFFSET;
    staa.Addr.Register=Device->PciExpress->PcieOffs+PCIE_LNK_STA_OFFSET;
    
    Status=PciCfg16(Device->RbIo, cnta, FALSE, &cnt.LNK_CNT);
    ASSERT_EFI_ERROR(Status);
    if(EFI_ERROR(Status)) return Status;    

#if PCI_EXPRESS_GEN3_SUPPORT
    if(LnkSpeed>=PCIE_LINK_SPEED_80G){
        Status=Pcie3EqualizeLink(Device, &lnkrt);
    	ASSERT_EFI_ERROR(Status);
    }
#endif

    //The above algorithm guarantees that Link training will be based on the Link control parameter
    //settings that software intends.
    for(i=0, ltok=FALSE; i<=gPciSetupData->LnkTrRetry; i++){
        //1. Software sets the relevant Link control parameters to the desired settings without writing a 1b to
        //   the Retrain Link bit. (Was done before in PcieProgramLink routine)...

        //2. Software polls the Link Training bit in the Link Status register until the value returned is 0b.
        Status=PciCfg16(Device->RbIo, staa, FALSE, &sta.LNK_STA);
        ASSERT_EFI_ERROR(Status);
        if(EFI_ERROR(Status)) goto rEXIT;    

        if(sta.LnkTraining!=0){
            for(j=0; j<=gPciSetupData->LnkTrRetry; j++){        
                Status=PciCfg16(Device->RbIo, staa, FALSE, &sta.LNK_STA);
                ASSERT_EFI_ERROR(Status);
                if(sta.LnkTraining==0) break;
                pBS->Stall(gPciSetupData->LnkTrTimeout);
            }
        }

        //if stll link did not come from Recovery State
        if(sta.LnkTraining!=0 && i>=gPciSetupData->LnkTrRetry){
            PCI_TRACE((TRACE_PCI,"PciE: TRAINING FAILURE! Link can't exit Recovery State. Disabling Link!\n"));
            Status=PcieDisableLink(Device, TRUE);
            Status=EFI_DEVICE_ERROR;
            ASSERT_EFI_ERROR(Status);
            goto rEXIT;
        } else PCI_TRACE((TRACE_PCI,"%d, ",i));
        
                
        //3. Software writes a 1b to the Retrain Link bit without changing any other fields in the Link
        //   Control register.
        cnt.RetrainLnk=TRUE;
        
        Status=PciCfg16(Device->RbIo, cnta, TRUE, &cnt.LNK_CNT);
        ASSERT_EFI_ERROR(Status);
        if(EFI_ERROR(Status)) return Status;    
        
        //Workaround for devices which having Link Retrain bit "sticky"
        //Spec says it always reads as "0".
        Status=PciCfg16(Device->RbIo, cnta, FALSE, &cnt.LNK_CNT);
        ASSERT_EFI_ERROR(Status);
        if(EFI_ERROR(Status)) return Status;    
        
        if(cnt.RetrainLnk==TRUE){
            cnt.RetrainLnk=FALSE;
            Status=PciCfg16(Device->RbIo, cnta, TRUE, &cnt.LNK_CNT);
            ASSERT_EFI_ERROR(Status);
            if(EFI_ERROR(Status)) return Status;    
        }

        //Pool link Status back again to make sure it trained well.
        Status=PciCfg16(Device->RbIo, staa, FALSE, &sta.LNK_STA);
        ASSERT_EFI_ERROR(Status);
        if(EFI_ERROR(Status)) goto rEXIT;

        if(sta.LnkTraining!=0){
            for(j=0; j<gPciSetupData->LnkTrRetry; j++){        
                Status=PciCfg16(Device->RbIo, staa, FALSE, &sta.LNK_STA);
                ASSERT_EFI_ERROR(Status);
                if(sta.LnkTraining==0) {
                    ltok=TRUE;
                    break;
                }
                pBS->Stall(gPciSetupData->LnkTrTimeout);
            }
        } else ltok=TRUE;


        if(ltok) break;
    }

#if PCI_EXPRESS_GEN3_SUPPORT
    if(LnkSpeed>=PCIE_LINK_SPEED_80G){
        Status=Pcie3GetEqualizationStatus(Device);
        if(EFI_ERROR(Status)){
            //if equalization did not went trough retry it 
            if(Status==EFI_DEVICE_ERROR) {
				PCI_TRACE((TRACE_PCI," EQ_STS=%r; ", Status));
			}
            Status=EFI_SUCCESS;
        }
    }
#endif

rEXIT:
    PCI_TRACE((TRACE_PCI," %r\n", Status));
    return Status;
} 

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   PcieSetSlotProperties()
//
// Description: This function will Initialize SLT_CNT and SLT_STA registers 
// of the "Device". 
//
// Input: 
//  PCI_DEV_INFO    *Device    Pointer to PCI Device Private Data structure.
//
// Output:	EFI_STATUS
//  EFI_SUCCESS             When everything is going on fine!
//  EFI_DEVICE_ERROR        When driver fails access PCI Bus.
//
// NOTE: Must be called only for PCI Express devices (Device->PciExpress!=NULL)
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS PcieSetSlotProperties(PCI_DEV_INFO *Device){
	EFI_STATUS		Status=EFI_SUCCESS;
	PCI_CFG_ADDR		addr;
	PCIE_SLT_CNT_REG	sltc;
	PCIE_SLT_STA_REG	slts;
//--------------------------------

    PCI_TRACE((TRACE_PCI," PciE:  PcieSetSlotProperties() SlotImpl=%d -> ",Device->PciExpress->PcieCap.SlotImpl));

    if(Device->PciExpress->PcieCap.SlotImpl==TRUE){
        addr.ADDR=Device->Address.ADDR; 

		addr.Addr.Register=Device->PciExpress->PcieOffs+PCIE_SLT_CNT_OFFSET;
		Status=PciCfg16(Device->RbIo,addr,FALSE,&sltc.SLT_CNT);
		ASSERT_EFI_ERROR(Status);
		
		addr.Addr.Register=Device->PciExpress->PcieOffs+PCIE_SLT_STA_OFFSET;
		Status=PciCfg16(Device->RbIo,addr,FALSE,&slts.SLT_STA);
		ASSERT_EFI_ERROR(Status);

		sltc.AttnBtnPress=0;
		sltc.PowerFaul=0;
		sltc.MrlSensor=0;
		sltc.PresenceDet=0;
		sltc.CmdCompleted=0;
		sltc.HpIntEnable=0;
        sltc.DllStatChEn=0;


        //Clear all RW1C bits in status reg...
        slts.AttnBtnPress=1;
		slts.PowerFaul=1;
        slts.MrlSensor=1;
		slts.PresenceDet=1;	
		slts.CmdCompleted=1;
        slts.DllStateChg=1;

		
		//Power Up slot and set all possible indication on...
		if(Device->PciExpress->SlotCap.AttnInd)	sltc.AttnIndCnt=PCIE_SLT_INDICATOR_ON;	
		if(Device->PciExpress->SlotCap.PowerInd)sltc.PowerIndCnt=PCIE_SLT_INDICATOR_ON;	
		if(Device->PciExpress->SlotCap.PwrCntler)sltc.PowerOff=PCIE_SLT_PWR_ON;
		
		Status=PciCfg16(Device->RbIo,addr,TRUE,&slts.SLT_STA);

		addr.Addr.Register=Device->PciExpress->PcieOffs+PCIE_SLT_CNT_OFFSET;
		Status=PciCfg16(Device->RbIo,addr,TRUE,&sltc.SLT_CNT);
    }
    PCI_TRACE((TRACE_PCI,"%r\n", Status));
	ASSERT_EFI_ERROR(Status);

    return Status;
}



//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   PcieGetCaps()
//
// Description: This function will Collect PCI Express Capabilities Data  
// of the "Device". 
//
// Input: 
//  PCI_DEV_INFO    *Device    Pointer to PCI Device Private Data structure.
//
// Output:	EFI_STATUS
//  EFI_SUCCESS             When everything is going on fine!
//  EFI_DEVICE_ERROR        When driver fails access PCI Bus.
//
// NOTE: Must be called only for PCI Express devices (Device->PciExpress!=NULL)
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS PcieGetCaps(PCI_DEV_INFO *Device){
	EFI_STATUS		Status=0;
	PCI_CFG_ADDR		addr;
//-------------------------------
	addr.ADDR=Device->Address.ADDR;

    PCI_TRACE((TRACE_PCI,"\n PciE: Collecting CAPs for [B%X|D%X|F%X]\n",
            Device->Address.Addr.Bus,Device->Address.Addr.Device,Device->Address.Addr.Function));

	PCI_TRACE((TRACE_PCI," PCIE_CAP-> [R=%X|IntMsgNo=%X|SlotImpl=%X|PortType=%X|CapVer=%X]\n",
				Device->PciExpress->PcieCap.Reserved,
				Device->PciExpress->PcieCap.IntMsgNo,
				Device->PciExpress->PcieCap.SlotImpl,
				Device->PciExpress->PcieCap.PortType,
				Device->PciExpress->PcieCap.CapVersion
	)); 

	//Get PCI Express Device CAPs - 32 bit after setting clock configuration
	addr.Addr.Register=Device->PciExpress->PcieOffs+PCIE_DEV_CAP_OFFSET;
	Status=PciCfg32(Device->RbIo,addr,FALSE,&Device->PciExpress->DeviceCap.DEV_CAP);
	ASSERT_EFI_ERROR(Status);


    //Print Content of DEV_CAP and DEV_CNT register..
	PCI_TRACE((TRACE_PCI," DEV_CAP -> [R2=%X|FR=%X|PwrS=%X|PwrV=%X|R1=%X|RBE=%X|PI=%X|AI=%X|AB=%X|EpL1=%X|EpL0=%X|ExT=%X|PhF=%X|MPL=%X]\n", 
				Device->PciExpress->DeviceCap.Reserved2,
                //Added in PCIe Base V2.0
				Device->PciExpress->DeviceCap.FuncResetCap,
				Device->PciExpress->DeviceCap.SlotPwrLimS,
				Device->PciExpress->DeviceCap.SlotPwrLimV,
				Device->PciExpress->DeviceCap.Reserved1,
                //Added in PCIe Base V2.0
				Device->PciExpress->DeviceCap.RoleBasedErr,
				Device->PciExpress->DeviceCap.PowerInd,
				Device->PciExpress->DeviceCap.AttnInd,
				Device->PciExpress->DeviceCap.AttnBtn,
				Device->PciExpress->DeviceCap.EpL1Latency,
				Device->PciExpress->DeviceCap.EpL0Latency,
				Device->PciExpress->DeviceCap.ExtTagFld,
				Device->PciExpress->DeviceCap.PhantomFunc,
				Device->PciExpress->DeviceCap.MaxPayload
	));

	addr.Addr.Register=Device->PciExpress->PcieOffs+PCIE_LNK_CAP_OFFSET;
	Status=PciCfg32(Device->RbIo,addr,FALSE,&Device->PciExpress->LinkCap.LNK_CAP);
	ASSERT_EFI_ERROR(Status);

    PCI_TRACE((TRACE_PCI," LNK_CAP -> [P#=%X|R=%X|BwN=%X|DllL=%X|SDE=%X|ClkPM=%X|L1=%X|L0=%X|ASPM=%X|MaxW=%X|MaxS=%X]\n",
				Device->PciExpress->LinkCap.PortNum,
				Device->PciExpress->LinkCap.Reserved,
                //Added in PCIe Base V2.0
				Device->PciExpress->LinkCap.BandwNotify,
				Device->PciExpress->LinkCap.DllLnkActive,
				Device->PciExpress->LinkCap.SurpDownErr,
				Device->PciExpress->LinkCap.ClockPm,
                //---------------------------------
				Device->PciExpress->LinkCap.ExL1Latency,
				Device->PciExpress->LinkCap.ExL0Latency,
				Device->PciExpress->LinkCap.AspmSupport,
				Device->PciExpress->LinkCap.MaxLnkWidth,
				Device->PciExpress->LinkCap.MaxLnkSpeed
	)); 
	
    //Get PCI Express Slot CAPs - 32 bit it is valid only for Ports Switches and Bridges
	if((Device->Type==tPci2PciBrg || Device->Type==tPci2CrdBrg) &&
	    Device->PciExpress->PcieCap.SlotImpl )
	{
		addr.Addr.Register=Device->PciExpress->PcieOffs+PCIE_SLT_CAP_OFFSET;
		Status=PciCfg32(Device->RbIo,addr,FALSE,&Device->PciExpress->SlotCap.SLT_CAP);
		ASSERT_EFI_ERROR(Status);

        PCI_TRACE((TRACE_PCI," SLT_CAP -> [S#=%X|NoCmdC=%X|EmLck=%X|PwrS=%X|PwrV=%X|HpC=%X|HpS=%X|PI=%X|AI=%X|MrlS=%X|PwC=%X|AB=%X]\n",
				Device->PciExpress->SlotCap.PhisSlotNum,
                //Added in PCIe Base V2.0
				Device->PciExpress->SlotCap.NoCmdCompl,
				Device->PciExpress->SlotCap.EmInterlock,
                //----------------------------
				Device->PciExpress->SlotCap.PwrLimScale,
				Device->PciExpress->SlotCap.PwrLimVal,
				Device->PciExpress->SlotCap.HpCapable,
				Device->PciExpress->SlotCap.HpSurprise,
				Device->PciExpress->SlotCap.PowerInd,
				Device->PciExpress->SlotCap.AttnInd,
				Device->PciExpress->SlotCap.MrlSensor,
				Device->PciExpress->SlotCap.PwrCntler,
				Device->PciExpress->SlotCap.AttnBtn
		));

    }

    return Status;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   PcieSetLnkProperties()
//
// Description: This function will Select values for Link Control2 register on 
// both sides of the LINK based on Setup Settiongs and hardware capabilities.
// 
// Input:
//  PCI_DEV_INFO        *DnStreamPort   Pointer to PCI Device Private Data of Downstream Port of the link.
//  PCIE_LNK_CNT2_REG   *DnLnkCnt      Pointer to the LNK_CNT Reg of the Downstream Port of the link.
//  PCI_DEV_INFO        *UpStreamPort   Pointer to PCI Device Private Data of Upwnstream Port of the link.
//  PCIE_LNK_CNT2_REG   *UpLnkCnt      Pointer to the LNK_CNT Reg of the Downstream Port of the link. 
//  BOOLEAN             *LinkTrainingRequired Flag to modify if Link will need RETRAINING after programming.
//
// Output:	EFI_STATUS
//  EFI_SUCCESS             When everything is going on fine!
//  EFI_DEVICE_ERROR        When driver fails access PCI Bus.
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS PcieSetLnkProperties( PCI_DEV_INFO           *DnStreamPort, 
                                 PCIE_LNK_CNT_REG       *DnLnkCnt, 
                                 PCI_DEV_INFO           *UpStreamPort,
                                 PCIE_LNK_CNT_REG       *UpLnkCnt, 
                                 BOOLEAN                *LinkTrainingRequired)
{
    EFI_STATUS          Status=EFI_SUCCESS;
    PCIE_LNK_STA_REG    dnls, upls; //link status reg content of up and down side of the link
	PCI_CFG_ADDR		addr;
    BOOLEAN             cc=FALSE;
//------------------------------

    PCI_TRACE((TRACE_PCI,"PciE: PcieSetLnkProperties() ENTRY:\n"));

    PCI_TRACE((TRACE_PCI," DN STREAM PORT -> [B%X|D%X|F%X] <--> [B%X|D%X|F%X] <- UP STREAM PORT\n",
            DnStreamPort->Address.Addr.Bus,DnStreamPort->Address.Addr.Device, DnStreamPort->Address.Addr.Function,
            UpStreamPort->Address.Addr.Bus,UpStreamPort->Address.Addr.Device, UpStreamPort->Address.Addr.Function));

    //Get DownStream Port Properties
    addr.ADDR=DnStreamPort->Address.ADDR;
    addr.Addr.Register=DnStreamPort->PciExpress->PcieOffs+PCIE_LNK_CNT_OFFSET;
    Status=PciCfg16(DnStreamPort->RbIo,addr,FALSE, &DnLnkCnt->LNK_CNT);
    ASSERT_EFI_ERROR(Status);
    if(EFI_ERROR(Status)) return Status;

    PCI_TRACE((TRACE_PCI," LNK_CNT -> [BwI=%X|BwMI=%X|AuWi=%X|CkPM=%X|ExS=%X|CCk=%X|Rtr=%X|LDis=%X|RCB=%X|ASPM=%X]\n",
                DnLnkCnt->AutoBandwInt,
                DnLnkCnt->BandwMgmtInt,
                DnLnkCnt->HwAutoWdtDis,
                DnLnkCnt->ClockPm,
                DnLnkCnt->ExtSynch,
                DnLnkCnt->CommonClk,
                DnLnkCnt->RetrainLnk,
                DnLnkCnt->LnkDisable,
                DnLnkCnt->RdComplBound,
                DnLnkCnt->AspmControl));



    addr.Addr.Register=DnStreamPort->PciExpress->PcieOffs+PCIE_LNK_STA_OFFSET;
    Status=PciCfg16(DnStreamPort->RbIo,addr,FALSE, &dnls.LNK_STA);
    ASSERT_EFI_ERROR(Status);
    if(EFI_ERROR(Status)) return Status;

    //Get UpStream Stream Port Properties
    addr.ADDR=UpStreamPort->Address.ADDR;

    addr.Addr.Register=UpStreamPort->PciExpress->PcieOffs+PCIE_LNK_CNT_OFFSET;
    Status=PciCfg16(UpStreamPort->RbIo,addr,FALSE, &UpLnkCnt->LNK_CNT);
    ASSERT_EFI_ERROR(Status);
    if(EFI_ERROR(Status)) return Status;

    PCI_TRACE((TRACE_PCI," LNK_CNT -> [BwI=%X|BwMI=%X|AuWi=%X|CkPM=%X|ExS=%X|CCk=%X|Rtr=%X|LDis=%X|RCB=%X|ASPM=%X]\n    ....... UPDATINNG .......\n",
                UpLnkCnt->AutoBandwInt,
                UpLnkCnt->BandwMgmtInt,
                UpLnkCnt->HwAutoWdtDis,
                UpLnkCnt->ClockPm,
                UpLnkCnt->ExtSynch,
                UpLnkCnt->CommonClk,
                UpLnkCnt->RetrainLnk,
                UpLnkCnt->LnkDisable,
                UpLnkCnt->RdComplBound,
                UpLnkCnt->AspmControl));
    
    //Get Lnk Status Content... from DownSteam and UpStream Ports
    addr.Addr.Register=UpStreamPort->PciExpress->PcieOffs+PCIE_LNK_STA_OFFSET;
    Status=PciCfg16(UpStreamPort->RbIo,addr,FALSE, &upls.LNK_STA);
    ASSERT_EFI_ERROR(Status);
    if(EFI_ERROR(Status)) return Status;

    //1.Disable ASPM for now we will set it later starting from Endpoints! 
    DnLnkCnt->AspmControl=0;
    UpLnkCnt->AspmControl=0;
    
    //2. Check Clock Config
    //Check if Lnk Clk config programmed correctly by CSP Code.
    //see if both sides can use Common Clock (Power up Default == 0)
    if(dnls.CommonClk && upls.CommonClk) cc=TRUE;
    
    //Verify if ClkConfig is set correctly and detect if link training is needed
    if((DnLnkCnt->CommonClk != cc) || (UpLnkCnt->CommonClk!=cc)) *LinkTrainingRequired=TRUE;
    DnLnkCnt->CommonClk=cc;
    UpLnkCnt->CommonClk=cc;
    
    //3.Extended Sinch 
    DnLnkCnt->ExtSynch=gPciSetupData->ExtendedSynch;
    UpLnkCnt->ExtSynch=gPciSetupData->ExtendedSynch;

    //4. Clock PM
#if PCI_EXPRESS_GEN2_SUPPORT     
    if((UpStreamPort->PciExpress->LinkCap.ClockPm) && (gPciSetupData->ClockPm)) 
    {
        DnLnkCnt->ClockPm=TRUE;
        UpLnkCnt->ClockPm=TRUE;
    } else {
        DnLnkCnt->ClockPm=FALSE;
        UpLnkCnt->ClockPm=FALSE;
    }
#endif
    //5. Clear Some interupt related bits.
    DnLnkCnt->BandwMgmtInt=FALSE;
    DnLnkCnt->AutoBandwInt=FALSE;

    PCI_TRACE((TRACE_PCI," LNK_CNT -> [BwI=%X|BwMI=%X|AuWi=%X|CkPM=%X|ExS=%X|CCk=%X|Rtr=%X|LDis=%X|RCB=%X|ASPM=%X]\n",
                DnLnkCnt->AutoBandwInt,
                DnLnkCnt->BandwMgmtInt,
                DnLnkCnt->HwAutoWdtDis,
                DnLnkCnt->ClockPm,
                DnLnkCnt->ExtSynch,
                DnLnkCnt->CommonClk,
                DnLnkCnt->RetrainLnk,
                DnLnkCnt->LnkDisable,
                DnLnkCnt->RdComplBound,
                DnLnkCnt->AspmControl));

    PCI_TRACE((TRACE_PCI," LNK_CNT -> [BwI=%X|BwMI=%X|AuWi=%X|CkPM=%X|ExS=%X|CCk=%X|Rtr=%X|LDis=%X|RCB=%X|ASPM=%X]\n\n",
                UpLnkCnt->AutoBandwInt,
                UpLnkCnt->BandwMgmtInt,
                UpLnkCnt->HwAutoWdtDis,
                UpLnkCnt->ClockPm,
                UpLnkCnt->ExtSynch,
                UpLnkCnt->CommonClk,
                UpLnkCnt->RetrainLnk,
                UpLnkCnt->LnkDisable,
                UpLnkCnt->RdComplBound,
                UpLnkCnt->AspmControl));

    return Status;
}



//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   PcieIsDownStreamPort()
//
// Description: This function will check if *PCI_DEV_INFO passed belongs to
// PCI Express DOWNSTREAM PORT:
//  - RootPort of PCIe Root Complex; 
//  - DownStream Port of PCIe Switch; 
//  - PCI/PCI-X to PCIe Bridge.
//
// Input:
//  PCI_DEV_INFO    *Dev    Pointer to PCI Device Private Data structure.
//
// Output:	BOOLEAN         
//  TRUE         When PCI_DEV_INFO passed belongs to DOWNSTREAM PORT
//  FALSE        All other cases...
//
// NOTE: Must be called only for PCI Express devices (Device->PciExpress!=NULL)
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
BOOLEAN PcieIsDownStreamPort(PCI_DEV_INFO *Device){
    
    if((Device->PciExpress->PcieCap.PortType == PCIE_TYPE_ROOTPORT) ||
       (Device->PciExpress->PcieCap.PortType == PCIE_TYPE_DNS_PORT) ||
       (Device->PciExpress->PcieCap.PortType == PCIE_TYPE_PCI_PCIE))
        return TRUE; 
    else 
        return FALSE;
}
//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   PcieSetSlotPower()
//
// Description: This function will power ON or OFF PCI Express Slot
//
// Input:
//  PCI_DEV_INFO    *Dev    Pointer to PCI Device Private Data structure.
//  BOOLEAN         PwrOn   Tells to turn slot power ON or OFF
//
// Output:	EFI_STATUS
//  EFI_SUCCESS             When everything is going on fine!
//  EFI_DEVICE_ERROR        When driver fails access PCI Bus.
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS PcieSetSlotPower(PCI_DEV_INFO* Device, BOOLEAN PwrOn){
	PCI_CFG_ADDR		addr;
	PCIE_SLT_CNT_REG	sltc;
	EFI_STATUS			Status=0;
	UINT16				pwr=PCIE_SLT_PWR_OFF;
//--------------------------------------------
	if(!Device->PciExpress) return EFI_SUCCESS;

	if(Device->PciExpress->SlotCap.PwrCntler){
		addr.ADDR=Device->Address.ADDR;
		addr.Addr.Register=Device->PciExpress->PcieOffs+PCIE_SLT_CNT_OFFSET;
		Status=PciCfg16(Device->RbIo,addr,FALSE,&sltc.SLT_CNT);
		ASSERT_EFI_ERROR(Status);
		if(PwrOn){
			if(Device->PciExpress->SlotCap.PowerInd) sltc.PowerIndCnt=PCIE_SLT_INDICATOR_ON;	
			sltc.PowerOff=PCIE_SLT_PWR_ON;
		} else {
			if(Device->PciExpress->SlotCap.PowerInd) sltc.PowerIndCnt=PCIE_SLT_INDICATOR_OFF;	
			sltc.PowerOff=PCIE_SLT_PWR_OFF;
		}	
		Status=PciCfg16(Device->RbIo,addr,TRUE,&sltc.SLT_CNT);
		ASSERT_EFI_ERROR(Status);
	}
	return Status;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   RestoreBridgeBuses()
//
// Description: This function will Reprogram Primary Secondary and Subordinate 
// bus numbers for the downsteram bridges after SEC BUS reset signal assertion.
//
// Input:
//  PCI_DEV_INFO    *DnPort    Pointer to PCI Device Private Data structure.
//
// Output:	EFI_STATUS
//  EFI_SUCCESS             When everything is going on fine!
//  EFI_DEVICE_ERROR        When driver fails access PCI Bus.
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS RestoreBridgeBuses(PCI_DEV_INFO *DnPort){
    UINTN           i;
    PCI_BRG_EXT     *ext=(PCI_BRG_EXT*)(DnPort+1);
    PCI_DEV_INFO    *dev;
    EFI_STATUS      Status=EFI_SUCCESS;
//---------------------
    for(i=0; i< ext->ChildCount; i++){
        dev=ext->ChildList[i];
        if(dev->Type==tPci2PciBrg){
            Status=MapBridgeBuses(dev);
            if(EFI_ERROR(Status)) return Status;
            //call recoursively to cover all hierarchy
            Status=RestoreBridgeBuses(dev);
            if(EFI_ERROR(Status)) return Status;
        }
    }
    return Status;    
}


//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   PcieInitLink()
//
// Description: This function will Initialize Pcie Link on both sides starting 
// fronm DownStream Port.
//
// Input:
//  PCI_DEV_INFO    *DnPort    Pointer to PCI Device Private Data structure.
//
// Output:	EFI_STATUS
//  EFI_SUCCESS             When everything is going on fine!
//  EFI_DEVICE_ERROR        When driver fails access PCI Bus.
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS PcieInitLink(PCI_DEV_INFO *DnPort){
	EFI_STATUS 			Status=EFI_SUCCESS;
	PCI_DEV_INFO		*dn, *up, *f0;
    PCI_BRG_EXT         *ext;
    PCIE_LNK_CNT_REG    dnlc, uplc;  
	BOOLEAN				lr=FALSE,lt=FALSE, pe2=FALSE, mf=FALSE;
    UINT16              mpl, l0, l1;//calculated link speed
    UINTN               i=0,r=1;
    T_ITEM_LIST         *chldlst=NULL;
    UINT8               lnkspeed=0;
#if PCI_EXPRESS_GEN2_SUPPORT    
    PCIE_LNK_CNT2_REG   dnlc2, uplc2;
#endif
//-------------------------------

    if(DnPort->PciExpress==NULL) return EFI_SUCCESS;

    //Going from DOWN STREAM PORT to EP   
    dn=DnPort;
    ext=(PCI_BRG_EXT*)(dn+1);


    PCI_TRACE((TRACE_PCI,"\n PciE: InitLink DNSP @ [B%X|D%X|F%X] has 0x%X Childs",
            dn->Address.Addr.Bus,dn->Address.Addr.Device,dn->Address.Addr.Function, ext->ChildCount));
    if(ext->ChildCount==0){
        Status=PcieDisableLink(dn, FALSE);
        PCI_TRACE((TRACE_PCI," - Disabe Inactive Link=%d: %r\n", gPciSetupData->LnkDisable, Status));
        ASSERT_EFI_ERROR(Status);
        return Status;
    }

    //Check if we need to initialize Pcie2 features as well
    //it will happened if both sides of the link supports PcieGen2 spec
#if PCI_EXPRESS_GEN2_SUPPORT    
    if(dn->PciExpress->Pcie2!=NULL)pe2=TRUE;
    else pe2=FALSE;
#endif

    if(pe2)PCI_TRACE((TRACE_PCI," ARI=%d; ",dn->PciExpress->Pcie2->AriEnabled));
    else PCI_TRACE((TRACE_PCI," ARI=0; "));

    Status=CpyItemLst((T_ITEM_LIST*)&ext->InitialCount, &chldlst);
    ASSERT_EFI_ERROR(Status);
    if(EFI_ERROR(Status)) return Status;
    
    //Went trough Bridge's Childs and...
    for(i=0,f0=NULL; i<chldlst->ItemCount; i++){
        up=(PCI_DEV_INFO*)chldlst->Items[i];

        if(up->PciExpress==NULL)return EFI_SUCCESS; 

        if(IsFunc0(up)){
            f0=up;
            mf=IsFunc0OfMfDev(up);
#if PCI_EXPRESS_GEN2_SUPPORT    
            //Set PCIe GEN2 Properties first it ia applicable only for Func0
            //if both sides of the link supports it...
            if((up->PciExpress->Pcie2!=NULL) && (pe2==TRUE)){
                PCI_TRACE((TRACE_PCI,"GEN2=%d.\n",pe2));
                Status=Pcie2SetLnkProperties(dn, &dnlc2, up, &uplc2, &lr, &lt);
                ASSERT_EFI_ERROR(Status);
                if(EFI_ERROR(Status)) return Status;
            } else pe2 = FALSE;
#endif
            if(pe2==FALSE)PCI_TRACE((TRACE_PCI,"GEN2=%d.\n",pe2));

            //Now Set PCIe GEN1 properties.
            Status=PcieSetLnkProperties(dn, &dnlc, up, &uplc, &lt);

            //Now remove pointer to the func 0 from DOWN STREAM PORT Child's List
            Status=DeleteItemLst(chldlst, i, FALSE);
            ASSERT_EFI_ERROR(Status);
            if(EFI_ERROR(Status)) return Status;
            break;
        } 
    }

    //It must be a Child with Function == 0 there... 
    ASSERT(f0!=NULL);

    //now we are here and have prepared content of LNK_CNT and LNK_CNT2 for programming.
    //there are some rules for link initialization that differes for ARI devices and regular ones.
    //1. If device is ARI devise (has ARI compatibility header) all programming is applicable for Function0 only.
    //   all other Link control Register bits are reserved for the functions other than 0.
    //2. If Device is NON-ARI than:
    //  a) all functions must report same value in capabilities except ClockPM bit - 
    //     it is independent but will work only if all Functions of the device reports same capability.
    //  b) all functions mus have same values in LNK_CNT for feature to work. 
    //     except same old ClockPM - it can be set only if all functions support it.

    //Check some condition which suppose to be true for PCI Express Devices.
    ASSERT(chldlst->ItemCount == f0->FuncCount); //it must be the same number as FuncCount of Func0 device    

    //If device id NON-ARI we must programm all functions to the same values
    if((f0!=NULL) && (f0->PciExpress->AriData == NULL) && (mf==TRUE)){

        PcieUpdateClockPm(f0,&uplc);        
        //Apply Settings for each child if device is MF
        for(i=0; i<f0->FuncCount; i++){
            up=f0->DevFunc[i];

            if(up->PciExpress==NULL) continue; 

            Status=PcieProgramLink(up,uplc.LNK_CNT, FALSE);
            ASSERT_EFI_ERROR(Status);
            if(EFI_ERROR(Status)) return Status;

#if PCI_EXPRESS_GEN2_SUPPORT    
            if(pe2){
                Status=PcieProgramLink(up,uplc2.LNK_CNT2,TRUE);
                ASSERT_EFI_ERROR(Status);
                if(EFI_ERROR(Status)) return Status;
            }
#endif

        }
    }

    //Now Program the link ....
    //Func 0 of Upstrem port...
    Status=PcieProgramLink(f0,uplc.LNK_CNT, FALSE);
    ASSERT_EFI_ERROR(Status);
    if(EFI_ERROR(Status)) return Status;

#if PCI_EXPRESS_GEN2_SUPPORT    
    if(pe2){
        Status=PcieProgramLink(f0,uplc2.LNK_CNT2, TRUE);            
        ASSERT_EFI_ERROR(Status);
        if(EFI_ERROR(Status)) return Status;
    }
#endif
        
    //Downstream port...
    Status=PcieProgramLink(dn,dnlc.LNK_CNT, FALSE);
    ASSERT_EFI_ERROR(Status);
    if(EFI_ERROR(Status)) return Status;

#if PCI_EXPRESS_GEN2_SUPPORT    
    if(pe2){
        Status=PcieProgramLink(dn,dnlc2.LNK_CNT2, TRUE);            
        ASSERT_EFI_ERROR(Status);
        if(EFI_ERROR(Status)) return Status;
    }
    //All soft instances of PCIe registers updated
    //now check update lnkspeed variable
    if(pe2)lnkspeed=(UINT8)(dnlc2.TargetLnkSpeed);
    else lnkspeed=1;
#else
    lnkspeed=1;
#endif

    //And now see do we need to Retrain link or issue a Hot Reset.
    //If Link Speed was changed we need to do a Hot Reset of a Link.
    //When Hot Reset issued with New Link Parameters link will be retrained anyway.
    if(lr){
        Status=PcieResetLink(dn, lnkspeed);
        Status=RestoreBridgeBuses(dn);
    }

    if(lt) Status=PcieRetrainLink(dn,dnlc.LNK_CNT, lnkspeed);   
    
    ASSERT_EFI_ERROR(Status);
    if(EFI_ERROR(Status)) return Status;

    //Update Internal Data now once we have applied all link settings
    //It might affect some capablities of the PCIe Device.
#if PCI_EXPRESS_GEN2_SUPPORT    
    if(pe2){
        dn->PciExpress->Pcie2->LnkSpeed=(UINT8)dnlc2.TargetLnkSpeed;
        f0->PciExpress->Pcie2->LnkSpeed=(UINT8)uplc2.TargetLnkSpeed;
    }
#endif

    //Set Flag that link was progranmmed!
    dn->PciExpress->LinkSet=TRUE;
    f0->PciExpress->LinkSet=TRUE;

    
    //If link was reseted or retrained update link capabilities 
    //since it might change besause of clock config and speed change.
    if(lt || lr ){
        PCI_TRACE((TRACE_PCI,"Pcie: Refresh CAPs for DNSTREAM; UPSTREAM + ALL FUNC\n"));        
        Status=PcieGetCaps(dn);
    	ASSERT_EFI_ERROR(Status);

        Status=PcieGetCaps(f0);
    	ASSERT_EFI_ERROR(Status);
    }

    //For all devices interfacing with DownStream port
    //update MaxPayLoad and L0s L1 exit Latencies once we are already here. 
    //We will use it later to Program Pcie Device Chain
    mpl=dn->PciExpress->DeviceCap.MaxPayload;

    //value of 0xFFFE indicates corresponded Lx state is not supported)
    //value of 0xFFFF indicates corresponded Lx latency was not calculated yet.
    if(dn->PciExpress->LinkCap.AspmSupport & PCIE_ASPM_L0_ENABLE) l0=dn->PciExpress->LinkCap.ExL0Latency;
    if(dn->PciExpress->LinkCap.AspmSupport & PCIE_ASPM_L1_ENABLE) l1=dn->PciExpress->LinkCap.ExL1Latency;

    if(mpl > f0->PciExpress->DeviceCap.MaxPayload)mpl=f0->PciExpress->DeviceCap.MaxPayload;
    //It is stated in spec "Multi-Function devices associated with an Upstream Port must
    //report the same value in this field for all Functions" 
    if(l0!=0xFFFF && (l0 < f0->PciExpress->LinkCap.ExL0Latency)) l0=f0->PciExpress->LinkCap.ExL0Latency;
    if(l1  < f0->PciExpress->LinkCap.ExL1Latency) l1=f0->PciExpress->LinkCap.ExL1Latency;

    for(i=0; i<f0->FuncCount; i++){
        up=f0->DevFunc[i];

        if(up->PciExpress==NULL)continue; 

        up->PciExpress->LinkSet=TRUE;
#if PCI_EXPRESS_GEN2_SUPPORT    
        if(pe2) up->PciExpress->Pcie2->LnkSpeed=(UINT8)uplc2.TargetLnkSpeed;
#endif
        //Link Retraining or Hot Reset might change Latency values...
        if(lt || lr ){
            Status=PcieGetCaps(up);
    	    ASSERT_EFI_ERROR(Status);
        }
        
        //Update MaxPL for all other functions,....spec says 
        // "The Functions of a multi-Function device are permitted to
        // report different values for this field."
        if(mpl>up->PciExpress->DeviceCap.MaxPayload)mpl=up->PciExpress->DeviceCap.MaxPayload;
        up->PciExpress->MaxL0Lat=l0;
        up->PciExpress->MaxL1Lat=l1;
    }

    //found smallest one and record it in MaxPayload field of DOWNSTREAM PORT and UPSTREAM PORT's F0;
    f0->PciExpress->MaxPayload=mpl;
    f0->PciExpress->MaxL0Lat=l0;
    f0->PciExpress->MaxL1Lat=l1;

    dn->PciExpress->MaxPayload=mpl;
    dn->PciExpress->MaxL0Lat=l0;
    dn->PciExpress->MaxL1Lat=l1;

    //some house keeping;
    ClearItemLst(chldlst, FALSE);
    if(chldlst)pBS->FreePool(chldlst);

    return Status;
}



//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   CollectDeviceExtCap()
//
// Description: This function will Fill out structure of PciE Ext Cap data 
//
// Input:
//  PCI_DEV_INFO    *Device     Pointer to PCI Device Private Data structure.
//
// Output:	EFI_STATUS
//  EFI_SUCCESS             When everything is going on fine!
//  EFI_DEVICE_ERROR        When driver fails access PCI Bus.
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS CollectDeviceExtCap(PCI_DEV_INFO *Device, VOID **DataPtr, UINTN DataSize, UINT32 CapHdrOffset, BOOLEAN Cap16, UINTN OffsetFromCapHdr){
    EFI_STATUS          Status=EFI_SUCCESS;
	PCI_CFG_ADDR		addr;
    PCIE_EXT_DATA_HDR   *dhdr;
//---------------------------------------
    
    //Pointer must be empty at the beginning.
    if(*DataPtr!=NULL) {
        ASSERT_EFI_ERROR(EFI_INVALID_PARAMETER);
        return EFI_INVALID_PARAMETER;
    }
    
    *DataPtr=MallocZ(DataSize); 

    if(*DataPtr==NULL) {
        ASSERT_EFI_ERROR(EFI_OUT_OF_RESOURCES);
        return EFI_OUT_OF_RESOURCES;
    }
 
    dhdr=(PCIE_EXT_DATA_HDR*)(*DataPtr);

    dhdr->CapHdrOffset=CapHdrOffset;

	addr.ADDR=Device->Address.ADDR;
    addr.Addr.ExtendedRegister=CapHdrOffset+(sizeof(PCIE_EXT_CAP_HDR))+(UINT32)OffsetFromCapHdr;
    
    if(Cap16)Status=PciCfg16(Device->RbIo, addr, FALSE,(UINT16*)&dhdr->CapReg);
    else Status=PciCfg32(Device->RbIo, addr, FALSE,(UINT32*)&dhdr->CapReg);

    ASSERT_EFI_ERROR(Status);
    return Status;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   PcieProgramPayloadUp()
//
// Description: This function will reprogram Max Payload and Read Request Size
// in upstream link if initialization code founds that one of Nodes down stream 
// has lesser Max Pay load size than currently programmed 
//
// Input:
//  PCI_DEV_INFO    *Device     Pointer to PCI Device Private Data structure.
//  UINT32          Payload     Reduced Max Payload Value.
//  UINT32          ReadRequest Reduced Read Request Value.
//
// Output:	EFI_STATUS
//  EFI_SUCCESS             When everything is going on fine!
//  EFI_DEVICE_ERROR        When driver fails access PCI Bus.
//
// Notes:
//  RootPortComplex<=>Switch0...<=>...SwitchN<=>EndPoint
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS PcieProgramPayloadUp(PCI_DEV_INFO *Device, UINT16 MaxPayload, UINT16 MaxReadReq){
    EFI_STATUS      Status=EFI_SUCCESS;
    PCI_DEV_INFO    *dev=Device;
//-------------------------

    //It has to be PCIE Switch device so it must have PCI2PCI Bridge Header structure.
    if(dev->Type!=tPci2PciBrg) return EFI_DEVICE_ERROR;

    //We are cominng here if Payload and MaxReadRequest been set for the device and
    //Device is NOT ENDPOINT Device. Means we hit switch here and it handling more then 
    //one ENDPOINT Devices. So check if MPL and MRRS is Bigger or Equal then passed Payload parameter.
    if(dev->PciExpress->MaxPayload > MaxPayload){
        UINTN               i;
        PCI_BRG_EXT         *ext=(PCI_BRG_EXT*)(dev+1);
    	PCI_CFG_ADDR		addr;
        PCIE_DEV_CNT_REG    devc;            
    //-------------
        //if condition met: one or some of the upstream device(s) are capable and programmed 
        //to generate TLP bigger than current proposed programming stored in "mrr" and "mpl".

       	//Select Device Control Register
        addr.ADDR= dev->Address.ADDR;
        addr.Addr.Register=dev->PciExpress->PcieOffs+PCIE_DEV_CNT_OFFSET;
        //Read what we have there
        Status=PciCfg16(dev->RbIo,addr,FALSE,&devc.DEV_CNT);
        ASSERT_EFI_ERROR(Status);

   		PCI_TRACE((TRACE_PCI,"PciE: Going UP @ [B%X|D%X|F%X] Updating: MPL %X to %X\n",
            Device->Address.Addr.Bus,Device->Address.Addr.Device, Device->Address.Addr.Function, 
            devc.MaxPayload, MaxPayload));
        
        for(i=0;i<ext->ChildCount; i++){
            dev=(PCI_DEV_INFO*)ext->ChildList[i];
            if(dev->PciExpress!=NULL){
                //Reprogram only devices we have programmed already.
                if(dev->PciExpress->DevSet){
                    //If we have other switches in upstream link call this function recursively.
                    if(dev->Type==tPci2PciBrg) {
                        PcieProgramPayloadUp(dev, MaxPayload, MaxReadReq);
                        ASSERT_EFI_ERROR(Status);
                        if(EFI_ERROR(Status)) return Status;
                    }
               	    //Select Device Control Register
                    addr.ADDR = dev->Address.ADDR;
                    addr.Addr.Register=dev->PciExpress->PcieOffs+PCIE_DEV_CNT_OFFSET;
                    //Read what we have there
                    Status=PciCfg16(dev->RbIo,addr,FALSE,&devc.DEV_CNT);
                    ASSERT_EFI_ERROR(Status);
                    if(EFI_ERROR(Status)) return Status;

                    PCI_TRACE((TRACE_PCI,"PciE: Reprogram Payload @ [B%X|D%X|F%X] Updating: MPL %X to %X\n",
                        dev->Address.Addr.Bus,dev->Address.Addr.Device, dev->Address.Addr.Function, 
                        devc.MaxPayload, MaxPayload));
                    
                    devc.MaxPayload=MaxPayload;
                    //Leave CHIPSET INIT value if AUTO selected.
                    if(MaxReadReq != 55) devc.MaxReadReq=MaxReadReq;    

                    Status=PciCfg16(dev->RbIo,addr,TRUE, &devc.DEV_CNT);
                    ASSERT_EFI_ERROR(Status);
                    if(EFI_ERROR(Status)) return Status;

                    dev->PciExpress->MaxPayload=MaxPayload;
                    
                }
            } else {
				//Such condition MUST NOT happened, since Parent is UPSTREAM PORT and childs must be a PciE only!
                PCI_TRACE((TRACE_PCI, "PciE: ERROR! PciE Data Uninitialized! Child#=%d. TotalChlds=%d.\n", i, ext->ChildCount));
                return EFI_DEVICE_ERROR;
            }
        }
    } else {
   		PCI_TRACE((TRACE_PCI,"PciE: NOT Going UP @ [B%X|D%X|F%X] Device's Link MPL %X <= New MPL %X\n",
            Device->Address.Addr.Bus,Device->Address.Addr.Device, Device->Address.Addr.Function, 
            dev->PciExpress->MaxPayload, MaxPayload));
    }

    return Status;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   PcieConvertLatency()
//
// Description: This function will convert Latency value from Values read from.
// PPCIe.LNK_CNT_REG to Nanoseconds and opposite.
//
// Input:
//  UINTN   Latency     Latency Value to convert
//  BOOLEAN L0s         Tells if L0s or L1 Exit latency 
//  BOOLEAN ToNs        Tells how to convert:
//                      TRUE  - to the units of nano Seconds; 
//                      FALSE - to the LNK_CNT_REG.LxExitLat register value
//
// Output:	EFI_STATUS
//  UINTN               Converted Value (-1) - means Invalid Value passed;
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

//Return value in nS of Max L0s, L1 Exit latency .
UINTN PcieConvertLatency(UINTN Latency, BOOLEAN L0s, BOOLEAN ToNs){
    UINTN   l0s[]={64,128,256,512,1000,2000,4000,8000};
    UINTN   l1[]= {1000, 2000, 4000, 8000, 16000,32000,64000,128000};
    UINTN   *a, max,i=0;
//---------------------
    //Init stuff
    if(L0s) a=&l0s[0];
    else a=&l1[0];

    if (ToNs) max=7;
    else{
        if(L0s) max=8000;
        else max=128000;
    }

    //Check parameters;
    if (Latency > max){
        return max;
    } 

    if(ToNs) return a[Latency];
    else {
        while(i<8){
            if(a[i]<Latency)i++;
            else break;
        }
        if(i==8) i=7;

        return i;
    }
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   PcieRemoveEpFromLst()
//
// Description: This function will removed Device referencesd as EndPoint from 
// the gPcieEpLst data structure used as a database of available EndPoint devices.
//
// Input:
//  PCI_DEV_INFO    *EndPoint   Pointer to PCI Device Private Data structure.
//
// Output:	EFI_STATUS
//  EFI_SUCCESS             When everything is going on fine!
//  EFI_NOT_FOUND           EndPoint not in the gPcieEpLst.
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS PcieRemoveEpFromLst(PCI_DEV_INFO *EndPoint){
    PCI_DEV_INFO    *dev;
    UINTN           i;
//-------------------------
    for(i=0; i<gPcieEpList.ItemCount; i++){
        dev=(PCI_DEV_INFO*)gPcieEpList.Items[i];
        
        if(dev==EndPoint){
            DeleteItemLst(&gPcieEpList, i, FALSE);
            PCI_TRACE((TRACE_PCI,"PciE: Removing Device [B%X|D%X|F%X] from gPcieEpList[%d]\n",
            EndPoint->Address.Addr.Bus,EndPoint->Address.Addr.Device, EndPoint->Address.Addr.Function, i));
            return EFI_SUCCESS;
        }
    }
    PCI_TRACE((TRACE_PCI,"PciE: Can't find device [B%X|D%X|F%X] in gPcieEpList[%d]\n",
    EndPoint->Address.Addr.Bus,EndPoint->Address.Addr.Device, EndPoint->Address.Addr.Function, gPcieEpList.ItemCount));

    return EFI_NOT_FOUND;
}



//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   PcieCalcMaxPayLoad()
//
// Description: This function will calculate MAX PayLoad Size needed to work 
// correctly.
//
// Input:
//  PCI_DEV_INFO    *EndPoint   Pointer to PCI Device Private Data structure.
//
// Output:	EFI_STATUS
//  EFI_SUCCESS             When everything is going on fine!
//  EFI_DEVICE_ERROR        When driver fails access PCI Bus.
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
UINT16 PcieCalcMaxPayLoad(PCI_DEV_INFO *EndPoint){
    UINT16          tmpl=0xFFFF, lmpl;
    PCI_DEV_INFO    *dn, *up;
    BOOLEAN         progup;
#if EFI_DEBUG == 1 //debug
    UINTN           i=1;
#endif
//--------------------
    up=EndPoint;
	PCI_TRACE((TRACE_PCI,"  Calculate MPL :\n"));
    //Down steam port and F0 holds optimal MPL for all elements on this link 
    do{
        if(up==NULL || up->ParentBrg==NULL)break;
        progup=FALSE;

        if(!IsFunc0(up)) up=up->Func0;
        //Init this link mpl var (dn<->up)
        lmpl=up->PciExpress->MaxPayload;

        dn=up->ParentBrg;
        if(dn->PciExpress->MaxPayload<lmpl){
            //if UP link has bigger MPL value then DN link
            //Update UP link recoded value...
            lmpl=dn->PciExpress->MaxPayload;
    
            //set the Flag that we have to reprogramm MPL since downstream MPL has been reduced        
            progup=TRUE; 
        }

        //Here lmpl holds smallest value of the link check if accomulated MPL exceeds MPL of this link...
        if(tmpl!=lmpl) progup=TRUE; 
        if(tmpl>lmpl) tmpl=lmpl;

        //PcieProgramPayloadUp has double check if MPL needs to be programmed
        if(progup && up->PciExpress->PcieCap.PortType==PCIE_TYPE_UPS_PORT && up->PciExpress->DevSet){
            if(gPciSetupData->MaxReadRequest!=55) PcieProgramPayloadUp(up, tmpl,gPciSetupData->MaxReadRequest);
            else PcieProgramPayloadUp(up, tmpl, PCIE_MAXPL_512B);
        }

        up->PciExpress->MaxPayload=tmpl;
		
#if EFI_DEBUG == 1 //debug
    	PCI_TRACE((TRACE_PCI,"        Link # %d, Link MPL=%X; Total MPL=%X dn->[B%X|D%X|F%X]<->[B%X|D%X|F%X]<-up;\n", i,lmpl, tmpl,
            dn->Address.Addr.Bus,dn->Address.Addr.Device, dn->Address.Addr.Function,
            up->Address.Addr.Bus,up->Address.Addr.Device, up->Address.Addr.Function ));
        i++;
#endif
        up=dn->ParentBrg;
    } while (up->ParentBrg->PciExpress!=NULL && up->ParentBrg->Type!=tPciRootBrg); //(EIP49743)
    
    PCI_TRACE((TRACE_PCI,"  Calculated MPL %X\n\n", tmpl));   

    return tmpl;
}



//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   PcieCalcLatency()
//
// Description: This function will calculate MAX Latency needed to exit from
// ome of the ASPM Sattes L0s or L1.
//
// Input:
//  PCI_DEV_INFO    *Device Pointer to PCI Device Private Data structure.
//  BOOLEAN         L0s     Tells which ASPM state Latency we are calculating
//
// Output:	EFI_STATUS
//  EFI_SUCCESS             When everything is going on fine!
//  EFI_DEVICE_ERROR        When driver fails access PCI Bus.
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
UINTN PcieCalcLatency(PCI_DEV_INFO *EndPoint, BOOLEAN L0s){
    PCI_DEV_INFO    *dn, *up;
    UINT16          *ll;
    UINTN           i=0, tmp=0, lat=0;
//--------------------
    up=EndPoint;
	PCI_TRACE((TRACE_PCI,"  Calculate "));
    if(L0s)PCI_TRACE((TRACE_PCI,"L0s:\n"));
    else PCI_TRACE((TRACE_PCI,"L1 :\n"));
    //Down steam port and F0 holds optimal MPL for all elements on this link 
    do{
        if(!IsFunc0(up)) up=up->Func0;
        dn=up->ParentBrg;
        if(L0s)ll=&dn->PciExpress->MaxL0Lat;
        else ll=&dn->PciExpress->MaxL1Lat;

        //if PciExpress->MaxL0Lat==0xFFFF means Link does not support ASPM
        if(*ll!=0xFFFF ) {
            if(L0s) {
                tmp=PcieConvertLatency(dn->PciExpress->MaxL0Lat, L0s, TRUE);
                lat+=tmp;
            } else {
                tmp=PcieConvertLatency(dn->PciExpress->MaxL1Lat, L0s, TRUE);
                if(tmp>lat) lat=tmp;
            }
        }
        
    	PCI_TRACE((TRACE_PCI,"        Link# %d Lat=%d(nS) dn->[B%X|D%X|F%X]<->[B%X|D%X|F%X]<-up;\n", i, tmp,
            dn->Address.Addr.Bus,dn->Address.Addr.Device, dn->Address.Addr.Function,
            up->Address.Addr.Bus,up->Address.Addr.Device, up->Address.Addr.Function ));
        i++;
        
        //Advance to the next link.
        up=dn->ParentBrg;
    } while (dn->ParentBrg->PciExpress!=NULL && dn->ParentBrg->Type!=tPciRootBrg);//(EIP49743)

    //Internal delay on each Upstream Port (per spec.) MUST BE NO MORE than 1uS. 
    //so next UPSTREAM Link will start transition from L1 to L0 state in 1uS (worst case)
    // to calculate L1 exit Latency we will use (MAX lat + 1000nS * (i-1)) where i number of links on the packet path. 
    if(!L0s && i>0) lat+=1000*(i-1);

    PCI_TRACE((TRACE_PCI,"  Total Calclulated latency: %d (nS)\n", lat ));   

    return lat;
}


//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   PcieInitVc()
//
// Description: This function will Initialize "Device"'s Virtual Channel properties
// based on Setup Settings and hardware capabilities.
// 
// Input:
//  PCI_DEV_INFO        *Device   Pointer to PCI Device Private Data.
//
// Output:	EFI_STATUS
//  EFI_SUCCESS             When everything is going on fine!
//  EFI_DEVICE_ERROR        When driver fails access PCI Bus.
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS PcieInitVc(PCI_DEV_INFO  *Device){
    EFI_STATUS          Status=EFI_SUCCESS;
	PCI_CFG_ADDR		addr;
	VC_RES_DATA			*vcrd;
	PCIE_VC_RESCNT_REG  vcrc;
	UINTN				c;
//-------------------------
	//Program VC configuration 
	//Limit VC TC to TC0 mapped trough VC0 and Disable all Extended VC resources on the way of the LINK.
	//This is a device driver responcibility to allow different TCs and enable Extended VCs if link has it.

    addr.ADDR=Device->Address.ADDR;
    //Arbitration Table has to be loaded by the Chipset specific code 
    //in NBDxe.c or SBDxe.c or by device specific driver. So don't bother
    for(c=0; c<Device->PciExpress->VcData->VcCount; c++){
        vcrd=Device->PciExpress->VcData->VcResData[c];

		//Locate VC Resource CNT reg
		addr.Addr.ExtendedRegister=vcrd->VcResOffset+4;
		Status=PciCfg32(Device->RbIo,addr,FALSE,&vcrc.VC_RESCNT);
		ASSERT_EFI_ERROR(Status);

		//Disable VC and TC mapping except default mapping TC0 VC0
		if(c){
			vcrc.Tc_VcMap=0; 
			vcrc.VcEnable=0;
		} else {
   			//for Channel0(Default VC this bits must be RO but who knows...)
			vcrc.Tc_VcMap=1; 
			vcrc.VcEnable=1;
		}
		vcrc.VcId=(UINT8)c;

		//write it back
		Status=PciCfg32(Device->RbIo,addr,TRUE,&vcrc.VC_RESCNT);
		ASSERT_EFI_ERROR(Status);
	}

    return Status;
}



//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   PcieSetDevProperties()
//
// Description: This function will Select values for DEVICE CONTROL register 
// based on Setup Settings and hardware capabilities.
// 
// Input:
//  PCI_DEV_INFO        *Device         Pointer to PCI Device Private Data.
//  UINT16              *MaxPayload     Pointer to the MaxPayload value.
//
// Output:	EFI_STATUS
//  EFI_SUCCESS             When everything is going on fine!
//  EFI_DEVICE_ERROR        When driver fails access PCI Bus.
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS PcieSetDevProperties(PCI_DEV_INFO *Device, UINT16 MaxPayload){
    EFI_STATUS          Status;
	PCI_CFG_ADDR		addr;
    PCI_DEV_INFO        *dev=Device;
	PCIE_DEV_CNT_REG	devc;
//-------------------------

    addr.ADDR=Device->Address.ADDR;

    PCI_TRACE((TRACE_PCI,"PciE: PcieSetDevProperties() Device @ [B%X|D%X|F%X] ENTRY:\n",
            addr.Addr.Bus,addr.Addr.Device, addr.Addr.Function));

    if (Device->PciExpress == NULL)
        return EFI_SUCCESS;

    //Select Device Control Register
    addr.Addr.Register=dev->PciExpress->PcieOffs+PCIE_DEV_CNT_OFFSET;
    //Read what we have there
	Status=PciCfg16(dev->RbIo,addr,FALSE,&devc.DEV_CNT);
	ASSERT_EFI_ERROR(Status);
    if(EFI_ERROR(Status)) return Status;

	PCI_TRACE((TRACE_PCI," DEV_CNT -> [FrBr=%X|MRR=%X|NS=%X|APPM=%X|PhF=%X|ETg=%X|MPL=%X|RO=%X|UpRR=%X|FtEr=%X|NfEr=%X|CEr=%X]\n    ....... UPDATINNG .......\n", 
                devc.FnRstBrgRtry,
                devc.MaxReadReq,
                devc.NoSnoop,
                devc.AuxPwrPm,
                devc.PhantomFunc,
                devc.ExtTagFld,
                devc.MaxPayload,
                devc.RelaxOrder,
                devc.UsupReqRep,
                devc.FatalErrRep,
                devc.NfErrRep,
                devc.CorrErrRep));

	//Set some bits:
	//1.Get Maximum PayLoad Size 
    //Don't allow overwrite if it is more than supported 
    if(gPciSetupData->MaxPayload!=55 && gPciSetupData->MaxPayload < MaxPayload) devc.MaxPayload=gPciSetupData->MaxPayload;
    else devc.MaxPayload=MaxPayload;

	//2.Get Max Read Request Size
	if(gPciSetupData->MaxReadRequest!=55) devc.MaxReadReq=gPciSetupData->MaxReadRequest;
    //if "AUTO" selected use value already sitting there...
//    else devc.MaxReadReq=PCIE_MAXPL_512B;

	//3.Enable/Disable extended tagfld per Setup Option
	devc.ExtTagFld=0; //use 5 bit tag.
	if(dev->PciExpress->DeviceCap.ExtTagFld)devc.ExtTagFld=gPciSetupData->ExtTagField;
		
	//4. Set No Snoop bit per Setup Option				
	devc.RelaxOrder=gPciSetupData->RelaxedOrdering;
	devc.NoSnoop=gPciSetupData->NoSnoop;

	//Write it back
	Status=PciCfg16(dev->RbIo,addr,TRUE,&devc.DEV_CNT);
	ASSERT_EFI_ERROR(Status);
        
    //Init device's VC 
    //if we have a virtual channel capability
	if(Device->PciExpress->VcData) Status=PcieInitVc(Device);


/*
    //Print Content of DEV_CAP and DEV_CNT register..
	PCI_TRACE((TRACE_PCI," DEV_CAP -> [R2=%X|FR=%X|PwrS=%X|PwrV=%X|R1=%X|RBE=%X|PI=%X|AI=%X|AB=%X|EpL1=%X|EpL0=%X|ExT=%X|PhF=%X|MPL=%X]\n", 
				dev->PciExpress->DeviceCap.Reserved2,
                //Added in PCIe Base V2.0
				dev->PciExpress->DeviceCap.FuncResetCap,
				dev->PciExpress->DeviceCap.SlotPwrLimS,
				dev->PciExpress->DeviceCap.SlotPwrLimV,
				dev->PciExpress->DeviceCap.Reserved1,
                //Added in PCIe Base V2.0
				dev->PciExpress->DeviceCap.RoleBasedErr,
				dev->PciExpress->DeviceCap.PowerInd,
				dev->PciExpress->DeviceCap.AttnInd,
				dev->PciExpress->DeviceCap.AttnBtn,
				dev->PciExpress->DeviceCap.EpL1Latency,
				dev->PciExpress->DeviceCap.EpL0Latency,
				dev->PciExpress->DeviceCap.ExtTagFld,
				dev->PciExpress->DeviceCap.PhantomFunc,
				dev->PciExpress->DeviceCap.MaxPayload
	));
*/
	PCI_TRACE((TRACE_PCI," DEV_CNT -> [FrBr=%X|MRR=%X|NS=%X|APPM=%X|PhF=%X|ETg=%X|MPL=%X|RO=%X|UpRR=%X|FtEr=%X|NfEr=%X|CEr=%X]\n\n", 
                devc.FnRstBrgRtry,
                devc.MaxReadReq,
                devc.NoSnoop,
                devc.AuxPwrPm,
                devc.PhantomFunc,
                devc.ExtTagFld,
                devc.MaxPayload,
                devc.RelaxOrder,
                devc.UsupReqRep,
                devc.FatalErrRep,
                devc.NfErrRep,
                devc.CorrErrRep));

/*    
    PCI_TRACE((TRACE_PCI," LNK_CAP -> [P#=%X|R=%X|BwN=%X|DllL=%X|SDE=%X|ClkPM=%X|L1=%X|L0=%X|ASPM=%X|MaxW=%X|MaxS=%X]\n",
				dev->PciExpress->LinkCap.PortNum,
				dev->PciExpress->LinkCap.Reserved,
                //Added in PCIe Base V2.0
				dev->PciExpress->LinkCap.BandwNotify,
				dev->PciExpress->LinkCap.DllLnkActive,
				dev->PciExpress->LinkCap.SurpDownErr,
				dev->PciExpress->LinkCap.ClockPm,
                //---------------------------------
				dev->PciExpress->LinkCap.ExL1Latency,
				dev->PciExpress->LinkCap.ExL0Latency,
				dev->PciExpress->LinkCap.AspmSupport,
				dev->PciExpress->LinkCap.MaxLnkWidth,
				dev->PciExpress->LinkCap.MaxLnkSpeed
	)); 

#if EFI_DEBUG         
   if (Device->PciExpress->PcieCap.SlotImpl){

        PCI_TRACE((TRACE_PCI," SLT_CAP -> [S#=%X|NoCmdC=%X|EmLck=%X|PwrS=%X|PwrV=%X|HpC=%X|HpS=%X|PI=%X|AI=%X|MrlS=%X|PwC=%X|AB=%X]\n",
				dev->PciExpress->SlotCap.PhisSlotNum,
                //Added in PCIe Base V2.0
				dev->PciExpress->SlotCap.NoCmdCompl,
				dev->PciExpress->SlotCap.EmInterlock,
                //----------------------------
				dev->PciExpress->SlotCap.PwrLimScale,
				dev->PciExpress->SlotCap.PwrLimVal,
				dev->PciExpress->SlotCap.HpCapable,
				dev->PciExpress->SlotCap.HpSurprise,
				dev->PciExpress->SlotCap.PowerInd,
				dev->PciExpress->SlotCap.AttnInd,
				dev->PciExpress->SlotCap.MrlSensor,
				dev->PciExpress->SlotCap.PwrCntler,
				dev->PciExpress->SlotCap.AttnBtn
		));
    }
#endif
*/
    return Status;

}


//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   PcieSetAspm()
//
// Description: This function will Select values for Link Control2 register on 
// both sides of the LINK based on Setup Settings and hardware capabilities.
// 
// Input:
//  PCI_DEV_INFO        *DnPort   Pointer to PCI Device Private Data of Downstream Port of the link.
//  PCI_DEV_INFO        *UpPort   Pointer to PCI Device Private Data of Upwnstream Port of the link.
//  UINT16              Aspm      ASPM value to programm. 
//  BOOLEAN             *LinkHotResetRequired Flag to modify if Link will need HOT RESET after programming.
//
// Output:	EFI_STATUS
//  EFI_SUCCESS             When everything is going on fine!
//  EFI_DEVICE_ERROR        When driver fails access PCI Bus.
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS PcieSetAspm(PCI_DEV_INFO *DnPort,PCI_DEV_INFO *UpPort,UINT16 Aspm){
    EFI_STATUS          Status;
    PCIE_LNK_CNT_REG	lnkc;
	PCI_CFG_ADDR		addr;
    UINT16              aspm=0, dnaspm, upaspm;
//-------------------------


    PCI_TRACE((TRACE_PCI,"\n Setting ASPM for Link...\n UP STREAM PORT -> [B%X|D%X|F%X] <--> [B%X|D%X|F%X] <- DN STREAM PORT\n",
            UpPort->Address.Addr.Bus,UpPort->Address.Addr.Device, UpPort->Address.Addr.Function,
            DnPort->Address.Addr.Bus,DnPort->Address.Addr.Device, DnPort->Address.Addr.Function ));

    //We are coming here with UpPort as Function 0 already.
    addr.ADDR=UpPort->Address.ADDR;
        
    //Select lnk Control Register
    addr.Addr.Register=UpPort->PciExpress->PcieOffs+PCIE_LNK_CNT_OFFSET;
    //Read what we have there
	Status=PciCfg16(UpPort->RbIo,addr,FALSE,&lnkc.LNK_CNT);
	ASSERT_EFI_ERROR(Status);
    if(EFI_ERROR(Status)) return Status;

    //Spec tells: "ASPM L1 must be enabled by software in the Upstream
    //component on a Link prior to enabling ASPM L1 in the
    //Downstream component on that Link. When disabling ASPM
    //L1, software must disable ASPM L1 in the Downstream
    //component on a Link prior to disabling ASPM L1 in the
    //Upstream component on that Link. ASPM L1 must only be 
    //enabled on the Downstream component if both components on
    //a Link support ASPM L1."

    //We have recorded in MaxLxLat field of the PciExpres Data Structure
    //Link capability to support certain Lx states. 
    //value of 0xFFFF indicates corresponded Lx state is not supported. 
    //It must be the same on both sides of the link!
    ASSERT(DnPort->PciExpress->MaxL0Lat == UpPort->PciExpress->MaxL0Lat);
    ASSERT(DnPort->PciExpress->MaxL1Lat == UpPort->PciExpress->MaxL1Lat);
    //If some links on the Pcie Packet Path does not support certain Lx states,
    //they will remain in L0 state all the time. Mean while ones that supports,
    //will transition to Lx power saving state.
    if( (UpPort->PciExpress->MaxL0Lat == 0xFFFF) ||
        !(UpPort->PciExpress->LinkCap.AspmSupport & PCIE_ASPM_L0_ENABLE) ||
        !(DnPort->PciExpress->LinkCap.AspmSupport & PCIE_ASPM_L0_ENABLE) ) Aspm &=(~PCIE_ASPM_L0_ENABLE);
    if( (UpPort->PciExpress->MaxL1Lat == 0xFFFF) || 
        !(UpPort->PciExpress->LinkCap.AspmSupport & PCIE_ASPM_L1_ENABLE) ||
        !(DnPort->PciExpress->LinkCap.AspmSupport & PCIE_ASPM_L1_ENABLE) ) Aspm &=(~PCIE_ASPM_L1_ENABLE);

    aspm=Aspm;

    //Check Setup settings "Force to L0s" must clear calculated PCIE_ASPM_L1_ENABLE;
    //But should not affect OVERWRITE capabilities.
    //[Disable]==0\ Auto==55 \ Force L0s==1
    if(gPciSetupData->AspmMode == 1) aspm &= (~PCIE_ASPM_L1_ENABLE);
    if(gPciSetupData->AspmMode == 0) aspm = 0;
    //Now "Aspm" has calculated MAX supported ASPM value
    //and "aspm" has Updated accordingly to setup 
    dnaspm=aspm;
    Status=PciPortOemSetAspm(DnPort, &dnaspm);
    PCI_TRACE((TRACE_PCI," Getting Overwr Aspm Settings for DNSTREAM PORT: Calc ASPM = %X ... Setup  ASPM = %X \n",Aspm, aspm));

    upaspm=aspm;
    Status=PciPortOemSetAspm(UpPort, &upaspm);
    PCI_TRACE((TRACE_PCI," Getting Overwr Aspm Settings for UPSTREAM PORT: Calc ASPM = %X ... Setup  ASPM = %X \n",Aspm, aspm));
    
    //check UP and DN STREAM ASPM override settings.
    //and pick smallest one...
    if(dnaspm<upaspm) aspm=dnaspm;
    else aspm=upaspm;
    PCI_TRACE((TRACE_PCI," Status = %r : Calc ASPM = %X ... Overwr ASPM = %X \n",Status,Aspm, aspm));

    //Check if ASPM settings were correctly overwritten 
    //It can't be more than calculated... otherwice system might hung!
    if (aspm>Aspm){
        PCI_TRACE((TRACE_PCI," !![Calc ASPM = %X] LESSER THAN [Ovr  ASPM = %X] - System Might HUNG. Reset to Calculated!!\n", Aspm, aspm));
        aspm=Aspm;
    }

    PCI_TRACE((TRACE_PCI,"\n"));

    if(aspm) {
        lnkc.AspmControl=aspm;

    	//Set ASPM in UpStream Port First for Function 0
        Status=PciCfg16(UpPort->RbIo,addr,TRUE,&lnkc.LNK_CNT);
	    ASSERT_EFI_ERROR(Status);
        if(EFI_ERROR(Status)) return Status;

        //It is recommended to programm all functions even in
        //case of ARI device Func0 is in charge for link behavior.
        if(IsFunc0OfMfDev(UpPort)){
            UINTN           i;
            PCI_DEV_INFO    *dev;
        //--------------------------
            for(i=0; i<UpPort->FuncCount; i++){
                dev=UpPort->DevFunc[i];
               
                if(dev->PciExpress==NULL) continue;                

                addr.ADDR=dev->Address.ADDR;
                addr.Addr.Register=dev->PciExpress->PcieOffs+PCIE_LNK_CNT_OFFSET;
                //Read what we have there
                Status=PciCfg16(dev->RbIo,addr,FALSE,&lnkc.LNK_CNT);
                ASSERT_EFI_ERROR(Status);
                if(EFI_ERROR(Status)) return Status;
         
                lnkc.AspmControl=aspm;

                Status=PciCfg16(dev->RbIo,addr,TRUE,&lnkc.LNK_CNT);
                ASSERT_EFI_ERROR(Status);
                if(EFI_ERROR(Status)) return Status;
            }

        }

        //Select lnk Control Register of Down Stream port
        addr.ADDR=DnPort->Address.ADDR;
        addr.Addr.Register=DnPort->PciExpress->PcieOffs+PCIE_LNK_CNT_OFFSET;
        //Read what we have there
        Status=PciCfg16(DnPort->RbIo,addr,FALSE,&lnkc.LNK_CNT);
        ASSERT_EFI_ERROR(Status);
        if(EFI_ERROR(Status)) return Status;

        //Set ASPM for Downstream Port
        lnkc.AspmControl=aspm;

        //Write Back
        Status=PciCfg16(DnPort->RbIo,addr,TRUE,&lnkc.LNK_CNT);
        ASSERT_EFI_ERROR(Status);
    }//if(Aspm)

    return Status;
}


//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   PcieApplyDevSettings()
//
// Description: This function will Select values for DEVICE CONTROL register 
// based on Setup Settings and hardware capabilities.
// 
// Input:
//  PCI_DEV_INFO    *EndPoint   Pointer to PCI Device Private Data.
//  UINT16          MaxPayload  MaxPayload value.
//  UINT16          LatencyL0s  Latency L0s value.
//  UINT16          LatencyL1   Latency L1 value.
//
// Output:	EFI_STATUS
//  EFI_SUCCESS             When everything is going on fine!
//  EFI_DEVICE_ERROR        When driver fails access PCI Bus.
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS PcieApplyDevSettings(PCI_DEV_INFO *EndPoint, UINT16 MaxPayLoad, UINT16 LatencyL0s, UINT16 LatencyL1){
    EFI_STATUS          Status=EFI_SUCCESS;
    PCI_DEV_INFO        *dn, *up, *f0=NULL;
    UINTN               i;
    UINT16              aspmc=0, mpl=0;
#if PCI_EXPRESS_GEN2_SUPPORT == 1
    BOOLEAN             pe2=FALSE;
#endif
//--------------------
    up=EndPoint;
    if(!IsFunc0(up)) up=up->Func0;
        
    if(up->PciExpress->DeviceCap.EpL0Latency >= LatencyL0s) aspmc |= PCIE_ASPM_L0_ENABLE;
    if(up->PciExpress->DeviceCap.EpL1Latency >= LatencyL1) aspmc |= PCIE_ASPM_L1_ENABLE;
    

    PCI_TRACE((TRACE_PCI,"\nPciE: PcieApplyDevSettings() -> Starting with Device [B%X|D%X|F%X]\n",
    up->Address.Addr.Bus,up->Address.Addr.Device, up->Address.Addr.Function));

    
    //Check if we need to initialize Pcie2 features as well
    //it will happened if both sides of the link supports PcieGen2 spec
#if PCI_EXPRESS_GEN2_SUPPORT    
    if((up->ParentBrg->PciExpress->Pcie2!=NULL)&&(up->PciExpress->Pcie2!=NULL))pe2=TRUE;
#endif

    do{
        if(up==NULL || up->ParentBrg==NULL)break;
        f0=NULL;
        dn=up->ParentBrg;
        //optimal MPL calculated and passed here; 
        mpl=MaxPayLoad;

        //Set fetures selected in SETUP
        PCI_TRACE((TRACE_PCI,"#---> EndPoint/UPSTREAM @ [B%X|D%X|F%X] ASPM=%X; MPL=%X;\n",
            up->Address.Addr.Bus,up->Address.Addr.Device, up->Address.Addr.Function, aspmc, mpl));

#if PCI_EXPRESS_GEN2_SUPPORT == 1
        if(pe2){
            //If applicable 
            //Set Device fetures for GEN2 devices
            Status=Pcie2SetDevProperties(up); 
    		ASSERT_EFI_ERROR(Status);
            if(EFI_ERROR(Status)) return Status;
        }
#endif

        Status=PcieSetDevProperties(up, mpl); 

        //SetFlag DevProgrammed FLAG..
        up->PciExpress->DevSet=TRUE;

        //Remove processed entrie from EndPoint Database...
        Status=PcieRemoveEpFromLst(up);

        
        //If we got an EndPoint and it is a Multy Func device - go and update all it's functions...
        if(up->PciExpress->PcieCap.PortType == PCIE_TYPE_ENDPOINT || 
           up->PciExpress->PcieCap.PortType == PCIE_TYPE_PCIE_PCI ||
           up->PciExpress->PcieCap.PortType == PCIE_TYPE_LEGACYEP ||
           up->PciExpress->PcieCap.PortType == PCIE_TYPE_UPS_PORT )  
        {
            f0=up;
            for (i=0; i<f0->FuncCount; i++){
                up=f0->DevFunc[i];
                
                PCI_TRACE((TRACE_PCI,"#---> EndPoint/UPSTREAM Function @ [B%X|D%X|F%X] ASPM=%X; MPL=%X;\n",
                        up->Address.Addr.Bus,up->Address.Addr.Device, up->Address.Addr.Function, aspmc, mpl));

                if(up->PciExpress==NULL) continue;

#if PCI_EXPRESS_GEN2_SUPPORT == 1
                if(pe2){
                    //If applicable 
                    //Set Device fetures for GEN2 devices
                    Status=Pcie2SetDevProperties(up); 
                    ASSERT_EFI_ERROR(Status);
                    if(EFI_ERROR(Status)) return Status;
                }
#endif

                //Set fetures selected in SETUP
                Status=PcieSetDevProperties(up, mpl); 
                ASSERT_EFI_ERROR(Status);
                if(EFI_ERROR(Status)) return Status;

                //SetFlag DevProgrammed FLAG..
                up->PciExpress->DevSet=TRUE;

                //Remove processed entrie from EndPoint Database...
                Status=PcieRemoveEpFromLst(up);
            } //for 
        }//if Mf endpoint

        //Restore "up" var 
        if(f0!=NULL) up=f0;        
        
        PCI_TRACE((TRACE_PCI,"<---# RootComp/DNSTREAM @ [B%X|D%X|F%X] ASPM=%X; MPL=%X;\n",
                dn->Address.Addr.Bus,dn->Address.Addr.Device, dn->Address.Addr.Function, aspmc, mpl));

        //now do the DownStream Port... it always ONLY one device!
#if PCI_EXPRESS_GEN2_SUPPORT == 1
        if(pe2){
            //If applicable 
            //Set Device fetures for GEN2 devices
            Status=Pcie2SetDevProperties(dn); 
    		ASSERT_EFI_ERROR(Status);
            if(EFI_ERROR(Status)) return Status;
        }
#endif
        Status=PcieSetDevProperties(dn,mpl); 
        ASSERT_EFI_ERROR(Status);
        if(EFI_ERROR(Status)) return Status;


        //Aspm is off at that point.
        //We should turn it on first in UPSTREAM PORT, than IN DOWNSTREAM port.
        //Since we can owerwrite Settings 
        Status=PcieSetAspm(dn,up,aspmc);
        ASSERT_EFI_ERROR(Status);
        if(EFI_ERROR(Status)) return Status;

        //SetFlag DevProgrammed FLAG..
        dn->PciExpress->DevSet=TRUE;

        //Remove processed entrie from EndPoint Database...
        //Status=PcieRemoveEpFromLst(dn);

        //Go to the next link if any...
        up=dn->ParentBrg;
    } while (up!=NULL && up->ParentBrg!=NULL && up->ParentBrg->Type!=tPciRootBrg && up->ParentBrg->PciExpress!=NULL); //(EIP49743)

    return Status;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   PcieInitDevChain()
//
// Description: This function will detect optimal settings and programm -
// MaxPayLoadSize, ReadRequestSize, ASPM settings and Virtual Channels
// for all devices in the PCIE Links Chain.
//
// Input:
//  PCI_DEV_INFO    *Device Pointer to PCI Device Private Data structure.
//
// Output:	EFI_STATUS
//  EFI_SUCCESS             When everything is going on fine!
//  EFI_DEVICE_ERROR        When driver fails access PCI Bus.
//
// Notes:
//  RootPortComplex<=>Switch0...<=>...SwitchN<=>EndPoint
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS PcieInitDevChain(PCI_DEV_INFO* Device ){
	EFI_STATUS			Status=0;
	UINT16				mpl=-1,mrr=-1;
    UINTN               lt0=0,lt1=0;        //Latency in Nano Seconds. 	
	UINT16				reg_lt0=0,reg_lt1=0;//Latency to be written into Register. 	
#if EFI_DEBUG == 1 //debug
//------------------------------
	PCIE_PCIE_CAP_REG	pciecap;
	PCIE_DEV_CAP_REG	devcap;
	PCIE_LNK_CAP_REG	lnkcap;
	PCIE_SLT_CAP_REG	sltcap;

#if PCI_EXPRESS_GEN2_SUPPORT == 1
	PCIE_DEV_CAP2_REG	devcap2;
	PCIE_LNK_CAP2_REG	lnkcap2;
#endif
//-----------------------------
#endif              //debug
//-----------------------

    //Now we will programm clock config when exiting from the bridge
	//Collect Min Supported feature at the length of the PCIE Devices Chain
#if EFI_DEBUG == 1 //debug
    pciecap.PCIE_CAP=Device->PciExpress->PcieCap.PCIE_CAP;
    devcap.DEV_CAP=Device->PciExpress->DeviceCap.DEV_CAP;
    lnkcap.LNK_CAP=Device->PciExpress->LinkCap.LNK_CAP;
    sltcap.SLT_CAP=Device->PciExpress->SlotCap.SLT_CAP;
#if PCI_EXPRESS_GEN2_SUPPORT == 1
    devcap2.DEV_CAP2=Device->PciExpress->Pcie2->DeviceCap2.DEV_CAP2;
    lnkcap2.LNK_CAP2=Device->PciExpress->Pcie2->LinkCap2.LNK_CAP2;
#endif
#endif//debug

    //Get MaxPayLoad 
    mpl=PcieCalcMaxPayLoad(Device);

	//After PcieCalcMaxPayLoad() Payload has to be adjusted DOWN STREAM already (towards EP Device)...
    //When We come here ASPM already disabled by PcieProbeDevice() function.
    //Since we are going to use Porting Hook to overwrite ASPM settings Calculate Latency OLWAYS
    //and Enable it only if Setup says so...- will be done in PcieSetAspm()


    //Get L0s L1 exit Latencies if needed... 
//    if(gPciSetupData->AspmMode!=0){

    lt0=PcieCalcLatency(Device,TRUE);

   	//now we should add CIPSET internal L0s Exit Latency to the total value
    //For NB if any
    if( (NbDmiAspmSupport & PCIE_ASPM_L0_ENABLE ) && (SbDmiAspmSupport & PCIE_ASPM_L0_ENABLE )){
        if(NbDmiL0ExitLatency > SbDmiL0ExitLatency) lt0 += NbDmiL0ExitLatency;
        else lt0 += SbDmiL0ExitLatency;
    }
    //and SB if any
    reg_lt0+=(UINT16) PcieConvertLatency(lt0, TRUE, FALSE);

//        if(gPciSetupData->AspmMode > 1){
    lt1=PcieCalcLatency(Device,FALSE);

   	//now we should add CIPSET L1 Exit Latency to the total value
    if( (NbDmiAspmSupport & PCIE_ASPM_L1_ENABLE ) && (SbDmiAspmSupport & PCIE_ASPM_L1_ENABLE )){
        if(NbDmiL1ExitLatency > SbDmiL1ExitLatency) lt1 += NbDmiL1ExitLatency;
        else lt1 += SbDmiL1ExitLatency;
    }
    //and SB
    lt1+=SbInternalDelay;
    reg_lt1+=(UINT16) PcieConvertLatency(lt1, FALSE, FALSE);
   
//        } else reg_lt1=0xFFFF;
//    } else reg_lt0=0xFFFF;

	//Apply collected values to the devices
    Status=PcieApplyDevSettings(Device, mpl, reg_lt0, reg_lt1);    

	return Status;
} 

#if SRIOV_SUPPORT
//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   ProbeSriovDevice()
//
// Description: This function will collect information about SRIOV PCIE Device
// and initialize it based on information collected.
//
// Input:
//  PCI_DEV_INFO    *Device Pointer to PCI Device Private Data structure.
//
// Output:	EFI_STATUS
//  EFI_SUCCESS             When everything is going on fine!
//  EFI_OUT_OF_RESOURCES    When system runs out of resources.
//  EFI_DEVICE_ERROR        When driver fails access PCI Bus.
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS ProbeSriovDevice(PCI_DEV_INFO *Device, UINT32 SriovCapBaseOffset){
    EFI_STATUS Status;
    PCIE_SRIOV_CNT_REG SrIoVControl;
    UINT32 PageSize, i=0, incr, maxbar;
    UINT16 InitialFv;
    UINT16 FirstVfOffset;
    UINT16 VfStride;
    UINT16 RoutingId;
    UINT8  VfMaxBus;

    PCI_BAR *Bar;
	PCI_CFG_ADDR		addr;

    addr.ADDR=Device->Address.ADDR;
    addr.Addr.ExtendedRegister = SriovCapBaseOffset;
    PCI_TRACE((TRACE_PCI,"PciBus: Found SRIOV Device @ B%X|D%X|F%X; ", addr.Addr.Bus, addr.Addr.Device, addr.Addr.Function));

//    Device->PciExpress->SriovData = MallocZ(sizeof(PCIE_SRIOV_DATA));
//    ASSERT(Device->PciExpress->SriovData!=NULL);

    //Disable VFs before any further manipulations
    addr.Addr.ExtendedRegister=SriovCapBaseOffset+PCIE_SRIOV_CNT_OFFSET;
    Status=PciCfg16(Device->RbIo,addr,FALSE,&SrIoVControl.SRIOV_CNT);
    ASSERT_EFI_ERROR(Status);
    SrIoVControl.VfEnable = 0;
    SrIoVControl.VfMse = 0;
    Status=PciCfg16(Device->RbIo,addr,TRUE,&SrIoVControl.SRIOV_CNT);
	ASSERT_EFI_ERROR(Status);

    //Initislize System Page Size
    //get supported page sizes
    addr.Addr.ExtendedRegister=SriovCapBaseOffset+PCIE_SRIOV_SUPPORTED_PAGE_SIZES_OFFSET;
    Status=PciCfg32(Device->RbIo,addr,FALSE,&PageSize);
    ASSERT_EFI_ERROR(Status);
    PCI_TRACE((TRACE_PCI,"PageSize: Sup=0x%X; ", PageSize));
    if(PageSize){
        //find the leftmost non-zero bit
	    for(i=1; (PageSize&i)==0 && i!=0; i<<=1) ;
        ASSERT(i!=0);
        //set page size
        addr.Addr.ExtendedRegister=SriovCapBaseOffset+PCIE_SRIOV_SYSTEM_PAGE_SIZE_OFFSET;
        Status=PciCfg32(Device->RbIo,addr,TRUE,&i);
	    ASSERT_EFI_ERROR(Status);
        PageSize = 1<<(i+11);
    }
    PCI_TRACE((TRACE_PCI,"Progr=0x%X(0x%X); ", i, PageSize));

    //Read InitialFv (number of initially associated VFs)
    addr.Addr.ExtendedRegister=SriovCapBaseOffset+PCIE_SRIOV_INITIAL_VF_OFFSET;
    Status=PciCfg16(Device->RbIo,addr,FALSE,&InitialFv);
    ASSERT_EFI_ERROR(Status);
    PCI_TRACE((TRACE_PCI,"InitialFv=%X; ", InitialFv));
            
    //Calculate number of buses conumed by VF
    //Read FirstVfOffset
    addr.Addr.ExtendedRegister=SriovCapBaseOffset+PCIE_SRIOV_FIRST_VF_OFFSET;
    Status=PciCfg16(Device->RbIo,addr,FALSE,&FirstVfOffset);
    ASSERT_EFI_ERROR(Status);
    PCI_TRACE((TRACE_PCI,"FirstVfOffset=%X; ", FirstVfOffset));
    //Read VfStride
    addr.Addr.ExtendedRegister=SriovCapBaseOffset+PCIE_SRIOV_VF_STRIDE_OFFSET;
    Status=PciCfg16(Device->RbIo,addr,FALSE,&VfStride);
    ASSERT_EFI_ERROR(Status);
    PCI_TRACE((TRACE_PCI,"VfStride=%X; ", VfStride));
    //Calculate number of busses conusmed by all VF
    RoutingId = //Request ID of PF
		(addr.Addr.Bus << 8 ) +
		(addr.Addr.Device << 3 ) +
		 addr.Addr.Function + 
         FirstVfOffset + (InitialFv-1)*VfStride;
    VfMaxBus = (UINT8)(RoutingId>>8);
    PCI_TRACE((TRACE_PCI,"VfMaxBus=%X; ", VfMaxBus));
    //reserve additional buses consumed by VF
    mMaxBusFound=VfMaxBus;

    //Read VF BARs
    addr.Addr.ExtendedRegister=SriovCapBaseOffset+PCIE_SRIOV_VF_BAR0_OFFSET;
    incr=0;
    Bar = &Device->PciExpress->SriovData->Bar[0];
    maxbar = PCI_MAX_BAR_NO; 
	for(i=0; i<maxbar; i++){
        UINT32 old32, val32;
        UINT64 old64, val64;
        Status=PciCfg32(Device->RbIo,addr,FALSE,&val32);
        if(EFI_ERROR(Status)) return Status;
        ASSERT((val32 & 1)==0) //VF BAR must be MMIO
        switch (val32 & 0x0F) {
            case 0x0 : 
                Bar[i].Type=tBarMmio32;
		        Bar[i].DiscoveredType=tBarMmio32;
			    incr=4;
                break;
            case 0x4 : 
			    Bar[i].Type=tBarMmio64;
			    Bar[i].DiscoveredType=tBarMmio64;
				incr=8;
				maxbar--;
				break;
			case 0x8 :
#if PCI_AMI_COMBINE_MEM_PMEM32 == 1
                Bar[i].Type=tBarMmio32;
#else 
                Bar[i].Type=tBarMmio32pf;
#endif
				Bar[i].DiscoveredType=tBarMmio32pf;
				incr=4;
				break;
			case 0xc :
				Bar[i].Type=tBarMmio64pf;
				Bar[i].DiscoveredType=tBarMmio64pf;
				incr=8;
				maxbar--;
				break;
			default : return EFI_UNSUPPORTED;
		} //switch			
		Bar[i].ExtOffset=addr.Addr.ExtendedRegister;
				
        val32=(~0); val64=(~0);
		
		switch (Bar[i].Type){
		
		    case tBarMmio64pf	:
			case tBarMmio64		:
			    Status=PciCfg64(Device->RbIo,addr,FALSE,&old64);
				if(EFI_ERROR(Status)) return Status;
				Status=PciCfg64(Device->RbIo,addr,TRUE,&val64);
				if(EFI_ERROR(Status)) return Status;
				Status=PciCfg64(Device->RbIo,addr,FALSE,&val64);
				if(EFI_ERROR(Status)) return Status;
				val64&=(~0x0F); //Mask don't care bits
				if(val64){
				    Bar[i].Gran=(UINTN)(~val64);
					Bar[i].Length=Mul64((Bar[i].Gran+1),(UINT32)InitialFv);
				} else {
                    Bar[i].Type=tBarUnused;
                }
				break;

			case tBarMmio32pf	:
			case tBarMmio32		:
				Status=PciCfg32(Device->RbIo,addr,FALSE,&old32);
				if(EFI_ERROR(Status)) return Status;
				Status=PciCfg32(Device->RbIo,addr,TRUE,&val32);
				if(EFI_ERROR(Status)) return Status;
				Status=PciCfg32(Device->RbIo,addr,FALSE,&val32);
				if(EFI_ERROR(Status)) return Status;
				val32&=(~0x0F);
				if(val32){
				    Bar[i].Gran=(~val32);
					Bar[i].Length=Mul64((Bar[i].Gran+1),(UINT32)InitialFv);
				} else{ 
                    Bar[i].Type=tBarUnused;
                }
				break;
			
			default : Bar[i].Type=tBarUnused;
		}//switch 
		
		//Restore Original Value value
		if(Bar[i].Type!=tBarUnused){
		    if(Bar[i].Type==tBarMmio64pf || Bar[i].Type==tBarMmio64) Status=PciCfg64(Device->RbIo,addr,TRUE,&old64);
			else Status=PciCfg32(Device->RbIo,addr,TRUE,&old32);
			if(EFI_ERROR(Status)) return Status;
		}
        Bar[i].Owner = Device;
        addr.Addr.ExtendedRegister+=incr;
	} // Bar enumeration loop
    PCI_TRACE((TRACE_PCI,"\n"));
    return EFI_SUCCESS;
}
#endif


//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   InitDeviceVc()
//
// Description: This function will Init VC_DATA structure of the "Device".
// 
// Input:
//  PCI_DEV_INFO    *Device     Pointer to PCI Device Private Data.
//  PCI_CFG_ADDR    *DevAddr    Pointer to Device Address value.
//
// Output:	EFI_STATUS
//  EFI_SUCCESS             When everything is going on fine!
//  EFI_DEVICE_ERROR        When driver fails access PCI Bus.
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS InitDeviceVc(PCI_DEV_INFO *Device, PCI_CFG_ADDR *DevAddr){
    EFI_STATUS      Status;
	VC_DATA		    *vcd=MallocZ(sizeof(VC_DATA));
	VC_RES_DATA	    *vcrd;
    UINTN		    i;
    PCI_CFG_ADDR    addr;
//-----------------	
    addr.ADDR=DevAddr->ADDR;
	if(!vcd) return EFI_OUT_OF_RESOURCES;

	Device->PciExpress->VcData=vcd;			
	vcd->VcOffset=addr.Addr.ExtendedRegister;
		//Read and store VC Cap 1 reg 
	addr.Addr.ExtendedRegister=vcd->VcOffset+PCIE_PORTVC_CAP1_OFFSET;
	Status=PciCfg32(Device->RbIo,addr,FALSE,&vcd->VcCap1.PORTVC_CAP1);
	ASSERT_EFI_ERROR(Status);

	//Read and store VC Cap 2 reg 
	addr.Addr.ExtendedRegister=vcd->VcOffset+PCIE_PORTVC_CAP2_OFFSET;
	Status=PciCfg32(Device->RbIo,addr,FALSE,&vcd->VcCap2.PORTVC_CAP2);
	ASSERT_EFI_ERROR(Status);
			
		//Collect VC resource info... 
	for(i=0; i<vcd->VcCap1.ExtVcCnt+vcd->VcCap1.LPExtVcCnt+1; i++){
		vcrd=MallocZ(sizeof(VC_RES_DATA));
		if(!vcrd) return EFI_OUT_OF_RESOURCES;
		addr.Addr.ExtendedRegister=(UINT32)(vcd->VcOffset+PCIE_VC_RES_CAP_OFFSET(i));
		//Record Offset of the VC resource capability register
		vcrd->VcResOffset=addr.Addr.ExtendedRegister;
		Status=PciCfg32(Device->RbIo,addr,FALSE,&vcrd->VcResCap.VC_RESCAP);
		ASSERT_EFI_ERROR(Status);

		Status=AppendItemLst((T_ITEM_LIST*)&vcd->InitCnt, vcrd);
		if(EFI_ERROR(Status)) return EFI_OUT_OF_RESOURCES;
	}
    return Status;
}




//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   PcieProbeDevice()
//
// Description: This function will collect information about PCIE Device
// and initialize it based on information collected.
//
// Input:
//  PCI_DEV_INFO    *Device Pointer to PCI Device Private Data structure.
//
// Output:	EFI_STATUS
//  EFI_SUCCESS             When everything is going on fine!
//  EFI_OUT_OF_RESOURCES    When system runs out of resources.
//  EFI_DEVICE_ERROR        When driver fails access PCI Bus.
//
// Notes: The function will do the following steps 
//  1.disable ASPM if any;
//  2.disable PMI Generation if any;
//  3.power up PCIE Slot (if capable) if the slot has device behind it;
//  4.if nothing connected to slot, power it down to make it HOTPLUG READY;
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS PcieProbeDevice(PCI_DEV_INFO *Device){
	PCI_CFG_ADDR		addr;
	PCIE_DEV_CNT_REG	devc;
	PCIE_LNK_CNT_REG	lnkc;
	PCIE_EXT_CAP_HDR	extcap;
    PCIE_LNK_STA_REG    lnks;
	EFI_STATUS		    Status=0;
//-------------------------------------

    //init fields that not suppose to be 0    
    Device->PciExpress->MaxL0Lat=0xFFFF;
    Device->PciExpress->MaxL1Lat=0xFFFF;

	addr.ADDR=Device->Address.ADDR;
	
	//Get PCI Express CAPs - 16 bit
	addr.Addr.Register=Device->PciExpress->PcieOffs+PCIE_CAP_OFFSET;
	Status=PciCfg16(Device->RbIo,addr,FALSE,&Device->PciExpress->PcieCap.PCIE_CAP);
	ASSERT_EFI_ERROR(Status);

    Status=PcieGetCaps(Device);
	ASSERT_EFI_ERROR(Status);

	//Get PCI Express Slot it is valid only for Ports Switches and Bridges
	if((Device->Type==tPci2PciBrg) || (Device->Type==tPci2CrdBrg)) PcieSetSlotProperties(Device);
	
	//Disable Device Control Reg functions we'll not need now
	addr.Addr.Register=Device->PciExpress->PcieOffs+PCIE_DEV_CNT_OFFSET;
	Status=PciCfg16(Device->RbIo,addr,FALSE,&devc.DEV_CNT);
	ASSERT_EFI_ERROR(Status);
	//Set Default values 
	devc.CorrErrRep=0; 	//bit 0
	devc.NfErrRep=0;	//bit 1
	devc.FatalErrRep=0;	//bit 2	
	devc.UsupReqRep=0;	//bit 3
	devc.RelaxOrder=1;	//bit 4
	devc.MaxPayload=PCIE_MAXPL_128B;//bit 5..7
	devc.ExtTagFld=0;	//bit 8
	devc.PhantomFunc=0;	//bit 9
	devc.NoSnoop=1;		//bit 11
    //Don't touch MRR value it might be device dependent and may cause system hung
    //devc.MaxReadReq=PCIE_MAXPL_512B;//bit 12..14

	Status=PciCfg16(Device->RbIo,addr,TRUE,&devc.DEV_CNT);
	ASSERT_EFI_ERROR(Status);

    //Get common Lnk Properties from LNK_STA reg..
	addr.Addr.Register=Device->PciExpress->PcieOffs+PCIE_LNK_STA_OFFSET;
	Status=PciCfg16(Device->RbIo,addr,FALSE,&lnks.LNK_STA);
	ASSERT_EFI_ERROR(Status);
    
    //Update data
    Device->PciExpress->CurrLnkSpeed=(UINT8)lnks.LnkSpeed;
    Device->PciExpress->CurrLnkWidth=(UINT8)lnks.LnkWidth; 

	//Disable ASPM
	addr.Addr.Register=Device->PciExpress->PcieOffs+PCIE_LNK_CNT_OFFSET;
	Status=PciCfg16(Device->RbIo,addr,FALSE,&lnkc.LNK_CNT);
	ASSERT_EFI_ERROR(Status);

	lnkc.AspmControl=PCIE_ASPM_DISABLE;
	lnkc.ExtSynch=0;

	Status=PciCfg16(Device->RbIo,addr,TRUE,&lnkc.LNK_CNT);
	ASSERT_EFI_ERROR(Status);

	//Check Pci Express Extended Capability header
	addr.Addr.ExtendedRegister=0x100;	
	//if something there advance trough EXT capabilities list to find VC Cap
	while(addr.Addr.ExtendedRegister){
		Status=PciCfg32(Device->RbIo,addr,FALSE,&extcap.EXT_CAP_HDR);
		ASSERT_EFI_ERROR(Status);
        //Check if Extended PciExpress Config Space is assessible.
		if(extcap.ExtCapId==0xFFFF) break;	//(EIP19144+)

		//we've got VC Cap header
		if(extcap.ExtCapId==PCIE_CAP_ID_VIRTUAL_CH){
            PCI_TRACE((TRACE_PCI,"PciE2: Found VIRTUAL_CHNL Ext Cap Header @ offset 0x%X\n", addr.Addr.ExtendedRegister));
            Status=InitDeviceVc(Device, &addr);
            ASSERT_EFI_ERROR(Status);
        }
#if SRIOV_SUPPORT
        if (extcap.ExtCapId==PCIE_CAP_ID_SRIOV){
            PCI_TRACE((TRACE_PCI,"PciE2: Found SRIOV Ext Cap Header @ offset 0x%X\n", addr.Addr.ExtendedRegister));
            Status=CollectDeviceExtCap(Device, &Device->PciExpress->SriovData, sizeof(PCIE_SRIOV_DATA), 
                    addr.Addr.ExtendedRegister, FALSE, 0); //32 bit cap register
            ASSERT_EFI_ERROR(Status);
 
            Status=ProbeSriovDevice(Device, addr.Addr.ExtendedRegister);
            ASSERT_EFI_ERROR(Status);
        } 
#endif
#if PCI_EXPRESS_GEN2_SUPPORT 
        //Check and collect capability (read only) data from devices
        //1. Alternative Routing ID capabilities  
        if (extcap.ExtCapId==PCIE_CAP_ID_ARI){
            PCI_TRACE((TRACE_PCI,"PciE2: Found ARI Ext Cap Header @ offset 0x%X\n", addr.Addr.ExtendedRegister));

            Status=CollectDeviceExtCap(Device, &Device->PciExpress->AriData, sizeof(PCIE2_ARI_DATA), 
                    addr.Addr.ExtendedRegister, TRUE, 0); // 16 bit cap reg
            ASSERT_EFI_ERROR(Status);
        } 

        //2. Access Control Services 
        if (extcap.ExtCapId==PCIE_CAP_ID_ACS){
            PCI_TRACE((TRACE_PCI," PciE2: Found ACS Ext Cap Header @ offset 0x%X\n", addr.Addr.ExtendedRegister));
            Status=CollectDeviceExtCap(Device, &Device->PciExpress->AcsData, sizeof(PCIE2_ACS_DATA), 
                    addr.Addr.ExtendedRegister, TRUE, 0); // 16 bit cap reg
            ASSERT_EFI_ERROR(Status);
        } 

        //3. Address Translation services
        if (extcap.ExtCapId==PCIE_CAP_ID_ATS){
            PCI_TRACE((TRACE_PCI,"PciE2: Found ATS Ext Cap Header @ offset 0x%X\n", addr.Addr.ExtendedRegister));
            Status=CollectDeviceExtCap(Device, &Device->PciExpress->AtsData, sizeof(PCIE2_ATS_DATA), 
                    addr.Addr.ExtendedRegister, TRUE, 0); // 16 bit cap reg
            ASSERT_EFI_ERROR(Status);
        } 

#if PCI_EXPRESS_GEN3_SUPPORT 
        //check for Secondary PCIe Extended Capability header.
        //must be implemented if device supports GEN 3 speed of 8.0 GT/s
        if (extcap.ExtCapId==PCIE_CAP_ID_SEC_PCIE_CAP){
            PCI_TRACE((TRACE_PCI,"PciE3: Found SEC PCIe Ext Cap Header @ offset 0x%X\n", addr.Addr.ExtendedRegister));
            Status=CollectDeviceExtCap(Device, &Device->PciExpress->Pcie3, sizeof(PCIE3_DATA), 
                    addr.Addr.ExtendedRegister, FALSE, 4); // 32 bit cap reg
            ASSERT_EFI_ERROR(Status);
        }
#endif
#endif //gen2 support
        //4. Internal RC Link
        if (extcap.ExtCapId==PCIE_CAP_ID_RC_INT_LNK){
            PCI_TRACE((TRACE_PCI,"PciE2: Found INT_LINK Ext Cap Header @ offset 0x%X\n", addr.Addr.ExtendedRegister));
            Status=CollectDeviceExtCap(Device, &Device->PciExpress->RcLnkData, sizeof(PCIE_RCLNK_DATA),
                    addr.Addr.ExtendedRegister, FALSE, 0); // 32 bit cap reg
            ASSERT_EFI_ERROR(Status);
        } 

		addr.Addr.ExtendedRegister=extcap.NextItemPtr;				
	} //while loop serching for ext caps	

#if PCI_EXPRESS_GEN2_SUPPORT 
    //if PciExpress Capability Reg if it supports PCIe 2.1
    if(Device->PciExpress->PcieCap.CapVersion>=PCIE_CAP_VER2){
        Device->PciExpress->Pcie2=MallocZ(sizeof(PCIE2_DATA));
        if(Device->PciExpress->Pcie2==NULL){
            ASSERT_EFI_ERROR(EFI_OUT_OF_RESOURCES);
            return EFI_OUT_OF_RESOURCES;
        } else Status=Pcie2GetGen2Info(Device);//Function Will update GEN 3 Properties as well...
    }    
#endif

    //If device is Upstream Port type add it to an EndPoint device list.
    if(!PcieIsDownStreamPort(Device) && (Device->Type!= tPci2PciBrg) &&
       (Device->PciExpress->PcieCap.PortType!=PCIE_TYPE_RC_INTEGR_EP) &&      
       (Device->PciExpress->PcieCap.PortType!=PCIE_TYPE_RC_EVT_COLLECT) &&
       (Device->ParentBrg->ParentBrg != NULL))
    {
        Status=AppendItemLst(&gPcieEpList, Device);
        PCI_TRACE((TRACE_PCI,"PciE: Adding Device [B%X|D%X|F%X] to gPcieEpList[%d]\n",
        Device->Address.Addr.Bus,Device->Address.Addr.Device, Device->Address.Addr.Function, gPcieEpList.ItemCount));
        ASSERT_EFI_ERROR(Status);
    }

	return Status;
}


//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   PcieRecordBootScript()
//
// Description: This function will create S3 Resume Boot Script
// for Device's Virtual Channels feature initialization if device
// supports Virtual Channels.
//
// Input:
//  PCI_DEV_INFO    *Brg    Pointer to PCI Device Private Data structure.
//
// Output:	EFI_STATUS
//  EFI_SUCCESS             When everything is going on fine!
//  EFI_OUT_OF_RESOURCES    When system runs out of resources.
//  EFI_DEVICE_ERROR        When driver fails access PCI Bus.
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID PcieRecordBootScript(PCI_DEV_INFO *Brg){
	PCI_DEV_INFO	*dev;
	PCI_BRG_EXT		*ext=(PCI_BRG_EXT*)(Brg+1);
	UINTN			i,c;
	PCI_CFG_ADDR	addr;		
	EFI_STATUS		Status;
	UINT64			v=0;
//------------------------------
	for(i=0; i<ext->ChildCount; i++){
		dev=ext->ChildList[i];
		if(!dev->PciExpress) continue;
        //It could be the case when we have PCI 2 PCI bridges chain and behind 
        //them we will found PCI 2 PCIE bridge. So starting from ROOT we should not 
        //skip bridges without PCIE Capabilities but must go inside and check!  
		//if((dev->PciExpress==NULL) || (dev->Type!=tPci2PciBrg && dev->Type!=tPci2CrdBrg)) continue;

		addr.ADDR=dev->Address.ADDR;
		addr.Addr.ExtendedRegister=0;
		//if device is PciExpress check if it has VC
		if(dev->Type==tPci2PciBrg || dev->Type==tPci2CrdBrg){
			//record Base bus Subordinste bus Secondary bus registers programming  
			//to have device visible on the bus
			addr.Addr.Register=PCI_BRIDGE_PRIMARY_BUS_REGISTER_OFFSET;

			Status=PciCfg32(dev->RbIo,addr,FALSE,(UINT32*)&v);
			BOOT_SCRIPT_S3_PCI_CONFIG_WRITE_MACRO(
				gBootScriptSave, 			//This
				EfiBootScriptWidthUint32,	//Width
				addr.ADDR,1,&v);			//Address, Data
			//call the same function recoursively
			PcieRecordBootScript(dev);

		}
		if(dev->PciExpress->VcData){
		//if(dev->PciExpress!=NULL && dev->PciExpress->VcData!=NULL){
			for(c=0; c<dev->PciExpress->VcData->VcCount; c++){
				VC_RES_DATA *vcrd=dev->PciExpress->VcData->VcResData[c];
			//---------------------------------------
				addr.Addr.ExtendedRegister=vcrd->VcResOffset+4;				
				Status=PciCfg32(dev->RbIo,addr,FALSE,(UINT32*)&v);
	
				BOOT_SCRIPT_S3_MEM_WRITE_MACRO(
					gBootScriptSave, 			//This
					EfiBootScriptWidthUint32,	//Width
					PCIE_CFG_ADDR(addr.Addr.Bus,addr.Addr.Device,addr.Addr.Function,addr.Addr.ExtendedRegister),
					1,&v);						//Data
			}
		}

        if (gPciSetupData->S3PciExpressScripts){
			addr.ADDR=dev->Address.ADDR;
	   		addr.Addr.Register=dev->PciExpress->PcieOffs+PCIE_DEV_CNT_OFFSET;
	   		Status=PciCfg16(dev->RbIo,addr,FALSE,(UINT16*)&v);

			   BOOT_SCRIPT_S3_PCI_CONFIG_WRITE_MACRO(
	    			gBootScriptSave,    //This
	    			EfiBootScriptWidthUint16, //Width
	   			addr.ADDR,
	    		   1,&v);      //Data

			addr.ADDR=dev->Address.ADDR;
	   		addr.Addr.Register=dev->PciExpress->PcieOffs+PCIE_LNK_CNT_OFFSET;
	   		Status=PciCfg16(dev->RbIo,addr,FALSE,(UINT16*)&v);

			   BOOT_SCRIPT_S3_PCI_CONFIG_WRITE_MACRO(
	    			gBootScriptSave,    //This
	    			EfiBootScriptWidthUint16, //Width
	   			addr.ADDR,
	    		   1,&v);      //Data
		
			if(dev->PciExpress->PcieCap.SlotImpl){
				addr.ADDR=dev->Address.ADDR;
		   		addr.Addr.Register=dev->PciExpress->PcieOffs+PCIE_SLT_CNT_OFFSET;
		   		Status=PciCfg16(dev->RbIo,addr,FALSE,(UINT16*)&v);
	
				   BOOT_SCRIPT_S3_PCI_CONFIG_WRITE_MACRO(
		    			gBootScriptSave,    //This
		    			EfiBootScriptWidthUint16, //Width
		   			addr.ADDR,
		    		   1,&v);      //Data
			}
			if(dev->PciExpress->Pcie2){
				addr.ADDR=dev->Address.ADDR;
		   		addr.Addr.Register=dev->PciExpress->PcieOffs+PCIE_DEV_CNT2_OFFSET;
		   		Status=PciCfg16(dev->RbIo,addr,FALSE,(UINT16*)&v);
	
				   BOOT_SCRIPT_S3_PCI_CONFIG_WRITE_MACRO(
		    			gBootScriptSave,    //This
		    			EfiBootScriptWidthUint16, //Width
		   			addr.ADDR,
		    		   1,&v);      //Data
	
				addr.ADDR=dev->Address.ADDR;
		   		addr.Addr.Register=dev->PciExpress->PcieOffs+PCIE_LNK_CNT2_OFFSET;
		   		Status=PciCfg16(dev->RbIo,addr,FALSE,(UINT16*)&v);
	
				   BOOT_SCRIPT_S3_PCI_CONFIG_WRITE_MACRO(
		    			gBootScriptSave,    //This
		    			EfiBootScriptWidthUint16, //Width
		   			addr.ADDR,
		    		   1,&v);      //Data
			}
        } // if (gPciSetupData->S3PciExpressScripts)
	}//for
}
//----------------------------------------------------------------------------
//Enable PCI Express Handling only if PCI Express Base is Defined and !=0
#endif //PCI_EXPRESS_SUPPORT
//----------------------------------------------------------------------------

#if S3_VIDEO_REPOST_SUPPORT == 1
//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   SaveBars()
//
// Description: This function will create S3 Resume Boot Script
// for Device's BAR Registers.
//
// Input:
//  PCI_DEV_INFO    *Dev    Pointer to PCI Device Private Data structure.
//
// Output:	
//  Nothing.
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

VOID SaveBars(PCI_DEV_INFO *Dev){
    UINTN           i;
    PCI_BAR         *bar;
	PCI_CFG_ADDR	addr;		
	EFI_STATUS		Status;
	UINT64			v=0;
	PCI_BRG_EXT		*ext;
//----------------------------

    for( i=0; i < PCI_MAX_BAR_NO+1; i++){
        bar=&Dev->Bar[i];
		addr.ADDR=Dev->Address.ADDR;
		addr.Addr.ExtendedRegister=0;
        
        if( (bar->Type != tBarUnused) && (bar->Length != 0)){
            addr.Addr.Register=bar->Offset;
            if( (Dev->Bar[0].DiscoveredType == tBarMmio64) || (Dev->Bar[0].DiscoveredType == tBarMmio64pf)){ 
                Status=PciCfg64(Dev->RbIo,addr,FALSE,&v);
       			BOOT_SCRIPT_S3_PCI_CONFIG_WRITE_MACRO(
    				            gBootScriptSave, 			//This
                				EfiBootScriptWidthUint64,	//Width
                				addr.ADDR,1,&v);			//Address, Data
            } else {
                Status=PciCfg32(Dev->RbIo,addr,FALSE,(UINT32*)&v);
       			BOOT_SCRIPT_S3_PCI_CONFIG_WRITE_MACRO(
    				            gBootScriptSave, 			//This
                				EfiBootScriptWidthUint32,	//Width
                				addr.ADDR,1,&v);			//Address, Data
            } 
        }
    } //for
    
    //if device is p2p bridge
    if( Dev->Type == tPci2PciBrg){
        //get bridge extension structure pointer
        ext=(PCI_BRG_EXT*)(Dev+1);
        
        //For IO 16 Resources Decoded by the bridge
        addr.Addr.Register = ext->Res[rtIo16].Offset;
        Status=PciCfg16(Dev->RbIo,addr,FALSE,(UINT16*)&v);
		BOOT_SCRIPT_S3_PCI_CONFIG_WRITE_MACRO(
  				            gBootScriptSave, 			//This
               				EfiBootScriptWidthUint16,	//Width
               				addr.ADDR,1,&v);			//Address, Data
        //Upper 16bits for IO window
        addr.Addr.Register = 0x30;
        Status=PciCfg32(Dev->RbIo,addr,FALSE,(UINT32*)&v);
		BOOT_SCRIPT_S3_PCI_CONFIG_WRITE_MACRO(
  				            gBootScriptSave, 			//This
               				EfiBootScriptWidthUint32,	//Width
               				addr.ADDR,1,&v);			//Address, Data
   		
        
		//For MMIO Resources Decoded by the bridge
        addr.Addr.Register = ext->Res[rtMmio32].Offset;
        Status=PciCfg32(Dev->RbIo,addr,FALSE,(UINT32*)&v);
		BOOT_SCRIPT_S3_PCI_CONFIG_WRITE_MACRO(
   				            gBootScriptSave, 			//This
               				EfiBootScriptWidthUint32,	//Width
               				addr.ADDR,1,&v);			//Address, Data

		//For MMIO_PF 
        addr.Addr.Register = ext->Res[rtMmio32p].Offset;
        Status=PciCfg32(Dev->RbIo,addr,FALSE,(UINT32*)&v);
		BOOT_SCRIPT_S3_PCI_CONFIG_WRITE_MACRO(
   				            gBootScriptSave, 			//This
               				EfiBootScriptWidthUint32,	//Width
               				addr.ADDR,1,&v);			//Address, Data

		//For MMIO_PF Upper 32 bit
        addr.Addr.Register = 0x28;
        Status=PciCfg64(Dev->RbIo,addr,FALSE,&v);
		BOOT_SCRIPT_S3_PCI_CONFIG_WRITE_MACRO(
   				            gBootScriptSave, 			//This
               				EfiBootScriptWidthUint64,	//Width
               				addr.ADDR,1,&v);			//Address, Data
    }


}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   SaveDevice()
//
// Description: This function will create S3 Resume Boot Script
// for Device's other than BAR Registers.
//
// Input:
//  PCI_DEV_INFO    *Dev    Pointer to PCI Device Private Data structure.
//
// Output:	
//  Nothing.
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

VOID SaveDevice(PCI_DEV_INFO *Dev){
	PCI_CFG_ADDR	addr;		
	EFI_STATUS		Status;
	UINT64			v=0;
//----------------------------
	addr.ADDR=Dev->Address.ADDR;
	addr.Addr.ExtendedRegister=0;
        
    //get Cache line size and Latency Timer + ProgInterface 
	addr.Addr.Register=PCI_CLS;
    Status=PciCfg32(Dev->RbIo,addr,FALSE,(UINT32*)&v);
    BOOT_SCRIPT_S3_PCI_CONFIG_WRITE_MACRO(
				gBootScriptSave, 			//This
				EfiBootScriptWidthUint32,	//Width
				addr.ADDR,1,&v);			//Address, Data

    //Save content of BARs 
    SaveBars(Dev);    

    //get IntLine; IntPin; MaxLat; MinGnt
    addr.Addr.Register=PCI_INTLINE;
    Status=PciCfg32(Dev->RbIo,addr,FALSE,(UINT32*)&v);
    BOOT_SCRIPT_S3_PCI_CONFIG_WRITE_MACRO(
				gBootScriptSave, 			//This
				EfiBootScriptWidthUint32,	//Width
				addr.ADDR,1,&v);			//Address, Data



    //if device is Pci2PciBrg
	if( Dev->Type == tPci2PciBrg){
			
        //get Base bus Subordinste bus Secondary bus registers + Secondary Latency Timer
        addr.Addr.Register=PCI_BRIDGE_PRIMARY_BUS_REGISTER_OFFSET;

    	Status=PciCfg32(Dev->RbIo,addr,FALSE,(UINT32*)&v);
	    BOOT_SCRIPT_S3_PCI_CONFIG_WRITE_MACRO(
  				    gBootScriptSave, 			//This
			        EfiBootScriptWidthUint32,	//Width
			        addr.ADDR,1,&v);			//Address, Data


	} else {
        //Get Subsystem VID; DID Just In case...
		addr.Addr.Register=PCI_SVID;
        Status=PciCfg32(Dev->RbIo,addr,FALSE,(UINT32*)&v);
		BOOT_SCRIPT_S3_PCI_CONFIG_WRITE_MACRO(
		    	    gBootScriptSave, 			//This
    				EfiBootScriptWidthUint32,	//Width
				    addr.ADDR,1,&v);			//Address, Data

    }

    //Now get Device Control Reg
	addr.Addr.Register=PCI_COMMAND_REGISTER_OFFSET;
	Status=PciCfg16(Dev->RbIo,addr,FALSE,(UINT16*)&v);
	BOOT_SCRIPT_S3_PCI_CONFIG_WRITE_MACRO(
			gBootScriptSave, 			//This
		    EfiBootScriptWidthUint16,	//Width
		    addr.ADDR,1,&v);			//Address, Data

}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   RecordPriVgaBootScript()
//
// Description: This function will create S3 Resume Boot Script
// for Device's on the path of primary VGA Device inclusive.
//
// Input:
//  Nothing
//
// Output:	EFI_STATUS
//  EFI_SUCCESS             When everything is going on fine!
//  EFI_OUT_OF_RESOURCES    When system runs out of resources.
//  EFI_DEVICE_ERROR        When driver fails access PCI Bus.
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID RecordPriVgaBootScript(IN EFI_EVENT Event, IN VOID *Context){
	PCI_DEV_INFO	*vga=NULL;
	PCI_DEV_INFO	*dev;
	PCI_HOST_INFO	*hst=&gPciHost[0];
    PCI_BRG_EXT     *ext;
    T_ITEM_LIST     VgaPath={0,0,NULL};
	INTN			i;
    UINTN           j;
	EFI_STATUS		Status;
//------------------------------
    for( i=0; (UINTN)i<gHostCnt; i++){
        hst=&gPciHost[i];
        //There might be only one legacy VGA device in the system
        if( hst->VgaDev!=0){
            vga=hst->VgaDev;
            break;//there will be only one Primary VGA
        }
    }
    
    //If we can't find Primery VGA device just exit 
    //Most likely we are dealing here with headless system.
    if( vga == NULL){
        return;
    }

    dev = vga;
    //Save Device pointers in Current Primary Vga Path
    while (dev!=NULL){
        Status=AppendItemLst(&VgaPath,dev);
        dev=dev->ParentBrg;
    }

    //Now write the boot script in opposite order for the devices stored @ VgaPath object.
    //So the script will go from Host Bridge down to the Pri VGA device 
	for(i=VgaPath.ItemCount-1; i>=0;i--){
		dev=(PCI_DEV_INFO*)VgaPath.Items[i];
                
        //Save device content into BOOT SCRIPT
        SaveDevice(dev);

        //Now check if device is a multifunction device
        //if so it's other functions needs to be saved as well
        if( ( dev->ParentBrg !=NULL) && ( dev->Type != tPci2PciBrg)){
            
            ext = (PCI_BRG_EXT*)(dev->ParentBrg+1);
            //check for devices with the same Dev# but different Function# among device's ParentBridge childs...
            for(j=0; j<ext->ChildCount; j++){           
                vga=ext->ChildList[j];    
                //Since this is one bridge childs they have to have same bus
                if(vga->Address.Addr.Device == dev->Address.Addr.Device &&
                   vga->Address.Addr.Function != dev->Address.Addr.Function) {
                    SaveDevice(vga);
                }

            }//for j
        }
    }//for i

    pBS->CloseEvent(Event);
}
#endif //S3_VIDEO_REPOST

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   ResetDevicePm()
//
// Description: This function will turn off SMI generation on PCI PME
// and put device in to D0 state, if device has PM capability. 
//
// Input:
//  PCI_DEV_INFO    *Brg    Pointer to PCI Device Private Data structure.
//
// Output:	Nothing
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID ResetDevicePm(PCI_DEV_INFO *Device)
{
	EFI_STATUS		Status;
	PCI_CFG_ADDR	devaddr;		
	UINT16			pmcsrv=0x8000;//Turn off the PME assertion and set D0 PM State
//-------------------------------
	
	if(Device->PmiCapOffs){
		devaddr.ADDR=Device->Address.ADDR;
		devaddr.Addr.Register=(UINT8)(Device->PmiCapOffs+4); //
		Status=PciCfg16(Device->RbIo,devaddr,TRUE,&pmcsrv);
		ASSERT_EFI_ERROR(Status);
	}
	return; 
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   QueryPciDevice()
//
// Description: This function will collect all possible data about PCI Device.
//
// Input:
//  PCI_DEV_INFO    *Device Pointer to PCI Device Private Data structure.
//
// Output:	EFI_STATUS
//  EFI_SUCCESS             When everything is going on fine!
//  EFI_OUT_OF_RESOURCES    When system runs out of resources.
//  EFI_DEVICE_ERROR        When driver fails access PCI Bus.
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS QueryPciDevice(PCI_DEV_INFO *Device)
{
	EFI_STATUS		Status=EFI_SUCCESS;
	UINT8			maxbar,	i, incr=0;	
	UINT64			buff=0xff, oldv;
	PCI_CFG_ADDR	devaddr;
	UINT32			*b32=&(UINT32)buff, *o32=&(UINT32)oldv;
//------------------------------------------

	//for accuracy
	Device->Address.Addr.Register=0; 
	Device->Address.Addr.ExtendedRegister=0;
	devaddr.ADDR=Device->Address.ADDR;
	
	PCI_TRACE((TRACE_PCI,"PciBus: Discovered PCI Device @ [B%X|D%X|F%X]; PCI_DEV_INFO.Type=%d.\n Device Data: -> ", 
			Device->Address.Addr.Bus, Device->Address.Addr.Device,
			Device->Address.Addr.Function, Device->Type));

	//Clear Interrupt line register
	devaddr.Addr.Register=PCI_INTLINE;
    //P2P Bridge Spec. v1.1 requires to set INT Line Register to 0xFF
    //PCI spec 3.0 require to set it to 0xFF - means not connected for x86 architecture.
    //Values of 0..0x0F indicating IRQ0..15 values 0x10..0xFE reserved.
	Status=PciCfg8(Device->RbIo,devaddr,TRUE,(UINT8*)&buff);
	ASSERT_EFI_ERROR(Status);
	if(EFI_ERROR(Status)) return Status;

	//We must call Preprocess Controller 
	Status=DoPrepController(Device);

	Status=GetDeviceCapabilities(Device);

	Status=GetPciCapPtrs(Device);
	ASSERT_EFI_ERROR(Status);
	if(EFI_ERROR(Status)) return Status;
	
	ResetDevicePm(Device);	

	//Set Pci Latency Timer register according to the Setup settings;
	devaddr.Addr.Register = 0x0d;
	Status=PciCfg8(Device->RbIo,devaddr,TRUE,(UINT8*)&gPciSetupData->PciLatency);
	if((Device->Type == tPci2PciBrg) || (Device->Type == tPci2CrdBrg)){
		devaddr.Addr.Register = 0x1b;
		Status=PciCfg8(Device->RbIo,devaddr,TRUE,(UINT8*)&gPciSetupData->PciLatency);
	}

#if PCI_X_SUPPORT
	//Set PCI-X Latency Timer register according to the Setup settings;
	devaddr.Addr.Register = 0x0d;
	Status=PciCfg8(Device->RbIo,devaddr,TRUE,(UINT8*)&gPciSetupData->PciXLatency);
	if((Device->Type == tPci2PciBrg) || (Device->Type == tPci2CrdBrg)){
		devaddr.Addr.Register = 0x1b;
		Status=PciCfg8(Device->RbIo,devaddr,TRUE,(UINT8*)&gPciSetupData->PciXLatency);
	}
#endif

//Enables PCI Express Handling only if PCI Express Base is Defined and !=0
#if PCI_EXPRESS_SUPPORT

	if(Device->PciExpress) {
		Status=PcieProbeDevice(Device);	
		ASSERT_EFI_ERROR(Status);
		if(EFI_ERROR(Status)) return Status;
/*
		//If it is end point Device or PCIE 2 PCI bridge
		if(
			Device->PciExpress->PcieCap.PortType==PCIE_TYPE_LEGACYEP||
			Device->PciExpress->PcieCap.PortType==PCIE_TYPE_PCIE_PCI||
            Device->PciExpress->PcieCap.PortType==PCIE_TYPE_RC_INTEGR_EP ||
            Device->PciExpress->PcieCap.PortType==PCIE_TYPE_RC_EVT_COLLECT)
		{
			//Programm Common Clock it will affect ASPM latency of the devices 
            //So it has to be programmed first before collecting all the information about 
            //Device Max PLoad ant reqd request and ep Latency.
			Status=PcieSetClockConfig(Device);
			ASSERT_EFI_ERROR(Status);

			//Programm MaxPayLoad, ReadRequest ASPM settings
			Status=PcieInitDevChain(Device); 
			ASSERT_EFI_ERROR(Status);
		}
*/
	}
#endif

	if(CheckPciCompatibility(Device,NULL,tBarUnused))Device->Incompatible=TRUE; //(EIP41687)
	switch (Device->Type){
		case tPci2PciBrg :
			maxbar=2;
			devaddr.Addr.Register=0x10; //first BAR starts here
			break;
		case tPciDevice	:
		case tPciHostDev:
			maxbar=PCI_MAX_BAR_NO;
			devaddr.Addr.Register=0x10; //first BAR starts here
			break;
		case tPci2CrdBrg :
			maxbar=1;	
			devaddr.Addr.Register=0x10; //first BAR starts here
			break;
		default	:	return EFI_SUCCESS; //other devices not suppose to be examined????
	}
	
	for(i=0; i<maxbar; i++){
		buff=0;
		oldv=0;		
		devaddr.Addr.Register=devaddr.Addr.Register+incr;
		Status=PciCfg32(Device->RbIo,devaddr,FALSE,b32);
		if(EFI_ERROR(Status)) return Status;
		
		//check if what it is...
		if((*b32) & 1) {
			Device->Bar[i].Type=tBarIo;
			incr=4;
		} else {
			switch ((*b32) & 0x0F) {
				case 0x0 : 
					Device->Bar[i].Type=tBarMmio32;
					Device->Bar[i].DiscoveredType=tBarMmio32;
					incr=4;
					break;
				case 0x4 : 
					Device->Bar[i].Type=tBarMmio64;
					Device->Bar[i].DiscoveredType=tBarMmio64;
					incr=8;
					maxbar--;
					break;
				case 0x8 :
#if PCI_AMI_COMBINE_MEM_PMEM32 == 1
					Device->Bar[i].Type=tBarMmio32;
#else 
					Device->Bar[i].Type=tBarMmio32pf;
#endif
					Device->Bar[i].DiscoveredType=tBarMmio32pf;
					incr=4;
					break;
				case 0xc :
					Device->Bar[i].Type=tBarMmio64pf;
					Device->Bar[i].DiscoveredType=tBarMmio64pf;
					incr=8;
					maxbar--;
					break;
				default : return EFI_UNSUPPORTED;
			} //switch			
		}// else for memory BAR
		Device->Bar[i].Offset=devaddr.Addr.Register;
		//Device->Bar[i].Owner=Device;
		
		buff=(~0ULL);
		
		switch (Device->Bar[i].Type){
		
			case tBarMmio64pf	:
			case tBarMmio64		:
				Status=PciCfg64(Device->RbIo,devaddr,FALSE,&oldv);
				if(EFI_ERROR(Status)) return Status;
				Status=PciCfg64(Device->RbIo,devaddr,TRUE,&buff);
				if(EFI_ERROR(Status)) return Status;
				Status=PciCfg64(Device->RbIo,devaddr,FALSE,&buff);
				if(EFI_ERROR(Status)) return Status;
				buff&=(~0x0F); //Mask don't care bits
				if(buff){
					//This workaround done for PCI Compliance Test... 
					//It could be the BAR that clames - "I'm a 64bit BAR", 
                    //but implemented as 32bit register. This BAR will not hold 
                    //64bit address and must be converted to 32bit BAR.
					if(buff<=0xFFFFFFFF) {
						buff|=0xFFFFFFFF00000000;
						Device->Bar[i].Type-=2; //reduce tBarType to 32 bit BAR
					}
					Device->Bar[i].Gran=(UINTN)(~buff);
					if(Device->Incompatible) AdjustBarGra(&Device->Bar[i]);
					if(Device->Bar[i].Type==tBarUnused) {
						Status=PciCfg64(Device->RbIo,devaddr,TRUE,&oldv);
						if(EFI_ERROR(Status)) return Status;
					}
					Device->Bar[i].Length=Device->Bar[i].Gran+1;
				} else Device->Bar[i].Type=tBarUnused;
				break;

			case tBarMmio32pf	:
			case tBarMmio32		:
			case tBarIo			:
				Status=PciCfg32(Device->RbIo,devaddr,FALSE,o32);
				if(EFI_ERROR(Status)) return Status;
				Status=PciCfg32(Device->RbIo,devaddr,TRUE,b32);
				if(EFI_ERROR(Status)) return Status;
				Status=PciCfg32(Device->RbIo,devaddr,FALSE,b32);
				if(EFI_ERROR(Status)) return Status;
				if(Device->Bar[i].Type==tBarIo){
					(*b32)&=(~0x03);
					if(*b32){
						//We got something here try to determine is it 32 bit addressing IO
						//of 16 bit addressing
						if(*b32&0xFFFF0000) {
							Device->Bar[i].Type=tBarIo32;
							Device->Bar[i].DiscoveredType=tBarIo32;
						} else { 
							(*b32)|=(0xffff0000);
							Device->Bar[i].Type=tBarIo16;
							Device->Bar[i].DiscoveredType=tBarIo16;
						}
					}
				} else (*b32)&=(~0x0F);
				if(*b32){
					Device->Bar[i].Gran=(~(*b32));
					if(Device->Incompatible) AdjustBarGra(&Device->Bar[i]);
					if(Device->Bar[i].Type==tBarUnused) {
						Status=PciCfg32(Device->RbIo,devaddr,TRUE,o32);
						if(EFI_ERROR(Status)) return Status;
					}
					Device->Bar[i].Length=Device->Bar[i].Gran+1;
					//Doing work around for resource requirements for I/O
					//where request is lesser than 16 bytes. I'll just make it 16
					//it might be some compatibility issues if I/O resourtce alignment will be 
					// lesser than 8 byte
					if((Device->Bar[i].Type==tBarIo32 || Device->Bar[i].Type==tBarIo16)&&
						Device->Bar[i].Length<0x10)
					{
						Device->Bar[i].Length=0x10;
						Device->Bar[i].Gran=0x0F;
					}

				} else Device->Bar[i].Type=tBarUnused;
				break;
			
			default : Device->Bar[i].Type=tBarUnused;
		}//switch 
		
		//Restore Original Value value
		if(Device->Bar[i].Type!=tBarUnused){
			if(Device->Bar[i].Type==tBarMmio64pf || Device->Bar[i].Type==tBarMmio64) Status=PciCfg64(Device->RbIo,devaddr,TRUE,&oldv);
			else Status=PciCfg32(Device->RbIo,devaddr,TRUE,o32);
			if(EFI_ERROR(Status)) return Status;
		}

//Check that all MMIO is allocated in 4k aligned chanks IVT-d requirements   
#if( (defined iVTd_SUPPORT && iVTd_SUPPORT == 1) || ( PCI_4K_RESOURCE_ALIGNMENT == 1 ) || (SRIOV_SUPPORT == 1) )
//---------------------------------------------
        if((Device->Bar[i].Type==tBarMmio64pf || Device->Bar[i].Type==tBarMmio64 ||
            Device->Bar[i].Type==tBarMmio32pf || Device->Bar[i].Type==tBarMmio32) &&
            Device->Bar[i].Length<0x1000 ) {
                Device->Bar[i].Length=0x1000;
                Device->Bar[i].Gran=0xFFF;
            }               
//---------------------------------------------
#endif        

	} // Bar enumeration loop

	if(Device->Type==tPci2CrdBrg){
		//Clear Brg Control Reg bits 8 & 9 to signify that Mem Window 1&2 is not PF
		devaddr.Addr.Register=PCI_BRIDGE_CONTROL_REGISTER_OFFSET;
		Status=PciCfg16(Device->RbIo,devaddr,FALSE,(UINT16*)&buff);
		ASSERT_EFI_ERROR(Status);
		buff&=(~(BIT09 | BIT08));	//Memory Window 2 is nonPF
		Status=PciCfg16(Device->RbIo,devaddr,TRUE,(UINT16*)&buff);
		ASSERT_EFI_ERROR(Status);
	}

	//now we're going to check if any Option ROM present
	Status=OptionRom(Device);
#if EFI_DEBUG
	for(i=0; i<=PCI_MAX_BAR_NO; i++){

		if((Device->Bar[i].Type>0) && (Device->Bar[i].Length>0))
		{
			PCI_TRACE((TRACE_PCI,"BAR Index=%d;\tType=%d;\tGRA=0x%lX;\tLEN=0x%lX;\tOffset=0x%X;\n", 
				i, Device->Bar[i].Type, Device->Bar[i].Gran, 
				Device->Bar[i].Length, Device->Bar[i].Offset));	
		}
	}
	PCI_TRACE((TRACE_PCI,"\n")); 
#endif

	Device->Discovered=TRUE;
	return Status;
}


//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   ApplyCrdPadding()
//
// Description: This function applys default Card Bus Bridge Padding. 
//
// Input:
//  PCI_DEV_INFO    *Device Pointer to PCI Device Private Data structure.
//  MRES_TYPE       ResType Type of resource padding is applied.
//
// Output:	Nothing
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID ApplyCrdPadding(PCI_DEV_INFO *Device, MRES_TYPE ResType){
	PCI_BRG_EXT		*ext=(PCI_BRG_EXT*)(Device+1);
	PCI_BAR			*bbar=&ext->Res[ResType];
//---------------

	bbar->Type=ResType+1;
	switch(ResType){
		case rtIo16:
			bbar->Length+=0x1000; 
			if(bbar->Gran < 0xFFF) bbar->Gran=0xFFF;
			break;
		
		case rtIo32:
			if(CPU_MAX_IO_SIZE <= 0x10000) {
				bbar->Type=tBarUnused;
				bbar=&ext->Res[ResType-1];
			}
			bbar->Length+=0x1000;
			if(bbar->Gran < 0xFFF) bbar->Gran=0xFFF;
			break;		

		case rtMmio32:
			bbar->Length+=0x1400000; 
			if(bbar->Gran < 0xFFFFF) bbar->Gran=0xFFFFF;
			break;

		case rtMmio32p:
			if (gAllocationAttributes & EFI_PCI_HOST_BRIDGE_COMBINE_MEM_PMEM) {
				bbar->Type=tBarUnused;
				bbar=&ext->Res[ResType-1];
			}
			bbar->Length+=0x1400000;
			if(bbar->Gran < 0xFFFFF) bbar->Gran=0xFFFFF; 
			break;
		case rtMmio64:
		case rtMmio64p:
			bbar->Type=tBarUnused;
			break;
	}
	
	ext->Padded=TRUE;
}


//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   Cmp128Int()
//
// Description: This function compares 2 128 bit integers. 
//
// Input:
//  VOID* pDestination  *Pointer to the 128bit Integer to compare.
//  VOID* pSource       *Pointer to the 128bit Integer to compare.
//
// Output:	INTN
//  == 0 Destination and are Source equal; 
//  >  0 Destination is bigger than Source;
//  <  0 Destination is lesser than Source;
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
INTN Cmp128Int(VOID* pDestination, VOID* pSource){
	INT64 r;
	UINT64 *d=(UINT64*)pDestination;
    UINT64 *s=(UINT64*)pSource;
//----------------------------------
    r = d[1] - s[1]; 
    if( r == 0){
        r = d[0] - s[0];
	}
	return (r>0) ? 1 : (r<0) ? -1 : 0;
}


//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   Cmp128IntRR()
//
// Description: This function compares 2 128 bit integers with respect to EFI 
//  Database Engine Record to Record comparation Routine.
//  When position of record gets determined. 
//
// Input:
//  VOID* pContext      Pointer to the DBE_OFFSET_KEY_CONTEXT structure
//  VOID* pRecord1      Pointer to the 128bit Integer to compare.
//  VOID* pRecord2      Pointer to the 128bit Integer to compare.
//
// Output:	INTN
//  == 0 pRecord1 and are pRecord2 equal; 
//  >  0 pRecord1 is bigger than pRecord2;
//  <  0 pRecord2 is lesser than pRecord2;
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
INTN Cmp128IntRR(IN VOID *pContext, VOID *pRecord1, VOID *pRecord2)
{
	DBE_OFFSET_KEY_CONTEXT *pOffsetKey = (DBE_OFFSET_KEY_CONTEXT*)pContext;
//--------------------------
    return Cmp128Int((VOID*)((INT8*)pRecord1+pOffsetKey->Offset),(VOID*)((INT8*)pRecord2+pOffsetKey->Offset));
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   Cmp128IntKR()
//
// Description: This function compares 2 128 bit integers with respect to EFI 
//  Database Engine Key to Record comparation Routine.
//  When search for record is conducted. 
//
// Input:
//  VOID* pContext      Pointer to the DBE_OFFSET_KEY_CONTEXT structure
//  VOID* pRecord1      Pointer to the 128bit Integer to compare.
//  VOID* pRecord2      Pointer to the 128bit Integer to compare.
//
// Output:	INTN
//  == 0 pRecord1 and are pRecord2 equal; 
//  >  0 pRecord1 is bigger than pRecord2;
//  <  0 pRecord2 is lesser than pRecord2;
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
INTN Cmp128IntKR(IN DBE_OFFSET_KEY_CONTEXT *pContext, VOID *pKey, VOID *pRecord)
{
	DBE_OFFSET_KEY_CONTEXT *pOffsetKey = (DBE_OFFSET_KEY_CONTEXT*)pContext;
//------------------------------
	return Cmp128Int((VOID*)pKey,(VOID*)((INT8*)pRecord+pOffsetKey->Offset));
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   FreeResDb()
//
// Description: This function suppore to free memory allocated for index array 
//  pool of the EFI Database Engine DATABASE.
//
// Input:
//  DBE_DATABASE*   Db    Pointer to the EFI Database Engine DATABASE.
//
// Output:	EFI_STATUS
//  EFI_SUCCESS if everything OK; 
//  an EFI_ERROR if an ERROR
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS FreeResDb(DBE_DATABASE *Db){
	if(Db->IndexArray!=NULL)return pBS->FreePool(Db->IndexArray);
	else return EFI_SUCCESS;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   InitResDb()
//
// Description: This function suppore to initialize EFI Database Engine DATABASE
//  with PCI_BAR pointers in decending order.
//
// Input:
//  DBE_DATABASE*   Db      Pointer to the EFI Database Engine DATABASE.
//  PCI_DEV_INFO*   Brg,    Bridge whose BARs must be stuffed in DATABASE.
//  MRES_TYPE       ResType Resource type of the BARs.
//  BOOLEAN         Dev     We are filling DATABASE with Bridges or Devices.
//
// Output:	EFI_STATUS
//  EFI_SUCCESS if everything OK; 
//  an EFI_ERROR if an ERROR
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS InitResDb(DBE_DATABASE *Db, PCI_DEV_INFO *Brg, MRES_TYPE ResType, BOOLEAN Dev){
	EFI_STATUS			Status=0;
	PCI_DEV_INFO		*dev; 
	PCI_BRG_EXT			*Ext=(PCI_BRG_EXT*)(Brg+1);
	UINTN				i,j;
//------------------------------------	

	//Initialize Optimization Database
	Db->KeyCount=1;
	Db->KeyField=&gBarKey;
	Db->MemoryType=EfiBootServicesData;
	Db->RecordCount=0;

	if(Dev)Db->InitialCount=0x30; //least likely it would be more than 48 BARs of the same type
	else Db->InitialCount=0x10; //same 16 for the bridges, but anyway it would be realocated...

	Status=pBS->AllocatePool(Db->MemoryType,sizeof(VOID*)*Db->InitialCount,&Db->IndexArray);
	if(EFI_ERROR(Status)) return Status;
	
	//Now we will stuff the database with resource requirements sorted in assending order
	for(i=0; i<Ext->ChildCount; i++){
		dev=Ext->ChildList[i];

        if(dev->OutOfResRemove) continue;

		if(Dev){
			for( j=0; j<PCI_MAX_BAR_NO+1; j++){
				//Use ResType+1 Since CountBars() takes diferent type of parameter - 
				//PCI_BAR_TYPE. It mapps to MRES_TYPE as MRES_TYPE+1
				if ((dev->Bar[j].Type==ResType+1) && dev->Bar[j].Length){
					Status=DbeInsert(Db,&dev->Bar[j]);
					if(EFI_ERROR(Status)) return Status;
				}
			}//bar loop
#if SRIOV_SUPPORT
            if (dev->PciExpress!=NULL && dev->PciExpress->SriovData!=NULL){
                PCI_BAR *VfBar = &dev->PciExpress->SriovData->Bar[0];
			    for( j=0; j<PCI_MAX_BAR_NO; j++){
				    //Use ResType+1 Since CountBars() takes diferent type of parameter - 
				    //PCI_BAR_TYPE. It mapps to MRES_TYPE as MRES_TYPE+1
				    if ((VfBar[j].Type==ResType+1) && VfBar[j].Length){
					    Status=DbeInsert(Db,&VfBar[j]);
					    if(EFI_ERROR(Status)) return Status;
				    }
			    }//bar loop
            }
#endif
		} else {
			//take care of the bridge
			if(dev->Type==tPci2PciBrg || dev->Type==tPci2CrdBrg){
				PCI_BRG_EXT *ext=(PCI_BRG_EXT*)(dev+1);
			//-----------------------
				//Don't add empry bridge BARs
				if((ext->Res[ResType].Type==ResType+1) && ext->Res[ResType].Length ){
					Status=DbeInsert(Db,&ext->Res[ResType]);
					if(EFI_ERROR(Status)) Status;
				}
			}
		}
	} //child loop

//	if(!Db->RecordCount)Status=EFI_NOT_FOUND;

	return Status;	
}


//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   AppendBarOrder()
//
// Description: This function suppore to fill array of BAR ORDER with actual 
//  order of PCI_BARs behind the Bridge and remove added BAR structure from
//  the BAR DATABASE.
//
// Input:
//  DBE_DATABASE*   Db      Pointer to the EFI Database Engine DATABASE.
//  BRG_RES_ORDER*  BrgResOrder Pointer to the Bridge Resource order structure.
//  PCI_BAR         Bar     Pointer to the BAR structure to be added.
//
// Output:	EFI_STATUS
//  EFI_SUCCESS if everything OK; 
//  an EFI_ERROR if an ERROR
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS AppendBarOrder(DBE_DATABASE *Db, BRG_RES_ORDER *BrgResOrder, PCI_BAR *Bar){
	EFI_STATUS			Status;
//--------------------------
   	Status=AppendItemLst((T_ITEM_LIST*)BrgResOrder, Bar);
    if(EFI_ERROR(Status))return Status;

	//Remove copied record from Database it not suppose to clear the *bar variable;
	Status=DbeDelete(Db,Bar,FALSE);

	PCI_TRACE((TRACE_PCI," BAR: Len=0x%lX;\t Gra=0x%lX;\t Ofs=0x%X; Owner->[B%X|D%X|F%X] DEV_TYPE=%d\n",
		Bar->Length, Bar->Gran, Bar->Offset, Bar->Owner->Address.Addr.Bus, 
		Bar->Owner->Address.Addr.Device, Bar->Owner->Address.Addr.Function, Bar->Owner->Type));
	
	return Status;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   OptimizeBrgResource()
//
// Description: This function arrange Bridge resource request in a way it will 
//  consume a optimal amount of resources.
//
// Input:
//  PCI_DEV_INFO*   Brg,    Bridge whose BARs must be stuffed in DATABASE.
//  MRES_TYPE       ResType Resource type we are doing optimization for.
//
// Output:	EFI_STATUS
//  EFI_SUCCESS if everything OK; 
//  an EFI_ERROR if an ERROR
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS OptimizeBrgResource(PCI_DEV_INFO *Brg, MRES_TYPE ResType){
	EFI_STATUS			Status=0;
	PCI_DEV_INFO		*dev; //Device Dtata used for iteration,
	PCI_DEV_INFO		*brg; //Bridge Device used to identify Bridge resources with uneven Granularity. 
	PCI_BRG_EXT			*Ext=(PCI_BRG_EXT*)(Brg+1),*ext; //This Bridge Bridge Extension Data.
	UINTN				i;
	PCI_BAR				*bar,*bbar,*nbbar,*nextbar; //temp BAR used in iterations, This Bridge child who is the bridge.  
	BRG_ALIGN_INFO		*balign;
	PCI_BAR				*ebar; 
	BRG_RES_ORDER		*ResOrd=&Ext->BarOrder[ResType]; //This Bridge this bridge Resource Alignment information
	DBE_DATABASE		DevDb={0,0,0,0,NULL,NULL},BrgDb={0,0,0,0,NULL,NULL};
	INT8				v;
	UINT64				val;
	UINT8				bit;
//------------------------------------	

	//No childs behind the bridge, no optimization...
	if(!Ext->ChildCount)return EFI_SUCCESS;
	PCI_TRACE((TRACE_PCI,"PciBus: OptimizeBrgRes() Bridge->[B%X|D%X|F%X] PCI_BRG_EXT.Res[%d] :\n",
			Brg->Address.Addr.Bus, Brg->Address.Addr.Device, Brg->Address.Addr.Function, ResType));


	//Start the optimization
	//1. Create Assending Sorted Database of all PCI Devices BARs behind the Brg of ResType.
	Status=InitResDb(&DevDb, Brg, ResType, TRUE);	
	if(EFI_ERROR(Status)) goto ExitLbl;
	
	Status=InitResDb(&BrgDb, Brg, ResType, FALSE);	
	if(EFI_ERROR(Status)) goto ExitLbl;
	
	PCI_TRACE((TRACE_PCI," BAR(s) Order for %d Device BAR(s); %d Bridge BAR(s) of BAR_TYPE=%d\n",
			DevDb.RecordCount, BrgDb.RecordCount, ResType+1));
	
	//2. Start Populating Resource Array Brg->BarOrder[ResType]
	while(DevDb.RecordCount || BrgDb.RecordCount){
	
		if(BrgDb.RecordCount){
			Status=DbeGoToIndex(&BrgDb,0,BrgDb.RecordCount-1,&bbar);
			if(EFI_ERROR(Status)){
				if(!((Status==EFI_DBE_EOF) || (Status==EFI_DBE_BOF))){
					ASSERT_EFI_ERROR(Status);
					goto ExitLbl;
				}
			}
		} else bbar=NULL;
		
		if(DevDb.RecordCount){
			Status=DbeGoToIndex(&DevDb,0,DevDb.RecordCount-1,&bar);
			if(EFI_ERROR(Status)){
				if(!((Status==EFI_DBE_EOF) || (Status==EFI_DBE_BOF))){
					ASSERT_EFI_ERROR(Status);
					goto ExitLbl;
				}
			}
		} else bar=NULL;

		//Check if THIS Bridge has a bridge childs
		if((bar!=NULL) && (bbar!=NULL)){
			//This case when we have bridge resourses among regular device resources
			brg=bbar->Owner;
			dev=bar->Owner;
			ext=(PCI_BRG_EXT*)(brg+1);
			balign=&ext->Align[ResType];
			
			//1. Check first if Biggest resource in "BrgDb" - "bbar" has the same or lesser 
			//Alignment Requirements as a Biggest one in "DevDb" - "bar". balign->MaxGran 
			if(bar->Gran >= balign->MaxGran){
				Status=AppendBarOrder(&DevDb,ResOrd, bar);
				ASSERT_EFI_ERROR(Status);
				if(EFI_ERROR(Status)) goto ExitLbl;
			} else {
				//This is the case when we should use PCI_BRG_EXT.ExtraRes[ResType] information to accomodate 
				//resources with lower granularity to utilize spase used to adjust uneven bridge granularity
				Status=AppendBarOrder(&BrgDb,ResOrd, bbar);
				ASSERT_EFI_ERROR(Status);
				if(EFI_ERROR(Status)) goto ExitLbl;
				
				//Determine how much Extra resources we will use here
				ebar=&balign->ExtraRes;
				if(bbar->Length & bbar->Gran){
					//Here we have add the biggest bridge resource to the BarOrdedr DB.
					//We have yet Biggrest Dev Resource. Let's see if there are any Bridge resources left
					if(BrgDb.RecordCount){
						Status=DbeGoToIndex(&BrgDb,0,BrgDb.RecordCount-1,&nbbar);
						if(EFI_ERROR(Status)){
							if(!((Status==EFI_DBE_EOF) || (Status==EFI_DBE_BOF))){
								ASSERT_EFI_ERROR(Status);
								goto ExitLbl;
							}
						}
					} else nbbar=NULL;
					//Now see which bar (nbbar-NextBridgeBar) if any, or bar-DeviceBar will be the next 
					//member in BarOrder Database.
					if(nbbar!=NULL){
						if(bar->Gran>=nbbar->Gran)nextbar=bar;
						else nextbar=nbbar;
					} else nextbar=bar;
					
					//Determine how much Extra resources we will use here
					//if we got here - the Bridge resource request, we just added to the BarOrder DB, has uneven alignment
					//Here we have:
					//bbar 		- already added to the BarOrder DB;
					//nextbar	- biggest resource following by the bbar;
					//bar		- biggest Device Bar evenly aligned ;
					if(nextbar->Gran <= balign->ResGran) {
						//if next biggest bar has Alignment requirements lesser or equal to the bbar just added
						//GREAT! We will just add it and forget it;
						if(nextbar==bar)Status=AppendBarOrder(&DevDb,ResOrd, nextbar);
						else Status=AppendBarOrder(&BrgDb,ResOrd, nextbar);
						
						ASSERT_EFI_ERROR(Status);
						if(EFI_ERROR(Status)) goto ExitLbl;
							
					} else {
						ebar->Length=(( bbar->Length | nextbar->Gran )+1)-bbar->Length;
						bit=FindFirstBit(ebar->Length-1,FALSE);
						ebar->Gran=Shr64((~0ULL),64 - bit);
					}
				} 

				//bar->Gran here < "bbar" MaxGran, so "bar" holds next biggest Gran after the bridge
				//we will try to adjust Extra Space requested by the bridge, analizing bar->Gran information
				if(ebar->Length) {
					while( ebar->Length >= (ebar->Gran+1) ){
						VOID*	p;
					//-----------------------

						if(!DevDb.RecordCount)break;

						bar=NULL;
						val=ebar->Gran+1;
						Status=DbeLocateKey(&DevDb,0,&val,&p,&v, &i);
						

						if(EFI_ERROR(Status)){
							if(!((Status==EFI_DBE_EOF) || (Status==EFI_DBE_BOF) || (Status==EFI_NOT_FOUND))){
								ASSERT_EFI_ERROR(Status);
								goto ExitLbl;
							}
						}
								
						Status=DbeGoToIndex(&DevDb,0,i,&bar);
						if(EFI_ERROR(Status)){
							if(!((Status==EFI_DBE_EOF) || (Status==EFI_DBE_BOF))){
								ASSERT_EFI_ERROR(Status);
								goto ExitLbl;
							}
						}

						//if DevDb (who has even sizes) has resource that smaller or equal
						//we will try to fill Extra Gap... 
						if((v == -1) && (bar!=NULL)){
							//Database sorted in ascending order. DbeLocateKey() function, parameter "v" tells how close the result is.
							//if DBE couldn't find exact match, it will return pointer at first element bigger than Parameter Passed.
							//There fore, if this is the case, we need to go down one index to get a smaller element than Parameter Passed.
							if(i>0){ 
								bar=NULL;
								Status=DbeGoToIndex(&DevDb,0,i-1,&bar);
								if(EFI_ERROR(Status)){
									if(!((Status==EFI_DBE_EOF) || (Status==EFI_DBE_BOF))){
										ASSERT_EFI_ERROR(Status);
										goto ExitLbl;
									}
								}
							} else break; //this will break "while(DevDb.RecordCount || BrgDb.RecordCount)" loop
						} //if(v==-1 && bar!=NULL)
						
						if(bar!=NULL && bar->Gran<=ebar->Gran){ 
							Status=AppendBarOrder(&DevDb,ResOrd,bar);
							ASSERT_EFI_ERROR(Status);
							if(EFI_ERROR(Status)) goto ExitLbl;
							
							//Adjust ebar->Length and Gran since we have filled out some extra space...
							ebar->Length-=bar->Length;
                            if(ebar->Length!=0){
    							bit=FindFirstBit(ebar->Length-1,FALSE);
				    			ebar->Gran=Shr64((~0ULL),64-bit);
                            } else break; //this will break "while( ebar->Length >= (ebar->Gran+1) )" loop
						} else break; //this will break "while( ebar->Length >= (ebar->Gran+1) )" loop

					} //while( ebar->Length >= (ebar->Gran+1)

					//if after all efforts we still have extra resources left
					//Mark ebar->Offset as 0xFF to notify routine which will programm the BARs
					//Not to toughch this one, but just add ebar->Length before next valid BAR. 

				    PCI_TRACE((TRACE_PCI," EBAR: Len=0x%lX;\t Gra=0x%lX;\t Ofs=0x%X; Owner [B%X|D%X|F%X] Type=%d\n",
				    ebar->Length, ebar->Gran, ebar->Offset, ebar->Owner->Address.Addr.Bus, 
				    ebar->Owner->Address.Addr.Device, ebar->Owner->Address.Addr.Function, ebar->Owner->Type));
                    if(ebar->Length!=0){
    					ebar->Offset=0xFF;
				    	ebar->Type=ResType+1;
					    ebar->DiscoveredType=ebar->Type;

    					Status=AppendItemLst((T_ITEM_LIST*)ResOrd, ebar);
				    	ASSERT_EFI_ERROR(Status);
					    if(EFI_ERROR(Status)) goto ExitLbl;
                    }  
				}//if(ebar->Length)
			}//else of "if(bar->Gran >= balign->MaxGran)"
		} else { //"if((bar!=NULL) && (bbar!=NULL))"
			//This case when we have only one type of resources most likely it would be regular device resources
			//But just in case do the check
			if(bbar==NULL) Status=AppendBarOrder(&DevDb,ResOrd,bar);
			else {
				ebar=NULL;
				//If we got only bridges (more than one) behind parent bridge we might got uneven alignment!
				//So we have to check if Granuilarity requirements satisfactory for them and padd resources if needed.
				if(BrgDb.RecordCount>1){
					UINT64  resgran;
					//---------------------
					PCI_TRACE((TRACE_PCI,"     Bridges ONLY found!!! \n"));
					brg=bbar->Owner;
					ext=(PCI_BRG_EXT*)(brg+1);
					balign=&ext->Align[ResType]; 

					bit=FindFirstBit(bbar->Length-1,FALSE);
					resgran=Shr64((~0ULL),64-bit);

					if(bbar->Gran>resgran){
						//get next record
						Status=DbeGoToIndex(&BrgDb,0,BrgDb.RecordCount-2,&nextbar);
						if(EFI_ERROR(Status)){ 
							if(!((Status==EFI_DBE_EOF) || (Status==EFI_DBE_BOF))){
								ASSERT_EFI_ERROR(Status);
								goto ExitLbl;
							}
						}
						//determine extra resource size... 
						ebar=&ext->Align[ResType].ExtraRes;
						ebar->Length=(( bbar->Length | nextbar->Gran )+1)-bbar->Length;
						if(ebar->Length!=0){
							bit=FindFirstBit(ebar->Length-1,FALSE);
							ebar->Gran=Shr64((~0ULL),64-bit);				
						}
					}//if(balign->MaxGran>balign->ResGran)
				}//if(BrgDb.RecordCount>1)
				Status=AppendBarOrder(&BrgDb,ResOrd,bbar);
				if(ebar!=NULL && ebar->Length){
					ebar->Offset=0xFF;
					ebar->Type=ResType+1;
					ebar->DiscoveredType=ebar->Type;
					PCI_TRACE((TRACE_PCI," EBAR: Len=0x%lX;\t Gra=0x%lX;\t Ofs=0x%X; Owner [B%X|D%X|F%X] Type=%d\n",
					ebar->Length, ebar->Gran, ebar->Offset, ebar->Owner->Address.Addr.Bus, 
					ebar->Owner->Address.Addr.Device, ebar->Owner->Address.Addr.Function, ebar->Owner->Type));

					Status=AppendItemLst((T_ITEM_LIST*)ResOrd, ebar);
					ASSERT_EFI_ERROR(Status);
					if(EFI_ERROR(Status)) goto ExitLbl;
				}				

				ASSERT_EFI_ERROR(Status);
			}
			if(EFI_ERROR(Status)) goto ExitLbl;
		}

	}//while(DevDb.RecordCount || BrgDb.RecordCount)

ExitLbl:	
	//Free Memory allocated... 
	FreeResDb(&DevDb);	
	FreeResDb(&BrgDb);

	//if there was an ERROR clear Bridge Resource Ortder Array.	
	if(EFI_ERROR(Status)){
		ClearItemLst((T_ITEM_LIST*)ResOrd,FALSE);
		PCI_TRACE((TRACE_PCI,"PciBus: OptimizeBrgResource() returning ERROR=%r\n", Status));
	}

	return Status;

}

VOID ClearBrgResources(PCI_DEV_INFO *Brg){
	EFI_STATUS			Status=0;
	PCI_DEV_INFO		*dev;
	PCI_BRG_EXT			*ext=(PCI_BRG_EXT*)(Brg+1);
	UINTN				i;
//-------------------------------

	for (i=0; i<ext->ChildCount; i++){
		dev=ext->ChildList[i];

		if((dev->Type==tPci2PciBrg || dev->Type==tPci2CrdBrg) )
			ClearBrgResources(dev);
	} //child loop
        
    //Once here that means all recourcive calls are done and 
    //all BridgeChilds Bridges - clean....      
    //Clear ThisBridge Res[], Pad[], Align[]...
    for(i=rtIo16; i<rtMaxRes; i++) {
        PCI_DEV_INFO    *owner;
        //----------------------
        owner=ext->Res[i].Owner;
        pBS->SetMem(&ext->Res[i], sizeof(PCI_BAR),0);
		ext->Res[i].Owner=owner;

        owner=ext->Align[i].ExtraRes.Owner; 
        pBS->SetMem(&ext->Align[i], sizeof(BRG_ALIGN_INFO),0);
		ext->Align[i].ExtraRes.Owner=owner;
#if HOTPLUG_SUPPORT			
        owner=ext->Pad[i].Owner; 
        pBS->SetMem(&ext->Pad[i], sizeof(PCI_BAR),0);
        ext->Pad[i].Owner=owner;
#endif
        if(ext->BarOrder[i].BarCount) ClearItemLst((T_ITEM_LIST*)&ext->BarOrder[i], FALSE);
    }    
}




//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   CalculateBrgResources()
//
// Description: The objective of this routine is to select the biggest
// possible Granularity/Alignment for the Bridge by adding all Child's
// resources of the same type together. 
//
// Input:
//  PCI_DEV_INFO    *Brg    Pointer to PCI Device Private Data structure.
//
// Output:	Nothing
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID CalculateBrgResources(PCI_DEV_INFO *Brg)
{
	EFI_STATUS			Status=0;
	PCI_DEV_INFO		*dev;
	PCI_BRG_EXT			*ext=(PCI_BRG_EXT*)(Brg+1);
	UINTN				i,j,k;
	PCI_BAR				*bar, *bbar;
	UINT8 				bit;
	BRG_RES_ORDER		*resord;
#if HOTPLUG_SUPPORT			
	PCI_BAR				*pbar;
#endif
	BRG_ALIGN_INFO		*balign;
	BOOLEAN				paddingappl;
    MRES_TYPE           LowResType=rtMaxRes;
//-----------------------------------------------
	//Tell what we are doing
	PCI_TRACE((TRACE_PCI,"++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++\n"));
    PCI_TRACE((TRACE_PCI,"PciBus: "));
    if(gPciOutOfRes) PCI_TRACE((TRACE_PCI," RE_"));
	PCI_TRACE((TRACE_PCI,"CalculateBrgResources() Bridge->[B%X|D%X|F%X] ---> BEGIN \n",
			Brg->Address.Addr.Bus, Brg->Address.Addr.Device, Brg->Address.Addr.Function));
	PCI_TRACE((TRACE_PCI,"++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++\n"));

    	//Init initial Alignment fields	for the special Bridge BARs
    	//every P2P brg has 4k IO and 1M MMMIO alignment
    	//Init Initial Granularity array
    	if(Brg->Type==tPciRootBrg){
    		//in case of Host Bridge Granularity Values should be provided by Root Brg
    		for(i=1; i<rtMaxRes; i++)	ext->Align[i].MinGran=1; //just don't care now
    	} else {
    		//in case of P2P Brg use default settings 
    		ext->Align[1].MinGran=P2P_BRG_IO_GRA;
    		ext->Align[2].MinGran=P2P_BRG_IO_GRA;
    		ext->Align[3].MinGran=P2P_BRG_MEM_GRA;
    		ext->Align[4].MinGran=P2P_BRG_MEM_GRA;
    		ext->Align[5].MinGran=P2P_BRG_MEM_GRA;
    		ext->Align[6].MinGran=P2P_BRG_MEM_GRA;
    	}
    
    	//Initialize fields in Bridge info Structure
    	ext->Res[rtIo16].Gran=P2P_BRG_IO_GRA;
    	ext->Res[rtIo32].Gran=P2P_BRG_IO_GRA;
    	ext->Res[rtMmio32].Gran=P2P_BRG_MEM_GRA;
    	ext->Res[rtMmio32p].Gran=P2P_BRG_MEM_GRA;
    	ext->Res[rtMmio64].Gran=P2P_BRG_MEM_GRA;
    	ext->Res[rtMmio64p].Gran=P2P_BRG_MEM_GRA;
    
    	//Init Bridge Bar offset fields
    	if(Brg->Type==tPci2PciBrg){
   		//For IO 16 Resources Decoded by the bridge
   		ext->Res[rtIo16].Offset=0x1C;
   		//For IO 32 Resources Decoded by the bridge
   		ext->Res[rtIo32].Offset=0x1C;
   		//For MMIO32 
   		ext->Res[rtMmio32].Offset=0x20;
   		//For MMIO32 PF 	
   		ext->Res[rtMmio32p].Offset=0x24;
   		//For MMIO64
   		ext->Res[rtMmio64].Offset=0x20; //P2PBridge doesnot have any MMIO64
   		//For MMIO64 PF
   		ext->Res[rtMmio64p].Offset=0x24;
   	} 
    
   	//Init Card Bus Bridge Bar offset fields
   	if(Brg->Type==tPci2CrdBrg){
   		//For IO 16 Resources Decoded by the bridge
   		ext->Res[rtIo16].Offset=0x2C;
   		//For IO 32 Resources Decoded by the bridge
   		ext->Res[rtIo32].Offset=0x34;
   		//For MMIO32 
   		ext->Res[rtMmio32].Offset=0x1C;
   		//For MMIO32 PF 	
   		ext->Res[rtMmio32p].Offset=0x24;
   		//For MMIO64
   		ext->Res[rtMmio64].Offset=0x1C; //P2Crd Bridge doesnot have any MMIO64
   		//For MMIO64 PF
   		ext->Res[rtMmio64p].Offset=0x24;//P2Crd Bridge doesnot have any MMIO64PF
   	} 

    if(gPciOutOfRes){	
//OUT_OF_RES!!                 
        //Get AmiOutOfResVar (suppose to be created by ROOT BRG Generic code or Custom HbCspAllocateResources())
        Status=AmiPciOutOfRes(&gPciOutOfResData, TRUE);
        ASSERT_EFI_ERROR(Status); //should not fail at that point!
       
        //gPciOutOfResData.Resource.Type can't be ASLRV_SPC_TYPE_BUS
        //Update resource type 
        if(gPciOutOfResData.Resource.Type==ASLRV_SPC_TYPE_IO) LowResType=rtIo16;

        if(gPciOutOfResData.Resource.Type==ASLRV_SPC_TYPE_MEM){
            if(gPciOutOfResData.Resource._GRA==32){
                LowResType=rtMmio32;
                if(gPciOutOfResData.Resource.TFlags.MEM_FLAGS._MEM!=ASLRV_MEM_UC)LowResType=rtMmio32p;
            }
            if(gPciOutOfResData.Resource._GRA==64){
                LowResType=rtMmio64;
                if(gPciOutOfResData.Resource.TFlags.MEM_FLAGS._MEM!=ASLRV_MEM_UC)LowResType=rtMmio64p;
            }
        }
    }

	//Start adding resources for all childs behind that bridge
	for (i=0; i<ext->ChildCount; i++){
		dev=ext->ChildList[i];

        //if we got Out Of resources condition call Platforn function to determine
        //priority list for devices Platform wants to IGNORE.
        //Pick just ONe device at a time.
        if(gPciOutOfRes && !gPciOutOfResHit && !dev->OutOfResRemove){ 
            Status=PciPortOutOfResourcesRemoveDevice(dev, gPciOutOfResData.Count, LowResType);
            if(!EFI_ERROR(Status)){
                gPciOutOfResHit=TRUE;
                dev->OutOfResRemove=TRUE;

                PCI_TRACE((TRACE_PCI,"!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n"));
	            PCI_TRACE((TRACE_PCI,"\nPciBus: OutOfRes Hit #%d!!! Removing Device [B%X|D%X|F%X]->",
			    gPciOutOfResData.Count, dev->Address.Addr.Bus, dev->Address.Addr.Device, dev->Address.Addr.Function));
                
                if(dev->PicIrqEntry!=NULL) PCI_TRACE((TRACE_PCI,"Slt #%d\n", dev->PicIrqEntry->SlotNum));
                else PCI_TRACE((TRACE_PCI,"Slt N/A\n"));
                PCI_TRACE((TRACE_PCI,"!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n"));

                //We must remove all it's functions also since f0 defines persence of the rest.
                if(IsFunc0OfMfDev(dev)&& dev->Type!=tPci2PciBrg) {
                    PCI_TRACE((TRACE_PCI,"       AND ALL IT's %d FUNCTIONS!!!\n",dev->FuncCount));                    
                    for(j=0;j<dev->FuncCount;j++){
                        dev->DevFunc[j]->OutOfResRemove=TRUE;    
                        DisableDeviceDecoding(dev->DevFunc[j], stDisableAll);   
                    }
                }
                //if we hit device from remove list - shut it down...
                DisableDeviceDecoding(dev, stDisableAll);
                if(dev->Type==tPci2PciBrg) DisableBridgeDecoding((PCI_BRG_INFO*)dev);
                
                //save OUT_OF_RES_VAR
                Status=AmiPciOutOfRes(&gPciOutOfResData, FALSE);

            }
        }

        if(dev->OutOfResRemove) continue;
		//here we have to check if the Child device is P2P brg - 
		//it requires a special handling
		if(dev->Type==tPci2PciBrg || dev->Type==tPci2CrdBrg)
			CalculateBrgResources(dev);
	} //child loop

	PCI_TRACE((TRACE_PCI,"=>>>Resource Requirements for Bridge->[B%X|D%X|F%X] :<<<=\n",
			Brg->Address.Addr.Bus, Brg->Address.Addr.Device, Brg->Address.Addr.Function));
	PCI_TRACE((TRACE_PCI,"ResType: 1=rtIo16; 2=rtIo32; 3=rtMmio32; 4=rtMmio32p; 5=rtMmio64; 6=rtMmio64p\n\n"));

	
	for(j=rtIo16; j<rtMaxRes; j++){
		//Init variables.
		paddingappl=FALSE;
		bbar=&ext->Res[j];
		balign=&ext->Align[j];
		resord=&ext->BarOrder[j];
		balign->MaxGran=bbar->Gran;

		Status=OptimizeBrgResource(Brg, j);
		ASSERT_EFI_ERROR(Status);		

		for(k=0; k<resord->BarCount; k++){
			bar=resord->BarList[k];
			//add children's resources to the bridge decoding
			if(bbar->Gran < bar->Gran)bbar->Gran=bar->Gran;	
			bbar->Length+=bar->Length;
			bbar->Type=bar->Type;
		}

#if HOTPLUG_SUPPORT	
		pbar=&ext->Pad[j];
		//if this is the bridge with hotplug capabilities it might supports Resource Padding
		//Apply padding and padding alignment if it is bigger than this bridge is currently requesting
		if(pbar->Length){
			if(pbar->Length > bbar->Length) bbar->Length = pbar->Length;
			if(bbar->Gran < pbar->Gran) bbar->Gran=pbar->Gran;
			bbar->Type=pbar->Type;	
			paddingappl=TRUE;
		}
#endif
		//if we have a card bus brg and hotplug is disabled we will APPLY default padding
		if(Brg->Type==tPci2CrdBrg && !paddingappl) {
			PCI_TRACE((TRACE_PCI,"->>>Applying CRD BUS Default Padding for Pci2CrdBrg [B%X|D%X|F%X]\n",
				Brg->Address.Addr.Bus, Brg->Address.Addr.Device, Brg->Address.Addr.Function));
			ApplyCrdPadding(Brg, j);
		}

		//if Brg have resource request
		balign->MaxGran=bbar->Gran;
		if(bbar->Length){
			if( (bbar->Length < (balign->MinGran + 1)) || ((bbar->Length & balign->MinGran)) )
				bbar->Length=(bbar->Length | balign->MinGran)+1;
			//Figure out Resource Delivered Granularity
			bit=FindFirstBit(bbar->Length-1,FALSE);
			balign->ResGran=Shr64((~0ULL),64-bit);
		}
		//Report Bridge Parameters
		PCI_TRACE((TRACE_PCI,"->ResType=%X; Len=%lX; Gran=%lX; MaxGran=%lX; ResGran=%lX; MinGran=%lX\n\n",
		j, bbar->Length, bbar->Gran, balign->MaxGran, balign->ResGran, balign->MinGran));
		PCI_TRACE((TRACE_PCI,"------------------------------------------------------------------------\n"));

	} //for(j=rtIo16; j<rtMaxRes; j++)..

	//Tell what we are doing
	PCI_TRACE((TRACE_PCI,"^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^\n"));
	PCI_TRACE((TRACE_PCI,"PciBus: CalculateBrgResources() Bridge->[B%X|D%X|F%X] ---> END \n",
			Brg->Address.Addr.Bus, Brg->Address.Addr.Device, Brg->Address.Addr.Function));
	PCI_TRACE((TRACE_PCI,"^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^\n\n"));

	//We did it ... EXIT!
}

//================================================
//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   NewDevice()
//
// Description: Allocats Space nedded for New PCI_Device Instance and inits
// some of it's Fields
//
// Input:
//  BOOLEAN         BrgDevice   Indicator that New Device is a BRIDGE Device.  
//  PCI_CFG_ADDR    *DevArrd	Device Address on PCI Bus.
//
// Output:	PCI_DEV_INFO*
//  Pointer to the Created PCI Device Private Data structure.
//	NULL, if there was an ERROR.
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

PCI_DEV_INFO* NewDevice(BOOLEAN BrgDevice, PCI_CFG_ADDR *DevAddr)
{
	UINTN			i;
	PCI_DEV_INFO	*dev;
	PCI_BRG_EXT		*ext;
//------------------------------------
  	PCI_TRACE((TRACE_PCI,"\n==========================================================================\n"));
	if(BrgDevice)i=sizeof(PCI_BRG_INFO);
	else i=sizeof(PCI_DEV_INFO);

	dev=MallocZ(i);
	if(!dev) return dev;

	//Specify Owner for BusSpecific Override Protocol
	dev->BusOvrData.Owner=dev;	
#if ((defined EFI_SPECIFICATION_VERSION) && (EFI_SPECIFICATION_VERSION >= 0x2001F))
    dev->LoadFileData.Owner=dev;	
#endif
    dev->Signature=AMI_PCI_SIG;
    dev->MajorVersion = PCI_BUS_MAJOR_VER;
	dev->MinorVersion = PCI_BUS_MINOR_VER;
	dev->Revision = PCI_BUS_REVISION;

	//init some fields which must not be ZERO
	for(i=0; i<PCI_MAX_BAR_NO+1; i++)dev->Bar[i].Owner=dev;
	if(DevAddr){
		dev->Address.ADDR=DevAddr->ADDR;	
		dev->Address.Addr.Register=0;
	} else dev->Address.ADDR=0;	

    //Initialize some static fields
	if(BrgDevice){
		dev->Type=tPci2PciBrg;
		ext=(PCI_BRG_EXT*)(dev+1);	
		for(i=0; i<rtMaxRes; i++) {
			ext->Res[i].Owner=dev;
			ext->Align[i].ExtraRes.Owner=dev;
		}
	} else dev->Type=tPciDevice;

	return dev;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   BridgeAddChild()
//
// Description: Adds Pointer at the child PCI Device to the "Bridge" 
// T_ITEM_LIST Child List Structure of the BRG_EXT.
// some of it's Fields
//
// Input:
//  PCI_DEV_INFO    *Brgidge    Pointer to PCI Device Private Data structure
//                              of the Parent Bridge.
//  PCI_DEV_INFO    *Child      Pointer to PCI Device Private Data structure.
//                              of the Child Device.
//
// Output:	EFI_STATUS
//  EFI_SUCCESS             When everything is going on fine!
//  EFI_OUT_OF_RESOURCES    When system runs out of resources.
// 
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS BridgeAddChild(PCI_DEV_INFO *Bridge,PCI_DEV_INFO *Child)
{
	PCI_BRG_EXT		*ext=(PCI_BRG_EXT*)(Bridge+1);
//-------------------------------------------------
	return AppendItemLst((T_ITEM_LIST*)&ext->InitialCount,Child);
}


//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   InitDeviceData()
//
// Description: Initializes missing fields in PCI_DEV_INFO structure.
//
// Input:
//  PCI_DEV_INFO    *Dev    Pointer to PCI Device Private Data structure
//                          to initialize.
//
// Output:	EFI_STATUS
//  EFI_SUCCESS             When everything is going on fine!
//  EFI_OUT_OF_RESOURCES    When system runs out of resources.
//  EFI_DEVICE_ERROR        When driver fails access PCI Bus.
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS InitDevData(PCI_DEV_INFO *Dev, PCI_DEV_INFO *Parent, UINT32 VenDevId, UINT32 ClassCodes, PCI_DEV_INFO *Func0){
    EFI_STATUS      Status;
	PCI_CFG_ADDR	addr;
//-------------------------
    //Get CMD Register's safe value per UEFI 2.1 spec
    addr.ADDR=Dev->Address.ADDR;

	Dev->ParentBrg=Parent;
    Dev->DevVenId.DEV_VEN_ID=VenDevId;
    Dev->Class.DEV_CLASS=ClassCodes;				
    Dev->HostData=Parent->HostData;
    Dev->RbIo=Parent->RbIo;
    Dev->Func0=Func0;

    //If (Func0==NULL && FuncCount==0) function is a single function device, following fields are not used and reserved;
    //If (Func0!=NULL && FuncCount==0) function is one of the Func1..Func7 of multi-func device, Func0 points on DevFunc0;
    //If (Func0!=NULL && (FuncCount!=0 || FuncInitCnt!=0)) function is Func0 of multyfunc device DevFunc holds pointers at all other Func1..7 found yet

    //If (Func0==NULL && FuncCount!=0) Illehgal combination - reserved!
    if(Func0!=NULL){
        if (Func0!=Dev){
            //This is func 1..7 of the device... add it to the list.
            Status=AppendItemLst((T_ITEM_LIST*)&Func0->FuncInitCnt,Dev);
            ASSERT_EFI_ERROR(Status)
            if(EFI_ERROR(Status)) return Status;
        } else {
            //This is Func 0 if the device.. init Func0->FuncInitCnt with 8 
            Func0->FuncInitCnt=8;
        }
    }

    addr.Addr.Register=PCI_CMD;
    Status=PciCfg16( Dev->RbIo, addr, FALSE, &Dev->CmdReg.CMD_REG);
    ASSERT_EFI_ERROR(Status)
    if(EFI_ERROR(Status)) return Status;

	Status=MakePciDevicePath(Dev);
    if(EFI_ERROR(Status)) return Status;

    Status=PciPortSkipThisDevice(Dev);
    if(!EFI_ERROR(Status)){
        PCI_TRACE((TRACE_PCI,"PciBus: Device @ [B%X|D%X|F%X], VID=%X, DID=%X SKIPPED from enumeration.\n\n", 
            Dev->Address.Addr.Bus, Dev->Address.Addr.Device, Dev->Address.Addr.Function,
            Dev->DevVenId.VenId, Dev->DevVenId.DevId));
        Dev->SkipDevice=TRUE;
    }else Status=EFI_SUCCESS;

    return Status;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   EnumerateBus()
//
// Description: Enumerate the PCI BUSes behind the "ParentBrg" and determine 
// how much resources nedded for all its Child devices.
//
// Input:
//  PCI_DEV_INFO    *ParentBrg  Pointer to PCI Device Private Data structure
//                              of the Parent Bridge.
//
// Output:	EFI_STATUS
//  EFI_SUCCESS             When everything is going on fine!
//  EFI_OUT_OF_RESOURCES    When system runs out of resources.
//  EFI_DEVICE_ERROR        When driver fails access PCI Bus.
// 
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS EnumerateBus(PCI_DEV_INFO *ParentBrg)
{
	EFI_STATUS		Status, Status1=EFI_NOT_FOUND;
	PCI_CFG_ADDR	pcidev;
	BOOLEAN			mf,ari; //multi-function flag; ARI Flag
	UINT32			id, cc; //Device ID Vendor ID reg
	UINT8			ht; //Header type reg
	PCI_BRG_EXT		*ext, *parext;
	PCI_DEV_INFO	*dev, *func0;
	UINT8			omb=0;
#if PCI_DEV_REVERSE_SCAN_ORDER
	UINT8            DevBuff;
#endif
//----------------------------------	
    PROGRESS_CODE(DXE_PCI_BUS_ENUM);
	//Root Bridges Will have Same Number for Primary and  Secondary bus
	pcidev.ADDR=PCI_VID;
	parext=(PCI_BRG_EXT*)(ParentBrg+1);
	pcidev.Addr.Bus=(UINT8)parext->Res[rtBus].Base;
    func0=NULL;
    ari=FALSE;

	for(pcidev.Addr.Device=0; pcidev.Addr.Device<=PCI_MAX_DEVICE; pcidev.Addr.Device++){
#if PCI_DEV_REVERSE_SCAN_ORDER
        DevBuff = pcidev.Addr.Device;
        pcidev.Addr.Device = PCI_MAX_DEVICE - pcidev.Addr.Device;
#endif
        //if ARI Detected and Enabled we should scan all devices and functions 
        //but in ARI Mode Dev0..31 and Func0..7 will be translted for PCIe as Dev0 Func 0...255 
        //So Func0 must be the same as we have detected when started from Actual Function 0
        //And we should not reset MF flag for ARI device when we reach Func 7 of the device. 
        if(ari == FALSE){
            mf=FALSE;  
            func0=NULL;
        }

		for(pcidev.Addr.Function=0;  pcidev.Addr.Function<=PCI_MAX_FUNC; pcidev.Addr.Function++){
			//read devid-vendid register pare,
			id=0;
			pcidev.Addr.Register=PCI_VID;

			///
            /// A config write is required in order for the device to re-capture the Bus number,
            /// according to PCI Express Base Specification, 2.2.6.2
            /// Write to a read-only register VendorID to not cause any side effects.
            ///
			Status=PciCfg32(ParentBrg->RbIo,pcidev,TRUE,&id);

			Status=PciCfg32(ParentBrg->RbIo,pcidev,FALSE,&id);	
			if(EFI_ERROR(Status)) return Status; //Error happend - can't continue
			//Check if all Ones  
#if PCI_EXPRESS_SUPPORT
			if( (id == 0xFFFFFFFF)&& //oinly if first attemt of CFG read did not find anything
                (ParentBrg->PciExpress!=NULL) && //and device is PCIe capable 
#if PCI_DEV_REVERSE_SCAN_ORDER
                (DevBuff==0) && (pcidev.Addr.Function==0) && //for PCIe dev0 func0 is only option
#else
                (pcidev.Addr.Device==0) && (pcidev.Addr.Function==0) && //for PCIe dev0 func0 is only option
#endif
                (ParentBrg->PciExpress->PcieCap.SlotImpl)) //and we have a slot there...
            {
                //Some cards does not reply on configuration transactions 
                //for some time after opening config space behind the bridge.
                //If slot is implemented behind the bridge -
                //doiblecheck if card present using PCIe facilities (SLOT_STATUS reg)
                //we will save time on skipping DEV 1..31 though
                Status=PcieDoubleCheckCard(ParentBrg,&pcidev,&id);
                ASSERT_EFI_ERROR(Status);     
            } 
#endif
			if(id == 0xFFFFFFFF || id==0){
				if (!mf)break;	//devX.fun0.reg=0 returns 0xFFFFFFFF nothing is there 
				else continue;  //if device was identified as multifunc keep scanning
			}	
			//here we got something alive there
            Status1=EFI_SUCCESS;
			ht=0;
			//read the HeaderType Reg
			pcidev.Addr.Register=EFI_FIELD_OFFSET(PCI_COMMON_REG,HeaderType);
			Status=PciCfg8(ParentBrg->RbIo,pcidev,FALSE,&ht);	
			if(EFI_ERROR(Status)) return Status; //Error happend cant continue
            
            if(ari==FALSE){    
    			if(pcidev.Addr.Function==0)	{
                    if(ht & HDR_TYPE_MULTIFUNC)mf=TRUE; //this is multifunc device 
                }
            }
    
    	    ht&=3;

			//Get the class code and revision Id
			pcidev.Addr.Register=PCI_RID;  //Rev ID and Class  Code
			Status=PciCfg32(ParentBrg->RbIo,pcidev,FALSE,&cc);
			if(EFI_ERROR(Status)) return Status; //Error happend can't continue

			switch (ht){
				case HDR_TYPE_DEVICE	: 
					//Allocate Space to accomodate found device
					dev=NewDevice(FALSE,&pcidev);
					if(!dev) return EFI_OUT_OF_RESOURCES; 

                    if((ari==FALSE) && (mf) && (pcidev.Addr.Function==0))func0=dev;
                    Status=InitDevData(dev, ParentBrg, id, cc, func0);
					if(EFI_ERROR(Status)) goto EEXIT;
					//Test the class code to mark host brg device
					if( dev->Class.SubClassCode==0 && 
                        dev->Class.BaseClassCode==6 &&
						dev->Class.ProgInterface==0 )
                    {
                        dev->Type=tPciHostDev;
                    }
					//Check if we got a debug port here
#if EFI_DEBUG || USB_DEBUG_TRANSPORT
					if( 
                        (gDbgPortHob && (
							(gDbgPortInfo.DebugPortType==USB2_EHCI) ||
							(gDbgPortInfo.DebugPortType==USB2_UHCI) ||		
							(gDbgPortInfo.DebugPortType==USB2_OHCI)	) 
                        ) && (
					    	(pcidev.Addr.Function==gDbgPortInfo.Address.Addr.Function) && 
					   		(pcidev.Addr.Device==gDbgPortInfo.Address.Addr.Device) && 
							(pcidev.Addr.Bus==gDbgPortInfo.Address.Addr.Bus)
						)
					)
					{
						dev->Bar[gDbgPortInfo.BarIndex].Length	=gDbgPortInfo.Length;
						dev->Bar[gDbgPortInfo.BarIndex].Gran	=gDbgPortInfo.Length-1;
						dev->Bar[gDbgPortInfo.BarIndex].Offset	=gDbgPortInfo.BarOffset;
						dev->Bar[gDbgPortInfo.BarIndex].Type	=gDbgPortInfo.BarType;
						dev->DebugPort=TRUE;
						dev->Enumerated=TRUE;
						dev->Discovered=TRUE;
					} 
                    else 
#endif
					{
                        if(dev->SkipDevice){
                            //if porting hook tells us to skip this device.
                            //We will just start it 
                            dev->Assigned=TRUE;
                            dev->Discovered=TRUE; 
                            dev->Enumerated=TRUE;
                            dev->Incompatible=TRUE;
                        } else {                                            
                            //Vars we need here
                            UINTN   i;
                            UINT64  tl32, tl64, tlIO;
                            //-------------
    						//make sure - Device is disabled
				    		Status=DisableDeviceDecoding(dev, stMemIoSpace);
    						if(EFI_ERROR(Status)) goto EEXIT;

    						//Try to determine how mutch resources Device consumes
				    		Status=QueryPciDevice(dev);
						    if(EFI_ERROR(Status)) goto EEXIT;

                            //Find IRQ Routing Entry for discovered device
                            Status = FindDevIrqEntry(dev);
                     
                            //This workaround done for PCI Compliance Test... 
                            //32 bit, 64bit and IO resource request excides certain length. 
                            for(i=0,tlIO=0,tl32=0,tl64=0; i<PCI_MAX_BAR_NO+1; i++){
                                if((dev->Bar[i].Type!=tBarUnused) && (dev->Bar[i].Length!=0) ){
                                    switch (dev->Bar[i].Type){
                                        case tBarIo16:
                                        case tBarIo32:
                                            tlIO+=dev->Bar[i].Length;
                                            break;
                                        case tBarMmio32:
                                        case tBarMmio32pf:
                                            tl32+=dev->Bar[i].Length;
                                            break;
                                        case tBarMmio64:
                                        case tBarMmio64pf:
                                            tl64+=dev->Bar[i].Length;
                                    }//switch
                                }//if not empty
                            } //for

                            //Check if Calculated total resource request falls in acceptable range
                            if( (tlIO>=PCI_DEVICE_IO_RESOURCE_THRESHOLD) ||
                                (tl32>=PCI_DEVICE_32BIT_RESOURCE_THRESHOLD) ||
                                (tl64>=PCI_DEVICE_64BIT_RESOURCE_THRESHOLD)
                                )
                            {
                                //Zero out all BARs and ROM BAR.
                                for(i=PCI_BAR0, id=0; i<PCI_CAPP; i+=4){
                               	    pcidev.Addr.Register=(UINT8)i;
                                    Status=PciCfg32(ParentBrg->RbIo,pcidev,TRUE,&id);
            	                    if(EFI_ERROR(Status)) goto EEXIT;
                                }
                                //Clear CMD_REG
                                pcidev.Addr.Register=(UINT8)PCI_CMD;
                                Status=PciCfg16(ParentBrg->RbIo,pcidev,TRUE,(UINT16*)(&id));
      	                       if(EFI_ERROR(Status)) goto EEXIT;

                                //Clear All collected resource information for that device
                                //to avoid them to be added to the system's resource request.
                                    for(i=0; i<PCI_MAX_BAR_NO+1; i++){
                                    dev->Bar[i].Type=tBarUnused;
                                    dev->Bar[i].DiscoveredType=tBarUnused;    
                                    dev->Bar[i].Length=0;
                                    dev->Bar[i].Gran=0;
                                }
                                //Setting Flags telling not to install PciIo protocol instance
                                //on this device and don't touch device at all! 
                                dev->Started=TRUE;
                                dev->Assigned=TRUE;
                                dev->Discovered=TRUE; 
                                dev->Enumerated=TRUE;
                                dev->RomBarError=TRUE;
                                dev->Incompatible=TRUE;
                            } //if .. Device requests too much resources.

#if PCI_EXPRESS_GEN2_SUPPORT
                            //Check if we have to enable ARI here.
                            if(IsFunc0(dev)){
                                Status=Pcie2CheckAri(dev,&mf,&ari);
        					    if(EFI_ERROR(Status)) goto EEXIT;
                            }
#endif
                           	dev->Enumerated=TRUE;
                    
                        }
					}
					break;

				case HDR_TYPE_P2P_BRG	: 
				case HDR_TYPE_P2C_BRG	: 
					//Allocate space for new bridge struct
					dev=NewDevice(TRUE,&pcidev);
                    if(!dev) return EFI_OUT_OF_RESOURCES;

					ext=(PCI_BRG_EXT*)(dev+1);	
					if(ht==HDR_TYPE_P2C_BRG)dev->Type=tPci2CrdBrg;
					
					//Record some properties of the discovered device
                    if(pcidev.Addr.Function==0 && mf)func0=dev;
                    Status=InitDevData(dev, ParentBrg, id, cc, func0);
					if(EFI_ERROR(Status)) goto EEXIT;

                    if(dev->SkipDevice){
                        //if porting hook tells us to skip this device.
                        //We will just start it 
                        dev->Assigned=TRUE;
                        dev->Discovered=TRUE; 
                        dev->Enumerated=TRUE;
                        dev->Incompatible=TRUE;
                    } else {
                        //make sure - Device is disabled
                        if(dev->Type == tPci2PciBrg) DisableBridgeDecoding((PCI_BRG_INFO*)dev);
				    	Status=DisableDeviceDecoding(dev, stMemIoSpace);
    					if(EFI_ERROR(Status)) goto EEXIT;
					
					    //Try to determine how mutch resources Device consumes
					    Status=QueryPciDevice(dev);
					    //this call must fill Bar[0..1] 
					    if(EFI_ERROR(Status)) goto EEXIT;
                    }
                    
#if PCI_EXPRESS_GEN2_SUPPORT
                    //Check if we have to enable Ari in case of 
                    if((dev->PciExpress!=0) && (PcieIsDownStreamPort(dev)==FALSE)){

#if PCI_BUS_SKIP_BRG_RECURSIVELY
                        if(dev->SkipDevice==0){
#endif
                            Status=Pcie2CheckAri(dev,&mf,&ari);
                            if(EFI_ERROR(Status)) goto EEXIT;

#if PCI_BUS_SKIP_BRG_RECURSIVELY
                        }
#endif
                    }
#endif

                    //Find PCI Bus Xlat entry corresponded to this bridge
                    Status=FindBridgeXlatEntry(dev, ext);
                    //Find IRQ Routing Entry for discovered device
                    Status = FindDevIrqEntry(dev);

                    //KeepUpdating NewBrg
                    //Programm Primary and Secondary I/F Bus Numbers
                    //To store Bridge SecondaryBusNo and SubordinateBusNo we will use PCI_BAR structure
                    //Device.Address.Addr.Bus will have PrimaryBusNo 
                    //Bar.Base will be used for SecondaryBusNo and 
                    //Bar.Base +Bar.Length-1 will give us SubordinateBusNo. 
                    //So Record the Secondary Bus we will use for this Bridge..  
                    
                    //Set Bridge Bus register Proprties
                    ext->Res[rtBus].Type=tBarBus;
                    ext->Res[rtBus].Offset=PCI_BRIDGE_SECONDARY_BUS_REGISTER_OFFSET; //SecondaryBusOffset

                    //If fixed bus assignment we should handle situation differenty
                    if( FixedBusAssign && ext->XlatTblEntry != NULL ){
                        //get sceondary bus number from BusXlat Table
                        mMaxBusFound = ext->XlatTblEntry->BusBuild;
                    } else {
    					//Bridge has been found just increase bus counter
				    	mMaxBusFound++;
					}

                    ext->Res[rtBus].Base = mMaxBusFound;					
                    //Set Sub Bus # for this bridge to max # available
				    ext->Res[rtBus].Length=mMaxBusScan-ext->Res[rtBus].Base;
                    if(ext->XlatTblEntry){
                        ext->XlatTblEntry->BusRun=mMaxBusFound;
                    }
        
                    if(mMaxBusReport < mMaxBusFound) mMaxBusReport=mMaxBusFound;

#if PCI_BUS_SKIP_BRG_RECURSIVELY 
                    if(dev->SkipDevice==0){
#endif
					Status=MapBridgeBuses(dev);
#if PCI_BUS_SKIP_BRG_RECURSIVELY 
                    }
#endif
					ASSERT_EFI_ERROR(Status);
					if(EFI_ERROR(Status)) goto EEXIT;

//Exclude Hotplug support 
#if HOTPLUG_SUPPORT
					omb=mMaxBusFound; //save the old number of buses found only in case of hotplug
					//this will try to init Root HPC siting behind this bridge if any...
#if PCI_BUS_SKIP_BRG_RECURSIVELY 
                    if(dev->SkipDevice==0){
#endif
					Status=CheckRootHotplug(dev);
#if PCI_BUS_SKIP_BRG_RECURSIVELY 
                    }
#endif
					ASSERT_EFI_ERROR(Status);
					//if root hpc init fail for any reason we just must keep going
#endif

					//Enter a Recursive call in both cases 
                    //Only in case Device is identifyes itself as Bridge
					if(dev->Class.BaseClassCode == PCI_CL_BRIDGE){
#if PCI_BUS_SKIP_BRG_RECURSIVELY 
                        if(dev->SkipDevice==0){
#endif
                            Status = EnumerateBus(dev);
#if PCI_BUS_SKIP_BRG_RECURSIVELY 
                        }
#endif

                        if(Status!=EFI_NOT_FOUND){
    					    ASSERT_EFI_ERROR(Status);
				    	    if(EFI_ERROR(Status)) goto EEXIT;
                        } else Status=EFI_SUCCESS;
                        //After we come back from enumeration update all IRQ Tables entries 
                        //From BusBuild to BusRun (actual bus number)
                        if(ext->XlatTblEntry){
                            UpdateIrqTables(ext->XlatTblEntry);
                            PCI_TRACE((TRACE_PCI,"PciBus: Update Bus# for Brg  [B%X|D%X|F%X] - Bld %X -> Run %X\n", 
                            dev->Address.Addr.Bus,dev->Address.Addr.Device,dev->Address.Addr.Function, 
                            ext->XlatTblEntry->BusBuild,ext->XlatTblEntry->BusRun));                
                        }
                    }

//-------------------------------------------------------------------------
//Exclude Hotplug support 
#if HOTPLUG_SUPPORT
					//here if this is the bridge who has hotplugable slots
					//we must appy resource padding to it
					if(dev->HotPlug){
#if PCI_BUS_SKIP_BRG_RECURSIVELY 
                        if(dev->SkipDevice==0){
#endif
						Status=GetHpbResPadding(dev);
						
						//Here we come with information about resources padding
						//dev->Hotplug->Padd[rtBus].Length will have Bus numbers needed to pad for this bridge
						//mMaxBusFound will have number of buses actualy present behind this bridge
						//take care of buses now the rest of resources will be taken care of when
						//CalculateBridge resources will be called
						if(ext->PaddAttr==EfiPaddingPciBus){
                            //EIP 19106 If 1 Bus set to padding in Setup it did not do the padding.
							if(ext->Pad[rtBus].Length && ext->Pad[rtBus].Length>mMaxBusFound-ext->Res[rtBus].Base){
								mMaxBusFound=omb+(UINT8)ext->Pad[rtBus].Length;							
							}
						}
#if PCI_BUS_SKIP_BRG_RECURSIVELY 
                        }
#endif

					}
#endif
//-------------------------------------------------------------------------
					//when we come back from EnumerateBus and have applyed padding for Bus Resources 
					// - mMaxBusFound will effectively reflect subordinate bus number for this Bridge so...

                    //If fixed bus assignment we should handle situation differenty
                    if( FixedBusAssign && 
                        (ext->XlatTblEntry != NULL) &&
                        (ext->ItemNumber < gPciBusDb.ItemCount-1))
                    {
                        UINT8   busnum;
                    //-------------------------                        
                        busnum=FindNextSameLevelBrgXlatEntry(ext);                        

                        if( mMaxBusFound <= busnum )mMaxBusFound = busnum; 
                        else {
                            //With Fixed Bus allocation this condition signifies an error if we here
                            //that means that we have found more buses than allowed buy fixed bus layout
                            //So scream about it.
                           	PCI_TRACE((TRACE_PCI,"PciBus: Can't apply Fixed Buses for the Bridge @ [B%X|D%X|F%X]:\n  Actual MAX Bus Discovered =%X; Proposed MAX Bus in BusXlatTbl = %X\n", 
                        	        dev->Address.Addr.Bus, dev->Address.Addr.Device, dev->Address.Addr.Function, 
                                    mMaxBusFound, busnum));
                            ASSERT(FALSE);                            
                        }

                    } 
   					ext->Res[rtBus].Length=mMaxBusFound-ext->Res[rtBus].Base+1;
    
                    if(mMaxBusReport < mMaxBusFound) mMaxBusReport=mMaxBusFound;
 						
#if PCI_BUS_SKIP_BRG_RECURSIVELY 
                    if(dev->SkipDevice==0){
#endif
					Status=SetSubBus(dev,mMaxBusFound);
#if PCI_BUS_SKIP_BRG_RECURSIVELY 
                    }
#endif

					ASSERT_EFI_ERROR(Status);
					if(EFI_ERROR(Status)) goto EEXIT;

//-------------------------------------------------------------------------
//Enables PCI Express Handling only if PCI Express Base is Defined and !=0
#if PCI_EXPRESS_SUPPORT
					//Now when we come back we can power off PCIExpress Empty slot to make it 
					//cpable for Hot Plugging
                    if(dev->PciExpress!=NULL){
                        //Check if we hit a DOWN STREAM type device,
                        //and Initialize PciE link properties if so.
                        if(PcieIsDownStreamPort(dev)){
                            Status=PcieInitLink(dev);
                            ASSERT_EFI_ERROR(Status);
						    if(EFI_ERROR(Status)) goto EEXIT;
                        } else {
                            //Add to the gPcieEpLst Orphan Upstream Ports of Switches and PCIe2PCI bridgers.
        					if((dev->PciExpress->PcieCap.PortType==PCIE_TYPE_UPS_PORT) ||
                               (dev->PciExpress->PcieCap.PortType==PCIE_TYPE_PCIE_PCI)){

                                Status=AppendItemLst(&gPcieEpList, dev);
                                PCI_TRACE((TRACE_PCI,"PciE: Adding Device [B%X|D%X|F%X] to gPcieEpList[%d]\n",
                                dev->Address.Addr.Bus,dev->Address.Addr.Device, dev->Address.Addr.Function, gPcieEpList.ItemCount));
                                ASSERT_EFI_ERROR(Status);
						        if (EFI_ERROR(Status)) goto EEXIT;
                            }
                        }
                    }
#endif
//-------------------------------------------------------------------------
					//Finally we got here this bridge is done for now!!! we will use 
					//information collected, when we will programm the resources 
                    dev->Enumerated=TRUE;
				break;

				default	: 
					Status=EFI_UNSUPPORTED;
					ASSERT_EFI_ERROR(Status);
					return Status;
			} //switch;
			//Now update ParentBridge ChildList and Count
			Status=BridgeAddChild(ParentBrg,dev);
			ASSERT_EFI_ERROR(Status);
			if(EFI_ERROR(Status)) goto EEXIT;
			//and so on
			if( !mf ) break;
		} //function loop
#if PCI_DEV_REVERSE_SCAN_ORDER
        pcidev.Addr.Device=DevBuff;
#endif
	} //device loop
    return Status1;
///////////////////////////////////////////
//Emergency Exit Label
EEXIT:
	if(dev){
		if(dev->PciExpress){
            if(dev->PciExpress->Pcie2) pBS->FreePool(dev->PciExpress->Pcie2);
            if(dev->PciExpress->VcData) {
                if(dev->PciExpress->VcData->VcCount)ClearItemLst((T_ITEM_LIST*)&dev->PciExpress->VcData->InitCnt, TRUE);
                pBS->FreePool(dev->PciExpress->VcData);
            }
            if(dev->PciExpress->SriovData) pBS->FreePool(dev->PciExpress->SriovData);
            if(dev->PciExpress->AriData) pBS->FreePool(dev->PciExpress->AriData);
            if(dev->PciExpress->AcsData) pBS->FreePool(dev->PciExpress->AcsData);
            if(dev->PciExpress->AtsData) pBS->FreePool(dev->PciExpress->AtsData);
            if(dev->PciExpress->RcLnkData) pBS->FreePool(dev->PciExpress->RcLnkData);
            if(dev->PciExpress->Pcie3) pBS->FreePool(dev->PciExpress->Pcie3);
            
            pBS->FreePool(dev->PciExpress);
        }

		if(dev->PciX) pBS->FreePool(dev->PciX);
		if(dev->HotPlug)pBS->FreePool(dev->HotPlug);
		pBS->FreePool(dev);
	}
	return Status;

}


//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   ProgramBar()
//
// Description: Programm PCI BAR Register with the Resource Address 
// provided by the "bar" parameter.
//
// Input:
//  PCI_BAR         *bar    Pointer at PCI BAR register information
//
// Output:	EFI_STATUS
//  EFI_SUCCESS             When everything is going on fine!
//  EFI_OUT_OF_RESOURCES    When system runs out of resources.
//  EFI_DEVICE_ERROR        When driver fails access PCI Bus.
// 
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS ProgramBar(PCI_BAR	*bar)
{
	EFI_STATUS	Status=0;
	PCI_CFG_ADDR	addr;
	PCI_DEV_INFO	*owner=bar->Owner;
//------------------------------------
	addr.ADDR=bar->Owner->Address.ADDR;
	addr.Addr.Register=bar->Offset;
    addr.Addr.ExtendedRegister=bar->ExtOffset;

#if EFI_DEBUG || USB_DEBUG_TRANSPORT
	if(owner->DebugPort){
		gDbgPortInfo.BaseAddress=bar->Base;		
		Status=gDbgPortHob->SetDebugPortResources(gDbgPortHob, pBS, &gDbgPortInfo);
		ASSERT_EFI_ERROR(Status);
		owner->Assigned=TRUE;
		return Status;
	}	
#endif

	PCI_TRACE((TRACE_PCI,"PciBus: Device [B%X|D%X|F%X] Type=%X Bar.Offs=%Xh, Bar.Type=%d \n  Assigned Base=%lX, Size=%lX \n", 
	owner->Address.Addr.Bus, owner->Address.Addr.Device,
	    owner->Address.Addr.Function, owner->Type, 
        ((bar->ExtOffset==0) ? bar->Offset : bar->ExtOffset), 
        bar->Type, bar->Base, bar->Length));
    //EIP 26787 +
    //Forgot to exclude P2P Bridge ROM BAR, it belongs to primary interface!
	//if(owner->Type==tPci2PciBrg && (bar->Offset > 0x14 ){
    if(owner->Type==tPci2PciBrg && ( (bar->Offset > PCI_BAR1) && (bar->Offset < PCI_EROM) ) ){
    //EIP 26787 -

		//we got special P2P bridge BAR 
		switch (bar->Type){
			case tBarIo16 :
			case tBarIo32 :
				Status=EnableBridgeIoDecoding(owner, (UINT64)bar->Base, (UINT64)bar->Length);
				//if(EFI_ERROR(Status)) return Status;
				break;

			case tBarMmio32:
			case tBarMmio64:
				Status=EnableBridgeMmioDecoding(owner, (UINT64)bar->Base, (UINT64)bar->Length);
				//if(EFI_ERROR(Status)) return Status;
				break;
			
			case tBarMmio32pf:
			case tBarMmio64pf:
				Status=EnableBridgePfmmDecoding(owner, (UINT64)bar->Base, (UINT64)bar->Length);
				//if(EFI_ERROR(Status)) return Status;
				break;
		}//switch
	
	} else {
		if(owner->Type==tPci2CrdBrg && bar->Offset > PCI_BAR0 ){
			//here goes special Memory and IO windows of CardBus Bridge
			UINT32 	buffer=(UINT32)bar->Base;
		//--------------------
			Status=PciCfg32(owner->RbIo,addr,TRUE,(UINT32*)&buffer); //Base 

			addr.Addr.Register+=4; //Limit
			buffer=(UINT32)(bar->Base+bar->Length-1);
			Status=PciCfg32(owner->RbIo,addr,TRUE,(UINT32*)&buffer); 

			//Program Brg Control Reg to notify that Bridge Mem Window is PF
			if(bar->Type==tBarMmio32pf || bar->Type==tBarMmio64pf){

				addr.Addr.Register=PCI_BRIDGE_CONTROL_REGISTER_OFFSET;
				Status=PciCfg16(owner->RbIo,addr,FALSE,(UINT16*)&buffer);
				
				if(bar->Offset==0x1C) buffer|=BIT08;	//Memory Window 1 is PF		
				if(bar->Offset==0x24) buffer|=BIT09;	//Memory Window 2 is PF		

				Status=PciCfg16(owner->RbIo,addr,TRUE,(UINT16*)&buffer);
			}
		} else {
			//do regular device BAR programming
			UINT64	buffer=bar->Base;
		//--------------------
			if(bar->DiscoveredType == tBarMmio64 || bar->DiscoveredType == tBarMmio64pf)
				Status=PciCfg64(owner->RbIo,addr,TRUE,&buffer);
			else Status=PciCfg32(owner->RbIo,addr,TRUE,(UINT32*)&buffer);
		}
	}
	return Status;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   AssignBridgeResources()
//
// Description: Sorts, Aligns, and Programms Resources requested by devices 
// residing behind its Parent PCI Bridge - "Brg".
//
// Input:
//  PCI_BRG_INFO    *Brg    Pointer to PCI Device Private Data structure
//                          of the Parent Bridge.
//  MRES_TYPE		rt		Type of PCI Bus resources to work with. 
//                          See definition of MRES_TYPE for detail.
//
// Output:	EFI_STATUS
//  EFI_SUCCESS             When everything is going on fine!
//  EFI_OUT_OF_RESOURCES    When system runs out of resources.
//  EFI_DEVICE_ERROR        When driver fails access PCI Bus.
// 
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS AssignBridgeResources(PCI_BRG_INFO *Brg, MRES_TYPE rt)
{
	EFI_STATUS		Status=EFI_NOT_FOUND;
	UINT64			min=Brg->Bridge.Res[rt].Base;
	UINT64			max=(min+Brg->Bridge.Res[rt].Length);
	PCI_BAR			*bar=NULL;
	BRG_RES_ORDER	*ord=&Brg->Bridge.BarOrder[rt];
	UINTN			i;//,j;
//---------------------------------------

    if(ord->BarCount == 0) return EFI_SUCCESS;

	//Assign Io resources to all of Bridge childs
	for(i=0; i<ord->BarCount; i++){
        if(min>=max) {
            Status=EFI_UNSUPPORTED;
            PCI_TRACE((TRACE_PCI,"PciBus: ERROR Assign Res: MIN_ADDR(0x%lX) >= MAX_ADDR(0x%lX)\n", min, max));
            break;
        }
		bar=ord->BarList[i];
//(EIP45278)>
#if PCI_MMIO_RES_TOP_ALLIGN == 1
		if(rt==rtIo16)
#endif
		bar->Base=min;
#if PCI_MMIO_RES_TOP_ALLIGN == 1
		else
		bar->Base=max-bar->Length;
#endif
//<(EIP45278)
		if(bar->Offset!=0xFF){
			Status=ProgramBar(bar);
			if(EFI_ERROR(Status)) break;
		}
//(EIP45278)>
#if PCI_MMIO_RES_TOP_ALLIGN == 1
		if(rt==rtIo16)
#endif
		min+=(bar->Length);
#if PCI_MMIO_RES_TOP_ALLIGN == 1
		else
		max-=(bar->Length);
#endif
//<(EIP45278)
	}	

	if(EFI_ERROR(Status)&& bar!=NULL){
		PCI_TRACE((TRACE_PCI,"PciBus: ERROR Assign Res for BAR(T=%X O=%X) @ [ B%X|D%X|F%X ]",
					bar->Type, bar->Offset,	bar->Owner->Address.Addr.Bus,
					bar->Owner->Address.Addr.Device,bar->Owner->Address.Addr.Function));
        ASSERT_EFI_ERROR(Status);
    } 

	return Status;
}


//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   ClearBar()
//
// Description: Clears/zeros contents of PCI_BAR structure.
//
// Input:
//  PCI_BAR         *Bar    Pointer to PCI_BAR structure to clear.
//
// Output:	Nothing
// 
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID ClearBar(PCI_BAR *Bar)
{
	Bar->Type=tBarUnused;
	Bar->Gran=0;
	Bar->Length=0;
	Bar->Base=0;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   FindBarByType()
//
// Description: Checks if PCI BAR register of a particular "BarType" present 
// behind the PCI Bridge. 
//
// Input:
//  PCI_BRG_INFO    *Brg    Pointer to PCI Device Private Data structure
//                          of the Parent Bridge.
//  PCI_BAR_TYPE	BarType	Bar Type to search for. 
//
// Output:	BOOLEAN
//  TRUE    if BAR of "BarType" present Behind the "Brg".
//  FALSE   if otherwice.
// 
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
BOOLEAN FindBarByType(PCI_BRG_INFO* Brg, PCI_BAR_TYPE BarType)
{
	UINTN			i,j;
	BOOLEAN 		res;	
	PCI_DEV_INFO	*dev;
//---------------------
	for(i=0; i<Brg->Bridge.ChildCount; i++){
		dev=Brg->Bridge.ChildList[i];
		if(dev->Type<tPciHostDev && dev->Type>=tPciRootBrg){
			//go inside the bridge...
			res=FindBarByType((PCI_BRG_INFO*)dev,BarType);
			if(res) return res;
		}
			
		for(j=0; j<PCI_MAX_BAR_NO+1; j++) if(dev->Bar[j].Type==BarType) return TRUE;
#if SRIOV_SUPPORT
//SRIOV Support adds some more bars ito the picture
        if( (dev->PciExpress != NULL) && (dev->PciExpress->SriovData != NULL)){
            for(j=0; j<PCI_MAX_BAR_NO; j++) if(dev->PciExpress->SriovData->Bar[j].Type==BarType) return TRUE;
        }
#endif
	}
	return FALSE;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   ConvertResources()
//
// Description: Converts Resources Requested by the Devices behind the 
// PCI Bridge of "ResType" using "ConvType" method of conversion 
//
// Input:
//  PCI_BRG_INFO    *Brg    Pointer to PCI Device Private Data structure
//                          of the Parent Bridge.
//  PCI_BAR_TYPE	ResType	Resource Type to convert. Accepted values are
//                          tBarIo, tBarMem, tBarMemPf, 
//                          all other values are invalid.
//  RES_CONV_TYPE  ConvType Type of Conversion to be performed.
//
// Output:	Nothing
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID ConvertResources(PCI_BRG_INFO	*Brg, PCI_BAR_TYPE ResType, RES_CONV_TYPE ConvType, BOOLEAN CombineMemPmem)
{
	PCI_BRG_EXT	 	*ext=&Brg->Bridge;
	PCI_DEV_INFO 	*dev;
	UINTN			i,j;
	BOOLEAN			cnv=FALSE;
	PCI_BAR_TYPE	nt, wt;	
	RES_CONV_TYPE	p2pct;
//----------------------------

	//Pick Brg Bars to convert
	switch (ResType) {
		case tBarIo:
			nt=tBarIo16;
			wt=tBarIo32;
			p2pct=rcOneOf;	
			if(Brg->Common.Type==tPci2CrdBrg)p2pct=rcBoth;
			break;

		case tBarMem:
			nt=tBarMmio32;
			wt=tBarMmio64;
			p2pct=rcNarrow;
			if(Brg->Common.Type==tPci2CrdBrg)p2pct=rcNarrow;
			break;			 

		case tBarMemPf:
			nt=tBarMmio32pf;
			wt=tBarMmio64pf;
			p2pct=rcOneOf;
			if(Brg->Common.Type==tPci2CrdBrg)p2pct=rcNarrow;
			break;			 

		default : return; //no other combinations supported
	}//switch

	switch (ConvType){
		case rcNone:
			cnv=TRUE;
			break;
		case rcOneOf:
			cnv=FindBarByType(Brg,nt);
			break;
		case rcNarrow: 
			cnv=FindBarByType(Brg,wt);
			break;
		case rcBoth: cnv=FALSE;
	}//switch

	//Take care about Padding behind the bridge if CombineMemPmem Attribute is set
	if(ext->Pad[rtMmio32p].Length && CombineMemPmem){
		 ext->Pad[rtMmio32].Length+=ext->Pad[rtMmio32p].Length;
		 ext->Pad[rtMmio32p].Length=0;
	}
	if(ext->Pad[rtMmio64p].Length && CombineMemPmem){
		 ext->Pad[rtMmio64].Length+=ext->Pad[rtMmio64p].Length;
		 ext->Pad[rtMmio64p].Length=0;
	}

	for(i=0; i<ext->ChildCount; i++) {
		dev=ext->ChildList[i];			
		for(j=0; j<PCI_MAX_BAR_NO; j++){
			if(cnv){
				switch(ConvType){
					case rcNone:
						if(dev->Bar[j].Type==wt) ClearBar(&dev->Bar[j]);
						break;
					case rcOneOf:
					case rcNarrow: 
						if(dev->Bar[j].Type==wt) dev->Bar[j].Type=nt;
						break;
				}
			} //if cnv 
			if(CombineMemPmem){
				if( dev->Bar[j].Type==tBarMmio32pf ) dev->Bar[j].Type=tBarMmio32;
				if( dev->Bar[j].Type==tBarMmio64pf ) dev->Bar[j].Type=tBarMmio64;
			}
		}//for j

#if SRIOV_SUPPORT
//SRIOV Support adds some more bars ito the picture
        if( (dev->PciExpress != NULL) && (dev->PciExpress->SriovData != NULL)){
		    for(j=0; j<PCI_MAX_BAR_NO; j++){
			    if(cnv){
				    switch(ConvType){
					    case rcNone:
						    if(dev->PciExpress->SriovData->Bar[j].Type==wt){ 
                                ClearBar(&dev->PciExpress->SriovData->Bar[j]);
                            }
						    break;
					    case rcOneOf:
					    case rcNarrow: 
						    if(dev->PciExpress->SriovData->Bar[j].Type==wt){
                                dev->PciExpress->SriovData->Bar[j].Type=nt;
                            }
						    break;
				    }//switch
			    } //if cnv 
			    if(CombineMemPmem){
				    if( dev->PciExpress->SriovData->Bar[j].Type==tBarMmio32pf ) 
                            dev->PciExpress->SriovData->Bar[j].Type=tBarMmio32;
				    if( dev->PciExpress->SriovData->Bar[j].Type==tBarMmio64pf ) 
                            dev->PciExpress->SriovData->Bar[j].Type=tBarMmio64;
			    }
		    }//for j
        }
#endif

		//recoursively call to convert child resources behind other brg
		if(dev->Type==tPci2PciBrg || dev->Type==tPci2CrdBrg){
			if(cnv){
				//Unconditionally convert all resources to narrow because parent requested resource conversion
				if(ConvType)ConvertResources((PCI_BRG_INFO*)dev, ResType, rcNarrow, CombineMemPmem);
				else ConvertResources((PCI_BRG_INFO*)dev, ResType, ConvType, CombineMemPmem);
			} else  ConvertResources((PCI_BRG_INFO*)dev, ResType, p2pct, CombineMemPmem);
		}
	} //Child loop
	//we did it!!!
}


//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   AssignBusResources()
//
// Description: Sorts, Aligns, and Programms Resources requested by devices 
// on the PCI Bus created by the PCI Bridge - "Brg".
//
// Input:
//  PCI_BRG_INFO    *Brg    Pointer to PCI Device Private Data structure
//                          of the Bridge who creates the bus.
//
// Output:	EFI_STATUS
//  EFI_SUCCESS             When everything is going on fine!
//  EFI_OUT_OF_RESOURCES    When system runs out of resources.
//  EFI_DEVICE_ERROR        When driver fails access PCI Bus.
// 
// Notes:
//  Assigns Resources by filling Device Bar structure
//  and programm all Bridge Childs Bars
//  and Enables Bridge devices to decode their resources
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS AssignBusResources(PCI_BRG_INFO *Brg)
{
	EFI_STATUS		Status=0;
	UINT8			i;
	PCI_DEV_INFO	*dev;
//----------------------------------
	//First Check if Resources Assigned don't do it multiple times
	if(Brg->Common.Assigned) return EFI_SUCCESS;
	
	if(Brg->Common.Type == tPci2PciBrg || Brg->Common.Type == tPci2CrdBrg){
		Status=DisableDeviceDecoding(&Brg->Common,stDisableAll);
		Brg->Common.Attrib=0;				
	}	

	//Start with IO 
	if (Brg->Bridge.Res[rtIo32].Length) Status=AssignBridgeResources(Brg,rtIo32);
	if(EFI_ERROR(Status)) return Status;

	if (Brg->Bridge.Res[rtIo16].Length) Status=AssignBridgeResources(Brg,rtIo16);
	if(EFI_ERROR(Status)) return Status;

	
	//Now MMIO 64 PF
	if(Brg->Bridge.Res[rtMmio64p].Length)Status=AssignBridgeResources(Brg,rtMmio64p);
	if(EFI_ERROR(Status)) return Status;

	//Now MMIO 64
	if(Brg->Bridge.Res[rtMmio64].Length)Status=AssignBridgeResources(Brg, rtMmio64);
	if(EFI_ERROR(Status)) return Status;

	//Now MMIO 32 PF
	if(Brg->Bridge.Res[rtMmio32p].Length)Status=AssignBridgeResources(Brg,rtMmio32p);
	if(EFI_ERROR(Status)) return Status;

	//And MMIO 32	
	if(Brg->Bridge.Res[rtMmio32].Length)Status=AssignBridgeResources(Brg, rtMmio32);
	if(EFI_ERROR(Status)) return Status;

	
	//So far so good - resources has been assigned on this Bridge level
	//now check if we have any p2p brg among this brg childs... 
	//if so we will call this function recoursively...
	for(i=0; i<Brg->Bridge.ChildCount; i++ ){
        PCI_CFG_ADDR	a;
        PCI_CMD_REG     cmdreg;
    //-----------------
		Status=EFI_SUCCESS;
   
		dev=Brg->Bridge.ChildList[i];
		a.ADDR=dev->Address.ADDR;

		//Now take care of CacheLine Size register 
		if(dev->Capab&MY_PCI_IO_ATTRIBUTE_MEM_WR_INVALIDATE){
			a.Addr.Register=PCI_CLS; // Cache Line Size
			
			Status=PciCfg8(dev->RbIo,a,TRUE,&gPciCaheLineSize);
			ASSERT_EFI_ERROR(Status);
			if(EFI_ERROR(Status)) return Status;
		}


		if(dev->Type==tPci2PciBrg ||dev->Type==tPci2CrdBrg) Status=AssignBusResources((PCI_BRG_INFO*)dev);

		//disable decoding fo the PCI  devices unles PciPortSkipThisDevice() 
		//says to Skip it. The Device Specific driver should enable it using Attributes() function.
		if(!dev->SkipDevice){
            Status=DisableDeviceDecoding(dev,stDisableAll);
    		dev->Attrib=0;
        }    

		if (EFI_ERROR(Status)) return Status;
		dev->Assigned=TRUE;
	    //UEFI 2.1 - we must leave BRIDGES open (decoding it's ranges)
		if(dev->Type==tPci2PciBrg ||dev->Type==tPci2CrdBrg){
            PCI_BRG_CNT_REG bc;
    		//---------------------------		
            Status=DeviceAttributes(dev, dev->Capab & (EFI_PCI_DEVICE_ENABLE), TRUE);
            ASSERT_EFI_ERROR(Status);
            
            a.Addr.Register=PCI_BRIDGE_CNTL; //Bridge Control Reg 

		    Status=PciCfg16(dev->RbIo,a,FALSE,&bc.BRG_CNT_REG);
		    ASSERT_EFI_ERROR(Status);
   			if(EFI_ERROR(Status)) return Status;

            //Set VGA16 enable to avoid forwarding ISA VGA Aliases
            bc.Vga16Enable=1;             

            //Programm device's BRG_CTL_REG to forward #SERR and #PERR to the primary Interface.
            if(gPciSetupData->SerrEnable) bc.SerrEnable=1;
            else bc.SerrEnable=0;
            
            if(gPciSetupData->PerrEnable) bc.PerrEnable=1;
            else bc.PerrEnable=0;

            
		    Status=PciCfg16(dev->RbIo,a,TRUE,&bc.BRG_CNT_REG);
		    ASSERT_EFI_ERROR(Status);
   			if(EFI_ERROR(Status)) return Status;
        }
    
        //Programm device's PCI_CMD_REG to generate #SERR and #PERR according to Setup.
        a.Addr.Register=PCI_CMD; //PCI Command Reg

	    Status=PciCfg16(dev->RbIo,a,FALSE,&cmdreg.CMD_REG);
	    ASSERT_EFI_ERROR(Status);
		if(EFI_ERROR(Status)) return Status;

        if(gPciSetupData->SerrEnable) cmdreg.SerrEnable=1;
        else cmdreg.SerrEnable=0;
            
        if(gPciSetupData->PerrEnable) cmdreg.ParityErrorResp=1;
        else cmdreg.ParityErrorResp=0;

	    Status=PciCfg16(dev->RbIo,a,TRUE,&cmdreg.CMD_REG);
	    ASSERT_EFI_ERROR(Status);
		if(EFI_ERROR(Status)) return Status;

	} //for 
	Brg->Common.Assigned=TRUE;

	return Status;
}


//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   CreateRootResDsc()
//
// Description: Creates an ACPI QWORD Resource Descriptors set to reflect 
// this "RootBrg" resource request
//
// Input:
//  PCI_BRG_INFO   *RootBrg Pointer to PCI Device Private Data structure
//                          of the Bridge who creates the bus.
//  IN OUT VOID*   *ResDsc  ACPI QWORD Resource Descriptors set.
//                          See definition of ASLR_QWORD_ASD for details.
//
// Output:	EFI_STATUS
//  EFI_SUCCESS             When everything is going on fine!
//  EFI_OUT_OF_RESOURCES    When system runs out of resources.
//  EFI_DEVICE_ERROR        When driver fails access PCI Bus.
// 
// Notes:
//  Meaning of QWORD Resource Descriptor Fields for this function
//  _LEN => Set to the size of the aperture that is requested.
//  _GRA => Used to differentiate between a 32-bit memory request and a 
//          64-bit memory request. For a 32-bit memory request, 
//          this field should be set to 32. For a 64-bit memory request, 
//          this field should be set to 64. All other values result in 
//          this function returning the error code of EFI_INVALID_PARAMETER.
//  _MAX => Used to specify the alignment requirement. 
//  All other fields are ignored.
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS CreateRootResDsc(PCI_DEV_INFO *RootBrg, VOID **ResDsc){
	UINTN				i, rc=0;
	ASLR_QWORD_ASD		*rd;
	PCI_BRG_EXT			*ext=(PCI_BRG_EXT*)(RootBrg+1);
//-----------------------------------------------------
	//First count how many rd suppose to be 
	for(i=rtIo16; i<rtMaxRes; i++){
		if(ext->Res[i].Type && ext->Res[i].Length) rc++;
	}

    //If RB don't have any resource requests fill out END_TAG_DESCRIPTOR and return.
    if(!rc){
        rd=MallocZ(sizeof(ASLR_EndTag));
        rd->Hdr.HDR=ASLV_END_TAG_HDR;        
    	*ResDsc=rd;
        return EFI_SUCCESS;
    }        

	//get some memory 
	rd=MallocZ(sizeof(ASLR_QWORD_ASD)*rc+sizeof(ASLR_EndTag));
	ASSERT(rd);
	if(!rd)	return EFI_OUT_OF_RESOURCES;
	
	*ResDsc=rd;
	for(i=rtIo16; i<rtMaxRes; i++){
		if(!(ext->Res[i].Type && ext->Res[i].Length)) continue ;
		switch(ext->Res[i].Type){
			case tBarIo16:
				rd->Type=ASLRV_SPC_TYPE_IO;
				rd->_GRA=16;
			break;
			case tBarIo32:
				rd->Type=ASLRV_SPC_TYPE_IO;
				rd->_GRA=32;
			break;
			case tBarMmio32pf:
				rd->TFlags.MEM_FLAGS._MEM=ASLRV_MEM_CEPF;
				//no break	intentionally!! DON'T CHANGE 
			case tBarMmio32:
				rd->Type=ASLRV_SPC_TYPE_MEM;
				rd->_GRA=32;
				rd->TFlags.MEM_FLAGS._RW=1;
			break;
			case tBarMmio64pf:
				rd->TFlags.MEM_FLAGS._MEM=ASLRV_MEM_CEPF;
				//no break	intentionally!! DON'T CHANGE 
			case tBarMmio64:
				rd->Type=ASLRV_SPC_TYPE_MEM;
				rd->_GRA=64;
				rd->TFlags.MEM_FLAGS._RW=1;
			break;
			default : continue;
		}
		rd->Hdr.HDR=0x8A;
		rd->GFlags.GFLAGS=0x0C; //Means _MIN and _MAX is fixed
		rd->Hdr.Length=0x2B; 	
		rd->_MAX=ext->Res[i].Gran;
		rd->_LEN=ext->Res[i].Length + ext->Align[i].ExtraRes.Length;

		if(rd->Type==ASLRV_SPC_TYPE_MEM){
			//Check to Memory Resource Size Align on 4K 
			if(rd->_LEN & (EFI_PAGE_SIZE-1))rd->_LEN=(rd->_LEN | (EFI_PAGE_SIZE-1))+1;
		}
		
       PCI_TRACE((TRACE_PCI,"CreateRD QWD: T=%X; GF=%X; TF=%X; _MN=%lX; _MX=%lX; _LN=%lX;_GR=%lX;\n",
					rd->Type, rd->GFlags.GFLAGS, rd->TFlags.TFLAGS, rd->_MIN, rd->_MAX, rd->_LEN, rd->_GRA));

		rd++;
	}
	rd->Hdr.HDR=ASLV_END_TAG_HDR;
	return EFI_SUCCESS;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   ConvertResources()
//
// Description: Converts Resource information from  QWORD ACPI ResDesc
// to internal format and store it within PCI_DEV_INFO structure.  
//
// Input:
//  PCI_BRG_EXT    *RbExt     Pointer to PCI Device Private Data structure
//                            of the Root Bridge. (PCI_BRG_EXT part)
//  ASLR_QWORD_ASD *Resources Pointer to the set 

//  RES_CONV_TYPE  ConvType Type of Conversion to be prformed.
//
// Output:	Nothing
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID ApplyAcpiResources(PCI_BRG_EXT	*RbExt, ASLR_QWORD_ASD *Resources){
	ASLR_QWORD_ASD 	*res=Resources;
	PCI_BAR			*bar;
	UINTN			i, s, e;
//------------------------------------	
	while(res->Hdr.HDR!=ASLV_END_TAG_HDR) {
		bar=NULL;
       	PCI_TRACE((TRACE_PCI,"ApplyRD QWD: T=%X; GF=%X; TF=%X; _MN=%lX; _MX=%lX; _LN=%lX;_GR=%lX;\n",
					res->Type, res->GFlags.GFLAGS, res->TFlags.TFLAGS, res->_MIN, res->_MAX, res->_LEN, res->_GRA));

		if(res->Type==ASLRV_SPC_TYPE_IO){
			s=rtIo16;
			e=rtMmio32;
		} else {
			if(res->Type==ASLRV_SPC_TYPE_MEM){
				s=rtMmio32;
				e=rtMaxRes;
			} else {  
				res++;
				continue;	
			}
		}

		for(i=s; i<e; i++){
			UINT64	len;
		//--------------------
			bar=&RbExt->Res[i];
			len=bar->Length+RbExt->Align[i].ExtraRes.Length;
			
			if( (res->Type==ASLRV_SPC_TYPE_MEM) && (len&(EFI_PAGE_SIZE-1)) ) 
					len=(len|(EFI_PAGE_SIZE-1))+1;

			//It might be an empty descriptor (i.e. System has MMIO32, but does not have MMIO32PF)
			//This might cause to break early. w/o searching through 64bit resources
			//take care of this condition by adding check (bar->Length != 0)
			if((bar->Base == 0) && (bar->Length != 0) && (len <= res->_LEN)) break;
			else bar=NULL;
		}
		
		if(bar)bar->Base=res->_MIN;
		res++;
	}
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   InitPciDb()
//
// Description: Creates all anckor structures and Initialize PCI Database.
//
// Input:
//  EFI_HANDLE  Controller  Controller Handle passed to the PCI Bus Driver
//                          Start Function.
//
// Output:	EFI_STATUS
//  EFI_SUCCESS             When everything is going on fine!
//  EFI_OUT_OF_RESOURCES    When system runs out of resources.
//  EFI_DEVICE_ERROR        When driver fails access PCI Bus.
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS InitPciDb(EFI_HANDLE Controller){
	EFI_STATUS					Status;
	EFI_HANDLE					*hBuff, htmp=NULL;
	EFI_DEVICE_PATH_PROTOCOL	*rbdp;
	UINTN						i, cnt=0;
	PCI_DEV_INFO				*rb;
	EFI_PCI_ROOT_BRIDGE_IO_PROTOCOL						*rbio;
    
//Exclude Hotplug support 
#if HOTPLUG_SUPPORT
	UINTN												 ghpccnt=0, j;
	EFI_HPC_LOCATION									*ghpclst=NULL;	
#endif

//------------------------
    Status=PopulateBusDb();
	ASSERT_EFI_ERROR(Status);
	if(EFI_ERROR(Status)) return EFI_DEVICE_ERROR;

	Status=pBS->HandleProtocol(Controller,&gPciRootBridgeIoProtocolGuid,&rbio);
	ASSERT_EFI_ERROR(Status);
	if(EFI_ERROR(Status)) return EFI_INVALID_PARAMETER;
	if(gPciHost && gPciHost[0].Updated)	return EFI_SUCCESS;


	//Try to figure out how many instances of PCI HostBridge Resource Allocation Protocol
	//exists, this will give us an idea how many PCI_ROOT_INFO instances to create...
	Status=pBS->LocateHandleBuffer(
							ByProtocol,						//	SearchType,
							&gEfiPciHostBrgResAllocProtocolGuid,	//*Protocol OPTIONAL,
							NULL,							//*SearchKey OPTIONAL,
							&gHostCnt,							//*NoHandles,	
							&hBuff);						//**Buffer
	ASSERT_EFI_ERROR(Status);
	if(EFI_ERROR(Status)) return Status;

	//Now we know how many Host Bridges the System has
	gPciHost=MallocZ(sizeof(PCI_HOST_INFO)*gHostCnt);

	//record Host Bridge Properties
	for(i=0; i<gHostCnt; i++){
		gPciHost[i].HostHandle=hBuff[i];
		//Get Resource Alloc Protocol and Record It 
		Status=pBS->HandleProtocol(hBuff[i],&gEfiPciHostBrgResAllocProtocolGuid,&gPciHost[i].ResAllocProt);
		//it has to be there or plaform is not Framework compliant
		ASSERT_EFI_ERROR(Status);
		if(EFI_ERROR(Status)) return Status;
		//now will locate some optional protocols which must be used if present during PCI enumeration
		//as per spec - only one instance of this protocols should be present
		if(i==0){
//Exclude Hotplug support 
#if HOTPLUG_SUPPORT
			pBS->LocateProtocol(&gEfiPciHotPlugInitProtocolGuid, NULL, &gPciHost[i].HpInitProt);
#endif
			pBS->LocateProtocol(&gEfiPciPlatformProtocolGuid, NULL, &gPciHost[i].PlatformProt);
			pBS->LocateProtocol(&gEfiIncompatiblePciDeviceProtocolGuid, NULL, &gPciHost[i].IncompDevProt);
		} else {
//Exclude Hotplug support 
#if HOTPLUG_SUPPORT
			gPciHost[i].HpInitProt=gPciHost[0].HpInitProt;
#endif
			gPciHost[i].PlatformProt=gPciHost[0].PlatformProt;
			gPciHost[i].IncompDevProt=gPciHost[0].IncompDevProt;
		}
		gPciHost[i].Updated=TRUE;
	}

//Exclude Hotplug support 
#if HOTPLUG_SUPPORT

	//If HpInitProtocol Exists get RootHpcList 
	if(gPciHost[0].HpInitProt ){
		Status=gPciHost[0].HpInitProt->GetRootHpcList(gPciHost[0].HpInitProt,&ghpccnt,&ghpclst);
		ASSERT_EFI_ERROR(Status);
	}
#endif

	//Now get all RbIo Protocol Handlers and find the right place for it Protocol Instance.
	Status=pBS->HandleProtocol(Controller,&gPciRootBridgeIoProtocolGuid,&rbio);
	//RBIoProtocol has to be installed on Controller Handle
	ASSERT_EFI_ERROR(Status);
	if(EFI_ERROR(Status)) return Status;

	//Select Right Host Brg for this RootBrg Io Protocol Handler
	for(i=0; i<gHostCnt; i++){
		//if(gPciHost[i].HostHandle==rbio->ParentHandle) gCurHost=i;
	
		htmp=NULL;
		//Now we will fill Pci Root infrastructure in the right order 
		while(!Status){
			//get Root Bridge Handle of this Host
			Status=gPciHost[i].ResAllocProt->GetNextRootBridge(gPciHost[i].ResAllocProt, &htmp);
			if(EFI_ERROR(Status)) break;
		
	
			//Create New PCI_BRG_INFO structure;
			rb=NewDevice(TRUE,NULL);
			if(!rb) return EFI_OUT_OF_RESOURCES;
            
			//Get the Resource Allocation Attributes
			//Status=gPciHost[i].ResAllocProt->GetAllocAttributes(gPciHost[i].ResAllocProt, htmp, &rb->Attrib);
			//if(EFI_ERROR(Status)) break;

				
			//Add it to the Root Bridge Item List
			Status=AppendItemLst((T_ITEM_LIST*)&gPciHost[i].RbInitCnt, rb);
			ASSERT_EFI_ERROR(Status);
			if(EFI_ERROR(Status)) return Status;
		
			//now I'll get DevicePath and RootBridgeIo protocols Associated with this Handle   
			//Status=pBS->HandleProtocol(htmp,&gPciRootBridgeIoProtocolGuid,&rb->RbIo);
			//This Protocol will remain opened untill PciBusStop is Called. 
			Status=pBS->OpenProtocol(htmp,
				&gPciRootBridgeIoProtocolGuid,(VOID **)&rb->RbIo, 
				gPciBusDriverBinding.DriverBindingHandle,htmp,
				EFI_OPEN_PROTOCOL_BY_DRIVER );

			ASSERT_EFI_ERROR(Status); //it MUST have this
			if(EFI_ERROR(Status)) return Status;

			Status=pBS->HandleProtocol(htmp,&gDevicePathProtocolGuid,&rbdp);
			ASSERT_EFI_ERROR(Status); //it MUST have this
			if(EFI_ERROR(Status)) return Status;

			//Fill out some missing and incorrectly filled fields
			rb->DevicePath=DPCopy(rbdp);
			rb->Type=tPciRootBrg;
			rb->HostData=&gPciHost[i];
			rb->Handle=htmp;
			rb->ParentBrg=NULL;

//Exclude Hotplug support 
#if HOTPLUG_SUPPORT
			
			//sort out Root Hot Plug Controlers list items to where they belongs
            PCI_TRACE((TRACE_PCI,"PciBus: Get Location - HpcLocCount=%d; RbDp=[HID(%X)UID(%X)]\n", 
                ghpccnt,((ACPI_HID_DEVICE_PATH*)rbdp)->HID,((ACPI_HID_DEVICE_PATH*)rbdp)->UID));
            PCI_TRACE((TRACE_PCI,"-------------------------------------------------\n"));

			for (j=0; j<ghpccnt; j++){
                
				if( !MemCmp(rbdp, ghpclst[j].HpcDevicePath, sizeof(ACPI_HID_DEVICE_PATH)) ){ 
					PCI_HPC_INFO	*rhpc;
				//-----------------------------	
					rhpc=MallocZ(sizeof(PCI_HPC_INFO));
					ASSERT(rhpc);
					if(!rhpc) return EFI_OUT_OF_RESOURCES;
					//Init PCI_ROOT_HPC structure
					rhpc->Root=TRUE;
					rhpc->HpcLocation=&ghpclst[j];
					
                    PCI_TRACE((TRACE_PCI,"HpcDP=[HID(%X)UID(%X)]; HpbDP[HID(%X)UID(%X)]\n",
                    ((ACPI_HID_DEVICE_PATH*)rhpc->HpcLocation->HpcDevicePath)->HID,((ACPI_HID_DEVICE_PATH*)rhpc->HpcLocation->HpcDevicePath)->UID,
                    ((ACPI_HID_DEVICE_PATH*)rhpc->HpcLocation->HpbDevicePath)->HID,((ACPI_HID_DEVICE_PATH*)rhpc->HpcLocation->HpbDevicePath)->UID));

					Status=AppendItemLst((T_ITEM_LIST*)&rb->HostData->RhpcInitCnt,rhpc);
					ASSERT_EFI_ERROR(Status); //it MUST have this
					if(EFI_ERROR(Status)) return Status;
				}
			}
            PCI_TRACE((TRACE_PCI,"-------------------------------------------------\n"));
#endif

		}
		if(Status!=EFI_NOT_FOUND) return Status;
	}

	//Don't forget to free handle Buffer;
	pBS->FreePool(hBuff);

	return EFI_SUCCESS;
}


//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   EnumerateAll()
//
// Description: This is Main function to start PCI Bus Enumeration Process.
//
// Input:
//  EFI_HANDLE  Controller  Controller Handle passed to the PCI Bus Driver
//                          Start Function.
//
// Output:	EFI_STATUS
//  EFI_SUCCESS             When everything is going on fine!
//  EFI_OUT_OF_RESOURCES    When system runs out of resources.
//  EFI_DEVICE_ERROR        When driver fails access PCI Bus.
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS EnumerateAll(EFI_HANDLE Controller){
	EFI_STATUS			Status=EFI_SUCCESS;
	UINTN				i, j;
	UINT8				StartBus, EndBus;
	RES_CONV_TYPE		ct;
	PCI_HOST_INFO		*lhst;
	PCI_DEV_INFO		*rb;
	PCI_BRG_EXT			*ext;
	ASLR_QWORD_ASD		*rres;
//-------------------------------
	//Init Pci Local Data if it wasn't initialized yet
    if(gPciHost==NULL){
    	Status=InitPciDb(Controller);
	    ASSERT_EFI_ERROR(Status);	
    }
    //Check if we have enumerated VERY FIRST ROOT we done.
    //That means all roots were enumerated alredy, don't spend eny more time here... 
	if(gPciHost[0].Enumerated) return EFI_SUCCESS; 

	//We will do enumeration for all PCI infrastructure, as soon as we got very first 
	//Root Bridge Handle. and then will start only devices belonging to the RootBridge   
	//who's handle we have received as a Controller Handle.
	mMaxBusFound=0;		
    mMaxBusReport=0;

	for(j=0; j<gHostCnt; j++){
		lhst=&gPciHost[j]; //init local host pointer

		//will circle trough Root bridges system has starting from _UID=0
		for(i=0; i<lhst->RbCount; i++){
			rb=lhst->RootBridges[i];			
			ext=(PCI_BRG_EXT*)(rb+1);

#if BoardPciRes_SUPPORT
            gPciOutOfRes=FALSE;
#endif
			//check if we have this Root Bridge Enumerated already
			if(rb->Enumerated) continue;		
//			ClearItemLst(&res, TRUE);

			//6. Notify the host bridge driver that PCI enumeration is about to begin by calling
			//NotifyPhase (EfiPciHostBridgeBeginEnumeration). This member function
			//must be the first one that gets called. PCI enumeration has two steps: bus enumeration and
			//resource enumeration.
			Status=DoPciNotify(lhst, EfiPciHostBridgeBeginEnumeration);
			ASSERT_EFI_ERROR(Status);
		
			//7. Notify the host bridge driver that bus enumeration is about to begin by calling
			//NotifyPhase (EfiPciHostBridgeBeginBusAllocation).
			Status=DoPciNotify(lhst, EfiPciHostBridgeBeginBusAllocation);
			ASSERT_EFI_ERROR(Status);
				
			//8. Do the following for every PCI root bridge handle:
			//	a. Call StartBusEnumeration (This,RootBridgeHandle).
			Status=lhst->ResAllocProt->StartBusEnumeration(lhst->ResAllocProt, rb->Handle, &rres);
			ASSERT_EFI_ERROR(Status);

			//Check if it is NULL descriptor..
			if(rres->_MIN==0 && rres->_MAX==0 && rres->_LEN==0) {
				Status=DoPciNotify(lhst, EfiPciHostBridgeEndBusAllocation);
    			Status=DoPciNotify(lhst, EfiPciHostBridgeBeginResourceAllocation);
				continue; 
			}

			//Check if we've received correct descriptors
			if(!ValidateDescriptorBlock(rres,tResBus,FALSE)) {
				ASSERT(0);
				return EFI_DEVICE_ERROR;
			}

			//we have reseived BUS configuration information in "rres"
			//_MIN Bus# has to be Updated with respect of previous pass 
			StartBus=(UINT8)rres->_MIN;
        	mMaxBusFound=StartBus;		

			rb->Address.Addr.Bus=StartBus;
            mMaxBusScan=(UINTN)(StartBus+rres->_LEN-1);
            //Maximum bus number must not exceed 0xFF buses!
            if(mMaxBusScan > 0xFF) ASSERT_EFI_ERROR(EFI_DEVICE_ERROR);
            //Match Busxlat Entry to the current Host Bridge
            Status=FindBridgeXlatEntry(rb, ext);
            //It's a seriouse error if it returns NOT_FOUND need to ASSERT here.
			ASSERT_EFI_ERROR(Status); 
            
			ext->Res[rtBus].Type=tBarBus;
			ext->Res[rtBus].Base=StartBus;
			ext->Res[rtBus].Length=rres->_LEN;
			//Get Attributes to see what this RB could support
			Status=rb->RbIo->GetAttributes(rb->RbIo,&rb->Capab,&rb->Attrib);		
			ASSERT_EFI_ERROR(Status);
			
//Exclude Hotplug support 
#if HOTPLUG_SUPPORT
			//this will try to init Root HPC siting behind this bridge if any...
			Status=CheckRootHotplug(rb);
			ASSERT_EFI_ERROR(Status);
			//if root hpc init fail for any reason we just must keep going
#endif
			//	b. Make sure each PCI root bridge handle supports the
			//	EFI_PCI_ROOT_BRIDGE_IO_PROTOCOL.
			//		c. Allocate memory to hold resource requirements. These resources can be two resource trees:
			//		one to hold bus requirements and another to hold the I/O and memory requirements.
			//
			//		e. Scan all the devices in the specified bus range and on the specified segment. If it is a PCIto-
			//		PCI bridge, update the bus numbers and program the bus number registers in the PCI-to-
			//		PCI bridge hardware. If it is an ordinary device, collect the resource request and add up all
			//		of these requests in multiple pools (e.g., I/O, 32-bit prefetchable memory). Combine
			//		different types of memory requests at an appropriate level based on the PCI root bridge
			//		attributes. Update the resource requirement information accordingly. On every PCI root
			//		bridge, reserve space to cover the largest expansion ROMs on that bus, which will allow
			//		the PCI bus driver to retrieve expansion ROMs from the PCI card or device without having
			//		to reprogram the PCI host bridge. Because the memory and I/O resource collection step
			//		does not call any member function of EFI_PCI_HOST_BRIDGE_RESOURCE_ALLOCATION_PROTOCOL, 
			//		it can be performed at a later time.
			//		f. Once the number of PCI buses under this PCI root bridge is known, call
			//		SetBusNumbers() with this information.			

			//Go and do the job! 
            mMaxBusReport=StartBus;
            PCI_TRACE((TRACE_PCI,"PciBus: Root#%d; ScanFullBusRange=%d; Scanning ",i, ScanFullBusRange));
            if(ScanFullBusRange) {
                EndBus=(UINT8)(mMaxBusScan);
                PCI_TRACE((TRACE_PCI,"Bus Range 0x%X...0x%X \n", StartBus, EndBus));
            } else {
                EndBus=StartBus;
        	    PCI_TRACE((TRACE_PCI,"Buses Starting from 0x%X \n",  StartBus));
            }

            if(ext->XlatTblEntry) ext->XlatTblEntry->BusRun=StartBus;
        
            do{
    			Status=EnumerateBus((PCI_DEV_INFO*)rb);
			    if(EFI_ERROR(Status)){
                    if(Status != EFI_NOT_FOUND) return Status;
                } else {
                    if(mMaxBusReport < rb->Address.Addr.Bus) mMaxBusReport = rb->Address.Addr.Bus;
                    rb->Address.Addr.Bus = mMaxBusReport;
        			ext->Res[rtBus].Base = mMaxBusReport;
                }
                
                //Bus is UINT8 to avoid deadloop here check 
                //for condition to berak the loop.
                if(rb->Address.Addr.Bus==0xFF) break;
                rb->Address.Addr.Bus++;
    			ext->Res[rtBus].Base++;
            } while (rb->Address.Addr.Bus <= EndBus);

#if PCI_EXPRESS_SUPPORT
            //We have collected all Upstream Ports information 
            //Now init it from EndPoint up to RootPort
            while(gPcieEpList.ItemCount!=0){
                PCI_DEV_INFO *epdev;            
            //---------------------
                epdev=(PCI_DEV_INFO*)gPcieEpList.Items[0];
                
                Status=PcieInitDevChain(epdev);
                ASSERT_EFI_ERROR(Status);
			    if(EFI_ERROR(Status)) return Status;
            }
#endif            
            //Restore old values    
            rb->Address.Addr.Bus = StartBus;    
			ext->Res[rtBus].Base = StartBus;
            if(ext->XlatTblEntry){
                UpdateIrqTables(ext->XlatTblEntry);
                PCI_TRACE((TRACE_PCI,"PciBus: Update Bus# for RootBrg [B%X|D%X|F%X] - Bld %X -> Run %X\n", 
                rb->Address.Addr.Bus,rb->Address.Addr.Device,rb->Address.Addr.Function, 
                ext->XlatTblEntry->BusBuild,ext->XlatTblEntry->BusRun));                
            }
            
			//we got lucky!!! finally we are here with information about all resources we need
			//in the Root Bridge device the following fields will reflect ACPI Resource descriptor fields
			// rb->Address.Bus = Primary Bus Number _MIN
			// ext->Res[rtBus].Base = Subordinate Bus Number = _MAX
			// ext->Res[rtBus].Len =  _MAX+1
			ext->Res[rtBus].Base=mMaxBusReport; //that how much this root brg has buses 
			ext->Res[rtBus].Length=mMaxBusReport-StartBus+1;

			//Update discovered Bus Numbers and report Bus Resources to the HOST
			rres->_LEN=ext->Res[rtBus].Length;
			rres->_MAX=rres->_MIN+rres->_LEN-1;
			Status=lhst->ResAllocProt->SetBusNumbers(lhst->ResAllocProt, rb->Handle, rres);
			ASSERT_EFI_ERROR(Status);
			//if everything OK free memory given by StartBusEnumeration function
			pBS->FreePool(rres);

            

			//Here we have to convert some resourcers which we have discovered but RB doesn't supports
			//Get Allocation Attributes for this Root Bridge it will let us know how to convert resources for this Root bridge
//???????????????????????????????????????????????????????????????????????????????????????????????????	
//Currently resource allocation attributes reflects only capability of RB to decode 64 bit address
//but still will not give any clue weathere it is single window or RB has a separate BAR to decode it.
//If the bar is single and it decodes eather 32 or 64 bit resources the "rcOneOf" must be selected
//???????????????????????????????????????????????????????????????????????????????????????????????????
			Status=lhst->ResAllocProt->GetAllocAttributes(lhst->ResAllocProt,rb->Handle,&gAllocationAttributes);
			ASSERT_EFI_ERROR(Status);

			//Notify HB and CSP
			Status=DoPciNotify(lhst, EfiPciHostBridgeEndBusAllocation);
			ASSERT_EFI_ERROR(Status);

            PROGRESS_CODE(DXE_PCI_BUS_REQUEST_RESOURCES);

			//First do IO - Any PCI Root Bridge supports only Io16 
			ConvertResources((PCI_BRG_INFO*)rb,tBarIo,rcNarrow,(BOOLEAN)(gAllocationAttributes & EFI_PCI_HOST_BRIDGE_COMBINE_MEM_PMEM));

			//than do MMIO
			if(gAllocationAttributes & EFI_PCI_HOST_BRIDGE_MEM64_DECODE)ct=rcBoth; 
			else ct=rcNarrow;
			ConvertResources((PCI_BRG_INFO*)rb,tBarMem,ct,(BOOLEAN)(gAllocationAttributes & EFI_PCI_HOST_BRIDGE_COMBINE_MEM_PMEM));

			//than do pfMMIO 
			if(gAllocationAttributes & EFI_PCI_HOST_BRIDGE_MEM64_DECODE)ct=rcBoth; 
			else ct=rcNarrow;
			ConvertResources((PCI_BRG_INFO*)rb,tBarMemPf,ct,(BOOLEAN)(gAllocationAttributes & EFI_PCI_HOST_BRIDGE_COMBINE_MEM_PMEM));

//???????????????????????????????????????????????????????????????????????????????????????????????????
// Attempt to boot with reduced number of PCI Cards if resources will be not enough  
//??has to be called consequently 
//??or create RecalculateBrgResources()...
//////////////////////////////////////////////////////////////////
//???????????????????????????????????????????????????????????????????????????????????????????????????
#if BoardPciRes_SUPPORT
            
            do{ 
//OUT_OF_RES!!  
                //Reset Flag to stop calling Platform function to select PCI device selected 
                // to be removed from enumeration for this pass. It will be SET in CalculateBrgResources().
                gPciOutOfResHit=FALSE;
                ext=(PCI_BRG_EXT*)(rb+1);
                if(gPciOutOfRes) ClearBrgResources(rb);   
#endif
    			//Calculate resources Consumed by this Root bridge
    			CalculateBrgResources(rb);
    			rb->Discovered=TRUE;

			    //Notify HB and CSP
    			Status=DoPciNotify(lhst, EfiPciHostBridgeBeginResourceAllocation);
    			ASSERT_EFI_ERROR(Status);

			    //Status=AllocateRootResources(gPciRoot.RootBrg[i], &mRootRes);
			    //Create Resource information to report to the HOST BRG
			    Status=CreateRootResDsc(rb,&rres);
    			if(EFI_ERROR(Status)){
                    PCI_TRACE((TRACE_PCI,"PciBus: CreateRootResDsc() returned %r \n ",Status));
                    return Status;
                }
            
                //Not Found Condition is Normal for RB it does not have enything behind it.
                //Skip Calling SubmitResources() since nothing to Submit
   	    		Status=lhst->ResAllocProt->SubmitResources(lhst->ResAllocProt, rb->Handle, rres);
    		    if(EFI_ERROR(Status)) {
                    VOID *Configuration;    //This is a dummy parameter.
#if BoardPciRes_SUPPORT
#if PCI_OUT_OF_RESOURCE_SETUP_SUPPORT
                //Declare Boot flow variable GUID...
                    EFI_GUID BootFlowVariableGuid = BOOT_FLOW_VARIABLE_GUID;
                    UINT32   BootFlow = BOOT_FLOW_CONDITION_PCI_OUT_OF_RESOURCE;
                //------------------------------
                    Status=pRS->SetVariable(L"BootFlow",&BootFlowVariableGuid,EFI_VARIABLE_BOOTSERVICE_ACCESS,sizeof(BootFlow),&BootFlow);
#endif

                    //Give Platform Policy Driver to handle OUT_OF_RESOURCES situation 
                    //by itself (it just might want to BEEP and HUNG the system)
                    gPciOutOfRes=TRUE;

#endif
                    lhst->ResAllocProt->GetProposedResources(
  		                lhst->ResAllocProt,
		                rb->Handle,
		                &Configuration);
#if BoardPciRes_SUPPORT
#else
                    ERROR_CODE(DXE_PCI_BUS_OUT_OF_RESOURCES,EFI_ERROR_MAJOR);
                    ASSERT_EFI_ERROR(Status);
#endif
			        pBS->FreePool(rres);
#if BoardPciRes_SUPPORT
    		    } else gPciOutOfRes=FALSE;
            } while(gPciOutOfRes); //while resources found
#else
			    return Status;
		    }
#endif
		} //loop (i) on submiting resources
#if BoardPciRes_SUPPORT
        //Check if we suppose to beep and report "OUT OF_RESOURCES" condition
        Status=AmiPciOutOfRes(NULL, TRUE);
        if(!EFI_ERROR(Status)) ERROR_CODE(DXE_PCI_BUS_OUT_OF_RESOURCES,EFI_ERROR_MAJOR);
#endif  
        //Notify HB and CSP
		Status=DoPciNotify(lhst, EfiPciHostBridgeAllocateResources);
        PROGRESS_CODE(DXE_PCI_BUS_ASSIGN_RESOURCES);
        

		ASSERT_EFI_ERROR(Status);
//TODO//TODO//TODO//TODO//TODO//TODO//TODO//TODO//TODO//TODO//TODO//TODO
// if Allocate Resources Notify Phase returns an ERROR 
// Here suppose to be the following logic :
// a. Make do with the smaller ranges.
// b. Call GetProposedResources() to retrieve the proposed settings and examine the
// 	differences. Prioritize various requests and drop lower-priority requests. Call
//	NotifyPhase (EfiPciHostBridgeFreeResources) to undo the previous
//	allocation. Go back to step 11 with reduced requirements, which includes resubmitting
//	requests for all the root bridges.


//  It easy to say, but hard to implement!!!!!
//TODO//TODO//TODO//TODO//TODO//TODO//TODO//TODO//TODO//TODO//TODO//TODO

		Status=DoPciNotify(lhst, EfiPciHostBridgeSetResources);
		ASSERT_EFI_ERROR(Status);

		//now enter the loop where we will get resource windows selected by the Root Bridge 
		//and programm it in to PCI subsystem BARs
		for(i=0; i<lhst->RbCount; i++){
			rb=lhst->RootBridges[i];			
			ext=(PCI_BRG_EXT*)(rb+1);

			//Get Copy of updated resources to see if our call worked
			Status=rb->RbIo->Configuration(rb->RbIo,(VOID**)&rres);
			if (Status==EFI_NOT_AVAILABLE_YET) continue;

			ASSERT_EFI_ERROR(Status);
			if(EFI_ERROR(Status)) return Status;

    		ApplyAcpiResources(ext, rres);
		
			//now we have to assign PCI bus resources, and PciRoot will be the special case.
			//We should not touch the device which adressed as gPciRoot.RootBrg[i].Address
			//because it is controlled by PciRootBridge Driver and we must not directly access it
			//So AssignBusResources routine has a checking of such condition
			Status=AssignBusResources((PCI_BRG_INFO*)rb);
			if(EFI_ERROR(Status)) return Status;

#if PCI_EXPRESS_SUPPORT
			//Record PciEcpress Boot Script since not all OSs knows about it
			PcieRecordBootScript(rb);
#endif
	
			//Set Started Flag for RootBridge device in order not to install PCI IO on it later
			rb->Started=TRUE;
		}//loop (i) for root bridge
		Status=DoPciNotify(lhst, EfiPciHostBridgeEndResourceAllocation);
		ASSERT_EFI_ERROR(Status);
		
		lhst->Enumerated=TRUE;
	} //loop (j)
#if S3_VIDEO_REPOST_SUPPORT == 1
//    if( (gPciSetupData->S3ResumeVideoRepost==1) && S3VideoRepost ){
        // Register the event handling function to Record Primary VGA BootScript.
        Status = CreateReadyToBootEvent (
                        TPL_CALLBACK,
                        RecordPriVgaBootScript,
                        NULL,
                        &gVgaS3Event);
//    }
#endif

	return Status;
}


//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   CheckPciDevicePath()
//
// Description: Checks if "DevicePath" is a PCI_DEVICE_PATH.
//
// Input:
//  EFI_DEVICE_PATH_PROTOCOL *DevicePath  Device Path Pointer.
//
// Output:	EFI_STATUS
//  EFI_SUCCESS             When everything is going on fine!
//  EFI_UNSUPPORTED         When "DevicePath" is not a PCI_DEVICE_PATH.
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS CheckPciDevicePath(EFI_DEVICE_PATH_PROTOCOL *DevicePath)
{
    // Check if the RemainingDevicePath is valid
	if (DevicePath->Type != HARDWARE_DEVICE_PATH ||
		DevicePath->SubType != HW_PCI_DP &&
		NODE_LENGTH(DevicePath) != sizeof (PCI_DEVICE_PATH)) 
      return EFI_UNSUPPORTED;
	else return EFI_SUCCESS;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   DoubleCheckOpRom()
//
// Description: This function called when PciRomHdr->InitializationSize and 
// Pcir->ImageSize has different values and Pcir->Indicator bit 7 is not set. 
// It evaluets whch one is correct by Searching for 0x55AA signature that is 
// must present in the beginning of next OptROM image.
//
// Input:
//  LEGACY_OPT_ROM_HEADER   *PciRomHdr  Pointer to Legacy Option ROM Header(0x55AA).
//  PCI_DATA_STRUCTURE      *Pcir       Pointer to PCI ROM header ("PCIR")
//  
// Output:	EFI_STATUS
//  UINTN   Size of the ROM in bytes;
// Note: PCIR and OptROM signatures assumed to be valid. 
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
UINTN   DoubleCheckOpRom(VOID *PciRomHdr, PCI_DATA_STRUCTURE *Pcir){
    UINT8                   *p;
    UINTN                   sz=0;
    UINTN                   hsz=0;
//---------------------------------
    //EFI Compatible ROM headers have 16 bit Length field... 
    if( ((PCI_EFI_OPT_ROM_HEADER*)PciRomHdr)->EfiSignature == PCI_OPT_ROM_EFISIG) hsz=((PCI_EFI_OPT_ROM_HEADER*)PciRomHdr)->InitializationSize; //16 bit size   
    else hsz=((LEGACY_OPT_ROM_HEADER*)PciRomHdr)->Size512;

    if(hsz == Pcir->ImageLength ) return (hsz*512);

    p=(UINT8*)PciRomHdr;

    if(hsz < Pcir->ImageLength ) {
       sz= Pcir->ImageLength*512;
       if( ((LEGACY_OPT_ROM_HEADER*)(p+sz))->Signature==PCI_OPT_ROM_SIG) return sz;
       if(Pcir->Indicator&0x80) return sz; //(EIP37774+)
    } 

    sz=hsz*512;
    if( ((LEGACY_OPT_ROM_HEADER*)(p+sz))->Signature==PCI_OPT_ROM_SIG) return sz;
    else {  
        if(Pcir->Indicator&0x80) return sz;//(EIP37774+)
        if ( ((LEGACY_OPT_ROM_HEADER*)PciRomHdr)->Signature==PCI_OPT_ROM_SIG ) return sz;
        return 512;    
    }
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   GetOptRom()
//
// Description: Validate and copy PCI Option ROM Image From ADD ON CARD to
// the System Memory.
//
// Input:
//  PCI_DEV_INFO    *Dev   Pointer PCI Devicse Private Data.
//  
// Output:	EFI_STATUS
//  EFI_SUCCESS             When everything is going on fine!
//  EFI_OUT_OF_RESOURCES    When system runs out of resources.
//  EFI_DEVICE_ERROR        When driver fails access PCI Bus.
//  EFI_INVALID_PARAMETER   When Parameter passed is invalid.
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS GetOptRom(PCI_DEV_INFO	*Dev)
{
	EFI_STATUS				Status=EFI_NOT_FOUND, ExitStatus=0; 
	PCI_BAR					*rombar=&Dev->Bar[PCI_MAX_BAR_NO];
	//UINT8					RomBuff[20];
	UINTN					OptRomSize = 0;
    UINT32					trs=0;
    PCI_DATA_STRUCTURE      Pcir;
    PCI_STD_OPT_ROM_HEADER  PciRomHdr;
	PCI_EFI_OPT_ROM_HEADER	*EfiRomHdr=(PCI_EFI_OPT_ROM_HEADER*)&PciRomHdr;
#if CSM_SUPPORT
	VOID					*EmbRom;
#endif
    BOOLEAN                 ff=TRUE;
    UINT64                  base=rombar->Base;
    UINTN                   sz=0;
//-------------------------------------
	//we got Opt ROM to check...
	if(Dev->Bar[PCI_MAX_BAR_NO].Type!=tBarUnused){
		//Enable RomBar Decoding
		//We will use PciIo->SetAttributes here to enable device Memory Space.
		//If device sits behind some P2P brg Attributes will enable it all the way down   
		//Per UEFI 2.1 spec bridges must be open and decoding it's resources.
		//Status=DeviceAttributes(Dev, EFI_PCI_IO_ATTRIBUTE_MEMORY, TRUE);
		//if(EFI_ERROR(Status))return Status;

		Status=EnableDeviceDecoding(Dev,stOptRomSpace);	
		if(EFI_ERROR(Status))return Status;

	    for(;;){
 	       if(base+trs+512 >= rombar->Base+rombar->Length) break;
   
	        // Get the first 20 bytes of the ROM header
	    	Status=Dev->RbIo->Mem.Read(Dev->RbIo, EfiPciWidthUint8, base+trs,
		    sizeof(PCI_STD_OPT_ROM_HEADER), &PciRomHdr);
		    if(EFI_ERROR(Status))goto ExitLbl;  

	    	// Check the validity of the ROM
		    if ((PciRomHdr.Signature != PCI_OPT_ROM_SIG) || (PciRomHdr.PcirOffset == 0) ){
	            if(ff) {
			        Status=EFI_NOT_FOUND;
			        goto ExitLbl;
		        } else {
	                //base+=512;
	                trs+=512;
	                continue;
	            }
	        } 
	        ff=FALSE;
               
	    	Status=Dev->RbIo->Mem.Read(Dev->RbIo, EfiPciWidthUint8, base+trs+PciRomHdr.PcirOffset,
								    sizeof(PCI_DATA_STRUCTURE), &Pcir);
		    if(EFI_ERROR(Status))goto ExitLbl;  
        
	        if(Pcir.Signature!=PCI_PCIR_SIG){
            //Status=EFI_NOT_FOUND;
            //goto ExitLbl;
 	           continue;        
	        }        

	        OptRomSize=trs;

            sz=DoubleCheckOpRom((VOID*)(base+trs), &Pcir);
            OptRomSize+=sz;
            
/*
			//Figure out the size of image. Some of the cards has PCI_STD_OPT_ROM_HEADER.Size value
			//bigger then in PCIR PCI_DATA_STRUCTURE.ImageLength field.
		    if(Pcir.CodeType == 0){
				if(PciRomHdr.Reserved[0] < Pcir.ImageLength) OptRomSize+=(Pcir.ImageLength*512);
				else OptRomSize+=(PciRomHdr.Reserved[0]*512);
	        }
			//Open Firmware Standard for PCI
		    if(Pcir.CodeType == 1){
				OptRomSize+=(Pcir.ImageLength*512);
			}

		    //In case of EFI Option ROM Header   
		    if(Pcir.CodeType == 3) { 
			    if(EfiRomHdr->InitializationSize < Pcir.ImageLength) OptRomSize+=(Pcir.ImageLength*512);
			    else OptRomSize+=(EfiRomHdr->InitializationSize*512);
		    }
*/
	        trs=(UINT32)OptRomSize;

	        if(Pcir.Indicator & 0x80) break;
		}//for(;;)

		//Allocate Memory For Opt Rom Image Buffer
		Dev->PciIo.RomImage=Malloc(OptRomSize);
		if(Dev->PciIo.RomImage==NULL){
			Status=EFI_OUT_OF_RESOURCES;
			goto ExitLbl;    
		}
		
	   	//Copy Rom image into memory
//		Status=Dev->RbIo->Mem.Read(Dev->RbIo, EfiPciWidthUint8,rombar->Base,
//									OptRomSize,Dev->PciIo.RomImage);
//		if(EFI_ERROR(Status)) goto ExitLbl;

        MemCpy32(Dev->PciIo.RomImage, (VOID*)(rombar->Base), OptRomSize);

		//We didnot parse OPT ROM buffer yet so RomSize will have temp value 
		Dev->PciIo.RomSize=OptRomSize;

ExitLbl:
		//Disable decoding option rom again 
		//Per UEFI 2.1 spec bridges must be open and decoding it's resources.
		//ExitStatus=DeviceAttributes(Dev, EFI_PCI_IO_ATTRIBUTE_MEMORY, FALSE);
		ExitStatus=DisableDeviceDecoding(Dev,stOptRomSpace);
	} //if(Dev->Bar[PCI_MAX_BAR_NO].Type!=tBarUnused) 
	//We tryed to Find PCI Off Board Card Option ROM because it's ROM BAR was valid. 
	//But Some On Board Devices Implements ROM BAR but It does not have a valid ROM
	//So I will check for embeded Option ROM if Status==EFI_NOT_FOUND and ExitStatus==EFI_SUCCES
#if CSM_SUPPORT
	if((Status==EFI_NOT_FOUND)&&(ExitStatus==EFI_SUCCESS)){
		//Here we'll try to locate Embeded rom For Onboard devices.
		//we'll use CSM Ext Protocol to do so.
		if(gLegacyBiosExt==NULL) Status=EFI_NOT_FOUND;
		else {
		//Got Protocol. Will try to use it.
			Status=gLegacyBiosExt->GetEmbeddedRom(0x20,Dev->DevVenId.VenId, 
						Dev->DevVenId.DevId,&EmbRom, &OptRomSize);
			if(EFI_ERROR(Status)) {
				Dev->PciIo.RomImage=NULL;
				Dev->PciIo.RomSize=0;
			} else {
				//Check if Embeded Op ROM is valid...
				if(*((UINT16*)EmbRom)!=PCI_OPT_ROM_SIG) Status=EFI_NOT_FOUND;
				else{
					//Allocate buffer for ROM Image.
					Dev->PciIo.RomImage=Malloc(OptRomSize);
					if(Dev->PciIo.RomImage==NULL) Status=EFI_OUT_OF_RESOURCES;
					else {
						MemCpy(Dev->PciIo.RomImage,EmbRom,OptRomSize);
						Dev->PciIo.RomSize=OptRomSize;
                        Dev->Capab |= (EFI_PCI_IO_ATTRIBUTE_EMBEDDED_DEVICE + EFI_PCI_IO_ATTRIBUTE_EMBEDDED_ROM);
                        Dev->Attrib  |= (EFI_PCI_IO_ATTRIBUTE_EMBEDDED_DEVICE + EFI_PCI_IO_ATTRIBUTE_EMBEDDED_ROM);
					}
				}
			}		
		}
	}
#endif
	if(EFI_ERROR(ExitStatus)) return ExitStatus;
//(EIP42750+)
    //Calling OEM Hook to override Option Rom content...
    Status=PciPortOemGetOptRom(Dev, &Dev->PciIo.RomImage, &Dev->PciIo.RomSize);
    //if porting hook not implemented, adjust Status, otherwice return whatever we got 
    if(Status==EFI_UNSUPPORTED) Status=EFI_SUCCESS;
//(EIP42750-)
	return Status;
}


#if ((defined EFI_SPECIFICATION_VERSION) && (EFI_SPECIFICATION_VERSION >= 0x2001F))
EFI_STATUS LoadRomFile( IN EFI_LOAD_FILE2_PROTOCOL  *This, 
                        IN EFI_DEVICE_PATH_PROTOCOL *FilePath,
                    	IN BOOLEAN                  BootPolicy, 
                        IN OUT UINTN                *BufferSize,
	                    IN VOID                     *Buffer OPTIONAL)
{
    PCI_LOAD_FILE_DATA  *lfdata=(PCI_LOAD_FILE_DATA*)This;   
    PCI_DEV_INFO        *dev=lfdata->Owner;
    EFI_STATUS          Status;
    UINTN               i;
    MEDIA_RELATIVE_OFFSET_RANGE_DEVICE_PATH *dp=(MEDIA_RELATIVE_OFFSET_RANGE_DEVICE_PATH*)FilePath;    
    PCI_ROM_IMAGE_DATA  *romdata;
    BOOLEAN             found=FALSE;
	VOID					*imgb=NULL;
	UINT32					imgsz;
//---------------------

    //Check input parameters first...
    if( (dev->Signature != AMI_PCI_SIG) || 
        (FilePath==NULL) || (BufferSize==NULL) ||
        (dp->Header.Type!=MEDIA_DEVICE_PATH)||
        (dp->Header.Type!=MEDIA_RELATIVE_OFFSET_RANGE_DP)||
        (dev->EfiRomCount==0) ) return EFI_INVALID_PARAMETER;
    
    if(BootPolicy==TRUE) return EFI_UNSUPPORTED;

    for(i=0;i<dev->EfiRomCount; i++){
        romdata=dev->EfiRomImages[i];
        //verify that relative odffset corresponds to the images stored.
        if(MemCmp(dp,&romdata->RomImageDP,sizeof(MEDIA_RELATIVE_OFFSET_RANGE_DEVICE_PATH))==0){
            found=TRUE;
            break;
        }                
    }
    
    if(!found) return EFI_NOT_FOUND;
    
    if((romdata->ActualSize<*BufferSize)||(Buffer==NULL)){
        *BufferSize=romdata->ActualSize;
        if(Buffer==NULL)return EFI_SUCCESS;
        else return EFI_BUFFER_TOO_SMALL;
    }
    
    //here we have checked everything Time to read file ...
    Status=ReadEfiRom(dev, romdata,&imgb,&imgsz);
    if(EFI_ERROR(Status)) return Status;

    MemCpy(Buffer,imgb,imgsz);
    
    pBS->FreePool(imgb);
    return Status;       

}
#endif

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   OvrGetDriver()
//
// Description: PCI Bus Specific Override Protocol Get Override Driver 
// function implementation of the PCI Bus Driver. 
//
// Input:
//  EFI_BUS_SPECIFIC_DRIVER_OVERRIDE_PROTOCOL **This    Pointer PCI Devicse's
//                                                      Bus Specific Override 
//                                                      Protocol Interface.
//  EFI_HANDLE IN OUT       *DriverImageHandle  Image Handle of the Option
//                                              ROM EFI Driver.
// Output:	EFI_STATUS
//  EFI_SUCCESS             When everything is going on fine!
//  EFI_NOT_FOUND		    When there are no more handles to override.
//  EFI_INVALID_PARAMETER   When Parameter passed is invalid.
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS OvrGetDriver(IN EFI_BUS_SPECIFIC_DRIVER_OVERRIDE_PROTOCOL  *This,
						IN OUT EFI_HANDLE                             *DriverImageHandle )
{
	PCI_BUS_OVERRIDE_DATA		*ovr=(PCI_BUS_OVERRIDE_DATA*)This;
	UINTN						i;
	EFI_HANDLE					himg=NULL;
    PCI_DEV_INFO                *dev=ovr->Owner;
    PCI_ROM_IMAGE_DATA          *romdata;
//------------------------------------------------------------------  

    if((DriverImageHandle==NULL)||(dev->EfiRomCount==0))return EFI_INVALID_PARAMETER;

    //Here we know dev->EfiRomCount>0
	if(*DriverImageHandle==NULL) {
        romdata=dev->EfiRomImages[0];
        himg=romdata->RomImgHandle;
	} else {
		for(i=0; i<dev->EfiRomCount; i++){
            romdata=dev->EfiRomImages[i];   
			if(*DriverImageHandle==romdata->RomImgHandle)break;
		}

		if(i==dev->EfiRomCount) return EFI_INVALID_PARAMETER;
	
		if(i<dev->EfiRomCount-1)himg=romdata->RomImgHandle;
		else return EFI_NOT_FOUND;
	}

	*DriverImageHandle=himg;
	return EFI_SUCCESS;
}

/*
//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   AddOvrHandle()
//
// Description: Adds EFI_HANDLE of the Addon Card Option ROM image to the 
// PCI Bus Driver Private Data.
//
// Input:
//  PCI_BUS_OVERRIDE_DATA   *OvrData    Pointer to the PCI Devicse's Bus 
//                                      Override data inside PCI_DEV_INFO
//  EFI_HANDLE              OvrHandle   Handle to add.
//  
// Output:	EFI_STATUS
//  EFI_SUCCESS             When everything is going on fine!
//  EFI_OUT_OF_RESOURCES    When system runs out of resources.
//  EFI_INVALID_PARAMETER   When Parameter passed is invalid.
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS AddOvrHandle( PCI_DEV_INFO *Device, EFI_HANDLE OvrHandle, UINTN StartOffset, UINTN EndOffset)
{
    PCI_ROM_IMAGE_DATA          *romdata;
//-------------------------------------------------
    if(Device->BusOvrData.BusOverride.GetDriver==NULL)Device->BusOvrData.BusOverride.GetDriver=OvrGetDriver;

		
	//Get the space needed
	romdata=MallocZ(sizeof(PCI_ROM_IMAGE_DATA));
	if (romdata==NULL) return EFI_OUT_OF_RESOURCES;	
	
    romdata->RomImgHandle=OvrHandle;
    romdata->RelOffsStart=StartOffset;
    romdata->RelOffsEnd=EndOffset;    

	return AppendItemLst((T_ITEM_LIST*)&Device->RomInitCnt, romdata);	
}
*/

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   DecompressOptRom()
//
// Description: Decompresses Option ROM Image if it is Compressed.
//
// Input:
//  VOID        *Image          Pointer at the compressed Option ROM Image.
//  UINT32      ImageLength     Length of the Compressed Image.
//  OUT VOID    **DecompImage   Place holder to return pointer to the 
//                              Decopressed Image.
//  OUT UINT32  ImageLength     Length of the Decompressed Image.
//
// Output:	EFI_STATUS
//  EFI_SUCCESS             When everything is going on fine!
//  EFI_OUT_OF_RESOURCES    When system runs out of resources.
//  EFI_INVALID_PARAMETER   When Parameter passed is invalid.
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS DecompressOptRom( VOID *Image, UINT32 ImageLength, VOID** DecompImage, UINT32 *DecompSize)
{
	EFI_STATUS 					Status;	
	EFI_DECOMPRESS_PROTOCOL		*dcp;
	UINT32						scrsz, imgsz;
	VOID						*imgb, *scrb;
//--------------------------------
	//Check for parameter first
	if(!DecompImage) return EFI_INVALID_PARAMETER;

	Status = pBS->LocateProtocol(&gEfiDecompressProtocolGuid, NULL,(VOID**)&dcp);
	if(EFI_ERROR(Status))return Status;

	Status = dcp->GetInfo(dcp,Image,ImageLength, &imgsz, &scrsz);
	if (EFI_ERROR (Status)) return Status;

	Status=pBS->AllocatePool(EfiBootServicesData, imgsz,&imgb);
	if(EFI_ERROR(Status)) return Status;

	Status=pBS->AllocatePool(EfiBootServicesData,	scrsz,&scrb);
	if(EFI_ERROR(Status)) return Status;

	Status=dcp->Decompress(dcp,Image,ImageLength,imgb,imgsz,scrb,scrsz);
	pBS->FreePool(scrb);

	if(!EFI_ERROR(Status)){
		*DecompImage=imgb;
		*DecompSize=imgsz;
	}

	return Status;
}


EFI_STATUS ReadEfiRom(PCI_DEV_INFO	*Dev, PCI_ROM_IMAGE_DATA *RomData, VOID **ImgBase, UINT32 *ImgSize){
    EFI_STATUS  Status=EFI_SUCCESS;
	VOID					*imgb;
	UINT32					imgsz;
//-------------------

    imgb=(VOID*)((UINTN)Dev->PciIo.RomImage+(UINTN)RomData->RomImageDP.StartingOffset);
    imgsz=(UINT32)(RomData->RomImageDP.EndingOffset-RomData->RomImageDP.StartingOffset+1);

    if (RomData->RomHeader->CompressionType){
        Status=DecompressOptRom((UINT8*)RomData->RomHeader+RomData->RomHeader->EfiImageOffset,imgsz,&imgb,&imgsz);
	} 
    
    if(!(EFI_ERROR(Status))){
        *ImgBase=imgb;
        *ImgSize=imgsz;
    }    
    return Status;

}



//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   InstallEfiOpRom()
//
// Description: Loads and Starts Native EFI PCI Option ROM.
//
// Input:
//  PCI_DEV_INFO            *Dev        Pointer PCI Devicse Private Data.
//  PCI_EFI_OPT_ROM_HEADER  *RomHeader  Pointer at PCI Option ROM Header
//  
// Output:	EFI_STATUS
//  EFI_SUCCESS             When everything is going on fine!
//  EFI_OUT_OF_RESOURCES    When system runs out of resources.
//  EFI_INVALID_PARAMETER   When Parameter passed is invalid.
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS InstallEfiOpRom(	PCI_DEV_INFO			*Dev,
							PCI_EFI_OPT_ROM_HEADER	*RomHeader,
                            PCI_DATA_STRUCTURE      *Pcir)
{
	EFI_STATUS				Status=0;
	VOID					*imgb;
	UINT32					imgsz;
    PCI_ROM_IMAGE_DATA      *romdata;
    EFI_DEVICE_PATH_PROTOCOL *romdp=NULL;
    
//-------------------------------------------

	if ((RomHeader->EfiSubsystem != EFI_IMAGE_BS_DRIVER) &&
		(RomHeader->EfiSubsystem != EFI_IMAGE_RT_DRIVER)) 
		return EFI_NOT_FOUND;

	// decompress it if needed
	if (RomHeader->CompressionType > 1)	return EFI_INVALID_PARAMETER;

	//Get the space needed
	romdata=MallocZ(sizeof(PCI_ROM_IMAGE_DATA));
	if (romdata==NULL) return EFI_OUT_OF_RESOURCES;

    //Fill RomData Parts
    romdata->RomHeader=RomHeader;
    //Init RELATIVE OFFS DP Header...
    romdata->RomImageDP.Header.Type=MEDIA_DEVICE_PATH;
    romdata->RomImageDP.Header.SubType=MEDIA_RELATIVE_OFFSET_RANGE_DP;
    SET_NODE_LENGTH(&romdata->RomImageDP.Header, sizeof(MEDIA_RELATIVE_OFFSET_RANGE_DEVICE_PATH));

	//imgsz=RomHeader->InitializationSize*512-RomHeader->EfiImageOffset;
    imgsz=(UINT32)DoubleCheckOpRom((VOID*)RomHeader, Pcir);
    imgsz-=RomHeader->EfiImageOffset;

    //Get Start..End offsets of Rom File...
    imgb=(VOID*)((UINT8*)RomHeader+RomHeader->EfiImageOffset);
    romdata->RomImageDP.StartingOffset=(UINT64)((UINTN)imgb-(UINTN)Dev->PciIo.RomImage);
    romdata->RomImageDP.EndingOffset=romdata->RomImageDP.StartingOffset+imgsz-1;
    
    Status=ReadEfiRom(Dev, romdata, &imgb, &imgsz);
    if(EFI_ERROR(Status)) return Status;		

    //update Actual File size..
    romdata->ActualSize=imgsz;
    
    //Form Rom Image Device Path from Dev->DevicePath + romdata->RomImgDP+DP_END...
    romdp=DPAddNode((VOID*)Dev->DevicePath, (VOID*)&romdata->RomImageDP);
    if(romdp==NULL) return EFI_OUT_OF_RESOURCES;

	//load image and start image
	Status=pBS->LoadImage(FALSE,gPciBusDriverBinding.ImageHandle,romdp,imgb,imgsz,&romdata->RomImgHandle);
	if (EFI_ERROR(Status)) return Status;

	Status=pBS->StartImage(romdata->RomImgHandle,NULL,NULL);
	if (EFI_ERROR(Status)) return Status;
							
    //Add romdata to the EfiRomList...
    Status=AppendItemLst((T_ITEM_LIST*)&Dev->RomInitCnt, romdata);
    if(EFI_ERROR(Status)) return Status;
    
    //update BusOvr Data...
    if(Dev->BusOvrData.BusOverride.GetDriver==NULL)Dev->BusOvrData.BusOverride.GetDriver=OvrGetDriver;
    
#if ((defined EFI_SPECIFICATION_VERSION) && (EFI_SPECIFICATION_VERSION >= 0x2001F))
    //Update LoadFile Data
    if(Dev->LoadFileData.LoadFile2.LoadFile==NULL)Dev->LoadFileData.LoadFile2.LoadFile=LoadRomFile;
#endif

    if(romdp!=NULL)pBS->FreePool(romdp);
    return Status;

}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   CheckPciRomDevId()
//
// Description: PCI Firmware Spec 3.0 defines some reserved field in PCIR 
// Structure as Device List Pointer. This function checks additional Device IDs  
//
// Input:
//  PCI_DEV_INFO           *Dev             Pointer PCI Devicse Private Data.
//  PCI_DATA_STRUCTURE     *PciRomStruct    Pointer at PCIR ROM Header
//  
// Output:	EFI_STATUS
//  EFI_SUCCESS             When everything is going on fine!
//  EFI_UNSUPPORTED         When ROM is not compatible with device.
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS CheckPciRomDevId(PCI_DEV_INFO    *Dev, PCI_DATA_STRUCTURE *PciRomStruct){
    UINT16      *did;
//--------------------------
    if(Dev->DevVenId.VenId != PciRomStruct->VendorId) return EFI_NOT_FOUND;
    
    if(Dev->DevVenId.DevId != PciRomStruct->DeviceId){
        //Dev->DevVenId.DevId ==0x0000 special case - (Service ROM like PXE, iSCIS boot agent)
        if(Dev->DevVenId.DevId==0) return EFI_SUCCESS;

        //Check Device List if any...
        if(PciRomStruct->Reserved0 == 0) return EFI_UNSUPPORTED;

        did=(UINT16*)((UINT8*)PciRomStruct + PciRomStruct->Reserved0);        
        
        while(*did != 0){
            if(Dev->DevVenId.DevId==*did) return EFI_SUCCESS;        
            did++; // next device list entry      
        }
        return EFI_UNSUPPORTED;    
    }

    return EFI_SUCCESS;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   ExecuteUefiRom()
//
// Description: This function decide to launch or not UEFI compatible  
// Option ROM
//
// Input:
//  UINT8       PciClass    PCI Class Code Of the Device.
//  
// Output:	BOOLEAN
//  TRUE             		Launch UEFI Option ROM
//  FALSE                   NOT Launch UEFI Option ROM
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
BOOLEAN ExecuteUefiRom(PCI_DEV_INFO *Dev)
{
    EFI_STATUS Status;
    AMI_OPROM_POLICY_PROTOCOL *AmiOpromPolicyProtocol;
    static EFI_GUID AmiOpromPolicyProtocolGuid = AMI_OPROM_POLICY_PROTOCOL_GUID;

    Status = pBS->LocateProtocol(&AmiOpromPolicyProtocolGuid, NULL, &AmiOpromPolicyProtocol);
    if(EFI_ERROR(Status))   //if CSM OptOut is disabled we should always launch UEFI OpROM
        return TRUE;

    Status = AmiOpromPolicyProtocol->CheckUefiOpromPolicy(AmiOpromPolicyProtocol, Dev->Handle);
    return (EFI_ERROR(Status)) ? FALSE : TRUE;
}


//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   ActivateOptRom()
//
// Description: This function parses Option ROM Image to decide which 
// Image to give control to and updates PciIO->OptioRom and  
// PciIO->OptioRomSize with Correct values.
//
// Input:
//  PCI_DEV_INFO    *Dev    Pointer PCI Devicse Private Data.
//  
// Output:	EFI_STATUS
//  EFI_SUCCESS             When everything is going on fine!
//  EFI_OUT_OF_RESOURCES    When system runs out of resources.
//  EFI_NOT_FOUND           When Device does not have any ROMs.
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS ActivateOptRom(PCI_DEV_INFO *Dev)
{
	UINT8					*cp; 
	UINTN					roms=0;
	UINTN					romc;
	PCI_EFI_OPT_ROM_HEADER	*rh;
	PCI_DATA_STRUCTURE		*pcir; 
	BOOLEAN					ff=TRUE;//, fnd=FALSE;
	BOOLEAN 				efior=FALSE;
	BOOLEAN					notarom=FALSE;
	UINTN					sz=0;  
	INT64					rsz=(INT64)Dev->PciIo.RomSize;
	EFI_STATUS				Status=EFI_SUCCESS;
    BOOLEAN                 RomMatch=FALSE;
//------------------------
	if (!Dev->PciIo.RomImage) return EFI_NOT_FOUND;

	cp=(UINT8*)Dev->PciIo.RomImage;
	for(romc=0;;romc++){
		rsz-=sz;
		if(rsz<=0)return Status;
		cp=cp+sz;
		
		rh=(PCI_EFI_OPT_ROM_HEADER*)cp;
		//Check if a valid signarture here 
		if(ff){//first time here
			if(rh->Signature!=PCI_OPT_ROM_SIG){
				notarom=TRUE;
				break;
			}
			roms=(UINTN)rh;
		} else {
			//here is the case when we can not find a valid signature for the next image  
			//withing the Option ROM
			if(rh->Signature!=PCI_OPT_ROM_SIG){
				sz=512;
				continue;				
			} 
		}		
		ff=FALSE;
	
		//Check if it is EFI Opt ROM		
		if(rh->EfiSignature==PCI_OPT_ROM_EFISIG) efior=TRUE;
		else efior=FALSE;

		//we got what we were looking for...
		pcir=(PCI_DATA_STRUCTURE*)(cp+rh->PcirOffset);
		if(pcir->Signature!=PCI_PCIR_SIG) continue;

        //Here is some more conditions to check.
        //some ROMs has Different Sizes filled in 0x55AA ROM Header and in PCIR structure.
        //So check which size is right by looking one 

        //PCI Firmware Spec 3.0 defines some reserved field in PCIR Structure as Device List Pointer  
        Status=CheckPciRomDevId(Dev, pcir);
        if(EFI_ERROR(Status)) {
            if(Status==EFI_NOT_FOUND){
                PCI_TRACE((TRACE_PCI," ROM Img #%d Dev.VID!=PCIR.VID ", romc));
            } else PCI_TRACE((TRACE_PCI," ROM Img #%d Dev.DID!=PCIR.DID ", romc));
        } else RomMatch=TRUE;
 
       //Check Setup option which Option ROM to post Legacy = 0 \[EFI Compatible = 1]
        if( ExecuteUefiRom(Dev) ) { 
    		//here we go...let's see what it is
		    //check conditions under which we must process EFI OptROM
		    if( efior && pcir->CodeType == PCI_CODE_TYPE_EFI_IMAGE && RomMatch) 
            {
                PCI_TRACE((TRACE_PCI,"(Install EFI ROM="));
                Status=InstallEfiOpRom(Dev,rh, pcir);
                PCI_TRACE((TRACE_PCI,"%r)", Status));
            }
        }
		
		if(pcir->Indicator&0x80) {
			break;
		}
		//else keep circling until we reach the end...
        sz=DoubleCheckOpRom((VOID*)rh, pcir);
	}	

	if(notarom || !RomMatch){
		Status=pBS->FreePool(Dev->PciIo.RomImage);
		Dev->PciIo.RomImage=NULL;
		Dev->PciIo.RomSize=0;
		return EFI_NOT_FOUND;
	}

	return EFI_SUCCESS;
}


//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   InstallPciDevice()
//
// Description: This function performs the following operations
// 1. Register Device with CORE by getting a brand new handle
// 2. Install PciIo Protocol Interface on This Device
// 3. Generates EFI_DEVICE_PPATH protocol instance for "Dev"ice
// 4. Installs DevicePath Protocol on Created Handle
// 5. If Device has Option ROM copy it to the Memory Buffer
// 6. If 5 is TRUE and if Opt ROM has EFI compliant Image 
// installs Bus Override protocol.
//
// Input:
//  EFI_HANDLE      ControllerHandle  Device's Controller Handle.
//  PCI_DEV_INFO    *Dev    Pointer PCI Devicse Private Data.
//  
// Output:	EFI_STATUS
//  EFI_SUCCESS             When everything is going on fine!
//  EFI_OUT_OF_RESOURCES    When system runs out of resources.
//  EFI_INVALID_PARAMETER   When Parameter passed is invalid.
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS InstallPciDevice(EFI_HANDLE ControllerHandle, PCI_DEV_INFO *Dev)
{
	EFI_STATUS		Status=0;	
    EFI_STATUS      OpRomStatus = EFI_NOT_FOUND;
	BOOLEAN			ndp=FALSE;//NewDevicePath
#if ((defined EFI_SPECIFICATION_VERSION) && (EFI_SPECIFICATION_VERSION >= 0x2001F))
	VOID	*buff[8]={NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL};
#else
	VOID        	*buff[6]={NULL,NULL,NULL,NULL,NULL,NULL};
#endif
	UINTN			offs=0;
    BOOLEAN         cr=TRUE;
//-----------------------------------

	PCI_TRACE((TRACE_PCI,"PciBus: Installing PCI IO for B%X|D%X|F%X; ->->->->\n", Dev->Address.Addr.Bus,
			Dev->Address.Addr.Device,Dev->Address.Addr.Function));

	//Check if Device Has Been already started
	if(Dev->Started) {
        Status=EFI_ALREADY_STARTED;
		PCI_TRACE((TRACE_PCI," -> Dev.Started=1; -> %r\n",Status));
        return Status;
	}

	if(Dev->Type==tPciRootBrg) ndp=FALSE;
	else ndp=TRUE;
	
    if(Dev->PciIo.PollMem!=gPciIoInstance.PollMem){
    	pBS->CopyMem(&Dev->PciIo, &gPciIoInstance, sizeof(EFI_PCI_IO_PROTOCOL));
    } else cr=FALSE;
	buff[offs]=&gPciIoProtocolGuid;
	buff[offs+1]=&Dev->PciIo;
	offs+=2;

	//Install Device Path Protocol on newly created Handle
	if(ndp){
		buff[offs]=&gDevicePathProtocolGuid;
		buff[offs+1]=Dev->DevicePath;
		offs+=2;
	}
	//Check if Device has Opton ROM ...
    if(cr) 
        OpRomStatus=GetOptRom(Dev);
    else if(Dev->PciIo.RomImage != NULL && Dev->PciIo.RomSize != 0) //OpROM was initialized earlier
        OpRomStatus = EFI_SUCCESS;

	Status=pBS->InstallMultipleProtocolInterfaces(
					&Dev->Handle,
					buff[0],buff[1], //PciIO    GUID - I/F pare
					buff[2],buff[3], //DevPath  GUID - I/F pare
					NULL, NULL );
	PCI_TRACE((TRACE_PCI,"/nPciBus: Installing DP; PCIO Status=%r",Status));
    ASSERT_EFI_ERROR(Status);
   	if(EFI_ERROR(Status)) return Status;

	//update offset it might be ==2 if ndp==FALSE, but we need it as 4 after this point.
	offs=4;

	PCI_TRACE((TRACE_PCI,":GetRom="));

	if(EFI_ERROR(OpRomStatus)){
		Dev->RomBarError=TRUE;
		Dev->PciIo.RomImage=NULL;
		Dev->PciIo.RomSize=0;
       	PCI_TRACE((TRACE_PCI,"%r\n", OpRomStatus));	
	} else {
        //Print Status from GetOptRom()
		PCI_TRACE((TRACE_PCI,"%r :ActivateRom", OpRomStatus));
		if(cr) Status=ActivateOptRom(Dev);
		PCI_TRACE((TRACE_PCI,"=%r\n", Status));
		if(EFI_ERROR(Status)){
			if(Status==EFI_NOT_FOUND) Status=EFI_SUCCESS; //just there are no any EFI Opt ROMs
            else return Status;
		}

		//Check if Override handle count gets changed..
		//then install Bus Override protocol interface
		if(Dev->BusOvrData.BusOverride.GetDriver!=NULL){
			buff[offs]=&gBusSpecificDriverOverrideProtocolGuid;
			buff[offs+1]=&Dev->BusOvrData.BusOverride;
		}

#if ((defined EFI_SPECIFICATION_VERSION) && (EFI_SPECIFICATION_VERSION >= 0x2001F))
		offs+=2;
        if(Dev->LoadFileData.LoadFile2.LoadFile!=NULL){
			buff[offs]=&gEfiLoadFile2ProtocolGuid;
			buff[offs+1]=&Dev->LoadFileData.LoadFile2;
		}
#endif

	}

	
    //Now Before installing Protocol Interface for THIS device.
    //Call Porting Hook to do OEM Custom Programming of the device.
    //PciIo and all the stuff been updated for this device.
    //But NO notification yet for PciIO installation dispatchetd
    Status=PciPortOemProgDevice(Dev);

	PCI_TRACE((TRACE_PCI,":PciBus: Calling PciPortOemProgDevice() >Status=%r\n", Status));

    if(buff[5]!=NULL){
	    Status=pBS->InstallMultipleProtocolInterfaces(
					&Dev->Handle,
					buff[4],buff[5], //PciIO    GUID - I/F pare
#if ((defined EFI_SPECIFICATION_VERSION) && (EFI_SPECIFICATION_VERSION >= 0x2001F))
					buff[6],buff[7], //LoadFile2  GUID - I/F pare if present
#endif
					NULL, NULL );

	    PCI_TRACE((TRACE_PCI," -> Installing BusOvr and LoadFile2 -> %r\n", Status));

	    if(EFI_ERROR(Status)) return Status;
    }

	if(Dev->Type>tPciRootBrg){//Don't Open Rb Protocol for itself
		Status=pBS->OpenProtocol(
					ControllerHandle, &gPciRootBridgeIoProtocolGuid,
					(VOID**)&Dev->RbIo, gPciBusDriverBinding.DriverBindingHandle,
					Dev->Handle, EFI_OPEN_PROTOCOL_BY_CHILD_CONTROLLER);
	}

	//Set Started Flag...
	Dev->Started=TRUE;
	return Status;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   StartPciChildDevice()
//
// Description: Starts PCI Devices Behind the Bridge. (Called recoursively)
// This function performs the following operations
// 1. Register Device with CORE by getting a brand new handle
// 2. Install PciIo Protocol Interface on This Device
// 3. Generates EFI_DEVICE_PPATH protocol instance for "Dev"ice
// 4. Installs DevicePath Protocol on Created Handle
// 5. If Device has Option ROM copy it to the Memory Buffer
// 6. If 5 is TRUE and if Opt ROM has EFI compliant Image 
// installs Bus Override protocol.
//
// Input:
//  EFI_HANDLE      ControllerHandle  Device's Controller Handle.
//  PCI_BRG_INFO    *Brg              Pointer at PCI Bridge Private Data.
//  EFI_DEVICE_PATH_PROTOCOL *RemainingDp Pointer at PCI Device Path
//                                    Protocol Instance or NULL.
//  
// Output:	EFI_STATUS
//  EFI_SUCCESS             When everything is going on fine!
//  EFI_OUT_OF_RESOURCES    When system runs out of resources.
//  EFI_INVALID_PARAMETER   When Parameter passed is invalid.
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS StartPciChildDevice(EFI_HANDLE ControllerHandle,PCI_BRG_INFO *Brg, PCI_DEVICE_PATH *RemainingDp)
{
	PCI_DEV_INFO				*dev;
	EFI_STATUS					Status = EFI_NOT_FOUND;
	UINTN						i;
	PCI_DEVICE_PATH				*pcidp=RemainingDp;
    BOOLEAN                     Started=FALSE, Success=FALSE;
//-------------------------------
	
	PCI_TRACE((TRACE_PCI, "PciBus: StartPciChildDevice -> Bridge has %d Child Devices \n",Brg->Bridge.ChildCount));

    //Check if Device Path is a valid PCI Device Path
    if (pcidp!=NULL){
		//Check if remaining device path is a valid PCI device path
	    if( EFI_ERROR(CheckPciDevicePath(&pcidp->Header)) ) return EFI_INVALID_PARAMETER;
        //If remaining device path is provided, we must find the device.
    }

	if(!Brg->Bridge.ChildCount)	return Status;

	for(i=0; i<Brg->Bridge.ChildCount; i++){
		dev=Brg->Bridge.ChildList[i];
        if(dev->OutOfResRemove) continue;
		//if Remaining Device Path provided start only specified device 
		if(pcidp) 
		{	
		    if(pcidp->Device != dev->Address.Addr.Device ||
			   pcidp->Function != dev->Address.Addr.Function
            ) continue;
			// The Device Path of this Device matches provided
			Status=InstallPciDevice(ControllerHandle, dev); 
			if (EFI_ERROR(Status)){
                if(Status==EFI_ALREADY_STARTED) Started=TRUE;
                else return Status;
            } else Success=TRUE;

			//if Device is P2P bridge than BDS might like to start next DP node
			//So recousively call this function to find desired Device
            pcidp++;
			if(dev->Type==tPci2PciBrg && !isEndNode(&pcidp->Header))
				Status=StartPciChildDevice(ControllerHandle,(PCI_BRG_INFO*)dev,pcidp);


            //if(!EFI_ERROR(Status) && Status == EFI_NOT_FOUND){
            //    if(Started && !Success) Status=EFI_ALREADY_STARTED;
            //}    
	        return Status;
		} 
		else //if no Remaining Device Path provided start all devices
		{
			Status=InstallPciDevice(ControllerHandle, dev); 
			if (EFI_ERROR(Status)){
                if(Status==EFI_ALREADY_STARTED){
                    Started=TRUE;
                    Status=EFI_SUCCESS;
                } else return Status;
            } else Success=TRUE;

			//if Device is P2P bridge recousively call this function 
			if(dev->Type==tPci2PciBrg){  
				Status=StartPciChildDevice(ControllerHandle,(PCI_BRG_INFO*)dev,pcidp);
				if(EFI_ERROR(Status)){
                    //StartPciChildDevice() could return EFI_ALREADY_STARTED or EFI_NOT_FOUND
                    //this is if we have started this device already, of Bridge don't have any 
                    //childs behind it. This is normal and we shouldn't break the loop.
                    //All other ERROR Statuses suppose to break the loop and raise an ERROR.
                    if(Status==EFI_ALREADY_STARTED || Status==EFI_NOT_FOUND){
                        Started=TRUE;
                        Status=EFI_SUCCESS;
                    } else return Status;
                } else Success=TRUE;
			}  	
		}
	}//for

    if(!EFI_ERROR(Status)){
        if(Started && !Success) Status=EFI_ALREADY_STARTED;
    }    
	return Status;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   StartPciDevices()
//
// Description: Installs PCI Io Protocol Instance on all or some PCI Devices
// in the System
//
// Input:
//  EFI_HANDLE      ControllerHandle  Device's Controller Handle.
//  EFI_DEVICE_PATH_PROTOCOL *RemainingDevicePath Pointer at PCI Device Path
//                                    Protocol Instance or NULL.
//  
// Output:	EFI_STATUS
//  EFI_SUCCESS             When everything is going on fine!
//  EFI_OUT_OF_RESOURCES    When system runs out of resources.
//  EFI_INVALID_PARAMETER   When Parameter passed is invalid.
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS StartPciDevices(IN EFI_HANDLE ControllerHandle, IN EFI_DEVICE_PATH_PROTOCOL *RemainingDevicePath)
{
	EFI_STATUS			Status = EFI_DEVICE_ERROR;
	UINTN				i, j;
	PCI_DEV_INFO		*rbrg;
	PCI_HOST_INFO		*lhst; //local host
    EFI_DEVICE_PATH_PROTOCOL *rdp=RemainingDevicePath;
//---------------------------------------------	
	PCI_TRACE((TRACE_PCI, "\n====================================================================\n"));
	PCI_TRACE((TRACE_PCI, "PciBus: StartPciDevices Called -> hCtrl=0x%X; RemainingDp=0x%X;\n",ControllerHandle,RemainingDevicePath));

	//Check if RemainingDevicePath is valid
	if(rdp!=NULL){

        if (isEndNode(rdp)) {
            PCI_TRACE((TRACE_PCI, "PciBus: RemainingDp==EndOfDpNode\n"));
            return EFI_SUCCESS;
        } else {
		    Status=CheckPciDevicePath(rdp);
		    PCI_TRACE((TRACE_PCI, "PciBus: START CheckPciDp -> %r\n",Status));
    		if(EFI_ERROR(Status)) goto ExitLbl;
        }
	}
	
	//find Root Bridge first
	for(j=0; j<gHostCnt; j++){
		lhst=&gPciHost[j];
		for(i=0; i<lhst->RbCount; i++){
			rbrg=lhst->RootBridges[i];

			if(rbrg->Handle==ControllerHandle){ 

    			Status=pBS->OpenProtocol(rbrg->Handle,
				    &gPciRootBridgeIoProtocolGuid,(VOID **)&rbrg->RbIo, 
				    gPciBusDriverBinding.DriverBindingHandle,rbrg->Handle,
				    EFI_OPEN_PROTOCOL_BY_DRIVER );

                if(EFI_ERROR(Status)){
                    if( Status!=EFI_ALREADY_STARTED ) return Status;
                    else Status=EFI_SUCCESS;
                }  

				Status=StartPciChildDevice(ControllerHandle,(PCI_BRG_INFO*)rbrg,(PCI_DEVICE_PATH*)rdp);
				break;
			}
		}
	}
ExitLbl:

	PCI_TRACE((TRACE_PCI, "PciBus: StartPciChildDevice -> %r\n",Status));
	PCI_TRACE((TRACE_PCI, "====================================================================\n"));

	return Status;
}

EFI_STATUS LocateDevHandle(PCI_DEV_INFO *Dev, T_ITEM_LIST *PciHnd){
    UINTN       i;  
    EFI_HANDLE  h;
//------------------------
    for(i=0; i<PciHnd->ItemCount; i++){
        h=*(EFI_HANDLE*)(PciHnd->Items[i]);
        if(Dev->Handle==h){
            DeleteItemLst(PciHnd, i, FALSE);
            Dev->Handle=NULL;
            return EFI_SUCCESS;
        }
    }
    return EFI_NOT_FOUND;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   StopPciDevice()
//
// Description: Stops PCI Device referenced as "Dev". Called From 
// StopPciDeviceBrg() function.
//
// Input:
//  PCI_DEV_INFO    *Dev    Pointer PCI Devicse Private Data.
//  EFI_HANDLE      Controller Device's Controller Handle.
//  
// Output:	EFI_STATUS
//  EFI_SUCCESS             When everything is going on fine!
//  EFI_OUT_OF_RESOURCES    When system runs out of resources.
//  EFI_INVALID_PARAMETER   When Parameter passed is invalid.
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS StopPciDevice(PCI_DEV_INFO *Dev,EFI_HANDLE Controller, T_ITEM_LIST *HndDb)
{
	EFI_STATUS 				Status=EFI_SUCCESS;
	UINTN					offs=0;
    BOOLEAN                 ndp;
#if ((defined EFI_SPECIFICATION_VERSION) && (EFI_SPECIFICATION_VERSION >= 0x2001F))
    VOID	*buff[8]={NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL};
#else
    VOID    *buff[6]={NULL,NULL,NULL,NULL,NULL,NULL};
#endif
//--------------------------------------------------------------------

    //Check if Device Has been Stopped already... 
    if(Dev->Started==FALSE) return EFI_SUCCESS;

    if(Dev->Type==tPciRootBrg) {
        Dev->Started=FALSE;
        return EFI_SUCCESS;
    }
	
   	PCI_TRACE((TRACE_PCI,"\nPciBusStop: Hnd=%X [B%X|D%X|F%X]->",Dev->Handle,
            Dev->Address.Addr.Bus,Dev->Address.Addr.Device, Dev->Address.Addr.Function));
	//Close Root Brg Protocol we've opened at the beginning.
    //Avoid Closing Protocol for RootBridge Device - we didn't open it.
    if(Dev->Handle!=Controller){ 
	    Status=pBS->CloseProtocol(Controller,&gPciRootBridgeIoProtocolGuid,
			    gPciBusDriverBinding.DriverBindingHandle, Dev->Handle);
        ndp=TRUE;
        PCI_TRACE((TRACE_PCI,"Close(RbIo)=%r;\n",Status));    
    } else {
        ndp=FALSE;
    }

    ASSERT_EFI_ERROR(Status);
	if(EFI_ERROR(Status)) return Status;
    
	buff[offs]=&gPciIoProtocolGuid;
	buff[offs+1]=&Dev->PciIo;
	offs+=2;

    //Same for Device Path: we did'not create device path for RootBridge device
    if(ndp){
    	buff[offs]=&gDevicePathProtocolGuid;
	    buff[offs+1]=Dev->DevicePath;
	    offs+=2;
	}
	
	//Now take care of BusSpecific Override	Protocol
	//If it was installed
	if(Dev->BusOvrData.BusOverride.GetDriver!=NULL){
		buff[offs]=&gBusSpecificDriverOverrideProtocolGuid;
		buff[offs+1]=&Dev->BusOvrData.BusOverride;
	}

#if ((defined EFI_SPECIFICATION_VERSION) && (EFI_SPECIFICATION_VERSION >= 0x2001F))
    //LoadFile2 Protocol
	offs+=2;
    if(Dev->LoadFileData.LoadFile2.LoadFile!=NULL){
        buff[offs]=&gEfiLoadFile2ProtocolGuid;
        buff[offs+1]=&Dev->LoadFileData.LoadFile2;
    }
#endif
	Status=pBS->UninstallMultipleProtocolInterfaces(
					Dev->Handle,
					buff[0],buff[1], //PciIO    GUID - I/F pare
					buff[2],buff[3], //DevPath  GUID - I/F pare
					buff[4],buff[5], //BusOwerride  GUID - I/F pare if present
#if ((defined EFI_SPECIFICATION_VERSION) && (EFI_SPECIFICATION_VERSION >= 0x2001F))
					buff[6],buff[7], //LoadFile2  GUID - I/F pare if present
#endif
					NULL, NULL );
    
   	PCI_TRACE((TRACE_PCI,"\nPciBusStop: Hnd=%X [B%X|D%X|F%X]->",Dev->Handle,
            Dev->Address.Addr.Bus,Dev->Address.Addr.Device, Dev->Address.Addr.Function));
    PCI_TRACE((TRACE_PCI,"Uninst(PciIo,DP,BusOvr)=%r;\n",Status));    
//DEBUG????
	if(!EFI_ERROR(Status)){
//DEBUG????
        Dev->Started=FALSE;
        if(HndDb!=NULL) Status=LocateDevHandle(Dev, HndDb);
        Dev->Handle=NULL;
//DEBUG????
    }
//DEBUG????
    ASSERT_EFI_ERROR(Status);
	return Status;
}	


//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   StopPciDeviceBrg()
//
// Description: Stops - Uninstalls PCI Io Protocol Instance from PCI Devices
// behind the PCI Bridge referenced as "Brg"
//
// Input:
//  PCI_BRG_INFO    *Brg        Pointer PCI Devicse Private Data.
//  EFI_HANDLE      Controller  Device's Controller (Parent) Handle.
//  
// Output:	EFI_STATUS
//  EFI_SUCCESS             When everything is going on fine!
//  EFI_OUT_OF_RESOURCES    When system runs out of resources.
//  EFI_INVALID_PARAMETER   When Parameter passed is invalid.
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS StopPciDeviceBrg(PCI_BRG_INFO *Brg, EFI_HANDLE Controller, T_ITEM_LIST   *HndDb)	
{
	PCI_DEV_INFO    *dev;
	UINTN           i;
	EFI_STATUS      Status;
//--------------------------------------------------------------------
	for(i=0; i<Brg->Bridge.ChildCount; i++){
		dev=Brg->Bridge.ChildList[i];
		//recoursive calling ourselfs 
		if(dev->Type==tPci2PciBrg) Status=StopPciDeviceBrg((PCI_BRG_INFO*)dev,Controller, HndDb);
        else Status=StopPciDevice(dev, Controller, HndDb);
        ASSERT_EFI_ERROR(Status);
		if(EFI_ERROR(Status)) return Status;
	}
	//After we done with the childs - Stop this Bridge itself
	Status=StopPciDevice(&Brg->Common, Controller, HndDb);
    ASSERT_EFI_ERROR(Status);

	return Status;
}	


//==============================================================================
//
// EFI Drver Binding Protocol Functions
//
//==============================================================================

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   PciBusSupported()
//
// Description: Supported Function of the EFI_DRIVER_BINDING_PROTOCOL
// for PCI Bus Driver.
//
// Notes:
//  See EFI Specification for detail description
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS PciBusSupported(IN EFI_DRIVER_BINDING_PROTOCOL    *This,
						   IN EFI_HANDLE                     Controller,
						   IN EFI_DEVICE_PATH_PROTOCOL       *RemainingDevicePath )
{
	EFI_STATUS                       Status;
	EFI_DEVICE_PATH_PROTOCOL         *ParentDevicePath;
	EFI_PCI_ROOT_BRIDGE_IO_PROTOCOL  *PciRootBridgeIo;
    EFI_DEVICE_PATH_PROTOCOL         *rdp=RemainingDevicePath;
//-----------------------------------------------
    
    
	//Check if it is valid Device Path 
	if (rdp != NULL){
        if (isEndNode(rdp)) rdp=NULL;
        else {   
		    Status=CheckPciDevicePath(rdp);
		    if (EFI_ERROR (Status))  return Status;
        }
	}

	//Open the IO Abstraction(s) needed to perform the supported test
	Status=pBS->OpenProtocol(Controller,
							&gDevicePathProtocolGuid,
							(VOID **)&ParentDevicePath,
							This->DriverBindingHandle,     
							Controller,   
							EFI_OPEN_PROTOCOL_BY_DRIVER	);

	if (Status == EFI_ALREADY_STARTED)return EFI_SUCCESS;
	if (EFI_ERROR (Status))  return Status;
 
	pBS->CloseProtocol(Controller,&gDevicePathProtocolGuid,This->DriverBindingHandle,
					 Controller);

	Status=pBS->OpenProtocol( Controller,
							  &gPciRootBridgeIoProtocolGuid,
							  (VOID **)&PciRootBridgeIo,
							  This->DriverBindingHandle,
							  Controller,
							  EFI_OPEN_PROTOCOL_BY_DRIVER );

	if(Status==EFI_ALREADY_STARTED) return EFI_SUCCESS;
  
	pBS->CloseProtocol(Controller,&gPciRootBridgeIoProtocolGuid,This->DriverBindingHandle,
						 Controller);

	return Status;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	PciBusStart()
//
// Description:	Start Function of the EFI_DRIVER_BINDING_PROTOCOL
// for PCI Bus Driver
//
// Notes:
//  See EFI Specification for detail description
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS PciBusStart(IN EFI_DRIVER_BINDING_PROTOCOL  *This,
					   IN EFI_HANDLE                   Controller,
					   IN EFI_DEVICE_PATH_PROTOCOL     *RemainingDevicePath )
{
	EFI_STATUS          Status;
    BOOLEAN             ft=FALSE;
//------------------------------------------------
    PROGRESS_CODE(DXE_PCI_BUS_BEGIN);

	PCI_TRACE((TRACE_PCI,"\n"));

	//Locate Boot Script protocol we will need it to record Extd PCIExpress Config Space Programing
    if(gBootScriptSave==NULL){
    	Status = pBS->LocateProtocol(&gEfiBootScriptSaveGuid, NULL, &gBootScriptSave);
	    if(EFI_ERROR(Status)) {
		    PCI_TRACE((TRACE_PCI,"PciBus: Unable to find EfiBootScriptSave Protocol! Status=%r EXITING!\n", Status));
		    return EFI_DEVICE_ERROR;
	    }
    }

#if CSM_SUPPORT
	//Locate Legacy BIOS Extended protocol, we will need it to record Extd PCIExpress Config Space Programing
    if(gLegacyBiosExt==NULL){
    	Status = pBS->LocateProtocol(&gEfiLegacyBiosExtProtocolGuid, NULL, &gLegacyBiosExt);
	    if(EFI_ERROR(Status)) {
		    PCI_TRACE((TRACE_PCI,"PciBus: Unable to find Legacy Bios Extension Protocol! Status=%r\n", Status));
		    gLegacyBiosExt=NULL;
	    }
    }
#endif

    //Locate Ami Board Info Protocol
    if(gAmiBoardInfo==NULL){
    	Status = pBS->LocateProtocol(&gAmiBoardInfoProtocolGuid, NULL, &gAmiBoardInfo);
	    if(EFI_ERROR(Status)) {
		    PCI_TRACE((TRACE_PCI,"PciBus: Unable to find AMI Board Info Protocol! Status=%r\n", Status));
		    return Status;
	    }
        ft=TRUE;
    }

	//Create Pci Setup Data Buffer;
    if(gPciSetupData==NULL){
        gPciSetupData=MallocZ(sizeof(PCI_SETUP_DATA));
        if (gPciSetupData==NULL) return EFI_OUT_OF_RESOURCES;
        //Call Board Specific function from PciPort.c to fill PCI Setup data buffer
        BrdGetPciSetupData(gPciSetupData);
    }

	// Enumerate the entire host bridge
	Status = EnumerateAll(Controller);
    if(ft){
#if EFI_DEBUG
    //Print Bus Xlat table 
        UINTN               i;
        PCI_IRQ_PIC_ROUTE   *ir;
        PCI_IRQ_APIC_ROUTE  *ar;
    //-----------
   		PCI_TRACE((TRACE_PCI,"PciBus: Printing PIC $PIR table, %d entries \n", gAmiBoardInfo->PicRoutLength/sizeof(PCI_IRQ_PIC_ROUTE) ));
   		PCI_TRACE((TRACE_PCI,"============================================================\n"));
   		PCI_TRACE((TRACE_PCI," #  Bus  D|F  PIRQ A    PIRQ B    PIRQ C    PIRQ D    Slt#\n"));
   		PCI_TRACE((TRACE_PCI,"------------------------------------------------------------\n"));
	    for(i=0; i<(gAmiBoardInfo->PicRoutLength/sizeof(PCI_IRQ_PIC_ROUTE));i++){
            ir=&gAmiBoardInfo->PicRoutTable[i];
    		PCI_TRACE((TRACE_PCI,"%02d  %02X  %02X|%X  %02X->%04X  %02X->%04X  %02X->%04X  %02X->%04X  %02X\n", i,
                            ir->PciBusNumber, ir->DevFun.Dev,ir->DevFun.Fun,
                            ir->PciIrq[0].ChipsetReg, ir->PciIrq[0].IrqMask,
                            ir->PciIrq[1].ChipsetReg, ir->PciIrq[1].IrqMask,
                            ir->PciIrq[2].ChipsetReg, ir->PciIrq[2].IrqMask,
                            ir->PciIrq[3].ChipsetReg, ir->PciIrq[3].IrqMask,
                            ir->SlotNum));
        }
   		PCI_TRACE((TRACE_PCI,"============================================================\n"));
   		PCI_TRACE((TRACE_PCI,"\nPciBus: Printing APIC table, %d entries \n", gAmiBoardInfo->ApicRoutLength/sizeof(PCI_IRQ_APIC_ROUTE) ));
   		PCI_TRACE((TRACE_PCI,"============================================================\n"));
   		PCI_TRACE((TRACE_PCI," #  Bus  Dev  PIRQ A    PIRQ B    PIRQ C    PIRQ D\n"));
   		PCI_TRACE((TRACE_PCI,"------------------------------------------------------------\n"));
	    for(i=0; i<(gAmiBoardInfo->ApicRoutLength/sizeof(PCI_IRQ_APIC_ROUTE));i++){
            ar=&gAmiBoardInfo->ApicRoutTable[i];
    		PCI_TRACE((TRACE_PCI,"%02d  %02X   %02X   %02X ID=%02X  %02X ID=%02X  %02X ID=%02X  %02X ID=%02X\n", i,
                            ar->PciBusNumber, ar->DeviceNumber,
                            ar->Intn[0].IoApicItin, ar->Intn[0].IoApicId,
                            ar->Intn[1].IoApicItin, ar->Intn[1].IoApicId,
                            ar->Intn[2].IoApicItin, ar->Intn[2].IoApicId,
                            ar->Intn[3].IoApicItin, ar->Intn[3].IoApicId));
        }
   		PCI_TRACE((TRACE_PCI,"============================================================\n"));
    
#endif
        RemoveUnusedIrqEntries();
        gAmiBoardInfo->DataValid=TRUE;
    } 

    ASSERT_EFI_ERROR(Status);
	if (EFI_ERROR (Status)) return Status;
 
    //If Enumeration is OK install Extended PCI BUS Protocol Interface NOW.
    //Only if we have not done it before. It is only single instance on PciBusExt possible.
    if(gAmiExtPciBusProtocol.PciExtHanle==NULL){
        Status=pBS->InstallMultipleProtocolInterfaces( &gAmiExtPciBusProtocol.PciExtHanle,
                               &gAmiExtPciBusProtocolGuid, &gAmiExtPciBusProtocol, NULL);
    }

	if (EFI_ERROR (Status)){
		PCI_TRACE((TRACE_PCI,"PciBus: Unable to INSTALL Extended PCI Bus Protocol! Status=%r\n", Status));
    }
    ASSERT_EFI_ERROR(Status);
 
	// Enable PCI device specified by remaining device path. BDS or other driver can call the
	// start more than once.
	Status=StartPciDevices (Controller, RemainingDevicePath);
    
	return Status;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   PciBusStop()
//
// Description: Stop Function of the EFI_DRIVER_BINDING_PROTOCOL
// for PCI Bus Driver.
//
// Notes:
//  See EFI Specification for detail description
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS PciBusStop(IN EFI_DRIVER_BINDING_PROTOCOL  *This,
					  IN EFI_HANDLE                   Controller,
					  IN UINTN                        NumberOfChildren,
					  IN EFI_HANDLE                   *ChildHandleBuffer)
{
	EFI_STATUS         	Status=0;
	PCI_DEV_INFO		*dev=NULL;
	UINTN				i; 
    T_ITEM_LIST         PciHndDb={0,0,NULL};
    EFI_HANDLE          hnd;
//------------------------------------------------
    PCI_TRACE((TRACE_PCI,"\nPciBusStop: NumberOfChildren=0x%X, Controller=0x%X\n",NumberOfChildren, Controller));

	if (NumberOfChildren == 0) {
		// Close the bus driver
		//mST->BootServices->CloseProtocol(Controller,&gDevicePathProtocolGuid,
		//	This->DriverBindingHandle, Controller);
		dev=FindPciDeviceByHandle(Controller);
		if(dev)	Status=StopPciDeviceBrg((PCI_BRG_INFO*)dev, Controller, NULL);
 		else Status=EFI_NOT_FOUND;	
		ASSERT_EFI_ERROR(Status);
        //Close PCI Rooty Bridge Protocol we opened BY_DRIVER
		pBS->CloseProtocol(Controller,&gPciRootBridgeIoProtocolGuid,
			This->DriverBindingHandle,Controller);
	} else {
        //Populate PciHandle Database we need to stop. If we will enter recoursive 
        //call we need to rtemove stopped handles from DB inside recoursive call 
        //to avoid getting EFI_INVALID_PARAMETER trying to Stop already stopped devices.
		for(i=0; i<NumberOfChildren; i++){
            AppendItemLst(&PciHndDb, &ChildHandleBuffer[i]);
            PCI_TRACE((TRACE_PCI,"Hnd #%X: %X \n", i, ChildHandleBuffer[i]));
        }

        //Stopping all the childs 
        while(PciHndDb.ItemCount){
            hnd=*(EFI_HANDLE*)(PciHndDb.Items[0]);
            dev=FindPciDeviceByHandle(hnd);
   		    if(dev){
                //If device a bridge stop all its childs first 
                if(dev->Type==tPci2PciBrg)Status=StopPciDeviceBrg((PCI_BRG_INFO*)dev,Controller, &PciHndDb);		
                else Status=StopPciDevice(dev,Controller,&PciHndDb);
                ASSERT_EFI_ERROR(Status);
                if(EFI_ERROR(Status))return Status;
            } else {
                Status=EFI_NOT_FOUND;
                break;
            }
            ASSERT_EFI_ERROR(Status);
        }//while...
	}

    if(gAmiExtPciBusProtocol.PciExtHanle!=NULL){
        Status=pBS->UninstallMultipleProtocolInterfaces( gAmiExtPciBusProtocol.PciExtHanle,
                               &gAmiExtPciBusProtocolGuid, &gAmiExtPciBusProtocol, NULL);
        if (!EFI_ERROR(Status)) {
            gAmiExtPciBusProtocol.PciExtHanle=NULL;
        }
    }

    //Cleanup used memory...
	ClearItemLst(&PciHndDb, FALSE);
	return Status;
}


//////////////////////////////////////////////////////////////////////////////
//----------------------------------------------------------------------------
// PCI BUS Extended Protocol Function Implementation

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   PciExtGetDevice()
//
// Description: Locates PCI_DEV_INFO using passed PCI Device Handle or PciIo
// Protocol pointer.
// Input:
//  EFI_HANDLE              PciDeviceHandle Handle of the PCI Device to check.
//  EFI_PCI_IO_PROTOCOL*    PciIo 		    Pointer to the instance of PCI IO Protocol (OPTIONAL)
//  
// Output:	
//  PCI_DEV_INFO*           When everything is going on fine!
//  NULL                    If no such device exists.
//
// Note: 
//  If PciDeviceHandle == NULL, PciIo must be valid.
//  If *PciIo == NULL PciDeviceHandle must be valid.
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
PCI_DEV_INFO*   PciExtGetDevice(EFI_HANDLE PciDeviceHandle, EFI_PCI_IO_PROTOCOL *PciIo){
	PCI_DEV_INFO		*dev=NULL;
//------------------------------------        
    if(PciDeviceHandle == NULL){
        if(PciIo!=NULL){
            dev=(PCI_DEV_INFO*)PciIo;
            if(dev->Signature != AMI_PCI_SIG) return NULL;
        } else return NULL;
    } else dev=FindPciDeviceByHandle(PciDeviceHandle);
    
    return dev;
}


//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   PciExtIsPciExpresss()
//
// Description: Checks if PciDeviceHandle, or PciIO passed belongs to 
// PCI Express device.
// Input:
//  AMI_PCI_EXT_PROTOCOL*   This            Pointer to the PciBusExtended protocol.
//  EFI_HANDLE              PciDeviceHandle Handle of the PCI Device to check.
//  EFI_PCI_IO_PROTOCOL*    PciIo 		    Pointer to the instance of PCI IO Protocol (OPTIONAL)
//  PCIE_DATA**             PciExpData      Double Pointer to the PCIE_DATA Structure (OPTIONAL)
//  
// Output:	EFI_STATUS
//  EFI_SUCCESS             When everything is going on fine!
//  EFI_NOT_FOUND           If Device is not PCI Express device.
//  EFI_INVALID_PARAMETER   When Parameter passed is invalid.
//
// Note:
//  If PciDeviceHandle == NULL, PciIo must be valid.
//  If *PciIo == NULL PciDeviceHandle must be valid.
//  **PciExpData if not needed must be NULL;
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS PciExtIsPciExpresss(
	IN  AMI_PCI_EXT_PROTOCOL	              			*This,
	IN  EFI_HANDLE                               		PciDeviceHandle,
	IN  EFI_PCI_IO_PROTOCOL								*PciIo 		    OPTIONAL,
    OUT PCIE_DATA                                       **PciExpData    OPTIONAL
)
{
	PCI_DEV_INFO		*dev=NULL;
//------------------------------------        
    dev=PciExtGetDevice(PciDeviceHandle, PciIo);

	if(dev)	{
        if(dev->PciExpress != NULL){
            //if we have to update pointer
            if(PciExpData != NULL){
                *PciExpData = dev->PciExpress;
            } 
            return EFI_SUCCESS;
        } else return EFI_NOT_FOUND; 
    } else return EFI_INVALID_PARAMETER;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   PciExtIsPciX()
//
// Description: Checks if PciDeviceHandle, or PciIO passed belongs to 
// PCI Express device.
// Input:
//  AMI_PCI_EXT_PROTOCOL*   This            Pointer to the PciBusExtended protocol.
//  EFI_HANDLE              PciDeviceHandle Handle of the PCI Device to check.
//  EFI_PCI_IO_PROTOCOL*    PciIo 		    Pointer to the instance of PCI IO Protocol (OPTIONAL)
//  PCIX_DATA**             PciXData      Double Pointer to the PCIX_DATA Structure (OPTIONAL)
//  
// Output:	EFI_STATUS
//  EFI_SUCCESS             When everything is going on fine!
//  EFI_NOT_FOUND           If Device is not PCI X device.
//  EFI_INVALID_PARAMETER   When Parameter passed is invalid.
//
// Note:
//  If PciDeviceHandle == NULL, PciIo must be valid.
//  If *PciIo == NULL PciDeviceHandle must be valid.
//  **PciXData if not needed must be NULL;
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS PciExtIsPciX(
	IN  AMI_PCI_EXT_PROTOCOL	              			*This,
	IN  EFI_HANDLE                               		PciDeviceHandle,
	IN  EFI_PCI_IO_PROTOCOL								*PciIo 		    OPTIONAL,
    OUT PCIX_DATA                                       **PciXData      OPTIONAL
)
{
	PCI_DEV_INFO		*dev=NULL;
//------------------------------------        
    dev=PciExtGetDevice(PciDeviceHandle, PciIo);

	if(dev)	{
        if(dev->PciX != NULL){
            //if we have to update pointer
            if(PciXData != NULL){
                *PciXData = dev->PciX;
            } 
            return EFI_SUCCESS;
        } else return EFI_NOT_FOUND; 
    } else return EFI_INVALID_PARAMETER;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   PciExtIsPciBrg()
//
// Description: Checks if PciDeviceHandle, or PciIO passed belongs to 
// PCI 2 PCI Bridge device.
// Input:
//  AMI_PCI_EXT_PROTOCOL*   This            Pointer to the PciBusExtended protocol.
//  EFI_HANDLE              PciDeviceHandle Handle of the PCI Device to check.
//  EFI_PCI_IO_PROTOCOL*    PciIo 		    Pointer to the instance of PCI IO Protocol (OPTIONAL)
//  PCI_BRG_EXT**           PciBrgExt       Double Pointer to the PCI_BRG_EXT Structure (OPTIONAL)
//  
// Output:	EFI_STATUS
//  EFI_SUCCESS             When everything is going on fine!
//  EFI_NOT_FOUND           If Device is not PCI 2 PCI Bridge device.
//  EFI_INVALID_PARAMETER   When Parameter passed is invalid.
//
// Note:
//  If PciDeviceHandle == NULL, PciIo must be valid.
//  If *PciIo == NULL PciDeviceHandle must be valid.
//  **PciBrgExt if not needed must be NULL;
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS PciExtIsPciBrg(
	IN  AMI_PCI_EXT_PROTOCOL	              			*This,
	IN  EFI_HANDLE                               		PciDeviceHandle,
	IN  EFI_PCI_IO_PROTOCOL								*PciIo 		    OPTIONAL,
    OUT PCI_BRG_EXT                                     **BrgData       OPTIONAL
)
{
	PCI_DEV_INFO		*dev=NULL;
//------------------------------------        
    dev=PciExtGetDevice(PciDeviceHandle, PciIo);

	if(dev)	{
        if(dev->Type == tPci2PciBrg){
            //if we have to update pointer
            if(BrgData != NULL){
                *BrgData = (PCI_BRG_EXT*)(dev+1);
            } 
            return EFI_SUCCESS;
        } else return EFI_NOT_FOUND; 
    } else return EFI_INVALID_PARAMETER;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   PciExtIsCrdBrg()
//
// Description: Checks if PciDeviceHandle, or PciIO passed belongs to 
// PCI 2 Card Bridge device.
// Input:
//  AMI_PCI_EXT_PROTOCOL*   This            Pointer to the PciBusExtended protocol.
//  EFI_HANDLE              PciDeviceHandle Handle of the PCI Device to check.
//  EFI_PCI_IO_PROTOCOL*    PciIo 		    Pointer to the instance of PCI IO Protocol (OPTIONAL)
//  PCI_BRG_EXT**           PciBrgExt       Double Pointer to the PCI_BRG_EXT Structure (OPTIONAL)
//  
// Output:	EFI_STATUS
//  EFI_SUCCESS             When everything is going on fine!
//  EFI_NOT_FOUND           If Device is not PCI 2 Card Bridge device.
//  EFI_INVALID_PARAMETER   When Parameter passed is invalid.
//
// Note:
//  If PciDeviceHandle == NULL, PciIo must be valid.
//  If *PciIo == NULL PciDeviceHandle must be valid.
//  **PciBrgExt if not needed must be NULL;
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS PciExtIsCrdBrg(
	IN  AMI_PCI_EXT_PROTOCOL	              			*This,
	IN  EFI_HANDLE                               		PciDeviceHandle,
	IN  EFI_PCI_IO_PROTOCOL								*PciIo 		    OPTIONAL,
    OUT PCI_BRG_EXT                                     **BrgData       OPTIONAL
)
{
	PCI_DEV_INFO		*dev=NULL;
//------------------------------------        
    dev=PciExtGetDevice(PciDeviceHandle, PciIo);

	if(dev)	{
        if(dev->Type == tPci2CrdBrg){
            //if we have to update pointer
            if(BrgData != NULL){
                *BrgData = (PCI_BRG_EXT*)(dev+1);
            } 
            return EFI_SUCCESS;
        } else return EFI_NOT_FOUND; 
    } else return EFI_INVALID_PARAMETER;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   PciExtIsDevice()
//
// Description: Checks if PciDeviceHandle, or PciIO passed belongs to 
// Regular PCI device.
// Input:
//  AMI_PCI_EXT_PROTOCOL*   This            Pointer to the PciBusExtended protocol.
//  EFI_HANDLE              PciDeviceHandle Handle of the PCI Device to check.
//  EFI_PCI_IO_PROTOCOL*    PciIo 		    Pointer to the instance of PCI IO Protocol (OPTIONAL)
//  
// Output:	EFI_STATUS
//  EFI_SUCCESS             When everything is going on fine!
//  EFI_NOT_FOUND           If Device is not Regular PCI device.
//  EFI_INVALID_PARAMETER   When Parameter passed is invalid.
//
// Note:
//  If PciDeviceHandle == NULL, PciIo must be valid.
//  If *PciIo == NULL PciDeviceHandle must be valid.
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS PciExtIsDevice(
	IN  AMI_PCI_EXT_PROTOCOL	              			*This,
	IN  EFI_HANDLE                               		PciDeviceHandle,
	IN  EFI_PCI_IO_PROTOCOL								*PciIo          OPTIONAL
)
{
	PCI_DEV_INFO		*dev=NULL;
//------------------------------------        
    dev=PciExtGetDevice(PciDeviceHandle, PciIo);

	if(dev){
        if(dev->Type == tPciDevice) return EFI_SUCCESS;
        else return EFI_NOT_FOUND; 
    } else return EFI_INVALID_PARAMETER;
}


//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   PciExtClassCodes()
//
// Description: Returns device's Class code; Sub Class code; Programing Interface
// and Revision Id information.
//
// Input:
//  AMI_PCI_EXT_PROTOCOL*   This            Pointer to the PciBusExtended protocol.
//  EFI_HANDLE              PciDeviceHandle Handle of the PCI Device to check.
//  EFI_PCI_IO_PROTOCOL*    PciIo 		    Pointer to the instance of PCI IO Protocol (OPTIONAL)
//  PCI_DEV_CLASS*          CassCodes       Pointer to the PCI_DEV_CLASS to fill.
//  
// Output:	EFI_STATUS
//  EFI_SUCCESS             When everything is going on fine!
//  EFI_INVALID_PARAMETER   When Parameter passed is invalid.
//
// Note:
//  If PciDeviceHandle == NULL, PciIo must be valid.
//  If *PciIo == NULL PciDeviceHandle must be valid.
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS PciExtClassCodes(
	IN  AMI_PCI_EXT_PROTOCOL	              			*This,
	IN  EFI_HANDLE                               		PciDeviceHandle,
	IN  EFI_PCI_IO_PROTOCOL								*PciIo 		OPTIONAL,
	OUT PCI_DEV_CLASS									*CassCodes 
)
{
	PCI_DEV_INFO		*dev=NULL;
//------------------------------------        
    dev=PciExtGetDevice(PciDeviceHandle, PciIo);

	if(dev){
        *CassCodes=dev->Class;
        return EFI_SUCCESS;
    } else return EFI_INVALID_PARAMETER;
}


//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   PciExtPicIrqRout()
//
// Description: Returns device's corresponded PIC IRQ routing entry from OEMPIR.INC
// table created by the BUILD process.
// If function returns EFI_SUCCESS the "PicIrqTblEntry" updated with corresponded PIC 
// IRQ Table entry pointer. "ParentDevices" == NULL and "EntryCount"==0
// Function will return EFI_NOT_FOUND if there a no entry for the Device HANDLE passed.
// 
// But it will return update the array of EFI_PCI_CONFIGURATION_ADDRESS structures with
// PCI Addresses of parenti 
//
// Input:
//  AMI_PCI_EXT_PROTOCOL*   This            Pointer to the PciBusExtended protocol.
//  EFI_HANDLE              PciDeviceHandle Handle of the PCI Device to check.
//  EFI_PCI_IO_PROTOCOL*    PciIo 		    Pointer to the instance of PCI IO Protocol (OPTIONAL)
//  PCI_IRQ_PIC_ROUTE**     PicIrqTblEntry  Double pointer to the corresponded PCI_IRQ_PIC_ROUTE entry
//  EFI_PCI_CONFIGURATION_ADDRESS** ParentDevices Pointer to an array of parent Devices 
//                                          for which was not found a valid PCI_IRQ_PIC_ROUTE entry.
//  UINTN*                  EntryCount      Number of elements in an array above.
//  
// Output:	EFI_STATUS
//  EFI_SUCCESS             When everything is going on fine!
//  EFI_NOT_FOUND           If no PIRQ entry was found for this device.
//  EFI_INVALID_PARAMETER   When Parameter passed is invalid.
//
// Note:
//  If PciDeviceHandle == NULL, PciIo must be valid.
//  If *PciIo == NULL PciDeviceHandle must be valid.
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS PciExtPicIrqRout (
	IN  AMI_PCI_EXT_PROTOCOL	              			*This,
	IN  EFI_HANDLE                               		PciDeviceHandle,
	IN  EFI_PCI_IO_PROTOCOL						 		*PciIo 		OPTIONAL,
    OUT PCI_IRQ_PIC_ROUTE                               **PicIrqTblEntry,
    OUT EFI_PCI_CONFIGURATION_ADDRESS                   **ParentDevices,
    OUT UINTN                                           *EntryCount )
{
    EFI_STATUS          Status;
	PCI_DEV_INFO		*dev=NULL;
    PCI_DEV_INFO        *parent;
    T_ITEM_LIST         ParentLst={0,0,NULL};
    INTN                i,j;
    EFI_PCI_CONFIGURATION_ADDRESS   *pa=NULL;
//------------------------------------        
    dev=PciExtGetDevice(PciDeviceHandle, PciIo);

	if(dev != NULL ){
        if( dev->PicIrqEntry != NULL ){
            *PicIrqTblEntry = dev->PicIrqEntry;
            ParentDevices = NULL;
            EntryCount = 0;
            return EFI_SUCCESS;
        } else {
            parent=dev;
            do{
                parent=parent->ParentBrg; 
                Status=AppendItemLst(&ParentLst, parent);
            }while( (parent->PicIrqEntry == NULL) || (parent->Type != tPciRootBrg));
            
            if( parent->PicIrqEntry != NULL ){
                *PicIrqTblEntry=parent->PicIrqEntry;
                //Create the array of addresses in order from Device which has IRQ endtry down to this Device parent
                if(ParentLst.ItemCount){    
                    pa=Malloc(sizeof(EFI_PCI_CONFIGURATION_ADDRESS)*(ParentLst.ItemCount));
                    for(i=(INTN)ParentLst.ItemCount-1, j=0; i<=0; i--,j++){
                        parent = (PCI_DEV_INFO*)ParentLst.Items[i];
                        pa[j] = parent->Address.Addr;
                    }
                } 
                *ParentDevices=pa;
                *EntryCount=ParentLst.ItemCount;
            } else {
                *PicIrqTblEntry=NULL;
                ParentDevices=NULL;
                EntryCount=0;
            }
            return EFI_NOT_FOUND;
        }
    } 
    else return EFI_INVALID_PARAMETER;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   PciExtApicIrqRout()
//
// Description: Returns device's corresponded APIC IRQ routing entry from MPPCIIRQ.INC
// table created by the BUILD process.
// If function returns EFI_SUCCESS the "ApicIrqTblEntry" updated with corresponded PIC 
// IRQ Table entry pointer. "ParentDevices" == NULL and "EntryCount"==0
// Function will return EFI_NOT_FOUND if there a no entry for the Device HANDLE passed.
// 
// But it will return update the array of EFI_PCI_CONFIGURATION_ADDRESS structures with
// PCI Addresses of parenti 
//
// Input:
//  AMI_PCI_EXT_PROTOCOL*   This            Pointer to the PciBusExtended protocol.
//  EFI_HANDLE              PciDeviceHandle Handle of the PCI Device to check.
//  EFI_PCI_IO_PROTOCOL*    PciIo 		    Pointer to the instance of PCI IO Protocol (OPTIONAL)
//  PCI_IRQ_PIC_ROUTE**     ApicIrqTblEntry Double pointer to the corresponded PCI_IRQ_PIC_ROUTE entry
//  EFI_PCI_CONFIGURATION_ADDRESS** ParentDevices Pointer to an array of parent Devices 
//                                          for which was not found a valid PCI_IRQ_PIC_ROUTE entry.
//  UINTN*                  EntryCount      Number of elements in an array above.
//  
// Output:	EFI_STATUS
//  EFI_SUCCESS             When everything is going on fine!
//  EFI_NOT_FOUND           If no PIRQ entry was found for this device.
//  EFI_INVALID_PARAMETER   When Parameter passed is invalid.
//
// Note:
//  If PciDeviceHandle == NULL, PciIo must be valid.
//  If *PciIo == NULL PciDeviceHandle must be valid.
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS PciExtApicIrqRout (
	IN  AMI_PCI_EXT_PROTOCOL	              			*This,
	IN  EFI_HANDLE                               		PciDeviceHandle,
	IN  EFI_PCI_IO_PROTOCOL						 		*PciIo 		OPTIONAL,
    OUT PCI_IRQ_APIC_ROUTE                              **ApicIrqTblEntry,
    OUT EFI_PCI_CONFIGURATION_ADDRESS                   **ParentDevices,
    OUT UINTN                                           *EntryCount )
{
    EFI_STATUS          Status;
	PCI_DEV_INFO		*dev=NULL;
    PCI_DEV_INFO        *parent;
    T_ITEM_LIST         ParentLst={0,0,NULL};
    INTN                i,j;
    EFI_PCI_CONFIGURATION_ADDRESS   *pa=NULL;
//------------------------------------        
    dev=PciExtGetDevice(PciDeviceHandle, PciIo);

	if(dev != NULL ){
        if( dev->ApicIrqEntry != NULL ){
            *ApicIrqTblEntry = dev->ApicIrqEntry;
            ParentDevices = NULL;
            EntryCount = 0;
            return EFI_SUCCESS;
        } else {
            parent=dev;
            do{
                parent=parent->ParentBrg; 
                Status=AppendItemLst(&ParentLst, parent);
            }while( (parent->ApicIrqEntry == NULL) || (parent->Type != tPciRootBrg));
            
            if( parent->ApicIrqEntry != NULL ){
                *ApicIrqTblEntry=parent->ApicIrqEntry;
                //Create the array of addresses in order from Device which has IRQ endtry down to this Device parent
                if(ParentLst.ItemCount){    
                    pa=Malloc(sizeof(EFI_PCI_CONFIGURATION_ADDRESS)*(ParentLst.ItemCount));
                    for(i=(INTN)ParentLst.ItemCount-1, j=0; i<=0; i--,j++){
                        parent = (PCI_DEV_INFO*)ParentLst.Items[i];
                        pa[j] = parent->Address.Addr;
                    }
                } 
                *ParentDevices=pa;
                *EntryCount=ParentLst.ItemCount;
            } else {
                *ApicIrqTblEntry=NULL;
                ParentDevices=NULL;
                EntryCount=0;
            }
            return EFI_NOT_FOUND;
        }
    } 
    else return EFI_INVALID_PARAMETER;
}

//**********************************************************************
//**********************************************************************
//**                                                                  **
//**        (C)Copyright 1985-2010, American Megatrends, Inc.         **
//**                                                                  **
//**                       All Rights Reserved.                       **
//**                                                                  **
//**      5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093        **
//**                                                                  **
//**                       Phone: (770)-246-8600                      **
//**                                                                  **
//**********************************************************************
//**********************************************************************
