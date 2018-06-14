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
// $Header: /Alaska/SOURCE/Modules/KbcEmulation/ALASKA/KBCEMUL/KbcEmulLib.c 4     2/10/11 1:00a Rameshr $
//
// $Revision: 4 $
//
// $Date: 2/10/11 1:00a $
//
//****************************************************************************
// Revision History
// ----------------
// $Log: /Alaska/SOURCE/Modules/KbcEmulation/ALASKA/KBCEMUL/KbcEmulLib.c $
// 
// 4     2/10/11 1:00a Rameshr
// [TAG]  		EIP53687
// [Category]  	Improvement
// [Description]  	AMI headers update for KbcEmulation Module 
// [Files]  		KbcEmul.mak,KbcEmul.dxs,KbcEmul.c,KbcEmul.h,KbcEmulLib.h,Kbc
// EmulLib.c,Kbc.h,KbcDevEmul.h,Kbccore.c,Legacykbc.c,Legacykbd.c,LegacyMo
// use.c,VirtualKbc.c,VirtualKbd.c,VirtualMouse.c,Ap4x.h,Ap4x.c,KbcUhci.c,
// KbcUhci.h,KbcEmulIrq.c, KbcOhci.c, Kbcohci.h
// 
// 3     6/30/09 11:29a Rameshr
// Coding Standard and File header updated.
// 
// 2     2/05/09 9:40a Rameshr
// Symptom : With Latest CSM Emulation doesn't work.
// Solution: Added Emulation enable code in outside SMM. This is called
// from Uhcd.c when ever USB mode changes to Legacy
// EIP:18730
// 
// 1     12/14/07 10:26a Rameshraju
// Initial Check-in
//****************************************************************************

//<AMI_FHDR_START>
//**********************************************************************
// Name:        KbcEmullib.c
//
// Description: KBC emulation lib file that used in other files
//
//**********************************************************************
//<AMI_FHDR_END>

#include "KbcEmul.h"
#include "KbcEmulLib.h"

UINT16  WritePCIConfig(UINT16, UINT8);

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   ByteReadIO
//
// Description: This routine reads a Byte from the specified IO address
//
// Input:       wIOAddr     I/O address to read
//
// Output:      Value read
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

UINT8
ByteReadIO(UINT16 wIOAddr)
{
    UINT8 value;
    gSmst->SmmIo.Io.Read(&gSmst->SmmIo, SMM_IO_UINT8, (UINT64)wIOAddr, 1, &value);
    return value;
}


//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   ByteWriteIO
//
// Description: This routine writes a byte to the specified IO address
//
// Input:       wIOAddr     I/O address to write
//              bValue      Byte value to write
//
// Output:      None
//
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

void
ByteWriteIO (UINT16 wIOAddr, UINT8 bValue)
{
    gSmst->SmmIo.Io.Write(&gSmst->SmmIo, SMM_IO_UINT8, (UINT64)wIOAddr, 1, &bValue);
}


//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   WordReadIO
//
// Description: This routine reads a Word from the specified IO address
//
// Input:       wIOAddr     I/O address to read
//
// Output:      Value read
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

UINT16
WordReadIO(UINT16 wIOAddr)
{
    UINT16 value;
    gSmst->SmmIo.Io.Read(&gSmst->SmmIo, SMM_IO_UINT16, (UINT64)wIOAddr, 1, &value);
    return  value;
}


//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   WordWriteIO
//
// Description: This routine writes a word to the specified IO address
//
// Input:       wIOAddr     I/O address to write
//              wValue      Word value to write
//
// Output:      None
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

void
WordWriteIO (UINT16 wIOAddr, UINT16 wValue)
{
    gSmst->SmmIo.Io.Write(&gSmst->SmmIo, SMM_IO_UINT16, (UINT64)wIOAddr, 1, &wValue);
}


//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   DwordReadIO
//
// Description: This routine reads a dword from the specified IO address
//
// Input:       wIOAddr     I/O address to read
//
// Output:      Value read
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

UINT32
DwordReadIO(UINT16 wIOAddr)
{
    UINT32  value;
    gSmst->SmmIo.Io.Read(&gSmst->SmmIo, SMM_IO_UINT32, (UINT64)wIOAddr, 1, &value);
    return  value;
}


//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   DwordWriteIO
//
// Description: This routine writes a double word to the specified IO address
//
// Input:       wIOAddr     I/O address to write
//              dValue      Double word value to write
//
// Output:      None
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

