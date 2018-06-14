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

//*************************************************************************
// $Header: /Alaska/SOURCE/Core/Modules/IA32Core/IA32CLib.c 14    11/11/11 3:39p Artems $
//
// $Revision: 14 $
//
// $Date: 11/11/11 3:39p $
//*************************************************************************
// Revision History
// ----------------
// $Log: /Alaska/SOURCE/Core/Modules/IA32Core/IA32CLib.c $
// 
// 14    11/11/11 3:39p Artems
// Bug fix: Verify pointer is not NULL when return value
// 
// 13    10/18/11 11:47a Yakovlevs
// [TAG]  		EIP71694 
// [Category]  	Bug Fix
// [Symptom]  	Option ROM is corrupted when copied from device on Rosecity
// Core 4.6.5.1.
// [RootCause]  	MemCpy was updated to use 8 bytes at a time. 
// PCI ROM BAR was not able to handle this type of request.
// [Solution]  	Introducesd MemCpy32 functiom.
// [Files]  		AmiLib.h; AmiX64Lib.cif; IA32CLib.c 
// MemCpy32.asm - added
// 
// 12    10/01/10 4:57p Felixp
// Most of the functions from IA32AsmLib.asm moved here
// 
// 11    11/25/09 1:55p Felixp
// 
// 10    11/24/09 5:24p Oleksiyy
// EIP 27605: Added ACPI 4.0 support. InitLongMode function modified.
// 
// 9     11/05/09 5:03p Oleksiyy
// EIP 27821 Support for 64 bit operations in IoRead and IoWrite added. 
// 
// 8     7/10/09 9:26a Felixp
// Function headers are added
// 
// 7     4/17/08 2:30p Markw
// Update InitLongMode to create pages above 32-bits.
// 
// 6     3/24/08 2:18p Markw
// Added support for pages tables above 4GB. Currently, disabled.
// 
// 5     3/18/08 2:41p Markw
// Update page table for first 2MB to have 4k pages. This is so cache
// attributes will not be different in a page.
// 
// 4     4/25/07 5:36p Felixp
// InitLongMode and EnableLongMode routines extended so support calling of
// the x64 routine with 2 parameters
// 
// 3     12/28/06 6:21p Felixp
// VC8 32-bit compiler support added
// 
// 2     10/09/06 10:09a Felixp
// Clean up
// 
// 1     8/24/06 12:54p Felixp
// 
//*************************************************************************
//<AMI_FHDR_START>
//
// Name: IA32CLib.c
//
// Description:	
//  Generic CPU library functions for the IA32 architecture.   See function
// definitions in the x64 library;  most IA32 functions have been removed
// from help builder output to fix a name collision issue.
//
//<AMI_FHDR_END>
//*************************************************************************
#include <PEI.h>
#include <AmiLib.h>
#include <Hob.h>

//*************************************************************************
// Math
//*************************************************************************

//*************************************************************************
//
// Name: Shr64
//
// Description:
//  UINT64 Shr64(IN UINT64 Value, IN UINT8 Shift) shifts the 64-bit Value
// right the provided number of bits, Shift.
//
// Input:
//  IN UINT64 Value
// The value to be shifted.
//
//  IN UINT8 Shift
// The number of bits to shift right.
//
// Output:
//  UINT64 Value shifted right Shift number of bits.
//
// Modified:
//
// Referrals:
// 
// Notes:	
// 
//*************************************************************************
UINT64 Shr64(
	IN UINT64 Value,
	IN UINT8 Shift
	)
{
	_asm {
		mov	edx, dword ptr Value[4]
		mov	eax, dword ptr Value
		mov	cl, Shift

		cmp	cl, 64
		jb	less_64
		xor	eax, eax
		xor	edx, edx
		jmp	exit
less_64:
		cmp	cl, 32			//Shift is 32 modulo
		jb less_32

		mov		eax, edx
		xor		edx, edx
less_32:
		shrd	eax, edx, cl
		shr		edx, cl
exit:
	}
}

//*************************************************************************
//
// Name: Shl64
//
// Description:
//  UINT64 Shl64(IN UINT64 Value, IN UINT8 Shift) shifts the 64-bit Value
// left the provided number of bits, Shift.
//
// Input:
//  IN UINT64 Value
// The value to be shifted left.
//
//  IN UINT8 Shift
// The number of bits to shift.
//
// Output:
//  UINT64 Value shifted left Shift number of bits.
//
// Modified:
//
// Referrals:
// 
// Notes:	
// 
//*************************************************************************
UINT64 Shl64(
	IN UINT64 Value,
	IN UINT8 Shift
	)
{
	_asm {
		mov	edx, dword ptr Value[4]
		mov	eax, dword ptr Value
		mov	cl, Shift

		cmp	cl, 64
		jb	less_64
		xor	eax, eax
		xor	edx, edx
		jmp	exit
less_64:
		cmp	cl, 32			//Shift is 32 modulo
		jb less_32

		mov		edx, eax
		xor		eax, eax
less_32:
		shld	edx, eax, cl
		shl		eax, cl
exit:
	}
}

