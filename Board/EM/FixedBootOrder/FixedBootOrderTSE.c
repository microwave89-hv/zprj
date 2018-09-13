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
// $Archive: /Alaska/BIN/Modules/Template/FixedBootOrder Demo/Board/em/FixedBootOrder/FixedBootOrderTSE.c $Author:
//
// $Revision: 19 $Date:
//
//*****************************************************************//
//*****************************************************************//
// Revision History
// ----------------
// $Log: /Alaska/BIN/Modules/Template/FixedBootOrder Demo/Board/em/FixedBootOrder/FixedBootOrderTSE.c $
// 
// 19    4/02/15 5:00a Klzhan
// [TAG]  		EIPNone
// [Category]  	Improvement
// [Description]  	Define TSE_MAX_DRIVE_NAME if not defined.
// 
// 18    3/26/15 10:50p Walonli
// [TAG]  		EIP210628
// [Category]  	Improvement
// [Description]  	Fixed build error when USE_BCP_DEFAULT_PRIORITIES token
// enable.
// [Files]  		Board\em\FixedBootOrder\FBOSetOrder.c
// Board\em\FixedBootOrder\FixedBootOrderTSE.c
// FixedBootOrder.cif
// 
// 17    1/27/15 1:22a Walonli
// [TAG]  		EIP198610
// [Category]  	Bug Fix
// [Severity]  	Important
// [Symptom]  	Boot wrong device when group disable/enable
// [RootCause]  	FixedBootOrder doesn't check group disable when Save and
// Exit.
// [Solution]  	Add code to check group status(enable/disable)
// 
// 16    9/09/14 3:36a Dukeyeh
// [TAG]  		EIP171752 
// [Category]  	Improvement
// [Description]  	Add FIXED_BOOT_ORDER_SUBMENU_MAX_NUM and
// FIXED_BOOT_ORDER_GROUP_MAX_NUM tokens to decide maximum number of
// submenus and groups at boot time.
// [Files]  		Board\em\FixedBootOrder\FixedBootOrder.sdl
// Board\em\FixedBootOrder\FixedBootOrderTSE.c
// Board\em\FixedBootOrder\FixedBootOrder.h
// Board\em\FixedBootOrder\FixedBootOrder.c
// 
// Board\em\FixedBootOrder\FixedBootOrderHII.h
// FixedBootOrder.cif
// 
// 15    8/13/14 11:19p Walonli
// [TAG]  		EIP180632
// [Category]  	New Feature
// [Description]  	Add FixedBootOrder Protocol to change device/group
// name.
// [Files]  		Board\em\FixedBootOrder\FixedBootOrderTSE.c
// Board\em\FixedBootOrder\FixedBootOrder.h
// Board\em\FixedBootOrder\FixedBootOrder.c
// FixedBootOrder.cif
// 
// 14    8/12/14 5:53a Dukeyeh
// 
// 13    8/06/14 8:27a Dukeyeh
// [TAG]  		EIP179738 
// [Category]  	Bug Fix
// [RootCause]  	
// 1. Set FboLegacyDevOrder variable error because of wrong attribute.
// 2. In FixedBootOrderSaveChange function, 
// if LoadedDefault is true, it would use the DefaultLegacyDevOrder
// variable to adjust order, 
// but the device type is wrong becasue it has already changed into BBS
// spec. specified one.
// 
// [Solution]  	
// 1. Set the FboLegacyDevOrder variable with right attribute.
// 2. FixedBootOrderSaveChange doesn't need to 
// get DefaultLegacyDevOrder to set order, using FboLegacyDevOrder
// instead.
// 
// 
// [Files]  		FixedBootOrderTSE.c
// 
// 12    7/24/14 4:21a Klzhan
// [TAG]  		EIP177104
// [Category]  	Bug Fix
// [Severity]  	Important
// [Symptom]  	System show no boot device when change mode and disable all
// bootoptions
// [RootCause]  	FBO will skip the boot option that attrib is hidden.
// [Solution]  	When change mode, also clear hidden attribute.
// 
// 11    5/20/14 3:48a Klzhan
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
// 10    4/15/14 2:26a Klzhan
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
// 9     10/25/13 5:53a Easonchen
// [TAG]  		EIPEIP129692.2
// [Category]  	Bug Fix
// [Severity]  	Minor
// [Symptom]  	BBS Priorities become DISABLE when set ENABLE in Boot
// Option Priorities
// [RootCause]  	Variable "UefiDevOrder" not set "Disable" Mask.
// [Solution]  	Add "Disable" mask to variable "UefiDevOrder".
// [Files]  		
// FboSetOrder.c
// FixedBootOrderTse.c
// 
// 8     10/21/13 5:54a Easonchen
// [TAG]  		EIP129692
// [Category]  	Bug Fix
// [Severity]  	Normal
// [Symptom]  	BBS Priorities become DISABLE when set ENABLE in Boot
// Option Priorities
// [RootCause]  	Variable "UefiDevOrder" not set "Disable" Mask.
// [Solution]  	Add "Disable" mask to variable "UefiDevOrder"
// [Files]  		
// FboSetOrder.c
// FixedBootOrderTse.c
// 
// 7     8/12/13 4:21a Easonchen
// [TAG]  		N/A
// [Category]  	Improvement
// [Description]  	CppCheck error fix.
// [Files]  		FixedBootOrderTSE.c
// 
// 6     5/31/13 2:31a Easonchen
// [TAG]  		EIP123284
// [Category]  	Improvement
// [Description]  	Set Boot Priority unicode string
// [Files]  		FixedBootOrder.c
// FixedBootOrder.h
// FixedBootOrder.sdl
// FixedBootOrderTSE.c
// DefaultFixedBootOrder.c
// DefaultFixedBootOrder.sd
// DefaultFixedBootOrder.uni
// 
// 5     5/28/13 5:27a Easonchen
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
// 4     4/22/13 11:17p Easonchen
// [TAG]  		EIP121259
// [Category]  	Bug Fix
// [Severity]  	Normal
// [Symptom]  	when selected save & exit from setup exit page, the system
// can't boot into Dos.
// [RootCause]  	BootOrder variable not update.
// [Solution]  	Add BootOrder variable update at ProcessProceedToBootHook.
// [Files]  		FixedBootOrderTSE.c
// 
// 3     2/05/13 3:49a Easonchen
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
// 2     6/28/12 11:34a Easonchen
// Make a new FixedBootOrder module by utilizing 4.6.4.1 BDS functionality
//
// 1     6/28/12 11:22a Easonchen
//*****************************************************************//


