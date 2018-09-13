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
// $Archive: /Alaska/SOURCE/Modules/AMITSE2_0/AMITSE/BootOnly/bbs.c $
//
// $Author: Premkumara $
//
// $Revision: 32 $
//
// $Date: 7/11/14 1:31p $
//
//*****************************************************************//
//*****************************************************************//
// Revision History
// ----------------
// $Log: /Alaska/SOURCE/Modules/AMITSE2_0/AMITSE/BootOnly/bbs.c $
// 
// 32    7/11/14 1:31p Premkumara
// [TAG]  		EIP175119
// [Category]  	Bug Fix
// [Severity]  	Normal
// [Symptom]  	Can not boot to PXE with boot override menu if
// GROUP_BOOT_OPTIONS_BY_TAG is 0
// [RootCause]  	With GROUP_BOOT_OPTIONS_BY_TAG = 0, the Index 
// 
// of the BBS Network Device was 0xFFFF Since CSM does not 
// 
// publish any handle for BBS Network Boot Device.
// 
// that's why it was not booting.
// [Solution]  	Added Condition to check whether the Boot option type is 
// 
// Network or not.if Network Type then,Directly assigning the 
// 
// Orig Index so that it will Boot.
// [Files]  		bbs.c
// 
// 31    7/11/14 1:23p Premkumara
// [TAG]  		EIP166385
// [Category]  	Bug Fix
// [Severity]  	Minor
// [Symptom]  	If the HDD boot option is selected to Disabled in Boot
// Priority, this HDD will be disappeared under DOS
// [RootCause]  	TSE was setting Boot priority to BBS_UNPRIORITIZED_ENTRY
// 
// insted of setting BBS_DO_NOT_BOOT_FROM for the disabled devices
// [Solution]  	modified the code to assign the Boot priority to
// BBS_DO_NOT_BOOT_FROM
// 
// instead of BBS_UNPRIORITIZED_ENTRY for the disabled devices
// 
// so that they will be visible under DOS
// [Files]  		bbs.c
// 
// 30    5/14/14 11:56a Arunsb
// [TAG]	EIP168723
// [Description]	Removed RT attribute for LegacyDevOrder variable.
// [Files]	bbs.c and callback.c
// 
// 29    5/02/14 10:39a Premkumara
// [TAG]  		EIP151484 
// [Category]  	Bug Fix
// [Severity]  	Normal
// [Symptom]  	When token MATCH_BOOT_OPTION_BY_LOCATION = 0 and
// GROUP_BOOT_OPTIONS_BY_TAG = 0, the device path info is not proper so
// device is not displaying.
// [RootCause]  	When MATCH_BOOT_OPTION_BY_LOCATION = 1 the BBS devicepath
// and bootdata DevicePath length are getting matched but when
// MATCH_BOOT_OPTION_BY_LOCATION = 0, then BBS devicepath and bootdata
// DevicePath length will be different. 
// [Solution]  	To resolve this, when MATCH_BOOT_OPTION_BY_LOCATION = 1
// i'm checking for valid DevicePath length and when
// MATCH_BOOT_OPTION_BY_LOCATION = 0 i'm checking for valid for BBS device
// type
// [Files]  		BootOnly\BBs.c
// 
// 28    12/03/13 2:09p Premkumara
// [TAG]  		EIP130420
// [Category]  	Bug Fix
// [Severity]  	Minor
// [Symptom]  	String is getting truncated
// [RootCause]  	The string for messagebox, Popup controls is getting
// truncated
// [Solution]  	Used temp variable to store original string and modify the
// string temp and used to avoid changing org string.
// [Files]  		String.c
// 
// 27    7/02/13 10:06a Premkumara
// [TAG]  		EIP120011
// [Category]  	Improvement
// [Description]  	Variable BootOrder and LegacyDevOrder need
// fool-proofing function when TSE load variabled
// [Files]  		Bbs.c, Boot.c, Callback.c, TseLiteHelper.c, Variable.c
// 
// 26    2/06/13 9:03a Arunsb
// Checked in properly
// 
// 26    1/31/13 12:51p Arunsb
// [TAG]  			EIP109382
// [Category]  	Bug Fix
// [Severity]  	Important
// [Symptom]  		Boot Device name incorrect when load default 
// [RootCause]  	Legacy offset in gbootdata corrupted so names displayed
// improperly.
// [Solution]  	Legacy offsets re-calculated properly
// [Files]  		CommonHelper.c, BootOnly\bbs.c and callback.c
// 
// 25    10/18/12 5:58a Arunsb
// Updated for 2.16.1235 QA submission
// 
// 20    10/10/12 12:36p Arunsb
// Synched the source for v2.16.1232, backup with Aptio
// 
// 24    9/24/12 9:04a Premkumara
// [TAG]  		EIP 93797
// [Description]	Add support to check for enabled device in BBS priority
// order before launching legacy boot.
// [Files]  		bbs.c, Boot.c, Protocol.c
// 
// 23    5/29/12 3:49a Arunsb
// [TAG]  		EIP91109
// [Category]  	Improvement
// [Description]  	Sync the Aptio IV source for AptioV
// 
// 22    4/27/12 7:21a Premkumara
// [TAG]  		EIP81402
// [Category]  	Bug Fix
// [Severity]  	Important
// [Symptom]  	HDD Port Number is not properly updated after adding
// "TseDefaultBootOrder"
// [RootCause]  	when GROUP_BOOT_OPTIONS_BY_TAG=0 BBSList->Name is not
// returned properly
// [Solution]  	Returned BBSList->Name properly
// [Files]  		bbs.c, variable.c
// 
// 21    1/11/12 7:11a Arunsb
// [TAG]  		EIP64700
// [Category]  	Improvement
// [Description]  	Request for _BBSSetDevicePriorities to check current
// BootPriority before assigning a new BootPriority
// [Files]  		bbs.c
// 
// 20    12/16/11 5:41a Arunsb
// Reverted 64700 change. Bcoz legacy boot not happening properly.
// 
// 19    11/30/11 1:24p Premkumara
// [TAG]  		EIP75352
// [Category]  	Improvement
// [Description]  	Suppress the warnings from static code analyzer
// [Files]  		Boot.c, bbs.c, TseAdvanced.c, Special.c, Variable.c,
// TseLiteHelper.c, PopupSel.c, AddBootOption.c, Hii.c, FormBrowser2.c
// 
// 18    10/31/11 9:49a Rajashakerg
// [TAG]  		EIP71120,71512 
// [Category]  	Bug Fix
// [Severity]  	Important
// [Symptom]  	BIOS gets stuck in infinite loop On enabling
// TSE_LOAD_OPTION_HIDDEN token,In first boot incorrect devices is
// disabled in Setup & BBS table but in second boot the correct device is
// disabled in both places.
// [Solution]  	Hidden option handled properly.
// [Files]  		TseLite\variable.c, TseLite\minisetupext.c, TseAdvanced.c,
// special.c, BootOnly\minisetup.h,BootOnly\boot.c, BootOnly\bbs.c
// 
// 17    9/29/11 1:15p Premkumara
// [TAG]  		EIP64700
// Category] 	Function Request
// [Description]  	Checking current BootPriority before assigning a new
// BootPriority.
// Not assigning priority if it also BBS_DO_NOT_BOOT_FROM
// [Files]  		bbs.c
// 
// 16    6/20/11 11:43a Rajashakerg
// [TAG]  		EIP59417
// [Category]  	New Feature
// [Description]  	Spport LOAD_OPTION_HIDDEN option in TSE 
// [Files]  		boot.h, AMITSE.sdl, CommonHelper.c, bbs.c, boot.c,
// minisetup.h, special.c, callback.c 
// 
// 15    3/07/11 4:49p Arunsb
// [TAG]  		EIP53106
// [Category]  	Bug Fix
// [Severity]  	Minor
// [Symptom]  	Invalid string appears in the boot order for Network
// related devices
// [RootCause]  	Handle not obtained for network related devices
// [Solution]  	Disabled option is checked only if
// GROUP_BOOT_OPTIONS_BY_TAG token is enabled
// [Files]  		bbs.c and commonhelper.c
// 
// 14    2/04/11 4:42p Mallikarjunanv
// udpated the BBSGetDeviceList() function to update the
// LegacyDevVariables properly in case of TSE Lite.
// 
// 13    12/21/10 11:32a Mallikarjunanv
// 
// 13    10/06/10 5:48p Madhans
// [TAG] - EIP 45620 
// [Category]- Enhancment
// [Severity]- Mordarate
// [Symptom]- TSE with TSE_CONTINUE_BOOT_NOW_ON_FAIL ON Not allows to boot
// to USB group of devices with customized BDS.
// [RootCause] - BBSTable does not contain the DeviceType called USB. Only
// in EFI Logical group is created in EFI variables.
// TSE was checking the DeviceType to set the priorities.
// [Solution]- TSE is changed to not check for DeviceType in BBSTable. But
// set the priorities based on LegacyDevOrder.
// [Files] - bbs.c commonhelper.c minisetup.h 
// 
// 12    10/05/10 5:08p Madhans
// [TAG] - EIP 45299 
// [Category]- Enhancment
// [Severity]- Minor
// [Symptom]- TSE by default saves the Disbaled BBS devices device path in
// NVRAM Varaiable "DisabledDevs" Variable. In Next boots it depend on
// this variable to consider the device as disabled inaddtion to
// LegacyDevOrder.
// Some BDS customized projects don't want this.
// [Solution]- TSE_SAVE_DISABLED_BBS_DEVICEPATH SDL token created to
// control this option. Bydefault It is Enabled.
// [Files] - callback.c bbs.c commonhelper.c minisetup.h AMITSE.sdl
// 
// 11    9/21/10 11:26a Madhans
// EIP44542 changes
// 
// 8     9/20/10 6:47p Madhans
// [TAG]    	EIP44542
// [Category]	BUILD ISSUE FIX
// [Symptom]	Build issues with TSE label (INT)4.6.2_TSE_2_10_1207_TEST
// when IdeSecurity and FastBoot modules added to the project
// [RootCause] -
// [Solution]	Build issues resolved
// [Files]		CommonHelper.c, Tsecommon.h, Hiilib.h, Boot.h, minisetup.h,
// bbs.c, special.c, Bds.c TseLitehelp
// 
// 7     9/16/10 8:38p Madhans
// Update for TSE 2.10. Refer Changelog.log for more details.
// 
// 10    9/16/10 3:01p Madhans
// To Avoid build issues with TSE_USE_EDK_LIBRARY Building.
// 
// 9     8/27/10 4:59a Mallikarjunanv
// EIP-39334: support to build TSE without the CSM module support
// 
// 8     7/28/10 4:46a Mallikarjunanv
// EIP-29951: TSE Device Path Name support updated
// 
// 7     3/23/10 5:07p Blaines
// Preseve the order of disabled BBS boot devices.
// 
// 6     2/19/10 8:14a Mallikarjunanv
// updated year in copyright message
// 
// 5     1/09/10 5:10a Mallikarjunanv
// Updated TSE2.01 Release sources with coding standards
// 
// 4     9/24/09 9:41a Sudhirv
// EIP-24971: moved the dependency for TSE_CONTINUE_BOOT_NOW_ON_FAIL to
// Tse Binary
// 
// 3     6/23/09 6:56p Blaines
// Coding standard update, 
// Remove spaces from file header to allow proper chm function list
// creation.
// 
// 2     6/12/09 7:41p Presannar
// Initial implementation of coding standards
// 
// 1     6/04/09 8:05p Madhans
// 
// 1     4/28/09 11:11p Madhans
// Tse 2.0 Code complete Checkin.
// 
// 2     1/30/09 6:06p Madhans
// Function headers added. 
// 
// 1     12/18/08 7:58p Madhans
// Intial version of TSE Lite sources
//*****************************************************************//
//*****************************************************************//
//**********************************************************************
//<AMI_FHDR_START>
//
// Name:		bbs.c
//
// Description:	takecare of bbs/legacy boot management.
//
//<AMI_FHDR_END>
//**********************************************************************

