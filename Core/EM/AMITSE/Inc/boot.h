//*****************************************************************//
//*****************************************************************//
//*****************************************************************//
//**                                                             **//
//**         (C)Copyright 2011, American Megatrends, Inc.        **//
//**                                                             **//
//**                     All Rights Reserved.                    **//
//**                                                             **//
//**   5555 Oakbrook Pkwy, Building 200,Norcross, Georgia 30093  **//
//**                                                             **//
//**                     Phone (770)-246-8600                    **//
//**                                                             **//
//*****************************************************************//
//*****************************************************************//
//*****************************************************************//
// $Archive: /Alaska/BIN/Modules/AMITSE2_0/AMITSE/Inc/boot.h $
//
// $Author: Arunsb $
//
// $Revision: 12 $
//
// $Date: 10/18/12 5:31a $
//
//*****************************************************************//
//*****************************************************************//
// Revision History
// ----------------
// $Log: /Alaska/BIN/Modules/AMITSE2_0/AMITSE/Inc/boot.h $
// 
// 12    10/18/12 5:31a Arunsb
// Updated for 2.16.1235 QA submission
// 
// 8     10/10/12 12:23p Arunsb
// Synched the source for v2.16.1232 backup with Aptio
// 
// 10    9/21/12 9:41a Premkumara
//  [TAG]  		EIP 97704
//  [Category]  	Improvement
//  [Description]  	Support BootFFFF variable
//  [Files]  		Boot.h, Boot.c, Special.c
// 
// 9     5/29/12 2:55a Arunsb
// [TAG]  		EIP91109
// [Category]  	Improvement
// [Description]  	Sync the Aptio IV source for AptioV
// [Files]  		boot.h
// 
// 8     11/13/11 12:21p Arunsb
// [TAG]  		EIP70421
// [Category]  	New Feature
// [Description]  	Support for driver order in TSE
// [Files]  		AMITSE.SDL, CommonHelper.c, setup.ini, uefisetup.ini,
// boot.c,
// minisetup.h, bbs.c, special.c, special.h, tseadvanced.c,
// addbootoption.c,
// callback.c, minisetupext.c, minisetupext.h, popupsel.c, popupsel.h,
// TseLitehelper.c, variable.c, Uefi21Wapper.c, AMIVfr.h, boot.h,
// TseElink.h, variable.h, 
// setup.h, Boot.vfr and Setup.uni
// 
// 7     6/20/11 11:38a Rajashakerg
// [TAG]  		EIP59417   
// [Category]  	New Feature
// [Description]  	Spport LOAD_OPTION_HIDDEN option in TSE 	
// [Files]  		boot.h, AMITSE.sdl, CommonHelper.c, bbs.c, boot.c,
// minisetup.h, special.c, callback.c 
// 
// 6     3/15/11 5:11a Rajashakerg
// [TAG]  		EIP51671
// [Category]  	New Feature
// [Description]  	Boot overide menu devices are not disable 
// [Files]  		boot.c, minisetup.h, special.c, minisetupext.c, AMITSE.sdl,
// boot.h, CommonHelper.c
// 
// 5     9/20/10 6:46p Madhans
// [TAG]    	EIP44542
// [Category]	BUILD ISSUE FIX
// [Symptom]	Build issues with TSE label (INT)4.6.2_TSE_2_10_1207_TEST
// when IdeSecurity and FastBoot modules added to the project
// [RootCause] -
// [Solution]	Build issues resolved
// [Files]		CommonHelper.c, Tsecommon.h, Hiilib.h, Boot.h, minisetup.h,
// bbs.c, special.c, Bds.c TseLitehelp
// 
// 4     3/26/10 5:26p Madhans
// EIP 35562: Support To create Boot option in Capital letters.
// 
// 3     2/19/10 12:59p Madhans
// Updated for TSE 2.01. Refer Changelog.log for File change history.
// 
// 4     2/19/10 7:59a Mallikarjunanv
// updated the year in copyright message
// 
// 3     1/09/10 2:29a Mallikarjunanv
// Updated TSE2.01 Release sources with coding standards
// 
// 2     6/24/09 6:33p Madhans
// Coding Standards.
// 
// 1     6/09/09 9:53a Madhans
// TSE 2.00.1201
// 
// 1     6/04/09 7:49p Madhans
// AMI TSE Advanced.
// 
// 1     4/28/09 10:50p Madhans
// Tse 2.0 Code complete Checkin.
// 
// 1     4/28/09 10:24p Madhans
// Tse 2.0 Code complete Checkin.
// 
// 
//*****************************************************************//
//*****************************************************************//
//<AMI_FHDR_START>
//----------------------------------------------------------------------------
//
// Name:		boot.h
//
// Description:	UEFI Boot related header
//
//----------------------------------------------------------------------------
//<AMI_FHDR_END>

