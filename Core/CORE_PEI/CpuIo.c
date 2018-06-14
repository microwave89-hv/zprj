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
// $Header: /Alaska/SOURCE/Core/EDK/PeiMain/CpuIo.c 13    3/22/11 5:14p Felixp $
//
// $Revision: 13 $
//
// $Date: 3/22/11 5:14p $
//*****************************************************************************
// Revision History
// ----------------
// $Log: /Alaska/SOURCE/Core/EDK/PeiMain/CpuIo.c $
// 
// 13    3/22/11 5:14p Felixp
// Method of invocation of the in-memory entry point has changed 
// from LOAD_HOB to eLink registered under PeiCoreMemoryInstalled.
// This is more efficient.
// 
// 12    2/05/11 3:43p Artems
// Changed functions calling interface (added CONST qualifiers) as
// required by PI 1.0 specification
// 
// 11    11/05/09 4:59p Oleksiyy
// EIP 27821 Support for 64 bit operations in IoRead and IoWrite added. To
// use this functions   IA32CLib.c, x64AsmLib.asm files should be updated
// also.
// 
// 10    7/08/09 5:53p Vyacheslava
// Updated according to the coding standards.
//
// 9     6/16/05 10:56a Felixp
// 1. Once memory is available, PEI Core PEIMs that created PEIM_LOAD_HOB
// are reallocated to memory.
// 2. ImagePei.c removed
// 3. FileLoader moved from DxeIpl to PEI Core
//
// 8     6/10/05 5:49p Felixp
// Bug fixes in MemRead, MemWrite, IoRead, IoWrite
//
// 7     6/06/05 7:48p Felixp
//
// 6     6/06/05 1:25p Felixp
//
// 5     6/03/05 3:45p Felixp
// Updated to support changes introduced in PEI CIS 0.91
//
// 4     3/04/05 9:38a Mandal
//
// 3     2/01/05 2:35a Felixp
//
// 2     1/18/05 3:21p Felixp
// PrintDebugMessage renamed to Trace
//
// 1     12/23/04 9:42a Felixp
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
// 3     12/15/03 12:40p Robert
// changed position of GUID definition below PPI include
//
// 2     12/15/03 11:49a Robert
// updated PPI definitions and removed entry point definitions
//
// 1     12/11/03 5:34p Robert
// Initial Check In
//
//*****************************************************************************
//<AMI_FHDR_START>
//
// Name:    CpuIo.c
//
// Description: This file contains the implementation of the CPU I/O
//      specification.  For questions about the specification refer to the
//      PEI CIS specification chapter 9
//
//<AMI_FHDR_END>
//*****************************************************************************

// Module specific Includes
#include <AmiPeiLib.h>
#include <AmiHobs.h>
// Produced PPIs
#include <PPI/CpuIo.h>

// Function Prototypes
static EFI_STATUS LocalMemRead (
    IN      CONST EFI_PEI_SERVICES          **PeiServices,
    IN      CONST EFI_PEI_CPU_IO_PPI        *This,
    IN      EFI_PEI_CPU_IO_PPI_WIDTH  Width,
    IN      UINT64                    Address,
    IN      UINTN                     Count,
    IN OUT  VOID                      *Buffer
);

static EFI_STATUS LocalMemWrite  (
    IN      CONST EFI_PEI_SERVICES          **PeiServices,
    IN      CONST EFI_PEI_CPU_IO_PPI        *This,
    IN      EFI_PEI_CPU_IO_PPI_WIDTH  Width,
    IN      UINT64                    Address,
    IN      UINTN                     Count,
    IN OUT  VOID                      *Buffer
);

static EFI_STATUS LocalIoRead (
    IN      CONST EFI_PEI_SERVICES          **PeiServices,
    IN      CONST EFI_PEI_CPU_IO_PPI        *This,
    IN      EFI_PEI_CPU_IO_PPI_WIDTH  Width,
    IN      UINT64                    Address,
    IN      UINTN                     Count,
    IN OUT  VOID                      *Buffer
);

static EFI_STATUS LocalIoWrite  (
    IN      CONST EFI_PEI_SERVICES          **PeiServices,
    IN      CONST EFI_PEI_CPU_IO_PPI        *This,
    IN      EFI_PEI_CPU_IO_PPI_WIDTH  Width,
    IN      UINT64                    Address,
    IN      UINTN                     Count,
    IN OUT  VOID                      *Buffer
);

