//**********************************************************************
//**********************************************************************
//**                                                                  **
//**        (C)Copyright 1985-2009, American Megatrends, Inc.         **
//**                                                                  **
//**                       All Rights Reserved.                       **
//**                                                                  **
//**             5555 Oakbrook Pkwy, Norcross, GA 30093               **
//**                                                                  **
//**                       Phone: (770)-246-8600                      **
//**                                                                  **
//**********************************************************************
//**********************************************************************

//**********************************************************************
// $Header: /Alaska/BIN/Modules/ACPI/Template/S3Support/S3Save/AcpiS3Save.c 8     7/11/14 11:36a Oleksiyy $
//
// $Revision: 8 $
//
// $Date: 7/11/14 11:36a $
//**********************************************************************
// Revision History
// ----------------
// $Log: /Alaska/BIN/Modules/ACPI/Template/S3Support/S3Save/AcpiS3Save.c $
// 
// 8     7/11/14 11:36a Oleksiyy
// [TAG]	EIP175962
// [Category]	Improvement
// [Description]	Memory allocation logic made more clear.
// [Files]	AcpiS3Save.c
// 
// 7     7/01/14 4:13p Oleksiyy
// [TAG]	EIP175962
// [Category]	Improvement
// [Description]	Memory type for AcpiGlobalVariable changed to Reserved to
// prevent OS from restoring it on thertain scenarious.
// [Files]	AcpiS3Save.c
// 
// 6     6/05/14 3:22p Oleksiyy
// [TAG]  		EIP165196
// [Category]  	Improvement
// [Description]  	Previous check in updated with better logic.
// [Files]  		AcpiS3Save.c
// 
// 5     6/03/14 6:13p Oleksiyy
// [TAG]  		EIP165196
// [Category]  	Improvement
// [Description]  	Taken care of case when BIOS will be updated with
// preserved NVRAM and AcpiGlobalVariable will still has runtime attribute
// [Files]  		AcpiS3Save.c
// 
// 4     4/22/14 3:35p Oleksiyy
// [TAG]  		EIP165196
// [Category]  	Improvement
// [Description]  	Runtime attribute removed when setting
// AcpiGlobalVariable.
// [Files]  		AcpiS3Save.c
// 
// 3     7/19/11 11:32a Oleksiyy
// [TAG]  		EIP64108 
// [Category]  	Improvement
// [Description]  	ACPI, convert or update all eModules to be compliant
// with PI 1.2, and UEFI 2.3.1 specifications. 
// [Files]  		AcpiCore.c, mptable.c, AcpiS3Save.c, S3Resume.dxs,
// S3Resume.c, AcpiPeiS3Func.c, BootScriptExecuter.c and DxeIpl.c
// 
// 2     4/15/11 5:53p Oleksiyy
// [TAG]  		EIP58481 
// [Category]  	Improvement
// [Description]  	AllocatePages used instead of AllocatePool to make
// AcpiMemoryBase aligned on 4KB boundary
// [Files]  		AcpiS3Save.c
// 
// 1     2/03/11 4:08p Oleksiyy
// [TAG]  		EIP53402 
// [Category]  	Improvement
// [Description]  	Create new label of ACPI with separate S3 Functionality
// [Files]  		S3Save.cif
// S3Save.sdl
// S3Save.mak
// AcpiS3.h
// AcpiS3Save.c
// BootScriptPrivate.h
// BootScriptSave.c
// AcpiS3Save.dxs
// SmmS3Save.dxs
// 
// 19    4/28/10 2:49p Oleksiyy
// EIP 35563  Added logic to handle only ACPI 1.1 case in saving FACS. 
// 
// 18    5/18/09 10:41a Yakovlevs
// Changed token name from S3_BASE_MEMORY to S3_BASE_MEMORY_SIZE for
// better token meaning.
// 
// 17    4/28/09 6:02p Markw
// EIP #16665  -  Unable to allocate enough memory in S3. Added allocation
// of base + memory per cpu.
// 
// 16    3/26/09 4:51p Oleksiyy
// New ACPI Core implementation - improves logic, execution time and
// memory usage of ACPI module.
// 
// 15    10/06/08 2:06p Yakovlevs
// Added NUM_S3_PAGES_RESERVED token support
// 
// 14    4/15/08 9:14p Yakovlevs
// Functions Headers added
// 
// 13    4/09/08 5:13p Yakovlevs
// Make S3Save code remember all possible locations of FACS.
// 
// 12    4/23/07 1:31p Felixp
// Boot Script related code moved from Core to ACPI module.
// PEI code added to S3 Resume PPI. DXE code added to AcpiS3Save driver.
// 
// 11    10/13/06 12:29a Felixp
// UEFI2.0 compliance: use CreateReadyToBootEvent instead of
// CreateEvent(READY_TO_BOOT)
// 
// 10    9/18/06 6:51p Markw
// Fix AcpiGlobalVariable Size below 4GB.
// 
// 9     8/24/06 3:00p Felixp
// x64 support (warnings/errors fixed)
// 
// 7     8/22/05 4:05p Markw
// Removed IDT saving to CPU.
// 
// 6     7/20/05 3:35p Girim
// Fix for S3 Resume.
// 
// 5     5/31/05 6:05p Markw
// Number of pages reported to PEI S3 resume and reserved for windows
// different. Added a #define, so are the same.
// 
// 4     5/31/05 10:26a Markw
// Changed reserving ACPI memory from 32k to 128k.
// 
// 3     5/04/05 12:24p Markw
// Moved structure definitions to AcpiS3.h.
// 
// 2     4/29/05 3:26p Markw
// 
// 1     4/29/05 12:17p Sivagarn
// 
// 5     4/22/05 2:45p Markw
// Only save S3 Resume Info once.
// 
// 4     3/31/05 11:00a Markw
// Storing the FACS table for S3 resume is working.
// 
// 3     3/30/05 2:56p Markw
// Added getting ACPI FACS table.
// 
// 2     3/24/05 5:40p Markw
// 

