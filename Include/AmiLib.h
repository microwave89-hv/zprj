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
// $Header: /Alaska/BIN/Core/Include/AmiLib.h 45    6/12/12 3:22p Oleksiyy $
//
// $Revision: 45 $
//
// $Date: 6/12/12 3:22p $
//**********************************************************************
// Revision History
// ----------------
// $Log: /Alaska/BIN/Core/Include/AmiLib.h $
// 
// 45    6/12/12 3:22p Oleksiyy
// TAG]  		EIP90322
// [Category]  	Improvement
// [Description] 	Extern declaradion of gAmiGlobalVariableGuid moved to
// AmiLib.h.
// [Files]  		AmiLib.h, Misc.c, EfiLib.c, AcpiCore.c and S3Resume.c
// 
// 44    5/22/12 4:13p Oleksiyy
// [TAG]  		EIP90322
// [Category]  	Improvement
// [Description]  	Defenition of AMI Global Variable Guid is added.
// [Files]  		AmiLib.h
// 
// 43    10/17/11 2:37p Yakovlevs
// [TAG]  		EIP71694 
// [Category]  	Bug Fix
// [Symptom]  	Option ROM is corrupted when copied from device on Rosecity
// Core 4.6.5.1.
// [RootCause]  	MemCopy routine was updated to use 64 bit access but PCI
// BAR
// Copy cannot handle this.
// 
// [Solution]  	Introduced MemCpy32 routine to handle fast copy 4 byte at
// a time.
// 
// 
// [Files]  		MemCpy32.asm; AmiLib.h
// 
// 42    3/09/11 5:37p Artems
// PI 1.1 clean-up, removed duplicated and unused definitions
// 
// 41    2/05/11 1:55p Artems
// Added Intel's style LinkedList support
// 
// 40    11/10/10 5:07p Felixp
// Enhancement: MMIO_ORX, MMIO_ANDX, MMIO_ANDORX macros are added(EIP
// 46932).
// 
// 39    8/20/10 12:39p Felixp
// LZMA compression support
// 
// 38    11/05/09 3:51p Oleksiyy
// EIP 27821: Support for 64 bit operations in IoRead and IoWrite added. 
// To use this functions AmiLib.h,  IA32CLib.c, x64AsmLib.asm files should
// be updated also.
// 
// 37    7/30/09 4:43p Vyacheslava
// Fixed comments.
// 
// 36    7/28/09 4:54p Vyacheslava
// Minor bug fix. EIP#24453: Synopsis: CPU exception when printing long
// debug messages.
// 
// 35    5/21/09 6:06p Felixp
// Bit definitions (BITXX macros) are enclosed in #ifdef's to avoid
// potential double definitions.
// 
// 34    11/20/08 3:00p Felixp
// ReallocatePeImage function is upadted to properly handle virtual
// address fixups of the runtime images.
// 
// 33    5/07/08 12:21p Felixp
// Performance API added
// 
// 32    4/17/08 3:17p Markw
// Added Read/Write Cr3 and Identity map x64 page tables.
// 
// 31    3/19/08 2:24p Markw
// Add declaration GetPowerOfTwo64.
// 
// 30    9/05/07 12:21p Felixp
// GetDebugDirectory routine declarations removed (it's a private routine
// used only by PELoader).
// 
// 29    8/02/07 1:29a Felixp
// Always define GetName (used to be only when EFI_DEBUG is defined). This
// is needed to support selective debugging.
// 
// 28    7/17/07 4:57p Yakovlevs
// 
// 27    3/08/07 2:55a Felixp
// AMI specific status code definitions moved to AmiStatusCodes.h
// 
// 26    10/27/06 10:17a Felixp
// Status codes for exit boot services and set  virtual address map added
// 
// 25    10/13/06 2:53p Felixp
// AMI_STATUS_CODE_BEEP_CLASS added
// 
// 24    10/12/06 9:36a Felixp
// SectionSize parameter of FindPeSection changed from UINT32 to UINTN
// 
// 23    8/24/06 9:09a Felixp
//  - x64 support
//  - memory mapped I/O macros added
// 
// 22    6/28/06 1:01p Felixp
// 
// 21    5/21/06 11:15p Felixp
// PEI_RECOVERY_FAILED error code added
// 
// 20    5/19/06 6:19p Felixp
// Strcpy, Wcscpy changed to return pointer to the end of the string
// 
// 19    4/30/06 9:40p Felixp
// 
// 18    4/03/06 5:04p Felixp
// Headers updated in accordance with new PCI and Super I/O infrastructure
// 
// 17    3/13/06 1:15a Felixp
// 
// 16    6/07/05 7:21p Felixp
// additional macroses to work with AMI Status Code
// 
// 15    5/31/05 10:23a Felixp
// 
// 14    5/27/05 5:28p Felixp
// 
// 12    4/02/05 2:23p Felixp
// Swprintf function added
// 
// 11    4/01/05 5:51p Felixp
// CONVERT_TO_WSTRING macros added
// 
// 10    4/01/05 3:50p Felixp
// CONVERT_TO_STRING macros added
// 
// 9     3/25/05 5:25p Felixp
// Wcstol funciton added
// 
// 8     3/23/05 4:27p Markw
// 
// 7     3/23/05 4:13p Felixp
// 
// 6     3/23/05 4:12p Felixp
// 
// 5     3/21/05 11:46a Felixp
// Bit definitions moved from AmiDxeLib.h to AmiLib.h
// 
// 4     3/07/05 6:10p Felixp
// FindPeSection added
// 
// 3     2/01/05 2:27a Felixp
// 
// 2     2/01/05 2:00a Felixp
// I/O routine declarations moved from AmiDxeLib.h to AmiLib.h
// 
// 1     1/28/05 12:44p Felixp
// 
// 5     1/18/05 3:21p Felixp
// PrintDebugMessage renamed to Trace
// 
// 2     1/14/05 1:14p Felixp
// FindNextHobByGuid added
// 
// 1     12/23/04 9:41a Felixp
// 
// 27    12/15/04 9:06p Felixp
// LegacyBoot application added
// Minor build process improvements
// 
// 26    12/15/04 3:51p Markw
// Added Strstr.
// 
// 25    11/24/04 9:36a Felixp
// int64 suppot added to Itoa and Itow
// 
// 24    11/19/04 1:33a Felixp
// GetName debug routine added
// 
// 23    11/18/04 11:55a Markw
// 
// 22    11/18/04 11:51a Felixp
// FindNextHobByType declaration added
// 
// 21    11/10/04 5:17p Felixp
// 1. Definitions for StdC functions added
// 2. Definition for NameAndEntryStr added
// 
// 20    10/22/04 7:35p Felixp
// 
// 19    10/14/04 12:04p Felixp
// 
// 18    8/22/04 11:57p Felixp
// 
// 17    8/18/04 3:16p Felixp
// 
// 16    7/13/04 10:42a Felixp
// 
// 15    4/11/04 2:49p Felixp
// 
// 14    4/10/04 1:07p Felixp
// 
// 13    4/08/04 6:54p Yakovlevs
// 
// 12    4/04/04 2:58p Felixp
// 
// 11    3/30/04 11:16a Felixp
// 
// 10    3/30/04 2:48a Felixp
// 
// 9     3/29/04 6:06p Felixp
// 
// 7     3/29/04 5:05p Felixp
// 
// 6     3/29/04 4:36p Felixp
// 
// 5     3/28/04 2:11p Felixp
// 1. PE Loader and some other commonly used code moved to the Library
// 2. Warnings fixed (from now on warning will be treated as error)
// 
// 4     3/26/04 6:04p Markw
// Replaced printf with sprintf.
// 
// 3     3/26/04 3:47p Markw
// Added headers for stdlib.c.
// 
// 2     3/25/04 2:12p Markw
// Added Shr64.
// 
// 1     3/23/04 5:52p Felixp
// 
// 11    3/20/04 10:46a Felixp
// 
// 10    3/19/04 10:30a Markw
// Added GetEfiConfigurationTable.
// 
// 9     3/17/04 12:01p Markw
// Changed size_t UINTN.
// 
// 8     3/08/04 5:44p Markw
//      
// 
// 7     3/05/04 12:46p Markw
// Added Div64
// 
// 6     3/01/04 2:00p Markw
// removed FILE typedef
// 
// 5     2/26/04 3:23p Felixp
// 
// 4     2/10/04 12:54p Markw
// Fixed return type on IoWrite16 and added definition memcmp and guidcmp
// 
// 3     2/05/04 3:45p Markw
// Fixed parameter type error on IoWrite16.
// 
// 2     1/28/04 12:11p Robert
// 
// 1     1/22/04 3:15p Markw
// 
//**********************************************************************
#ifndef __AMI_LIBRARY__H__
#define __AMI_LIBRARY__H__
#ifdef __cplusplus
extern "C" {
#endif

#include <EFI.h>
#include <AmiStatusCodes.h>

//****************************************************************************/
//		TYPE DECLARATIONS
//****************************************************************************/
typedef CHAR8   *va_list;

// PE Loader                                                                */
#pragma pack(push)
#pragma pack(2)

typedef struct _FILE_HEADER { // File Header
	UINT16 Machine;
	UINT16 NumberOfSections;
	UINT32 Dummy[3];
	UINT16 OptionalHeaderSize;
	UINT16 Characteristics;
} FILE_HEADER;

typedef struct _DIRECTORY_ENTRY{ // Directory entry
	UINT32 VirtualAddress;
	UINT32 Size;
} DIRECTORY_ENTRY;

typedef struct _OPTIONAL_HEADER { // Optional header
	UINT16 Magic;
	UINT8 MajorLinkerVersion;
	UINT8 MinorLinkerVersion;
	UINT32 SizeOfCode;
	UINT32 SizeOfInitializedData;
	UINT32 SizeOfUninitializedData;
	UINT32 AddressOfEntryPoint;
	UINT32 BaseOfCode;
#if !defined(EFI64) && !defined(EFIx64)
	UINT32 BaseOfData;
#endif
	UINTN  ImageBase;
	UINT32 SectionAlignment;
	UINT32 FileAlignment;
	UINT16 MajorOperatingSystemVersion;
	UINT16 MinorOperatingSystemVersion;
	UINT16 MajorImageVersion;
	UINT16 MinorImageVersion;
	UINT16 MajorSubsystemVersion;
	UINT16 MinorSubsystemVersion;
	UINT32 Reserved;
	UINT32 SizeOfImage;
	UINT32 SizeOfHeaders;
	UINT32 CheckSum;
	UINT16 Subsystem;
	UINT16 Characteristics;
	UINTN SizeOfStackReserve;
	UINTN SizeOfStackCommit;
	UINTN SizeOfHeapReserve;
	UINTN SizeOfHeapCommit;
	UINT32 LoaderFlags;
	UINT32 NumberOfRvaAndSizes;
	DIRECTORY_ENTRY Export, Import, Resource, Exception,
				 	Certificate, Reallocations, Debug;
} OPTIONAL_HEADER;

typedef struct _DEBUG_DIRECTORY{
	UINT32 Characteristics;	//A reserved field intended to be used for flags, set to zero for now.
	UINT32 TimeDateStamp; //Time and date the debug data was created.
	UINT16 MajorVersion; //Major version number of the debug data format.
	UINT16 MinorVersion; //Minor version number of the debug data format.
	UINT32 Type; //Format of debugging information: this field enables support of multiple debuggers. See Section 6.1.2, Debug Type, for more information.
	UINT32 SizeOfData; //Size of the debug data (not including the debug directory itself).
	//TODO: Is it UINT32 for IPF ?????
	UINT32 AddressOfRawData; //Address of the debug data when loaded, relative to the image base.
	UINT32 PointerToRawData; //File pointer to the debug data.
} DEBUG_DIRECTORY;
#pragma pack(pop)

typedef enum {
	CpuIoWidthUint8,
	CpuIoWidthUint16,
	CpuIoWidthUint32,
	CpuIoWidthUint64,
	CpuIoWidthFifoUint8,
	CpuIoWidthFifoUint16,
	CpuIoWidthFifoUint32,
	CpuIoWidthFifoUint64,
	CpuIoWidthFillUint8,
	CpuIoWidthFillUint16,
	CpuIoWidthFillUint32,
	CpuIoWidthFillUint64
} CPU_IO_WIDTH;

//Decompression routine types
typedef EFI_STATUS (*GET_INFO) (
	IN VOID *Source, IN UINT32 SourceSize,
	OUT UINT32 *DestinationSize, OUT UINT32 *ScratchSize
);

typedef EFI_STATUS (*DECOMPRESS) (
	IN VOID* Source, IN UINT32 SourceSize,
	IN OUT VOID* Destination, IN UINT32 DestinationSize,
	IN OUT VOID* Scratch, IN UINT32 ScratchSize
);
// Variable Services
#define AMI_GLOBAL_VARIABLE_GUID \
    {0x1368881,0xc4ad,0x4b1d,0xb6,0x31,0xd5,0x7a,0x8e,0xc8,0xdb,0x6b}

extern EFI_GUID gAmiGlobalVariableGuid;
//****************************************************************************/
//		MACOROS DECLARATIONS
//****************************************************************************/
//Some BIT values definition for the sake of convenience
#ifndef BIT0
#define 	BIT0                0x01
#endif
#ifndef BIT1
#define 	BIT1                0x02
#endif
#ifndef BIT2
#define 	BIT2                0x04
#endif
#ifndef BIT3
#define 	BIT3                0x08
#endif
#ifndef BIT4
#define 	BIT4                0x10
#endif
#ifndef BIT5
#define 	BIT5                0x20
#endif
#ifndef BIT6
#define 	BIT6                0x40
#endif
#ifndef BIT7
#define 	BIT7                0x80
#endif
#ifndef BIT8
#define 	BIT8               0x100
#endif
#ifndef BIT9
#define 	BIT9    0x200
#endif
#ifndef BIT00
#define 	BIT00	0x00000001
#endif
#ifndef BIT01
#define 	BIT01	0x00000002
#endif
#ifndef BIT02
#define 	BIT02	0x00000004
#endif
#ifndef BIT03
#define 	BIT03	0x00000008
#endif
#ifndef BIT04
#define 	BIT04	0x00000010
#endif
#ifndef BIT05
#define 	BIT05	0x00000020
#endif
#ifndef BIT06
#define 	BIT06	0x00000040
#endif
#ifndef BIT07
#define 	BIT07	0x00000080
#endif
#ifndef BIT08
#define 	BIT08	0x00000100
#endif
#ifndef BIT09
#define 	BIT09	0x00000200
#endif
#ifndef BIT10
#define 	BIT10	0x00000400
#endif
#ifndef BIT11
#define 	BIT11	0x00000800
#endif
#ifndef BIT12
#define 	BIT12	0x00001000
#endif
#ifndef BIT13
#define 	BIT13	0x00002000
#endif
#ifndef BIT14
#define 	BIT14	0x00004000
#endif
#ifndef BIT15
#define 	BIT15	0x00008000
#endif
#ifndef BIT16
#define 	BIT16	0x00010000
#endif
#ifndef BIT17
#define 	BIT17	0x00020000
#endif
#ifndef BIT18
#define 	BIT18	0x00040000
#endif
#ifndef BIT19
#define 	BIT19	0x00080000
#endif
#ifndef BIT20
#define 	BIT20	0x00100000
#endif
#ifndef BIT21
#define 	BIT21	0x00200000
#endif
#ifndef BIT22
#define 	BIT22	0x00400000
#endif
#ifndef BIT23
#define 	BIT23	0x00800000
#endif
#ifndef BIT24
#define 	BIT24	0x01000000
#endif
#ifndef BIT25
#define 	BIT25	0x02000000
#endif
#ifndef BIT26
#define 	BIT26	0x04000000
#endif
#ifndef BIT27
#define 	BIT27	0x08000000
#endif
#ifndef BIT28
#define 	BIT28	0x10000000
#endif
#ifndef BIT29
#define 	BIT29	0x20000000
#endif
#ifndef BIT30
#define 	BIT30	0x40000000
#endif
#ifndef BIT31
#define 	BIT31	0x80000000
#endif
//=============================================================================
// This is all ANSI Standard macros pulled from stdarg.h
// Support for Variable arguments in strings
#ifndef _INTSIZEOF
#define _INTSIZEOF(n)( (sizeof(n) + sizeof(UINTN) - 1) & ~(sizeof(UINTN) - 1) )
#endif 
// Also support coding convention rules for var arg macros
#ifndef va_start
#define va_start(ap,v)  ( ap = (va_list)&(v) + _INTSIZEOF(v) )
#endif
#define va_arg(ap,t)    ( *(t *)((ap += _INTSIZEOF(t)) - _INTSIZEOF(t)) )
#define va_end(ap)      ( ap = (va_list)0 )
// end variable argument support
//=============================================================================
#define ___INTERNAL_CONVERT_TO_STRING___(a) #a
#define CONVERT_TO_STRING(a) ___INTERNAL_CONVERT_TO_STRING___(a)
#define ___INTERNAL_CONVERT_TO_WSTRING___(a) L#a
#define CONVERT_TO_WSTRING(a) ___INTERNAL_CONVERT_TO_WSTRING___(a)

#define guidcmp(g1,g2) MemCmp(g1,g2,sizeof(EFI_GUID))

// The EFI memory allocation functions work in units of EFI_PAGEs that are
// 4K. This should in no way be confused with the page size of the processor.
// An EFI_PAGE is just the quanta of memory in EFI.
#define EFI_PAGE_MASK   (EFI_PAGE_SIZE - 1)
#define EFI_PAGE_SHIFT  12

#define EFI_SIZE_TO_PAGES(s)  \
    ( (((UINTN)(s)) >> EFI_PAGE_SHIFT) + ((((UINTN)(s)) & EFI_PAGE_MASK) ? 1 : 0) )

#define EFI_PAGES_TO_SIZE(p)   ( ((UINTN)(p)) << EFI_PAGE_SHIFT)
//FIELD_OFFSET - returns the byte offset to a field within a structure
#define EFI_FIELD_OFFSET(TYPE,Field) ((UINTN)(&(((TYPE *) 0)->Field)))

//returns the field size within a structure
#define EFI_FIELD_SIZE(TYPE,Field) (sizeof((((TYPE *) 0)->Field)))
#define OUTTER(pField, Field, OutterType) ((OutterType*)((UINT8*)(pField)-EFI_FIELD_OFFSET(OutterType,Field)))

#define Itoa(value,string,radix) ItoaEx((INT32)value,string,radix,FALSE)
#define Itow(value,string,radix) ItowEx((INT32)value,string,radix,FALSE)
#define I64toa(value,string,radix) ItoaEx(value,string,radix,TRUE)
#define I64tow(value,string,radix) ItowEx(value,string,radix,TRUE)

#define Strtol(nptr,endptr,base) StrtolEx(nptr,endptr,base,1)
#define Wcstol(nptr,endptr,base) StrtolEx((char*)nptr,(char**)endptr,base,2)

//Debug Message Categories
#define TRACE_NEVER 0 // never displayed
#define TRACE_ALWAYS -1 // always displayed
#define TRACE_PEICORE 1
#define TRACE_DXEIPL 2
#define TRACE_PEI_CHIPSET 4
#define TRACE_PEI_PLATFORM 8
#define TRACE_PEI_CPU 0x10
#define TRACE_DXE_CORE 0x20
#define TRACE_DXE_CHIPSET 0x40
#define TRACE_DXE_PLATFORM 0x80
#define TRACE_DXE_CPU 0x100
#define TRACE_CSM 0x200
#define TRACE_USB 0x400

#define EFI_DEADLOOP() { volatile UINTN __DeadLoopVar__ = 1; while (__DeadLoopVar__); }

#define MMIO_READ8(Address) (*(volatile UINT8*)(Address))
#define MMIO_WRITE8(Address,Value) (*(volatile UINT8*)(Address)=(Value))
#define MMIO_READ16(Address) (*(volatile UINT16*)(Address))
#define MMIO_WRITE16(Address,Value) (*(volatile UINT16*)(Address)=(Value))
#define MMIO_READ32(Address) (*(volatile UINT32*)(Address))
#define MMIO_WRITE32(Address,Value) (*(volatile UINT32*)(Address)=(Value))
#define MMIO_READ64(Address) (*(volatile UINT64*)(Address))
#define MMIO_WRITE64(Address,Value) (*(volatile UINT64*)(Address)=(Value))

#define MMIO_OR8(Address, Value)  (*(volatile UINT8*)(Address) |= (Value))
#define MMIO_OR16(Address, Value) (*(volatile UINT16*)(Address) |= (Value))
#define MMIO_OR32(Address, Value) (*(volatile UINT32*)(Address) |= (Value))
#define MMIO_OR64(Address, Value) (*(volatile UINT64*)(Address) |= (Value))

#define MMIO_AND8(Address, Value)  (*(volatile UINT8*)(Address) &= (Value))
#define MMIO_AND16(Address, Value) (*(volatile UINT16*)(Address) &= (Value))
#define MMIO_AND32(Address, Value) (*(volatile UINT32*)(Address) &= (Value))
#define MMIO_AND64(Address, Value) (*(volatile UINT64*)(Address) &= (Value))

#define MMIO_ANDOR8(Address, AndData, OrData)   (*(volatile UINT8*)(Address))  = (*(volatile UINT8*)(Address)  & (AndData) | (OrData))
#define MMIO_ANDOR16(Address, AndData, OrData)  (*(volatile UINT16*)(Address)) = (*(volatile UINT16*)(Address) & (AndData) | (OrData))
#define MMIO_ANDOR32(Address, AndData, OrData)  (*(volatile UINT32*)(Address)) = (*(volatile UINT32*)(Address) & (AndData) | (OrData))
#define MMIO_ANDOR64(Address, AndData, OrData)  (*(volatile UINT64*)(Address)) = (*(volatile UINT32*)(Address) & (AndData) | (OrData))

#define DXE_TOK L"DXE"
#define SHELL_TOK L"SHELL"
#define PEI_TOK L"PEI"
#define BDS_TOK L"BDS"
#define DRIVERBINDING_START_TOK L"DriverBinding:Start"
#define DRIVERBINDING_SUPPORT_TOK L"DriverBinding:Support"
#define START_IMAGE_TOK L"StartImage"
#define LOAD_IMAGE_TOK L"LoadImage"
#define DXEIPL_TOK L"DXEIPL"
#define PCI_TOK L"PCI"
#define CSM_TOK L"CSM"
#define NVRAM_TOK L"NVRAM"
#define S3RESUME_TOK L"S3RESUME"

//****************************************************************************/
//		VARIABLE DECLARATIONS
//****************************************************************************/

//****************************************************************************/
//		FUNCTION DECLARATIONS
//****************************************************************************/
UINTN Sprintf_va_list( char *buffer, char *format, va_list arg );
UINTN Sprintf(char *Buffer, char *Format, ...);
UINTN Sprintf_s(char *Buffer, UINTN BufferSize, char *Format, ...);
UINTN Sprintf_s_va_list(char *Buffer, UINTN BufferSize, char *Format, va_list Marker);
UINTN Swprintf_va_list(CHAR16 *buffer, CHAR16 *format, va_list arg);
UINTN Swprintf(CHAR16 *Buffer, CHAR16 *Format, ...);
UINTN Swprintf_s(CHAR16 *Buffer, UINTN BufferSize, CHAR16 *Format, ...);
UINTN Swprintf_s_va_list(CHAR16 *Buffer, UINTN BufferSize, CHAR16 *Format, va_list Marker);
int Atoi( char *string );
char * ItoaEx(INT64 value, char *string,int radix, BOOLEAN is_int64);
CHAR16 * ItowEx(INT64 value, CHAR16 *string,int radix, BOOLEAN is_int64);
long StrtolEx(char *nptr,char **endptr,int base, int increment);
int Strcmp(char *string1, char *string2);
int Wcscmp(CHAR16 *string1, CHAR16 *string2);
UINTN Strlen(char *);
UINTN Wcslen(CHAR16 *);
char* Strcpy(char *,char *);
CHAR16* Wcscpy(CHAR16 *,CHAR16 *);
char *Strstr(const char *,const char *);
char * Strupr(char *str);
CHAR16 * Wcsupr(CHAR16 *str);

/*
int tolower(int);
int toupper(int);
char * strupr(char *str);
char *strcpy(char *,char *);
char *strcat(char *,char *);
CHAR16 *wcscat(CHAR16 *,CHAR16 *);
*/

VOID MemCpy(VOID* pDestination, VOID* pSource, UINTN Length);
VOID MemCpy32(VOID* pDestination, VOID* pSource, UINTN Length);
void MemSet(VOID* pBuffer, UINTN Size, UINT8 Value);
INTN MemCmp(VOID* pDestination, VOID* pSource, UINTN Length);

UINT64 Shr64( IN UINT64 Value, IN UINT8 Shift );
UINT64 Shl64( IN UINT64 Value, IN UINT8 Shift );

UINT64 Div64 (
	IN UINT64	Dividend,
	IN UINTN	Divisor,	//Can only be 31 bits for IA-32
  	OUT UINTN	*Remainder OPTIONAL
);

UINT64 Mul64(
	IN UINT64   Value64,
	IN UINTN	Value32
);

UINT64 GetPowerOfTwo64(
  IN  UINT64  Input
);


// PE Loader
BOOLEAN ReallocatePeImage(UINT8 *pcurrent, UINT8 *pnew, UINT8 *prealloc);
BOOLEAN IsPeImageValid(UINT8* pstart);
UINT32 GetImageSize(VOID *p);
OPTIONAL_HEADER* GetPeOptionalHeader(VOID *p);
VOID* LoadPeImage(UINT8* pold, UINT8* pnew);
VOID* LoadPeImageEx(UINT8* pold, UINT8* pnew, UINT8 *prealloc);
VOID* FindPeSection(UINT8* pstart, UINT64 name, UINTN* pSize);
BOOLEAN GetName(UINT8 *p, CHAR8 *sName);

//Decompression
// Standard UEFI Decompression
EFI_STATUS GetInfo (
	IN VOID *Source, IN UINT32 SourceSize,
	OUT UINT32 *DestinationSize, OUT UINT32 *ScratchSize
);

EFI_STATUS Decompress (
	IN VOID* Source, IN UINT32 SourceSize,
	IN OUT VOID* Destination, IN UINT32 DestinationSize,
	IN OUT VOID* Scratch, IN UINT32 ScratchSize
);

// LZMA Decompression
EFI_STATUS LzmaGetInfo (
	IN VOID *Source, IN UINT32 SourceSize,
	OUT UINT32 *DestinationSize, OUT UINT32 *ScratchSize
);

EFI_STATUS LzmaDecompress (
	IN VOID* Source, IN UINT32 SourceSize,
	IN OUT VOID* Destination, IN UINT32 DestinationSize,
	IN OUT VOID* Scratch, IN UINT32 ScratchSize
);

//Defined in Tokens.c
BOOLEAN GetDecompressInterface(
    UINT8 CompressionType, GET_INFO *GetInfoPtr, DECOMPRESS *DecompressPtr
);

// DEBUG
VOID checkpoint(UINT8 c);
UINT64 GetCpuTimer();
VOID PrepareStatusCodeString(VOID* pBuffer, UINTN Size, CHAR8 *sFormat, va_list ArgList);

//HOB
EFI_STATUS FindNextHobByType(IN UINT16   Type,IN OUT VOID **Hob);
EFI_STATUS FindNextHobByGuid(IN EFI_GUID *Guid, IN OUT VOID **Hob);

UINT8 IoRead8(UINT16 Port);
VOID IoWrite8(UINT16 Port, UINT8 Value);
UINT16 IoRead16(UINT16 Port);
VOID IoWrite16(UINT16 Port, UINT16 Value);
UINT32 IoRead32(UINT16 Port);
VOID IoWrite32(UINT16 Port, UINT32 Value);
UINT64 IoRead64(UINT16 Port);
VOID IoWrite64(UINT16 Port, UINT64 Value);

EFI_STATUS IoRead(
	IN CPU_IO_WIDTH	Width,
	IN UINT64		Address,
	IN UINTN		Count,
	IN VOID			*Buffer
);

EFI_STATUS IoWrite(
	IN CPU_IO_WIDTH	Width,
	IN UINT64		Address,
	IN UINTN		Count,
	OUT VOID		*Buffer
);

EFI_STATUS IoReadWrite(
	IN CPU_IO_WIDTH	Width,
	IN UINT64		Address,
	IN VOID			*DataValue,
	IN VOID			*DataMask
);

EFI_STATUS MemRead(
	IN CPU_IO_WIDTH	Width,
	IN UINT64		Address,
	IN UINTN		Count,
	IN VOID			*Buffer
);

EFI_STATUS MemWrite(
	IN CPU_IO_WIDTH	Width,
	IN UINT64		Address,
	IN UINTN		Count,
	OUT VOID		*Buffer
);

EFI_STATUS MemReadWrite(
	IN CPU_IO_WIDTH	Width,
	IN UINT64		Address,
	IN VOID			*DataValue,
	IN VOID			*DataMask
);

typedef	struct _IO_DATA{
	UINT16 			Addr;
	CPU_IO_WIDTH	Width;	
	UINT32 			Data;
} IO_DATA;

//IO Init table execution function
EFI_STATUS ExecScript(IO_DATA *ScriptData, UINTN EntryCount);


UINTN ReadCr3(VOID);
VOID WriteCr3(UINTN Value);

UINT32 GetPageTableNumPages(
    IN UINT8 NumberMemoryBits
);

VOID FillPageTable(
    IN UINT8  NumberMemoryBits,
    IN VOID   *PageTable
);

//Linked List

//
// Prevent multiple includes in the same source file
//

#ifndef EFI_LIST_ENTRY_DEFINED
#define EFI_LIST_ENTRY_DEFINED
typedef struct _EFI_LIST_ENTRY {
  struct _EFI_LIST_ENTRY  *ForwardLink;
  struct _EFI_LIST_ENTRY  *BackLink;
} EFI_LIST_ENTRY;
//*** AMI PORTING BEGIN ***//
#endif
//*** AMI PORTING END *****//

typedef EFI_LIST_ENTRY EFI_LIST;      
typedef EFI_LIST_ENTRY EFI_LIST_NODE;

#define INITIALIZE_LIST_HEAD_VARIABLE(ListHead)  {&ListHead, &ListHead}

VOID
InitializeListHead (
  EFI_LIST_ENTRY       *List
  )
/*++

Routine Description:

  Initialize the head of the List.  The caller must allocate the memory 
  for the EFI_LIST. This function must be called before the other linked
  list macros can be used.
    
Arguments:

  List - Pointer to list head to initialize
   
Returns:

  None.

--*/
;

BOOLEAN
IsListEmpty (
  EFI_LIST_ENTRY  *List
  )
/*++

Routine Description:

  Return TRUE is the list contains zero nodes. Otherzise return FALSE.
  The list must have been initialized with InitializeListHead () before using 
  this function.
    
Arguments:

  List - Pointer to list head to test

   
Returns:

  Return TRUE is the list contains zero nodes. Otherzise return FALSE.

--*/
;

VOID
RemoveEntryList (
  EFI_LIST_ENTRY  *Entry
  )
/*++

Routine Description:

  Remove Node from the doubly linked list. It is the caller's responsibility
  to free any memory used by the entry if needed. The list must have been 
  initialized with InitializeListHead () before using this function.
    
Arguments:

  Entry - Element to remove from the list.
   
Returns:
  
  None

--*/
;

VOID
InsertTailList (
  EFI_LIST_ENTRY  *ListHead,
  EFI_LIST_ENTRY  *Entry
  )
/*++

Routine Description:

  Insert a Node into the end of a doubly linked list. The list must have 
  been initialized with InitializeListHead () before using this function.
    
Arguments:

  ListHead - Head of doubly linked list

  Entry    - Element to insert at the end of the list.
   
Returns:
  
  None

--*/
;

VOID
InsertHeadList (
  EFI_LIST_ENTRY  *ListHead,
  EFI_LIST_ENTRY  *Entry
  )
/*++

Routine Description:

  Insert a Node into the start of a doubly linked list. The list must have 
  been initialized with InitializeListHead () before using this function.
    
Arguments:

  ListHead - Head of doubly linked list

  Entry    - Element to insert to beginning of list
   
Returns:
  
  None

--*/
;

VOID
SwapListEntries (
  EFI_LIST_ENTRY  *Entry1,
  EFI_LIST_ENTRY  *Entry2
  )
/*++

Routine Description:

  Swap the location of the two elements of a doubly linked list. Node2 
  is placed in front of Node1. The list must have been initialized with 
  InitializeListHead () before using this function.
    
Arguments:

  Entry1 - Element in the doubly linked list in front of Node2. 

  Entry2 - Element in the doubly linked list behind Node1.
   
Returns:
  
  None

--*/
;

EFI_LIST_ENTRY *
GetFirstNode (
  EFI_LIST_ENTRY  *List 
  )
/*++

Routine Description:

  Return the first node pointed to by the list head.  The list must 
  have been initialized with InitializeListHead () before using this 
  function and must contain data.
    
Arguments:

  List - The head of the doubly linked list.
   
Returns:
  
  Pointer to the first node, if the list contains nodes.  The list will
  return a null value--that is, the value of List--when the list is empty.
    See the description of IsNull for more information.


--*/
;

EFI_LIST_ENTRY *
GetNextNode (
  EFI_LIST_ENTRY  *List,
  EFI_LIST_ENTRY  *Node
  )
/*++

Routine Description:

  Returns the node following Node in the list. The list must 
  have been initialized with InitializeListHead () before using this 
  function and must contain data.
    
Arguments:

  List - The head of the list.  MUST NOT be the literal value NULL.
  Node - The node in the list.  This value MUST NOT be the literal value NULL.
    See the description of IsNull for more information.
   
Returns:
  
  Pointer to the next node, if one exists.  Otherwise, returns a null value,
  which is actually a pointer to List.
    See the description of IsNull for more information.

--*/
;

BOOLEAN 
IsNull ( 
  EFI_LIST_ENTRY  *List,
  EFI_LIST_ENTRY  *Node 
  )
/*++

Routine Description:

  Determines whether the given node is null.  Note that Node is null
  when its value is equal to the value of List.  It is an error for
  Node to be the literal value NULL [(VOID*)0x0].

Arguments:

  List - The head of the list.  MUST NOT be the literal value NULL.
  Node - The node to test.  MUST NOT be the literal value NULL.  See
    the description above.
   
Returns:
  
  Returns true if the node is null.

--*/
;

BOOLEAN 
IsNodeAtEnd ( 
  EFI_LIST_ENTRY  *List, 
  EFI_LIST_ENTRY  *Node 
  )
/*++

Routine Description:

  Determines whether the given node is at the end of the list.  Used
  to walk the list.  The list must have been initialized with 
  InitializeListHead () before using this function and must contain 
  data.

Arguments:

  List - The head of the list.  MUST NOT be the literal value NULL.
  Node - The node to test.  MUST NOT be the literal value NULL.
    See the description of IsNull for more information.
   
Returns:
  
  Returns true if the list is the tail.

--*/
;

/****** DO NOT WRITE BELOW THIS LINE *******/
#ifdef __cplusplus
}
#endif
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
