//**********************************************************************
//**********************************************************************
//**                                                                  **
//**        (C)Copyright 1985-2011, American Megatrends, Inc.         **
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
// $Header: /Alaska/SOURCE/Core/EDK/DxeMain/AmiDxeInit.c 24    5/05/11 3:47p Artems $
//
// $Revision: 24 $
//
// $Date: 5/05/11 3:47p $
//**********************************************************************
// Revision History
// ----------------
// $Log: /Alaska/SOURCE/Core/EDK/DxeMain/AmiDxeInit.c $
// 
// 24    5/05/11 3:47p Artems
// Added DevicePathToText and DevicePathFromText protocols
// 
// 23    2/05/11 4:09p Artems
// EDK library functions CopyMem and ZeroMem moved to EdkLib.c
// 
// 22    9/29/10 8:05a Felixp
// Enhancement: Initialization of the library TheImageHandle variable is
// added.
// 
// 21    4/22/10 10:43p Felixp
// Install dummy instance of the security protocol when 
// INSTALL_DUMMY_SECURITY_PROTOCOL SDL token is set to "on".
// 
// 20    2/23/10 10:01p Felixp
// Updated to use CORE_COMBINED_VERSION token.
// 
// 19    11/13/09 4:31p Felixp
// Buffer overflow protection is added (calls to Sprintf replaced with
// Sprintf_s).
// 
// 18    7/30/09 4:04p Felixp
// Bug fix:
// Symptoms: memory corruption during DXE Core initialization.
// Details: the corruption was caused by the HOBs created in AmiDxeInit1. 
// The HOB creation moved to an earlier point (before HOB data is used by
// CoreInitializeMemoryServices).
// 
// 17    5/04/09 3:10p Felixp
// Creation of CPU HOB moved from AmiPeiInit.c to AmiDxeInit.c
// 
// 16    3/05/09 4:39p Oleksiyy
// EIP 18486: 3 GUID EXTENSION HOBs created. 
// Code clean up performed. 
// 
// 15    4/18/08 6:28p Felixp
// checkpoint(0x60) removed. Corresponsing status code (DXE_CORE_ENTRY is
// now reported at the and of DXE IPL using status code infrastructure
// 
// 14    3/12/08 12:44p Felixp
// Progress/Error codes reporting added
// 
// 13    2/21/08 5:05p Felixp
// FirmwareRevision field of the EFI system table is updated to use
// CORE_BUILD_NUMBER.
// 
// 12    9/05/07 4:22p Felixp
// FirmwareVendor field of the EFI_SYSTEM_TABLE was initialized with a
// pointer to boot time memory. However, this is a runtime field.
// File updated to allocate runtime memory for the field.
// 
// 11    10/12/06 9:43p Felixp
// 
// 10    10/12/06 6:51p Felixp
// UEFI2.0 support: DevicePathUtilities protocol added
// 
// 9     10/07/06 10:24a Felixp
// UIEFI2.0 support.
// Updated to EDK 20060904
// 
// 8     8/24/06 10:11a Felixp
// x64 support: warning/error fixes
// 
// 7     5/23/06 4:16a Felixp
// 
// 6     5/22/06 11:57a Felixp
// 
// 5     5/22/06 12:12a Felixp
// Vendor & Revision fields of ST initialized
// 
// 4     5/20/06 9:37p Felixp
// checkpoint 0x60 added
// debug message for drivers startting/stopping
// clean up
// 
// 3     5/19/06 10:46p Felixp
// Updated to EDK 03.16.06
// Cleanup
// 
// 2     4/30/06 9:41p Felixp
// 
// 1     3/13/06 2:00a Felixp
// 
//**********************************************************************
//<AMI_FHDR_START>
//
// Name:	AmiDxeInit.c
//
// Description:	
//
//<AMI_FHDR_END>
//**********************************************************************
#include<EFI.h>
#include<Protocol/Decompress.h>
#include<Protocol/DriverBinding.h>
#include<Protocol/DevicePathUtilities.h>
#include<Protocol/DevicePathToText.h>
#include<Protocol/DevicePathFromText.h>
#include<Protocol/Security.h>
#include<AmiDxeLib.h>
#include<AmiHobs.h>
#include<Token.h>
#include<Guid/PeiFlushInstructionCache.h>
#include<Guid/PeiPeCoffLoader.h>
#include<Guid/PeiTransferControl.h>