//*************************************************************************
//
// Name: Div64
//
// Description:
//  UINT64 Div64(IN UINT64 Dividend, IN UINTN Divisor, 
// OUT UINTN *Remainder OPTIONAL) divides a 64-bit number, Dividend, by the
// Divisor, which can be up to 31-bits.
//
// Input:
//  IN UINT64 Dividend
// The 64-bit number to be divided.
//
//  IN UINT Divisor
// The number to divide Dividend by; may not exceed 31-bits in size.
//
//  OUT UINTN *Remainder OPTIONAL
// The remainder of the division.  Provide NULL if undesired; otherwise user
// is responsible for handling the necessary memory resources.
//
// Output:
//  UINT64 result of dividing Dividend by Divisor.
//
// Modified:
//
// Referrals:
// 
// Notes:	
// 
//*************************************************************************
UINT64 Div64 (
	IN UINT64	Dividend,
	IN UINTN	Divisor,	//Can only be 31 bits.
  	OUT UINTN	*Remainder OPTIONAL
  	)
{
	UINT64	Result;
  	UINT32	Rem;
 	_asm
	{
		mov		eax, dword ptr Dividend[0]
		mov		edx, dword ptr Dividend[4]
		mov		esi, Divisor
		xor		edi, edi					; Remainder
		mov		ecx, 64						; 64 bits
Div64_loop:		
      	shl     eax, 1						;Shift dividend left. This clears bit 0.
      	rcl     edx, 1    
      	rcl     edi, 1						;Shift remainder left. Bit 0 = previous dividend bit 63.

      	cmp     edi, esi					; If Rem >= Divisor, don't adjust
      	cmc                                 ; else adjust dividend and subtract divisor.
      	sbb     ebx, ebx                    ; if Rem >= Divisor, ebx = 0, else ebx = -1.
		sub		eax, ebx					; if adjust, bit 0 of dividend = 1
      	and     ebx, esi					; if adjust, ebx = Divisor, else ebx = 0. 
      	sub     edi, ebx					; if adjust, subtract divisor from remainder.
		loop	Div64_loop    	

		mov		dword ptr Result[0], eax
		mov		dword ptr Result[4], edx
		mov		Rem, edi
	}

 	if (Remainder) *Remainder = Rem;

  	return Result;
}
//*************************************************************************
//
// Name: Mul64
//
// Description:
//  UINT64 Mul64(IN UINT64 Value64, IN UINTN Value32) multiplies a 64-bit
// number by a 32-bit number and returns the 64-bit result.
//
// Input:
//  IN UINTN64 Value64
// The 64-bit number to multiply by.
//
//  IN UINTN Value32
// The 32-bit number to multiply by.
//
// Output:
//  UINT64 result of multiplying Value64 by Value32.
//
// Modified:
//
// Referrals:
// 
// Notes:	
// 
//*************************************************************************
UINT64 Mul64(
    IN UINT64   Value64,
    IN UINTN	Value32
    )
{
    UINT64      Result;

    _asm {
        mov     eax, dword ptr Value64[0]
        mul     Value32
        mov     dword ptr Result[0], eax
        mov     dword ptr Result[4], edx
        mov     eax, dword ptr Value64[4]
        mul     Value32
        add     dword ptr Result[4], eax
    }

    return Result;
}

//*************************************************************************
// Memory Operations
//*************************************************************************

//*************************************************************************
//
// Name: MemCpy
//
// Description:
//  VOID MemCpy(OUT VOID *pDestination, IN VOID *pSource, IN UINTN Count)
// copies Count bytes of memory from Source to Destination.
//
// Input:
//  OUT VOID *pDestination
// Memory address where data shall be copied.  User is responsible for
// allocating the necessary memory resources.
//
//  IN VOID *pSource
// Memory address from where data shall be copied.
//
//  IN UINTN Count
// Number of bytes to copy from pSource.
//
// Output:
//  VOID.
//
// Modified:
//
// Referrals:
// 
// Notes:	
//  This function checks for overlapping of source and destination and
// selects copy direction that prevents memory corruption.
// 
//*************************************************************************
VOID MemCpy(VOID* pDestination, VOID* pSource, UINTN Count)
{
	_asm{
//      esi, edi, ebx are saved/restores in compiler prolog/epilog code
		pushf
		mov esi, pSource
		mov edi, pDestination
		mov ecx, Count
		mov dl, 0
		mov eax, esi
		sub eax, edi
		jnb CopyForward
		lea ebx, [esi+ecx]
		neg eax
		cmp ebx, edi
		jb CopyForward
		mov esi, ebx
		lea edi, [edi+ecx]
		mov dl, 1
		std
CopyForward:
		cmp ecx, 4
		jb m8
		cmp eax, 4
		jb m8
		mov eax, esi
		mov ebx, edi
		and eax, 3
		and ebx, 3
		test dl, dl
		jz skip1
		dec esi
		dec edi
skip1:
		cmp eax, ebx
		jne m32
		test eax, eax
		jz m32
		test dl, dl
		jnz skip_nz1
		neg eax
		add eax, 4
skip_nz1:
		xchg eax, ecx
		sub eax, ecx
		rep movsb
		mov ecx, eax
m32:
		test dl, dl
		jz skip2
		sub esi, 3
		sub edi, 3
skip2:
		mov eax, ecx
		shr ecx, 2
		rep movsd
		and eax, 3
		jz end
		test dl, dl
		jz skip3
		add esi, 4
		add edi, 4
skip3:
		mov ecx, eax
m8:
		test dl, dl
		jz skip4
		dec esi
		dec edi
skip4:
		rep movsb
end:
		popf
//      esi, edi, ebx are saved/restores in compiler prolog/epilog code
	}
}

VOID MemCpy32(VOID* pDestination, VOID* pSource, UINTN Count){
    MemCpy(pDestination, pSource, Count);
}

