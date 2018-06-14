//*************************************************************************
//*************************************************************************
//**                                                                     **
//**        (C)Copyright 1985-2009, American Megatrends, Inc.            **
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
// $Header: /Alaska/Projects/Intel/Haswell/LynxPoint_SharkBay-DT_Crb_1AQQW/Library/PeiLib.c 1     4/16/14 3:10a Chaseliu $
//
// $Revision: 1 $
//
// $Date: 4/16/14 3:10a $
//*************************************************************************
// Revision History
// ----------------
// $Log: /Alaska/Projects/Intel/Haswell/LynxPoint_SharkBay-DT_Crb_1AQQW/Library/PeiLib.c $
// 
// 1     4/16/14 3:10a Chaseliu
// [TAG]           EIP163569
// [Category]      Improvement
// [Description]   Update for support 2014 BIOS Security Disclosures.
// [Files]
// Library\PeiLib.c
// Library\EfiLib.c
// Core\EM\NVRAM\NVRAMDXE.c
// Core\EM\Capsule2_0\Capsule2_0.c
// Core\CORE_DXE\FwVolBlock.c
// 
// 29    2/28/14 5:41p Artems
// EIP 154195 Fixed vulnerability where memory pointer was stored in NVRaM
// and may be compromised
// 
// 27    8/12/11 12:25p Artems
// EIP 64107: Added changes for module to be compliant with PI
// specification v 1.2
// 
// 26    5/27/11 5:59p Felixp
// PeiGetNextVariableName is updated:
// The GetNextVariableName function has been renamed to NextVariableName
// to comply with the specification.
// 
// 25    2/05/11 3:14p Artems
// Added compatibility functions to work in both PI 0.91 and PI 1.0
// versions
// 
// 24    11/05/10 2:47p Artems
// EIP 44635 - removed commented out string
// 
// 23    10/12/10 5:15p Artems
// EIP 44635  Added token MAX_PEI_PERF_LOG_ENTRIES
// 
// 22    11/25/09 1:32p Felixp
// PeiTrace functions is updated to suppress Trace message 
// if message Level defined by the first parameter is disabled using
// TRACE_LEVEL_MASK SDL token.
// 
// 21    7/30/09 4:45p Vyacheslava
// Fixed comments.
// 
// 20    7/28/09 4:55p Vyacheslava
// Minor bug fix. EIP#24453: Synopsis: CPU exception when printing long
// debug messages.
// 
// 19    7/10/09 3:49p Felixp
// Function headers added
// 
// 18    6/06/08 10:54a Felixp
// SaveS3PerformanceData routine added
// 
// 17    5/07/08 12:22p Felixp
// Performance API added
// 
// 16    10/22/07 6:24p Felixp
// FindFfsFileByName routine added.
// 
// 15    8/30/07 11:01p Felixp
// PeiGetVariable and PeiGetNextVariableName routines added.
// 
// 14    3/13/07 1:40a Felixp
// 
// 13    8/24/06 9:27a Felixp
// Preliminary x64 support (work in progress)
// 
// 12    3/13/06 1:50a Felixp
// 
// 11    12/09/05 2:08p Felixp
// 
// 10    10/11/05 2:43p Felixp
// 
// 9     10/09/05 8:52p Felixp
// 
// 8     10/09/05 4:54p Felixp
// 
// 7     10/09/05 4:14p Felixp
// 
// 6     10/09/05 11:27a Felixp
// Support for performance measurements added.
// 
// 5     6/16/05 10:48a Felixp
// CreateLoadHob function added (used by PEIMs to reguest reallocation to
// RAM,
// once memory is detected)
// 
// 3     1/18/05 3:22p Felixp
// PrintDebugMessage renamed to Trace
// 
// 1     12/23/04 9:42a Felixp
// 
// 2     11/10/04 5:16p Felixp
// Level parameter added to PeiTrace fucntion
// 
// 1     11/02/04 5:30p Felixp
// 
//*************************************************************************
//<AMI_FHDR_START>
//
// Name: PeiLib.c
//
// Description:	
//  Contains an assortment of localized PEI library functions.
//
//<AMI_FHDR_END>
//*************************************************************************

#include <Token.h>
#include <AmiPeiLib.h>
#include <StatusCodes.h>
#include <AmiHobs.h>
#include <PPI/ReadOnlyVariable2.h>
#include <PPI/LoadFile.h>
#include <Protocol/Performance.h>

//*************************************************************************
//<AMI_PHDR_START>
//
// Name: PeiTrace
//
// Description:	
//  VOID PeiTrace(IN UINTN Level, IN EFI_PEI_SERVICES **ppPS,
// IN CHAR8 *sFormat, IN ...) prints a debug message using the
// ReportStatusCode from PEI Services if the specified error level is
// enabled.
//
// Input:
//  IN UINTN Level
// The error level of the debug message.
//
//  IN EFI_PEI_SERVICES **ppPS
// Double pointer to PEI Services Table.
//
//  IN CHAR8 *sFormat
// Format string for the debug message to print.
//
//  IN ...
// Additional parameters utilized by the format string.
//
// Output:
//  VOID.
//
// Modified:
//
// Referrals:
//  PrepareStatusCodeString
//  va_start
//  va_end
//  PEI_TRACE
//  Sprintf
// 
// Notes:
//  Use the PEI_TRACE macro for debug messages in PEI!  This allows the
// DEBUG_MODE token to control the inclusion of debug messages.  See 
// Sprintf function for format string syntax.
//          
//<AMI_PHDR_END>
//*************************************************************************

