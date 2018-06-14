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

//**********************************************************************
// $Header: /Alaska/SOURCE/Modules/AHCI/AhciAccess.c 3     2/11/11 4:09a Rameshr $
//
// $Revision: 3 $
//
// $Date: 2/11/11 4:09a $
//**********************************************************************
// Revision History
// ----------------
// $Log: /Alaska/SOURCE/Modules/AHCI/AhciAccess.c $
// 
// 3     2/11/11 4:09a Rameshr
// [TAG]  		EIP53704
// [Category]  	Improvement
// [Description]  	AMI headers update for Alaska Ahci Driver
// [Files]  		AhciAccess.c
// 
// 2     5/07/10 11:51a Krishnakumarg
// Update for coding standard.
// 
// 1     5/28/08 9:49a Rameshraju
// Initial Check-in for Index/Data access method.
//
//**********************************************************************
//<AMI_FHDR_START>
//
// Name: AhciAccess.c
//
// Description: Provides Index Data Port Access to AHCI Controller
//
//<AMI_FHDR_END>
//**********************************************************************
//#include <AmiDxeLib.h>

#define LBAR_REGISTER           0x20
#define LBAR_ADDRESS_MASK       0xFFFFFFE0
#define INDEX_OFFSET_FROM_LBAR  0x10
#define DATA_OFFSET_FROM_LBAR   0x14

#include "AmiDxeLib.h"
#include "Protocol\PciIo.h"

UINT16 IndexPort, DataPort;

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Name:        InitilizeIndexDataPortAddress
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
InitilizeIndexDataPortAddress (
    IN EFI_PCI_IO_PROTOCOL *PciIo
)
{
    EFI_STATUS Status;
    UINT32 lbar;

    Status = PciIo->Pci.Read(PciIo, EfiPciIoWidthUint32, LBAR_REGISTER, 1, &lbar);
    ASSERT_EFI_ERROR(Status);

    lbar &= LBAR_ADDRESS_MASK;  // Legacy Bus Master Base Address

    IndexPort = (UINT16)lbar + INDEX_OFFSET_FROM_LBAR;
    DataPort = (UINT16)lbar + DATA_OFFSET_FROM_LBAR;

    return EFI_SUCCESS;

}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Name:        ReadDataDword
//
// Description: Read the Dword Data using Index/Data access method
//
// Input:       BaseAddress - BaseAddress of AHCI Controller
//              Index       - Index address to read           
//
// Output:      Value Read
//              
//
//-------------------------------------------------------------------------
//<AMI_PHDR_END>
UINT32
ReadDataDword(
    IN  UINTN   BaseAddr,
    IN  UINTN   Index
)
{ 
    IoWrite32(IndexPort, (UINT32)Index);
    return IoRead32(DataPort);
}
//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Name:        WriteDataDword
//
// Description: WriteRead the Dword Data using Index/Data access method
//
// Input:       BaseAddress - BaseAddress of AHCI Controller
//              Index       - Index address to Write
//              Data        - Data to be written        
//
// Output:      Nothing
//              
//
//-------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID
WriteDataDword(
    IN  UINTN   BaseAddr,
    IN  UINTN   Index, 
    IN  UINTN   Data
)
{ 
    IoWrite32(IndexPort, (UINT32)Index);
    IoWrite32(DataPort, (UINT32)Data);
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Name:        ReadDataDword
//
// Description: Read the Word Data using Index/Data access method
//
// Input:       BaseAddress - BaseAddress of AHCI Controller
//              Index       - Index address to read           
//
// Output:      Value Read
//              
//
//-------------------------------------------------------------------------
//<AMI_PHDR_END>
UINT16
ReadDataWord(
    IN  UINTN   BaseAddr,
    IN  UINTN   Index
)
{ 
    IoWrite32(IndexPort, (UINT32)Index);
    return (UINT16)IoRead32(DataPort);
}
//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Name:        WriteDataDword
//
// Description: WriteRead the word Data using Index/Data access method
//
// Input:       BaseAddress - BaseAddress of AHCI Controller
//              Index       - Index address to Write
//              Data        - Data to be written        
//
// Output:      Nothing
//              
//
//-------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID
WriteDataWord(
    IN  UINTN   BaseAddr,
    IN  UINTN   Index, 
    IN  UINTN   Data
)
{ 
    IoWrite32(IndexPort, (UINT32)Index);
    IoWrite32(DataPort, (UINT16)Data);
}
//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Name:        ReadDataDword
//
// Description: Read the Byte Data using Index/Data access method
//
// Input:       BaseAddress - BaseAddress of AHCI Controller
//              Index       - Index address to read           
//
// Output:      Value Read
//              
//
//-------------------------------------------------------------------------
//<AMI_PHDR_END>
UINT8
ReadDataByte(
    IN  UINTN   BaseAddr,
    IN  UINTN   Index
)
{ 
    IoWrite32(IndexPort, (UINT32)Index);
    return (UINT8)IoRead32(DataPort);
}
//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Name:        WriteDataByte
//
// Description: WriteRead the Dword Data using Index/Data access method
//
// Input:       BaseAddress - BaseAddress of AHCI Controller
//              Index       - Index address to Write
//              Data        - Data to be written        
//
// Output:      Nothing
//              
//
//-------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID
WriteDataByte(
    IN  UINTN   BaseAddr,
    IN  UINTN   Index,
    IN  UINTN   Data
)
{ 
    IoWrite32(IndexPort, (UINT32)Index);
    IoWrite8(DataPort, (UINT8)Data);
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