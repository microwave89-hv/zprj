//**********************************************************************
//**********************************************************************
//**                                                                  **
//**        (C)Copyright 1985-2014, American Megatrends, Inc.         **
//**                                                                  **
//**                       All Rights Reserved.                       **
//**                                                                  **
//**         5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093     **
//**                                                                  **
//**                       Phone: (770)-246-8600                      **
//**                                                                  **
//**********************************************************************
//**********************************************************************

//**********************************************************************
// $Header: /Alaska/SOURCE/Modules/AHCI/AhciBus.c 74    6/25/14 10:01a Anandakrishnanl $
//
// $Revision: 74 $
//
// $Date: 6/25/14 10:01a $
//**********************************************************************
// Revision History
// ----------------
// $Log: /Alaska/SOURCE/Modules/AHCI/AhciBus.c $
// 
// 74    6/25/14 10:01a Anandakrishnanl
// [TAG]  		EIP170118
// [Category]  	Bug Fix
// [Severity]  	Normal
// [Symptom]  	MDAT can't program correctly in AHCI module
// [RootCause]  	Identify Data Word 76_79 Offset for DiPM Support/Enabled
// is incorrect for validation
// [Solution]  	Changed separating DiPM and Device Sleep into two routines
// and also modified the tokens to disable both support by default .
// Corrected Identify data validations.
// [Files]  		  AhciBus.c
//   AhciBus.h
//   AhciSrc.sdl
//   PAhciBus.h
//   PIDEBus.h 
// 
// 73    6/09/14 9:56a Anbuprakashp
// [TAG]  		EIP172443
// [Category]  	Improvement
// [Description]  	"RaidDriverBlockingStatus" is using
// gEfiGlobalVariableGuid that violates UEFI 2.4 spec in
// IdeSecurityBdsCall.c and Runtime attribute set of this variable need to
// be removed
// [Files]  		IdeSecurityBdsCall.c, AhciBus.c
// 
// 72    1/27/14 4:55a Rameshr
// [TAG]  		EIP148180
// [Category]  	Improvement
// [Description]  	change from EFI_MBR_WRITE_PROTECTION_PROTOCOL to
// AMI_BLOCKIO_WRITE_PROTECTION_PROTOCOL
// [Files]  		Ahcibus.c, Ahcibus.h, AhciComponentName.c, AhciController.c
// 
// 71    1/13/14 4:26a Rameshr
// [TAG]  		EIP147909
// [Category]  	Bug Fix
// [Severity]  	Important
// [Symptom]  	Boot devices can not find after resume from s4
// [RootCause]  	HddPassword Verification failed because of
// gHddSecurityEndProtocolGuid is uninstalled on the controller handle
// [Solution]  	If the gHddSecurityEndProtocolGuid protocol is already
// installed , to signel the event Reinstall Protocol interface is done
// instead of uninstalling the protocol interface.
// [Files]  		Ahcibus.c
// 
// 70    12/20/13 4:06a Rameshr
// [TAG]  		EIP126640
// [Category]  	Improvement
// [Description]  	AHCIBUS driver need to preserve the port settings in
// GeneratePortReset
// [Files]  		Ahcibus.c, AhciController.c
// 
// 69    12/18/13 3:17a Srikantakumarp
// [TAG]  		EIP127356
// [Category]  	Improvement
// [Description]  	Flash NVRAM seems to cause HDD can't be unlocked when
// S3 resume.
// [Files]  		IdeSecurity.c, IDESMM.c, HddPassword.c, AhciBus.c, AhciBus.h
// 
// 68    12/02/13 5:46a Anbuprakashp
// [TAG]  		EIP138377
// [Category]  	Improvement
// [Description]  	"CR has Bad Signature" error on AHCI eModule when
// "disconnect -r" from shell
// [Files]  		AhciBus.c
// 
// 67    9/26/13 2:22a Rameshr
// [TAG]  		EIP128963
// [Category]  	Improvement
// [Description]  	Uninitilized variable cleaned up in AhciBus Stop
// function.
// [Files]  		Ahcibus.c
// 
// 66    9/26/13 2:10a Rameshr
// [TAG]  		EIP125006
// [Category]  	Improvement
// [Description]  	Dummy Protocol installed for the protocol event
// signaling is uninstalled. So that Ahcibus driver can signal the event
// again if the bus driver gets starts again.
// [Files]  		Ahcibus.c
// 
// 65    8/27/13 4:19a Rameshr
// [TAG]  		EIP125560
// [Category]  	Improvement
// [Description]  	MbrWriteProtectionProtocol file name changesd to
// AmiMbrWriteProtectionProtocol.h
// [Files]  		AhciController.c, AhciBus.h, Ahcibus.c
// 
// 64    8/22/13 2:52a Srikantakumarp
// [TAG]  		EIP106423
// [Category]  	Improvement
// [Description]  	Correcting the previous changes.
// [Files]  		AhciBus.c
// 
// 63    7/23/13 11:52p Srikantakumarp
// [TAG]  		EIP129989
// [Category]  	Improvement
// [Description]  	Added DIPM support in Aptio 4.x AHCIBUS driver.
// [Files]  		AhciBus.c, AhciBus.h, AhciController.h, AhciSrc.sdl,
// PAhciBus.h
// 
// 62    7/22/13 2:05a Rameshr
// [TAG]  		EIP129028
// [Category]  	Improvement
// [Description]  	Implement the POWERUP_IN_STANDBY_MODE support in
// AHCIBUS driver
// [Files]  		Ahcibus.c, Ahcibus.h, Pahcibus.h
// 
// 61    7/18/13 4:21a Rameshr
// [TAG]  		EIP127919
// [Category]  	Improvement
// [Description]  	"Device is Atapi" bit of PxCMD will be set if the ATAPI
// device connected on the Port and "Drive LED on ATAPI" Enabled by AHCI
// platform policy
// [Files]  		Pahcibus.h, Ahcibus.c, Ahcibus.h
// 
// 60    7/01/13 4:31a Kapilporwal
// [TAG]  		EIP125560
// [Category]  	Improvement
// [Description]  	 	Please support Boot Sector Virus Protection for CSM
// Disabled Mode
// [Files]  		VirusProtect.c, VirusProtect.dxs, AhciBus.c,
// AhciController.c, CsmBlockIo.c, CsmInt13.c, Ata.c, IdeBus.c,
// SdioBlkIo.c, SdioDriver.c, efiusbmass.c
// 
// 59    6/06/13 4:22a Rameshr
// [TAG]  		EIP106423
// [Category]  	Improvement
// [Description]  	HddPassword Support in UEFI Raid and Legacy Raid. And
// also taken care where there is no Conin Device avilable in the post
// [Files]  		IdeSecurity.cif,IdeSecurity.sdl,IdeSecurity.mak,IdeSecurityB
// dsCall.c,HddPassword.c, Ahcibus.c, Pidebus.h
// 
// 58    6/06/13 2:30a Rameshr
// [TAG]  		EIP119759
// [Category]  	Improvement
// [Description]  	Ahcibus driver should not be stated when the Idebus
// driver is active on the SATA Controller  
// [Files]  		Ahcibus.c
// 
// 57    3/25/13 4:55a Rameshr
// [TAG]  		EIP118033
// [Category]  	Improvement
// [Description]  	If the device is not yet detected in the remaining
// device path port, proceed for the device detection and configuration.
// 
// [Files]  		Ahcibus.c
// 
// 56    2/11/13 12:35a Rameshr
// [TAG]  		EIP114276
// [Category]  	Improvement
// [Description]  	Error in AHCIBus Driver when Power management and HPA
// support is turned on. Removed the unused Power mangement and HPA code
// from Ahcibus driver
// [Files]  		Ahcibus.c
// 
// 55    10/18/12 5:36a Srilathasc
// [TAG]  		EIP95446
// [Category]  	Bug Fix
// [Severity]  	Minor
// [Symptom]  	Diskinfo Identify function returns the invalid Identify
// data after post
// [RootCause]  	DiskInfoIdentify function copies the identify data from
// buffer.
// 
// [Solution]  	DiskInfoIdentify function should send command and get
// identify data.
// [Files]  		IdeBus.c, AhciBus.c
// 
// 54    9/17/12 1:49a Anandakrishnanl
// [TAG]  		EIP100891
// [Category]  	Bug Fix
// [Severity]  	Important
// [Symptom]  	PortFISBaseAddr and PortCommandListBaseAddr allocation to
// support memory allocation above 4gb
// [RootCause]  	System hangs in Ahci Mode > 4Gb memory allocation, With
// Filesystem and UEFI Boot Failing
// [Solution]  	Fixed by handling FIS and Command List base Address
// allocation >4gb allocation
// [Files]  		AhciBus.c
// 
// 53    9/17/12 12:48a Rameshr
// [TAG]  		EIP100335
// [Category]  	Improvement
// [Description]  	Port Multiplier spend long time to connect device.
// [Files]  		Ahcibus.c, AhciController.c
// 
// 52    9/10/12 2:48a Rameshr
// [TAG]  		EIP95440
// [Category]  	Improvement
// [Description]  	Add HddSecurity and HddSmart feature under UEFI Raid
// driver mode
// [Files]  		Ahcibus.c, Pahcibus.h, Aint13.c
// 
// 51    9/03/12 6:07a Rameshr
// [TAG]  		EIP94991
// [Category]  	Improvement
// [Description]  	If the link is already established before setting up
// the allowed port speed, current interface speed has not been set based
// on the port speed allowed. ComReset has been issued to setup the
// current interface speed according to the port speed allowed. 
// [Files]  		Ahcibus.c
// 
// 50    8/21/12 2:13a Rameshr
// [TAG]  		EIP98436
// [Category]  	Bug Fix
// [Severity]  	Important
// [Symptom]  	FISAddress is being set incorrrectly.
// [RootCause]  	Before setting the FIS Address, it has been used in
// GeneratePortReset function.
// [Solution]  	Moveed the FIS base address and command list base address
// programming before GeneratePortReset 
// [Files]  		Ahcibus.c
// 
// 49    8/16/12 3:05a Rajeshms
// [TAG]  		EIP97048
// [Category]  	New Feature
// [Description]  	ATAPI PassThru Support using
// EFI_EXT_SCSI_PASS_THRU_PROTOCOL.
// [Files]  		AhciBus.c, AhciController.c, IdeBus.c, Atapi.c, PIDEBus.h,
// PAhciBus.h, ScsiPassThruAtapi.sdl, ScsiPassThruAtapi.mak,
// ScsiPassThruAtapi.c, ScsiPassThruAtapiSupport.h, ScsiPassThruAtapi.chm,
// ScsiPassThruExt.h
// 
// 48    8/16/12 2:27a Anandakrishnanl
// [TAG]  		EIP97113
// [Category]  	Improvement
// [Description]  	AtaPassThru - Module Enhancement
// [Files]  		AtaPassThru.c,
// AtaPassThruSupport.h,AtaPassThru.mak,IdeBus.c,AhciBus.c
// 
// 47    7/20/12 6:09a Anandakrishnanl
// [TAG]  		EIP88683
// [Category]  	New Feature
// [Description]  	EFI_ATA_PASS_THRU_PROTOCOL Support for Aptio IDE
// [Files]  		AhciBus.c
// AhciBus.h
// AInt13.h
// IdeBus.c
// IdeBus.h
// PIDEBus.h
// PAhciBus.h
// AtaPassThru.sdl
// AtaPassThru.mak	
// AtaPassThru.c	
// AtaPassThruSupport.h
// AtaPassThru.chm
// 
// 46    11/03/11 5:44a Rajeshms
// [TAG]  		EIP73249
// [Category]  	Improvement
// [Description]  	AHCI Driver Follow the UEFI Driver Model as per the
// UEFI Spec. and STOP function was Verified.
// [Files]  		AhciBus.c
// 
// 45    10/11/11 2:21a Rameshr
// [TAG]  		EIP71410
// [Category]  	Bug Fix
// [Severity]  	Important
// [Symptom]  	10 seconds Delay in post if ODD with CD/DVD
// [RootCause]  	ATA Specific commands are executed for ATAPI devices
// also.
// [Solution]  	ATA device check added before sending the command.
// [Files]  		Ahcibus.c
// 
// 44    9/19/11 3:03a Lavanyap
// [TAG]  		EIP69398
// [Category]  	Bug Fix
// [Severity]  	Minor
// [Symptom]  	Function ConfigureController() has a runtime error (NULL
// pointer dereference)
// [RootCause]  	variable SupportedModes has been initialized again in
// ConfigureController().
// [Solution]  	variable SupportedModes is passed as an input parameter
// for ConfigureController() and ConfigureDevice().
// [Files]  		AhciBus.c, AhciBus.h
// 
// 43    8/02/11 4:34a Rameshr
// [TAG] - EIP 61076
// [Category]- IMPROVEMENT
// [Description]- Setting the Interface Speed Support in CAP.ISS. so that
// it's get programmed in PxSCT[7:4]. For this programming the link
// communication should not be established. If it's already established we
// should use GeneratePortReset function to set the speed
// [Files] - AhciBus.c
// 
// 42    7/05/11 2:50a Anandakrishnanl
// [TAG]  		EIP56530 
// [Category]  	Improvement
// [Description]  	EFI_IDE_CONTROLLER_INIT_PROTOCOL and
// EFI_DISK_INFO_PROTOCOL are used accordingly to the PI 1.2 spec
// [Files]  		AhciBus.c, IdeControllerInit.h, PDiskInfo.h
// 
// 41    6/14/11 5:48a Rameshr
// [TAG]- EIP 59495
// [Category]-IMPROVEMENT
// [Description]- Update implementation of EFI_BLOCK_IO_PROTOCOL as
// described in UEFI specification v 2.3.1, page 12.8
// [Files]- AhciBus.c 
// 
// 40    5/19/11 3:12a Anandakrishnanl
// [TAG]  		EIP53565
// [Category]  	New Feature
// [Description]  	UEFI2.3+ Specifications defines Storage Security
// protocol which needs to be implemented.
// [Files]  		AhciBus.c,IdeBus.c,AHCIOpalSec.c,IDEOpalSec.c,OpalSecurity.c
// ,OpalSecurity.chm,OpalSecurity.cif,OpalSecurity.h,OpalSecurity.mak,Opal
// Security.sdl,PIDEBus.h,StorageSecurityProtocol.CIF,StorageSecurityProto
// col.h
// 
// 39    2/18/11 5:04a Rameshr
// [TAG]- EIP 37975
// [Category]-IMPROVEMENT
// [Description]- Klocwork Issues II - IDE/Ahci module
// [Files]- AhciBus.c, AhciController.c 
// 
// 38    2/11/11 4:22a Rameshr
// [TAG]  		EIP53730
// [Category]  	Improvement
// [Description]  	Add Odd Loading type information into ATAPI_DEVICE
// structure in AHCI mode
// [Files]  		AhciBus.c
// AhciController.c
// AhciBus.h
// 
// 37    2/10/11 10:35a Rameshr
// [TAG]  		EIP53704
// [Category]  	Improvement
// [Description]  	AMI headers update for Alaska Ahci Driver
// [Files]  		AhciSrc.mak
// AhciBus.c
// AhciController.c
// AhciComponentName.c
// AhciBus.h
// AhciController.h
// 
// 36    12/30/10 3:48a Rameshr
// [TAG] - EIP 49229
// [Category]- BUG FIX
// [Severity]- Minor
// [Symptom] - SATA interface setting (SATA speed)
// [RootCause]- Read the SATA device speed from the Capabilities Register
// and set it to Port Control speed Register
// [Solution] - Read the SATA device speed from the Capabilities Register
// and set it to Port Control speed Register.
// [Files] - AhciBus.c
// 
// 35    12/23/10 3:58a Lavanyap
// [TAG] - EIP41445
// [Category] - NEW FEATURE
// [Description] - Created SataPioDataOut and AtaPioDataOut protocol
// function that can accept additional input parameters.
// [Files] - AhciBus.h, AhciBus.c, AhciController.c, Ata.c, IdeBus.c,
//           IdeBus.h, IdeBusMaster.c,PAhciBus.h, PIdeBus.h
// 
// 34    11/25/10 7:09a Rameshr
// 
// [TAG] - EIP 48045
// [Category]- BUG FIX
// [Severity]- Minor
// [Symptom] - DISABLE_SOFT_SET_PREV sdl token set 1 , throws build error
// in AHCI driver.
// [RootCause]- Status Variable not declared 
// [Solution] - Declared the Status variable. 
// [Files] - Ahcibus.c
// 
// 33    11/02/10 12:03a Rameshr
// [TAG] - EIP 45266
// [Category]- BUG FIX
// [Severity]- Minor
// [Symptom] - E-SATA card will hang up on post and debug card show "AE
// [RootCause]- Device doesn't support any of the UDMA mode and function
// ReturnMsbbit returns incorrect values 
// [Solution] - If any of the bit is not set in Input value, ReturnMsbbit
// returns 0xFF.
// [Files] - Ata.c, AhciBus.c
// 
// 32    10/11/10 6:28p Krishnakumarg
// [TAG] - EIP 44800
// [Category] - Defect
// [Severity] - Major
// [Symptom]  - Side Effect of EIP 40528. HDD security setup option
// disappear on warn boot in AHCI mode.
// [RootCause]- When FORCE_HDD_PASSWORD_PROMPT token enabled,Software
// preservation is disabled only when password is enabled.
// [Solution] - Software preservation is disabled when HDD can support
// software preservation.
// [Files] - AhciBus.c
// 
// 31    9/24/10 2:40a Rameshr
// [TAG]- EIP 42817
// [Category]-IMPROVEMENT
// [Description]- Ide Smart checks HDDs for errors moved after Idebus
// Device path has been installed.
// [Files]- AhciBus.c, IdeBus.c
// 
// 30    5/26/10 6:21a Rameshr
// Checked the Device Configuration Overlay feature set supported status
// before sending the DEV_CONFIG_FREEZE_LOCK 
// EIP 38384
// 
// 29    5/07/10 11:44a Krishnakumarg
// Coding standard update
// 
// 28    4/16/10 4:15p Pats
// EIP 30719: Support for the HDD with sector size more than 512bytes.
// 
// 27    3/26/10 5:35p Krishnakumarg
// UEFI2.1 compliance change EIP#34744.
// 
// 26    2/15/10 5:51p Srinin
// KlockWork flags "'SupportedModes' is explicitly dereferenced.". Fix
// added.
// 
// 25    2/11/10 4:00a Rameshr
// Atapi devices are handled by AhciBus driver based on
// SUPPORT_ATAPI_IN_RAID_MODE SDL token.
// EIP 34583
// 
// 24    1/11/10 12:12p Krishnakumarg
// Update for Eip 11835 - To implement Acoustic Management function
// EIP 30041 - Aptio 4 Device Initiated Power Management (DipM) support
// for SATA devices
// 
// 23    10/15/09 11:46p Fasihm
// EIP#28961:  Corrected the Disk Info Protocol installation information,
// and corrected it from EFI_BLOCK_IO_PROTOCOL to EFI_DISK_INFO_PROTOCOL.
// 
// 22    9/22/09 10:57a Krishnakumarg
// Code modified to update SataDevInterface->identifydata in
// GetIdentifyData function instead of returning in global variable -
// EIP26411
// 
// 21    9/04/09 3:32p Krishnakumarg
// Coding Standard and unwanted code removal in InitAcousticSupport
// function
// 
// 20    9/04/09 3:16p Krishnakumarg
// Acoustic Management function updated to set acoustic level according to
// setup option EIP:11835
// 
// 19    8/18/09 2:04p Rameshr
// AhciBus driver doesn't work for Multi Entry.
// Ahci Int13 initilization code moved from AhciBus to CsmHwinfo.c
// EIP: 25369
// 
// 18    8/17/09 2:55p Rameshr
// AHCI bus driver doesn't detect the devices other than port 0 when the
// remaining device path is not null
// EIP:25368
// 
// 17    7/13/09 3:37p Rameshr
// Symptom: After installing the UEFI windows 7 and reboot, system hangs
// on post.
// Rootcause: Devicepath created with NULL when the Remainingdevicepath
// has valid value. 
// Solution: Created the Devicepath even if the RemainingDevicePath has
// the valid value.
// 
// 16    6/22/09 11:33a Rameshr
// Odd Type information Saved in Atapi Device Structure.
// EIP:21548
// 
// 15    4/28/09 3:47p Rameshr
// 
// HDD password support in RAID mode
// EIP:20421
// 
// 14    12/31/08 3:05p Rameshraju
// BugFix- Validate the PIO mode before programming the PIO mode into the
// device EIP:17885
// 
// 13    14/08/08 10:47a Anandakrishnanl
// Compatible Mode AHCI Support Added and Sdl Token Added in IdeBusSrc.sdl
// 
// 12    5/28/08 9:38a Rameshraju
// Based on the SDL token index/data or MMIO method used to access the
// AHCI configuration space.
// 
// 11    5/14/08 4:42p Rameshraju
// Error code added if error happens while configuring device or
// controller.
// 
// 10    5/09/08 9:59a Rameshraju
// Cdrom block size initilized.
// 
// 9     5/02/08 3:41p Rameshraju
// Insteed of OR, Write the FIS base address.
// 
// 8     4/23/08 12:30p Srinin
// Bug fix in CheckDevicePresence()
// 
// 7     4/18/08 2:58p Srinin
// If Device SPINUP is enabled, check is added to see whether 
// COMRESET is expected or not.
// 
// 6     4/14/08 4:58p Rameshraju
// Security feature stopped when the AHCI bus driver is stopped.
// 
// 5     3/27/08 11:23a Srinin
// CreateSataDevicePath() modified to create a devicepath 
// even if Remaining devicepath is not NULL.
// 
// 4     3/24/08 6:17p Fasihm
// Fixed the issue that HDD Password prompt is not displayed in POST in
// AHCI mode when DISABLE_SOFT_SET_PREV is enabled.
// 
// 3     7/03/08 5:31p Anandakrishnanl
// Added Smart Support as a seperate Driver and Corresponding changes to
// invoke Smart Protocols and removed SDL-Token
// 
// 2     28/02/08 6:21p Anandakrishnanl
// Cleaned up Code and re Checked - in
// 
// 1     28/02/08 6:03p Anandakrishnanl
// AHCI Bus Driver initial check-in.
// 
// 
// 
//**********************************************************************
//<AMI_FHDR_START>
//
// Name: AhciBus.c
//
// Description: Provides AHCI Block IO protocol
//
//<AMI_FHDR_END>
//**********************************************************************

