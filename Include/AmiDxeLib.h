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
// $Header: /Alaska/Projects/Intel/Haswell/LynxPoint_SharkBay-DT_Crb_1AQQW/Include/AmiDxeLib.h 2     10/25/12 8:50a Wesleychen $
//
// $Revision: 2 $
//
// $Date: 10/25/12 8:50a $
//**********************************************************************
// Revision History
// ----------------
// $Log: /Alaska/Projects/Intel/Haswell/LynxPoint_SharkBay-DT_Crb_1AQQW/Include/AmiDxeLib.h $
// 
// 2     10/25/12 8:50a Wesleychen
//  - Update Core to 4.6.5.4.
//  - Reprogram 'SaveStateMemPoll' functon.
// 
// 68    7/19/12 5:08p Felixp
// Declaration of the IsValidDevicePath is added.
// 
// 67    4/30/12 3:59p Artems
// [TAG]  		EIP N/A
// [Category]  	Improvement
// [Description]  	Modified GraphicsConsole driver to output whole string
// instead of symbol-by-symbol output
// [Files]  		Gc.c, AmiDxeLib.h, EfiLib.c, UefiHiiUtils.c
// 
// 66    11/08/11 5:22p Oleksiyy
// [TAG]  		EIP64296 
// [Category]  	New Feature
// [Description]  	Creation and filling of Firmware Performance Data Table
// is added.
// [Files]  		AcpiCore.c, AmiDxeLib.h, CSM.c, DxeMain.c, EfiLib.c,
// Image.c, S3Resume.c and FirmPerfDataTab.h
// 
// 65    7/22/11 2:51p Oleksiyy
// [TAG]  		EIP64391 
// [Category]  	Improvement
// [Description]  	Some BOOT_SCRIPT_S3_xxx macros was updated with correct
// parameters.
// [Files]  		AmiDxeLib.h
// 
// 64    7/22/11 10:03a Oleksiyy
// [TAG]  		EIP64391 
// [Category]  	Improvement
// [Description]  	Some BOOT_SCRIPT_S3_xxx macros was updated with correct
// parameters.
// [Files]  		AmiDxeLib.h
// 
// 63    6/24/11 1:44p Felixp
// PI definitions of the BOOT_SCRIPT_S3_ macros are updated to detect
// which protocol to use (S3SaveState or BootScriptSave).
// 
// 62    6/23/11 8:36p Artems
// Backward compatibility bug fix - temporary disable new boot script till
// modules are ready
// 
// 61    6/16/11 3:42p Felixp
// 
// 60    6/16/11 2:57p Felixp
// Surround backward compatibility definitions with #if
// BACKWARD_COMPATIBLE_MODE
// 
// 59    6/16/11 9:24a Felixp
// Enhancements: 
// 1. SMM-related functions and global variables are split into Framework
// and PI instances. Proper instance is selected based on supported
// version of the PI specification and module type.
// 2. BOOT_SCRIPT_S3_... macros moved to AmiDxeLib.h from BootScripSave.h.
// (both Framework and PI modes are supported).
// 
// 58    2/05/11 2:02p Artems
// Added helper function to initialize global pointers in SMM
// 
// 57    11/17/10 4:30p Felixp
// Declarations of EfiAtRuntime and  EfiGoneVirtual functions are added.
// 
// 56    10/01/10 2:57p Felixp
// declaration of LibInitStatusCodePtr is added.
// 
// 55    2/23/10 10:13p Felixp
// HiiLibSetBrowserData function is added
// 
// 54    10/14/09 10:41p Felixp
// 
// 53    10/14/09 3:49p Felixp
// HII_LIBRARY_FUNCTIONS_SUPPORT macro added.
// 
// 52    10/09/09 4:28p Felixp
// UEFI 2.1 related updates.
// 
// 51    8/21/09 3:04p Felixp
// LanguageCodesEqual function is added.
// 
// 50    5/21/09 4:28p Felixp
// New function InitAmiRuntimeLib is added. 
// The function can be used by Runtime drivers to initialize library 
// (the function calls InitAmiLib) and register callbacks 
// on exit boot services and virtual address change events.
// 
// 49    5/14/09 9:42a Felixp
// New functions: InitSmmHandlerEx and GetSmstConfigurationTable are
// added.
// 
// 48    9/30/08 12:09a Felixp
// WriteBootToOsPerformanceData function added
// 
// 47    6/06/08 10:47a Felixp
// 
// 44    9/04/07 12:10p Felixp
// TheImageHandle global variable is added. The variable is initialized in
// the InitAmiLib routine with the current image handle.
// 
// 43    8/30/07 11:03p Felixp
// GetBootMode routine is added. The routine can be used by DXE/EFI
// modules to get current boot mode.
// 
// 42    4/20/07 5:08p Felixp
// Status Code macros redefined
// 
// 41    4/19/07 12:31p Felixp
// New functions added: LibGetDxeSvcTbl and LibAllocateCspResource
// LibAllocateCspResource replaces AllocCspResource
// AllocCspResource preserved for backward compatibility.
// 
// 39    4/17/07 10:56a Yakovlevs
// AllocCspResource function preserved for compatibility witn core 4.5.3
// 
// 36    4/13/07 6:51p Yakovlevs
// Added function prototype LibGetDxeSvcTbl() 
// changed name of AllocateCspResource() to LibAllocateCspResource
// 
// 
// 							EFI_HANDLE ImgHandle,EFI_HANDLE CntrHandle);
// 
// 
// 35    3/08/07 3:01a Felixp
// Status code reporting macros PROGRESS_CODE and ERROR_CODE added
// 
// 34    2/12/07 1:37p Felixp
// 
// 33    2/12/07 1:19p Felixp
// DPGetEndNode declaration added
// 
// 32    11/26/06 11:49p Yakovlevs
// Added Functions AmiIsaIrqMAsk() and AmiIsaDmaMask() to sinchronize IRQ
// allocation in SIO and CSM modules
// 
// 31    11/26/06 11:00p Yakovlevs
// Added AMI_IRQ_DMA_MASK_VARIABLE_GUID
// 
// 30    10/13/06 2:36p Felixp
// 
// 29    10/12/06 6:43p Felixp
// DPNextInstance, DPCreateNode, DPIsMultiInstance functions added
// 
// 28    10/12/06 9:37a Felixp
// CreateLegacyBootEvent & CreateReadyToBootEvent functions added
// 
// 27    9/08/06 9:20a Felixp
// 
// 26    8/24/06 9:10a Felixp
// x64 support
// 
// 25    5/20/06 9:35p Felixp
// 
// 24    3/13/06 1:15a Felixp
// 
// 23    11/16/05 11:15a Yakovlevs
// DPCmp(), DPCut() functions added
// 
// 22    11/11/05 2:47p Felixp
// GetControllerName added
// 
// 21    11/11/05 11:47a Markw
// Renamed IntallSmmHandler to InitSmmHandler because of build errors
// because another driver used InstallSmmHandler.
// 
// 20    11/08/05 5:59p Markw
// Created InstallSmiHandler library function.
// 
// 19    11/07/05 3:15p Felixp
// CopyItemLst prototype added
// 
// 18    6/29/05 10:41a Yakovlevs
// 
// 17    6/28/05 6:45p Yakovlevs
// Added: Function  AllocCspResources() and CSP_RES_ITEM Structure
// definition
// 
// 16    6/03/05 3:45p Yakovlevs
// 
// 15    4/06/05 9:33a Felixp
// Function LoadStrings added
// 
// 14    4/04/05 2:58p Felixp
// LoadResources function added
// 
// 13    3/25/05 11:34a Felixp
// RegisterProtocolCallback function added
// 
// 12    3/21/05 11:46a Felixp
// Bit definitions moved from AmiDxeLib.h to AmiLib.h
// 
// 11    3/17/05 1:28p Felixp
// ReadImageResource funciton added
// 
// 10    3/04/05 10:21a Mandal
// 
// 9     3/03/05 12:31p Felixp
// GetDefaultLang added
// 
// 8     2/11/05 5:51p Felixp
// DPAddNode, DPAddInstance functions added
// 
// 7     2/08/05 5:24p Felixp
// Parameter added to DPIsOneOf.
// 
// 6     2/07/05 5:20p Felixp
// GetEfiVariable funciton added
// 
// 5     2/07/05 4:22p Yakovlevs
// 
// 4     2/03/05 8:00p Felixp
// DPLength and DPIsOneOf functions added
// 
// 3     2/01/05 2:27a Felixp
// 
// 2     2/01/05 2:00a Felixp
// I/O routine declarations moved from AmiDxeLib.h to AmiLib.h
// 
// 1     1/28/05 12:44p Felixp
// 
// 3     1/18/05 3:21p Felixp
// PrintDebugMessage renamed to Trace
// 
// 2     1/17/05 3:46p Andriyn
// 
// 1     12/23/04 9:41a Felixp
// 
// 31    12/20/04 5:07p Felixp
// 
// 30    12/17/04 6:45p Felixp
// DEBUG_MSG renamed to TRACE
// 
// 29    12/17/04 6:40p Olegi
// 
// 28    12/16/04 6:34a Felixp
// 
// 27    11/19/04 1:33a Felixp
// GetImageName debug routine added (image name by image handle)
// 
// 26    11/18/04 6:10p Felixp
// FindNextHobByType removed (moved to AmiLib.h)
// 
// 25    11/17/04 3:31p Markw
// 
// 24    11/16/04 5:03p Markw
// Added ASSERT.
// 
// 23    11/10/04 5:15p Felixp
// Level parameter added to Trace fucntion
// 
// 22    11/02/04 5:33p Felixp
// 
// 21    10/22/04 7:35p Felixp
// 
// 20    10/14/04 12:04p Felixp
// 
// 19    9/22/04 8:39p Yakovlevs
// Added definition of GCD - TestRegion() Function to check if reg1
// belongs to reg2
// 
// 18    8/28/04 1:49a Felixp
// NVRAM Routines fixes
// 
// 17    8/10/04 1:03p Yakovlevs
// 
// 16    8/06/04 12:17p Yakovlevs
// Defined BIT mask from BIT00 to BIT32 to help set it in chipset
// registers
// 
// 15    7/13/04 10:42a Felixp
// 
// 14    4/22/04 5:39p Markw
// Changed FvReadFile to FvReadPe32Image.
// 
// 13    4/17/04 4:23p Felixp
// 
// 12    4/14/04 11:01a Markw
// Added FvReadFile.
// 
// 11    4/13/04 5:37p Felixp
// 
// 10    4/13/04 5:36p Felixp
// 
// 9     4/11/04 2:49p Felixp
// 
// 8     4/10/04 4:38p Felixp
// 
// 7     4/07/04 12:46a Felixp
// REAL PLATFORM DEBUGGING (lots of bug fixes)
// 
// 6     4/05/04 1:10a Felixp
// 
// 5     3/30/04 3:26p Felixp
// 
// 4     3/30/04 9:32a Markw
// Added DEBUG_MSG macro.
// 
// 3     3/28/04 2:11p Felixp
// 1. PE Loader and some other commonly used code moved to the Library
// 2. Warnings fixed (from now on warning will be treated as error)
// 
// 2     3/24/04 1:29p Felixp
// 
// 1     3/23/04 5:52p Felixp
// 
//**********************************************************************
//<AMI_FHDR_START>
//
// Name:	AmiDxeLib.h
//
// Description:	
//
//<AMI_FHDR_END>
//**********************************************************************
#ifndef __AMI_DXE_LIB__H__
#define __AMI_DXE_LIB__H__
#ifdef __cplusplus
extern "C" {
#endif
#include <amilib.h>
#include <Dxe.h>
#include <Protocol/FirmwareVolume.h>
#include <Protocol/HiiUtilities.h>
#include <Protocol/SmmBase.h>
#include <Protocol/SmmBase2.h>
#include <Protocol/BootScriptSave.h>
#if PI_SPECIFICATION_VERSION >= 0x0001000A
#include <Protocol/S3SaveState.h>
#endif

//****************************************************************************/
//		TYPE DECLARATIONS
//****************************************************************************/
//**********************************************************************
//<AMI_THDR_START>
//
// Name: DBE_DATABASE_STRUCT
//
// Fields:	
// ColNum	Type		Description
//	1		UINTN		Initial elements Count of index array to be created
//	2		UINTN		Current RecordCount stored in Database
//	3		UINTN		Number of Indexes in Database
//	4		DBE_INDEX*	Pointerto the indexes information of this Database;
//	5		VOID		*IndexArray;
//
// Description:	Initial structure to hold Database information
//
// Notes:	
//
//<AMI_THDR_END>
//**********************************************************************

typedef struct _DBE_KEY_FIELD DBE_KEY_FIELD;

typedef INTN (EFIAPI *DBE_CMP)(
				IN VOID				*pContext, 
				IN VOID				*pRecord1,
				IN VOID				*pRecord2
);

struct _DBE_KEY_FIELD {
	DBE_CMP	RRcmp;
	DBE_CMP	KRcmp;
	VOID *pContext;
};

typedef struct _DBE_OFFSET_KEY_CONTEXT {
	UINTN				Offset;
	UINTN				Size;
}DBE_OFFSET_KEY_CONTEXT;

typedef struct _DBE_DATABASE{
	EFI_MEMORY_TYPE			MemoryType;
	UINTN					InitialCount;
	UINTN					RecordCount;
	UINTN					KeyCount;
	DBE_KEY_FIELD			*KeyField;
	VOID					*IndexArray;
}DBE_DATABASE;

struct _DLINK;
typedef struct _DLINK DLINK;
struct _DLINK{
    DLINK *pNext, *pPrev;
};

typedef struct _DLIST{
	UINTN Size;
	DLINK *pHead, *pTail;
} DLIST;

//Structure to store pointers to data
//similar to VECTOR
typedef struct _T_ITEM_LIST {
	UINTN				InitialCount;
	UINTN				ItemCount;					
	VOID				**Items;
}T_ITEM_LIST;

//Structure to reserve CSP resources
typedef struct _CSP_RES_ITEM {
	UINT64				ResBase;
	UINTN				ResLength;
	UINTN				ResType;
	UINT64				Attributes;
} CSP_RES_ITEM;

#pragma pack(push,1)
typedef struct{
    EFI_GUID SubtypeGuid;
	UINT32 NumberOfPackages;
} HII_RESOURCE_SECTION_HEADER;
#pragma pack(pop)

//****************************************************************************/
//		MACROS DECLARATIONS
//****************************************************************************/
#define AMI_IRQ_DMA_MASK_VARIABLE_GUID \
  		{ 0xfc8be767, 0x89f1, 0x4d6e, 0x80, 0x99, 0x6f, 0x2, 0x1e, 0xbc, 0x87, 0xcc }

// {395C33FE-287F-413e-A055-8088C0E1D43E}
#define EFI_SMM_RUNTIME_SERVICES_TABLE_GUID \
    { 0x395c33fe, 0x287f, 0x413e, { 0xa0, 0x55, 0x80, 0x88, 0xc0, 0xe1, 0xd4, 0x3e } }

#define OFFSET_CONTEXT(Type, Field) { EFI_FIELD_OFFSET(Type,Field), EFI_FIELD_SIZE(Type,Field) }
#define OFFSET_KEY(Context) {	&OffsetRRCmp, &OffsetKRCmp, &Context }
#define ADDRESS_KEY {	&AddrRRCmp, &AddrKRCmp, NULL }

#define new(Type) Malloc(sizeof(Type))
#define delete(p) FreePool(p)
#define DListEmpty(pList) (!(pList)->pHead)

#ifdef EFI_DEBUG
#define TRACE(Arguments) Trace Arguments

#ifndef ASSERT
#define ASSERT(Condition) if(!(Condition)) { \
	Trace(-1,"ASSERT in %s on %i: %s\n",__FILE__, __LINE__, #Condition);\
	EFI_DEADLOOP() \
	}
#define ASSERT_EFI_ERROR(Status)  ASSERT(!EFI_ERROR(Status))
#endif

#define VERIFY ASSERT
#define VERIFY_EFI_ERROR ASSERT_EFI_ERROR

#else // EFI_DEBUG==0
#define TRACE(Arguments)

#ifndef ASSERT
#define ASSERT(Condition)
#define ASSERT_EFI_ERROR(Status)

#endif

#define VERIFY(x) (x)
#define VERIFY_EFI_ERROR(x) (x)
#endif

#define PROGRESS_CODE(Code)\
	LibReportStatusCode(EFI_PROGRESS_CODE, Code, 0, NULL, NULL)

#define ERROR_CODE(Code, Severity)\
	LibReportStatusCode(EFI_ERROR_CODE|(Severity), Code, 0, NULL, NULL)

#define DEVICE_PROGRESS_CODE(Code,DeviceHandle)\
	LibReportStatusCode(EFI_PROGRESS_CODE, Code, 0, NULL, NULL)

#define DEVICE_ERROR_CODE(Code, Severity, DeviceHandle)\
	LibReportStatusCode(EFI_ERROR_CODE|(Severity), Code, 0, NULL, NULL)

//Performance Measurement Macros
#ifdef EFI_DXE_PERFORMANCE
#define PERF_START(handle, token, host, ticker) StartMeasure (handle, token, host, ticker)
#define PERF_END(handle, token, host, ticker)   EndMeasure (handle, token, host, ticker)
#define PERF_CODE(code) code
#else
#define PERF_START(handle, token, host, ticker)
#define PERF_END(handle, token, host, ticker)
#define PERF_CODE(code)
#endif

#if (EFI_SPECIFICATION_VERSION > 0x00020000)
#define LANGUAGE_RFC_4646
#define LANGUAGE_CODE_ENGLISH    "en-US"
#else
#define LANGUAGE_ISO_639_2
#define LANGUAGE_CODE_ENGLISH    "eng"
#endif

#define HII_RESOURCES_FFS_SECTION_GUID\
    {0x97e409e6, 0x4cc1, 0x11d9, 0x81, 0xf6, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0}

//the macro serves as an indicator that this version of library
//contains HII-related functions such as HiiLibGetString/HiiLibSetString
#define HII_LIBRARY_FUNCTIONS_SUPPORT

#if (!defined(BACKWARD_COMPATIBLE_MODE) || defined(SMM_BUILD)) && PI_SPECIFICATION_VERSION >= 0x0001000A
#define pSmst pSmstPi
#define pSmmBase pSmmBasePi
#define GetSmstConfigurationTable GetSmstConfigurationTablePi
#define InitSmmHandler InitSmmHandlerPi
#define InitSmmHandlerEx InitSmmHandlerPi
#define InitAmiSmmLib InitAmiSmmLibPi
#else
#define pSmst pSmstFramework
#define pSmmBase pSmmBaseFramework
#define GetSmstConfigurationTable GetSmstConfigurationTableFramework
#define InitSmmHandler InitSmmHandlerFramework
#define InitSmmHandlerEx InitSmmHandlerExFramework
#define InitAmiSmmLib InitAmiSmmLibFramework
#endif

//Boot Script macros
#if PI_SPECIFICATION_VERSION >= 0x0001000A
#if BACKWARD_COMPATIBLE_MODE
#define __PI_BOOT_SCRIPT_MACRO__(This, FrameworkCommand, PiCommand)\
    ( (This==_GetBootScriptSaveInterface())  ? (FrameworkCommand) : (PiCommand) )
#else
#define __PI_BOOT_SCRIPT_MACRO__(This, FrameworkCommand, PiCommand) PiCommand
#endif

// S3SaveStateProtocol
#define BOOT_SCRIPT_S3_IO_WRITE_MACRO(This, Width, Address, Count, Buffer) \
	__PI_BOOT_SCRIPT_MACRO__(This,\
        BOOT_SCRIPT_IO_WRITE_MACRO(This, EFI_ACPI_S3_RESUME_SCRIPT_TABLE, Width, Address, Count, Buffer),\
        ((EFI_S3_SAVE_STATE_PROTOCOL*)This)->Write((EFI_S3_SAVE_STATE_PROTOCOL*)This,EFI_BOOT_SCRIPT_IO_WRITE_OPCODE,Width,(UINT64)Address,(UINTN)Count,Buffer)\
    )

#define BOOT_SCRIPT_S3_IO_READ_WRITE_MACRO(This,Width,Address,Data,DataMask) \
	__PI_BOOT_SCRIPT_MACRO__(This,\
        BOOT_SCRIPT_IO_READ_WRITE_MACRO(This,EFI_ACPI_S3_RESUME_SCRIPT_TABLE,Width,Address,Data,DataMask),\
        ((EFI_S3_SAVE_STATE_PROTOCOL*)This)->Write((EFI_S3_SAVE_STATE_PROTOCOL*)This,EFI_BOOT_SCRIPT_IO_READ_WRITE_OPCODE,Width,(UINT64)Address,Data,DataMask)\
    )

#define BOOT_SCRIPT_S3_MEM_WRITE_MACRO(This,Width,Address,Count,Buffer) \
	__PI_BOOT_SCRIPT_MACRO__(This,\
        BOOT_SCRIPT_MEM_WRITE_MACRO(This,EFI_ACPI_S3_RESUME_SCRIPT_TABLE,Width,Address,Count,Buffer),\
	    ((EFI_S3_SAVE_STATE_PROTOCOL*)This)->Write((EFI_S3_SAVE_STATE_PROTOCOL*)This,EFI_BOOT_SCRIPT_MEM_WRITE_OPCODE,Width,(UINT64)Address,(UINTN)Count,Buffer)\
    )

#define BOOT_SCRIPT_S3_MEM_READ_WRITE_MACRO(This,Width,Address,Data,DataMask) \
	__PI_BOOT_SCRIPT_MACRO__(This,\
        BOOT_SCRIPT_MEM_READ_WRITE_MACRO(This,EFI_ACPI_S3_RESUME_SCRIPT_TABLE,Width,Address,Data,DataMask),\
	    ((EFI_S3_SAVE_STATE_PROTOCOL*)This)->Write((EFI_S3_SAVE_STATE_PROTOCOL*)This,EFI_BOOT_SCRIPT_MEM_READ_WRITE_OPCODE,Width,(UINT64)Address,Data,DataMask)\
    )

#define BOOT_SCRIPT_S3_PCI_CONFIG_WRITE_MACRO(This,Width,Address,Count,Buffer) \
	__PI_BOOT_SCRIPT_MACRO__(This,\
        BOOT_SCRIPT_PCI_CONFIG_WRITE_MACRO(This,EFI_ACPI_S3_RESUME_SCRIPT_TABLE,Width,Address,Count,Buffer),\
	    ((EFI_S3_SAVE_STATE_PROTOCOL*)This)->Write((EFI_S3_SAVE_STATE_PROTOCOL*)This,EFI_BOOT_SCRIPT_PCI_CONFIG_WRITE_OPCODE,Width,(UINT64)Address,(UINTN)Count,Buffer)\
    )

#define BOOT_SCRIPT_S3_PCI_CONFIG_READ_WRITE_MACRO(This,Width,Address,Data,DataMask) \
	__PI_BOOT_SCRIPT_MACRO__(This,\
        BOOT_SCRIPT_PCI_CONFIG_READ_WRITE_MACRO(This,EFI_ACPI_S3_RESUME_SCRIPT_TABLE,Width,Address,Data,DataMask),\
	    ((EFI_S3_SAVE_STATE_PROTOCOL*)This)->Write((EFI_S3_SAVE_STATE_PROTOCOL*)This,EFI_BOOT_SCRIPT_PCI_CONFIG_READ_WRITE_OPCODE,Width,(UINT64)Address,Data,DataMask)\
    )

#define BOOT_SCRIPT_S3_SMBUS_EXECUTE_MACRO(This,SlaveAddress,Command,Operation,PecCheck,Length,Buffer) \
	__PI_BOOT_SCRIPT_MACRO__(This,\
        BOOT_SCRIPT_SMBUS_EXECUTE_MACRO(This,EFI_ACPI_S3_RESUME_SCRIPT_TABLE,SlaveAddress,Command,Operation,PecCheck,Length,Buffer),\
	    ((EFI_S3_SAVE_STATE_PROTOCOL*)This)->Write((EFI_S3_SAVE_STATE_PROTOCOL*)This,EFI_BOOT_SCRIPT_SMBUS_EXECUTE_OPCODE,SlaveAddress,Command,Operation,PecCheck,Length,Buffer)\
    )

#define BOOT_SCRIPT_S3_STALL_MACRO(This,Duration) \
	__PI_BOOT_SCRIPT_MACRO__(This,\
        BOOT_SCRIPT_STALL_MACRO(This,EFI_ACPI_S3_RESUME_SCRIPT_TABLE,Duration),\
	    ((EFI_S3_SAVE_STATE_PROTOCOL*)This)->Write((EFI_S3_SAVE_STATE_PROTOCOL*)This,EFI_BOOT_SCRIPT_STALL_OPCODE,Duration)\
    )

#define BOOT_SCRIPT_S3_DISPATCH_MACRO(This,EntryPoint) \
	__PI_BOOT_SCRIPT_MACRO__(This,\
        BOOT_SCRIPT_DISPATCH_MACRO(This,EFI_ACPI_S3_RESUME_SCRIPT_TABLE,EntryPoint),\
        ((EFI_S3_SAVE_STATE_PROTOCOL*)This)->Write((EFI_S3_SAVE_STATE_PROTOCOL*)This,EFI_BOOT_SCRIPT_DISPATCH_2_OPCODE,(EFI_PHYSICAL_ADDRESS)EntryPoint,NULL)\
    )

#define BOOT_SCRIPT_S3_IO_POLL_MACRO(This,Width,Address,Mask,Data) \
	__PI_BOOT_SCRIPT_MACRO__(This,\
        BOOT_SCRIPT_IO_POLL_MACRO(This,EFI_ACPI_S3_RESUME_SCRIPT_TABLE,Width,Address,Mask,Data),\
        ((EFI_S3_SAVE_STATE_PROTOCOL*)This)->Write((EFI_S3_SAVE_STATE_PROTOCOL*)This,EFI_BOOT_SCRIPT_IO_POLL_OPCODE,Width,(UINT64)Address,Data,Mask,(UINT64)-1)\
    )

#define BOOT_SCRIPT_S3_IO_POLL2_MACRO(This,Width,Address,Mask,Data,Delay) \
    This->Write(This,EFI_BOOT_SCRIPT_IO_POLL_OPCODE,Width,(UINT64)Address,Data,Mask,(UINT64)Delay)

#if 0
#define BOOT_SCRIPT_S3_MEM_POLL_MACRO(This,Width,Address,Mask,Data) \
	__PI_BOOT_SCRIPT_MACRO__(This,\
        BOOT_SCRIPT_MEM_POLL_MACRO(This,EFI_ACPI_S3_RESUME_SCRIPT_TABLE,Width,Address,Mask,Data),\
        ((EFI_S3_SAVE_STATE_PROTOCOL*)This)->Write((EFI_S3_SAVE_STATE_PROTOCOL*)This,EFI_BOOT_SCRIPT_MEM_POLL_OPCODE,Width,(UINT64)Address,Data,Mask,(UINT64)-1)\
    )

#define BOOT_SCRIPT_S3_MEM_POLL2_MACRO(This,Width,Address,Mask,Data,Delay) \
    This->Write(This,EFI_BOOT_SCRIPT_MEM_POLL_OPCODE,Width,(UINT64)Address,Data,Mask,(UINT64)Delay)
#else
#define BOOT_SCRIPT_S3_MEM_POLL_MACRO(This,Width,Address,Mask,Data) \
	__PI_BOOT_SCRIPT_MACRO__(This,\
        BOOT_SCRIPT_MEM_POLL_MACRO(This,EFI_ACPI_S3_RESUME_SCRIPT_TABLE,Width,Address,Mask,Data),\
        ((EFI_S3_SAVE_STATE_PROTOCOL*)This)->Write((EFI_S3_SAVE_STATE_PROTOCOL*)This,EFI_BOOT_SCRIPT_MEM_POLL_OPCODE,Width,(UINT64)Address,Mask,Data,(UINT64)-1)\
    )

#define BOOT_SCRIPT_S3_MEM_POLL2_MACRO(This,Width,Address,Mask,Data,Delay) \
    This->Write(This,EFI_BOOT_SCRIPT_MEM_POLL_OPCODE,Width,(UINT64)Address,Mask,Data,(UINT64)Delay)
#endif

#define BOOT_SCRIPT_S3_PCI_POLL_MACRO(This,Width,Address,Mask,Data) \
	__PI_BOOT_SCRIPT_MACRO__(This,\
        BOOT_SCRIPT_PCI_POLL_MACRO(This,EFI_ACPI_S3_RESUME_SCRIPT_TABLE,Width,Address,Mask,Data),\
        ((EFI_S3_SAVE_STATE_PROTOCOL*)This)->Write((EFI_S3_SAVE_STATE_PROTOCOL*)This,EFI_BOOT_SCRIPT_PCI_CONFIG_POLL_OPCODE,Width,(UINT64)Address,Data,Mask,(UINT64)-1)\
    )

#define BOOT_SCRIPT_S3_PCI_POLL2_MACRO(This,Width,Address,Mask,Data,Delay) \
    This->Write(This,EFI_BOOT_SCRIPT_PCI_CONFIG_POLL_OPCODE,Width,(UINT64)Address,Data,Mask,(UINT64)Delay)

#define BOOT_SCRIPT_S3_DISPATCH_2_MACRO(This,EntryPoint,Context) \
	This->Write(This,EFI_BOOT_SCRIPT_DISPATCH_2_OPCODE,(EFI_PHYSICAL_ADDRESS)EntryPoint,(EFI_PHYSICAL_ADDRESS)Context)

#define BOOT_SCRIPT_S3_PCI_CONFIG2_WRITE_MACRO(This,Width,Segment,Address,Count,Buffer) \
	This->Write(This,EFI_BOOT_SCRIPT_PCI_CONFIG2_WRITE_OPCODE,Width,(UINT16)Segment,(UINT64)Address,(UINTN)Count,Buffer)

#define BOOT_SCRIPT_S3_PCI_CONFIG2_READ_WRITE_MACRO(This,Width,Segment,Address,Data,DataMask) \
	This->Write(This,EFI_BOOT_SCRIPT_PCI_CONFIG2_READ_WRITE_OPCODE,Width,(UINT16)Segment,(UINT64)Address,Data,DataMask)

#define BOOT_SCRIPT_S3_PCI_CFG2_POLL_MACRO(This,Width,Segment,Address,Mask,Result,Delay) \
    This->Write(This,EFI_BOOT_SCRIPT_PCI_CONFIG2_POLL_OPCODE,Width,(UINT16)Segment,(UINT64)Address,Mask,Result,(UINT64)Delay)

#else // #if PI_SPECIFICATION_VERSION >= 0x0001000A

// BootScriptSave
//************************************************
// S3 specific macros below. Generic macros below.
//************************************************
#define BOOT_SCRIPT_S3_IO_WRITE_MACRO(This,Width,Address,Count,Buffer) \
    BOOT_SCRIPT_IO_WRITE_MACRO(This, EFI_ACPI_S3_RESUME_SCRIPT_TABLE, Width, Address, Count, Buffer)

#define BOOT_SCRIPT_S3_IO_READ_WRITE_MACRO(This,Width,Address,Data,DataMask) \
    BOOT_SCRIPT_IO_READ_WRITE_MACRO(This,EFI_ACPI_S3_RESUME_SCRIPT_TABLE,Width,Address,Data,DataMask)

#define BOOT_SCRIPT_S3_MEM_WRITE_MACRO(This,Width,Address,Count,Buffer) \
    BOOT_SCRIPT_MEM_WRITE_MACRO(This,EFI_ACPI_S3_RESUME_SCRIPT_TABLE,Width,Address,Count,Buffer)

#define BOOT_SCRIPT_S3_MEM_READ_WRITE_MACRO(This,Width,Address,Data,DataMask) \
    BOOT_SCRIPT_MEM_READ_WRITE_MACRO(This,EFI_ACPI_S3_RESUME_SCRIPT_TABLE,Width,Address,Data,DataMask)

#define BOOT_SCRIPT_S3_PCI_CONFIG_WRITE_MACRO(This,Width,Address,Count,Buffer) \
    BOOT_SCRIPT_PCI_CONFIG_WRITE_MACRO(This,EFI_ACPI_S3_RESUME_SCRIPT_TABLE,Width,Address,Count,Buffer)

#define BOOT_SCRIPT_S3_PCI_CONFIG_READ_WRITE_MACRO(This,Width,Address,Data,DataMask) \
    BOOT_SCRIPT_PCI_CONFIG_READ_WRITE_MACRO(This,EFI_ACPI_S3_RESUME_SCRIPT_TABLE,Width,Address,Data,DataMask)

#define BOOT_SCRIPT_S3_SMBUS_EXECUTE_MACRO(This,SlaveAddress,Command,Operation,PecCheck,Length,Buffer) \
    BOOT_SCRIPT_SMBUS_EXECUTE_MACRO(This,EFI_ACPI_S3_RESUME_SCRIPT_TABLE,SlaveAddress,Command,Operation,PecCheck,Length,Buffer)

#define BOOT_SCRIPT_S3_STALL_MACRO(This,Duration) \
    BOOT_SCRIPT_STALL_MACRO(This,EFI_ACPI_S3_RESUME_SCRIPT_TABLE,Duration)

#define BOOT_SCRIPT_S3_DISPATCH_MACRO(This,EntryPoint) \
    BOOT_SCRIPT_DISPATCH_MACRO(This,EFI_ACPI_S3_RESUME_SCRIPT_TABLE,EntryPoint)

//OEM
#define BOOT_SCRIPT_S3_IO_POLL_MACRO(This,Width,Address,Mask,Result) \
    BOOT_SCRIPT_IO_POLL_MACRO(This,EFI_ACPI_S3_RESUME_SCRIPT_TABLE,Width,Address,Mask,Result)

#define BOOT_SCRIPT_S3_MEM_POLL_MACRO(This,Width,Address,Mask,Result) \
    BOOT_SCRIPT_MEM_POLL_MACRO(This,EFI_ACPI_S3_RESUME_SCRIPT_TABLE,Width,Address,Mask,Result)

#define BOOT_SCRIPT_S3_PCI_POLL_MACRO(This,Width,Address,Mask,Result) \
    BOOT_SCRIPT_PCI_POLL_MACRO(This,EFI_ACPI_S3_RESUME_SCRIPT_TABLE,Width,Address,Mask,Result)
#endif // #if PI_SPECIFICATION_VERSION >= 0x0001000A

//****************************************************************************/
//		VARIABLE DECLARATIONS
//****************************************************************************/
extern EFI_SYSTEM_TABLE			*pST;
extern EFI_BOOT_SERVICES		*pBS;
extern EFI_RUNTIME_SERVICES		*pRS;
#if (!defined(BACKWARD_COMPATIBLE_MODE) || defined(SMM_BUILD)) && PI_SPECIFICATION_VERSION >= 0x0001000A
extern EFI_SMM_BASE2_PROTOCOL	*pSmmBasePi;
extern EFI_SMM_SYSTEM_TABLE2	*pSmstPi;
#else
extern EFI_SMM_BASE_PROTOCOL	*pSmmBaseFramework;
extern EFI_SMM_SYSTEM_TABLE		*pSmstFramework;
#endif
extern EFI_HANDLE               TheImageHandle;
extern EFI_GUID					guidDevicePath;
extern EFI_GUID					guidFV;
//****************************************************************************/
//		FUNCTION DECLARATIONS
//****************************************************************************/
VOID * GetEfiConfigurationTable(
	IN EFI_SYSTEM_TABLE *SystemTable,
	IN EFI_GUID			*Guid
);

DBE_DATABASE* DbeCreateDatabase(UINTN KeyCount, UINTN InitialCount);

EFI_STATUS DbeInsert(DBE_DATABASE *Database,VOID* Record);

EFI_STATUS DbeLocateKey(IN DBE_DATABASE *Database,IN UINTN KeyNo,IN	VOID *KeyValue,OUT VOID	**Record,OUT INT8 *Vicinity, OPTIONAL OUT	UINTN *RecordIndex);

EFI_STATUS DbeGoToIndex(IN DBE_DATABASE	*Database,IN UINTN KeyNo, IN INTN Index, OUT VOID **Record);

EFI_STATUS DbeDelete(IN DBE_DATABASE *Database, IN VOID* Data, BOOLEAN FreeData);

INTN OffsetRRCmp(
	IN VOID *pContext, IN VOID *pRecord1, IN VOID *pRecord2
);

INTN OffsetKRCmp(
	IN VOID *pContext, IN VOID *pKey, IN VOID *pRecord
);

INTN AddrRRCmp(
	IN VOID* *pContext, VOID *pRecord1, VOID *pRecord2
);

INTN AddrKRCmp(
	IN DBE_OFFSET_KEY_CONTEXT *pContext, VOID *pKey, VOID *pRecord
);

//List functions
VOID DListInit(DLIST* pList);
VOID DListAdd(DLIST* pList, DLINK* pElement);
VOID DListDelete(DLIST* pList, DLINK* pElement);
VOID DListInsert(DLIST* pList, DLINK* pElement, DLINK* pAfter);

/*
EFI_STATUS DbeAddIndexKeyEntry(DBE_DATABASE *Database, UINTN KeyNo, VOID* Data);

EFI_STATUS DbeNext(IN DBE_DATABASE *Database,IN UINTN KeyNo,IN OUT VOID **Record);

EFI_STATUS DbePrev(IN DBE_DATABASE *Database,IN UINTN KeyNo,IN OUT VOID **Record);

EFI_STATUS DbeFirst(IN DBE_DATABASE *Database,IN UINTN KeyNo, OUT VOID **Record);

EFI_STATUS DbeLast(IN DBE_DATABASE *Database,IN UINTN KeyNo, OUT VOID **Record);

EFI_STATUS DbeDelIndexKeyEntry(IN DBE_DATABASE *Database, IN UINTN KeyNo, IN VOID* Data);

VOID* DbeGetKeyPtrValue(IN DBE_DATABASE *Database, IN UINTN KeyNo, VOID* Data);

VOID* DbeGetKeyPtrAddr(IN DBE_DATABASE *Database, IN UINTN KeyNo, VOID* Data);

VOID* DbeGetKeyPtrPtr(IN DBE_DATABASE *Database, IN UINTN KeyNo, VOID* Data);
*/

#ifdef EFI_DEBUG
void Trace(UINTN /* Level*/, CHAR8 * /*sFormat*/,...);
void PrintDebugMessageVaList(UINTN /* Level*/, CHAR8 * /*sFormat*/, va_list /*ArgList*/);
BOOLEAN GetImageName(EFI_HANDLE ImageHandle, CHAR8 *sName);
#endif
BOOLEAN GetControllerName(EFI_HANDLE Controller, CHAR16 **wsName);

void* Malloc(UINTN Size);

void* MallocZ(UINTN Size);

VOID InitAmiLib(
	IN EFI_HANDLE ImageHandle, IN EFI_SYSTEM_TABLE *SystemTable
);

UINTN DPLength(EFI_DEVICE_PATH_PROTOCOL *pDp);
VOID* DPCopy(EFI_DEVICE_PATH_PROTOCOL *pDp);
VOID* DPAdd(EFI_DEVICE_PATH_PROTOCOL *pDp1, EFI_DEVICE_PATH_PROTOCOL *pDp2);
VOID* DPAddNode(EFI_DEVICE_PATH_PROTOCOL *pDp1, EFI_DEVICE_PATH_PROTOCOL *pDp2);
VOID* DPAddInstance(EFI_DEVICE_PATH_PROTOCOL *pDp1, EFI_DEVICE_PATH_PROTOCOL *pDp2);
VOID* DPGetLastNode(EFI_DEVICE_PATH_PROTOCOL *pDp);
INTN  DPCmp(EFI_DEVICE_PATH_PROTOCOL *pDp1, EFI_DEVICE_PATH_PROTOCOL *pDp2);
VOID* DPCut(EFI_DEVICE_PATH_PROTOCOL *pDp);
BOOLEAN DPIsOneOf(EFI_DEVICE_PATH_PROTOCOL *pAll, EFI_DEVICE_PATH_PROTOCOL *pOne, BOOLEAN ExactMatch);
VOID* DPNextInstance(EFI_DEVICE_PATH_PROTOCOL **ppDp, UINTN *pSize);
VOID* DPCreateNode(UINT8 Type, UINT8 SubType, UINT16 Length);
BOOLEAN DPIsMultiInstance(EFI_DEVICE_PATH_PROTOCOL* pDp);
EFI_DEVICE_PATH_PROTOCOL* DPGetEndNode(EFI_DEVICE_PATH_PROTOCOL *pDp);

EFI_EVENT TimerStart(BOOLEAN *pTimerFlag, UINT64 Delay);
void TimerStop(BOOLEAN TimerFlag, EFI_EVENT Event);

EFI_STATUS FvReadPe32Image (
  IN EFI_GUID	*NameGuid,
  IN OUT VOID	**Buffer,
  IN OUT UINTN	*BufferSize,
  OUT UINT32	*AuthenticationStatus);

EFI_STATUS ReadImage (
	IN BOOLEAN BootPolicy, IN EFI_DEVICE_PATH_PROTOCOL *FilePath,
	IN OUT VOID **ppSource, IN OUT UINTN *pSourceSize OPTIONAL,
	OUT UINTN *pImageSize OPTIONAL,
	OUT EFI_HANDLE *phDevice OPTIONAL, OUT EFI_DEVICE_PATH_PROTOCOL **ppPath OPTIONAL
);

//Tests if region1(s-e) belongs to the region2(S-E)
//returns EFI_ACCESS_DENIED if Belongs=FALSE and region 1 belong to region 2
//returns EFI_ACCESS_DENIED if Belongs=TRUE and region 1 don't belong to region 2
//returns EFI_SUCCESS in all other cases.
EFI_STATUS TestRegions(UINT64 s, UINT64 e, UINT64 S, UINT64 E, BOOLEAN Belongs);

EFI_STATUS AppendItemLst(T_ITEM_LIST *Lst, VOID* pRes);

EFI_STATUS InsertItemLst(T_ITEM_LIST *Lst, VOID* pRes, UINTN ItemIndex);

EFI_STATUS DeleteItemLst(T_ITEM_LIST *Lst, UINTN ItemIndex, BOOLEAN FreeData);

VOID ClearItemLst(T_ITEM_LIST *Lst, BOOLEAN FreeData);

EFI_STATUS CopyItemLst(T_ITEM_LIST *Lst, T_ITEM_LIST **NewLstPtr);

EFI_STATUS GetEfiVariable(
	IN CHAR16 *sName, IN EFI_GUID *pGuid,
	OUT UINT32 *pAttributes OPTIONAL,
	IN OUT UINTN *pDataSize, OUT VOID **ppData
);

EFI_STATUS GetDefaultLang(UINT16 *DefaultLang);

EFI_STATUS ReadImageResource(
	EFI_HANDLE ImageHandle, EFI_GUID *pGuid, 
	VOID **ppData, UINTN *pDataSize
);

EFI_STATUS RegisterProtocolCallback(
	IN EFI_GUID *pProtocol, IN EFI_EVENT_NOTIFY	NotifyFunction,
	IN VOID *pNotifyContext, OUT EFI_EVENT *pEvent,
	OUT VOID **ppRegistration
);

EFI_STATUS LoadResources(
	EFI_HANDLE ImageHandle, UINTN NumberOfCallbacks,
	CALLBACK_INFO *pCallBack, INIT_HII_PACK InitFunction
);

EFI_STATUS LoadStrings(
	EFI_HANDLE ImageHandle, EFI_HII_HANDLE *pHiiHandle
);

EFI_STATUS HiiLibGetString(
	IN EFI_HII_HANDLE HiiHandle, IN STRING_REF StringId, 
	IN OUT UINTN *StringSize, OUT EFI_STRING String
);
EFI_STATUS HiiLibSetString(
	IN EFI_HII_HANDLE HiiHandle, IN STRING_REF StringId, IN EFI_STRING String
);
EFI_STATUS HiiLibPublishPackages(
    IN VOID *PackagePointers, IN UINTN NumberOfPackages, 
    IN EFI_GUID *PackageGuid, IN EFI_HANDLE DriverHandle OPTIONAL,
    OUT EFI_HII_HANDLE *HiiHandle
);
EFI_STATUS HiiLibGetBrowserData(
    IN OUT UINTN *BufferSize, OUT VOID *Buffer, 
    IN CONST EFI_GUID *VarStoreGuid, OPTIONAL 
    IN CONST CHAR16 *VarStoreName  OPTIONAL
);
EFI_STATUS HiiLibSetBrowserData(
    IN UINTN BufferSize, IN VOID *Buffer, 
    IN CONST EFI_GUID *VarStoreGuid, OPTIONAL 
    IN CONST CHAR16 *VarStoreName  OPTIONAL
);
EFI_STATUS HiiLibGetGlyphWidth(
    IN CHAR16 Char, OUT UINT16 *Width
);

EFI_STATUS LibGetDxeSvcTbl(DXE_SERVICES **ppDxe OPTIONAL);

EFI_STATUS LibAllocCspResource(CSP_RES_ITEM *ResTable, UINTN ResCount,
							EFI_HANDLE ImgHandle,EFI_HANDLE CntrHandle);

EFI_STATUS AllocCspResource(DXE_SERVICES *Dxe, CSP_RES_ITEM *ResTable, UINTN ResCount,
							EFI_HANDLE ImgHandle,EFI_HANDLE CntrHandle, BOOLEAN AddSpace);

#if (!defined(BACKWARD_COMPATIBLE_MODE) || defined(SMM_BUILD)) && PI_SPECIFICATION_VERSION >= 0x0001000A
EFI_STATUS InitSmmHandlerPi(
	IN EFI_HANDLE		ImageHandle,
	IN EFI_SYSTEM_TABLE	*SystemTable,
	IN EFI_STATUS		(*InSmmFunction)(EFI_HANDLE,EFI_SYSTEM_TABLE*),
	IN EFI_STATUS		(*NotInSmmFunction)(EFI_HANDLE,EFI_SYSTEM_TABLE *) OPTIONAL
);

VOID* GetSmstConfigurationTablePi(IN EFI_GUID *TableGuid);

EFI_STATUS InitAmiSmmLibPi(
    IN EFI_HANDLE	    ImageHandle,
    IN EFI_SYSTEM_TABLE	*SystemTable
);
#else
EFI_STATUS InitSmmHandlerFramework(
	IN EFI_HANDLE		ImageHandle,
	IN EFI_SYSTEM_TABLE	*SystemTable,
	IN EFI_STATUS		(*InSmmFunction)(EFI_HANDLE,EFI_SYSTEM_TABLE*),
	IN EFI_STATUS		(*NotInSmmFunction)(EFI_HANDLE,EFI_SYSTEM_TABLE *) OPTIONAL
);

EFI_STATUS InitSmmHandlerExFramework(
	IN EFI_HANDLE		ImageHandle,
	IN EFI_SYSTEM_TABLE	*SystemTable,
	IN EFI_STATUS		(*InSmmFunction)(EFI_HANDLE,EFI_SYSTEM_TABLE*),
	IN EFI_STATUS		(*NotInSmmFunction)(EFI_HANDLE,EFI_SYSTEM_TABLE *) OPTIONAL
);

VOID* GetSmstConfigurationTableFramework(IN EFI_GUID *TableGuid);

EFI_STATUS InitAmiSmmLibFramework(
    IN EFI_HANDLE	    ImageHandle,
    IN EFI_SYSTEM_TABLE	*SystemTable
);
#endif

EFI_STATUS CreateReadyToBootEvent(
    IN EFI_TPL NotifyTpl, IN EFI_EVENT_NOTIFY	NotifyFunction,
	IN VOID *pNotifyContext, OUT EFI_EVENT *pEvent
);
EFI_STATUS CreateLegacyBootEvent(
    IN EFI_TPL NotifyTpl, IN EFI_EVENT_NOTIFY	NotifyFunction,
	IN VOID *pNotifyContext, OUT EFI_EVENT *pEvent
);

#if EFI_SPECIFICATION_VERSION>=0x20000
EFI_STATUS LibReportStatusCode(
	IN EFI_STATUS_CODE_TYPE Type, IN EFI_STATUS_CODE_VALUE Value,
	IN UINT32 Instance, IN EFI_GUID *CallerId OPTIONAL,
	IN EFI_STATUS_CODE_DATA *Data OPTIONAL
);
#else
#define LibReportStatusCode pRS->ReportStatusCode
#endif

EFI_STATUS AmiIsaIrqMask(UINT16 *IsaIrqMask, BOOLEAN Get);
EFI_STATUS AmiIsaDmaMask(UINT8 *IsaIrqMask, BOOLEAN Get);

//returns current boot mode
EFI_BOOT_MODE GetBootMode();

//Performance Measurement Functions
EFI_STATUS StartMeasure (
  IN EFI_HANDLE Handle, IN CHAR16 *Token, 
  IN CHAR16 *Host, IN UINT64 Ticker
);

EFI_STATUS EndMeasure (
  IN EFI_HANDLE Handle, IN CHAR16 *Token,
  IN CHAR16 *Host, IN UINT64 Ticker
);

VOID WriteBootToOsPerformanceData();

typedef enum {
    FillOsLoaderLoadImageStart,
    FillOsLoaderStartImageStart,
    FillExitBootServicesEntry,
    FillExitBootServicesExit
} FPDT_FILL_TYPE;

VOID AmiFillFpdt (IN FPDT_FILL_TYPE FieldToFill);

VOID EFIAPI InitAmiRuntimeLib(
    IN EFI_HANDLE ImageHandle, IN EFI_SYSTEM_TABLE *SystemTable,
    IN EFI_EVENT_NOTIFY ExitBsCallback OPTIONAL,
    IN EFI_EVENT_NOTIFY GoVirtualCallback OPTIONAL
);
//The EfiAtRuntime and  EfiGoneVirtual functions will only work 
//if library has been initialized with InitAmiRuntimeLib
BOOLEAN EFIAPI EfiAtRuntime();
BOOLEAN EFIAPI EfiGoneVirtual();

BOOLEAN LanguageCodesEqual(CONST CHAR8* LangCode1, CONST CHAR8* LangCode2);
EFI_STATUS LibInitStatusCodePtr();
#ifdef PEI_BUILD
#define _GetBootScriptSaveInterface() NULL
#else
VOID* _GetBootScriptSaveInterface();
#endif
EFI_STATUS IsValidDevicePath(
    IN EFI_DEVICE_PATH_PROTOCOL *pDp
);
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