//<AMI_FHDR_START>
//---------------------------------------------------------------------------
//
// Name:	FixedBootOrderTSE.c
//
// Description: TSE Related Functions
//
//---------------------------------------------------------------------------
//<AMI_FHDR_END>

//---------------------------------------------------------------------------
// Include Files
//---------------------------------------------------------------------------
#include <efi.h>
#include <token.h>
#include <AmiDxeLib.h>
#include <Variable.h>
#if CSM_SUPPORT
#include <Protocol\Legacybios.h>
#endif
#include <Protocol\HiiString.h>
#include <Protocol\HiiDatabase.h>
#include <Setup.h>
#include <setupdata.h>
#include "FixedBootOrderHII.h"
#include "FixedBootOrder.h"
#include "AMITSEStrTokens.h"
//#include "SetupStrTokens.h"
#include <AUTOID.h>
#include <Uefihii.h>

#include <boot.h>
#define VARIABLE_ATTRIBUTES \
	(EFI_VARIABLE_NON_VOLATILE | EFI_VARIABLE_BOOTSERVICE_ACCESS | EFI_VARIABLE_RUNTIME_ACCESS)

#pragma pack(1)
typedef struct
{
	UINT32	Type;
	UINT16	Length;
	UINT16	Data[1];
}
LEGACY_DEVICE_ORDER;

#if CSM_SUPPORT
#ifndef TSE_MAX_DRIVE_NAME
#define TSE_MAX_DRIVE_NAME 32
#endif
// To fix c compiler typedef is tagged but not implement.
typedef struct _BBS_ORDER_LIST
{
    UINT16  Index;
    CHAR16  Name[TSE_MAX_DRIVE_NAME];
}
BBS_ORDER_LIST;
#endif
#pragma pack()

//---------------------------------------------------------------------------
// External functions
//---------------------------------------------------------------------------
BOOLEAN BBSValidDevicePath( EFI_DEVICE_PATH_PROTOCOL *DevicePath );
EFI_STATUS SetBootVariable( UINT16 BootIndex, BOOLEAN EnableDisable );
CHAR16* Wcscpy(CHAR16 *string1, CHAR16* string2);
UINTN Wcslen(CHAR16 *string);
extern UINTN gBootOptionCount;
extern NVRAM_VARIABLE *gVariableList;
extern BOOT_DATA *gBootData;

//---------------------------------------------------------------------------
// Global Variable declarations
//---------------------------------------------------------------------------
#define DEFAULTS_GUID {0x4599d26f, 0x1a11, 0x49b8, 0xb9, 0x1f, 0x85, 0x87, 0x45, 0xcf, 0xf8, 0x24}

EFI_GUID DefaultLegacyDevOrderGuid = DEFAULT_LEGACY_DEV_ORDER_VARIABLE_GUID;
EFI_GUID FixedBootOrderGuid = FIXED_BOOT_ORDER_GUID;
BOOLEAN LoadedDefault = FALSE;
FBODevMap *pFBOLegacyDevMap = NULL;
FBODevMap *pFBOUefiDevMap = NULL;
FBODevMap *pFBODualDevMap = NULL;
FBOHiiMap *pFBOHiiMap = NULL;
UINT16 *pBootOptionTokenMap = NULL;       //(EIP123284+)
FBO_DEVICE_INFORM *pFBONewDevDescription = NULL ;
EFI_HII_STRING_PROTOCOL *gHiiString = NULL;
CHAR8 Language[] = "en-US";
EFI_HII_HANDLE HiiHandle;
extern NVRAM_VARIABLE *gVariableList;

UINT16 GetDevMapDataCount(FBODevMap *pFBODevMap)
{
	UINT16 count = 0;

	if( !pFBODevMap ) return 0;

	do{
		if( pFBODevMap[count].DevType == 0 ) break;
		count++;
	}while(1);

	return count;
}


UINT16 GetHiiMapMapCount()
{
	UINT16 count = 0;

	if( !pFBOHiiMap ) return 0;

	do{
		if( pFBOHiiMap[count].DevType == 0 ) break;
		count++;
	}while(1);

	return count;
}

UINT16 SearchDevMapByType(FBODevMap *pFBODevMap, UINT16 DevType )
{
	UINT16 i=0;
	
	do{
		if(pFBODevMap[i].DevType == 0 ) break;
		if(pFBODevMap[i].DevType == DevType)
			return i;
		i++;
	}while(1);

	return 0;
}

UINT16 SearchHiiMapByType(UINT16 DevType)
{
	UINT16 i=0;
	
	do{
		if(pFBOHiiMap[i].DevType == 0 ) break;
		if(pFBOHiiMap[i].DevType == DevType)
			return i;
		i++;
	}while(1);

	return 0;
}

//<AMI_PHDR_START>
//---------------------------------------------------------------------------
//
// Procedure:	FixedBootOrderSetupEnter
//
// Description:	TSE Setup enter Hook.
//
// Input:
//	None
//
// Output:
//	None
//
// Modified: 
//	
// Referrals: 
//      None
// Notes:	
//
//---------------------------------------------------------------------------
//<AMI_PHDR_END>
BOOLEAN FBO_EnterSetup = FALSE;										
EFI_STATUS FixedBootOrderSetupEnter(IN void)
{
	TRACE((-1,"FixedBootOrder ELINK Setup Enter......\n"));
	FBO_EnterSetup = TRUE;
	return EFI_SUCCESS;
}

