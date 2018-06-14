//**********************************************************************
//**********************************************************************
//**                                                                  **
//**        (C)Copyright 1985-2012, American Megatrends, Inc.         **
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
// $Header: /Alaska/SOURCE/Core/Modules/NVRAM/NVRAM.h 28    11/29/12 5:10p Felixp $
//
// $Revision: 28 $
//
// $Date: 11/29/12 5:10p $
//**********************************************************************
// Revision History
// ----------------
// $Log: /Alaska/SOURCE/Core/Modules/NVRAM/NVRAM.h $
// 
// 28    11/29/12 5:10p Felixp
// Minor improvement: Since UEFI Specification versions prior to 2.1
// (0x2000A) are no longer supported,
//   all the "#if EFI_SPECIFICATION_VERSION >= 0x2000A" conditional
// compilation statements are removed.
// Files modified: NVRAM.h, NVRAMRead.c, NVRAMDXE.c
// 
// 27    11/29/12 3:27p Felixp
// Nvram.h, NvramDxe.c:
//   1. Bug Fix (EIP106441): The Authenticated Variable SCT test was
// failing due to a 
//     bug in UpdateVariable function. The function was skipping the
// update if new variable data
//     is equal to the old variable data. The update should not be skipped
// in case of the append operation
//     (when EFI_VARIABLE_APPEND_WRITE attribute is set). 
//     The function is updated accordingly.
//  2. Bug fix: External declaration for the FlashEmpty variable declared
// variable type as UINT32, 
//     even though the variable is defined in Tokenc.c as UINTN.
// 
// 26    11/07/12 4:13p Oleksiyy
// [TAG]  		EIP99114
// [Category]  	New Feature
// [Description]  	Please make state of "Runtime" variable used in
// NvramDxe.c globally available
// [Files]  		NVRAM.h and NVRAMDXE.c
// 
// 25    7/13/11 9:24a Justinj
// [TAG]  		EIP62762
// [Category]  	Improvement
// [Description]  	Optimize NVRAM cache index so that the entire linked
// list is not walked every time a variable is set or retrieved.
// [Files]  		NVRAM.h
// NVRAMRead.c
// NVRAMDXE.c
// 
// 24    5/13/11 5:44p Artems
// Added CheckStore function definition
// 
// 23    5/13/11 5:22p Artems
// Minor code beautification change
// 
// 22    5/11/11 6:34p Oleksiyy
// [TAG]  		EIP60206 
// [Category]  	Improvement
// [Description]  	Authenticated Variables improvement.
// NV_CACHE_SUPPORT == O support added.
// [Files]  		NVRAMDXE.c and NVRAM.h
// 
// 21    5/09/11 11:04a Artems
// Minor code beautification change
// 
// 19    9/30/10 4:35p Oleksiyy
// Issue Number:  40356 and 39462
// 
// Category:  New Feature
// 
// Description:  Support for EFI_VARIABLE_AUTHENTICATED_WRITE_ACCESS
// Small fix of previously checked in code.
// 
// Files:  NVRAM. h,  NVRAMRead.c, NVRAMDXE.c
// 
// 18    9/22/10 6:39p Felixp
// Enhancement(EIP 39462 and EIP 40356): 
//   Support of the authenticated update of the NVRAM variables
//   as described in UEFI specification version 2.1 and above. 
// NOTE: The actual authentication is performed by the external SecureMod
// eModule, 
//   which must be in the proejct to use this feature.
// 
// 17    12/04/09 12:27p Felixp
// NvarEqNvar function is added
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
// 14    8/25/09 4:11p Felixp
// NVRAM Record Checksum Support(EIP 23825) is added.
// Disabled by default.  Enable using NVRAM_RECORD_CHECKSUM_SUPPORT SDL
// token. 
// 
// 13    6/26/09 3:28p Felixp
// 
// 12    6/26/09 3:27p Felixp
// New IsMainNvramStoreValid function is added. 
// The function detects is main NVRAM or backup NVRAM is currently active
// (returns FALSE when backup is active).
// 
// 11    10/09/08 11:47a Felixp
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
// 10    9/06/07 12:14a Felixp
// 
// 9     8/31/07 3:44p Felixp
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
// 8     5/01/07 6:06p Felixp
// Clean up
// 
// 7     3/18/07 4:08p Felixp
// 1. IsNvramBlock function declaration added
// 2. Clean up
// 
// 6     12/29/06 3:02p Felixp
// Update to use new flash interface
// 
// 5     12/20/06 1:33p Felixp
// Bug fix in BLOCK macro
// 
// 4     10/27/06 11:45a Felixp
// 
// 3     10/27/06 10:42a Felixp
// Bug fixes for correct work in Virtual Address Space.
// 
// 2     10/23/06 7:03p Felixp
// 1. Virtual address space fixup of the global variables added
// 2. NVRAM simulation support
// 
// 1     8/24/06 12:38p Felixp
// 
// 4     3/22/05 9:51p Felixp
// sAmiRomFile added
// 
// 3     3/22/05 8:59p Felixp
// FlashSize variable added
// 
// 2     3/04/05 9:40a Mandal
// 
// 1     1/28/05 12:44p Felixp
// 
// 3     1/20/05 11:37a Felixp
// Component restructurized to support release in binary format
// 
// 2     1/18/05 3:22p Felixp
// PrintDebugMessage renamed to Trace
// 
// 1     12/27/04 4:08p Felixp
// 
// 8     12/09/04 9:02p Felixp
// minor iprovements
// 
// 7     8/28/04 1:49a Felixp
// NVRAM Routines fixes
// 
// 
// 1     3/29/04 2:32a Felixp
// 
//**********************************************************************
//<AMI_FHDR_START>
//
// Name:	NVRAM.h
//
// Description:	NVRAM Definitions
//
//<AMI_FHDR_END>
//**********************************************************************
#ifndef __NVRAM__H__
#define __NVRAM__H__
#ifdef __cplusplus
extern "C" {
#endif
#include <AmiLib.h>
#include <Flash.h>
#include <Hob.h>
#include <Ffs.h>

#define FLASH_EMPTY_BYTE ((UINT8)FlashEmpty)
#define FLASH_EMPTY_FLAG FLASH_EMPTY_BYTE
#define FLASH_EMPTY_NEXT FlashEmptyNext
#define FLASH_EMPTY_SIGNATURE ((UINT32)FlashEmpty)
#define FLASH_EMPTY_SIZE ((VAR_SIZE_TYPE)FlashEmpty)

#define NVRAM_FLAG_VALID 0x80
#define NVRAM_FLAG_RUNTIME 1
#define NVRAM_FLAG_ASCII_NAME 2
#define NVRAM_FLAG_GUID 4
#define NVRAM_FLAG_DATA_ONLY 8
#define NVRAM_FLAG_EXT_HEDER 0x10
#define NVRAM_FLAG_AUTH_WRITE 0x40
#define NVRAM_FLAG_HARDWARE_ERROR_RECORD 0x20
#define UEFI21_SPECIFIC_NVRAM_FLAGS (NVRAM_FLAG_HARDWARE_ERROR_RECORD | NVRAM_FLAG_AUTH_WRITE)
#define UEFI23_1_AUTHENTICATED_VARIABLE_ATTRIBUTES \
                (EFI_VARIABLE_AUTHENTICATED_WRITE_ACCESS | EFI_VARIABLE_TIME_BASED_AUTHENTICATED_WRITE_ACCESS)

#define NVRAM_EXT_FLAG_CHECKSUM 1

#define NVRAM_eFLAG_AUTH_WRITE              EFI_VARIABLE_AUTHENTICATED_WRITE_ACCESS //0x10
#define NVRAM_eFLAG_TIME_BASED_AUTH_WRITE   EFI_VARIABLE_TIME_BASED_AUTHENTICATED_WRITE_ACCESS //0x20

#define ALL_FLAGS (NVRAM_FLAG_VALID | NVRAM_FLAG_RUNTIME |\
				   NVRAM_FLAG_ASCII_NAME | NVRAM_FLAG_GUID|\
				   NVRAM_FLAG_DATA_ONLY | NVRAM_FLAG_EXT_HEDER|\
                   UEFI21_SPECIFIC_NVRAM_FLAGS\
                  )

