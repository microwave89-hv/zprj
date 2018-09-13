//**********************************************************************
//**********************************************************************
//**                                                                  **
//**        (C)Copyright 1985-2012, American Megatrends, Inc.         **
//**                                                                  **
//**                       All Rights Reserved.                       **
//**                                                                  **
//**             6145-F Northbelt Pkwy, Norcross, GA 30071            **
//**                                                                  **
//**                       Phone: (770)-246-8600                      **
//**                                                                  **
//**********************************************************************
//**********************************************************************
//**********************************************************************
// $Archive: /Alaska/BIN/Modules/Template/FixedBootOrder Demo/Board/em/FixedBootOrder/FBOSetOrder.c $
//
// $Author: Walonli $
//
// $Revision: 31 $
//
// $Date: 3/26/15 10:50p $
//
//*****************************************************************//
//*****************************************************************//
// Revision History
// ----------------
// $Log: /Alaska/BIN/Modules/Template/FixedBootOrder Demo/Board/em/FixedBootOrder/FBOSetOrder.c $
// 
// 31    3/26/15 10:50p Walonli
// [TAG]  		EIP210628
// [Category]  	Improvement
// [Description]  	Fixed build error when USE_BCP_DEFAULT_PRIORITIES token
// enable.
// [Files]  		Board\em\FixedBootOrder\FBOSetOrder.c
// Board\em\FixedBootOrder\FixedBootOrderTSE.c
// FixedBootOrder.cif
// 
// 30    5/20/14 3:48a Klzhan
// [TAG]  		EIP167196
// [Category]  	Improvement
// [Description]  	Runtime attribute set for the some of the variable used
// by FixedBootOrder needs to be reviewed.
// [Files]  		Board\em\FixedBootOrder\FixedBootOrder.sdl
// Board\em\FixedBootOrder\FixedBootOrder.mak
// Board\em\FixedBootOrder\FBOSetOrder.c
// Board\em\FixedBootOrder\FixedBootOrderTSE.c
// Board\em\FixedBootOrder\FixedBootOrder.h
// Board\em\FixedBootOrder\FixedBootOrder.c
// Board\em\FixedBootOrder\FixedBootOrder.chm
// Board\em\FixedBootOrder\FixedBootOrderHII.c
// Board\em\FixedBootOrder\FixedBootOrderHII.h
// FixedBootOrder.cif
// 
// 29    4/16/14 5:16a Walonli
// 
// 28    4/15/14 2:26a Klzhan
// [TAG]  		EIP143078
// [Category]  	Improvement
// [Description]  	Set LOAD_OPTION_ACTIVE must be 0 when
// LOAD_OPTION_HIDDEN=1
// [Files]  		Board\em\FixedBootOrder\FixedBootOrder.sdl
// Board\em\FixedBootOrder\FixedBootOrder.mak
// Board\em\FixedBootOrder\FBOSetOrder.c
// Board\em\FixedBootOrder\FixedBootOrderTSE.c
// Board\em\FixedBootOrder\FixedBootOrder.h
// Board\em\FixedBootOrder\FixedBootOrder.c
// Board\em\FixedBootOrder\FixedBootOrder.chm
// Board\em\FixedBootOrder\FixedBootOrderHII.c
// Board\em\FixedBootOrder\FixedBootOrderHII.h
// FixedBootOrder.cif
// 
// 27    12/05/13 1:00a Klzhan
// [TAG]  		EIP143740
// [Category]  	Improvement
// [Description]  	1. Add a token for setting Windows To Go boot option to
// 1st priority.
// 2. Clean up code for windows to go 
// [Files]  		Board\em\FixedBootOrder\FixedBootOrder.sdl
// Board\em\FixedBootOrder\FBOSetOrder.c
// FixedBootOrder.cif
// 
// 26    10/21/13 5:41a Easonchen
// [TAG]  		EIP129692
// [Category]  	Bug Fix
// [Severity]  	Normal
// [Symptom]  	BBS Priorities become DISABLE when set ENABLE in Boot
// Option Priorities
// [RootCause]  	Variable "UefiDevOrder" not set "Disable" Mask.
// [Solution]  	Add "Disable" mask to variable "UefiDevOrder"
// [Files]  		FboSetOrder.c
// FixedBootOrderTse.c
// 
// 25    8/12/13 11:24p Easonchen
// [TAG]  		EIP128779
// [Category]  	Bug Fix
// [Severity]  	Minor
// [Symptom]  	UEFI USB CD/DVD Drive BBS Priotites displayed incorrectly
// [RootCause]  	Boot#### Boot Option record disable status. when group
// set to disable, group sub-menu display too.
// [Solution]  	Not change Boot#### disable status, Use variable
// "UefiDevOrder" record boot option disable status.
// [Files]  		FBOSetOrder.c
// 
// 24    8/12/13 4:17a Easonchen
// [TAG]  		N/A
// [Category]  	Improvement
// [Description]  	CppCheck error fix.
// [Files]  		FBOSetOrder.c
// 
// 23    5/28/13 5:25a Easonchen
// [TAG]  		EIP122146
// [Category]  	Improvement
// [Description]  	Support Dual mode default priority with tool AMIBCP. 
// [Files]
// FboSetOrder.c
// FixedBootOrder.c
// FixedBoorOrderTse.c
// DefaultFixedBootOrder.c
// DefaultFixedBootOrder.sd
// DefaultFixedBootOrder.uni
// 
// 22    4/22/13 11:04p Easonchen
// [TAG]  		EIP101213
// [Category]  	Improvement
// [Description]  	FixedBootOrder should match the BootOrder variable
// [Files]  		FboSetOrder.c
// FixedBootOrder.sdl
// 
// 21    4/09/13 9:07a Easonchen
// [TAG]  		EIP118170
// [Category]  	Bug Fix
// [Severity]  	Minor
// [Symptom]  	Windows Boot Manager will become disable on BBS Priorities
// when change Boot option filter
// [RootCause]  	when CsmOptOut module set legacy only, windows boot
// mangger boot option attribute become LOAD_OPTION_HIDDEN.
// [Solution]  	Check boot option attribute LOAD_OPTION_HIDDEN then don't
// disable boot option.
// [Files]  		FboSetOrder.c
// 
// 20    2/19/13 1:49a Easonchen
// [TAG]  		EIP114186
// [Category]  	Bug Fix
// [Severity]  	Important
// [Symptom]  	BSU Exit Page, Boot Override appears ¡§Unknown Device¡¨
// [RootCause]  	same boot option priority.
// [Solution]  	reassign boot option priority.
// [Files]  		FboSetOrder.c
// 
// 19    2/05/13 3:46a Easonchen
// [TAG]  		EIP107268
// [Category]  	New Feature
// [Description]  	Add support managing default boot order list using
// AMIBCP.
// [Files]  		
// FBOSetOrder.c
// FixedBootOrder.c
// FixedBootOrderTSE.c
// FixedBootOrder.sdl
// DefaultFixedBootOrder.sd
// DefaultFixedBootOrder.uni
// 
// 18    12/07/12 2:03a Easonchen
// [TAG]  		EIP107440
// [Category]  	Bug Fix
// [Severity]  	Important
// [Symptom]  	In UEFI mode, system should be only boot with EFI boot
// device.However, system will boot into DOS when enter "exit" in EFI
// shell.
// [RootCause]  	BootOption LOAD_OPTION_ACTIVE not setting.
// [Solution]  	Add BootOption LOAD_OPTION_ACTIVE set disable in UEFI
// mode.
// 
// 17    11/09/12 4:56a Easonchen
// [TAG]  		EIP99368
// [Category]  	Improvement
// [Description]  	WHCK - Boot from USB
// [Files]  		FBOSetOrder.c
// 
// 16    9/20/12 2:45a Easonchen
// [TAG]  		EIP100223
// [Category]  	Bug Fix
// [Severity]  	Minor
// [Symptom]  	does not recognize a USB device correctly.
// [RootCause]  	First plug USB CDROM boot option number is 0003, unplug
// and plug USB HDD boot option number is 0003 again.
// [Solution]  	Add device type check to filter.
// [Files]  		FBOSetOrder.c
// 
// 15    6/28/12 11:22a Easonchen
// Make a new FixedBootOrder module by utilizing 4.6.4.1 BDS
// functionality. 
// 
// 14    6/11/12 10:04a Easonchen
// [TAG]  		EIP92141
// [Category]  	Bug Fix
// [Severity]  	Minor
// [Symptom]  	build error with TSE 1227
// [RootCause]  	TSE EDKhelper.c change function name DivU64x32 to
// AmiTseDivU64x32.
// [Solution]  	Change to use function Div64
// [Files]  		FBOSetOrder.c
// 
// 12    5/02/12 2:49a Easonchen
// [TAG]  		EIP87316
// [Category]  	Improvement
// [Description]  	 FixedBootOrder Module needs support CsmOptOut Boot
// Filter UEFI Only. Set BBS Table BootPriority to BBS_IGNORE_ENTRY.
// [Files]  		FBOSetOrder.c
// 
// 11    6/17/11 3:44a Easonchen
// [TAG]  		EIP57950
// [Category]  	Improvement
// [Description]  	
// Replace BBS_TABLE BootPriority BBS_UNPRIORITIZED_ENTRY to
// BBS_DO_NOT_BOOT_FROM.
// 
// 10    4/14/11 4:01a Easonchen
// TAG: EIP35562
// In Core 4.6.4.1 or Last, Fixed boot variable name - hex digits should
// be in upper case
// 
// TAG: EIP54209
// Improvement: NetBootHotKey eModule Functionality with TSE 1210
// Verification Check
// [Description] 
// Check TSE gBootFlow status in function FBOCheckNormalBoot
// 
// TAG: EIP57727
// Improvement: It always increase one device while reboot in F12 (Boot
// device menu) even you only insert one HDD in it.
// [Description] 
// Modify function UpdateBootOrder() and AddUEFIDevice() to support
// 4.6.4.1
// 
// 9     3/31/11 2:03a Easonchen
// [TAG]  		EIP57272
// [Category]  	Improvement
// [Description]  	Check BootMode BOOT_ON_S4_RESUME and exit
// [Files]  		FBOSetOrder.c
// 
// 8     3/22/11 4:35a Easonchen
// [TAG]  		EIP51709
// [Category]  	Improvement
// [Description]  	1.Code is reformatted in accordance with the coding
// standards.
// 2.Remove file boot.vfr and setup.c, OEM need patch boot.vfr to remove
// original boot options.
// 
// 7     12/10/10 4:41a Easonchen
// Minor bug fix (EIP47257.2)
// 
// 6     11/12/10 2:57a Easonchen
// Add TSE ELINK ProcessProceedToBootNowHook.
// 
// TAG: EIP33514
// Improvement: The FixedBootOrder function caused the side effect
// -"AMT_TC010( IDE-Redirection).
// [Description] 
// Check variable "AmtBootOption" created, OemFixedBootOrder() don't
// change BBS_TABE Boot priority.
// 
// TAG: EIP47257
// Improvement: Load Default user define HDD order will lost.
// [Description] 
// Modified routine BbsChecksum(), If can't get hard disk serial number.
// use device name to make checksum.
// 
// 5     9/14/10 3:04a Easonchen
// TAG: EIP33514
// Improvement: Modify function FixedBootOrderSaveChange().
// [Description] 
// 1.Change BOOT#### LoadOption Bit Active status.
// 2.Update variable BootOrder after SaveChange.
// TAG: EIP33900
// Improvement: add function FixedBootOrderLoadedConfigDefaults() for TSE
// ELINK LoadedConfigDefaults().
// [Description]
// 1.Add function CreateDefaultDevOrder().
// 2.Call FixedBootOrderProtocol->load_default_string().
// TAG: EIP30275
// Improvement: Windows Boot Manager delete and restore.
// [Description]
// 1.Add function WindowsBootManager().
// TAG: EIP26947
// Improvement: Update variable "BootOrder" and "LegacyDevOrder"
// [Description]
// 1.Add function UpdateBootOrder().
// TAG: EIP22689
// Improvement: Support submenu function.
// 
// 4     3/31/10 6:54a Jameswang
// [Tag] EIP35944
// [Bug fix] Fixed USB CDROM will be analyzed as USB key with some CD
// medium(HD format)
// [Severity] Medium
// [Root cause] We only checked the USB device size to determined if it is
// a USB key, if USB CDROM has a medium that is emulated as a HDD / Floppy
// between 2MB and 64GB then it will also be determined as USB key.
// [Solution] Not only checks the size but also checks BBS types for HDD
// and Floppy, excludes CDROM.
// 
// 3     4/15/09 6:12a Jameswang
// TAG: EIP19998
// Improvement: New type:BOOT_USB_KEY is added and boot option can display
// the device name.
// [Description]
// 1. Added BOOT_USB_KEY type: 64GB > USB KEY!=USB floppy >= 2MB
// 2. SetPriorityForStringInit is added for pre-running the boot order for
// each boot options, so the FixedBootOrderStringInit can add device names
// to strings accordingly.
// 3. When FixedBootOrderStringInit signaling a protocol event,
// SetPriorityForStringInit::SetPriorityForStringInit will be called and
// gInitStrPhase=TRUE, the BBS_TABLE[].BootPriority = BOOT_XXXX enum value
// if the device is present.
// 4. FBORegisterEvent is linked to MinisetupDriverEntryHook and register
// a fake protocol so FixedBootOrderStringInit can signal it and callback
// to SetPriorityForStringInit accross the EDK.
// 
// 2     3/26/09 2:46a Jameswang
// All include use <> only without any path.  So that include files can be
// override by CIF2MAK "/x" option.
// All debug message add "\n".
// 
// 1     3/02/09 3:31a Jameswang
// Separate OemFixedBootOrder here to be linked with minisetup because we
// changed to use eLinks instead of using events.  We will not need to
// modify bbs.c using eLinks.
// 
//*****************************************************************//