//<AMI_PHDR_START>
//---------------------------------------------------------------------------
//
// Procedure:	FixedBootOrderToBoot
//
// Description:	
//
// Input:
//	None
//
// Output:
//	None
//
// Modified: 
//	variable "LegacyDevOrder", "UefiDevOrder".
// Referrals: 
//      None
// Notes:	
//
//---------------------------------------------------------------------------
//<AMI_PHDR_END>
extern BOOLEAN gEnterSetup;										
EFI_STATUS FixedBootOrderToBoot(IN void)
{
	EFI_STATUS Status;
	EFI_GUID gSetupGuid=SETUP_GUID;
	EFI_GUID gEfiGlobalVariableGuid = EFI_GLOBAL_VARIABLE;
	SETUP_DATA *pSetupData=NULL;
	UINT32 SetupAttr;
	UINTN SetupSize=0;
	UINT16 i, j, BootIndex=0;
	UINT16 NewBootOrder[50];

	TRACE((-1,"FixedBootOrderToBoot............\n"));
	TRACE((-1,"FBO_EnterSetup=%d\n", FBO_EnterSetup));
	//-------------------------------------------------------------------
	if( !FBO_EnterSetup ) return EFI_SUCCESS;

	Status = GetEfiVariable(L"Setup", &gSetupGuid, &SetupAttr, &SetupSize, &pSetupData);

        if(pSetupData == NULL || EFI_ERROR(Status)) return Status;
#if FBO_DUAL_MODE
	if( pSetupData->BootMode == 2 )	//dual MODE?
	{
		VOID *DevOrderBuffer = NULL;
		UINTN Size=0;
		UINT16 DevCount=0;
		DevCount = GetDevMapDataCount( pFBODualDevMap );

		Status = GetEfiVariable( L"UefiDevOrder", &FixedBootOrderGuid, NULL, &Size, &DevOrderBuffer );
		if( !EFI_ERROR( Status ) )
		{
			for( i=0; i<DevCount; i++)
			{
				UINT16 DevIndex;
				UEFI_DEVICE_ORDER *DevOrder;

				DevIndex=pSetupData->DualPriorities[i];
				TRACE((-1,"pFBODualDevMap[%d].DevType=%x\n", DevIndex, pFBODualDevMap[DevIndex].DevType));

				if( pFBODualDevMap[DevIndex].DevType == 0 ) continue;		//Is Disable?
				
				if( pFBODualDevMap[DevIndex].BBSType == 0 )					//Uefi boot option?
				{

					for(  DevOrder = DevOrderBuffer
						;(UINT8*)DevOrder<(UINT8*)DevOrderBuffer+Size
						; DevOrder = (UEFI_DEVICE_ORDER*)((UINT8*)DevOrder + DevOrder->Length + sizeof(DevOrder->Type)) ) 
					{
						if( pFBODualDevMap[DevIndex].DevType == DevOrder->Type )
						{			
							for(j=0; j<(DevOrder->Length-2)/sizeof(UINT16); j++)
							{
								TRACE((-1,"Uefi BootOrder Number = %04x\n", DevOrder->Device[j] & 0xff));
								NewBootOrder[BootIndex]=DevOrder->Device[j] & 0xff;
								BootIndex++;
							}
							break;
						}
					}
				}
				else
				{
					for( j=0; j<gBootOptionCount; j++)
					{
						BBS_BBS_DEVICE_PATH *BbsDp;

						if( !BBSValidDevicePath(gBootData[j].DevicePath) ) continue;
				
						BbsDp = (BBS_BBS_DEVICE_PATH*)gBootData[j].DevicePath;
						if( pFBODualDevMap[DevIndex].DevType == BbsDp->DeviceType )
						{
							TRACE((-1,"Legacy BootOrder Number = %04x DeviceType = %02x \n", gBootData[j].Option, BbsDp->DeviceType));
							NewBootOrder[BootIndex]=gBootData[j].Option;
							BootIndex++;
						}
					}
				}
			}

			if( DevOrderBuffer )
				pBS->FreePool( DevOrderBuffer );
		}
	}
	else
#endif
	if( pSetupData->BootMode == 1 )	//uefi MODE?
	{
		VOID *DevOrderBuffer = NULL;
		UINTN Size=0;
		UINT16 DevCount=0;
		DevCount = GetDevMapDataCount( pFBOUefiDevMap );

		Status = GetEfiVariable( L"UefiDevOrder", &FixedBootOrderGuid, NULL, &Size, &DevOrderBuffer );
		if( !EFI_ERROR( Status ) )
		{
			for( i=0; i<DevCount; i++)
			{
				UINT16 DevIndex;
				UEFI_DEVICE_ORDER *DevOrder;

				TRACE((-1,"pSetupData->UefiPriorities[%d]=%d\n", i, pSetupData->UefiPriorities[i]));
				DevIndex=pSetupData->UefiPriorities[i];
				if( pFBOUefiDevMap[DevIndex].DevType == 0 ) continue;		//Is Disable?

				for(  DevOrder = DevOrderBuffer
					;(UINT8*)DevOrder<(UINT8*)DevOrderBuffer+Size
					; DevOrder = (UEFI_DEVICE_ORDER*)((UINT8*)DevOrder + DevOrder->Length + sizeof(DevOrder->Type)) ) 
				{
					if( pFBOUefiDevMap[DevIndex].DevType == DevOrder->Type )
					{
						for(j=0; j<(DevOrder->Length-2)/sizeof(UINT16); j++)
						{
							NewBootOrder[BootIndex]=DevOrder->Device[j] & 0xff;
							BootIndex++;
						}
						break;
					}
				}
			}
	
			if( DevOrderBuffer )
				pBS->FreePool( DevOrderBuffer );
		}
	}
	else	//if( pSetupData->BootMode == 1 )	//uefi MODE?
	if( pSetupData->BootMode == 0 )	//legacy MODE?
	{
		UINT16 LegacyDevCount=0;
		LegacyDevCount = GetDevMapDataCount( pFBOLegacyDevMap );			
		for( i=0; i<LegacyDevCount; i++)
		{
			UINT16 DevIndex;
			DevIndex=pSetupData->LegacyPriorities[i];
			if( pFBOLegacyDevMap[DevIndex].DevType == 0 ) continue;		//Is Disable?

			for( j=0; j<gBootOptionCount; j++)
			{
				BBS_BBS_DEVICE_PATH *BbsDp;

				if( !BBSValidDevicePath(gBootData[j].DevicePath) ) continue;
				
				BbsDp = (BBS_BBS_DEVICE_PATH*)gBootData[j].DevicePath;
				if( pFBOLegacyDevMap[DevIndex].DevType == BbsDp->DeviceType )
				{
					NewBootOrder[BootIndex]=gBootData[j].Option;
					BootIndex++;
				}
			}
		}
	}

    // Above loop for getting NewBootOrder will be skip if the group is disabled:
    // pFBOXXXDevMap[DevIndex].DevType==0 (disable = last DevIndex in pFBOXXXDevMap which is 0)

    // Here we have boot options which are not added because the group is disabled
        
    for (i = 0; i < gBootOptionCount; i++)
    {
        // boot options with group enabled
        for (j = 0; j < BootIndex; j++)
        {
            if (NewBootOrder[j] == gBootData[i].Option)
            {
                if (BBSValidDevicePath(gBootData[i].DevicePath))
                {
                    // Legacy Boot Option
                    // Enable Legacy group option, attr |= ACTIVE
                    SetBootVariable(gBootData[i].Option, TRUE);
                }
                else
                {  
                    // UEFI Boot Option
                    // Due to EFI option is not group, so we need double check with device group sub menu.
                    VOID *UefiDevOrderBuffer = NULL;
                    UINTN UefiDevSize = 0 ;
                    UEFI_DEVICE_ORDER *DevOrder;
                    Status = GetEfiVariable( L"UefiDevOrder", &FixedBootOrderGuid, NULL, &UefiDevSize, &UefiDevOrderBuffer );
                    if (EFI_ERROR(Status)) continue ;
                    for (DevOrder = UefiDevOrderBuffer
                         ; (UINT8*)DevOrder < (UINT8*)UefiDevOrderBuffer + UefiDevSize
                         ; DevOrder = (UEFI_DEVICE_ORDER*)((UINT8*)DevOrder + DevOrder->Length + sizeof(DevOrder->Type)))
                    {
                        UINTN index ;
                        for (index = 0 ; index < DEVORDER_COUNT(DevOrder) ; index++)
                        {      
                            if ((UINT16)DevOrder->Device[index] == gBootData[i].Option)
                            {
                                // Check device is enable or not in sub menu
                                if (DevOrder->Device[index] & FBO_UEFI_DISABLED_MASK)
                                    SetBootVariable(gBootData[i].Option, FALSE);
                                else
                                    SetBootVariable(gBootData[i].Option, TRUE);
                                break ;
                            }
                        }
                    }
                    if( UefiDevOrderBuffer )
				        pBS->FreePool( UefiDevOrderBuffer );
                }
                break;
            }
        }

        // boot options with group disabled
        // need to disable the boot#### variable directly
        if (j == BootIndex)
        {
            NewBootOrder[BootIndex] = gBootData[i].Option;
            BootIndex++;
            SetBootVariable(gBootData[i].Option, FALSE);
        }
    }

#if FIXED_BOOT_INCLUDE_DISABLED_OPTION
    {
        // Put disable boot variable to last.
        UINT16 *TempBootOrder = MallocZ(BootIndex * sizeof(UINT16));
        UINT16 TempIndex = 0 ;
        
        
        for (i = 0; i < gBootOptionCount; i++)
        {
            BOOT_DATA *pBootData = BootGetBootData(NewBootOrder[i]) ;
            if (pBootData->Active & LOAD_OPTION_ACTIVE)
            {
                TempBootOrder[TempIndex] = NewBootOrder[i] ;
                NewBootOrder[i] = 0xffff ; //added flag
                TempIndex++ ;
            }
        }
        for (i = 0; i < gBootOptionCount; i++)
        {
            if (NewBootOrder[i] != 0xffff)
            {
                TempBootOrder[TempIndex] = NewBootOrder[i] ;
                TempIndex++ ;
            }
        }
        
        MemCpy(NewBootOrder, TempBootOrder, BootIndex * sizeof(UINT16)) ;
        pBS->FreePool(TempBootOrder);
    }
#endif

    pRS->SetVariable(L"BootOrder",
                     &gEfiGlobalVariableGuid,
                     VARIABLE_ATTRIBUTES,
                     BootIndex * sizeof(UINT16),
                     NewBootOrder);

    if( pSetupData )
        pBS->FreePool( pSetupData );

	return EFI_SUCCESS;
}

