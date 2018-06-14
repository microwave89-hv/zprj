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
// $Header: /Alaska/SOURCE/Modules/PEI Ram Boot/PeiRamBootOfbd.c 3     6/18/14 11:57p Calvinchen $
//
// $Revision: 3 $
//
// $Date: 6/18/14 11:57p $
//**********************************************************************
// Revision History
// ----------------
// $Log: /Alaska/SOURCE/Modules/PEI Ram Boot/PeiRamBootOfbd.c $
// 
// 3     6/18/14 11:57p Calvinchen
// Bug Fixed: System hangs with using AFU. 
// 
// 2     5/05/14 5:03a Calvinchen
// [TAG]  		EIP166551
// [Category]  	Spec Update
// [Severity]  	Important
// [Description]  	Runtime attribute set for the some of the variable used
// by PEI Ram Boot driver and needs to be reviewed
// [Files]  		PeiRamBootDxe.c
// PeiRamBootOfbd.c
// PeiRamBoot.chm
// PeiRamBoot.cif
// 
// 1     2/11/11 3:15a Calvinchen
// Bug Fixed : System hangs after reflashed BIOS with warm reset if
// PEI_RAM_BOOT_S3_SUPPORT = 1 with fast warm boot support.
// 
// 
//**********************************************************************
//<AMI_FHDR_START>
//
// Name:	PeiRamBootOfbd.c
//
// Description: If system updated BIOS with warm reset, PeiRamBoot module
//              will not copy rom to ram in sequence boot, and, it could 
//              cause system crashed. For avoiding this situation, BIOS 
//              delete the PEI RAM Boot related variables if system executed
//              AFU.
//
//<AMI_FHDR_END>
//**********************************************************************
//----------------------------------------------------------------------------
// Includes
// Statements that include other files
#include <AmiLib.h>
#include <AmiDxeLib.h>
#include <Setup.h>
#include <HOB.h>
#include "PeiRamBoot.h"
#include "OFBD.h"
//----------------------------------------------------------------------------
// Function Externs

//----------------------------------------------------------------------------
// Local prototypes
typedef EFI_STATUS (*SHOW_BOOT_TIME_VARIABLES)(BOOLEAN Show);
typedef struct{
    SHOW_BOOT_TIME_VARIABLES ShowBootTimeVariables;
} AMI_NVRAM_CONTROL_PROTOCOL;
static AMI_NVRAM_CONTROL_PROTOCOL  *gpNvramControl = NULL;

//----------------------------------------------------------------------------
// Local Variables

//----------------------------------------------------------------------------
// Function Definitions
//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	PeiRamBootOfbdEntry
//
// Description:	
//
// Input:
//      IN VOID             *Buffer
//      IN OUT UINT8        *pOFBDDataHandled
// Output:
//      VOID
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID PeiRamBootOfbdEntry (
    IN VOID             *Buffer,
    IN OUT UINT8        *pOFBDDataHandled )
{
    EFI_GUID                RomImageAddressGuid = ROM_IMAGE_ADDRESS_GUID;
    EFI_STATUS              Status;
    EFI_PHYSICAL_ADDRESS    HobRomImageAddress;
    UINTN                   VariableSize;
    static BOOLEAN          blIsProcessed = FALSE;
    
    if (blIsProcessed == FALSE) blIsProcessed = TRUE;
    else return;

    // Temporarily enable Nvram Variable Boot Time Access permission. 
    if (gpNvramControl) gpNvramControl->ShowBootTimeVariables(TRUE);

    VariableSize = sizeof(EFI_PHYSICAL_ADDRESS);
    Status = pRS->GetVariable ( L"HobRomImage", \
                                &RomImageAddressGuid, \
                                NULL, \
                                &VariableSize, \
                                &HobRomImageAddress );
    if (!EFI_ERROR(Status)) {
        // Delete HobRomImage Variable if system is executing AFU for forcing BIOS
        // copy rom to image in sequence boot.    
        VariableSize = 0;
        Status = pRS->SetVariable ( L"HobRomImage", \
                                    &RomImageAddressGuid, \
                                    EFI_VARIABLE_NON_VOLATILE | \
                                    EFI_VARIABLE_BOOTSERVICE_ACCESS,
                                    VariableSize, \
                                    &HobRomImageAddress );
    }
    // Disable Nvram Variable Boot Time Access permission. 
    if (gpNvramControl) gpNvramControl->ShowBootTimeVariables(FALSE);
    return;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	PeiRamBootOfbdInSmm
//
// Description:	
//
// Input:
//      VOID
//
// Output:
//      VOID
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID PeiRamBootOfbdInSmm (VOID)
{
    EFI_STATUS              Status;
    EFI_SMM_BASE2_PROTOCOL  *pSmmBase2;
    EFI_SMM_SYSTEM_TABLE2   *mSmst;
    UINTN                   i;
    EFI_CONFIGURATION_TABLE *Table;
    static EFI_GUID         gAmiNvramControlProtocolGuid = \
    { 0xf7ca7568, 0x5a09, 0x4d2c, { 0x8a, 0x9b, 0x75, 0x84, 0x68, 0x59, 0x2a, 0xe2 } };

    Status = pBS->LocateProtocol(&gEfiSmmBase2ProtocolGuid, NULL, &pSmmBase2);
    if (EFI_ERROR(Status)) return ;

    Status = pSmmBase2->GetSmstLocation (pSmmBase2, &mSmst);
    if (EFI_ERROR(Status)) return ;

	Table = mSmst->SmmConfigurationTable;
	for (i = mSmst->NumberOfTableEntries; i; --i, ++Table) {
		if (guidcmp(&Table->VendorGuid, &gAmiNvramControlProtocolGuid)) continue;
        gpNvramControl = (AMI_NVRAM_CONTROL_PROTOCOL*)Table->VendorTable;
        break;
	}
    return;
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
