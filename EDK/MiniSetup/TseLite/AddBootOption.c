//*****************************************************************//
//*****************************************************************//
//*****************************************************************//
//**                                                             **//
//**         (C)Copyright 2013, American Megatrends, Inc.        **//
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
// $Archive: /Alaska/SOURCE/Modules/AMITSE2_0/AMITSE/TseLite/AddBootOption.c $
//
// $Author: Arunsb $
//
// $Revision: 29 $
//
// $Date: 5/21/14 6:28p $
//
//*****************************************************************//
//*****************************************************************//
// Revision History
// ----------------
// $Log: /Alaska/SOURCE/Modules/AMITSE2_0/AMITSE/TseLite/AddBootOption.c $
// 
// 29    5/21/14 6:28p Arunsb
// [TAG]		EIP170152
// [Category]	Bug Fix
// [Severity:]	Normal
// [Symptom:]	Add boot option failed to add the boot option
// [Root Cause]	If boot order is not there then TSE not allowing to add
// boot options
// [Solution]	If boot order not presents also allowing to add boot option
// [Files]		AddBootOption.c
// 
// 28    5/02/14 12:56p Premkumara
// [TAG]	EIP131549
// [Category]	Bug Fix
// [Severity:]	Important
// [Symptom:]	After adding boot/driver options and Loading defaults causes
// crashing issue.
// [Root Cause]	While discarding boot/driver options the boot order get
// corrupted by copying extra data because of wrong size.
// [Solution]	Handled proper size to copy boot/driver options while
// loading defaults
// [Files]	AddBootOption.c, Special.c
// 
// 27    2/11/14 8:46p Arunsb
// 
// 26    1/30/14 10:58a Arunsb
// [TAG]	EIP132762
// [Category]	Bug Fix
// [Severity:]	Normal
// [Symptom:]	Adding UEFI bootable RHEL OS(Bootx64.efi) from UEFI REHL6.4
// DVD disk causes setup hang
// [Root Cause]	The DevicePath is not created properly while adding boot
// options
// [Solution]	Added '\' before file path name e.g \EFI\Boot\Bootx64.efi
// instead of EFI\Boot\Bootx64.efi
// [Files]	AddBootOption.c
// 
// 25    12/04/13 2:22p Premkumara
// [TAG]	EIP131549
// [Category]	Bug Fix
// [Severity:]	Important
// [Symptom:]	After adding boot/driver options and Loading defaults causes
// crashing issue.
// [Root Cause]	While discarding boot/driver options the boot order get
// corrupted by copying extra data because of wrong size.
// [Solution]	Handled proper size to copy boot/driver options while
// loading defaults
// [Files]	AddBootOption.c, Special.c
// 
// 24    5/22/13 10:56a Premkumara
// [TAG]  		EIP123432 
// [Category]  	Bug Fix
// [Issue Faced]           Take print screen for save & Exit msg box. OK
// of msg box is consumed by Save & Exit msg box.
// 		- Cursor is missing after taking print screen of popupedit box in
// string control
// 		- Printscreen support is not given for Filebrowser feature
// [RootCause]  	- When msg box for Save&Exit is popped and printscreen
// event is called and displaying msg box over Save&Exit. Then msgbox
// handleaction for printscreen event will change the result value in
// _CallbackMsgbox() function so it will break the while loop in
// _CallbackGetValue() function so destroy the next msg box in
// CallbackShowMessageBox() function.
// 		- DrawCursor variable is not set to TRUE after printscreen event
// [Solution]  	- Returning EFI_UNSUPPORTED for printscreen event handling
// function for messgebox and change the result value to 0xff
// 		- Support given for file browser feature
// [Files]  		Callback.c, MessageBox.c, Minisetupext.c, PopupString.c,
// AddBootOption.c
// 		AmiTSEStr.uni, FakeToken.c
// 
// 23    5/22/13 10:51a Arunsb
// EfiLibAllocateCopyPool leads to memory crash so changed it to
// EfiLibAllocateZeroPool
// 
// 22    4/16/13 12:59p Arunsb
// [TAG]  		EIP113590 
// [Category]  	Bug Fix
// [Severity]  	Normal
// [Symptom]  	Can't load default boot priorities if enable token
// "SETUP_SUPPORT_ADD_BOOT_OPTION"
// [RootCause]  	Size calculated wrongly
// [Solution]  	Defaults will be formed only if size is 0, otherwise
// current buffer will be overwritten.
// [Files]  		AddBootOption.c
// 
// 21    3/29/13 12:23p Premkumara
// [TAG]  		EIP97611
// [Category]  	New Feature
// [Description]  	PrintScreen Support in TSE
// [Files]  		AMITSE.sdl, CommonHelper.c, HotKeyBin.h, AddBootOption.c,
// Page.c, TseUefiHii.h, Uefi21Wapper.c
// 
// 20    12/01/12 6:46a Premkumara
// [TAG]  		EIP105725 
// [Category]  	Bug Fix
// [Severity]  	Important
// [Symptom]  	Setup hangs on BBS Menu having string more than 200
// characters
// [RootCause]  	File path string is not handled properly
// [Solution]  	Handled FilePath strings based on length of string and
// allocate memory based on length dynamically
// [Files]  		AddBootOption.c, AMIVfr.h
// 
// 19    10/18/12 6:02a Arunsb
// Updated for 2.16.1235 QA submission
// 
// 15    10/10/12 12:38p Arunsb
// Synched the source for v2.16.1232, backup with Aptio
// 
// 18    5/29/12 4:37a Arunsb
// [TAG]  		EIP91109
// [Category]  	Improvement
// [Description]  	Sync the Aptio IV source for AptioV
// 
// 17    1/24/12 4:37a Arunsb
// [TAG]  		EIP81581
// [Category]  	Improvement
// [Description]  	Default driver order support
// [Files]  		globals.c, addbootoption.c, callback.c, minisetupext.h and
// variable.c
// 
// 16    1/19/12 10:49a Arunsb
// [TAG]  		EIP79956
// [Category]  	Bug Fix
// [Severity]  	Important
// [Symptom]  	Two boot option entries displayed with the single name
// value
// [RootCause]  	If defaults are loaded then boot order is trying to load
// the improper boot order due to add boot option feature
// [Solution]  	Boot order formed properly for add boot option case.
// If no tsedefaultbootorder module present then gOptimalDefaults
// [VARIABLE_ID_BOOT_ORDER] are saved properly in SaveAddDelBootOptions at
// first time.
// At first time optimal buffer is empty so it was filled with some junk
// value so it is changed to fill the current variable list at first time
// of saving with add boot option feature.
// [Files]  		Addbootoption.c and callback.c
// 
// 15    1/09/12 1:50a Arunsb
// [TAG]  		EIP79952
// [Category]  	Bug Fix
// [Severity]  	Normal
// [Symptom]  	Add driver option displays select boot option as title
// [RootCause]  	Title problem
// [Solution]  	Title changes
// [Files]  		Faketokens.c, amitsestr.uni, addbootoption.c,
// uefi2.0\hiicallback.c and uefi21wapper.c
// 
// 14    11/30/11 1:34p Premkumara
// [TAG]  		EIP75352
// [Category]  	Improvement
// [Description]  	Suppress the warnings from static code analyzer
// [Files]  		Boot.c, bbs.c, TseAdvanced.c, Special.c, Variable.c,
// TseLiteHelper.c, PopupSel.c, AddBootOption.c, Hii.c, FormBrowser2.c
// 
// 13    11/13/11 12:54p Arunsb
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
// 12    1/10/11 3:55p Mallikarjunanv
// Updated to work with respect to EDK Libraries
// 
// 11    1/07/11 12:09a Mallikarjunanv
// [TAG]  		EIP51378
// [Description]  	Global variable gHandleBuffer changed to
// gSmplFileSysHndlBuf because of the conflict with HddSecurity module,
// which already using gHandleBuffer.
// 
// 10    1/06/11 11:14p Mallikarjunanv
// [TAG]  		EIP41615
// [Description]  	Updated the files with respect to File Browser support.
// 
// 9     12/28/10 6:20p Mallikarjunanv
// [TAG]  		EIP41615
// [Description]  	Added the file browser support for the Add boot option
// reated controls
// [Files]  		AmiVfr.h, AmiTse.sdl, AmiTseStr.uni, CommonHelper.c,
// Faketokens.c, TseElinks.h, EdkHelper.h, minisetup.h, TseAdvanced.c,
// AddBootOption.c
// 
// 8     3/26/10 5:25p Madhans
// EIP 35562: Support To create Boot option in Capital letters.
// 
// 7     2/26/10 8:54p Madhans
// For TSE 2.01.1024. refer changelog.log for file checkin history .
// 
// 11    2/25/10 8:04a Mallikarjunanv
// Updated the memory corruptions in case of add delete boot options
// 
// 10    2/19/10 8:19a Mallikarjunanv
// updated year in copyright message
// 
// 9     1/28/10 1:10p Mallikarjunanv
// //EIP:34119 - Fix to solve issues, if the boot option name is set with
// max number of characters allowed. 
// 
// 8     1/09/10 7:12a Mallikarjunanv
// Updated TSE2.01 Release sources with coding standards
// 
// 7     1/04/10 10:40a Mallikarjunanv
// EIPs 27161/29095 - Added support for reserved boot option names and
// added support not to create empty boot option names
// 
// 6     12/18/09 2:27p Madhans
// EIP: 32350/32445 To fix the Add/Delete Boot option issues with TSE 2.0.
// 
// 5     8/18/09 5:34p Madhans
// EIP 25367: To resolve the build issue and to avoid redefinition.
// 
// 4     8/13/09 7:39a Mallikarjunanv
// eip:24971 - supporting tse features without tse sources
// 
// 3     6/23/09 6:52p Blaines
// Coding standard update, 
// Remove spaces from file header to allow proper chm function list
// creation.
// 
// 2     6/12/09 7:44p Presannar
// Initial implementation of coding standards for AMITSE2.0
// 
// 1     6/04/09 8:05p Madhans
// 
// 2     4/29/09 9:02p Madhans
// Bug Fixes after unit Testing..
// 
// 1     4/28/09 11:04p Madhans
// Tse 2.0 Code complete Checkin.
// 
// 1     4/28/09 9:39p Madhans
// Tse 2.0 Code complete Checkin.
// 
// 1     12/18/08 7:59p Madhans
// Intial version of TSE Lite sources
// 
//
//*****************************************************************//
//*****************************************************************//

//<AMI_FHDR_START>
//----------------------------------------------------------------------------
//
// Name:		AddBootOption.c
//
// Description:	This file contains code to handle the Add boot option operation.
//
//----------------------------------------------------------------------------
//<AMI_FHDR_END>

#include "minisetup.h"


///////////////////////////////////////////////////////
///	MACRO DEFINITIONS
///////////////////////////////////////////////////////


///////////////////////////////////////////////////////
///	VARIABLE DECLARATIONS
///////////////////////////////////////////////////////

