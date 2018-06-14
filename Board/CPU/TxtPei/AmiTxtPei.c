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
// $Header: /Alaska/SOURCE/Modules/SharkBayRefCodes/Haswell/AMI Cpu PKG/AMI TXT PEI/AmiTxtPei.c 5     6/11/15 10:32p Crystallee $
//
// $Revision: 5 $
//
// $Date: 6/11/15 10:32p $
//**********************************************************************
// Revision History
// ----------------
// $Log: /Alaska/SOURCE/Modules/SharkBayRefCodes/Haswell/AMI Cpu PKG/AMI TXT PEI/AmiTxtPei.c $
// 
// 5     6/11/15 10:32p Crystallee
// [TAG]  		EIP207854
// [Category]  	Bug Fix
// [Severity]  	Important
// [Symptom]  	Txt test fail with TCG2 module
// [RootCause]  	Tokne TCG_SUPPORT was removed.
// [Solution]  	Add TCG2Support token.
// 
// 4     4/10/15 3:17a Crystallee
// 
// 3     9/13/12 4:15a Davidhsieh
// [TAG]  		None
// [Category]  	Bug Fix
// [Severity]  	Important
// [Symptom]  	Disable TCG support causes BIOS buiding error
// [RootCause]  	TCG setup data is used in TxtDxe and the data is not
// exist when TCG disabled.
// [Solution]  	Do not use TCG setup data when TCG disabled.
// 
// 2     8/22/12 3:29a Davidhsieh
// [TAG]  		None
// [Category]  	Improvement
// [Description]  	Install TPM_INITIALIZED_PPI  when TPM device is present
// TPM enabled in setup
// 
// 1     7/18/12 2:09a Davidhsieh
// [TAG]  		None
// [Category]  	Improvement
// [Description]  	AMI TXT PEI module part create
// 
//
//**********************************************************************
//<AMI_FHDR_START>
//
// Name:    AmiTxtPei.c
//
// Description:
//
//<AMI_FHDR_END>
//**********************************************************************
//
#include <PEI.h>
#include <AmiPeiLib.h>
#include <AmiCspLib.h>
#include <ppi\ReadOnlyVariable.h>
#include <Setup.h>
#include <token.h>

#define PEI_TPM_INITIALIZED_PPI_GUID \
  { \
    0xe9db0d58, 0xd48d, 0x47f6, 0x9c, 0x6e, 0x6f, 0x40, 0xe8, 0x6c, 0x7b, 0x41 \
  }

static EFI_GUID gPeiTpmInitializedPpiGuid = PEI_TPM_INITIALIZED_PPI_GUID;
static EFI_GUID gEfiPeiReadOnlyVariablePpiGuid = EFI_PEI_READ_ONLY_VARIABLE_PPI_GUID;
static EFI_GUID gEfiSetupGuid                  = SETUP_GUID;

static EFI_PEI_PPI_DESCRIPTOR Tpm_Initialized[] =
{ 
	{
		EFI_PEI_PPI_DESCRIPTOR_PPI | EFI_PEI_PPI_DESCRIPTOR_TERMINATE_LIST,
		&gPeiTpmInitializedPpiGuid, NULL 
	}
};

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:   AmiTxtPeiEntry
//
// Description: PEI Entry Point for Intel TXT Driver.
//
// Input:       EFI_HANDLE          - ImageHandle
//              EFI_SYSTEM_TABLE*   - SystemTable
//
// Output:      None.
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS
AmiTxtPeiEntry (
    IN EFI_FFS_FILE_HEADER  *FfsHeader,
    IN EFI_PEI_SERVICES     **PeiServices
)
{
        
    UINT8       *TpmBaseAddr = (UINT8*)0xfed40000;
    EFI_PEI_READ_ONLY_VARIABLE_PPI  *ReadOnlyVariable;
    EFI_STATUS  Status;
    UINTN       VariableSize;
    
    SETUP_DATA SetupData;

    if (*TpmBaseAddr != 0xff){  //If TPM device is present, check TPM setup data
        Status = (*PeiServices)->LocatePpi(
            PeiServices,
            &gEfiPeiReadOnlyVariablePpiGuid,
            0, 
            NULL,
            &ReadOnlyVariable       
        );                                        
    
        if (EFI_ERROR(Status)) return EFI_SUCCESS;
                                        
        VariableSize = sizeof(SETUP_DATA);
    
        Status = ReadOnlyVariable->GetVariable(
            PeiServices,
            L"Setup", 
            &gEfiSetupGuid,
            NULL,
            &VariableSize,  
            &SetupData
        );

		if ( EFI_ERROR(Status) ) return EFI_SUCCESS;

#if TCG_SUPPORT || TCG2Support
        if (SetupData.TpmSupport)   
            (*PeiServices)->InstallPpi(PeiServices, Tpm_Initialized);    //Install PPI if TPM device detected and enable in setup
#endif            
    }
    
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
