//**********************************************************************
//**********************************************************************
//**                                                                  **
//**        (C)Copyright 1985-2013, American Megatrends, Inc.         **
//**                                                                  **
//**                       All Rights Reserved.                       **
//**                                                                  **
//**         5555 Oakbrook Pkwy, Suite 200, Norcross, GA 30093        **
//**                                                                  **
//**                       Phone: (770)-246-8600                      **
//**                                                                  **
//**********************************************************************
//**********************************************************************

//**********************************************************************
// $Header: /Alaska/Projects/Intel/Haswell/LynxPoint_SharkBay-DT_Crb_1AQQW/Include/Protocol/PIDEBus.h 3     2/01/15 11:02p Chienhsieh $
//
// $Revision: 3 $
//
// $Date: 2/01/15 11:02p $
//**********************************************************************
// Revision History
// ----------------
// $Log: /Alaska/Projects/Intel/Haswell/LynxPoint_SharkBay-DT_Crb_1AQQW/Include/Protocol/PIDEBus.h $
// 
// 3     2/01/15 11:02p Chienhsieh
// Update v31 for AHCI module labeled 27.
// 
// 31    6/25/14 10:12a Anandakrishnanl
// [TAG]  		EIP170118
// [Category]  	Bug Fix
// [Severity]  	Normal
// [Symptom]  	MDAT can't program correctly in AHCI module
// [RootCause]  	Identify Data Word 76_79  Offset  for DiPM
// Support/Enabled is incorrect for validation
// [Solution]  	Changed separating DiPM and Device Sleep into two routines
// and also modified the tokens to disable both support  by default .
// Corrected Identify data validations.
// [Files]  		  AhciBus.c
//   AhciBus.h
//   AhciSrc.sdl
//   PAhciBus.h
//   PIDEBus.h 
// 
// 2     9/18/13 1:47a Thomaschen
// Update for ACHI module labeled 24.
// 
// 29    6/06/13 4:17a Rameshr
// [TAG]  		EIP106423
// [Category]  	Improvement
// [Description]  	HddPassword Support in UEFI Raid and Legacy Raid. And
// also taken care where there is no Conin Device avilable in the post
// [Files]  		IdeSecurity.cif,IdeSecurity.sdl,IdeSecurity.mak,IdeSecurityB
// dsCall.c,HddPassword.c, Ahcibus.c, Pidebus.h
// 
// 28    11/27/12 3:23a Rameshr
// [TAG]  		EIP106985
// [Category]  	Improvement
// [Description]  	The IDE_SMART_INTERFACE structure matched with the
// SMART_INTERFACE structure
// [Files]  		PIDEBus.h
// 
// 27    8/16/12 3:14a Rajeshms
// [TAG]  		EIP97048
// [Category]  	New Feature
// [Description]  	ATAPI PassThru Support using
// EFI_EXT_SCSI_PASS_THRU_PROTOCOL.
// [Files]  		AhciBus.c, AhciController.c, IdeBus.c, Atapi.c, PIDEBus.h,
// PAhciBus.h, ScsiPassThruAtapi.sdl, ScsiPassThruAtapi.mak,
// ScsiPassThruAtapi.c, ScsiPassThruAtapiSupport.h, ScsiPassThruAtapi.chm,
// ScsiPassThruExt.h
// 
// 26    7/20/12 6:15a Anandakrishnanl
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
// 25    7/02/12 8:17a Jittenkumarp
// [TAG]  		EIP91969 
// [Category]  	Improvement
// [Description]  	Added versioning and signature  support in IDESMART
// driver
// [Files]  		IdeSMART.c, IdeSMART.h, IdeSMART.sdl, PIDEBus.h
// 
// 24    3/20/12 12:10a Anandakrishnanl
// [TAG]  		EIP68496
// [Category]  	Bug Fix
// [Severity]  	Normal
// [Symptom]  	Opal Security Little Endian vs Big Endian
// [RootCause]  	Equate defines are defined in alternative endian 
// [Solution]  	Equate defines changed to reflect correct format
// [Files]  		PIDEBus.h
// 
// 23    12/05/11 6:14p Rajkumarkc
// [TAG]  		EIP77142 
// [Category]  	Improvement
// [Description]	Added the function 'IdeNonDataCommandExp' in the
// 'IDE_BUS_PROTOCOL' and removed the existing function
// 'IdeNonDataCommand' for supporting the upper 24bits of LBA.
// [Files]
//     Ata.c
//     IdeBus.c
//     Idebus.h
//     PIDEBus.h
// 
// 22    8/22/11 2:59a Anandakrishnanl
// [TAG]  		EIP62912
// [Category]  	Improvement
// [Description]  	Opal Security Definitions Should be Moved to PIDEBUS.h
// from StorageSecurityProtocol.h
// StorageSecurityProtocol.h included in OPAL security driver module will
// give build error when disabled without sdl token #if
// OpalSecurity_SUPPORT properly placed in Ahcibus and IdeBus drivers. But
// Bus driver should not depend on any tokens. For this reason need to
// move OPAL_SEC_INIT_PROTOCOL_GUID in Pidebus.h
// [Files]  		IdeBus.c
// Pidebus.h
// OpalSecurity.cif
// OpalSecurity.h
// IdeOpalSec.c
// AhciOpalSec.c
// 
// 21    6/13/11 11:52a Artems
// Removed unreferenced include
// 
// 20    5/19/11 2:42a Anandakrishnanl
// [TAG]  		EIP53565
// [Category]  	New Feature
// [Description]  	UEFI2.3+ Specifications defines Storage Security
// protocol which needs to be implemented.
// [Files]  		AhciBus.c,IdeBus.c,AHCIOpalSec.c,IDEOpalSec.c,OpalSecurity.c
// ,OpalSecurity.chm,OpalSecurity.cif,OpalSecurity.h,OpalSecurity.mak,Opal
// Security.sdl,PIDEBus.h,StorageSecurityProtocol.CIF,StorageSecurityProto
// col.h
// 
// 19    2/21/11 3:50a Rameshr
// [TAG] - EIP53730
// [Category] - Improvement
// [Description] - Add Odd Loading type information into ATAPI_DEVICE
// structure in AHCI mode
// [Files] - Pidebus.h
// 
// 18    2/05/11 6:39p Krishnakumarg
// [TAG] - EIP36485
// [Category] - Action Item
// [Description] - IDESMART module enhancement
// [Files] - IdeSmart.c,IdeSmart.h,PIdeBus.h
// 
// 17    12/23/10 3:48a Lavanyap
// [TAG] - EIP41445
// [Category] - NEW FEATURE
// [Description] - Created SataPioDataOut and AtaPioDataOut protocol
// function that can accept additional input parameters.
// [Files] - AhciBus.h, AhciBus.c, AhciController.c, Ata.c, IdeBus.c,
//           IdeBus.h, IdeBusMaster.c,PAhciBus.h, PIdeBus.h
// 
// 16    9/13/10 1:48a Rameshr
// [TAG]- EIP 43299
// [Category]-IMPROVEMENT
// [Description]- About IdeSecurity module. It use soft smi port 0xb2
// directly.It will need to re-modify on all of AMD project.
// 1) Added the SDL token for Sw SMI port address.
// 2) Used Pciio protocol to get the device location and passed this
// information to SMM driver.
// [Files]- IdeSecurity.c, IdeSmm.c, PideBus.h
// 
// 15    8/25/10 5:41a Rameshr
// New Feature: EIP 37748
// Description: Move all the IDEBus Source driver SDL token into IdeBus
// Bin Driver.
// FilesModified: Ata.c, Atapi.c, idebus.c, IdeBus.h,
// IdebuscomponentName.c, IdeBusmaster.c IdeBusSrc.mak IdebusSrc.sdl
// IdeHpa.c, IdePowerManagement.c
// 
// 14    8/20/10 4:28p Krishnakumarg
// Ide Smart doesn't support the ATA 8 Read Smart Data. EIP#42492
// Corrected datasize for PollPeriod in Selftest funtion
// 
// 13    8/13/10 5:02p Krishnakumarg
// Ide Smart doesn't support the ATA 8 Read Smart Data. EIP#42492
// 
// 12    5/12/10 4:58p Aaronp
// Changed definitions of password flags function and security flags
// function to refelect return values.
// 
// 11    5/05/10 11:39a Aaronp
// 
// 10    5/03/10 11:04a Krishnakumarg
// Request additional generic functionality to be added to the IdeSMART
// component.EIP#31559
// 
// 9     2/24/10 2:04p Felixp
// 
// 8     1/20/10 9:51a Krishnakumarg
// Included previous IDE_SETUP_PROTOCOL structure and definitions to have
// backward compatibility with AHCI drivers.
// 
// 7     1/11/10 12:17p Krishnakumarg
// Added DiPM in IDE_BUS_PROTOCOL - EIP 30041.
// Removed IDE_SETUP_PROTOCOL and Acoustic defintions as this is
// implemented in SBIDE subcomponent.
// 
// 6     9/04/09 5:21p Krishnakumarg
// IDE_SETUP_PROTOCOL definition added for Acoustic management
// implementation EIP:11835
// Acoustic flag definitions added.
// 
// 5     7/08/09 12:52p Felixp
// 
// 4     6/22/09 11:41a Rameshr
// Odd Type information Saved in Atapi Device Structure.
// EIP:21548
// 
// 3     4/28/09 7:13p Rameshr
// HDD password support in RAID mode
// 
// 2     7/03/08 6:02p Anandakrishnanl
//  Added Protocol and Guid Changes for SMART support as a seperate
// Driver.
// 
// 
// 1     28/02/08 7:51p Anandakrishnanl
// Added PIdeBus.h and PAhciBus.h to generic Protocol for HddSecurity
// support.
// 
// 11    14/08/07 2:04p Anandakrishnanl
// Coding standard applied.
// 
// 10    22/06/07 12:51p Anandakrishnanl
// HardDisk Security Support Module Added.
// Need ACPI Module and SB Module and under Core\Include we updated
// Setup.h.
// Also New IdeBus bin module.
// 
// 9     12/19/06 6:16p Srinin
// DISABLE_SATA2_SOFTPREV equate added.
// 
// 8     11/13/06 1:39p Ambikas
// 
// 7     4/26/06 4:03p Robert
// 
// 5     3/13/06 1:46a Felixp
// 
// 4     1/09/06 11:34a Felixp
// IDE_BUS_INIT_PROTOCOL modified.
// 
// 2     12/14/05 3:13p Srinin
// IDE_BUS_INIT_PROTOCOL modified.
// 
// 1     12/01/05 9:38a Felixp
// 
// 4     8/23/05 10:57a Srinin
// 
// 4     8/17/05 3:30p Srinin
// ATA/ATAPI device identification modified.
// 
// 3     3/04/05 10:45a Mandal
// 
// 2     2/01/05 1:03p Srinin
// IDE HotPlug Support added.
// 
// 1     1/28/05 12:45p Felixp
// 
// 7     1/18/05 3:22p Felixp
// PrintDebugMessage renamed to Trace
// 
// 5     1/13/05 4:26p Srinin
// Host Protection Area Support added.
// 
// 4     1/11/05 2:11p Srinin
// IDE Power Management Support added.
// 
// 3     1/10/05 11:32a Srinin
// IDE SMART Support added.
// 
// 2     1/05/05 11:22a Srinin
// Busmaster and Password support added.
// 
// 1     12/10/04 1:01p Srinin
// 
// 
//**********************************************************************

