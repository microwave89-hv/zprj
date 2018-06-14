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

//*************************************************************************
// $Header: /Alaska/BIN/Chipset/Intel/SouthBridge/LynxPoint/Intel Pch SB Chipset/SmBus/SmBusPciHooks.c 1     6/06/12 8:00a Victortu $
//
// $Revision: 1 $
//
// $Date: 6/06/12 8:00a $
//*************************************************************************
// Revision History
// ----------------
// $Log: /Alaska/BIN/Chipset/Intel/SouthBridge/LynxPoint/Intel Pch SB Chipset/SmBus/SmBusPciHooks.c $
// 
// 1     6/06/12 8:00a Victortu
// Implement EFI_PEI_SMBUS2_PPI Support.
// 
// 2     1/27/11 9:44p Abelwu
// Supports SMBUS Protocol in early DXE phase. (EIP#40778)
// 
//*************************************************************************
//<AMI_FHDR_START>
//
// Name:        SmbusPciHooks.c
//
// Description: This file contains PCI initialized hooks for SMBus porting.
//
// Notes:       Porting required if SMBus early DXE supported
//
//<AMI_FHDR_END>
//*************************************************************************

//---------------------------------------------------------------------------
// Include(s)
//---------------------------------------------------------------------------

#include <Efi.h>
#include <Token.h>
#include <AmiDxeLib.h>
#include <AmiCspLib.h>
#include <PciBus.h>

//---------------------------------------------------------------------------
// Constant, Macro and Type Definition(s)
//---------------------------------------------------------------------------
// Constant Definition(s)

// Macro Definition(s)

// Type Definition(s)

// Function Prototype(s)

//---------------------------------------------------------------------------
// Variable and External Declaration(s)
//---------------------------------------------------------------------------
// Variable Declaration(s)

// Local variable

// GUID Definition(s)

// Protocol Definition(s)

// External Declaration(s)

// Function Definition(s)

//---------------------------------------------------------------------------

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:   SmBusProtectedPciDevice
//
// Description: This function is called by PCI Bus Driver before configuring
//              or disabling any PCI device. This function should examine the
//              Vendor/Device ID or PCI Bus, Device and Function numbers to
//              make sure it is not a south bridge device or any other device
//              which should no be configured by PCI Bus Driver.
//
// Input:       *PciDevice - Pointer to PCI Device Info structure.
//
// Output:      EFI_STATUS
//                  EFI_SUCCESS     - SKIP this device, do not touch
//                                    PCI Command register.
//                  EFI_UNSUPPORTED - DON'T SKIP this device do complete
//                                    enumeration as usual.
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS SmBusProtectedPciDevice (
    IN PCI_DEV_INFO             *PciDevice )
{
/* 
if ((PciDevice->Address.Addr.Bus == SMBUS_BUS) && \
    (PciDevice->Address.Addr.Device == SMBUS_DEV) && \
    (PciDevice->Address.Addr.Function == SMBUS_FUN)) {

    return EFI_SUCCESS;
}
*/
    return EFI_UNSUPPORTED;
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
