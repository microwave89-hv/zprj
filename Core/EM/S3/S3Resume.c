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
// $Header: /Alaska/Projects/Intel/Haswell/LynxPoint_SharkBay-DT_Crb_1AQQW/Core/EM/S3/S3Resume.c 3     4/16/14 6:18a Chaseliu $
//
// $Revision: 3 $
//
// $Date: 4/16/14 6:18a $
//**********************************************************************
// Revision History
// ----------------
// $Log: /Alaska/Projects/Intel/Haswell/LynxPoint_SharkBay-DT_Crb_1AQQW/Core/EM/S3/S3Resume.c $
// 
// 3     4/16/14 6:18a Chaseliu
// sync to ACPI module 48
// 
// 2     9/18/13 1:04a Thomaschen
// Fix RHEL6.4 S3 resume issue.
// 
// 9     3/03/14 5:04p Oleksiyy
// [TAG]  		EIP154308
// [Category]  	Improvement
// [Description]  	Aptio 4: Intel Doc #542550 4h) FirmwarePerformance EFI
// variable contains address of FPDT ACPI table.
// [Files]  		AcpiCore.c and S3Resume.c
// 
// 8     6/12/12 3:20p Oleksiyy
// TAG]  		EIP90322
// [Category]  	Improvement
// [Description] 	Extern declaradion of gAmiGlobalVariableGuid moved to
// AmiLib.h.
// [Files]  		AmiLib.h, Misc.c, EfiLib.c, AcpiCore.c and S3Resume.c
// 
// 7     6/12/12 11:18a Oleksiyy
// [TAG]  		EIP88889
// [Category]  	Improvement
// [Description]  	FACP ver 5.0 structure added, FPDT mesurment accuracy
// improved.
// [Files]  		ACPI50.h, ACPI.sdl, AcpiCore.c, S3Resume.c, Image.c,
// EfiLib.c
// 
// 6     5/22/12 4:31p Oleksiyy
// [TAG]  		EIP90322
// [Category]  	Bug Fix
// [Severity]  	Normal
// [Symptom]  	ChiefRiver SCT Fail, improper variable FPDT_Variable in
// ACPI module
// [RootCause]  	EFI_GLOBAL_VARIABLE guid is used in non EFI defined
// variable.
// [Solution]  	New guig AMI_GLOBAL_VARIABLE_GUID is created and used.
// [Files]  		AmiLib.h, Misc.c, EfiLib.c, AcpiCore.c and S3Resume.c
// 
// 5     5/08/12 6:05p Oleksiyy
// [TAG]  		EIP89643
// [Category]  	Bug Fix
// [Severity]  	Normal
// [Symptom]  	S3Resume2 Ppi newer installs
// [RootCause]  	EFI_PEI_PPI_DESCRIPTOR_TERMINATE_LIST incorrect usage in
// previous Ppi descriptor entree.
// [Solution]  	EFI_PEI_PPI_DESCRIPTOR_TERMINATE_LISTremoved.
// [Files]  		S3Resume.c
// 
// 4     11/11/11 5:13p Oleksiyy
// [TAG]  		EIP64296 
// [Category]  	New Feature
// [Description]  	Creation and filling of Firmware Performance Data Table
// is added. FirmPerfDataTab.h renamed to ACPI50.h
// [Files]  		AcpiCore.c, EfiLib.c, S3Resume.c and ACPI50.h added.
// 
// 3     11/08/11 4:45p Oleksiyy
// [TAG]  		EIP64296 
// [Category]  	New Feature
// [Description]  	Creation and filling of Firmware Performance Data Table
// is added.
// [Files]  		AcpiCore.c, AmiDxeLib.h, CSM.c, DxeMain.c, EfiLib.c,
// Image.c, S3Resume.c and FirmPerfDataTab.h
// 
// 2     7/19/11 11:33a Oleksiyy
// [TAG]  		EIP64108 
// [Category]  	Improvement
// [Description]  	ACPI, convert or update all eModules to be compliant
// with PI 1.2, and UEFI 2.3.1 specifications. 
// [Files]  		AcpiCore.c, mptable.c, AcpiS3Save.c, S3Resume.dxs,
// S3Resume.c, AcpiPeiS3Func.c, BootScriptExecuter.c and DxeIpl.c
// 
// 1     2/03/11 4:09p Oleksiyy
// [TAG]  		EIP53402 
// [Category]  	Improvement
// [Description]  	Create new label of ACPI with separate S3 Functionality
// [Files]  		S3Restore.cif
// S3Restore.sdl
// S3Restore.mak
// S3Resume.dxs
// AcpiS3Wake.asm
// S3Resume.c
// AcpiPeiS3Func.c
// AcpiPeiS3Func.h
// BootScriptExecuter.c
// 
// 25    11/24/09 5:21p Oleksiyy
// EIP 27605: Added ACPI 4.0 support. 
// 
// 24    3/26/09 4:51p Oleksiyy
// New ACPI Core implementation - improves logic, execution time and
// memory usage of ACPI module.
// 
// 23    10/03/08 3:20p Felixp
// Performance measurement support added
// 
// 19    4/15/08 9:09p Yakovlevs
// Added support to chech for wake vector in all instances of FACS.
// EndOfPEIPhase PPI now installed.
// 
// 18    4/09/08 5:52p Markw
// Install End of PEI PPI.
// 
// 17    8/07/07 2:51p Felixp
// Additional Status Codes added
// 
// 16    5/18/07 11:11a Markw
// Reintialize gdt before calling thunk.
// 
// 15    4/23/07 1:31p Felixp
// Boot Script related code moved from Core to ACPI module.
// PEI code added to S3 Resume PPI. DXE code added to AcpiS3Save driver.
// 
// 14    3/13/07 11:58a Felixp
// Error reporting updated to use new PEI_ERROR_CODE macro
// 
// 13    2/07/07 3:08p Markw
// Add video repost support setup question.
// 
// 12    1/23/07 4:24p Markw
// Added thunk support for a call for S3 video repost.
// 
// 11    4/03/06 4:01p Felixp
// New Super I/O infrastructure Support
// 
// 10    12/12/05 9:25p Yakovlevs
// SIO-specific core surrounded by #ifdefs
// 
// 9     12/05/05 11:32a Yakovlevs
// Disabled Generation of SW SMI in order to switch to ACPI mode. 
// System waking up from S3 with SCI_ENABLE bit ON.
// 
// 8     10/09/05 11:27a Felixp
// Performance measurements added.
// 
// 7     5/27/05 4:23p Markw
// Added Keyboard init.
// 
// 6     5/10/05 2:50p Markw
// Use 16bit selectors for data segment.
// 
// 5     5/07/05 11:53p Markw
// Store GDT in memory. Give pointer to GDT descripteor base/limit to wake
// up.
// 
// 4     5/06/05 5:07p Markw
// Added 16 bit wakeup support.
// 
// 3     5/04/05 12:24p Markw
// Moved structure definitions to AcpiS3.h.
// 
// 2     4/29/05 3:26p Markw
// 
// 1     4/29/05 12:17p Sivagarn
// 
// 5     4/05/05 2:19p Markw
// Added enable ACPI Mode.
// 
// 4     3/31/05 11:11a Markw
// Add wakeup vector support.
// 
// 3     3/28/05 6:01p Markw
// Fixed bug. NVRAM variable is address not data.
// 
// 2     3/27/05 6:36p Markw
// Execute Boot Script supported added.
// 
// 1     3/25/05 5:37p Markw
// 

