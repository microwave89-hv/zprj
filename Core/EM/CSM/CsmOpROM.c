//**********************************************************************
//**********************************************************************
//**                                                                  **
//**        (C)Copyright 1985-2010, American Megatrends, Inc.         **
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
// $Header: /Alaska/SOURCE/Modules/CSM/Generic/Core/CsmOpROM.c 180   9/14/15 10:15a Olegi $
//
// $Revision: 180 $
//
// $Date: 9/14/15 10:15a $
//
//**********************************************************************
// Revision History
// ----------------
// $Log: /Alaska/SOURCE/Modules/CSM/Generic/Core/CsmOpROM.c $
// 
// 180   9/14/15 10:15a Olegi
// [TAG]  		EIP237972
// [Category]  	Bug Fix
// [Symptom]  	Aptio4 CSM: default int10 installation may fail
// 
// 179   9/09/15 11:09a Olegi
// [TAG]  		EIP237387
// [Description]  	Aptio4 CSM: Add PciIo check to prevent CPU exceptions
// when executing service ROMs
// 
// 178   9/09/15 10:54a Olegi
// [TAG]  		EIP237386
// [Description]  	Aptio4 CSM: ASSERT in headless mode on OptionROM
// execution
// 
// 177   9/09/15 10:47a Olegi
// [TAG]  		EIP237385
// [Description]  	Aptio4 CSM: trapped INT19 may fail
// 
// 176   9/09/15 9:53a Olegi
// [TAG]  		EIP237381
// [Description]  	Aptio 4 CSM: add INT19 TRAP setup question
// 
// 175   9/08/15 2:47p Olegi
// [TAG]  		EIP237205
// [Description]  	Aptio4 CSM: Add Lock/Unlock console calls during Option
// ROMs execution
// 
// 174   8/24/15 3:00p Olegi
// [TAG]  		EIP235037
// [Description]  	Aptio4 CSM: Optimize video mode switching during Option
// ROMs execution
// 
// 173   12/01/14 11:40a Olegi
// correction to the previous check-in
// 
// 172   11/06/14 11:28a Olegi
// [TAG]  		EIP187681
// [Description]  	Aptio4 CSM: Larger than 128KB sized OPROM support /
// checking
// 
// 171   8/06/14 4:24p Fasihm
// [TAG]           EIP180681
// [Category]      Improvement
// [Severity]      Normal
// [Symptom]       Aptio 4 CSM: Clean the setup settings and options.
// [Solution]      INT19 trap setup question removed, cleaned code. 
// [Files]
//         Board\EM\Csm\csm.sd
//         Board\EM\Csm\csm.uni
//         Core\EM\CSM\CsmBsp.c
//         Core\EM\CSM\CsmOpROM.c
// 
// 170   11/20/13 6:03p Olegi
// EIP144132: Extend the checking for VGA controller.
// 
// 169   10/25/13 3:10p Olegi
// [TAG]  		EIP141160
// [Category]  	Improvement
// [Description]  	InstallPciRom has the code that updates the list of
// executed ROMs; the condition used there is not correct.
// 
// 168   6/04/13 12:15p Olegi
// [TAG]  		EIP125092
// [Category]  	Improvement
// [Description]  	CSM does not handle PCI ROM 2.1+3.0 combination
// 
// 167   5/15/13 3:32p Olegi
// [TAG]  		EIP123915
// [Category]  	Improvement
// [Description]  	BBS table update in CSM should be atomic operation
// [Files]  		CsmOpROM.c
// CsmLib.c
// 
// 166   4/01/13 8:46a Olegi
// [TAG]  		EIP111209
// [Category]  	Improvement
// [Description]  	ISA boot devices controlled by the Option ROM are added
// to the boot list.
// [Files]  		CsmOprom.c
// 
// 165   12/20/12 11:02a Olegi
// 
// 164   10/23/12 4:45p Olegi
// EIP 104052 - Support for generic Option ROMs with PCI3.0 headers
// 
// 163   10/22/12 10:02a Olegi
// [TAG]  		EIP100790
// [Category]  	Improvement
// 
// ConnectSerialIO is moved after Video is reconnected.
// 
// 162   7/23/12 12:05p Olegi
// [TAG]  		EIP92895
// [Category]  	New Feature
// [Description]  	Event-based PreProcessOpRom replacement for AptioV
// 
// 161   6/25/12 3:59p Olegi
// [TAG]  		EIP90257
// [Category]  	Improvement
// [Description]  	In CSM, don't clear allocated memory below 640K - added
// ClearFreeMemory function
// [Files]  		CsmOpROM.c
// CSM.c
// CsmHwInfo.c
// 
// 160   6/15/12 10:39a Olegi
// [TAG]  		EIP83856
// [Description]  	Audio device show can not start under Device Manager
// with UEFI win7
// 
// 159   6/15/12 10:23a Olegi
// [TAG]  		EIP90155
// [Category]  	Improvement
// [Description]  	CSM changes to support OpRomTxt module genericly
// [Files]  		CsmOpROM.c
// CsmBsp.c
// 
// 158   6/13/12 12:56p Olegi
// [TAG]  		EIP91376
// [Category]  	Improvement
// [Description]  	Added the verification of gExecutedRomsPci before PCI
// Option ROM execution.
// Increased the number of maximum PCI Option ROMs to 32.
// [Files]  		CSM.h
// CsmOpROM.c
// 
// 157   4/24/12 6:49p Olegi
// 
// 156   4/24/12 6:40p Olegi
// [TAG]  		EIP86770
// [Category]  	Improvement
// [Description]  	Added ExecuteBcv function.
// 
// 155   2/10/12 10:09a Olegi
// [TAG]  		EIP82449
// [Category]  	Bug Fix
// [Severity]  	Important
// [Symptom]  	During LegacyBoot some EBDA locations might be destroyed
// [RootCause]  	The amount of EBDA allocated by the Option ROM was not
// properly calculated in case Option ROM uses several allocation methods
// at the same time: EBDA and 40-:13.
// [Solution]  	Corrected the calculation of the size of allocated EBDA
// [Files]  		CsmOpROM.c
// 
// 154   12/23/11 2:47p Olegi
// [TAG]  		EIP79228
// [Category]  	Improvement
// [Description]  	Implement CSM_INT19_TRAP_IMMEDIATE_ACTION functionality
// [Files]  		CsmOpROM.c
// CSM.c
// 
// 153   12/13/11 10:58a Matthewh
// 
// 152   12/13/11 10:53a Matthewh
// [TAG]  		EIP77897
// [Category]  	Bug Fix
// [Severity]  	Normal
// [Symptom]  	Using More then one ISA PnP Card with an Option ROM that have
// overlapping Memory ranges only one Option ROM will be run. Address range
// may be skipped if the address is already aligned properly before "AND"ing
// with the Aln variable and adding the alignment.
// [RootCause]  The global variable gNextRomAddress is not moved to the next 
// available locatation untill the InstallIsaRom function is run but by then
// both Option Roms have already been assigned to the same address.  There is
// no check to see if the address is already aligned properly before the 
// alignment calculation is applied.
// [Solution]  	Change GetShadowRamAddress function to update gNextRomAddress
// and remove the update of gNextRomAddress from InstallIsaRom. Update 
// GetShadowRamAddress function to take into account that the address may 
// already be aligned and no need to add the alignment.
// [Files]  		CsmOpROM.c