static UINT8 LocalIoRead8 (
    IN  CONST EFI_PEI_SERVICES      **PeiServices,
    IN  CONST EFI_PEI_CPU_IO_PPI    *This,
    IN  UINT64                Address
);

static UINT16 LocalIoRead16 (
    IN  CONST EFI_PEI_SERVICES      **PeiServices,
    IN  CONST EFI_PEI_CPU_IO_PPI    *This,
    IN  UINT64                Address
);

static UINT32 LocalIoRead32 (
    IN  CONST EFI_PEI_SERVICES      **PeiServices,
    IN  CONST EFI_PEI_CPU_IO_PPI    *This,
    IN  UINT64                Address
);

static UINT64 LocalIoRead64 (
    IN  CONST EFI_PEI_SERVICES      **PeiServices,
    IN  CONST EFI_PEI_CPU_IO_PPI    *This,
    IN  UINT64                Address
);

static VOID LocalIoWrite8 (
    IN  CONST EFI_PEI_SERVICES      **PeiServices,
    IN  CONST EFI_PEI_CPU_IO_PPI    *This,
    IN  UINT64                Address,
    IN  UINT8                 Data
);

static VOID LocalIoWrite16 (
    IN  CONST EFI_PEI_SERVICES      **PeiServices,
    IN  CONST EFI_PEI_CPU_IO_PPI    *This,
    IN  UINT64                Address,
    IN  UINT16                Data
);

static VOID LocalIoWrite32 (
    IN  CONST EFI_PEI_SERVICES      **PeiServices,
    IN  CONST EFI_PEI_CPU_IO_PPI    *This,
    IN  UINT64                Address,
    IN  UINT32                Data
);

static VOID LocalIoWrite64 (
    IN  CONST EFI_PEI_SERVICES      **PeiServices,
    IN  CONST EFI_PEI_CPU_IO_PPI    *This,
    IN  UINT64                Address,
    IN  UINT64                Data
);

static UINT8 MemRead8 (
    IN  CONST EFI_PEI_SERVICES      **PeiServices,
    IN  CONST EFI_PEI_CPU_IO_PPI    *This,
    IN  UINT64                Address
);

static UINT16 MemRead16 (
    IN  CONST EFI_PEI_SERVICES      **PeiServices,
    IN  CONST EFI_PEI_CPU_IO_PPI    *This,
    IN  UINT64                Address
);

static UINT32 MemRead32 (
    IN  CONST EFI_PEI_SERVICES      **PeiServices,
    IN  CONST EFI_PEI_CPU_IO_PPI    *This,
    IN  UINT64                Address
);

static UINT64 MemRead64 (
    IN  CONST EFI_PEI_SERVICES      **PeiServices,
    IN  CONST EFI_PEI_CPU_IO_PPI    *This,
    IN  UINT64                Address
);

static VOID MemWrite8 (
    IN  CONST EFI_PEI_SERVICES      **PeiServices,
    IN  CONST EFI_PEI_CPU_IO_PPI    *This,
    IN  UINT64                Address,
    IN  UINT8                 Data
);

static VOID MemWrite16 (
    IN  CONST EFI_PEI_SERVICES      **PeiServices,
    IN  CONST EFI_PEI_CPU_IO_PPI    *This,
    IN  UINT64                Address,
    IN  UINT16                Data
);

static VOID MemWrite32 (
    IN  CONST EFI_PEI_SERVICES      **PeiServices,
    IN  CONST EFI_PEI_CPU_IO_PPI    *This,
    IN  UINT64                Address,
    IN  UINT32                Data
);

static VOID MemWrite64 (
    IN  CONST EFI_PEI_SERVICES      **PeiServices,
    IN  CONST EFI_PEI_CPU_IO_PPI    *This,
    IN  UINT64                Address,
    IN  UINT64                Data
);

// PPI interface definition
static EFI_PEI_CPU_IO_PPI mCpuIoPpi = {
    {LocalMemRead, LocalMemWrite},
    {LocalIoRead, LocalIoWrite},
    LocalIoRead8, LocalIoRead16, LocalIoRead32, LocalIoRead64,
    LocalIoWrite8, LocalIoWrite16, LocalIoWrite32, LocalIoWrite64,
    MemRead8, MemRead16, MemRead32, MemRead64,
    MemWrite8, MemWrite16, MemWrite32, MemWrite64
};

// PPI that are installed
static EFI_PEI_PPI_DESCRIPTOR mPpiList[] = {
    {
        EFI_PEI_PPI_DESCRIPTOR_PPI | EFI_PEI_PPI_DESCRIPTOR_TERMINATE_LIST,
        &gPeiCpuIoPpiInServiceTableGuid, 
        NULL
    }
};