#ifndef _PIDEBus_
#define _PIDEBus_

#ifdef __cplusplus
extern "C" {
#endif

#ifndef GUID_VARIABLE_DEFINITION

#include <Protocol\IdeControllerInit.h>

#define IDE_BUS_DRIVER_BINDING_PROTOCOL_GUID \
		{ 0x8AA67071, 0x8BEC, 0x47AB, 0x83, 0xC8, 0xCD, 0x0E, 0xB7, 0x23, 0xD0, 0x72 }

#define	IDE_BUS_INIT_PROTOCOL_GUID \
		{ 0xE159A956, 0x3299, 0x4EE9, 0x91, 0x76, 0x65, 0x18, 0x1A, 0x4E, 0x5E, 0x9F }

#define	IDE_SECURITY_INTERFACE_GUID \
		{ 0xF4F63529, 0x281E, 0x4040, 0xA3, 0x13, 0xC1, 0xD6, 0x76, 0x63, 0x84, 0xBE }

#define	IDE_SMART_INTERFACE_GUID \
		{ 0xFFBD9AD2, 0xF1DB, 0x4F92, 0xA6, 0x49, 0xEB, 0x9E, 0xED, 0xEA, 0x86, 0xB5 }

#define	IDE_POWER_MGMT_INTERFACE_GUID \
		{ 0x67BC3883, 0x7E79, 0x4BC1, 0xA3, 0x3E, 0x3A, 0xF7, 0xD1, 0x75, 0x89, 0xBA }

#define	IDE_HPA_INTERFACE_GUID\
		{ 0x51AA65FC, 0x82B6, 0x49E6, 0x95, 0xE2, 0xE6, 0x82, 0x7A, 0x8D, 0x7D, 0xB4 }

#define	IDE_SETUP_PROTOCOL_GUID\
		{ 0x5578ae16, 0xf1c9, 0x4e8f, 0xb1, 0x29, 0xba, 0x7, 0xf8, 0xfc, 0xf8, 0x4a }

#define HDD_SECURITY_INIT_PROTOCOL_GUID \
	    { 0xce6f86bb, 0xb800, 0x4c71, 0xb2, 0xd1, 0x38, 0x97, 0xa3, 0xbc, 0x1d, 0xae }

#define HDD_SMART_INIT_PROTOCOL_GUID \
	    { 0x9401bd4f, 0x1a00, 0x4990, 0xab, 0x56, 0xda, 0xf0, 0xe4, 0xe3, 0x48, 0xde }

#define HDD_SECURITY_END_PROTOCOL_GUID \
	    { 0xad77ae29, 0x4c20, 0x4fdd, 0x85, 0x04, 0x81, 0x76, 0x61, 0x9b, 0x67, 0x6a }

#define OPAL_SEC_INIT_PROTOCOL_GUID \
        { 0x59af16b0, 0x661d, 0x4865, 0xa3, 0x81, 0x38, 0xde, 0x68, 0x38, 0x5d, 0x8d }

#define ATA_PASS_THRU_INIT_PROTOCOL_GUID \
	    { 0xc6734411, 0x2dda, 0x4632, 0xa5, 0x92, 0x92, 0x0f, 0x24, 0xd6, 0xed, 0x21 }

#define SCSI_PASS_THRU_ATAPI_INIT_PROTOCOL_GUID \
        { 0x0fc50878, 0x1633, 0x432a, 0xbd, 0xe4, 0x84, 0x13, 0x57, 0xfc, 0x15, 0xe9 }

#define ONBOARD_RAID_CONTROLLER_GUID \
        { 0x5d206dd3, 0x516a, 0x47dc, 0xa1, 0xbc, 0x6d, 0xa2, 0x04, 0xaa, 0xbe, 0x08 }

#define HDD_PASSWORD_VERIFIED_GUID \
        { 0x1fd29be6, 0x70d0, 0x42a4, 0xa6, 0xe7, 0xe5, 0xd1, 0x0e, 0x6a, 0xc3, 0x76 }

#define MASTER_DRIVE		0
#define SLAVE_DRIVE			1
#define PRIMARY_CHANNEL		0
#define SECONDARY_CHANNEL	1


#define		HOB			0x80
#define		SRST		0x04
#define		nIEN		0x02

#define		ABRT		0x04

#define		BSY			0x80
#define		DRDY		0x40
#define		DF			0x20
#define		DRQ			0x08
#define		ERR			0x01
#define		CHK			0x01

//	Get Media Status ERROR register output
#define		WP			0x40
#define		MC			0x20
#define		MCR			0x08
#define		NM			0x02

// IDE Bus Master status Register
#define		BM_INTERRUPT	0x4
#define		BM_ERROR		0x2
#define		BM_ACTIVE		0x1

// IDE Bus Master Command Register
#define		BM_START_STOP		0x1
#define		DMA_MEMORY_WRITE	0x08
#define		DMA_MEMORY_READ		0x00


#define 	SPIN_UP_REQUIRED1				0x37C8
#define 	SPIN_UP_REQUIRED2				0x738c

#define		ATAPI_SIGNATURE					0xEB14
#define		ATAPI_FORMAT_UNIT				0x04
#define		ATAPI_INQUIRY					0x12
#define		ATAPI_MODE_SELECT				0x55
#define		ATAPI_MODE_SENSE				0x5A
#define			READ_WRITE_ERROR			0x01	
#define			CACHING_PAGE				0x08	
#define			REMOVABLE_BLOCK_CAPABILITIES 0x1B	
#define			TIMER_PROTECT_PAGE			0x1C	
#define			RETURN_ALL_PAGES			0x3F	
#define		ATAPI_PREVENT_ALLOW_MEDIA_REMOVAL 0x1E
#define		ATAPI_READ_10					0x28
#define		ATAPI_READ_12					0xA8
#define		ATAPI_READ_CAPACITY				0x25
#define		ATAPI_READ_FORMAT_CAPACITIES	0x23
#define		ATAPI_REQUEST_SENSE				0x03
#define		ATAPI_SEEK						0x2B
#define		ATAPI_START_STOP_UNIT			0x1B
#define			STOP_DISC					0x00
#define			START_DISC					0x01
#define			EJECT_DISC					0x02
#define			LOAD_DISC					0x03
#define		ATAPI_TEST_UNIT_READY			0x00
#define		ATAPI_VERIFY					0x2F
#define		ATAPI_WRITE_10					0x2A
#define		ATAPI_WRITE_12					0xAA
#define		ATAPI_WRITE_AND_VERIFY			0x2E
#define		ATAPI_GET_CONFIGURATION			0x46
#define		    GET_PROFILE_LIST			0x00
#define         FEATURE_DISCRIPTOR          0x02	
#define		    GET_REMOVEABLE_MEDIUM_FEATURE   0x03


#define		MEDIUM_NOT_PRESENT				0x01
#define		BECOMING_READY					0x02
#define		MEDIA_CHANGED					0x03
#define		DEVICE_ERROR					0x04
#define		WRITE_PROTECTED_MEDIA			0x05
#define		POWER_ON_OR_DEVICE_RESET		0x06
#define		ILLEGAL_REQUEST		            0x07


#define		DEVICE_RESET					0x08
#define		PACKET_COMMAND					0xA0
#define			DMA							0x01
#define			OVL							0x02

#define		IDENTIFY_COMMAND 				0xEC
#define		IDENTIFY_PACKET_COMMAND 		0xA1

#define		READ_SECTORS					0x20
#define		READ_SECTORS_EXT				0x24
#define     READ_LOG_EXT_COMMAND            0x2F

#define		READ_MULTIPLE					0xC4
#define		READ_MULTIPLE_EXT				0x29

#define		WRITE_SECTORS					0x30
#define		WRITE_SECTORS_EXT				0x34

#define		WRITE_MULTIPLE					0xC5
#define		WRITE_MULTIPLE_EXT				0x39

#define		READ_DMA						0xC8
#define		READ_DMA_EXT					0x25

#define		WRITE_DMA						0xCA
#define		WRITE_DMA_EXT					0x35

#define		SET_MULTIPLE_MODE				0xC6
#define		GET_MEDIA_STATUS				0xDA

#define		SET_FEATURE_COMMAND				0xEF
#define			SET_TRANSFER_MODE			0x03
#define			ADV_POWER_MANAGEMENT		0x05
#define			ENABLE_POWERUP_IN_STANDBY	 0x06
#define			SET_DEVICE_SPINUP			0x07
#define			DISABLE_MEDIA_STATUS_NOTIFICATION 0x31
#define			ENABLE_MEDIA_STATUS_NOTIFICATION  0x95
#define			ACOUSTIC_MANAGEMENT_ENABLE	0x42
#define			DISABLE_ADV_POWER_MANAGEMENT 0x85
#define			DISABLE_POWERUP_IN_STANDBY	 0x86
#define			ACOUSTIC_MANAGEMENT_DISABLE	0xC2
#define			DISABLE_SATA2_SOFTPREV      0x90


#define		SECURITY_SET_PASSWORD			0xF1
#define		SECURITY_UNLOCK					0xF2
#define		SECURITY_ERASE_PREPARE			0xF3
#define		SECURITY_ERASE_UNIT				0xF4
#define		SECURITY_FREEZE_LOCK			0xF5
#define		SECURITY_DISABLE_PASSWORD		0xF6
#define			SECURITY_BUFFER_LENGTH		512		// Bytes
#define		DEV_CONFIG_FREEZE_LOCK			0xB1
#define	  		DEV_CONFIG_FREEZE_LOCK_FEATURES	0xC1


#define		SMART_COMMAND					0xB0	
#define			SMART_READ_DATA				0xD0
#define         SMART_READ_THRESHOLD        0xD1    // (Obsolete)
#define			SMART_AUTOSAVE				0xD2
#define			SMART_EXECUTE_OFFLINE_IMMEDIATE 0xD4
#define			SMART_READLOG				0xD5
#define			SMART_WRITELOG				0xD6
#define			SMART_ENABLE_CMD			0xD8
#define			SMART_DISABLE_CMD			0xD9
#define			SMART_RETURN_STATUS			0xDA
#define			THRESHOLD_NOT_EXCEEDED		0xC24F
#define			THRESHOLD_EXCEEDED			0x2CF4
#define         SMART_ABORT_SELF_TEST_SUBROUTINE 0x7F
	
//
// Trusted Commands
//
#define     TRUSTED_NON_DATA            0x5B
#define     TRUSTED_RECEIVE             0x5C
#define     TRUSTED_SEND                0x5E

//
// Level 0 Discovery Feature code
//
#define     TPER_FEATURE_CODE       0x0100
#define     LOCKING_FEATURE_CODE    0x0200
#define     OPAL_SSC_FEATURE_CODE   0x0002

#define		PIO_FLOW_CONTROL				0x08			
#define		MWDMA_MODE						0x20			
#define		UDMA_MODE						0x40			

#define		ATA_SECTOR_BYTES				512
#define		MAX_SECTOR_COUNT_PIO			256	
#define		MAX_SECTOR_COUNT_PIO_48BIT		65536
#define		CDROM_BLOCK_SIZE				2048
#define		LS120_BLOCK_SIZE				512

#define		STANDBY_IMMEDIATE				0xE0
#define		IDLE_IMMEDIATE					0xE1
#define		STANDBY_CMD						0xE2
#define		IDLE_CMD						0xE3
#define		CHECK_POWER_MODE				0xE5
#define		SLEEP_CMD						0xE6

#define		READ_NATIVE_MAX_ADDRESS			0xF8
#define		READ_NATIVE_MAX_ADDRESS_EXT		0x27
#define		SET_MAX_ADDRESS					0xF9
#define			SET_MAX_SET_PASSWORD		0x01
#define			SET_MAX_LOCK				0x02
#define			SET_MAX_UNLOCK				0x03
#define			SET_MAX_FREEZE_LOCK			0x04
#define		SET_MAX_ADDRESS_EXT				0x37

#define     READ_LOG_EXT                    0x2F
#define     IDENTIFY_DEVICE_DATA_LOG        0x30
#define     SERIAL_ATA_SETTINGS_PAGE        0x08
#define     DEVSLP_TIMING_VARIABLES_OFFSET  0x30
#define     DEVSLEEP_EXIT_TIMEOUT           20
#define     MINIMUM_DEVSLP_ASSERTION_TIME   10

#define		DIRECT_ACCESS_DEVICE			0
#define		SEQUENTIAL_ACCESS_DEVICE		1
#define		WORM							4
#define		CDROM_DEVICE					5
#define		OPTICAL_MEMORY_DEVICE			7

#if (SBIDE_SUPPORT == 0)

//	Equates used for Acoustic Flags
#define     ACOUSTIC_SUPPORT_DISABLE            0x00
#define     ACOUSTIC_SUPPORT_ENABLE             0x01
#define     ACOUSTIC_LEVEL_BYPASS               0xFF
#define     ACOUSTIC_LEVEL_MAXIMUM_PERFORMANCE  0xFE
#define     ACOUSTIC_LEVEL_QUIET                0x80


///  Equates used for DiPM Support
#define     DiPM_SUB_COMMAND                            0x03  // Count value in SetFeature identification : 03h  Device-initiated interface power state transitions 
#define     DiPM_ENABLE                                 0x10
#define     DiPM_DISABLE                                0x90
#define     IDENTIFY_DiPM_ENABLED                       0x08  // Identify Data Word 79 Bit 3 : Device initiating interface power management Enabled
#define     IDENTIFY_DiPM__SUPPORT                      0x08  // Identify Data Word 78 Bit 3 : Supports Device initiating interface power management
#define     IDENTIFY_DiPM_HIIPM_REQUESTS_CAPABLE        0x200 // Identify Data Word 76 Bit 9 : Receipt of host-initiated interface power management requests

///  Equates used for DevSleep Support
#define     DEVSLEEP_SUB_COMMAND                        0x09  // Count value in SetFeature identification : 09h  Device Sleep 
#define     DEVSLEEP_ENABLE                             0x10
#define     DEVSLEEP_DISABLE                            0x90
#define     IDENTIFY_DEVSLEEP_ENABLED                   0x100 // Identify Data Word 79 Bit 8 : Device Sleep Enabled
#define     IDENTIFY_DEVSLEEP_SUPPORT                   0x100 // Identify Data Word 78 Bit 8 : Supports Device Sleep
#define     IDENTIFY_DEVSLP_TO_REDUCED_PWRSTATE_CAPABLE 0x80  // Identify Data Word 77 Bit 7 : Device Sleep in reduced Power state capable

typedef struct { 
    UINT8           AcousticPwrMgmt;
    UINT8           AcousticLevel;
    UINT8           DiPM;
}IDE_SETUP_PROTOCOL;
#else 
#include "SBIDE.h"
#endif

//	Equates used for SMART command support

// LOG Address Definition
#define     LOG_DIRECTORY                0x00
#define     SUM_SMART_ERROR_LOG          0x01 //Summary SMART ERROR LOG 
#define     COMP_SMART_ERROR_LOG         0x02 //Comprehensive SMART ERROR LOG 
#define     SMART_SELFTEST_LOG           0x06
#define     HOST_VENDOR_SPECIFIC         0x80 //0x80 - 0x9F
#define     DEVICE_VENDOR_SPECIFIC       0xA0 //0xA0 - 0xBF

// AUTOSAVE Enable/Disable option
#define     DISABLE_AUTOSAVE       0x00
#define     ENABLE_AUTOSAVE        0xF1

typedef enum {	
  ATA = 0,
  ATAPI = 1,
  PMPORT = 2
} DEVICE_TYPE;

// Forward reference for pure ANSI compatability
typedef	struct _IDE_SMART_INTERFACE IDE_SMART_INTERFACE;
typedef	struct _IDE_SECURITY_PROTOCOL IDE_SECURITY_PROTOCOL;
typedef	struct _IDE_POWER_MGMT_INTERFACE IDE_POWER_MGMT_INTERFACE;
typedef	struct _IDE_HPA_INTERFACE IDE_HPA_INTERFACE;
typedef	struct _HDD_SECURITY_INIT_PROTOCOL HDD_SECURITY_INIT_PROTOCOL;
typedef struct _OPAL_SECURITY_INIT_PROTOCOL OPAL_SECURITY_INIT_PROTOCOL;
typedef	struct _HDD_SMART_INIT_PROTOCOL HDD_SMART_INIT_PROTOCOL;
typedef	struct _ATA_PASS_THRU_INIT_PROTOCOL ATA_PASS_THRU_INIT_PROTOCOL;
typedef	struct _IDE_BUS_PROTOCOL IDE_BUS_PROTOCOL;
typedef	struct _IDE_BLOCK_IO IDE_BLOCK_IO;

typedef struct _IDE_DISK_INFO{ 
	EFI_DISK_INFO_PROTOCOL				DiskInfo;				// should be the first Entry
	IDE_BUS_PROTOCOL					*IdeBusInterface;
}IDE_DISK_INFO;

typedef struct _IDE_BLOCK_IO{ 
	EFI_BLOCK_IO_PROTOCOL						BlkIo;					// should be the first Entry
	IDE_BUS_PROTOCOL					*IdeBusInterface;
}IDE_BLOCK_IO;

typedef EFI_STATUS (*EFI_IDE_ATA_RAED_WRITE_PIO) (
    IN IDE_BUS_PROTOCOL	        *This,
    IN OUT VOID					*Buffer,
	IN UINTN					ByteCount,
	IN UINT64					LBA,
	IN UINT8					ReadWriteCommand,
	IN BOOLEAN					ReadWrite
);

typedef EFI_STATUS (*EFI_IDE_ATA_PIO_DATA_IN) (
    IN IDE_BUS_PROTOCOL	        *This,
    OUT VOID 					*Buffer,
	IN UINT32					ByteCount,
	IN UINT8					Features,
	IN UINT8					SectorCount,
	IN UINT8					LBALow,
	IN UINT8					LBAMid,
	IN UINT8					LBAHigh,
	IN UINT8					Device,
	IN UINT8					Command,
	IN BOOLEAN					Multiple
);

typedef EFI_STATUS (*EFI_IDE_ATA_PIO_DATA_OUT) (
    IN IDE_BUS_PROTOCOL         *This,
    IN OUT VOID                 *Buffer,
    IN UINTN                    ByteCount,
    IN UINT8                    Features,
    IN UINT32                   SectorCountIn,
    IN UINT8                    LBALow,
    IN UINT8                    LBALowExp,
    IN UINT8                    LBAMid,
    IN UINT8                    LBAMidExp,
    IN UINT8                    LBAHigh,
    IN UINT8                    LBAHighExp,
    IN UINT8                    Device,
    IN UINT8                    Command,
    IN BOOLEAN                  ReadWrite,
    IN BOOLEAN                  Multiple
);

typedef EFI_STATUS (*EFI_IDE_NON_DATA_CMD) (
    IN IDE_BUS_PROTOCOL	        *This,
    IN UINT8					Features,
	IN UINT8					SectorCount,
	IN UINT8					SectorCountExp,
	IN UINT8					LBALow,
	IN UINT8					LBALowExp,
	IN UINT8					LBAMid,
	IN UINT8					LBAMidExp,
	IN UINT8					LBAHigh,
	IN UINT8					LBAHighExp,
	IN UINT8					Device,
	IN UINT8					Command
	
);

typedef EFI_STATUS (*EFI_WAIT_FOR_CMD_COMPLETE) (
    IN IDE_BUS_PROTOCOL				*This
);

typedef UINT16 SECURITY_FLAGS;
// BIT0 : Security Supported
// BIT1 : Security Enabled
// BIT2 : Security Locked
// BIT3 : Security Frozen
// BIT4 : Security Count Expired
// BIT5 : Enhanced Security Erase supported
// BIT6 : Enhanced Security Erase supported
// BIT8 : Security Level 0:High, 1:Maximum

typedef EFI_STATUS (*EFI_IDE_RETURN_SECURITY_STATUS) (
    IN IDE_SECURITY_PROTOCOL	*This,
	SECURITY_FLAGS				*SecurityStatus
);

typedef EFI_STATUS (*EFI_IDE_SECURITY_SET_PASSWORD) (
    IN IDE_SECURITY_PROTOCOL	*This,
	UINT16						Control,
	UINT8						*Buffer,
	UINT16						RevisionCode
);

typedef EFI_STATUS (*EFI_IDE_SECURITY_UNLOCK_PASSWORD) (
    IN IDE_SECURITY_PROTOCOL	*This,
	UINT16						Control,
	UINT8						*Buffer
);


typedef EFI_STATUS (*EFI_IDE_SECURITY_DISABLE_PASSWORD) (
    IN IDE_SECURITY_PROTOCOL	*This,
	UINT16						Control,
	UINT8						*Buffer
);

typedef EFI_STATUS (*EFI_IDE_SECURITY_FREEZE_LOCK) (
    IN IDE_SECURITY_PROTOCOL	*This
);

typedef EFI_STATUS (*EFI_IDE_SECURITY_ERASE_UNIT) (
    IN IDE_SECURITY_PROTOCOL	*This,
	UINT16						Control,
	UINT8						*Buffer
);

typedef UINT32 PASSWORD_FLAGS;
// IdePasswordFlags:
// BIT0  User Password Support
// BIT1  Master Password Support
// BIT2  Display User Password
// BIT3  Display Master Password
// BIT11 OEM Default Master Password
// BIT16 MasterPassword Set Status.
// BIT17 UserPassword Set Status.

typedef EFI_STATUS (*EFI_IDE_RETURN_PASSWORD_FLAGS) (
    IN IDE_SECURITY_PROTOCOL	*This,
	PASSWORD_FLAGS              *IdePasswordFlags
);

typedef EFI_STATUS (*IDE_SMARTRETURNSTATUS) (
	IN 	IDE_SMART_INTERFACE			*This
);

typedef EFI_STATUS (*IDE_SMARTSELFTEST) (
	IN 	IDE_SMART_INTERFACE			*This,
	IN	UINT8						SelfTestType,
	OUT	UINT16						*PollPeriod
);

typedef EFI_STATUS (*IDE_SMARTABORTSELFTEST) (
	IN 	IDE_SMART_INTERFACE			*This
);

typedef EFI_STATUS (*IDE_SENDSMARTCOMMAND) (
    IN IDE_SMART_INTERFACE  *This,
    IN UINT8                SubCommand,
    IN UINT8                AutoSaveEnable, //OPTIONAL
    IN UINT8                SelfTestType    //OPTIONAL
);

typedef EFI_STATUS (*IDE_SMARTREADDATA) (
    IN  IDE_SMART_INTERFACE  *This,
    IN  UINT8                SubCommand,
    OUT VOID                 *Buffer,
    IN  UINT8                LogAddress,   //OPTIONAL    
    IN  UINT8                SectorCount   //OPTIONAL 
);

typedef	EFI_STATUS (*IDE_SMARTWRITEDATA) (
    IN IDE_SMART_INTERFACE  *This,
    IN UINT8                SubCommand,
    IN VOID                 *Buffer,
    IN UINT8                LogAddress,    
    IN UINT8                SectorCount    
);

typedef EFI_STATUS (*IDE_SMARTGETSMARTDATA) (
	IN 	IDE_SMART_INTERFACE			*This,
    OUT UINT8                       **SmartData
);

typedef EFI_STATUS (*IDE_SMARTSELFTESTSTATUS) (
	IN 	IDE_SMART_INTERFACE			*This,
	OUT	UINT8						*TestStatus
);

typedef	EFI_STATUS	(*EFI_IDE_CHECK_POWER_MODE)(
	IN IDE_POWER_MGMT_INTERFACE			*IdePowerMgmtInterface,
	IN OUT UINT8						*PowerMode
);

typedef	EFI_STATUS	(*EFI_IDE_IDLE_MODE)(
	IN IDE_POWER_MGMT_INTERFACE			*IdePowerMgmtInterface,
	IN UINT8							StandbyTimeout
);

typedef	EFI_STATUS	(*EFI_IDE_STANDBY_MODE)(
	IN IDE_POWER_MGMT_INTERFACE			*IdePowerMgmtInterface,
	IN UINT8							StandbyTimeout
);

typedef	EFI_STATUS	(*EFI_IDE_ADVANCE_POWER_MGMT_MODE)(
	IN IDE_POWER_MGMT_INTERFACE			*IdePowerMgmtInterface,
	IN UINT8							AdvPowerMgmtLevel
);

typedef	EFI_STATUS (*EFI_IDE_GET_NATIVE_MAX_ADDRESS)(
	IN 	IDE_HPA_INTERFACE			*This,
	OUT	UINT64						*LBA
);

typedef	EFI_STATUS (*EFI_IDE_SET_MAX_ADDRESS)(
	IN 	IDE_HPA_INTERFACE			*This,
	OUT	UINT64						LBA,
	IN	BOOLEAN						Volatile
);

typedef	EFI_STATUS (*EFI_IDE_HPA_DISABLED_LAST_LBA)(
	IN 	IDE_HPA_INTERFACE			*This,
	OUT	UINT64						*LBA
);

typedef	EFI_STATUS (*EFI_IDE_SET_MAX_PASSWORD)(
	IN 	IDE_HPA_INTERFACE			*This,
	IN	UINT8						*PasswordBuffer
);

typedef	EFI_STATUS (*EFI_IDE_SET_MAX_LOCK)(
	IN 	IDE_HPA_INTERFACE			*This
);

typedef	EFI_STATUS (*EFI_IDE_SET_MAX_UNLOCK)(
	IN 	IDE_HPA_INTERFACE			*This,
	IN	UINT8						*PasswordBuffer
);

typedef	EFI_STATUS (*EFI_IDE_SET_MAX_FREEZE_LOCK)(
	IN 	IDE_HPA_INTERFACE			*This
);

typedef EFI_STATUS (EFIAPI *HDD_SECURITY_INSTALL) (
	IN VOID     *BusInterface,
	IN BOOLEAN  ModeFlag
);

typedef EFI_STATUS (EFIAPI *HDD_SECURITY_UNINSTALL) (
	IN VOID     *BusInterface,
	IN BOOLEAN  ModeFlag
);

typedef EFI_STATUS (EFIAPI *HDD_SMART_INSTALL) (
	IN VOID     *BusInterface,
	IN BOOLEAN  ModeFlag
);

typedef EFI_STATUS (EFIAPI *HDD_SMART_UNINSTALL) (
	IN VOID     *BusInterface,
	IN BOOLEAN  ModeFlag
);

typedef EFI_STATUS (EFIAPI *HDD_SMART_INIT) (
	IN VOID     *BusInterface,
	IN BOOLEAN  ModeFlag
);


#pragma pack(1)

typedef struct {
  CHAR8   *Language;
  CHAR16  *UnicodeString;
} EFI_UNICODE_STRING_TABLE;


typedef struct {
    UINT32  DataLength;
    UINT8   Reserved[2];
    UINT16  CurrentProfile;
} GET_CONFIGURATION_HEADER;

// Based on ATA/ATAPI-6
typedef struct _IDENTIFY_DATA{ 

	UINT16	General_Config_0;
	UINT16	Reserved_1;
	UINT16	Special_Config_2;
	UINT16	Reserved_3;
	UINT16	Reserved_4;
	UINT16	Reserved_5;
	UINT16	Reserved_6;
	UINT16	Reserved_7;
	UINT16	Reserved_8;
	UINT16	Reserved_9;
	UINT8	Serial_Number_10[20];
	UINT16	Reserved_20;
	UINT16	Reserved_21;
	UINT16	Reserved_22;
	UINT8	Firmware_Revision_23[8];
	UINT8	Model_Number_27[40];
	UINT16	Maximum_Sector_Multiple_Command_47;
	UINT16	Trusted_Computing_Support;
	UINT16	Capabilities_49;
	UINT16	Capabilities_50;
	UINT16	PIO_Mode_51;
	UINT16	Reserved_52;
	UINT16	Valid_Bits_53;
	UINT16	Reserved_54_58[5];
	UINT16	Valid_Bits_59;
	UINT32	Addressable_Sector_60;
	UINT16	SingleWord_DMA_62;
	UINT16	MultiWord_DMA_63;
	UINT16	PIO_Mode_64;
	UINT16	Min_Multiword_DMA_timing_65;
	UINT16	Manuf_Multiword_DMA_timing_66;
	UINT16	Min_PIO_Mode_timing_67;
	UINT16	Min_PIO_Mode_timing_68;
	UINT16	Reserved_69_74[6];
	UINT16	Queue_Depth_75;
	UINT16	Reserved_76_79[4];
	UINT16	Major_Revision_80;
	UINT16	Minor_Revision_81;
	UINT16	Command_Set_Supported_82;
	UINT16	Command_Set_Supported_83;
	UINT16	Command_Set_Supported_84;
	UINT16	Command_Set_Enabled_85;
	UINT16	Command_Set_Enabled_86;
	UINT16	Command_Set_Enabled_87;
	UINT16	UDMA_Mode_88;
	UINT16	Time_security_Earse_89;
	UINT16	Time_Esecurity_Earse_90;
	UINT16	Current_Power_Level_91;
	UINT16	Master_Password_Rev_92;
	UINT16	Hard_Reset_Value_93;
	UINT16	Acoustic_Level_94;
	UINT16	Reserved_95_99[5];
	UINT64	LBA_48;
	UINT16	Reserved_104_126[23];
	UINT16	Status_Notification_127;
	UINT16	Security_Status_128;
	UINT16	Reserved_129_159[31];
	UINT16	CFA_Power_Mode_160;
	UINT16	Reserved_161_175[15];
	UINT16	Media_Serial_Number_176_205[30];
	UINT16	Reserved_206_254[49];
	UINT16	Checksum_255;
} IDENTIFY_DATA;

typedef struct { 
	UINT16		BMCommandRegister;
	UINT16		Reserved;
	UINT16		BMStatusRegister;
	UINT16		BMDescriptorTablePointerReg;
} BUS_MASTER_IO;


typedef struct { 
	UINT32		BaseAddress;
	UINT16		ByteCount;
	UINT16		Flag;
} BUS_MASTER_DESCRIPTOR_TABLE;


typedef struct { 
	UINT16		DataReg;
	UINT16		FeatureReg;
	UINT16		ErrorReg;
	UINT16		SectorCountReg;
	UINT16		LBALowReg;
	UINT16		LBAMidReg;
	UINT16		LBAHighReg;
	UINT16		DeviceReg;
	UINT16		CommandReg;
	UINT16		StatusReg;
} COMMAND_BLOCK;

typedef struct{ 
	UINT16		DeviceControlReg;
	UINT16		AlternateStatusReg;
} CONTROL_BLOCK;


typedef struct { 
	UINT8								IdeBusInitData[2][2];
	IDE_BUS_PROTOCOL					*pIdeBusProtocol[2][2];
    EFI_IDE_CONTROLLER_INIT_PROTOCOL    *EfiIdeControllerInterface;
	IDE_CONTROLLER_PROTOCOL				*IdeControllerInterface;
	UINT8								BusMasterSelection;
	UINT8								HPMask;
	EFI_EVENT							HPEvent;
	UINT8								Flags;
	UINT8								Acoustic_Management_Level;
    UINT8                               DiPM;
    UINT16                              PrevPortNum;
    UINT16                              PrevPortMultiplierPortNum;
} IDE_BUS_INIT_PROTOCOL;

typedef struct { 
	COMMAND_BLOCK						CommandBlock;
	CONTROL_BLOCK						ControlBlock;
	BUS_MASTER_IO						BusMasterBlock;
} IO_REGS;


typedef enum {
    Obsolete,
    Removabledisk,
    CDROM,
    CDR,
    CDRW,
    DVDROM,
    DVDRSequentialrecording,
    DVDRAM,
    DVDRWRestrictedOverwrite,
    DVDRWSequentialrecording,
    DVDRDualLayerSequential,
    DVDRDualLayerJumprecording,
    DVDRWDualLayer,
    DVDDownloaddiscrecording,
    DVDRW,
    DVDR,
    BDROM,
    BDRSequentialRecording,
    BDRRandomRecordingMode,
    BDRE,
    HDDVDROM,
    HDDVDR,
    HDDVDRAM,
    HDDVDRW,
    HDDVDRDualLayer,
    HDDVDRWDualLayer,
    UnknownType
} ODD_TYPE;

typedef enum {
    CaddySlotType,
    TrayType,
    PopupType,
    ReservedType,
    EmbeddedChangerWithIndividuallyChangeablediscs,
    EmbeddedChangerUsingCartridgeMmechanism,
    ReservedLoadingType
} ODD_LOADING_TYPE;

typedef struct { 
	UINT8 								*PacketBuffer;
	UINT8								DeviceType;
	UINT8								Lun;
	UINT8								PacketSize;
	UINT16								BlockSize;
	BOOLEAN								ReadOnly;
	UINT8								Atapi_Status;
	UINT8								*InquiryData;							
	UINT32								InquiryDataSize;
    ODD_TYPE                            OddType;							
    ODD_LOADING_TYPE                    OddLoadingType;							
} ATAPI_DEVICE;

typedef struct _IDE_DEVICE_INTERFACE {
	IDENTIFY_DATA						IdentifyData;
	UINT8								Channel;
	UINT8								Device;
	DEVICE_TYPE							DeviceType;
	UINT8								PIOMode;
	UINT8								SWDma;
	UINT8								MWDma;
	UINT8								UDma;
	UINT8								IORdy;
	UINT8								ReadCommand;
	UINT8								WriteCommand;
	IO_REGS								Regs;
    EFI_PCI_IO_PROTOCOL					*PciIO;
	EFI_UNICODE_STRING_TABLE			*UDeviceName;
	ATAPI_DEVICE						*AtapiDevice;
} IDE_DEVICE_INTERFACE;


typedef struct {
	UINT32	Signature;
    UINT8	UserPassword[32];	
    UINT8	MasterPassword[32];
	UINT16	BaseAddress;
	UINT16	DeviceControlReg;
	UINT8	Device;				// Master/Slave
	UINT16	Control;
	UINT16	RevisionCode;
    UINT8   PortNumber;
    UINT8   PMPortNumber;
    UINT8   BusNo;
    UINT8   DeviceNo;
    UINT8   FunctionNo;
    BOOLEAN ModeFlag;   
	DLINK	LinkList;
} HDD_PASSWORD;

typedef struct _IDE_SMART_INTERFACE{ 
    UINT8                               Revision;
    UINT32                              Signature;
	IDE_SMARTSELFTEST					SMARTSelfTest;
	IDE_SMARTSELFTESTSTATUS				SMARTSelfTestStatus;
	IDE_SMARTRETURNSTATUS				SMARTReturnStatus;
    IDE_SENDSMARTCOMMAND                SendSmartCommand;
    IDE_SMARTREADDATA                   SmartReadData;
    IDE_SMARTWRITEDATA                  SmartWriteData;
    IDE_SMARTABORTSELFTEST              SMARTAbortSelfTest;
    IDE_SMARTGETSMARTDATA               SMARTGetSmartData;
}IDE_SMART_INTERFACE;


typedef struct _SMART_INTERFACE{
 
    UINT8                               Revision;
    UINT32                              Signature;
	IDE_SMARTSELFTEST					SMARTSelfTest;
	IDE_SMARTSELFTESTSTATUS				SMARTSelfTestStatus;
	IDE_SMARTRETURNSTATUS				SMARTReturnStatus;
    IDE_SENDSMARTCOMMAND                SendSmartCommand;
    IDE_SMARTREADDATA                   SmartReadData;
    IDE_SMARTWRITEDATA                  SmartWriteData;
    IDE_SMARTABORTSELFTEST              SMARTAbortSelfTest;
    IDE_SMARTGETSMARTDATA               SMARTGetSmartData;
	VOID					            *BusInterface;
	UINT8								ShortPollingTime;
	UINT16								ExtPollingTime;
    BOOLEAN                             ModeFlag;
}SMART_INTERFACE;

typedef struct _IDE_SECURITY_PROTOCOL{ 

	EFI_IDE_RETURN_SECURITY_STATUS			ReturnSecurityStatus;
	EFI_IDE_SECURITY_SET_PASSWORD			SecuritySetPassword;
	EFI_IDE_SECURITY_UNLOCK_PASSWORD		SecurityUnlockPassword;
	EFI_IDE_SECURITY_DISABLE_PASSWORD		SecurityDisablePassword;
	EFI_IDE_SECURITY_FREEZE_LOCK			SecurityFreezeLock;
	EFI_IDE_SECURITY_ERASE_UNIT				SecurityEraseUnit;
    EFI_IDE_RETURN_PASSWORD_FLAGS           ReturnIdePasswordFlags;

}IDE_SECURITY_PROTOCOL;

typedef struct _SECURITY_PROTOCOL{ 

	EFI_IDE_RETURN_SECURITY_STATUS			ReturnSecurityStatus;
	EFI_IDE_SECURITY_SET_PASSWORD			SecuritySetPassword;
	EFI_IDE_SECURITY_UNLOCK_PASSWORD		SecurityUnlockPassword;
	EFI_IDE_SECURITY_DISABLE_PASSWORD		SecurityDisablePassword;
	EFI_IDE_SECURITY_FREEZE_LOCK			SecurityFreezeLock;
	EFI_IDE_SECURITY_ERASE_UNIT				SecurityEraseUnit;
    EFI_IDE_RETURN_PASSWORD_FLAGS           ReturnIdePasswordFlags;
	HDD_PASSWORD							*pHDDPasswordBuffer;
	VOID            						*BusInterface;
    BOOLEAN                                 ModeFlag;

}SECURITY_PROTOCOL;

typedef	struct _IDE_POWER_MGMT_INTERFACE {

	EFI_IDE_CHECK_POWER_MODE				CheckPowerMode;
	EFI_IDE_IDLE_MODE						IdleMode;
	EFI_IDE_STANDBY_MODE					StandbyMode;
	EFI_IDE_ADVANCE_POWER_MGMT_MODE			AdvancePowerMgmtMode;

}IDE_POWER_MGMT_INTERFACE;

typedef	struct _POWER_MGMT_INTERFACE {

	EFI_IDE_CHECK_POWER_MODE				CheckPowerMode;
	EFI_IDE_IDLE_MODE						IdleMode;
	EFI_IDE_STANDBY_MODE					StandbyMode;
	EFI_IDE_ADVANCE_POWER_MGMT_MODE			AdvancePowerMgmtMode;
	IDE_BUS_PROTOCOL						*IdeBusInterface;

}POWER_MGMT_INTERFACE;

typedef	struct	_IDE_HPA_INTERFACE {

	EFI_IDE_GET_NATIVE_MAX_ADDRESS			GetNativeMaxAddress;
	EFI_IDE_SET_MAX_ADDRESS					SetMaxAddress;
	EFI_IDE_HPA_DISABLED_LAST_LBA			HPADisabledLastLBA;
	EFI_IDE_SET_MAX_PASSWORD				SetMaxPassword;
	EFI_IDE_SET_MAX_LOCK					SetMaxLock;
	EFI_IDE_SET_MAX_UNLOCK					SetMaxUnLock;
	EFI_IDE_SET_MAX_FREEZE_LOCK				SetMaxFreezeLock;

}IDE_HPA_INTERFACE;

typedef	struct	_HPA_INTERFACE {

	EFI_IDE_GET_NATIVE_MAX_ADDRESS			GetNativeMaxAddress;
	EFI_IDE_SET_MAX_ADDRESS					SetMaxAddress;
	EFI_IDE_HPA_DISABLED_LAST_LBA			HPADisabledLastLBA;
	EFI_IDE_SET_MAX_PASSWORD				SetMaxPassword;
	EFI_IDE_SET_MAX_LOCK					SetMaxLock;
	EFI_IDE_SET_MAX_UNLOCK					SetMaxUnLock;
	EFI_IDE_SET_MAX_FREEZE_LOCK				SetMaxFreezeLock;
	IDE_BUS_PROTOCOL						*IdeBusInterface;

}HPA_INTERFACE;

typedef struct _PORT_DRIVE_DATA {
   UINT8                DriveNumber;
   UINT8                PortNumber;
} PORT_DRIVE_DATA;

typedef struct _HDD_SECURITY_INIT_PROTOCOL {
	HDD_SECURITY_INSTALL    InstallSecurityInterface;
    HDD_SECURITY_UNINSTALL  StopSecurityModeSupport;
} HDD_SECURITY_INIT_PROTOCOL;

typedef struct _HDD_SMART_INIT_PROTOCOL {
    HDD_SMART_INSTALL       InstallSMARTInterface;
    HDD_SMART_UNINSTALL     UnInstallSMARTInterface;
    HDD_SMART_INIT          InitSMARTSupport;
    BOOLEAN                 SmartDiagonasticFlag;
} HDD_SMART_INIT_PROTOCOL;

typedef EFI_STATUS (EFIAPI *OPAL_SECURITY_INSTALL) (
    IN VOID     *BusInterface,
    IN BOOLEAN  ModeFlag
);

typedef EFI_STATUS (EFIAPI *OPAL_SECURITY_UNINSTALL) (
    IN VOID     *BusInterface,
    IN BOOLEAN  ModeFlag
);

typedef struct _OPAL_SECURITY_INIT_PROTOCOL {
    OPAL_SECURITY_INSTALL    InstallOpalSecurityInterface;
    OPAL_SECURITY_UNINSTALL  UnInstallOpalSecurityInterface;
} OPAL_SECURITY_INIT_PROTOCOL;

typedef EFI_STATUS (EFIAPI *ATA_PASS_THRU_INSTALL) (
    IN VOID     *Controller,
    IN BOOLEAN  ModeFlag
);

typedef EFI_STATUS (EFIAPI *ATA_PASS_THRU_UNINSTALL) (
    IN VOID     *Controller,
    IN BOOLEAN  ModeFlag
);

typedef struct _ATA_PASS_THRU_INIT_PROTOCOL {
	ATA_PASS_THRU_INSTALL    InstallAtaPassThru;
    ATA_PASS_THRU_UNINSTALL  StopAtaPassThruSupport;
} ATA_PASS_THRU_INIT_PROTOCOL;

typedef EFI_STATUS (EFIAPI *GENERAL_ATAPI_COMMAND_DATA)(
    IN IDE_BUS_PROTOCOL *IdeBusInterface,
    UINT8               *PacketBuffer,
    UINT8               *Buffer,
    IN OUT UINT16       *ByteCount );

typedef EFI_STATUS (EFIAPI *SCSI_PASS_THRU_INSTALL) (
    IN VOID     *Controller,
    IN BOOLEAN  ModeFlag
);

typedef EFI_STATUS (EFIAPI *SCSI_PASS_THRU_UNINSTALL) (
    IN VOID     *Controller,
    IN BOOLEAN  ModeFlag
);

typedef struct _SCSI_PASS_THRU_ATAPI_INIT_PROTOCOL {
	SCSI_PASS_THRU_INSTALL    InstallScsiPassThruAtapi;
    SCSI_PASS_THRU_UNINSTALL  StopScsiPassThruAtapiSupport;
} SCSI_PASS_THRU_ATAPI_INIT_PROTOCOL;


typedef struct _IDE_BUS_PROTOCOL{ 
	IDE_BLOCK_IO						*IdeBlkIo;
	IDE_DISK_INFO						*IdeDiskInfo;
	EFI_DEVICE_PATH_PROTOCOL		    *DevicePathProtocol;
    EFI_IDE_CONTROLLER_INIT_PROTOCOL    *EfiIdeControllerInterface;
    EFI_HANDLE                          IdeControllerInterfaceHandle;
	IDE_CONTROLLER_PROTOCOL				*IdeControllerInterface;
	SECURITY_PROTOCOL					*IdeSecurityInterface;
	SMART_INTERFACE						*SMARTInterface;
	POWER_MGMT_INTERFACE				*PowerMgmtInterface;
    HPA_INTERFACE						*HPAInterface;
	IDE_BUS_INIT_PROTOCOL				*IdeBusInitInterface;
    EFI_PCI_IO_PROTOCOL					*PciIO;
	EFI_HANDLE							IdeDeviceHandle;
	IDE_DEVICE_INTERFACE				IdeDevice;
    EFI_UNICODE_STRING_TABLE            *ControllerNameTable;
    UINT8                               AtapiSenseData[256];
    UINT8                               AtapiSenseDataLength;
    EFI_IDE_ATA_RAED_WRITE_PIO          AtaReadWritePio;
    EFI_IDE_ATA_PIO_DATA_IN             AtaPioDataIn;
    EFI_IDE_ATA_PIO_DATA_OUT            AtaPioDataOut;
    EFI_IDE_NON_DATA_CMD                IdeNonDataCommand;
    EFI_WAIT_FOR_CMD_COMPLETE           WaitForCmdCompletion;
    GENERAL_ATAPI_COMMAND_DATA          GeneralAtapiCommandAndData;
} IDE_BUS_PROTOCOL;

typedef struct _IDE_BLK_IO_DEV {
  UINT32                      Signature;
  EFI_HANDLE                  Handle;
	EFI_BLOCK_IO_PROTOCOL				BlkIo;					// should be the first Entry
	IDE_BUS_PROTOCOL					*IdeBusInterface;
	IDE_DISK_INFO						*IdeDiskInfo;
	EFI_DEVICE_PATH_PROTOCOL		    *DevicePathProtocol;
    EFI_IDE_CONTROLLER_INIT_PROTOCOL    *EfiIdeControllerInterface;
    EFI_HANDLE                          IdeControllerInterfaceHandle; 
	IDE_CONTROLLER_PROTOCOL				*IdeControllerInterface;
	SECURITY_PROTOCOL					*IdeSecurityInterface;
	SMART_INTERFACE						*SMARTInterface;
	POWER_MGMT_INTERFACE				*PowerMgmtInterface;
    HPA_INTERFACE						*HPAInterface;
	IDE_BUS_INIT_PROTOCOL				*IdeBusInitInterface;
    EFI_PCI_IO_PROTOCOL					*PciIO;
	EFI_HANDLE							IdeDeviceHandle;
	IDE_DEVICE_INTERFACE				IdeDevice;
    EFI_UNICODE_STRING_TABLE			*ControllerNameTable;
    UINT8                               AtapiSenseData[256];
} IDE_BLK_IO_DEV;

#define _CR(Record, TYPE, Field)  ((TYPE *) ((CHAR8 *) (Record) - (CHAR8 *) &(((TYPE *) 0)->Field)))
#ifndef CR
#define CR(record, TYPE, field, signature) _CR(record, TYPE, field)
#endif

#define EFI_SIGNATURE_16(A, B)        ((A) | (B << 8))
#define EFI_SIGNATURE_32(A, B, C, D)  (EFI_SIGNATURE_16 (A, B) | (EFI_SIGNATURE_16 (C, D) << 16))

#define IDE_BLK_IO_DEV_SIGNATURE  EFI_SIGNATURE_32 ('i', 'b', 'i', 'd')
#define IDE_BLOCK_IO_DEV_FROM_THIS(a)           CR (a, IDE_BLK_IO_DEV, BlkIo, IDE_BLK_IO_DEV_SIGNATURE)



#pragma pack()


/****** DO NOT WRITE BELOW THIS LINE *******/
#endif // #ifndef GUID_VARIABLE_DEFINITION
#ifdef __cplusplus
}
#endif

#endif

//**********************************************************************
//**********************************************************************
//**                                                                  **
//**        (C)Copyright 1985-2013, American Megatrends, Inc.         **
//**                                                                  **
//**                       All Rights Reserved.                       **
//**                                                                  **
//**         5555 Oakbrook Pkwy, Suite 200, Norcross, GA 30093        **
//**                                                                  **
//**                       Phone: (770)-246-8600                      **
//**                                                                  **
//**********************************************************************
//**********************************************************************
