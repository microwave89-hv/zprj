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
// $Header: /Alaska/SOURCE/Core/EDK/PPI/FindFv.h 1     5/19/06 11:28p Felixp $
//
// $Revision: 1 $
//
// $Date: 5/19/06 11:28p $
//**********************************************************************
// Revision History
// ----------------
// $Log: /Alaska/SOURCE/Core/EDK/PPI/FindFv.h $
// 
// 1     5/19/06 11:28p Felixp
// 
// 1     3/13/06 1:57a Felixp
// 
//**********************************************************************
//<AMI_FHDR_START>
//
// Name:	FindFv.h
//
// Description:	
//
//<AMI_FHDR_END>
//**********************************************************************
#ifndef __FIND_FV_PPI__H__
#define __FIND_FV_PPI__H__
#ifdef __cplusplus
extern "C" {
#endif
#include <PEI.h>
#include <FFS.h>

#define EFI_FIND_FV_PPI_GUID \
	{ 0x36164812, 0xa023, 0x44e5, 0xbd, 0x85, 0x5, 0xbf, 0x3c, 0x77, 0x0, 0xaa }

typedef struct _EFI_FIND_FV_PPI EFI_FIND_FV_PPI;

typedef EFI_STATUS (EFIAPI *EFI_FIND_FV_FINDFV)(
	IN EFI_FIND_FV_PPI * This,
	IN EFI_PEI_SERVICES **PeiServices,
	UINT8 *FvNumber, EFI_FIRMWARE_VOLUME_HEADER **FVAddress
);

struct _EFI_FIND_FV_PPI {
	EFI_FIND_FV_FINDFV  FindFv;
};

GUID_VARIABLE_DECLARATION(gEfiFindFvPpiGuid, EFI_FIND_FV_PPI_GUID);
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