//*************************************************************************
//*************************************************************************
//**                                                                     **
//**        (C)Copyright 1985-2008, American Megatrends, Inc.            **
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
// $Header: /Alaska/SOURCE/Modules/SMM/SMMDispatcher/SmmMemoryManager.c 12    4/22/10 4:39p Markw $
//
// $Revision: 12 $
//
// $Date: 4/22/10 4:39p $
//**********************************************************************
// Revision History
// ----------------
// $Log: /Alaska/SOURCE/Modules/SMM/SMMDispatcher/SmmMemoryManager.c $
// 
// 12    4/22/10 4:39p Markw
// Update to build with /w4 flag.
// 
// 11    5/08/09 10:56a Markw
// Header updates.
// 
// 10    12/16/08 2:34a Iminglin
// (EIP17767) The function value of FindFreeSpace, FindFreeAddress,
// Allocate for compliance.
// 
// 9     10/29/07 10:58a Markw
// Smm Thunk:
// * Code and data different segments.
// * Code position independent.
// * Switch for CSM for code and EBDA for data.
// 
// 8     10/24/07 12:02p Markw
// SMM Thunk code position independent. Data in a separate segment than
// code in Smm Thunk.
// 
// 7     7/25/07 2:11p Markw
// Exclude A000 region if needed.
// 
// 6     8/24/06 7:13p Felixp
// 
// 5     8/24/06 7:00p Felixp
// x64 support (warnings/errors fixed)
// 
// 4     4/25/06 6:25p Markw
// 
// 3     4/21/06 5:14p Markw
// 
// 2     7/19/05 6:09p Markw
// Add support for managing A&B SMM segments.
// 
// 1     1/28/05 4:32p Sivagarn
// SMM Dispatcher Component - Initial check in
// 
// 
//**********************************************************************

//<AMI_FHDR_START>
//---------------------------------------------------------------------------
//
// Name:		SmmMemoryManager.c
//
// Description:	Provides functions to manage SMM memory. Allocate and Free memory.
//
//---------------------------------------------------------------------------
//<AMI_FHDR_END>

#include <efi.h>
#include <AmiDxeLib.h>
#include "SmmPrivateShared.h"

#define NUM_MEM_DESCRIPTORS 30 //<--Number of descriptors before in a table. If more descriptors needed, a new table is created.

typedef struct _MEMORY_DESCRIPTOR MEMORY_DESCRIPTOR;
typedef struct _MEMORY_RESERVED_TABLE MEMORY_RESERVED_TABLE;


//<AMI_SHDR_START>
//---------------------------------------------------------------------------
//
// Name:        MEMORY_DESCRIPTOR
//
// Description:
//  Each descriptor contains the Base and end + 1 of each
//  memory allocation. The list is sorted from lowest to highest.
//  Last linked descriptor has a Link = 0.
//  Unused descriptors have links = 0xffffffff.
//
// Fields:     Name            Type                 Description
//        ------------------------------------------------------------
//        MemBase              UINT8*				Base address of allocated memory.
//        MemEnd			   UINT8*				End address + 1 of allocated memory.
//		  Link				   MEMORY_DESCRIPTOR*	Link to next Descriptor.
//
//---------------------------------------------------------------------------
//<AMI_SHDR_END>

struct _MEMORY_DESCRIPTOR
{
	UINT8				*MemBase;
	UINT8				*MemEnd;
	MEMORY_DESCRIPTOR	*Link;
};

//<AMI_SHDR_START>
//---------------------------------------------------------------------------
//
// Name:        MEMORY_RESERVED_TABLE
//
// Description:
//  Table stores memory descriptors. If runs out of descriptors,
//	additional tables will be linked. New tables can not be removed.
//	Unused descriptors Link will be 0xffffffff.
//	Last table Link = 0.
//			    
//
// Fields:     Name            Type                Description
//        ------------------------------------------------------------
//        MemDesc			MEMORY_DESCRIPTOR[]		Array of memory descriptors.	
//        MemNextTable		MEMORY_DESCRIPTOR		A descriptor used if a new table is created.		
//		  NumMemDescUsed	UINTN					Number of descriptors used.
//		  Link				MEMORY_RESERVED_TABLE*	Link to next table.
//
//---------------------------------------------------------------------------
//<AMI_SHDR_END>