VOID PeiTrace(UINTN Level, CONST EFI_PEI_SERVICES **ppPS, CHAR8 *sFormat,...)
{
	CHAR8  Buffer[256];
    extern const UINT32 TraceLevelMask;
	va_list	ArgList;
    if ( (Level & TraceLevelMask) == 0 ) return;
	ArgList = va_start(ArgList,sFormat);
	PrepareStatusCodeString( Buffer, sizeof(Buffer), sFormat, ArgList );
	(*ppPS)->ReportStatusCode (
		(EFI_PEI_SERVICES**)ppPS, EFI_DEBUG_CODE, 
		EFI_SOFTWARE_UNSPECIFIED, 0, NULL,
		(EFI_STATUS_CODE_DATA *)Buffer
	);
	va_end(ArgList);
}

//*************************************************************************
//<AMI_PHDR_START>
//
// Name: CreateHobMemoryAllocationModule
//
// Description:	
//  EFI_STATUS CreateHobMemoryAllocationModule(
// IN EFI_PEI_SERVICES **PeiServices,
// IN EFI_PHYSICAL_ADDRESS MemoryBaseAddress, IN UINT64 MemoryLength,
// IN EFI_MEMORY_TYPE MemoryType, IN EFI_GUID *ModuleName, 
// IN EFI_PHYSICAL_ADDRESS EntryPoint) adds a memory allocation HOB with a 
// memory allocation module GUID using CreateHob from PEI Services.
//
// Input:
//  IN EFI_PEI_SERVICES **PeiServices
// Double pointer to PEI Services Table.
//
//  IN EFI_PHYSICAL_ADDRESS MemoryBaseAddress 
// The physical address of the module.
//
//  IN UINT64 MemoryLength
// The length of the module in bytes.
//
//  IN EFI_MEMORY_TYPE MemoryType
// Module memory type.
//
//  IN EFI_GUID *ModuleName 
// The GUID File Name of the module.
//
//  IN EFI_PHYSICAL_ADDRESS EntryPoint
// The 64-bit physical address of the module's entry point.
//
// Output:
//  EFI_INVALID_PARAMETER, if Hob = NULL.
//  EFI_OUT_OF_RESOURCES,  if there is not enough space to create HOB.
//  Otherwise, EFI_SUCCESS.
//
// Modified:
//
// Referrals:
// 
// Notes:	
//          
//<AMI_PHDR_END>
//*************************************************************************
EFI_STATUS CreateHobMemoryAllocationModule(
	IN EFI_PEI_SERVICES **PeiServices,
    IN EFI_PHYSICAL_ADDRESS MemoryBaseAddress,
    IN UINT64 MemoryLength, IN EFI_MEMORY_TYPE MemoryType,
    IN EFI_GUID *ModuleName,
    IN EFI_PHYSICAL_ADDRESS EntryPoint
)
{
	static EFI_GUID gHobMemAllocModGuid=EFI_HOB_MEMORY_ALLOC_MODULE_GUID;
    EFI_STATUS Status;
    EFI_HOB_MEMORY_ALLOCATION_MODULE *MemAllocModHob;

    Status = (*PeiServices)->CreateHob(
        PeiServices,
        EFI_HOB_TYPE_MEMORY_ALLOCATION,
        sizeof(EFI_HOB_MEMORY_ALLOCATION_MODULE),
        &MemAllocModHob);
    if (Status != EFI_SUCCESS) return Status;
    MemAllocModHob->MemoryAllocationHeader.Name=gHobMemAllocModGuid;
    MemAllocModHob->MemoryAllocationHeader.MemoryBaseAddress=MemoryBaseAddress;
    MemAllocModHob->MemoryAllocationHeader.MemoryLength=MemoryLength;
    MemAllocModHob->MemoryAllocationHeader.MemoryType=MemoryType;
    *(UINT32*)&MemAllocModHob->MemoryAllocationHeader.Reserved=0;
    MemAllocModHob->ModuleName=*ModuleName;
    MemAllocModHob->EntryPoint=EntryPoint;
    return EFI_SUCCESS;
}

