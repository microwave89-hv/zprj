//*************************************************************************
//*************************************************************************
//**                                                                     **
//**        (C)Copyright 1985-2009, American Megatrends, Inc.            **
//**                                                                     **
//**                       All Rights Reserved.                          **
//**                                                                     **
//**      5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093           **
//**                                                                     **
//**                       Phone: (770)-246-8600                         **
//**                                                                     **
//*************************************************************************
//*************************************************************************

//*****************************************************************************
// $Header: /Alaska/SOURCE/Core/EDK/PeiMain/PciCfg.c 12    8/12/11 12:24p Artems $
//
// $Revision: 12 $
//
// $Date: 8/12/11 12:24p $
//*****************************************************************************
// Revision History
// ----------------
// $Log: /Alaska/SOURCE/Core/EDK/PeiMain/PciCfg.c $
// 
// 12    8/12/11 12:24p Artems
// EIP 64107: Added changes for module to be compliant with PI
// specification v 1.2
// 
// 11    3/22/11 5:15p Felixp
// Method of invocation of the in-memory entry point has changed 
// from LOAD_HOB to eLink registered under PeiCoreMemoryInstalled.
// This is more efficient.
// 
// 10    2/05/11 3:44p Artems
// Changed functions calling interfaces to meet PI 1.0 specification
// requirements
// 
// 9     11/05/09 5:01p Oleksiyy
// EIP 27821 Support for 64 bit operations in PciRead and PciWrite added.
// To use this functions  CpuIo.c, IA32CLib.c, x64AsmLib.asm files should
// be updated also.
// 
// 8     7/08/09 5:53p Vyacheslava
// Updated according to the coding standards.
//
// 7     6/16/05 10:56a Felixp
// 1. Once memory is available, PEI Core PEIMs that created PEIM_LOAD_HOB
// are reallocated to memory.
// 2. ImagePei.c removed
// 3. FileLoader moved from DxeIpl to PEI Core
//
// 6     6/06/05 7:49p Felixp
//
// 5     6/06/05 1:25p Felixp
//
// 4     6/03/05 3:45p Felixp
// Updated to support changes introduced in PEI CIS 0.91
//
// 3     3/04/05 9:43a Mandal
//
// 2     1/18/05 3:21p Felixp
// PrintDebugMessage renamed to Trace
//
// 1     12/23/04 9:42a Felixp
//
// 8     1/28/04 3:24a Felixp
//
// 7     1/27/04 3:58a Felixp
// Bug fixes and improvements as a part of PEI CORE integration
//
// 6     12/29/03 5:25p Felixp
// preffix 'EFI_' added to the names of the PEIM descriptor structures and
// flags
//
// 5     12/15/03 4:35p Robert
//
// 4     12/15/03 4:25p Robert
//
// 3     12/15/03 12:41p Robert
// changed position of GUID definition below PPI include
//
// 2     12/15/03 11:54a Robert
// Updated the definitions of PPI includes and removed the entry point
// definitions
//
// 1     12/11/03 5:34p Robert
// Initial Check in
//
//*****************************************************************************
//<AMI_FHDR_START>
//
// Name:    PciCfg.c
//
// Description: This file contains the implementation of the PCI Cfg I/O
//      specification.  For questions about the specification refer to the
//      PEI CIS specification chapter 9
//
//<AMI_FHDR_END>
//*****************************************************************************

// Module specific Includes
#include <AmiPeiLib.h>
// PPI Produced
#include <PPI/PciCfg2.h>

// Module specific macros
// Make a PCI Access address out of the value that is passed in.  Clear the lowest 2 bits
//  PCI accesses are always 4 byte aligned
#define GET_PCI_ADDRESS(x) \
(0x080000000 | (((UINTN)x & 0x0FF000000) >> 8) | (((UINTN)x & 0x0FF0000)>> 5) | (x & 0x0700) | (x & 0x0FC))

// Function Prototypes
EFI_STATUS PciRead (
    IN CONST  EFI_PEI_SERVICES                  **PeiServices,
    IN CONST  EFI_PEI_PCI_CFG2_PPI              *This,
    IN        EFI_PEI_PCI_CFG_PPI_WIDTH         Width,
    IN        UINT64                            Address,
    IN OUT    VOID                              *Buffer
);

