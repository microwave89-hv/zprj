//**********************************************************************
//**********************************************************************
//**                                                                  **
//**        (C)Copyright 1985-2011, American Megatrends, Inc.         **
//**                                                                  **
//**                       All Rights Reserved.                       **
//**                                                                  **
//**      5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093        **
//**                                                                  **
//**                       Phone: (770)-246-8600                      **
//**                                                                  **
//**********************************************************************
//**********************************************************************
//**********************************************************************
// $Header: /Alaska/SOURCE/Core/Runtime/CpuIoDxe.c 5     5/17/12 4:14p Artems $
//
// $Revision: 5 $
//
// $Date: 5/17/12 4:14p $
//**********************************************************************
// Revision History
// ----------------
// $Log: /Alaska/SOURCE/Core/Runtime/CpuIoDxe.c $
// 
// 5     5/17/12 4:14p Artems
// [TAG]  		EIP N/A
// [Category]  	Improvement
// [Description]  	Added support to address MMIO space above 4GB in x64
// mode
// [Files]  		CpuIoDxe.c
// 
// 4     4/15/11 12:47p Artems
// EIP 56523: Added support of PI specification v 1.2
// 
// 3     6/24/09 4:24p Robert
// updated Comments, copyrights, and some coding standard issues
// 
// 2     10/21/08 3:41p Felixp
// Support for usage of the protocol at runtime is added.
// 
//**********************************************************************

//<AMI_FHDR_START>
//---------------------------------------------------------------------------
//
// Name:        CpuIo.c
//
// Description: 
//  This file contains Protocol functions and definitions for the 
//  EFI_CPU_IO_PROTOCOL.  This protocol contains functions for memory and I/O
//  access 
//
//---------------------------------------------------------------------------
//<AMI_FHDR_END>

//==========================================================================
//  Includes
#include <Protocol\CpuIo.h>
#include <AmiDxeLib.h>


//==========================================================================
//  GUID definitions

//==========================================================================
//  Function Definitions

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   CpuIoMemRead
//
// Description: 
//  This function reads from the Memory space at the address defined by Address
//  with the size defined by the lowest 2 bits in the Width parameter.  It
//  repeats this Count number of times while incrementing the Buffer, 
//  the Address, or both depending on the type of operation defined by the
//  upper 6 bits in the width parameter.  Refer to the notes section for
//  further definition of the Width parameter
//
// Input:   
//  IN EFI_CPU_IO_PROTOCOL *This - Pointer to the EFI_CPU_IO_PROTOCOL
//  IN EFI_CPU_IO_PROTOCOL_WIDTH Width - Contains Type and Width of the Memory operation
//  IN UINT64 Address - Memory address to read from 
//  IN UINTN Count - number of times to perform the read operation
//  IN OUT VOID *Buffer - Data buffer to store the data read
//
// Output:      
//  EFI_SUCCESS 
//
// Notes:
//  The Width Variable contains a width and a type component
//  - The width is defined by the lowest 2 bits
//  - The Type is defined by the other bits as follows:
//  - - Type = 0 - EfiIoWidthUintxx - Increment Buffer and address
//  - - Type = 1 - EfiIoWidthFifoUintxx - Increment only Buffer
//  - - Type > 1 - EfiIoWidthFillUintxx - Increment only Address
//  - The increment happens after each Operation
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS CpuIoMemRead(
    IN EFI_CPU_IO_PROTOCOL          *This,
    IN EFI_CPU_IO_PROTOCOL_WIDTH    Width,
    IN UINT64                       Address,
    IN UINTN                        Count,
    IN OUT VOID                     *Buffer
)
{
    UINTN   IncrementType       = Width & ~3;
    UINT8   IncrementValue      = 1 << (Width & 3); //1st 2 bits currently define width. Other bits define type.
    UINT8   IncrementBuffer     = 0;
    UINT8   IncrementAddress    = 0;
    UINT64  Limit;

    if (Buffer==NULL) return EFI_INVALID_PARAMETER;
    if (IncrementType > 16 || IncrementValue > 8) return EFI_INVALID_PARAMETER;

    Limit = (sizeof(UINTN) < 8) ? 0xffffffff : 0xffffffffffffffff;
    if ((Count * IncrementValue) > (Limit - Address))
            return EFI_INVALID_PARAMETER;                       //Memory must be within range of the bridge.

    switch (IncrementType)
    {
    case 0: //EfiIoWidthUintxx
        IncrementAddress = IncrementBuffer = IncrementValue;
        break;
    case 4: //EfiIoWidthFifoUintxx
        IncrementBuffer = IncrementValue;
        break;
    default: //EfiIoWidthFillUintxx
        IncrementAddress = IncrementValue;
    }

    while(Count--)
    {
        switch(IncrementValue)
        {
        case 1:     // byte
            *(UINT8*) Buffer = *(UINT8*)Address;
            break;
        case 2:     // word
            *(UINT16*) Buffer = *(UINT16*)Address;
            break;
        case 4:     // dword
            *(UINT32*) Buffer = *(UINT32*)Address;
            break;      
        case 8:     // qword
            *(UINT64*) Buffer = *(UINT64*)Address;
            break;
        default: return EFI_INVALID_PARAMETER;
        }
        (UINT8*) Buffer += IncrementBuffer;
        Address += IncrementAddress;
    }

    return EFI_SUCCESS;
}


