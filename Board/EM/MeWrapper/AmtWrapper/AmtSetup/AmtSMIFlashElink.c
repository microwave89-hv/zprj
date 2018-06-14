//*************************************************************************
//*************************************************************************
//**                                                                     **
//**        (C)Copyright 1985-2010, American Megatrends, Inc.            **
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
// $Header: /Alaska/SOURCE/Modules/SharkBayRefCodes/ME/AmtWrapper/AmtSetup/AmtSMIFlashElink.c 3     5/14/14 9:48p Tristinchou $
//
// $Revision: 3 $
//
// $Date: 5/14/14 9:48p $
//**********************************************************************
// Revision History
// ----------------
// $Log: /Alaska/SOURCE/Modules/SharkBayRefCodes/ME/AmtWrapper/AmtSetup/AmtSMIFlashElink.c $
// 
// 3     5/14/14 9:48p Tristinchou
// [TAG]  		EIP167030
// [Category]  	Improvement
// [Description]  	Remove the variable runtime attribute and keep original
// attributes.
// 
// 2     9/19/12 6:38a Klzhan
// Check MebxVariable exist or not before restore.
// 
// 1     4/24/12 12:38a Klzhan
// Update modulepart to latest
// 
// 1     2/16/12 9:01a Klzhan
// [TAG]  		EIP83223
// [Category]  	Improvement
// [Description]  	Restore MEBiosExtensionSetup when NVRam updated by AFU.
//
//**********************************************************************

//<AMI_FHDR_START>
//---------------------------------------------------------------------------
// Name:        AMTSMIFlashElink.c
//
// Description:	AMT TSE Functions.
//
//---------------------------------------------------------------------------
//<AMI_FHDR_END>
#include <AmiDxeLib.h>
#include "MeBiosExtensionSetup\MeBiosExtensionSetup.h"

ME_BIOS_EXTENSION_SETUP     BiosExtensionSetup;
UINT32                      mMebxSetupVariableDataAttr;
UINTN                       mMebxSetupVariableDataSize;
//<AMI_PHDR_START>
//----------------------------------------------------------------------
// Procedure:   PreserveMEBXSyncData
//
// Description: Restore the MEBiosExtensionSetup variable
//
// Input:       NONE
//
// Output:      NONE
//
// Returns:     NONE
//
//----------------------------------------------------------------------
//<AMI_PHDR_END>
VOID PreserveMEBXSyncData (VOID)
{

    EFI_STATUS  Status;

    mMebxSetupVariableDataSize = sizeof(ME_BIOS_EXTENSION_SETUP);
    Status = pRS->GetVariable ( gEfiMeBiosExtensionSetupName,
                                &gEfiMeBiosExtensionSetupGuid,
                                &mMebxSetupVariableDataAttr,
                                &mMebxSetupVariableDataSize,
                                &BiosExtensionSetup);

   if(EFI_ERROR(Status))
      mMebxSetupVariableDataSize = 0;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------
// Procedure:   RestoreMEBXSyncData
//
// Description: Restore the MEBiosExtensionSetup variable
//
// Input:       NONE
//
// Output:      NONE
//
// Returns:     NONE
//
//----------------------------------------------------------------------
//<AMI_PHDR_END>
VOID RestoreMEBXSyncData (VOID)
{
    EFI_STATUS  Status;

    if(mMebxSetupVariableDataSize == 0)
        return;

    Status = pRS->SetVariable (  gEfiMeBiosExtensionSetupName,
                                 &gEfiMeBiosExtensionSetupGuid,
                                 mMebxSetupVariableDataAttr,
                                 mMebxSetupVariableDataSize,
                                 &BiosExtensionSetup );
}
//*************************************************************************
//*************************************************************************
//**                                                                     **
//**        (C)Copyright 1985-2010, American Megatrends, Inc.            **
//**                                                                     **
//**                       All Rights Reserved.                          **
//**                                                                     **
//**      5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093           **
//**                                                                     **
//**                       Phone: (770)-246-8600                         **
//**                                                                     **
//*************************************************************************
//*************************************************************************