struct _MEMORY_RESERVED_TABLE
{
	MEMORY_DESCRIPTOR		MemDesc[NUM_MEM_DESCRIPTORS];
	MEMORY_DESCRIPTOR		MemNextTable;
	UINTN					NumMemDescUsed;
	MEMORY_RESERVED_TABLE	*Link;
};

//Default descriptor for unused descriptor.
MEMORY_DESCRIPTOR gDefaultMemoryDescriptor = {0,0,(MEMORY_DESCRIPTOR*)(UINTN)0xffffffff};

//Default descriptor for next table.
MEMORY_DESCRIPTOR gDefaultMemoryDescriptor2 = {0,0,0};

UINT8	*gSmmMemBase;	
UINT8	*gSmmMemEnd;	//Top of SMM memory + 1.

MEMORY_RESERVED_TABLE	gTableHead;		//First memory table.
MEMORY_DESCRIPTOR		*gDescHead;		//Pointer to first descriptor. (Lowest memory address.)

BOOLEAN ABSegPageAlloc[32] = {
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,		//ASEG. 
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,		//BSEG. 	
};


//<AMI_PHDR_START>
//---------------------------------------------------------------------------
//
// Procedure:	Align8
//
// Description:	Align the address to nearest 8 byte alignment.
//
// Input:
//	UINTN	Value - Value to Align.
//
// Output:
//	UINTN - Aligned Value.
//
//---------------------------------------------------------------------------
//<AMI_PHDR_END>
UINTN Align8(UINTN Value)
{
	return (Value + 7) & ~7;
}

//<AMI_PHDR_START>
//---------------------------------------------------------------------------
//
// Procedure:	Align2n
//
// Description:	Align the address to nearest specified 2n alignment.
//				If the alignment isn't 2^n-1, then result will be invalid.
//
// Input:
//	UINT8	*Value - Pointer to value to Align.
//	UINTN	Alignment (This the 2n Alignment - 1. Example Alignment = 31, for 32 byte alignment.
//
// Output:
//	UINT8* - Aligned Value.
//
//---------------------------------------------------------------------------
//<AMI_PHDR_END>

UINT8* Align2n(UINT8 *Value,UINTN Alignment)
{
	return (UINT8*)(((UINTN)Value+Alignment) & ~Alignment);
}

//<AMI_PHDR_START>
//---------------------------------------------------------------------------
//
// Procedure:	ConstructMemoryReservedTable
//
// Description:	Intitialize the MEMORY_RESERVED_TABLE.
//
// Input:
//	MEMORY_RESERVED_TABLE	*Table
//
// Output:
//	VOID
//
//---------------------------------------------------------------------------
//<AMI_PHDR_END>

VOID ConstructMemoryReservedTable(MEMORY_RESERVED_TABLE *Table)
{
	UINTN i;
	for(i=0;i<NUM_MEM_DESCRIPTORS;++i) Table->MemDesc[i] = gDefaultMemoryDescriptor;
	Table->MemNextTable = gDefaultMemoryDescriptor2;
	Table->Link = 0;
}

//<AMI_PHDR_START>
//---------------------------------------------------------------------------
//
// Procedure:	FindFreeSpace
//
// Description:	Find a gap of free memory of a size and possibly of an alignment. This returns
//				the preceding memory descriptor. If no gaps are found, the last memory descriptor
//				is returned.
//
// Input:
//	UINTN	Size - Size of free space.
//	UINTN	Alignment OPTIONAL - This the 2n Alignment - 1. Example Alignment = 31, for 32 byte alignment.
//
// Output:
//	MEMORY_DESCRIPTOR *
//
// Notes:
//  Here is the control flow of this function:
//	1. Start with the first descriptor.
//  2. Evaluate the difference (empty space) between the 
//     (a) the base of address of the next descriptor and (b) the
//     aligned End address of the current descriptor.
//  3. If the difference is greater or equal to the requested size,
//     return the link.
//  4. Repeat 2-4, until out of descriptors.
//  5. Return the last descriptor.
//
//---------------------------------------------------------------------------
//<AMI_PHDR_END>