//*************************************************************************
//<AMI_PHDR_START>
//
// Name: memcpy
//
// Description:
//  VOID memcpy(OUT VOID *pDestination, IN VOID *pSource, IN UINTN Count) is
// a wrapper for MemCpy, which copies Count bytes of memory from Source to 
// Destination.
//
// Input:
//  OUT VOID *pDestination
// Memory address where data shall be copied.  User is responsible for
// allocating the necessary memory resources.
//
//  IN VOID *pSource
// Memory address from where data shall be copied.
//
//  IN UINTN Count
// Number of bytes to copy from pSource.
//
// Output:
//  VOID.
//
// Modified:
//
// Referrals:
//  MemCpy
// 
// Notes:
//  MemCpy checks for overlapping of source and destination and selects copy 
// direction that prevents memory corruption.
// 
//<AMI_PHDR_END>
//*************************************************************************
VOID memcpy(VOID* pDestination, VOID* pSource, UINTN Count)
{
    MemCpy(pDestination,pSource,Count);
}

//*************************************************************************
//
// Name: MemSet
//
// Description:
//  VOID MemSet(IN VOID *pBuffer, IN UINTN Count, IN UINT8 Value) fills Count
// bytes of memory in pBuffer with Value.
//
// Input:
//  IN VOID *pBuffer
// The starting location in memory where to begin filling.
//
//  IN UINTN Count
// The number of bytes to fill with Value.
//
//  IN UINT8 Value
// The value to fill memory with starting at pBuffer.
//
// Output:
//  VOID.
//
// Modified:
//
// Referrals:
// 
// Notes:	
// 
//*************************************************************************
VOID MemSet(VOID* pBuffer, UINTN Count, UINT8 Value)
{
	_asm{
//      edi, ebx are saved/restores in compiler prolog/epilog code
		// fill EAX with the Value so that we can perform DWORD operatins
		mov al,Value
		mov ah, al
		mov bx,ax
		shl eax,16
		mov ax,bx
		mov edi, pBuffer
		// if Counter is less then 4, jump to byte copy
		mov ecx, Count
		cmp ecx, 4
		jb  CopyByte
		// check if the Buffer is 4-bytes aligned
		mov edx,edi
		and edx, 3
		// if the Buffer is 4-bytes aligned, jump to DWORD copy 
		jz CopyDword
		// Buffer is not 4-bytes aligned
		// Calculate 4-(Buffer%4), which is a number of bytes we have to copy before
		// Buffer will reach 4-bytes boundary, and perform byte copy
		neg edx
		add edx, 4
		xchg ecx, edx
		sub edx, ecx
		rep stosb
		mov ecx, edx
CopyDword:
		// perform DWORD copy
		mov edx, ecx
		shr ecx, 2
		rep stosd
		// copy the remainder
		and edx,3
		mov ecx, edx
CopyByte:
		rep stosb
		///
//      edi, ebx are saved/restores in compiler prolog/epilog code
	}
}

//*************************************************************************
//
// Name: memset
//
// Description:
//  VOID memset(IN VOID *pBuffer, IN UINT8 Value, IN UINTN Count) is a
// wrapper for MemSet which fills Count bytes of memory in pBuffer with
// Value.
//
// Input:
//  IN VOID *pBuffer
// The starting location in memory where to begin filling.
//
//  IN UINT8 Value
// The value to fill memory with starting at pBuffer.
//
//  IN UINTN Count
// The number of bytes to fill with Value.
//
// Output:
//  VOID.
//
// Modified:
//
// Referrals:
// 
// Notes:	
// 
//*************************************************************************
VOID memset(VOID* pBuffer, UINTN Value, UINTN Count)
{
    MemSet(pBuffer,Count,(UINT8)Value);
}
//*************************************************************************
// Debug routines
//*************************************************************************

//*************************************************************************
//
// Name: checkpoint
//
// Description:
//  VOID checkpoint(IN UINT8 c) writes the value c to port 0x80.
//
// Input:
//  IN UINT8 c
// The value/checkpoint to write to 0x80.
//
// Output:
//  VOID.
//
// Modified:
//
// Referrals:
// 
// Notes:
//  This routine should only be used if the PROGRESS_CODE or
// PEI_PROGRESS_CODE macros are unavailable.
// 
//*************************************************************************
VOID checkpoint(UINT8 c){
	_asm{
		mov al, c
		out 0x80,al
 	}
}

//*************************************************************************
//
// Name: GetCpuTimer
//
// Description:
//  UINT64 GetCpuTimer() returns the value of the CPU timer.
//
// Input:
//  None.
//
// Output:
//  UINT64 value of the CPU timer.
//
// Modified:
//
// Referrals:
// 
// Notes:	
// 
//*************************************************************************
UINT64 GetCpuTimer(){_asm rdtsc}

//*************************************************************************
// I/O Operations
//*************************************************************************

//*************************************************************************
//
// Name: IoRead8
//
// Description:
//  UINT8 IoRead8(IN UINT16 Port) reads the 8-bit value stored at the I/O
// port defined by Port.
//
// Input:
//  IN UINT16 Port
// I/O port to read 8-bits from.
//
// Output:
//  UINT8 value stored at I/O Port.
//
// Modified:
//
// Referrals:
// 
// Notes:	
// 
//*************************************************************************
UINT8 IoRead8(UINT16 Port)
{
	_asm {
		mov dx, Port
		in al, dx
	}
}