//<AMI_FHDR_START>
//----------------------------------------------------------------------------
//
// Name:	S3Resume.c
//
// Description: Restore configuration state from S3 resume.
//
//----------------------------------------------------------------------------
//<AMI_FHDR_END>

#include <Pei.h>
#include <Ppi\S3Resume.h>
#include <Ppi\S3Resume2.h>
#include <ppi\BootScriptExecuter.h>
#include <Ppi\ReadOnlyVariable2.h>
#include <AmiPeiLib.h>
#include <token.h>
#include <setup.h>
#include "AcpiS3.h"
#include "AcpiPeiS3Func.h"
#include "AMICSPLIBInc.H"
#include <ACPI50.h>

#pragma pack(1)
typedef struct {
    UINT16   GdtLimit;
    UINT64  *GdtBase;
} PTR_GDT_DESCS;
#pragma pack()

extern UINT32 RealModeThunkStart;
extern UINT32 RealModeThunkSize;

EFI_GUID gEfiPeiS3ResumePpiGuid = EFI_PEI_S3_RESUME_PPI_GUID;
EFI_GUID gEfiPeiBootScriptExecuterPpiGuid = EFI_PEI_BOOT_SCRIPT_EXECUTER_PPI_GUID;
EFI_GUID gEfiPeiEndOfPeiPhasePpiGuid = EFI_PEI_END_OF_PEI_PHASE_PPI_GUID;
extern EFI_GUID gEfiPeiReadOnlyVariable2PpiGuid;
EFI_GUID gEfiSetupGuid = SETUP_GUID;

