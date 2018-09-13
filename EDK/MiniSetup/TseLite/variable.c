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
// $Archive: /Alaska/SOURCE/Modules/AMITSE2_0/AMITSE/TseLite/variable.c $
//
// $Author: Arunsb $
//
// $Revision: 34 $
//
// $Date: 2/11/14 8:44p $
//
//*****************************************************************//
//*****************************************************************//
// Revision History
// ----------------
// $Log: /Alaska/SOURCE/Modules/AMITSE2_0/AMITSE/TseLite/variable.c $
// 
// 34    2/11/14 8:44p Arunsb
// [TAG]	EIP135606
// [Category]	Bug Fix
// [Symptom:]	SAS Driver Issues.
// [Root Cause]	In the function CopyNvramVariableList, the buffered value
// for DynamicPageCount variable is updated from nvram when copying from
// one variable list to another variable list. 
// [Solution]	In the function CopyNvramVariableList, update the buffered
// value for DynamicPageCount from the cached value of the variable.
// [Files]	variable.c
// 
// 33    7/02/13 10:09a Premkumara
// [TAG]  		EIP120011
// [Category]  	Improvement
// [Description]  	Variable BootOrder and LegacyDevOrder need
// fool-proofing function when TSE load variabled
// [Files]  		Bbs.c, Boot.c, Callback.c, TseLiteHelper.c, Variable.c
// 
// 32    5/22/13 10:47a Arunsb
// General checks added
// 
// 31    10/18/12 6:02a Arunsb
// Updated for 2.16.1235 QA submission
// 
// 14    10/10/12 12:38p Arunsb
// Synched the source for v2.16.1232, backup with Aptio
// 
// 29    9/17/12 6:20a Rajashakerg
// Updated EIP changes for 2.16 release.
// 
// 27    9/11/12 3:40p Blaines
// [TAG] - EIP 100429
// [Category] - Function Request
// [Synopsis] -  "Save and exit" pop up message appear when viewing BBS
// priorities in BIOS menu
// [Root cause] - The function SetupConfigModifiedHook is called whenever
// a variable is modified from Setup.
// [Solution] - Prevent calls to SetupConfigModifiedHook for variables
// that don't affect setup changes.
// [Files] - Variable.c 
// 
// 26    8/29/12 8:52a Premkumara
// [TAG]  		EIP93954
// [Category]  	Bug Fix
// [Severity]  	Important
// [Symptom]  	Boot Options get corrupted on Loading defaults when
// TseDefaultBootOrder is added.
// [RootCause]  	Legacy dev order is not updated properly.
// [Solution]  	Restore Default issue
// [Files]  		variable.c
// 
// 25    5/09/12 7:39a Rajashakerg
// [TAG]  		EIP71351 
// [Category]  	Bug Fix
// [Severity]  	Normal
// [Symptom]  	System hangs with SETUP_RUNTIME_IFR_PROCESSING enabled and
// Intel GIG Undi driver
// [RootCause]  	The issue is occured when driver is loaded from shell the
// variable is not updated propely in setup
// [Solution]  	If the variable ist is null then clearing the cache values
// and updaitng the cache with new list
// [Files]  		variable.c
// 
// 24    4/27/12 7:52a Premkumara
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
// 23    1/24/12 4:42a Arunsb
// [TAG]  		EIP81581
// [Category]  	Improvement
// [Description]  	Default driver order support
// [Files]  		globals.c, addbootoption.c, callback.c, minisetupext.h and
// variable.c
// 
// 22    1/20/12 5:07a Rajashakerg
// [TAG]  		EIP77875 
// [Category]  	Improvement
// [Description]  	Minisetup: Memory leaks in text browser
// [Files]  		Uefi21Wapper.c, hiistring21.c, variable.c
// 
// 21    12/16/11 1:36a Arunsb
// [TAG]  		EIP76381
// [Category]  	Improvement
// [Description]  	Performance: Improving variable data load and usage.
//                                 Upto TSE entering into setup the
// variables are read from
//                                 NVRAM in setup it will read from
// temporary buffer. 
// 
// 20    12/05/11 5:43a Rajashakerg
// [TAG]  		EIP76381 
// [Category]  	Improvement
// [Description]  	Performance: Improving variable data load and usage
// [Files]  		callback.c, minisetupext.c, variable.c, variable.h,
// minisetup.h, Hii.c, FormBrowser2.c
// 
// 19    12/02/11 8:21a Arunsb
// [TAG]  		EIP75524
// [Category]  	Improvement
// 
// 18    11/30/11 11:29p Arunsb
// [TAG]  		EIP75588
// Build error correction
// 
// 17    11/30/11 1:31p Premkumara
// [TAG]  		EIP75352
// [Category]  	Improvement
// [Description]  	Suppress the warnings from static code analyzer
// [Files]  		Boot.c, bbs.c, TseAdvanced.c, Special.c, Variable.c,
// TseLiteHelper.c, PopupSel.c, AddBootOption.c, Hii.c, FormBrowser2.c
// 
// 16    11/30/11 6:39a Premkumara
// [TAG]  		EIP71351
// [Category]  	Bug Fix
// [Severity]  	Important
// [Symptom]  	Setup Crash when iSCSI is loaded
// [RootCause]  	Aptio giving length as 0xe(matches size of
// EFI_IFR_ONE_OF_OPTION) but in latest EDKII driver it is 0x1c.
// [Solution]  	change the length as j += ((EFI_IFR_OP_HEADER*)(buff + i +
// j))->Length;
// [Files]  		Parse.c, Hii.c, Variable.c, Minisetupext.c
// 
// 15    11/23/11 5:11a Rajashakerg
// [TAG]  		EIP75473 
// [Category]  	Improvement
// [Description]  	System Time is not updated every second
// [Files]  		variable.h, variable.c, FormBrowser2.c, TseUefiHii.h,
// Uefi21Wapper.c, hii.h, uefi20Wapper.c
// 
// 14    11/13/11 1:09p Arunsb
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
// 13    10/31/11 9:37a Rajashakerg
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
// 12    9/28/11 12:38p Arunsb
// [TAG]  		EIP69143
// [Category]  	Bug Fix
// [Severity]  	Important
// [Symptom]  	CPU exception
// [RootCause]  	Accessing gVariableList even it is NULL in
// VarUpdateVariable function.
// 
// [Solution]  	gVariableList initialized by calling VarLoadVariables
// [Files]  		TseLite\variable.c
// 
// 10    8/23/11 1:25p Arunsb
// In _VarUpdate function if VarGetNvram returns NULL then no need to
// update the buffer
// 
// 9     5/11/11 12:07p Madhans
// [TAG]  		EIP54219
// [Category]  	Bug Fix
// [Severity]  	Important
// [Symptom]  	Language Popup Control will not update correctly
// CHINESE_TRAD,CHINESE_SIMP used togather.
// [RootCause]  	The Current Language is not read from the NVRAM fully and
// compared. It was reading only 2 bytes for Lanugage comparition.
// [Solution]  	_VarGetRealValue function fixed to compare the Current
// Lang from NVRAM is read and compared with supported languages.
// [Files]  		variable.c
// 
// 8     3/23/11 8:38p Blaines
// [TAG] - EIP 23601
// [Category]- Enhancement
// [Symptom]- Add support for OEM special controls.
// [Files] - AmiTse.sdl, CommonHelper.c, Setup.ini, UefiSetup.ini,
// AmiVfr.h, minisetup.h, minisetup.sdl, variable.c, special.c
// 
// 7     1/07/11 12:23a Mallikarjunanv
// [TAG]  		EIP51619
// [Category]  	Bug Fix
// [Severity]  	Normal
// [Symptom]  	Changing the option in the "HDD BBS Priority" option not
// reflected in the boot options list. 
// [RootCause]  	Boot page is not updated properly with changes made by
// BBS HDD BBS Priority
// [Solution]  	Updated the boot page with changes made by  BBS HDD BBS
// Priority
// [Files]  		special.c, variable.c
// 
// 6     12/24/10 12:56p Mallikarjunanv
// [TAG]  		EIP 46296
// [Category]  	Bug Fix
// [Severity]  	Normal
// [Symptom]  	HDD BBS priority option having two same entries in its list
// (with 2 SATA HDD, 1 USB drive emulated as FDD) 
// [RootCause]  	The defaults for BBS order variable not initialized
// properly.
// [Solution]  	Fixed the issue by properly initializing the defaults for
// BBS order variable. 
// 
// [Files]  		variable.c
// 
// 5     9/16/10 8:38p Madhans
// Update for TSE 2.10. Refer Changelog.log for more details.
// 
// 9     9/13/10 4:43p Madhans
// BBSReOrderDefultLegacyDevOrder() function checks if the
// DefaultLegacyDevOrder can be considered or not. (if the device list is
// different from LegacyDevOrder then DefaultLegacyDevOrder is ignored.)
// on that case make the Size of gOptimalDefaults[ VARIABLE_ID_BBS_ORDER ]
// also 0.
// 
// 8     2/19/10 8:19a Mallikarjunanv
// updated year in copyright message
// 
// 7     2/18/10 8:26p Madhans
// To take care NOGET and NOSET Attribs from Exetendedflags of
// VariableInfo
// 
// 6     1/27/10 9:30a Mallikarjunanv
// EIP-24971: Tse features without tse sources support update for token
// SETUP_SUPPORT_PLATFORM_LANG_VAR 
// 
// 5     1/09/10 7:10a Mallikarjunanv
// Updated TSE2.01 Release sources with coding standards
// 
// 4     9/15/09 9:52a Sudhirv
// //to Ignore the DefaultLegacyDevOrder if is size is not matching with
// LegacyDevOder.
// 
// 3     6/23/09 6:53p Blaines
// Coding standard update, 
// Remove spaces from file header to allow proper chm function list
// creation.
// 
// 2     6/12/09 7:44p Presannar
// Initial implementation of coding standards for AMITSE2.0
// 
// 1     6/04/09 8:05p Madhans
// 
// 1     4/28/09 11:07p Madhans
// Tse 2.0 Code complete Checkin.
// 
// 4     4/28/09 9:40p Madhans
// Tse 2.0 Code complete Checkin.
// 
// 3     3/31/09 4:13p Madhans
// UEFI 2.1 Support
// 
// 2     1/30/09 6:06p Madhans
// Function headers added. 
// 
// 1     12/18/08 7:59p Madhans
// Intial version of TSE Lite sources
//*****************************************************************//
//*****************************************************************//