//*************************************************************************
//
// Name: IoWrite8
//
// Description:
//  VOID IoWrite8(IN UINT16 Port, IN UINT8 Value) writes the 8-bit Value to
// the I/O port defined by Port.
//
// Input:
//  IN UINT16 Port
// I/O port to write 8-bits to.
//
//  IN UINT8 Value
// 8-bits to write to the I/O Port.
//
// Output:
//  VOID.
//
// Modified:
//
// Referrals:
// 
// Notes:	
// 
//*************************************************************************
void IoWrite8(UINT16 Port,UINT8 Value)
{
	_asm {
		mov dx, Port
		mov	al, Value
		out dx, al
	}
}

//*************************************************************************
//
// Name: IoRead16
//
// Description:
//  UINT16 IoRead16(IN UINT16 Port) reads the 16-bit value stored at the I/O
// port defined by Port.
//
// Input:
//  IN UINT16 Port
// I/O port to read 16-bits from.
//
// Output:
//  UINT16 value stored at I/O Port.
//
// Modified:
//
// Referrals:
// 
// Notes:	
// 
//*************************************************************************
UINT16 IoRead16(UINT16 Port)
{
	_asm {
		mov dx, Port
		in ax, dx
	}
}

//*************************************************************************
//
// Name: IoWrite16
//
// Description:
//  VOID IoWrite16(IN UINT16 Port, IN UINT16 Value) writes the 16-bit Value
// to the I/O port defined by Port.
//
// Input:
//  IN UINT16 Port
// I/O port to write 16-bits to.
//
//  IN UINT16 Value
// 16-bits to write to the I/O Port. 
//
// Output:
//  VOID.
//
// Modified:
//
// Referrals:
// 
// Notes:	
// 
//*************************************************************************
void IoWrite16(UINT16 Port,UINT16 Value)
{
	_asm {
		mov dx, Port
		mov	ax, Value
		out dx, ax
	}
}

//*************************************************************************
//
// Name: IoRead32
//
// Description:
//  UINT32 IoRead32(IN UINT16 Port) reads the 32-bit value stored at the I/O
// port defined by Port.
//
// Input:
//  IN UINT16 Port
// I/O port to read 32-bits from.
//
// Output:
//  UINT32 value stored at I/O Port.
//
// Modified:
//
// Referrals:
// 
// Notes:	
// 
//*************************************************************************
UINT32 IoRead32(UINT16 Port)
{
	_asm {
		mov dx, Port
		in eax, dx
	}
}

//*************************************************************************
//
// Name: IoWrite32
//
// Description:
//  VOID IoWrite32(IN UINT16 Port, IN UINT32 Value) writes the 32-bit Value
// to the I/O port defined by Port.
//
// Input:
//  IN UINT16 Port
// I/O port to write 32-bits to.
//
//  IN UINT32 Value
// 32-bits to write to the I/O Port. 
//
// Output:
//  VOID.
//
// Modified:
//
// Referrals:
// 
// Notes:	
// 
//*************************************************************************
void IoWrite32(UINT16 Port,UINT32 Value)
{
	_asm {
		mov dx, Port
		mov	eax, Value
		out dx, eax
	}
}

//*************************************************************************
//
// Name: IoRead64
//
// Description:
//  UINT32 IoRead64(IN UINT16 Port) reads the 64-bit value stored at the I/O
// port defined by Port.
//
// Input:
//  IN UINT16 Port
// I/O port to read 64-bits from.
//
// Output:
//  UINT64 value stored at I/O Port.
//
// Modified:
//
// Referrals:
// 
// Notes:	
// 
//*************************************************************************
UINT64 IoRead64(UINT16 Port)
{

    UINT64      Result;
    UINT64      *Buffer = &Result;

	_asm {
        xor edx, edx
        mov dx, Port
        mov esi, Buffer
        in  eax, dx
        mov dword ptr[esi],eax
        add esi, 4
        add dx, 4
        in  eax, dx
        mov dword ptr[esi],eax
	}
    return Result;
}

//*************************************************************************
//
// Name: IoWrite64
//
// Description:
//  VOID IoWrite64(IN UINT16 Port, IN UINT64 Value) writes the 64-bit Value
// to the I/O port defined by Port.
//
// Input:
//  IN UINT16 Port
// I/O port to write 64-bits to.
//
//  IN UINT64 Value
// 64-bits to write to the I/O Port. 
//
// Output:
//  VOID.
//
// Modified:
//
// Referrals:
// 
// Notes:	
// 
//*************************************************************************
void IoWrite64(UINT16 Port, UINT64 Value)
{
//    UINT32  Lo=(UINT32)Value, Hi=(UINT32)Shr64(Value,32);
    
    VOID*   Buffer=&Value;


	_asm {
        xor edx, edx
        mov dx, Port
        mov esi, Buffer
        mov eax, dword ptr[esi]
        out dx, eax
        add esi, 4
        add dx, 4
        mov eax, dword ptr[esi]
        out dx, eax
	}
    
    

}

VOID EnableLongMode(VOID *PageTable, VOID *Function, VOID *Parameter1, VOID *Parameter2);

