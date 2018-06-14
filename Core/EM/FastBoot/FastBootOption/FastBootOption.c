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
// $Header: /Alaska/SOURCE/Modules/PTT/FastBootOption/FastBootOption.c 2     7/14/13 10:52p Simonchen $
//
// $Revision: 2 $
//
// $Date: 7/14/13 10:52p $
//**********************************************************************
// Revision History
// ----------------
// $Log: /Alaska/SOURCE/Modules/PTT/FastBootOption/FastBootOption.c $
// 
// 2     7/14/13 10:52p Simonchen
// [TAG]  		EIP129092
// [Category]  	Improvement
// [Description]  	Add CloseEvent in OnExitBootServices in
// FastBootOption.c
// [Files]  		FastBootOption.c
// 
// 1     10/30/12 4:22a Bibbyyeh
// [TAG]           EIP105177
// [Category]      New Feature
// [Description]   Report pseudo boot option for Windows 'Boot To Device'
// support
// [Files]         FastBootOption.cif FastBootOption.sdl
// FastBootOption.mak FastBootOption.h FastBootOption.c
// FastBootOptionBds.c FastBootOption.dxs
// 
//
//<AMI_FHDR_START>
//---------------------------------------------------------------------------
//
// Name: FastBootOption.c
//
// Description:	FastBootOption Support
//
//---------------------------------------------------------------------------
//<AMI_FHDR_END>

#include "FastBootOption.h"
#include <Setup.h>
#include <Protocol\FastBootProtocol.h>

#define EFI_TPL_NOTIFY TPL_NOTIFY

#define	BOOT_FLOW_CONDITION_FAST_BOOT 7
#define BOOT_FLOW_CONDITION_NORMAL  0

EFI_EVENT gExitBootServicesEvent;
EFI_GUID EfiVariableGuid = EFI_GLOBAL_VARIABLE;

TempDeviceMap BootOptionTemp[]={
//	{ TempUefiHddDevice, "UEFI:Hard Drive" },
	{ TempUefiOddDevice, "UEFI:CD/DVD Drive" },
	{ TempUefiRemDevice, "UEFI:Removable Device" },
	{ TempUefiNetDevice, "UEFI:Network Device" }
};

//<AMI_PHDR_START>
//---------------------------------------------------------------------------
//
// Procedure:	GetUEFIBootName
//
// Description:	 Get Variable Boot#### and return data pointer.
//
// Input:
//  IN UINT16 BootIndex
//
// Output:
//  EFI_LOAD_OPTION
//
// Modified:
//      
// Referrals: 
//
// Notes:	
//
//---------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_LOAD_OPTION* GetUEFIBootName(IN UINT16 BootIndex)
{
//    	EFI_GUID EfiVariableGuid = EFI_GLOBAL_VARIABLE;
	EFI_STATUS Status;
	UINTN OptionSize;
	CHAR16 BootVarName[15];
	EFI_LOAD_OPTION *BootOption = NULL; 				//buffer for BootXXX variables

	Swprintf( BootVarName, gBootName, BootIndex);			//(EIP35562)

	OptionSize = 0;
	Status = pRS->GetVariable( BootVarName, &EfiVariableGuid, NULL, &OptionSize, NULL);
	if(Status != EFI_NOT_FOUND)
	{
		BootOption=Malloc( OptionSize );
		Status = pRS->GetVariable( BootVarName, &EfiVariableGuid, NULL, &OptionSize, BootOption);
		return BootOption;
	}
	else
		return NULL;

}