#ifndef _BOOT_H_
#define _BOOT_H_

#if !TSE_USE_EDK_LIBRARY
//EIP:39334 - START
#if TSE_CSM_SUPPORT
#include <Protocol/LegacyBios.h>
#else	//If CSM support is not available, then TSE need the following info to build.

#define EFI_LEGACY_BIOS_PROTOCOL_GUID            \
  { 0xdb9a1e3d, 0x45cb, 0x4abb, 0x85, 0x3b, 0xe5, 0x38, 0x7f, 0xdb, 0x2e, 0x2d}

GUID_VARIABLE_DECLARATION(gEfiLegacyBiosProtocolGuid,EFI_LEGACY_BIOS_PROTOCOL_GUID);

#ifndef GUID_VARIABLE_DEFINITION
#include <Protocol/DevicePath.h>

typedef struct _EFI_LEGACY_BIOS_PROTOCOL EFI_LEGACY_BIOS_PROTOCOL;

//<AMI_SHDR_START>
//----------------------------------------------------------------------------
// Name:    HDD_INFO
//
// Fields:
//  Status UINT16   Status of IDE device. See Notes for details.
//  Bus     UINT32  PCI bus of IDE controller.
//  Device  UINT32  PCI device of IDE controller.
//  Function            UINT32  PCI function of IDE controller.
//  CommandBaseAddress  UINT16  Command ports base address.
//  ControlBaseAddress  UINT16  Control ports base address.
//  BusMasterAddress    UINT16  Bus master address.
//  IdentifyDrive       ATAPI_IDENTIFY  Data that identifies the drive data.
//
// Notes:
//  The values for the Status field are the following:
//      HDD_PRIMARY              0x01
//      HDD_SECONDARY            0x02
//      HDD_MASTER_ATAPI         0x04
//      HDD_SLAVE_ATAPI          0x08
//      HDD_MASTER_IDE           0x20
//      HDD_SLAVE_IDE            0x40
//      HDD_SATA_PATA            0x80
//  There is one HDD_INFO structure per IDE controller. The IdentifyDrive is
//  one per drive. Index 0 is master and index 1 is slave.
//----------------------------------------------------------------------------
//<AMI_SHDR_END>

typedef struct _ATAPI_IDENTIFY {
  UINT16    Raw[256];
} ATAPI_IDENTIFY;

//*************************************************
// IDE device status values
//*************************************************

#define HDD_PRIMARY              0x01
#define HDD_SECONDARY            0x02
#define HDD_MASTER_ATAPI         0x04
#define HDD_SLAVE_ATAPI          0x08
#define HDD_MASTER_IDE           0x20
#define HDD_SLAVE_IDE            0x40
#define HDD_SATA_PATA            0x80

typedef struct _HDD_INFO {
  UINT16                    Status;
  UINT32                    Bus;
  UINT32                    Device;
  UINT32                    Function;
  UINT16                    CommandBaseAddress;
  UINT16                    ControlBaseAddress;
  UINT16                    BusMasterAddress;
  UINT8                     HddIrq;
  ATAPI_IDENTIFY            IdentifyDrive[2];
} HDD_INFO;


//****************************************************
// BBS related definitions
//****************************************************

//
// BootPriority values
//
#define BBS_DO_NOT_BOOT_FROM        0xFFFC
#define BBS_LOWEST_PRIORITY         0xFFFD
#define BBS_UNPRIORITIZED_ENTRY     0xFFFE
#define BBS_IGNORE_ENTRY            0xFFFF
//
// Following is a description of the above fields.
//
// BBS_DO_NOT_BOOT_FROM -   Removes a device from the boot list but still
//                          allows it to be enumerated as a valid device
//                          under MS-DOS*.
// BBS_LOWEST_PRIORITY -    Forces the device to be the last boot device.
// BBS_UNPRIORITIZED_ENTRY -    Value that is placed in the BBS_TABLE.BootPriority
//                          field before priority has been assigned but that
//                          indicates it is valid entry.  Other values indicate
//                          the priority, with 0x0000 being the highest priority.
// BBS_IGNORE_ENTRY -       When placed in the BBS_TABLE.BootPriority field,
//                          indicates that the entry is to be skipped.
//

