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

//**********************************************************************
// $Header: /Alaska/Projects/Intel/Haswell/LynxPoint_SharkBay-DT_Crb_1AQQW/Core/CORE_DXE/BdsBoard.c 2     10/30/13 6:54a Ireneyang $
//
// $Revision: 2 $
//
// $Date: 10/30/13 6:54a $
//**********************************************************************
// Revision History
// ----------------
// $Log: /Alaska/Projects/Intel/Haswell/LynxPoint_SharkBay-DT_Crb_1AQQW/Core/CORE_DXE/BdsBoard.c $
// 
// 2     10/30/13 6:54a Ireneyang
// - Fix Setup menu erroneously shows multiple instances of 
//   the same bootable device for EIP139412 
// 
// 65    5/20/13 4:37p Artems
// [TAG]  		EIP N/A
// [Category]  	Improvement
// [Description]  	Implement ORPHAN_BOOT_POLICY_KEEP for legacy groups
// [Files]  		BootOptions.h BootOptions.c BdsBoard.c
// 
// 64    5/24/12 3:24p Artems
// [TAG]  		EIP N/A
// [Category]  	Improvement
// [Description]  	Graphics console tokens moved from BdsBoard.c into
// Tokens.c
// [Files]  		BdsBoard.c Tokens.c
// 
// 1     8/25/12 4:39a Wesleychen
// Update to rev.63 for EIP85762.
// 
// 63    4/09/12 5:41p Artems
// Implementation of NON_FW_BOOT_OPTION_HIDE functionality
// 
// 62    11/01/11 1:41p Felixp
// Definition of the BeforeLegacyBootProtocolGuid variable is added.
// 
// 61    10/28/11 2:52p Artems
// Moved function ConnectConsoles to FastBoot module
// 
// 60    3/28/11 3:49p Felixp
// Bug fix: Cloning of BOOT_OPTION_NAME_PREFIX_FUNCTION,
// BOOT_OPTION_NAME_SUFFIX_FUNCTION, or 
// BOOT_OPTION_GET_BBS_ENTRY_DEVICE_TYPE_FUNCTION caused an unknown
// identifier error because 
// "extern" declaration for the cloned function was missing.
// 
// 59    3/09/11 5:47p Artems
// For ConnectPS2ConIn function added #ifdef from PS2Ctl_SUPPORT
// 
// 58    2/25/11 12:30p Artems
// EIP 53767 - Velocity boot time above 5 seconds. Added provision to skip
// USB keyboard initialization
// 
// 57    2/15/11 6:50p Artems
// 
// 56    1/24/11 3:51p Pats
// [TAG] - EIP 18488
// [Category] - Enhancement
// [Severity] - Normal
// [Symptom] - PS2CTL: Need hooks for port swap, Keybaord mouse detect.
// [RootCause] - Support may be needed for kbc controller or SIO with
// different support from AMI KB-5.
// [Solution] - Modified to allow external f AutodetectKbdMousePortsPtr()
// function.
// [Files] - BdsBaord.c, CORE_DXE.C, and in PS2CTL module - kbc.c,
// ps2ctl.h, ps2ctl.sdl, and ps2main.c
// NOTE: Implementation of this change requires changes to the PS2CTL
// module.
// 
// 55    11/18/10 3:33p Felixp
// Clean up
// 
// 54    11/17/10 4:45p Felixp
// Minor bug fix in SetBootOptionPriorities
// 
// 53    11/15/10 5:23p Felixp
// Default values of the orphan policy macros are updated to 
//   match with the setting of the corresponding SDL tokens.
// ApplyOrphanBootOptionsPolicy renamed to ApplyOrphanBootOptionPolicy
// Some debug messages are removed
// 
// 52    10/07/10 1:35p Felixp
// Make sure code compiles without CSM
// 
// 51    10/07/10 1:21p Felixp
// Support for BOOT_OPTION_GET_BBS_ENTRY_DEVICE_TYPE_FUNCTION SDL token is
// added.
// 
// 50    10/01/10 8:11a Felixp
// Boot option normalization is moved from PreProcessBootOptions 
// to a separate function NormalizeBootOptions.
// 
// 49    9/29/10 9:19a Felixp
// Enhancement(EIP 39464) : Implementation of the BdsEntry function is
// changed. 
// The BdsEntry is now a dispatching function that calls a collection of
// functions 
// formed by the BDS_CONTROL_FLOW eLink.
// 
// 48    9/21/10 3:31p Felixp
// Boot Option Infrastructure Improvements: 
// - NORMALIZE_BOOT_OPTIONS SDL token is replaced with 
//   NORMALIZE_BOOT_OPTION_NAME and NORMALIZE_BOOT_OPTION_DEVICE_PATH
// - MATCH_BOOT_OPTION_BY_LOCATION and MATCH_BOOT_OPTION_BY_DEVICE 
//   SDL tokens and the supporting code are added.
// 
// 47    9/02/10 11:47a Felixp
// 
// 46    8/27/10 9:33a Felixp
// Bug fix in the implementation of the eLink-based hooks.
// Function headers added.
// 
// 45    8/20/10 4:10p Felixp
// Bug fin in LZMA support ( InstallLzmaDecompressProtocol was called too
// late).
// 
// 44    8/20/10 3:25p Felixp
// 
// 43    8/20/10 3:12p Felixp
// LZMA compression support
// 
// 42    6/30/10 11:11a Felixp
// Clean up
// 
// 41    6/29/10 11:03p Felixp
// New Boot Options Maintenance Infrastructure.
// See AMI_Aptio_4.x_Boot_Options_Maintenance_Infrastructure_Porting_Guide
// _NDA.doc for details.
// 
// 40    5/07/10 6:03p Felixp
// Improvement in CreateLegacyBootOption (EIP 38132): Protection against
// BootOrder buffer overrun is added
// 
// 39    4/22/10 10:44p Felixp
// INSTALL_DUMMY_SECURITY_PROTOCOL SDL token is created.
// 
// 38    2/24/10 8:23a Felixp
// 
// 37    2/24/10 8:22a Felixp
// IsFastBoot function removed (it is part of the FastBoot eModule).
// 
// 36    2/03/10 3:40p Oleksiyy
// Minor bug fix 
// 
// 35    2/02/10 5:46p Felixp
// Fast Boot related code is removed from BDS. It is now part of the stand
// alone FastBoot eModule.
// 
// 34    10/28/09 12:23p Felixp
// Minor improvement of the CreateDefaultBootOptions function: compiler
// dependent code is removed(EIP 28577).
// 
// 33    10/09/09 6:18p Felixp
// UGA pixel type replaced with GOP type (UEFI 2.1 compatibility)
// 
// 32    3/06/09 2:12p Felixp
// Bug fix in IsFastBoot function (SetupData pointer was used after memory
// had been freed).
// 
// 31    1/16/09 3:00p Felixp
// Iso9660FileSystemSupportEnabled global constant is added.
// The constant is used to enable/disable ISO96660 partition support in
// the partition driver.
// 
// 30    11/03/08 5:21p Felixp
// Do no re-create boot option for the built-in Shell, if Shell is not
// included into the ROM
// 
// 29    10/22/08 10:58a Felixp
// Code to recreate deleted boot option for the built-in Shell is
// added(EIP 15524). 
// Processing of the DriverOrder list is added.
// 
// 28    10/21/08 5:56p Felixp
// Multi-language support added to UEFI boot options implementation
// 
// 27    10/17/08 3:47p Yakovlevs
// Support for UEFI boot options added
// 
// 26    9/30/08 11:08p Felixp
// BeforeBootProtocolGuid is added
// 
// 25    6/06/08 10:52a Felixp
// Support for boot with minimal configuration added
// 
// 24    11/08/07 4:52p Felixp
// Code updated to compile and work without CSM.
// 
// 23    10/26/07 2:38p Felixp
// New FW based load file protocl is added.
// This protocol is used to load FW based EFI applications such as built
// in Shell.
// 
// 22    10/19/07 9:20a Felixp
//  - SDL tokens are added in CORE_DXE.sdl to customize list of text
// modes.
//  - SDL tokens are added in CORE_DXE.sdl to customize color values(EIP:
// 9854).
// BdsBoard updated with the graphic console tables
// 
// 21    4/10/07 9:36a Felixp
// 
// 19    2/12/07 1:46p Felixp
// 1. Correct handling of disabled legacy BBS options
// 2. Name of the legacy device removed from legacy boot option because it
// is not needed (AMITSE does not use it)
// 3. Clean up in ConnectDevicePath
// 
// 18    1/31/07 11:57a Yakovlevs
// Fixed EIP 8888. BIOS build w/o SIO_SUPPORT
// 
// 17    12/29/06 2:39p Felixp
// 
// 16    10/12/06 9:39a Felixp
// Default boot order changed (from HD, CD to CD,HD)
// 
// 15    6/08/06 7:12p Sivagarn
// - Included function headers
// - Updated file header
// - Fixed EIP 7580 issue. Search for (EIP7580) for changes
// 
// 14    3/13/06 1:44a Felixp
// 
// 13    1/12/06 7:00p Felixp
// Do nor create Shell boot option if Shell module is not in the project
// or disabled.
// 
// 12    12/12/05 9:46a Felixp
// Default boot order changed.
// 
// 11    11/08/05 4:07a Felixp
// Setup notification GUIDs added
// 
// 10    11/07/05 10:26a Felixp
// 1. Support for Boot with Minimum Configuration
// 2. Support for customization of default boot options and their order
// 3. Support for Shell residing at any FV
// 
// 7     5/24/05 2:52p Felixp
// Boot menu moved to SetupEngine
// 
// 2     4/08/05 3:02p Felixp
// Improved responce for the QuietBoot
// 
// 1     4/08/05 7:39a Felixp
// 
//**********************************************************************