//<AMI_FHDR_START>
//----------------------------------------------------------------------------
//
//  Name:    AcpiS3Save.c
//
//  Description: ACPI S3 support functions
//
//----------------------------------------------------------------------------
//<AMI_FHDR_END>

#include <Efi.h>
#include <Dxe.h>
#include <Hob.h>
#include <Protocol\BootScriptSave.h>
#include <Protocol\MpService.h>
#include <AmiDxeLib.h>
#include <Acpi20.h>
#include "AcpiS3.h"
#include <token.h>

EFI_BOOT_SCRIPT_SAVE_PROTOCOL   *gBootScriptSave;
EFI_MP_SERVICES_PROTOCOL        *gMpServices;
CHAR16		gAcpiGlobalVariable[] = ACPI_GLOBAL_VARIABLE;

EFI_GUID	gAcpi20TableGuid		= ACPI_20_TABLE_GUID;
EFI_GUID    gAcpi11TAbleGuid 	    = ACPI_10_TABLE_GUID;
EFI_GUID	gEfiBootScriptSaveGuid	= EFI_BOOT_SCRIPT_SAVE_GUID;
EFI_GUID	gEfiAcpiVariableGuid	= EFI_ACPI_VARIABLE_GUID;
EFI_GUID	gHobListGuid			= HOB_LIST_GUID;
EFI_GUID    gEfiMpServicesGuid      = EFI_MP_SERVICES_PROTOCOL_GUID;

//Declaration of Boot Script Save module initializarion routine
EFI_STATUS InitBootScript(
	IN EFI_HANDLE ImageHandle,
	IN EFI_SYSTEM_TABLE *SystemTable
	);


//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//  Procedure:   GetAcpiFacsTable
//
//  Description:
//  This function returns address of memory where FACS ACPI table resides
//
//  Input:
// 	VOID
//
//  Output:
//  EFI_PHYSICAL_ADDRESS - address of FACS table
//
//  Notes:
//  The routine may fail if the FACS table is in a different location for 
//  ACPI 1.0 and ACPI 2.0 (e.g. 1 above 4G and 1 below 4G). WIN98 will read the
//  RSDT, and WINXP will read the XSDT. If the XSDT and RSDT aren't pointing to
//  the same tables, a S3 resume failure will occur.
//  Currently, the variable from Intel only supports one FACS table.
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