//<AMI_PHDR_START>
//---------------------------------------------------------------------------
//
// Procedure:	SetBootVariable
//
// Description:	Set Boot#### variable Enable/Disable.
//
// Input:
//	UINT16 BootIndex
//      BOOLEAN EnableDisable
//
// Output:
//	None
//
// Modified: variable Boot####.
//
// Referrals: 
//
// Notes:	
//
//---------------------------------------------------------------------------
//<AMI_PHDR_END>	
EFI_STATUS SetBootVariable( UINT16 BootIndex, BOOLEAN EnableDisable )
{
    EFI_GUID EfiVariableGuid = EFI_GLOBAL_VARIABLE;
	EFI_STATUS Status;
	UINTN OptionSize=0;
    UINT32 Attr = 0;
	CHAR16 BootVarName[15];
	UINT8	Buffer[0x200];
	EFI_LOAD_OPTION *BootOption = NULL; 	//buffer for BootXXX variables

	Swprintf( BootVarName, gBootName, BootIndex);

	BootOption=(EFI_LOAD_OPTION*)Buffer;

	OptionSize=sizeof(Buffer);
	Status = pRS->GetVariable( BootVarName, &EfiVariableGuid, &Attr, &OptionSize, BootOption);


	if( !EFI_ERROR(Status) )
	{
        BOOT_DATA *pBootData = BootGetBootData(BootIndex);
		if(EnableDisable)
        {
            BootOption->Attributes |= LOAD_OPTION_ACTIVE;
            BootOption->Attributes &= ~LOAD_OPTION_HIDDEN;
            if (pBootData) pBootData->Active |= LOAD_OPTION_ACTIVE;
        }
		else
        {
			BootOption->Attributes&=~(LOAD_OPTION_ACTIVE);
            if (pBootData) pBootData->Active &= ~(LOAD_OPTION_ACTIVE);
        }

		pRS->SetVariable( BootVarName, 
				&EfiVariableGuid,
				Attr,
	 			OptionSize,
				BootOption);

		TRACE((-1,"[FixedBootOrderTSE.c]::SetBootVariable(%d) Boot%04x=(%r)\n", EnableDisable, BootIndex, Status));
	}

	return Status;

}

