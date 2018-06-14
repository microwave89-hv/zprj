//**********************************************************************
//**********************************************************************
//**                                                                  **
//**        (C)Copyright 1985-2013, American Megatrends, Inc.         **
//**                                                                  **
//**                       All Rights Reserved.                       **
//**                                                                  **
//**           5555 Oakbrook Pkwy, Suite 200, Norcross, GA 30093      **
//**                                                                  **
//**                       Phone: (770)-246-8600                      **
//**                                                                  **
//**********************************************************************
//**********************************************************************

//****************************************************************************
// $Header: /Alaska/SOURCE/Modules/CSM/Generic/Core/csm.c 198   8/06/14 12:57p Fasihm $
//
// $Revision: 198 $
//
// $Date: 8/06/14 12:57p $
//
//****************************************************************************
// Revision History
// ----------------
// $Log: /Alaska/SOURCE/Modules/CSM/Generic/Core/csm.c $
// 
// 198   8/06/14 12:57p Fasihm
// [TAG]           EIP180667
// [Category]      Bug Fix
// [Severity]      Normal
// [Symptom]       Aptio 4 CSM: CPU cache attributes need adjustment.
// [Solution]      Changed the cache attributes to WriteProtect for all 4
// regions.
// [Files]
//         Core/EM/CSM/CSM.c
// 
// 197   1/10/14 12:21p Olegi
// EIP149769: LegacyToEfi boot management
// Changed default setting, added new token to extend the functionality
// 
// 196   10/18/13 12:36p Olegi
// EIP139866
// Create interface to manage LegacyToEfi CSM feature
// 
// 195   10/07/13 10:21a Olegi
// [TAG]  		EIP138427
// [Category]  	New Feature
// [Description]  	Create interface to let OEM customers change CSM16
// variables
// [Files] csm.c, csm.h, csmlib.c, legacybiosext.h
// 
// 194   10/07/13 8:57a Olegi
// EIP135289
// Legacy2Efi update
// 
// 193   8/14/13 8:38a Olegi
// EIP132753: Legacy2Efi module support
// 
// 192   7/24/13 11:46a Olegi
// [TAG]  		EIP121303
// [Category]  	Improvement
// [Description]  	UEFI Win7 hibernation wake up may fail
// [Files]  		csm.c
// 
// 191   5/03/13 2:38a Rameshr
// [TAG]  		EIP117874
// [Category]  	Improvement
// [Description]  	Modified AllConnectedCallback function event is based
// on TPL_NOTIFY
// [Files]  		csm.c
// 
// 190   4/29/13 12:31p Olegi
// [TAG]  		EIP120105
// [Category]  	Improvement
// [Description]  	Incorrect 'CSM16LocationAttribute' passed to
// CopyLegacyTable(), in CSM.c
// 
// 189   4/09/13 9:25a Olegi
// [TAG]  		EIP118727
// [Category]  	New Feature
// [Description]  	Onboard PCI Option ROM loading is moved outside CSM
// [Files]  		CSM.mak
// CSM.dxs
// CSM.c
// PciInterrupts.c
// CsmBsp.c
// CsmLib.c
// 
// 188   12/24/12 12:06p Olegi
// [TAG]  		EIP89376
// [Category]  	Improvement
// [Description]  	[CSM] Support to return EFI_SECURITY_VIOLATION from
// EFI_Legacy_BIOS_Protocol.LegacyBoot when secure boot is on
// 
// 187   12/18/12 1:44p Olegi
// [TAG]  		EIP108682
// [Category]  	Bug Fix
// [Severity]  	Normal
// [Symptom]  	Invalid Error Code from CSM Functions
// [RootCause]  	BIT31 is used as error indication
// [Solution]  	use EFI_ERROR_BIT macro instead of BIT31
// [Files]  		CSM.c
// CsmHwInfo.c
// 
// 186   12/14/12 3:04p Olegi
// [TAG]  		EIP105734
// [Category]  	Bug Fix
// [Symptom]  	PCI Resource Issue with PLX Bridges
// [RootCause]  	Bridge stays disabled on LegacyBoot
// [Solution]  	Enable the bridges on legacy boot along with the other PCI
// devices.
// 
// 185   7/23/12 4:46p Olegi
// [TAG]        EIP93685
// [Category]   Improvement
// [Description]    Clear CSM used resources when it is disabled
// 
// 184   7/23/12 12:10p Olegi
// [TAG]        EIP92416
// [Description]    Testing request for Smbios (INT)a_4.6.5.1_SMBIOS_32
// label
// LegacyBiosExt protocol is rearranged to match the one used by the
// SMBIOS.
// 
// 183   6/25/12 3:59p Olegi
// [TAG]        EIP90257
// [Category]   Improvement
// [Description]    In CSM, don't clear allocated memory below 640K - added
// ClearFreeMemory function
// [Files]          CsmOpROM.c
// CSM.c
// CsmHwInfo.c
// 
// 182   6/13/12 9:12a Olegi
// [TAG]        EIP90257
// [Category]   Improvement
// [Description]    In CSM, don't clear allocated memory below 640K.
// 
// 181   12/23/11 3:09p Olegi
// [TAG]        EIP78921
// [Category]   Improvement
// [Description]    CsmBlockIo should create device handle in BBS table
// [Files]          CSM.h
// CSM.c
// CsmLib.c
// 
// 180   12/23/11 2:47p Olegi
// [TAG]        EIP79228
// [Category]   Improvement
// [Description]    Implement CSM_INT19_TRAP_IMMEDIATE_ACTION functionality
// [Files]          CsmOpROM.c
// CSM.c
// 
// 179   11/14/11 11:59a Olegi
// 
// 176   11/10/11 7:28p Olegi
// CSM_OPTOUT_SUPPORT is replaced with CsmOptOut_SUPPORT master token.
// 
// 175   10/31/11 11:55a Olegi
// Installation of AMISCMStartedProtocolGuid is moved our of
// CSM_OPTOUT_IMPLEMENTED scope.
// 
// 174   10/12/11 10:06p Olegi
// [TAG]        EIP72331
// [Category]   Improvement
// [Description]    Added CSM_INIT_LEGACY_MEMORY_FUNCTIONS eLink for custom
// memory initialization.
// [Files]          CSM.mak
// CSM.c
// CsmBsp.c
// 
// 173   10/12/11 2:56p Olegi
// [TAG]        EIP72177
// [Category]   Improvement
// [Description]    CheckPmmTable function suppressed.
// [Files]          CsmOpROM.c
// CSM.c
// CsmBsp.c
// CSM.SDL
// 
// 172   10/03/11 5:05p Olegi
// 
// 171   10/03/11 3:22p Olegi
// [TAG]        EIP71591
// [Category]   Improvement
// [Description]    CSM opt-out changes
// 
// 170   10/03/11 1:44p Olegi
// Modifications in HaltApsBeforeBoot function related to PI1.1
// 
// 169   8/29/11 2:23p Olegi
// [TAG]        EIP56792
// [Category]   Improvement
// [Description]    Original fix for this EIP checked in earlier does not
// work for the newer Core versions. FLEXBOOT has been depreciated for
// newer Cores, and it must be enabled for proper operation.
// [Files]          csm.c
// 
// 168   6/10/11 5:37p Olegi
// [TAG]        EIP59263
// [Category]   New Feature
// [Description]    High memory PMM area made dynamic.
// [Files]          CSM.h
// CsmOpROM.c
// CSM.c
// CsmBsp.c
// csm.sdl
// 
// 167   6/10/11 5:07p Olegi
// Undone check-ins #165 and #166 as EIP59263 is resolved differently.
// 
// 164   3/24/11 9:39a Olegi
// [TAG]        EIP56792
// [Category]   Improvement
// [Description]    The value of FLEX_BOOT is depreciated for the newer
// Core.
// [Files]          csm.c
// 
// 163   3/15/11 3:50p Olegi
// [TAG]        EIP55913
// [Category]   Improvement
// [Description]    Remove LastOpromAddress from EFI_COMPATIBILITY16_TABLE
// structure
// [Files]          Csm.c LegacyBios.h LegacyBiosExt.h
// 
// 162   3/10/11 3:04a Rameshr
// [TAG]- EIP 54231
// [Category]-IMPROVEMENT
// [Description]- Display the virus warning message when writting into MBR
// of HDD. This support added for IDE, AHCI and USB HD devices.
// [Files]- Csm.c, CsmOem.cif, Csm.uni, Csm.sdl, Csm.sd, Amilegacy16.bin,
// AI13.Bin, Ui13.bin, VirusProtect module
// 
// 161   3/08/11 12:44p Olegi
// [TAG]        EIP55496
// [Category]   Improvement
// [Description]    Added ebdaOffset field to SAVED_PCI_ROM structure to
// ensure the correct EBDA saving/restoration.
// [Files]          CSM.h
// CsmOpROM.c
// CSM.c
// 
// 160   12/13/10 5:29p Olegi
// [TAG]        EIP50206
// [Category]   Bug Fix
// [Severity]   Important
// [Symptom]    Calls to Get16BitFuncAddress() can hang the system when
// CSM_OEM_SUPPORT is disabled
// [RootCause]      Disabling CSM_OEM_SUPPORT and calling
// Get16BitFuncAddress() will hang the system because gCsm16FuncAddress is
// NULL (uninitialized) and gCsm16FuncAddress is dereferenced.
// [Solution]   Added validation of gCsm16FuncAddress variable in
// Get16BitFuncAddress function.
// [Files]          CSM.C
// 
// 159   11/15/10 12:04p Olegi
// [TAG]        EIP47997
// [Category]   Improvement
// [Description]    Project tag updated in F000:F4F0
// [Files]          CSM.C
// 
// 158   10/13/10 12:43p Olegi
// Undoing the previous change related to InitCsmSimpleIn as it is not
// generic change.
// 
// 157   10/12/10 5:43p Olegi
// Function call InitCsmSimpleIn made conditional; in the older BDS this
// call causes problem. EIP43050
// 
// 156   9/15/10 5:21p Olegi
// Added reverse thunk stack allocation.
// 
// 155   7/16/10 12:47p Olegi
// 
// 154   7/16/10 12:31p Olegi
// - EIP39395: Update CSM16 header checksum after LastPciBus field of it
// has been changed.
// - EIP39768: Modifications in the video mode switching policy
// - Isolated all AMI CSM16 specific programming into a separate function
// so that it can be skipped in case of non-AMI CSM16.
// 
// 153   7/09/10 9:18a Olegi
// Changed the sequence of HaltApsBeforeBoot and SignalAmiLegacyBootEvent
// execution. EIP39089.
// 
// 152   7/08/10 11:31a Olegi
// Added SignalAmiLegacyBootEvent call. EIP39089
// 
// 151   5/27/10 4:59p Olegi
// Modified UpdatePciLastBus function, made it a callback notification on
// PciIo, not on RootBridgeIo. EIP#39123.
// 
// 150   5/14/10 4:16p Olegi
// 
// 149   5/10/10 2:24p Olegi
// Update BIOS date/time/rev in CSM16 area. EIP#34791
// 
// 148   4/28/10 11:53a Olegi
// 
// 147   3/26/10 9:36a Olegi
// Dynamic CSM16 location calculation. EIP36484
// 
// 146   3/02/10 5:13p Olegi
// Making use of AmiExtPciBusProtocol when PCI Bus driver version is 240
// or newer.
// 
// 145   2/19/10 3:13p Olegi
// 
// 144   2/19/10 1:24p Olegi
// Changed the resolution of EIP34733 (>10s delay during boot). Root cause
// of the problem is one of the LEGACY_BOOT callback notification
// functions (BootNotify function in CpuDxe.c) is initializing IDT with
// the "iret", at the same time interrupts kept enabled. This is not
// suitable for the HW interrupt (IRQ1 from timer) - at least EOI must be
// sent to PIC before executing "iret". This was causing a timeout while
// reading the HDD in the PrepareToBoot function. The current solution is
// to mask timer interrupt after all callback notifications are complete. 
// 
// 143   2/17/10 1:50p Olegi
// Undo the final resolution for EIP32001: UpdatePciLastBus can not be
// called from AllConnectedCallback as the last PCI bus # may be needed
// earlier than that (Option ROMs). EIP35258.
// 
// 142   2/05/10 7:14p Olegi
// 
// 141   2/01/10 1:56p Olegi
// EIP33173: During LegacyBoot set video mode 3 only if it is not set
// already.
// 
// 140   1/26/10 12:38p Olegi
// EIP32001: functionality of UpdatePciLastBus function is moved to
// AllConnectedCallback.
// 
// 139   1/12/10 11:46a Olegi
// Copyright message updated.
// 
// 138   12/28/09 8:48a Olegi
// RemoveDecodingForShadow call moved to LEGACYREGION.Lock
// 
// 137   12/28/09 8:25a Olegi
// WinCE loader support. EIP#30803
// 
// 136   12/02/09 10:00a Olegi
// EIP#23106: added NMI information related call.
// 
// 135   12/01/09 11:40a Olegi
// Changed the order of UpdateCmos-->EnableDisableNmi functions because
// UpdateCmos will unconditionally enable NMIs.
// 
// 134   11/17/09 12:06p Olegi
// Changed the order of PrepareToBoot execution. It is moved after
// singaling LegacyBoot event. The reason is PrepareToBoot finalizes E820
// table and LegacyBoot event callbacks may allocate some memory that must
// be reflected in E820 map. Example - S3 resume script memory. EIP#29087.
// 
// 133   11/10/09 8:24a Olegi
// Added CSM SimpleTextIn support. EIP#27843
// 
// 132   10/27/09 8:08a Olegi
// EIP#29883: Bugfix in InitCompatibility16 function.
// 
// 131   6/16/09 4:11p Olegi
// Generic modifications to update LastPciBus field in
// EFI_COMPATIBILITY16_TABLE.
// 
// 130   4/02/09 2:14p Olegi
// Modification in EnablePciDevices: the counter of PCI devices was
// declared as UINT8 - some configurations have more than 256 devices.
// Changed to UINTN.
// 
// 129   3/30/09 5:05p Olegi
// Change in OEM16 routines: fixups are done so that every routine is
// entered at a correct offset; no fixup is needed to access the local
// variables. EIP#16383.
// 
// 128   12/16/08 10:47a Olegi
// Correction in the return value: 0 changed to NULL. EIP#17767
// 
// 126   12/11/08 3:00p Olegi
// Added shadow regions initialization. EIP#17763
// 
// 125   12/09/08 3:31p Olegi
// Added EfiGetPlatformGateA20Information function.
// 
// 124   11/13/08 1:01p Olegi
// 
// 123   11/12/08 4:59p Olegi
// Added board specific hooks.
// 
// 122   10/10/08 3:35p Olegi
// 
// 121   9/23/08 2:18p Olegi
// 
// 120   9/02/08 10:54a Olegi
// Modification in EnablePciDevice function that will keep "unused" PCI
// bridges disabled after legacy boot.
// 
// 119   7/23/08 9:57a Fasihm
// Fix EIP#: 14947:  Added fix for CPU MTRR registers being inconsistent
// between cores. Moved the RemoveDecodingForShadow call from after to
// before the Signal_Legacy_Boot event.
// 
// 118   6/30/08 3:50p Olegi
// 
// 117   6/09/08 2:07p Olegi
// Added HaltApsBeforeBoot routine that halts the APs before legacy boot.
// 
// 116   5/19/08 12:37p Olegi
// Removed EBDA size limitation.
// 
// 115   4/14/08 2:45p Rameshraju
// Removed the decoding for the remaining Shadow region
// 
// 114   3/20/08 4:44p Olegi
// FLEXBOOT initialization added.
// 
// 113   3/12/08 11:59a Olegi
// Added progress status codes.
// 
// 112   1/31/08 11:53a Olegi
// AllocateEbda call definition changed.
// 
// 111   1/16/08 2:17p Olegi
// Modified AllocateEbda function.
// 
// 110   12/17/07 4:22p Olegi
// KBC_SUPPORT dependency removed.
// 
// 109   12/04/07 11:07a Olegi
// 
// 108   10/24/07 12:27p Olegi
// Function AllocateEbda added to LegacyBiosExt protocol.
// 
// 107   10/17/07 3:23p Olegi
// - modified PrepareToBoot to properly Unlock/Lock shadow regions. The
// problem was with the ROMs that are not in the SavedRom list (service
// ROMs or non-BBS compliant ROMs). After the final locking these ROMs
// areas were not decoded
// - modified GetBbsInfo to treat floppy with NO_FLOPPY_DISK and
// FLOPPY_INSERTED the same way
// 
// 106   8/23/07 9:14a Olegi
// Reverted #105, it causes problems on MCP55 AMD projects. Instead,
// UninstallMemoryManagerEF call is removed from CSM16 PrepareToBoot.
// 
// 105   8/21/07 11:07a Olegi
// CreateLegacyBootEvent moved before PrepareToBoot call so that legacy
// boot event callbacks have a chance to allocate E/F memory
// 
// 104   8/10/07 11:05a Olegi
// 
// 103   7/23/07 12:41p Olegi
// Change the order of PrepareToBoot and BspPrepareToBoot execution.
// 
// 102   7/10/07 12:42p Olegi
// Added the initialization of kbd head and tail in PrepareToBoot
// function.
// 
// 101   6/27/07 3:52p Olegi
// Workaround for OpROMs that use 40:13 to allocate memory, not EBDA.
// 
// 100   6/21/07 10:32a Olegi
// 
// 99    6/18/07 5:46p Olegi
// Added two new protocol functions GetEmbeddedRom and AddBbsEntry.
// 
// 98    6/12/07 5:47p Olegi
// Removed the loop that initializes the priorities for the existing BBS
// devices.
// 
// 97    6/12/07 2:59p Olegi
// 
// 96    6/04/07 12:34p Olegi
// 
// 95    6/04/07 10:45a Olegi
// 
// 94    6/02/07 10:46a Olegi
// 
// 93    6/02/07 10:25a Olegi
// Shadow size correction.
// 
// 92    6/01/07 12:29p Olegi
// Fixed the return values while exiting the entry point.
// 
// 91    5/29/07 12:21p Olegi
// The code to disable Shadow W/R for the unused shadow regions is moved
// to CsmOpROM.c
// 
// 90    5/24/07 4:05p Olegi
// Added two setup questions - NumLock state at boot and OpROM display
// mode.
// 
// 89    5/03/07 1:23p Olegi
// PCIE_BASE_ADDRESS token is changed to PCIEX_BASE_ADDRESS
// 
// 88    4/27/07 5:28p Olegi
// PCIEX_BASE_ADDRESS is used instead of PCIE_BASE_ADDRESS. It is
// currently defined in NB.SDL
// 
// 87    4/27/07 5:13p Olegi
// CSM.CHM file preparation.
//
// 86    4/20/07 11:31a Olegi
// Bugfix in OEM interrupts and OEM 16-bit function initialization.
//
// 85    4/19/07 10:21a Olegi
// Updated InitializeOem16 function.
//
// 84    4/12/07 1:28p Olegi
// 
// 83    4/10/07 5:18p Olegi
// LastOpromAddress is passed from CSM32 to CSM16.
// 
// 82    3/01/07 9:12a Olegi
//
// 81    12/13/06 4:12p Olegi
//
// 80    12/12/06 5:30p Olegi
// BBS table dump before PrepareToBoot.
//
// 79    10/13/06 12:30a Felixp
// UEFI2.0 compliance: use CreateLegacyBootEvent instead of
// CreateEvent(LEGACY_BOOT)
//
// 78    10/05/06 5:53p Olegi
// Added context to EFI_EVENT_SIGNAL_LEGACY_BOOT event.
//
// 77    9/22/06 6:13p Olegi
//
// 76    9/20/06 11:35a Felixp
// x64 warning fixed
//
// 75    8/24/06 6:49p Felixp
// x64 support (warnings/errors fixed)
//
// 74    8/16/06 2:38p Olegi
// Previous typecast changes undone.
//
// 72    8/11/06 4:44p Olegi
//
// 71    7/31/06 4:05p Olegi
//
// 70    7/28/06 4:43p Olegi
//
// 68    7/07/06 8:24a Olegi
// At entry point clear 0..640K, assuming no other driver allocated any
// memory within this range. This assumption implies the whole
// conventional memory directly and indirectly belongs to CSM.
//
// 67    7/05/06 3:42p Olegi
// LegacyBoot used to do INT10 first, then TxtOut->ClearScreen. This
// sequence needs to be reversed.
//
// 64    5/25/06 2:23p Olegi
//
// 63    5/16/06 1:57p Olegi
//
// 62    5/04/06 9:42a Olegi
// Removed the logic that fixes the location of PATA/SATA in BBS table.
//
// 61    4/24/06 9:27a Olegi
// Lock/UnLock shadow regions added before and after each CSM API call.
//
// 59    4/18/06 12:06p Olegi
//
// 58    4/18/06 10:38a Olegi
// SHADOWREGION_GRANULARITY token has been removed; shadow regions
// granularity is taken from Lock/Unlock routines.
//
// 57    4/17/06 4:27p Olegi
//
// 56    4/17/06 9:32a Olegi
//
// 55    3/31/06 4:44p Olegi
//
// 54    3/31/06 9:14a Olegi
//
// 53    3/30/06 1:20p Olegi
//
// 50    3/03/06 5:09p Olegi
// EFI System Table pointer is passed to CSM16.
//
// 49    3/01/06 3:10p Olegi
//
// 47    2/23/06 7:06p Olegi
// GetLegacyRegion and CopyLegacyRegion functions added.
//
// 46    12/16/05 2:59p Robert
// Clear the screen before PrepareToBoot function: some BCVs (Netcell PCI
// SATA RAID) attempt to output messages using INT10, this causes screen
// corruption.
//
// 45    12/14/05 4:16p Olegi
// NMI enable/disable changes.
//
// 44    12/12/05 12:13p Olegi
//
// 43    10/13/05 6:23p Olegi
// Interrupt save/restore correction.
//
// 42    10/11/05 2:57p Olegi
//
// 41    10/11/05 11:56a Olegi
//
// 40    10/10/05 7:27p Olegi
//
// 39    9/30/05 6:27p Olegi
// VC7.1 compatibility issues solved.
//
// 38    9/29/05 5:20p Olegi
// Clear TxtOut screens before booting.
//
// 37    9/28/05 8:29a Olegi
// Interrupt save/restore code is divided into SW and HW interrupts
// restoration.
//
// 36    9/21/05 3:55p Olegi
//
// 35    9/09/05 6:04p Olegi
//
// 34    9/09/05 11:22a Olegi
//
// 33    9/06/05 10:48a Olegi
//
// 32    9/02/05 2:57p Olegi
// Save/restore additional interrupts.
//
// 31    8/25/05 10:31a Olegi
// Previous change undone, issue with some VGA cards that hook int 6d
// (Matrox PCI) is solved different way: vector base for the master 8259
// is changed from 0x68 to 0x58.
//
// 29    8/02/05 11:28a Olegi
// GetBbsInfo: device priorities are initialized for all entries with
// priority different from BBS_IGNORE.
//
// 28    6/22/05 8:35a Olegi
//
// 27    6/21/05 12:12p Olegi
// LegacyBios and LegacyBiosPlatform are combined into one FFS.
//
// 26    4/29/05 8:42a Olegi
//
// 25    4/25/05 5:32p Olegi
//
// 24    4/22/05 2:11p Olegi
//
// 24    4/21/05 9:04a Olegi
// - moved INT 13 vector manipulation here from BiosBlkIo
// - added ShadowPciRoms and EnablePciDevices functions
// - modified the sequence of signaling the boot event and locking shadow
// in LegacyBoot function
//
// 23    4/19/05 11:16a Olegi
// Signal legacy boot event code moved after the shadow memory is locked.
//
// 22    4/19/05 11:12a Olegi
// ShadowAllLegacyOproms call added.
//
// 21    4/12/05 12:20p Olegi
//
// 20    3/10/05 4:45p Olegi
// Removed ASSERT after allocation of shadow memory since it might be
// allocated already.
//
// 19    3/04/05 1:53p Mandal
//
//**********************************************************************