EFI_GUID gEfiPeiFlushInstructionCacheGuid = EFI_PEI_FLUSH_INSTRUCTION_CACHE_GUID;
EFI_GUID gEfiPeiPeCoffLoaderGuid = EFI_PEI_PE_COFF_LOADER_GUID;
EFI_GUID gEfiPeiTransferControlGuid = EFI_PEI_TRANSFER_CONTROL_GUID;
EFI_GUID gEfiStatusCodeSpecificDataGuid = EFI_STATUS_CODE_SPECIFIC_DATA_GUID;
typedef VOID (*INIT_PARTS)(VOID* p1, VOID*p2);
VOID InitParts(VOID* p1, VOID*p2);
extern EFI_SYSTEM_TABLE *gST;

extern EFI_DEVICE_PATH_FROM_TEXT_PROTOCOL EfiDevicePathFromTextProtocol;
extern EFI_DEVICE_PATH_TO_TEXT_PROTOCOL EfiDevicePathToTextProtocol;

///////////////////////////////////////////////////////////////
////===================== Print Protocol ==================.
#define EFI_PRINT_PROTOCOL_GUID \
	{ 0xdf2d868e, 0x32fc, 0x4cf0, 0x8e, 0x6b, 0xff, 0xd9, 0x5d, 0x13, 0x43, 0xd0 }

typedef struct _EFI_PRINT_PROTOCOL EFI_PRINT_PROTOCOL;

typedef UINTN (EFIAPI *EFI_VSPRINT)(
	OUT CHAR16 *StartOfBuffer, IN UINTN BufferSize,
	IN CHAR16 *FormatString, IN va_list Marker
);

struct _EFI_PRINT_PROTOCOL{
	EFI_VSPRINT VSPrint;
};

EFI_GUID guidPrint = EFI_PRINT_PROTOCOL_GUID;
EFI_PRINT_PROTOCOL Print = {&Swprintf_s_va_list};

////===================== Decompress Protocol ==================.
EFI_GUID guidDecompress = EFI_DECOMPRESS_PROTOCOL_GUID;
EFI_STATUS DecomprGetInfo (
	IN VOID *This,
	IN VOID *Source, IN UINT32 SourceSize,
	OUT UINT32 *DestinationSize, OUT UINT32 *ScratchSize
)
{
	return GetInfo(Source,SourceSize,DestinationSize,ScratchSize);
}

EFI_STATUS DecomprDecompress (
	IN VOID *This,
	IN VOID* Source, IN UINT32 SourceSize,
	IN OUT VOID* Destination, IN UINT32 DestinationSize,
	IN OUT VOID* Scratch, IN UINT32 ScratchSize
)
{
	return Decompress(Source,SourceSize,Destination,DestinationSize,Scratch,ScratchSize);
}

EFI_DECOMPRESS_PROTOCOL DecompressInterface = {&DecomprGetInfo, &DecomprDecompress};
EFI_DECOMPRESS_PROTOCOL *pDecompressInterface=&DecompressInterface;

////===================== Device Path Utilities Protocol ==================
EFI_DEVICE_PATH_UTILITIES_PROTOCOL DevicePathUtilitiesInstance =
{
    (EFI_DEVICE_PATH_UTILS_GET_DEVICE_PATH_SIZE)DPLength,
    (EFI_DEVICE_PATH_UTILS_DUP_DEVICE_PATH)DPCopy,
    (EFI_DEVICE_PATH_UTILS_APPEND_PATH)DPAdd,
    (EFI_DEVICE_PATH_UTILS_APPEND_NODE)DPAddNode,
    (EFI_DEVICE_PATH_UTILS_APPEND_INSTANCE)DPAddInstance,
    (EFI_DEVICE_PATH_UTILS_GET_NEXT_INSTANCE)DPNextInstance,
    (EFI_DEVICE_PATH_UTILS_IS_MULTI_INSTANCE)DPIsMultiInstance,
    (EFI_DEVICE_PATH_UTILS_CREATE_NODE)DPCreateNode
};

////===================== Security Architectural Protocol =================
EFI_STATUS FileAuthenticationState(
	IN EFI_SECURITY_ARCH_PROTOCOL *This,
	IN UINT32 AuthenticationStatus,
	IN EFI_DEVICE_PATH_PROTOCOL *File
)
{
    if (File==NULL) return EFI_INVALID_PARAMETER;
    return EFI_SUCCESS;
}

EFI_SECURITY_ARCH_PROTOCOL Security = {FileAuthenticationState};

///////////////////////////////////////////////////////////////
extern EFI_GUID gEfiTianoDecompressProtocolGuid;
extern VOID  *mHobStart;
extern EFI_HANDLE gDxeCoreImageHandle;

extern EFI_PEI_FLUSH_INSTRUCTION_CACHE_PROTOCOL  mFlushInstructionCache;
extern EFI_PEI_PE_COFF_LOADER_PROTOCOL mPeCoffLoader;
extern EFI_PEI_TRANSFER_CONTROL_PROTOCOL mTransferControl;
extern BOOLEAN const InstallDummySecurityProtocol;

