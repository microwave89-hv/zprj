//**********************************************************************
//**********************************************************************
//**                                                                  **
//**        (C)Copyright 1985-2012, American Megatrends, Inc.         **
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
// $Header: /Alaska/SOURCE/Modules/RsdpPlus/ManageShadowRam.c 8     3/05/13 4:33a Norlwu $
//
// $Revision: 8 $
//
// $Date: 3/05/13 4:33a $
//**********************************************************************
// Revision History
// ----------------
// $Log: /Alaska/SOURCE/Modules/RsdpPlus/ManageShadowRam.c $
// 
// 8     3/05/13 4:33a Norlwu
// [TAG]  		EIP116590
// [Category]  	Bug Fix
// [Severity]  	Normal
// [Symptom]  	Using HeapToF000 to insert 2 datas with alignment will
// cause a part of 1st data covered by 2nd data
// [RootCause]  	It's wrong to update for gE000BuffLength and
// gF000BuffLength.
// [Solution]  	Use EndOfDataPtr and HeapPtr to calculate BuffLength.
// [Files]  		ManageShadowRam.c
// 
// 7     1/17/13 2:52a Norlwu
// [TAG]  		EIP108029
// [Category]  	Bug Fix
// [Severity]  	Normal
// [RootCause]  	Cause by Fastboot enable.
// [Solution]  	Add EraseShadowAfterEfiBoot() under in elink
// ReturnNormalMode.
// [Files]  		RsdpPlus.sdl
// ManageShadowRam.c
// 
// 6     10/25/12 3:45a Norlwu
// [TAG]  		EIP104587
// [Category]  	Bug Fix
// [Severity]  	Important
// [Symptom]  	Update RsdpPlus to 4.6.4.0_RsdpPlus_04 with Core 4.6.5.4.
// it hang up when exit Shell to legacy boot
// [RootCause]  	It's wrong backup data size. So if restore the data into
// E000 and F000, it will cause the system halt when boot to legacy.
// [Solution]  	Change backup size to current usage size.
// [Files]  		ManageShadowRam.c
// 
// 5     10/21/12 11:39p Norlwu
// Fixed the system halt when exit shell enviroment.
// 
// 4     9/17/12 11:32p Norlwu
// [TAG]  		EIP92735
// [Category]  	Improvement
// [Description]  	Please help to return the pointer and offset of
// HeapToF000 in MANAGE_SHADOW_RAM_PROTOCOL
// [Files]  		RsdpPlus.c
// ManageShadowRam.c
// ManageShadowProtocol.h
// 
// 3     8/17/12 8:12a Norlwu
// [TAG]  		EIP98247
// [Category]  	Improvement
// [Description]  	[RsdpPlus]Add alignment support in
// MANAGE_SHADOW_RAM_PROTOCOL
// [Files]  		RsdpPlus.sdl
// RsdpPlus.mak
// RsdpPlus.c
// ManageShadowRam.c
// ManageShadowRam.h
// 
// 2     7/27/12 6:58a Norlwu
// [TAG]  		EIP94704
// [Category]  	Bug Fix
// [Severity]  	Important
// [Symptom]  	Cause the system hatl at post time.
// [RootCause]  	ManageShasdow protocl is anot able to installed, when
// monitor was disconnected.So change the register event to
// BdsAllDeriverConnectGuid and if locate protocl failure return status
// continue.
// [Solution]  	[HP_DTO_emodule] token DEFAULT_CSM_LAUNCH_POLICY=0 and
// BIOS hang with FastBoot enable when monitor was disconnected
// [Files]  		RsdpPlusLInk.c
// ManageShadowRam.c
// 
// 1     2/09/12 3:06a Norlwu
// [TAG]  		EIP81756
// [Category]  	New Feature
// [Description]  	Enhance RspdPlus module.
// Install Shadow Ram Protocol and shadow ram protocl.
// [Files]  		ManageShadowRam.c
// ShadowRamProtocol.h
// 
//**********************************************************************
//<AMI_FHDR_START>
//
// Name:  		ManageShadowRam.c
//
// Description:	
//
//<AMI_FHDR_END>
//**********************************************************************