//*************************************************************************
//<AMI_PHDR_START>
//
// Name: InitLongModeExt
//
// Description:
//  VOID InitLongMode(IN EFI_PEI_SERVICES **PeiServices, IN VOID *Function,
// IN VOID *Parameter1, IN VOID *Parameter2) initializes memory page mapping,
// enables long mode and jumps to a provided function.
//
// Input:
//  IN EFI_PEI_SERVICES **PeiServices
// Double pointer to the PEI Services table.
//
//  IN VOID *Function
// Pointer to a function for EnableLongMode to call.
//
//  IN VOID *Parameter1
// First parameter to provide the Function to be called.
//
//  IN VOID *Parameter2
// Second parameter to provide the Function to be called.
//
// Output:
//  VOID.
//
// Modified:
//
// Referrals:
//  FindNextHobByType
//  EFI_ERROR
//  GetPageTableNumPages
//  FillPageTable
//  EnableLongMode
//  
// 
// Notes:	
// 
//<AMI_PHDR_END>
//*************************************************************************
VOID InitLongModeExt(
	IN EFI_PEI_SERVICES **PeiServices,
	IN VOID *Function,
	IN VOID *Parameter1,
	IN VOID *Parameter2,
    IN UINT8 NumMemBits
)
{
	EFI_PHYSICAL_ADDRESS PageTable;
    UINT32      NumPages;
	EFI_STATUS	Status;
//TODO: In AllocatePages below, change EfiACPIMemoryNVS to EfiBootServicesData.
//TODO: It is left as EfiACPIMemoryNVS until future projects can be updated to
//TODO: a later CPU module. Future CPU modules will allocate EfiACPIMemoryNVS
//TODO: for only 32-bits.

    NumPages = GetPageTableNumPages(NumMemBits);

	Status = (*PeiServices)->AllocatePages(
		PeiServices,
		EfiACPIMemoryNVS,
		NumPages,
		&PageTable
	);
	//ASSERT_PEI_ERROR(PeiServices,Status);

    FillPageTable(NumMemBits, (VOID*)PageTable);

	EnableLongMode((VOID*)PageTable, Function, Parameter1, Parameter2);
}
//*************************************************************************
//<AMI_PHDR_START>
//
// Name: InitLongMode
//
// Description:
//  VOID InitLongMode(IN EFI_PEI_SERVICES **PeiServices, IN VOID *Function,
// IN VOID *Parameter1, IN VOID *Parameter2) initializes memory page mapping,
// enables long mode and jumps to a provided function.
//
// Input:
//  IN EFI_PEI_SERVICES **PeiServices
// Double pointer to the PEI Services table.
//
//  IN VOID *Function
// Pointer to a function for EnableLongMode to call.
//
//  IN VOID *Parameter1
// First parameter to provide the Function to be called.
//
//  IN VOID *Parameter2
// Second parameter to provide the Function to be called.
//
// Output:
//  VOID.
//
// Modified:
//
// Referrals:
//  FindNextHobByType
//  EFI_ERROR
//  GetPageTableNumPages
//  FillPageTable
//  EnableLongMode
//  
// 
// Notes:	
// 
//<AMI_PHDR_END>
//*************************************************************************
VOID InitLongMode(
	IN EFI_PEI_SERVICES **PeiServices,
	IN VOID *Function,
	IN VOID *Parameter1,
	IN VOID *Parameter2
)
{


    UINT8       NumMemBits = 32;
    EFI_HOB_CPU *CpuHob;
    VOID        *FirstHob;
	EFI_STATUS	Status;

    (*PeiServices)->GetHobList(PeiServices, &FirstHob);
    //if (!FirstHob) ASSERT_PEI_ERROR(PeiServices, EFI_NOT_FOUND);

    CpuHob = (EFI_HOB_CPU*) FirstHob;
    Status = FindNextHobByType(EFI_HOB_TYPE_CPU, &CpuHob);

    //If error during release mode, The memory cache size will be 32-bits.
    //During debug mode, an assert will happen to alert that the CPU HOB is
    //not produced, so that all memory will not be paged.
    //ASSERT_PEI_ERROR(PeiServices, Status);

    //Find APIC ID Hob.
    if (!EFI_ERROR(Status)) {
        NumMemBits = CpuHob->SizeOfMemorySpace;
    }

    InitLongModeExt (PeiServices, Function, Parameter1, Parameter2, NumMemBits);
}

//*************************************************************************
//
// Name: GetPowerOfTwo64
//
// Description:
//  UINT64 GetPowerOfTwo64(IN UINT64 Input) returns the highest bit set in
// the provided UINT64 Input.  Equivalent to 1 << log2(x).
//
// Input:
//  IN UINT64 Input
// The 64-bit value to check for its highest bit.
//
// Output:
//  UINT64 value of the highest bit; if Input is 0, returns 0.
//
// Modified:
//
// Referrals:
// 
// Notes:	
// 
//*************************************************************************
UINT64 GetPowerOfTwo64(
  IN  UINT64  Input
)
{
	UINT64 Result = 0;
	
	if (Input > 0xffffffff) {
		_asm {
			bsr eax, dword ptr Input[4]
			bts dword ptr Result[4], eax
		}
	} else {
		_asm {
			bsr eax, dword ptr Input[0]
			bts dword ptr Result[0], eax
		}
	}
	return  Result;
}

//*************************************************************************
//
// Name: ReadMsr
//
// Description:
//  UINT64 ReadMsr(IN UINT32 Msr) reads the CPU MSR index defined by Msr and
// returns the value.
//
// Input:
//  IN UINT32 Msr
// 32-bit MSR index to be read.
//
// Output:
//  UINT64 MSR value at MSR index, Msr.
//
// Modified:
//
// Referrals:
//
// Notes:
//
//*************************************************************************
UINT64 ReadMsr(IN UINT32 Msr){
    _asm{
        mov	ecx, Msr                 ;MSR register
        rdmsr
    }
}