//<AMI_PHDR_START>
//---------------------------------------------------------------------------
//
// Procedure:	AddBootOption
//
// Description:	calculate devicepath length
//              
//
// Input: 	IN UINT16 Number
//		IN EFI_DEVICE_PATH_PROTOCOL *Dp
//		IN UINT32 Attributes 
//		IN VOID *pOptions
//		IN UINTN OptionsSize 
//		IN CHAR16 *DefaultName
// Output:
//
// Modified:
//      
// Referrals: 
//
// Notes:	
//
//---------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS AddBootOption(
	IN UINT16 Number,
	IN EFI_DEVICE_PATH_PROTOCOL *Dp,
	IN UINT32 Attributes, 
	IN VOID *pOptions, IN UINTN OptionsSize, IN CHAR16 *DefaultName
)
{

	EFI_GUID EfiVariableGuid = EFI_GLOBAL_VARIABLE;
	EFI_LOAD_OPTION *Option;
	UINTN Size=0, Length;
	CHAR16 BootVarName[15]; //Boot0000
	CHAR16 NameStr[1024];
	EFI_STATUS Status;

	Length = DPLength(Dp);

	if ( !pOptions ) 
		OptionsSize=0;
	else
	{
		Swprintf( NameStr, L"%S", pOptions );
		Size = (Wcslen(NameStr)+1)*sizeof(CHAR16);
	}
	//Size = (EfiStrLen(NameStr)+1)*sizeof(CHAR16);
	Option = Malloc(sizeof(*Option)+Size+Length);
	if (!Option) return EFI_OUT_OF_RESOURCES;

	Option->Attributes = Attributes;
	Option->FilePathListLength = (UINT16)Length;

	if(OptionsSize)
		pBS->CopyMem(Option+1, NameStr, Size);

	pBS->CopyMem((UINT8*)(Option+1)+Size, Dp, Length);

	Swprintf(BootVarName, gBootName, Number);
	TRACE((-1,"[FastBootOption] Add %S (%S)\n", BootVarName, NameStr)); 
	Status = pRS->SetVariable(
		BootVarName, &EfiVariableGuid,
		EFI_VARIABLE_NON_VOLATILE | EFI_VARIABLE_BOOTSERVICE_ACCESS | EFI_VARIABLE_RUNTIME_ACCESS,
		sizeof(*Option)+Size+Length, Option
	);

	pBS->FreePool(Option);
	return Status;
}

//<AMI_PHDR_START>
//---------------------------------------------------------------------------
//
// Procedure:	CreateBootOption
//
// Description:	Create variable Boot#### 
//              
//
// Input: 	IN UINT16 OptionNumber
//		IN UINT16 Index
//		IN UINT16 DevType
//
// Output:
//
// Modified:
//      
// Referrals: 
//
// Notes:	
//
//---------------------------------------------------------------------------
//<AMI_PHDR_END>
void CreateBootOption(IN UINT16 OptionNumber, IN UINT16 DevType, CHAR8 *Description)
{

static struct {
	BBS_BBS_DEVICE_PATH bbs;
	EFI_DEVICE_PATH_PROTOCOL end;
} LegacyDp = 
	{
		{{BBS_DEVICE_PATH,BBS_BBS_DP,sizeof(BBS_BBS_DEVICE_PATH)},0xff,0,0},
		{END_DEVICE_PATH,END_ENTIRE_SUBTYPE,sizeof(EFI_DEVICE_PATH_PROTOCOL)}
	};

	
	LegacyDp.bbs.DeviceType = DevType;

	AddBootOption(
			OptionNumber, &LegacyDp.bbs.Header,
			LOAD_OPTION_ACTIVE, 
			Description, sizeof(Description) + 1, NULL);

}


//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   CreateTempBootOption
//
// Description: This function is the entry point for FastBootOption Driver.
//
// Input:
//
//
// Output:
//
//
// Notes:
//
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS CreateTempBootOption()
{
	EFI_STATUS Status = EFI_SUCCESS;
    	UINT16 *BootOrder = NULL, NewBootOrder[50];
	UINTN BootOrderSize = 0;
	UINT16 MapIndex, i, BootIndex = 1;
	BOOLEAN TempDeviceFound = FALSE;

	Status = GetEfiVariable( L"BootOrder", &EfiVariableGuid, NULL, &BootOrderSize, &BootOrder);

	if( !EFI_ERROR(Status) )
	{
		for( i=0; i<BootOrderSize/sizeof(UINT16); i++)
		{
			EFI_LOAD_OPTION *BootOption=NULL;
			BBS_BBS_DEVICE_PATH *BBSdp;
			BootOption=GetUEFIBootName( BootOrder[i] );

			if( BootOption )
			{
				BBSdp = (BBS_BBS_DEVICE_PATH*) ((UINT8*)(BootOption+1) 						
					+(Wcslen((CHAR16*)(BootOption+1))+1)*sizeof(CHAR16));

				if( BBSdp->Header.Type == BBS_DEVICE_PATH )
				{
					switch( BBSdp->DeviceType )
					{
						case TempUefiHddDevice:
						case TempUefiOddDevice:
						case TempUefiRemDevice:
						case TempUefiNetDevice:
							TempDeviceFound=TRUE;
							break;
					}
				}

				pBS->FreePool(BootOption);
			}

			if( TempDeviceFound )
				break;
		}

		pBS->CopyMem(NewBootOrder, BootOrder, BootOrderSize);
		pBS->FreePool(BootOrder);
		
		//TRACE((-1,"CreateTempBootOption::TempDeviceFound(%d)\n", TempDeviceFound));
		//already create temp device?
		if( TempDeviceFound )
			return EFI_SUCCESS;
	}

	for( MapIndex=0; MapIndex<sizeof(BootOptionTemp)/sizeof(TempDeviceMap); MapIndex++)
	{
		for( i=0; i<BootOrderSize/sizeof(UINT16); i++)
		{
			if( NewBootOrder[i] == BootIndex )
			{
				BootIndex++;
				i=-1;
				continue;
			}
		}

		NewBootOrder[i]=BootIndex;
		BootOrderSize+=sizeof(UINT16);

		CreateBootOption( BootIndex, BootOptionTemp[MapIndex].DeviceTypeId, BootOptionTemp[MapIndex].TempName );
	}

	//Update Variable "BootOrder".
	if( BootOrderSize )
	{
		pRS->SetVariable(
				L"BootOrder",
				&EfiVariableGuid,
				EFI_VARIABLE_NON_VOLATILE | EFI_VARIABLE_BOOTSERVICE_ACCESS | EFI_VARIABLE_RUNTIME_ACCESS,
				BootOrderSize,
				&NewBootOrder[0]);
	}

	return Status;
}