//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   CpuIoMemWrite
//
// Description: 
//  This function writes to the Memory space at the address defined by Address
//  with the size defined by the lowest 2 bits in the Width parameter.  It
//  repeats this Count number of times while incrementing the Buffer, 
//  the Address, or both depending on the type of operation defined by the
//  upper 6 bits in the width parameter.  Refer to the notes section for
//  further definition of the Width parameter
//
// Input:   
//  IN EFI_CPU_IO_PROTOCOL *This - Pointer to the EFI_CPU_IO_PROTOCOL
//  IN EFI_CPU_IO_PROTOCOL_WIDTH Width - Contains Type and Width of the Memory operation
//  IN UINT64 Address - Memory address to Write to
//  IN UINTN Count - number of times to perform the write operation
//  IN OUT VOID *Buffer - Data buffer of the data to write
//
// Output:      
//  EFI_SUCCESS 
//
// Notes:
//  The Width Variable contains a width and a type component
//  - The width is defined by the lowest 2 bits
//  - The Type is defined by the other bits as follows:
//  - - Type = 0 - EfiIoWidthUintxx - Increment Buffer and address
//  - - Type = 1 - EfiIoWidthFifoUintxx - Increment only Buffer
//  - - Type > 1 - EfiIoWidthFillUintxx - Increment only Address
//  - The increment happens after each Operation
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS CpuIoMemWrite(
    IN EFI_CPU_IO_PROTOCOL          *This,
    IN EFI_CPU_IO_PROTOCOL_WIDTH    Width,
    IN UINT64                       Address,
    IN UINTN                        Count,
    IN OUT VOID                     *Buffer
)
{
    // 1st 2 bits currently define width. Other bits define type.
    UINTN   IncrementType       = Width & ~3;
    UINT8   IncrementValue      = 1 << (Width & 3); 
    UINT8   IncrementBuffer     = 0;
    UINT8   IncrementAddress    = 0;
    UINT64  Limit;

    if (Buffer==NULL) return EFI_INVALID_PARAMETER;
    if (IncrementType > 16 || IncrementValue > 8) return EFI_INVALID_PARAMETER;

    // Memory must be within range of the bridge.
    Limit = (sizeof(UINTN) < 8) ? 0xffffffff : 0xffffffffffffffff;
    if ((Count * IncrementValue) > (Limit - Address))
            return EFI_INVALID_PARAMETER;               

    switch (IncrementType)
    {
    case 0: //EfiIoWidthUintxx
        IncrementAddress = IncrementBuffer = IncrementValue;
        break;
    case 4: //EfiIoWidthFifoUintxx
        IncrementBuffer = IncrementValue;
        break;
    default: //EfiIoWidthFillUintxx
        IncrementAddress = IncrementValue;
    }

    while(Count--)
    {
        switch(IncrementValue)
        {
        case 1:     //byte
            *(UINT8*) Address = *(UINT8*)Buffer;
            break;
        case 2:     //word
            *(UINT16*) Address = *(UINT16*)Buffer;
            break;
        case 4:     //dword
            *(UINT32*) Address = *(UINT32*)Buffer;
            break;
        case 8:     // qword
            *(UINT64*) Address = *(UINT64*)Buffer;
            break;
        default: return EFI_INVALID_PARAMETER;
        }
        (UINT8*) Buffer += IncrementBuffer;
        Address += IncrementAddress;
    }

    return EFI_SUCCESS;
}