//<AMI_SHDR_START>
//----------------------------------------------------------------------------
// Name:        BBS_STATUS_FLAGS
//
// Fields:
//  OldPosition UINT16:4    Prior priority.
//  Reserved1   UINT16:4    Reserved for future use.
//  Enabled     UINT16:1    If 0, ignore this entry.
//  Failed      UINT16:1    0-Not known if boot failure occurred; 1-Boot attempt failed.
//  MediaPresent UINT16:2   State of media present, see notes.
//  Reserved2   UINT16:4    Reserved for future use.
//
//  Notes:
//      MediaPresent field details:
//          00 = No bootable media is present in the device.
//          01 = Unknown if a bootable media present.
//          10 = Media is present and appears bootable.
//          11 = Reserved.
//----------------------------------------------------------------------------
//<AMI_SHDR_END>

typedef struct {
  UINT16                   OldPosition : 4;
  UINT16                   Reserved1   : 4;
  UINT16                   Enabled     : 1;
  UINT16                   Failed      : 1;
  UINT16                   MediaPresent: 2;
  UINT16                   Reserved2   : 4;
} BBS_STATUS_FLAGS;



//****************************************************
// DeviceType values
//****************************************************
#define    BBS_FLOPPY        0x01
#define    BBS_HARDDISK      0x02
#define    BBS_CDROM         0x03
#define    BBS_PCMCIA        0x04
#define    BBS_USB           0x05
#define    BBS_EMBED_NETWORK 0x06
#define    BBS_BEV_DEVICE    0x80
#define    BBS_UNKNOWN       0xff



//<AMI_SHDR_START>
//----------------------------------------------------------------------------
// Name:    BBS_TABLE
//
// Fields:
//  BootPriority    UINT16 The boot priority for this boot device.
//  Bus         UINT32  The PCI bus for this boot device.
//  Device      UINT32  The PCI device for this boot device.
//  Function    UINT32  The PCI function for the boot device.
//  Class       UINT8   The PCI class for this boot device..
//  SubClass    UINT8   The PCI Subclass for this boot device.
//  MfgString   UINT32  Segment:offset address of an ASCIIZ description.
//  DeviceType  UINT16  BBS device type.
//  StatusFlags BBS_STATUS_FLAGS    Status of this boot device.
//  BootHandler UINT32  Segment:Offset address of boot loader for IPL devices.
//  DescString  UINT32  Segment:offset address of an ASCIIZ description string.
//  InitPerReserved         UINT32  Reserved.
//  AdditionalIrq??Handler  UINT32  See notes for details.
//  AssignedDriveNumber     UINT8   The drive number(0x80 -0x8?) assigned by the 16-bit code.
//  IBV1                    UINT32  IBV specific field.
//  IBV2                    UINT32  IBV specific field.
//
//  Notes:
//      The use of AdditionalIrq??Handler fields is IBV dependent. They can be
//      used to flag that an OpROM has hooked the specified IRQ. The OpROM
//      may be BBS compliant as some SCSI BBS-compliant OpROMs also hook IRQ
//      vectors in order to run their BIOS Setup.
//----------------------------------------------------------------------------
//<AMI_SHDR_END>

