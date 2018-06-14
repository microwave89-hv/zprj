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
// $Header: /Alaska/Projects/Intel/Haswell/LynxPoint_SharkBay-DT_Crb_1AQQW/Core/CORE_PEI/DxeIpl.c 4     10/25/12 8:50a Wesleychen $
//
// $Revision: 4 $
//
// $Date: 10/25/12 8:50a $
//**********************************************************************
// Revision History
// ----------------
// $Log: /Alaska/Projects/Intel/Haswell/LynxPoint_SharkBay-DT_Crb_1AQQW/Core/CORE_PEI/DxeIpl.c $
// 
// 4     10/25/12 8:50a Wesleychen
//  - Update Core to 4.6.5.4.
//  - Fixed system hang at CKP 0x4F during S3 resume if HT is disabled.
// 
// 45    5/21/12 10:42a Artems
// [TAG]  		EIP87678
// [Category]  	Improvement
// [Description]  	Select ROM image to use on BOOT_ON_FLASH_UPDATE path
// We have two images - one already in flash (old) and one in reflash
// capsule
// We can use either one to boot
// [Files]  		DxeIpl.c
// 
// 44    4/20/12 2:23p Artems
// [TAG]  		EIP87678
// [Category]  	New Feature
// [Description]  	Select image to boot from on flash update boot path -
// either old one (currently in flash) or new one (in recovery capsule)
// [Files]  		Recovery.c DxeIpl.c Core.sdl Tokens.c
// 
// 43    11/01/11 1:57p Felixp
// [TAG]  		EIP 69841 and 71719
// [Category]  	Improvement
// [Description]  	The AMI customizations are removed from the DXE memory
// manager. 
// They are replaced with the Memory Type Information HOB used in Tiano
// projects. 
// This is done to reduces number of descriptors in the memory map 
// and to workaround Windows bug (Windows can't handle memory allocations 
// that happen after the start of the OS loader).
// [Files] CORE_DXE.sdl, Page.c, BDS.c, DxeIpl.c
// 
// 42    7/19/11 11:29a Oleksiyy
// [TAG]  		EIP64108 
// [Category]  	Improvement
// [Description]  	ACPI, convert or update all eModules to be compliant
// with PI 1.2, and UEFI 2.3.1 specifications. 
// [Files]  		AcpiCore.c, mptable.c, AcpiS3Save.c, S3Resume.dxs,
// S3Resume.c, AcpiPeiS3Func.c, BootScriptExecuter.c and DxeIpl.c
// 
// 41    6/02/11 4:49p Artems
// 
// 40    5/13/11 5:12p Artems
// Preserved boot mode when recovery/flash update failed for error
// reporting
// 
// 39    5/05/11 3:44p Artems
// Bugfix: different FV count for PI 0.9 and PI 1.0 specification
// 
// 38    2/15/11 12:35p Artems
// Added workaround so in recovery DXE_CORE ffs will be picked from right
// FV
// 
// 37    2/05/11 3:48p Artems
// Added new ROM layout infrastructure support
// Replaced call to FFS PPI with library function to work both in PI 0.91
// and 1.0 modes
// 
// 36    10/01/10 4:33p Felixp
// Debug message with DXE Core addres is moved to after the instalaltion
// of the END of PEI PPI
// 
// 35    11/13/09 4:32p Felixp
// Buffer overflow protection is added (calls to Sprintf replaced with
// Sprintf_s).
// 
// 34    7/10/09 4:32p Artems
// Added function headers
// 
// 33    5/21/09 5:19p Felixp
// RomLayout support. Call to ReportFvDxeIpl is added.
// 
// 32    5/07/08 12:23p Felixp
// Converted to use new Performance API
// 
// 31    4/18/08 6:27p Felixp
// DXE_CORE_STARTED reported at the very end of PEI phase
// 
// 30    4/20/07 5:10p Felixp
// Status codes added
// 
// 29    4/19/07 1:03p Felixp
// 
// 27    4/17/07 9:07a Felixp
// S3 & Recovery Status Codes removed. They are reported by the S3 &
// Recovery PEIM
// 
// 26    3/13/07 1:46a Felixp
// Error reporting updated to use new PEI_ERROR_CODE macro
// 
// 25    3/12/07 10:26a Felixp
// LoadedImage PPI support added (defined in PI 1.0; used by AmiDebugger)
// 
// 23    11/02/06 10:25p Felixp
// Install EFI_PEI_END_OF_PEI_PHASE_PPI_GUID right before launching DXE
// Core
// 
// 22    8/25/06 10:58a Felixp
// 
// 21    8/24/06 9:43a Felixp
// Preliminary x64 support (work in progress)
// DXE Core interfaces are no longer passed from PEI Core.
// They are linked directly with DXE Core
// 
// 20    6/04/06 10:50p Ambikas
// 
// 19    5/22/06 12:14a Felixp
// More status/error codes added
// 
// 18    3/13/06 9:51a Felixp
// 
// 17    12/01/05 9:52a Felixp
// Recovery Logic changed: RecoveryModule PPI is used. Capsule processing
// is moved to Recovery.c
// 
// 16    10/09/05 11:25a Felixp
// Performance measurements added.
// 
// 15    6/16/05 10:56a Felixp
// 1. Once memory is available, PEI Core PEIMs that created PEIM_LOAD_HOB
// are reallocated to memory.
// 2. ImagePei.c removed
// 3. FileLoader moved from DxeIpl to PEI Core
// 
// 14    6/06/05 1:25p Felixp
// Type parameter removed from AllocatePages to match PEI CIS 0.91
// 
// 13    3/25/05 5:47p Felixp
// 1. S3 boot path: call of S3RestoreConfig added
// 3. Recovery boot path: trace messages added
// 
// 12    3/24/05 6:48p Felixp
// 
// 11    3/22/05 10:03p Felixp
// Recovery Support
// 
// 10    3/17/05 1:54p Felixp
// implementation of S3Resume boot path started
// 
// 9     3/17/05 1:45p Felixp
// Bug fix in memory installed callback (status was not checked)
// 
// 8     3/04/05 9:39a Mandal
// 
// 7     1/25/05 3:37p Felixp
// 
// 6     1/25/05 3:26p Felixp
// Once memory is available DxeIpl realocates itself to memory and
// installs
// LoadFile PPI
// 
// 5     1/22/05 12:29p Felixp
// Bug fix:
// Last parameter to AllocatePages was VOID* instead of
// EFI_PHYSICAL_ADDRESS, which
// resulted in a stack corruption.
// 
// 4     1/22/05 11:29a Felixp
// 
// 2     1/18/05 3:21p Felixp
// PrintDebugMessage renamed to Trace
// 
// 1     12/23/04 9:42a Felixp
// 
// 19    12/20/04 5:10p Felixp
// 
// 18    12/20/04 4:54p Felixp
// 
// 17    12/17/04 6:59p Felixp
// PEI_DEBUG_MSG renamed to PEI_TRACE
// 
// 16    11/24/04 9:38a Felixp
// format of debug message changed
// 
// 15    11/19/04 1:23a Felixp
// 
// 14    11/10/04 5:18p Felixp
// Debug message added
// 
// 13    10/21/04 2:47p Felixp
// Support for DXE Core compression added
// 
// 12    7/13/04 10:42a Felixp
// 
// 11    4/11/04 2:49p Felixp
// 
// 10    4/07/04 12:46a Felixp
// REAL PLATFORM DEBUGGING (lots of bug fixes)
// 
// 9     3/29/04 6:06p Felixp
// 
// 8     3/29/04 5:40p Felixp
// 
// 7     3/28/04 2:11p Felixp
// 1. PE Loader and some other commonly used code moved to the Library
// 2. Warnings fixed (from now on warning will be treated as error)
// 
// 6     3/20/04 12:03p Felixp
// 
// 5     2/19/04 10:08a Felixp
// Debugging code removed.
// 
// 4     2/11/04 12:29a Felixp
// 
// 3     2/10/04 4:02p Felixp
// 
// 2     2/04/04 2:04a Felixp
// work in progress...
// 
// 1     1/28/04 3:23a Felixp
// 
//**********************************************************************
//<AMI_FHDR_START>
//
// Name:	DxeIpl.c
//
// Description:	DXE Core Loader
//
//<AMI_FHDR_END>
//**********************************************************************