// Function Definitions
EFI_STATUS EFIAPI CpuIoMemInit (
    IN EFI_FFS_FILE_HEADER       *FfsHeader,
    IN EFI_PEI_SERVICES          **PeiServices
)
{
    // Update the CpuIo pointer
    (*PeiServices)->CpuIo = &mCpuIoPpi;
    return EFI_SUCCESS;
}

//<AMI_PHDR_START>
//============================================================================
// Procedure:   CpuIoInit
//
// Description: This function installs the CPU I/O PPI and exits
//
// Input:
//      *FfsHeader - pointer to the header of the current firmware file system
//      **PeiServices - pointer to the Pei Services function and data structure
//
// Output:  always returns EFI_SUCCESS
//
//============================================================================
//<AMI_PHDR_END>

EFI_STATUS EFIAPI CpuIoInit (
    IN EFI_FFS_FILE_HEADER       *FfsHeader,
    IN EFI_PEI_SERVICES          **PeiServices
)
{
    EFI_STATUS      Status;
    
    // Install the CpuIo Ppi
    (*PeiServices)->CpuIo = &mCpuIoPpi;
    Status = (*PeiServices)->InstallPpi( PeiServices, mPpiList );
    
    return Status;
}

//<AMI_PHDR_START>
//============================================================================
// Procedure:   CalcAddrChanges
//
// Description: This function determines which addresses need to be changed
//      as data is read or written.
//
// Input:
//      Width - Contains the width and type of memory or I/O read that is needed
//
// Output:
//      *In - The number of bytes to increment the input buffer address after
//              every read or write access
//      *Out - The number of bytes to increment the output buffer address after
//              every read or write access
//
//============================================================================
//<AMI_PHDR_END>

VOID CalcAddrChanges(
    IN  EFI_PEI_CPU_IO_PPI_WIDTH    Width,
    OUT UINTN                       *In,
    OUT UINTN                       *Out
)
{
    // get the number of bytes per read or write access and the turn that into
    //  an Hex Address Incrementing value
    *In = *Out = 1 << (Width % 4);
    
    if ( (Width >= EfiPeiCpuIoWidthFifoUint8) && 
         (Width <= EfiPeiCpuIoWidthFifoUint64) )
        *Out = 0;
        
    else if ( (Width >= EfiPeiCpuIoWidthFillUint8) && 
              (Width <= EfiPeiCpuIoWidthFillUint64) )
        *In = 0;
}


//<AMI_PHDR_START>
//============================================================================
// Procedure:   LocalIoRead8
//
// Description: This function is called to read a byte from the I/O space
//
// Input:
//      **PeiServices - pointer to the Pei Services function and data structure
//      *This - Pointer to the instance of the CPU I/O PPI structure
//      Address - A 64 bit address that points to the location to be read from
//
// Output:  UINT8 - This is the value read from the I/O space specified by the
//                      value passed in by the input variable Address
//
//============================================================================
//<AMI_PHDR_END>

static UINT8 LocalIoRead8 (
    IN CONST EFI_PEI_SERVICES **PeiServices,
    IN CONST EFI_PEI_CPU_IO_PPI *This,
    IN UINT64 Address
)
{
    return IoRead8 ((UINT16) Address);
}


//<AMI_PHDR_START>
//============================================================================
// Procedure:   LocalIoRead16
//
// Description: This function is called to read a word from the I/O space
//
// Input:
//      **PeiServices - pointer to the Pei Services function and data structure
//      *This - Pointer to the instance of the CPU I/O PPI structure
//      Address - A 64 bit address that points to the location to be read from
//
// Output:  UINT16 - This is the value read from the I/O space specified by the
//                      by the input variable Address
//
//============================================================================
//<AMI_PHDR_END>

static UINT16 LocalIoRead16 (
    IN CONST EFI_PEI_SERVICES **PeiServices,
    IN CONST EFI_PEI_CPU_IO_PPI *This,
    IN UINT64 Address
)
{
    return IoRead16 ((UINT16) Address);
}


//<AMI_PHDR_START>
//============================================================================
// Procedure:   LocalIoRead32
//
// Description: This function is called to read a dword from the I/O space
//
// Input:
//      **PeiServices - pointer to the Pei Services function and data structure
//      *This - Pointer to the instance of the CPU I/O PPI structure
//      Address - A 64 bit address that points to the location to be read from
//
// Output:  UINT32 - This is the value read from the I/O space specified by the
//                      value passed in by the input variable Address
//
//============================================================================
//<AMI_PHDR_END>

