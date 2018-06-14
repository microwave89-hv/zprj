//*************************************************************************
//*************************************************************************
//**                                                                     **
//**        (C)Copyright 1985-2011, American Megatrends, Inc.            **
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
// $Header: /Alaska/SOURCE/Modules/SMM/SMMBase/SmmBase.c 73    2/13/12 4:41p Markw $
//
// $Revision: 73 $
//
// $Date: 2/13/12 4:41p $
//**********************************************************************
// Revision History
// ----------------
// $Log: /Alaska/SOURCE/Modules/SMM/SMMBase/SmmBase.c $
// 
// 73    2/13/12 4:41p Markw
// [TAG]  		EIP83005
// [Category]  	Improvement
// [Description]  	Some framework based SMM libraries expect a DXE image
// handle on input. However, PI 1.1 SMM drivers expect a SMM handle on
// input.
// Update code to provide proper EFI_HANDLE when calling SMM functions.
// [Files]  		SmmBase.c, SmmDriverDispatcher.c
// 
// 72    8/25/11 10:29a Markw
// [TAG]  		EIP64115
// [Category]  	Bug Fix
// [Severity]  	Normal
// [Symptom]  	PI 1.1 - unable to install protocol on image handle.
// [RootCause]  	Image handle is created by AMI code, but protocol handles
// are created by Intel code.
// [Solution]  	Create a new dummy handle from Intel's code and use that a
// the image handle in the entry point.
// [Files]  		SmmBase.c
// 
// 71    2/07/11 3:35p Markw
// [TAG]  		EIP53481
// [Category]  	New Feature
// [Description]  	Add PIWG 1.1 SMM support
// [Files]  		Smm.sdl, SmmPrivateShared.h, SmmDispatcher.mak,
// SmmDispatcher.h, SmmDispatcher.c,
// Smst.c, SmmPiSmst.c, SmmInit.c, SmmBase.c, SmmBase2.c,
// SmmDriverDispatcher.c, Smm Framewwork Protocol files, SmmPi.h,
// Smm Pi Protocol files, SmmPciRbio files
// 
// 70    12/28/09 11:07a Markw
// EIP #32378 - Use SDL token to determine how much memory to page to be
// able to page above 4GB.
// 
// 69    11/23/09 11:04a Markw
// Add back SMM Communicate function. Smm runtime module needed this.
// 
// 68    11/05/09 4:31p Markw
// SMM Base functions pre-initalize Status to EFI_DEVICE_ERROR in case sw
// smi doesn't happen.
// 
// 67    10/13/09 3:42p Markw
// EIP #27823 - Fix allocating SMM driver below 1MB if out of SMM memory.
// 
// 66    8/11/09 11:47a Markw
// Removed Legacy registration. This is removed from latest PI and not
// used by projects.
// 
// 65    8/05/09 2:59p Markw
// When functions aren't available in BDS for SMM security, return proper
// error of EFI_UNSUPPORTED.
// 
// 64    7/17/09 4:19p Markw
// Added back changes 60 and 61.
// 
// 63    7/16/09 8:12p Markw
// EIP #24284 -  Correct order SmmCpuInfo structure. It's was ordered
// incorrectly the same as CpuInfo. Thus, the wrong APIC ID could be used
// when starting unstarted APs if the BSP was changed.
// 
// 62    7/08/09 8:03p Markw
// Update headers.
// 
// 61    6/25/09 4:15p Markw
// Move setting gDispatcherPrivate->SmrrEnable outside condition.
// 
// 60    6/10/09 3:17p Markw
// Remove extra freepool.
// 
// 59    1/26/09 5:29p Markw
// EIP 14800: Aptio 4.x SMI Code vulnerablity. Disable call back inside
// SMM before BDS can launch option roms.
// 
// 58    1/22/09 1:07p Markw
// EIP #18671 (OPEN) Clear SW SMI status and set EOS inside SMM. Move
// Clear from Base function. 
// 
// 57    12/24/08 10:55a Markw
// EIP #18423: Adjust EBDA location as more EBDA data is allocated.
// 
// 56    12/23/08 2:19p Markw
// EIP #17900  Set up TSS. Borland C in DOS hangs otherwise.
// 
// 55    11/21/08 5:02p Markw
// Use 32-bit CPU Count.
// 
// 54    10/06/08 6:27p Markw
// Add generic Smm Memory libary hook.
// 
// 53    9/26/08 4:51p Markw
// InSmm is now a runtime function.
// 
// 52    9/15/08 4:00p Markw
// Initialize HandlerListHead and FloatingPointSave in Dispatcher Private
// structure.
// 
// 51    9/09/08 3:06p Markw
// Align Dispatcher to 4k.
// 
// 50    9/07/08 12:47a Markw
// Separate SMM Private structure into inside SMM and outside SMM
// structure.
// 
// 49    8/27/08 9:07p Markw
// Nehalem SMRR is not WB. Fix VIA not supporting cpuid 0x80000008.
// 
// 47    6/10/08 6:46p Markw
// Disable SMM Thunk if no A & B seg, and no CSM.
// 
// 46    6/10/08 1:30p Markw
// Update gdt for Smm Thunk for APs.
// 
// 45    6/09/08 5:42p Markw
// Provide support for any CPU to be BSP by providing APIC for each CPU
// and allowing CPU 0  to have a structure for controlling as an Ap.
// 
// 44    5/23/08 5:28p Markw
// Undo change from previous revision to lock smm before os with AMI
// debugger.
// 
// 43    5/23/08 12:25p Markw
// Disallow registering now disallows all callbacks.
// 
// 42    4/04/08 6:23p Markw
// Change SMM base here instead of CPU module.
// 
// 41    3/18/08 4:59p Markw
// Change 64-bit pages to have the first 2MB as 4k pages. This is so
// different MTRR types will not overlap a page.
// 
// 40    3/11/08 12:46p Markw
// 
// 39    3/04/08 9:01a Markw
// Updated EBDA allocation for SMM THUNK to use the changed protocol from
// 4.5.3_CSM.6.43_56.
// 
//**********************************************************************

