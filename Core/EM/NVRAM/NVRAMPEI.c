//**********************************************************************
//**********************************************************************
//**                                                                  **
//**        (C)Copyright 1985-2013, American Megatrends, Inc.         **
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
// $Header: /Alaska/SOURCE/Core/Modules/NVRAM/NVRAMPEI.c 19    5/22/14 6:05p Oleksiyy $
//
// $Revision: 19 $
//
// $Date: 5/22/14 6:05p $
//**********************************************************************
// Revision History
// ----------------
// $Log: /Alaska/SOURCE/Core/Modules/NVRAM/NVRAMPEI.c $
// 
// 19    5/22/14 6:05p Oleksiyy
// [TAG]  		EIP170545
// [Category]  	Improvement
// [Description]  	Spelling errors corrected.
// [Files]  		NVRAMPEI.c
// 
// 18    1/04/13 10:35a Felixp
// Minor improvement in PeiInitNV: when CreateHob fails, still install the
// PPI.
// 
// 17    12/13/12 6:17p Oleksiyy
// [TAG]  		EIP109422
// [Category]  	Improvement
// [Description]  	Issues found by CppCheck in NVRAM Module part
// [Files]  		NVRAMDXE.c and NVRAMPEI.c
// 
// 16    8/12/11 12:15p Artems
// EIP 64107: Added changes for module to be compliant with UEFI
// specification v 2.3.1
// 
// 15    2/02/10 5:15p Oleksiyy
// EIP 33263 : Hooks for SetVariable, GetVariable and GetNextVarName
// added
// 
// 14    11/24/09 4:05p Oleksiyy
// EIP 26085: Added support to read All the NVRAM variable (including
// defoults) with GetNextVariable in PEI and DXE.
// 
// 13    11/23/09 6:25p Felixp
// 
// 12    11/23/09 4:44p Felixp
// Code to validate NVRAM header fields used by the NVRAM driver is added.
// If problem is found, the header fields are updated with the correct
// values.
// 
// 11    7/10/09 8:50a Felixp
// Code clean  up; comments and function header added
// 
// 10    6/26/09 3:29p Felixp
// Active varstore detection is moved into new IsMainNvramStoreValid
// function in NvramRead.c
// 
// 9     5/21/09 5:39p Felixp
// 1. Disable NVRAM content if it has been corrupted during failed BIOS
// update
// 2. Validate compatibility of the NVRAM data using external hook
// (IsNvramDataCompatible). 
//  Disable incompatible NVRAM content.
// 
// 8     1/16/09 3:39p Felixp
// New Feature. EIP 18483. Interface of the hooks that detect NVRAM
// operational mode is extended.
// NVRAM driver uses platform hooks(IsMfgMode, IsResetConfigMode,
// IsDefaultConfigMode) to detect, which set of configuration values 
// are to be used. In some cases the mode is detected based on value of
// the NVRAM variable.
// Interface of the hook functions is extended. New parameter is added. 
// Pointer to EFI_PEI_READ_ONLY_VARIABLE2_PPI PPI is passed to the hook
// functions. 
// The pointer can be used to read and enumerate existing NVRAM variables.
// 
// 7     10/09/08 11:47a Felixp
// 1. Fault tolerant NVRAM garbage collection support is added.
// Use FAULT_TOLERANT_NVRAM_UPDATE SDL token to enable/disable (disabled
// by default). 
// NOTE: This feature requires upgrade of the Board module. 
// NOTE: This feature requires porting:
// Fault tolerant update requires reserved flash area of size NVRAM_SIZE
// used for back up during NVRAM garbage collection.
// The address of the area is defined by NVRAM_BACKUP_ADDRESS SDL token
// defined in Board.sdl.
// Size and Base addresses of other firmware volumes may need to be
// adjusted to free up space for the NVRAM back up area.
// Default ROM layout expects NVRAM back up area immediately below the
// main NVRAM area.
// For projects with the customized ROM layout Core.mak has to be updated.
// 2. Top level NVRAM function updated to be reentrance-safe.
// NOTE: This feature requires upgrade of the SB module.
// 3. Improved recovery from the flash programming failures and
// corruptions within NVRAM area. 
// 4. More reliable non-fault tolerant garbage collection.
// 
// 6     6/06/08 11:01a Felixp
// 
// 4     2/19/08 11:07p Felixp
// Update in init routine PeiInitNV: during boot with default
// configuration, main NVRAM store is also exposed. This is needed to
// provide current value for variables without defaults.
// 
// 3     9/06/07 12:14a Felixp
// 
// 2     8/31/07 3:44p Felixp
// NVRAM code has been significantly changed to introduce the following
// improvements:
// 1. The code is chaned to always use the same amount of memory. 
// Previous implementation allocated memory as needed, which caused
// occasional S4 problems.
// Plus S4 resume never worked during the very first boot after the
// firmware update.
// 2. Support for NVRAM defaults added.
// NVRAM image with the default values for the Setup variables is now
// generated by the build process.
// The image is generated by the HpkTool (included into AMITSE module
// part). 
// In addition to standard Setup defaults it is also possible
// to generate manufactoring defaults. Support for the manufactoring
// defaults
// is disabled by default and can be enabled using
// MANUFACTURING_MODE_SUPPORT SDL token.
// 3. Support for boot with alternative configurations is added.
// Decision to switch to the alternative configuration
// (alternative set of values for NVRAM variables)
// is based on values returned by the porintg routine in OemPort.c.
// During boot with alternative configurations GetVariable service 
// returns alternative values for the setup-related variables.
// If variable does not have an alternative value, current value is
// returned.
// Two alternative configurations are supported:
// Boot with manufactoring settings(activated when IsMfgMode routine in
// OemPort.c returns TRUE).
// Boot with default settings(activated when IsDefaultConfigMode routine
// in OemPort.c returns TRUE).
// NOTE: This feature requires of the Board module
// 4.NVRAM reset option is added.
// If porting routine IsResetConfigMode in OemPort.c returns TRUE in PEI
// phase, 
// NVRAM content will be reset during initialization of the DXE NVRAM
// driver.
// During reset operation all setup-related variables are reset to their
// default values.
// All other variables are deleted.
// NOTE: This feature requires upgrade of the Board module
// 5.Detection of NVRAM update added.
// NVRAM implementation detects if NVRAM has been updated since the last
// NVRAM call.
// This provides ability to use variables services before and after
// firmware update.
// 6.Overall code clean up and simplification.
// 7.Core Sources are no longer required in order to use NV_SIMULATION
// option.
// 8.PI 1.0 support.
// Support for a PI 1.0 complient variable PPI is added. Old PPI is still
// preserved in this label for backward compatibility.
// New library routines PeiGetVariable and PeiGetNextVariableName are
// created in order to hide the differences between two PPIs.
// It is recommended to update existing code to use new library routines. 
// Support of the old PPI may be dropped in the future versions of Core.
// 9. NVRAM is now packaged as a raw FFS file embedded into the standard
// FV (used to be non-standard FV with raw NVRAM image).
// Validation: New NVRAM code has been validated using SCT and EFI version
// of Windows Server 2008
// Files modified: Core.sdl, Core.mak, AmiPeiLib.h, PeiLib.c,
// ReadOnlyVariable.h, , Token.c, HpkTool.exe, AMITSE.mak, Setup.ini,
//             NVRAM.sdl, NVRAM.mak, NVRAM.h, NVRAMRead.c, NVRAMPEI.c,
// NVRAMDXE.c
// 
// 1     8/24/06 12:38p Felixp
// 
// 3     10/09/05 11:25a Felixp
// Performance measurements added.
// 
// 2     3/04/05 9:42a Mandal
// 
// 1     1/28/05 12:44p Felixp
// 
// 2     1/18/05 3:22p Felixp
// PrintDebugMessage renamed to Trace
// 
// 1     12/27/04 4:08p Felixp
// 
// 3     4/05/04 1:10a Felixp
// 
// 2     4/04/04 2:58p Felixp
// 
// 1     3/29/04 2:32a Felixp
// 
//**********************************************************************
//<AMI_FHDR_START>
//
// Name:	NVRAMPEI.h
//
// Description:	
//
//<AMI_FHDR_END>
//**********************************************************************
#include <PPI/ReadOnlyVariable2.h>
#include <PPI/ReadOnlyVariable.h>
#include <AmiPeiLib.h>
#include "NVRAM.h"