static UINT32 LocalIoRead32 (
    IN CONST EFI_PEI_SERVICES **PeiServices,
    IN CONST EFI_PEI_CPU_IO_PPI *This,
    IN UINT64 Address
)
{
    return IoRead32 ((UINT16) Address);
}



//<AMI_PHDR_START>
//============================================================================
// Procedure:   LocalIoRead64
//
// Description: This function is called to read a qword from the I/O space
//      This function is not available in a 32bit system so we just return 0 if
//      it is called. We cannot remove this function because it is part of the
//      specification
//
// Input:
//      **PeiServices - pointer to the Pei Services function and data structure
//      *This - Pointer to the instance of the CPU I/O PPI structure
//      Address - A 64 bit address that points to the location to be read from
//
// Output:  UINT64 - This is the value read from the I/O space specified by the
//                      value passed in by the input variable Address
//
//============================================================================
//<AMI_PHDR_END>
static UINT64 LocalIoRead64 (
    IN CONST EFI_PEI_SERVICES **PeiServices,
    IN CONST EFI_PEI_CPU_IO_PPI *This,
    IN UINT64 Address
)
{
    return IoRead64 ((UINT16) Address);
}


//<AMI_PHDR_START>
//============================================================================
// Procedure:   LocalIoWrite8
//
// Description: This function is called to write a byte to the I/O space
//
// Input:
//      **PeiServices - pointer to the Pei Services function and data structure
//      *This - Pointer to the instance of the CPU I/O PPI structure
//      Address - A 64 bit address that points to the location to be written to
//      Buffer8 -   The value to be written to location specified by Address
//
// Output:  None
//
//============================================================================
//<AMI_PHDR_END>

static VOID LocalIoWrite8 (
    IN CONST EFI_PEI_SERVICES **PeiServices,
    IN CONST EFI_PEI_CPU_IO_PPI *This,
    IN UINT64 Address,
    IN UINT8  Buffer8
)
{
    IoWrite8 ((UINT16) Address, Buffer8);
}


//<AMI_PHDR_START>
//============================================================================
// Procedure:   LocaIoWrite16
//
// Description: This function is called to write a word to the I/O space
//
// Input:
//      **PeiServices - pointer to the Pei Services function and data structure
//      *This - Pointer to the instance of the CPU I/O PPI structure
//      Address - A 64 bit address that points to the location to be written to
//      Buffer16 -  The value to be written to location specified by Address
//
// Output:  VOID
//
//============================================================================
//<AMI_PHDR_END>

static VOID LocalIoWrite16 (
    IN CONST EFI_PEI_SERVICES **PeiServices,
    IN CONST EFI_PEI_CPU_IO_PPI *This,
    IN UINT64 Address,
    IN UINT16 Buffer16
)
{
    IoWrite16 ((UINT16) Address, Buffer16);
}


//<AMI_PHDR_START>
//============================================================================
// Procedure:   LocaIoWrite32
//
// Description: This function is called to write a dword to the I/O space
//
// Input:
//      **PeiServices - pointer to the Pei Services function and data structure
//      *This - Pointer to the instance of the CPU I/O PPI structure
//      Address - A 64 bit address that points to the location to be written to
//      Buffer32 -  The value to be written to location specified by Address
//
// Output:  None
//
//============================================================================
//<AMI_PHDR_END>

static VOID LocalIoWrite32 (
    IN CONST EFI_PEI_SERVICES **PeiServices,
    IN CONST EFI_PEI_CPU_IO_PPI *This,
    IN UINT64 Address,
    IN UINT32 Buffer32
)
{
    IoWrite32 ((UINT16) Address, Buffer32);
}


//<AMI_PHDR_START>
//============================================================================
// Procedure:   LocaIoWrite64
//
// Description: This function is called to write a qword to the I/O space
//      This function is not available in a 32bit system so we just do nothing
//      if it is called. We cannot remove this function because it is part of
//      the specification
//
// Input:
//      **PeiServices - pointer to the Pei Services function and data structure
//      *This - Pointer to the instance of the CPU I/O PPI structure
//      Address - A 64 bit address that points to the location to be written to
//      Buffer64 -  The value to be written to location specified by Address
//
// Output:  None
//
//============================================================================
//<AMI_PHDR_END>