//*************************************************************************
//<AMI_PHDR_START>
//
// Name: CreateHobResourceDescriptor
//
// Description:	
//  EFI_STATUS CreateHobResourceDescriptor(IN EFI_PEI_SERVICES **PeiServices,
// IN EFI_GUID *Owner, IN EFI_RESOURCE_TYPE ResourceType, 
// IN EFI_RESOURCE_ATTRIBUTE_TYPE ResourceAttribute, 
// IN EFI_PHYSICAL_ADDRESS PhysicalStart, IN UINT64 ResourceLength) builds a
// resource descriptor HOB that describes a chunk of system memory using 
// CreateHob from PEI Services.
//
// Input:
//  IN EFI_PEI_SERVICES **PeiServices
// Double pointer to the PEI Services Table.
//
//  IN EFI_GUID *Owner
// GUID of the owner of this resource.  Make this NULL if there is none.
//
//  IN EFI_RESOURCE_TYPE ResourceType
// The type of resource described by this HOB.
//
//  IN EFI_RESOURCE_ATTRIBUTE_TYPE ResourceAttribute
// The resource attributes of the memory described by this HOB.
//
//  IN EFI_PHYSICAL_ADDRESS PhysicalStart
// The 64-bit physical address of memory described by this HOB.
//
//  IN UINT64 ResourceLength
// The length of the memory described by this HOB in bytes.
//
// Output:
//  EFI_INVALID_PARAMETER, if HOB = NULL.
//  EFI_OUT_OF_RESOURCES,  if there is not enough space to create HOB.
//  Otherwise, EFI_SUCCESS.
//
// Modified:
//
// Referrals:
// 
// Notes:	
//          
//<AMI_PHDR_END>
//*************************************************************************
EFI_STATUS CreateHobResourceDescriptor
(
	IN EFI_PEI_SERVICES **PeiServices,
    IN EFI_GUID *Owner, IN EFI_RESOURCE_TYPE ResourceType,
    IN EFI_RESOURCE_ATTRIBUTE_TYPE ResourceAttribute,
    IN EFI_PHYSICAL_ADDRESS PhysicalStart,
    IN UINT64 ResourceLength
)
{
    EFI_STATUS Status;
    EFI_HOB_RESOURCE_DESCRIPTOR *ResHob;

    Status = (*PeiServices)->CreateHob(
        PeiServices,
        EFI_HOB_TYPE_RESOURCE_DESCRIPTOR,
        sizeof(EFI_HOB_RESOURCE_DESCRIPTOR),
        &ResHob);
    if (Status != EFI_SUCCESS) return Status;

    ResHob->Owner=*Owner;
    ResHob->ResourceType=ResourceType;
    ResHob->ResourceAttribute=ResourceAttribute;
    ResHob->PhysicalStart=PhysicalStart;
    ResHob->ResourceLength=ResourceLength;
    return EFI_SUCCESS;
}

//*************************************************************************
//<AMI_PHDR_START>
//
// Name: CreateLoadHob
//
// Description:	
//  EFI_STATUS CreateLoadHob(IN EFI_PEI_SERVICES **ppPS,
// IN EFI_FFS_FILE_HEADER *pFfsHeader, EFI_PEIM_ENTRY_POINT EntryPoint, 
// EFI_PEIM_ENTRY_POINT InMemEntryPoint) builds a EFI_HOB_TYPE_GUID_EXTENSION
// HOB with a PEIM load HOB.
//
// Input:
//	IN EFI_PEI_SERVICES **ppPS
// Double pointer to the PEI Services Table.
//
//  IN EFI_FFS_FILE_HEADER *pFfsHeader
// Pointer to the desired FFS header.
//
//  EFI_PEIM_ENTRY_POINT EntryPoint
// Pointer to the FFS entry point.
//
//  EFI_PEIM_ENTRY_POINT InMemEntryPoint
// Pointer to the FFS entry point in memory.
//
// Output:
//  EFI_INVALID_PARAMETER, if HOB = NULL.
//  EFI_OUT_OF_RESOURCES,  if not enough space to create HOB.
//  Otherwise, EFI_SUCCESS.
//
// Modified:
//
// Referrals:
// 
// Notes:	
//          
//<AMI_PHDR_END>
//*************************************************************************
EFI_STATUS CreateLoadHob(
	IN EFI_PEI_SERVICES **ppPS, IN EFI_FFS_FILE_HEADER *pFfsHeader,
	EFI_PEIM_ENTRY_POINT EntryPoint, EFI_PEIM_ENTRY_POINT InMemEntryPoint
)
{
	EFI_STATUS	Status;
	PEIM_LOAD_HOB *pHob;
	static EFI_GUID guidAmiPeimLoadHob = AMI_PEIM_LOAD_HOB_GUID;
	
	Status=(*ppPS)->CreateHob(ppPS, EFI_HOB_TYPE_GUID_EXTENSION, sizeof(PEIM_LOAD_HOB),&pHob);
	if (!EFI_ERROR(Status))
	{
		pHob->Header.Name = guidAmiPeimLoadHob;
		pHob->pFfsHeader = pFfsHeader;
		pHob->EntryPoint = EntryPoint;
		pHob->InMemEntryPoint= InMemEntryPoint;
	}
	return Status;
}