CHAR16		gSetupVariable[]	= L"Setup";

VOID RealModeThunk(PTR_GDT_DESCS *GdtDesc, UINT32 Firmware_Waking_Vector, BOOLEAN UseCall);
typedef VOID(*REAL_MODE_THUNK_FUNCTION)(PTR_GDT_DESCS*, UINT32, BOOLEAN);
//Boot Script Executer module initialization routine
EFI_STATUS InitBootScriptExecuter(
	IN EFI_FFS_FILE_HEADER	*FfsHeader,
	IN EFI_PEI_SERVICES		**PeiServices
	);
//S3 Resume PPI routine
//Defined in this file
EFI_STATUS S3RestoreConfig(
	IN EFI_PEI_SERVICES **PeiServices
);
EFI_STATUS S3RestoreConfig2(
	IN EFI_PEI_S3_RESUME2_PPI *This
);
//To be copied to memory.
UINT64 gGDT[] = {
	0,					//NULL_SEL
	0x00009a000000ffff,	//CODE_SEL 0x08	 16-bit code selector, limit of 4K
	0x000093000000ffff	//DATA_SEL 0x10, 16-bit data selector Data 0-ffffffff
};

//PPI to be installed
EFI_PEI_S3_RESUME_PPI S3ResumePpi = {S3RestoreConfig};
EFI_PEI_S3_RESUME2_PPI S3ResumePpi2 = {S3RestoreConfig2};

static EFI_PEI_PPI_DESCRIPTOR gPpiList[] = {
  	{EFI_PEI_PPI_DESCRIPTOR_PPI,
    &gEfiPeiS3ResumePpiGuid,
    &S3ResumePpi},

    {(EFI_PEI_PPI_DESCRIPTOR_PPI | EFI_PEI_PPI_DESCRIPTOR_TERMINATE_LIST),
    &gEfiPeiS3Resume2PpiGuid,
    &S3ResumePpi2}
};

static EFI_PEI_PPI_DESCRIPTOR gEndOfPpiList[] = { 
	EFI_PEI_PPI_DESCRIPTOR_PPI | EFI_PEI_PPI_DESCRIPTOR_TERMINATE_LIST,
	&gEfiPeiEndOfPeiPhasePpiGuid,
    NULL 
};

