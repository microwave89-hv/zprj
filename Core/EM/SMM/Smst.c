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
// $Header: /Alaska/Projects/Intel/Haswell/LynxPoint_SharkBay-DT_Crb_1AQQW/Core/EM/SMM/Smst.c 2     11/21/12 4:07a Wesleychen $
//
// $Revision: 2 $
//
// $Date: 11/21/12 4:07a $
//**********************************************************************
// Revision History
// ----------------
// $Log: /Alaska/Projects/Intel/Haswell/LynxPoint_SharkBay-DT_Crb_1AQQW/Core/EM/SMM/Smst.c $
// 
// 2     11/21/12 4:07a Wesleychen
// Support Intel PFAT.
// 
// 25    3/14/11 3:18p Markw
// Rename gSmmFirmwareVender to gSmmFirmwareVendor.
// 
// 24    2/07/11 3:29p Markw
// [TAG]  		EIP53481
// [Category]  	New Feature
// [Description]  	Add PIWG 1.1 SMM support
// [Files]  		Smm.sdl, SmmPrivateShared.h, SmmDispatcher.mak,
// SmmDispatcher.h, SmmDispatcher.c,
// Smst.c, SmmPiSmst.c, SmmInit.c, SmmBase.c, SmmBase2.c,
// SmmDriverDispatcher.c, Smm Framewwork Protocol files, SmmPi.h,
// Smm Pi Protocol files, SmmPciRbio files
// 
// 23    6/18/10 12:29p Markw
// Fix history log.
// 
// 22    4/22/10 6:22p Markw
// Support /w4 compilier option.
// 
// 21    2/25/10 5:16p Markw
// Add support for all APs to execute non-blocking.
// Fixed issue with memory allocation
// 
// 20    2/12/10 3:54p Markw
// Update SmmSmstAllocatePages for AllocateAddress to return correct
// Status.
// 
// 19    5/08/09 10:55a Markw
// Header updates.
// 
// 18    11/05/08 5:25p Markw
// Fix SMM Allocate Pool of type AllocateMaxAddress.
// 
// 17    9/09/08 4:30p Markw
// Add headers.
// 
// 16    9/07/08 12:45a Markw
// Separate SMM Private structure into inside SMM and outside SMM
// structure. Remove access to BS function for CRC.
// 
// 15    6/09/08 5:47p Markw
// CPU0 has its own AP control structure. CPU0 can now be the AP.
// 
// 14    3/14/07 5:57p Markw
// Only allow SmmStartupThisAp if all CPUs are in SMM.
// 
//**********************************************************************

//<AMI_FHDR_START>
//---------------------------------------------------------------------------
//
// Name: Smst.c
//
// Description:	Smst functions.
//
//---------------------------------------------------------------------------
//<AMI_FHDR_END>

//This include should come first.
#include "SmmPrivateShared.h"
#include <AmiDxeLib.h>
#include <AmiCspLib.h>

#if SMM_USE_FRAMEWORK
#include <Smm.h>
#endif

#if SMM_USE_PI
#include <SmmPi.h>
#endif

#include "ReferenceCode\Haswell\Include\CpuRegs.h"
#ifndef BIT35
#define BIT35 0x0000000800000000ULL
#endif

//TODOx64: move it to a library header
VOID CPULib_Pause();

VOID *Allocate(VOID *Base, UINTN Size,UINTN Alignment);

EFI_STATUS AllocateABSegPages(
	IN EFI_ALLOCATE_TYPE		Type,
	IN UINTN					NumberOfPages,
	IN OUT EFI_PHYSICAL_ADDRESS	*Memory
);
EFI_STATUS FreeABSegPages(
	IN EFI_PHYSICAL_ADDRESS	Memory,
	IN UINTN				NumberOfPages
);

BOOLEAN Free(VOID *Buffer);
BOOLEAN Free4kPages(VOID *StartAddress,UINTN Pages);

UINT8* Align2n(UINT8 *Value,UINTN Alignment);

#if SMM_USE_FRAMEWORK

