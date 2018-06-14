//**********************************************************************
//**********************************************************************
//**                                                                  **
//**        (C)Copyright 1985-2010, American Megatrends, Inc.         **
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
// $Header: /Alaska/SOURCE/Core/EDK/PeiMain/AmiPeiInit.c 24    5/13/11 5:10p Artems $
//
// $Revision: 24 $
//
// $Date: 5/13/11 5:10p $
//**********************************************************************
// Revision History
// ----------------
// $Log: /Alaska/SOURCE/Core/EDK/PeiMain/AmiPeiInit.c $
// 
// 24    5/13/11 5:10p Artems
// Added functions CopyMem and ZeroMem for PEI build
// 
// 23    3/22/11 5:20p Felixp
// LOAD_HOB processing and AmiInitParts-related code has been restructured
// to achieve the following goals:
//  - Support LOAD_HOB in PI mode
//  - Reduce amount of PI version specific code
//  - Minimize number of patches in the EDK portion of code
//  - Eliminate global variables
//  - Simplify the implementation
// 
// 22    3/09/11 5:53p Artems
// Removed usage of global pointer InitFunction. Fixed bug in
// MigrateIdtTable with wrong IdtBase
// 
// 21    3/08/11 10:22a Artems
// Fixed bug in MigrateIdtTable, where IdtBase assigned wrong address
// 
// 20    3/04/11 4:06p Artems
// Modified FindPPI function to work with both FV hob types
// 
// 19    2/05/11 3:42p Artems
// Added PI 1.0 support
// 
// 18    9/22/10 7:13p Felixp
// Imrpovement: gEfiStatusCodeSpecificDataGuid variable is added. Used by
// PEI Core to report status codes.
// 
// 17    8/20/10 3:26p Felixp
// LZMA compression support: ReadSection function updated.
// 
// 16    8/28/09 3:08p Felixp
// More generic FindFv PPI implementation. Old implementation was assuming
// that boot FV is described by the first FV HOB.
// 
// 15    8/27/09 1:58p Felixp
// AmiInitParts is updated to call InitFunction once when AmiInitParts is
// called multiple times.
// 
// 14    7/30/09 4:46p Vyacheslava
// Fixed comments.
// 
// 13    7/28/09 4:56p Vyacheslava
// Minor bug fix. EIP#24453: Synopsis: CPU exception when printing long
// debug messages.
// 
// 12    5/04/09 3:09p Felixp
// Creation of CPU HOB moved from AmiPeiInit.c to AmiDxeInit.c
// 
// 11    8/07/07 2:24p Felixp
// Additional Status Codes added
// 
// 10    3/12/07 10:26a Felixp
// LoadedImage PPI support added (defined in PI 1.0; used by AmiDebugger)
// 
// 8     10/18/06 11:30a Felixp
// LoadFile updated to return EFI_LOAD_ERROR when image format is invalid
// 
// 7     8/24/06 9:43a Felixp
// Preliminary x64 support (work in progress)
// DXE Core interfaces are no longer passed from PEI Core.
// They are linked directly with DXE Core
// 
// 6     6/04/06 9:20p Ambikas
// 
// 5     5/30/06 7:06p Yakovlevs
// Fixed STACK HOB memory type from ConventionalMemory to EfiLoaderData.
// 
// 4     5/20/06 12:58a Felixp
// 
// 3     5/20/06 12:36a Felixp
// checkpoints added
// 
// 2     5/19/06 10:38p Felixp
// Clean up
// 
// 1     3/13/06 1:57a Felixp
// 
//**********************************************************************
//<AMI_FHDR_START>
//
// Name:	AmiPeiInit.c
//
// Description:	
//
//<AMI_FHDR_END>
//**********************************************************************
#include <AmiHobs.h>
#include <AmiPeiLib.h>
#include <PPI/LoadFile.h>
#include <PPI/LoadedImagePpi.h>
#include <PPI/Decompress.h>
#include <StatusCodes.h>

typedef VOID (*INIT_PARTS)(VOID* p1, VOID*p2);
VOID InitParts(VOID* p1, VOID*p2);
VOID InitParts2(VOID* p1, VOID*p2);

EFI_GUID gEfiStatusCodeSpecificDataGuid = EFI_STATUS_CODE_SPECIFIC_DATA_GUID;