//<AMI_FHDR_START>
//----------------------------------------------------------------------
//
// Name:	FBOSetOrder.c
//
// Description:	FixedBootOrder Boot Option control
//
//----------------------------------------------------------------------
//<AMI_FHDR_END>

//----------------------------------------------------------------------
// Include Files
//----------------------------------------------------------------------
#include <efi.h>
#include <amidxelib.h>
#include <protocol\blockio.h>

#include <BootOptions.h>
#include <Setup.h>
#include <setupdata.h>

#if CSM_SUPPORT
#include <Protocol\LegacyBios.h>
#include <protocol\LegacyBiosExt.h>
#endif

#include "FixedBootOrder.h"
typedef CHAR8 *VA_LIST;
#include "Core\EfiCommonLib.h"
#include "SetupStrTokens.h"
//---------------------------------------------------------------------------
// Global Variable declarations
//---------------------------------------------------------------------------
EFI_GUID gFixedBootOrderGuid = FIXED_BOOT_ORDER_GUID;
//---------------------------------------------------------------------------
// External functions
//---------------------------------------------------------------------------
EFI_HANDLE GetPhysicalBlockIoHandle(EFI_HANDLE BlockIoHandle);
UINT32 GetUefiBootOptionTag(IN EFI_DEVICE_PATH_PROTOCOL *Dp);
UINT16 GetDevicePortNumber(BBS_TABLE *BbsTable);
UINT32 FindPositionInTheGroupByBbsIndex(LEGACY_DEVICE_ORDER *Group, UINT16 BbsIndex);
//---------------------------------------------------------------------------
// Function Definitions
//---------------------------------------------------------------------------
VOID BuildFboLegacyDevOrder(VOID);
//---------------------------------------------------------------------------
// Type definitions
//---------------------------------------------------------------------------
#define DEFAULTS_GUID {0x4599d26f, 0x1a11, 0x49b8, 0xb9, 0x1f, 0x85, 0x87, 0x45, 0xcf, 0xf8, 0x24}
//---------------------------------------------------------------------------
// Constant and Variables declarations
//---------------------------------------------------------------------------
FBODevMap *pFBODualDevMap = NULL;
FBODevMap *pFBOLegacyDevMap = NULL;
FBODevMap *pFBOUefiDevMap = NULL;
UINT16 NewBootOptionNumber=0xffff;			//(EIP101213+)