#include "AhciBus.h"
#include "protocol\legacyahci.h"
#if SBIDE_SUPPORT
#include "SBIDE.h" 
#endif

#if defined CORE_COMBINED_VERSION && (CORE_COMBINED_VERSION > 0x4028E)
AMI_BLOCKIO_WRITE_PROTECTION_PROTOCOL *AmiBlkWriteProtection = NULL;
#endif

EFI_GUID gEfiAhciBusProtocolGuid            = AHCI_BUS_INIT_PROTOCOL_GUID;
EFI_GUID gAhciBusDriverBindingProtocolGuid  = EFI_DRIVER_BINDING_PROTOCOL_GUID;
EFI_GUID gEfiIdeControllerProtocolGuid      = IDE_CONTROLLER_PROTOCOL_GUID;
static EFI_GUID gDevicePathProtocolGuid     = EFI_DEVICE_PATH_PROTOCOL_GUID;

#ifndef EFI_COMPONENT_NAME2_PROTOCOL_GUID
EFI_GUID gComponentNameProtocolGuid = EFI_COMPONENT_NAME_PROTOCOL_GUID;
#else
EFI_GUID gComponentNameProtocolGuid = EFI_COMPONENT_NAME2_PROTOCOL_GUID;
#endif

static EFI_GUID gEfiBlockIoProtocolGuid     = EFI_BLOCK_IO_PROTOCOL_GUID;
EFI_GUID gEfiDiskInfoProtocolGuid           = EFI_DISK_INFO_PROTOCOL_GUID;
EFI_GUID gEfiAhciDiskInfoProtocolGuid       = EFI_DISK_INFO_AHCI_INTERFACE_GUID;
EFI_GUID gSecurityModeProtocolGuid          = IDE_SECURITY_INTERFACE_GUID;
EFI_GUID gSMARTProtocolGuid                 = IDE_SMART_INTERFACE_GUID;
EFI_GUID gPowerMgmtProtocolGuid             = IDE_POWER_MGMT_INTERFACE_GUID;
EFI_GUID gHPAProtocolGuid                   = IDE_HPA_INTERFACE_GUID;
EFI_GUID gStorageSecurityProtocolGuid       = EFI_STORAGE_SECURITY_COMMAND_PROTOCOL_GUID;
EFI_EVENT gIDEBusEvtBootScript              = NULL; 
static EFI_GUID gHddSecurityInitProtocolGuid= HDD_SECURITY_INIT_PROTOCOL_GUID; 
static EFI_GUID gHddSmartInitProtocolGuid   = HDD_SMART_INIT_PROTOCOL_GUID;  
static EFI_GUID gHddSecurityEndProtocolGuid = HDD_SECURITY_END_PROTOCOL_GUID;
static EFI_GUID gOpalSecInitProtocolGuid    = OPAL_SEC_INIT_PROTOCOL_GUID;
static EFI_GUID gAtaPassThruInitProtocolGuid= ATA_PASS_THRU_INIT_PROTOCOL_GUID; 
static EFI_GUID gScsiPassThruAtapiInitProtocolGuid = SCSI_PASS_THRU_ATAPI_INIT_PROTOCOL_GUID;
static EFI_GUID gEfiIdeBusInitProtocolGuid      = IDE_BUS_INIT_PROTOCOL_GUID;
static EFI_GUID gOnboardRaidControllerGuid      = ONBOARD_RAID_CONTROLLER_GUID;
static EFI_GUID gHddPasswordVerifiedGuid        = HDD_PASSWORD_VERIFIED_GUID;
static EFI_GUID gAmiGlobalVariableGuid          = AMI_GLOBAL_VARIABLE_GUID;


#if SBIDE_SUPPORT
EFI_GUID gIdeSetupProtocolguid              = IDE_SETUP_PROTOCOL_GUID;
VOID InitMiscConfig(IN SATA_DEVICE_INTERFACE    *SataDevInterface);
#endif


#if INDEX_DATA_PORT_ACCESS
extern      InitilizeIndexDataPortAddress();
#endif

extern
EFI_STATUS
ExecutePacketCommand (
    IN SATA_DEVICE_INTERFACE               *SataDevInterface, 
    IN COMMAND_STRUCTURE                   *CommandStructure,
    IN BOOLEAN                             READWRITE
);

#if (EFI_SPECIFICATION_VERSION > 0x00020000)
extern EFI_COMPONENT_NAME2_PROTOCOL gAhciBusControllerDriverName;
#else
extern EFI_COMPONENT_NAME_PROTOCOL gAhciBusControllerDriverName;
#endif


AHCI_CONTOLLER_LINKED_LIST AhciControllerLinkedList;

EFI_DRIVER_BINDING_PROTOCOL	gAhciBusDriverBinding = {
  AhciBusSupported, 
  AhciBusStart,     
  AhciBusStop,      
  AHCI_BUS_DRIVER_VERSION,  // version
  NULL,                    // ImageHandle
  NULL                     // DriverBindingHandle
};

HDD_SECURITY_INIT_PROTOCOL     *HddSecurityInitProtocol;  
HDD_SMART_INIT_PROTOCOL         *HddSmartInitProtocol;     
OPAL_SECURITY_INIT_PROTOCOL    *OpalSecInitProtocol;
ATA_PASS_THRU_INIT_PROTOCOL     *AtaPassThruInitProtocol;  
SCSI_PASS_THRU_ATAPI_INIT_PROTOCOL   *gScsiPassThruAtapiInitProtocol; 
AHCI_PLATFORM_POLICY_PROTOCOL   *AhciPlatformPolicy = NULL;

//
// Instantiate AHCI_PLATFORM_POLICY_PROTOCOL with default values 
//
AHCI_PLATFORM_POLICY_PROTOCOL        gDefaultAhciPlatformPolicy = {
    FALSE,                              // Legacy Raid option selected 
    TRUE,                               // Ahcibus driver handles the ATAPI devices
    FALSE,                              // Drive LED on ATAPI Enable (DLAE)
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
#ifdef DiPM_SUPPORT
    DiPM_SUPPORT,                        // Device Initiated power management
#else
    FALSE,
#endif
#ifdef ENABLE_DIPM
    ENABLE_DIPM,
#else
    FALSE,
#endif
#ifdef DEVICE_SLEEP_SUPPORT
    DEVICE_SLEEP_SUPPORT,
#else
    FALSE,
#endif
#ifdef ENABLE_DEVICE_SLEEP
    ENABLE_DEVICE_SLEEP
#else
    FALSE
#endif
                    
};

//**********************************************************************
//<AMI_PHDR_START>
//
// Procedure:   AhciBusEntryPoint
//
// Description: Installs gAhciBusDriverBinding protocol
//
// Input:
//  IN EFI_HANDLE        ImageHandle,
//  IN EFI_SYSTEM_TABLE  *SystemTable
//
// Output:
//  EFI_STATUS
//
// Modified:
//      
// Referrals: InitAmiLib InstallMultipleProtocolInterfaces DListInit
//
// Notes:   
//  Here is the control flow of this function:
//  1. Initialize Ami Lib.
//  2. Install Driver Binding Protocol
//  3. Return EFI_SUCCESS.
//
//<AMI_PHDR_END>
//**********************************************************************
EFI_STATUS AhciBusEntryPoint(
    IN EFI_HANDLE        ImageHandle,
    IN EFI_SYSTEM_TABLE  *SystemTable
  )
{
    EFI_STATUS  Status;


    gAhciBusDriverBinding.DriverBindingHandle=NULL;
    gAhciBusDriverBinding.ImageHandle=ImageHandle;

    InitAmiLib(ImageHandle, SystemTable);
    DListInit(&(AhciControllerLinkedList.AhciControllerList));
    Status = pBS->InstallMultipleProtocolInterfaces(
                &gAhciBusDriverBinding.DriverBindingHandle,
                &gAhciBusDriverBindingProtocolGuid,&gAhciBusDriverBinding,
                &gComponentNameProtocolGuid, &gAhciBusControllerDriverName,
                NULL
                );

    return Status;
}

//**********************************************************************
//<AMI_PHDR_START>
//
// Procedure:   AhciBusSupported
//
// Description: Checks whether EFI_IDE_CONTROLLER_INIT_PROTOCOL_GUID 
//              is installed on the controller. If 'yes', return SUCCESS else ERROR
//
// Input:
//  IN EFI_DRIVER_BINDING_PROTOCOL    *This,
//  IN EFI_HANDLE                     Controller,
//  IN EFI_DEVICE_PATH_PROTOCOL       *RemainingDevicePath
//
// Output:
//  EFI_STATUS
//
// Modified:
//      
// Referrals: OpenProtocol CloseProtocol 
//
// Notes:   
//  Here is the control flow of this function:
// 1. If Devicepath is NULL, check "gEfiIdeControllerInitProtocolGuid"
//    is installed by IdeController device driver,if yes, it is the 
//    IDE controller that this Bus will manage. Then return Success.
// 2. If Devicepath is valid, check if it is a SATA device Path. See 
//    if gEfiAhciBusProtocolGuid is installed on the device.
// 3. make sure the the Controller class code is AHCI
//
//<AMI_PHDR_END>
//**********************************************************************
EFI_STATUS 
AhciBusSupported(
    IN EFI_DRIVER_BINDING_PROTOCOL    *This,
    IN EFI_HANDLE                     Controller,
    IN EFI_DEVICE_PATH_PROTOCOL        *RemainingDevicePath )
{

    EFI_STATUS                  Status;
    EFI_IDE_CONTROLLER_INIT_PROTOCOL IdeControllerInterface;
    SATA_DEVICE_PATH            *SataRemainingDevicePath = (SATA_DEVICE_PATH *) RemainingDevicePath;
    AHCI_BUS_PROTOCOL           *AhciBusInterface;
    SATA_DEVICE_INTERFACE       *SataDevInterface = NULL;
    EFI_PCI_IO_PROTOCOL         *PciIO;
    UINT8                       PciConfig[256];

    //
    // Check for Valid SATA Device Path. If no return UNSUPPORTED
    //
    if (!(SataRemainingDevicePath == NULL)) {
        //
        // Check if the SataRemainingDevicePath is valid 8.3.4.1 
        //
        if (SataRemainingDevicePath->Header.Type != MESSAGING_DEVICE_PATH ||
            SataRemainingDevicePath->Header.SubType != MSG_USB_SATA_DP &&
            NODE_LENGTH(&SataRemainingDevicePath->Header) != SATA_DEVICE_PATH_LENGTH) {
            return EFI_UNSUPPORTED;
        }

        //
        // Now check whether it is OK to enumerate the specified device.
        //
        Status = pBS->OpenProtocol( Controller,
                    &gEfiAhciBusProtocolGuid,
                    (VOID **)&AhciBusInterface,
                    This->DriverBindingHandle,
                    Controller,
                    EFI_OPEN_PROTOCOL_BY_DRIVER );
        if (Status == EFI_SUCCESS || Status == EFI_ALREADY_STARTED) {
            pBS->CloseProtocol (
                    Controller,
                    &gEfiAhciBusProtocolGuid,
                    This->DriverBindingHandle,
                    Controller);

            SataDevInterface = GetSataDevInterface(
                                AhciBusInterface, 
                                (UINT8)SataRemainingDevicePath->PortNumber,
                                (UINT8)SataRemainingDevicePath->MultiplierPortNumber
                               );

            // If the device in the remaining device path Port already detected and configued 
            // return as EFI_ALREADY_STARTED. If the device is not yet detected in the 
            // remaining device path port, proceed for the device detection and configuration

            if (SataDevInterface && (SataDevInterface->DeviceState >= DEVICE_DETECTION_FAILED)) {
                return EFI_ALREADY_STARTED;
            }
            else {
                return EFI_SUCCESS;
            }
        }
    }

    // Check if the IDEBUS installed on the controller. If it is installed 
    // Idebus driver already handling the Controller. So AHCIBUS driver should not handle
    // the controller 

    Status = pBS->OpenProtocol( Controller,
                                    &gEfiIdeBusInitProtocolGuid,
                                    NULL,
                                    This->DriverBindingHandle,
                                    Controller,
                                    EFI_OPEN_PROTOCOL_TEST_PROTOCOL );

    if (Status == EFI_SUCCESS) {

        // Idebus handling the controller. Return with Error.
        return EFI_UNSUPPORTED;
    }


    // Check whether IDE_CONTROLLER_PROTOCOL  has been installed on 
    // this controller	
    //
    Status = pBS->OpenProtocol( Controller,
                &gEfiIdeControllerInitProtocolGuid,
                (VOID **)&IdeControllerInterface,
                This->DriverBindingHandle,     
                Controller,   
                EFI_OPEN_PROTOCOL_BY_DRIVER	);

    //
    // IDE_CONTROLLER_PROTOCOL will be opened by each device. So 
    // EFI_ALREADY_STARTED is not an error.
    //
    if  ( !(Status == EFI_SUCCESS || Status == EFI_ALREADY_STARTED)) {
        return EFI_UNSUPPORTED;
    }

    //
    // Close IDE_CONTROLLER_PROTOCOL
    //
    pBS->CloseProtocol (
        Controller,
        &gEfiIdeControllerInitProtocolGuid,
        This->DriverBindingHandle,
        Controller                
        );

    //
    // Check if Controller is in AHCI mode or not?
    //
    Status = pBS->OpenProtocol( Controller,
                                &gEfiPciIoProtocolGuid,
                                (VOID **)&PciIO,
                                This->DriverBindingHandle,     
                                Controller,   
                                EFI_OPEN_PROTOCOL_GET_PROTOCOL);
     if (EFI_ERROR(Status)) {return EFI_UNSUPPORTED;}

     Status = PciIO->Pci.Read ( PciIO,
                                EfiPciIoWidthUint8,
                                0,
                                sizeof (PciConfig),
                                PciConfig
                                );

    if (PciConfig [IDE_SUB_CLASS_CODE] == SCC_AHCI_CONTROLLER) {
#ifdef AHCI_COMPATIBLE_MODE
    #if !(AHCI_COMPATIBLE_MODE)
            return EFI_SUCCESS;
    #endif
#endif
    }

#ifdef SUPPORT_ATAPI_IN_RAID_MODE
#ifdef HDD_PASSWORD_SUPPORT_UNDER_RAIDMODE
    #if SUPPORT_ATAPI_IN_RAID_MODE || HDD_PASSWORD_SUPPORT_UNDER_RAIDMODE
    if (PciConfig [IDE_SUB_CLASS_CODE] == SCC_RAID_CONTROLLER) {

        //
        // Under Raid mode, don't detect the devices again 
        // Check if AHCI_BUS_PROTOCOL installed status. If already installed
        // Ahcibus started already and device detection done
        //
        Status = pBS->OpenProtocol( Controller,
                                &gEfiAhciBusProtocolGuid,
                                NULL,
                                This->DriverBindingHandle,     
                                Controller,   
                                EFI_OPEN_PROTOCOL_TEST_PROTOCOL);		


        if  ( EFI_ERROR(Status)) {
            return EFI_SUCCESS;
        } else {
            return EFI_ALREADY_STARTED;
        }
    }
    #endif
#endif
#endif

    return EFI_UNSUPPORTED; 

}