VOID *CoreAllocateRuntimeCopyPool (
    IN  UINTN   AllocationSize, CONST IN  VOID    *Buffer
);

typedef struct{
	EFI_GUID *pGuid;
	VOID* pInterface;
} DXE_MAIN_INTERFACES;

DXE_MAIN_INTERFACES DxeMainInterfaces[] = 
{
	{&gEfiPeiFlushInstructionCacheGuid,&mFlushInstructionCache},
	{&gEfiPeiPeCoffLoaderGuid,&mPeCoffLoader},
	{&gEfiPeiTransferControlGuid,&mTransferControl},
	{NULL,NULL}
};

EFI_STATUS CreateHob ( IN UINT16 Type, IN UINT16 Length, IN OUT VOID **Hob ){
	EFI_HOB_HANDOFF_INFO_TABLE           *HandOffHob;
	EFI_HOB_GENERIC_HEADER               *HobEnd;
	EFI_PHYSICAL_ADDRESS                 FreeMemory;
	
	if (mHobStart == NULL) return EFI_NOT_AVAILABLE_YET;
	if (Hob == NULL) return EFI_INVALID_PARAMETER;

	// first entry in the HOB list is the HOB handoff table
	HandOffHob = mHobStart;
	// make sure Hob length is a multiple of 8 bytes.
	Length = (UINT16)((Length + 0x7) & (~0x7));
	// calculate the amount of free memory
	FreeMemory =   HandOffHob->EfiFreeMemoryTop
	             - HandOffHob->EfiFreeMemoryBottom;
	if (FreeMemory < Length) return EFI_OUT_OF_RESOURCES;
	
	// add a HOB to the end of the HOB list
	*Hob = (VOID*)(UINTN) HandOffHob->EfiEndOfHobList;
	((EFI_HOB_GENERIC_HEADER*) *Hob)->HobType = Type;
	((EFI_HOB_GENERIC_HEADER*) *Hob)->HobLength = Length;
	((EFI_HOB_GENERIC_HEADER*) *Hob)->Reserved = 0;
	
	// move a new end of the HOB list past the newly created HOB
	HobEnd = (EFI_HOB_GENERIC_HEADER*) ((UINTN) *Hob + Length);
	HandOffHob->EfiEndOfHobList = (EFI_PHYSICAL_ADDRESS) (UINTN) HobEnd;
	
	// initialize the new end HOB and update the pointer to the bottom of free memory
	HobEnd->HobType   = EFI_HOB_TYPE_END_OF_HOB_LIST;
	HobEnd->HobLength = sizeof(EFI_HOB_GENERIC_HEADER);
	HobEnd->Reserved = 0;
	HobEnd++;
	HandOffHob->EfiFreeMemoryBottom = (EFI_PHYSICAL_ADDRESS) (UINTN) HobEnd;
	
	return EFI_SUCCESS;   
}

VOID AmiDxeInit0()
{
	DXE_MAIN_INTERFACES *p;
	EFI_HOB_CPU *CpuHob;

	//Create CPU HOB
    // NOTE: It is responsibility of CPU and/or NB PEIM to make sure
    // CPU HOB exists and contains valid data.
    // The HOB created here is just to prevent system from hanging
    // in case CPU HOB has not been created.
    // If CPU HOB already exists, the HOB crated here will be ignored 
    // by DXE Core because it uses only the first instance of the HOB.
    CreateHob(EFI_HOB_TYPE_CPU, sizeof(EFI_HOB_CPU), &CpuHob);
	CpuHob->SizeOfMemorySpace=32;
	CpuHob->SizeOfIoSpace=16;
	CpuHob->Reserved[0]=0; 
	CpuHob->Reserved[1]=0;
	CpuHob->Reserved[2]=0;
	CpuHob->Reserved[3]=0;
	CpuHob->Reserved[4]=0;
	CpuHob->Reserved[5]=0;

	// =========== Initialize DxeMain Pointers
	for(p=DxeMainInterfaces; p->pGuid; p++)
	{
		PEIM_HOB *PeimHob;
		CreateHob(EFI_HOB_TYPE_GUID_EXTENSION, sizeof(PEIM_HOB),&PeimHob);
		PeimHob->Header.Name = *p->pGuid;
		PeimHob->DxeEntryPoint= p->pInterface;
	}
}

VOID AmiDxeInit1()
{
	InitAmiLib(gDxeCoreImageHandle,gST);

	// =========== Initialize System Table Fields
    gST->FirmwareVendor = CoreAllocateRuntimeCopyPool(
        sizeof( CONVERT_TO_WSTRING(CORE_VENDOR)), CONVERT_TO_WSTRING(CORE_VENDOR)
    );
	gST->FirmwareRevision = CORE_COMBINED_VERSION;
}