EFI_STATUS PciWrite (
    IN CONST  EFI_PEI_SERVICES                  **PeiServices,
    IN CONST  EFI_PEI_PCI_CFG2_PPI              *This,
    IN        EFI_PEI_PCI_CFG_PPI_WIDTH         Width,
    IN        UINT64                            Address,
    IN OUT    VOID                              *Buffer
);

EFI_STATUS PciModify (
    IN CONST  EFI_PEI_SERVICES                  **PeiServices,
    IN CONST  EFI_PEI_PCI_CFG2_PPI              *This,
    IN        EFI_PEI_PCI_CFG_PPI_WIDTH         Width,
    IN        UINT64                            Address,
#if PI_SPECIFICATION_VERSION<0x00010000
    IN        UINTN                             SetBits,
    IN        UINTN                             ClearBits
#else
	IN VOID							            *SetBits,
	IN VOID							            *ClearBits
#endif
);


// Local Definitions
EFI_PEI_PCI_CFG2_PPI  mPciCfgPpi = {
    PciRead, 
    PciWrite, 
    PciModify
};

static EFI_PEI_PPI_DESCRIPTOR mPpiList[] = {
    {
        EFI_PEI_PPI_DESCRIPTOR_PPI | EFI_PEI_PPI_DESCRIPTOR_TERMINATE_LIST,
        &gEfiPciCfg2PpiGuid, 
        &mPciCfgPpi
    }
};

// Function Definitions

//<AMI_PHDR_START>
//============================================================================
// Procedure:   PciCfgMemInit
//
// Description: This function installs the PCI Configuration PPI and exits
//
// Input:
//      *FfsHeader - pointer to the header of the current firmware file system
//      **PeiServices - pointer to the Pei Services function and data structure
//
// Output:  EFI_SUCCESS
//
//============================================================================
//<AMI_PHDR_END>

EFI_STATUS EFIAPI PciCfgMemInit (
    IN EFI_FFS_FILE_HEADER       *FfsHeader,
    IN EFI_PEI_SERVICES          **PeiServices
)
{
    // update PCI Config pointer
    (*PeiServices)->PciCfg = &mPciCfgPpi;
    return EFI_SUCCESS;
}

//<AMI_PHDR_START>
//============================================================================
// Procedure:   PciCfgInit
//
// Description: This function installs the PCI Configuration PPI and exits
//
// Input:
//      *FfsHeader - pointer to the header of the current firmware file system
//      **PeiServices - pointer to the Pei Services function and data structure
//
// Output:  EFI_SUCCESS
//
//============================================================================
//<AMI_PHDR_END>

EFI_STATUS EFIAPI PciCfgInit (
    IN EFI_PEI_FILE_HANDLE       FfsHeader,
    IN EFI_PEI_SERVICES          **PeiServices
)
{
    EFI_STATUS  Status;
    
    // Install the PCI Config Ppi
    (*PeiServices)->PciCfg = &mPciCfgPpi;
    Status = (*PeiServices)->InstallPpi( PeiServices, mPpiList );
    return Status;
}

//<AMI_PHDR_START>
//============================================================================
// Procedure:   PciRead
//
// Description: This function Reads a value from the PCI Config space and
//              returns that value in Buffer.
//
// Input:
//      **PeiServices - Pointer to the PEI Core data Structure
//      *This - Pointer to the instance of the PCI Config PPI
//      Width - Size of the data to be read from the configuration space
//      Address - PCI address of the register to be read(Bus/Dev/Func/Reg)
//      *Buffer - The data read from the requested PCI Configuration register
//
// Output:  EFI_SUCCESS
//
//============================================================================
//<AMI_PHDR_END> 

