//**********************************************************************
//**********************************************************************
//**                                                                  **
//**        (C)Copyright 1985-2012, American Megatrends, Inc.         **
//**                                                                  **
//**                       All Rights Reserved.                       **
//**                                                                  **
//**        5555 Oakbrook Pkwy, Suite 200, Norcross, GA 30093         **
//**                                                                  **
//**                       Phone: (770)-246-8600                      **
//**                                                                  **
//**********************************************************************
//**********************************************************************
//**********************************************************************
// $Header: /Alaska/SOURCE/Modules/SharkBayRefCodes/SwitchableGraphics/Sg TPV/SgTpvPei.c 4     10/30/13 6:42a Joshchou $
//
// $Revision: 4 $
//
// $Date: 10/30/13 6:42a $
//**********************************************************************
// Revision History
// ----------------
// $Log: /Alaska/SOURCE/Modules/SharkBayRefCodes/SwitchableGraphics/Sg TPV/SgTpvPei.c $
// 
// 4     10/30/13 6:42a Joshchou
// [TAG]  		None
// [Category]  	Improvement
// [Description]  	system assert after clear nvram,and we have give it
// value,so do not assert
// 
// 3     2/07/13 2:58a Joshchou
// [TAG]  		None
// [Category]  	Improvement
// [Description]  	Install a PPI for broadcasting OEM.
// 
// 2     9/09/12 11:15p Joshchou
// [TAG]  		EIPNone
// [Category]  	New Feature
// [Description]  	Tpv module support for sharkbay.
// [Files]  		SgTpv.sdl
// SgTpv.mak
// SgTpvPei.c
// SgTpvPei.dxs
// SgTpvDxe.c
// SgTpvDxe.dxs
// SgTpv.cif
// 
// 3     12/06/11 2:33a Alanlin
// [TAG]  		EIP76248
// [Category]  	New Feature
// [Description]  	PX 5.0 feature updated.
// 
// 2     10/14/11 2:54a Alanlin
// [TAG]  		EIP72054
// [Category]  	Improvement
// [Description]  	SgTpv is not compatible with SETUP_DATA_LAYOUT_OVERRIDE
// in core > 4.6.4.1
// [Files]  		Board\EM\SgTpv\SgTpvPei.c
// 
// 1     6/27/11 5:25a Alanlin
// [TAG]  		EIP61848
// [Category]  	New Feature
// [Description]  	Initial check-in.Integrated SwitchableGraphics Intel
// Reference code 0.6.0
// [Files]  		SgTpv.cif
// SgTpv.sdl
// SgTpv.mak
// SgTpvPei.c
// SgTpvPei.dxs
// SgTpvDxe.c
// SgTpvDxe.dxs
// 
// 
// 5     3/17/11 6:12p Alexp
// 1. Add nNvOptimusSMM module part
// 2. cleaned up SgTpvPei.c
// 3. Optimus:Add code to preserve HD AudioCodec enable flag in CMOS
// 
// 4     11/12/10 1:08p Alexp
// Update to match Intel HR SwitchableGraphics  Reference Code Version
// 1.00
// Code to set SSID for IGD moved to SgPei.c
// 
// 3     9/30/10 2:51p Alexp
//  [TAG]    	  EIP43103 ---> Set IGD SSID/SVID based on the SG mode 
// 
// 2     9/21/10 5:23p Alexp
// [TAG]    	  EIP43103 ---> re-arranged include statements
// 
// 1     9/17/10 1:12p Alexp
// [TAG]    	  EIP43103 
// [Category]  Function Request
// [Severity]	  Normal
// [Symptom]    Initial check-in of SgTPV module
// [RootCause] Request to implement SG reference code .
// [Solution]	Initial check-in. 
// [Files]	
//         SgTpv.cif;*.sdl;*.mak;
//         SgTpvPei.c;*.dxs;
//         SgTpvDxe.c;*.dxs  
// 
// 
//**********************************************************************

//<AMI_FHDR_START>
//----------------------------------------------------------------------------
//
// Name:		SgTpvPEI.c
//
// Description:	This file contains the PEI SG Entry point SgPei_Init.
//              The function updates SG Policy settings 
//
// Notes:		MAKE SURE NO PEI OR DXE SPECIFIC CODE IS NEEDED
//
//----------------------------------------------------------------------------
//<AMI_FHDR_END>

#include <Token.h>

#define SETUP_GUID { 0xEC87D643, 0xEBA4, 0x4BB5, 0xA1, 0xE5, 0x3F, 0x3E, 0x36, 0xB2, 0x0D, 0xA9 }

#if !defined(EDK_RELEASE_VERSION) || (EDK_RELEASE_VERSION < 0x00020000)
#include "EdkIIGluePeim.h"
#include "EdkIIGlueIoLib.h"
#endif

