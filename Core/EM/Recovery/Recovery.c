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
// $Header: /Alaska/BIN/Core/Modules/Recovery/Recovery.c 34    8/09/12 11:10a Pats $
//
// $Revision: 34 $
//
// $Date: 8/09/12 11:10a $
//**********************************************************************
// Revision History
// ----------------
// $Log: /Alaska/BIN/Core/Modules/Recovery/Recovery.c $
// 
// 34    8/09/12 11:10a Pats
// [TAG] - EIP 80780
// [Category] - Function Request
// [Description] - Support for recovery from media formatted with the
// EXT(x) file system.
// [Files] Recovery.c, Recovery.mak, Recovery.sdl, RecoveryCsp.h (bin),
// and FsRecovery.c (source)
// 
// 33    8/02/12 11:56a Artems
// [TAG]  		EIP93520
// [Category]  	New Feature
// [Description]  	Support of Microsoft ESRT spec
// [Files]  		Recovery.h Recovery.sdl Recovery.c Reflash.c ReflashWorker.c
// Esrt.c
// 
// 32    4/20/12 2:53p Artems
// [TAG]  		EIP87678
// [Category]  	Improvement
// [Description]  	Added function headers for CHM builder
// [Files]  		Recovery.c
// 
// 31    4/20/12 2:17p Artems
// [TAG]  		EIP87678
// [Category]  	New Feature
// [Description]  	Selection of image to boot from on flash update boot
// path - either old image (currently in flash) or new one in recovery
// capsule
// [Files]  		Recovery.c
// DxeIpl.c
// Core.sdl
// Tokens.c
// 
// 30    1/25/12 2:45p Pats
// [TAG] - EIP 26909
// [Category] - Function Request
// [Description] - Support for recovery from media formatted with the NTFS
// file system. This of necessity includes detection of GPT partitions,
// which may contain any file system.
// [Files] Recovery.c, Recovery.mak, Recovery.sdl, RecoveryCsp.h (bin),
// and FsRecovery.c (source)
// 
// 29    11/02/11 4:52p Artems
// EIP 74446: Fixed bug - reflash is enabled when recovery image is not
// found
// 
// 28    8/11/11 5:57p Artems
// Minor fix to initialize recovery hob Address field before calling
// ReportFV
//
// 27    5/13/11 4:47p Artems
// Added secured recovery support
// 
// 26    2/15/11 6:14p Artems
// Fixed bug with duplicated Size variable
// 
// 25    2/05/11 2:45p Artems
// EIP 39463: Added support for secure update
// EIP 39461: New ROM layout infrastructure support
// 
// 24    10/01/10 7:40p Felixp
// Improvement:
// The code that detects Firmware Volumes in the recovery image 
// and publishes them is updated to use information from the ROM Layout
// HOB.
// 
// 23    6/11/10 11:43a Artems
// Added porting hooks for recovery file name and validation
// 
// 22    2/09/10 11:34a Felixp
// ReadCapsule function update: code that verifies if FV in ROM is updated
// to ensure that base address is below 4GB.
// 
// 21    2/05/10 2:32p Felixp
// Bug fix in UnknownType function. 
// The bug caused occasional hanging, when recovery image was not found.
// 
// 20    2/05/10 8:40a Felixp
// More flexible FV detection in the recovery image.
// 
// 19    11/25/09 4:46p Felixp
// sAmiRomFile renamed to RecoveryFileName
// FlashSize renamed ro RecoveryImageSize
// 
// 18    8/25/09 5:15p Felixp
// Recovery module is updated to pass recovery image location via special
// GUIDed HOB. 
// Old implementation that was relying on Firmware Volume (FV) handle, 
// required porting for a projects with non standard FV management policy.
// 
// 17    7/09/09 12:50p Artems
// Updated file headers
// 
// 16    7/08/09 2:14p Robert
// Changed the definition of the variable FlashSize from FLASH_SIZE to
// RECOVERY_FLASH_SIZE
// 
// 15    6/16/09 5:20p Artems
// EIP 21169 Added Eltorito support
// 
// 14    3/12/08 2:08p Ambikas
// Added recovery error code for no capsule found.  
// 
// 13    8/07/07 2:21p Felixp
// New StatusCodes added
// 
// 12    4/13/07 6:03p Ambikas
// Coding standard changes: updated year in AMI copyright header/footer;
// added AMI_PHDRs for all functions; split the one line function
// GuidMatch into several lines.
// 
// 11    12/22/06 11:29a Felixp
// SDL token added to customize name of the recovery ROM image
// 
// 10    6/28/06 12:44p Felixp
// OEM recovery type added
// 
// 9     6/04/06 9:27p Ambikas
// 
// 8     5/21/06 11:29p Felixp
// Support for retries added (If recovery image not found, retry
// RECOVERY_SCAN_RETRIES times)
// 
// 7     4/13/06 2:02p Ambikas
// 
// 6     4/10/06 9:50a Ambikas
// 
// 5     3/17/06 6:10p Felixp
// More generic calculation of the FV_MAIN offset within recovery BIOS
// image
// 
// 4     1/06/06 9:54a Felixp
// 
// 1     12/01/05 9:35a Felixp
// 
//**********************************************************************
//<AMI_FHDR_START>
//
// Name:	    Recovery.c
//
// Description:	Recovery functionality implementation
//
//<AMI_FHDR_END>
//**********************************************************************

