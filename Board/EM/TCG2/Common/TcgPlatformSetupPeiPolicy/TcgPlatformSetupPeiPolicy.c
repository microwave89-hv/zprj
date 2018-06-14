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
//**********************************************************************
// $Header: /Alaska/SOURCE/Modules/TCG2/Common/TcgPlatformSetupPeiPolicy/TcgPlatformSetupPeiPolicy.c 1     4/21/14 2:18p Fredericko $
//
// $Revision: 1 $
//
// $Date: 4/21/14 2:18p $
//**********************************************************************
// Revision History
// ----------------
// $Log: /Alaska/SOURCE/Modules/TCG2/Common/TcgPlatformSetupPeiPolicy/TcgPlatformSetupPeiPolicy.c $
// 
// 1     4/21/14 2:18p Fredericko
// 
// 2     12/10/13 12:56p Fredericko
// [TAG]  		EIP143615 
// [Category]  	Bug Fix
// [Severity]  	Minor
// [Symptom]  	Bitlocker WHCK failure
// [RootCause]  	PPI interface for TPM 1.2 device was failing
// [Solution]  	Fix the error in PPI interface error
// [Files]  		TcgPlatformSetupPeiPolicy.c
// 
// 1     10/08/13 12:05p Fredericko
// Initial Check-In for Tpm-Next module
// 
// 2     10/03/13 2:42p Fredericko
// 
// 1     7/10/13 5:56p Fredericko
// [TAG]  		EIP120969
// [Category]  	New Feature
// [Description]  	TCG (TPM20)
// 
// 4     9/07/12 11:00a Fredericko
// [TAG]  		EIP94081
// [Category]  	Bug Fix
// [Severity]  	Normal
// [Symptom]  	TcgPlatformSetupPeiPolicy.c does not load defaults when
// unable to load Setup variable
// [RootCause]  	Setupvariables not initialized if NVRAM is corrupted. 
// [Solution]  	Initialize TCG variables to default if NVRAM corrupted
// [Files]  		TcgPlatformSetupPeiPolicy.c
// 
// 3     12/18/11 10:24p Fredericko
// Changes to support TcgplatformPeiPolicy in relation to O.S. requests.
// 
// 2     10/07/11 6:52p Fredericko
// 
// 1     9/27/11 10:10p Fredericko
// [TAG]  		EIP67286
// [Category]  	Improvement
// [Description]  	Initial check-in for Tcg Setup policy for pei
// [Files]  		TcgPlatformSetupPeiPolicy.cif
// TcgPlatformSetupPeiPolicy.c
// TcgPlatformSetupPeiPolicy.h
// TcgPlatformSetupPeiPolicy.sdl
// TcgPlatformSetupPeiPolicy.mak
// TcgPlatformSetupPeiPolicy.dxs
// 
//**********************************************************************

//<AMI_FHDR_START>
//---------------------------------------------------------------------------
// Name: TcgPlatformpeipolicy.c
//
// Description:	Installs Tcg policy from setup variables in Pei
//
//---------------------------------------------------------------------------
//<AMI_FHDR_END>

#include <AmiPeiLib.h>
#include "TcgPlatformSetupPeiPolicy.h"

EFI_GUID  gTcgPlatformSetupPolicyGuid = TCG_PLATFORM_SETUP_PEI_POLICY_GUID;
EFI_GUID  gTcgPeiInternalflagsGuid = PEI_TCG_INTERNAL_FLAGS_GUID;
EFI_GUID  gTcgInternalPeiSyncflagGuid = TCG_PPI_SYNC_FLAG_GUID;


EFI_STATUS
 getTcgPeiPolicy (IN EFI_PEI_SERVICES     **PeiServices ,
                  IN TCG_CONFIGURATION    *ConfigFlags)