//defined in PeiMain.c
VOID UpdatedLoadedImagePpi(
  IN EFI_PEI_SERVICES         **PeiServices,
  EFI_PHYSICAL_ADDRESS        ImageAddress,
  UINT64                      ImageSize,
  EFI_PEI_FILE_HANDLE         FileHandle
);
////////////// from PeiCore.c
#if PI_SPECIFICATION_VERSION<0x00010000
EFI_PEI_SERVICES **ppPS = NULL;
#endif

VOID InitPartsMem(VOID* p1, VOID*p2)
{
#if PI_SPECIFICATION_VERSION<0x00010000
	ppPS = (EFI_PEI_SERVICES**)p2;
#endif
	InitParts2(p1,p2);
}

#if PI_SPECIFICATION_VERSION<0x00010000
EFI_STATUS FvLoadFile(
	IN EFI_PEI_FV_FILE_LOADER_PPI *This,
	IN EFI_FFS_FILE_HEADER *FfsHeader,
	OUT EFI_PHYSICAL_ADDRESS *ImageAddress,
	OUT UINT64 *ImageSize,
	OUT EFI_PHYSICAL_ADDRESS *EntryPoint
);

// PPIs
EFI_PEI_FV_FILE_LOADER_PPI FileLoader = {FvLoadFile};

// PPI to be installed
EFI_GUID gPeiLoadFilePpiGuid = EFI_PEI_FV_FILE_LOADER_GUID;
static EFI_PEI_PPI_DESCRIPTOR FileLoaderPpi[] =
{ 
	{
		EFI_PEI_PPI_DESCRIPTOR_PPI | EFI_PEI_PPI_DESCRIPTOR_TERMINATE_LIST,
		&gPeiLoadFilePpiGuid, &FileLoader 
	}
};

EFI_STATUS ReadSection(
	EFI_PEI_SERVICES **ppPS, IN EFI_SECTION_TYPE SectionType,
	IN EFI_FFS_FILE_HEADER *pFile, OUT VOID **ppData
)
{
	EFI_STATUS Status;
	UINT32 SrcSize, DstSize, TmpSize;
	VOID *pSrc;
	EFI_PHYSICAL_ADDRESS DstAddress;
	EFI_HOB_HANDOFF_INFO_TABLE *pHob;
    EFI_COMPRESSION_SECTION_HEADER *pCompressionSection;
	if (!ppData) return EFI_INVALID_PARAMETER;
	//TODO: Support for GUIDed sections
	Status = (*ppPS)->FfsFindSectionData(
						ppPS, SectionType, pFile, &pSrc
					  );
	if (!EFI_ERROR(Status)){*ppData=pSrc; return Status; }
	Status = (*ppPS)->FfsFindSectionData(
						ppPS, EFI_SECTION_COMPRESSION,
						pFile, &pCompressionSection
					  );
	if (EFI_ERROR(Status)) return Status;
	SrcSize = FVSECTION_SIZE(pCompressionSection) - sizeof(EFI_COMPRESSION_SECTION_HEADER);
    pSrc = pCompressionSection + 1;
    if (pCompressionSection->CompressionType!=EFI_NOT_COMPRESSED){
        GET_INFO GetInfoPtr;
        DECOMPRESS DecompressPtr;
        BOOLEAN KnownCompressionType = GetDecompressInterface(
            pCompressionSection->CompressionType,
            &GetInfoPtr, &DecompressPtr
        );
        if (!KnownCompressionType) return EFI_UNSUPPORTED;
	    Status = GetInfoPtr(pSrc, SrcSize, &DstSize, &TmpSize);
	    if (EFI_ERROR(Status)) return Status;
	    //No FreePool, so the memory is never freed
	    Status = (*ppPS)->AllocatePages(
            ppPS,EfiBootServicesCode,(DstSize>>12)+1,&DstAddress
        );
	    if (EFI_ERROR(Status)) return Status;
	    (*ppPS)->GetHobList(ppPS,&pHob);
	    if (pHob->EfiFreeMemoryTop - pHob->EfiFreeMemoryBottom <  TmpSize)
		    return EFI_OUT_OF_RESOURCES;
    	Status = DecompressPtr(
            pSrc, SrcSize, (VOID*)DstAddress, DstSize,
			(VOID*)pHob->EfiFreeMemoryBottom, TmpSize
		);
	    if (EFI_ERROR(Status)) return Status;
        pSrc = (VOID*)(UINTN)DstAddress;
    }
    do {
	    if (((EFI_COMMON_SECTION_HEADER*)pSrc)->Type==SectionType){
	        *ppData = (EFI_COMMON_SECTION_HEADER*)pSrc+1;
	        return EFI_SUCCESS;
        }
        TmpSize = FVSECTION_SIZE(pSrc);
        TmpSize += (4 - (TmpSize & 3)) & 3;
        if (TmpSize>=DstSize) return EFI_NOT_FOUND;
        DstSize -= TmpSize;
        pSrc =  (UINT8*)pSrc + TmpSize;
    }while(TRUE);
}