//**********************************************************************
//<AMI_FHDR_START>
//
//  Name:           CSM.C
//  Description:    Compatibility Support Module entry point and interface functions.
//
//<AMI_FHDR_END>
//****************************************************************************

#include "token.h"
#include "csm.h"
#include <Protocol/cpu.h>
#include <Protocol/PciIo.h>
#include <AmiDxeLib.h>
#include "biosdata.h"
#include "pci.h"
#include "setup.h"
#include <Protocol/MPService.h>
#include <Protocol/PciRootBridgeIo.h>
#include <Protocol/Timer.h>
#include <Protocol/CsmPlatform.h>
#include "timestamp.h"
#include <ImageAuthentication.h>
#include <Protocol/AmiBoardInfo.h>

#include <AmiCspLib.h>
#ifndef DEFAULT_TICK_DURATION
#define DEFAULT_TICK_DURATION ((65535 * 838 + 50) / 100)
#endif
#define LTEB_GUID  \
    {0xC8BCA618, 0xBFC6, 0x46B7, 0x8D, 0x19, 0x83, 0x14, 0xE2, 0xE5, 0x6E, 0xC1}
EFI_GUID    gLTEBGuid = LTEB_GUID;

#define AMI_PCI_BUS_EXT_PROTOCOL_GUID \
{ 0xf42a009d, 0x977f, 0x4f08, 0x94, 0x40, 0xbc, 0xa5, 0xa3, 0xbe, 0xd9, 0xaf };

#define BDS_ALL_DRIVERS_CONNECTED_PROTOCOL_GUID \
    {0xdbc9fd21, 0xfad8, 0x45b0, 0x9e, 0x78, 0x27, 0x15, 0x88, 0x67, 0xcc, 0x93}

#define WINCE_GUID \
{ 0xC184562C,0x6864,0x40a3,{0xA0,0x81,0xC8,0xD3,0x5E,0x82,0xB9,0x20 }}

EFI_GUID  WinceGuid=WINCE_GUID;

EFI_GUID gEfiMpServicesProtocolGuid = EFI_MP_SERVICES_PROTOCOL_GUID;
EFI_GUID gBdsAllDriversConnectedProtocolGuid = BDS_ALL_DRIVERS_CONNECTED_PROTOCOL_GUID;

BIOS_INFO       *CoreBiosInfo = NULL;
SAVED_PCI_ROM   *gSavedOprom;
BOOLEAN         gServiceRomsExecuted = FALSE;

UINT8   *gNextRomAddress;       // PCI ROM address pointer, updated as ROMs are installed
UINTN   gMaxOpRomAddress;       // Highest available address for PCI ROM

EXECUTED_PCI_ROM    *gExecutedRomsPci;   // List of PciIo's with installed OpROMs
VOID    *mAllocatedOnceMemory = NULL;

BOOLEAN     gIsBootPrepared;
BOOLEAN     gIsBbsInitialized;
BOOLEAN     gIsMassStorageInstalled;

UINT32  HwIrqRedirSav[8];   // hw interrupts redirected vectors - IRQ0..IRQ7
UINT8   irq0;

#define MAX_NUM_IRQS_SAVERESTORE 16
IVT_SAVE_RESTORE gIrqSav[MAX_NUM_IRQS_SAVERESTORE];