//Defined in CSPLib(OEMPort.c)
BOOLEAN IsMfgMode(
    IN EFI_PEI_SERVICES **PeiServices, 
    IN CONST EFI_PEI_READ_ONLY_VARIABLE2_PPI *ReadVariablePpi
);
BOOLEAN IsResetConfigMode(
    IN EFI_PEI_SERVICES **PeiServices, 
    IN CONST EFI_PEI_READ_ONLY_VARIABLE2_PPI *ReadVariablePpi
);
BOOLEAN IsDefaultConfigMode(
    IN EFI_PEI_SERVICES **PeiServices, 
    IN CONST EFI_PEI_READ_ONLY_VARIABLE2_PPI *ReadVariablePpi
);
BOOLEAN IsNvramDataCompatible(
    IN EFI_PEI_SERVICES **PeiServices,
    IN CONST EFI_PEI_READ_ONLY_VARIABLE2_PPI *ReadVariablePpi
);

//Defined in Tokens.c
extern UINTN NvramAddress;
extern UINTN NvramBackupAddress;
extern const UINTN NvramSize;
extern const BOOLEAN NvSimulation;

typedef struct{
    EFI_PEI_READ_ONLY_VARIABLE2_PPI Ppi;
    UINT32 InfoCount;
    UINT32 LastInfoIndex;
    NVRAM_STORE_INFO NvramInfo[3];
    NVRAM_STORE_INFO *MainInfo;
} VARIABLE_PPI;