//<AMI_PHDR_START>
//---------------------------------------------------------------------------
//
// Procedure:	FixedBootOrderSaveChange
//
// Description:	Save boot device priority to variable.
//
// Input:
//	None
//
// Output:
//	None
//
// Modified: 
//	variable "LegacyDevOrder", "UefiDevOrder".
// Referrals: 
//      None
// Notes:	
//
//---------------------------------------------------------------------------
//<AMI_PHDR_END>										
EFI_STATUS FixedBootOrderSaveChange(IN void)
{
    EFI_STATUS 		Status;
    UINTN 			Size, i=0;
    UINTN 			VariableSize;
    VOID 			*DevOrderBuffer=NULL;
    EFI_GUID 		FixedBootOrderGuid = FIXED_BOOT_ORDER_GUID;
    EFI_GUID 		LegacyDevOrderGuid = LEGACY_DEV_ORDER_GUID;
    EFI_GUID 		gSetupGuid = SETUP_GUID;
    FIXED_BOOT_SETUP   	FixedBootSetupData;
    LEGACY_DEVICE_ORDER	*NewDevBuffer, *NewDevBuffer2;
    UINT32			Attr, LegacyDevAttr;
    EFI_GUID        gFixedBootOrderGuid = FIXED_BOOT_ORDER_GUID;

    VariableSize = sizeof(FIXED_BOOT_SETUP);

    Status = pRS->GetVariable( L"FixedBoot",
        		&gSetupGuid,
       			NULL,
        		&VariableSize,
        		&FixedBootSetupData );

	if(EFI_ERROR(Status))
	{
		TRACE((-1, "[FixedBoot SaveChange]GetVariable(FixedBoot):%r\n", Status));
		return Status;
	}
			
	//-------------------------------------------------------------------------------------------------------
	// Update Variable "FboLegacyDevOrder"
	//-------------------------------------------------------------------------------------------------------	
	Size = 0;
    // Get LegacyDevOrder Attrib
    Status = GetEfiVariable(L"LegacyDevOrder", &LegacyDevOrderGuid, &LegacyDevAttr, &Size, &DevOrderBuffer);
    
    // Set Size to 0 for GetEfiVariable, DevOrderBuffer will also be clear in GetEfiVariable
    Size = 0;
	if(LoadedDefault)
	{					
		Status = GetEfiVariable(L"DefaultLegacyDevOrder", &DefaultLegacyDevOrderGuid, &Attr, &Size, &DevOrderBuffer);
		TRACE((-1, "[FixedBootOrderTSE.c] GetVariable(DefaultLegacyDevOrder):%r\n", Status));
	}
	else
	{					
		Status = GetEfiVariable(L"FboLegacyDevOrder", &gFixedBootOrderGuid, &Attr, &Size, &DevOrderBuffer);
		TRACE((-1, "[FixedBootOrderTSE.c] GetVariable(OldLegacyDevOrder):%r\n", Status));	
	}


	NewDevBuffer2 = NewDevBuffer = Malloc( Size );

	if (!EFI_ERROR(Status) && Size >= 6)
	{
		LEGACY_DEVICE_ORDER *DevOrder;
		UINT16 *OrderData;
		UINT8  *NVramOrderIndex;
		UINT16 Index;
		UINT16 DevDataIndex;
 
		for(  DevOrder = DevOrderBuffer
			;(UINT8*)DevOrder<(UINT8*)DevOrderBuffer+Size
			; DevOrder = (LEGACY_DEVICE_ORDER*)((UINT8*)DevOrder + DevOrder->Length + sizeof(DevOrder->Type)) ) 
		{
            UINT16 *NewOrderData;
				
			pBS->CopyMem(   NewDevBuffer, 
					DevOrder, 
					DevOrder->Length + sizeof(DevOrder->Type) );

			NewOrderData=(UINT16*)&NewDevBuffer->Data[0];
			OrderData = (UINT16*)&DevOrder->Data[0];
			DevDataIndex = SearchDevMapByType( pFBOLegacyDevMap, DevOrder->Type );
			NVramOrderIndex = &FixedBootSetupData.LegacyDevice[DevDataIndex * FIXED_BOOT_ORDER_SUBMENU_MAX_NUM];

			TRACE((-1,"[FixedBootOrderTSE.c]DeviceType:%x (", DevOrder->Type));			
			for(i=0; i<(DevOrder->Length-2)/sizeof(UINT16); i++)
			{
				TRACE((-1,"%x ", OrderData[i]));
			}
			TRACE((-1,")\n"));

			TRACE((-1,"[FixedBootOrderTSE.c]FixedBootSetupData DeviceType:%x (:", DevOrder->Type));
			for(i=0; i<(DevOrder->Length-2)/sizeof(UINT16); i++)
			{
				if( i >= FIXED_BOOT_ORDER_SUBMENU_MAX_NUM) break;
				
				Index=NVramOrderIndex[i];
				if(Index >= FIXED_BOOT_ORDER_SUBMENU_MAX_NUM)
					break;	//is Disable

				TRACE((-1,"%x ",Index));
				NewOrderData[i]= OrderData[Index] & 0xff;
				OrderData[Index]=0xffff;	
			}

#if FIXED_BOOT_INCLUDE_DISABLED_OPTION
			//Check Disable Item and SetMask
			if(i<(DevOrder->Length-2)/sizeof(UINT16))
			{
                                UINTN j;
				TRACE((-1,"Disable: "));
				for(j=0;j<(DevOrder->Length-2)/sizeof(UINT16);j++)
				{
					if(OrderData[j] == 0xffff) continue;
			
					TRACE((-1,"%x ", OrderData[j]));
					NewOrderData[i]= OrderData[j] | 0xff00;
					i++;
				}
			}
#endif
			TRACE((-1,"\n"));

			NewDevBuffer = (LEGACY_DEVICE_ORDER*)((UINT8*)NewDevBuffer 
							      + NewDevBuffer->Length 
							      + sizeof(NewDevBuffer->Type));
		}

       	Status = pRS->SetVariable(L"FboLegacyDevOrder", &gFixedBootOrderGuid, Attr, Size, NewDevBuffer2);
        // Priorities changed !! Sync with LegacyDevOrder
        {
            LEGACY_DEVICE_ORDER*            TempDevOrder;
            EFI_LEGACY_BIOS_PROTOCOL        *LegacyBios;
            UINT16                          HddCount = 0;
            HDD_INFO                        *LocalHddInfo = NULL;
            UINT16                          BbsCount = 0;
            BBS_TABLE                       *BbsTable;
            EFI_GUID                        gEfiLegacyBiosProtocolGuid = EFI_LEGACY_BIOS_PROTOCOL_GUID;
            UINTN                           Offset = 0;
            
            Status = pBS->LocateProtocol (&gEfiLegacyBiosProtocolGuid, NULL, &LegacyBios);      
            if (!EFI_ERROR (Status)) {      
                Status = LegacyBios->GetBbsInfo (
                                      LegacyBios,
                                      &HddCount, 
                                      &LocalHddInfo, 
                                      &BbsCount,
                                      &BbsTable
                                      );
            }

            for (TempDevOrder = NewDevBuffer2
                        ; (UINT8*)TempDevOrder < (UINT8*)NewDevBuffer2 + Size
                        ; TempDevOrder = (LEGACY_DEVICE_ORDER*)((UINT8*)TempDevOrder + TempDevOrder->Length + sizeof(TempDevOrder->Type)))
            {
                
                // Due to TSE SaveBBSOrder function will reassign gBootData->LegacyEntryOffset
                // We need calculate offset again.
                for (i = 0; i < gBootOptionCount; i++)
                {
                    UINTN j;
                    BBS_ORDER_LIST *OrderList = gBootData[i].OrderList ;
                    
                    for (j =0; j < gBootData[i].LegacyDevCount ; j++)
                        if ((OrderList[j].Index & FBO_LEGACY_ORDER_MASK) == TempDevOrder->Data[0])
                            break ;
                    
                    if (j != gBootData[i].LegacyDevCount)
                    {
                        // Matched, update gBootData offset.
                        gBootData[i].LegacyEntryOffset = Offset ;
                        break ;
                    }
                }
                Offset += TempDevOrder->Length + sizeof(TempDevOrder->Type) ;
            }
        }
        // Need to sync with LegacyDevOrder for TSE to boot (in case it continues to boot without reset)
        Status = pRS->SetVariable(L"LegacyDevOrder", &LegacyDevOrderGuid, Attr, Size, NewDevBuffer2);
		pBS->FreePool(DevOrderBuffer);

	}

	if( NewDevBuffer2 )
		pBS->FreePool(NewDevBuffer2);
	//-------------------------------------------------------------------------------------------------------
	// Update Variable "UefiDevOrder"
	//-------------------------------------------------------------------------------------------------------
	Size = 0;
	DevOrderBuffer=NULL;
	if(LoadedDefault)
	{
		Status = GetEfiVariable(L"DefaultUefiDevOrder", &FixedBootOrderGuid, &Attr, &Size, &DevOrderBuffer);
		TRACE((-1, "[FixedBootOrderTSE.c] GetVariable(DefaultUefiDevOrder):%r\n", Status));
	}
	else
	{
		Status = GetEfiVariable(L"OldUefiDevOrder", &FixedBootOrderGuid, &Attr, &Size, &DevOrderBuffer);
		TRACE((-1, "[FixedBootOrderTSE.c] GetVariable(UefiDevOrder):%r\n", Status));
	}

	NewDevBuffer2 = NewDevBuffer = Malloc( Size );

	if (!EFI_ERROR(Status) && Size >= 6)
	{
		LEGACY_DEVICE_ORDER *DevOrder;
		UINT16 *OrderData;
		UINT8  *NVramOrderIndex;
		UINT16 Index;
		UINT16 DevDataIndex;

		for(  DevOrder = DevOrderBuffer
			;(UINT8*)DevOrder<(UINT8*)DevOrderBuffer+Size
			; DevOrder = (LEGACY_DEVICE_ORDER*)((UINT8*)DevOrder + DevOrder->Length + sizeof(DevOrder->Type)) ) 
		{
                        UINT16 *NewOrderData;

			pBS->CopyMem(   NewDevBuffer, 
					DevOrder, 
					DevOrder->Length + sizeof(DevOrder->Type) );

			NewOrderData=(UINT16*)&NewDevBuffer->Data[0];
			OrderData = (UINT16*)&DevOrder->Data[0];
			DevDataIndex = SearchDevMapByType( pFBOUefiDevMap, DevOrder->Type );
            NVramOrderIndex = &FixedBootSetupData.UefiDevice[DevDataIndex * FIXED_BOOT_ORDER_SUBMENU_MAX_NUM];

			TRACE((-1,"[FixedBootOrderTSE.c]DeviceType:%x (", DevOrder->Type));			
			for(i=0; i<(DevOrder->Length-2)/sizeof(UINT16); i++)
			{
				TRACE((-1,"%x ", OrderData[i]));
			}
			TRACE((-1,")\n"));

			TRACE((-1,"[FixedBootOrderTSE.c]FixedBootSetupData DeviceType:%x (:", DevOrder->Type));
			for(i=0; i<(DevOrder->Length-2)/sizeof(UINT16); i++)
			{
				if( i >= FIXED_BOOT_ORDER_SUBMENU_MAX_NUM) break;
				
				Index=NVramOrderIndex[i];
				if(Index >= FIXED_BOOT_ORDER_SUBMENU_MAX_NUM)
					break;	//is Disable

				TRACE((-1,"%x ",Index));
				NewOrderData[i]= OrderData[Index] & 0xff;
				SetBootVariable( NewOrderData[i], TRUE);		//set boot#### enable.
				OrderData[Index]=0xffff;		
			}

#if FIXED_BOOT_INCLUDE_DISABLED_OPTION
			//Check Disable Item and SetMask
			if(i<(DevOrder->Length-2)/sizeof(UINT16))
			{
                                UINTN j;
				TRACE((-1,"Disable: "));
				for(j=0;j<(DevOrder->Length-2)/sizeof(UINT16);j++)
				{
					if(OrderData[j] == 0xffff) continue;
			
					TRACE((-1,"%x ", OrderData[j]));
					NewOrderData[i]= OrderData[j] | 0xff00;     //(EIP129692.2)
					SetBootVariable( OrderData[j], FALSE);		//set boot#### disable.
					i++;
				}
			}
#endif
			TRACE((-1,"\n"));

			NewDevBuffer = (LEGACY_DEVICE_ORDER*)((UINT8*)NewDevBuffer 
							      + NewDevBuffer->Length 
							      + sizeof(NewDevBuffer->Type));
		}

       	Status = pRS->SetVariable(L"UefiDevOrder", &FixedBootOrderGuid, Attr, Size, NewDevBuffer2);

		pBS->FreePool(DevOrderBuffer);
	}

	if( NewDevBuffer2 )
		pBS->FreePool(NewDevBuffer2);

	return Status;
}

