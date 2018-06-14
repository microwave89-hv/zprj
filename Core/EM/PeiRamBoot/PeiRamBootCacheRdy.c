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
// $Header: /Alaska/SOURCE/Modules/PEI Ram Boot/PeiRamBootCacheRdy.c 2     8/28/15 3:53a Tristinchou $
//
// $Revision: 2 $
//
// $Date: 8/28/15 3:53a $
//**********************************************************************
// Revision History
// ----------------
// $Log: /Alaska/SOURCE/Modules/PEI Ram Boot/PeiRamBootCacheRdy.c $
// 
// 2     8/28/15 3:53a Tristinchou
// [TAG]  		EIP235157
// [Category]  	Improvement
// [Description]  	Security vulnerability - PeiRamBoot: Should leave cold
// boot optimization only
// 
// 1     4/22/11 1:39a Calvinchen
// Added Token "SAVE_ENTIRE_FV_TO_MEM" for OEM measure FV if needed. 
// 
// 
//
//**********************************************************************
//<AMI_FHDR_START>
//
// Name: PeiRamBootCacheRdy.c
//
// Description: PEI RAM BOOT Pei driver.
//
//<AMI_FHDR_END>
//**********************************************************************
//----------------------------------------------------------------------------
// Includes
// Statements that include other files
#include <PEI.h>
#include <AmiPeiLib.h>
#include <AmiCspLib.h>
#include <PeiRamBoot.h>
//----------------------------------------------------------------------------
// Function Externs
//----------------------------------------------------------------------------
// Local prototypes
EFI_GUID gRomCacheEnablePpiGuid = ROM_CACHE_ENABLE_PPI_GUID;

// PPI to be installed
EFI_PEI_PPI_DESCRIPTOR  RomCacheEnablePpiList[] = {
    {
        EFI_PEI_PPI_DESCRIPTOR_PPI | EFI_PEI_PPI_DESCRIPTOR_TERMINATE_LIST,
        &gRomCacheEnablePpiGuid, NULL
    }
};
//----------------------------------------------------------------------------
// Local Variables

//----------------------------------------------------------------------------
// Function Definitions
//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:   PeiRamBootCacheRdyEntry
//
// Description: PEI Entry Point for PeiRamBootCacheRdy Driver.
//
// Input:       EFI_FFS_FILE_HEADER*    - FfsHeader
//              EFI_PEI_SERVICES**      - PeiServices
//
// Output:      EFI_STATUS
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS
PeiRamBootCacheRdyEntry (
    IN EFI_FFS_FILE_HEADER  *FfsHeader,
    IN EFI_PEI_SERVICES     **PeiServices
)
{
    EFI_STATUS          Status;
    EFI_BOOT_MODE       BootMode;

    Status = (*PeiServices)->GetBootMode (PeiServices, &BootMode);
    if (EFI_ERROR(Status)) return Status;
    if ((BootMode == BOOT_ON_FLASH_UPDATE) || (BootMode == BOOT_ON_S3_RESUME) || \
        (BootMode == BOOT_IN_RECOVERY_MODE)) return Status;
    Status = (*PeiServices)->InstallPpi (PeiServices, RomCacheEnablePpiList);
    return Status;

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