MEMORY_DESCRIPTOR *FindFreeSpace(
	IN UINTN Size,
	IN UINTN Alignment OPTIONAL)
{
	MEMORY_DESCRIPTOR	*Link;
	UINT8				*FreeStart;
	UINT8				*UsedNext;

	if (!Size) return NULL;

	//Find the preceding descriptor of a memory gap of the specified size (and alignment).
	for (Link = gDescHead; Link->Link; Link = Link->Link)
	{
		UINTN EmptySpace;
        FreeStart = Link->MemEnd;									//Beginning of possible gap.
		if (Alignment) FreeStart = Align2n(FreeStart,Alignment);	//Align possible gap to requested alignment.
		UsedNext  = Link->Link->MemBase;							//Find end of possible gap.
		EmptySpace = (UINTN)UsedNext - (UINTN)FreeStart;			//Gap size (may be negative because of alligned start)
        if ((INTN)EmptySpace >= (INTN) Size) return Link;			//If gap size is larger or equal requested size,
																	// return link of descriptor preceding link.
	}
    return Link;	//Out of descriptors, return last Link.
}

//<AMI_PHDR_START>
//---------------------------------------------------------------------------
//
// Procedure:	FindAddress
//
// Description:	Find a gap of free memory of an specific Address and a size.
//				If part of the space is taken, return 0.
//				If the space is found, return the preceding memory descriptor,
//				 or the last memory descriptor.
//
// Input:
//	UINTN	Size - Size of memory.
//	UINTN	Alignment  - This the 2n Alignment - 1. Example Alignment = 31, for 32 byte alignment.
//
// Output:
//	MEMORY_DESCRIPTOR * - 0 if the address range is taken.
//                      - not zero, if gap is found, or last link.
//
// Notes:
//  Here is the control flow of this function:
//	1. Start with the first descriptor.
//  2. If the specifed address is in the descriptor, it is taken return 0.
//  3. If the specified address is in the gap after the descriptor,
//       if the gap is big enough, return the preceding link, otherwise return 0.
//  4. Repeat steps 2-4 until iterated all the descriptors.
//  5. Return the last descriptor.
//
//---------------------------------------------------------------------------
//<AMI_PHDR_END>

MEMORY_DESCRIPTOR *FindFreeAddress(UINT8 *Address, UINTN Size)
{
	MEMORY_DESCRIPTOR	*Link;
	UINT8				*FreeStart;
	UINT8				*UsedNext;

	if (!Size) return NULL;

	for(Link = gDescHead; Link->Link; Link = Link->Link)
	{
		UINTN EmptySpace;
        FreeStart = Link->MemEnd;
		UsedNext  = Link->Link->MemBase;

		if (Address >= Link->MemBase && Address < FreeStart) return NULL;	//Space taken, if address is in the descriptor.

		if (Address >= FreeStart && Address <= UsedNext ) {				//Is address in the, gap after the descriptor.
			//UINTN typecasts used instead of UINT32, so complier won't give warning.
			EmptySpace = (UINTN)UsedNext - (UINTN)Address;
			if ((INTN)EmptySpace >= (INTN) Size) return Link;			//If enough space in gap, return Link
			return NULL;													//Space not available.
		}
	}
    return Link;	//Out of descriptors, return last Link.
}

//<AMI_PHDR_START>
//---------------------------------------------------------------------------
//
// Procedure:	GetEmptyDescriptor
//
// Description:	Find an unused memory descriptor in the tables.
//
// Input: VOID
//
// Output:
//	MEMORY_DESCRIPTOR * - 0 if can not allocate a new descriptor.
//                      - Empty descriptor.
//
// Notes:
//  Here is the control flow of this function:
//	1. Find a table with empty descriptors.
//  2. If a table is not found with an empty descriptor, go to step 5.
//  ---Found table with an empty descriptor---
//  3. Search descriptor array for an unused descriptors (Link = 0xffffffff)
//  4. Return the descriptor.
//  ---Did not find table with an empty descriptor---
//  5. Search memory descriptors for free space for a new table.
//  6. Check if last descriptor and enough free space at end, if not return 0.
//  7. Add a new memory table descriptor at the end of the returned descriptor.
//  8. Add new table link.
//  9. Construct a new table.
//  10. Return the first descriptor.
//
//---------------------------------------------------------------------------
//<AMI_PHDR_END>