//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   CpuIoIoRead
//
// Description: 
//  This function reads the IO space at the address defined by Address
//  with the size defined by the lowest 2 bits in the Width parameter.  It
//  repeats this Count number of times while incrementing the Buffer, 
//  the Address, or both depending on the type of operation defined by the
//  upper 6 bits in the width parameter.  Refer to the notes section for
//  further definition of the Width parameter
//
// Input:   
//  IN EFI_CPU_IO_PROTOCOL *This - Pointer to the EFI_CPU_IO_PROTOCOL
//  IN EFI_CPU_IO_PROTOCOL_WIDTH Width - Contains Type and Width of the Io operation
//  IN UINT64 Address - IO address to Read from
//  IN UINTN Count - number of times to perform the read operation
//  IN OUT VOID *Buffer - Data buffer to store the data read
//
// Output:      
//  EFI_SUCCESS 
//
// Notes:
//  The Width Variable contains a width and a type component
//  - The width is defined by the lowest 2 bits
//  - The Type is defined by the other bits as follows:
//  - - Type = 0 - EfiIoWidthUintxx - Increment Buffer and address
//  - - Type = 1 - EfiIoWidthFifoUintxx - Increment only Buffer
//  - - Type > 1 - EfiIoWidthFillUintxx - Increment only Address
//  - The increment happens after each Operation
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS CpuIoIoRead(
    IN EFI_CPU_IO_PROTOCOL          *This,
    IN EFI_CPU_IO_PROTOCOL_WIDTH    Width,
    IN UINT64                       Address,
    IN UINTN                        Count,
    IN OUT VOID                     *Buffer
)
{
    //1st 2 bits of the Width parameter currently define width. Other bits define type.
    UINTN   IncrementType       = Width & ~3;
    UINT8   IncrementValue      = 1 << (Width & 3); 
    UINT8   IncrementBuffer     = 0;
    UINT8   IncrementAddress    = 0;

    if ((UINT32) Width >= EfiCpuIoWidthMaximum) return EFI_INVALID_PARAMETER;

    if (Buffer==NULL) return EFI_INVALID_PARAMETER;
    if (IncrementType > 16 || IncrementValue > 8) return EFI_INVALID_PARAMETER;

    if ((Address + Count * IncrementValue) > 0xffff)
            return EFI_INVALID_PARAMETER;           //Memory must be within range of the bridge.

    switch (IncrementType)
    {
    case 0: //EfiIoWidthUintxx
        IncrementAddress = IncrementBuffer = IncrementValue;
        break;
    case 4: //EfiIoWidthFifoUintxx
        IncrementBuffer = IncrementValue;
        break;
    default: //EfiIoWidthFillUintxx
        IncrementAddress = IncrementValue;
    }

    while(Count--)
    {
        switch(IncrementValue)
        {
        case 1:     // byte
            *(UINT8*) Buffer = IoRead8((UINT16)Address);
            break;
        case 2:     // word
            *(UINT16*) Buffer = IoRead16((UINT16)Address);
            break;
        case 4:     // dword
            *(UINT32*) Buffer = IoRead32((UINT16)Address);
            break;
        case 8:     // qword
            *(UINT32*) Buffer = IoRead32((UINT16)Address);
            *((UINT32*)((UINT32*)Buffer+1)) = IoRead32((UINT16)(Address+4));
            break;
        default: return EFI_INVALID_PARAMETER;
        }
        (UINT8*) Buffer += IncrementBuffer;
        Address += IncrementAddress;
    }

    return EFI_SUCCESS;
}


//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   CpuIoIoWrite
//
// Description: 
//  This function writes to the IO space at the address defined by Address
//  with the size defined by the lowest 2 bits in the Width parameter.  It
//  repeats this Count number of times while incrementing the Buffer, 
//  the Address, or both depending on the type of operation defined by the
//  upper 6 bits in the width parameter.  Refer to the notes section for
//  further definition of the Width parameter
//
// Input:   
//  IN EFI_CPU_IO_PROTOCOL *This - Pointer to the EFI_CPU_IO_PROTOCOL
//  IN EFI_CPU_IO_PROTOCOL_WIDTH Width - Contains Type and Width of the Io operation
//  IN UINT64 Address - IO address to Write to
//  IN UINTN Count - number of times to perform the write operation
//  IN OUT VOID *Buffer - Data buffer of the data to write
//
// Output:      
//  EFI_SUCCESS 
//
// Notes:
//  The Width Variable contains a width and a type component
//  - The width is defined by the lowest 2 bits
//  - The Type is defined by the other bits as follows:
//  - - Type = 0 - EfiIoWidthUintxx - Increment Buffer and address
//  - - Type = 1 - EfiIoWidthFifoUintxx - Increment only Buffer
//  - - Type > 1 - EfiIoWidthFillUintxx - Increment only Address
//  - The increment happens after each Operation
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS CpuIoIoWrite(
    IN EFI_CPU_IO_PROTOCOL          *This,
    IN EFI_CPU_IO_PROTOCOL_WIDTH    Width,
    IN UINT64                       Address,
    IN UINTN                        Count,
    IN OUT VOID                     *Buffer
)
{
    //1st 2 bits of the Width parameter currently define width. Other bits define type.
    UINTN   IncrementType       = Width & ~3;
    UINT8   IncrementValue      = 1 << (Width & 3);
    UINT8   IncrementBuffer     = 0;
    UINT8   IncrementAddress    = 0;

    if ((UINT32) Width >= EfiCpuIoWidthMaximum) return EFI_INVALID_PARAMETER;

    if (Buffer==NULL) return EFI_INVALID_PARAMETER;
    if (IncrementType > 16 || IncrementValue > 4) return EFI_INVALID_PARAMETER;

    if ((Address + Count * IncrementValue) > 0xffff)
            return EFI_INVALID_PARAMETER;                       //Memory must be within range of the bridge.

    switch (IncrementType)
    {
    case 0: //EfiIoWidthUintxx
        IncrementAddress = IncrementBuffer = IncrementValue;
        break;
    case 4: //EfiIoWidthFifoUintxx
        IncrementBuffer = IncrementValue;
        break;
    default: //EfiIoWidthFillUintxx
        IncrementAddress = IncrementValue;
    }

    while(Count--)
    {
        switch(IncrementValue)
        {
        case 1:     //byte
             IoWrite8((UINT16)Address,*(UINT8*) Buffer);
            break;
        case 2:     //word
             IoWrite16((UINT16)Address,*(UINT16*) Buffer);
            break;
        default:    //dword
             IoWrite32((UINT16)Address,*(UINT32*) Buffer);
            break;
        }
        (UINT8*) Buffer += IncrementBuffer;
        Address += IncrementAddress;
    }

    return EFI_SUCCESS;
}