#define NVAR_SIGNATURE ('N'+('V'<<8)+(('A'+('R'<<8))<<16))//NVAR

// {C0EC00FD-C2F8-4e47-90EF-9C8155285BEC}
#define NVRAM_HOB_GUID \
    { 0xc0ec00fd, 0xc2f8, 0x4e47, { 0x90, 0xef, 0x9c, 0x81, 0x55, 0x28, 0x5b, 0xec } }

#define NVRAM_MODE_MANUFACTORING 1
#define NVRAM_MODE_RESET_CONFIGURATION 2
#define NVRAM_MODE_DEFAULT_CONFIGURATION 4
#define NVRAM_MODE_SIMULATION 8

#define NVRAM_STORE_FLAG_NON_VALATILE 1
#define NVRAM_STORE_FLAG_READ_ONLY 2
#define NVRAM_STORE_FLAG_DO_NOT_ENUMERATE 4

extern const UINTN FlashEmpty;
extern const UINT32 FlashEmptyNext;
extern const EFI_GUID AmiDefaultsVariableGuid;
extern const EFI_GUID AmiNvramHobGuid;
extern const CHAR16 MfgDefaults[];
extern const CHAR16 StdDefaults[];
extern const UINT32 NvramHeaderLength;

typedef UINT16 VAR_SIZE_TYPE;
#define NEXT_OFFSET (EFI_FIELD_OFFSET(NVAR,size)+sizeof(VAR_SIZE_TYPE))
#define NEXT_SIZE 3
#define FLAG_SIZE 1
#define FLAG_OFFSET (NEXT_OFFSET + NEXT_SIZE)
#define MAX_NVRAM_VARIABLE_SIZE ((1<<(sizeof(VAR_SIZE_TYPE)<<3))-1)
#pragma pack(push)
#pragma pack(1)
typedef struct{
	UINT32 signature;
	VAR_SIZE_TYPE size;
	UINT32 next:24;
	UINT32 flags:8;
//  guid and name are there only if NVRAM_FLAG_DATA_ONLY is not set
//	UINT8 guid; 
//	CHAR8 or CHAR16 name[...];
//  UINT8 data[...];
//  if NVRAM_FLAG_EXT_HEDER is set
//  UINT8 extflags;
//  UINT8 extdata[...];
//  VAR_SIZE_TYPE extsize;
}NVAR;