MEMORY_DESCRIPTOR * GetEmptyDescriptor()
{
    MEMORY_RESERVED_TABLE	*Table = &gTableHead;
	MEMORY_RESERVED_TABLE	*PrevTable = NULL;
	MEMORY_DESCRIPTOR		*MemDesc;
	UINTN i;

	//Find a table with an unused descriptor.
	while (Table && (Table->NumMemDescUsed == NUM_MEM_DESCRIPTORS)) //If table full, find next descriptor.
	{
		PrevTable = Table;						//Keep track of last table, in case we need to create a new one.
		Table = Table->Link;
	}

	if (Table)									//Found table.
	{
		for(i=0;i<NUM_MEM_DESCRIPTORS;++i)
		{
			if (Table->MemDesc[i].Link == (MEMORY_DESCRIPTOR*)(UINTN)0xffffffff)	//Search for empty descriptor
			{
				++Table->NumMemDescUsed;
                return &Table->MemDesc[i];									//Return empty descriptor.
			}
		}   //Will not exit from this loop. An empty descriptor is guaranteed since NumMemDescUsed isn't the max.
	}

	//No more empty descriptors. Create a new table
	MemDesc = FindFreeSpace(sizeof(MEMORY_RESERVED_TABLE),0);			//Find free memory.
	
	//This is the address of the new table if there is space available for the table. The table doesn't exist yet.
	Table = (MEMORY_RESERVED_TABLE*) MemDesc->MemEnd;	

	if (!MemDesc->Link) {		//If end of descriptors, check if enough space for table.
        if ((UINT8*) Table + Align8(sizeof(MEMORY_RESERVED_TABLE)) > gSmmMemEnd) return 0;	//If out of space
	}
	
	PrevTable->MemNextTable.Link = MemDesc->Link;							//Add new table descriptor.
	MemDesc->Link = &PrevTable->MemNextTable;

	PrevTable->MemNextTable.MemBase = (UINT8*) Table;						//Fill in table descriptor
	PrevTable->MemNextTable.MemEnd  = (UINT8*) Table + Align8(sizeof(MEMORY_RESERVED_TABLE));
    PrevTable->Link = Table;												//Add table end of previous table link.

	ConstructMemoryReservedTable(Table);									//Fill in table with default values.
	Table->NumMemDescUsed = 1;												//1 descriptor is being allocated.

    return &Table->MemDesc[0];												//Return first descriptor.
}

//<AMI_PHDR_START>
//---------------------------------------------------------------------------
//
// Procedure:	RemoveDescriptor
//
// Description:	Find an unused memory descriptor in the tables.
//
// Input: MEMORY_DESCRIPTOR * Descriptor  -  Descriptor to free.
//
// Output: VOID
//
// Notes:
//  Here is the control flow of this function:
//	1. Start with first table.
//  2. Check each table's descriptor array for the descriptor to be removed.
//  3. If descriptor not found go to step 7.
//  ---Descriptor found---
//  4. Replace the Link with 0xffffffff.
//  5. Reduce number of descripors being used.
//  6. return.
//  ---Descriptor not found---
//  7. Repeat for next table steps 2-7 until last table.
//  8. Return
//
//---------------------------------------------------------------------------
//<AMI_PHDR_END>

VOID RemoveDescriptor(MEMORY_DESCRIPTOR * Descriptor)
{
	MEMORY_RESERVED_TABLE	*Table;
	UINTN i;
	
	for (Table = &gTableHead; Table; Table = Table->Link)
	{	
		if (Table->NumMemDescUsed==0) continue;
		for(i=0; i < NUM_MEM_DESCRIPTORS; ++i)
		{
			if (&Table->MemDesc[i] == Descriptor)
			{
				Table->MemDesc[i].Link = (MEMORY_DESCRIPTOR*)(UINTN)0xffffffff;
				--Table->NumMemDescUsed;			
				return;
			}
		}
	}
}