#include <AmiDxeLib.h>
#include <Protocol\ConsoleControl.h>
#include <token.h>
#include <AmiCspLib.h>
#include <Protocol\ManageShadowProtocol.h>
#include "ShadowRamProtocol.h"

#define BDS_ALL_DRIVERS_CONNECTED_PROTOCOL_GUID \
    {0xdbc9fd21, 0xfad8, 0x45b0, 0x9e, 0x78, 0x27, 0x15, 0x88, 0x67, 0xcc, 0x93}

//EFI_GUID gConOutStartedGuid = CONSOLE_OUT_DEVICES_STARTED_PROTOCOL_GUID;
EFI_GUID gAllDriverConnectGuid = BDS_ALL_DRIVERS_CONNECTED_PROTOCOL_GUID;	
EFI_GUID gShdowRamProtocolGuid = SHADOW_RAM_PROTOCOL_GUID;
EFI_GUID gManageShdowRamProtocolGuid = MANAGE_SHADOW_RAM_PROTOCOL_GUID;

VOID UpdateShadowBeforEfiBoot(VOID);
VOID EraseShadowAfterEfiBoot(VOID);
EFI_STATUS HeapToE000(IN UINT8 *pData, UINT32 Align, IN UINTN Length, IN OUT DATA_BUFF_STRUC	*pData2 OPTIONAL);
EFI_STATUS HeapToF000(IN UINT8 *pData, UINT32 Align, IN UINTN Length, IN OUT DATA_BUFF_STRUC	*pData2 OPTIONAL);

EFI_HANDLE	gShadowRameHandle = NULL;
EFI_HANDLE	gManageShadowRamHandle = NULL;
UINT8 	*gE000HeapPtr = NULL;
UINT8 	*gF000HeapPtr = NULL;
UINT8	*gESegStore = NULL;
UINT8	*gFSegStore = NULL;
UINT8	EsegUserCount = 0, FsegUserCount = 0;
UINTN	gE000BuffLength = 0;
UINTN	gF000BuffLength = 0;
UINTN	gBufferSize = 0x10000;


SHADOW_RAM_PROTOCOL gShadowRamProtocol = 
{
	UpdateShadowBeforEfiBoot,
	EraseShadowAfterEfiBoot
};

MANAGE_SHADOW_RAM_PROTOCOL gManageShadowRamProtocol =
{
	HeapToE000,
	HeapToF000
};

//************** Update Shadow Ram Hook support ****************************
extern UPDATE_E000_SHDOW_RAM_HOOK UPDATE_E000_SHADOW_RAM_HOOK_LIST EndOfUpdateE000ShadowRamHookList;
UPDATE_E000_SHDOW_RAM_HOOK* UpdateE000ShdowRamHookList[] = {UPDATE_E000_SHADOW_RAM_HOOK_LIST NULL};