typedef struct// EIP-41615: Start
{
    UINT64 Type;
    UINTN Size;
    CHAR16 *Name;
    STRING_REF Token;
} FILE_TYPE;
EFI_FILE_PROTOCOL 			*gFs 							= NULL;
EFI_GUID 						gSimpleFileSystemGuid 	= EFI_SIMPLE_FILE_SYSTEM_PROTOCOL_GUID;
AMI_POST_MANAGER_PROTOCOL 	*mPostMgr 					= NULL;
static EFI_HANDLE 			*gSmplFileSysHndlBuf 	= NULL;	//EIP:51378 Global variable gHandleBuffer changed to gSmplFileSysHndlBuf because of the conflict with HddSecurity module, which already using gHandleBuffer.
BOOLEAN 							gValidOption 				= FALSE;
UINT16 							gSelIdx						= 0;/// EIP-41615: End
UINTN 							gDelOptionCount;
BOOT_DATA 						*gDelBootData;
UINTN 							gFsCount;
FS_DATA 							*gFsList;
UINTN 							gDriverDelOptionCount;	//EIP70421 & 70422  Support for driver order
BOOT_DATA 						*gDelDriverData;			//EIP70421 & 70422  Support for driver order
///////////////////////////////////////////////////////
///	EXTERN VARIABLES
///////////////////////////////////////////////////////
extern UINTN gDelBootOptionReserved;
extern UINTN gAddBootOptionEmpty;
extern UINTN gAddDriverOptionEmpty;
///////////////////////////////////////////////////////
///	FUNCTION DECLARATIONS
///////////////////////////////////////////////////////
EFI_DEVICE_PATH_PROTOCOL *_BootBuildFileDevicePath( UINT32 *index, CHAR16 *fileName );
VOID 			BbsStrnCpy ( CHAR16  *Dst, CHAR16  *Src, UINTN   Length ); 
VOID 			_GetFsLists (VOID);
UINT16 		*_DevicePathToStr(EFI_DEVICE_PATH_PROTOCOL *Path);
VOID 			FixHiddenOptions (BOOLEAN, UINT16 **, UINTN);
UINT16 		_BootSetBootNowCount(VOID);
EFI_STATUS ShowPostMsgBox(IN CHAR16  *MsgBoxTitle,IN CHAR16  *Message,IN UINT8  MsgBoxType, UINT8 *pSelection);//EIP:41615
EFI_STATUS FileBrowserLaunchFilePath(UINT32 Variable);

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	TseUpdateAddDeleteBootVar
//
// Description:	Function to update add and delete boot variables
//
// Input:	None
//
// Output:	None
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
void TseUpdateAddDeleteBootVar(void)
{
    UINT16 u16DelOption;
    EFI_GUID DelBootOptionGuid = DEL_BOOT_OPTION_GUID;
    EFI_GUID AddBootOptionGuid = ADD_BOOT_OPTION_GUID;
    NEW_BOOT_OPTION AddBootOption;

    //Set del boot option var
    u16DelOption = DISABLED_BOOT_OPTION;
    VarSetNvramName( L"DelBootOption", &DelBootOptionGuid, EFI_VARIABLE_BOOTSERVICE_ACCESS, &u16DelOption, sizeof(UINT16) );

    //Set AddBootOption variable
    _GetFsLists ();
    MemSet(&AddBootOption, sizeof(NEW_BOOT_OPTION),0);
    AddBootOption.FsCount = (UINT16)gFsCount;
    VarSetNvramName( L"AddBootOption", &AddBootOptionGuid, EFI_VARIABLE_BOOTSERVICE_ACCESS, &AddBootOption, sizeof(NEW_BOOT_OPTION) );

}