//
// gSetTxtMode
// 0 - switching to text mode is needed (init value)
// 1 - switching is needed, restoration is not (set in ShadowOptionRoms)
// 2 - neither switching nor restoration is needed
//
UINT8  gSetTxtMode;

EFI_GUID    guidSetup = SETUP_GUID;
SETUP_DATA  gSetup;

OEMINT_FUNC *gCsm16IntStart = 0;
OEM16_FUNC  *gCsm16FuncAddress = 0;
UINTN       gCsm32DataAddress = 0;
VOID        *gProtocolNotifyRegistration;

extern EFI_HANDLE gVgaHandle;

AMI_BOARD_INFO_PROTOCOL *gAmiBoardInfo = NULL;

VOID        ConnectSerialIO();
VOID        DisconnectSerialIO();
VOID        DummyFunction(EFI_EVENT Event, VOID *Context);
EFI_TPL     gOldTplValue = NULL;
UINT16      gProtectedIrqMask = 0xffff;
BBS_TABLE   *gOriginalBbsTable = NULL;

VOID DumpBbsTable(UINT32);
#define BBS_LOWEST_ACTIVE_PRIORITY 0xfffb

/*---------------------------------------------------*/
/*---                                             ---*/
/*---    AMI CSM Extensions Protocol functions    ---*/
/*---                                             ---*/
/*---------------------------------------------------*/

EFI_LEGACY_BIOS_EXT_PROTOCOL gAmiCsmExtensionsProtocol = {
  GetEmbeddedRom,
  AddBbsEntry,
  InsertBbsEntryAt,
  RemoveBbsEntryAt,
  AllocateEbda,
  UnlockShadow,
  LockShadow,
  Get16BitFuncAddress,
  CopyLegacyTable,
  InstallIsaRom,
  GetShadowRamAddress,
  GetBbsTable,
  Csm16Configuration
};

//<AMI_PHDR_START>
//---------------------------------------------------------------------------
//
// Name:        GetEmbeddedRom
//
// Description:
//  This function calls FindEmbeddedRom to search for onboard Option ROM.
//
// Output:
//  EFI_SUCCESS or EFI_NOT_FOUND
//
// Referrals:
//  FindEmbeddedRom
//
//---------------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS
GetEmbeddedRom (
    IN UINT16 ModuleId,
    IN UINT16 VendorId,
    IN UINT16 DeviceId,
    OUT VOID **ImageStart,
    OUT UINTN *ImageSize
)
{
    return FindEmbeddedRom(ModuleId, VendorId, DeviceId, ImageStart, ImageSize);
}


//<AMI_PHDR_START>
//---------------------------------------------------------------------------
//
// Name:        InitializeCsm16MiscInfo
//
// Description:
//  This function initialize AMI specific CSM16 data: POST/RT variables in
//  CSM16 based on Setup settings, OEM porting overridesIt will be skipped
//  in case of non-AMI CSM16 binary.
//
// 
// Notes:
//  Shadow regions are unlocked.
//
//---------------------------------------------------------------------------
//<AMI_PHDR_END>

VOID
InitializeCsm16MiscInfo(
    LEGACY16_TO_EFI_DATA_TABLE_STRUC    *Csm16Data,
    SETUP_DATA  *Setup
)
{
    UINT8   KbcSupport;
    UINTN   Data;
    EFI_STATUS  Status;

    //
    // Initialize misc_info
    //
    KbcSupport = IoRead8(0x64);
    if (KbcSupport != 0xff) {
        Csm16Configuration(Csm16FeatureReset, Csm16LegacyFree, NULL);
    }
    else {
        Csm16Configuration(Csm16FeatureSet, Csm16LegacyFree, NULL);
    }

    if (Setup->ZipEmulation) {
        Csm16Configuration(Csm16FeatureSet, Csm16ZipHddEmulation, NULL);
    }

    Csm16Configuration(Csm16FeatureSet, Csm16I19Trap, NULL);
    Csm16Configuration(Csm16FeatureSet, Csm16Flexboot, NULL);

    // Set GA20 related information in misc_info and rt_cmos_byte
    Status = CoreBiosInfo->iBiosPlatform->GetPlatformInfo(CoreBiosInfo->iBiosPlatform,
                    EfiGetPlatformGateA20Information,
                    NULL, NULL, NULL,
                    &Data, 0, 0);
    if (!EFI_ERROR(Status)) {
        if (Data & 1) {
            Csm16Configuration(Csm16FeatureSet, Csm16GA20, NULL);
        } else {
            Csm16Configuration(Csm16FeatureReset, Csm16GA20, NULL);
        }
        if (Data & 2) {
            Csm16Configuration(Csm16FeatureSet, Csm16SkipGA20Deactivation, NULL);
        } else {
            Csm16Configuration(Csm16FeatureReset, Csm16SkipGA20Deactivation, NULL);
        }
    }
    // Set NMI related information in misc_info and rt_cmos_byte; if porting function is not
    // implemented, enable NMI
    Status = CoreBiosInfo->iBiosPlatform->GetPlatformInfo(CoreBiosInfo->iBiosPlatform,
                    EfiGetPlatformNmiInformation,
                    NULL, NULL, NULL,
                    &Data, 0, 0);
    if (EFI_ERROR(Status) || (Data == 1)) {
        Csm16Configuration(Csm16FeatureSet, Csm16Nmi, NULL);
     } else {
         Csm16Configuration(Csm16FeatureReset, Csm16Nmi, NULL);
    }

    // Allocate stack for reverse thunk
    {
        EFI_PHYSICAL_ADDRESS RtStackPtr;
        UINTN CsmRtStackPtrLocation;

        Status = pBS->AllocatePages(AllocateAnyPages, EfiReservedMemoryType, 16, &RtStackPtr);
        ASSERT_EFI_ERROR(Status);
        pBS->SetMem( (UINT8*)(UINTN)RtStackPtr, 0x10000, 0 );
        CsmRtStackPtrLocation = 0xf0000 + Csm16Data->ReverseThunkStackPtrOfs;
        *(UINTN*)CsmRtStackPtrLocation = (UINTN)RtStackPtr + 0x10000;
    }
    {
        // Update the E000 memory bounds
        UINTN StartOfFreeE000Ptr = 0xf0000 + Csm16Data->StartOfFreeE000Ofs;
        UINT16 StartOfFreeE000;
        UINT16 SizeOfFreeE000;

        ASSERT(gMaxOpRomAddress >= 0xdffff);
        ASSERT(gMaxOpRomAddress < 0xeffff);

        StartOfFreeE000 = (UINT16)((UINT32)gMaxOpRomAddress + 1);   // Cut off upper word
        SizeOfFreeE000 = ~StartOfFreeE000;

        *(UINT16*)StartOfFreeE000Ptr = StartOfFreeE000;
        *(UINT16*)(StartOfFreeE000Ptr + 2) = SizeOfFreeE000;
    }
    {
        // Allocate legacy boot context save buffer and pass the pointer and the size to CSM16
        UINTN NumberOfPages = EFI_SIZE_TO_PAGES(LEGACY_TO_EFI_BOOT_BUFFER_SIZE);
        EFI_PHYSICAL_ADDRESS Address = 0xffffffff;
        UINTN Csm16BufferPointer = 0xf0000 + Csm16Data->BootBufferPtrOfs;

        Status = pBS->AllocatePages (
                    AllocateMaxAddress,
                    EfiACPIMemoryNVS,
                    NumberOfPages,
                    &Address
        );
        ASSERT_EFI_ERROR(Status);

        TRACE((-1, "CSM LegacyBoot context save buffer: %x, size %x; pointer is updated at %x\n",
                Address, LEGACY_TO_EFI_BOOT_BUFFER_SIZE, Csm16BufferPointer));

        *(UINT32*)Csm16BufferPointer = (UINT32)Address;
        *(UINT32*)(Csm16BufferPointer+4) = LEGACY_TO_EFI_BOOT_BUFFER_SIZE;

        Csm16Configuration(Csm16FeatureReset, Csm16LegacyToEfi, NULL);
        Csm16Configuration(Csm16FeatureReset, Csm16LegacyToEfiPonr, NULL);

#if LEGACY_TO_EFI_DEFAULT
        Csm16Configuration(Csm16FeatureSet, Csm16LegacyToEfi, NULL);
#if LEGACY_TO_EFI_BOOTRECORD_RETURN
        Csm16Configuration(Csm16FeatureSet, Csm16LegacyToEfiPonr, NULL);
#endif
#endif
    }
}


//<AMI_PHDR_START>
//---------------------------------------------------------------------------
//
// Name:        EnablePciDevices
//
// Description:
//  This function enables all PCI devices before legacy boot
//
//---------------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS EnablePciDevices(EFI_LEGACY_BIOS_PROTOCOL *Bios)
{
    EFI_PCI_IO_PROTOCOL *PciIo;
    UINTN       Count;
    EFI_HANDLE  *Buffer;
    UINTN       i;
    EFI_STATUS  Status;
    UINT8       PciCfg[4];
    UINT64      Capabilities;

    Status = pBS->LocateHandleBuffer(ByProtocol,
                    &gEfiPciIoProtocolGuid,
                    NULL,
                    &Count,
                    &Buffer);
    ASSERT_EFI_ERROR (Status);

    for (i = 0; i < Count; i++) {
        Status = pBS->HandleProtocol (Buffer[i], &gEfiPciIoProtocolGuid, &PciIo);
        ASSERT_EFI_ERROR (Status);

        PciIo->Pci.Read (PciIo, EfiPciIoWidthUint32, 8, 1, &PciCfg);    // Reg 8,9,A,B

        //
        // Skip enabling device for:
        // - VGA
        // - Old VGA
        // - IDE
        // - LPC Bridge
        //
        if ((PciCfg[3]==PCI_CL_DISPLAY && PciCfg[2]==PCI_CL_DISPLAY_SCL_VGA)
            || (PciCfg[3]==PCI_CL_OLD && PciCfg[2]==PCI_CL_OLD_SCL_VGA)
            || (PciCfg[3]==PCI_CL_MASS_STOR && PciCfg[2]==PCI_CL_MASS_STOR_SCL_IDE)) {
            continue;
        }
        Status = PciIo->Attributes (PciIo,
                EfiPciIoAttributeOperationSupported, 0,
                &Capabilities);     // Get device capabilities
        ASSERT_EFI_ERROR(Status);

        Status = PciIo->Attributes (PciIo,
                EfiPciIoAttributeOperationEnable,
                Capabilities & EFI_PCI_DEVICE_ENABLE,
                NULL);              // Enable device
        ASSERT_EFI_ERROR(Status);
    }

    pBS->FreePool(Buffer);

    return EFI_SUCCESS;
}


//<AMI_PHDR_START>
//------------------------------------------------------------------------------------
//
//  Name:       UpdatePciLastBus
//
// Description:
//  In a multiple root-complex platform, the CSM16 routine "rth_pci_get_last_bus"
//  needs to return the correct bus number. For example, in a 2 IOH system, the
//  base bus #s for IOH0 can be 0 and IOH1 can be 80h. It should not be assumned
//  there is only one root-complex and return the correct bus # (max bus of first IOH),
//  for the card is plugged into the 2nd IOH.
//
//  This function creates a callback notification event for EfiPciRootBridgeProtocol GUID
//  installation. The callback function then will process the list of root bridges and
//  will update the LastPciBus field of EFI_COMPATIBILITY16_TABLE accordingly.
//
//------------------------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS UpdatePciLastBus()
{
    EFI_STATUS  Status;
    EFI_EVENT   UpdatePciLastBusEvent;
    VOID        *UpdatePciLastBusReg = NULL;
    EFI_GUID    AmiExtPciBusProtocolGuid = AMI_PCI_BUS_EXT_PROTOCOL_GUID;

    //
    // Create the notification and register callback function on the AmiExtPciBusProtocolGuid,
    // callback function will update Pci Last Bus in Csm16 header.
    //
    Status = pBS->CreateEvent (
        EVT_NOTIFY_SIGNAL,
        TPL_CALLBACK,
        UpdatePciLastBusCallback,
        NULL,
        &UpdatePciLastBusEvent);
    ASSERT_EFI_ERROR(Status);

    if (EFI_ERROR(Status)) return Status;

    Status = pBS->RegisterProtocolNotify (
        &AmiExtPciBusProtocolGuid,
        UpdatePciLastBusEvent,
        &UpdatePciLastBusReg);
    ASSERT_EFI_ERROR(Status);

    return Status;
}

VOID ReadyToBootNotify(EFI_EVENT Event, VOID *Context)
{
    EFI_TO_COMPATIBILITY16_INIT_TABLE *Csm16InitTable;

    Csm16InitTable = &CoreBiosInfo->Thunk->Csm16InitTable;
    pBS->FreePool((VOID*)(UINTN)Csm16InitTable->HiPmmMemory);
    pBS->CloseEvent(Event);
}
 