EFI_STATUS PciRead (
    IN CONST  EFI_PEI_SERVICES                  **PeiServices,
    IN CONST  EFI_PEI_PCI_CFG2_PPI              *This,
    IN        EFI_PEI_PCI_CFG_PPI_WIDTH       Width,
    IN        UINT64                          Address,
    IN OUT    VOID                            *Buffer
)
{
    UINT64              IoAddr;
    UINT32              PciAddr;
    EFI_PEI_CPU_IO_PPI  *CpuIo = (*PeiServices)->CpuIo;
    EFI_PEI_PCI_CFG_PPI_WIDTH       TmpWidth;
    UINT8               *Buffer8=(UINT8*)Buffer;
    
    if (((Width & 3) == EfiPeiPciCfgWidthUint16) && (Address & 0x01))
        return EFI_INVALID_PARAMETER;
    if (((Width & 3) >= EfiPeiPciCfgWidthUint32) && (Address & 0x03))
        return EFI_INVALID_PARAMETER;
    // Make a usable PCI address out of the Address passed in
    PciAddr = (UINT32)GET_PCI_ADDRESS(Address);
    
    // Access 0xCF8 and use corrected address to enable the read to PCI
    IoAddr = 0x0CF8;
    CpuIo->Io.Write(
        PeiServices,
        CpuIo,
        EfiPeiCpuIoWidthUint32,
        IoAddr,
        1,
        (VOID*)(&PciAddr)
    );
    
    // Access 0xCFC to get the data requested.  Increment IoAddr to
    //  read the correct register from the PCI Config space
    IoAddr = 0x0CFC + (Address & 0x03);

    TmpWidth=Width;

    if ((Width & 3) > EfiPeiPciCfgWidthUint32)TmpWidth=Width-1;
    // Read the register requested.  Use the passed in Width value to
    //  indicate the number of bytes to read. If Width = 8 bytes - split into two reads
    CpuIo->Io.Read(
            PeiServices,
            CpuIo,
            TmpWidth,
            IoAddr,
            1,
            (VOID*)Buffer8
    );
        // no formatting should be needed on the output data.  Read the correct
        //  register and the correct width should format the data properly
    
    if (Width == TmpWidth) return EFI_SUCCESS;
    
    IoAddr = 0x0CF8;
    PciAddr = PciAddr + 4;
    CpuIo->Io.Write(
        PeiServices,
        CpuIo,
        EfiPeiCpuIoWidthUint32,
        IoAddr,
        1,
        (VOID*)(&PciAddr)
    );
    // Read the next 4 bytes    
    IoAddr = 0x0CFC;
    CpuIo->Io.Read(
            PeiServices,
            CpuIo,
            TmpWidth,
            IoAddr,
            1,
            (VOID*)(Buffer8+4)
        );
    

    

    return EFI_SUCCESS;
}

//<AMI_PHDR_START>
//============================================================================
// Procedure:   PciWrite
//
// Description: This function writes a value to the PCI Config space
//
// Input:
//      **PeiServices - Pointer to the PEI Core data Structure
//      *This - Pointer to the instance of the PCI Config PPI
//      Width - Size of the data to write to the configuration space
//      Address - PCI address of the register to write to (Bus/Dev/Func/Reg)
//      *Buffer - The data to write to the requested PCI Configuration register
//
// Output:  EFI_SUCCESS
//
//============================================================================
//<AMI_PHDR_END>