EFI_STATUS CalculateCrc32(
	IN VOID *Data, IN UINTN DataSize, OUT UINT32 *Crc32
);

extern EFI_SMM_SYSTEM_TABLE		        gSmmSystemTable;
extern UINT8                            **gSmmBase;
#endif

#if SMM_USE_PI
extern EFI_SMM_SYSTEM_TABLE2            gSmmSystemTable2;
#endif


extern SMM_DISPATCHER_PRIVATE_STRUCT   *gDispatcherPrivate;

static UINT32 CrcTable[256];

//<AMI_PHDR_START>
//---------------------------------------------------------------------------
//
// Procedure: InitCrc
//
// Description: InitCrc
//
// Input: VOID
//
// Output: VOID
//
//---------------------------------------------------------------------------
//<AMI_PHDR_END>

VOID InitCrc()
{
	UINT32 i, j;
	for(i = 0; i < 256; i++) {
		CrcTable[i] = i;
		for(j = 8; j > 0; j--) 
			CrcTable[i] =
                (CrcTable[i] & 1) ? (CrcTable[i] >> 1) ^ 0xedb88320 : CrcTable[i] >> 1;
	}
}

//<AMI_PHDR_START>
//---------------------------------------------------------------------------
//
// Procedure: CalculateCrc32
//
// Description: Calculate Crc 32
//
// Input: 
//  IN VOID *Data
//  IN UINTN DataSize
//  OUT UINT32 *Crc32
//
// Output:
//	EFI_STATUS
//
//---------------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS CalculateCrc32(
	IN VOID *Data, IN UINTN DataSize, OUT UINT32 *Crc32
)
{
	UINT32 i, crc = (UINT32)-1;
	if (!Data || !DataSize || !Crc32) return EFI_INVALID_PARAMETER;
	for(i = 0; i < DataSize; i++) crc = (crc >> 8) ^ CrcTable[(UINT8)crc ^ ((UINT8*)Data)[i]];
	*Crc32 = ~crc;
	return EFI_SUCCESS;
}

//<AMI_PHDR_START>
//---------------------------------------------------------------------------
//
// Procedure: SmmMemRead
//
// Description: Read memory buffer.
//
// Input: 
//  IN EFI_SMM_CPU_IO_INTERFACE *This
//  IN EFI_SMM_IO_WIDTH         Width
//  IN UINT64                   Address
//  IN UINTN                    Count
//  IN OUT VOID                 *Buffer
//
// Output:
//	EFI_STATUS
//  * EFI_SUCCESS - Buffer written Successfully.
//  * EFI_INVALID_PARAMETER - 0 Count, Unsupported Width, or memory region out of range.
//
//---------------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS SmmMemRead(
    IN EFI_SMM_CPU_IO_INTERFACE *This,
    IN EFI_SMM_IO_WIDTH         Width,
    IN UINT64                   Address,
    IN UINTN                    Count,
    IN OUT VOID                 *Buffer
)
{
	UINT8	ByteWidth;
	if (Width >= (UINTN)SMM_IO_UINT64) return EFI_INVALID_PARAMETER;
	if (!Count) return EFI_INVALID_PARAMETER;
	
	ByteWidth = (UINT8)(1 << Width);

	
	//Alignment must be done by the caller.
	switch(ByteWidth) {
	case 1:
		while(Count--) {
			*(UINT8*)Buffer = *(UINT8*)(UINTN)Address;
			++((UINT8*)(UINTN)Buffer);
			++((UINT8*)(UINTN)Address);
		}
		break;
	case 2:
		while(Count--) {
			*(UINT16*)Buffer = *(UINT16*)(UINTN)Address;
			++((UINT16*)(UINTN)Buffer);
			++((UINT16*)(UINTN)Address);
		}
		break;
	default: //case 4:
		while(Count--) {
			*(UINT32*)Buffer = *(UINT32*)(UINTN)Address;
			++((UINT32*)(UINTN)Buffer);
			++((UINT32*)(UINTN)Address);
		}
		break;
	}

	return EFI_SUCCESS;
}