VOID AmiDxeInit2()
{
	VOID *p=mHobStart;
	EFI_HANDLE Handle = NULL;

//  TheImageHandle is a library variable, which is initialized in the InitAmiLib library function
//	However, in our case InitAmiLib has been called too early (from AmiDxeInit1), before 
//  gDxeCoreImageHandle has beeen initialized. It is initialized now.
//  Let's update TheImageHandle variable.
    TheImageHandle = gDxeCoreImageHandle;
	// =========== Initialize modules inherited from PEI ======================= //	
#ifndef EFIx64 //no code sharing between PEI and DXE in x64 mode
	for(p = mHobStart; !EFI_ERROR(FindNextHobByType(EFI_HOB_TYPE_GUID_EXTENSION,&p)); )
	{
		PEIM_HOB *pHob = (PEIM_HOB*)p;
		static EFI_GUID guidAmiPeimHob = AMI_PEIM_HOB_GUID;
		if (guidcmp(&pHob->Header.Name,&guidAmiPeimHob)) continue;
		pHob->DxeEntryPoint(gDxeCoreImageHandle,gST);
	}
#endif
	// ========================================================================== //
	gST->BootServices->InstallMultipleProtocolInterfaces(
		&Handle,
		&guidDecompress, &DecompressInterface,
		&gEfiTianoDecompressProtocolGuid, &DecompressInterface,
		&guidPrint, &Print,
        &gEfiDevicePathUtilitiesProtocolGuid, &DevicePathUtilitiesInstance,
        &gEfiDevicePathFromTextProtocolGuid, &EfiDevicePathFromTextProtocol,
        &gEfiDevicePathToTextProtocolGuid, &EfiDevicePathToTextProtocol,
		NULL
	);
    if (InstallDummySecurityProtocol)
    	gST->BootServices->InstallMultipleProtocolInterfaces(
    		&Handle, &gEfiSecurityArchProtocolGuid, &Security, NULL
    	);
	InitParts(gDxeCoreImageHandle,gST);
}

EFI_STATUS AmiResetNotAvailableYet(
	IN EFI_RESET_TYPE ResetType, IN EFI_STATUS ResetStatus,
	IN UINTN DataSize, IN CHAR16 *ResetData OPTIONAL
)
{
    ERROR_CODE(DXE_RESET_NOT_AVAILABLE,EFI_ERROR_MINOR);
    return EFI_NOT_AVAILABLE_YET;;
}

VOID AmiReportArhcProtocolMissingError(){
    ERROR_CODE(DXE_ARCH_PROTOCOL_NOT_AVAILABLE,EFI_ERROR_MAJOR);
}

//GUID definitions

/// Library routines
#ifdef EFI_DEBUG
#define EFI_D_ERROR       0x80000000          // Error
#define EFI_DBUG_MASK   (EFI_D_ERROR)
#define EFI_D_LOAD        0x00000004          // Load events
UINTN gErrorLevel=EFI_DBUG_MASK | EFI_D_LOAD;

VOID
EfiDebugAssert (
  IN CHAR8    *FileName,
  IN INTN     LineNumber,
  IN CHAR8    *Description
  )
 {
	Trace(TRACE_ALWAYS,"ASSERT in %s on %i: %s\n",FileName, LineNumber, Description);
	EFI_DEADLOOP()
 }

VOID
EfiDebugVPrint (
  IN  UINTN   ErrorLevel,
  IN  CHAR8   *Format,
  IN  va_list ArgList
  )
  {
    if (!gST) return;
#if EFI_SPECIFICATION_VERSION<0x20000
	if (!(gST->RuntimeServices && gST->RuntimeServices->ReportStatusCode)) return;
#endif
	if (!(gErrorLevel & ErrorLevel)) return;
    PrintDebugMessageVaList(ErrorLevel, Format, ArgList);
  }

CHAR8* GetDriverName(EFI_DRIVER_BINDING_PROTOCOL *pDriver)
{
	static char sName[0x100];
	if (   !GetImageName(pDriver->DriverBindingHandle,sName)
		&& !GetImageName(pDriver->ImageHandle,sName)
	) Sprintf_s(sName,sizeof(sName),"Unknown");
	return sName;
}
#endif
//**********************************************************************
//**********************************************************************
//**                                                                  **
//**        (C)Copyright 1985-2011, American Megatrends, Inc.         **
//**                                                                  **
//**                       All Rights Reserved.                       **
//**                                                                  **
//**      5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093        **
//**                                                                  **
//**                       Phone: (770)-246-8600                      **
//**                                                                  **
//**********************************************************************
//**********************************************************************