#include "minisetup.h"

EFI_GUID gLegacyDevGuid = LEGACY_DEV_ORDER_GUID;
BOOT_DATA *gCurrLegacyBootData;
static EFI_LEGACY_BIOS_PROTOCOL *gLegacyBios = NULL;
extern EFI_GUID gEfiLegacyBiosProtocolGuid;

//Internal functions
EFI_STATUS _BBSInitProtocol( VOID );
VOID _BBSSetDevicePriorities( BBS_TABLE *BBSInfo, UINT16 *Priority, BOOT_DATA *BootData );
VOID _CreateDriveString ( CHAR16 *String, UINT16 *IdentifyDriveData );
VOID BBSBuildName( CHAR16 *String, BBS_TABLE *info, UINTN index, HDD_INFO *HDDInfo );
BOOLEAN _BBSCheckDisabled( BBS_TABLE *BBSEntry );
UINT8   IsBootOptionsGroupingEnabled (void);

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	_BBSInitProtocol
//
// Description:	function to initialize the bbs protocol.
//
// Input:		void
//
// Output:		device path
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS _BBSInitProtocol( VOID )
{
	EFI_STATUS Status = EFI_SUCCESS;

	if ( gLegacyBios != NULL )
		return Status;

	Status = gBS->LocateProtocol( &gEfiLegacyBiosProtocolGuid, NULL, &gLegacyBios );
	if ( EFI_ERROR( Status ) )
		gLegacyBios = NULL;

	return Status;
}