//<AMI_FHDR_START>
//---------------------------------------------------------------------------
// Name:        BdsBoard.C
//
// Description: This file contains BDS/CORE_DXE related OEM code.  There are
//              variables defined in this file that might change for each
//              OEM project
////---------------------------------------------------------------------------
//<AMI_FHDR_END>

//---------------------------------------------------------------------------
// Include Files
//---------------------------------------------------------------------------
#include "BootOptions.h"
#include <Protocol/GraphicsOutput.h>
#include <Protocol/Decompress.h>
#include <CORE_DXEStrTokens.h>
#include <Setup.h>
#include <GenericSio.h>
#include <BootOptioneLinks.h>
#ifdef CSM_SUPPORT
#include <Protocol/LegacyBiosExt.h>
#endif

//---------------------------------------------------------------------------
// MACRO Constants
//---------------------------------------------------------------------------
#define _AND_               &       // (EIP7580)+

#ifndef FW_ORPHAN_BOOT_OPTIONS_POLICY
#define FW_ORPHAN_BOOT_OPTIONS_POLICY ORPHAN_BOOT_OPTIONS_POLICY_DELETE
#endif
#ifndef NON_FW_ORPHAN_BOOT_OPTIONS_POLICY
#define NON_FW_ORPHAN_BOOT_OPTIONS_POLICY ORPHAN_BOOT_OPTIONS_POLICY_KEEP
#endif
#ifndef ORPHAN_GROUP_HEADERS_POLICY
#define ORPHAN_GROUP_HEADERS_POLICY ORPHAN_BOOT_OPTIONS_POLICY_DELETE
#endif