//*************************************************************************
//<AMI_PHDR_START>
//
// Name: PeiGetVariable
//
// Description:	
//  EFI_STATUS PeiGetNextVariableName(IN EFI_PEI_SERVICES **PeiServices,
// IN CONST CHAR16 *VariableName, IN CONST EFI_GUID *VariableGuid,
// OUT UINT32 *Attributes, IN OUT UINTN *DataSize, OUT VOID *Data) reads an
// EFI variable; it serves as a wrapper for the Read Only Variable PPI 
// GetVariable routine. The functions first locates the Read Only Variable
// PPI instance, then makes a call to the GetVariable routine and returns 
// the EFI_STATUS of the GetVariable call. 
//
// Input:
//  IN EFI_PEI_SERVICES **PeiServices
// Double pointer to the PEI Services Table.
//
//  IN CONST CHAR16 *VariableName
// A pointer to a null-terminated string that is the variable's name.
//
//  IN CONST EFI_GUID *VariableGuid
// A pointer to an EFI_GUID that is the variable's GUID. The combination of
// VariableGuid and VariableName must be unique.
//
//  OUT UINT32 *Attributes
// If non-NULL, on return, points to the variable's attributes.
//
//  IN OUT UINTN *DataSize
// On entry, points to the size in bytes of the Data buffer. On return,
// points to the size of the data returned in Data.
//
//  OUT VOID *Data
// Points to the buffer which will hold the returned variable value.  The
// user is responsible for allocating this memory!
//
// Output:
//  EFI_BUFFER_TOO_SMALL,  if DataSize is too small to hold the contents of
//                         the variable.  DataSize will be set to show the
//                         minimum required size.
//  EFI_INVALID_PARAMETER, if VariableName, VariableGuid, DataSize, or Data
//                         are equal to NULL.
//  EFI_DEVICE_ERROR,      if variable could not be retrieved because of a
//                         device error.
//  EFI_NOT_FOUND,         if the variable or Read Only Variable PPI could
//                         not be found.
//  Otherwise, EFI_SUCCESS.
//
// Modified:
//
// Referrals:
// 
// Notes:	
//  See Platform Initialization Specification for details regarding the
// Read Only Variable PPI and GetVariable.
//          
//<AMI_PHDR_END>
//*************************************************************************
EFI_STATUS PeiGetVariable(
	IN EFI_PEI_SERVICES **PeiServices,
    IN CONST CHAR16 *VariableName, IN CONST EFI_GUID *VariableGuid,
    OUT UINT32 *Attributes, 
    IN OUT UINTN *DataSize, OUT VOID *Data
)
{
    EFI_PEI_READ_ONLY_VARIABLE2_PPI *VariablePpi;
    EFI_STATUS Status = (*PeiServices)->LocatePpi(
        PeiServices, &gEfiPeiReadOnlyVariable2PpiGuid, 0, NULL, &VariablePpi
    );
    if (EFI_ERROR(Status)) return Status;
    return VariablePpi->GetVariable(
        VariablePpi,VariableName, VariableGuid, Attributes, DataSize, Data
    );
}

//*************************************************************************
//<AMI_PHDR_START>
//
// Name: PeiGetNextVariableName
//
// Description:	
//  EFI_STATUS PeiGetNextVariableName(IN EFI_PEI_SERVICES **PeiServices, 
// IN OUT UINTN *VariableNameSize, IN OUT CHAR16 *VariableName, 
// IN OUT EFI_GUID *VariableGuid) performs enumeration of the EFI variables. 
// This function serves as a wrapper for the Read Only Variable PPI
// GetNextVariableName routine. It locates the Read Only Variable PPI
// instance, then makes a call to the GetNextVariableName routine and returns
// its EFI_STATUS.
//
// Input:
//  IN EFI_PEI_SERVICES **PeiServices
// Double pointer to the PEI Services Table.
//
//  IN OUT UINTN *VariableNameSize
// On entry, points to the size of the buffer pointed to by VariableName.
// If function returns EFI_BUFFER_TOO_SMALL, VariableNameSize is updated to
// reflect the buffer size required for the next variable's name.
// 
//  IN OUT CHAR16 *VariableName
// On entry, a pointer to a null-terminated string that is the variable's
// name. On return, points to the next variable's null-terminated name
// string.
//
//  IN OUT EFI_GUID *VariableGuid
// On entry, a pointer to an UEFI _GUID that is the variable's GUID. On
// return, a pointer to the next variable's GUID.
//
// Output:
//  EFI_NOT_FOUND,         if the variable or Read Only Variable PPI could
//                         not be found.
//  EFI_BUFFER_TOO_SMALL,  if VariableNameSize is too small for the resulting
//                         data.  VariableNameSize is updated with the size
//                         required for the specified variable.
//  EFI_INVALID_PARAMETER, if VariableName, VariableNameSize, or VariableGuid
//                         are NULL.
//  EFI_DEVICE_ERROR,      if the variable could not be retrieved because of
//                         a device error.
//  Otherwise, EFI_SUCCESS.
//
// Modified:
//
// Referrals:
// 
// Notes:
//  See the Platform Initialization Specification for details regarding
// the Read Only Variable PPI and NextVariableName.
//          
//<AMI_PHDR_END>
//*************************************************************************
EFI_STATUS PeiGetNextVariableName(
	IN EFI_PEI_SERVICES **PeiServices,
    IN OUT UINTN *VariableNameSize, IN OUT CHAR16 *VariableName,
    IN OUT EFI_GUID *VariableGuid
)
{
    EFI_PEI_READ_ONLY_VARIABLE2_PPI *VariablePpi;
    EFI_STATUS Status = (*PeiServices)->LocatePpi(
        PeiServices, &gEfiPeiReadOnlyVariable2PpiGuid, 0, NULL, &VariablePpi
    );
    if (EFI_ERROR(Status)) return Status;
    return VariablePpi->NextVariableName(
        VariablePpi,VariableNameSize, VariableName, VariableGuid
    );
}