static VOID LocalIoWrite64 (
    IN CONST EFI_PEI_SERVICES **PeiServices,
    IN CONST EFI_PEI_CPU_IO_PPI *This,
    IN UINT64 Address,
    IN UINT64 Buffer64
)
{
    IoWrite64 ((UINT16) Address, Buffer64);
}

//<AMI_PHDR_START>
//============================================================================
// Procedure:   MemRead8
//
// Description: This function is called to read a byte from the Memory space
//
// Input:
//      **PeiServices - pointer to the Pei Services function and data structure
//      *This - Pointer to the instance of the CPU I/O PPI structure
//      Address - A 64 bit address that points to the location to be read from
//
// Output:  UINT8 - This is the value read from the Memory space specified by
//                      the input variable Address
//
// Referrals:
//
//============================================================================
//<AMI_PHDR_END>

static UINT8 MemRead8 (
    IN CONST EFI_PEI_SERVICES **PeiServices,
    IN CONST struct _EFI_PEI_CPU_IO_PPI *This,
    IN UINT64 Address
)
{
	return  *(volatile UINT8*) Address;
}

//<AMI_PHDR_START>
//============================================================================
// Procedure:   MemRead16
//
// Description: This function is called to read a word from the Memory space
//
// Input:
//      **PeiServices - pointer to the Pei Services function and data structure
//      *This - Pointer to the instance of the CPU I/O PPI structure
//      Address - A 64 bit address that points to the location to be read from
//
// Output:  UINT16 - This is the value read from the Memory space specified
//                      by the input variable Address
//
//============================================================================
//<AMI_PHDR_END>

static UINT16 MemRead16 (
    IN CONST EFI_PEI_SERVICES **PeiServices,
    IN CONST struct _EFI_PEI_CPU_IO_PPI *This,
    IN UINT64 Address
)
{
	return  *(volatile UINT16*) Address;
}

//<AMI_PHDR_START>
//============================================================================
// Procedure:   MemRead32
//
// Description: This function is called to read a dword from the Memory space
//
// Input:
//      **PeiServices - pointer to the Pei Services function and data structure
//      *This - Pointer to the instance of the CPU I/O PPI structure
//      Address - A 64 bit address that points to the location to be read from
//
// Output:  UINT32 - This is the value read from the Memory space specified by
//                      the input variable Address
//
//============================================================================
//<AMI_PHDR_END>

static UINT32 MemRead32 (
    IN CONST EFI_PEI_SERVICES **PeiServices,
    IN CONST struct _EFI_PEI_CPU_IO_PPI *This,
    IN UINT64 Address
)
{
	return  *(volatile UINT32*) Address;
}

//<AMI_PHDR_START>
//============================================================================
// Procedure:   MemRead64
//
// Description: This function is called to read a qword from the Memory space
//      This function is not available in a 32bit system so we just return 0 if
//      it is called. We cannot remove this function because it is part of the
//      specification
//
// Input:
//      **PeiServices - pointer to the Pei Services function and data structure
//      *This - Pointer to the instance of the CPU I/O PPI structure
//      Address - A 64 bit address that points to the location to be read from
//
// Output:  UINT64 - This is the value read from the Memory space specified by
//                      the input variable Address
//
//============================================================================
//<AMI_PHDR_END>

static UINT64 MemRead64 (
    IN CONST EFI_PEI_SERVICES **PeiServices,
    IN CONST struct _EFI_PEI_CPU_IO_PPI *This,
    IN UINT64 Address
)
{
	return  *(volatile UINT64*) Address;
}

//<AMI_PHDR_START>
//============================================================================
// Procedure:   MemWrite8
//
// Description: This function is called to write a byte to the Memory space
//
// Input:
//      **PeiServices - pointer to the Pei Services function and data structure
//      *This - Pointer to the instance of the CPU I/O PPI structure
//      Address - A 64 bit address that points to the location to be written to
//      Buffer8 -   The value to be written to location specified by Address
//
// Output:  None
//
//============================================================================
//<AMI_PHDR_END>

static VOID MemWrite8 (
    IN CONST EFI_PEI_SERVICES **PeiServices,
    IN CONST struct _EFI_PEI_CPU_IO_PPI *This,
    IN UINT64 Address,
    IN UINT8    Buffer8
)
{
	*(volatile UINT8*) Address = Buffer8;
}