EFI_STATUS LoadFile(
	EFI_PEI_SERVICES **ppPS, 
	IN EFI_FFS_FILE_HEADER *pFfsHeader,
	OUT VOID **ppFfsImageAddress,
	OUT EFI_PHYSICAL_ADDRESS *pImageAddress,
	OUT UINT64 *pImageSize,
	OUT EFI_PHYSICAL_ADDRESS *pEntryPoint
)
{
	VOID *pData;
	EFI_STATUS Status;
	UINTN Size;
	if (!pEntryPoint || !pImageAddress) return EFI_INVALID_PARAMETER;
	Status = ReadSection(ppPS, EFI_SECTION_PE32, pFfsHeader, &pData);
	//TODO: add TE support ???
	if (EFI_ERROR(Status)) return Status;
	Size = GetImageSize(pData); 
	if (EFI_ERROR((*ppPS)->AllocatePages(
		ppPS, EfiBootServicesCode, 
		(Size >> 12)+1, pImageAddress)
		)
	) return EFI_OUT_OF_RESOURCES;

	*pEntryPoint = (EFI_PHYSICAL_ADDRESS)LoadPeImage(pData,(UINT8*)*pImageAddress);
    if (!*pEntryPoint) return EFI_LOAD_ERROR;
	if (pImageSize) *pImageSize = Size;
	if (ppFfsImageAddress) *ppFfsImageAddress = pData;
	return EFI_SUCCESS;
}

EFI_STATUS FvLoadFile(
	IN EFI_PEI_FV_FILE_LOADER_PPI *This,
	IN EFI_FFS_FILE_HEADER *FfsHeader,
	OUT EFI_PHYSICAL_ADDRESS *ImageAddress,
	OUT UINT64 *ImageSize,
	OUT EFI_PHYSICAL_ADDRESS *EntryPoint
)
{
	return LoadFile(ppPS,FfsHeader,NULL,ImageAddress,ImageSize,EntryPoint);
}

typedef VOID (*PEICORE_INMEM_ENTRY_POINT)(
	EFI_PHYSICAL_ADDRESS Delta,
	IN EFI_PEI_SERVICES **PeiServices,
	IN VOID  *PeiCoreEntryPoint, 
	IN UINTN Parameter1, IN UINTN Parameter2,
	IN VOID  *NewStack
);

VOID SwitchCoreStacks(
	IN VOID  *PeiCoreEntryPoint, 
	IN UINTN Parameter1, 
    IN UINTN Parameter2,
	IN VOID  *NewStack
);

VOID PeiCoreMemEntry(
	EFI_PHYSICAL_ADDRESS Delta,
	IN EFI_PEI_SERVICES **PeiServices,
	IN VOID  *PeiCoreEntryPoint, 
	IN UINTN Parameter1, IN UINTN Parameter2,
	IN VOID  *NewStack
)
{
	ppPS = PeiServices;
	if (Delta)
	{
		PEI_TRACE((TRACE_PEICORE,PeiServices,"PEI core reallocated to memory\n"));
		// intall file loader
		(*ppPS)->InstallPpi(ppPS, FileLoaderPpi);
	}
	SwitchCoreStacks(
		(UINT8*)PeiCoreEntryPoint+(UINTN)Delta,Parameter1,Parameter2,NewStack
	);
}