INTN CompareDevicePath(EFI_DEVICE_PATH_PROTOCOL *pDp1, EFI_DEVICE_PATH_PROTOCOL *pDp2){
	UINTN	len;
//---------------------
	if(!pDp1 && !pDp2) return 0; //if both is NULL than Dp1==Dp2
	if(!pDp1 || !pDp2) return -1; // if one is NULL than Dp1!=Dp2
	len=EfiDevicePathSize(pDp1);
	if(EfiDevicePathSize(pDp2)!=len) return -1;
	return MemCmp(pDp1,pDp2, len);
}


//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	MatchDevicePath
//
// Description:	Matches the Device path from the BootOption to BBS Device path to locate the 
//              right Device
//
// Input:		pBootData - Boot Data of Boot Option
//              LegacyOrder - LegacyDevOrder Entry for Boot Option
//              DevHandle   - BBS device Handle
//
// Output:		BOOLEAN - TRUE - Device path matched betweend LegacyOrder and pBootData.
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
BOOLEAN MatchDevicePath(BOOT_DATA *pBootData, BBS_ORDER_TABLE* LegacyOrder, EFI_HANDLE DevHandle)
{
    CHAR16 *varName = L"BootXXXX";
    BOOT_OPTION *pOption;
    UINTN OptionSize;
    EFI_DEVICE_PATH_PROTOCOL *Path;
    EFI_DEVICE_PATH_PROTOCOL *BBSDevDP;
    EFI_STATUS Status;
    BOOLEAN bRet=FALSE; 

    OptionSize = 0; pOption = NULL;
    SPrint( varName, sizeof(CHAR16) * (EfiStrLen( varName )+1),gBootFormarSpecifier, pBootData->Option );
    pOption = (BOOT_OPTION *)VarGetNvramName( varName, &gEfiGlobalVariableGuid, NULL, &OptionSize );

    if(EfiDevicePathSize(pBootData->DevicePath) == pOption->PathLength)
    {   // Device path Length Matches
        // Not Flex Boot 
        bRet=TRUE;
        goto DONE;
    }

    //For Flex Boot try to match Device path of BBS Device

	// Skip the BBS Devicepath
	Path = (EFI_DEVICE_PATH_PROTOCOL*)(((UINTN)pBootData->DevicePath) + EfiDevicePathSize(pBootData->DevicePath));

 	Status = gBS->HandleProtocol( DevHandle, &gEfiDevicePathProtocolGuid, &BBSDevDP );

 	// Not able to locate just matched the Device type
 	if ( EFI_ERROR( Status ) )
	{
	  bRet=TRUE; 
	  goto DONE;
	}

	//Comparing device path length if MATCH_BOOT_OPTION_BY_LOCATION = 1 devicepath(BBSDevDP) and DevicePath length are equal
	if(CompareDevicePath(Path, BBSDevDP) == 0)
	{
		bRet=TRUE;
	}

	//EIP-151484 If MATCH_BOOT_OPTION_BY_LOCATION = 0 then devicepath(BBSDevDP) and Device Pathlength will be different so matching with DeviceType
	else if( ( ((BBS_ORDER_TABLE*)LegacyOrder)->Type == BBSDevDP->Type ) || 
				( ((BBS_BBS_DEVICE_PATH*)pBootData->DevicePath)->DeviceType == BBSDevDP->Type )
	)
	{
		bRet = TRUE;
	}

DONE:
    MemFreePointer((VOID **)&pOption);

    return bRet;
}