//--- GetVariable and GetNextVarName Hooks ------
//============================================================================
// Type definitions
typedef EFI_STATUS (PEI_HOOK_GET_VARIABLE)(
    IN CONST EFI_PEI_READ_ONLY_VARIABLE2_PPI *This,
    IN CONST CHAR16 *VariableName, IN CONST EFI_GUID *VendorGuid,
    OUT UINT32 *Attributes, IN OUT UINTN *DataSize, OUT VOID *Data
);

typedef EFI_STATUS (PEI_HOOK_GET_NEXT_VARIABLE_NAME)(
    IN CONST EFI_PEI_READ_ONLY_VARIABLE2_PPI *This,
    IN OUT UINTN *VariableNameSize,
    IN OUT CHAR16 *VariableName, IN OUT EFI_GUID *VendorGuid
);

//======================================================================
// Global extern variables

extern PEI_HOOK_GET_VARIABLE PEI_GET_VAR_LIST EndOfGetVariableHook;
extern PEI_HOOK_GET_NEXT_VARIABLE_NAME PEI_GET_NEXT_VAR_NAME_LIST EndOfGetNextVarNameHook;

PEI_HOOK_GET_VARIABLE* PeiGetVariableHookList[]=
    {PEI_GET_VAR_LIST NULL};
PEI_HOOK_GET_NEXT_VARIABLE_NAME* PeiGetNextVarNameHookList[]=
    {PEI_GET_NEXT_VAR_NAME_LIST NULL};

EFI_STATUS PeiGetVariableHook(
    IN CONST EFI_PEI_READ_ONLY_VARIABLE2_PPI *This,
    IN CONST CHAR16 *VariableName, IN CONST EFI_GUID *VendorGuid,
    OUT UINT32 *Attributes, IN OUT UINTN *DataSize, OUT VOID *Data
){
    UINTN i;
    EFI_STATUS Result = EFI_UNSUPPORTED;
    for(i=0; PeiGetVariableHookList[i] && (Result == EFI_UNSUPPORTED); i++) 
        Result = PeiGetVariableHookList[i](This,VariableName, VendorGuid,Attributes, DataSize, Data);
    return Result;
}

