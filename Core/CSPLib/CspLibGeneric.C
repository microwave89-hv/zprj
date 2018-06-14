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
// $Header: /Alaska/BIN/Chipset/Template/CSPLibrary/CspLibGeneric.C 7     11/12/11 6:39p Artems $
//
// $Revision: 7 $
//
// $Date: 11/12/11 6:39p $
//
//*****************************************************************************
// Revision History
// ----------------
// $Log: /Alaska/BIN/Chipset/Template/CSPLibrary/CspLibGeneric.C $
// 
// 7     11/12/11 6:39p Artems
// Added functions for TopSwap functionality
// 
// 6     2/22/11 3:33p Artems
// EIP 51548 - Added AMI copyright headers, replaced TABs with spaces
// 
// 5     3/31/10 11:31a Artems
// Updated function help header
// 
// 4     3/29/10 3:58p Artems
// Fixed OemRuntimeShadowRamWrite function help header
// 
// 3     3/25/10 3:07p Artems
// EIP 33953: Added eLink infrastructure to support runtime shadow ram
// writing
// 
// 2     6/11/09 5:43p Robert
// Comment updates for CHM and coding standard
// 
// 1     10/13/07 11:27p Michaela
// Initial Checkin
// 
// 1     10/05/07 7:02a Michaela
// Initial checkin.
//
//*****************************************************************************


//<AMI_FHDR_START>
//----------------------------------------------------------------------------
//
// Name:        CspLibGeneric.c
//
// Description: This file contains generic code to add functionality that can 
//              be used by any module.
//
//----------------------------------------------------------------------------
//<AMI_FHDR_END>

#include <Token.h>
#include "CspLibGeneric.h"


//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   LocateMultiplePpi
//
// Description: 
//  This function wraps the initialization and error checking of LocatePpi() 
//  in a table, in order to reduce code size in functions that use several PPI.
//
// Input:       
//  EFI_PEI_SERVICES **PeiServices - Instance of a pointer to the PeiServices pointer
//  UINT32 PpiTableSize  - Size of argument table
//  PPI_LOCATE_STRUCT *Ppi - Table of arguments for LocatePpi()
//
// Output:      
//  Pointers in PPI_LOCATE_STRUCT are updated
//  Status is returned with values defined by the LocatePpi function
//
// Note:
//  This function will use a Guid pointer or a Guid value defined locally 
//  in the PPI_LOCATE_STRUCT of the caller.
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS  LocateMultiplePpi (
    EFI_PEI_SERVICES    **PeiServices,
    UINT32              PpiTableSize,
    PPI_LOCATE_STRUCT   *Ppi
)
{
    EFI_STATUS          Status;
    UINT32              i;
    EFI_PEI_LOCATE_PPI  Locate = (*PeiServices)->LocatePpi;
    
    for (i = 0; i < PpiTableSize; i++) {
        //-------------------------------------------
        // locate the PPI (or) break on error
        Status = Locate( PeiServices,
                        (Ppi[i].Guid.Data1 == 0) 
                            ? Ppi[i].GuidPtr : &Ppi[i].Guid,
                        Ppi[i].Instance, 
                        Ppi[i].Descriptor, 
                        Ppi[i].Ptr );
        if (EFI_ERROR(Status)){
            break;
        }
    }
                                        
    return Status;
} 

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   LocateMultipleProtocol
//
// Description: 
//  This function wraps the initialization and error checking of 
//  LocateProtocol() in a table, in order to reduce code size in functions 
//  that use several Protocol.
//
// Input:       
//  EFI_BOOT_SERVICES *pBS - Instance of a pointer to the Boot Services Table
//  UINT32 ProtocolTableSize - Number of Protocols in the table
//  PROTOCOL_LOCATE_STRUCT *Protocol - Table of Parameters for LocateProtocol
//
// Output:      
//  Pointers in PROTOCOL_LOCATE_STRUCT are updated
//  Status is returned with values defined by the LocateProtocol function
//
// Note:        
//  This function will use a Guid pointer or a Guid value defined locally in 
//  the PROTOCOL_LOCATE_STRUCT of the caller.
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS  LocateMultipleProtocol (
    EFI_BOOT_SERVICES           *pBS,
    UINT32                      ProtocolTableSize,
    PROTOCOL_LOCATE_STRUCT      *Protocol
)
{
    EFI_STATUS          Status;
    UINT32              i;
    EFI_LOCATE_PROTOCOL Locate = pBS->LocateProtocol;
    
    for (i = 0; i < ProtocolTableSize; i++) {
        //-------------------------------------------
        // locate the PPI (or) break on error
        Status = Locate((Protocol[i].Guid.Data1 == 0) 
                            ? Protocol[i].GuidPtr 
                            : &Protocol[i].Guid,
                        Protocol[i].Registration, 
                        Protocol[i].Interface );
        if (EFI_ERROR(Status)){
            break;
        }
    }
                                        
    return Status;
} 