//-----------------------------------------------------------------------------

#include <PEI.h>
#include <HOB.h>
#include <AmiHobs.h>
#include <AmiPeiLib.h>
#include <PPI/RecoveryModule.h>
#include <PPI/S3Resume2.h>
#include <PPI/S3Resume.h>
#include <PPI/LoadedImagePpi.h>
#include <Guid/MemoryTypeInformation.h>
#include <token.h>
#include <AmiHobs.h>
#include "Core/CPU/CPU.h"
#include "Core/CPU/CpuCspLib.h"

#define SMM_ASM_FIXUP_SMM_BASE                  0x38002
#define SMM_ASM_FIXUP_IED_ZERO_MEM              0x38029
#define SMM_ASM_BASE_CHANGE_FLAG                0x3808f
#define APIC_SMI                (2 << 8)
#define APIC_LEVEL_ASSERT	    (1 << 14)
#define APIC_NO_SHORT_HAND      (0 << 18)

//-----------------------------------------------------------------------------

//****************************************************************************/
//		TYPE DECLARATIONS
//****************************************************************************/
typedef VOID (EFIAPI *DXE_ENTRY_POINT)(
    IN VOID *HobStart
);

//****************************************************************************/
//		FUNCTION DECLARATIONS
//****************************************************************************/
EFI_STATUS EFIAPI Entry(
	IN EFI_DXE_IPL_PPI            *This,
	IN EFI_PEI_SERVICES           **PeiServices,
	IN EFI_HOB_HANDOFF_INFO_TABLE *HobList
);