//*************************************************************************
//<AMI_PHDR_START>
//
// Name: FindFfsFileByName
//
// Description:	
//  VOID* FindFfsFileByName(IN EFI_PEI_SERVICES **PeiServices, 
// IN EFI_FV_FILETYPE FileType, IN EFI_GUID *FileName) scans all available 
// firmware volumes for a FFS file of type FileType with GUID equal to
// FileName and returns the address of the first byte of the FFS file data.
// If more than one file matches the criteria, the function returns the
// address of the first file found.
//
// Input:
//  IN EFI_PEI_SERVICES **PeiServices
// Double pointer to the PEI Services Table.
//
//  IN EFI_FV_FILETYPE FileType
// Type of FFS file to find.
//
//  IN EFI_GUID *FileName
// GUID of FFS file to find.
//
// Output:
//  VOID* pointer to the first byte of the FFS file data. Returns NULL if no
// FFS file found.
//   
// Modified:
//
// Referrals:
// 
// Notes:
//          
//<AMI_PHDR_END>
//*************************************************************************
VOID* FindFfsFileByName(
    IN EFI_PEI_SERVICES **PeiServices, EFI_FV_FILETYPE FileType, 
    EFI_GUID *FileName
){
	EFI_FIRMWARE_VOLUME_HEADER* pFV;
	UINTN FvNum=0;
    //loop over all FV
	while( !EFI_ERROR ((*PeiServices)->FfsFindNextVolume (PeiServices, FvNum++, &pFV) ) ){
        EFI_FFS_FILE_HEADER* pFile = NULL;
	    EFI_STATUS Status;
	    // loop over raw files within FV
	    while(TRUE){
		    Status = (*PeiServices)->FfsFindNextFile(PeiServices, FileType, pFV, &pFile);
		    if( EFI_ERROR(Status) ) break;
            //make sure this is our RAW file.
            //guidcmp works like strcmp. It returns 0 when GUIDs are the same.
            if (guidcmp(&pFile->Name,&FileName)) continue;
            //skip file header
            return pFile+1;
	    }
    }
    return NULL;
}

//****************************************************************************
//        PERFORMANCE MEASUREMENT DEFINITIONS
//****************************************************************************
static EFI_GUID gEfiPeiPerformanceHobGuid = EFI_PEI_PERFORMANCE_HOB_GUID;

#define EFI_PERF_PEI_ENTRY_MAX_NUM      50

typedef struct {
    CHAR8   Token[EFI_PERF_PDBFILENAME_LENGTH];
    UINT32  Duration;
} EFI_PERF_DATA;
    
typedef struct {
    UINT64        BootToOs;
    UINT64        S3Resume;
    UINT32        S3EntryNum;
    EFI_PERF_DATA S3Entry[EFI_PERF_PEI_ENTRY_MAX_NUM];
    UINT64        CpuFreq;
    UINT64        BDSRaw;
    UINT32        Count;
    UINT32        Signiture;
} EFI_PERF_HEADER;

//*************************************************************************
//<AMI_PHDR_START>
//
// Name: PEI_PERF_START
//
// Description:
//  PEI_PERF_START(Ps, Token, FileHeader, Value) is a macro which invokes
// the PeiPerfMeasure function to log a timer entry for measuring performance
// if the PEI_PERFORMANCE SDL token is turned on.  If the PEI_PERFORMANCE SDL
// token is turned off, the macro does nothing.
//
// Input:
//  IN EFI_PEI_SERVICES **Ps
// Double pointer to the PEI Services Table.
//
//  IN CHAR16 *Token
// Pointer to token name.
//
//  IN EFI_FFS_FILE_HEADER *FileHeader
// Pointer to the file header.
//
//  IN UINT64 Value
// A non-zero value indicates the start time.  Otherwise, GetCpuTimer is used
// to get the current CPU timer value.
//
// Output:
//  VOID.
//
// Modified:
//
// Referrals:
//  PeiPerfMeasure
//  GetCpuTimer
// 
// Notes:
//  This macro is defined in AmiPeiLib.h.
//
//<AMI_PHDR_END>
//*************************************************************************

//*************************************************************************
//<AMI_PHDR_START>
//
// Name: PEI_PERF_END
//
// Description:
//  PEI_PERF_END(Ps, Token, FileHeader, Value) is a macro which invokes
// the PeiPerfMeasure function to stop timing for an entry to determine
// performance if the PEI_PERFORMANCE SDL token is turned on.  If the
// PEI_PERFORMANCE SDL token is turned off, the macro does nothing.
//
// Input:
//  IN EFI_PEI_SERVICES **Ps
// Double pointer to the PEI Services Table.
//
//  IN CHAR16 *Token
// Pointer to token name.
//
//  IN EFI_FFS_FILE_HEADER *FileHeader
// Pointer to the file header.
//
//  IN UINT64 Value
// A non-zero value indicates the stop time.  Otherwise, GetCpuTimer is used
// to get the current CPU timer value.
//
// Output:
//  VOID.
//
// Modified:
//
// Referrals:
//  PeiPerfMeasure
//  GetCpuTimer
// 
// Notes:
//  This macro is defined in AmiPeiLib.h.
//
//<AMI_PHDR_END>
//*************************************************************************