//<AMI_PHDR_START>
//---------------------------------------------------------------------------
//
// Procedure:	Allocate
//
// Description:
//  Allocate a memory. Caller may specify either a specific address
//	or alignment, or neither. Alignment is a minimum of 8 bytes.
//
// Input: 
//	IN VOID *Address OPTIONAL	- If caller wants to specify a specific address (Alignment is ignored).
//	IN UINTN Size				- Size of allocation.
//	UINTN Alignment OPTIONAL    - Specific alignment, if required. An address must not be given.
//                                If alignment is set to 0, then alignment is 8 bytes. (Required by SMM spec.)
//
// Output:
// VOID *						- Memory allocated start address.
//
// Notes:
//  Here is the control flow of this function:
//	1. If no size requested return 0.
//  2. Align Size up to the nearest 8 bytes.
//  3. Get an empty descriptor. If none, return 0.
//  4. If Address is given, set BaseStart to address.
//     If not aligned on 8 byte boundary, remove descriptor and return 0.
//  5. Otherwise, set BaseStart to gSmmMemBase and
//     align if and to the given alignment. (Bottom of SMM.)
//  6. If Size requested is greater than the Smm memory region,
//     remove descriptor and return 0.
//  7. If no memory is previously allocated, setup descriptor, and point to it from gDescHead.
//     (Baseaddress is either the Address requested or beggining of Smm RAM.) Return address.
//  8. Otherwise if requested memory base is lower than the base pointed by gDescHead or
//		gap between start of smm ram and memory base pointed to by gDescHead is larger than
//			the size requested is available,
//      fill in memory descriptor, and add it in front of gDescHead, replacing gDescHead. Return Address.
//  9. Otherwise, if address address, find descriptor preceding the Address requested.
//  10. If size requested, find the descriptor preceding the gap >= Size requested.
//  11. If last descriptor, if not enough space left, remove descriptor, and return 0.
//  12. Fill in descriptor. Return Address.
//
//---------------------------------------------------------------------------
//<AMI_PHDR_END>

void * Allocate(
	IN VOID *Address OPTIONAL,
	IN UINTN Size,
	UINTN Alignment OPTIONAL
	)
{
	MEMORY_DESCRIPTOR	*EmptyDesc = NULL;
	MEMORY_DESCRIPTOR	*FreeSpaceDesc;
	UINT8				*BaseStart;

	if (!Size) return NULL;

	Size = Align8(Size);									//Minimum size requested is 8 bytes.
        
	EmptyDesc = GetEmptyDescriptor();
	if (!EmptyDesc){
	 	return NULL;		//Return if out of descriptors.
	}

	if (Address) 
	{
		if ((UINTN)Address != Align8((UINTN)Address)) {RemoveDescriptor(EmptyDesc);return 0;}	//Address must be 8 byte aligned.
		BaseStart = Address;
	} else {
		BaseStart = gSmmMemBase;
		if (Alignment) BaseStart = Align2n(BaseStart,Alignment);
	}
		
	if (Size > (UINTN)(gSmmMemEnd - BaseStart)) {	//If Smm Memory is smaller than requested, return error.
		RemoveDescriptor(EmptyDesc);
		return NULL;
	}

	if (!gDescHead)									//True if no previous allocated memory.
	{
        EmptyDesc->MemBase	= BaseStart;
		EmptyDesc->Link		= 0;
		
		gDescHead = EmptyDesc;
	//else if is true if requested memory base or gap larger than the size requested is available.
	} else if (((INTN) gDescHead->MemBase - (INTN)BaseStart) >= (INTN) Size) {//Insert before gDescHead;
		EmptyDesc->MemBase=BaseStart;
		EmptyDesc->Link = gDescHead;
		gDescHead = EmptyDesc;
	//else is true if memory base is more than
	} else {
		if (Address)
		{
			FreeSpaceDesc = FindFreeAddress(Address,Size);
			if (!FreeSpaceDesc)
			{
				RemoveDescriptor(EmptyDesc);
				return NULL;
			}
			BaseStart = Address;
		} else {
			FreeSpaceDesc = FindFreeSpace(Size,Alignment);
			BaseStart = FreeSpaceDesc->MemEnd;
			if (Alignment) BaseStart = Align2n(BaseStart,Alignment);
		}
		
		if(!FreeSpaceDesc->Link && (UINTN)(gSmmMemEnd - BaseStart) < Size)
		{   //Last Link and not enough room.
			RemoveDescriptor(EmptyDesc);
			return NULL;
		}
	
		EmptyDesc->MemBase = BaseStart;
		EmptyDesc->Link = FreeSpaceDesc->Link;
		FreeSpaceDesc->Link = EmptyDesc;
	}

	EmptyDesc->MemEnd = EmptyDesc->MemBase + Size;
    
    return EmptyDesc->MemBase;
}

//<AMI_PHDR_START>
//---------------------------------------------------------------------------
//
// Procedure:	Free
//
// Description:	Free an allocated buffer.
//
// Input: 
//	IN VOID *Buffer - Allocation to free.
//
// Output:
// BOOLEAN	- TRUE if buffer freed.
//
// Notes:
//  Here is the control flow of this function:
//	1. If no allocations, return FALSE.
//  2. If Buffer to free is gDescHead, set gDescHead to next Link, remove decriptor, and return TRUE.
//  3. Search link list for buffer.
//  4. If not found, return FALSE.
//  5. Set previous link of buffer to link after buffer.
//  6. Remove Descriptor.
//  7. Return TRUE.
//
//---------------------------------------------------------------------------
//<AMI_PHDR_END>

