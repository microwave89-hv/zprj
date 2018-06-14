//*************************************************************************
//*************************************************************************
//**                                                                     **
//**        (C)Copyright 1987-2013, American Megatrends, Inc.            **
//**                                                                     **
//**                       All Rights Reserved.                          **
//**                                                                     **
//**      5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093           **
//**                                                                     **
//**                       Phone: (770)-246-8600                         **
//**                                                                     **
//*************************************************************************
//*************************************************************************

//**********************************************************************
// $Header: /Alaska/Projects/Intel/Haswell/LynxPoint_SharkBay-DT_Crb_1AQQW/Board/Cpu/TxtDxe/AmiTxtInfoHook.c 1     7/08/15 4:26a Chienhsieh $
//
// $Revision: 1 $
//
// $Date: 7/08/15 4:26a $
//**********************************************************************
// Revision History
// ----------------
// $Log:
//
//**********************************************************************

//<AMI_FHDR_START>
//---------------------------------------------------------------------------
//
// Name:	AmiTxtInfoHook.c
//
// Description:	AmiTxtInfo Rountines
//
//---------------------------------------------------------------------------
//<AMI_FHDR_END>

#include <Setup.h>
#include <AmiDxeLib.h>
#include <AmiHobs.h>
#include <Protocol/SimpleTextIn.h>
#include <Protocol/AMIPostMgr.h>
#include "Include/Protocol/AmiTxtInfo.h"

extern EFI_BOOT_SERVICES      *gBS;
extern EFI_SYSTEM_TABLE       *gST;
extern EFI_RUNTIME_SERVICES   *gRT;

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	AmiTxtHook
//
// Description:	Initialize CPU strings.
//
// Input:
//      IN EFI_HII_HANDLE   HiiHandle
//      IN UINT16           Class
//
// Output:
//      VOID
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

BOOLEAN AmiTxtHook  (VOID)
{
    EFI_STATUS  Status;
	EFI_GUID AmiTseSetupguid = AMITSESETUP_GUID;
	EFI_GUID gAmiTxtInfoProtocolGuid    = AMI_TXT_INFO_PROTOCOL_GUID;
	EFI_GUID gAmiPostManagerProtocolGuid = AMI_POST_MANAGER_PROTOCOL_GUID;
	AMI_POST_MANAGER_PROTOCOL *gAmiPostMgr = NULL;
	AMI_TXT_INFO_PROTOCOL *gAmiTxtInfoProt;
	AMI_TXT_INFO_DATA     *AmiTxtInfoData = NULL;    
	UINTN 		Index;
	EFI_INPUT_KEY 	Key;
	AMITSESETUP TSEVar;
    UINTN       Size;
	CHAR16		Str[30];

	Size = sizeof (AMITSESETUP);

    Status = gRT->GetVariable(L"AMITSESetup", \
                               &AmiTseSetupguid, \
                               NULL, \
                               &Size, \
                               &TSEVar );
	if (EFI_ERROR(Status)) return EFI_SUCCESS;

	Status = pBS->LocateProtocol( &gAmiPostManagerProtocolGuid, NULL, &gAmiPostMgr );
	if (EFI_ERROR(Status)) return EFI_SUCCESS;

	Status = pBS->LocateProtocol (&gAmiTxtInfoProtocolGuid, NULL, &gAmiTxtInfoProt);
	if (EFI_ERROR(Status)) return EFI_SUCCESS;

	//Get AmiTxt info data
	gAmiTxtInfoProt->GetTxtInfo(gAmiTxtInfoProt, &AmiTxtInfoData);

	//Only display txtinfor when error occur
	if (!AmiTxtInfoData->TxtErrCode) return EFI_SUCCESS;

	//If it's silent boot, change to post screen
	if(TSEVar.AMISilentBoot != 0) gAmiPostMgr->SwitchToPostScreen();

	gAmiPostMgr->DisplayPostMessage(L"Intel Txt Information:");

	if (AmiTxtInfoData->ChipsetIsProduction)
		gAmiPostMgr->DisplayPostMessage(L"Chipset Production Fused");
	else
		gAmiPostMgr->DisplayPostMessage(L"Chipset Debug Fused");

	if (AmiTxtInfoData->ChipsetIsTxtCapable)
		gAmiPostMgr->DisplayPostMessage(L"Chipset Txt Supported");
	else
		gAmiPostMgr->DisplayPostMessage(L"Chipset Txt Don't Support");
	
	if (AmiTxtInfoData->CpuIsTxtCapable)   //CPUID eax=1 ecx[6]
		gAmiPostMgr->DisplayPostMessage(L"Cpu Txt Supported");
	else
		gAmiPostMgr->DisplayPostMessage(L"Cpu Txt don't Support");
	
	if (AmiTxtInfoData->TxtErrCode) {
		UINT32 ClassCode = (AmiTxtInfoData->TxtErrCode >> 4) & 0x3f; //ErrorCode[9:4]
		UINT32 MajorCode = (AmiTxtInfoData->TxtErrCode >> 10) & 0x1f; //ErrorCode[14:10]
		UINT32 MinorCode = (AmiTxtInfoData->TxtErrCode >> 16) & 0x1ff; //ErrorCode[24:16]
		
		Swprintf(Str,L"Error Code %x", AmiTxtInfoData->TxtErrCode);
		gAmiPostMgr->DisplayPostMessage(Str);
		
		Swprintf(Str,L"  Class Code %x", ClassCode);
		gAmiPostMgr->DisplayPostMessage(Str);

		Swprintf(Str,L"  Major Code %x", MajorCode);
		gAmiPostMgr->DisplayPostMessage(Str);
		
		Swprintf(Str,L"  Minor Code %x", MinorCode);
		gAmiPostMgr->DisplayPostMessage(Str);
    } else {
		gAmiPostMgr->DisplayPostMessage(L"Error Code None");
		gAmiPostMgr->DisplayPostMessage(L"  Class Code None");
		gAmiPostMgr->DisplayPostMessage(L"  Major Code None");
		gAmiPostMgr->DisplayPostMessage(L"  Minor Code None");
	}

	gAmiPostMgr->DisplayPostMessage(L"Press anykey to continue");

	while(1){
		gBS->WaitForEvent(1, &(gST->ConIn->WaitForKey), &Index);
		gST->ConIn->ReadKeyStroke(gST->ConIn, &Key);
		if((Key.UnicodeChar != 0) || (Key.ScanCode != 0)) break;
	}
					
	return EFI_SUCCESS; 
}

//*************************************************************************
//*************************************************************************
//**                                                                     **
//**        (C)Copyright 1987-2013, American Megatrends, Inc.            **
//**                                                                     **
//**                       All Rights Reserved.                          **
//**                                                                     **
//**      5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093           **
//**                                                                     **
//**                       Phone: (770)-246-8600                         **
//**                                                                     **
//*************************************************************************
//*************************************************************************
