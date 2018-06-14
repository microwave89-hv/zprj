//**********************************************************************
//**********************************************************************
//**                                                                  **
//**        (C)Copyright 1985-2009, American Megatrends, Inc.         **
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
// $Header: /Alaska/SOURCE/Core/Runtime/Runtime.c 23    6/16/11 9:07a Felixp $
//
// $Revision: 23 $
//
// $Date: 6/16/11 9:07a $
//**********************************************************************
// Revision History
// ----------------
// $Log: /Alaska/SOURCE/Core/Runtime/Runtime.c $
// 
// 23    6/16/11 9:07a Felixp
// Enhancements(EIP 49676): 
// 1. FindDescriptor: upated to ignore boot time memory map descriptors
// 2. SetVirtualAddressMap: updated to skip virtual address change
// callbacks that reside in the boot time memory.
// 
// 22    9/22/10 6:57p Felixp
// Minor improvements: use InitAmiRuntimeLib instead of InitAmiLib
// 
// 21    3/12/10 12:00p Felixp
// 
// 20    3/12/10 10:26a Felixp
// Bug fix: Potential problems with UEFI OS. 
// pST was used here even after it has been virtualized in the
// AmiLibGoVirtual. 
// The local copy of the pointer is created.
// 
// 19    7/08/09 12:00p Felixp
// 
// 18    6/24/09 4:23p Robert
// updated comments, copyright and some coding standard items
// 
// 17    5/14/09 9:34a Felixp
// New feature: SMM version of Runtime Services
// Runtime driver is updated to install SMM version of the runtime
// services table.
// 
// 15    11/20/08 2:58p Felixp
// Bug fix in SetVirtualAddressMap( bug fix in the runtime images fixup
// logic )
// 
// 14    11/07/07 11:54a Felixp
// Bug fix in FindDescriptor routine
// 
// 13    8/07/07 2:23p Felixp
// New StatusCodes added
// 
// 7     10/27/06 10:31a Felixp
// checkpoints on begin/end of SetVirtualAddressMap added
// 
// 6     10/27/06 10:15a Felixp
// Bug fixes in SetVirtualAddressMap
// 
// 5     10/07/06 10:22a Felixp
// New Runtime protocol defined by DXE CIS 0.91 implemented
// (Old(DXE CIS 0.90) Runtime protocol and AMI Runtime protocols removed).
// 
// 3     1/18/05 3:22p Felixp
// PrintDebugMessage renamed to Trace
// 
// 14    12/23/04 9:29a Felixp
// ArchProtocols moved to Include\Protocols
// 
//**********************************************************************
//<AMI_FHDR_START>
//
// Name:	Runtime.c
//
// Description:	
//  This file contains the Runtime Architectural Protocol along with 
//  some runtime functions that are included in the Runtime Services Table
//  SetVirtualAddressMap, ConvertPointer, and CalculateCrc32.  The entry
//  point for the Runtime Driver also contains a call to InitParts which 
//  uses the RuntimeInitialize and RuntimeSmmInitialize eLinks to 
//  initialize other pieces of the Runtime Structure
//
//<AMI_FHDR_END>
//**********************************************************************

//=============================================================================
// Includes
#include <Protocol/Runtime.h>
#include <Protocol/LoadedImage.h>
#include <AmiDxeLib.h>

//=============================================================================
// Protocol Definition
EFI_RUNTIME_ARCH_PROTOCOL Runtime = 
{
        {&Runtime.ImageHead,&Runtime.ImageHead}, //EFI_LIST_ENTRY ImageHead;
        {&Runtime.EventHead,&Runtime.EventHead}, //EFI_LIST_ENTRY EventHead;
        0, //UINTN MemoryDescriptorSize;
        0, //UINT32 MemoryDesciptorVersion;
        0, //UINTN MemoryMapSize;
        NULL, //EFI_MEMORY_DESCRIPTOR *MemoryMapPhysical;
        NULL, //EFI_MEMORY_DESCRIPTOR *MemoryMapVirtual;
        FALSE, //BOOLEAN VirtualMode;
        FALSE //BOOLEAN AtRuntime;
} ;