VOID AmiSwitchToMemory(
	IN EFI_PEI_SERVICES **PeiServices,
	IN VOID  *PeiCoreEntryPoint, 
	IN UINTN Parameter1, IN UINTN Parameter2,
	IN VOID  *NewStack
)
{
	//reallocate ourself to memory
	EFI_FIRMWARE_VOLUME_HEADER* pFV;
	EFI_PHYSICAL_ADDRESS NewAddress, EntryPoint;
	VOID *pOldAddress;
	UINT64 Size;
	EFI_FFS_FILE_HEADER* pFile=NULL;
	PEI_PROGRESS_CODE(PeiServices,PEI_MEMORY_INSTALLED);
	// if we already in memory just call memory routine
	//TODO: if (pData->pLoader) PeiCoreInMem(pData, 0);
	//find our FFS file header
	//PEI Core must be in boot FV.
	//Boot FV must be the first one returned by FfsFindNextVolume
	(*PeiServices)->FfsFindNextVolume (PeiServices, 0, &pFV);
	//No error checking. Since if we are here, the file is in the FV, so we should be able to find it.
	(*PeiServices)->FfsFindNextFile (PeiServices, EFI_FV_FILETYPE_PEI_CORE, pFV, &pFile);
	if (EFI_ERROR(LoadFile(PeiServices,pFile,&pOldAddress,&NewAddress,&Size,&EntryPoint))){
		//if we don't have enough memory, don't install FileLoader PPI
		PeiCoreMemEntry(0,PeiServices,PeiCoreEntryPoint,Parameter1,Parameter2,NewStack);
	}else{
        //Update LoadedImage PPI information
        UpdatedLoadedImagePpi(PeiServices,NewAddress,Size,pFile);
		((PEICORE_INMEM_ENTRY_POINT)(
		 	(UINT8*)PeiCoreMemEntry-(UINT8*)pOldAddress+(UINT8*)NewAddress
		))(NewAddress-(UINT64)(UINTN)pOldAddress,PeiServices,PeiCoreEntryPoint,Parameter1,Parameter2,NewStack);
    }
}

typedef struct {
	UINTN BootFirmwareVolume;
	UINTN SizeOfCacheAsRam;
	EFI_PEI_PPI_DESCRIPTOR *DispatchTable;
} EFI_PEI_STARTUP_DESCRIPTOR;

EFI_STATUS EFIAPI PeiMain(
  IN EFI_PEI_STARTUP_DESCRIPTOR  *PeiStartupDescriptor
);

VOID PeiCoreEntry(
	EFI_PEI_STARTUP_DESCRIPTOR StartUpDescriptor
)
{
	checkpoint(0x10);
	PeiMain(&StartUpDescriptor);
}

#include <PPI/FindFv.h>

EFI_STATUS FindFv(
	IN EFI_FIND_FV_PPI *This,
	IN EFI_PEI_SERVICES **PeiServices,
	UINT8 *FvNumber, 
    EFI_FIRMWARE_VOLUME_HEADER **FVAddress
)
{
	UINT8 Instance;
    EFI_FIRMWARE_VOLUME_HEADER *BootFv;
    EFI_HOB_GENERIC_HEADER *HobPointer;
    EFI_STATUS Status;

	if (!FVAddress || !FvNumber) 
        return EFI_INVALID_PARAMETER;

    Status = (*PeiServices)->FfsFindNextVolume(PeiServices, 0, &BootFv);
    if(EFI_ERROR(Status))
        return Status;

    if (*FvNumber == 0) {       //0 is always Boot FV
        *FVAddress = BootFv;
        (*FvNumber)++;
        return Status;
    }

	Instance = *FvNumber;
    Status = (*PeiServices)->GetHobList(PeiServices, &HobPointer);
    if(EFI_ERROR(Status))
        return Status;

    while(HobPointer->HobType != EFI_HOB_TYPE_END_OF_HOB_LIST) {
        if(HobPointer->HobType == EFI_HOB_TYPE_FV || HobPointer->HobType == EFI_HOB_TYPE_FV2) {
            EFI_FIRMWARE_VOLUME_HEADER *Fv;
            Fv = (EFI_FIRMWARE_VOLUME_HEADER *)((EFI_HOB_FIRMWARE_VOLUME *)HobPointer)->BaseAddress;
            if (Fv == BootFv) {
                HobPointer = NextHob(HobPointer, EFI_HOB_GENERIC_HEADER);
                continue;
            }

		    if (Instance == 1) {
			    *FVAddress = Fv;
			    (*FvNumber)++;
    		    return EFI_SUCCESS;
		    }
            Instance--;
        }
		HobPointer = NextHob(HobPointer, EFI_HOB_GENERIC_HEADER);
	}
	return EFI_OUT_OF_RESOURCES; //EFI_NOT_FOUND;
}

EFI_GUID gPeiFindFvPpiGuid = EFI_FIND_FV_PPI_GUID;

// PPIs
EFI_FIND_FV_PPI FindFvPpi = {FindFv};

// PPI to be installed
EFI_PEI_PPI_DESCRIPTOR FindFvPpiDescriptor[] =
{ 
	{
		EFI_PEI_PPI_DESCRIPTOR_PPI | EFI_PEI_PPI_DESCRIPTOR_TERMINATE_LIST,
		&gPeiFindFvPpiGuid, &FindFvPpi 
	}
};