//<AMI_PHDR_START>
//---------------------------------------------------------------------------
//
// Procedure: SmmMemWrite
//
// Description: Write to memory from buffer.
//
// Input: 
//  IN EFI_SMM_CPU_IO_INTERFACE *This
//  IN EFI_SMM_IO_WIDTH         Width
//  IN UINT64                   Address
//  IN UINTN                    Count
//  IN OUT VOID                 *Buffer
//
// Output:
//  EFI_STATUS
//  * EFI_SUCCESS - Buffer written Successfully.
//  * EFI_INVALID_PARAMETER - 0 Count, Unsupported Width, or memory region out of range.
//
//---------------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS SmmMemWrite(
	IN EFI_SMM_CPU_IO_INTERFACE	*This,
	IN EFI_SMM_IO_WIDTH			Width,
	IN UINT64					Address,
	IN UINTN					Count,
	IN OUT VOID					*Buffer
	)
{
	UINT8	ByteWidth;
	if (Width >= (UINTN)SMM_IO_UINT64) return EFI_INVALID_PARAMETER;
	if (!Count) return EFI_INVALID_PARAMETER;
	
	//Alignment must be done by the caller.
	ByteWidth = (UINT8)(1 << Width);
	
	switch(ByteWidth) {
	case 1:
		while(Count--) {
			*(UINT8*)(UINTN)Address = *(UINT8*)(UINTN)Buffer;
			++((UINT8*)(UINTN)Buffer);
			++((UINT8*)(UINTN)Address);
		}
		break;
	case 2:
		while(Count--) {
			*(UINT16*)(UINTN)Address = *(UINT16*)(UINTN)Buffer;
			++((UINT16*)(UINTN)Buffer);
			++((UINT16*)(UINTN)Address);
		}
		break;
	default: //case 4:
		while(Count--) {
			*(UINT32*)(UINTN)Address = *(UINT32*)(UINTN)Buffer;
			++((UINT32*)(UINTN)Buffer);
			++((UINT32*)(UINTN)Address);
		}
		break;
	}

	return EFI_SUCCESS;
}

//<AMI_PHDR_START>
//---------------------------------------------------------------------------
//
// Procedure: SmmIoRead
//
// Description: Read io buffer.
//
// Input: 
//  IN EFI_SMM_CPU_IO_INTERFACE	*This
//  IN EFI_SMM_IO_WIDTH         Width
//  IN UINT64                   Address
//  IN UINTN                    Count
//  IN OUT VOID                 *Buffer
//
// Output:
//	EFI_STATUS
//  * EFI_SUCCESS - Buffer written Successfully.
//  * EFI_INVALID_PARAMETER - 0 Count, Unsupported Width, or memory region out of range.
//
//---------------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS SmmIoRead(
	IN EFI_SMM_CPU_IO_INTERFACE	*This,
	IN EFI_SMM_IO_WIDTH			Width,
	IN UINT64					Address,
	IN UINTN					Count,
	IN OUT VOID					*Buffer
	)
{
	UINT8	ByteWidth;
	if (Width >= (UINTN)SMM_IO_UINT64) return EFI_INVALID_PARAMETER;
	if (!Count) return EFI_INVALID_PARAMETER;
	
	ByteWidth = (UINT8)(1 << Width);
	
	if (Address + ByteWidth * Count > 0x10000) return EFI_INVALID_PARAMETER;	//Beyond IO space.
	if ((UINT64)(UINTN)Buffer + ByteWidth * Count > (UINT64)0x100000000) return EFI_INVALID_PARAMETER;	//Beyond address space.	

	//Alignment must be done by the caller.
	switch(ByteWidth) {
	case 1:
		while(Count--) {
			*(UINT8*)Buffer = IoRead8((UINT16)Address);
			++((UINT8*)(UINTN)Buffer);
			++((UINT8*)(UINTN)Address);
		}
		break;
	case 2:
		while(Count--) {
			*(UINT16*)(UINTN)Buffer = IoRead16((UINT16)Address);
			++((UINT16*)(UINTN)Buffer);
			++((UINT16*)(UINTN)Address);
		}
		break;
	default: //case 4:
		while(Count--) {
			*(UINT32*)Buffer = IoRead32((UINT16)Address);
			++((UINT32*)(UINTN)Buffer);
			++((UINT32*)(UINTN)Address);
		}
		break;
	}

	return EFI_SUCCESS;
}