extern UPDATE_F000_SHDOW_RAM_HOOK UPDATE_F000_SHADOW_RAM_HOOK_LIST EndOfUpdateF000ShadowRamHookList;
UPDATE_F000_SHDOW_RAM_HOOK* UpdateF000ShdowRamHookList[] = {UPDATE_F000_SHADOW_RAM_HOOK_LIST NULL};

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   OemUpdateE000ShdowRamHook
//
// Description: 
//              
//
// Input:
//
// Output: VOID
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID OemUpdateE000ShdowRamHook(
    IN UINT32*	pShadowRam,
	IN UINTN	UsageLength
)
{
    UINTN i;
    
    for (i = 0; UpdateE000ShdowRamHookList[i] != NULL; i++) 
        UpdateE000ShdowRamHookList[i](pShadowRam,UsageLength);
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   OemUpdateF000ShdowRamHook
//
// Description: 
//              
//
// Input:	IN UINT32*	pShadowRam
//			IN UINTN	UsageLength
//
// Output: VOID
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID OemUpdateF000ShdowRamHook(
    IN UINT32*	pShadowRam,
	IN UINTN	UsageLength
)
{
    UINTN i;
    
    for (i = 0; UpdateF000ShdowRamHookList[i] != NULL; i++) 
        UpdateF000ShdowRamHookList[i](pShadowRam,UsageLength);
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure: 	UpdateShadowBeforEfiBoot
//
// Description:	This is "BeforeEfiBootLaunchHook" elink function.
//				It will store original data of Shadow ram and then copy
//				shadow buff's data to shadow ram. 
//				
// Input:	VOID
//
// Output:	VOID
//      
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID UpdateShadowBeforEfiBoot(VOID)
{
	EFI_STATUS	Status;
	UINT32 E000Offset = 0xE0000;
	UINT32 F000Offset = 0xF0000;

	TRACE((-1,"Entry Update Shadow Ram!!!\n"));	

	//unlock shadow ram
	OemRuntimeShadowRamWrite(TRUE);

	TRACE((-1,"RsdpPlus (UpdateShadowBeforEfiBoot): gE000BuffLength [0x%x] \n",gE000BuffLength));

	if(gE000BuffLength != 0){
		Status = pBS->AllocatePool(
					EfiBootServicesData,
					gE000BuffLength,
					&gESegStore
					);
		ASSERT_EFI_ERROR(Status);
		if(EFI_ERROR(Status))
			return;
		
		pBS->CopyMem(gESegStore,(UINT32*)E000Offset,gE000BuffLength);
		MemSet((VOID*)E000Offset,gE000BuffLength, 0);
		pBS->CopyMem((UINT32*)E000Offset,gE000HeapPtr,gE000BuffLength);
		TRACE((-1,"E000 Info : Data length %d bytes, There are %d data in Shadow Ram!!!\n",gE000BuffLength, EsegUserCount));
		OemUpdateE000ShdowRamHook((UINT32*)E000Offset, gE000BuffLength);
	}

	TRACE((-1,"RsdpPlus (UpdateShadowBeforEfiBoot): gF000BuffLength [0x%x] \n",gF000BuffLength));
	if(gF000BuffLength != 0){
		Status = pBS->AllocatePool(
					EfiBootServicesData,
					gF000BuffLength,
					&gFSegStore
					);
		ASSERT_EFI_ERROR(Status);
		if(EFI_ERROR(Status))
			return;
		
		pBS->CopyMem(gFSegStore,(UINT32*)F000Offset,gF000BuffLength);
		MemSet((VOID*)F000Offset,gF000BuffLength, 0);
		pBS->CopyMem((UINT32*)F000Offset,gF000HeapPtr,gF000BuffLength);
		TRACE((-1,"F000 Info : Data length %d bytes, There are %d data in Shadow Ram!!!\n",gF000BuffLength, FsegUserCount));
		OemUpdateF000ShdowRamHook((UINT32*)F000Offset, gE000BuffLength);
	}

	//Lock shadow ram
	OemRuntimeShadowRamWrite(FALSE);

	return;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure: 	EraseShadowAfterEfiBoot
//
// Description: This is "AfterEfiBootLaunchHook" elink function.
//				It will restore original data to Shadow ram. 
//				
// Input:	VOID
//
// Output:	VOID
//      
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID EraseShadowAfterEfiBoot(VOID)
{
	UINT32 E000Offset = 0xE0000;
	UINT32 F000Offset = 0xF0000;
	
	if(gE000BuffLength == 0 && gF000BuffLength == 0) return;
	
	TRACE((-1,"Store Shadow Ram to default!!!\n"));	
	OemRuntimeShadowRamWrite(TRUE);

 	if(gE000BuffLength != 0){
		pBS->CopyMem((UINT32*)E000Offset,gESegStore,gE000BuffLength);
		pBS->FreePool(gESegStore);
		gE000BuffLength = 0;
		EsegUserCount = 0;	
	}

	if(gF000BuffLength != 0){
		pBS->CopyMem((UINT32*)F000Offset,gFSegStore,gF000BuffLength);
		pBS->FreePool(gFSegStore);
		gF000BuffLength = 0;
		FsegUserCount = 0;
	}
	
	OemRuntimeShadowRamWrite(FALSE);

	return;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure: 	HeapToE000
//
// Description: This is protocol function.
//				According to input data and copy those datas to buffer.
//
// Input:	UINT8 	*pData
//			UINT32	Align
//			UINTN 	Length
//			DATA_BUFF_STRUC *pData2 OPTIONAL
//
// Output:	EFI_STATUS
//      
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS HeapToE000(
	IN UINT8 *pData,
	IN UINT32 Align,
	IN UINTN Length,
	IN OUT DATA_BUFF_STRUC *pData2 OPTIONAL)
{

	UINT8	*DataPtr = NULL;
	UINT8	*EndOfDataPtr = NULL;

	if(pData == NULL || Length == 0)
		return EFI_INVALID_PARAMETER;

	if((gE000BuffLength + Length) > gBufferSize)
		return EFI_BUFFER_TOO_SMALL;

	if(Align != 0){
		DataPtr = (UINT8*)(( (UINT32)((UINTN)gE000HeapPtr + gE000BuffLength)& ~(Align - 1)) + Align);
	}else{
		DataPtr = gE000HeapPtr + gE000BuffLength;
	}

	if(pData2 != NULL){
		pData2->BuffAddress = (UINTN)gE000HeapPtr;
		//pData2->UsedLength = gE000BuffLength;
		pData2->UsedLength = (UINTN)(DataPtr - gE000HeapPtr);
	}

	EndOfDataPtr = (UINT8*)((UINTN)DataPtr + Length);
	TRACE((-1,"RsdpPlus : Align [0x%x],DataPtr [0x%lx],EndOfDataPtr [0x%lx] \n",Align,DataPtr,EndOfDataPtr));
	
	if(EndOfDataPtr > (gE000HeapPtr + gBufferSize))
		return EFI_BUFFER_TOO_SMALL;

	pBS->CopyMem(DataPtr, pData, Length);

	//gE000BuffLength = gE000BuffLength + (UINTN)(EndOfDataPtr - DataPtr);
	gE000BuffLength = (UINTN)(EndOfDataPtr - gE000HeapPtr);
	TRACE((-1,"RsdpPlus (HeapToE000): gE000BuffLength [0x%x] \n",gE000BuffLength));

	EsegUserCount++;

	return EFI_SUCCESS;		
}
		
//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure: 	HeapToF000
//
// Description: This is protocol function.
//				According to input data and copy those datas to buffer.
//				
// Input:	UINT8 *pData
//			UINT32 Align
//			UINTN Length
//			DATA_BUFF_STRUC *pData2 OPTIONAL
//
// Output:	EFI_STATUS
//      
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS HeapToF000(
	IN UINT8 *pData,
	IN UINT32 Align,
	IN UINTN Length,
	IN OUT DATA_BUFF_STRUC *pData2 OPTIONAL)
{
	UINT8	*DataPtr = NULL;
	UINT8	*EndOfDataPtr = NULL;


	if(pData == NULL || Length == 0)
		return EFI_INVALID_PARAMETER;

	if((gF000BuffLength + Length) > gBufferSize)
		return EFI_BUFFER_TOO_SMALL;

	if(Align != 0){
		DataPtr = (UINT8*)(( (UINT32)((UINTN)gF000HeapPtr + gF000BuffLength)& ~(Align - 1)) + Align);
	}else{
		DataPtr = gF000HeapPtr + gF000BuffLength;
	}

	if(pData2 != NULL){
		pData2->BuffAddress = (UINTN)gF000HeapPtr;
		//pData2->UsedLength = gF000BuffLength;
		pData2->UsedLength = (UINTN)(DataPtr - gF000HeapPtr);
	}

	EndOfDataPtr = (UINT8*)((UINTN)DataPtr + Length);
	TRACE((-1,"RsdpPlus : Align [0x%x],DataPtr [0x%lx],EndOfDataPtr [0x%lx] \n",Align,DataPtr,EndOfDataPtr));
	
	if(EndOfDataPtr > (gF000HeapPtr + gBufferSize))
		return EFI_BUFFER_TOO_SMALL;

	pBS->CopyMem(DataPtr, pData, Length);

	//gF000BuffLength = gF000BuffLength + (UINTN)(EndOfDataPtr - DataPtr);
	gF000BuffLength = (UINTN)(EndOfDataPtr - gF000HeapPtr);
	TRACE((-1,"RsdpPlus (HeapToF000): gF000BuffLength [0x%x] \n",gF000BuffLength));

	FsegUserCount++;

	return EFI_SUCCESS;		
}


//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure: 	ShadowRamCallBack
//
// Description: Install Shadow Ram Protocol.
//				
// Input:	EFI_EVENT	Event
//			VOID 		*Context
//
// Output:	EFI_STATUS	Status
//      
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS ShadowRamCallBack(IN EFI_EVENT Event,IN VOID *Context)
{
	EFI_STATUS	Status;
	
	Status = pBS->InstallProtocolInterface(
								&gShadowRameHandle,
								&gShdowRamProtocolGuid,
								EFI_NATIVE_INTERFACE,
								&gShadowRamProtocol
								);
	if(EFI_ERROR(Status)) return Status;
	pBS->CloseEvent(Event);
	
	return Status;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure: 	ManageShadowRamEntryPoint
//
// Description: Entry point for RsdpPlus initialization.
//				Register a ConOutStarted protocol callback function.
//				And allocate two buff for Manage Shadow Ram protocol used.				 
//				Install Manage Shadow Ram protocol.
//
// Input:	EFI_HANDLE			ImageHandle
//			EFI_SYSTEM_TABLE 	*SystemTable
//
// Output:	EFI_STATUS	Status
//      
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS ManageShadowRamEntryPoint(
	IN EFI_HANDLE ImageHandle,
	IN EFI_SYSTEM_TABLE *SystemTable
)
{
	EFI_EVENT	Event;
	EFI_STATUS	Status;
	VOID		*Registration;
	static	EFI_PHYSICAL_ADDRESS	E000PagePtr;
	static 	EFI_PHYSICAL_ADDRESS	F000PagePtr;

	InitAmiLib(ImageHandle,SystemTable);

   	Status = RegisterProtocolCallback(
				&gAllDriverConnectGuid,
				ShadowRamCallBack,
				NULL,   // Context
				&Event,
				&Registration
				);
	if(EFI_ERROR(Status)) return Status;

	Status = pBS->AllocatePages(
                 AllocateAnyPages, 
                 EfiBootServicesData, 
                 16,
                 &E000PagePtr);
	ASSERT_EFI_ERROR(Status);
	gE000HeapPtr = (UINT8*)E000PagePtr;
	TRACE((-1,"RsdpPlus : gE000HeapPtr [0x%lx] \n",gE000HeapPtr));

	Status = pBS->AllocatePages(
				AllocateAnyPages, 
                EfiBootServicesData, 
                16,
                &F000PagePtr);
	ASSERT_EFI_ERROR(Status);
	gF000HeapPtr = (UINT8*)F000PagePtr;
	TRACE((-1,"RsdpPlus : gF000HeapPtr [0x%lx] \n",gF000HeapPtr));

	Status = pBS->InstallProtocolInterface(
					&gManageShadowRamHandle,
					&gManageShdowRamProtocolGuid,
					EFI_NATIVE_INTERFACE,
					&gManageShadowRamProtocol
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
//**      5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093        **
//**                                                                  **
//**                       Phone: (770)-246-8600                      **
//**                                                                  **
//**********************************************************************
//**********************************************************************
