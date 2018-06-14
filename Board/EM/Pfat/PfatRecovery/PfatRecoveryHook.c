//*************************************************************************
//*************************************************************************
//**                                                                     **
//**        (C)Copyright 1985-2012, American Megatrends, Inc.            **
//**                                                                     **
//**                       All Rights Reserved.                          **
//**                                                                     **
//**      5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093           **
//**                                                                     **
//**                       Phone: (770)-246-8600                         **
//**                                                                     **
//*************************************************************************
//*************************************************************************

//**********************************************************************
// $Header: /Alaska/SOURCE/Modules/SharkBayRefCodes/IntelPfat/PfatRecovery/PfatRecoveryHook.c 2     5/29/13 5:45p Fredericko $
//
// $Revision: 2 $
//
// $Date: 5/29/13 5:45p $
//**********************************************************************
// Revision History
// ----------------
// $Log: /Alaska/SOURCE/Modules/SharkBayRefCodes/IntelPfat/PfatRecovery/PfatRecoveryHook.c $
// 
// 2     5/29/13 5:45p Fredericko
// [TAG]  		EIP124189
// [Description]  	[PFAT] Secure Flash is fail using
// 4.6.5.1_INTEL_PFAT_2_6 or 2_7
// [Files]  		PfatPubKeysAndBuildPsl.sdl
// Pfatrecovery.sdl
// PfatRecoveryHook.c
// Recovery.mak
//
// 1     4/05/13 5:37p Fredericko
// [TAG]  		EIP119706
// [Category]  	Improvement
// [Description]  	Support Recovery in pfat module
// [Files]  		PfatRecovery.cif
// PfatRecovery.sdl
// PfatRecovery.mak
// PfatRecovery.dxs
// PfatRecovery.c
// PfatRecoveryHook.c
//
//
//**********************************************************************
//<AMI_FHDR_START>
//----------------------------------------------------------------------
//
// Name:
//
// Description:
//
//----------------------------------------------------------------------
//<AMI_FHDR_END>

//----------------------------------------------------------------------------
// Includes
#include <AmiPeiLib.h>
#include <token.h>
#include <Setup.h>
#include <ppi\ReadOnlyVariable.h>

// Statements that include other files

//----------------------------------------------------------------------------
// Function Externs

//----------------------------------------------------------------------------
// Local prototypes
#if defined(SecFlashUpd_SUPPORT) && SecFlashUpd_SUPPORT == 1
EFI_STATUS
FwCapsuleInfo (
  IN EFI_PEI_SERVICES  **PeiServices,
  IN OUT VOID          **pCapsuleName,
  IN OUT UINTN         *pCapsuleSize,
  OUT   BOOLEAN        *ExtendedVerification
);
#else
AmiGetRecoveryFileInfo (
  IN EFI_PEI_SERVICES  **PeiServices,
  IN OUT VOID          **pCapsuleName,
  IN OUT UINTN         *pCapsuleSize,
  OUT   BOOLEAN        *ExtendedVerification
);
#endif

//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
// Local Variables
const char *RecoveryPfatFileName = CONVERT_TO_STRING(PFAT_RECOVERY_FILE);
const UINTN RecoveryPfatImageSize = PFAT_RECOVERY_IMAGE_SIZE; // 8k should be enough to cover Sec Capsule Hdr overhead

//----------------------------------------------------------------------------
// Function Definitions

//----------------------------------------------------------------------------
// Local Variables

//----------------------------------------------------------------------------
// Function Definitions
//<AMI_PHDR_START>
//----------------------------------------------------------------------
//
// Procedure:   PfatImageInfo
//
// Description:
//
// Input:       EFI_PEI_SERVICES**  PeiServices
//              VOID**              pPfatImageName
//              UINTN*              pPfatImageSize
//              BOOLEAN*            ExtendedVerification
//
// Output:      EFI_STATUS
//
//----------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS
PfatImageInfo (
  IN EFI_PEI_SERVICES  **PeiServices,
  IN OUT VOID          **pPfatImageName,
  IN OUT UINTN         *pPfatImageSize,
  OUT   BOOLEAN        *ExtendedVerification
){
    EFI_GUID                         gEfiPeiReadOnlyVariablePpiGuid = EFI_PEI_READ_ONLY_VARIABLE_PPI_GUID;
    EFI_PEI_READ_ONLY_VARIABLE_PPI   *ReadOnlyVar = NULL;
    EFI_GUID                         SetupGuid = SETUP_GUID;
    UINTN                            VariableSize= sizeof (SETUP_DATA);
    SETUP_DATA                       SetupData;
    EFI_STATUS                       Status;

    Status = (*PeiServices)->LocatePpi ( PeiServices, \
                                         &gEfiPeiReadOnlyVariablePpiGuid, \
                                         0, \
                                         NULL, \
                                         &ReadOnlyVar   );
    if ( !EFI_ERROR(Status) ) {
        Status = ReadOnlyVar->GetVariable (
                     PeiServices,
                     L"Setup",
                     &SetupGuid,
                     NULL,
                     &VariableSize,
                     &SetupData
                 );
        if ( EFI_ERROR( Status ) ) {
            return Status;
        }
    } else {
        return Status;
    }

    if ( SetupData.Pfatstate == 0 ) {
#if defined(SecFlashUpd_SUPPORT) && SecFlashUpd_SUPPORT == 1
	Status = FwCapsuleInfo(PeiServices, pPfatImageName, pPfatImageSize, ExtendedVerification);
#else
	Status = AmiGetRecoveryFileInfo(PeiServices, pPfatImageName, pPfatImageSize, ExtendedVerification);
#endif
        return Status;
    } else {
        if(!pPfatImageName && !pPfatImageSize && !ExtendedVerification )
            return EFI_UNSUPPORTED;

        if(ExtendedVerification != NULL)
            *ExtendedVerification = FALSE;

        *pPfatImageSize = RecoveryPfatImageSize;
        *pPfatImageName = (VOID*)RecoveryPfatFileName;
    }
    return EFI_SUCCESS;
}

//*************************************************************************
//*************************************************************************
//**                                                                     **
//**        (C)Copyright 1985-2011, American Megatrends, Inc.            **
//**                                                                     **
//**                       All Rights Reserved.                          **
//**                                                                     **
//**      5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093           **
//**                                                                     **
//**                       Phone: (770)-246-8600                         **
//**                                                                     **
//*************************************************************************
//*************************************************************************