//EIP109382 Starts
//<AMI_PHDR_START>
//-------------------------------------------------------------------------------------
// Procedure:	RearrangeBBSOrder
//
// Description:	Rearranges the bootdata legacy entries with legacydevorder defaults
//
// Input:		VOID * - Cache Buffer
//
// Output:		VOID
//
//--------------------------------------------------------------------------------------
//<AMI_PHDR_END>
//UINT8   IsBootOptionsGroupingEnabled (VOID);
EFI_STATUS _BBSInitProtocol (VOID);
BOOLEAN MatchDevicePath(BOOT_DATA *pBootData, BBS_ORDER_TABLE* LegacyOrder, EFI_HANDLE DevHandle);
VOID RearrangeBBSOrder (NVRAM_VARIABLE *nvPtr, NVRAM_VARIABLE *DefaultBuffer)
{
   EFI_STATUS  Status;
   UINT16      HDDCount = 0, BBSCount = 0;
   HDD_INFO    *HDDInfo = NULL;
   BBS_TABLE   *BBSInfo = NULL;
   UINT16      *BootOrder;
   UINTN       BootOrderSize,p;
   BOOT_DATA   *pBootData;
   UINT16      count = 0;
   UINTN       CurrSize = 0, iIndex = 0;
   EFI_GUID    AmitseBootOrderChangeGuid = AMITSE_BOOT_ORDER_CHANGE_GUID;
   BBS_ORDER_TABLE      *DevEntry = NULL, *CurrOrder = NULL, *NewLegacyOrder = NULL, *NewDevEntry = NULL;
   BBS_BBS_DEVICE_PATH  *DevPath = NULL;
   
   Status = _BBSInitProtocol ();
   if (EFI_ERROR (Status))
      return;

   Status = gLegacyBios->GetBbsInfo (
               gLegacyBios,
               &HDDCount,
               &HDDInfo,
               &BBSCount,
               &BBSInfo
               );
   if (EFI_ERROR (Status))
   {
      return;
   }
   BootOrderSize = 0;
   BootOrder = VarGetNvramName (L"BootOrder", &gEfiGlobalVariableGuid, NULL, &BootOrderSize);
   
   if ((NULL == BootOrder) || (0 == BootOrderSize))
      return; //continue;

   NewLegacyOrder = EfiLibAllocateZeroPool (DefaultBuffer->Size);
   if (NULL == NewLegacyOrder)
   {
      MemFreePointer((VOID **) &BootOrder);
      return;
   }   
   
   //NOTE: Taking advantage of the fact that
   //VARIABLE_ID_BBS_ORDER is after
   //VARIABLE_ID_BOOT_ORDER
   NewDevEntry = NewLegacyOrder;
   for (p=0; p<(BootOrderSize/sizeof(UINT16)); p++)
   {
      pBootData = BootGetBootData (BootOrder[p]);
      //EIP:59417 - Error Handling in case of pBootData is NULL. If its NULL the setupgets a CRASH
      if (pBootData == NULL)
         goto DONE;
   
      if (BBSValidDevicePath (pBootData->DevicePath))
      {
         DevPath = (BBS_BBS_DEVICE_PATH *)pBootData->DevicePath;
         DevEntry = (BBS_ORDER_TABLE *)DefaultBuffer->Buffer;
         for (iIndex = 0; iIndex < DefaultBuffer->Size; )
         {
				if ( (DevEntry->Length >= DefaultBuffer->Size) || (0 == DevEntry->Length) ) //EIP-120011
				{
					return;
				}

            count = DevEntry->Length / sizeof(UINT16) - 1;

            if (count)
            {
               if (DevPath->DeviceType == DevEntry->Type)
               {
                  if (MatchDevicePath (pBootData, DevEntry, (EFI_HANDLE)*(UINTN*)&BBSInfo[(UINT8)DevEntry->Data[0]].IBV1) )
                  //Found a valid dev entry group.
                     break;
               }
            }
            count = sizeof (UINT32) + DevEntry->Length;
            DevEntry = (BBS_ORDER_TABLE *)((UINTN)DevEntry + count);
            iIndex += count;
         }
         if (iIndex < DefaultBuffer->Size)
         {
            MemCopy (NewDevEntry, DevEntry, sizeof(UINT32) + DevEntry->Length);
         }
         pBootData->LegacyEntryOffset = (UINTN)NewDevEntry - (UINTN)NewLegacyOrder;
         //create boot data order list
         NewDevEntry = (BBS_ORDER_TABLE *)((UINTN)NewDevEntry + sizeof (UINT32) + DevEntry->Length);
      }
   }
   MemFreePointer ((VOID **)&nvPtr->Buffer);
   nvPtr->Buffer = (UINT8 *)NewLegacyOrder;
DONE:
   //Update the nv buffer with the re ordered list
   
   //Signal TPM if BBS order has changed
   CurrOrder = VarGetNvramName (L"LegacyDevOrder", &gLegacyDevGuid, NULL, &CurrSize);
   if (NULL == CurrOrder)
   {
      MemFreePointer((VOID **) &BootOrder);
      return;
   }
   if (CurrOrder)
   {
      if (MemCmp ((UINT8 *)CurrOrder, (UINT8 *)NewLegacyOrder, CurrSize))
         EfiLibNamedEventSignal (&AmitseBootOrderChangeGuid);
      
      MemFreePointer((VOID **) &CurrOrder);
   }
   MemFreePointer((VOID **) &BootOrder);
}
//EIP109382 Ends

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	BBSGetDeviceList
//
// Description:	function to get the list of all the devices
//
// Input:		void
//
// Output:		void
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID BBSGetDeviceList( VOID )
{
    EFI_STATUS Status;

    UINT16 HDDCount = 0, BBSCount = 0;
    HDD_INFO *HDDInfo = NULL;
    BBS_TABLE *BBSInfo = NULL;

    BBS_ORDER_TABLE *LegacyOrder = NULL, *NewLegacyOrder = NULL, *DevEntry, *NewDevEntry;
    UINTN NewLegacyOrderSize, LegacyOrderSize=0, j, l;
    UINT16 count = 0,u16Tmp;
    UINT16 *BootOrder = NULL, *NewBootOrder = NULL;
    UINTN NewBootOrderSize, BootOrderSize=0, i, k;
    BOOT_DATA *pBootData;
    BBS_BBS_DEVICE_PATH * DevPath;
    UINT16 NoOfLegacyGroups = 0;
	UINT32 LegDevOrderAttribute = 7;
    
    Status = _BBSInitProtocol();
    if ( EFI_ERROR( Status ) )
        return;

    Status = gLegacyBios->GetBbsInfo(
            gLegacyBios,
            &HDDCount,
            &HDDInfo,
            &BBSCount,
            &BBSInfo
            );

    LegacyOrderSize = 0;

    LegacyOrder = VarGetNvramName( L"LegacyDevOrder", &gLegacyDevGuid, &LegDevOrderAttribute, &LegacyOrderSize );
    if ( LegacyOrder == NULL )
        goto DONE;

    BootOrderSize = 0;
    BootOrder = VarGetNvramName( L"BootOrder", &gEfiGlobalVariableGuid, NULL, &BootOrderSize );
    if(NULL == BootOrder)
        goto DONE;

    //Check if the Master boot order and Legacy dev order match.
    //Create corrected new orders if not.
    NewLegacyOrder = EfiLibAllocateZeroPool(LegacyOrderSize);
    NewBootOrder = EfiLibAllocateZeroPool(BootOrderSize);

    //NOTE: Device count will not be initialised here. It will be
    //initialised with the number of devices in a group when the user
    //switches to a page specific to that group.
    NoOfLegacyGroups = 0;
    k = 0;
    NewDevEntry = NewLegacyOrder;
    for(i=0; i<(BootOrderSize/sizeof(UINT16)); i++)
    {
        pBootData = BootGetBootData(BootOrder[i]);
        if(pBootData)
        {
            if(BBSValidDevicePath(pBootData->DevicePath))
            {
                //BBS boot order entry
                DevPath = (BBS_BBS_DEVICE_PATH *)pBootData->DevicePath;

                DevEntry = LegacyOrder;
					for(j=0; j<LegacyOrderSize; )
					{
						if ( (DevEntry->Length >= LegacyOrderSize) || (0 == DevEntry->Length) ) //EIP-120011
						{
							return;
						}
						count = DevEntry->Length / sizeof(UINT16) - 1;

						if (count)
						{
                     if(DevPath->DeviceType == DevEntry->Type)
                     {
                         if(MatchDevicePath(pBootData, DevEntry,(EFI_HANDLE)*(UINTN*)&BBSInfo[(UINT8)DevEntry->Data[0]].IBV1 ))
                             //Found a valid dev entry group.
                             break;
                     }
						}

						//Go to next entry
						count = sizeof(UINT32) + DevEntry->Length;
						DevEntry = (BBS_ORDER_TABLE *)((UINTN)DevEntry + count);
						j += count;
					}

                if(j<LegacyOrderSize)
                {
                    //Found a valid BBS entry. Take dev entry and boot option.
                    NewBootOrder[k] = BootOrder[i];
                    k++;

                    MemCopy(NewDevEntry, DevEntry, sizeof(UINT32) + DevEntry->Length);
                    NoOfLegacyGroups++;

                    pBootData->LegacyEntryOffset = (UINTN)NewDevEntry - (UINTN)NewLegacyOrder;
                    pBootData->LegacyDevCount = count;


                    if(gIsSaveDisabledBBSDevicePath)
                    {
                        //Make sure the right devices are disabled
                        for(j=0;j<count;j++)//Caution: destroying contents of j
                        {
                            if(BBS_ORDER_DISABLE_MASK == (NewDevEntry->Data[j] & BBS_ORDER_DISABLE_MASK))
                            {
                                //BBS Type Network Device doesnot publish any Handle hence, directly assigning the actual Index
								if(BBS_TYPE_EMBEDDED_NETWORK == NewDevEntry->Type)//EIP-175119
									NewDevEntry->Data[j] = (UINT8)(NewDevEntry->Data[j]);
								//Make sure we have the device path in NVRAM for this legacy option
                                else if( !_BBSCheckDisabled( &(BBSInfo[(UINT8)(NewDevEntry->Data[j])]) ) )
                                {
                                    NewDevEntry->Data[j] = (UINT8)(NewDevEntry->Data[j]);
                                }
                            }
                        }
                    }

    				if(!IsPreservedDisabledBootOptionOrder())
    				{
	                    //Correct LegacyDevOrder variable if necessary. Move
		                //disabled devices to end.
			            for ( j = 0; j < count; j++ )
				        {
							if(BBS_ORDER_DISABLE_MASK == (NewDevEntry->Data[j] & BBS_ORDER_DISABLE_MASK))
							{
								for(l=j+1; l<count; l++)
								{
									if(BBS_ORDER_DISABLE_MASK != (NewDevEntry->Data[l] & BBS_ORDER_DISABLE_MASK))
									{
										u16Tmp = NewDevEntry->Data[l];
										NewDevEntry->Data[l] = NewDevEntry->Data[j];
										NewDevEntry->Data[j] = u16Tmp;
										break;
									}
								}
								if(l>=count)
	                                break;
		                    }
                        }
                    }

                    //create boot data order list
                    pBootData->OrderList = EfiLibAllocateZeroPool( count * sizeof(BBS_ORDER_LIST) );
                    for ( j = 0; j < count; j++ )
                    {
                        pBootData->OrderList[j].Index = NewDevEntry->Data[j] & (~BBS_ORDER_DISABLE_MASK);
                        BBSBuildName(
                                    pBootData->OrderList[j].Name,
                                    &BBSInfo[pBootData->OrderList[j].Index],
                                    pBootData->OrderList[j].Index,
                                    HDDInfo
                                    );
                    }

                    //Move pointer to the unused portion
                    count = sizeof(UINT32) + NewDevEntry->Length;
                    NewDevEntry = (BBS_ORDER_TABLE *)((UINTN)NewDevEntry + count);

                    //Mark it used in DevEntry by assigning device type
                    //to BBS_TYPE_UNKNOWN
                    DevEntry->Type = BBS_TYPE_UNKNOWN;
                }
            }
            else
            {
                //A valid non bbs boot order entry
                NewBootOrder[k] = BootOrder[i];
                k++;
            }
        }
    }

    //Set corrected variables
    NewLegacyOrderSize = (UINTN)NewDevEntry - (UINTN)NewLegacyOrder;
    VarSetNvramName(L"LegacyDevOrder",
                    &gLegacyDevGuid,
                    LegDevOrderAttribute,
                    NewLegacyOrder,
                    NewLegacyOrderSize);

    NewBootOrderSize = k*sizeof(UINT16);
    VarSetNvramName(L"BootOrder",
                    &gEfiGlobalVariableGuid,
                    EFI_VARIABLE_BOOTSERVICE_ACCESS | EFI_VARIABLE_RUNTIME_ACCESS | EFI_VARIABLE_NON_VOLATILE,
                    NewBootOrder,
                    NewBootOrderSize);

    MemFreePointer( (VOID **)&BootOrder );
    MemFreePointer( (VOID **)&NewBootOrder );
    MemFreePointer( (VOID **)&LegacyOrder );
    MemFreePointer( (VOID **)&NewLegacyOrder );

DONE:
    //Set LegacyDev variable with number of groups
	UpdateLegacyDevVariable(NoOfLegacyGroups);

    //Set the LegacyGroup variable to zero for now
    NoOfLegacyGroups = 0;
    VarSetNvramName( L"LegacyGroup", &gLegacyDevGuid, EFI_VARIABLE_BOOTSERVICE_ACCESS, &NoOfLegacyGroups, sizeof(NoOfLegacyGroups) );

}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	BBSSetBootPriorities_BootOrder
//
// Description:	Assign priority as per boot order other than 0 priority devices
//
// Input:		void
//
// Output:		void
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID BBSSetBootPriorities_BootOrder(UINT16 Priority)
{
	EFI_STATUS	Status;
	UINT16		*pBootOrder=NULL;
	UINT16		BootOrderCount = 0;
	UINT16        DevType=0;
	UINTN         size=0;
	UINT16        HDDCount = 0;
	UINT16        BBSCount = 0;
	HDD_INFO      *HDDInfo = NULL;
	BBS_TABLE     *BBSInfo = NULL;
	BOOT_DATA     *pBootData;
	UINT16        i,index,index1;
	UINT16        j;
    UINT8   *pDevOrder;
    BBS_ORDER_TABLE	*pDevEntry;
	
	Status = _BBSInitProtocol();
	if ( EFI_ERROR( Status ) )
		return;
	
	Status = gLegacyBios->GetBbsInfo(
										gLegacyBios,
										&HDDCount,
										&HDDInfo,
										&BBSCount,
										&BBSInfo
									);
	
	if ( EFI_ERROR( Status ) )
		return;
	
	size =0 ;
	pBootOrder = (UINT16 *)VarGetNvramName( L"BootOrder", &gEfiGlobalVariableGuid, NULL, &size );
	BootOrderCount=(UINT16)(size/sizeof(UINT16));

	if (pBootOrder==NULL) 
		return;

    size = 0;
    pDevOrder = (UINT8 *)VarGetNvramName( L"LegacyDevOrder", &gLegacyDevGuid, NULL, &size );

	if (pDevOrder==NULL) 
    {
        MemFreePointer((VOID **) &pBootOrder);
		return;
    }

	for(j=0;j<BootOrderCount;j++)
	{
		pBootData = BootGetBootData(pBootOrder[j]);
		if(!pBootData)
			continue;

        if ( BBSValidDevicePath( pBootData->DevicePath ) )
        {
            pDevEntry = (BBS_ORDER_TABLE *)(pDevOrder + pBootData->LegacyEntryOffset);

			if ( (pDevEntry->Length >= size) || (0 == pDevEntry->Length) ) //EIP-120011
			{
				return;
			}
			//search for boot options which are disabled and change their priority to BBS_DO_NOT_BOOT_FROM
			for(index=0;index<pBootData->LegacyDevCount;index++)//EIP-166385
			{
			    for(index1=0;index1<pBootData->LegacyDevCount;index1++)
			    {
					if(((pBootData->OrderList[index])).Index == pDevEntry->Data[index1])
				   		break;
			    }
				if(index1 == pBootData->LegacyDevCount)
					BBSInfo[((pBootData->OrderList[index])).Index].BootPriority = BBS_DO_NOT_BOOT_FROM;
			}
            for(i=0;i<pBootData->LegacyDevCount;i++)
            {
                if(!(pDevEntry->Data[i] & BBS_ORDER_DISABLE_MASK))
                {
                    if(BBSInfo[pDevEntry->Data[i]].BootPriority == BBS_UNPRIORITIZED_ENTRY)
                    {
        	            BBSInfo[pDevEntry->Data[i]].BootPriority = Priority;
        			    Priority++;
                    }
                }
            }
        }
	}

    MemFreePointer((VOID **) &pDevOrder);
    MemFreePointer((VOID **) &pBootOrder);
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	BBSSetBootPriorities
//
// Description:	function to set boot priorities
//
// Input:		BOOT_DATA *pBootData, UINT16 *pOrder, UINTN u16OrderCount
//
// Output:		void
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID BBSSetBootPriorities( BOOT_DATA *pBootData, UINT16 *pOrder, UINTN u16OrderCount)
{
	EFI_STATUS	Status;
	UINT16		HDDCount = 0, BBSCount = 0;
    UINT16		i, Priority = 0;
	HDD_INFO	*HDDInfo = NULL;
	BBS_TABLE	*BBSInfo = NULL;
	UINT16		  *pBootOrder=NULL;
	UINT16		  BootOrderCount = 0;
	UINTN         size=0;

	Status = _BBSInitProtocol();
	if ( EFI_ERROR( Status ) )
		return;

	Status = gLegacyBios->GetBbsInfo(
										gLegacyBios,
										&HDDCount,
										&HDDInfo,
										&BBSCount,
										&BBSInfo
									);

	if ( EFI_ERROR( Status ) )
		return;
	pBootOrder = (UINT16 *)VarGetNvramName( L"BootOrder", &gEfiGlobalVariableGuid, NULL, &size );
	BootOrderCount=(UINT16)(size/sizeof(UINT16));
	for ( i = 0; i < BBSCount; i++ )
	{
		switch ( BBSInfo[i].BootPriority )
		{
			case BBS_IGNORE_ENTRY:
			case BBS_LOWEST_PRIORITY:
			case BBS_DO_NOT_BOOT_FROM:						//EIP 64700
				continue;
			default:
				BBSInfo[i].BootPriority = BBS_UNPRIORITIZED_ENTRY;
				break;
		}
	}

    if(pOrder)
    {
        for ( i = 0; i < BootOrderCount; i++ )
	    {
            pBootData = BootGetBootData(pOrder[i]);

		    if(!pBootData)
                continue;
    		
		    if ( BBSValidDevicePath( pBootData->DevicePath ) )
			    _BBSSetDevicePriorities( BBSInfo, &Priority, pBootData);
	    }
    }
    else
    {
        if ( BBSValidDevicePath( pBootData->DevicePath ) )
            _BBSSetDevicePriorities( BBSInfo, &Priority, pBootData );
    }
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	_BBSSetDevicePriorities
//
// Description:	function to set boot device priorities
//
// Input:		BBS_TABLE *BBSInfo, UINT16 *Priority, BOOT_DATA *BootData
//
// Output:		void
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID _BBSSetDevicePriorities( BBS_TABLE *BBSInfo, UINT16 *Priority, BOOT_DATA *BootData )
{
    UINT8   *pDevOrder;
    UINTN	size;
    UINT16	i,index,index1;
    BBS_ORDER_TABLE	*pDevEntry;

    size = 0;
    pDevOrder = (UINT8 *)VarGetNvramName( L"LegacyDevOrder", &gLegacyDevGuid, NULL, &size );
	//EIP-75352 Suppress the warnings from static code analyzer
	if(NULL == pDevOrder)
		return;

    pDevEntry = (BBS_ORDER_TABLE *)(pDevOrder + BootData->LegacyEntryOffset);

	if ( (pDevEntry->Length >= size) || (0 == pDevEntry->Length) ) //EIP-120011
		return;
	//search for boot options which are disabled and change their priority to BBS_DO_NOT_BOOT_FROM
	for(index=0;index<BootData->LegacyDevCount;index++)//EIP-166385
	{
	    for(index1=0;index1<BootData->LegacyDevCount;index1++)
	    {
			if(((BootData->OrderList[index])).Index == pDevEntry->Data[index1])
		   		break;
	    }
		if(index1 == BootData->LegacyDevCount)
			BBSInfo[((BootData->OrderList[index])).Index].BootPriority = BBS_DO_NOT_BOOT_FROM;
	}

	for ( i = 0; i < BootData->LegacyDevCount; i++ )
	{
        if(!(pDevEntry->Data[i] & BBS_ORDER_DISABLE_MASK))
        {
			// don't set the BootPriority if it already the first one.
			//EIP: 64700 Checking current BootPriority before assigning a new BootPriority
			if ( (BBSInfo[pDevEntry->Data[i]].BootPriority != 0)  && (BBSInfo[pDevEntry->Data[i]].BootPriority != BBS_DO_NOT_BOOT_FROM) )	    //EIP 64700
			{
	            BBSInfo[pDevEntry->Data[i]].BootPriority = *Priority;
			    (*Priority)++;
			}
        }
	}

    MemFreePointer((VOID **) &pDevOrder);
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	BBSSetBootNowPriority
//
// Description:	Sets BBS priority for the BootNow devices.
//
// Input:		BootData - Boot data
//				uiPrefferedDevice - prefered Device type valid in ShowAllBBSDev case
//				ShowAllBbsDev - SETUP_SHOW_ALL_BBS_DEVICES
//
// Output:		EFI_STATUS
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS BBSSetBootNowPriority( BOOT_DATA *BootData,UINTN uiPrefferedDevice,BOOLEAN ShowAllBbsDev)
{
    EFI_STATUS	Status = EFI_SUCCESS;
	UINT16		count = 0, offset = 0;
    UINT8   	*pDevOrder = NULL;
    UINTN 		size = 0;
	UINT16 		HDDCount = 0, BBSCount = 0;
    UINT16 		i;
    UINT16 		Priority = 0;

    BBS_ORDER_TABLE	*pDev = NULL;
	HDD_INFO		*HDDInfo = NULL;
	BBS_TABLE		*BBSInfo = NULL;
    BBS_ORDER_LIST	*BBSList = NULL;

	Status = _BBSInitProtocol();
	if ( EFI_ERROR( Status ) )
		return Status;

	Status = gLegacyBios->GetBbsInfo(
										gLegacyBios,
										&HDDCount,
										&HDDInfo,
										&BBSCount,
										&BBSInfo
									);

	if ( EFI_ERROR( Status ) )
		return Status;

	for ( i = 0; i < BBSCount; i++ )
	{
		switch ( BBSInfo[i].BootPriority )
		{
			case BBS_IGNORE_ENTRY:
			case BBS_LOWEST_PRIORITY:
			case BBS_DO_NOT_BOOT_FROM:				//EIP 64700
				continue;
			default:
				BBSInfo[i].BootPriority = BBS_UNPRIORITIZED_ENTRY;
				break;
		}
	}
	if(!ShowAllBbsDev)
	{
	    count = BootData->LegacyDevCount;
	    offset = (UINT16)BootData->LegacyEntryOffset;
	
	    size = 0;
		pDevOrder = HelperGetVariable(VARIABLE_ID_BBS_ORDER,L"LegacyDevOrder", &gLegacyDevGuid, NULL, &size);
		//EIP-75352 Suppress the warnings from static code analyzer
		if(NULL == pDevOrder)
			return EFI_NOT_FOUND;

		pDev = (BBS_ORDER_TABLE *)(pDevOrder + offset);

		if ( (pDev->Length >= size) ||(0 == pDev->Length) ) //EIP-120011
			return EFI_NOT_FOUND;
	
		for ( i = 0; i < count; i++ )
		{
	        if(DISABLED_BOOT_OPTION != pDev->Data[i])
	        {
	            BBSInfo[pDev->Data[i]].BootPriority = Priority;
			    Priority++;
	        }
		}
	}
	else
	{
	   BBSList = BootData->OrderList;
 	   BBSInfo[BBSList[uiPrefferedDevice].Index].BootPriority = Priority;
	   Priority++;
	}


  TseBBSSetBootPriorities_BootOrder(Priority);

  if (0 == Priority ) //EIP-93797
	return EFI_UNSUPPORTED;

    return Status;
}


//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	CreateDriveString 
//
// Description:	function to create the device string
//
// Input:		CHAR16 *String, UINT16 *IdentifyDriveData
//
// Output:		void
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID _CreateDriveString ( CHAR16 *String, UINT16 *IdentifyDriveData )
{
	UINT8	i, data8;
	UINT16	data16;
	UINT8	s[MAX_DRIVE_NAME] = "APAT :";	// "PATA: "

    //Check if identify drive data is available
    if(NULL == IdentifyDriveData)
        return;

	// Check Word76 for BIT1 and BIT2; set for SATA drives
    data16 = IdentifyDriveData[76];
	if ((data16 != 0xFFFF) && (data16 & 6)) {
		s[1] = 'S';
	}

	// Get the drive name out of IdentifyDrive data word 27..46 (upto 40 chars)
	MemCopy(&s[6], IdentifyDriveData+27, MAX_DRIVE_NAME-5);

	// Swap the bytes
	for (i=0; i<MAX_DRIVE_NAME; i+=2) 
	{
		data8=s[i];
		s[i]=s[i+1];
		s[i+1]=data8;
	}

	s[MAX_DRIVE_NAME-1] = 0;	// terminate with zero

	//Put drive name in CHAR 16 array
	for (i=0; i<(MAX_DRIVE_NAME-1); i++)
	{
		String[i] = s[i];
	}
	String[MAX_DRIVE_NAME-1] = 0; // terminate with 0
}

EFI_STATUS GetAdvanceDeviceName( CHAR16 *String, VOID *info, UINTN index, VOID *HDDInfo );
//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	BBSBuildDefaultName
//
// Description:	function to build the default boot device name
//
// Input:		CHAR16 *String, BBS_TABLE *info, UINTN index, HDD_INFO *HDDInfo
//
// Output:		void
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID BBSBuildDefaultName( CHAR16 *String, BBS_TABLE *info, UINTN index, HDD_INFO *HDDInfo )
{
	EFI_STATUS Status = EFI_UNSUPPORTED;
	UINT8	i, *StringDesc;

	// If current BBS entry has its description then use it.
	StringDesc = (UINT8*)(UINTN)((info->DescStringSegment << 4) + info->DescStringOffset);
	if ( StringDesc != NULL )
	{
		for ( i = 0; (i < (MAX_DRIVE_NAME - 1)) && (StringDesc[i] != L'\0'); i++ )
			String[i] = (CHAR16)StringDesc[i];
		
		String[i] = L'\0';
	}
	else
	{
		Status = GetAdvanceDeviceName(String, info, index, HDDInfo);
		if ( Status != EFI_SUCCESS ) {
			switch ( info->DeviceType )
			{
				case BBS_TYPE_FLOPPY:
					EfiStrCpy(String, L"Floppy");
					break;
		
				case BBS_TYPE_HARDDRIVE:
					EfiStrCpy(String, L"Hard Drive");
	
				case BBS_TYPE_CDROM:
					if(BBS_TYPE_CDROM == info->DeviceType)
						EfiStrCpy(String, L"CDROM");
	
					if((index < 17) && (index > 0)) {
						_CreateDriveString(String, HDDInfo[(index-1)/2].IdentifyDrive[(index-1)%2].Raw);
					}
					break;
		
				case BBS_TYPE_EMBEDDED_NETWORK:
					EfiStrCpy(String, L"Network");
					break;
		
				case BBS_TYPE_DEV:
					EfiStrCpy(String, L"BEV Device");
					break;
		
				case BBS_TYPE_UNKNOWN:
				default:
					EfiStrCpy(String, L"Unknown");
					break;
			}
		}
	}
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	BBSLaunchDevicePath
//
// Description:	function to launch the device path
//
// Input:		EFI_DEVICE_PATH_PROTOCOL *DevicePath
//
// Output:		status
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS BBSLaunchDevicePath( EFI_DEVICE_PATH_PROTOCOL *DevicePath )
{
	EFI_STATUS Status;

	Status = _BBSInitProtocol();

	if ( EFI_ERROR( Status ) )
		return Status;

	// Performance measurement Pause
	PERF_END (0, AMITSE_TEXT("Boot"), NULL, 0);

	Status = gLegacyBios->LegacyBoot( gLegacyBios, (BBS_BBS_DEVICE_PATH *)DevicePath, 0, NULL );

	// Performance measurement continue
	PERF_START (0, AMITSE_TEXT("Boot"), NULL, 0);

	return Status;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	BBSUpdateBootData
//
// Description:	function to update boot related data
//
// Input:		UINT16 GroupNo
//
// Output:		void
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID BBSUpdateBootData(UINT16 GroupNo)
{
    UINTN i,j;
    BOOT_DATA *bootData;

    for( j=0,i=0; i<gBootOptionCount; i++ )
    {
        bootData = &(gBootData[i]);
		 //EIP:59417 - Checking the  LOAD_OPTION_HIDDEN for the boot option
		if(gLoadOptionHidden && (bootData->Active & LOAD_OPTION_HIDDEN))
		   continue;

        if ( BBSValidDevicePath(bootData->DevicePath) )
        {
            if(GroupNo == j)
            {
                gCurrLegacyBootData = bootData;
                break;
            }
            j++;
        }
    }
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	BBSGetOptionName
//
// Description:	function to get the name of the option
//
// Input:		UINT16 *Option, UINT16 Pos
//
// Output:		string
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
CHAR16 *BBSGetOptionName( UINT16 *Option, UINT16 Pos  )
{
	UINT16 count;
	BBS_ORDER_LIST *BBSList;

    BBSList = gCurrLegacyBootData->OrderList;
    count = gCurrLegacyBootData->LegacyDevCount;
	
	if(count <= Pos)
	  return( L"");

    if( Option != NULL )
        *Option=(BBSList+Pos)->Index;

	if ( BBSList != NULL )
  	  return (BBSList+Pos)->Name;

	return NULL;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	_BBSCheckDisabled
//
// Description:	function to check whether a perticular entry is disabled.
//
// Input:		UINT16 *Option, UINT16 Pos
//
// Output:		TRUE/FALSE
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
BOOLEAN _BBSCheckDisabled( BBS_TABLE *BbsEntry )
{
    EFI_STATUS	Status;
    EFI_HANDLE	Handle;
    UINTN		i,size = 0;
    EFI_GUID	BootManGuid = BOOT_MANAGER_GUID;
    EFI_DEVICE_PATH_PROTOCOL	*dpp = NULL, *NvramDP = NULL, *TmpNvramDP;

    Handle = *(VOID**)(&BbsEntry->IBV1);

    if (Handle == 0)
        return TRUE;

    Status = gBS->HandleProtocol(Handle, &gEfiDevicePathProtocolGuid, &dpp);

    if(EFI_ERROR(Status))
        return TRUE;

    TmpNvramDP = NvramDP = (EFI_DEVICE_PATH_PROTOCOL *)VarGetNvramName(L"DisabledDevs", &BootManGuid, NULL, &size);

    if(NULL == NvramDP)
        return FALSE;

    for(i=0;i<size;)
    {
        if(EfiDevicePathSize(TmpNvramDP) == EfiDevicePathSize(dpp))
        {
            if(!MemCmp((UINT8 *)TmpNvramDP, (UINT8 *)dpp, EfiDevicePathSize(TmpNvramDP)))
                break;
        }
        i+= EfiDevicePathSize(TmpNvramDP);
        TmpNvramDP = (EFI_DEVICE_PATH_PROTOCOL *) ( ((UINT8 *)NvramDP) + i );
    }

    MemFreePointer((VOID **) &NvramDP);

    if(i<size)
        return TRUE;

    return FALSE;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	BBSSetDisabled
//
// Description:	function to disable a perticular entry.
//
// Input:		UINT16 Index, VOID **DisDPs, UINTN *DPSize
//
// Output:		void
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID BBSSetDisabled(UINT16 Index, VOID **DisDPs, UINTN *DPSize)
{
    EFI_STATUS	Status;
    EFI_HANDLE	Handle;
   	UINT16		HDDCount = 0, BBSCount = 0;

	HDD_INFO *HDDInfo = NULL;
	BBS_TABLE *BBSInfo = NULL;
    EFI_DEVICE_PATH_PROTOCOL    *dpp = NULL;

   	Status = _BBSInitProtocol();
	if ( EFI_ERROR( Status ) )
		return;

	Status = gLegacyBios->GetBbsInfo(
										gLegacyBios,
										&HDDCount,
										&HDDInfo,
										&BBSCount,
										&BBSInfo
									);

    Handle = *(VOID**)(&(BBSInfo[Index].IBV1));
    if (Handle)
    {
        Status = gBS->HandleProtocol(Handle, &gEfiDevicePathProtocolGuid, &dpp);
        if(!EFI_ERROR(Status))
        {
            *DisDPs = MemReallocateZeroPool(*DisDPs, *DPSize, *DPSize + EfiDevicePathSize(dpp));
            MemCopy( ((UINT8 *)*DisDPs)+*DPSize, dpp, EfiDevicePathSize(dpp));
            *DPSize += EfiDevicePathSize(dpp);
        }
    }
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	GetBBSBootOptionName
//
// Description:	function to get the Boot option name.
//
// Input:		BOOT_DATA *bootData
//
// Output:		CHAR16* - BootOptionName
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

CHAR16 *GetBBSBootOptionName( BOOT_DATA *bootData)
{
    UINT16	offset = 0, count = 0, i;
    UINT8	*pDevOrder;
    UINTN	size = 0;
    BBS_ORDER_LIST	*BBSList = NULL;
    BBS_ORDER_TABLE	*pDev;

    BBSList = bootData->OrderList;
    count = bootData->LegacyDevCount;
    offset = (UINT16)bootData->LegacyEntryOffset;

	pDevOrder = HelperGetVariable(VARIABLE_ID_BBS_ORDER,L"LegacyDevOrder", &gLegacyDevGuid, NULL, &size);
	//EIP-75352 Suppress the warnings from static code analyzer
	if(NULL == pDevOrder)
		return NULL;
	
    if (IsBootOptionsGroupingEnabled ())
    {
		pDev = (BBS_ORDER_TABLE *)(pDevOrder + offset); //EIP-81402

		if ( (pDev->Length >= size) || (0 == pDev->Length) ) //EIP-120011
			return NULL;

        if (DISABLED_BOOT_OPTION == pDev->Data[0])  //For grouping only test for disable option
        {
            return  gBBSDisabled;
        }  
		
		for(i=0; i<count; i++)
		{
			if(BBSList[i].Index == pDev->Data[0])
				break;
		}
		if(i<count)
			return BBSList[i].Name;
	}
	else //EIP-81402 If GROUP_BOOT_OPTIONS_BY_TAG == 0 then retrun name
	{
		return BBSList->Name;
	}

    return bootData->Name;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	IsBBSDevicePath
//
// Description:	function to check for bbs device path support.
//
// Input:		EFI_DEVICE_PATH_PROTOCOL *DevicePath
//
// Output:		TRUE/FALSE
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
BOOLEAN IsBBSDevicePath( EFI_DEVICE_PATH_PROTOCOL *DevicePath )
{
	return (BOOLEAN)(
			( DevicePathType( DevicePath ) == BBS_DEVICE_PATH ) &&
			( DevicePathSubType( DevicePath ) == BBS_BBS_DP )
			);
}

//EIP-93797 Starts
//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	GetBBSOptionStatus
//
// Description:	function to get for bbs option status
//
// Input:		BOOT_DATA
//
// Output:		BOOLEAN
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
BOOLEAN GetBBSOptionStatus(BOOT_DATA *pBootData)
{
	UINT32 offset=0;
	UINT8 *pDevOrder;
	BBS_ORDER_TABLE	*pDev;
	UINTN size = 0;
	
 	offset = (UINT16)pBootData->LegacyEntryOffset;

  	pDevOrder = HelperGetVariable(VARIABLE_ID_BBS_ORDER,L"LegacyDevOrder", &gLegacyDevGuid, NULL, &size);

 	pDev = (BBS_ORDER_TABLE *)(pDevOrder + offset);

	if ( (pDev->Length >= size) || (0 == pDev->Length) ) //EIP-120011
		return TRUE;

	//if(((UINT8)pDev->Data[0] == (pBootData->OrderList->Index))&&(BBS_ORDER_DISABLE_MASK == (UINT8)((pDev->Data[0])>>8)))
	if(pDev->Data[0] & BBS_ORDER_DISABLE_MASK)
	{
		 MemFreePointer((VOID **) &pDevOrder);
		    return  TRUE;
	}
	else
	{
		 MemFreePointer((VOID **) &pDevOrder);
    		return  FALSE;
	}
}
//EIP-93797 Ends

//**********************************************************************
//**********************************************************************
//**                                                                  **
//**        (C)Copyright 1985-2011, American Megatrends, Inc.         **
//**                                                                  **
//**                       All Rights Reserved.                       **
//**                                                                  **
//**     5555 Oakbrook Pkwy, Building 200,Norcross, Georgia 30093     **
//**                                                                  **
//**                       Phone: (770)-246-8600                      **
//**                                                                  **
//**********************************************************************
//**********************************************************************