//<AMI_PHDR_START>
//============================================================================
// Procedure:   MemWrite16
//
// Description: This function is called to write a word to the Memory space
//
// Input:
//      **PeiServices - pointer to the Pei Services function and data structure
//      *This - Pointer to the instance of the CPU I/O PPI structure
//      Address - A 64 bit address that points to the location to be written to
//      Buffer16 -  The value to be written to location specified by Address
//
// Output:  None
//
//============================================================================
//<AMI_PHDR_END>

static VOID MemWrite16 (
    IN CONST EFI_PEI_SERVICES **PeiServices,
    IN CONST struct _EFI_PEI_CPU_IO_PPI *This,
    IN UINT64 Address,
    IN UINT16 Buffer16
)
{
	*(volatile UINT16*) Address = Buffer16;
}

//<AMI_PHDR_START>
//============================================================================
// Procedure:   MemWrite32
//
// Description: This function is called to write a dword to the Memory space
//
// Input:
//      **PeiServices - pointer to the Pei Services function and data structure
//      *This - Pointer to the instance of the CPU I/O PPI structure
//      Address - A 64 bit address that points to the location to be written to
//      Buffer32 -  The value to be written to location specified by Address
//
// Output:  None
//
//============================================================================
//<AMI_PHDR_END>

static VOID MemWrite32 (
    IN CONST EFI_PEI_SERVICES **PeiServices,
    IN CONST struct _EFI_PEI_CPU_IO_PPI *This,
    IN UINT64 Address,
    IN UINT32 Buffer32
)
{
	*(volatile UINT32*) Address = Buffer32;
}

//<AMI_PHDR_START>
//============================================================================
// Procedure:   MemWrite64
//
// Description: This function is called to write a qword to the Memory space
//      This function is not available in a 32bit system so we just do nothing
//      if it is called. We cannot remove this function because it is part of
//      the specification
//
// Input:
//      **PeiServices - pointer to the Pei Services function and data structure
//      *This - Pointer to the instance of the CPU I/O PPI structure
//      Address - A 64 bit address that points to the location to be written to
//      Buffer64 -  The value to be written to location specified by Address
//
// Output:  None
//
//============================================================================
//<AMI_PHDR_END>

static VOID MemWrite64 (
    IN CONST EFI_PEI_SERVICES **PeiServices,
    IN CONST struct _EFI_PEI_CPU_IO_PPI *This,
    IN UINT64 Address,
    IN UINT64 Buffer
)
{
	*(volatile UINT64*) Address = Buffer;
}

//<AMI_PHDR_START>
//============================================================================
// Procedure:   LocalMemWrite
//
// Description: This function is called to do multiple writes to the memory
//      space. It also is capable of doing a memory space fill of a single value
//      or a serial write from a buffer depending on the Width type being passed
//      in.
//
// Input:
//      **PeiServices - pointer to the Pei Services function and data structure
//      *This - Pointer to the instance of the CPU I/O PPI structure
//      Width - Size of the I/O space that is to be written
//      Address - A 64 bit address that points to the location to be read from
//      Count - Number of times to write
//      *Buffer - Data to be written to the I/O space
//
// Output:  always returns EFI_SUCCESS
//
//============================================================================
//<AMI_PHDR_END>

static EFI_STATUS LocalMemWrite (
    IN      CONST EFI_PEI_SERVICES            **PeiServices,
    IN      CONST struct _EFI_PEI_CPU_IO_PPI  *This,
    IN      EFI_PEI_CPU_IO_PPI_WIDTH    Width,
    IN      UINT64                      Address,
    IN      UINTN                       Count,
    IN OUT  VOID                        *Buffer
)
{
    UINTN   Idx;
    UINTN   OutputInc, InputInc; // Input and Output counters
    
    CalcAddrChanges(
        Width, 
        &InputInc, 
        &OutputInc
    );
    
    for ( Idx = 0; Idx < Count; Idx++, Address += OutputInc, Buffer = (UINT8*)Buffer + InputInc ) {

        switch (Width) {
            case EfiPeiCpuIoWidthUint8:
            case EfiPeiCpuIoWidthFifoUint8:
            case EfiPeiCpuIoWidthFillUint8:
                    MemWrite8(
                        PeiServices, 
                        This, 
                        Address, 
                        *(UINT8*)Buffer
                    );
                break;
                
            case EfiPeiCpuIoWidthUint16:
            case EfiPeiCpuIoWidthFifoUint16:
            case EfiPeiCpuIoWidthFillUint16:
                    MemWrite16(
                        PeiServices, 
                        This, 
                        Address, 
                        *(UINT16*)Buffer
                    );
                break;
                
            case EfiPeiCpuIoWidthUint32:
            case EfiPeiCpuIoWidthFifoUint32:
            case EfiPeiCpuIoWidthFillUint32:
                    MemWrite32(
                        PeiServices, 
                        This, 
                        Address, 
                        *(UINT32*)Buffer
                    );
                break;
                
            case EfiPeiCpuIoWidthUint64:
            case EfiPeiCpuIoWidthFifoUint64:
            case EfiPeiCpuIoWidthFillUint64: 
                    MemWrite64(
                        PeiServices, 
                        This, 
                        Address, 
                        *(UINT64*)Buffer
                    );
                break;
        }
    }
    
    return EFI_SUCCESS;
}

