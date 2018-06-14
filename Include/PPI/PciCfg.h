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
// $Header: /Alaska/BIN/Core/Include/PPI/PciCfg.h 7     6/16/11 3:18p Felixp $
//
// $Revision: 7 $
//
// $Date: 6/16/11 3:18p $
//*****************************************************************************
// Revision	History
// ----------------
// $Log: /Alaska/BIN/Core/Include/PPI/PciCfg.h $
// 
// 7     6/16/11 3:18p Felixp
// Surround backward compatibility definitions with #if
// BACKWARD_COMPATIBLE_MODE
// 
// 6     5/27/11 5:52p Felixp
// Headers are updated to improve separation of the Framework and PI
// interfaces.
// The definitions that will be removed in the future versions are marked
// with the comments.
// 
// 5     2/05/11 2:09p Artems
// Added PI 1.0 compatibility definitions
// 
// 4     3/13/06 1:16a Felixp
// 
// 3     6/06/05 1:24p Felixp
// 
// 2     6/03/05 3:44p Felixp
// Updated to support changes introduced in PEI CIS 0.91
// 
// 1     1/28/05 12:44p Felixp
// 
// 1     12/23/04 9:41a Felixp
// 
// 5     12/18/03 3:08p Robert
//
// 4		 12/18/03	2:46p	Robert
//
// 3		 12/16/03	4:03p	Robert
//
// 2		 12/15/03	4:21p	Robert
//
// 1		 12/11/03	5:36p	Robert
// Initial Check in	of the PCI Cfg PPI
//
//*****************************************************************************
//<AMI_FHDR_START>
//
// Name:	PciCfg.h
//
// Description:	This file	is an	include	file used	to define	the	PPI	for	the
//		PCI	CFG	PPI.	For	questions	about	the	specification	refer	to the PEI CIS
//
//<AMI_FHDR_END>
//*****************************************************************************
#ifndef	_PCI_CFG_PPI_H_
#define	_PCI_CFG_PPI_H_
#ifdef __cplusplus
extern "C" {
#endif
#include <PEI.h>

#if BACKWARD_COMPATIBLE_MODE
#include <Ppi/PciCfg2.h>
#if PI_SPECIFICATION_VERSION >= 0x00010000
//Compatibility definition
#define EFI_PEI_PCI_CFG_PPI_INSTALLED_GUID EFI_PEI_PCI_CFG2_PPI_GUID
#endif
#endif

//Remove the #ifndef-clause when backward compatibility definitions above are removed.
#ifndef EFI_PEI_PCI_CFG_PPI_INSTALLED_GUID
#define EFI_PEI_PCI_CFG_PPI_INSTALLED_GUID \
	{ 0xe1f2eba0, 0xf7b9, 0x4a26, 0x86, 0x20, 0x13, 0x12, 0x21, 0x64, 0x2a, 0x90 }
#endif

GUID_VARIABLE_DECLARATION(gPeiPciCfgPpiInServiceTableGuid,EFI_PEI_PCI_CFG_PPI_INSTALLED_GUID);

/******	DO NOT WRITE BELOW THIS	LINE *******/
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