#include "Pei.h"

#include "SaAccess.h"

#include EFI_PPI_DEPENDENCY (Variable)
#include EFI_PPI_DEPENDENCY  (SaPlatformPolicy)
#include EFI_GUID_DEFINITION (SaDataHob)

static EFI_GUID	   gSetupGuid = SETUP_GUID;

#include <SetupDataDefinition.h>

EFI_GUID guidEndOfSgTpvPei = EFI_PEI_END_OF_SG_TPV_PPI_GUID;

static EFI_PEI_PPI_DESCRIPTOR EndOfSgTpvPpiList[] =
{
  {
	EFI_PEI_PPI_DESCRIPTOR_PPI | EFI_PEI_PPI_DESCRIPTOR_TERMINATE_LIST,
	&guidEndOfSgTpvPei, NULL 
  }
};

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   SgTpvPeiInit
//
// Description: This function is the entry point for this PEI. 
//
// Input:		FfsHeader	Pointer to the FFS file header
//	    		PeiServices	Pointer to the PEI services table
//
// Output:      Return Status based on errors that occurred while waiting for
//              time to expire.
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS
EFIAPI
SgTpvPeiInit (
  IN EFI_FFS_FILE_HEADER       *FfsHeader,
  IN EFI_PEI_SERVICES          **PeiServices
)
{
  EFI_STATUS                            Status;
  EFI_PEI_READ_ONLY_VARIABLE_PPI       *VariableServices;
  UINTN                                 VariableSize;
  SETUP_DATA                            SetupData;

  SA_PLATFORM_POLICY_PPI  *SaPlatformPolicyPpi;
  EFI_GUID                gSaPlatformPolicyPpiGuid = SA_PLATFORM_POLICY_PPI_GUID;

DEBUG ((EFI_D_ERROR, "==============SgTpvPeiInit==========\n"));
  //
  // Locate Variable Ppi
  //
  Status = (*PeiServices)->LocatePpi(PeiServices,
                                     &gPeiReadOnlyVariablePpiGuid,
                                     0,
                                     NULL,
                                     &VariableServices);

  //
  // Make sure we have a PPI, if not, just return.
  //
  if (!VariableServices) {
   	return EFI_UNSUPPORTED;
  }
  VariableSize = sizeof(SETUP_DATA);
  //
  // Get Setup Variable
  //
  Status = VariableServices->PeiGetVariable (
                    PeiServices,
                    L"Setup",
                    &gSetupGuid,
                    NULL,
                    &VariableSize,
                    &SetupData);

  if (EFI_ERROR(Status))
        return Status;

  //
  // Get platform policy settings through the SgPlatformPolicy PPI
  //
  Status = (**PeiServices).LocatePpi (
                            PeiServices,
                            &gSaPlatformPolicyPpiGuid,
                            0,
                            NULL,
                            &SaPlatformPolicyPpi
                            );
  ASSERT_EFI_ERROR (Status);

  //
  // GPIO Assigned from policy
  //

  //
  // Initialzie the Platform Configuration
  //

  //
  // Switchable Graphics mode set as MUXED (By default)
  //
  if( SetupData.PrimaryDisplay == 4 ) {
    SaPlatformPolicyPpi->PlatformData->SgMode              = SetupData.SgMuxMode;
    SaPlatformPolicyPpi->PlatformData->PXFixedDynamicMode  = SetupData.PX_FIXED_DYNAMIC_MODE;

  } else if ((SetupData.PrimaryDisplay == 1) || (SetupData.PrimaryDisplay == 3)) { // PEG || Auto

    SaPlatformPolicyPpi->PlatformData->SgMode              = 3;//SgModeDgpu;  

  } else if (SetupData.PrimaryDisplay == 0) { // IGFX
    //
    // In IGFX only mode mode set Switchable Gfx mode as Disabled
    //
    SaPlatformPolicyPpi->PlatformData->SgMode = SgModeDisabled;
  }

  //
  // Set SSID/SVID for IGD in SG mode only
  //
       SaPlatformPolicyPpi->PlatformData->SgSubSystemId = (UINT16)((SG_MUXLESS_SSVID_DID >> 16 )& 0xFFFF);
  (*PeiServices)->InstallPpi(PeiServices,EndOfSgTpvPpiList);
  return Status;
}

//**********************************************************************
//**********************************************************************
//**                                                                  **
//**        (C)Copyright 1985-2012, American Megatrends, Inc.         **
//**                                                                  **
//**                       All Rights Reserved.                       **
//**                                                                  **
//**        5555 Oakbrook Pkwy, Suite 200, Norcross, GA 30093         **
//**                                                                  **
//**                       Phone: (770)-246-8600                      **
//**                                                                  **
//**********************************************************************
//**********************************************************************