// 
// 151   11/11/11 6:09p Olegi
// [TAG]  		EIP74894
// [Category]  	Improvement
// [Description]  	In some cases OEM logo partially remains on the screen
// during EFI shell/boot popup menu.
// [Files]  		csmoprom.c
// 
// 150   10/31/11 12:38p Olegi
// [TAG]  		EIP72804
// [Category]  	Improvement
// [Description]  	Promise FastTrak 2650 Option ROM hangs the system.
// [Files]  		CsmOprom.c
// 
// 149   10/12/11 2:56p Olegi
// [TAG]  		EIP72177
// [Category]  	Improvement
// [Description]  	CheckPmmTable function suppressed.
// [Files]  		CsmOpROM.c
// CSM.c
// CsmBsp.c
// CSM.SDL
// 
// 148   9/30/11 12:46p Olegi
// Undone all changes related to EIP70382 (check-in 144, 146, 147. INT19
// trapping modifications are added to CSM16.
// 
// 147   9/29/11 10:52a Olegi
// Continuation of check-in #144 related to EIP70382; clearing keyboard
// status is moved to FarCall86.
// 
// 146   9/29/11 9:45a Olegi
// Continuation of check-in #144 related to EIP70382; adding a check for
// Setup.I19Trap.
// 
// 145   9/28/11 10:45a Olegi
// [TAG]  		EIP71227
// [Category]  	Improvement
// [Description]  	Added out-of-resource reporting during memory
// allocation failure.
// [Files]  		csmoprom.c
// 
// 144   9/27/11 6:26p Olegi
// [TAG]  		EIP70382
// [Category]  	Bug Fix
// [Severity]  	Important
// [Symptom]  	Keyboard is not functional in some Option ROM setup utility
// [RootCause]  	When Option ROM hot key combination has Ctrl as a part of
// it (Ctrl-H), then the state of Ctrl key might remain in 40:17 after
// control comes back to EFI.
// If after this another 16-bit code is executed and requires keyboard
// handling, having improper settings in 40:17 affect the key reporting
// data.
// [Solution]  	Make sure the booting process go through INT19, and Option
// ROM setup is not invoked earlier during PrepareToBoot.
// INT19 code has the initialization of 40:17 that resolves the issue.
// [Files]  		CsmOpROM.c
// 
// 143   8/25/11 10:06a Olegi
// Change in CheckPmmTable: skip the low memory PMM entries.
// 
// 142   8/22/11 9:59a Olegi
// [TAG]  		EIP66613
// [Category]  	Improvement
// [Description]  	Dynamic PMM size.
// [Files]  		CsmOprom.c
// 
// 141   8/15/11 5:52p Olegi
// Changed the type of the counter variable in CheckPmmTable function from
// UINT8 to UINTN.
// 
// 140   8/11/11 4:23p Olegi
// [TAG]  		EIP66636
// [Category]  	Improvement
// [Description]  	Validation of legacy Option ROM modified: some Option
// ROMs are not properly report last image indicator (Adaptec SCSI BIOS
// v4.31.4 (c) 2007).
// [Files]  		CsmOpROM.c
// 
// 139   6/21/11 2:03p Olegi
// 1. EIP62285: Immediate INT19 execution call added
// 2. VGA enabling properly done after VGA driver is disconnected
// 3. Multiple legacy Option ROMs handling corrected to return the 1st
// legacy
// 
// 138   6/15/11 10:43a Olegi
// [TAG]  		EIP61986
// [Category]  	Bug Fix
// [Severity]  	Normal
// [Symptom]  	Post Screen corruption occurs while loading multiple Option
// ROMS.
// [RootCause]  	There are cases when video get reconnected outside CSM,
// in between Option ROM execution. That gets VGA disconnect/connect logic
// out of hand.
// [Solution]  	Added the LegacyVgaStartCounter to keep the sync between
// disconnect/connect video, so that setting CSM_DEFAULT_VMODE_SWITCHING
// to 1 will work correctly.
// [Files]  		CsmOpROM.c
// 
// 137   6/10/11 5:37p Olegi
// [TAG]  		EIP59263
// [Category]  	New Feature
// [Description]  	High memory PMM area made dynamic.
// [Files]  		CSM.h
// CsmOpROM.c
// CSM.c
// CsmBsp.c
// csm.sdl
// 
// 136   5/20/11 11:27a Olegi
// [TAG]  		EIP60317
// [Category]  	Improvement
// [Description]  	Do not enable PCI siblings for VGA; if multiple VGA is
// enabled at the same time, OS might have a problem.
// [Files]  		CsmOprom.c
// 
// 135   3/22/11 1:52p Olegi
// [TAG]  		EIP54935
// [Category]  	Improvement
// [Description]  	Added checking for EBDA deallocation done by the Option
// ROM.
// [Files]  		CsmOprom.c
// 
// 134   3/18/11 10:02a Olegi
// [TAG]  		EIP56215
// [Category]  	Improvement
// [Description]  	Added $PnP checksum validation.
// [Files]  		CsmOprom.c
// 
// 133   3/15/11 3:54p Olegi
// Changes from #127 are restored.
// 
// 132   3/14/11 10:00a Olegi
// [TAG]  		EIP54942
// [Category]  	New Feature
// [Description]  	CLP support implementation
// [Files]  		CsmOprom.c LegacyBiosExt.h
// 
// 131   3/10/11 5:38a Rajeshms
// [TAG] - EIP 39307
// [Category]- BUG FIX
// [Severity]- Normal
// [Symptom] - Enter DOS no screen when legacy serial redirection enable
// with option rom message display option is set to " Keep current" in
// setup.
// [RootCause] - Actual INT 10h handler was not replaced after dispatching
// option rom. Legacy console redirection driver INT10h was replaced
// instead of actual handler when option rom message display option was
// set to " Keep current".
// [Solution] - Legacy Console redirection is disabled after its handler
// is replaced in INT 10h place by the dummy handler so that actual INT10h
// handler is replaced by Legacy Console redirection driver. To Support
// redirection for ISA oprom's , enable and disable of legacy console
// redirection has been moved to CsmOpRom.c from OemDxe.c.
// [Files] - CsmOpRom.c, OemDxe.c
// 
// 130   3/08/11 2:15p Olegi
// [TAG]  		EIP55344
// [Category]  	Improvement
// [Description]  	In some cases screen mode is not properly set in
// ConsoleControl after Option ROM execution.
// [Files]  		CsmOprom.c
// 
// 129   3/08/11 12:44p Olegi
// [TAG]  		EIP55496
// [Category]  	Improvement
// [Description]  	Added ebdaOffset field to SAVED_PCI_ROM structure to
// ensure the correct EBDA saving/restoration.
// [Files]  		CSM.h
// CsmOpROM.c
// CSM.c
// 
// 128   2/21/11 1:59p Olegi
// [TAG]  		EIP54262
// [Category]  	Improvement
// [Description]  	Modification CheckPciRom that sometimes does not return
// the proper PCI ROM Status.
// [Files]  		CsmOprom.c
// 
// 127   1/31/11 4:34p Olegi
// [TAG]  		EIP51947
// [Category]  	Improvement
// [Description]  	Change the handling of Option ROMs that trap INT19.
// [Files]  		CsmOpROM.C, AmiLegacy16.bin
// 
// 126   1/19/11 10:18a Olegi
// 
// 124   12/17/10 12:09p Olegi
// Zero FinalLocationSegment field before executing 2.1 (or any other less
// than 3.0) PCI Option ROM.
// 
// 123   12/15/10 1:24p Olegi
// [TAG]  		EIP47379
// [Category]  	Bug Fix
// [RootCause]  	For multiple images in the Option ROM, if the 1st image
// in not IA32 type, the IA32 image will not be found.
// [Solution]  	Modified IsValidLegacyPciOpROM routine, now it does not
// break on the non-IA32 image.
// [Files]  		CsmOpROM.c
// 
// 122   12/14/10 11:44a Olegi
// [TAG]  		EIP48212
// [Category]  	Improvement
// [Description]  	The default implementation of CheckEnablePciSiblings
// can be improved. It could enable all PCI devices with the same VID/DID
// because most of the Option ROMs expect that.
// [Files]  		CsmOpROM.C
// 
// 121   11/08/10 9:21a Olegi
// Modified CsmInstallRom function to use correct PciIo.
// 
// 120   10/29/10 11:39a Olegi
// [TAG]  		EIP47186
// [Category]  	Bug Fix
// [RootCause]  	FindAnyVga returns EFI_SUCCESS in case of headless
// system.
// [Solution]  	Correct the logic in FindAnyVga.
// [Files]  		CsmOprom.c
// 
// 119   10/21/10 4:34p Olegi
// [TAG]  		EIP46470
// [Category]  	Bug Fix
// [Severity]  	Important
// [Symptom]  	VGA enable bit is being set in the upstream PCI bridge
// control register for a non-VGA device that uses an option ROM
// [RootCause]  	ShadowAllLegacyOproms was enabling EFI_VGA_DEVICE_ENABLE
// attribute before the Option ROM execution; that was done for all
// devices, VGA or not.
// [Solution]  	Move enabling EFI_VGA_DEVICE_ENABLE attribute inside
// InstallPciRom, do it for VGA controllers only
// [Files]  		CsmOprom.c
// 
// 118   8/17/10 3:15p Olegi
// Fixes discovered by Klockwork II engine: EIP37977
// 
// 117   7/29/10 3:16p Olegi
// EIP39768:: Added a call to ConsolControl->SetMode after switching to
// text mode.
// 
// 116   7/21/10 9:30a Olegi
// 
// 115   7/20/10 8:59a Olegi
// EIP40907: Initialize Option ROM size field to 0 before ROM execution
// 
// 114   7/16/10 12:34p Olegi
// - removed GetPciControllerClassCode function, replaced with inline code
// - Connect/DisconnectSerialIO functions are moved to CSMLIB.C
// 
// 113   6/18/10 10:35a Olegi
// Added checking for EFI ROM in IsValidLegacyPciOpROM function.
// 
// 112   5/17/10 4:26p Olegi
// Modified the meaning of the 2nd parameter in GetShadowRamAddress
// function.
// 
// 111   5/14/10 4:13p Olegi
// 
// 110   5/06/10 4:47p Olegi
// 
// 109   4/28/10 11:51a Olegi
// Added InstallIsaRom funtion.
// 
// 108   4/27/10 12:19p Olegi
// ERROR_CODE is changed to DEVICE_ERROR_CODE, EIP#37648
// 
// 
// 104   3/02/10 5:11p Olegi
// Changed the parameters for Pre/PostProcessOpROM function. EIP34085.
// 
// 103   2/17/10 4:06p Olegi
// Change in InstallPciRom: if during Option ROM execution there is a
// change in the BBS table, it was not processed correctly. EIP35247.
// 
// 102   1/12/10 11:46a Olegi
// Copyright message updated.
// 
// 101   12/28/09 8:05a Olegi
// Changed the sequence of updating INT10 vector with the dummy and
// calling PostprocessOpRom function. EIP#32832
// 
// 100   12/21/09 3:03p Olegi
// 
// 99    12/08/09 5:07p Olegi
// EIP#15138::Implementation of CheckEnablePciSiblings
// 
// 98    11/02/09 9:32a Olegi
// EIP#29425 Added platform function to get the ROMs from FV, since the
// default method do not always satisfy OEM requirements.
// 
// 97    8/07/09 2:35p Rameshr
// SD boot support Added.
// 
// 96    8/05/09 5:54p Olegi
// - Added check for runtime size being FF
// - Added check for BCV and BEV both being 0
// - Change related to EIP#24327
// 
// 95    6/15/09 5:50p Olegi
// Disconnect/Reconnect serial IO devices while executing OpROMs.
// EIP#20254.
// 
// 94    2/21/09 3:47p Olegi
// FetchBbsDevices is modified to properly handle iSCSI drives. EIP#19614.
// 
// 93    12/31/08 11:41a Olegi
// Change in FetchBbsBootDevices: device class and subclass information is
// taken from PCI configuration space, not from PnP header.
// 
// 92    12/30/08 9:06a Olegi
// Modification in CheckPciRom: added a check for a valid legacy OpROM
// after calling FindEmbeddedRom. EIP#18520.
// 
// 91    12/12/08 3:16p Olegi
// 
// 90    12/09/08 4:06p Olegi
// 
// 89    11/13/08 1:01p Olegi
// 
// 88    11/12/08 4:58p Olegi
// Modified InstallPciRom function that now calls LegacyBiosPlatform to
// get the VGA switching policy override.
// 
// 87    10/10/08 3:34p Olegi
// Added PciRomAlreadyExecuted function.
// 
// 86    9/23/08 2:18p Olegi
// 
// 85    8/18/08 4:53p Olegi
// Modified the rule that verifies the presence of KBC: port 64 is only
// checked for 0xFF, checking for 0x00 is removed.
// 
// 84    6/05/08 12:00p Olegi
// - PreProcessRom execution is moved before checking for VGA OpROM is
// installed.
// - ShadowAllRoms function is modified to execute VGA OpROM if it was not
// executed.
// 
// 83    6/02/08 3:59p Olegi
// Changes in InstallPciRom that address the memory deallocation issues.
// 
// 82    5/21/08 5:00p Olegi
// Bugfix in InstallPciRom: did not free up low memory for 3.0 OpROMs if
// PreprocessOprom returned error.
// 
// 81    5/19/08 12:37p Olegi
// Removed EBDA size limitation.
// 
// 80    5/09/08 3:26p Olegi
// 
// 79    3/12/08 12:56p Olegi
// PROGRESS_CODE((DXE_LEGACY_OPROM_NO_SPACE) is changed to
// ERROR_CODE(DXE_LEGACY_OPROM_NO_SPACE, EFI_ERROR_MAJOR)
// 
// 78    3/12/08 11:59a Olegi
// Added progress status codes.
// 
// 77    12/17/07 4:22p Olegi
// KBC_SUPPORT dependency removed.
// 
// 76    12/04/07 11:07a Olegi
// 
// 75    10/17/07 3:25p Olegi
// Replaced NextRomAddress with gNextRomAddress.
// 
// 74    9/19/07 2:04p Olegi
// Modified UnlockShadow to return the proper LockUnlockSize.
// 
// 73    8/21/07 11:10a Olegi
// Added Intel AHCI Option ROM in the list of PCI 3.0 pretenders
// 
// 72    8/10/07 11:04a Olegi
// VGA handling changed.
// 
// 71    7/27/07 9:33a Olegi
// PreprocessOpRom call is moved before the shadow memory is open.
// 
// 70    7/12/07 5:47p Olegi
// Save BX after dispatching Option ROM to use it later for # of non-BBS
// compliant drives checking.
// 
// 69    7/09/07 6:05p Olegi
// 
// 68    7/09/07 6:04p Olegi
// Change in FetchBbsDevices for nVIDIA MCP55 LAN device in bridge mode.
// 
// 67    6/27/07 3:52p Olegi
// Workaround for OpROMs that use 40:13 to allocate memory, not EBDA.
// 
// 66    6/21/07 10:32a Olegi
// 
// 65    6/18/07 5:45p Olegi
// bugfix in InstallPciRom for non-BBS compliant card that traps int19
// 
// 64    6/08/07 7:57a Olegi
// Fix in FetchBbsBootDevices that properly creates CDROM, not HDD entry
// for BEV mass storage devices.
// 
// 63    6/04/07 12:34p Olegi
// 
// 62    6/02/07 10:23a Olegi
// Shadow size correction.
// 
// 61    30/05/07 12:34p Anandakrishnanl
// Updated LockShadow routine.
// 
// 60    5/29/07 12:20p Olegi
// Added the code to disable Shadow W/R for the unused shadow regions
// after every OpROM execution.
// 
// 59    4/27/07 5:13p Olegi
// CSM.CHM file preparation.
//
// 58    4/12/07 1:30p Olegi
//
// 57    4/10/07 5:17p Olegi
// PreprocessOptionRom call moved closer to the actual option ROM
// execution.
//
// 56    3/29/07 5:38p Olegi
// Temporarily revert the option rom code execution: from
// DispatchOptionRom C function to CSM16 function #5.
//
// 55    3/01/07 9:11a Olegi
//
// 54    1/03/07 12:57p Felixp
// New code introduced in label 4.5.3_CSM.6.32_41 had problems.
// Option ROM handling reverted back to label 4.5.2_CSM.6.32_40
//
// 51    11/14/06 12:37p Olegi
//
// 50    9/22/06 6:13p Olegi
// Introduction of DispatchOptionRom routine.
//
// 49    9/15/06 11:48a Markw
// Removed warning. Added typecast.
//
// 48    8/24/06 6:49p Felixp
// x64 support (warnings/errors fixed)
//
// 47    8/22/06 9:08a Olegi
// "pci30pretender" list is updated with the new Robson card VID/DID.
//
// 46    7/31/06 4:05p Olegi
//
// 45    7/28/06 4:49p Olegi
//
// 43    7/10/06 5:52p Ambikas
//
// 42    5/25/06 2:23p Olegi
//
// 41    5/16/06 1:57p Olegi
//
// 40    5/11/06 12:40p Fredericko
// Make F000 segment writable along with OpROM shadow area for the cases
// where F000 area needs to be updated during DispatchOptionRom call, e.g.
// for non-BBS OpROMs.
// TODO:: remove this call when OpROM handling is moved out of CSM16.
//
// 39    5/01/06 5:06p Olegi
// Added checking for VGA class code in ShadowAllLegacyOproms: enabling
// VGA devices is skipped.
//
// 38    5/01/06 3:23p Olegi
// IsValidLegacyPciOpROM: removed checking for DID/VID as some OpROMs
// might serve several devices.
//
// 37    4/24/06 8:37a Olegi
//
// 36    4/18/06 12:08p Olegi
// Lock/Unlock PAM regions before and after OpROMs.
//
// 35    12/12/05 10:05a Felixp
// Video driver disconnected before switching to text mode
//
// 34    11/29/05 4:17p Olegi
// Get the run-time Option ROM size right after Oprom is executed; the
// value of OpROMSeg:0002 can change later, for example after BCV
// execution (noticed on PCI NetCell RAID SATA card).
//
// 33    10/13/05 6:22p Olegi
// Added HW interrupt handling.
//
// 32    9/30/05 6:27p Olegi
// VC7.1 compatibility issues solved.
//
// 31    9/29/05 5:19p Olegi
// UpdateEbdaMap routine added.
//
// 26    8/02/05 11:26a Olegi
// FetchBbsBootDevices returns if runtime size of OpROM equals 0.
//
// 23    6/22/05 8:35a Olegi
// PCI3.0 support
//
// 22    6/21/05 12:12p Olegi
// LegacyBios and LegacyBiosPlatform are combined into one FFS.
//
// 21    4/21/05 9:06a Olegi
// Added the logic for switching the video mode.
//
// 20    4/19/05 11:12a Olegi
// ShadowAllLegacyOproms function added.
//
// 16    3/04/05 1:52p Mandal
//
//****************************************************************************

//****************************************************************************
//<AMI_FHDR_START>
//
//  Name:           CsmOpROM.c
//  Description:    CSM PCI ROM interface routines
//
//<AMI_FHDR_END>
//****************************************************************************