//<AMI_PHDR_START>
//---------------------------------------------------------------------------
//
// Name:        CsmEntryPoint
//
// Description:
//  CSM driver entry point
//
//---------------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS
CsmEntryPoint(
    IN EFI_HANDLE     ImageHandle,
    IN EFI_SYSTEM_TABLE   *SystemTable
    )
{
    EFI_STATUS  Status;
    UINT16      IrqMask, SaveIrqMask;
    UINTN       Size=sizeof(SETUP_DATA);
    EFI_EVENT   Event;
    EFI_HANDLE  Handle = NULL;
    EFI_GUID    AMICSMStartedProtocolGuid = AMI_CSM_DRIVER_STARTED_GUID;
    EFI_GUID    AMICSMLoadProtocolGuid = AMI_LOAD_CSM_GUID;

    InitAmiLib(ImageHandle, SystemTable);

    PROGRESS_CODE(DXE_CSM_INIT);

    // Indicate that CSM has been launched. This protocol can be used as dependecy for other driver instead of 
    // LegacyBIOS protocol which may or may not be installed.
    pBS->InstallProtocolInterface (
        &Handle, &AMICSMStartedProtocolGuid, EFI_NATIVE_INTERFACE, NULL
        );

    // Clear uninitialized memory @ 0..640K
    Status = ClearFreeMemory(0, 0xa0000);
    ASSERT_EFI_ERROR(Status);
    if (EFI_ERROR(Status)) return Status;

#if CsmOptOut_SUPPORT
    {
        VOID        *CsmLoad;

        // Check if CSM needs to be enabled or not
        Status = pBS->LocateProtocol (&AMICSMLoadProtocolGuid, NULL, &CsmLoad);
        if (EFI_ERROR(Status)) {
            // Unload the image if CSM needs to be disabled
            return  Status;
        }
    }
#endif

    //
    // Initialize LegacyBiosPlatform
    //
    Status = InitCsmBoard (ImageHandle, SystemTable);
    if (EFI_ERROR(Status)) return Status;

    //
    // Initialize Csm Simple Key In
    //
    Status = InitCsmSimpleIn (ImageHandle, SystemTable);
    if (EFI_ERROR(Status)) return Status;

    //
    // Instantiate LEGACY_BIOS
    //
    Status = pBS->AllocatePool(EfiBootServicesData, sizeof(BIOS_INFO), &CoreBiosInfo);
    if (EFI_ERROR(Status)) return Status;

    pBS->SetMem(CoreBiosInfo, sizeof(BIOS_INFO), 0);
    CoreBiosInfo->hImage = ImageHandle;

    Status = pBS->LocateProtocol (&gEfiLegacyRegionProtocolGuid, NULL, &CoreBiosInfo->iRegion);
    if (EFI_ERROR(Status)) return Status;

    Status = pBS->LocateProtocol (&gEfiLegacyBiosPlatformProtocolGuid, NULL, &CoreBiosInfo->iBiosPlatform);
    if (EFI_ERROR(Status)) return Status;

    Status = pBS->LocateProtocol (&gEfiLegacy8259ProtocolGuid, NULL, &CoreBiosInfo->i8259);
    if (EFI_ERROR(Status)) return Status;

    Status = pBS->LocateProtocol (&gEfiLegacyInterruptProtocolGuid, NULL, &CoreBiosInfo->iInterrupt);
    if (EFI_ERROR(Status)) return Status;

	Status = pBS->LocateProtocol(&gAmiBoardInfoProtocolGuid, NULL,(VOID**)&gAmiBoardInfo);
	if(EFI_ERROR(Status))  return Status;

    CoreBiosInfo->iBios.Int86            = Int86;
    CoreBiosInfo->iBios.FarCall86        = FarCall86;
    CoreBiosInfo->iBios.CheckPciRom      = CheckPciRom;
    CoreBiosInfo->iBios.InstallPciRom    = InstallPciRom;
    CoreBiosInfo->iBios.PrepareToBootEFI = PrepareToBoot;
    CoreBiosInfo->iBios.LegacyBoot       = LegacyBoot;
    CoreBiosInfo->iBios.GetBbsInfo       = GetBbsInfo;
    CoreBiosInfo->iBios.ShadowAllLegacyOproms   = ShadowAllLegacyOproms;
    CoreBiosInfo->iBios.GetLegacyRegion         = GetLegacyRegion;
    CoreBiosInfo->iBios.CopyLegacyRegion        = CopyLegacyRegion;
    CoreBiosInfo->iBios.UpdateKeyboardLedStatus = UpdateKeyboardLedStatus;
    //
    // Call LegacyBiosPlatform to get the end of OpROM
    //
    Status = CoreBiosInfo->iBiosPlatform->GetPlatformInfo(
                    CoreBiosInfo->iBiosPlatform,
                    EfiGetPlatformEndRomShadowAddr,
                    NULL, NULL,
                    &gMaxOpRomAddress,
                    NULL, NULL, NULL);
    if (EFI_ERROR(Status)) {
        gMaxOpRomAddress = 0xDFFFF;
    }

    ASSERT(gMaxOpRomAddress > 0xC0000 && gMaxOpRomAddress < 0xF0000);

    //
    // Initialize memory
    //
    Status = InitializeLegacyMemory(CoreBiosInfo);
    if (EFI_ERROR(Status)) return Status;

    // Get the current IRQ mask
    Status = CoreBiosInfo->i8259->GetMask(CoreBiosInfo->i8259, &SaveIrqMask, NULL, NULL, NULL);
    ASSERT_EFI_ERROR(Status);

    // Mask all interrupts
    IrqMask = -1;
    Status = CoreBiosInfo->i8259->SetMask(CoreBiosInfo->i8259, &IrqMask, NULL, NULL, NULL);
    ASSERT_EFI_ERROR(Status);

	Status = pRS->GetVariable(L"Setup",&guidSetup, NULL, &Size, &gSetup);
    if (EFI_ERROR(Status)) {
        pBS->SetMem(&gSetup, sizeof(SETUP_DATA), 0);
    }

    // The following code implements the video mode switching policy during
    // Option ROMs installation. There are two ingredients in this policy
    // implementation - one SDL token and one setup question:
    //
    //  - SDL token CSM_DEFAULT_VMODE_SWITCHING
    //  - Setup question "Option ROM Messages" (use BIOS/keep current)
    //
    // Meaning of the "Option ROM Messages" setup options:
    //  - "Keep Current" installs dummy INT10, output from Option ROMs is
    //    suppressed, value of CSM_DEFAULT_VMODE_SWITCHING is ignored.
    //  - "Use BIOS" will have INT10 available for the Option ROMs to output
    //    the messages.
    // Meaning of the CSM_DEFAULT_VMODE_SWITCHING:
    //  - 0 - switch video mode from graphics to text before executing the
    //      Option ROM, switch back to graphics afterwards
    //  - 1 - use text mode during all Option ROMs execution time, no mode
    //      switching during this time frame.

    gSetTxtMode = CSM_DEFAULT_VMODE_SWITCHING;
    if (Status == EFI_SUCCESS && gSetup.ExpansionCardText == 0) {
        gSetTxtMode = 2;
    }

    //
    // Copy Compatibility16 binary into shadow and
    // call its Func0 (InitializeYourself)
    //
    Status = InitCompatibility16(CoreBiosInfo, SystemTable);
    if (EFI_ERROR(Status)) return Status;

    // Re-enable IRQ mask
    Status = CoreBiosInfo->i8259->SetMask(CoreBiosInfo->i8259, &SaveIrqMask, NULL, NULL, NULL);
    ASSERT_EFI_ERROR(Status);

    //
    // Create entries for legacy SW SMIs
    //
    Status = CoreBiosInfo->iBiosPlatform->SmmInit(
                CoreBiosInfo->iBiosPlatform,
                &CoreBiosInfo->Thunk->Csm16BootTable);
    ASSERT_EFI_ERROR(Status);

    //
    // Make a new handle and install the protocol
    //
    CoreBiosInfo->hBios = NULL;
    Status = pBS->InstallMultipleProtocolInterfaces(
                &CoreBiosInfo->hBios,
                &gEfiLegacyBiosProtocolGuid, &CoreBiosInfo->iBios,
                &gEfiLegacyBiosExtProtocolGuid, &gAmiCsmExtensionsProtocol,
                NULL
    );
    ASSERT_EFI_ERROR(Status);
    if (EFI_ERROR(Status)) return Status;

    CoreBiosInfo->hVga = NULL;

    gNextRomAddress = (UINT8*)0xC0000;   // Beginning of shadow region
    gIsBootPrepared = FALSE;
    gIsBbsInitialized = FALSE;
    gIsMassStorageInstalled = FALSE;

    //
    // Allocate memory for saved OpROM structures
    //
    Status = pBS->AllocatePool(EfiBootServicesData,
        MAX_BCV_OPROMS * sizeof(SAVED_PCI_ROM),
        &gSavedOprom);
    ASSERT_EFI_ERROR(Status);
    if (EFI_ERROR(Status)) return Status;

    pBS->SetMem(gSavedOprom, MAX_BCV_OPROMS * sizeof(SAVED_PCI_ROM), 0);
    gSavedOprom++;   // 1st entry is zero, this will let us find the beginning
                    // afterwards.
    //
    // Allocate memory for PciIo's with executed OpROMs
    //
    Status = pBS->AllocatePool(EfiBootServicesData,
        MAX_EXECUTED_OPROMS * sizeof(EXECUTED_PCI_ROM),
        &gExecutedRomsPci);
    ASSERT_EFI_ERROR(Status);
    if (EFI_ERROR(Status)) return Status;

    pBS->SetMem(gExecutedRomsPci, MAX_EXECUTED_OPROMS * sizeof(EXECUTED_PCI_ROM), 0);
    gExecutedRomsPci++;  // 1st entry is zero, this will let us find the
                        // beginning afterwards.
    //
    // Register callback notification on AllDriverConnected. 
    // This is set to TPL_NOTIFY so that this callback gets executed first
    // and GOP will be ready for the other callback function, who wants to 
    // display based on the AllDriverconnected event
    //
    Status = pBS->CreateEvent( EFI_EVENT_NOTIFY_SIGNAL,
                                TPL_NOTIFY,
                                AllConnectedCallback,
                                NULL,
                                &Event );

    ASSERT_EFI_ERROR(Status);

    Status = pBS->RegisterProtocolNotify(
                                &gBdsAllDriversConnectedProtocolGuid,
                                Event,
                                &gProtocolNotifyRegistration);


    ASSERT_EFI_ERROR(Status);

    UpdatePciLastBus(); // Update Pci Last Bus number in Csm16 Header

    Status = CreateReadyToBootEvent(TPL_CALLBACK, ReadyToBootNotify, NULL, &Event);
    ASSERT_EFI_ERROR(Status);

    return EFI_SUCCESS; // Force success: every unsuccessful status is branched
                        // before, GetVariable status will not be successful on 
                        // a "fresh" boot.
}


//<AMI_PHDR_START>
//---------------------------------------------------------------------------
//
// Name:        AllConnectedCallback
//
// Description:
//  This function is executed after all drivers have been connected.
//
// Notes:
//  Specific to Core version, first time this event is signaled in 4.6.3.1.
//
//---------------------------------------------------------------------------
//<AMI_PHDR_END>

VOID
AllConnectedCallback (
    EFI_EVENT Event,
    VOID      *Context
)
{
    if (gSetTxtMode == 1 && gVgaHandle != NULL) {
        pBS->ConnectController(gVgaHandle, NULL, NULL, TRUE);
    }
}


//<AMI_PHDR_START>
//---------------------------------------------------------------------------
//
// Name:  FindCompatibility16Table
//
// Description:
//  This function identifies the validity of CSM16 binary by searching "$EFI"
//  and verifying table checksum and returs the location of $EFI table
//
// Input:
//  RomImageStart    Binary location address
//  RomImageSize     Size in bytes
//
// Output:
//  Address of the beginning of $EFI table or NULL if this table is not found
//
// Notes:
//  Compatibility16 binary is linked with the current section
//
//---------------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_COMPATIBILITY16_TABLE*
FindCompatibility16Table(
    VOID *RomImageStart,
    UINTN RomImageSize
)
{
    UINT8 *ImageStart = RomImageStart;
    UINT8 *ImageEnd = ImageStart + RomImageSize;

    for (;ImageStart < ImageEnd; ImageStart +=16) {
        if (*(UINT32*)ImageStart == '$EFI') {
            UINT8 TableLength = ((EFI_COMPATIBILITY16_TABLE*)ImageStart)->TableLength;
            UINT8 Checksum = 0;
            UINT8 i;
            for(i=0; i < TableLength; ++i) Checksum += ImageStart[i];
            return (Checksum == 0) ? (EFI_COMPATIBILITY16_TABLE*)ImageStart : 0;
        }
    }

    return NULL;
}


//<AMI_PHDR_START>
//---------------------------------------------------------------------------
//
// Name:  ClearFreeMemory
//
// Description:
//  This function goes through system memory map and clears memory that is not
//  allocated within the given range.
//
// Input:
//  Start and End addresses 
//
// Output:
//  EFI_STATUS the status of memory clearing operation
//
//---------------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS ClearFreeMemory(
    EFI_PHYSICAL_ADDRESS AddrFrom,
    EFI_PHYSICAL_ADDRESS AddrTo
)
{
    EFI_MEMORY_DESCRIPTOR *MemoryMap = NULL;
    EFI_MEMORY_DESCRIPTOR *MemDesc = NULL;
    UINTN DescriptorSize = 0;
    UINTN NumberOfDescriptors = 0;
    EFI_STATUS Status;
    UINTN i;
    UINTN Size;

    Status = GetSystemMemoryMap(&MemoryMap, &DescriptorSize, &NumberOfDescriptors);
    ASSERT_EFI_ERROR(Status);

    if (EFI_ERROR(Status)) return Status;

    for (i = 0; i < NumberOfDescriptors; i++)
    {
        MemDesc = (EFI_MEMORY_DESCRIPTOR*)((UINT8*)MemoryMap + i * DescriptorSize);

        if (MemDesc->Type == EfiConventionalMemory &&
            MemDesc->PhysicalStart < AddrTo &&
            MemDesc->PhysicalStart >= AddrFrom
        )
        {
            Size = (UINTN)MemDesc->NumberOfPages * EFI_PAGE_SIZE;
            if (((UINTN)MemDesc->PhysicalStart + Size) > (UINTN)AddrTo)
            {
                Size = (UINTN)AddrTo - (UINTN)MemDesc->PhysicalStart;
            }

            pBS->SetMem((VOID*)(UINTN)MemDesc->PhysicalStart, Size, 0);
        }
    }

    pBS->FreePool(MemoryMap);

    return EFI_SUCCESS;
}