//<AMI_PHDR_START>
//---------------------------------------------------------------------------
//
// Procedure: SmmIoWrite
//
// Description: Write to Io from buffer.
//
// Input: 
//  IN EFI_SMM_CPU_IO_INTERFACE	*This
//  IN EFI_SMM_IO_WIDTH         Width
//  IN UINT64                   Address
//  IN UINTN                    Count
//  IN OUT VOID                 *Buffer
//
// Output:
//  EFI_STATUS
//  * EFI_SUCCESS - Buffer written Successfully.
//  * EFI_INVALID_PARAMETER - 0 Count, Unsupported Width, or memory region out of range.
//
//---------------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS SmmIoWrite(
	IN EFI_SMM_CPU_IO_INTERFACE	*This,
	IN EFI_SMM_IO_WIDTH			Width,
	IN UINT64					Address,
	IN UINTN					Count,
	IN OUT VOID					*Buffer
	)
{
	UINT8	ByteWidth;
	if (Width >= (UINTN)SMM_IO_UINT64) return EFI_INVALID_PARAMETER;
	if (!Count) return EFI_INVALID_PARAMETER;
	
	ByteWidth = (UINT8)(1 << Width);
	
	if (Address + ByteWidth * Count > 0x10000) return EFI_INVALID_PARAMETER;	//Beyond IO space.
	if ((UINT64)(UINTN)Buffer + ByteWidth * Count > (UINT64)0x100000000) return EFI_INVALID_PARAMETER;	//Beyond address space.	
	
	//Alignment must be done by the caller.
	switch(ByteWidth) {
	case 1:
		while(Count--) {
			IoWrite8((UINT16)Address,*(UINT8*)(UINTN)Buffer);
			++((UINT8*)(UINTN)Buffer);
			++((UINT8*)(UINTN)Address);
		}
		break;
	case 2:
		while(Count--) {
			IoWrite16((UINT16)Address,*(UINT16*)(UINTN)Buffer);
			++((UINT16*)(UINTN)Buffer);
			++((UINT16*)(UINTN)Address);
		}
		break;
	default: //case 4:
		while(Count--) {
			IoWrite32((UINT16)Address,*(UINT32*)(UINTN)Buffer);
			++((UINT32*)(UINTN)Buffer);
			++((UINT32*)(UINTN)Address);
		}
		break;
	}

	return EFI_SUCCESS;
}

//<AMI_PHDR_START>
//---------------------------------------------------------------------------
//
// Procedure: SmmSmstAllocatePool
//
// Description: Allocate a pool of memory.
//
// Input: 
//  IN EFI_MEMORY_TYPE  PoolType
//  IN UINTN            Size
//  OUT VOID            **Buffer
//
// Output:
//	EFI_STATUS
//  * EFI_SUCCESS - Pool of memory allocated.
//  * EFI_INVALID_PARAMETER - Allocate 0 size.
//  * EFI_OUT_OF_RESOURCES - Memory unavailable.
//
//---------------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS SmmSmstAllocatePool(
	IN EFI_MEMORY_TYPE	PoolType,
	IN UINTN			Size,
	OUT VOID			**Buffer
	)
{
	if (!Size) return EFI_INVALID_PARAMETER;
	*Buffer = Allocate(0,Size,0);
	if (!(*Buffer)) return EFI_OUT_OF_RESOURCES;
	return EFI_SUCCESS;
}