#ifdef x64_BUILD_SUPPORT
VOID InitLongMode(
	IN EFI_PEI_SERVICES **PeiServices,
	IN VOID             *Function,
	IN VOID             *Parameter1
);
#endif

//****************************************************************************/
//		VARIABLE DECLARATIONS
//****************************************************************************/
// PPIs
EFI_DXE_IPL_PPI DxeIplPpi = { Entry };
EFI_GUID guidDxeIpl = EFI_DXE_IPL_PPI_GUID;
EFI_GUID guidEndOfPei = EFI_PEI_END_OF_PEI_PHASE_PPI_GUID;

// PPI to be installed
static EFI_PEI_PPI_DESCRIPTOR PpiList[] =
{ 
	{
		EFI_PEI_PPI_DESCRIPTOR_PPI | EFI_PEI_PPI_DESCRIPTOR_TERMINATE_LIST,
		&guidDxeIpl, &DxeIplPpi 
	}
};

static EFI_PEI_PPI_DESCRIPTOR EndOfPpiList[] =
{ 
	{
		EFI_PEI_PPI_DESCRIPTOR_PPI | EFI_PEI_PPI_DESCRIPTOR_TERMINATE_LIST,
		&guidEndOfPei, NULL 
	}
};

EFI_PEI_LOADED_IMAGE_PPI LoadedImagePpi;
EFI_GUID guidLoadedImage = EFI_PEI_LOADED_IMAGE_PPI_GUID;
static EFI_PEI_PPI_DESCRIPTOR LoadedImagePpiDesc[] =
{ 
	{
	    EFI_PEI_PPI_DESCRIPTOR_PPI | EFI_PEI_PPI_DESCRIPTOR_TERMINATE_LIST,
	    &guidLoadedImage, &LoadedImagePpi 
    }
};

// The order of elements in this array is important.
// It defines the order of memory types in the DXE memory map.
// The first array element corresponds to the type with the largest address.
// Keeping boot time memory types at the bottom of the list improves 
// stability of the runtime portions of the memory map
// which is important during S4 resume.
CONST EFI_MEMORY_TYPE_INFORMATION DefaultMemoryTypeInformation[] = {
  { EfiRuntimeServicesCode,     0x30 },
  { EfiRuntimeServicesData,     0x20 },
  { EfiACPIMemoryNVS,           0x60 },
  { EfiACPIReclaimMemory,       0x10 },
  { EfiReservedMemoryType,      0x30 },
  { EfiBootServicesCode,        0x600 },
  { EfiBootServicesData,        0x1500 },
  { EfiMaxMemoryType,           0 }		// indicates the end of the table
};