VOID GetAcpiFacsTable(EFI_PHYSICAL_ADDRESS *FacsTable)
{
    RSDT_PTR_20 *RSDP = NULL;
    RSDT_20     *RSDT = NULL;
    XSDT_20     *XSDT = NULL;
    FACP_20     *FADT = 0;
    UINT32      i;
    BOOLEAN     Ver1 = FALSE;

	// Initialize each pointer to 0
	for (i = 0; i < 3; i++) FacsTable[i] = 0;

    RSDP = GetEfiConfigurationTable(pST,&gAcpi20TableGuid);
    if (!RSDP) 
    {
        RSDP = GetEfiConfigurationTable(pST,&gAcpi11TAbleGuid);
        Ver1 = TRUE;
    }
    if (!RSDP) return;   

    RSDT = (RSDT_20*)RSDP->RsdtAddr;    // 32-bit pointer table
    if (!Ver1) XSDT = (XSDT_20*)RSDP->XsdtAddr;    // 64-bit pointer table.

	// Get XSDT FACS Pointers
	if (XSDT) {
        UINT32 NumPtrs = (XSDT->Header.Length - sizeof(ACPI_HDR)) / 8;
        for(i = 0; i < NumPtrs; ++i) {
            if (((ACPI_HDR*)XSDT->Ptrs[i])->Signature == 'PCAF') {
                FADT = (FACP_20*)XSDT->Ptrs[i];
				FacsTable[0] = (EFI_PHYSICAL_ADDRESS)FADT->X_FIRMWARE_CTRL;
				FacsTable[1] = (EFI_PHYSICAL_ADDRESS)FADT->FIRMWARE_CTRL;
                break;
            }
        }
    }

	// Get RSDT FACS Pointer
    if (RSDT) {
        UINT32 NumPtrs = (RSDT->Header.Length - sizeof(ACPI_HDR)) / 4;
        for(i = 0; i < NumPtrs; ++i) {
            if (((ACPI_HDR*)RSDT->Ptrs[i])->Signature == 'PCAF') {
                FADT = (FACP_20*)RSDT->Ptrs[i];
                FacsTable[2] = (EFI_PHYSICAL_ADDRESS)FADT->FIRMWARE_CTRL;
				break;
            }
        }
    } 
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//  Procedure:   CallbackReadyToBoot
//
//  Description:
//  This function will be called when ReadyToBoot event will be signaled and 
//  will update data, needed for S3 resume control flow.
//
//  Input:
//  IN EFI_EVENT Event - signalled event
//  IN VOID *Context - calling context
//
//  Output:
//  VOID
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

VOID CallbackReadyToBoot(
	IN EFI_EVENT	Event,
	IN VOID			*Context
)
{
	EFI_HOB_RESOURCE_DESCRIPTOR	*ResDescHob;
	ACPI_VARIABLE_SET		*AcpiVariableSet;
	EFI_PHYSICAL_ADDRESS    AcpiMemoryBase;
	EFI_PHYSICAL_ADDRESS	ScriptAddress;
	UINT64					SystemMemoryLength;
	VOID					*FirstHob;
	EFI_STATUS				Status;
    UINTN                   NumCpus = 1;
    EFI_PHYSICAL_ADDRESS	MaxAddress = 0xFFFFFFFF;

	static BOOLEAN S3ResumeInfo = FALSE;
	if (S3ResumeInfo) return;

    //Get number of CPUs.
	Status = pBS->LocateProtocol(
        &gEfiMpServicesGuid,
        NULL,
        &gMpServices
    );
	ASSERT_EFI_ERROR(Status);
    if (!EFI_ERROR(Status)) {
#if PI_SPECIFICATION_VERSION < 0x0001000A || BACKWARD_COMPATIBLE_MODE && defined(NO_PI_MP_SERVICES_SUPPORT)
        Status = gMpServices->GetGeneralMPInfo(
       	gMpServices, &NumCpus, NULL, NULL, NULL, NULL
        );
#else
        UINTN       NumEnCpus;
        Status = gMpServices->GetNumberOfProcessors(
       	gMpServices, &NumCpus, &NumEnCpus
        );
#endif
 
        ASSERT_EFI_ERROR(Status);
    }

	Status = pBS->AllocatePages(
        AllocateMaxAddress,
        EfiReservedMemoryType,
		EFI_SIZE_TO_PAGES(sizeof(ACPI_VARIABLE_SET)),
		&MaxAddress
	);

	ASSERT_EFI_ERROR(Status);

	AcpiVariableSet = (VOID*)(UINTN)MaxAddress;

	pBS->SetMem(AcpiVariableSet, sizeof(ACPI_VARIABLE_SET),0);

	Status = pBS->LocateProtocol(
		&gEfiBootScriptSaveGuid,
		NULL,
		&gBootScriptSave
		);
	ASSERT_EFI_ERROR(Status);

	Status = gBootScriptSave->CloseTable(
		gBootScriptSave,
		EFI_ACPI_S3_RESUME_SCRIPT_TABLE,
		&ScriptAddress);
	ASSERT_EFI_ERROR(Status);

	// Allocate ACPI reserved memory for S3 resume.
    Status = pBS->AllocatePages (
        AllocateAnyPages,
        EfiACPIMemoryNVS,
        EFI_SIZE_TO_PAGES(S3_BASE_MEMORY_SIZE + S3_MEMORY_SIZE_PER_CPU * NumCpus),
        &AcpiMemoryBase
        );

	ASSERT_EFI_ERROR(Status);
	
	// Calculate the system memory length by memory hobs
	SystemMemoryLength = 0x100000;

	FirstHob = GetEfiConfigurationTable(pST,&gHobListGuid);
	if (!FirstHob) ASSERT_EFI_ERROR(EFI_NOT_FOUND);

	ResDescHob = (EFI_HOB_RESOURCE_DESCRIPTOR*) FirstHob;

	//Find APIC ID Hob.
	while (!EFI_ERROR(Status = FindNextHobByType(EFI_HOB_TYPE_RESOURCE_DESCRIPTOR,&ResDescHob)))
	{
		if (ResDescHob->ResourceType == EFI_RESOURCE_SYSTEM_MEMORY)
		{
			if (ResDescHob->PhysicalStart >= 0x100000)
				SystemMemoryLength += ResDescHob->ResourceLength;
		}
	}
	if (SystemMemoryLength == 0x100000) ASSERT_EFI_ERROR(EFI_NOT_FOUND);

	AcpiVariableSet->AcpiReservedMemoryBase	= (EFI_PHYSICAL_ADDRESS)AcpiMemoryBase;
	AcpiVariableSet->AcpiReservedMemorySize	= S3_BASE_MEMORY_SIZE + S3_MEMORY_SIZE_PER_CPU * (UINT32)NumCpus;
	AcpiVariableSet->AcpiBootScriptTable	= (EFI_PHYSICAL_ADDRESS) ScriptAddress;
	AcpiVariableSet->SystemMemoryLength		= SystemMemoryLength;
	GetAcpiFacsTable(&AcpiVariableSet->AcpiFacsTable[0]);

	Status = pRS->SetVariable(
		gAcpiGlobalVariable,
		&gEfiAcpiVariableGuid,
		EFI_VARIABLE_NON_VOLATILE | EFI_VARIABLE_BOOTSERVICE_ACCESS,
		sizeof(UINT32),
		&AcpiVariableSet
	);
	//In case BIOS was updated with preserved NVRAM and AcpiGlobalVariable still has runtime attribute
	if (Status == EFI_INVALID_PARAMETER)
	{
		Status = pRS->SetVariable(
				gAcpiGlobalVariable,
				&gEfiAcpiVariableGuid,
				0,
				0,
				NULL
			);
		ASSERT_EFI_ERROR(Status);
	
	    Status = pRS->SetVariable(
			    gAcpiGlobalVariable,
			    &gEfiAcpiVariableGuid,
			    EFI_VARIABLE_NON_VOLATILE | EFI_VARIABLE_BOOTSERVICE_ACCESS,
			    sizeof(UINT32),
			    &AcpiVariableSet
		    );
	}

	ASSERT_EFI_ERROR(Status);

	S3ResumeInfo = TRUE;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//  Procedure:   AcpiS3SaveEntryPoint
//
//  Description:
//  This function is ACPI S3 driver entry point 
//
//  Input:
// 	IN EFI_HANDLE ImageHandle - Image handle
// 	IN EFI_SYSTEM_TABLE *SystemTable - pointer to system table
//
//  Output:
//  EFI_SUCCESS - Function executed successfully
//
//  Notes:
//  This function also creates ReadyToBoot event to save data 
//  needed for S3 resume control flow.
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS AcpiS3SaveEntryPoint(
	IN EFI_HANDLE		ImageHandle,
	IN EFI_SYSTEM_TABLE	*SystemTable
	)
{
	EFI_STATUS	Status;

	InitAmiLib(ImageHandle,SystemTable);

    //Initialize Boot Script Save module
    Status = InitBootScript(ImageHandle,SystemTable);

	return Status;
}

//**********************************************************************
//**********************************************************************
//**                                                                  **
//**        (C)Copyright 1985-2009, American Megatrends, Inc.         **
//**                                                                  **
//**                       All Rights Reserved.                       **
//**                                                                  **
//**             5555 Oakbrook Pkwy, Norcross, GA 30093               **
//**                                                                  **
//**                       Phone: (770)-246-8600                      **
//**                                                                  **
//**********************************************************************
//**********************************************************************