//<AMI_PHDR_START>
//---------------------------------------------------------------------------
//
// Name:        OnExitBootServices
//
// Description: EXIT_BOOT_SERVICES notification callback function.
//
//---------------------------------------------------------------------------
//<AMI_PHDR_END>

VOID
OnExitBootServices(
    IN EFI_EVENT    Event,
    IN VOID       *Context
)
{
    EFI_STATUS Status;
    EFI_GUID   FastBootPolicyGuid = FAST_BOOT_POLICY_PROTOCOL_GUID;
    FAST_BOOT_POLICY    *gFastBootPolicy;
    EFI_GUID guidBootFlow = BOOT_FLOW_VARIABLE_GUID;
    UINT32 BootFlow;
    UINTN Size;

    TRACE((-1,"FastBootOption OnExitBootServices event .............\n"));
    Status = pBS->LocateProtocol(&FastBootPolicyGuid,NULL,&gFastBootPolicy);

    TRACE((-1,"FastBootOption gFastBootPolicy->FastBootEnable = %d\n", gFastBootPolicy->FastBootEnable));
    if (EFI_ERROR(Status) || gFastBootPolicy->FastBootEnable == FALSE) {
		pBS->CloseEvent (Event);
        return;
	}
    Status = pRS->GetVariable(L"BootFlow", &guidBootFlow, NULL, &Size, &BootFlow);
    TRACE((-1,"FastBootOption BootFlow = %d\n", BootFlow));

    if(!EFI_ERROR(Status) && (BootFlow == BOOT_FLOW_CONDITION_FAST_BOOT)) 
	    CreateTempBootOption();

	pBS->CloseEvent (Event);
}


//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   FastBootOptionEntryPoint
//
// Description: This function is the entry point for FastBootOption Driver.
//
// Input:
//  EFI_HANDLE          ImageHandle     Image handle.
//  EFI_SYSTEM_TABLE    *SystemTable    Pointer to the EFI system table.
//
// Output:
//  EFI_SUCCESS         Security interface installed.
//  EFI_ERROR           Security interface not installed or unable to locate
//                      some protocol.
//
// Notes:
//  Entry Points are used to locate or install protocol interfaces and
//  notification events.
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS FastBootOptionEntryPoint(
    IN EFI_HANDLE       ImageHandle,
    IN EFI_SYSTEM_TABLE *SystemTable )
{
    EFI_HANDLE Handle = NULL;
    EFI_STATUS Status = EFI_SUCCESS;

    InitAmiLib( ImageHandle, SystemTable );

    TRACE((-1,"FastBootOptionEntryPoint.............\n"));

    pBS->CreateEvent (
                EVT_SIGNAL_EXIT_BOOT_SERVICES,
                EFI_TPL_NOTIFY,
                OnExitBootServices,
                NULL,
                &gExitBootServicesEvent
            );

    return Status;
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