//<AMI_PHDR_START>
//---------------------------------------------------------------------------
//
// Name:  InitializeLegacyMemory
//
// Description:
//  This function initializes CSM related memory regions
//
// Input:
//  BIOS_INFO *CoreBiosInfo
//
// Output:
//  EFI_STATUS  Legacy memory initialization status
//
// Referrals:
//  BIOS_INFO
//
//---------------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS  InitializeLegacyMemory(BIOS_INFO *CoreBiosInfo)
{
    EFI_PHYSICAL_ADDRESS    Address;
    EFI_CPU_ARCH_PROTOCOL   Cpu;
    EFI_CPU_ARCH_PROTOCOL   *pCpu = &Cpu;
    EFI_GUID                gCpu = EFI_CPU_ARCH_PROTOCOL_GUID;
    EFI_STATUS              Status;
    BDA_DATA                *bda;
    UINT8                   *ebda;
    BBS_TABLE               *BbsEntry;
    UINT16                  i;
    UINT32                  TopOfBaseMemory;

    //
    // Set memory attributes for legacy regions
    //
    Status = pBS->LocateProtocol(&gCpu, NULL, &pCpu);
    if (EFI_ERROR(Status)) return Status;
    pCpu->SetMemoryAttributes(pCpu, 0xC0000, 0x40000, EFI_MEMORY_WP);   // WriteProtected

    //
    // Allocate PMM and EBDA areas at the top of 640K; if some memory was already allocated,
    // then adjust base memory information accordingly in 40:13 and EBDA
    //
    Address = 0xa0000;
    Status = pBS->AllocatePages (
                AllocateMaxAddress,
                EfiBootServicesCode,
                PMM_EBDA_LOMEM_SIZE >> 12,  // Bytes->4KiloBytes conversion
                &Address);

    ASSERT_EFI_ERROR(Status);
    if (EFI_ERROR(Status)) return Status;

    TopOfBaseMemory = (UINT32)Address+PMM_EBDA_LOMEM_SIZE;
    ASSERT(TopOfBaseMemory>=PMM_EBDA_LOMEM_SIZE+0x8000);	// PMM, EBDA, and extra 32KB must fit in
    if (TopOfBaseMemory<(PMM_EBDA_LOMEM_SIZE+0x8000))
        return EFI_OUT_OF_RESOURCES;

    //
    // Allocate base memory for IVT/BDA(0..2K), PMM data(2K..6K), Thunk (6K..32K),
    // low memory PMM and EBDA (640K-PMM_EBDA_LOMEM_SIZE .. 640K).
    //
    Address = 0;    // Allocate 0..32K
    Status = pBS->AllocatePages (AllocateAddress,
                    EfiBootServicesCode, 8, &Address);
    ASSERT_EFI_ERROR(Status);

    CoreBiosInfo->Thunk = (THUNK_MEMORY*)0x1800;    // at 6K

    //
    // Initialize BDA and EBDA
    //
    bda = (BDA_DATA*)((UINTN) 0x400);

    bda->system_memory = (TopOfBaseMemory>>10)-1;   // 1K is for BIOS EBDA
    bda->kb_buf_head_ptr = bda->kb_buf_tail_ptr = 0x1E;
    bda->motor_time_count = 0xFF;
    bda->kb_buff_begin = 0x1E;
    bda->kb_buff_end = 0x3E;

    bda->current_floppy_media[0] = 7;
    bda->winch_number = 0;
//  bda->machine_config is updated later when SIO information becomes available

    bda->ext_bios_data_seg = (TopOfBaseMemory>>4)-0x40;

    ebda = (UINT8*)((UINTN)(TopOfBaseMemory-0x400));
    *ebda = 1;  // 1K

    //
    // Create BBS table and initialize it with BBS_IGNORE_ENTRY values
    //
    Status = pBS->AllocatePool(
                EfiBootServicesData,
                sizeof(BBS_TABLE)*MAX_BBS_ENTRIES_NO,
                &CoreBiosInfo->BbsTable);
    pBS->SetMem(CoreBiosInfo->BbsTable, sizeof(BBS_TABLE)*MAX_BBS_ENTRIES_NO, 0);

    for (BbsEntry = CoreBiosInfo->BbsTable, i = 0; i < MAX_BBS_ENTRIES_NO; i++, BbsEntry++) {
        BbsEntry->BootPriority = BBS_IGNORE_ENTRY;
    }

    CoreBiosInfo->BbsEntriesNo = MAX_IDE_CONTROLLER*2 + 1;  //  1 floppy + up to MAX_IDE_CONTROLLER*2 HDD

    return Status;
}


//<AMI_PHDR_START>
//---------------------------------------------------------------------------
//
// Name:        InitCompatibility16
//
// Description:
//  This function reads Compatibility16 binary into the pre-defined shadow
//  memory region, executes InitializeYourself function and initializes Thunk
//  data structures.
//
// Input:
//  BIOS_INFO           *CoreBiosInfo
//  EFI_SYSTEM_TABLE    *SystemTable
//
// Output:
//  EFI_SUCCESS = Success
//
// Notes:
//  InitializeLegacyMemory has to be executed prior to this function
//
//---------------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS
InitCompatibility16(
    IN BIOS_INFO        *CoreBiosInfo,
    IN EFI_SYSTEM_TABLE *SystemTable
)
{
    EFI_STATUS          Status;
    VOID                *RomImageStart;
    UINTN               RomImageSize;
    EFI_IA32_REGISTER_SET   RegSet;
    EFI_TO_COMPATIBILITY16_INIT_TABLE   *Csm16InitTable;
    UINT32              *ivt = (UINT32*)0;
    UINT16              RedirSeg, RedirOfs;
    UINT8               i;
    UINTN               LowPmmMemorySizeInBytes;
    UINTN               HiPmmMemorySizeInBytes;
    VOID                *HiPmmMemory;
    UINTN               PciExpressBase;

    struct IRQ_REDIRECTION_CODE {
        UINT8 intOpCode;
        UINT8 intnumOpCode;
        UINT8 iretOpCode;
    } RedirTable[8] = {
        {0xcd, 0x08, 0xcf}, // int 8, iret
        {0xcd, 0x09, 0xcf}, // int 9, iret
        {0xcd, 0x0a, 0xcf}, // int a, iret
        {0xcd, 0x0b, 0xcf}, // int b, iret
        {0xcd, 0x0c, 0xcf}, // int c, iret
        {0xcd, 0x0d, 0xcf}, // int d, iret
        {0xcd, 0x0e, 0xcf}, // int e, iret
        {0xcd, 0x0f, 0xcf}  // int f, iret
    };

    UINT8   *InterruptsToPreserve;
    UINTN   NumberOfInterruptsToPreserve;

    //
    // Open all shadow regions for writing and initalize them
    //
    Status = CoreBiosInfo->iRegion->UnLock (CoreBiosInfo->iRegion,
        0xC0000, 0x40000, NULL);

    pBS->SetMem((UINT8*)(UINTN)0xC0000, gMaxOpRomAddress-0xBFFFF, 0xFF);
    pBS->SetMem((UINT8*)(gMaxOpRomAddress+1), 0xFFFFF-gMaxOpRomAddress, 0);

    CoreBiosInfo->HddCount = 0;

    //
    // Get Eficompatibility16 binary
    //
    Status = CoreBiosInfo->iBiosPlatform->GetPlatformInfo(
                    CoreBiosInfo->iBiosPlatform,
                    EfiGetPlatformBinarySystemRom,
                    &RomImageStart, &RomImageSize,
                    NULL, NULL, NULL, NULL);
    if (EFI_ERROR(Status)) return Status;

    pBS->CopyMem((VOID*)((UINTN)(0x100000-RomImageSize)), RomImageStart, RomImageSize);
    RomImageStart = (VOID*)((UINTN)(0x100000-RomImageSize));

    CoreBiosInfo->Csm16Header = FindCompatibility16Table(RomImageStart, RomImageSize);
    if (CoreBiosInfo->Csm16Header == NULL) return EFI_NOT_FOUND;

    //
    // Save CSM16 entry point
    //
    CoreBiosInfo->Csm16EntrySeg = CoreBiosInfo->Csm16Header->Compatibility16CallSegment;
    CoreBiosInfo->Csm16EntryOfs = CoreBiosInfo->Csm16Header->Compatibility16CallOffset;

    //
    // Get PCIe base address
    //
    Status = CoreBiosInfo->iBiosPlatform->GetPlatformInfo(
                    CoreBiosInfo->iBiosPlatform,
                    EfiGetPlatformPciExpressBase,
                    NULL, NULL,
                    &PciExpressBase,
                    NULL, NULL, NULL);

    CoreBiosInfo->Csm16Header->PciExpressBase = (EFI_ERROR(Status))? 0 : (UINT32)PciExpressBase;

//TODOx64: What is SystemTable pointer is more the 4G in 64 bit mode?
//CSM specification 0.96 defines the pointer as UINT32
    CoreBiosInfo->Csm16Header->EfiSystemTable = (UINT32)SystemTable;

    //
    // Initialize thunk code
    //
    Status = InitializeThunk(CoreBiosInfo);
    if (EFI_ERROR(Status)) return Status;

    //
    // Fill in EFI_TO_COMPATIBILITY16_INIT_TABLE for InitializeYourself input
    //
    Csm16InitTable = &CoreBiosInfo->Thunk->Csm16InitTable;  // Located below 1 MB
    Csm16InitTable->ThunkStart = (UINT32)CoreBiosInfo->Thunk;
    Csm16InitTable->ThunkSizeInBytes = sizeof (THUNK_MEMORY);
    Csm16InitTable->LowPmmMemory = 0xa0000-PMM_EBDA_LOMEM_SIZE;
    Csm16InitTable->ReverseThunkCallSegment = Csm16InitTable->ThunkStart >> 4;
    Csm16InitTable->ReverseThunkCallOffset = *(UINT16*)(UINTN)(Csm16InitTable->ThunkStart + 4);

    GetExtendedMemSize(&Csm16InitTable->OsMemoryAbove1Mb);

    //
    // E820 table will be valid before PrepareToBoot
    //
    Csm16InitTable->NumberE820Entries = 0;

    //
    // Call LegacyBiosPlatform to get the PMM boundaries
    //
    Status = CoreBiosInfo->iBiosPlatform->GetPlatformInfo(
                    CoreBiosInfo->iBiosPlatform,
                    EfiGetPlatformPmmSize,
                    NULL,
                    &LowPmmMemorySizeInBytes,
                    NULL,
                    &HiPmmMemorySizeInBytes,
                    NULL,
                    NULL);
    ASSERT_EFI_ERROR(Status);

    Csm16InitTable->LowPmmMemorySizeInBytes = (UINT32)LowPmmMemorySizeInBytes;
    Csm16InitTable->HiPmmMemorySizeInBytes = (UINT32)HiPmmMemorySizeInBytes;

    //
    // Allocate Hi memory for PMM
    //
    Status = pBS->AllocatePool(
                EfiBootServicesData,
                Csm16InitTable->HiPmmMemorySizeInBytes,
                &HiPmmMemory);
    ASSERT_EFI_ERROR(Status);
    Csm16InitTable->HiPmmMemory = (UINT32)HiPmmMemory;

    //
    // Make a call to 16 bit code to initialize itself
    //
    pBS->SetMem(&RegSet, sizeof (EFI_IA32_REGISTER_SET), 0);
    RegSet.X.AX = Compatibility16InitializeYourself;
    RegSet.X.ES = EFI_SEGMENT (Csm16InitTable);
    RegSet.X.BX = EFI_OFFSET (Csm16InitTable);

    FarCall86 (&CoreBiosInfo->iBios,
                CoreBiosInfo->Csm16EntrySeg,
                CoreBiosInfo->Csm16EntryOfs,
                &RegSet,
                NULL,
                0);
    if (RegSet.X.AX) Status = (RegSet.X.AX & 0x7FFF) | EFI_ERROR_BIT;
    ASSERT_EFI_ERROR(Status);
    if (EFI_ERROR(Status)) return Status;

    // InitializeYourself (func #0) that has just executed, returns a pointer to
    // LEGACY16_TO_EFI_DATA_TABLE_STRUC to pass the AMIBIOS specific data to CSM16
    // This structure is AMI BIOS specific, so that the following call that updates
    // CSM16 data structures must be avoided for non-AMI CSM16 binaries.

    if (IsAMICSM16(CoreBiosInfo->Csm16Header)) {
        // Program POST/RT variables in CSM16 based on Setup settings, OEM porting overrides
        InitializeCsm16MiscInfo(
            (LEGACY16_TO_EFI_DATA_TABLE_STRUC*)(UINTN)Csm16InitTable->BiosLessThan1MB, &gSetup
        );
    }

    Status = InitializePortingHooks(CoreBiosInfo);
    if (EFI_ERROR(Status)) {
        TRACE((-1,"No OEM/Chipset CSM16 porting hooks found.\n"));
    }

    // Update project specific fields in CSM16 bin
    if (IsAMICSM16(CoreBiosInfo->Csm16Header)) {

        // BIOS date, time, and version information
        UINT8   BiosDate[] = TODAY;
        UINT8   BiosTime[] = NOW;
        UINT8   *p = (UINT8*)0xff55b;

        pBS->CopyMem(p, BiosDate, 6);    // MM/DD/
        // Place two-digit year since TODAY is in a different format
        p[6] = BiosDate[8];
        p[7] = BiosDate[9];

        pBS->CopyMem(&p[9], BiosTime, 8);   // BIOS time

        Sprintf(&p[23], "%02X.%02X.%02X",
            CORE_MAJOR_VERSION, CORE_MINOR_VERSION, CORE_REVISION);

        // Update BIOS project tag
        p = (UINT8*)0xff4f0;

        // The following conversion assumes the following:
        // 1. PROJECT_TAG to be 5 Bytes long, e.g. '0ABCD'; this assumption
        //    follows AMI project naming convention.
        // 2. PROJECT_MAJOR_VERSION is limited to one decimal digit, i.e. in
        //    the range from 0 to 9.
        //    If it is greater than 9, then the upper digit(s) will be truncated. This is
        //    needed to keep the length of the project tag as 8.
        Sprintf(&p[0], "%s%1d%02d",
            CONVERT_TO_STRING(PROJECT_TAG), PROJECT_MAJOR_VERSION, PROJECT_MINOR_VERSION);
    }

    ChecksumCSM16Header(CoreBiosInfo->Csm16Header);

    //
    // Lock legacy region
    //
    CoreBiosInfo->iRegion->Lock (
        CoreBiosInfo->iRegion,
        0xC0000,
        0x40000,
        NULL
    );

    //
    // Initialize interrupt save tables with 0
    //
    pBS->SetMem(gIrqSav, sizeof(gIrqSav), 0);

    //
    // Prepare hardware interrupt (IRQ0...IRQF) redirection table
    //
    pBS->CopyMem(&CoreBiosInfo->Thunk->InterruptRedirectionCode, RedirTable, 8*3);
    RedirSeg = EFI_SEGMENT(CoreBiosInfo->Thunk->InterruptRedirectionCode);
    RedirOfs = EFI_OFFSET(CoreBiosInfo->Thunk->InterruptRedirectionCode);

    CoreBiosInfo->i8259->GetVector(CoreBiosInfo->i8259, 0, &irq0);

    for(i = 0; i < 8; i++) {
        UINT32 vector;

        HwIrqRedirSav[i] = ivt[irq0 + i];
        vector = RedirSeg << 4 | RedirOfs;
        ivt[irq0 + i] = vector;
        RedirOfs += 3;
    }

    Status = CoreBiosInfo->iBiosPlatform->GetPlatformInfo(CoreBiosInfo->iBiosPlatform,
                    EfiGetPlatformIntSaveRestoreTable,
                    &InterruptsToPreserve,
                    &NumberOfInterruptsToPreserve,
                    NULL, NULL, 0, 0);
    if (!EFI_ERROR(Status)) {
        if (NumberOfInterruptsToPreserve > MAX_NUM_IRQS_SAVERESTORE) {
            NumberOfInterruptsToPreserve = MAX_NUM_IRQS_SAVERESTORE;
        }
        for (i = 0; i < NumberOfInterruptsToPreserve; i++) {
            gIrqSav[i].irq_num = InterruptsToPreserve[i];
            gIrqSav[i].irq_adr = ivt[InterruptsToPreserve[i]];
        }
    }


    return EFI_SUCCESS;
}