//---------------------------------------------------------------------- 

#include <PPI/RecoveryModule.h>
#include <AmiPeiLib.h>
#include <Token.h>
#include <AmiHobs.h>
#include "Recovery.h"
#include "RecoveryCsp.h"

RECOVERY_IMAGE_HOB *pRecoveryHob;

extern UINTN FlashDeviceBase;
const CHAR8 *RecoveryFileName = CONVERT_TO_STRING(RECOVERY_ROM);
const UINTN RecoveryImageSize = RECOVERY_IMAGE_SIZE;
const BOOLEAN CdRecoverySupport = CD_RECOVERY_SUPPORT;
const BOOLEAN FatRecoverySupport = FAT_RECOVERY_SUPPORT;
const BOOLEAN NtfsRecoverySupport = NTFS_RECOVERY_SUPPORT;
const BOOLEAN ExtRecoverySupport = EXT_RECOVERY_SUPPORT;

EFI_GUID guidBlockDeviceCapsule = BLOCK_DEVICE_RECOVERY_CAPSULE_GUID;
EFI_GUID guidSerialCapsule = SERIAL_RECOVERY_CAPSULE_GUID;
EFI_GUID guidOemCapsule = OEM_RECOVERY_CAPSULE_GUID;

#define BLOCK   &guidBlockDeviceCapsule
#define SERIAL  &guidSerialCapsule
#define CAPSULE &guidOemCapsule

EFI_GUID* RecoveryDeviceOrder[] = {RECOVERY_DEVICE_ORDER, NULL};

EFI_GUID guidRecoveryModule = EFI_PEI_RECOVERY_MODULE_PPI_GUID;
EFI_GUID guidRecoveryDevice = EFI_PEI_DEVICE_RECOVERY_MODULE_PPI_GUID;

EFI_STATUS LoadRecoveryCapsule(
	IN EFI_PEI_SERVICES **PeiServices,
	IN struct _EFI_PEI_RECOVERY_MODULE_PPI *This
);

EFI_PEI_RECOVERY_MODULE_PPI RecoveryModule = {LoadRecoveryCapsule};

// PPI to be installed
static EFI_PEI_PPI_DESCRIPTOR RecoveryPpiList[] =
{ 
	{
		EFI_PEI_PPI_DESCRIPTOR_PPI | EFI_PEI_PPI_DESCRIPTOR_TERMINATE_LIST,
		&guidRecoveryModule, &RecoveryModule
	}	
};

EFI_PHYSICAL_ADDRESS RecoveryBuffer = NULL;
UINTN RecoveryBufferSize = 0;