void
DwordWriteIO(UINT16 wIOAddr, UINT32 dValue)
{
    gSmst->SmmIo.Io.Write(&gSmst->SmmIo, SMM_IO_UINT32, (UINT64)wIOAddr, 1, &dValue);
}


//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   ReadPCIConfig
//
// Description: This routine reads from the PCI configuration space register
//              the value can be typecasted to 8bits - 32bits
//
// Input:       BusDevFunc - Bus, device & function number of the PCI device
//              Register   - Register offset to read
//
// Output:      Value read
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

UINT32
ReadPCIConfig(UINT16 BusDevFunc, UINT8 Register)
{
    UINT32 data;
    DwordWriteIO(0xCF8, (UINT32)(0x80000000 | (BusDevFunc<<8) | (Register & 0xFC)));
    data = DwordReadIO(0xCFC);
    return (data >> ((Register & 3) << 3)); // Adjust uneven register

}


//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   ByteWritePCIConfig
//
// Description: This routine writes a byte value to the PCI configuration
//              register space
//
// Input:       BusDevFunc - Bus, device & function number of the PCI device
//              Register   - Register offset to read
//              Value      - Value to write
//
// Output:      None
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

void
ByteWritePCIConfig(UINT16 BusDevFunc, UINT8 Register, UINT8 Value)
{
    UINT16 wIOAddr;
    wIOAddr = WritePCIConfig(BusDevFunc, Register);
    ByteWriteIO (wIOAddr, Value);
}


//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   WordWritePCIConfig
//
// Description: This routine writes a byte value to the PCI configuration
//              register space
//
// Input:       BusDevFunc - Bus, device & function number of the PCI device
//              Register   - Register offset to read
//              Value      - Value to write
//
// Output:      None
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

void
WordWritePCIConfig(UINT16 BusDevFunc, UINT8 Register, UINT16 Value)
{
    UINT16 wIOAddr;
    wIOAddr = WritePCIConfig(BusDevFunc, Register);
    WordWriteIO (wIOAddr, Value);
}


//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   DwordWritePCIConfig
//
// Description: This routine writes a Dword value to the PCI configuration
//              register space
//
// Input:       BusDevFunc - Bus, device & function number of the PCI device
//              Register   - Register offset to read
//              Value      - Value to write
//
// Output:      None
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

void
DwordWritePCIConfig(UINT16 BusDevFunc, UINT8 Register, UINT32 Value)
{
    UINT16 wIOAddr;
    wIOAddr = WritePCIConfig(BusDevFunc, Register);
    DwordWriteIO (wIOAddr, Value);
}


//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   WritePCIConfig
//
// Description: This function opens PCI configuration for a given register
//
// Input:       wBDF  - Bus, device and function number
//              bReg  - Register number to read
//
// Output:      IO register to write the value
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