//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Name:        GetBbsInfo
//
// Description:
//  Presents BBS information to external agents.
//
// Input:
//  This        Indicates the EFI_LEGACY_BIOS_PROTOCOL instance.
//  HddCount    Number of HDD_INFO structures.
//  HddInfo     Onboard IDE controller information.
//  BbsCount    Number of BBS_TABLE structures.
//  BbsTable    BBS entry.
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS
GetBbsInfo (
  IN EFI_LEGACY_BIOS_PROTOCOL         *This,
  OUT  UINT16                         *HddCount,
  OUT  struct _HDD_INFO               **HddInfo,
  OUT  UINT16                         *BbsCount,
  IN OUT  struct _BBS_TABLE           **BbsTable
)
{
    BBS_TABLE *BbsEntry;
    UINT8 count=0;
    EFI_STATUS  Status;
    EFI_IA32_REGISTER_SET RegSet;

    if (!gIsBbsInitialized) {
        //
        // Insert floppy drive entry
        //
        BbsEntry = CoreBiosInfo->BbsTable;
        BbsEntry->Bus        = 0xFF;
        BbsEntry->Device     = 0xFF;
        BbsEntry->Function   = 0xFF;
        BbsEntry->DeviceType = BBS_FLOPPY;
        BbsEntry->Class      = 1;
        BbsEntry->SubClass   = 2;

        switch (GetFDDStatus()) {
            case NO_FLOPPY_DRIVE: BbsEntry->BootPriority = BBS_IGNORE_ENTRY; break;
            case NO_FLOPPY_DISK:
            case FLOPPY_INSERTED: BbsEntry->BootPriority = BBS_UNPRIORITIZED_ENTRY; break;
        }

        if (!gIsMassStorageInstalled) {
            InstallLegacyMassStorageDevices();
        }
        Status = UpdateCsm16Configuration(&CoreBiosInfo->Thunk->Csm16BootTable);
        ASSERT_EFI_ERROR(Status);

        //
        // Make UpdateBBS call to CSM16 to adjust the table if needed.
        //
        pBS->SetMem(&RegSet, sizeof (EFI_IA32_REGISTER_SET), 0);
        RegSet.X.AX = Compatibility16UpdateBbs;
        RegSet.X.ES = EFI_SEGMENT (&CoreBiosInfo->Thunk->Csm16BootTable);
        RegSet.X.BX = EFI_OFFSET (&CoreBiosInfo->Thunk->Csm16BootTable);

        Status = CoreBiosInfo->iRegion->UnLock (
            CoreBiosInfo->iRegion,
            (UINT32)gMaxOpRomAddress+1,
            0xFFFFF-(UINT32)gMaxOpRomAddress,
            NULL
        );
        ASSERT_EFI_ERROR(Status);

        FarCall86 (&CoreBiosInfo->iBios,
                    CoreBiosInfo->Csm16EntrySeg,
                    CoreBiosInfo->Csm16EntryOfs,
                    &RegSet,
                    NULL,
                    0);
        Status = (RegSet.X.AX)? ((RegSet.X.AX & 0x7FFF) | EFI_ERROR_BIT) : EFI_SUCCESS;
        ASSERT_EFI_ERROR(Status);
        CoreBiosInfo->iRegion->Lock (
            CoreBiosInfo->iRegion,
            (UINT32)gMaxOpRomAddress+1,
            0xFFFFF-(UINT32)gMaxOpRomAddress,
            NULL
        );

        CoreBiosInfo->BbsEntriesNo = CoreBiosInfo->Thunk->Csm16BootTable.NumberBbsEntries;
        gIsBbsInitialized = TRUE;
    }

    *HddCount = CoreBiosInfo->HddCount;
    *HddInfo  = CoreBiosInfo->Thunk->Csm16BootTable.HddInfo;
    *BbsCount = CoreBiosInfo->BbsEntriesNo;
    *BbsTable = CoreBiosInfo->BbsTable;

    return EFI_SUCCESS;
}


//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Name:        UpdateKeyboardLedStatus
//
// Description:
//  Updates the BDA to reflect status of the Scroll Lock, Num Lock, and Caps
//  Lock keys and LEDs.
//
// Input:
//  This    Indicates the EFI_LEGACY_BIOS_PROTOCOL instance.
//  Leds    Current LED status, as follows:
//                      Bit 0 - Scroll Lock         
//                      Bit 1 - Num Lock
//                      Bit 2 - Caps Lock
// Output:
//  EFI_SUCCESS The BDA was updated successfully.
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS
UpdateKeyboardLedStatus(
  IN EFI_LEGACY_BIOS_PROTOCOL         *This,
  IN  UINT8                           Leds
)
{
    *(UINT8*)0x417 &= 0x8F;         // Clear BIT4, BIT5 and BIT6
    *(UINT8*)0x417 |= (Leds << 4);  // Set the state of xLock keys
    return EFI_SUCCESS;
}


//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Name:        CopyLegacyTable
//
// Description:
//  This fuction allocates CSM16 memory within E0000..FFFFF and then copies the
//  passed data into allocated region.
//
// Input:
//  Data to be copied, data size and CSM16 and memory location attribute
//  (F0000_BIT or E0000_BIT or both)
//
// Notes:
//  CSM16 memory must be open for writing.
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

UINTN
CopyLegacyTable(
    VOID *Table,
    UINT16 TableSize,
    UINT16 Alignment,
    UINT16 Csm16LocationAttribute)
{
    EFI_IA32_REGISTER_SET   RegSet;
    EFI_STATUS Status;
    UINTN Dest = 0;

    Status = CoreBiosInfo->iRegion->UnLock (
        CoreBiosInfo->iRegion,
        (UINT32)gMaxOpRomAddress+1,
        0xFFFFF-(UINT32)gMaxOpRomAddress,
        NULL
    );
    ASSERT_EFI_ERROR(Status);

    pBS->SetMem(&RegSet, sizeof (EFI_IA32_REGISTER_SET), 0);
    RegSet.X.AX = Compatibility16GetTableAddress;
    RegSet.X.BX = Csm16LocationAttribute;
    RegSet.X.CX = TableSize;
    RegSet.X.DX = Alignment;

    FarCall86 (&CoreBiosInfo->iBios,
                CoreBiosInfo->Csm16EntrySeg,
                CoreBiosInfo->Csm16EntryOfs,
                &RegSet,
                0, 0);

    Status = (RegSet.X.AX)? EFI_OUT_OF_RESOURCES : EFI_SUCCESS;
    ASSERT_EFI_ERROR(Status);

    if (!(EFI_ERROR(Status))) {
        Dest = ((UINTN)RegSet.X.DS << 4) + RegSet.X.BX;
        pBS->CopyMem((VOID*)Dest, Table, TableSize);
    }

    Status = CoreBiosInfo->iRegion->Lock (
        CoreBiosInfo->iRegion,
        (UINT32)gMaxOpRomAddress+1,
        0xFFFFF-(UINT32)gMaxOpRomAddress,
        NULL
    );
    ASSERT_EFI_ERROR(Status);

    return Dest;
}


//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Name:        GetLegacyRegion
//
// Description:
//  This function is called when EFI needs to reserve an area in the 0xE0000
//  or 0xF0000 64 KB blocks.
//
// Input:
//  This                Indicates the EFI_LEGACY_BIOS_PROTOCOL instance.
//  LegacyMemorySize    Requested size in bytes of the region.
//  Region              Requested region.
//                          00 = Either 0xE0000 or 0xF0000 blocks.
//                          Bit0 = 1 Specify 0xF0000 block
//                          Bit1 = 1 Specify 0xE0000 block
//  Alignment           Bit-mapped value specifying the address alignment 
//                      of the requested region. The first nonzero value 
//                      from the right is alignment.
//  LegacyMemoryAddress Address assigned.
//
// Output:
//  EFI_SUCCESS The requested region was assigned.
//  EFI_ACCESS_DENIED   The function was previously invoked.
//  Other   The requested region was not assigned.
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS
GetLegacyRegion (
  IN EFI_LEGACY_BIOS_PROTOCOL          *This,
  IN UINTN                             LegacyMemorySize,
  IN UINTN                             Region,
  IN UINTN                             Alignment,
  OUT VOID                             **LegacyMemoryAddress
 )
{
    EFI_IA32_REGISTER_SET   Regs;
    EFI_STATUS              Status;

    CoreBiosInfo->iRegion->UnLock (
        CoreBiosInfo->iRegion,
        (UINT32)gMaxOpRomAddress+1,
        0xFFFFF-(UINT32)gMaxOpRomAddress,
        NULL
    );

    pBS->SetMem(&Regs, sizeof (EFI_IA32_REGISTER_SET), 0);
    Regs.X.AX = Compatibility16GetTableAddress;
    Regs.X.BX = (UINT16) Region;
    Regs.X.CX = (UINT16) LegacyMemorySize;
    Regs.X.DX = (UINT16) Alignment;
    FarCall86 (
            This,
            CoreBiosInfo->Csm16EntrySeg,
            CoreBiosInfo->Csm16EntryOfs,
            &Regs,
            NULL,
            0
            );

    Status = (Regs.X.AX)? ((Regs.X.AX & 0x7FFF) | EFI_ERROR_BIT) : EFI_SUCCESS;

    mAllocatedOnceMemory = (VOID *) (UINTN) ((Regs.X.DS << 4) + Regs.X.BX);
    *LegacyMemoryAddress  = mAllocatedOnceMemory;

    CoreBiosInfo->iRegion->Lock (
        CoreBiosInfo->iRegion,
        (UINT32)gMaxOpRomAddress+1,
        0xFFFFF-(UINT32)gMaxOpRomAddress,
        NULL
    );

    return Status;
}


//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Name:        CopyLegacyRegion
//
// Description:
//  This function is called when copying data to the region assigned by
//  EFI_LEGACY_BIOS_PROTOCOL.GetLegacyRegion().
//
// Input:
//  This                Indicates the EFI_LEGACY_BIOS_PROTOCOL instance.
//  LegacyMemorySize    Size in bytes of the memory to copy.
//  LegacyMemoryAddress The location within the region returned by
//                      EFI_LEGACY_BIOS_PROTOCOL.GetLegacyRegion().
//  LegacyMemorySourceAddress       Source of the data to copy.
//
// Output:
//  EFI_SUCCESS         The data was copied successfully.
//  EFI_ACCESS_DENIED   Either the starting or ending address is out of bounds.
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS
CopyLegacyRegion (
  IN EFI_LEGACY_BIOS_PROTOCOL          *This,
  IN UINTN                             LegacyMemorySize,
  IN VOID                              *LegacyMemoryAddress,
  IN VOID                              *LegacyMemorySourceAddress
)
{
    EFI_STATUS Status = EFI_SUCCESS;

    if (((UINTN)LegacyMemoryAddress <= gMaxOpRomAddress) ||
        ((UINTN) ((UINTN) (LegacyMemoryAddress) + LegacyMemorySize) > 0xFFFFF)) {
        return EFI_ACCESS_DENIED;
    }

    Status = CoreBiosInfo->iRegion->UnLock (
        CoreBiosInfo->iRegion,
        (UINT32)gMaxOpRomAddress+1,
        0xFFFFF-(UINT32)gMaxOpRomAddress,
        NULL
    );
    ASSERT_EFI_ERROR(Status);
    if (EFI_ERROR(Status)) return Status;

    pBS->CopyMem(LegacyMemoryAddress, LegacyMemorySourceAddress, LegacyMemorySize);

    CoreBiosInfo->iRegion->Lock (
        CoreBiosInfo->iRegion,
        (UINT32)gMaxOpRomAddress+1,
        0xFFFFF-(UINT32)gMaxOpRomAddress,
        NULL
    );

    return Status;
}