{
  EFI_STATUS              Status;
  EFI_PEI_READ_ONLY_VARIABLE_PPI *ReadOnlyVariable;
  EFI_GUID gPeiReadOnlyVariablePpiGuid
                                  = EFI_PEI_READ_ONLY_VARIABLE_PPI_GUID;
  UINTN                   VariableSize = sizeof(SETUP_DATA);
  SETUP_DATA              SetupData;
  EFI_GUID                gSetupGuid = SETUP_GUID;
  UINT8                   DisallowTpmFlag=0;
  UINT8                   SyncVar = 0;
  UINTN                   SyncVarSize = sizeof(UINT8);

  //
  //
  //
  Status = (*PeiServices)->LocatePpi(
                PeiServices,
                &gPeiReadOnlyVariablePpiGuid,
                0, NULL,
                &ReadOnlyVariable);

  PEI_TRACE((-1, PeiServices, "gPeiReadOnlyVariablePpiGuid Status = %r \n", Status)); 

  if(!EFI_ERROR(Status)){

    Status = ReadOnlyVariable->GetVariable(PeiServices,
								L"Setup",
								&gSetupGuid,
								NULL,
								&VariableSize,
								&SetupData);

    PEI_TRACE((-1, PeiServices, "gSetupGuid Status = %r \n", Status));

    if (EFI_ERROR(Status)) {
        ConfigFlags->TpmSupport           = 0;
        ConfigFlags->TcmSupport           = 0; 
        ConfigFlags->TpmEnable            = 0;
        ConfigFlags->TpmAuthenticate      = 0;
        ConfigFlags->TpmOperation         = 0;
        ConfigFlags->Tpm20Device          = 0;
    } else {
        ConfigFlags->TpmSupport           = SetupData.TpmSupport;
        ConfigFlags->TcmSupport           = SetupData.TcmSupport;
        ConfigFlags->TpmEnable            = SetupData.TpmEnable ;
        ConfigFlags->TpmAuthenticate      = SetupData.TpmAuthenticate;
        ConfigFlags->TpmOperation         = SetupData.TpmOperation;
        ConfigFlags->Tpm20Device          = SetupData.Tpm20Device;
        ConfigFlags->Reserved1            = SetupData.ShaPolicy;
    }
    
   
    VariableSize = sizeof(UINT8);
    Status = ReadOnlyVariable->GetVariable(PeiServices,
								L"InternalDisallowTpmFlag",
								&gTcgPeiInternalflagsGuid,
								NULL,
								&VariableSize,
								&DisallowTpmFlag);
    if(EFI_ERROR(Status)){
        Status = EFI_SUCCESS;
        DisallowTpmFlag = 0;
    }

    PEI_TRACE((-1, PeiServices, "gTcgPeiInternalflagsGuid Status = %r \n", Status));

    Status = ReadOnlyVariable->GetVariable(PeiServices,
                            L"TcgInternalSyncFlag",
                            &gTcgInternalPeiSyncflagGuid,
                            NULL,
                            &SyncVarSize,
                            &SyncVar);

    PEI_TRACE((-1, PeiServices, "gTcgInternalPeiSyncflagGuid Status = %r \n", Status));

    if(EFI_ERROR(Status)){
     SyncVar = 0;
     Status = EFI_SUCCESS;
    }  

    ConfigFlags->Reserved2                = 0;
    ConfigFlags->DisallowTpm              = DisallowTpmFlag;
    ConfigFlags->TpmHardware              = 0;
    ConfigFlags->TpmEnaDisable            = 0;
    ConfigFlags->TpmActDeact              = 0;
    ConfigFlags->TpmOwnedUnowned          = 0;
    ConfigFlags->TcgSupportEnabled        = 0;
    ConfigFlags->TpmError                 = 0;
    ConfigFlags->PpiSetupSyncFlag         = SyncVar;
    ConfigFlags->Reserved3                = 0;

    ConfigFlags->Reserved4              = 0;
    ConfigFlags->Reserved5              = 0;    
  }else{
    ConfigFlags->TpmSupport               = 0;
    ConfigFlags->TcmSupport               = 0;
    ConfigFlags->TpmEnable                = 0 ;
    ConfigFlags->TpmAuthenticate          = 0;
    ConfigFlags->TpmOperation             = 0;
    ConfigFlags->DisallowTpm              = 0;
    ConfigFlags->Reserved1                = 0;
    ConfigFlags->Reserved2                = 0;

    ConfigFlags->TpmHardware              = 0;
    ConfigFlags->TpmEnaDisable            = 0;
    ConfigFlags->TpmActDeact              = 0;
    ConfigFlags->TpmOwnedUnowned          = 0;
    ConfigFlags->TcgSupportEnabled        = 0;
    ConfigFlags->TpmError                 = 0;
    ConfigFlags->PpiSetupSyncFlag         = 0;
    ConfigFlags->Reserved3                = 0;

    ConfigFlags->Reserved4              = 0;
    ConfigFlags->Reserved5              = 0;
  }

  return Status;

}



static TCG_PLATFORM_SETUP_INTERFACE   TcgPlatformSetupInstance = {
    TCG_PLATFORM_SETUP_PEI_PROTOCOL_REVISION_1,
    getTcgPeiPolicy
};

static EFI_PEI_PPI_DESCRIPTOR TcgPlatformSetupPeiPolicyDesc[] = {
    {
        EFI_PEI_PPI_DESCRIPTOR_PPI
        | EFI_PEI_PPI_DESCRIPTOR_TERMINATE_LIST,
        &gTcgPlatformSetupPolicyGuid,
        &TcgPlatformSetupInstance
    }
};



//**********************************************************************
//<AMI_PHDR_START>
//
// Procedure:   TcgPlatformSetupPolicyEntryPoint
//
// Description:  Entry point for TcgPlatformSetupPolicyEntryPoint
//
// Input:       ImageHandle       Image handle of this driver.
//              SystemTable       Global system service table.
//
// Output:      EFI_STATUS
//
// Modified:
//
// Referrals:   
//
// Notes:       
//<AMI_PHDR_END>
//**********************************************************************
EFI_STATUS
EFIAPI
TcgPlatformSetupPeiPolicyEntryPoint (
  IN EFI_FFS_FILE_HEADER *FfsHeader,
  IN EFI_PEI_SERVICES    **PeiServices
)
{
  EFI_STATUS 	                Status;
  EFI_PEI_READ_ONLY_VARIABLE_PPI *ReadOnlyVariable;
  EFI_GUID gPeiReadOnlyVariablePpiGuid
                                  = EFI_PEI_READ_ONLY_VARIABLE_PPI_GUID;
  UINTN                          VariableSize = sizeof(SETUP_DATA);
  SETUP_DATA                     SetupData;
  EFI_GUID                       gSetupGuid = SETUP_GUID;


  Status = (*PeiServices)->LocatePpi(
                PeiServices,
                &gPeiReadOnlyVariablePpiGuid,
                0, NULL,
                &ReadOnlyVariable);

  if (EFI_ERROR(Status))
    return EFI_SUCCESS;

  Status = ReadOnlyVariable->GetVariable(PeiServices,
								L"Setup",
								&gSetupGuid,
								NULL,
								&VariableSize,
								&SetupData);

  Status = (**PeiServices).InstallPpi (PeiServices, TcgPlatformSetupPeiPolicyDesc);
 
  return Status;
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
