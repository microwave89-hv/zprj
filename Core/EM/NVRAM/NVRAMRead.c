//**********************************************************************
//**********************************************************************
//**                                                                  **
//**        (C)Copyright 1985-2014, American Megatrends, Inc.         **
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
// $Header: /Alaska/SOURCE/Core/Modules/NVRAM/NVRAMRead.c 32    6/11/14 3:12p Oleksiyy $
//
// $Revision: 32 $
//
// $Date: 6/11/14 3:12p $
//**********************************************************************
// Revision History
// ----------------
// $Log: /Alaska/SOURCE/Core/Modules/NVRAM/NVRAMRead.c $
// 
// 32    6/11/14 3:12p Oleksiyy
// [TAG]  		EIP173026
// [Category]  	Bug Fix
// [Severity]  	Important
// [Symptom]  	With AMITSE 2.17.1245 windows 8.1 (UEFI) does not install
// [RootCause]  	GetNextVariableName was in certain cases returning name
// and GUID of a boot time variable
// [Solution]  	Variable name and GUID of a boot time variable X were
// returned at runtime under the following conditions:
//     - The variable X was present in the default var.store and not
// present in the main var.store
//     - The variable immediately before variable X in the default
// var.store was present in the main var.store
//   The default var.store is a var.store generated at build time that
// contains default values for all setup variables
//     (variables associated with setup controls).
//   The main var.store is the main NVRAM area. Variable is added into a
// main var.store when somebody
//     calls SetVariable.
// [Files]  		NVRAMRead.c
// NVRAMDXE.c
// NVRAM.cif
// 
// 31    4/11/14 5:13p Oleksiyy
// [TAG]  		EIP162446 
// [Category]  	Improvement
// [Description]  	Chm file added.
// [Files]  		NVRAMRead.c
// NVRAM.cif
// 
// 30    1/08/14 5:34p Oleksiyy
// [TAG]  		EIP125555
// [Category]  	Improvement
// [Description]  	A Work-around provided for NvGetNextVariableName2() to
// preserve the original VariableName when returning an
// EFI_BUFFER_TOO_SMALL error from NvGetNameFromNvar().
// [Files]  		NVRANRead.c
// 
// 29    11/29/12 5:10p Felixp
// Minor improvement: Since UEFI Specification versions prior to 2.1
// (0x2000A) are no longer supported,
//   all the "#if EFI_SPECIFICATION_VERSION >= 0x2000A" conditional
// compilation statements are removed.
// Files modified: NVRAM.h, NVRAMRead.c, NVRAMDXE.c
// 
// 28    7/13/11 9:24a Justinj
// [TAG]  		EIP62762
// [Category]  	Improvement
// [Description]  	Optimize NVRAM cache index so that the entire linked
// list is not walked every time a variable is set or retrieved.
// [Files]  		NVRAM.h
// NVRAMRead.c
// NVRAMDXE.c
// 
// 27    5/06/11 6:14p Oleksiyy
// [TAG]  		EIP53253
// [Category]  	Improvement
// [Description]  	To comply with UEFI 2.3.1
// EFI_VARIABLE_TIME_BASED_AUTHENTICATED_WRITE_ACCESS and
// EFI_VARIABLE_APPEND_WRITE attributes handling added.
// [Files]  		NVRAM.h, NVRAMRead.c and NVRAMDXE.c
// 
// 26    9/30/10 4:36p Oleksiyy
// Issue Number:  40356 and 39462
// 
// Category:  New Feature
// 
// Description:  Support for EFI_VARIABLE_AUTHENTICATED_WRITE_ACCESS
// Small fix of previously checked in code.
// 
// Files:  NVRAM. h,  NVRAMRead.c, NVRAMDXE.c
// 
// 25    9/22/10 6:39p Felixp
// Enhancement(EIP 39462 and EIP 40356): 
//   Support of the authenticated update of the NVRAM variables
//   as described in UEFI specification version 2.1 and above. 
// NOTE: The actual authentication is performed by the external SecureMod
// eModule, 
//   which must be in the proejct to use this feature.
// 
// 24    8/18/10 11:08a Oleksiyy
// [TAG]         EIP42324 
// [Category]    BUG FIX
// [Severity]    Normal
// [Symptom]     NVRAM checksum at EFI Variable deletion
// [RootCause]   Deleted variables also were checksummed when NVRAM
// consistency is checked.
// [Solution]    Deleted variables not checksummed any more.
// [Files]       NVRAMRead.c
// 
// 23    12/16/09 5:55p Oleksiyy
// EIP 26085: Added support to read All the NVRAM variable. Final version.
// 
// 22    12/04/09 2:27p Felixp
// NvarEqNvar moved from NvramDxe.c to NvramRead.c
// 
// 21    11/25/09 4:42p Felixp
// NvGetNextVariableName2 changes are rolled back
// 
// 20    11/25/09 4:38p Felixp
// NvGetNextVariableName2 updated.
// 
// 19    11/24/09 4:40p Felixp
// Minor bug fixes
// 
// 18    11/24/09 4:04p Oleksiyy
// EIP 26085: Added support to read All the NVRAM variable (including
// defoults) with GetNextVariable in PEI and DXE.
// 
// 17    11/23/09 11:00p Felixp
// 
// 16    11/23/09 4:44p Felixp
// Code to validate NVRAM header fields used by the NVRAM driver is added.
// If problem is found, the header fields are updated with the correct
// values.
// 
// 15    11/20/09 4:06p Felixp
// NVRAM driver is updated to support UEFI2.1
// EFI_VARIABLE_HARDWARE_ERROR_RECORD attribue.
// 
// 14    11/19/09 4:30p Felixp
// 
// 13    11/18/09 12:10p Oleksiyy
// EIP 30751: Bug fix in the NVRAM record checksum implementation
// 
// 12    8/25/09 4:11p Felixp
// NVRAM Record Checksum Support(EIP 23825) is added.
// Disabled by default.  Enable using NVRAM_RECORD_CHECKSUM_SUPPORT SDL
// token. 
// 
// 11    7/10/09 8:50a Felixp
// Code clean  up; comments and function header added
// 
// 10    6/26/09 3:28p Felixp
// New IsMainNvramStoreValid function is added. 
// The function detects is main NVRAM or backup NVRAM is currently active
// (returns FALSE when backup is active).
// 
// 9     5/14/09 9:36a Felixp
// New feature: SMM version of Runtime Services
//   NVRAM driver is updated to populate SMM runtime table 
//   with the pointers to SMM version of variable services.
// 
// 8     11/18/08 5:45p Felixp
// Bug fix in NvIsVariable and NvGetNextNvar functions.
// Symptoms: False NVRAM corruption detection on systems with 
// NVRAM larger than 64KB during creation or update of the large
// variables.
// Reason: overflow during validation of record size
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
// 6     9/06/07 12:14a Felixp
// 
// 5     8/31/07 3:44p Felixp
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
// 4     4/27/07 7:12p Pavell
// Bug fix in NVGetNextVariableName: GetNextVariable did not return
// EFI_NOT_FOUND after the last variable if the very first operation after
// ExitBootServices was update of the existing NV variable.
// 
// 3     3/18/07 4:08p Felixp
// 1. IsNvramBlock function added
// 2. Clean up
// 
// 2     10/27/06 10:42a Felixp
// Bug fixes for correct work in Virtual Address Space.
// 
// 3     1/20/05 11:37a Felixp
// Component restructurized to support release in binary format
// 
// 2     1/18/05 3:22p Felixp
// PrintDebugMessage renamed to Trace
// 
// 1     12/27/04 4:08p Felixp
// 
// 11    12/09/04 9:02p Felixp
// minor improvements
// 
// 10    8/28/04 1:49a Felixp
// NVRAM Routines fixes
// 
//**********************************************************************
//<AMI_FHDR_START>
//
// Name:	NVRAMRead.c
//
// Description:	NVRAM data area access API
//
//<AMI_FHDR_END>
//**********************************************************************
#include "NVRAM.h"