//<AMI_PHDR_START>
//---------------------------------------------------------------------------
//
// Procedure: SmmSmstFreePool
//
// Description: Free Allocated memory.
//
// Input: 
//  IN VOID *Buffer
//
// Output:
//  EFI_STATUS
//  * EFI_SUCCESS - Memory is freed.
//  * EFI_INVALID_PARAMETER - Memory starting at Buffer was not allocated.
//
//---------------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS SmmSmstFreePool(
	IN VOID	*Buffer
	)
{
	if (!Free(Buffer)) return EFI_INVALID_PARAMETER;
	return EFI_SUCCESS;
}

//<AMI_PHDR_START>
//---------------------------------------------------------------------------
//
// Procedure: SmmSmstAllocatePages
//
// Description: Allocate # pages at any address, a max address, or a specified address.
//
// Input: 
//  IN EFI_ALLOCATE_TYPE        Type
//  IN EFI_MEMORY_TYPE          MemoryType
//  IN UINTN                    NumberOfPages
//  OUT EFI_PHYSICAL_ADDRESS    *Memory
//
// Output:
//	EFI_STATUS
//	* EFI_SUCCESS - Memory allocated.
//  * EFI_OUT_OF_RESOURCES - Memory already allocated or unavailable.
//  * EFI_INVALID_PARAMETER - Incorrect Type or specified address not 4k aligned.
//
//---------------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS SmmSmstAllocatePages(
	IN EFI_ALLOCATE_TYPE		Type,
	IN EFI_MEMORY_TYPE			MemoryType,
	IN UINTN					NumberOfPages,
	IN OUT EFI_PHYSICAL_ADDRESS	*Memory
	)
{
    VOID *AllocatedMemory;

	if (!NumberOfPages) return EFI_INVALID_PARAMETER;
	if (Type != AllocateAnyPages && *Memory <= 0x100000) return AllocateABSegPages(Type, NumberOfPages, Memory);
    
    switch(Type) {
	case AllocateAnyPages:
	    *Memory = (EFI_PHYSICAL_ADDRESS)(UINTN)Allocate(0, NumberOfPages * 4096, 4095);
        if (!(*Memory)) return EFI_OUT_OF_RESOURCES;
        return EFI_SUCCESS;
        
    case AllocateMaxAddress:
	    AllocatedMemory = Allocate(0, NumberOfPages * 4096, 4095);
        if (!AllocatedMemory) return EFI_OUT_OF_RESOURCES;
        if ((UINTN)AllocatedMemory > *(UINTN*)(UINTN)Memory) {
            Free(AllocatedMemory);
            return EFI_OUT_OF_RESOURCES;
        }
        *Memory = (EFI_PHYSICAL_ADDRESS)(UINTN)AllocatedMemory;
        return EFI_SUCCESS;
    case AllocateAddress:
	    if ((UINT8*)(UINTN)*Memory != Align2n((UINT8*)(UINTN)*Memory,4095)) return EFI_INVALID_PARAMETER;
		AllocatedMemory = Allocate((UINT8*)(UINTN)*Memory,NumberOfPages * 4096,0);
        if (!AllocatedMemory) return EFI_OUT_OF_RESOURCES;
        return EFI_SUCCESS;
	}
    return EFI_INVALID_PARAMETER;
}

//<AMI_PHDR_START>
//---------------------------------------------------------------------------
//
// Procedure: SmmSmstFreePages
//
// Description:
//  Free pages. The address must be on a page boundary, but it doesn't have to
//  start on address from AllocatePages. It only frees the requested pages.
//
// Input: 
//  IN EFI_PHYSICAL_ADDRESS Memory
//  IN UINTN                NumberOfPages
//
//---------------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS SmmSmstFreePages(
	IN EFI_PHYSICAL_ADDRESS Memory,
	IN UINTN NumberOfPages
	)
{
	if (Memory <= 0x100000) return FreeABSegPages(Memory, NumberOfPages);

	if (!Free4kPages((VOID*)(UINTN)Memory,NumberOfPages)) return EFI_INVALID_PARAMETER;
	return EFI_SUCCESS;
}