//*************************************************************************
//
// Name: WriteMsr
//
// Description:
//  VOID WriteMsr(IN UINT32 Msr, IN UINT64 Value) writes the Value to the
// supplied MSR index, Msr.
//
// Input:
//  IN UINT32 Msr
// 32-bit MSR index to be written to.
//
//  IN UINT64 Value
// Value to be written to MSR index.
//
// Output:
//  VOID.
//
// Modified:
//
// Referrals:
//
// Notes:
//
//*************************************************************************
VOID WriteMsr(IN UINT32 Msr, IN UINT64 Value){
    _asm{
        mov ecx, Msr					;MSR register
        mov edx, dword ptr Value[4]     ;Upper 32 bit MSR Value
        mov eax, dword ptr Value[0]     ;Lower 32 bit MSR Value
        wrmsr
    }
}
//*************************************************************************
//
// Name: CPULib_CpuID
//
// Description:
//  VOID CPULib_CpuID(IN UINT32 CpuIDIndex, IN OUT UINT32 *pRegEAX,
// IN OUT UINT32 *pRegEBX, IN OUT UINT32 *pRegECX, IN OUT UINT32 *pRegEDX)
// issues the CPUID instruction with the index provided and returns the
// register values.
//
// Input:
//  IN UINT32 CpuIDIndex
// 32-bit CPUID index.
//
//  IN OUT UINT32 *pRegEAX
// Pointer to UINT32 for EAX return value.
//
//  IN OUT UINT32 *pRegEBX
// Pointer to UINT32 for EBX return value.
//
//  IN OUT UINT32 *pRegECX
// Pointer to UINT32 for ECX return value.
//
//  IN OUT UINT32 *pRegEDX
// Pointer to UINT32 for EDX return value.
//
// Output:
//  IN OUT UINT32 *pRegEAX
// Value of EAX after CPUID instruction.
//
//  IN OUT UINT32 *pRegEBX
// Value of EBX after CPUID instruction.
//
//  IN OUT UINT32 *pRegECX
// Value of ECX after CPUID instruction.
//
//  IN OUT UINT32 *pRegEDX
// Value of EDX after CPUID instruction.
//
// Modified:
//
// Referrals:
//
// Notes:
//
//*************************************************************************
VOID CPULib_CpuID(
    IN UINT32 CpuIDIndex, 
    IN OUT UINT32 *pRegEAX, 
    IN OUT UINT32 *pRegEBX, 
    IN OUT UINT32 *pRegECX, 
    IN OUT UINT32 *pRegEDX)
{
    _asm{
        push ebx
        push ecx
        push edx
        push esi
        mov esi, pRegECX
        mov	ecx, [esi]
        mov eax, CpuIDIndex
        cpuid
        mov esi, pRegEAX
        or  esi, esi
        jz  skip1
        mov	[esi], eax
skip1:
        mov	esi, pRegEBX
        or  esi, esi
        jz  skip2
        mov	[esi], ebx
skip2:
        mov	esi, pRegECX
        or  esi, esi
        jz  skip3
        mov	[esi], ecx
skip3:
        mov	esi, pRegEDX
        or  esi, esi
        jz  skip4
        mov	[esi], edx
skip4:
        pop	esi
        pop	edx
        pop	ecx
        pop ebx
    }
}

//*************************************************************************
//
// Name: DisableCacheInCR0
//
// Description:
//  VOID DisableCacheInCR0(VOID) disables the CPU cache using the CR0 register.
//
// Input:
//  VOID.
//
// Output:
//  VOID.
//
// Modified:
//
// Referrals:
//
// Notes:
//
//*************************************************************************
VOID DisableCacheInCR0(VOID){
    _asm{
        wbinvd
        mov	eax, cr0
        or	eax, 060000000h		;SET CD, NW
        mov	cr0, eax
        wbinvd					;Invalidate cache
    }
}

//*************************************************************************
//
// Name: EnableCacheInCR0
//
// Description:
//  VOID EnableCacheInCR0(VOID) enables the CPU cache using the CR0 register.
//
// Input:
//  VOID.
//
// Output:
//  VOID.
//
// Modified:
//
// Referrals:
//
// Notes:
//
//*************************************************************************
VOID EnableCacheInCR0(VOID){
    _asm{
    // Enable cache
        mov	eax, cr0
        and	eax, 09fffffffh		;SET CD, NW
        mov	cr0, eax
        wbinvd
    }
}
//*************************************************************************
//
// Name: ReadCr3
//
// Description:
//  UINTN ReadCr3(VOID) reads the register CR3 and returns its value.
//
// Input:
//  VOID.
//
// Output:
//  Returns UINTN value stored in the CR3 register.
//
// Modified:
//
// Referrals:
//
// Notes:
//
//*************************************************************************
UINTN ReadCr3(VOID){
    _asm{
        mov     eax, cr3
    }
}
//*************************************************************************
//
// Name: WriteCr3
//
// Description:
//  VOID WriteCr3(IN UINTN CR3) writes the provided value to the CR3 register.
//
// Input:
//  IN UINTN CR3
// Value to be written to the CR3 register.
//
// Output:
//  VOID.
//
// Modified:
//
// Referrals:
//
// Notes:
//
//*************************************************************************
VOID WriteCr3(IN UINTN CR3){
    _asm{
        mov     eax, CR3 
        mov     cr3, eax
    }
}
//*************************************************************************
//
// Name: CPULib_EnableInterrupt
//
// Description:
//  VOID CPULib_EnableInterrupt(VOID) enables interrupts on the CPU.
//
// Input:
//  VOID.
//
// Output:
//  VOID.
//
// Modified:
//
// Referrals:
//
// Notes:
//
//*************************************************************************
VOID CPULib_EnableInterrupt(VOID){
    _asm{
    // Enable Interrupt
        sti
    }
}

