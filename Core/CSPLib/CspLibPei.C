//*************************************************************************
//*************************************************************************
//**                                                                     **
//**        (C)Copyright 1985-2008, American Megatrends, Inc.            **
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
//
// $Header: /Alaska/BIN/Chipset/Template/CSPLibrary/CspLibPei.C 17    7/14/11 2:44p Artems $
//
// $Revision: 17 $
//
// $Date: 7/14/11 2:44p $
//
//*****************************************************************************
// Revision History
// ----------------
// $Log: /Alaska/BIN/Chipset/Template/CSPLibrary/CspLibPei.C $
// 
// 17    7/14/11 2:44p Artems
// EIP 64106: Updated source to be UEFI 2.3.1 and PI 1.2 compliant
// 
// 16    3/23/11 1:02p Artems
// Bug fix - added backward compatibility with Core 4.6.4.1
// 
// 15    2/22/11 3:48p Artems
// EIP 51548 - Added AMI copyright headers, replaced TABs with spaces
// 
// 1     2/02/11 5:17p Artems
// 
// 14    5/07/10 10:09a Artems
// Fixed bug that causes build error when use Core 4.6.4.0
// 
// 13    5/06/10 12:22p Artems
// EIP 38241 - $FID signature is absent
// 
// 12    8/14/09 10:47a Robert
// Added FID.asm to the component for compliance with AMI Utility
// specification
// 
// 11    6/11/09 5:43p Robert
// Comment updates for CHM and coding standard
// 
// 10    10/13/07 11:49p Michaela
// added PciTableInit2 with a PCI access width parameter to support
// PCI initialization tables for various access widths
// 
// 9     2/16/07 6:13p Felixp
// Better handling of Firmware ID structure:
// 1. FW_VERSION_GUID and BIOS Tag come from SDL tokens.
// 2. Core/Project versions properly reported
// 3. CSM version removed
// 
// 5     6/06/05 3:20p Felixp
// updated to match PEI CIS 0.91 (CpuIo and PciCfg usage model changed)
// 
// 4     4/08/05 11:39a Sivagarn
// Included FID table
// 
// 3     2/15/05 12:29p Sivagarn
// Optimized the register programming call
// 
// 1     1/21/05 12:46p Sivagarn
// Initial Checkin - Version 0.05
//
//*****************************************************************************


//<AMI_FHDR_START>
//----------------------------------------------------------------------------
//
// Name:        CspLibPei.C
//
// Description: 
//  This file contains code for Generic CSP Library PEI functions.  The 
//  functions include PCI table update etc.
//
//----------------------------------------------------------------------------
//<AMI_FHDR_END>


//============================================================================
// Module specific Includes
#include <token.h>
#include <Efi.h>
#include <Pei.h>
#include <StatusCodes.h>
#include <AmiLib.h>
#include <AmiPeiLib.h>
#include <PPI\CspLibPpi.h>
#include <PPI\PCICfg.h>



//============================================================================
// GUID Definitions
EFI_GUID    gPeiPCITableInitPCIGUID = AMI_PEI_PCI_TABLE_INIT_PPI_GUID;

//============================================================================


#if CORE_REVISION <= 3
#include "ppi\FwVersion.h"
extern FW_VERSION   FwVersionData;
FW_VERSION *Version = &FwVersionData;
#endif    //#if CORE_REVISION <= 3

#ifndef PI_SPECIFICATION_VERSION //old Core

EFI_STATUS PciCfgModify(
    IN CONST EFI_PEI_SERVICES 	**PeiServices,
    IN EFI_PEI_PCI_CFG_PPI_WIDTH	Width,
    IN UINT64					Address,
    IN UINTN					SetBits,
    IN UINTN					ClearBits)
{
    if((*PeiServices)->PciCfg==NULL)
        return EFI_NOT_AVAILABLE_YET;

    return (*PeiServices)->PciCfg->Modify(
                    (EFI_PEI_SERVICES**)PeiServices,
                    (*PeiServices)->PciCfg,
                    Width, Address,
                    SetBits, ClearBits);
}
#endif


EFI_STATUS PciTableInit (
    IN EFI_PEI_SERVICES                **PeiServices,
    IN AMI_PEI_PCI_TABLE_INIT_PPI      *This,
    IN EFI_PEI_PCI_CFG2_PPI            *PciCfg,
    IN UINT64                          Address,
    IN AMI_PEI_PCI_INIT_TABLE_STRUCT   *PCIInitTable,
    IN UINT16                          wSize
);

EFI_STATUS PciTableInit2 (
    IN EFI_PEI_SERVICES                **PeiServices,
    IN AMI_PEI_PCI_TABLE_INIT_PPI      *This,
    IN EFI_PEI_PCI_CFG2_PPI            *PciCfg,        // OPTIONAL
    IN UINT64                          CfgAddress,
    IN AMI_PEI_PCI_INIT_TABLE_STRUCT2  *PciInitTable,
    IN UINT16                          TableEntries,
    IN EFI_PEI_PCI_CFG_PPI_WIDTH       AccessWidth
);


// PPI interface definition
AMI_PEI_PCI_TABLE_INIT_PPI  mPciTableInitPpi =
{
    PciTableInit,
    PciTableInit2,
};