//<AMI_PHDR_START>
//----------------------------------------------------------------------
//
// Procedure:	VerifyFwImage
//
// Description:	Verifies recovery capsule
// 
// Note: This is dummy function. Actual implementation is in SecureFlash pkg
//---------------------------------------------------------------------- 
//<AMI_PHDR_END>
EFI_STATUS VerifyFwImage (
  IN EFI_PEI_SERVICES  **PeiServices,
  IN VOID              **Buffer,
  IN OUT UINT32         *Size,
  OUT UINT32            *FailedTask
)
#if defined(SecFlashUpd_SUPPORT) && SecFlashUpd_SUPPORT == 1
;
#else
{ 
    if(FailedTask)
        *FailedTask = 0;
    return EFI_SUCCESS; 
}
#endif

//<AMI_PHDR_START>
//----------------------------------------------------------------------
//
// Procedure:	ReadCapsule
//
// Description:	Called by FindRecoveryDevice.  Calls LoadRecoveryCapsule
//      function of the passed in ppi EFI_PEI_DEVICE_RECOVERY_MODULE_PPI 
//      to get recovery image.  If found, an HOB is created for this 
//      recovery image.  
//
//---------------------------------------------------------------------- 
//<AMI_PHDR_END>

EFI_STATUS ReadCapsule(
	IN EFI_PEI_SERVICES **PeiServices,
	EFI_PEI_DEVICE_RECOVERY_MODULE_PPI *pDRM, 
	UINTN CapsuleInstance, UINTN Size
)
{
	EFI_STATUS           Status;
    EFI_PHYSICAL_ADDRESS RomImageStart = FlashDeviceBase;
    UINT32               FailedStage;

    if(Size > RecoveryBufferSize){
		Status = (*PeiServices)->AllocatePages(PeiServices, EfiBootServicesCode, (Size >> 12) + 1, &RecoveryBuffer);
        if (EFI_ERROR(Status)) 
            return Status;

        RecoveryBufferSize = Size;
    }

	PEI_TRACE((TRACE_DXEIPL, PeiServices, "Loading Recovery Image..."));

	Status = pDRM->LoadRecoveryCapsule(PeiServices, pDRM, CapsuleInstance, (VOID*)RecoveryBuffer);

	PEI_TRACE((TRACE_DXEIPL, PeiServices, "done. Status: %r\n",Status));

	if (EFI_ERROR(Status)) 
        return Status;

    Status = VerifyFwImage(PeiServices, (VOID**)&RecoveryBuffer, (UINT32*)&Size, (UINT32*)&FailedStage ); 
    pRecoveryHob->FailedStage = FailedStage;
    pRecoveryHob->Status = (UINT8)Status;
    if (EFI_ERROR(Status )) {
        PEI_ERROR_CODE(PeiServices, PEI_RECOVERY_INVALID_CAPSULE, EFI_ERROR_MAJOR | Status );
        return Status;
    }

    pRecoveryHob->Address = RecoveryBuffer;

	return Status;
}

typedef BOOLEAN (*PREDICATE)(EFI_GUID *pType, VOID* pContext);