//---------------------------------------------------------------------------
// Type definitions
//---------------------------------------------------------------------------
typedef enum{
//    BoTagLegacyXxx
//    BoTagUefiXxx
//    BoTagXxx
    BoTagLegacyFloppy,
    BoTagLegacyHardDisk,
    BoTagLegacyCdrom,
    BoTagLegacyPcmcia,
    BoTagLegacyUsb,
    BoTagLegacyEmbedNetwork,
    BoTagLegacyBevDevice,
    BoTagUefi,
    BoTagEmbeddedShell
} BOOT_OPTION_TAG;

//---------------------------------------------------------------------------
// Constant and Variables declarations
//---------------------------------------------------------------------------
const   UINT16  DefaultTimeout  = DEFAULT_BOOT_TIMEOUT;

STRING_REF BbsDevTypeNameToken[] = {
	STRING_TOKEN(STR_FD),
	STRING_TOKEN(STR_HD),
	STRING_TOKEN(STR_CD),
	STRING_TOKEN(STR_PCMCIA),
	STRING_TOKEN(STR_USB),
	STRING_TOKEN(STR_NET),
	STRING_TOKEN(STR_BEV),
	STRING_TOKEN(STR_UNKNOWN)
};

struct{
    UINT8   Type;
    UINT8	SubType; 			
    STRING_REF StrToken;
} DpStrings[] = {   
    {MESSAGING_DEVICE_PATH, MSG_ATAPI_DP, STRING_TOKEN(STR_ATAPI)},
    {MESSAGING_DEVICE_PATH, MSG_SCSI_DP, STRING_TOKEN(STR_SCSI)},
	{MESSAGING_DEVICE_PATH, MSG_USB_DP, STRING_TOKEN(STR_USB)},
	{MESSAGING_DEVICE_PATH, MSG_MAC_ADDR_DP, STRING_TOKEN(STR_NET)},
	{MEDIA_DEVICE_PATH, MEDIA_HARDDRIVE_DP, STRING_TOKEN(STR_HD)},
	{MEDIA_DEVICE_PATH, MEDIA_CDROM_DP, STRING_TOKEN(STR_CD)}
};

//these GUIDs are used by BDS.c
EFI_GUID    SetupEnterProtocolGuid=AMITSE_SETUP_ENTER_GUID;
EFI_GUID    SecondBootOptionProtocolGuid=AMITSE_AFTER_FIRST_BOOT_OPTION_GUID;
EFI_GUID    BeforeBootProtocolGuid = AMITSE_EVENT_BEFORE_BOOT_GUID;
#ifndef EFI_AMI_LEGACYBOOT_PROTOCOL_GUID
#define EFI_AMI_LEGACYBOOT_PROTOCOL_GUID            \
  {0x120d28aa, 0x6630, 0x46f0, 0x81, 0x57, 0xc0, 0xad, 0xc2, 0x38, 0x3b, 0xf5}
#endif
EFI_GUID    BeforeLegacyBootProtocolGuid = EFI_AMI_LEGACYBOOT_PROTOCOL_GUID;
EFI_GUID    ShellFfsFileNameGuid = SHELL_GUID;
#if Shell_SUPPORT
EFI_GUID    *DefaultAppFfsGuidPtr = &ShellFfsFileNameGuid;
#else
EFI_GUID    *DefaultAppFfsGuidPtr = NULL;
#endif

EFI_GUID    SetupVariableGuid = SETUP_GUID;

struct {
	VENDOR_DEVICE_PATH media;
	MEDIA_FW_VOL_FILEPATH_DEVICE_PATH ffs;
	EFI_DEVICE_PATH_PROTOCOL end;
} ShellDp = {
	{
        {
            MEDIA_DEVICE_PATH, MEDIA_VENDOR_DP,
            sizeof(VENDOR_DEVICE_PATH)
        },
        AMI_MEDIA_DEVICE_PATH_GUID
    },
	{
        {
            MEDIA_DEVICE_PATH, MEDIA_FV_FILEPATH_DP,
            sizeof(MEDIA_FW_VOL_FILEPATH_DEVICE_PATH)
        },
        SHELL_GUID
    },
	{
        END_DEVICE_PATH, END_ENTIRE_SUBTYPE,
        sizeof(EFI_DEVICE_PATH_PROTOCOL)
    }
};

const STRING_REF UnknownDeviceToken = STRING_TOKEN(STR_UNKNOWN);

BOOT_OPTION_TAG LegacyBootOptionTags[] = {
    BoTagLegacyFloppy,
    BoTagLegacyHardDisk,
    BoTagLegacyCdrom,
    BoTagLegacyPcmcia,
    BoTagLegacyUsb,
    BoTagLegacyEmbedNetwork,
    BoTagLegacyBevDevice,
    UNASSIGNED_HIGHEST_TAG
};

BOOT_OPTION_TAG BootOptionTagPriorities[] = {
    BOOT_OPTION_TAG_PRIORITIES,
    UNASSIGNED_HIGHEST_TAG
};