//*************************************************************************
//
// Name: CPULib_DisableInterrupt
//
// Description:
//  VOID CPULib_DisableInterrupt() disables interrupts on the CPU.
//
// Input:
//  VOID.
//
// Output:
//  VOID.
//
// Modified:
//
// Referrals:
//
// Notes:
//
//*************************************************************************
VOID CPULib_DisableInterrupt(){
    _asm{
    // Disable Interrupt
        cli
    }
}

//*************************************************************************
//
// Name: CPULib_GetInterruptState
//
// Description:
//  BOOLEAN CPULib_GetInterruptState(VOID)returns the current CPU interrupt
// state.
//
// Input:
//  VOID.
//
// Output:
//  Returns FALSE if interrupts are disabled; otherwise TRUE.
//
// Modified:
//
// Referrals:
//
// Notes:
//
//*************************************************************************
BOOLEAN CPULib_GetInterruptState(VOID){
    _asm{
        xor	bl, bl
        pushfd			; push flags onto stack.
        pop	eax		; eax = flags.
        bt	eax,9		; IF (bit 9) if set, set carry flag.
                                    ; Interrupts are allowed if IF is set.
        adc	bl, 0		; BL = IF = CF.

        mov	al, bl		; Return value
    }
}

//*************************************************************************
//
// Name: GetCsSegment
//
// Description:
//  UINT16 GetCsSegment(VOID) retreives the value of the CS register.
//
// Input:
//  VOID.
//
// Output:
//  Returns UINT16 value of CS.
//
// Modified:
//
// Referrals:
//
// Notes:
//
//*************************************************************************
UINT16 GetCsSegment(VOID){
    _asm{
        mov ax, cs
    }
}

//*************************************************************************
//
// Name: ReadRtdsc
//
// Description:
//  UINT64 ReadRtdsc(VOID) retrieves the time stamp counter.
//
// Input:
//  VOID.
//
// Output:
//  Returns UINT64 value of the time stamp counter.
//
// Modified:
//
// Referrals:
//
// Notes:
//
//*************************************************************************
UINT64 ReadRtdsc(VOID){
    _asm{
        rdtsc
    }
}

//*************************************************************************
//
// Name: WaitForever
//
// Description:
//  VOID WaitForever(VOID) performs an infinite loop which does nothing.
//
// Input:
//  VOID.
//
// Output:
//  VOID.
//
// Modified:
//
// Referrals:
//
// Notes:
//
//*************************************************************************
VOID WaitForever(VOID){
    _asm{
    bbb:
        jmp	bbb
    }
}

//*************************************************************************
//
// Name: HltCpu
//
// Description:
//  VOID HltCpu(VOID) halts the CPU.
//
// Input:
//  VOID.
//
// Output:
//  VOID.
//
// Modified:
//
// Referrals:
//
// Notes:
//
//*************************************************************************
VOID HltCpu(VOID){
    _asm{
    bbb:
        cli
        hlt
        jmp	bbb
    }
}

//*************************************************************************
//
// Name: CPULib_Pause
//
// Description:
//  VOID CPULib_Pause(VOID) performs the pause assembly instruction.
//
// Input:
//  VOID.
//
// Output:
//  VOID.
//
// Modified:
//
// Referrals:
//
// Notes:
//
//*************************************************************************
VOID CPULib_Pause(VOID){
    _asm{
        pause
    }
}

//*************************************************************************
//
// Name: WaitForSemaphore
//
// Description:
//  VOID WaitForSemaphore(IN volatile UINT8 *Semaphore) waits for the
// semaphore to become available; once available, it claims the semaphore and
// returns.
//
// Input:
//  IN volatile UINT8 *Semaphore
// Pointer to the desired semaphore.
//
// Output:
//  VOID.
//
// Modified:
//
// Referrals:
//
// Notes:
//
//*************************************************************************
VOID WaitForSemaphore(IN volatile UINT8 *Semaphore){
    _asm{
        push ebx
        mov	al, 1
        mov ebx, Semaphore
    bbb:
        xchg al, [ebx]
        or	al, al
        pause
        jnz	bbb
        pop	ebx
    }
}

//*************************************************************************
//
// Name: WaitUntilZero8
//
// Description:
//  VOID WaitUntilZero8(IN volatile UINT8 *Value) waits until the byte stored
// at Value becomes 0, then continues.
//
// Input:
//  IN volatile UINT8 *Value
// Address of the byte value to be monitored.
//
// Output:
//  VOID.
//
// Modified:
//
// Referrals:
//
// Notes:
//
//*************************************************************************
VOID WaitUntilZero8(IN volatile UINT8 *Value){
    _asm{
        push ebx
        mov	ebx, Value
    bbb:
        mov al, [ebx]
        or	al, al
        pause
        jnz bbb
        pop	ebx
    }
}

//*************************************************************************
//
// Name: WaitUntilZero32
//
// Description:
//  VOID WaitUntilZero32(IN volatile UINT32 *Value) waits until the UINT32
// value stored at the Value address becomes 0, then continues.
//
// Input:
//  IN volatile UINT32 *Value
// Address of the UINT32 value to be monitored.
//
// Output:
//  VOID.
//
// Modified:
//
// Referrals:
//
// Notes:
//
//*************************************************************************
VOID WaitUntilZero32(IN volatile UINT32 *Value) {
    _asm{
        push ebx
        mov	ebx, Value
    bbb:
        mov eax, [ebx]
        or	eax, eax
        pause
        jnz bbb
        pop	ebx
    }
}