//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Name:        PrepareToBoot
//
// Description:
//  This function is called when booting an EFI-aware OS with legacy hard disks.
//  The legacy hard disks may or may not be the boot device but will be accessed
//  by the EFI-aware OS.
//
// Input:
//  This        Indicates the EFI_LEGACY_BIOS_PROTOCOL instance.
//  BbsCount    Number of BBS_TABLE structures.
//  BbsTable    BBS entry.
//
// Output:
//  Status of the boot preparation.
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS
PrepareToBoot(
  IN EFI_LEGACY_BIOS_PROTOCOL         *This,
  OUT  UINT16                         *BbsCount,
  OUT  struct _BBS_TABLE              **BbsTable
)
{
    EFI_STATUS  Status;
    EFI_IA32_REGISTER_SET   RegSet;
    UINTN E820MapAddress;
    UINT32 *ivt = (UINT32*)0;
    SAVED_PCI_ROM   *rom;
    UINT32 LockUnlockAddr, LockUnlockSize;

    CoreBiosInfo->NumberE820Entries = UpdateE820Map(CoreBiosInfo->E820Map);

    Status = UpdateCsm16Configuration(&CoreBiosInfo->Thunk->Csm16BootTable);
    ASSERT_EFI_ERROR(Status);

    //
    // Copy prepared ACPI, E820 tables to F000 segment and update EFI header.
    // Note that after executing CopyLegacyTable function E/F000 regions are read-only.
    //
    E820MapAddress = CopyLegacyTable(
                CoreBiosInfo->E820Map,
                CoreBiosInfo->NumberE820Entries * sizeof(E820_ENTRY),
                0,  // alignment
                0); // either E000 or F000 segment
    ASSERT(E820MapAddress);

    //
    // Unlock the shadow regions necessary for OpROM execution
    //
    Status = UnlockShadow(
        (UINT8*)(UINTN)0xC0000,
        (UINTN)gNextRomAddress-0xC0000,
        &LockUnlockAddr,
        &LockUnlockSize
    );
    ASSERT_EFI_ERROR(Status);

    CoreBiosInfo->Csm16Header->E820Pointer = (UINT32)E820MapAddress;
    CoreBiosInfo->Csm16Header->E820Length = CoreBiosInfo->NumberE820Entries * sizeof(E820_ENTRY);

    //
    // Restore saved OpROMs and EBDAs associated with them
    //
    for (rom=gSavedOprom-1; rom->Address; rom--) {
        pBS->CopyMem (
            rom->Address,
            rom->Data,
            ((LEGACY_OPT_ROM_HEADER*)rom->Data)->Size512 * 0x200
        );

        if (rom->rtDataAddr) {
            // Adjust rt data address according to the current EBDA location
            if (rom->isEbda) {
                rom->rtDataAddr = (UINT8*)(UINTN)((((UINT32)*(UINT16*)0x40e) << 4) + rom->ebdaOffset);
            }

            pBS->CopyMem (
                rom->rtDataAddr,
                rom->rtData,
                rom->rtDataSize
            );
        }
    }

    //
    // Reset number of ATA drives to let CSM16 PrepareToBoot function connect the drives
    //
    *(UINT8*)0x475 = 0;
    //
    // Make PrepareToBoot 16 bit call
    //
    pBS->SetMem(&RegSet, sizeof (EFI_IA32_REGISTER_SET), 0);
    RegSet.X.AX = Compatibility16PrepareToBoot;
    RegSet.X.ES = EFI_SEGMENT (&CoreBiosInfo->Thunk->Csm16BootTable);
    RegSet.X.BX = EFI_OFFSET (&CoreBiosInfo->Thunk->Csm16BootTable);

    FarCall86 (&CoreBiosInfo->iBios,
                CoreBiosInfo->Csm16EntrySeg,
                CoreBiosInfo->Csm16EntryOfs,
                &RegSet,
                NULL,
                0);

    Status = LockShadow(
            LockUnlockAddr,
            LockUnlockSize
    );
    ASSERT_EFI_ERROR(Status);

    if (RegSet.X.AX) Status = (RegSet.X.AX & 0x7FFF) | EFI_ERROR_BIT;

    if (EFI_ERROR(Status)) return Status;

    gIsBootPrepared = TRUE;

    *BbsCount = CoreBiosInfo->BbsEntriesNo;
    *BbsTable = CoreBiosInfo->BbsTable;

    //
    // Reinitialize keyboard buffer tail and head
    //
    *(UINT16*)0x41A = 0x1E;
    *(UINT16*)0x41C = 0x1E;

    return EFI_SUCCESS;
}


//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Name:        LegacyBoot
//
// Description:
//  Boots a traditional OS
//
// Input:
//  This            Indicates the EFI_LEGACY_BIOS_PROTOCOL instance.
//  BootOption      The EFI device path from BootXXXX variable.
//  LoadOptionSize  Size of LoadOption.
//  LoadOption      The load option from BootXXXX variable.
//
// Output:
//  EFI_DEVICE_ERROR    Failed to boot from any legacy boot device
//
// Notes:
//  This function normally never returns. It will either boot the OS or
//  reset the system if memory has been "corrupted" by loading a boot sector
//  and passing control to it.
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS
LegacyBoot (
  IN EFI_LEGACY_BIOS_PROTOCOL         *This,
  IN  BBS_BBS_DEVICE_PATH             *BootOption,
  IN  UINT32                          LoadOptionsSize,
  IN  VOID                            *LoadOptions
)
{
    UINT16      BbsCount;
    BBS_TABLE   *BbsTable;
    EFI_EVENT   eLegacyBoot;
    EFI_STATUS  Status;
    EFI_IA32_REGISTER_SET   RegSet;
    UINT32      *ivt = (UINT32*)0;
    UINT16      i;
    EFI_TIME    boottime;
    UINT32      localtime;
    BDA_DATA    *bda;
    UINTN       Count;
    EFI_HANDLE  *Buffer;
    EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL *TxtOut;
	UINTN       Size;
    MEDIA_FW_VOL_FILEPATH_DEVICE_PATH   *MediaDevicePath=(MEDIA_FW_VOL_FILEPATH_DEVICE_PATH *)BootOption;
    EFI_TIMER_ARCH_PROTOCOL *Timer;
    UINT8       Data;
    static EFI_GUID EfiGlobalVariableGuid = EFI_GLOBAL_VARIABLE;
    EFI_EVENT   Event;

    PROGRESS_CODE(DXE_LEGACY_BOOT);

	//
	// Check if Secure Boot is on; if so, return EFI_SECURITY_VIOLATION
	//
    Size = sizeof(UINT8);
    Status = pRS->GetVariable(EFI_SECURE_BOOT_NAME, &EfiGlobalVariableGuid, NULL, &Size, &Data);
    if(!EFI_ERROR(Status) && (Data != 0)) {
        return EFI_SECURITY_VIOLATION;     // no CSM in secure boot mode
    }

    //
    // Clear all screens
    //
    Status = pBS->LocateHandleBuffer(ByProtocol,
                    &gEfiSimpleTextOutProtocolGuid,
                    NULL,
                    &Count,
                    &Buffer);

    if (!EFI_ERROR (Status)) {
        for (i = 0; i < Count; i++) {
            Status = pBS->HandleProtocol (Buffer[i], &gEfiSimpleTextOutProtocolGuid, &TxtOut);
            ASSERT_EFI_ERROR (Status);
            TxtOut->ClearScreen(TxtOut);
        }
    }

    bda = (BDA_DATA*)((UINTN) 0x400);
    if (bda->mode_of_vdo != 3) {
        RegSet.X.AX = 3;
        Status = CoreBiosInfo->iBios.Int86 (&CoreBiosInfo->iBios, 0x10, &RegSet);
        ASSERT_EFI_ERROR(Status);
    }

    //
    // Update local time data in BDA (dword at 40:6C and byte at 40:70)
    //
    pRS->GetTime (&boottime, NULL);
    localtime = (boottime.Hour * 3600 + boottime.Minute * 60 + boottime.Second) + 1;

    localtime = (localtime * 182)/10;   // Count number of timer ticks.

    bda->timer_count = localtime;
    bda->timer_count_rolled = 0;
    for (i=0; i<4; i++) bda->print_time_max[i] = 0x14;  // Maximum time for printing
    for (i=0; i<4; i++) bda->rs_232_time_max[i] = 0x1;  // Maximum transmission time for COM ports

    UpdateCmos();       // This function unconditionally enables NMI
    EnableDisableNmi();

    //
    // Restore saved interrupts
    //
    for(i = 0; gIrqSav[i].irq_adr; i++) {
        ivt[gIrqSav[i].irq_num] = gIrqSav[i].irq_adr;
    }

    Status = ShadowAllLegacyOproms(This);   // Launch remaining OpROMs
    ASSERT_EFI_ERROR(Status);

    // For the 1st boot store BBS table, else update the entries
    if (gOriginalBbsTable == NULL){
        Status = pBS->AllocatePool(EfiBootServicesData, (sizeof(BBS_TABLE))*CoreBiosInfo->BbsEntriesNo,
                               &gOriginalBbsTable);
        ASSERT_EFI_ERROR(Status);
        pBS->CopyMem(gOriginalBbsTable, CoreBiosInfo->BbsTable, (sizeof(BBS_TABLE))*CoreBiosInfo->BbsEntriesNo);
    }
    else
    {
        // find the lowest priority and update failed-to-boot entries with even lower priority values
        UINT16 LowestPriority = 0;

        for (i = 0; i < CoreBiosInfo->BbsEntriesNo; i++)
        {
            if (CoreBiosInfo->BbsTable[i].BootPriority > LowestPriority
                && CoreBiosInfo->BbsTable[i].BootPriority <= BBS_LOWEST_ACTIVE_PRIORITY)
            {
                LowestPriority = CoreBiosInfo->BbsTable[i].BootPriority;
            }
        }
        // the failed entries have the priority of BBS_UNPRIORITIZED_ENTRY (set by TSE)
        for (i = 0; i < CoreBiosInfo->BbsEntriesNo; i++)
        {
            if (CoreBiosInfo->BbsTable[i].BootPriority == BBS_UNPRIORITIZED_ENTRY
                && gOriginalBbsTable[i].BootPriority != BBS_UNPRIORITIZED_ENTRY)
            {
                CoreBiosInfo->BbsTable[i].BootPriority = ++LowestPriority; // bump the entry all the way back
                ASSERT(LowestPriority < BBS_LOWEST_ACTIVE_PRIORITY);
            }
        }
    }

    DumpBbsTable(0);

    Status = EnablePciDevices(This);
    ASSERT_EFI_ERROR(Status);

// The following call moved to LEGACYREGION.Lock, EIP29087
//    RemoveDecodingForShadow((UINT32)gNextRomAddress);

    Status = pBS->LocateProtocol(&gEfiTimerArchProtocolGuid, NULL, &Timer);
    ASSERT_EFI_ERROR(Status);

    //
    // Signal EFI_EVENT_SIGNAL_LEGACY_BOOT event
    //
    Status = CreateLegacyBootEvent (
        TPL_CALLBACK, NULL, NULL, &eLegacyBoot
    );

    if (Status == EFI_SUCCESS) {
        Status = pBS->SignalEvent(eLegacyBoot);
        ASSERT_EFI_ERROR(Status);
        pBS->CloseEvent(eLegacyBoot);
    }

    Timer->SetTimerPeriod (Timer, 0);   // Kill timer, mask its interrupt

    Status = CoreBiosInfo->iBiosPlatform->PrepareToBoot(
        CoreBiosInfo->iBiosPlatform,
        BootOption,
        CoreBiosInfo->BbsTable,
        LoadOptionsSize,
        LoadOptions,
        &CoreBiosInfo->Thunk->Csm16BootTable
    );

    Status = PrepareToBoot(This, &BbsCount, &BbsTable);
    ASSERT_EFI_ERROR(Status);

    HaltApsBeforeBoot();

    SignalAmiLegacyBootEvent();

    //
    // Set NumLock state according to Setup question
    //
	Size = sizeof(SETUP_DATA);
	Status = pRS->GetVariable(L"Setup",&guidSetup, NULL, &Size, &gSetup);
	if (Status==EFI_SUCCESS) {
        i = (gSetup.Numlock)? 2 : 0;    
    } else {
        i = 2;   // NumLock is on
    }
    //
    // Note: GetVariable call could have been done once in the entry point,
    //       but in this case we will have to require reset on Setup.Numlock
    //       change.
    //
    UpdateKeyboardLedStatus(This, (UINT8)i);
    						//(EIP52733+)>
    DisconnectSerialIO();
    CoreBiosInfo->i8259->GetMask(CoreBiosInfo->i8259, NULL, NULL, &gProtectedIrqMask, NULL);      // Save current Mask
    						//<(EIP52733+)

    //
    // Restore redirected HW IRQ0..7
    //
    						//(EIP52733+)>
    gOldTplValue = pBS->RaiseTPL(TPL_HIGH_LEVEL);  // disable interrupts
    						//<(EIP52733+)
    //
    // Note: after this point TPL stays HIGH
    //
    for(i = 0; i < 8; i++) {
        ivt[irq0 + i] = HwIrqRedirSav[i];
    }

    //
    // Program legacy vector base in 8259
    //
    CoreBiosInfo->i8259->SetVectorBase (CoreBiosInfo->i8259, 8, 0x70);

    if(guidcmp(&MediaDevicePath->NameGuid, &WinceGuid) == 0) {
        return EFI_NOT_FOUND;   // WinCE boot request, called from WinCE module
    }  
    //
    // Pass control to CSM16 to execute Int19
    //
    pBS->SetMem(&RegSet, sizeof (EFI_IA32_REGISTER_SET), 0);
    RegSet.X.AX = Compatibility16Boot;

    FarCall86 (&CoreBiosInfo->iBios,
                CoreBiosInfo->Csm16EntrySeg,
                CoreBiosInfo->Csm16EntryOfs,
                &RegSet,
                NULL,
                0);
                				//(EIP52733+)>
    pBS->RaiseTPL(TPL_HIGH_LEVEL);              // disable interrupts
    CoreBiosInfo->i8259->SetVectorBase(CoreBiosInfo->i8259, MASTER_INTERRUPT_BASE, SLAVE_INTERRUPT_BASE);
    CoreBiosInfo->i8259->SetMask(CoreBiosInfo->i8259, NULL , NULL, &gProtectedIrqMask, NULL);

    pBS->RestoreTPL(gOldTplValue);
    Timer->SetTimerPeriod (Timer, DEFAULT_TICK_DURATION);
 
    Status = pBS->CreateEventEx(
                 EVT_NOTIFY_SIGNAL,
                 TPL_CALLBACK,
                 DummyFunction,
                 NULL,
                 &gLTEBGuid,
                 &Event);

    pBS->SignalEvent(Event);
    pBS->CloseEvent(Event);
    
    
    if (gVgaHandle != NULL){
        pBS->DisconnectController(gVgaHandle, NULL, NULL);
        pBS->ConnectController(gVgaHandle, NULL, NULL, TRUE);
    }
    ConnectSerialIO();

    return EFI_SUCCESS;

						//<(EIP52733+)
}