BOOLEAN NormalizeBootOptionName = NORMALIZE_BOOT_OPTION_NAME;
BOOLEAN NormalizeBootOptionDevicePath = NORMALIZE_BOOT_OPTION_DEVICE_PATH;

//---------------------------------------------------------------------------
// External variables
//---------------------------------------------------------------------------
extern  EFI_GUID        EfiVariableGuid;

#if SIO_SUPPORT										// (EIP8888)+
extern  SPIO_LIST_ITEM  SIO_DEVICE_LIST EndOfList;  // (EIP7580)+
#endif												// (EIP8888)-
//---------------------------------------------------------------------------
// Variables
//---------------------------------------------------------------------------

#if SIO_SUPPORT	// (EIP8888)+
SPIO_LIST_ITEM  *gSpioList[] = {SIO_DEVICE_PTR_LIST NULL};  // (EIP7580)+
#endif			// (EIP8888)-

//---------------------------------------------------------------------------
// Function Prototypes
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
// Function Implementations
//---------------------------------------------------------------------------
//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   DevicePathNodeToStrRef
//
// Description: This function converts node from the device path to a string.
//              Once the whole device path is converted the string is used as
//              as a boot opton name.
//              This function is only used is component name protocol does not report device name.
//
// Input:       EFI_DEVICE_PATH_PROTOCOL *Dp  - pointer to the device path node
//
// Output:      STRING_REF - string token (-1, if the string token is not available)
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
STRING_REF DevicePathNodeToStrRef(EFI_DEVICE_PATH_PROTOCOL *Dp){
    UINTN i;
    //Built in Shell is a special case
    if (   NODE_LENGTH(Dp)==NODE_LENGTH(&ShellDp.media.Header)
        && MemCmp(Dp,&ShellDp.media.Header,NODE_LENGTH(Dp))==0
    ) return STRING_TOKEN(STR_SHELL);
    //BBS device path is another special case
#ifdef CSM_SUPPORT
    if ( Dp->Type==BBS_DEVICE_PATH ){
        return BbsDevTypeNameToken[BBS_DEVICE_TYPE_TO_INDEX(((BBS_BBS_DEVICE_PATH*)Dp)->DeviceType)];
    }
#endif
    for (i=0; i < sizeof(DpStrings)/sizeof(DpStrings[0]); i++){
        if ((Dp->Type==DpStrings[i].Type) && (Dp->SubType==DpStrings[i].SubType)){
            return DpStrings[i].StrToken;
        }		
    }//for i

    return INVALID_STR_TOKEN;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   GetBbsEntryDeviceTypeDefault
//
// Description: Using the passed BBS_TABLE entry pointer, determine the device
//              type of the associated device
//
// Input:       BBS_TABLE *BbsEntry - pointer to a BBS_TABLE entry
//
// Output:      UINT16 - device type of the BBS entry, see LegacyBios.h for actual values
//                  BBS_FLOPPY
//                  BBS_HARDDISK
//                  BBS_CDROM
//                  BBS_PCMCIA
//                  BBS_USB
//                  BBS_EMBED_NETWORK
//                  BBS_BEV_DEVICE
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
UINT16 GetBbsEntryDeviceTypeDefault(BBS_TABLE *BbsEntry){
#ifdef CSM_SUPPORT
    UINT16 DeviceType = BbsEntry->DeviceType;
#if BBS_USB_DEVICE_TYPE_SUPPORT
    if (   BbsEntry->Class == PCI_CL_SER_BUS
        && BbsEntry->SubClass == PCI_CL_SER_BUS_SCL_USB
    ) return BBS_USB;
#endif
#if BBS_NETWORK_DEVICE_TYPE_SUPPORT
    if (   BbsEntry->Class == PCI_CL_NETWORK
        && BbsEntry->DeviceType == BBS_BEV_DEVICE
    ) return BBS_EMBED_NETWORK;
#endif
    return DeviceType;
#else
    return 0;
#endif
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   GetLegacyDevOrderType
//
// Description: Using the passed BOOT_OPTION structure, which should correspond to
//              a legacy device entry, determine the device type 
//
// Input:       BOOT_OPTION *Option - pointer to the BOOT_OPTION structure for the 
//                  device in question
//
// Output:      UINT16 - device type of the BOOT_OPTION item, see LegacyBios.h for actual values
//                  BBS_FLOPPY
//                  BBS_HARDDISK
//                  BBS_CDROM
//                  BBS_PCMCIA
//                  BBS_USB
//                  BBS_EMBED_NETWORK
//                  BBS_BEV_DEVICE
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
UINT16 GetLegacyDevOrderType(BOOT_OPTION *Option){
    return ((BBS_BBS_DEVICE_PATH*)Option->FilePathList)->DeviceType;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   FindTagPriority
//
// Description: For the passed Tag entry, return the correct boot priority based on 
//              the BootOptionTagPriorities global variable that is filled out
//              based on the SDL Token BOOT_OPTION_TAG_PRIORITIES.
//
// Input:       UINT16 Tag - one of the following items of the BOOT_OPTION_TAG enum:
//                  BoTagLegacyFloppy
//                  BoTagLegacyHardDisk
//                  BoTagLegacyCdrom
//                  BoTagLegacyPcmcia
//                  BoTagLegacyUsb
//                  BoTagLegacyEmbedNetwork
//                  BoTagLegacyBevDevice
//                  BoTagUefi
//                  BoTagEmbeddedShell
//
// Output:      The index of this item in the BootOptionTagPriorities structure, which
//              also corresponds to the boot priority that should be assigned to this
//              class of device
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
UINT32 FindTagPriority(UINT16 Tag){
    UINT32 i;
    for(i=0; BootOptionTagPriorities[i]!=UNASSIGNED_HIGHEST_TAG; i++)
        if (Tag==BootOptionTagPriorities[i]) return i;
    return UNASSIGNED_HIGHEST_TAG;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   IsShellBootOption
//
// Description: Determine if the passed BOOT_OPTION is the built in EFI Shell
//
// Input:       BOOT_OPTION *Option - the boot option in question
//
// Output:      BOOLEAN -   TRUE - this boot option represent the built in EFI Shell
//                          FALSE - this is not the built in EFI Shell
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
BOOLEAN IsShellBootOption(BOOT_OPTION *Option){
    EFI_DEVICE_PATH_PROTOCOL *Dp = Option->FilePathList;

    if (Dp==NULL) return FALSE;
    if (   NODE_LENGTH(Dp)==NODE_LENGTH(&ShellDp.media.Header)
        && MemCmp(Dp,&ShellDp.media.Header,NODE_LENGTH(Dp))==0
    ) return TRUE;

    return FALSE;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   SetBootOptionTags
//
// Description: Go through the entire boot option list and Apply priorities for 
//              each entry in the list.
//
// Input:       DLIST *BootOptionList - the entire Boot Option List
//
// Output:      none
//
// Note:        To change boot order priorities, do not modify this function,
//              modify the SDL Token BootOptionTagPriorities.
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID SetBootOptionTags(){
	DLINK *Link;
    BOOT_OPTION *Option;
    UINT32 UefiBootOptionsInc = 0x100;

    FOR_EACH_BOOT_OPTION(BootOptionList,Link,Option){
        UINT32 TagPriority;
        UINT32 BaseTag = UNASSIGNED_HIGHEST_TAG;
#ifdef CSM_SUPPORT
        if (IsLegacyBootOption(Option)){
            UINT16 DeviceType;
            DeviceType = ((BBS_BBS_DEVICE_PATH*)Option->FilePathList)->DeviceType;
            BaseTag = LegacyBootOptionTags[BBS_DEVICE_TYPE_TO_INDEX(DeviceType)];
        }else
#endif
        if (IsShellBootOption(Option)) BaseTag = BoTagEmbeddedShell;
        else BaseTag = BoTagUefi;
        if (BaseTag == UNASSIGNED_HIGHEST_TAG) continue;
        TagPriority = FindTagPriority(BaseTag);
        //UEFI boot options must have unique tags, otherwise then will be groupped when 
        //GROUP_BOOT_OPTIONS_BY_TAG tokens is enabled
        if (BaseTag == BoTagUefi) BaseTag += UefiBootOptionsInc++;
        Option->Tag = BootOptionTag(BaseTag, TagPriority);
	}
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   CreateGroupHeader
//
// Description: Create a Group Header Entry for the passed BOOT_OPTION and add the
//              group header to the master boot options list
//
// Input:       DLIST *BootOptionList - the master boot options list to add the newly
//                  created group item
//              BOOT_OPTION *FirstGroupOption - the boot option which needs linked to a 
//                  group item
//
// Output:      none
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID CreateGroupHeader(DLIST *BootOptionList, BOOT_OPTION *FirstGroupOption){
#ifdef CSM_SUPPORT
    static struct {
		BBS_BBS_DEVICE_PATH bbs;
		EFI_DEVICE_PATH_PROTOCOL end;
	} BbsDpTemplate =  {
		{
            {BBS_DEVICE_PATH,BBS_BBS_DP,sizeof(BBS_BBS_DEVICE_PATH)},
            BBS_HARDDISK,0,0
        },
		{END_DEVICE_PATH,END_ENTIRE_SUBTYPE,sizeof(EFI_DEVICE_PATH_PROTOCOL)}
	};

    BOOT_OPTION *Option;

	if (!IsLegacyBootOption(FirstGroupOption)) return;
	Option = CreateBootOption(BootOptionList);
	Option->BootOptionNumber = FirstGroupOption->BootOptionNumber;
	Option->Priority = FirstGroupOption->Priority;
	Option->Tag = FirstGroupOption->Tag;
	Option->FwBootOption = TRUE;
    Option->GroupHeader = TRUE;
    BbsDpTemplate.bbs.DeviceType=GetBbsEntryDeviceType(FirstGroupOption->BbsEntry);
	Option->FilePathList = DPCopy(&BbsDpTemplate.bbs.Header);
	Option->FilePathListLength = DPLength(Option->FilePathList);
    ConstructBootOptionName(Option);
#endif
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   SetBootOptionPriorities
//
// Description: Go through the boot option list and set the priorities of each 
//              group of devices
//
// Input:       DLIST *BootOptionList - the master list of boot options
//
// Output:      none
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID SetBootOptionPriorities(){
	DLINK *Link;
    UINT16 PreviousBootOptionNumber = INVALID_BOOT_OPTION_NUMBER;
    UINT32 PreviousTag = UNASSIGNED_HIGHEST_TAG;
    UINT32 PreviousPriority=0;
    BOOT_OPTION *Option;
    UINT16 NextOptionNumber;

    //Detect first unused boot option number
    NextOptionNumber = 0;
    if (!DListEmpty(BootOptionList)){
        FOR_EACH_BOOT_OPTION(BootOptionList,Link,Option){
            if (   Option->BootOptionNumber != INVALID_BOOT_OPTION_NUMBER 
                && Option->BootOptionNumber > NextOptionNumber 
            ) NextOptionNumber = Option->BootOptionNumber;
        }
        NextOptionNumber++;
    }

	SortList(BootOptionList, CompareTagThenPriority);
    FOR_EACH_BOOT_OPTION(BootOptionList,Link,Option){
#if GROUP_BOOT_OPTIONS_BY_TAG
        if (Option->BootOptionNumber==INVALID_BOOT_OPTION_NUMBER){
            if (   PreviousTag != Option->Tag 
                || Option->Tag==UNASSIGNED_LOWEST_TAG 
                || Option->Tag==UNASSIGNED_HIGHEST_TAG
            ) PreviousBootOptionNumber=NextOptionNumber++;
            Option->BootOptionNumber=PreviousBootOptionNumber;
            Option->Priority=++PreviousPriority;
        }else{
            PreviousBootOptionNumber = Option->BootOptionNumber;
            PreviousPriority = Option->Priority;
        }
		PreviousTag = Option->Tag;
#else
        if (Option->BootOptionNumber==INVALID_BOOT_OPTION_NUMBER){
            Option->BootOptionNumber=(NextOptionNumber)++;
            Option->Priority=++PreviousPriority;
        }else{
            PreviousPriority = Option->Priority;
        }
#endif
	}
    DUMP_BOOT_OPTION_LIST(BootOptionList,"After Setting Priorities");
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   CreateGroupHeaders
//
// Description: Go throuhg the the boot option list and  
//
// Input:       
//
// Output:      
//
// Note: This function assums that the BootOptionList is already sorted by tag and
//          then by priority.  failure to adhere to those assumptions will cause
//          undesired behavoir
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID CreateGroupHeaders(DLIST *BootOptionList){
    DLINK *Link;
    BOOT_OPTION *Option;
    UINT32 PreviousTag = UNASSIGNED_LOWEST_TAG;

    //PRECONDITION: Boot Option List is sorted by tag then by priority

    DUMP_BOOT_OPTION_LIST(BootOptionList,"Before Adding Group Headers");
    FOR_EACH_BOOT_OPTION(BootOptionList,Link,Option){
        if (PreviousTag == Option->Tag) continue;
        PreviousTag = Option->Tag;
        if (   Option->Tag==UNASSIGNED_LOWEST_TAG 
            || Option->Tag==UNASSIGNED_HIGHEST_TAG
        ) continue;
        if (!Option->GroupHeader) CreateGroupHeader(BootOptionList,Option);
	}
}


//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   ApplyOrphanBootOptionPolicy
//
// Description: Apply the correct policy to the passed orphaned boot iptions
//
// Input:       DLIST *BootOptionList - the master boot option list
//              BOOT_OPTION *Option - The orphaned boot option
//              UINTN Policy - the policy to follow, valid values are 
//                  ORPHAN_BOOT_OPTIONS_POLICY_DELETE
//                  ORPHAN_BOOT_OPTIONS_POLICY_DISABLE
//                  ORPHAN_BOOT_OPTIONS_POLICY_KEEP
//
// Output:      
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID ApplyOrphanBootOptionPolicy(
    DLIST *BootOptionList, BOOT_OPTION *Option, const int Policy
){
    if (Policy==ORPHAN_BOOT_OPTIONS_POLICY_DELETE){
        if (Option->BootOptionNumber!=INVALID_BOOT_OPTION_NUMBER){
            CHAR16 BootStr[9];
    		Swprintf(BootStr,L"Boot%04X",Option->BootOptionNumber);
    		pRS->SetVariable(
    			BootStr, &EfiVariableGuid, 0, 0, NULL
    		);
        }    
        DeleteBootOption(BootOptionList, Option);
    }else if (Policy==ORPHAN_BOOT_OPTIONS_POLICY_DISABLE){
        Option->Attributes &= ~LOAD_OPTION_ACTIVE;
    }else if (Policy==ORPHAN_BOOT_OPTIONS_POLICY_HIDE){
        if(!IsLegacyBootOption(Option) || Option->GroupHeader)
            Option->Attributes |= LOAD_OPTION_HIDDEN;
        MaskFilePathList(Option);
    }
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   PreProcessBootOptions
//
// Description: Attempts to find stale boot options in the master boot option
//              list, and apply the specified policy to them. 
//
//              Policy is based on SDL tokens: FW_ORPHAN_BOOT_OPTIONS_POLICY and
//              NON_FW_ORPHAN_BOOT_OPTIONS_POLICY
//
// Input:       DLIST *BootOptionList - master boot option list
//
// Output:      none
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID PreProcessBootOptions(){
    DLINK *Link;
    BOOT_OPTION *Option;

    // Process boot options not associated with the particular boot device.
    // We can't process group headers just yet because groups that
    // are non-empty now, can become empty at the end of this loop
    // once their orphan members are deleted.
    FOR_EACH_BOOT_OPTION(BootOptionList,Link,Option){
        //skip group headers for now; we'll process them later 
		//in the PostProcessBootOptions
        if (Option->GroupHeader || IsBootOptionWithDevice(Option))
            continue;
        if (Option->FwBootOption) 
            ApplyOrphanBootOptionPolicy(
                BootOptionList, Option, FW_ORPHAN_BOOT_OPTIONS_POLICY
            );
        else
            ApplyOrphanBootOptionPolicy(
                BootOptionList, Option, NON_FW_ORPHAN_BOOT_OPTIONS_POLICY
            );
    }
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   PostProcessBootOptions
//
// Description: Go through the master boot option list and apply orphan boot option
//              policy to the boot option groups
//
// Input:       DLIST *BootOptionList - the master boot option list
//
// Output:      none
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID PostProcessBootOptions(){
    DLINK *Link;
    BOOT_OPTION *Option;

    SortList(BootOptionList, CompareTagThenPriority);
    //Now we are ready for the processing of orphan group headers.
    //process empty groups ( groups with just the header)
    FOR_EACH_BOOT_OPTION(BootOptionList,Link,Option){
        if (!Option->GroupHeader) continue;
        if (IsGroupOrphan(Option))
            ApplyOrphanBootOptionPolicy(BootOptionList, Option, ORPHAN_GROUP_HEADERS_POLICY);
    }

#if GROUP_BOOT_OPTIONS_BY_TAG
    CreateGroupHeaders(BootOptionList);
#endif
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   ConstructBootOptionNamePrefixDefault
//
// Description: Based on the passed boot option, determine if a prefix
//              needs prepended to the front of the boot option name.  If return
//              value is non-zero, then the returned number of CHAR16s from the 
//              Name buffer should prepended to the front of the boot option name
//
// Input:       BOOT_OPTION *Option - boot option in question
//              CHAR16 *Name - pointer to the buffer in which to return the prefix
//              UINTN NameSize - size of the buffer being passed
//
// Output:      UINTN - size of the string being returned
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
UINTN ConstructBootOptionNamePrefixDefault(BOOT_OPTION *Option, CHAR16 *Name, UINTN NameSize){
    if (IsLegacyBootOption(Option)) return 0;
    //TODO: use string token
    return Swprintf(Name, L"UEFI: ");
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   ConstructBootOptionNameSuffixDefault
//
// Description: Based on the passed boot option, determine if anything needs appended
//              to the boot option name string.  If return value is not zero, then the
//              returned number of characers should be appended to the end of the name
//              string buffer.
//
// Input:       BOOT_OPTION *Option - the boot option in question
//              CHAR16 *Name - pointer to the buffer to returne the append string
//              UINTN NameSize - the size of the buffer being passed
//
// Output:      
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
UINTN ConstructBootOptionNameSuffixDefault(
    BOOT_OPTION *Option, CHAR16 *Name, UINTN NameSize
){
    return 0;
}

extern DEVICE_PATH_TO_DEVICE_MATCH_TEST BOOT_OPTION_DP_MATCHING_FUNCTIONS EndOfDpMatchingFunctions;
DEVICE_PATH_TO_DEVICE_MATCH_TEST *DpMatchingFunction[] = {
    BOOT_OPTION_DP_MATCHING_FUNCTIONS NULL
};

extern BOOT_OPTION_TO_DEVICE_MATCH_TEST BOOT_OPTION_MATCHING_FUNCTIONS EndOfMatchingFunctions;
BOOT_OPTION_TO_DEVICE_MATCH_TEST *MatchingFunction[] = {
    BOOT_OPTION_MATCHING_FUNCTIONS NULL
};

extern FILTER_BOOT_DEVICE_TEST BOOT_OPTION_BOOT_DEVICE_FILTERING_FUNCTIONS EndOfFilteringFunctions;
FILTER_BOOT_DEVICE_TEST *FilteringFunction[] = {
    BOOT_OPTION_BOOT_DEVICE_FILTERING_FUNCTIONS NULL
};

extern CONSTRUCT_BOOT_OPTION_NAME BOOT_OPTION_BUILD_NAME_FUNCTIONS EndOfBuildNameFunctions;
CONSTRUCT_BOOT_OPTION_NAME *BuildNameFunctions[] = {
    BOOT_OPTION_BUILD_NAME_FUNCTIONS NULL
};

extern BUILD_BOOT_OPTION_FILE_PATH_LIST BOOT_OPTION_BUILD_FILE_PATH_FUNCTIONS EndOfBuildFilePathFunctions;
BUILD_BOOT_OPTION_FILE_PATH_LIST *BuildFilePathFunctions[] = {
  BOOT_OPTION_BUILD_FILE_PATH_FUNCTIONS NULL
};

extern CONSTRUCT_BOOT_OPTION_NAME BOOT_OPTION_NAME_PREFIX_FUNCTION;
CONSTRUCT_BOOT_OPTION_NAME *ConstructBootOptionNamePrefix = BOOT_OPTION_NAME_PREFIX_FUNCTION;

extern CONSTRUCT_BOOT_OPTION_NAME BOOT_OPTION_NAME_SUFFIX_FUNCTION;
CONSTRUCT_BOOT_OPTION_NAME *ConstructBootOptionNameSuffix = BOOT_OPTION_NAME_SUFFIX_FUNCTION;

#ifndef BOOT_OPTION_GET_BBS_ENTRY_DEVICE_TYPE_FUNCTION
#define BOOT_OPTION_GET_BBS_ENTRY_DEVICE_TYPE_FUNCTION GetBbsEntryDeviceTypeDefault
#endif
extern GET_BBS_ENTRY_DEVICE_TYPE BOOT_OPTION_GET_BBS_ENTRY_DEVICE_TYPE_FUNCTION;
GET_BBS_ENTRY_DEVICE_TYPE *GetBbsEntryDeviceType = BOOT_OPTION_GET_BBS_ENTRY_DEVICE_TYPE_FUNCTION;

#if FAST_BOOT_SUPPORT
VOID FastBoot();
BOOLEAN IsFastBoot();

VOID FastBootHook(){
    if(IsFastBoot()) FastBoot();
}
#endif

#if CAPSULE_SUPPORT
EFI_STATUS CapsuleDispatch(IN DXE_SERVICES *DxeServices);
VOID CapsuleHook(){
	DXE_SERVICES *pDxe;
    
    if (EFI_ERROR(LibGetDxeSvcTbl(&pDxe)))
        return;
	// Process capsule
	CapsuleDispatch(pDxe);
}
#endif
//==========================================================
//Graphic Console Tables
//==========================================================
const EFI_GRAPHICS_OUTPUT_BLT_PIXEL ColorArray[] = {			
	{ GC_COLOR_BLACK       ,   0}, // case EFI_BLACK: 		// case EFI_BACKGROUND_BLACK >> 4
	{ GC_COLOR_BLUE        ,   0}, // case EFI_BLUE : 		// case EFI_BACKGROUND_BLUE >> 4
	{ GC_COLOR_GREEN       ,   0}, // case EFI_GREEN : 	// case EFI_BACKGROUND_GREEN >> 4
	{ GC_COLOR_CYAN        ,   0}, // case EFI_CYAN : 		// case EFI_BACKGROUND_CYAN >> 4
	{ GC_COLOR_RED         ,	0}, // case EFI_RED : 		// case EFI_BACKGROUND_RED >> 4
	{ GC_COLOR_MAGENTA     ,	0}, // case EFI_MAGENTA : 	// case EFI_BACKGROUND_MAGENTA >> 4
	{ GC_COLOR_BROWN       ,	0}, // case EFI_BROWN : 	// case EFI_BACKGROUND_BROWN >> 4
	{ GC_COLOR_LIGHTGRAY   ,	0}, // case EFI_LIGHTGRAY : // case EFI_BACKGROUND_LIGHTGRAY >> 4
	{ GC_COLOR_DARKGRAY    ,	0}, // case EFI_DARKGRAY : 
	{ GC_COLOR_LIGHTBLUE   ,	0}, // case EFI_LIGHTBLUE : 
	{ GC_COLOR_LIGHTGREEN  ,	0}, // case EFI_LIGHTGREEN : 
	{ GC_COLOR_LIGHTCYAN   ,	0}, // case EFI_LIGHTCYAN : 
	{ GC_COLOR_LIGHTRED    ,	0}, // case EFI_LIGHTRED : 
	{ GC_COLOR_LIGHTMAGENTA,	0}, // case EFI_LIGHTMAGENTA : 
	{ GC_COLOR_YELLOW      ,	0}, // case EFI_YELLOW : 
	{ GC_COLOR_WHITE       ,	0}  // case EFI_WHITE : 
};

const BOOLEAN Iso9660FileSystemSupportEnabled = 
#ifdef FsIso9660_SUPPORT
    (FsIso9660_SUPPORT==1)
#else
    FALSE
#endif
    ;

BOOLEAN const InstallDummySecurityProtocol = INSTALL_DUMMY_SECURITY_PROTOCOL;

//==========================================================
// LZMA Compression Support
//==========================================================
#if LZMA_SUPPORT

//LZMA Decompress protocol
#define EFI_CUSTOMIZED_DECOMPRESS_PROTOCOL_GUID \
  { 0x9a44198e, 0xa4a2, 0x44e6, 0x8a, 0x1f, 0x39, 0xbe, 0xfd, 0xac, 0x89, 0x6f }

EFI_STATUS LzmaDecomprGetInfo (
	IN VOID *This,
	IN VOID *Source, IN UINT32 SourceSize,
	OUT UINT32 *DestinationSize, OUT UINT32 *ScratchSize
){
	return LzmaGetInfo(Source,SourceSize,DestinationSize,ScratchSize);
}

EFI_STATUS LzmaDecomprDecompress (
	IN VOID *This,
	IN VOID* Source, IN UINT32 SourceSize,
	IN OUT VOID* Destination, IN UINT32 DestinationSize,
	IN OUT VOID* Scratch, IN UINT32 ScratchSize
){
	return LzmaDecompress(Source,SourceSize,Destination,DestinationSize,Scratch,ScratchSize);
}

VOID InstallLzmaDecompressProtocol(
    IN EFI_HANDLE ImageHandle, IN EFI_SYSTEM_TABLE *SystemTable
){
static const EFI_DECOMPRESS_PROTOCOL LzmaDecompressInterface = {
    &LzmaDecomprGetInfo, &LzmaDecomprDecompress
};
static const EFI_GUID CustomizedDecompressProtocolGuid = EFI_CUSTOMIZED_DECOMPRESS_PROTOCOL_GUID;
    EFI_HANDLE Handle = NULL;
    SystemTable->BootServices->InstallProtocolInterface(
		&Handle,(EFI_GUID*)&CustomizedDecompressProtocolGuid, 
        EFI_NATIVE_INTERFACE, (VOID*)&LzmaDecompressInterface
	);        
}
#endif

extern BDS_CONTROL_FLOW_FUNCTION BDS_CONTROL_FLOW EndOfBdsControlFlowFunctions;
BDS_CONTROL_FLOW_FUNCTION *BdsControlFlowFunctions[] = {
    BDS_CONTROL_FLOW NULL
};
CHAR8 *BdsControlFlowFunctionNames[] = {
    BDS_CONTROL_FLOW_NAMES NULL
};

VOID* AutodetectKbdMousePortsPtr=
#if KBC_AUTODETECT_PORTS_FUNCTION
    KBC_AUTODETECT_PORTS_FUNCTION
#else
    NULL
#endif
    ;

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