//<AMI_PHDR_START>
//---------------------------------------------------------------------------
//
// Procedure:	FixedBootOrderLoadedConfigDefaults
//
// Description:	 TSE LoadDefault ELINK Hook.
//
// Input:
// 	None
// Output:
//	None
// Modified:
//	None  
// Referrals: 
//      None
// Notes:	
//
//---------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS
FixedBootOrderLoadedConfigDefaults(IN void)
{
	EFI_STATUS Status;
	SETUP_DATA *pSetupData;
	UINT16 i, DevMapDataCount;

	EFI_GUID FixedBootOrderSetupGuid = FIXED_BOOT_ORDER_SETUP_GUID;
	EFI_FIXED_BOOT_ORDER_SETUP_PROTOCOL *pFBOSetup=NULL;

    	Status = pBS->LocateProtocol( &FixedBootOrderSetupGuid, NULL, &pFBOSetup );

        if( !EFI_ERROR(Status) )
		pFBOSetup->load_default_string();

	LoadedDefault=TRUE;

	pSetupData = (SETUP_DATA*)gVariableList[VARIABLE_ID_SETUP].Buffer;
										//(EIP107268+)>
#if USE_BCP_DEFAULT_PRIORITIES							
	DevMapDataCount = GetDevMapDataCount(pFBOLegacyDevMap);
	for(i=0;i<DevMapDataCount;i++)
		pSetupData->LegacyPriorities[i]=pSetupData->BcpDefaultLegacyPriorities[i];

	DevMapDataCount = GetDevMapDataCount(pFBOUefiDevMap);
	for(i=0;i<DevMapDataCount;i++)
		pSetupData->UefiPriorities[i]=pSetupData->BcpDefaultUefiPriorities[i];
										//(EIP122146+)>
#if FBO_DUAL_MODE
	DevMapDataCount = GetDevMapDataCount(pFBODualDevMap);
	for(i=0;i<DevMapDataCount;i++)
		pSetupData->DualPriorities[i]=pSetupData->BcpDefaultDualPriorities[i];
#endif
                                        //<(EIP122146+)
#else	                                //<(EIP107268+)
	DevMapDataCount = GetDevMapDataCount(pFBOLegacyDevMap);
	for(i=0;i<DevMapDataCount;i++)
		pSetupData->LegacyPriorities[i]=i;

	DevMapDataCount = GetDevMapDataCount(pFBOUefiDevMap);
	for(i=0;i<DevMapDataCount;i++)
		pSetupData->UefiPriorities[i]=i;

#if FBO_DUAL_MODE
	DevMapDataCount = GetDevMapDataCount(pFBODualDevMap);
	for(i=0;i<DevMapDataCount;i++)
		pSetupData->DualPriorities[i]=i;
#endif

#endif                                  //(EIP107268+)
	pSetupData->FBO_Init=1;
	return EFI_SUCCESS;
}