UINT16 GetDevMapDataCount(FBODevMap *pFBODevMap)
{
	UINT16 count = 0;

	if( !pFBODevMap ) return 0;			//end of data

	do{
		if( pFBODevMap[count].DevType == 0 ) break;
		count++;
	}while(1);

	return count;
}

//<AMI_PHDR_START>
//---------------------------------------------------------------------------
//
// Procedure:	SearchDevMapByType
//
// Description:	 Search DevMap data index by device type.
//
// Input:
//  IN FBODevMap *pFBODevMap
//  IN UINT16 DevType
//
// Output:
//  OUT UINT16
//
// Modified: None
//      
// Referrals: None
//
// Notes: None	
//
//---------------------------------------------------------------------------
//<AMI_PHDR_END>
UINT16 SearchDevMapByType(FBODevMap *pFBODevMap, UINT16 DevType)
{
	UINT16 i=0;
	
	do{
		if(pFBODevMap[i].DevType == 0 ) break;	//end of data
		if(pFBODevMap[i].DevType == DevType)
			return i;
		i++;
	}while(1);

	return 0;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   FBO_FindTagPriority
//
// Description: For the passed Tag entry, return the correct boot priority based on 
//              the BootOptionTagPriorities global variable that is filled out
//              based on the SDL Token BOOT_OPTION_TAG_PRIORITIES.
//
// Input:       UINT16 Tag - one of the following items of the BOOT_OPTION_TAG enum:
//
// Output:      The index of this item in the FBODevMapData structure, which
//              also corresponds to the boot priority that should be assigned to this
//              class of device
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
UINT32 FBO_FindTagPriority(UINT16 Tag){
    UINT32 i=0;
    UINT16 DeviceMapCount;

    DeviceMapCount=GetDevMapDataCount( pFBOLegacyDevMap );

    for( i=0; i<DeviceMapCount; i++ )
	if( Tag == pFBOLegacyDevMap[i].DevType ) return i;

    return UNASSIGNED_HIGHEST_TAG;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   IsUSBkeyByHandle
//
// Description: determine the device type of the USBKey size.
//              
// Input:       EFI_HANDLE Handle
//
// Output:      BOOLEAN
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
BOOLEAN IsUSBkeyByHandle(EFI_HANDLE Handle)
{
	EFI_BLOCK_IO_PROTOCOL *BlkIo;
	UINT64 	SizeInMb;
	EFI_GUID gEfiBlockIoProtocolGuid = EFI_BLOCK_IO_PROTOCOL_GUID;


	if ( !EFI_ERROR( pBS->HandleProtocol(
               					Handle,
								&gEfiBlockIoProtocolGuid,
								&BlkIo)))
	{
		SizeInMb = MultU64x32(BlkIo->Media->LastBlock + 1, BlkIo->Media->BlockSize);
		SizeInMb = DivU64x32(SizeInMb, 1000000, NULL);
          
               	if (SizeInMb <= USBKEY_RANGE_SIZE ) 
               		return TRUE;
	}

	return FALSE;
}

#if CSM_SUPPORT
//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   CheckIsUSBkey
//
// Description: Using the passed BBS_TABLE entry pointer, determine the device
//              type of the USBKey
//
// Input:       BBS_TABLE *BbsEntry - pointer to a BBS_TABLE entry
//
// Output:      BOOLEAN
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
BOOLEAN CheckIsUSBkey(BBS_TABLE *BbsEntry)
{
	if( BbsEntry->DeviceType == BBS_HARDDISK )
		return IsUSBkeyByHandle( *(VOID**)(&BbsEntry->IBV1) );
	else
		return FALSE;
}
#endif

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   FBO_GetBbsEntryDeviceType
//
// Description: Using the passed BBS_TABLE entry pointer, determine the device
//              type of the associated device
//
// Input:       BBS_TABLE *BbsEntry - pointer to a BBS_TABLE entry
//
// Output:      UINT16 - device type
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
UINT16 FBO_GetBbsEntryDeviceType(BBS_TABLE *BbsEntry){

#ifdef CSM_SUPPORT
    UINT16 i;    	 
    UINT16 DeviceType = BbsEntry->DeviceType;
    BOOLEAN IsUSBDevice, IsUSBKey = FALSE;
    UINT16  Matched=0, OldMatched=0, DevMapIndex = 0xff;
    UINT16 DeviceMapCount=0;
    CHAR8 *AsciiNameStr;
     
    IsUSBDevice = (BbsEntry->Class == 0xc) && (BbsEntry->SubClass == 0x3);
   
    if( IsUSBDevice )
	IsUSBKey = CheckIsUSBkey( BbsEntry );

#if BBS_NETWORK_DEVICE_TYPE_SUPPORT
    if (   BbsEntry->Class == PCI_CL_NETWORK
        && BbsEntry->DeviceType == BBS_BEV_DEVICE
    ) DeviceType = BBS_EMBED_NETWORK;
#endif

    //Name from BBS table
    AsciiNameStr = (CHAR8*)(UINTN)((BbsEntry->DescStringSegment<<4)
         			  + BbsEntry->DescStringOffset);

    TRACE((-1,"%s (IsUSBDevice=%d)(IsUSBKey=%d)\n", AsciiNameStr, IsUSBDevice, IsUSBKey));

    DeviceMapCount=GetDevMapDataCount( pFBOLegacyDevMap );
    for( i=0; i<DeviceMapCount; i++ )
    {
		Matched=1;
		if( pFBOLegacyDevMap[i].BBSType != DeviceType ) continue;

		if( IsUSBDevice && (pFBOLegacyDevMap[i].Attr & F_USB )) Matched++;
		if( !IsUSBDevice && !(pFBOLegacyDevMap[i].Attr & F_USB )) Matched++;
		if( IsUSBKey && (pFBOLegacyDevMap[i].Attr & F_USBKEY )) Matched++;
		if( !IsUSBKey && !(pFBOLegacyDevMap[i].Attr & F_USBKEY )) Matched++;
		
		if( pFBOLegacyDevMap[i].Port != 0xff )
			if( pFBOLegacyDevMap[i].Port == GetDevicePortNumber( BbsEntry ) )
				return pFBOLegacyDevMap[DevMapIndex].DevType;

		if( Matched > OldMatched )
		{
			OldMatched = Matched;
			DevMapIndex = i;
		}
    }

    if( DevMapIndex != 0xff )
		return pFBOLegacyDevMap[DevMapIndex].DevType;

    TRACE((-1,"FBODevMapData not found\n"));
    return BBS_UNKNOWN;
#else
    return 0;
#endif	//#ifdef CSM_SUPPORT

}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   BuildUEFIDevOrder
//
// Description: Go through the master boot option list and create
//              memory representation of the uefi dev order variable
//
// Input:       DLIST *BootOptionList - the master boot option list
//
// Output:      none
//
// Note: 
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID BuildUEFIDevOrder(
){
    EFI_STATUS Status;
    UINT16 i,j;
    DLINK *Link;
    BOOT_OPTION *Option;
    UINTN OldDvOrderSize=0;
    UEFI_DEVICE_ORDER *OldDevOrder=NULL, *OldDevOrder2=NULL, *DevOrder=NULL, *DevOrder2=NULL;
    EFI_GUID FixedBootOrderGuid = FIXED_BOOT_ORDER_GUID;
    UINT16 DeviceMapCount;
    UINT16 BootOrderFlag[128];

    pBS->SetMem( BootOrderFlag, 128, 0);

    Status = GetEfiVariable(L"UefiDevOrder", &FixedBootOrderGuid, NULL, &OldDvOrderSize, &OldDevOrder);
    TRACE((-1,"FBOSetOrder.c BuildUEFIDevOrder:: GetEfiVariable UefiDevOrder (%r)\n", Status));
    if( EFI_ERROR(Status) )
    {
		OldDvOrderSize = 0;
		OldDevOrder = NULL;
    }

    DevOrder2 = DevOrder = Malloc(512);
    if( DevOrder == NULL )
		return;

    DeviceMapCount=GetDevMapDataCount( pFBOUefiDevMap );
    for(i=0; i<DeviceMapCount;i++)
    {
		UINT16 DevType;
		DevType = pFBOUefiDevMap[i].DevType;
		if( DevType == 0 ) break;	//end of data
		DevOrder->Type = DevType;
		DevOrder->Length=2;

		j=0;
										//(EIP101213+)>
		//collect new UEFI device to first position of group.
		if(NewBootOptionNumber != 0xffff)
		{
			FOR_EACH_BOOT_OPTION(BootOptionList,Link,Option){
				if(Option->BootOptionNumber == NewBootOptionNumber)
				{
					if(GetUefiBootOptionTag(Option->FilePathList) == DevType)
					{
						DevOrder->Length += 2;
						DevOrder->Device[j] = Option->BootOptionNumber;
						BootOrderFlag[Option->BootOptionNumber]=0xffff;	//mask flag.
						if(!(Option->Attributes & LOAD_OPTION_ACTIVE))
							DevOrder->Device[j] |= 0xff00;
						j++;
						break;
					}
				}
			}
		}
										//<(EIP101213+)

		//------------------------------------------------------------------------------
		//Get Previous boot priority.
		for(  OldDevOrder2 = OldDevOrder
			;(UINT8*)OldDevOrder2<(UINT8*)OldDevOrder+OldDvOrderSize
			; OldDevOrder2 = (UEFI_DEVICE_ORDER*)((UINT8*)OldDevOrder2 + OldDevOrder2->Length + sizeof(OldDevOrder2->Type)) ) 
		{
			if( DevType != OldDevOrder2->Type ) continue;
		
			{
				UINT16 k;

				for(k=0;k<(OldDevOrder2->Length-2)/sizeof(UINT16);k++)
				{
			    	FOR_EACH_BOOT_OPTION(BootOptionList,Link,Option){

                        if( BootOrderFlag[Option->BootOptionNumber] ) continue;	//not zero? //(EIP129692)
						if(GetUefiBootOptionTag(Option->FilePathList) != DevType) continue;	//(EIP100223+)
						if(Option->BootOptionNumber == (OldDevOrder2->Device[k] & 0xff))
						{
							DevOrder->Length += 2;
							DevOrder->Device[j] = Option->BootOptionNumber;
							BootOrderFlag[Option->BootOptionNumber]=0xffff;	//mask flag.
							if(OldDevOrder2->Device[k] & 0xff00)                           //(EIP129692)
								DevOrder->Device[j] |= 0xff00;
							j++;
						}
					}
				}
			}
		}
		//------------------------------------------------------------------------------

		FOR_EACH_BOOT_OPTION(BootOptionList,Link,Option){
		
			if( IsLegacyBootOption(Option) || Option->GroupHeader) continue;
			if( BootOrderFlag[Option->BootOptionNumber] ) continue;	//not zero?

			if( GetUefiBootOptionTag(Option->FilePathList) == DevType )
			{
				DevOrder->Length += 2;
				DevOrder->Device[j] = Option->BootOptionNumber;
				if(!(Option->Attributes & LOAD_OPTION_ACTIVE))
					DevOrder->Device[j] |= 0xff00;	
				j++;
			}
   		}

		if( DevOrder->Length > 2)
        {                                                                         //(EIP129692+)>
		    //re-alignment, move all disable item to last.
            UINT16 DeviceCount;
		    DeviceCount=(DevOrder->Length-2)/sizeof(UINT16);
		    {
                UEFI_DEVICE_ORDER *NewOrder=Malloc(DevOrder->Length+sizeof(DevOrder->Type));
                if( NewOrder )
                {
                    UINT16 NewOrderCount=0;

                    NewOrder->Type=DevOrder->Type;
                    NewOrder->Length=DevOrder->Length;

                    for(j=0; j<DeviceCount; j++)
			        {
                        if(DevOrder->Device[j] & 0xff00) continue;
                        NewOrder->Device[NewOrderCount]=DevOrder->Device[j];
                        NewOrderCount++;
                    }

                    for(j=0; j<DeviceCount; j++)
                    {
                        if(!(DevOrder->Device[j] & 0xff00)) continue;
                        NewOrder->Device[NewOrderCount]=DevOrder->Device[j];
                        NewOrderCount++;
                    }
                    pBS->CopyMem( DevOrder, NewOrder, DevOrder->Length+sizeof(DevOrder->Type) );
                    pBS->FreePool(NewOrder);
                }
            }
			DevOrder = (UEFI_DEVICE_ORDER*)((UINT8*)DevOrder + DevOrder->Length + sizeof(DevOrder->Type));
        }
                                                                                  //<(EIP129692+)
    }

    {
		UINTN DevOrderSize;
		DevOrderSize = (UINT8*)DevOrder - (UINT8*)DevOrder2;
	
		if(DevOrderSize)
		{
			pRS->SetVariable(
				L"UefiDevOrder", &FixedBootOrderGuid,
				BS_NV_VARIABLE_ATTRIBUTES, DevOrderSize, DevOrder2);

			pRS->SetVariable(
				L"OldUefiDevOrder", &FixedBootOrderGuid,
				BS_NV_VARIABLE_ATTRIBUTES, DevOrderSize, DevOrder2);
		}
		else
		{
			pRS->SetVariable(
				L"UefiDevOrder", &FixedBootOrderGuid,
				0, 0, NULL);

			pRS->SetVariable(
				L"OldUefiDevOrder", &FixedBootOrderGuid,
				0, 0, NULL);
		}

    }

    pBS->FreePool( DevOrder2 );
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:   FBO_CompareTagThenBbsIndex
//
// Description: This function returns result of compairing two DLINK tags.
//
// Input:       
//  Link1 - pointer to the first tag for compare
//  Link1 - pointer to the second tag for compare
//
// Output:  INT32 - result of comparing. 
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
INT32 FBO_CompareTagThenBbsIndex( IN DLINK *Link1, IN DLINK *Link2 )
{
    BOOT_OPTION *Option1 = (BOOT_OPTION*)Link1;
    BOOT_OPTION *Option2 = (BOOT_OPTION*)Link2;
    
    // Compare Tags first
    if (Option1->Tag < Option2->Tag) 
        return -1;
    else if (Option1->Tag > Option2->Tag) 
        return 1;

    // Compare by BBS index
    if (Option1->BbsIndex < Option2->BbsIndex) 
        return -1;
    else if (Option1->BbsIndex > Option2->BbsIndex) 
        return 1;

    return 0;
}


//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   FBO_SetDefaultUEFIDevOrder
//
// Description: Go through the master boot option list and create
//              memory representation of the default uefi order variable
//
// Input:       DLIST *BootOptionList - the master boot option list
//
// Output:      none
//
// Note: 
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID FBO_SetDefaultUEFIDevOrder(
){
    UINT16 i,j;
    DLINK *Link;
    BOOT_OPTION *Option;
    UEFI_DEVICE_ORDER *DevOrder=NULL, *DevOrder2=NULL;
    EFI_GUID FixedBootOrderGuid = FIXED_BOOT_ORDER_GUID;
    UINT16 DeviceMapCount;

	DevOrder2 = DevOrder = Malloc(512);

   	if( DevOrder == NULL )
		return;

   	SortList(BootOptionList, FBO_CompareTagThenBbsIndex);

   	DeviceMapCount=GetDevMapDataCount( pFBOUefiDevMap );
   	for(i=0; i<DeviceMapCount;i++)
   	{
		UINT16 DevType;
		DevType = pFBOUefiDevMap[i].DevType;
		if( DevType == 0 ) break;	//end of data
		DevOrder->Type = DevType;
		DevOrder->Length=2;

		j=0;
   		FOR_EACH_BOOT_OPTION(BootOptionList,Link,Option){
		
			if ( IsLegacyBootOption(Option) || Option->GroupHeader) continue;

			if( GetUefiBootOptionTag(Option->FilePathList) == DevType )
			{
				DevOrder->Length += 2;
				DevOrder->Device[j] = Option->BootOptionNumber;

				j++;
			}
   		}

		//TRACE((-1,"DevType=%x DevOrder->Length=%x\n", DevType, DevOrder->Length));
		if( DevOrder->Length > 2)
			DevOrder = (UEFI_DEVICE_ORDER*)((UINT8*)DevOrder + DevOrder->Length + sizeof(DevOrder->Type));
   	}

   	{
		UINTN DevOrderSize;
		DevOrderSize = (UINT8*)DevOrder - (UINT8*)DevOrder2;
	
		if( DevOrderSize )
		{
			pRS->SetVariable(
				L"DefaultUefiDevOrder", &FixedBootOrderGuid,
				BS_NV_VARIABLE_ATTRIBUTES, DevOrderSize, DevOrder2);
		}
		else
		{
			pRS->SetVariable(
				L"DefaultUefiDevOrder", &FixedBootOrderGuid,
				0, 0, NULL);
		}

   	}

   	pBS->FreePool( DevOrder2 );
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   SetLegacyBootOptionPriority
//
// Description: Set legacy boot option list priority.
//            
// Input:       DeviceType - Legacy Device type
//		Priority - pointer of Priority(UINT32).
//
// Output:      none
//
// Note: 
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
SetLegacyBootOptionPriority(UINT16 DeviceType, UINT32 *Priority)
{
   	DLINK *Link;
   	BOOT_OPTION *Option;
	BBS_BBS_DEVICE_PATH *BbsDp;

	//Search Group Header
	FOR_EACH_BOOT_OPTION(BootOptionList,Link,Option){
		BbsDp = (BBS_BBS_DEVICE_PATH*)Option->FilePathList;
		if(BbsDp->DeviceType != DeviceType ) continue;
			if(!Option->GroupHeader) continue;

		Option->Priority=++(*Priority);
	        Option->Attributes&=~LOAD_OPTION_HIDDEN;
		Option->Attributes|=LOAD_OPTION_ACTIVE;

		TRACE((-1,"[FBOSetOrder.c]Legacy Option->Priority=%x Name=%S\n", Option->Priority, Option->Description));
//		(*Priority)++;
		break;
	}

	FOR_EACH_BOOT_OPTION(BootOptionList,Link,Option){
		if (!IsLegacyBootOption(Option)) continue;	//Is Uefi? continue;
		if(Option->GroupHeader) continue;

		BbsDp = (BBS_BBS_DEVICE_PATH*)Option->FilePathList;
		if(BbsDp->DeviceType != DeviceType ) continue;
		Option->Priority=++(*Priority);
//		Option->Attributes|=LOAD_OPTION_ACTIVE;
		TRACE((-1,"[FBOSetOrder.c]Legacy Option->Priority=%x Name=%S\n", Option->Priority, Option->Description));
	}
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   SetUefiBootOptionPriority
//
// Description: Set uefi boot option list priority.
//            
// Input:       DeviceType - Uefi Device type
//		Priority - pointer of Priority(UINT32).
//
// Output:      none
//
// Note: 
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
SetUefiBootOptionPriority(UINT16 DeviceType, UINT32 *Priority)
{
   	EFI_GUID FixedBootOrderGuid = FIXED_BOOT_ORDER_GUID;
   	UEFI_DEVICE_ORDER *DevOrder=NULL, *DevOrder2=NULL;
   	UINTN DevOrderSize=0;
   	DLINK *Link;
   	BOOT_OPTION *Option;
   	UINT16 j;

   	GetEfiVariable(L"UefiDevOrder", &FixedBootOrderGuid, NULL, &DevOrderSize, &DevOrder);

   	DevOrder2=DevOrder;    

   	for( DevOrder=DevOrder2 
         	;(UINT8*)DevOrder<(UINT8*)DevOrder2+DevOrderSize
         	; DevOrder = (UEFI_DEVICE_ORDER*)((UINT8*)DevOrder + DevOrder->Length + sizeof(DevOrder->Type)) ) 
   	{
		if( DeviceType != DevOrder->Type ) continue;	
		
		for(j=0; j<(DevOrder->Length-2)/sizeof(UINT16); j++)
		{
			TRACE((-1,"[FBOSetOrder.c]DevOrder->Device[%d]=%x\n", j, DevOrder->Device[j]));

   			FOR_EACH_BOOT_OPTION(BootOptionList,Link,Option){
				if(IsLegacyBootOption(Option)) continue;						
				if( Option->BootOptionNumber != (DevOrder->Device[j] & 0xff)) continue;

				if( DevOrder->Device[j] & 0xff00 )
					Option->Attributes&=~LOAD_OPTION_ACTIVE;	//Disable
				else
                {                                               //(EIP128779+)
					Option->Attributes|=LOAD_OPTION_ACTIVE;		//Enable
					Option->Priority=++(*Priority);             //(EIP128779+)
                }                                               //(EIP128779+)

				Option->Attributes&=~LOAD_OPTION_HIDDEN;
				TRACE((-1,"[FBOSetOrder.c]UEFI BootOptionNumber=%x Priority=%x Name=%S\n", Option->BootOptionNumber, Option->Priority, Option->Description));
				break;
			}
		}
	}

	if( DevOrder2 )
		pBS->FreePool( DevOrder2 );
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   FBO_UpdateBootListPriority
//
// Description: use setup data LegacyPriorities/UefiPriorities/DualPriorities
//	        ,set legacy/uefi boot option list priority.
//
// Input: None
//
// Output: None
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID FBO_UpdateBootListPriority()
{
	EFI_STATUS Status;
	EFI_GUID gSetupGuid=SETUP_GUID;
	SETUP_DATA *pSetupData=NULL;
	UINT32 SetupAttr;
	UINTN SetupSize=0;
	DLINK *Link;
   	BOOT_OPTION *Option;
	UINT16 i; //,j;
	UINT16 DeviceMapCount=0;
	UINT16 TypeIndex;
	UINT32 PreviousPriority=0;

//(EIP99368+)>>
  	FOR_EACH_BOOT_OPTION(BootOptionList,Link,Option){
		if (IsLegacyBootOption(Option)) continue;
		if(!Wcscmp(Option->Description,L"USB Entry for Windows To Go Logo Test"))
			return;
	}
//<<(EIP99368+)

	BuildUEFIDevOrder();

	Status = GetEfiVariable(L"Setup", &gSetupGuid, &SetupAttr, &SetupSize, &pSetupData);

	if (EFI_ERROR(Status)) return;

#if FBO_DUAL_MODE
	if(pSetupData->BootMode == 2)	//Is Dual boot mode?
	{
		//-----------------------------------------------------
		//Search Legacy Group Header and Set is disable
 		FOR_EACH_BOOT_OPTION(BootOptionList,Link,Option){
			if (IsLegacyBootOption(Option))												//(EIP114186+)
				Option->Priority=UNASSIGNED_HIGHEST_TAG;								//(EIP114186+)
			if(!Option->GroupHeader) continue;
		    Option->Attributes&=~LOAD_OPTION_ACTIVE;
            Option->Priority=LOWEST_BOOT_OPTION_PRIORITY;
		}
		//-----------------------------------------------------
		//Set All Uefi device Disable
  		FOR_EACH_BOOT_OPTION(BootOptionList,Link,Option){
			if (IsLegacyBootOption(Option)) continue;

			if(Option->Attributes & LOAD_OPTION_HIDDEN) continue;	//(EIP118170+)

			Option->Attributes&=~LOAD_OPTION_ACTIVE;	//Disable
            Option->Priority=LOWEST_BOOT_OPTION_PRIORITY;
		}
		//-----------------------------------------------------
		DeviceMapCount=GetDevMapDataCount( pFBODualDevMap );
    	for(i=0;i<DeviceMapCount;i++)
		{
			TypeIndex=pSetupData->DualPriorities[i];
			if( !pFBODualDevMap[TypeIndex].BBSType )		//0, Uefi device
			{
				TRACE((-1,"[FBOSetOrder.c]DualPriorities[%d] pFBODualDevMap[%d].DevType=%x\n", i, TypeIndex, pFBODualDevMap[TypeIndex].DevType));
				SetUefiBootOptionPriority( pFBODualDevMap[TypeIndex].DevType, &PreviousPriority );
			}
			else
			{
				if( pFBODualDevMap[TypeIndex].DevType == 0 ) continue;	//Disable?		//(EIP114186+)
				TRACE((-1,"[FBOSetOrder.c]DualPriorities[%d] pFBODualDevMap[%d].DevType=%x\n", i, TypeIndex, pFBODualDevMap[TypeIndex].DevType));
				SetLegacyBootOptionPriority( pFBODualDevMap[TypeIndex].DevType, &PreviousPriority );
			}
		}
	}
	else
#endif	
	if(pSetupData->BootMode == 1) 	//Is Uefi boot mode?
	{
		//-----------------------------------------------------
		//Set All device Disable
  		FOR_EACH_BOOT_OPTION(BootOptionList,Link,Option){
			if (IsLegacyBootOption(Option))			//(EIP107440)
				if(!Option->GroupHeader) continue;	//(EIP107440+)

			if(Option->Attributes & LOAD_OPTION_HIDDEN) continue;	//(EIP118170+)

			Option->Attributes&=~LOAD_OPTION_ACTIVE;	//Disable
			Option->Priority=LOWEST_BOOT_OPTION_PRIORITY;
		}
		//-----------------------------------------------------
		DeviceMapCount=GetDevMapDataCount( pFBOUefiDevMap );
    	for(i=0; i<DeviceMapCount;i++)
		{
			TypeIndex=pSetupData->UefiPriorities[i];
			
			TRACE((-1,"[FBOSetOrder.c]UefiPriorities[%d] pFBOUefiDevMap[TypeIndex].DevType=%x\n", i, pFBOUefiDevMap[TypeIndex].DevType));
			SetUefiBootOptionPriority( pFBOUefiDevMap[TypeIndex].DevType, &PreviousPriority );
		}

		//-----------------------------------------------------
		//Set Other UEFI device priority
  		FOR_EACH_BOOT_OPTION(BootOptionList,Link,Option){

			if (IsLegacyBootOption(Option) 
			    || (Option->Priority != LOWEST_BOOT_OPTION_PRIORITY) ) continue;

			Option->Priority=++PreviousPriority;
			TRACE((-1,"UEFI device Option->Priority=%x Name=%S\n", Option->Priority, Option->Description));
			
		}
		//-----------------------------------------------------

		//-----------------------------------------------------
		//Set Other Legacy device priority and hide
		FOR_EACH_BOOT_OPTION(BootOptionList,Link,Option){

			if (!IsLegacyBootOption(Option)) continue;
		
			Option->Priority=++PreviousPriority;
			Option->Attributes|=LOAD_OPTION_HIDDEN;
			TRACE((-1,"[FBOSetOrder.c]Legacy Option->Priority=%x Name=%S\n", Option->Priority, Option->Description));
		}
		//-----------------------------------------------------
	}
	else
	if(pSetupData->BootMode == 0)	//Is Legacy boot mode?
	{
		//-----------------------------------------------------
		//Search Legacy Group Header and Set is disable
 		FOR_EACH_BOOT_OPTION(BootOptionList,Link,Option){
			if (IsLegacyBootOption(Option))												//(EIP114186+)
				Option->Priority=UNASSIGNED_HIGHEST_TAG;								//(EIP114186+)
			if(!Option->GroupHeader) continue;
		        Option->Attributes&=~LOAD_OPTION_ACTIVE;
		}

		DeviceMapCount=GetDevMapDataCount( pFBOLegacyDevMap );
		TRACE((-1,"[FBOSetOrder.c] DeviceMapCount=%x\n", DeviceMapCount));
    	for(i=0; i<DeviceMapCount;i++)
		{
			TypeIndex=pSetupData->LegacyPriorities[i];
			if( pFBOLegacyDevMap[TypeIndex].DevType == 0 ) continue;	//Disable?		//(EIP114186+)
			SetLegacyBootOptionPriority( pFBOLegacyDevMap[TypeIndex].DevType, &PreviousPriority );
		}

		FOR_EACH_BOOT_OPTION(BootOptionList,Link,Option){
			if (IsLegacyBootOption(Option)) continue;
			Option->Priority=++PreviousPriority;
			Option->Attributes |= LOAD_OPTION_HIDDEN;
			TRACE((-1,"[FBOSetOrder.c]UEFI Option->Priority=%x Name=%S\n", Option->Priority, Option->Description));
		}
	}
    BuildFboLegacyDevOrder();

    //
    // Undesried boot options should be not able to boot (ACTIVE=0)
    // This code must not be executed before BuildFboLegacyDevOrder
    // in order to keep the FboLegacyDevOrder has the same disabled information as setup
    //
    FOR_EACH_BOOT_OPTION(BootOptionList, Link, Option)
    {
        UINT16 LegacyFlag = IsLegacyBootOption(Option);

        if (pSetupData->BootMode == 2  // Dual mode?
                || (pSetupData->BootMode == 0 && LegacyFlag)    // legacy mode and legacy option?
                || (pSetupData->BootMode == 1 && !LegacyFlag)   // UEFI mode and UEFI option?
           )
        {
            // option should be ACTIVE to boot and NOT HIDDEN for TSE
            Option->Attributes &= ~LOAD_OPTION_HIDDEN;  // clear HIDDEN for all legacy boot options
        }
        else
        {
            // undesried boot options for selected boot mode
            // HIDDEN for TSE not sees it
            // NOT ACTIVE for not booting from it
            Option->Attributes |= LOAD_OPTION_HIDDEN;   // HIDDEN
            Option->Attributes &= ~LOAD_OPTION_ACTIVE;  // Disable undesired UEFI boot options
        }
    }
	pBS->FreePool(pSetupData);

	DUMP_BOOT_OPTION_LIST(BootOptionList,"After UpdateBootListPriority");
}
//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:   BuildFboLegacyDevOrder
//
// Description: Build FboLegacyDevOrder variable from BootOptionList.
//              This variable should be set before we disable the undesried boot
//              options for selected boot mode.  So we can get the correct
//              BootOptionList.Attributes reflecting the selection of setup.
//
// Input:       None
//
// Output:      FboLegacyDevOrder variable updated
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

VOID BuildFboLegacyDevOrder()
{
#if CSM_SUPPORT
    UINTN DevOrderSize;
    LEGACY_DEVICE_ORDER *DevOrder, *DevOrderStart;
    LEGACY_DEVICE_ORDER *NewDevOrder, *NewDevOrderStart;
    UINT16 DeviceCount;
    UINT16 i, j;
    
    // return if no BootOption
    if(!BootOptionList->Size)
        return;
    
    SortList(BootOptionList, ComparePriorityThenBootOptionNumber);
    BuildLegacyDevOrderBuffer(&DevOrder, &DevOrderSize);

    DevOrderStart = DevOrder;
    //
    // Crerate the NewDevOrder from DevOrder for changing order
    //
    NewDevOrderStart = NewDevOrder = MallocZ(DevOrderSize);
    if (NewDevOrder == NULL)
    {
        pBS->FreePool(DevOrderStart);
        return;
    }
    pBS->CopyMem(NewDevOrder, DevOrder, DevOrderSize);

    //
    // We need to keep the disabled ones at last
    //
    for (; (UINT8*)NewDevOrder < (UINT8*)NewDevOrderStart + DevOrderSize;)
    {
        j = 0;
        DeviceCount = DEVORDER_COUNT(NewDevOrder);

        //
        // Save the enabled ones first
        //
        for (i = 0; i < DeviceCount; i++)
        {
            if (DevOrder->Device[i] & FBO_LEGACY_DISABLED_MASK)
            {
                continue;
            }
            NewDevOrder->Device[j++] = DevOrder->Device[i];
        }
        //
        // Save the disabled ones later
        //
        for (i = 0; i < DeviceCount; i++)
        {
            if (!(DevOrder->Device[i] & FBO_LEGACY_DISABLED_MASK))
            {
                continue;
            }
            NewDevOrder->Device[j++] = DevOrder->Device[i];
        }

        //
        // Next
        //
        NewDevOrder = (LEGACY_DEVICE_ORDER*)((UINT8*)NewDevOrder + NewDevOrder->Length + sizeof(NewDevOrder->Type));
        DevOrder = (LEGACY_DEVICE_ORDER*)((UINT8*)DevOrder + DevOrder->Length + sizeof(DevOrder->Type));
    }

    pRS->SetVariable(
        L"FboLegacyDevOrder", &gFixedBootOrderGuid,
        BS_NV_VARIABLE_ATTRIBUTES, DevOrderSize, NewDevOrderStart
    );

    pBS->FreePool(DevOrderStart);
    pBS->FreePool(NewDevOrderStart);
#endif  //#if CSM_SUPPORT
}
								//(EIP101213+)>
//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   FBO_AdjustWtgPriority()
//
// Description: First boot order of group, Change this gorup
//				uefi Priorities to Top position.
//	        
// Input: None
//
// Output: None
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
void FBO_AdjustWtgPriority()
{
	EFI_STATUS  Status;
	UINT16      *BootOrder = NULL;
	UINTN       BootOrderSize = 0; 
	UINT32      SetupAttr;
	UINTN       SetupSize = 0;
	SETUP_DATA  *pSetupData = NULL;
    DLINK       *Link;
    BOOT_OPTION *Option;
    EFI_GUID    gSetupGuid = SETUP_GUID;
    UINT16      i, TypeIndex;
    UINT16      DeviceMapCount = 0;
    BOOLEAN     UpdateSetup = FALSE, WindowsToGoFound = FALSE;

    Status = GetEfiVariable(L"Setup", &gSetupGuid, &SetupAttr, &SetupSize, &pSetupData);
    if (EFI_ERROR(Status)) 
        return;

    // Search for Windwos To Go Boot Option
    FOR_EACH_BOOT_OPTION(BootOptionList,Link,Option)
    {
        if (IsLegacyBootOption(Option)) 
            continue;

        // Found !!
        if(!Wcscmp(Option->Description,L"USB Entry for Windows To Go"))	//if WTG?
        {
            Status=GetEfiVariable(
                        L"BootOrder", 
                        &EfiVariableGuid, 
                        NULL, 
                        &BootOrderSize, 
                        &BootOrder);

            if(EFI_ERROR(Status))
			{
                pBS->FreePool( pSetupData );
                return;
			}

            // There are 2 Options in "Windows To Go Startup Options"
            // Choose Yes, Windows will set Windows to Go BootOption to Frist Priority in BootOrder.
            // Choose No,  User Need to change PC's Firmware Setting.
            // So, We Only handle the "Yes" Option

            if(BootOrder[0] != Option->BootOptionNumber)
            {
                pBS->FreePool( pSetupData );
                pBS->FreePool( BootOrder );
                return;
            }else
            {
                WindowsToGoFound = TRUE;
                break;
            }
        }
    }
    if(!WindowsToGoFound)
	{
		pBS->FreePool( pSetupData );
        return;
	}

#if FBO_DUAL_MODE
    TypeIndex = SearchDevMapByType( pFBODualDevMap,GetUefiBootOptionTag(Option->FilePathList));
    DeviceMapCount=GetDevMapDataCount( pFBODualDevMap );

    for(i=0;i<DeviceMapCount;i++)
    {
        if(TypeIndex == pSetupData->DualPriorities[i])
        {
            UINT16 j;
            UINT16 FirstPriority = pSetupData->DualPriorities[i];
						
            for(j=i;j>0;j--)
                pSetupData->DualPriorities[j] = pSetupData->DualPriorities[j-1];

            pSetupData->DualPriorities[0] = FirstPriority;
            UpdateSetup=TRUE;
            break;
        }
    }
#endif
    TypeIndex = SearchDevMapByType( pFBOUefiDevMap,GetUefiBootOptionTag(Option->FilePathList));
    DeviceMapCount = GetDevMapDataCount( pFBOUefiDevMap );
    for(i = 0 ; i < DeviceMapCount ; i++)
    {
        if(TypeIndex == pSetupData->UefiPriorities[i])
        {
            UINT16 j;
            UINT16 FirstPriority = pSetupData->UefiPriorities[i];
						
            for(j = i ; j > 0 ; j--)
                pSetupData->UefiPriorities[j] = pSetupData->UefiPriorities[j-1];

            pSetupData->UefiPriorities[0] = FirstPriority;
            UpdateSetup=TRUE;
            break;
        }
    }

    if(UpdateSetup)
        Status = pRS->SetVariable(L"Setup",&gSetupGuid, SetupAttr, SetupSize, pSetupData);

    pBS->FreePool( pSetupData );
    pBS->FreePool( BootOrder );

    return;
}


//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   FBO_AdjustPriority()
//
// Description: first boot order of group, Change this gorup
//				uefi and dual Priorities to Top position.
//	        
// Input: None
//
// Output: None
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
void FBO_AdjustPriority()
{
	FBO_AdjustWtgPriority();
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   FBO_Init
//
// Description: Initialize the module memory, and device map data.
//	       
// Input: None
//
// Output: None
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS FBO_Init(IN void)
{
	EFI_STATUS Status;
	EFI_GUID FixedBootOrderGuid=FIXED_BOOT_ORDER_GUID;
	EFI_FIXED_BOOT_ORDER_PROTOCOL *pFBO=NULL;
	EFI_GUID gSetupGuid=SETUP_GUID;
	SETUP_DATA *pSetupData=NULL;
	UINT32 SetupAttr;
	UINTN SetupSize=0;
	UINT16 i, DeviceMapCount;

	Status = pBS->LocateProtocol( &FixedBootOrderGuid, NULL, &pFBO );

	if(!EFI_ERROR(Status))
	{
		pFBOLegacyDevMap = pFBO->GetLegacyDevMap();
		pFBOUefiDevMap = pFBO->GetUefiDevMap();
#if FBO_DUAL_MODE
		pFBODualDevMap = pFBO->GetDualDevMap();
#endif
	}

	Status = GetEfiVariable(L"Setup", &gSetupGuid, &SetupAttr, &SetupSize, &pSetupData);
	if( !EFI_ERROR(Status) )
	{
		if( !pSetupData->FBO_Init )
		{
			pSetupData->FBO_Init=1;
                                            //(EIP107268+)>
#if USE_BCP_DEFAULT_PRIORITIES			
			DeviceMapCount=GetDevMapDataCount( pFBOLegacyDevMap );
			for( i=0; i<DeviceMapCount; i++ )
				pSetupData->LegacyPriorities[i]=pSetupData->BcpDefaultLegacyPriorities[i];

			DeviceMapCount=GetDevMapDataCount( pFBOUefiDevMap );
			for( i=0; i<DeviceMapCount; i++ )
				pSetupData->UefiPriorities[i]=pSetupData->BcpDefaultUefiPriorities[i];
                                            //(EIP122146+)>
#if FBO_DUAL_MODE
			DeviceMapCount=GetDevMapDataCount( pFBODualDevMap );
			for( i=0; i<DeviceMapCount; i++ )
				pSetupData->DualPriorities[i]=pSetupData->BcpDefaultDualPriorities[i];
#endif
                                            //<(EIP122146+)
#else										//<(EIP107268+)
			DeviceMapCount=GetDevMapDataCount( pFBOLegacyDevMap );
			for( i=0; i<DeviceMapCount; i++ )
				pSetupData->LegacyPriorities[i]=i;

			DeviceMapCount=GetDevMapDataCount( pFBOUefiDevMap );
			for( i=0; i<DeviceMapCount; i++ )
				pSetupData->UefiPriorities[i]=i;

#if FBO_DUAL_MODE
			DeviceMapCount=GetDevMapDataCount( pFBODualDevMap );	
			for( i=0; i<DeviceMapCount; i++ )
				pSetupData->DualPriorities[i]=i;
#endif

#endif  //#if USE_BCP_DEFAULT_PRIORITIES    //(EIP107268+)

            Status = pRS->SetVariable(L"Setup",&gSetupGuid, SetupAttr, SetupSize, pSetupData);
			pBS->FreePool( pSetupData );
		}
	}
		
	return Status;
}
//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   FindLegacyDeviceGroupByType
//
// Description: Go through the legacy device order structure and find the legacy dev order
//              group type that we want then return this group.
//
// Input:       LEGACY_DEVICE_ORDER *DevOrder - pointer to the legacy device order
//              UINTN DevOrderSize - size of the legacy dev order structure
//              UINT32 Type - Group type to match
//
// Output:      LEGACY_DEVICE_ORDER *
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
LEGACY_DEVICE_ORDER* FindLegacyDeviceGroupByType(
    LEGACY_DEVICE_ORDER *DevOrder, UINTN DevOrderSize, UINT32 Type
)
{
    LEGACY_DEVICE_ORDER *LegacyGroup = DevOrder;

    for (; (UINT8*)LegacyGroup < (UINT8*)DevOrder + DevOrderSize
            ; (UINT8*)LegacyGroup += LegacyGroup->Length + sizeof(LegacyGroup->Type))
    {
        if (LegacyGroup->Type == Type) {
            return LegacyGroup;
        }
    }

    return NULL;
}
//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   FboSyncBootOptionsFromDevOrder
//
// Description: UefiDevOrder and FboLegacyDevOrder variables contain the
//              disabled flags saved by setup.  Need to update the disabled
//              flag to BootOptionList right before any other functions
//              that will process the BootOptionList.
//              BootOptionList will be set to NOT ACTIVE for disabled
//              DevOrder, ACTIVE for enabled one.
//
// Input:       None
//
// Output:      None
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
FboSyncBootOptionsFromDevOrder()
{
    LEGACY_DEVICE_ORDER *LegacyOrder = NULL, *LegacyGroup = NULL;
    LEGACY_DEVICE_ORDER *OldLegacyOrder = NULL, *OldLegacyGroup = NULL;
    UEFI_DEVICE_ORDER *UefiOrder = NULL, *UefiGroup = NULL;
    UINTN DevOrderSize = 0;
    UINTN OldDevOrderSize = 0;
    DLINK *Link;
    BOOT_OPTION *Option;
    INT32 j;
    EFI_STATUS Status;
    UINT16 DeviceCount;
    INT32 DevIndex;
    UINT32 Type;

    //
    // Set ACTIVE information according to UefiDevOrder
    //
    Status = GetEfiVariable(L"UefiDevOrder", &gFixedBootOrderGuid, NULL, &DevOrderSize, &UefiOrder);
    TRACE((-1, "[fbo] Get UefiDevOrder: %r\n", Status));
    if (!EFI_ERROR(Status))
    {
        for (UefiGroup = UefiOrder
                         ; (UINT8*)UefiGroup < (UINT8*)UefiOrder + DevOrderSize
                ; UefiGroup = (UEFI_DEVICE_ORDER*)((UINT8*)UefiGroup + UefiGroup->Length + sizeof(UefiGroup->Type)))
        {
            DeviceCount = DEVORDER_COUNT(UefiGroup);

            // loop through boot option numbers within this group
            for (j = 0; j < DeviceCount; j++)
            {
                // set up Option->Attributes.LOAD_OPTION_ACTIVE
                FOR_EACH_BOOT_OPTION(BootOptionList, Link, Option)
                {
                    if (IsLegacyBootOption(Option))
                        continue;

                    if ((UefiGroup->Device[j]&FBO_UEFI_ORDER_MASK) == Option->BootOptionNumber)  // [31:24] = disabled flag
                    {
                        TRACE((-1, "[fbo] %S.Device[%d] = %x\n", Option->Description, j, UefiGroup->Device[j]));
                        if (UefiGroup->Device[j] & FBO_UEFI_DISABLED_MASK)  // disabled?
                            Option->Attributes &= ~LOAD_OPTION_ACTIVE;
                        else
                            Option->Attributes |= LOAD_OPTION_ACTIVE;
                    }
                }
            }
        }

    }


    //
    // Set ACTIVE information according to FboLegacyDevOrder
    //

    // The flow of this FboLegacyDevOrder variable:
    // 1. Updated the BootOptionList.Attributes from FboLegacyDevOrder right after boot options are
    //    read from NVRAM in FboSyncBootOptionsFromDevOrder() to reflect the setup controls.
    // 2. Attributes will be changed to HIDDEN and NOT ACTIVE according to boot mode in FBO_UpdateBootListPriority().
    // 3. Save the disabled information here for setup to use before we modifying the Attributes later
    //    in FBO_UpdateBootListPriority().
    // 4. OldLegacyDevOrder variable indicates the sequence of legacy boot options by group in BootOptionList
    //    after reading from NVRAM, we need it to compare with FboLegacyDevOrder variable to find out options
    //    should set ACTIVE attribute or INACTIVE attribute.

    Status = GetEfiVariable(L"FboLegacyDevOrder", &gFixedBootOrderGuid, NULL, &DevOrderSize, &LegacyOrder);
    TRACE((-1, "[fbo] Get FboLegacyDevOrder: %r\n", Status));

    if (!EFI_ERROR(Status))
    {
        Status = GetEfiVariable(L"OldLegacyDevOrder", &LegacyDevOrderGuid, NULL, &OldDevOrderSize, &OldLegacyOrder);
        TRACE((-1, "[fbo] Get OldLegacyDevOrder: %r\n", Status));

        //
        // Only TRUE if..
        // 1. Get variable successfully
        // 2. Same size
        // 3. Different contents
        //
        if (!EFI_ERROR(Status)
                && OldDevOrderSize == DevOrderSize
                && MemCmp(LegacyOrder, OldLegacyOrder, DevOrderSize))
        {
            UINT16 BootOptionNumber = INVALID_BOOT_OPTION_NUMBER;

            FOR_EACH_BOOT_OPTION(BootOptionList, Link, Option)
            {
                if (!IsLegacyBootOption(Option) || Option->GroupHeader) continue;

                if (BootOptionNumber != Option->BootOptionNumber) {

                    Type = BOOT_OPTION_GET_BBS_ENTRY_DEVICE_TYPE_FUNCTION(Option->BbsEntry);
                    LegacyGroup = FindLegacyDeviceGroupByType(LegacyOrder, DevOrderSize, Type);
                    OldLegacyGroup = FindLegacyDeviceGroupByType(OldLegacyOrder, OldDevOrderSize, Type);

                    j = 0;
                    BootOptionNumber = Option->BootOptionNumber;
                }

                if (LegacyGroup == NULL || OldLegacyGroup == NULL) continue;

                DevIndex = FindPositionInTheGroupByBbsIndex(LegacyGroup, OldLegacyGroup->Device[j]);
                // FixedBootOrderSaveChange function doesn't save FboLegacyDevOrder variable as 
                // group sequence we change in Setup, and that cause AdjustLegacyBootOptionPriorities
                // function update the wrong Priority to Option, hence, we disable 
                // AdjustLegacyBootOptionPriorities function by SDL and update correct priority here.
                Option->Priority += (DevIndex - j) * DEFAULT_PRIORITY_INCREMENT;
                j++;

                if (LegacyGroup->Device[DevIndex] & FBO_LEGACY_DISABLED_MASK)
                {
                    Option->Attributes &= ~LOAD_OPTION_ACTIVE;
                }
                else
                {
                    Option->Attributes |= LOAD_OPTION_ACTIVE;
                }
            }
        }
    }

    if (OldLegacyOrder != NULL)
        pBS->FreePool(OldLegacyOrder);
    if (LegacyOrder != NULL)
        pBS->FreePool(LegacyOrder);
    if (UefiOrder != NULL)
        pBS->FreePool(UefiOrder);

}
//**********************************************************************
//**********************************************************************
//**                                                                  **
//**        (C)Copyright 1985-2012, American Megatrends, Inc.         **
//**                                                                  **
//**                       All Rights Reserved.                       **
//**                                                                  **
//**             6145-F Northbelt Pkwy, Norcross, GA 30071            **
//**                                                                  **
//**                       Phone: (770)-246-8600                      **
//**                                                                  **
//**********************************************************************
//**********************************************************************