#include "csm.h"
#include <Protocol/PciIo.h>
#include "token.h"
#include <AmiDxeLib.h>
#include "pci.h"
#include <Protocol/PciIo.h>
#include <Protocol/CsmPlatform.h>
//#include <Protocol/ConsoleControl.h>
#include "setup.h"

#if LEGACYSREDIR_SUPPORT
#include "Protocol\LegacySredir.h"
#endif

#if LEGACYSREDIR_SUPPORT
EFI_LEGACY_SREDIR_PROTOCOL  *gLegacySredir=NULL;
#endif

extern  SETUP_DATA  gSetup;

extern  UINT8 *gNextRomAddress;
extern  EXECUTED_PCI_ROM *gExecutedRomsPci;
//extern  EFI_GUID gPciIoProtocol;
extern  SAVED_PCI_ROM *gSavedOprom;

EFI_HANDLE gVgaHandle = NULL;

BOOLEAN gBbsUpdateInProgress = FALSE;
BOOLEAN gDoNotUpdateBbsTable = FALSE;

EFI_STATUS  PreProcessOpRom(CSM_PLATFORM_PROTOCOL*, EFI_PCI_IO_PROTOCOL*, VOID**);
EFI_STATUS  PostProcessOpRom(CSM_PLATFORM_PROTOCOL*, EFI_PCI_IO_PROTOCOL*, VOID**);
EFI_STATUS  GetOpromVideoSwitchingMode(EFI_PCI_IO_PROTOCOL*, UINT16,UINTN*);

//
// gSetTxtMode
// ff - initial value
// 0 - switching to text mode is needed
// 1 - switching is needed, restoration is not
// 2 - neither switching nor restoration is needed
//
extern UINT8  gSetTxtMode;
extern BOOLEAN gServiceRomsExecuted;

#pragma pack(push, 1)

// EFI Load Option needed for call to LegacyBios->LegacyBoot()
static struct {
    EFI_LOAD_OPTION             LoadOption;
    CHAR16                      Description[10];
    BBS_BBS_DEVICE_PATH         BbsDevicePath;
    EFI_DEVICE_PATH_PROTOCOL    DevicePathEnd;
} DummyLoadOption = {
    {   // EFI_LOAD_OPTION LoadOption
        0,                              // Attributes (UINT32)
        sizeof (BBS_BBS_DEVICE_PATH)
            + sizeof (EFI_DEVICE_PATH_PROTOCOL), // FilePathListLength (UINT16)
    },

    L"DummyLoad",                         // Description

    {   // BbsDevicePath   
        {   // Header
            BBS_DEVICE_PATH,            // Type
            BBS_BBS_DP,                 // Subtype
            sizeof(BBS_BBS_DEVICE_PATH) // Length
        },
        
        BBS_HARDDISK,       // DeviceType
        0,                  // StatusFlags
        0,                  // String
    },

    {   // DevicePathEnd
        END_DEVICE_PATH,                    // Type
        END_ENTIRE_SUBTYPE,                 // SubType
        sizeof(EFI_DEVICE_PATH_PROTOCOL)    // Size
    }
};

#pragma pack(pop)

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Name:        IsValidLegacyPciOpROM
//
// Description: Tests PCI ROM for Legacy PCI ROM compatibility.
//
// Output:
//      TRUE    - Image is valid
//      FALSE   - Image is not valid
//
// Notes:
//  From PCI Fw Specification 3.0, 5.2.1.21. Backward Compatibility of Option ROMs Page # 86.
//    It is also possible to have two separate ROM images for the same PCI device: one for PCI 2.1
//    System Firmware and one for PCI 3.0 compliance. In this case, the PCI 2.1 Option ROM image
//    must appear first in the sequence of images. PCI 3.0 System Firmware will first search for a
//    PCI 3.0 Option ROM image and only use the PCI 2.1 Option ROM image if no PCI 3.0 Option ROM
//    image is found.
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

BOOLEAN
IsValidLegacyPciOpROM (
    IN UINT32 VidDid,       // PCI vendor ID/Device ID
    IN OUT VOID **Image,    // Pointer to the beginning of PCI Option ROM
    IN OUT UINTN *Size      // Input: PciIo->RomSize, Output: OpROM size in bytes
)
{
    PCI_DATA_STRUCTURE *pcir;
    BOOLEAN IsLastImage = FALSE;
    UINT8 *RomStart = *Image;
    UINT32 RomSize = 0;
    BOOLEAN FoundLegacyRom = FALSE;
    UINTN   RomEnd = (UINTN)*Image + *Size;

    for(; !IsLastImage, (UINTN)RomStart < RomEnd; ) {
        //
        // Check for 55AA in the beginning of the image
        //
        if (((LEGACY_OPT_ROM_HEADER*)RomStart)->Signature != 0xaa55) {
            RomStart += 512;
            continue;
        }

        //
        // Validate "PCIR" data
        //
        pcir = (PCI_DATA_STRUCTURE *)(RomStart + *(UINT16*)(RomStart + 0x18));
        if (pcir->Signature != 0x52494350) return FALSE;    // "PCIR"

        IsLastImage = pcir->Indicator & 0x80;

        //   Code Type Description
        //   0x00 Intel IA-32, PC-AT compatible
        //   0x01 Open Firmware standard for PCI
        //   0x02 Hewlett-Packard PA RISC
        //   0x03 EFI Image
        //   0x04-0xFF Reserved
        //
        if (pcir->CodeType == 0) {  // IA-32, PC-AT compatible

            if (pcir->Revision != 3 && FoundLegacyRom)
            {
                // More than one legacy OpROM is present with revision less
                // than 3.0; return the pointer and the size of the previous one.
                // Image and Size are updated when FoundLegacyRom became TRUE.
                // This implements backward compatibility mentioned in the notes
                // above.
                //
                return TRUE;
            }
            
            // Validate the ROM size
            RomSize = pcir->ImageLength << 9;
            if (RomSize <= 0x1fe00)
            {
                UINT32 HeaderRomSize = ((LEGACY_OPT_ROM_HEADER*)RomStart)->Size512 << 9;
                if (HeaderRomSize > RomSize) RomSize = HeaderRomSize;
            }
            else
            {
                TRACE((-1, "CSM: Found unusually large legacy Option ROM (%d Bytes) - loading ", RomSize));
                if (CSM_ALLOW_LARGE_OPROMS == 0)
                {
                    TRACE((-1, "skipped.\n"));
                    RomSize = 0;
                } else TRACE((-1, "allowed.\n"));
            }

            if (RomSize == 0) return FALSE;
    
            *Image = RomStart;
            *Size = (UINTN)RomSize;

            if (pcir->Revision == 3) return TRUE;

            FoundLegacyRom = TRUE;
            RomStart += RomSize;
            continue;
        }

        // Non-legacy ROM; find the size from "PCIR" structure
        RomSize = pcir->ImageLength << 9;
        RomStart += RomSize;
    }

    return FoundLegacyRom;
}


//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Name:        UpdateEbdaMap
//
// Description: This routine is called after every OpROM (BBS or non-BBS) is
//              executed. It updates the locations of EBDA in SAVED_PCI_ROM.ebdaAddr
//              fields after OpROM expands EBDA.
//
// Input:       The size of EBDA created by the OpROM
//
// Output:      None
//
// Notes:       When this function is called SAVED_PCI_ROM structure will not have
//              the current OpROM information inserted; gSavedOprom is pointing to NULL
//              located right after the last valid entry (1st entry is also NULL).
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