//****************************************************************************/
//		IMPLEMENTATION
//****************************************************************************/

//<AMI_PHDR_START>
//-----------------------------------------------------------------------------
// Name: LoadDxeCore
//
// Description: 
//  Loads DXE core file into memory
//
// Input:
//	IN EFI_PEI_SERVICES **ppPS - pointer to PEI services structure
//	IN EFI_FIRMWARE_VOLUME_HEADER *pFV - pointer to firmware volume header
//	OUT EFI_FFS_FILE_HEADER **ppFile - pointer to returned FFS file header
//  OUT EFI_PHYSICAL_ADDRESS *pAddress - pointer to returned address where file loaded
//  OUT UINT64 *pSize - pointer to returned file size
//  OUT EFI_PHYSICAL_ADDRESS *pEntry - pointer to returned address of entry point
//
// Output:
//  EFI_STATUS
//	    EFI_SUCCESS	- DXE core loaded successfully
//	    EFI_ERROR - DXE core file not found or cannot be loaded
//		
// Notes:
//-----------------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS LoadDxeCore(
	IN EFI_PEI_SERVICES           **ppPS,
	IN EFI_FIRMWARE_VOLUME_HEADER *pFV, 
	OUT EFI_FFS_FILE_HEADER       **ppFile,
	OUT EFI_PHYSICAL_ADDRESS      *pAddress, 
    OUT UINT64                    *pSize, 
	OUT EFI_PHYSICAL_ADDRESS      *pEntry
)
{
	EFI_STATUS Status;
	*ppFile = NULL;
	// loop via all files
	while(TRUE)
	{
		Status = (*ppPS)->FfsFindNextFile(ppPS, EFI_FV_FILETYPE_DXE_CORE, pFV, ppFile);
		if( EFI_ERROR(Status) ) return Status;
        Status = PeiLoadFile(ppPS,*ppFile,pAddress,pSize,pEntry);
		if( !EFI_ERROR(Status) ) return Status;
	}
}

//<AMI_PHDR_START>
//-----------------------------------------------------------------------------
// Name: S3Resume
//
// Description: 
//  Implementation of S3 wake boot path
//
// Input:
//	IN EFI_PEI_SERVICES **PeiServices - pointer to PEI services structure
//
// Output:
//  EFI_STATUS
//	    EFI_ERROR - S3 resume boot path is failed or cannot be found
//		
// Notes:
//-----------------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS S3Resume(
    IN EFI_PEI_SERVICES **PeiServices
)
{
	EFI_PEI_S3_RESUME2_PPI *pS32;
    EFI_PEI_S3_RESUME_PPI *pS3;
	EFI_PEI_PPI_DESCRIPTOR *pDummy;
	EFI_STATUS Status;
	PEI_TRACE((TRACE_DXEIPL, PeiServices, "S3Resume\n"));
	Status = (*PeiServices)->LocatePpi(PeiServices,&gEfiPeiS3Resume2PpiGuid,0,&pDummy,&pS32);
	if (EFI_ERROR(Status))
    {
        Status = (*PeiServices)->LocatePpi(PeiServices,&gPeiS3ResumePpiGuid,0,&pDummy,&pS3);
        if (EFI_ERROR(Status))
        {
            PEI_ERROR_CODE(PeiServices,PEI_S3_RESUME_PPI_NOT_FOUND,EFI_ERROR_MAJOR);
            return Status;
        }
        PEI_TRACE((TRACE_DXEIPL, PeiServices, "Calling S3RestoreConfig\n"));
	    return pS3->S3RestoreConfig(PeiServices);
    }
	PEI_TRACE((TRACE_DXEIPL, PeiServices, "Calling S3RestoreConfig2\n"));
	return pS32->S3RestoreConfig2(pS32);
}