static EFI_CPU_IO_PROTOCOL gEfiCpuIoProtocol = {
    { CpuIoMemRead, CpuIoMemWrite },
    { CpuIoIoRead, CpuIoIoWrite },
};

//==========================================================================
//  Module specific Global Variable
static EFI_RUNTIME_SERVICES *MyRS=NULL;
// End Module specific Global Variable
//==========================================================================


//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   CpuIoVirtAddressChange
//
// Description: 
//  This function is a callback function that changes the Protocol function 
//  pointers from Physical Address Mapping to Virtual Address Mapping
//
// Input:   
//  IN EFI_EVENT Event - Pointer to the event that was triggered
//  IN VOID *Context - Buffer Pointer defined by the code that calls CreateEvent
//
// Output:      
//  None 
//
// Notes:
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID CpuIoVirtAddressChange (IN EFI_EVENT Event, IN VOID *Context)
{
    MyRS->ConvertPointer(0,(VOID**)&gEfiCpuIoProtocol.Mem.Read);
    MyRS->ConvertPointer(0,(VOID**)&gEfiCpuIoProtocol.Mem.Write);
    MyRS->ConvertPointer(0,(VOID**)&gEfiCpuIoProtocol.Io.Read);
    MyRS->ConvertPointer(0,(VOID**)&gEfiCpuIoProtocol.Io.Write);
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   CpuIoDxeInit
//
// Description: 
//  This function is the entry point for the EFI_CPU_IO_PROTOCOL.  
//
// Input:   
//  EFI_HANDLE ImageHandle - The firmware allocated handle for this driver
//  EFI_SYSTEM_TABLE *SystemTable - Pointer to the UEFI SystemTable
//
// Output:      
//  EFI_SUCCESS 
//
// Notes:
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS CpuIoDxeInit(
    IN EFI_HANDLE       ImageHandle,
    IN EFI_SYSTEM_TABLE *SystemTable)
{
    EFI_HANDLE Handle = NULL;
    EFI_STATUS Status;

    // initialize the AMI Library
    InitAmiLib(ImageHandle, SystemTable);

    // install the CpuIo Protocol
    Status = pBS->InstallMultipleProtocolInterfaces(
                    &Handle,
                    &gEfiCpuIoProtocolGuid, &gEfiCpuIoProtocol,
#if PI_SPECIFICATION_VERSION >= 0x10014
                    &gEfiCpuIo2ProtocolGuid, &gEfiCpuIoProtocol,
#endif
                    NULL);
    ASSERT_EFI_ERROR(Status);
    if(EFI_ERROR(Status))
        return Status;

{
    EFI_EVENT Event;
    // defines the local Runtime Services pointer
    MyRS = pRS;

    // creates event for virtual address change fixup
    Status = pBS->CreateEvent(
                        EVT_SIGNAL_VIRTUAL_ADDRESS_CHANGE,
                        TPL_CALLBACK, 
                        &CpuIoVirtAddressChange, 
                        NULL, 
                        &Event);
}

    return Status;
}



//**********************************************************************
//**********************************************************************
//**                                                                  **
//**        (C)Copyright 1985-2011, American Megatrends, Inc.         **
//**                                                                  **
//**                       All Rights Reserved.                       **
//**                                                                  **
//**      5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093        **
//**                                                                  **
//**                       Phone: (770)-246-8600                      **
//**                                                                  **
//**********************************************************************
//**********************************************************************