//<AMI_FHDR_START>
//----------------------------------------------------------------------------
//
// Name:		variable.c
//
// Description:	This file contains code to handle variable operations
//
//----------------------------------------------------------------------------
//<AMI_FHDR_END>

#include "minisetup.h"

extern UINTN gSetupCount;

//---------------------------------------------------------------------------
// Variables
//---------------------------------------------------------------------------
NVRAM_VARIABLE *gCurrNvramVarList = (NVRAM_VARIABLE *)NULL;
UINTN gCurrNvramVarCount = 0;

CHAR8 *gPrevLanguage;
UINTN gPrevLangSize = 0;
BOOLEAN gSetupUpdated = FALSE;//EIP:51619 Flag which represents the setup update 

#if SETUP_OEM_SPECIAL_CONTROL_SUPPORT
EFI_STATUS OEMSpecialUpdateOneOf(UINT16 newOption,UINT32 *offset,UINTN *size, VOID OUT **buffer);
#endif // SETUP_OEM_SPECIAL_CONTROL_SUPPORT

UINT8   IsBootOptionsGroupingEnabled (void); //EIP-93954 To Restore BootOption default issue

//EIP 76381 : START 
//<AMI_PHDR_START>
//---------------------------------------------------------------------------
// Procedure:   GetNvramVariableList
//
// Description: Gets all system variables
//
// Input:   NVRAM_VARIABLE **RetNvramVarList - Returns pointer to the var list
//
// Output:  EFI_STATUS status - EFI_SUCCESS if successful, else EFI_ERROR
//---------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS GetNvramVariableList(NVRAM_VARIABLE **RetNvramVarList)
{
    EFI_STATUS status = EFI_SUCCESS;
    NVRAM_VARIABLE *nvVarlist = (NVRAM_VARIABLE *)NULL;
    UINT32 index = 0;

    if ( (gCurrNvramVarList == NULL) || (gVariables->VariableCount != gCurrNvramVarCount) || (gPostStatus <= TSE_POST_STATUS_ENTERING_TSE))
	{
        gCurrNvramVarList = EfiLibAllocateZeroPool(gVariables->VariableCount * sizeof(NVRAM_VARIABLE));
        if(gCurrNvramVarList == NULL)
		{
            status = EFI_OUT_OF_RESOURCES;
            goto DONE;
        }

        // Get the Current Values from the NVRAM
        nvVarlist = gCurrNvramVarList;
        for(index = 0; index < gVariables->VariableCount; index++, nvVarlist++){
            nvVarlist->Buffer = VarGetNvram(index, &nvVarlist->Size);
            if ((0 != nvVarlist->Size) && (NULL == nvVarlist->Buffer))
            {
        	    nvVarlist->Buffer = EfiLibAllocateZeroPool (nvVarlist->Size);
            }
        }
        gCurrNvramVarCount = gVariables->VariableCount;
    }
    status = CopyNvramVariableList(gCurrNvramVarList, RetNvramVarList);
    
DONE:
    return status;
}