//<AMI_PHDR_START>
//-----------------------------------------------------------------------------
// Name: Recovery
//
// Description: 
//  Implementation of recovery boot path
//
// Input:
//	IN EFI_PEI_SERVICES **PeiServices - pointer to PEI services structure
//
// Output:
//  EFI_STATUS
//	    EFI_ERROR - recovery capsule not found
//		
// Notes:
//-----------------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS Recovery(
    IN EFI_PEI_SERVICES **PeiServices
)
{
	static EFI_GUID guidRecoveryModule = EFI_PEI_RECOVERY_MODULE_PPI_GUID;
	EFI_PEI_RECOVERY_MODULE_PPI *pRecovery;
	EFI_PEI_PPI_DESCRIPTOR *pDummy;
	EFI_STATUS Status = (*PeiServices)->LocatePpi(PeiServices,&guidRecoveryModule,0,&pDummy,&pRecovery);
	if (EFI_ERROR(Status)){
        PEI_ERROR_CODE(PeiServices,PEI_RECOVERY_PPI_NOT_FOUND,EFI_ERROR_MAJOR);
        return Status;
    }
	return pRecovery->LoadRecoveryCapsule(PeiServices,pRecovery);
}

//defined in ReportFv2.c
EFI_STATUS ReportFV2Dxe(
    IN VOID* RecoveryCapsule OPTIONAL,
	IN EFI_PEI_SERVICES **PeiServices
);

//<AMI_PHDR_START>
//-----------------------------------------------------------------------------
// Name: FindRecoveryBuffer
//
// Description: 
//  Searches for recovery capsule address in HOB
//
// Input:
//	IN EFI_PEI_SERVICES **PeiServices - pointer to PEI services structure
//  OUT VOID **Buffer - pointer where to store found address
//
// Output:
//  EFI_STATUS
//	    EFI_ERROR - recovery capsule not found
//		
// Notes:
//-----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS FindRecoveryBuffer(
    IN EFI_PEI_SERVICES **PeiServices,
    OUT VOID **Buffer
)
{
    EFI_STATUS Status;
    RECOVERY_IMAGE_HOB *RecoveryHob;
    static EFI_GUID RecoveryHobGuid = AMI_RECOVERY_IMAGE_HOB_GUID;

    Status = (*PeiServices)->GetHobList(PeiServices, &RecoveryHob);
    if(EFI_ERROR(Status))
        return Status;     //we are not on recovery boot path

    Status = FindNextHobByGuid(&RecoveryHobGuid, &RecoveryHob);
    if(EFI_ERROR(Status))
        return Status;     //we are not on recovery boot path

    if(RecoveryHob->Status == EFI_SUCCESS && RecoveryHob->Address != NULL) {
        *Buffer = (VOID *)(UINTN)RecoveryHob->Address;
        return EFI_SUCCESS;
    }

    return EFI_NOT_FOUND;
}

extern const BOOLEAN UseNewImage;