EFI_STATUS EFIAPI InstallFindFv(
	IN EFI_FFS_FILE_HEADER *FfsHeader,
	IN EFI_PEI_SERVICES **PeiServices
)
{
	return (*PeiServices)->InstallPpi(PeiServices,FindFvPpiDescriptor);
}
#else //#if PI_SPECIFICATION_VERSION<0x00010000

EFI_STATUS DecompressPpiDecompress(
    IN CONST EFI_PEI_DECOMPRESS_PPI *This,
    IN CONST EFI_COMPRESSION_SECTION *InputSection,
    OUT VOID **OutputBuffer,
    OUT UINTN *OutputSize
){
	EFI_STATUS Status;
	UINT32 SrcSize, DstSize, TmpSize;
	VOID *pSrc;
	EFI_PHYSICAL_ADDRESS DstAddress;
	EFI_HOB_HANDOFF_INFO_TABLE *pHob;
    EFI_COMPRESSION_SECTION_HEADER *pCompressionSection;

	if (!OutputBuffer || !OutputSize) return EFI_INVALID_PARAMETER;

    pCompressionSection = (EFI_COMPRESSION_SECTION_HEADER*)&InputSection->UncompressedLength;
	SrcSize = FVSECTION_SIZE(pCompressionSection) - sizeof(EFI_COMPRESSION_SECTION_HEADER);
    pSrc = pCompressionSection + 1;
    if (pCompressionSection->CompressionType!=EFI_NOT_COMPRESSED){
        GET_INFO GetInfoPtr;
        DECOMPRESS DecompressPtr;
        EFI_PEI_SERVICES **ppPS = GetPeiServicesTablePointer();
        BOOLEAN KnownCompressionType = GetDecompressInterface(
            pCompressionSection->CompressionType,
            &GetInfoPtr, &DecompressPtr
        );
        if (!KnownCompressionType) return EFI_UNSUPPORTED;
	    Status = GetInfoPtr(pSrc, SrcSize, &DstSize, &TmpSize);
	    if (EFI_ERROR(Status)) return Status;
	    //No FreePool, so the memory is never freed
	    Status = (*ppPS)->AllocatePages(
            ppPS,EfiBootServicesCode,(DstSize>>12)+1,&DstAddress
        );
	    if (EFI_ERROR(Status)) return Status;
	    (*ppPS)->GetHobList(ppPS,&pHob);
	    if (pHob->EfiFreeMemoryTop - pHob->EfiFreeMemoryBottom <  TmpSize)
		    return EFI_OUT_OF_RESOURCES;
    	Status = DecompressPtr(
            pSrc, SrcSize, (VOID*)DstAddress, DstSize,
			(VOID*)pHob->EfiFreeMemoryBottom, TmpSize
		);
	    if (EFI_ERROR(Status)) return Status;
        *OutputBuffer = (VOID*)(UINTN)DstAddress;
        *OutputSize = DstSize;
    }else{
        *OutputBuffer = pSrc;
        *OutputSize = SrcSize;
    }
    return EFI_SUCCESS;
}

// PPI to be installed
EFI_PEI_DECOMPRESS_PPI DecomppressInterface = {DecompressPpiDecompress};
static EFI_PEI_PPI_DESCRIPTOR DecompressPpi[] =
{ 
	{
		EFI_PEI_PPI_DESCRIPTOR_PPI | EFI_PEI_PPI_DESCRIPTOR_TERMINATE_LIST,
		&gEfiPeiDecompressPpiGuid, &DecomppressInterface 
	}
};


EFI_STATUS EFIAPI InstallDecompressionPpi(
	IN EFI_FFS_FILE_HEADER *FfsHeader,
	IN EFI_PEI_SERVICES **PeiServices
)
{
	return (*PeiServices)->InstallPpi(PeiServices, DecompressPpi);
}

EFI_STATUS PeiMain(IN CONST EFI_SEC_PEI_HAND_OFF *SecCoreData, IN CONST EFI_PEI_PPI_DESCRIPTOR *PpList);

VOID PeiCoreEntry(
  IN CONST EFI_SEC_PEI_HAND_OFF   *SecCoreData,
  IN CONST EFI_PEI_PPI_DESCRIPTOR *PpList)
{
	checkpoint(0x10);
	PeiMain(SecCoreData,PpList);
}
#endif //#else branch of #if PI_SPECIFICATION_VERSION<0x00010000