EFI_STATUS PciWrite (
    IN CONST  EFI_PEI_SERVICES                  **PeiServices,
    IN CONST  EFI_PEI_PCI_CFG2_PPI              *This,
    IN        EFI_PEI_PCI_CFG_PPI_WIDTH       Width,
    IN        UINT64                          Address,
    IN OUT    VOID                            *Buffer
)
{
    UINT64              IoAddr;
    UINT32              PciAddr;
    EFI_PEI_CPU_IO_PPI  *CpuIo = (*PeiServices)->CpuIo;
    EFI_PEI_PCI_CFG_PPI_WIDTH       TmpWidth;
    UINT8               *Buffer8=(UINT8*)Buffer;
    if (((Width & 3) == EfiPeiPciCfgWidthUint16) && (Address & 0x01))
        return EFI_INVALID_PARAMETER;
    if (((Width & 3) >= EfiPeiPciCfgWidthUint32) && (Address & 0x03))
        return EFI_INVALID_PARAMETER;
    
    // Make a usable PCI address out of the Address passed in
    PciAddr = (UINT32)GET_PCI_ADDRESS(Address);
    
    // Access 0xCF8 and use corrected address to enable the read to PCI
    IoAddr = 0x0CF8;
    CpuIo->Io.Write(
        PeiServices,
        CpuIo,
        EfiPeiCpuIoWidthUint32,
        IoAddr,
        1,
        (VOID*)(&PciAddr)
    );
    
    // Access 0xCFC to get the data requested.  Increment IoAddr to
    //  read the correct register from the PCI Config space
    IoAddr = 0x0CFC + (Address & 0x03);
    
    TmpWidth=Width;

    if ((Width & 3) > EfiPeiPciCfgWidthUint32) TmpWidth = Width - 1;
    //  Write the register requested.  Use the passed in Width value to
    //  indicate the number of bytes to read. If Width = 8 bytes - split into two writes
    CpuIo->Io.Write(
            PeiServices,
            CpuIo,
            TmpWidth,
            IoAddr,
            1,
            (VOID*)Buffer8
    );
        
    
    if (Width == TmpWidth) return EFI_SUCCESS;
    
    // Access 0xCF8 and use next 4 bytes address to enable the read to PCI
    IoAddr = 0x0CF8;
    PciAddr = PciAddr + 4;
    CpuIo->Io.Write(
        PeiServices,
        CpuIo,
        EfiPeiCpuIoWidthUint32,
        IoAddr,
        1,
        (VOID*)(&PciAddr)
    );

    // Write the next 4 bytes    
    IoAddr = 0x0CFC;
    CpuIo->Io.Write(
            PeiServices,
            CpuIo,
            TmpWidth,
            IoAddr,
            1,
            (VOID*)(Buffer8+4)
        );
    

    return EFI_SUCCESS;
}

//<AMI_PHDR_START>
//============================================================================
// Procedure:   PciModify
//
// Description: This function modifies a value in the PCI Config space.
//      This function uses the SetBits and ClearBits values to modify the
//      register.  First the ClearBits value is used to clear the unwanted bits
//      then the SetBits value is used to set the wanted bits.
//
// Input:
//      **PeiServices - Pointer to the PEI Core data Structure
//      *This - Pointer to the instance of the PCI Config PPI
//      Width - Size of the data to write to the configuration space
//      Address - PCI address of the register to write to (Bus/Dev/Func/Reg)
//      SetBits - The bits in the register that need to be set
//      ClearBits - The bits in the register that should be cleared
//
// Output:  EFI_SUCCESS
//
//============================================================================
//<AMI_PHDR_END>

EFI_STATUS PciModify (
    IN CONST  EFI_PEI_SERVICES                  **PeiServices,
    IN CONST  EFI_PEI_PCI_CFG2_PPI              *This,
    IN        EFI_PEI_PCI_CFG_PPI_WIDTH         Width,
    IN        UINT64                            Address,
#if PI_SPECIFICATION_VERSION<0x00010000
    IN        UINTN                             SetBits,
    IN        UINTN                             ClearBits
#else
	IN VOID							            *SetBits,
	IN VOID							            *ClearBits
#endif
)
{
    EFI_STATUS  Status;
    UINTN       Data;
    if (((Width & 3) == EfiPeiPciCfgWidthUint16) && (Address & 0x01))
        return EFI_INVALID_PARAMETER;
    if (((Width & 3) >= EfiPeiPciCfgWidthUint32) && (Address & 0x03))
        return EFI_INVALID_PARAMETER;
    
    Status = PciRead (
        PeiServices,
        This,
        Width,
        Address,
        &Data
    );
#if PI_SPECIFICATION_VERSION<0x00010000   
    Data = SetBits | (Data & (~ClearBits));
#else
    Data = *(UINTN*)SetBits | (Data & (~*(UINTN*)ClearBits));
#endif    
    Status = PciWrite (
        PeiServices,
        This,
        Width,
        Address,
        &Data
    );
    
    return Status;
}

//*************************************************************************
//*************************************************************************
//**                                                                     **
//**        (C)Copyright 1985-2009, American Megatrends, Inc.            **
//**                                                                     **
//**                       All Rights Reserved.                          **
//**                                                                     **
//**      5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093           **
//**                                                                     **
//**                       Phone: (770)-246-8600                         **
//**                                                                     **
//*************************************************************************
//*************************************************************************