//<AMI_PHDR_START>
//---------------------------------------------------------------------------
//
// Procedure: SmmStartupThisAp
//
// Description: Execute a procedure on an AP.
//
// Input: 
//	IN EFI_AP_PROCEDURE         Procedure
//	IN UINTN                    CpuNumber
//	IN OUT VOID                 *ProcArguments 	OPTIONAL
//
// Output:
//	EFI_STATUS
//
//---------------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS SmmStartupThisAp(
    IN EFI_AP_PROCEDURE         Procedure,
    IN UINTN                    CpuNumber,
    IN OUT VOID                 *ProcArguments  OPTIONAL
)
{
    volatile SMM_AP_CPU_CONTROL *SmmApCpuControl;
    BOOLEAN IsBlocking = (BOOLEAN)(CpuNumber != (UINTN)-1);
    UINT32 i;

    if (Procedure == NULL) return EFI_INVALID_PARAMETER;
    if (CpuNumber == gDispatcherPrivate->SmmBspNumber) return EFI_INVALID_PARAMETER;
    if (CpuNumber >= gDispatcherPrivate->NumCpus && IsBlocking) return EFI_INVALID_PARAMETER;

    if (IsBlocking) {
        if (!gDispatcherPrivate->SmmCpuInfo[CpuNumber].InSmm) return EFI_NOT_READY;
        SmmApCpuControl = &gDispatcherPrivate->SmmApCpuControl[CpuNumber];

        SmmApCpuControl->ProcArguments = ProcArguments;
        SmmApCpuControl->Procedure = Procedure;

        if ( !((ReadMsr (MSR_PLATFORM_INFO) & B_MSR_PLATFORM_INFO_PFAT_AVAIL) && 
               (ReadMsr (MSR_PLAT_FRMW_PROT_CTRL) & B_MSR_PLAT_FRMW_PROT_CTRL_EN)) ) {  
              while(SmmApCpuControl->Procedure) CPULib_Pause();
        }
        return EFI_SUCCESS;
    }

    for (i = 0; i < gDispatcherPrivate->NumCpus; ++i) {
        if (i == gDispatcherPrivate->SmmBspNumber) continue;
        if (!gDispatcherPrivate->SmmCpuInfo[i].InSmm) continue;
        SmmApCpuControl = &gDispatcherPrivate->SmmApCpuControl[i];
        ASSERT(SmmApCpuControl->Procedure == NULL);
        if (SmmApCpuControl->Procedure != NULL) continue;

        SmmApCpuControl->ProcArguments = ProcArguments;
        SmmApCpuControl->Procedure = Procedure;
    }

    return EFI_SUCCESS;
}

//<AMI_PHDR_START>
//---------------------------------------------------------------------------
//
// Procedure: MoveToNewConfigurationTable
//
// Description: Create a new bigger or smaller table and copy the old table to the new table.
//
// Input: 
//	IN EFI_CONFIGURATION_TABLE  *OldTable
//	IN UINTN                    NumOldDescriptors
//	IN UINTN                    NumDescriptors
//
// Output:
//	EFI_CONFIGURATION_TABLE * - New table address.
//
//---------------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_CONFIGURATION_TABLE * MoveToNewConfigurationTable(
	EFI_CONFIGURATION_TABLE *OldTable,
	UINTN NumOldDescriptors,
	UINTN NumDescriptors
	)
{	
	EFI_CONFIGURATION_TABLE *NewTable,*Descriptor,*OldDescriptor;
	UINTN i;
	//Create new table
	if (SmmSmstAllocatePool(0,NumDescriptors * sizeof(EFI_CONFIGURATION_TABLE),&NewTable)!=EFI_SUCCESS) return 0;
	
	//If new table is larger, only copy valid descriptors.
	//If new table is smaller, only copy descriptors for allocated table.
	NumDescriptors  = NumDescriptors > NumOldDescriptors ? NumOldDescriptors : NumDescriptors;
	Descriptor = NewTable;
	OldDescriptor = OldTable;
	for (i=0;i<NumDescriptors;++i) *Descriptor++ = *OldDescriptor++;
	
	//Free old table
	SmmSmstFreePool(OldTable);

	return NewTable;
}