BOOLEAN Free(VOID *Buffer)
{
	MEMORY_DESCRIPTOR *Link;
	MEMORY_DESCRIPTOR *Prev;

    if (!gDescHead) return FALSE;
	if (gDescHead->MemBase == (UINT8*)Buffer)
	{
		Link = gDescHead;
		gDescHead = gDescHead->Link;
		RemoveDescriptor(Link);
		return TRUE;
	}

	Prev = gDescHead; Link = gDescHead->Link;

	while(Link)
	{
		if (Link->MemBase == Buffer)
		{
			Prev->Link = Link->Link;
			RemoveDescriptor(Link);
			return TRUE;
		}
		Prev = Link;
		Link = Link->Link;
	}
	return FALSE;
}

//<AMI_PHDR_START>
//---------------------------------------------------------------------------
//
// Procedure:	Free4kPages
//
// Description:	Free pages from buffer.
//
// Input: 
//	IN VOID		*StartAddress - Pages to free.
//  IN UINTN	Pages		  - # of 4k pages. 
//
// Output:
// BOOLEAN	- TRUE if buffer freed.
//
// Notes:
//  Here is the control flow of this function:
//	1. If End Address is not greater than 4G, return FALSE.
//  2. If StartAddress is not aligned 4k, return FALSE.
//  3. If no allocations, return FALSE.
//  4. Search for a descriptor with the StartAddress is allocated.
//  5. If descriptor not found, return FALSE.
//  6. Search for a descriptor with the EndAddress is allocated. These criteria must be met which searching.
//     * Allocation size of each descriptor must be 4k pages, otherwise return FALSE.
//     * End address of descriptor must match base address of next descriptor (no free space), otherwise return FALSE.
//  7. If descriptor not found, return FALSE.
//  8. If Start and End descriptors are not the same go to step 13.
//  -----Start and End Descriptor match exactly.----
//  9. If Base and End descriptor match exactly, remove the descriptor from the list.
//  10. If only Start Address matches exactly, free that space by setting the start address to the End Address.
//  11. If only the End Address matches exactly, move the end address to Start Address.
//  Note: the end address of the descriptor is not allocated.
//  12. return TRUE.
//  ----Start and End Descriptors are different descriptors.----
//  13. If Base address of the Start Descriptor, adjust its end address to the space, and
//      move the Start Descriptor to the next descriptor.
//  14. Free the descriptors up till the end descriptor.
//  15. If the End Descriptor's End address doesn match the end address to free,
//      set the base address to the end address, to free the space.
//  16. Otherwise, remove the end descriptor.
//  17. Return True.
//---------------------------------------------------------------------------
//<AMI_PHDR_END>