//=============================================================================
// Module specific Global Variables

static EFI_MEMORY_DESCRIPTOR *pMap = NULL;
static UINTN MapSize, DescSize;
static UINT32 CrcTable[256];

//=============================================================================
// Function Prototypes

//this funciton is created from InitList.c template file during build process
VOID InitParts(IN EFI_HANDLE ImageHandle, IN EFI_SYSTEM_TABLE *SystemTable);


EFI_STATUS SetVirtualAddressMap(
	IN UINTN MemoryMapSize, IN UINTN DescriptorSize,
	IN UINT32 DescriptorVersion, IN EFI_MEMORY_DESCRIPTOR *VirtualMap
);

EFI_STATUS ConvertPointer(
	IN UINTN DebugDisposition, IN VOID **Address
);

EFI_STATUS CalculateCrc32(
	IN VOID *Data, IN UINTN DataSize, OUT UINT32 *Crc32
);

VOID InitCrc();

//=============================================================================
// Function Definitions

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	RuntimeInitialize
//
// Description:	
//  This function is the Initialization function for the runtime driver that is
//  outside of SMM.  It sets up all the pieces of the Runtime Architectural
//  Protocol that exist outside of SMM
//
// Input:   
//  EFI_HANDLE ImageHandle - The firmware allocated handle for this driver
//  EFI_SYSTEM_TABLE *SystemTable - Pointer to the UEFI SystemTable
//
// Output:		
//  EFI_SUCCESS 
//
// Notes:
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS RuntimeInitialize(
	IN EFI_HANDLE ImageHandle, IN EFI_SYSTEM_TABLE *SystemTable
)
{
	EFI_HANDLE Handle = NULL;

	InitAmiRuntimeLib(ImageHandle, SystemTable, NULL, NULL);
	InitCrc();

	//this funciton is created from InitList.c template file during build process
	InitParts(ImageHandle, SystemTable);

    // Initialize pointers in the Runtime Services Table
	pRS->SetVirtualAddressMap = SetVirtualAddressMap;
	pRS->ConvertPointer = ConvertPointer;
	pBS->CalculateCrc32 = CalculateCrc32;

    // install the Runtime Achitectural Protocol
	pBS->InstallMultipleProtocolInterfaces(
        &Handle, &gEfiRuntimeArchProtocolGuid, &Runtime, NULL
	);
	return EFI_SUCCESS;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	FindDescriptor
//
// Description:	
//  This function finds the memory descriptor that contains the pointer that 
//  is passed into the function.  This is used by the ConvertPointer function 
//  to determine how to find the virtual fixup address of the pointer
//
// Input:   
//	VOID *p - Pointer that needs to be fixed up
//
// Output:		
//  EFI_MEMORY_DESCRIPTOR * - Memory descriptor that contain the pointer that is passed in
//
// Notes:  
//  Used only by ConvertPointer function to help it convert the pointer from
//  a physical address to a virtual address
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_MEMORY_DESCRIPTOR* FindDescriptor(VOID *p)
{
	EFI_MEMORY_DESCRIPTOR *pD;
    EFI_PHYSICAL_ADDRESS Address = (EFI_PHYSICAL_ADDRESS)(UINTN)p;

    if(!pMap) return NULL;
    // Search for the memory descriptor that contains the address of the pointer 
    //  that was passed in
	for(pD = pMap
		;pD < (EFI_MEMORY_DESCRIPTOR*)((UINT8*)pMap + MapSize)
		;pD = (EFI_MEMORY_DESCRIPTOR*)((UINT8*)pD + DescSize)
	)	if (   (pD->Attribute & EFI_MEMORY_RUNTIME)
			&& pD->PhysicalStart <= Address 
			&& pD->PhysicalStart + Shl64(pD->NumberOfPages, EFI_PAGE_SHIFT)
			   > Address
		) return pD;
	return NULL;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	SetVirtualAddressMap
//
// Description:	
//  This function is called by a UEFI OS.  It changes the pointers for the 
//  Runtime Services Table and each of the function pointers and variables 
//  that are its elements from physical addresses to virtual addresses.
//
// Input:   
//	IN UINTN MemoryMapSize - Size of the Current Memory Map
//  IN UINTN DescriptorSize - Size of one descriptor in the Memory Map
//  IN UINT32 DescriptorVersion - Version of the MemoryDescriptor Data Structure
//  IN EFI_MEMORY_DESCRIPTOR *VirtualMap - Address to the first Descriptor in the Virtual Memory Map
//
// Output:		
//  EFI_SUCCESS
//
// Notes:  
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS SetVirtualAddressMap(
    IN UINTN MemoryMapSize, 
    IN UINTN DescriptorSize,
    IN UINT32 DescriptorVersion, 
    IN EFI_MEMORY_DESCRIPTOR *VirtualMap
)
{
    EFI_LIST_ENTRY *pLink;
    VOID **p;
    UINTN i;
    UINT32 crc;
    EFI_RUNTIME_IMAGE_ENTRY *pThisImageEntry;
    VOID *VirtualImageBase;

    //Make a local copy of pRS or pST
    //it case one of the runtime drivers linked with this module
    //converts pRS or pST to virtual address in the event handler
    EFI_SYSTEM_TABLE	 *pSTCopy = pST;
    EFI_RUNTIME_SERVICES *pRSCopy = pRS;

    //SetVirtualAddressMap can only be called once	
    if(pMap) return EFI_UNSUPPORTED;
    checkpoint(0xB0);

    //Initialize Global Variables
    pMap = VirtualMap;
    MapSize = MemoryMapSize;
    DescSize = DescriptorSize;

    //Call Event notification funcitons
    for(pLink = Runtime.EventHead.ForwardLink; pLink != &Runtime.EventHead; pLink = pLink->ForwardLink)
    {
        EFI_RUNTIME_EVENT_ENTRY *pEvent = OUTTER(pLink, Link, EFI_RUNTIME_EVENT_ENTRY);
        if (!pEvent->NotifyFunction) continue;
        //Let's see if the notification function we about to call is a runtime function
        if (!FindDescriptor(pEvent->NotifyFunction)){
            TRACE((TRACE_DXE_CORE,"ERROR: Virtual address change callback at address %X resides in the boot time memory\n",pEvent->NotifyFunction));
            ASSERT(FALSE);
            continue;
        }
        ASSERT(!pEvent->NotifyContext || FindDescriptor(pEvent->NotifyFunction));
        pEvent->NotifyFunction(*pEvent->Event, pEvent->NotifyContext);
    }

    //Fixup runtime images
    for(pLink = Runtime.ImageHead.ForwardLink; pLink != &Runtime.ImageHead; pLink = pLink->ForwardLink)
    {
        EFI_RUNTIME_IMAGE_ENTRY *pImage = OUTTER(pLink, Link, EFI_RUNTIME_IMAGE_ENTRY);
        //skip this image; it will be fixed up later
        if (TheImageHandle == pImage->Handle){
            pThisImageEntry = pImage;
            continue;
        }
        VirtualImageBase = pImage->ImageBase;
        ConvertPointer(0, &VirtualImageBase);
        ReallocatePeImage(pImage->ImageBase, VirtualImageBase, pImage->RelocationData);
    }
    //Fixup RuntimeServices
    for(p = (VOID**)((UINT8*)pRSCopy + sizeof(pRSCopy->Hdr)); p < (VOID**)(pRSCopy + 1); p++)
        ConvertPointer(0, p);
    //Fixup Configuration Table
    for(i = 0; i < pSTCopy->NumberOfTableEntries; i++)
        ConvertPointer(0, &pSTCopy->ConfigurationTable[i].VendorTable);
    //Fixup SystemTable
    ConvertPointer(0, &pSTCopy->ConfigurationTable);
    ConvertPointer(0, &pSTCopy->RuntimeServices);
    ConvertPointer(0, &pSTCopy->FirmwareVendor);
    // Update CRC32 of the System Tables
    pRSCopy->Hdr.CRC32 = 0; crc = 0;
    CalculateCrc32(pRSCopy, sizeof(*pRSCopy), &crc);
    pRSCopy->Hdr.CRC32 = crc;
    pSTCopy->Hdr.CRC32 = 0; crc = 0;
    CalculateCrc32(pSTCopy, sizeof(*pSTCopy), &crc);
    pSTCopy->Hdr.CRC32 = crc;

    //finally, fixup ourself
    VirtualImageBase = pThisImageEntry->ImageBase;
    ConvertPointer(0, &VirtualImageBase);
	ReallocatePeImage(pThisImageEntry->ImageBase, VirtualImageBase, pThisImageEntry->RelocationData);

    checkpoint(0xB1);
	return EFI_SUCCESS;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	ConvertPointer
//
// Description:	
//  This function converts pointers from a Physical Memory Map Pointer 
//  to a Virtual Memory Map Pointer.  Called during the SetVirtualAddressMap
//  function execution.  
//
// Input:   
//	IN UINTN DebugDisposition - If set as EFI_OPTIONAL_POINTER, then Address is allowed to be NULL
//  IN VOID **Address - Pointer to convert to a virtual address
//
// Output:		
//  EFI_SUCCESS - Pointer converted to Virtual Address
//  EFI_INVALID_PARAMETER - DebugDisposition != EFI_OPTIONAL_POINTER and *Address == NULL
//  EFI_INVALID_PARAMETER - Address == NULL
//  EFI_UNSUPPORTED - Virtual Memory Map address has not be set
//  EFI_NOT_FOUND - Descriptor not found that contains the address of *Address
//
// Notes:  
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS ConvertPointer(
	IN UINTN DebugDisposition, 
    IN VOID **Address
)
{
	EFI_MEMORY_DESCRIPTOR *pD;

    // Check for error conditions
	if(!pMap) return EFI_UNSUPPORTED;
	if (!Address) return EFI_INVALID_PARAMETER;
	if (!*Address)
		return (DebugDisposition == EFI_OPTIONAL_PTR) ? EFI_SUCCESS : EFI_INVALID_PARAMETER;

    // find the descriptor that contains the address passed in  If not found, return error
	if (!(pD = FindDescriptor(*Address))) return EFI_NOT_FOUND;

    // if the descriptor is found, fixup the address to the new virtual address
	*Address = (VOID*)((EFI_PHYSICAL_ADDRESS)*Address - pD->PhysicalStart + pD->VirtualStart);
	return EFI_SUCCESS;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	InitCrc
//
// Description:	
//  This function Initializes the CrcTable with lookup values for future 
//  use durning CRC32 calculations
//
// Input:   
//  None
//
// Output:
//  None
//
// Notes:  
//  At the end of this function the CrcTable will be initialized with lookup 
//  values that make calculating CRC32 values much easier
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID InitCrc( VOID )
{
	UINT32 i;
    UINT32 j;

	for(i = 0; i < 256; i++)
	{
		CrcTable[i] = i;
		for(j = 8; j > 0; j--) 
			CrcTable[i] = (CrcTable[i] & 1) 
    			? (CrcTable[i] >> 1)^0xedb88320 
    			: CrcTable[i] >> 1;
	}
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	CalculateCrc32
//
// Description:	
//  This function Calculates a CRC32 value using the Data Buffer that is 
//  and the DataSize passed in 
//
// Input:   
//  IN VOID *Data - Pointer to the data to have the CRC function run on
//  IN UINTN DataSize - Size in bytes of the Data pointed to by *Data
//
// Output:
//  OUT UINT32 *Crc32 - CRC32 value calculated based on Data and Data Size
//
// Notes:  
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS CalculateCrc32(
	IN VOID *Data, IN UINTN DataSize, OUT UINT32 *Crc32
)
{
	UINT32 i, crc = (UINT32)-1;
	if (!Data || !DataSize || !Crc32) return EFI_INVALID_PARAMETER;
	for(i = 0; i < DataSize; i++) crc = (crc >> 8)^CrcTable[(UINT8)crc^((UINT8*)Data)[i]];
	*Crc32 = ~crc;
	return EFI_SUCCESS;
}

//**********************************************************************
// RT SMM BEGIN
//**********************************************************************
//======================================================================
// SMM externs
extern EFI_GUID SmmRsTableGuid;

//======================================================================
// SMM Function Prototypes

//this funciton is created from InitList.c template file during build process
VOID InitParts2(IN EFI_HANDLE ImageHandle, IN EFI_SYSTEM_TABLE *SystemTable);


//======================================================================
// SMM Function Definitions
//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	DummySmmRtFunction
//
// Description:	
//  This function is a Dummy function that is used as a default function
//  for the SMM instance of the Runtime Services Table
//
// Input:   
//  None
//
// Output:
//  EFI_UNSUPPORTED
//
// Notes:  
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS DummySmmRtFunction(){ return EFI_UNSUPPORTED; }

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	RuntimeSmmInitialize
//
// Description:	
//  This function initializes the SMM version of the Runtime Services Table
//
// Input:   
//  EFI_HANDLE ImageHandle - The firmware allocated handle for this driver
//  EFI_SYSTEM_TABLE *SystemTable - Pointer to the UEFI SystemTable
//
// Output:
//  EFI_STATUS - based on the return values of the SmmInstallConfigurationTable function
//
// Notes:  
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS RuntimeSmmInitialize(
    EFI_HANDLE ImageHandle, EFI_SYSTEM_TABLE *SystemTable
)
{
    EFI_RUNTIME_SERVICES 	SmmRs;
    EFI_STATUS Status;
    VOID **p;

    //copy header
    SmmRs.Hdr = pRS->Hdr;
    //Init Runtime Services function pointers with our dummy function
    for(p = (VOID**)((UINT8*)&SmmRs + sizeof(SmmRs.Hdr)); p < (VOID**)(&SmmRs + 1); p++)
        *p = DummySmmRtFunction;

    // install the SMM version of the Runtime Services Table SMM Configuration Table
    Status = pSmst->SmmInstallConfigurationTable(
        pSmst, &SmmRsTableGuid, &SmmRs, sizeof(EFI_RUNTIME_SERVICES) );
    ASSERT_EFI_ERROR(Status);

    return Status;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	RuntimeEntry
//
// Description:	
//  This function is the entry point for the Runtime Driver.  It initializes
//  the AMI Library and then it calls the Initialization functions for both
//  the SMM and NON-SMM versions of the Runtime Driver.  It then calls the 
//  InitParts2 function which calls the functions in the RuntimeSmmInitialize
//  eLink.
//
// Input:   
//  EFI_HANDLE ImageHandle - The firmware allocated handle for this driver
//  EFI_SYSTEM_TABLE *SystemTable - Pointer to the UEFI SystemTable
//
// Output:
//  EFI_STATUS - based on the return values of the InitSmmHandlerEx function
//
// Notes:  
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS RuntimeEntry (
    IN EFI_HANDLE ImageHandle, IN EFI_SYSTEM_TABLE *SystemTable
)
{
    EFI_STATUS Status;

    // Initialize the AMI Library for this module
	InitAmiLib(ImageHandle, SystemTable);
    
    // Initialize both the SMM and Non-SMM verions of the Runtime Services
	Status = InitSmmHandlerEx(
        ImageHandle, SystemTable, RuntimeSmmInitialize, RuntimeInitialize
    );
    InitParts2(ImageHandle, SystemTable);
    return Status;
}
//**********************************************************************
// RT SMM END
//**********************************************************************

//**********************************************************************
//**********************************************************************
//**                                                                  **
//**        (C)Copyright 1985-2009, American Megatrends, Inc.         **
//**                                                                  **
//**                       All Rights Reserved.                       **
//**                                                                  **
//**      5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093        **
//**                                                                  **
//**                       Phone: (770)-246-8600                      **
//**                                                                  **
//**********************************************************************
//**********************************************************************