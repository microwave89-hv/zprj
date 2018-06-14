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
// $Header: /Alaska/SOURCE/Core/EDK/PPI/Security.h 1     5/19/06 11:28p Felixp $
//
// $Revision: 1 $
//
// $Date: 5/19/06 11:28p $
//**********************************************************************
// Revision History
// ----------------
// $Log: /Alaska/SOURCE/Core/EDK/PPI/Security.h $
// 
// 1     5/19/06 11:28p Felixp
// 
// 1     3/13/06 1:57a Felixp
// 
//**********************************************************************
//<AMI_FHDR_START>
//
// Name:	Security.h
//
// Description:	
//
//<AMI_FHDR_END>
//**********************************************************************
#ifndef __SECURITY_PPI_H__
#define __SECURITY_PPI_H__
#ifdef __cplusplus
extern "C" {
#endif
#include <PEI.h>
#include <FFS.h>

#define PEI_SECURITY_PPI_GUID \
	{ 0x1388066e, 0x3a57, 0x4efa, 0x98, 0xf3, 0xc1, 0x2f, 0x3a, 0x95, 0x8a, 0x29 }

typedef struct _PEI_SECURITY_PPI PEI_SECURITY_PPI;

typedef EFI_STATUS (EFIAPI *PEI_SECURITY_AUTHENTICATION_STATE)(
	IN EFI_PEI_SERVICES **PeiServices,
	IN PEI_SECURITY_PPI *This,
	IN UINT32 AuthenticationStatus,
	IN EFI_FFS_FILE_HEADER *FfsFileHeader,
	IN OUT BOOLEAN *StartCrisisRecovery
);

struct _PEI_SECURITY_PPI {
  PEI_SECURITY_AUTHENTICATION_STATE AuthenticationState;
};

GUID_VARIABLE_DECLARATION(gPeiSecurityPpiGuid, PEI_SECURITY_PPI_GUID);

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