EFI_STATUS PeiGetNextVarNameHook(
    IN CONST EFI_PEI_READ_ONLY_VARIABLE2_PPI *This,
    IN OUT UINTN *VariableNameSize,
    IN OUT CHAR16 *VariableName, IN OUT EFI_GUID *VendorGuid
){
    UINTN i;
    EFI_STATUS Result = EFI_UNSUPPORTED;
    for(i=0; PeiGetNextVarNameHookList[i] && (Result == EFI_UNSUPPORTED); i++) 
        Result = PeiGetNextVarNameHookList [i](This,VariableNameSize,VariableName, VendorGuid);
    return Result;
}
//---GetVariable and GetNextVarName Hooks END------

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   VarPpiGetVariable
//
// Description: This function searches for a Variable with specific GUID and Name
//
// Input:       IN EFI_PEI_SERVICES **PeiServices - Double pointer to Pei Services instance
//              IN CHAR16 *VariableName - pointer to Var Name in Unicode
//              IN EFI_GUID *VendorGuid - pointer to Var GUID
//              OPTIONAL OUT UINT32* Attributes - Pointer to memory where Attributes will be returned 
//              IN OUT UINTN *DataSize - size of Var - if smaller than actual EFI_BUFFER_TOO_SMALL 
//              will be returned and DataSize will be set to actual size needed
//              OUT VOID *Data - Pointer to memory where Var will be returned
//
// Output:      EFI_STATUS - based on result
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS VarPpiGetVariable(
	IN EFI_PEI_SERVICES **PeiServices,
	IN CHAR16 *VariableName, IN EFI_GUID *VendorGuid,
	OUT UINT32 *Attributes OPTIONAL,
	IN OUT UINTN *DataSize, OUT VOID *Data
)
{
	return PeiGetVariable(
        PeiServices, VariableName, VendorGuid, Attributes, DataSize, Data
    );
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   VarPpiGetNextVariableName
//
// Description: This function searches for Var folowed by the Var with specific name (optional) 
//              and GUID and returns it's Name. 
//
// Input:       IN EFI_PEI_SERVICES **PeiServices - Double pointer to Pei Services instance
//              IN OUT UINTN *VariableNameSize - size of Varname - if smaller than actual EFI_BUFFER_TOO_SMALL 
//              will be returned and DataSize will be set to actual size needed
//              IN OUT CHAR16 *VariableName - pointer where Var Name in Unicode will be stored
//              IN OUT EFI_GUID *VendorGuid - pointer to menory where Var GUID is stored
//
// Output:      EFI_STATUS - based on result
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS VarPpiGetNextVariableName(
	IN EFI_PEI_SERVICES **PeiServices,
	IN OUT UINTN *VariableNameSize,
	IN OUT CHAR16 *VariableName, IN OUT EFI_GUID *VendorGuid
)
{
	return PeiGetNextVariableName(
        PeiServices, VariableNameSize, VariableName, VendorGuid
    );
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   VarPpi2GetVariable
//
// Description: This function searches for Var with specific GUID
//
// Input:       IN CONST EFI_PEI_READ_ONLY_VARIABLE2_PPI *This - pointer to FI_PEI_READ_ONLY_VARIABLE2_PPI
//              IN CHAR16 *VariableName - pointer to Var Name in Unicode
//              IN EFI_GUID *VendorGuid - pointer to Var GUID
//              OPTIONAL OUT UINT32* Attributes - Pointer to memory where Attributes will be returned 
//              IN OUT UINTN *DataSize - size of Var - if smaller than actual EFI_BUFFER_TOO_SMALL 
//              will be returned and DataSize will be set to actual size needed
//              OUT VOID *Data - Pointer to memory where Var will be returned
//
// Output:      EFI_STATUS - based on result
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS VarPpi2GetVariable(
    IN CONST EFI_PEI_READ_ONLY_VARIABLE2_PPI *This,
    IN CONST CHAR16 *VariableName, IN CONST EFI_GUID *VendorGuid,
    OUT UINT32 *Attributes, IN OUT UINTN *DataSize, OUT VOID *Data
)
{
	EFI_STATUS Status;
    VARIABLE_PPI *VarPpi = (VARIABLE_PPI*)This;
    Status = PeiGetVariableHook (
                This, VariableName, VendorGuid, Attributes, DataSize, Data
             );
    if (Status != EFI_UNSUPPORTED) return Status;
	Status = NvGetVariable2(
				(CHAR16*)VariableName, (EFI_GUID*)VendorGuid, Attributes,
				DataSize, Data, VarPpi->InfoCount, VarPpi->NvramInfo
			 );
	return Status;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   NvGetNextVariableName2
//
// Description: This function searches for Var with specific GUID and Enty number 
//              not betwin LastInfoIndex - InfoCount parameter and returns it's Name. 
//
// Input:       IN CONST EFI_PEI_READ_ONLY_VARIABLE2_PPI *This - pointer to FI_PEI_READ_ONLY_VARIABLE2_PPI
//              IN OUT UINTN *VariableNameSize - size of Varname - if smaller than actual EFI_BUFFER_TOO_SMALL 
//              will be returned and DataSize will be set to actual size needed
//              IN OUT CHAR16 *VariableName - pointer where Var Name in Unicode will be stored
//              IN OUT EFI_GUID *VendorGuid - pointer to menory where Var GUID will be stored
//
// Output:      EFI_STATUS - based on result
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS VarPpi2GetNextVariableName(
    IN CONST EFI_PEI_READ_ONLY_VARIABLE2_PPI *This,
    IN OUT UINTN *VariableNameSize,
    IN OUT CHAR16 *VariableName, IN OUT EFI_GUID *VendorGuid
)
{
	EFI_STATUS Status;
    VARIABLE_PPI *VarPpi = (VARIABLE_PPI*)This;
    Status = PeiGetNextVarNameHook (
                This, VariableNameSize, VariableName, VendorGuid
             );
    if (Status != EFI_UNSUPPORTED) return Status;
    Status = NvGetNextVariableName2(
                 VariableNameSize, VariableName, VendorGuid,
                 VarPpi->InfoCount, VarPpi->NvramInfo,
                 &(VarPpi->LastInfoIndex),FALSE
		   );
	return Status;
}

// PPI interface definition
EFI_PEI_READ_ONLY_VARIABLE_PPI VariablePpi = {VarPpiGetVariable, VarPpiGetNextVariableName};
EFI_PEI_READ_ONLY_VARIABLE2_PPI Variable2Ppi = {VarPpi2GetVariable, VarPpi2GetNextVariableName};

// PPI to be installed
EFI_PEI_PPI_DESCRIPTOR VariablePpiListTemplate[] =
{ 
    {
        EFI_PEI_PPI_DESCRIPTOR_PPI,
	    &gEfiPeiReadOnlyVariable2PpiGuid, &Variable2Ppi
    },
    {
        EFI_PEI_PPI_DESCRIPTOR_PPI | EFI_PEI_PPI_DESCRIPTOR_TERMINATE_LIST,
	    &gPeiReadOnlyVariablePpiGuid, &VariablePpi
    }
};

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   PeiInitNV
//
// Description: This function inits NVRAM
//
// Input:       IN EFI_FFS_FILE_HEADER *FfsHeader - pointer to FfsHeader
//              IN EFI_PEI_SERVICES **PeiServices - double pointer to the Pei Sevices structure
//
// Output:      EFI_STATUS - based on result
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS PeiInitNV (
	IN EFI_FFS_FILE_HEADER       *FfsHeader,
	IN EFI_PEI_SERVICES          **PeiServices
)
{
    EFI_STATUS Status;
    EFI_PEI_PPI_DESCRIPTOR *VariablePpiList;
    VARIABLE_PPI *VarPpi;
    UINT32 NvramMode=0;
    NVRAM_HOB *pHob;
    BOOLEAN ResetConfigMode;
    NVRAM_STORE_INFO MainNvram;
    VARIABLE_PPI TmpVarPpi;
    VOID *BackupNvramAddress = (VOID*)NvramBackupAddress;
    BOOLEAN BackupStoreValid;
    BOOLEAN NvramIsCorrupted = FALSE;

    Status = (*PeiServices)->AllocatePool(PeiServices, sizeof(VariablePpiListTemplate)+sizeof(VARIABLE_PPI), &VariablePpiList);
    if (EFI_ERROR(Status)) return Status;
    VariablePpiList[0]=VariablePpiListTemplate[0];
    VariablePpiList[1]=VariablePpiListTemplate[1];
    VarPpi = (VARIABLE_PPI*)(VariablePpiList + 2);
    VariablePpiList[0].Ppi = VarPpi;
    VarPpi->Ppi = Variable2Ppi;
    VarPpi->InfoCount = 0;
    VarPpi->LastInfoIndex = 0;
    MainNvram.NvramAddress = (UINT8*)NvramAddress;
    MainNvram.NvramSize = NvramSize;
    if (!IsMainNvramStoreValid(&MainNvram, BackupNvramAddress,&BackupStoreValid)){
        if (BackupStoreValid){
            VOID *Tmp = BackupNvramAddress;
            BackupNvramAddress = MainNvram.NvramAddress;
            MainNvram.NvramAddress = Tmp;
        }else{
            NvramIsCorrupted = TRUE;
        }
    }
    NvInitInfoBuffer(
        &MainNvram,
        NvramHeaderLength,
        NVRAM_STORE_FLAG_NON_VALATILE
    );
    //Check if FV signature is valid
    NvramIsCorrupted =   NvramIsCorrupted 
                      || ((EFI_FIRMWARE_VOLUME_HEADER*)MainNvram.NvramAddress)->Signature!=FV_SIGNATURE;
    if (NvramIsCorrupted){
        VarPpi->MainInfo = NULL;
        NvramMode=NVRAM_MODE_RESET_CONFIGURATION;
        PEI_TRACE((-1, PeiServices, "PEI: NVRAM header corruption is detected\n"));
    }else{
        TmpVarPpi = *VarPpi;
        TmpVarPpi.NvramInfo[0]=MainNvram;
        TmpVarPpi.MainInfo = &TmpVarPpi.NvramInfo[0];
        TmpVarPpi.InfoCount=1;
    
        if (   IsMfgMode(PeiServices,&TmpVarPpi.Ppi)
            && NvGetDefaultsInfo(
                   MfgDefaults,&MainNvram,&VarPpi->NvramInfo[VarPpi->InfoCount]
               ) != NULL
        ){
            VarPpi->InfoCount++;
            NvramMode|=NVRAM_MODE_MANUFACTORING;
        }
        ResetConfigMode = IsResetConfigMode(PeiServices,&TmpVarPpi.Ppi);
        if (!ResetConfigMode && !IsDefaultConfigMode(PeiServices,&TmpVarPpi.Ppi)){
            VarPpi->NvramInfo[VarPpi->InfoCount]=MainNvram;
            VarPpi->MainInfo = &VarPpi->NvramInfo[VarPpi->InfoCount];
            VarPpi->InfoCount++;
            if (NvGetDefaultsInfo(
                    StdDefaults,&MainNvram,&VarPpi->NvramInfo[VarPpi->InfoCount]
                ) != NULL
            ){
                VarPpi->InfoCount++;
            }
        }else{
            if (NvGetDefaultsInfo(
                    StdDefaults,&MainNvram,&VarPpi->NvramInfo[VarPpi->InfoCount]
                ) != NULL
            ){
                VarPpi->InfoCount++;
            }
            if (ResetConfigMode){
                VarPpi->MainInfo = NULL;
                NvramMode|=NVRAM_MODE_RESET_CONFIGURATION;
            }else{
                VarPpi->NvramInfo[VarPpi->InfoCount]=MainNvram;
                VarPpi->MainInfo = &VarPpi->NvramInfo[VarPpi->InfoCount];
                VarPpi->InfoCount++;
                NvramMode|=NVRAM_MODE_DEFAULT_CONFIGURATION;
            }
        }
        if (!IsNvramDataCompatible(PeiServices, &VarPpi->Ppi)){
            PEI_TRACE((-1, PeiServices, "PEI: Incompatible NVRAM detected\n"));
            VarPpi->MainInfo = NULL;
            VarPpi->InfoCount=0;
        }
    }
    Status=(*PeiServices)->CreateHob(PeiServices, EFI_HOB_TYPE_GUID_EXTENSION, sizeof(NVRAM_HOB),&pHob);
    ASSERT_PEI_ERROR(PeiServices,Status)
	if (!EFI_ERROR(Status)){
	    pHob->Header.Name=AmiNvramHobGuid;
	    pHob->NvramAddress=(EFI_PHYSICAL_ADDRESS)(UINTN)MainNvram.NvramAddress;
	    pHob->BackupAddress = (EFI_PHYSICAL_ADDRESS)(UINTN)BackupNvramAddress;
	    pHob->NvramSize = MainNvram.NvramSize;
	    if (NvSimulation) NvramMode|=NVRAM_MODE_SIMULATION;
	    pHob->NvramMode = NvramMode;
	    pHob->HeaderLength = NvramHeaderLength;
	}
	return (*PeiServices)->InstallPpi(PeiServices,VariablePpiList);
}

//**********************************************************************
//**********************************************************************
//**                                                                  **
//**        (C)Copyright 1985-2013, American Megatrends, Inc.         **
//**                                                                  **
//**                       All Rights Reserved.                       **
//**                                                                  **
//**      5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093        **
//**                                                                  **
//**                       Phone: (770)-246-8600                      **
//**                                                                  **
//**********************************************************************
//**********************************************************************