//EIP70421 & 70422  Support for driver order
//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	TseUpdateAddDeleteDriverVar
//
// Description:	Function to update add and delete driver variables
//
// Input:	None
//
// Output:	None
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
void TseUpdateAddDeleteDriverVar (void)
{
    UINT16 u16DelOption;
    EFI_GUID DelDriverOptionGuid = DEL_DRIVER_OPTION_GUID;
    EFI_GUID AddDriverOptionGuid = ADD_DRIVER_OPTION_GUID;
    NEW_DRIVER_OPTION AddDriverOption;

    //Set del driver option var
    u16DelOption = DISABLED_DRIVER_OPTION;
    VarSetNvramName (L"DelDriverOption", &DelDriverOptionGuid, EFI_VARIABLE_BOOTSERVICE_ACCESS, &u16DelOption, sizeof (UINT16));

    //Set AddDriverOption variable
    _GetFsLists();
    MemSet (&AddDriverOption, sizeof (NEW_DRIVER_OPTION), 0);
    AddDriverOption.FsCount = (UINT16)gFsCount;
    VarSetNvramName (L"AddDriverOption", &AddDriverOptionGuid, EFI_VARIABLE_BOOTSERVICE_ACCESS, &AddDriverOption, sizeof (NEW_DRIVER_OPTION));
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	_GetFsLists
//
// Description:	function to get the file system details 
//
// Input:	None
//
// Output:	None
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID _GetFsLists (VOID)
{
    UINTN Count,i;
    EFI_HANDLE *HandleBuffer;
    EFI_DEVICE_PATH_PROTOCOL *DevicePath;
    CHAR16 *Str;
    EFI_STATUS Status;

    //Find all handles supporting Simple File Sys Protocol
	if (0 == gFsCount)			//EIP70421 Support for driver order; No need of calling continuously boot then driver, one call is enough to set gFsCount
	{
	    Status = gBS->LocateHandleBuffer(
	            ByProtocol,
	            &gEfiSimpleFileSystemProtocolGuid,
	            NULL,
	            &Count,
	            &HandleBuffer
	            );
	    if(EFI_ERROR(Status))
	        return;
	
	    for(i=0;i<Count;i++)
	    {
	        DevicePath = NULL;
	        Status = gBS->OpenProtocol (
	                    HandleBuffer[i],
	                    &gEfiDevicePathProtocolGuid,
	                    (VOID **) &DevicePath,
	                    NULL,
	                    HandleBuffer[i],
						EFI_OPEN_PROTOCOL_GET_PROTOCOL
	                    );
	        if(EFI_ERROR(Status))
	            continue;
	        if(!DevicePath)
	            continue;
	        Str = NULL;
	        Str = _DevicePathToStr(DevicePath);
	
	        gFsList = MemReallocateZeroPool(gFsList, gFsCount * sizeof(FS_DATA), (gFsCount + 1) * sizeof(FS_DATA));
	        gFsList[gFsCount].FsId = Str ? Str : StrDup(L"Unknown");
	        gFsList[gFsCount].FsPath = DevicePath;
	
	        gFsCount++;
	    }
	}
}

static UINT16 DefaultDevicePath[]=L"DevicePath(Type %x, SubType %x)";

static UINT16 *HWDP[] = {
	L"PCI(%X|%X)\\",			//HW_PCI_DP
	L"Pccard(Socket %x)\\",		//HW_PCCARD_DP
	L"VenHw(%g)\\"				//HW_VENDOR_DP
};

/*Uncomment if ACPI details are necessary
static UINT16 *ACPIDP[] = {
	L"Acpi(%x, %x)\\"			//ACPI_DP
};*/

static UINT16 *MSGDP[] = {
	L"ATA(%s,%s)\\",			//MSG_ATAPI_DP
	L"SCSI(%x,%x)\\",			//MSG_SCSI_DP
	L"VenMsg(%g)\\"				//MSG_VENDOR_DP
};

static UINT16 *MEDIADP[] = {
	L"CDROM(Entry%x)\\",		//MEDIA_CDROM_DP
	L"VenMedia(%g)\\",			//MEDIA_VENDOR_DP
	L"%g\\"						//MEDIA_FILEPATH_DP
};

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure: _HWToStr
//
// Description: Convert Device Path of type to string.
//
// Input:
//	IN EFI_DEVICE_PATH_PROTOCOL	*Path - Device Path
//	OUT UINT16			*Str  - String form of device path.
//
// Output:
//		int - number of characters not including \0 or -1 if error.
//
// Notes:	
//          
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
UINTN _HWToStr(
	EFI_DEVICE_PATH_PROTOCOL *Path,
	UINT16			*Str
	)
{
	switch(Path->SubType)
	{
	case HW_PCI_DP:
		return SPrint(Str,0,HWDP[0],((PCI_DEVICE_PATH*)Path)->Device,((PCI_DEVICE_PATH*)Path)->Function);
	case HW_PCCARD_DP:
		return SPrint(Str,0,HWDP[1],((AMITSE_PCCARD_DEVICE_PATH*)Path)->FunctionNumber);
	case HW_VENDOR_DP:
		return SPrint(Str,0,HWDP[2],&((VENDOR_DEVICE_PATH*)Path)->Guid);
	}

	return SPrint(Str,0,DefaultDevicePath,Path->Type,Path->SubType);
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure: ACPIToStr
//
// Description: Convert Device Path of type to string.
//
// Input:
//	IN EFI_DEVICE_PATH_PROTOCOL	*Path - Device Path
//	OUT UINT16			*Str  - String form of device path.
//
// Output:
//		int - number of characters not including \0 or -1 if error.
//
// Notes:	
//          
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
/*
Uncomment below code if ACPI details are necessary.
CAUTION: If ACPI details are included then the string becomes too big
to display
*/
/*
UINTN ACPIToStr(
	EFI_DEVICE_PATH_PROTOCOL *Path,
	UINT16			*Str
	)
{
	switch(Path->SubType)
	{
	case ACPI_DP:
		return SPrint(Str,0,ACPIDP[0], ((ACPI_HID_DEVICE_PATH*)Path)->HID, ((ACPI_HID_DEVICE_PATH*)Path)->UID);
	}
	return SPrint(Str,0,DefaultDevicePath,Path->Type,Path->SubType);
}
*/

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure: _MSGToStr
//
// Description: Convert Device Path of type to string.
//
// Input:
//	IN EFI_DEVICE_PATH_PROTOCOL	*Path - Device Path
//	OUT UINT16			*Str  - String form of device path.
//
// Output:
//		int - number of characters not including \0 or -1 if error.
//
// Notes:	
//          
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
UINTN _MSGToStr(
	EFI_DEVICE_PATH_PROTOCOL *Path,
	UINT16			*Str
	)
{
	switch(Path->SubType)
	{
	case MSG_ATAPI_DP:
        return SPrint(Str,0,MSGDP[0],
            ((ATAPI_DEVICE_PATH*)Path)->PrimarySecondary ? L"Sec" : L"Pri",
            ((ATAPI_DEVICE_PATH*)Path)->SlaveMaster ? L"Sl" :L"Ma");
	case MSG_SCSI_DP:
		return SPrint(Str,0,MSGDP[1], ((SCSI_DEVICE_PATH*)Path)->Pun, ((SCSI_DEVICE_PATH*)Path)->Lun);
	case MSG_VENDOR_DP:
		return SPrint(Str,0,MSGDP[2], ((VENDOR_DEVICE_PATH*)Path)->Guid);
	case MSG_USB_DP:
		return SPrint(Str,0,L"USB(%x,%x)\\",
			((USB_DEVICE_PATH*)Path)->ParentPortNumber,((USB_DEVICE_PATH*)Path)->InterfaceNumber);
		
	}
	return SPrint(Str,0,DefaultDevicePath,Path->Type,Path->SubType);
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure: _MEDIAToStr
//
// Description: Convert Device Path of type to string.
//
// Input:
//	IN EFI_DEVICE_PATH_PROTOCOL	*Path - Device Path
//	OUT UINT16			*Str  - String form of device path.
//
// Output:
//		int - number of characters not including \0 or -1 if error.
//
// Notes:	
//          
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
UINTN _MEDIAToStr(
	EFI_DEVICE_PATH_PROTOCOL *Path,
	UINT16			*Str
	)
{
	switch(Path->SubType)
	{
	case MEDIA_HARDDRIVE_DP:
        {
            HARDDRIVE_DEVICE_PATH *Hd = (HARDDRIVE_DEVICE_PATH *)Path;
            switch(Hd->SignatureType)
            {
            case SIGNATURE_TYPE_MBR:
                return SPrint(Str,0,L"HD(Part%d,Sig%08X)", Hd->PartitionNumber, *((UINT32 *)(&(Hd->Signature[0]))));
            case SIGNATURE_TYPE_GUID:
                return SPrint(Str,0, L"HD(Part%d,Sig%g)", Hd->PartitionNumber, (EFI_GUID *) &(Hd->Signature[0]));
            default:
                return SPrint(Str,0,L"HD(Part%d,MBRType=%02x,SigType=%02x)", 
                Hd->PartitionNumber,
                Hd->MBRType,
                Hd->SignatureType
                );
            }
        }
	case MEDIA_CDROM_DP:
		return SPrint(Str,0,MEDIADP[0], ((CDROM_DEVICE_PATH*)Path)->BootEntry);
	case MEDIA_VENDOR_DP:
		return SPrint(Str,0,MEDIADP[1], ((VENDOR_DEVICE_PATH*)Path)->Guid);
	case MEDIA_FILEPATH_DP:
		return SPrint(Str,0,MEDIADP[2], &((AMITSE_MEDIA_FW_VOL_FILEPATH_DEVICE_PATH*)Path)->FvFileName);
	}
	return SPrint(Str,0,DefaultDevicePath,Path->Type,Path->SubType);
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure: _UnknownToStr
//
// Description: Convert Device Path of type to string.
//
// Input:
//	IN EFI_DEVICE_PATH_PROTOCOL	*Path - Device Path
//	OUT UINT16			*Str  - String form of device path.
//
// Output:
//		int - number of characters not including \0 or -1 if error.
//
// Notes:	
//          
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
UINTN _UnknownToStr(
	EFI_DEVICE_PATH_PROTOCOL *Path,
	UINT16			*Str
	)
{
	return SPrint(Str,0,DefaultDevicePath,Path->Type,Path->SubType);
}


//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure: _DevicePathToStr
//
// Description: Convert Device Path of type to string. Str is allocated by
//  this routine. It must be freed by the caller.
//
// Input:
//	IN EFI_DEVICE_PATH_PROTOCOL	*Path - Device Path
//	
//
// Output:
//		OUT UINT16			*Str  - String form of device path.
//
// Notes:	
//          
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
UINT16 *_DevicePathToStr(EFI_DEVICE_PATH_PROTOCOL *Path)
{
	CHAR16	Buffer[512];
	CHAR16	*p = Buffer, *Str = NULL;
	UINTN	Count = 0;
	UINTN	Length;

    MemSet(Buffer,sizeof(Buffer),0);
	for(;;)
	{
		switch(Path->Type)
		{
		case HARDWARE_DEVICE_PATH:
			Count = _HWToStr(Path, p);
			break;
		case ACPI_DEVICE_PATH:
/*
Uncomment below code if ACPI details are necessary.
CAUTION: If ACPI details are included then the string becomes too big
to display
*/
/*
            Count = SPrint(p,0,L"Acpi\\");
            ACPIToStr(Path, p);
*/
			break;
		case MESSAGING_DEVICE_PATH:
			Count = _MSGToStr(Path, p);
			break;
		case MEDIA_DEVICE_PATH:
			Count = _MEDIAToStr(Path, p);
			break;
		case END_DEVICE_PATH_TYPE:
			Count = 0;
			break;
		case END_ENTIRE_DEVICE_PATH_SUBTYPE:
			*p = L'|';
			*(p+1) = L'\0';
			Count = 1;
			break;
		default:
			Count = _UnknownToStr(Path, p);
		}

		p += EfiStrLen(p);

		if (Count == -1) return NULL;
		if (IsDevicePathEnd(Path)) break;

		Path = NextDevicePathNode(Path);
	}

	Length = (UINTN)p - (UINTN)Buffer;

	Str = (UINT16 *)EfiLibAllocateZeroPool(Length+sizeof(UINT16));

	MemCopy(Str, Buffer, Length);

	return Str;
}

//EIP70421 & 70422  Support for driver order
//<AMI_PHDR_START>
//--------------------------------------------------------------------------------------------
// Procedure:	_DisableRestorePrevOptions
//
// Description:	Function to make the boot/driver option as disable in bootorder/driverorder
//				if it is inactive and non hidden
//
//
// Input:		BOOLEAN , UINT16 **, UINTN 
//
// Output:		VOID
//
//-------------------------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID _DisableRestorePrevOptions (BOOLEAN Option, UINT16 **Order, UINTN OptionCount)
{
	UINTN iIndex = 0;
	BOOT_DATA   *pBootData;

	if (0 == OptionCount)
	{
		return;
	}
	for (iIndex = 0; iIndex < OptionCount; iIndex ++)
	{
		if (BOOT_ORDER_OPTION == Option)
		{
			pBootData = BootGetBootData ((*Order) [iIndex]);
		}
		else
		{
			pBootData = DriverGetDriverData ((*Order) [iIndex]);
		}
		if (pBootData)
		{
			if ( (!(pBootData->Active & LOAD_OPTION_ACTIVE)) && (!(pBootData->Active & LOAD_OPTION_HIDDEN)) )
			{
					(*Order) [iIndex] = DISABLED_BOOT_OPTION;
			}
		}
	}
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	BootAddBootOption
//
// Description:	Function to add boot option 
//
// Input:		VOID
//
// Output:		VOID
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID BootAddBootOption( VOID )
{
    UINTN i,size;
    UINT16 u16Option;
    NEW_BOOT_OPTION *newBoot = NULL, *tmpPtr;
    CHAR16 *fileName;
    UINT32 index;
    EFI_DEVICE_PATH_PROTOCOL *devicePath;
    UINT16 *NewBootOrder = NULL, *CurrBootOrder = NULL;
    UINT16 BootCountVal;
    CHAR16 *BootNameBuf = NULL;		//EIP:34119
	EFI_STATUS Status;
    //Get input
    size = 0;
    Status = gBS->LocateProtocol(&gAmiPostManagerProtocolGuid, NULL,(void**) &mPostMgr);
    if(Status != EFI_SUCCESS)
  	    return;
    newBoot = VarGetVariable( VARIABLE_ID_ADD_BOOT_OPTION, &size );
	//EIP-75352 Suppress the warnings from static code analyzer
	if (NULL == newBoot){
        return;
    }

//EIP:34119 - Start
	//Fix EIP:29095 - not to create boot option with out a name
    if (( EfiStrLen( newBoot->Path ) == 0 ) || ( EfiStrLen(newBoot->Label) == 0 ))
    {
	//	CallbackShowMessageBox( (UINTN)gAddBootOptionEmpty, MSGBOX_TYPE_OK );
		
    	 mPostMgr->DisplayMsgBox(  L"WARNING",  L"Please set Boot Option Name and File Path", MSGBOX_TYPE_OK,NULL);
		return;
    }
    BootNameBuf = EfiLibAllocateZeroPool( sizeof(newBoot->Label)+2 );  
    BbsStrnCpy( BootNameBuf, newBoot->Label, (sizeof(newBoot->Label))/2 );
//EIP:34119 - End

    // cleanup old data
    tmpPtr = EfiLibAllocateZeroPool( size );
    tmpPtr->FsCount = (UINT16)gFsCount;
    VarSetValue( VARIABLE_ID_ADD_BOOT_OPTION, 0, size, tmpPtr );
    MemFreePointer( (VOID **)&tmpPtr );

    fileName = newBoot->Path;

    index = newBoot->SelFs;

    devicePath = _BootBuildFileDevicePath( &index, fileName );
    if ( devicePath != NULL )
    {
        EFI_DEVICE_PATH_PROTOCOL *TmpDevPath, *HddMediaPath;

        //Find a free option number
        for ( u16Option = 0; u16Option < MAX_BOOT_OPTIONS; u16Option++ )
        {
            for(i=0;i<gBootOptionCount;i++)
            {
                if(gBootData[i].Option == u16Option)
                    break;
            }
            if(i<gBootOptionCount)
                continue;
            for(i=0;i<gDelOptionCount;i++)
            {
                 if(gDelBootData[i].Option == u16Option)
                    break;
            }
            if(i<gDelOptionCount)
                continue;
            
            break;//The desired option number is in u16Option
        }
    
        if ( u16Option == MAX_BOOT_OPTIONS ) //Not possible
            return;

        gBootData = MemReallocateZeroPool(gBootData, gBootOptionCount * sizeof(BOOT_DATA), (gBootOptionCount + 1) * sizeof(BOOT_DATA) );

        gBootData[gBootOptionCount].Option = u16Option;
        gBootData[gBootOptionCount].Active |= LOAD_OPTION_ACTIVE;
//EIP:34119 - Fix to solve issues, if the boot option name is set with max number of characters allowed. 
        //gBootData[gBootOptionCount].Name = StrDup( newBoot->Label );
        gBootData[gBootOptionCount].Name = BootNameBuf;
//EIP:34119 - End

        //For a hard drive start the dev path from the partition
        for( TmpDevPath = devicePath; 
             !IsDevicePathEndType(TmpDevPath);
             TmpDevPath=NextDevicePathNode(TmpDevPath)
        )
        {
            if(TmpDevPath->Type==MEDIA_DEVICE_PATH && TmpDevPath->SubType==MEDIA_HARDDRIVE_DP)
            {
                HddMediaPath = EfiLibAllocateZeroPool(EfiDevicePathSize(TmpDevPath));
                MemCopy(HddMediaPath, TmpDevPath, EfiDevicePathSize(TmpDevPath));
                MemFreePointer((VOID **)&devicePath);
                devicePath = HddMediaPath;
                break;
            }
        }
        gBootData[gBootOptionCount].DevicePath = devicePath;
        gBootData[gBootOptionCount].bNewOption = TRUE;

        size = 0;
        CurrBootOrder = VarGetVariable(VARIABLE_ID_BOOT_ORDER, &size);
		//EIP-75352 Suppress the warnings from static code analyzer
/*        if (NULL == CurrBootOrder){		//If file system available and no boot option presents then add boot option always fails so commenting it.
            return;
        }*/
        NewBootOrder = EfiLibAllocateZeroPool((gBootOptionCount+1) * sizeof(UINT16));

        for(i=0;i<gBootOptionCount;i++)
        {
            if(DISABLED_BOOT_OPTION == CurrBootOrder[i])
                break;
            NewBootOrder[i] = CurrBootOrder[i];
        }
		if (i < gBootOptionCount)		//Preserve the hidden options at last
		{
			MemCpy (NewBootOrder+i+1, CurrBootOrder+i, (gBootOptionCount-i)*2);
		}
        NewBootOrder [i] = u16Option;
        //i ++;
        MemFreePointer ((VOID **) &CurrBootOrder);
        gBootOptionCount ++;
        MemFreePointer ((VOID **)&newBoot);

        //Update boot manager vars in memory
        //1. TSE Boot order
        MemFreePointer((VOID **) &gVariableList[VARIABLE_ID_BOOT_ORDER].Buffer);
		if (gLoadOptionHidden)				//Move hidden options to last
		{
			FixHiddenOptions (BOOT_ORDER_OPTION, &NewBootOrder, gBootOptionCount);
		}
        gVariableList[VARIABLE_ID_BOOT_ORDER].Buffer = (UINT8 *)NewBootOrder;
        gVariableList[VARIABLE_ID_BOOT_ORDER].Size = gBootOptionCount * sizeof(UINT16);

        //2. BootManager
        BootCountVal = (UINT16)gBootOptionCount;
        VarSetValue(VARIABLE_ID_BOOT_MANAGER, 0, sizeof(UINT16), (VOID *)(&BootCountVal));

        //3. Set Boot now count
		if(gShowAllBbsDev)
	        BootCountVal = _BootSetBootNowCount();

        Status = VarSetValue(VARIABLE_ID_BOOT_NOW, 0, sizeof(UINT16), (VOID *)(&BootCountVal));
        if(Status == EFI_SUCCESS)
        	mPostMgr->DisplayMsgBox(  L"SUCCESS",  L"Boot Option Created Successfully", MSGBOX_TYPE_OK,NULL);
    }
}

//EIP70421 & 70422  Support for driver order
//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	DriverAddDriverOption
//
// Description:	Function to add driver options
//
// Input:		VOID
//
// Output:		VOID
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID DriverAddDriverOption(VOID)
{
    UINTN i,size;
    UINT16 u16Option;
    NEW_DRIVER_OPTION *newDriver = NULL, *tmpPtr;
    CHAR16 *fileName;
    UINT32 index;
    EFI_DEVICE_PATH_PROTOCOL *devicePath;
    UINT16 *NewDriverOrder = NULL, *CurrDriverOrder = NULL;
    UINT16 DriverCountVal;
    CHAR16 *BootNameBuf = NULL;
	EFI_STATUS Status;
	 //Get input
    size = 0;
    Status = gBS->LocateProtocol(&gAmiPostManagerProtocolGuid, NULL,(void**) &mPostMgr);
    if(Status != EFI_SUCCESS)
	    return;
    newDriver = VarGetVariable( VARIABLE_ID_ADD_DRIVER_OPTION, &size );
	if (( EfiStrLen (newDriver->DriverPath) == 0 ) || (EfiStrLen (newDriver->Label) == 0))
    {
		//CallbackShowMessageBox( (UINTN)gAddDriverOptionEmpty, MSGBOX_TYPE_OK );
		
		 mPostMgr->DisplayMsgBox(  L"WARNING",  L"Please set Driver Option Name and File Path", MSGBOX_TYPE_OK,NULL);
		return;
    }

	BootNameBuf = EfiLibAllocateZeroPool( sizeof(newDriver->Label)+2 );  
    BbsStrnCpy( BootNameBuf, newDriver->Label, (sizeof(newDriver->Label))/2 );	
	
	    // cleanup old data
    tmpPtr = EfiLibAllocateZeroPool( size );
    tmpPtr->FsCount = (UINT16)gFsCount;
    VarSetValue( VARIABLE_ID_ADD_DRIVER_OPTION, 0, size, tmpPtr );
    MemFreePointer( (VOID **)&tmpPtr );

    fileName = newDriver->DriverPath;

    index = newDriver->SelFs;

    devicePath = _BootBuildFileDevicePath( &index, fileName );
	
	if ( devicePath != NULL )
    {
//        EFI_DEVICE_PATH_PROTOCOL *TmpDevPath, *HddMediaPath;

        //Find a free option number
        for ( u16Option = 0; u16Option < MAX_BOOT_OPTIONS; u16Option++ )
        {
         for(i=0;i<gDriverOptionCount;i++)
            {
                if(gDriverData[i].Option == u16Option)
                    break;
            }
            if(i<gDriverOptionCount)
                continue;
		 for(i=0;i<gDriverDelOptionCount;i++)
            {
                 if(gDelDriverData[i].Option == u16Option)
                    break;
            }
            if(i<gDriverDelOptionCount)
                continue;
            
            break;//The desired option number is in u16Option
        }

        if ( u16Option == MAX_BOOT_OPTIONS ) //Not possible
            return;

        gDriverData = MemReallocateZeroPool(gDriverData, gDriverOptionCount * sizeof(BOOT_DATA), (gDriverOptionCount + 1) * sizeof(BOOT_DATA) );

        gDriverData[gDriverOptionCount].Option = u16Option;
        gDriverData[gDriverOptionCount].Active |= LOAD_OPTION_ACTIVE;
//EIP:34119 - Fix to solve issues, if the boot option name is set with max number of characters allowed. 
        //gBootData[gBootOptionCount].Name = StrDup( newDriver->Label );
        gDriverData[gDriverOptionCount].Name = BootNameBuf;
//EIP:34119 - End

        /*
		//TSE will append hard drive device path at front if it is MEDIA_DEVICE_PATH but core needs fullpath so commented below
		//For a hard drive start the dev path from the partition
        for( TmpDevPath = devicePath; 						
             !IsDevicePathEndType(TmpDevPath);
             TmpDevPath=NextDevicePathNode(TmpDevPath)
        )
        {
            if(TmpDevPath->Type==MEDIA_DEVICE_PATH && TmpDevPath->SubType==MEDIA_HARDDRIVE_DP)
            {
                HddMediaPath = EfiLibAllocateZeroPool(EfiDevicePathSize(TmpDevPath));
                MemCopy(HddMediaPath, TmpDevPath, EfiDevicePathSize(TmpDevPath));
                MemFreePointer((VOID **)&devicePath);
                devicePath = HddMediaPath;
                break;
            }
        }*/

		gDriverData[gDriverOptionCount].DevicePath = devicePath;
        gDriverData[gDriverOptionCount].bNewOption = TRUE;

        size = 0;
        CurrDriverOrder = VarGetVariable(VARIABLE_ID_DRIVER_ORDER, &size);
        NewDriverOrder = EfiLibAllocateZeroPool((gDriverOptionCount+1) * sizeof(UINT16));

        for(i=0;i<gDriverOptionCount;i++)
        {
            if(DISABLED_DRIVER_OPTION == CurrDriverOrder[i])
                break;
            NewDriverOrder[i] = CurrDriverOrder[i];
        }
		if (i < gDriverOptionCount)		//Preserve the hidden options at last
		{
			MemCpy (NewDriverOrder+i+1, CurrDriverOrder+i, (gDriverOptionCount-i)*2);
		}

        NewDriverOrder[i] = u16Option;
        //i++;

        MemFreePointer((VOID **) &CurrDriverOrder);

        gDriverOptionCount ++;

        MemFreePointer( (VOID **)&newDriver );

        //Update boot manager vars in memory
        //1. TSE driver order
        MemFreePointer((VOID **) &gVariableList[VARIABLE_ID_DRIVER_ORDER].Buffer);
		if (gLoadOptionHidden)			//Move the hidden options to last
		{
			FixHiddenOptions (DRIVER_ORDER_OPTION, &NewDriverOrder, gDriverOptionCount);
		}
        gVariableList[VARIABLE_ID_DRIVER_ORDER].Buffer = (UINT8 *)NewDriverOrder;
        gVariableList[VARIABLE_ID_DRIVER_ORDER].Size = gDriverOptionCount * sizeof(UINT16);

        //2. DriverManager
        DriverCountVal = (UINT16)gDriverOptionCount;
        Status = VarSetValue(VARIABLE_ID_DRIVER_MANAGER, 0, sizeof(UINT16), (VOID *)(&DriverCountVal));
        if(Status == EFI_SUCCESS)
                mPostMgr->DisplayMsgBox(  L"SUCCESS",  L"Driver Option Created Successfully", MSGBOX_TYPE_OK,NULL);
	}
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	BootDelBootOption
//
// Description:	Function to handle the del boot option 
//
// Input:		UINT16 index
//
// Output:		VOID
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID BootDelBootOption( UINT16 index )
{
    UINTN i,j,k, size;
    BOOT_DATA *pBootData = NULL;
    UINT16 BootCountVal;
    UINT16 *NewBootOrder = NULL, *CurrBootOrder = NULL;
    EFI_STATUS Status=EFI_UNSUPPORTED;
    VOID * UnicodeInterface;
    CHAR16 *ResStr = NULL;
    CHAR16 *TmpStr = NULL;
	
	// If it BBS device we should not delete it.
	// FIX......to check for the correct Boot option.
    Status = gBS->LocateProtocol(&gAmiPostManagerProtocolGuid, NULL,(void**) &mPostMgr);
      if(Status != EFI_SUCCESS)
  	    return;
	for(i=0; i<gBootOptionCount; i++)
    {
    	if(index == gBootData[i].Option)
		{
 		   if(gBootData[i].DevicePath->Type == BBS_DEVICE_PATH && gBootData[i].DevicePath->SubType == BBS_BBS_DP)
				return;

			///Fix: Eip-27161 - not to allow Reserved boot options to delete 
			if( ( IsReservedBootOptionNamesEnable() ) && 
			    ( gBootData[i].Name ) ) 
			{ 
				ResStr = CONVERT_TO_WSTRING(RESERVED_ADD_DEL_BOOT_OPTION_NAME);
				TmpStr = EfiLibAllocateZeroPool( EfiStrLen(ResStr)+1 ); 
				BbsStrnCpy(TmpStr, gBootData[i].Name, (EfiStrLen(ResStr)+1) );
				TmpStr[EfiStrLen(ResStr)]= L'\0';
				Status = InitUnicodeCollectionProtocol(&UnicodeInterface);
				if(!EFI_ERROR(Status)) {
					if( StringColl( UnicodeInterface, TmpStr, ResStr) == 0 )
					{
						//CallbackShowMessageBox( (UINTN)gDelBootOptionReserved, MSGBOX_TYPE_OK );
						 mPostMgr->DisplayMsgBox(  L"WARNING",  L"Reserved Boot Option, can not be Deleted", MSGBOX_TYPE_OK,NULL);
						return;
					}
				}
			}
		}
	}

    //Remove option from gBootData and add to gDelBootData
    //Remove option from BootOrder
    if(gBootOptionCount - 1)
    {
        pBootData = EfiLibAllocateZeroPool(sizeof(BOOT_DATA) * (gBootOptionCount - 1));
        NewBootOrder = EfiLibAllocateZeroPool(sizeof(UINT16) * (gBootOptionCount - 1));
    }

    size = 0;
    CurrBootOrder = VarGetVariable(VARIABLE_ID_BOOT_ORDER, &size);
	//EIP-75352 Suppress the warnings from static code analyzer
    if (NULL == CurrBootOrder){
        return;
    }

    gDelBootData = MemReallocateZeroPool(gDelBootData, sizeof(BOOT_DATA) * gDelOptionCount, sizeof(BOOT_DATA) * (gDelOptionCount + 1));

    for(i=0,j=0,k=0; i<gBootOptionCount; i++)
    {
        if(index == gBootData[i].Option)
        {
            MemCopy(gDelBootData + gDelOptionCount, gBootData + i, sizeof(BOOT_DATA));
        }
        else
        {
            MemCopy(pBootData + j, gBootData + i, sizeof(BOOT_DATA));
            j++;
        }

        if(index != CurrBootOrder[i])
        {
            if(k<(gBootOptionCount-1))
            {
                NewBootOrder[k] = CurrBootOrder[i];
                k++;
            }
        }
    }

    gDelOptionCount++;
    gBootOptionCount--;

    MemFreePointer((VOID **)&gBootData);
    gBootData = pBootData;

    MemFreePointer((VOID **)&CurrBootOrder);

    //Update boot manager vars in memory
    //1. TSE Boot order
    MemFreePointer((VOID **) &gVariableList[VARIABLE_ID_BOOT_ORDER].Buffer);
	if (gLoadOptionHidden)			//Move the hidden options to last
	{
		FixHiddenOptions (BOOT_ORDER_OPTION, &NewBootOrder, gBootOptionCount);
	}
    gVariableList[VARIABLE_ID_BOOT_ORDER].Buffer = (UINT8 *)NewBootOrder;
    gVariableList[VARIABLE_ID_BOOT_ORDER].Size = gBootOptionCount * sizeof(UINT16);

    //2. BootManager
    BootCountVal = (UINT16)gBootOptionCount;
    VarSetValue(VARIABLE_ID_BOOT_MANAGER,0,sizeof(UINT16),(VOID *)(&BootCountVal));

    //3. Set Boot now count
	if(gShowAllBbsDev)
	    BootCountVal = _BootSetBootNowCount();

    Status = VarSetValue(VARIABLE_ID_BOOT_NOW,0,sizeof(UINT16),(VOID *)(&BootCountVal));
    if(EFI_SUCCESS == Status)
	    mPostMgr->DisplayMsgBox(  L"SUCCESS",  L"Boot Option Deleted Successfully", MSGBOX_TYPE_OK,NULL);
}

//EIP70421 & 70422  Support for driver order
//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	DriverDelDriverOption
//
// Description:	Function to handle the del Driver option 
//
// Input:		UINT16 index
//
// Output:		VOID
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID DriverDelDriverOption( UINT16 index )
{
	UINTN i,j,k, size;
    BOOT_DATA *pDriverData = NULL;
    UINT16 DriverCountVal;
    UINT16 *NewDriverOrder = NULL, *CurrDriverOrder = NULL;
    EFI_STATUS Status=EFI_UNSUPPORTED;
//    VOID * UnicodeInterface;
    CHAR16 *ResStr = NULL;
    CHAR16 *TmpStr = NULL;
	
	if ((NULL == gDriverData) ||  (0 == gDriverOptionCount))
		return;
	Status = gBS->LocateProtocol(&gAmiPostManagerProtocolGuid, NULL,(void**) &mPostMgr);
	      if(Status != EFI_SUCCESS)
	  	    return;
	for(i=0; i<gDriverOptionCount; i++)
    {
    	if(index == gDriverData[i].Option)
		{
 		   if(gDriverData[i].DevicePath->Type == BBS_DEVICE_PATH && gDriverData[i].DevicePath->SubType == BBS_BBS_DP)
				return;
			break;
		}
	}

    //Remove option from gDriverData and add to gDelDriverData
    //Remove option from DriverOrder
    if(gDriverOptionCount - 1)
    {
        pDriverData = EfiLibAllocateZeroPool(sizeof(BOOT_DATA) * (gDriverOptionCount - 1));
        NewDriverOrder = EfiLibAllocateZeroPool(sizeof(UINT16) * (gDriverOptionCount - 1));
    }

    size = 0;
    CurrDriverOrder = VarGetVariable(VARIABLE_ID_DRIVER_ORDER, &size);

    gDelDriverData = MemReallocateZeroPool(gDelDriverData, sizeof(BOOT_DATA) * gDriverDelOptionCount, sizeof(BOOT_DATA) * (gDriverDelOptionCount + 1));

    for(i=0,j=0,k=0; i<gDriverOptionCount; i++)
    {
        if(index == gDriverData[i].Option)
        {
            MemCopy(gDelDriverData + gDriverDelOptionCount, gDriverData + i, sizeof(BOOT_DATA));
        }
        else
        {
            MemCopy(pDriverData + j, gDriverData + i, sizeof(BOOT_DATA));
            j++;
        }

        if(index != CurrDriverOrder[i])
        {
            if(k<(gDriverOptionCount-1))
            {
                NewDriverOrder[k] = CurrDriverOrder[i];
                k++;
            }
        }
    }

    gDriverDelOptionCount++;
    gDriverOptionCount--;

    MemFreePointer((VOID **)&gDriverData);
    gDriverData = pDriverData;

    MemFreePointer((VOID **)&CurrDriverOrder);

    //Update boot manager vars in memory
    //1. TSE Driver Order
    MemFreePointer((VOID **) &gVariableList[VARIABLE_ID_DRIVER_ORDER].Buffer);
	if (gLoadOptionHidden)
	{
		FixHiddenOptions (DRIVER_ORDER_OPTION, &NewDriverOrder, gDriverOptionCount);
	}
    gVariableList[VARIABLE_ID_DRIVER_ORDER].Buffer = (UINT8 *)NewDriverOrder;
    gVariableList[VARIABLE_ID_DRIVER_ORDER].Size = gDriverOptionCount * sizeof(UINT16);

    //2. DriverManager
    DriverCountVal = (UINT16)gDriverOptionCount;
    Status =  VarSetValue(VARIABLE_ID_DRIVER_MANAGER,0,sizeof(UINT16),(VOID *)(&DriverCountVal));
    if(EFI_SUCCESS == Status)
	    mPostMgr->DisplayMsgBox(  L"SUCCESS",  L"Driver Deleted Successfully", MSGBOX_TYPE_OK,NULL);
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	DiscardAddDelBootOptions
//
// Description:	Function to discarding the add/del boot option
//
// Input:	VOID
//
// Output:	VOID
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID DiscardAddDelBootOptions(VOID)
{
    UINTN count,i,j;
    BOOT_DATA *pBootData;
	UINT16 *AddOptionList=NULL,*DelOptionList=NULL;
	UINTN AddOptionListCount=0, DelOptionListCount=0;
    UINT16 *NewBootOrder = NULL, *CurrBootOrder = NULL;
	UINTN   size, tempsize = 0;

    //find no. of boot options
    count = 0;
    for(i=0;i<gBootOptionCount;i++)
    {
        if(!gBootData[i].bNewOption)
            count++;
        else
            AddOptionListCount++;
    }
    for(i=0;i<gDelOptionCount;i++)
    {
        if(!gDelBootData[i].bNewOption)
            count++;
        else
            DelOptionListCount++;
    }

    //Allocate for boot options
    pBootData = NULL;
    if(count)
        pBootData = EfiLibAllocateZeroPool(count * sizeof(BOOT_DATA));
    if(AddOptionListCount)
        AddOptionList=EfiLibAllocateZeroPool(AddOptionListCount * sizeof(UINT16));
    if(DelOptionListCount)
        DelOptionList=EfiLibAllocateZeroPool(DelOptionListCount * sizeof(UINT16));

    count = 0;
    AddOptionListCount=0;
    DelOptionListCount=0;

    //Copy old options
    for(i=0;i<gBootOptionCount;i++)
    {
        if(!gBootData[i].bNewOption)
        {
            MemCopy(pBootData+count, gBootData+i, sizeof(BOOT_DATA));
            count++;
        }
		else
		{ 	// Newly added option that need to removed.
			AddOptionList[AddOptionListCount++] = gBootData[i].Option;
		}
    }

    for(i=0;i<gDelOptionCount;i++)
    {
        if(!gDelBootData[i].bNewOption)
        {
            MemCopy(pBootData+count, gDelBootData+i, sizeof(BOOT_DATA));
            count++;

			// deleted option that need to added.
			DelOptionList[DelOptionListCount++] = gDelBootData[i].Option;
        }
    }

    MemFreePointer((VOID **) &gBootData);
    gBootData = pBootData;
    gBootOptionCount = count;

    MemFreePointer((VOID **) &gDelBootData);
    gDelOptionCount = 0;

// EIP 32445
// Update BootOrderVar Cache after discarding the changes.
// If newly add/Del option discorded.
	if(AddOptionListCount || DelOptionListCount)
	{
        CurrBootOrder = VarGetVariable(VARIABLE_ID_BOOT_ORDER, &size);
        NewBootOrder = EfiLibAllocateZeroPool((gBootOptionCount) * sizeof(UINT16));
		count = size/2;

		// Defaults might be load Move the disabled boot option to the end
        for(j=0;j<count;j++)
		{
			if(DISABLED_BOOT_OPTION == CurrBootOrder[j])
			{
				if (size < ((j+1)*sizeof(UINT16))) //EIP-131549
					tempsize = ((j+1)*sizeof(UINT16)) - size;
				else
					tempsize = size - ((j+1)*sizeof(UINT16));

				MemCopy(&CurrBootOrder[j], &CurrBootOrder[j+1], tempsize);
				size-=sizeof(UINT16);
			}
		}

		// remove the Newly added boot options
		count = size/2;
        for(i=0;i<AddOptionListCount;i++)
		{
	        for(j=0;j<count;j++)
			{
				if(CurrBootOrder[j] == AddOptionList[i])
				{					
					if (size < ((j+1)*sizeof(UINT16))) //EIP-131549
						tempsize = ((j+1)*sizeof(UINT16)) - size;
					else
						tempsize = size - ((j+1)*sizeof(UINT16));

					MemCopy(&CurrBootOrder[j], &CurrBootOrder[j+1], tempsize);
					size-=sizeof(UINT16);
				}
			}
		}
		count = size/2;
		// Add the DelOptions
		MemCopy(NewBootOrder, CurrBootOrder, size);
		MemCopy(&NewBootOrder[count],DelOptionList,DelOptionListCount*sizeof(UINT16) );
		
		// Make the remailing options as disabled.
		for(i=count+DelOptionListCount;i<gBootOptionCount;i++)
            NewBootOrder[i] = DISABLED_BOOT_OPTION;

        MemFreePointer((VOID **) &CurrBootOrder);
        MemFreePointer((VOID **) &DelOptionList);
        MemFreePointer((VOID **) &AddOptionList);

        //Update boot manager vars in memory
        //1. TSE Boot order
        MemFreePointer((VOID **) &gVariableList[VARIABLE_ID_BOOT_ORDER].Buffer);
		if (gLoadOptionHidden)
		{
			FixHiddenOptions (BOOT_ORDER_OPTION, &NewBootOrder, gBootOptionCount);
		}
		_DisableRestorePrevOptions (BOOT_ORDER_OPTION, &NewBootOrder, gBootOptionCount);			//Disable options after discarding changes to active so fixed it
        gVariableList[VARIABLE_ID_BOOT_ORDER].Buffer = (UINT8 *)NewBootOrder;
        gVariableList[VARIABLE_ID_BOOT_ORDER].Size = gBootOptionCount * sizeof(UINT16);
	}
}

//EIP70421 & 70422 Support for driver order
//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	DiscardAddDelDriverOptions
//
// Description:	Function to discarding the add/del driver option
//
// Input:	VOID
//
// Output:	VOID
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID DiscardAddDelDriverOptions(VOID)
{
	UINTN count,i,j;
    BOOT_DATA *pDriverData;
	UINT16 *AddOptionList=NULL,*DelOptionList=NULL;
	UINTN AddOptionListCount=0, DelOptionListCount=0;
   UINT16 *NewDriverOrder = NULL, *CurrDriverOrder = NULL;
	UINTN   size = 0, tempsize = 0;

    //find no. of boot options
    count = 0;
    for(i=0;i<gDriverOptionCount;i++)
    {
        if(!gDriverData[i].bNewOption)
            count++;
        else
            AddOptionListCount++;
    }
    for(i=0;i<gDriverDelOptionCount;i++)
    {
        if(!gDelDriverData[i].bNewOption)
            count++;
        else
            DelOptionListCount++;
    }

    //Allocate for boot options
    pDriverData = NULL;
    if(count)
        pDriverData = EfiLibAllocateZeroPool(count * sizeof(BOOT_DATA));
    if(AddOptionListCount)
        AddOptionList=EfiLibAllocateZeroPool(AddOptionListCount * sizeof(UINT16));
    if(DelOptionListCount)
        DelOptionList=EfiLibAllocateZeroPool(DelOptionListCount * sizeof(UINT16));

    count = 0;
    AddOptionListCount=0;
    DelOptionListCount=0;

    //Copy old options
    for(i=0;i<gDriverOptionCount;i++)
    {
        if(!gDriverData[i].bNewOption)
        {
            MemCopy(pDriverData+count, gDriverData+i, sizeof(BOOT_DATA));
            count++;
        }
		else
		{ 	// Newly added option that need to removed.
			AddOptionList[AddOptionListCount++] = gDriverData[i].Option;
		}
    }

    for(i=0;i<gDriverDelOptionCount;i++)
    {
        if(!gDelDriverData[i].bNewOption)
        {
            MemCopy(pDriverData+count, gDelDriverData+i, sizeof(BOOT_DATA));
            count++;

			// deleted option that need to added.
			DelOptionList[DelOptionListCount++] = gDelDriverData[i].Option;
        }
    }

    MemFreePointer((VOID **) &gDriverData);
    gDriverData = pDriverData;
    gDriverOptionCount = count;

    MemFreePointer((VOID **) &gDelDriverData);
    gDriverDelOptionCount = 0;

// Update DriverOrderVar Cache after discarding the changes.
// If newly add/Del option discorded.
	if(AddOptionListCount || DelOptionListCount)
	{
        CurrDriverOrder = VarGetVariable(VARIABLE_ID_DRIVER_ORDER, &size);
        NewDriverOrder = EfiLibAllocateZeroPool((gDriverOptionCount) * sizeof(UINT16));
		count = size/2;

		// Defaults might be load Move the disabled driver option to the end
        for(j=0;j<count;j++)
		{
			if(DISABLED_BOOT_OPTION == CurrDriverOrder[j])
			{
				if (size > ((j+1)*sizeof(UINT16))) //EIP-131549
					tempsize = size - ((j+1)*sizeof(UINT16));
				else
					tempsize = ((j+1)*sizeof(UINT16)) - size;

				MemCopy(&CurrDriverOrder[j], &CurrDriverOrder[j+1], tempsize );
				size-=sizeof(UINT16);
			}
		}

		// remove the Newly added driver options
		count = size/2;
        for(i=0;i<AddOptionListCount;i++)
		{
	        for(j=0;j<count;j++)
			{
				if(CurrDriverOrder[j] == AddOptionList[i])
				{
					if ((UINTN)size >= ((j+1)*sizeof (UINT16)) )		//Check added bcoz, If only added driver presents and loading defaults will lead to crash
					{
						if (size > ((j+1)*sizeof(UINT16))) //EIP-131549
							tempsize = size - ((j+1)*sizeof(UINT16));
						else
							tempsize = ((j+1)*sizeof(UINT16)) - size;

						MemCopy (&CurrDriverOrder [j], &CurrDriverOrder[j+1], tempsize );
						size-=sizeof(UINT16);
					}
				}
			}
		}

		count = size/2;
		// Add the DelOptions
		MemCopy(NewDriverOrder, CurrDriverOrder, size);
		MemCopy(&NewDriverOrder[count],DelOptionList,DelOptionListCount*sizeof(UINT16) );
		
		// Make the remaining options as disabled.
		for(i=count+DelOptionListCount;i<gDriverOptionCount;i++)
            NewDriverOrder[i] = DISABLED_BOOT_OPTION;

        MemFreePointer((VOID **) &CurrDriverOrder);
        MemFreePointer((VOID **) &DelOptionList);
        MemFreePointer((VOID **) &AddOptionList);

        //Update driver manager vars in memory
        //1. TSE Driver Order
        MemFreePointer((VOID **) &gVariableList[VARIABLE_ID_DRIVER_ORDER].Buffer);
		if (gLoadOptionHidden)
		{
			FixHiddenOptions (DRIVER_ORDER_OPTION, &NewDriverOrder, gDriverOptionCount);
		}
		_DisableRestorePrevOptions (DRIVER_ORDER_OPTION, &NewDriverOrder, gDriverOptionCount);
        gVariableList[VARIABLE_ID_DRIVER_ORDER].Buffer = (UINT8 *)NewDriverOrder;
        gVariableList[VARIABLE_ID_DRIVER_ORDER].Size = gDriverOptionCount * sizeof(UINT16);
	}
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	SaveAddDelBootOptions
//
// Description:	function to save the added/deleted boot option 
//
// Input:	VOID
//
// Output:	VOID
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID SaveAddDelBootOptions(VOID)
{
	UINTN i,OptimalIndex,FailsafeIndex,size;
	UINT16 dpLength,*pNewOptimal, *pOldOptimal, *pNewFailsafe, *pOldFailsafe;
	BOOT_OPTION *pOption;
	CHAR16 *varName = L"BootXXXX";
	UINT16 BootCountVal;
	
	//Old Boot order defaults are not valid any more. Form the new
	//defaults by removing deleted options and adding the new options at the end.
	pNewOptimal = EfiLibAllocateZeroPool( gBootOptionCount * sizeof(UINT16) );
	pNewFailsafe = EfiLibAllocateZeroPool( gBootOptionCount * sizeof(UINT16) );
	pOldOptimal = (UINT16 *)gOptimalDefaults[ VARIABLE_ID_BOOT_ORDER ].Buffer;
	pOldFailsafe = (UINT16 *)gFailsafeDefaults[ VARIABLE_ID_BOOT_ORDER ].Buffer;
	size = gOptimalDefaults[ VARIABLE_ID_BOOT_ORDER ].Size;
	OptimalIndex = FailsafeIndex = 0;
	
	//Add existing options first
	for(i=0;i<size/sizeof(UINT16);i++)
	{
		if(BootGetBootData(pOldOptimal[i]))
		{
			pNewOptimal[OptimalIndex] = pOldOptimal[i];
			OptimalIndex++;
		}
		if(BootGetBootData(pOldFailsafe[i]))
		{
			pNewFailsafe[FailsafeIndex] = pOldFailsafe[i];
			FailsafeIndex++;
		}
	}
	//Save New boot options
	for(i=0;i<gBootOptionCount;i++)
	{
		if(gBootData[i].bNewOption)
		{
			dpLength = (UINT16)EfiDevicePathSize( gBootData[i].DevicePath );
			size = sizeof(BOOT_OPTION) + sizeof(CHAR16)*EfiStrLen(gBootData[i].Name) + dpLength;
			pOption = EfiLibAllocateZeroPool( size );
			pOption->Active = gBootData[i].Active;
			pOption->PathLength = dpLength;
			EfiStrCpy( pOption->Name, gBootData[i].Name );
			MemCopy( (UINT8 *)pOption + size - dpLength, gBootData[i].DevicePath, dpLength );
	
			SPrint( varName, sizeof(CHAR16) * (EfiStrLen( varName )+1), gBootFormarSpecifier, gBootData[i].Option );
			VarSetNvramName( varName,
				&gEfiGlobalVariableGuid,
				EFI_VARIABLE_BOOTSERVICE_ACCESS | EFI_VARIABLE_RUNTIME_ACCESS | EFI_VARIABLE_NON_VOLATILE,
				pOption,
				size );
	
			gBootData[i].bNewOption = 0;
	
			//Append this option in defaults
			pNewOptimal[OptimalIndex] = gBootData[i].Option;
			pNewFailsafe[FailsafeIndex] = gBootData[i].Option;
			OptimalIndex++;
			FailsafeIndex++;
		}
	}
	
	//Put new defaults in global default repository
   //If Default order is not found in first time then will take current order.
   //If any boot options added after that then new boot option always follow the first saved optimized buffer
   //Removed EIP81581 fixes All the time changing the default buffer is not good
	if (0 == gOptimalDefaults [VARIABLE_ID_BOOT_ORDER].Size)		//EIP79956 Defaults not loading properly
	{
		UINT8 *pOptWithOutDefaultBootOrder = EfiLibAllocateZeroPool (gVariableList [VARIABLE_ID_BOOT_ORDER].Size);
		if (NULL != pOptWithOutDefaultBootOrder)
		{
			MemCopy (pOptWithOutDefaultBootOrder, gVariableList [VARIABLE_ID_BOOT_ORDER].Buffer, gVariableList [VARIABLE_ID_BOOT_ORDER].Size);
			gOptimalDefaults [VARIABLE_ID_BOOT_ORDER].Buffer = pOptWithOutDefaultBootOrder;
			gOptimalDefaults [VARIABLE_ID_BOOT_ORDER].Size = gVariableList [VARIABLE_ID_BOOT_ORDER].Size;
		}
	}
	else
	{		 	 
		MemFreePointer( (VOID **) &gOptimalDefaults[ VARIABLE_ID_BOOT_ORDER ].Buffer );
		gOptimalDefaults[ VARIABLE_ID_BOOT_ORDER ].Buffer = (UINT8 *)pNewOptimal;
		gOptimalDefaults[ VARIABLE_ID_BOOT_ORDER ].Size = OptimalIndex * sizeof(UINT16);
	}

	MemFreePointer( (VOID **) &gFailsafeDefaults[ VARIABLE_ID_BOOT_ORDER ].Buffer );
	gFailsafeDefaults[ VARIABLE_ID_BOOT_ORDER ].Buffer = (UINT8 *)pNewFailsafe;
	gFailsafeDefaults[ VARIABLE_ID_BOOT_ORDER ].Size = FailsafeIndex * sizeof(UINT16);
	
	//Delete removed options
	for(i=0;i<gDelOptionCount;i++)
	{
		if(!gDelBootData[i].bNewOption)
		{
			SPrint( varName, sizeof(CHAR16) * (EfiStrLen( varName )+1), gBootFormarSpecifier, gDelBootData[i].Option );
			VarSetNvramName( varName,
				&gEfiGlobalVariableGuid,
				EFI_VARIABLE_BOOTSERVICE_ACCESS | EFI_VARIABLE_RUNTIME_ACCESS | EFI_VARIABLE_NON_VOLATILE,
				varName,
				0);
		}
	}
	MemFreePointer((VOID **)&gDelBootData);
	gDelOptionCount = 0;
	
	//Update default value for Boot Manager and Boot Now count
	BootCountVal = (UINT16) gBootOptionCount;
	_VarGetSetValue (VAR_COMMAND_SET_VALUE, gOptimalDefaults, VARIABLE_ID_BOOT_MANAGER, 0, sizeof(UINT16), (VOID *)(&BootCountVal));
	_VarGetSetValue (VAR_COMMAND_SET_VALUE, gFailsafeDefaults, VARIABLE_ID_BOOT_MANAGER, 0, sizeof(UINT16), (VOID *)(&BootCountVal));
	
	if (gShowAllBbsDev)
		BootCountVal = _BootSetBootNowCount ();
	
	_VarGetSetValue (VAR_COMMAND_SET_VALUE, gOptimalDefaults, VARIABLE_ID_BOOT_NOW, 0, sizeof(UINT16), (VOID *)(&BootCountVal));
	_VarGetSetValue (VAR_COMMAND_SET_VALUE, gFailsafeDefaults, VARIABLE_ID_BOOT_NOW, 0, sizeof(UINT16), (VOID *)(&BootCountVal));
}

//EIP70421 & 70422  Support for driver order
//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	SaveAddDelDriverOptions
//
// Description:	Function to save the added/deleted Driver option 
//
// Input:	VOID
//
// Output:	VOID
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID SaveAddDelDriverOptions(VOID)
{
	UINTN i,OptimalIndex,FailsafeIndex,size;
	UINT16 dpLength,*pNewOptimal, *pOldOptimal, *pNewFailsafe, *pOldFailsafe;
	BOOT_OPTION *pOption;
	CHAR16 *varName = L"DriverXXXX";
	UINT16 DriverCountVal;
	
	//Old Driver order defaults are not valid any more. Form the new
	//defaults by removing deleted options and adding the new options at the end.
	pNewOptimal = EfiLibAllocateZeroPool( gDriverOptionCount * sizeof(UINT16) );
	pNewFailsafe = EfiLibAllocateZeroPool( gDriverOptionCount * sizeof(UINT16) );
	pOldOptimal = (UINT16 *)gOptimalDefaults[ VARIABLE_ID_DRIVER_ORDER ].Buffer;
	pOldFailsafe = (UINT16 *)gFailsafeDefaults[ VARIABLE_ID_DRIVER_ORDER ].Buffer;
	size = gOptimalDefaults[ VARIABLE_ID_DRIVER_ORDER ].Size;
	OptimalIndex = FailsafeIndex = 0;
	
	//Add existing options first
	for(i=0;i<size/sizeof(UINT16);i++)
	{
		if (DriverGetDriverData (pOldOptimal [i]))
		{
			pNewOptimal[OptimalIndex] = pOldOptimal[i];
			OptimalIndex++;
		}
		if(DriverGetDriverData (pOldFailsafe[i]))
		{
			pNewFailsafe[FailsafeIndex] = pOldFailsafe[i];
			FailsafeIndex++;
		}
	}
	//Save New driver options
	for(i=0;i<gDriverOptionCount;i++)
	{
		if(gDriverData[i].bNewOption)
		{
			dpLength = (UINT16)EfiDevicePathSize( gDriverData[i].DevicePath );
			size = sizeof(BOOT_OPTION) + sizeof(CHAR16)*EfiStrLen(gDriverData[i].Name) + dpLength;
			pOption = EfiLibAllocateZeroPool( size );
			pOption->Active = gDriverData[i].Active;
			pOption->PathLength = dpLength;
			EfiStrCpy( pOption->Name, gDriverData[i].Name );
			MemCopy( (UINT8 *)pOption + size - dpLength, gDriverData[i].DevicePath, dpLength );
	
			SPrint( varName, sizeof(CHAR16) * (EfiStrLen( varName )+1), gDriverFormarSpecifier, gDriverData[i].Option );
				VarSetNvramName( varName,
				&gEfiGlobalVariableGuid,
				EFI_VARIABLE_BOOTSERVICE_ACCESS | EFI_VARIABLE_RUNTIME_ACCESS | EFI_VARIABLE_NON_VOLATILE,
				pOption,
				size );
	
			gDriverData[i].bNewOption = 0;
			//Append this option in defaults
			pNewOptimal[OptimalIndex] = gDriverData[i].Option;
			pNewFailsafe[FailsafeIndex] = gDriverData[i].Option;
			OptimalIndex++;
			FailsafeIndex++;
		}
	}
	
	//Put new defaults in global default repository
   //Default order is not found in first time then will take current order.
   //If any driver options added after that then new driver option always follow the first saved optimized buffer
   //Removed EIP81581 fixes All the time changing the default buffer is not good
	if (0 == gOptimalDefaults [VARIABLE_ID_DRIVER_ORDER].Size)
	{
		UINT8 *pOptWithOutDefaultDriverOrder = EfiLibAllocateZeroPool (gVariableList [VARIABLE_ID_DRIVER_ORDER].Size);
		if (NULL != pOptWithOutDefaultDriverOrder)
		{
			MemCopy (pOptWithOutDefaultDriverOrder, gVariableList [VARIABLE_ID_DRIVER_ORDER].Buffer, gVariableList [VARIABLE_ID_DRIVER_ORDER].Size);
			gOptimalDefaults [VARIABLE_ID_DRIVER_ORDER].Buffer = pOptWithOutDefaultDriverOrder;
			gOptimalDefaults [VARIABLE_ID_DRIVER_ORDER].Size = gVariableList [VARIABLE_ID_DRIVER_ORDER].Size;
		}
	}
	else
	{
		MemFreePointer( (VOID **) &gOptimalDefaults[ VARIABLE_ID_DRIVER_ORDER ].Buffer );			
		gOptimalDefaults[ VARIABLE_ID_DRIVER_ORDER ].Buffer = (UINT8 *)pNewOptimal;
		gOptimalDefaults[ VARIABLE_ID_DRIVER_ORDER ].Size = OptimalIndex * sizeof(UINT16);
	}
	MemFreePointer( (VOID **) &gFailsafeDefaults[ VARIABLE_ID_DRIVER_ORDER ].Buffer );
	gFailsafeDefaults[ VARIABLE_ID_DRIVER_ORDER ].Buffer = (UINT8 *)pNewFailsafe;
	gFailsafeDefaults[ VARIABLE_ID_DRIVER_ORDER ].Size = FailsafeIndex * sizeof(UINT16);
	
	//Delete removed options
	for(i=0;i<gDriverDelOptionCount;i++)
	{
		if(!gDelDriverData[i].bNewOption)
		{
			SPrint( varName, sizeof(CHAR16) * (EfiStrLen( varName )+1), gDriverFormarSpecifier, gDelDriverData[i].Option );
			VarSetNvramName (varName,
				&gEfiGlobalVariableGuid,
				EFI_VARIABLE_BOOTSERVICE_ACCESS | EFI_VARIABLE_RUNTIME_ACCESS | EFI_VARIABLE_NON_VOLATILE,
				varName,
				0);
		}
	}
	MemFreePointer((VOID **)&gDelDriverData);
	gDriverDelOptionCount = 0;
	
	//Update default value for Driver Manager
	DriverCountVal = (UINT16) gDriverOptionCount;
	_VarGetSetValue( VAR_COMMAND_SET_VALUE, gOptimalDefaults, VARIABLE_ID_DRIVER_MANAGER, 0, sizeof(UINT16), (VOID *)(&DriverCountVal) );
	_VarGetSetValue( VAR_COMMAND_SET_VALUE, gFailsafeDefaults, VARIABLE_ID_DRIVER_MANAGER, 0, sizeof(UINT16), (VOID *)(&DriverCountVal) );
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	TSELiteFixAddBootOptionFileList
//
// Description:	Function to fix Add Boot Option file list
//
// Input:		CONTROL_DATA *ControlData
//
// Output:		VOID
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID TSELiteFixAddBootOptionFileList(CONTROL_DATA *ControlData)
{
	POPUPSEL_DATA *popupSel = (POPUPSEL_DATA *)ControlData;
	UINT16 i=0;
	if(gFsCount >= popupSel->ItemCount) // If the filesystem found
	{
		for(i=0;i<popupSel->ItemCount;i++)
		{
			popupSel->PtrTokens[i].Option = HiiAddString( popupSel->ControlData.ControlHandle, gFsList[i].FsId );
			popupSel->PtrTokens[i].Value = i;
		}
	}
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	TSELiteFixAddBootOptionFileList
//
// Description:	Function to fix Delete Boot option file list
//
// Input:		CONTROL_DATA *ControlData
//
// Output:		VOID
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID TSELiteFixDelBootOptionFileList(CONTROL_DATA *ControlData)
{
	POPUPSEL_DATA *popupSel = (POPUPSEL_DATA *)ControlData;
	UINT16 i=0;

	for(i=0;i<popupSel->ItemCount;i++)
	{
		if((UINT16)popupSel->PtrTokens[i].Value != 0xFFFF)
		{
			popupSel->PtrTokens[i].Value = gBootData[i-1].Option;
			popupSel->PtrTokens[i].Option = HiiAddString( popupSel->ControlData.ControlHandle, BootGetOptionName( &(gBootData[i-1]) ) );
		}
	}
}

/// EIP-41615: START - File Browser related functions for Add Boot Option..
//<AMI_PHDR_START>
//----------------------------------------------------------------------
// Procedure:   CleanFileTypes
//
// Description: Frees all allocated memory associated with the FILE_TYPE structure
//      and resets the InternalString current strings next available string token
//      to be the first dynamically added string
//
// Input:   FILE_TYPE **FileList - The array of FILE_TYPE structures found in 
//              a directory
//          UINTN *FileCount - pointer to the number of entries in the FileList
//
// Output:
//
// Returns:
//
//----------------------------------------------------------------------
//<AMI_PHDR_END>
VOID CleanFileTypes(FILE_TYPE **FileList, UINTN *FileCount)
{
    UINTN i;
    for(i = 0; i<*FileCount; i++) gBS->FreePool((*FileList)[i].Name);
    if(FileList!=NULL && (*FileList!=NULL) && (*FileCount>0)) gBS->FreePool(*FileList);
    if(FileList!=NULL) *FileList = NULL;
    *FileCount = 0;
}
//<AMI_PHDR_START>
//----------------------------------------------------------------------
// Procedure:   CheckDirectoryType
//
// Description: Checks if the EFI_FILE_INFO is a directory (and not the current directory)
//
// Input:   EFI_FILE_INFO *File
//
// Output:  
//
// Returns: BOOLEAN - TRUE - item is a directory, and not the current directory
//                    FALSE - item is not a directory, or is the current directory
//
//----------------------------------------------------------------------
//<AMI_PHDR_END>
BOOLEAN CheckDirectoryType(EFI_FILE_INFO *File)
{
    BOOLEAN Status = FALSE;

    if((File->Attribute & EFI_FILE_DIRECTORY) && (EfiStrCmp(File->FileName, L".") != 0)) {

        Status = TRUE;
    }

    return Status;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------
// Procedure:   CheckExtension
//
// Description: Check is the EFI_FILE_INFO has the same extension as the 
//      extension passed in the second parameter
//
// Input:   EFI_FILE_INFO *File - The file entry whose extension should be checked
//          CHAR16 *ExtensionEfi - the extension
//
// Output:
//
// Returns: BOOLEAN - TRUE - The extension matches
//                    FALSE - the extension does not match
//
//----------------------------------------------------------------------
//<AMI_PHDR_END>
BOOLEAN CheckExtension(EFI_FILE_INFO *File, CHAR16 *ExtensionEfi)
{
    BOOLEAN Status = FALSE;
    UINTN Length = EfiStrLen(File->FileName);

    if((File->Attribute & EFI_FILE_DIRECTORY) != EFI_FILE_DIRECTORY && Length > 3)
        if((((File->FileName[Length-1])&0xdf) == ((ExtensionEfi[2])&0xdf)) &&
           (((File->FileName[Length-2])&0xdf) == ((ExtensionEfi[1])&0xdf)) &&
           (((File->FileName[Length-3])&0xdf) == ((ExtensionEfi[0])&0xdf)))
            Status = TRUE;
    return Status;    
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------
// Procedure:   FindInsertionIndex
//
// Description: Finds the inded where directories items turn into file items
//
// Input:   FILE_TYPE *List - the current array of File Type structures
//          UINTN FileCount - the count of File Type structures in the array
//
// Output:
//
// Returns: the index to insert a new item
//
//----------------------------------------------------------------------
//<AMI_PHDR_END>
UINTN FindInsertionIndex(FILE_TYPE *List, UINTN FileCount)
{
    UINTN i = 0;
    
    if(FileCount <= 1) return 0;

    for(i = 1; i < (FileCount-1); i++)
    {
        if(List[i-1].Type != List[i].Type)
        break;
    }

    return i;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------
// Procedure:   AddFileTypeEntry
//
// Description: Creates a new entry in the FILE_TYPE array and adds the current File into
//      the array.
//
// Input:   FILE_TYPE **List - Array of FILE_TYPE structures alread found
//          UINTN *FileCount - number of entries in the FILE_TYPE array
//          EFI_FILE_INFO *FileInfo - file info of the file that should be added
//
// Output:
//
// Returns:
//
//----------------------------------------------------------------------
//<AMI_PHDR_END>
static VOID AddFileTypeEntry(FILE_TYPE **List, UINTN *FileCount, EFI_FILE_INFO *FileInfo)
{
    FILE_TYPE *NewList=NULL;
    UINTN Length;
    UINTN Index = 0;

    Length = (EfiStrLen(FileInfo->FileName)+3)*sizeof(CHAR16);

    // Allocate space for a new list entry plus all the previous list items
    NewList = EfiLibAllocateZeroPool(sizeof(FILE_TYPE)*(++(*FileCount)));
    if (NewList != NULL) 
    {
        // Clear the memory of the entire list
        MemSet(NewList, sizeof(FILE_TYPE)*(*FileCount), 0);
    
        // Copy the old entries (if there are any old entries to copy)
        if(*List != NULL) 
        {
            Index = FindInsertionIndex(*List, *FileCount);

            MemCopy(NewList, *List, sizeof(FILE_TYPE)*(Index));
            MemCopy(&(NewList[Index+1]), &((*List)[Index]), sizeof(FILE_TYPE)*((*FileCount)-Index-1));

            gBS->FreePool(*List);
        }

        // Store the type of this FILE_TYPE entry (non-zero is directory)
        NewList[Index].Type = ((FileInfo->Attribute) & EFI_FILE_DIRECTORY);

        // Store the size of the file
        NewList[Index].Size = (UINTN)FileInfo->FileSize;

        // Allocate space for the string
        NewList[Index].Name = EfiLibAllocateZeroPool (Length);
        if((NewList[Index].Name) != NULL )
        {
            // Clear the allocated memory
            MemSet(NewList[Index].Name, Length, 0);

            // Create either a Dir string or a File string for addition to the HiiDataBase
            if(NewList[Index].Type == EFI_FILE_DIRECTORY)
                 SPrint(NewList[Index].Name, (sizeof(CHAR16)*EfiStrLen(FileInfo->FileName)+1), L"<%s>", FileInfo->FileName);
            else
                 SPrint(NewList[Index].Name, (sizeof(CHAR16)*EfiStrLen(FileInfo->FileName)+1), L"%s", FileInfo->FileName);

            // Add the string to the HiiDataBase
            ///NewList[Index].Token = AddStringToHii(FileInfo->FileName, &gInternalStrings);	///Just by trying using the following line
            NewList[Index].Token = 	HiiAddString(gHiiHandle, NewList[Index].Name );

            // Clear the memory and create the string for the File Structure
            MemSet(NewList[Index].Name, Length, 0);
             SPrint(NewList[Index].Name, (sizeof(CHAR16)*EfiStrLen(FileInfo->FileName)+1), L"%s", FileInfo->FileName);            
        }
        *List = NewList;
    }
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------
// Procedure:   CreateFileList
//
// Description: Parse all the files in the current directory and add valid files to the
//      FILE_TYPE list and update the filecount
//
// Input:   EFI_FILE_PROTOCOL *FileProtocol - the current direcotry to parse
//
// Output:  FILE_TYPE **FileList - pointer in which to return the array of FileType items
//          UINTN *FileCount - the count of filetype items discovered
//
// Returns: EFI_STATUS
//
//----------------------------------------------------------------------
//<AMI_PHDR_END>
static EFI_STATUS CreateFileList(EFI_FILE_PROTOCOL *FileProtocol, FILE_TYPE **FileList, UINTN *FileCount)
{
    EFI_STATUS Status = EFI_SUCCESS;

    UINTN   BufferSize = 1;
    EFI_FILE_INFO *File = NULL;

    CHAR16 ExtensionEfi[] = L"EFI";

    // Continue parsing the directory until we no longer read valid files
    while(BufferSize != 0 && !EFI_ERROR(Status))
    {
        BufferSize = 0;
        Status = FileProtocol->Read(FileProtocol, &BufferSize, NULL);

        if(!EFI_ERROR(Status)) break;

        if(Status == EFI_BUFFER_TOO_SMALL)
        {
            File = EfiLibAllocateZeroPool (BufferSize);
            if(File != NULL) {
					MemSet(File, BufferSize, 0);
				}
        }

        Status = FileProtocol->Read(FileProtocol, &BufferSize, File);

        // Check if a valid file was read
        if(!EFI_ERROR(Status) && BufferSize != 0)
        {
            // check if the file read was a directory or a ".efi" extension
            if(CheckDirectoryType(File) || CheckExtension(File, ExtensionEfi))
            {
                // the file was valid, add it to the file list
                AddFileTypeEntry(FileList, FileCount, File);
            }
        }

        // free the space allocated for readin the file info structure
        gBS->FreePool(File);

        // set the pointer to null to prevent the chance of memory corruption
        File = NULL;
    }

    if(*FileCount == 0) Status = EFI_NOT_FOUND;

    return Status;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------
// Procedure:   DisplayFileListMenu
//
// Description: Display a menu of the FILE_TYPE items and return the selected item
//              in the Selection
//
// Input:   FILE_TYPE *FileList - List of FILE_TYPE items to display in the menu
//          UINTN FileCount - the number of FILE_TYPE items in the list
//
// Output:  UINT16 *Selection - The index of the selected FILE_TYPE item
//
// Returns:
//
//----------------------------------------------------------------------
//<AMI_PHDR_END>
static EFI_STATUS DisplayFileListMenu(FILE_TYPE *FileList, UINTN FileCount, UINT16 *Selection, UINT32 Variable)
{
    EFI_STATUS Status = EFI_SUCCESS;

    UINT16 i = 0;

    POSTMENU_TEMPLATE *List = NULL;

    // Check there are any files to display
    if(FileCount != 0 && FileList != NULL)
    {
        // allocate space for the POSTMENU_TEMPLATE items
        List = EfiLibAllocateZeroPool (sizeof(POSTMENU_TEMPLATE)*FileCount);
        if(List != NULL)
        {
            // Clear the memory allocated 
            MemSet(List, sizeof(POSTMENU_TEMPLATE)*FileCount, 0);

            // Add the STRING_REF tokens to the POSTMENU_TEMPLATE structures
            for(i = 0; i < FileCount; i++)
                List[i].ItemToken = FileList[i].Token;
        }

        // Call post manager to display the menu
        Status = mPostMgr->DisplayPostMenu(gHiiHandle,
                                            (VARIABLE_ID_ADD_BOOT_OPTION == Variable) ? STRING_TOKEN (STR_FILE_PATH) : STRING_TOKEN (STR_DRIVER_PATH),
                                            0,
                                            List,
                                            (UINT16)FileCount,
                                            Selection);
    }
    return Status;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------
// Procedure:   UpdateFilePathString
//
// Description: To create the File Path string based on the file selected.
//
// Input:   CHAR16 *FilePath  - Buffer to fill with the file path
//          CHAR16 * CurFile  - current file selected
//          UINT16 idx        - Index of the file in the current directory
//
// Output:  CHAR16 *FilePath - Updated File Path
//
// Returns:
//
//----------------------------------------------------------------------
//<AMI_PHDR_END>
VOID UpdateFilePathString(CHAR16 *FilePath, CHAR16 * CurFile, UINT16 idx)
{
	UINTN Length=0;

	if(EfiStrLen(FilePath))
	{
		if( idx==0 ) {
			if(EfiStrCmp(CurFile,L".."))  {
				EfiStrCat(FilePath,L"\\");
				EfiStrCat(FilePath,CurFile);
			}
			else {
				
				for ( Length = EfiStrLen(FilePath); ( Length!= 0 ) && (FilePath[Length-1] != L'\\') ; Length -- ); 
					if ( Length )
						FilePath[Length-1] = L'\0';
					else
						FilePath[Length] = L'\0';	
			}
		}
		else {
			EfiStrCat(FilePath,L"\\");
			EfiStrCat(FilePath,CurFile);
		}
	}
	else {
		EfiStrCpy(FilePath,L"\\");
		EfiStrCat(FilePath,CurFile);
		//EfiStrCpy(FilePath,CurFile);
	}
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------
// Procedure:   FileBrowserLaunchFileSystem
//
// Description: To select the File System for the new boot option with the help of file browser.
//
// Input:   VOID
//
// Output:  Selected File System Index
//
// Returns: EFI_STATUS
//
//----------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS FileBrowserLaunchFileSystem(UINT32 Variable)
{
    EFI_STATUS Status;
    UINTN Count = 0;
    UINT16 i = 0;

    EFI_GUID DevicePathGuid = EFI_DEVICE_PATH_PROTOCOL_GUID;
    EFI_DEVICE_PATH_PROTOCOL *Dp = NULL;

    POSTMENU_TEMPLATE *PossibleFileSystems = NULL;

    Status = gBS->LocateProtocol(&gAmiPostManagerProtocolGuid, NULL, &mPostMgr);
    if(EFI_ERROR(Status)) {
	return EFI_UNSUPPORTED;
    }
    // Locate all the simple file system devices in the system
    Status = gBS->LocateHandleBuffer(ByProtocol, &gSimpleFileSystemGuid, NULL, &Count, &gSmplFileSysHndlBuf);
    if(!EFI_ERROR(Status))
    {
        // allocate space to display all the simple file system devices
        PossibleFileSystems = EfiLibAllocateZeroPool (sizeof(POSTMENU_TEMPLATE)*Count);
        if(PossibleFileSystems != NULL)
        {
            // clear the allocated space
            MemSet(PossibleFileSystems, sizeof(POSTMENU_TEMPLATE)*Count, 0);
            for(i = 0; i < Count; i++)
            {
                // get the device path for each handle with a simple file system
                Status = gBS->HandleProtocol(gSmplFileSysHndlBuf[i], &DevicePathGuid, &Dp);
                if(!EFI_ERROR(Status))
                {
                    CHAR16 *Name = NULL;

                    // Get the name of the driver installed on the handle
                    // GetControllerName(gHandleBuffer[i],&Name);

                    Name = NULL;
                    Name = _DevicePathToStr(Dp);

                    // Add the name to the Hii Database
                    ///PossibleFileSystems[i].ItemToken = AddStringToHii(Name);
                    PossibleFileSystems[i].ItemToken = HiiAddString(gHiiHandle, Name ); 

                    PossibleFileSystems[i].Attribute = AMI_POSTMENU_ATTRIB_FOCUS;
                }
                else
                {
                    PossibleFileSystems[i].ItemToken = 0;
                    PossibleFileSystems[i].Attribute = AMI_POSTMENU_ATTRIB_HIDDEN;
                }
            }
            // Reset the item selected to be the first item
            gSelIdx = 0;

            // Display the post menu and wait for user input
            Status = mPostMgr->DisplayPostMenu(gHiiHandle,
                                                (Variable != 0xffff)? STRING_TOKEN(STR_FILE_SYSTEM) : STRING_TOKEN(STR_FILE_SYSTEM_TO_SAVE_IMG),//EIP-123432
                                                0,
                                                PossibleFileSystems,
                                                (UINT16)Count,
                                                &gSelIdx);


            // A valid item was selected by the user
            if(!EFI_ERROR(Status))
            {
                    gValidOption = TRUE;
            }
        }
    }
	
    else {
        ShowPostMsgBox( L"No Valid File System", L"No Valid File System Available", MSGBOX_TYPE_OK, NULL );//EIP:41615  To display Warning message when there is no file system connected.

    }
    // Free the allocated menu list space
    if(PossibleFileSystems != NULL) 
        gBS->FreePool(PossibleFileSystems);
	if(Variable == VARIABLE_ID_ADD_BOOT_OPTION)
	{
    // Set the File System Index for the new boot option added
 	   VarSetValue(VARIABLE_ID_ADD_BOOT_OPTION, STRUCT_OFFSET(NEW_BOOT_OPTION,SelFs), sizeof(UINT16), (VOID*)&gSelIdx);
	}
	if(Variable == VARIABLE_ID_ADD_DRIVER_OPTION)			//EIP70421 & 70422 Support for driver order
	{
		 VarSetValue(VARIABLE_ID_ADD_DRIVER_OPTION, STRUCT_OFFSET(NEW_DRIVER_OPTION,SelFs), sizeof(UINT16), (VOID*)&gSelIdx);
	}
    return Status;
}


//<AMI_PHDR_START>
//----------------------------------------------------------------------
// Procedure:   FileBrowserLaunchFilePath
//
// Description: To select the Boot file for the new boot option with the help of file browser.
//
// Input:   VOID
//
// Output:  File Path string
//
// Returns: EFI_STATUS
//
//----------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS FileBrowserLaunchFilePath(UINT32 Variable)
{
	EFI_STATUS Status;
	EFI_HANDLE Handle = 0;

	EFI_SIMPLE_FILE_SYSTEM_PROTOCOL *SimpleFs = NULL;
	EFI_FILE_PROTOCOL *NewFs = NULL;
	FILE_TYPE *FileList = NULL;
	UINTN FileCount = 0;
	UINT16 i = 0;
	//CHAR16 FilePath[120];
	CHAR16 *FilePath=NULL;
	UINTN filenamelength = 0, Length = 0;

	// Attempt to locate the post manager protocol
	Status = gBS->LocateProtocol(&gAmiPostManagerProtocolGuid, NULL, &mPostMgr);
	if(!EFI_ERROR(Status))
	{
		if( gValidOption == TRUE ) 
		{
			gValidOption = FALSE;

			// Get the simple file system protocol 
			Status = gBS->HandleProtocol(gSmplFileSysHndlBuf[gSelIdx], &gSimpleFileSystemGuid, &SimpleFs);
			if(!EFI_ERROR(Status))
			{
				// And open it and return the efi file protocol
				Status = SimpleFs->OpenVolume(SimpleFs, &gFs);
			}
		}
		else {
			return EFI_UNSUPPORTED;
		}

		// Free handle buffer space (auto allocated by the called function)
		if(gSmplFileSysHndlBuf != NULL) 
			gBS->FreePool(gSmplFileSysHndlBuf);

		// clean up the file list and strings used in getting the file system
		CleanFileTypes(&FileList, &FileCount);
	}

	//MemSet(FilePath, 120, 0);
	if ( NULL == FilePath ) //EIP-105725
	{
		FilePath = (CHAR16*)EfiLibAllocateZeroPool(sizeof(CHAR16));
	}

	while(!EFI_ERROR(Status) && gFs != NULL)
	{
		i = 0;

		// Create a list of the files in the current directory
		Status = CreateFileList(gFs, &FileList, &FileCount);
		if(!EFI_ERROR(Status))
		{
			// Display the list in a menu and allow the user to select
			Status = DisplayFileListMenu(FileList, FileCount, &i, Variable);
			if(!EFI_ERROR(Status))
			{
				// The user selected something, attempt to open it
				Status = gFs->Open(  gFs,
					&NewFs,
					FileList[i].Name,
					EFI_FILE_MODE_READ,
					0);

				// close the old file system protocol and set it to null
				gFs->Close(gFs);
				gFs = NULL;

				Length = EfiStrLen(FilePath) + 3; // adding 2 more character for \ and null termination
				filenamelength = EfiStrLen(FileList[i].Name);
				if ( NULL != FilePath )
				{
					////EIP-105725 Re-allocating based on filePath string length
					FilePath = MemReallocateZeroPool( FilePath, (Length * sizeof (CHAR16)), ( (Length * sizeof (CHAR16)) + (filenamelength * sizeof (CHAR16)) ) );
				}


				// Create the File Path based on the file selected
				UpdateFilePathString(FilePath, FileList[i].Name, i);

				// the newly selected item was opened correctly
				if(!EFI_ERROR(Status))
				{
					// check what type was opened
					if(FileList[i].Type != EFI_FILE_DIRECTORY)
					{
						// the file was read, close the file system protocol and set it to null
						NewFs->Close(NewFs);
						NewFs = NULL;

						//SPrint (FileName, 50, L"%s", FileList[i].Name);
						//ShowPostMsgBox( L"Selected Boot File Name", FileName, MSGBOX_TYPE_OK, &SelOpt );
					}
					gFs = NewFs;
				}
			}
		}

		if(FileCount <= 0) {
			ShowPostMsgBox( L"No Valid File", L"No Valid File Available in the Selected File System", MSGBOX_TYPE_OK, NULL );//EIP:41615 Warning message to show unavailability of the selected file
		}
		// clean the strings that were used and free allocated space
		CleanFileTypes(&FileList, &FileCount);

		if(Status == EFI_ABORTED) {
			return Status;//EIP:41615 Returning the status if its aborted.
		}
	}
	// Set the File path for the new boot option added.
	if(!EFI_ERROR(Status))
	{
		if (VARIABLE_ID_ADD_BOOT_OPTION == Variable)
			VarSetValue(VARIABLE_ID_ADD_BOOT_OPTION, STRUCT_OFFSET(NEW_BOOT_OPTION,Path), ((EfiStrLen(FilePath)+1)*sizeof(CHAR16)), FilePath);
		if (VARIABLE_ID_ADD_DRIVER_OPTION == Variable)				//EIP70421 & 70422 Support for driver order
			VarSetValue(VARIABLE_ID_ADD_DRIVER_OPTION, STRUCT_OFFSET(NEW_DRIVER_OPTION,DriverPath), ((EfiStrLen(FilePath)+1)*sizeof(CHAR16)), FilePath);
	}
	MemFreePointer((VOID**)&FilePath);
	return Status;
}
//EIP-41615: END.. 
//**********************************************************************
//**********************************************************************
//**                                                                  **
//**        (C)Copyright 1985-2014, American Megatrends, Inc.         **
//**                                                                  **
//**                       All Rights Reserved.                       **
//**                                                                  **
//**     5555 Oakbrook Pkwy, Building 200,Norcross, Georgia 30093     **
//**                                                                  **
//**                       Phone: (770)-246-8600                      **
//**                                                                  **
//**********************************************************************
//**********************************************************************