//<AMI_PHDR_START>
//============================================================================
// Procedure:   LocalMemRead
//
// Description: This function is called to do multiple reads from the Memory
//      space. It also is capable of doing an read of an I/O space area to a
//      single byte or a serial read into a buffer depending on the Width type
//      being passed in.
//
// Input:
//      **PeiServices - pointer to the Pei Services function and data structure
//      *This - Pointer to the instance of the CPU I/O PPI structure
//      Width - Size of the Memory space that is to be read each time
//      Address - A 64 bit address that points to the location to be read from
//      Count - Number of times to read
//
// Output:  always returns EFI_SUCCESS
//      *Buffer - Data to be read from the Memory space
//
//============================================================================
//<AMI_PHDR_END>

static EFI_STATUS LocalMemRead (
    IN      CONST EFI_PEI_SERVICES            **PeiServices,
    IN      CONST struct _EFI_PEI_CPU_IO_PPI  *This,
    IN      EFI_PEI_CPU_IO_PPI_WIDTH    Width,
    IN      UINT64                      Address,
    IN      UINTN                       Count,
    IN OUT  VOID                        *Buffer
)
{
    UINTN   Idx;
    UINTN   OutputInc, InputInc; // Input and Output counters
    
    CalcAddrChanges(
        Width, 
        &InputInc, 
        &OutputInc
    );
    
    for ( Idx = 0; Idx < Count; Idx++, Address += OutputInc, Buffer = (UINT8*)Buffer + InputInc ) {
    
        switch (Width) {
            case EfiPeiCpuIoWidthUint8:
            case EfiPeiCpuIoWidthFifoUint8:
            case EfiPeiCpuIoWidthFillUint8: 
                    *(UINT8*)Buffer = MemRead8(
                        PeiServices, 
                        This, 
                        Address
                    );
                break;
                
            case EfiPeiCpuIoWidthUint16:
            case EfiPeiCpuIoWidthFifoUint16:
            case EfiPeiCpuIoWidthFillUint16: 
                    *(UINT16*)Buffer = MemRead16(
                        PeiServices, 
                        This, 
                        Address
                    );
                break;
                
            case EfiPeiCpuIoWidthUint32:
            case EfiPeiCpuIoWidthFifoUint32:
            case EfiPeiCpuIoWidthFillUint32: 
                    *(UINT32*)Buffer = MemRead32(
                        PeiServices, 
                        This, 
                        Address
                    );
                break;
                
            case EfiPeiCpuIoWidthUint64:
            case EfiPeiCpuIoWidthFifoUint64:
            case EfiPeiCpuIoWidthFillUint64: 
                    *(UINT64*)Buffer = MemRead64(
                        PeiServices, 
                        This, 
                        Address
                    );
                break;
        }
    }
    
    return EFI_SUCCESS;
}

//<AMI_PHDR_START>
//============================================================================
// Procedure:   LocalIoRead
//
// Description: This function is called to do multiple reads from the I/O space
//      It also is capable of doing an read of an I/O space area to a single byte
//      or a serial read into a buffer depending on the Width type being passed in.
//
// Input:
//      **PeiServices - pointer to the Pei Services function and data structure
//      *This - Pointer to the instance of the CPU I/O PPI structure
//      Width - Size of the I/O space that is to be read
//      Address - A 64 bit address that points to the location to be read from
//      Count - Number of times to read
//
// Output:  always returns EFI_SUCCESS
//      *Buffer - Data to be read from the I/O space
//
//============================================================================
//<AMI_PHDR_END>