typedef struct _BBS_TABLE {
  UINT16                BootPriority;
  UINT32                Bus;
  UINT32                Device;
  UINT32                Function;
  UINT8                 Class;
  UINT8                 SubClass;
  UINT16                MfgStringOffset;
  UINT16                MfgStringSegment;
  UINT16                DeviceType;
  BBS_STATUS_FLAGS      StatusFlags;
  UINT16                BootHandlerOffset;
  UINT16                BootHandlerSegment;
  UINT16                DescStringOffset;
  UINT16                DescStringSegment;
  UINT32                InitPerReserved;
  UINT32                AdditionalIrq13Handler;
  UINT32                AdditionalIrq18Handler;
  UINT32                AdditionalIrq19Handler;
  UINT32                AdditionalIrq40Handler;
  UINT8                 AssignedDriveNumber;
  UINT32                AdditionalIrq41Handler;
  UINT32                AdditionalIrq46Handler;
  UINT32                IBV1;
  UINT32                IBV2;
} BBS_TABLE;

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Name:        EFI_LEGACY_BIOS_BOOT
//
// Description: Boots a traditional OS
//
// Input:
//  This            Indicates the EFI_LEGACY_BIOS_PROTOCOL instance.
//  BootOption      The EFI device path from BootXXXX variable.
//  LoadOptionSize  Size of LoadOption.
//  LoadOption      The load option from BootXXXX variable.
//
// Output:
//  EFI_DEVICE_ERROR    Failed to boot from any boot device and
//  memory is uncorrupted.
//
// Notes:   This function normally never returns. It will either boot the OS
//          or reset the system if memory has been "corrupted" by loading a
//          boot sector and passing control to it.
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

typedef
EFI_STATUS
(EFIAPI *EFI_LEGACY_BIOS_BOOT) (
  IN EFI_LEGACY_BIOS_PROTOCOL         *This,
  IN  BBS_BBS_DEVICE_PATH             *BootOption,
  IN  UINT32                          LoadOptionsSize,
  IN  VOID                            *LoadOptions
  );

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Name:        EFI_LEGACY_BIOS_GET_BBS_INFO
//
// Description: Presents BBS information to external agents.
//
// Input:
//  This        Indicates the EFI_LEGACY_BIOS_PROTOCOL instance.
//  HddCount    Number of HDD_INFO structures.
//  HddInfo     Onboard IDE controller information.
//  BbsCount    Number of BBS_TABLE structures.
//  BbsTable    BBS entry.
//
// Output:  EFI_SUCCESS
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

typedef
EFI_STATUS
(EFIAPI *EFI_LEGACY_BIOS_GET_BBS_INFO) (
  IN EFI_LEGACY_BIOS_PROTOCOL         *This,
  OUT  UINT16                         *HddCount,
  OUT  struct _HDD_INFO               **HddInfo,
  OUT  UINT16                         *BbsCount,
  IN OUT  struct _BBS_TABLE           **BbsTable
  );

//<AMI_SHDR_START>
//----------------------------------------------------------------------------
// Name:        EFI_LEGACY_BIOS_PROTOCOL
//
// Description: Abstracts the traditional BIOS from the rest of EFI. The
//              LegacyBoot() member function allows the BDS to support booting
//              a traditional OS. EFI thunks drivers that make EFI bindings for
//              BIOS INT services use all the other member functions.
//----------------------------------------------------------------------------
//<AMI_SHDR_END>

typedef struct _EFI_LEGACY_BIOS_PROTOCOL {
  EFI_LEGACY_BIOS_BOOT            LegacyBoot;
  EFI_LEGACY_BIOS_GET_BBS_INFO    GetBbsInfo;
} EFI_LEGACY_BIOS_PROTOCOL;

#endif	//#ifndef GUID_VARIABLE_DEFINITION
#endif	//#if !TSE_CSM_SUPPORT
#endif
//EIP:39334 - END


#define	MAX_BOOT_OPTIONS	0xFFFF

#ifndef LOAD_OPTION_ACTIVE
#define LOAD_OPTION_ACTIVE  0x00000001
#endif
//EIP:59417 - Checking for LOAD_OPTION_HIDDEN attribute declearaton
#define LOAD_OPTION_HIDDEN  0x00000008

#ifndef LOAD_OPTION_FORCE_RECONNECT
#define LOAD_OPTION_FORCE_RECONNECT 0x00000002
#endif
//EIP-97704 changed macro to global variable
//#define DISABLED_BOOT_OPTION 	0xFFFF
//#define DISABLED_DRIVER_OPTION 	0xFFFF
extern UINT16 DISABLED_BOOT_OPTION;
extern UINT16 DISABLED_DRIVER_OPTION;

#define BOOT_ORDER_OPTION 		0
#define DRIVER_ORDER_OPTION 	1

typedef struct _BOOT_OPTION
{
	UINT32	Active;
	UINT16	PathLength;
	CHAR16	Name[1];
}
BOOT_OPTION;

