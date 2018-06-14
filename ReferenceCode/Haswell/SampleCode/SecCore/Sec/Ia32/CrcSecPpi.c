/*++
  This file contains an 'Intel Peripheral Driver' and is        
  licensed for Intel CPUs and chipsets under the terms of your  
  license agreement with Intel or your vendor.  This file may   
  be modified by the user, subject to additional terms of the   
  license agreement                                             
--*/
/*++

Copyright (c)  1999 - 2008 Intel Corporation. All rights reserved
This software and associated documentation (if any) is furnished
under a license and may only be used or copied in accordance
with the terms of the license. Except as permitted by such
license, no part of this software or documentation may be
reproduced, stored in a retrieval system, or transmitted in any
form or by any means without the express written consent of
Intel Corporation. 


Module Name:

  CrcSecPpi.c

Abstract:

  Install SecPlatformInformation PPI.

--*/

//#include "Tiano.h"
//#include "PeiCore.h"
//#include "FlashMap.h"
//#include "EfiFirmwareFileSystem.h"
//#include "EfiFirmwareVolumeHeader.h"

//#include EFI_PPI_DEFINITION (SecPlatformInformation)
#include "Tiano.h"
//#include <Core\Core_Pei\PeiCore.h>

//#include "Efi.h"
//#include "Pei.h"

#include "EfiCommonLib.h"
#include <Ppi\AmiEarlyBistPpi.h>
static EFI_GUID gAmiEarlyBistGuid = AMI_EARLY_BIST_PPI_GUID;

#include "SecPlatformInformation.h"

EFI_STATUS
SecPlatformInformation (
  IN EFI_PEI_SERVICES                    **PeiServices,
  IN OUT UINT64                          *StructureSize,
  IN OUT SEC_PLATFORM_INFORMATION_RECORD *PlatformInformationRecord
  );

EFI_SEC_PLATFORM_INFORMATION_PPI  mSecPlatformInformationPpi = { SecPlatformInformation };

EFI_PEI_PPI_DESCRIPTOR            mPeiSecPlatformInformationPpi = {
  (EFI_PEI_PPI_DESCRIPTOR_PPI | EFI_PEI_PPI_DESCRIPTOR_TERMINATE_LIST),
  &gEfiSecPlatformInformationPpiGuid,
  &mSecPlatformInformationPpi
};

EFI_STATUS
EFIAPI
SecPlatformInformation (
  IN EFI_PEI_SERVICES                    **PeiServices,
  IN OUT UINT64                          *StructureSize,
  IN OUT SEC_PLATFORM_INFORMATION_RECORD *PlatformInformationRecord
  )