static EFI_PEI_PPI_DESCRIPTOR mPpiList[] =  { 
    (EFI_PEI_PPI_DESCRIPTOR_PPI | EFI_PEI_PPI_DESCRIPTOR_TERMINATE_LIST),
    &gPeiPCITableInitPCIGUID,
    &mPciTableInitPpi};

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   PciTableInit
//
// Description: 
//  This function programs the PCI device with the values provided 
//  in the init table provided
//
// Input:
//  EFI_PEI_SERVICES **PeiServices - Pointer to the PEI Core data Structure
//  AMI_PEI_PCI_TABLE_INIT_PPI *This - Pointer to an instance of the AMI PEI PCI TABLE INIT PPI
//  EFI_PEI_PCI_CFG_PPI *PciCfg - Optional pointer to an instance of the PciCfg PPI
//  UINT64 Address - PCI address of the register to write to (Bus/Dev/Func/Reg)
//  AMI_PEI_PCI_INIT_TABLE_STRUCT *PCIInitTable - Table with register number, set and clear bits
//  UINT16 wSize - Table length (multiples of structure)
//
// Output:      
//  Always returns EFI_SUCCESS
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS PciTableInit (
    IN EFI_PEI_SERVICES                **PeiServices,
    IN AMI_PEI_PCI_TABLE_INIT_PPI      *This,
    IN EFI_PEI_PCI_CFG2_PPI            *PciCfg,
    IN UINT64                          Address,
    IN AMI_PEI_PCI_INIT_TABLE_STRUCT   *PCIInitTable,
    IN UINT16                          wSize)
{
    EFI_STATUS      Status = EFI_SUCCESS;
    UINTN           Index;
    UINT64          LocalAddr;


    if ((! wSize) || (!PCIInitTable))
        return Status;

    // Take data defined in the PCIInitTable and program the PCI devices
    // as ported
    for (Index = 0; Index < wSize; Index ++) {
        LocalAddr = Address + PCIInitTable[Index].bRegIndex;

        PciCfgModify( PeiServices, 
                      EfiPeiPciCfgWidthUint8,
                      LocalAddr, 
                      PCIInitTable[Index].bORMask, 
                      ~PCIInitTable[Index].bANDMask );
    }

    return EFI_SUCCESS;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   PciTableInit2
//
// Description: 
//  This function is identical to PciTableInit with the addition of an extra 
//  parameter to specify PCI access width.
//
// Input:
//  EFI_PEI_SERVICES **PeiServices - Pointer to the PEI Core data Structure
//  AMI_PEI_PCI_TABLE_INIT_PPI *This - Pointer to an instance of the AMI PEI PCI TABLE INIT PPI
//  EFI_PEI_PCI_CFG_PPI *PciCfg - Optional pointer to an instance of the PciCfg PPI
//  UINT64 CfgAddress - PCI address of the register to write to (Bus/Dev/Func/Reg)
//  AMI_PEI_PCI_INIT_TABLE_STRUCT2 *PCIInitTable - Table with register number, set and clear bits
//  UINT16 TableEntries - Table length (multiples of structure)
//  EFI_PEI_PCI_CFG_PPI_WIDTH AccessWidth - Register-level access width
//
// Output:      
//  Always returns EFI_SUCCESS
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS PciTableInit2 (
    IN EFI_PEI_SERVICES                **PeiServices,
    IN AMI_PEI_PCI_TABLE_INIT_PPI      *This,
    IN EFI_PEI_PCI_CFG2_PPI            *PciCfg,        // OPTIONAL
    IN UINT64                          CfgAddress,
    IN AMI_PEI_PCI_INIT_TABLE_STRUCT2  *PciInitTable,
    IN UINT16                          TableEntries,
    IN EFI_PEI_PCI_CFG_PPI_WIDTH       AccessWidth)
{
    EFI_STATUS      Status = EFI_SUCCESS;
    UINTN           Index;
    UINT64          LocalAddr;


    if ((! TableEntries) || (!PciInitTable))
        return Status;

    // Take data defined in the PCIInitTable and program the PCI devices
    // as ported
    for (Index = 0; 
         Index < TableEntries && !EFI_ERROR(Status); 
         Index ++) 
    {
        LocalAddr = CfgAddress + PciInitTable[Index].bRegIndex;

        Status = PciCfgModify( PeiServices,
                               AccessWidth,
                               LocalAddr,
                               PciInitTable[Index].bORMask,
                               PciInitTable[Index].bANDMask );
    }

    return EFI_SUCCESS;
}


//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   CspLibPei_Init
//
// Description: 
//  This function is the entry point for this PEI. This function initializes 
//  installs the CSP PPI
//
// Input:       
//  FfsHeader   Pointer to the FFS file header
//  PeiServices Pointer to the PEI services table
//
// Output:      
//  Return Status based on errors that are returned by the InstallPpi function
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS CspLibPei_Init (
    IN EFI_FFS_FILE_HEADER       *FfsHeader,
    IN EFI_PEI_SERVICES          **PeiServices)
{
    EFI_STATUS                  Status;

    // Install the NB Init Policy PPI
    Status = (*PeiServices)->InstallPpi(PeiServices, &mPpiList[0]);
#ifdef EFI_DEBUG
    if (Status) {
        PEI_TRACE((TRACE_PEI_CHIPSET, PeiServices, "CspLibPei_Init Return Code : %r\n", Status));
    }
#endif
    return Status;
}

//*************************************************************************
//*************************************************************************
//**                                                                     **
//**        (C)Copyright 1985-2008, American Megatrends, Inc.            **
//**                                                                     **
//**                       All Rights Reserved.                          **
//**                                                                     **
//**      5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093           **
//**                                                                     **
//**                       Phone: (770)-246-8600                         **
//**                                                                     **
//*************************************************************************
//*************************************************************************