static EFI_STATUS LocalIoRead (
    IN CONST EFI_PEI_SERVICES **PeiServices,
    IN CONST EFI_PEI_CPU_IO_PPI *This,
    IN EFI_PEI_CPU_IO_PPI_WIDTH Width,
    IN UINT64 Address,
    IN UINTN Count,
    IN OUT VOID *Buffer )
{
    UINTN Idx;
    UINTN OutputInc, InputInc; // Input and Output counters
    
    CalcAddrChanges(
        Width, 
        &InputInc, 
        &OutputInc
    );
    
    for ( Idx = 0; Idx < Count; Idx++, Address += OutputInc, Buffer = (UINT8*)Buffer + InputInc ) {
    
        switch (Width) {
            case EfiPeiCpuIoWidthUint8:
            case EfiPeiCpuIoWidthFifoUint8:
            case EfiPeiCpuIoWidthFillUint8: 
                    *(UINT8*)Buffer = LocalIoRead8(
                        PeiServices, 
                        This, 
                        Address
                    );
                break;
                
            case EfiPeiCpuIoWidthUint16:
            case EfiPeiCpuIoWidthFifoUint16:
            case EfiPeiCpuIoWidthFillUint16:
                    *(UINT16*)Buffer = LocalIoRead16(
                        PeiServices, 
                        This, 
                        Address
                    );
                break;
                
            case EfiPeiCpuIoWidthUint32:
            case EfiPeiCpuIoWidthFifoUint32:
            case EfiPeiCpuIoWidthFillUint32:
                    *(UINT32*)Buffer = LocalIoRead32(
                        PeiServices, 
                        This, 
                        Address
                    );
                break;
                
            case EfiPeiCpuIoWidthUint64:
            case EfiPeiCpuIoWidthFifoUint64:
            case EfiPeiCpuIoWidthFillUint64:
                    *(UINT64*)Buffer = LocalIoRead64(
                        PeiServices, 
                        This, 
                        Address
                    );
                break;
        }
    }
    
    return EFI_SUCCESS;
}

//<AMI_PHDR_START>
//============================================================================
// Procedure:   LocalIoWrite
//
// Description: This function is called to do multiple writes to the I/O space
//      It also is capable of doing an I/O space fill of a single value or a
//      serial write from a buffer depending on the Width type being passed in.
//
// Input:
//      **PeiServices - pointer to the Pei Services function and data structure
//      *This - Pointer to the instance of the CPU I/O PPI structure
//      Width - Size of the I/O space that is to be written
//      Address - A 64 bit address that points to the location to be read from
//      Count - Number of times to write
//      *Buffer - Data to be written to the I/O space
//
// Output:  always returns EFI_SUCCESS
//
//============================================================================
//<AMI_PHDR_END>

static EFI_STATUS LocalIoWrite (
    IN CONST EFI_PEI_SERVICES **PeiServices,
    IN CONST EFI_PEI_CPU_IO_PPI *This,
    IN EFI_PEI_CPU_IO_PPI_WIDTH Width,
    IN UINT64 Address,
    IN UINTN Count,
    IN OUT VOID *Buffer )
{
    UINTN Idx;
    UINTN OutputInc, InputInc; // Input and Output counters
    
    CalcAddrChanges(
        Width, 
        &InputInc, 
        &OutputInc
    );
    
    for ( Idx = 0; Idx < Count; Idx++, Address += OutputInc, Buffer = (UINT8*)Buffer + InputInc ) {
        switch (Width) {
            case EfiPeiCpuIoWidthUint8:
            case EfiPeiCpuIoWidthFifoUint8:
            case EfiPeiCpuIoWidthFillUint8:
                    LocalIoWrite8(
                        PeiServices, 
                        This, 
                        Address, 
                        *(UINT8*)Buffer
                    );
                break;
                
            case EfiPeiCpuIoWidthUint16:
            case EfiPeiCpuIoWidthFifoUint16:
            case EfiPeiCpuIoWidthFillUint16:
                    LocalIoWrite16(
                        PeiServices, 
                        This, 
                        Address, 
                        *(UINT16*)Buffer
                    );
                break;
                
            case EfiPeiCpuIoWidthUint32:
            case EfiPeiCpuIoWidthFifoUint32:
            case EfiPeiCpuIoWidthFillUint32:
                    LocalIoWrite32(
                        PeiServices, 
                        This, 
                        Address, 
                        *(UINT32*)Buffer
                    );
                break;
                
            case EfiPeiCpuIoWidthUint64:
            case EfiPeiCpuIoWidthFifoUint64:
            case EfiPeiCpuIoWidthFillUint64:
                    LocalIoWrite64(
                        PeiServices, 
                        This, 
                        Address, 
                        *(UINT64*)Buffer
                    );
                break;
        }
    }
    
    return EFI_SUCCESS;
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