//*************************************************************************
//<AMI_PHDR_START>
//
// Name: PEI_PERF_SAVE_S3_DATA
//
// Description:
//  PEI_PERF_SAVE_S3_DATA(Ps) is a macro which invokes the
// SaveS3PerformanceData function in order to save the S3 performance data in
// an EFI PEI performance HOB.  This should only be called once, just before
// the end of PEI.
//
// Input:
//  IN EFI_PEI_SERVICES **Ps
// Double pointer to the PEI Services Table.
//
// Output:
//  VOID.
//
// Modified:
//
// Referrals:
//  SaveS3PerformanceData
// 
// Notes:
//  This macro is defined in AmiPeiLib.h.
//
//<AMI_PHDR_END>
//*************************************************************************

//*************************************************************************
//<AMI_PHDR_START>
//
// Name: PeiPerfMeasure
//
// Description:	
//  VOID PeiPerfMeasure(IN EFI_PEI_SERVICES **PeiServices, IN CHAR16 *Token,
// IN EFI_FFS_FILE_HEADER *FileHeader, IN BOOLEAN EntryExit, IN UINT64 Value)
// logs a timestamp count for measuring performance.  See the notes for
// proper usage.
//
// Input:
//  IN EFI_PEI_SERVICES **PeiServices
// Double pointer to the PEI Services Table.
//
//  IN CHAR16 *Token
// Pointer to token name.
//
//  IN EFI_FFS_FILE_HEADER *FileHeader
// Pointer to the file header.
//
//  IN BOOLEAN EntryExit
// FALSE indicates start, TRUE indicates stop.
//
//  IN UINT64 Value
// If EntryExit is TRUE, a non-zero value indicates stop time.  Otherwise if
// EntryExit is FALSE, a non-zero value indicates start time.
//
// Output:
//  VOID.
//   
// Modified:
//
// Referrals:
//  GetCpuTimer
// 
// Notes:
//  Use the PEI_PERF_START and PEI_PERF_END macros; this allows performance
// monitoring to be enabled or disabled with the PEI_PERFORMANCE SDL token.
//          
//<AMI_PHDR_END>
//*************************************************************************
VOID PeiPerfMeasure (
  EFI_PEI_SERVICES **PeiServices,
  IN CHAR16 *Token, IN EFI_FFS_FILE_HEADER *FileHeader,
  IN BOOLEAN EntryExit, IN UINT64 Value
)
{
  EFI_STATUS                         Status;
  EFI_HOB_GUID_TYPE                  *Hob;
  EFI_HOB_GUID_DATA_PERFORMANCE_LOG  *PerfHobData;
  PEI_PERFORMANCE_MEASURE_LOG_ENTRY  *Log;
  EFI_PEI_PPI_DESCRIPTOR             *PerfHobDescriptor;
  UINT64                             TimeCount;
  UINTN                              Index;
  UINTN                              Index2;
  EFI_GUID                           *Guid;
  EFI_GUID                           *CheckGuid;

  TimeCount = 0;
  //
  // Get the END time as early as possible to make it more accurate.
  //
  if (EntryExit) {
	  TimeCount = GetCpuTimer();
  }

  //
  // Locate the Pei Performance Log Hob.
  //
  Status = (*PeiServices)->LocatePpi (
                             PeiServices,
                             &gEfiPeiPerformanceHobGuid,
                             0,
                             &PerfHobDescriptor,
                             NULL
                             );

  //
  // If the Performance Hob was not found, build and install one.
  //
  if (EFI_ERROR(Status)) {
    Status = (*PeiServices)->CreateHob (
      PeiServices,
      EFI_HOB_TYPE_GUID_EXTENSION,
      sizeof (EFI_HOB_GUID_TYPE) +
      sizeof(EFI_HOB_GUID_DATA_PERFORMANCE_LOG) +
      (MAX_PEI_PERF_LOG_ENTRIES-1) * sizeof(PEI_PERFORMANCE_MEASURE_LOG_ENTRY) +
      sizeof(EFI_PEI_PPI_DESCRIPTOR),
      &Hob
    );
    ASSERT_PEI_ERROR(PeiServices, Status);
    Hob->Name = gEfiPeiPerformanceHobGuid;
    PerfHobData = (EFI_HOB_GUID_DATA_PERFORMANCE_LOG *)(Hob+1);
    PerfHobData->NumberOfEntries = 0;
    PerfHobDescriptor = (EFI_PEI_PPI_DESCRIPTOR *)((UINT8 *)(PerfHobData+1) +
                                                     (sizeof(PEI_PERFORMANCE_MEASURE_LOG_ENTRY) *
                                                       (MAX_PEI_PERF_LOG_ENTRIES-1)
                                                     )
                                                  );
    PerfHobDescriptor->Flags = (EFI_PEI_PPI_DESCRIPTOR_PPI | EFI_PEI_PPI_DESCRIPTOR_TERMINATE_LIST);
    PerfHobDescriptor->Guid = &gEfiPeiPerformanceHobGuid;
    PerfHobDescriptor->Ppi = NULL;

    (*PeiServices)->InstallPpi (
                      PeiServices,
                      PerfHobDescriptor
                      );
  }

  PerfHobData = (EFI_HOB_GUID_DATA_PERFORMANCE_LOG *)(((UINT8 *)(PerfHobDescriptor)) -
                                                        ((sizeof(PEI_PERFORMANCE_MEASURE_LOG_ENTRY) *
                                                           (MAX_PEI_PERF_LOG_ENTRIES-1)
                                                         )
                                                         + sizeof(EFI_HOB_GUID_DATA_PERFORMANCE_LOG)
                                                      )
                                                     );

  if (PerfHobData->NumberOfEntries >= MAX_PEI_PERF_LOG_ENTRIES) {
    return;
  }

  if (!EntryExit) {
    Log = &(PerfHobData->Log[PerfHobData->NumberOfEntries]);
    (*PeiServices)->SetMem (Log, sizeof(PEI_PERFORMANCE_MEASURE_LOG_ENTRY), 0);

    //
    // If not NULL pointer, copy the file name
    //
    if (FileHeader != NULL) {
      Log->Name = FileHeader->Name;
    }

    //
    // Copy the description string
    //
    (*PeiServices)->CopyMem (
                      &(Log->DescriptionString), 
                      Token,
                      (PEI_PERF_MAX_DESC_STRING-1) * sizeof(UINT16)
                      );

    //
    // Get the start time as late as possible to make it more accurate.
    //
    TimeCount = GetCpuTimer();

    //
    // Record the time stamp.
    //
    if (Value != 0) {
      Log->StartTimeCount = Value;
    } else {
      Log->StartTimeCount = TimeCount;
    }
    Log->StopTimeCount = 0;

    //
    // Increment the number of valid log entries.
    //
    PerfHobData->NumberOfEntries++;

  } else {

    for (Index = PerfHobData->NumberOfEntries-1; Index >= 0; Index--) {
      Log = NULL;
      for (Index2 = 0; Index2 < PEI_PERF_MAX_DESC_STRING; Index2++) {
        if (PerfHobData->Log[Index].DescriptionString[Index2] == 0) {
          Log = &(PerfHobData->Log[Index]);
          break;
        }
        if (PerfHobData->Log[Index].DescriptionString[Index2] !=
            Token[Index2]) {
          break;
        }
      }
      if (Log != NULL) {
        if (FileHeader != NULL) {
          Guid = &(Log->Name);
          CheckGuid = &(FileHeader->Name);
          if ((((INT32 *)Guid)[0] == ((INT32 *)CheckGuid)[0]) &&
              (((INT32 *)Guid)[1] == ((INT32 *)CheckGuid)[1]) &&
              (((INT32 *)Guid)[2] == ((INT32 *)CheckGuid)[2]) &&
              (((INT32 *)Guid)[3] == ((INT32 *)CheckGuid)[3]))  {
            if (Value != 0) {
              Log->StopTimeCount = Value;
            } else {
             Log->StopTimeCount = TimeCount;
            }
            break;
          }
        } else {
          if (Value != 0) {
            Log->StopTimeCount = Value;
          } else {
           Log->StopTimeCount = TimeCount;
          }
          break;
        }
      }
    }
            
  }

  return;
}