//<AMI_PHDR_START>
//---------------------------------------------------------------------------
//
// Procedure: SmmInstallConfigurationTable
//
// Description:
//	This procedure add/updates/deletes configuration table entries.
//
// Configuration Table Entry definition:
//	EFI_GUID    VendorGuid
//	VOID        *VenderTable
//
// 1. If Vendor Guid is not in table and Input table isn't NULL, add Guid/Table pair.
// 2. If Vendor Guid is in table and Input table isn't NULL, update Guid/Table pair.
// 3. If Vendor Guid is in table and Input table is NULL, remove Guid/Tablble pair.
// 4. If Vendor Guid is not in table, Input table is NULL, return EFI_NOT_FOUND. Nothing to delete.
//
// Input: 
//  IN EFI_SMM_SYSTEM_TABLE *SystemTable
//  IN EFI_GUID             *Guid
//  IN VOID                 *Table
//  IN UINTN                TableSize
//
// Output:
//  EFI_STATUS
//  * EFI_SUCCESS - Add/update/remove operation successful.
//  * EFI_INVALID_PARAMETER - Guid = 0.
//  * EFI_NOT_FOUND - Can not delete a nonexistent entry.
//  * EFI_OUT_OF_RESOURCES - Not enough memory to complete operation.
//
//---------------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS SmmInstallConfigurationTable(
#if SMM_USE_FRAMEWORK
    IN EFI_SMM_SYSTEM_TABLE  *SystemTable,
#else
    IN EFI_SMM_SYSTEM_TABLE2 *SystemTable,
#endif
    IN EFI_GUID             *Guid,
    IN VOID                 *Table,
    IN UINTN                TableSize
    )
{
    UINTN   i;
    UINT32  CRC32;

#if SMM_USE_PI
    EFI_CONFIGURATION_TABLE **FirstEntryPtr = &gSmmSystemTable2.SmmConfigurationTable;
    EFI_CONFIGURATION_TABLE *Entry = *FirstEntryPtr;
    UINTN *NumberOfTableEntries = &gSmmSystemTable2.NumberOfTableEntries;
    UINT32 SystemTableSize = sizeof(gSmmSystemTable2);
 #else
    EFI_CONFIGURATION_TABLE **FirstEntryPtr = &gSmmSystemTable.SmmConfigurationTable;
    EFI_CONFIGURATION_TABLE *Entry = *FirstEntryPtr;
    UINTN *NumberOfTableEntries = &gSmmSystemTable.NumberOfTableEntries;
    UINT32 SystemTableSize = sizeof(gSmmSystemTable);
#endif

    EFI_CONFIGURATION_TABLE *NewConfigTable;
    VOID *NewVendorTable;

    if (!Guid) return EFI_INVALID_PARAMETER;

    for (i=0;i < *NumberOfTableEntries;++i) {
        if (guidcmp(&Entry->VendorGuid,Guid)==0) break;
        ++Entry;
    }
    if (i == *NumberOfTableEntries) Entry=0;

    if (!Entry) {
        if (!Table) return EFI_NOT_FOUND;
        //Add Guid
        NewConfigTable = MoveToNewConfigurationTable(
            *FirstEntryPtr,
            *NumberOfTableEntries,
            *NumberOfTableEntries+1);
        if (!NewConfigTable) return EFI_OUT_OF_RESOURCES;

        if (SmmSmstAllocatePool(0,TableSize,&NewVendorTable)!=EFI_SUCCESS) return EFI_OUT_OF_RESOURCES;
        MemCpy(NewVendorTable,Table,TableSize);
        *FirstEntryPtr = NewConfigTable;
        ++(*NumberOfTableEntries);
        NewConfigTable[*NumberOfTableEntries - 1].VendorGuid = *Guid;
        NewConfigTable[*NumberOfTableEntries - 1].VendorTable = NewVendorTable;
    } else {
        if (!Table) {
            //Remove Guid
            EFI_CONFIGURATION_TABLE *LastEntry = *FirstEntryPtr + *NumberOfTableEntries;

            SmmSmstFreePool(Entry->VendorTable);

            while (Entry != LastEntry) {
                *Entry = *(Entry + 1);
                ++Entry;
            }

            --(*NumberOfTableEntries);
        } else {
            //Update Guid
            if (SmmSmstAllocatePool(0,TableSize,&NewVendorTable)!=EFI_SUCCESS) return EFI_OUT_OF_RESOURCES;
            MemCpy(NewVendorTable,Table,TableSize);

            SmmSmstFreePool(Entry->VendorTable);
            Entry->VendorTable = NewVendorTable;
        }
    }

#if SMM_USE_PI && SMM_USE_FRAMEWORK
    gSmmSystemTable.SmmConfigurationTable = gSmmSystemTable2.SmmConfigurationTable;
    gSmmSystemTable.NumberOfTableEntries = gSmmSystemTable2.NumberOfTableEntries;
#endif

#if SMM_USE_PI
    gSmmSystemTable2.Hdr.CRC32 = 0;
    CalculateCrc32(&gSmmSystemTable2, SystemTableSize, &CRC32);
    gSmmSystemTable2.Hdr.CRC32 = CRC32;
#endif

#if SMM_USE_FRAMEWORK
    gSmmSystemTable.Hdr.CRC32 = 0;
    CalculateCrc32(&gSmmSystemTable, sizeof(EFI_SMM_SYSTEM_TABLE), &CRC32);
    gSmmSystemTable.Hdr.CRC32 = CRC32;
#endif

    return EFI_SUCCESS;
}


