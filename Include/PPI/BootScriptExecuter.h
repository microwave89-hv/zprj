//**********************************************************************//
//**********************************************************************//
//**                                                                  **//
//**        (C)Copyright 1985-2003, American Megatrends, Inc.         **//
//**                                                                  **//
//**                       All Rights Reserved.                       **//
//**                                                                  **//
//**             6145-F Northbelt Pkwy, Norcross, GA 30071            **//
//**                                                                  **//
//**                       Phone: (770)-246-8600                      **//
//**                                                                  **//
//**********************************************************************//
//**********************************************************************//

//**********************************************************************
// $Header: /Alaska/BIN/Core/Include/PPI/BootScriptExecuter.h 2     3/13/06 1:16a Felixp $
//
// $Revision: 2 $
//
// $Date: 3/13/06 1:16a $
//**********************************************************************
// Revision History
// ----------------
// $Log: /Alaska/BIN/Core/Include/PPI/BootScriptExecuter.h $
// 
// 2     3/13/06 1:16a Felixp
// 
// 1     1/28/05 12:44p Felixp
// 
// 1     12/23/04 9:41a Felixp
// 
// 1     2/26/04 2:45p Markw
// 
//**********************************************************************
//<AMI_FHDR_START>
//
// Name:	BootScriptExecuter_h
//
// Description:
//
//<AMI_FHDR_END>
//**********************************************************************
#ifndef __BOOT_SCRIPT_EXECUTER_PPI__H__
#define __BOOT_SCRIPT_EXECUTER_PPI__H__
#include <PEI.h>

#ifdef __cplusplus
extern "C" {
#endif

#define EFI_PEI_BOOT_SCRIPT_EXECUTER_PPI_GUID \
	{0xabd42895,0x78cf,0x4872,0x84,0x44,0x1b,0x5c,0x18,0x0b,0xfb,0xff}

GUID_VARIABLE_DECLARATION(gPeiBootScriptExecuterPpiGuid,EFI_PEI_BOOT_SCRIPT_EXECUTER_PPI_GUID);

typedef struct _EFI_PEI_BOOT_SCRIPT_EXECUTER_PPI EFI_PEI_BOOT_SCRIPT_EXECUTER_PPI;

typedef EFI_STATUS (EFIAPI * EFI_PEI_BOOT_SCRIPT_EXECUTE) (
	IN EFI_PEI_SERVICES					**PeiServices,
	IN EFI_PEI_BOOT_SCRIPT_EXECUTER_PPI	*This,
	IN EFI_PHYSICAL_ADDRESS				Address,
	IN EFI_GUID							*FvFile OPTIONAL
);

struct _EFI_PEI_BOOT_SCRIPT_EXECUTER_PPI {
	EFI_PEI_BOOT_SCRIPT_EXECUTE Execute;
};


/****** DO NOT WRITE BELOW THIS LINE *******/
#ifdef __cplusplus
}
#endif
#endif

//**********************************************************************//
//**********************************************************************//
//**                                                                  **//
//**        (C)Copyright 1985-2003, American Megatrends, Inc.         **//
//**                                                                  **//
//**                       All Rights Reserved.                       **//
//**                                                                  **//
//**             6145-F Northbelt Pkwy, Norcross, GA 30071            **//
//**                                                                  **//
//**                       Phone: (770)-246-8600                      **//
//**                                                                  **//
//**********************************************************************//
//**********************************************************************//