//*************************************************************************
//<AMI_PHDR_START>
//
// Name: SaveS3PerformanceData
//
// Description:	
//  VOID SaveS3PerformanceData(IN EFI_PEI_SERVICES **PeiServices) saves the
// S3 performance data in an EFI PEI performance HOB.  This should only be
// called once, just before the end of PEI.  See notes for proper usage.
//
// Input:
//  IN EFI_PEI_SERVICES **PeiServices
// Double pointer to PEI Services Table.
//
// Output:
//  VOID.
//   
// Modified:
//
// Referrals:
//  GetCpuTimer
// 
// Notes:
//  To use this function properly, use the PEI_PERF_SAVE_S3_DATA macro.  This
// allows the PEI_PERFORMANCE SDL token to control enabling and disabling
// performance measurements.
// The PEI_PERF_SAVE_S3_DATA macro is used by S3Resume module to log performance data.
//          
//<AMI_PHDR_END>
//*************************************************************************
VOID SaveS3PerformanceData(IN EFI_PEI_SERVICES **PeiServices){
    static EFI_GUID gEfiPeiPerformanceHobGuid = EFI_PEI_PERFORMANCE_HOB_GUID;
    EFI_STATUS                         Status;
    UINT64                             Time;
    UINTN                              VarSize;
    EFI_GUID                           gEfiGlobalVariableGuid = EFI_GLOBAL_VARIABLE;
    EFI_PERF_HEADER                    *PerfHeader;
    EFI_PHYSICAL_ADDRESS               AcpiLowMemoryBase;
    UINT32                             i;
    UINT32                             j;
    EFI_HOB_GUID_DATA_PERFORMANCE_LOG  *LogHob;
    PEI_PERFORMANCE_MEASURE_LOG_ENTRY  *LogEntry;
    EFI_PEI_HOB_POINTERS               Hob;

    Time  = GetCpuTimer();
    VarSize   = sizeof (EFI_PHYSICAL_ADDRESS);
    Status = PeiGetVariable(
        PeiServices,
		L"PerfDataMemAddrInternal", &gAmiGlobalVariableGuid,
		NULL, &VarSize, &AcpiLowMemoryBase

    );
    if (EFI_ERROR (Status)) return;

    PerfHeader = (EFI_PERF_HEADER *) ((UINT32) AcpiLowMemoryBase);
    *((UINT64 *) (&PerfHeader->S3Resume)) = Time;
    // Get S3 detailed performance data
    PerfHeader->S3EntryNum = 0;

    (*PeiServices)->GetHobList (PeiServices, &Hob.Raw);
    Status = FindNextHobByGuid(&gEfiPeiPerformanceHobGuid,&Hob.Raw);
    if (EFI_ERROR (Status)) return;
    LogHob = (EFI_HOB_GUID_DATA_PERFORMANCE_LOG *) (Hob.Raw + sizeof (EFI_HOB_GENERIC_HEADER) + sizeof (EFI_GUID));

    for( i = 0;
         ((i < LogHob->NumberOfEntries) && (PerfHeader->S3EntryNum < EFI_PERF_PEI_ENTRY_MAX_NUM));
         i++
    ){
        LogEntry = &(LogHob->Log[i]);
        if (LogEntry->StopTimeCount == 0) {
            continue;
        }
        for (j = 0; j < 8; j++) {
            PerfHeader->S3Entry[PerfHeader->S3EntryNum].Token[j] = (CHAR8) (LogEntry->DescriptionString[j]);
        }
        PerfHeader->S3Entry[PerfHeader->S3EntryNum].Duration = (UINT32) Div64 (
                                                                              LogEntry->StopTimeCount - LogEntry->StartTimeCount,
                                                                              (UINT32) PerfHeader->CpuFreq,
                                                                              NULL
                                                                           );
        PerfHeader->S3EntryNum++;
    }
}