//<AMI_FHDR_START>
//---------------------------------------------------------------------------
//
// Name:		SmmBase.c
//
// Description:	Provide functions to register drivers with SMM, 
//				determine if driver is in SMM Mode, register call backs,
//      		provide callback buffer, return SMST table pointer,
//				and allocate memory.
//
//---------------------------------------------------------------------------
//<AMI_FHDR_END>


//This include should be first.
#include "SmmPrivateShared.h"

#include <Protocol\LoadPe32Image.h>
#include <Protocol\LoadedImage.h>
#include <token.h>
#include <Ffs.h>
#include <AmiDxeLib.h>

#if SMM_USE_FRAMEWORK
#include <Smm.h>
#include <Protocol\SmmBase.h>
#endif

#if SMM_USE_PI
#include <SmmPi.h>
#include <Protocol\SmmReadyToLock.h>
#endif

UINT8 gDisallowCallbacks = FALSE;
BOOLEAN gRegisterForPi = FALSE;

VOID SmmRegisterHandler();

#if SMM_USE_FRAMEWORK
VOID SmmUnregisterHandler();
VOID SmmCommunicate();
VOID SmmAllocatePool();
VOID SmmFreePool();

extern EFI_SMM_SYSTEM_TABLE             *gSmstTable;
#endif

#if SMM_USE_PI
extern EFI_SMM_SYSTEM_TABLE2            *gSmstTable2;
#endif

extern EFI_HANDLE                       gThisImageHandle;
extern SMM_BASE_PRIVATE_STRUCT          *gBasePrivate;
extern EFI_PE32_IMAGE_PROTOCOL          *gPe32Image;
extern SMM_DISPATCHER_PRIVATE_STRUCT    *gDispatcherPrivate;

EFI_GUID gEfiLoadedImageProtocolGuid = EFI_LOADED_IMAGE_PROTOCOL_GUID;


#if SMM_USE_PI
//EFI_GUID gEfiSmmReadyToLockProtocolGuid = EFI_SMM_READY_TO_LOCK_PROTOCOL_GUID;
EFI_GUID gSmmImageHandleDummyGuid = {0x33aa4ba3, 0x5439, 0x4658, 0x89, 0x51, 0xe2, 0xe7, 0xea, 0xf8, 0x1c, 0x49};
#endif

VOID CallFuncInSmm(IN VOID func());

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure: SetDisallowRegistering
//
// Description:	 Don't allow registering handlers from SMM.
//
// Input: VOID 
//
// Output:
//	None
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