//<AMI_PHDR_START>
//-----------------------------------------------------------------------------
// Name: PublishDxeFv
//
// Description: 
//  Publishes Firmware volumes required for DXE phase
//
// Input:
//	IN EFI_PEI_SERVICES **PeiServices - pointer to PEI services structure
//  IN EFI_BOOT_MODE BootMode - current boot mode
//
// Output:
//  UINTN - Number of next firmware volume to start search for DXE_CORE from
//		
// Notes:
//-----------------------------------------------------------------------------
//<AMI_PHDR_END>
UINTN PublishDxeFv(
	IN EFI_PEI_SERVICES **PeiServices,
    IN EFI_BOOT_MODE BootMode
)
{
    EFI_STATUS Status;
    UINTN FvNum = 0;
    VOID *RecoveryBuffer = NULL;
	EFI_FIRMWARE_VOLUME_HEADER* pFV;

/* first check for recovery/flashupdate capsule
BOOT_IN_RECOVERY_MODE - actual recovery or flash update via recovery capsule on disk (in latter case
boot mode will be changed to BOOT_ON_FLASH_UPDATE after call to Recovery() function)
BOOT_ON_FLASH_UPDATE - flash update via recovery capsule in memory
*/
    if (BootMode == BOOT_IN_RECOVERY_MODE || BootMode == BOOT_ON_FLASH_UPDATE) {
        Status = Recovery(PeiServices);
		if (!EFI_ERROR(Status)) {
            Status = FindRecoveryBuffer(PeiServices, &RecoveryBuffer);
            (*PeiServices)->GetBootMode(PeiServices, &BootMode); //check if boot mode changed
		}

        if(EFI_ERROR(Status)) {
        /* we can't find recovery capsule, report error */
            PEI_ERROR_CODE(PeiServices, PEI_RECOVERY_FAILED, EFI_ERROR_MAJOR);
        }
    }

    if(RecoveryBuffer != NULL) {
        if(BootMode == BOOT_IN_RECOVERY_MODE || UseNewImage) {
#if PI_SPECIFICATION_VERSION >= 0x00010000
        /* when we're in recovery we publish DXE Fv from recovery buffer, instead of flash */
            while( !EFI_ERROR((*PeiServices)->FfsFindNextVolume(PeiServices, FvNum, &pFV)))
                FvNum++;        //determine how many FVs published already
#endif
            Status = ReportFV2Dxe(RecoveryBuffer, PeiServices);
            if(!EFI_ERROR(Status)) {
                return FvNum;
            } else {
            /* we can't publish recovery capsule, report error */
                PEI_ERROR_CODE(PeiServices, PEI_RECOVERY_FAILED, EFI_ERROR_MAJOR);
            }
        } 
    }

    Status = ReportFV2Dxe(NULL, PeiServices);
    return 0;
}