typedef struct {
    EFI_HOB_GUID_TYPE Header;
    EFI_PHYSICAL_ADDRESS NvramAddress;
    EFI_PHYSICAL_ADDRESS BackupAddress;
    UINT32 NvramSize;
    UINT32 HeaderLength;
    UINT32 NvramMode;
} NVRAM_HOB;
#pragma pack(pop)

typedef struct {
    UINT8 *NvramAddress;
    UINTN NvramSize;
    EFI_GUID* NvramGuidsAddress;
    UINT8 *pEndOfVars, *pFirstVar;
    INT16 NextGuid;
    VAR_SIZE_TYPE LastVarSize;
    NVAR *pLastReturned;
    UINT8 Flags;
} NVRAM_STORE_INFO;

//Low level access routines
EFI_GUID* NvGetGuid(NVAR* pVar, NVRAM_STORE_INFO *pInfo);
VOID* NvGetName(NVAR* pVar);
NVAR* NvGetDataNvar(NVAR *pVar, NVRAM_STORE_INFO *pInfo);
VOID* NvGetData(NVAR* pVar, UINTN NameLength, UINTN* pDataSize, NVRAM_STORE_INFO *pInfo);

//Validation routines
BOOLEAN NvIsVariable(NVAR *pVar, NVRAM_STORE_INFO *pInfo);
BOOLEAN NvIsValid(NVAR* pVar);

//Iteration routines
NVAR* NvGetNextNvar(NVAR* pVar, NVRAM_STORE_INFO *pInfo);
NVAR* NvGetNextValid(NVAR* pVar, NVRAM_STORE_INFO *pInfo);

//Comparison routines
BOOLEAN NvAttribEq(NVAR* pNvar, UINT32 Attributes, NVRAM_STORE_INFO *pInfo);
BOOLEAN NvVarEq(NVAR* pNvar, CHAR16* sName, EFI_GUID* pGuid, UINTN* pNameSize, NVRAM_STORE_INFO *pInfo);
BOOLEAN NvarEqNvar(NVAR *Nvar1, NVRAM_STORE_INFO *Info1, NVAR *Nvar2, NVRAM_STORE_INFO *Info2);

