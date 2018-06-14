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
// $Header: /Alaska/BIN/Chipset/Template/CSPLibrary/CspLibDxe.C 3     2/22/11 3:36p Artems $
//
// $Revision: 3 $
//
// $Date: 2/22/11 3:36p $
//
//*****************************************************************************
// Revision History
// ----------------
// $Log: /Alaska/BIN/Chipset/Template/CSPLibrary/CspLibDxe.C $
// 
// 3     2/22/11 3:36p Artems
// EIP 51548 - Added AMI copyright headers, replaced TABs with spaces
// 
// 2     6/11/09 5:43p Robert
// Comment updates for CHM and coding standard
// 
// 1     1/21/05 12:46p Sivagarn
// Initial Checkin - Version 0.05
//
//
//*****************************************************************************


//<AMI_FHDR_START>
//----------------------------------------------------------------------------
//
// Name:        CspLibDxe.C
//
// Description: This file contains code for Generic Csp protocols such as
//              PCI table init etc
//
//----------------------------------------------------------------------------
//<AMI_FHDR_END>


// Module specific Includes
#include "Efi.h"
#include "token.h"
#include <AmiLib.h>

#include "protocol\CspLibProtocols.h"

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   CspLibDxe_Init
//
// Description: 
//  This function is the entry point for this DXE. This function installs 
//  necessary Csp protocols
//
// Input:       
//  EFI_HANDLE ImageHandle - Image handle
//  EFI_SYSTEM_TABLE SystemTable - Pointer to the system table
//
// Output:      
//  Return Status currently always EFI_SUCCESS
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS
CspLibDxe_Init (
IN EFI_HANDLE           ImageHandle,
IN EFI_SYSTEM_TABLE   *SystemTable
  )
{
    EFI_STATUS          Status = EFI_SUCCESS;


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