VOID
UpdateEbdaMap(UINT32 AddrChange)
{
    SAVED_PCI_ROM *SavedOprom;

    //
    // for every SAVED_PCI_ROM update ebdaAddr
    //
    for (SavedOprom=gSavedOprom-1; SavedOprom->Address; SavedOprom--) {
        if (SavedOprom->isEbda && SavedOprom->rtDataAddr) {
            SavedOprom->rtDataAddr -= AddrChange;
        }
    }
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Name:        SaveOprom
//
// Description: This routine saves Oprom that was just executed to the next
//              gSavedOprom data field; gSavedOprom is incremented.
//
// Input:       Rom address
//              Address and size or runtime data taken during ROM initialization
//
// Notes:       Saving Oprom data is only required for the option ROMs that
//              produce BCV because of early BCV execution; it should not be
//              called for non-BBS compliant OpROMs, for those OpROMs related
//              memory context will be the same til the system is booted.
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

VOID
SaveOprom (
    UINT8   *Rom,
    UINT8   *RtDataAddr,
    UINT32  RtDataSize,
    BOOLEAN IsEbda,
    UINT32  EbdaOffset
)
{
    UINTN  RomSize = ((LEGACY_OPT_ROM_HEADER*)Rom)->Size512 << 9;

    if (RomSize==0) return;
    pBS->AllocatePool(EfiBootServicesData, RomSize, &gSavedOprom->Data);
    pBS->CopyMem(gSavedOprom->Data, Rom, RomSize);
    gSavedOprom->Address = Rom;
    //
    // Save runtime data associated with this ROM
    //
    if (RtDataSize) {
        ASSERT(RtDataAddr); // if size is not zero, address must not be zero
        gSavedOprom->rtDataAddr = RtDataAddr;
        gSavedOprom->rtDataSize = RtDataSize;
        gSavedOprom->isEbda = IsEbda;
        gSavedOprom->ebdaOffset = EbdaOffset;
        pBS->AllocatePool(EfiBootServicesData, RtDataSize, &gSavedOprom->rtData);
        pBS->CopyMem(gSavedOprom->rtData, RtDataAddr, RtDataSize);
    }
    gSavedOprom++;  // Points to zero address/data now.
}


//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Name:        ExecuteBcv
//
// Description:
//   Checks if the platform allows BCV execution; if so, executes BCV and logs
//   the status of HW interrupt changes.
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS
ExecuteBcv (
    BIOS_INFO *BiosInfo,
    UINT8 *PciCfg,
    UINT16 BcvSeg,
    UINT16 BcvOfs,
    UINT8 *Disk
)
{
    EFI_STATUS  Status;
    UINTN       TotalDevices;
    UINT32      *DeviceList;
    UINTN       Counter;
    EFI_IA32_REGISTER_SET RegSet;
    UINT8       Irq;
    UINT32      *Ivt = (UINT32*)0;
    UINT32      IrqHandler = 0;
 
    Status = BiosInfo->iBiosPlatform->GetPlatformInfo(BiosInfo->iBiosPlatform,
                    EfiGetBcvSkipDeviceList,
                    &DeviceList,
                    &TotalDevices,
                    NULL, NULL, 0, 0);

    ASSERT_EFI_ERROR(Status);
    if (EFI_ERROR(Status)) return Status;

    if (TotalDevices > 0 && *DeviceList == 0xffffffff) return EFI_UNSUPPORTED;  // Force to skip BCV execution

    for (Counter = 0; Counter < TotalDevices; Counter++)
    {
        if (*(UINT32*)PciCfg == DeviceList[Counter]) return EFI_UNSUPPORTED;
    }

    // Get the hardware interrupt vector and its handler pointer
    Irq =  *(PciCfg+0x3C);
    if (Irq > 0 && Irq < 0xF)
    {
        Status = BiosInfo->i8259->GetVector (BiosInfo->i8259, Irq, &Irq);   // irq has INT number
        ASSERT_EFI_ERROR(Status);
        IrqHandler = Ivt[Irq];
    }

    //
    // Execute BCV
    //
    pBS->SetMem (&RegSet, sizeof (EFI_IA32_REGISTER_SET), 0);
    RegSet.X.ES = BiosInfo->Csm16Header->PnPInstallationCheckSegment;
    RegSet.X.DI = BiosInfo->Csm16Header->PnPInstallationCheckOffset;

    FarCall86 (&BiosInfo->iBios,
                BcvSeg,
                BcvOfs,
                &RegSet,
                NULL,
                0);
    if (IrqHandler && (Ivt[Irq] != IrqHandler)) {
        *Disk |= 0x40;  // Indicate BCV has hooked HW IRQ
    }

    return EFI_SUCCESS;
}


//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Name:        FetchBbsBootDevices
//
// Description: Check PCI ROM for PnP structures and inserts BCV/BEV devices
//              into BBS table.
//
// Input:       Pointer to PCI ROM.
//
// Output:      Number of devices installed.
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

VOID
FetchBbsBootDevices(
    BIOS_INFO *BiosInfo,
    UINT8 *Rom,
    UINT8 *PciCfgOfs8,
    UINTN Bus, UINTN Dev, UINTN Fun,
    UINT8 *DiskFrom,
    BOOLEAN NewInt18,
    BOOLEAN NewInt19)
{
    UINT16 BbsDevType, bbsDevType;
    PCI_PNP_EXPANSION_HEADER *PnpHdr;
    UINT16 PnpSeg = (UINT16)((UINTN)Rom >> 4);
    UINT16 PnpOfs;
    BBS_TABLE *BbsTable = BiosInfo->BbsTable;
    UINT8 BbsCount;
    UINT32 *ivt = (UINT32*)0;
    UINT8  i, Checksum;

    if (gDoNotUpdateBbsTable) return;

    gBbsUpdateInProgress = TRUE;

    BbsCount = BiosInfo->BbsEntriesNo;

    //
    // Get BBS device type
    //
TRACE((-1, "FetchBbsBootDevices: B%x/D%x/F%x, ClassCode %x\n", Bus, Dev, Fun, *(PciCfgOfs8+0xB)));

    if (Bus|Dev|Fun) {
        switch (*(PciCfgOfs8+0xB)) {    // class code
            case PCI_CL_SYSTEM_PERIPHERALS:
                                    if(*(PciCfgOfs8+0xA) == PCI_CL_SYSTEM_PERIPHERALS_SCL_SD) {
                                        BbsDevType = BBS_HARDDISK;
                                    } else {
                                        BbsDevType = BBS_UNKNOWN;
                                    }
                                    break;
            case PCI_CL_MASS_STOR:
            case PCI_CL_I2O:        BbsDevType = BBS_HARDDISK; break;
            case PCI_CL_NETWORK:    BbsDevType = BBS_EMBED_NETWORK; break;
            case PCI_CL_BRIDGE:     BbsDevType = BBS_EMBED_NETWORK;     //for nVIDIA MCP55 LAN device is bridge mode
                break;
            case PCI_CL_SER_BUS:    BbsDevType = BBS_BEV_DEVICE; break;

            default:    BbsDevType = BBS_UNKNOWN;
        }
    } else {
        BbsDevType = BBS_EMBED_NETWORK; // Service ROMs
    }
    //
    // Get PnP information from ROM header and fill BBS structures
    //
    PnpOfs = *((UINT16*)(Rom + 0x1A));// Offset of the 1st PnP header
    for (;;PnpOfs = (UINT16)PnpHdr->NextHeaderOffset) {
        if (gDoNotUpdateBbsTable) break;

        PnpHdr = (PCI_PNP_EXPANSION_HEADER*) (Rom + PnpOfs);
        if (*((UINT32*)PnpHdr) != 0x506E5024) break;    // "$PnP"

        //
        // Calculate the CheckSum and check if table is valid
        //
        Checksum = 0;
        for (i = 0; i < sizeof(PCI_PNP_EXPANSION_HEADER); i++){
            Checksum += *(((UINT8*)PnpHdr) + i);
        }
        if (Checksum) continue;

        if (PnpHdr->BCV == 0 && PnpHdr->BEV == 0 &&
            !(NewInt18 || NewInt19)) continue;

        //
        // Change BbsType from BBS_HARDDISK to BBS_CDROM if BCV==0 and BEV!=0
        //
        bbsDevType = BbsDevType;
        if (BbsDevType == BBS_HARDDISK && (!PnpHdr->BCV) && PnpHdr->BEV) {
            bbsDevType = BBS_CDROM;
        }
        if (PnpHdr->BCV != 0) {
            bbsDevType = BBS_HARDDISK;
        }

        BbsTable[BbsCount].DeviceType = bbsDevType;
        BbsTable[BbsCount].Bus = (UINT32)Bus;
        BbsTable[BbsCount].Device = (UINT32)Dev;
        BbsTable[BbsCount].Function = (UINT32)Fun;
        BbsTable[BbsCount].Class = *(PciCfgOfs8+0xB);
        BbsTable[BbsCount].SubClass = *(PciCfgOfs8+0xA);
        BbsTable[BbsCount].DescStringSegment = PnpSeg;
        BbsTable[BbsCount].DescStringOffset = PnpHdr->ProductNamePtr;
        BbsTable[BbsCount].MfgStringSegment = PnpSeg;
        BbsTable[BbsCount].MfgStringOffset = PnpHdr->MfgPtr;
        BbsTable[BbsCount].BootPriority = BBS_UNPRIORITIZED_ENTRY;
        BbsTable[BbsCount].BootHandlerSegment = PnpSeg;
        if (NewInt18) {
            BbsTable[BbsCount].AdditionalIrq18Handler = ivt[0x18];
            BbsTable[BbsCount].BootHandlerOffset = ivt[0x18];
        }
        if (NewInt19) {
            BbsTable[BbsCount].AdditionalIrq19Handler = ivt[0x19];
            BbsTable[BbsCount].BootHandlerOffset = ivt[0x19];
        }

        if (PnpHdr->BCV) {
            BbsTable[BbsCount].BootHandlerOffset = PnpHdr->BCV;
            ExecuteBcv(BiosInfo, PciCfgOfs8, PnpSeg, PnpHdr->BCV, DiskFrom);
        }
        if (PnpHdr->BEV && !(NewInt18 || NewInt19)) {
            BbsTable[BbsCount].BootHandlerOffset = PnpHdr->BEV;
        }

        if (gSetup.I19Trap == 0 && NewInt19) {
            TRACE((-1, "CSM: trapped int19 execution postponed.\n"));
            
            // clear up the BBS table, leave only the one entry that traps INT19
            // block any further BBS table updates
            for (i = 0; i < BbsCount; i++) {
                BbsTable[i].BootPriority = BBS_IGNORE_ENTRY;
            }
            gDoNotUpdateBbsTable = TRUE;
        }
        BbsCount++;
    }

    //
    // Update number of BBS entries
    //
    BiosInfo->BbsEntriesNo = BbsCount;
    gBbsUpdateInProgress = FALSE;
}


//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Name:        Check30ROM
//
// Description: Verifies whether the passed PCI ROM image is PCI 3.0 compatible.
//              If so, returns the projected (runtime) size of this ROM.
//
// Output:      TRUE - image is PCI 3.0 compliant ROM, size is updated
//              FALSE - image is not PCI 3.0 compliant ROM, size remains untouched.
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

BOOLEAN
Check30ROM(
    IN VOID         *RomLocation,
    IN OUT UINTN    *Size,
    IN  EFI_HANDLE  PciHandle
)
{
    PCI_DATA_STRUCTURE *pcir;
    EFI_STATUS Status;
    // TODO:: move this patchy data elswhere
    static UINT32 pci30pretender[] = {
                0x00041103, // Adaptec 1200 (did 0004 vid 1103)
                0x444d8086, // Intel ROBSON Technology card (444D)
                0x444e8086, // Intel ROBSON Technology card (444E)
                0x26818086  // Intel AHCI Option ROM
    };

    //
    // Check for 55AA in the beginning of the image
    //
    if (((LEGACY_OPT_ROM_HEADER*)RomLocation)->Signature != 0xAA55) return FALSE;
    //
    // Validate "PCIR" data
    //
    pcir = (PCI_DATA_STRUCTURE *)((UINT8*)RomLocation + *(UINT16*)((UINT8*)RomLocation + 0x18));
    if (pcir->Signature != 0x52494350) return FALSE;    // "PCIR"

    if (pcir->Revision == 3) {
        UINT8 i;    // check for the OpROMs that are faking PCI3.0 compatibility
        UINT32 VidDid;
        EFI_PCI_IO_PROTOCOL *PciIo;

        if (PciHandle != NULL) {

            Status = pBS->HandleProtocol(PciHandle, &gEfiPciIoProtocolGuid, &PciIo);
            ASSERT(PciIo);
    
            if (EFI_ERROR(Status)) return FALSE;
    
            Status = PciIo->Pci.Read(PciIo, EfiPciIoWidthUint32,
                0,  // offset
                1,  // width
                &VidDid);
            ASSERT_EFI_ERROR(Status);
    
            for (i=0; i<(sizeof(pci30pretender)/sizeof(pci30pretender[0])); i++) {
                if (pci30pretender[i] == VidDid) return FALSE;
            }
        }

        *Size = pcir->Reserved1 << 9;   // Follow PCI.H definitions
        return TRUE;
    }
    return FALSE;
}


//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Name:        CheckPciRom
//
// Description: Tests to see if a traditional PCI ROM exists for this device
//
// Input:
//  This        Indicates the EFI_LEGACY_BIOS_PROTOCOL instance.
//  PciHandle   The handle for this device. Type EFI_HANDLE is defined in
//              InstallProtocolInterface() in the EFI 1.10 Specification.
//  RomImage    Pointer to the ROM image.
//  RomSize     The size of the ROM image.
//  Flags       The type of ROM discovered. Multiple bits can be set, as follows:
//                  00 = No ROM
//                  01 = ROM Found
//                  02 = ROM is a valid legacy ROM
//
// Output:      EFI_SUCCESS A traditional OpROM is available for this device.
//              EFI_UNSUPPORTED A traditional OpROM is not supported.
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS CheckPciRom (
  IN EFI_LEGACY_BIOS_PROTOCOL         *This,
  IN  EFI_HANDLE                      PciHandle,
  OUT VOID                            **RomImage, OPTIONAL
  OUT UINTN                           *RomSize,   OPTIONAL
  OUT UINTN                           *Flags
)
{
    EFI_PCI_IO_PROTOCOL *pPciIo;
    UINT32 VidDid;
    VOID *PciRom;
    UINTN PciRomSize = 0;
    EFI_STATUS Status;
    BOOLEAN ValidRom = FALSE;
    UINTN RomStatus = 0;
    PCI_STD_DEVICE              Pci;
    EXECUTED_PCI_ROM *ExecutedRom = gExecutedRomsPci-1;
    EXECUTED_PCI_ROM *er;
    UINTN PciSegment, PciBus, PciDeviceNumber, PciFunction;

    Status = pBS->HandleProtocol(PciHandle, &gEfiPciIoProtocolGuid, &pPciIo);
    if (EFI_ERROR(Status) || (&pPciIo == NULL)) return EFI_UNSUPPORTED;

    PciRom = pPciIo->RomImage;

    Status = pPciIo->Pci.Read(pPciIo,
        EfiPciIoWidthUint32,
        0,  // offset
        1,  // width
        &VidDid);
    ASSERT_EFI_ERROR(Status);

    if (PciRom) {
        PciRomSize = (UINTN)pPciIo->RomSize;
        ValidRom = IsValidLegacyPciOpROM(VidDid, &PciRom, &PciRomSize);
        RomStatus = ValidRom? 2 : 1;
    }
    if (!ValidRom) {
		Status = GetPlatformPciEmbeddedRom(pPciIo, &PciRom, &PciRomSize);
        
		if (EFI_ERROR(Status)) {
        	Status = FindEmbeddedRom(OPROM_MODULEID, (UINT16)VidDid,
            	        *((UINT16*)&VidDid+1), &PciRom, &PciRomSize);
        }

        //
        // Check whether the identified ROM is a legacy OptionROM,
        // and correspondingly modify the value of "RomStatus".
        // Note: PciRomSize is initialized here
        if (!EFI_ERROR(Status)) {
    		ValidRom = IsValidLegacyPciOpROM(VidDid, &PciRom, &PciRomSize);
    		RomStatus = ValidRom? 2 : 1;
    	}
    }

    if(!ValidRom) {

        Status = pPciIo->GetLocation(pPciIo,
                    &PciSegment, &PciBus, &PciDeviceNumber, &PciFunction);

        //
        // Sd option rom can handle all the function on one time
        // So if any of one of the function on device already launched option
        // no need to launch the option rom for other functions.
        //
        for (er = ExecutedRom; er->Seg | er->Bus | er->Dev | er->Fun; er--) {
            if (er->Seg == PciSegment && er->Bus == PciBus &&
                er->Dev == PciDeviceNumber) {
                break;
            }
        }
        
        //
        //SD option can handle all the function. So don't launch option for other functions.
        //
        if(!(er->Seg | er->Bus | er->Dev | er->Fun)) {

            Status = pPciIo->Pci.Read (pPciIo,
                                EfiPciIoWidthUint32,
                                0,
                                sizeof (Pci) / sizeof (UINT32),
                                &Pci);
            //
            //Check For SD controller. If it's SD controller find Sd option rom and launch it.
            //
		    if ( Pci.Header.ClassCode[1] == PCI_CL_SYSTEM_PERIPHERALS_SCL_SD && \
			    Pci.Header.ClassCode[2] == PCI_CL_SYSTEM_PERIPHERALS ) {
                Status=FindEmbeddedRom( CSM16_MODULEID, CSM16_VENDORID, CSM16_SD_BOOT_DID, &PciRom, &PciRomSize);
                if (!EFI_ERROR(Status)) {
    		        ValidRom = IsValidLegacyPciOpROM(VidDid, &PciRom, &PciRomSize);
    		        RomStatus = ValidRom? 2 : 1;
    	        }
            }
        }
    }

    *Flags = RomStatus;

    if (RomStatus == 2) {
        if (RomImage != NULL) *RomImage = PciRom;
        if (RomSize != NULL) *RomSize = PciRomSize;
        return EFI_SUCCESS;
    }

    return EFI_UNSUPPORTED;
}


//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Name:        FindAnyVga
//
// Description: Returns the first VGA controller handle from PciIo device list.
//
// Input:       None
//
// Output:      PCI VGA controller PciIo handle
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS FindAnyVga(
    OUT EFI_HANDLE* hVga
)
{
    EFI_HANDLE  *HandleBuffer;
    UINTN       n, HandleCount;
    EFI_STATUS  Status;
    UINT8       dData[4];
    EFI_PCI_IO_PROTOCOL *PciIo;
    EFI_STATUS  VgaStatus = EFI_NOT_FOUND;

    //
    // Locate all PciIo handles
    //
    Status = pBS->LocateHandleBuffer (
        ByProtocol,
        &gEfiPciIoProtocolGuid,
        NULL,
        &HandleCount,
        &HandleBuffer);

    ASSERT_EFI_ERROR(Status);
    if (EFI_ERROR (Status)) {
        return Status;
    }
    for (n = 0 ; n < HandleCount; n++) {

        Status = pBS->HandleProtocol (
            HandleBuffer[n],
            &gEfiPciIoProtocolGuid,
            &PciIo);           // Get PciIo protocol
        ASSERT_EFI_ERROR (Status);
        if (EFI_ERROR(Status)) break;

        Status = PciIo->Pci.Read(
            PciIo,
            EfiPciIoWidthUint32,
            8,  // offset
            1,  // width
            dData);
        ASSERT_EFI_ERROR(Status);
        if (EFI_ERROR(Status)) break;

        if (dData[3]==PCI_CL_DISPLAY) {
            *hVga = HandleBuffer[n];
            VgaStatus = EFI_SUCCESS;
            break;
        }
    }
    pBS->FreePool(HandleBuffer);
    return VgaStatus;
}


//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Name:        PciRomAlreadyExecuted
//
// Description: Reports whether OpROM for a given PciIo already executed.
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

EXECUTED_PCI_ROM*
PciRomAlreadyExecuted(
    IN EFI_PCI_IO_PROTOCOL *PciIo
)
{
    UINTN               Seg, Bus, Dev, Fun;
    EXECUTED_PCI_ROM    *ExecutedRom;
    EFI_STATUS          Status;


    Status = PciIo->GetLocation(PciIo, &Seg, &Bus, &Dev, &Fun);
    ASSERT_EFI_ERROR(Status);

    for (ExecutedRom = gExecutedRomsPci-1;
         ExecutedRom->Seg | ExecutedRom->Bus | ExecutedRom->Dev | ExecutedRom->Fun;
         ExecutedRom--)
    {
        if (ExecutedRom->Seg == Seg && ExecutedRom->Bus == Bus &&
            ExecutedRom->Dev == Dev && ExecutedRom->Fun == Fun) {
            return ExecutedRom;
        }
    }
    return NULL;
}


//<AMI_PHDR_START>
//---------------------------------------------------------------------------
//
// Name:        CheckEnablePciSiblings
//
// Description:
//  This function manages the ability of the Option ROM to control several PCI
//  devices in the system.
//  For example, SCSI Option ROM designed for the multi-channel SCSI adaptor
//  usually controls all the channels even though they are different PCI 
//  functions of the same device. Likewise, NIC Option ROM may be able to control
//  several NICs located on different PCI devices or even on different PCI buses.
//
// Input:
//  PciIo       - PCI I/O protocol of the PCI device whose Option ROM is about
//                to be executed
//  PciCfgData  - byte array of device's PCI configuration space (registers 0..3f)
//
// Output:
//  EFI_SUCCESS         - Option ROM is okay execute
//  EFI_ALREADY_STARTED - Option ROM must be skipped
//
// Notes:
//  Function code flow:
//  1) Execute OEM porting hook to see if OEM overrides the default device enable
//     policy. If so, return EFI_ALREADY_STARTED.
//  2) Enable all function of the given PciIo.
//  3) Enable all PCI devices with the same VID/DID as in given PciIo.
//  4) Return EFI_SUCCESS indicating "greenlight" for Option ROM execution.
//
//---------------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS
CheckEnablePciSiblings(
    EFI_PCI_IO_PROTOCOL *PciIo,
    UINT8               *PciCfgData
)
{
    EFI_STATUS          Status;
    EXECUTED_PCI_ROM    *ExecutedRom = gExecutedRomsPci-1;
    EFI_HANDLE          *HandleBuffer;
    UINTN               Count;
    UINTN               HandleCount;
    UINTN               PciSegment, PciBus, PciDeviceNumber, PciFunction;
    UINTN               Seg, Bus, Dev, Func;
    EFI_PCI_IO_PROTOCOL *CurrentPciIo;
    UINT64              Capabilities;
    UINT32              VidDid;
    UINT8               PciCfgData1[40];
    Status = pBS->LocateHandleBuffer (ByProtocol, &gEfiPciIoProtocolGuid,
        NULL, &HandleCount, &HandleBuffer);
    ASSERT_EFI_ERROR(Status);

    Status = CheckOemPciSiblings(PciIo, ExecutedRom);
    if (Status == EFI_SUCCESS) return EFI_ALREADY_STARTED;

    Status = EnableOemPciSiblings(PciIo);
    if (Status == EFI_SUCCESS) return EFI_SUCCESS;


    Status = PciIo->GetLocation(PciIo, &Seg, &Bus, &Dev, &Func);
    ASSERT_EFI_ERROR(Status);

    for (Count = 0; Count < HandleCount; Count++) {
        Status = pBS->HandleProtocol (HandleBuffer[Count], &gEfiPciIoProtocolGuid, &CurrentPciIo);
        ASSERT_EFI_ERROR(Status);

        Status = CurrentPciIo->GetLocation(CurrentPciIo,
                    &PciSegment, &PciBus, &PciDeviceNumber, &PciFunction);

        // Check if it is the same device
        if (PciBus == Bus && PciDeviceNumber == Dev && PciFunction == Func) continue;

        Status = CurrentPciIo->Pci.Read(CurrentPciIo, EfiPciIoWidthUint32, 0, 1, &VidDid);
        ASSERT_EFI_ERROR(Status);
		
        // Do not do anything else for VGA; if multiple VGA is enabled at the same time,
        // OS might have a problem. EIP60317.
        Status = CurrentPciIo->Pci.Read(CurrentPciIo, EfiPciIoWidthUint8, 0, 40, PciCfgData1);
        ASSERT_EFI_ERROR(Status);
        if (PciCfgData1[0xb] == PCI_CL_DISPLAY) continue;

        // Check if it is a different function of the same device or if VID/DID is the same
        if ((PciBus == Bus && PciDeviceNumber == Dev)
            || (*(UINT32*)PciCfgData == VidDid)) {

            Status = CurrentPciIo->Attributes (CurrentPciIo,
                    EfiPciIoAttributeOperationSupported, 0,
                    &Capabilities);     // Get device capabilities
            ASSERT_EFI_ERROR(Status);
    
            Status = CurrentPciIo->Attributes (CurrentPciIo,
                    EfiPciIoAttributeOperationEnable,
                    Capabilities & EFI_PCI_DEVICE_ENABLE,
                    NULL);              // Enable device
            ASSERT_EFI_ERROR(Status);
            TRACE((TRACE_ALWAYS,
                "CSM OPROM: device B%x/d%x/F%x was enabled for B%x/d%x/F%x OPROM execution.\n",
                PciBus, PciDeviceNumber, PciFunction, Bus, Dev, Func));
        }
    }

    return EFI_SUCCESS;
}


//<AMI_PHDR_START>
//---------------------------------------------------------------------------
//
// Name:        ClpExecute
//
// Description:
//  This is CLP execution protocol function that is called by any driver that
//  needs to perform device configuration using Command Line Protocol.
//
// Input:
//  PciIo               Command Line Protocol instance pointer
//  CmdInputLine        Pointer to a null-terminated input string
//  CmdResponseBuffer   Pointer to command output buffer
//  CmdStatus           CLP command execution status
//
// Output:
//  EFI_SUCCESS         Execution succeeded, result is in CmdStatus
//  Any other value     Error status of the execution
//
//---------------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS
ClpExecute (
    IN EFI_CLP_PROTOCOL *This,
    IN OUT UINT8        *CmdInputLine,
    IN OUT UINT8        *CmdResponseBuffer,
    OUT UINT32          *CmdStatus
)
{
    EFI_STATUS  Status;
    BOOLEAN FarCallStatus;
    EFI_IA32_REGISTER_SET   RegSet;
    static EFI_LEGACY_BIOS_PROTOCOL *LegacyBios = NULL;
    EFI_PCI_IO_PROTOCOL *PciIo;
    UINTN Seg, Bus, Dev, Fun;

    // Get LegacyBios protocol for FarCall86 execution
    if (LegacyBios == NULL) {
        Status = pBS->LocateProtocol(&gEfiLegacyBiosProtocolGuid, NULL, &LegacyBios);
        ASSERT_EFI_ERROR(Status);
        if (EFI_ERROR(Status)) {
            return Status;
        }
    }

    // Get PciIo protocol for the PCI bus/dev/func information
    Status = pBS->HandleProtocol(This->Handle, &gEfiPciIoProtocolGuid, &PciIo);
    ASSERT_EFI_ERROR(Status);
    if (EFI_ERROR(Status)) {
        return Status;
    }
    
    PciIo->GetLocation(PciIo, &Seg, &Bus, &Dev, &Fun);

    // Prepare the registers for CLP execution
    pBS->SetMem(&RegSet, sizeof (EFI_IA32_REGISTER_SET), 0);
    RegSet.H.AH = (UINT8)Bus;
    RegSet.H.AL = ((UINT8)Dev << 3) | (UINT8)Fun;
    RegSet.E.EDI = (UINT32)(UINTN)CmdInputLine;
    RegSet.E.ESI = (UINT32)(UINTN)CmdResponseBuffer;

    // Execute CLP command
    FarCallStatus = FarCall86 (LegacyBios,
                This->EntrySeg,
                This->EntryOfs,
                &RegSet,
                NULL,
                0);

    if (FarCallStatus == FALSE) {
        Status = EFI_SUCCESS;
        *CmdStatus = RegSet.E.EAX;
    } else {
        Status = EFI_DEVICE_ERROR;
    }

    return Status;
}


//<AMI_PHDR_START>
//---------------------------------------------------------------------------
//
// Name:        InitClp
//
// Description:
//  This function is initializing and installing the CLP protocol.
//
// Input:
//  Handle      PCI device handle
//  Csm16DOT    Option ROM related data structure
//
// Output:
//  EFI_SUCCESS         CLP protocol successfully installed
//  EFI_UNSUPPORTED     CLP protocol can not be installed on this device
//
//---------------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS
InitClp (
    IN EFI_HANDLE   Handle,
    IN EFI_DISPATCH_OPROM_TABLE *Csm16DOT
)
{
    UINT8 *RomLocation;
    PCI_PCIR30_DATA_STRUCTURE *Pcir;
    EFI_CLP_PROTOCOL *ClpProtocol;
    EFI_STATUS Status;
    static EFI_GUID guidClp = EFI_CLP_PROTOCOL_GUID;

    RomLocation = (UINT8*)(UINTN)((UINT32)Csm16DOT->OpromSegment << 4);

    Pcir = (PCI_PCIR30_DATA_STRUCTURE *)(RomLocation + *(UINT16*)(RomLocation + 0x18));

    if (Pcir->Signature != 0x52494350) {
        TRACE((-1, "Init CLP: PCIR signature is missing."));
        return EFI_UNSUPPORTED;
    }

    if (Pcir->Revision < 3) {
        TRACE((-1, "Init CLP: CLP support requires PCI version 3.0 or above."));
        return EFI_UNSUPPORTED;
    }

    if (Pcir->ClpEntryPoint == 0) {
        TRACE((-1, "Init CLP: CLP entry point is not present."));
        return EFI_UNSUPPORTED;
    }

    if (Handle == NULL) {
        TRACE((-1, "Init CLP: CLP ROM must be associated with PCI device."));
        return EFI_UNSUPPORTED;
    }

    Status = pBS->AllocatePool(EfiBootServicesData, sizeof(EFI_CLP_PROTOCOL), &ClpProtocol);
    ASSERT_EFI_ERROR(Status);

    ClpProtocol->Handle = Handle;
    ClpProtocol->EntrySeg = Csm16DOT->OpromSegment;
    ClpProtocol->EntryOfs = Pcir->ClpEntryPoint;
    ClpProtocol->Execute = ClpExecute;

    return pBS->InstallProtocolInterface(
        &Handle, &guidClp, EFI_NATIVE_INTERFACE, ClpProtocol);
}


//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Name:        CsmInstallRom
//
// Description: Executes a given ROM using parameters pre-defined as input in
//  EFI_DISPATCH_OPROM_TABLE data structure.
//
// Input:
//  CoreBiosInfo    The pointer to the BIOS_INFO variable
//  PciIo           PCI IO handle, NULL for non-PCI ROMs
//  Csm16DOT        ROM execution input parameters
//  NextRomAddress  The location in the shadow that will have the run-time image
//                  of the ROM
//  IsVga           Video ROM indicator
//
// Output:
//  NewRomSize          Run-time size of the ROM, in Bytes
//  ProcessBootDevices  Indicator of the new bootable devices found during
//                      ROM execution
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS
CsmInstallRom (
    IN BIOS_INFO    *CoreBiosInfo,
    IN EFI_HANDLE   Handle,
    IN EFI_DISPATCH_OPROM_TABLE *Csm16DOT,
    IN UINTN        NextRomAddress,
    IN BOOLEAN      IsVga,
    OUT UINT32      *NewRomSize,
    OUT BOOLEAN     *ProcessBootDevices
)
{
    UINT16      ebdaSeg1, ebdaSeg2;  // ebda pointer before and after OpROM execution
    UINT16      baseMem1, baseMem2;  // 40:13 before and after OpROM execution
    UINT32      ebdaSize1, ebdaSize2;  // ebda size before and after OpROM execution
    BOOLEAN     IsEbda;
    UINT8       ebdaSizeKB;
    EFI_IA32_REGISTER_SET   RegSet;
    UINT16      RegBX;
    UINT8       *RtData = NULL;
    UINT32      RtDataSize;
    UINT32      RtRomSize;
    EFI_STATUS  Status;
    UINT32      CurrentInt10 = 0;
    UINT32      EbdaOffset;
    EFI_PCI_IO_PROTOCOL *PciIo = NULL;
    UINT64      Capabilities;
    UINTN       SetTxtMode;


    if (!IsVga) {
        LockConsole();
        if ((gSetTxtMode == 0) || (gSetTxtMode == 0xff)) {
            DisconnectSerialIO();
            
            if (gSetTxtMode == 0xff) {
                // Call LegacyBiosPlatform to get the VGA switching policy override
                // by default gSetTxtMode will be set to CSM_DEFAULT_VMODE_SWITCHING
                if (Handle != NULL) {
                    Status = pBS->HandleProtocol (
                        Handle,
                        &gEfiPciIoProtocolGuid,
                        &PciIo);
                    ASSERT_EFI_ERROR (Status);
                }
            
                GetOpromVideoSwitchingMode(PciIo, CSM_DEFAULT_VMODE_SWITCHING, &SetTxtMode);
                gSetTxtMode = (UINT8)SetTxtMode;

                if (gSetTxtMode == 1) {
                    // gSetTxtMode is 1: keep gVgaHandle connected, quietly change the video mode
                    RegSet.X.AX = 3;
                    Int86 (&CoreBiosInfo->iBios, 0x10, &RegSet);
                }
            }

            if (gSetTxtMode == 0) {
                // gSetTxtMode is 0: disconnect controller and enable legacy VGA MEM/IO
                Status = pBS->DisconnectController(gVgaHandle, NULL, NULL);
                ASSERT_EFI_ERROR(Status);
                
                Status = pBS->HandleProtocol (
                        gVgaHandle,
                        &gEfiPciIoProtocolGuid,
                        &PciIo);
                ASSERT_EFI_ERROR(Status);

                Status = PciIo->Attributes (PciIo, EfiPciIoAttributeOperationSupported, 0,
                        &Capabilities);
                ASSERT_EFI_ERROR(Status);

                // Enable VGA legacy MEM/IO access
                PciIo->Attributes (PciIo, EfiPciIoAttributeOperationEnable,
                        (Capabilities & EFI_PCI_DEVICE_ENABLE)
                         | EFI_PCI_IO_ATTRIBUTE_VGA_MEMORY | EFI_PCI_IO_ATTRIBUTE_VGA_IO,
                         NULL);
            }
        }
        // Set a dummy INT10 handler if gSetTxtMode is set to 2; note that gSetTxtMode
        // might change after GetOpromVideoSwitchingMode
        if (gSetTxtMode == 2) {
            CurrentInt10 = *(UINT32*)(UINTN)0x40;
            *(UINT32*)(UINTN)0x40 = 0xf000f065;    // legacy int10
        }
    }

    // Initialize CLP (Command Line Protocol) support for this ROM
    Status = InitClp(Handle, Csm16DOT);

    //
    // Save the current EBDA location to check if OpROM modifies it
    ebdaSeg1 = *(UINT16*)(UINTN)0x40e;
    ebdaSizeKB = *(UINT8*)((UINTN)ebdaSeg1<<4);
    ebdaSize1 = (UINTN)ebdaSizeKB << 10;
    ASSERT(ebdaSizeKB);   // should be initialized, can not be 0
    baseMem1 = *(UINT16*)(UINTN)0x413;

    // Execute OpROM

    pBS->SetMem(&RegSet, sizeof (EFI_IA32_REGISTER_SET), 0);
    RegSet.X.AX = Compatibility16DispatchOprom;
    RegSet.X.ES = EFI_SEGMENT (Csm16DOT);
    RegSet.X.BX = EFI_OFFSET (Csm16DOT);

    FarCall86 (&CoreBiosInfo->iBios,
                CoreBiosInfo->Csm16EntrySeg,
                CoreBiosInfo->Csm16EntryOfs,
                &RegSet,
                NULL,
                0);

    RegBX = RegSet.X.BX;

    // Get the run-time Option ROM size right away; note that the value of
    // OpROMSeg:0002 can change later, for example after BCV execution (noticed
    // on NetCell PCI SATA RAID card).
    RtRomSize = ((LEGACY_OPT_ROM_HEADER*)NextRomAddress)->Size512 * 0x200;
TRACE((-1, "InstallRom...Run-time ROM Size = %x Bytes\n", RtRomSize));

    // Update EBDA map
    ebdaSeg2 = *(UINT16*)(UINTN)0x40e;
    ebdaSize2 = *(UINT8*)((UINTN)ebdaSeg2<<4) << 10;

    RtDataSize = 0;
    if (ebdaSeg1 > ebdaSeg2) {
        RtDataSize = ebdaSize2 - ebdaSize1; // #of bytes taken by this OpROM
        UpdateEbdaMap((UINT32)(ebdaSeg1 - ebdaSeg2) << 4);
    }

    // Check for a ROM size not being FF
    if (RtRomSize == 0x1fe00) RtRomSize = 0;

    // Prepare the output parameters
    *ProcessBootDevices = (RegBX == 0 && RtRomSize != 0);
    *NewRomSize = RtRomSize;

    if (IsVga) return EFI_SUCCESS;  // Done for VBIOS

    if (gSetTxtMode != 1) {
        UnlockConsole();
    }

    // Restore video mode if needed
    //  gSetTxtMode:
    //      0: reconnect VGA controller
    //      1: do nothing
    //      2: restore fake INT10 vector
    // Note that at first pass gSetTxtMode is either 0 or 2; in case of 0 it is
    // reassigned using CSM_DEFAULT_VMODE_SWITCHING and OEM override.

    if (gSetTxtMode == 2) {
        *(UINT32*)(UINTN)0x40 = CurrentInt10;
    }

    if (gSetTxtMode == 0) {
        pBS->DisconnectController(gVgaHandle, NULL, NULL);
        pBS->ConnectController(gVgaHandle, NULL, NULL, TRUE);
        ConnectSerialIO();
    }

    // Update BBS device count
    if (CoreBiosInfo->BbsEntriesNo != Csm16DOT->NumberBbsEntries) {
        // CSM16 had inserted some BBS entries for non-BBS devices
        CoreBiosInfo->BbsEntriesNo = Csm16DOT->NumberBbsEntries;
    }

    // Process boot devices
    if (RegBX == 0 && RtRomSize != 0) {   // Either BBS OpROM or no bootable devices connected

        // Save the BBS compliant OpROM memory context here. Note that saving Oprom
        // data is only required for the option ROMs that produce BCV because of early
        // BCV execution; it should not be called for non-BBS compliant OpROMs, for
        // those OpROMs memory context will be the same til the system is booted.

        if (RtDataSize) {
            // EBDA was allocated, calculate the address
            IsEbda = TRUE;
            RtData = (UINT8*)(((UINTN)ebdaSeg2<<4) + ((UINTN)ebdaSizeKB<<10));
        } else {
            // EBDA was not allocated; verify data is not requested
            // by a blind update of 40:13. This memory allocation method
            // was observed on OpROM by Adaptec 39160, FW ver V2.55.0.
            IsEbda = FALSE;
            baseMem2 = *(UINT16*)(UINTN)0x413;
            RtDataSize = (UINT32)(baseMem1-baseMem2)<<10;
            if (RtDataSize) {
                RtData = (UINT8*)((UINTN)baseMem2<<10);
            }
        }

        EbdaOffset = IsEbda? (UINT32)ebdaSizeKB<<10 : 0;
        SaveOprom ((UINT8*)NextRomAddress, RtData, RtDataSize, IsEbda, EbdaOffset);
    }

    return EFI_SUCCESS;
}


//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Name:        InstallPciRom
//
// Description: Shadows an OpROM
//
// Input:
//  This        Indicates the EFI_LEGACY_BIOS_PROTOCOL instance.
//  PciHandle   The PCI PC-AT* OpROM from this device's ROM BAR will be loaded
//  RomImage    A PCI PC-AT ROM image.  This argument is non-NULL if there is
//                  no hardware associated with the ROM and thus no PciHandle;
//                  otherwise it must be NULL. An example is the PXE base code.
//  Flags       The type of ROM discovered. Multiple bits can be set, as follows:
//                  00 = No ROM.
//                  01 = ROM found.
//                  02 = ROM is a valid legacy ROM.
//  DiskStart   Disk number of the first device hooked by the ROM. If DiskStart is
//                  the same as DiskEnd, no disks were hooked.
//  DiskEnd     Disk number of the last device hooked by the ROM.
//  RomShadowAddress    Shadow address of PC-AT ROM.
//  ShadowedRomSize     Size in bytes of RomShadowAddress.
//
// Output:
//  EFI_SUCCESS     The OpROM was shadowed
//  EFI_UNSUPPORTED The PciHandle was not found
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS
InstallPciRom (
  IN EFI_LEGACY_BIOS_PROTOCOL         *This,
  IN  EFI_HANDLE                      PciHandle,
  IN  VOID                            **RomImage,
  OUT UINTN                           *Flags,
  OUT UINT8                           *DiskStart, OPTIONAL
  OUT UINT8                           *DiskEnd, OPTIONAL
  OUT VOID                            **RomShadowAddress, OPTIONAL
  OUT UINT32                          *ShadowedRomSize OPTIONAL
  )
{
    EFI_STATUS Status, Status1 = EFI_SUCCESS;
    VOID* RomLocation;
    EFI_PHYSICAL_ADDRESS Rom30Address = 0;
    UINTN RomSize, Rom30Size = 0;
    EFI_DISPATCH_OPROM_TABLE *Csm16DOT;
    UINTN PciSegment, PciBus, PciDeviceNumber, PciFunction;
    BIOS_INFO *CoreBiosInfo = (BIOS_INFO*)This;
    UINT32 NewRomSize = 0;
    BOOLEAN IsVga = FALSE;
    UINT8 DiskFrom = 0x80;
    UINT8 DiskTo = 0x80;
    UINT8 PciCfgData[0x40];
    EFI_HANDLE *VgaHandlePtr = &gVgaHandle;
    UINTN VgaHandleCount;
    EFI_PCI_IO_PROTOCOL *PciIo = NULL;
    UINT64 Capabilities;
    BOOLEAN is30ROM = FALSE;
    UINT32 LockUnlockAddr, LockUnlockSize;
    CSM_PLATFORM_PROTOCOL *CsmPlatformProtocol;
    UINTN LowMem4KPages = 0;
    EXECUTED_PCI_ROM *ExecutedRom = NULL;
    BOOLEAN ProcessBootDevices;
    volatile UINT32 *ivt = (UINT32*)0;
    UINT32 Int18;
    UINT32 Int19;
    BOOLEAN Int19Trapped = FALSE;
	UINT32 NumberAlreadyExecutedPciRoms;

    //
    // Handle separately HW independent OpROMs, e.g. PXE
    //
    if (PciHandle == NULL) {
        IsVga = FALSE;
        PciSegment = 0; PciBus = 0; PciDeviceNumber = 0; PciFunction = 0;
    }
    else {
        Status = pBS->HandleProtocol (
            PciHandle,
            &gEfiPciIoProtocolGuid,
            &PciIo);            // Get PciIo protocol
        ASSERT_EFI_ERROR (Status);

        //
        // NOTE: The following call will check whether the LegacyOpROM
        // has already been executed for PciIo. If so, it returns EFI_SUCCESS.
        //
        ExecutedRom = PciRomAlreadyExecuted(PciIo);
        if (ExecutedRom != NULL) {
            *Flags = ExecutedRom->Flags;
            if (DiskStart) *DiskStart = ExecutedRom->DiskFrom;
            if (DiskEnd) *DiskEnd = ExecutedRom->DiskTo;
            if (RomShadowAddress) *RomShadowAddress = ExecutedRom->RomAddress;
            if (ShadowedRomSize) *ShadowedRomSize = ExecutedRom->RomSize;

            return EFI_SUCCESS;
        }

        // Verify the number of already executed PCI ROMs does not exceed MAX_EXECUTED_OPROMS
        NumberAlreadyExecutedPciRoms = 0;
        for (
            ExecutedRom = gExecutedRomsPci-1;
            ExecutedRom->Seg | ExecutedRom->Bus | ExecutedRom->Dev | ExecutedRom->Fun;
            NumberAlreadyExecutedPciRoms++, ExecutedRom--
        ){}

        if (NumberAlreadyExecutedPciRoms >= MAX_EXECUTED_OPROMS)
        {
            return EFI_OUT_OF_RESOURCES;
        }

        Status = PciIo->Pci.Read(
            PciIo,
            EfiPciIoWidthUint8,
            0,      // offset
            0x40,   // width
            PciCfgData);
        ASSERT_EFI_ERROR(Status);

        if (PciCfgData[0xB]==PCI_CL_OLD && PciCfgData[0xA]==PCI_CL_OLD_SCL_VGA) {
            IsVga = TRUE;
        }
        if (PciCfgData[0xB]==PCI_CL_DISPLAY && PciCfgData[0xA]==PCI_CL_DISPLAY_SCL_VGA) {
            IsVga = TRUE;
        }

        Status = CheckEnablePciSiblings(PciIo, PciCfgData);
        if (EFI_ERROR(Status)) return Status;

        Status = PciIo->GetLocation(PciIo,
                    &PciSegment, &PciBus, &PciDeviceNumber, &PciFunction);
        ASSERT_EFI_ERROR(Status);
    }


    //
    // Execute platform pre-OpROM function
    //
    Status = pBS->LocateProtocol(&gCsmPlatformProtocolGuid, NULL, &CsmPlatformProtocol);

    if (!EFI_ERROR(Status)) {
        Status = PreProcessOpRom(CsmPlatformProtocol, PciIo, RomImage);

        if (EFI_ERROR(Status)) {
            PostProcessOpRom(CsmPlatformProtocol, PciIo, RomImage);
            return Status;
        }
    }

    if (IsVga) {
        if (CoreBiosInfo->hVga != NULL) {
            //
            // More than one legacy video is not supported
            // We return EFI_SUCCESS so that Video Thunk driver start function
            // does not fail.
            //
            if (CsmPlatformProtocol) {
                PostProcessOpRom(CsmPlatformProtocol, PciIo, RomImage);
            }
            return EFI_SUCCESS;
        }
        Status = CoreBiosInfo->iBiosPlatform->GetPlatformHandle(
                        CoreBiosInfo->iBiosPlatform,
                        EfiGetPlatformVgaHandle,
                        0,
                        &VgaHandlePtr,
                        &VgaHandleCount,
                        NULL);
        if (!EFI_ERROR(Status)) {       // Platform returned VGA handle
            if (PciHandle != *VgaHandlePtr) {   // Not the one requested by platform
                if (CsmPlatformProtocol) {
                    PostProcessOpRom(CsmPlatformProtocol, PciIo, RomImage);
                }
                return EFI_UNSUPPORTED;
            }
        }
    }
    else {  // Not VGA
        if (CoreBiosInfo->hVga == NULL) {
            // NOTE: WITH THE CURRENT BDS IMPLEMENTATION CONTROL SHOULD NEVER COME HERE
            EFI_PCI_IO_PROTOCOL *VgaPciIo = NULL;
            //
            // The control is passed to this routine to install non-VGA OpROM and VGA BIOS is
            // not yet installed. This could happen in the following scenarios:
            // 1) Video is controlled by Efi native video driver
            // 2) BDS is connecting mass storage before consoles
            // 3) The system is headless (no video controller)
            //
            // We will try to find video and launch its oprom; for case #1 we will disconnect
            // the native driver and reconnect it after OpROM is executed.
            //
            Status = CoreBiosInfo->iBiosPlatform->GetPlatformHandle(
                        CoreBiosInfo->iBiosPlatform,
                        EfiGetPlatformVgaHandle,
                        0,
                        &VgaHandlePtr,
                        &VgaHandleCount,
                        NULL);
            if (EFI_ERROR(Status)) {        // Platform did not return VGA handle, try to find one
                Status1 = FindAnyVga(VgaHandlePtr);
            }
            if (!EFI_ERROR(Status) || !EFI_ERROR(Status1)) {    // Found VGA - enable it and launch OpROM
                Status = pBS->HandleProtocol (
                        *VgaHandlePtr,
                        &gEfiPciIoProtocolGuid,
                        &VgaPciIo);            // Get PciIo protocol
                ASSERT_EFI_ERROR(Status);

                Status = VgaPciIo->Attributes (VgaPciIo,
                        EfiPciIoAttributeOperationSupported, 0,
                        &Capabilities);     // Get device capabilities
                ASSERT_EFI_ERROR(Status);

                Status = VgaPciIo->Attributes (VgaPciIo,
                        EfiPciIoAttributeOperationEnable,
                        Capabilities & EFI_PCI_DEVICE_ENABLE,
                        NULL);              // Enable device
                ASSERT_EFI_ERROR(Status);

                InstallPciRom(This,         // Recursive call
                        *VgaHandlePtr, NULL, Flags,
                        NULL, NULL, NULL, NULL);
            }
        }
    }

    VgaHandlePtr = &gVgaHandle;

    if (IsVga) {
        ASSERT(PciIo != NULL);
        Status = PciIo->Attributes (PciIo, EfiPciIoAttributeOperationGet, 0,
                &Capabilities);     // Get device capabilities
        ASSERT_EFI_ERROR(Status);

        Status = PciIo->Attributes (PciIo, EfiPciIoAttributeOperationEnable,
                Capabilities | EFI_PCI_IO_ATTRIBUTE_VGA_MEMORY | EFI_PCI_IO_ATTRIBUTE_VGA_IO,
                NULL);              // Enable VGA legacy MEM/IO access
        ASSERT_EFI_ERROR(Status);

        CoreBiosInfo->hVga = PciHandle;
        *VgaHandlePtr = PciHandle;
    }

    //
    // Get the ROM image location
    //
    if (PciHandle != NULL) {
        Status = CheckPciRom (This, PciHandle, &RomLocation, &RomSize, Flags);
        if (EFI_ERROR(Status) || (RomLocation == NULL)) {
            if (CsmPlatformProtocol) {
                PostProcessOpRom(CsmPlatformProtocol, PciIo, RomImage);
            }
            return EFI_UNSUPPORTED;
        }

        is30ROM = Check30ROM(RomLocation, &Rom30Size, PciHandle);
    }
    else {  // ROM is not associated with PCI device
        RomLocation = *RomImage;
        RomSize = ((LEGACY_OPT_ROM_HEADER*)RomLocation)->Size512 * 0x200;
        if (RomSize == 0) {
            if (CsmPlatformProtocol) {
                PostProcessOpRom(CsmPlatformProtocol, PciIo, RomImage);
            }
            return EFI_UNSUPPORTED;
        }
        is30ROM = Check30ROM(RomLocation, &Rom30Size, NULL);
    }

    //
    // For PCI3.0 compliant ROMs reserve base memory for ROM Init code
    //
    if (is30ROM) {
        Rom30Address = 0xA0000;
        LowMem4KPages = RomSize >> 12;   // Number of 4KB units
        if (RomSize % 0x1000) {
            LowMem4KPages++;
        }
        Status = pBS->AllocatePages(AllocateMaxAddress,
                    EfiBootServicesData,
                    LowMem4KPages,
                    &Rom30Address);
        ASSERT_EFI_ERROR(Status);
        if (EFI_ERROR(Status)) {
            if (CsmPlatformProtocol) {
                PostProcessOpRom(CsmPlatformProtocol, PciIo, RomImage);
            }
            DEVICE_ERROR_CODE(DXE_LEGACY_OPROM_NO_SPACE, EFI_ERROR_MAJOR, PciHandle);
            return EFI_OUT_OF_RESOURCES;
        }

        if (Rom30Address < 0x8000) {
            if (CsmPlatformProtocol) {
                PostProcessOpRom(CsmPlatformProtocol, PciIo, RomImage);
            }
            Status = EFI_OUT_OF_RESOURCES;
            TRACE(((UINTN)TRACE_ALWAYS,"Can not execute PCI 3.0 OPROM: out of Base Memory.\n"));
            DEVICE_ERROR_CODE(DXE_LEGACY_OPROM_NO_SPACE, EFI_ERROR_MAJOR, PciHandle);
            goto ReturnErrorStatus;
        }
    }

    PROGRESS_CODE(DXE_LEGACY_OPROM_INIT);

    //
    // Check for the room in shadow for this ROM and copy it from RomLocation.
    //
    {
        UINTN SizeInShadow = is30ROM? Rom30Size : RomSize;
        UINTN CopyToAddress = is30ROM? (UINTN)Rom30Address : (UINTN)gNextRomAddress;

        if(((UINTN)(gNextRomAddress) + SizeInShadow) > OPROM_MAX_ADDRESS){
            if (CsmPlatformProtocol) {
                PostProcessOpRom(CsmPlatformProtocol, PciIo, RomImage);
            }
            TRACE(((UINTN)TRACE_ALWAYS,"Can not execute PCI OPROM: out of resources. RomAddr %x RomSize %x\n", gNextRomAddress, SizeInShadow));
            Status = EFI_OUT_OF_RESOURCES;
            DEVICE_ERROR_CODE(DXE_LEGACY_OPROM_NO_SPACE, EFI_ERROR_MAJOR, PciHandle);
            goto ReturnErrorStatus;
        }

        Status = UnlockShadow(gNextRomAddress, SizeInShadow, &LockUnlockAddr, &LockUnlockSize);
        ASSERT_EFI_ERROR(Status);

        //
        // Initilize the size field to 0.
        //
        ((LEGACY_OPT_ROM_HEADER*)gNextRomAddress)->Size512=0;
        pBS->CopyMem((VOID*)CopyToAddress, RomLocation, RomSize);
    }

	DiskFrom = *(UINT8*)(UINTN)0x475 + 0x80;

    Csm16DOT = &CoreBiosInfo->Thunk->DispatchOpromTable;
    Csm16DOT->PnpInstallationCheckSegment = CoreBiosInfo->Csm16Header->PnPInstallationCheckSegment;
    Csm16DOT->PnpInstallationCheckOffset = CoreBiosInfo->Csm16Header->PnPInstallationCheckOffset;
    if (is30ROM) {
        Csm16DOT->OpromSegment = (UINT16)(Shr64(Rom30Address, 4));
        Csm16DOT->FinalLocationSegment = (UINT16)((UINTN)gNextRomAddress >> 4);
    }
    else {
        Csm16DOT->OpromSegment = (UINT16)((UINTN)gNextRomAddress >> 4);
        Csm16DOT->FinalLocationSegment = 0;
    }

    Csm16DOT->PciBus = (UINT8)PciBus;
    Csm16DOT->PciDeviceFunction = (UINT8)(PciDeviceNumber << 3 | PciFunction);
    Csm16DOT->NumberBbsEntries = CoreBiosInfo->BbsEntriesNo;
	Csm16DOT->BbsTable = (UINT32)(UINTN)(CoreBiosInfo->BbsTable);

    TRACE((TRACE_ALWAYS, "OptionROM for B%x/D%x/F%x is executed from %x:0003\n",
            PciBus, PciDeviceNumber, PciFunction, Csm16DOT->OpromSegment));

    // Save INT18 and INT19 to be able to see its trapping after ROM execution
    Int19 = ivt[0x19];
    Int18 = ivt[0x18];

    Status = CsmInstallRom(CoreBiosInfo, PciHandle,
                Csm16DOT, (UINTN)gNextRomAddress, IsVga, &NewRomSize, &ProcessBootDevices);

    Int19Trapped = Int19 != ivt[0x19];

    if (ProcessBootDevices) {
            FetchBbsBootDevices(CoreBiosInfo,
                gNextRomAddress,
                PciCfgData,
                PciBus,
                PciDeviceNumber,
                PciFunction,
                &DiskFrom,
                Int18 != ivt[0x18],
                Int19 != ivt[0x19]);
    }

    // Restore INT18 and INT19
    ivt[0x18] = Int18;
    ivt[0x19] = Int19;

    DiskTo = (DiskFrom & 0xc0) + *(UINT8*)(UINTN)0x475; 

    if (CsmPlatformProtocol) {
        PostProcessOpRom(CsmPlatformProtocol, PciIo, RomImage);
    }

    if (is30ROM) {
    //
    // For PCI3.0 do necessary things with Setup Routine here, then
    // free Rom30Address memory
    //
        pBS->FreePages(Rom30Address, LowMem4KPages);
    }

    if (!is30ROM) {
        if (RomSize > NewRomSize) {
            pBS->SetMem(gNextRomAddress+NewRomSize, RomSize-NewRomSize, 0xFF);
        }
    }
    Status = LockShadow(LockUnlockAddr, LockUnlockSize);
    ASSERT_EFI_ERROR(Status);

    //
    // Make the rom size 2K aligned
    //
    if (NewRomSize % 0x800) {
        NewRomSize += (0x800 - (NewRomSize % 0x800));
    }

    //
    // Return OPTIONAL parameters: updated disks, oprom address and size.
    //
    if (DiskStart) *DiskStart = DiskFrom;
    if (DiskEnd) *DiskEnd = DiskTo;
    if (RomShadowAddress) *RomShadowAddress = gNextRomAddress;
    if (ShadowedRomSize) *ShadowedRomSize = NewRomSize;

    //
    // Update the list of Executed Roms
    //
    if (PciHandle) {
        gExecutedRomsPci->Seg = PciSegment;
        gExecutedRomsPci->Bus = PciBus;
        gExecutedRomsPci->Dev = PciDeviceNumber;
        gExecutedRomsPci->Fun = PciFunction;
        gExecutedRomsPci->Flags = *Flags;
        gExecutedRomsPci->DiskFrom = DiskFrom;
        gExecutedRomsPci->DiskTo = DiskTo;
        gExecutedRomsPci->RomAddress = gNextRomAddress;
        gExecutedRomsPci->RomSize = NewRomSize;
        gExecutedRomsPci++;
    }
TRACE((TRACE_ALWAYS, "PCI OPROM(handle %x, %x/%x/%x): addr %x, size %x\n",
            PciHandle, PciBus, PciDeviceNumber, PciFunction, gNextRomAddress, NewRomSize));
    gNextRomAddress += NewRomSize;

    if (Int19Trapped && !IsVga && (gSetup.I19Trap == 1))
    {
        if (gSetTxtMode == 1)
        {
			if (gVgaHandle != NULL) 
			{
	            TRACE((-1, "Reconnecting video and serial before calling INT19 trap.\n"));
	            pBS->DisconnectController(gVgaHandle, NULL, NULL);
	            pBS->ConnectController(gVgaHandle, NULL, NULL, TRUE);
	            ConnectSerialIO();
			}
			UnlockConsole();
        }

        // Signal READY_TO_BOOT event
        {
            EFI_EVENT ReadyToBootEvent;
            Status = CreateReadyToBootEvent(
                TPL_CALLBACK, NULL, NULL, &ReadyToBootEvent
            );
            if (!EFI_ERROR(Status)) {
                pBS->SignalEvent(ReadyToBootEvent);
                pBS->CloseEvent(ReadyToBootEvent);
            }
        }

        LegacyBoot (
            &CoreBiosInfo->iBios,
            &(DummyLoadOption.BbsDevicePath),
            sizeof(DummyLoadOption),
            &DummyLoadOption
        );
        ASSERT(FALSE);  // CONTROL MUST NOT BE GIVEN BACK HERE
        // If by any chance we are here, we have to do the needful:
        pRS->ResetSystem(EfiResetCold, EFI_SUCCESS, 0, NULL);
    }

    return EFI_SUCCESS;

ReturnErrorStatus:
    if (LowMem4KPages != 0) {
        pBS->FreePages(Rom30Address, LowMem4KPages);
    }
    return Status;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
//  Name:        GetShadowRamAddress
//
//  Description:
//      Returns the available shadow RAM address out of the given range.
//
//  Input:
//      UINT32    *AddrMin      Min address
//      UINT32    AddrMax       Max address
//      UINT32    Size          Range size, in Bytes
//      UINT32    Alignment     Range alignment
//
//  Output:
//      EFI_SUCCESS             AddrMin variable contains the available address
//      EFI_OUT_OF_RESOURCES    The requested memory range is not available in
//                              the shadow RAM
//  Notes:
//      This function does not reserve or allocate memory in the shadow RAM
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS
GetShadowRamAddress(
    IN OUT UINT32   *AddrMin,
    IN UINT32       AddrMax,
    IN UINT32       Size,
    IN UINT32       Alignment
)
{    
	UINT32  Addr = *AddrMin;
	UINT32  Aln;
	
	if (Addr > AddrMax) return EFI_INVALID_PARAMETER;
	if (Size == 0x00) return EFI_INVALID_PARAMETER;
	if (Alignment > OPROM_MAX_ADDRESS) return EFI_INVALID_PARAMETER;
	if (AddrMax + Size > (OPROM_MAX_ADDRESS + 1)) return EFI_OUT_OF_RESOURCES;
	if (AddrMax < (UINT32)(UINTN)gNextRomAddress) return EFI_OUT_OF_RESOURCES;
	
	if(Alignment != 0) Alignment--;
    Aln = ~Alignment;
	
	if (Addr < (UINT32)(UINTN)gNextRomAddress) {
        Addr = (UINT32)(UINTN)gNextRomAddress;
    }

	if ((Alignment !=0) && (Addr & Aln)) {
		if ( (Addr & Aln) != Addr){
			Addr += (Alignment+1);
			Addr &= Aln;
            
		}
    }
	gNextRomAddress = (UINT8 *)(Addr + Size);
	*AddrMin = Addr;

return EFI_SUCCESS;
}



//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Name:        InstallIsaRom
//
// Description: Executes ISA Option ROM
//
// Input:
//  This        Indicates the EFI_LEGACY_BIOS_PROTOCOL instance.
//  RomAddress  Location of the Option ROM
//
// Output:
//  EFI_SUCCESS             ROM was successfully executed
//  EFI_OUT_OF_RESOURCES    Shadow RAM full, ROM was not executed
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS
InstallIsaRom(
    IN EFI_LEGACY_BIOS_EXT_PROTOCOL *This,
    IN UINTN    RomAddress
)
{
    UINTN       RomSize;
    BOOLEAN     ProcessBootDevices;
    EFI_STATUS  Status;
    EFI_DISPATCH_OPROM_TABLE *Csm16DOT;
    EFI_LEGACY_BIOS_PROTOCOL    *LegacyBios;
    BIOS_INFO   *CoreBiosInfo;
    CSM_PLATFORM_PROTOCOL *CsmPlatformProtocol;
    UINT8       PciCfgData[0x40] = {0};
    UINT8       DiskFrom = 0x80;
    volatile UINT32 *ivt = (UINT32*)0;
    UINT32      Int18;
    UINT32      Int19;

    // Validate ISA ROM
    if (((LEGACY_OPT_ROM_HEADER*)RomAddress)->Signature != 0xAA55) {
        TRACE((-1, "Can not execute ISA ROM: missing 0xAA55 signature.\n"));
        return EFI_UNSUPPORTED;
    }

    // See if ROM fits in the shadow
    RomSize = ((LEGACY_OPT_ROM_HEADER*)RomAddress)->Size512 << 9;
	if((RomAddress + RomSize) > OPROM_MAX_ADDRESS) {
        TRACE((-1, "Can not execute ISA ROM: won't fit in the shadow memory.\n"));
        return EFI_OUT_OF_RESOURCES;
    }

    // Get BIOS_INFO variable pointer
    Status = pBS->LocateProtocol(&gEfiLegacyBiosProtocolGuid, NULL, &LegacyBios);
    ASSERT_EFI_ERROR(Status);
    CoreBiosInfo = (BIOS_INFO*)LegacyBios;

    //
    // Execute platform pre-OpROM function
    //
    Status = pBS->LocateProtocol(&gCsmPlatformProtocolGuid, NULL, &CsmPlatformProtocol);

    if (!EFI_ERROR(Status)) {
        Status = PreProcessOpRom(CsmPlatformProtocol,  NULL, (VOID*)&RomAddress);
        if (EFI_ERROR(Status)) {
            PostProcessOpRom(CsmPlatformProtocol,  NULL, (VOID*)&RomAddress);
            return Status;
        }
    }

	DiskFrom = *(UINT8*)(UINTN)0x475 + 0x80;

    Csm16DOT = &CoreBiosInfo->Thunk->DispatchOpromTable;
    Csm16DOT->OpromSegment = (UINT16)(RomAddress >> 4);
    Csm16DOT->NumberBbsEntries = CoreBiosInfo->BbsEntriesNo;
	Csm16DOT->BbsTable = (UINT32)(UINTN)(CoreBiosInfo->BbsTable);

    TRACE((TRACE_ALWAYS, "OptionROM for ISA Device is executed from %x:0003\n", Csm16DOT->OpromSegment));

    // Save INT18 and INT19 to be able to see its trapping after ROM execution
    Int19 = ivt[0x19];
    Int18 = ivt[0x18];

    Status = CsmInstallRom(CoreBiosInfo, NULL,
                Csm16DOT, RomAddress, FALSE, NULL, &ProcessBootDevices);

    if (ProcessBootDevices) {
            FetchBbsBootDevices(CoreBiosInfo,
                (UINT8*)RomAddress,
                PciCfgData,
                0,
                0,
                0,
                &DiskFrom,
                Int18 != ivt[0x18],
                Int19 != ivt[0x19]);
    }

    // Restore INT18 and INT19
    ivt[0x18] = Int18;
    ivt[0x19] = Int19;

    if (CsmPlatformProtocol) {
        PostProcessOpRom(CsmPlatformProtocol, NULL, (VOID*)&RomAddress);
    }

    return Status;
}


//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Name:        ShadowAllLegacyOproms
//
// Description: Allows external agents to force loading of all legacy OpROMs.
//              This function can be invoked before GetBbsInfo() to ensure all
//              devices are counted.
// Input:
//  This        Indicates the EFI_LEGACY_BIOS_PROTOCOL instance.
//
// Output:
//  EFI_SUCCESS OpROMs are shadowed successfully.
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS
ShadowAllLegacyOproms (
    IN EFI_LEGACY_BIOS_PROTOCOL *This
)
{
    EFI_HANDLE  *HandleBuffer;
    UINTN       n, HandleCount;
    EFI_STATUS  Status;
    EFI_PCI_IO_PROTOCOL *PciIo;
    BIOS_INFO   *CoreBiosInfo = (BIOS_INFO*)This;
    UINT64      Capabilities;
    UINTN       Flags;
    UINT8       dData[4];

    //
    // Locate all PciIo handles
    //
    Status = pBS->LocateHandleBuffer (
        ByProtocol,
        &gEfiPciIoProtocolGuid,
        NULL,
        &HandleCount,
        &HandleBuffer);

    ASSERT_EFI_ERROR(Status);
    if (EFI_ERROR (Status)) {
        return Status;
    }

    for (n = 0; n < HandleCount; n++) {
        Status = pBS->HandleProtocol (HandleBuffer[n], &gEfiPciIoProtocolGuid, &PciIo);
        ASSERT_EFI_ERROR(Status);

        if (PciRomAlreadyExecuted(PciIo)) continue;

        //
        // Skip the VGA devices: the active VGA controller might have
        // been already enabled, all other VGA controllers have to be disabled.
        //
        if (CoreBiosInfo->hVga != NULL) {
            Status = PciIo->Pci.Read(
                PciIo,
                EfiPciIoWidthUint32,
                8,  // offset
                1,  // width
                &dData);
            ASSERT_EFI_ERROR(Status);
            if (dData[3]==PCI_CL_DISPLAY) continue;
        }

        //
        // See if device has OpROM, if so - enable device and istlall OpROM; assume
        // CSM has already assinged IRQ and programmed IRQ router and register 3C
        //
        Status = CheckPciRom(This, HandleBuffer[n], NULL, NULL, &Flags);
        if (EFI_ERROR(Status) || (Flags != 2)) continue;    // No OpROM or OpROM is invalid

        Status = PciIo->Attributes (PciIo,
                EfiPciIoAttributeOperationSupported, 0,
                &Capabilities);     // Get device capabilities
        ASSERT_EFI_ERROR(Status);

        Status = PciIo->Attributes (PciIo,
                EfiPciIoAttributeOperationEnable,
                Capabilities & EFI_PCI_DEVICE_ENABLE,
                NULL);              // Enable device

        if (EFI_ERROR(Status)) continue;

        InstallPciRom(This,
                HandleBuffer[n], NULL, &Flags,
                NULL, NULL, NULL, NULL);
    }
    pBS->FreePool(HandleBuffer);	

    if (!gServiceRomsExecuted) {
        //
        // Launch service ROMs
        //
        Status = CoreBiosInfo->iBiosPlatform->PlatformHooks(
                    CoreBiosInfo->iBiosPlatform,
                    EfiPlatformHookShadowServiceRoms,
                    0, NULL, NULL, NULL, NULL);
        gServiceRomsExecuted = TRUE;
    }

    return EFI_SUCCESS;
}

EFI_STATUS
PreProcessOpRom(
    CSM_PLATFORM_PROTOCOL   *CsmPlatformProtocol,
    EFI_PCI_IO_PROTOCOL     *PciIo,
    VOID                    **RomImage
)
{
    EFI_STATUS Status;

    if (gVgaHandle == NULL)
    {
        BOOLEAN IsVga = FALSE;

        if (PciIo != NULL)
        {
            UINT8 PciCfgData[4];
            EFI_STATUS Status;
            
            Status = PciIo->Pci.Read(
                PciIo,
                EfiPciIoWidthUint8,
                8,   // offset
                4,   // width
                PciCfgData);
            ASSERT_EFI_ERROR(Status);
    
            if (PciCfgData[3]==PCI_CL_OLD && PciCfgData[2]==PCI_CL_OLD_SCL_VGA) {
                IsVga = TRUE;
            }
            if (PciCfgData[3]==PCI_CL_DISPLAY && PciCfgData[2]==PCI_CL_DISPLAY_SCL_VGA) {
                IsVga = TRUE;
            }
        }
        if (!IsVga)
            gSetTxtMode = 2;
    }

    Status = CsmPlatformProtocol->PreProcessOpRom(CsmPlatformProtocol, PciIo, RomImage);

#if LEGACYSREDIR_SUPPORT
    if(gLegacySredir == NULL) {
        pBS->LocateProtocol (
            &gEfiLegacySredirProtocolGuid,
            NULL,
            &gLegacySredir
            );
    }
    if(gLegacySredir != NULL) {	
        gLegacySredir->EnableLegacySredir(gLegacySredir);
    }
#endif
    return Status;
}

EFI_STATUS
PostProcessOpRom(
    CSM_PLATFORM_PROTOCOL   *CsmPlatformProtocol,
    EFI_PCI_IO_PROTOCOL     *PciIo,
    VOID                    **RomImage
)
{
    EFI_STATUS Status;
    Status = CsmPlatformProtocol->PostProcessOpRom(CsmPlatformProtocol, PciIo, RomImage);

#if LEGACYSREDIR_SUPPORT
    if(gLegacySredir == NULL) {
        pBS->LocateProtocol (
            &gEfiLegacySredirProtocolGuid,
            NULL,
            &gLegacySredir
            );
    }
    if(gLegacySredir != NULL) {	
        gLegacySredir->DisableLegacySredir(gLegacySredir);
    }
#endif
    return Status;
}

//**********************************************************************
//**********************************************************************
//**                                                                  **
//**        (C)Copyright 1985-2010, American Megatrends, Inc.         **
//**                                                                  **
//**                       All Rights Reserved.                       **
//**                                                                  **
//**           5555 Oakbrook Pkwy, Suite 200, Norcross, GA 30093      **
//**                                                                  **
//**                       Phone: (770)-246-8600                      **
//**                                                                  **
//**********************************************************************
//**********************************************************************
