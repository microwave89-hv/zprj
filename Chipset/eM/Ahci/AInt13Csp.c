//**********************************************************************
//**********************************************************************
//**                                                                  **
//**        (C)Copyright 1985-2011, American Megatrends, Inc.         **
//**                                                                  **
//**                       All Rights Reserved.                       **
//**                                                                  **
//**         5555 Oakbrook Pkwy, Suite 200, Norcross, GA 30093        **
//**                                                                  **
//**                       Phone: (770)-246-8600                      **
//**                                                                  **
//**********************************************************************
//**********************************************************************

//****************************************************************************
// $Header: /Alaska/SOURCE/Modules/AHCI/INT13/CSP/AInt13Csp.c 3     2/10/11 10:52a Rameshr $
//
// $Revision: 3 $
//
// $Date: 2/10/11 10:52a $
//
//****************************************************************************
// Revision History
// ----------------
// $Log: /Alaska/SOURCE/Modules/AHCI/INT13/CSP/AInt13Csp.c $
// 
// 3     2/10/11 10:52a Rameshr
// [TAG]  		EIP53704
// [Category]  	Improvement
// [Description]  	AMI headers update for Alaska Ahci Driver
// [Files]  		AHCIACC.ASM
// HACCESS.EQU
// AHCI.EQU
// AINT13.EQU
// AInt13Csp.c
// 
// 2     5/28/08 9:44a Rameshraju
// Updated the AMI Address.
// 
// 1     12/07/07 11:17a Olegi
//
//****************************************************************************

//<AMI_FHDR_START>
//----------------------------------------------------------------------------
//
//  Name:           AINT13CSP.C
//  Description:    AHCI INT13 Support Chipset Configuration File
//
//----------------------------------------------------------------------------
//<AMI_FHDR_END>

#define LBAR_REGISTER		    0x20
#define LBAR_ADDRESS_MASK	    0xFFFFFFE0
#define INDEX_OFFSET_FROM_LBAR  0x10
#define DATA_OFFSET_FROM_LBAR   0x14

#include "AmiDxeLib.h"
#include "Protocol\PciIo.h"

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Name:        GetAccessInfo
//
// Description: This is chipset porting routine that returns index/data ports
//              to access memory-mapped registers.
//
// Input:       PciIo
//
// Output:      EFI_SUCCESS         - Access information is collected
//              EFI_ACCESS_DENIED   - No Access information avaliable
//
//-------------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS
GetAccessInfo (
    IN EFI_PCI_IO_PROTOCOL *PciIo,
    OUT UINT16  *AccessIndexPort,
    OUT UINT16  *AccessDataPort
)
{
    EFI_STATUS Status;
    UINT32 lbar;

    Status = PciIo->Pci.Read(PciIo, EfiPciIoWidthUint32, LBAR_REGISTER, 1, &lbar);
    ASSERT_EFI_ERROR(Status);

    lbar &= LBAR_ADDRESS_MASK;  // Legacy Bus Master Base Address

    *AccessIndexPort = (UINT16)lbar + INDEX_OFFSET_FROM_LBAR;
    *AccessDataPort = (UINT16)lbar + DATA_OFFSET_FROM_LBAR;

    return EFI_SUCCESS;

}


//**********************************************************************
//**********************************************************************
//**                                                                  **
//**        (C)Copyright 1985-2011, American Megatrends, Inc.         **
//**                                                                  **
//**                       All Rights Reserved.                       **
//**                                                                  **
//**         5555 Oakbrook Pkwy, Suite 200, Norcross, GA 30093        **
//**                                                                  **
//**                       Phone: (770)-246-8600                      **
//**                                                                  **
//**********************************************************************
//**********************************************************************