BOOLEAN Free4kPages(VOID *StartAddress,UINTN Pages)
{
	MEMORY_DESCRIPTOR *StartDesc,*EndDesc,*PrevStart = NULL,*Link,*Link2;
	UINT8* EndAddress = (UINT8*) StartAddress + 4096 * Pages;
	if (EndAddress < (UINT8*)StartAddress) return FALSE;	//If Endaddress > 4G.

	if (StartAddress != Align2n(StartAddress,4095)) return FALSE;	//Must be align 4k.

	//--------Find Beginning and End of Descriptors to adjust--------

	if (!gDescHead) return FALSE;
	for (StartDesc = gDescHead; StartDesc; StartDesc = StartDesc->Link)
	{
		if ((UINT8*)StartAddress >= StartDesc->MemBase && (UINT8*)StartAddress < StartDesc->MemEnd) break;
		PrevStart = StartDesc;
	}

	if (!StartDesc) return FALSE;

	EndDesc = StartDesc;
	for (;;)
	{
		if ((UINT8*)(EndDesc->MemEnd - EndDesc->MemBase) != Align2n((UINT8*)(EndDesc->MemEnd - EndDesc->MemBase),4095))
			return FALSE; //Size must be multiple of 4k.

		if (EndAddress >= EndDesc->MemBase && EndAddress <= EndDesc->MemEnd) break;
		if (!EndDesc->Link) return FALSE;
		if (EndDesc->MemEnd != EndDesc->Link->MemBase) return FALSE;	//Gap of unallocated space in region to free.
		EndDesc=EndDesc->Link;
	}

	//--------Adjust Descriptors, Removing unused ones--------

	if (StartDesc == EndDesc)					//If true, range only affects 1 descriptor.
	{
		if (StartAddress == StartDesc->MemBase)
		{
			if (EndAddress == StartDesc->MemEnd) //If descriptor matches address exactly, free descriptor.
			{
				if (StartDesc == gDescHead) gDescHead = StartDesc->Link;
				else PrevStart->Link = StartDesc->Link;
				RemoveDescriptor(StartDesc);
				return TRUE;
			}
			StartDesc->MemBase = EndAddress;		//Start address matches, change start address.
			return TRUE;
		}
		StartDesc->MemEnd = StartAddress;			//If End address matches, change End address.
		return TRUE;
	}


	//Range affects multiple descriptors.
	if (StartAddress != StartDesc->MemBase)
	{
		StartDesc->MemEnd = StartAddress;

		PrevStart = StartDesc;
		StartDesc = StartDesc->Link;				//Don't delete this descriptor, since it has been adjusted.
	}


	//Remove descriptors in the middle before End.
	if (StartDesc == gDescHead) gDescHead = EndDesc;
	else PrevStart->Link = EndDesc;

	for (Link = StartDesc; Link != EndDesc; Link = Link2)
	{
		Link2 = Link->Link;
		RemoveDescriptor(Link); //Remove Descriptors in between.
	}
		
	
	//If end address matches, free descriptor, otherwise adjust end address.
	if (EndAddress != EndDesc->MemEnd)
	{
		EndDesc->MemBase = EndAddress;
	} else {
		if (EndDesc==gDescHead) gDescHead = EndDesc->Link;
		else PrevStart->Link = EndDesc->Link;
		RemoveDescriptor(EndDesc);	
	}

	return TRUE;
}

//<AMI_PHDR_START>
//---------------------------------------------------------------------------
//
// Procedure:	AllocateABSegPages
//
// Description:	Allocate SMM 4k pages of memory in A or B segment.
//
// Input: 
//	IN EFI_ALLOCATE_TYPE		Type
//	IN UINTN					NumberOfPages
//	IN OUT EFI_PHYSICAL_ADDRESS	*Memory
//
// Output:
//  EFI_STATUS
//
//---------------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS AllocateABSegPages(
	IN EFI_ALLOCATE_TYPE		Type,
	IN UINTN					NumberOfPages,
	IN OUT EFI_PHYSICAL_ADDRESS	*Memory
)
{
	UINTN	i;
	UINT8	FreePageCount;
	UINTN	StartPage, EndPage;
	UINT32	MaxAddress;

	VOID	**pMemory32 = (VOID**) Memory;
	UINT32	Memory32 = (UINT32)(UINTN)*pMemory32;

	//Only supported types.
	if (Type != AllocateMaxAddress && Type != AllocateAddress)
		return EFI_INVALID_PARAMETER;

	if (Memory32 < 0xa0000) return EFI_NOT_FOUND;

	if (Type == AllocateAddress) {
		//Check memory alignment.
		if ((Memory32 & (EFI_PAGE_SIZE - 1)) != 0) return EFI_INVALID_PARAMETER;

		StartPage = (Memory32 - 0xa0000) >> 12;

		//Check for allocation range.
		if ((StartPage + NumberOfPages) > 32) return EFI_OUT_OF_RESOURCES;

		//Check if pages are free.
		for (i = StartPage; i < (StartPage + NumberOfPages); ++i)
		{
			if (ABSegPageAlloc[i] == TRUE) return EFI_OUT_OF_RESOURCES;
		}
		for(i = StartPage;  i < (StartPage + NumberOfPages); ++i)
			ABSegPageAlloc[i] = TRUE;

		return EFI_SUCCESS;
	}

	if (Memory32 < 0xa0ffe) return EFI_OUT_OF_RESOURCES;	//Max address must be whole page.

	MaxAddress = Memory32 & ~(EFI_PAGE_SIZE - 1);	//Round down to 4k alignment

	EndPage = (Memory32 - 0xa0000) >> 12;
	if (EndPage > 31) EndPage = 31;						//Max page is 31.

	//Find free pages.
	FreePageCount = (UINT8) NumberOfPages;
	for (i = 0;  i < EndPage; ++i)
	{
		UINTN j;
		if (ABSegPageAlloc[i] == TRUE)
		{
			FreePageCount = (UINT8) NumberOfPages;
			continue;	//Page allocated. Find next
		}
		if (--FreePageCount) continue;

		//Found page
		StartPage = i + 1 - NumberOfPages;
		*pMemory32 = (VOID *)((StartPage << 12) + 0xa0000);

		for (j = StartPage; j <= i; ++j) ABSegPageAlloc[j] = TRUE;

		return EFI_SUCCESS;
	}
	return EFI_OUT_OF_RESOURCES;
}