//**********************************************************************
//<AMI_PHDR_START>
//
// Procedure:   AhciBusStart
//
// Description: Installs AHCI Block IO Protocol
//
// Input:
//  IN EFI_DRIVER_BINDING_PROTOCOL    *This,
//  IN EFI_HANDLE                     Controller,
//  IN EFI_DEVICE_PATH_PROTOCOL       *RemainingDevicePath
//
// Output:
//  EFI_STATUS
//
// Modified:
//      
// Referrals: OpenProtocol CloseProtocol InstallProtocolInterface 
//            AllocatePool InstallAhciBusProtocol CheckPortImplemented 
//            DetectAndConfigureDevice.
//
// Notes:   
// 1. Collect the info about the number of devices to detect and configure.
// 2. Configure the AHCI controller if it is not done yet.
// 3. Detect the device connected to the port
// 4. If the device is a Port Multiplier, detect & configure all the 
//    devices behind it, else configure the device directly connected
//    to the port.
// 5. Continue step 3 and 4 for all the ports on the controller.
//
//<AMI_PHDR_END>
//**********************************************************************                
EFI_STATUS 
AhciBusStart (
    IN EFI_DRIVER_BINDING_PROTOCOL    *This,
    IN EFI_HANDLE                     Controller,
    IN EFI_DEVICE_PATH_PROTOCOL       *RemainingDevicePath )
{

    EFI_STATUS                  Status;
    EFI_PCI_IO_PROTOCOL         *PciIO;
    EFI_IDE_CONTROLLER_INIT_PROTOCOL *IdeControllerInterface;
    SATA_DEVICE_INTERFACE       *SataDevInterface = NULL;
    AHCI_BUS_PROTOCOL           *AhciBusInterface;	
    UINT8                       Enumeration_Process = ENUMERATE_ALL;
    SATA_DEVICE_PATH            *SataRemainingDevicePath = (SATA_DEVICE_PATH *)RemainingDevicePath;
    UINT8                       PortEnumeration = 0xFF, PMPortEnumeration = 0xFF; // Bit Map
    UINT8                       CurrentPort = 0, CurrentPMPort = 0xFF; 
    BOOLEAN                     Enabled = TRUE;
    UINT8                       MaxDevices = 0; 
    UINT8                       Data8;
    EFI_HANDLE                  SecHandle=NULL;
    EFI_DEVICE_PATH_PROTOCOL    *DevicePath;
    VOID                        *TempProtocolPtr;
    EFI_STATUS                  SecurityStatus=EFI_NOT_FOUND;
    BOOLEAN                     RaidDriverBlocked=FALSE;

    PROGRESS_CODE(DXE_IDE_BEGIN);

#if defined CORE_COMBINED_VERSION && (CORE_COMBINED_VERSION > 0x4028E)
    if(AmiBlkWriteProtection == NULL) {
        Status = pBS->LocateProtocol(&gAmiBlockIoWriteProtectionProtocolGuid, NULL, &AmiBlkWriteProtection); 
        if(EFI_ERROR(Status)) {
            AmiBlkWriteProtection = NULL;
        }
    }
#endif

    // Open IDE_CONTROLLER_PROTOCOL. If success or Already opened, It is OK to proceed.
    Status = pBS->OpenProtocol( Controller,
                                &gEfiIdeControllerInitProtocolGuid,
                                (VOID **)&IdeControllerInterface,
                                This->DriverBindingHandle,     
                                Controller,   
                                EFI_OPEN_PROTOCOL_BY_DRIVER	);

    if  ( !(Status == EFI_SUCCESS || Status == EFI_ALREADY_STARTED)) return EFI_DEVICE_ERROR;

    // Get the PciIO interface
    Status = pBS->OpenProtocol( Controller,
                                &gEfiPciIoProtocolGuid,
                                (VOID **)&PciIO,
                                This->DriverBindingHandle,     
                                Controller,   
                                EFI_OPEN_PROTOCOL_GET_PROTOCOL);

    if (EFI_ERROR(Status)) return EFI_DEVICE_ERROR;

    // Check if AHCI_BUS_PROTOCOL installed.
    Status = pBS->OpenProtocol( Controller,
                                &gEfiAhciBusProtocolGuid,
                                (VOID **)&AhciBusInterface,
                                This->DriverBindingHandle,     
                                Controller,   
                                EFI_OPEN_PROTOCOL_BY_DRIVER);		


    if  ( !(Status == EFI_SUCCESS || Status == EFI_ALREADY_STARTED)) {

        Status = pBS->AllocatePool (EfiBootServicesData,
                    sizeof(AHCI_BUS_PROTOCOL),
                    (VOID**)&AhciBusInterface
                    );

        if (EFI_ERROR(Status)) return EFI_OUT_OF_RESOURCES; //No need to close IDE_CONTROLLER_PROTOCOL

        Status = InstallAhciBusProtocol (Controller, AhciBusInterface, IdeControllerInterface, PciIO);
        if (EFI_ERROR(Status)) return EFI_DEVICE_ERROR;    //No need to close the protocol. Will be handled in STOP
    }

    if (!IdeControllerInterface->EnumAll) {
    // Check if sataRemainingDevicePath is valid or not
        if (!(SataRemainingDevicePath == NULL)) {
         // Check if the SataRemainingDevicePath is valid 8.3.4.1 
            if (SataRemainingDevicePath->Header.Type != MESSAGING_DEVICE_PATH ||
                SataRemainingDevicePath->Header.SubType != MSG_USB_SATA_DP &&
                NODE_LENGTH(&SataRemainingDevicePath->Header) != SATA_DEVICE_PATH_LENGTH) { 
                    return EFI_DEVICE_ERROR;
            }
            // Get the Port# that needs to be processed.
            PortEnumeration = 1 << SataRemainingDevicePath->PortNumber;     //Bit Map
            PMPortEnumeration = 1 << SataRemainingDevicePath->MultiplierPortNumber;      // Bit Map
            CurrentPMPort =  (UINT8) SataRemainingDevicePath->MultiplierPortNumber;
        }
    }
    else {
        PortEnumeration = AhciBusInterface->HBAPortImplemented;
    }

    //
    // Get the Ahci Platform Policy Protocol
    //
    Status=pBS->LocateProtocol(&gAciPlatformPolicyProtocolGuid, NULL, &AhciPlatformPolicy);
    if(EFI_ERROR(Status)) {
        //
        // If the Ahci Platform policy protocol not found, initilize with default value
        //
        AhciPlatformPolicy=(AHCI_PLATFORM_POLICY_PROTOCOL *)&gDefaultAhciPlatformPolicy;
    }    

    
    TRACE_AHCI((-1,"\nAHCI Driver Detection and Configuratiion starts\n"));


    //--------------------------------------------------------------------------
    //  Detection and Configuration starts
    //--------------------------------------------------------------------------
    for (  ; PortEnumeration != 0 ; PortEnumeration >>= 1, CurrentPort++, CurrentPMPort = 0xFF) {

        if(!(PortEnumeration & 1)) {
            continue;
        }    

        // Check if the current port is implemented or not?
        Status = CheckPortImplemented(AhciBusInterface, CurrentPort);       
        if (EFI_ERROR(Status)) { continue;}
    
        Status = IdeControllerInterface->NotifyPhase (IdeControllerInterface, EfiIdeBeforeChannelEnumeration, CurrentPort);
        if (EFI_ERROR(Status)) { continue;}

        Status = IdeControllerInterface->GetChannelInfo(IdeControllerInterface, CurrentPort, &Enabled, &MaxDevices);
        if (EFI_ERROR(Status) || !Enabled) { goto NextDevice; }

        Status = DetectAndConfigureDevice(This, Controller, RemainingDevicePath, AhciBusInterface, IdeControllerInterface, CurrentPort, CurrentPMPort);
        SataDevInterface = GetSataDevInterface(AhciBusInterface, CurrentPort, CurrentPMPort);

        if(SataDevInterface != NULL && EFI_ERROR(SecurityStatus)) {
            // Verify that Security interface has been installed
            // on atleast one device
            SecurityStatus = pBS->HandleProtocol(SataDevInterface->IdeDeviceHandle, 
                                &gSecurityModeProtocolGuid, 
                                &TempProtocolPtr
                                );
        }

        // Check whether the device detected is PM. Also check whether PM is supported by the Controller
        // and also MaxDevices should be more than 1 if PM is Supported.
        if (!EFI_ERROR(Status) && SataDevInterface && SataDevInterface->NumPMPorts &&
                (SataDevInterface->DeviceType == PMPORT) && MaxDevices > 1){

            Data8 = SataDevInterface->NumPMPorts > MaxDevices  ? MaxDevices : SataDevInterface->NumPMPorts;
            PMPortEnumeration = 1;
            for (Data8-- ;Data8; Data8-- ){
                PMPortEnumeration = (PMPortEnumeration << 1) | 1;
            }
            
            // Port Multiplier loop
            for (CurrentPMPort = 0; PMPortEnumeration & 1 ; PMPortEnumeration >>= 1, CurrentPMPort++ ){
                DetectAndConfigureDevice(This, Controller, RemainingDevicePath, AhciBusInterface, IdeControllerInterface, CurrentPort, CurrentPMPort);
            }

        }

NextDevice:
        IdeControllerInterface->NotifyPhase(IdeControllerInterface, EfiIdeAfterChannelEnumeration, CurrentPort);

    }


	TRACE_AHCI((-1," AHCI Driver Detection and Configuratiion Ends\n"));

    Status = pBS->LocateProtocol (
                                &gAtaPassThruInitProtocolGuid,
                                NULL,
                                &AtaPassThruInitProtocol
                        );

    if(!EFI_ERROR(Status)) {
        if(AtaPassThruInitProtocol != NULL) {
            AtaPassThruInitProtocol->InstallAtaPassThru(Controller, TRUE);
        }
    }

    // SCSIPassThruAtapi install
    Status = pBS->LocateProtocol (
                                &gScsiPassThruAtapiInitProtocolGuid,
                                NULL,
                                &gScsiPassThruAtapiInitProtocol
                        );


    if(!EFI_ERROR(Status)) {
        if(gScsiPassThruAtapiInitProtocol != NULL) {
            gScsiPassThruAtapiInitProtocol->InstallScsiPassThruAtapi(Controller, TRUE);
        }
    }

    // Handle the Onboard Raid controller Password Verification

    Status = pBS->HandleProtocol(Controller, 
                                    &gHddSecurityEndProtocolGuid, 
                                    & TempProtocolPtr
                                    );

    if(Status == EFI_SUCCESS) {
        //
        // Protocol already installed on the Controller handle.
        // Re-Install the protocol interface to Notify the Password verification 
        //
        Status = pBS->ReinstallProtocolInterface(
                                &Controller, 
                                &gHddSecurityEndProtocolGuid, NULL,NULL
                                );
    } else {
        //
        // This will notify AMITSE to invoke the HDD password Screen
        //
        Status = pBS->InstallProtocolInterface(
                                &Controller, 
                                &gHddSecurityEndProtocolGuid, EFI_NATIVE_INTERFACE,NULL
                                );
    }

    if(!EFI_ERROR(Status) && !EFI_ERROR(SecurityStatus)) {

        // Handle the Onboard Raid controller Password Verification

        Status = pBS->HandleProtocol(Controller, 
                                    &gOnboardRaidControllerGuid, 
                                    &TempProtocolPtr
                                    );
         if(!EFI_ERROR(Status)) {


            // Check the Hdd Password verification done. If the password 
            // Verification done, proceed for RAID driver launch. Otherwise
            // Hold the Raid driver until Password verification finished.

            Status = pBS->HandleProtocol(Controller, 
                                    &gHddPasswordVerifiedGuid, 
                                    &TempProtocolPtr
                                    );

            if(EFI_ERROR(Status)) {

                // Don't launch the Raid Option rom until password verified
        
                Status = pBS->OpenProtocol (
                                        Controller,
                                        &gDevicePathProtocolGuid,
                                        (VOID *) &DevicePath,
                                        This->DriverBindingHandle,
                                        Controller,
                                        EFI_OPEN_PROTOCOL_BY_DRIVER
                                        );

                if(Status == EFI_SUCCESS) {
                    RaidDriverBlocked=TRUE;
                    Status = pRS->SetVariable(L"RaidDriverBlockingStatus",
                                        &gAmiGlobalVariableGuid,
                                        EFI_VARIABLE_BOOTSERVICE_ACCESS,
                                        sizeof(RaidDriverBlocked),
                                        &RaidDriverBlocked );
                }
            }
        }
    }

    return EFI_SUCCESS;
}


//**********************************************************************
//<AMI_PHDR_START>
//
// Procedure:   DetectAndConfigureDevice
//
// Description: Detects and Configures Sata Device
//
// Input:
//  IN EFI_DRIVER_BINDING_PROTOCOL    *This,
//  IN EFI_HANDLE                     Controller
//  IN EFI_DEVICE_PATH_PROTOCOL       *RemainingDevicePath,
//  AHCI_BUS_PROTOCOL                 *AhciBusInterface,
//  EFI_IDE_CONTROLLER_INIT_PROTOCOL  *IdeControllerInterface,
//  UINT8                             Port,
//  UINT8                             PMPort
//
// Output:
//  EFI_STATUS
//
// Modified:
//      
// Referrals: AhciDetectDevice ConfigureDevice InitSataBlockIO InitSataDiskInfo
//
// Notes:
// 1. Detect whether device is connected to the port. If no device exit.
// 2. Install SataDevInterface. If PMPort, Configure PMPort and Exit.
// 3. Configure the SATA device and the controller.
// 4. Install DevicePath, BlockIO and DiskInfo protocol.
//
//<AMI_PHDR_END>
//**********************************************************************
EFI_STATUS
DetectAndConfigureDevice (
    IN EFI_DRIVER_BINDING_PROTOCOL    *This,
    IN EFI_HANDLE                     Controller,
    IN EFI_DEVICE_PATH_PROTOCOL       *RemainingDevicePath,
    AHCI_BUS_PROTOCOL                 *AhciBusInterface,
    EFI_IDE_CONTROLLER_INIT_PROTOCOL  *IdeControllerInterface,
    UINT8                             Port,
    UINT8                             PMPort
)
{

    EFI_STATUS                  Status;
    SATA_DEVICE_INTERFACE       *SataDevInterface = NULL;
    EFI_ATA_COLLECTIVE_MODE     *SupportedModes = NULL;
    UINT16                      SecurityStatus = 0;

    SataDevInterface = GetSataDevInterface(AhciBusInterface, Port, PMPort);

    if (SataDevInterface && ((SataDevInterface->DeviceState == DEVICE_DETECTION_FAILED)||
        (SataDevInterface->DeviceState == DEVICE_CONFIGURED_SUCCESSFULLY))){ 
        return EFI_SUCCESS;
    }
    
    Status = AhciDetectDevice(AhciBusInterface, IdeControllerInterface, Port, PMPort);
    SataDevInterface = GetSataDevInterface(AhciBusInterface, Port, PMPort);
    if (EFI_ERROR(Status)) { 
        if (SataDevInterface) SataDevInterface->DeviceState = DEVICE_DETECTION_FAILED;
        return EFI_DEVICE_ERROR;
    }

    if (!SataDevInterface) { 
        return EFI_DEVICE_ERROR;
    }

    SataDevInterface->DeviceState = DEVICE_DETECTED_SUCCESSFULLY;

    //
    // if this is a Port Multiplier skip the rest
    //
    if (SataDevInterface->DeviceType == PMPORT) {
        SataDevInterface->DeviceState = DEVICE_CONFIGURED_SUCCESSFULLY;

        //
        //Update Port Multiplier Data
        //
        Status = ConfigurePMPort(SataDevInterface);
        if (!EFI_ERROR(Status)) {
            TRACE_AHCI((-1,"AHCI: SATA Device type %x detected at Port Number : %x, PM Port Number : %x\n",
                SataDevInterface->DeviceType, SataDevInterface->PortNumber, SataDevInterface->PMPortNumber));
        }
        return Status;
    }

    Status = ConfigureDevice(SataDevInterface, &SupportedModes);
    if (EFI_ERROR(Status)) { 
        ERROR_CODE(DXE_IDE_DEVICE_FAILURE, EFI_ERROR_MAJOR);
        SataDevInterface->DeviceState = DEVICE_DETECTION_FAILED;
        return EFI_DEVICE_ERROR;
    }

    Status = ConfigureController(SataDevInterface, SupportedModes);
    if (EFI_ERROR(Status)) { 
        ERROR_CODE(DXE_IDE_DEVICE_FAILURE, EFI_ERROR_MAJOR);
        SataDevInterface->DeviceState = DEVICE_DETECTION_FAILED;
        return EFI_DEVICE_ERROR;
    }

    SataDevInterface->DeviceState = DEVICE_CONFIGURED_SUCCESSFULLY;

    Status = ConfigureSataPort(SataDevInterface);

    if (EFI_ERROR(Status)) { 
        return EFI_DEVICE_ERROR; 
    }

    //
    // Create the Devicepath
    //
    Status = CreateSataDevicePath (This, Controller, SataDevInterface, RemainingDevicePath);
    if (EFI_ERROR(Status)) { return EFI_DEVICE_ERROR; }

    //
    // Initialize Block_IO Protocol
    //
    Status = InitSataBlockIO (SataDevInterface);
    if (EFI_ERROR(Status)){
        return EFI_DEVICE_ERROR;
    }

    //
    // Initialize IDE EFI_DISK_INFO_PROTOCOL
    //
    Status = InitSataDiskInfo (SataDevInterface);
    if (EFI_ERROR(Status)){
        return EFI_DEVICE_ERROR;
    }

    //
    // Install Devicepath
    //
    Status = pBS->InstallMultipleProtocolInterfaces (
            &(SataDevInterface->IdeDeviceHandle),
            &gDevicePathProtocolGuid, SataDevInterface->DevicePathProtocol,
            NULL);

    if(EFI_ERROR(Status)) {
        SataDevInterface->DeviceState = DEVICE_DETECTION_FAILED;
        if (EFI_ERROR(Status)){
            return EFI_DEVICE_ERROR;
        }
    }

    //
    // Open IdeControllerProtocol 
    //
    Status = pBS->OpenProtocol(Controller,
                &gEfiIdeControllerInitProtocolGuid,
                (VOID **)&IdeControllerInterface,
                This->DriverBindingHandle,     
                SataDevInterface->IdeDeviceHandle,   
                EFI_OPEN_PROTOCOL_BY_CHILD_CONTROLLER);

    Status = pBS->LocateProtocol (
                                &gHddSecurityInitProtocolGuid,
                                NULL,
                                &HddSecurityInitProtocol
                        );

     if(!EFI_ERROR(Status)) {
         if(HddSecurityInitProtocol != NULL) {
             HddSecurityInitProtocol->InstallSecurityInterface(SataDevInterface, TRUE);
         }
     } else {

        //
        // If Security Feature support is not enabled, always freeze 
        // lock the security feature
        //
        if (SataDevInterface->IdentifyData.Command_Set_Supported_82 & 0x2) {
            COMMAND_STRUCTURE           CommandStructure;
            ZeroMemory(&CommandStructure, sizeof(COMMAND_STRUCTURE)); 
            CommandStructure.Command = SECURITY_FREEZE_LOCK;
    		Status = ExecuteNonDataCommand (SataDevInterface, CommandStructure);
            //
            // if Device Configuration Overlay feature set supported then issue the
            // Dev config Free lock command.
            //
            if (SataDevInterface->IdentifyData.Command_Set_Supported_83 & 0x800) {
    		    CommandStructure.Command = DEV_CONFIG_FREEZE_LOCK;
    		    CommandStructure.Features = DEV_CONFIG_FREEZE_LOCK_FEATURES;
    		    Status = ExecuteNonDataCommand (SataDevInterface, CommandStructure);
            }
            //
            // Update the Identify device buffer
            //
            Status = GetIdentifyData(SataDevInterface);
            if (EFI_ERROR(Status)) {
                return EFI_DEVICE_ERROR; 
            }
        }
    }

    Status = pBS->LocateProtocol (
                                &gOpalSecInitProtocolGuid,
                                NULL,
                                &OpalSecInitProtocol
                        );

     if(!EFI_ERROR(Status)) {
         if(OpalSecInitProtocol != NULL) {
             OpalSecInitProtocol->InstallOpalSecurityInterface(SataDevInterface, TRUE);
         }
     }

    Status = pBS->LocateProtocol (
                    &gHddSmartInitProtocolGuid,
                    NULL,
                    &HddSmartInitProtocol
            );

    if(!EFI_ERROR(Status)) {
        if(HddSmartInitProtocol != NULL) {
            HddSmartInitProtocol->InitSMARTSupport(SataDevInterface, TRUE);
            //
            // Update the Idendify Data.
            //
            Status = GetIdentifyData(SataDevInterface);
            if(HddSmartInitProtocol->SmartDiagonasticFlag) {
                HddSmartInitProtocol->InstallSMARTInterface(SataDevInterface, TRUE);
            }
        }
    }

    //
    // Check BlockIO has been installed or not.
    //
    Status = pBS->OpenProtocol( SataDevInterface->IdeDeviceHandle,
                &gEfiBlockIoProtocolGuid,
                NULL,
                This->DriverBindingHandle,     
                SataDevInterface->IdeDeviceHandle,   
                EFI_OPEN_PROTOCOL_TEST_PROTOCOL);

    if (EFI_ERROR(Status)) {
        //
        // BLOCKIO not installed and device has been configured successfully
        //
        Status = EFI_UNSUPPORTED;
        SecurityStatus = 0;	
    }

    if ((Status == EFI_UNSUPPORTED) || (!(SecurityStatus & 4))){
        //
        // Either the device doesn't support Security Mode OR   Device is not locked
        //
        Status = pBS->InstallMultipleProtocolInterfaces (
                    &(SataDevInterface->IdeDeviceHandle),
                    &gEfiDiskInfoProtocolGuid,
                    (EFI_DISK_INFO_PROTOCOL *)(SataDevInterface->SataDiskInfo),
                    NULL);

#if HDD_PASSWORD_SUPPORT_UNDER_RAIDMODE
    if (!(!(AhciBusInterface->AHCIRAIDMODE) && (SataDevInterface->DeviceType == ATA))) {
#endif

    //
    // If it's Raid mode and AHCIBUS handles the ATAPI devices, install the BlockIo
    // for the ATAPI devices. BlockIo Will be installed for all the ATA and ATAPI device under AHCI mode
    //
    if (!(!(AhciBusInterface->AHCIRAIDMODE) && (AhciPlatformPolicy->AhciBusAtapiSupport == FALSE ))) {

        //
        // Either the device doesn't support Security Mode OR Device is not locked
        //
        Status = pBS->InstallMultipleProtocolInterfaces (
                    &(SataDevInterface->IdeDeviceHandle),
                    &gEfiBlockIoProtocolGuid,
                    (EFI_BLOCK_IO_PROTOCOL *)(SataDevInterface->SataBlkIo),
                    NULL);
    }

#if HDD_PASSWORD_SUPPORT_UNDER_RAIDMODE
    }
#endif

     }                                                  // Install BLOCKIO

    TRACE_AHCI((-1,"AHCI: SATA Device type %x detected at Port Number : %x, PM Port Number : %x\n",
            SataDevInterface->DeviceType, SataDevInterface->PortNumber, SataDevInterface->PMPortNumber));

    return EFI_SUCCESS;
}