//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   PeiWritePci
//
// Description: 
//  This function writes a value to a PCI register using a PCI_CONTROL 
//  structure to simplify the call.
//
// Input:       
//  PEI_PCI_ARGS *Pci - control structure
//
// Output:      
//  Status is returned with values defined in the PCI PPI Write function
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS PeiWritePci (  
    PEI_PCI_ARGS     *Pci
)
{
    EFI_STATUS Status;
    Status = Pci->Cfg->Write(   Pci->PeiServices,
                                Pci->Cfg,
                                Pci->Width,
                                Pci->Address,
                                Pci->Value );
    return Status;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   PeiReadPci
//
// Description: 
//  This function reads the value in a PCI Register using a PCI_CONTROL 
//  structure to simplify the call.
//
// Input:       
//  PEI_PCI_ARGS *Pci - control structure
//
// Output:      
//  Pci->Value is updated with the value read from the PCI device
//  Status is returned with values defined in the PCI PPI Read function
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS PeiReadPci (  
    PEI_PCI_ARGS     *Pci
)
{
    EFI_STATUS Status;
    Status = Pci->Cfg->Read(   Pci->PeiServices,
                               Pci->Cfg,
                               Pci->Width,
                               Pci->Address,
                               Pci->Value );
    return Status;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   RbReadPci
//
// Description: 
//  This function reads the value(s) in a PCI Register using a RTBRG_PCI_ARGS 
//  structure to simplify the call.
//
// Input:       
//  RTBRG_PCI_ARGS *Arg - pointer to an instance of RTBRG_PCI_ARGS that contains parameters to the RootBrg PCI Read Function
//
// Output:      
//  Arg->Buffer is filled with the data read from the PCI device
//  Return the status returned by the PCI Read funcntion of the Root Bridge protocol
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS RbReadPci (
    RTBRG_PCI_ARGS  *Arg
)
{   
    EFI_STATUS Status =
        Arg->RtBrdg->Pci.Read( Arg->RtBrdg,
                                Arg->Width,     
                                Arg->Address, 
                                Arg->Count,
                                Arg->Buffer);
    return Status;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   RbWritePci
//
// Description: 
//  This function writes the value(s) in a PCI Register using a RTBRG_PCI_ARGS 
//  structure to simplify the call.
//
// Input:       
//  RTBRG_PCI_ARGS *Arg - pointer to an instance of RTBRG_PCI_ARGS that contains parameters to the RootBrg PCI Read Function
//
// Output:      
//  Return the status
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS RbWritePci (
    RTBRG_PCI_ARGS  *Arg
)
{   
    EFI_STATUS Status =
        Arg->RtBrdg->Pci.Write( Arg->RtBrdg,
                                Arg->Width,     
                                Arg->Address, 
                                Arg->Count,
                                Arg->Buffer);
    return Status;
}

//************** Runtime Shadow Ram access support ****************************
typedef VOID (RUNTIME_SHADOW_RAM_WRITE)(
    IN BOOLEAN Enable
);

extern RUNTIME_SHADOW_RAM_WRITE RUNTIME_SHADOW_RAM_WRITE_LIST EndOfList;
RUNTIME_SHADOW_RAM_WRITE* RuntimeShadowRamWriteList[] = {RUNTIME_SHADOW_RAM_WRITE_LIST NULL};

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   OemRuntimeShadowRamWrite
//
// Description: This function enables or disables runtime writing to shadow RAM
//              (E000-F000 segment)
//              
//
// Input:
//  IN BOOLEAN Enable - if TRUE - enable writing to shadow region
//                      if FALSE - disable writing to shadow region
//
// Output: VOID
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID OemRuntimeShadowRamWrite(
    IN BOOLEAN Enable
)
{
    UINTN i;
    
    for (i = 0; RuntimeShadowRamWriteList[i]; i++) 
        RuntimeShadowRamWriteList[i](Enable);
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   IsTopSwapOn
//
// Description: This function checks if TopSwap (A16 address line inversion)
//              is on
//              
//
// Input:
//  None
//
// Output:
//  TRUE - TopSwap is ON
//  FALSE - TopSwap is OFF
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
BOOLEAN IsTopSwapOn(
    VOID
)
{
  volatile UINT8* Address8;

  Address8 = (UINT8 *)(SB_RCBA + SB_BACKED_UP_CONTROL_REGISTER);

  return ((*Address8) & 1) ? TRUE : FALSE;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   SetTopSwap
//
// Description: This function sets TopSwap (A16 address line inversion) ON or OFF
//
// Input:
//  BOOLEAN On - if TRUE, set TopSwap to ON, if FALSE - set to OFF
//
// Output:
//  None
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID  SetTopSwap(
    IN BOOLEAN On
)
{
  volatile UINT8* Address8;

  Address8 = (UINT8 *)(SB_RCBA + SB_BACKED_UP_CONTROL_REGISTER);

  if (On) {
    *Address8 |= 1;
  } else {
    *Address8 &= 0xFE;
  }
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