//<AMI_PHDR_START>
//---------------------------------------------------------------------------
// Procedure:   CleanTempNvramVariableList()
//
// Description: Clean up the current retrive variable list
//
// Input:   None
//
// Output:  VOID
//---------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID CleanTempNvramVariableList()
{
    NVRAM_VARIABLE *nvVarlist = (NVRAM_VARIABLE *)NULL;
    UINT32 index = 0;

    if(gCurrNvramVarList != NULL){
        nvVarlist = gCurrNvramVarList;
        for(index = 0; index < gCurrNvramVarCount; index++, nvVarlist++){
            MemFreePointer(&nvVarlist->Buffer);
        }        
    }
    gCurrNvramVarCount = 0;
    MemFreePointer(&gCurrNvramVarList);
    gCurrNvramVarList = (NVRAM_VARIABLE *)NULL;
}

//<AMI_PHDR_START>
//---------------------------------------------------------------------------
// Procedure:   CopyNvramVariableList
//
// Description: Copies variable buffer from one var list to another var list
//
// Input:   NVRAM_VARIABLE *SrcVarList - Source variable list
//          NVRAM_VARIABLE **DestVarList - Destination variable list
//
// Output:  EFI_STATUS status - EFI_SUCCESS if successful, else EFI_ERROR
//---------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS CopyNvramVariableList(NVRAM_VARIABLE *SrcVarList, NVRAM_VARIABLE **DestVarList)
{
    EFI_STATUS status = EFI_SUCCESS;
    UINT32 index = 0;
    NVRAM_VARIABLE *varPtr = (NVRAM_VARIABLE *)NULL;
    NVRAM_VARIABLE *currVarPtr = (NVRAM_VARIABLE *)NULL;

    *DestVarList = (NVRAM_VARIABLE *)EfiLibAllocateZeroPool(gVariables->VariableCount * sizeof(NVRAM_VARIABLE));
    if(*DestVarList == NULL){
        status = EFI_OUT_OF_RESOURCES;
        goto DONE;
    }

    varPtr = *DestVarList;
    currVarPtr = SrcVarList;
    for(index = 0; index < gVariables->VariableCount; index++, varPtr++, currVarPtr++)
    {
        if((varPtr->Buffer == NULL) && (currVarPtr != NULL) && (currVarPtr->Size != 0))
        {
            varPtr->Buffer = EfiLibAllocatePool(currVarPtr->Size);
            if(varPtr->Buffer == NULL){
                status = EFI_OUT_OF_RESOURCES;
                goto DONE;
            } else{
        	    if (currVarPtr->Buffer)
        	    {
        	            //EIP-135606: Update the buffered value for DynamicPageCount from the cache.
        	            if(index == VARIABLE_ID_DYNAMIC_PAGE_COUNT)
       	         	    		VarGetValue( VARIABLE_ID_DYNAMIC_PAGE_COUNT, 0, sizeof(UINT16), currVarPtr->Buffer );    
       	                MemCopy( varPtr->Buffer, currVarPtr->Buffer, currVarPtr->Size );        		    
        	    }
                varPtr->Size = currVarPtr->Size;
            }
        }
    }
DONE:
    return status;
}
//EIP 76381 : END

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	VarLoadVariables
//
// Description:	function to load the variables
//
// Input:	VOID **list, NVRAM_VARIABLE *defaultList
//
// Output:	status
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS VarLoadVariables( VOID **list, NVRAM_VARIABLE *defaultList )
{
	EFI_STATUS Status = EFI_SUCCESS;
	UINT32 index;

	NVRAM_VARIABLE *varPtr;
	NVRAM_VARIABLE *defaultVar = defaultList;

	if(*list != NULL)//EIP 71351 : If the list is null then clearing the cache values and updaitng the cache with new list
		CleanTempNvramVariableList();
	MemFreePointer( (VOID **)list );

	if( ( ! gVariables ) || ( gVariables->VariableCount == 0 ) )	// fatal error
		while(1);

	Status = GetNvramVariableList((NVRAM_VARIABLE **)list);
    if(EFI_ERROR(Status)){
        goto DONE;//EIP 76381 :Performance Improving of variable data load and usage
    }

	varPtr = *list;
	for ( index = 0; index < gVariables->VariableCount; index++, varPtr++, defaultVar++ )
	{
		if ( ( varPtr->Buffer == NULL ) && ( defaultList != NULL ) && ( defaultVar->Size != 0 ) )
		{
			varPtr->Buffer = EfiLibAllocatePool( defaultVar->Size );
			if ( varPtr->Buffer == NULL )
				Status = EFI_OUT_OF_RESOURCES;
			else
			{
				MemCopy( varPtr->Buffer, defaultVar->Buffer, defaultVar->Size );
				varPtr->Size = defaultVar->Size;
			}
		}

		if ( varPtr->Buffer == NULL ) // If varPtr->Buffer is still NULL Skip the variable.
			continue;		

        //Introduce DISABLED_BOOT_OPTION in place of disabled options
        //for mem copy of BootOrder and BBSOrder
        if(gBootData && (VARIABLE_ID_BOOT_ORDER == index))
        {
            UINT16 *BootOrder = (UINT16 *)varPtr->Buffer;
            BOOT_DATA *pBootData;
            UINTN i;

            for(i=0; i<(varPtr->Size / sizeof(UINT16)); i++)
            {
                pBootData = BootGetBootData(BootOrder[i]); //Should yield a valid option
				if(NULL != pBootData)			//EIP-75352 Suppress the warnings from static code analyzer
				{
					if ( (!(pBootData->Active & LOAD_OPTION_ACTIVE)) && (!(pBootData->Active & LOAD_OPTION_HIDDEN)) )
                    	BootOrder[i] = DISABLED_BOOT_OPTION;
				}
            }
        }
        //Introduce DISABLED_DRIVER_OPTION in place of disabled options
        //Change the DriverOrder cache
        else if (gDriverData && (VARIABLE_ID_DRIVER_ORDER == index))		//EIP70421 & 70422  Support for driver order
        {
            UINT16 *DriverOrder = (UINT16 *)varPtr->Buffer;
            BOOT_DATA *pDriverData;
            UINTN i;

            for (i = 0; i < (varPtr->Size / sizeof (UINT16)); i++)
            {
				pDriverData = DriverGetDriverData (DriverOrder[i]); //Should yield a valid option
				if (pDriverData)
				{
					if ( (!(pDriverData->Active & LOAD_OPTION_ACTIVE)) && (!(pDriverData->Active & LOAD_OPTION_HIDDEN)) )
						DriverOrder [i] = DISABLED_DRIVER_OPTION;
				}
            }
        }
        else if(VARIABLE_ID_BBS_ORDER == index)
        {
            BBS_ORDER_TABLE *TypeEntry, *TSEDevOrder = (BBS_ORDER_TABLE *) varPtr->Buffer;
            UINTN i,j,count;

            TypeEntry = TSEDevOrder;
            for(i=0; i < varPtr->Size;)
            {
					if ( ( TypeEntry->Length >= varPtr->Size) || (0 == TypeEntry->Length) ) //EIP-120011
					{
               	break;
					}

					count = TypeEntry->Length / sizeof(UINT16) - 1;

                for(j=0; j < count; j++)
                {
                    if(TypeEntry->Data[j] & BBS_ORDER_DISABLE_MASK)
                        TypeEntry->Data[j] = DISABLED_BOOT_OPTION;
                }
        
					count = sizeof(UINT32) + TypeEntry->Length;
        			TypeEntry = (BBS_ORDER_TABLE *)((UINTN)TypeEntry + count);
					i += count;
            }
        }
	}

DONE:
	return Status;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	VarBuildDefaults
//
// Description:	function to build the default variables
//
// Input:	VOID
//
// Output:	status
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS VarBuildDefaults( VOID )
{
	EFI_STATUS Status;

	UINT8 *newBuffer = NULL;
	UINT8 *DefDrvBuffer = NULL;
	UINTN size = 0;

	Status = VarBuildAMIDefaults();

	if(Status == EFI_UNSUPPORTED)
	{
		Status = HiiLoadDefaults( (VOID **)&gFailsafeDefaults,(UINT32) HiiGetManufactuingMask() ); // Allocates Space and filles
		if ( EFI_ERROR( Status ) )
			return Status;
	
		Status = HiiLoadDefaults( (VOID **)&gOptimalDefaults, (UINT32) HiiGetDefaultMask() ); // Allocates Space and filles
		if ( EFI_ERROR( Status ) )
			return Status;

	}

	//EIP-46296: reset default values of BBS order variable.
	if ( gOptimalDefaults[ VARIABLE_ID_BOOT_ORDER ].Buffer != NULL ) {
		MemFreePointer( (VOID **) &gOptimalDefaults[ VARIABLE_ID_BOOT_ORDER ].Buffer );
	}
	if ( gOptimalDefaults[ VARIABLE_ID_DRIVER_ORDER ].Buffer != NULL ) {				//EIP70421 & 70422  Support for driver order
		MemFreePointer( (VOID **) &gOptimalDefaults[ VARIABLE_ID_DRIVER_ORDER ].Buffer );
	}
	gOptimalDefaults[ VARIABLE_ID_BBS_ORDER ].Buffer = gOptimalDefaults[ VARIABLE_ID_BOOT_ORDER ].Buffer = gOptimalDefaults[ VARIABLE_ID_DRIVER_ORDER ].Buffer = NULL;
	gOptimalDefaults[ VARIABLE_ID_BBS_ORDER ].Size = gOptimalDefaults[ VARIABLE_ID_BOOT_ORDER ].Size = gOptimalDefaults[ VARIABLE_ID_DRIVER_ORDER ].Size = 0;

	if ( gFailsafeDefaults[ VARIABLE_ID_BBS_ORDER ].Buffer != NULL ) {
		MemFreePointer( (VOID **) &gFailsafeDefaults[ VARIABLE_ID_BBS_ORDER ].Buffer );
	}
	if ( gFailsafeDefaults[ VARIABLE_ID_DRIVER_ORDER ].Buffer != NULL ) {
		MemFreePointer( (VOID **) &gFailsafeDefaults[ VARIABLE_ID_DRIVER_ORDER ].Buffer );
	}

	gFailsafeDefaults[ VARIABLE_ID_BBS_ORDER ].Buffer = gFailsafeDefaults[ VARIABLE_ID_BOOT_ORDER ].Buffer = gFailsafeDefaults[ VARIABLE_ID_DRIVER_ORDER ].Buffer = NULL;
	gFailsafeDefaults[ VARIABLE_ID_BBS_ORDER ].Size = gFailsafeDefaults[ VARIABLE_ID_BOOT_ORDER ].Size = gFailsafeDefaults[ VARIABLE_ID_DRIVER_ORDER ].Size = 0;

	// special provision for language
	//VarGetValue( VARIABLE_ID_LANGUAGE, 0, 3, gPrevLanguage );
	gPrevLanguage = VarGetNvram ( VARIABLE_ID_LANGUAGE, &gPrevLangSize );

    //Special provision for "Boot order" and "Legacy dev order"
	size = 0;
	newBuffer = VarGetNvramName ( L"DefaultBootOrder", &EfiDefaultBootOrderGuid, NULL, &size );
	if(newBuffer)
	{
		MemFreePointer( (VOID **) &gOptimalDefaults[ VARIABLE_ID_BOOT_ORDER ].Buffer );
		gOptimalDefaults[ VARIABLE_ID_BOOT_ORDER ].Buffer = (UINT8 *)newBuffer;
		gOptimalDefaults[ VARIABLE_ID_BOOT_ORDER ].Size = size;
	}
	size = 0;				//EIP81581 Default driver order support
	DefDrvBuffer = VarGetNvramName (L"DefaultDriverOrder", &EfiDefaultDriverOrderGuid, NULL, &size);
	if (DefDrvBuffer)
	{
		MemFreePointer ((VOID **) &gOptimalDefaults [VARIABLE_ID_DRIVER_ORDER].Buffer);
		gOptimalDefaults [VARIABLE_ID_DRIVER_ORDER].Buffer = (UINT8 *)DefDrvBuffer;
		gOptimalDefaults [VARIABLE_ID_DRIVER_ORDER].Size = size;
	}	
	CsmLoadDefaultLegDevOrder();
	LoadedBuildDefaultsHook();

	return Status;
}
//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	LoadDefaultLegDevOrder
//
// Description:	Function to load default legacy boot order
//
// Input:		VOID
//
// Output:		VOID
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID LoadDefaultLegDevOrder(VOID)
{
	UINT8 *newBuffer = NULL;
	UINTN size = 0;

	newBuffer = VarGetNvramName( L"DefaultLegacyDevOrder", &EfiDefaultLegacyDevOrderGuid, NULL, &size );
	if(newBuffer)
	{
        MemFreePointer( (VOID **)&gOptimalDefaults[ VARIABLE_ID_BBS_ORDER ].Buffer );
		gOptimalDefaults[ VARIABLE_ID_BBS_ORDER ].Buffer = BBSReOrderDefultLegacyDevOrder((BBS_ORDER_TABLE *)newBuffer,size);
		//Ignore the DefaultLegacyDevOrder if is size is not matching with LegacyDevOder.
		if(gOptimalDefaults[ VARIABLE_ID_BBS_ORDER ].Buffer == NULL)
			size = 0;
		gOptimalDefaults[ VARIABLE_ID_BBS_ORDER ].Size = size;
		MemFreePointer(&newBuffer);
	}
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	VarGetNvram
//
// Description:	function to get the NvRam varible names
//
// Input:	UINT32 variable, UINTN *size
//
// Output:	void
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID *VarGetNvram( UINT32 variable, UINTN *size )
{
	VOID *buffer = NULL;
	VARIABLE_INFO *varInfo;
	EFI_STATUS status = EFI_SUCCESS;

	*size = 0;

	varInfo = VarGetVariableInfoIndex( variable );
	if ( varInfo == NULL )
		return buffer;

	if((varInfo->ExtendedAttibutes & AMI_SPECIAL_VARIABLE_NO_GET) == AMI_SPECIAL_VARIABLE_NO_GET)
	{
		// Don't read from the NVRAM
		// But in the Init we may need to take care return empty buffer
		NVRAM_VARIABLE *list = gVariableList;
		NVRAM_VARIABLE *nvVar;
		if(gVariableList != NULL)
		{
			nvVar = &list[ variable ];
			if((nvVar!=NULL)&&(nvVar->Size!=0))
			{
				*size = nvVar->Size;
				//This function Suppose allocate and give the buffer
				buffer = EfiLibAllocateZeroPool( *size );
				if(nvVar->Buffer != NULL)
					MemCopy( buffer, nvVar->Buffer, *size );
				return buffer;
			}
		}
		// If Local catch is not found Just return null.
		*size = 0;
		return buffer;
	}

	if(UefiIsEfiVariable(variable,varInfo))
	{
		*size = 0;
    	if(varInfo->VariableAttributes == 0)
      		varInfo->VariableAttributes = 0x07;
			buffer = VarGetNvramName( varInfo->VariableName, &varInfo->VariableGuid, &varInfo->VariableAttributes, size );
	}
	else
	{
		{
			if((varInfo->ExtendedAttibutes & VARIABLE_ATTRIBUTE_VARSTORE) == VARIABLE_ATTRIBUTE_VARSTORE)
				*size = varInfo->VariableSize;
			status = UefiVarGetNvram(varInfo, &buffer, VAR_ZERO_OFFSET, *size);
			if(EFI_ERROR(status))
			{
				*size = 0;
			}
		}
	}
	return buffer;
}

//<AMI_PHDR_START>
//---------------------------------------------------------------------------
// Procedure:   VarGetNvramQuestionValue
//
// Description: Gets the question value buffer from a specific offset of a
//              variable buffer
//
// Input:   UINT32 variable
//          UINTN offset
//          UINTN *size
//
// Output:  VOID *buffer - Question value buffer
//---------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID *VarGetNvramQuestionValue(UINT32 variable, UINTN Offset, UINTN Size)
{
    VOID *buffer = (VOID *)NULL;
    VARIABLE_INFO *varInfo = (VARIABLE_INFO *)NULL;
    EFI_STATUS status = EFI_SUCCESS;

    varInfo = VarGetVariableInfoIndex( variable );
    if ( varInfo == NULL )
    return buffer;
//EIP 77875 : Minisetup: Memory leaks in text browser
    if(UefiIsEfiVariable(variable,varInfo))
    {
        UINTN size = 0;
        UINT8 *tempBuffer = NULL;
   
		buffer = EfiLibAllocateZeroPool(Size+1);
   		if(buffer == NULL)
    	{
     		status = EFI_OUT_OF_RESOURCES;
      		goto DONE;
    	}

        if(varInfo->VariableAttributes == 0){
            varInfo->VariableAttributes = 0x07;
        }
        tempBuffer = VarGetNvramName( varInfo->VariableName, &varInfo->VariableGuid, &varInfo->VariableAttributes, &size );
        if(tempBuffer != NULL && size != 0)
        {
            if((Offset + Size) > size)
            {
                status = EFI_INVALID_PARAMETER;
                goto DONE;
            }
            MemCopy(buffer, &tempBuffer[Offset], Size);
            MemFreePointer(&tempBuffer);
        }
    }
    else
    {
        {
        if((varInfo->ExtendedAttibutes & VARIABLE_ATTRIBUTE_VARSTORE) == VARIABLE_ATTRIBUTE_VARSTORE)
            if((Offset + Size) > varInfo->VariableSize)
            {
                status = EFI_INVALID_PARAMETER;
                goto DONE;
            }
            status = UefiVarGetNvram(varInfo, &buffer, Offset, Size);
        }
    }
DONE:
    return buffer;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	VarSetNvram
//
// Description:	function to set the NvRam varible names
//
// Input:	UINT32 variable, VOID *buffer, UINTN *size
//
// Output:	status
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS VarSetNvram( UINT32 variable, VOID *buffer, UINTN size )
{
    EFI_STATUS Status = EFI_INVALID_PARAMETER;
    VARIABLE_INFO *varInfo = (VARIABLE_INFO *)NULL;

    if(buffer == NULL)
    {
        goto DONE;
    }

    varInfo = VarGetVariableInfoIndex(variable);
    if(varInfo == NULL)
    {
        goto DONE;
    }

	if((varInfo->ExtendedAttibutes & AMI_SPECIAL_VARIABLE_NO_SET) == AMI_SPECIAL_VARIABLE_NO_SET)
	{
		// Don't save the variable
		Status = EFI_SUCCESS;
	}
	else
	{
		if(UefiIsEfiVariable(variable,varInfo))
		{
			Status = VarSetNvramName( varInfo->VariableName, &varInfo->VariableGuid, varInfo->VariableAttributes, buffer, size );
		}
		else
		{
			Status = UefiVarSetNvram(varInfo, buffer, VAR_ZERO_OFFSET, size);
		}
	}
	if ( ! EFI_ERROR( Status ) )
    {
        VarUpdateVariable(variable);
    }

DONE:
    return Status;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	_VarGetRealValue
//
// Description:	function to get the real value of the variable
//
// Input:	UINT32 variable, UINTN offset, UINTN size, VOID *buffer
//
// Output:	status
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS _VarGetRealValue( UINT32 variable, UINTN offset, UINTN size, VOID *buffer )
{
	EFI_STATUS Status = EFI_SUCCESS;
	UINTN i;

	switch ( variable )
	{
		case VARIABLE_ID_LANGUAGE:
			{
                UINTN varsize=0;
        		VOID * LangBuf = VarGetNvram( variable, &varsize ); // Read the Variable from Variable Service
				for ( i = 0; i < gLangCount; i++ )
				{
					if ( ! EfiCompareMem( LangBuf, gLanguages[i].LangCode, varsize ) )
					{
						MemSet( buffer, size, 0 );
						*(UINT16 *)buffer = (UINT16)i;
						break;
					}
				}
        		MemFreePointer(&LangBuf);
        	}
			break;

        default:
			break;
	}

	return Status;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	_VarSetRealValue
//
// Description:	function to set the real value of the variable
//
// Input:	UINT32 variable, UINT32 *offset, UINTN *size,
//					VOID *buffer, VOID **realBuffer
//
// Output:	status
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS _VarSetRealValue( UINT32 variable, UINT32 *offset, UINTN *size, VOID *buffer, VOID **realBuffer )
{
	EFI_STATUS Status = EFI_SUCCESS;
	UINT16 index = *(UINT16 *)buffer;

	if ( variable == VARIABLE_ID_SETUP )
	{
		Status = EFI_UNSUPPORTED;
		return Status;
	}
	if (VARIABLE_ID_BOOT_ORDER == variable)
		*size = gBootOptionCount * sizeof(UINT16);
	
	if (VARIABLE_ID_DRIVER_ORDER == variable)				//EIP70421 & 70422  Support for driver order
		*size = gDriverOptionCount * sizeof(UINT16);
	
	*realBuffer = EfiLibAllocateZeroPool( *size );
	if ( *realBuffer == NULL )
	{
		Status = EFI_OUT_OF_RESOURCES;
		return Status;
	}

	switch ( variable )
	{
		case VARIABLE_ID_LANGUAGE:
			{
				if ( index > gLangCount )
					Status = EFI_INVALID_PARAMETER;
				else
				{
					///EIP-24971:Removed the Token SETUP_SUPPORT_PLATFORM_LANG_VAR dependency from TSE sources
					if( PlatformLangVerSupport() ) {	
				        	MemFreePointer( (VOID **)realBuffer );
				        	*size = StrLen8(gLanguages[index].LangCode) +1;
				        	*realBuffer = EfiLibAllocateZeroPool( *size );
					}
					else {
				        	*size = 3;
					}

					MemCopy( *realBuffer, gLanguages[index].LangCode, *size );
				}
			}
			break;
		case VARIABLE_ID_BOOT_ORDER:
   			MemFreePointer ((VOID **)realBuffer);
			BootUpdateOrder (buffer, offset, size, realBuffer);
			break;
		case VARIABLE_ID_DRIVER_ORDER:								//EIP70421 & 70422  Support for driver order
			MemFreePointer ((VOID **)realBuffer);
			DriverUpdateOrder (buffer, offset, size, realBuffer);
			break;
        case VARIABLE_ID_BBS_ORDER:
   			MemFreePointer( (VOID **)realBuffer );
			//BBSUpdateOrder( /*index*/buffer, offset, size, realBuffer );
			Status = CsmBBSUpdateOrder(buffer, offset, size, realBuffer);
            break;

#if SETUP_OEM_SPECIAL_CONTROL_SUPPORT
        case VARIABLE_ID_OEM_TSE_VAR:
   			MemFreePointer( (VOID **)realBuffer );
			Status = OEMSpecialUpdateOneOf( index, offset, size, realBuffer );
            break;
#endif

		default:
			MemFreePointer( (VOID **)realBuffer );
			Status = EFI_INVALID_PARAMETER;
			break;
	}

	return Status;
}
//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	VarGetValue
//
// Description:	Function to get var value
//
// Input:		UINT32 variable, UINT32 offset, UINTN size, VOID *buffer
//
// Output:		STATUS
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS VarGetValue( UINT32 variable, UINT32 offset, UINTN size, VOID *buffer )
{
	return _VarGetData( variable, offset, size, buffer, FALSE );
}
//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	VarGetDefaults
//
// Description:	Function to get var defaults
//
// Input:		UINT32 variable, UINT32 offset, UINTN size, VOID *buffer
//
// Output:		STATUS
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS VarGetDefaults( UINT32 variable, UINT32 offset, UINTN size, VOID *buffer )
{
	return _VarGetData( variable, offset, size, buffer, TRUE );
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	_VarGetData
//
// Description:	function to get variable data
//
// Input:	UINT32 variable, UINT32 offset, UINTN size,
//					VOID *buffer, BOOLEAN useDefaults
//
// Output:	status
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS _VarGetData( UINT32 variable, UINT32 offset, UINTN size, VOID *buffer, BOOLEAN useDefaults )
{
	UINT32 TempOffset =offset;
    EFI_STATUS Status = EFI_SUCCESS;

	NVRAM_VARIABLE *list = gVariableList;

	if ( ( useDefaults ) || ( list == NULL ) )
		list = gOptimalDefaults;

	Status = _VarGetSetValue( VAR_COMMAND_GET_VALUE, list, variable, TempOffset, size, buffer );

	if ( ! EFI_ERROR( Status ) )
		Status = _VarGetRealValue( variable, offset,size, buffer );

	return Status;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	VarSetValue
//
// Description:	Function to set variable value
//
// Input:		UINT32 variable, UINT32 offset, UINTN size, VOID *buffer
//					
//
// Output:	status
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS VarSetValue( UINT32 variable, UINT32 offset, UINTN size, VOID *buffer )
{
	EFI_STATUS Status = EFI_SUCCESS;
	VOID *realBuffer = (VOID *)NULL;

	Status = _VarSetRealValue( variable, &offset, &size, buffer, &realBuffer );
	if ( EFI_ERROR( Status ) )
		realBuffer = buffer;

	Status = _VarGetSetValue( VAR_COMMAND_SET_VALUE, gVariableList, variable, offset, size, realBuffer );

	if ( ( variable == VARIABLE_ID_LANGUAGE ) && ( ! EFI_ERROR( Status ) ) )
	{
		if (NULL != gApp)
		{
        gApp->CompleteRedraw = TRUE;
		}
		Status = VarSetNvram( variable, realBuffer, size );
	}

    if ( realBuffer != buffer )
		MemFreePointer( (VOID **)&realBuffer );
	
    //EIP:100429 Prevent calls to SetupConfigModifiedHook for variables that don't affect setup changes. 
    if(!(
    		//variable == VARIABLE_ID_SETUP			    	||
    		//variable == VARIABLE_ID_LANGUAGE		    	||
    		//variable == VARIABLE_ID_BOOT_TIMEOUT	   		 ||
    		//variable == VARIABLE_ID_USER_DEFAULTS	   		 ||
    		variable == VARIABLE_ID_ERROR_MANAGER	   		 ||
    		//variable == VARIABLE_ID_AMITSESETUP      		 ||
    		//variable == VARIABLE_ID_IDE_SECURITY      		 ||
    		//variable == VARIABLE_ID_BOOT_ORDER       		 ||
    		//variable == VARIABLE_ID_BBS_ORDER           	 ||
    		variable == VARIABLE_ID_DEL_BOOT_OPTION     	 ||
    		variable == VARIABLE_ID_ADD_BOOT_OPTION     	 ||
    		variable == VARIABLE_ID_BOOT_MANAGER        	 ||
    		variable == VARIABLE_ID_BOOT_NOW            	 ||
    		variable == VARIABLE_ID_LEGACY_DEV_INFO     	 ||
    		variable == VARIABLE_ID_AMI_CALLBACK        	 ||
    		variable == VARIABLE_ID_LEGACY_GROUP_INFO   	 ||
    		variable == VARIABLE_ID_OEM_TSE_VAR		    	 ||
    		variable == VARIABLE_ID_DYNAMIC_PAGE_COUNT		 ||
    		variable == VARIABLE_ID_DRV_HLTH_ENB			 ||
    		variable == VARIABLE_ID_DRV_HLTH_COUNT			 ||
    		variable == VARIABLE_ID_DRIVER_MANAGER			 ||
    		//variable == VARIABLE_ID_DRIVER_ORDER			 ||
    		variable == VARIABLE_ID_ADD_DRIVER_OPTION   	 ||
    		variable == VARIABLE_ID_DEL_DRIVER_OPTION   	 ||
    		variable == VARIABLE_ID_PORT_OEM1				 ||
    		variable == VARIABLE_ID_PORT_OEM2				 ||
    		variable == VARIABLE_ID_PORT_OEM3				 ||
    		variable == VARIABLE_ID_PORT_OEM4				 ||
    		variable == VARIABLE_ID_PORT_OEM5				))
    	{
    		/// Hook can be used after a control is modified...
    		SetupConfigModifiedHook();
            gSetupUpdated = TRUE;//EIP:51619 Flag is Set when any of the setup variable is set
    	}

	

	return Status;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	_VarGetSetValue
//
// Description:	intermediate function for the set and get operations
//
// Input:	UINTN command, NVRAM_VARIABLE *list, UINT32 variable,
//					UINT32 offset, UINTN size, VOID *buffer
//
// Output:	status
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS _VarGetSetValue( UINTN command, NVRAM_VARIABLE *list, UINT32 variable, UINT32 offset, UINTN size, VOID *buffer )
{
	EFI_STATUS Status = EFI_INVALID_PARAMETER;
	NVRAM_VARIABLE *varInfo;

	if ( ( variable >= gVariables->VariableCount ) || ( buffer == NULL ) || ( size == 0 ) )
		return Status;

	varInfo = &list[ variable ];

	if ( ( command == VAR_COMMAND_SET_VALUE ) && ( varInfo->Buffer == NULL ) )
	{
		varInfo->Buffer = EfiLibAllocateZeroPool( offset + size );
		if ( varInfo->Buffer != NULL )
			varInfo->Size = offset + size;
	}

	if ( varInfo->Size == 0 )
	{
		varInfo->Buffer = VarGetNvram( variable, &varInfo->Size );
		if ( varInfo->Buffer == NULL )
			return Status;
	}

	if ( offset + size > varInfo->Size )
	{
		if ( command == VAR_COMMAND_SET_VALUE )
		{
			UINT8 *newBuffer;

			newBuffer = EfiLibAllocateZeroPool( offset + size );
			if ( newBuffer == NULL )
				return Status;
			MemCopy( newBuffer, varInfo->Buffer, varInfo->Size );
			MemFreePointer( (VOID **)&varInfo->Buffer );
			varInfo->Buffer = newBuffer;
			varInfo->Size = offset + size;
		}
	}

	if ( command == VAR_COMMAND_GET_VALUE )
    {
       	MemSet( buffer, size, 0 );
    	if ( offset + size > varInfo->Size )
            size = varInfo->Size - offset;
    	if ( varInfo->Size > offset )
    		MemCopy( buffer, &varInfo->Buffer[offset], size );
    }
	else
		MemCopy( &varInfo->Buffer[offset], buffer, size );

	Status = EFI_SUCCESS;

	return Status;

}
//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	_VarUpdate
//
// Description:	Function to update variable
//
// Input:		NVRAM_VARIABLE *nvramVar, UINT32 variable
//					
//
// Output:		VOID
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID _VarUpdate(NVRAM_VARIABLE *nvramVar, UINT32 variable)
{
	UINT8 *newBuffer;
	UINTN nvSize;
	
	newBuffer = (UINT8 *)VarGetNvram( variable, &nvSize );
	if (NULL == newBuffer)				//No need to update the buffer if it is NULL
	{
		return;
	}
	MemFreePointer( (VOID **)&nvramVar->Buffer );
	nvramVar->Buffer = newBuffer;
	nvramVar->Size = nvSize;
}
//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	VarUpdateVariable
//
// Description:	Function to update variable
//
// Input:		UINT32 variable
//					
//
// Output:		VOID
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID VarUpdateVariable(UINT32 variable)
{
	NVRAM_VARIABLE 	*nvramVar;
    EFI_STATUS 		Status = EFI_SUCCESS;

    if (NULL == gVariableList) 
        Status = VarLoadVariables ((VOID **)&gVariableList, NULL);
    if (EFI_ERROR (Status))
        return;
	nvramVar = &gVariableList[ variable ];
	_VarUpdate(nvramVar, variable);
}
//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	VarUpdateDefaults
//
// Description:	Function to update variable defaults
//
// Input:		UINT32 variable
//					
//
// Output:		VOID
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID VarUpdateDefaults(UINT32 variable)
{
	NVRAM_VARIABLE *nvramVar;
	nvramVar = &gFailsafeDefaults[ variable ];
	_VarUpdate(nvramVar, variable);
	nvramVar = &gOptimalDefaults[ variable ];
	_VarUpdate(nvramVar, variable);
}
//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	VarUpdateDefaults
//
// Description:	Function to get variable 
//
// Input:		UINT32 variable, UINTN *size 
//					
//
// Output:		VOID*
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID *VarGetVariable( UINT32 variable, UINTN *size )
{
	VOID *buffer = NULL;
	NVRAM_VARIABLE *nvramVar;

	if ( variable >= gVariables->VariableCount )
		return buffer;
	
	if(gVariableList == NULL)
		return buffer;

	nvramVar = &gVariableList[ variable ];
	if ( nvramVar == NULL )
		return buffer;

	if ( ( *size == 0 ) || ( *size > nvramVar->Size ) )
		*size = nvramVar->Size;

	if(*size == 0)
		return buffer;

	buffer = EfiLibAllocateZeroPool( *size );
	if ( ( buffer != NULL ) && ( nvramVar->Buffer != NULL ) )
		MemCopy( buffer, nvramVar->Buffer, *size );
	else
		*size = 0;

	return buffer;
}
//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	VarGetVariableInfoIndex
//
// Description:	Function to get variable info index
//
// Input:		UINT32 index 
//					
//
// Output:		VARIABLE_INFO *
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
VARIABLE_INFO *VarGetVariableInfoIndex( UINT32 index )
{
	VARIABLE_INFO *varInfo = NULL;

	if ( index < gVariables->VariableCount )
		varInfo = (VARIABLE_INFO *)((UINT8 *)gVariables + gVariables->VariableList[index]);

	return varInfo;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	VarGetVariableInfoId
//
// Description:	function to get the ID of the variable information
//
// Input:	UINTN command, NVRAM_VARIABLE *list, UINT32 variable,
//					UINT32 offset, UINTN size, VOID *buffer
//
// Output:	Variable Info
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
VARIABLE_INFO *VarGetVariableInfoId( UINT32 varId, UINT32 *index )
{
	VARIABLE_INFO *varInfo = NULL;
	UINT32 i;

	for ( i = 0; i < gVariables->VariableCount; i++, varInfo++ )
	{
		varInfo = VarGetVariableInfoIndex( i );
		if ( NULL != varInfo && varInfo->VariableID == varId)//EIP-75352 Suppress the warnings from static code analyzer
		{
			if ( index != NULL )
				*index = i;
			return varInfo;
		}
	}

	varInfo = NULL;
	return varInfo;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   BBSReOrderDefultLegacyDevOrder
//
// Description: To reoder the DefaultLegacyDevOrder Variable as TSE reorders 
//				the LegacyDevOrder based on Boot Order
//
// Input:       DefaultLegDevOrder and DefaultLegDevOrderSize
//
// Output:      NewDefultLegacyDevOrder
//				NULL = if DefaultLegDevOrderSize is not Equal with LegacuDevOrderSize
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID *BBSReOrderDefultLegacyDevOrder(BBS_ORDER_TABLE *DefaultLegDevOrder,UINTN DefaultLegDevOrderSize)
{
	BBS_ORDER_TABLE * LegacyDevOrder,*NewDefultLegacyDevOrder,*TempDevOrder,*NewDevEntry;
	UINTN LegacyOrderSize=0;
	UINTN count=0;
	UINTN i,j;
	
	LegacyDevOrder = VarGetNvramName( L"LegacyDevOrder", &gLegacyDevGuid, NULL, &LegacyOrderSize );

	// If the DefaultLegacyDevOrderSize is not Matching with LegacyDevOrderSize (EIP-25288)
	if(LegacyOrderSize != DefaultLegDevOrderSize)
		return NULL;

	if(DefaultLegDevOrderSize && LegacyDevOrder)
		NewDefultLegacyDevOrder = EfiLibAllocateZeroPool( DefaultLegDevOrderSize);
	else 
		return NULL;

	NewDevEntry = NewDefultLegacyDevOrder;
	for(j=0; j<LegacyOrderSize; )
 	{
		TempDevOrder = DefaultLegDevOrder;
		for(i=0;i<DefaultLegDevOrderSize;)
		{
			if ( (0 == TempDevOrder->Length) || (TempDevOrder->Length >= DefaultLegDevOrderSize) ) //EIP-120011
			{
				return NULL;
			}
			
			count = sizeof(UINT32) + TempDevOrder->Length;
			
			//If GROUP_BOOT_OPTIONS_BY_TAG is enable
			if ( LegacyDevOrder->Type == TempDevOrder->Type && IsBootOptionsGroupingEnabled() ) //EIP-93954 To Restore BootOption default issue
			{
				MemCopy(NewDevEntry,TempDevOrder,count); //Copying default legacyDevOrder
				NewDevEntry = (BBS_ORDER_TABLE *)((UINTN)NewDevEntry + count);							
				break;
			}
			//If GROUP_BOOT_OPTIONS_BY_TAG is disable
			else
			{
				if ( (LegacyDevOrder->Type == TempDevOrder->Type) && (LegacyDevOrder->Data[0] == TempDevOrder->Data[0]) )
				{
					MemCopy(NewDevEntry,TempDevOrder,count); //Copying default legacyDevOrder
					NewDevEntry = (BBS_ORDER_TABLE *)((UINTN)NewDevEntry + count);							
					break;
				}
			}

			TempDevOrder = (BBS_ORDER_TABLE *)((UINTN)TempDevOrder + count);
            i += count;
		}

		//Go to next entry
  		count = sizeof(UINT32) + LegacyDevOrder->Length;
    	LegacyDevOrder = (BBS_ORDER_TABLE *)((UINTN)LegacyDevOrder + count);
     	j += count;
	}
	
	if(((UINTN)NewDevEntry - (UINTN)NewDefultLegacyDevOrder) != LegacyOrderSize)
		// Something wrong in the Variables. Lets just use LegacyDevOrder
		MemCopy(NewDefultLegacyDevOrder,LegacyDevOrder,LegacyOrderSize);

	return NewDefultLegacyDevOrder;
}
//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	HelperGetVariable
//
// Description:	Function helper to get variable
//
// Input:		UINT32 variable, CHAR16 *name, EFI_GUID *guid, UINT32 *attributes, UINTN *size
//					
//
// Output:		VOID *
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID * HelperGetVariable( UINT32 variable, CHAR16 *name, EFI_GUID *guid, UINT32 *attributes, UINTN *size )
{
	VOID * Buffer;
	Buffer = VarGetVariable( variable, size );
	if(Buffer == NULL)
		Buffer = VarGetNvram( variable, size );
	return Buffer;
}

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