UINT16
WritePCIConfig(UINT16 wBDF, UINT8 bReg)
{
    DwordWriteIO(0xCF8, (UINT32)(0x80000000 | (wBDF<<8) | (bReg & 0xFC)));
    return (UINT16)(0xCFC+(bReg & 3));
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   NonSmmByteReadIO
//
// Description: This routine reads a Byte from the specified IO address
//
// Input:       wIOAddr     I/O address to read
//
// Output:      Value read
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

UINT8
NonSmmByteReadIO(UINT16 wIOAddr)
{
    UINT8 value;
    CpuIo->Io.Read(CpuIo, EfiCpuIoWidthUint8, wIOAddr, 1, &value);
    return value;
}


//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   NonSmmByteWriteIO
//
// Description: This routine writes a byte to the specified IO address
//
// Input:       wIOAddr     I/O address to write
//              bValue      Byte value to write
//
// Output:      None
//
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

void
NonSmmByteWriteIO (UINT16 wIOAddr, UINT8 bValue)
{
    CpuIo->Io.Write(CpuIo, EfiCpuIoWidthUint8, wIOAddr, 1, &bValue);
}


//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   NonSmmWordReadIO
//
// Description: This routine reads a Word from the specified IO address
//
// Input:       wIOAddr     I/O address to read
//
// Output:      Value read
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

UINT16
NonSmmWordReadIO(UINT16 wIOAddr)
{
    UINT16 value;
    CpuIo->Io.Read(CpuIo, EfiCpuIoWidthUint16, wIOAddr, 1, &value);
    return  value;
}


//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   NonSmmWordWriteIO
//
// Description: This routine writes a word to the specified IO address
//
// Input:       wIOAddr     I/O address to write
//              wValue      Word value to write
//
// Output:      None
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

void
NonSmmWordWriteIO (UINT16 wIOAddr, UINT16 wValue)
{
    CpuIo->Io.Write(CpuIo, EfiCpuIoWidthUint16, wIOAddr, 1, &wValue);
}


//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   NonSmmDwordReadIO
//
// Description: This routine reads a dword from the specified IO address
//
// Input:       wIOAddr     I/O address to read
//
// Output:      Value read
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

UINT32
NonSmmDwordReadIO(UINT16 wIOAddr)
{
    UINT32  value;
    CpuIo->Io.Read(CpuIo, EfiCpuIoWidthUint32, wIOAddr, 1, &value);
    return  value;
}


//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   NonSmmDwordWriteIO
//
// Description: This routine writes a double word to the specified IO address
//
// Input:       wIOAddr     I/O address to write
//              dValue      Double word value to write
//
// Output:      None
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

void
NonSmmDwordWriteIO(UINT16 wIOAddr, UINT32 dValue)
{
    CpuIo->Io.Write(CpuIo, EfiCpuIoWidthUint32, wIOAddr, 1, &dValue);
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   NonSmmWritePCIConfig
//
// Description: This function opens PCI configuration for a given register
//
// Input:       wBDF  - Bus, device and function number
//              bReg  - Register number to read
//
// Output:      IO register to write the value
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

UINT16
NonSmmWritePCIConfig(UINT16 wBDF, UINT8 bReg)
{
    NonSmmDwordWriteIO(0xCF8, (UINT32)(0x80000000 | (wBDF<<8) | (bReg & 0xFC)));
    return (UINT16)(0xCFC+(bReg & 3));
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   NonSmmReadPCIConfig
//
// Description: This routine reads from the PCI configuration space register
//              the value can be typecasted to 8bits - 32bits
//
// Input:       BusDevFunc - Bus, device & function number of the PCI device
//              Register   - Register offset to read
//
// Output:      Value read
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

UINT32
NonSmmReadPCIConfig(UINT16 BusDevFunc, UINT8 Register)
{
    UINT32 data;
    NonSmmDwordWriteIO(0xCF8, (UINT32)(0x80000000 | (BusDevFunc<<8) | (Register & 0xFC)));
    data = NonSmmDwordReadIO(0xCFC);
    return (data >> ((Register & 3) << 3)); // Adjust uneven register

}


//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   NonSmmByteWritePCIConfig
//
// Description: This routine writes a byte value to the PCI configuration
//              register space
//
// Input:       BusDevFunc - Bus, device & function number of the PCI device
//              Register   - Register offset to read
//              Value      - Value to write
//
// Output:      None
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

void
NonSmmByteWritePCIConfig(UINT16 BusDevFunc, UINT8 Register, UINT8 Value)
{
    UINT16 wIOAddr;
    wIOAddr = NonSmmWritePCIConfig(BusDevFunc, Register);
    NonSmmByteWriteIO (wIOAddr, Value);
}


//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   NonSmmWordWritePCIConfig
//
// Description: This routine writes a word value to the PCI configuration
//              register space
//
// Input:       BusDevFunc - Bus, device & function number of the PCI device
//              Register   - Register offset to write
//              Value      - Value to write
//
// Output:      None
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

void
NonSmmWordWritePCIConfig(UINT16 BusDevFunc, UINT8 Register, UINT16 Value)
{
    UINT16 wIOAddr;
    wIOAddr = NonSmmWritePCIConfig(BusDevFunc, Register);
    NonSmmWordWriteIO (wIOAddr, Value);
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   NonSmmDwordWritePCIConfig
//
// Description: This routine writes a Dword value to the PCI configuration
//              register space
//
// Input:       BusDevFunc - Bus, device & function number of the PCI device
//              Register   - Register offset to read
//              Value      - Value to write
//
// Output:      None
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

void
NonSmmDwordWritePCIConfig(UINT16 BusDevFunc, UINT8 Register, UINT32 Value)
{
    UINT16 wIOAddr;
    wIOAddr = NonSmmWritePCIConfig(BusDevFunc, Register);
    NonSmmDwordWriteIO (wIOAddr, Value);
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