EFI_STATUS PeiLoadFile(
    IN CONST EFI_PEI_SERVICES ** PeiServices,
    IN  EFI_PEI_FILE_HANDLE            FileHandle,
    OUT EFI_PHYSICAL_ADDRESS           *ImageAddress,
    OUT UINT64                         *ImageSize,
    OUT EFI_PHYSICAL_ADDRESS           *EntryPoint
){
#if PI_SPECIFICATION_VERSION < 0x00010000
    EFI_PEI_FV_FILE_LOADER_PPI *Loader;
#else
    EFI_PEI_LOAD_FILE_PPI *Loader;
    UINT32 AuthenticationState;
#endif;
    EFI_PEI_PPI_DESCRIPTOR *Dummy;
    EFI_STATUS Status = (*PeiServices)->LocatePpi(
        (EFI_PEI_SERVICES**)PeiServices, 
        &gEfiPeiLoadFilePpiGuid,0, &Dummy, &Loader
    );
    if ((EFI_ERROR(Status))) return Status;
    return 
#if PI_SPECIFICATION_VERSION < 0x00010000
    Status = Loader->FvLoadFile(
#else
    Status = Loader->LoadFile(
#endif
        Loader, FileHandle, ImageAddress, ImageSize, EntryPoint
#if PI_SPECIFICATION_VERSION >= 0x00010000
        ,&AuthenticationState
#endif
    );
}

#if PI_SPECIFICATION_VERSION >= 0x00010000
#pragma pack (1)
typedef struct {
	UINT16	Limit;
	UINTN   Base;
} DESCRIPTOR_TABLE;
#pragma pack()

VOID CPULib_SaveIdt(DESCRIPTOR_TABLE *Idt);

EFI_PEI_SERVICES ** GetPeiServicesTablePointer (VOID){
  EFI_PEI_SERVICES  **PeiServices;
  DESCRIPTOR_TABLE Idtr;
  
  CPULib_SaveIdt (&Idtr);
  PeiServices = (EFI_PEI_SERVICES **) (*(UINTN*)(Idtr.Base - sizeof (UINTN)));
  return PeiServices;
}

VOID SetPeiServicesTablePointer (
    IN CONST EFI_PEI_SERVICES ** PeiServicesTablePointer
){
  DESCRIPTOR_TABLE Idtr;
  
  CPULib_SaveIdt (&Idtr);
  (*(UINTN*)(Idtr.Base - sizeof (UINTN))) = (UINTN)PeiServicesTablePointer; 
}
#else
EFI_PEI_SERVICES ** GetPeiServicesTablePointer (VOID){
_asm {
    push    eax
    push    eax
    movq    [esp], mm7
    pop     eax
    pop     edx
    emms
  }
}
#endif

EFI_STATUS PciCfgModify(
    IN CONST EFI_PEI_SERVICES ** PeiServices,
	IN EFI_PEI_PCI_CFG_PPI_WIDTH		Width,
	IN UINT64							Address,
	IN UINTN							SetBits,
	IN UINTN							ClearBits
){
    if ((*PeiServices)->PciCfg==NULL) return EFI_NOT_AVAILABLE_YET;
    return (*PeiServices)->PciCfg->Modify(
        (EFI_PEI_SERVICES**)PeiServices, (*PeiServices)->PciCfg,
        Width, Address,
#if PI_SPECIFICATION_VERSION < 0x00010000
        SetBits, ClearBits
#else
        &SetBits, &ClearBits
#endif
    );
}
//*************************************************************************
//*************************************************************************
//**                                                                     **
//**        (C)Copyright 1985-2009, American Megatrends, Inc.            **
//**                                                                     **
//**                       All Rights Reserved.                          **
//**                                                                     **
//**      5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093           **
//**                                                                     **
//**                       Phone: (770)-246-8600                         **
//**                                                                     **
//*************************************************************************
//*************************************************************************