//<AMI_PHDR_START>
//---------------------------------------------------------------------------
//
// Procedure:	AllocateABSegPages
//
// Description:	Allocate SMM 4k pages of memory in A or B segment.
//
// Input: 
//  IN EFI_PHYSICAL_ADDRESS	Memory - Memory address.
//  IN UINTN				NumberOfPages
//
// Output:
//  EFI_STATUS
//
//---------------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS FreeABSegPages(
	IN EFI_PHYSICAL_ADDRESS	Memory,
	IN UINTN				NumberOfPages
)
{
	UINTN i, StartPage, EndPage;
	VOID	*Memory32 = (VOID*)(UINTN)Memory;

	if (((UINT32)(UINTN)Memory32 & (EFI_PAGE_SIZE - 1)) != 0) return EFI_INVALID_PARAMETER;

	if ((UINT32)(UINTN)Memory32 < 0xa0000) return EFI_NOT_FOUND;

	StartPage = ((UINT32)(UINTN)Memory32 - 0xa0000) >> 12;

	//Check for allocation range.
	if ((StartPage + NumberOfPages) > 32) return EFI_NOT_FOUND;

	EndPage = StartPage + NumberOfPages;

	for (i = StartPage; i < EndPage; ++i) if (ABSegPageAlloc[i] == FALSE) return EFI_NOT_FOUND;
	for (i = StartPage; i < EndPage; ++i) ABSegPageAlloc[i] = FALSE;

	return EFI_SUCCESS;
}

//<AMI_PHDR_START>
//---------------------------------------------------------------------------
//
// Procedure:	InitializeMemoryManager
//
// Description:	Initialize the memory manager, so the functions can be used.
//
// Input: VOID
//
// Output: VOID
//
//---------------------------------------------------------------------------
//<AMI_PHDR_END>

VOID InitializeMemoryManager(SMM_BASE_PRIVATE_STRUCT *Private) {
    UINT32 *pSmmBase = &Private->SmmHob->SmmBase[0];
    UINT32 NumCpus = Private->SmmHob->NumCpus;
    UINT8  i;

#if SMM_EXCLUDE_A000 == 1
    for (i = 0; i < 16; ++i) ABSegPageAlloc[i] = TRUE;
#endif    

    //Initalize Legacy memory management.
    for (i = 0; i < NumCpus; ++i) {
        if (pSmmBase[i] < 0x100000) {
            UINT8 Page = (UINT8)((pSmmBase[i] - 0x98000) / 4096);
            ASSERT(Page < 32);
            ASSERT((Page + 7) < 32);
            ABSegPageAlloc[Page] = TRUE;
            ABSegPageAlloc[Page + 7] = TRUE;
        }
    }

//If Bsp = TSEG, reserve 1 page for SMM thunk and its stack.
    if (pSmmBase[0] > 0x100000) {
#if SMM_EXCLUDE_A000 != 1
        ABSegPageAlloc[0] = TRUE;
#else
        ABSegPageAlloc[16] = TRUE;
#endif
    }

    //Initialize TSEG memory management.
	gSmmMemBase = Private->SmmAllocMemoryStart;
	gSmmMemEnd = gSmmMemBase + Private->SmmAllocMemoryLength;
	ConstructMemoryReservedTable(&gTableHead);
}

//*************************************************************************
//*************************************************************************
//**                                                                     **
//**        (C)Copyright 1985-2008, American Megatrends, Inc.            **
//**                                                                     **
//**                       All Rights Reserved.                          **
//**                                                                     **
//**      5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093           **
//**                                                                     **
//**                       Phone: (770)-246-8600                         **
//**                                                                     **
//*************************************************************************
//*************************************************************************
