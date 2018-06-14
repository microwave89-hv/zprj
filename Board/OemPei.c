//**********************************************************************
//**********************************************************************
//**                                                                  **
//**        (C)Copyright 1985-2009, American Megatrends, Inc.         **
//**                                                                  **
//**                       All Rights Reserved.                       **
//**                                                                  **
//**         5555 Oakbrook Pkwy, Suite 200, Norcross, GA 30093        **
//**                                                                  **
//**                       Phone: (770)-246-8600                      **
//**                                                                  **
//**********************************************************************
//**********************************************************************
//**********************************************************************
//
// $Header: /Alaska/BIN/Board/OemPei.c 4     8/24/11 7:41a Felixp $
//
// $Revision: 4 $
//
// $Date: 8/24/11 7:41a $
//
//*****************************************************************************
// Revision History
// ----------------
// $Log: /Alaska/BIN/Board/OemPei.c $
// 
// 4     8/24/11 7:41a Felixp
// EIP 64107: Changes to support UEFI 2.3.1 and PI 1.2 specifications
// 
// 3     6/25/09 6:09p Robert
// Updated Comments and function headers
//
// 2     12/05/06 12:29p Felixp
// Diable OemPei.ffs by default
//
// 1     6/13/06 4:53p Sivagarn
// Initial Checkin
//
//
//*****************************************************************************


//<AMI_FHDR_START>
//----------------------------------------------------------------------------
//
// Name:        OEMPEI.C
//
// Description: This file contains code for Template OEM initialization
//              in the PEI stage
//
//----------------------------------------------------------------------------
//<AMI_FHDR_END>


// Module specific Includes
#include "Efi.h"
#include "Pei.h"
#include "token.h"
#include <AmiPeiLib.h>
#include <Hob.h>
#include <Setup.h>

// Produced/used PPI interfaces
#include <ppi\CspLibPpi.h>

// Produced PPIs

// GUID Definitions
EFI_GUID gAmiPEIPCITableInitPpiGuid = AMI_PEI_PCI_TABLE_INIT_PPI_GUID;
EFI_GUID gMasterBootModeGuid        = EFI_PEI_MASTER_BOOT_MODE_PEIM_PPI;
EFI_GUID gRecoveryBootModeGuid      = EFI_PEI_BOOT_IN_RECOVERY_MODE_PEIM_PPI;

// Portable Constants

// Function Prototypes

// Function Prototypes

// PPI interface definition

// PPI Definition

// PPI that are installed

// Function Definition

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   OEMPEI_Init
//
// Description: 
//  This function is the entry point for this PEI. This function programs OEM 
//  related changes common to complete board. This might involve programming 
//  SB/NB & SIO
//
// Input:       
//  FfsHeader   Pointer to the FFS file header
//  PeiServices Pointer to the PEI services table
//
// Output:      
//  EFI_STATUS - porting hook is empty so it returns EFI_SUCCESS
//
// Notes: 
//  This module is disabled by default. If you add code here, you need to 
//  enable $(BUILD_DIR)\OemPei.ffs eLink, which is child of FV_BB. Otherwise 
//  this module will not be included in the ROM image.
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS
EFIAPI
OEMPEI_Init (
  IN EFI_FFS_FILE_HEADER       *FfsHeader,
  IN EFI_PEI_SERVICES          **PeiServices
  )
{
    EFI_STATUS                  Status = EFI_SUCCESS;

    return Status;

}

//**********************************************************************
//**********************************************************************
//**                                                                  **
//**        (C)Copyright 1985-2009, American Megatrends, Inc.         **
//**                                                                  **
//**                       All Rights Reserved.                       **
//**                                                                  **
//**         5555 Oakbrook Pkwy, Suite 200, Norcross, GA 30093        **
//**                                                                  **
//**                       Phone: (770)-246-8600                      **
//**                                                                  **
//**********************************************************************
//**********************************************************************