VOID SetDisallowRegistering()
{
#if SMM_USE_PI
    EFI_HANDLE Handle = NULL;
#endif

    //Dispatcher has a private variable, is set after this.
    //Thus, once DisallowCallbacks is set, it can not be unset.
    gBasePrivate->DisallowCallbacks = TRUE;
    gDisallowCallbacks = TRUE;

#if SMM_USE_PI
    gSmstTable2->SmmInstallProtocolInterface(
        &Handle,
        &gEfiSmmReadyToLockProtocolGuid,
        EFI_NATIVE_INTERFACE,
        NULL
    );
#endif
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure: EfiSmmRegister
//
// Description:	Register a driver with the SMM Handler.
//  * Loads SMM PE32 Driver into SMM memory and give control to the entry point.
//  * Or, loads SMM 16-bit driver into SMM memory. It is given control during SMM mode.
//
// Input: 
//	IN EFI_SMM_BASE_PROTOCOL	*This
//	IN EFI_DEVICE_PATH_PROTOCOL	*FilePath
//	IN VOID						*SourceBuffer OPTIONAL
//	IN UINTN					SourceSize
//	OUT EFI_HANDLE				*ImageHandle
//	IN BOOLEAN					LegacyIA32Binary OPTIONAL
//
// Output:
//	EFI_STATUS 
//		* EFI_SUCCESS - Driver was registered.
//		* EFI_OUT_OF_RESOURCES - No additional resources to load handler.
//		* EFI_INVALID_PARAMETER - Invalid inputs.
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS EfiSmmRegister(
	IN EFI_SMM_BASE_PROTOCOL	*This,
	IN EFI_DEVICE_PATH_PROTOCOL	*FilePath,
	IN VOID						*SourceBuffer OPTIONAL,
	IN UINTN					SourceSize,
	OUT EFI_HANDLE				*ImageHandle,
	IN BOOLEAN					LegacyIA32Binary OPTIONAL
	)
{

    if (gDisallowCallbacks) return EFI_UNSUPPORTED;
	if (LegacyIA32Binary) return EFI_UNSUPPORTED;

	gBasePrivate->CallbackParameters.RegisterHandler.FilePath			= FilePath;
	gBasePrivate->CallbackParameters.RegisterHandler.SourceBuffer		= SourceBuffer;
	gBasePrivate->CallbackParameters.RegisterHandler.SourceSize			= SourceSize;
	gBasePrivate->CallbackParameters.RegisterHandler.ImageHandle		= ImageHandle;
	gBasePrivate->CallbackParameters.RegisterHandler.LegacyIA32Binary	= FALSE;
	gBasePrivate->CallbackStatus = EFI_DEVICE_ERROR; //Pre-init - SW SMI didn't happen.

	CallFuncInSmm(SmmRegisterHandler);

	return gBasePrivate->CallbackStatus;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure: SmmRegisterHandler
//
// Description:	 Does the actual work for EfiSmmRegisterHandler.
//
// Input: VOID
//
// Output:
//	None
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

//Can Legacy and PE32 handle overlap?
VOID SmmRegisterHandler()
{
	EFI_PHYSICAL_ADDRESS EntryPoint, DstBuffer;
	UINTN NumberOfPages,RealNumberOfPages;
	EFI_STATUS Status;
    EFI_HANDLE  NewImageHandle;
    EFI_HANDLE  SmmImageHandle;

    //Pre-allocate plenty of pages for the SMM driver, so LoadPeImage will only decompress the driver once.
    //If memory is not enough, the number of pages will returned and enough memory allocated,
    //  then LoadPeImage will decompress the driver again.
    //Any extra pages will be freed and not wasted.
#define DEFAULT_SMM_DRIVER_PAGES 16
	NumberOfPages = DEFAULT_SMM_DRIVER_PAGES;
#if SMM_USE_FRAMEWORK
	Status = gSmstTable->SmmAllocatePages(
#else
    Status = gSmstTable2->SmmAllocatePages(
#endif
	        AllocateAnyPages, 0, NumberOfPages, &DstBuffer
	);
    if (EFI_ERROR(Status)) {
      	//If allocation failed, so try the minimum of 1 page.
        NumberOfPages = 1;
#if SMM_USE_FRAMEWORK
    Status = gSmstTable->SmmAllocatePages(
#else
    Status = gSmstTable2->SmmAllocatePages(
#endif
    		AllocateAnyPages, 0, NumberOfPages, &DstBuffer
    	);
        ASSERT_EFI_ERROR(Status);
        if (EFI_ERROR(Status)) {
            gBasePrivate->CallbackStatus = Status;
            return;
        }
    }

    //DstBuffer can't be 0, or LoadPeImage will allocate non-SMM memory.
	RealNumberOfPages = NumberOfPages;
	Status=gPe32Image->LoadPeImage(
		gPe32Image, gThisImageHandle,
		gBasePrivate->CallbackParameters.RegisterHandler.FilePath,		//Either DevicePath or
		gBasePrivate->CallbackParameters.RegisterHandler.SourceBuffer,	//Buffer. This will be zero if DevicePath.
		gBasePrivate->CallbackParameters.RegisterHandler.SourceSize,
		DstBuffer, &RealNumberOfPages,
		&NewImageHandle,
		&EntryPoint, EFI_LOAD_PE_IMAGE_ATTRIBUTE_NONE
	);
	//If Image has been loaded, let's free extra memory
	if (!EFI_ERROR(Status) && RealNumberOfPages<NumberOfPages) {
#if SMM_USE_FRAMEWORK
	    gSmstTable->SmmFreePages(
#else
	    gSmstTable2->SmmFreePages(
#endif
			DstBuffer+EFI_PAGES_TO_SIZE(RealNumberOfPages),
			NumberOfPages-RealNumberOfPages
		);
	//If it's not enough memory, let's allocate new chunk and try again.
	} else if (Status==EFI_BUFFER_TOO_SMALL) {
		//Free Old Buffer
#if SMM_USE_FRAMEWORK
        gSmstTable->SmmFreePages(
#else
        gSmstTable2->SmmFreePages(
#endif
		        DstBuffer, NumberOfPages);
		//Allocate New Buffer
#if SMM_USE_FRAMEWORK
        Status = gSmstTable->SmmAllocatePages(
#else
        Status = gSmstTable2->SmmAllocatePages(
#endif
			AllocateAnyPages, 0, RealNumberOfPages, &DstBuffer
		);
		if (!EFI_ERROR(Status))
			Status=gPe32Image->LoadPeImage(
				gPe32Image, gThisImageHandle,
				gBasePrivate->CallbackParameters.RegisterHandler.FilePath,		//Either DevicePath or
				gBasePrivate->CallbackParameters.RegisterHandler.SourceBuffer,	//Buffer. This will be zero if DevicePath.
				gBasePrivate->CallbackParameters.RegisterHandler.SourceSize,
				DstBuffer, &RealNumberOfPages,
				&NewImageHandle,
				&EntryPoint, EFI_LOAD_PE_IMAGE_ATTRIBUTE_NONE
			);
	}
	if (!EFI_ERROR(Status)) {
	    EFI_LOADED_IMAGE_PROTOCOL *LoadedImage;
	    //EFI_IMAGE_ENTRY_POINT EntryPoint;

	    Status = pBS->HandleProtocol(NewImageHandle, &gEfiLoadedImageProtocolGuid, &LoadedImage);
	    ASSERT_EFI_ERROR(Status);

	    TRACE((TRACE_ALWAYS,"SMM."));
#ifdef EFI_DEBUG
{
//Debug message: name/entry point of the module being started
BOOLEAN GetImageName(EFI_HANDLE, CHAR8 *);
VOID Trace(UINTN Level, CHAR8 *sFormat,...);
CHAR8 sName[0x100];

    GetImageName(NewImageHandle, sName);
    TRACE((TRACE_ALWAYS, "%s.Entry(%X)\n", sName, EntryPoint));
}
#endif

        SmmImageHandle = NewImageHandle;
#if SMM_USE_PI
        if (gRegisterForPi) {
            //Create an Image Handle for SMM driver, so the handle can be used to install new handles on.
            SmmImageHandle = NULL;
            Status = gSmstTable2->SmmInstallProtocolInterface(
                    &SmmImageHandle,
                    &gSmmImageHandleDummyGuid,
                    EFI_NATIVE_INTERFACE,
                    NULL   //Dummy
            );
            ASSERT_EFI_ERROR(Status);
        }
#endif

        gBasePrivate->CallbackParameters.RegisterHandler.ImageHandle = SmmImageHandle;

        Status = ((EFI_IMAGE_ENTRY_POINT)EntryPoint)(SmmImageHandle, pST);
		if (EFI_ERROR(Status)) 
#if SMM_USE_FRAMEWORK
		    gSmstTable->SmmFreePages(
#else
		    gSmstTable2->SmmFreePages(
#endif
				DstBuffer, RealNumberOfPages
			);
	}
	gBasePrivate->CallbackStatus = Status;
}

#if SMM_USE_FRAMEWORK

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure: EfiSmmUnregister
//
// Description:	Removes handler from being called in SMM.
//
// Input: 
//	IN EFI_SMM_BASE_PROTOCOL	*This
//	IN EFI_HANDLE				ImageHandle
//
// Output:
//	EFI_STATUS
//		* EFI_SUCCESS - Driver was unregistered.
//		* EFI_INVALID_PARAMETER - Image Handle doesn't exist.
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS EfiSmmUnregister(
	IN EFI_SMM_BASE_PROTOCOL	*This,
	IN EFI_HANDLE				ImageHandle
	)
{
    if (gDisallowCallbacks) return EFI_UNSUPPORTED;

	gBasePrivate->CallbackParameters.UnregisterHandler.ImageHandle = ImageHandle;
	gBasePrivate->CallbackStatus = EFI_DEVICE_ERROR; //Pre-init - SW SMI didn't happen.

	CallFuncInSmm(SmmUnregisterHandler);

	return gBasePrivate->CallbackStatus;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure: SmmUnregisterHandler
//
// Description:	Does the actual work for EfiSmmUnregisterHandler.
//
// Input: VOID 
//
// Output:
//	VOID
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

VOID SmmUnregisterHandler()
{
	gBasePrivate->CallbackStatus = EFI_UNSUPPORTED;
}


//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure: EfiSmmCommunicate
//
// Description:	Buffer location for EFI Call Back function.
//
// Input: 
//	IN EFI_SMM_BASE_PROTOCOL	*This
//	IN EFI_HANDLE				ImageHandle
//	IN OUT VOID					*CommunicationBuffer
//	IN OUT UINTN				*SourceSize
//
// Output:
//	EFI_STATUS 
//		* EFI_SUCCESS - Buffer is set.
//		* EFI_INVALID_PARAMETER - Buffer is NULL
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS EfiSmmCommunicate(
	IN EFI_SMM_BASE_PROTOCOL	*This,
	IN EFI_HANDLE				ImageHandle,
	IN OUT VOID					*CommunicationBuffer,
	IN OUT UINTN				*SourceSize
	)
{
    if (gDisallowCallbacks) return EFI_UNSUPPORTED;

	if (!CommunicationBuffer) return EFI_INVALID_PARAMETER;

	gBasePrivate->CallbackParameters.Communicate.ImageHandle			= ImageHandle;
	gBasePrivate->CallbackParameters.Communicate.CommunicationBuffer	= CommunicationBuffer;
	gBasePrivate->CallbackParameters.Communicate.SourceSize			    = SourceSize;
	gBasePrivate->CallbackStatus = EFI_DEVICE_ERROR; //Pre-init - SW SMI didn't happen.

	CallFuncInSmm(SmmCommunicate);
	
	return gBasePrivate->CallbackStatus;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure: SmmCommunicate
//
// Description:	Does the actual work for EfiSmmCommunicate.
//
// Input: VOID
//
// Output:
//	VOID
//
// Notes:
//  A runtime driver will have to call this function again for a virtual address.
//  Currently, virtual address are not automatically fixed up.
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

VOID SmmCommunicate()
{
//  A runtime driver will have to call this function again for a virtual address.
//  Currently, virtual address are not automaically fixed up. Also, no runtime drivers are
//  using this.

	HANDLER_LIST *Link;
	for (Link = gDispatcherPrivate->HandlerListHead;Link; Link = Link->Link) {
		if (Link->SmmImageHandle == gBasePrivate->CallbackParameters.Communicate.ImageHandle) {
			Link->CommunicationBuffer	    = gBasePrivate->CallbackParameters.Communicate.CommunicationBuffer;
			Link->SourceSize		        = gBasePrivate->CallbackParameters.Communicate.SourceSize;
			gBasePrivate->CallbackStatus	= EFI_SUCCESS;
			return;
		}
	}
	gBasePrivate->CallbackStatus = EFI_NOT_FOUND;
}


//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure: EfiSmmCallBackService
//
// Description:	Function for the SMM to call back.
//
// Input: 
//	IN EFI_SMM_BASE_PROTOCOL		*This
//	IN EFI_HANDLE					SmmImageHandle
//	IN EFI_SMM_CALLBACK_ENTRY_POINT	CallbackAddress
//	IN BOOLEAN						MakeLast OPTIONAL
//	IN BOOLEAN						FloatingPointSave OPTIONAL
//
// Output:
//	EFI_STATUS
//		* EFI_SUCCESS - Call back function set for Handle.
//		* EFI_OUT_OF_RESOURCES - Not enough memory to add callback.
//		* EFI_UNSUPPORTED - Caller not in SMM.
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS EfiSmmCallBackService(
	IN EFI_SMM_BASE_PROTOCOL		*This,
	IN EFI_HANDLE					SmmImageHandle,
	IN EFI_SMM_CALLBACK_ENTRY_POINT	CallbackAddress,
	IN BOOLEAN						MakeLast OPTIONAL,
	IN BOOLEAN						FloatingPointSave OPTIONAL
	)
{
	HANDLER_LIST	*Handler,*Link;

	if (!*gBasePrivate->InSmm) return EFI_UNSUPPORTED;
	
	if (gSmstTable->SmmAllocatePool(0,sizeof(HANDLER_LIST),&Handler) != EFI_SUCCESS)
		return EFI_OUT_OF_RESOURCES;
	
	Handler->EntryPoint	            = CallbackAddress;
	Handler->SmmImageHandle	        = SmmImageHandle;
    Handler->CommunicationBuffer    = 0;
    Handler->SourceSize             = 0;
	Handler->IsRoot                 = TRUE;
    Handler->IsPi                   = FALSE;
    Handler->Link                   = 0;

	if (FloatingPointSave) gDispatcherPrivate->FloatingPointSave = TRUE;

	//If very first add.
	if (!gDispatcherPrivate->HandlerListHead) {
		gDispatcherPrivate->HandlerListHead = Handler;
		return EFI_SUCCESS;
	}

	//If not MakeLast, add to beginning of list.
	if (!MakeLast) {
		Handler->Link = gDispatcherPrivate->HandlerListHead;
		gDispatcherPrivate->HandlerListHead = Handler;
		return EFI_SUCCESS;
	}

	//Add to end of list.
	for (Link = gDispatcherPrivate->HandlerListHead; Link->Link; Link = Link->Link);	//Find end of list
	Link->Link = Handler;
	return EFI_SUCCESS;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure: EfiSmmAllocatePool
//
// Description:	Allocate buffer from SMM Memory.
//
// Input: 
//	IN EFI_SMM_BASE_PROTOCOL	*This
//	IN EFI_MEMORY_TYPE			PoolType
//	IN UINTN					Size
//	OUT VOID					**Buffer
//
// Output:
//	EFI_STATUS
//		* EFI_SUCCESS - Allocation successful.
//		* EFI_OUT_OF_RESOURCES - Not enough space.
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS EfiSmmAllocatePool(
	IN EFI_SMM_BASE_PROTOCOL	*This,
	IN EFI_MEMORY_TYPE			PoolType,
	IN UINTN					Size,
	OUT VOID					**Buffer
	)
{
    if (gDisallowCallbacks) return EFI_UNSUPPORTED;

	gBasePrivate->CallbackParameters.AllocatePool.Size   = Size;
	gBasePrivate->CallbackParameters.AllocatePool.Buffer = Buffer;
	gBasePrivate->CallbackStatus = EFI_DEVICE_ERROR; //Pre-init - SW SMI didn't happen.

	CallFuncInSmm(SmmAllocatePool);
	
	return gBasePrivate->CallbackStatus;	
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure: SmmAllocatePool
//
// Description:	Does the actual work for EfiSmmAllocatePool.
//
// Input: VOID
//
// Output:
//	None
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

VOID SmmAllocatePool()
{
	gBasePrivate->CallbackStatus = gSmstTable->SmmAllocatePool(
		0,
		gBasePrivate->CallbackParameters.AllocatePool.Size,
		gBasePrivate->CallbackParameters.AllocatePool.Buffer
		);
}


//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure: EfiSmmFreePool
//
// Description:	Free pool of memory.
//
// Input: 
//	IN EFI_SMM_BASE_PROTOCOL	*This
//	IN VOID						*Buffer
//
// Output:
//	EFI_STATUS
//		* EFI_SUCCESS - Buffer freed
//		* EFI_INVALID_PARAMETER - Buffer invalid.
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS EfiSmmFreePool(
	IN EFI_SMM_BASE_PROTOCOL	*This,
	IN VOID						*Buffer
	)
{
    if (gDisallowCallbacks) return EFI_UNSUPPORTED;

	gBasePrivate->CallbackParameters.FreePool.Buffer = Buffer;
	gBasePrivate->CallbackStatus = EFI_DEVICE_ERROR; //Pre-init - SW SMI didn't happen.

	CallFuncInSmm(SmmFreePool);

	return gBasePrivate->CallbackStatus;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure: SmmFreePool
//
// Description:	Does the actual work for EfiSmmFreePool.
//
// Input: VOID
//
// Output:
//	None
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

VOID SmmFreePool()
{
	gBasePrivate->CallbackStatus = gSmstTable->SmmFreePool(
		gBasePrivate->CallbackParameters.FreePool.Buffer);
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure: EfiSmmGetSmstLocation
//
// Description:	Returns a pointer to the Smst.
//
// Input: 
//	IN EFI_SMM_BASE_PROTOCOL	*This
//	IN OUT EFI_SMM_SYSTEM_TABLE	**Smst
//
// Output:
//	EFI_STATUS
//		* EFI_SUCCESS - SMST address saved in *Smst.
//		* EFI_INVALID_PARAMETER - Smst = NULL.
//		* EFI_UNSUPPORTED - Not in SMM.
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS EfiSmmGetSmstLocation(
	IN EFI_SMM_BASE_PROTOCOL	*This,
	IN OUT EFI_SMM_SYSTEM_TABLE	**Smst
	)
{
	if (!*gBasePrivate->InSmm) return EFI_UNSUPPORTED;
	if (Smst == NULL) return EFI_INVALID_PARAMETER;

	*Smst = gSmstTable;
	return EFI_SUCCESS;
}

EFI_SMM_BASE_PROTOCOL gEfiSmmBase = {
	EfiSmmRegister,
	EfiSmmUnregister,
	EfiSmmCommunicate,
	EfiSmmCallBackService,
	NULL,           //EfiSmmInSmm is runtime function. This will be updated.
	EfiSmmAllocatePool,
	EfiSmmFreePool,
	EfiSmmGetSmstLocation,
};

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure: EfiSmmRegisterUnsupported
//
// Description:
//  The SMM Base Protocol function Register return unsupported after
//      BIOS is done executing.
//
// Input: 
//  IN EFI_SMM_BASE_PROTOCOL	*This
//	IN EFI_DEVICE_PATH_PROTOCOL	*FilePath
//	IN VOID						*SourceBuffer OPTIONAL,
//	IN UINTN					SourceSize
//	OUT EFI_HANDLE				*ImageHandle
//	IN BOOLEAN					LegacyIA32Binary OPTIONAL
//
// Output:
//  EFI_STATUS
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS EfiSmmRegisterUnsupported(
	IN EFI_SMM_BASE_PROTOCOL	*This,
	IN EFI_DEVICE_PATH_PROTOCOL	*FilePath,
	IN VOID						*SourceBuffer OPTIONAL,
	IN UINTN					SourceSize,
	OUT EFI_HANDLE				*ImageHandle,
	IN BOOLEAN					LegacyIA32Binary OPTIONAL
	)
{
    return EFI_UNSUPPORTED;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure: EfiSmmUnregisterUnsupported
//
// Description:
//  The SMM Base Protocol function UnRegister return unsupported after
//      BIOS is done executing.
//
// Input: 
//	IN EFI_SMM_BASE_PROTOCOL	*This
//	IN EFI_HANDLE				ImageHandle
//
// Output:
//  EFI_STATUS
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS EfiSmmUnregisterUnsupported(
	IN EFI_SMM_BASE_PROTOCOL	*This,
	IN EFI_HANDLE				ImageHandle
    )
{
    return EFI_UNSUPPORTED;
}
#endif

//*************************************************************************
//*************************************************************************
//**                                                                     **
//**        (C)Copyright 1985-2010, American Megatrends, Inc.            **
//**                                                                     **
//**                       All Rights Reserved.                          **
//**                                                                     **
//**      5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093           **
//**                                                                     **
//**                       Phone: (770)-246-8600                         **
//**                                                                     **
//*************************************************************************
//*************************************************************************
