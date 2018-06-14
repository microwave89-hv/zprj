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

//**********************************************************************
// $Header: /Alaska/SOURCE/Modules/SMM/SmmPciRootBridgeIo.h 3     4/15/11 4:32p Markw $
//
// $Revision: 3 $
//
// $Date: 4/15/11 4:32p $
//**********************************************************************
// Revision History
// ----------------
// $Log: /Alaska/SOURCE/Modules/SMM/SmmPciRootBridgeIo.h $
// 
// 3     4/15/11 4:32p Markw
// Header Update.
// 
//**********************************************************************

//<AMI_FHDR_START>
//----------------------------------------------------------------------------
//
// Name: SmmPciRootBridgeIo.h
//
// Description:
//  Smm Pci Root Bridge Io Protocol
//
//----------------------------------------------------------------------------
//<AMI_FHDR_END>

#ifndef _SMM_PCI_ROOT_BRIDGE_IO_H_
#define _SMM_PCI_ROOT_BRIDGE_IO_H_
#if PI_SPECIFICATION_VERSION >= 0x0001000A

#ifdef __cplusplus
extern "C" {
#endif

#include <Protocol/PciRootBridgeIo.h>

#define EFI_SMM_PCI_ROOT_BRIDGE_IO_PROTOCOL_GUID \
    {0x8bc1714d, 0xffcb, 0x41c3, 0x89, 0xdc, 0x6c, 0x74, 0xd0, 0x6d, 0x98, 0xea}

typedef EFI_PCI_ROOT_BRIDGE_IO_PROTOCOL  EFI_SMM_PCI_ROOT_BRIDGE_IO_PROTOCOL;

GUID_VARIABLE_DECLARATION(gEfiSmmPciRootBridgeIoProtocolGuid, EFI_SMM_PCI_ROOT_BRIDGE_IO_PROTOCOL_GUID);

/****** DO NOT WRITE BELOW THIS LINE *******/
#ifdef __cplusplus
}
#endif
#endif
#endif

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