VOID AmiInitParts(IN EFI_PEI_SERVICES **PeiServices, INIT_PARTS InitFunctionPtr)
{
    if (InitFunctionPtr == NULL) 
        return;

    (InitFunctionPtr)(NULL, PeiServices);
}

VOID ProcessLoadHob(IN EFI_PEI_SERVICES **PeiServices)
{
	static EFI_GUID LoadHobGuid = AMI_PEIM_LOAD_HOB_GUID;
	PEIM_LOAD_HOB *LoadHob;
    EFI_STATUS Status;

	Status = (*PeiServices)->GetHobList(PeiServices,&LoadHob);
    if (EFI_ERROR(Status)) return;
	// Load PEIMs
	while(!EFI_ERROR(FindNextHobByGuid(&LoadHobGuid, &LoadHob)))
	{
		EFI_PHYSICAL_ADDRESS Address,EntryPoint, ModuleDelta;
		UINT64 Size;
		// if file header is NULL, the entry is in the PEI Core binary
        if (LoadHob->pFfsHeader == NULL) continue;
        Status = PeiLoadFile(
            PeiServices,LoadHob->pFfsHeader,&Address,&Size,&EntryPoint
        );
        if (EFI_ERROR(Status)) continue;
		ModuleDelta = EntryPoint - (UINT64)LoadHob->EntryPoint;
        if (ModuleDelta==0) continue; // the module was not loaded
#ifdef EFI_DEBUG
{
    char sName[0x100];
    EFI_FFS_FILE_HEADER *PeimFileHeader = LoadHob->pFfsHeader;

    if (!GetName((VOID*)(UINTN)Address,sName))
        Sprintf_s(sName,sizeof(sName),"[%G]",&PeimFileHeader->Name);
    PeiTrace(
        TRACE_PEICORE, PeiServices, "%s.InMemEntry(%X)\n", sName, 
        (UINT64)LoadHob->InMemEntryPoint+ModuleDelta
    );
}
#endif
		((EFI_PEIM_ENTRY_POINT)(
			(UINT64)LoadHob->InMemEntryPoint+ModuleDelta
		))(LoadHob->pFfsHeader, PeiServices);		
	}
}

EFI_STATUS
PeiBuildHobStack (
  IN EFI_PEI_SERVICES            **PeiServices,
  IN EFI_PHYSICAL_ADDRESS        BaseAddress,
  IN UINT64                      Length
  )
/*++

Routine Description:

  Builds a HOB for the Stack

Arguments:

  PeiServices               - The PEI core services table.

  BaseAddress               - The 64 bit physical address of the Stack

  Length                    - The length of the stack in bytes

Returns:

  EFI_SUCCESS               - Hob is successfully built.
  Others                    - Errors occur while creating new Hob

--*/
{
  EFI_STATUS                       Status;  
  EFI_HOB_MEMORY_ALLOCATION_STACK  *Hob;
  static EFI_GUID gEfiHobMemeryAllocStackGuid=EFI_HOB_MEMORY_ALLOC_STACK_GUID;

  Status = (*PeiServices)->CreateHob (
                             PeiServices,
                             EFI_HOB_TYPE_MEMORY_ALLOCATION,
                             sizeof (EFI_HOB_MEMORY_ALLOCATION_STACK),
                             &Hob
                             );
  if (EFI_ERROR (Status)) {
    return Status;
  }
 
  Hob->AllocDescriptor.Name = gEfiHobMemeryAllocStackGuid;
  Hob->AllocDescriptor.MemoryBaseAddress = BaseAddress;
  Hob->AllocDescriptor.MemoryLength = Length;
  Hob->AllocDescriptor.MemoryType = EfiLoaderData;
  return EFI_SUCCESS;
}

EFI_STATUS
PeiBuildHobMemoryAllocation (
  IN EFI_PEI_SERVICES            **PeiServices,
  IN EFI_PHYSICAL_ADDRESS        BaseAddress,
  IN UINT64                      Length,
  IN EFI_GUID                    *Name,
  IN EFI_MEMORY_TYPE             MemoryType
  )