//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Name:        InitializePortingHooks
//
// Description:
//  Initialize the data areas for Chipset/OEM 16 bit and 32 bit routines and
//  interrupt handlers.
//
// Input:
//  BIOS_INFO *CoreBiosInfo
//
// Output:
//  EFI_STATUS Success of failure of the operation.
//
// Notes:
//  At the point of calling CSM16 is loaded, no CSM16 function is executed.
//  E0000..FFFFF area is unlocked.
//
// Referrals:
//  BIOS_INFO
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS
InitializePortingHooks (
    BIOS_INFO *CoreBiosInfo
)
{
    EFI_COMPATIBILITY16_TABLE   *Csm16;

    EFI_IA32_REGISTER_SET   Registers;
    EFI_STATUS              Status;
    VOID                    *OemData;
    UINTN                   OemDataSize;

    Csm16 = CoreBiosInfo->Csm16Header;

    //
    // Read OEM code/data image from the FW. The following steps are to be taken:
    // 1) Copy it into E000/F000 area
    // 2) Initialize the appropriate pointers in CSM16: Csm16->OemIntSegment/Offset,
    //    Csm16->Oem32Segment/Offset, Csm16->Oem16Segment/Offset.
    //
    Status = FindEmbeddedRom(OEM_MODULEID, CSM16_VENDORID, CSM16_DEVICEID,
                        &OemData, &OemDataSize);

    if (EFI_ERROR(Status)) return Status;

    pBS->SetMem(&Registers, sizeof (EFI_IA32_REGISTER_SET), 0);
    Registers.X.AX = Compatibility16GetTableAddress;
    Registers.X.BX = E0000_BIT; // Allocate from 0xE0000 64 KB block
    Registers.X.CX = (UINT32)OemDataSize;
    Registers.X.DX = 1;         // Alignment

    FarCall86 (&CoreBiosInfo->iBios,
            CoreBiosInfo->Csm16EntrySeg, CoreBiosInfo->Csm16EntryOfs,
            &Registers, 0, 0);
    Status = (Registers.X.AX)? ((Registers.X.AX & 0x7FFF) | EFI_ERROR_BIT) : EFI_SUCCESS;
    ASSERT_EFI_ERROR(Status);
    if (EFI_ERROR(Status)) return Status;

    gCsm16IntStart = (OEMINT_FUNC*)(UINTN)(((UINTN)Registers.X.DS << 4) + Registers.X.BX);

    //
    // Copy the data to E000/F000
    //
    pBS->CopyMem((VOID*)gCsm16IntStart, OemData, OemDataSize);

    //
    // Initialize OEM data and update CSM16 data pointers
    //
    gCsm16FuncAddress = InitializeOemInt(&Csm16->OemIntSegment);
    gCsm32DataAddress = InitializeOem16(&Csm16->Oem16Segment);
//  InitializeOemData(&Csm16->Oem32Segment);

    return EFI_SUCCESS;
}


//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Name:        InitializeOemInt
//
// Description:
//  Initialize OEM interrupts and update CSM16 OEM int pointer
//
// Input:
//  Csm16TableStart     The address of the beginning of OEM table
//  Csm16Address        The address of the beginning of OEM interrupt table handler(s)
//  Csm16InitSegPtr     The address of the field with OEM interrupt pointer that is
//                      passed to CSM16.
//
// Output:
//  Pointer to the next type of OEM code/data
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

OEM16_FUNC*
InitializeOemInt(
    IN OUT UINT16   *Csm16InitSegPtr
)
{
    OEMINT_FUNC *IntFuncTable;

    UINT32  *ivt = (UINT32*)0;
    UINT32  *IntSavAddress;

    UINT16 Seg16 = (UINT16)((UINTN)gCsm16IntStart >> 4);

    //
    // Update Csm16 data pointer
    //
    *Csm16InitSegPtr = Seg16;
    *(Csm16InitSegPtr+1) = 0;

    //
    // Initialize interrupt handlers with the interrupt original locations
    //
    for (IntFuncTable=gCsm16IntStart;IntFuncTable->interrupt!=0xFFFF;IntFuncTable++) {
        IntSavAddress = (UINT32*)((UINTN)gCsm16IntStart+IntFuncTable->funcoffset-sizeof(UINT32));
        // interrupt vector handshake
        *IntSavAddress = ivt[IntFuncTable->interrupt];
        ivt[IntFuncTable->interrupt] = ((UINT32)Seg16 << 16) + IntFuncTable->funcoffset;
    }

    //
    // Return the pointer to the OEM16 function table that immediately follows OEMINT table
    //
    return (OEM16_FUNC*)(++IntFuncTable);
}


//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Name:        InitializeOem16
//
// Description:
//  Initialize OEM interrupts and update CSM16 OEM int pointer
//
// Input:
//  Csm16TableStart     The address of the beginning of OEM table
//  Csm16Address        The address of the beginning of OEM16 data/code
//  Csm16InitSegPtr     The address of the field with OEM16 pointer
//                      that is passed to CSM16.
//
// Output:
//  Pointer to the next type of OEM code/data
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

UINTN
InitializeOem16(
    IN OUT UINT16   *Csm16InitSegPtr
)
{
    OEM16_FUNC  *Oem16FuncTable;

    UINT16 Seg16 = (UINT16)(((UINTN)gCsm16FuncAddress >> 4) & 0xf000);
    UINT16 Ofs16 = (UINT16)((UINTN)gCsm16FuncAddress & 0xffff);

    //
    // Update Csm16 data pointer
    //
    *Csm16InitSegPtr = Seg16;
    *(Csm16InitSegPtr+1) = Ofs16;

    //
    // Find the offset of the first OEM16 routine, use it to update the
    // entry points of each CSM16 routine
    //
    Ofs16 = 0xffff;
    for (Oem16FuncTable = gCsm16FuncAddress;
            Oem16FuncTable->funcID != 0xffff; Oem16FuncTable++) {
        if (Ofs16 > *(UINT16*)&Oem16FuncTable->funcOffset) {
            Ofs16 = *(UINT16*)&Oem16FuncTable->funcOffset;
        }
    }

    for (Oem16FuncTable = gCsm16FuncAddress;
            Oem16FuncTable->funcID != 0xffff; Oem16FuncTable++) {
        *(UINT16*)&Oem16FuncTable->funcOffset -= Ofs16;
    }

    //
    // Update the OEM16 segment to SEG so that the 1st routine has an
    // entry point at SEG:0. Store this SEG value at gCsm16FuncAddress-2
    // This will make all offsets in OEM16_CSEG valid.
    //
    *(UINT16*)((UINTN)gCsm16FuncAddress-2) = (UINT16)(((UINTN)gCsm16IntStart + Ofs16) >> 4);

    //
    // Return the pointer to the OEM16 function table that immediately follows OEMINT table
    //
    return (UINTN)(++Oem16FuncTable);
}


//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Name:        Get16BitFuncAddress
//
// Description:
//  LegacyBiosExt API, returns the entry point of 16-bit function which was
//  added using "CsmOem16Functions" eLink
//
// Input:
//  id          function ID
//
// Output:
//  EFI_SUCCESS if found, Addr is updated with 32-bit pointer to the function
//  EFI_NOT_FOUND if function with the requested ID is not found
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS
Get16BitFuncAddress (
    IN UINT16 id,
    OUT UINT32 *Addr
)
{
    OEM16_FUNC  *Oem16FuncTable;
    UINT16      Seg16;

    if (gCsm16FuncAddress == NULL) return EFI_NOT_FOUND;

    Oem16FuncTable = gCsm16FuncAddress;
    Seg16 = *(UINT16*)((UINTN)gCsm16FuncAddress-2);

    for (; Oem16FuncTable->funcID != 0xffff; Oem16FuncTable++) {
        if (Oem16FuncTable->funcID == id) {
            *Addr = ((UINT32)Seg16<<4)+(UINT32)Oem16FuncTable->funcOffset;
            return EFI_SUCCESS;
        }
    }

    return EFI_NOT_FOUND;
}


//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Name:        HaltApsBeforeBoot
//
// Description:
//  This call is halting APs before giving control to Legacy OS.
//
// Input:
//  None
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

VOID
HaltApsBeforeBoot()
{
    UINTN NumberOfCPUs;
    EFI_STATUS Status;
    EFI_MP_SERVICES_PROTOCOL *MpServices;

    // Execute on running APs
    Status = pBS->LocateProtocol (&gEfiMpServicesProtocolGuid, NULL, &MpServices);
    ASSERT_EFI_ERROR(Status);
    if (EFI_ERROR(Status)) return;

// Use the #else path for the CPU modules compliant with PI1.1
#if PI_SPECIFICATION_VERSION < 0x0001000A || BACKWARD_COMPATIBLE_MODE && defined(NO_PI_MP_SERVICES_SUPPORT)
    MpServices->GetGeneralMPInfo(MpServices,
        &NumberOfCPUs, NULL, NULL, NULL, NULL); 
#else
{
    UINTN NumberOfEnabledProcessors;

    MpServices->GetNumberOfProcessors(MpServices,
        &NumberOfCPUs, &NumberOfEnabledProcessors);
}
#endif

    NumberOfCPUs--;  //Exclude BSP
    while(NumberOfCPUs) {
        MpServices->EnableDisableAP(
            MpServices,
            NumberOfCPUs,
            FALSE,
            NULL);
        NumberOfCPUs--;
    }	
}


VOID DumpBbsTable(UINT32 CaseNumber)
{
#ifdef EFI_DEBUG
    BBS_TABLE   *BbsEntry;
    EFI_HANDLE  Handle;
    EFI_GUID    DevicePathProtocolGuid = EFI_DEVICE_PATH_PROTOCOL_GUID;
    EFI_DEVICE_PATH_PROTOCOL    *dpp;
    UINT32      i;
    EFI_STATUS  Status;

    TRACE((-1,"_____BBS_TABLE(%x)_____\n", CaseNumber));
    for (BbsEntry = CoreBiosInfo->BbsTable, i = 0; i < MAX_BBS_ENTRIES_NO; i++, BbsEntry++) {
        if (BbsEntry->BootPriority == BBS_IGNORE_ENTRY) continue;
        TRACE((-1, "#%02d: %d %02X/%02X/%02X %x %x %x %04X handle: %x %x, %s\n", i, BbsEntry->BootPriority,
                    (BbsEntry->Bus==0xffffffff)? 0xff : BbsEntry->Bus,
                    (BbsEntry->Device==0xffffffff)? 0xff : BbsEntry->Device,
                    (BbsEntry->Function==0xffffffff)? 0xff : BbsEntry->Function,
                    BbsEntry->Class, BbsEntry->SubClass,
                    BbsEntry->DeviceType, BbsEntry->StatusFlags,
                    BbsEntry->IBV1, BbsEntry->IBV2,
                    (UINTN)((UINTN)BbsEntry->DescStringSegment<<4) + BbsEntry->DescStringOffset
        ));
        Handle = *(VOID**)(&BbsEntry->IBV1);
        if (Handle == 0) continue;
        Status = pBS->HandleProtocol(Handle, &DevicePathProtocolGuid, &dpp);
        TRACE((-1, "Handle=%x, HandleProtocol status: %r, DevicePath: %x\n", Handle, Status, dpp));
    }
#endif
}

//**********************************************************************
//**********************************************************************
//**                                                                  **
//**        (C)Copyright 1985-2013, American Megatrends, Inc.         **
//**                                                                  **
//**                       All Rights Reserved.                       **
//**                                                                  **
//**           5555 Oakbrook Pkwy, Suite 200, Norcross, GA 30093      **
//**                                                                  **
//**                       Phone: (770)-246-8600                      **
//**                                                                  **
//**********************************************************************
//**********************************************************************