//*************************************************************************
//
// Name: CPULib_LockByteInc
//
// Description:
//  VOID CPULib_LockByteInc(IN UINT8 *ptr) locks the next byte after the
// address pointed to by ptr.
//
// Input:
//  IN UINT8 *ptr// Address to the byte which preceeds the desired byte to be locked.
//
// Output:
//  VOID.
//
// Modified:
//
// Referrals:
//
// Notes:
//
//*************************************************************************
VOID CPULib_LockByteInc(IN UINT8 *xptr){
    _asm{
        mov	eax, xptr
        lock inc byte ptr [eax]
    }
}

//*************************************************************************
//
// Name: CPULib_LockByteDec
//
// Description:
//  VOID CPULib_LockByteDec(IN UINT8 *ptr) locks the preceeding byte before
// the address pointed to by ptr.
//
// Input:
//  IN UINT8 *ptr
// Address to the byte which follows the desired byte to be locked.
//
// Output:
//  VOID.
//
// Modified:
//
// Referrals:
//
// Notes:
//
//*************************************************************************
VOID CPULib_LockByteDec(IN UINT8 *xptr) {
    _asm{
        mov	eax, xptr
        lock dec byte ptr [eax]
    }
}

//*************************************************************************
//
// Name: CPULib_LoadGdt
//
// Description:
//  VOID CPULib_LoadGdt(IN VOID *ptr) loads the GDT at the location pointed to
// by ptr.
//
// Input:
//  IN VOID *ptr
// Address of the GDT to be loaded.
//
// Output:
//  VOID.
//
// Modified:
//
// Referrals:
//
// Notes:
//
//*************************************************************************
VOID CPULib_LoadGdt(IN VOID *xptr) {
    _asm{
        mov	eax, xptr
        lgdt fword ptr [eax]
    }
}

//*************************************************************************
//
// Name: CPULib_SaveGdt
//
// Description:
//  VOID CPULib_SaveGdt(IN VOID *ptr) stores the loaded GDT at the location
// provided by ptr.
//
// Input:
//  IN VOID *ptr
// Address to save the GDT.  User is responsible for allocating the necessary
// memory resources.
//
// Output:
//  VOID.
//
// Modified:
//
// Referrals:
//
// Notes:
//
//*************************************************************************
VOID CPULib_SaveGdt(IN VOID *xptr) {
    _asm{
        mov	eax, xptr
        sgdt fword ptr [eax]
    }
}

//*************************************************************************
//
// Name: CPULib_LoadIdt
//
// Description:
//  VOID CPULib_LoadIdt(IN VOID *ptr) loads the IDT at the location provided
// by ptr.
//
// Input:
//  IN VOID *ptr
// Address of the IDT to be loaded.
//
// Output:
//  VOID.
//
// Modified:
//
// Referrals:
//
// Notes:
//
//*************************************************************************
VOID CPULib_LoadIdt(IN VOID *xptr) {
    _asm{
        mov	eax, xptr
        lidt fword ptr [eax]
    }
}

//*************************************************************************
//
// Name: CPULib_SaveIdt
//
// Description:
//  VOID CPULib_SaveIdt(IN VOID *ptr) stores the loaded IDT at the location
// provided by ptr.
//
// Input:
//  IN VOID *ptr
// Address to save the IDT.  User is responsible for allocating the necessary
// memory resources.
//
// Output:
//  VOID.
//
// Modified:
//
// Referrals:
//
// Notes:
//
//*************************************************************************
VOID CPULib_SaveIdt(IN VOID *xptr) {
    _asm{
        mov	eax, xptr
        sidt fword ptr [eax]
    }
}

//*************************************************************************
//
// Name: MemRead32
//
// Description:
//  UINT32 MemRead32(IN UINT32 *Address) reads and returns the 32-bit value
// stored at the user provided address.
//
// Input:
//  IN UINT32 *Address
// Address to read 32-bits from.
//
// Output:
//  UINT32 value stored at Address.
//
// Modified:
//
// Referrals:
//
// Notes:
//
//*************************************************************************
UINT32 MemRead32(IN UINT32 *Address) {
    _asm{
        push esi
        mov esi, Address		;esi = address
        mov	eax, [esi]
        pop	esi
    }
}

//*************************************************************************
//
// Name: MemReadWrite32
//
// Description:
//  VOID MemReadWrite32(IN UINT32 *Address, IN UINT32 Value, IN UINT32 Mask)
// reads the 32-bit value stored at Address, ANDs it with Mask, ORs the result
// with Value, then writes the result back to Address.
//
// Input:
//  IN UINT32 *Address
// Address which shall be read from and subsequently written to.
//
//  IN UINT32 Value
// Value to be ORed with the value stored at Address after it has been ANDed
// with the provided Mask.
//
//  IN UINT32 Mask
// Mask to be ANDed with the original value stored at Address.
//
// Output:
//  VOID.
//
// Modified:
//
// Referrals:
//
// Notes:
//
//*************************************************************************
VOID MemReadWrite32(
    IN UINT32 *Address, 
    IN UINT32 Value, 
    IN UINT32 Mask)
{
    _asm{
        push esi
        mov esi, Address		;esi = address
        mov	eax, [esi]
        and eax, Mask		;Mask
        or	eax, Value		;Value
        mov [esi], eax
        pop	esi
    }
}

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