/*++

Routine Description:

  Builds a HOB for the memory allocation.

Arguments:

  PeiServices               - The PEI core services table.

  BaseAddress               - The 64 bit physical address of the memory

  Length                    - The length of the memory allocation in bytes

  Name                      - Name for Hob

  MemoryType                - Memory type

Returns:

  EFI_SUCCESS               - Hob is successfully built.
  Others                    - Errors occur while creating new Hob

--*/
{
  EFI_STATUS                 Status; 
  EFI_HOB_MEMORY_ALLOCATION  *Hob;

  Status = (*PeiServices)->CreateHob (
                             PeiServices,
                             EFI_HOB_TYPE_MEMORY_ALLOCATION,
                             sizeof (EFI_HOB_MEMORY_ALLOCATION),
                             &Hob
                             );
  if (EFI_ERROR (Status)) {
    return Status;
  }

  if (Name != NULL) {
    Hob->AllocDescriptor.Name = *Name;
  } else {
    (*PeiServices)->SetMem(&(Hob->AllocDescriptor.Name), sizeof (EFI_GUID), 0);
  }

  Hob->AllocDescriptor.MemoryBaseAddress = BaseAddress;
  Hob->AllocDescriptor.MemoryLength = Length;
  Hob->AllocDescriptor.MemoryType = MemoryType;

  return EFI_SUCCESS;
}

EFI_STATUS
PeiBuildHobGuid (
  IN EFI_PEI_SERVICES            **PeiServices,
  IN EFI_GUID                    *Guid,
  IN UINTN                       DataLength,
  IN OUT VOID                    **Hob
  )
/*++

Routine Description:

  Builds a custom HOB that is tagged with a GUID for identification

Arguments:

  PeiServices - The PEI core services table.

  Guid        - The GUID of the custome HOB type

  DataLength  - The size of the data payload for the GUIDed HOB

  Hob         - Pointer to the Hob

Returns:

  EFI_SUCCESS   - Hob is successfully built.
  Others        - Errors occur while creating new Hob

--*/
{
  EFI_STATUS         Status;

  Status = (*PeiServices)->CreateHob (
                             PeiServices,
                             EFI_HOB_TYPE_GUID_EXTENSION,
                             (UINT16) (sizeof (EFI_HOB_GUID_TYPE) + DataLength),
                             Hob
                             );
  if (EFI_ERROR (Status)) {
    return Status;
  }

  ((EFI_HOB_GUID_TYPE *)(*Hob))->Name = *Guid;
  
  return EFI_SUCCESS;
}

BOOLEAN CompareGuid (IN EFI_GUID *Guid1,IN EFI_GUID *Guid2)
{
	return !MemCmp(Guid1,Guid2,sizeof(EFI_GUID));
}

VOID CopyMem (
  IN VOID   *Destination, IN VOID   *Source, IN UINTN  Length
)
{
  MemCpy (Destination, Source, Length);
}

VOID ZeroMem(IN VOID *Buffer, IN UINTN Size)
{
	MemSet(Buffer,Size,0);
}

#ifdef EFI_DEBUG
 VOID 
 PeiDebugAssert (
    IN EFI_PEI_SERVICES   **PeiServices,
    IN CHAR8              *FileName,
    IN INTN               LineNumber,
    IN CHAR8              *Description
    )
 {
	PeiTrace(TRACE_ALWAYS,PeiServices,"ASSERT in %s on %i: %s\n",FileName, LineNumber, Description);
	EFI_DEADLOOP()
 }

  VOID
  PeiDebugPrint (
    IN CONST EFI_PEI_SERVICES   **PeiServices,
    IN UINTN              ErrorLevel,
    IN CHAR8              *Format,
    ...
    )
  {
	CHAR8  Buffer[256];
	va_list	ArgList = va_start(ArgList,Format);
	PrepareStatusCodeString( Buffer, sizeof(Buffer), Format, ArgList );
	(*PeiServices)->ReportStatusCode (
		(EFI_PEI_SERVICES**)PeiServices, EFI_DEBUG_CODE, 
		EFI_SOFTWARE_UNSPECIFIED, 0, NULL,
		(EFI_STATUS_CODE_DATA *)Buffer
	);
	va_end(ArgList);
  }
#endif
#if PI_SPECIFICATION_VERSION >= 0x00010000
#pragma pack (1)
typedef struct {
	UINT16	Limit;
	UINTN   Base;
} DESCRIPTOR_TABLE;
#pragma pack()

VOID CPULib_LoadIdt(DESCRIPTOR_TABLE *Idt);
VOID CPULib_SaveIdt(DESCRIPTOR_TABLE *Idt);