#define VALID_STATE_FLAGS (\
    EFI_FILE_HEADER_CONSTRUCTION | EFI_FILE_HEADER_VALID |\
    EFI_FILE_DATA_VALID | EFI_FILE_MARKED_FOR_UPDATE)

//Definitions for Variables that are used
//to store nested defaults images
// {4599D26F-1A11-49b8-B91F-858745CFF824}
const EFI_GUID AmiDefaultsVariableGuid = 
    { 0x4599d26f, 0x1a11, 0x49b8, { 0xb9, 0x1f, 0x85, 0x87, 0x45, 0xcf, 0xf8, 0x24 } };
const CHAR16 MfgDefaults[] = L"MfgDefaults";
const CHAR16 StdDefaults[] = L"StdDefaults";
const EFI_GUID AmiNvramHobGuid = NVRAM_HOB_GUID;

//Low level access routines

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   NvGetGuid
//
// Description: This function returns GUID of specified variable. 
//
// Input:       NVAR* pVar - pointer to Var 
//              NVRAM_STORE_INFO *pInfo - pointer to NVRAM store structure
//
// Output:      EFI_GUID* - pionter to the Var GUID
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_GUID* NvGetGuid(NVAR* pVar, NVRAM_STORE_INFO *pInfo)
{
    if (pVar->flags&NVRAM_FLAG_GUID) return (EFI_GUID*)(pVar+1);
    else return pInfo->NvramGuidsAddress-*(UINT8*)(pVar+1);
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   NvGetName
//
// Description: This function returns pointer to the Var name. 
//
// Input:       NVAR* pVar - pointer to the Var 
//
// Output:      VOID* - pionter to the Var name
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID* NvGetName(NVAR* pVar)
{
    return (INT8*)(pVar+1)+(pVar->flags&NVRAM_FLAG_GUID ? sizeof(EFI_GUID) : 1);
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   NvGetDataNvar
//
// Description: This function returns last variable in NVRAM storage. 
//
// Input:       NVAR* pVar - pointer to Var 
//              NVRAM_STORE_INFO *pInfo - pointer to NVRAM store structure
//
// Output:      NVAR* - pointer to the last Var
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
NVAR* NvGetDataNvar(NVAR *pVar, NVRAM_STORE_INFO *pInfo)
{
    NVAR *pLastVar=NULL;
    
    for (
        ; NvIsVariable(pVar,pInfo) //--Check if pVar reccord is correct
        ; pVar = (NVAR*)((UINT8*)pVar + pVar->next)
    )
    {
        if (pVar->next==FLASH_EMPTY_NEXT) return pVar;
        
        pLastVar=pVar;
    }
    
    return pLastVar;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	NvGetExtSize
//
// Description:	This function returs pointer to Ext Size feild in Var
//
// Input:		NVAR* NvStart - pointer to the Var to checksumm
//
// Output:		
//			UINT16* 		Pointer to Ext Size feild in Var
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
VAR_SIZE_TYPE* NvGetExtSize (NVAR* pVar)
{
    return (VAR_SIZE_TYPE*) (((UINT8*) pVar + pVar->size) - sizeof(VAR_SIZE_TYPE));
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	NvGetExtFlags
//
// Description:	This function returs pointer to Ext Flags feild in Var
//
// Input:		NVAR* NvStart - pointer to the Var to checksumm
//
// Output:		
//			UINT8* 		Pointer to Ext Flags feild in Var
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
UINT8* NvGetExtFlags (NVAR* pVar)
{
    return (UINT8*) ((UINT8*) NvGetExtSize (pVar) - *NvGetExtSize (pVar) + sizeof(VAR_SIZE_TYPE));
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	NvCalculateNvarChecksum
//
// Description:	This function calculates and Checks the checksum of the Var
//
// Input:		NVAR* NvStart - pointer to the Var to checksumm
//              BOOLEAN Calculate - if TRUE - skeep checksumm feild in Var
//
// Output:		
//			UINT8 		Checksum value
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
UINT8 NvCalculateNvarChecksum(NVAR* pVar)
{
    UINT8      *p, *Start;
	UINT8		Checksum = 0;

	if (   !(pVar->flags & NVRAM_FLAG_EXT_HEDER)
        || !(*NvGetExtFlags(pVar) & NVRAM_EXT_FLAG_CHECKSUM)
    ) return 0;
    
    //calculate checksum of the variable excluding the header
    Start = (UINT8*)(pVar+1);
	for(p=Start; p < Start+pVar->size - sizeof(NVAR); p++) 
    {
        Checksum += *p; 
    }
    //add variable size
    Start = (UINT8*)&pVar->size;
	for(p=Start; p < Start+sizeof(VAR_SIZE_TYPE); p++) 
    {
        Checksum += *p; 
    }
    //add flags except NVRAM_FLAG_VALID
    Checksum += pVar->flags;

	return 0 - Checksum;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   NvGetData
//
// Description: This function returns last variable in NVRAM storage. 
//
// Input:       NVAR* pVar - pointer to Var 
//              UINTN NameLength - Length of the Var name
//              UINTN* pDataSize - pointer to where the site of data returned will be store
//              NVRAM_STORE_INFO *pInfo - pointer to NVRAM store structure
//
// Output:      VOID* - pointer to the Data
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID* NvGetData(NVAR* pVar, UINTN NameLength, UINTN* pDataSize, NVRAM_STORE_INFO *pInfo)
{
    UINTN DataOffset;
    UINTN ExtSize;

    pVar = NvGetDataNvar(pVar,pInfo);
    
    if (pVar==NULL) return NULL;
    
    DataOffset = sizeof(NVAR);
    
    if (!(pVar->flags&NVRAM_FLAG_DATA_ONLY))
    {
        DataOffset +=  NameLength
                       + (   pVar->flags&NVRAM_FLAG_GUID
                             ? sizeof(EFI_GUID) : 1
                         );
    }
    
    if (pDataSize) 
    {   // if Ext. Header present - get its size
        if (pVar->flags & NVRAM_FLAG_EXT_HEDER) ExtSize = *NvGetExtSize (pVar);
        else ExtSize = 0;
        *pDataSize = pVar->size - DataOffset - ExtSize;
    }
    
    return (INT8*)pVar+DataOffset;
}

//Validation routines
//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   NvIsValid
//
// Description: This function checks if passed Var is valid. 
//
// Input:       NVAR* pVar - pointer to the Var 
//
// Output:      BOOLEAN - TRUE of FALSE based on result
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
BOOLEAN NvIsValid(NVAR* pVar)
{
    return  ((pVar->flags^~FLASH_EMPTY_FLAG)&NVRAM_FLAG_VALID) &&
            !(pVar->flags&NVRAM_FLAG_DATA_ONLY);
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   NvIsVariable
//
// Description: This function checks if pVar reccord is correct. 
//
// Input:       NVAR* pVar - pointer to Var 
//              NVRAM_STORE_INFO *pInfo - pointer to NVRAM store structure
//
// Output:      BOOLEAN - TRUE of FALSE based on result
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
BOOLEAN NvIsVariable(NVAR *pVar, NVRAM_STORE_INFO *pInfo)
{
    return
           pVar->signature==NVAR_SIGNATURE
        && pVar->flags!=FLASH_EMPTY_FLAG
        && !(pVar->flags&~ALL_FLAGS)
        && pVar->size!=FLASH_EMPTY_SIZE && pVar->size>sizeof(NVAR)
        && pVar->size<=(pInfo->pEndOfVars-(UINT8*)pVar)
        && (       pVar->next==FLASH_EMPTY_NEXT
               ||     pVar->next>=pVar->size
                   && pVar->next<=(UINT32)(pInfo->pEndOfVars-(UINT8*)pVar) 
           )
        && (      !(pVar->flags & NVRAM_FLAG_EXT_HEDER)
               || !(*NvGetExtFlags (pVar) & NVRAM_EXT_FLAG_CHECKSUM)
               || !(pVar->flags & NVRAM_FLAG_VALID)
               || !NvCalculateNvarChecksum(pVar)
           )
        ;
}

//Iteration routines
//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   NvGetNextNvar
//
// Description: This function returns the next valid Var after pVar. 
//
// Input:       NVAR* pVar - pointer to Var 
//              NVRAM_STORE_INFO *pInfo - pointer to NVRAM store structure
//
// Output:      NVAR* - pointer to next valid Var after pVar, NULL - if none
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
NVAR* NvGetNextNvar(NVAR* pVar, NVRAM_STORE_INFO *pInfo)
{
    if (!pVar || pVar >= (NVAR*)pInfo->pEndOfVars) return NULL;
    
    if (NvIsVariable(pVar,pInfo))
    {
        pVar = (NVAR*)((UINT8*)pVar+pVar->size);
        
        if (pVar >= (NVAR*)pInfo->pEndOfVars) return NULL;
    }
    
    do
    {
        if (pVar >= (NVAR*)pInfo->pEndOfVars) return NULL;
        
        //If we found a variable, we are done
        if (NvIsVariable(pVar,pInfo)) return pVar;
        
        //Otherwise, let's check if record size seems valid
        //If size is valid, skip corrupted NVAR
        //Otherwise give up and return NULL
        if (    pVar->size!=FLASH_EMPTY_SIZE
                && pVar->size>sizeof(NVAR)
                && pVar->size<=(pInfo->pEndOfVars-(UINT8*)pVar)
           ) pVar = (NVAR*)((UINT8*)pVar+pVar->size);
        else return NULL;
    }
    while (TRUE);
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   NvGetNextNvar
//
// Description: This function returns the next valid Var after pVar. 
//
// Input:       NVAR* pVar - pointer to Var 
//              NVRAM_STORE_INFO *pInfo - pointer to NVRAM store structure
//
// Output:      NVAR* - pointer to next valid Var after pVar, NULL - if none
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
NVAR* NvGetNextValid(NVAR* pVar, NVRAM_STORE_INFO *pInfo)
{
    do
    {
        pVar = NvGetNextNvar(pVar,pInfo);
    }
    while (pVar && !NvIsValid(pVar));
    
    return pVar;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   NvGetFirstValid
//
// Description: This function returns the first valid Var in NVRAM. 
//
// Input:       NVRAM_STORE_INFO *pInfo - pointer to NVRAM store structure
//
// Output:      NVAR* - pointer to first valid Var in NVRAM, NULL - if none
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
NVAR* NvGetFirstValid(NVRAM_STORE_INFO *pInfo)
{
    NVAR* pNvar = (NVAR*)pInfo->pFirstVar;
    
    //We assume that the first variable pInfo->pFirstVar is non-corrupted.
    //We checked for pInfo->pFirstVar validity
    //during NVRAM_STORE_INFO initialization in NvInitInfoBuffer routine.
    if (!NvIsVariable(pNvar,pInfo)) return NULL;
    
    if (NvIsValid(pNvar)) return pNvar;
    
    return NvGetNextValid(pNvar,pInfo);
}

//Comparison routines
//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   NvAttribEq
//
// Description: This function checks if pNvar attributes ara same with Attributes passed. 
//
// Input:       NVAR* pNVar - pointer to Var 
//              UINT32 Attributes - Attributes of Var
//              NVRAM_STORE_INFO *pInfo - pointer to NVRAM store structure
//
// Output:      NVAR* - pointer to next valid Var after pVar, NULL - if none
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
BOOLEAN NvAttribEq(NVAR* pNvar, UINT32 Attributes, NVRAM_STORE_INFO *pInfo)
{
    //--- By ! we convert integer to boolean
    return        !(pNvar->flags & NVRAM_FLAG_RUNTIME)
              ==  !(Attributes & EFI_VARIABLE_RUNTIME_ACCESS)
            &&    !(pInfo->Flags & NVRAM_STORE_FLAG_NON_VALATILE)
              ==  !(Attributes & EFI_VARIABLE_NON_VOLATILE)
            &&    !(pNvar->flags & NVRAM_FLAG_HARDWARE_ERROR_RECORD)
              ==  !(Attributes & EFI_VARIABLE_HARDWARE_ERROR_RECORD)
            &&    !(pNvar->flags & NVRAM_FLAG_AUTH_WRITE)
              ==  !(Attributes & UEFI23_1_AUTHENTICATED_VARIABLE_ATTRIBUTES)
           ;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   NvarEqNvar
//
// Description: This function verifies if two Var are the same
//
// Input:       NVAR *Nvar1 - pointer to the first Var 
//              IN NVRAM_STORE_INFO *Info1 - pointer to the first NVRAM_STORE_INFO structure
//              NVAR *Nvar2 - pointer to the second Var 
//              IN NVRAM_STORE_INFO *Info2 - pointer to the second NVRAM_STORE_INFO structure
//
// Output:      VOID
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
BOOLEAN NvarEqNvar(
    NVAR *Nvar1, NVRAM_STORE_INFO *Info1,
    NVAR *Nvar2, NVRAM_STORE_INFO *Info2
)
{
    EFI_GUID *Guid1, *Guid2;
    UINT8 *Name1, *Name2;
    BOOLEAN AsciiName = Nvar1->flags&NVRAM_FLAG_ASCII_NAME;

    if (AsciiName != (Nvar2->flags&NVRAM_FLAG_ASCII_NAME)) return FALSE;

    if (   (Info1->Flags & NVRAM_STORE_FLAG_NON_VALATILE)
            != (Info2->Flags & NVRAM_STORE_FLAG_NON_VALATILE)
       ) return FALSE;

    Guid1=NvGetGuid(Nvar1,Info1);
    Guid2=NvGetGuid(Nvar2,Info2);

    if (guidcmp(Guid1,Guid2)) return FALSE;

    Name1=(UINT8*)NvGetName(Nvar1);
    Name2=(UINT8*)NvGetName(Nvar2);

    if (AsciiName)
    {
        while (*Name1 && *Name1==*Name2) {Name1++; Name2++;}

        if (*Name1!=*Name2) return FALSE;
    }

    else
    {
        CHAR16 *N1 = (CHAR16*)Name1;
        CHAR16 *N2 = (CHAR16*)Name2;

        while (*N1 && *N1==*N2) {N1++; N2++;}

        if (*N1!=*N2) return FALSE;
    }

    return TRUE;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   NvVarEq
//
// Description: This function checks if pNvar GUID and Name ara same with passed one. 
//
// Input:       NVAR* pNVar - pointer to Var 
//              CHAR16* sName - Name of the Var to compare 
//              EFI_GUID* pGuid - pointer to GUID to compare with
//              UINTN* pNameSize - Pointer to memory where Nane size will be returned
//              NVRAM_STORE_INFO *pInfo - pointer to NVRAM store structure
//
// Output:      BOOLEAN - TRUE of FALSE based on result
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
BOOLEAN NvVarEq(NVAR* pNvar, CHAR16* sName, EFI_GUID* pGuid, UINTN* pNameSize, NVRAM_STORE_INFO *pInfo)
{
    UINT8 *pVarGuid, *pNameStart, *pN;
    pVarGuid=(UINT8*)NvGetGuid(pNvar,pInfo);
    pN=(UINT8*)NvGetName(pNvar);
    pNameStart=pN;
    //-- Check name if ASCII
    if (pNvar->flags&NVRAM_FLAG_ASCII_NAME)
    {
        while (*pN && *pN==*sName) {pN++; sName++;}
        
        if (*pN!=*sName) return FALSE;
        
        pN++;
    }
    
    else   //-- Check name if Unicode
    {
        CHAR16 *sN=(CHAR16*)pN;
        
        while (*sN && *sN==*sName) {sN++; sName++;}
        
        if (*sN!=*sName) return FALSE;
        
        pN=(UINT8*)++sN;
    }
    
    if (!guidcmp(pVarGuid,pGuid))//---Check GUID
    {
        if (pNameSize) *pNameSize=pN-pNameStart;
        
        return TRUE;
    }
    
    return FALSE;
}

//High level routines that work with a single NV store
//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   NvFindVariable
//
// Description: This function searches for Var with specific GUID and Name. 
//
// Input:       CHAR16* sName - Name of the Var to search 
//              EFI_GUID* pGuid - pointer to GUID to search
//              UINTN* pNameSize - Pointer to memory where Nane size will be returned
//              NVRAM_STORE_INFO *pInfo - pointer to NVRAM store structure
//
// Output:      VOID* - Pointer to found Var, NULL - if not found
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID* NvFindVariable(
    CHAR16* sName, EFI_GUID* pGuid,
    UINTN* pNameSize, NVRAM_STORE_INFO *pInfo
)
{
    NVAR* pNvar = NvGetFirstValid(pInfo);
    
    for (; pNvar; pNvar=NvGetNextValid(pNvar,pInfo))
    {
        if (NvVarEq(pNvar,sName,pGuid,pNameSize,pInfo)) return pNvar;
    }
    
    return NULL;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   NvFindVariableByNvar
//
// Description: This function searches for Var equal to one passed. 
//
// Input:       NVAR* SourceNvar - pointer to Var, which need to be found 
//              NVRAM_STORE_INFO* SourceInfo - pointer to source NVRAM store structure
//              NVRAM_STORE_INFO* DestInfo - pointer to NVRAM store structure where to search
//
// Output:      VOID* - Pointer to found Var, NULL - if not found
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID* NvFindVariableByNvar(NVAR* SourceNvar, 
        NVRAM_STORE_INFO *SourceInfo, NVRAM_STORE_INFO *DestInfo
)
{
    NVAR* pNvar = NvGetFirstValid(DestInfo);
    
    for (; pNvar; pNvar=NvGetNextValid(pNvar,DestInfo))
    {
        if (NvarEqNvar(SourceNvar, SourceInfo, pNvar, DestInfo)) return pNvar;
    }
    
    return NULL;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   NvGetAttributesFromNvar
//
// Description: This function returns the attributes from a given Nvar
//
// Input:       NVAR* pNVar - pointer to Var 
//              OPTIONAL OUT UINT32* Attributes - Pointer to memory where Attributes will be returned 
//              NVRAM_STORE_INFO *pInfo - pointer to NVRAM store structure
//
// Output:      EFI_STATUS - based on result
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS NvGetAttributesFromNvar(
    IN NVAR *pNvar, IN NVRAM_STORE_INFO *pInfo,
    OUT UINT32 *Attributes
)
{
    if (!pNvar || !pInfo || !Attributes) return EFI_INVALID_PARAMETER;
    
    *Attributes = EFI_VARIABLE_BOOTSERVICE_ACCESS;
    if ( pNvar->flags & NVRAM_FLAG_RUNTIME )
        *Attributes|=EFI_VARIABLE_RUNTIME_ACCESS;
    if ( pInfo->Flags & NVRAM_STORE_FLAG_NON_VALATILE )
        *Attributes|=EFI_VARIABLE_NON_VOLATILE;
    if ( pNvar->flags & NVRAM_FLAG_HARDWARE_ERROR_RECORD )
        *Attributes|=EFI_VARIABLE_HARDWARE_ERROR_RECORD;
    if ( pNvar->flags & NVRAM_FLAG_AUTH_WRITE )
        *Attributes|= (UINT8)(*NvGetExtFlags (pNvar) & UEFI23_1_AUTHENTICATED_VARIABLE_ATTRIBUTES);
    
    return EFI_SUCCESS;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   NvGetVariableFromNvar
//
// Description: This function searches for Var with specific GUID and Name. 
//
// Input:       NVAR* pNVar - pointer to Var 
//              UINTN NameSize - size of the Var name
//              OPTIONAL OUT UINT32* Attributes - Pointer to memory where Attributes will be returned 
//              IN OUT UINTN *DataSize - size of Var - if smaller than actual EFI_BUFFER_TOO_SMALL 
//              will be returned and DataSize will be set to actual size needed
//              OUT VOID *Data - Pointer to memory where Var will be returned
//              NVRAM_STORE_INFO *pInfo - pointer to NVRAM store structure
//              OUT UINT8 *Flags - Pointer to memory where Var Flags will be returned
//
// Output:      EFI_STATUS - based on result
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS NvGetVariableFromNvar(
    NVAR *pNvar, UINTN NameSize, OUT UINT32 *Attributes OPTIONAL,
    IN OUT UINTN *DataSize, OUT VOID *Data,
    IN NVRAM_STORE_INFO *pInfo, OUT UINT8 *Flags
)
{
    UINT8* pN;
    UINTN Size;
    
    if (!pNvar || !NvIsVariable(pNvar,pInfo)) return EFI_NOT_FOUND;
    
    if (Attributes)
        NvGetAttributesFromNvar(pNvar, pInfo, Attributes);
    
    // Data
    pN = (UINT8*)NvGetData(pNvar,NameSize,&Size,pInfo);
    
    if (*DataSize<Size) { *DataSize=Size; return EFI_BUFFER_TOO_SMALL;}
    
    *DataSize=Size;
    MemCpy(Data,pN,Size);
    
    if (Flags) *Flags=pNvar->flags;
    
    return EFI_SUCCESS;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   NvGetVariable
//
// Description: This function searches for a Var after Var  with specific GUID and Name. 
//
// Input:       IN CHAR16 *VariableName - pointer to Var Name in Unicode
//              IN EFI_GUID *VendorGuid - pointer to Var GUID
//              OPTIONAL OUT UINT32* Attributes - Pointer to memory where Attributes will be returned 
//              IN OUT UINTN *DataSize - size of Var - if smaller than actual EFI_BUFFER_TOO_SMALL 
//              will be returned and DataSize will be set to actual size needed
//              OUT VOID *Data - Pointer to memory where Var will be returned
//              NVRAM_STORE_INFO *pInfo - pointer to NVRAM store structure
//              OUT NVAR **Var - pointer to found Var variable  
//
// Output:      EFI_STATUS - based on result
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS NvGetVariable(
    IN CHAR16 *VariableName, IN EFI_GUID *VendorGuid,
    OUT UINT32 *Attributes OPTIONAL,
    IN OUT UINTN *DataSize, OUT VOID *Data,
    IN NVRAM_STORE_INFO *pInfo, OUT NVAR **Var
)
{
    UINTN NameSize;
    NVAR* pNvar;
    
    if (!VariableName || !VendorGuid || !DataSize || !Data && *DataSize)
        return EFI_INVALID_PARAMETER;
        
    pNvar = (NVAR*)NvFindVariable(VariableName,VendorGuid,&NameSize,pInfo);
    if ((Var != NULL) && (pNvar != NULL))
       *Var = pNvar;
    return NvGetVariableFromNvar(pNvar,NameSize,Attributes,DataSize,Data,pInfo, NULL);
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   NvGetNameFromNvar
//
// Description: This function searches for a Var after Var with specific GUID and returns it's Name. 
//
// Input:       IN OUT UINTN *VariableNameSize - size of Varname - if smaller than actual EFI_BUFFER_TOO_SMALL 
//              will be returned and DataSize will be set to actual size needed
//              IN OUT CHAR16 *VariableName - pointer where Var Name in Unicode will be stored
//              IN OUT EFI_GUID *VendorGuid - pointer to menory where Var GUID will be stored
//              NVRAM_STORE_INFO *pInfo - pointer to NVRAM store structure
//              BOOLEAN Runtime - search for Var with NVRAM_FLAG_RUNTIME set
//
// Output:      EFI_STATUS - based on result
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS NvGetNameFromNvar(
    IN NVAR *pNvar, IN OUT CHAR16 *VariableName,
    IN OUT UINTN *VariableNameSize,
    IN OUT EFI_GUID *VendorGuid, NVRAM_STORE_INFO *pInfo
)
{
    UINTN NameSize;
    UINT8 *pN, *pNameStart;
    EFI_GUID* pVarGuid;
    
    if (!pNvar || !VariableNameSize || !VariableName || !VendorGuid) return EFI_INVALID_PARAMETER;
    
    
    pN = pNameStart = (UINT8*)NvGetName(pNvar);
    
    if (pNvar->flags&NVRAM_FLAG_ASCII_NAME)
    {
        while (*pN++);
        
        NameSize = (pN - pNameStart)*2;
    }
    
    else
    {
        CHAR16* sN=(CHAR16*)pN;
        
        while (*sN++);
        
        pN=(UINT8*)sN;
        NameSize = pN - pNameStart;
    }
    
    if (NameSize>*VariableNameSize)
    {
        *VariableNameSize=NameSize;
        return EFI_BUFFER_TOO_SMALL;
    }
    
    *VariableNameSize=NameSize;
    pVarGuid=NvGetGuid(pNvar,pInfo);
    
    if (pNvar->flags&NVRAM_FLAG_ASCII_NAME) while (*VariableName++=*pNameStart++);
    else
    {
        CHAR16* sN = (CHAR16*)pNameStart;
        
        while (*VariableName++=*sN++);
    }
    
    MemCpy(VendorGuid,pVarGuid,sizeof(EFI_GUID));
    pInfo->pLastReturned = pNvar;
    return EFI_SUCCESS;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   NvGetNextVariableNvar
//
// Description: This function searches for a Var after Var with specific GUID and returns 
//    pointer to is using NextNvar parameter
//
// Input:       
//              IN CHAR16 *VariableName - pointer to a Var Name in Unicode
//              IN OUT EFI_GUID *VendorGuid - pointer to Var GUID
//              NVRAM_STORE_INFO *pInfo - pointer to NVRAM store structure
//              BOOLEAN Runtime - search for Var with NVRAM_FLAG_RUNTIME set
//              NVAR **NextNvar - pointer to the next varaible's NVAR
//
// Output:      EFI_STATUS - based on result
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS NvGetNextVariableNvar(
    IN OUT CHAR16 *VariableName, IN OUT EFI_GUID *VendorGuid,
    NVRAM_STORE_INFO *pInfo, BOOLEAN Runtime, NVAR **NextNvar
)
{
    NVAR* pNvar;

    if (!VariableName || !VendorGuid) return EFI_INVALID_PARAMETER;
    
    if (VariableName[0]==0)
    {
        pNvar = NvGetFirstValid(pInfo);
    }
    
    else
    {
        if (   pInfo->pLastReturned!=NULL
                && NvIsVariable(pInfo->pLastReturned, pInfo)
                && NvVarEq(pInfo->pLastReturned,VariableName,VendorGuid,NULL, pInfo)
           )
        {
            pNvar=pInfo->pLastReturned;
        }
        
        else
        {
            UINTN NameSize;
            pNvar=(NVAR*)NvFindVariable(VariableName,VendorGuid,&NameSize,pInfo);
            
            if (!pNvar) return EFI_INVALID_PARAMETER;
        }
        if (Runtime && !(pNvar->flags & NVRAM_FLAG_RUNTIME) ) return EFI_INVALID_PARAMETER;
        pNvar=NvGetNextValid(pNvar,pInfo);
    }
    
    if (!pNvar)
    {
        pInfo->pLastReturned = NULL;
        return EFI_NOT_FOUND;
    }
    
    if (Runtime)
    {
        while (pNvar && !(pNvar->flags & NVRAM_FLAG_RUNTIME))
            pNvar=NvGetNextValid(pNvar,pInfo);
            
        if (!pNvar)
        {
            pInfo->pLastReturned = NULL;
            return EFI_NOT_FOUND;
        }
    }
    if (NextNvar) *NextNvar = pNvar;
    return EFI_SUCCESS;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   NvGetNextVariableName
//
// Description: This function searches for a Var after Var with specific GUID and returns it's Name. 
//
// Input:       IN OUT UINTN *VariableNameSize - size of Varname - if smaller than actual EFI_BUFFER_TOO_SMALL 
//              will be returned and DataSize will be set to actual size needed
//              IN OUT CHAR16 *VariableName - pointer where Var Name in Unicode will be stored
//              IN OUT EFI_GUID *VendorGuid - pointer to menory where Var GUID will be stored
//              NVRAM_STORE_INFO *pInfo - pointer to NVRAM store structure
//              BOOLEAN Runtime - search for Var with NVRAM_FLAG_RUNTIME set
//
// Output:      EFI_STATUS - based on result
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS NvGetNextVariableName(
    IN OUT UINTN *VariableNameSize,
    IN OUT CHAR16 *VariableName, IN OUT EFI_GUID *VendorGuid,
    NVRAM_STORE_INFO *pInfo, BOOLEAN Runtime
)
{
    NVAR* pNvar;
    EFI_STATUS Status;
    
    Status=NvGetNextVariableNvar(VariableName,VendorGuid,pInfo,Runtime,&pNvar);
    if (EFI_ERROR(Status)) return Status;
    return NvGetNameFromNvar(
        pNvar, VariableName, VariableNameSize, VendorGuid, pInfo
    );
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   NvInitInfoBuffer
//
// Description: This function inits NVRAM_STORE_INFO structure. 
//
// Input:       NVRAM_STORE_INFO *pInfo - pointer to NVRAM store structure
//              UINTN HeaderSize - Size of the header 
//              UINT8 Flags - default Flags
//
// Output:      VOID
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID NvInitInfoBuffer(IN NVRAM_STORE_INFO *pInfo, UINTN HeaderSize, UINT8 Flags)
{
    NVAR *pVar;
    pInfo->NvramGuidsAddress = (EFI_GUID*)(pInfo->NvramAddress+pInfo->NvramSize-sizeof(EFI_GUID));
    pInfo->pFirstVar = pInfo->NvramAddress+HeaderSize;
    pInfo->NextGuid = 0;
    pInfo->Flags = Flags;
    pInfo->LastVarSize = 0;
    pInfo->pLastReturned = NULL;
    
    if (!(Flags & NVRAM_STORE_FLAG_NON_VALATILE))
    {
        pInfo->pEndOfVars = pInfo->pFirstVar;
        return;
    }
    
    pInfo->pEndOfVars = pInfo->NvramAddress+pInfo->NvramSize;
    pVar = NvGetFirstValid(pInfo);
    
    if ((NVAR*)pInfo->pFirstVar!=pVar)
    {
        if (pVar!=NULL)
        {
            pInfo->pFirstVar=(UINT8*)pVar;
        }
        
        else //if pVar==NULL
        {
            //there are no valid variables
            //set pEndOfVars equal to pFirstVar to indicate that variable store is empty
            pInfo->pEndOfVars = pInfo->pFirstVar;
        }
    }
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   NvGetDefaultsInfo
//
// Description: This function returns Default Variables info. 
//
// Input:       IN const CHAR16* DefaultsVar - name of the defaults Vars
//              NVRAM_STORE_INFO *pInfo - pointer to NVRAM store structure
//              OUT NVRAM_STORE_INFO *pOutInfo - pointer to memory where defaults vill be stored
//              NULL - if not found
//
// Output:      NVRAM_STORE_INFO*
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
NVRAM_STORE_INFO* NvGetDefaultsInfo(IN const CHAR16* DefaultsVar, IN NVRAM_STORE_INFO *pInInfo, OUT NVRAM_STORE_INFO *pOutInfo)
{
    UINTN NameSize;
    NVAR* pNvar;
    pNvar = (NVAR*)NvFindVariable(
                (CHAR16*)DefaultsVar, (EFI_GUID*)&AmiDefaultsVariableGuid,
                &NameSize,pInInfo
            );
            
    if (!pNvar) return NULL;
    
    pOutInfo->NvramAddress = (UINT8*)NvGetData(
                                 pNvar,NameSize,
                                 &pOutInfo->NvramSize,pInInfo
                             );
                             
    if (pOutInfo->NvramAddress==NULL) return NULL;
    
    NvInitInfoBuffer(
        pOutInfo, 0,
        NVRAM_STORE_FLAG_NON_VALATILE
        | NVRAM_STORE_FLAG_READ_ONLY
        | NVRAM_STORE_FLAG_DO_NOT_ENUMERATE
    );
    return pOutInfo;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   NvGetVariable2
//
// Description: This function searches for Var with specific GUID, Name and Enty number 
//              not bigger than InfoCount parameter. 
//
// Input:       IN CHAR16 *VariableName - pointer to Var Name in Unicode
//              IN EFI_GUID *VendorGuid - pointer to Var GUID
//              OPTIONAL OUT UINT32* Attributes - Pointer to memory where Attributes will be returned 
//              IN OUT UINTN *DataSize - size of Var - if smaller than actual EFI_BUFFER_TOO_SMALL 
//              will be returned and DataSize will be set to actual size needed
//              OUT VOID *Data - Pointer to memory where Var will be returned
//              UINT32 InfoCount - Max NVRAM entry number 
//              NVRAM_STORE_INFO *pInfo - pointer to NVRAM store structure
//
// Output:      EFI_STATUS - based on result
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS NvGetVariable2(
    IN CHAR16 *VariableName, IN EFI_GUID *VendorGuid,
    OUT UINT32 *Attributes OPTIONAL,
    IN OUT UINTN *DataSize, OUT VOID *Data,
    UINT32 InfoCount, NVRAM_STORE_INFO *Info
)
{
    UINT32 i;
    
    for (i=0; i<InfoCount; i++)
    {
        EFI_STATUS Status = NvGetVariable(
                                VariableName,VendorGuid,Attributes,DataSize,Data,&Info[i],NULL
                            );
                            
        if (Status!=EFI_NOT_FOUND) return Status;
    }
    
    return EFI_NOT_FOUND;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   NvGetNextVariableName2
//
// Description: This function searches for Var with specific GUID and Enty number 
//              not betwin LastInfoIndex - InfoCount parameter and returns it's Name. 
//
// Input:       IN OUT UINTN *VariableNameSize - size of Varname - if smaller than actual EFI_BUFFER_TOO_SMALL 
//              will be returned and DataSize will be set to actual size needed
//              IN OUT CHAR16 *VariableName - pointer where Var Name in Unicode will be stored
//              IN OUT EFI_GUID *VendorGuid - pointer to menory where Var GUID will be stored
//              UINT32 InfoCount - Max NVRAM entry number 
//              NVRAM_STORE_INFO *pInfo - pointer to NVRAM store structure
//              UINT32 *LastInfoIndex - NVRAM entry number to starf from
//              BOOLEAN Runtime - search for Var with NVRAM_FLAG_RUNTIME set
//
// Output:      EFI_STATUS - based on result
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS NvGetNextVariableName2(
    IN OUT UINTN *VariableNameSize,
    IN OUT CHAR16 *VariableName, IN OUT EFI_GUID *VendorGuid,
    UINT32 InfoCount, NVRAM_STORE_INFO *pInfo, UINT32 *LastInfoIndex,
    BOOLEAN Runtime
)
{
    UINT32 i;
    EFI_STATUS Status;
    NVAR* Nvar;
    CHAR16 OrgName; 

    OrgName = VariableName[0];
    // Preserve first letter of passed Var name, for the case when NvGetNameFromNvar returns EFI_BUFFER_TOO_SMALL right 
    // after setting first letter of name to 0 for search in the next Varstore 
    if (VariableName[0]==0 && LastInfoIndex) *LastInfoIndex=0;
    
    for ( i=(LastInfoIndex) ? *LastInfoIndex : 0
            ; i<InfoCount; i++
        )
    {
        Status=NvGetNextVariableNvar(VariableName,VendorGuid,&pInfo[i],Runtime,&Nvar);
        if (!EFI_ERROR(Status) && pInfo[i].Flags & NVRAM_STORE_FLAG_DO_NOT_ENUMERATE){
            while ( Nvar ){
                UINT32 j;
                for (j = 0; j < i; j++)
                    if (NvFindVariableByNvar(Nvar, &pInfo[i], &pInfo[j] )) 
                        break;
                if (j==i) break;
                Nvar=NvGetNextValid(Nvar,&pInfo[i]);
                if ( Runtime ){
                    while (Nvar && !(Nvar->flags & NVRAM_FLAG_RUNTIME))
                        Nvar=NvGetNextValid(Nvar,&pInfo[i]);
                }
            }
            if (!Nvar)
            {
                pInfo[i].pLastReturned = NULL;
                Status=EFI_NOT_FOUND;
            }
        }

        if (!EFI_ERROR(Status))
        {
            if (LastInfoIndex) *LastInfoIndex=i;
            Status = NvGetNameFromNvar(
                Nvar, VariableName, VariableNameSize, VendorGuid, &pInfo[i]
            );
            if (EFI_ERROR(Status)) {
                VariableName[0] = OrgName; //Restore first letter in case it was set to 0 before going to new Varstore
            }
            return Status;
        }
        
        //When variable with VariableName/VendorGuid
        //is not is the store EFI_INVALID_PARAMETER is returned
        //and we have to keep searching.
        //EFI_NOT_FOUND is returned when variable with VariableName/VendorGuid
        //is found but it's the last variable in the store.
        //In this case we have to return first variable from the next store
        //In order to do that we need to reset the name
        if (Status==EFI_NOT_FOUND)
        {
            VariableName[0]=0;
        }
        
        else
        {
            //If we are here the Status should be EFI_INVALID_PARAMETER,
            //which means the variable with VariableName/VendorGuid has not been found.
            //If we were using LastInfoIndex, the fact that variable has not been found
            //indicates that LastInfoIndex is invalid and we have to restart the search.
            //The condition below checks if LastInfoIndex has been used during this iteration.
            //Seting i to -1 in conjunction with i++ at the end of the iteration restarts
            //the search from 0.
            if (LastInfoIndex && i!=0 && i==*LastInfoIndex){
                i=(UINT32)-1;
                *LastInfoIndex = 0;
            }
        }
    }
    
    if (LastInfoIndex) *LastInfoIndex=0;
    
    return Status;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   GetNvramFfsFileStatePtr
//
// Description: This function searches for firmvare vol header and returns pointer to its State field
//
// Input:       NVRAM_STORE_INFO *Info - pointer to NVRAM store structure
//
// Output:      EFI_FFS_FILE_STATE* - pointer to Ffs header State field
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_FFS_FILE_STATE* GetNvramFfsFileStatePtr(NVRAM_STORE_INFO *Info)
{
    EFI_FFS_FILE_HEADER *FfsFileHeader;
    EFI_FIRMWARE_VOLUME_HEADER *FwVolHeader;
    
    FwVolHeader = (EFI_FIRMWARE_VOLUME_HEADER *)Info->NvramAddress;
    
    if (FwVolHeader->FvLength == Info->NvramSize)
    {
        FfsFileHeader = (EFI_FFS_FILE_HEADER *)(
                            Info->NvramAddress + FwVolHeader->HeaderLength
                        );
        return &FfsFileHeader->State;
    }
    
    return NULL;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   GetNvramFfsFileState
//
// Description: This function searches for the header of the NVRAM image FFS file and returns the value of its State field
//
// Input:       NVRAM_STORE_INFO *Info - pointer to NVRAM store structure
//
// Output:      EFI_FFS_FILE_STATE -  Ffs header State 
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_FFS_FILE_STATE GetNvramFfsFileState(NVRAM_STORE_INFO *Info)
{
    EFI_FFS_FILE_STATE State;
    EFI_FFS_FILE_STATE *StatePtr = GetNvramFfsFileStatePtr(Info);
    if (StatePtr==NULL) return EFI_FILE_HEADER_INVALID;
    State = (FlashEmpty==0) ? *StatePtr : ~*StatePtr;
    if (State==0) State = EFI_FILE_HEADER_INVALID;
    return State;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   IsMainNvramStoreValid
//
// Description: This function verifies if main NVRAM storage is valid
//
// Input:       
//              NVRAM_STORE_INFO *MainInfo - pointer to Main NVRAM storage descriptor
//              VOID *BackUpAddress - address of the back up storage
//
// Output:      BOOLEAN
//                TRUE - the main NVRAM storage is valid
//                FALSE - the main NVRAM storage is invalid. Back up srorage should be used.
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
BOOLEAN IsMainNvramStoreValid(
    NVRAM_STORE_INFO *MainInfo, VOID *BackUpAddress, 
    BOOLEAN *BackupStoreValid
){
    NVRAM_STORE_INFO BackupNvram;
    EFI_FFS_FILE_STATE MainState;
    EFI_FFS_FILE_STATE BackupState;

    if (BackUpAddress==NULL) return TRUE;
    BackupNvram.NvramAddress = BackUpAddress;
    BackupNvram.NvramSize = MainInfo->NvramSize;
    MainState = GetNvramFfsFileState(MainInfo);
    BackupState = GetNvramFfsFileState(&BackupNvram);
// State Transitions:
//    Main              Backup            Valid Store
// = Initial State After Firmware Flashing
// 1. DATA_VALID        HEADER_INVALID    Main
// = Update  Cycle 1
// 2. DATA_VALID        HEADER_VALID      Main
// 3. MARKED_FOR_UPDATE HEADER_VALID      Main
// 4. MARKED_FOR_UPDATE DATA_VALID        Backup
// = Update  Cycle 1 is Over
// = Update  Cycle 2
// 5. HEADER_VALID      DATA_VALID        Backup
// 6. HEADER_VALID      MARKED_FOR_UPDATE Backup
// 7. DATA_VALID        MARKED_FOR_UPDATE Main
// = Update  Cycle 2 is Over
// = Update  Cycle 3
// 8. DATA_VALID        HEADER_VALID      Main
// Stae 8 == State 2
    if (  (MainState & EFI_FILE_DATA_VALID)==0
        ||  (MainState & EFI_FILE_MARKED_FOR_UPDATE)!=0
          &&(BackupState & EFI_FILE_DATA_VALID)!=0
        ||(MainState & ~VALID_STATE_FLAGS)!=0
    ){
        if (BackupStoreValid)
            *BackupStoreValid=
                  ((BackupState & EFI_FILE_DATA_VALID)!=0)
                &&((BackupState & ~VALID_STATE_FLAGS)==0)
                ;
        return FALSE;
    }
    return TRUE;
}

//**********************************************************************
//**********************************************************************
//**                                                                  **
//**        (C)Copyright 1985-2014, American Megatrends, Inc.         **
//**                                                                  **
//**                       All Rights Reserved.                       **
//**                                                                  **
//**      5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093        **
//**                                                                  **
//**                       Phone: (770)-246-8600                      **
//**                                                                  **
//**********************************************************************
//**********************************************************************