//High level routines that work with a single NV store
VOID* NvFindVariable(CHAR16* sName, EFI_GUID* pGuid, UINTN* pNameSize, NVRAM_STORE_INFO *pInfo);
EFI_STATUS NvGetVariable(
	IN CHAR16 *VariableName, IN EFI_GUID *VendorGuid,
	OUT UINT32 *Attributes OPTIONAL,
	IN OUT UINTN *DataSize, OUT VOID *Data, 
    NVRAM_STORE_INFO *pInfo,  OUT NVAR **Var OPTIONAL
);
EFI_STATUS NvGetNextVariableName(
	IN OUT UINTN *VariableNameSize,
	IN OUT CHAR16 *VariableName, IN OUT EFI_GUID *VendorGuid,
    NVRAM_STORE_INFO *pInfo, BOOLEAN Runtime
);

//High level routines that work with a multiple NV stores
EFI_STATUS NvGetVariable2(
	IN CHAR16 *VariableName, IN EFI_GUID *VendorGuid,
	OUT UINT32 *Attributes OPTIONAL,
	IN OUT UINTN *DataSize, OUT VOID *Data,
    UINT32 InfoCount, NVRAM_STORE_INFO *pInfo
);
EFI_STATUS NvGetNextVariableName2(
	IN OUT UINTN *VariableNameSize,
	IN OUT CHAR16 *VariableName, IN OUT EFI_GUID *VendorGuid,
    UINT32 InfoCount, NVRAM_STORE_INFO *pInfo, UINT32 *LastInfoIndex,
    BOOLEAN Runtime
);

//Service routines
VOID NvInitInfoBuffer(IN NVRAM_STORE_INFO *pInfo, UINTN HeaderSize, UINT8 Flags);
NVRAM_STORE_INFO* NvGetDefaultsInfo(
    IN const CHAR16* DefaultsVar, 
    IN NVRAM_STORE_INFO *pInInfo, OUT NVRAM_STORE_INFO *pOutInfo
);
EFI_STATUS NvGetAttributesFromNvar(
    IN NVAR *pNvar, IN NVRAM_STORE_INFO *pInfo,
    OUT UINT32 *Attributes
);
EFI_STATUS NvGetVariableFromNvar(
    NVAR *pNvar, UINTN NameSize, OUT UINT32 *Attributes OPTIONAL,
	IN OUT UINTN *DataSize, OUT VOID *Data,
    IN NVRAM_STORE_INFO *pInfo, OUT UINT8 *Flags OPTIONAL
);
EFI_FFS_FILE_STATE* GetNvramFfsFileStatePtr(NVRAM_STORE_INFO *Info);
EFI_FFS_FILE_STATE GetNvramFfsFileState(NVRAM_STORE_INFO *Info);
BOOLEAN IsMainNvramStoreValid(
    NVRAM_STORE_INFO *MainInfo, VOID *BackUpAddress,
    BOOLEAN *BackupStoreValid
);

UINT8 NvCalculateNvarChecksum(NVAR* pVar);
UINT8* NvGetExtFlags (NVAR* pVar);

// Shared with AuthVariable service
typedef struct {
    UINT8  AuthFlags; // AuthWriteAccess = 0x10 and TimeWriteAccess = 0x20
    UINT64 Mc;
    UINT8  KeyHash[32]; // sha256
}EXT_SEC_FLAGS; 

VOID
GetVarAuthExtFlags(
    IN NVAR *Var, 
    IN NVRAM_STORE_INFO *pInfo, 
    OUT EXT_SEC_FLAGS *ExtFlags
);

EFI_STATUS FindVariable(
    IN CHAR16 *VariableName, IN EFI_GUID *VendorGuid,
    OUT UINT32 *Attributes ,
    IN OUT UINTN *DataSize, OUT VOID **Data
);

VOID CheckStore(
    IN BOOLEAN Recover
);

BOOLEAN IsNvramRuntime();

/****** DO NOT WRITE BELOW THIS LINE *******/
#ifdef __cplusplus
}
#endif
#endif
//**********************************************************************
//**********************************************************************
//**                                                                  **
//**        (C)Copyright 1985-2012, American Megatrends, Inc.         **
//**                                                                  **
//**                       All Rights Reserved.                       **
//**                                                                  **
//**      5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093        **
//**                                                                  **
//**                       Phone: (770)-246-8600                      **
//**                                                                  **
//**********************************************************************
//**********************************************************************