/*++

Routine Description:

  Implementation of the PlatformInformation service in 
  EFI_SEC_PLATFORM_INFORMATION_PPI.
  This function conveys state information out of the SEC phase into PEI.

Arguments:

  PeiServices               - Pointer to the PEI Services Table.
  StructureSize             - Pointer to the variable describing size of the input buffer.
  PlatformInformationRecord - Pointer to the EFI_SEC_PLATFORM_INFORMATION_RECORD.
  
Returns:

  EFI_SUCCESS          - The data was successfully returned.
  EFI_BUFFER_TOO_SMALL - The buffer was too small.
  
--*/
{
    UINT32  *BIST;
    UINT32  Size;
    UINT32  Count;
    AMI_EARLY_BIST_PPI  *AmiEarlyPpi;
    EFI_STATUS Status;
    CPU_BIST PrivateBist;
    
	Status = (*PeiServices)->LocatePpi(
		PeiServices,
		&gAmiEarlyBistGuid,
		0, NULL,
		&AmiEarlyPpi
	); 
    //Force BIST no error if PPI not found
    if (Status != EFI_SUCCESS) {
        Size  = sizeof (UINT64);
        if ((*StructureSize) < (UINT64) Size) {
            *StructureSize = Size;
            return EFI_BUFFER_TOO_SMALL;
        }
        PrivateBist.ApicId = 0;
        PrivateBist.Bist = 0;
        BIST = (UINT32*)&PrivateBist;
    } else{   
        Count = AmiEarlyPpi->NumBists;
        Size  = Count * sizeof (UINT64);
        if ((*StructureSize) < (UINT64) Size) {
            *StructureSize = Size;
            return EFI_BUFFER_TOO_SMALL;
        }        
        BIST = (UINT32 *) (&(AmiEarlyPpi->CpuBist));
    }
    *StructureSize  = Size;
    EfiCommonLibCopyMem (PlatformInformationRecord, BIST, Size);
    
    return EFI_SUCCESS;
    
/*
  UINT32  *BIST;
  UINT32  Size;
  UINT32  Count;

  //
  // The entries of BIST information, together with the number of them,
  // reside in the bottom of stack, left untouched by normal stack operation.
  // This routine copies the BIST information to the buffer pointed by
  // PlatformInformationRecord for output.
  //
  Count = *(TopOfCar - 1);
  Size  = Count * sizeof (UINT64);

  if ((*StructureSize) < (UINT64) Size) {
    *StructureSize = Size;
    return EFI_BUFFER_TOO_SMALL;
  }

  *StructureSize  = Size;
  BIST            = (UINT32 *) ((UINT32) TopOfCar - sizeof (UINT32) - Size);

  EfiCommonLibCopyMem (PlatformInformationRecord, BIST, Size);

  return EFI_SUCCESS;
*/
}

//<AMI_PHDR_START>
//**********************************************************************
//
// Procedure:	CrcSecPlatformInformationPpi
//
// Description:	
//  Install SecPlatformInformation PPI that Intel Ivybridge CPU reference code needs.
//  (conveys state information out of the SEC phase into PEI)
//
// Input:
//	IN EFI_FFS_FILE_HEADER *FfsHeader - pointer to the header of the current firmware file system
//  IN EFI_PEI_SERVICES **PeiServices - pointer to the PeiServices Table
//
// Output:
//  EFI_SUCCESS
//
// Notes:	
//          
//**********************************************************************
//<AMI_PHDR_END>
//PeiInitialize eLink

EFI_STATUS EFIAPI CrcSecPlatformInformationPpi(
	IN EFI_FFS_FILE_HEADER *FfsHeader,
	IN EFI_PEI_SERVICES **PeiServices
){
	EFI_STATUS					Status;

	// Install the NB Init Policy PPI
	Status = (*PeiServices)->InstallPpi(PeiServices, &mPeiSecPlatformInformationPpi);

	return EFI_SUCCESS;
}


//	VOID
//	SecStartup (
//	  IN UINT32               SizeOfRam,
//	  IN UINT32               BootFirmwareVolume,
//	  IN PEI_MAIN_ENTRY_POINT PeiCoreEntryPoint
//	  )
/*++

Routine Description:

  Entry point to the C language phase of SEC. After the SEC assembly
  code has initialized some temporary memory and set up the stack,
  the control is transferred to this function.

Arguments:

  SizeOfRam          - Size of the temporary memory available for use.
  BootFirmwareVolume - Base address of the Boot Firmware Volume.
  PeiCoreEntryPoint  - Pointer to the entry point of the PEI core.
  
Returns:

  This function never returns

--*/
//	{
//	  EFI_PEI_STARTUP_DESCRIPTOR  PeiStartup;
//	
//	  PeiStartup.SizeOfCacheAsRam   = SizeOfRam;
//	  PeiStartup.BootFirmwareVolume = BootFirmwareVolume;
//	  PeiStartup.DispatchTable      = &mPeiSecPlatformInformationPpi;
//	
//	  //
//	  // Transfer the control to the PEI core
//	  //
//	  (*PeiCoreEntryPoint) (&PeiStartup);
//	
//	  //
//	  // Should not come here.
//	  //
//	  return ;
//	}