//**********************************************************************
//<AMI_PHDR_START>
//
// Procedure:   AhciBusStop
//
// Description: Uninstall all devices installed in start procedure.
//
// Input:
//  IN EFI_DRIVER_BINDING_PROTOCOL    *This,
//  IN EFI_HANDLE                     Controller,
//  IN UINTN                          NumberOfChildren,
//  IN EFI_HANDLE                     *ChildHandleBuffer
//
// Output:
//  EFI_STATUS
//
// Modified:
//      
// Referrals: OpenProtocol CloseProtocol 
//
// Notes:   
// 1. Check whether "gEfiAhciBusProtocolGuid" is installed on this 
//     controller. If not exit with error.
// 2. If "NumberOfChildren" is zero, check wether all child devices 
//    have been stopped. If not exit with error.If all child devices 
//    have been stopped, then close "gEfiAhciBusProtocolGuid" and 
//    "gEfiIdeControllerInitProtocolGuid",uninstall 
//    "gEfiIdeControllerInitProtocolGuid" and then exit with success.
// 3. If "NumberOfChildren" is non-zero,	close 
//    "gEfiIdeControllerInitProtocolGuid" opened by the child device 
//    in start function.Uninstall all protocols installed on this 
//    child device in start function,free up all resources allocated 
//    in start function. Repeat step 3 for all child devices and
//    return success at the end.
//
//<AMI_PHDR_END>
//**********************************************************************
EFI_STATUS 
AhciBusStop (
    IN EFI_DRIVER_BINDING_PROTOCOL    *This,
    IN EFI_HANDLE                     Controller,
    IN UINTN                          NumberOfChildren,
    IN EFI_HANDLE                     *ChildHandleBuffer
 )
{
    AHCI_BUS_PROTOCOL           *AhciBusInterface;
    SATA_DEVICE_INTERFACE       *SataDeviceInterface;
    EFI_STATUS                  Status;
    EFI_IDE_CONTROLLER_INIT_PROTOCOL *IdeControllerInterface;
    UINT16                      Index = 0;
    UINT16                      Port=0;
    UINT16                      PMPort=0;
    BOOLEAN                     Flag = TRUE;
    EFI_DEVICE_PATH_PROTOCOL    *DevicePath;
    DLINK                       *dlink;

    //
    // Check if AHCI_BUS_PROTOCOL is installed on the Controller.
    //
    Status = pBS->OpenProtocol( Controller,
                                &gEfiAhciBusProtocolGuid,
                                (VOID **)&AhciBusInterface,
                                This->DriverBindingHandle,
                                Controller,
                                EFI_OPEN_PROTOCOL_GET_PROTOCOL);

    if (EFI_ERROR(Status)) { 
        return EFI_DEVICE_ERROR;
    }

    //
    // Check if ChildHandleBuffer is valid
    //
    if (NumberOfChildren) {
        while (NumberOfChildren) {


            Status = pBS->CloseProtocol ( Controller,
                                &gEfiIdeControllerInitProtocolGuid,
                                This->DriverBindingHandle,
                                ChildHandleBuffer[Index]);

            Status = pBS->OpenProtocol(
                                ChildHandleBuffer[Index],
                                &gDevicePathProtocolGuid,
                                (VOID **)&DevicePath,
                                This->DriverBindingHandle,     
                                Controller,
                                EFI_OPEN_PROTOCOL_GET_PROTOCOL);

            //
            // Lookout for SATA device path ACPI_DEVICE path, PCI 
            // Device path and then ATAPI device path will be the sequence
            //
            do {
                if ((DevicePath->Type == MESSAGING_DEVICE_PATH) && (DevicePath->SubType == MSG_USB_SATA_DP)) {
                    Port = ((SATA_DEVICE_PATH *)DevicePath)->PortNumber;
                    PMPort = ((SATA_DEVICE_PATH *)DevicePath)->MultiplierPortNumber;
                    break;
                }
                else {
                    DevicePath = NEXT_NODE(DevicePath);
                }
            } while (DevicePath->Type != END_DEVICE_PATH);

            if(DevicePath->Type == END_DEVICE_PATH) {
                //Unable to find the Messaging device path node.
                ASSERT(FALSE);  
                return EFI_DEVICE_ERROR;
            }

            SataDeviceInterface = GetSataDevInterface(AhciBusInterface, (UINT8)Port, (UINT8)PMPort);
            if (!SataDeviceInterface) return EFI_DEVICE_ERROR;

            //
            // Before uninstalling DiskInfo check whether it is installed or not
            //
            Status = pBS->OpenProtocol( ChildHandleBuffer[Index],
                                &gEfiDiskInfoProtocolGuid,
                                NULL,
                                This->DriverBindingHandle,     
                                ChildHandleBuffer[Index],   
                                EFI_OPEN_PROTOCOL_TEST_PROTOCOL);

            if (Status == EFI_SUCCESS) {
                Status = pBS->UninstallMultipleProtocolInterfaces (
                                ChildHandleBuffer[Index],
                                &gEfiDiskInfoProtocolGuid, 
                                (EFI_DISK_INFO_PROTOCOL *)(SataDeviceInterface->SataDiskInfo),
                                NULL);
            }

            //
            // Before uninstalling BLOCKIO check whether it is installed or not
            //
            Status = pBS->OpenProtocol( ChildHandleBuffer[Index],
                                &gEfiBlockIoProtocolGuid,
                                NULL,
                                This->DriverBindingHandle,     
                                ChildHandleBuffer[Index],   
                                EFI_OPEN_PROTOCOL_TEST_PROTOCOL);

            if (Status == EFI_SUCCESS) {
                Status = pBS->UninstallMultipleProtocolInterfaces (
                                ChildHandleBuffer[Index],
                                &gEfiBlockIoProtocolGuid,
                                (EFI_BLOCK_IO_PROTOCOL *)(SataDeviceInterface->SataBlkIo),
                                NULL);
            }

            Status = pBS->UninstallMultipleProtocolInterfaces (
                            ChildHandleBuffer[Index],
                            &gDevicePathProtocolGuid,
                            SataDeviceInterface->DevicePathProtocol,
                            NULL);

            if (EFI_ERROR(Status)) {
                return EFI_DEVICE_ERROR;
            } else {

                //
                // Now free up all resources allocated.
                //
                if (SataDeviceInterface->AtapiDevice != NULL){
                    pBS->FreePool(SataDeviceInterface->AtapiDevice->PacketBuffer);
                    pBS->FreePool(SataDeviceInterface->AtapiDevice->InquiryData);
                    pBS->FreePool(SataDeviceInterface->AtapiDevice);
                }

                //
                // Freeup resources allocated for component names
                //
                if (SataDeviceInterface->UDeviceName != NULL) {
                    pBS->FreePool(SataDeviceInterface->UDeviceName->Language);
                    pBS->FreePool(SataDeviceInterface->UDeviceName->UnicodeString);
                    pBS->FreePool(SataDeviceInterface->UDeviceName);
                }

                //
                // Before uninstalling HDD security check whether it is installed or not
                //
                Status = pBS->OpenProtocol( ChildHandleBuffer[Index],
                            &gSecurityModeProtocolGuid,
                            NULL,
                            This->DriverBindingHandle,     
                            ChildHandleBuffer[Index], 
                            EFI_OPEN_PROTOCOL_TEST_PROTOCOL);

                if (Status == EFI_SUCCESS) {
                        if(HddSecurityInitProtocol != NULL) {
                            HddSecurityInitProtocol->StopSecurityModeSupport(SataDeviceInterface, TRUE);
                        }
                }

                //
                // Before uninstalling Hdd Smart check whether it is installed or not
                //
                Status = pBS->OpenProtocol( ChildHandleBuffer[Index],
                            &gSMARTProtocolGuid,
                            NULL,
                            This->DriverBindingHandle, 
                            ChildHandleBuffer[Index],
                            EFI_OPEN_PROTOCOL_TEST_PROTOCOL);

                if (Status == EFI_SUCCESS) {
                    if(HddSmartInitProtocol != NULL) {
                        if(HddSmartInitProtocol->SmartDiagonasticFlag) {
                            HddSmartInitProtocol->UnInstallSMARTInterface(SataDeviceInterface, TRUE);
                        }
                    }
                }

                //
                // Before uninstalling OPAL security interface check whether it is installed or not.
                //
                Status = pBS->OpenProtocol( ChildHandleBuffer[Index],
                            &gStorageSecurityProtocolGuid,
                            NULL,
                            This->DriverBindingHandle,
                            ChildHandleBuffer[Index], 
                            EFI_OPEN_PROTOCOL_TEST_PROTOCOL);

                if (Status == EFI_SUCCESS) {
                        if(OpalSecInitProtocol != NULL) {
                            OpalSecInitProtocol->UnInstallOpalSecurityInterface(SataDeviceInterface, TRUE);
                        }
                }

                pBS->FreePool(SataDeviceInterface->SataBlkIo->BlkIo.Media);
                pBS->FreePool(SataDeviceInterface->SataBlkIo);
                pBS->FreePool(SataDeviceInterface->SataDiskInfo);
                pBS->FreePool (SataDeviceInterface->DevicePathProtocol);
                DListDelete(&(AhciBusInterface->SataDeviceList), &(SataDeviceInterface->SataDeviceLink));
                pBS->FreePool (SataDeviceInterface);
            }
            NumberOfChildren--;
            Index++;
        }
    } else {

        //
        // Check if AHCI_BUS_PROTOCOL can be removed. No device other 
        // than Port Multiplier can be present.
        //
        dlink = AhciBusInterface->SataDeviceList.pHead; 
        Status = EFI_SUCCESS;
        if (dlink){ 
            do {
                SataDeviceInterface = OUTTER(dlink, SataDeviceLink, SATA_DEVICE_INTERFACE);
                if (SataDeviceInterface->DeviceType != PMPORT ||
                    SataDeviceInterface->DeviceState == DEVICE_CONFIGURED_SUCCESSFULLY) {
                    Status = EFI_DEVICE_ERROR;
                    break;                
                }
                dlink = dlink-> pNext;
            }while (dlink);    
        }

        if (EFI_ERROR(Status)) { 
            return Status;
        }

        //
        // Free PM resources
        //
    	dlink = AhciBusInterface->SataDeviceList.pHead; 
        Status = EFI_SUCCESS;
        if (dlink){ 
            do {
                SataDeviceInterface = OUTTER(dlink, SataDeviceLink, SATA_DEVICE_INTERFACE);
                //
                // Now free up all resources allocated.
                //
                if (SataDeviceInterface->AtapiDevice != NULL){
                    pBS->FreePool(SataDeviceInterface->AtapiDevice->PacketBuffer);
                    pBS->FreePool(SataDeviceInterface->AtapiDevice->InquiryData);
                    pBS->FreePool(SataDeviceInterface->AtapiDevice);
                }

                //
                // Freeup resources allocated for component names
                //
                if (SataDeviceInterface->UDeviceName != NULL) {
                    pBS->FreePool(SataDeviceInterface->UDeviceName->Language);
                    pBS->FreePool(SataDeviceInterface->UDeviceName->UnicodeString);
                    pBS->FreePool(SataDeviceInterface->UDeviceName);
                }
                DListDelete(&(AhciBusInterface->SataDeviceList), &(SataDeviceInterface->SataDeviceLink));
                dlink = dlink-> pNext;
                pBS->FreePool (SataDeviceInterface);
            }while (dlink);    
        }    

        //
        // Close all the protocols opened in Start Function
        //
        Status = pBS->CloseProtocol ( Controller,
                            &gEfiIdeControllerInitProtocolGuid,
                            This->DriverBindingHandle,
                            Controller);
        //
        // AtaPass Thru uninstall
        //
        Status = pBS->LocateProtocol (
                            &gAtaPassThruInitProtocolGuid,
                            NULL,
                            &AtaPassThruInitProtocol
                    );

         if(!EFI_ERROR(Status)) {
             if(AtaPassThruInitProtocol != NULL) {
                 AtaPassThruInitProtocol->StopAtaPassThruSupport(Controller, TRUE);
             }
         }

        //
        // SCSIPassThruAtapi uninstall
        //
        Status = pBS->LocateProtocol (
                            &gScsiPassThruAtapiInitProtocolGuid,
                            NULL,
                            &gScsiPassThruAtapiInitProtocol
                    );

         if(!EFI_ERROR(Status)) {
             if(gScsiPassThruAtapiInitProtocol != NULL) {
                 gScsiPassThruAtapiInitProtocol->StopScsiPassThruAtapiSupport(Controller, TRUE);
             }
         }

        Status = pBS->CloseProtocol( Controller,
                            &gEfiAhciBusProtocolGuid,
                            This->DriverBindingHandle,
                            Controller);

        Status = pBS->UninstallProtocolInterface ( Controller,
                            &gEfiAhciBusProtocolGuid,
                            AhciBusInterface);

        if (EFI_ERROR(Status)) {

            Status = pBS->OpenProtocol( Controller,
                            &gEfiAhciBusProtocolGuid,
                            (VOID **)&AhciBusInterface,
                            This->DriverBindingHandle,
                            Controller,
                            EFI_OPEN_PROTOCOL_BY_DRIVER);

            Status = pBS->OpenProtocol( Controller,
                            &gEfiIdeControllerInitProtocolGuid,
                            (VOID **)&IdeControllerInterface,
                            This->DriverBindingHandle,     
                            Controller,   
                            EFI_OPEN_PROTOCOL_BY_DRIVER	);

            return EFI_DEVICE_ERROR;
        }

        // Free the Pages allocated for the FIS and Command List
        if (AhciBusInterface->Address1) {
           pBS->FreePages(AhciBusInterface->Address1,
                          EFI_SIZE_TO_PAGES(AhciBusInterface->NumberofPortsImplemented * RECEIVED_FIS_SIZE + 0x100 ));
        }

        if (AhciBusInterface->Address2) {
            pBS->FreePages((AhciBusInterface->Address2),EFI_SIZE_TO_PAGES(COMMAND_LIST_SIZE_PORT * 2));
        }

    }

    return EFI_SUCCESS;

}

//**********************************************************************
//<AMI_PHDR_START>
//
// Procedure:   InstallAhciBusProtocol
//
// Description: Installs BUS Init Protocol on the IDE controller Handle
//
// Input:
//  IN EFI_HANDLE                   Controller,
//  IDE_BUS_INIT_PROTOCOL           *IdeBusInitInterface,
//  IDE_CONTROLLER_PROTOCOL         *IdeControllerInterface,
//  EFI_PCI_IO_PROTOCOL             *PciIO
//
// Output:
//  EFI_STATUS
//
// Modified:
//      
// Referrals: AllocatePool, InstallProtocolInterface, AhciInitController
//
// Notes:
//   1. Call AhciInitController
//   2. Install gEfiAhciBusProtocolGuid protocol
//
//<AMI_PHDR_END>
//**********************************************************************
EFI_STATUS
InstallAhciBusProtocol (
    IN EFI_HANDLE                       Controller,
    IN OUT AHCI_BUS_PROTOCOL            *AhciBusInterface,
    IN EFI_IDE_CONTROLLER_INIT_PROTOCOL *IdeControllerInterface,
    IN EFI_PCI_IO_PROTOCOL              *PciIO
 )
{
    
    EFI_STATUS                  Status;
    UINT8                       PciConfig[16];
#if SBIDE_SUPPORT
    IDE_SETUP_PROTOCOL        *gIdeSetupProtocol;
#endif

    //
    // Initialize the default Values
    //
    ZeroMemory (AhciBusInterface, sizeof(AHCI_BUS_PROTOCOL));

    AhciBusInterface->ControllerHandle = Controller;
    AhciBusInterface->IdeControllerInterface = IdeControllerInterface;
    AhciBusInterface->PciIO = PciIO;
    DListInit(&(AhciBusInterface->SataDeviceList));

    AhciBusInterface->SataReadWritePio          = SataReadWritePio;
    AhciBusInterface->SataPioDataOut            = SataPioDataOut;
    AhciBusInterface->ExecutePioDataCommand     = ExecutePioDataCommand;
    AhciBusInterface->ExecuteNonDataCommand     = ExecuteNonDataCommand;
    AhciBusInterface->WaitforCommandComplete    = WaitforCommandComplete;
    AhciBusInterface->GeneratePortReset         = GeneratePortReset;
    AhciBusInterface->ExecutePacketCommand      = ExecutePacketCommand;
    AhciBusInterface->AHCIRAIDMODE    = TRUE;       // Set TRUE when in AHCI mode

    Status = PciIO->Pci.Read ( PciIO,
                                EfiPciIoWidthUint8,
                                0,
                                sizeof (PciConfig),
                                PciConfig
                                );

    if (PciConfig [IDE_SUB_CLASS_CODE]== SCC_RAID_CONTROLLER ){
        AhciBusInterface->AHCIRAIDMODE    = FALSE;
    }

    //
    // Using setup question if needed, set Bit 0 to enable/Disable
    // Acoustic Power Management.
    // Set bit1 only if HDD Losses power in S3 state. HDD freeze lock 
    // command will be issued during S3 resume when this bit is set 
    // and also if Password is enabled for HDD, it will be unlocked 
    // during S3 resume.
    //

    AhciBusInterface->Acoustic_Enable = 0; // ACOUSTIC_SUPPORT_DISABLE

#if SBIDE_SUPPORT
    Status = pBS->LocateProtocol(&gIdeSetupProtocolguid, NULL, &gIdeSetupProtocol);

    #if ACOUSTIC_MANAGEMENT_SUPPORT
        if (!EFI_ERROR(Status)) {
            AhciBusInterface->Acoustic_Enable = gIdeSetupProtocol->AcousticPwrMgmt;
            AhciBusInterface->Acoustic_Management_Level   = gIdeSetupProtocol->AcousticLevel;
        } else {
            AhciBusInterface->Acoustic_Enable = ACOUSTIC_SUPPORT_DISABLE;
            AhciBusInterface->Acoustic_Management_Level   = ACOUSTIC_LEVEL_BYPASS;
        }    	
    #endif //End of ACOUSTIC_MANAGEMENT_SUPPORT
#endif // end of if SBIDE_SUPPORT


    // Initialize PrevPortNum and PrevPortMultiplierPortNum for AtaPassThru to 0xFFFF

    AhciBusInterface->PrevPortNum = 0xffff;
    AhciBusInterface->PrevPortMultiplierPortNum = 0xffff;

    // 
    // Init AHCI Controller
    //
    Status = AhciInitController(AhciBusInterface);
    if (EFI_ERROR(Status)) return Status;

    Status = pBS->InstallProtocolInterface(
                        &Controller,
                        &gEfiAhciBusProtocolGuid,
                        EFI_NATIVE_INTERFACE,
                        AhciBusInterface);

    return Status;
}

//**********************************************************************
//<AMI_PHDR_START>
//
// Procedure:   AhciInitController
//
// Description: Initializes AHCI Controller
//
// Input:
// IN OUT   AHCI_BUS_PROTOCOL       *AhciBusInterface
//
// Output:
//  EFI_STATUS
//
//
// Notes:
//  1. Update internal Data area about the AHCI controller Capabilities.
//  2. Allocate memory for FIS and CommandList
//  3. Enable AHCI mode
//  3. Disable all the ports
//
//<AMI_PHDR_END>
//**********************************************************************
EFI_STATUS
AhciInitController (
    IN OUT AHCI_BUS_PROTOCOL        *AhciBusInterface
)
{
    EFI_STATUS      Status;
    UINT8           PciConfig[40];
    UINT32          PortsImplemented;
    UINT8           i, PortNumber;
    UINT32          AhciBaseAddr;
    UINTN			AllocatePageSize = 0;
    UINT32          Data32;


    //
    // Make sure AHCI Base address is programmed Properly
    //
    Status = AhciBusInterface->PciIO->Pci.Read (
                                      AhciBusInterface->PciIO,
                                      EfiPciIoWidthUint8,
                                      0,
                                      sizeof (PciConfig),
                                      PciConfig
                                      );

    if (EFI_ERROR(Status)) { return Status;}
    
    AhciBusInterface->AhciBaseAddress = *(UINT32 *)(PciConfig + PCI_ABAR); 
    if (!AhciBusInterface->AhciBaseAddress) return EFI_DEVICE_ERROR;   

    AhciBaseAddr = (UINT32) (AhciBusInterface->AhciBaseAddress);

#if INDEX_DATA_PORT_ACCESS
    Status = InitilizeIndexDataPortAddress (AhciBusInterface->PciIO);
#endif

    //
    // Get AHCI Capability
    //
    AhciBusInterface->HBACapability = HBA_REG32(AhciBaseAddr, HBA_CAP);
    if (AhciBusInterface->HBACapability == 0xFFFFFFFF) return EFI_DEVICE_ERROR; // Not decoded properly

    //
    // Get # of Ports Implemented (bit map)
    //
    AhciBusInterface->HBAPortImplemented = HBA_REG32(AhciBaseAddr, HBA_PI);
    if (!AhciBusInterface->HBAPortImplemented)  return EFI_DEVICE_ERROR;

    //
    // Cross check whether # of Ports implemented is less or equal to
    // Max. # of ports supported by the silicon
    //
    PortsImplemented = AhciBusInterface->HBAPortImplemented;
    AhciBusInterface->NumberofPortsImplemented = 0;
    for ( ;PortsImplemented; PortsImplemented >>= 1){ 
        if  (PortsImplemented & 1) AhciBusInterface->NumberofPortsImplemented++;
    }
    if (((AhciBusInterface->HBACapability & HBA_CAP_NP_MASK) + 1) < AhciBusInterface->NumberofPortsImplemented)
            { return EFI_DEVICE_ERROR; }

    //
    //  Get the HBA version #
    //
    AhciBusInterface->AhciVersion = HBA_REG32(AhciBaseAddr, HBA_VS);    

    //
    //  Set AE bit
    //
    HBA_REG32_OR(AhciBaseAddr, HBA_GHC, HBA_GHC_AE);

    //
    // Allocate memory for FIS. Should be aligned on 256 Bytes. Each 
    // Port will have it own FIS data area.
    //

    AhciBusInterface->PortFISBaseAddr=0xFFFFFFFF;
    AllocatePageSize = AhciBusInterface->NumberofPortsImplemented * RECEIVED_FIS_SIZE + 0x100;

    Status = pBS->AllocatePages (
    					AllocateMaxAddress,
    					EfiBootServicesData,
    					EFI_SIZE_TO_PAGES(AllocatePageSize),  // Bytes->4KiloBytes conversion
    					(EFI_PHYSICAL_ADDRESS*)&(AhciBusInterface->PortFISBaseAddr));

    ZeroMemory ((VOID *) AhciBusInterface->PortFISBaseAddr, 
                AhciBusInterface->NumberofPortsImplemented * RECEIVED_FIS_SIZE + 0x100);
    AhciBusInterface->PortFISBaseAddrEnd = AhciBusInterface->PortFISBaseAddr + 
                                    AhciBusInterface->NumberofPortsImplemented * RECEIVED_FIS_SIZE;
    AhciBusInterface->Address1 = AhciBusInterface->PortFISBaseAddr; // Will be used to free the memory later
    AhciBusInterface->PortFISBaseAddr = (AhciBusInterface->PortFISBaseAddr & (~0xFF))+ 0x100;

    //
    // Allocate memory for Command List (1KB aligned) and Command Table (128KB aligned).
    // All the ports in the controller will share Command List and Command table data Area.
    //

    AhciBusInterface->PortCommandListBaseAddr=0xFFFFFFFF;
    AllocatePageSize = COMMAND_LIST_SIZE_PORT * 2;

    Status = pBS->AllocatePages (
    					AllocateMaxAddress,
    					EfiBootServicesData,
    					EFI_SIZE_TO_PAGES(AllocatePageSize),  // Bytes->4KiloBytes conversion
    					(EFI_PHYSICAL_ADDRESS*)&(AhciBusInterface->PortCommandListBaseAddr));

    ZeroMemory ((VOID *)AhciBusInterface->PortCommandListBaseAddr, COMMAND_LIST_SIZE_PORT * 2);
    AhciBusInterface->Address2 = AhciBusInterface->PortCommandListBaseAddr;

    AhciBusInterface->PortCommandListBaseAddr = (AhciBusInterface->PortCommandListBaseAddr & (~0x3FF)) + 0x400;
    AhciBusInterface->PortCommandListLength = 0x20; 
    AhciBusInterface->PortCommandTableBaseAddr = AhciBusInterface->PortCommandListBaseAddr + 0x80;
    AhciBusInterface->PortCommandTableLength = COMMAND_LIST_SIZE_PORT - 0x80;

    //
    // Make sure controller is not running
    //
    PortsImplemented = AhciBusInterface->HBAPortImplemented;
    PortNumber = 0;
    for (i=0; PortsImplemented; PortsImplemented>>=1, PortNumber++){
        if (PortsImplemented & 1) { 

            //
            // Program PxCLB and PxFB
            //
            HBA_PORT_WRITE_REG32 (AhciBaseAddr, PortNumber, HBA_PORTS_CLB,AhciBusInterface->PortCommandListBaseAddr);

            HBA_PORT_WRITE_REG32 (AhciBaseAddr, PortNumber, 0x0008, AhciBusInterface->PortFISBaseAddr +(i * RECEIVED_FIS_SIZE));

            //
            // Clear Start
            //
            HBA_PORT_REG32_AND(AhciBaseAddr, PortNumber, HBA_PORTS_CMD, ~(HBA_PORTS_CMD_ST));

            //
            // Make sure CR is 0 with in 500msec
            //
            Status = WaitForMemClear(AhciBaseAddr, PortNumber, HBA_PORTS_CMD,
                            HBA_PORTS_CMD_CR,
                            HBA_CR_CLEAR_TIMEOUT
            );

            if (EFI_ERROR(Status)) { 
                // Get the Port Speed allowed and Interface Power Management Transitions Allowed
                // Pass the values for PortReset. 
                Data32 = HBA_PORT_REG32 ((UINT32)(AhciBusInterface->AhciBaseAddress), PortNumber, HBA_PORTS_SCTL);
                Data32 &= 0xFF0;          

                Status = GeneratePortReset(AhciBusInterface, NULL, PortNumber, 0xFF,
                                        (UINT8)((Data32 & 0xF0) >> 4), (UINT8)(Data32 >> 8));
            }

            if (EFI_ERROR(Status)) { 
                HostReset(AhciBusInterface);
            }

            //
            // Clear FIS receive enable.
            //
            HBA_PORT_REG32_AND (AhciBaseAddr, PortNumber, 
                                HBA_PORTS_CMD, ~(HBA_PORTS_CMD_FRE));
            //
            // Make sure FR is 0 with in 500msec
            //
            Status = WaitForMemClear(AhciBaseAddr, PortNumber, HBA_PORTS_CMD,
                                    HBA_PORTS_CMD_FR,
                                    HBA_FR_CLEAR_TIMEOUT);

            if (EFI_ERROR(Status)) { 
                continue;
            }

            HBA_PORT_REG32_OR (AhciBaseAddr, PortNumber,
                                  HBA_PORTS_SERR, HBA_PORTS_ERR_CLEAR); // Clear Status register

            i++;        
        }
    }
    return EFI_SUCCESS;
}