//<AMI_PHDR_START>
//---------------------------------------------------------------------------
//
// Procedure:	SetLegacyDevMap
//
// Description:	Set Legacy DevMap data to pFBOLegacyDevMap
//
// Input:
//  FBODevMap *p
// Output:
//  EFI_STATUS
// Modified:
//  None    
// Referrals: 
//  None
// Notes:	
//
//---------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS SetLegacyDevMap(IN FBODevMap *p)
{
	pFBOLegacyDevMap = p;
	return EFI_SUCCESS;
}

//<AMI_PHDR_START>
//---------------------------------------------------------------------------
//
// Procedure:	SetUefiDevMap
//
// Description:	Set Uefi DevMap data to pFBOUefiDevMap
//
// Input:
//  FBODevMap *p
// Output:
//  EFI_STATUS
// Modified:
//  None    
// Referrals: 
//  None
// Notes:	
//
//---------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS SetUefiDevMap(IN FBODevMap *p)
{
	pFBOUefiDevMap = p;
	return EFI_SUCCESS;
}

//<AMI_PHDR_START>
//---------------------------------------------------------------------------
//
// Procedure:	SetDualDevMap
//
// Description:	Set Dual DevMap data to pFBODaulDevMap
//
// Input:
//  FBODevMap *p
// Output:
//  EFI_STATUS
// Modified:
//  None    
// Referrals: 
//  None
// Notes:	
//
//---------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS SetDualDevMap(IN FBODevMap *p)
{
	pFBODualDevMap = p;
	return EFI_SUCCESS;
}

//<AMI_PHDR_START>
//---------------------------------------------------------------------------
//
// Procedure:	GetLegacyDevMap
//
// Description:	Get Legacy DevMap data.
//
// Input:
//  None
// Output:
//  *FBODevMap
// Modified:
//  None    
// Referrals: 
//  None
// Notes:	
//
//---------------------------------------------------------------------------
//<AMI_PHDR_END>
FBODevMap *GetLegacyDevMap(IN VOID)
{
	return pFBOLegacyDevMap;
}

