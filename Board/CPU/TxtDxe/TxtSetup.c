//*************************************************************************
//*************************************************************************
//**                                                                     **
//**        (C)Copyright 1987-2013, American Megatrends, Inc.            **
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
// $Header: /Alaska/SOURCE/Modules/SharkBayRefCodes/Haswell/AMI Cpu PKG/AMI TXT DXE/TxtSetup.c 2     10/14/12 11:49p Davidhsieh $
//
// $Revision: 2 $
//
// $Date: 10/14/12 11:49p $
//**********************************************************************
// Revision History
// ----------------
// $Log: /Alaska/SOURCE/Modules/SharkBayRefCodes/Haswell/AMI Cpu PKG/AMI TXT DXE/TxtSetup.c $
// 
// 2     10/14/12 11:49p Davidhsieh
// [TAG]  		None
// [Category]  	Improvement
// [Description]  	Use SBLib_ExtResetSystem when pRS->ResetSystem does not
// support GlobaRest type in the project
// 
// 1     8/14/12 5:05a Davidhsieh
// [TAG]  		EIP97190
// [Category]  	Improvement
// [Description]  	Changes in TXT Configuration require a Powercycle reset
// 
//
//
//**********************************************************************
//<AMI_FHDR_START>
//
// Name:    TXTSetup.c
//
// Description:
//
//<AMI_FHDR_END>
//**********************************************************************
//----------------------------------------------------------------------------
// Includes
#include <AmiLib.h>
#include <AmiDxeLib.h>
#include <Setup.h>
#include <AmiCspLib.h>
#include <SetupStrTokens.h>

#pragma pack (1)
typedef struct {
	UINT8	SMXSupport;
} SETUP_TXT_FEATURES;
#pragma pack ()

//----------------------------------------------------------------------------
// Local Variables

//----------------------------------------------------------------------------

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:   TxtExitSetupEvent
//
// Description: This routine for calling global reset if necessary.
//
// Input:       EFI_EVENT   - Efi event.
//              VOID*       - Image handle.
//
// Output:      None.
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
typedef enum {
  mColdReset,
  mWarmReset,
  mShutdownReset,
  mPowerCycleReset,
  mGlobalReset,
  mGlobalResetWithEc
} PCH_RESET_TYPE;

EFI_STATUS
TxtExitSetupEvent  (VOID)
{
    EFI_STATUS          Status;
    SETUP_DATA          SetupData;
    UINTN               VariableSize;
    EFI_GUID            SetupGuid = SETUP_GUID;
    // Get current Setup Data.
    VariableSize = sizeof(SETUP_DATA);
    Status = pRS->GetVariable ( L"Setup", \
                                &SetupGuid, \
                                NULL, \
                                &VariableSize, \
                                &SetupData );
    if (EFI_ERROR(Status)) return (Status);

    if ( SetupData.TxtSupport != 0 ) {
        // Generate Global Reset System if TXT is enabled w/o SMX enabled 
        if ((UINT16)(ReadMsr(0x3A) & 0xFF03) == 0xFF03) return EFI_SUCCESS; 
    } else { 
        // Generate Global Reset System if TXT is disabled with SMX enabled.
        if ((UINT16)(ReadMsr(0x3A) & 0xFF03) != 0xFF03) return EFI_SUCCESS; 
    }
    // PlatformResetSystem() of ReferenceCode\ME\..\PlatformReset.c
#if defined(RESET_RUNTIME_SERVICES_SUPPORT) && (RESET_RUNTIME_SERVICES_SUPPORT == 0)
    pRS->ResetSystem (mGlobalReset, EFI_SUCCESS, 0, NULL);
#else
    SBLib_ExtResetSystem (SbResetGlobal);
#endif
    EFI_DEADLOOP()
    return EFI_SUCCESS;
}

//*************************************************************************
//*************************************************************************
//**                                                                     **
//**        (C)Copyright 1987-2013, American Megatrends, Inc.            **
//**                                                                     **
//**                       All Rights Reserved.                          **
//**                                                                     **
//**      5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093           **
//**                                                                     **
//**                       Phone: (770)-246-8600                         **
//**                                                                     **
//*************************************************************************
//*************************************************************************