typedef struct _BBS_ORDER_LIST BBS_ORDER_LIST;

typedef struct _BOOT_DATA
{
	UINT16						Option;
	UINT32						Active;
	CHAR16						*Name;
	EFI_DEVICE_PATH_PROTOCOL	*DevicePath;
	VOID						*LoadOptions;
	UINTN						LoadOptionSize;
    BOOLEAN                     bNewOption;
    UINTN                       LegacyEntryOffset;
    UINT16                      LegacyDevCount;
    BBS_ORDER_LIST              *OrderList;
}
BOOT_DATA;

typedef struct _LANGUAGE_DATA
{
//#if SETUP_SUPPORT_PLATFORM_LANG_VAR
	CHAR8	*LangCode;
	CHAR16	*Unicode;
//#else
//	CHAR8	LangCode[4];
//	CHAR16	Unicode[4];
//#endif
	CHAR16	*LangString;
	UINT16	Token;
}
LANGUAGE_DATA;

//#if SETUP_SUPPORT_ADD_BOOT_OPTION
typedef struct _FS_DATA
{
	CHAR16	*FsId;
    EFI_DEVICE_PATH_PROTOCOL *FsPath;
}
FS_DATA;
//#endif

//exported variables
extern UINTN gBootOptionCount;
extern CHAR16 gBootFileName[];
extern BOOLEAN gShowAllBbsDev,gPopupMenuShowAllBbsDev;
extern BOOLEAN gSetupHideDisableBootOptions,gPopupMenuHideDisableBootOptions;// EIP:51671 extern decleration of the global varibales to use in soruces.
extern BOOLEAN gLoadOptionHidden; //EIP:59417 - extern decleration of the global varibales to use in soruces.
extern CHAR16 gBootFormarSpecifier[];

extern UINT16 *gBBSDisabled;
//#if SETUP_SUPPORT_ADD_BOOT_OPTION
extern UINTN gFsCount;
extern FS_DATA *gFsList;
//#endif

//exported functions
EFI_STATUS BootGetBootOptions( VOID );
EFI_STATUS BootLaunchBootOption(UINT16 u16Option, UINT16 *pOrder, UINTN u16OrderCount);
BOOT_DATA *BootGetBootData( UINT16 Option );
CHAR16 *BootGetOptionName( BOOT_DATA *bootData);

CHAR16 *BootGetBootNowName( UINT16 value, BOOLEAN ShowAllBBSDev, BOOLEAN TseBootNowInBootOrde);

VOID BootGetLanguages( VOID );
//EFI_STATUS BootLaunchBootNow( UINT16 Index );
EFI_STATUS BootLaunchBootNow( UINT16 index, BOOLEAN ShowAllBbsDev );
EFI_STATUS BootLaunchGuid( EFI_GUID *guid );
EFI_STATUS BootLaunchFilename( CHAR16 *fileName );
//#if SETUP_SUPPORT_ADD_BOOT_OPTION
VOID BootAddBootOption( VOID );
VOID BootDelBootOption( UINT16 index );
VOID DiscardAddDelBootOptions(VOID);
VOID SaveAddDelBootOptions(VOID);

//EIP70421 & 70422 Support for driver order starts
extern UINTN gDriverOptionCount;
extern CHAR16 gDriverFormarSpecifier [];
BOOT_DATA *DriverGetDriverData (UINT16);
CHAR16 *DriverGetOptionName (BOOT_DATA *);
VOID DriverDelDriverOption (UINT16);
VOID DriverAddDriverOption ();
VOID DiscardAddDelDriverOptions (VOID);
VOID SaveAddDelDriverOptions (VOID);
//EIP70421 & 70422 Support for driver order ends
//#endif

#endif /* _BOOT_H_ */

//**********************************************************************
//**********************************************************************
//**                                                                  **
//**         (C)Copyright 2011, American Megatrends, Inc.             **
//**                                                                  **
//**                       All Rights Reserved.                       **
//**                                                                  **
//**   5555 Oakbrook Pkwy, Building 200,Norcross, Georgia 30093       **
//**                                                                  **
//**                       Phone: (770)-246-8600                      **
//**                                                                  **
//**********************************************************************
//**********************************************************************