//<AMI_PHDR_START>
//-----------------------------------------------------------------------------
// Name: Entry
//
// Description: 
//  Implementation of EFI_DXE_IPL_PPI Entry function
//
// Input:
//  IN EFI_DXE_IPL_PPI *This - pointer to PPI instance
//	IN EFI_PEI_SERVICES **PeiServices - pointer to PEI services structure
//  IN EFI_HOB_HANDOFF_INFO_TABLE *HobList - pointer to HOB list
//
// Output:
//  EFI_STATUS
//	    EFI_ERROR - Boot failed
//		
// Notes:
//-----------------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS EFIAPI Entry(
	IN EFI_DXE_IPL_PPI            *This,
	IN EFI_PEI_SERVICES           **PeiServices,
	IN EFI_HOB_HANDOFF_INFO_TABLE *HobList
)
{
	EFI_FIRMWARE_VOLUME_HEADER* pFV;
    UINTN FvNum;
	EFI_PHYSICAL_ADDRESS DxeCoreAddress, DxeCoreEntry;
	UINT64 DxeCoreSize;
	EFI_STATUS Status;
	EFI_FFS_FILE_HEADER* pFile;
	EFI_BOOT_MODE BootMode=(EFI_BOOT_MODE)-1; //set it to invalid value
    EFI_PEI_LOADED_IMAGE_PPI *OldLoadedImagePpi;
    EFI_PEI_PPI_DESCRIPTOR *OldLoadedImageDesc;
#ifdef EFI_DEBUG
	CHAR8 sName[0x100];
#endif
    EFI_MEMORY_TYPE_INFORMATION MemoryInformationBuffer[EfiMaxMemoryType + 1];
    EFI_MEMORY_TYPE_INFORMATION *MemoryInformationPtr = NULL;
    UINTN MemoryInformationSize;
    EFI_HOB_GUID_TYPE *MemoryInformationHob;

	PEI_PERF_START(PeiServices,DXEIPL_TOK, NULL,0);
    PEI_PROGRESS_CODE(PeiServices,PEI_DXE_IPL_STARTED);

	(*PeiServices)->GetBootMode(PeiServices, &BootMode);
	if (BootMode == BOOT_ON_S3_RESUME) {
#ifndef AMI_CPU_S3_PEI_SUPPORT
#define AMI_CPU_S3_PEI_SUPPORT 0
#endif
#if AMI_CPU_S3_PEI_SUPPORT == 0
    {
        VOID *FirstHob;
        SMM_HOB *SmmHob;
        EFI_GUID gSmmHobGuid = SMM_HOB_GUID;
        VOID *SaveBuffer;
        UINT8 ApicId;
        UINT8 i,j;

        (*PeiServices)->GetHobList(PeiServices, &FirstHob);
        SmmHob = (SMM_HOB*)FirstHob;
        while (!EFI_ERROR(Status = FindNextHobByType(EFI_HOB_TYPE_GUID_EXTENSION, &SmmHob)))
        {
            if (guidcmp(&SmmHob->EfiHobGuidType.Name, &gSmmHobGuid) == 0)
                break;
        }
        if (!EFI_ERROR(Status))
        {
            //Allocate memory for temporarly perserve the 3000:8000 data.
            Status = (*PeiServices)->AllocatePool(
                            PeiServices,
                            SmmGetBaseSaveBufferSize(),
                            &SaveBuffer
                            );
            ASSERT_PEI_ERROR(PeiServices, Status);

            SmmSetupDefaultHandler(SaveBuffer, SmmHob);

            for (i = 0, j = 0; i < SmmHob->NumCpus; ++i)
            {
                *(UINT32*)SMM_ASM_FIXUP_SMM_BASE = (UINT32)SmmHob->SmmBase[i];
                *(UINT8*)SMM_ASM_BASE_CHANGE_FLAG = 0;  //Initialize Flag

                ApicId = j;
                MemReadWrite32((UINT32*)(LOCAL_APIC_BASE + APIC_ICR_HIGH_REGISTER), ApicId << 24, 0x00ffffff);
                MemReadWrite32((UINT32*)(LOCAL_APIC_BASE + APIC_ICR_LOW_REGISTER),  APIC_NO_SHORT_HAND + APIC_LEVEL_ASSERT + APIC_SMI, 0);

                while (!(*(volatile UINT8*)SMM_ASM_BASE_CHANGE_FLAG))
                {
                        CPULib_Pause();    //Wait on Flag
                }
                ++*(UINT16*)SMM_ASM_FIXUP_IED_ZERO_MEM; //Only 0, for first thread to clear IED memory.

                if (IsHtEnabled())
                {
                    j++;
                }
                else
                {
                    j += 2;
                }
            }

            SmmRemoveDefaultHandler(SaveBuffer);
        }
    }
#endif
		PEI_PERF_END(PeiServices, DXEIPL_TOK, NULL, 0);
		S3Resume(PeiServices);
		//if S3 Resume failed, report error and reset system
        PEI_ERROR_CODE(PeiServices, PEI_S3_RESUME_FAILED, EFI_ERROR_MAJOR);
        (*PeiServices)->ResetSystem(PeiServices);
	} else {
        FvNum = PublishDxeFv(PeiServices, BootMode);
	}

	while( !EFI_ERROR ((*PeiServices)->FfsFindNextVolume (PeiServices, FvNum++, &pFV) ) 
		&& EFI_ERROR(Status=LoadDxeCore(PeiServices,pFV,&pFile,&DxeCoreAddress,&DxeCoreSize,&DxeCoreEntry))
	);
	if (EFI_ERROR(Status))
	{
		PEI_ERROR_CODE(PeiServices,PEI_DXE_CORE_NOT_FOUND,EFI_ERROR_MAJOR);
		PEI_PERF_END(PeiServices,DXEIPL_TOK, NULL,0);
		return Status;		
	}
	//Create module allocation HOB for DXE Core
	CreateHobMemoryAllocationModule(
		PeiServices, DxeCoreAddress, DxeCoreSize, 
		EfiBootServicesCode, &pFile->Name,
		DxeCoreEntry
    );

    // Create a MemoryTypeInformation HOB (used by DXE memory manager)

    // There can only be a single memory type information HOB.
    // Invalidate other HOB instances (if any).
    Status = (*PeiServices)->GetHobList(PeiServices, &MemoryInformationHob);
    ASSERT_PEI_ERROR(PeiServices, Status);
    while (!EFI_ERROR(
        FindNextHobByGuid(&gEfiMemoryTypeInformationGuid, &MemoryInformationHob)
    )) MemoryInformationHob->Header.HobType = EFI_HOB_TYPE_UNUSED;

    MemoryInformationSize = sizeof(MemoryInformationBuffer);

    // In case of S4 resume, use memory type information 
    // from the last full boot (S5 resume).
    // This preserves the memory map across sessions.
    Status = PeiGetVariable (
        PeiServices,
          (BootMode == BOOT_ON_S4_RESUME) 
        ? L"PreviousMemoryTypeInformation"
        : EFI_MEMORY_TYPE_INFORMATION_VARIABLE_NAME,
        &gEfiMemoryTypeInformationGuid,
        NULL, &MemoryInformationSize, MemoryInformationBuffer
    );
    if (EFI_ERROR(Status)){
        MemoryInformationPtr = (EFI_MEMORY_TYPE_INFORMATION*)DefaultMemoryTypeInformation;
        MemoryInformationSize = sizeof(DefaultMemoryTypeInformation);
    }else{
        MemoryInformationPtr=MemoryInformationBuffer;
    }
    Status = (*PeiServices)->CreateHob (
        PeiServices, EFI_HOB_TYPE_GUID_EXTENSION,
        sizeof(EFI_HOB_GUID_TYPE) + MemoryInformationSize,
        &MemoryInformationHob
    );
    if (!EFI_ERROR(Status)) {
        MemoryInformationHob->Name = gEfiMemoryTypeInformationGuid;
        MemCpy( MemoryInformationHob+1, MemoryInformationPtr, MemoryInformationSize);
    }
        

    //Update LoadedImage PPI information
    LoadedImagePpi.ImageAddress = DxeCoreAddress;
    LoadedImagePpi.ImageSize = DxeCoreSize;
    LoadedImagePpi.FileHandle = pFile;
    Status = (*PeiServices)->LocatePpi (
         PeiServices, &guidLoadedImage,
         0, &OldLoadedImageDesc, &OldLoadedImagePpi
    );
    if (!(EFI_ERROR(Status))) { // if Loaded Image PPI was located
        Status = (*PeiServices)->ReInstallPpi (
            PeiServices, OldLoadedImageDesc, LoadedImagePpiDesc
        );
    } else {
		// Loaded Image PPI not found, try installing it again.
   	    Status = (*PeiServices)->InstallPpi(
            PeiServices,LoadedImagePpiDesc
        );
	}
	PEI_PERF_END(PeiServices,DXEIPL_TOK, NULL,0);
	(*PeiServices)->InstallPpi(PeiServices,EndOfPpiList);
#ifdef EFI_DEBUG
	if (!GetName((VOID*)DxeCoreAddress,sName)) Sprintf_s(sName,sizeof(sName),"DXE-Core");
	PeiTrace(TRACE_DXEIPL, PeiServices, "%s.Entry(%X)\n", sName, DxeCoreEntry);
#endif
    PEI_PROGRESS_CODE(PeiServices,DXE_CORE_STARTED);
#ifdef x64_BUILD_SUPPORT
	InitLongMode(
		PeiServices, (VOID*)(UINTN)DxeCoreEntry, HobList
	);
#else
	((DXE_ENTRY_POINT )DxeCoreEntry)(HobList);
#endif
	return EFI_NOT_FOUND;
}

//<AMI_PHDR_START>
//-----------------------------------------------------------------------------
// Name: PeiInitDxeIpl
//
// Description: 
//  DXE loader entry point
//
// Input:
//  IN EFI_FFS_FILE_HEADER *FfsHeader - pointer to FFS file header
//	IN EFI_PEI_SERVICES **PeiServices - pointer to PEI services structure
//
// Output:
//  EFI_STATUS
//	    EFI_SUCCESS - EFI_DXE_IPL_PPI installed successfully
//      EFI_ERROR - error occured during execution
//		
// Notes:
//-----------------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS PeiInitDxeIpl (
	IN EFI_FFS_FILE_HEADER       *FfsHeader,
	IN EFI_PEI_SERVICES          **PeiServices
)
{
	return (*PeiServices)->InstallPpi(PeiServices,PpiList);
}

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