//<AMI_PHDR_START>
//---------------------------------------------------------------------------
//
// Procedure:	GetUefiDevMap
//
// Description:	Get Uefi DevMap data.
//
// Input:
//  None
// Output:
//  *FBODevMap
// Modified:
//  None    
// Referrals: 
//  None
// Notes:	
//
//---------------------------------------------------------------------------
//<AMI_PHDR_END>
FBODevMap *GetUefiDevMap(IN VOID)
{
	return pFBOUefiDevMap;
}

//<AMI_PHDR_START>
//---------------------------------------------------------------------------
//
// Procedure:	GetDualDevMap
//
// Description:	Get Daul DevMap data.
//
// Input:
//  *FBODevMap
// Output:
//  EFI_STATUS
// Modified:
//  None    
// Referrals: 
//  None
// Notes:	
//
//---------------------------------------------------------------------------
//<AMI_PHDR_END>
FBODevMap *GetDualDevMap(IN VOID)
{
	return pFBODualDevMap;
}


//<AMI_PHDR_START>
//---------------------------------------------------------------------------
//
// Procedure:	SetHiiMap
//
// Description:	Set Uefi DevMap data to pFBOHiiMap
//
// Input:
//  FBOHiiMap *p
// Output:
//  EFI_STATUS
// Modified:
//  None    
// Referrals: 
//  None
// Notes:	
//
//---------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS SetHiiMap(IN FBOHiiMap *p)
{
	pFBOHiiMap = p;
	return EFI_SUCCESS;
}

//<AMI_PHDR_START>
//---------------------------------------------------------------------------
//
// Procedure:	GetHiiMap
//
// Description:	Get HiiMap data.
//
// Input:
//  None
// Output:
//  *pFBOHiiMap
// Modified:
//  None    
// Referrals: 
//  None
// Notes:
//
//---------------------------------------------------------------------------
//<AMI_PHDR_END>
FBOHiiMap *GetHiiMap(IN VOID)
{
	return pFBOHiiMap;
}

                                         //(EIP123284+)>
//<AMI_PHDR_START>
//---------------------------------------------------------------------------
//
// Procedure:	SetBootOptionTokenMap
//
// Description:	Set BootOptionTokenMap data
//
// Input:
//  UINT16 *p
// Output:
//  EFI_STATUS
// Modified:
//  None    
// Referrals: 
//  None
// Notes:	
//
//---------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS SetBootOptionTokenMap(IN UINT16 *p)
{
	pBootOptionTokenMap = p;
	return EFI_SUCCESS;
}

//<AMI_PHDR_START>
//---------------------------------------------------------------------------
//
// Procedure:	GetBootOptionTokenMap
//
// Description:	Get BootOptionTokenMap data.
//
// Input:
//  None
// Output:
//  *UINT16
// Modified:
//  None    
// Referrals: 
//  None
// Notes:
//
//---------------------------------------------------------------------------
//<AMI_PHDR_END>
UINT16 *GetBootOptionTokenMap(IN VOID)
{
	return pBootOptionTokenMap;
}
                                         //<(EIP123284+)

//<AMI_PHDR_START>
//---------------------------------------------------------------------------
//
// Procedure:   FBOSetNewDescription
//
// Description: Set New Description data
//
// Input:
//  FBO_DEVICE_INFORM *p
// Output:
//  EFI_STATUS
// Modified:
//  None
// Referrals:
//  None
// Notes:
//
//---------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS SetNewDescription(IN FBO_DEVICE_INFORM *p)
{
	if (pFBONewDevDescription == NULL) 
	{
		pFBONewDevDescription = p ;
		return EFI_SUCCESS ;
	}
	else
	{
		FBO_DEVICE_INFORM *DevInfom = pFBONewDevDescription ;
		while( DevInfom->Next )
		    DevInfom = DevInfom->Next ;
		DevInfom->Next = p ;
		return EFI_SUCCESS ;
	}
	
}

//<AMI_PHDR_START>
//---------------------------------------------------------------------------
//
// Procedure:   GetNewDescription
//
// Description: Get New Description data.
//
// Input:
//  None
// Output:
//  *FBO_DEVICE_INFORM
// Modified:
//  None
// Referrals:
//  None
// Notes:
//
//---------------------------------------------------------------------------
//<AMI_PHDR_END>
FBO_DEVICE_INFORM *GetNewDescription(IN VOID)
{
    return pFBONewDevDescription;
}

static EFI_FIXED_BOOT_ORDER_PROTOCOL gFixedBootOrderProtocol =
{
    SetLegacyDevMap,
    SetUefiDevMap,
    SetDualDevMap,
	SetHiiMap,
    SetBootOptionTokenMap,     //(EIP123284+)
    SetNewDescription,
	GetLegacyDevMap,
	GetUefiDevMap,
	GetDualDevMap,
	GetHiiMap,
    GetBootOptionTokenMap,     //(EIP123284+)
    GetNewDescription
};

//<AMI_PHDR_START>
//---------------------------------------------------------------------------
//
// Procedure:	FBO_Protocol_install
//
// Description:	Initialize EFI_FIXED_BOOT_ORDER_PROTOCOL function service.
//
// Input:
//  None
// Output:
//  None
// Modified:
//  None    
// Referrals: 
//  None
// Notes:
//
//---------------------------------------------------------------------------
//<AMI_PHDR_END>
void FBO_Protocol_install(IN void)
{
	EFI_HANDLE Handle = NULL;
	EFI_GUID FixedBootOrderGuid = FIXED_BOOT_ORDER_GUID;
	EFI_STATUS Status;

    Status = pBS->InstallProtocolInterface (
             	&Handle,
             	&FixedBootOrderGuid,
             	EFI_NATIVE_INTERFACE,
             	&gFixedBootOrderProtocol
                );

    	// Install protocol interface
	TRACE((-1,"Install FixedBootOrder protocol (%r)\n", Status));
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
