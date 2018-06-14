//**********************************************************************
//**********************************************************************
//**                                                                  **
//**        (C)Copyright 1985-2006, American Megatrends, Inc.         **
//**                                                                  **
//**                       All Rights Reserved.                       **
//**                                                                  **
//**             6145-F Northbelt Pkwy, Norcross, GA 30071            **
//**                                                                  **
//**                       Phone: (770)-246-8600                      **
//**                                                                  **
//**********************************************************************
//**********************************************************************

//**********************************************************************
// $Header: /Alaska/SOURCE/Core/EDK/PPI/MemoryDiscovered.h 1     5/19/06 11:28p Felixp $
//
// $Revision: 1 $
//
// $Date: 5/19/06 11:28p $
//**********************************************************************
// Revision History
// ----------------
// $Log: /Alaska/SOURCE/Core/EDK/PPI/MemoryDiscovered.h $
// 
// 1     5/19/06 11:28p Felixp
// 
// 1     3/13/06 1:57a Felixp
// 
//**********************************************************************
//<AMI_FHDR_START>
//
// Name:	MemoryDiscovered.h
//
// Description:	
//
//<AMI_FHDR_END>
//**********************************************************************
#ifndef __PERMANENT_MEMORY_INSTALLED_PPI__H__
#define __PERMANENT_MEMORY_INSTALLED_PPI__H__
#ifdef __cplusplus
extern "C" {
#endif
#include <PEI.h>
#define PEI_PERMANENT_MEMORY_INSTALLED_PPI_GUID EFI_PEI_PERMANENT_MEMORY_INSTALLED_PPI

GUID_VARIABLE_DECLARATION(gPeiMemoryDiscoveredPpiGuid, PEI_PERMANENT_MEMORY_INSTALLED_PPI_GUID);
/****** DO NOT WRITE BELOW THIS LINE *******/
#ifdef __cplusplus
}
#endif
#endif
//**********************************************************************
//**********************************************************************
//**                                                                  **
//**        (C)Copyright 1985-2006, American Megatrends, Inc.         **
//**                                                                  **
//**                       All Rights Reserved.                       **
//**                                                                  **
//**             6145-F Northbelt Pkwy, Norcross, GA 30071            **
//**                                                                  **
//**                       Phone: (770)-246-8600                      **
//**                                                                  **
//**********************************************************************
//**********************************************************************
