//**********************************************************************
//**********************************************************************
//**                                                                  **
//**        (C)Copyright 1985-2007, American Megatrends, Inc.         **
//**                                                                  **
//**                       All Rights Reserved.                       **
//**                                                                  **
//**             6145-F Northbelt Pkwy, Norcross, GA 30071            **
//**                                                                  **
//**                       Phone: (770)-246-8600                      **
//**                                                                  **
//**********************************************************************
//**********************************************************************

//**********************************************************************
// $Header: /Alaska/BIN/Core/Include/AmiPeiLib.h 16    2/05/11 2:01p Artems $
//
// $Revision: 16 $
//
// $Date: 2/05/11 2:01p $
//**********************************************************************
// Revision History
// ----------------
// $Log: /Alaska/BIN/Core/Include/AmiPeiLib.h $
// 
// 16    2/05/11 2:01p Artems
// Added functions to support both PI 0.91 and PI 1.0-1.1 specifications
// 
// 15    6/06/08 10:50a Felixp
// Performance API extended with PEI_PERF_SAVE_S3_DATA macro
// 
// 14    5/07/08 12:21p Felixp
// Performance API added
// 
// 13    10/22/07 6:24p Felixp
// FindFfsFileByName routine added.
// 
// 12    8/30/07 11:00p Felixp
// PeiGetVariable and PeiGetNextVariableName routines added.
// 
// 11    4/20/07 5:08p Felixp
// Status Code macros redefined
// 
// 10    3/08/07 2:59a Felixp
// Update of the status code specific definitions
// 
// 9     8/24/06 9:10a Felixp
// x64 support
// 
// 8     5/23/06 5:03a Felixp
// 
// 7     5/20/06 9:35p Felixp
// PEI_ASSET & EFI_PEI_ASSERT added
// 
// 6     3/13/06 1:15a Felixp
// 
// 5     10/09/05 11:26a Felixp
// Support for performance measurements added.
// 
// 4     6/16/05 10:43a Felixp
// CreateLoadHob function added (used by PEIMs to reguest reallocation to
// RAM,
// once memory is detected)
// 
// 3     6/07/05 7:22p Felixp
// PEI_PROGRESS_CODE imeplemented via call to ReportStatusCode
// 
// 2     3/04/05 10:21a Mandal
// 
// 1     1/28/05 12:44p Felixp
// 
// 5     1/24/05 2:23p Felixp
// FVFILE_SIZE macros added
// 
// 3     1/18/05 3:21p Felixp
// PrintDebugMessage renamed to Trace
// 
// 1     12/23/04 9:41a Felixp
// 
// 7     12/17/04 6:45p Felixp
// PEI_DEBUG_MSG renamed to PEI_TRACE
// 
// 6     11/10/04 5:16p Felixp
// Level parameter added to PeiTrace fucntion
// 
// 5     11/02/04 5:32p Felixp
// 
// 4     10/22/04 7:35p Felixp
// 
// 3     10/20/04 10:48a Felixp
// 
// 2     3/28/04 2:11p Felixp
// 1. PE Loader and some other commonly used code moved to the Library
// 2. Warnings fixed (from now on warning will be treated as error)
// 
// 1     3/23/04 5:52p Felixp
// 
//**********************************************************************
//<AMI_FHDR_START>
//
// Name:	AmiPeiLib.h
//
// Description:	
//
//<AMI_FHDR_END>
//**********************************************************************
#ifndef __AMI_PEI_LIB__H__
#define __AMI_PEI_LIB__H__
#ifdef __cplusplus
extern "C" {
#endif
#include <PEI.h>
#include <HOB.h>
#include <AmiLib.h>
//****************************************************************************/
//		TYPE DECLARATIONS
//****************************************************************************/

//****************************************************************************/
//		MACOROS DECLARATIONS
//****************************************************************************/
#define FVSECTION_SIZE(pSection) ((*(UINT32*)&((EFI_COMMON_SECTION_HEADER*)(pSection)-1)->Size[0] & 0xffffff) - sizeof(EFI_COMMON_SECTION_HEADER))
#define FVFILE_SIZE(pFile) (*(UINT32*)&(pFile)->Size[0]&0xffffff)

#ifdef EFI_DEBUG
#define PEI_TRACE(Arguments) PeiTrace Arguments

#ifndef PEI_ASSERT
#define PEI_ASSERT(PeiServices,Condition) if(!(Condition)) { \
	PeiTrace(-1,PeiServices,"ASSERT in %s on %i: %s\n",__FILE__, __LINE__, #Condition);\
	EFI_DEADLOOP() \
	}
#define ASSERT_PEI_ERROR(PeiServices,Status)  PEI_ASSERT(PeiServices,!EFI_ERROR(Status))
#endif

#define PEI_VERIFY PEI_ASSERT
#define VERIFY_PEI_ERROR ASSERT_EFI_ERROR

#else // EFI_DEBUG==0
#define PEI_TRACE(Arguments)

#ifndef PEI_ASSERT
#define PEI_ASSERT(PeiServices,Condition)
#define ASSERT_PEI_ERROR(PeiServices,Status)
#endif

#define PEI_VERIFY(x) (x)
#define VERIFY_PEI_ERROR(x) (x)

#endif

#define PEI_PROGRESS_CODE(PeiServices, Code)\
	(*PeiServices)->ReportStatusCode(PeiServices, EFI_PROGRESS_CODE, Code, 0, NULL, NULL)

#define PEI_ERROR_CODE(PeiServices, Code, Severity)\
	(*PeiServices)->ReportStatusCode(\
        (EFI_PEI_SERVICES**)PeiServices, EFI_ERROR_CODE|(Severity),\
        Code, 0, NULL, NULL\
    )

#ifdef EFI_PEI_PERFORMANCE
#define PEI_PERF_START(Ps, Token, FileHeader, Value)  PeiPerfMeasure (Ps, Token, FileHeader, FALSE, Value)
#define PEI_PERF_END(Ps, Token, FileHeader, Value)    PeiPerfMeasure (Ps, Token, FileHeader, TRUE, Value)
#define PEI_PERF_SAVE_S3_DATA(Ps) SaveS3PerformanceData(Ps)
#else
#define PEI_PERF_START(Ps, Token, FileHeader, Value)
#define PEI_PERF_END(Ps, Token, FileHeader, Value)
#define PEI_PERF_SAVE_S3_DATA(Ps) 
#endif

//****************************************************************************/
//		VARIABLE DECLARATIONS
//****************************************************************************/

//****************************************************************************/
//		FUNCTION DECLARATIONS
//****************************************************************************/
VOID* PEEntryPoint(VOID *p);
VOID* TEEntryPoint(VOID *p);
UINT32 GetImageSize(VOID *p);

VOID PeiTrace(UINTN Level, CONST EFI_PEI_SERVICES **ppPS, CHAR8 *sFormat,...);
VOID PeiReportErrorCode(EFI_PEI_SERVICES **ppPS, UINT16 Code, UINT32 Action);

EFI_STATUS CreateHobMemoryAllocationModule(
	IN EFI_PEI_SERVICES **PeiServices,
    IN EFI_PHYSICAL_ADDRESS MemoryBaseAddress,
    IN UINT64 MemoryLength, IN EFI_MEMORY_TYPE MemoryType,
    IN EFI_GUID *ModuleName,
    IN EFI_PHYSICAL_ADDRESS EntryPoint
);
EFI_STATUS CreateHobResourceDescriptor
(
	IN EFI_PEI_SERVICES **PeiServices,
    IN EFI_GUID *Owner, IN EFI_RESOURCE_TYPE ResourceType,
    IN EFI_RESOURCE_ATTRIBUTE_TYPE ResourceAttribute,
    IN EFI_PHYSICAL_ADDRESS PhysicalStart,
    IN UINT64 ResourceLength
);
EFI_STATUS CreateLoadHob(
	IN EFI_PEI_SERVICES **ppPS, IN EFI_FFS_FILE_HEADER *pFfsHeader,
	EFI_PEIM_ENTRY_POINT EntryPoint, EFI_PEIM_ENTRY_POINT InMemEntryPoint
);

EFI_STATUS PeiGetVariable(
	IN EFI_PEI_SERVICES **PeiServices,
    IN CONST CHAR16 *VariableName, IN CONST EFI_GUID *VariableGuid,
    OUT UINT32 *Attributes, 
    IN OUT UINTN *DataSize, OUT VOID *Data
);
EFI_STATUS PeiGetNextVariableName(
	IN EFI_PEI_SERVICES **PeiServices,
    IN OUT UINTN *VariableNameSize, IN OUT CHAR16 *VariableName,
    IN OUT EFI_GUID *VariableGuid
);

VOID* FindFfsFileByName(
    IN EFI_PEI_SERVICES **PeiServices, EFI_FV_FILETYPE FileType, 
    EFI_GUID *FileName
);

VOID PeiPerfMeasure (
  EFI_PEI_SERVICES **PeiServices,
  IN CHAR16 *Token, IN EFI_FFS_FILE_HEADER *FileHeader,
  IN BOOLEAN EntryExit, IN UINT64 Value
);

VOID SaveS3PerformanceData(IN EFI_PEI_SERVICES **PeiServices);

EFI_STATUS PeiLoadFile(
    IN CONST EFI_PEI_SERVICES ** PeiServices,
    IN  EFI_PEI_FILE_HANDLE            FileHandle,
    OUT EFI_PHYSICAL_ADDRESS           *ImageAddress,
    OUT UINT64                         *ImageSize,
    OUT EFI_PHYSICAL_ADDRESS           *EntryPoint
);

EFI_PEI_SERVICES ** GetPeiServicesTablePointer (VOID);
#if PI_SPECIFICATION_VERSION >= 0x00010000
VOID SetPeiServicesTablePointer (
    IN CONST EFI_PEI_SERVICES ** PeiServicesTablePointer
);
#endif

EFI_STATUS PciCfgModify(
    IN CONST EFI_PEI_SERVICES ** PeiServices,
	IN EFI_PEI_PCI_CFG_PPI_WIDTH		Width,
	IN UINT64							Address,
	IN UINTN							SetBits,
	IN UINTN							ClearBits
);

/****** DO NOT WRITE BELOW THIS LINE *******/
#ifdef __cplusplus
}
#endif
#endif
//**********************************************************************
//**********************************************************************
//**                                                                  **
//**        (C)Copyright 1985-2007, American Megatrends, Inc.         **
//**                                                                  **
//**                       All Rights Reserved.                       **
//**                                                                  **
//**             6145-F Northbelt Pkwy, Norcross, GA 30071            **
//**                                                                  **
//**                       Phone: (770)-246-8600                      **
//**                                                                  **
//**********************************************************************
//**********************************************************************