#if SMM_USE_FRAMEWORK

//////////////////////////////////////////
extern CHAR16 gSmmFirmwareVendor[];
EFI_SMM_SYSTEM_TABLE gSmmSystemTable =
{
    {                               //Header
    SMM_SMST_SIGNATURE,             //Signature
    EFI_SMM_SYSTEM_TABLE_REVISION,  //Revision
    sizeof(EFI_SMM_SYSTEM_TABLE),   //Header size
    0,                              //CRC32
    0                               //Reserved
	},
	gSmmFirmwareVendor,				//Vendor
	0,								//Vendor version
	SmmInstallConfigurationTable,
	EFI_SMM_CPU_IO_GUID,
	{
		{
			SmmMemRead,
		    SmmMemWrite
		},
		{	SmmIoRead,
			SmmIoWrite
		}
	},
	SmmSmstAllocatePool,
	SmmSmstFreePool,
	SmmSmstAllocatePages,
	SmmSmstFreePages,
	SmmStartupThisAp,
	1,								//Executing CPU
	1,								//Number of CPUs
	0,								//Cpu Save State
	0,								//Cpu Floating Point Save
	0,								//Number of Table Entries
	0								//Table pointer
};


//<AMI_PHDR_START>
//---------------------------------------------------------------------------
//
// Procedure: InitializeSmmSystemTable
//
// Description: Initialize the System Table.
//
// Input: SMM_BASE_PRIVATE_STRUCT *Private
//
// Output: VOID
//
//---------------------------------------------------------------------------
//<AMI_PHDR_END>

VOID InitializeSmmSystemTable()
{
	UINT32 CRC32;

	gSmmSystemTable.NumberOfCpus = gDispatcherPrivate->NumCpus;

    gSmmSystemTable.CpuSaveState = Allocate(0,sizeof(EFI_SMM_CPU_SAVE_STATE) * gSmmSystemTable.NumberOfCpus,0);
	gSmmSystemTable.CpuOptionalFloatingPointState = Allocate(0, 512 * gSmmSystemTable.NumberOfCpus, 15);	//16 byte alignment, Save floating point context.

	CalculateCrc32(&gSmmSystemTable, sizeof(EFI_SMM_SYSTEM_TABLE), &CRC32);
	gSmmSystemTable.Hdr.CRC32 = CRC32;
}

#endif

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