//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   CheckPortImplemented
//
// Description: Check if the port is implemented in the AHCI Controller
//
// Input:           
//  IN AHCI_BUS_PROTOCOL        *AhciBusInterface, 
//  IN UINT8                    Port 
//
// Output:      
//   EFI_STATUS
//
// Notes:	
//  1. Check Port Implemented register whether the PORT is 
//     implemented in the Controller or not.
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END> 
EFI_STATUS
CheckPortImplemented (
    IN AHCI_BUS_PROTOCOL                   *AhciBusInterface, 
    IN UINT8                               Port
)
{

    if (AhciBusInterface->HBAPortImplemented & (1<< Port)) return EFI_SUCCESS;

    return EFI_NOT_FOUND;

}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   AhciDetectDevice
//
// Description:  Detects a SATA device connected to given Port and PMPort
//
// Input:           
//  IN AHCI_BUS_PROTOCOL                   *AhciBusInterface, 
//  IN EFI_IDE_CONTROLLER_INIT_PROTOCOL    *IdeControllerInterface, 
//  IN UINT8                               Port, 
//  IN UINT8                               PMPort
//
// Output:      
//   EFI_STATUS
//
// Modified:
//      
// Referrals:  CheckDevicePresence CheckPMDevicePresence GenerateSoftReset
//
// Notes:	
//  1. if CheckDevicePresence fails exit.
//  2. If Controller supports PM, issue Softreset
//  3. Check the Device Signature.
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END> 
EFI_STATUS
AhciDetectDevice (
    IN AHCI_BUS_PROTOCOL                   *AhciBusInterface, 
    IN EFI_IDE_CONTROLLER_INIT_PROTOCOL    *IdeControllerInterface, 
    IN UINT8                               Port, 
    IN UINT8                               PMPort
)
{

    EFI_STATUS              Status;
    UINT32                  AhciBaseAddr = (UINT32)(AhciBusInterface->AhciBaseAddress);
    SATA_DEVICE_INTERFACE   *SataDevInterface = NULL;

    PROGRESS_CODE(DXE_IDE_DETECT);

    IdeControllerInterface->NotifyPhase (IdeControllerInterface, EfiIdeBusBeforeDevicePresenceDetection, Port);

    SataDevInterface = GetSataDevInterface(AhciBusInterface, Port, PMPort);
    
    if (!SataDevInterface){

        //
        // A device is present.
        //
        Status = pBS->AllocatePool (EfiBootServicesData,
                    sizeof(SATA_DEVICE_INTERFACE),
                    (VOID**)&SataDevInterface);
        if (EFI_ERROR(Status)) return Status;

        ZeroMemory (SataDevInterface, sizeof(SATA_DEVICE_INTERFACE));

        SataDevInterface->PortNumber = Port;
        SataDevInterface->PMPortNumber = PMPort;
        SataDevInterface->AhciBusInterface = AhciBusInterface;
        SataDevInterface->DeviceState = DEVICE_IN_RESET_STATE;

        //
        // Update Base addresses
        //
        SataDevInterface->PortCommandListBaseAddr = HBA_PORT_REG32 (AhciBaseAddr, Port, HBA_PORTS_CLB);
        SataDevInterface->PortFISBaseAddr = HBA_PORT_REG32 (AhciBaseAddr, Port, HBA_PORTS_FB);

        //
        // Add to the AhciBusInterface
        //
        DListAdd(&(AhciBusInterface->SataDeviceList), &(SataDevInterface->SataDeviceLink));   

    
    }

    if (PMPort == 0xFF) {
        Status = CheckDevicePresence (SataDevInterface, IdeControllerInterface, Port, PMPort);
    }
    else {
        Status = CheckPMDevicePresence (SataDevInterface, IdeControllerInterface, Port, PMPort);
    }

    if (EFI_ERROR(Status)) {
        IdeControllerInterface->NotifyPhase (IdeControllerInterface, EfiIdeBusAfterDevicePresenceDetection, Port);
        if (SataDevInterface->DeviceState == DEVICE_IN_RESET_STATE) {
            DListDelete(&(AhciBusInterface->SataDeviceList), &(SataDevInterface->SataDeviceLink));
            pBS->FreePool(SataDevInterface);
        }
        return EFI_DEVICE_ERROR;
    }

    #if PORT_MULTIPLIER_SUPPORT
    //
    // Check if PM support is present
    //
    if (AhciBusInterface->HBACapability & HBA_CAP_SPM) {
        Status = GenerateSoftReset(SataDevInterface, PMPort == 0xFF ? CONTROL_PORT : PMPort);
        if (EFI_ERROR(Status)) {

            //
            // We know link has been established, meaning device is 
            // present. Maybe we need delay before giving a Soft reset.
            //
            Status = ReadytoAcceptCmd(SataDevInterface);
            if (!EFI_ERROR(Status)){
                pBS->Stall(3000000);        // 3sec delay
                Status = GenerateSoftReset(SataDevInterface, PMPort == 0xFF ? CONTROL_PORT : PMPort);
            }
        }

        if (EFI_ERROR(Status)) {
            IdeControllerInterface->NotifyPhase (IdeControllerInterface, EfiIdeBusAfterDevicePresenceDetection, Port);
            if (SataDevInterface->DeviceState == DEVICE_IN_RESET_STATE) {
                DListDelete(&(AhciBusInterface->SataDeviceList), &(SataDevInterface->SataDeviceLink));
                pBS->FreePool(SataDevInterface);
            }
            return EFI_DEVICE_ERROR;
        }
    }
    #endif

    if (!(SataDevInterface->PortCommandListBaseAddr) || !(SataDevInterface->PortFISBaseAddr)) {
        ASSERT_EFI_ERROR(EFI_DEVICE_ERROR);
    }

    //
    // Save the Signature
    //
    SataDevInterface->Signature = HBA_PORT_REG32(AhciBaseAddr, Port, HBA_PORTS_SIG);
    switch (SataDevInterface->Signature) {
        case ATA_SIGNATURE_32:
            SataDevInterface->DeviceType = ATA;
            break;
        case ATAPI_SIGNATURE_32:
            SataDevInterface->DeviceType = ATAPI;
            break;
        case PMPORT_SIGNATURE:
            SataDevInterface->DeviceType = PMPORT;
            // 1 sec Delay needed for the next device to be discovered from PM.
            pBS->Stall(1000000);        
            break;
        default:
        Status =  EFI_DEVICE_ERROR;
    }

#if !HDD_PASSWORD_SUPPORT_UNDER_RAIDMODE
    if ((!AhciBusInterface->AHCIRAIDMODE) && (SataDevInterface->DeviceType == ATA)) {
        DListDelete(&(AhciBusInterface->SataDeviceList), &(SataDevInterface->SataDeviceLink));
        pBS->FreePool(SataDevInterface);
        Status =  EFI_DEVICE_ERROR;
    }
#endif

#if !SUPPORT_ATAPI_IN_RAID_MODE

    //
    // If the Atapi devices are handled by Raid option rom, then 
    // don't configure the Atapi devices.
    //
    if ((!AhciBusInterface->AHCIRAIDMODE) && (SataDevInterface->DeviceType == ATAPI)) {
        DListDelete(&(AhciBusInterface->SataDeviceList), &(SataDevInterface->SataDeviceLink));
        pBS->FreePool(SataDevInterface);
        Status =  EFI_DEVICE_ERROR;
    }
#endif
    IdeControllerInterface->NotifyPhase (IdeControllerInterface, EfiIdeBusAfterDevicePresenceDetection, Port);

    return Status;

}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   CheckDevicePresence
//
// Description: Check if any device is connected to the port
//
// Input:           
//  IN SATA_DEVICE_INTERFACE                *SataDevInterface,
//  IN EFI_IDE_CONTROLLER_INIT_PROTOCOL     *IdeControllerInterface, 
//  IN UINT8                                Port, 
//  IN UINT8                                PMPort
//
// Output:      
//   EFI_STATUS
//
// Modified:
//
// Referrals: HandlePortComReset CheckValidDevice GeneratePortReset
//
// Notes:
//  1. If Staggered spin-up is supported, power-up the device.
//  2. Call CheckValidDevice if success exit. Else generate Softreset.
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END> 
EFI_STATUS
CheckDevicePresence (
    IN SATA_DEVICE_INTERFACE                *SataDevInterface,
    IN EFI_IDE_CONTROLLER_INIT_PROTOCOL     *IdeControllerInterface, 
    IN UINT8                                Port, 
    IN UINT8                                PMPort
)
{

    EFI_STATUS                  Status;
    AHCI_BUS_PROTOCOL           *AhciBusInterface = SataDevInterface->AhciBusInterface; 
    UINT32                      AhciBaseAddr = (UINT32)(AhciBusInterface->AhciBaseAddress);
    UINT8                       CapIss;  
    UINT8                       PortSpeed=0;
    UINT8                       CurrentPortSpeed=0;
    UINT32                      Data32;

    //
    // PM disabled
    //
    HBA_PORT_REG32_OR (AhciBaseAddr, Port, HBA_PORTS_SCTL, HBA_PORTS_SCTL_IPM_PSD_SSD);       

    //
    // Clear Status register
    //
    HBA_PORT_REG32_OR (AhciBaseAddr, Port, HBA_PORTS_SERR, HBA_PORTS_ERR_CLEAR); 
    HBA_PORT_REG32_OR (AhciBaseAddr, Port, HBA_PORTS_IS, HBA_PORTS_IS_CLEAR); 

    //
    // Get the Interface Speed Support( Maximum Speed supported)
    //
    CapIss = (UINT8)((HBA_REG32(AhciBaseAddr, HBA_CAP) & HBA_CAP_ISS_MASK)>>20);    

    //
    // Get the Speed Allowed (SPD) for the Port. Maximum speed allowed for the Port
    //
    PortSpeed = (UINT8)((HBA_PORT_REG32(AhciBaseAddr, Port, HBA_PORTS_SCTL) 
                            & HBA_PORTS_SCTL_SPD_MASK)>>4); 

    //
    // If the Maximum speed allowed is programmed for the port, use the Port Speed allowed value 
    //
    if(PortSpeed != 0 ) {
        if(PortSpeed > CapIss) {
            //
            // Port Speed allowed can't be more than Interface Speed. So limit Port speed to Interface Speed 
            //
            PortSpeed = CapIss;
        }
    } else {
        //
        // If there is no Maximum speed allowed for the port, use the Interface Speed
        //
        PortSpeed = CapIss;
    }   

    //
    // Check if Link is already established
    //
    if ((HBA_PORT_REG32 (AhciBusInterface->AhciBaseAddress, Port, HBA_PORTS_SSTS) 
            & HBA_PORTS_SSTS_DET_MASK) == HBA_PORTS_SSTS_DET_PCE) {

        //
        // As the Link is already established, get the negotiated interface
        // communication speed
        //
        CurrentPortSpeed = (UINT8)((HBA_PORT_REG32(AhciBaseAddr, Port, HBA_PORTS_SSTS) 
                                & HBA_PORTS_SSTS_SPD_MASK)>>4); 

        //
        // Check the Current Interface Speed with Speed Allowed. If current inerface speed is more than 
        // Speed allowed set, then set the port speed according to the speed allowed 
        //        
        if( CurrentPortSpeed > PortSpeed) {

            Status = GeneratePortReset(AhciBusInterface, SataDevInterface, Port, PMPort,
                    PortSpeed, HBA_PORTS_SCTL_IPM_PSSD);
        }
    } else {
        //
        // Link Not Established. Set SPD by PortSpeed 
        //
        CapIss = (UINT8)((HBA_REG32(AhciBaseAddr, HBA_CAP) & HBA_CAP_ISS_MASK)>>20);    
        HBA_PORT_REG32_AND_OR (AhciBaseAddr, Port, HBA_PORTS_SCTL, ~HBA_PORTS_SCTL_SPD_MASK,PortSpeed<<4 );
    }

    //
    //  Check if Staggered Spinup is supported
    //
    if (HBA_REG32 (AhciBaseAddr,  HBA_CAP) & HBA_CAP_SSS) {

        //
        // Check if Link is already established, if yes dodn't expect a COMRESET
        //
        if ((HBA_PORT_REG32 (AhciBusInterface->AhciBaseAddress, Port, HBA_PORTS_SSTS) 
            & HBA_PORTS_SSTS_DET_MASK) != HBA_PORTS_SSTS_DET_PCE) {
            //
            // Enable FIS Receive Enable
            //
            HBA_PORT_REG32_OR (AhciBaseAddr, Port, HBA_PORTS_CMD, HBA_PORTS_CMD_FRE); 

            //
            // Wait till FIS is running
            //
            WaitForMemSet(AhciBaseAddr, Port, HBA_PORTS_CMD,
                                    HBA_PORTS_CMD_FR,
                                    HBA_PORTS_CMD_FR,
                                    HBA_FR_CLEAR_TIMEOUT);


            HBA_PORT_REG32_OR (AhciBaseAddr, Port, HBA_PORTS_CMD, HBA_PORTS_CMD_SUD); // Spin up the device

            //
            // Todo Todo delay necessary here after power up?
            //
            Status = HandlePortComReset(AhciBusInterface, NULL, Port, 0xFF);

            //
            //  Disable FIS Receive Enable
            //
            HBA_PORT_REG32_AND (AhciBaseAddr, Port, HBA_PORTS_CMD, ~HBA_PORTS_CMD_FRE);
  
            IdeControllerInterface->NotifyPhase (IdeControllerInterface, EfiIdeBusAfterDevicePresenceDetection, Port);
            }
        else {
            HBA_PORT_REG32_OR (AhciBaseAddr, Port, HBA_PORTS_CMD, HBA_PORTS_CMD_SUD); // Spin up the device
        }
    }

    //
    // Check if Device detected. And check if Cold Presence logic 
    // is enabled. If yes enable POD
    //
    if (((HBA_PORT_REG32 (AhciBaseAddr, Port, HBA_PORTS_SSTS) & HBA_PORTS_SSTS_DET_MASK) == HBA_PORTS_SSTS_DET_PCE) && 
            (HBA_PORT_REG32(AhciBaseAddr, Port, HBA_PORTS_CMD) & HBA_PORTS_CMD_CPD)) {
        HBA_PORT_REG32_OR (AhciBaseAddr, Port, HBA_PORTS_CMD, HBA_PORTS_CMD_POD);
    } 

    Status = CheckValidDevice(AhciBusInterface, Port, PMPort);

#if PORT_MULTIPLIER_SUPPORT
    // If PORT Multiplier support is enabled, SoftReset generated later will get the signature. 
    // No need for this additional Port Reset here
    if ((HBA_PORT_REG32 (AhciBaseAddr, Port, HBA_PORTS_SSTS) & HBA_PORTS_SSTS_DET_MASK) == HBA_PORTS_SSTS_DET_PCE) {
        return EFI_SUCCESS;
    }
#else
    if (EFI_ERROR(Status)) {
        IdeControllerInterface->NotifyPhase (
                                    IdeControllerInterface,
                                    EfiIdeBeforeChannelReset,
                                    (UINT8)Port
                                    );

        // Get the Port Speed allowed and Interface Power Management Transitions Allowed
        // Pass the values for PortReset. 
        Data32 = HBA_PORT_REG32 ((UINT32)(AhciBusInterface->AhciBaseAddress), Port, HBA_PORTS_SCTL);
        Data32 &= 0xFF0;          

        Status = GeneratePortReset(
                                    AhciBusInterface,
                                    SataDevInterface,
                                    Port,
                                    PMPort,
                                    (UINT8)((Data32 & 0xF0) >> 4),
                                    (UINT8)(Data32 >> 8)
                                  );
        
        IdeControllerInterface->NotifyPhase (
                                    IdeControllerInterface,
                                    EfiIdeAfterChannelReset,
                                    (UINT8)Port
                                   );
    }
#endif
    return Status;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   CheckPMDevicePresence
//
// Description: Checks for the presence device behind a Port Multiplier.
//
// Input:           
//  SATA_DEVICE_INTERFACE               *SataDevInterface, 
//  EFI_IDE_CONTROLLER_INIT_PROTOCOL    *IdeControllerInterface, 
//  UINT8                               Port, 
//  UINT8                               PMPort
//
// Output:      
//  EFI_STATUS
//
// Modified:
//      
// Referrals: ReadWritePMPort GeneratePortReset
//
// Notes:
//  1. Check whether communication is established?
//  2. If yes exit else issues Port Reset
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END> 
EFI_STATUS
CheckPMDevicePresence (
    IN SATA_DEVICE_INTERFACE                *SataDevInterface, 
    IN EFI_IDE_CONTROLLER_INIT_PROTOCOL     *IdeControllerInterface, 
    IN UINT8                                Port, 
    IN UINT8                                PMPort
)
{

    EFI_STATUS                  Status = EFI_DEVICE_ERROR;
    AHCI_BUS_PROTOCOL           *AhciBusInterface = SataDevInterface->AhciBusInterface; 
    UINT32                      AhciBaseAddr = (UINT32)(AhciBusInterface->AhciBaseAddress);
    UINT32                      Data32 = 0, Init_SStatus = 0;

    ReadWritePMPort (SataDevInterface, PMPort, PSCR_0_SSTATUS, &Init_SStatus, FALSE);

    SataDevInterface->SControl = HBA_PORTS_SCTL_IPM_PSD_SSD;
    if ((Init_SStatus & HBA_PORTS_SSTS_DET_MASK) == HBA_PORTS_SSTS_DET_PCE) { 
        Data32 = HBA_PORTS_SCTL_IPM_PSD_SSD;
        ReadWritePMPort (SataDevInterface, PMPort, PSCR_2_SCONTROL, &Data32, TRUE);
    } else {

        //
        // Perform Port Reset to bring the communication back
        //
        IdeControllerInterface->NotifyPhase (
                                    IdeControllerInterface,
                                    EfiIdeBeforeChannelReset,
                                    (UINT8)Port
                                   );

        // Get the Port Speed allowed and Interface Power Management Transitions Allowed
        // Pass the values for PortReset. 
        Data32 = HBA_PORT_REG32 ((UINT32)(AhciBusInterface->AhciBaseAddress), Port, HBA_PORTS_SCTL);
        Data32 &= 0xFF0;          

        Status = GeneratePortReset(
                                    AhciBusInterface,
                                    SataDevInterface,
                                    Port,
                                    PMPort,
                                    (UINT8)((Data32 & 0xF0) >> 4),
                                    (UINT8)(Data32 >> 8)
                                  );
        
        IdeControllerInterface->NotifyPhase (
                                    IdeControllerInterface,
                                    EfiIdeAfterChannelReset,
                                    (UINT8)Port
                                   );

        // Giving a Softreset immediatly after Port Reset doesn't help to detect the 
        // devices behind PM quickly. Add a delay here before Softreset is generated.
        // Add 1Sec delay
        pBS->Stall(1000000);  
    }

    //
    // Clear Status register
    //
    HBA_PORT_REG32_OR (AhciBaseAddr, Port, HBA_PORTS_SERR, HBA_PORTS_ERR_CLEAR); 
    HBA_PORT_REG32_OR (AhciBaseAddr, Port, HBA_PORTS_IS, HBA_PORTS_IS_CLEAR); 

    Data32 = HBA_PORTS_ERR_CLEAR;
    ReadWritePMPort (SataDevInterface, PMPort, PSCR_1_SERROR, &Data32, TRUE);

    Data32 = 0;
    ReadWritePMPort (SataDevInterface, PMPort, PSCR_0_SSTATUS, &Data32, FALSE);

    if ((Data32 & HBA_PORTS_SSTS_DET_MASK) == HBA_PORTS_SSTS_DET_PCE) Status = EFI_SUCCESS;

    return Status;

}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   ConfigureSataPort
//
// Description: Configure Sata Port settings
//
// Input:           
//              IN SATA_DEVICE_INTERFACE   *SataDevInterface, 
//
// Output:      
//              EFI_SUCCESS
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END> 
EFI_STATUS
ConfigureSataPort (
    IN SATA_DEVICE_INTERFACE   *SataDevInterface
)
{

    // Check for the ATAPI device
    if (SataDevInterface->DeviceType == ATAPI) {
        //
        // Set Device is ATAPI Bit in CMD register
        //
        HBA_PORT_REG32_OR (
                        SataDevInterface->AhciBusInterface->AhciBaseAddress,
                        SataDevInterface->PortNumber,
                        HBA_PORTS_CMD,
                        HBA_PORTS_CMD_ATAPI
                       );
    }

    // Check the AHCI platform policy protocol to set the 
    // Drive LED on ATAPI Enable (DLAE) bit

    if(AhciPlatformPolicy->DriverLedOnAtapiEnable) {
        //
        // Set Drive LED on ATAPI Enable (DLAE) Bit in CMD register
        //
        HBA_PORT_REG32_OR (
                        SataDevInterface->AhciBusInterface->AhciBaseAddress,
                        SataDevInterface->PortNumber,
                        HBA_PORTS_CMD,
                        HBA_PORTS_CMD_DLAE
                       );
    }

    return EFI_SUCCESS;
}


//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   ConfigurePMPort
//
// Description: Configure Port Multiplier
//
// Input:           
//    IN SATA_DEVICE_INTERFACE   *SataDevInterface, 
//
// Output:      
//
// Modified:
//      
// Referrals: ReadWritePMPort
//
// Notes:
//      1. Read the number of Ports implemented in the Port Multiplier
//      2. Update PM attached bit in the AHCI controller.
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END> 
EFI_STATUS
ConfigurePMPort (
    IN SATA_DEVICE_INTERFACE   *SataDevInterface
)
{
    EFI_STATUS  Status;
    UINT32      Data;

    //
    // Read the number of Ports preset in PM
    //
    Status = ReadWritePMPort (SataDevInterface, CONTROL_PORT, GSCR_2, &Data, FALSE);
    SataDevInterface->NumPMPorts = ((UINT8)Data) - 1;

    //
    // Set PM Attched bit in CMD register
    //
    HBA_PORT_REG32_OR (
                        SataDevInterface->AhciBusInterface->AhciBaseAddress,
                        SataDevInterface->PortNumber,
                        HBA_PORTS_CMD,
                        HBA_PORTS_CMD_PMA
                       );

    return Status;

}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   ConfigureDevice
//
// Description: Configure the SATA device
//
// Input:           
//    IN SATA_DEVICE_INTERFACE       *SataDevInterface  
//    IN OUT EFI_ATA_COLLECTIVE_MODE **SupportedModes - 
//                                   Modes collection supported by the device 
//
// Output:      
//    EFI_STATUS
//
// Modified:
//      
// Referrals: GetIdentifyData, GeneratePortReset, ExecuteNonDataCommand, InitAcousticSupport
//
// Notes:
//      1. Get the Identify data command.
//      2. From the IdeControllerInit protocol, get the DMA & PIO supported
//      3. Issue Set feature command to set PIO, DMA and multiple mode
//      4. Initialize Acoustic, SMART, Power Management features.
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END> 
EFI_STATUS
ConfigureDevice (
    IN SATA_DEVICE_INTERFACE               *SataDevInterface,
    IN OUT EFI_ATA_COLLECTIVE_MODE         **SupportedModes 
)
{

    EFI_STATUS                          Status;
    AHCI_BUS_PROTOCOL                   *AhciBusInterface = SataDevInterface->AhciBusInterface; 
    EFI_IDE_CONTROLLER_INIT_PROTOCOL    *IdeControllerInterface = AhciBusInterface->IdeControllerInterface; 
    UINT8                               Port = SataDevInterface->PortNumber;
    UINT8                               PMPort = SataDevInterface->PMPortNumber;
    COMMAND_STRUCTURE                   CommandStructure;
    UINT8                               Data8;
    UINT32                              Data32;
    UINT8                               Index;
    UINT16                              DeviceName[41];
    CHAR8                               Language[] = "Eng";
    EFI_UNICODE_STRING_TABLE            *tempUnicodeTable;


    if (SataDevInterface->DeviceType == PMPORT) return EFI_SUCCESS; // This is a Port Multiplier

    Status = GetIdentifyData(SataDevInterface);
    if (EFI_ERROR(Status)) return EFI_DEVICE_ERROR;

#if !DISABLE_SOFT_SET_PREV
#if FORCE_HDD_PASSWORD_PROMPT
    if ((SataDevInterface->DeviceType == ATA) &&
        (SataDevInterface->IdentifyData.Reserved_76_79[0] != 0xFFFF )&&
        (SataDevInterface->IdentifyData.Reserved_76_79[2] & 0x0040)&&           // Software Preservation support
        (SataDevInterface->IdentifyData.Reserved_76_79[3] & 0x0040)){ // Software Preservation Enabled

        ZeroMemory(&CommandStructure, sizeof(COMMAND_STRUCTURE)); 

        CommandStructure.Features = DISABLE_SATA2_SOFTPREV;                     // Disable Software Preservation
        CommandStructure.SectorCount = 6;
        CommandStructure.Command = SET_FEATURE_COMMAND;
        ExecuteNonDataCommand (SataDevInterface, CommandStructure);

        // Get the Port Speed allowed and Interface Power Management Transitions Allowed
        // Pass the values for PortReset. 
        Data32 = HBA_PORT_REG32 ((UINT32)(AhciBusInterface->AhciBaseAddress), Port, HBA_PORTS_SCTL);
        Data32 &= 0xFF0;          

        GeneratePortReset(AhciBusInterface,
                            SataDevInterface,
                            Port,
                            PMPort,
                            (UINT8)((Data32 & 0xF0) >> 4),
                            (UINT8)(Data32 >> 8)
                           );

        CommandStructure.Features = 0x10;                                       // Enable Software Preservation
        CommandStructure.SectorCount = 6;
        CommandStructure.Command = SET_FEATURE_COMMAND;
        ExecuteNonDataCommand (SataDevInterface, CommandStructure);
    }
#endif
#endif

    //
    // Check if Device need spin-up
    //
     if ((SataDevInterface->IdentifyData.General_Config_0 & 4) &&
           (SataDevInterface->IdentifyData.Special_Config_2 == SPIN_UP_REQUIRED1 ||
            SataDevInterface->IdentifyData.Special_Config_2 == SPIN_UP_REQUIRED2 )){

       	ZeroMemory(&CommandStructure, sizeof(COMMAND_STRUCTURE)); 
        CommandStructure.Features = SET_DEVICE_SPINUP;
        CommandStructure.Command = SET_FEATURE_COMMAND;
        Status = ExecuteNonDataCommand (SataDevInterface, CommandStructure);

        //
        // Get the Identify Command once more
        //
        Status = GetIdentifyData(SataDevInterface);
        if (EFI_ERROR(Status)){
            return EFI_DEVICE_ERROR;
        }
    }

    Status = IdeControllerInterface->SubmitData(IdeControllerInterface,
                                                Port, 
                                                PMPort == 0xFF ? 0 : PMPort, 
                                                (EFI_IDENTIFY_DATA *) &(SataDevInterface->IdentifyData));
    if (EFI_ERROR(Status))
        return Status;

    Status = IdeControllerInterface->CalculateMode(IdeControllerInterface, 
                                                   Port, 
                                                   PMPort == 0xFF ? 0 : PMPort, 
                                                   SupportedModes);

    if (EFI_ERROR(Status) || (*SupportedModes == NULL) )
        return EFI_INVALID_PARAMETER;

    //
    // Check ExtMode
    //
    if ((*SupportedModes)->ExtMode[0].TransferProtocol) {      // Not Auto speed
        Status = GeneratePortReset(AhciBusInterface, SataDevInterface, Port, PMPort,
                    (*SupportedModes)->ExtMode[0].TransferProtocol, HBA_PORTS_SCTL_IPM_PSSD);
        if (PMPort != 0xFF) {
            Data32 = HBA_PORTS_ERR_CLEAR;
            ReadWritePMPort (SataDevInterface, PMPort, PSCR_1_SERROR, &Data32, TRUE);
        }
    }

    Status = IdeControllerInterface->SetTiming(IdeControllerInterface, 
                                               Port, 
                                               PMPort == 0xFF ? 0 : PMPort, 
                                               (*SupportedModes));
    if (EFI_ERROR(Status)) return Status;

    SataDevInterface->PIOMode = 0xff;
    SataDevInterface->SWDma = 0xff;
    SataDevInterface->MWDma = 0xff;
    SataDevInterface->UDma = 0xff;    

    if ((*SupportedModes)->PioMode.Valid)
        SataDevInterface->PIOMode = (*SupportedModes)->PioMode.Mode;

    if ((*SupportedModes)->SingleWordDmaMode.Valid)
        SataDevInterface->SWDma = (*SupportedModes)->SingleWordDmaMode.Mode;

    if ((*SupportedModes)->MultiWordDmaMode.Valid)
        SataDevInterface->MWDma = (*SupportedModes)->MultiWordDmaMode.Mode;

    if ((*SupportedModes)->UdmaMode.Valid)
        SataDevInterface->UDma = (*SupportedModes)->UdmaMode.Mode;

    SataDevInterface->IORdy = ((EFI_IDENTIFY_DATA *)&(SataDevInterface->IdentifyData))->AtaData.capabilities & 0x800;

	 if	((SataDevInterface->IdentifyData.Valid_Bits_53 & 0x2) && ((*SupportedModes)->PioMode.Valid)){
        	ZeroMemory(&CommandStructure, sizeof(COMMAND_STRUCTURE)); 
            CommandStructure.Features = SET_TRANSFER_MODE;
            CommandStructure.Command = SET_FEATURE_COMMAND;
            CommandStructure.SectorCount = PIO_FLOW_CONTROL | SataDevInterface->PIOMode;
            Status = ExecuteNonDataCommand (SataDevInterface, CommandStructure);
    }

    if (EFI_ERROR(Status))
        return EFI_DEVICE_ERROR;

    //
    // Issue Set Multiple Mode Command only for ATA device
    //
    if  (SataDevInterface->DeviceType == ATA){
        Data8 = SataDevInterface->IdentifyData.Maximum_Sector_Multiple_Command_47 & 0xff;
        if (Data8 & 0x2)  Data8 = 2;
        if (Data8 & 0x4)  Data8 = 0x4;
        if (Data8 & 0x8)  Data8 = 0x8;
        if (Data8 & 0x10) Data8 = 0x10;
        if (Data8 & 0x20) Data8 = 0x20;
        if (Data8 & 0x40) Data8 = 0x40;
        if (Data8 & 0x80) Data8 = 0x80;
        
        if (Data8 > 1) {
            ZeroMemory(&CommandStructure, sizeof(COMMAND_STRUCTURE)); 
            CommandStructure.Command = SET_MULTIPLE_MODE;
            CommandStructure.SectorCount = Data8;
            Status = ExecuteNonDataCommand (SataDevInterface, CommandStructure);
        }
    }

    //
    // Check if  UDMA is supported
    //
    if  (SataDevInterface->UDma != 0xff){
        ZeroMemory(&CommandStructure, sizeof(COMMAND_STRUCTURE)); 
        CommandStructure.Features = SET_TRANSFER_MODE;
        CommandStructure.Command = SET_FEATURE_COMMAND;
        CommandStructure.SectorCount = UDMA_MODE | SataDevInterface->UDma;
        Status = ExecuteNonDataCommand (SataDevInterface, CommandStructure);
    }
    else {
        if (SataDevInterface->MWDma != 0xff){
            ZeroMemory(&CommandStructure, sizeof(COMMAND_STRUCTURE)); 
            CommandStructure.Features = SET_TRANSFER_MODE;
            CommandStructure.Command = SET_FEATURE_COMMAND;
            CommandStructure.SectorCount = MWDMA_MODE | SataDevInterface->MWDma;
            Status = ExecuteNonDataCommand (SataDevInterface, CommandStructure);
        }
    }

    //
    // Convert the Device string from Engligh to Unicode
    //
    SataDevInterface->UDeviceName = NULL;
    for (Index = 0; Index < 40; Index += 2) {
        DeviceName[Index] = ((UINT8 *)SataDevInterface->IdentifyData.Model_Number_27)[Index + 1];
        DeviceName[Index + 1] = ((UINT8 *)SataDevInterface->IdentifyData.Model_Number_27)[Index];
    }
    DeviceName[40] = 0;                 // Word

    tempUnicodeTable = MallocZ(sizeof (EFI_UNICODE_STRING_TABLE) * 2);
    Status = pBS->AllocatePool (EfiBootServicesData,
                sizeof (Language),
                (VOID**)&tempUnicodeTable[0].Language
                );

    Status = pBS->AllocatePool (EfiBootServicesData,
                sizeof (DeviceName),
                (VOID**)&tempUnicodeTable[0].UnicodeString
                );

    pBS->CopyMem(tempUnicodeTable[0].Language, &Language, sizeof(Language)); 
    pBS->CopyMem(tempUnicodeTable[0].UnicodeString, DeviceName, sizeof (DeviceName)); 
    tempUnicodeTable[1].Language = NULL;
    tempUnicodeTable[1].UnicodeString = NULL;
    SataDevInterface->UDeviceName = tempUnicodeTable;

    #if SBIDE_SUPPORT
        InitMiscConfig(SataDevInterface);
    #endif	
    
    
    if( AhciPlatformPolicy->DipmSupport) {        
        // Initialize and Enable Device initiated Power management
        InitializeDipm(SataDevInterface);
    }
    
    if( AhciPlatformPolicy->DeviceSleepSupport) {
        // Initialize and Enable Device Sleep Support
        InitializeDeviceSleep(SataDevInterface);
    }

	
    ConfigurePowerUpInStandby(SataDevInterface);
    
    Status = GetIdentifyData(SataDevInterface);
    if (EFI_ERROR(Status)) return EFI_DEVICE_ERROR;

    return EFI_SUCCESS;        

}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   ConfigureController
//
// Description: Configure the AHCI Controller
//
// Input:           
//    IN SATA_DEVICE_INTERFACE   *SataDevInterface 
//    IN EFI_ATA_COLLECTIVE_MODE *SupportedModes - 
//                                  Modes collection supported by the device 
//
// Output:      
//    EFI_STATUS
//
//
// Notes:
//  1. Issue IdeControllerInterface->SetTiming for setting  uDMA 
//     and PIO mode timings in the controller.
//  2. Update the Read/Write command for the device
//  3. Update the Device name used in Component Name protocol
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END> 
EFI_STATUS
ConfigureController (
    IN SATA_DEVICE_INTERFACE               *SataDevInterface,
    IN EFI_ATA_COLLECTIVE_MODE             *SupportedModes
)
{
    AHCI_BUS_PROTOCOL                   *AhciBusInterface = SataDevInterface->AhciBusInterface; 
    EFI_IDE_CONTROLLER_INIT_PROTOCOL    *IdeControllerInterface = AhciBusInterface->IdeControllerInterface; 
    UINT8                               Port = SataDevInterface->PortNumber;
    UINT8                               PMPort = SataDevInterface->PMPortNumber;

    //
    // Check if UDMA and MWDMA are programmed successfully
    //
    if (SataDevInterface->UDma != 0xff) {
        if (!(ReturnMSBset((SataDevInterface->IdentifyData.UDMA_Mode_88 >> 8)) == SataDevInterface->UDma)) {
            SataDevInterface->UDma = ReturnMSBset((SataDevInterface->IdentifyData.UDMA_Mode_88 >> 8));
            SupportedModes->UdmaMode.Mode = SataDevInterface->UDma;
            IdeControllerInterface->SetTiming (IdeControllerInterface, Port, 
                                                PMPort == 0xFF ? 0 : PMPort, SupportedModes);
        }
    }
    else {
        if (SataDevInterface->MWDma != 0xff) {
            if (!(ReturnMSBset(SataDevInterface->IdentifyData.MultiWord_DMA_63 >> 8) == SataDevInterface->MWDma)) {
                SataDevInterface->MWDma = ReturnMSBset((SataDevInterface->IdentifyData.MultiWord_DMA_63 >> 8));
                SupportedModes->MultiWordDmaMode.Mode = SataDevInterface->MWDma;
                IdeControllerInterface->SetTiming (IdeControllerInterface, Port, 
                                                    PMPort == 0xFF ? 0 : PMPort, SupportedModes);
            }
        }
    }

    //
    // Check for ATA
    //
    if (SataDevInterface->DeviceType == ATA) {

        //
        //  Update IDE Read/Write Command
        //
        if  ((SataDevInterface->IdentifyData.Valid_Bits_59 & 0x100) && 
                (SataDevInterface->IdentifyData.Valid_Bits_59 & 0xff)) {    // Check if Multiple Read/Write
            if (SataDevInterface->IdentifyData.Command_Set_Supported_83 & 0x400) {

                    //
                    // 48Bit LBA supported
                    //
                    SataDevInterface->ReadCommand = READ_MULTIPLE_EXT;	
                    SataDevInterface->WriteCommand = WRITE_MULTIPLE_EXT;
                }
                else {
                    SataDevInterface->ReadCommand = READ_MULTIPLE;
                    SataDevInterface->WriteCommand = WRITE_MULTIPLE;
                }
            }                       // End of Multiple
        else {                      // 1 Block = 1 Sector
            if (SataDevInterface->IdentifyData.Command_Set_Supported_83 & 0x400) {

                    //
                    // 48Bit LBA supported
                    //
                    SataDevInterface->ReadCommand = READ_SECTORS_EXT;
                    SataDevInterface->WriteCommand = WRITE_SECTORS_EXT;
                }
                else {
                    SataDevInterface->ReadCommand = READ_SECTORS;
                    SataDevInterface->WriteCommand = WRITE_SECTORS;
                }
            }
        if (DMACapable(SataDevInterface)) {
            #if IDEBUSMASTER_SUPPORT
            SataDevInterface->ReadCommand = READ_DMA;
            SataDevInterface->WriteCommand = WRITE_DMA;
            if (SataDevInterface->IdentifyData.Command_Set_Supported_83 & 0x400) {

                //
                // 48Bit LBA supported
                //
                SataDevInterface->ReadCommand = READ_DMA_EXT;
                SataDevInterface->WriteCommand = WRITE_DMA_EXT;
            }
            #endif
        }
    }                                               // end of ATA

#if DISABLE_SOFT_SET_PREV

    //
    // Software settings preserved
    //
    if ((SataDevInterface->DeviceType == ATA) &&
        (SataDevInterface->IdentifyData.Reserved_76_79[0] != 0xFFFF )&&
        (SataDevInterface->IdentifyData.Reserved_76_79[2] & 0x0040)) {

            COMMAND_STRUCTURE           CommandStructure;
            EFI_STATUS                  Status;
            ZeroMemory(&CommandStructure, sizeof(COMMAND_STRUCTURE)); 
            CommandStructure.Command = SET_FEATURE_COMMAND;
            CommandStructure.Features = DISABLE_SATA2_SOFTPREV;
            CommandStructure.SectorCount = 6;
            ExecuteNonDataCommand (SataDevInterface, CommandStructure);

            //
            // Update the Identify device buffer
            //
            Status = GetIdentifyData(SataDevInterface);
            if (EFI_ERROR(Status)){
                return EFI_DEVICE_ERROR;
            }
    }
#endif

    return EFI_SUCCESS;

}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   InitializeDipm
//
// Description: Initialize Dipm in the device and controller
//
// Input:           
//              IN SATA_DEVICE_INTERFACE   *SataDevInterface 
//
// Output:      
//    VOID
//
//
// Notes:
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END> 
VOID
InitializeDipm (
    IN SATA_DEVICE_INTERFACE    *SataDevInterface
)
{
    AHCI_BUS_PROTOCOL       *AhciBusInterface = SataDevInterface->AhciBusInterface; 
    COMMAND_STRUCTURE       CommandStructure;

    ZeroMemory(&CommandStructure, sizeof(COMMAND_STRUCTURE)); 
    CommandStructure.Command        = SET_FEATURE_COMMAND;
    CommandStructure.SectorCount    = DiPM_SUB_COMMAND; // 0x03 : DiPM

    // Check Host Supports Aggressive Link Power Management 
    // and Check DiPM supported by device
    
    if((SataDevInterface->AhciBusInterface->HBACapability & HBA_CAP_SALP) && 
       (SataDevInterface->IdentifyData.Reserved_76_79[0] & IDENTIFY_DiPM_HIIPM_REQUESTS_CAPABLE) &&
       (SataDevInterface->IdentifyData.Reserved_76_79[2] & IDENTIFY_DiPM__SUPPORT)){ 
    
        // Check DiPM needs to be enabled from Platform Policy
        if(AhciPlatformPolicy->DipmEnable) {
            // Check DiPM is already enabled via Identify Data Word.
            if (!(SataDevInterface->IdentifyData.Reserved_76_79[3] & IDENTIFY_DiPM_ENABLED)) {
                // Enable DiPM and Issue Set Feature command.
                CommandStructure.Features = DiPM_ENABLE; 
                ExecuteNonDataCommand (SataDevInterface, CommandStructure);
            } 
        } else {
            if (SataDevInterface->IdentifyData.Reserved_76_79[3] & IDENTIFY_DiPM_ENABLED) {
            
                // Disable DiPM and Issue Set Feature command only if it is enabled already.
                CommandStructure.Features = DiPM_DISABLE; 
                ExecuteNonDataCommand (SataDevInterface, CommandStructure);
            }
        }     
    }
    return;
}



//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   InitializeDeviceSleep
//
// Description: Initialize Device Sleep in the device and controller
//
// Input:           
//              IN SATA_DEVICE_INTERFACE   *SataDevInterface 
//
// Output:      
//    VOID
//
//
// Notes:
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END> 

VOID
InitializeDeviceSleep (
    IN SATA_DEVICE_INTERFACE    *SataDevInterface
)
{

    AHCI_BUS_PROTOCOL       *AhciBusInterface = SataDevInterface->AhciBusInterface; 
    UINT32                  AhciBaseAddr = (UINT32)(AhciBusInterface->AhciBaseAddress);
    UINT8                   PortNumber = SataDevInterface->PortNumber;
    COMMAND_STRUCTURE       CommandStructure;
    EFI_STATUS              Status;
    UINT8                   DevSleep_Exit_TimeOut = DEVSLEEP_EXIT_TIMEOUT;        
    UINT8                   Minimum_DevSleep_Assertion_Time = MINIMUM_DEVSLP_ASSERTION_TIME;        
    UINT8                   DITO_Multiplier = 0xF;     
    UINT8                   *Buffer = NULL;
    UINT32                  PxDevSlp;
    UINT8                   SectorCount = 1;

    // If Aggressive DelSlp is supported then DevSlp also supported. Also check if the port supports DevSlp or not           
    if ((HBA_REG32(AhciBaseAddr, HBA_CAP2) & HBA_CAP2_SADM)  &&   
            (HBA_PORT_REG32(AhciBaseAddr, PortNumber, HBA_PORTS_PxDEVSLP) & HBA_PORTS_PxDEVSLP_DSP)) { 

        //Clear ADSE
        HBA_PORT_REG32_AND (AhciBaseAddr, PortNumber, HBA_PORTS_PxDEVSLP, ~(HBA_PORTS_PxDEVSLP_ADSE)); 

        // Check Word 78 Bit8 and Word 77 Bit7 of Identify Data.
        if ((SataDevInterface->IdentifyData.Reserved_76_79[2] & IDENTIFY_DEVSLEEP_SUPPORT) && 
                (SataDevInterface->IdentifyData.Reserved_76_79[1] & IDENTIFY_DEVSLP_TO_REDUCED_PWRSTATE_CAPABLE)) {
            
            if(AhciPlatformPolicy->DeviceSleepEnable) {

                // DevSlp not enabled in device. Issue Set Feature command. 
                if (!(SataDevInterface->IdentifyData.Reserved_76_79[3] & IDENTIFY_DEVSLEEP_ENABLED)) {
                
                    ZeroMemory(&CommandStructure, sizeof(COMMAND_STRUCTURE)); 
                    CommandStructure.Command        = SET_FEATURE_COMMAND;
                    CommandStructure.SectorCount    = DEVSLEEP_SUB_COMMAND; 
                    CommandStructure.Features       = DEVSLEEP_ENABLE; 
                    ExecuteNonDataCommand (SataDevInterface, CommandStructure);
                } 
            
                // Allocate Memory for Identify Device Data
                pBS->AllocatePool(EfiBootServicesData, ATA_SECTOR_BYTES, (VOID**)&Buffer);
                ZeroMemory(Buffer, ATA_SECTOR_BYTES); 
    
                // Get Identify Device Data Log (log 30h Page 8)
                ZeroMemory(&CommandStructure, sizeof(COMMAND_STRUCTURE)); 
                CommandStructure.Command        = READ_LOG_EXT;
                CommandStructure.SectorCount    = SectorCount;
                CommandStructure.LBAMid         = SERIAL_ATA_SETTINGS_PAGE;
                CommandStructure.LBALow         = IDENTIFY_DEVICE_DATA_LOG;
                CommandStructure.ByteCount      = SectorCount * ATA_SECTOR_BYTES;;
                CommandStructure.Buffer         = Buffer;
    
                Status = ExecutePioDataCommand (SataDevInterface, &CommandStructure, FALSE);
                if (!EFI_ERROR(Status)){

                    // Update the Time out values
                    ///BYTE 30h..37h DEVSLP Timing Variables (Qword) of Identify Device Data log (log 30h page 08h) 
                            ///63 Valid 
                            ///62:16 Reserved 
                            ///15:8 DevSleep Exit Timeout, in ms (DETO) 
                            ///5:7 Reserved 
                            ///4:0 Minimum DEVSLP Assertion Time, in ms (MDAT) 
                            
                    DevSleep_Exit_TimeOut = Buffer[DEVSLP_TIMING_VARIABLES_OFFSET + 1] ?  Buffer[DEVSLP_TIMING_VARIABLES_OFFSET + 1] : DEVSLEEP_EXIT_TIMEOUT;
                    Minimum_DevSleep_Assertion_Time = (Buffer[DEVSLP_TIMING_VARIABLES_OFFSET] & 0x1F) ? (Buffer[DEVSLP_TIMING_VARIABLES_OFFSET] & 0x1F) : MINIMUM_DEVSLP_ASSERTION_TIME;
                }

                // Program the Timeouts and Multiplier value in PxDEVSLP Registers
                PxDevSlp = HBA_PORT_REG32 (AhciBaseAddr, PortNumber, HBA_PORTS_PxDEVSLP);
                PxDevSlp &= ~(HBA_PORTS_PxDEVSLP_DETO_MASK | HBA_PORTS_PxDEVSLP_DMDAT_MASK | HBA_PORTS_PxDEVSLP_DM_MASK);
                PxDevSlp |= ((DevSleep_Exit_TimeOut << 2) +  (Minimum_DevSleep_Assertion_Time << 10) + (DITO_Multiplier << 25));
                HBA_PORT_REG32_OR (AhciBaseAddr, PortNumber, HBA_PORTS_PxDEVSLP, PxDevSlp);
    
                // Enable PxDEVSLP.ADSE
                HBA_PORT_REG32_OR (AhciBaseAddr, PortNumber, HBA_PORTS_PxDEVSLP, HBA_PORTS_PxDEVSLP_ADSE);
                pBS->FreePool(Buffer);
            } else {
                if (SataDevInterface->IdentifyData.Reserved_76_79[3] & IDENTIFY_DEVSLEEP_ENABLED) {

                    // Disable Device Sleep and Issue Set Feature command only if it is enabled already.
                    ZeroMemory(&CommandStructure, sizeof(COMMAND_STRUCTURE)); 
                    CommandStructure.Command        = SET_FEATURE_COMMAND;
                    CommandStructure.SectorCount    = DEVSLEEP_SUB_COMMAND; 
                    CommandStructure.Features       = DEVSLEEP_DISABLE; 
                    ExecuteNonDataCommand (SataDevInterface, CommandStructure);
                }
            }
        }
    }

    return;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   GetSataDevInterface
//
// Description: 
//
// Input:           
//  IN AHCI_BUS_PROTOCOL                   *AhciBusInterface, 
//  IN UINT8                               Port, 
//  IN UINT8                               PMPort, 
//
// Output:      
//      SATA_DEVICE_INTERFACE*
//
// Modified:
//
// Referrals: 
//
// Notes:
//  1. Return the Pointer to the SATA_DEVICE_INTERFACE for the given
//     Port and PM Port
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END> 
SATA_DEVICE_INTERFACE *
GetSataDevInterface(
    IN AHCI_BUS_PROTOCOL                   *AhciBusInterface, 
    IN UINT8                               Port,
    IN UINT8                               PMPort
)
{
    
    DLINK                   *dlink = AhciBusInterface->SataDeviceList.pHead; 
    SATA_DEVICE_INTERFACE   *SataDevInterface = NULL;

    if (!dlink) return NULL;
    do {
        SataDevInterface = OUTTER(dlink, SataDeviceLink, SATA_DEVICE_INTERFACE);
        if (SataDevInterface->PortNumber == Port && 
                SataDevInterface->PMPortNumber == PMPort ) break;
        dlink = dlink-> pNext;
        SataDevInterface = NULL;
    }while (dlink);    

    return SataDevInterface;

}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   WaitForMemSet
//
// Description: Wait for memory to be set to the test value.
//
// Input:       MemTestAddr      - The memory address to test
//              MaskValue        - The mask value of memory
//              TestValue        - The test value of memory
//              WaitTimeInMs     - The time out value for wait memory set
//
// Output:      EFI_SUCCESS      - HBA reset successfully.
//              EFI_DEVICE_ERROR - HBA failed to complete hardware reset.
//
// Modified:
//
// Referrals: 
//
// Notes:
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END> 
EFI_STATUS 
WaitForMemSet (
    IN UINT32 BaseAddr,
    IN UINT8  Port,
    IN UINT8  Register,
    IN UINT32 AndMask,
    IN UINT32 TestValue,
    IN UINT32 WaitTimeInMs
)
{
    UINT8  Delay;
    while(WaitTimeInMs!=0){ 
        for ( Delay = 10; Delay > 0; Delay--) {

            if(((HBA_PORT_REG32(BaseAddr, Port, Register)) & AndMask) == TestValue){
                return EFI_SUCCESS;
            }

            pBS->Stall (100);  // 100 usec * 10 = 1Msec
        }
        WaitTimeInMs--;
   }
   return EFI_DEVICE_ERROR;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   WaitForMemClear
//
// Description: Wait for memory to be set to the test value.
//
// Input:       MemTestAddr      - The memory address to test
//              MaskValue        - The mask value of memory
//              WaitTimeInMs     - The time out value for wait memory set
//
// Output:      EFI_SUCCESS      - HBA reset successfully.
//              EFI_DEVICE_ERROR - HBA failed to complete hardware reset.
//
// Modified:
//      
//
// Referrals: 
//
// Notes:
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END> 
EFI_STATUS 
WaitForMemClear (
    IN UINT32 BaseAddr,
    IN UINT8  Port,
    IN UINT8  Register,
    IN UINT32 AndMask,
    IN UINT32 WaitTimeInMs
)
{
    UINT8  Delay;
    while(WaitTimeInMs!=0){ 
        for ( Delay = 10; Delay > 0; Delay--) {

            if(!((HBA_PORT_REG32(BaseAddr, Port, Register)) & AndMask)){
                return EFI_SUCCESS;
            }

            pBS->Stall (100);  // 100 usec * 10 = 1Msec
        }
        WaitTimeInMs--;
   }
   return EFI_DEVICE_ERROR;
}

//**********************************************************************
//<AMI_PHDR_START>
//
// Procedure:   ReturnMSBset
//
// Description: Returns the MOST significant Bit set.
//
// Input:
//  IN UINT32       Data
//
// Output:
//      UINT8
//
// Modified:
//      
// Referrals: 
//
// Notes:
//
//
//<AMI_PHDR_END>
//**********************************************************************
UINT8
ReturnMSBset(
 IN UINT32              Data
 )
{
    UINT8       Index;
    UINT8       Value = 0xFF;

    for (Index = 0; Index < 32; Index++) {
        if ( Data & 1) { 
            Value = Index;
        }
            Data >>= 1;
    }

    return Value;
}

//**********************************************************************
//<AMI_PHDR_START>
//
// Procedure:   InitSataBlockIO
//
// Description:	Initializes SATA Block IO interface
//
// Input:
//  IN SATA_DEVICE_INTERFACE            *SataDevInterface
//
// Output:
//  EFI_STATUS
//
// Modified:
//      
// Referrals: AllocatePool, OpenProtocol, DetectAtapiMedia, AtapiInquiryData
//
// Notes:
//  Here is the control flow of this function:
//  1. Initialize EFI_BLOCK_IO_PROTOCOL Protocol.
//  2. In case of Removable devices, detect Media presence.
//
//<AMI_PHDR_END>
//**********************************************************************
EFI_STATUS
InitSataBlockIO (
    IN SATA_DEVICE_INTERFACE            *SataDevInterface
 )
{
    EFI_STATUS                  Status;
    EFI_BLOCK_IO_PROTOCOL       *BlkIo;
    SATA_BLOCK_IO               *SataBlkIo;
    EFI_BLOCK_IO_MEDIA          *BlkMedia;
    ATAPI_DEVICE                *AtapiDevice;
    UINT8                       *Data, *InquiryData;
    UINT16                      InquiryDataSize;
    UINT16                      OddType=0;
    UINT8                       OddLoadingType=0xFF;
    UINT32                      SectorSize = ATA_SECTOR_BYTES;

    Status = pBS->AllocatePool (EfiBootServicesData,
                sizeof(SATA_BLOCK_IO),
                (VOID**)&SataBlkIo);
    if (EFI_ERROR(Status)) return Status;

    BlkMedia = MallocZ(sizeof(EFI_BLOCK_IO_MEDIA));
    if (!BlkMedia) {
        pBS->FreePool (SataBlkIo);
        return EFI_OUT_OF_RESOURCES;
    }

    //
    // Initialize the IdeBlkIo pointer in IDE_BUS_PROTOCOL (IdeBusInterface)
    //
    SataDevInterface->SataBlkIo = SataBlkIo;

    //
    // Initialize the fields in IdeBlkIo (SATA_BLOCK_IO)
    //
    SataBlkIo->SataDevInterface = SataDevInterface;

    if (SataDevInterface->DeviceType == ATA){
        // ATA
        BlkIo = &(SataBlkIo->BlkIo);

#if defined CORE_COMBINED_VERSION && CORE_COMBINED_VERSION > 0x4028a
        if(pST->Hdr.Revision >= 0x0002001F) {
            BlkIo->Revision    = EFI_BLOCK_IO_PROTOCOL_REVISION3;
        } else {
            BlkIo->Revision    = BLKIO_REVISION;
        }
#else 
        BlkIo->Revision    = BLKIO_REVISION;
#endif
        BlkIo->Media = BlkMedia;
        BlkIo->Reset = SataReset;
        BlkIo->ReadBlocks = SataBlkRead;
        BlkIo->WriteBlocks = SataBlkWrite;
        BlkIo->FlushBlocks = SataBlkFlush;

        BlkMedia->MediaId = 0;
        BlkMedia->RemovableMedia = (SataDevInterface->IdentifyData.General_Config_0 & 0x80) == 0x80 ? TRUE : FALSE;

        BlkMedia->MediaPresent = TRUE;
        BlkMedia->LogicalPartition = FALSE;
        BlkMedia->ReadOnly = FALSE;
        BlkMedia->WriteCaching = FALSE;

        if((SataDevInterface->IdentifyData.Reserved_104_126[2] & BIT14) && // WORD 106 valid? - BIT 14 - 1
           (!(SataDevInterface->IdentifyData.Reserved_104_126[2] & BIT15)) && // WORD 106 valid? - BIT 15 - 0
           (SataDevInterface->IdentifyData.Reserved_104_126[2] & BIT12)) { // WORD 106 bit 12 - Sectorsize > 256 words
            // The sector size is in words 117-118.
            SectorSize = (UINT32)(SataDevInterface->IdentifyData.Reserved_104_126[13] + \
                                  (SataDevInterface->IdentifyData.Reserved_104_126[14] << 16)) * 2;
        }

        BlkMedia->BlockSize = SectorSize;
        BlkMedia->IoAlign = 4;

        if (SataDevInterface->IdentifyData.Command_Set_Supported_83 & 0x400) {
            BlkMedia->LastBlock = SataDevInterface->IdentifyData.LBA_48 - 1;
        }
        else {
            BlkMedia->LastBlock = SataDevInterface->IdentifyData.Addressable_Sector_60 - 1;
        }

#if defined CORE_COMBINED_VERSION && CORE_COMBINED_VERSION > 0x4028a
        if(pST->Hdr.Revision >= 0x0002001F) {

            BlkMedia->OptimalTransferLengthGranularity=BlkMedia->BlockSize;
            //
            // bit 14 of word 106 is set to one and bit 15 of word 106 is cleared to zero, 
            // then the contents of word 106 contain valid information . 
            // Otherwise, information is not valid in this word.
            //
            if ( (SataDevInterface->IdentifyData.Reserved_104_126[2] & 0xC000) == 0x4000 ) {
                //
                // If bit 13 of word 106 is set to one, then the device has more than one 
                // logical sector per physical sector and bits (3:0) of word 106 are valid
                //
                if ( SataDevInterface->IdentifyData.Reserved_104_126[2] & 0x2000 ) {
    
                    BlkMedia->LogicalBlocksPerPhysicalBlock = 1 << 
                                    (SataDevInterface->IdentifyData.Reserved_104_126[2] & 0xF);
    
                    //
                    // Bits 13:0 of word 209 indicate the Logical sector offset within the first physical 
                    // sector where the first logical sector is placed
                    //
                    BlkMedia->LowestAlignedLba =SataDevInterface->IdentifyData.Reserved_206_254[3] & 0x3FFF;
    
                } else {
                    //
                    // Default set the 1 logical blocks per PhysicalBlock
                    //
                    BlkMedia->LogicalBlocksPerPhysicalBlock=1;
    
                    //
                    // Default value set to 0 for Lowest Aligned LBA
                    //
                    BlkMedia->LowestAlignedLba=0;
                }
            } else {
                    //
                    // Default set the 1 logical blocks per PhysicalBlock
                    //
                    BlkMedia->LogicalBlocksPerPhysicalBlock=1;
                    //
                    // Default value set to 0 for Lowest Aligned LBA
                    //
                    BlkMedia->LowestAlignedLba=0;
            }
        }
#endif

    } else {

        //
        // If it is an ATAPI device, check whether it is a CDROM or not. 
        // Currently only CDROM/Direct access Devices are supported.
        //
        if ((SataDevInterface->IdentifyData.General_Config_0 & 0x1f00) == (CDROM_DEVICE << 8) ||
            (SataDevInterface->IdentifyData.General_Config_0 & 0x1f00) == (DIRECT_ACCESS_DEVICE << 8) ||
            (SataDevInterface->IdentifyData.General_Config_0 & 0x1f00) == (OPTICAL_MEMORY_DEVICE << 8)){

            AtapiDevice = MallocZ(sizeof (ATAPI_DEVICE));

            if (!AtapiDevice)   return EFI_OUT_OF_RESOURCES;

            SataDevInterface->AtapiDevice = AtapiDevice;

            Status = pBS->AllocatePool (EfiBootServicesData,
                    16,
                    (VOID**)&Data
                    );

            if (EFI_ERROR(Status))  return Status;

            AtapiDevice->PacketBuffer = Data;
            AtapiDevice->DeviceType = (SataDevInterface->IdentifyData.General_Config_0 & 0x1f00) >> 8; 
            AtapiDevice->PacketSize = (SataDevInterface->IdentifyData.General_Config_0 & 3) == 1 ? 16 : 12; 

            BlkIo = &(SataBlkIo->BlkIo);
#if defined CORE_COMBINED_VERSION && CORE_COMBINED_VERSION > 0x4028a
            if(pST->Hdr.Revision >= 0x0002001F) {
                BlkIo->Revision    = EFI_BLOCK_IO_PROTOCOL_REVISION3;
            } else {
                BlkIo->Revision    = BLKIO_REVISION;
            }
#else 
            BlkIo->Revision    = BLKIO_REVISION;
#endif
            BlkIo->Media = BlkMedia;
            BlkIo->Reset = SataReset;
            BlkIo->ReadBlocks = SataAtapiBlkRead;
            BlkIo->WriteBlocks = SataAtapiBlkWrite;
            BlkIo->FlushBlocks = SataBlkFlush;
            BlkMedia->BlockSize = CDROM_BLOCK_SIZE;

            //
            // Update Inquiry Data
            //
            Status = pBS->AllocatePool (EfiBootServicesData,
                        INQUIRY_DATA_LENGTH,
                        (VOID**)&InquiryData);
            if (EFI_ERROR(Status)) 	return Status;
            InquiryDataSize = INQUIRY_DATA_LENGTH;
            SataAtapiInquiryData(SataDevInterface, InquiryData, &InquiryDataSize);
            AtapiDevice->InquiryData = InquiryData;
            AtapiDevice->InquiryDataSize = InquiryDataSize;

            //
            // Get the ATAPI drive type information and save it ATAPI_DEVICE
            //
            Status=SataGetOddType(SataDevInterface, &OddType);
            if(!EFI_ERROR(Status)) {
                AtapiDevice->OddType=GetEnumOddType(OddType);
            }  

            //
            // Get the ATAPI drive Loading information and save it ATAPI_DEVICE
            //
            Status=SataGetOddLoadingType(SataDevInterface, &OddLoadingType);

            if ( !EFI_ERROR( Status )) {
                AtapiDevice->OddLoadingType = (ODD_LOADING_TYPE)OddLoadingType;
            } else {
                AtapiDevice->OddLoadingType = (ODD_LOADING_TYPE)0xFF;
            }

            BlkMedia->RemovableMedia = (SataDevInterface->IdentifyData.General_Config_0 & 0x80) == 0x80 ? TRUE : FALSE;
            BlkMedia->LogicalPartition = FALSE;
            BlkMedia->WriteCaching = FALSE;
            BlkMedia->IoAlign = 4;
#if defined CORE_COMBINED_VERSION && CORE_COMBINED_VERSION > 0x4028a
            if(pST->Hdr.Revision >= 0x0002001F) {
                //
                // For Atapi Devices, Default set the 1 for logical blocks per PhysicalBlock
                //
                BlkMedia->LogicalBlocksPerPhysicalBlock=1;
    
                //
                // For Atapi Devices, Default value set to 0 for Lowest Aligned LBA
                //
                BlkMedia->LowestAlignedLba=0;
    
                BlkMedia->OptimalTransferLengthGranularity=BlkMedia->BlockSize;
            }
#endif
        }
    }

	return EFI_SUCCESS;

}

//<AMI_PHDR_START>
//---------------------------------------------------------------------------
//
// Procedure:   GetEnumOddType
//
// Description: Get the Enum value for ODD type found on profile
//
// Input:
//
//      UINT16      Oddtype
// Output:
//      ODD_TYPE    EnumValue
//
// Modified:
//      
// Referrals: 
//
// Notes:
//
//---------------------------------------------------------------------------
//<AMI_PHDR_END>
ODD_TYPE GetEnumOddType(
    UINT16 OddType
)
{

    switch(OddType) {
        case 1:
        case 3:
        case 4:
        case 5:
                return Obsolete;

        case 2:
                return Removabledisk;

        case 8:
                return CDROM;

        case 9:
                return CDR;

        case 0xa:
                return CDRW;

        case 0x10:
                return DVDROM;

        case 0x11:
                return DVDRSequentialrecording;

        case 0x12:
                return DVDRAM;

        case 0x13:
                return DVDRWRestrictedOverwrite;

        case 0x15:
                return DVDRWSequentialrecording;

        case 0x16:
                return DVDRDualLayerJumprecording;

        case 0x17:
                return DVDRWDualLayer;

        case 0x18:
                return DVDDownloaddiscrecording;

        case 0x1a:
                return DVDRW;

        case 0x1b:
                return DVDR;

        case 0x40:
                return BDROM;

        case 0x41:
                return BDRSequentialRecording;

        case 0x42:
                return BDRRandomRecordingMode;

        case 0x43:
                return BDRE;

        case 0x50:
                return HDDVDROM;

        case 0x51:
                return HDDVDR;

        case 0x52:
                return HDDVDRAM;

        case 0x53:
                return HDDVDRW;

        case 0x58:
                return HDDVDRDualLayer;

        case 0x5a:
                return HDDVDRWDualLayer;

        default:
                return UnknownType;
    }

}

//**********************************************************************
//<AMI_PHDR_START>
//
// Procedure:   InitSataDiskInfo
//
// Description: Initializes SATA DiskInfo Interface
//
// Input:
//  IN SATA_DEVICE_INTERFACE            *SataDevInterface
//
// Output:
//  EFI_STATUS
//
// Modified:
//      
// Referrals: AllocatePool
//
// Notes:
//
//<AMI_PHDR_END>
//**********************************************************************
EFI_STATUS
InitSataDiskInfo (
    IN SATA_DEVICE_INTERFACE            *SataDevInterface
 )
{
    EFI_STATUS              Status;
    SATA_DISK_INFO          *SataDiskInfo;

    Status = pBS->AllocatePool (EfiBootServicesData,
                sizeof(SATA_DISK_INFO),
                (VOID**)&SataDiskInfo);
    if (EFI_ERROR(Status)){
        return Status;
    }

    //
    // Initialize the SataBlkIo pointer in SATA_DEVICE_INTERFACE
    //
    SataDevInterface->SataDiskInfo = SataDiskInfo;

    // Initialize the fields in SataDiskInfo (SATA_DISK_INFO)
    SataDiskInfo->SataDevInterface = SataDevInterface;

    pBS->CopyMem (&(SataDiskInfo->DiskInfo.Interface), &gEfiAhciDiskInfoProtocolGuid, sizeof (EFI_GUID));
    SataDiskInfo->DiskInfo.Inquiry = DiskInfoInquiry;
    SataDiskInfo->DiskInfo.Identify = DiskInfoIdentify;
    SataDiskInfo->DiskInfo.SenseData = DiskInfoSenseData;
    SataDiskInfo->DiskInfo.WhichIde = DiskInfoWhichIDE;
    return EFI_SUCCESS;

}

//**********************************************************************
//<AMI_PHDR_START>
//
// Procedure:   CreateSataDevicePath
//
// Description: Creates a SATA device devicepath and adds it to SataDevInterface
//
// Input:
//  IN EFI_DRIVER_BINDING_PROTOCOL    *This,
//  IN EFI_HANDLE                     Controller,
//  IN SATA_DEVICE_INTERFACE          *SataDevInterface
//  IN OUT EFI_DEVICE_PATH_PROTOCOL       *RemainingDevicePath
//
// Output:
//  EFI_STATUS
//
// Modified:
//      
// Referrals: AllocatePool, OpenProtocol, IdeBusStart
//
// Notes:
//  Here is the control flow of this function:
//  1. If Remaining Devicepath is not NULL, we have already verified that it is a 
//          valid Atapi device path in IdeBusStart. So nothing to do. Just exit.  
//  2. Build a Atapi devicepath and a End devce path. 
//  3. Get the Devicepath for the IDE controller.
//  4. Append Atapi devicepath to  IDE controller devicepath.
//
//<AMI_PHDR_END>
//**********************************************************************
EFI_STATUS
CreateSataDevicePath (
    IN EFI_DRIVER_BINDING_PROTOCOL      *This,
    IN EFI_HANDLE                       Controller,
    IN SATA_DEVICE_INTERFACE            *SataDevInterface,
    IN OUT EFI_DEVICE_PATH_PROTOCOL     *RemainingDevicePath
 )
{

    EFI_STATUS                  Status = EFI_SUCCESS;
    SATA_DEVICE_PATH            NewDevicePath;
    EFI_DEVICE_PATH_PROTOCOL    *TempDevicePath;

    NewDevicePath.Header.Type = MESSAGING_DEVICE_PATH;
    NewDevicePath.Header.SubType = MSG_USB_SATA_DP;
    SET_NODE_LENGTH(&NewDevicePath.Header,SATA_DEVICE_PATH_LENGTH);
    NewDevicePath.PortNumber = SataDevInterface->PortNumber;
    NewDevicePath.MultiplierPortNumber = SataDevInterface->PMPortNumber == 0xFF ? 0xFFFF : SataDevInterface->PMPortNumber;
    NewDevicePath.LogicalUnitNumber = 0;

    //
    // Append the Device Path
    //
    Status = pBS->OpenProtocol( Controller,
                    &gDevicePathProtocolGuid,
                    (VOID **)&TempDevicePath,
                    This->DriverBindingHandle,     
                    Controller,   
                    EFI_OPEN_PROTOCOL_GET_PROTOCOL);

    SataDevInterface->DevicePathProtocol = DPAddNode(TempDevicePath, &NewDevicePath.Header);
    return Status;

}

#if SBIDE_SUPPORT
//**********************************************************************
//<AMI_PHDR_START>
//
// Procedure:   InitMiscConfig
//
// Description: Initialize misc IDE configurations.
//
// Input:
//  IN SATA_DEVICE_INTERFACE    *SataDevInterface
//
// Output:
//  None
//
//<AMI_PHDR_END>
//**********************************************************************
VOID InitMiscConfig (
    IN SATA_DEVICE_INTERFACE    *SataDevInterface
)
{
    IDE_SETUP_PROTOCOL              *gIdeSetupProtocol;
    COMMAND_STRUCTURE               CommandStructure;
    EFI_STATUS                      Status = EFI_SUCCESS;

    Status = pBS->LocateProtocol(&gIdeSetupProtocolguid, NULL, &gIdeSetupProtocol);
    if(EFI_ERROR(Status)){
        return;
    }

    #if ACOUSTIC_MANAGEMENT_SUPPORT
        InitAcousticSupport (SataDevInterface);
    #endif

}
#endif

//**********************************************************************
//<AMI_PHDR_START>
//
// Procedure:   ConfigurePowerUpInStandby
//
// Description: Configure PowerUpInStandby
//
// Input:
//              IN SATA_DEVICE_INTERFACE	*SataDevInterface
//
// Output:
//              EFI_STATUS
//
// Modified:
//      
// Referrals:   ExecuteNonDataCommand
//
// Notes:
// 1. Check if the device support PowerUp In Standby.
// 2. Check the desired state Vs the current state.
// 3. If both are equal nothing to do, exit else program the desired level
//
//<AMI_PHDR_END>
//**********************************************************************
EFI_STATUS
ConfigurePowerUpInStandby (
    IN SATA_DEVICE_INTERFACE    *SataDevInterface
 )
{
    COMMAND_STRUCTURE   CommandStructure;
    EFI_STATUS          Status = EFI_SUCCESS;

    if(AhciPlatformPolicy->PowerUpInStandbySupport) { 
        //
        // Check if the device supports PowerUpInStandby feature
        //
        if  (SataDevInterface->IdentifyData.Command_Set_Supported_83 & 0x20){
            //
            //Check if the desired state is already present or not
            //
            if  (!((SataDevInterface->IdentifyData.Command_Set_Enabled_86 & 0x20) == 
                    (AhciPlatformPolicy->PowerUpInStandbyMode))){

                ZeroMemory(&CommandStructure, sizeof(COMMAND_STRUCTURE)); 
                CommandStructure.Command     = SET_FEATURE_COMMAND;
                CommandStructure.Features    = (AhciPlatformPolicy->PowerUpInStandbyMode) == 0 ? DISABLE_POWERUP_IN_STANDBY : ENABLE_POWERUP_IN_STANDBY;
                Status = ExecuteNonDataCommand (SataDevInterface, CommandStructure);

            }
        }
    }

    return Status;
}

#if ACOUSTIC_MANAGEMENT_SUPPORT
//**********************************************************************
//<AMI_PHDR_START>
//
// Procedure:   InitAcousticSupport
//
// Description: Initialize Acoustic functionality
//
// Input:
//  IN SATA_DEVICE_INTERFACE	*SataDevInterface
//
// Output:
//  EFI_STATUS
//
// Modified:
//      
// Referrals: ExecuteNonDataCommand
//
// Notes:
// 1. Check if the device support Acoustic management.
// 2. Check the desired state Vs the current state.
// 3. If both are equal nothing to do, exit else program the desired level
//
//<AMI_PHDR_END>
//**********************************************************************
EFI_STATUS
InitAcousticSupport (
    IN SATA_DEVICE_INTERFACE    *SataDevInterface
 )
{

    UINT8               Data8;
    COMMAND_STRUCTURE   CommandStructure;
    EFI_STATUS          Status;

    ZeroMemory(&CommandStructure, sizeof(COMMAND_STRUCTURE)); 
    CommandStructure.Command = SET_FEATURE_COMMAND;

    //
    // Check if the device supports Acoustic Management
    //
    if  (SataDevInterface->IdentifyData.Command_Set_Supported_83 & 0x200){

        //
        // Check if Acoustic Level need to be enabled or Disabled
        //
        if (SataDevInterface->AhciBusInterface->Acoustic_Enable & ACOUSTIC_SUPPORT_ENABLE) {
            Data8 = SataDevInterface->AhciBusInterface->Acoustic_Management_Level;

            //
            // Do we need to program the recommended value
            //
            if (Data8 == ACOUSTIC_LEVEL_BYPASS) {

                //
                // Get the rcommended value
                //
                Data8 = (UINT8)(SataDevInterface->IdentifyData.Acoustic_Level_94 >> 8);
            }

            CommandStructure.Features       = ACOUSTIC_MANAGEMENT_ENABLE;
            CommandStructure.SectorCount    = Data8;
            Status = ExecuteNonDataCommand (SataDevInterface, CommandStructure);

        } else {

            //
            // If already disabled, nothing to do
            //
            if  (SataDevInterface->IdentifyData.Command_Set_Enabled_86 & 0x200) {
                CommandStructure.Features       = ACOUSTIC_MANAGEMENT_DISABLE;
                CommandStructure.SectorCount    = 0;
                Status = ExecuteNonDataCommand (SataDevInterface, CommandStructure);
            }
        }
    }
    return EFI_SUCCESS;
}

#endif                          // ACOUSTIC_MANAGEMENT_SUPPORT ends

//**********************************************************************
//<AMI_PHDR_START>
//
// Procedure:   DMACapable
//
// Description: Check if DMA is supported
//
// Input:
//  IN SATA_DEVICE_INTERFACE    *SataDevInterface
//
// Output:
//      TRUE : DMA Capable
//
// Modified:
//      
// Referrals: 
//
// Notes:
//  1. Check the Identify Data to check if device supports DMA
//
//<AMI_PHDR_END>
//**********************************************************************
BOOLEAN
DMACapable(
    IN SATA_DEVICE_INTERFACE    *SataDevInterface
)
{

    if (SataDevInterface->DeviceType == ATAPI){
        //For Atapi Devices check Bit 8 in Word 49 =  DMA	Supported or not
        if((SataDevInterface->IdentifyData.Capabilities_49 & 0x100) == 0) return FALSE;
    }

    if ( (SataDevInterface->UDma != 0xff) ||
        (SataDevInterface->MWDma != 0xff))
        return TRUE;
    else
    return FALSE;

}

//**********************************************************************
//<AMI_PHDR_START>
//
// Procedure:   DiskInfoInquiry
//
// Description: Return ATAPI Inquiry data
//
// Input:
//  IN EFI_DISK_INFO_PROTOCOL   *This,
//  IN OUT VOID                 *InquiryData,
//  IN OUT UINT32               *InquiryDataSize
//
// Output:
//  EFI_STATUS
//
// Modified:
//      
// Referrals: InitSataDiskInfo
//
// Notes:
//  1. Check for Atapi Device. If not exit 
//  2. COpy the Inquiry Data from AtapiDevice->InquiryData to the input pointer.
//
//
//<AMI_PHDR_END>
//**********************************************************************                
EFI_STATUS
DiskInfoInquiry (
    IN EFI_DISK_INFO_PROTOCOL   *This,
    IN OUT VOID                 *InquiryData,
    IN OUT UINT32               *InquiryDataSize
)
{

    SATA_DEVICE_INTERFACE       *SataDevInterface = ((SATA_BLOCK_IO *)This)->SataDevInterface;
    ATAPI_DEVICE                *AtapiDevice = SataDevInterface->AtapiDevice;

    //
    // Check for ATAPI device. If not return EFI_NOT_FOUND
    //
    if (SataDevInterface->DeviceType == ATA){
        return EFI_NOT_FOUND;               // ATA device
    }
    else {
        if (*InquiryDataSize < AtapiDevice->InquiryDataSize) {
            *InquiryDataSize = AtapiDevice->InquiryDataSize;
            return EFI_BUFFER_TOO_SMALL;
        }
        if (AtapiDevice->InquiryData != NULL) {
            pBS->CopyMem (InquiryData, AtapiDevice->InquiryData, AtapiDevice->InquiryDataSize);  
            *InquiryDataSize = AtapiDevice->InquiryDataSize;
            return	EFI_SUCCESS;
        }
        else    return EFI_NOT_FOUND;
    }
}


//**********************************************************************
//<AMI_PHDR_START>
//
// Procedure:   DiskInfoIdentify
//
// Description: Return Identify Data
//
// Input:
//  EFI_DISK_INFO_PROTOCOL          *This,
//  IN OUT VOID                     *IdentifyData,
//  IN OUT UINT32                   *IdentifyDataSize
//
// Output:
//  EFI_STATUS
//
// Modified:
//      
// Referrals: InitSataDiskInfo
//
// Notes:
//  1. Return the Identify command data.
//
//
//<AMI_PHDR_END>
//**********************************************************************
EFI_STATUS
DiskInfoIdentify (
    EFI_DISK_INFO_PROTOCOL          *This,
    IN OUT VOID                     *IdentifyData,
    IN OUT UINT32                   *IdentifyDataSize
 )
{

    SATA_DEVICE_INTERFACE       *SataDevInterface = ((SATA_BLOCK_IO *)This)->SataDevInterface;

    if (*IdentifyDataSize < sizeof (IDENTIFY_DATA)) {
        *IdentifyDataSize = sizeof (IDENTIFY_DATA);
        return EFI_BUFFER_TOO_SMALL;
    }

	//
	// ATA devices identify data might be changed because of the SetFeature command, 
	// So read the data from the device again by sending identify command.
	//
    if(SataDevInterface->DeviceType == ATA){
        GetIdentifyData(SataDevInterface);
    }

    pBS->CopyMem (IdentifyData, &(SataDevInterface->IdentifyData), sizeof (IDENTIFY_DATA)); 
    *IdentifyDataSize =  sizeof (IDENTIFY_DATA);
    return EFI_SUCCESS;

}


//**********************************************************************
//<AMI_PHDR_START>
//
// Procedure:   DiskInfoSenseData
//
// Description: Return InfoSenseData.
//
// Input:
//  EFI_DISK_INFO_PROTOCOL      *This,
//  VOID                        *SenseData,
//  UINT32                      *SenseDataSize,
//  UINT8                       *SenseDataNumber
//
// Output:
//  EFI_STATUS
//
// Modified:
//      
// Referrals: InitSataDiskInfo
//
// Notes:
//  1. Return the Sense data for the Atapi device.
//
//
//<AMI_PHDR_END>
//**********************************************************************
EFI_STATUS
DiskInfoSenseData(
    IN EFI_DISK_INFO_PROTOCOL       *This,
    OUT VOID                        *SenseData,
    OUT UINT32                      *SenseDataSize,
    OUT UINT8                       *SenseDataNumber
 )

{

    return EFI_NOT_FOUND;

}


//**********************************************************************
//<AMI_PHDR_START>
//
// Procedure:   DiskInfoWhichIDE
//
// Description: Returns info about where the device is connected.
//
// Input:
//  IN EFI_DISK_INFO_PROTOCOL   *This,
//  OUT UINT32                  *IdeChannel,
//  OUT UINT32                  *IdeDevice
//
// Output:
//  EFI_STATUS
//
// Modified:
//      
// Referrals: InitSataDiskInfo
//
// Notes:
//  1. Return Port and PMPort
//
//<AMI_PHDR_END>
//**********************************************************************
EFI_STATUS
DiskInfoWhichIDE
(
    IN EFI_DISK_INFO_PROTOCOL   *This,
    OUT UINT32                  *IdeChannel,
    OUT UINT32                  *IdeDevice
 )
{

    SATA_DEVICE_INTERFACE       *SataDevInterface = ((SATA_BLOCK_IO *)This)->SataDevInterface;

    *IdeChannel = SataDevInterface->PortNumber; 
    *IdeDevice = SataDevInterface->PMPortNumber == 0xFF ? 0 : SataDevInterface->PMPortNumber;
    return EFI_SUCCESS;

}

//**********************************************************************
//**********************************************************************
//**                                                                  **
//**        (C)Copyright 1985-2014, American Megatrends, Inc.         **
//**                                                                  **
//**                       All Rights Reserved.                       **
//**                                                                  **
//**         5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093     **
//**                                                                  **
//**                       Phone: (770)-246-8600                      **
//**                                                                  **
//**********************************************************************
//**********************************************************************