VOID InitLongModeExt(
	IN EFI_PEI_SERVICES **PeiServices,
	IN VOID *Function,
	IN VOID *Parameter1,
	IN VOID *Parameter2,
    IN UINT8 NumMemBits
);

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	S3RestoreConfig
//
// Description:	Restore configuration state from S3 resume.
//
// Input:		EFI_PEI_SERVICES **PeiServices
//
// Output:		EFI_STATUS
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS S3RestoreConfig(
	IN EFI_PEI_SERVICES **PeiServices
)
{
	EFI_STATUS      Status;
    UINT32          i;
	PTR_GDT_DESCS   *GdtDesc;
	UINT64          *Gdt;

	ACPI_VARIABLE_SET                   *AcpiVariableSet;
	EFI_PEI_BOOT_SCRIPT_EXECUTER_PPI    *BootScript;
	EFI_PHYSICAL_ADDRESS                BootScriptTable;
#if S3_VIDEO_REPOST_SUPPORT == 1
	EFI_PEI_READ_ONLY_VARIABLE2_PPI     *ReadOnlyVariable;
	SETUP_DATA                          SetupData;
	BOOLEAN                             IsSetupDataValid;
	UINTN                               VariableSize=sizeof(SETUP_DATA);
#endif
	void(*X_Firmware_Waking_Vector)(); 
	UINT32 Firmware_Waking_Vector;
    UINTN VarSize = sizeof(UINT32);
    EFI_FPDT_STRUCTURE                 *FpdtVar;

	PEI_PERF_START(PeiServices,S3RESUME_TOK,NULL,0);
    PEI_PROGRESS_CODE(PeiServices,PEI_S3_STARTED);
#if S3_VIDEO_REPOST_SUPPORT == 1
	Status = (*PeiServices)->LocatePpi(
		PeiServices,
		&gEfiPeiReadOnlyVariable2PpiGuid,
		0, NULL,
		&ReadOnlyVariable		
	);
	ASSERT_PEI_ERROR(PeiServices, Status);
#endif

	Status = (*PeiServices)->LocatePpi (
		PeiServices,
		&gEfiPeiBootScriptExecuterPpiGuid,
		0,
		NULL,
		&BootScript
		);
	ASSERT_PEI_ERROR (PeiServices, Status);
    if (EFI_ERROR(Status)){
        PEI_ERROR_CODE(PeiServices, PEI_S3_BOOT_SCRIPT_ERROR, EFI_ERROR_MAJOR);
        return Status;
    }

	AcpiVariableSet = GetAcpiS3Info(PeiServices);
    if (!AcpiVariableSet){
		PEI_TRACE((-1, PeiServices, "Smm S3 Resume -- No Acpi Global Variable\n"));
		PEI_ERROR_CODE(PeiServices, PEI_S3_RESUME_ERROR, EFI_ERROR_MAJOR);
        return EFI_NOT_FOUND;
    }

	BootScriptTable = AcpiVariableSet->AcpiBootScriptTable;

#if S3_VIDEO_REPOST_SUPPORT == 1
	VariableSize = sizeof(SETUP_DATA);
	Status = ReadOnlyVariable->GetVariable(
        ReadOnlyVariable,
		gSetupVariable, &gEfiSetupGuid,
		NULL,
		&VariableSize, 	&SetupData
	);
	IsSetupDataValid = !EFI_ERROR(Status);
#endif

    PEI_PROGRESS_CODE(PeiServices,PEI_S3_BOOT_SCRIPT);
	PEI_TRACE((-1, PeiServices, "Smm S3 Resume -- Executing Boot Script Table.\n"));
	Status = BootScript->Execute(
		PeiServices,
		BootScript,
		BootScriptTable,
		NULL
	);
	if (EFI_ERROR(Status))
	{
		PEI_TRACE((-1, PeiServices, "Smm S3 Resume -- Error executing Boot Script Table.\n"));
		PEI_ERROR_CODE(PeiServices, PEI_S3_BOOT_SCRIPT_ERROR, EFI_ERROR_MAJOR);
	}

//for legacy free systems it will be infinite loop

	//keyboard init
	#define KBC_CMDSTS_PORT 0x64
	#define KBC_DATA_PORT   0x60
	#define KBC_IBF			0x02
    if( IoRead8(KBC_CMDSTS_PORT) != 0xff){
    	IoWrite8(KBC_CMDSTS_PORT, 0xaa);
	    for (;;) {
		    if (!(IoRead8(KBC_CMDSTS_PORT) & KBC_IBF)) {
			    break;
		    }
	    }
	}

	_asm cli

    //allocate memory for GDT and copy to Thunk to 16-bit.
	(*PeiServices)->AllocatePool(PeiServices,sizeof(gGDT), &Gdt);
	
	//Allocate memory for descriptor.
	(*PeiServices)->AllocatePool(PeiServices,sizeof(PTR_GDT_DESCS), &GdtDesc);
	GdtDesc->GdtLimit = sizeof(gGDT)-1;
	GdtDesc->GdtBase = Gdt;	

    (*PeiServices)->InstallPpi(PeiServices, gEndOfPpiList);

#if S3_VIDEO_REPOST_SUPPORT == 1
    if (IsSetupDataValid && SetupData.S3ResumeVideoRepost) {
        //The following code executes video option ROM at c000:0003.
        //For the video option ROM, a thunk is needed to 16-bit.
        //The Thunk and the area for 16-bit stack are located starting at 
        //ACPI_THUNK_REAL_MODE_SEGMENT * 16 with a length ACPI_THUNK_STACK_TOP.

        VOID *RealModeThunkSave;

        PEI_PROGRESS_CODE(PeiServices,PEI_S3_VIDEO_REPOST);
        //Allocate memory to perserve the the thunk region.
		Status = (*PeiServices)->AllocatePool(PeiServices, ACPI_THUNK_STACK_TOP, &RealModeThunkSave);
    	ASSERT_PEI_ERROR (PeiServices, Status);

        //Save the thunk and stack region.
        MemCpy(RealModeThunkSave, (VOID*)(ACPI_THUNK_REAL_MODE_SEGMENT * 16), ACPI_THUNK_STACK_TOP);    //Save Region to copy
        //Copy the thunk code.
        MemCpy((VOID*)(ACPI_THUNK_REAL_MODE_SEGMENT * 16), (VOID*)RealModeThunkStart, RealModeThunkSize);

        //Open 0xc0000 region--the video option ROM.
        NBPeiProgramPAMRegisters(
            PeiServices,
            0xc0000,
            0x10000,
            LEGACY_REGION_UNLOCK,
            NULL
        );

        //Call video option rom: C000:0003.
    	for(i = 0; i < sizeof(gGDT)/sizeof(UINT64); ++i) Gdt[i] = gGDT[i];  //Set GDT for Thunk to 16-bit
        ((REAL_MODE_THUNK_FUNCTION)(ACPI_THUNK_REAL_MODE_SEGMENT * 16))(GdtDesc, 0xc0000003, TRUE);

        //Close c000 region
        NBPeiProgramPAMRegisters(
            PeiServices,
            0xc0000,
            0x10000,
            LEGACY_REGION_LOCK,
            NULL
        );

        //Restore region where THUNK and 16-bit stack was copied over.
        MemCpy((VOID*)(ACPI_THUNK_REAL_MODE_SEGMENT * 16), RealModeThunkSave, ACPI_THUNK_STACK_TOP);    //Restore region.
    }
#endif

	PEI_TRACE((-1, PeiServices, "Smm S3 resume -- ACPI Mode Enable.\n"));
	if (!AcpiVariableSet->AcpiFacsTable[0] && \
		!AcpiVariableSet->AcpiFacsTable[1] && \
		!AcpiVariableSet->AcpiFacsTable[2])
	{
		PEI_TRACE((-1, PeiServices, "Smm S3 Resume -- No ACPI FACS Table\n"));
		PEI_ERROR_CODE(PeiServices, PEI_S3_RESUME_ERROR, EFI_ERROR_MAJOR);
	}

	PEI_PERF_END(PeiServices,S3RESUME_TOK,NULL,0);
    PEI_PERF_SAVE_S3_DATA(PeiServices);
    
    Status = PeiGetVariable(
        PeiServices,
		L"FPDT_Variable_NV", &gAmiGlobalVariableGuid,
		NULL, &VarSize, &FpdtVar

    );
    if (!EFI_ERROR (Status))
    {
        if (((PERF_TAB_HEADER*)(UINT8*)(FpdtVar->S3Pointer))->Signature == 0x54503353)
        {
            BASIC_S3_RESUME_PERF_REC    *S3PerRec;
            UINT64                      NanoTime;
            S3PerRec = (BASIC_S3_RESUME_PERF_REC*)((UINT8*)(FpdtVar->S3Pointer) + sizeof(PERF_TAB_HEADER));
            if ((FpdtVar->NanoFreq !=0) && (S3PerRec->Header.PerfRecType == 0)) 
            {
                NanoTime = Div64 (Mul64 (GetCpuTimer (), (UINTN)FpdtVar->NanoFreq), 1000000 , NULL);
            
                S3PerRec->AverageResume = Div64 ((Mul64 (S3PerRec->AverageResume, (UINTN)(S3PerRec->ResumeCount)) + NanoTime), 
                                                        (UINTN)(S3PerRec->ResumeCount + 1), NULL);
                S3PerRec->FullResume = NanoTime;
                S3PerRec->ResumeCount++;
            
            }
        }
    }
    
	//If given control to X_Firmware_Waking_Vector. It will not return.
	// Search each FACS table for a valid vector
	for (i = 0; i < 3; i++ ) {
		if (!AcpiVariableSet->AcpiFacsTable[i]) continue;
		PEI_TRACE((-1, PeiServices, "Smm S3 Resume -- Trying FACS table #%d.\n", i + 1));
		X_Firmware_Waking_Vector = (void(*)())*(VOID**)((UINT8*)AcpiVariableSet->AcpiFacsTable[i] + 24);
		if (X_Firmware_Waking_Vector)
		{
			PEI_TRACE((-1, PeiServices, "Smm S3 Resume -- Waking in protected mode.\n"));
        	PEI_PROGRESS_CODE(PeiServices,PEI_S3_OS_WAKE);
            PEI_TRACE((-1, PeiServices, "Smm S3 Vector %x.\n", X_Firmware_Waking_Vector));
            if (((UINT32*)AcpiVariableSet->AcpiFacsTable[i] + 36) && 1) 
            {
                PEI_TRACE((-1, PeiServices, "Smm S3 Resume -- Waking in protected mode 64 bit enable.\n"));
                InitLongModeExt (PeiServices, X_Firmware_Waking_Vector, NULL, NULL, 12);
            }
            else
			    X_Firmware_Waking_Vector(); // Will not return	
		}

		Firmware_Waking_Vector = *(UINT32*)((UINT8*)AcpiVariableSet->AcpiFacsTable[i] + 12);
		if (Firmware_Waking_Vector)
		{
    	    UINT32  RealModeSegOff;

			PEI_TRACE((-1, PeiServices, "Smm S3 Resume -- Waking in real mode.\n"));
            PEI_TRACE((-1, PeiServices, "Smm S3 Vector %x.\n", Firmware_Waking_Vector));
    	    RealModeSegOff = ((Firmware_Waking_Vector & ~0xf) << 12) + (Firmware_Waking_Vector & 0xf);

    	    //Execute this thunk from ROM.
    		for(i = 0; i < sizeof(gGDT)/sizeof(UINT64); ++i) Gdt[i] = gGDT[i];  //Set GDT for Thunk to 16-bit
        	PEI_PROGRESS_CODE(PeiServices,PEI_S3_OS_WAKE);
			RealModeThunk(GdtDesc, RealModeSegOff, FALSE);	//Will not return.
		}
	}

	PEI_TRACE((-1, PeiServices, "Smm S3 Resume -- No waking vector.\n"));
	PEI_ERROR_CODE(PeiServices, PEI_S3_OS_WAKE_ERROR, EFI_ERROR_MAJOR);

	return EFI_UNSUPPORTED;
}
//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	S3RestoreConfig2
//
// Description:	Restore configuration state from S3 resume.
//
// Input:		EFI_PEI_S3_RESUME2_PPI *This
//
// Output:		EFI_STATUS
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS S3RestoreConfig2(
	IN EFI_PEI_S3_RESUME2_PPI *This
)
{
    EFI_PEI_SERVICES **PeiServices;

    if (This != &S3ResumePpi2) return EFI_INVALID_PARAMETER;

    PeiServices = GetPeiServicesTablePointer ();
    
    return S3RestoreConfig(PeiServices);

}

EFI_STATUS S3ResumeEntryPoint(
  IN EFI_FFS_FILE_HEADER       *FfsHeader,
  IN EFI_PEI_SERVICES          **PeiServices
  )
{
    //Initialize Boot Script Executer module
    InitBootScriptExecuter(FfsHeader,PeiServices);
	return (*PeiServices)->InstallPpi(PeiServices,gPpiList);
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