/*++

Routine Description:

  Invalidates a range of instruction cache lines in the cache coherency domain
  of the calling CPU.

  Invalidates the instruction cache lines specified by Address and Length. If
  Address is not aligned on a cache line boundary, then entire instruction
  cache line containing Address is invalidated. If Address + Length is not
  aligned on a cache line boundary, then the entire instruction cache line
  containing Address + Length -1 is invalidated. This function may choose to
  invalidate the entire instruction cache if that is more efficient than
  invalidating the specified range. If Length is 0, the no instruction cache
  lines are invalidated. Address is returned.

  If Length is greater than (EFI_MAX_ADDRESS - Address + 1), then ASSERT().

Arguments:

  Address   -     The base address of the instruction cache lines to
                  invalidate. If the CPU is in a physical addressing mode, then
                  Address is a physical address. If the CPU is in a virtual
                  addressing mode, then Address is a virtual address.

  Length    -      The number of bytes to invalidate from the instruction cache.

 Returns:
  Address

**/
VOID MigrateIdtTable (IN EFI_PEI_SERVICES  **PeiServices){
  UINTN           Size;
  VOID            *NewIdtBase;
  EFI_STATUS      Status;
  DESCRIPTOR_TABLE IdtDescriptor;

  CPULib_SaveIdt(&IdtDescriptor);

  Size = sizeof(EFI_PEI_SERVICES**) + (IdtDescriptor.Limit + 1);  
  Status = (*PeiServices)->AllocatePool (PeiServices, Size, &NewIdtBase);
  ASSERT_PEI_ERROR (PeiServices, Status);
  (*PeiServices)->CopyMem (
        (VOID*)((UINTN)NewIdtBase + sizeof(EFI_PEI_SERVICES**)),
        (VOID*)IdtDescriptor.Base, (IdtDescriptor.Limit + 1)
  );

  IdtDescriptor.Base = (UINTN)NewIdtBase + sizeof(EFI_PEI_SERVICES**);
  CPULib_LoadIdt(&IdtDescriptor);
  SetPeiServicesTablePointer(PeiServices);
}
/**
Routine Description:

  Scans a target buffer for a GUID, and returns a pointer to the matching GUID
  in the target buffer.

  This function searches target the buffer specified by Buffer and Length from
  the lowest address to the highest address at 128-bit increments for the 128-bit
  GUID value that matches Guid.  If a match is found, then a pointer to the matching
  GUID in the target buffer is returned.  If no match is found, then NULL is returned.
  If Length is 0, then NULL is returned.
  If Length > 0 and Buffer is NULL, then ASSERT().
  If Buffer is not aligned on a 32-bit boundary, then ASSERT().
  If Length is not aligned on a 128-bit boundary, then ASSERT().
  If Length is greater than (EFI_MAX_ADDRESS ?Buffer + 1), then ASSERT(). 

Arguments:

  Buffer - Pointer to the target buffer to scan.
  Length - Number of bytes in Buffer to scan.
  Guid   - Value to search for in the target buffer.
  
Returns:
  A pointer to the matching Guid in the target buffer or NULL otherwise.

**/
VOID *ScanGuid (IN VOID *Buffer, IN UINTN Length, IN EFI_GUID *Guid){
  EFI_GUID                 *GuidPtr;
  EFI_PEI_SERVICES         **PeiServices;
  
  PeiServices = GetPeiServicesTablePointer();
  PEI_ASSERT(PeiServices, (((UINTN)Buffer & (sizeof (Guid->Data1) - 1)) == 0));
  PEI_ASSERT(PeiServices, (Length <= (0xFFFFFFFF - (UINTN)Buffer + 1)));
  PEI_ASSERT(PeiServices, ((Length & (sizeof (*GuidPtr) - 1)) == 0));

  GuidPtr = (EFI_GUID*)Buffer;
  Buffer  = GuidPtr + Length / sizeof (*GuidPtr);
  while (GuidPtr < (EFI_GUID*)Buffer) {
    if (!guidcmp (GuidPtr, Guid)) {
      return (VOID*)GuidPtr;
    }
    GuidPtr++;
  }
  return NULL;
}
#endif
//**********************************************************************
//**********************************************************************
//**                                                                  **
//**        (C)Copyright 1985-2010, American Megatrends, Inc.         **
//**                                                                  **
//**                       All Rights Reserved.                       **
//**                                                                  **
//**      5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093        **
//**                                                                  **
//**                       Phone: (770)-246-8600                      **
//**                                                                  **
//**********************************************************************
//**********************************************************************