//<AMI_PHDR_START>
//----------------------------------------------------------------------
//
// Procedure:	FindRecoveryDevice
//
// Description:	Called by LoadRecoveryCapsule.  
//              Loop: Locate all installed EFI_PEI_DEVICE_RECOVERY_MODULE_PPI 
//              ppis and call ReadCapsule on them.  
//
//---------------------------------------------------------------------- 
//<AMI_PHDR_END>
EFI_STATUS FindRecoveryDevice(
	IN EFI_PEI_SERVICES **PeiServices,
	PREDICATE Criteria, VOID* pContext
){
	EFI_STATUS Status = EFI_SUCCESS;
	BOOLEAN Loaded = FALSE;
	UINTN i = 0;

	do {
		EFI_PEI_DEVICE_RECOVERY_MODULE_PPI *pRecoveryDevice;
		EFI_PEI_PPI_DESCRIPTOR *pDummy;
		UINTN j, n;

		Status = (*PeiServices)->LocatePpi(PeiServices, &guidRecoveryDevice, i++, &pDummy, &pRecoveryDevice);
		if (EFI_ERROR(Status)) 
            break;

		Status = pRecoveryDevice->GetNumberRecoveryCapsules(PeiServices, pRecoveryDevice, &n);
		if (EFI_ERROR(Status)) 
            continue;

		for(j = 0; j < n; j++) {
			UINTN Size;
			EFI_GUID CapsuleType;

			Status = pRecoveryDevice->GetRecoveryCapsuleInfo(PeiServices, pRecoveryDevice, j, &Size, &CapsuleType);
			if (EFI_ERROR(Status) || !Criteria(&CapsuleType, pContext)) 
                continue;

			Status = ReadCapsule(PeiServices, pRecoveryDevice, j, Size);
			if (!EFI_ERROR(Status)){
                Loaded = TRUE; 
                PEI_PROGRESS_CODE(PeiServices,PEI_RECOVERY_CAPSULE_LOADED);
                break; 
            }
		}
	} while(!Loaded);
	return Status;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------
//
// Procedure:	GuidMatch
//
// Description:	Wrapper for guidcmp function.   
//
//---------------------------------------------------------------------- 
//<AMI_PHDR_END>
BOOLEAN GuidMatch(EFI_GUID* Type1, EFI_GUID* Type2)
{
    return !guidcmp(Type1,Type2);
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------
//
// Procedure:	UnknownType
//
// Description:	Returns TRUE if the parameter, guid CapsuleType, in not 
//              in parameter, List (a list of guids).  
//
//---------------------------------------------------------------------- 
//<AMI_PHDR_END>
BOOLEAN UnknownType(EFI_GUID* CapsuleType, EFI_GUID** List)
{
	EFI_GUID **pType;
	for(pType = List; *pType; pType++) if (!guidcmp(*pType,CapsuleType)) return FALSE;
	return TRUE;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------
//
// Procedure:	LoadRecoveryCapsule
//
// Description:	LoadRecoveryCapsule function of EFI_PEI_RECOVERY_MODULE_PPI 
//              ppi.  RecoveryDeviceOrder is a list of guids; each guid 
//              represents a type of recovery device.  We go through 
//              this list and call FindRecoveryDevice for each type of 
//              device. 
//              -This function should not be confused with LoadRecoveryCapsule
//              function of the EFI_PEI_DEVICE_RECOVERY_MODULE_PPI ppi.  
//              -Called by DxeIpl.
//
//---------------------------------------------------------------------- 
//<AMI_PHDR_END>
EFI_STATUS LoadRecoveryCapsule(
	IN EFI_PEI_SERVICES **PeiServices,
	IN struct _EFI_PEI_RECOVERY_MODULE_PPI *This
)
{
	EFI_GUID **ppType;
	EFI_STATUS Status = EFI_NOT_FOUND;
	UINTN i;
    EFI_GUID RecoveryHobGuid = AMI_RECOVERY_IMAGE_HOB_GUID;

    PEI_PROGRESS_CODE(PeiServices,PEI_RECOVERY_STARTED);

// Create Recovery Hob
	Status = (*PeiServices)->CreateHob(
		PeiServices, EFI_HOB_TYPE_GUID_EXTENSION, 
		sizeof(RECOVERY_IMAGE_HOB), &pRecoveryHob);

    if (EFI_ERROR(Status)) 
        return Status;

    pRecoveryHob->Header.Name = RecoveryHobGuid;
    pRecoveryHob->Address = NULL;
    pRecoveryHob->FailedStage = 0;

	for(i = 0; i < RECOVERY_SCAN_RETRIES; i++) {
		for(ppType = RecoveryDeviceOrder; *ppType; ppType++) {
			Status = FindRecoveryDevice(PeiServices,GuidMatch,*ppType);
			if (!EFI_ERROR(Status)) 
                return Status;
		}

		Status = FindRecoveryDevice(PeiServices, UnknownType, RecoveryDeviceOrder);
		if (!EFI_ERROR(Status)) break;
	}

    if (EFI_ERROR(Status)) { 
        PEI_ERROR_CODE(PeiServices, PEI_RECOVERY_NO_CAPSULE, EFI_ERROR_MAJOR);
        pRecoveryHob->Status = (UINT8)Status;
    }

	return Status;
}

//this funciton is created from InitList.c template file during build process
VOID InitParts(IN EFI_FFS_FILE_HEADER *FfsHeader,IN EFI_PEI_SERVICES **PeiServices);

//<AMI_PHDR_START>
//----------------------------------------------------------------------
//
// Procedure:	RecoveryEntry
//
// Description:	Entry point.  Installs EFI_PEI_RECOVERY_MODULE_PPI ppi 
//              (which has function LoadRecoveryCapsule).  
//
//---------------------------------------------------------------------- 
//<AMI_PHDR_END>
EFI_STATUS RecoveryEntry (
	IN EFI_FFS_FILE_HEADER       *FfsHeader,
	IN EFI_PEI_SERVICES          **PeiServices
)
{
	InitParts(FfsHeader,PeiServices);
	return (*PeiServices)->InstallPpi(PeiServices,RecoveryPpiList);
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------
//
// Procedure:	OemGetFileListFromPrimaryVolume
//
// Description:	Porting hook to return recovery capsule file name from CD
//
//---------------------------------------------------------------------- 
//<AMI_PHDR_END>
VOID OemGetFileListFromPrimaryVolume(
    IN  DIR_RECORD          *Root,
    IN  UINT32              RootSize,
    OUT UINTN               *NumberOfFiles,
    OUT DIR_RECORD          **Buffer
);

//<AMI_PHDR_START>
//----------------------------------------------------------------------
//
// Procedure:	OemGetFileListFromFatVolume
//
// Description:	Porting hook to return recovery capsule file name from FAT
//
//---------------------------------------------------------------------- 
//<AMI_PHDR_END>
VOID OemGetFileListFromFatVolume(
    IN  DIR_ENTRY            *Root,
    IN  UINT32               RootEntries,
    OUT UINTN                *NumberOfFiles,
    OUT DIR_ENTRY            **Buffer
);


#if NTFS_RECOVERY_SUPPORT
//<AMI_PHDR_START>
//----------------------------------------------------------------------
//
// Procedure:	OemGetFileListFromNtfsVolume
//
// Description:	Porting hook to return recovery capsule file name from NTFS
//
//---------------------------------------------------------------------- 
//<AMI_PHDR_END>
VOID OemGetFileListFromNtfsVolume(
    IN  UINT8                *Root,
    IN  UINT32               RootSize,
    OUT UINTN                *NumberOfFiles,
    OUT INDEX_ENTRY          **Buffer
);
#endif

#if EXT_RECOVERY_SUPPORT
//<AMI_PHDR_START>
//----------------------------------------------------------------------
//
// Procedure:	OemGetFileListFromExtVolume
//
// Description:	Porting hook to return recovery capsule file name from EXT(n)
//
//---------------------------------------------------------------------- 
//<AMI_PHDR_END>
VOID OemGetFileListFromExtVolume(
    IN  UINT8                *Root,
    IN  UINT32               RootSize,
    OUT UINTN                *NumberOfFiles,
    OUT DIR_ENTRY_EXT        **Buffer
);
#endif

//<AMI_PHDR_START>
//----------------------------------------------------------------------
//
// Procedure:	OemIsValidFile
//
// Description:	Porting hook to validate recovery capsule file
//
//---------------------------------------------------------------------- 
//<AMI_PHDR_END>
BOOLEAN OemIsValidFile(
    IN VOID  *FileData,
    IN UINTN FileSize
);

//<AMI_PHDR_START>
//----------------------------------------------------------------------
//
// Procedure:	GetFileListFromPrimaryVolume
//
// Description:	Wrapper for porting hook OemGetFileListFromPrimaryVolume
//
//---------------------------------------------------------------------- 
//<AMI_PHDR_END>
VOID GetFileListFromPrimaryVolume(
    IN  DIR_RECORD          *Root,
    IN  UINT32              RootSize,
    OUT UINTN               *NumberOfFiles,
    OUT DIR_RECORD          **Buffer
)
{
    OemGetFileListFromPrimaryVolume(Root, RootSize, NumberOfFiles, Buffer);
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------
//
// Procedure:	GetFileListFromFatVolume
//
// Description:	Wrapper for porting hook OemGetFileListFromFatVolume
//
//---------------------------------------------------------------------- 
//<AMI_PHDR_END>
VOID GetFileListFromFatVolume(
    IN  DIR_ENTRY            *Root,
    IN  UINT32               RootEntries,
    OUT UINTN                *NumberOfFiles,
    OUT DIR_ENTRY            **Buffer
)
{
    OemGetFileListFromFatVolume(Root, RootEntries, NumberOfFiles, Buffer);
}

#if NTFS_RECOVERY_SUPPORT
//<AMI_PHDR_START>
//----------------------------------------------------------------------
//
// Procedure:	GetFileListFromNtfsVolume
//
// Description:	Wrapper for porting hook OemGetFileListFromNtfsVolume
//
//---------------------------------------------------------------------- 
//<AMI_PHDR_END>
VOID GetFileListFromNtfsVolume(
    IN  UINT8                *Root,
    IN  UINT32               RootSize,
    OUT UINTN                *NumberOfFiles,
    OUT INDEX_ENTRY          **Buffer
)
{
    OemGetFileListFromNtfsVolume(Root, RootSize, NumberOfFiles, Buffer);
}
#endif

#if EXT_RECOVERY_SUPPORT
//<AMI_PHDR_START>
//----------------------------------------------------------------------
//
// Procedure:	GetFileListFromExtVolume
//
// Description:	Wrapper for porting hook OemGetFileListFromExtVolume
//
//---------------------------------------------------------------------- 
//<AMI_PHDR_END>
VOID GetFileListFromExtVolume(
    IN  UINT8               *Root,
    IN  UINT32              RootSize,
    OUT UINTN               *NumberOfFiles,
    OUT DIR_ENTRY_EXT       **Buffer
)
{
    OemGetFileListFromExtVolume(Root, RootSize, NumberOfFiles, Buffer);
}
#endif

//<AMI_PHDR_START>
//----------------------------------------------------------------------
//
// Procedure:	IsValidFile
//
// Description:	Wrapper for porting hook OemIsValidFile
//
//---------------------------------------------------------------------- 
//<AMI_PHDR_END>
BOOLEAN IsValidFile(
    IN VOID  *FileData,
    IN UINTN FileSize
)
{
    return OemIsValidFile(FileData, FileSize);
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------
//
// Procedure:	OemGetRecoveryFileInfo
//
// Description:	Porting hook to return recovery capsule filename and size
//
//---------------------------------------------------------------------- 
//<AMI_PHDR_END>
EFI_STATUS OemGetRecoveryFileInfo(
    IN EFI_PEI_SERVICES **PeiServices,
    IN OUT VOID         **pCapsuleName,
    IN OUT UINTN        *pCapsuleSize,
    OUT    BOOLEAN      *ExtendedVerification
);

//<AMI_PHDR_START>
//----------------------------------------------------------------------
//
// Procedure:	GetRecoveryFileInfo
//
// Description:	Wrapper for porting hook OemGetRecoveryFileInfo
//
//---------------------------------------------------------------------- 
//<AMI_PHDR_END>
EFI_STATUS GetRecoveryFileInfo(
    IN EFI_PEI_SERVICES **PeiServices,
    IN OUT VOID         **pCapsuleName,
    IN OUT UINTN        *pCapsuleSize,
    OUT    BOOLEAN      *ExtendedVerification
)
{
    if(pCapsuleName != NULL)
        *pCapsuleName = (CHAR8 *)RecoveryFileName;

    if(pCapsuleSize != NULL)
        *pCapsuleSize = (UINTN)RecoveryImageSize;

    if(ExtendedVerification != NULL)
        *ExtendedVerification = FALSE;

    return OemGetRecoveryFileInfo(PeiServices, pCapsuleName, pCapsuleSize, ExtendedVerification);
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------
//
// Procedure:	AmiGetRecoveryFileInfo
//
// Description:	Default porting hook value for OemGetRecoveryFileInfo
//
//---------------------------------------------------------------------- 
//<AMI_PHDR_END>
EFI_STATUS AmiGetRecoveryFileInfo(
    IN EFI_PEI_SERVICES **PeiServices,
    IN OUT VOID         **pCapsuleName,
    IN OUT UINTN        *pCapsuleSize,
    OUT    BOOLEAN      *ExtendedVerification
)
{
    return EFI_SUCCESS;
}

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
