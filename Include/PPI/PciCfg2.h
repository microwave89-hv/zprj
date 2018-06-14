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
// $Header: /Alaska/BIN/Core/Include/PPI/PciCfg2.h 1     5/27/11 5:50p Felixp $
//
// $Revision: 1 $
//
// $Date: 5/27/11 5:50p $
//**********************************************************************
// Revision History
// ----------------
// $Log: /Alaska/BIN/Core/Include/PPI/PciCfg2.h $
// 
// 1     5/27/11 5:50p Felixp
// 
// 6     1/13/10 2:13p Felixp
// 
//**********************************************************************
//<AMI_FHDR_START>
//
// Name:  PciCfg2.h
//
// Description:	
//
//<AMI_FHDR_END>
//**********************************************************************
#ifndef __PCI_CFG2_PPI__H__
#define __PCI_CFG2_PPI__H__
#ifdef __cplusplus
extern "C" {
#endif

#include <PEI.h>

#if PI_SPECIFICATION_VERSION<0x00010000
//Compatibility definition
//#define EFI_PEI_PCI_CFG2_PPI_GUID EFI_PEI_PCI_CFG_PPI_INSTALLED_GUID
#define EFI_PEI_PCI_CFG2_PPI_GUID \
	{ 0xe1f2eba0, 0xf7b9, 0x4a26, 0x86, 0x20, 0x13, 0x12, 0x21, 0x64, 0x2a, 0x90 }
#else
#define EFI_PEI_PCI_CFG2_PPI_GUID \
    { 0x57a449a, 0x1fdc, 0x4c06, 0xbf, 0xc9, 0xf5, 0x3f, 0x6a, 0x99, 0xbb, 0x92 }
#endif

GUID_VARIABLE_DECLARATION(gEfiPciCfg2PpiGuid,EFI_PEI_PCI_CFG2_PPI_GUID);

/****** DO NOT WRITE BELOW THIS LINE *******/
#ifdef __cplusplus
}
#endif
#endif
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
